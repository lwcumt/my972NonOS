#include "App_Plc.h"

#include "app_modbus_972.h"
#include "modbus_972.h"
#include "app_modbus_plc.h"
#include "app_modbus_test.h"

#include "m25pe16.h"
#include "app_plc_ext_form.h"

unsigned char Modbus_Servo_Link_Flag=0;// MODBUS 伺服连接标志位
unsigned char Modbus_Servo_Err_Flag=0; // MODBUS 伺服错误标志位
int Modbus_ServoTimeOut=0;


unsigned char Circle_UpData_Flag=0;
unsigned int App_Modbus_Servo_Status=0;

Int32U App_ModBus_DecTime=0;


unsigned char App_Modbus_Send_Return_Flag=0;


unsigned char  Modbus_PLC_Link_Flag=0;
int Modbus_PlcTimeOut=0;


unsigned char FX_Plc_EnbCut_Flag=0;
unsigned char FX_Plc_EnbAutoCut_Flag=0;
unsigned char FX_Plc_EnbAutoCut_Send_Flag=0;






unsigned char FX_Plc_EnbYaZhi_Flag=0;

unsigned char FX_Plc_EnbQiFa_Flag=0;
unsigned char FX_Plc_EnbQiFa_Flag_Temp=0xff;
unsigned char FX_Plc_EnbLiZhi_Flag=0;





unsigned char YaZhiMotorRun_Flag=0;
unsigned char FastCut_Enb_Flag=0;


unsigned short KnifeDownTime=0;//下刀时间

unsigned char PLC_PowerOn_Init_Flag=1;

unsigned char Plc_X_Err_Status=0;



unsigned short FX_Plc_Real_PressureData=0;

unsigned short FX_Plc_Foot_Real_PressureData=0;

unsigned short FX_Plc_PressureData=0;
unsigned short FX_Foot_Plc_PressureData=0;
unsigned short FX_Plc_OldPressureData=0;
unsigned short FX_Plc_Foot_OldPressureData=0;

void App_Plc_Init(void)
{

	
	
	
//App_FX_Plc_LoadPressureData();//调入当前压力
PLC_Load_Config();//高入配置

//FX_Plc_Comm_Status=' ';
//Plc_Comm_TimeOut=0;
//App_Fx_Plc_Poll_SetpCnt=0;
PLC_PowerOn_Init_Flag=1;//上电标志位
	

	
	
}


//modbus 任务运行
void App_Plc_Modbus_Task_Run(void)
{
	
	
	
	
}




//int Modbus_PlcTimeOut=0;

//通讯超时检测
void App_Modbus_PLC_TimeOut(void)
{
if(Modbus_PLC_Link_Flag==1)
			{
				Modbus_PlcTimeOut++;
				if(Modbus_PlcTimeOut>=600)
					{//
					Modbus_PlcTimeOut=0;
					Modbus_PLC_Link_Flag=0;
						
					LinkUpDate_Flag=1;
					}				
			}
else
			{				
				Modbus_PlcTimeOut=0;				
			}	
}


//通讯超时检测
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

unsigned char Ori_Sensor_Status=0;

unsigned char Knife_Sensor_Status=1;
unsigned char Press_Sensor_Status=1;
unsigned char TuoBan_Status=0;
unsigned char IR_Sensor_Status=0;





