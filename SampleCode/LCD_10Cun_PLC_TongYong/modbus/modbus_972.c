#include "modbus_972.h"


#include <stdio.h>
#include <stdlib.h>
#include <string.h>


//#include "../App/App_Modbus.h"

#include "app_modbus_972.h"

//#include "uart_modbus.h"

#include "uart_config.h"
//#include "modbus.h"

#include "app_plc.h"

//#include "app_modbus.h"


#include "uart.h"
#include "uart_config.h"

#include "app_modbus_972.h"


#include "app_modbus_servo.h"


unsigned char Modbus_Adder;
unsigned char Modbus_Cmd;
unsigned char Modbus_Length;

unsigned char ModBus_CommEnd_Flag=0;
unsigned char ModBus_Send_Flag=0;

unsigned char Modbus_Sendbuf[64];

unsigned char Modbus_RecvBuf[64];

//unsigned char Modbus_Sendbuf[64];
//unsigned char ModBus_RecvBuf[64];


int ModeBus_DataRecv_Cnt=0;
int ModBuf_TimeOut_TimeCnt=0;
int ModBus_CommCou=0;


unsigned char ModBus_DataBuf[128];
unsigned char ModBus_Rec_Data[128];

unsigned char ModBus_FIFO_Cnt=0;
unsigned char ModBus_FIFO_Buf[32];

unsigned char FIFO_Buf[32];

char App_ModBus_Status=0;
unsigned char Modbus_Int_Send_Flag=0;
unsigned char Modubs_Int_SendCnt=0;

unsigned char Uart_SendBuf[128];

//队列

#define MAX_QUEUE_CNT 32
unsigned char ModBus_Queue_Buf[32][32];//队列缓冲
int ModBus_QueueLoadCou;
unsigned char ModBus_QueueCurCou;
unsigned char ModBus_QueueCou;
unsigned char ModBus_Comm_LinkErr;
unsigned char ModBus_CurCommand;   //当前的通讯命令
unsigned short ModBus_CurAdder;   //当前的通讯地址


void Modbus_Init(void)
{

}


void ModBusIO_Init(void)
{
//LCD_LE=0;
//P3_MUX_CLR=(1<<12);
 RS485_IO_FUN();
RS485_CS_OUT();
ModBus_QueueLoadCou=0;
ModBus_QueueCurCou=0;
}


void ModBus_SendFrame(unsigned char mid,unsigned char mcommand,unsigned short madder,unsigned int mdata)//
{
//int x;
//RS485_SEND();
unsigned short crcdata;
	
if(mcommand==0x10)
	{//多数据写
	Modbus_Sendbuf[0]=mid;
	Modbus_Sendbuf[1]=mcommand;
	Modbus_Sendbuf[2]=madder>>8;
	Modbus_Sendbuf[3]=madder&0xff;
		
	Modbus_Sendbuf[4]=0x00;//寄存器数量
	Modbus_Sendbuf[5]=0x02;
		
	Modbus_Sendbuf[6]=4;//字节数
		
	Modbus_Sendbuf[7]=mdata>>8;
	Modbus_Sendbuf[8]=mdata&0xff;
		
	Modbus_Sendbuf[9]=mdata>>24;
	Modbus_Sendbuf[10]=(mdata>>16)&0xff;
		
	crcdata=ModBus_CRC_Code(Modbus_Sendbuf,11);	//加入CRC
	Modbus_Sendbuf[11]=crcdata&0xff;
	Modbus_Sendbuf[12]=crcdata>>8;	
		
	}
	else
	{
	Modbus_Sendbuf[0]=mid;
	Modbus_Sendbuf[1]=mcommand;
	Modbus_Sendbuf[2]=madder>>8;
	Modbus_Sendbuf[3]=madder&0xff;
	Modbus_Sendbuf[4]=mdata>>8;
	Modbus_Sendbuf[5]=mdata&0xff;
	crcdata=ModBus_CRC_Code(Modbus_Sendbuf,6);	//加入CRC
	Modbus_Sendbuf[6]=crcdata&0xff;
	Modbus_Sendbuf[7]=crcdata>>8;
	}
}


