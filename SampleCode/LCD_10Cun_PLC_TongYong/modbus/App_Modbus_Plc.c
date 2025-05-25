#include "app_modbus_plc.h"


#include "app_plc.h"



#ifdef N972_MODBUS_SERVO


#include "modbus_972.h"


#include "modbus_972.h"
//#include "modbus.h"
#include "uart_config.h"

#include "pic_exec.h"

#include "app_plc.h"

#include "string.h"

//#include "app_modbus_motion.h"

//#include "app_fx_plc.h"
//#include "app_modbus_fxplc.h"


#include "app_modbus_972.h"
#include "modbus_972.h"


#else



#endif




unsigned char PLC_X_Status[8][8];
unsigned char PLC_Y_Status[8][8];
unsigned char PLC_M_Status[8][8];



unsigned char PLC_Run_Mode=PLC_MODE_3U;//PLC 运行模式  0:无PLC  1:3U  2:2N


unsigned int Modbus_PLC_AutoCut_SetTime=0;//自动裁切设定时间
unsigned char Modbus_PLC_D20_DownCutTime=0;//下刀时间


void App_Modbus_Plc_Init(void)
{
	
PLC_Run_Mode=PLC_MODE_3U;//PLC_MODE_NONE;//PLC_MODE_NONE;//PLC_MODE_3U;//PLC_MODE_NONE;//PLC_MODE_3U;//PLC_MODE_3U;//PLC_MODE_3U;//PLC_MODE_NONE;//PLC_MODE_3U;//PLC_MODE_3U;//PLC_MODE_NONE;//PLC_MODE_3U;//PLC 运行模式  0:无PLC  1:3U  2:2N	
	
//if((PLC_Run_Mode==PLC_MODE_NONE)||(PLC_Run_Mode==PLC_MODE_SERVO))//无PLC或SERVO不入
//		return;
	App_Load_Modbus_PLC_CFG();
	
}





//保存自动裁切时间 和下刀时间  新版本
void App_Save_Modbus_PLC_CFG(void)
{
unsigned char *pdtr;
pdtr=(unsigned char *)DOWNFILE_SDRAM_ADD;
	
iFiles.FileLength=3;

*pdtr++=Modbus_PLC_AutoCut_SetTime>>8;
*pdtr++=Modbus_PLC_AutoCut_SetTime;
*pdtr++=Modbus_PLC_D20_DownCutTime;


//memcpy((unsigned char *)DOWNFILE_SDRAM_ADD,&Modbus_Motion_Parameter,iFiles.FileLength);

ChangeFileName((unsigned char*)"Modbus_PLC.cfg");	//NandEccWrite_Flag=0;
File_Create((char*)iFiles.FileName);//建立文件
	
	
}




//调入自动裁切时间 和下刀时间
void App_Load_Modbus_PLC_CFG(void)
{	
	
unsigned char *pdtr;
	pdtr=(unsigned char *)DOWNFILE_SDRAM_ADD;
	
FileRead("Modbus_PLC.cfg",(unsigned char *)DOWNFILE_SDRAM_ADD);
	
Modbus_PLC_AutoCut_SetTime=*pdtr++;//=Modbus_Servo_Small_Gear>>8;
	Modbus_PLC_AutoCut_SetTime<<=8;
Modbus_PLC_AutoCut_SetTime+=*pdtr++;
	
Modbus_PLC_D20_DownCutTime=*pdtr++;//=Modbus_Servo_Big_Gear>>8;

	
	
if((Modbus_PLC_AutoCut_SetTime<100)||(Modbus_PLC_AutoCut_SetTime>5000)||(Modbus_PLC_D20_DownCutTime<1)||(Modbus_PLC_D20_DownCutTime>20))//>999)||(Modbus_Servo_DaoChen==0)||(Modbus_Servo_DaoChen>50))
		{
		Modbus_PLC_AutoCut_SetTime=1000;
		Modbus_PLC_D20_DownCutTime=10;	
		App_Save_Modbus_PLC_CFG();//预保存
		}			
}



unsigned char PLC_X_READ_OK_Flag=0;
unsigned char IO_StatusBuf[8];



#include "app_plc_ext_form.h"