void App_Sensor_Get_Status(void)
{
	
////////////if(PLC_PowerOn_Init_Flag==1)
////////////	{
////////////	Ori_Sensor_Status=1;
////////////	Knife_Sensor_Status=1;
////////////	Press_Sensor_Status=1;
////////////	//TuoBan_Status=1;
//////////////	IR_Sensor_Status=0;
////////////		return;
////////////	}

///***************************
//刀

	//原点
			if(PLC_X_Status[ORI_X_IN/10][ORI_X_IN%10]=='0')
			{
			Ori_Sensor_Status=1;
			}
		else
			{
			Ori_Sensor_Status=0;
			}
			
			
if(PLC_Run_Mode!=PLC_MODE_3U)//无PLC功能退出，以下不显示
	{//没有PLC的时候，刀只能在伺服上

//////////	//Knife_Sensor_Status=Modbus_Servo_X_Status[SERVO_KNIFE_X_IN/10][SERVO_KNIFE_X_IN%10];
//////////	if(Modbus_Servo_X_Status[SERVO_KNIFE_X_IN/10][SERVO_KNIFE_X_IN%10]=='0')
//////////		{
//////////		Knife_Sensor_Status=0;
//////////		}
//////////	else
//////////		{
//////////		Knife_Sensor_Status=1;
//////////		}
	}
else
	{

	#ifdef NACHUAN_SERVO//纳川的，刀只能在PLC

		//刀信号接在PLC X 端
		//Knife_Sensor_Status=PLC_X_Status[KNIFE_X_IN/10][KNIFE_X_IN%10];
		if(PLC_X_Status[KNIFE_X_IN/10][KNIFE_X_IN%10]=='0')
			{
			Knife_Sensor_Status=1;
			}
		else
			{
			Knife_Sensor_Status=0;
			}


	#else

		#ifdef KNIFE_ON_SERVO
		//刀信号接在伺服 X 端
		//Knife_Sensor_Status=Modbus_Servo_X_Status[SERVO_KNIFE_X_IN/10][SERVO_KNIFE_X_IN%10];
		if(Modbus_Servo_X_Status[SERVO_KNIFE_X_IN/10][SERVO_KNIFE_X_IN%10]=='0')
			{
			Knife_Sensor_Status=0;
			}
		else
			{
			Knife_Sensor_Status=1;
			}
		#else
		//刀信号接在PLC X 端
		//Knife_Sensor_Status=PLC_X_Status[KNIFE_X_IN/10][KNIFE_X_IN%10];
		if(PLC_X_Status[KNIFE_X_IN/10][KNIFE_X_IN%10]=='0')
			{
			Knife_Sensor_Status=1;
			}
		else
			{
			Knife_Sensor_Status=0;
			}

		#endif
	#endif

	}


///***************************
//压纸
if(PLC_Run_Mode!=PLC_MODE_3U)//无PLC功能退出，以下不显示
	{//没有PLC的时候，压只能在伺服上
////////	//压纸信号接在伺服 X 端
////////	if(Modbus_Servo_X_Status[SERVO_PRESS_X_IN/10][SERVO_PRESS_X_IN%10]=='0')
////////		{
////////		Press_Sensor_Status=1;
////////		}
////////	else
////////		{
////////		Press_Sensor_Status=0;
////////		}
	}
else
	{

	#ifdef NACHUAN_SERVO//纳川的，压只能在PLC

		//压纸信号接在PLC X 端
		if(PLC_X_Status[PRESS_X_IN/10][PRESS_X_IN%10]=='0')
			{
			Press_Sensor_Status=1;
			}
		else
			{
			Press_Sensor_Status=0;
			}
	#else

		#ifdef PRESS_ON_SERVO
		//压纸信号接在伺服 X 端
		if(Modbus_Servo_X_Status[SERVO_PRESS_X_IN/10][SERVO_PRESS_X_IN%10]=='0')
			{
			Press_Sensor_Status=1;
			}
		else
			{
			Press_Sensor_Status=0;
			}
		#else
		//压纸信号接在PLC X 端
		if(PLC_X_Status[PRESS_X_IN/10][PRESS_X_IN%10]=='0')
			{
			Press_Sensor_Status=1;
			}
		else
			{
			Press_Sensor_Status=0;
			}

		#endif
	#endif
	}


///***************************
//托板
#ifdef TUOBAN_ON_SERVO
//托板信号接在伺服 X 端
if(Modbus_Servo_X_Status[SERVO_TUOBAN_X_IN/10][SERVO_TUOBAN_X_IN%10]=='0')
	{
	TuoBan_Status=0;
	}
else
	{
	TuoBan_Status=1;
	}
#else
//托板信号接在PLC X 端
if(PLC_X_Status[TUOBAN_X_IN/10][TUOBAN_X_IN%10]=='0')
	{
	TuoBan_Status=0;
	}
else
	{
	TuoBan_Status=1;
	}
#endif

///***************************
//后限
//////////////if(Modbus_Servo_X_Status[SERVO_BACK_LIMIT_X_IN/10][SERVO_BACK_LIMIT_X_IN%10]=='0')
//////////////	{
//////////////	Back_Limit_Sensor_Status=1;
//////////////	}
//////////////else
//////////////	{
//////////////	Back_Limit_Sensor_Status=0;
//////////////	}


/////////////////***************************
////////////////前限
//////////////if(Modbus_Servo_X_Status[SERVO_AHEAD_LIMIT_X_IN/10][SERVO_AHEAD_LIMIT_X_IN%10]=='0')
//////////////	{
//////////////	Ahead_Limit_Sensor_Status=1;
//////////////	}
//////////////else
//////////////	{
//////////////	Ahead_Limit_Sensor_Status=0;
//////////////	}


///***************************
//红外

if(PLC_Run_Mode!=PLC_MODE_3U)//无PLC功能退出，以下不显示
	{//没有PLC的时候，红外只能在伺服上
	//红外信号接在伺服 X 端

////////	//红外在伺服上
////////	if(Modbus_Servo_X_Status[SERVO_IR_X_IN/10][SERVO_IR_X_IN%10]=='0')
////////		{
////////		IR_Sensor_Status=0;
////////		}
////////	else
////////		{
////////		IR_Sensor_Status=1;
////////		}
	}
else
	{
	#ifdef NACHUAN_SERVO//纳川  红外只能在PLC
		//红外接在PLC上
		if(PLC_X_Status[IR_X_IN/10][IR_X_IN%10]=='0')
			{
			IR_Sensor_Status=0;
			}
		else
			{
			IR_Sensor_Status=1;
			}

	#else

		#ifdef IR_ON_SERVO
		//红外在伺服上
		if(Modbus_Servo_X_Status[SERVO_IR_X_IN/10][SERVO_IR_X_IN%10]=='0')
			{
			IR_Sensor_Status=0;
			}
		else
			{
			IR_Sensor_Status=1;
			}
		#else
		//红外接在PLC上
		if(PLC_X_Status[IR_X_IN/10][IR_X_IN%10]=='0')
			{
			IR_Sensor_Status=0;
			}
		else
			{
			IR_Sensor_Status=1;
			}

		#endif
	#endif

	}

}





