#include "mdbus.h"
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <errno.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <termios.h>
#include <stdlib.h>
#include  <pthread.h>
#include "LinuxList.h"
#include "MdsModlink.h"
#include "MdsParaCheck.h"
#include "RobotVar.h"
#include "RobotVarMarco.h"
#include "uartHw.h"


#if	(ENABLE_DEBUG)
#define _yPrintf		LOGE
#else
#define _yPrintf(...)
#endif


int set_opt(int fd,int nSpeed, int nBits, char nEvent, int nStop,int timeout);

CMdBus::CMdBus()
{
	this->port_fd = -1;
}

CMdBus::~CMdBus(){
	if(this->port_fd >= 0)
		close(this->port_fd);
}

int CMdBus::init_port()
{
	this->port_fd = open(DEV_PATH, O_RDWR|O_NOCTTY|O_NDELAY);
	//this->port_fd = open(DEV_PATH, O_RDWR|O_NOCTTY);
	if(port_fd < 0){
		LOGE("open %s fail %d\n",DEV_PATH,port_fd);
		return -1;
	}
	
	//if(fcntl(this->port_fd, F_SETFL, 0)<0) //block
	if(fcntl(this->port_fd, F_SETFL, O_NDELAY) < 0) //noblock
	{
		LOGE("fcntl failed!\n");
		return -2;
	}

	if(isatty(this->port_fd)==0)
	{
		LOGE("standard input is not a terminal device\n");
		return -3;
	}
	
	//1.0 seconds timeout
	if(set_opt(this->port_fd, 115200, 8, 'N', 2, 0) < 0){
		LOGE("standard input is not a terminal device\n");
		return -4;
	}
	
	//init data 
	_yInitRobotVar();
	_yInitModlinkVar();
	_yInitUartDcb();
	return 0;
}

int CMdBus::mdbus_read_bit(int type, unsigned char *buf, unsigned int stadr, unsigned int len) {
	unsigned int i,j;
	
	switch(type) {
	case OP_BIT_X:
		if((stadr>=X_RANGE) ||((stadr+len)>X_RANGE)) {
			return 1;
		}
		j = 0;
		for(i=stadr; i<(stadr+len); i++) {
			buf[j] = gau8_X[i];
			j++;
		}		
		break;
		
	case OP_BIT_Y:
		if((stadr>=Y_RANGE) ||((stadr+len)>Y_RANGE)) {
			return 1;
		}
		j = 0;
		for(i=stadr; i<(stadr+len); i++) {
			buf[j] = gau8_Y[i];
			j++;
		}		
		break;

		break;
		
	case OP_BIT_M:
		if((stadr>=M_RANGE) ||((stadr+len)>M_RANGE)) {
			return 1;
		}
		j = 0;
		for(i=stadr; i<(stadr+len); i++) {
			buf[j] = gau8_M[i];
			j++;
		}		
		break;

	case OP_BIT_S:
		if((stadr>=S_RANGE) ||((stadr+len)>S_RANGE)) {
			return 1;
		}
		j = 0;
		for(i=stadr; i<(stadr+len); i++) {
			buf[j] = gau8_S[i];
			j++;
		}		
		break;

	case OP_BIT_T:
		if((stadr>=T_RANGE) ||((stadr+len)>T_RANGE)) {
			return 1;
		}
		j = 0;
		for(i=stadr; i<(stadr+len); i++) {
			buf[j] = gau8_T[i];
			j++;
		}		
		break;

	case OP_BIT_C:
		if((stadr>=C_RANGE) ||((stadr+len)>C_RANGE)) {
			return 1;
		}
		j = 0;
		for(i=stadr; i<(stadr+len); i++) {
			buf[j] = gau8_C[i];
			j++;
		}		
		break;

	case OP_BIT_SM:
		if((stadr>=SM_RANGE) ||((stadr+len)>SM_RANGE)) {
			return 1;
		}
		j = 0;
		for(i=stadr; i<(stadr+len); i++) {
			buf[j] = gau8_SM[i];
			j++;
		}		
		break;

	default:
		return -1;
	}

	return 0;	
}

