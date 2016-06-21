//----------------------------------------------------
//Copyright (C), 2016,  Kawakp.
//版权所有 (C), 2016,   Kawakp.
//所属模块:	APP modbus通讯库模块
//作者：yjs
//版本：V1.0.0
//初始版本完成日期：2016-04-20
//文件描述: Modbus主站通讯变量,及其效验函数定义,头文件
//其他说明: 无
//修订历史:
//2. ...
//1. 日期: 2016-04-20
//   作者: yjs
//   新版本号: V1.0.0
//   修改说明: 原始版本 
//------------------------------------------------------

#ifndef _ROBOT_VAR_H_H_H
#define _ROBOT_VAR_H_H_H

#include "RobotVarMarco.h"

#ifdef __cplusplus
extern "C" {
#endif


extern unsigned char gau8_X[X_RANGE];      // X位元件定义
extern unsigned char gau8_T[T_RANGE];      // T位元件定义
extern unsigned char gau8_C[C_RANGE];      // C位元件定义

extern unsigned char gau8_Y[Y_RANGE];      // Y位元件定义
extern unsigned char gau8Wt_Y[Y_RANGE];    // Y位元件定义
extern unsigned char gau8_ChY[Y_RANGE];

extern unsigned char gau8_M[M_RANGE];      // M位元件定义
extern unsigned char gau8Wt_M[M_RANGE];    // M位元件定义
extern unsigned char gau8_ChM[M_RANGE];

extern unsigned char gau8_S[S_RANGE];      // S位元件定义
extern unsigned char gau8Wt_S[S_RANGE];    // S位元件定义
extern unsigned char gau8_ChS[S_RANGE];

extern unsigned char gau8_SM[SM_RANGE];    // SM位元件定义
extern unsigned char gau8Wt_SM[SM_RANGE];  // SM位元件定义
extern unsigned char gau8_ChSm[SM_RANGE];

extern unsigned short gau16_D[D_RANGE];        // D字元件定义
extern unsigned short gau16Wt_D[D_RANGE];      // D字元件定义
extern unsigned char gau16_ChD[D_RANGE];

extern unsigned short gau16_R[R_RANGE];        // R字元件定义
extern unsigned short gau16Wt_R[R_RANGE];      // R字元件定义
extern unsigned char gau16_ChR[R_RANGE];

extern unsigned short gau16_SD[SD_RANGE];      // SD字元件定义
extern unsigned short gau16Wt_SD[SD_RANGE];    // SD字元件定义
extern unsigned char gau16_ChSd[SD_RANGE];

extern unsigned short gau16_Z[Z_RANGE];        // Z字元件定义
extern unsigned short gau16Wt_Z[Z_RANGE];      // Z字元件定义
extern unsigned char gau16_ChZ[Z_RANGE];


extern unsigned short gau16_TCurValue[T_RANGE];// 定时器的当前值
extern unsigned long gau32_CCurValue[C_RANGE]; // 计数器的当前值(分三段)

extern unsigned long gu32_CurMsTime;


void _yInitRobotVar(void);
unsigned short Crc_Check(unsigned char *data, unsigned short length);
unsigned long _yMdsAddVerify(unsigned char *pu8Dta, unsigned long len);
unsigned long _yGetStrLen(unsigned char *pu8);



#ifdef __cplusplus
}
#endif
#endif	// _ROBOT_VAR_H_H_H


