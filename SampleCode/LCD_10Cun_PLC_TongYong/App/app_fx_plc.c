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
#include "app_modbus_fxplc.h"


#include "word_lib.h"


unsigned char  GuangDian_Flag=0;



unsigned short FX_Plc_PressureData=0;
unsigned short FX_Plc_OldPressureData=0;

unsigned char App_FX_Plc_CommBuf[32];


unsigned char FX_Plc_X_Status_Byte[16]={'0',0};  //
unsigned char FX_Plc_Y_Status_Byte[16]={'0',0};

unsigned char FX_Plc_M_Status_Byte[16]={'0',0};


unsigned char FX_PLC_X_StatusBuf[4];
unsigned char FX_PLC_Y_StatusBuf[4];
unsigned char FX_PLC_M_StatusBuf[4];


char FX_PLC_X_Status[4][8];
char FX_PLC_Y_Status[4][8];

char FX_PLC_M_Status[4][8];

char FX_Plc_X4_Status='0';
char FX_Plc_X5_Status='0';
char FX_Plc_X12_Status='0';


unsigned short FX_Plc_DT20_Data=10;   //下刀时间  2-100 对应0.2秒 -10秒
unsigned short FX_Plc_DT10_Data=120;  //星三角启动  80-200  对应 8秒-20秒

unsigned char App_FX_Plc_PollTime=0;
unsigned char App_Fx_Plc_Poll_SetpCnt=0;

unsigned char FX_PLC_PowerOn_Init_Flag=1;

unsigned char FX_Plc_PressureData_Download_Flag=0;

unsigned char FX_Plc_EnbCut_Flag=0;
unsigned char FX_Plc_EnbAutoCut_Flag=0;


		
unsigned char FX_Plc_EnbAutoCut_Send_Flag=0;


unsigned char FX_Plc_EnbYaZhi_Flag=0;

unsigned char FX_Plc_EnbQiFa_Flag=0;
unsigned char FX_Plc_EnbQiFa_Flag_Temp=0xff;
unsigned char FX_Plc_EnbLiZhi_Flag=0;


int 	FX_Plc_Connect_TimeOut=0;

unsigned char FX_Plc_Comm_TimeOut_Flag=0;

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
		
		case 'R':
		//	unsigned char hex;
		  if(Fx_Plc_RecvBuf[2]>'9')
				YaZhiYaLi_Data=Fx_Plc_RecvBuf[2]-0x37;
			else
				YaZhiYaLi_Data=Fx_Plc_RecvBuf[2]-0x30;
			
			YaZhiYaLi_Data<<=4;
			
			if(Fx_Plc_RecvBuf[3]>'9')
				YaZhiYaLi_Data+=Fx_Plc_RecvBuf[3]-0x37;
			else
				YaZhiYaLi_Data+=Fx_Plc_RecvBuf[3]-0x30;
			
			YaZhiYaLi_Data<<=4;
			
		 if(Fx_Plc_RecvBuf[0]>'9')
				YaZhiYaLi_Data+=Fx_Plc_RecvBuf[0]-0x37;
			else
				YaZhiYaLi_Data+=Fx_Plc_RecvBuf[0]-0x30;
			
			YaZhiYaLi_Data<<=4;
					  if(Fx_Plc_RecvBuf[1]>'9')
				YaZhiYaLi_Data+=Fx_Plc_RecvBuf[1]-0x37;
			else
				YaZhiYaLi_Data+=Fx_Plc_RecvBuf[1]-0x30;
			
			break;	
				
		case ' '://  ACK \NAK  返回
			
			break;
		
		case 'M'://读M 寄存器		
		
			memcpy(FX_Plc_M_Status_Byte,Fx_Plc_RecvBuf,16);  //			
		
			for(i=0;i<4;i++)
				{
				if(FX_Plc_M_Status_Byte[i*2]>'9')
					x_status=FX_Plc_M_Status_Byte[i*2]-0x37;
				else
					x_status=FX_Plc_M_Status_Byte[i*2]-0x30;
				x_status<<=4;
			
				if(FX_Plc_M_Status_Byte[i*2+1]>'9')
					x_status+=FX_Plc_M_Status_Byte[i*2+1]-0x37;
				else
					x_status+=FX_Plc_M_Status_Byte[i*2+1]-0x30;	
			
				FX_PLC_M_StatusBuf[i]=x_status;
				
				for(n=0;n<8;n++)
					{
						if(x_status&0x01)
							FX_PLC_M_Status[i][n]='1';
						else
							FX_PLC_M_Status[i][n]='0';
						x_status>>=1;
					}
				}	
			break;
		}		
}


void App_FX_Plc_Init(void)
{
	
	
	
App_FX_Plc_LoadPressureData();

FX_Plc_Comm_Status=' ';
FX_Plc_Comm_TimeOut=0;
}



void App_FX_Plc_LoadPressureData(void)
{
ProData_ProNum_Old=Pro_data.pro_num;
	
FX_Plc_PressureData=FX_Read_PressureData(Pro_data.pro_num);//读取压力值

if((FX_Plc_PressureData<100)||(FX_Plc_PressureData>1500))
		{//非法数据，置初值
		FX_Plc_PressureData=750;	
		FX_Save_PressureData(Pro_data.pro_num);				
		}	
		
FX_Plc_OldPressureData=FX_Plc_PressureData;		
FX_Plc_PressureData_Download_Flag=1;//更新一下压力值		
	
}