int CMdBus::mdbus_write_bit(int type, unsigned char *buf, unsigned int stadr, unsigned int len) {
	unsigned long i,j;
	unsigned long setStAdr,setEdAdr,wtStAdr,wtEdAdr;
	struct tag_MdsModlinkCmd *phcmd;
	struct tag_MdsModlinkCmd *plcmd;

	if(len ==0)
		return 0;
	phcmd = &gat_MdsHighCmd[0];
	plcmd = &gat_MdsLowCmd[0];
	wtStAdr = stadr;
	wtEdAdr = stadr +len;
	//LOGE("WrMutiBit @@@@: gu32_MdsHcmdCnt=%d, gu32_MdsLcmdCnt=%d", gu32_MdsHcmdCnt, gu32_MdsLcmdCnt);
	switch(type) {		
	case OP_BIT_Y:
		if((stadr>=Y_RANGE) ||((stadr+len)>Y_RANGE)) {
			return 1;
		}
		j = 0;
		for(i=stadr; i<(stadr+len); i++) {
			gau8Wt_Y[i] = buf[j];
			gau8_ChY[i] = 1;
			j++;
		}
		for(i=0; i<gu32_MdsHcmdCnt; i++) {
			if(phcmd[i].MstDel ==0)
				continue;
			if((phcmd[i].pname[0]!='Y') ||(_yGetStrLen(phcmd[i].pname)!=1))
				continue;
			if((phcmd[i].cmd!=WrMutiBit) &&(phcmd[i].cmd!=WrSimpBit))
				continue;
			setStAdr = phcmd[i].opAdr;
			setEdAdr = setStAdr +phcmd[i].opCnt;
			if( (wtStAdr==setStAdr)
				||((wtStAdr>setStAdr) &&(wtStAdr<setEdAdr) )
				||((wtEdAdr>setStAdr) &&(wtEdAdr>=setEdAdr)) ) {
				phcmd[i].cnt++;
			}

		}
		for(i=0; i<gu32_MdsLcmdCnt; i++) {
			if(plcmd[i].MstDel ==0)
				continue;
			if((plcmd[i].pname[0]!='Y') ||(_yGetStrLen(plcmd[i].pname)!=1))
				continue;
			if((plcmd[i].cmd!=WrMutiBit) &&(plcmd[i].cmd!=WrSimpBit))
				continue;
			setStAdr = plcmd[i].opAdr;
			setEdAdr = setStAdr +plcmd[i].opCnt;
			if( (wtStAdr==setStAdr)
				||((wtStAdr>setStAdr) &&(wtStAdr<setEdAdr) )
				||((wtEdAdr>setStAdr) &&(wtEdAdr>=setEdAdr)) ) {
				plcmd[i].cnt++;
			}
		}
		break;
		
	case OP_BIT_M:
		if((stadr>=M_RANGE) ||((stadr+len)>M_RANGE)) {
			return 1;
		}
		j = 0;
		for(i=stadr; i<(stadr+len); i++) {
			gau8Wt_M[i] = buf[j];
			gau8_ChM[i] = 1;
			j++;
		}
		for(i=0; i<gu32_MdsHcmdCnt; i++) {
			if(phcmd[i].MstDel ==0)
				continue;
			if((phcmd[i].pname[0]!='M') ||(_yGetStrLen(phcmd[i].pname)!=1))
				continue;
			if((phcmd[i].cmd!=WrMutiBit) &&(phcmd[i].cmd!=WrSimpBit))
				continue;
			setStAdr = phcmd[i].opAdr;
			setEdAdr = setStAdr +phcmd[i].opCnt;
			//LOGE("WrMutiBit ####: setStAdr=%d, setEdAdr=%d, wtStAdr=%d, wtEdAdr=%d", setStAdr, setEdAdr, wtStAdr, wtEdAdr);
			if( (wtStAdr==setStAdr)
				||((wtStAdr>setStAdr) &&(wtStAdr<setEdAdr) )
				||((wtEdAdr>setStAdr) &&(wtEdAdr>=setEdAdr)) ) {
				phcmd[i].cnt++;
				//LOGE("WrMutiBit H: setStAdr=%d, setEdAdr=%d, wtStAdr=%d, wtEdAdr=%d", setStAdr, setEdAdr, wtStAdr, wtEdAdr);
			}
		}
		for(i=0; i<gu32_MdsLcmdCnt; i++) {
			if(plcmd[i].MstDel ==0)
				continue;
			if((plcmd[i].pname[0]!='M') ||(_yGetStrLen(plcmd[i].pname)!=1))
				continue;
			if((plcmd[i].cmd!=WrMutiBit) &&(plcmd[i].cmd!=WrSimpBit))
				continue;
			setStAdr = plcmd[i].opAdr;
			setEdAdr = setStAdr +plcmd[i].opCnt;
			//LOGE("WrMutiBit $$$$: setStAdr=%d, setEdAdr=%d, wtStAdr=%d, wtEdAdr=%d", setStAdr, setEdAdr, wtStAdr, wtEdAdr);
			if( (wtStAdr==setStAdr)
				||((wtStAdr>setStAdr) &&(wtStAdr<setEdAdr) )
				||((wtEdAdr>setStAdr) &&(wtEdAdr>=setEdAdr)) ) {
				plcmd[i].cnt++;
				//LOGE("WrMutiBit L: setStAdr=%d, setEdAdr=%d, wtStAdr=%d, wtEdAdr=%d", setStAdr, setEdAdr, wtStAdr, wtEdAdr);
			}
		}
		break;

	case OP_BIT_S:
		if((stadr>=S_RANGE) ||((stadr+len)>S_RANGE)) {
			return 1;
		}
		j = 0;
		for(i=stadr; i<(stadr+len); i++) {
			gau8Wt_S[i] = buf[j];
			gau8_ChS[i] = 1;
			j++;
		}
		for(i=0; i<gu32_MdsHcmdCnt; i++) {
			if(phcmd[i].MstDel ==0)
				continue;
			if((phcmd[i].pname[0]!='S') ||(_yGetStrLen(phcmd[i].pname)!=1))
				continue;
			if((phcmd[i].cmd!=WrMutiBit) &&(phcmd[i].cmd!=WrSimpBit))
				continue;
			setStAdr = phcmd[i].opAdr;
			setEdAdr = setStAdr +phcmd[i].opCnt;
			if( (wtStAdr==setStAdr)
				||((wtStAdr>setStAdr) &&(wtStAdr<setEdAdr) )
				||((wtEdAdr>setStAdr) &&(wtEdAdr>=setEdAdr)) ) {
				phcmd[i].cnt++;
			}
		}
		for(i=0; i<gu32_MdsLcmdCnt; i++) {
			if(plcmd[i].MstDel ==0)
				continue;
			if((plcmd[i].pname[0]!='S') ||(_yGetStrLen(plcmd[i].pname)!=1))
				continue;
			if((plcmd[i].cmd!=WrMutiBit) &&(plcmd[i].cmd!=WrSimpBit))
				continue;
			setStAdr = plcmd[i].opAdr;
			setEdAdr = setStAdr +plcmd[i].opCnt;
			if( (wtStAdr==setStAdr)
				||((wtStAdr>setStAdr) &&(wtStAdr<setEdAdr) )
				||((wtEdAdr>setStAdr) &&(wtEdAdr>=setEdAdr)) ) {
				plcmd[i].cnt++;
			}
		}
		break;

	case OP_BIT_SM:
		if((stadr>=SM_RANGE) ||((stadr+len)>SM_RANGE)) {
			return 1;
		}
		j = 0;
		for(i=stadr; i<(stadr+len); i++) {
			gau8Wt_SM[i] = buf[j];
			gau8_ChSm[i] = 1;
			j++;
		}
		for(i=0; i<gu32_MdsHcmdCnt; i++) {
			if(phcmd[i].MstDel ==0)
				continue;
			if((phcmd[i].pname[0]!='S') ||(phcmd[i].pname[1]!='M'))
				continue;
			if((plcmd[i].cmd!=WrMutiBit) &&(plcmd[i].cmd!=WrSimpBit))
				continue;
			setStAdr = phcmd[i].opAdr;
			setEdAdr = setStAdr +phcmd[i].opCnt;
			if( (wtStAdr==setStAdr)
				||((wtStAdr>setStAdr) &&(wtStAdr<setEdAdr) )
				||((wtEdAdr>setStAdr) &&(wtEdAdr>=setEdAdr)) ) {
				phcmd[i].cnt++;
			}
		}
		for(i=0; i<gu32_MdsLcmdCnt; i++) {
			if(plcmd[i].MstDel ==0)
				continue;
			if((phcmd[i].pname[0]!='S') ||(phcmd[i].pname[1]!='M'))
				continue;
			if((plcmd[i].cmd!=WrMutiBit) &&(plcmd[i].cmd!=WrSimpBit))
				continue;
			setStAdr = plcmd[i].opAdr;
			setEdAdr = setStAdr +plcmd[i].opCnt;
			if( (wtStAdr==setStAdr)
				||((wtStAdr>setStAdr) &&(wtStAdr<setEdAdr) )
				||((wtEdAdr>setStAdr) &&(wtEdAdr>=setEdAdr)) ) {
				plcmd[i].cnt++;
			}
		}		
		break;

	default:
		return -1;
	}

	return 0;
}

