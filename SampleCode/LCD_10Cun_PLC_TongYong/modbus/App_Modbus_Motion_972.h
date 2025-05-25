#ifndef _APP_MODBUS_MOTION_972_H
#define _APP_MODBUS_MOTION_972_H


#include "main.h"



#define AHEAD_JOGRUN_MODE 1
#define FAST_AHEAD_JOGRUN_MODE 2
#define BACK_JOGRUN_MODE 3
#define FAST_BACK_JOGRUN_MODE 4





#define RUN_STOP 0
#define RUN_AHEAD 1
#define RUN_BACK 2


extern unsigned char Servo_Emergency_Switch_Status;  //伺服上的急停开关
extern unsigned char PLC_Emergency_Switch_Status;    //PLC上的急停开关
extern unsigned char PLC_MainPower_YOUT_Status; 	//PLC的主机电源开启Y输出
extern unsigned char PLC_MainPower_YOUT_Status_Temp;
extern  unsigned char PLC_GuangDian_Switch_Status;//PLC光电开关的状态
extern unsigned char PLC_GuangDian_Switch_Status_Temp;

extern unsigned char Modbus_Servo_RunEnb_Flag;//电机允许运行标志

extern unsigned char StepRun_Flag;//步进运行标志位
extern unsigned char App_Manual_JogRun_Status;//1:前进 2：快进  3:后退  4：快退


extern unsigned char YaZhi_M310_Sync_Flag;
extern unsigned char YaZhi_M310_Sync_Temp_Flag;



extern unsigned char ManualMode_M311_Flag;
extern unsigned char ManualMode_M311_Temp_Flag;


extern unsigned char Modbus_Servo_Run_Dir_Flag;//0： 前进，1，后退

//后退 6mm后的再前进
void App_Modbus_Motion_Run_Next_972(Int32U target_size);

void App_Modbus_Motion_Run_972(Int32U target_size);

void App_Modbus_Motion_JogRun_972(Int32U spd,Int32U target_size);


void App_Servo_Check_CutEnb(void);//允许裁切判断

void App_Manual_JogRun(unsigned char msta);
void App_Manual_JogRun_Check_Stop(void);


//按数字键停机
void App_PressNumKey_Stop(void);


//运行中检测限位等状态   限位或急停后，停止运行
void App_Motion_Runing_Check_Limit_Sensor(void);

//运行循环
void App_Modbus_Motion_Loop_Run(void);
//M控制处理，用在实时判断上
void App_Plc_M_Con_Process(void);


#endif
