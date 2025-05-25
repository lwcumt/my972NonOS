#include "comm_fx_plc.h"

#include "uart_config.h"
//#include "modbus.h"

//#include "device.h"
//#include "modbus_rtu.h"


#include "fx_plc_form.h"
#include "app_fx_plc.h"
#include "pic_exec.h"
#include "modbus_972.h"


unsigned char Fx_Plc_RecvBuf[32];


unsigned char Fx_Plc_SendBuf[32];

unsigned char Fx_Plc_RecvCnt=0;
unsigned char Fx_Plc_Cnt=0;

unsigned int FX_Plc_AutoSendTime=0;

//////unsigned char FX_PLC_X_Status[18];
//////unsigned char FX_PLC_Y_Status[18];


unsigned char FX_Plc_Comm_Recv_Head_Flag=0;



static char _getAscii(int i) 
{
	if (i >=0 && i <= 9) return i+'0';
	else if (i>=10 && i <=15) return (i-10)+'A';
}

static char _getAddressAscii(int address, char buf[4])
{
	int x = address * 2 + 0x1000;

	int i, j, m, n;  
	i = x / (16 * 16 * 16); 
	j = (x / (16 * 16)) % 16; 
	m = x - i*(16*16*16) - j*(16*16); 
	m = m / 16; 
	n = x % 16; 

	buf[0] = _getAscii(i);
	buf[1] = _getAscii(j);
	buf[2] = _getAscii(m);
	buf[3] = _getAscii(n);
}

unsigned char Send_Status=1;
unsigned char Send_Cnt=20;

char FX_Plc_Comm_Status;


unsigned int SwapAdder(unsigned int add);
unsigned int Comm_FX_Plc_AsciiToHex(char *asc);


unsigned int Comm_FX_Plc_AsciiToHex(char *asc)
{
unsigned int hexdata=0;
unsigned char lowbyte=0;
	unsigned char highbyte=0;
		
		if(*asc>'9')
			lowbyte+=(*asc-0x3A)*16;
		else
			lowbyte+=(*asc-0x30)*16;					
		asc++;
		if(*asc>'9')
			lowbyte+=(*asc-0x3A);
		else
			lowbyte+=(*asc-0x30);			
		asc++;
		
		if(*asc>'9')
			highbyte+=(*asc-0x3A)*16;
		else
			highbyte+=(*asc-0x30)*16;					
		asc++;
		if(*asc>'9')
			highbyte+=(*asc-0x3A);
		else
			highbyte+=(*asc-0x30);				
	hexdata=highbyte*256+lowbyte;
		return hexdata;
}

void CommExec_FX_Plc(unsigned char  rx)
{
int sum=0;
	int i;
if(FX_Plc_Comm_Recv_Head_Flag==0)
	{	
	Fx_Plc_RecvCnt=0;
	if(rx==0x06)
			{				//ACK
				//FX_Plc_Form_Display(rx); //更新显示
				
				FX_Plc_Comm_Status=' ';//接收到清状态		
			}
	else	
			{
			if(rx==0x15)
					{//NAK	
						
					FX_Plc_Comm_Status=' ';//接收到清状态		
					}		
			else
					{
					if(rx==0x02)
							{//Data Frame	
							//	Fx_Plc_RecvCnt=0;
								FX_Plc_Comm_Recv_Head_Flag=1;//置数据帧接收
							}										
					}				
			}		
	}
else	
	{
	FX_Plc_Comm_TimeOut=0; 
	Fx_Plc_RecvBuf[Fx_Plc_RecvCnt++]=rx;
	if(Fx_Plc_RecvBuf[Fx_Plc_RecvCnt-3]==0x03)
			{ //帧数据完成
			//	FX_Plc_Form_Display(rx); //更新显示
				
				sum=0;
				for(i=0;i<(Fx_Plc_RecvCnt-2);i++)
				{
					sum+=Fx_Plc_RecvBuf[i];
				}
				if((Fx_Plc_RecvBuf[Fx_Plc_RecvCnt-2]==_getAscii((sum>>4)&0x0f))&&(Fx_Plc_RecvBuf[Fx_Plc_RecvCnt-1]==_getAscii(sum&0xf)))
				{//校验和正确
					Fx_Plc_RecvBuf[Fx_Plc_RecvCnt-3]=0;
					
					
					App_FX_Plc_CommDecode();//接收译码
					
////////					//  
////////					if(FX_Plc_Comm_Status=='R')
////////					{
////////					i=Comm_FX_Plc_AsciiToHex((char *)Fx_Plc_RecvBuf);
////////					sprintf((char*)Fx_Plc_RecvBuf,"%d",i);
////////						Printf24(Fx_Plc_RecvBuf,100,400,RED_COLOR,0,0xffffff);
////////					//FX_Plc_Form_PrintLabel((char*)&Fx_Plc_RecvBuf);
////////					}
					
					FX_Plc_Comm_Status=' ';//接收到清状态							
				}
				else
				{
				//	FX_Plc_Form_PrintLabel("CheckSum Err");
				}
				
				Fx_Plc_RecvCnt=0;
				FX_Plc_Comm_Recv_Head_Flag=0;
			}
	}
	
/*
if(Fx_Plc_RecvCnt>=10)
		{
			Fx_Plc_RecvCnt=0;
		}
		*/


}