void PLC_Load_Config(void)
{

	
	Int32U add,n;
unsigned char rdata[10];
	unsigned short rdat;
add= FX_PLC_CONFIG_SAVE_ADDER;
FastRead_Datas_Start(add);
for(n=0;n<10;n++)
	{
	rdata[n]=ReadFlash_Datas();
	}
FlashChip_Dis;

//unsigned int Motor_StartUpTime=0;//电机启动时间
////////Motor_StartUpTime= rdata[0];
////////Motor_StartUpTime<<=8;//
////////Motor_StartUpTime+=rdata[1];
////////	
////////	
//unsigned int Motor_StopTime=0;//电机停止时间
Motor_StopTime= rdata[2];
Motor_StopTime<<=8;//
Motor_StopTime+=rdata[3];
	
	
//unsigned int KnifeDownTime=0;//下刀时间
KnifeDownTime= rdata[4];
KnifeDownTime<<=8;//
KnifeDownTime+=rdata[5];
	
////////////	unsigned char CutOpt_Flag=0;//裁切优化 《开关》
//////////CutOpt_Flag= rdata[6];

//////////	
////////////unsigned int CutTime=0;   //优化时间  
//////////CutTime= rdata[7];
//////////CutTime<<=8;//
//////////CutTime+=rdata[8];

////////////	unsigned int FastCut_Flag=0;  //快速裁切 《开关》
//////////FastCut_Flag= rdata[9];	

n=0;

//////////unsigned int Motor_StartUpTime=0;//电机启动时间
////////if((Motor_StartUpTime<8)||(Motor_StartUpTime>30))
////////	{
////////	Motor_StartUpTime=15;
////////	n=1;	
////////	}
////////	
	//unsigned int Motor_StopTime=0;//电机停止时间
	if((Motor_StopTime<1)||(Motor_StopTime>180))
	{
	Motor_StopTime=120;
  n=1;			
	}
	
	//unsigned int KnifeDownTime=0;//下刀时间
	if((KnifeDownTime<1)||(KnifeDownTime>30))
	{
		KnifeDownTime=4;
		n=1;	
	}
	
//////////	//	unsigned char CutOpt_Flag=0;//裁切优化 《开关》
//////////	if(CutOpt_Flag>1)//||(Motor_StartUpTime>30))
//////////	{
//////////	CutOpt_Flag=0;//默认关闭
//////////	n=1;	
//////////	}
//////////	
//////////	
//////////	//unsigned int CutTime=0;   //优化时间  
//////////	if((CutTime<1)||(CutTime>10))
//////////	{
//////////	CutTime=4;//默认4
//////////	n=1;		
//////////	}
//////////	
//////////	//	unsigned int FastCut_Flag=0;  //快速裁切 《开关》
//////////	if(FastCut_Flag>1)//<8)||(Motor_StartUpTime>30))
//////////	{
//////////	FastCut_Flag=0;//默认关闭
//////////	n=1;		
//////////	}
	
	if(	n==1)
	{		
		PLC_Save_Config();//保存默认
	}	
}