int CMdBus::mdbus_read_word(int type, unsigned short *buf, unsigned int stadr, unsigned int len) {
	unsigned long i,j;
	
	switch(type) {
	case OP_WORD_D:
		if((stadr>=D_RANGE) ||((stadr+len)>D_RANGE)) {
			return 1;
		}
		j = 0;
		for(i=stadr; i<(stadr+len); i++) {
			buf[j] = gau16_D[i];
			j++;
		}
		break;
		
	case OP_WORD_R:
		if((stadr>=R_RANGE) ||((stadr+len)>R_RANGE)) {
			return 1;
		}
		j = 0;
		for(i=stadr; i<(stadr+len); i++) {
			buf[j] = gau16_R[i];
			j++;
		}
		break;
		
	case OP_WORD_SD:
		if((stadr>=SD_RANGE) ||((stadr+len)>SD_RANGE)) {
			return 1;
		}
		j = 0;
		for(i=stadr; i<(stadr+len); i++) {
			buf[j] = gau16_SD[i];
			j++;
		}
		break;

	case OP_WORD_Z:
		if((stadr>=Z_RANGE) ||((stadr+len)>Z_RANGE)) {
			return 1;
		}
		j = 0;
		for(i=stadr; i<(stadr+len); i++) {
			buf[j] = gau16_Z[i];
			j++;
		}
		break;

	case OP_WORD_T:
		if((stadr>=T_RANGE) ||((stadr+len)>T_RANGE)) {
			return 1;
		}
		j = 0;
		for(i=stadr; i<(stadr+len); i++) {
			buf[j] = gau16_TCurValue[i];
			j++;
		}
		break;
		
	default:
		return -1;		
	}

	return 0;
}

