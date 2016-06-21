//----------------------------------------------------
//Copyright (C), 2016,  Kawakp.
//版权所有 (C), 2016,   Kawakp.
//所属模块:	APP modbus通讯库模块
//作者：yjs
//版本：V1.0.0
//初始版本完成日期：2016-04-20
//文件描述: Modbus主站通讯参数表格定义头文件
//其他说明: 无
//修订历史:
//2. ...
//1. 日期: 2016-04-20
//   作者: yjs
//   新版本号: V1.0.0
//   修改说明: 原始版本 
//------------------------------------------------------
#ifndef _MDS_PARA_CHECK_H_H_H
#define _MDS_PARA_CHECK_H_H_H


#ifdef __cplusplus
extern "C" {
#endif

#define MdsSchEnd       (0)     // 寻址方式,有3类寻址方式,(0: 表格搜索结束)(1: Bit)(2: Word)(3: BitX)
#define MdsSchBit       (1)
#define MdsSchWord      (2)
#define MdsSchBitX      (3)

#define MdsBitY         (0)     // 寻址类型,X,Y,M,SM,S,T,C,D,R,SD
#define MdsBitX         (1)
#define MdsBitM         (2)
#define MdsBitSM        (3)
#define MdsBitS         (4)
#define MdsBitT         (5)
#define MdsBitC         (6)
#define MdsWrdD         (7)
#define MdsWrdSD        (8)
#define MdsWrdZ         (9)
#define MdsWrdT         (10)
#define MdsWrdC         (11)
#define MdsWrdR         (12)

#define MdsSec0         (0)     // 段号,原件一般分段(0: 没有)(1: 第一段)(2: 第二段)(3: 第三段)
#define MdsSec1         (1)
#define MdsSec2         (2)
#define MdsSec3         (3)

#define MdsMode0        (0)     // 原件是否是双字寻址(0: 不是)(1: 是)
#define MdsMode1        (1)

#define MdsRW           (0)     // 可读写
#define MdsROnly        (1)
struct tag_MdsElemMap {
    unsigned char searchAdr;    // 寻址方式,有3类寻址方式,(0: 表格搜索结束)(1: Bit)(2: Word)(3: BitX)
    unsigned char type;         // 寻址类型,X,Y,M,SM,S,T,C,D,R,SD
    unsigned char section;      // 段号,原件一般分段(0: 没有)(1: 第一段)(2: 第二段)(3: 第三段)
    unsigned char mode;         // 原件是否是双字寻址(0: 不是)(1: 是)
    
    unsigned short stElem;      // 元件开始地址
    unsigned short nStAdr;      // Mds通讯开始地址
    unsigned short nEdAdr;      // Mds通讯结束地址
    unsigned short nMaxCnt;     // 本段原件最大个数

    unsigned short nMaxElem;    // 元件类型的最大个数
    unsigned short IsReadOnly;  //

    unsigned char pname[8];       // 名字
    void *pElemAdr;             // 元件开始地址
    void *pWtElmAdr;          	// 元件开始地址
    unsigned char *pu8Chg;		// 改变
};

#define RdMutiBit           (0x01)      // 读多个线圈
#define RdMutiIn            (0x02)      // 读取多个输入
#define RdMutiReg           (0x03)      // 读多个寄存器
#define WrSimpBit           (0x05)      // 写单个线圈
#define WrSimpReg           (0x06)      // 写单个寄存器
#define WrMutiBit           (0x0f)      // 写多个线圈
#define WrMutiReg           (0x10)      // 写多个寄存器
#define NON_USE_CMD         (0xff)
struct tag_MdsCmdTable {
    unsigned char cmd;          // 命令表
    unsigned char searchAdr;    // 寻址方式,有3类寻址方式,(0: 表格搜索结束)(1: Bit)(2: Word)(3: BitX)
    unsigned short maxnum;      // 最大操作个数
};

struct tag_MdsElemMap * _yMgetMdsElmIfo(unsigned char cmd, unsigned char *pbuf, unsigned long buflen,unsigned long num);
struct tag_MdsElemMap * _yGetMdsElmIfo(unsigned long searchAdr, unsigned long mdsAdr);
struct tag_MdsElemMap * _yGetMdsElmIfoExt(unsigned long searchAdr, unsigned long mdsAdr, unsigned long rw);





#ifdef __cplusplus
}
#endif
#endif	// _MDS_PARA_CHECK_H_H_H