void App_Modbus_FxPlc_Decode(void)
{
int idx=0;
int high_low_byte=1;
int i;
unsigned char * pdn;
//unsigned char * ypdn;
unsigned char temp;
unsigned char x_status=0;
unsigned char n;
	
ModBus_Queue_ChangeBuf();//收到返回后，清除缓冲区
Modbus_Queue_Clear_SendStatus();//接收到后，清除发送状态
	
if(Modbus_PLC_Link_Flag==0)
	{
	LinkUpDate_Flag=1;
	}
Modbus_PLC_Link_Flag=1;

Modbus_PlcTimeOut=0;
	
	
//unsigned char testbytecnt=0;
switch(Modubs_Cmd_Type)
	{
	case PLC_READ_X:

		////printf("PLC X Status is Read...\r\n");//,sendcnt,frecvcnt);// recv count = %d \r\n",recvcnt);//...\r\n"); 
	
	//	PLC_X_READ_OK_Flag=0;
	
	
						if(PLC_Run_Mode==PLC_MODE_3U)
					{
					IO_StatusBuf[0]=ModBus_DataBuf[1];
					IO_StatusBuf[1]=ModBus_DataBuf[0];
					IO_StatusBuf[2]=ModBus_DataBuf[3];
					IO_StatusBuf[3]=ModBus_DataBuf[2];
					}
					/*
						
					IO_StatusBuf[0]=ModBus_DataBuf[0];
					IO_StatusBuf[1]=ModBus_DataBuf[1];
					IO_StatusBuf[2]=ModBus_DataBuf[2];
					IO_StatusBuf[3]=ModBus_DataBuf[3];
					*/
				
					for(i=0;i<4;i++)
					{
						x_status=IO_StatusBuf[i];
							for(n=0;n<8;n++)
						{
							if(x_status&0x01)
								PLC_X_Status[i][n]='1';
							else
								PLC_X_Status[i][n]='0';
							x_status>>=1;
						}
					}
						
					
			//		sysprintf("X0 X1 X2 X3 X4 X5 X6 X7 X10 X12 X13 X14\r\n");
					for(i=0;i<8;i++)
							{
			//				sysprintf(" %d ",PLC_X_Status[0][i]-'0');							
							}
							
					for(i=0;i<4;i++)
							{
			//				sysprintf("  %d ",PLC_X_Status[1][i]-'0');							
							}
			//		sysprintf("\r\n");
							

		//			sprintf(stemp,"X %d",ModeBus_DataRecv_Cnt);		
		//			Printf24(stemp,REMIND_WINDOW_X+800,REMIND_WINDOW_Y-30,RED_COLOR,1,0xffff);
					ModeBus_DataRecv_Cnt=0;
		
					
					App_Modbus_Send_Return_Flag=1;//发送后收到有返回
					
					
					
//////////////		pdn=(unsigned char *)PLC_X_Status;

//////////////	//	//printf("X pdn = %d \r\n ",pdn);
//////////////		high_low_byte=1;
//////////////		for(idx=0;idx<4;idx++)
//////////////			{
//////////////			for(high_low_byte=1;high_low_byte>=0;high_low_byte--)
//////////////				{
//////////////				temp=ModBus_DataBuf[idx*2+high_low_byte];
//////////////				for(i=0;i<8;i++)
//////////////					{
//////////////					if(temp&0x01)
//////////////						*pdn++=1;
//////////////					else
//////////////						*pdn++=0;
//////////////					temp>>=1;
//////////////					}
//////////////				}
//////////////			}


	//	//printf("X Read X12  = %d ; X14 = %d \r\n",PLC_X_Status[10],PLC_X_Status[12]);
	//PLC_X_READ_OK_Flag=1;

		Modubs_Cmd_Type=0;
		break;

	case PLC_READ_Y:		
	
					if(PLC_Run_Mode==PLC_MODE_3U)
					{
					IO_StatusBuf[0]=ModBus_DataBuf[1];
					IO_StatusBuf[1]=ModBus_DataBuf[0];
					IO_StatusBuf[2]=ModBus_DataBuf[3];
					IO_StatusBuf[3]=ModBus_DataBuf[2];
						
					IO_StatusBuf[4]=ModBus_DataBuf[5];
					IO_StatusBuf[5]=ModBus_DataBuf[4];
					IO_StatusBuf[6]=ModBus_DataBuf[7];
					IO_StatusBuf[7]=ModBus_DataBuf[6];
					}
				
					for(i=0;i<8;i++)
					{
						x_status=IO_StatusBuf[i];
							for(n=0;n<8;n++)
						{
							if(x_status&0x01)
								PLC_Y_Status[i][n]='1';
							else
								PLC_Y_Status[i][n]='0';
							x_status>>=1;
						}
					}
//////////						
//////////				  sysprintf("Y20 Y21 Y22 Y23 Y24 Y25 Y26 Y27\r\n");
//////////					for(i=0;i<8;i++)
//////////							{
//////////							sysprintf(" %d ",PLC_Y_Status[2][i]-'0');							
//////////							}
//////////					sysprintf("\r\n");
//////////							
//////////				
//////////					  sysprintf("Y30 Y31 Y32 Y33 Y34 Y35 Y36 Y37\r\n");
//////////					for(i=0;i<8;i++)
//////////							{
//////////							sysprintf(" %d ",PLC_Y_Status[3][i]-'0');							
//////////							}
//////////							
//////////					sysprintf("\r\n");		
//////////							

//////////					sysprintf("Y40 Y41 Y42 Y43 Y44 Y45 Y46 Y47\r\n");
//////////					for(i=0;i<8;i++)
//////////							{
//////////							sysprintf(" %d ",PLC_Y_Status[4][i]-'0');							
//////////							}
//////////							
//////////					sysprintf("\r\n");	
//////////							
							
		//			sprintf(stemp,"X %d",ModeBus_DataRecv_Cnt);		
		//			Printf24(stemp,REMIND_WINDOW_X+800,REMIND_WINDOW_Y-30,RED_COLOR,1,0xffff);
					ModeBus_DataRecv_Cnt=0;
		
					
					App_Modbus_Send_Return_Flag=1;//发送后收到有返回
					
	  //	//printf("PLC Y Status is Read...\r\n");//

		//	//printf("Y enter Read X12  = %d ; X14 = %d \r\n",PLC_X_Status[10],PLC_X_Status[12]);

//////////////		pdn=(unsigned char *)PLC_Y_Status;
//////////////		high_low_byte=1;
//////////////	//	//printf("Y pdn = %d \r\n ",pdn);
//////////////	//	testbytecnt=0;
//////////////	//	//printf("testbytecnt = %d \r\n ",testbytecnt);
//////////////		for(idx=0;idx<4;idx++)
//////////////			{
//////////////			for(high_low_byte=1;high_low_byte>=0;high_low_byte--)
//////////////				{
//////////////				temp=ModBus_DataBuf[idx*2+high_low_byte];

//////////////		//		testbytecnt++;
//////////////		//		//printf("testbytecnt = %d \r\n ",testbytecnt);
//////////////				for(i=0;i<8;i++)
//////////////					{
//////////////					if(temp&0x01)
//////////////						*pdn++=1;
//////////////					else
//////////////						*pdn++=0;

//////////////					temp>>=1;
//////////////					}
//////////////				}
//////////////			}
	//	//printf("Y exit Read X12  = %d ; X14 = %d \r\n",PLC_X_Status[10],PLC_X_Status[12]);
		Modubs_Cmd_Type=0;
		break;
	}
}



