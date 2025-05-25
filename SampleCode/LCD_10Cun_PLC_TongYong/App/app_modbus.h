#ifndef _APP_MODBUS_H
#define _APP_MODBUS_H


#include "main.h"



#define N972_MODBUS_SERVO

/*
#define PLC_ADDER 0x02
#define SERVO_ADDER 0x01
*/

//PLC  地址相关定义


/*
// 0x01  位读
// 0x05  位写

//软件元件 位寻址
#define PLC_M_BIT_BASE_ADDER  0x0000	//0x0000～0x1DFF M0～M7679 
#define PLC_Y_BIT_BASE_ADDER  0x3300	//0x3300～0x33FF Y0～Y377  	 可读写
#define PLC_X_BIT_BASE_ADDER  0x3400	//0x3400～0x34FF  X0～X377   只读


// 0x03  字读
// 0x06  字写

//软件元件 字寻址
#define PLC_D_BASE_ADDER  0x0000	//0x0000～0x1F3F D0～D7999
#define PLC_M_BASE_ADDER  0xA478	//0xA478～0xA657 M0～M7679 
#define PLC_Y_BASE_ADDER  0xA7A8	//0xA7A8～0xA7B7 Y0～Y377  	 可读写
#define PLC_X_BASE_ADDER  0xA7B8	//0xA7B8～0xA7C7  X0～X377   只读


*/
//PLC  地址相关定义   结束



//SERVO  地址相关定义

#define SERVO_PULSE_BASE_ADDER 0x0600			//0x600:给定脉冲数低十六位(可读可写)	0x601:给定脉冲数高十六位(可读可写) 0x600,0x601同时写时会启动一次内部位置运行
#define SERVO_SPEED_SET_ADDER  0x0602				//0x602:给定速度(可读可写单位rpm,写完后会启动一次内部位置运行)--可写入数据

#define SERVO_POSITION_BASE_ADDER 0x0511		//0x511:当前实际位置低十六位--（指令单位)  高字节在前 （ 可读，与Un013相对应)，当前脉冲
																					//0x512:当前实际位置高十六位--(指令单位)   高字节在前 大端模式(可读，与Un013相对应）
																					
																					
#define SERVO_ALARM_ADDER 0x0514			//0x514:报警号（可读，可清（写任何内容均为清错)，如果无报警，读出是0，如果报警，如报警A840,读取出的报警号为A840	
#define SERVO_STATUS_ADDER 0x0513			//0x513:驱动器状态(只读,位定义，只实现了如下后有注释--部分)
																			//Uint16 coin:1;			// ----位置到达
																			//Uint16 svstate:1;		          // ----使能与否
																			//Uint16 SvReady:1;		//  ----准备好
																			//Uint16 ALM:1;			//  -----报警
																			
#define SERVO_MULCIRCLE_ADDER 0x8011		//0x8011:读取多圈数值   //写0  多圈清零
#define SERVO_SIGCIRCLE_ADDER 0x8012    //读取单圈数据


//实际位置=0x8012+0x8011*65536

//SERVO  地址相关定义   结束

//extern char App_ModBus_Status;
extern int App_Modbus_EnbInit_Flag;

extern unsigned char App_Modbus_Send_Return_Flag;

extern unsigned int App_Modbus_Servo_Status;


extern unsigned short Stop_0x800C_Data;
extern unsigned short Stop_0x800D_Data;

extern unsigned char D70_Write_Flag;
extern unsigned short D70_Data;


extern unsigned short D_Area_Array[128];


extern unsigned char App_Modbus_Task_Ready_Flag;
extern unsigned char Circle_UpData_Flag;

void App_ModBus_Task_Test(void);
void App_ModBus_Task_Run(void);

//Modbus 解码
void APP_ModBus_Decode(void);

void App_Modbus_Send(void);


#endif