int CMdBus::mdbus_write_word(int type, unsigned short *buf, unsigned int stadr, unsigned int len) {
	unsigned long i,j;
	unsigned long setStAdr,setEdAdr,wtStAdr,wtEdAdr;
	struct tag_MdsModlinkCmd *phcmd;
	struct tag_MdsModlinkCmd *plcmd;

	if(len ==0)
		return 0;
	phcmd = &gat_MdsHighCmd[0];
	plcmd = &gat_MdsLowCmd[0];
	wtStAdr = stadr;
	wtEdAdr = stadr +len;
	switch(type) {
	case OP_WORD_D:
		if((stadr>=D_RANGE) ||((stadr+len)>D_RANGE)) {
			return 1;
		}
		j = 0;
		for(i=stadr; i<(stadr+len); i++) {
			gau16_D[i] = buf[j];
			gau16Wt_D[i] = buf[j];
			gau16_ChD[i] = 1;
			_yPrintf("WrMutiReg gau16Wt_D[%d] = %d \n", i, gau16Wt_D[i]);
			_yPrintf("WrMutiReg gau16_ChD[%d] = %d \n", i, gau16_ChD[i]);
			j++;
		}
		for(i=0; i<gu32_MdsHcmdCnt; i++) {
			if(phcmd[i].MstDel ==0)
				continue;
			if((phcmd[i].pname[0]!='D') ||(_yGetStrLen(phcmd[i].pname)!=1))
				continue;
			if((phcmd[i].cmd!=WrMutiReg) &&(phcmd[i].cmd!=WrSimpReg))
				continue;
			setStAdr = phcmd[i].opAdr;
			setEdAdr = phcmd[i].opAdr +phcmd[i].opCnt;
			//_yPrintf("WrMutiReg High WtSt=%d WtEd=%d CurSt=%d, CurEd=%d \n", wtStAdr, wtEdAdr, setStAdr, setEdAdr);
			if( (wtStAdr==setStAdr)
				||((wtStAdr>setStAdr) &&(wtStAdr<setEdAdr) )
				||((wtEdAdr>setStAdr) &&(wtEdAdr>=setEdAdr)) ) {
				_yPrintf("WrMutiReg High## WtSt=%d WtEd=%d CurSt=%d, CurEd=%d \n", wtStAdr, wtEdAdr, setStAdr, setEdAdr);
				phcmd[i].cnt++;
			}
		}
		for(i=0; i<gu32_MdsLcmdCnt; i++) {
			if(plcmd[i].MstDel ==0)
				continue;
			if((plcmd[i].pname[0]!='D') ||(_yGetStrLen(plcmd[i].pname)!=1))
				continue;
			if((plcmd[i].cmd!=WrMutiReg) &&(plcmd[i].cmd!=WrSimpReg))
				continue;
			setStAdr = plcmd[i].opAdr;
			setEdAdr = plcmd[i].opAdr +plcmd[i].opCnt;
			//_yPrintf("WrMutiReg Low WtSt=%d WtEd=%d CurSt=%d, CurEd=%d \n", wtStAdr, wtEdAdr, setStAdr, setEdAdr);
			if( (wtStAdr==setStAdr)
				||((wtStAdr>setStAdr) &&(wtStAdr<setEdAdr) )
				||((wtEdAdr>setStAdr) &&(wtEdAdr>=setEdAdr)) ) {
				_yPrintf("WrMutiReg Low## WtSt=%d WtEd=%d CurSt=%d, CurEd=%d \n", wtStAdr, wtEdAdr, setStAdr, setEdAdr);
				plcmd[i].cnt++;
			}
		}
		break;
		
	case OP_WORD_R:
		if((stadr>=R_RANGE) ||((stadr+len)>R_RANGE)) {
			return 1;
		}
		j = 0;
		for(i=stadr; i<(stadr+len); i++) {
			gau16_R[i] = buf[j];
			gau16Wt_R[i] = buf[j];
			gau16_ChR[i] = 1;
			j++;
		}
		for(i=0; i<gu32_MdsHcmdCnt; i++) {
			if(phcmd[i].MstDel ==0)
				continue;
			if((phcmd[i].pname[0]!='R') ||(_yGetStrLen(phcmd[i].pname)!=1))
				continue;
			if((phcmd[i].cmd!=WrMutiReg) &&(phcmd[i].cmd!=WrSimpReg))
				continue;
			setStAdr = phcmd[i].opAdr;
			setEdAdr = phcmd[i].opAdr +phcmd[i].opCnt;
			if( (wtStAdr==setStAdr)
				||((wtStAdr>setStAdr) &&(wtStAdr<setEdAdr) )
				||((wtEdAdr>setStAdr) &&(wtEdAdr>=setEdAdr)) ) {
				phcmd[i].cnt++;
			}
		}
		for(i=0; i<gu32_MdsLcmdCnt; i++) {
			if(plcmd[i].MstDel ==0)
				continue;
			if((plcmd[i].pname[0]!='R') ||(_yGetStrLen(plcmd[i].pname)!=1))
				continue;
			if((plcmd[i].cmd!=WrMutiReg) &&(plcmd[i].cmd!=WrSimpReg))
				continue;
			setStAdr = plcmd[i].opAdr;
			setEdAdr = plcmd[i].opAdr +plcmd[i].opCnt;
			if( (wtStAdr==setStAdr)
				||((wtStAdr>setStAdr) &&(wtStAdr<setEdAdr) )
				||((wtEdAdr>setStAdr) &&(wtEdAdr>=setEdAdr)) ) {
				plcmd[i].cnt++;
			}
		}
		break;
		
	case OP_WORD_SD:
		if((stadr>=SD_RANGE) ||((stadr+len)>SD_RANGE)) {
			return 1;
		}
		j = 0;
		for(i=stadr; i<(stadr+len); i++) {
			gau16_SD[i] = buf[j];
			gau16Wt_SD[i] = buf[j];
			gau16_ChSd[i] = 1;
			j++;
		}
		for(i=0; i<gu32_MdsHcmdCnt; i++) {
			if(phcmd[i].MstDel ==0)
				continue;
			if((phcmd[i].pname[0]!='S') ||(phcmd[i].pname[1]!='D'))
				continue;
			if((phcmd[i].cmd!=WrMutiReg) &&(phcmd[i].cmd!=WrSimpReg))
				continue;
			setStAdr = phcmd[i].opAdr;
			setEdAdr = phcmd[i].opAdr +phcmd[i].opCnt;
			if( (wtStAdr==setStAdr)
				||((wtStAdr>setStAdr) &&(wtStAdr<setEdAdr) )
				||((wtEdAdr>setStAdr) &&(wtEdAdr>=setEdAdr)) ) {
				phcmd[i].cnt++;
			}
		}
		for(i=0; i<gu32_MdsLcmdCnt; i++) {
			if(plcmd[i].MstDel ==0)
				continue;
			if((plcmd[i].pname[0]!='S') ||(plcmd[i].pname[1]!='D'))
				continue;
			if((plcmd[i].cmd!=WrMutiReg) &&(plcmd[i].cmd!=WrSimpReg))
				continue;
			setStAdr = plcmd[i].opAdr;
			setEdAdr = plcmd[i].opAdr +plcmd[i].opCnt;
			if( (wtStAdr==setStAdr)
				||((wtStAdr>setStAdr) &&(wtStAdr<setEdAdr) )
				||((wtEdAdr>setStAdr) &&(wtEdAdr>=setEdAdr)) ) {
				plcmd[i].cnt++;
			}
		}
		break;

	case OP_WORD_Z:
		if((stadr>=Z_RANGE) ||((stadr+len)>Z_RANGE)) {
			return 1;
		}
		j = 0;
		for(i=stadr; i<(stadr+len); i++) {
			gau16_Z[i] = buf[j];
			gau16Wt_Z[i] = buf[j];
			gau16_ChZ[i] = 1;
			j++;
		}
		for(i=0; i<gu32_MdsHcmdCnt; i++) {
			if(phcmd[i].MstDel ==0)
				continue;
			if((phcmd[i].pname[0]!='Z') ||(_yGetStrLen(phcmd[i].pname)!=1))
				continue;
			if((phcmd[i].cmd!=WrMutiReg) &&(phcmd[i].cmd!=WrSimpReg))
				continue;
			setStAdr = phcmd[i].opAdr;
			setEdAdr = phcmd[i].opAdr +phcmd[i].opCnt;
			if( (wtStAdr==setStAdr)
				||((wtStAdr>setStAdr) &&(wtStAdr<setEdAdr) )
				||((wtEdAdr>setStAdr) &&(wtEdAdr>=setEdAdr)) ) {
				phcmd[i].cnt++;
			}
		}
		for(i=0; i<gu32_MdsLcmdCnt; i++) {
			if(plcmd[i].MstDel ==0)
				continue;
			if((plcmd[i].pname[0]!='Z') ||(_yGetStrLen(plcmd[i].pname)!=1))
				continue;
			if((plcmd[i].cmd!=WrMutiReg) &&(plcmd[i].cmd!=WrSimpReg))
				continue;
			setStAdr = plcmd[i].opAdr;
			setEdAdr = plcmd[i].opAdr +plcmd[i].opCnt;
			if( (wtStAdr==setStAdr)
				||((wtStAdr>setStAdr) &&(wtStAdr<setEdAdr) )
				||((wtEdAdr>setStAdr) &&(wtEdAdr>=setEdAdr)) ) {
				plcmd[i].cnt++;
			}
		}
		break;		
	default:
		return -1;		
	}

	return 0;
}

