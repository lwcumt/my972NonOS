#include "App_plc_ext_form.h"
//#include "plcsetform.h"

//#include "setupform.h"

#include "touchevent.h"

#include "string.h"
#include "stdio.h"
//#include "tcpclient.h"
#include "drv_glcd.h"

#include "key.h"

#include "m25pe16.h"
#include "chndot.h"

#include "io.h"
#include "timer.h"

#include "pic_exec.h"

#include  "test_io.h"

#include "port.h"
#include "servo.h"
#include "name_input.h"
#include "keyboard.h"
#include "file.h"
#include "string.h"
//#include "tcpserver.h"
//#include "message.h"
//#include "net_process.h"

//#include "messageform.h"


#include "app_plc.h"
//#include "app_fx_plc.h"
//#include "optimize_cut.h"

//#include "comm_fx_plc.h"


#include "app_modbus_plc.h"

#include "app_plc.h"



#define PRESSURE_CHANGE_DIS


	#define IO_DIS_X 80
	#define IO_DIS_Y 490
	
	
					#define FX_PLC_IO_STATUS_WIN_X 50
				#define FX_PLC_IO_STATUS_WIN_Y 125-20
				
				#define FX_PLC_IO_STATUS_WIN_WIDE 700
				#define FX_PLC_IO_STATUS_WIN_HIGH 330
				
				
				unsigned char Plc_Poll_Enb_Flag=0;
				unsigned char  Plc_Comm_Status=0;
				#define PLC_COMM_TIMEOUT 1

unsigned char Plc_X_Status[8][8];

unsigned char XD_XE_Flag=0;

				

unsigned char MotorSetType=0;	//MotorSetType 为新加入的设置变量。只在选择工作系统时使用
unsigned char FX_PLC_IO_Dis_Flag=0;

unsigned char FX_PLC_Ori_Status=1;
unsigned char FX_PLC_TuoBan_Status=0;
unsigned char FX_PLC_YaZhi_Status=1;
unsigned char FX_PLC_Dao_Status=1;
unsigned char FX_PLC_FLimit_Status=1;//前极限
unsigned char FX_PLC_BLimit_Status=1;//后极限
unsigned char FX_PLC_MLimit_Status=1;//中极限
unsigned char FX_PLC_YaLi_Status=1; //压力输入 
unsigned char FX_PLC_YaLiSel_Status=1;//选择压力




unsigned short Motor_StartUpTime=0;//电机启动时间
unsigned short Motor_StopTime=0;//电机停止时间

unsigned char CutOpt_Flag=0;//裁切优化 《开关》
unsigned short CutTime=0;   //优化时间  
unsigned char FastCut_Flag=0;  //快速裁切 《开关》


unsigned char X16_Status=0;
unsigned char X17_Status=0;
unsigned char X12_Status=0;
unsigned char X13_Status=0;
unsigned char X21_Status=0;

PICTUREBOX Main_PowerOn_Picture_Enb=
{
PictureBox_Type,//unsigned char Type;
TRUE,//unsigned char Enabled;
TRUE,
FALSE,//unsigned char Focus
570,2,//LOCATION Location;	//定位
52,52,//SIZE Size; //总大小
(255<<16)+(255<<8),//unsigned int picturebkColor;
255,//unsigned int textboxSelectColor;
0,//unsigned int textColor;
None,//unsigned int textbkColor;	//背景色
16,//unsigned short FontWidth;//字体宽度
16,//unsigned short FontHigh;
0,//index
6,//MaxCount
"textbox1",
"manual_knife.bmp",
(unsigned char *)POWER_ON_UP_sdram//POWER_ON_DOWN_sdram
};


PICTUREBOX Main_PowerOn_Picture_Dis=
{
PictureBox_Type,//unsigned char Type;
TRUE,//unsigned char Enabled;
TRUE,
FALSE,//unsigned char Focus
570,2,//MARK_LABEL_X,MARK_LABEL_Y,//LOCATION Location;	//定位
52,52,//SIZE Size; //总大小
(255<<16)+(255<<8),//unsigned int picturebkColor;
255,//unsigned int textboxSelectColor;
0,//unsigned int textColor;
None,//unsigned int textbkColor;	//背景色
16,//unsigned short FontWidth;//字体宽度
16,//unsigned short FontHigh;
0,//index
6,//MaxCount
"textbox1",
"manual_knife.bmp",
(unsigned char *)POWER_OFF_UP_sdram
};


PICTUREBOX Main_PowerOff_Picture_Enb=
{
PictureBox_Type,//unsigned char Type;
TRUE,//unsigned char Enabled;
TRUE,
FALSE,//unsigned char Focus
570,2,//LOCATION Location;	//定位
MAIN_PWR_BUTT_W,MAIN_PWR_BUTT_H,//SIZE Size; //总大小
(255<<16)+(255<<8),//unsigned int picturebkColor;
255,//unsigned int textboxSelectColor;
0,//unsigned int textColor;
None,//unsigned int textbkColor;	//背景色
16,//unsigned short FontWidth;//字体宽度
16,//unsigned short FontHigh;
0,//index
6,//MaxCount
"textbox1",
"manual_knife.bmp",
(unsigned char *)POWER_OFF_UP_sdram
};


PICTUREBOX Main_PowerOff_Picture_Dis=
{
PictureBox_Type,//unsigned char Type;
TRUE,//unsigned char Enabled;
TRUE,
FALSE,//unsigned char Focus
570,2,//LOCATION Location;	//定位
MAIN_PWR_BUTT_W,MAIN_PWR_BUTT_H,//SIZE Size; //总大小
(255<<16)+(255<<8),//unsigned int picturebkColor;
255,//unsigned int textboxSelectColor;
0,//unsigned int textColor;
None,//unsigned int textbkColor;	//背景色
16,//unsigned short FontWidth;//字体宽度
16,//unsigned short FontHigh;
0,//index
6,//MaxCount
"textbox1",
"manual_knife.bmp",
(unsigned char *)POWER_OFF_DOWN_sdram
};





PICTUREBOX Fast_Knife_Picture_Enb=
{
PictureBox_Type,//unsigned char Type;
TRUE,//unsigned char Enabled;
TRUE,
FALSE,//unsigned char Focus
627,2,//LOCATION Location;	//定位
52,52,//SIZE Size; //总大小
(255<<16)+(255<<8),//unsigned int picturebkColor;
255,//unsigned int textboxSelectColor;
0,//unsigned int textColor;
None,//unsigned int textbkColor;	//背景色
16,//unsigned short FontWidth;//字体宽度
16,//unsigned short FontHigh;
0,//index
6,//MaxCount
"textbox1",
"fast_knife.bmp",
(unsigned char *)NORMAL_KNIFE_DOWN_sdram
};


PICTUREBOX Fast_Knife_Picture_Dis=
{
PictureBox_Type,//unsigned char Type;
TRUE,//unsigned char Enabled;
TRUE,
FALSE,//unsigned char Focus
627,2,//MARK_LABEL_X+70,MARK_LABEL_Y,//LOCATION Location;	//定位
52,52,//SIZE Size; //总大小
(255<<16)+(255<<8),//unsigned int picturebkColor;
255,//unsigned int textboxSelectColor;
0,//unsigned int textColor;
None,//unsigned int textbkColor;	//背景色
16,//unsigned short FontWidth;//字体宽度
16,//unsigned short FontHigh;
0,//index
6,//MaxCount
"textbox1",
"fast_knife.bmp",
(unsigned char *)NORMAL_KNIFE_UP_sdram
};





PICTUREBOX Manual_Knife_Picture_Enb=
{
PictureBox_Type,//unsigned char Type;
TRUE,//unsigned char Enabled;
TRUE,
FALSE,//unsigned char Focus
CHANGE_KNIFE_WIN_WIDE/4+CHANGE_KNIFE_WIN_X,CHANGE_KNIFE_WIN_Y+CHANGE_KNIFE_WIN_HIGH/2-50,//LOCATION Location;	//定位
99,92,//SIZE Size; //总大小
(255<<16)+(255<<8),//unsigned int picturebkColor;
255,//unsigned int textboxSelectColor;
0,//unsigned int textColor;
None,//unsigned int textbkColor;	//背景色
16,//unsigned short FontWidth;//字体宽度
16,//unsigned short FontHigh;
0,//index
6,//MaxCount
"textbox1",
"ManualKnifeChange.bmp",
(unsigned char *)MANUAL_KNIFE_DOWN_sdram
};


PICTUREBOX Manual_Knife_Picture_Dis=
{
PictureBox_Type,//unsigned char Type;
TRUE,//unsigned char Enabled;
TRUE,
FALSE,//unsigned char Focus
CHANGE_KNIFE_WIN_WIDE/4+CHANGE_KNIFE_WIN_X,CHANGE_KNIFE_WIN_Y+CHANGE_KNIFE_WIN_HIGH/2-50,//LOCATION Location;	//定位
99,92,//SIZE Size; //总大小
(255<<16)+(255<<8),//unsigned int picturebkColor;
255,//unsigned int textboxSelectColor;
0,//unsigned int textColor;
None,//unsigned int textbkColor;	//背景色
16,//unsigned short FontWidth;//字体宽度
16,//unsigned short FontHigh;
0,//index
6,//MaxCount
"textbox1",
"ManualKnifeChange.bmp",
(unsigned char *)MANUAL_KNIFE_UP_sdram
};


PICTUREBOX Normal_Knife_Picture_Enb=
{
PictureBox_Type,//unsigned char Type;
TRUE,//unsigned char Enabled;
TRUE,
FALSE,//unsigned char Focus
CHANGE_KNIFE_WIN_WIDE/4+CHANGE_KNIFE_WIN_X+CHANGE_KNIFE_WIN_WIDE/4,CHANGE_KNIFE_WIN_Y+CHANGE_KNIFE_WIN_HIGH/2-50,//LOCATION Location;	//定位
99,92,//SIZE Size; //总大小
(255<<16)+(255<<8),//unsigned int picturebkColor;
255,//unsigned int textboxSelectColor;
0,//unsigned int textColor;
None,//unsigned int textbkColor;	//背景色
16,//unsigned short FontWidth;//字体宽度
16,//unsigned short FontHigh;
0,//index
6,//MaxCount
"textbox1",
"NormalKnifeChange.bmp",
(unsigned char *)NORMAL_KNIFE_DOWN_sdram
};


PICTUREBOX Normal_Knife_Picture_Dis=
{
PictureBox_Type,//unsigned char Type;
TRUE,//unsigned char Enabled;
TRUE,
FALSE,//unsigned char Focus
CHANGE_KNIFE_WIN_WIDE/4+CHANGE_KNIFE_WIN_X+CHANGE_KNIFE_WIN_WIDE/4,CHANGE_KNIFE_WIN_Y+CHANGE_KNIFE_WIN_HIGH/2-50,//LOCATION Location;	//定位
99,92,//SIZE Size; //总大小
(255<<16)+(255<<8),//unsigned int picturebkColor;
255,//unsigned int textboxSelectColor;
0,//unsigned int textColor;
None,//unsigned int textbkColor;	//背景色
16,//unsigned short FontWidth;//字体宽度
16,//unsigned short FontHigh;
0,//index
6,//MaxCount
"textbox1",
"NormalKnifeChange.bmp",
(unsigned char *)NORMAL_KNIFE_UP_sdram
};

PICTUREBOX Motor_Knife_Picture_Enb=
{
PictureBox_Type,//unsigned char Type;
TRUE,//unsigned char Enabled;
TRUE,
FALSE,//unsigned char Focus
CHANGE_KNIFE_WIN_WIDE/4+CHANGE_KNIFE_WIN_X+CHANGE_KNIFE_WIN_WIDE/4+CHANGE_KNIFE_WIN_WIDE/4,CHANGE_KNIFE_WIN_Y+CHANGE_KNIFE_WIN_HIGH/2-50,//LOCATION Location;	//定位
99,92,//SIZE Size; //总大小
(255<<16)+(255<<8),//unsigned int picturebkColor;
255,//unsigned int textboxSelectColor;
0,//unsigned int textColor;
None,//unsigned int textbkColor;	//背景色
16,//unsigned short FontWidth;//字体宽度
16,//unsigned short FontHigh;
0,//index
6,//MaxCount
"textbox1",
"MotorKnifeChange.bmp",
(unsigned char *)ELECTRIC_KNIFE_DOWN_sdram
};


PICTUREBOX Motor_Knife_Picture_Dis=
{
PictureBox_Type,//unsigned char Type;
TRUE,//unsigned char Enabled;
TRUE,
FALSE,//unsigned char Focus
CHANGE_KNIFE_WIN_WIDE/4+CHANGE_KNIFE_WIN_X+CHANGE_KNIFE_WIN_WIDE/4+CHANGE_KNIFE_WIN_WIDE/4,CHANGE_KNIFE_WIN_Y+CHANGE_KNIFE_WIN_HIGH/2-50,//LOCATION Location;	//定位
99,92,//SIZE Size; //总大小
(255<<16)+(255<<8),//unsigned int picturebkColor;
255,//unsigned int textboxSelectColor;
0,//unsigned int textColor;
None,//unsigned int textbkColor;	//背景色
16,//unsigned short FontWidth;//字体宽度
16,//unsigned short FontHigh;
0,//index
6,//MaxCount
"textbox1",
"MotorKnifeChange.bmp",
(unsigned char *)ELECTRIC_KNIFE_UP_sdram
};



PICTUREBOX Wind_Motor_Picture_Enb=
{
PictureBox_Type,//unsigned char Type;
TRUE,//unsigned char Enabled;
TRUE,
FALSE,//unsigned char Focus
684,2,//LOCATION Location;	//定位
52,52,//SIZE Size; //总大小
(255<<16)+(255<<8),//unsigned int picturebkColor;
255,//unsigned int textboxSelectColor;
0,//unsigned int textColor;
None,//unsigned int textbkColor;	//背景色
16,//unsigned short FontWidth;//字体宽度
16,//unsigned short FontHigh;
0,//index
6,//MaxCount
"textbox1",
"motor_knife_dis.bmp",
(unsigned char *)PUMP_ON_UP_sdram
};


PICTUREBOX Wind_Motor_Picture_Dis=
{
PictureBox_Type,//unsigned char Type;
TRUE,//unsigned char Enabled;
TRUE,
FALSE,//unsigned char Focus
684,2,//MARK_LABEL_X,MARK_LABEL_Y+42,//LOCATION Location;	//定位//PUMP_OFF_X,PUMP_OFF_Y,//LOCATION Location;	//定位
52,52,//SIZE Size; //总大小
(255<<16)+(255<<8),//unsigned int picturebkColor;
255,//unsigned int textboxSelectColor;
0,//unsigned int textColor;
None,//unsigned int textbkColor;	//背景色
16,//unsigned short FontWidth;//字体宽度
16,//unsigned short FontHigh;
0,//index
6,//MaxCount
"textbox1",
"motor_knife_dis.bmp",
(unsigned char *)PUMP_OFF_UP_sdram
};


#define LAMP_PIC_W 52
#define LAMP_PIC_H 52

PICTUREBOX Lamp_Picture_Enb=
{
PictureBox_Type,//unsigned char Type;
TRUE,//unsigned char Enabled;
TRUE,
FALSE,//unsigned char Focus
741,2,//LOCATION Location;	//定位
LAMP_PIC_W,LAMP_PIC_H,//SIZE Size; //总大小
(255<<16)+(255<<8),//unsigned int picturebkColor;
255,//unsigned int textboxSelectColor;
0,//unsigned int textColor;
None,//unsigned int textbkColor;	//背景色
16,//unsigned short FontWidth;//字体宽度
16,//unsigned short FontHigh;
0,//index
6,//MaxCount
"textbox1",
"灯光开.bmp",
(unsigned char *)LIGHT_LED_DOWN_sdram
};


PICTUREBOX Lamp_Picture_Dis=
{
PictureBox_Type,//unsigned char Type;
TRUE,//unsigned char Enabled;
TRUE,
FALSE,//unsigned char Focus
	
741,2,//LOCATION Location;	//定位
	
LAMP_PIC_W,LAMP_PIC_H,//SIZE Size; //总大小
(255<<16)+(255<<8),//unsigned int picturebkColor;
255,//unsigned int textboxSelectColor;
0,//unsigned int textColor;
None,//unsigned int textbkColor;	//背景色
16,//unsigned short FontWidth;//字体宽度
16,//unsigned short FontHigh;
0,//index
6,//MaxCount
"textbox1",
"灯光关.bmp",
(unsigned char *)LIGHT_LED_UP_sdram
};


////////PICTUREBOX IR_ReadLine_Picture=
////////{
////////PictureBox_Type,//unsigned char Type;
////////TRUE,//unsigned char Enabled;
////////TRUE,
////////FALSE,//unsigned char Focus
////////IR_X,IR_Y,//LOCATION Location;	//定位
////////100,550,//LED_BUTT_W,LED_BUTT_H,//SIZE Size; //总大小
////////(255<<16)+(255<<8),//unsigned int picturebkColor;
////////255,//unsigned int textboxSelectColor;
////////0,//unsigned int textColor;
////////None,//unsigned int textbkColor;	//背景色
////////16,//unsigned short FontWidth;//字体宽度
////////16,//unsigned short FontHigh;
////////0,//index
////////6,//MaxCount
////////"textbox1",
////////"红线.bmp",
////////IR_LINE_sdram
////////};


////////PICTUREBOX IR_Handle_Picture=
////////{
////////PictureBox_Type,//unsigned char Type;
////////TRUE,//unsigned char Enabled;
////////TRUE,
////////FALSE,//unsigned char Focus
////////IR_X,IR_Y,//LOCATION Location;	//定位
////////100,550,//LED_BUTT_W,LED_BUTT_H,//SIZE Size; //总大小
////////(255<<16)+(255<<8),//unsigned int picturebkColor;
////////255,//unsigned int textboxSelectColor;
////////0,//unsigned int textColor;
////////None,//unsigned int textbkColor;	//背景色
////////16,//unsigned short FontWidth;//字体宽度
////////16,//unsigned short FontHigh;
////////0,//index
////////6,//MaxCount
////////"textbox1",
////////"手红外.bmp",
////////IR_CUT_sdram
////////};


//////////PICTUREBOX Pressure_Set_Picture=
//////////{
//////////PictureBox_Type,//unsigned char Type;
//////////TRUE,//unsigned char Enabled;
//////////TRUE,
//////////FALSE,//unsigned char Focus
//////////640,2,//MARK_LABEL_X+70,MARK_LABEL_Y+50,//LOCATION Location;	//定位
//////////52,52,//SIZE Size; //总大小
//////////	
//////////(255<<16)+(255<<8),//unsigned int picturebkColor;
//////////255,//unsigned int textboxSelectColor;
//////////0,//unsigned int textColor;
//////////None,//unsigned int textbkColor;	//背景色
//////////16,//unsigned short FontWidth;//字体宽度
//////////16,//unsigned short FontHigh;
//////////0,//index
//////////6,//MaxCount
//////////"textbox1",
//////////"转速.bmp",
//////////PRESSURE_SET_Set_sdram
//////////};


LABEL PLCMachineLabel={Label_Type,
							TRUE,
							100,100,
						128,24,	
						0,
						None,
						24,24,
					"3 伺服+PLC模式"
					};	

					
LABEL PLC_DT0SetLabel={Label_Type,
							TRUE,
							100,100,
						42,24,	
						0,
						None,
						24,24,
					"启动时间DT0:"
					};	

LABEL PLC_DT1SetLabel={Label_Type,
							TRUE,
							100,100,
						42,24,	
						0,
						None,
						24,24,
					"下刀时间DT1:"
					};	

	
LABEL PLC_OptimizeCut_DelayTime_SetLabel={Label_Type,
							TRUE,
							100,100,
						42,24,	
						0,
						None,
						24,24,
					"优化时间:"
					};	

					LABEL PLC_OptimizeCut_DelayTime_DataLabel={Label_Type,
							TRUE,
							100,100,
						42,24,	
						0,
						None,
						24,24,
					""
					};	
					
					
LABEL PLC_OptimizeCut_Label={Label_Type,
							TRUE,
							100,100,
						42,24,	
						0,
						None,
						24,24,
					"优化裁切:"
					};	

LABEL PLC_OptimizeCut_Select_Label={Label_Type,
							TRUE,
							100,100,
						42,24,	
						0,
						None,
						24,24,
					"关"
					};						
					
					
LABEL PLC_FastCut_Label={Label_Type,
							TRUE,
							100,100,
						42,24,	
						0,
						None,
						24,24,
					"快速裁切:"
					};	

LABEL PLC_FastCut_Select_Label={Label_Type,
							TRUE,
							100,100,
						42,24,	
						0,
						None,
						24,24,
					"关"
					};					
					
					
BUTTON PLC_OptimizeCut_Select_BT={Button_Type,\
								TRUE,
								100,56+100,\
								160,36,\
								(240<<16)+(240<<8)+240,\
								24,\
								24,
								"优化裁切打开"};


LABEL PLC_DT3SetLabel={Label_Type,
							TRUE,
							100,100,
						42,24,	
						0,
						None,
						24,24,
					"压力调节DT3:"
					};	

LABEL PLC_DT4SetLabel={Label_Type,
							TRUE,
							100,100,
						42,24,	
						0,
						None,
						24,24,
					"最小电压DT4:"
					};

LABEL PLC_DT5SetLabel={Label_Type,
							TRUE,
							100,100,
						42,24,	
						0,
						None,
						24,24,
					"最大电压DT5:"
					};

					


					
LABEL PLC_DT0DataLabel={Label_Type,
							TRUE,
							100,100,
						42,24,	
						0,
						None,
						24,24,
					"80"//下刀时间 5*0.1S  0.5秒
					};	

LABEL PLC_DT1DataLabel={Label_Type,
							TRUE,
							100,100,
						42,24,	
						0,
						None,
						24,24,
					"0"//启动时间 80*0.1S  8秒
					};	

LABEL PLC_DT3DataLabel={Label_Type,
							TRUE,
							100,100,
						42,24,	
						0,
						None,
						24,24,
					"0"
					};	

LABEL PLC_DT4DataLabel={Label_Type,
							TRUE,
							100,100,
						42,24,	
						0,
						None,
						24,24,
					"0"
					};

LABEL PLC_DT5DataLabel={Label_Type,
							TRUE,
							100,100,
						42,24,	
						0,
						None,
						24,24,
					"0"
					};


#ifdef PLC_3U
LABEL PLC_SET_DT3SetLabel={Label_Type,
							TRUE,
							512-120-112-100,380-100,
						42,24,	
						0,
						None,
						24,24,
					"裁切压力:"
					};

LABEL PLC_SET_Foot_DT3SetLabel={Label_Type,
							TRUE,
							512-120-112-100,380-100+60,
						42,24,	
						0,
						None,
						24,24,
					"脚踩压力:"
					};
#else

LABEL PLC_SET_DT3SetLabel={Label_Type,
							TRUE,
							512-160,380-100,
						42,24,	
						0,
						None,
						24,24,
					"压力调节DT3:"
					};
#endif
					
					
LABEL PLC_SET_DT3DataLabel={Label_Type,
							TRUE,
							512+10-80-150,380-100,
						50,24,	
						0,
						0xffff00,
						24,24,
					"0"
					};	

					
LABEL PLC_SET_Foot_DT3DataLabel={Label_Type,
							TRUE,
							512+10-80-150,380-100+60,
						50,24,	
						0,
						0xffff00,
						24,24,
					"0"
					};	

					
LABEL FX_Plc_YaZhi_RunDataLabel={Label_Type,
							TRUE,
							512+10,380-100,
						80,24,	
						0,
						0xffff00,
						24,24,
					"0"
					};				

										//	x=PARA_START_X1+PARA_COL_WIDE,y=PARA_START_Y,gap=PARA_ROW_GAP;
//设置星三角启动时间			
LABEL FX_Plc_Set_MotorStartUpTime_Label={Label_Type,
							TRUE,
							PARA_START_X1+PARA_COL_WIDE,PARA_START_Y,
						80,24,	
						0,
						0xe8ece8,
						24,24,
				"电机启动时间:"
					};	

//设定启动时间
LABEL FX_Plc_Set_MotorStartUpTime_Data_Label={Label_Type,
							TRUE,
							PARA_START_X1+PARA_COL_WIDE+160,PARA_START_Y,
						50,24,	
						0,
						0xe8ece8,
						24,24,
					"16"
					};	
					
//设置星三角停止时间			
LABEL FX_Plc_Set_MotorStopTime_Label={Label_Type,
							TRUE,
							PARA_START_X1+PARA_COL_WIDE,PARA_START_Y+4*PARA_ROW_GAP,
						80,24,	
						0,
						0xe8ece8,
						24,24,
					"电机停止时间:"
					};	

					//设定停止时间
LABEL FX_Plc_Set_MotorStopTime_Data_Label={Label_Type,
							TRUE,
							PARA_START_X1+PARA_COL_WIDE+160,PARA_START_Y+4*PARA_ROW_GAP,
						50,24,	
						0,
						0xe8ece8,
						24,24,
					"121"
					};	
					
//设置下刀时间		
LABEL FX_Plc_Set_KnifeDownTime_Label={Label_Type,
							TRUE,
							PARA_START_X1+PARA_COL_WIDE,PARA_START_Y+2*PARA_ROW_GAP,
						80,24,	
						0,
						0xe8ece8,
						24,24,
				"下刀时间:"
					};	

					//设定下刀时间
					LABEL FX_Plc_Set_KnifeDownTime_Data_Label={Label_Type,
							TRUE,
							PARA_START_X1+PARA_COL_WIDE+160,PARA_START_Y+2*PARA_ROW_GAP,
						50,24,	
						0,
						0xe8ece8,
						24,24,
				"5"
					};	
					
