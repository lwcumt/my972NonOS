#include "App_Modbus_Motion_972.h"
#include "app_modbus_servo.h"

#include "app_modbus_plc.h"

#include "modbus_972.h"


#include "key.h"

#include "app_plc.h"

unsigned char Servo_Emergency_Switch_Status=0;  //伺服上的急停开关
unsigned char PLC_Emergency_Switch_Status=0;    //PLC上的急停开关
unsigned char PLC_MainPower_YOUT_Status=0; 	//PLC的主机电源开启Y输出
unsigned char PLC_MainPower_YOUT_Status_Temp=0xff;

unsigned char PLC_GuangDian_Switch_Status=0;//PLC光电开关的状态

unsigned char PLC_GuangDian_Switch_Status_Temp=0xff;

unsigned char StepRun_Flag=0;//步进运行标志位

unsigned char CutEnb_Flag=0; //允许裁位判断

unsigned char Modbus_Servo_RunEnb_Flag=0;//电机允许运行标志




unsigned char Modbus_Servo_Run_Dir_Flag=0;//0： 前进，1，后退

#include "process_main.h"

//后退 6mm后的再前进
void App_Modbus_Motion_Run_Next_972(Int32U target_size)
{
Modbus_Servo_RunEnb_Flag=0;																									
App_Modbus_Motion_Run_972(target_size);
Run_flag=1;
RunStop_flag=0;
InTargetPosit_flag=0;	//目标位置
OneCutRoutine_flag=0; // 清 裁切 循环标志
AutoCutStart_flag=0;
AirOffOK_flag=0;
PressUp_flag=0;
PressDown_flag=0;
}



void App_Modbus_Motion_Run_972(Int32U target_size)
{
	float tsize=(float)target_size/100;
	
	RLOUT1_ON;  RLOUT1_1_ON;  // 允许裁切继电器	//电机运行的时候，允许裁切要断开  电机停止时闭合
		#ifdef PLC_3U
	FX_Plc_EnbCut_Flag=1;
#endif
	CutEnb_Flag=0;
	if(PLC_Run_Mode==PLC_MODE_3U)//只有在PLC模式下才发送
		{
		App_Modbus_Plc_Write_M_Status(300,M_OFF);
		while(ModBus_QueueLoadCou!=0){};//等待前面序列的全部发送 

		}

	App_Modbus_Servo_Write_Y(SERVO_Y6,SERVO_CONTROL_OFF);//允许裁切 Y6 关
	while(ModBus_QueueLoadCou!=0){};//等待前面序列的全部发送 
		
		
	if(target_size>CurrentSize)
	{
		Modbus_Servo_Run_Dir_Flag=RUN_BACK;	
	}
	else
	{
	if(target_size<CurrentSize)
			{
			Modbus_Servo_Run_Dir_Flag=RUN_AHEAD;	

			}		
	else
			{
			Modbus_Servo_Run_Dir_Flag=RUN_STOP;				
			}		
	}
		
	
	if(StepRun_Flag!=0)
		{		
		App_Modebus_Servo_Run(300,tsize);	
		}
	else
		App_Modebus_Servo_Run(AC_MotorSPD,tsize);	
}




void App_Modbus_Motion_JogRun_972(Int32U spd,Int32U target_size)
{
float tsize=(float)target_size/100;
	RLOUT1_ON;  RLOUT1_1_ON;  // 允许裁切继电器	//电机运行的时候，允许裁切要断开  电机停止时闭合
	#ifdef PLC_3U
		FX_Plc_EnbCut_Flag=1;
	#endif
	CutEnb_Flag=0;
	if(PLC_Run_Mode==PLC_MODE_3U)//只有在PLC模式下才发送
		{
		App_Modbus_Plc_Write_M_Status(300,M_OFF);
		while(ModBus_QueueLoadCou!=0){};//等待前面序列的全部发送 

		}
App_Modbus_Servo_Write_Y(SERVO_Y6,SERVO_CONTROL_OFF);//允许裁切 Y6
		while(ModBus_QueueLoadCou!=0){};//等待前面序列的全部发送 
App_Modebus_Servo_Run(spd,tsize);
}



#include "pic_exec.h"
#include "timer.h"

#include "process_main.h"


unsigned char App_Manual_JogRun_Status=0;//1:前进 2：快进  3:后退  4：快退


