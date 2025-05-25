#include "app_modbus.h"


#include "modbus_972.h"


#include "modbus_972.h"
//#include "modbus.h"
#include "uart_config.h"

#include "pic_exec.h"

#include "app_modbus.h"

#include "string.h"

#include "app_modbus_motion.h"

#include "app_fx_plc.h"
#include "app_modbus_fxplc.h"

#include "optimize_cut.h"

#include "app_modbus_972.h"

static unsigned char App_ModBus_Task_Cnt=0;
static unsigned int App_ModBus_TaskTime=0;


unsigned char App_Modbus_Send_Return_Flag=0;


//char App_ModBus_Status=' ';


unsigned short D_Area_Array[128];


unsigned int App_ModBus_DataArea_Address=0;

int App_Modbus_EnbInit_Flag=1;

int App_ModBus_Send_Time=0;


void App_ModBus_Task_Test(void)
{
	
		//		RLOUT5_ON;
			ModBus_SendFrame(PLC_ADDER,MODBUS_READ_CMD,PLC_X_BASE_ADDER,0x04);//读取4个字的数据		
			ModBus_Queue_LoadBuf(Modbus_Sendbuf,'X',8);


			App_ModBus_Status='Y';//读 Y		//大写是读，小写是写
			ModBus_SendFrame(PLC_ADDER,MODBUS_READ_CMD,PLC_Y_BASE_ADDER,0x04);//读取4个字的数据
		ModBus_Queue_LoadBuf(Modbus_Sendbuf,'Y',8);

			App_ModBus_Status='M';//读 M		//大写是读，小写是写
			ModBus_SendFrame(PLC_ADDER,MODBUS_READ_CMD,PLC_M_BASE_ADDER,0x04);//读取4个字的数据
			ModBus_Queue_LoadBuf(Modbus_Sendbuf,'M',8);
		
	
	
}


unsigned char App_Modbus_Task_Ready_Flag=0;
unsigned char App_ModBus_Init_Flag=0;

unsigned short Stop_0x800C_Data=0;
unsigned short Stop_0x800D_Data=0;

unsigned char D70_Write_Flag=0;
unsigned short D70_Data=0;