//设置裁切优化		
LABEL FX_Plc_Set_CutOpt_Label={Label_Type,
							TRUE,
							PARA_START_X1+PARA_COL_WIDE,PARA_START_Y+3*PARA_ROW_GAP,
						80,24,	
						0,
						0xe8ece8,
						24,24,
				"裁切优化:"
					};	

		//设定裁切优化开关			
LABEL FX_Plc_Set_CutOpt_Data_Label={Label_Type,
							TRUE,
							PARA_START_X1+PARA_COL_WIDE+160,PARA_START_Y+3*PARA_ROW_GAP,
						50,24,	
						0,
						0xe8ece8,
						24,24,
				"关闭"
					};

					
//设置裁切优化时间	
LABEL FX_Plc_Set_CutTime_Label={Label_Type,
							TRUE,
							PARA_START_X1+PARA_COL_WIDE,PARA_START_Y+4*PARA_ROW_GAP,
						80,24,	
						0,
						0xe8ece8,
						24,24,
				"优化时间:"
					};	

				//设定优化时间  	
					LABEL FX_Plc_Set_CutTime_Data_Label={Label_Type,
							TRUE,
							PARA_START_X1+PARA_COL_WIDE+160,PARA_START_Y+4*PARA_ROW_GAP,
						50,24,	
						0,
						0xe8ece8,
						24,24,
				"5"
					};	
					
					
//设置快速度裁切	
LABEL FX_Plc_Set_FastCut_Enb_Label={Label_Type,
							TRUE,
							PARA_START_X1+PARA_COL_WIDE,PARA_START_Y+5*PARA_ROW_GAP,
						80,24,	
						0,
						0xe8ece8,
						24,24,
				"快速裁切:"
					};	

					//设定快速度裁切 开关
LABEL FX_Plc_Set_FastCut_Enb_Data_Label={Label_Type,
							TRUE,
							PARA_START_X1+PARA_COL_WIDE+160,PARA_START_Y+5*PARA_ROW_GAP,
						50,24,	
						0,
						0xe8ece8,
						24,24,
				"关闭"
					};	

					
					//设定快速度裁切 开关
LABEL FX_Plc_ChangeKnife_Hint_Label={Label_Type,
							TRUE,
							CHANGE_KNIFE_WIN_X+80,CHANGE_KNIFE_WIN_Y+CHANGE_KNIFE_WIN_HIGH/2-100,
						50,24,	
						0xff0000,
						0xffFF00,
						24,24,
				   "注意：请选择换刀，高度危险!!!"
					};	

					
					
					
//Printf24("注意：请选择换刀，高度危险!!!",CHANGE_KNIFE_WIN_X+80,CHANGE_KNIFE_WIN_Y+CHANGE_KNIFE_WIN_HIGH/2-100,RED_COLOR,0,0xffff);	
					
//脚踩压力					
BUTTON PLC_Foot_Pressure_SET_UP_BT={Button_Type,\
								TRUE,
								512-130+32,380-100+60-10,
								80,36,\
								(240<<16)+(240<<8)+240,\
								16,\
								32,
								"+0.1"};

								
BUTTON PLC_Foot_Pressure_SET_DOWN_BT={Button_Type,\
								TRUE,
								512+120-130+32,380-100+60-10,
								80,36,\
								(240<<16)+(240<<8)+240,\
								16,\
								32,
								"-0.1"};

								
//裁切压力					
BUTTON PLC_Pressure_SET_UP_BT={Button_Type,\
								TRUE,
								512-130+32,380-100-10,
								80,36,\
								(240<<16)+(240<<8)+240,\
								16,\
								32,
								"+0.1"};

								
BUTTON PLC_Pressure_SET_DOWN_BT={Button_Type,\
								TRUE,
								512+120-130+32,380-100-10,
								80,36,\
								(240<<16)+(240<<8)+240,\
								16,\
								32,
								"-0.1"};

								
BUTTON PLC_Pressure_SET_EXIT_BT={Button_Type,\
								TRUE,
								512+10+120+10-200+60,380+16,\
								100,36,\
								(240<<16)+(240<<8)+240,\
								16,\
								32,
								"Exit"};				

								
BUTTON PLC_YaZhi_SET_EXIT_BT={Button_Type,\
								TRUE,
								YAZHI_PROCESS_WIN_X+YAZHI_PROCESS_WIN_WIDE-55,YAZHI_PROCESS_WIN_Y+YAZHI_PROCESS_WIN_HIGH-38,\
								50,36,\
								(240<<16)+(240<<8)+240,\
								16,\
								32,
								"X"};									

					
unsigned char Normal_Knife_Status=0;
unsigned char MainPower_Status=0;
unsigned char Manual_Knife_Status=0;
unsigned char Fast_Knife_Status=0;
unsigned char Motor_Knife_Status=0;								
unsigned char Knife_Change_Status=0;
								
unsigned char Wind_Motor_Status=0;//风泵

unsigned char Lamp_Status=0;
					
unsigned char PLC_Enb_Flag=0;
					
unsigned char Pressure_Set_Status=0;
								
								
unsigned int Foot_Pressure_Set_Data=0;
								
unsigned int Pressure_Set_Data=0;
								
								
////////uint8_t Machine_Set_UserCount_Flag=0;
////////uint32_t Machine_Set_UserCount_Time=0;

unsigned char Modbus_Motion_Set_LuoJu=1;
unsigned char Modbus_Motion_Set_ChiLunBi=1;
unsigned int YaZhiYaLi_Data=0;
unsigned int yazhiyali_data_temp=10000;

void Plc_Ext_Form_Init(void)
{
//cpGui_CreatePictureBox(&Manual_Knife_Picture_Enb);	
	

//PowerBlack_dis( MAIN_PWR_CTRL_X, MAIN_PWR_CTRL_Y);//电源黑	
//cpGui_CreatePictureBox(&Main_PowerOff_Picture_Dis);
	
//cpGui_CreatePictureBox(&Manual_Knife_Picture_Dis);
//cpGui_CreatePictureBox(&Fast_Knife_Picture_Enb);

//cpGui_CreatePictureBox(&Motor_Knife_Picture_Enb);
//cpGui_CreatePictureBox(&Motor_Knife_Picture_Dis);
	


	
cpGui_CreatePictureBox(&Main_PowerOn_Picture_Dis);	
	
//Fast_Knife_Picture_Dis.picAdder=LIGHT_LED_DOWN_sdram;
cpGui_CreatePictureBox(&Fast_Knife_Picture_Dis);	
cpGui_CreatePictureBox(&Wind_Motor_Picture_Dis);		
cpGui_CreatePictureBox(&Lamp_Picture_Dis);//灯光关	//cpGui_CreatePictureBox(&Lamp_Picture_Enb);		
////////cpGui_CreatePictureBox(&Pressure_Set_Picture);//压力设置	
////////cpGui_CreatePictureBox(&IR_ReadLine_Picture);//显示红外线
	
}


unsigned char  Fx_Plc_Dao_DelayTime=0;

void FX_PLC_Check_IO_Status(void)
{
//////////if(FX_PLC_PowerOn_Init_Flag==1)
//////////{
//////////	FX_PLC_Ori_Status=1;
//////////	FX_PLC_TuoBan_Status=1;
//////////	FX_PLC_YaZhi_Status=1;
//////////	FX_PLC_Dao_Status=1;
//////////	FX_PLC_FLimit_Status=1;
//////////	FX_PLC_BLimit_Status=1;
//////////	FX_PLC_MLimit_Status=1;
//////////	FX_PLC_YaLi_Status=1;
//////////	FX_PLC_YaLiSel_Status=1;
//////////	return;
//////////}



//////////if(PLC_X_Status[2][4]==PLC_IO_OFF)
//////////{
//////////	FX_PLC_Ori_Status=0;
//////////	
//////////}
//////////else
//////////{
//////////	FX_PLC_Ori_Status=1;
//////////}





//////////if(PLC_X_Status[2][5]==PLC_IO_OFF)
//////////{
//////////	FX_PLC_TuoBan_Status=1;
//////////	
//////////}
//////////else
//////////{
//////////	FX_PLC_TuoBan_Status=0;
//////////}
//////////	

//////////if(PLC_X_Status[2][6]==PLC_IO_OFF)
//////////{
//////////	FX_PLC_YaZhi_Status=0;
//////////	
//////////}
//////////else
//////////{
//////////	FX_PLC_YaZhi_Status=1;
//////////}




//////////if(	FX_PLC_Dao_Status==0)
//////////{
//////////	
//////////	if(PLC_X_Status[2][7]!=PLC_IO_OFF)
//////////	{
//////////		Fx_Plc_Dao_DelayTime++;
//////////		if(Fx_Plc_Dao_DelayTime>=30)
//////////		{
//////////			Fx_Plc_Dao_DelayTime=0;
//////////			FX_PLC_Dao_Status=1;
//////////		}
//////////	}
//////////else
//////////	Fx_Plc_Dao_DelayTime=0;
//////////	
//////////}
//////////else
//////////{
//////////	
//////////if(PLC_X_Status[2][7]==PLC_IO_OFF)
//////////	{
//////////		Fx_Plc_Dao_DelayTime++;
//////////		if(Fx_Plc_Dao_DelayTime>=30)
//////////		{
//////////			Fx_Plc_Dao_DelayTime=0;
//////////			FX_PLC_Dao_Status=0;
//////////		}
//////////	}
//////////else
//////////	Fx_Plc_Dao_DelayTime=0;
//////////	
//////////}

//////////////////if(PLC_X_Status[2][7]==PLC_IO_OFF)
//////////////////{
//////////////////	FX_PLC_Dao_Status=0;
//////////////////	
//////////////////}
//////////////////else
//////////////////{
//////////////////	FX_PLC_Dao_Status=1;
//////////////////}

////////////前极限

//////////if(PLC_X_Status[2][2]==PLC_IO_OFF)
//////////{
//////////	FX_PLC_FLimit_Status=0;
//////////	
//////////}
//////////else
//////////{
//////////	FX_PLC_FLimit_Status=1;
//////////}

////////////后极限
//////////if(PLC_X_Status[2][3]==PLC_IO_OFF)
//////////{
//////////	FX_PLC_BLimit_Status=0;
//////////	
//////////}
//////////else
//////////{
//////////	FX_PLC_BLimit_Status=1;
//////////}


////////////中极限
//////////if(PLC_X_Status[3][0]==PLC_IO_OFF)
//////////{
//////////	FX_PLC_MLimit_Status=0;
//////////	
//////////}
//////////else
//////////{
//////////	FX_PLC_MLimit_Status=1;
//////////}
//////////	

////////////压力输入
//////////if(PLC_X_Status[3][1]==PLC_IO_OFF)
//////////{
//////////	FX_PLC_YaLi_Status=0;
//////////	
//////////}
//////////else
//////////{
//////////	FX_PLC_YaLi_Status=1;
//////////}


////////////压力选择
//////////if(PLC_X_Status[3][2]==PLC_IO_OFF)
//////////{
//////////	FX_PLC_YaLiSel_Status=0;
//////////	
//////////}
//////////else
//////////{
//////////	FX_PLC_YaLiSel_Status=1;
//////////}


}



void Plc_Form_DisUpdata(void)
{	
//////if(WorkStart_flag==1)//if(FormActive[0]==PLC_SET_FORM_SHOW)
//////	{

//////	if(Plc_X_Status[HW_IR_IN_BUFADD][0]==PLC_IR_OFF)   //如果第一路光藕输入为高?
//////		{	
//////		cpGui_CreatePictureBox(&IR_ReadLine_Picture);//显示红外线
//////		}
//////	else
//////		{	
//////		cpGui_CreatePictureBox(&IR_Handle_Picture);//显示手红线
//////		}		
//////	}	
}



//系统设置里的PLC参数 画面显示
void Plc_Ext_PlcSeting_Init_Disp(int x,int y)
{
int gap=PARA_ROW_GAP;
	
////////////	
////////////	
////////////		#ifdef PLC_3U
//////////////if(PLC_Enb_Flag==PLC_ENB)
////////////	{				
////////////	//DT0
////////////	PLC_DT0SetLabel.Location.x=x;							
////////////	PLC_DT0SetLabel.Location.y=y;

////////////	cpGui_CreateLabel(PLC_DT0SetLabel);
////////////	
////////////	PLC_DT0DataLabel.Location.x=PARA_START_X2;							
////////////	PLC_DT0DataLabel.Location.y=y;
////////////	sprintf(PLC_DT0DataLabel.Text,"%d",Plc_DT_Data_t[0]);	
////////////	cpGui_CreateLabel(PLC_DT0DataLabel);
////////////	y+=gap;	
////////////		
////////////	//DT1
////////////	PLC_DT1SetLabel.Location.x=x;							
////////////	PLC_DT1SetLabel.Location.y=y;
////////////	cpGui_CreateLabel(PLC_DT1SetLabel);
////////////	
////////////	PLC_DT1DataLabel.Location.x=PARA_START_X2;							
////////////	PLC_DT1DataLabel.Location.y=y;
////////////	sprintf(PLC_DT1DataLabel.Text,"%d",Plc_DT_Data_t[1]);			
////////////	cpGui_CreateLabel(PLC_DT1DataLabel);
////////////	y+=gap;	
////////////		
////////////		
////////////		
////////////	//优化裁切  延时时间
////////////	PLC_OptimizeCut_DelayTime_SetLabel.Location.x=x;							
////////////	PLC_OptimizeCut_DelayTime_SetLabel.Location.y=y;
////////////	cpGui_CreateLabel(PLC_OptimizeCut_DelayTime_SetLabel);
////////////	
////////////	PLC_OptimizeCut_DelayTime_DataLabel.Location.x=PARA_START_X2;							
////////////	PLC_OptimizeCut_DelayTime_DataLabel.Location.y=y;
////////////	sprintf(PLC_OptimizeCut_DelayTime_DataLabel.Text,"%d",OptimizeCut_DelayTime);			
////////////	cpGui_CreateLabel(PLC_OptimizeCut_DelayTime_DataLabel);
////////////	y+=gap;	



////////////	//优化裁切  允许开关
////////////	PLC_OptimizeCut_Label.Location.x=x;							
////////////	PLC_OptimizeCut_Label.Location.y=y;
////////////	cpGui_CreateLabel(PLC_OptimizeCut_Label);
////////////	
////////////	PLC_OptimizeCut_Select_Label.Location.x=PARA_START_X2;							
////////////	PLC_OptimizeCut_Select_Label.Location.y=y;
////////////	if(OptimizeCut_Enb_Flag==0)
////////////		sprintf(PLC_OptimizeCut_Select_Label.Text,"关");
////////////	else
////////////		sprintf(PLC_OptimizeCut_Select_Label.Text,"开");
////////////	//sprintf(PLC_OptimizeCut_Select_Label.Text,"%d",OptimizeCut_DelayTime);			
////////////	cpGui_CreateLabel(PLC_OptimizeCut_Select_Label);
////////////	y+=gap;	
////////////	
////////////	
////////////	//快速裁切  允许开关
////////////	PLC_FastCut_Label.Location.x=x;							
////////////	PLC_FastCut_Label.Location.y=y;
////////////	cpGui_CreateLabel(PLC_FastCut_Label);
////////////	
////////////	PLC_FastCut_Select_Label.Location.x=PARA_START_X2;							
////////////	PLC_FastCut_Select_Label.Location.y=y;
////////////	if(FastCut_Enb_Flag==0)
////////////		sprintf(PLC_FastCut_Select_Label.Text,"关");
////////////	else
////////////		sprintf(PLC_FastCut_Select_Label.Text,"开");
////////////	//sprintf(PLC_OptimizeCut_Select_Label.Text,"%d",OptimizeCut_DelayTime);			
////////////	cpGui_CreateLabel(PLC_FastCut_Select_Label);
////////////	y+=gap;	
////////////	

//////////////////	//DT3
//////////////////	PLC_DT3SetLabel.Location.x=x;							
//////////////////	PLC_DT3SetLabel.Location.y=y;
//////////////////	cpGui_CreateLabel(PLC_DT3SetLabel);
//////////////////	
//////////////////	PLC_DT3DataLabel.Location.x=PARA_START_X2;							
//////////////////	PLC_DT3DataLabel.Location.y=y;
//////////////////	
//////////////////	sprintf(PLC_DT3DataLabel.Text,"%d",Plc_DT_Data_t[3]);		
//////////////////	cpGui_CreateLabel(PLC_DT3DataLabel);
//////////////////	y+=gap;	

//////////////////	//DT4
//////////////////	PLC_DT4SetLabel.Location.x=x;							
//////////////////	PLC_DT4SetLabel.Location.y=y;
//////////////////	cpGui_CreateLabel(PLC_DT4SetLabel);
//////////////////	
//////////////////	PLC_DT4DataLabel.Location.x=PARA_START_X2;							
//////////////////	PLC_DT4DataLabel.Location.y=y;
//////////////////	sprintf(PLC_DT4DataLabel.Text,"%d",Plc_DT_Data_t[4]);		
//////////////////	cpGui_CreateLabel(PLC_DT4DataLabel);
//////////////////	y+=gap;	

//////////////////	//DT5
//////////////////	PLC_DT5SetLabel.Location.x=x;							
//////////////////	PLC_DT5SetLabel.Location.y=y;
//////////////////	cpGui_CreateLabel(PLC_DT5SetLabel);
//////////////////	
//////////////////	PLC_DT5DataLabel.Location.x=PARA_START_X2;							
//////////////////	PLC_DT5DataLabel.Location.y=y;
//////////////////	sprintf(PLC_DT5DataLabel.Text,"%d",Plc_DT_Data_t[5]);		
//////////////////	cpGui_CreateLabel(PLC_DT5DataLabel);
//////////////////	y+=gap;		
////////////	}	
////////////	#endif
}


unsigned char Plc_Ext_PlcSeting_Select_ChangeData(unsigned char dp_index,Int32U indata)
{
//////////char str[12];
//////////	#ifdef PLC_3U
//////////	
////////////if(PLC_Enb_Flag==PLC_ENB)
//////////	{	
//////////	//indata/=100;
//////////	switch(dp_index)
//////////		{
//////////		case 2://启动时间
//////////				if((indata>=80)&&(indata<=200))
//////////				{
//////////				sprintf(PLC_DT0DataLabel.Text,"%d",indata);		
//////////				Plc_DT_Data_t[0]=indata;
//////////				Save_PLC_DT_Data((pInt8U)&Plc_DT_Data_t);//保存PLC DT 数据		
//////////				Plc_Send_DT_Data_Flag=1;		//DT数据变化，重发		
//////////				FX_PLC_PowerOn_Init_Flag=1; //DT数据变化，重发					
//////////				}
//////////			 else
//////////				return 1;
//////////				break;
//////////		case 3://下刀时间
//////////				if((indata>=2)&&(indata<=30))
//////////				{
//////////				sprintf(PLC_DT1DataLabel.Text,"%d",indata);	
//////////				
//////////				Plc_DT_Data_t[1]=indata;
//////////				Save_PLC_DT_Data((pInt8U)&Plc_DT_Data_t);//保存PLC DT 数据	
//////////					Plc_Send_DT_Data_Flag=1;		//DT数据变化，重发
//////////					
//////////					FX_PLC_PowerOn_Init_Flag=1; //DT数据变化，重发
//////////				}			
//////////			 else
//////////				return 1;				
//////////				break;
//////////		case 4://压力调节
//////////			
//////////					if((indata>=1)&&(indata<=10))
//////////						{	
//////////						sprintf(PLC_OptimizeCut_DelayTime_DataLabel.Text,"%d",indata);				
//////////						OptimizeCut_DelayTime=indata;
//////////						Plc_DT_Data_t[10]=OptimizeCut_DelayTime;  //Plc_DT_Data_t[10] 保存 优化裁切的延时时间数据
//////////						Save_PLC_DT_Data((pInt8U)&Plc_DT_Data_t);//保存PLC DT 数据	
//////////						Optimize_Cut_DelayTime_DownLoad_Flag=1;		//优化裁切延时有变化 重发
//////////						}			
//////////					else
//////////						return 1;
//////////				//}
////////////////	
////////////////				if((indata>=100)&&(indata<=1500))
////////////////				{
////////////////				sprintf(PLC_DT3DataLabel.Text,"%d",indata);				
////////////////				Plc_DT_Data_t[3]=indata;
////////////////				Save_PLC_DT_Data((pInt8U)&Plc_DT_Data_t);//保存PLC DT 数据	
////////////////				Plc_Send_DT_Data_Flag=1;		//DT数据变化，重发
////////////////				}			
////////////////				else
////////////////					return 1;
//////////				break;
//////////		case 5://最小电压
//////////				break;
//////////		case 6://最大电压
//////////				break;	
//////////		}
//////////	}
////////////	sprintf(str,"%d",indata);
////////////	Printf24(str,REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,BLACK_COLOR,0,0xffff);
//////////	
//////////Plc_Ext_PlcSeting_Select_Disp(dp_index);
//////////	
//////////	#endif
//////////	
//////////	return 0;
}


void Plc_Ext_PlcSeting_Hint_Disp(unsigned char num)
{
switch(num)
	{
	case 2://下刀时间
			switch(Language)
				{
				case CHN_HAN:
					Printf24("输入数据范围        到",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,BLACK_COLOR,0,0xffff);
					break;
				case ENGLISH:	
					Printf24("Data range          to ",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,BLACK_COLOR,0,0xffff);
					break;
				case INDONSIA:	//印尼
					Printf24("Rentang nilai      untuk",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,BLACK_COLOR,0,0xffff);
					break;
				case PORTUGAL:	//葡萄牙
					Printf16("Intervalo de dados           --",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,BLACK_COLOR,0,0xffff);
						break;
				case SPANISH: //西班牙
					Printf16("Rango de datos               --",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,BLACK_COLOR,0,0xffff);
						break;
				}
		//	if(Unit==UNIT_MM)
				Printf24("80          200",REMIND_WINDOW_X+200,REMIND_WINDOW_Y+5,RED_COLOR,0,0xffff);
		//	else
		//		Printf24("0           35",REMIND_WINDOW_X+200,REMIND_WINDOW_Y+5,RED_COLOR,0,0xffff);			
			break;
	case 3://启动时间
			switch(Language)
				{
				case CHN_HAN:
					Printf24("输入数据范围        到",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,BLACK_COLOR,0,0xffff);
					break;
				case ENGLISH:	
					Printf24("Data range          to ",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,BLACK_COLOR,0,0xffff);
					break;
				case INDONSIA:	//印尼
					Printf24("Rentang nilai      untuk",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,BLACK_COLOR,0,0xffff);
					break;
				case PORTUGAL:	//葡萄牙
					Printf16("Intervalo de dados           --",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,BLACK_COLOR,0,0xffff);
						break;
				case SPANISH: //西班牙
					Printf16("Rango de datos               --",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,BLACK_COLOR,0,0xffff);
						break;
				}
		//	if(Unit==UNIT_MM)
				Printf24("2          30",REMIND_WINDOW_X+200,REMIND_WINDOW_Y+5,RED_COLOR,0,0xffff);
		//	else
			//	Printf24("0           35",REMIND_WINDOW_X+200,REMIND_WINDOW_Y+5,RED_COLOR,0,0xffff);			
			break;
	case 4:  //优化裁切时间   //压力调节
			switch(Language)
				{
				case CHN_HAN:
					Printf24("输入数据范围        到",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,BLACK_COLOR,0,0xffff);
					break;
				case ENGLISH:	
					Printf24("Data range          to ",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,BLACK_COLOR,0,0xffff);
					break;
				case INDONSIA:	//印尼
					Printf24("Rentang nilai      untuk",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,BLACK_COLOR,0,0xffff);
					break;
				case PORTUGAL:	//葡萄牙
					Printf16("Intervalo de dados           --",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,BLACK_COLOR,0,0xffff);
						break;
				case SPANISH: //西班牙
					Printf16("Rango de datos               --",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,BLACK_COLOR,0,0xffff);
						break;
				}
			//if(Unit==UNIT_MM)
				Printf24("1         10",REMIND_WINDOW_X+200,REMIND_WINDOW_Y+5,RED_COLOR,0,0xffff);
		//	else
			//	Printf24("0           35",REMIND_WINDOW_X+200,REMIND_WINDOW_Y+5,RED_COLOR,0,0xffff);			
			break;	
				
			case 5:  //优化裁切时间   //压力调节
			switch(Language)
				{
				case CHN_HAN:
									Printf24("按<>打开/关闭优化裁切",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,BLACK_COLOR,0,0xffff);
									break;
								case ENGLISH:	
								case INDONSIA:	//印尼
								case PORTUGAL:	//葡萄牙
								case SPANISH: //西班牙
									Printf24("press <> change Optimize Cut",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,BLACK_COLOR,0,0xffff);
										break;
				}
			//if(Unit==UNIT_MM)
			//	Printf24("1         10",REMIND_WINDOW_X+200,REMIND_WINDOW_Y+5,RED_COLOR,0,0xffff);
		//	else
			//	Printf24("0           35",REMIND_WINDOW_X+200,REMIND_WINDOW_Y+5,RED_COLOR,0,0xffff);			
			break;	
				
			case 6:  //优化裁切时间   //压力调节
			switch(Language)
				{
				case CHN_HAN:
									Printf24("按<>打开/关闭快速裁切",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,BLACK_COLOR,0,0xffff);
									break;
								case ENGLISH:	
								case INDONSIA:	//印尼
								case PORTUGAL:	//葡萄牙
								case SPANISH: //西班牙
									Printf24("press <> change Fast Cut",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,BLACK_COLOR,0,0xffff);
										break;
				}
			//if(Unit==UNIT_MM)
			//	Printf24("1         10",REMIND_WINDOW_X+200,REMIND_WINDOW_Y+5,RED_COLOR,0,0xffff);
		//	else
			//	Printf24("0           35",REMIND_WINDOW_X+200,REMIND_WINDOW_Y+5,RED_COLOR,0,0xffff);			
			break;					
	}	
}



