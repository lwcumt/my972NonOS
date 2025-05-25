#include "app_modbus_test.h"

#include "app_plc.h"

#include "app_modbus_972.h"

#include "app_modbus_plc.h"

#include "timer.h"

#include <stdio.h>
#include <string.h>

#include "nuc970.h"
#include "sys.h"


#include "modbus_972.h"




void App_Modbus_Test_Init(void)
{





}




void App_Modbus_Test_Run(void)
{	
App_Modbus_Plc_Init();
	
//App_Modbus_Get_CurrentSize();
	
	return;
sysprintf("App_Modbus_Test_Run\r\n");
while(1)
	{
	if(Ms_Flag!=0)
		{
			Ms_Flag=0;		
			App_Modbus_Test_Task();//运行任务
		}
	}
}

int taskTime=0;
unsigned char TaskStep=0;

unsigned char Servo_Run_Step=0;


#include "app_modbus_servo.h"

#include "pic_exec.h"

//#include "app_modbus_motion.h"

unsigned char  App_ModBus_Test_TaskTime=0;

void  App_Modbus_Test_Task(void)
{
	
		unsigned short tempdat=0;
	/*
App_ModBus_Test_TaskTime++;
if(App_ModBus_Test_TaskTime<1)
	return;

	*/

App_ModBus_Test_TaskTime=0;

ModBus_Queue_SendFrame();//队列发送
	
	
#ifdef MODBUS_SERVO_ENB
	if(Modbus_Servo_Calibration_Flag!=0)
			{//校基准，1S内不发送其它命令
			Modbus_Servo_Calibration_RumTime++;
			if(Modbus_Servo_Calibration_RumTime>=1500)
				{				
				Modbus_Servo_Calibration_RumTime=0;
				Modbus_Servo_Calibration_Flag=0;
				}
			else
				{			
				taskTime=0;
				TaskStep=0;
				return;			
				}
			}
	else
		{
		Modbus_Servo_Calibration_RumTime=0;	
		}

	App_Modbus_Servo_TimeOut();//伺服通讯超时检测
#endif


App_Modbus_PLC_TimeOut();//PLC通讯超时检测
	

App_Sensor_Get_Status();//读取状态

taskTime++;
if(taskTime<18)//20ms 一个发送周期

//	if(taskTime<100)
		return;

//PLC_Run_Mode=PLC_MODE_NONE;//暂时禁止PLC

taskTime=0;
TaskStep++;
switch(TaskStep)
	{
	case 1:

	if((PLC_Run_Mode==PLC_MODE_NONE)||(PLC_Run_Mode==PLC_MODE_SERVO))//无PLC或SERVO不入
		{

		}
	else
		{
////////			if(BackUpTime_Enable!=(int)PSW_Lock_Disp_Flag)
////////				{
////////				BackUpTime_Enable=(int)PSW_Lock_Disp_Flag;

////////				if(PSW_Lock_Disp_Flag==0)
////////					App_Modbus_Plc_Write_M_Status(258,M_OFF);
////////				else
////////					App_Modbus_Plc_Write_M_Status(258,M_ON);

////////				}

////////			if(BackUpTime_Data!=(int)Knife_ChangeTime)
////////				{
////////				BackUpTime_Data=(int)Knife_ChangeTime;

////////				App_Modbus_Plc_Write_D_Data(258,Knife_ChangeTime);

////////				}
		}

	
		break;
	case 2:
		#ifdef MODBUS_SERVO_ENB

			#ifdef NACHUAN_SERVO
				App_Modbus_Servo_Set_AddSubTime();//发送伺服加减时间  上电和改变数据时清发送标志位重发 
				App_Modbus_Servo_Set_HandWheel(Wheel_Step);//设定手轮
			#else
			App_Modbus_Servo_MotorRunDir_Set();//设置下电机方向
			App_Modbus_Servo_Set_AddSubTime();//发送伺服加减时间  上电和改变数据时清发送标志位重发 
			App_Modbus_Servo_Set_HandWheel(Wheel_Step);//设定手轮

			#endif
		#endif
	
	
	if((PLC_Run_Mode==PLC_MODE_NONE)||(PLC_Run_Mode==PLC_MODE_SERVO))//无PLC或SERVO不入
		{

		}
	else
		{
	if(WorkMode==MANUAL_MODE)
				{
					if(Run_flag==1)
					{
						App_Modbus_Plc_Write_M_Status(300,M_OFF);	
				
					}
				else
					{
						App_Modbus_Plc_Write_M_Status(300,M_ON);	

					}					
				}
				else
				{
				if(FX_Plc_EnbCut_Flag==0)
					{
						App_Modbus_Plc_Write_M_Status(300,M_ON);	

				
					}
				else
					{
						App_Modbus_Plc_Write_M_Status(300,M_OFF);	
							
								
					}
				}
				
				
				
			
				
			if(FX_Plc_EnbAutoCut_Flag==0)
				{
					App_Modbus_Plc_Write_M_Status(301,M_ON);	
							
				}
			else
				{
					App_Modbus_Plc_Write_M_Status(301,M_OFF);	
			
							
				}	
			if(FX_Plc_EnbQiFa_Flag!=0)
					{
						App_Modbus_Plc_Write_M_Status(302,M_ON);	
						
					}
				else
					{
						App_Modbus_Plc_Write_M_Status(302,M_OFF);	
						
									
					}
					
					if((YaZhiMotorRun_Flag==1)||(WorkMode!=AUTO_MODE))
					{
						App_Modbus_Plc_Write_M_Status(303,M_OFF);	
						App_Modbus_Plc_Write_M_Status(304,M_OFF);	
						FX_Plc_EnbLiZhi_Flag=0;
						FX_Plc_EnbYaZhi_Flag=0;
					}
					else
					{
						if(FX_Plc_EnbLiZhi_Flag==0)
							{
								App_Modbus_Plc_Write_M_Status(303,M_OFF);	
																	
							}
						else
							{
								if(Run_flag==1)
								{
									App_Modbus_Plc_Write_M_Status(303,M_OFF);	

								}
								else
								{									
									App_Modbus_Plc_Write_M_Status(303,M_ON);	
									
								}
										
							}


				if(FX_Plc_EnbYaZhi_Flag==0)
						{
						App_Modbus_Plc_Write_M_Status(304,M_OFF);	
						}
				else
						{
								if(Run_flag==1)
								{
									App_Modbus_Plc_Write_M_Status(304,M_OFF);	

								}
								else
								{									
									App_Modbus_Plc_Write_M_Status(304,M_ON);	
																
					
								}	
								//	App_Modbus_Plc_Write_M_Status(304,M_ON);		
						}
					}
					
					//此版本 不需要优化裁切  2025 03 
////////				if(OptimizeCut_Enb_Flag==0)
////////					{
////////						App_Modbus_Plc_Write_M_Status(210,M_ON);	
////////					//	App_Modbus_FXPlc_M_CTRL_Interrupt("ON",M210);		
////////					//App_FX_Plc_Force_Process("ON",M210);								
////////							
////////					}
////////				else
////////					{
////////						App_Modbus_Plc_Write_M_Status(210,M_OFF);	
////////				//	App_Modbus_FXPlc_M_CTRL_Interrupt("OFF",M210);
////////				//		App_FX_Plc_Force_Process("OFF",M210);
////////					
////////					}
					
				if(FastCut_Enb_Flag==0)
					{
						App_Modbus_Plc_Write_M_Status(230,M_ON);	
						
						
					}
				else
					{
						App_Modbus_Plc_Write_M_Status(230,M_OFF);	
					
					}	
		}			
		break;
	case 3:
	//	App_Modbus_Plc_Read_Y_Status(0,32);//读取32路  2N 的读取12路  3U的读取32路 4组X
	
		#ifdef MODBUS_SERVO_ENB

			#ifdef NACHUAN_SERVO
				#ifdef NC_SERVO_WITH_PLC_CONTROL
				App_Modbus_Plc_Read_M_Status(404);
				#else
				App_Modbus_NC_Servo_Read_RunStatus();
				#endif
			#else
				App_Modbus_Servo_Read_X();
			#endif
		#endif
	
	
			if(PLC_PowerOn_Init_Flag==1)
				{//		D20下刀时间			
					
				tempdat=KnifeDownTime*10;
					
						App_Modbus_Plc_Write_D_Data(20,tempdat);
					//写D
	//			Comm_FX_Plc_Write_D_Area(20,(unsigned char*)&tempdat,2);		
			//	Optimize_Cut_DelayTime_DownLoad_Flag=1;//发送一次优化裁切延时时间					
				PLC_PowerOn_Init_Flag=0;					
				}
				
		break;
	case 4:
		#ifdef MODBUS_SERVO_ENB	
			#ifdef NACHUAN_SERVO

				App_Modbus_Plc_Read_D_Data(D62_ADD,6);//读D62 _ D64 对应的M300等，映射到D62
				//App_Modbus_Plc_Read_D_Data(40,2);//读手轮
			#else
				App_Modbus_Servo_Read_Y();

				#endif		
		#endif
	
		break;
	case 5:

		
	if((PLC_Run_Mode==PLC_MODE_NONE)||(PLC_Run_Mode==PLC_MODE_SERVO))//无PLC或SERVO不入
	{
	}
	else
	{
	//	App_Modbus_Plc_Write_D20_DownCutTime();		//D20 下刀时间发送,   清0 可以重复发送
	//	App_Modbus_Plc_Write_M280_FastCutMode();
	}
		break;
	case 6:
		if((PLC_Run_Mode==PLC_MODE_NONE)||(PLC_Run_Mode==PLC_MODE_SERVO))//无PLC或SERVO不入
		{
			
		}
		else
			App_Modbus_Plc_Read_X_Status(0,32);//读取32路  2N 的读取12路  3U的读取32路 4组X
		break;
	case 7:		
		if((PLC_Run_Mode==PLC_MODE_NONE)||(PLC_Run_Mode==PLC_MODE_SERVO))//无PLC或SERVO不入
			{

			}
		else
			App_Modbus_Plc_Read_Y_Status(PLC_Y_BASE_ADDER,32);//读取Y00开始的数据
	
		break;
	case 8:		
		#ifdef MODBUS_SERVO_ENB	
			#ifdef NACHUAN_SERVO
					App_Modbus_Servo_Alarm_Read();//读故障代码
			#else
		
			App_Modbus_Servo_Alarm_Read();//读故障代码
			#endif
		#endif
	
		//16寸的加油  M 控制
//////////		App_Automode_Oil_To_PLC_M_Process();

		break;
	case 9:
		
		#ifdef MODBUS_SERVO_ENB	
			#ifdef NACHUAN_SERVO
			App_Modebus_Servo_Read_Cur_Position();
			#else
			App_Modebus_Servo_Read_Cur_Position();
			#endif
		#endif
	
		break;
	case 10:
		if((PLC_Run_Mode==PLC_MODE_NONE)||(PLC_Run_Mode==PLC_MODE_SERVO))//无PLC或SERVO不入
			{

			}
		else
		{
			
//////////		if(CutKnife_Position_Flag!=0)
//////////			{
//////////			//printf("D60 read...\r\n");
//////////				App_Modbus_Plc_Read_D_Data(60,1);
//////////			}

//////////		App_Modbus_Plc_Write_D50_Pressure();//低压
//////////		App_Modbus_Plc_Write_D410_Pressure();//高压

		}

		break;
	}
	
if(TaskStep>=8)
	{
	TaskStep=0;
	}

}