int CMdBus::mdbus_read_dword(int type, unsigned int *buf, unsigned int stadr, unsigned int len) {
	unsigned long i,j;
	
	switch(type) {
	case OP_DWORD_D:
		if((stadr>=(D_RANGE-1)) ||((stadr+len*2)>D_RANGE)) {
			return 1;
		}
		j = stadr;
		for(i=0; i<len; i++) {
			buf[i] = gau16_D[j+1]<<16;
			buf[i] += gau16_D[j];
			j += 2;
		}
		break;
		
	case OP_DWORD_R:
		if((stadr>=(R_RANGE-1)) ||((stadr+len*2)>R_RANGE)) {
			return 1;
		}
		j = stadr;
		for(i=0; i<len; i++) {
			buf[i] = gau16_R[j+1]<<16;
			buf[i] += gau16_R[j];
			j += 2;
		}
		break;
		
	case OP_DWORD_SD:
		if((stadr>=(SD_RANGE-1)) ||((stadr+len*2)>SD_RANGE)) {
			return 1;
		}
		j = stadr;
		for(i=0; i<len; i++) {
			buf[i] = gau16_SD[j+1]<<16;
			buf[i] += gau16_SD[j];
			j += 2;
		}
		break;

	case OP_DWORD_Z:
		if((stadr>=(Z_RANGE-1)) ||((stadr+len*2)>Z_RANGE)) {
			return 1;
		}
		j = stadr;
		for(i=0; i<len; i++) {
			buf[i] = gau16_Z[j+1]<<16;
			buf[i] += gau16_Z[j];
			j += 2;
		}
		break;

	case OP_DWORD_C:
		if((stadr>=C_RANGE) ||((stadr+len)>C_RANGE)) {
			return 1;
		}
		j = stadr;
		for(i=0; i<len; i++) {
			buf[i] = gau32_CCurValue[j];
			j++;
		}
		break;

	default:
		return -1;		
	}

	return 0;
}

int CMdBus::mdbus_write_dword(int type, unsigned int *buf, unsigned int stadr, unsigned int len) {
	unsigned long i,j;
	unsigned long setStAdr,setEdAdr,wtStAdr,wtEdAdr;
	struct tag_MdsModlinkCmd *phcmd;
	struct tag_MdsModlinkCmd *plcmd;

	if(len ==0)
		return 0;
	phcmd = &gat_MdsHighCmd[0];
	plcmd = &gat_MdsLowCmd[0];
	wtStAdr = stadr;
	wtEdAdr = stadr +len*2;
	switch(type) {
	case OP_DWORD_D:
		if((stadr>=(D_RANGE-1)) ||((stadr+len*2)>D_RANGE)) {
			return 1;
		}
		j = stadr;
		for(i=0; i<len; i++) {
			gau16_D[j+1] = buf[i]>>16;
			gau16_D[j] = buf[i];
			gau16Wt_D[j+1] = buf[i]>>16;
			gau16Wt_D[j] = buf[i];
			gau16_ChD[j+1] = 1;
			gau16_ChD[j] = 1;
			_yPrintf("WrMutiReg gau16Wt_D[%d]=%d  gau16Wt_D[%d]=%d \n", j, gau16Wt_D[j], j+1, gau16Wt_D[j+1]);
			_yPrintf("WrMutiReg gau16_ChD[%d]=%d  gau16_ChD[%d]=%d \n", j, gau16_ChD[j], j+1, gau16_ChD[j+1]);
			j += 2;
		}
		for(i=0; i<gu32_MdsHcmdCnt; i++) {
			if(phcmd[i].MstDel ==0)
				continue;
			if((phcmd[i].pname[0]!='D') ||(_yGetStrLen(phcmd[i].pname)!=1))
				continue;
			if((phcmd[i].cmd!=WrMutiReg) &&(phcmd[i].cmd!=WrSimpReg))
				continue;
			setStAdr = phcmd[i].opAdr;
			setEdAdr = phcmd[i].opAdr +phcmd[i].opCnt;
			//_yPrintf("WrMutiReg High WtSt=%d WtEd=%d CurSt=%d, CurEd=%d \n", wtStAdr, wtEdAdr, setStAdr, setEdAdr);
			if( (wtStAdr==setStAdr)
				||((wtStAdr>setStAdr) &&(wtStAdr<setEdAdr) )
				||((wtEdAdr>setStAdr) &&(wtEdAdr>=setEdAdr)) ) {
				_yPrintf("WrMutiReg High## WtSt=%d WtEd=%d CurSt=%d, CurEd=%d \n", wtStAdr, wtEdAdr, setStAdr, setEdAdr);
				phcmd[i].cnt++;
			}
		}
		for(i=0; i<gu32_MdsLcmdCnt; i++) {
			if(plcmd[i].MstDel ==0)
				continue;
			if((plcmd[i].pname[0]!='D') ||(_yGetStrLen(plcmd[i].pname)!=1))
				continue;
			if((plcmd[i].cmd!=WrMutiReg) &&(plcmd[i].cmd!=WrSimpReg))
				continue;
			setStAdr = plcmd[i].opAdr;
			setEdAdr = plcmd[i].opAdr +plcmd[i].opCnt;
			//_yPrintf("WrMutiReg Low WtSt=%d WtEd=%d CurSt=%d, CurEd=%d \n", wtStAdr, wtEdAdr, setStAdr, setEdAdr);
			if( (wtStAdr==setStAdr)
				||((wtStAdr>setStAdr) &&(wtStAdr<setEdAdr) )
				||((wtEdAdr>setStAdr) &&(wtEdAdr>=setEdAdr)) ) {
				_yPrintf("WrMutiReg Low## WtSt=%d WtEd=%d CurSt=%d, CurEd=%d \n", wtStAdr, wtEdAdr, setStAdr, setEdAdr);
				plcmd[i].cnt++;
			}
		}
		break;
		
	case OP_DWORD_R:
		if((stadr>=(R_RANGE-1)) ||((stadr+len*2)>R_RANGE)) {
			return 1;
		}
		j = stadr;
		for(i=0; i<len; i++) {
			gau16_R[j+1] = buf[i]>>16;
			gau16_R[j] = buf[i];
			gau16Wt_R[j+1] = buf[i]>>16;
			gau16Wt_R[j] = buf[i];
			gau16_ChR[j+1] = 1;
			gau16_ChR[j] = 1;
			j += 2;
		}
		for(i=0; i<gu32_MdsHcmdCnt; i++) {
			if(phcmd[i].MstDel ==0)
				continue;
			if((phcmd[i].pname[0]!='R') ||(_yGetStrLen(phcmd[i].pname)!=1))
				continue;
			if((phcmd[i].cmd!=WrMutiReg) &&(phcmd[i].cmd!=WrSimpReg))
				continue;
			setStAdr = phcmd[i].opAdr;
			setEdAdr = phcmd[i].opAdr +phcmd[i].opCnt;
			if( (wtStAdr==setStAdr)
				||((wtStAdr>setStAdr) &&(wtStAdr<setEdAdr) )
				||((wtEdAdr>setStAdr) &&(wtEdAdr>=setEdAdr)) ) {
				phcmd[i].cnt++;
			}
		}
		for(i=0; i<gu32_MdsLcmdCnt; i++) {
			if(plcmd[i].MstDel ==0)
				continue;
			if((plcmd[i].pname[0]!='R') ||(_yGetStrLen(plcmd[i].pname)!=1))
				continue;
			if((plcmd[i].cmd!=WrMutiReg) &&(plcmd[i].cmd!=WrSimpReg))
				continue;
			setStAdr = plcmd[i].opAdr;
			setEdAdr = plcmd[i].opAdr +plcmd[i].opCnt;
			if( (wtStAdr==setStAdr)
				||((wtStAdr>setStAdr) &&(wtStAdr<setEdAdr) )
				||((wtEdAdr>setStAdr) &&(wtEdAdr>=setEdAdr)) ) {
				plcmd[i].cnt++;
			}
		}
		break;
		
	case OP_DWORD_SD:
		if((stadr>=(SD_RANGE-1)) ||((stadr+len*2)>SD_RANGE)) {
			return 1;
		}
		j = stadr;
		for(i=0; i<len; i++) {
			gau16_SD[j+1] = buf[i]>>16;
			gau16_SD[j] = buf[i];			
			gau16Wt_SD[j+1] = buf[i]>>16;
			gau16Wt_SD[j] = buf[i];
			gau16_ChSd[j+1] = 1;
			gau16_ChSd[j] = 1;			
			j += 2;
		}
		for(i=0; i<gu32_MdsHcmdCnt; i++) {
			if(phcmd[i].MstDel ==0)
				continue;
			if((phcmd[i].pname[0]!='S') ||(phcmd[i].pname[1]!='D'))
				continue;
			if((phcmd[i].cmd!=WrMutiReg) &&(phcmd[i].cmd!=WrSimpReg))
				continue;
			setStAdr = phcmd[i].opAdr;
			setEdAdr = phcmd[i].opAdr +phcmd[i].opCnt;
			if( (wtStAdr==setStAdr)
				||((wtStAdr>setStAdr) &&(wtStAdr<setEdAdr) )
				||((wtEdAdr>setStAdr) &&(wtEdAdr>=setEdAdr)) ) {
				phcmd[i].cnt++;
			}
		}
		for(i=0; i<gu32_MdsLcmdCnt; i++) {
			if(plcmd[i].MstDel ==0)
				continue;
			if((plcmd[i].pname[0]!='S') ||(plcmd[i].pname[1]!='D'))
				continue;
			if((plcmd[i].cmd!=WrMutiReg) &&(plcmd[i].cmd!=WrSimpReg))
				continue;
			setStAdr = plcmd[i].opAdr;
			setEdAdr = plcmd[i].opAdr +plcmd[i].opCnt;
			if( (wtStAdr==setStAdr)
				||((wtStAdr>setStAdr) &&(wtStAdr<setEdAdr) )
				||((wtEdAdr>setStAdr) &&(wtEdAdr>=setEdAdr)) ) {
				plcmd[i].cnt++;
			}
		}
		break;

	case OP_DWORD_Z:
		if((stadr>=(Z_RANGE-1)) ||((stadr+len*2)>Z_RANGE)) {
			return 1;
		}
		j = stadr;
		for(i=0; i<len; i++) {
			gau16_Z[j+1] = buf[i]>>16;
			gau16_Z[j] = buf[i];			
			gau16Wt_Z[j+1] = buf[i]>>16;
			gau16Wt_Z[j] = buf[i];
			gau16_ChZ[j+1] = 1;
			gau16_ChZ[j] = 1;
			j += 2;
		}
		for(i=0; i<gu32_MdsHcmdCnt; i++) {
			if(phcmd[i].MstDel ==0)
				continue;
			if((phcmd[i].pname[0]!='Z') ||(_yGetStrLen(phcmd[i].pname)!=1))
				continue;
			if((phcmd[i].cmd!=WrMutiReg) &&(phcmd[i].cmd!=WrSimpReg))
				continue;
			setStAdr = phcmd[i].opAdr;
			setEdAdr = phcmd[i].opAdr +phcmd[i].opCnt;
			if( (wtStAdr==setStAdr)
				||((wtStAdr>setStAdr) &&(wtStAdr<setEdAdr) )
				||((wtEdAdr>setStAdr) &&(wtEdAdr>=setEdAdr)) ) {
				phcmd[i].cnt++;
			}
		}
		for(i=0; i<gu32_MdsLcmdCnt; i++) {
			if(plcmd[i].MstDel ==0)
				continue;
			if((plcmd[i].pname[0]!='Z') ||(_yGetStrLen(plcmd[i].pname)!=1))
				continue;
			if((plcmd[i].cmd!=WrMutiReg) &&(plcmd[i].cmd!=WrSimpReg))
				continue;
			setStAdr = plcmd[i].opAdr;
			setEdAdr = plcmd[i].opAdr +plcmd[i].opCnt;		
			if( (wtStAdr==setStAdr)
				||((wtStAdr>setStAdr) &&(wtStAdr<setEdAdr) )
				||((wtEdAdr>setStAdr) &&(wtEdAdr>=setEdAdr)) ) {
				plcmd[i].cnt++;
			}
		}	
		break;
	default:
		return -1;		
	}

	return 0;
}

