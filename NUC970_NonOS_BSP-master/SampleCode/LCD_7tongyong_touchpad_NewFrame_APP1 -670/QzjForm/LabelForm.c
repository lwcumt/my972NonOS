#include "setupform.h"


LABEL ServerLabel={Label_Type,
							TRUE,
							100,80,
						128,24,	
						0,
						None,
						24,24,
					"服务器IP："
					};	

					
TEXTBOX ServerTextBox=
{
TextBox_Type,//unsigned char Type;
TRUE,//unsigned char Enabled;
	FALSE,//unsigned char Focus
230,80,//LOCATION Location;	//定位
200,28,//SIZE Size; //总大小
(255<<16)+(255<<8),//unsigned int textboxColor;
255,//unsigned int textboxSelectColor;
0,//unsigned int textColor;
None,//unsigned int bkColor;	//背景色
24,//unsigned short FontWidth;//字体宽度
24,//unsigned short FontHigh;
0,//index
15,//MaxCount
"192.168.1.1"	
};


LABEL ServerPortLabel={Label_Type,
							TRUE,
							100,118,
						128,24,	
						0,
						None,
						24,24,
					"端口："
					};	

					
TEXTBOX ServerPortTextBox=
{
TextBox_Type,//unsigned char Type;
TRUE,//unsigned char Enabled;
	FALSE,//unsigned char Focus
230,80+1*38,//LOCATION Location;	//定位
200,28,//SIZE Size; //总大小
(255<<16)+(255<<8),//unsigned int textboxColor;
255,//unsigned int textboxSelectColor;
0,//unsigned int textColor;
None,//unsigned int bkColor;	//背景色
24,//unsigned short FontWidth;//字体宽度
24,//unsigned short FontHigh;
0,//index
4,//MaxCount
"8228"	
};



LABEL TimeYearLabel={Label_Type,
							TRUE,
							100,80+2*38,
						128,24,	
						0,
						None,
						24,24,
					"年："
					};	

					
TEXTBOX TimeYearTextBox=
{
TextBox_Type,//unsigned char Type;
TRUE,//unsigned char Enabled;
	FALSE,//unsigned char Focus
230,80+2*38,//LOCATION Location;	//定位
200,28,//SIZE Size; //总大小
(255<<16)+(255<<8),//unsigned int textboxColor;
255,//unsigned int textboxSelectColor;
0,//unsigned int textColor;
None,//unsigned int bkColor;	//背景色
24,//unsigned short FontWidth;//字体宽度
24,//unsigned short FontHigh;
0,//index
4,//MaxCount
"2017"	
};


LABEL TimeMonthLabel={Label_Type,
							TRUE,
							100,80+3*38,
						128,24,	
						0,
						None,
						24,24,
					"月："
					};	

					
TEXTBOX TimeMonthTextBox=
{
TextBox_Type,//unsigned char Type;
TRUE,//unsigned char Enabled;
FALSE,//unsigned char Focus
230,80+3*38,//LOCATION Location;	//定位
200,28,//SIZE Size; //总大小
(255<<16)+(255<<8),//unsigned int textboxColor;
255,//unsigned int textboxSelectColor;
0,//unsigned int textColor;
None,//unsigned int bkColor;	//背景色
24,//unsigned short FontWidth;//字体宽度
24,//unsigned short FontHigh;
0,//index
2,//MaxCount
"10"	
};


LABEL TimeDayLabel={Label_Type,
							TRUE,
							100,80+4*38,
						128,24,	
						0,
						None,
						24,24,
					"日："
					};	

					
TEXTBOX TimeDayTextBox=
{
TextBox_Type,//unsigned char Type;
TRUE,//unsigned char Enabled;
	FALSE,//unsigned char Focus
230,80+4*38,//LOCATION Location;	//定位
200,28,//SIZE Size; //总大小
(255<<16)+(255<<8),//unsigned int textboxColor;
255,//unsigned int textboxSelectColor;
0,//unsigned int textColor;
None,//unsigned int bkColor;	//背景色
24,//unsigned short FontWidth;//字体宽度
24,//unsigned short FontHigh;
0,//index
2,//MaxCount
"10"	
};



LABEL TimeHourLabel={Label_Type,
							TRUE,
							100,80+5*38,
						128,24,	
						0,
						None,
						24,24,
					"时："
					};	

					
TEXTBOX TimeHourTextBox=
{
TextBox_Type,//unsigned char Type;
TRUE,//unsigned char Enabled;
	FALSE,//unsigned char Focus
230,80+5*38,//LOCATION Location;	//定位
200,28,//SIZE Size; //总大小
(255<<16)+(255<<8),//unsigned int textboxColor;
255,//unsigned int textboxSelectColor;
0,//unsigned int textColor;
None,//unsigned int bkColor;	//背景色
24,//unsigned short FontWidth;//字体宽度
24,//unsigned short FontHigh;
0,//index
2,//MaxCount
"12"	
};

LABEL TimeMinuteLabel={Label_Type,
							TRUE,
							100,80+6*38,
						128,24,	
						0,
						None,
						24,24,
					"分："
					};	

					
TEXTBOX TimeMinuteTextBox=
{
TextBox_Type,//unsigned char Type;
TRUE,//unsigned char Enabled;
FALSE,//unsigned char Focus	
230,80+6*38,//LOCATION Location;	//定位
200,28,//SIZE Size; //总大小
(255<<16)+(255<<8),//unsigned int textboxColor;
255,//unsigned int textboxSelectColor;
0,//unsigned int textColor;
None,//unsigned int bkColor;	//背景色
24,//unsigned short FontWidth;//字体宽度
24,//unsigned short FontHigh;
0,//index
2,//MaxCount
"00"	
};