void App_Modbus_Plc_Read_X_Status(unsigned short x_add,unsigned char num)
{
if((PLC_Run_Mode==PLC_MODE_NONE)||(PLC_Run_Mode==PLC_MODE_SERVO))//无PLC或SERVO不入
		return;
	
switch(PLC_Run_Mode)
		{
		case PLC_MODE_3U:	//3U
			ModBus_Queue_Insert(PLC_READ_X,PLC_ADDER,MODBUS_READ_CMD,PLC_X_BASE_ADDER,0x04);//
			break;
		case PLC_MODE_2N://2N
			
			ModBus_Queue_Insert(PLC_READ_X,PLC_ADDER,MODBUS_PLC_BIT_READ_CMD,PLC_2N_X_ADDER,num);//
			break;
		}		
	
	
}


void App_Modbus_Plc_Read_Y_Status(unsigned short y_add,unsigned char y_num)
{
if((PLC_Run_Mode==PLC_MODE_NONE)||(PLC_Run_Mode==PLC_MODE_SERVO))//无PLC或SERVO不入
		return;
	
switch(PLC_Run_Mode)
		{
		case PLC_MODE_3U:	//3U		
			ModBus_Queue_Insert(PLC_READ_Y,PLC_ADDER,MODBUS_READ_CMD,PLC_Y_BASE_ADDER,0x04);//
			break;
		case PLC_MODE_2N://2N
			ModBus_Queue_Insert(PLC_READ_Y,PLC_ADDER,MODBUS_PLC_BIT_READ_CMD,y_add+PLC_2N_Y_ADDER,y_num);//
			break;
		}		
}