void App_FX_Plc_Run(void)
{
char strbuf[16];
////////APP_FX_Plc_Poll_Exec();
////////	
////////App_FX_Plc_Pressure_AutoSave();
////////	
////////if(ProData_ProNum_Old!=Pro_data.pro_num)
////////{
////////	App_FX_Plc_LoadPressureData();//重新载入压力数据
////////	
////////}
////////	
	


////////PLC_FX_Hint_DisPlay();//加入信息提示
////////	
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
	
	
}


int FX_Plc_Comm_TimeOut_RstTime=0;
void App_FX_Plc_TimeOut_Exec(void)
{

	
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
		if(FX_Plc_PressureData>=100)
				{			
				FX_Save_PressureData(Pro_data.pro_num);//保存一下新数据
				FX_Plc_OldPressureData=FX_Plc_PressureData;		
					
				FX_Plc_PressureData_Download_Flag=1;
				}		
		else
				{//数据不合法
					
					
				}
		}
}



//************************************************************************************
void FX_Save_PressureData(int prognum)//保存对应程序的压力值
{
unsigned char wdata[2];
	

	wdata[0]=FX_Plc_PressureData;
	wdata[1]=FX_Plc_PressureData>>8;
Write_25pe_data(wdata, PRESSURE_DATA_SAVE_ADDER+((prognum-1)*2),     2);//保存压力值
}


//************************************************************************************
unsigned short FX_Read_PressureData(int prognum)//读取对应程序的压力值
{
Int32U add,n;
unsigned char rdata[2];
	unsigned short rdat;
add= PRESSURE_DATA_SAVE_ADDER+((prognum-1)*2);
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


unsigned int YaZhi_RunStepData=20000;  //压纸音隔数据

unsigned YaZhi_Sensor_Status=0;
unsigned char YaZhiRun_Cnt=0;



int YaZhi_Run_Data[16];
unsigned char YaZhi_Run_Enb_Flag=0;


unsigned char Plc_X_Err_Status=1;


void YaZhi_Run_Check_Enter(void)
{
if(YaZhi_Process_Flag==0)
	{
	if(YaZhi_Run_Enb_Flag==1)
		{			
		if((FX_PLC_X_Status[0][6]=='1')&&(FX_PLC_X_Status[0][7]=='1'))
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
			
		FX_Plc_EnbYaZhi_Flag=1;
			
////////		if(Knife_datas.size<(YaZhi_RunStepData+8000))//超出极限
////////				{
////////				YaZhi_Run_Enb_Flag=0;
////////				return;
////////				}

////////		i=0;
////////		while(1)
////////		{
////////		Knife_datas.size-=	YaZhi_RunStepData;
////////			YaZhi_Run_Data[i++]=Knife_datas.size;
////////		if(Knife_datas.size<(YaZhi_RunStepData+8000))//超出极限
////////			break;
////////		}
////////			YaZhi_Run_Enb_Flag=1;
		
		if(FX_Plc_EnbLiZhi_Flag==1)
							FX_Plc_EnbLiZhi_Flag=0;		
		}
	else
		{
		FX_Plc_EnbYaZhi_Flag=0;
			
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
if((FX_PLC_X_Status[1][0]=='0'))
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
			//		if(FX_PLC_X_Status[0][5]=='0') 
				if(FX_PLC_M_Status[0][2]=='0') //单次X005 已改成M370	
							{
							if(Run_flag==0)
							{
								X05_Sensor_Status++;
							}
							}
				break;
				case 1:
					//if(FX_PLC_X_Status[0][5]!='0')
							if(FX_PLC_M_Status[0][2]!='0')//单次X005 已改成M370	
							{
								X05_Sensor_Status++;
								OptimizeCut_X05_CYCLE_DelayTime=0;
							}
					break;
				case 2:
					//if(FX_PLC_X_Status[0][5]=='0')
							if(FX_PLC_M_Status[0][2]=='0')//单次X005 已改成M370	
							{//一个周期完成
								if(OptimizeCut_X05_CYCLE_OK_Flag==0)
								{//未置位有效
									OptimizeCut_X05_CYCLE_DelayTime++;
									if(OptimizeCut_X05_CYCLE_DelayTime>=100)
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
		  if(OIN3_PIN==0) //3
	    {
				if(Run_flag==0)
					{
					YaZhi_Sensor_Status++;	
					}
			}				
				break;
		case 1:
	//			Printf24("2",950,50,RED_COLOR,1,cpGui_ColorChange(PLC_HINT_DIS_BAK_COLOR));			
		  if(OIN3_PIN!=0) //3
	    {
			YaZhi_Sensor_Status++;	
			}					
			break;
		case 2:
		//					Printf24("3",950,50,RED_COLOR,1,cpGui_ColorChange(PLC_HINT_DIS_BAK_COLOR));
		  if(OIN3_PIN==0) //3
	    {//一个周期
					//YaZhi_Sensor_Status++;	
			if(YaZhi_Run_Data[YaZhiRun_Cnt]!=-1)
				{
					
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
////////	//RLOUT1_ON; //RLOUT1_ON;   // 允许裁切断开
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
	 
//////////	//RLOUT1_ON;//RLOUT1_ON;    // 允许裁切断开
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