int CMdBus::mdbus_read_real(int type, float *buf, unsigned int stadr, unsigned int len) {
	unsigned long i,j;
	unsigned int *pu32;

	pu32 = (unsigned int *)(buf);
	switch(type) {
	case OP_REAL_D:
		if((stadr>=(D_RANGE-1)) ||((stadr+len*2)>D_RANGE)) {
			return 1;
		}
		j = stadr;
		for(i=0; i<len; i++) {
			pu32[i] = gau16_D[j+1]<<16;
			pu32[i] += gau16_D[j];
			j += 2;
		}
		break;

	case OP_REAL_R:
		if((stadr>=(R_RANGE-1)) ||((stadr+len*2)>R_RANGE)) {
			return 1;
		}
		j = stadr;
		for(i=0; i<len; i++) {
			pu32[i] = gau16_R[j+1]<<16;
			pu32[i] += gau16_R[j];
			j += 2;
		}
		break;

	default:
		return -1;		
	}
	
	return 0;
}

int CMdBus::mdbus_write_real(int type, float *buf, unsigned int stadr, unsigned int len) {
	unsigned long *pu32;
	unsigned long i,j;
	unsigned long setStAdr,setEdAdr,wtStAdr,wtEdAdr;
	struct tag_MdsModlinkCmd *phcmd;
	struct tag_MdsModlinkCmd *plcmd;

	if(len ==0)
		return 0;
	phcmd = &gat_MdsHighCmd[0];
	plcmd = &gat_MdsLowCmd[0];
	wtStAdr = stadr;
	wtEdAdr = stadr +len*2;
	pu32 = (unsigned long *)(buf);
	switch(type) {
	case OP_REAL_D:
		if((stadr>=(D_RANGE-1)) ||((stadr+len*2)>D_RANGE)) {
			return 1;
		}
		j = stadr;
		for(i=0; i<len; i++) {
			gau16_D[j+1] = pu32[i] >>16;
			gau16_D[j] = pu32[i];			
			gau16Wt_D[j+1] = pu32[i] >>16;
			gau16Wt_D[j] = pu32[i];
			gau16_ChD[j+1] = 1;
			gau16_ChD[j] = 1;			
			j += 2;
		}
		for(i=0; i<gu32_MdsHcmdCnt; i++) {
			if(phcmd[i].MstDel ==0)
				continue;
			if((phcmd[i].pname[0]!='D') ||(_yGetStrLen(phcmd[i].pname)!=1))
				continue;
			if((phcmd[i].cmd!=WrMutiReg) &&(phcmd[i].cmd!=WrSimpReg))
				continue;
			setStAdr = phcmd[i].opAdr;
			setEdAdr = phcmd[i].opAdr +phcmd[i].opCnt;
			if( (wtStAdr==setStAdr)
				||((wtStAdr>setStAdr) &&(wtStAdr<setEdAdr) )
				||((wtEdAdr>setStAdr) &&(wtEdAdr>=setEdAdr)) ) {
				phcmd[i].cnt++;
			}
		}
		for(i=0; i<gu32_MdsLcmdCnt; i++) {
			if(plcmd[i].MstDel ==0)
				continue;
			if((plcmd[i].pname[0]!='D') ||(_yGetStrLen(plcmd[i].pname)!=1))
				continue;
			if((plcmd[i].cmd!=WrMutiReg) &&(plcmd[i].cmd!=WrSimpReg))
				continue;
			setStAdr = plcmd[i].opAdr;
			setEdAdr = plcmd[i].opAdr +plcmd[i].opCnt;
			if( (wtStAdr==setStAdr)
				||((wtStAdr>setStAdr) &&(wtStAdr<setEdAdr) )
				||((wtEdAdr>setStAdr) &&(wtEdAdr>=setEdAdr)) ) {
				plcmd[i].cnt++;
			}
		}
		break;

	case OP_REAL_R:
		if((stadr>=(R_RANGE-1)) ||((stadr+len*2)>R_RANGE)) {
			return 1;
		}
		j = stadr;
		for(i=0; i<len; i++) {
			gau16_R[j+1] = pu32[i] >>16;
			gau16_R[j] = pu32[i];			
			gau16Wt_R[j+1] = pu32[i] >>16;
			gau16Wt_R[j] = pu32[i];
			gau16_ChR[j+1] = 1;
			gau16_ChR[j] = 1;			
			j += 2;
		}
		for(i=0; i<gu32_MdsHcmdCnt; i++) {
			if(phcmd[i].MstDel ==0)
				continue;
			if((phcmd[i].pname[0]!='R') ||(_yGetStrLen(phcmd[i].pname)!=1))
				continue;
			if((phcmd[i].cmd!=WrMutiReg) &&(phcmd[i].cmd!=WrSimpReg))
				continue;
			setStAdr = phcmd[i].opAdr;
			setEdAdr = phcmd[i].opAdr +phcmd[i].opCnt;
			if( (wtStAdr==setStAdr)
				||((wtStAdr>setStAdr) &&(wtStAdr<setEdAdr) )
				||((wtEdAdr>setStAdr) &&(wtEdAdr>=setEdAdr)) ) {
				phcmd[i].cnt++;
			}
		}
		for(i=0; i<gu32_MdsLcmdCnt; i++) {
			if(plcmd[i].MstDel ==0)
				continue;
			if((plcmd[i].pname[0]!='R') ||(_yGetStrLen(plcmd[i].pname)!=1))
				continue;
			if((plcmd[i].cmd!=WrMutiReg) &&(plcmd[i].cmd!=WrSimpReg))
				continue;
			setStAdr = plcmd[i].opAdr;
			setEdAdr = plcmd[i].opAdr +plcmd[i].opCnt;
			if( (wtStAdr==setStAdr)
				||((wtStAdr>setStAdr) &&(wtStAdr<setEdAdr) )
				||((wtEdAdr>setStAdr) &&(wtEdAdr>=setEdAdr)) ) {
				plcmd[i].cnt++;
			}
		}	
		break;

	default:
		return -1;		
	}
	
	return 0;
}