////////for Test
//////void Comm_FX_Plc_Exec(void)
//////{
//////int fxplctime=0;
//////unsigned int ti;
//////	unsigned char wdata[8];
//////	char strbuf[16];
//////	
////////FX_Plc_Comm_Status='I';
//////			
//////FX_Plc_PollTime++;
//////if(FX_Plc_PollTime>=10)
//////		{
//////		FX_Plc_PollTime=0;
//////		Fx_Plc_Poll_SetpCnt++;
//////		if(Fx_Plc_Poll_SetpCnt>=10)
//////			{			
//////			Fx_Plc_Poll_SetpCnt=0;
//////			
//////					

//////			}
//////		//	sprintf(strbuf,"%x",Fx_Plc_Poll_SetpCnt);
//////		//	Printf24(strbuf,50,500,RED_COLOR,1,WHITE_COLOR);				
//////		switch(Fx_Plc_Poll_SetpCnt)
//////			{
//////			case 1:
//////					//强制打开Y50
//////					Comm_FX_Plc_ForceON(SwapAdder(Y050));
//////				break;
//////			case 2:
//////				Comm_FX_Plc_Read_X_Status(X000_7,4);//读取X00-X07  至 X30 -X37的状态
//////				break;
//////		  case 3:
//////				Comm_FX_Plc_Read_Y_Status(Y020_7,4);//读取X00-X07  至 X30 -X37的状态
//////				break;
//////			case 4:
//////				wdata[0]=0x2;//写入长度
//////				wdata[1]=100;//先低字节，再高字节
//////				wdata[2]=0;
//////				ti=625;
//////					
//////				Comm_FX_Plc_Write_D_Area(300,(unsigned char*)&ti,2);

//////				break;
//////			case 5:
//////				break;
//////			case 6:
//////		//		Comm_FX_Plc_Read_D_Area(20,2);
//////				//		Comm_FX_Plc_Read(X000_7,2);//读取2个字节 从X00-X07 到 X10-X17							
//////				break;
//////			case 7:
//////				break;
//////				}
//////		}			
//////}

unsigned int SwapAdder(unsigned int add)
{
	unsigned int a1;
	a1=(add>>8)&0xff;
	a1+=(add<<8)&0xFF00;
	return a1;	
}



void Comm_FX_Plc_Read_X_Status(unsigned short xadd,unsigned char len)
{
//if(FX_Plc_Comm_Status=='I')
		{
		FX_Plc_Comm_Status='X';		
		FX_PLC_SendFrame(FX_CMD_READ,xadd,&len,len);//写入N个字节的数据
			
	//	Comm_FX_Plc_Read(xadd,len);//读取2个字节 从X00-X07 到 X30-X17			
		}	
}


void Comm_FX_Plc_Read_Y_Status(unsigned short yadd,unsigned char len)
{
//if(FX_Plc_Comm_Status=='I')
		{
		FX_Plc_Comm_Status='Y';		
		FX_PLC_SendFrame(FX_CMD_READ,yadd,&len,len);//写入N个字节的数据		
	//	Comm_FX_Plc_Read(yadd,len);//读取2个字节 从X00-X07 到 X30-X17			
		}	
}


void Comm_FX_Plc_Read_M_Status(unsigned short madd,unsigned char len)
{
//if(FX_Plc_Comm_Status=='I')
		{
			
	//		madd*=2;
		madd+=M_BASE_ADD;
			
		FX_Plc_Comm_Status='M';		
		FX_PLC_SendFrame(FX_CMD_READ,madd,&len,len);//写入N个字节的数据		
	//	Comm_FX_Plc_Read(yadd,len);//读取2个字节 从X00-X07 到 X30-X17			
		}	
}



//读 数据
void Comm_FX_Plc_Read(unsigned int adder,unsigned char len)
{
adder*=2;
adder+=D_BASE_ADD;
FX_PLC_SendFrame(FX_CMD_READ,adder,&len,1);//读取1个字节的数据
}

//写数据
void Comm_FX_Plc_Write(unsigned int adder,unsigned char *dbuf,unsigned char len)
{

adder*=2;
adder+=D_BASE_ADD;	
FX_PLC_SendFrame(FX_CMD_WRITE,adder,dbuf,len);//写入N个字节的数据
}


