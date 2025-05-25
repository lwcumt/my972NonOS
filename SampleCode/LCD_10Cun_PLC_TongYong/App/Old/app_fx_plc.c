#include "app_fx_plc.h"

#include "stdio.h"
#include "string.h"
#include "stdlib.h"

#include "key.h"
#include "pic_exec.h"
#include "m25pe16.h"
#include "comm_fx_plc.h"

#include "plc_ext_form.h"

#include "chndot.h"

#include "optimize_cut.h"


#include "port.h"

unsigned char  GuangDian_Flag=0;


unsigned short FX_Plc_Real_PressureData=0;

unsigned short FX_Plc_Foot_Real_PressureData=0;

unsigned short FX_Plc_PressureData=0;
unsigned short FX_Foot_Plc_PressureData=0;
unsigned short FX_Plc_OldPressureData=0;
unsigned short FX_Plc_Foot_OldPressureData=0;

unsigned char App_FX_Plc_CommBuf[32];


unsigned char FX_Plc_X_Status_Byte[16]={'0',0};  //
unsigned char FX_Plc_Y_Status_Byte[16]={'0',0};;


unsigned char FX_PLC_X_StatusBuf[5];
unsigned char FX_PLC_Y_StatusBuf[5];


char FX_PLC_X_Status[5][8];
char FX_PLC_Y_Status[5][8];

char FX_Plc_X4_Status='0';
char FX_Plc_X5_Status='0';
char FX_Plc_X12_Status='0';


unsigned short FX_Plc_DT20_Data=10;   //下刀时间  2-100 对应0.2秒 -10秒
unsigned short FX_Plc_DT10_Data=120;  //星三角启动  80-200  对应 8秒-20秒

unsigned char App_FX_Plc_PollTime=0;
unsigned char App_Fx_Plc_Poll_SetpCnt=0;

unsigned char FX_PLC_PowerOn_Init_Flag=1;

unsigned char FX_Plc_PressureData_Download_Flag=0;
unsigned char FX_Plc_Foot_PressureData_Download_Flag=0;

unsigned char FX_Plc_EnbCut_Flag=0;
unsigned char FX_Plc_EnbAutoCut_Flag=0;

unsigned char FX_Plc_EnbQiFa_Flag=0;
unsigned char FX_Plc_EnbLiZhi_Flag=0;

									int 	FX_Plc_Connect_TimeOut=0;

unsigned char FX_Plc_Comm_TimeOut_Flag=1;

unsigned char ProData_ProNum_Old=0;

int FX_Plc_Comm_TimeOut=0;

void App_FX_Plc_CommDecode(void)
{
unsigned char x_status=0;
int i=0;
int n=0;
//memcpy(App_FX_Plc_CommBuf,Fx_Plc_RecvBuf,32);
switch(FX_Plc_Comm_Status)
		{
		case 'X':
			memcpy(FX_Plc_X_Status_Byte,Fx_Plc_RecvBuf,16);  //
		
			for(i=0;i<4;i++)
				{
				if(FX_Plc_X_Status_Byte[i*2]>'9')
					x_status=FX_Plc_X_Status_Byte[i*2]-0x37;
				else
					x_status=FX_Plc_X_Status_Byte[i*2]-0x30;
				x_status<<=4;
			
				if(FX_Plc_X_Status_Byte[i*2+1]>'9')
					x_status+=FX_Plc_X_Status_Byte[i*2+1]-0x37;
				else
					x_status+=FX_Plc_X_Status_Byte[i*2+1]-0x30;	
			
				FX_PLC_X_StatusBuf[i]=x_status;
				
				for(n=0;n<8;n++)
					{
						if(x_status&0x01)
							FX_PLC_X_Status[i][n]='1';
						else
							FX_PLC_X_Status[i][n]='0';
						x_status>>=1;
					}
				}
			

////			
////			//取X4状态
////			if(FX_PLC_X_StatusBuf[0]&(1<<4))
////				FX_Plc_X4_Status='1';
////			else
////				FX_Plc_X4_Status='0';
////			
////			//取X5 状态
////			if(FX_PLC_X_StatusBuf[0]&(1<<5))
////				FX_Plc_X5_Status='1';
////			else
////				FX_Plc_X5_Status='0';			
////			
////		  if(FX_Plc_X_Status_Byte[2]>'9')
////				x_status=FX_Plc_X_Status_Byte[2]-0x37;
////			else
////				x_status=FX_Plc_X_Status_Byte[2]-0x30;
////			x_status<<=4;
////			
////		  if(FX_Plc_X_Status_Byte[3]>'9')
////				x_status+=FX_Plc_X_Status_Byte[3]-0x37;
////			else
////				x_status+=FX_Plc_X_Status_Byte[3]-0x30;	
////			
////			//取X12 状态
////			if(FX_PLC_X_StatusBuf[1]&(1<<2))
////				FX_Plc_X12_Status='1';   
////			else
////				FX_Plc_X12_Status='0';		
			
			break;
		case 'Y':
			memcpy(FX_Plc_Y_Status_Byte,Fx_Plc_RecvBuf,16);  //			
		
			for(i=0;i<4;i++)
				{
				if(FX_Plc_Y_Status_Byte[i*2]>'9')
					x_status=FX_Plc_Y_Status_Byte[i*2]-0x37;
				else
					x_status=FX_Plc_Y_Status_Byte[i*2]-0x30;
				x_status<<=4;
			
				if(FX_Plc_Y_Status_Byte[i*2+1]>'9')
					x_status+=FX_Plc_Y_Status_Byte[i*2+1]-0x37;
				else
					x_status+=FX_Plc_Y_Status_Byte[i*2+1]-0x30;	
			
				FX_PLC_Y_StatusBuf[i]=x_status;
				
				for(n=0;n<8;n++)
					{
						if(x_status&0x01)
							FX_PLC_Y_Status[i][n]='1';
						else
							FX_PLC_Y_Status[i][n]='0';
						x_status>>=1;
					}
				}		
			break;
		case 'D':
			break;	
		case ' '://  ACK \NAK  返回
			break;
		}		
}