//////////////////////////////////////////
//队列

//队列插入
void ModBus_Queue_Insert(unsigned char cmdtye,unsigned char mid,unsigned char mcommand,unsigned short madder,unsigned int mdata)
{

ModBus_SendFrame(mid,mcommand,madder,mdata);//
if(mcommand==0x10)
	{

	ModBus_Queue_LoadBuf(Modbus_Sendbuf,cmdtye,13);
	}
else
	{
	ModBus_Queue_LoadBuf(Modbus_Sendbuf,cmdtye,8);
	}
}


//初始化队列
void ModBus_Queue_Init(void)
{
	int i;
	for(i=0;i<MAX_QUEUE_CNT;i++)
		{
		ModBus_Queue_Buf[i][0]=0;
		}	
ModBus_QueueLoadCou=0;
}


//装载队列
void ModBus_Queue_LoadBuf(unsigned char *buf, unsigned char sta,unsigned char length)
{
int i;
ModBus_QueueLoadCou=Modbus_Queue_CheckCnt();//获取index
//printf(("ModBus_QueueLoadCou = %d \r\n",ModBus_QueueLoadCou);
if(ModBus_QueueLoadCou<31)//共32个队列
	{
	//ModBus_QueueLoadCou++;
	ModBus_Queue_Buf[ModBus_QueueLoadCou][0]=length;//第一字节为长度
	ModBus_Queue_Buf[ModBus_QueueLoadCou][1]=sta;//状态 发送的状态	
	for(i=0;i<length;i++)
		{
		ModBus_Queue_Buf[ModBus_QueueLoadCou][i+2]=buf[i];
		}	
	}
}





//发送装载后的队列
unsigned char  ModBus_Queue_SendBuf(unsigned char queue,unsigned char flag)
{
int i;
//int x;
int length;
if(queue<=0)
	return 1;
/*
if(flag==1)//队列转换
	{
	if(ModBus_Queue_ChangeBuf()==1)//无队列已完成退出
		return 1;
	}
*/

//RS485_SEND();
length=ModBus_Queue_Buf[queue][0];
for(i=0;i<length;i++)
	{
	Modbus_Sendbuf[i]=ModBus_Queue_Buf[queue][i+2];
	}

//读入当前地址和命令
//Modbus_Sendbuf[0]=MODBUS_SERVO_COMMADD;
ModBus_CurCommand=Modbus_Sendbuf[1];//=A6_COMMAND_REGISTER_WRITE;
ModBus_CurAdder=Modbus_Sendbuf[2]<<8;//=bsnum>>8;
ModBus_CurAdder+=Modbus_Sendbuf[3];//=bsnum&0xff;



UART0_SendBuf(Modbus_Sendbuf,length);

return 0;

}

unsigned char Modbus_Queue_Send_Flag=0;
unsigned char Modbus_Queue_Send_RepeatCnt=0;
unsigned int Modbus_Queue_Send_TimeOut_t=0;



void Modbus_Queue_Clear_SendStatus(void)
{
	
Modbus_Queue_Send_Flag=0;
Modbus_Queue_Send_TimeOut_t=0;
Modbus_Queue_Send_RepeatCnt=0;	
	
}



#define MODBUS_QUEUE_SEND_TIMEOUT 20  //每包超时时间

#define MODBUS_QUEUE_REPEAT_CNT 3	//超时重发次数