void Plc_Ext_PlcSeting_Select_Disp(unsigned char num)
{
int len;
	#ifdef PLC_3U
//if(PLC_Enb_Flag==PLC_ENB)
	{			
	if(num<1)
		return;
	
	Plc_Ext_PlcSeting_Hint_Disp(num);
	//DT0			
	PLC_DT0DataLabel.textColor=0;
	PLC_DT0DataLabel.bkColor=0xefedea;
			
	PLC_DT0DataLabel.Location.x=PARA_START_X2;							
	PLC_DT0DataLabel.Location.y=PARA_START_Y+2*PARA_ROW_GAP;
	//	cpGui_CreateLabel(PLC_DT0DataLabel);
	
				//DT1		
				PLC_DT1DataLabel.textColor=0;
				PLC_DT1DataLabel.bkColor=0xefedea;
		
				PLC_DT1DataLabel.Location.x=PARA_START_X2;							
				PLC_DT1DataLabel.Location.y=PARA_START_Y+3*PARA_ROW_GAP;
			//	cpGui_CreateLabel(PLC_DT1DataLabel);


	
				PLC_OptimizeCut_DelayTime_DataLabel.textColor=0;
				PLC_OptimizeCut_DelayTime_DataLabel.bkColor=0xefedea;
				PLC_OptimizeCut_DelayTime_DataLabel.Location.x=PARA_START_X2;							
				PLC_OptimizeCut_DelayTime_DataLabel.Location.y=PARA_START_Y+4*PARA_ROW_GAP;
				
				
				PLC_OptimizeCut_Select_Label.textColor=0;
				PLC_OptimizeCut_Select_Label.bkColor=0xefedea;
				PLC_OptimizeCut_Select_Label.Location.x=PARA_START_X2;							
				PLC_OptimizeCut_Select_Label.Location.y=PARA_START_Y+5*PARA_ROW_GAP;



				PLC_FastCut_Select_Label.textColor=0;
				PLC_FastCut_Select_Label.bkColor=0xefedea;
				PLC_FastCut_Select_Label.Location.x=PARA_START_X2;							
				PLC_FastCut_Select_Label.Location.y=PARA_START_Y+6*PARA_ROW_GAP;
				
				
				//DT3
				PLC_DT3DataLabel.textColor=0;
				PLC_DT3DataLabel.bkColor=0xefedea;
		
				PLC_DT3DataLabel.Location.x=PARA_START_X2;							
				PLC_DT3DataLabel.Location.y=PARA_START_Y+4*PARA_ROW_GAP;
			//	cpGui_CreateLabel(PLC_DT2DataLabel);
				
				//DT4
				PLC_DT4DataLabel.textColor=0;
				PLC_DT4DataLabel.bkColor=0xefedea;
		
				PLC_DT4DataLabel.Location.x=PARA_START_X2;							
				PLC_DT4DataLabel.Location.y=PARA_START_Y+5*PARA_ROW_GAP;
			//	cpGui_CreateLabel(PLC_DT3DataLabel);

				//DT5
				PLC_DT5DataLabel.textColor=0;
				PLC_DT5DataLabel.bkColor=0xefedea;
		
				PLC_DT5DataLabel.Location.x=PARA_START_X2;							
				PLC_DT5DataLabel.Location.y=PARA_START_Y+6*PARA_ROW_GAP;
				//cpGui_CreateLabel(PLC_DT4DataLabel);
				

			
	switch(num)
		{
			
			case 2:
				//DT0
			
				PLC_DT0DataLabel.textColor=0xffffff;
				PLC_DT0DataLabel.bkColor=0x0000ff;
			
			//	PLC_DT0DataLabel.Location.x=PARA_START_X2;							
			//	PLC_DT0DataLabel.Location.y=PARA_START_Y+num*PARA_ROW_GAP;
				//cpGui_CreateLabel(PLC_DT0DataLabel);
					
				break;
			case 3:
				//DT1
				PLC_DT1DataLabel.textColor=0xffffff;
				PLC_DT1DataLabel.bkColor=0x0000ff;
			
			//	PLC_DT1DataLabel.Location.x=PARA_START_X2;							
			//	PLC_DT1DataLabel.Location.y=PARA_START_Y+num*PARA_ROW_GAP;
			//	cpGui_CreateLabel(PLC_DT1DataLabel);
					
			
					break;
			case 4:
				//DT3
			
				PLC_OptimizeCut_DelayTime_DataLabel.textColor=0xffffff;
				PLC_OptimizeCut_DelayTime_DataLabel.bkColor=0x0000ff;
		//		PLC_OptimizeCut_DelayTime_DataLabel.Location.x=PARA_START_X2;							
		//		PLC_OptimizeCut_DelayTime_DataLabel.Location.y=PARA_START_Y+7*PARA_ROW_GAP;

			
			//	PLC_DT3DataLabel.textColor=0xffffff;
			//	PLC_DT3DataLabel.bkColor=0x0000ff;
			
		//		PLC_DT2DataLabel.Location.x=PARA_START_X2;							
			//	PLC_DT2DataLabel.Location.y=PARA_START_Y+num*PARA_ROW_GAP;
			//	cpGui_CreateLabel(PLC_DT2DataLabel);
								
					break;
			case 5:
				//DT4
				PLC_OptimizeCut_Select_Label.textColor=0xffffff;
				PLC_OptimizeCut_Select_Label.bkColor=0x0000ff;
			
			//	PLC_DT3DataLabel.Location.x=PARA_START_X2;							
			//	PLC_DT3DataLabel.Location.y=PARA_START_Y+num*PARA_ROW_GAP;
			//	cpGui_CreateLabel(PLC_DT0DataLabel);
								
					break;
			case 6:
				//DT5
				PLC_FastCut_Select_Label.textColor=0xffffff;
				PLC_FastCut_Select_Label.bkColor=0x0000ff;
			
			//	PLC_DT4DataLabel.Location.x=PARA_START_X2;							
			//	PLC_DT4DataLabel.Location.y=PARA_START_Y+num*PARA_ROW_GAP;
			//	cpGui_CreateLabel(PLC_DT3DataLabel);
								
					break;
			case 7:
				//DT
				//PLC_DT4DataLabel.Location.x=PARA_START_X2;							
				//PLC_DT4DataLabel.Location.y=PARA_START_Y+num*PARA_ROW_GAP;
				//cpGui_CreateLabel(PLC_DT4DataLabel);								
				break;			
		}	
			cpGui_CreateLabel(PLC_DT0DataLabel);
			cpGui_CreateLabel(PLC_DT1DataLabel);
			cpGui_CreateLabel(PLC_OptimizeCut_DelayTime_DataLabel);		
			cpGui_CreateLabel(PLC_OptimizeCut_Select_Label);
		
			cpGui_CreateLabel(PLC_FastCut_Select_Label);
			//cpGui_CreateLabel(PLC_DT2DataLabel);
//			cpGui_CreateLabel(PLC_DT3DataLabel);
//			cpGui_CreateLabel(PLC_DT4DataLabel);
	//		cpGui_CreateLabel(PLC_DT5DataLabel);
	}	
	#endif
}

//////	if(OptimizeCut_Enb_Flag==0)
//////		sprintf(PLC_OptimizeCut_Select_Label.Text,"关");
//////	else
//////		sprintf(PLC_OptimizeCut_Select_Label.Text,"开");

void OptimizeCut_Select(unsigned char snum)
{
//////////if(snum==5)
//////////		{//优化裁切
//////////		if(OptimizeCut_Enb_Flag==0)
//////////				{
//////////				OptimizeCut_Enb_Flag=1;
//////////				sprintf(PLC_OptimizeCut_Select_Label.Text,"开");					
//////////				}	
//////////		else
//////////				{
//////////					OptimizeCut_Enb_Flag=0;
//////////					sprintf(PLC_OptimizeCut_Select_Label.Text,"关");					
//////////				}			
//////////		}
//////////else
//////////		{//快速裁切
//////////			if(snum==6)
//////////					{//   快速裁切  需要保存s
//////////						
//////////					if(FastCut_Enb_Flag==0)
//////////							{
//////////							FastCut_Enb_Flag=1;
//////////							sprintf(PLC_FastCut_Select_Label.Text,"开");									
//////////							}	
//////////					else
//////////							{
//////////								FastCut_Enb_Flag=0;
//////////								sprintf(PLC_FastCut_Select_Label.Text,"关");									
//////////							}		

//////////						Plc_DT_Data_t[11]=FastCut_Enb_Flag;								
//////////						Save_PLC_DT_Data((pInt8U)&Plc_DT_Data_t);//保存PLC DT 数据	
//////////					}
//////////		}
//////////Plc_Ext_PlcSeting_Select_Disp(Para2_sel);				
}




//压力设置处理
////////void Plc_Form_Pressure_Set_Process(void)
//////////{
//////////	
//////////					if(Pressure_Set_Status==0)
//////////				{//进入压力设置
//////////					CurrentArea_save1(PRESSURE_SET_WIN_X,PRESSURE_SET_WIN_Y, PRESSURE_SET_WIN_WIDE,PRESSURE_SET_WIN_HIGH-120);	
//////////					GLCD_SetWindow_Fill(PRESSURE_SET_WIN_X,PRESSURE_SET_WIN_Y,PRESSURE_SET_WIN_X+PRESSURE_SET_WIN_WIDE-1,PRESSURE_SET_WIN_Y+PRESSURE_SET_WIN_HIGH-1-120,YELLOW_COLOR,YELLOW_COLOR);//cpGui_ColorChange(cSystemColor),cpGui_ColorChange(cSystemColor));//.Location.x,label.Location.y,label.Location.x+label.Size.width,label.Location.y+label.Size.high,cpGui_ColorChange(label.bkColor),cpGui_ColorChange(label.bkColor));				
//////////					GLCD_SetWindow_Fill(PRESSURE_SET_WIN_X,PRESSURE_SET_WIN_Y,PRESSURE_SET_WIN_X+PRESSURE_SET_WIN_WIDE-1,PRESSURE_SET_WIN_Y+31,cpGui_ColorChange(255),cpGui_ColorChange(255));	
//////////					
//////////					
//////////					if(Language==CHN_HAN)
//////////					{
//////////						
//////////						
//////////					Printf24("压力设置",PRESSURE_SET_WIN_X+PRESSURE_SET_WIN_WIDE/2-24-4,PRESSURE_SET_WIN_Y+5,WHITE_COLOR,0,0xffff);
//////////					}
//////////					else
//////////					{
//////////						
//////////					Printf24("Pressure Seting",PRESSURE_SET_WIN_X+PRESSURE_SET_WIN_WIDE/2-60-4,PRESSURE_SET_WIN_Y+5,WHITE_COLOR,0,0xffff);
//////////					}
//////////							//Printf24("注意：快速换刀，高度危险!!!",CHANGE_KNIFE_WIN_X+80,CHANGE_KNIFE_WIN_Y+CHANGE_KNIFE_WIN_HIGH/2,RED_COLOR,0,0xffff);						
//////////					cpGui_CreateButton(&PLC_Pressure_SET_UP_BT);	
//////////					cpGui_CreateButton(&PLC_Pressure_SET_DOWN_BT);	
//////////					
//////////										cpGui_CreateButton(&PLC_Foot_Pressure_SET_UP_BT);	
//////////					cpGui_CreateButton(&PLC_Foot_Pressure_SET_DOWN_BT);	
//////////					
//////////					
//////////					cpGui_CreateButton(&PLC_Pressure_SET_EXIT_BT);	
//////////					
//////////					#ifdef PLC_3U
//////////					Pressure_Set_Data=FX_Plc_PressureData;//Plc_DT_Data_t[3];
//////////					
//////////					Foot_Pressure_Set_Data=FX_Foot_Plc_PressureData;  //压力直接有效
//////////					
//////////					#else
//////////					Pressure_Set_Data=Plc_DT_Data_t[3];					
//////////					#endif

//////////					

//////////					sprintf(PLC_SET_DT3DataLabel.Text,"%.2f",((float)Pressure_Set_Data/100));	
//////////					sprintf(PLC_SET_Foot_DT3DataLabel.Text,"%.2f",((float)Foot_Pressure_Set_Data/100));	
//////////					
//////////					
//////////					if(Language==CHN_HAN)
//////////					{
//////////					memcpy(PLC_SET_DT3SetLabel.Text,"裁切压力:",10);
//////////					cpGui_CreateLabel(PLC_SET_DT3SetLabel);
//////////					memcpy(PLC_SET_Foot_DT3SetLabel.Text,"脚踩压力:",10);
//////////					cpGui_CreateLabel(PLC_SET_Foot_DT3SetLabel);		
//////////						
//////////					}
//////////					else
//////////					{
//////////						
//////////					memcpy(PLC_SET_DT3SetLabel.Text,"Cut PR:",8);
//////////					cpGui_CreateLabel(PLC_SET_DT3SetLabel);
//////////						memcpy(PLC_SET_Foot_DT3SetLabel.Text,"Foot PR:",9);
//////////					cpGui_CreateLabel(PLC_SET_Foot_DT3SetLabel);						
//////////						
//////////					}
//////////					
//////////			
//////////					
//////////					cpGui_CreateLabel(PLC_SET_DT3DataLabel);
//////////					cpGui_CreateLabel(PLC_SET_Foot_DT3DataLabel);
//////////									
//////////					Printf24("MPa         ",PLC_SET_DT3DataLabel.Location.x+64,PLC_SET_DT3DataLabel.Location.y,BLACK_COLOR,0,cpGui_ColorChange(PLC_HINT_DIS_BAK_COLOR));	
//////////					Printf24("MPa         ",PLC_SET_Foot_DT3DataLabel.Location.x+64,PLC_SET_Foot_DT3DataLabel.Location.y,BLACK_COLOR,0,cpGui_ColorChange(PLC_HINT_DIS_BAK_COLOR));	
//////////									
//////////								

//////////					#ifdef PRESSURE_CHANGE_DIS
//////////					
//////////					
//////////					float realpresure=((float)FX_Plc_PressureData-250.0)/2.5+370;
//////////					FX_Plc_Real_PressureData=realpresure;//发送转换后的压力


//////////					sprintf(PLC_SET_DT3DataLabel.Text,"%d",FX_Plc_Real_PressureData);	
//////////					Printf24(PLC_SET_DT3DataLabel.Text,PLC_SET_Foot_DT3DataLabel.Location.x+64,PLC_SET_Foot_DT3DataLabel.Location.y-120,BLACK_COLOR,1,YELLOW_COLOR);//
//////////					

//////////					
//////////					
//////////					
//////////							if(FX_Foot_Plc_PressureData>=140)
//////////						{
//////////					float	 realpresure=((float)FX_Foot_Plc_PressureData-140.0)/2.5+300;
//////////				  	FX_Plc_Foot_Real_PressureData=realpresure;//发送转换后的压力			
//////////							
//////////						}
//////////					else
//////////					{
//////////						if(FX_Foot_Plc_PressureData==130)
//////////						{
//////////							FX_Plc_Foot_Real_PressureData=295;
//////////						}
//////////						else
//////////							if(FX_Foot_Plc_PressureData==120)
//////////							{
//////////								FX_Plc_Foot_Real_PressureData=290;
//////////							}
//////////							else								
//////////							if(FX_Foot_Plc_PressureData==110)
//////////							{
//////////								FX_Plc_Foot_Real_PressureData=285;
//////////							}
//////////							else								
//////////							{
////////////////									if(FX_Foot_Plc_PressureData==110)
////////////////									{
////////////////										FX_Plc_Foot_Real_PressureData=300;	
////////////////									}
////////////////									else
//////////										FX_Plc_Foot_Real_PressureData=280;							
//////////							}						
//////////					}
//////////					
//////////					
//////////					sprintf(PLC_SET_DT3DataLabel.Text,"%d",FX_Plc_Foot_Real_PressureData);	
//////////					Printf24(PLC_SET_DT3DataLabel.Text,PLC_SET_Foot_DT3DataLabel.Location.x+64+80,PLC_SET_Foot_DT3DataLabel.Location.y-120,BLACK_COLOR,1,YELLOW_COLOR);//
//////////									

//////////					#endif

//////////					Pressure_Set_Status=1;
//////////				}
//////////				else
//////////				{//退出压力设置
//////////					CurrentArea_recover1(PRESSURE_SET_WIN_X,PRESSURE_SET_WIN_Y, PRESSURE_SET_WIN_WIDE,PRESSURE_SET_WIN_HIGH-120);
//////////					Pressure_Set_Status=0;
//////////					
//////////					#ifdef PLC_3U
//////////						FX_Plc_PressureData=	Pressure_Set_Data;//Plc_DT_Data_t[3];					
//////////					#else
//////////								
//////////					#endif
//////////					
//////////				}						
//////////}

unsigned char YaZhi_Process_Flag=0;




void YaZhi_Process(void)
{
////////////////{
////////////////int i=0;
////////////////	char strr[16];
////////////////	
////////////////if(YaZhi_Process_Flag==0)
////////////////		{
////////////////				YaZhi_Sensor_Status=0;
////////////////					App_Modbus_Plc_Write_M_Status(304,M_ON);	
////////////////			
////////////////			//	 if(App_FX_Plc_Force_Process("ON",M304)==0)
////////////////									{//退出时断开M305  进入时 闭合M304
////////////////										
////////////////									}
////////////////									
////////////////						YaZhi_Process_Flag=1;		
////////////////									
////////////////			//			cpGui_CreatePictureBox(&Fast_Knife_Picture_Enb);							
////////////////						CurrentArea_save1(YAZHI_PROCESS_WIN_X,YAZHI_PROCESS_WIN_Y, YAZHI_PROCESS_WIN_WIDE,YAZHI_PROCESS_WIN_HIGH);	
////////////////						GLCD_SetWindow_Fill(YAZHI_PROCESS_WIN_X,YAZHI_PROCESS_WIN_Y,YAZHI_PROCESS_WIN_X+YAZHI_PROCESS_WIN_WIDE-1,YAZHI_PROCESS_WIN_Y+YAZHI_PROCESS_WIN_HIGH-1,YELLOW_COLOR,cpGui_ColorChange(cSystemColor));//(cSystemColor));//.Location.x,label.Location.y,label.Location.x+label.Size.width,label.Location.y+label.Size.high,cpGui_ColorChange(label.bkColor),cpGui_ColorChange(label.bkColor));				
////////////////						GLCD_SetWindow_Fill(YAZHI_PROCESS_WIN_X,YAZHI_PROCESS_WIN_Y,YAZHI_PROCESS_WIN_X+YAZHI_PROCESS_WIN_WIDE-1,YAZHI_PROCESS_WIN_Y+31,cpGui_ColorChange(255),cpGui_ColorChange(255));	
////////////////						Printf24("压纸处理",YAZHI_PROCESS_WIN_X+YAZHI_PROCESS_WIN_WIDE/2-24-4,YAZHI_PROCESS_WIN_Y+5,WHITE_COLOR,0,0xffff);			
////////////////						cpGui_CreateButton(&PLC_YaZhi_SET_EXIT_BT);
////////////////							i=0;
////////////////							while(1)
////////////////							{
////////////////								if(YaZhi_Run_Data[i]!=-1)
////////////////								{
////////////////								sprintf(strr,"%d",i+1);
////////////////								Printf24(strr,YAZHI_PROCESS_WIN_X+20,YAZHI_PROCESS_WIN_Y+50+i*28,BLACK_COLOR,0,0xffff);
////////////////									
////////////////								FX_Plc_YaZhi_RunDataLabel.Location.x=YAZHI_PROCESS_WIN_X+60;
////////////////								FX_Plc_YaZhi_RunDataLabel.Location.y=YAZHI_PROCESS_WIN_Y+50+i*28;
////////////////								FX_Plc_YaZhi_RunDataLabel.bkColor=0xffff00;
////////////////								sprintf(FX_Plc_YaZhi_RunDataLabel.Text,"%0.2f",(float)YaZhi_Run_Data[i]/100);
////////////////								cpGui_CreateLabel(FX_Plc_YaZhi_RunDataLabel);
////////////////								i++;
////////////////								}
////////////////							else
////////////////								break;					
////////////////								
////////////////							}
////////////////											
////////////////	
////////////////	
////////////////						//Printf24("注意：请选择换刀，高度危险!!!",CHANGE_KNIFE_WIN_X+80,CHANGE_KNIFE_WIN_Y+CHANGE_KNIFE_WIN_HIGH/2,RED_COLOR,0,0xffff);							

////////////////			
////////////////		}
////////////////else
////////////////		{
////////////////			
////////////////							i=0;
////////////////							while(1)
////////////////							{
////////////////								if(YaZhi_Run_Data[i]!=-1)
////////////////								{
////////////////									if(CurrentSize==YaZhi_Run_Data[i])
////////////////										FX_Plc_YaZhi_RunDataLabel.bkColor=0x0000ff;
////////////////									else
////////////////										FX_Plc_YaZhi_RunDataLabel.bkColor=0xffff00;
////////////////								
////////////////							//	sprintf(strr,"%d",i+1);
////////////////							//	Printf24(strr,YAZHI_PROCESS_WIN_X+20,YAZHI_PROCESS_WIN_Y+50+i*28,BLACK_COLOR,0,0xffff);
////////////////									
////////////////								FX_Plc_YaZhi_RunDataLabel.Location.x=YAZHI_PROCESS_WIN_X+60;
////////////////								FX_Plc_YaZhi_RunDataLabel.Location.y=YAZHI_PROCESS_WIN_Y+50+i*28;
////////////////								sprintf(FX_Plc_YaZhi_RunDataLabel.Text,"%0.2f",(float)YaZhi_Run_Data[i]/100);
////////////////								cpGui_CreateLabel(FX_Plc_YaZhi_RunDataLabel);
////////////////								i++;
////////////////								}
////////////////							else
////////////////								break;					
////////////////								
////////////////							}			
////////////////			
////////////////			
////////////////			
////////////////		}
////////////////	
////////////////	
////////////////}
}



#include "Cal_Form.h"



#include "pic_exec.h"

