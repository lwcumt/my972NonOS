#include "app_plc.h"

#include "string.h"

#include "uart_config.h"

#include "key.h"
#include "m25pe16.h"

#include "plc_ext_form.h"


//PLC发送缓冲区
char Plc_SendBuf[128];

//PLC接收缓冲区
char Plc_RecvBuf[128];
char Plc_RecvTempBuf[128];

unsigned char Plc_Poll_Enb_Flag=0;

unsigned char Plc_RecvCnt=0;

char Plc_ContactStatus[64][1];//PLC触点状态

char Plc_Cur_Cmd=0;

char Plc_X_Status[64][1];//PLC输入触点状态

char Plc_Y_Status[64][1];//PLC输出触点状态

char Plc_X_Old_Status[64][1];//PLC输入触点状态
char Plc_Y_Old_Status[64][1];//PLC输出触点状态

char Plc_DT_Data[64][4];

unsigned short Plc_DT_Data_t[32];


unsigned char  Plc_ReadContactChannel=0;//当前读取的通道

unsigned char App_Plc_RCS_Return_OK_Flag=0;
unsigned char App_Plc_WCS_Return_Ok_Flag=0;

unsigned char Plc_Send_DT_Data_Flag=0;

unsigned int  Plc_Comm_TimeOut=0;

unsigned char XD_XE_Flag=0;


unsigned char Plc_Comm_Status=0;//0正常通读




char Plc_Add[2]={'0','1'};

//PLC通讯初始化
void App_Plc_Init(void)
{	
int i;
//发送接收缓冲区全为0
	
	MainPower_Status=0;
	Manual_Knife_Status=0;
	Fast_Knife_Status=0;
	Motor_Knife_Status=0;
	XD_XE_Flag=1;//开机设XD_XE信号正常
for(i=0;i<128;i++)
	{
		Plc_SendBuf[i]=0;
		Plc_RecvBuf[i]=0;
//		Plc_RecvBuf[i]=0;		
	}	

//触点状态全为OFF	
for(i=0;i<64;i++)
	{
		Plc_ContactStatus[i][0]=PLC_CONTACT_OFF;
		Plc_X_Status[i][0]=PLC_CONTACT_OFF;
		Plc_Y_Status[i][0]=PLC_CONTACT_OFF;
		Plc_X_Old_Status[i][0]=PLC_CONTACT_OFF;
		Plc_Y_Old_Status[i][0]=PLC_CONTACT_OFF;		
		Plc_DT_Data[i][0]='0';
		Plc_DT_Data[i][1]='1';
		Plc_DT_Data[i][2]='5';
		Plc_DT_Data[i][3]='8';
	}		
	
Read_PLC_DT_Data((pInt8U)&Plc_DT_Data_t);//保存PLC DT 数据
	
	/*
Plc_DT_Data_t[0]=80;
Plc_DT_Data_t[1]=5;
Plc_DT_Data_t[2]=0;	
Plc_DT_Data_t[3]=500;	
Plc_DT_Data_t[4]=200;	
Plc_DT_Data_t[5]=1000;	
	*/
	
//////Plc_Send_DT_Data_Flag=1;
//////	App_Plc_Send_DT_Data();
	
//App_Plc_WriteData("WD","D",0,5);// 写入DT0，DT1
	
}



void App_Plc_Send_DT_Data(void)
{
if(Plc_Send_DT_Data_Flag==1)
	{
	Plc_Send_DT_Data_Flag=0;
	App_Plc_WriteData("WD","D",0,5);// 写入DT0，DT1		
	}
	
}



//超时检测

void App_Plc_TimeOut_Exec(void)
{
Plc_Comm_TimeOut++;
if(Plc_Comm_TimeOut<PLC_COMM_TIMEOUT_DATA)
		{
		return;
		}

Plc_Comm_TimeOut=0;
		
if(Plc_Comm_Status!=PLC_COMM_TIMEOUT)//超时
	{
	Plc_Comm_Status=PLC_COMM_TIMEOUT;//置超时	

	}	
else
		Printf24("无法连接到PLC，请关机检查......",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,RED_COLOR,1,0xffff);
}

#include "optimize_cut.h"