//发送装载后的队列
//T113 新改动的
unsigned char  ModBus_Queue_SendFrame(void)
{
int i,x;
int length;

if(Modbus_Queue_Send_Flag!=0)
	{//判断是否超时
		Modbus_Queue_Send_TimeOut_t++;
		if(Modbus_Queue_Send_TimeOut_t>=MODBUS_QUEUE_SEND_TIMEOUT)//判断是否超时
		{
			Modbus_Queue_Send_TimeOut_t=0;
			
			Modbus_Queue_Send_Flag=0;//再次发送
			
			Modbus_Queue_Send_RepeatCnt++;
			if(Modbus_Queue_Send_RepeatCnt>=MODBUS_QUEUE_REPEAT_CNT)//判断是否最大重发次数
			{//重发3次。超时转下一条
				
				Modbus_Queue_Send_RepeatCnt=0;
				
				ModBus_Queue_ChangeBuf();//超时，转下一条发送
			}
			
		}
	else
		return 0;
	}
else
	{
	Modbus_Queue_Send_TimeOut_t=0;		
	}

	
ModBus_QueueLoadCou=Modbus_Queue_CheckCnt();//获取index
//sysprintf("ModBus_QueueLoadCou = %d\r\n",ModBus_QueueLoadCou);
if(ModBus_QueueLoadCou<=0)
	return 1;

ModBus_Send_Flag=0;
Modbus_Queue_Send_Flag=1;

//printf(("ModBus_QueueLoadCou Sending...= %d \r\n",ModBus_QueueLoadCou);

/*
if(flag==1)//队列转换
	{
	if(ModBus_Queue_ChangeBuf()==1)//无队列已完成退出
		return 1;
	}
*/

RS485_SEND();
length=ModBus_Queue_Buf[0][0];
for(i=0;i<length;i++)
	{
	Modbus_Sendbuf[i]=ModBus_Queue_Buf[0][i+2];
	}

//读入当前地址和命令
//Modbus_Sendbuf[0]=MODBUS_SERVO_COMMADD;
Modubs_Cmd_Type=ModBus_Queue_Buf[0][1];
ModBus_CurCommand=Modbus_Sendbuf[1];//=A6_COMMAND_REGISTER_WRITE;
ModBus_CurAdder=Modbus_Sendbuf[2]<<8;//=bsnum>>8;
ModBus_CurAdder+=Modbus_Sendbuf[3];//=bsnum&0xff;

if(length<8)
{
	for(x=0;x<8000;x++);
	RS485_RECV();
//	ModBus_Queue_ChangeBuf();//队列减1
	return 1;
}

//Uart_Modbus_Comm_Send(Modbus_Sendbuf,length);


UART0_SendBuf(Modbus_Sendbuf,length);
for(x=0;x<8000;x++);
RS485_RECV();

//sysprintf("ModBus_Queue_SendFrame\r\n");
//ModBus_Queue_ChangeBuf();//队列减1

ModBus_Send_Flag=1;
return 0;

}



unsigned char ModBus_Queue_ChangeBuf(void)//
{
unsigned int i,n;
	
ModBus_QueueLoadCou=Modbus_Queue_CheckCnt();//获取index
//sysprintf("ModBus_QueueLoadCou = %d \r\n",ModBus_QueueLoadCou);	
if(ModBus_QueueLoadCou>0)
	{//有多个队列  //指向首个队列。待发送
	for(i=0;i<ModBus_QueueLoadCou+1;i++)
		{
		for(n=0;n<32;n++)
			{
			ModBus_Queue_Buf[i][n]=ModBus_Queue_Buf[i+1][n];
			}
		}
	ModBus_QueueLoadCou--;//队列装载计数减1
	for(n=0;n<32;n++)
		{
		ModBus_Queue_Buf[ModBus_QueueLoadCou+1][n]=0;
		}
	if(ModBus_QueueLoadCou==0)
		return 1;//队列空
	else
		return 0;//还有队列
	}
else
	{
	return 1;
	}
}



//检查队列长度
int Modbus_Queue_CheckCnt(void)
{
int i;
	for(i=0;i<MAX_QUEUE_CNT;i++)
	{
		if(ModBus_Queue_Buf[i][0]==0)
			return i;
		
	}	
return -1;
}


