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
	
App_Modbus_Get_CurrentSize();
	
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


void  App_Modbus_Test_Task(void)
{
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
	
	
taskTime++;
if(taskTime<30)
		return;



taskTime=0;
TaskStep++;
switch(TaskStep)
	{
	case 1:
	//	if(Servo_Run_Step==0)
	//		App_Modebus_Servo_Run(2000,1000);
	//	if(Servo_Run_Step==3)
	//		App_Modebus_Servo_Run(2000,800);
		
	//	Servo_Run_Step++;
	//	if(Servo_Run_Step>=6)
	//		Servo_Run_Step=0;		

		break;
	case 2:
			App_Modbus_Servo_MotorRunDir_Set();
		//	App_Modbus_Plc_Write_M_Status(100,PLC_CONTROL_ON);
		App_Modbus_Servo_Set_AddSubTime();//发送伺服加减时间  上电和改变数据时清发送标志位重发 
		App_Modbus_Servo_Set_HandWheel(ElectricWheelOn_flag*10);//设定手轮 现在是0X 10X
	//App_Modbus_Servo_Set_HandWheel(ElectricWheelOn_flag*9+1);//设定手轮  原来是1X 10X
		break;
	case 3:
	//	App_Modbus_Plc_Read_Y_Status(0,32);//读取32路  2N 的读取12路  3U的读取32路 4组X
			App_Modbus_Servo_Read_X();
		break;
	case 4:
	//	
		App_Modebus_Servo_Read_Cur_Position();
		break;
	case 5:
		
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
	
	
		App_Modbus_Servo_Alarm_Read();//读故障代码
		break;
	case 9:

		break;
	case 10:
		
		//App_Modbus_Plc_Write_Y_Status(1,PLC_CONTROL_OFF);
		break;
	}
	
if(TaskStep>=10)
	{
	TaskStep=0;
	}

}
