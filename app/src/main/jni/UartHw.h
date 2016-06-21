#ifndef _UART_HW_H_H_H
#define _UART_HW_H_H_H


#ifdef __cplusplus
extern "C" {
#endif

// 串口通讯,核心控制字--------------------------------------------------------------------
struct tag_UartFlag
{
    unsigned short isTxing  :1; // 正在发送标志,(0:未使用)(0:正在发送中)
    unsigned short isRxing  :1; // 正在接收标志,(0:未使用)(0:正在接收中)
    unsigned short UseRx    :1; // 正在使用的缓冲区,(0:0号缓冲区)(0:1号缓冲区)
    unsigned short HaveRxMsg:2; // 是否有接收完整包(0:没有)(0:有)
    unsigned short Rx0Flg   :2; // 接收缓冲区0标志,(0:未使用)(1:正在接收数据中)(2:接收到整包数据)(3:数据正在解包处理中)
    unsigned short Rx1Flg   :2; // 接收缓冲区1标志,(0:未使用)(1:正在接收数据中)(2:接收到整包数据)(3:数据正在解包处理中)

    unsigned short enFramTimeout:1;
    unsigned short bsave1       :6; // 保留  
};

typedef void (*pFunUartPdcb)(struct tag_UartDcb *pdcb);
struct tag_UartDcb
{
    unsigned long TxTimeout;    // 发送超时时间
    unsigned long TxStTime;     // 发送开始时间
    
    unsigned long RxChgFarmTime;//接收切换一包数据时间        
    unsigned long RxStTime;     // 接收开始的时间

    unsigned char *pTxBuf;      // 真实发送缓冲区
    unsigned long TxCnt;        // 真实要发送数据的个数
    unsigned long Txflg;		// 发送标志
    
    unsigned char *pRxBuf;      // 真实接收缓冲区
    unsigned long RxCnt;        // 真实接收数据个数    
    unsigned char *paRxBuf[2];  // 备份接收缓冲区
    unsigned long aRxCnt[2];    // 备份接收到数据个数
        
    unsigned long baud;         // 其他协议时候波特率
    unsigned short datalen;     // 数据宽度,7,8
    unsigned short stoplen;     // 停止位,1,2
    unsigned short evenodd;     // 效验证，0,1,2
    struct tag_UartFlag flag;   // 串口标志
    
    pFunUartPdcb pfSendByte;    // 启动发送函数
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