void ModBus_Start_SendFrame(void)
{
 if(ModBus_QueueLoadCou>0)
				  {
				  ModBus_CommCou=0;
				  ModBus_CommEnd_Flag=0;
				//  if(ACServoDrvErr_flag==0)
				  ModBus_Queue_SendBuf(1,0);//发送
				  }	
}

//队列相关结束
/////////////////////////////////////////////

//MODBUS_COMM 超时检测  从接收到第一个字节
void ModBus_Comm_Check_Recv_TimeOut(void)
{
unsigned short crcdata,recvcrcdata;
if(ModBus_CommCou>0)
		{			
		ModBuf_TimeOut_TimeCnt++;
		if(ModBuf_TimeOut_TimeCnt>=3)//接收3ms 超时判断
				{
				ModBuf_TimeOut_TimeCnt=0;
		
				if(ModBus_CommCou>2)
				{
					
				crcdata=ModBus_CRC_Code(ModBus_Rec_Data,ModBus_CommCou-2);
				recvcrcdata=(unsigned short)ModBus_Rec_Data[ModBus_CommCou-1]<<8;
				recvcrcdata+=ModBus_Rec_Data[ModBus_CommCou-2];
				if(crcdata==recvcrcdata)
					{
					ModBus_CommEnd_Flag=1;//置接收正确				
					App_Modbus_Decode(ModBus_Rec_Data,ModBus_CommCou);//	App_Modbus_FxPlc_Decode					
					}
				else
					sysprintf("crc Err ModBus_CommCou = %d \r\n",ModBus_CommCou);
				}
					
				//sysprintf("ModBus_CommCou = %d \r\n",ModBus_CommCou);
				ModBus_Send_Flag=0;//置发送完成
				ModBus_CommCou=0;					
				}		
		}	
else
		{
			ModBuf_TimeOut_TimeCnt=0;
			
		}
	
}