void App_Modbus_Plc_Read_M_Status(unsigned short m_add)
{
if((PLC_Run_Mode==PLC_MODE_NONE)||(PLC_Run_Mode==PLC_MODE_SERVO))//无PLC或SERVO不入
		return;
	
switch(PLC_Run_Mode)
		{
		case PLC_MODE_3U:	//3U
			break;
		case PLC_MODE_2N://2N
			break;
		}	
}



void App_Modbus_Plc_Write_Y_Status(unsigned short y_add,unsigned short y_status)
{
if((PLC_Run_Mode==PLC_MODE_NONE)||(PLC_Run_Mode==PLC_MODE_SERVO))//无PLC或SERVO不入
		return;
switch(PLC_Run_Mode)
		{
		case PLC_MODE_3U:	//3U
				ModBus_Queue_Insert(PLC_WRITE_Y,PLC_ADDER,MODBUS_PLC_BIT_WRITE_CMD,y_add+PLC_2N_Y_ADDER,y_status);//
			break;
		case PLC_MODE_2N://2N
				ModBus_Queue_Insert(PLC_WRITE_Y,PLC_ADDER,MODBUS_PLC_BIT_WRITE_CMD,y_add+PLC_2N_Y_ADDER,y_status);//
			break;
		}		
}



void App_Modbus_Plc_Write_M_Status(unsigned short m_add,unsigned short m_status)
{
if((PLC_Run_Mode==PLC_MODE_NONE)||(PLC_Run_Mode==PLC_MODE_SERVO))//无PLC或SERVO不入
		return;
switch(PLC_Run_Mode)
		{
		case PLC_MODE_3U:	//3U
			ModBus_Queue_Insert(PLC_WRITE_M,PLC_ADDER,MODBUS_PLC_BIT_WRITE_CMD,m_add,m_status);//
			break;
		case PLC_MODE_2N://2N
			ModBus_Queue_Insert(PLC_WRITE_M,PLC_ADDER,MODBUS_PLC_BIT_WRITE_CMD,m_add+PLC_2N_M_ADDER,m_status);//
			break;
		}		
}



void App_Modbus_Plc_Read_D_Data(unsigned short d_add)
{
if((PLC_Run_Mode==PLC_MODE_NONE)||(PLC_Run_Mode==PLC_MODE_SERVO))//无PLC或SERVO不入
		return;
	
switch(PLC_Run_Mode)
		{
		case PLC_MODE_3U:	//3U
			break;
		case PLC_MODE_2N://2N
			break;
		}		
}


unsigned char Modbus_Plc_M280_Send_Flag=0;
void App_Modbus_Plc_Write_M280_FastCutMode(void)//M280 快速裁切模式
{
if(Modbus_Plc_M280_Send_Flag!=0)
{
	return;
	
}
	Modbus_Plc_M280_Send_Flag=1;
	

	if(IRChgWorkmodeValid_flag==0)
				{
				App_Modbus_Plc_Write_M_Status(280,M_OFF);	
				}
		else
				{
				App_Modbus_Plc_Write_M_Status(280,M_ON);						
				}
				
				
}



unsigned char Modbus_Plc_D20_Send_Flag=0;//D20 下刀时间 ，清0 可以重复发送

void App_Modbus_Plc_Write_D20_DownCutTime(void)		//D20 下刀时间发送,   清0 可以重复发送
{
if(Modbus_Plc_D20_Send_Flag!=0)
	return;
Modbus_Plc_D20_Send_Flag=1;

App_Modbus_Plc_Write_D_Data(20,Modbus_PLC_D20_DownCutTime);
	
}


void App_Modbus_Plc_Write_D_Data(unsigned short d_add,unsigned short d_data)
{
if((PLC_Run_Mode==PLC_MODE_NONE)||(PLC_Run_Mode==PLC_MODE_SERVO))//无PLC或SERVO不入
		return;	
switch(PLC_Run_Mode)
		{
		case PLC_MODE_3U:	//3U
			ModBus_Queue_Insert(PLC_WRITE_D,PLC_ADDER,MODBUS_WRITE_CMD,d_add,d_data);//
			break;
		case PLC_MODE_2N://2N
			break;
		}			
}



//为了兼容原来的程序编译
unsigned char App_Plc_SendFrame_Process(char* cmd,char * ctype,unsigned char sta,char str_c)
{
	
	
	
return 0;
}
