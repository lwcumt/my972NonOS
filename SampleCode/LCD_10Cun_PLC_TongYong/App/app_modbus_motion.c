#include "app_modbus_motion.h"

#include "app_modbus.h"

#include "drv_glcd.h"

#include "file.h"
#include "string.h"
#include "stdlib.h"
#include "stdio.h"

#include "modbus_972.h"

#include "timer.h"

#include "app_fx_plc.h"
#include "io.h"

#include "app_modbus_fxplc.h"
#include "comm_fx_plc.h"


#include "word_lib.h"

int Circle_Data=0;
int CurPosition=0;

int RunPosition_Pulse_Cnt=0;

Int32U App_ModBus_DecTime=0;


unsigned char APP_MODBUS_MOTIRON_DIR=1;   //0： 正转   1：反转


int Cur_Circle_Data=0;//当前的多圈数据


int Machine_Load_Postion_Pulse=0;
unsigned char Machine_Position_Pulse_LoadOK_Flag=0;

unsigned char Machine_LuoJu_Data=0;//螺距

int const Motion_Speed[10]={1200,1400,1600,1800,2000,2200,2400,2600,2800,3000};


//机器校基准参数
MODBUS_MOTION_PARAMETER Modbus_Motion_Parameter;

int Machine_Cur_Dimension;	//机器当前实际尺寸

unsigned char Machine_Cur_Dimension_LoadOK_Flag=0;

int Machine_Target_Dimension;	//机器目标尺寸


unsigned char Modbus_Servo_Link_Flag=0;// MODBUS 伺服连接标志位
unsigned char Modbus_Servo_Err_Flag=0; // MODBUS 伺服错误标志位

#include "pic_exec.h"

//初始化
void App_Modbus_Motion_Init(void)
{

//char stemp[16];
		
App_Modbus_Load_LuoJu_DaoCheng();//调入螺距导程	
	
FileRead("ModBus_Servo_Config.cfg",(unsigned char *)&Modbus_Motion_Parameter);
	
	
if(Modbus_Motion_Parameter.Calibration_Flag!=0xAA)
	{
		Modbus_Motion_Parameter.Calibration_Circle_Data=Circle_Data;
		Modbus_Motion_Parameter.Calibration_Dimension_Data=12345;
	}
	
//////if(Modbus_Motion_Parameter.Calibration_Flag!=0xAA)
//////		return;
//////if(Circle_UpData_Flag==0)
//////	return;
	
	App_Modbus_Motion_Reload_Dimension();
	
	App_Modbus_Motion_Cal_CurDimension();//计算当前值
	
	if(APP_MODBUS_PLC==1)// APP_MODUBS_PLC 为0 时，使用板载IO
	{
								//允许裁切  放在马达运行前
		if(FX_Plc_EnbCut_Flag==0)
				{
				App_Modbus_FXPlc_M_CTRL("ON",300);

				}
			else
				{
					App_Modbus_FXPlc_M_CTRL("OFF",300);
				
				}

			}
}



float App_LuoJu=1000.0;
float App_ChiLunBi=0.0;
float App_LuoJu_ChiLunBi_XS=0.0;

#include "plc_ext_form.h"

//保存螺距导程
void App_Modbus_Save_LuoJu_DaoCheng(void)
{
	unsigned char *pdtr;
	pdtr=(unsigned char *)DOWNFILE_SDRAM_ADD;
	
	iFiles.FileLength=2;
*pdtr++=Modbus_Motion_Set_LuoJu;
*pdtr++=Modbus_Motion_Set_ChiLunBi;
//memcpy((unsigned char *)DOWNFILE_SDRAM_ADD,&Modbus_Motion_Parameter,iFiles.FileLength);

ChangeFileName((unsigned char*)"LuoJu_ChiLunBi.cfg");	//NandEccWrite_Flag=0;
File_Create((char*)iFiles.FileName);//建立文件
	
	
}

//调入螺距导程
void App_Modbus_Load_LuoJu_DaoCheng(void)
{	
	
unsigned char *pdtr;
	pdtr=(unsigned char *)DOWNFILE_SDRAM_ADD;
	
FileRead("LuoJu_ChiLunBi.cfg",(unsigned char *)DOWNFILE_SDRAM_ADD);
	
Modbus_Motion_Set_LuoJu=*pdtr++;	
Modbus_Motion_Set_ChiLunBi=*pdtr++;
	
App_Modbus_Cal_Dimension_Of_LuoJu_DaoCheng();//计算系数	
	
	
}



void App_Modbus_Cal_Dimension_Of_LuoJu_DaoCheng(void)
{
switch(Modbus_Motion_Set_LuoJu)
{
	case 1:
		App_LuoJu=1000.0;
		break;
	case 2:
		App_LuoJu=1200.0;		
		break;
	case 3:
		App_LuoJu=2000.0;		
		break;
	default:
		App_LuoJu=1000.0;//默认
		break;
}

switch(Modbus_Motion_Set_ChiLunBi)
{//
	case 1://齿轮比 1:2 
		App_ChiLunBi=1.0/2.0;
		break;
	case 2:////齿轮比 1:2.5 
		App_ChiLunBi=1.0/2.5;		
		break;
	case 3:	////齿轮比 12:32
		App_ChiLunBi=12.0/32.0;		
		break;
	case 4:	////齿轮比 1:3	
		App_ChiLunBi=1.0/3.0;			
		break;
	default:	
			App_ChiLunBi=1.0/2.0;	//默认
	break;		
}


App_LuoJu_ChiLunBi_XS=App_LuoJu*App_ChiLunBi;

////////						sprintf(strtemp,"%0.1f",App_LuoJu_ChiLunBi_XS);
////////			Printf24(strtemp,150,40,RED_COLOR,1,BLACK_COLOR);


////////						sprintf(strtemp,"%0.1f",App_LuoJu);
////////			Printf24(strtemp,220,40,RED_COLOR,1,BLACK_COLOR);

////////						sprintf(strtemp,"%0.1f",App_ChiLunBi);
////////			Printf24(strtemp,290,40,RED_COLOR,1,BLACK_COLOR);


//////			//10mm螺距
//////		
//////					Modbus_Motion_Set_LuoJu=1;
//////				//12mm螺距
//////					Modbus_Motion_Set_LuoJu=2;
//////						//20mm螺距a
//////					Modbus_Motion_Set_LuoJu=3;
//////		
//////		//齿轮比 1:2  
//////		Modbus_Motion_Set_ChiLunBi=1;
//////		////齿轮比 1:2.5 
//////		Modbus_Motion_Set_ChiLunBi=2;
//////				////齿轮比 12:32
//////					Modbus_Motion_Set_ChiLunBi=3;
//////						////齿轮比 1:3		
//////			Modbus_Motion_Set_ChiLunBi=4;
	
	
}