void App_FX_Plc_Init(void)
{
	
	
	
App_FX_Plc_LoadPressureData();//调入当前压力
FX_PLC_Load_Config();//高入配置

FX_Plc_Comm_Status=' ';
FX_Plc_Comm_TimeOut=0;
App_Fx_Plc_Poll_SetpCnt=0;
FX_PLC_PowerOn_Init_Flag=1;//上电标志位
	
}



void App_FX_Plc_LoadPressureData(void)
{
ProData_ProNum_Old=Pro_data.pro_num;
	
FX_Plc_PressureData=FX_Read_PressureData(Pro_data.pro_num);//读取压力值
FX_Foot_Plc_PressureData=	FX_Read_Foot_PressureData(Pro_data.pro_num);

if((FX_Plc_PressureData<250)||(FX_Plc_PressureData>1000))
		{//非法数据，置初值
		FX_Plc_PressureData=750;	
		FX_Save_PressureData(Pro_data.pro_num);				
		}	
		
if((FX_Foot_Plc_PressureData<100)||(FX_Foot_Plc_PressureData>400))
		{//非法数据，置初值
		FX_Foot_Plc_PressureData=200;	
		FX_Save_Foot_PressureData(Pro_data.pro_num);//保存一下新数据					
		}	
		
		
FX_Plc_OldPressureData=FX_Plc_PressureData;		
FX_Plc_Foot_OldPressureData=FX_Foot_Plc_PressureData;
		
FX_Plc_PressureData_Download_Flag=1;//更新一下压力值		
FX_Plc_Foot_PressureData_Download_Flag=1;
	
}


void App_FX_Plc_Run(void)
{
char strbuf[16];
APP_FX_Plc_Poll_Exec();
	
App_FX_Plc_Pressure_AutoSave();
	
if(ProData_ProNum_Old!=Pro_data.pro_num)
{
	App_FX_Plc_LoadPressureData();//重新载入压力数据
	
}
	

PLC_FX_Hint_DisPlay();//加入信息提示
	
FX_PLC_XY_Status_Display();//PLC IO状态显示

FX_PLC_Check_IO_Status();
	
//sprintf(strbuf,"%2x",FX_Plc_X_Status_Byte[0]);
//////Printf24(FX_Plc_X_Status_Byte,50,300,RED_COLOR,1,WHITE_COLOR);	
//////Printf24(FX_Plc_Y_Status_Byte,50,340,RED_COLOR,1,WHITE_COLOR);	
	
}


#include "app_plc.h"


