//----------------------------------------------------
//Copyright (C), 2016,  Kawakp.
//版权所有 (C), 2016,   Kawakp.
//所属模块:	APP modbus通讯库模块
//作者：yjs
//版本：V1.0.0
//初始版本完成日期：2016-04-20
//文件描述: Modbus主站通讯命令定义
//其他说明: 如果需要增加别的通讯变量,只需要增加"gat_MdsHighCmd"和"gat_MdsLowCmd"变量表
//修订历史:
//2. ...
//1. 日期: 2016-04-20
//   作者: yjs
//   新版本号: V1.0.0
//   修改说明: 原始版本 
//------------------------------------------------------
#include "RobotVar.h"
#include "MdsModlink.h"
#include "MdsParaCheck.h"
#include "UartHw.h"
#include "mdbus.h"


#if	(ENABLE_DEBUG)
#define _yPrintf		LOGE
#else
#define _yPrintf(...)
#endif

// 最大支持100条通讯,但为了速度保证,最好次表长度控制在10条内
unsigned long gu32_MdsHcmdCnt;
struct tag_MdsModlinkCmd gat_MdsHighCmd[] = {
/*id        cmd        IsStop    MstDel   cnt    pname    opAdr     opCnt     save      */
{ USID,   RdMutiBit,	0,		   0,	  0,	 "Y",		0,		  256,		0 },   	// 读取下位机Y0开始的100个位元件

{ USID,   RdMutiBit,	0,		   0,	  0,	 "M",		0,	      1000,		0 },	// 读取下位机M0 开始的1000个位元件
{ USID,   WrMutiBit,    0,         1,     0,     "M",       0,        1000,     0 },	// 写入M0 开始的1000个位元件到下位机
{ USID,   WrMutiBit,	0,		   1,	  1,	 "M",		1000,	  1000,		0 },   	// 写入M1000 开始的1000个位元件到下位机

{ USID,   RdMutiReg,	0,		   0,	  1,	 "D",	   0,		 100,	   0 }, 	// 读取下位机D0 开始的100个字元件
{ USID,   WrMutiReg,	0,		   1,	  0,	 "D",		0,		100,	0 },   // 写入下位机D0 开始的100个字元件
{ USID,   RdMutiReg,	0,		   0,	  1,	 "D",	   100, 	 100,	   0 }, 	// 读取下位机D100 开始的100个字元件
{ USID,   WrMutiReg,	0,		   1,	  0,	 "D",		100,	100,	0 },   // 写入下位机D100 开始的100个字元件
{ USID,   RdMutiReg,    0,         0,     1,     "D",      200,      100,      0 },   	// 读取下位机D200 开始的100个字元件
{ USID,   WrMutiReg,	0,		   1,	  0,	 "D",		200,	100,	0 },   // 写入下位机D200 开始的100个字元件
{ USID,   RdMutiReg,    0,         0,     1,     "D",      300,      100,      0 },		// 读取下位机D300 开始的100个字元件
{ USID,   WrMutiReg,	0,		   1,	  0,	 "D",		300,	100,	0 },   // 写入下位机D300 开始的100个字元件

{ UNUSE,  0,            0,         0,     0,     "",        0,        0,        0 }    // 最后一条，必须放最后
};