void App_Modbus_Motion_Reload_Dimension(void)
{
	
int temp_circle_data=0;	

float dismension_t=0.0;
	

	
Machine_Cur_Dimension_LoadOK_Flag=0;//重新装载最新的位置信息
Machine_Position_Pulse_LoadOK_Flag=0;//重新装载最新的位置信息
	
Circle_UpData_Flag=0;
	

		if((Modbus_Servo_Link_Flag==1)&&(Machine_Cur_Dimension_LoadOK_Flag==0))
			{//上电读取当前位置	
				
				Machine_Cur_Dimension_LoadOK_Flag=1;
				
				Cur_Circle_Data=Circle_Data;	
				
////////								sprintf(strtemp,"%d",Modbus_Motion_Parameter.Calibration_Circle_Data);
////////			Printf24(strtemp,10,10,RED_COLOR,1,BLACK_COLOR);
////////			
////////						sprintf(strtemp,"%d",Cur_Circle_Data);
////////			Printf24(strtemp,10,40,RED_COLOR,1,BLACK_COLOR);
				
////////				if(APP_MODBUS_MOTIRON_DIR==0)
////////						{
				
							if(Cur_Circle_Data>Modbus_Motion_Parameter.Calibration_Circle_Data)
								{//正数
									if(APP_MODBUS_MOTIRON_DIR==0)
									{
								temp_circle_data=Cur_Circle_Data-Modbus_Motion_Parameter.Calibration_Circle_Data;
								dismension_t=(float)temp_circle_data*((float)(App_LuoJu_ChiLunBi_XS)/(float)65536);//(float)temp_circle_data*((float)(600)/(float)65536);
									
								Machine_Cur_Dimension=Modbus_Motion_Parameter.Calibration_Dimension_Data+(int)(dismension_t);
									}
									else
									{
										temp_circle_data=0-(Cur_Circle_Data-Modbus_Motion_Parameter.Calibration_Circle_Data);		
										dismension_t=(float)temp_circle_data*((float)(App_LuoJu_ChiLunBi_XS)/(float)65536);
											
										Machine_Cur_Dimension=Modbus_Motion_Parameter.Calibration_Dimension_Data+(int)(dismension_t);
									}									
								}
							else
								{
								if(Cur_Circle_Data<Modbus_Motion_Parameter.Calibration_Circle_Data)
										{//负数
												if(APP_MODBUS_MOTIRON_DIR==0)
									{
										temp_circle_data=0-(Cur_Circle_Data-Modbus_Motion_Parameter.Calibration_Circle_Data);		
										dismension_t=(float)temp_circle_data*((float)(App_LuoJu_ChiLunBi_XS)/(float)65536);
											
										Machine_Cur_Dimension=Modbus_Motion_Parameter.Calibration_Dimension_Data-(int)(dismension_t);
									}
									else
									{
									temp_circle_data=Cur_Circle_Data-Modbus_Motion_Parameter.Calibration_Circle_Data;
								dismension_t=(float)temp_circle_data*((float)(App_LuoJu_ChiLunBi_XS)/(float)65536);
									
								Machine_Cur_Dimension=Modbus_Motion_Parameter.Calibration_Dimension_Data-(int)(dismension_t);
									}
											
										}
								else
										{//相等 当前尺寸= 校准尺寸
											
//////////																			sprintf(strtemp,"%d",Modbus_Motion_Parameter.Calibration_Circle_Data);
//////////			Printf24(strtemp,10,80,RED_COLOR,1,BLACK_COLOR);
//////////			
//////////						sprintf(strtemp,"%d",Cur_Circle_Data);
//////////			Printf24(strtemp,10,120,RED_COLOR,1,BLACK_COLOR);
											
											Machine_Cur_Dimension = Modbus_Motion_Parameter.Calibration_Dimension_Data;	
										}
								}
								
								
////////																											sprintf(strtemp,"%d",Machine_Cur_Dimension);
////////			Printf24(strtemp,10,80,RED_COLOR,1,BLACK_COLOR);
								
						//		sprintf(stemp,"%d",Machine_Cur_Dimension);		
						//Printf24(stemp,REMIND_WINDOW_X+700,REMIND_WINDOW_Y-30,RED_COLOR,1,0xffff);
//////////						}	
//////////			else
//////////					{
//////////							if(Cur_Circle_Data<Modbus_Motion_Parameter.Circle_Data)
//////////								{//正数
//////////								temp_circle_data=Cur_Circle_Data-Modbus_Motion_Parameter.Circle_Data;
//////////								dismension_t=(float)temp_circle_data*((float)(500)/(float)65536);
//////////									
//////////								Machine_Cur_Dimension=Modbus_Motion_Parameter.Calibration_Dimension_Data+(int)(dismension_t);
//////////									
//////////								}
//////////							else
//////////								{
//////////								if(Cur_Circle_Data>Modbus_Motion_Parameter.Circle_Data)
//////////										{//负数
//////////										temp_circle_data=0-(Cur_Circle_Data-Modbus_Motion_Parameter.Circle_Data);		
//////////										dismension_t=(float)temp_circle_data*((float)(500)/(float)65536);
//////////											
//////////										Machine_Cur_Dimension=Modbus_Motion_Parameter.Calibration_Dimension_Data-(int)(dismension_t);
//////////											
//////////										}
//////////								else
//////////										{//相等 当前尺寸= 校准尺寸
//////////											Machine_Cur_Dimension = Modbus_Motion_Parameter.Calibration_Dimension_Data;	
//////////										}
//////////								}
//////////														
//////////					}
			
		}

	
}





//根据反馈的脉冲计算实际位置
void App_Modbus_Motion_Cal_CurDimension(void)
{
//	char stemp[16];
int temppositionpulse=0;
	

////////////////////	
////////////////////if(CurPosition>Machine_Load_Postion_Pulse)
////////////////////		{		
////////////////////		if(APP_MODBUS_MOTIRON_DIR==0)
////////////////////		{
////////////////////		temppositionpulse=CurPosition-Machine_Load_Postion_Pulse;
////////////////////		Machine_Target_Dimension=Machine_Cur_Dimension+temppositionpulse;				
////////////////////		}
////////////////////		else
////////////////////		{
////////////////////						temppositionpulse=0-(CurPosition-Machine_Load_Postion_Pulse);
////////////////////			Machine_Target_Dimension=Machine_Cur_Dimension-temppositionpulse;
////////////////////		}
////////////////////		}
////////////////////else
////////////////////		{
////////////////////			if(CurPosition<Machine_Load_Postion_Pulse)
////////////////////			{
////////////////////			if(APP_MODBUS_MOTIRON_DIR==0)
////////////////////			{
////////////////////			temppositionpulse=0-(CurPosition-Machine_Load_Postion_Pulse);
////////////////////			Machine_Target_Dimension=Machine_Cur_Dimension-temppositionpulse;
////////////////////			}
////////////////////			else
////////////////////			{
////////////////////						temppositionpulse=CurPosition-Machine_Load_Postion_Pulse;
////////////////////		Machine_Target_Dimension=Machine_Cur_Dimension+temppositionpulse;		
////////////////////			}
////////////////////			}
////////////////////		else
////////////////////				{
////////////////////				Machine_Target_Dimension=Machine_Cur_Dimension;
////////////////////				}		
////////////////////		}
////////////////////		
////////////////////CurrentSize=Machine_Target_Dimension;
////////sprintf(stemp,"%d",CurPosition);		
////////Printf24("                ",REMIND_WINDOW_X+300,REMIND_WINDOW_Y,RED_COLOR,1,0xffff);
////////Printf24(stemp,REMIND_WINDOW_X+300,REMIND_WINDOW_Y,RED_COLOR,1,0xffff);
//CurrentSize_temp=Machine_Cur_Dimension;
//CurrentSize_dis(CurrentSize_temp); //当前尺寸 更新显示
	
}

#include "key.h"

#include "App_Modbus_Motion_972.h"


