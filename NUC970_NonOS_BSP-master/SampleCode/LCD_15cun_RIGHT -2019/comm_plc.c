
#include "comm_plc.h"

Int8U PLC_Comm_RxMode;
Int8U PLC_Comm_RxBuf[200],PLC_Comm_RxBufSave[200];
Int8U PLC_Comm_TxBuf[200];
Int8U cou;
Int8U PLC_Comm_AddH_temp;
Int8U PLC_Comm_AddL_temp;
Int8U PLC_Comm_ErrH_temp;
Int8U PLC_Comm_ErrL_temp;
Int8U xor_temp[2],xor_Rx[2],xor_Tx[2];
Int8U PLC_Comm_RxCommd[3]={0};
Int8U PLC_Comm_RxOk_flag;


void PLC_saveRxData(Int8U sum)
{
Int8U i;
for(i=0;i<sum;i++)	
	{
	PLC_Comm_RxBufSave[i]=PLC_Comm_RxBuf[i];
	}
PLC_Comm_RxBufSave[i]=CR_CHR;
}
void CheckXOR(pInt8U buf, Int8U size)
{
Int8U i,xor=0;
for(i=0;i<size;i++)
	{
	xor^=buf[i];
	}
xor_temp[0]=((xor>>4)&0x0f)+48;
xor_temp[1]=(xor&0x0f)+48;
}

void CommExec_plc(Int8U rx)
{
switch(PLC_Comm_RxMode)
	{
	case 0:
		if(rx=='%')
			{
			cou=0;	PLC_Comm_RxOk_flag=0;
			PLC_Comm_RxBuf[cou++]=rx;
			PLC_Comm_RxMode++;
			}
			break;
	case 1:	//addH
			PLC_Comm_RxBuf[cou++]=rx;
			PLC_Comm_RxMode++;
			break;
	case 2:	//addL		
			PLC_Comm_RxBuf[cou++]=rx;
			PLC_Comm_RxMode++;
			break;
	case 3://  $/!
		if('!'==rx)	//Error--->4
			{	
			PLC_Comm_RxBuf[cou++]=rx;
			PLC_Comm_RxMode++;	
			}
		else if('$'==rx)//ok
			{
			PLC_Comm_RxBuf[cou++]=rx;	
			PLC_Comm_RxMode=9;//------------------------------->-9
			}
		else
			PLC_Comm_RxMode=0;//-----0
			break;
	case 4://errH !
		PLC_Comm_RxBuf[cou++]=rx;
		PLC_Comm_RxMode++;
			break;
	case 5://errL !
		PLC_Comm_RxBuf[cou++]=rx;
		PLC_Comm_RxMode++;
			break;
	case 6://errBCC
		CheckXOR(PLC_Comm_RxBuf,cou);
		xor_Rx[0]=xor_temp[0];
		xor_Rx[1]=xor_temp[1];
		PLC_Comm_RxBuf[cou++]=rx;
		if(xor_Rx[0]==rx)
			{
			PLC_Comm_RxMode++;	
			}
		else//err
			{
			PLC_Comm_RxMode=0;//-----0	
			}
			break;
	case 7://errBCC
		PLC_Comm_RxBuf[cou++]=rx;
		if(xor_Rx[1]==rx)
			{
			PLC_Comm_RxMode++;	
			}
		else//err
			{
			PLC_Comm_RxMode=0;//-----0	
			}
			break;
	case 8://	cr
		if(rx==CR_CHR)
			{
			PLC_Comm_RxOk_flag=1;	//---------------------------.........
			PLC_saveRxData(cou);
			}
		PLC_Comm_RxMode=0;//-----0		
			break;
	//-----------ok--data--------------
	case 9://cmdH
		PLC_Comm_RxBuf[cou++]=rx;
		PLC_Comm_RxCommd[0]=rx;
		PLC_Comm_RxMode++;	
			break;	
	case 10://cmdL
		PLC_Comm_RxBuf[cou++]=rx;
		PLC_Comm_RxCommd[1]=rx;
		PLC_Comm_RxMode++;	
			break;	
	case 11://data
		if(rx!=CR_CHR)
			{
			PLC_Comm_RxBuf[cou++]=rx;	
			if(cou>=250)//err
				{
				PLC_Comm_RxMode=0;//-----0		
				}
			}
		else//==cr
			{
			CheckXOR(PLC_Comm_RxBuf, cou-2);
			xor_Rx[0]=xor_temp[0];
			xor_Rx[1]=xor_temp[1];	
			if((xor_Rx[0]==PLC_Comm_RxBuf[cou-2])&&(xor_Rx[1]==PLC_Comm_RxBuf[cou-1]))//BCC 
				{
				PLC_Comm_RxOk_flag=1;//---------------------------.........
				PLC_saveRxData(cou);
				}
			PLC_Comm_RxMode=0;//-----0		
			}
			break;	
	}
}

void PLC_SendData(pInt8U buf)
{
	
}

void PLC_SendCmd_RCS(Int8U pos_CHR, Int8U num)
{
Int8U i=0,bcd[3];	
PLC_Comm_TxBuf[i++]='%';
PLC_Comm_TxBuf[i++]=PLC_DEVICE_ADDH;
PLC_Comm_TxBuf[i++]=PLC_DEVICE_ADDL;
PLC_Comm_TxBuf[i++]='#';
PLC_Comm_TxBuf[i++]='R';
PLC_Comm_TxBuf[i++]='C';
PLC_Comm_TxBuf[i++]='S';
//´¥µã
PLC_Comm_TxBuf[i++]=pos_CHR;
//±àºÅ
PLC_Comm_TxBuf[i++]=(num/100)+0x30;
PLC_Comm_TxBuf[i++]=((num%100)/10)+0x30;
PLC_Comm_TxBuf[i++]=(num%10)+0x30;
PLC_Comm_TxBuf[i++]=num+0x30;
CheckXOR(PLC_Comm_TxBuf,i);
xor_Tx[0]=xor_temp[0];
xor_Tx[1]=xor_temp[1];	
PLC_Comm_TxBuf[i++]=xor_Tx[0];
PLC_Comm_TxBuf[i++]=xor_Tx[1];
PLC_Comm_TxBuf[i++]=CR_CHR;//cr
PLC_Comm_TxBuf[i++]=0;//0
UART0_SendStr(PLC_Comm_TxBuf);
}


void PLC_CtrlExec(void)
{
Int8U err_code;
if(PLC_Comm_RxOk_flag==1)	
	{
	PLC_Comm_RxOk_flag	=0;
	if((PLC_Comm_RxBufSave[1]==PLC_DEVICE_ADDH)&&(PLC_Comm_RxBufSave[2]==PLC_DEVICE_ADDL))//add 
		{
		if(PLC_Comm_RxBufSave[3]=='$')	//ack
			{
			if((PLC_Comm_RxBufSave[4]=='R')&&(PLC_Comm_RxBufSave[5]=='C'))//RC
				{
				if(PLC_Comm_RxBufSave[6]==CONTACT_ON)//
					{
						BellOUT_ON;
					}
				}
			}
		else if(PLC_Comm_RxBufSave[3]=='!')	//err
			{
			err_code=((PLC_Comm_RxBufSave[4]-48)<<4)+(PLC_Comm_RxBufSave[5]-48);
			switch(err_code)
				{
				case 0x40://BCC err
					break;
				default:
					break;
				}
			}
		}
	}
	
}