void Read_PLC_DT_Data(pInt8U pdata)
{
// pInt8U pdata;
Int32U add,n;
add=ORIGINAL_25PEADD+PLC_SAVE_ADD;
FastRead_Datas_Start(add);
for(n=0;n<64;n++)
	{
	*pdata++=ReadFlash_Datas();
	}
FlashChip_Dis;
	
if((Plc_DT_Data_t[0]<80)||(Plc_DT_Data_t[0]>200)||
	(Plc_DT_Data_t[1]<2)||(Plc_DT_Data_t[1]>30)||
	(Plc_DT_Data_t[3]<200)||(Plc_DT_Data_t[3]>1000)||
	(Plc_DT_Data_t[4]!=200)||
	(Plc_DT_Data_t[5]!=1000)||
   (Plc_DT_Data_t[10]<1)||(Plc_DT_Data_t[10]>10)||
	(Plc_DT_Data_t[11]>1))//50)||(Plc_DT_Data_t[0]<50))
		{//默认值
		///*

		Plc_DT_Data_t[0]=100;
		Plc_DT_Data_t[1]=10;
		Plc_DT_Data_t[2]=0;	
		Plc_DT_Data_t[3]=500;	
		Plc_DT_Data_t[4]=200;	
		Plc_DT_Data_t[5]=1000;	
			
		Plc_DT_Data_t[10]=OptimizeCut_DelayTime=5;  //Plc_DT_Data_t[10]  保存优化裁切 延时时间
		Plc_DT_Data_t[11]=FastCut_Enb_Flag=0;
			
		Save_PLC_DT_Data((pInt8U)&Plc_DT_Data_t);//保存PLC DT 数据
		//*/
		}

OptimizeCut_DelayTime=Plc_DT_Data_t[10];	//Plc_DT_Data_t[10]  保存优化裁切 延时时间	
		FastCut_Enb_Flag=Plc_DT_Data_t[11];
}

void Save_PLC_DT_Data(pInt8U pdata)
{
Int32U add,n;
add=ORIGINAL_25PEADD+PLC_SAVE_ADD;
Write_25pe_data(pdata, add, 64);
}

//PLC 串口接收处理  把此函数放在串口中断 引用
void App_Plc_RecvData(char rdata)
{	
Plc_RecvBuf[Plc_RecvCnt++]=rdata;
if(rdata=='\r')//帧结尾
		{
			Plc_RecvBuf[Plc_RecvCnt]=0;//结尾
			Plc_RecvCnt=0;//重新开始接收
			memcpy(Plc_RecvTempBuf,Plc_RecvBuf,128);//拷贝到暂存区，以防新数据覆盖
			App_Plc_DeCode(Plc_RecvTempBuf);//对暂存区数据进行解码
			
		}	
}


//读取触点
void App_Plc_Read_Contact(void)
{
App_Plc_SendFrame("RCS","X",Plc_ReadContactChannel,0);//读取0通道触点	
}


//PLC发送帧
void App_Plc_SendFrame(char *cmd, char *datcode,unsigned int num,char sta)
{
char  *pdn;
unsigned char chk=0;
char numstr[8];
int len;
len=strlen((char*)cmd);
if(len<1)
		return;

	
pdn=Plc_SendBuf;
*pdn++='%';
*pdn++=Plc_Add[0];
*pdn++=Plc_Add[1];
*pdn++='#';
memcpy(pdn,cmd,len);
pdn+=len;

len=strlen((char*)datcode);
if(len<1)
		return;	

memcpy(pdn,datcode,len);
pdn+=len;


//sprintf(numstr,"%04d",num);
*pdn++='0';
*pdn++='0';
*pdn++=((unsigned char)num>>4)+0x30;
if(((unsigned char)num&0x0f)>9)
	*pdn++=((unsigned char)num&0x0f)+0x37;
else
		*pdn++=((unsigned char)num&0x0f)+0x30;
//memcpy(pdn,numstr,4);
//pdn+=4;
if(sta==0)
{
	
}
else
	{
	*pdn++=sta;
	}
*pdn=0;

chk=App_Plc_CheckSum(Plc_SendBuf);

if((chk>>4)>9)
	*pdn++=(chk>>4)+0x37;
else
	*pdn++=(chk>>4)+0x30;

if((chk&0x0f)>9)
	*pdn++=(chk&0xf)+0x37;
else
	*pdn++=(chk&0xf)+0x30;
*pdn++='\r'; //插入CR
*pdn++=0;//字符串结尾	


UART0_SendStr(Plc_SendBuf);

//UART_Printf(UART0,Plc_SendBuf);
}


