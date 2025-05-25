#include "App_Modbus_Servo.h"



#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "app_plc.h"
//#include "app_modbus.h"


#ifdef N972_MODBUS_SERVO


#include "modbus_972.h"


#include "modbus_972.h"
//#include "modbus.h"
#include "uart_config.h"

#include "pic_exec.h"

//#include "app_modbus.h"

#include "string.h"

//#include "app_modbus_motion.h"

//#include "app_fx_plc.h"
//#include "app_modbus_fxplc.h"


#include "app_modbus_972.h"
#include "modbus_972.h"


#include "key.h"


#else


#include "../Serial/Serial.h"

#include "../main.h"

#include "../gpio_config.h"


#include "../modbus/modbus.h"
#include "../modbus/uart_modbus.h"



#include "App_Modbus.h"


#endif





unsigned char Modbus_Servo_X_Status[2][8];


unsigned char Servo_Send_Enb_Flag=1;


unsigned short Modbus_Servo_Small_Gear=30;
unsigned short Modbus_Servo_Big_Gear=60;
unsigned short Modbus_Servo_DaoChen=12;

unsigned char Modbus_Servo_Limit_Sensor_Status=0;


unsigned char Modebus_Servo_RUN_DIR_Set_Flag=0;//0:正转 1：反转
int Modbus_Servo_Vision=0;


//初始化  新版本 202308
void App_Modebus_Servo_Init(void)
{


App_Load_Modbus_Servo_CFG();

}


//保存螺距导程  新版本
void App_Save_Modbus_Servo_CFG(void)
{
unsigned char *pdtr;
pdtr=(unsigned char *)DOWNFILE_SDRAM_ADD;
	
iFiles.FileLength=7;

*pdtr++=Modbus_Servo_Small_Gear>>8;
*pdtr++=Modbus_Servo_Small_Gear;
*pdtr++=Modbus_Servo_Big_Gear>>8;
*pdtr++=Modbus_Servo_Big_Gear;
*pdtr++=Modbus_Servo_DaoChen>>8;
*pdtr++=Modbus_Servo_DaoChen;
*pdtr++=Modebus_Servo_RUN_DIR_Set_Flag;

//memcpy((unsigned char *)DOWNFILE_SDRAM_ADD,&Modbus_Motion_Parameter,iFiles.FileLength);

ChangeFileName((unsigned char*)"Modbus_Servo.cfg");	//NandEccWrite_Flag=0;
File_Create((char*)iFiles.FileName);//建立文件
	
	
}




//调入螺距导程
void App_Load_Modbus_Servo_CFG(void)
{	
	
unsigned char *pdtr;
	pdtr=(unsigned char *)DOWNFILE_SDRAM_ADD;
	
FileRead("Modbus_Servo.cfg",(unsigned char *)DOWNFILE_SDRAM_ADD);
	
Modbus_Servo_Small_Gear=*pdtr++;//=Modbus_Servo_Small_Gear>>8;
	Modbus_Servo_Small_Gear<<=8;
Modbus_Servo_Small_Gear+=*pdtr++;
	
Modbus_Servo_Big_Gear=*pdtr++;//=Modbus_Servo_Big_Gear>>8;
	Modbus_Servo_Big_Gear<<=8;
Modbus_Servo_Big_Gear+=*pdtr++;
	
Modbus_Servo_DaoChen=*pdtr++;//=Modbus_Servo_DaoChen>>8;
Modbus_Servo_DaoChen<<=8;
Modbus_Servo_DaoChen+=*pdtr++;
	
Modebus_Servo_RUN_DIR_Set_Flag=*pdtr++;
	
if((Modbus_Servo_Small_Gear==0)||(Modbus_Servo_Small_Gear>999)||(Modbus_Servo_Big_Gear==0)||(Modbus_Servo_Big_Gear>999)||(Modbus_Servo_DaoChen==0)||(Modbus_Servo_DaoChen>50)||(Modebus_Servo_RUN_DIR_Set_Flag>1))
		{
		Modbus_Servo_Small_Gear=30;
		Modbus_Servo_Big_Gear=60;	
		Modbus_Servo_DaoChen=12;
		Modebus_Servo_RUN_DIR_Set_Flag=0;//正转
		App_Save_Modbus_Servo_CFG();//预保存
		}			
}