void Plc_Ext_Form_Event(TOUCH touch)
{
BUTTON buttemp;
int textlength;
int i;
int dotcou;
uint8_t formaterr_flag=0;
touch.x+=10;
touch.y+=10;	
	
if(WorkStart_flag==1)//if(FormActive[0]==PLC_SET_FORM_SHOW)
	{		
	//BellOn_Enb();
	if(touch.status==TOUCH_DOWN)
		{
		//	EventType[FormActive[0]]=0;
		//	EventButton=NULL;
		//  Main_PowerOn_Picture_Enb  //主机开电源
			
			if((WorkMode==MANUAL_TOOLS_MODE)&&(PramSel_Page==0))
			{
////////////								
////////////			//设定电机启动时间
////////////			if((touch.x>=FX_Plc_Set_MotorStartUpTime_Data_Label.Location.x)&&(touch.x<FX_Plc_Set_MotorStartUpTime_Data_Label.Location.x+FX_Plc_Set_MotorStartUpTime_Data_Label.FontWidth)&&\
////////////			(touch.y>=FX_Plc_Set_MotorStartUpTime_Data_Label.Location.y)&&(touch.y<FX_Plc_Set_MotorStartUpTime_Data_Label.Location.y+FX_Plc_Set_MotorStartUpTime_Data_Label.FontHigh))
////////////			{
////////////				ParameterPage2_dis(Para2_sel, 0);
////////////				Para2_sel=7;

////////////			FX_PLC_Setup_Para_Refish(7);
////////////				
////////////			}
////////////			
						//设定电机停止时间
			if((touch.x>=FX_Plc_Set_MotorStopTime_Data_Label.Location.x)&&(touch.x<FX_Plc_Set_MotorStopTime_Data_Label.Location.x+FX_Plc_Set_MotorStopTime_Data_Label.FontWidth)&&\
			(touch.y>=FX_Plc_Set_MotorStopTime_Data_Label.Location.y)&&(touch.y<FX_Plc_Set_MotorStopTime_Data_Label.Location.y+FX_Plc_Set_MotorStopTime_Data_Label.FontHigh))
			{
				ParameterPage1_dis(Para_sel, 0);
				Para_sel=11;

				FX_PLC_Setup_Para_Refish(11);
				return;
			}
////////////			
////////////						//设定下刀时间
////////////			if((touch.x>=FX_Plc_Set_KnifeDownTime_Data_Label.Location.x)&&(touch.x<FX_Plc_Set_KnifeDownTime_Data_Label.Location.x+FX_Plc_Set_KnifeDownTime_Data_Label.FontWidth)&&\
////////////			(touch.y>=FX_Plc_Set_KnifeDownTime_Data_Label.Location.y)&&(touch.y<FX_Plc_Set_KnifeDownTime_Data_Label.Location.y+FX_Plc_Set_KnifeDownTime_Data_Label.FontHigh))
////////////			{
////////////								ParameterPage2_dis(Para2_sel, 0);	
////////////				Para2_sel=9;

////////////			FX_PLC_Setup_Para_Refish(9);
////////////				
////////////			}
////////////			
////////////						//设定裁切优化开关
////////////			if((touch.x>=FX_Plc_Set_CutOpt_Data_Label.Location.x)&&(touch.x<FX_Plc_Set_CutOpt_Data_Label.Location.x+FX_Plc_Set_CutOpt_Data_Label.FontWidth)&&\
////////////			(touch.y>=FX_Plc_Set_CutOpt_Data_Label.Location.y)&&(touch.y<FX_Plc_Set_CutOpt_Data_Label.Location.y+FX_Plc_Set_CutOpt_Data_Label.FontHigh))
////////////			{
////////////				ParameterPage2_dis(Para2_sel, 0);
////////////				Para2_sel=10;

////////////			FX_PLC_Setup_Para_Refish(10);
////////////				
////////////			}
////////////			
////////////			
////////////			//设定优化时间
////////////			if((touch.x>=FX_Plc_Set_CutTime_Data_Label.Location.x)&&(touch.x<FX_Plc_Set_CutTime_Data_Label.Location.x+FX_Plc_Set_CutTime_Data_Label.FontWidth)&&\
////////////			(touch.y>=FX_Plc_Set_CutTime_Data_Label.Location.y)&&(touch.y<FX_Plc_Set_CutTime_Data_Label.Location.y+FX_Plc_Set_CutTime_Data_Label.FontHigh))
////////////			{
////////////			 ParameterPage2_dis(Para2_sel, 0);
////////////				Para2_sel=11;

////////////				FX_PLC_Setup_Para_Refish(11);	
////////////			}
////////////			
////////////			
////////////						//设定快速裁切开关
////////////			if((touch.x>=FX_Plc_Set_FastCut_Enb_Data_Label.Location.x)&&(touch.x<FX_Plc_Set_FastCut_Enb_Data_Label.Location.x+FX_Plc_Set_FastCut_Enb_Data_Label.FontWidth)&&\
////////////			(touch.y>=FX_Plc_Set_FastCut_Enb_Data_Label.Location.y)&&(touch.y<FX_Plc_Set_FastCut_Enb_Data_Label.Location.y+FX_Plc_Set_FastCut_Enb_Data_Label.FontHigh))
////////////			{
////////////								ParameterPage2_dis(Para2_sel, 0);	
////////////				Para2_sel=12;		
////////////			
////////////				FX_PLC_Setup_Para_Refish(12);				
////////////			}
////////////		

		}

			
			
			
////////////								if((touch.x>=IO_DIS_X)&&(touch.x<IO_DIS_X+40)&&\
////////////			(touch.y>=IO_DIS_Y)&&(touch.y<IO_DIS_Y+40))
////////////			{	//IO状态触摸
////////////			
////////////			if(Cal_Form_Show_Flag!=0)//大计算器模式不入
////////////				 return;
////////////			
////////////			if(Fast_Knife_Status!=0)//换刀模式时不入
////////////				return;
////////////			
////////////			if(Pressure_Set_Status!=0)//压力设置时不入
////////////				return;
////////////			
////////////			BellOn_Enb();
////////////			
////////////			if(WorkStart_flag==1)
////////////			{
////////////			
////////////			if(FX_PLC_IO_Dis_Flag==0)
////////////				{
////////////					FX_PLC_IO_Dis_Flag=1;
////////////				CurrentArea_save1(FX_PLC_IO_STATUS_WIN_X,FX_PLC_IO_STATUS_WIN_Y, FX_PLC_IO_STATUS_WIN_WIDE,FX_PLC_IO_STATUS_WIN_HIGH);	
////////////							GLCD_SetWindow_Fill(FX_PLC_IO_STATUS_WIN_X,FX_PLC_IO_STATUS_WIN_Y,FX_PLC_IO_STATUS_WIN_X+FX_PLC_IO_STATUS_WIN_WIDE-1,FX_PLC_IO_STATUS_WIN_Y+FX_PLC_IO_STATUS_WIN_HIGH-1,YELLOW_COLOR,YELLOW_COLOR);//(cSystemColor));//.Location.x,label.Location.y,label.Location.x+label.Size.width,label.Location.y+label.Size.high,cpGui_ColorChange(label.bkColor),cpGui_ColorChange(label.bkColor));				
////////////							GLCD_SetWindow_Fill(FX_PLC_IO_STATUS_WIN_X,FX_PLC_IO_STATUS_WIN_Y,FX_PLC_IO_STATUS_WIN_X+FX_PLC_IO_STATUS_WIN_WIDE-1,FX_PLC_IO_STATUS_WIN_Y+31,cpGui_ColorChange(255),cpGui_ColorChange(255));	
////////////							Printf24("PLC IO 状态！",FX_PLC_IO_STATUS_WIN_X+FX_PLC_IO_STATUS_WIN_WIDE/2-72-4,FX_PLC_IO_STATUS_WIN_Y+5,RED_COLOR,0,0xffff);
////////////						//	Printf24("注意：请选择换刀，高度危险!!!",FX_PLC_IO_STATUS_WIN_X+80,FX_PLC_IO_STATUS_WIN_Y+FX_PLC_IO_STATUS_WIN_WIDE/2,RED_COLOR,0,0xffff);		
////////////				}
////////////			else
////////////				{
////////////					FX_PLC_IO_Dis_Flag=0;
////////////					CurrentArea_recover1(FX_PLC_IO_STATUS_WIN_X,FX_PLC_IO_STATUS_WIN_Y, FX_PLC_IO_STATUS_WIN_WIDE,FX_PLC_IO_STATUS_WIN_HIGH);
////////////				}
////////////			
////////////			
////////////////////			if((WorkMode!=MANUAL_IO_MODE))
////////////////////					{
////////////////////						if(WorkStart_flag==1)
////////////////////						{
////////////////////							WorkMode=MANUAL_IO_MODE;//进入端口测试模式
////////////////////							
////////////////////						}
////////////////////					}
////////////////////			else
////////////////////					{
////////////////////						
////////////////////						
////////////////////					}
////////////				}
////////////			
////////////			}
			
////////////////			
////////////////					if((touch.x>=MODE_NAME_X1+40)&&(touch.x<MODE_NAME_X1+40+120)&&\
////////////////			(touch.y>=MODE_NAME_Y1)&&(touch.y<MODE_NAME_Y1+32))
////////////////			{	
////////////////			 if(Cal_Form_Show_Flag!=0)
////////////////				 return;
////////////////			 
////////////////				BellOn_Enb();
////////////////				
////////////////				
////////////////			if(WorkMode==MANUAL_MODE)
////////////////				{
////////////////				Touch_code=THREE_KEY_CODE;	//自动mode
////////////////				KeyExec(Touch_code); //调键处理------------
////////////////				}				
////////////////			else
////////////////				{
////////////////					if(WorkMode==AUTO_MODE)
////////////////					{
////////////////						
////////////////						Touch_code=TWO_KEY_CODE;	//手动mode
////////////////						KeyExec(Touch_code); //调键处理------------
////////////////						
////////////////					}
////////////////				else
////////////////					{
////////////////				  Touch_code=THREE_KEY_CODE;	//自动mode
////////////////					KeyExec(Touch_code); //调键处理------------					
////////////////					}
////////////////				//				Touch_code=TWO_KEY_CODE;	//手动mode		
////////////////				//	Touch_code=PROC_KEY_CODE;   //程序 选择		(查找模式)				
////////////////				}			
////////////////				
////////////////				return;
////////////////			}
			
			
								if((touch.x>=100)&&(touch.x<100+50)&&\
			(touch.y>=120)&&(touch.y<120+32))
			{		
				BellOn_Enb();
				
				Touch_code=PROC_KEY_CODE;   //程序 选择		(查找模式)				
				KeyExec(Touch_code); //调键处理------------
				
				
////////			if(WorkMode==MANUAL_MODE)
////////				{
////////				Touch_code=THREE_KEY_CODE;	//自动mode
////////				KeyExec(Touch_code); //调键处理------------
////////				}				
////////			else
////////				{
////////					if(WorkMode==AUTO_MODE)
////////					{
////////						
////////						Touch_code=TWO_KEY_CODE;	//手动mode
////////						KeyExec(Touch_code); //调键处理------------
////////						
////////					}
////////	

////////				}			
				
				return;
			}
			
			
		if((touch.x>=Main_PowerOn_Picture_Enb.Location.x)&&(touch.x<Main_PowerOn_Picture_Enb.Location.x+Main_PowerOn_Picture_Enb.Size.width)&&\
			(touch.y>=Main_PowerOn_Picture_Enb.Location.y)&&(touch.y<Main_PowerOn_Picture_Enb.Location.y+Main_PowerOn_Picture_Enb.Size.high))
			{			
			BellOn_Enb();
			if(Run_flag==1)
						return;//电机运行时退出
			if(Pressure_Set_Status==1)
					return;
				
			if((Manual_Knife_Status==0)&&(Fast_Knife_Status==0)&&(Motor_Knife_Status==0)&&(Knife_Change_Status==0))
				{
					
					#ifdef PLC_3U
					if(MainPower_Status==0)
							{
//							if(FX_PLC_Motor_Run_Enb_Flag==0)//允许位无效，不允许打开
//								return;
							
							App_Modbus_Plc_Write_M_Status(101,M_OFF);	
						//	if(App_FX_Plc_Force_Process("OFF",M101)==0)
									{
										App_Modbus_Plc_Write_M_Status(100,M_ON);	
								//	if(App_FX_Plc_Force_Process("ON",M100)==0)
										{
										MainPower_Status=1;
										//Printf24("主机已启动          ",PLC_HINT_DIS_X,PLC_HINT_DIS_Y,RED_COLOR,1,cpGui_ColorChange(PLC_HINT_DIS_BAK_COLOR));
											
										cpGui_CreatePictureBox(&Main_PowerOn_Picture_Enb);
											
////////										if((FX_Plc_X4_Status=='0')&&(FX_Plc_X4_Status=='0'))
////////														{
////////														Printf24("PLC X4 X5 信号断开       ",PLC_HINT_DIS_X,PLC_HINT_DIS_Y,RED_COLOR,1,cpGui_ColorChange(PLC_HINT_DIS_BAK_COLOR));	
////////														XD_XE_Flag=0;
////////														return;
////////														}
////////										if((FX_Plc_X4_Status=='1')&&(FX_Plc_X4_Status=='0'))
////////														{
////////														Printf24("PLC X5 信号断开         ",PLC_HINT_DIS_X,PLC_HINT_DIS_Y,RED_COLOR,1,cpGui_ColorChange(PLC_HINT_DIS_BAK_COLOR));	
////////														XD_XE_Flag=0;
////////														return;
////////														}

////////										if((FX_Plc_X4_Status=='0')&&(FX_Plc_X4_Status=='1'))
////////														{
////////														Printf24("PLC X4 信号断开          ",PLC_HINT_DIS_X,PLC_HINT_DIS_Y,RED_COLOR,1,cpGui_ColorChange(PLC_HINT_DIS_BAK_COLOR));
////////														XD_XE_Flag=0;
////////														return;
////////														}																				
										}
								}
									return;
					}
					else
					{
						
						App_Modbus_Plc_Write_M_Status(100,M_OFF);	
				//	if(App_FX_Plc_Force_Process("OFF",M100)==0)
								{
										App_Modbus_Plc_Write_M_Status(101,M_ON);	
						//		if(App_FX_Plc_Force_Process("ON",M101)==0)
										{			
										if(MainPower_Status>0)
												{
												MainPower_Status=0;
												cpGui_CreatePictureBox(&Main_PowerOn_Picture_Dis);
											//	Printf24("          主机已停止          ",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,RED_COLOR,1,0xffff);
												}			
										}
								}
					return;
					}
					#else
					
					while(Plc_Poll_Enb_Flag==1)
					{
					if(Plc_Comm_Status==PLC_COMM_TIMEOUT)
						return;						
					}//等特查询指令OK
									
				if((Plc_X_Status[0x0D][0]=='0')&&(Plc_X_Status[0x0E][0]=='1'))
				{
				Printf24("        PLC XD 信号断开         ",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,RED_COLOR,1,0xffff);	
					XD_XE_Flag=0;
					return;
				}
				if((Plc_X_Status[0x0D][0]=='1')&&(Plc_X_Status[0x0E][0]=='0'))
				{
				Printf24("        PLC XE 信号断开         ",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,RED_COLOR,1,0xffff);	
					XD_XE_Flag=0;
					return;
				}

				if((Plc_X_Status[0x0D][0]=='0')&&(Plc_X_Status[0x0E][0]=='0'))
				{
				Printf24("      PLC XD、XE 信号断开       ",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,RED_COLOR,1,0xffff);
				XD_XE_Flag=0;
				return;
				}					
					



				if(App_Plc_SendFrame_Process("WCS","R",0x11,'0')==0)
				{
//////				App_Plc_WCS_Return_Ok_Flag=0;
//////				App_Plc_SendFrame("WCS","R",0x11,'0');//关闭R11
//////				while(App_Plc_WCS_Return_Ok_Flag==0);
					
						if(App_Plc_SendFrame_Process("WCS","R",0x10,'1')==0)
						{
						//////				App_Plc_WCS_Return_Ok_Flag=0;
						//////				App_Plc_SendFrame("WCS","R",0x10,'1');//开启R10
						//////				while(App_Plc_WCS_Return_Ok_Flag==0);				
						MainPower_Status=1;
							Printf24("          主机已启动          ",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,RED_COLOR,1,0xffff);
						}
					}
					
					#endif
				}
				
			}


//////////		//Main_PowerOff_Picture_Enb  //主机关电源
//////////		if((touch.x>=Main_PowerOff_Picture_Enb.Location.x)&&(touch.x<Main_PowerOff_Picture_Enb.Location.x+Main_PowerOff_Picture_Enb.Size.width)&&\
//////////			(touch.y>=Main_PowerOff_Picture_Enb.Location.y)&&(touch.y<Main_PowerOff_Picture_Enb.Location.y+Main_PowerOff_Picture_Enb.Size.high))
//////////			{			
//////////			BellOn_Enb();
//////////							if(Run_flag==1)
//////////						return;//电机运行时退出
//////////			if(Pressure_Set_Status==1)
//////////					return;
//////////			
//////////			
//////////			#ifdef PLC_3U
//////////												if(App_FX_Plc_Force_Process("OFF",M100)==0)
//////////								{
//////////												if(App_FX_Plc_Force_Process("ON",M101)==0)
//////////								{			
//////////						if(MainPower_Status>0)
//////////						{
//////////						MainPower_Status=0;
//////////						Printf24("          主机已停止          ",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,RED_COLOR,1,0xffff);
//////////						}			
//////////					}
//////////								}
//////////			
//////////			#else
//////////					while(Plc_Poll_Enb_Flag==1)
//////////					{
//////////					if(Plc_Comm_Status==PLC_COMM_TIMEOUT)
//////////						return;
//////////						
//////////					}//等特查询指令OK
//////////				//Plc_Send_WCS_Flag=1;
//////////				
//////////				if(App_Plc_SendFrame_Process("WCS","R",0x10,'0')==0)
//////////				{
//////////				//////				App_Plc_WCS_Return_Ok_Flag=0;
//////////				//////				App_Plc_SendFrame("WCS","R",0x10,'0');//关闭R10
//////////				//////				while(App_Plc_WCS_Return_Ok_Flag==0);				
//////////				if(App_Plc_SendFrame_Process("WCS","R",0x11,'1')==0)
//////////					{
//////////					//////				App_Plc_WCS_Return_Ok_Flag=0;
//////////					//////				App_Plc_SendFrame("WCS","R",0x11,'1');//开启R11
//////////					//////				while(App_Plc_WCS_Return_Ok_Flag==0);
//////////				
//////////						if(MainPower_Status>0)
//////////						{
//////////						MainPower_Status=0;
//////////						Printf24("          主机已停止          ",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,RED_COLOR,1,0xffff);
//////////						}
//////////					}
//////////				}
//////////				#endif
//////////				
//////////			}
//////////				
			
////////////		//Pressure_Set_Picture  //压力设置
////////////		if((touch.x>=Pressure_Set_Picture.Location.x)&&(touch.x<Pressure_Set_Picture.Location.x+Pressure_Set_Picture.Size.width)&&\
////////////			(touch.y>=Pressure_Set_Picture.Location.y)&&(touch.y<Pressure_Set_Picture.Location.y+Pressure_Set_Picture.Size.high))
////////////			{			
////////////			if(Fast_Knife_Status!=0)//换刀模式不入
////////////				return;
////////////			
////////////			if(FX_PLC_IO_Dis_Flag!=0)//显示PLC IO状态时不入
////////////				return;
////////////			
////////////			BellOn_Enb();
////////////			if(Run_flag==1)
////////////					return;//电机运行时退出
////////////				
////////////////////					while(Plc_Poll_Enb_Flag==1)
////////////////////					{
////////////////////					if(Plc_Comm_Status==PLC_COMM_TIMEOUT)
////////////////////						return;
////////////////////					}//等特查询指令OK
////////////				//Plc_Send_WCS_Flag=1;					
////////////					
////////////			if((Manual_Knife_Status!=0)||(Motor_Knife_Status!=0)&&(Knife_Change_Status!=0))//换刀状态下不入
////////////				return;
////////////						if(WorkMode==SELF_CUT_MODE)//自刀模式不入
////////////				return;
////////////			if(Pressure_Set_Status==0)
////////////				{
////////////				Plc_Form_Pressure_Set_Process();//压力设置处理
////////////				}
////////////			}
						
			
			
		//	Foot_Pressure_Set_Data
		
//////////		//脚踩压力设置			
//////////			//PLC_Pressure_SET_UP_BT  
//////////	if((touch.x>=PLC_Foot_Pressure_SET_UP_BT.Location.x)&&(touch.x<PLC_Foot_Pressure_SET_UP_BT.Location.x+PLC_Foot_Pressure_SET_UP_BT.Size.width)&&\
//////////			(touch.y>=PLC_Foot_Pressure_SET_UP_BT.Location.y)&&(touch.y<PLC_Foot_Pressure_SET_UP_BT.Location.y+PLC_Foot_Pressure_SET_UP_BT.Size.high))
//////////		{
//////////			
//////////		if(Pressure_Set_Status==1)
//////////				{//正确，退出
//////////				BellOn_Enb();
//////////				if(Run_flag==1)
//////////						return;//电机运行时退出	
//////////				
//////////				if(Foot_Pressure_Set_Data<=(400-10))
//////////				{
//////////				Foot_Pressure_Set_Data+=10;
//////////				sprintf(PLC_SET_Foot_DT3DataLabel.Text,"%0.2f",((float)Foot_Pressure_Set_Data/100));			
//////////				Printf24("     ",PLC_SET_Foot_DT3DataLabel.Location.x,PLC_SET_Foot_DT3DataLabel.Location.y,BLACK_COLOR,1,YELLOW_COLOR);//cpGui_ColorChange(PLC_HINT_DIS_BAK_COLOR));	
//////////				cpGui_CreateLabel(PLC_SET_Foot_DT3DataLabel);						
//////////				FX_Foot_Plc_PressureData=Foot_Pressure_Set_Data;   //压力直接有效
//////////				}						
//////////				
//////////				
//////////				#ifdef PRESSURE_CHANGE_DIS
//////////					if(FX_Foot_Plc_PressureData>=140)
//////////						{
//////////						 float realpresure=((float)FX_Foot_Plc_PressureData-140.0)/2.5+300;
//////////				  	FX_Plc_Foot_Real_PressureData=realpresure;//发送转换后的压力			
//////////							
//////////						}
//////////					else
//////////					{
//////////						if(FX_Foot_Plc_PressureData==130)
//////////						{
//////////							FX_Plc_Foot_Real_PressureData=295;
//////////						}
//////////						else
//////////							if(FX_Foot_Plc_PressureData==120)
//////////							{
//////////								FX_Plc_Foot_Real_PressureData=290;
//////////							}
//////////							else								
//////////							if(FX_Foot_Plc_PressureData==110)
//////////							{
//////////								FX_Plc_Foot_Real_PressureData=285;
//////////							}
//////////							else								
//////////							{
////////////////									if(FX_Foot_Plc_PressureData==110)
////////////////									{
////////////////										FX_Plc_Foot_Real_PressureData=300;	
////////////////									}
////////////////									else
//////////										FX_Plc_Foot_Real_PressureData=280;							
//////////							}						
//////////					}
//////////				
//////////				sprintf(PLC_SET_DT3DataLabel.Text,"%d",FX_Plc_Foot_Real_PressureData);	
//////////					Printf24(PLC_SET_DT3DataLabel.Text,PLC_SET_Foot_DT3DataLabel.Location.x+64+80,PLC_SET_Foot_DT3DataLabel.Location.y-120,BLACK_COLOR,1,YELLOW_COLOR);//
//////////				
//////////				#endif
//////////				
//////////				
//////////				cpGui_Button_UpDown(&PLC_Foot_Pressure_SET_UP_BT,TOUCH_DOWN);
//////////			
//////////				EventButton=&PLC_Foot_Pressure_SET_UP_BT;
//////////				EventType[FormActive[0]]=Button_Type;		
//////////				
//////////				return;
//////////				
//////////				//cpGui_Button_UpDown(&PLC_Pressure_SET_UP_BT,TOUCH_DOWN);			
//////////				}		
//////////		}		
		
//////////	//PLC_Pressure_SET_UP_BT  脚踩压力设置 减
//////////	if((touch.x>=PLC_Foot_Pressure_SET_DOWN_BT.Location.x)&&(touch.x<PLC_Foot_Pressure_SET_DOWN_BT.Location.x+PLC_Foot_Pressure_SET_DOWN_BT.Size.width)&&\
//////////			(touch.y>=PLC_Foot_Pressure_SET_DOWN_BT.Location.y)&&(touch.y<PLC_Foot_Pressure_SET_DOWN_BT.Location.y+PLC_Foot_Pressure_SET_DOWN_BT.Size.high))
//////////		{			
//////////		if(Pressure_Set_Status==1)
//////////				{//正确，退出
//////////				BellOn_Enb();
//////////					
//////////				if(Run_flag==1)
//////////						return;//电机运行时退出					
//////////				#ifdef PLC_3U
//////////				if(Foot_Pressure_Set_Data>=(100+10))
//////////				{
//////////				Foot_Pressure_Set_Data-=10;
//////////				Printf24("     ",PLC_SET_Foot_DT3DataLabel.Location.x,PLC_SET_Foot_DT3DataLabel.Location.y,BLACK_COLOR,1,YELLOW_COLOR);
//////////				sprintf(PLC_SET_Foot_DT3DataLabel.Text,"%.2f",((float)Foot_Pressure_Set_Data/100));		
//////////				cpGui_CreateLabel(PLC_SET_Foot_DT3DataLabel);					
//////////				FX_Foot_Plc_PressureData=Foot_Pressure_Set_Data;  //压力直接有效
//////////					

//////////				}	
//////////				
//////////				
//////////				#ifdef PRESSURE_CHANGE_DIS
//////////				
//////////						if(FX_Foot_Plc_PressureData>=140)
//////////						{
//////////						 float realpresure=((float)FX_Foot_Plc_PressureData-140.0)/2.5+300;
//////////				  	FX_Plc_Foot_Real_PressureData=realpresure;//发送转换后的压力			
//////////							
//////////						}
//////////					else
//////////					{
//////////						if(FX_Foot_Plc_PressureData==130)
//////////						{
//////////							FX_Plc_Foot_Real_PressureData=295;
//////////						}
//////////						else
//////////							if(FX_Foot_Plc_PressureData==120)
//////////							{
//////////								FX_Plc_Foot_Real_PressureData=290;
//////////							}
//////////							else								
//////////							if(FX_Foot_Plc_PressureData==110)
//////////							{
//////////								FX_Plc_Foot_Real_PressureData=285;
//////////							}
//////////							else								
//////////							{
////////////////									if(FX_Foot_Plc_PressureData==110)
////////////////									{
////////////////										FX_Plc_Foot_Real_PressureData=300;	
////////////////									}
////////////////									else
//////////										FX_Plc_Foot_Real_PressureData=280;							
//////////							}						
//////////					}
//////////					
//////////				sprintf(PLC_SET_DT3DataLabel.Text,"%d",FX_Plc_Foot_Real_PressureData);	
//////////				Printf24(PLC_SET_DT3DataLabel.Text,PLC_SET_Foot_DT3DataLabel.Location.x+64+80,PLC_SET_Foot_DT3DataLabel.Location.y-120,BLACK_COLOR,1,YELLOW_COLOR);//
//////////				#endif
//////////				
//////////				
//////////				cpGui_Button_UpDown(&PLC_Foot_Pressure_SET_DOWN_BT,TOUCH_DOWN);			
//////////				EventButton=&PLC_Foot_Pressure_SET_DOWN_BT;
//////////				EventType[FormActive[0]]=Button_Type;	
//////////				return;
//////////        #else
//////////				if(Pressure_Set_Data>=(200+10))
//////////				{
//////////				Pressure_Set_Data-=10;
//////////				sprintf(PLC_SET_DT3DataLabel.Text,"%d",Pressure_Set_Data);		
//////////				cpGui_CreateLabel(PLC_SET_DT3DataLabel);					
//////////				Plc_DT_Data_t[3]=Pressure_Set_Data;
//////////				Save_PLC_DT_Data((pInt8U)&Plc_DT_Data_t);//保存PLC DT 数据	
//////////				Plc_Send_DT_Data_Flag=1;		//DT数据变化，重发
//////////				}	
//////////				#endif
//////////				
//////////				//cpGui_Button_UpDown(&PLC_Pressure_SET_UP_BT,TOUCH_DOWN);			
//////////				}		
//////////		}	
		
			
//////////	//PLC_Pressure_SET_UP_BT
//////////	if((touch.x>=PLC_Pressure_SET_UP_BT.Location.x)&&(touch.x<PLC_Pressure_SET_UP_BT.Location.x+PLC_Pressure_SET_UP_BT.Size.width)&&\
//////////			(touch.y>=PLC_Pressure_SET_UP_BT.Location.y)&&(touch.y<PLC_Pressure_SET_UP_BT.Location.y+PLC_Pressure_SET_UP_BT.Size.high))
//////////		{
//////////			
//////////		if(Pressure_Set_Status==1)
//////////				{//正确，退出
//////////				BellOn_Enb();
//////////				if(Run_flag==1)
//////////						return;//电机运行时退出	
//////////				
//////////				if(Pressure_Set_Data<=(1000-10))
//////////				{
//////////				Pressure_Set_Data+=10;
//////////				sprintf(PLC_SET_DT3DataLabel.Text,"%0.2f",((float)Pressure_Set_Data/100));			
//////////				Printf24("     ",PLC_SET_DT3DataLabel.Location.x,PLC_SET_DT3DataLabel.Location.y,BLACK_COLOR,1,YELLOW_COLOR);//cpGui_ColorChange(PLC_HINT_DIS_BAK_COLOR));	
//////////				cpGui_CreateLabel(PLC_SET_DT3DataLabel);						
//////////				FX_Plc_PressureData=Pressure_Set_Data;   //压力直接有效
//////////					
//////////				Pressure_Dis_Refish_Flag=0;
//////////						
//////////	
//////////				//		Save_PLC_DT_Data((pInt8U)&Plc_DT_Data_t);//保存PLC DT 数据	
//////////				//		Plc_Send_DT_Data_Flag=1;		//DT数据变化，重发
//////////				}		
//////////				
//////////				
//////////				#ifdef PRESSURE_CHANGE_DIS
//////////									float realpresure=((float)FX_Plc_PressureData-250.0)/2.5+370;
//////////					FX_Plc_Real_PressureData=realpresure;//发送转换后的压力


//////////					sprintf(PLC_SET_DT3DataLabel.Text,"%d",FX_Plc_Real_PressureData);	
//////////					Printf24(PLC_SET_DT3DataLabel.Text,PLC_SET_Foot_DT3DataLabel.Location.x+64,PLC_SET_Foot_DT3DataLabel.Location.y-120,BLACK_COLOR,1,YELLOW_COLOR);//
//////////				
//////////				#endif

//////////				
//////////			  cpGui_Button_UpDown(&PLC_Pressure_SET_UP_BT,TOUCH_DOWN);
//////////			
//////////				EventButton=&PLC_Pressure_SET_UP_BT;
//////////				EventType[FormActive[0]]=Button_Type;	
//////////				return;
//////////				//cpGui_Button_UpDown(&PLC_Pressure_SET_UP_BT,TOUCH_DOWN);			
//////////				}		
//////////		}		
		
////////////	//PLC_Pressure_SET_UP_BT
////////////	if((touch.x>=PLC_Pressure_SET_DOWN_BT.Location.x)&&(touch.x<PLC_Pressure_SET_DOWN_BT.Location.x+PLC_Pressure_SET_DOWN_BT.Size.width)&&\
////////////			(touch.y>=PLC_Pressure_SET_DOWN_BT.Location.y)&&(touch.y<PLC_Pressure_SET_DOWN_BT.Location.y+PLC_Pressure_SET_DOWN_BT.Size.high))
////////////		{			
////////////		if(Pressure_Set_Status==1)
////////////				{//正确，退出
////////////				BellOn_Enb();
////////////				if(Run_flag==1)
////////////						return;//电机运行时退出					
////////////				#ifdef PLC_3U
////////////				if(Pressure_Set_Data>=(250+10))
////////////				{
////////////				Pressure_Set_Data-=10;
////////////				Printf24("     ",PLC_SET_DT3DataLabel.Location.x,PLC_SET_DT3DataLabel.Location.y,BLACK_COLOR,1,YELLOW_COLOR);
////////////				sprintf(PLC_SET_DT3DataLabel.Text,"%.2f",((float)Pressure_Set_Data/100));		
////////////				cpGui_CreateLabel(PLC_SET_DT3DataLabel);					
////////////				FX_Plc_PressureData=Pressure_Set_Data;  //压力直接有效
////////////			//	Save_PLC_DT_Data((pInt8U)&Plc_DT_Data_t);//保存PLC DT 数据	
////////////			//	Plc_Send_DT_Data_Flag=1;		//DT数据变化，重发
////////////					
////////////				Pressure_Dis_Refish_Flag=0;
////////////					
////////////				}	
////////////				
////////////				
////////////				#ifdef PRESSURE_CHANGE_DIS
////////////				
////////////									float realpresure=((float)FX_Plc_PressureData-250.0)/2.5+370;
////////////					FX_Plc_Real_PressureData=realpresure;//发送转换后的压力


////////////					sprintf(PLC_SET_DT3DataLabel.Text,"%d",FX_Plc_Real_PressureData);	
////////////					Printf24(PLC_SET_DT3DataLabel.Text,PLC_SET_Foot_DT3DataLabel.Location.x+64,PLC_SET_Foot_DT3DataLabel.Location.y-120,BLACK_COLOR,1,YELLOW_COLOR);//cpGui_ColorChange(PLC_HINT_DIS_BAK_COLOR));	
////////////				
////////////				#endif
////////////				
////////////				

////////////				
////////////								cpGui_Button_UpDown(&PLC_Pressure_SET_DOWN_BT,TOUCH_DOWN);
////////////			
////////////				EventButton=&PLC_Pressure_SET_DOWN_BT;
////////////				EventType[FormActive[0]]=Button_Type;	
////////////				return;
////////////        #else
////////////				if(Pressure_Set_Data>=(200+10))
////////////				{
////////////				Pressure_Set_Data-=10;
////////////				sprintf(PLC_SET_DT3DataLabel.Text,"%d",Pressure_Set_Data);		
////////////				cpGui_CreateLabel(PLC_SET_DT3DataLabel);					
////////////				Plc_DT_Data_t[3]=Pressure_Set_Data;
////////////				Save_PLC_DT_Data((pInt8U)&Plc_DT_Data_t);//保存PLC DT 数据	
////////////				Plc_Send_DT_Data_Flag=1;		//DT数据变化，重发
////////////				}	
////////////				#endif
////////////				
////////////				//cpGui_Button_UpDown(&PLC_Pressure_SET_UP_BT,TOUCH_DOWN);			
////////////				}		
////////////		}			

		
		
//PLC_Pressure_SET_EXIT_BT
////////////	if((touch.x>=PLC_Pressure_SET_EXIT_BT.Location.x)&&(touch.x<PLC_Pressure_SET_EXIT_BT.Location.x+PLC_Pressure_SET_EXIT_BT.Size.width)&&\
////////////			(touch.y>=PLC_Pressure_SET_EXIT_BT.Location.y)&&(touch.y<PLC_Pressure_SET_EXIT_BT.Location.y+PLC_Pressure_SET_EXIT_BT.Size.high))
////////////		{			
////////////		if(Pressure_Set_Status==1)
////////////				{//正确，退出
////////////				BellOn_Enb();
////////////				if(Run_flag==1)
////////////						return;//电机运行时退出				
////////////				
////////////				#ifdef PLC_3U
////////////			//	if((Manual_Knife_Status!=0)||(Motor_Knife_Status!=0))//换刀状态下不入
////////////				//	return;
////////////				if(Pressure_Set_Status==1)
////////////					{
////////////			//		Plc_Form_Pressure_Set_Process();//压力设置处理
////////////					}
////////////			//	Save_PLC_DT_Data((pInt8U)&Plc_DT_Data_t);//保存PLC DT 数据	
////////////			//	Plc_Send_DT_Data_Flag=1;		//DT数据变化，重发
////////////					
////////////        #else
////////////				if(Pressure_Set_Data>=(200+10))
////////////				{
////////////				Pressure_Set_Data-=10;
////////////				sprintf(PLC_SET_DT3DataLabel.Text,"%d",Pressure_Set_Data);		
////////////				cpGui_CreateLabel(PLC_SET_DT3DataLabel);					
////////////				Plc_DT_Data_t[3]=Pressure_Set_Data;
////////////				Save_PLC_DT_Data((pInt8U)&Plc_DT_Data_t);//保存PLC DT 数据	
////////////				Plc_Send_DT_Data_Flag=1;		//DT数据变化，重发
////////////				}	
////////////				#endif
////////////				
////////////				//cpGui_Button_UpDown(&PLC_Pressure_SET_UP_BT,TOUCH_DOWN);			
////////////				}		
////////////			}
		//}	

//////////////		//PLC_Pressure_SET_EXIT_BT
//////////////	if((touch.x>=PLC_YaZhi_SET_EXIT_BT.Location.x)&&(touch.x<PLC_YaZhi_SET_EXIT_BT.Location.x+PLC_YaZhi_SET_EXIT_BT.Size.width)&&\
//////////////			(touch.y>=PLC_YaZhi_SET_EXIT_BT.Location.y)&&(touch.y<PLC_YaZhi_SET_EXIT_BT.Location.y+PLC_YaZhi_SET_EXIT_BT.Size.high))
//////////////		{		
//////////////			if(YaZhi_Process_Flag==0)
//////////////				return;
//////////////				BellOn_Enb();
//////////////			CurrentArea_recover1(YAZHI_PROCESS_WIN_X,YAZHI_PROCESS_WIN_Y, YAZHI_PROCESS_WIN_WIDE,YAZHI_PROCESS_WIN_HIGH);
//////////////			
//////////////			ACServoStop();
//////////////			
//////////////			YaZhiMotorRun_Flag=0;
//////////////				App_Modbus_Plc_Write_M_Status(304,M_OFF);	
//////////////				//	if(App_FX_Plc_Force_Process("OFF",M304)==0)//退出关闭 M304
//////////////									{//退出时断开M304

//////////////									}			
//////////////			App_Modbus_Plc_Write_M_Status(305,M_OFF);										
//////////////		//	if(App_FX_Plc_Force_Process("OFF",M305)==0)
//////////////									{//退出时断开M305
//////////////										
//////////////									}
//////////////			YaZhi_Process_Flag=0;			
//////////////				YaZhiRun_Cnt=0;
//////////////		}
		
		
		//Manual_Knife_Picture_Enb  手动换刀
		if((touch.x>=Manual_Knife_Picture_Enb.Location.x)&&(touch.x<Manual_Knife_Picture_Enb.Location.x+Manual_Knife_Picture_Enb.Size.width)&&\
			(touch.y>=Manual_Knife_Picture_Enb.Location.y)&&(touch.y<Manual_Knife_Picture_Enb.Location.y+Manual_Knife_Picture_Enb.Size.high))
			{			
			if(Fast_Knife_Status==0)
				return;
			
			BellOn_Enb();			
			if(Run_flag==1)
						return;//电机运行时退出				
			if(Pressure_Set_Status==1)
					return;			

			
			if(Manual_Knife_Status==0)
				{//手动换刀
				//if((Fast_Knife_Status==0)&&(Motor_Knife_Status==0))
				{
								
						App_Modbus_Plc_Write_M_Status(100,M_OFF);	
				//	if(App_FX_Plc_Force_Process("OFF",M100)==0)//先关闭主电机
								{
										App_Modbus_Plc_Write_M_Status(101,M_ON);	
							//	if(App_FX_Plc_Force_Process("ON",M101)==0)
										{	
											
										MainPower_Status=0;
										cpGui_CreatePictureBox(&Main_PowerOn_Picture_Dis);
											
										if(Manual_Change_Knife_Steps==0)
										{//第一步，延时120秒  等延时到后，转第2步  延时3秒
											
											
											Manual_Change_Knife_InvertTime=Motor_StopTime;
											
											
												App_Modbus_Plc_Write_M_Status(201,M_OFF);	
										//	if(App_FX_Plc_Force_Process("OFF",M201)==0)
												{			
														App_Modbus_Plc_Write_M_Status(202,M_OFF);	
											//	if(App_FX_Plc_Force_Process("OFF",M202)==0)
													{	
															App_Modbus_Plc_Write_M_Status(200,M_ON);	
													//if(App_FX_Plc_Force_Process("ON",M200)==0)
															{						//关闭其它状态
													//		cpGui_CreatePictureBox(&Manual_Knife_Picture_Enb);
																
																Normal_Knife_Status=0;
																Motor_Knife_Status=0;
																Manual_Knife_Status=1;		
																cpGui_CreatePictureBox(&Manual_Knife_Picture_Enb);
																cpGui_CreatePictureBox(&Motor_Knife_Picture_Dis);
																cpGui_CreatePictureBox(&Normal_Knife_Picture_Dis);	
																
																GLCD_SetWindow_Fill(CHANGE_KNIFE_WIN_X,CHANGE_KNIFE_WIN_Y+CHANGE_KNIFE_WIN_HIGH/2+16,CHANGE_KNIFE_WIN_X+CHANGE_KNIFE_WIN_WIDE-2,CHANGE_KNIFE_WIN_Y+CHANGE_KNIFE_WIN_HIGH/2+16+65,YELLOW_COLOR,YELLOW_COLOR);
																if(Language==CHN_HAN)
																							{
																								
																							Printf24("注意：手动换刀，高度危险!!!   ",CHANGE_KNIFE_WIN_X+80,CHANGE_KNIFE_WIN_Y+CHANGE_KNIFE_WIN_HIGH/2+16,RED_COLOR,1,YELLOW_COLOR);	
																								
																					//		Printf24("注意：电动换刀，高度危险!!!   ",CHANGE_KNIFE_WIN_X+80,CHANGE_KNIFE_WIN_Y+CHANGE_KNIFE_WIN_HIGH/2,RED_COLOR,1,YELLOW_COLOR);
																							}
																							else
																							{
																								
																								
																							Printf24("NOTE: Manual tool change",CHANGE_KNIFE_WIN_X+80+50,CHANGE_KNIFE_WIN_Y+CHANGE_KNIFE_WIN_HIGH/2+16,RED_COLOR,1,YELLOW_COLOR);
																							Printf24("    Highly Hazardous!!!",CHANGE_KNIFE_WIN_X+80+50,CHANGE_KNIFE_WIN_Y+CHANGE_KNIFE_WIN_HIGH/2+16+22,RED_COLOR,1,YELLOW_COLOR);
																						//		memcpy(FX_Plc_ChangeKnife_Hint_Label.Text,"Note: Please select Tool Change, Highly Dangerous !!!",strlen("Note: Please select Tool Change, Highly Dangerous !!!"));//
																								
																								
																							}
						
															GLCD_SetWindow_Fill(CHANGE_KNIFE_WIN_X,CHANGE_KNIFE_WIN_Y+32,CHANGE_KNIFE_WIN_X+CHANGE_KNIFE_WIN_WIDE-2,CHANGE_KNIFE_WIN_Y+32+65,YELLOW_COLOR,YELLOW_COLOR);
													//		Printf24("                               ",CHANGE_KNIFE_WIN_X.Location.x,FX_Plc_ChangeKnife_Hint_Label.Location.y,YELLOW_COLOR,1,YELLOW_COLOR);
														//	Printf24("                               ",FX_Plc_ChangeKnife_Hint_Label.Location.x,FX_Plc_ChangeKnife_Hint_Label.Location.y,YELLOW_COLOR,1,YELLOW_COLOR);
																							
													//		memcpy(FX_Plc_ChangeKnife_Hint_Label.Text,"                             ",strlen("                             "));//
														//	cpGui_CreateLabel(FX_Plc_ChangeKnife_Hint_Label);//选择换刀		
																
															sprintf(FX_Plc_ChangeKnife_Hint_Label.Text,"%d",Manual_Change_Knife_InvertTime);
															cpGui_CreateLabel(FX_Plc_ChangeKnife_Hint_Label);//选择换刀																		
														}			
													}		
												}																																
										}
										else
										{//延时3秒进入
											
											Manual_Change_Knife_InvertTime=3;
											
												App_Modbus_Plc_Write_M_Status(201,M_ON);	
										//	if(App_FX_Plc_Force_Process("ON",M201)==0)
												{			
														App_Modbus_Plc_Write_M_Status(202,M_OFF);	
											//	if(App_FX_Plc_Force_Process("OFF",M202)==0)
													{	
															App_Modbus_Plc_Write_M_Status(200,M_ON);	
											//		if(App_FX_Plc_Force_Process("ON",M200)==0)
															{						//关闭其它状态
													//		cpGui_CreatePictureBox(&Manual_Knife_Picture_Enb);
																
																Normal_Knife_Status=0;
																Motor_Knife_Status=0;
																Manual_Knife_Status=1;		
																cpGui_CreatePictureBox(&Manual_Knife_Picture_Enb);
																cpGui_CreatePictureBox(&Motor_Knife_Picture_Dis);
																cpGui_CreatePictureBox(&Normal_Knife_Picture_Dis);	
																
																GLCD_SetWindow_Fill(CHANGE_KNIFE_WIN_X,CHANGE_KNIFE_WIN_Y+CHANGE_KNIFE_WIN_HIGH/2+16,CHANGE_KNIFE_WIN_X+CHANGE_KNIFE_WIN_WIDE-2,CHANGE_KNIFE_WIN_Y+CHANGE_KNIFE_WIN_HIGH/2+16+65,YELLOW_COLOR,YELLOW_COLOR);																
																if(Language==CHN_HAN)
																							{
																								
																							Printf24("注意：手动换刀，高度危险!!!   ",CHANGE_KNIFE_WIN_X+80,CHANGE_KNIFE_WIN_Y+CHANGE_KNIFE_WIN_HIGH/2+16,RED_COLOR,1,YELLOW_COLOR);	
																								
																					//		Printf24("注意：电动换刀，高度危险!!!   ",CHANGE_KNIFE_WIN_X+80,CHANGE_KNIFE_WIN_Y+CHANGE_KNIFE_WIN_HIGH/2,RED_COLOR,1,YELLOW_COLOR);
																							}
																							else
																							{
																								
																								
																							Printf24("NOTE: Manual tool change",CHANGE_KNIFE_WIN_X+80+50,CHANGE_KNIFE_WIN_Y+CHANGE_KNIFE_WIN_HIGH/2+16,RED_COLOR,1,YELLOW_COLOR);
																							Printf24("    Highly Hazardous!!!",CHANGE_KNIFE_WIN_X+80+50,CHANGE_KNIFE_WIN_Y+CHANGE_KNIFE_WIN_HIGH/2+16+22,RED_COLOR,1,YELLOW_COLOR);
																						//		memcpy(FX_Plc_ChangeKnife_Hint_Label.Text,"Note: Please select Tool Change, Highly Dangerous !!!",strlen("Note: Please select Tool Change, Highly Dangerous !!!"));//
																								
																								
																							}
																							
													//		Printf24("注意：手动换刀，高度危险!!!   ",CHANGE_KNIFE_WIN_X+80,CHANGE_KNIFE_WIN_Y+CHANGE_KNIFE_WIN_HIGH/2+16,RED_COLOR,1,YELLOW_COLOR);		

															GLCD_SetWindow_Fill(CHANGE_KNIFE_WIN_X,CHANGE_KNIFE_WIN_Y+32,CHANGE_KNIFE_WIN_X+CHANGE_KNIFE_WIN_WIDE-2,CHANGE_KNIFE_WIN_Y+32+65,YELLOW_COLOR,YELLOW_COLOR);
														//	memcpy(FX_Plc_ChangeKnife_Hint_Label.Text,"                             ",strlen("                             "));//
														//	cpGui_CreateLabel(FX_Plc_ChangeKnife_Hint_Label);//选择换刀	
															sprintf(FX_Plc_ChangeKnife_Hint_Label.Text,"%d",Manual_Change_Knife_InvertTime);
															cpGui_CreateLabel(FX_Plc_ChangeKnife_Hint_Label);//选择换刀																
														}			
													}		
												}												
											}							
									}
								}
						
					}
				}
			else
				{//已在手动换刀状态下。退出
					return;//无此状态执行
					
					#ifdef PLC_3U
					
						App_Modbus_Plc_Write_M_Status(200,M_OFF);	
				//	if(App_FX_Plc_Force_Process("OFF",M200)==0)
								{					
						cpGui_CreatePictureBox(&Manual_Knife_Picture_Dis);												
						Manual_Knife_Status=0;
							
							Printf24("                         ",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,RED_COLOR,1,0xffff);	
							
							CurrentArea_recover1(CHANGE_KNIFE_WIN_X,CHANGE_KNIFE_WIN_Y, CHANGE_KNIFE_WIN_WIDE,CHANGE_KNIFE_WIN_HIGH);
								}
					#else
					
				
					while(Plc_Poll_Enb_Flag==1)
					{
					if(Plc_Comm_Status==PLC_COMM_TIMEOUT)
						return;
						
					}//等特查询指令OK
					
					if(App_Plc_SendFrame_Process("WCS","R",0x0F,'0')==0)//开启RF
						{
							
						cpGui_CreatePictureBox(&Manual_Knife_Picture_Dis);													
						Manual_Knife_Status=0;
							
							Printf24("                         ",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,RED_COLOR,1,0xffff);	
							
							CurrentArea_recover1(CHANGE_KNIFE_WIN_X,CHANGE_KNIFE_WIN_Y, CHANGE_KNIFE_WIN_WIDE,CHANGE_KNIFE_WIN_HIGH);
						}
						
					#endif
				}
					
			}		

			
		//	/*
		//Fast_Knife_Picture_Enb    进入、退出换刀
		if((touch.x>=Fast_Knife_Picture_Enb.Location.x)&&(touch.x<Fast_Knife_Picture_Enb.Location.x+Fast_Knife_Picture_Enb.Size.width)&&\
			(touch.y>=Fast_Knife_Picture_Enb.Location.y)&&(touch.y<Fast_Knife_Picture_Enb.Location.y+Fast_Knife_Picture_Enb.Size.high))
			{			
			BellOn_Enb();
			if(Run_flag==1)
						return;//电机运行时退出				
			if(Pressure_Set_Status==1)
					return;
				if(FX_PLC_IO_Dis_Flag!=0)//状态显示是不入
					return;
				if(WorkMode==MANUAL_IO_TEST_MODE)
					return;
			if(Fast_Knife_Status==0)
				{
				//if((Manual_Knife_Status==0)&&(Motor_Knife_Status==0))
					{				
						#ifdef PLC_3U
						
						Fast_Knife_Status=1;					
						Manual_Knife_Status=0; //清手动换刀状态
						Motor_Knife_Status=0;  //清电动换刀状态
						Normal_Knife_Status=0;//清正常换刀						
						cpGui_CreatePictureBox(&Fast_Knife_Picture_Enb);							
						CurrentArea_save1(CHANGE_KNIFE_WIN_X,CHANGE_KNIFE_WIN_Y, CHANGE_KNIFE_WIN_WIDE,CHANGE_KNIFE_WIN_HIGH);	
						GLCD_SetWindow_Fill(CHANGE_KNIFE_WIN_X,CHANGE_KNIFE_WIN_Y,CHANGE_KNIFE_WIN_X+CHANGE_KNIFE_WIN_WIDE-1,CHANGE_KNIFE_WIN_Y+CHANGE_KNIFE_WIN_HIGH-1,YELLOW_COLOR,YELLOW_COLOR);//(cSystemColor));//.Location.x,label.Location.y,label.Location.x+label.Size.width,label.Location.y+label.Size.high,cpGui_ColorChange(label.bkColor),cpGui_ColorChange(label.bkColor));				
						GLCD_SetWindow_Fill(CHANGE_KNIFE_WIN_X,CHANGE_KNIFE_WIN_Y,CHANGE_KNIFE_WIN_X+CHANGE_KNIFE_WIN_WIDE-1,CHANGE_KNIFE_WIN_Y+31,cpGui_ColorChange(255),cpGui_ColorChange(255));	
						
						if(Language==CHN_HAN)
						{
						Printf24("警告！",CHANGE_KNIFE_WIN_X+CHANGE_KNIFE_WIN_WIDE/2-24-4,CHANGE_KNIFE_WIN_Y+5,RED_COLOR,0,0xffff);
						memcpy(FX_Plc_ChangeKnife_Hint_Label.Text,"注意：请选择换刀，高度危险!!!",strlen("注意：请选择换刀，高度危险!!!"));//
						cpGui_CreateLabel(FX_Plc_ChangeKnife_Hint_Label);//选择换刀
						}
						else
						{
						Printf24("Warn!",CHANGE_KNIFE_WIN_X+CHANGE_KNIFE_WIN_WIDE/2-24-4,CHANGE_KNIFE_WIN_Y+5,RED_COLOR,0,0xffff);
						Printf24("NOTE: Please select Tool Change",FX_Plc_ChangeKnife_Hint_Label.Location.x,FX_Plc_ChangeKnife_Hint_Label.Location.y,0,0,0);
						Printf24("     Highly Hazardous !!!",FX_Plc_ChangeKnife_Hint_Label.Location.x,FX_Plc_ChangeKnife_Hint_Label.Location.y+22,0,0,0);
					//		memcpy(FX_Plc_ChangeKnife_Hint_Label.Text,"Note: Please select Tool Change, Highly Dangerous !!!",strlen("Note: Please select Tool Change, Highly Dangerous !!!"));//
							
							
						}
						

						
					//	Printf24("注意：请选择换刀，高度危险!!!",CHANGE_KNIFE_WIN_X+80,CHANGE_KNIFE_WIN_Y+CHANGE_KNIFE_WIN_HIGH/2-100,RED_COLOR,0,0xffff);		
						
						cpGui_CreatePictureBox(&Manual_Knife_Picture_Dis);
						cpGui_CreatePictureBox(&Motor_Knife_Picture_Dis);
						cpGui_CreatePictureBox(&Normal_Knife_Picture_Dis);		

						#else
					while(Plc_Poll_Enb_Flag==1)
					{
					if(Plc_Comm_Status==PLC_COMM_TIMEOUT)
						return;
						
					}//等特查询指令OK	

					if(App_Plc_SendFrame_Process("WCS","R",0x15,'1')==0)//开启R11
						{
						cpGui_CreatePictureBox(&Fast_Knife_Picture_Enb);
						Fast_Knife_Status=1;	
							
							CurrentArea_save1(CHANGE_KNIFE_WIN_X,CHANGE_KNIFE_WIN_Y, CHANGE_KNIFE_WIN_WIDE,CHANGE_KNIFE_WIN_HIGH);	
							GLCD_SetWindow_Fill(CHANGE_KNIFE_WIN_X,CHANGE_KNIFE_WIN_Y,CHANGE_KNIFE_WIN_X+CHANGE_KNIFE_WIN_WIDE-1,CHANGE_KNIFE_WIN_Y+CHANGE_KNIFE_WIN_HIGH-1,cpGui_ColorChange(cSystemColor),cpGui_ColorChange(cSystemColor));//.Location.x,label.Location.y,label.Location.x+label.Size.width,label.Location.y+label.Size.high,cpGui_ColorChange(label.bkColor),cpGui_ColorChange(label.bkColor));				
							GLCD_SetWindow_Fill(CHANGE_KNIFE_WIN_X,CHANGE_KNIFE_WIN_Y,CHANGE_KNIFE_WIN_X+CHANGE_KNIFE_WIN_WIDE-1,CHANGE_KNIFE_WIN_Y+31,cpGui_ColorChange(255),cpGui_ColorChange(255));	
							Printf24("警告！",CHANGE_KNIFE_WIN_X+CHANGE_KNIFE_WIN_WIDE/2-24-4,CHANGE_KNIFE_WIN_Y+5,RED_COLOR,0,0xffff);
							Printf24("注意：快速换刀，高度危险!!!",CHANGE_KNIFE_WIN_X+80,CHANGE_KNIFE_WIN_Y+CHANGE_KNIFE_WIN_HIGH/2,RED_COLOR,0,0xffff);							
						//////			App_Plc_WCS_Return_Ok_Flag=0;
						//////			App_Plc_SendFrame("WCS","R",0x15,'1');
						//////			while(App_Plc_WCS_Return_Ok_Flag==0);				
						}		
						#endif
					}
				}
			else
				{
					
					#ifdef PLC_3U
					//退出时全关
						App_Modbus_Plc_Write_M_Status(200,M_OFF);	
				//	if(App_FX_Plc_Force_Process("OFF",M200)==0)
							{
									App_Modbus_Plc_Write_M_Status(201,M_OFF);	
						 //  if(App_FX_Plc_Force_Process("OFF",M201)==0)
								{
										App_Modbus_Plc_Write_M_Status(202,M_OFF);	
									
									
								App_Modbus_Plc_Write_M_Status(200,M_OFF);	
								App_Modbus_Plc_Write_M_Status(201,M_OFF);	
								App_Modbus_Plc_Write_M_Status(175,M_OFF);
					//			PLC_MainPower_YOUT_Status_Temp=0xFF;//刷新一下主电源状态
									
									
								//if(App_FX_Plc_Force_Process("OFF",M202)==0)
									{
									Fast_Knife_Status=0;
									Manual_Knife_Status=0; //清手动换刀状态
									Motor_Knife_Status=0;  //清电动换刀状态
										Normal_Knife_Status=0;//清正常换刀
									//恢复窗口
									CurrentArea_recover1(CHANGE_KNIFE_WIN_X,CHANGE_KNIFE_WIN_Y, CHANGE_KNIFE_WIN_WIDE,CHANGE_KNIFE_WIN_HIGH);
										
										cpGui_CreatePictureBox(&Fast_Knife_Picture_Dis);	
									}
								}									
							}
					
					
					#else
					
					while(Plc_Poll_Enb_Flag==1)
					{
					if(Plc_Comm_Status==PLC_COMM_TIMEOUT)
						return;
						
					}//等特查询指令OK
				if(App_Plc_SendFrame_Process("WCS","R",0x15,'0')==0)
					{
					cpGui_CreatePictureBox(&Fast_Knife_Picture_Dis);		
					//////					App_Plc_WCS_Return_Ok_Flag=0;
					//////					App_Plc_SendFrame("WCS","R",0x15,'0');//开启R11
					//////					while(App_Plc_WCS_Return_Ok_Flag==0);							
					Fast_Knife_Status=0;
					//恢复窗口
					CurrentArea_recover1(CHANGE_KNIFE_WIN_X,CHANGE_KNIFE_WIN_Y, CHANGE_KNIFE_WIN_WIDE,CHANGE_KNIFE_WIN_HIGH);
					}
					#endif
				}				
			}		
//*/
			
		//Motor_Knife_Picture_Enb  电动换刀
		if((touch.x>=Motor_Knife_Picture_Enb.Location.x)&&(touch.x<Motor_Knife_Picture_Enb.Location.x+Motor_Knife_Picture_Enb.Size.width)&&\
			(touch.y>=Motor_Knife_Picture_Enb.Location.y)&&(touch.y<Motor_Knife_Picture_Enb.Location.y+Motor_Knife_Picture_Enb.Size.high))
			{			
//////////			if(Fast_Knife_Status==0)
//////////					return;
			
				
			if(Fast_Knife_Status==0)
					return;
			
	//		return;
			
			
			BellOn_Enb();
			if(Run_flag==1)
						return;//电机运行时退出				
			if(Pressure_Set_Status==1)
					return;
				
			if(Motor_Knife_Status==0)
				{
			//	if((Manual_Knife_Status==0)&&(Fast_Knife_Status==0))
					{								
						
					#ifdef PLC_3U
						
							App_Modbus_Plc_Write_M_Status(200,M_OFF);	
				//	if(App_FX_Plc_Force_Process("OFF",M200)==0)
							{			
									App_Modbus_Plc_Write_M_Status(202,M_OFF);	
						//	if(App_FX_Plc_Force_Process("OFF",M202)==0)
								{	
												//关闭其它状态
										App_Modbus_Plc_Write_M_Status(201,M_ON);	
									
																		
						//		App_Modbus_Plc_Write_M_Status(200,M_OFF);	
						//		App_Modbus_Plc_Write_M_Status(201,M_OFF);	
								App_Modbus_Plc_Write_M_Status(175,M_OFF);
							//	PLC_MainPower_YOUT_Status_Temp=0xFF;//刷新一下主电源状态
									
				//if(App_FX_Plc_Force_Process("ON",M201)==0)
								{
									//			cpGui_CreatePictureBox(&Motor_Knife_Picture_Enb);		
						Normal_Knife_Status=0;
						Manual_Knife_Status=0;
						Motor_Knife_Status=1;
											cpGui_CreatePictureBox(&Manual_Knife_Picture_Dis);
											cpGui_CreatePictureBox(&Motor_Knife_Picture_Enb);
											cpGui_CreatePictureBox(&Normal_Knife_Picture_Dis);
						//x=;
						//y=ALL_FLAG_WIN_BASE_Y;
					//		CurrentArea_save1(CHANGE_KNIFE_WIN_X,CHANGE_KNIFE_WIN_Y, CHANGE_KNIFE_WIN_WIDE,CHANGE_KNIFE_WIN_HIGH);	
						//	GLCD_SetWindow_Fill(CHANGE_KNIFE_WIN_X,CHANGE_KNIFE_WIN_Y,CHANGE_KNIFE_WIN_X+CHANGE_KNIFE_WIN_WIDE-1,CHANGE_KNIFE_WIN_Y+CHANGE_KNIFE_WIN_HIGH-1,YELLOW_COLOR,YELLOW_COLOR);//(cSystemColor));//.Location.x,label.Location.y,label.Location.x+label.Size.width,label.Location.y+label.Size.high,cpGui_ColorChange(label.bkColor),cpGui_ColorChange(label.bkColor));				
						//	GLCD_SetWindow_Fill(CHANGE_KNIFE_WIN_X,CHANGE_KNIFE_WIN_Y,CHANGE_KNIFE_WIN_X+CHANGE_KNIFE_WIN_WIDE-1,CHANGE_KNIFE_WIN_Y+31,cpGui_ColorChange(255),cpGui_ColorChange(255));	
					//		Printf24("警告！",CHANGE_KNIFE_WIN_X+CHANGE_KNIFE_WIN_WIDE/2-24-4,CHANGE_KNIFE_WIN_Y+5,RED_COLOR,0,0xffff);
									
							
							GLCD_SetWindow_Fill(CHANGE_KNIFE_WIN_X,CHANGE_KNIFE_WIN_Y+CHANGE_KNIFE_WIN_HIGH/2+16,CHANGE_KNIFE_WIN_X+CHANGE_KNIFE_WIN_WIDE-2,CHANGE_KNIFE_WIN_Y+CHANGE_KNIFE_WIN_HIGH/2+16+65,YELLOW_COLOR,YELLOW_COLOR);
									
						if(Language==CHN_HAN)
						{
							Printf24("注意：电动换刀，高度危险!!!",CHANGE_KNIFE_WIN_X+80,CHANGE_KNIFE_WIN_Y+CHANGE_KNIFE_WIN_HIGH/2+16,RED_COLOR,1,YELLOW_COLOR);
						}
						else
						{
							
							
						Printf24("NOTE: Electric tool change",CHANGE_KNIFE_WIN_X+80+50,CHANGE_KNIFE_WIN_Y+CHANGE_KNIFE_WIN_HIGH/2+16,RED_COLOR,1,YELLOW_COLOR);
						Printf24("    Highly Hazardous!!!",CHANGE_KNIFE_WIN_X+80+50,CHANGE_KNIFE_WIN_Y+CHANGE_KNIFE_WIN_HIGH/2+16+22,RED_COLOR,1,YELLOW_COLOR);
					//		memcpy(FX_Plc_ChangeKnife_Hint_Label.Text,"Note: Please select Tool Change, Highly Dangerous !!!",strlen("Note: Please select Tool Change, Highly Dangerous !!!"));//
							
							
						}
						
							GLCD_SetWindow_Fill(CHANGE_KNIFE_WIN_X,CHANGE_KNIFE_WIN_Y+32,CHANGE_KNIFE_WIN_X+CHANGE_KNIFE_WIN_WIDE-2,CHANGE_KNIFE_WIN_Y+32+65,YELLOW_COLOR,YELLOW_COLOR);
								}
							}
						}
					#else			
					while(Plc_Poll_Enb_Flag==1)
					{
					if(Plc_Comm_Status==PLC_COMM_TIMEOUT)
						return;
						
					}//等特查询指令OK			

					if(App_Plc_SendFrame_Process("WCS","R",0x0E,'1')==0)
						{
						cpGui_CreatePictureBox(&Motor_Knife_Picture_Enb);		
					
						Motor_Knife_Status=1;
							
							

							
						//x=;
						//y=ALL_FLAG_WIN_BASE_Y;
							CurrentArea_save1(CHANGE_KNIFE_WIN_X,CHANGE_KNIFE_WIN_Y, CHANGE_KNIFE_WIN_WIDE,CHANGE_KNIFE_WIN_HIGH);	
							GLCD_SetWindow_Fill(CHANGE_KNIFE_WIN_X,CHANGE_KNIFE_WIN_Y,CHANGE_KNIFE_WIN_X+CHANGE_KNIFE_WIN_WIDE-1,CHANGE_KNIFE_WIN_Y+CHANGE_KNIFE_WIN_HIGH-1,cpGui_ColorChange(cSystemColor),cpGui_ColorChange(cSystemColor));//.Location.x,label.Location.y,label.Location.x+label.Size.width,label.Location.y+label.Size.high,cpGui_ColorChange(label.bkColor),cpGui_ColorChange(label.bkColor));				
							GLCD_SetWindow_Fill(CHANGE_KNIFE_WIN_X,CHANGE_KNIFE_WIN_Y,CHANGE_KNIFE_WIN_X+CHANGE_KNIFE_WIN_WIDE-1,CHANGE_KNIFE_WIN_Y+31,cpGui_ColorChange(255),cpGui_ColorChange(255));	
							Printf24("警告！",CHANGE_KNIFE_WIN_X+CHANGE_KNIFE_WIN_WIDE/2-24-4,CHANGE_KNIFE_WIN_Y+5,RED_COLOR,0,0xffff);
							Printf24("注意：电动换刀，高度危险!!!",CHANGE_KNIFE_WIN_X+80,CHANGE_KNIFE_WIN_Y+CHANGE_KNIFE_WIN_HIGH/2,RED_COLOR,0,0xffff);
						}
						#endif
					}
				}
			else
				{
					return;//无此状态执行
					
				#ifdef PLC_3U
					
					
						App_Modbus_Plc_Write_M_Status(201,M_OFF);	
					
						//	if(App_FX_Plc_Force_Process("OFF",M201)==0)
								{
									cpGui_CreatePictureBox(&Motor_Knife_Picture_Dis);														

					
										Motor_Knife_Status=0;

										//恢复窗口
										CurrentArea_recover1(CHANGE_KNIFE_WIN_X,CHANGE_KNIFE_WIN_Y, CHANGE_KNIFE_WIN_WIDE,CHANGE_KNIFE_WIN_HIGH);
									
								}
					#else
					
					while(Plc_Poll_Enb_Flag==1)
					{
					if(Plc_Comm_Status==PLC_COMM_TIMEOUT)
						return;
						
					}//等特查询指令OK		

										if(App_Plc_SendFrame_Process("WCS","R",0x0E,'0')==0)
										{
										cpGui_CreatePictureBox(&Motor_Knife_Picture_Dis);														
										//////				App_Plc_WCS_Return_Ok_Flag=0;
										//////				App_Plc_SendFrame("WCS","R",0x0E,'0');//开启R11
										//////				while(App_Plc_WCS_Return_Ok_Flag==0);
					
										Motor_Knife_Status=0;
										
										//恢复窗口
										CurrentArea_recover1(CHANGE_KNIFE_WIN_X,CHANGE_KNIFE_WIN_Y, CHANGE_KNIFE_WIN_WIDE,CHANGE_KNIFE_WIN_HIGH);
											
										}
						#endif
				}		
			}		
			
			
		//Normal_Knife_Picture_Enb  正常换刀
		if((touch.x>=Normal_Knife_Picture_Enb.Location.x)&&(touch.x<Normal_Knife_Picture_Enb.Location.x+Normal_Knife_Picture_Enb.Size.width)&&\
			(touch.y>=Normal_Knife_Picture_Enb.Location.y)&&(touch.y<Normal_Knife_Picture_Enb.Location.y+Normal_Knife_Picture_Enb.Size.high))
			{			
				if(Fast_Knife_Status==0)
					return;
			BellOn_Enb();
			if(Run_flag==1)
						return;//电机运行时退出				
			if(Pressure_Set_Status==1)
					return;
			
									
			#ifdef PLC_3U
			
						App_Modbus_Plc_Write_M_Status(200,M_OFF);	
					
						//if(App_FX_Plc_Force_Process("OFF",M200)==0)
							{
								
									App_Modbus_Plc_Write_M_Status(201,M_OFF);	
						   //if(App_FX_Plc_Force_Process("OFF",M201)==0)
								{
									
										App_Modbus_Plc_Write_M_Status(202,M_OFF);	
									
																		
								App_Modbus_Plc_Write_M_Status(200,M_OFF);	
								App_Modbus_Plc_Write_M_Status(201,M_OFF);	
								App_Modbus_Plc_Write_M_Status(175,M_OFF);
							//	PLC_MainPower_YOUT_Status_Temp=0xFF;//刷新一下主电源状态
						//		if(App_FX_Plc_Force_Process("OFF",M202)==0)
									{
									Fast_Knife_Status=0;
									Manual_Knife_Status=0; //清手动换刀状态
									Motor_Knife_Status=0;  //清电动换刀状态
									Normal_Knife_Status=0;//清正常换刀
									//恢复窗口
									CurrentArea_recover1(CHANGE_KNIFE_WIN_X,CHANGE_KNIFE_WIN_Y, CHANGE_KNIFE_WIN_WIDE,CHANGE_KNIFE_WIN_HIGH);
										
									cpGui_CreatePictureBox(&Fast_Knife_Picture_Dis);	
									}
								}									
							}
							
							#endif
							
							return;
							
				
			if(Normal_Knife_Status==0)
				{
			//	if((Manual_Knife_Status==0)&&(Fast_Knife_Status==0))
					{								

						
					#ifdef PLC_3U
							App_Modbus_Plc_Write_M_Status(200,M_OFF);	
					//if(App_FX_Plc_Force_Process("OFF",M200)==0)
							{			
									App_Modbus_Plc_Write_M_Status(201,M_OFF);	
							//if(App_FX_Plc_Force_Process("OFF",M201)==0)
								{	
												//关闭其它状态
									
										App_Modbus_Plc_Write_M_Status(202,M_ON);
									
										App_Modbus_Plc_Write_M_Status(175,M_OFF);	
							//PLC_MainPower_YOUT_Status_Temp=0xFF;//刷新一下主电源状态
									
							//	if(App_FX_Plc_Force_Process("ON",M202)==0)
								{
								//				cpGui_CreatePictureBox(&Motor_Knife_Picture_Enb);		
						Normal_Knife_Status=1;
						Manual_Knife_Status=0;
						Motor_Knife_Status=0;
									

											cpGui_CreatePictureBox(&Manual_Knife_Picture_Dis);
											cpGui_CreatePictureBox(&Motor_Knife_Picture_Dis);
											cpGui_CreatePictureBox(&Normal_Knife_Picture_Enb);
						//x=;
						//y=ALL_FLAG_WIN_BASE_Y;
						//		CurrentArea_save1(CHANGE_KNIFE_WIN_X,CHANGE_KNIFE_WIN_Y, CHANGE_KNIFE_WIN_WIDE,CHANGE_KNIFE_WIN_HIGH);	
						//	GLCD_SetWindow_Fill(CHANGE_KNIFE_WIN_X,CHANGE_KNIFE_WIN_Y,CHANGE_KNIFE_WIN_X+CHANGE_KNIFE_WIN_WIDE-1,CHANGE_KNIFE_WIN_Y+CHANGE_KNIFE_WIN_HIGH-1,YELLOW_COLOR,YELLOW_COLOR);//(cSystemColor));//.Location.x,label.Location.y,label.Location.x+label.Size.width,label.Location.y+label.Size.high,cpGui_ColorChange(label.bkColor),cpGui_ColorChange(label.bkColor));				
						//	GLCD_SetWindow_Fill(CHANGE_KNIFE_WIN_X,CHANGE_KNIFE_WIN_Y,CHANGE_KNIFE_WIN_X+CHANGE_KNIFE_WIN_WIDE-1,CHANGE_KNIFE_WIN_Y+31,cpGui_ColorChange(255),cpGui_ColorChange(255));	
						//		Printf24("警告！",CHANGE_KNIFE_WIN_X+CHANGE_KNIFE_WIN_WIDE/2-24-4,CHANGE_KNIFE_WIN_Y+5,RED_COLOR,0,0xffff);
								Printf24("     正常裁切，注意安全!!!   ",CHANGE_KNIFE_WIN_X+80,CHANGE_KNIFE_WIN_Y+CHANGE_KNIFE_WIN_HIGH/2,RED_COLOR,1,YELLOW_COLOR);
								}
							}
						}
					#else			
					while(Plc_Poll_Enb_Flag==1)
					{
					if(Plc_Comm_Status==PLC_COMM_TIMEOUT)
						return;
						
					}//等特查询指令OK			

					if(App_Plc_SendFrame_Process("WCS","R",0x0E,'1')==0)
						{
						cpGui_CreatePictureBox(&Motor_Knife_Picture_Enb);		
						
						Motor_Knife_Status=1;
							
							

							
						//x=;
						//y=ALL_FLAG_WIN_BASE_Y;
							CurrentArea_save1(CHANGE_KNIFE_WIN_X,CHANGE_KNIFE_WIN_Y, CHANGE_KNIFE_WIN_WIDE,CHANGE_KNIFE_WIN_HIGH);	
							GLCD_SetWindow_Fill(CHANGE_KNIFE_WIN_X,CHANGE_KNIFE_WIN_Y,CHANGE_KNIFE_WIN_X+CHANGE_KNIFE_WIN_WIDE-1,CHANGE_KNIFE_WIN_Y+CHANGE_KNIFE_WIN_HIGH-1,cpGui_ColorChange(cSystemColor),cpGui_ColorChange(cSystemColor));//.Location.x,label.Location.y,label.Location.x+label.Size.width,label.Location.y+label.Size.high,cpGui_ColorChange(label.bkColor),cpGui_ColorChange(label.bkColor));				
							GLCD_SetWindow_Fill(CHANGE_KNIFE_WIN_X,CHANGE_KNIFE_WIN_Y,CHANGE_KNIFE_WIN_X+CHANGE_KNIFE_WIN_WIDE-1,CHANGE_KNIFE_WIN_Y+31,cpGui_ColorChange(255),cpGui_ColorChange(255));	
							Printf24("警告！",CHANGE_KNIFE_WIN_X+CHANGE_KNIFE_WIN_WIDE/2-24-4,CHANGE_KNIFE_WIN_Y+5,RED_COLOR,0,0xffff);
							Printf24("注意：电动换刀，高度危险!!!",CHANGE_KNIFE_WIN_X+80,CHANGE_KNIFE_WIN_Y+CHANGE_KNIFE_WIN_HIGH/2,RED_COLOR,0,0xffff);
						}
						#endif
					}
				}
			else
				{
					return;//无此状态执行
					
				#ifdef PLC_3U
					
						App_Modbus_Plc_Write_M_Status(201,M_OFF);	
					
						//	if(App_FX_Plc_Force_Process("OFF",M201)==0)
								{
									cpGui_CreatePictureBox(&Motor_Knife_Picture_Dis);														
					
										Motor_Knife_Status=0;

										//恢复窗口
										CurrentArea_recover1(CHANGE_KNIFE_WIN_X,CHANGE_KNIFE_WIN_Y, CHANGE_KNIFE_WIN_WIDE,CHANGE_KNIFE_WIN_HIGH);
									
								}
					#else
					
					while(Plc_Poll_Enb_Flag==1)
					{
					if(Plc_Comm_Status==PLC_COMM_TIMEOUT)
						return;
						
					}//等特查询指令OK		

										if(App_Plc_SendFrame_Process("WCS","R",0x0E,'0')==0)
										{
										cpGui_CreatePictureBox(&Motor_Knife_Picture_Dis);														
										//////				App_Plc_WCS_Return_Ok_Flag=0;
										//////				App_Plc_SendFrame("WCS","R",0x0E,'0');//开启R11
										//////				while(App_Plc_WCS_Return_Ok_Flag==0);
					
										Motor_Knife_Status=0;
										
										//恢复窗口
										CurrentArea_recover1(CHANGE_KNIFE_WIN_X,CHANGE_KNIFE_WIN_Y, CHANGE_KNIFE_WIN_WIDE,CHANGE_KNIFE_WIN_HIGH);
											
										}
						#endif
				}	
			}				
			
			
			

		//Wind_Motor_Picture_Enb  //风泵开   改成单按扭
		if((touch.x>=Wind_Motor_Picture_Enb.Location.x)&&(touch.x<Wind_Motor_Picture_Enb.Location.x+Wind_Motor_Picture_Enb.Size.width)&&\
			(touch.y>=Wind_Motor_Picture_Enb.Location.y)&&(touch.y<Wind_Motor_Picture_Enb.Location.y+Wind_Motor_Picture_Enb.Size.high))
			{			
			BellOn_Enb();
			if(Run_flag==1)
						return;//电机运行时退出				
			if(Pressure_Set_Status==1)
					return;				
			
			
									#ifdef PLC_3U
				//	while(FX_Plc_Comm_Status!=' ');
			
								if(Wind_Motor_Status==0)
								{
							//	if(App_FX_Plc_Force_Process("OFF",M103)==0)
								{
									
										App_Modbus_Plc_Write_M_Status(102,M_ON);	
							//	if(App_FX_Plc_Force_Process("ON",M102)==0)
											{
												Wind_Motor_Status=1;
												
												cpGui_CreatePictureBox(&Wind_Motor_Picture_Enb);
												
											}									
								}				
							}
								else
									
								{
									
										App_Modbus_Plc_Write_M_Status(102,M_OFF);	
								//						if(App_FX_Plc_Force_Process("OFF",M102)==0)
								{
					//			if(App_FX_Plc_Force_Process("ON",M103)==0)
											{
												
													Wind_Motor_Status=0;
												cpGui_CreatePictureBox(&Wind_Motor_Picture_Dis);
											}									
								}	
									
								}
						
						#else
			
////////					while(Plc_Poll_Enb_Flag==1)
////////					{
////////					if(Plc_Comm_Status==PLC_COMM_TIMEOUT)
////////						return;
////////						
////////					}//等特查询指令OK			
				
					if(App_Plc_SendFrame_Process("WCS","R",0x13,'0')==0)
							{				
							//////				App_Plc_WCS_Return_Ok_Flag=0;
							//////				App_Plc_SendFrame("WCS","R",0x13,'0');//关闭R13
							//////				while(App_Plc_WCS_Return_Ok_Flag==0);
											
							if(App_Plc_SendFrame_Process("WCS","R",0x12,'1')==0)
										{
										//////				App_Plc_WCS_Return_Ok_Flag=0;
										//////				App_Plc_SendFrame("WCS","R",0x12,'1');//开启R12
										//////				while(App_Plc_WCS_Return_Ok_Flag==0);
				
										Wind_Motor_Status=1;
										}
							}
							#endif
			}


//////////		//Wind_Motor_Picture_Dis  //风泵关
//////////		if((touch.x>=Wind_Motor_Picture_Dis.Location.x)&&(touch.x<Wind_Motor_Picture_Dis.Location.x+Wind_Motor_Picture_Dis.Size.width)&&\
//////////			(touch.y>=Wind_Motor_Picture_Dis.Location.y)&&(touch.y<Wind_Motor_Picture_Dis.Location.y+Wind_Motor_Picture_Dis.Size.high))
//////////			{			
//////////			BellOn_Enb();
//////////			if(Run_flag==1)
//////////						return;//电机运行时退出				
//////////			if(Pressure_Set_Status==1)
//////////					return;				
//////////			
//////////						#ifdef PLC_3U
//////////						
//////////						if(App_FX_Plc_Force_Process("OFF",M102)==0)
//////////								{
//////////								if(App_FX_Plc_Force_Process("ON",M103)==0)
//////////											{
//////////												
//////////													Wind_Motor_Status=0;
//////////											}									
//////////								}
//////////						
//////////						#else
//////////			
//////////					while(Plc_Poll_Enb_Flag==1)
//////////					{
//////////					if(Plc_Comm_Status==PLC_COMM_TIMEOUT)
//////////						return;
//////////						
//////////					}//等特查询指令OK	

//////////			if(App_Plc_SendFrame_Process("WCS","R",0x12,'0')==0)
//////////				{
//////////											
//////////				//////	App_Plc_WCS_Return_Ok_Flag=0;
//////////				//////	App_Plc_SendFrame("WCS","R",0x12,'0');//关闭R12
//////////				//////	while(App_Plc_WCS_Return_Ok_Flag==0);
//////////											
//////////				if(App_Plc_SendFrame_Process("WCS","R",0x13,'1')==0)
//////////							{
//////////							//////	App_Plc_WCS_Return_Ok_Flag=0;
//////////							//////	App_Plc_SendFrame("WCS","R",0x13,'1');//开启R12
//////////							//////	while(App_Plc_WCS_Return_Ok_Flag==0);								
//////////							Wind_Motor_Status=0;
//////////							}											
//////////				}
//////////				#endif
//////////			}
			

		//Lamp_Picture_Enb  //灯开关
		if((touch.x>=Lamp_Picture_Enb.Location.x)&&(touch.x<Lamp_Picture_Enb.Location.x+Lamp_Picture_Enb.Size.width)&&\
			(touch.y>=Lamp_Picture_Enb.Location.y)&&(touch.y<Lamp_Picture_Enb.Location.y+Lamp_Picture_Enb.Size.high))
			{
			if(Run_flag==1)
						return;//电机运行时退出				

			if(Pressure_Set_Status==1)
					return;
			
			BellOn_Enb();
			
			if(Lamp_Status==0)
				{
					
				App_Modbus_Plc_Write_M_Status(104,M_ON);	
			//	if(App_FX_Plc_Force_Process("ON",M104)==0)
											{
						Lamp_Status=1;
				cpGui_CreatePictureBox(&Lamp_Picture_Enb);	
											}
				}
			else
				{
						App_Modbus_Plc_Write_M_Status(104,M_OFF);	
					//													if(App_FX_Plc_Force_Process("OFF",M104)==0)
											{
						Lamp_Status=0;
				cpGui_CreatePictureBox(&Lamp_Picture_Dis);	
											}
				}				
			}			
		}
		else
		{
		switch(EventType[FormActive[0]])
				{
				case Button_Type:
		//		buttemp=*EventButton;
				if(EventButton!=NULL)
				{
					//if(strcmp(EventButton->Text,"Default"))
				//	{
				//		WIFI_DEFAULT_HIGH();
					//}
					cpGui_Button_UpDown(EventButton,TOUCH_UP);
				}
				break;
				case Label_Type:
					break;
				case CheckBox_Type:
					break;
				case Chart_Type:
					break;
				case RadioButton_Type:
					break;		
				}
			//EventType=0;		
			}	
	}
}


