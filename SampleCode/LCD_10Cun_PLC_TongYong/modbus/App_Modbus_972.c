#include "App_Modbus_972.h"


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "app_plc.h"



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

//#include "optimize_cut.h"


#include "app_modbus_servo.h"

#include "modbus_972.h"

#include "app_modbus_plc.h"



#else

#include "../Serial/Serial.h"

#include "../main.h"

#include "../gpio_config.h"


#include "../modbus/modbus.h"
#include "../modbus/uart_modbus.h"

#include  "App_Modbus_Servo.h"

#endif


float Servo_Cur_Position=8.88f;


//PLC IO
////////unsigned char PLC_X_Status[128];
////////unsigned char PLC_Y_Status[128];
////////unsigned char PLC_M_Status[128];

//Modbus Servo IO
unsigned char ModbusServo_X_Status[64];
unsigned char ModbusServo_Y_Status[64];


unsigned char App_ModBus_Task_Cnt=0;


unsigned char Modubs_Cmd_Type=1;

unsigned int Motor_run_Testtime=0;

unsigned char Zero_Flag=0;

int Servo_Send_Enb_Time=0;

#include "timer.h"

#include <stdio.h>
#include <string.h>

#include "nuc970.h"
#include "sys.h"



int test_time=0;

void App_Modbus_Test(void)
{
Timer0Init();
		
sysprintf("App_Modbus_Test\r\n");
while(1)
	{
	if(Ms_Flag!=0)
		{
			Ms_Flag=0;
			
			test_time++;
			if(test_time>1000)
			{
				test_time=0;
			BellOUT_ON;	
			}
			if(test_time==500)
				BellOUT_OFF;
			
			
			
		}
		
		
	}
	
	
}



//Modbus Task
void App_Modbus_Task(void)
{


App_ModBus_Task_Cnt++;
switch(App_ModBus_Task_Cnt)
	{
	//switch(App_ModBus_Task_Cnt)
	//	{
		case 1:
			
//////////////		if(Servo_Send_Enb_Flag==1)
//////////////			{
//////////////			App_Modebus_Servo_Read_Cur_Position();
//////////////			Servo_Send_Enb_Time=0;
//////////////			}
//////////////		else
//////////////		{
//////////////		Servo_Send_Enb_Time++;
//////////////		if(Servo_Send_Enb_Time>=10)
//////////////			{
//////////////			Servo_Send_Enb_Time=0;
//////////////			Servo_Send_Enb_Flag=1;
//////////////			}
//////////////		}
		break;
		case 10:
			break;
	//	}
	}
if(App_ModBus_Task_Cnt>10)
	App_ModBus_Task_Cnt=0;

ModBus_Queue_SendFrame();//队列发送



return;

App_ModBus_Task_Cnt++;
switch(App_ModBus_Task_Cnt)
	{
	case 1:
		Modubs_Cmd_Type=PLC_READ_X;//读PLC X
		ModBus_SendFrame(PLC_ADDER,MODBUS_READ_CMD,PLC_X_BASE_ADDER,0x04);//读取4个字的数据	
	//	Uart_Modbus_Comm_Send(Modbus_Sendbuf,8);
		break;
	case 2:
		Modubs_Cmd_Type=PLC_READ_Y;//读PLC Y
		ModBus_SendFrame(PLC_ADDER,MODBUS_READ_CMD,PLC_Y_BASE_ADDER,0x04);//读取4个字的数据	
//		Uart_Modbus_Comm_Send(Modbus_Sendbuf,8);
		break;
	case 3:

		Modubs_Cmd_Type=PLC_READ_Y;//读SERVO Y
		ModBus_SendFrame(SERVO_ADDER,MODBUS_CMD_READ_COL,0x0400,0x08);//读取4个字的数据	
	//	Uart_Modbus_Comm_Send(Modbus_Sendbuf,8);

		break;
	case 4:

		if(Zero_Flag==0)
		{

		Modubs_Cmd_Type=0;
		App_Modebus_Servo_Set_Start_Position(1000);
	//	App_Modbus_Servo_Set_ZeroPosition();
		Zero_Flag=1;
		return;
		}

		if(Zero_Flag<50)
		{

		Zero_Flag++;
		return;

		}


	//	App_ModBus_Task_Cnt=0;
	//	return;
		if(Motor_run_Testtime==0)
		{

		//	App_Modbus_Servo_Ahead_RunAndStop(SERVO_CONTROL_ON);//正转开
		Modubs_Cmd_Type=PLC_READ_Y;//读SERVO Y
		//ModBus_SendFrame(SERVO_ADDER,05,0x0801,0xff00);//读取4个字的数据	
		//Uart_Modbus_Comm_Send(Modbus_Sendbuf,8);

		}
		
		if(Motor_run_Testtime==50)
		{

		Modubs_Cmd_Type=PLC_READ_Y;//读SERVO Y

		//App_Modbus_Servo_Ahead_RunAndStop(SERVO_CONTROL_OFF);//正转停
		//ModBus_SendFrame(SERVO_ADDER,05,0x0801,0x0000);//读取4个字的数据	
		//Uart_Modbus_Comm_Send(Modbus_Sendbuf,8);


		}
		if(Motor_run_Testtime>=100)
		{
		Motor_run_Testtime=0;


		}
		else
			Motor_run_Testtime++;

//01 05 08 01 FF 00 DF 9A

	//	App_ModBus_Task_Cnt=0;
		break;
	case 5:
		if(Zero_Flag==1)
		{

		Modubs_Cmd_Type=0;
		//	App_Modebus_Servo_Set_Start_Position(0);
		//App_Modbus_Servo_Set_ZeroPosition();
		Zero_Flag=2;
		return;

		}

		if(Zero_Flag<50)
		{
			return;
		}

		if(Servo_Send_Enb_Flag==1)
		{
		//App_Modebus_Servo_Read_Cur_Position();
		}

		
		break;
	case 6:

		App_ModBus_Task_Cnt=0;
		break;
	case 7:
		break;
	case 8:
		break;
	case 9:
		break;
	case 10:
		break;
	case 11:
		App_ModBus_Task_Cnt=0;
		break;
	}

}