//检测目标值
void App_Modbus_Motion_CheckTarget(void)
{
if(Run_flag==1)
		{
			Machine_Target_Dimension=CurrentSize;
						
		  //if(Back_Run_Dimension!=-1)
			if(Back_Run_Dimension>0)//!=-1)
					{
					if((Machine_Target_Dimension>=Back_Run_Dimension+600-2)&&(Machine_Target_Dimension<=Back_Run_Dimension+600+2))
								{				
									Modbus_Motion_AutoStop_Flag=1;
									
									ACServoStop();									
									RunStop_flag=1;									
								//	PromptNum_dis();//显示一下输入范围									
										{									
									//	TargetBell_flag=1;  //蜂鸣器 启动
									//	TargetBell_mode=0;
										}										
								App_Modbus_Motion_Run_Next_972(Back_Run_Dimension);			
								TargetSize=Back_Run_Dimension;
								Back_Run_Dimension=-1;//转到正常停止										
								}			
					 }
			 else
					{
					if(App_Manual_JogRun_Status==0)//非JOG下判断
						{
						if((Machine_Target_Dimension>=TargetSize-2)&&(Machine_Target_Dimension<=TargetSize+2))
									{				
									Modbus_Motion_AutoStop_Flag=1;
									
									ACServoStop();		
									RunStop_flag=1;		

									if(StepRun_Flag!=0)
												{
												StepRun_Flag=0;	
												}				
												
									PromptNum_dis();//显示一下输入范围
									
											{						
											TargetBell_flag=1;  //蜂鸣器 启动
											TargetBell_mode=0;
											}
									}			
							}					
					}
					
			
//////////			{
//////////			//if(Machine_Target_Dimension==TargetSize)
//////////				
//////////			if(App_Manual_JogRun_Status==0)//非JOG下判断
//////////				{
//////////					if((Machine_Target_Dimension>=TargetSize-2)&&			(Machine_Target_Dimension<=TargetSize+2))
//////////							{				
//////////							Modbus_Motion_AutoStop_Flag=1;
//////////							
//////////							ACServoStop();		
//////////							RunStop_flag=1;		

//////////							if(StepRun_Flag!=0)
//////////							{
//////////							//sysprintf("SetpRun\r\n");
//////////							StepRun_Flag=0;	
//////////							}					
//////////								
//////////							PromptNum_dis();//显示一下输入范围
//////////							
//////////									{						
//////////									TargetBell_flag=1;  //蜂鸣器 启动
//////////									TargetBell_mode=0;
//////////									}
//////////							}			
//////////						}
//////////					}
//////////						
		}	
}

//原目标检测
////////////////////void App_Modbus_Motion_CheckTarget(void)
////////////////////{
////////////////////if(Run_flag==1)
////////////////////		{
////////////////////			Machine_Target_Dimension=CurrentSize;
////////////////////						
////////////////////		  if(Back_Run_Dimension!=-1)
////////////////////					{
////////////////////						
////////////////////						
////////////////////						
////////////////////					}
////////////////////			
//////////////////////////////			if(Back_Run_Dimension!=-1)
//////////////////////////////			{//往后再回
////////////////////////////////	if(Machine_Target_Dimension==TargetSize)
//////////////////////////////			if((Machine_Target_Dimension>=Back_Run_Dimension+600-1)&&(Machine_Target_Dimension<=Back_Run_Dimension+600+1))
//////////////////////////////						{				
//////////////////////////////							Modbus_Motion_AutoStop_Flag=1;
//////////////////////////////							
//////////////////////////////							ACServoStop();
//////////////////////////////							
//////////////////////////////							
//////////////////////////////							RunStop_flag=1;
//////////////////////////////							
//////////////////////////////							PromptNum_dis();//显示一下输入范围
//////////////////////////////							
//////////////////////////////			////////////////				if(Electric_Wheel_Run_Flag==1)
//////////////////////////////			////////////////				{
//////////////////////////////			////////////////					
//////////////////////////////			////////////////					Electric_Wheel_Run_Flag=0;
//////////////////////////////			////////////////					
//////////////////////////////			////////////////				}
//////////////////////////////			////////////////				else
//////////////////////////////								{
//////////////////////////////							
//////////////////////////////							TargetBell_flag=1;  //蜂鸣器 启动
//////////////////////////////							TargetBell_mode=0;
//////////////////////////////							}
//////////////////////////////						}
//////////////////////////////			}
//////////////////////////////			else
////////////////////			{
//////////////////////	if(Machine_Target_Dimension==TargetSize)
////////////////////				
////////////////////				if(App_Manual_JogRun_Status==0)//非JOG下判断
////////////////////				{
////////////////////					if((Machine_Target_Dimension>=TargetSize-2)&&			(Machine_Target_Dimension<=TargetSize+2))
////////////////////							{				
////////////////////							Modbus_Motion_AutoStop_Flag=1;
////////////////////							
////////////////////							ACServoStop();		
////////////////////							RunStop_flag=1;		

////////////////////							if(StepRun_Flag!=0)
////////////////////							{
////////////////////							//sysprintf("SetpRun\r\n");
////////////////////							StepRun_Flag=0;	
////////////////////							}					
////////////////////								
////////////////////							PromptNum_dis();//显示一下输入范围
////////////////////							
////////////////////			//////////////				if(Electric_Wheel_Run_Flag==1)
////////////////////			//////////////				{
////////////////////			//////////////					
////////////////////			//////////////					Electric_Wheel_Run_Flag=0;
////////////////////			//////////////					
////////////////////			//////////////				}
////////////////////			//////////////				else
////////////////////										{						
////////////////////									TargetBell_flag=1;  //蜂鸣器 启动
////////////////////									TargetBell_mode=0;
////////////////////									}
////////////////////							}			
////////////////////						}
////////////////////					}
////////////////////						
////////////////////		}	
////////////////////}



unsigned char Modbus_Motion_AutoStop_Flag=0;

unsigned char Modbus_Motion_WaitStop_Flag=0;

unsigned int WatiDelayTime=0;