unsigned char Pressure_Dis_Refish_Flag=0;


extern void Time_dis(void);//

unsigned char LinkUpDate_Flag=1;

//显示PLC连接状态
void PLC_DispLink_Status(void)
{
if(WorkStart_flag==0)
{
LinkUpDate_Flag=0;
return;	
	
}

if(Modbus_PLC_Link_Flag==1)
		{
			
			if(LinkUpDate_Flag!=0)
						{
							LinkUpDate_Flag=0;
							
							GLCD_SetWindow_Fill( 600, MARK_LABEL_Y, 600+200, MARK_LABEL_Y+30, cpGui_ColorChange(PLC_HINT_DIS_BAK_COLOR), cpGui_ColorChange(PLC_HINT_DIS_BAK_COLOR));//提
						if(Language==CHN_HAN)
									
						Printf24("    PLC已连接!",600,MARK_LABEL_Y+5,RED_COLOR,1,cpGui_ColorChange(PLC_HINT_DIS_BAK_COLOR));	
						else
						{
								Printf24("    PLC LINK!",600,MARK_LABEL_Y+5,RED_COLOR,1,cpGui_ColorChange(PLC_HINT_DIS_BAK_COLOR));	
						}
				//		Printf24("     PLC  已连接     ",PLC_HINT_DIS_X,PLC_HINT_DIS_Y+5,RED_COLOR,1,cpGui_ColorChange(PLC_HINT_DIS_BAK_COLOR));
						}
		}
else
			{
			if(LinkUpDate_Flag!=0)
						{
							LinkUpDate_Flag=0;
							
						GLCD_SetWindow_Fill( 600, MARK_LABEL_Y, 600+200, MARK_LABEL_Y+30, cpGui_ColorChange(PLC_HINT_DIS_BAK_COLOR), cpGui_ColorChange(PLC_HINT_DIS_BAK_COLOR));//提
						if(Language==CHN_HAN)
							Printf24("    PLC断开!  ",600,MARK_LABEL_Y+5,RED_COLOR,1,cpGui_ColorChange(PLC_HINT_DIS_BAK_COLOR));	
						else
						{
							Printf24("   PLC NO LINK!",600,MARK_LABEL_Y+5,RED_COLOR,1,cpGui_ColorChange(PLC_HINT_DIS_BAK_COLOR));	
							
						}
				//		Printf24("     PLC  已连接     ",PLC_HINT_DIS_X,PLC_HINT_DIS_Y+5,RED_COLOR,1,cpGui_ColorChange(PLC_HINT_DIS_BAK_COLOR));
						}

			}	
}


