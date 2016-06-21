//----------------------------------------------------
//Copyright (C), 2016,  Kawakp.
//版权所有 (C), 2016,   Kawakp.
//所属模块:	APP modbus通讯库模块
//作者：yjs
//版本：V1.0.0
//初始版本完成日期：2016-04-20
//文件描述: Modbus主站通讯参数表格定义
//其他说明: 无
//修订历史:
//2. ...
//1. 日期: 2016-04-20
//   作者: yjs
//   新版本号: V1.0.0
//   修改说明: 原始版本 
//------------------------------------------------------
#include "stdio.h"
#include "string.h"
#include "RobotVar.h"
#include "MdsParaCheck.h"
#include "mdbus.h"

struct tag_MdsElemMap gat_MdsElmMap[] ={
/*searchAdr    type        section     mode        stElem    nStAdr    nEdAdr    nMaxCnt  nMaxElem IsReadOnly  pname      pElemAdr            pWtElmAdr         pu8Chg  */
{MdsSchBit,    MdsBitY,    MdsSec1,    MdsMode0,   0,        0,        1200,     256,      2048,    0,         "Y",       (void *)gau8_Y,  (void *)gau8Wt_Y,    gau8_ChY  },   // Bit Y
{MdsSchBit,    MdsBitY,    MdsSec2,    MdsMode0,   256,      10000,    12000,    1792,     2048,    0,         "Y",       (void *)gau8_Y,  (void *)gau8Wt_Y,    gau8_ChY  },

{MdsSchBit,    MdsBitX,    MdsSec1,    MdsMode0,   0,        1200,     2000,     256,      2048,    1,         "X",       (void *)gau8_X,  (void *)gau8_X,      NULL },   // Bit X
{MdsSchBit,    MdsBitX,    MdsSec2,    MdsMode0,   256,      12000,    14000,    1792,     2048,    1,         "X",       (void *)gau8_X,  (void *)gau8_X,      NULL },

{MdsSchBit,    MdsBitM,    MdsSec1,    MdsMode0,   0,        2000,     4400,     2048,     16384,   0,         "M",       (void *)gau8_M,  (void *)gau8Wt_M,    gau8_ChM },   // Bit M
{MdsSchBit,    MdsBitM,    MdsSec2,    MdsMode0,   2048,     34000,    54000,    14336,    16384,   0,         "M",       (void *)gau8_M,  (void *)gau8Wt_M,    gau8_ChM },

{MdsSchBit,    MdsBitSM,   MdsSec1,    MdsMode0,   0,        4400,     6000,     256,      4096,    0,         "SM",      (void *)gau8_SM,  (void *)gau8Wt_SM,  gau8_ChSm },  // Bit SM
{MdsSchBit,    MdsBitSM,   MdsSec2,    MdsMode0,   256,      14000,    18000,    3840,     4096,    0,         "SM",      (void *)gau8_SM,  (void *)gau8Wt_SM,  gau8_ChSm },

{MdsSchBit,    MdsBitS,    MdsSec1,    MdsMode0,   0,        6000,     8000,     1024,     8192,    0,         "S",       (void *)gau8_S,  (void *)gau8Wt_S,    gau8_ChS },   // Bit S
{MdsSchBit,    MdsBitS,    MdsSec2,    MdsMode0,   1024,     18000,    26000,    7168,     8192,    0,         "S",       (void *)gau8_S,  (void *)gau8Wt_S,    gau8_ChS },

{MdsSchBit,    MdsBitT,    MdsSec1,    MdsMode0,   0,        8000,     9200,     256,      4096,    0,         "T",       (void *)gau8_T,  (void *)gau8_T,      NULL },   // Bit T
{MdsSchBit,    MdsBitT,    MdsSec2,    MdsMode0,   256,      26000,    30000,    3840,     4096,    0,         "T",       (void *)gau8_T,  (void *)gau8_T,      NULL },

{MdsSchBit,    MdsBitC,    MdsSec1,    MdsMode0,   0,        9200,     10000,    256,      4096,    0,         "C",       (void *)gau8_C,  (void *)gau8_C,      NULL },   // Bit C
{MdsSchBit,    MdsBitC,    MdsSec2,    MdsMode0,   256,      30000,    34000,    3840,     4096,    0,         "C",       (void *)gau8_C,  (void *)gau8_C,      NULL},

{MdsSchWord,   MdsWrdD,    MdsSec1,    MdsMode0,   0,        0,        8000,     8000,     8000,    0,         "D",       (void *)gau16_D,  (void *)gau16Wt_D,  gau16_ChD },  // Word D

{MdsSchWord,   MdsWrdSD,   MdsSec1,    MdsMode0,   0,        8000,     8500,     256,      4096,    0,         "SD",      (void *)gau16_SD, (void *)gau16Wt_SD, gau16_ChSd }, // Word SD
{MdsSchWord,   MdsWrdSD,   MdsSec2,    MdsMode0,   256,      46000,    50000,    3840,     4096,    0,         "SD",      (void *)gau16_SD, (void *)gau16Wt_SD, gau16_ChSd },

{MdsSchWord,   MdsWrdZ,    MdsSec1,    MdsMode0,   0,        8500,     9000,     256,      2048,    0,         "Z",       (void *)gau16_Z,  (void *)gau16Wt_Z,  gau16_ChZ },  // Word Z
{MdsSchWord,   MdsWrdZ,    MdsSec2,    MdsMode0,   256,      10000,    12000,    1792,     2048,    0,         "Z",       (void *)gau16_Z,  (void *)gau16Wt_Z,  gau16_ChZ },

{MdsSchWord,   MdsWrdT,    MdsSec1,    MdsMode0,   0,        9000,     9500,     256,      4096,    0,         "T",      (void *)gau16_TCurValue,  (void *)gau16_TCurValue, NULL },    // Word T
{MdsSchWord,   MdsWrdT,    MdsSec2,    MdsMode0,   256,      50000,    54000,    3840,     4096,    0,         "T",      (void *)gau16_TCurValue,  (void *)gau16_TCurValue, NULL },

{MdsSchWord,   MdsWrdC,    MdsSec1,    MdsMode0,   0,        9500,     9700,     200,      4096,    0,         "C",      (void *)gau32_CCurValue,  (void *)gau32_CCurValue, NULL },    // Word C
{MdsSchWord,   MdsWrdC,    MdsSec2,    MdsMode1,   200,      9700,     9812,     56,       4096,    0,         "C",      (void *)gau32_CCurValue,  (void *)gau32_CCurValue, NULL },
{MdsSchWord,   MdsWrdC,    MdsSec3,    MdsMode1,   256,      54000,    62000,    3840,     4096,    0,         "C",      (void *)gau32_CCurValue,  (void *)gau32_CCurValue, NULL },

{MdsSchWord,   MdsWrdR,    MdsSec1,    MdsMode0,   0,        13000,    46000,    32768,    32768,   0,         "R",      (void *)gau16_R,  (void *)gau16Wt_R,   gau16_ChR },  // Word R

{MdsSchBitX,   MdsBitX,    MdsSec1,    MdsMode0,   0,        0,        2048,     2048,     2048,    0,         "R",      (void *)gau8_X,  (void *)gau8_X, NULL },
{MdsSchEnd,    0,          0,          0,          0,        0,        0,        0,        0,       0,         "END",    (void *)0, (void *)0 }
};