void App_Manual_JogRun(unsigned char msta)
{
unsigned int m_speed=0;
App_Manual_JogRun_Status=msta;
switch(App_Manual_JogRun_Status)
		{	
		case AHEAD_JOGRUN_MODE:
			m_speed=(AC_MotorSPD*30)/100;
		if(	StepRun_Flag!=0)
			{
			StepRun_Flag=0;
				ACServoStop();	
			}
		
			if(Carrier_IN==0)  //托板 信号
					Size_MIN=FrontLimit;
				else
					Size_MIN=MiddleLimit;

			App_Modbus_Motion_JogRun_972(m_speed,Size_MIN);
			Run_flag=1;
					
			Modbus_Servo_Run_Dir_Flag=RUN_AHEAD;	
			break;
		case FAST_AHEAD_JOGRUN_MODE:
			m_speed=(AC_MotorSPD*70)/100;
			if(	StepRun_Flag!=0)
			{
			StepRun_Flag=0;
				ACServoStop();	
			}
			
				if(Carrier_IN==0)  //托板 信号
					Size_MIN=FrontLimit;
				else
					Size_MIN=MiddleLimit;
				
			App_Modbus_Motion_JogRun_972(m_speed,Size_MIN);
				Run_flag=1;
			Modbus_Servo_Run_Dir_Flag=RUN_AHEAD;	
			break;
		case BACK_JOGRUN_MODE:
			m_speed=(AC_MotorSPD*30)/100;
			if(	StepRun_Flag!=0)
			{
			StepRun_Flag=0;
				ACServoStop();	
			}
			App_Modbus_Motion_JogRun_972(m_speed,Size_MAX);
					Run_flag=1;
			Modbus_Servo_Run_Dir_Flag=RUN_BACK;	
			break;
		case FAST_BACK_JOGRUN_MODE:
			m_speed=(AC_MotorSPD*70)/100;
				if(	StepRun_Flag!=0)
			{
			StepRun_Flag=0;
				ACServoStop();	
			}
			App_Modbus_Motion_JogRun_972(m_speed,Size_MAX);
					Run_flag=1;
			Modbus_Servo_Run_Dir_Flag=RUN_BACK;	
			break;
		case 5:
		break;
		default:
			break;
		}
}




void App_Manual_JogRun_Check_Stop(void)
{
if(App_Manual_JogRun_Status>0)
		{
		if(Run_flag!=0)
			{
			App_Modbus_Servo_Stop(1);  //交流伺服	停止
			Run_flag=0;
			}
		App_Manual_JogRun_Status=0;		
		}
}
	
//按数字键停机
void App_PressNumKey_Stop(void)
{
	if(Run_flag!=0)
	{
			//		App_Modbus_Servo_Stop(1);  //交流伺服	停止
			Run_flag=0;
		


			StepRun_Flag=0;
				ACServoStop();	

			Modbus_Servo_Run_Dir_Flag=0;	

			App_Manual_JogRun_Status=0;
		}
	
}


void App_Servo_Check_CutEnb(void)//允许裁切判断
{
if(Run_flag==0)
	{
	if(CutEnb_Flag==0)
		{
		CutEnb_Flag=1;
		RLOUT1_OFF;  RLOUT1_1_OFF;  // 允许裁切继电器	//电机运行的时候，允许裁切要断开  电机停止时闭合
						#ifdef PLC_3U
							FX_Plc_EnbCut_Flag=0;
						#endif		
		if(PLC_Run_Mode==PLC_MODE_3U)//只有在PLC模式下才发送
				{
				App_Modbus_Plc_Write_M_Status(300,M_ON);
				while(ModBus_QueueLoadCou!=0){};//等待前面序列的全部发送 	

				}
		App_Modbus_Servo_Write_Y(SERVO_Y6,SERVO_CONTROL_ON);//允许裁切 Y6
		while(ModBus_QueueLoadCou!=0){};//等待前面序列的全部发送 	
		}
	}
else
	{
	RLOUT1_ON; RLOUT1_1_ON;  // 允许裁切继电器	//电机运行的时候，允许裁切要断开  电机停止时闭合
	#ifdef PLC_3U
		FX_Plc_EnbCut_Flag=1;
	#endif		
	}
}

unsigned char FX_Plc_EnbLiZhi_Temp_Flag=0xff;
unsigned char FX_Plc_EnbYaZhi_Temp_Flag=0xff;

//#include "app_fx_plc.h"


//运行循环
void App_Modbus_Motion_Loop_Run(void)
{
	
	App_Plc_M_Con_Process();
	
}


unsigned char YaZhi_M310_Sync_Flag=0;
unsigned char YaZhi_M310_Sync_Temp_Flag=0xff;


unsigned char ManualMode_M311_Flag=0;
unsigned char ManualMode_M311_Temp_Flag=0xff;



//#include "app_modbus_motion.h"

