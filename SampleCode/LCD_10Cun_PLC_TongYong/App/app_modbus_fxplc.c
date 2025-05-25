#include "app_modbus_fxplc.h"


#include "app_modbus_motion.h"

#include "app_modbus.h"

#include "drv_glcd.h"

#include "file.h"
#include "string.h"
#include "stdlib.h"
#include "stdio.h"

#include "modbus_972.h"

#include "timer.h"


#include "string.h"

#include "app_fx_plc.h"

#include "app_modbus_972.h"

#include "app_modbus_plc.h"


#include "app_modbus_servo.h"


unsigned char  Modbus_PLC_Link_Flag=0;


void App_Modbus_FXPlc_AutoCnt_Check(void)
{
	
if(FX_Plc_EnbAutoCut_Flag==1)
		{
			if(FX_Plc_EnbAutoCut_Send_Flag==0)
			{
				FX_Plc_EnbAutoCut_Send_Flag=1;
				
				
				if(PLC_Run_Mode==PLC_MODE_3U)//只有在PLC模式下才发送
						{																	
												//以下这段新15寸上 MODBUS servo +PLC
						if(FX_Plc_EnbAutoCut_Flag==0)
									{
									App_Modbus_Plc_Write_M_Status(301,M_ON);
											App_Modbus_Servo_Write_Y(SERVO_Y7,SERVO_CONTROL_ON);//自动裁切 Y7
									//	App_Modbus_FXPlc_M_CTRL("ON",301);
															
									}
						else
									{
									App_Modbus_Plc_Write_M_Status(301,M_OFF);
											App_Modbus_Servo_Write_Y(SERVO_Y7,SERVO_CONTROL_OFF);//自动裁切 Y7
									//	App_Modbus_FXPlc_M_CTRL("OFF",301);			
									}	
						//while(ModBus_QueueLoadCou!=0){};//等待前面序列的全部发送 
						}
				else
				{//伺服一直有
							if(FX_Plc_EnbAutoCut_Flag==0)
									{
							//		App_Modbus_Plc_Write_M_Status(301,M_ON);
											App_Modbus_Servo_Write_Y(SERVO_Y7,SERVO_CONTROL_ON);//自动裁切 Y7
									//	App_Modbus_FXPlc_M_CTRL("ON",301);
															
									}
						else
									{
							//		App_Modbus_Plc_Write_M_Status(301,M_OFF);
											App_Modbus_Servo_Write_Y(SERVO_Y7,SERVO_CONTROL_OFF);//自动裁切 Y7
									//	App_Modbus_FXPlc_M_CTRL("OFF",301);			
									}					
					
					
				}
			}					
		}
else
	FX_Plc_EnbAutoCut_Send_Flag=0;
	
	
}


//写M命令  中断中写，不要查询命令
void App_Modbus_FXPlc_M_CTRL_Interrupt(char *msta,unsigned int madd)
{
unsigned int target_madd=M_BASE_ADDD+madd;

if(strcmp(msta,"ON")==0)
			{
					
		//	while(App_Modbus_Task_Ready_Flag==0){};//如果是MODBUS发送状态，则等待
			ModBus_SendFrame(PLC_ADDER,MODBUS_PLC_BIT_WRITE_CMD,target_madd,0xff00);//读取4个字的数据
			ModBus_Queue_LoadBuf(Modbus_Sendbuf,'m',8);//写M命令
			}
	else
			{
				if(strcmp(msta,"OFF")==0)
				{						
			//	while(App_Modbus_Task_Ready_Flag==0){};//如果是MODBUS发送状态，则等待
				ModBus_SendFrame(PLC_ADDER,MODBUS_PLC_BIT_WRITE_CMD,target_madd,0);//读取4个字的数据
				ModBus_Queue_LoadBuf(Modbus_Sendbuf,'m',8);//写M命令
				}
			}	
}



//写M命令
void App_Modbus_FXPlc_M_CTRL(char *msta,unsigned int madd)
{
unsigned int target_madd=M_BASE_ADDD+madd;
	
	return;

if(strcmp(msta,"ON")==0)
			{
					
			while(App_Modbus_Task_Ready_Flag==0){};//如果是MODBUS发送状态，则等待
			ModBus_SendFrame(PLC_ADDER,MODBUS_PLC_BIT_WRITE_CMD,target_madd,0xff00);//读取4个字的数据
			ModBus_Queue_LoadBuf(Modbus_Sendbuf,'m',8);//写M命令
			}
	else
			{
				if(strcmp(msta,"OFF")==0)
				{						
				while(App_Modbus_Task_Ready_Flag==0){};//如果是MODBUS发送状态，则等待
				ModBus_SendFrame(PLC_ADDER,MODBUS_PLC_BIT_WRITE_CMD,target_madd,0);//读取4个字的数据
				ModBus_Queue_LoadBuf(Modbus_Sendbuf,'m',8);//写M命令
				}
			}	
}


//写D命令
void App_Modbus_FXPlc_D_Write(unsigned int dadd,unsigned int ddata)
{
	
//	while(App_Modbus_Task_Ready_Flag==0){};//如果是MODBUS发送状态，则等待
ModBus_SendFrame(PLC_ADDER,MODBUS_WRITE_CMD,dadd,ddata);//读取4个字的数据
ModBus_Queue_LoadBuf(Modbus_Sendbuf,'d',8);//写M命令	
	
}




int Modbus_PlcTimeOut=0;

//通读超时检测
void App_Modbus_PLC_TimeOut(void)
{
if(Modbus_PLC_Link_Flag==1)
			{
				Modbus_PlcTimeOut++;
				if(Modbus_PlcTimeOut>=600)
					{//
					Modbus_PlcTimeOut=0;
					Modbus_PLC_Link_Flag=0;
					}				
			}
else
			{				
				Modbus_PlcTimeOut=0;				
			}	
}