static void thread_recv_func(void *data)
{
	static unsigned long mu32_RecStartTime =0;
	static unsigned long mu32_RecUseTime =10;
	static unsigned long mu32_RecFlag =0;
	static int rdlen = 0;
	static char buf[1024];
	int fd = (int) data;
	int ret = -1;
	int isfram = 0;
	int i;
	struct tag_UartDcb *pdcb;
	static unsigned long cyclecnt =0;

	pdcb = &gat_UartDcb[0];
	if(mu32_RecFlag) {													// 处于接收标志
		if( _yIs1msTimeout(mu32_RecStartTime, mu32_RecUseTime) ) {		// 接收是否完成
			ret = read(fd, &buf[rdlen], (1024-rdlen));
			if(ret >0) {												// 读取到数据
				rdlen += ret;
				if(rdlen >=1024) {										// 数据超过限制,一包结束
					isfram = 1;
				}
				else {													// 数据未超过限制
					mu32_RecStartTime = _yGetCurMsTime();
				}
			}
			else {														// 未读取到数据
				isfram = 1;
			}
		}

		if( isfram ) {													// 是一包数据
			//LOGE ("Thread recv packe data %d\n",cyclecnt);
			cyclecnt++;
			mu32_RecFlag = 0;											// 清除接收标志
			if(rdlen >UART_MAX_BUF) {								// 检查超限
				rdlen = UART_MAX_BUF;
			}
			
			for(i=0; i<rdlen; i++) {								// 数据拷贝到缓冲区
				pdcb->pRxBuf[i] = buf[i];
			}
			pdcb->RxCnt = rdlen;
			rdlen = 0;

            if( pdcb->flag.UseRx ) {                                // 当前使用1号缓冲区
                if(pdcb->flag.Rx0Flg ==0) {                         // 0号缓冲区处于未使用
                    pdcb->aRxCnt[1] = pdcb->RxCnt;                  // 接收个数处理
                    pdcb->flag.Rx1Flg =2;                           // 置1号缓冲区有完整包
                    if(pdcb->flag.HaveRxMsg <2)
                        pdcb->flag.HaveRxMsg++;                     // 置有完整包标志
                    pdcb->pRxBuf = pdcb->paRxBuf[0];                // 使用0号缓冲区
                    pdcb->flag.UseRx =0;                            // 设置使用0号缓冲区标志
                }
            }
            else {
                if(pdcb->flag.Rx1Flg ==0) {                         // 1号缓冲区处于未使用
                    pdcb->aRxCnt[0] = pdcb->RxCnt;                  // 接收个数处理
                    pdcb->flag.Rx0Flg =2;                           // 置0号缓冲区有完整包
                    if(pdcb->flag.HaveRxMsg <2)
                        pdcb->flag.HaveRxMsg++;                     // 置有完整包标志
                    pdcb->pRxBuf = pdcb->paRxBuf[1];                // 使用1号缓冲区
                    pdcb->flag.UseRx =1;                            // 设置使用1号缓冲区标志
                }
            }
            pdcb->RxCnt = 0;                                        // 清除为下次接收准备
            pdcb->flag.isRxing = 0;                                 // 清除正在接收标志				
		}		
	}
	else {																// 未处于接收标志
		ret = read(fd, buf, 1024);
		if(ret >0) {
			rdlen = ret;
			mu32_RecFlag = 1;
			pdcb->flag.isRxing = 1;                                 // 设置正在接收标志
			mu32_RecStartTime = _yGetCurMsTime();
		}	
	}
}