//M控制处理，用在实时判断上
void App_Plc_M_Con_Process(void)
{
//压纸标志控制 M304
if(FX_Plc_EnbYaZhi_Temp_Flag!=FX_Plc_EnbYaZhi_Flag)
	{
		FX_Plc_EnbYaZhi_Temp_Flag=FX_Plc_EnbYaZhi_Flag;
		if(FX_Plc_EnbYaZhi_Flag==0)
				{
				App_Modbus_Plc_Write_M_Status(304,M_OFF);	
				}
		else
				{
				App_Modbus_Plc_Write_M_Status(304,M_ON);						
				}		
	}
	
	
if(Modbus_Servo_Err_Flag!=0)
	{
	App_Modbus_Plc_Write_M_Status(303,M_ON);			
		
	}
else
{
	
//理纸标志 控制M303
if(FX_Plc_EnbLiZhi_Temp_Flag!=FX_Plc_EnbLiZhi_Flag)
	{
	FX_Plc_EnbLiZhi_Temp_Flag=FX_Plc_EnbLiZhi_Flag;
	if(PLC_Run_Mode==PLC_MODE_3U)//只有在PLC模式下才发送
		{
		if(FX_Plc_EnbLiZhi_Flag==0)
				{
				App_Modbus_Plc_Write_M_Status(303,M_OFF);	
				}
		else
				{
				App_Modbus_Plc_Write_M_Status(303,M_ON);						
				}
		}
	}	
	
}
	
	
if(YaZhi_M310_Sync_Temp_Flag!=YaZhi_M310_Sync_Flag)
		{	
		YaZhi_M310_Sync_Temp_Flag=YaZhi_M310_Sync_Flag;
		
		
			if(YaZhi_M310_Sync_Flag==0)
				{
				App_Modbus_Plc_Write_M_Status(310,M_OFF);	
				}
		else
				{
				App_Modbus_Plc_Write_M_Status(310,M_ON);						
				}				
		}
		

if((WorkMode==MANUAL_MODE)||(WorkMode==MANUAL_IO_MODE))
		{
		ManualMode_M311_Flag=1;	
		}
else
		{		
		ManualMode_M311_Flag=0;
		}
		
if(ManualMode_M311_Temp_Flag!=ManualMode_M311_Flag)
		{	
		ManualMode_M311_Temp_Flag=ManualMode_M311_Flag;
	  if(ManualMode_M311_Flag==0)
				{
				App_Modbus_Plc_Write_M_Status(311,M_OFF);	
				}
		else
				{
				App_Modbus_Plc_Write_M_Status(311,M_ON);						
				}				
		}		
		
		
//气阀
if(FX_Plc_EnbQiFa_Flag_Temp!=FX_Plc_EnbQiFa_Flag)
{
FX_Plc_EnbQiFa_Flag_Temp=FX_Plc_EnbQiFa_Flag;
if(FX_Plc_EnbQiFa_Flag==1)
		{			
		App_Modbus_Plc_Write_M_Status(302,M_ON);	
			//		App_Modbus_FXPlc_M_CTRL_Interrupt("ON",302);												
		}
else
	 {
		App_Modbus_Plc_Write_M_Status(302,M_OFF);	
		//	App_Modbus_FXPlc_M_CTRL_Interrupt("OFF",302);								
	 }
 }
}



//运行中检测限位等状态   限位或急停后，停止运行
void App_Motion_Runing_Check_Limit_Sensor(void)
{
if(Run_flag==0)
	return;

if(Modbus_Servo_Limit_Sensor_Status!=0)
		{
			
		if(Modbus_Servo_Limit_Sensor_Status==3)
			{//急停优先
			App_Modbus_Servo_Stop(1);  //交流伺服	停止
			Run_flag=0;
				
			App_Manual_JogRun_Status=0;		
			StepRun_Flag=0;					
				
			}
		else
			{					
			if(Modbus_Servo_Run_Dir_Flag==RUN_AHEAD)
				{//前进
				if(Modbus_Servo_Limit_Sensor_Status==2)
						{
						App_Modbus_Servo_Stop(1);  //交流伺服	停止
						Run_flag=0;
							
						App_Manual_JogRun_Status=0;		
						StepRun_Flag=0;		
						
						}
				}
				
		if(Modbus_Servo_Run_Dir_Flag==RUN_BACK)
				{//后退
				if(Modbus_Servo_Limit_Sensor_Status==1)
						{
						App_Modbus_Servo_Stop(1);  //交流伺服	停止
						Run_flag=0;
			
						App_Manual_JogRun_Status=0;		
						StepRun_Flag=0;								
						}								
				}
			}		
		}	
}




