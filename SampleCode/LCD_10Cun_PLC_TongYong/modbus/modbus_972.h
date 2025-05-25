#ifndef _MODBUS_972_H
#define _MODBUS_972_H


#include"main.h"

#define RS485_CS_PIN BIT2

//ver1.4 IO==
#define RS485_IO_FUN() (GPIO_OpenBit(GPIOH, RS485_CS_PIN, DIR_OUTPUT, NO_PULL_UP))//P1_MUX_SET_bit.P1_20=1//IO mode
#define RS485_CS_OUT()	 (GPIO_OpenBit(GPIOH, RS485_CS_PIN, DIR_OUTPUT, NO_PULL_UP))//GPIO_ClrBit(GPIOD, LED0)//P1_DIR_SET_bit.P1_20=1//out mode
#define RS485_SEND()  GPIO_SetBit(GPIOH, RS485_CS_PIN)//P1_OUTP_SET_bit.P1_20=1
#define RS485_RECV()  GPIO_ClrBit(GPIOH, RS485_CS_PIN)//P1_OUTP_CLR_bit.P1_20=1
//ver1.4 IO==




#define MODBUS_CMD_READ_REG 0x03
#define MODBUS_CMD_MULTI_WIRTE_REG 0x10
#define MODBUS_CMD_READ_COL 0x02
#define MODBUS_CMD_WRITE_COL 0x05




#define MODBUS_PLC_BIT_WRITE_CMD 0x05		//FX 兼容PLC位写
#define MODBUS_PLC_BIT_READ_CMD 0x01    //FX 兼容PLC位读

#define MODBUS_WRITE_CMD 0x06				//写命令
#define MODBUS_READ_CMD 0x03		  	//读命令
#define MODBUS_MORE_WRITE_CMD 0x10	//多字节写  命令  <=12Byte


extern char App_ModBus_Status;



extern unsigned char ModBus_DataBuf[128];
extern unsigned char ModBus_Rec_Data[128];

extern unsigned char Modbus_Sendbuf[64];



extern int ModeBus_DataRecv_Cnt;
extern int ModBuf_TimeOut_TimeCnt;
extern int ModBus_CommCou;

extern unsigned char Modbus_Adder;
extern unsigned char Modbus_Cmd;
extern unsigned char Modbus_Length;

extern unsigned char ModBus_CommEnd_Flag;
extern unsigned char ModBus_Send_Flag;

extern unsigned char ModBus_CurCommand;   //当前的通讯命令
extern unsigned short ModBus_CurAdder;   //当前的通讯地址



extern unsigned char ModBus_DataBuf[128];
extern unsigned char ModBus_Queue_Buf[32][32];//队列缓冲

extern int ModBus_QueueLoadCou;
extern unsigned char ModBus_QueueCurCou;
extern unsigned char ModBus_QueueCou;
extern unsigned char ModBus_Comm_LinkErr;
extern unsigned char ModBus_CurCommand;   //当前的通讯命令
extern unsigned short ModBus_CurAdder;   //当前的通讯地址



extern unsigned char Modbus_Int_Send_Flag;
extern unsigned char Modubs_Int_SendCnt;
extern unsigned char Uart_SendBuf[128];


void Modbus_Init(void);

void ModBusIO_Init(void);


//Modbus 
void ModBus_SendFrame(unsigned char mid,unsigned char mcommand,unsigned short madder,unsigned int mdata);//

//////////////////////////////////////////
//队列相关
//队列插入
void ModBus_Queue_Insert(unsigned char cmdtye,unsigned char mid,unsigned char mcommand,unsigned short madder,unsigned int mdata);
//初始化队列
void ModBus_Queue_Init(void);
//装载队列
void ModBus_Queue_LoadBuf(unsigned char *buf, unsigned char sta,unsigned char length);

//发送装载后的队列
unsigned char  ModBus_Queue_SendBuf(unsigned char queue,unsigned char flag);

void Modbus_Queue_Clear_SendStatus(void);
//发送装载后的队列
unsigned char  ModBus_Queue_SendFrame(void);


unsigned char ModBus_Queue_ChangeBuf(void);//

//检查队列长度
int Modbus_Queue_CheckCnt(void);


//队列相关结束
//////////////////////////////////////////


//MODBUS_COMM 超时检测  从接收到第一个字节
void ModBus_Comm_Check_Recv_TimeOut(void);

//通讯接收
void ModBus_CommExec(unsigned char  rx_data);
unsigned short ModBus_CRC_Code(unsigned char *sbuf,unsigned short length);

//ModBus 超时
void ModBus_TimeOut(void);

void Modbus_IntSend_Enter(void);
void Modbus_IntSend(void);

#endif
