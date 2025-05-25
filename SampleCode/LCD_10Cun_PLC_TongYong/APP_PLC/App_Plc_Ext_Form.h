#ifndef _PLC_EXT_FORM_H
#define _PLC_EXT_FORM_H

#include "main.h"
#include "datagui.h"
#include "pic_exec.h"
#include "drv_glcd.h"

#include "key.h"
#include "touch.h"
#include "tsc2046.h"
#include "gtp.h"
#include "pic_exec.h"
#include "timer.h"

#define PLC_ENB 1
#define PLC_DIS 0





/*
							#define CHANGE_KNIFE_WIN_X  144
							#define CHANGE_KNIFE_WIN_Y  110
							#define CHANGE_KNIFE_WIN_WIDE  512							
							#define CHANGE_KNIFE_WIN_HIGH  380
							*/
					

							#define CHANGE_KNIFE_WIN_X  144
							#define CHANGE_KNIFE_WIN_Y  110
							#define CHANGE_KNIFE_WIN_WIDE  512							
							#define CHANGE_KNIFE_WIN_HIGH  300
							
							
							
							#define PRESSURE_SET_WIN_X  144
							#define PRESSURE_SET_WIN_Y  180
							#define PRESSURE_SET_WIN_WIDE  512							
							#define PRESSURE_SET_WIN_HIGH  380
							

							#define YAZHI_PROCESS_WIN_X  250// 110+150+32
							#define YAZHI_PROCESS_WIN_Y  110
							#define YAZHI_PROCESS_WIN_WIDE  300							
							#define YAZHI_PROCESS_WIN_HIGH  380
							
							
extern PICTUREBOX IR_ReadLine_Picture;							
							
extern unsigned char MainPower_Status;
extern unsigned char Manual_Knife_Status;
extern unsigned char Fast_Knife_Status;
extern unsigned char Motor_Knife_Status;
extern unsigned char Knife_Change_Status;



extern unsigned char Wind_Motor_Status;//风泵


extern unsigned char Lamp_Status;

extern unsigned char YaZhi_Process_Flag;

extern unsigned char FX_PLC_IO_Dis_Flag;
					
extern unsigned char Pressure_Dis_Refish_Flag;


extern unsigned short Motor_StartUpTime;//电机启动时间
extern unsigned short Motor_StopTime;//电机停止时间

extern unsigned char CutOpt_Flag;//裁切优化 《开关》
extern unsigned short CutTime;   //优化时间  
extern unsigned char FastCut_Flag;  //快速裁切 《开关》



#define PLC_HINT_DIS_BAK_COLOR  0x948FA6


#define PLC_HINT_DIS_X 2 // (REMIND_WINDOW_X+2)
#define PLC_HINT_DIS_Y REMIND_WINDOW_Y// 550+12 //(REMIND_WINDOW_Y+5-30)
					
					
extern unsigned char PLC_Enb_Flag;

extern unsigned char MotorSetType;//电机设置的类型  //MotorSetType 为新加入的设置变量。只在选择工作系统时使用


extern PICTUREBOX Main_PowerOn_Picture_Enb;
extern PICTUREBOX Main_PowerOn_Picture_Dis;
extern PICTUREBOX Main_PowerOff_Picture_Enb;
extern PICTUREBOX Main_PowerOff_Picture_Dis;
extern PICTUREBOX Manual_Knife_Picture_Enb;
extern PICTUREBOX Manual_Knife_Picture_Dis;
extern PICTUREBOX Fast_Knife_Picture_Enb;
extern PICTUREBOX Fast_Knife_Picture_Dis;
extern PICTUREBOX Motor_Knife_Picture_Enb;
extern PICTUREBOX Motor_Knife_Picture_Dis;
extern PICTUREBOX Wind_Motor_Picture_Enb;
extern PICTUREBOX Wind_Motor_Picture_Dis;
extern PICTUREBOX Lamp_Picture_Enb;
extern PICTUREBOX IR_ReadLine_Picture;
extern PICTUREBOX IR_Handle_Picture;
extern PICTUREBOX Pressure_Set_Picture;

extern LABEL PLCMachineLabel;
extern LABEL PLC_SET_DT3SetLabel;
extern LABEL PLC_SET_DT3DataLabel;


extern BUTTON PLC_Pressure_SET_UP_BT;
extern BUTTON PLC_Pressure_SET_DOWN_BT;


extern LABEL PLC_DT0SetLabel;
extern LABEL PLC_DT1SetLabel;
extern LABEL PLC_DT2SetLabel;
extern LABEL PLC_DT3SetLabel;
extern LABEL PLC_DT4SetLabel;
extern LABEL PLC_DT5SetLabel;

extern LABEL PLC_DT0DataLabel;
extern LABEL PLC_DT1DataLabel;
extern LABEL PLC_DT2DataLabel;
extern LABEL PLC_DT3DataLabel;
extern LABEL PLC_DT4DataLabel;
extern LABEL PLC_DT5DataLabel;


extern unsigned char Pressure_Set_Status;
extern unsigned int Pressure_Set_Data;

extern unsigned char FX_PLC_Ori_Status;
extern unsigned char FX_PLC_TuoBan_Status;

extern unsigned char FX_PLC_YaZhi_Status;
extern unsigned char FX_PLC_Dao_Status;

extern unsigned char FX_PLC_FLimit_Status;//前极限
extern unsigned char FX_PLC_BLimit_Status;//后极限
extern unsigned char FX_PLC_MLimit_Status;//中极限
extern unsigned char FX_PLC_YaLi_Status; //压力输入 
extern unsigned char FX_PLC_YaLiSel_Status;//选择压力

////////extern uint8_t Machine_Set_UserCount_Flag;
////////extern uint32_t Machine_Set_UserCount_Time;

extern unsigned char Modbus_Motion_Set_LuoJu;
extern unsigned char Modbus_Motion_Set_ChiLunBi;
extern unsigned int YaZhiYaLi_Data;
extern unsigned int yazhiyali_data_temp;

void Plc_Ext_Form_Init(void);


void FX_PLC_Check_IO_Status(void);

void Plc_Form_DisUpdata(void);

//系统设置里的PLC参数 画面显示
void Plc_Ext_PlcSeting_Init_Disp(int x,int y);


void FX_PLC_ChangeAndSave_ParaData(void);


unsigned char Plc_Ext_PlcSeting_Select_ChangeData(unsigned char dp_index,Int32U indata);
void Plc_Ext_PlcSeting_Hint_Disp(unsigned char num);

void Plc_Ext_PlcSeting_Select_Disp(unsigned char num);

void OptimizeCut_Select(unsigned char snum);

void Plc_Form_Pressure_Set_Process(void);

void YaZhi_Process(void);

void Plc_Ext_Form_Event(TOUCH touch);

//信息提示显示
void PLC_FX_Hint_DisPlay(void);

//状态显示
void FX_PLC_XY_Status_Display(void);
void FX_PLC_Setup_ParaData_Init(void);
void FX_PLC_Setup_Para_Refish(unsigned char index);

void FX_PLC_Set_Process(unsigned  char sindex,unsigned int dat);
void FX_PLC_ChangeMode(unsigned char sindex);


extern unsigned char MainMotor_Run_Flag;
extern unsigned int MainMotor_StopTime;

extern unsigned char Manual_Change_Knife_Steps;//手动换刀步骤
extern unsigned int Manual_Change_Knife_InvertTime;

extern unsigned char LinkUpDate_Flag;

//显示PLC连接状态
void PLC_DispLink_Status(void);

//检测主机是否为启动状态
void Check_MainMotor_Run_Status(void);


#endif

