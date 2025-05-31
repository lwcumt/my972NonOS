#include "mainform.h"


#include "touchevent.h"


unsigned char SecTemp2;
unsigned int Ms100tt5;

PICTUREBOX F1_PictureBox=
{
PictureBox_Type,//unsigned char Type;
TRUE,//unsigned char Enabled;
TRUE,
FALSE,//unsigned char Focus
10,200,//LOCATION Location;	//定位
48,48,//SIZE Size; //总大小
(255<<16)+(255<<8),//unsigned int picturebkColor;
255,//unsigned int textboxSelectColor;
0,//unsigned int textColor;
None,//unsigned int textbkColor;	//背景色
16,//unsigned short FontWidth;//字体宽度
16,//unsigned short FontHigh;
0,//index
6,//MaxCount
"textbox1",
"F1up.bmp",
F1_LABELS_UP_sdram
};



PICTUREBOX F2_PictureBox=
{
PictureBox_Type,//unsigned char Type;
TRUE,//unsigned char Enabled;
TRUE,
FALSE,//unsigned char Focus
10,200+1*48,//LOCATION Location;	//定位
48,48,//SIZE Size; //总大小
(255<<16)+(255<<8),//unsigned int picturebkColor;
255,//unsigned int textboxSelectColor;
0,//unsigned int textColor;
None,//unsigned int textbkColor;	//背景色
16,//unsigned short FontWidth;//字体宽度
16,//unsigned short FontHigh;
0,//index
6,//MaxCount
"textbox1",
"F2up.bmp",
F1_LABELS_UP_sdram	
};


PICTUREBOX F3_PictureBox=
{
PictureBox_Type,//unsigned char Type;
TRUE,//unsigned char Enabled;
TRUE,
FALSE,//unsigned char Focus
10,200+2*48,//LOCATION Location;	//定位
48,48,//SIZE Size; //总大小
(255<<16)+(255<<8),//unsigned int picturebkColor;
255,//unsigned int textboxSelectColor;
0,//unsigned int textColor;
None,//unsigned int textbkColor;	//背景色
16,//unsigned short FontWidth;//字体宽度
16,//unsigned short FontHigh;
0,//index
6,//MaxCount
"textbox1",
"F3up.bmp",
F1_LABELS_UP_sdram	
};


PICTUREBOX F4_PictureBox=
{
PictureBox_Type,//unsigned char Type;
TRUE,//unsigned char Enabled;
TRUE,
FALSE,//unsigned char Focus
10,200+3*48,//LOCATION Location;	//定位
48,48,//SIZE Size; //总大小
(255<<16)+(255<<8),//unsigned int picturebkColor;
255,//unsigned int textboxSelectColor;
0,//unsigned int textColor;
None,//unsigned int textbkColor;	//背景色
16,//unsigned short FontWidth;//字体宽度
16,//unsigned short FontHigh;
0,//index
6,//MaxCount
"textbox1",
"F4up.bmp",
F1_LABELS_UP_sdram
};


PICTUREBOX F5_PictureBox=
{
PictureBox_Type,//unsigned char Type;
TRUE,//unsigned char Enabled;
TRUE,
FALSE,//unsigned char Focus
10,200+4*48,//LOCATION Location;	//定位
48,48,//SIZE Size; //总大小
(255<<16)+(255<<8),//unsigned int picturebkColor;
255,//unsigned int textboxSelectColor;
0,//unsigned int textColor;
None,//unsigned int textbkColor;	//背景色
16,//unsigned short FontWidth;//字体宽度
16,//unsigned short FontHigh;
0,//index
6,//MaxCount
"textbox1",
"F5压纸循环.bmp",
F1_LABELS_UP_sdram
};


PICTUREBOX F6_PictureBox=
{
PictureBox_Type,//unsigned char Type;
TRUE,//unsigned char Enabled;
TRUE,
FALSE,//unsigned char Focus
10,200+5*48,//LOCATION Location;	//定位
48,48,//SIZE Size; //总大小
(255<<16)+(255<<8),//unsigned int picturebkColor;
255,//unsigned int textboxSelectColor;
0,//unsigned int textColor;
None,//unsigned int textbkColor;	//背景色
16,//unsigned short FontWidth;//字体宽度
16,//unsigned short FontHigh;
0,//index
6,//MaxCount
"textbox1",
"F1标签.bmp",
F1_LABELS_UP_sdram
};


void MainFormInit(void)
{
//*FormActive[0]=3;	
ReadFiles();
cpGui_CreatePictureBox(&F1_PictureBox);
cpGui_CreatePictureBox(&F2_PictureBox);
cpGui_CreatePictureBox(&F3_PictureBox);
cpGui_CreatePictureBox(&F4_PictureBox);
cpGui_CreatePictureBox(&F5_PictureBox);
}


void MainFormLoad(void)
{
	
	
}