//读D区数据
void Comm_FX_Plc_Read_D_Area(unsigned int adder,unsigned char len)
{
//*********************************
//读D区 地址高字节在前，低字节在后	  返回值 低字节在前 高字节在后	
adder*=2;
adder+=D_BASE_ADD;
FX_Plc_Comm_Status='R';		
FX_PLC_SendFrame(FX_CMD_READ,adder,&len,len);//读取1个字节的数据
}

//写D区数据
void Comm_FX_Plc_Write_D_Area(unsigned int adder,unsigned char *dbuf,unsigned char len)
{
//*********************************
//写D区 地址高字节在前，低字节在后	  返回值 低字节在前 高字节在后
adder*=2;
adder+=D_BASE_ADD;	
FX_Plc_Comm_Status='W';		
FX_PLC_SendFrame(FX_CMD_WRITE,adder,dbuf,len);//写入N个字节的数据
}



//读XY区数据
void Comm_FX_Plc_Read_XY_Area(unsigned int adder,unsigned char len)
{
FX_Plc_Comm_Status='A';//读xy区
FX_PLC_SendFrame(FX_CMD_READ,adder,&len,1);//读取1个字节的数据
}

//写XY区数据
void Comm_FX_Plc_Write_XY_Area(unsigned int adder,unsigned char *dbuf,unsigned char len)
{
FX_PLC_SendFrame(FX_CMD_WRITE,adder,dbuf,len);//写入N个字节的数据
}


//*************************
//强制 开
void Comm_FX_Plc_ForceON(unsigned int adder)
{
//*********************************
//强制ON 地址低字节在前，高字节在后
	//if(FX_Plc_Comm_Status=='I')
		{//空闲状态发送
		FX_Plc_Comm_Status='F';		
		FX_PLC_SendFrame(FX_CMD_FORCE_ON,adder,0,0);//强制开启
	//	FX_Plc_Comm_Status='I';
	}
}

//*************************
//强制 关
void Comm_FX_Plc_ForceOFF(unsigned int adder)
{
//*********************************
//强制ON 地址低字节在前，高字节在后	
//if(FX_Plc_Comm_Status=='I')
			{//空闲状态发送
			FX_Plc_Comm_Status='F';		
			FX_PLC_SendFrame(FX_CMD_FORCE_OFF,adder,0,0);//强制关闭
		//	FX_Plc_Comm_Status='I';
			}
}



void Comm_FX_Plc_Send(void)
{
unsigned char *pdu;
	FX_Plc_AutoSendTime++;
	if(FX_Plc_AutoSendTime<1000)
		return;
	FX_Plc_AutoSendTime=0;
	pdu=Fx_Plc_SendBuf;
	
//	FX_PLC_SendFrame('0',0x1000+20,2);//D  区
//	FX_PLC_SendFrame('0',0x0100,1);//M 区
	FX_PLC_SendFrame('7',0x0008,0,0);//M 区
	//FX_PLC_SendFrame('0',0x80,1);//X  区
//	FX_PLC_SendFrame('0',0xA0,1);//Y  区
	return;
	
	
	/*
	Fx_Plc_SendBuf[0]=0x01;
	Fx_Plc_SendBuf[1]=0x05
	Fx_Plc_SendBuf[2]=(0xA7A8+20)>>8;
	Fx_Plc_SendBuf[3]=0xA7A8+20;
	Fx_Plc_SendBuf[4]=
	Fx_Plc_SendBuf[5]=
	Fx_Plc_SendBuf[6]=
	*/
	
	ModBus_SendFrame(0x1,0x05,0xA7A8+Send_Cnt,Send_Status);//编码器位置
	
	/*
Fx_Plc_SendBuf[0]=0x02;
Fx_Plc_SendBuf[1]='7';
	
		_getAddressAscii(0x10, &Fx_Plc_SendBuf[2]);
	
			Fx_Plc_SendBuf[2]='1';
		Fx_Plc_SendBuf[3]='3';
		Fx_Plc_SendBuf[4]='0';
		Fx_Plc_SendBuf[5]='5';
	Fx_Plc_SendBuf[6]=3;//'0';
	Fx_Plc_SendBuf[7]='0';
	Fx_Plc_SendBuf[8]='3';

	Fx_Plc_SendBuf[8]=3;
		int i, sum = 0;
	for (i = 1; i <= 6; i++)
		sum += Fx_Plc_SendBuf[i];

	i = sum&0xFF;
	Fx_Plc_SendBuf[7]  = _getAscii(i/16);
	Fx_Plc_SendBuf[8] = _getAscii(i%16);
	
	*/
	UART0_SendBuf(Modbus_Sendbuf,8);
	
	Send_Cnt++;
	if(Send_Cnt>=57)
	{
		Send_Cnt=20;
		if(Send_Status>0)
			Send_Status=0;
		else
			Send_Status=1;
	}
	
//UART0_SendBuf(Fx_Plc_SendBuf,9);
	
}

