#include "string.h"
#include "RobotVarMarco.h"
#include "RobotVar.h"
#include "UartHw.h"
#include "MdsModlink.h"
#include "MdsParaCheck.h"
#include "mdbus.h"


#if	(ENABLE_DEBUG)
#define _yPrintf		LOGE
#else
#define _yPrintf(...)
#endif


struct tag_UartDcb gat_UartDcb[MAX_UART_NUM];
unsigned char ma2u8_SendBuf[MAX_UART_NUM][UART_MAX_BUF];
static unsigned char ma2u8_Rec0Buf[MAX_UART_NUM][UART_MAX_BUF];
static unsigned char ma2u8_Rec1Buf[MAX_UART_NUM][UART_MAX_BUF];


// ��ȡϵͳ��ǰ������
unsigned long _yGetCurMsTime(void)
{
    return gu32_CurMsTime;
}

unsigned long _yIs1msTimeout(unsigned long uiOrignal, unsigned long uiTimeout)
{
    unsigned int ui_TimeofUs;
    unsigned int ui_TimeOffset;
    
    ui_TimeofUs = _yGetCurMsTime();       // ȡ1ms��������ǰֵ
    if( ui_TimeofUs >= uiOrignal ) {
        ui_TimeOffset = ui_TimeofUs - uiOrignal;
    }
    else {
        ui_TimeOffset = ~uiOrignal + ui_TimeofUs + 1;
    }
    
    if( ui_TimeOffset >= uiTimeout ) {
        return 1;
    }
    return 0;
}

static void _yUartSendByte(struct tag_UartDcb *pdcb)
{
    if(0x0 ==pdcb->TxCnt) {
        return ;
    }

	pdcb->TxStTime = _yGetCurMsTime();
    pdcb->flag.isTxing =1;
	pdcb->Txflg = 1;
}

void _yInitUartDcb(void)
{
    struct tag_UartDcb *Pdcb;
    unsigned long i;

    Pdcb =&gat_UartDcb[0];
    for(i=0; i<MAX_UART_NUM; i++) {
        *((unsigned short *)(&Pdcb->flag)) =0;  // ���ڱ�־

        Pdcb->TxStTime = 0;                     // ���Ϳ�ʼʱ��
        Pdcb->TxTimeout = 1000;                 // ���ͳ�ʱʱ��
        Pdcb->RxChgFarmTime =2;                 //�����л�һ������ʱ��
        Pdcb->RxStTime = 0;                     // ���տ�ʼ��ʱ��

        Pdcb->pTxBuf = &ma2u8_SendBuf[i][0];    // ��ʵ���ͻ�����
        Pdcb->TxCnt =0;                         // ��ʵҪ�������ݵĸ���
        Pdcb->Txflg = 0;
        Pdcb->pRxBuf = &ma2u8_Rec0Buf[i][0];    // ��ʵ���ջ�����
        Pdcb->RxCnt = 0;                        // ��ʵ�������ݸ���
        Pdcb->paRxBuf[0] = &ma2u8_Rec0Buf[i][0];// ���ݽ��ջ�����
        Pdcb->aRxCnt[0] = 0;                    // ���ݽ��յ����ݸ���
        Pdcb->paRxBuf[1] =&ma2u8_Rec1Buf[i][0]; // ���ݽ��ջ�����
        Pdcb->aRxCnt[1] = 0;                    // ���ݽ��յ����ݸ���

        Pdcb->baud = 115200;
        Pdcb->datalen = 8;                      // ���ݿ��,7,8
        Pdcb->stoplen = 2;                      // ֹͣλ,1,2
        Pdcb->evenodd = 0;                      // Ч��֤��0,1,2
        
        Pdcb->pfSendByte =_yUartSendByte;
        Pdcb++;
    }
}