//伺服驱动解码
void App_Modbus_Servo_Decode(void)
{
	
char strtemp[64];
	unsigned char btemp=0;
	int i;
//int idx=0;
//int high_low_byte=1;
//int i;
//unsigned char * pdn;
//unsigned char * ypdn;
//unsigned char temp;
//unsigned char testbytecnt=0;
//float cur_position;
//Modubs_Cmd_Type=ModBus_CurCommand;
ModBus_Queue_ChangeBuf();//收到返回后，清除缓冲区
Modbus_Queue_Clear_SendStatus();//接收到后，清除发送状态

Modbus_Servo_Link_Flag=1;//Modbus 伺服已连接
Modbus_ServoTimeOut=0;
	
	
switch(Modubs_Cmd_Type)
	{
	case SERVO_READ_X:
		
	 btemp=ModBus_DataBuf[0];
		
		for(i=0;i<8;i++)
					{
					if(btemp&0x01)
							{
								Modbus_Servo_X_Status[0][i]='1';
							}
					else
						Modbus_Servo_X_Status[0][i]='0';	
					btemp>>=1;					
					}
			
					
			btemp=ModBus_DataBuf[1];
			for(i=0;i<8;i++)
					{
					if(btemp&0x01)
							{
								Modbus_Servo_X_Status[1][i]='1';
							}
					else
						Modbus_Servo_X_Status[1][i]='0';	
					btemp>>=1;					
					}	
	//	sysprintf("ModBus_DataBuf[0]= %x \r\n ",ModBus_DataBuf[0]);

		//printf("ModBus_DataBuf[0]= %x \r\n ",ModBus_DataBuf[0]);
		////printf("PLC X Status is Read...\r\n");//,sendcnt,frecvcnt);// recv count = %d \r\n",recvcnt);//...\r\n"); 
	
	//	PLC_X_READ_OK_Flag=0;
	
		//pdn=(unsigned char *)PLC_X_Status;

	//	//printf("X pdn = %d \r\n ",pdn);


	/*
		high_low_byte=1;
		for(idx=0;idx<4;idx++)
			{
			for(high_low_byte=1;high_low_byte>=0;high_low_byte--)
				{
				temp=ModBus_DataBuf[idx*2+high_low_byte];
				for(i=0;i<8;i++)
					{
					if(temp&0x01)
						*pdn++=1;
					else
						*pdn++=0;
					temp>>=1;
					}
				}
			}
*/


		Modubs_Cmd_Type=0;
		break;

	case SERVO_READ_Y:

/*
		pdn=(unsigned char *)PLC_Y_Status;
		high_low_byte=1;

		for(idx=0;idx<4;idx++)
			{
			for(high_low_byte=1;high_low_byte>=0;high_low_byte--)
				{
				temp=ModBus_DataBuf[idx*2+high_low_byte];


				for(i=0;i<8;i++)
					{
					if(temp&0x01)
						*pdn++=1;
					else
						*pdn++=0;

					temp>>=1;
					}
				}
			}
	*/
		Modubs_Cmd_Type=0;

		break;


	case MCT_SERVO_READ_CUR_POSITION://读取当前位置
		//Servo_Cur_Position=*f_pdn;//(float)ModBus_DataBuf;
	//	//printf("ModBus_DataBuf[0]= %x \r\n",ModBus_DataBuf[0]);
	//			//printf("ModBus_DataBuf[1]= %x \r\n",ModBus_DataBuf[1]);
	//					//printf("ModBus_DataBuf[2]= %x \r\n",ModBus_DataBuf[2]);
	//							//printf("ModBus_DataBuf[3]= %x \r\n",ModBus_DataBuf[3]);

	//memcpy(&cur_position,ModBus_DataBuf,4);
	//	Servo_Cur_Position=cur_position;


	FAB.union_byte[0]=ModBus_DataBuf[1];
	FAB.union_byte[1]=ModBus_DataBuf[0];
	FAB.union_byte[2]=ModBus_DataBuf[3];
	FAB.union_byte[3]=ModBus_DataBuf[2];

	//	FAB.union_float =100.00;// cur_position;

	//			//printf("cur_position[0]= %x \r\n",FAB.union_byte[0]);
	//			//printf("cur_position[1]= %x \r\n",FAB.union_byte[1]);
	//					//printf("cur_position[2]= %x \r\n",FAB.union_byte[2]);
	//							//printf("cur_position[3]= %x \r\n",FAB.union_byte[3]);

		//printf("Servo_Cur_Position= %0.2f \r\n",FAB.union_float);
		Servo_Cur_Position=FAB.union_float;
		
		
		
	//	sprintf(strtemp,"Servo_Cur_Position= %0.2f \r\n",FAB.union_float);
		sysprintf(strtemp);//"Servo_Cur_Position= %0.2f \r\n",FAB.union_float);
	//	if(Servo_Cur_Position>3000)
		//	Servo_Cur_Position=3000;

		Modubs_Cmd_Type=0;
		break;
		
	case MCT_SERVO_ALARM_READ://读故障代码
		
		App_Modbus_Servo_Status=(unsigned char )ModBus_DataBuf[0];
		App_Modbus_Servo_Status<<=8;
		App_Modbus_Servo_Status+=(unsigned char )ModBus_DataBuf[1];
					
		if(App_Modbus_Servo_Status>0)
				Modbus_Servo_Err_Flag=1;
		else
				Modbus_Servo_Err_Flag=0;
		break;
		
	case MCT_SERVO_READ_VISION:
		Modbus_Servo_Vision=(unsigned char )ModBus_DataBuf[0];
		Modbus_Servo_Vision<<=8;
		Modbus_Servo_Vision+=(unsigned char )ModBus_DataBuf[1];	
	
	  //sprintf(strtemp,"%d",Modbus_Servo_Vision);
		
		break;
	}
}