unsigned char  App_Plc_SendFrame_Process(char *cmd, char *datcode,unsigned int num,char sta)
{
int i;
for(i=0;i<3;i++)
		{
		Plc_Comm_TimeOut=0; 
		App_Plc_WCS_Return_Ok_Flag=0;
			
		App_Plc_SendFrame(cmd,datcode,num,sta);//发送关闭R11
		while(App_Plc_WCS_Return_Ok_Flag==0)
				{
					
				if(Plc_Comm_Status==PLC_COMM_TIMEOUT)//置超时	
					{
					break;
						
					}
				};
				
		if(App_Plc_WCS_Return_Ok_Flag==1)
			{
			Plc_Comm_TimeOut=0; 
			break;
			}
		}
		
if(i>=3)
		{//超时，通讯错误
			
		return 1;	
		}
	
return 0;
}


//读取数据
void App_Plc_ReadData(char *cmd, char *datcode,unsigned int startadd,unsigned int endadd)
{
	char  *pdn;
unsigned char chk=0;
char numstr[8];
int len;
len=strlen((char*)cmd);
if(len<1)
		return;

	
pdn=Plc_SendBuf;
*pdn++='%';
*pdn++=Plc_Add[0];
*pdn++=Plc_Add[1];
*pdn++='#';
memcpy(pdn,cmd,len);
pdn+=len;

len=strlen((char*)datcode);
if(len<1)
		return;	

memcpy(pdn,datcode,len);
pdn+=len;


//sprintf(numstr,"%04d",num);
*pdn++='0';
	
sprintf(numstr,"%04d",startadd);

memcpy(pdn,numstr,4);
pdn+=4;
*pdn++='0';
sprintf(numstr,"%04d",endadd);

memcpy(pdn,numstr,4);
pdn+=4;
*pdn=0;

chk=App_Plc_CheckSum(Plc_SendBuf);

if((chk>>4)>9)
	*pdn++=(chk>>4)+0x37;
else
	*pdn++=(chk>>4)+0x30;

if((chk&0x0f)>9)
	*pdn++=(chk&0xf)+0x37;
else
	*pdn++=(chk&0xf)+0x30;
*pdn++='\r'; //插入CR
*pdn++=0;//字符串结尾	
UART0_SendStr(Plc_SendBuf);
//UART_Printf(UART0,Plc_SendBuf);

}


//写入数据
void App_Plc_WriteData(char *cmd, char *datcode,unsigned int startadd,unsigned int endadd)
{
	char  *pdn;
unsigned char chk=0;
char numstr[8];
int senddatanum=0;
	int i;
	
char tempbuf[4];
unsigned char temp=0;
	
int len;
len=strlen((char*)cmd);
if(len<1)
		return;

if(startadd>endadd)
	return;	
senddatanum=endadd-startadd;
senddatanum++;

pdn=Plc_SendBuf;
*pdn++='%';
*pdn++=Plc_Add[0];
*pdn++=Plc_Add[1];
*pdn++='#';
memcpy(pdn,cmd,len);
pdn+=len;

len=strlen((char*)datcode);
if(len<1)
		return;	

memcpy(pdn,datcode,len);
pdn+=len;


//sprintf(numstr,"%04d",num);
*pdn++='0';
	
sprintf(numstr,"%04d",startadd);

memcpy(pdn,numstr,4);
pdn+=4;
*pdn++='0';
sprintf(numstr,"%04d",endadd);

memcpy(pdn,numstr,4);
pdn+=4;





for(i=0;i<senddatanum;i++)
	{
	temp=(Plc_DT_Data_t[i]>>4)&0x0F;
	if(temp>9)
		tempbuf[0]=temp+0x37;
	else
		tempbuf[0]=temp+0x30;
	
	temp=(Plc_DT_Data_t[i])&0x0F;
	if(temp>9)
		tempbuf[1]=temp+0x37;
	else
		tempbuf[1]=temp+0x30;

		temp=(Plc_DT_Data_t[i]>>16)&0x0F;
	if(temp>9)
		tempbuf[2]=temp+0x37;
	else
		tempbuf[2]=temp+0x30;
	
	temp=(Plc_DT_Data_t[i]>>8)&0x0F;
	if(temp>9)
		tempbuf[3]=temp+0x37;
	else
		tempbuf[3]=temp+0x30;
	
	memcpy(pdn,tempbuf,4);
	pdn+=4;	
	}
	
*pdn=0;

chk=App_Plc_CheckSum(Plc_SendBuf);

if((chk>>4)>9)
	*pdn++=(chk>>4)+0x37;
else
	*pdn++=(chk>>4)+0x30;

if((chk&0x0f)>9)
	*pdn++=(chk&0xf)+0x37;
else
	*pdn++=(chk&0xf)+0x30;
*pdn++='\r'; //插入CR
*pdn++=0;//字符串结尾	


UART0_SendStr(Plc_SendBuf);
//UART_Printf(UART0,Plc_SendBuf);

}