void App_Modbus_Motion_AutoStop(void)
{
	//return;
	
	
	return;

				
				
	while(App_Modbus_Task_Ready_Flag==0){};//如果是MODBUS发送状态，则等待
		
						ModBus_SendFrame(0x01,0x06,0x5f6,10000);//读取4个字的数据
		ModBus_Queue_LoadBuf(Modbus_Sendbuf,'S',8);
		
		
				ModBus_SendFrame(0x01,0x06,0x0602,0);//读取4个字的数据
		ModBus_Queue_LoadBuf(Modbus_Sendbuf,'S',8);
		
		
		ModBus_SendFrame(0x01,0x06,0x0600,0);//写低16位			
		ModBus_Queue_LoadBuf(Modbus_Sendbuf,'S',8);
			
		ModBus_SendFrame(0x01,0x06,0x0601,0);//写高16位
		ModBus_Queue_LoadBuf(Modbus_Sendbuf,'S',8);
			
			

		
		
		WatiDelayTime=0;
		while(1)
		{
			if(Ms_Flag==1)
			{
				Ms_Flag=0;
				WatiDelayTime++;
				if(WatiDelayTime>=300)
				{
					
				WatiDelayTime=0;
					break;
				}
			}			
			
		}
		
			while(App_Modbus_Task_Ready_Flag==0){};//如果是MODBUS发送状态，则等待
				
		ModBus_SendFrame(0x01,MODBUS_READ_CMD,0x800C,0x02);//读取4个字的数据
		ModBus_Queue_LoadBuf(Modbus_Sendbuf,'K',8);	
		
		Modbus_Motion_WaitStop_Flag=1;
		while(Modbus_Motion_WaitStop_Flag==1){};
			
			
		while(App_Modbus_Task_Ready_Flag==0){};//如果是MODBUS发送状态，则等待
		
		ModBus_SendFrame(0x01,0x06,0x0600,Stop_0x800C_Data);//写低16位			
		ModBus_Queue_LoadBuf(Modbus_Sendbuf,'S',8);
			
		ModBus_SendFrame(0x01,0x06,0x0601,Stop_0x800D_Data);//写高16位
		ModBus_Queue_LoadBuf(Modbus_Sendbuf,'S',8);
			
			
		ModBus_SendFrame(0x01,0x06,0x0602,50);//读取4个字的数据
		ModBus_Queue_LoadBuf(Modbus_Sendbuf,'S',8);
		
				ModBus_SendFrame(0x01,0x06,0x0451,1);//读取4个字的数据
		ModBus_Queue_LoadBuf(Modbus_Sendbuf,'S',8);
		
			ModBus_SendFrame(0x01,0x06,0x0451,0x8001);//读取4个字的数据
		ModBus_Queue_LoadBuf(Modbus_Sendbuf,'S',8);
			
			
//			ElectricWheelOn_flag=1;//强制手轮
			
		if(ElectricWheelOn_flag!=0)//继续允许手轮
								{
							WatiDelayTime=0;
							while(1)
							{
								if(Ms_Flag==1)
								{
									Ms_Flag=0;
									WatiDelayTime++;
									if(WatiDelayTime>=300)
									{
										
									WatiDelayTime=0;
										break;
									}
								}			
								
							}
			
							if(Back_Run_Dimension==-1)
							{

											while(App_Modbus_Task_Ready_Flag==0);//如果是MODBUS发送状态，则等待
									
									//、、1：位置手轮模式：先设置地址0x1095=0x80，再设置0x1000=0x10，手轮有效，内部位置无效。
					
									ModBus_SendFrame(0x01,0x06,0x1095,0x80);//位置手轮模式：先设置地址0x1095=0x80，
									ModBus_Queue_LoadBuf(Modbus_Sendbuf,'r',8);
										
																				if(APP_MODBUS_MOTIRON_DIR==0)						
												{
												
											ModBus_SendFrame(0x01,0x06,0x1000,0x10);//再设置0x1000=0x10，手轮有效，内部位置无效。
											ModBus_Queue_LoadBuf(Modbus_Sendbuf,'r',8);
											}
											else
											{
											ModBus_SendFrame(0x01,0x06,0x1000,0x11);//再设置0x1000=0x10，手轮有效，内部位置无效。
											ModBus_Queue_LoadBuf(Modbus_Sendbuf,'r',8);
												
											}
									}
								}
								
		FX_Plc_EnbCut_Flag=0;
		
			if(APP_MODBUS_PLC==1)// APP_MODUBS_PLC 为0 时，使用板载IO
			{
							//允许裁切  放在马达运行前
		if(FX_Plc_EnbCut_Flag==0)
				{
				App_Modbus_FXPlc_M_CTRL("ON",300);
				//	App_FX_Plc_Force_Process("ON",M300);
				}
			else
				{
					App_Modbus_FXPlc_M_CTRL("OFF",300);
					//App_FX_Plc_Force_Process("OFF",M300);					
				}
			}
}




#include "app_modbus_servo.h"


void App_Modbus_Motion_Stop(void)
{
	//return;
	
	App_Modbus_Servo_Stop(1);
	return;
	
//if(Modbus_Motion_AutoStop_Flag==1)
{
	
Modbus_Motion_AutoStop_Flag=0;
App_Modbus_Motion_AutoStop();

return;	
}

				
				
	while(App_Modbus_Task_Ready_Flag==0){};//如果是MODBUS发送状态，则等待

		
		ModBus_SendFrame(0x01,0x06,0x0600,0);//写低16位			
		ModBus_Queue_LoadBuf(Modbus_Sendbuf,'S',8);
			
		ModBus_SendFrame(0x01,0x06,0x0601,0);//写高16位
		ModBus_Queue_LoadBuf(Modbus_Sendbuf,'S',8);
			
			
		ModBus_SendFrame(0x01,0x06,0x0602,0);//读取4个字的数据
		ModBus_Queue_LoadBuf(Modbus_Sendbuf,'S',8);
		
		ModBus_SendFrame(0x01,0x06,0x0451,1);//读取4个字的数据
		ModBus_Queue_LoadBuf(Modbus_Sendbuf,'S',8);
		
			ModBus_SendFrame(0x01,0x06,0x0451,0x8001);//读取4个字的数据
		ModBus_Queue_LoadBuf(Modbus_Sendbuf,'S',8);
		
		FX_Plc_EnbCut_Flag=0;
		
			if(APP_MODBUS_PLC==1)// APP_MODUBS_PLC 为0 时，使用板载IO
			{
							//允许裁切  放在马达运行前
		if(FX_Plc_EnbCut_Flag==0)
				{
				App_Modbus_FXPlc_M_CTRL("ON",300);
				//	App_FX_Plc_Force_Process("ON",M300);
				}
			else
				{
					App_Modbus_FXPlc_M_CTRL("OFF",300);
					//App_FX_Plc_Force_Process("OFF",M300);					
				}
				
			}	
}


void App_Modbus_motion_Disp(void)
{
		char stemp[16];
	int targe_size_data;	
		targe_size_data=CurPosition;
sprintf(stemp,"%d",targe_size_data);		
Printf24("           ",REMIND_WINDOW_X+300,REMIND_WINDOW_Y-30,RED_COLOR,1,0xffff);
Printf24(stemp,REMIND_WINDOW_X+300,REMIND_WINDOW_Y-30,RED_COLOR,1,0xffff);
	
	
}


int Electric_WheelPulse_Cnt=0;


unsigned int Electric_Whell_RunTime=0;

unsigned char Electric_Wheel_Run_Step=0;
unsigned char Electric_Whell_Dir=0;
unsigned char Electric_Wheel_Run_Flag=0;