//读取当前位置
void App_Modebus_Servo_Read_Cur_Position(void)
{


ModBus_Queue_Insert(MCT_SERVO_READ_CUR_POSITION,SERVO_ADDER,MODBUS_READ_CMD,0x1064,0x02);//

//ModBus_SendFrame(SERVO_ADDER,MODBUS_READ_CMD,0x1064,0x02);//读取4个字的数据	
//Uart_Modbus_Comm_Send(Modbus_Sendbuf,8);


}




unsigned char Modbus_Servo_Set_Config_Flag=0;//配置大小齿轮比和导程
//设置配置参数   小齿轮，大齿轮，导程
void App_Modbus_Servo_Set_Config(void)
{

if(Modbus_Servo_Set_Config_Flag!=0)
	return;
Modbus_Servo_Set_Config_Flag=1;
	
FAB.union_float=(float)Modbus_Servo_DaoChen;//转一圈距离
ModBus_Queue_Insert(MCT_ERVO_SET_CONFIG,SERVO_ADDER,0x10,0x121C,FAB.union_uint);//

FAB.union_float=(float)Modbus_Servo_Small_Gear;//小齿轮
ModBus_Queue_Insert(MCT_ERVO_SET_CONFIG,SERVO_ADDER,0x10,0x1220,FAB.union_uint);//

FAB.union_float=(float)Modbus_Servo_Big_Gear;//大齿轮
ModBus_Queue_Insert(MCT_ERVO_SET_CONFIG,SERVO_ADDER,0x10,0x121E,FAB.union_uint);//	

FAB.union_float=(float)Modbus_Servo_DaoChen*100.0f;//转一圈脉冲数
ModBus_Queue_Insert(MCT_ERVO_SET_CONFIG,SERVO_ADDER,0x10,0x1222,FAB.union_uint);//
	
}


//校基准
unsigned char Modbus_Servo_Calibration_Flag=0;
unsigned int Modbus_Servo_Calibration_RumTime=0;

#include "timer.h"


int calibration_demension=0;
unsigned char calibration_cnt=0;
	