// 最大支持100条通讯
unsigned long gu32_MdsLcmdCnt;
struct tag_MdsModlinkCmd gat_MdsLowCmd[] = {
/*id        cmd        IsStop   MstDel    cnt    pname    opAdr     opCnt    save */
{ USID,   RdMutiBit,    0,         0,     0,  	 "X",       0,        256,      0 },   	// 读取下位机X0 开始的100个位元件
{ USID,   WrMutiBit,    0,         1,     0,     "Y",       0,        256,      0 },   	// 写入Y0 开始的100个位元件到下位机
{ USID,   RdMutiBit,	0,		   0,	  0,	 "M",		1000,	  1000, 	0 },	// 读取下位机M1000 开始的1000个位元件

{ USID,   RdMutiReg,	0,		   0,	  1,	 "D",	   400, 	 100,	   0 },   	// 读取下位机D400 开始的100个字元件
{ USID,   WrMutiReg,	0,		   1,	  0,	 "D",		400,	100,	0 },   // 写入下位机D400 开始的100个字元件
{ USID,   RdMutiReg,    0,         0,     1,     "D",      500,      100,      0 },   	// 读取下位机D500 开始的100个字元件
{ USID,   WrMutiReg,	0,		   1,	  0,	 "D",		500,	100,	0 },   // 写入下位机D500 开始的100个字元件
{ USID,   RdMutiReg,    0,         0,     1,     "D",      600,      100,      0 },   	// 读取下位机D600 开始的100个字元件
{ USID,   WrMutiReg,	0,		   1,	  0,	 "D",		600,	100,	0 },   // 写入下位机D600 开始的100个字元件
{ USID,   RdMutiReg,	0,		   0,	  1,	 "D",	   700, 	 100,	   0 },   	// 读取下位机D700 开始的100个字元件
{ USID,   WrMutiReg,	0,		   1,	  0,	 "D",		700,	100,	0 },   // 写入下位机D700 开始的100个字元件

{ USID,   RdMutiReg,    0,         0,     1,     "D",      800,      100,      0 },   	// 读取下位机D800 开始的100个字元件
{ USID,   WrMutiReg,	0,		   1,	  0,	 "D",		800,	100,	0 },   // 写入下位机D800 开始的100个字元件
{ USID,   RdMutiReg,    0,         0,     1,     "D",      900,      100,      0 },   	// 读取下位机D900 开始的100个字元件
{ USID,   WrMutiReg,	0,		   1,	  0,	 "D",		900,	100,	0 },   // 写入下位机D900 开始的100个字元件
{ USID,   RdMutiReg,	0,		   0,	  1,	 "D",	   1000, 	 100,	   0 },   	// 读取下位机D1000 开始的100个字元件
{ USID,   WrMutiReg,	0,		   1,	  0,	 "D",		1000,	100,	0 },   // 写入下位机D1000 开始的100个字元件
{ USID,   RdMutiReg,	0,		   0,	  1,	 "D",	   1100, 	 100,	   0 },   	// 读取下位机D1100 开始的100个字元件
{ USID,   WrMutiReg,	0,		   1,	  0,	 "D",		1100,	100,	0 },   // 写入下位机D1100 开始的100个字元件

{ USID,   RdMutiReg,    0,         0,     1,     "D",      1200,     100,      0 },   	// 读取下位机D1200 开始的100个字元件
{ USID,   WrMutiReg,	0,		   1,	  0,	 "D",		1200,	100,	0 },   // 写入下位机D1200 开始的100个字元件
{ USID,   RdMutiReg,    0,         0,     1,     "D",      1300,     100,      0 },   	// 读取下位机D1300 开始的100个字元件
{ USID,   WrMutiReg,	0,		   1,	  0,	 "D",		1300,	100,	0 },   // 写入下位机D1300 开始的100个字元件
{ USID,   RdMutiReg,	0,		   0,	  1,	 "D",	   1400, 	 100,	   0 },   	// 读取下位机D1400 开始的100个字元件
{ USID,   WrMutiReg,	0,		   1,	  0,	 "D",		1400,	100,	0 },   // 写入下位机D1400 开始的100个字元件
{ USID,   RdMutiReg,	0,		   0,	  1,	 "D",	   1500, 	 100,	   0 },   	// 读取下位机D1500 开始的100个字元件
{ USID,   WrMutiReg,	0,		   1,	  0,	 "D",		1500,	100,	0 },   // 写入下位机D1500 开始的100个字元件

{ USID,   RdMutiReg,    0,         0,     1,     "D",      1600,     100,      0 },   	// 读取下位机D1600 开始的100个字元件
{ USID,   WrMutiReg,	0,		   1,	  0,	 "D",		1600,	100,	0 },   // 写入下位机D1600 开始的100个字元件
{ USID,   RdMutiReg,    0,         0,     1,     "D",      1700,     100,      0 },   	// 读取下位机D1700 开始的100个字元件
{ USID,   WrMutiReg,	0,		   1,	  0,	 "D",		1700,	100,	0 },   // 写入下位机D1700 开始的100个字元件
{ USID,   RdMutiReg,	0,		   0,	  1,	 "D",	   1800, 	 100,	   0 },   	// 读取下位机D1800 开始的100个字元件
{ USID,   WrMutiReg,	0,		   1,	  0,	 "D",		1800,	100,	0 },   // 写入下位机D1800 开始的100个字元件
{ USID,   RdMutiReg,	0,		   0,	  1,	 "D",	   1900, 	 100,	   0 },   	// 读取下位机D1900 开始的100个字元件
{ USID,   WrMutiReg,	0,		   1,	  0,	 "D",		1900,	100,	0 },   // 写入下位机D1900 开始的100个字元件

{ USID,   RdMutiReg,    0,         1,     1,     "SD",      0,     100,      0 },		// 读取下位机SD0 开始的100个字元件,只读取一次
{ USID,   RdMutiReg,	0,		   1,	  1,	 "SM",		0,	   512, 	 0 },		// 读取下位机SM0 开始的512个位元件,只读取一次

{ UNUSE,  0,            0,         0,     0,     "",        0,        0,        0 }    // 最后一条，必须放最后
};