void SetupFormInit(void)
{
*FormActive[0]=1;
	

	
	GLCD_SetWindow_Fill(0,32,799,479,cpGui_ColorChange(cSystemColor),cpGui_ColorChange(cSystemColor));//.Location.x,label.Location.y,label.Location.x+label.Size.width,label.Location.y+label.Size.high,cpGui_ColorChange(label.bkColor),cpGui_ColorChange(label.bkColor));				
cpGui_CreateLabel(ServerLabel);
cpGui_CreateTextBox(&ServerTextBox);	
cpGui_CreateLabel(ServerPortLabel);
cpGui_CreateTextBox(&ServerPortTextBox);	


cpGui_CreateLabel(TimeYearLabel);
cpGui_CreateTextBox(&TimeYearTextBox);	

	
cpGui_CreateLabel(TimeMonthLabel);
cpGui_CreateTextBox(&TimeMonthTextBox);		
	
	cpGui_CreateLabel(TimeDayLabel);
cpGui_CreateTextBox(&TimeDayTextBox);	
	
cpGui_CreateLabel(TimeHourLabel);
cpGui_CreateTextBox(&TimeHourTextBox);	
	
cpGui_CreateLabel(TimeMinuteLabel);
cpGui_CreateTextBox(&TimeMinuteTextBox);	
	
cpGui_ChangeText(&MainFormLabel.Text,"设  置");
cpGui_CreateLabel(MainFormLabel);
	
BTNum1.Location.x=500;
	BTNum1.Location.y=80;
		cpGui_CreateButton(BTNum1);
	
	BTNum2.Location.x=556;
	BTNum2.Location.y=80;
		cpGui_CreateButton(BTNum2);
	
	BTNum3.Location.x=612;
	BTNum3.Location.y=80;
		cpGui_CreateButton(BTNum3);
	
	BTNum4.Location.x=500;
	BTNum4.Location.y=136;
	cpGui_CreateButton(BTNum4);
		
BTNum5.Location.x=556;
	BTNum5.Location.y=136;		
		cpGui_CreateButton(BTNum5);
		
		BTNum6.Location.x=612;
	BTNum6.Location.y=136;
		cpGui_CreateButton(BTNum6);
		
		BTNum7.Location.x=500;
		BTNum7.Location.y=192;
		cpGui_CreateButton(BTNum7);
		
		
		BTNum8.Location.x=556;
		BTNum8.Location.y=192;
		cpGui_CreateButton(BTNum8);
		
		BTNum9.Location.x=612;
	BTNum9.Location.y=192;
		cpGui_CreateButton(BTNum9);
		
		BTNum0.Location.x=500;
	BTNum0.Location.y=248;
		cpGui_CreateButton(BTNum0);
		
		BTDot.Location.x=556;
	BTDot.Location.y=248;
		cpGui_CreateButton(BTDot);
		
		BTClear.Location.x=612;
	BTClear.Location.y=248;
	cpGui_CreateButton(BTClear);
	
		SaveButton.Location.x=520;
	SaveButton.Location.y=248+56;
	cpGui_CreateButton(SaveButton);	
	
	
	
	FileFolderRead("Wave_64x64.bmp",(unsigned char*)START_PIC_sdram);//读开机画面
Bmp_Decode((Int32U)START_PIC_sdram, 60, 480-64-2, (pInt16U)SDRAM0_BASE_ADDR); //显示开机画面

FileFolderRead("Note_64x64.bmp",(unsigned char*)START_PIC_sdram);//读开机画面
Bmp_Decode((Int32U)START_PIC_sdram, 60+1*64+8, 480-64-2, (pInt16U)SDRAM0_BASE_ADDR); //显示开机画面

FileFolderRead("Setup_64x64.bmp",(unsigned char*)START_PIC_sdram);//读开机画面
Bmp_Decode((Int32U)START_PIC_sdram, 60+2*64+8, 480-64-2-10, (pInt16U)SDRAM0_BASE_ADDR); //显示开机画面


FileFolderRead("Net_64x64.bmp",(unsigned char*)START_PIC_sdram);//读开机画面
Bmp_Decode((Int32U)START_PIC_sdram, 60+3*64+8, 480-64-2, (pInt16U)SDRAM0_BASE_ADDR); //显示开机画面

FileFolderRead("Save_64x64.bmp",(unsigned char*)START_PIC_sdram);//读开机画面
Bmp_Decode((Int32U)START_PIC_sdram, 60+4*64+8, 480-64-2, (pInt16U)SDRAM0_BASE_ADDR); //显示开机画面

FileFolderRead("Riss_64x64.bmp",(unsigned char*)START_PIC_sdram);//读开机画面
Bmp_Decode((Int32U)START_PIC_sdram, 60+5*64+8, 480-64-2, (pInt16U)SDRAM0_BASE_ADDR); //显示开机画面

FileFolderRead("Clock_64x64.bmp",(unsigned char*)START_PIC_sdram);//读开机画面
Bmp_Decode((Int32U)START_PIC_sdram, 60+6*64+8, 480-64-2, (pInt16U)SDRAM0_BASE_ADDR); //显示开机画面

			cpGui_ChangeText(&PictureBox1.ImageName,"F1参数.bmp");
		cpGui_CreatePictureBox(&PictureBox1);
}


void SetupFormLoad(void)
{
	
	
}