unsigned char App_Modbus_Servo_Calibration(int cal_dimension)
{
int targetdimension=0;

int calibration_mstime=0;	

char ctemp[16];
	 calibration_demension=cal_dimension;//暂存，防止局部变量数据被修改
//sysprintf("cal_dimension =%d   \r\n",cal_dimension);
while(1)
	{
		cal_dimension=calibration_demension;//回读 防止局部变量数据被修改
		Modbus_Servo_Calibration_Flag=1;
		Modbus_Servo_Calibration_RumTime=0;
		App_Modebus_Servo_Set_Start_Position((float)cal_dimension/100);
		while(Modbus_Servo_Calibration_Flag==1){};//等特校准完毕
	
		calibration_mstime=0;
			Ms_Flag=0;
		while(1)//延时500MS，确保读到返回值
		{
		if(Ms_Flag!=0)
			{
			Ms_Flag=0;
			calibration_mstime++;
			if(calibration_mstime>=500)
				{
					calibration_mstime=0;
					break;					
				}		
			}			
		}
		
//	sysprintf("cal_dimension =%d   ",cal_dimension);
		
	targetdimension=Servo_Cur_Position*100;		
//	sprintf(ctemp,"\r\nServo_Cur_Position= %0.2f \r\n",Servo_Cur_Position);	
//	sysprintf(ctemp);//
//////	sysprintf("cal_dimension =%d   ",calibration_demension);
//////	sysprintf("targetdimension =%d\r\n",targetdimension);

		
	if((targetdimension>=calibration_demension-1)&&(targetdimension<=calibration_demension+1))
			{
			App_Modbus_Get_CurrentSize();//更新显示一下最新数据
		//	sysprintf("cal_dimension =%d   ",calibration_demension);
		//	sysprintf("targetdimension =%d\r\n\r\n",targetdimension);
			break;		
			}			
	calibration_cnt++;
			
//	sysprintf("calibration_cnt =%d  \r\n ",calibration_cnt+1);
	if(calibration_cnt>=5)//校了5次，退出，不对就不对了。
				break;
	}
	
}


//设定起点位置
//发送起点位置后，再发送置零点命令
void App_Modebus_Servo_Set_Start_Position(float start_position)
{
//unsigned char tbuf[4];
	
char ctemp[16];

FAB.union_float=start_position;//浮点转UINT
	
//sprintf(ctemp,"start_position= %0.2f \r\n",start_position);
	
//sysprintf(ctemp);//
//sysprintf("start_position= %0.2f \r\n",start_position);

Servo_Send_Enb_Flag=0;

//装载起点位置
ModBus_Queue_Insert(MCT_SERVO_SET_START_POSITION,SERVO_ADDER,0x10,0x1232,FAB.union_uint);//

//ModBus_SendFrame(SERVO_ADDER,0x10,0x1232,FAB.union_uint);//读取4个字的数据	
//Uart_Modbus_Comm_Send(Modbus_Sendbuf,13);

//装载置零位
ModBus_Queue_Insert(MCT_SERVO_SET_ZERO_CONTROL,SERVO_ADDER,0x05,0x0807,SERVO_CONTROL_ON);//


//ModBus_SendFrame(SERVO_ADDER,0x05,0x0807,SERVO_CONTROL_ON); //置零位	
//Uart_Modbus_Comm_Send(Modbus_Sendbuf,8);

}


int Modbus_Servo_Err_Cnt=0;
int Modbus_Servo_Send_Cnt=0;

//运行到目标位置
//发送目标位置后，再发送定位命令
void App_Modebus_Servo_Run(float speed,float target)
{
	
	//App_Modbus_Servo_Stop(1);//先停止一下
	

//装载SPEED
App_Modebus_Servo_Set_Speed(speed);//

Modbus_Servo_Send_Cnt++;
FAB.union_float=target;//浮点转UINT

//装载目标位置
ModBus_Queue_Insert(MCT_SERVO_RUN_TO_TARGET_POSITION,SERVO_ADDER,0x10,0x1208,FAB.union_uint);//
//ModBus_SendFrame(SERVO_ADDER,0x10,0x1208,FAB.union_uint);//读取4个字的数据	
//Uart_Modbus_Comm_Send(Modbus_Sendbuf,13);

//允许转动
ModBus_Queue_Insert(MCT_SERVO_BACK_RUN_CONTROL,SERVO_ADDER,0x05,0x0808,SERVO_CONTROL_OFF);//

//装载 定位
ModBus_Queue_Insert(MCT_SERVO_SET_ZERO_CONTROL,SERVO_ADDER,0x05,0x0800,SERVO_CONTROL_ON);//

//ModBus_SendFrame(SERVO_ADDER,0x05,0x0800,SERVO_CONTROL_ON);//定位	
//Uart_Modbus_Comm_Send(Modbus_Sendbuf,8);
}