int Plc_Poll_Enb_Time=0;
unsigned char Plc_Send_WCS_Flag=0;
unsigned char Plc_Send_WCS_TimeOut=0;

//PLC 状态查询
void App_Plc_PollReadStatus(void)
{
	
/*
if(Plc_Send_WCS_Flag==1)
	{
	Plc_Poll_Enb_Time=0;
	return;
	}
	
*/
///*

			
	//*/
if(Plc_Poll_Enb_Flag==0)
		{
			Plc_Poll_Enb_Time++;
			if(Plc_Poll_Enb_Time>=2)
			{
				Plc_Poll_Enb_Time=0;
				Plc_Poll_Enb_Flag=1;
				
				if(Plc_Send_DT_Data_Flag==1)
				{
				App_Plc_Send_DT_Data();//判断是否有更新DT数据
				
				Plc_Send_DT_Data_Flag=0;
				Plc_Poll_Enb_Flag=0;
					return;
				}
				
				if(Plc_Cur_Cmd==0)
					{
					Plc_Cur_Cmd='X';
					Plc_ReadContactChannel=0;
					App_Plc_SendFrame("RCS","X",Plc_ReadContactChannel,0);//读取0通道触点		
						
					
					return;
					}
	
				Plc_ReadContactChannel++;
				
				if((Plc_Cur_Cmd=='X')&&(Plc_ReadContactChannel>0x17))
						{
						Plc_Cur_Cmd='Y';
						Plc_ReadContactChannel=0;
							App_Plc_CheckStatus_DisHint();
						}
				else
						{
						if((Plc_Cur_Cmd=='Y')&&(Plc_ReadContactChannel>0x0F))
							{
							Plc_Cur_Cmd='X';
							Plc_ReadContactChannel=0;			
							}							
						else
							{

							}
						}					

				if(Plc_Cur_Cmd=='X')
					App_Plc_SendFrame("RCS","X",Plc_ReadContactChannel,0);//读取0通道触点			
				if(Plc_Cur_Cmd=='Y')			
					App_Plc_SendFrame("RCS","Y",Plc_ReadContactChannel,0);//读取0通道触点				
				}					
		}
else
		{
		Plc_Poll_Enb_Time=0;			
		}		
}


void App_Plc_CheckStatus_DisHint(void)
{
	
						if(MainPower_Status>0)
				{
					
					if((Plc_X_Status[0x0D][0]=='0')&&(Plc_X_Status[0x0E][0]=='1'))
					{
					Printf24("   PLC XD 信号断开  主机已停止",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,RED_COLOR,1,0xffff);	
						MainPower_Status=0;
						XD_XE_Flag=0;
					//	return;
					}
					if((Plc_X_Status[0x0D][0]=='1')&&(Plc_X_Status[0x0E][0]=='0'))
					{
					Printf24("   PLC XE 信号断开  主机已停止",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,RED_COLOR,1,0xffff);	
						MainPower_Status=0;
							XD_XE_Flag=0;
					//	return;
					}

					if((Plc_X_Status[0x0D][0]=='0')&&(Plc_X_Status[0x0E][0]=='0'))
					{
					Printf24("PLC XD、XE信号断开 主机停止",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,RED_COLOR,1,0xffff);
						MainPower_Status=0;
						XD_XE_Flag=0;
				//	return;
					}					
				}
			else
			{
				if((Plc_X_Status[0x0D][0]=='1')&&(Plc_X_Status[0x0E][0]=='1'))
					{
					if(XD_XE_Flag==0)
						{
						XD_XE_Flag=1;
						Printf24("      PLC XD、XE信号正常      ",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,RED_COLOR,1,0xffff);
						MainPower_Status=0;
						}
					//return;
					}					
			}	

			if(Manual_Knife_Status==1)
				{	
				if((Plc_X_Status[1][0]=='1'))
						{
						Printf24("        PLC X1 信号闭合         ",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,RED_COLOR,1,0xffff);	
								//	return;
						}
				else
						{
							Printf24("        PLC X1 信号断开         ",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,RED_COLOR,1,0xffff);		
						}
				}

}