struct tag_ModelinkRecord gat_ModelinkRecord[MAX_MODELINK_RECORD];
struct tag_ModlinkFlag gt_ModeLinkFlag;

unsigned long _yInitModlinkVar(void)
{
    struct tag_ModelinkRecord *precord;
    struct tag_ModlinkFlag *pflg;
    struct tag_MdsModlinkCmd *phcmd;
    unsigned long hcnt;
    struct tag_MdsModlinkCmd *plcmd;
    unsigned long lcnt;
    unsigned long i,j,k;
    
    phcmd = &gat_MdsHighCmd[0];
    hcnt = 0;
	gu32_MdsHcmdCnt = 0;
    while (1) {
        if(phcmd->id ==UNUSE) {
            break;
        }
		phcmd++;
        hcnt++;
		gu32_MdsHcmdCnt++;
    }
	
    plcmd = &gat_MdsLowCmd[0];
    lcnt = 0;
	gu32_MdsLcmdCnt = 0;
    while (1) {
        if(plcmd->id ==UNUSE) {
            break;
        }
		plcmd++;
        lcnt++;
		gu32_MdsLcmdCnt++;
    }
	
    precord = &gat_ModelinkRecord[0];
    pflg = &gt_ModeLinkFlag;
    INIT_LIST_HEAD(&pflg->head);
    pflg->pcur = MYINIT(0);
    pflg->fsm = FSM_NON_INIT;
    pflg->cnt = 0;
    pflg->MainSend = 0;

    pflg->pSdBuf = &ma2u8_SendBuf[0][0];
    pflg->sendLen = 0;
    pflg->pRcBuf = (unsigned char *)0;
    pflg->rcvLen = 0;
    pflg->RetryTick = 1;
    pflg->RunNxtList = 0;

    pflg->pause = 0;
    pflg->slaveCmd = 0;

    phcmd = &gat_MdsHighCmd[0];
    plcmd = &gat_MdsLowCmd[0];
    if((hcnt==0) &&(lcnt==0)) {
        pflg->fsm = FSM_EMPTY;
        return 0;
    }
    else if(hcnt ==lcnt) {
        j = 0;
        for(i=0; i<hcnt; i++) {
            if(j >=MAX_MODELINK_RECORD) {
                goto CLC_ERR;
            }
            precord[j].pvoid = phcmd;
            list_add_tail(&precord[j].list, &pflg->head);
            phcmd++;
            j++;

            if(j >=MAX_MODELINK_RECORD) {
                goto CLC_ERR;
            }
            precord[j].pvoid = plcmd;
            list_add_tail(&precord[j].list, &pflg->head);
            plcmd++;
            j++;
        }
    }
    else if(hcnt >lcnt) {
        j =0;
        for(i=0; i<hcnt; i++) {
            if(j >=MAX_MODELINK_RECORD) {
                goto CLC_ERR;
            }
            precord[j].pvoid = phcmd;
            list_add_tail(&precord[j].list, &pflg->head);
            phcmd++;
            j++;
            
            if(lcnt >0) {
                if(j >=MAX_MODELINK_RECORD) {
                    goto CLC_ERR;
                }
                precord[j].pvoid = plcmd;
                list_add_tail(&precord[j].list, &pflg->head);
                plcmd++;
                j++;
                lcnt--;
            }
        }
    }
    else {
        j = 0;
        k = hcnt;
        for(i=0; i<lcnt; i++) {
            if(hcnt !=0) {
                if(j >=MAX_MODELINK_RECORD) {
                    goto CLC_ERR;
                }
                precord[j].pvoid = phcmd;
                list_add_tail(&precord[j].list, &pflg->head);
                phcmd++;
                j++;
                k--;
                if(k ==0) {
                    k = hcnt;
                    phcmd = &gat_MdsHighCmd[0];
                }
            }

            if(j >=MAX_MODELINK_RECORD) {
                goto CLC_ERR;
            }
            precord[j].pvoid = plcmd;
            list_add_tail(&precord[j].list, &pflg->head);
            plcmd++;
            j++;
        }
    }

    pflg->fsm = FSM_COMPILE_OK;
    pflg->cnt = j;
	_yPrintf("WrMutiBit !!!!: gu32_MdsHcmdCnt=%d, gu32_MdsLcmdCnt=%d, pflg->cnt=%d", gu32_MdsHcmdCnt, gu32_MdsLcmdCnt, pflg->cnt);
    return 0;
    
    CLC_ERR:
    pflg->fsm = FSM_COMPILE_OVER;
    pflg->cnt = MAX_MODELINK_RECORD;
	_yPrintf("WrMutiBit !!!!: gu32_MdsHcmdCnt=%d, gu32_MdsLcmdCnt=%d, pflg->cnt=%d", gu32_MdsHcmdCnt, gu32_MdsLcmdCnt, pflg->cnt);
    return 1;
}