//设定运行速度
void App_Modebus_Servo_Set_Speed(float speed)
{

FAB.union_float=speed;//浮点转UINT

ModBus_Queue_Insert(MCT_SERVO_RUN_TO_TARGET_POSITION,SERVO_ADDER,0x10,0x11FC,FAB.union_uint);//

//ModBus_SendFrame(SERVO_ADDER,0x05,0x11FC,FAB.union_uint);//设定转速度
//Uart_Modbus_Comm_Send(Modbus_Sendbuf,8);


}



unsigned char App_ModeBus_Servo_Set_HandWheel_Flag=1;

//设定手轮倍率  
void App_Modbus_Servo_Set_HandWheel(unsigned short handwheel_x)
{
if(App_ModeBus_Servo_Set_HandWheel_Flag!=0)
	return;

App_ModeBus_Servo_Set_HandWheel_Flag=1;

ModBus_Queue_Insert(MCT_SERVO_RUN_TO_TARGET_POSITION,SERVO_ADDER,0x10,0x11FE,handwheel_x);//
}


unsigned char App_Modbus_Servo_Set_AddSubTime_Flag=1;
//设定加减速时间
void App_Modbus_Servo_Set_AddSubTime(void)
{
	
if(App_Modbus_Servo_Set_AddSubTime_Flag!=0)
	return;

App_Modbus_Servo_Set_AddSubTime_Flag=1;

App_Modbus_Servo_Set_Speed_AddTime(App_ModBus_DecTime);
App_Modbus_Servo_Set_Speed_SubTime(App_ModBus_DecTime);
	
}




//设定电机运行方向
void App_Modbus_Servo_ReadVision(void)
{
ModBus_Queue_Insert(MCT_SERVO_READ_VISION,SERVO_ADDER,0x03,1196,0x01);//
//ModBus_Queue_Insert(MCT_SERVO_SET_ZERO_CONTROL,SERVO_ADDER,0x05,,SERVO_CONTROL_ON);//

}


unsigned char Modebus_Servo_RUN_DIR_Set_Flag_Temp=0xFF;

//设定电机运行方向
void App_Modbus_Servo_MotorRunDir_Set(void)
{
	
if(Modebus_Servo_RUN_DIR_Set_Flag==Modebus_Servo_RUN_DIR_Set_Flag_Temp)
	return;

Modebus_Servo_RUN_DIR_Set_Flag_Temp=Modebus_Servo_RUN_DIR_Set_Flag;

		
if(Modebus_Servo_RUN_DIR_Set_Flag==0)
	ModBus_Queue_Insert(MCT_SERVO_SET_ZERO_CONTROL,SERVO_ADDER,0x05,0x0A01,SERVO_CONTROL_OFF);//
else
	ModBus_Queue_Insert(MCT_SERVO_SET_ZERO_CONTROL,SERVO_ADDER,0x05,0x0A01,SERVO_CONTROL_ON);//
}


//设定 加速时间
void App_Modbus_Servo_Set_Speed_AddTime(unsigned short speed_addtime)
{
ModBus_Queue_Insert(MCT_SERVO_RUN_TO_TARGET_POSITION,SERVO_ADDER,0x10,0x120A,speed_addtime);//

}



//设定减速时间
void App_Modbus_Servo_Set_Speed_SubTime(unsigned short speed_subtime)
{
ModBus_Queue_Insert(MCT_SERVO_RUN_TO_TARGET_POSITION,SERVO_ADDER,0x10,0x120C,speed_subtime);//


}

//正转 启或停
void App_Modbus_Servo_Ahead_RunAndStop(float speed,unsigned short control_bits)
{
//装载SPEED
App_Modebus_Servo_Set_Speed(speed);//
//装载 正转 启停
ModBus_Queue_Insert(MCT_SERVO_AHEAD_RUN_CONTROL,SERVO_ADDER,0x05,0x0802,control_bits);//

//ModBus_SendFrame(SERVO_ADDER,05,0x0801,control_bits);//读取4个字的数据	
//Uart_Modbus_Comm_Send(Modbus_Sendbuf,8);


}



