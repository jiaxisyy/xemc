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


// 获取系统当前毫秒数
unsigned long _yGetCurMsTime(void)
{
    return gu32_CurMsTime;
}

unsigned long _yIs1msTimeout(unsigned long uiOrignal, unsigned long uiTimeout)
{
    unsigned int ui_TimeofUs;
    unsigned int ui_TimeOffset;
    
    ui_TimeofUs = _yGetCurMsTime();       // 取1ms计数器当前值
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
        *((unsigned short *)(&Pdcb->flag)) =0;  // 串口标志

        Pdcb->TxStTime = 0;                     // 发送开始时间
        Pdcb->TxTimeout = 1000;                 // 发送超时时间
        Pdcb->RxChgFarmTime =2;                 //接收切换一包数据时间
        Pdcb->RxStTime = 0;                     // 接收开始的时间

        Pdcb->pTxBuf = &ma2u8_SendBuf[i][0];    // 真实发送缓冲区
        Pdcb->TxCnt =0;                         // 真实要发送数据的个数
        Pdcb->Txflg = 0;
        Pdcb->pRxBuf = &ma2u8_Rec0Buf[i][0];    // 真实接收缓冲区
        Pdcb->RxCnt = 0;                        // 真实接收数据个数
        Pdcb->paRxBuf[0] = &ma2u8_Rec0Buf[i][0];// 备份接收缓冲区
        Pdcb->aRxCnt[0] = 0;                    // 备份接收到数据个数
        Pdcb->paRxBuf[1] =&ma2u8_Rec1Buf[i][0]; // 备份接收缓冲区
        Pdcb->aRxCnt[1] = 0;                    // 备份接收到数据个数

        Pdcb->baud = 115200;
        Pdcb->datalen = 8;                      // 数据宽度,7,8
        Pdcb->stoplen = 2;                      // 停止位,1,2
        Pdcb->evenodd = 0;                      // 效验证，0,1,2
        
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

    if(pflg->rcvLen <4) {                       // 数据量太小
        return 1;
    }

    mchId = pflg->pRcBuf[0];                    // 设备号
	if(mchId !=USID) {	                        // 设备地址判断
	    return 2;
	}

    lenth = pflg->rcvLen -2;
    cnt_crc =Crc_Check(pflg->pRcBuf, lenth);    // 计算校验码
    cur_crc = *(pflg->pRcBuf +lenth);
    cur_crc <<= 8;
    cur_crc += (*(pflg->pRcBuf +lenth +1));
    if(cur_crc !=cnt_crc) {                     // CRC效验错误
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
    if((pdcb->flag.isTxing) ||(pdcb->flag.isRxing)) {                  // 主站增在发送,或者正在接收
        return ;
    }

    pflg =&gt_ModeLinkFlag;
	if(pdcb->flag.HaveRxMsg ==0) {                                 		// 没有接收到完整数据包
        if(pflg->MainSend >0) {                                         // 主站发送了数据
            if( _yIs1msTimeout(pdcb->TxStTime, pdcb->TxTimeout) ) {     // 发送响应延迟时间到
                if(pflg->RetryTick ==0) {                               // 重试次数到
                    pflg->MainSend = 0;                                 // 清主站事务处理标志
                    pflg->RunNxtList = 1;                               // 执行下一条标志
                }
                else {
                    pdcb->pTxBuf = pflg->pSdBuf;
                    pdcb->TxCnt = pflg->sendLen;
                    pdcb->pfSendByte(pdcb);
                    pdcb->TxStTime = _yGetCurMsTime();
                    pflg->RetryTick--;                                  // 重发次数减一 
                }
                return ;
            }
        }
        return ;
    }

    if(0x2 ==pdcb->flag.Rx0Flg) {                                       // Pack状态机处理
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

    if(_yMdsMasterCheckRcvPack(pflg)) {                                 // 效验包出错了
        pflg->MainSend = 0;                                             // 清主站事务处理标志
        pflg->RunNxtList = 1;                                           // 执行下一条标志
        pdcb->flag.HaveRxMsg--;
        if(0x3 ==pdcb->flag.Rx0Flg) {                                   // Pack状态机处理
            pdcb->flag.Rx0Flg =0x0;
        }
        else {
            pdcb->flag.Rx1Flg =0x0;
        }
        return;
    }

    precord = list_entry(pflg->pcur, struct tag_ModelinkRecord, list);
    pcmd = (struct tag_MdsModlinkCmd *)(precord->pvoid);
    if((pflg->pcur) &&(pcmd->cmd ==pflg->pRcBuf[1])) {                  // 功能吗和上次收到的功能码相同
        switch(pcmd->cmd) {
        case RdMutiBit:     // 读多个线圈
		case RdMutiIn:      // 读取多个输入
            elmadr = pcmd->opAdr;
            if((pflg->rcvLen-5) ==(pflg->pRcBuf[2])) {                  // 字节数匹配
                if((pflg->pRcBuf[2]*8) >=pcmd->opCnt) {                 // 回复数据匹配
                    pmap = _yMgetMdsElmIfo(pcmd->cmd, pcmd->pname, _yGetStrLen(pcmd->pname), elmadr);
                    if(pmap) {                                          // 查找到
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
			
        case RdMutiReg:     // 读多个寄存器
            elmadr = pcmd->opAdr;
            if((pflg->rcvLen-5) ==(pflg->pRcBuf[2])) {                  // 字节数匹配
                if((pflg->pRcBuf[2]/2) ==pcmd->opCnt) {                 // 回复数据匹配
                    pmap = _yMgetMdsElmIfo(RdMutiReg, pcmd->pname, _yGetStrLen(pcmd->pname), elmadr);
                    if(!pmap) {                                         // 没有找到,退出
                        break;
                    }
                    if(pmap->mode ==MdsMode1) {                                // 双字寻址
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
                    else {                                              // 单字寻址
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
            
        case WrSimpBit:     // 写单个线圈
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
        case WrSimpReg:     // 写单个寄存器
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
        case WrMutiBit:     // 写多个线圈
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
        case WrMutiReg:     // 写多个寄存器
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
        default:            // 写标志和其他不需要处理
            break;
        }

        pflg->MainSend = 0;                                             // 清主站事务处理标志
        pflg->RunNxtList = 1;                                           // 执行下一条标志
        pdcb->flag.HaveRxMsg--;
        if(0x3 ==pdcb->flag.Rx0Flg) {                                   // Pack状态机处理
            pdcb->flag.Rx0Flg =0x0;
        }
        else {
            pdcb->flag.Rx1Flg =0x0;
        }
        return;        
    }
    else {                                                              // 全双工模式,从站主动发送来代码
        //switch(pflg->pRcBuf[1]) {                                       // 主站需要告诉从站已经收到正确命令,暂时停止
        //default:
        //    break;
        //}

        pflg->MainSend = 0;                                             // 清主站事务处理标志
        pflg->RunNxtList = 1;                                           // 执行下一条标志
        pdcb->flag.HaveRxMsg--;
        if(0x3 ==pdcb->flag.Rx0Flg) {                                   // Pack状态机处理
            pdcb->flag.Rx0Flg =0x0;
        }
        else {
            pdcb->flag.Rx1Flg =0x0;
        }        
    }
}