unsigned long _yPackedBzMdsDta(struct tag_MdsElemMap *pmap, struct tag_MdsModlinkCmd *pcmd)
{
    struct tag_ModlinkFlag *pflg;
    unsigned char *pu8Tmp;
	unsigned char *pu8TmpChg;
    unsigned short *pu16Tmp;
	unsigned short *pu16TmpChg;
    unsigned long *pu32Tmp;
    unsigned long i,j,k,m,n;
	unsigned short mstAdr;
    unsigned char tmpu8;

    pflg = &gt_ModeLinkFlag;
    pflg->sendLen = 0;
    pflg->pSdBuf[0] = pcmd->id;
    pflg->pSdBuf[1] = pcmd->cmd;
	mstAdr = pmap->nStAdr +pcmd->opAdr -pmap->stElem;
    pflg->pSdBuf[2] = mstAdr >>8;
    pflg->pSdBuf[3] = mstAdr &0xff;
    switch(pcmd->cmd) {
    case RdMutiBit:     // 读多个线圈        
    case RdMutiIn:      // 读取多个输入        
    case RdMutiReg:     // 读多个寄存器
        pflg->pSdBuf[4] = pcmd->opCnt >>8;
        pflg->pSdBuf[5] = pcmd->opCnt &0xff;
        pflg->sendLen =_yMdsAddVerify(pflg->pSdBuf, 6);
        break;
        
    case WrSimpBit:     // 写单个线圈
    	if(_yPointEq(pmap->pElemAdr, pmap->pWtElmAdr)) {
			return 2;
		}    
    	if(pmap->pu8Chg[pcmd->opAdr]) {							// 数据有改变
    		pmap->pu8Chg[pcmd->opAdr] = 0;
        	pu8Tmp = (unsigned char *)(pmap->pWtElmAdr);
	        if(pu8Tmp[pcmd->opAdr]) {
	            pflg->pSdBuf[4] = 0xff;
	            pflg->pSdBuf[5] = 0x00;
	        }
	        else {
	            pflg->pSdBuf[4] = 0x00;
	            pflg->pSdBuf[5] = 0x00;
	        }
	        pflg->sendLen =_yMdsAddVerify(pflg->pSdBuf, 6);			
		}
		else {													// 数据没有改变
			return 3;
		}

        break;
        
    case WrSimpReg:     // 写单个寄存器
    	if(_yPointEq(pmap->pElemAdr, pmap->pWtElmAdr)) {
			return 2;
		}
		if(pmap->pu8Chg[pcmd->opAdr]) {							// 数据有改变		
			pmap->pu8Chg[pcmd->opAdr] = 0;
			pu16Tmp = (unsigned short *)(pmap->pWtElmAdr);
			pflg->pSdBuf[4] = pu16Tmp[pcmd->opAdr] >>8;
			pflg->pSdBuf[5] = pu16Tmp[pcmd->opAdr] &0xff;
			pflg->sendLen =_yMdsAddVerify(pflg->pSdBuf, 6);		
		}
		else {
			return 3;
		}
        break;
        
    case WrMutiBit:     // 写多个线圈
        if(pcmd->opCnt >1900) {
            return 1;
        }
		if(_yPointEq(pmap->pElemAdr, pmap->pWtElmAdr)) {
			return 2;
		}
        pflg->pSdBuf[4] = pcmd->opCnt >>8;
        pflg->pSdBuf[5] = pcmd->opCnt &0xff;
        pflg->pSdBuf[6] = pcmd->opCnt >>3;
        if(pcmd->opCnt &0x07) {
            pflg->pSdBuf[6] += 1;
        }
        pu8Tmp = (unsigned char *)(pmap->pElemAdr);
		pu8TmpChg = (unsigned char *)(pmap->pWtElmAdr);
        tmpu8 = 0;
        j = 0;
        k = 0;
		m = pcmd->opAdr;
		n = 0;
        for(i=0; i<pcmd->opCnt; i++) {
			if(pmap->pu8Chg[m]) {
				pmap->pu8Chg[m] = 0;
				n = 1;
				tmpu8 += (pu8TmpChg[m]<<j);
			}
			else {
				tmpu8 += (pu8Tmp[m]<<j);
			}
            j++;
			m++;
            if(j >=8) {
                j = 0;
                pflg->pSdBuf[7+k] = tmpu8;
                tmpu8 = 0;
                k++;
            }
        }
		if(n >0) {													// 有数据改变
	        if(pcmd->opCnt &0x07) {
	            pflg->pSdBuf[7+k] = tmpu8;
	            k++;
	        }
	        pflg->sendLen =_yMdsAddVerify(pflg->pSdBuf, 7+k);		
		}
		else {
			return 3;
		}
        break;
        
    case WrMutiReg:     // 写多个寄存器
        if(pcmd->opCnt >120) {
            return 1;
        }
		if(_yPointEq(pmap->pElemAdr, pmap->pWtElmAdr)) {
			return 2;
		}
		if(pcmd->pname[1]!='\0') {
			_yPrintf("WrSimpBit WantSend %c%c%d Num=%d ok!\n", pcmd->pname[0], pcmd->pname[1], pcmd->opAdr, pcmd->opCnt);
		}
		else {
			_yPrintf("WrSimpBit WantSend %c%d Num=%d ok!\n", pcmd->pname[0], pcmd->opAdr, pcmd->opCnt);
		}		
        pu16Tmp = (unsigned short *)(pmap->pElemAdr);
		pu16TmpChg = (unsigned short *)(pmap->pWtElmAdr);
		m = pcmd->opAdr;
		n = 0;
        pflg->pSdBuf[4] = pcmd->opCnt >>8;
        pflg->pSdBuf[5] = pcmd->opCnt &0xff;
        pflg->pSdBuf[6] = pcmd->opCnt <<1;
		k = 0;
        for(i=0; i<pcmd->opCnt; i++) {
			if(pmap->pu8Chg[m]) {
				pmap->pu8Chg[m] = 0;
				n = 1;
				pflg->pSdBuf[7+k] = pu16TmpChg[m] >>8;
				
				k++;
				pflg->pSdBuf[7+k] = pu16TmpChg[m] >>0;
				k++;				
			}
			else {
				pflg->pSdBuf[7+k] = pu16Tmp[m] >>8;
				k++;
				pflg->pSdBuf[7+k] = pu16Tmp[m] >>0;
				k++;
			}
			m++;
        }
		if(n >0) {													// 有数据改变
        	pflg->sendLen =_yMdsAddVerify(pflg->pSdBuf, 7+k);
			if(pcmd->pname[1]!='\0') {
				_yPrintf("WrSimpBit Send %c%c%d Num=%d ok!\n", pcmd->pname[0], pcmd->pname[1], pcmd->opAdr, pcmd->opCnt);
			}
			else {
				_yPrintf("WrSimpBit Send %c%d Num=%d ok!\n", pcmd->pname[0], pcmd->opAdr, pcmd->opCnt);
			}
		}
		else {
			return 3;
		}
        break;
    default:            // 出错
        return 1;
    }
    return 0;
}