//for Test
void APP_FX_Plc_Poll_Exec(void)
{
int fxplctime=0;
unsigned int ti;
	unsigned char wdata[8];
	char strbuf[16];
	
	unsigned short tempdat=0;
	
	
	float  realpresure=0.0;
	
//FX_Plc_Comm_Status='I';
	

			
App_FX_Plc_PollTime++;
if(App_FX_Plc_PollTime>=10)
		{
		App_FX_Plc_PollTime=0;
		//	strbuf[0]=FX_Plc_Comm_Status;
		//	strbuf[1]=0;
		//	Printf24(strbuf,50,500,RED_COLOR,1,WHITE_COLOR);	
			
		if(FX_Plc_Comm_Status!=' ')
				return;
		App_Fx_Plc_Poll_SetpCnt++;
		if(App_Fx_Plc_Poll_SetpCnt>=10)
			{			
			App_Fx_Plc_Poll_SetpCnt=0;
			}			
		//	sprintf(strbuf,"%x",Fx_Plc_Poll_SetpCnt);
		//	Printf24(strbuf,50,500,RED_COLOR,1,WHITE_COLOR);			
		if((App_Fx_Plc_Poll_SetpCnt<4)&&(FX_PLC_PowerOn_Init_Flag==0))
			App_Fx_Plc_Poll_SetpCnt=4;
		
		switch(App_Fx_Plc_Poll_SetpCnt)
			{
			case 1:
				if(FX_PLC_PowerOn_Init_Flag==1)
					{   //D10   星三角启动 时间
						tempdat=Motor_StartUpTime*10;
					Comm_FX_Plc_Write_D_Area(10,(unsigned char*)&tempdat,2);						
					}
					
////				if(Plc_Send_DT_Data_Flag==1)
////				{
////					Plc_Send_DT_Data_Flag=0;
////					Comm_FX_Plc_Write_D_Area(20,(unsigned char*)&Plc_DT_Data_t[1],2);						
////				}
				//强制打开Y50
				//	Comm_FX_Plc_ForceON(SwapAdder(Y050));
				break;
			case 2:
				
				if(FX_PLC_PowerOn_Init_Flag==1)
					{   //D10   星三角安全停止 时间
						tempdat=Motor_StopTime*10;
					Comm_FX_Plc_Write_D_Area(400,(unsigned char*)&tempdat,2);						
					}
					
				break;
			
			case 3:
				if(FX_PLC_PowerOn_Init_Flag==1)
				{//		D20下刀时间			
					
				tempdat=KnifeDownTime*10;
				Comm_FX_Plc_Write_D_Area(20,(unsigned char*)&tempdat,2);		
				Optimize_Cut_DelayTime_DownLoad_Flag=1;//发送一次优化裁切延时时间					
				FX_PLC_PowerOn_Init_Flag=0;					
				}
				break;
			case 4:
				Comm_FX_Plc_Read_X_Status(X000_7,4);//读取X00-X07  至 X30 -X37的状态
				break;
			case 5:
				Comm_FX_Plc_Read_Y_Status(Y020_7,4);//读取Y20-Y27  至 Y50 -Y57的状态				
				break;
			case 6://允许裁切		//M3XX开头的，合并发送
				if(WorkMode==MANUAL_MODE)
				{
					if(Run_flag==1)
					{
					App_FX_Plc_Force_Process("OFF",M300);						
					}
				else
					{
					App_FX_Plc_Force_Process("ON",M300);
					}					
				}
				else
				{
				if(FX_Plc_EnbCut_Flag==0)
					{
					App_FX_Plc_Force_Process("ON",M300);
				//Comm_FX_Plc_ForceON(SwapAdder(M300));
					}
				else
					{
					App_FX_Plc_Force_Process("OFF",M300);					
					//Comm_FX_Plc_ForceOFF(SwapAdder(M300));				
					}
				}
				
			if(FX_Plc_EnbAutoCut_Flag==0)
				{
					App_FX_Plc_Force_Process("ON",M301);					
			//	Comm_FX_Plc_ForceON(SwapAdder(M301));
				}
			else
				{
					App_FX_Plc_Force_Process("OFF",M301);					
			//	Comm_FX_Plc_ForceOFF(SwapAdder(M301));					
				}	
			if(FX_Plc_EnbQiFa_Flag==0)
					{
					App_FX_Plc_Force_Process("ON",M302);						
					//	Comm_FX_Plc_ForceON(SwapAdder(M302));								
					}
				else
					{
					App_FX_Plc_Force_Process("OFF",M302);						
					//	Comm_FX_Plc_ForceOFF(SwapAdder(M302));					
					}
					
					if((YaZhiMotorRun_Flag==1)||(WorkMode!=AUTO_MODE))
					{
						App_FX_Plc_Force_Process("OFF",M303);			
					}
					else
					{
						if(FX_Plc_EnbLiZhi_Flag==0)
							{
							App_FX_Plc_Force_Process("OFF",M303);						
									
							}
						else
							{
								if(Run_flag==1)
								{
									App_FX_Plc_Force_Process("OFF",M303);
								}
								else
								{									
								App_FX_Plc_Force_Process("ON",M303);						
								}
										
							}					
					}
					
				if(OptimizeCut_Enb_Flag==0)
					{
					App_FX_Plc_Force_Process("ON",M210);						
				//	Comm_FX_Plc_ForceON(SwapAdder(M210));								
					}
				else
					{
					App_FX_Plc_Force_Process("OFF",M210);
				//	Comm_FX_Plc_ForceOFF(SwapAdder(M210));					
					}
					
				if(FastCut_Enb_Flag==0)
					{
					App_FX_Plc_Force_Process("ON",M230);						
				//	Comm_FX_Plc_ForceON(SwapAdder(M230));								
					}
				else
					{
					App_FX_Plc_Force_Process("OFF",M230);						
				//	Comm_FX_Plc_ForceOFF(SwapAdder(M230));					
					}	
					
//////				wdata[0]=0x2;//写入长度
//////				wdata[1]=100;//先低字节，再高字节
//////				wdata[2]=0;
//////				ti=625;					
//////		//		Comm_FX_Plc_Write_D_Area(300,(unsigned char*)&ti,2);		
				if(FX_Plc_PressureData_Download_Flag==0)
				{
				if(FX_Plc_Foot_PressureData_Download_Flag==1)
							App_Fx_Plc_Poll_SetpCnt=7;//跳转到 发送脚踩压力
				else
					{											
					if(Optimize_Cut_DelayTime_DownLoad_Flag==0)
					{
						App_Fx_Plc_Poll_SetpCnt=0;//没有压力发送和D30允许，直接跳到0步
							
					}
				else
						{
							App_Fx_Plc_Poll_SetpCnt=8;//没有压力发送允许，实际为7，下次进入指向计数器加1 D30发送允许，则跳到 D30处
						}
					}
				}
				break;					
					
			case 7:
				if(FX_Plc_PressureData_Download_Flag==1)
				{
					FX_Plc_PressureData_Download_Flag=0;
					 realpresure=((float)FX_Plc_PressureData-250.0)/2.5+370;
					FX_Plc_Real_PressureData=realpresure;//发送转换后的压力
					Comm_FX_Plc_Write_D_Area(50,(unsigned char*)&FX_Plc_Real_PressureData,2);	
					//Comm_FX_Plc_Write_D_Area(50,(unsigned char*)&FX_Plc_PressureData,2);	
				}
				break;
			case 8:
				
			

					
					
				if(FX_Plc_Foot_PressureData_Download_Flag==1)
					{
					FX_Plc_Foot_PressureData_Download_Flag=0;
						
					if(FX_Foot_Plc_PressureData>=140)
						{
						 realpresure=((float)FX_Foot_Plc_PressureData-140.0)/2.5+300;
				  	FX_Plc_Foot_Real_PressureData=realpresure;//发送转换后的压力			
							
						}
					else
					{
						if(FX_Foot_Plc_PressureData==130)
						{
							FX_Plc_Foot_Real_PressureData=295;
						}
						else
							if(FX_Foot_Plc_PressureData==120)
							{
								FX_Plc_Foot_Real_PressureData=290;
							}
							else								
							if(FX_Foot_Plc_PressureData==110)
							{
								FX_Plc_Foot_Real_PressureData=285;
							}
							else								
							{
//////									if(FX_Foot_Plc_PressureData==110)
//////									{
//////										FX_Plc_Foot_Real_PressureData=300;	
//////									}
//////									else
										FX_Plc_Foot_Real_PressureData=280;							
							}						
					}
					
////////					if(FX_Foot_Plc_PressureData>=150)
////////						{
////////						 realpresure=((float)FX_Foot_Plc_PressureData-150.0)/2.5+330;
////////				  	FX_Plc_Foot_Real_PressureData=realpresure;//发送转换后的压力			
////////							
////////						}
////////					else
////////					{
////////						if(FX_Foot_Plc_PressureData==140)
////////						{
////////							FX_Plc_Foot_Real_PressureData=320;
////////						}
////////						else
////////							if(FX_Foot_Plc_PressureData==130)
////////							{
////////								FX_Plc_Foot_Real_PressureData=315;
////////							}
////////							else								
////////							if(FX_Foot_Plc_PressureData==120)
////////							{
////////								FX_Plc_Foot_Real_PressureData=310;
////////							}
////////							else								
////////							{
////////									if(FX_Foot_Plc_PressureData==110)
////////									{
////////										FX_Plc_Foot_Real_PressureData=300;	
////////									}
////////									else
////////										FX_Plc_Foot_Real_PressureData=280;							
////////							}						
////////					}
					
					
					Comm_FX_Plc_Write_D_Area(410,(unsigned char*)&FX_Plc_Foot_Real_PressureData,2);	
				//	Comm_FX_Plc_Write_D_Area(410,(unsigned char*)&FX_Foot_Plc_PressureData,2);	
					}
					
				if(Optimize_Cut_DelayTime_DownLoad_Flag==0)
					{
						App_Fx_Plc_Poll_SetpCnt=0;//没有压力发送和D30允许，直接跳到0步
					}
				
				break;
			
				//		Comm_FX_Plc_Read_D_Area(20,2);
				//		Comm_FX_Plc_Read(X000_7,2);//读取2个字节 从X00-X07 到 X10-X17						
				//		break;	
			case 9://D30发送
						if(Optimize_Cut_DelayTime_DownLoad_Flag==1)
					{
						tempdat=CutTime*10;
						Comm_FX_Plc_Write_D_Area(30,(unsigned char*)&tempdat,2);			
						Optimize_Cut_DelayTime_DownLoad_Flag=0;
					}				
				// Comm_FX_Plc_ForceOFF(SwapAdder(M101));
				break;
			case 10://气阀
						
				break;		

			case 11://理纸
					
				break;	
			case 12: //D30发送优化裁切延时时间 

				break;
			case 13:
							
				break;
			case 14:				
				
				break;
			}
	}			
}