void FX_PLC_SendFrame(char cmd,unsigned int adder,unsigned char *dbuf,unsigned int len)//unsigned int fxdata)
{
unsigned char *pdu;
unsigned char ascii;
unsigned char sendbytelen=0;
int i;
	
	//adder*=2;
	//adder+=0x1000;
	
	pdu=Fx_Plc_SendBuf;
	
	*pdu++=0x02;
	sendbytelen++;
	*pdu++=cmd;
	sendbytelen++;
	
	
	//转换地址	
	ascii=(adder>>12)&0x0F;
	if(ascii>9)
		ascii+=0x37;
	else
		ascii+=0x30;
	*pdu++=ascii;
		sendbytelen++;
	
	ascii=(adder>>8)&0x0F;
	if(ascii>9)
		ascii+=0x37;
	else
		ascii+=0x30;
	*pdu++=ascii;
	sendbytelen++;	


	ascii=(adder>>4)&0x0F;
	if(ascii>9)
		ascii+=0x37;
	else
		ascii+=0x30;
	*pdu++=ascii;
	sendbytelen++;
	
	ascii=adder&0x0F;
	if(ascii>9)
		ascii+=0x37;
	else
		ascii+=0x30;
	*pdu++=ascii;
		sendbytelen++;
	
	//转换数据
	
	if(len>0)//发送数据命令
	{
		//加入长度
				ascii=(len>>4)&0x0F;
				if(ascii>9)
					ascii+=0x37;
				else
					ascii+=0x30;
				*pdu++=ascii;
					sendbytelen++;		
				
				ascii=(len)&0x0F;
				if(ascii>9)
					ascii+=0x37;
				else
					ascii+=0x30;
				*pdu++=ascii;
					sendbytelen++;		
		
			if(FX_Plc_Comm_Status=='W')//写入时才加载数据					
			//if(len>1)
			{
			//加入数据
			for(i=0;i<len;i++)
				{
					ascii=(dbuf[i]>>4)&0x0F;
					if(ascii>9)
						ascii+=0x37;
					else
						ascii+=0x30;
					*pdu++=ascii;
						sendbytelen++;		
					
					ascii=(dbuf[i])&0x0F;
					if(ascii>9)
						ascii+=0x37;
					else
						ascii+=0x30;
					*pdu++=ascii;
						sendbytelen++;		
				}
		}
	}
	
	*pdu++=0x03;//帧结束
	sendbytelen++;	
	
//	_getAddressAscii(27,&Fx_Plc_SendBuf[2]);
			int sum = 0;
	for (i = 1; i <= (sendbytelen-1); i++)
		sum += Fx_Plc_SendBuf[i];

	i = sum&0xFF;
	Fx_Plc_SendBuf[sendbytelen]  = _getAscii(i/16);
		sendbytelen++;
	Fx_Plc_SendBuf[sendbytelen] = _getAscii(i%16);
		sendbytelen++;
	
	Comm_FX_Plc_SendBuf(Fx_Plc_SendBuf,sendbytelen);	
}





void Comm_FX_Plc_SendStr(char *sbuf)
{
	
	
	
}


unsigned char servosendbuf[16]={0x02,0x06,0x06,0x00,0x4e,0x20 ,0xbd,0x09};
unsigned char servospeedbuf[16]={0x02 ,0x06 ,0x06 ,0x02 ,0x00 ,0x64  ,0x29 ,0x5a};

unsigned char FX_Plc_TestBuf[16]={0x01,0x05,0x33,0x27,0x00,0x01,0xB3,0x45};


void ServoSend_Test(void)
{
	
	int i;
		Comm_FX_Plc_SendBuf(FX_Plc_TestBuf,0x08);
	return;
	
	Comm_FX_Plc_SendBuf(servosendbuf,0x08);
	i=100000000;
	while(i--){};
	Comm_FX_Plc_SendBuf(servospeedbuf,0x08);
}

//#include "main.h"

void Comm_FX_Plc_SendBuf(unsigned char *sbuf,unsigned char len)
{
	int i;

	RS485_SEND();
		i=500;
	while(i--);
	UART0_SendBuf(sbuf,len);
	
	//Uart2_SendBuf(sbuf,len);
  //	UART_WAIT_TX_EMPTY(UART2);//等待发送完成
	
	//i=200;
	//while(i--);
		i=500;
	while(i--);
	RS485_RECV();

}