unsigned short _yMdsMasterCheckRcvPack(struct tag_ModlinkFlag *pflg)
{
    unsigned long i;
	unsigned short mchId;
    unsigned short lenth;
	unsigned short cnt_crc;
	unsigned short cur_crc;

    if(pflg->rcvLen <4) {                       // ������̫С
        return 1;
    }

    mchId = pflg->pRcBuf[0];                    // �豸��
	if(mchId !=USID) {	                        // �豸��ַ�ж�
	    return 2;
	}

    lenth = pflg->rcvLen -2;
    cnt_crc =Crc_Check(pflg->pRcBuf, lenth);    // ����У����
    cur_crc = *(pflg->pRcBuf +lenth);
    cur_crc <<= 8;
    cur_crc += (*(pflg->pRcBuf +lenth +1));
    if(cur_crc !=cnt_crc) {                     // CRCЧ�����
        return 3;
    }

    return 0;
}

void _yMdsMasterProtocolRev(void)
{
    struct tag_UartDcb *pdcb;
    struct tag_ModlinkFlag *pflg;
    struct tag_ModelinkRecord *precord;
    struct tag_MdsModlinkCmd *pcmd;
    struct tag_MdsElemMap *pmap;
    unsigned char *pu8Tmp;
	unsigned char *pu8Cpy;
    unsigned short *pu16Tmp;
	unsigned short *pu16Cpy;
    unsigned long *pu32Tmp;
    unsigned short elmadr;
    unsigned short i,j,k,m;
    
    pdcb =&gat_UartDcb[0];
    if((pdcb->flag.isTxing) ||(pdcb->flag.isRxing)) {                  // ��վ���ڷ���,�������ڽ���
        return ;
    }

    pflg =&gt_ModeLinkFlag;
	if(pdcb->flag.HaveRxMsg ==0) {                                 		// û�н��յ��������ݰ�
        if(pflg->MainSend >0) {                                         // ��վ����������
            if( _yIs1msTimeout(pdcb->TxStTime, pdcb->TxTimeout) ) {     // ������Ӧ�ӳ�ʱ�䵽
                if(pflg->RetryTick ==0) {                               // ���Դ�����
                    pflg->MainSend = 0;                                 // ����վ�������־
                    pflg->RunNxtList = 1;                               // ִ����һ����־
                }
                else {
                    pdcb->pTxBuf = pflg->pSdBuf;
                    pdcb->TxCnt = pflg->sendLen;
                    pdcb->pfSendByte(pdcb);
                    pdcb->TxStTime = _yGetCurMsTime();
                    pflg->RetryTick--;                                  // �ط�������һ 
                }
                return ;
            }
        }
        return ;
    }

    if(0x2 ==pdcb->flag.Rx0Flg) {                                       // Pack״̬������
        pdcb->flag.Rx0Flg =0x3;
        pflg->pRcBuf =pdcb->paRxBuf[0];
        pflg->rcvLen =pdcb->aRxCnt[0];
    }
    else if(0x2 ==pdcb->flag.Rx1Flg) {
        pdcb->flag.Rx1Flg =0x3;
        pflg->pRcBuf =pdcb->paRxBuf[1];
        pflg->rcvLen =pdcb->aRxCnt[1];
    }
    else {
        pdcb->flag.HaveRxMsg = 0;
        return ;
    }

    if(_yMdsMasterCheckRcvPack(pflg)) {                                 // Ч���������
        pflg->MainSend = 0;                                             // ����վ�������־
        pflg->RunNxtList = 1;                                           // ִ����һ����־
        pdcb->flag.HaveRxMsg--;
        if(0x3 ==pdcb->flag.Rx0Flg) {                                   // Pack״̬������
            pdcb->flag.Rx0Flg =0x0;
        }
        else {
            pdcb->flag.Rx1Flg =0x0;
        }
        return;
    }

    precord = list_entry(pflg->pcur, struct tag_ModelinkRecord, list);
    pcmd = (struct tag_MdsModlinkCmd *)(precord->pvoid);
    if((pflg->pcur) &&(pcmd->cmd ==pflg->pRcBuf[1])) {                  // ��������ϴ��յ��Ĺ�������ͬ
        switch(pcmd->cmd) {
        case RdMutiBit:     // �������Ȧ
		case RdMutiIn:      // ��ȡ�������
            elmadr = pcmd->opAdr;
            if((pflg->rcvLen-5) ==(pflg->pRcBuf[2])) {                  // �ֽ���ƥ��
                if((pflg->pRcBuf[2]*8) >=pcmd->opCnt) {                 // �ظ�����ƥ��
                    pmap = _yMgetMdsElmIfo(pcmd->cmd, pcmd->pname, _yGetStrLen(pcmd->pname), elmadr);
                    if(pmap) {                                          // ���ҵ�
                        pu8Tmp = (unsigned char *)(pmap->pElemAdr);
                        j = elmadr;
                        k = 0;
                        m = 0;
                        for(i=0; i<pcmd->opCnt; i++) {
							if(pflg->pRcBuf[3+m] &(1<<k)) {
								pu8Tmp[j] = 1;
							}
							else {
								pu8Tmp[j] = 0;
							}
                            j++;
                            k++;
                            if(k >=8) {
                                k = 0;
                                m++;
                            }                                
                        }

						//if(!_yPointEq(pmap->pElemAdr, pmap->pWtElmAdr)) {
						//    pu8Tmp =(unsigned char *)(pmap->pElemAdr);
						//	pu8Cpy =(unsigned char *)(pmap->pWtElmAdr);
						//	for(i=pcmd->opAdr; i<(pcmd->opAdr +pcmd->opCnt); i++) {
						//		pu8Cpy[i] = pu8Tmp[i];
						//	}
						//}
						if(pcmd->MstDel) {
							if(pcmd->cnt >0) {
								pcmd->cnt--;
							}
						}
						if(pcmd->pname[1]!='\0') {
							_yPrintf("RdMutiBit %c%c%d Num=%d ok!\n", pcmd->pname[0], pcmd->pname[1], pcmd->opAdr, pcmd->opCnt);
						}
						else {
							_yPrintf("RdMutiBit %c%d Num=%d ok!\n", pcmd->pname[0], pcmd->opAdr, pcmd->opCnt);
						}
                    }
                }
            }
            break;
			
        case RdMutiReg:     // ������Ĵ���
            elmadr = pcmd->opAdr;
            if((pflg->rcvLen-5) ==(pflg->pRcBuf[2])) {                  // �ֽ���ƥ��
                if((pflg->pRcBuf[2]/2) ==pcmd->opCnt) {                 // �ظ�����ƥ��
                    pmap = _yMgetMdsElmIfo(RdMutiReg, pcmd->pname, _yGetStrLen(pcmd->pname), elmadr);
                    if(!pmap) {                                         // û���ҵ�,�˳�
                        break;
                    }
                    if(pmap->mode ==MdsMode1) {                                // ˫��Ѱַ
                        pu32Tmp = (unsigned long *)(pmap->pElemAdr);
                        j = elmadr;
                        k = 0;
                        for(i=0; i<pcmd->opCnt/2; i++) {
                            pu32Tmp[j] = pflg->pRcBuf[3+k];
                            pu32Tmp[j] <<= 8;
							k++;
							
                            pu32Tmp[j] += pflg->pRcBuf[3+k];
                            pu32Tmp[j] <<= 8;
							k++;

                            pu32Tmp[j] += pflg->pRcBuf[3+k];
                            pu32Tmp[j] <<= 8;
							k++;
							
                            pu32Tmp[j] += pflg->pRcBuf[3+k];
                            k++;
							j++;
                        }
                    }
                    else {                                              // ����Ѱַ
                        pu16Tmp = (unsigned short *)(pmap->pElemAdr);
                        j = elmadr;
                        k = 0;
                        for(i=0; i<pcmd->opCnt; i++) {
                            pu16Tmp[j] = pflg->pRcBuf[3+k];
                            pu16Tmp[j] <<= 8;
                            k++;

                            pu16Tmp[j] += pflg->pRcBuf[3+k];
                            k++;
							j++;
                        }
                    }

					if(pcmd->MstDel) {
						if(pcmd->cnt >0) {
							pcmd->cnt--;
						}
					}
					if(pcmd->pname[1]!='\0') {
						_yPrintf("RdMutiReg %c%c%d Num=%d ok!\n", pcmd->pname[0], pcmd->pname[1], pcmd->opAdr, pcmd->opCnt);
					}
					else {
						_yPrintf("RdMutiReg %c%d Num=%d ok!\n", pcmd->pname[0], pcmd->opAdr, pcmd->opCnt);
					}
                }
            }
            break;
            
        case WrSimpBit:     // д������Ȧ
			if(pcmd->MstDel) {
				if(pcmd->cnt >0) {
					pcmd->cnt--;
				}
			}
			if(pcmd->pname[1]!='\0') {
				_yPrintf("WrSimpBit %c%c%d Num=%d ok!\n", pcmd->pname[0], pcmd->pname[1], pcmd->opAdr, pcmd->opCnt);
			}
			else {
				_yPrintf("WrSimpBit %c%d Num=%d ok!\n", pcmd->pname[0], pcmd->opAdr, pcmd->opCnt);
			}
        	break;        
        case WrSimpReg:     // д�����Ĵ���
			if(pcmd->MstDel) {
				if(pcmd->cnt >0) {
					pcmd->cnt--;
				}
			}        
			if(pcmd->pname[1]!='\0') {
				_yPrintf("WrSimpReg %c%c%d Num=%d ok!\n", pcmd->pname[0], pcmd->pname[1], pcmd->opAdr, pcmd->opCnt);
			}
			else {
				_yPrintf("WrSimpReg %c%d Num=%d ok!\n", pcmd->pname[0], pcmd->opAdr, pcmd->opCnt);
			}
        	break;        
        case WrMutiBit:     // д�����Ȧ
			if(pcmd->MstDel) {
				if(pcmd->cnt >0) {
					pcmd->cnt--;
				}
			}
			if(pcmd->pname[1]!='\0') {
				_yPrintf("WrMutiBit %c%c%d Num=%d ok!\n", pcmd->pname[0], pcmd->pname[1], pcmd->opAdr, pcmd->opCnt);
			}
			else {
				_yPrintf("WrMutiBit %c%d Num=%d ok!\n", pcmd->pname[0], pcmd->opAdr, pcmd->opCnt);
			}
        	break;        
        case WrMutiReg:     // д����Ĵ���
			if(pcmd->MstDel) {
				if(pcmd->cnt >0) {
					pcmd->cnt--;
				}
			}
			if(pcmd->pname[1]!='\0') {
				_yPrintf("WrMutiReg %c%c%d Num=%d ok!\n", pcmd->pname[0], pcmd->pname[1], pcmd->opAdr, pcmd->opCnt);
			}
			else {
				_yPrintf("WrMutiReg %c%d Num=%d ok!\n", pcmd->pname[0], pcmd->opAdr, pcmd->opCnt);
			}
        	break;
        default:            // д��־����������Ҫ����
            break;
        }

        pflg->MainSend = 0;                                             // ����վ�������־
        pflg->RunNxtList = 1;                                           // ִ����һ����־
        pdcb->flag.HaveRxMsg--;
        if(0x3 ==pdcb->flag.Rx0Flg) {                                   // Pack״̬������
            pdcb->flag.Rx0Flg =0x0;
        }
        else {
            pdcb->flag.Rx1Flg =0x0;
        }
        return;        
    }
    else {                                                              // ȫ˫��ģʽ,��վ��������������
        //switch(pflg->pRcBuf[1]) {                                       // ��վ��Ҫ���ߴ�վ�Ѿ��յ���ȷ����,��ʱֹͣ
        //default:
        //    break;
        //}

        pflg->MainSend = 0;                                             // ����վ�������־
        pflg->RunNxtList = 1;                                           // ִ����һ����־
        pdcb->flag.HaveRxMsg--;
        if(0x3 ==pdcb->flag.Rx0Flg) {                                   // Pack״̬������
            pdcb->flag.Rx0Flg =0x0;
        }
        else {
            pdcb->flag.Rx1Flg =0x0;
        }        
    }
}