//信息提示显示
void PLC_FX_Hint_DisPlay(void)
{
char strtemp[16];
	Int16U Ms100t; 
			if(WorkStart_flag==0)
			{
				return;
			}
if((Pressure_Set_Status==0)&&(Manual_Knife_Status==0)&&(Motor_Knife_Status==0)&&(Fast_Knife_Status==0)&&(Knife_Change_Status==0))
		{
		if(WorkStart_flag!=0)
			{
				
				if(Pressure_Dis_Refish_Flag==0)
				{
					Pressure_Dis_Refish_Flag=1;
					
				sprintf(strtemp,"%0.2f",(float)(FX_Plc_PressureData)/100);		
				
				
				GLCD_SetWindow_Fill( 670, 600-8-32, 798,600-8-32+32, 0xffff, 0xffff);//提示框
				
				Printf24("P:",680,600-8-32,0,0,0x73ae);//cpGui_ColorChange(0xcbc4d6));
				Printf24(strtemp,680+25,600-8-32,0,0,0x73ae);//cpGui_ColorChange(0xcbc4d6));			
				Printf24("MPa",760,600-8-32,0,0,0x73ae);//cpGui_ColorChange(0xcbc4d6));				
					
				}
			}
		}	
		
if(Modbus_PLC_Link_Flag==1)
		{
			
			if(LinkUpDate_Flag!=0)
						{
							LinkUpDate_Flag=0;
							
				GLCD_SetWindow_Fill( PLC_HINT_DIS_X, REMIND_WINDOW_Y, PLC_HINT_DIS_X+(REMIND_WINDOW_X-PLC_HINT_DIS_X-6), REMIND_WINDOW_Y+30, cpGui_ColorChange(PLC_HINT_DIS_BAK_COLOR), cpGui_ColorChange(PLC_HINT_DIS_BAK_COLOR));//提
						Printf24("       PLC断开!      ",PLC_HINT_DIS_X,PLC_HINT_DIS_Y+5,RED_COLOR,1,cpGui_ColorChange(PLC_HINT_DIS_BAK_COLOR));	
				//		Printf24("     PLC  已连接     ",PLC_HINT_DIS_X,PLC_HINT_DIS_Y+5,RED_COLOR,1,cpGui_ColorChange(PLC_HINT_DIS_BAK_COLOR));
						}
						
//////////			while(1)//程序停止，不能再进行操作
//////////			{
//////////				if(Ms_Flag==1)
//////////				{
//////////					
//////////					Ms_Flag=0;
//////////					         Ms100t++;
//////////         if(Ms100t>=200)
//////////             {
//////////             Ms100t=0;
//////////		     read_time();
//////////		     Time_dis();
//////////             } 
//////////					
//////////				}
//////////				
//////////			}
			
			return;
		}
else
	
		{			
			

			
		if(Manual_Knife_Status==1)
			{
				
//////////						if((PLC_X_Status[1][2]=='0'))
//////////							{			
//////////							Printf24("    刀锁信号没到位      ",PLC_HINT_DIS_X,PLC_HINT_DIS_Y,RED_COLOR,1,cpGui_ColorChange(PLC_HINT_DIS_BAK_COLOR));								
//////////						
//////////							return;								
//////////							}
//////////					else
//////////						 Printf24("                         ",PLC_HINT_DIS_X,PLC_HINT_DIS_Y,RED_COLOR,1,cpGui_ColorChange(PLC_HINT_DIS_BAK_COLOR));
					return;					
				
			}

					if((PLC_X_Status[1][2]=='0'))
					{
							X12_Status=0;
						
					}
					else
					{
							X12_Status=1;
					}
					
											if((PLC_X_Status[1][3]=='0'))
					{
							X13_Status=0;
						
					}
					else
					{
							X13_Status=1;
					}
			
					
																if((PLC_X_Status[2][1]=='0'))
					{
							X21_Status=0;
						
					}
					else
					{
							X21_Status=1;
					}
					
			
			
						if((PLC_X_Status[1][6]=='0'))
					{
							X16_Status=0;
						
					}
					else
					{
							X16_Status=1;
					}
					
		if((PLC_X_Status[1][7]=='0'))
				{
					X17_Status=0;							
				}
		else
				{			
				X17_Status=1;
				}
				//只要一路断开。就提示“当前换刀"
				if((X12_Status==0)||(X13_Status==0)||(X21_Status==0))
				{
					GLCD_SetWindow_Fill( PLC_HINT_DIS_X, REMIND_WINDOW_Y, PLC_HINT_DIS_X+(REMIND_WINDOW_X-PLC_HINT_DIS_X-6), REMIND_WINDOW_Y+30, cpGui_ColorChange(PLC_HINT_DIS_BAK_COLOR), cpGui_ColorChange(PLC_HINT_DIS_BAK_COLOR));//提示框
					if(Language==CHN_HAN)
						Printf24("      当前换刀       ",PLC_HINT_DIS_X,PLC_HINT_DIS_Y+5,RED_COLOR,1,cpGui_ColorChange(PLC_HINT_DIS_BAK_COLOR));
					else
					  Printf24("Current Knife Change",PLC_HINT_DIS_X,PLC_HINT_DIS_Y+5,RED_COLOR,1,cpGui_ColorChange(PLC_HINT_DIS_BAK_COLOR));
					
					LinkUpDate_Flag=0;
				}
			
			if((PLC_X_Status[1][0]=='0')&&(PLC_X_Status[1][1]=='0'))//判断双手
					{
					if((X12_Status==0)||(X13_Status==0)||(X21_Status==0))
						{
						LinkUpDate_Flag=0;							
						}
						else
						{
						if(LinkUpDate_Flag==0)
								{
								LinkUpDate_Flag=1;
									
		//						FX_Plc_PressureData_Download_Flag=1;//更新一下压力值		
		//						FX_Plc_Foot_PressureData_Download_Flag=1;
								GLCD_SetWindow_Fill( PLC_HINT_DIS_X, REMIND_WINDOW_Y, PLC_HINT_DIS_X+(REMIND_WINDOW_X-PLC_HINT_DIS_X-6), REMIND_WINDOW_Y+30, cpGui_ColorChange(PLC_HINT_DIS_BAK_COLOR), cpGui_ColorChange(PLC_HINT_DIS_BAK_COLOR));//提示框
								
								//Printf32(" PLC  已连接 ",PLC_HINT_DIS_X,REMIND_WINDOW_Y,GREEN_COLOR,1,cpGui_ColorChange(PLC_HINT_DIS_BAK_COLOR));										
								//	Printf24("      当前换刀       ",PLC_HINT_DIS_X,PLC_HINT_DIS_Y+5,RED_COLOR,1,cpGui_ColorChange(PLC_HINT_DIS_BAK_COLOR));
								//	else
								if(Language==CHN_HAN)
									Printf24("     PLC  已连接     ",PLC_HINT_DIS_X,PLC_HINT_DIS_Y+5,RED_COLOR,1,cpGui_ColorChange(PLC_HINT_DIS_BAK_COLOR));
								else
									Printf24("     PLC  is Link     ",PLC_HINT_DIS_X,PLC_HINT_DIS_Y+5,RED_COLOR,1,cpGui_ColorChange(PLC_HINT_DIS_BAK_COLOR));
								}
						}
						
					//	Printf24("                    ",PLC_HINT_DIS_X,PLC_HINT_DIS_Y,RED_COLOR,1,cpGui_ColorChange(cSystemBKColor));
						
											if((PLC_X_Status[0][6]=='0')&&(PLC_X_Status[0][5]=='0'))
							{			
						//	Printf24("  PLC故障  ",PLC_HINT_DIS_X,PLC_HINT_DIS_Y,RED_COLOR,1,cpGui_ColorChange(PLC_HINT_DIS_BAK_COLOR));								
							Plc_X_Err_Status=1;
							return;								
							}
					if((PLC_X_Status[0][6]=='0')&&(PLC_X_Status[0][5]=='1'))
							{								
						//	Printf24("  PLC故障  ",PLC_HINT_DIS_X,PLC_HINT_DIS_Y,RED_COLOR,1,cpGui_ColorChange(PLC_HINT_DIS_BAK_COLOR));
							Plc_X_Err_Status=2;
							return;								
							}
					if((PLC_X_Status[0][6]=='1')&&(PLC_X_Status[0][5]=='0'))
							{								
					//		Printf24("  PLC故障  ",PLC_HINT_DIS_X,PLC_HINT_DIS_Y,RED_COLOR,1,cpGui_ColorChange(PLC_HINT_DIS_BAK_COLOR));
								Plc_X_Err_Status=3;
							return;								
							}
					if((PLC_X_Status[0][6]=='1')&&(PLC_X_Status[0][5]=='1'))
							{								
					//		Printf24("                    ",PLC_HINT_DIS_X,PLC_HINT_DIS_Y,RED_COLOR,1,cpGui_ColorChange(cSystemBKColor));
							Plc_X_Err_Status=0;
							return;								
							}		
							/*
					if((PLC_X_Status[0][6]=='0')&&(PLC_X_Status[0][5]=='0'))
							{			
							Printf24("X6上下半周、X5单次不正常!",PLC_HINT_DIS_X,PLC_HINT_DIS_Y,RED_COLOR,1,cpGui_ColorChange(PLC_HINT_DIS_BAK_COLOR));								
							Plc_X_Err_Status=1;
							return;								
							}
					if((PLC_X_Status[0][6]=='0')&&(PLC_X_Status[0][5]=='1'))
							{								
							Printf24("  X6 上下半周不正常！    ",PLC_HINT_DIS_X,PLC_HINT_DIS_Y,RED_COLOR,1,cpGui_ColorChange(PLC_HINT_DIS_BAK_COLOR));
							Plc_X_Err_Status=2;
							return;								
							}
					if((PLC_X_Status[0][6]=='1')&&(PLC_X_Status[0][5]=='0'))
							{								
							Printf24("  X5 单次信号不正常！    ",PLC_HINT_DIS_X,PLC_HINT_DIS_Y,RED_COLOR,1,cpGui_ColorChange(PLC_HINT_DIS_BAK_COLOR));
								Plc_X_Err_Status=3;
							return;								
							}
					if((PLC_X_Status[0][6]=='1')&&(PLC_X_Status[0][5]=='1'))
							{								
							Printf24("                         ",PLC_HINT_DIS_X,PLC_HINT_DIS_Y,RED_COLOR,1,cpGui_ColorChange(PLC_HINT_DIS_BAK_COLOR));
							Plc_X_Err_Status=0;
							return;								
							}		*/
					return;
					}
					
					

			
//////////			if((PLC_X_Status[1][0]=='1')&&(PLC_X_Status[1][1]=='1'))//判断双手
//////////					{
//////////					if((PLC_X_Status[1][2]=='0'))
//////////							{			
//////////							Printf24("    刀锁信号没到位      ",PLC_HINT_DIS_X,PLC_HINT_DIS_Y,RED_COLOR,1,cpGui_ColorChange(PLC_HINT_DIS_BAK_COLOR));								
//////////						
//////////							return;								
//////////							}
//////////					else
//////////						 Printf24("                         ",PLC_HINT_DIS_X,PLC_HINT_DIS_Y,RED_COLOR,1,cpGui_ColorChange(PLC_HINT_DIS_BAK_COLOR));
//////////					return;					
//////////					}	
	//	Printf24(" PLC  已连接 ",PLC_HINT_DIS_X,PLC_HINT_DIS_Y,RED_COLOR,1,cpGui_ColorChange(PLC_HINT_DIS_BAK_COLOR));			
	//	Printf24("                    ",PLC_HINT_DIS_X,PLC_HINT_DIS_Y,RED_COLOR,1,cpGui_ColorChange(PLC_HINT_DIS_BAK_COLOR));					
		}

		//	Printf24("                         ",PLC_HINT_DIS_X,PLC_HINT_DIS_Y,RED_COLOR,1,cpGui_ColorChange(PLC_HINT_DIS_BAK_COLOR));
	

}



