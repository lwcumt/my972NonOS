
#include"modbus.h"
#include "pic_exec.h"
#include "key.h"
#include "port.h"
#include "timer.h"

/*
#include"chndot.h"

#include"down_status.h"

*/

unsigned char ModBus_Rec_Data[60];
int ModBus_CommCou;
char ModBus_CommHead_Flag;  //接收帧头标志位
char ModBus_CommFrame_Flag; //接收帧标志位
char ModBus_CommModBus_Commd;   //命令
int ModBus_CommAdder;   //地址
int ModBus_CommFileLenth; //文件长度
int ModBus_CommLengthTemp;
char ModBus_CommEnd_Flag;  //帧结束标志位

unsigned char ModBus_BackStatus,ModBus_ForwardStatus;


unsigned char ModBus_SendBuf[32];
unsigned char ModsBuf_RecBuf[32];

unsigned char ModBus_Queue_Buf[16][32];//队列缓冲



unsigned char ModBusWaitTime;//等待计时
unsigned char ModBusWaitTime_Flag;//启动计时;

unsigned int ModBus_CurDesmion;//绝对值位置
 short ModBus_QuanData;  //多圈数据
unsigned int ModBus_TransPulsData; //已发送的脉冲数据

unsigned int ModBus_ACErr;     //驱动错误
unsigned int ModBus_AcErr_HisData[16];//历史错误代码
unsigned int ModBus_AcErr_Type;//

unsigned char ModBus_Comm_LinkErr;

unsigned char ModBus_CurCommand;   //当前的通讯命令
unsigned short ModBus_CurAdder;   //当前的通讯地址

unsigned char ModBus_Busy_Flag;  //通讯忙标志位

unsigned char Modbus_A6_LuoJu;	//螺距
unsigned short Modbus_A6_Puls;     //每转肪冲数
unsigned char Modbus_A6_JianSuBi; //减速比
unsigned int  Modbus_A6_Speed;   //速度
unsigned int  Modbus_A6_SpeedTemp;   //速度暂存

unsigned char Modbus_A6_Speed_Sel;//速度的选择项

unsigned short Modbus_A6_AddSpeedTime; //加速度时间
unsigned short Modbus_A6_DecSpeedTime; //减速时间
unsigned int   Modbus_A6_PulsSize;//每脉冲的距离尺寸

unsigned int Modbus_A6_JiZhunMark;
unsigned int Modbus_A6_JiZhunDesmion;
 short Modbus_A6_JiZhunQuan;

unsigned int Modbus_A6_ManualSpeed;//手动速度


unsigned short ModBus_Status;

unsigned char ModBus_WaitRun_Flag;

unsigned char ModBus_Run_Flag;//运行标志位

unsigned int ModBusCommTime;
unsigned int ModBusCommTimeOut;

unsigned char ModBus_QueueLoadCou;
unsigned char ModBus_QueueCurCou;
unsigned char ModBus_QueueCou;

ModBusQueue ModBus_Queue; 


int ShouLunlunSize;//手轮尺寸
unsigned int ShouLunExecTime;  //手轮执行计时  0.5秒


//pInt16U fPtr;
//unsigned char *dfPtr;


Int8U SendCmdOn_flag;
Int16U SendCmdWaitTime;
Int16U ReadErrorTime;

Int8U ModBus_CodeDataMode;
Int32U CurrentSize_A6Coder;


Int8U A6CoderEqual_flag;//A6编码器等值标记
Int8U A6CoderCorrectMode;//矫正尺寸
Int16U A6CoderCorrectTime;//
Int8U A6CoderCorrectRun_flag;//矫正运行标记

Int32U StartInitSize;	//开机初始尺寸

Int16U A6ReadCoderSizeWaitTime;


void ModBusIO_Init(void)
{
//LCD_LE=0;
//P3_MUX_CLR=(1<<12);
 RS485_IO_FUN();
RS485_CS_OUT();
ModBus_QueueLoadCou=0;
ModBus_QueueCurCou=0;
}