//PLC解码
void App_Plc_DeCode(char *rbuf)
{
char *pdn;
	int len;

	if(App_Plc_CheckedCHK(rbuf)==1)
		return; //检验码出错
	
len=strlen(rbuf);
	
	
if(rbuf[len-1]!='\r')
	return;


pdn=rbuf;
	
if(*pdn++!='%')
		return;//非法数据
if(*pdn++!=Plc_Add[0])
	return;//非法地址
if(*pdn++!=Plc_Add[1])
	return;//非法地址

if(*pdn++=='$')
		{//正确应答			
		if((*pdn=='R')&&(*(pdn+1)=='C'))
				{//读取触点返回指令
				pdn+=2;
				if(*pdn==PLC_CONTACT_OFF)
					{//OFF状态
					switch(Plc_Cur_Cmd)
							{
							case 'X':
								Plc_X_Status[Plc_ReadContactChannel][0]=*pdn;
								break;
							
							case 'Y':
								Plc_Y_Status[Plc_ReadContactChannel][0]=*pdn;
								break;												
							}
					Plc_ContactStatus[Plc_ReadContactChannel][0]=*pdn;
					}					
				else
					{
					if(*pdn==PLC_CONTACT_ON)
						{//ON状态
						switch(Plc_Cur_Cmd)
								{
								case 'X':
									Plc_X_Status[Plc_ReadContactChannel][0]=*pdn;
									break;
							
								case 'Y':
									Plc_Y_Status[Plc_ReadContactChannel][0]=*pdn;
									break;													
								}							
								
						Plc_ContactStatus[Plc_ReadContactChannel][0]=*pdn;
						}
					else
						{//非法数据状态
						return;
						}
					}	
				Plc_Poll_Enb_Flag=0;
				App_Plc_RCS_Return_OK_Flag=1;
				Plc_Comm_TimeOut=0;
				return;
				}		
				
		if((*pdn=='R')&&(*(pdn+1)=='D'))
				{//读取数据返回指令
				pdn+=2;

					
				
				return;
				}	
		if((*pdn=='W')&&(*(pdn+1)=='C'))
				{//写触点返回指令
				App_Plc_WCS_Return_Ok_Flag=1;
				Plc_Comm_TimeOut=0;
				}					
		}
else
		{
		if(*pdn++=='!')
			{//错误应答
			
			}
		else
			{
				return; //非法格式
			}			
		}
}






//生成校验码并返回
unsigned char App_Plc_CheckSum(char *cbuf)
{
int len;
int i;
unsigned char chk=0;
len=strlen((char*)cbuf);
for(i=0;i<len;i++)
	{
		chk^=*cbuf++;		
	}
return chk;	
}


//检验校验码是否正确   正确返回0，错误返回1
unsigned char App_Plc_CheckedCHK(char *cbuf)
{
	
int len;
int i;
	//char *pdn;
unsigned char chk=0;
char chkstr[2];
len=strlen((char*)cbuf);
	//pdn=cbuf;
for(i=0;i<len-3;i++)
	{
		chk^=cbuf[i];		
	}
	
	
if((chk>>4)>9)
	chkstr[0]=(chk>>4)+0x37;
else
	chkstr[0]=(chk>>4)+0x30;

if((chk&0x0f)>9)
	chkstr[1]=(chk&0xf)+0x37;
else
	chkstr[1]+=(chk&0xf)+0x30;

if((chkstr[0]==cbuf[len-3])&&(chkstr[1]==cbuf[len-2]))
		return 0;
else
	return 1;	
}

	