unsigned char X_Status_Need_Disp[]={0,1,2,3,4,5,6,7,10,11,12,0xAA,14,15,16,17,20,21,22,23,24,25,26,27,30,31,32,0xAA};
const unsigned char  	X_Status_Need_Disp_Hint[][16]={
	"原点",	  //X 0
	"刀",  //X 1 
	"左手",      //X 2
	"右手",	 //X 3
	"光电",	 //X 4
	"单次",	     //X 5
	"上下半周",	 //X 6
	"压纸",	     //X 7
	"刀锁到位",	   //X10
	"急停",	   //X11
	"托板",	 //X12
	"空",	 //X13
	"拍风",	     //X14
	"解锁压",	   //X15
	"拉刀开关左",//X16
	"拉刀开关右",//X17
	"脚踩开关",	//X20
	"换刀开关",	//X21
	"前限位",	  //X22
	"后限位",	  //X23
	"原点信号",	//X24
	"托板信号",	//X25
	"压纸信号",	//X26
	"切刀信号",	//X27
	"中限位",	//X30
	"压力",	//X31
	"选择压力"};	//X32

	
	const unsigned char  	X_Status_Need_Disp_Hint_EN[][16]={
	"Ori_Limit",	  //X 0
	"K-Signal",  //X 1 
	"Hand L",      //X 2
	"Hand R",	 //X 3
	"PhotoElec",	 //X 4
	"Single",	     //X 5
	"UD Half",	 //X 6
	"P-Signal",	     //X 7
	"K-Lock",	   //X10
	"Emerg",	   //X11
	"M_Limit",	 //X12
	"null",	 //X13
	"Wind",	     //X14
	"UnLock Pres",	   //X15
	"Broach SW L",//X16
	"Broach SW R",//X17
	"Foot SW",	//X20
	"Change SW",	//X21
	"F_Limit",	  //X22
	"B_Limit",	  //X23
	"Ori_Limit",	//X24
	"Pallet signal",	//X25
	"Press",	//X26
	"Cut signal",	//X27
	"M_Limit",	//X30
	"Pressure",	//X31
	"Sel Pressure"};	//X32

	
unsigned char Y_Status_Need_Disp[]={20,21,22,23,24,25,26,27,30,31,0xAA,33,34,40,41,43,44,50,0xAA};//,12,13,14,15,16,17,20,21,22,23,40,0xAA};
 const unsigned char 	Y_Status_Need_Disp_Hint[][16]={
	"主接触器",//Y20
	"Y接触器",//Y21
	"△接触器",//Y22
	"风泵接触器",	//Y23
	"刀锁",//Y24
	"下压阀",	//Y25
	"锁压阀",//Y26
	"下刀阀1",//Y27
	"下刀阀2",	//Y30
	"日光灯",		 //Y31
	"Null",
	"对刀灯"};

	
	
 const unsigned char 	Y_Status_Need_Disp_Hint_EN[][16]={
	"M Relay",
	"Y Relay",
	"△Relay",
	"Pump Realy",	
	"K Lock",
	"P Down Va",	
	"P Lock Va",	
	"Down Va 1",	
	"Down Va 2",		 
	"Lamp",
	"Null"};
	
	
	
	
	

	
	int errflashtime=0;
	unsigned char errflash_flag=0;
