//----------------------------------------------------
//Copyright (C), 2016,  Kawakp.
//版权所有 (C), 2016,   Kawakp.
//所属模块:	APP modbus通讯库模块
//作者：yjs
//版本：V1.0.0
//初始版本完成日期：2016-04-20
//文件描述: Modbus主站通讯头文件
//其他说明: 
//修订历史:
//2. ...
//1. 日期: 2016-04-20
//   作者: yjs
//   新版本号: V1.0.0
//   修改说明: 原始版本 
//------------------------------------------------------
#ifndef _MDS_MODLINK_H_H_H
#define _MDS_MODLINK_H_H_H

#include "LinuxList.h"


#ifdef __cplusplus
extern "C" {
#endif

#define USID        (0x01)
#define UNUSE       (0x00)

#define MYINIT(x)   		((struct list_head *)(0))

#define _yPointEq(x,y)		((unsigned long)(x) ==(unsigned long)(y))
struct tag_MdsModlinkCmd {
    unsigned char id;       // 站号,    (1 ~ 255)
    unsigned char cmd;      // 功能码   (1,  2,  3,  5,  6, 15, 16) 详细含义见"gat_MdsCmdTable"
    unsigned char IsStop;   // 本条通讯命令是否有用
    unsigned char MstDel;   // 执行完成后,是否需要删除(用于新加快速通讯命令)

	unsigned long cnt;		// 指令执行的次数(0不执行)(当MstDel=1时候,每次执行完后会减一)
    unsigned char pname[8]; // 操作元件名字,eg:"M""T""D"
    unsigned short opAdr;   // 读写元件的开始地址
    unsigned short opCnt;   // 读写元件的个数(有范围限制,字:120    位:1900)

    unsigned long save;     // 保留
};

extern unsigned long gu32_MdsHcmdCnt;
extern unsigned long gu32_MdsLcmdCnt;
extern struct tag_MdsModlinkCmd gat_MdsHighCmd[];
extern struct tag_MdsModlinkCmd gat_MdsLowCmd[];

struct tag_ModelinkRecord {
    struct list_head list;  // 编译时候用
    struct tag_MdsModlinkCmd *pvoid;
};
#define MAX_MODELINK_RECORD (300)
extern struct tag_ModelinkRecord gat_ModelinkRecord[MAX_MODELINK_RECORD];


#define FSM_NON_INIT        (0)
#define FSM_EMPTY           (1)
#define FSM_COMPILE_OK      (2)
#define FSM_COMPILE_OVER    (3)
#define FSM_SEND_BZ         (4)
#define FSM_SEND_EXT        (5)
#define FSM_WAIT_REC        (6)
#define FSM_RUN_NXT         (7)
#define FSM_DELY_TO_SEND	(8)

struct tag_ModlinkFlag {
    struct list_head head;      // 链表头
	struct list_head *pcur;     // 当前执行命令
	unsigned long fsm;          // 状态机
	unsigned long dlyStTime;	// 控制发送延迟时间
    
	unsigned short cnt;         // 记录通讯记录数据
	unsigned short MainSend;    // 主站已经发送标志(0:未发送)  (1:已发送)

    unsigned char *pSdBuf;      // 真实发送缓冲区
    unsigned long sendLen;      // 真实要发送数据的个数
    unsigned char *pRcBuf;      // 接收缓冲区(Modbus主指令中赋值)
    unsigned long rcvLen;       // 接收长度
    
    unsigned char RetryTick;    // 重试次数
    unsigned char RunNxtList;   // 执行下一条标志(0:不执行)  (1:启动下一条执行)

    unsigned char pause;        // 暂停,主站收到从站主动发过来的数据(0:不暂停)   (1:暂停)
    unsigned char slaveCmd;     // 从站命令号
};

extern struct tag_ModlinkFlag gt_ModeLinkFlag;

unsigned long _yInitModlinkVar(void);
unsigned long _yRunModlinkModule(void);


#ifdef __cplusplus
}
#endif
#endif	// _MDS_MODLINK_H_H_H