static void thread_send_func(void *data)
{
	static unsigned long mu32_SendStartTime =0;
	static unsigned long mu32_SendUseTime =0;
	static unsigned long mu32_SdFlag =0;
	int fd = (int) data;
	struct tag_UartDcb *pdcb;

	pdcb = &gat_UartDcb[0];
	if(mu32_SdFlag) {													// 处于发送状态
		if( _yIs1msTimeout(mu32_SendStartTime, mu32_SendUseTime) ) {	// 发送完成
			pdcb->flag.isTxing = 0;                                 	// 清除正在发送标志	
			mu32_SdFlag = 0;											// 清除处于发送状态
		}
		
	}
	else if(pdcb->Txflg >0) {											// 已经有数据要发送
		pdcb->Txflg = 0;
		
		write(fd, pdcb->pTxBuf, pdcb->TxCnt);
		mu32_SendUseTime = 1000*11*pdcb->TxCnt/115200;
		if(mu32_SendUseTime ==0) {
			mu32_SendUseTime = 2;
		}
		else {
			mu32_SendUseTime += 2;
		}
		mu32_SendStartTime = _yGetCurMsTime();
		mu32_SdFlag = 1;												// 设置处于发送状态
	}
}

static void *thread_time_func(void *data)
{	
	int fd = (int) data;

	LOGE ("Create time_thread ok! \n");
	while(1) {
		usleep(1*1000);													// 延迟1 MS
		gu32_CurMsTime++;
	}

}

int CMdBus::mdus_mainloop(){
	int ret = -1;
	int i;
	pthread_t time_thread = -1;

	ret = pthread_create(&time_thread, NULL, thread_time_func, (void *)this->port_fd);
	if (ret!=0) {
		LOGE ("Create time_thread error!");
		return 1;
	}

	LOGE ("start run in mainloop ok! \n");
	usleep(100*1000);

	while(1) {
		_yMdsMasterProtocolRev();

		usleep(5*1000);
		thread_recv_func((void *)this->port_fd);

		_yRunModlinkModule();


		thread_send_func((void *)this->port_fd);
		usleep(5*1000);
		thread_recv_func((void *)this->port_fd);
	}

	//pthread_join(time_thread, &ret);
}

int set_opt(int fd,int nSpeed, int nBits, char nEvent, int nStop,int timeout)
{
	struct termios newtio,oldtio;
	
	if ( tcgetattr( fd,&oldtio) != 0) {
		LOGE("SetupSerial 1");
		return -1;
	}
	
	bzero( &newtio, sizeof( newtio ) );
	newtio.c_cflag |= CLOCAL | CREAD;
	newtio.c_cflag &= ~CSIZE;
	switch(nBits ) {
	case 7:
		newtio.c_cflag |= CS7;
		break;
	case 8:
		newtio.c_cflag |= CS8;
		break;
	default:
		newtio.c_cflag |= CS8;
		break;
	}
	
	switch( nEvent ) {
	case 'O':
		newtio.c_cflag |= PARENB;
		newtio.c_cflag |= PARODD;
		newtio.c_iflag |= (INPCK | ISTRIP);
		break;
	case 'E':
		newtio.c_iflag |= (INPCK | ISTRIP);
		newtio.c_cflag |= PARENB;
		newtio.c_cflag &= ~PARODD;
		break;
	case 'N':
		newtio.c_cflag &= ~PARENB;
	break;
	}

	switch( nSpeed ) {
	case 2400:
		cfsetispeed(&newtio, B2400);
		cfsetospeed(&newtio, B2400);
		break;
	case 4800:
		cfsetispeed(&newtio, B4800);
		cfsetospeed(&newtio, B4800);
		break;
	case 9600:
		cfsetispeed(&newtio, B9600);
		cfsetospeed(&newtio, B9600);
		break;
	case 115200:
		cfsetispeed(&newtio, B115200);
		cfsetospeed(&newtio, B115200);
		break;
	case 921600:
		cfsetispeed(&newtio, B921600);
		cfsetospeed(&newtio, B921600);
		break;
	default:
		cfsetispeed(&newtio, B9600);
		cfsetospeed(&newtio, B9600);
		break;
	}
	
	//set stop bit
	if( nStop == 1 ) {
		newtio.c_cflag &= ~CSTOPB;
	}
	else if ( nStop == 2 ) {
		newtio.c_cflag |= CSTOPB;
	}

	// set wait time and mine rec byes
	newtio.c_cc[VTIME] = timeout;
	newtio.c_cc[VMIN] = 0;

	tcflush(fd,TCIFLUSH);
	if((tcsetattr(fd,TCSANOW,&newtio))!=0)
	{
		LOGE("com set error");
		return -1;
	}
	LOGE("set done!\n");
	return 0;
}


