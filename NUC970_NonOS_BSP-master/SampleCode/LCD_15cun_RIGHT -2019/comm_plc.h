#ifndef __COMM_PLC_H
#define __COMM_PLC_H



#include"main.h"


#define PLC_DEVICE_ADDH	(0x0+0x30)
#define PLC_DEVICE_ADDL	(0x1+0x30)


#define CONTACT_ON	'1'
#define CONTACT_OFF '0'

#define CR_CHR 13



void CommExec_plc(Int8U rx);
void PLC_CtrlExec(void);



void PLC_SendCmd_RCS(Int8U pos_CHR, Int8U num);

#endif