struct tag_MdsCmdTable gat_MdsCmdTable[] = {
/*  cmd              searchAdr         maxnum         */
{RdMutiBit,      MdsSchBit,    2000  },     // 读多个线圈
{RdMutiIn,       MdsSchBitX,   2000  },     // 读取多个输入
{RdMutiReg,      MdsSchWord,   125   },     // 读多个寄存器

{WrSimpBit,      MdsSchBit,    1  },        // 写单个线圈
{WrSimpReg,      MdsSchWord,   1  },        // 写单个寄存器
{WrMutiBit,      MdsSchBit,    1968},       // 写多个线圈
{WrMutiReg,      MdsSchWord,   125 },       // 写多个寄存器

{NON_USE_CMD,    MdsSchEnd,    0  }
};

struct tag_MdsElemMap * _yMgetMdsElmIfo(unsigned char cmd, unsigned char *pbuf, unsigned long buflen,unsigned long num)
{
    struct tag_MdsElemMap *pmap;
    struct tag_MdsCmdTable *pcmd;
    unsigned long searchAdr;

    pmap =(struct tag_MdsElemMap *)0;
    pcmd = &gat_MdsCmdTable[0];
    while(1) {
        if(pcmd->searchAdr ==MdsSchEnd) {
            return pmap;
        }
        if(pcmd->cmd ==cmd) {
            searchAdr = pcmd->searchAdr;
            break;
        }
        pcmd++;
    }
    
    pmap =(struct tag_MdsElemMap *)&gat_MdsElmMap[0];
    while(1) {
        if(pmap->searchAdr ==MdsSchEnd) {
            pmap =(struct tag_MdsElemMap *)0;
            break;
        }
        if(buflen !=_yGetStrLen(pmap->pname)) {
            pmap++;
            continue;
        }
        if(memcmp(pbuf, &pmap->pname[0], buflen) !=0) {
            pmap++;
            continue;
        }
        if((num<pmap->stElem) ||(num>=(pmap->stElem +pmap->nMaxCnt))) {
            pmap++;
            continue;
        }
        break;
    }

    return pmap;
}

struct tag_MdsElemMap * _ySgetMdsElmIfo(unsigned long searchAdr, unsigned long mdsAdr)
{
    struct tag_MdsElemMap *pmap;

    pmap =(struct tag_MdsElemMap *)&gat_MdsElmMap[0];
    while(1) {
        if(pmap->searchAdr ==MdsSchEnd) {
            pmap =(struct tag_MdsElemMap *)0;
            break;
        }
        if(pmap->section ==MdsSec0) {
            pmap++;
            continue;
        }
        if(pmap->searchAdr !=searchAdr) {
            pmap++;
            continue;            
        }
        if((mdsAdr>=pmap->nStAdr) &&(mdsAdr<pmap->nEdAdr))
            break;
        pmap++;
    }

    if(pmap) {
        if((mdsAdr-pmap->nStAdr) >pmap->nMaxCnt) {
            pmap =(struct tag_MdsElemMap *)0;
        }
    }

    return pmap;
}

struct tag_MdsElemMap * _ySgetMdsElmIfoExt(unsigned long searchAdr, unsigned long mdsAdr, unsigned long rw)
{
    struct tag_MdsElemMap *pmap;

    pmap =(struct tag_MdsElemMap *)&gat_MdsElmMap[0];
    while(1) {
        if(pmap->searchAdr ==MdsSchEnd) {
            pmap =(struct tag_MdsElemMap *)0;
            break;
        }
        if(pmap->section ==MdsSec0) {
            pmap++;
            continue;
        }
        if(pmap->searchAdr !=searchAdr) {
            pmap++;
            continue;            
        }
        if(pmap->IsReadOnly ==rw) {
            pmap++;
            continue;            
        }            
        if((mdsAdr>=pmap->nStAdr) &&(mdsAdr<pmap->nEdAdr))
            break;
        pmap++;
    }

    if(pmap) {
        if((mdsAdr-pmap->nStAdr) >pmap->nMaxCnt) {
            pmap =(struct tag_MdsElemMap *)0;
        }
    }

    return pmap;
}


