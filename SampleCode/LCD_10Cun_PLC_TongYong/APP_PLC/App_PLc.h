#ifndef _APP_PLC_H
#define _APP_PLC_H


#include "main.h"
#define PLC_3U


#define FX_PLC_CONFIG_SAVE_ADDER  2046*1024  //FX_PLC 配置寄存器


#define N972_MODBUS_SERVO



#define PLC_CONTACT_OFF '0' //触点为OFF
#define PLC_CONTACT_ON '1'  //触点为ON

#define ORI_X_IN 0
#define KNIFE_X_IN 1
#define PRESS_X_IN 7

#define AHEAD_LIMIT_X_IN 24
#define BACK_LIMIT_X_IN 21

#define TUOBAN_X_IN 12
#define IR_X_IN 4


//#define MODBUS_SERVO_ENB

extern unsigned char Modbus_Servo_Link_Flag;// MODBUS 伺服连接标志位
extern unsigned char Modbus_Servo_Err_Flag; // MODBUS 伺服错误标志位
extern int Modbus_ServoTimeOut;

extern unsigned char Circle_UpData_Flag;
extern unsigned int App_Modbus_Servo_Status;
extern Int32U App_ModBus_DecTime;


extern unsigned char App_Modbus_Send_Return_Flag;
extern unsigned char  Modbus_PLC_Link_Flag;
extern int Modbus_PlcTimeOut;



extern unsigned char FX_Plc_EnbCut_Flag;
extern unsigned char FX_Plc_EnbAutoCut_Flag;
extern unsigned char FX_Plc_EnbAutoCut_Send_Flag;

extern unsigned char FX_Plc_EnbYaZhi_Flag;

extern unsigned char FX_Plc_EnbQiFa_Flag;
extern unsigned char FX_Plc_EnbQiFa_Flag_Temp;
extern unsigned char FX_Plc_EnbLiZhi_Flag;

extern unsigned char YaZhiMotorRun_Flag;
extern unsigned char FastCut_Enb_Flag;


extern unsigned char Ori_Sensor_Status;

extern unsigned char Knife_Sensor_Status;
extern unsigned char Press_Sensor_Status;
extern unsigned char TuoBan_Status;
extern unsigned char IR_Sensor_Status;

extern unsigned char PLC_PowerOn_Init_Flag;
extern unsigned short KnifeDownTime;//下刀时间


extern unsigned char Plc_X_Err_Status;


extern unsigned short FX_Plc_Real_PressureData;

extern  unsigned short FX_Plc_Foot_Real_PressureData;

extern unsigned short FX_Plc_PressureData;
extern unsigned short FX_Foot_Plc_PressureData;
extern unsigned short FX_Plc_OldPressureData;
extern unsigned short FX_Plc_Foot_OldPressureData;

//通讯超时检测
void App_Modbus_PLC_TimeOut(void);
//通讯超时检测
void App_Modbus_Servo_TimeOut(void);


void App_Sensor_Get_Status(void);


void PLC_Load_Config(void);
void PLC_Save_Config(void);


extern unsigned char FX_PLC_Motor_Run_Enb_Flag;

//检测主机启动状态
void Check_FX_PLC_Motor_Run_Status(void);

void YaZhi_CheckData(void);


#endif
