//----------------------------------------------------
//Copyright (C), 2016,  Kawakp.
//��Ȩ���� (C), 2016,   Kawakp.
//����ģ��:	APP modbusͨѶ��ģ��
//���ߣ�yjs
//�汾��V1.0.0
//��ʼ�汾������ڣ�2016-04-20
//�ļ�����: Modbus��վͨѶͷ�ļ�
//����˵��: 
//�޶���ʷ:
//2. ...
//1. ����: 2016-04-20
//   ����: yjs
//   �°汾��: V1.0.0
//   �޸�˵��: ԭʼ�汾 
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
    unsigned char id;       // վ��,    (1 ~ 255)
    unsigned char cmd;      // ������   (1,  2,  3,  5,  6, 15, 16) ��ϸ�����"gat_MdsCmdTable"
    unsigned char IsStop;   // ����ͨѶ�����Ƿ�����
    unsigned char MstDel;   // ִ����ɺ�,�Ƿ���Ҫɾ��(�����¼ӿ���ͨѶ����)

	unsigned long cnt;		// ָ��ִ�еĴ���(0��ִ��)(��MstDel=1ʱ��,ÿ��ִ�������һ)
    unsigned char pname[8]; // ����Ԫ������,eg:"M""T""D"
    unsigned short opAdr;   // ��дԪ���Ŀ�ʼ��ַ
    unsigned short opCnt;   // ��дԪ���ĸ���(�з�Χ����,��:120    λ:1900)

    unsigned long save;     // ����
};

extern unsigned long gu32_MdsHcmdCnt;
extern unsigned long gu32_MdsLcmdCnt;
extern struct tag_MdsModlinkCmd gat_MdsHighCmd[];
extern struct tag_MdsModlinkCmd gat_MdsLowCmd[];

struct tag_ModelinkRecord {
    struct list_head list;  // ����ʱ����
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
    struct list_head head;      // ����ͷ
	struct list_head *pcur;     // ��ǰִ������
	unsigned long fsm;          // ״̬��
	unsigned long dlyStTime;	// ���Ʒ����ӳ�ʱ��
    
	unsigned short cnt;         // ��¼ͨѶ��¼����
	unsigned short MainSend;    // ��վ�Ѿ����ͱ�־(0:δ����)  (1:�ѷ���)

    unsigned char *pSdBuf;      // ��ʵ���ͻ�����
    unsigned long sendLen;      // ��ʵҪ�������ݵĸ���
    unsigned char *pRcBuf;      // ���ջ�����(Modbus��ָ���и�ֵ)
    unsigned long rcvLen;       // ���ճ���
    
    unsigned char RetryTick;    // ���Դ���
    unsigned char RunNxtList;   // ִ����һ����־(0:��ִ��)  (1:������һ��ִ��)

    unsigned char pause;        // ��ͣ,��վ�յ���վ����������������(0:����ͣ)   (1:��ͣ)
    unsigned char slaveCmd;     // ��վ�����
};

extern struct tag_ModlinkFlag gt_ModeLinkFlag;

unsigned long _yInitModlinkVar(void);
unsigned long _yRunModlinkModule(void);


#ifdef __cplusplus
}
#endif
#endif	// _MDS_MODLINK_H_H_H