/*
unsigned char Modbus_Adder;
unsigned char Modbus_Cmd;
unsigned char Modbus_Length;
*/



void App_Modbus_Decode(unsigned char *rbuf,int len)
{
unsigned char i;

Modbus_Adder=*rbuf++;
Modbus_Cmd=*rbuf++;
Modbus_Length=*rbuf++;

if((Modbus_Cmd==MODBUS_PLC_BIT_WRITE_CMD)||(Modbus_Cmd==MODBUS_WRITE_CMD)||(Modbus_Cmd==MODBUS_MORE_WRITE_CMD))	// 0x06或 0x10 命令。返回8个字节 
	{//写返回
		
//	if((Modbus_Adder==SERVO_ADDER)&&(Modbus_Cmd==0x90))
//			{
//			Modbus_Servo_Err_Cnt++;
//			sysprintf("ServCMD_Send_Cnt= %d ServoCMD_Err_Cnt= %d\r\n",Modbus_Servo_Send_Cnt,Modbus_Servo_Err_Cnt); //				
	//		}
//	else			
			ModBus_Queue_ChangeBuf();//收到返回后，清除缓冲区
		Modbus_Queue_Clear_SendStatus();
	}
else
	if((Modbus_Cmd==0x81)||(Modbus_Cmd==0x83)||(Modbus_Cmd==0x85)||(Modbus_Cmd==0x86)||(Modbus_Cmd==0x90)||(Modbus_Cmd==0x95))
		{//异常返回

		Modbus_Servo_Err_Cnt++;
		sysprintf("ServCMD_Send_Cnt= %d ServoCMD_Err_Cnt= %d\r\n",Modbus_Servo_Send_Cnt,Modbus_Servo_Err_Cnt); //	
			
		//ModBus_Queue_ChangeBuf();//队列减1
			
		}
	else
		if((Modbus_Cmd==MODBUS_READ_CMD)||(Modbus_Cmd==MODBUS_CMD_READ_COL)||(Modbus_Cmd==MODBUS_PLC_BIT_READ_CMD))
			{//读返回
			for(i=0;i<Modbus_Length;i++)
				{
			//	ModBus_DataBuf[i]=*rbuf++;
				memcpy(ModBus_DataBuf,rbuf,Modbus_Length);
				}
			
			switch(Modbus_Adder)
				{
				case SERVO_ADDER:
					App_Modbus_Servo_Decode();
					break;

				case PLC_ADDER:
					App_Modbus_FxPlc_Decode();
					break;
				}
			}
}





FloatAndByte FAB;
 //  FloatAndByte FAB;


// IEEE 754  float to Buf
void Float_To_ByteBuf(float fn,unsigned char * bbuf)
{
FAB.union_float=fn;

*bbuf++=FAB.union_byte[1];
*bbuf++=FAB.union_byte[0];
*bbuf++=FAB.union_byte[3];
*bbuf++=FAB.union_byte[2];

/*
FAB.union_byte[0]=ModBus_DataBuf[1];
FAB.union_byte[1]=ModBus_DataBuf[0];	
FAB.union_byte[2]=ModBus_DataBuf[3];
FAB.union_byte[3]=ModBus_DataBuf[2];
*/
}



// IEEE 754  Buf To float
float ByteBuf_To_Float(unsigned char *bbuf)
{
float fn;
FAB.union_byte[0]=bbuf[1];
FAB.union_byte[1]=bbuf[0];	
FAB.union_byte[2]=bbuf[3];
FAB.union_byte[3]=bbuf[2];

fn=FAB.union_float;
return fn;
}


unsigned char * FloatToBytes(unsigned char * data, float float_to_byte)
{
FAB.union_float = float_to_byte;
for (int i = 0; i < 4; i++)
{
data[i] = FAB.union_byte[i];
}
return data;
}




void  App_Modbus_Get_CurrentSize(void)
{
	
	
	CurrentSize=Servo_Cur_Position*100;
	
}




/*

//写M命令
void App_Modbus_FXPlc_M_CTRL(char *msta,unsigned int madd)
{
unsigned int target_madd=M_BASE_ADDD+madd;

if(strcmp(msta,"ON")==0)
			{
					
		//	while(App_Modbus_Task_Ready_Flag==0){};//如果是MODBUS发送状态，则等待
			ModBus_SendFrame(PLC_ADDER,MODBUS_PLC_BIT_WRITE_CMD,target_madd,0xff00);//读取4个字的数据
		//	ModBus_Queue_LoadBuf(ModBus_SendBuf,'m',8);//写M命令
			}
	else
			{
				if(strcmp(msta,"OFF")==0)
				{						
		//		while(App_Modbus_Task_Ready_Flag==0){};//如果是MODBUS发送状态，则等待
				ModBus_SendFrame(PLC_ADDER,MODBUS_PLC_BIT_WRITE_CMD,target_madd,0);//读取4个字的数据
		//		ModBus_Queue_LoadBuf(ModBus_SendBuf,'m',8);//写M命令
				}
			}	
}


*/