void Test_Main(void)
{
int n;
	Timer0Init();
FileFolderRead("Power.bmp",(unsigned char*)START_PIC_sdram);//?????
		Bmp_Decode((Int32U)START_PIC_sdram, 0, 0, (pInt16U)SDRAM0_BASE_ADDR); //??????
		
		
		
		FileRead("??_0x20000.FON",(unsigned char *)df_zk_sdram);//		

		 n=1000000;
		while(n--);
				 n=1000000;
		while(n--);
				 n=1000000;
		while(n--);
				 n=1000000;
		while(n--);
				 n=1000000;
		while(n--);
				 n=1000000;
		while(n--);
		
		chart1.Location.x=100;
		chart1.Location.y=50;		
		chart1.Size.width=566;
		chart1.Size.high=286;
		chart1.RowData=100;
		chart1.RowStep=5;
		chart1.ColData=10;
		chart1.ColStep=10;
		
		GLCD_SetWindow_Fill(0,0,799,31,cpGui_ColorChange(255),cpGui_ColorChange(255));
		GLCD_SetWindow_Fill(0,32,799,599,cpGui_ColorChange(cSystemColor),cpGui_ColorChange(cSystemColor));//.Location.x,label.Location.y,label.Location.x+label.Size.width,label.Location.y+label.Size.high,cpGui_ColorChange(label.bkColor),cpGui_ColorChange(label.bkColor));				
		cpGui_CreateLabel(MainFormLabel);
	
		WaveFormInit();
		MainFormInit();
		
while(1)
		{
	//	Modbus_Run_Main();
		if(Ms_Flag==1)
			{
			Ms_Flag=0;
			
				
					 //************????????
         Ms100tt5++;
         if(Ms100tt5>=200)
             {
             Ms100tt5=0;
						 read_time();
						 RealTime_Dis();
             } 
						 
						 
						 /*
						 
				ModbusAutoSendTime++;
				if(ModbusAutoSendTime>500)
				{
					ModbusAutoSendTime=0;				
				}				
			else
				{
				switch(ModbusAutoSendTime)
					{
					case 100:
						Old_Add=CURD_ADD;
			//		Printf24("CURD_ADD",200,400,BLACK_COLOR,1,BLUE_COLOR);
						ModBus_SendFrame(0x01,MODBUS_COMMAND_REGISTER_READ,Old_Add,1);
						break;
					case 200:
						Old_Add=VLOTD_ADD;
				//	Printf24("VLOTD_ADD",200,400,BLACK_COLOR,1,BLUE_COLOR);
						ModBus_SendFrame(0x01,MODBUS_COMMAND_REGISTER_READ,Old_Add,1);
						ModbusAutoSendTime=0;
						break;								
					}			
				}
				*/
				
	//  if(Touch_code==0)
	//	Keyboard_scan();	

		#ifdef CAP_TOUCH
		
////		if(KeyboardDown_flag==0)
					GtpCheckTime++;
		if(GtpCheckTime>15)
		  {
			GtpCheckTime=0;
	//	 if(KeyboardDown_flag==0)
			//		{
				//	Printf24("Gtp_Touch_Scan()",200,400,BLACK_COLOR,1,BLUE_COLOR);//,label.Location.y,label.textColor,bkflag,cpGui_ColorChange(label.bkColor));
					Gtp_Touch_Scan();//?????
				//		Printf24("Gtp_Touch_STOP()",200,400,BLACK_COLOR,1,BLUE_COLOR);
			//		}
			//GT911_Scan_OLD(0);
		  }

				 
		#else
			if(KeyDown_Flag==0)
			// ToucScan(); 
			TouchScan_Uart(); //????				
		#endif
		
    //  ShiftKeyExec();//
			
			}
		
			
		//CheckOp_IN();
//		read_time();
		}
}


void RealTime_Dis(void)
{
	if(Sec!=SecTemp2)
	{
	SecTemp2=Sec;
   Bcd[0]=2+48;
   Bcd[1]=0+48;
   Bcd[2]=(Year>>4)+48;
   Bcd[3]=(Year&0xf)+48;
	 Bcd[4]='-';

   Bcd[5]=(Month>>4)+48;
   Bcd[6]=(Month&0xf)+48;

	 Bcd[7]='-';
   Bcd[8]=(Dom>>4)+48;
   Bcd[9]=(Dom&0xf)+48;

	 Bcd[10]='-';
   Bcd[11]=(Hour>>4)+48;
   Bcd[12]=(Hour&0xf)+48;

		Bcd[13]=':';
   Bcd[14]=(Min>>4)+48;
   Bcd[15]=(Min&0xf)+48;
	 Bcd[16]=':';
   Bcd[17]=(Sec>>4)+48;
   Bcd[18]=(Sec&0xf)+48;
	 Bcd[19]=0;
	 
		cpGui_ChangeText(&TimeLabel.Text,Bcd);
		//Label1.bkColor=cSystemColor;
		cpGui_CreateLabel(TimeLabel);	 
 }	 
}


void MainForm_Event(TOUCH touch)
{
BUTTON buttemp;

touch.x-=10;
touch.y-=8;

if(*FormActive[0]==2)
	{
	if(touch.status==TOUCH_DOWN)
		{
		EventType=0;
		if((touch.x>=60+2*64+8)&&(touch.x<60+3*64+8)&&\
			(touch.y>=480-64-2)&&(touch.y<480-2))
			{
			 SetupFormInit();
			}
	}
	
else
	{
	switch(EventType)
		{
		case Button_Type:
		buttemp=*EventButton;
		cpGui_Button_UpDown(buttemp,TOUCH_UP);
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
////if(EventType==0)
////	Focus=0;
}
