//----------------------------------------------------
//Copyright (C), 2016,  Kawakp.
//��Ȩ���� (C), 2016,   Kawakp.
//����ģ��:	APP modbusͨѶ��ģ��
//���ߣ�yjs
//�汾��V1.0.0
//��ʼ�汾������ڣ�2016-04-20
//�ļ�����: Modbus��վͨѶ����,����Ч�麯������,ͷ�ļ�
//����˵��: ��
//�޶���ʷ:
//2. ...
//1. ����: 2016-04-20
//   ����: yjs
//   �°汾��: V1.0.0
//   �޸�˵��: ԭʼ�汾 
//------------------------------------------------------

#ifndef _ROBOT_VAR_H_H_H
#define _ROBOT_VAR_H_H_H

#include "RobotVarMarco.h"

#ifdef __cplusplus
extern "C" {
#endif


extern unsigned char gau8_X[X_RANGE];      // XλԪ������
extern unsigned char gau8_T[T_RANGE];      // TλԪ������
extern unsigned char gau8_C[C_RANGE];      // CλԪ������

extern unsigned char gau8_Y[Y_RANGE];      // YλԪ������
extern unsigned char gau8Wt_Y[Y_RANGE];    // YλԪ������
extern unsigned char gau8_ChY[Y_RANGE];

extern unsigned char gau8_M[M_RANGE];      // MλԪ������
extern unsigned char gau8Wt_M[M_RANGE];    // MλԪ������
extern unsigned char gau8_ChM[M_RANGE];

extern unsigned char gau8_S[S_RANGE];      // SλԪ������
extern unsigned char gau8Wt_S[S_RANGE];    // SλԪ������
extern unsigned char gau8_ChS[S_RANGE];

extern unsigned char gau8_SM[SM_RANGE];    // SMλԪ������
extern unsigned char gau8Wt_SM[SM_RANGE];  // SMλԪ������
extern unsigned char gau8_ChSm[SM_RANGE];

extern unsigned short gau16_D[D_RANGE];        // D��Ԫ������
extern unsigned short gau16Wt_D[D_RANGE];      // D��Ԫ������
extern unsigned char gau16_ChD[D_RANGE];

extern unsigned short gau16_R[R_RANGE];        // R��Ԫ������
extern unsigned short gau16Wt_R[R_RANGE];      // R��Ԫ������
extern unsigned char gau16_ChR[R_RANGE];

extern unsigned short gau16_SD[SD_RANGE];      // SD��Ԫ������
extern unsigned short gau16Wt_SD[SD_RANGE];    // SD��Ԫ������
extern unsigned char gau16_ChSd[SD_RANGE];

extern unsigned short gau16_Z[Z_RANGE];        // Z��Ԫ������
extern unsigned short gau16Wt_Z[Z_RANGE];      // Z��Ԫ������
extern unsigned char gau16_ChZ[Z_RANGE];


extern unsigned short gau16_TCurValue[T_RANGE];// ��ʱ���ĵ�ǰֵ
extern unsigned long gau32_CCurValue[C_RANGE]; // �������ĵ�ǰֵ(������)

extern unsigned long gu32_CurMsTime;


void _yInitRobotVar(void);
unsigned short Crc_Check(unsigned char *data, unsigned short length);
unsigned long _yMdsAddVerify(unsigned char *pu8Dta, unsigned long len);
unsigned long _yGetStrLen(unsigned char *pu8);



#ifdef __cplusplus
}
#endif
#endif	// _ROBOT_VAR_H_H_H


