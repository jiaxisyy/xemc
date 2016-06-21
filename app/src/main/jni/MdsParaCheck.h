//----------------------------------------------------
//Copyright (C), 2016,  Kawakp.
//��Ȩ���� (C), 2016,   Kawakp.
//����ģ��:	APP modbusͨѶ��ģ��
//���ߣ�yjs
//�汾��V1.0.0
//��ʼ�汾������ڣ�2016-04-20
//�ļ�����: Modbus��վͨѶ���������ͷ�ļ�
//����˵��: ��
//�޶���ʷ:
//2. ...
//1. ����: 2016-04-20
//   ����: yjs
//   �°汾��: V1.0.0
//   �޸�˵��: ԭʼ�汾 
//------------------------------------------------------
#ifndef _MDS_PARA_CHECK_H_H_H
#define _MDS_PARA_CHECK_H_H_H


#ifdef __cplusplus
extern "C" {
#endif

#define MdsSchEnd       (0)     // Ѱַ��ʽ,��3��Ѱַ��ʽ,(0: �����������)(1: Bit)(2: Word)(3: BitX)
#define MdsSchBit       (1)
#define MdsSchWord      (2)
#define MdsSchBitX      (3)

#define MdsBitY         (0)     // Ѱַ����,X,Y,M,SM,S,T,C,D,R,SD
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

#define MdsSec0         (0)     // �κ�,ԭ��һ��ֶ�(0: û��)(1: ��һ��)(2: �ڶ���)(3: ������)
#define MdsSec1         (1)
#define MdsSec2         (2)
#define MdsSec3         (3)

#define MdsMode0        (0)     // ԭ���Ƿ���˫��Ѱַ(0: ����)(1: ��)
#define MdsMode1        (1)

#define MdsRW           (0)     // �ɶ�д
#define MdsROnly        (1)
struct tag_MdsElemMap {
    unsigned char searchAdr;    // Ѱַ��ʽ,��3��Ѱַ��ʽ,(0: �����������)(1: Bit)(2: Word)(3: BitX)
    unsigned char type;         // Ѱַ����,X,Y,M,SM,S,T,C,D,R,SD
    unsigned char section;      // �κ�,ԭ��һ��ֶ�(0: û��)(1: ��һ��)(2: �ڶ���)(3: ������)
    unsigned char mode;         // ԭ���Ƿ���˫��Ѱַ(0: ����)(1: ��)
    
    unsigned short stElem;      // Ԫ����ʼ��ַ
    unsigned short nStAdr;      // MdsͨѶ��ʼ��ַ
    unsigned short nEdAdr;      // MdsͨѶ������ַ
    unsigned short nMaxCnt;     // ����ԭ��������

    unsigned short nMaxElem;    // Ԫ�����͵�������
    unsigned short IsReadOnly;  //

    unsigned char pname[8];       // ����
    void *pElemAdr;             // Ԫ����ʼ��ַ
    void *pWtElmAdr;          	// Ԫ����ʼ��ַ
    unsigned char *pu8Chg;		// �ı�
};

#define RdMutiBit           (0x01)      // �������Ȧ
#define RdMutiIn            (0x02)      // ��ȡ�������
#define RdMutiReg           (0x03)      // ������Ĵ���
#define WrSimpBit           (0x05)      // д������Ȧ
#define WrSimpReg           (0x06)      // д�����Ĵ���
#define WrMutiBit           (0x0f)      // д�����Ȧ
#define WrMutiReg           (0x10)      // д����Ĵ���
#define NON_USE_CMD         (0xff)
struct tag_MdsCmdTable {
    unsigned char cmd;          // �����
    unsigned char searchAdr;    // Ѱַ��ʽ,��3��Ѱַ��ʽ,(0: �����������)(1: Bit)(2: Word)(3: BitX)
    unsigned short maxnum;      // ����������
};

struct tag_MdsElemMap * _yMgetMdsElmIfo(unsigned char cmd, unsigned char *pbuf, unsigned long buflen,unsigned long num);
struct tag_MdsElemMap * _yGetMdsElmIfo(unsigned long searchAdr, unsigned long mdsAdr);
struct tag_MdsElemMap * _yGetMdsElmIfoExt(unsigned long searchAdr, unsigned long mdsAdr, unsigned long rw);





#ifdef __cplusplus
}
#endif
#endif	// _MDS_PARA_CHECK_H_H_H