unsigned long _yRunModlinkModule(void)
{
    struct tag_UartDcb *pdcb;
    struct tag_ModlinkFlag *pflg;
    static struct tag_MdsModlinkCmd *pcmd;
    static struct tag_ModelinkRecord *precord;
    static struct tag_MdsElemMap *pmap;
	unsigned char *ptu8;
    unsigned long cnt;
    unsigned long i,j,k;
	static unsigned long cyclecnt =0;

    pdcb =&gat_UartDcb[0];
    if((pdcb->flag.isTxing) ||(pdcb->flag.isRxing)) {                           // 主站增在发送,或者正在接收
        return 0;
    }
    
    pflg = &gt_ModeLinkFlag;
    cnt = 0;
    RE_CHECK:
    switch(pflg->fsm) {
    case FSM_NON_INIT:          // 没有初始化
    case FSM_EMPTY:             // 初始化后,编译后位空
        break;
        
    case FSM_COMPILE_OK:        // 编译正确
    case FSM_COMPILE_OVER:
 	  	if(pflg->pause ==0) {   // 没有暂停
            if(cnt >=pflg->cnt) {                                               // 超过限制,退出
                break;
            }
            pflg->pcur = pflg->head.next;
            if(pflg->pcur ==(&pflg->head)) {                                     // 空,退出
                pflg->fsm = FSM_EMPTY;
                goto RE_CHECK;
            }

            list_del_init(pflg->pcur);
            precord = list_entry(pflg->pcur, struct tag_ModelinkRecord, list);
            pcmd = (struct tag_MdsModlinkCmd *)(precord->pvoid);
            if(pcmd->IsStop) {                                                  // 已经停止使用,查找下一条
                cnt++;
                list_add_tail(pflg->pcur, &pflg->head);
                goto RE_CHECK;
            }
			if((pcmd->MstDel) &&(pcmd->cnt==0)) {
                cnt++;
                list_add_tail(pflg->pcur, &pflg->head);
                goto RE_CHECK;				
			}
            list_add_tail(pflg->pcur, &pflg->head);
            if(pcmd->cmd >WrMutiReg)
                pflg->fsm = FSM_SEND_EXT;                                       // 切换状态机
            else
                pflg->fsm = FSM_SEND_BZ;                                        // 切换状态机
            goto RE_CHECK;
        }
        break;
        
    case FSM_SEND_BZ:															// 打包数据,启动发送
    	ptu8 = (unsigned char *)(pcmd->pname);
        pmap = _yMgetMdsElmIfo(pcmd->cmd, ptu8, _yGetStrLen(pcmd->pname), pcmd->opAdr);
        if( !pmap ) {															// 数据包出错
            pflg->fsm = FSM_COMPILE_OK;
            break;
        }
		if( _yPackedBzMdsDta(pmap, pcmd) ){										// 打包数据出错
            pflg->fsm = FSM_COMPILE_OK;
            break;        
        }
		if(pflg->sendLen >0) {
			//LOGE ("Modelink send data %d\n",cyclecnt);
			cyclecnt++;
	        pdcb->pTxBuf = pflg->pSdBuf;
	        pdcb->TxCnt = pflg->sendLen;
	        pdcb->pfSendByte(pdcb);
	        pflg->MainSend = 1;
	        pflg->RetryTick = 1;
	        pflg->fsm = FSM_WAIT_REC;
		}
		else {
			pflg->fsm = FSM_RUN_NXT;
		}

        break;
    case FSM_SEND_EXT:          // 打包数据,启动发送(扩展)
        break;

    case FSM_WAIT_REC:
        if(pflg->RunNxtList) {                                                  // 启动下一条执行
            pflg->RunNxtList = 0;
			pflg->fsm = FSM_DELY_TO_SEND;
			pflg->dlyStTime = _yGetCurMsTime();
            goto RE_CHECK;
        }
        break;
		
	case FSM_DELY_TO_SEND:
		if(_yIs1msTimeout(pflg->dlyStTime, 0)) {
			pflg->fsm = FSM_RUN_NXT;
			goto RE_CHECK;
		}
		break;
		
    case FSM_RUN_NXT:
        if(cnt >=pflg->cnt) {                                               // 超过限制,退出
            break;
        }
        pflg->pcur = pflg->head.next;
        if(pflg->pcur ==(&pflg->head)) {                                     // 空,退出
            pflg->fsm = FSM_EMPTY;
            goto RE_CHECK;
        }

        list_del_init(pflg->pcur);
        precord = list_entry(pflg->pcur, struct tag_ModelinkRecord, list);
        pcmd = (struct tag_MdsModlinkCmd *)(precord->pvoid);
        if(pcmd->IsStop) {                                                  // 已经停止使用,查找下一条
            cnt++;
            list_add_tail(pflg->pcur, &pflg->head);
            goto RE_CHECK;
        }
		if((pcmd->MstDel) &&(pcmd->cnt==0)) {
            cnt++;
            list_add_tail(pflg->pcur, &pflg->head);
            goto RE_CHECK;				
		}		
        list_add_tail(pflg->pcur, &pflg->head);
        if(pcmd->cmd >WrMutiReg)
            pflg->fsm = FSM_SEND_EXT;                                       // 切换状态机
        else
            pflg->fsm = FSM_SEND_BZ;                                        // 切换状态机
        goto RE_CHECK;
        //break;
        
    default:
    	_yInitModlinkVar();
        break;
    }
    return 0;
}