//电子手轮检测
void App_Modbus_Motion_Whell_Check(void)
{
//	int i;
//	char stemp[16];
	return;
	
	if(WorkStart_flag==0)
		return;
	
	if((ElectricWheelOn_flag==1)&&(Run_flag==0)&&(Electric_Wheel_Run_Flag==0))
			{
			// if((AllPressUp_flag==1)&&(AllKnifeUp_flag==1))
			if(1)		//20191115
				{
					
				switch(Electric_Wheel_Run_Step)
				{
					case 0:
						if((OIN6_PIN!=0)||(OIN7_PIN!=0))
						{
							Electric_Wheel_Run_Step++;
						}
						break;
					case 1:
						if((OIN6_PIN!=0)&&(OIN7_PIN==0))
							{
							Electric_Whell_Dir=1;//正转
								Electric_Wheel_Run_Step++;
							}	
						else
							{
							if((OIN7_PIN!=0)&&(OIN6_PIN==0))
									{
									Electric_Whell_Dir=0;//正反转
									Electric_Wheel_Run_Step++;
									}
							else
									{										
										Electric_Wheel_Run_Step=0;//干扰。返回第1步
									}
							}
						break;
					case 2:
						if((OIN6_PIN==0)&&(OIN7_PIN==0))
						{	
							Electric_Wheel_Run_Step=0;//干扰。返回第1步
							
						}		

					if((OIN6_PIN!=0)&&(OIN7_PIN!=0))
								{
								Electric_Wheel_Run_Step++;
								}								
								
						break;
								
					case 3:
						if(Electric_Whell_Dir==1)
							{
							if((OIN6_PIN!=0)&&(OIN7_PIN==0))
									{
									Electric_Wheel_Run_Step--;
									}
							else
									{
									if((OIN7_PIN!=0)&&(OIN6_PIN==0))
											{
											Electric_Wheel_Run_Step++;
											}	
									}
							}
							else
							{
							if((OIN7_PIN!=0)&&(OIN6_PIN==0))
									{
									Electric_Wheel_Run_Step--;
										
									}		
							else
									{
									if((OIN6_PIN!=0)&&(OIN7_PIN==0))
											{
											Electric_Wheel_Run_Step++;
											}																				
									}									
							}
					break;
					case 4:
						if((OIN6_PIN==0)&&(OIN7_PIN==0))
						{	
						if(Electric_Whell_Dir==1)
							{
											InTargetPosit_flag=0;
											Electric_WheelPulse_Cnt++;

								Electric_Wheel_Run_Step=0;
							}
							else
							{//反转
									InTargetPosit_flag=0;
									Electric_WheelPulse_Cnt--;
////////										sprintf(stemp,"%d",Electric_WheelPulse_Cnt);		
////////										Printf24("           ",REMIND_WINDOW_X+300,REMIND_WINDOW_Y-30,RED_COLOR,1,0xffff);
////////										Printf24(stemp,REMIND_WINDOW_X+300,REMIND_WINDOW_Y-30,RED_COLOR,1,0xffff);								
								Electric_Wheel_Run_Step=0;
							}
						}	
						else
						{
						if((OIN6_PIN!=0)&&(OIN7_PIN!=0))
								{
										Electric_Wheel_Run_Step--;//回退									
								}
						//	Electric_Wheel_Run_Step--;//回退							
						}

						
						break;
					
					
				}

				}
			}		

}

//手轮运行
void App_ModBus_Motion_ElectricWheel_Run(void)
{
//	char stemp[16];
	
	
	return;
	
if((ElectricWheelOn_flag==1)&&(Run_flag==0)&&(Electric_WheelPulse_Cnt!=0)&&(Electric_Wheel_Run_Step==0)&&(Electric_Wheel_Run_Flag==0))
			{
				
////////																								sprintf(stemp,"%d",Electric_WheelPulse_Cnt);		
////////												Printf24("           ",REMIND_WINDOW_X+300,REMIND_WINDOW_Y-30,RED_COLOR,1,0xffff);
////////												Printf24(stemp,REMIND_WINDOW_X+300,REMIND_WINDOW_Y-30,RED_COLOR,1,0xffff);

				Electric_Whell_RunTime++;
				if(Electric_Whell_RunTime>50)
						{
						Electric_Whell_RunTime=0;
							
							if(Electric_Wheel_Run_Step==0)
							{
							Run_flag=1;
						Electric_Wheel_Run_Flag=1;
							
										TargetSize=Electric_WheelPulse_Cnt+Machine_Target_Dimension;
						App_Modbus_Motion_JogRun(10,TargetSize);								
						Electric_WheelPulse_Cnt=0;
							}
						}					
			}
			else
				Electric_Whell_RunTime=0;			
	
}