//状态显示
void FX_PLC_XY_Status_Display(void)
{
int i,n;
int xp,yp;
	
int index;

	
unsigned char *pdn;
	
char strtmp[16];
	
	
errflashtime++;
	if(errflashtime>=50)
	{
		errflashtime=0;
		if(errflash_flag==0)
			errflash_flag=1;
		else
			errflash_flag=0;
	}
	
		
	if(WorkMode!=MANUAL_IO_TEST_MODE)//非测试模式下，退出
		return;
	

	
//if((WorkMode!=AUTO_IO_MODE))
//	if((WorkMode!=TEACH_IO_MODE))
	//	if((WorkMode!=MANUAL_IO_MODE))
			
////////		if(FX_PLC_IO_Dis_Flag!=1)
////////		{
////////			if(WorkStart_flag==1)
////////			{//IO状态显示  需要则打开
////////			if((Plc_X_Err_Status!=0)&&(errflash_flag==1))
////////			{
////////				GLCD_SetWindow_Fill(IO_DIS_X,IO_DIS_Y,IO_DIS_X+40-1,IO_DIS_Y+40-1,cpGui_ColorChange(cSystemColor),cpGui_ColorChange(cSystemColor));//cpGui_ColorChange(cSystemColor),cpGui_ColorChange(cSystemColor));//.Location.x,label.Location.y,label.Location.x+label.Size.width,label.Location.y+label.Size.high,cpGui_ColorChange(label.bkColor),cpGui_ColorChange(label.bkColor));				
////////			}
////////			else		
////////			{				
////////			//	IoTestButton_dis(IO_DIS_X,IO_DIS_Y);
////////			}
////////			
////////		}
////////	return;			
////////	}
	//	IoTestButton_dis(IO_DIS_X,IO_DIS_Y);


if((Pressure_Set_Status==0)&&(Manual_Knife_Status==0)&&(Motor_Knife_Status==0)&&(Fast_Knife_Status==0)&&(Knife_Change_Status==0))
		{
			
		xp=95;
		yp=FX_PLC_IO_STATUS_WIN_Y+40+40;

			
			pdn=X_Status_Need_Disp;
			n=0;
			i=0;
			while(*pdn!=0xAA)
			{
	//	for(n=0;n<8;n++)
		{
			sprintf(strtmp,"X%02d",*pdn);
//////////			switch(Plc_X_Err_Status)
//////////					{
//////////					case 0://正常显示			
//////////							if((*pdn!=16)&&(*pdn!=17))
//////////								{						
//////////						if(PLC_X_Status[*pdn/10][*pdn%10]=='0')
//////////							{
//////////							Printf24(strtmp,xp,yp,BLACK_COLOR,1,UP_COL);
//////////							}
//////////						else
//////////							{
//////////							Printf24(strtmp,xp,yp,BLACK_COLOR,1,DOWN_COL);
//////////							}	
//////////						}
//////////							break;
//////////					case 1://"X6上下半周、X5单次不正常!"
//////////						if(((errflash_flag==1)&&*pdn==6)||((errflash_flag==1)&&*pdn==5))
//////////							{
//////////							Printf24(strtmp,xp,yp,YELLOW_COLOR,1,YELLOW_COLOR);							
//////////							}
//////////						else
//////////							{
//////////							if((*pdn!=16)&&(*pdn!=17))
//////////								{
//////////							if(PLC_X_Status[*pdn/10][*pdn%10]=='0')
//////////								{
//////////								Printf24(strtmp,xp,yp,BLACK_COLOR,1,UP_COL);
//////////								}
//////////							else
//////////								{
//////////								Printf24(strtmp,xp,yp,BLACK_COLOR,1,DOWN_COL);
//////////								}			
//////////							}								
//////////							}
//////////						break;
//////////					case 2:// X6 上下半周不正常！
//////////						if(((errflash_flag==1)&&(*pdn==6)))
//////////							{
//////////							Printf24(strtmp,xp,yp,YELLOW_COLOR,1,YELLOW_COLOR);							
//////////							}
//////////						else
//////////							{
//////////															if((*pdn!=16)&&(*pdn!=17))
//////////								{
//////////							if(PLC_X_Status[*pdn/10][*pdn%10]=='0')
//////////								{
//////////								Printf24(strtmp,xp,yp,BLACK_COLOR,1,UP_COL);
//////////								}
//////////							else
//////////								{
//////////								Printf24(strtmp,xp,yp,BLACK_COLOR,1,DOWN_COL);
//////////								}		
//////////							}								
//////////							}						
//////////						break;
//////////					case 3: //X5 单次信号不正常！  
//////////						if(((errflash_flag==1)&&*pdn==5))
//////////							{
//////////							Printf24(strtmp,xp,yp,YELLOW_COLOR,1,YELLOW_COLOR);							
//////////							}
//////////						else
//////////							{
//////////							if((*pdn!=16)&&(*pdn!=17))
//////////								{
//////////								if(PLC_X_Status[*pdn/10][*pdn%10]=='0')
//////////									{
//////////									Printf24(strtmp,xp,yp,BLACK_COLOR,1,UP_COL);
//////////									}
//////////								else
//////////									{
//////////									Printf24(strtmp,xp,yp,BLACK_COLOR,1,DOWN_COL);
//////////									}		
//////////								}								
//////////							}						
//////////						break;
//////////					}
					
////////					if(*pdn==16)
////////					{
////////			if(X16_Status==0)
////////			{
////////						if(((errflash_flag==1)&&*pdn==16))
////////							{
////////							Printf24(strtmp,xp,yp,YELLOW_COLOR,1,YELLOW_COLOR);							
////////							}
////////							else
////////							{
////////					if(PLC_X_Status[*pdn/10][*pdn%10]=='0')
////////								{
////////								Printf24(strtmp,xp,yp,BLACK_COLOR,1,UP_COL);
////////								}
////////							else
////////								{
////////								Printf24(strtmp,xp,yp,BLACK_COLOR,1,DOWN_COL);
////////								}	
////////							}
////////			}
////////			else
////////			{
////////												if(PLC_X_Status[*pdn/10][*pdn%10]=='0')
////////									{
////////									Printf24(strtmp,xp,yp,BLACK_COLOR,1,UP_COL);
////////									}
////////								else
////////									{
////////									Printf24(strtmp,xp,yp,BLACK_COLOR,1,DOWN_COL);
////////									}	
////////			}
////////		}
					
////////		if(*pdn==17)
////////					{
////////					if(X17_Status==0)
////////						{
////////									if(((errflash_flag==1)&&*pdn==17))
////////										{
////////										Printf24(strtmp,xp,yp,YELLOW_COLOR,1,YELLOW_COLOR);							
////////										}		
////////								else
////////								{
////////								if(PLC_X_Status[*pdn/10][*pdn%10]=='0')
////////											{
////////											Printf24(strtmp,xp,yp,BLACK_COLOR,1,UP_COL);
////////											}
////////										else
////////											{
////////											Printf24(strtmp,xp,yp,BLACK_COLOR,1,DOWN_COL);
////////											}	
////////								}	
////////						}
////////									else
////////						{
////////															if(PLC_X_Status[*pdn/10][*pdn%10]=='0')
////////												{
////////												Printf24(strtmp,xp,yp,BLACK_COLOR,1,UP_COL);
////////												}
////////											else
////////												{
////////												Printf24(strtmp,xp,yp,BLACK_COLOR,1,DOWN_COL);
////////												}	
////////						}
////////					}
					
					sprintf(strtmp,"X%02d",*pdn);
					
				if(PLC_X_Status[*pdn/10][*pdn%10]=='0')
									{
									Printf24(strtmp,xp,yp,BLACK_COLOR,1,UP_COL);
									}
					else
								{
								Printf24(strtmp,xp,yp,BLACK_COLOR,1,DOWN_COL);
								}	
												
			if(Language==CHN_HAN)
				Printf16(X_Status_Need_Disp_Hint[i],xp,yp+26,BLACK_COLOR,0,DOWN_COL);	
			else
				Printf16(X_Status_Need_Disp_Hint_EN[i],xp,yp+26,BLACK_COLOR,0,DOWN_COL);	
				

			pdn++;
			i++;
				n++;
			xp+=78;			
			}		
			if(n>=6)
			{
			n=0;
			xp=95;
			yp+=50;		
			}
		

			}
			
			
			//Y状态
			xp=95;
			yp=275+50-4-20;

//////////			for(int n=0;n<4;n++)
//////////			{
//////////						sprintf(strtmp,"x%02x",FX_PLC_Y_StatusBuf[n]);	
//////////				
//////////					Printf24(strtmp,xp+n*32,yp+80,BLACK_COLOR,1,UP_COL);
//////////			}
			
			
			pdn=Y_Status_Need_Disp;
			n=0;
			i=0;
			while(*pdn!=0xAA)
			{
	//	for(n=0;n<8;n++)
		{
			 index=*pdn;
			sprintf(strtmp,"Y%02d",index);//*pdn);
			
			
			index-=20;
			
			if(PLC_Y_Status[index/10][index%10]=='0')
				{
				Printf24(strtmp,xp,yp,BLACK_COLOR,1,UP_COL);
				}
			else
				{
				Printf24(strtmp,xp,yp,BLACK_COLOR,1,DOWN_COL);
				}	

			if(Language==CHN_HAN)				
					Printf16(Y_Status_Need_Disp_Hint[i],xp,yp+26,BLACK_COLOR,0,DOWN_COL);				
			else
					Printf16(Y_Status_Need_Disp_Hint_EN[i],xp,yp+26,BLACK_COLOR,0,DOWN_COL);	
			

			pdn++;
			i++;
				n++;
			xp+=78;			
			}		
			if(n>=6)
			{
				n=0;
			xp=95;
			yp+=50;		
			}
		

			}			

		}


	
	
//////	xp=110;
//////	yp=470;

//////	for(i=0;i<4;i++)
//////	{
//////		for(n=0;n<8;n++)
//////		{
//////		sprintf(strtmp,"Y%02d",(i+2)*10+n);
//////		if(PLC_Y_Status[i][n]=='0')
//////			{
//////			Printf24(strtmp,xp,yp,BLACK_COLOR,1,UP_COL);
//////			}
//////		else
//////			{
//////			Printf24(strtmp,xp,yp,BLACK_COLOR,1,DOWN_COL);
//////			}	
//////		xp+=60;			
//////		}		
//////	xp=110;
//////	yp+=30;		
//////	}
	
////}
	
//IO_Stus_Dis(11,IO_STUS_X4,IO_STUS_Y2 ,DOWN_COL);
	
}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>



//当参数改变后，且按保存键时，转换并保存参数


void FX_PLC_ChangeAndSave_ParaData(void)
{
	
////////	extern unsigned int Motor_StartUpTime;//电机启动时间
////////extern unsigned int Motor_StopTime;//电机停止时间
////////extern unsigned int KnifeDownTime;//下刀时间
////////extern unsigned char CutOpt_Flag;//裁切优化 《开关》
////////extern unsigned int CutTime;   //优化时间  
////////extern unsigned int FastCut_Flag;  //快速裁切 《开关》	
	
////////	Motor_StartUpTime=atoi(FX_Plc_Set_MotorStartUpTime_Data_Label.Text);
	
	Motor_StopTime=atoi(FX_Plc_Set_MotorStopTime_Data_Label.Text);
	
//////	KnifeDownTime=atoi(FX_Plc_Set_KnifeDownTime_Data_Label.Text);
//////	
//////	if(strcmp(FX_Plc_Set_CutOpt_Data_Label.Text,"关闭")==0)
//////		CutOpt_Flag=0;
//////	else
//////		CutOpt_Flag=1;
//////	
//////CutTime=atoi(FX_Plc_Set_CutTime_Data_Label.Text);
//////	
//////	
//////		if(strcmp(FX_Plc_Set_FastCut_Enb_Data_Label.Text,"关闭")==0)
//////		FastCut_Flag=0;
//////	else
//////		FastCut_Flag=1;
	
	PLC_Save_Config();//保存参数
}



void FX_PLC_Setup_ParaData_Init(void)
{
	
//标签显示
if(Language==CHN_HAN)
{
//////////	memcpy(FX_Plc_Set_MotorStartUpTime_Label.Text,"电机启动时间:",14);
	memcpy(FX_Plc_Set_MotorStopTime_Label.Text,"电机停止时间:",14);
//////////	memcpy(FX_Plc_Set_KnifeDownTime_Label.Text,"下刀时间:",10);
//////////	memcpy(FX_Plc_Set_CutOpt_Label.Text,"裁切优化:",10);
//////////	memcpy(FX_Plc_Set_CutTime_Label.Text,"优化时间:",10);
//////////	memcpy(FX_Plc_Set_FastCut_Enb_Label.Text,"快速裁切:",10);
	
//////////cpGui_CreateLabel(FX_Plc_Set_MotorStartUpTime_Label);	
cpGui_CreateLabel(FX_Plc_Set_MotorStopTime_Label);	
////////cpGui_CreateLabel(FX_Plc_Set_KnifeDownTime_Label);	
////////cpGui_CreateLabel(FX_Plc_Set_CutOpt_Label);	
////////cpGui_CreateLabel(FX_Plc_Set_CutTime_Label);	
////////cpGui_CreateLabel(FX_Plc_Set_FastCut_Enb_Label);	
	
	
	
	
}
else
{
	
//////	memcpy(FX_Plc_Set_MotorStartUpTime_Label.Text,"MOT Stat Tim:",14);
	memcpy(FX_Plc_Set_MotorStopTime_Label.Text,"MOT Stop Tim:",14);
//////	memcpy(FX_Plc_Set_KnifeDownTime_Label.Text,"Down Knf Tim:",14);
//////	memcpy(FX_Plc_Set_CutOpt_Label.Text, 			 "Optimize Cut:",14);
//////	memcpy(FX_Plc_Set_CutTime_Label.Text,			 "Optimize Tim:",14);
//////	memcpy(FX_Plc_Set_FastCut_Enb_Label.Text,  "Fast Cut:",10);
	
////////cpGui_CreateLabel(FX_Plc_Set_MotorStartUpTime_Label);	
cpGui_CreateLabel(FX_Plc_Set_MotorStopTime_Label);	
//////cpGui_CreateLabel(FX_Plc_Set_KnifeDownTime_Label);	
//////cpGui_CreateLabel(FX_Plc_Set_CutOpt_Label);	
//////cpGui_CreateLabel(FX_Plc_Set_CutTime_Label);	
//////cpGui_CreateLabel(FX_Plc_Set_FastCut_Enb_Label);	
	}
	
//数据显示
	
////////	extern unsigned int Motor_StartUpTime;//电机启动时间
////////extern unsigned int Motor_StopTime;//电机停止时间
////////extern unsigned int KnifeDownTime;//下刀时间
////////extern unsigned char CutOpt_Flag;//裁切优化 《开关》
////////extern unsigned int CutTime;   //优化时间  
////////extern unsigned int FastCut_Flag;  //快速裁切 《开关》
	
//////	sprintf(FX_Plc_Set_MotorStartUpTime_Data_Label.Text,"%d",Motor_StartUpTime);//电机启动时间
//////cpGui_CreateLabel(FX_Plc_Set_MotorStartUpTime_Data_Label);
	
	sprintf(FX_Plc_Set_MotorStopTime_Data_Label.Text,"%d",Motor_StopTime);//电机停止时间
cpGui_CreateLabel(FX_Plc_Set_MotorStopTime_Data_Label);

////////sprintf(FX_Plc_Set_KnifeDownTime_Data_Label.Text,"%d",KnifeDownTime);//下刀时间
////////cpGui_CreateLabel(FX_Plc_Set_KnifeDownTime_Data_Label);

//////////	
//////////	if(Language==CHN_HAN)
//////////	{
//////////	if(CutOpt_Flag==0)
//////////		memcpy(FX_Plc_Set_CutOpt_Data_Label.Text,"关闭",5);
//////////	else
//////////		memcpy(FX_Plc_Set_CutOpt_Data_Label.Text,"打开",5);		
//////////		
//////////	}
//////////else
//////////	{
//////////	if(CutOpt_Flag==0)
//////////		memcpy(FX_Plc_Set_CutOpt_Data_Label.Text,"Close",6);
//////////	else
//////////		memcpy(FX_Plc_Set_CutOpt_Data_Label.Text,"Open ",6);	
//////////		
//////////	}


//////////cpGui_CreateLabel(FX_Plc_Set_CutOpt_Data_Label);//裁切优化 《开关》

//////////sprintf(FX_Plc_Set_CutTime_Data_Label.Text,"%d",CutTime);  //优化时间  
//////////cpGui_CreateLabel(FX_Plc_Set_CutTime_Data_Label);

//////////if(Language==CHN_HAN)
//////////	{
//////////	if(FastCut_Flag==0)
//////////		memcpy(FX_Plc_Set_FastCut_Enb_Data_Label.Text,"关闭",5);
//////////	else
//////////		memcpy(FX_Plc_Set_FastCut_Enb_Data_Label.Text,"打开",5);
//////////	}
//////////else
//////////	{
//////////	if(FastCut_Flag==0)
//////////		memcpy(FX_Plc_Set_FastCut_Enb_Data_Label.Text,"Close",6);
//////////	else
//////////		memcpy(FX_Plc_Set_FastCut_Enb_Data_Label.Text,"Open ",6);
//////////	}

//////////cpGui_CreateLabel(FX_Plc_Set_FastCut_Enb_Data_Label);//快速裁切 《开关》
FX_PLC_Setup_Para_Refish(Para_sel);
}


void FX_PLC_Setup_Para_Refish(unsigned char index)
{
////////FX_Plc_Set_MotorStartUpTime_Data_Label.textColor=0;
FX_Plc_Set_MotorStopTime_Data_Label.textColor=0;
////////FX_Plc_Set_KnifeDownTime_Data_Label.textColor=0;
////////FX_Plc_Set_CutOpt_Data_Label.textColor=0;
////////FX_Plc_Set_CutTime_Data_Label.textColor=0;
////////FX_Plc_Set_FastCut_Enb_Data_Label.textColor=0;
	
////////FX_Plc_Set_MotorStartUpTime_Data_Label.bkColor=0xe8ece8;
FX_Plc_Set_MotorStopTime_Data_Label.bkColor=0xe8ece8;
////////FX_Plc_Set_KnifeDownTime_Data_Label.bkColor=0xe8ece8;
////////FX_Plc_Set_CutOpt_Data_Label.bkColor=0xe8ece8;
////////FX_Plc_Set_CutTime_Data_Label.bkColor=0xe8ece8;
////////FX_Plc_Set_FastCut_Enb_Data_Label.bkColor=0xe8ece8;
	
	
switch(index)
	{
		case 18:
			FX_Plc_Set_MotorStartUpTime_Data_Label.bkColor=0x0000ff;
					FX_Plc_Set_MotorStartUpTime_Data_Label.textColor=0xffffff;
		GLCD_SetWindow_Fill( REMIND_WINDOW_X, REMIND_WINDOW_Y, REMIND_WINDOW_X+REMIND_LENGTH, REMIND_WINDOW_Y+30, 0xffff, 0xffff);//提示框
		if(Language==CHN_HAN)
		  Printf24("设置 电机启动时间               ",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,BLACK_COLOR,0,0xffff);		
		else
			Printf24("Set  Motor Start Time           ",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,BLACK_COLOR,0,0xffff);		
		//Printf24("按插入键,切换光电有效电平!     ",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,BLACK_COLOR,0,0xffff);
			break;
		case 11:
			FX_Plc_Set_MotorStopTime_Data_Label.bkColor=0x0000ff;
					FX_Plc_Set_MotorStopTime_Data_Label.textColor=0xffffff;
		GLCD_SetWindow_Fill( REMIND_WINDOW_X, REMIND_WINDOW_Y, REMIND_WINDOW_X+REMIND_LENGTH, REMIND_WINDOW_Y+30, 0xffff, 0xffff);//提示框
		
		if(Language==CHN_HAN)					
			Printf24("设置 电机停止时间   1 TO 180  ",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,BLACK_COLOR,0,0xffff);		
		else
			Printf24("Set Motor Stop Time 1 TO 180  ",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,BLACK_COLOR,0,0xffff);	
		//Printf24("按插入键,切换光电有效电平!     ",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,BLACK_COLOR,0,0xffff);
			break;
		case 10:
////////			FX_Plc_Set_KnifeDownTime_Data_Label.bkColor=0x0000ff;
////////					FX_Plc_Set_KnifeDownTime_Data_Label.textColor=0xffffff;
////////		GLCD_SetWindow_Fill( REMIND_WINDOW_X, REMIND_WINDOW_Y, REMIND_WINDOW_X+REMIND_LENGTH, REMIND_WINDOW_Y+30, 0xffff, 0xffff);//提示框
////////		
////////				if(Language==CHN_HAN)		
////////				Printf24("设置 下刀时间               ",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,BLACK_COLOR,0,0xffff);		
////////				else
////////				Printf24("Set DownKnife Time         ",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,BLACK_COLOR,0,0xffff);			
////////		//Printf24("按插入键,切换光电有效电平!     ",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,BLACK_COLOR,0,0xffff);
			break;
		case 15:
			FX_Plc_Set_CutOpt_Data_Label.bkColor=0x0000ff;
					FX_Plc_Set_CutOpt_Data_Label.textColor=0xffffff;
		GLCD_SetWindow_Fill( REMIND_WINDOW_X, REMIND_WINDOW_Y, REMIND_WINDOW_X+REMIND_LENGTH, REMIND_WINDOW_Y+30, 0xffff, 0xffff);//提示框
				if(Language==CHN_HAN)	
					Printf24("设置 裁切优化 打开/关闭      ",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,BLACK_COLOR,0,0xffff);		
				else
					Printf24("Set OptimizeCut Opwen/Close     ",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,BLACK_COLOR,0,0xffff);	
		//Printf24("按插入键,切换光电有效电平!     ",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,BLACK_COLOR,0,0xffff);
			break;
		case 16:
//////////			FX_Plc_Set_CutTime_Data_Label.bkColor=0x0000ff;
//////////					FX_Plc_Set_CutTime_Data_Label.textColor=0xffffff;
//////////		GLCD_SetWindow_Fill( REMIND_WINDOW_X, REMIND_WINDOW_Y, REMIND_WINDOW_X+REMIND_LENGTH, REMIND_WINDOW_Y+30, 0xffff, 0xffff);//提示框
//////////		
//////////			if(Language==CHN_HAN)	
//////////				Printf24("设置 下刀时间          ",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,BLACK_COLOR,0,0xffff);		
//////////			else
//////////				Printf24("Set Knife Down Time  ",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,BLACK_COLOR,0,0xffff);		
//////////		//Printf24("按插入键,切换光电有效电平!     ",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,BLACK_COLOR,0,0xffff);
//////////			break;
		case 12:
			FX_Plc_Set_FastCut_Enb_Data_Label.bkColor=0x0000ff;
					FX_Plc_Set_FastCut_Enb_Data_Label.textColor=0xffffff;
		GLCD_SetWindow_Fill( REMIND_WINDOW_X, REMIND_WINDOW_Y, REMIND_WINDOW_X+REMIND_LENGTH, REMIND_WINDOW_Y+30, 0xffff, 0xffff);//提示框
			
			if(Language==CHN_HAN)							
				Printf24("设置 快速裁切 打开/关闭        ",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,BLACK_COLOR,0,0xffff);		
			else
				Printf24("Set FastCut Open/Close        ",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,BLACK_COLOR,0,0xffff);
			//Printf24("按插入键,切换光电有效电平!     ",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,BLACK_COLOR,0,0xffff);
			break;	
	}
	
	
	//数据显示
//////cpGui_CreateLabel(FX_Plc_Set_MotorStartUpTime_Data_Label);
cpGui_CreateLabel(FX_Plc_Set_MotorStopTime_Data_Label);
//////cpGui_CreateLabel(FX_Plc_Set_KnifeDownTime_Data_Label);
//////cpGui_CreateLabel(FX_Plc_Set_CutOpt_Data_Label);
//////cpGui_CreateLabel(FX_Plc_Set_CutTime_Data_Label);
//////cpGui_CreateLabel(FX_Plc_Set_FastCut_Enb_Data_Label);
	
}

void FX_PLC_ChangeMode(unsigned char sindex)
{
switch(sindex)
		{
		case 10:
		if(Language==CHN_HAN)
			{
			if(strcmp(FX_Plc_Set_CutOpt_Data_Label.Text,"关闭")==0)
				{
				memcpy(FX_Plc_Set_CutOpt_Data_Label.Text,"打开",5);
				}
			else
				{
					memcpy(FX_Plc_Set_CutOpt_Data_Label.Text,"关闭",5);				
				}			
			}
		else
			{
			if(strcmp(FX_Plc_Set_CutOpt_Data_Label.Text,"Close")==0)
					{
					memcpy(FX_Plc_Set_CutOpt_Data_Label.Text,"Open ",6);
					}
				else
					{
						memcpy(FX_Plc_Set_CutOpt_Data_Label.Text,"Close",6);				
					}	
			}
	
		FX_PLC_Setup_Para_Refish(sindex);
		break;
	case 12:
		if(Language==CHN_HAN)
		{
		if(strcmp(FX_Plc_Set_FastCut_Enb_Data_Label.Text,"关闭")==0)
			{
			memcpy(FX_Plc_Set_FastCut_Enb_Data_Label.Text,"打开",5);
			}
	  else
			{
				memcpy(FX_Plc_Set_FastCut_Enb_Data_Label.Text,"关闭",5);
				
			}
		}
		else
		{
		if(strcmp(FX_Plc_Set_FastCut_Enb_Data_Label.Text,"Close")==0)
			{
			memcpy(FX_Plc_Set_FastCut_Enb_Data_Label.Text,"Open ",6);
			}
	  else
			{
				memcpy(FX_Plc_Set_FastCut_Enb_Data_Label.Text,"Close",6);				
			}		
		}
		
		FX_PLC_Setup_Para_Refish(sindex);
		break;			
		}	
}






void FX_PLC_Set_Process(unsigned  char sindex,unsigned int dat)
{
switch(sindex)
{
	case 7://主电机启动时间
		if((dat>=8)&&(dat<=30))
		{
		//	Motor_StartUpTime=dat;
		sprintf(FX_Plc_Set_MotorStartUpTime_Data_Label.Text,"%d",dat);
				FX_PLC_Setup_Para_Refish(sindex);
		}
		break;
	case 11://主电机停止时间
		
			if((dat>=1)&&(dat<=180))
		{
		//	Motor_StopTime=dat;
			sprintf(FX_Plc_Set_MotorStopTime_Data_Label.Text,"%d",dat);
				FX_PLC_Setup_Para_Refish(sindex);
			
		}
		break;
	case 9://下刀时间
				if((dat>=1)&&(dat<=30))
		{
		//	KnifeDownTime=dat;
						sprintf(FX_Plc_Set_KnifeDownTime_Data_Label.Text,"%d",dat);
				FX_PLC_Setup_Para_Refish(sindex);
		}
		break;
	case 8://裁切时间
				if((dat>=1)&&(dat<=10))
		{
			
		//	CutTime=dat;					
		sprintf(FX_Plc_Set_CutTime_Data_Label.Text,"%d",dat);	
		FX_PLC_Setup_Para_Refish(sindex);
			
		}
		break;
}
	
	
	
}


unsigned char MainMotor_Run_Flag=0;
unsigned int MainMotor_StopTime=0;


unsigned char Manual_Change_Knife_Steps=0;//手动换刀步骤

unsigned int CheckBaseTime=0;
unsigned int Manual_Change_Knife_InvertTime=0;



//检测主机是否为启动状态
void Check_MainMotor_Run_Status(void)
{
	

	
	if(PLC_PowerOn_Init_Flag==1)
	{
		
		MainMotor_StopTime=0;
		return;
	}
	
	
	//Y20,对应的基址  Y[0][0]
	
if(PLC_Y_Status[0][0]==PLC_CONTACT_OFF)
		{//停止状态			
		if(MainMotor_StopTime<180*1000)//最大180秒
			{
			
				MainMotor_StopTime++;
			}
			
		}
else
		{
		MainMotor_StopTime=0;//启动状态			
		Manual_Change_Knife_Steps=0;//电机启动后的换刀步骤
		}
		
		
if(Manual_Knife_Status==1)
	{//手动换刀处理		
	CheckBaseTime++;
	if(CheckBaseTime>=1000)//500)
		{
			CheckBaseTime=0;
			
			if(Manual_Change_Knife_InvertTime>0)
				{
				Manual_Change_Knife_InvertTime--;
					

					
					if(Manual_Change_Knife_InvertTime==0)
					{
						App_Modbus_Plc_Write_M_Status(175,M_ON);	
						memset(FX_Plc_ChangeKnife_Hint_Label.Text,0,32);
						if(Language==CHN_HAN)
						{
						memcpy(FX_Plc_ChangeKnife_Hint_Label.Text,"吸盘吸合",strlen("吸盘吸合"));//
						}
						else
						{
						memcpy(FX_Plc_ChangeKnife_Hint_Label.Text,"Suction cup suction",strlen("Suction cup suction"));//
						}
						cpGui_CreateLabel(FX_Plc_ChangeKnife_Hint_Label);//选择换刀	
					}
					
				else
				{
					
				sprintf(FX_Plc_ChangeKnife_Hint_Label.Text,"%d",Manual_Change_Knife_InvertTime);
				cpGui_CreateLabel(FX_Plc_ChangeKnife_Hint_Label);//选择换刀		
				}
					
				}		
      else
			{
				if(Manual_Change_Knife_Steps==0)
				 {
					Manual_Change_Knife_Steps++;
				 }
			}				
		}
	}
else
	CheckBaseTime=0;

	
}