void App_FX_PLC_LiZhi_MotorRunStop(void)
{
	#ifdef FX_PLC
	
	App_FX_Plc_Force_Process("OFF",M303);
	
	if(WorkMode==MANUAL_MODE)
				{
				//	if(Run_flag==1)
					{
					App_FX_Plc_Force_Process("OFF",M300);						
					}
			//	else
					{
				//	App_FX_Plc_Force_Process("ON",M300);
					}					
				}
	
	#endif	
}


int FX_Plc_Comm_TimeOut_RstTime=1;
void App_FX_Plc_TimeOut_Exec(void)
{
////////if(WorkStart_flag==0)//没进入工作画面。退出
////////{
////////FX_Plc_Comm_TimeOut_RstTime=0;	
////////FX_Plc_Comm_TimeOut=0;				
////////FX_Plc_Comm_TimeOut_Flag=0;//置超时			
////////	return;
////////}
	if((FX_Plc_Comm_Status!=' '))//(FX_Plc_Comm_Status!='T'))
			{
				FX_Plc_Comm_TimeOut++;
				if(FX_Plc_Comm_TimeOut>=2000)//通讯发送2S超时
				{					
				FX_Plc_Comm_TimeOut=0;				
				FX_Plc_Comm_TimeOut_Flag=1;//置超时					
				//	FX_Plc_Comm_Status=' ';
					
				//	FX_Plc_Comm_Status='T';//超时					
				}
			}
else
		FX_Plc_Comm_TimeOut=0;	
	
if(FX_Plc_Comm_TimeOut_Flag==1)
			{//30秒后复检清0
			FX_Plc_Comm_TimeOut_RstTime++;
			if(FX_Plc_Comm_TimeOut_RstTime>=10000)
				{
				FX_Plc_Comm_TimeOut_RstTime=0;
				FX_Plc_Comm_TimeOut_Flag=0;
					
				FX_Plc_Comm_Status=' ';//清状态
				}				
			}
else
			{
				FX_Plc_Comm_TimeOut_RstTime=0;
			}
}



unsigned char  App_FX_Plc_Force_Process(char *sta,unsigned int adder)
{
int i;
for(i=0;i<3;i++)//3次重发 超时判断
		{
		FX_Plc_Comm_TimeOut=0; 
//		FX_Plc_Comm_TimeOut_Flag=0;
		//App_Plc_SendFrame(cmd,datcode,num,sta);//发送关闭R11
		while(FX_Plc_Comm_Status!=' ')
				{					
				if(FX_Plc_Comm_TimeOut_Flag!=0)//置超时	
					{
					break;						
					}
				};
				
		if(strcmp(sta,"ON")==0)
			{
				Comm_FX_Plc_ForceON(SwapAdder(adder));
			}
	else
			{
				if(strcmp(sta,"OFF")==0)
				{
				Comm_FX_Plc_ForceOFF(SwapAdder(adder));
				}
			}
			
		//App_Plc_SendFrame(cmd,datcode,num,sta);//发送关闭R11
		while(FX_Plc_Comm_Status!=' ')
				{					
				if(FX_Plc_Comm_TimeOut_Flag!=0)//置超时	
					{
					break;						
					}
				};
				
		if(FX_Plc_Comm_Status==' ')
			{
			FX_Plc_Comm_TimeOut=0; 
			break;
			}
		}
		
if(i>=3)
		{//超时，通讯错误
			
		return 1;	
		}
	
return 0;
}


void App_FX_Plc_Pressure_AutoSave(void)
{
if(FX_Plc_OldPressureData!=FX_Plc_PressureData)
		{			
		if((FX_Plc_PressureData>=250)&&(FX_Plc_PressureData<=1000))
				{			
				FX_Save_PressureData(Pro_data.pro_num);//保存一下新数据
				FX_Plc_OldPressureData=FX_Plc_PressureData;		
					
				FX_Plc_PressureData_Download_Flag=1;
				}		
		else
				{//数据不合法
					
					
				}	
		}
		
		if(FX_Plc_Foot_OldPressureData!=FX_Foot_Plc_PressureData)
		{
				if((FX_Foot_Plc_PressureData>=100)&&(FX_Foot_Plc_PressureData<=400))
				{			
				FX_Save_Foot_PressureData(Pro_data.pro_num);//保存一下新数据
				FX_Plc_Foot_OldPressureData=FX_Foot_Plc_PressureData;	
					
				FX_Plc_Foot_PressureData_Download_Flag=1;
				}		
		else
				{//数据不合法
					
					
				}
			}				
}


/*
unsigned int Motor_StartUpTime=0;//电机启动时间
unsigned int Motor_StopTime=0;//电机停止时间
unsigned int KnifeDownTime=0;//下刀时间
unsigned char CutOpt_Flag=0;//裁切优化 《开关》
unsigned int CutTime=0;   //优化时间  
unsigned int FastCut_Flag=0;  //快速裁切 《开关》

*/