//通讯接收
void ModBus_CommExec(unsigned char  rx_data)
{
//int i;
//char a;
//char stemp[8];
unsigned short crcdata,recvcrcdata;
	
#ifdef MODBUS_972
if(ModBus_CommCou<127)
	{
		if(ModBus_CommCou==0)
			{
			if(rx_data>10)//地址不大于10  防错
				return;
			}
		
		if(ModBus_CommCou==1)
			{
			if(rx_data>0x10)//读写命令不大于0x10  防错
				{
					ModBus_CommCou=0;
					return;
				}
			}
			
//		ModBuf_TimeOut_TimeCnt=0;	
		ModBus_Rec_Data[ModBus_CommCou++]=rx_data;	
	}
	
	
	
#else
	
//return;
	
ModBuf_TimeOut_TimeCnt=0;//超时计数清0
if(ModBus_CommCou>=60)
	return;

////////if(ModBus_FIFO_Cnt==0)
////////	return;

////////for(i=0;i<ModBus_FIFO_Cnt;i++)
////////	{
////////	ModBus_Rec_Data[ModBus_CommCou+i]=ModBus_FIFO_Buf[i];	
////////	}
////////if(ModBus_CommCou==0)
////////	ModeBus_DataRecv_Cnt=0;

////////ModBus_CommCou+=ModBus_FIFO_Cnt;
////////ModBus_FIFO_Cnt=0;

//ModBus_CommEnd_Flag=ModBus_FIFO_Cnt;
	
ModBus_Rec_Data[ModBus_CommCou++]=rx_data;	
	
if(ModBus_CommCou>2)
	{
	if((ModBus_Rec_Data[1]==MODBUS_WRITE_CMD)||(ModBus_Rec_Data[1]==MODBUS_MORE_WRITE_CMD)||(ModBus_Rec_Data[1]==MODBUS_CMD_WRITE_COL))	// 0x06或 0x10 命令。返回8个字节 
		{
		if(ModBus_CommCou>=8)
			{//一帧接收完毕
			//ModBus_CommEnd_Flag=1;
			crcdata=ModBus_CRC_Code(ModBus_Rec_Data,6);
			recvcrcdata=(unsigned short)ModBus_Rec_Data[7]<<8;
			recvcrcdata+=ModBus_Rec_Data[6];
			if(crcdata==recvcrcdata)
				{
				ModBus_CommEnd_Flag=1;//置接收正确				
				App_Modbus_Decode(ModBus_Rec_Data,ModBus_CommCou);//	App_Modbus_FxPlc_Decode					
				}				
			ModBus_Send_Flag=0;//置发送完成
			ModBus_CommCou=0;
			}
		}
	else
		{
		if((ModBus_Rec_Data[1]==0x81)||(ModBus_Rec_Data[1]==0x83)||(ModBus_Rec_Data[1]==0x85)||(ModBus_Rec_Data[1]==0x86)||(ModBus_Rec_Data[1]==0x90))
			{//异常返回
			if(ModBus_CommCou>=5)
				{//一帧接收完毕
				crcdata=ModBus_CRC_Code(ModBus_Rec_Data,3);
				recvcrcdata=(unsigned short)ModBus_Rec_Data[4]<<8;
				recvcrcdata+=ModBus_Rec_Data[3];
				if(crcdata==recvcrcdata)
				{
					ModBus_CommEnd_Flag=1;//置接收正确
					App_Modbus_Decode(ModBus_Rec_Data,ModBus_CommCou);//	App_Modbus_FxPlc_Decode
				}
				
					ModBus_Send_Flag=0;//置发送完成
				ModBus_CommCou=0;
				}
			}
		else
			{//读命令的返回
				if(ModBus_CommCou>3)
				{
					if(ModeBus_DataRecv_Cnt<ModBus_Rec_Data[2])//小于数据长度，放入缓冲区
							ModBus_DataBuf[ModeBus_DataRecv_Cnt++]=rx_data;
				}
				
			if(ModBus_CommCou>ModBus_Rec_Data[2]+4)
				{//一帧接收完毕
				//ModBus_CommEnd_Flag=1;
				crcdata=ModBus_CRC_Code(ModBus_Rec_Data,ModBus_Rec_Data[2]+3);
				recvcrcdata=(unsigned short)ModBus_Rec_Data[ModBus_CommCou-1]<<8;
				recvcrcdata+=ModBus_Rec_Data[ModBus_CommCou-2];
			//		sysprintf("Modbus Frame Recv Ok ModBus_CommCou =%d \r\n",ModBus_CommCou);
				if(crcdata==recvcrcdata)
						{								
						//App_Modbus_Decode();//App Modbus 解码
							
						App_Modbus_Decode(ModBus_Rec_Data,ModBus_CommCou);//	App_Modbus_FxPlc_Decode
						//sysprintf("Modbus Frame Recv Ok ModBus_CommCou =%d \r\n",ModBus_CommCou);
						}
				
						
				ModBus_CommEnd_Flag=ModBus_CommCou;//置接收正确			
				if(App_ModBus_Status=='p')
				{
						if(ModBus_CommEnd_Flag>0)
							memcpy(FIFO_Buf,ModBus_Rec_Data,ModBus_CommEnd_Flag);
					}
				ModBus_Send_Flag=0;//置发送完成

				ModBus_CommCou=0;
				}
			}
		}
	}
else
	ModeBus_DataRecv_Cnt=0;//不满接收长度
#endif

}




unsigned short ModBus_CRC_Code(unsigned char *sbuf,unsigned short length)
{ 
int i;
unsigned short crc=0xffff;

while(length--)
	{
	 crc ^= *sbuf++;
	 for (i = 0; i < 8; ++i)
		{
		 if (crc & 1)
			crc = (crc >> 1) ^ 0xA001;
		 else
			crc = (crc >> 1);
		}
	}
 return crc;
}