void App_Modbus_Motion_JogRun(Int32U spd,Int32U target_size)
{

//Int32U tempqianjin1;    
//Int32U temphoutui1;   
int targe_size_data;	
	
	int motion_runspeed=0;
	
//	char stemp[16];
	
	int speedtemp=AC_MotorSPD-9;

				
if(speedtemp>9)//if(AC_MotorSPD>18)
	{
	motion_runspeed =	Motion_Speed[9];
	}
	else
	{
	motion_runspeed =	Motion_Speed[speedtemp];		
	}

	
	motion_runspeed*=spd;
	motion_runspeed/=100;
	
	RunPosition_Pulse_Cnt=CurPosition;
	
										if(ElectricWheelOn_flag!=0)
								{
								//	ElectricWheelOn_flag=0;//继续允许电子手轮，不清除
									
									if(WorkMode==MANUAL_MODE)
									{
										ElectricalWheel_dis();  //电子手轮  开关状态
									}
									else
									{
										
										if((WorkMode==AUTO_MODE)||(WorkMode==TEACH_MODE))
										{
											ElectricalWheel_dis_OF_AUTO_MODE();//自动模式下的手轮显示
										}
									}
									
									
															
											while(App_Modbus_Task_Ready_Flag==0);//如果是MODBUS发送状态，则等待
																	//	内部位置模式：先设置地址0x1095=0x70，再设置0x1000=0xd0 ，手轮无效，内部位置有效。
								ModBus_SendFrame(0x01,0x06,0x1095,0x70);//写低16位			内部位置模式：先设置地址0x1095=0x70
								ModBus_Queue_LoadBuf(Modbus_Sendbuf,'r',8);
									
								if(APP_MODBUS_MOTIRON_DIR==0)											
										{												
											ModBus_SendFrame(0x01,0x06,0x1000,0xd0);//再设置0x1000=0xd0 ，手轮无效，内部位置有效	
											ModBus_Queue_LoadBuf(Modbus_Sendbuf,'r',8);
											}
											else
											{
												ModBus_SendFrame(0x01,0x06,0x1000,0xd1);//再设置0x1000=0xd0 ，手轮无效，内部位置有效	
												ModBus_Queue_LoadBuf(Modbus_Sendbuf,'r',8);
												
											}		
									}
	
//////////targe_size_data=target_size;
//////////sprintf(stemp,"%d",targe_size_data);		
//////////Printf24("           ",REMIND_WINDOW_X+300,REMIND_WINDOW_Y-30,RED_COLOR,1,0xffff);
//////////Printf24(stemp,REMIND_WINDOW_X+300,REMIND_WINDOW_Y-30,RED_COLOR,1,0xffff);
//////	
	
if(APP_MODBUS_MOTIRON_DIR==0)
			{//正转
				
			//计算目标尺寸	
			if(target_size>Machine_Target_Dimension)
				{
					
					targe_size_data=target_size-Machine_Target_Dimension;
					
					
					targe_size_data+=RunPosition_Pulse_Cnt;

					
						//RLOUT1_ON;//RLOUT1_ON;    // 允许裁切断开
					#ifdef FX_PLC
					if(APP_MODBUS_PLC==1)// APP_MODUBS_PLC 为0 时，使用板载IO
						FX_Plc_EnbCut_Flag=1;
					#endif			
						AutoPress_Stop();	//断 自动压，允许压 20191108
						EnblePress_Stop();		
						AirSwitch_Work();// 气阀闭合
						CutPermit_flag=0; 
					
					if(APP_MODBUS_PLC==1)// APP_MODUBS_PLC 为0 时，使用板载IO
					{
								//允许裁切  放在马达运行前
					if(FX_Plc_EnbCut_Flag==0)
							{
							App_Modbus_FXPlc_M_CTRL("ON",300);
							//	App_FX_Plc_Force_Process("ON",M300);
							}
						else
							{
								App_Modbus_FXPlc_M_CTRL("OFF",300);
								//App_FX_Plc_Force_Process("OFF",M300);					
							}
						}
							
							
					while(App_Modbus_Task_Ready_Flag==0){};//如果是MODBUS发送状态，则等待
					
					ModBus_SendFrame(0x01,0x06,0x0600,(unsigned int)targe_size_data);//写低16位			
					ModBus_Queue_LoadBuf(Modbus_Sendbuf,'B',8);
						
					ModBus_SendFrame(0x01,0x06,0x0601,(unsigned int)targe_size_data>>16);//写高16位
					ModBus_Queue_LoadBuf(Modbus_Sendbuf,'B',8);
						
						
					ModBus_SendFrame(0x01,0x06,0x0602,motion_runspeed);//设置运行速度
					ModBus_Queue_LoadBuf(Modbus_Sendbuf,'P',8);
				}
				else
				{
					if(target_size<Machine_Target_Dimension)
					{
						targe_size_data=0-(Machine_Target_Dimension-target_size);//-Machine_Target_Dimension;//-vbcd;//(int)vbcd-(int);

						
							targe_size_data+=RunPosition_Pulse_Cnt;
						
						
							//RLOUT1_ON; //RLOUT1_ON;   // 允许裁切断开
						#ifdef FX_PLC
						if(APP_MODBUS_PLC==1)// APP_MODUBS_PLC 为0 时，使用板载IO
							FX_Plc_EnbCut_Flag=1;
						#endif		
							AutoPress_Stop();	//断 自动压，允许压 20191108
							EnblePress_Stop();
							AirSwitch_Work();// 气阀闭合
							CutPermit_flag=0;
						
									
						if(APP_MODBUS_PLC==1)// APP_MODUBS_PLC 为0 时，使用板载IO
						{
									//允许裁切  放在马达运行前
					if(FX_Plc_EnbCut_Flag==0)
							{
							App_Modbus_FXPlc_M_CTRL("ON",300);
							//	App_FX_Plc_Force_Process("ON",M300);
							}
						else
							{
								App_Modbus_FXPlc_M_CTRL("OFF",300);
								//App_FX_Plc_Force_Process("OFF",M300);					
							}
						}
							
						while(App_Modbus_Task_Ready_Flag==0){};//如果是MODBUS发送状态，则等待
						ModBus_SendFrame(0x01,0x06,0x0600,(unsigned int)targe_size_data);//写低16位			
						ModBus_Queue_LoadBuf(Modbus_Sendbuf,'B',8);
						
						ModBus_SendFrame(0x01,0x06,0x0601,(unsigned int)targe_size_data>>16);//写高16位
						ModBus_Queue_LoadBuf(Modbus_Sendbuf,'B',8);			
						
						ModBus_SendFrame(0x01,0x06,0x0602,motion_runspeed);//设置运行速度
						ModBus_Queue_LoadBuf(Modbus_Sendbuf,'P',8);
					}
					else
					{//相同位置，不运行
						
						
					}
				}		
			}
else
			{//反转
				
			//计算目标尺寸	
			if(target_size<Machine_Target_Dimension)
				{
					
					targe_size_data=target_size-Machine_Target_Dimension;
					
					
					targe_size_data+=RunPosition_Pulse_Cnt;

					
						//RLOUT1_ON;//RLOUT1_ON;    // 允许裁切断开
					#ifdef FX_PLC
					if(APP_MODBUS_PLC==1)// APP_MODUBS_PLC 为0 时，使用板载IO
						FX_Plc_EnbCut_Flag=1;
					#endif			
						AutoPress_Stop();	//断 自动压，允许压 20191108
						EnblePress_Stop();		
						AirSwitch_Work();// 气阀闭合
						CutPermit_flag=0; 
					
					if(APP_MODBUS_PLC==1)// APP_MODUBS_PLC 为0 时，使用板载IO
					{
								//允许裁切  放在马达运行前
					if(FX_Plc_EnbCut_Flag==0)
							{
							App_Modbus_FXPlc_M_CTRL("ON",300);
							//	App_FX_Plc_Force_Process("ON",M300);
							}
						else
							{
								App_Modbus_FXPlc_M_CTRL("OFF",300);
								//App_FX_Plc_Force_Process("OFF",M300);					
							}
						}
							
					while(App_Modbus_Task_Ready_Flag==0){};//如果是MODBUS发送状态，则等待
					
					ModBus_SendFrame(0x01,0x06,0x0600,(unsigned int)targe_size_data);//写低16位			
					ModBus_Queue_LoadBuf(Modbus_Sendbuf,'B',8);
						
					ModBus_SendFrame(0x01,0x06,0x0601,(unsigned int)targe_size_data>>16);//写高16位
					ModBus_Queue_LoadBuf(Modbus_Sendbuf,'B',8);
						
						
					ModBus_SendFrame(0x01,0x06,0x0602,motion_runspeed);//设置运行速度
					ModBus_Queue_LoadBuf(Modbus_Sendbuf,'P',8);
				}
				else
				{
					if(target_size>Machine_Target_Dimension)
					{
						targe_size_data=0-(Machine_Target_Dimension-target_size);//-Machine_Target_Dimension;//-vbcd;//(int)vbcd-(int);

						
							targe_size_data+=RunPosition_Pulse_Cnt;
						
						
							//RLOUT1_ON; //RLOUT1_ON;   // 允许裁切断开
						#ifdef FX_PLC
						if(APP_MODBUS_PLC==1)// APP_MODUBS_PLC 为0 时，使用板载IO
							FX_Plc_EnbCut_Flag=1;
						#endif		
							AutoPress_Stop();	//断 自动压，允许压 20191108
							EnblePress_Stop();
							AirSwitch_Work();// 气阀闭合
							CutPermit_flag=0;
						
									if(APP_MODBUS_PLC==1)// APP_MODUBS_PLC 为0 时，使用板载IO
									{
									//允许裁切  放在马达运行前
					if(FX_Plc_EnbCut_Flag==0)
							{
							App_Modbus_FXPlc_M_CTRL("ON",300);
							//	App_FX_Plc_Force_Process("ON",M300);
							}
						else
							{
								App_Modbus_FXPlc_M_CTRL("OFF",300);
								//App_FX_Plc_Force_Process("OFF",M300);					
							}
						}
							
							
						while(App_Modbus_Task_Ready_Flag==0){};//如果是MODBUS发送状态，则等待
						ModBus_SendFrame(0x01,0x06,0x0600,(unsigned int)targe_size_data);//写低16位			
						ModBus_Queue_LoadBuf(Modbus_Sendbuf,'B',8);
						
						ModBus_SendFrame(0x01,0x06,0x0601,(unsigned int)targe_size_data>>16);//写高16位
						ModBus_Queue_LoadBuf(Modbus_Sendbuf,'B',8);			
						
						ModBus_SendFrame(0x01,0x06,0x0602,motion_runspeed);//设置运行速度
						ModBus_Queue_LoadBuf(Modbus_Sendbuf,'P',8);
					}
					else
					{//相同位置，不运行
						
						
					}
				}		
			}
}