void PLC_Save_Config(void)
{	
	
	
unsigned char wdata[10];	
	
////////	//unsigned int Motor_StartUpTime=0;//电机启动时间
////////  	wdata[0]=Motor_StartUpTime>>8;
////////		wdata[1]=Motor_StartUpTime;
////////	
////////	
	//unsigned int Motor_StopTime=0;//电机停止时间
		wdata[2]=Motor_StopTime>>8;
		wdata[3]=Motor_StopTime;
////////	
	
	//unsigned int KnifeDownTime=0;//下刀时间
		wdata[4]=KnifeDownTime>>8;
		wdata[5]=KnifeDownTime;
	
//////////	unsigned char CutOpt_Flag=0;//裁切优化 《开关》
////////		wdata[6]=CutOpt_Flag;
////////	
////////	
////////	//unsigned int CutTime=0;   //优化时间  
////////		wdata[7]=CutTime>>8;
////////		wdata[8]=CutTime;
////////		
////////	//	unsigned int FastCut_Flag=0;  //快速裁切 《开关》
////////		wdata[9]=FastCut_Flag;


Write_25pe_data(wdata, FX_PLC_CONFIG_SAVE_ADDER,10);//保存压力值	

PLC_PowerOn_Init_Flag=1; //DT数据变化，重发			
	
}



#include "app_plc_ext_form.h"

unsigned char FX_PLC_Motor_Run_Enb_Flag=0;

unsigned int MainPower_Delay_Check_YOUT_Time=0;