void ModBus_CommExec(Int8U rx_data)
{
int i;
char a;
char stemp[8];
unsigned short crcdata,recvcrcdata;
ModBus_Rec_Data[ModBus_CommCou++]=rx_data;
if(ModBus_CommCou>2)
	{
	if((ModBus_Rec_Data[1]==A6_COMMAND_COIL_WRITE)||(ModBus_Rec_Data[1]==A6_COMMAND_REGISTER_WRITE)||(ModBus_Rec_Data[1]==A6_COMMAND_REGISTER_CWRITE))
		{
		if(ModBus_CommCou>=8)
			{//一帧接收完毕
			//ModBus_CommEnd_Flag=1;
			crcdata=ModBus_CRC_Code(ModBus_Rec_Data,6);
			recvcrcdata=(unsigned short)ModBus_Rec_Data[7]<<8;
			recvcrcdata+=ModBus_Rec_Data[6];
			if(crcdata==recvcrcdata)
				ModBus_CommEnd_Flag=1;//置接收正确
			ModBus_CommCou=0;
			}
		}
	else
		{
		if((ModBus_Rec_Data[1]==0x81)||(ModBus_Rec_Data[1]==0x83)||(ModBus_Rec_Data[1]==0x85)||(ModBus_Rec_Data[1]==0x86))
			{//异常返回
			if(ModBus_CommCou>=5)
				{//一帧接收完毕
				crcdata=ModBus_CRC_Code(ModBus_Rec_Data,3);
				recvcrcdata=(unsigned short)ModBus_Rec_Data[4]<<8;
				recvcrcdata+=ModBus_Rec_Data[3];
				if(crcdata==recvcrcdata)
					ModBus_CommEnd_Flag=1;//置接收正确
				ModBus_CommCou=0;
				}
			}
		else
			{
			if(ModBus_CommCou>ModBus_Rec_Data[2]+4)
				{//一帧接收完毕
				//ModBus_CommEnd_Flag=1;
				crcdata=ModBus_CRC_Code(ModBus_Rec_Data,ModBus_Rec_Data[2]+3);
				recvcrcdata=(unsigned short)ModBus_Rec_Data[ModBus_CommCou-1]<<8;
				recvcrcdata+=ModBus_Rec_Data[ModBus_CommCou-2];
				if(crcdata==recvcrcdata)
					ModBus_CommEnd_Flag=1;//置接收正确
				ModBus_CommCou=0;
				}
			}
		}
	}

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



void ModBus_CRC_DeCode(unsigned char *rbuf)
{


}


void ModBus_SendFrame(unsigned char mid,unsigned char mcommand,unsigned short madder,unsigned short mdata)//
{
int x;
//RS485_SEND();
unsigned short crcdata;
ModBus_SendBuf[0]=mid;
ModBus_SendBuf[1]=mcommand;
ModBus_SendBuf[2]=madder>>8;
ModBus_SendBuf[3]=madder&0xff;
ModBus_SendBuf[4]=mdata>>8;
ModBus_SendBuf[5]=mdata&0xff;
crcdata=ModBus_CRC_Code(ModBus_SendBuf,6);	//加入CRC
ModBus_SendBuf[6]=crcdata&0xff;
ModBus_SendBuf[7]=crcdata>>8;

ModBus_Queue_LoadBuf(ModBus_SendBuf,8);//保存到队列

//UART0_SendBuf(ModBus_SendBuf,8);

//for(x=0;x<8000;x++);
//RS485_RECV();

}


void ModBus_CrcTest(void)
{
unsigned short crcdata;
ModBus_SendBuf[0]=0x01;
ModBus_SendBuf[1]=0x05;
ModBus_SendBuf[2]=0x00;
ModBus_SendBuf[3]=0x60;
ModBus_SendBuf[4]=0x00;
ModBus_SendBuf[5]=0x00;

crcdata=ModBus_CRC_Code(ModBus_SendBuf,6);	//加入CRC
ModBus_SendBuf[6]=crcdata&0xff;
ModBus_SendBuf[7]=crcdata>>8;



ModBus_SendBuf[0]=0x01;
ModBus_SendBuf[1]=0x05;
ModBus_SendBuf[2]=0x00;
ModBus_SendBuf[3]=0x60;
ModBus_SendBuf[4]=0xff;
ModBus_SendBuf[5]=0x00;

crcdata=ModBus_CRC_Code(ModBus_SendBuf,6);	//加入CRC
ModBus_SendBuf[6]=crcdata&0xff;
ModBus_SendBuf[7]=crcdata>>8;


ModBus_SendBuf[0]=0x01;
ModBus_SendBuf[1]=0x06;
ModBus_SendBuf[2]=0x44;
ModBus_SendBuf[3]=0x14;
ModBus_SendBuf[4]=0x00;
ModBus_SendBuf[5]=0x00;

crcdata=ModBus_CRC_Code(ModBus_SendBuf,6);	//加入CRC
ModBus_SendBuf[6]=crcdata&0xff;
ModBus_SendBuf[7]=crcdata>>8;


ModBus_SendBuf[0]=0x01;
ModBus_SendBuf[1]=0x05;
ModBus_SendBuf[2]=0x01;
ModBus_SendBuf[3]=0x20;
ModBus_SendBuf[4]=0x00;
ModBus_SendBuf[5]=0x00;

crcdata=ModBus_CRC_Code(ModBus_SendBuf,6);	//加入CRC
ModBus_SendBuf[6]=crcdata&0xff;
ModBus_SendBuf[7]=crcdata>>8;

}


//设定速度，加减速度时间   block对应的操作块
void ModBus_SetSpeedAndTime(unsigned char block,unsigned short speed,unsigned short addtime,unsigned short dectime)
{
ModBus_WirteBlockSpeed(block,speed);//设定转速
//ModBusWaitTime=20;//等待20mS
//ModBusWaitTime_Flag=1;//启动计时
//while(ModBusWaitTime_Flag==1);//等待

ModBus_WirteBlockAddTime(block,addtime);//设定加速度时间
//ModBusWaitTime=20;//等待20mS
//ModBusWaitTime_Flag=1;//启动计时
//while(ModBusWaitTime_Flag==1);//等待

ModBus_WirteBlockDecTime(block,dectime);//设定减速度时间
//ModBusWaitTime=20;//等待20mS
//ModBusWaitTime_Flag=1;//启动计时
//while(ModBusWaitTime_Flag==1);//等待



}


//装载队列
void ModBus_Queue_LoadBuf(unsigned char *buf,unsigned char length)
{
int i;
//if(ModBus_QueueLoadCou==0)
if(ModBus_QueueLoadCou<15)
	{
	ModBus_QueueLoadCou++;
	ModBus_Queue_Buf[ModBus_QueueLoadCou][0]=length;//第一字节为长度
	for(i=0;i<length;i++)
		{
		ModBus_Queue_Buf[ModBus_QueueLoadCou][i+1]=buf[i];
		}	
	}
//ModBus_QueueLoadCou++;
}


//发送装载后的队列
unsigned char  ModBus_Queue_SendBuf(unsigned char queue,unsigned char flag)
{
int i,x;
int length;
if(flag==1)//队列转换
	{
	if(ModBus_Queue_ChangeBuf()==1)//无队列已完成退出
		return 1;
	}

RS485_SEND();
length=ModBus_Queue_Buf[queue][0];
for(i=0;i<length;i++)
	{
	ModBus_SendBuf[i]=ModBus_Queue_Buf[queue][i+1];
	}

//读入当前地址和命令
//ModBus_SendBuf[0]=MODBUS_SERVO_COMMADD;
ModBus_CurCommand=ModBus_SendBuf[1];//=A6_COMMAND_REGISTER_WRITE;
ModBus_CurAdder=ModBus_SendBuf[2]<<8;//=bsnum>>8;
ModBus_CurAdder+=ModBus_SendBuf[3];//=bsnum&0xff;

UART0_SendBuf(ModBus_SendBuf,length);
for(x=0;x<8000;x++);
RS485_RECV();
return 0;

}

unsigned char ModBus_Queue_ChangeBuf(void)//
{
unsigned int i,n;
if(ModBus_QueueLoadCou>0)
	{//有多个队列  //指向首个队列。待发送
	for(i=1;i<ModBus_QueueLoadCou+1;i++)
		{
		for(n=0;n<32;n++)
			{
			ModBus_Queue_Buf[i][n]=ModBus_Queue_Buf[i+1][n];
			}
		}
	ModBus_QueueLoadCou--;//队列装载计数减1
	for(n=0;n<32;n++)
		{
		ModBus_Queue_Buf[ModBus_QueueLoadCou+1][n]=0xff;
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



void ModBus_WirteBlock(unsigned short block,unsigned char commd,unsigned char v0,unsigned char a0,unsigned char d0, int position)
{
//unsigned int blockdata;
int x;
//RS485_SEND();
unsigned short crcdata;/*
block*=2;//一个BLOCK占2个地址位
block+=0x4800;//BLOCK地址
ModBus_SendBuf[0]=0x01;
ModBus_SendBuf[1]=A6_COMMAND_REGISTER_WRITE;
ModBus_SendBuf[2]=block>>8;
ModBus_SendBuf[3]=block&0xff;

ModBus_SendBuf[4]=(d0<<2)+0;//0为不迁移
ModBus_SendBuf[5]=0x00;//固定00
ModBus_SendBuf[6]=commd;//固定00
ModBus_SendBuf[7]=(v0<<4)+a0;//固定00


crcdata=ModBus_CRC_Code(ModBus_SendBuf,8);	//加入CRC
ModBus_SendBuf[8]=crcdata&0xff;
ModBus_SendBuf[9]=crcdata>>8;

ModBus_SendBuf[8]=(position>>8)&0xff;//(v0<<4)+a0;//固定00
ModBus_SendBuf[9]=(position&0xff);//(v0<<4)+a0;//固定00
ModBus_SendBuf[10]=(position>>24)&0xff;//(v0<<4)+a0;//固定00
ModBus_SendBuf[11]=(position>>16)&0xff;//(v0<<4)+a0;//固定00

crcdata=ModBus_CRC_Code(ModBus_SendBuf,12);	//加入CRC
ModBus_SendBuf[12]=crcdata&0xff;
ModBus_SendBuf[13]=crcdata>>8;

UART0_SendBuf(ModBus_SendBuf,10);
for(x=0;x<8000;x++);
RS485_RECV();
*/
/*

block*=2;//一个BLOCK占2个地址位
block+=0x4800;//BLOCK地址
ModBus_SendBuf[0]=0x01;
ModBus_SendBuf[1]=A6_COMMAND_REGISTER_WRITE;
ModBus_SendBuf[2]=block>>8;
ModBus_SendBuf[3]=block&0xff;

ModBus_SendBuf[4]=(d0<<2)+0;//0为不迁移
ModBus_SendBuf[5]=0x00;//固定00
ModBus_SendBuf[6]=commd;//固定00
ModBus_SendBuf[7]=(v0<<4)+a0;//固定00

ModBus_SendBuf[8]=(position>>8)&0xff;//(v0<<4)+a0;//固定00
ModBus_SendBuf[9]=(position&0xff);//(v0<<4)+a0;//固定00
ModBus_SendBuf[10]=(position>>24)&0xff;//(v0<<4)+a0;//固定00
ModBus_SendBuf[11]=(position>>16)&0xff;//(v0<<4)+a0;//固定00

crcdata=ModBus_CRC_Code(ModBus_SendBuf,12);	//加入CRC
ModBus_SendBuf[12]=crcdata&0xff;
ModBus_SendBuf[13]=crcdata>>8;
UART0_SendBuf(ModBus_SendBuf,14);
for(x=0;x<8000;x++);
RS485_RECV();
*/


block*=2;//一个BLOCK占2个地址位
block+=0x4800;//BLOCK地址
ModBus_SendBuf[0]=0x01;
ModBus_SendBuf[1]=A6_COMMAND_REGISTER_CWRITE;
ModBus_SendBuf[2]=block>>8;
ModBus_SendBuf[3]=block&0xff;
ModBus_SendBuf[4]=0;
ModBus_SendBuf[5]=0x4;
ModBus_SendBuf[6]=0x08;

ModBus_SendBuf[7]=(d0<<2)+0;//0为不迁移
ModBus_SendBuf[8]=0x00;//固定00
ModBus_SendBuf[9]=commd;//block 的命令
ModBus_SendBuf[10]=(v0<<4)+a0;//速度和加速度时间合并

ModBus_SendBuf[11]=(unsigned char)((position>>8));//&0xff;//相对或绝对位置低16位的高位
ModBus_SendBuf[12]=(unsigned char)((position));//;//相对或绝对位置低16位的低位
ModBus_SendBuf[13]=(unsigned char)((position>>24));//&0xff;//相对或绝对位置高16位的高位
ModBus_SendBuf[14]=(unsigned char)((position>>16));//&0xff;//相对或绝对位置高16位的低位

crcdata=ModBus_CRC_Code(ModBus_SendBuf,15);	//加入CRC
ModBus_SendBuf[15]=crcdata&0xff;
ModBus_SendBuf[16]=crcdata>>8;
ModBus_Queue_LoadBuf(ModBus_SendBuf,17);
//UART0_SendBuf(ModBus_SendBuf,17);
//for(x=0;x<8000;x++);
//RS485_RECV();
//*/
}


void ModBus_WirteBlockSpeed(unsigned short bsnum,unsigned short speed)//设置速度  0-15个对应速度索引
{
int x;
//RS485_SEND();
unsigned short crcdata;
bsnum+=0x4600;//0x4600 为0号速度索引初始地址
ModBus_SendBuf[0]=MODBUS_SERVO_COMMADD;
ModBus_SendBuf[1]=A6_COMMAND_REGISTER_WRITE;
ModBus_SendBuf[2]=bsnum>>8;
ModBus_SendBuf[3]=bsnum&0xff;
ModBus_SendBuf[4]=speed>>8;
ModBus_SendBuf[5]=speed&0xff;
crcdata=ModBus_CRC_Code(ModBus_SendBuf,6);	//加入CRC
ModBus_SendBuf[6]=crcdata&0xff;
ModBus_SendBuf[7]=crcdata>>8;

ModBus_Queue_LoadBuf(ModBus_SendBuf,8);
//UART0_SendBuf(ModBus_SendBuf,8);
//for(x=0;x<8000;x++);
//RS485_RECV();
}

void ModBus_WirteBlockAddTime(unsigned short bsnum,unsigned short time)//设置加速时间  0-15个对应加速时间索引
{
int x;
//RS485_SEND();
unsigned short crcdata;
bsnum+=0x4610;//0x4610 为0号加速时间索引初始地址
ModBus_SendBuf[0]=MODBUS_SERVO_COMMADD;
ModBus_SendBuf[1]=A6_COMMAND_REGISTER_WRITE;
ModBus_SendBuf[2]=bsnum>>8;
ModBus_SendBuf[3]=bsnum&0xff;
ModBus_SendBuf[4]=time>>8;
ModBus_SendBuf[5]=time&0xff;
crcdata=ModBus_CRC_Code(ModBus_SendBuf,6);	//加入CRC
ModBus_SendBuf[6]=crcdata&0xff;
ModBus_SendBuf[7]=crcdata>>8;
ModBus_Queue_LoadBuf(ModBus_SendBuf,8);
//UART0_SendBuf(ModBus_SendBuf,8);
//for(x=0;x<8000;x++);
//RS485_RECV();

}

void ModBus_WirteBlockDecTime(unsigned short bsnum,unsigned short time)//设置减速时间  0-15个对应减速时间索引
{
int x;
//RS485_SEND();
unsigned short crcdata;
bsnum+=0x4620;//0x4600 为0号速度索引初始地址
ModBus_SendBuf[0]=MODBUS_SERVO_COMMADD;
ModBus_SendBuf[1]=A6_COMMAND_REGISTER_WRITE;
ModBus_SendBuf[2]=bsnum>>8;
ModBus_SendBuf[3]=bsnum&0xff;
ModBus_SendBuf[4]=time>>8;
ModBus_SendBuf[5]=time&0xff;
crcdata=ModBus_CRC_Code(ModBus_SendBuf,6);	//加入CRC
ModBus_SendBuf[6]=crcdata&0xff;
ModBus_SendBuf[7]=crcdata>>8;
ModBus_Queue_LoadBuf(ModBus_SendBuf,8);
//UART0_SendBuf(ModBus_SendBuf,8);
//for(x=0;x<8000;x++);
//RS485_RECV();
}



void ModBus_Queue_StartBuf(void)//启动队列缓冲区
{
ModBusCommTime++;
switch(ModBusCommTime)
		  {
		  case 1:		
			    if(ModBus_QueueLoadCou>0)
				  {
				  ModBus_CommCou=0;
				  ModBus_CommEnd_Flag=0;
				  if(ACServoDrvErr_flag==0)
				  ModBus_Queue_SendBuf(1,0);//发送
				  }
				//永远都只是第一个队列先发送			
			    //ModBus_SendFrame(0x1,A6_COMMAND_REGISTER_READ,A6_REGISTER_ADDRES4202,0x02);//编码器位置  绝对值
				//ModBus_SendFrame(0x1,A6_COMMAND_REGISTER_READ,A6_REGISTER_ADDRES600F,0x02);//读取当前值
			  break;
		  case 25://通讯超时
				if(ModBus_CommEnd_Flag==1)
					{
					if(ModBus_CurCommand==A6_COMMAND_REGISTER_READ)
						{
						switch(ModBus_CurAdder)
							{
							case A6_REGISTER_ADDRES4202://编码器位置
								ModBus_CurDesmion=(unsigned int)ModBus_Rec_Data[5]<<24;
								ModBus_CurDesmion+=(unsigned int)ModBus_Rec_Data[6]<<16;
								ModBus_CurDesmion+=(unsigned int)ModBus_Rec_Data[3]<<8;
								ModBus_CurDesmion+=(unsigned int)ModBus_Rec_Data[4];
								break;
							case A6_REGISTER_ADDRES4204://多圈数据
								ModBus_QuanData=(unsigned int)ModBus_Rec_Data[5]<<24;
								ModBus_QuanData+=(unsigned int)ModBus_Rec_Data[6]<<16;
								ModBus_QuanData+=(unsigned int)ModBus_Rec_Data[3]<<8;
								ModBus_QuanData+=(unsigned int)ModBus_Rec_Data[4];

								if(Run_flag==1)
									{
								//	if((ModBus_BackStatus==0)&&(ModBus_ForwardStatus==0))
									//	{
										 if(houtui==1)
											{
											 if(((CurrentSize>TargetSize+500-5))&&((CurrentSize<TargetSize+500+5)))
												{
												 Modbus_ACServoStop();
												 ModBus_WaitRun_Flag=1;

												 Modbus_ACMotorRunStart(TargetSize);//后退+5   变成前进
												 Run_flag=1;
												RunStop_flag=0;
												InTargetPosit_flag=0;	//目标位置
												OneCutRoutine_flag=0; // 清 裁切 循环标志
												AutoCutStart_flag=0;
												AirOffOK_flag=0;
												PressUp_flag=0;
												PressDown_flag=0;
												PromptNum_dis();
												}
											// Run_flag=1;//置运行，运行键不能按下
											//Modbus_ACMotorRunStart(TargetSize);
											// Modbus_ACMotorRunStart(CurrentSize-500);// vbcd)
											}
										else
											{
											if(ModBus_WaitRun_Flag==1)
												ModBus_WaitRun_Flag=0;
											if(((CurrentSize>TargetSize-5))&&((CurrentSize<TargetSize+5)))
												{
												 Modbus_ACServoStop();
												}
											}
									//	 }

									ShouLunlunSize=0;
									ShouLunExecTime=0;
									}
								else
									{//判断是否电子手轮有效
									if((ElectricWheelOn_flag==1))
											{//电子手轮处理
											ShouLunExecTime++;
											if(ShouLunExecTime>=10)
												{
												ShouLunExecTime=0;
												if(ShouLunlunSize!=0)
													{
													Modbus_ACMotorShouLun();//手轮转动  0.5秒
													ShouLunlunSize=0;
													}
												}
											}
									else
										{
										ShouLunlunSize=0;
										ShouLunExecTime=0;

										}
									}


								//if(ModBus_WaitRun_Flag==1)
								//{
								//	ModBus_WaitRun_Flag=0;
								//	Modbus_ACMotorRunStart(TargetSize);//后退+5   变成前进

								//}
								break;
							case A6_REGISTER_ADDRES4001://错误代码
							ModBus_ACErr=(unsigned int)ModBus_Rec_Data[3]<<8;
							ModBus_ACErr+=(unsigned int)ModBus_Rec_Data[4];

								break;
							case A6_REGISTER_ADDRES4000://驱动器状态
								//ModBus_Status=(unsigned int)ModBus_Rec_Data[3]<<8;
							//	ModBus_Status+=(unsigned int)ModBus_Rec_Data[4];

								break;
							case 0x00a2:
								ModBus_Status=(unsigned int)ModBus_Rec_Data[3]<<8;
								ModBus_Status+=(unsigned int)ModBus_Rec_Data[4];
								//if(ModBus_Status&0x0001)
							//		 Modbus_ACServoStop();
								break;
														
							}
						}
					else
						{
						if(ModBus_CurCommand==A6_COMMAND_COIL_READ)
							{
							switch(ModBus_CurAdder)
							{
							case 0x0102:
								ModBus_BackStatus=ModBus_Rec_Data[3];
							//	unsigned char ModBus_BackStatus,ModBus_ForwardStatus;
								break;
							case 0x0103:
								ModBus_ForwardStatus=ModBus_Rec_Data[3];
								if(Run_flag==1)
									{
									if((ModBus_BackStatus==0)&&(ModBus_ForwardStatus==0))
										{
										 if(houtui==1)
											{
											 if(((CurrentSize>TargetSize+500-5))&&((CurrentSize<TargetSize+500+5)))
												{
												 Modbus_ACServoStop();
												 ModBus_WaitRun_Flag=1;
												}
											// Run_flag=1;//置运行，运行键不能按下
											//Modbus_ACMotorRunStart(TargetSize);
											// Modbus_ACMotorRunStart(CurrentSize-500);// vbcd)
											}
										else
											{
											if(((CurrentSize>TargetSize-5))&&((CurrentSize<TargetSize+5)))
												{
												 Modbus_ACServoStop();
												}
											}
										 }
									}
								break;	
							}


							}
						}
					

					if(ModBus_Queue_ChangeBuf()==1)
						{//如队列结束，插入查询当前尺寸等队列
						ModBus_SendFrame(0x1,A6_COMMAND_REGISTER_READ,A6_REGISTER_ADDRES4202,0x02);//编码器位置
						ModBus_SendFrame(0x1,A6_COMMAND_REGISTER_READ,A6_REGISTER_ADDRES4204,0x02);//多圈数据
						ModBus_SendFrame(0x1,A6_COMMAND_REGISTER_READ,A6_REGISTER_ADDRES4001,1);//读错误代码
					//	ModBus_SendFrame(0x1,A6_COMMAND_REGISTER_READ,A6_REGISTER_ADDRES4000,1);//读驱动器状态
					//	if(Run_flag==1)
					//		{
					//		ModBus_SendFrame(0x1,A6_COMMAND_COIL_READ,0x0102,1);//查询是否在反转是否完成
					//		ModBus_SendFrame(0x1,A6_COMMAND_COIL_READ,0x0103,1);//查询是否在正转
					//		}
						//	ModBus_SendFrame(0x1,A6_COMMAND_REGISTER_READ,0x00a2,1);//查询定位是否完成
						}				
					ModBus_CommEnd_Flag=0;
					ModBusCommTime=0;//收到有效数据，重新发送
					ModBusCommTimeOut=0;
					ModBus_Comm_LinkErr=0;
					}
				else
					{
					 ModBusCommTime=0;
					 ModBusCommTimeOut++;
					 if(ModBusCommTimeOut>3)
						{ //超时错误
						  ModBusCommTimeOut=0;
						  ModBus_Comm_LinkErr=1;//通讯连接错误
						  if(Run_flag==1)
								{
									Modbus_ACServoStop();
								}
						}
					}

			  break;
		  }
if(ModBusCommTime>100)
	{//严重超时
		ModBus_CommEnd_Flag=0;
					ModBusCommTime=0;//收到有效数据，重新发送
					ModBusCommTimeOut=0;
					ModBus_Comm_LinkErr=1;//通讯连接错误
					if(Run_flag==1)
							{
					Modbus_ACServoStop();
							}

	}
}

/***
void ModBus_Queue_Start(void)//启动队列
{

ModBusCommTime++;
switch(ModBusCommTime)
		  {
		  case 1:
			  	ModBus_CommCou=0;
				ModBus_CommEnd_Flag=0;
				//永远都只是第一个队列先发送
				ModBus_SendFrame(ModBus_Queue.MB_Id[1],ModBus_Queue.MB_Command[1],ModBus_Queue.MB_Adder[1],ModBus_Queue.MB_Data[1]);
				ModBus_CurCommand=ModBus_Queue.MB_Command[1];
				ModBus_CurAdder=ModBus_Queue.MB_Adder[1];
			    //ModBus_SendFrame(0x1,A6_COMMAND_REGISTER_READ,A6_REGISTER_ADDRES4202,0x02);//编码器位置  绝对值
				//ModBus_SendFrame(0x1,A6_COMMAND_REGISTER_READ,A6_REGISTER_ADDRES600F,0x02);//读取当前值
			  break;
		  case 20://通讯超时
			  ModBusCommTime=0;
			  break;
		  }

if(ModBusCommTime>100)
	{//出错严重超时
	 ModBusCommTime=0;
	}
else
	{
	if(ModBusCommTime>5)
		{//判断是否有返回
	    if(ModBus_CommEnd_Flag==1)
					{
					ModBus_CurDesmion=(unsigned int)ModBus_Rec_Data[5]<<24;
					ModBus_CurDesmion+=(unsigned int)ModBus_Rec_Data[6]<<16;
					ModBus_CurDesmion+=(unsigned int)ModBus_Rec_Data[3]<<8;
					ModBus_CurDesmion+=(unsigned int)ModBus_Rec_Data[4];

					if(ModBus_ChangeQueue()==1)
						{//如队列结束，插入查询当前尺寸等队列
						ModBus_LoadQueue(0x1,A6_COMMAND_REGISTER_READ,A6_REGISTER_ADDRES4202,0x02);//编码器位置
						ModBus_LoadQueue(0x1,A6_COMMAND_REGISTER_READ,A6_REGISTER_ADDRES4204,0x02);//多圈数据
						ModBus_LoadQueue(0x1,A6_COMMAND_REGISTER_READ,A6_REGISTER_ADDRES4001,0x02);//读错误代码

						}				
					ModBus_CommEnd_Flag=0;
					ModBusCommTime=0;//收到有效数据，重新发送
					}
		}
	}
}


void ModBus_Queue_Test(void)
{
	unsigned char x,i;
	ModBus_QueueLoadCou=0;
	ModBus_QueueCurCou=0;
ModBus_LoadQueue(0x1,A6_COMMAND_REGISTER_READ,A6_REGISTER_ADDRES4202,0x02);//编码器位置
ModBus_LoadQueue(0x1,A6_COMMAND_REGISTER_READ,A6_REGISTER_ADDRES4204,0x02);//多圈数据
ModBus_LoadQueue(0x1,A6_COMMAND_REGISTER_READ,0x4800,0x0004);

i=ModBus_ChangeQueue();
i=ModBus_ChangeQueue();
i=ModBus_ChangeQueue();
i=ModBus_ChangeQueue();
x=i+ModBus_ChangeQueue();
}



//装载队列
unsigned char  ModBus_LoadQueue(unsigned char mid,unsigned char mcommand,unsigned short madder,unsigned short mdata)
{


if(ModBus_QueueLoadCou<10)
	{
	if(ModBus_QueueLoadCou==ModBus_QueueCurCou)
		{
		ModBus_QueueLoadCou++;//当前队列已在传送，指向下一队列缓存
		}
	ModBus_Queue.MB_Id[ModBus_QueueLoadCou]=mid;
	ModBus_Queue.MB_Command[ModBus_QueueLoadCou]=mcommand;
	ModBus_Queue.MB_Adder[ModBus_QueueLoadCou]=madder;
	ModBus_Queue.MB_Data[ModBus_QueueLoadCou]=mdata;
	ModBus_QueueLoadCou++;
	return 0;
	}
else
	{
	return 1;//队列满，错误
	}
}


//转换队列
unsigned char ModBus_ChangeQueue(void)//大于2个队列有效，否则始终传送第一个队列
{
unsigned int i;
if(ModBus_QueueLoadCou>1)
	{//有多个队列  //指向首个队列。待发送
	for(i=1;i<ModBus_QueueLoadCou;i++)
		{
		ModBus_Queue.MB_Id[i]=ModBus_Queue.MB_Id[i+1];		
		ModBus_Queue.MB_Command[i]=ModBus_Queue.MB_Command[i+1];		
		ModBus_Queue.MB_Adder[i]=ModBus_Queue.MB_Adder[i+1];		
		ModBus_Queue.MB_Data[i]=ModBus_Queue.MB_Data[i+1];		
		}
	ModBus_QueueLoadCou--;//队列装载计数减1
	ModBus_Queue.MB_Id[ModBus_QueueLoadCou]=0xFF;
	ModBus_Queue.MB_Command[ModBus_QueueLoadCou]=0xFF;
	ModBus_Queue.MB_Adder[ModBus_QueueLoadCou]=0xFFFF;
	ModBus_Queue.MB_Data[ModBus_QueueLoadCou]=0xFFFF;
	return 0; //队列转换完成
	}
else
	{//只有一个队列
	return 1;//只有1个队列
	}
}


//删除队列
unsigned char ModBus_DeletQueue(unsigned char queue)// 形参：1：删除第一个队列  16:删除 最后正在执行后面的的所有队列
{
	// /*
// if(ModBus_QueueLoadCou<10)
	// {
	// ModBus_Queue.MB_Id[ModBus_QueueLoadCou]=mid;
	// ModBus_Queue.MB_Command[ModBus_QueueLoadCou]=mcommand;
	// ModBus_Queue.MB_Adder[ModBus_QueueLoadCou]=madder;
	// ModBus_Queue.MB_Data[ModBus_QueueLoadCou]=mdata;
	// ModBus_QueueLoadCou++;
	// return 0;
	// }
// else
	// {
	// return 1;//队列满，错误
	// }
	// 
	return 0;
}
****/






void Modbus_MoveStop(void)
{



}

void Modbus_AC_ChangeSPD(void)  
{
if(flagqyx==1)
	{
	 step_add=10;      
	  step_ground=11; 

	  speedup_steps=30;
	  status=1;      
	  houtui=0; 
	}    
}


void  A6_CalPulsSize(void)   //计算一脉冲的距离
{
Modbus_A6_PulsSize=Modbus_A6_LuoJu*10000/Modbus_A6_Puls;
}

void  A6_CalCurSize(void)//计算当前位置
{
  long long int  A6_CurDesmionSize;
 long long int  JiZhunDesmionSize;
unsigned  long long  LuoJuPuls;
unsigned  long long  LuoJuSize;


 long long int ModBus_CurDesmionTemp;
 long long int Modbus_A6_JiZhunDesmionTemp;

 long long int ModBus_QuanDataTemp;
 long long  int Modbus_A6_JiZhunQuanTemp;
 long long int Modbus_A6_JiZhunTemp;
 long long int CurrentSizeTemp;

int quandata;
//当前圈数据
ModBus_CurDesmionTemp=ModBus_CurDesmion;
ModBus_QuanDataTemp=(int)ModBus_QuanData;
//基准圈数据
Modbus_A6_JiZhunDesmionTemp=Modbus_A6_JiZhunDesmion;
//ModBus_QuanDataTemp=(long long int)ModBus_QuanData;
Modbus_A6_JiZhunQuanTemp=(long long int)Modbus_A6_JiZhunQuan;

//基准值
Modbus_A6_JiZhunTemp=OriginalSize;	//Modbus_A6_JiZhunMark;
Modbus_A6_JiZhunTemp*=10;

/**
// LuoJuPuls=838860700/((unsigned  long long )(Modbus_A6_LuoJu)*1000);
LuoJuPuls=838860800/((unsigned  long long )(Modbus_A6_LuoJu)*1000);

ModBus_CurDesmionTemp*=100;
ModBus_CurDesmionTemp/=(unsigned  long long )(LuoJuPuls);

Modbus_A6_JiZhunDesmionTemp*=100;
Modbus_A6_JiZhunDesmionTemp/=(unsigned  long long )(LuoJuPuls);
***/

//LuoJuSize=((unsigned  long long )(Modbus_A6_LuoJu)*1000*1000)/8388608;

ModBus_CurDesmionTemp=ModBus_CurDesmionTemp*((unsigned  long long )(Modbus_A6_LuoJu)*1000)/8388608;
Modbus_A6_JiZhunDesmionTemp=Modbus_A6_JiZhunDesmionTemp*((unsigned  long long )(Modbus_A6_LuoJu)*1000)/8388608;


A6_CurDesmionSize=((ModBus_QuanDataTemp*Modbus_A6_LuoJu)*1000)+ModBus_CurDesmionTemp;//(ModBus_CurDesmionTemp)*100000/LuoJuPuls;
JiZhunDesmionSize=((Modbus_A6_JiZhunQuanTemp*Modbus_A6_LuoJu)*1000)+Modbus_A6_JiZhunDesmionTemp;//(Modbus_A6_JiZhunDesmionTemp)*100000/LuoJuPuls;
if(A6_CurDesmionSize>JiZhunDesmionSize)
	{
	A6_CurDesmionSize-=JiZhunDesmionSize;
	CurrentSizeTemp=Modbus_A6_JiZhunTemp-A6_CurDesmionSize;
	}
else
	{
	if(A6_CurDesmionSize<JiZhunDesmionSize)
		{
		JiZhunDesmionSize-=A6_CurDesmionSize;
		CurrentSizeTemp=Modbus_A6_JiZhunTemp+JiZhunDesmionSize;
		}
	else
		{
		CurrentSizeTemp=Modbus_A6_JiZhunTemp;
		}
	}


//CurrentSizeTemp/=100;
unsigned int a;

a=CurrentSizeTemp%10;

if((a)>4)
	{//4舍5入
	CurrentSizeTemp/=10;
	CurrentSizeTemp++;
	}
else
	{
	CurrentSizeTemp/=10;
	}

CurrentSize_A6Coder=CurrentSizeTemp;

ModBus_CodeDataMode=0;//读取完毕
			
// //CurrentSize=CurrentSizeTemp;

// // if((ElectricWheelOn_flag==0)&&(Run_flag==0))
	// // {
	// // if(TargetSize!=CurrentSize)
		// // {
		// // if((TargetSize>(CurrentSize-5))&&(TargetSize<(CurrentSize+5)))
			// // {
			// // CurrentSize=TargetSize;

			// // }
		// // }
	// // }


/*

//A6_CurDesmionSize=0x7fffff*1000;

//LuoJuPuls=0x7fffff*1000/(Modbus_A6_LuoJu);//*1000);
LuoJuPuls=8388607000/(unsigned  long long )(Modbus_A6_LuoJu);//*1000);

ModBus_CurDesmionTemp*=20000000;
ModBus_CurDesmionTemp/=(unsigned  long long )(LuoJuPuls);
//ModBus_CurDesmionTemp*=10;


Modbus_A6_JiZhunDesmionTemp*=20000000;
Modbus_A6_JiZhunDesmionTemp/=(unsigned  long long )(LuoJuPuls);
//Modbus_A6_JiZhunDesmionTemp*=10;



A6_CurDesmionSize=((ModBus_QuanDataTemp*Modbus_A6_LuoJu)*100000)+ModBus_CurDesmionTemp;//(ModBus_CurDesmionTemp)*100000/LuoJuPuls;
JiZhunDesmionSize=((Modbus_A6_JiZhunQuanTemp*Modbus_A6_LuoJu)*100000)+Modbus_A6_JiZhunDesmionTemp;//(Modbus_A6_JiZhunDesmionTemp)*100000/LuoJuPuls;
if(A6_CurDesmionSize>JiZhunDesmionSize)
	{
	A6_CurDesmionSize-=JiZhunDesmionSize;
	CurrentSizeTemp=Modbus_A6_JiZhunTemp-A6_CurDesmionSize;
	}
else
	{
	if(A6_CurDesmionSize<JiZhunDesmionSize)
		{
		JiZhunDesmionSize-=A6_CurDesmionSize;
		CurrentSizeTemp=Modbus_A6_JiZhunTemp+JiZhunDesmionSize;
		}
	else
		{
		CurrentSizeTemp=Modbus_A6_JiZhunTemp;
		}
	}


CurrentSizeTemp/=100;
unsigned int a;

a=CurrentSizeTemp%10;

if((a%10)>3)
	{//4舍5入
	CurrentSizeTemp/=10;
	CurrentSizeTemp++;
	}
else
	{
	CurrentSizeTemp/=10;
	}

CurrentSize=CurrentSizeTemp;
*/

}


void A6_LoadSpeed(void)
{
switch(Modbus_A6_Speed_Sel)
	{
	case 0:
		Modbus_A6_Speed=100;
		break;
	case 1:
		Modbus_A6_Speed=200;
		break;
	case 2:
		Modbus_A6_Speed=400;
		break;
	case 3:
		Modbus_A6_Speed=600;
		break;
	case 4:
		Modbus_A6_Speed=800;
		break;
	case 5:
		Modbus_A6_Speed=1000;
		break;
	case 6:
		Modbus_A6_Speed=1200;
		break;
	case 7:
		Modbus_A6_Speed=1400;
		break;
	case 8:
		Modbus_A6_Speed=1500;
		break;
	case 9:
		Modbus_A6_Speed=1600;
		break;
	case 10:
		Modbus_A6_Speed=1800;
		break;
	case 11:
		Modbus_A6_Speed=2000;
		break;
	case 12:
		Modbus_A6_Speed=2200;
		break;
	case 13:
		Modbus_A6_Speed=2500;
		break;
	case 14:
		Modbus_A6_Speed=2800;
		break;
	case 15:
		Modbus_A6_Speed=3000;
		break;
	}
}


void Modbus_ACMotorRunStart(Int32U vbcd)//  AC伺服  运行启动
{
Int32U tempqianjin1;    
Int32U temphoutui1;    
Int32U tragsize;
int rollsteps1;
/*
ModBus_SetSpeedAndTime(0,800,1000,1000);
ModBus_WirteBlock(0,0x1,0,0,0,-20000); // 写入相对目标值
ModBus_SendFrame(0x1,A6_COMMAND_COIL_WRITE,A6_COIL_ADDRESB120,MODBUS_SERVO_ON);  //启动运转  开启STB  STB——ON
ModBus_SendFrame(0x1,A6_COMMAND_COIL_WRITE,A6_COIL_ADDRESB120,MODBUS_SERVO_OFF); //关闭STB STB——OFF

return;
*/
TargetSize=vbcd;
A6_CalPulsSize();//计算一脉冲距离
if(vbcd<CurrentSize)
	{ 
	//tempqianjin1=(CurrentSize-vbcd)*2;
	//rollsteps1=tempqianjin1-yushu;
	tempqianjin1=(CurrentSize-vbcd);

    rollsteps1=tempqianjin1*100/Modbus_A6_PulsSize;//-yushu;

	if(rollsteps1>1)
		{
	tragsize=rollsteps1*Modbus_A6_PulsSize/100;
	tragsize=CurrentSize-tragsize;
	if(tragsize>TargetSize)
		{
		rollsteps1++;
		}
	else
		{
		if(tragsize<TargetSize)
			{
			rollsteps1--;
			}
		}
		}
	
    qianjin=1;
    houtui=0;  
	
	RLOUT1_ON;    // 允许裁切断开
	CutPermit_flag=0;
	}  
else if(vbcd>CurrentSize)
    {
	// temphoutui1=(vbcd-CurrentSize)*2;
		//rollsteps1=temphoutui1+yushu;
	 vbcd+=500;
	// TargetSize+=500;
	 temphoutui1=(vbcd-CurrentSize);

	 rollsteps1=temphoutui1*100/Modbus_A6_PulsSize;//+yushu;

	 if(rollsteps1>1)
		{

	 tragsize=rollsteps1*Modbus_A6_PulsSize/100;
	 tragsize+=CurrentSize;
	 if(tragsize>vbcd)
		{
		rollsteps1--;
		}
	else
		{
		if(tragsize<vbcd)
			{
			rollsteps1++;
			}
		}
		}
	 houtui=1;
	 qianjin=0;
	 
	 
	RLOUT1_ON;    // 允许裁切断开
	CutPermit_flag=0; 
    }  
else
    {
	qianjin=0;
    houtui=0;
	ModBus_Run_Flag=0;
	}   
          
if(houtui==1)
    {     
	step_ground=11; 
//	rollsteps1=rollsteps1+50000/Modbus_A6_PulsSize;    
	//
        
	if(rollsteps1>3000)
		{
	   speedup_steps=100;  
	   Modbus_A6_SpeedTemp=Modbus_A6_Speed;
	  // speedup_steps_B=speedup_steps;
	 //  rollsteps1=(rollsteps1- speedup_steps*22)+2;
	   status=1;      
		
		}
	else if(rollsteps1>2000&&rollsteps1<3001)
		{  
		speedup_steps=45; 
		Modbus_A6_SpeedTemp=Modbus_A6_Speed*80/100;
		//speedup_steps_B=speedup_steps;
		//rollsteps1=(rollsteps1- speedup_steps*22)+2;
		status=1;  
		  
		
		}                                                               
	else if(rollsteps1>1000&&rollsteps1<2001)
		{
	   speedup_steps=30; 
	   Modbus_A6_SpeedTemp=Modbus_A6_Speed*60/100;
	  // speedup_steps_B=speedup_steps;
	  // rollsteps1=(rollsteps1- speedup_steps*22)+2;
	   status=1;  
						
		} 
	else if(rollsteps1>500&&rollsteps1<1001)
		{
	   speedup_steps=20;
	   Modbus_A6_SpeedTemp=Modbus_A6_Speed*40/100;
	 //  speedup_steps_B=speedup_steps;
	  // rollsteps1=(rollsteps1- speedup_steps*22)+2;
	   status=1;  
					
		}   
	else  if(rollsteps1>100&&rollsteps1<501)
		{
		speedup_steps=4;   
		Modbus_A6_SpeedTemp=Modbus_A6_Speed*30/100;
		//speedup_steps_B=speedup_steps;
		//rollsteps1=(rollsteps1- speedup_steps*22)+2;
		status=1;  
			
		}
	else
		{  
		   status=9;    
		   step_add=1;  
		   Modbus_A6_SpeedTemp=Modbus_A6_Speed*20/100;
		   
	 //       speedup_steps=1;
		}
          
	flagtingji8=0;
	flagyunxing8=1;
	step_add=1;     
	
	ModBus_Run_Flag=1;

	ModBus_SetSpeedAndTime(0,Modbus_A6_SpeedTemp,Modbus_A6_AddSpeedTime,Modbus_A6_DecSpeedTime);
	ModBus_WirteBlock(0,0x1,0,0,0,0-rollsteps1); // 写入相对目标值
	ModBus_SendFrame(0x1,A6_COMMAND_COIL_WRITE,A6_COIL_ADDRESB120,MODBUS_SERVO_ON);  //启动运转  开启STB  STB——ON
	ModBus_SendFrame(0x1,A6_COMMAND_COIL_WRITE,A6_COIL_ADDRESB120,MODBUS_SERVO_OFF); //关闭STB STB——OFF

	//Timer1Init();
	//Timer0Disable();
    }  
            
            
if(qianjin==1)//----------------------------------------------------------
    {
     step_ground=11;  
  
	if(rollsteps1>3000)
		{
	   speedup_steps=100;  
	   Modbus_A6_SpeedTemp=Modbus_A6_Speed;
	  // speedup_steps_B=speedup_steps;
	  // rollsteps1=(rollsteps1- speedup_steps*22)+2;
	   status=1;  
	  
		}
	else if(rollsteps1>2000&&rollsteps1<3001)
		{
		speedup_steps=45;
		 Modbus_A6_SpeedTemp=Modbus_A6_Speed*80/100;
	//	speedup_steps_B=speedup_steps;
	//	rollsteps1=(rollsteps1- speedup_steps*22)+2;
		status=1;   
	   
		}
	else if(rollsteps1>1000&&rollsteps1<2001)
		{
	   speedup_steps=30;
	    Modbus_A6_SpeedTemp=Modbus_A6_Speed*60/100;
	 //  speedup_steps_B=speedup_steps;
	 //  rollsteps1=(rollsteps1- speedup_steps*22)+2;
	   status=1;   
				
		} 
	else if(rollsteps1>500&&rollsteps1<1001)
		{
	   speedup_steps=20;
	    Modbus_A6_SpeedTemp=Modbus_A6_Speed*40/100;
	 //  speedup_steps_B=speedup_steps;
	 //  rollsteps1=(rollsteps1- speedup_steps*22)+2;
	   status=1;   
				  
		}   
	else  if(rollsteps1>100&&rollsteps1<501)
		{
		speedup_steps=4;  
		 Modbus_A6_SpeedTemp=Modbus_A6_Speed*30/100;
	//	speedup_steps_B=speedup_steps;
	//	rollsteps1=(rollsteps1- speedup_steps*22)+2;
		status=1;  
		 
		}
	else
		{    
		status=9; 
		step_add=1;  
		Modbus_A6_SpeedTemp=Modbus_A6_Speed*20/100;
	 //       speedup_steps=1;
		}
	
	 flagtingji8=0;     
	 flagyunxing8=1;
	 step_add=1;  
	 
	 ModBus_Run_Flag=1;

	//Timer1Init();
	//Timer0Disable();
	ModBus_SetSpeedAndTime(0,Modbus_A6_SpeedTemp,Modbus_A6_AddSpeedTime,Modbus_A6_DecSpeedTime);
	ModBus_WirteBlock(0,0x1,0,0,0,rollsteps1); // 写入相对目标值
	ModBus_SendFrame(0x1,A6_COMMAND_COIL_WRITE,A6_COIL_ADDRESB120,MODBUS_SERVO_ON);  //启动运转  开启STB  STB——ON
	ModBus_SendFrame(0x1,A6_COMMAND_COIL_WRITE,A6_COIL_ADDRESB120,MODBUS_SERVO_OFF); //关闭STB STB——OFF
	
	}

}



//伺服启动
void Modbus_ACServoOn(void)
{
ModBus_SendFrame(0x1,A6_COMMAND_COIL_WRITE,A6_COIL_ADDRES60,MODBUS_SERVO_ON);
}



//伺服关闭
void Modbus_ACServoOff(void)
{
ModBus_SendFrame(0x1,A6_COMMAND_COIL_WRITE,A6_COIL_ADDRES60,MODBUS_SERVO_OFF);
}


void Modbus_ACServoStop(void)
{
//即时停止
flagtingji8=1;     
flagyunxing8=0; 
t0zhongduan=1;//0;
flagone=0;
flagqyx=0;



//装载队列
ModBus_SendFrame(0x1,A6_COMMAND_COIL_WRITE,A6_COIL_ADDRESB123,MODBUS_SERVO_ON); //即时停止开 H_STOP-ON    H_STOP开和关需要连接执行。 如果HSTOP 一直处于ON，电机不会再运转
ModBus_SendFrame(0x1,A6_COMMAND_COIL_WRITE,A6_COIL_ADDRESB123,MODBUS_SERVO_OFF); //即时停止关  H_STOP——OFF

//Timer1Disable();
//Timer0Init(); 
if(flagyd==1)
	{
	 flagyd=0;
	}
	
RunStop_flag=0;
LowerAC_SPD_flag=0;

stop_time=0;
Run_flag=0;	
if(ACServoDrvErr_flag==0)
	RLOUT1_OFF;    // 允许裁切------------------++++++++++++++


/*
ModBus_SendFrame(0x1,A6_COMMAND_COIL_WRITE,A6_COIL_ADDRESB123,MODBUS_SERVO_ON); //即时停止开 H_STOP-ON    H_STOP开和关需要连接执行。 如果HSTOP 一直处于ON，电机不会再运转
ModBusWaitTime=20;//等待20mS
ModBusWaitTime_Flag=1;//启动计时
while(ModBusWaitTime_Flag==1);//等待
ModBus_SendFrame(0x1,A6_COMMAND_COIL_WRITE,A6_COIL_ADDRESB123,MODBUS_SERVO_OFF); //即时停止关  H_STOP——OFF
ModBusWaitTime=20;//等待20mS
ModBusWaitTime_Flag=1;//启动计时
while(ModBusWaitTime_Flag==1);//等待
*/

}



void Modbus_ACServoMoveBack_MID_SPD(void)    //交流伺服  中速后退
{

houtui=1;
qianjin=0;   

step_add=10;   

step_ground=11; 

speedup_steps=40;
status=1;
flagqyx=2;
 

ModBus_SetSpeedAndTime(0,800,1000,1000);
ModBus_WirteBlock(0,0x1,0,0,0,-10000000); // 写入相对目标值
ModBus_SendFrame(0x1,A6_COMMAND_COIL_WRITE,A6_COIL_ADDRESB120,MODBUS_SERVO_ON);  //启动运转  开启STB  STB——ON
ModBus_SendFrame(0x1,A6_COMMAND_COIL_WRITE,A6_COIL_ADDRESB120,MODBUS_SERVO_OFF); //关闭STB STB——OFF

//Timer1Init();
//Timer0Disable(); 
//BellOUT_OFF;

RLOUT1_ON;    // 允许裁切断开
CutPermit_flag=0;
}



void Modbus_ACServoMoveFwd_MID_SPD(void)  //交流伺服  中速前进
{

	 houtui=0;
qianjin=1;   

step_add=10;   

step_ground=11; 

speedup_steps=40;
status=1;
 flagqyx=2;
 
ModBus_SetSpeedAndTime(0,800,1000,1000);
ModBus_WirteBlock(0,0x1,0,0,0,10000000); // 写入相对目标值
ModBus_SendFrame(0x1,A6_COMMAND_COIL_WRITE,A6_COIL_ADDRESB120,MODBUS_SERVO_ON);  //启动运转  开启STB  STB——ON
ModBus_SendFrame(0x1,A6_COMMAND_COIL_WRITE,A6_COIL_ADDRESB120,MODBUS_SERVO_OFF); //关闭STB STB——OFF

//Timer1Init();
//Timer0Disable(); 
//BellOUT_OFF;

RLOUT1_ON;    // 允许裁切断开
CutPermit_flag=0;

}


void Modbus_ACMotorShouLun(void)//手轮处理
{
unsigned int targ;
unsigned int tempqianjin1;
unsigned int rollsteps1;
if(ModBus_QueueLoadCou<11)
	{
targ=BackLimit;
A6_CalPulsSize();//计算一脉冲距离
if(targ>CurrentSize)
	{
	tempqianjin1=(targ-CurrentSize);

    rollsteps1=tempqianjin1*100/Modbus_A6_PulsSize;//-yushu;

	ModBus_SetSpeedAndTime(0,Modbus_A6_ManualSpeed*40/100,100,100);
	ModBus_WirteBlock(0,0x1,0,0,0,ShouLunlunSize); // 写入相对目标值
	//ModBus_WirteBlock(0,0x1,0,0,0,0-rollsteps1); // 写入相对目标值
	ModBus_SendFrame(0x1,A6_COMMAND_COIL_WRITE,A6_COIL_ADDRESB120,MODBUS_SERVO_ON);  //启动运转  开启STB  STB——ON
	ModBus_SendFrame(0x1,A6_COMMAND_COIL_WRITE,A6_COIL_ADDRESB120,MODBUS_SERVO_OFF); //关闭STB STB——OFF

	}
	}
}


void Modbus_ACMotorDDBack(void)//电子手轮点动  后退
{

unsigned int targ;
unsigned int tempqianjin1;
unsigned int rollsteps1;
if(ModBus_QueueLoadCou<11)
	{
targ=BackLimit;
A6_CalPulsSize();//计算一脉冲距离
if(targ>CurrentSize)
	{
	tempqianjin1=(targ-CurrentSize);

    rollsteps1=tempqianjin1*100/Modbus_A6_PulsSize;//-yushu;

	ModBus_SetSpeedAndTime(0,Modbus_A6_ManualSpeed*40/100,100,100);
	ModBus_WirteBlock(0,0x1,0,0,0,-1); // 写入相对目标值
	//ModBus_WirteBlock(0,0x1,0,0,0,0-rollsteps1); // 写入相对目标值
	ModBus_SendFrame(0x1,A6_COMMAND_COIL_WRITE,A6_COIL_ADDRESB120,MODBUS_SERVO_ON);  //启动运转  开启STB  STB——ON
	ModBus_SendFrame(0x1,A6_COMMAND_COIL_WRITE,A6_COIL_ADDRESB120,MODBUS_SERVO_OFF); //关闭STB STB——OFF

	}
	}
}

void Modbus_ACMotorDDForward(void)//前进
{
unsigned int targ;
unsigned int tempqianjin1;
unsigned int rollsteps1;
if(ModBus_QueueLoadCou<11)
	{
if(OIN4_PIN!=0)  //托板 信号
	{	
	targ=MiddleLimit;
	}
else
		targ=FrontLimit;//Modbus_ACMotorRunStart(FrontLimit);

A6_CalPulsSize();//计算一脉冲距离
if(targ<CurrentSize)
	{
	tempqianjin1=(CurrentSize-targ);
    rollsteps1=tempqianjin1*100/Modbus_A6_PulsSize;//-yushu;   

	ModBus_SetSpeedAndTime(0,Modbus_A6_ManualSpeed*40/100,100,100);
	ModBus_WirteBlock(0,0x1,0,0,0,1); // 写入相对目标值
	//ModBus_WirteBlock(0,0x1,0,0,0,rollsteps1); // 写入相对目标值
	ModBus_SendFrame(0x1,A6_COMMAND_COIL_WRITE,A6_COIL_ADDRESB120,MODBUS_SERVO_ON);  //启动运转  开启STB  STB——ON
	ModBus_SendFrame(0x1,A6_COMMAND_COIL_WRITE,A6_COIL_ADDRESB120,MODBUS_SERVO_OFF); //关闭STB STB——OFF

	}
	}
}



void Modbus_ACMotorGoBack(void)//后退
{

	
unsigned int targ;
unsigned int tempqianjin1;
unsigned int rollsteps1;
/*
if(OIN4_PIN!=0)  //托板 信号
	{	
	targ=MiddleLimit;
	//Modbus_ACMotorRunStart(MiddleLimit);
	}
else
		targ=FrontLimit;//Modbus_ACMotorRunStart(FrontLimit);
		*/
targ=BackLimit;
A6_CalPulsSize();//计算一脉冲距离
if(targ>CurrentSize)
	{

	//tempqianjin1=(CurrentSize-vbcd)*2;
	//rollsteps1=tempqianjin1-yushu;
	tempqianjin1=(targ-CurrentSize);

    rollsteps1=tempqianjin1*100/Modbus_A6_PulsSize;//-yushu;


qianjin=0;
flagqyx=2;
 flagyd=1;

step_add=60;   
step_ground=11; 

speedup_steps=30;
houtui=1; 
status=1;

flagtingji8=0;
flagyunxing8=1;  


	ModBus_SetSpeedAndTime(0,Modbus_A6_ManualSpeed*40/100,1000,1000);
	ModBus_WirteBlock(0,0x1,0,0,0,0-rollsteps1); // 写入相对目标值
	ModBus_SendFrame(0x1,A6_COMMAND_COIL_WRITE,A6_COIL_ADDRESB120,MODBUS_SERVO_ON);  //启动运转  开启STB  STB——ON
	ModBus_SendFrame(0x1,A6_COMMAND_COIL_WRITE,A6_COIL_ADDRESB120,MODBUS_SERVO_OFF); //关闭STB STB——OFF

	/*
ModBus_SetSpeedAndTime(0,1000,1000,1000);
ModBus_WirteBlock(0,0x1,0,0,0,-10000000); // 写入相对目标值
ModBus_SendFrame(0x1,A6_COMMAND_COIL_WRITE,A6_COIL_ADDRESB120,MODBUS_SERVO_ON);  //启动运转  开启STB  STB——ON
ModBus_SendFrame(0x1,A6_COMMAND_COIL_WRITE,A6_COIL_ADDRESB120,MODBUS_SERVO_OFF); //关闭STB STB——OFF
*/

//Timer1Init();
//Timer0Disable();

RLOUT1_ON;    // 允许裁切断开
CutPermit_flag=0;
	}


	/*
qianjin=0;
flagqyx=2;
flagyd=1;

step_add=25;   
step_ground=11; 

speedup_steps=30;
houtui=1; 
status=1;

flagtingji8=0;
flagyunxing8=1;  

//Timer1Init();
//Timer0Disable();

ModBus_SetSpeedAndTime(0,500,1000,1000);
ModBus_WirteBlock(0,0x1,0,0,0,-10000000); // 写入相对目标值
ModBus_SendFrame(0x1,A6_COMMAND_COIL_WRITE,A6_COIL_ADDRESB120,MODBUS_SERVO_ON);  //启动运转  开启STB  STB——ON
ModBus_SendFrame(0x1,A6_COMMAND_COIL_WRITE,A6_COIL_ADDRESB120,MODBUS_SERVO_OFF); //关闭STB STB——OFF


RLOUT1_ON;    // 允许裁切断开
CutPermit_flag=0;
*/
}

void Modbus_ACMotorGoFastBack(void)//快速后退
{

unsigned int targ;
unsigned int tempqianjin1;
unsigned int rollsteps1;
/*
if(OIN4_PIN!=0)  //托板 信号
	{	
	targ=MiddleLimit;
	//Modbus_ACMotorRunStart(MiddleLimit);


}

else
		targ=FrontLimit;//Modbus_ACMotorRunStart(FrontLimit);
		*/
targ=BackLimit;
A6_CalPulsSize();//计算一脉冲距离
if(targ>CurrentSize)
{

	//tempqianjin1=(CurrentSize-vbcd)*2;
	//rollsteps1=tempqianjin1-yushu;
	tempqianjin1=(targ-CurrentSize);

    rollsteps1=tempqianjin1*100/Modbus_A6_PulsSize;//-yushu;


qianjin=0;
flagqyx=2;
 flagyd=1;

step_add=60;   
step_ground=11; 

speedup_steps=30;
houtui=1; 
status=1;

flagtingji8=0;
flagyunxing8=1;  


	ModBus_SetSpeedAndTime(0,Modbus_A6_ManualSpeed,1000,1000);
	ModBus_WirteBlock(0,0x1,0,0,0,0-rollsteps1); // 写入相对目标值
	ModBus_SendFrame(0x1,A6_COMMAND_COIL_WRITE,A6_COIL_ADDRESB120,MODBUS_SERVO_ON);  //启动运转  开启STB  STB——ON
	ModBus_SendFrame(0x1,A6_COMMAND_COIL_WRITE,A6_COIL_ADDRESB120,MODBUS_SERVO_OFF); //关闭STB STB——OFF

	/*

ModBus_SetSpeedAndTime(0,1000,1000,1000);
ModBus_WirteBlock(0,0x1,0,0,0,-10000000); // 写入相对目标值
ModBus_SendFrame(0x1,A6_COMMAND_COIL_WRITE,A6_COIL_ADDRESB120,MODBUS_SERVO_ON);  //启动运转  开启STB  STB——ON
ModBus_SendFrame(0x1,A6_COMMAND_COIL_WRITE,A6_COIL_ADDRESB120,MODBUS_SERVO_OFF); //关闭STB STB——OFF
*/

//Timer1Init();
//Timer0Disable();

RLOUT1_ON;    // 允许裁切断开
CutPermit_flag=0;
	}

}


void Modbus_ACMotorGoForward(void)//前进
{
unsigned int targ;
unsigned int tempqianjin1;
unsigned int rollsteps1;

if(OIN4_PIN!=0)  //托板 信号
	{	
	targ=MiddleLimit;
	//Modbus_ACMotorRunStart(MiddleLimit);
	}
else
		targ=FrontLimit;//Modbus_ACMotorRunStart(FrontLimit);

A6_CalPulsSize();//计算一脉冲距离
if(targ<CurrentSize)
	{

	//tempqianjin1=(CurrentSize-vbcd)*2;
	//rollsteps1=tempqianjin1-yushu;
	tempqianjin1=(CurrentSize-targ);

    rollsteps1=tempqianjin1*100/Modbus_A6_PulsSize;//-yushu;


	flagyd=1;       
	flagqyx=1;
	
	qianjin=1;

	step_add=60;      
	step_ground=11; 

	speedup_steps=30;
	status=1;      
	houtui=0; 
 
	flagtingji8=0;
	flagyunxing8=1;      


	ModBus_SetSpeedAndTime(0,Modbus_A6_ManualSpeed*40/100,1000,1000);
	ModBus_WirteBlock(0,0x1,0,0,0,rollsteps1); // 写入相对目标值
	ModBus_SendFrame(0x1,A6_COMMAND_COIL_WRITE,A6_COIL_ADDRESB120,MODBUS_SERVO_ON);  //启动运转  开启STB  STB——ON
	ModBus_SendFrame(0x1,A6_COMMAND_COIL_WRITE,A6_COIL_ADDRESB120,MODBUS_SERVO_OFF); //关闭STB STB——OFF




/*
ModBus_SetSpeedAndTime(0,1000,1000,1000);
ModBus_WirteBlock(0,0x1,0,0,0,10000000); // 写入相对目标值
ModBus_SendFrame(0x1,A6_COMMAND_COIL_WRITE,A6_COIL_ADDRESB120,MODBUS_SERVO_ON);  //启动运转  开启STB  STB——ON
ModBus_SendFrame(0x1,A6_COMMAND_COIL_WRITE,A6_COIL_ADDRESB120,MODBUS_SERVO_OFF); //关闭STB STB——OFF
*/


//Timer1Init();
//Timer0Disable();

	RLOUT1_ON;    // 允许裁切断开
	CutPermit_flag=0;
	}

	/*

	flagyd=1;       
flagqyx=1;

qianjin=1;

step_add=25;      
step_ground=11; 

speedup_steps=30;
status=1;      
houtui=0; 
 
flagtingji8=0;
flagyunxing8=1;      




ModBus_SetSpeedAndTime(0,500,1000,1000);
ModBus_WirteBlock(0,0x1,0,0,0,10000000); // 写入相对目标值
ModBus_SendFrame(0x1,A6_COMMAND_COIL_WRITE,A6_COIL_ADDRESB120,MODBUS_SERVO_ON);  //启动运转  开启STB  STB——ON
ModBus_SendFrame(0x1,A6_COMMAND_COIL_WRITE,A6_COIL_ADDRESB120,MODBUS_SERVO_OFF); //关闭STB STB——OFF

//Timer1Init();
//Timer0Disable();
RLOUT1_ON;    // 允许裁切断开
CutPermit_flag=0;
*/


}

void Modbus_ACMotorGoFastForward(void)//快速前进
{
unsigned int targ;
unsigned int tempqianjin1;
unsigned int rollsteps1;

if(OIN4_PIN!=0)  //托板 信号
	{	
	targ=MiddleLimit;
	//Modbus_ACMotorRunStart(MiddleLimit);
	}
else
		targ=FrontLimit;//Modbus_ACMotorRunStart(FrontLimit);

A6_CalPulsSize();//计算一脉冲距离
if(targ<CurrentSize)
	{

	//tempqianjin1=(CurrentSize-vbcd)*2;
	//rollsteps1=tempqianjin1-yushu;
	tempqianjin1=(CurrentSize-targ);

    rollsteps1=tempqianjin1*100/Modbus_A6_PulsSize;//-yushu;


	flagyd=1;       
	flagqyx=1;
	
	qianjin=1;

	step_add=60;      
	step_ground=11; 

	speedup_steps=30;
	status=1;      
	houtui=0; 
 
	flagtingji8=0;
	flagyunxing8=1;      


	ModBus_SetSpeedAndTime(0,Modbus_A6_ManualSpeed,1000,1000);
	ModBus_WirteBlock(0,0x1,0,0,0,rollsteps1); // 写入相对目标值
	ModBus_SendFrame(0x1,A6_COMMAND_COIL_WRITE,A6_COIL_ADDRESB120,MODBUS_SERVO_ON);  //启动运转  开启STB  STB——ON
	ModBus_SendFrame(0x1,A6_COMMAND_COIL_WRITE,A6_COIL_ADDRESB120,MODBUS_SERVO_OFF); //关闭STB STB——OFF




/*

ModBus_SetSpeedAndTime(0,1000,1000,1000);
ModBus_WirteBlock(0,0x1,0,0,0,10000000); // 写入相对目标值
ModBus_SendFrame(0x1,A6_COMMAND_COIL_WRITE,A6_COIL_ADDRESB120,MODBUS_SERVO_ON);  //启动运转  开启STB  STB——ON
ModBus_SendFrame(0x1,A6_COMMAND_COIL_WRITE,A6_COIL_ADDRESB120,MODBUS_SERVO_OFF); //关闭STB STB——OFF
*/


//Timer1Init();
//Timer0Disable();

	RLOUT1_ON;    // 允许裁切断开
	CutPermit_flag=0;
	}
}



void Modbus_ACMotor_ReleaseStop(void)
{
flagkey=0;
flagkeysong=1;
// flagyici=0;
 flagtime1=0;
flagyunxing8=0;

/*
if(flagyd==1)
	{
	 flagyd=0;
	 
	   flagzhiyou=0;
	   flagtingji8=1;
	   flagyunxing8=0;
	  // keytingji=0;
	   flagqyx=0;
  
	  flagtingji8=1;
   
	 Timer1Disable();
	 Timer0Init();
	}
	*/

}

void Modbus_ACServoMoveBack_LOW_SPD(void)
{

step_add=50;
step_ground=11; 
speedup_steps=40;  

status=4;   


ModBus_SetSpeedAndTime(0,200,1000,1000);
ModBus_WirteBlock(0,0x1,0,0,0,-10000000); // 写入相对目标值
ModBus_SendFrame(0x1,A6_COMMAND_COIL_WRITE,A6_COIL_ADDRESB120,MODBUS_SERVO_ON);  //启动运转  开启STB  STB——ON
ModBus_SendFrame(0x1,A6_COMMAND_COIL_WRITE,A6_COIL_ADDRESB120,MODBUS_SERVO_OFF); //关闭STB STB——OFF

//Timer1Init();
//Timer0Disable(); 
//BellOUT_OFF;

RLOUT1_ON;    // 允许裁切断开
CutPermit_flag=0;

}





void ModBus_Test(void)
{
int i;
	ModBus_SendFrame(0x1,A6_COMMAND_REGISTER_READ,A6_REGISTER_ADDRES4202,0x02);//编码器位置

	// ModBusWaitTime=20;//等待20mS
	// ModBusWaitTime_Flag=1;//启动计时
	// while(ModBusWaitTime_Flag==1);//等待

	ModBus_SendFrame(0x1,A6_COMMAND_REGISTER_READ,A6_REGISTER_ADDRES4204,0x02);//多圈数据
	// ModBusWaitTime=20;//等待20mS
	// ModBusWaitTime_Flag=1;//启动计时
	// while(ModBusWaitTime_Flag==1);//等待


ModBus_WirteBlockSpeed(0,1500);//设定转速
// ModBusWaitTime=20;//等待20mS
// ModBusWaitTime_Flag=1;//启动计时
// while(ModBusWaitTime_Flag==1);//等待

ModBus_WirteBlockAddTime(0,1000);//设定加速度时间
// ModBusWaitTime=20;//等待20mS
// ModBusWaitTime_Flag=1;//启动计时
// while(ModBusWaitTime_Flag==1);//等待

ModBus_WirteBlockDecTime(0,1000);//设定减速度时间
// ModBusWaitTime=20;//等待20mS
// ModBusWaitTime_Flag=1;//启动计时
// while(ModBusWaitTime_Flag==1);//等待

ModBus_SendFrame(0x1,A6_COMMAND_COIL_WRITE,A6_COIL_ADDRES60,MODBUS_SERVO_OFF);
// ModBusWaitTime=100;//等待20mS
// ModBusWaitTime_Flag=1;//启动计时
// while(ModBusWaitTime_Flag==1);//等待

ModBus_SendFrame(0x1,A6_COMMAND_COIL_WRITE,A6_COIL_ADDRES60,MODBUS_SERVO_ON);
// ModBusWaitTime=200;//等待20mS
// ModBusWaitTime_Flag=1;//启动计时
// while(ModBusWaitTime_Flag==1);//等待

// ModBus_SendFrame(0x1,A6_COMMAND_REGISTER_WRITE,0x4300,0x0055);//打开权限

ModBus_SendFrame(0x1,A6_COMMAND_REGISTER_READ,A6_REGISTER_ADDRES600F,0x02);//读取当前值
// ModBusWaitTime=20;//等待20mS
// ModBusWaitTime_Flag=1;//启动计时
// while(ModBusWaitTime_Flag==1);//等待


/*
ModBus_WirteBlock(0,0x1,0,0,0,50000); // 写入相对目标值
ModBusWaitTime=20;//等待20mS
ModBusWaitTime_Flag=1;//启动计时
while(ModBusWaitTime_Flag==1);//等待

ModBus_SendFrame(0x1,A6_COMMAND_REGISTER_WRITE,A6_REGISTER_ADDRES4414,0);  //指定要Block 0操作
ModBusWaitTime=20;//等待20mS
ModBusWaitTime_Flag=1;//启动计时
while(ModBusWaitTime_Flag==1);//等待


ModBus_SendFrame(0x1,A6_COMMAND_COIL_WRITE,A6_COIL_ADDRESB120,MODBUS_SERVO_ON);  //启动运转  开启STB  STB——ON
ModBusWaitTime=20;//等待20mS
ModBusWaitTime_Flag=1;//启动计时
while(ModBusWaitTime_Flag==1);//等待
ModBus_SendFrame(0x1,A6_COMMAND_COIL_WRITE,A6_COIL_ADDRESB120,MODBUS_SERVO_OFF); //关闭STB STB——OFF
ModBusWaitTime=20;//等待20mS
ModBusWaitTime_Flag=1;//启动计时
while(ModBusWaitTime_Flag==1);//等待

ModBus_SendFrame(0x1,A6_COMMAND_REGISTER_READ,A6_REGISTER_ADDRES600F,0x2);//读取当前值
ModBusWaitTime=20;//等待20mS
ModBusWaitTime_Flag=1;//启动计时
while(ModBusWaitTime_Flag==1);//等待


ModBus_WirteBlock(0,0x1,0,0,0,80000); // 写入相对目标值
ModBusWaitTime=100;//等待20mS
ModBusWaitTime_Flag=1;//启动计时
while(ModBusWaitTime_Flag==1);//等待



//**************************************
//以下测试即时停止

//先运转马达

ModBus_SendFrame(0x1,A6_COMMAND_COIL_WRITE,A6_COIL_ADDRESB120,MODBUS_SERVO_ON);  //启动运转  开启STB  STB——ON
ModBusWaitTime=20;//等待20mS
ModBusWaitTime_Flag=1;//启动计时
while(ModBusWaitTime_Flag==1);//等待
ModBus_SendFrame(0x1,A6_COMMAND_COIL_WRITE,A6_COIL_ADDRESB120,MODBUS_SERVO_OFF); //关闭STB STB——OFF
ModBusWaitTime=20;//等待20mS
ModBusWaitTime_Flag=1;//启动计时
while(ModBusWaitTime_Flag==1);//等待

*/

/*
//即时停止
ModBus_SendFrame(0x1,A6_COMMAND_COIL_WRITE,A6_COIL_ADDRESB123,MODBUS_SERVO_ON); //即时停止开 H_STOP-ON    H_STOP开和关需要连接执行。 如果HSTOP 一直处于ON，电机不会再运转
ModBusWaitTime=20;//等待20mS
ModBusWaitTime_Flag=1;//启动计时
while(ModBusWaitTime_Flag==1);//等待
ModBus_SendFrame(0x1,A6_COMMAND_COIL_WRITE,A6_COIL_ADDRESB123,MODBUS_SERVO_OFF); //即时停止关  H_STOP——OFF
ModBusWaitTime=20;//等待20mS
ModBusWaitTime_Flag=1;//启动计时
while(ModBusWaitTime_Flag==1);//等待


//**************************************
//以下测试减速停止

//先运转马达

ModBus_SendFrame(0x1,A6_COMMAND_COIL_WRITE,A6_COIL_ADDRESB120,MODBUS_SERVO_ON);  //启动运转  开启STB  STB——ON
ModBusWaitTime=20;//等待20mS
ModBusWaitTime_Flag=1;//启动计时
while(ModBusWaitTime_Flag==1);//等待
ModBus_SendFrame(0x1,A6_COMMAND_COIL_WRITE,A6_COIL_ADDRESB120,MODBUS_SERVO_OFF); //关闭STB STB——OFF
ModBusWaitTime=20;//等待20mS
ModBusWaitTime_Flag=1;//启动计时
while(ModBusWaitTime_Flag==1);//等待

*/
/*
//减速停止
ModBus_SendFrame(0x1,A6_COMMAND_COIL_WRITE,A6_COIL_ADDRESB124,MODBUS_SERVO_ON); //减速停止开 S_STOP-ON    S_STOP开和关需要连接执行。 如果S-STOP 一直处于ON，电机不会再运转
ModBusWaitTime=20;//等待20mS
ModBusWaitTime_Flag=1;//启动计时
while(ModBusWaitTime_Flag==1);//等待
ModBus_SendFrame(0x1,A6_COMMAND_COIL_WRITE,A6_COIL_ADDRESB124,MODBUS_SERVO_OFF); //减速停止关  S_STOP——OFF
ModBusWaitTime=20;//等待20mS
ModBusWaitTime_Flag=1;//启动计时
while(ModBusWaitTime_Flag==1);//等待

*/


}



void Modbus_A6_SaveSetData(void)
{
unsigned char *ptr;

ptr=(unsigned char *)(DOWNFILE_SDRAM_ADD); //下载的地址

//螺距
*ptr++=Modbus_A6_LuoJu;

Modbus_A6_Puls=2000;//固定在2000脉冲/转
//周脉冲数
*ptr++=(unsigned char)(Modbus_A6_Puls>>8);
*ptr++=(unsigned char)Modbus_A6_Puls;


//减速比
*ptr++=Modbus_A6_JianSuBi;


//电机速度
*ptr++=(unsigned char)(Modbus_A6_Speed>>8);
*ptr++=(unsigned char)Modbus_A6_Speed;



//手动速度
*ptr++=(unsigned char)(Modbus_A6_ManualSpeed>>8);
*ptr++=(unsigned char)Modbus_A6_ManualSpeed;



//加速时间
*ptr++=(unsigned char)(Modbus_A6_AddSpeedTime>>8);
*ptr++=(unsigned char)Modbus_A6_AddSpeedTime;


//减速时间
*ptr++=(unsigned char)(Modbus_A6_DecSpeedTime>>8);
*ptr++=(unsigned char)Modbus_A6_DecSpeedTime;


//基准
*ptr++=(unsigned char)(Modbus_A6_JiZhunMark>>24);
*ptr++=(unsigned char)(Modbus_A6_JiZhunMark>>16);
*ptr++=(unsigned char)(Modbus_A6_JiZhunMark>>8);
*ptr++=(unsigned char)Modbus_A6_JiZhunMark;


//基准 编码器值
*ptr++=(unsigned char)(Modbus_A6_JiZhunDesmion>>24);
*ptr++=(unsigned char)(Modbus_A6_JiZhunDesmion>>16);
*ptr++=(unsigned char)(Modbus_A6_JiZhunDesmion>>8);
*ptr++=(unsigned char)Modbus_A6_JiZhunDesmion;

//基准  圈数
//*ptr++=(unsigned char)(Modbus_A6_JiZhunQuan>>24);
//*ptr++=(unsigned char)(Modbus_A6_JiZhunQuan>>16);
*ptr++=(unsigned char)(Modbus_A6_JiZhunQuan>>8);
*ptr++=(unsigned char)Modbus_A6_JiZhunQuan;



NandEccWrite_Flag=0;
iFiles.FileLength=64;//读取文件长度	
ChangeFileName("ModbusA6.ini");
File_Create(iFiles.FileName);//建立文件

}



void Modbus_A6_LoadSetData(void)
{

unsigned char *ptr;

ptr=(unsigned char *)(DOWNFILE_SDRAM_ADD); //下载的地址


FileRead("ModbusA6.ini",(unsigned char*)DOWNFILE_SDRAM_ADD);


//螺距
Modbus_A6_LuoJu=*ptr++;


//周脉冲数
Modbus_A6_Puls=(unsigned short)(*ptr++<<8);
Modbus_A6_Puls+=*ptr++;

Modbus_A6_Puls=2000;//固定在2000脉冲/转

//减速比
Modbus_A6_JianSuBi=*ptr++;


//电机速度


Modbus_A6_Speed=(unsigned short)(*ptr++<<8);
Modbus_A6_Speed+=*ptr++;



//手动速度
Modbus_A6_ManualSpeed=(unsigned short)(*ptr++<<8);
Modbus_A6_ManualSpeed+=*ptr++;




//加速时间

Modbus_A6_AddSpeedTime=(unsigned short)(*ptr++<<8);
Modbus_A6_AddSpeedTime+=*ptr++;



//减速时间

Modbus_A6_DecSpeedTime=(unsigned short)(*ptr++<<8);
Modbus_A6_DecSpeedTime+=*ptr++;


//基准
Modbus_A6_JiZhunMark=(unsigned int)(*ptr++<<24);//=(unsigned char)(Modbus_A6_JiZhunMark>>24);
Modbus_A6_JiZhunMark+=(unsigned int)(*ptr++<<16);//*ptr++=(unsigned char)(Modbus_A6_JiZhunMark>>16);
Modbus_A6_JiZhunMark+=(unsigned int)(*ptr++<<8);//*ptr++=(unsigned char)(Modbus_A6_JiZhunMark>>8);
Modbus_A6_JiZhunMark+=(unsigned int)(*ptr++);//*ptr++=(unsigned char)Modbus_A6_JiZhunMark;


//基准 编码器值

Modbus_A6_JiZhunDesmion=(unsigned int)(*ptr++<<24);//=(unsigned char)(Modbus_A6_JiZhunMark>>24);
Modbus_A6_JiZhunDesmion+=(unsigned int)(*ptr++<<16);//*ptr++=(unsigned char)(Modbus_A6_JiZhunMark>>16);
Modbus_A6_JiZhunDesmion+=(unsigned int)(*ptr++<<8);//*ptr++=(unsigned char)(Modbus_A6_JiZhunMark>>8);
Modbus_A6_JiZhunDesmion+=(unsigned int)(*ptr++);//*ptr++=(unsigned char)Modbus_A6_JiZhunMark;



//基准  圈数


//Modbus_A6_JiZhunQuan=(unsigned int)(*ptr++<<24);//=(unsigned char)(Modbus_A6_JiZhunMark>>24);
//Modbus_A6_JiZhunQuan+=(unsigned int)(*ptr++<<16);//*ptr++=(unsigned char)(Modbus_A6_JiZhunMark>>16);
Modbus_A6_JiZhunQuan=(unsigned short)(*ptr++<<8);//*ptr++=(unsigned char)(Modbus_A6_JiZhunMark>>8);
Modbus_A6_JiZhunQuan+=(unsigned short)(*ptr++);//*ptr++=(unsigned char)Modbus_A6_JiZhunMark;


/***
if(((Modbus_A6_LuoJu<1)||(Modbus_A6_LuoJu>20))||
	((Modbus_A6_Puls<500)||(Modbus_A6_Puls>10000))||
	((Modbus_A6_JianSuBi<1)||(Modbus_A6_JianSuBi>5))||
	((Modbus_A6_Speed<200)||(Modbus_A6_Speed>3000))||
	((Modbus_A6_AddSpeedTime<100)||(Modbus_A6_AddSpeedTime>2000))||
	((Modbus_A6_DecSpeedTime<100)||(Modbus_A6_DecSpeedTime>2000))||
	((Modbus_A6_JiZhunMark<1000)||(Modbus_A6_JiZhunMark>300000))||
	((Modbus_A6_ManualSpeed<200)||(Modbus_A6_ManualSpeed>3000)))
	{//数据不在范围内，重新初始化
	Modbus_A6_LuoJu=12;
	Modbus_A6_Puls=2000;
	Modbus_A6_JianSuBi=1;
	Modbus_A6_Speed=1800;
	Modbus_A6_ManualSpeed=1000;
	Modbus_A6_AddSpeedTime=500;
	Modbus_A6_DecSpeedTime=500;
	Modbus_A6_JiZhunMark=50000;
	Modbus_A6_SaveSetData();
	}
	**/
	Modbus_A6_LuoJu=10;
	// Modbus_A6_JiZhunMark=123450;
	Modbus_A6_SaveSetData();
}

void Modbus_A6_SaveErrData(void)//保存错误代码
{
unsigned int *ptr;
int i;

ptr=(unsigned int *)(DOWNFILE_SDRAM_ADD); //下载的地址
for(i=0;i<16;i++)
	{
	*ptr++=ModBus_AcErr_HisData[i];
	}

NandEccWrite_Flag=0;
iFiles.FileLength=64;//读取文件长度	
ChangeFileName("ModbusA6Err.ini");
File_Create(iFiles.FileName);//建立文件

}
void Modbus_A6_LoadErrData(void) //调入错误代码
{

unsigned int *ptr;
int i;

ptr=(unsigned int *)(DOWNFILE_SDRAM_ADD); //下载的地址


FileRead("ModbusA6Err.ini",(unsigned char*)DOWNFILE_SDRAM_ADD);

for(i=0;i<16;i++)
	{
	ModBus_AcErr_HisData[i]=*ptr++;
	}
}
















//--------------
void ModbusComm_CtrlExec(void)
{
if(SendCmdOn_flag==0)	//发送------------->>>>>>
	{
	if(ModBus_QueueLoadCou>0)
		{
		ModBus_CommCou=0;
		ModBus_CommEnd_Flag=0;
		// if(ACServoDrvErr_flag==0)
			{
			ModBus_Queue_SendBuf(1,0);//
			SendCmdOn_flag=1;
			SendCmdWaitTime=0;
			}
		}
	}


if(ModBus_CommEnd_Flag==1)		//接收----------<<<<<
	{
	switch(ModBus_CurCommand)
		{
		case A6_COMMAND_REGISTER_READ://读取 寄存器
				switch(ModBus_CurAdder)
					{
					case A6_REGISTER_ADDRES4202://编码器位置
						ModBus_CurDesmion=(unsigned int)ModBus_Rec_Data[5]<<24;
						ModBus_CurDesmion+=(unsigned int)ModBus_Rec_Data[6]<<16;
						ModBus_CurDesmion+=(unsigned int)ModBus_Rec_Data[3]<<8;
						ModBus_CurDesmion+=(unsigned int)ModBus_Rec_Data[4];
						ModBus_CodeDataMode|=0x01;
						break;
					case A6_REGISTER_ADDRES4204://多圈数据
						ModBus_QuanData=(unsigned int)ModBus_Rec_Data[5]<<24;
						ModBus_QuanData+=(unsigned int)ModBus_Rec_Data[6]<<16;
						ModBus_QuanData+=(unsigned int)ModBus_Rec_Data[3]<<8;
						ModBus_QuanData+=(unsigned int)ModBus_Rec_Data[4];
						ModBus_CodeDataMode|=0x10;
						break;
					case A6_REGISTER_ADDRES4001://错误代码
						ModBus_ACErr=(unsigned int)ModBus_Rec_Data[3]<<8;
						ModBus_ACErr+=(unsigned int)ModBus_Rec_Data[4];
						break;
					}
					break;
		case A6_COMMAND_COIL_READ:
				switch(ModBus_CurAdder)
					{
					case 0x0102:
						ModBus_BackStatus=ModBus_Rec_Data[3];
					//	unsigned char ModBus_BackStatus,ModBus_ForwardStatus;
						break;
					case 0x0103:
						ModBus_ForwardStatus=ModBus_Rec_Data[3];
						if(Run_flag==1)
							{
							if((ModBus_BackStatus==0)&&(ModBus_ForwardStatus==0))
								{
								 // if(houtui==1)
									// {
									 // if(((CurrentSize>TargetSize+500-5))&&((CurrentSize<TargetSize+500+5)))
										// {
										 // Modbus_ACServoStop();
										 // ModBus_WaitRun_Flag=1;
										// }
									// }
								// else
									// {
									// if(((CurrentSize>TargetSize-5))&&((CurrentSize<TargetSize+5)))
										// {
										 // Modbus_ACServoStop();
										// }
									// }
								 }
							}
						break;	
					}
				break;
		}
	ModBus_CommEnd_Flag=0;
	ModBus_Queue_ChangeBuf();	//队列移位
	SendCmdOn_flag=0;	
	SendCmdWaitTime=0;
	ModBus_Comm_LinkErr=0;
	}
else		//------未接收到数据-----
	{
	if(SendCmdOn_flag==1)	//数据  已发出
		{
		SendCmdWaitTime++;
		if(SendCmdWaitTime>=500)	//数据返回超时 错误
			{
			SendCmdWaitTime=0;
			SendCmdOn_flag=0;
			ModBus_Comm_LinkErr=1;//通讯连接错误
			ModBus_QueueLoadCou=0;
			}
		}
	else
		{
		ReadErrorTime++;
		if(ReadErrorTime>=2000)//间隔  2000ms
			{
			ReadErrorTime=0;
			if(A6ReadCoderSizeWaitTime>=5000)//5s 后再保持连接
				ModBus_SendFrame(0x1,A6_COMMAND_REGISTER_READ,A6_REGISTER_ADDRES4001,1);//读错误代码
			}
		}
	}
if(A6ReadCoderSizeWaitTime<5000)//5s
	A6ReadCoderSizeWaitTime++;	
	
}


void ReadCurrentSize_A6Coder(void)//读取当前 编码器值
{
if(MotorType>=MOTOR_AC_A6_SERVO)
	{
	ModBus_SendFrame(0x1,A6_COMMAND_REGISTER_READ,A6_REGISTER_ADDRES4202,0x02);//编码器位置
	ModBus_SendFrame(0x1,A6_COMMAND_REGISTER_READ,A6_REGISTER_ADDRES4204,0x02);//多圈数据
	ModBus_CodeDataMode=0;
	ReadErrorTime=0;
	A6ReadCoderSizeWaitTime=0;
	}
}

void SaveA6OriginalBenchMark(void)//A6基准 保存
{
	Modbus_A6_JiZhunDesmion=ModBus_CurDesmion;
	Modbus_A6_JiZhunQuan=ModBus_QuanData;
	
	// Modbus_A6_SaveSetData();
	SaveA6MarkBenchSize();//A6 编码器 基准值(6 Byte)
	ModBus_AcErr_HisData[0]=0;
	Modbus_A6_SaveErrData();
}