void App_ModBus_Task_Run(void)
{
	
	return;
	
//ModBus_Start_SendFrame();	
	if(App_Modbus_EnbInit_Flag==1)
		return;
	
	
App_ModBus_TaskTime++;
if(App_ModBus_TaskTime>=25)
		{	
		App_ModBus_TaskTime=0;
		App_ModBus_Task_Cnt++;
		}
else
	{
		if(App_ModBus_TaskTime<10)
			{
			App_Modbus_Task_Ready_Flag=0;				
			}
		else
			{
			App_Modbus_Task_Ready_Flag=1;								
			}
			
////	if(App_Modbus_Send_Return_Flag==1)//不间断发送
////		{
////		App_Modbus_Send();//检查一下发送任务。
////			
////		}
		
		return;
	}
	
switch(App_ModBus_Task_Cnt)
		{			
		case 1:		
			if(APP_MODBUS_PLC==1)// APP_MODUBS_PLC 为0 时，使用板载IO
			{
			if(FX_PLC_PowerOn_Init_Flag==1)
					{   //D10   星三角启动 时间
					App_Modbus_FXPlc_D_Write(10,Plc_DT_Data_t[0]);		
					App_Modbus_FXPlc_D_Write(20,Plc_DT_Data_t[1]);		
					Optimize_Cut_DelayTime_DownLoad_Flag=1;//发送一次优化裁切延时时间					
					FX_PLC_PowerOn_Init_Flag=0;							
					}	
			else
			{//写入D70数据
				if(D70_Write_Flag==1)
				{
					D70_Write_Flag=0;
					App_Modbus_FXPlc_D_Write(70,D70_Data);	
				}
				
			}
		}
			else				
			{
			App_ModBus_Status='C';//读伺服 多圈		//大写是读，小写是写
			ModBus_SendFrame(0x01,MODBUS_READ_CMD,0x8011,0x02);//读取4个字的数据
			ModBus_Queue_LoadBuf(Modbus_Sendbuf,'C',8);		
				
			}
		break;

		case 2:		//查询PLC X 状态
			if(APP_MODBUS_PLC==1)// APP_MODUBS_PLC 为0 时，使用板载IO
				{
				App_ModBus_Status='X';//读 X	//大写是读，小写是写		
				ModBus_SendFrame(PLC_ADDER,MODBUS_READ_CMD,PLC_X_BASE_ADDER,0x04);//读取4个字的数据		
				ModBus_Queue_LoadBuf(Modbus_Sendbuf,'X',8);
				}
			else
				{
				App_ModBus_Status='p';//读伺服 当前脉冲		//大写是读，小写是写
				ModBus_SendFrame(0x01,MODBUS_READ_CMD,0x0511,0x02);//读取4个字的数据
				ModBus_Queue_LoadBuf(Modbus_Sendbuf,'p',8);	
				}
			break;
		case 3:
			if(APP_MODBUS_PLC==1)// APP_MODUBS_PLC 为0 时，使用板载IO
				{			
			App_ModBus_Status='Y';//读 Y		//大写是读，小写是写
			ModBus_SendFrame(PLC_ADDER,MODBUS_READ_CMD,PLC_Y_BASE_ADDER,0x04);//读取4个字的数据
		ModBus_Queue_LoadBuf(Modbus_Sendbuf,'Y',8);
				}
			else
				{
				App_ModBus_Status='s';//读伺服 状态		
				ModBus_SendFrame(0x01,MODBUS_READ_CMD,0x514,0x02);//读取4个字的数据
				ModBus_Queue_LoadBuf(Modbus_Sendbuf,'s',8);	
				}
			break;
		case 4:
			if(APP_MODBUS_PLC==1)// APP_MODUBS_PLC 为0 时，使用板载IO
				{	
					
			App_ModBus_Status='C';//读伺服 多圈		//大写是读，小写是写
			ModBus_SendFrame(0x01,MODBUS_READ_CMD,0x8011,0x02);//读取4个字的数据
			ModBus_Queue_LoadBuf(Modbus_Sendbuf,'C',8);		
				}
			else
			{
				
					if(App_ModBus_Init_Flag==0)
				{//清伺服当前脉冲
				App_ModBus_Init_Flag=1;
					
//					ElectricWheelOn_flag=0;//手轮模式为0
					
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
					
					
//////				//、、1：位置手轮模式：先设置地址0x1095=0x80，再设置0x1000=0x10，手轮有效，内部位置无效。
//////					
//////				ModBus_SendFrame(0x01,0x06,0x1095,0x80);//位置手轮模式：先设置地址0x1095=0x80，
//////				ModBus_Queue_LoadBuf(Modbus_Sendbuf,'r',8);
//////					
//////				ModBus_SendFrame(0x01,0x06,0x1000,0x10);//再设置0x1000=0x10，手轮有效，内部位置无效。
//////				ModBus_Queue_LoadBuf(Modbus_Sendbuf,'r',8);


					
				ModBus_SendFrame(0x01,0x06,0x0511,0);//写低16位			
				ModBus_Queue_LoadBuf(Modbus_Sendbuf,'q',8);
			
				ModBus_SendFrame(0x01,0x06,0x0512,0);//写高16位
				ModBus_Queue_LoadBuf(Modbus_Sendbuf,'q',8);
		
											
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
				
			}
			
			break;
		case 5://读多圈位置
			if(APP_MODBUS_PLC==1)// APP_MODUBS_PLC 为0 时，使用板载IO
				{				
			App_ModBus_Status='p';//读伺服 当前脉冲		//大写是读，小写是写
			ModBus_SendFrame(0x01,MODBUS_READ_CMD,0x0511,0x02);//读取4个字的数据
			ModBus_Queue_LoadBuf(Modbus_Sendbuf,'p',8);	
				}
			else
				
			{
			App_ModBus_Status='s';//读伺服 状态		
			ModBus_SendFrame(0x01,MODBUS_READ_CMD,0x514,0x02);//读取4个字的数据
			ModBus_Queue_LoadBuf(Modbus_Sendbuf,'s',8);					
				
			}
			break;
		

		case 6:
						if(APP_MODBUS_PLC==1)// APP_MODUBS_PLC 为0 时，使用板载IO
				{
	if(App_ModBus_Init_Flag==0)
				{//清伺服当前脉冲
				App_ModBus_Init_Flag=1;
					
			//		ElectricWheelOn_flag=0;//手轮模式为0
					
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
					
					
//////				//、、1：位置手轮模式：先设置地址0x1095=0x80，再设置0x1000=0x10，手轮有效，内部位置无效。
//////					
//////				ModBus_SendFrame(0x01,0x06,0x1095,0x80);//位置手轮模式：先设置地址0x1095=0x80，
//////				ModBus_Queue_LoadBuf(Modbus_Sendbuf,'r',8);
//////					
//////				ModBus_SendFrame(0x01,0x06,0x1000,0x10);//再设置0x1000=0x10，手轮有效，内部位置无效。
//////				ModBus_Queue_LoadBuf(Modbus_Sendbuf,'r',8);


					
				ModBus_SendFrame(0x01,0x06,0x0511,0);//写低16位			
				ModBus_Queue_LoadBuf(Modbus_Sendbuf,'q',8);
			
				ModBus_SendFrame(0x01,0x06,0x0512,0);//写高16位
				ModBus_Queue_LoadBuf(Modbus_Sendbuf,'q',8);
		
											
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
			}
				break;
		case 7:				
		
//////////////		//允许裁切  放在马达运行前
			if(APP_MODBUS_PLC==1)// APP_MODUBS_PLC 为0 时，使用板载IO
			{
				
			if(FX_Plc_EnbQiFa_Flag==1)
					{
					App_Modbus_FXPlc_M_CTRL_Interrupt("ON",302);												
					}
				else
					{
					App_Modbus_FXPlc_M_CTRL_Interrupt("OFF",302);								
					}
					
				if(FX_Plc_EnbLiZhi_Flag==0)
					{
					App_Modbus_FXPlc_M_CTRL_Interrupt("OFF",303);
		
					}
				else
					{
					App_Modbus_FXPlc_M_CTRL_Interrupt("ON",303);
					
					}
					
				if(OptimizeCut_Enb_Flag==0)
					{
						App_Modbus_FXPlc_M_CTRL_Interrupt("ON",210);
				//	App_FX_Plc_Force_Process("ON",M210);						
					}
				else
					{
					App_Modbus_FXPlc_M_CTRL_Interrupt("OFF",210);						
				//	App_FX_Plc_Force_Process("OFF",M210);
					}
					
				if(FastCut_Enb_Flag==0)
					{
						App_Modbus_FXPlc_M_CTRL_Interrupt("ON",230);
				//	App_FX_Plc_Force_Process("ON",M230);									
					}
				else
					{
					App_Modbus_FXPlc_M_CTRL_Interrupt("OFF",230);
					//	App_FX_Plc_Force_Process("OFF",M230);									
					}	
				}
			else
			{
				
				
			}
			break;
		case 8:
if(APP_MODBUS_PLC==1)// APP_MODUBS_PLC 为0 时，使用板载IO
			{			
				if(FX_Plc_PressureData_Download_Flag==1)
				{
					FX_Plc_PressureData_Download_Flag=0;
					
					App_Modbus_FXPlc_D_Write(300,FX_Plc_PressureData);		
					
					// Comm_FX_Plc_Write_D_Area(300,(unsigned char*)&FX_Plc_PressureData,2);	
					
				}
			}
			else
			{
				
				
			}
				break;
				
		case 9:
			
		if(APP_MODBUS_PLC==1)// APP_MODUBS_PLC 为0 时，使用板载IO
			{

			if(Optimize_Cut_DelayTime_DownLoad_Flag==1)
					{
						
						App_Modbus_FXPlc_D_Write(300,OptimizeCut_DelayTime);		
						
					//	Comm_FX_Plc_Write_D_Area(30,(unsigned char*)&OptimizeCut_DelayTime,2);			
						Optimize_Cut_DelayTime_DownLoad_Flag=0;
					}	
				}
		break;
			
		case 10:
		//	Comm_FX_Plc_Read_D_Area(90,2);
if(APP_MODBUS_PLC==1)// APP_MODUBS_PLC 为0 时，使用板载IO
			{		
			App_ModBus_Status='X';//读 X	//大写是读，小写是写		
			ModBus_SendFrame(PLC_ADDER,MODBUS_READ_CMD,90,1);//读取2个字的数据		1个16位数据
			ModBus_Queue_LoadBuf(Modbus_Sendbuf,'u',8);
			}
			else
			{
				
			}
			break;

		case 11:
		if(APP_MODBUS_PLC==1)// APP_MODUBS_PLC 为0 时，使用板载IO
				{	
					App_ModBus_Status='s';//读伺服 状态		
					ModBus_SendFrame(0x01,MODBUS_READ_CMD,0x514,0x02);//读取4个字的数据
					ModBus_Queue_LoadBuf(Modbus_Sendbuf,'s',8);	
				}
			break;
		case 12:
			
		//读取D80 状态
		if(APP_MODBUS_PLC==1)// APP_MODUBS_PLC 为0 时，使用板载IO
				{
						//	Comm_FX_Plc_Read_D_Area(80,2);
				App_ModBus_Status='D';//读 X	//大写是读，小写是写		
				App_ModBus_DataArea_Address=60;//D数据区的地址。 改为D60了。原D80　被占用了
				ModBus_SendFrame(PLC_ADDER,MODBUS_READ_CMD,60,1);//读取2个字的数据		1个16位数据
				ModBus_Queue_LoadBuf(Modbus_Sendbuf,'D',8);
				}
			else
				{	
				
				}
		
			break;	
		}
	
		if(APP_MODBUS_PLC==1)// APP_MODUBS_PLC 为0 时，使用板载IO
			{
			if(App_ModBus_Task_Cnt>=18)
				{
					App_ModBus_Task_Cnt=0;
					//		RLOUT5_OFF;
				}	
			}
		else
			{
			if(App_ModBus_Task_Cnt>=11)
				{
					App_ModBus_Task_Cnt=0;
					//		RLOUT5_OFF;
				}		
				
			}	
		
App_Modbus_Send();//检查一下发送任务。
}



#include "app_fx_plc.h"
#include "word_lib.h"

#include "plc_ext_form.h"


unsigned char Circle_UpData_Flag=0;
unsigned int App_Modbus_Servo_Status=0;

//Modbus 解码
void APP_ModBus_Decode(void)
{
int i,n;	
//	char stemp[16];
	
	unsigned char x_status;
	unsigned char IO_StatusBuf[8];
	short mcirlce_data;
	unsigned short scirlce_data;
	unsigned int tempdata;
	
	
	//App_ModBus_Status='X';
//return;
//GLCD_SetWindow_Fill( REMIND_WINDOW_X+800, REMIND_WINDOW_Y-30, REMIND_WINDOW_X+888, REMIND_WINDOW_Y-10, 0xffff, 0xffff);//提示框
switch(App_ModBus_Status)
	{

		case 'X'://读X返回
					//if((ModeBus_DataRecv_Cnt<2)&&(ModeBus_DataRecv_Cnt>8))
						{
						//	ModeBus_DataRecv_Cnt=0;
						//	return; 
						}
					
					IO_StatusBuf[0]=ModBus_DataBuf[1];
					IO_StatusBuf[1]=ModBus_DataBuf[0];
					IO_StatusBuf[2]=ModBus_DataBuf[3];
					IO_StatusBuf[3]=ModBus_DataBuf[2];

				
					for(i=0;i<4;i++)
					{
						x_status=IO_StatusBuf[i];
							for(n=0;n<8;n++)
						{
							if(x_status&0x01)
								FX_PLC_X_Status[i][n]='1';
							else
								FX_PLC_X_Status[i][n]='0';
							x_status>>=1;
						}
					}
						
					Modbus_PLC_Link_Flag=1;
					Modbus_PlcTimeOut=0;
		//			sprintf(stemp,"X %d",ModeBus_DataRecv_Cnt);		
		//			Printf24(stemp,REMIND_WINDOW_X+800,REMIND_WINDOW_Y-30,RED_COLOR,1,0xffff);
					ModeBus_DataRecv_Cnt=0;
		
					
					App_Modbus_Send_Return_Flag=1;//发送后收到有返回
					
			break;
		case 'Y'://读Y返回
					if((ModeBus_DataRecv_Cnt<2)&&(ModeBus_DataRecv_Cnt>8))
					{
						ModeBus_DataRecv_Cnt=0;
						return; 
					}
					IO_StatusBuf[0]=ModBus_DataBuf[1];
					IO_StatusBuf[1]=ModBus_DataBuf[0];
					IO_StatusBuf[2]=ModBus_DataBuf[3];
					IO_StatusBuf[3]=ModBus_DataBuf[2];

				
					for(i=0;i<ModeBus_DataRecv_Cnt/2;i++)
					{
						x_status=IO_StatusBuf[i];
							for(n=0;n<8;n++)
						{
							if(x_status&0x01)
								FX_PLC_Y_Status[i][n]='1';
							else
								FX_PLC_Y_Status[i][n]='0';
							x_status>>=1;
						}
					}
					
					Modbus_PLC_Link_Flag=1;
					Modbus_PlcTimeOut=0;
					ModeBus_DataRecv_Cnt=0;
					
					App_Modbus_Send_Return_Flag=1;//发送后收到有返回
		//							sprintf(stemp,"Y %d",ModeBus_DataRecv_Cnt);
		//				Printf24(stemp,REMIND_WINDOW_X+800,REMIND_WINDOW_Y-30,RED_COLOR,1,0xffff);
			break;
		case 'y'://写Y返回
			break;
		
		case 'u':
			
		
			tempdata=	ModBus_DataBuf[0];			
			tempdata<<=8;
			tempdata+=ModBus_DataBuf[1];
		
			YaZhiYaLi_Data=	tempdata;
		
			ModeBus_DataRecv_Cnt=0;
		
		App_Modbus_Send_Return_Flag=1;//发送后收到有返回
		
			break;
		
		case 'M'://读M返回
			break;
		case 'm'://写M返回
			break;
		case 'D'://读D返回
			tempdata=	ModBus_DataBuf[0];			
			tempdata<<=8;
			tempdata+=ModBus_DataBuf[1];
		
		//	YaZhiYaLi_Data=	tempdata;
		
					D_Area_Array[App_ModBus_DataArea_Address/10]=tempdata;

					Modbus_PlcTimeOut=0;
		//			sprintf(stemp,"X %d",ModeBus_DataRecv_Cnt);		
		//			Printf24(stemp,REMIND_WINDOW_X+800,REMIND_WINDOW_Y-30,RED_COLOR,1,0xffff);
					ModeBus_DataRecv_Cnt=0;
		
					
					App_Modbus_Send_Return_Flag=1;//发送后收到有返回
		
			//App_ModBus_DataArea_Address=0;
		
			break;
		case 'd'://写D返回
			break;
		case 'A'://写前进返回
		break;
		case 'B'://写后退返回
			break;
		case 'S'://写停止返回
			break;
		case 's'://读状态返回
			if((ModeBus_DataRecv_Cnt<2)&&(ModeBus_DataRecv_Cnt>8))
					{
						ModeBus_DataRecv_Cnt=0;
						return; 
					}
					
					
				  App_Modbus_Servo_Status=(unsigned char )ModBus_DataBuf[0];
					App_Modbus_Servo_Status<<=8;
					App_Modbus_Servo_Status+=(unsigned char )ModBus_DataBuf[1];
					
					if(App_Modbus_Servo_Status>100)
						Modbus_Servo_Err_Flag=1;
					else
						Modbus_Servo_Err_Flag=0;
//////					App_Modbus_Servo_Status<<=8;
//////					App_Modbus_Servo_Status+=(unsigned char )ModBus_DataBuf[2];
//////					App_Modbus_Servo_Status<<=8;
//////					App_Modbus_Servo_Status+=ModBus_DataBuf[3];
					
					

					
				ModeBus_DataRecv_Cnt=0;					
				App_Modbus_Send_Return_Flag=1;//发送后收到有返回
					
			break;
		case 'C'://读多圈值返回
					if((ModeBus_DataRecv_Cnt<2)&&(ModeBus_DataRecv_Cnt>8))
					{
						ModeBus_DataRecv_Cnt=0;
						return; 
					}
					IO_StatusBuf[0]=ModBus_DataBuf[1];
					IO_StatusBuf[1]=ModBus_DataBuf[0];
					IO_StatusBuf[2]=ModBus_DataBuf[3];
					IO_StatusBuf[3]=ModBus_DataBuf[2];
					
					 mcirlce_data=(unsigned char )ModBus_DataBuf[0];
					mcirlce_data<<=8;
					mcirlce_data+=(unsigned char )ModBus_DataBuf[1];
					scirlce_data=(unsigned char )ModBus_DataBuf[2];
					scirlce_data<<=8;
					scirlce_data+=ModBus_DataBuf[3];
					
					Circle_Data=(int)mcirlce_data*65536+(unsigned int)scirlce_data;

					Circle_UpData_Flag=1;
					
					Modbus_Servo_Link_Flag=1;//Modbus 伺服已连接
						Modbus_ServoTimeOut=0;		
					ModeBus_DataRecv_Cnt=0;
					
					App_Modbus_Send_Return_Flag=1;//发送后收到有返回
					
//					memcpy(FIFO_Buf,IO_StatusBuf,4);
			break;
			
		case 'K':
			
						if((ModeBus_DataRecv_Cnt<2)&&(ModeBus_DataRecv_Cnt>8))
					{
						ModeBus_DataRecv_Cnt=0;
						return; 
					}
					IO_StatusBuf[0]=ModBus_DataBuf[1];
					IO_StatusBuf[1]=ModBus_DataBuf[0];
					IO_StatusBuf[2]=ModBus_DataBuf[3];
					IO_StatusBuf[3]=ModBus_DataBuf[2];
					
					 Stop_0x800C_Data=(unsigned char )ModBus_DataBuf[0];
					Stop_0x800C_Data<<=8;
					Stop_0x800C_Data+=(unsigned char )ModBus_DataBuf[1];
					
					Stop_0x800D_Data=(unsigned char )ModBus_DataBuf[2];
					Stop_0x800D_Data<<=8;
					Stop_0x800D_Data+=ModBus_DataBuf[3];
					
					
					Modbus_Servo_Link_Flag=1;//Modbus 伺服已连接
						Modbus_ServoTimeOut=0;		
					ModeBus_DataRecv_Cnt=0;
					
					App_Modbus_Send_Return_Flag=1;//发送后收到有返回
					
				Modbus_Motion_WaitStop_Flag=0;
		
		break;
		
		case 'c'://读单圈值返回

					if((ModeBus_DataRecv_Cnt<2)&&(ModeBus_DataRecv_Cnt>8))
					{
						ModeBus_DataRecv_Cnt=0;
						return; 
					}
					IO_StatusBuf[0]=ModBus_DataBuf[1];
					IO_StatusBuf[1]=ModBus_DataBuf[0];
					IO_StatusBuf[2]=ModBus_DataBuf[3];
					IO_StatusBuf[3]=ModBus_DataBuf[2];
					
					
					Modbus_Servo_Link_Flag=1;//Modbus 伺服已连接
						Modbus_ServoTimeOut=0;		
					ModeBus_DataRecv_Cnt=0;
					
					App_Modbus_Send_Return_Flag=1;//发送后收到有返回
					
			break;
		case 'R'://复位多圈值返回
			break;
		case 'r':
			
							if((ModeBus_DataRecv_Cnt<2)&&(ModeBus_DataRecv_Cnt>8))
					{
						ModeBus_DataRecv_Cnt=0;
						return; 
					}
					IO_StatusBuf[0]=ModBus_DataBuf[1];
					IO_StatusBuf[1]=ModBus_DataBuf[0];
					IO_StatusBuf[2]=ModBus_DataBuf[3];
					IO_StatusBuf[3]=ModBus_DataBuf[2];
					
					

						Modbus_ServoTimeOut=0;		
					ModeBus_DataRecv_Cnt=0;
					
					App_Modbus_Send_Return_Flag=1;//发送后收到有返回
					
			break;
		case 'p'://读伺服当前脉冲值
				if((ModeBus_DataRecv_Cnt<2)&&(ModeBus_DataRecv_Cnt>8))
					{
						ModeBus_DataRecv_Cnt=0;
						return; 
					}
					IO_StatusBuf[0]=ModBus_DataBuf[1];
					IO_StatusBuf[1]=ModBus_DataBuf[0];
					IO_StatusBuf[2]=ModBus_DataBuf[3];
					IO_StatusBuf[3]=ModBus_DataBuf[2];
					
					tempdata=ModBus_DataBuf[2];
					tempdata<<=8;
					
					tempdata+=ModBus_DataBuf[3];
					tempdata<<=8;
					
					tempdata+=ModBus_DataBuf[0];
					tempdata<<=8;
					
					tempdata+=ModBus_DataBuf[1];
					//tempdata<<=8;
					

					CurPosition=(int)tempdata;
					
					
					
					if(Machine_Position_Pulse_LoadOK_Flag==0)
					{
						Machine_Position_Pulse_LoadOK_Flag=1;
						Machine_Load_Postion_Pulse=CurPosition;						
					}
		
					Modbus_Servo_Link_Flag=1;//Modbus 伺服已连接
						Modbus_ServoTimeOut=0;		
					ModeBus_DataRecv_Cnt=0;
					
					App_Modbus_Send_Return_Flag=1;//发送后收到有返回
			break;
	}
}


////////void App_ModBus_Send_Task(void)
////////{
////////App_ModBus_Send_Time++;
////////if(App_ModBus_Send_Time>=50)
////////	{
////////	App_ModBus_Send_Time=0;//50MS收发一次
////////	App_Modbus_Send();//开始发送	
////////	}	
////////}

#include "stdlib.h"
#include "string.h"
#include "stdio.h"



void App_Modbus_Send(void)
{
return;
	//	RLOUT5_ON;
if(Modbus_Int_Send_Flag==0)
			{
				ModBus_QueueLoadCou=Modbus_Queue_CheckCnt();//获取index
				if(ModBus_QueueLoadCou>0)
				{
					
				
				memcpy(Uart_SendBuf,ModBus_Queue_Buf[0],32);
					
				App_ModBus_Status=Uart_SendBuf[1];//当前的状态
					
				////////			Uart_SendBuf[0]=8;	
				////////			Uart_SendBuf[1]='A';
				////////			ModBus_SendFrame(PLC_ADDER,MODBUS_READ_CMD,PLC_X_BASE_ADDER,0x04);//读取4个字的数据
				////////			memcpy(&Uart_SendBuf[2],Modbus_Sendbuf,8);
					
////////				Uart_SendBuf[0]=8;	
////////				Uart_SendBuf[1]='X';
////////				App_ModBus_Status=Uart_SendBuf[1];//读 X	//大写是读，小写是写
////////					
////////				Uart_SendBuf[2]=0x02;	
////////				Uart_SendBuf[3]=0x03;
////////				Uart_SendBuf[4]=0xA7;	
////////				Uart_SendBuf[5]=0xB8;
////////				Uart_SendBuf[6]=0x00;	
////////				Uart_SendBuf[7]=0x04;
////////				Uart_SendBuf[8]=0xe7;	
////////				Uart_SendBuf[9]=0x6B;

					
				ModBus_CommCou=0;

				Modbus_IntSend_Enter();	
				}					
			}	
}