//ModBus 超时
void ModBus_TimeOut(void)
{
//return;
if(ModBus_Send_Flag==1)
	{//已在发送状态的超时检测 
	if(ModBus_CommCou>0)
			{			
			ModBuf_TimeOut_TimeCnt++;
			if(ModBuf_TimeOut_TimeCnt>=20)	//收到大于一个字节 的超时
					{
						ModBuf_TimeOut_TimeCnt=0;				
						ModBus_CommCou=0;	//超时重新接收			

					ModBus_Send_Flag=0;						
					}			
			}
	else
			{
			ModBuf_TimeOut_TimeCnt++;
			if(ModBuf_TimeOut_TimeCnt>=30)	//一个字节都没收到 超时
					{
					ModBuf_TimeOut_TimeCnt=0;			
					ModBus_CommCou=0;	//超时重新接收		

					ModBus_Send_Flag=0;						
					}					
			}
	}
else
	{
	ModBuf_TimeOut_TimeCnt=0;	
	}	
}




int CommCnt=0;

void Modbus_IntSend_Enter(void)
{
//	UINT32 uOffset;
//	Int32U Uart_Fsr;
//	Int32U u32Reg;	
	 UINT32 uReg = 0;	
//	uOffset = 3 * UARTOFFSET;	
	
	if(Modbus_Int_Send_Flag==0)
		{
			
			//非发送中断进入
	//	if(Uart_SendBuf[0]>0)
				{//发送长度大于0
				//if(!(inpw(REG_UART0_FSR+uOffset) & UART_FSR_TE_FLAG_Msk))
				//	return;
				RS485_SEND();//置成发送
					
				Modbus_Int_Send_Flag=1;
					
				App_Modbus_Send_Return_Flag=0;//清发送返回标志位
					
					
				ModBus_Send_Flag=1;
					
				ModBus_CommCou=0;//接收计数器清0
			//	RLOUT5_OFF;
					
				CommCnt=0;
				
				//////				outpw(REG_UART0_THR+uOffset, Uart_SendBuf[Modubs_Int_SendCnt+2]);	
				//////				Modubs_Int_SendCnt++;			

				Modubs_Int_SendCnt=0;
					
				//开中断
				uReg = inpw(REG_UART0_IER+(3 * UARTOFFSET));
				uReg |= UART_IER_THRE_IEN_Msk;
				outpw(REG_UART0_IER+(3 * UARTOFFSET), uReg); 
				
				}			
		}
	else
		{
		//发送后的中断进入
		
		}
}

void Modbus_IntSend(void)
{		//发送后的中断进入
		UINT32 uOffset;

//	Int32U Uart_Fsr;
//	Int32U u32Reg;	
	 UINT32 uReg = 0;	

	
if(Modbus_Int_Send_Flag==1)
		{
		uOffset = 3 * UARTOFFSET;
		if(Modubs_Int_SendCnt<8)
				{//继续发送
				//	if(	Uart_SendBuf[0]>0)
					{
					outpw(REG_UART0_THR+uOffset, Uart_SendBuf[Modubs_Int_SendCnt+2]);	
					Modubs_Int_SendCnt++;			
					}
				}		
		else
				{					
				if(inpw(REG_UART0_FSR+uOffset) & UART_FSR_TE_FLAG_Msk)			
					{		
						//关中断
					uReg = inpw(REG_UART0_IER+(3 * UARTOFFSET));
					uReg &= ~UART_IER_THRE_IEN_Msk;
					outpw(REG_UART0_IER+(3 * UARTOFFSET), uReg);
						
					//		RLOUT5_ON;	
						
					RS485_RECV();//置成接收							
					ModBus_Queue_ChangeBuf();//转换下队列
						
					Uart_SendBuf[0]=0;//清发送长度
					Modbus_Int_Send_Flag=0;//置发送完毕					
					Modubs_Int_SendCnt=0;
						
					}
				}			
			}
	
}
