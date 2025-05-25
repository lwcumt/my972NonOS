#include "app_modbus_test.h"



#include "app_modbus.h"

#include "app_modbus_plc.h"

//#include "timer.h"

#include <stdio.h>
#include <string.h>

//#include "nuc970.h"
//#include "sys.h"


#include "modbus.h"

#include "../main.h"

#include "../App/App_Parameter.h"


#include "app_modbus_servo.h"

//#include "pic_exec.h"

#include "app_modbus_motion.h"

#include "../App/App_Automode.h"



unsigned char ElectricWheelOn_flag=0;

void App_Modbus_Test_Init(void)
{





}


#include "../gpio_config.h"


void App_Modbus_Test_Run(void)
{	

App_Modebus_Servo_Init();
App_Modbus_Plc_Init();


Gpio_outp_init(MODBUS_TR_IO,Low);
	
//App_Modbus_Get_CurrentSize();
	
	return;
printf("App_Modbus_Test_Run\r\n");
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




#include "App_FX5_Plc.h"


int BackUpTime_Enable=-1;//PSW_Lock_Disp_Flag_old=-1;
int BackUpTime_Data=-1;

unsigned char  App_ModBus_Test_TaskTime=0;

void  App_Modbus_Test_Task(void)
{
	/*
App_ModBus_Test_TaskTime++;
if(App_ModBus_Test_TaskTime<1)
	return;

	*/

App_ModBus_Test_TaskTime=0;

ModBus_Queue_SendFrame();//队列发送
	
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

App_Modbus_PLC_TimeOut();//PLC通讯超时检测
	
	
taskTime++;
if(taskTime<2)

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
			if(BackUpTime_Enable!=(int)PSW_Lock_Disp_Flag)
				{
				BackUpTime_Enable=(int)PSW_Lock_Disp_Flag;

				if(PSW_Lock_Disp_Flag==0)
					App_Modbus_Plc_Write_M_Status(258,M_OFF);
				else
					App_Modbus_Plc_Write_M_Status(258,M_ON);

				}

			if(BackUpTime_Data!=(int)Knife_ChangeTime)
				{
				BackUpTime_Data=(int)Knife_ChangeTime;

				App_Modbus_Plc_Write_D_Data(258,Knife_ChangeTime);

				}
		}

	//	App_Modbus_Plc_Read_X_Status(0,32);//读取32路  2N 的读取12路  3U的读取32路 4组X
	//	TaskStep=0;//测试
	//	printf("Write Y Status ...\r\n");

	//	App_Modbus_FX5_Write_Y(8,PLC_CONTROL_ON);
	//	TaskStep=0;//测试



	//	if(Servo_Run_Step==0)
	//		App_Modebus_Servo_Run(2000,1000);
	//	if(Servo_Run_Step==3)
	//		App_Modebus_Servo_Run(2000,800);
		
	//	Servo_Run_Step++;
	//	if(Servo_Run_Step>=6)
	//		Servo_Run_Step=0;		
		break;
	case 2:
		//	App_Modbus_Plc_Write_M_Status(100,PLC_CONTROL_ON);

		#ifdef NACHUAN_SERVO
			App_Modbus_Servo_Set_AddSubTime();//发送伺服加减时间  上电和改变数据时清发送标志位重发 
			App_Modbus_Servo_Set_HandWheel(Wheel_Step);//设定手轮
		#else
		App_Modbus_Servo_MotorRunDir_Set();//设置下电机方向
		App_Modbus_Servo_Set_AddSubTime();//发送伺服加减时间  上电和改变数据时清发送标志位重发 
		App_Modbus_Servo_Set_HandWheel(Wheel_Step);//设定手轮

		#endif
		break;
	case 3:
	//	App_Modbus_Plc_Read_Y_Status(0,32);//读取32路  2N 的读取12路  3U的读取32路 4组X

		#ifdef NACHUAN_SERVO
			#ifdef NC_SERVO_WITH_PLC_CONTROL
			App_Modbus_Plc_Read_M_Status(404);
			#else
			App_Modbus_NC_Servo_Read_RunStatus();
			#endif
		#else
			App_Modbus_Servo_Read_X();
		#endif

		break;
	case 4:
		#ifdef NACHUAN_SERVO

			App_Modbus_Plc_Read_D_Data(D62_ADD,6);//读D62 _ D64 对应的M300等，映射到D62
			//App_Modbus_Plc_Read_D_Data(40,2);//读手轮
		#else
			App_Modbus_Servo_Read_Y();

	    #endif		

		break;
	case 5:
		/*
		if(ModBus_Plc_CommWait_Status!=0)
		{
		TaskStep=7;//转到读伺服故障代码
		break;
		}
		*/
		
	if((PLC_Run_Mode==PLC_MODE_NONE)||(PLC_Run_Mode==PLC_MODE_SERVO))//无PLC或SERVO不入
	{
	}
	else
	{
		App_Modbus_Plc_Write_D20_DownCutTime();		//D20 下刀时间发送,   清0 可以重复发送
		App_Modbus_Plc_Write_M280_FastCutMode();
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
		
		//App_Modbus_Plc_Read_Y_Status(PLC_X_BASE_ADDER,4);//读PLC  Y 状态
		break;
	case 8:		
		
	//	App_Modbus_Plc_Write_M_Status(100,PLC_CONTROL_OFF);
	
		#ifdef NACHUAN_SERVO
				App_Modbus_Servo_Alarm_Read();//读故障代码
		#else
	
		App_Modbus_Servo_Alarm_Read();//读故障代码
		#endif

		App_Automode_Oil_To_PLC_M_Process();

		break;
	case 9:
		#ifdef NACHUAN_SERVO
		App_Modebus_Servo_Read_Cur_Position();
		#else
		App_Modebus_Servo_Read_Cur_Position();
		#endif
		break;
	case 10:
		if((PLC_Run_Mode==PLC_MODE_NONE)||(PLC_Run_Mode==PLC_MODE_SERVO))//无PLC或SERVO不入
			{

			}
		else
		{
		if(CutKnife_Position_Flag!=0)
			{
			//printf("D60 read...\r\n");
				App_Modbus_Plc_Read_D_Data(60,1);
			}

		App_Modbus_Plc_Write_D50_Pressure();//低压
		App_Modbus_Plc_Write_D410_Pressure();//高压




		//App_Modbus_Plc_Write_Y_Status(1,PLC_CONTROL_OFF);
		}

		break;
	}
	
if(TaskStep>=10)
	{
	TaskStep=0;
	}

}