void FX_PLC_Save_Config(void)
{	
	
	
unsigned char wdata[10];	
	
	//unsigned int Motor_StartUpTime=0;//电机启动时间
  	wdata[0]=Motor_StartUpTime>>8;
		wdata[1]=Motor_StartUpTime;
	
	
	//unsigned int Motor_StopTime=0;//电机停止时间
		wdata[2]=Motor_StopTime>>8;
		wdata[3]=Motor_StopTime;
	
	
	//unsigned int KnifeDownTime=0;//下刀时间
		wdata[4]=KnifeDownTime>>8;
		wdata[5]=KnifeDownTime;
	
//	unsigned char CutOpt_Flag=0;//裁切优化 《开关》
		wdata[6]=CutOpt_Flag;
	
	
	//unsigned int CutTime=0;   //优化时间  
		wdata[7]=CutTime>>8;
		wdata[8]=CutTime;
		
	//	unsigned int FastCut_Flag=0;  //快速裁切 《开关》
		wdata[9]=FastCut_Flag;


Write_25pe_data(wdata, FX_PLC_CONFIG_SAVE_ADDER,10);//保存压力值	

FX_PLC_PowerOn_Init_Flag=1; //DT数据变化，重发			
	
}



void FX_PLC_Load_Config(void)
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
Motor_StartUpTime= rdata[0];
Motor_StartUpTime<<=8;//
Motor_StartUpTime+=rdata[1];
	
	
//unsigned int Motor_StopTime=0;//电机停止时间
Motor_StopTime= rdata[2];
Motor_StopTime<<=8;//
Motor_StopTime+=rdata[3];
	
	
//unsigned int KnifeDownTime=0;//下刀时间
KnifeDownTime= rdata[4];
KnifeDownTime<<=8;//
KnifeDownTime+=rdata[5];
	
//	unsigned char CutOpt_Flag=0;//裁切优化 《开关》
CutOpt_Flag= rdata[6];

	
//unsigned int CutTime=0;   //优化时间  
CutTime= rdata[7];
CutTime<<=8;//
CutTime+=rdata[8];

//	unsigned int FastCut_Flag=0;  //快速裁切 《开关》
FastCut_Flag= rdata[9];	

n=0;

//unsigned int Motor_StartUpTime=0;//电机启动时间
if((Motor_StartUpTime<8)||(Motor_StartUpTime>30))
	{
	Motor_StartUpTime=15;
	n=1;	
	}
	
	//unsigned int Motor_StopTime=0;//电机停止时间
	if((Motor_StopTime<30)||(Motor_StopTime>180))
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
	
	//	unsigned char CutOpt_Flag=0;//裁切优化 《开关》
	if(CutOpt_Flag>1)//||(Motor_StartUpTime>30))
	{
	CutOpt_Flag=0;//默认关闭
	n=1;	
	}
	
	
	//unsigned int CutTime=0;   //优化时间  
	if((CutTime<1)||(CutTime>10))
	{
	CutTime=4;//默认4
	n=1;		
	}
	
	//	unsigned int FastCut_Flag=0;  //快速裁切 《开关》
	if(FastCut_Flag>1)//<8)||(Motor_StartUpTime>30))
	{
	FastCut_Flag=0;//默认关闭
	n=1;		
	}
	
	if(	n==1)
	{		
		FX_PLC_Save_Config();//保存默认
	}	
}


//************************************************************************************
void FX_Save_PressureData(int prognum)//保存对应程序的压力值
{
unsigned char wdata[2];
	

wdata[0]=FX_Plc_PressureData;
wdata[1]=FX_Plc_PressureData>>8;


	
Write_25pe_data(wdata, PRESSURE_DATA_SAVE_ADDER+((prognum-1)*4),     2);//保存压力值
}


//************************************************************************************
void FX_Save_Foot_PressureData(int prognum)//保存对应程序的压力值
{
unsigned char wdata[2];
	

wdata[0]=FX_Foot_Plc_PressureData;
wdata[1]=FX_Foot_Plc_PressureData>>8;
	
Write_25pe_data(wdata, PRESSURE_DATA_SAVE_ADDER+((prognum-1)*4)+2,     2);//保存压力值
}


//************************************************************************************
unsigned short FX_Read_PressureData(int prognum)//读取对应程序的压力值
{
Int32U add,n;
unsigned char rdata[2];
	unsigned short rdat;
add= PRESSURE_DATA_SAVE_ADDER+((prognum-1)*4);
FastRead_Datas_Start(add);
for(n=0;n<2;n++)
	{
	rdata[n]=ReadFlash_Datas();
	}
FlashChip_Dis;
rdat=rdata[1];
rdat<<=8;
rdat+=rdata[0];
return(rdat);
}


//************************************************************************************
unsigned short FX_Read_Foot_PressureData(int prognum)//读取对应程序的压力值
{
Int32U add,n;
unsigned char rdata[2];
	unsigned short rdat;
add= PRESSURE_DATA_SAVE_ADDER+((prognum-1)*4+2);
FastRead_Datas_Start(add);
for(n=0;n<2;n++)
	{
	rdata[n]=ReadFlash_Datas();
	}
FlashChip_Dis;
rdat=rdata[1];
rdat<<=8;
rdat+=rdata[0];
return(rdat);
}


unsigned int YaZhi_RunStepData=20000;  //压纸间隔数据

unsigned YaZhi_Sensor_Status=0;
unsigned char YaZhiRun_Cnt=0;



int YaZhi_Run_Data[16];
unsigned char YaZhi_Run_Enb_Flag=0;


unsigned char Plc_X_Err_Status=0;


unsigned char FX_PLC_Motor_Run_Enb_Flag=0;

unsigned int MainPower_Delay_Check_YOUT_Time=0;

