#ifndef _APP_MODBUS_MOTION_H
#define _APP_MODBUS_MOTION_H



#include "main.h"




#define APP_MODBUS_MOTION 1




//基准参数结构 控件
typedef struct 
{
unsigned char Calibration_Flag;//是否校准  ，如果未校准，测进行初始化：读当前圈数值，赋 校准尺寸为123.45
	
int Calibration_Circle_Data;				//记忆的圈值
int Calibration_Dimension_Data;//校准和数据
	
}MODBUS_MOTION_PARAMETER;




//基准参数结构 控件
typedef struct 
{
unsigned char LimitInit_Flag;//是否初始化  ，如果未校准，测进行初始化： 前极限 1280  中极限 1000  后极限  80	
int Back_Limit;	 //后极限
int Mid_Limit;	 //中间限
int Ahead_Limit; //前极限	
}MACHINE_LIMIT;


extern unsigned char APP_MODBUS_MOTIRON_DIR;

extern MODBUS_MOTION_PARAMETER Modbus_Motion_Parameter;

extern MACHINE_LIMIT Machine_Limit;

extern int Circle_Data;
extern int CurPosition;

extern int RunPosition_Pulse_Cnt;

extern int Machine_Load_Postion_Pulse;
extern unsigned char Machine_Position_Pulse_LoadOK_Flag;

extern int Machine_Cur_Dimension;	//机器当前实际尺寸
extern unsigned char Machine_Cur_Dimension_LoadOK_Flag;

extern int Machine_Target_Dimension;	//机器目标尺寸

extern unsigned char Modbus_Servo_Link_Flag;	// MODBUS 伺服连接标志位
extern unsigned char Modbus_Servo_Err_Flag; // MODBUS 伺服错误标志位

extern int 	Modbus_ServoTimeOut;

extern unsigned char Electric_Wheel_Run_Flag;


extern unsigned char Modbus_Motion_AutoStop_Flag;
extern unsigned char Modbus_Motion_WaitStop_Flag;

extern int Cur_Circle_Data;

extern unsigned int WatiDelayTime;

extern Int32U App_ModBus_DecTime;

//初始化
void App_Modbus_Motion_Init(void);

//保存螺距导程
void App_Modbus_Save_LuoJu_DaoCheng(void);
//调入螺距导程
void App_Modbus_Load_LuoJu_DaoCheng(void);
	
//螺距和齿轮比系数计算
void App_Modbus_Cal_Dimension_Of_LuoJu_DaoCheng(void);

void App_Modbus_Motion_Reload_Dimension(void);

//计算当前尺寸
void App_Modbus_Motion_Cal_CurDimension(void);



//检测目标值
void App_Modbus_Motion_CheckTarget(void);

//停止
void App_Modbus_Motion_Stop(void);

void App_Modbus_motion_Disp(void);


//电子手轮检测
void App_Modbus_Motion_Whell_Check(void);

//手轮运行
void App_ModBus_Motion_ElectricWheel_Run(void);
	

void App_Modbus_Motion_JogRun(Int32U spd,Int32U target_size);

//运行
void App_Modbus_Motion_Run(Int32U target_size);

//校基准
unsigned char App_Modbus_Motion_Calibration(int cal_dimension);
//前进
void App_Modbus_Motion_Ahead_Run(void);
//后退
void App_Modbus_Motion_Back_Run(void);


//通读超时检测
void App_Modbus_Servo_TimeOut(void);


//进入系统前的运行
void App_Modbus_Motion_SystemEnter_Run(void);



#endif


