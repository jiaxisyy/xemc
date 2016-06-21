#ifndef _UART_HW_H_H_H
#define _UART_HW_H_H_H


#ifdef __cplusplus
extern "C" {
#endif

// ����ͨѶ,���Ŀ�����--------------------------------------------------------------------
struct tag_UartFlag
{
    unsigned short isTxing  :1; // ���ڷ��ͱ�־,(0:δʹ��)(0:���ڷ�����)
    unsigned short isRxing  :1; // ���ڽ��ձ�־,(0:δʹ��)(0:���ڽ�����)
    unsigned short UseRx    :1; // ����ʹ�õĻ�����,(0:0�Ż�����)(0:1�Ż�����)
    unsigned short HaveRxMsg:2; // �Ƿ��н���������(0:û��)(0:��)
    unsigned short Rx0Flg   :2; // ���ջ�����0��־,(0:δʹ��)(1:���ڽ���������)(2:���յ���������)(3:�������ڽ��������)
    unsigned short Rx1Flg   :2; // ���ջ�����1��־,(0:δʹ��)(1:���ڽ���������)(2:���յ���������)(3:�������ڽ��������)

    unsigned short enFramTimeout:1;
    unsigned short bsave1       :6; // ����  
};

typedef void (*pFunUartPdcb)(struct tag_UartDcb *pdcb);
struct tag_UartDcb
{
    unsigned long TxTimeout;    // ���ͳ�ʱʱ��
    unsigned long TxStTime;     // ���Ϳ�ʼʱ��
    
    unsigned long RxChgFarmTime;//�����л�һ������ʱ��        
    unsigned long RxStTime;     // ���տ�ʼ��ʱ��

    unsigned char *pTxBuf;      // ��ʵ���ͻ�����
    unsigned long TxCnt;        // ��ʵҪ�������ݵĸ���
    unsigned long Txflg;		// ���ͱ�־
    
    unsigned char *pRxBuf;      // ��ʵ���ջ�����
    unsigned long RxCnt;        // ��ʵ�������ݸ���    
    unsigned char *paRxBuf[2];  // ���ݽ��ջ�����
    unsigned long aRxCnt[2];    // ���ݽ��յ����ݸ���
        
    unsigned long baud;         // ����Э��ʱ������
    unsigned short datalen;     // ���ݿ��,7,8
    unsigned short stoplen;     // ֹͣλ,1,2
    unsigned short evenodd;     // Ч��֤��0,1,2
    struct tag_UartFlag flag;   // ���ڱ�־
    
    pFunUartPdcb pfSendByte;    // �������ͺ���
};

#define MAX_UART_NUM    (1)
#define UART_MAX_BUF    (360) 
extern unsigned char ma2u8_SendBuf[MAX_UART_NUM][UART_MAX_BUF];
extern struct tag_UartDcb gat_UartDcb[MAX_UART_NUM];

unsigned long _yGetCurMsTime(void);
unsigned long _yIs1msTimeout(unsigned long uiOrignal, unsigned long uiTimeout);
void _yInitUartDcb(void);
void _yMdsMasterProtocolRev(void);



#ifdef __cplusplus
}
#endif
#endif	// _UART_HW_H_H_H


