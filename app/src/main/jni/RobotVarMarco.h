//----------------------------------------------------
//Copyright (C), 2016,  Kawakp.
//版权所有 (C), 2016,   Kawakp.
//所属模块:	APP modbus通讯库模块
//作者：yjs
//版本：V1.0.0
//初始版本完成日期：2016-04-20
//文件描述: 宏定义
//其他说明: 无
//修订历史:
//2. ...
//1. 日期: 2016-04-20
//   作者: yjs
//   新版本号: V1.0.0
//   修改说明: 原始版本 
//------------------------------------------------------
#ifndef _ROBOT_VAR_MARCO_H_H_H
#define _ROBOT_VAR_MARCO_H_H_H


#ifdef __cplusplus
extern "C" {
#endif

#define ENABLE_DEBUG	(0)


// JAVE接口定义------------------------------------------------
#define OP_BIT_X		(0)
#define OP_BIT_Y		(1)
#define OP_BIT_M		(2)
#define OP_BIT_S		(3)
#define OP_BIT_T		(4)
#define OP_BIT_C		(5)
#define OP_BIT_SM		(6)

#define OP_WORD_D		(10)
#define OP_WORD_R		(11)
#define OP_WORD_SD		(12)
#define OP_WORD_Z		(13)
#define OP_WORD_T		(14)

#define OP_DWORD_D		(20)
#define OP_DWORD_R		(21)
#define OP_DWORD_SD		(22)
#define OP_DWORD_Z		(23)
#define OP_DWORD_C		(24)

#define OP_REAL_D		(30)
#define OP_REAL_R		(31)


// 变量范围定义---------------------------------------------
#define X_RANGE         (2 *1024)
#define Y_RANGE         (2 *1024)
#define M_RANGE         (16 *1024)
#define S_RANGE         (8 *1024)
#define T_RANGE         (4 *1024)
#define C_RANGE         (4 *1024)
#define SM_RANGE        (4 *1024)

#define D_RANGE         (8 *1024)
#define R_RANGE         (32 *1024)
#define SD_RANGE        (4 *1024)
#define Z_RANGE         (2 *1024)



#ifdef __cplusplus
}
#endif
#endif	// _ROBOT_VAR_MARCO_H_H_H


