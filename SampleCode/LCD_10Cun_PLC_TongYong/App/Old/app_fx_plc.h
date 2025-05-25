#ifndef _APP_FX_PLC_H
#define _APP_FX_PLC_H

#include "main.h"

#define PRESSURE_DATA_SAVE_ADDER 2045*1024   //压力值放在最后的2K地址


#define FX_PLC_CONFIG_SAVE_ADDER  2046*1024  //FX_PLC 配置寄存器




extern unsigned short Plc_DT_Data_t[32];

extern unsigned char  Plc_ReadContactChannel;//当前读取的通道

extern unsigned char FX_Plc_X_Status_Byte[16];  //
extern unsigned char FX_Plc_Y_Status_Byte[16];

extern char FX_Plc_X_Status[64][1];//PLC输入触点状态
extern char FX_Plc_Y_Status[64][1];//PLC输出触点状态
extern char FX_Plc_X_Old_Status[64][1];//PLC输入触点状态
extern char FX_Plc_Y_Old_Status[64][1];//PLC输出触点状态


extern unsigned char FX_PLC_X_StatusBuf[5];
extern unsigned char FX_PLC_Y_StatusBuf[5];

extern char FX_PLC_X_Status[5][8];
extern char FX_PLC_Y_Status[5][8];

extern char FX_Plc_X4_Status;
extern char FX_Plc_X5_Status;
extern char FX_Plc_X12_Status;

extern unsigned short FX_Plc_PressureData;

extern unsigned char YaZhiMotorRun_Flag;

extern 		int 	FX_Plc_Connect_TimeOut;

extern unsigned short FX_Plc_Real_PressureData;
extern unsigned short FX_Plc_Foot_Real_PressureData;


extern unsigned short FX_Foot_Plc_PressureData;

extern unsigned char FX_PLC_PowerOn_Init_Flag;

extern unsigned char FX_Plc_PressureData_Download_Flag;
extern unsigned char FX_Plc_Foot_PressureData_Download_Flag;

extern unsigned char FX_Plc_EnbCut_Flag;
extern unsigned char FX_Plc_EnbAutoCut_Flag;

extern unsigned char FX_Plc_EnbQiFa_Flag;
extern unsigned char FX_Plc_EnbLiZhi_Flag;

extern unsigned char FX_Plc_Comm_TimeOut_Flag;

extern unsigned char Plc_X_Err_Status;

extern int YaZhi_Run_Data[16];


extern unsigned YaZhi_Sensor_Status;
extern unsigned char YaZhiRun_Cnt;

extern unsigned char FX_PLC_Motor_Run_Enb_Flag;



void App_FX_PLC_LiZhi_MotorRunStop(void);


void App_FX_Plc_CommDecode(void);

void App_FX_Plc_Init(void);

void App_FX_Plc_Run(void);

void APP_FX_Plc_Poll_Exec(void);

void App_FX_Plc_TimeOut_Exec(void);

unsigned char  App_FX_Plc_Force_Process(char *sta,unsigned int adder);


void FX_PLC_Save_Config(void);
void FX_PLC_Load_Config(void);

void App_FX_Plc_LoadPressureData(void);


void FX_Save_PressureData(int prognum);//保存对应程序的压力值

//************************************************************************************
void FX_Save_Foot_PressureData(int prognum);//保存对应程序的压力值
	
void App_FX_Plc_Pressure_AutoSave(void);//当压力数据改变时。自动保存压力数据
unsigned short FX_Read_PressureData(int prognum);//读取对应程序的压力值
//************************************************************************************
unsigned short FX_Read_Foot_PressureData(int prognum);//读取对应程序的压力值

void App_Plc_Check_GuangDian(void);

void YaZhi_Run_Check_Enter(void);

void YaZhi_CheckData(void);
void YaZhi_MotorRun(Int32U vbcd);
void OptimizeCut_X05_RunCheck(void);

void YaZhi_Process_RunCheck(void);

void Check_FX_PLC_Motor_Run_Status(void);

void YaZhi_Instert(void);//压力纸插入

#endif