//反转 启或停
void App_Modbus_Servo_Back_RunAndStop(float speed,unsigned short control_bits)
{

//装载SPEED
App_Modebus_Servo_Set_Speed(speed);//
//装载 反转 启停
ModBus_Queue_Insert(MCT_SERVO_BACK_RUN_CONTROL,SERVO_ADDER,0x05,0x0801,control_bits);//

}



//停止 启或停
void App_Modbus_Servo_Stop(unsigned short control_bits)
{
//装载 停止
ModBus_Queue_Insert(MCT_SERVO_BACK_RUN_CONTROL,SERVO_ADDER,0x05,0x0808,SERVO_CONTROL_ON);//

//装载 取消定位
ModBus_Queue_Insert(MCT_SERVO_BACK_RUN_CONTROL,SERVO_ADDER,0x05,0x0800,SERVO_CONTROL_OFF);//
//装载 允许转动
ModBus_Queue_Insert(MCT_SERVO_BACK_RUN_CONTROL,SERVO_ADDER,0x05,0x0808,SERVO_CONTROL_OFF);//
}


//置零点
void App_Modbus_Servo_Set_ZeroPosition(void)
{

//装载置零位
ModBus_Queue_Insert(MCT_SERVO_SET_ZERO_CONTROL,SERVO_ADDER,0x05,0x0807,SERVO_CONTROL_ON);//

//ModBus_SendFrame(SERVO_ADDER,05,0x0807,0xFF00);//读取4个字的数据	
//Uart_Modbus_Comm_Send(Modbus_Sendbuf,8);
}



//读故障代码
void App_Modbus_Servo_Alarm_Read(void)
{
//装载 读故障代码
ModBus_Queue_Insert(MCT_SERVO_ALARM_READ,SERVO_ADDER,0x03,0x106A,0x01);//


}


//清故障代码
void App_Modbus_Servo_Alarm_Clear(void)
{

//装载 报警清除
ModBus_Queue_Insert(MCT_SERVO_ALARM_CLEAR,SERVO_ADDER,0x05,0x0809,SERVO_CONTROL_ON);//

}




//读X状态
void App_Modbus_Servo_Read_X(void)
{
ModBus_Queue_Insert(SERVO_READ_X,SERVO_ADDER,0x02,0x400,16);//	
	
}



void  App_Modbus_Servo_Read_1406(void)
{
//	01 03 14 06 00 02 21 FA
ModBus_Queue_Insert(SERVO_READ_1406,SERVO_ADDER,0x03,0x1406,1);//		
	
}



//写Y状态

//例子：发送：01 05 05 06 FF 00 6C F7 接收：01 05 05 06 FF 00 6C F7
//功能：置位 Y6


void App_Modbus_Servo_Write_Y(unsigned short ynum,unsigned short ysta)
{
//return;
ModBus_Queue_Insert(MCT_SERVO_WRITE_Y,SERVO_ADDER,0x05,ynum,ysta);//		
}



//读Y状态
void App_Modbus_Servo_Read_Y(void)
{
	
	
	
	
	
}



//判断伺服是否停止 运行状态下 如当前值，过1秒后。不变，则发送停止


unsigned int CheckStopTime=0;


int	CheckStop_Size;//=CurrentSize;


#include "App_Modbus_Motion_972.h"


void App_Modbus_Servo_CheckStop(void)
{
	
if(Run_flag==0)
	{
	
	CheckStopTime=0;
	CheckStop_Size=CurrentSize;

	return;
	
	}

	
	CheckStopTime++;
	if(CheckStopTime>=500)
	{
		CheckStopTime=0;
		
		if(CheckStop_Size!=CurrentSize)
			{
			CheckStop_Size=CurrentSize;
				
			}
	else
			{
			App_Modbus_Servo_Stop(1);  //交流伺服	停止
			Run_flag=0;
				
			App_Manual_JogRun_Status=0;		
			StepRun_Flag=0;			
				
			}
	}	
}