//检测主机启动状态
void Check_FX_PLC_Motor_Run_Status(void)
{
	
	return;
	
				if(MainPower_Status>0)//延时1秒后再检查Y有无输出
						{
							if(MainPower_Delay_Check_YOUT_Time<1200)
								MainPower_Delay_Check_YOUT_Time++;
							else
							{
							if(PLC_Y_Status[0][0]==PLC_CONTACT_OFF)//判断下Y20 输出，如果没有，关闭已打开图标
								{//停目状态	
									
										App_Modbus_Plc_Write_M_Status(100,M_OFF);	
							//	if(App_FX_Plc_Force_Process("OFF",M100)==0)
											{
												
													App_Modbus_Plc_Write_M_Status(101,M_ON);	
											//if(App_FX_Plc_Force_Process("ON",M101)==0)
													{			
													//if(MainPower_Status>0)
															{
															MainPower_Status=0;
															cpGui_CreatePictureBox(&Main_PowerOn_Picture_Dis);
															//Printf24("          主机已停止          ",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,RED_COLOR,1,0xffff);
															}			
													}
											}
									
								FX_PLC_Motor_Run_Enb_Flag=0;
								}	
							}								
						}
			else
				
			{
				MainPower_Delay_Check_YOUT_Time=0;
			FX_PLC_Motor_Run_Enb_Flag=1;
			}
			
	
	return;
	
	
	//if((FX_PLC_X_Status[1][2]=='1')&&(FX_PLC_X_Status[1][3]=='1')&&(FX_PLC_X_Status[1][6]=='1')&&(FX_PLC_X_Status[1][7]=='1'))	
if((PLC_X_Status[1][6]=='1')&&(PLC_X_Status[1][7]=='1'))	//判断一下左右拉手
		{			
			
			if(MainPower_Status>0)//延时1秒后再检查Y有无输出
						{
							if(MainPower_Delay_Check_YOUT_Time<1000)
								MainPower_Delay_Check_YOUT_Time++;
							else
							{
							if(PLC_Y_Status[0][0]==PLC_CONTACT_OFF)//判断下Y20 输出，如果没有，关闭已打开图标
								{//停目状态	
									
										App_Modbus_Plc_Write_M_Status(100,M_OFF);	
							//	if(App_FX_Plc_Force_Process("OFF",M100)==0)
											{
												
													App_Modbus_Plc_Write_M_Status(101,M_ON);	
											//if(App_FX_Plc_Force_Process("ON",M101)==0)
													{			
													//if(MainPower_Status>0)
															{
															MainPower_Status=0;
															cpGui_CreatePictureBox(&Main_PowerOn_Picture_Dis);
															//Printf24("          主机已停止          ",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,RED_COLOR,1,0xffff);
															}			
													}
											}
									
								FX_PLC_Motor_Run_Enb_Flag=0;
								}	
							}								
						}
			else
				
			{
				MainPower_Delay_Check_YOUT_Time=0;
			FX_PLC_Motor_Run_Enb_Flag=1;
			}
		
		}
else	
		{//断开后关闭主机
			FX_PLC_Motor_Run_Enb_Flag=0;
			MainPower_Delay_Check_YOUT_Time=0;
			
			if(MainPower_Status>0)
						{
							
							App_Modbus_Plc_Write_M_Status(100,M_OFF);	
					//	if(App_FX_Plc_Force_Process("OFF",M100)==0)
									{
										
										App_Modbus_Plc_Write_M_Status(101,M_ON);	
								//	if(App_FX_Plc_Force_Process("ON",M101)==0)
											{			
											//if(MainPower_Status>0)
													{
													MainPower_Status=0;
													cpGui_CreatePictureBox(&Main_PowerOn_Picture_Dis);
													//Printf24("          主机已停止          ",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,RED_COLOR,1,0xffff);
													}			
											}
									}									
					 }	
		
		}		
}



//每次到位时进入

void YaZhi_CheckData(void)	
{
	int i;
	char strr[16];
	KNIFE_DATA Knife_datas;
	
//	if(YaZhi_Process_Flag==0) //已进入，退出
	{	


//////	sprintf(strr,"%d",Knife_order);
//////	Printf24(strr,1000,50,RED_COLOR,1,cpGui_ColorChange(PLC_HINT_DIS_BAK_COLOR));
	GetOneKnife_datas(Pro_data.pro_num, Knife_order , (pInt8U)&Knife_datas);//取出一刀 数据

//	sprintf(strr,"%d",Knife_datas.k_flag);
//	Printf24(strr,950,50,RED_COLOR,1,cpGui_ColorChange(PLC_HINT_DIS_BAK_COLOR));
	
if((Knife_datas.k_flag&0xf)==PRESS_FLAG)
		{

			FX_Plc_EnbYaZhi_Flag=1;
			
	//		YaZhi_Run_Enb_Flag=1;
		
		if(FX_Plc_EnbLiZhi_Flag==1)
							FX_Plc_EnbLiZhi_Flag=0;		
		}
	else
		
			if((Knife_datas.k_flag&0xf)==SORT_FLAG)
				{
				FX_Plc_EnbLiZhi_Flag=1;
				if(FX_Plc_EnbYaZhi_Flag!=0)
					FX_Plc_EnbYaZhi_Flag=0;
				}			
		else
				{
				FX_Plc_EnbLiZhi_Flag=0;		
				FX_Plc_EnbYaZhi_Flag=0;
				}
		

		
									
//////					{
//////					BellOn_Enb();
//////					}
	//	}
	}
}