//运行
void App_Modbus_Motion_Run(Int32U target_size)
{    
//Int32U tempqianjin1;    
//Int32U temphoutui1;   
int targe_size_data;	
	
	int motion_runspeed=0;
	
//	char stemp[16];
	
		int speedtemp=AC_MotorSPD-9;
	
	if(speedtemp>9)
	{
	motion_runspeed =	Motion_Speed[9];
	}
	else
	{
	motion_runspeed =	Motion_Speed[speedtemp];		
	}

	RunPosition_Pulse_Cnt=CurPosition;
	

	
//////targe_size_data=CurPosition;
//////sprintf(stemp,"%d",targe_size_data);		
//////Printf24("           ",REMIND_WINDOW_X+300,REMIND_WINDOW_Y-30,RED_COLOR,1,0xffff);
//////Printf24(stemp,REMIND_WINDOW_X+300,REMIND_WINDOW_Y-30,RED_COLOR,1,0xffff);
//////	
//////	
//////sprintf(stemp,"%d",Machine_Target_Dimension);		
//////Printf24("           ",REMIND_WINDOW_X,REMIND_WINDOW_Y-30,RED_COLOR,1,0xffff);
//////Printf24(stemp,REMIND_WINDOW_X,REMIND_WINDOW_Y-30,RED_COLOR,1,0xffff);
	
	
									if(ElectricWheelOn_flag!=0)
								{
									//	ElectricWheelOn_flag=0;//继续允许电子手轮，不清除
																			if(WorkMode==MANUAL_MODE)
									{
										ElectricalWheel_dis();  //电子手轮  开关状态
									}
									else
									{
										
										if((WorkMode==AUTO_MODE)||(WorkMode==TEACH_MODE))
										{
											ElectricalWheel_dis_OF_AUTO_MODE();//自动模式下的手轮显示
										}
									}
											while(App_Modbus_Task_Ready_Flag==0);//如果是MODBUS发送状态，则等待
																	//	内部位置模式：先设置地址0x1095=0x70，再设置0x1000=0xd0 ，手轮无效，内部位置有效。
								ModBus_SendFrame(0x01,0x06,0x1095,0x70);//写低16位			内部位置模式：先设置地址0x1095=0x70
								ModBus_Queue_LoadBuf(Modbus_Sendbuf,'r',8);
									
								if(APP_MODBUS_MOTIRON_DIR==0)											
										{												
											ModBus_SendFrame(0x01,0x06,0x1000,0xd0);//再设置0x1000=0xd0 ，手轮无效，内部位置有效	
											ModBus_Queue_LoadBuf(Modbus_Sendbuf,'r',8);
											}
											else
											{
												ModBus_SendFrame(0x01,0x06,0x1000,0xd1);//再设置0x1000=0xd0 ，手轮无效，内部位置有效	
												ModBus_Queue_LoadBuf(Modbus_Sendbuf,'r',8);
												
											}		
									}

	
if(APP_MODBUS_MOTIRON_DIR==0)
		{
			
		if(target_size>Machine_Target_Dimension)
			{
				
				targe_size_data=target_size-Machine_Target_Dimension;
				
				
				targe_size_data+=RunPosition_Pulse_Cnt;

		////////		sprintf(stemp,"%d",targe_size_data);		
		////////		Printf24("           ",REMIND_WINDOW_X+150,REMIND_WINDOW_Y-30,RED_COLOR,1,0xffff);
		////////		Printf24(stemp,REMIND_WINDOW_X+150,REMIND_WINDOW_Y-30,RED_COLOR,1,0xffff);
			
				
					//RLOUT1_ON;//RLOUT1_ON;    // 允许裁切断开
				#ifdef FX_PLC
				if(APP_MODBUS_PLC==1)// APP_MODUBS_PLC 为0 时，使用板载IO
					FX_Plc_EnbCut_Flag=1;
				#endif			
					AutoPress_Stop();	//断 自动压，允许压 20191108
					EnblePress_Stop();		
					AirSwitch_Work();// 气阀闭合
					CutPermit_flag=0; 
				
				if(APP_MODBUS_PLC==1)// APP_MODUBS_PLC 为0 时，使用板载IO
				{				
								//允许裁切  放在马达运行前
				if(FX_Plc_EnbCut_Flag==0)
						{
						App_Modbus_FXPlc_M_CTRL("ON",300);
						//	App_FX_Plc_Force_Process("ON",M300);
						}
					else
						{
							App_Modbus_FXPlc_M_CTRL("OFF",300);
							//App_FX_Plc_Force_Process("OFF",M300);					
						}
					}
						
				while(App_Modbus_Task_Ready_Flag==0){};//如果是MODBUS发送状态，则等待
				
				ModBus_SendFrame(0x01,0x06,0x0600,(unsigned int)targe_size_data);//写低16位			
				ModBus_Queue_LoadBuf(Modbus_Sendbuf,'B',8);
					
				ModBus_SendFrame(0x01,0x06,0x0601,(unsigned int)targe_size_data>>16);//写高16位
				ModBus_Queue_LoadBuf(Modbus_Sendbuf,'B',8);
					
					
				ModBus_SendFrame(0x01,0x06,0x0602,motion_runspeed);//设置运行速度
				ModBus_Queue_LoadBuf(Modbus_Sendbuf,'P',8);
			}
			else
			{
				if(target_size<Machine_Target_Dimension)
				{
					targe_size_data=0-(Machine_Target_Dimension-target_size);//-Machine_Target_Dimension;//-vbcd;//(int)vbcd-(int);

					
						targe_size_data+=RunPosition_Pulse_Cnt;
					
					
						//RLOUT1_ON; //RLOUT1_ON;   // 允许裁切断开
					#ifdef FX_PLC
					if(APP_MODBUS_PLC==1)// APP_MODUBS_PLC 为0 时，使用板载IO
						FX_Plc_EnbCut_Flag=1;
					#endif		
						AutoPress_Stop();	//断 自动压，允许压 20191108
						EnblePress_Stop();
						AirSwitch_Work();// 气阀闭合
						CutPermit_flag=0;
					
					if(APP_MODBUS_PLC==1)// APP_MODUBS_PLC 为0 时，使用板载IO
					{
					
									//允许裁切  放在马达运行前
				if(FX_Plc_EnbCut_Flag==0)
						{
						App_Modbus_FXPlc_M_CTRL("ON",300);
						//	App_FX_Plc_Force_Process("ON",M300);
						}
					else
						{
							App_Modbus_FXPlc_M_CTRL("OFF",300);
							//App_FX_Plc_Force_Process("OFF",M300);					
						}
					}
		////////				sprintf(stemp,"%d",targe_size_data);		
		////////				Printf24("           ",REMIND_WINDOW_X+150,REMIND_WINDOW_Y-30,RED_COLOR,1,0xffff);
		////////				Printf24(stemp,REMIND_WINDOW_X+150,REMIND_WINDOW_Y-30,RED_COLOR,1,0xffff);
					
					while(App_Modbus_Task_Ready_Flag==0){};//如果是MODBUS发送状态，则等待
						
						
												ModBus_SendFrame(0x01,0x06,0x5f6,App_ModBus_DecTime);//读取4个字的数据
		ModBus_Queue_LoadBuf(Modbus_Sendbuf,'S',8);
						
						
					ModBus_SendFrame(0x01,0x06,0x0600,(unsigned int)targe_size_data);//写低16位			
					ModBus_Queue_LoadBuf(Modbus_Sendbuf,'B',8);
					
					ModBus_SendFrame(0x01,0x06,0x0601,(unsigned int)targe_size_data>>16);//写高16位
					ModBus_Queue_LoadBuf(Modbus_Sendbuf,'B',8);			
					
					ModBus_SendFrame(0x01,0x06,0x0602,motion_runspeed);//设置运行速度
					ModBus_Queue_LoadBuf(Modbus_Sendbuf,'P',8);
				}
				else
				{//相同位置，不运行
					
					
				}
			}
				
		}
else
		{//反转
			
		if(target_size<Machine_Target_Dimension)
			{
				
				targe_size_data=target_size-Machine_Target_Dimension;
				
				
				targe_size_data+=RunPosition_Pulse_Cnt;

		////////		sprintf(stemp,"%d",targe_size_data);		
		////////		Printf24("           ",REMIND_WINDOW_X+150,REMIND_WINDOW_Y-30,RED_COLOR,1,0xffff);
		////////		Printf24(stemp,REMIND_WINDOW_X+150,REMIND_WINDOW_Y-30,RED_COLOR,1,0xffff);
			
				
					//RLOUT1_ON;//RLOUT1_ON;    // 允许裁切断开
				#ifdef FX_PLC
				if(APP_MODBUS_PLC==1)// APP_MODUBS_PLC 为0 时，使用板载IO
					FX_Plc_EnbCut_Flag=1;
				#endif			
					AutoPress_Stop();	//断 自动压，允许压 20191108
					EnblePress_Stop();		
					AirSwitch_Work();// 气阀闭合
					CutPermit_flag=0; 
				
				if(APP_MODBUS_PLC==1)// APP_MODUBS_PLC 为0 时，使用板载IO
				{
								//允许裁切  放在马达运行前
				if(FX_Plc_EnbCut_Flag==0)
						{
						App_Modbus_FXPlc_M_CTRL("ON",300);
						//	App_FX_Plc_Force_Process("ON",M300);
						}
					else
						{
							App_Modbus_FXPlc_M_CTRL("OFF",300);
							//App_FX_Plc_Force_Process("OFF",M300);					
						}
					}
						
				while(App_Modbus_Task_Ready_Flag==0){};//如果是MODBUS发送状态，则等待
				
					
											ModBus_SendFrame(0x01,0x06,0x5f6,App_ModBus_DecTime);//读取4个字的数据
		ModBus_Queue_LoadBuf(Modbus_Sendbuf,'S',8);
					
				ModBus_SendFrame(0x01,0x06,0x0600,(unsigned int)targe_size_data);//写低16位			
				ModBus_Queue_LoadBuf(Modbus_Sendbuf,'B',8);
					
				ModBus_SendFrame(0x01,0x06,0x0601,(unsigned int)targe_size_data>>16);//写高16位
				ModBus_Queue_LoadBuf(Modbus_Sendbuf,'B',8);
					
					
				ModBus_SendFrame(0x01,0x06,0x0602,motion_runspeed);//设置运行速度
				ModBus_Queue_LoadBuf(Modbus_Sendbuf,'P',8);
			}
			else
			{
				if(target_size>Machine_Target_Dimension)
				{
					targe_size_data=0-(Machine_Target_Dimension-target_size);//-Machine_Target_Dimension;//-vbcd;//(int)vbcd-(int);

					
						targe_size_data+=RunPosition_Pulse_Cnt;
					
					
						//RLOUT1_ON; //RLOUT1_ON;   // 允许裁切断开
					#ifdef FX_PLC
					if(APP_MODBUS_PLC==1)// APP_MODUBS_PLC 为0 时，使用板载IO
						FX_Plc_EnbCut_Flag=1;
					#endif		
						AutoPress_Stop();	//断 自动压，允许压 20191108
						EnblePress_Stop();
						AirSwitch_Work();// 气阀闭合
						CutPermit_flag=0;
					
					if(APP_MODBUS_PLC==1)// APP_MODUBS_PLC 为0 时，使用板载IO
					{
									//允许裁切  放在马达运行前
				if(FX_Plc_EnbCut_Flag==0)
						{
						App_Modbus_FXPlc_M_CTRL("ON",300);
						//	App_FX_Plc_Force_Process("ON",M300);
						}
					else
						{
							App_Modbus_FXPlc_M_CTRL("OFF",300);
							//App_FX_Plc_Force_Process("OFF",M300);					
						}
					}
					
		////////				sprintf(stemp,"%d",targe_size_data);		
		////////				Printf24("           ",REMIND_WINDOW_X+150,REMIND_WINDOW_Y-30,RED_COLOR,1,0xffff);
		////////				Printf24(stemp,REMIND_WINDOW_X+150,REMIND_WINDOW_Y-30,RED_COLOR,1,0xffff);
					
					while(App_Modbus_Task_Ready_Flag==0){};//如果是MODBUS发送状态，则等待
						
												ModBus_SendFrame(0x01,0x06,0x5f6,App_ModBus_DecTime);//读取4个字的数据
		ModBus_Queue_LoadBuf(Modbus_Sendbuf,'S',8);
						
					ModBus_SendFrame(0x01,0x06,0x0600,(unsigned int)targe_size_data);//写低16位			
					ModBus_Queue_LoadBuf(Modbus_Sendbuf,'B',8);
					
					ModBus_SendFrame(0x01,0x06,0x0601,(unsigned int)targe_size_data>>16);//写高16位
					ModBus_Queue_LoadBuf(Modbus_Sendbuf,'B',8);			
					
					ModBus_SendFrame(0x01,0x06,0x0602,motion_runspeed);//设置运行速度
					ModBus_Queue_LoadBuf(Modbus_Sendbuf,'P',8);
				}
				else
				{//相同位置，不运行
					
					
				}
			}
				
		}

}