void Check_FX_PLC_Motor_Run_Status(void)
{
	//if((FX_PLC_X_Status[1][2]=='1')&&(FX_PLC_X_Status[1][3]=='1')&&(FX_PLC_X_Status[1][6]=='1')&&(FX_PLC_X_Status[1][7]=='1'))	
if((FX_PLC_X_Status[1][6]=='1')&&(FX_PLC_X_Status[1][7]=='1'))	
		{			
			
			if(MainPower_Status>0)//延时1秒后再检查Y有无输出
						{
							if(MainPower_Delay_Check_YOUT_Time<1000)
								MainPower_Delay_Check_YOUT_Time++;
							else
							{
							if(FX_PLC_Y_Status[0][0]==PLC_CONTACT_OFF)//判断下Y20 输出，如果没有，关闭已打开图标
								{//停目状态	
								if(App_FX_Plc_Force_Process("OFF",M100)==0)
											{
											if(App_FX_Plc_Force_Process("ON",M101)==0)
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
						if(App_FX_Plc_Force_Process("OFF",M100)==0)
									{
									if(App_FX_Plc_Force_Process("ON",M101)==0)
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



void YaZhi_Run_Check_Enter(void)
{
if(YaZhi_Process_Flag==0)
	{
	if(YaZhi_Run_Enb_Flag==1)
		{			
		if((FX_PLC_X_Status[1][0]=='1')&&(FX_PLC_X_Status[1][1]=='1'))//判断双手
					{						
					YaZhi_Process();	//while(1)
					}			
		}
	}
else
		{
			App_Plc_Check_GuangDian();
		}
}


//每次到位时进入

void YaZhi_CheckData(void)	
{
	int i;
	char strr[16];
	KNIFE_DATA Knife_datas;
	
	if(YaZhi_Process_Flag==0) //已进入，退出
	{	
	for(i=0;i<16;i++)
		YaZhi_Run_Data[i]=-1;

//////	sprintf(strr,"%d",Knife_order);
//////	Printf24(strr,1000,50,RED_COLOR,1,cpGui_ColorChange(PLC_HINT_DIS_BAK_COLOR));
	GetOneKnife_datas(Pro_data.pro_num, Knife_order , (pInt8U)&Knife_datas);//取出一刀 数据

//	sprintf(strr,"%d",Knife_datas.k_flag);
//	Printf24(strr,950,50,RED_COLOR,1,cpGui_ColorChange(PLC_HINT_DIS_BAK_COLOR));
	
if((Knife_datas.k_flag&0xf)==PRESS_FLAG)
		{
		if(Knife_datas.size<(YaZhi_RunStepData+8000))//超出极限
				{
				YaZhi_Run_Enb_Flag=0;
				return;
				}

		i=0;
		while(1)
		{
		Knife_datas.size-=	YaZhi_RunStepData;
			YaZhi_Run_Data[i++]=Knife_datas.size;
		if(Knife_datas.size<(YaZhi_RunStepData+8000))//超出极限
			break;
		}
			YaZhi_Run_Enb_Flag=1;
		
		if(FX_Plc_EnbLiZhi_Flag==1)
							FX_Plc_EnbLiZhi_Flag=0;		
		}
	else
		{
		YaZhi_Run_Enb_Flag=0;
			
		if((Knife_datas.k_flag&0xf)==SORT_FLAG)
				{
				FX_Plc_EnbLiZhi_Flag=1;
				}			
		else
				FX_Plc_EnbLiZhi_Flag=0;		
		}
		
									
//////					{
//////					BellOn_Enb();
//////					}
	//	}
	}
else
		{
			
		YaZhi_Process();
		if(YaZhi_Run_Data[YaZhiRun_Cnt]==-1)
				{//最后一步运行完毕，退出
					YaZhiRun_Cnt=0;
					
					if(App_FX_Plc_Force_Process("OFF",M305)==0)//退出关闭 M305
									{//退出时断开M305
									
										
									}
									
					CurrentArea_recover1(YAZHI_PROCESS_WIN_X,YAZHI_PROCESS_WIN_Y, YAZHI_PROCESS_WIN_WIDE,YAZHI_PROCESS_WIN_HIGH);
					YaZhi_Process_Flag=0;		
					AutoRun_AutoPush_exec();  // 自动 循环运行
				}
		else
				{
				if(GuangDian_Flag==1)
					{						
					if(App_FX_Plc_Force_Process("OFF",M305)==0)//M 305闭合
								 {
									if(App_FX_Plc_Force_Process("ON",M304)==0)//M 305闭合
													{
														
														
													}
								 }		
					GuangDian_Flag=0;								 
					}
				else
					{						
					if(App_FX_Plc_Force_Process("ON",M305)==0)//M 305闭合
								 {
									 
								 }
								 
					}					
				}						
		}
}



void App_Plc_Check_GuangDian(void)
{
if((FX_PLC_X_Status[0][7]=='0'))
			{		
			GuangDian_Flag=1;
			}						
		
}





unsigned char X05_Sensor_Status=0;

unsigned char OptimizeCut_X05_CYCLE_OK_Flag=0;
unsigned char OptimizeCut_X05_CYCLE_DelayTime=0;

void OptimizeCut_X05_RunCheck(void)
{
if((WorkMode == AUTO_MODE)&&(OptimizeCut_Enb_Flag==1))
		{
		switch(X05_Sensor_Status)
				{
				case 0:
				if(FX_PLC_X_Status[0][5]=='0')
							{
							if(Run_flag==0)
							{
								X05_Sensor_Status++;
							}
							}
				break;
				case 1:
							if(FX_PLC_X_Status[0][5]!='0')
							{
								X05_Sensor_Status++;
								OptimizeCut_X05_CYCLE_DelayTime=0;
							}
					break;
				case 2:
							if(FX_PLC_X_Status[0][5]=='0')
							{//一个周期完成
								if(OptimizeCut_X05_CYCLE_OK_Flag==0)
								{//未置位有效
									OptimizeCut_X05_CYCLE_DelayTime++;
									if(OptimizeCut_X05_CYCLE_DelayTime>=30)
									{
									OptimizeCut_X05_CYCLE_DelayTime=0;
									OptimizeCut_X05_CYCLE_OK_Flag=1;
									X05_Sensor_Status=0;
									}
								}

							}
					break;
							//	X05_Sensor_Status=0;

				}
		}
else
		{
			X05_Sensor_Status=0;
			OptimizeCut_X05_CYCLE_OK_Flag=0;
		}
}


unsigned char YaZhiMotorRun_Flag=0;


void YaZhi_Process_RunCheck(void)
{
	
		if(YaZhi_Process_Flag==0)
			{
				YaZhi_Sensor_Status=0;
			//Printf24("0",950,50,RED_COLOR,1,cpGui_ColorChange(PLC_HINT_DIS_BAK_COLOR));
		//	YaZhi_Process_RunCheck();	//运行检测				
			}
//	Printf24("0",950,50,RED_COLOR,1,cpGui_ColorChange(PLC_HINT_DIS_BAK_COLOR));
switch(YaZhi_Sensor_Status)
		{
		case 0:
	//						Printf24("1",950,50,RED_COLOR,1,cpGui_ColorChange(PLC_HINT_DIS_BAK_COLOR));
		#ifdef FX_PLC
				  if(FX_PLC_YaZhi_Status==0) //3
	    {
				if(Run_flag==0)
					{
					if(YaZhiMotorRun_Flag==1)
						YaZhiMotorRun_Flag=0;
					YaZhi_Sensor_Status++;	
					}
			}	
		#else
		
		  if(OIN3_PIN==0) //3
	    {
				if(Run_flag==0)
					{
					YaZhi_Sensor_Status++;	
					}
			}				
		#endif
		
				break;
		case 1:
	//			Printf24("2",950,50,RED_COLOR,1,cpGui_ColorChange(PLC_HINT_DIS_BAK_COLOR));		
		#ifdef FX_PLC
			//	  if(FX_PLC_YaZhi_Status==0) //3
		  if(FX_PLC_YaZhi_Status!=0) //3
	    {
			YaZhi_Sensor_Status++;	
			}		
		#else		
		  if(OIN3_PIN!=0) //3
	    {
			YaZhi_Sensor_Status++;	
			}		
		#endif			
			break;
		case 2:
		//					Printf24("3",950,50,RED_COLOR,1,cpGui_ColorChange(PLC_HINT_DIS_BAK_COLOR));
		#ifdef FX_PLC
		 if(FX_PLC_YaZhi_Status==0) //3
	    {//一个周期
					//YaZhi_Sensor_Status++;	
			if(YaZhi_Run_Data[YaZhiRun_Cnt]!=-1)
				{
					
					YaZhiMotorRun_Flag=1;//压纸运行标志位 有效
					
					
				if(App_FX_Plc_Force_Process("OFF",M303)==0)//M303关闭
										{

										}											
					
				if(App_FX_Plc_Force_Process("OFF",M304)==0)// 运行时关闭 M304
								 {
									 
								 }
								 
				if(App_FX_Plc_Force_Process("OFF",M305)==0)// 运行时关闭 M305
								 {
									 
								 }
								 
			//	Printf24("3",950,50,RED_COLOR,1,cpGui_ColorChange(PLC_HINT_DIS_BAK_COLOR));
				YaZhi_MotorRun(YaZhi_Run_Data[YaZhiRun_Cnt]);
					GuangDian_Flag=0;
											Run_flag=1;
								 App_FX_PLC_LiZhi_MotorRunStop();//判断下理纸，关
											RunStop_flag=0;
											InTargetPosit_flag=0;	//目标位置
											OneCutRoutine_flag=0; // 清 裁切 循环标志
											AutoCutStart_flag=0;
											AirOffOK_flag=0;
											PressUp_flag=0;
											PressDown_flag=0;					
				YaZhiRun_Cnt++;
				}
			YaZhi_Sensor_Status=0;
			}	
		#else
		
		  if(OIN3_PIN==0) //3
	    {//一个周期
					//YaZhi_Sensor_Status++;	
			if(YaZhi_Run_Data[YaZhiRun_Cnt]!=-1)
				{
					YaZhiMotorRun_Flag=1;
					
					if(App_FX_Plc_Force_Process("OFF",M303)==0)// 运行时关闭 M304
								 {
								 }
					
				if(App_FX_Plc_Force_Process("OFF",M304)==0)// 运行时关闭 M304
								 {
									 
								 }
					
								 
				if(App_FX_Plc_Force_Process("OFF",M305)==0)// 运行时关闭 M305
								 {
									 
								 }
								 
			//	Printf24("3",950,50,RED_COLOR,1,cpGui_ColorChange(PLC_HINT_DIS_BAK_COLOR));
				YaZhi_MotorRun(YaZhi_Run_Data[YaZhiRun_Cnt]);
					GuangDian_Flag=0;
											Run_flag=1;
											App_FX_PLC_LiZhi_MotorRunStop();//判断下理纸，关
											RunStop_flag=0;
											InTargetPosit_flag=0;	//目标位置
											OneCutRoutine_flag=0; // 清 裁切 循环标志
											AutoCutStart_flag=0;
											AirOffOK_flag=0;
											PressUp_flag=0;
											PressDown_flag=0;					
				YaZhiRun_Cnt++;
				}
			YaZhi_Sensor_Status=0;
			}			
			#endif

			break;	
		}
}


void YaZhi_MotorRun(Int32U vbcd)
{
Int32U tempqianjin1;    
Int32U temphoutui1;    
if(vbcd<CurrentSize)
	{ 
	tempqianjin1=(CurrentSize-vbcd)*2;

    rollsteps=tempqianjin1-yushu;
    qianjin=1;
    houtui=0;  
////////	
////////	RLOUT1_ON; RLOUT1_1_ON;   // 允许裁切断开
////////#ifdef FX_PLC
////////	FX_Plc_EnbCut_Flag=1;
////////#endif		
////////	AutoPress_Stop();	//断 自动压，允许压 20191108
////////	EnblePress_Stop();
////////	AirSwitch_Work();// 气阀闭合
////////	CutPermit_flag=0;
	}  
else if(vbcd>CurrentSize)
    {
	 temphoutui1=(vbcd-CurrentSize)*2;

	 rollsteps=temphoutui1+yushu;
	 houtui=1;
	 qianjin=0;
	 
//////////	RLOUT1_ON;RLOUT1_1_ON;    // 允许裁切断开
//////////#ifdef FX_PLC
//////////	FX_Plc_EnbCut_Flag=1;
//////////#endif			
//////////	AutoPress_Stop();	//断 自动压，允许压 20191108
//////////	EnblePress_Stop();
//////////	AirSwitch_Work();// 气阀闭合
//////////	CutPermit_flag=0; 
    }  
else
    {
	qianjin=0;
    houtui=0;
	}   
          
if(houtui==1)
    {     
	step_ground=11; 
	rollsteps=rollsteps+2400;    
        
	if(rollsteps>3000)
		{
	   speedup_steps=100;  
	   speedup_steps_B=speedup_steps;
	   rollsteps=(rollsteps- speedup_steps*22)+2;
	   status=1;      
		
		}
	else if(rollsteps>2000&&rollsteps<3001)
		{  
		speedup_steps=45; 
		speedup_steps_B=speedup_steps;
		rollsteps=(rollsteps- speedup_steps*22)+2;
		status=1;  
		  
		
		}                                                               
	else if(rollsteps>1000&&rollsteps<2001)
		{
	   speedup_steps=30; 
	   speedup_steps_B=speedup_steps;
	   rollsteps=(rollsteps- speedup_steps*22)+2;
	   status=1;  
						
		} 
	else if(rollsteps>500&&rollsteps<1001)
		{
	   speedup_steps=20;
	   speedup_steps_B=speedup_steps;
	   rollsteps=(rollsteps- speedup_steps*22)+2;
	   status=1;  
					
		}   
	else  if(rollsteps>100&&rollsteps<501)
		{
		speedup_steps=4;   
		speedup_steps_B=speedup_steps;
		rollsteps=(rollsteps- speedup_steps*22)+2;
		status=1;  
			
		}
	else
		{  
		   status=9;    
		   step_add=1;  
		   
	 //       speedup_steps=1;
		}
          
	flagtingji8=0;
	flagyunxing8=1;
	step_add=1;     

	Timer1Init();
	Timer0Disable();
    }  
            
            
if(qianjin==1)//----------------------------------------------------------
    {
     step_ground=11;  
  
	if(rollsteps>3000)
		{
	   speedup_steps=100;  
	   speedup_steps_B=speedup_steps;
	   rollsteps=(rollsteps- speedup_steps*22)+2;
	   status=1;  
	  
		}
	else if(rollsteps>2000&&rollsteps<3001)
		{
		speedup_steps=45;
		speedup_steps_B=speedup_steps;
		rollsteps=(rollsteps- speedup_steps*22)+2;
		status=1;   
	   
		}
	else if(rollsteps>1000&&rollsteps<2001)
		{
	   speedup_steps=30;
	   speedup_steps_B=speedup_steps;
	   rollsteps=(rollsteps- speedup_steps*22)+2;
	   status=1;   
				
		} 
	else if(rollsteps>500&&rollsteps<1001)
		{
	   speedup_steps=20;
	   speedup_steps_B=speedup_steps;
	   rollsteps=(rollsteps- speedup_steps*22)+2;
	   status=1;   
				  
		}   
	else  if(rollsteps>100&&rollsteps<501)
		{
		speedup_steps=4;  
		speedup_steps_B=speedup_steps;
		rollsteps=(rollsteps- speedup_steps*22)+2;
		status=1;  
		 
		}
	else
		{    
		status=9; 
		step_add=1;  
		 
	 //       speedup_steps=1;
		}
	
	 flagtingji8=0;     
	 flagyunxing8=1;
	 step_add=1;     

	Timer1Init();
	Timer0Disable();
	
	}
 //A6CoderEqual_flag=0;
    
}	
	



void YaZhi_Instert(void)
{
InputSize=10000;
Knife_order++;
if(Knife_order<=OnePro_head.pro_knifeSUM)
										{
										if(OnePro_head.pro_knifeSUM<MAX_Knife)
											{
											OnePro_head.pro_knifeSUM++;
											InsertOneKnife(Pro_data.pro_num, Knife_order);
											pKnife_data=(pInt8U)&OneKnife_data;
											// GetOneKnife_datas(Knife_order, pKnife_data);//
											OneKnife_data.size=InputSize;  //尺寸修改
											OneKnife_data.k_flag=NOAIR_FLAG|FLAG_FLAG;//标记初始待设定
											SaveOneKnife_datas(Pro_data.pro_num, Knife_order , pKnife_data);//保存一刀数据
											//------------------//下一刀 清除刀 标记
											if((Knife_order+1)<=OnePro_head.pro_knifeSUM)
												{
												GetOneKnife_datas(Pro_data.pro_num, Knife_order+1, pKnife_data);//下一刀
												if((OneKnife_data.k_flag&0xf)==KNIFE_FLAG) //刀 标志
													{
													if(OneKnife_data.size>InputSize)
														{
														OneKnife_data.k_flag&=0xf0;	//清除刀 标记
														OneKnife_data.k_flag|= FLAG_FLAG;//标记待设定
														SaveOneKnife_datas(Pro_data.pro_num, Knife_order+1 , pKnife_data);//保存一刀数据
														}
													}
												}
											//-----显示
											//KnifeSize_dis(cursor_row,InputSize);//尺寸
											StepNum_dis(OnePro_head.pro_knifeSUM,Knife_order);//步骤更新
											Size_1page_dis(Knife_order,cursor_row);
											}
										else  //程序数据已满，不可插入
											{
											PromptDis_flag=0;
											GLCD_SetWindow_Fill( REMIND_WINDOW_X, REMIND_WINDOW_Y, REMIND_WINDOW_X+REMIND_LENGTH, REMIND_WINDOW_Y+30, 0xffff, 0xffff);//提示框
											switch(Language)
												{
												case CHN_HAN:
													Printf24("程序刀数已满,不可插入!",REMIND_WINDOW_X,REMIND_WINDOW_Y+5,RED_COLOR,0,0xffff);
													break;
												case ENGLISH:
													Printf24("Data full,no inserting!",REMIND_WINDOW_X,REMIND_WINDOW_Y+5,RED_COLOR,0,0xffff);
													break;
												case INDONSIA:	//印尼
													Printf16("Penuh, tidak dapat dimasukkan",REMIND_WINDOW_X,REMIND_WINDOW_Y+5,RED_COLOR,0,0xffff);
													break;
												case PORTUGAL:	//葡萄牙
													Printf16("Dados estácheio, n?o pode entrar",REMIND_WINDOW_X,REMIND_WINDOW_Y+5,RED_COLOR,0,0xffff);
													ASCII_Printf("a",ASCII16_MODE,8,16,PUTAO_ZK16,REMIND_WINDOW_X+8*19,REMIND_WINDOW_Y+5,RED_COLOR,0xffff);
													break;
												case SPANISH: //西班牙
													Printf16("No puede insertar datos se ha llenado",REMIND_WINDOW_X,REMIND_WINDOW_Y+5,RED_COLOR,0,0xffff);
													break;
												}
											}
										}
}