//校基准
unsigned char App_Modbus_Motion_Calibration(int cal_dimension)
{
if(Modbus_Servo_Link_Flag==0)//如果没有连接，不允许校基准
	return 1;
	
while(Circle_UpData_Flag==0);

Circle_UpData_Flag=0;

Modbus_Motion_Parameter.Calibration_Flag=0xAA;
Modbus_Motion_Parameter.Calibration_Circle_Data=Circle_Data;
Modbus_Motion_Parameter.Calibration_Dimension_Data=cal_dimension;



iFiles.FileLength=sizeof(Modbus_Motion_Parameter);//.fsize;

memcpy((unsigned char *)DOWNFILE_SDRAM_ADD,&Modbus_Motion_Parameter,iFiles.FileLength);

ChangeFileName((unsigned char*)"ModBus_Servo_Config.cfg");	//NandEccWrite_Flag=0;
File_Create((char*)iFiles.FileName);//建立文件
	
App_Modbus_Motion_Reload_Dimension();//重新装载

return 0;	
}


int Modbus_ServoTimeOut=0;

//通读超时检测
void App_Modbus_Servo_TimeOut(void)
{
if(Modbus_Servo_Link_Flag==1)
			{
				Modbus_ServoTimeOut++;
				if(Modbus_ServoTimeOut>=600)
					{//
					Modbus_ServoTimeOut=0;
					Modbus_Servo_Link_Flag=0;
					}				
			}
else
			{				
				Modbus_ServoTimeOut=0;				
			}	
}



//进入系统前的运行
//如果前极限断开。进行后退100MM操作再进入
//如果后极限断开，进行前进100MM操作再进入
//如果前后极限都断开。提示检查


extern void LoadWorkMode_Process(void);

void App_Modbus_Motion_SystemEnter_Run(void)
{
if(WorkStart_flag==0)
	LoadWorkMode_Process();//调入工作画面	
}
