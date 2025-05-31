#include "setupform.h"
#include "touchevent.h"


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


void SetupForm_Event(TOUCH touch)
{
BUTTON buttemp;

	if(*FormActive[0]==1)
	{


if(touch.status==TOUCH_DOWN)
	{
	EventType=0;



	if((touch.x>=60)&&(touch.x<60+1*64)&&\
			(touch.y>=480-64-2)&&(touch.y<480-2))
		{
		 WaveFormInit();
		}
		
//BTNum0

	if((touch.x>=BTNum0.Location.x)&&(touch.x<BTNum0.Location.x+BTNum0.Size.width)&&\
			(touch.y>=BTNum0.Location.y)&&(touch.y<BTNum0.Location.y+BTNum0.Size.high))
		{
		cpGui_Button_UpDown(BTNum0,TOUCH_DOWN);
		*EventButton=BTNum0;
			EventType=Button_Type;
			TouchEvent_ObjAddText("0");
		//	cpGui_TextBox_AddText(&TextBox1,"0");
		}


//BTNum1

	if((touch.x>=BTNum1.Location.x)&&(touch.x<BTNum1.Location.x+BTNum1.Size.width)&&\
			(touch.y>=BTNum1.Location.y)&&(touch.y<BTNum1.Location.y+BTNum1.Size.high))
		{
		cpGui_Button_UpDown(BTNum1,TOUCH_DOWN);
		*EventButton=BTNum1;
			EventType=Button_Type;
			TouchEvent_ObjAddText("1");
		//	cpGui_TextBox_AddText(&TextBox1,"1");
		}



//BTNum2

	if((touch.x>=BTNum2.Location.x)&&(touch.x<BTNum2.Location.x+BTNum2.Size.width)&&\
			(touch.y>=BTNum2.Location.y)&&(touch.y<BTNum2.Location.y+BTNum2.Size.high))
		{
		cpGui_Button_UpDown(BTNum2,TOUCH_DOWN);
		*EventButton=BTNum2;
			EventType=Button_Type;
			TouchEvent_ObjAddText("2");
			//cpGui_TextBox_AddText(&TextBox1,"2");
		}


//BTNum3

	if((touch.x>=BTNum3.Location.x)&&(touch.x<BTNum3.Location.x+BTNum3.Size.width)&&\
			(touch.y>=BTNum3.Location.y)&&(touch.y<BTNum3.Location.y+BTNum3.Size.high))
		{
		cpGui_Button_UpDown(BTNum3,TOUCH_DOWN);
		*EventButton=BTNum3;
			EventType=Button_Type;
			TouchEvent_ObjAddText("3");
		//	cpGui_TextBox_AddText(&TextBox1,"3");
		}


//BTNum4

	if((touch.x>=BTNum4.Location.x)&&(touch.x<BTNum4.Location.x+BTNum4.Size.width)&&\
			(touch.y>=BTNum4.Location.y)&&(touch.y<BTNum4.Location.y+BTNum4.Size.high))
		{
		cpGui_Button_UpDown(BTNum4,TOUCH_DOWN);
		*EventButton=BTNum4;
			EventType=Button_Type;
			TouchEvent_ObjAddText("4");
			//cpGui_TextBox_AddText(&TextBox1,"4");
		}


//BTNum5

	if((touch.x>=BTNum5.Location.x)&&(touch.x<BTNum5.Location.x+BTNum5.Size.width)&&\
			(touch.y>=BTNum5.Location.y)&&(touch.y<BTNum5.Location.y+BTNum5.Size.high))
		{
		cpGui_Button_UpDown(BTNum5,TOUCH_DOWN);
		*EventButton=BTNum5;
			EventType=Button_Type;
			TouchEvent_ObjAddText("5");
			//cpGui_TextBox_AddText(&TextBox1,"5");
		}


//BTNum6

	if((touch.x>=BTNum6.Location.x)&&(touch.x<BTNum6.Location.x+BTNum6.Size.width)&&\
			(touch.y>=BTNum6.Location.y)&&(touch.y<BTNum6.Location.y+BTNum6.Size.high))
		{
		cpGui_Button_UpDown(BTNum6,TOUCH_DOWN);
		*EventButton=BTNum6;
			EventType=Button_Type;
			TouchEvent_ObjAddText("6");
			//cpGui_TextBox_AddText(&TextBox1,"6");
		}



//BTNum7

	if((touch.x>=BTNum7.Location.x)&&(touch.x<BTNum7.Location.x+BTNum7.Size.width)&&\
			(touch.y>=BTNum7.Location.y)&&(touch.y<BTNum7.Location.y+BTNum7.Size.high))
		{
		cpGui_Button_UpDown(BTNum7,TOUCH_DOWN);
		*EventButton=BTNum7;
			EventType=Button_Type;
			TouchEvent_ObjAddText("7");
			//cpGui_TextBox_AddText(&TextBox1,"7");
		}


//BTNum8

	if((touch.x>=BTNum8.Location.x)&&(touch.x<BTNum8.Location.x+BTNum8.Size.width)&&\
			(touch.y>=BTNum8.Location.y)&&(touch.y<BTNum8.Location.y+BTNum8.Size.high))
		{
		cpGui_Button_UpDown(BTNum8,TOUCH_DOWN);
		*EventButton=BTNum8;
			EventType=Button_Type;
			TouchEvent_ObjAddText("8");
			//cpGui_TextBox_AddText(&TextBox1,"8");
		}


//BTNum9

	if((touch.x>=BTNum9.Location.x)&&(touch.x<BTNum9.Location.x+BTNum9.Size.width)&&\
			(touch.y>=BTNum9.Location.y)&&(touch.y<BTNum9.Location.y+BTNum9.Size.high))
		{
		cpGui_Button_UpDown(BTNum9,TOUCH_DOWN);
		*EventButton=BTNum9;
			EventType=Button_Type;
			TouchEvent_ObjAddText("9");
			//cpGui_TextBox_AddText(&TextBox1,"9");
		}
		
//BTDot

	if((touch.x>=BTDot.Location.x)&&(touch.x<BTDot.Location.x+BTDot.Size.width)&&\
			(touch.y>=BTDot.Location.y)&&(touch.y<BTDot.Location.y+BTDot.Size.high))
		{
		cpGui_Button_UpDown(BTDot,TOUCH_DOWN);
		*EventButton=BTDot;
			EventType=Button_Type;
			TouchEvent_ObjAddText(".");
			//cpGui_TextBox_AddText(&TextBox1,".");
		}
		
//BTClear
	if((touch.x>=BTClear.Location.x)&&(touch.x<BTClear.Location.x+BTClear.Size.width)&&\
			(touch.y>=BTClear.Location.y)&&(touch.y<BTClear.Location.y+BTClear.Size.high))
		{
		cpGui_Button_UpDown(BTClear,TOUCH_DOWN);
		*EventButton=BTClear;
			EventType=Button_Type;
			
			TouchEvent_ObjAddText("");
		//cpGui_ChangeText(&TextBox1.Text,"");
		//	TextBox1.Index=0;
		//cpGui_CreateTextBox(&TextBox1);
	
		}		
		
		//SaveButton
	if((touch.x>=SaveButton.Location.x)&&(touch.x<SaveButton.Location.x+SaveButton.Size.width)&&\
			(touch.y>=SaveButton.Location.y)&&(touch.y<SaveButton.Location.y+SaveButton.Size.high))
		{
		cpGui_Button_UpDown(SaveButton,TOUCH_DOWN);
		*EventButton=SaveButton;
		EventType=Button_Type;
		
		Min=(TimeMinuteTextBox.Text[0]-0x30)<<4;			
		Min+=(TimeMinuteTextBox.Text[1]-0x30);
		Hour=(TimeHourTextBox.Text[0]-0x30)<<4;
		Hour+=(TimeHourTextBox.Text[1]-0x30);
		Dom=(TimeDayTextBox.Text[0]-0x30)<<4;
		Dom+=(TimeDayTextBox.Text[1]-0x30);		
		Month=(TimeMonthTextBox.Text[0]-0x30)<<4;
		Month+=(TimeMonthTextBox.Text[1]-0x30);
		Year=(TimeYearTextBox.Text[2]-0x30)<<4;
		Year+=(TimeYearTextBox.Text[3]-0x30);
		write_time();
		
		//cpGui_ChangeText(&TextBox1.Text,"");
		//	TextBox1.Index=0;
		//cpGui_CreateTextBox(&TextBox1);	
		}		
		
	//CheckBox1
	if((touch.x>=CheckBox1.Location.x)&&(touch.x<(CheckBox1.Location.x+CheckBox1.Size.width-8))&&\
			(touch.y>=CheckBox1.Location.y)&&(touch.y<CheckBox1.Location.y+CheckBox1.Size.high))
		{
		if(CheckBox1.Checked==FALSE)
			CheckBox1.Checked=TRUE;
		else
			CheckBox1.Checked=FALSE;			
		cpGui_CreateCheckBox(CheckBox1);
////////		*EventCheckBox=CheckBox1;
		EventType=CheckBox_Type;
		}		
		
	//RadioButton1
	if((touch.x>=RadioButton1.Location.x)&&(touch.x<(RadioButton1.Location.x+RadioButton1.Size.width-8))&&\
			(touch.y>=RadioButton1.Location.y)&&(touch.y<RadioButton1.Location.y+RadioButton1.Size.high))
		{
		if(RadioButton1.Checked==FALSE)
			RadioButton1.Checked=TRUE;
		else
			RadioButton1.Checked=FALSE;			
		cpGui_CreateRadioButton(RadioButton1);
////////		*EventCheckBox=CheckBox1;
		EventType=RadioButton_Type;
		}			
		
	//ServerTextBox
	if((touch.x>=ServerTextBox.Location.x)&&(touch.x<(ServerTextBox.Location.x+ServerTextBox.Size.width-8))&&\
			(touch.y>=ServerTextBox.Location.y)&&(touch.y<ServerTextBox.Location.y+ServerTextBox.Size.high))
		{
		EventType=TextBox_Type;
		Focus=&ServerTextBox.Type;
		TouchEvent_ObjSetFocus();
		}	
	//ServerPortTextBox
	if((touch.x>=ServerPortTextBox.Location.x)&&(touch.x<(ServerPortTextBox.Location.x+ServerPortTextBox.Size.width-8))&&\
			(touch.y>=ServerPortTextBox.Location.y)&&(touch.y<ServerPortTextBox.Location.y+ServerPortTextBox.Size.high))
		{
		EventType=TextBox_Type;
		Focus=&ServerPortTextBox.Type;
		TouchEvent_ObjSetFocus();
		}	
		
		
	//TimeYearTextBox
	if((touch.x>=TimeYearTextBox.Location.x)&&(touch.x<(TimeYearTextBox.Location.x+TimeYearTextBox.Size.width-8))&&\
			(touch.y>=TimeYearTextBox.Location.y)&&(touch.y<TimeYearTextBox.Location.y+TimeYearTextBox.Size.high))
		{
		EventType=TextBox_Type;
		Focus=&TimeYearTextBox.Type;
			TouchEvent_ObjSetFocus();
		}	
					//TimeMonthTextBox
	if((touch.x>=TimeMonthTextBox.Location.x)&&(touch.x<(TimeMonthTextBox.Location.x+TimeMonthTextBox.Size.width-8))&&\
			(touch.y>=TimeMonthTextBox.Location.y)&&(touch.y<TimeMonthTextBox.Location.y+TimeMonthTextBox.Size.high))
		{
		EventType=TextBox_Type;
		Focus=&TimeMonthTextBox.Type;
			TouchEvent_ObjSetFocus();
		}	
	//TimeDayTextBox
	if((touch.x>=TimeDayTextBox.Location.x)&&(touch.x<(TimeDayTextBox.Location.x+TimeDayTextBox.Size.width-8))&&\
			(touch.y>=TimeDayTextBox.Location.y)&&(touch.y<TimeDayTextBox.Location.y+TimeDayTextBox.Size.high))
		{
		EventType=TextBox_Type;
		Focus=&TimeDayTextBox.Type;
			TouchEvent_ObjSetFocus();
		}	
		
		
	//TimeHourTextBox
	if((touch.x>=TimeHourTextBox.Location.x)&&(touch.x<(TimeHourTextBox.Location.x+TimeHourTextBox.Size.width-8))&&\
			(touch.y>=TimeHourTextBox.Location.y)&&(touch.y<TimeHourTextBox.Location.y+TimeHourTextBox.Size.high))
		{
		EventType=TextBox_Type;
		Focus=&TimeHourTextBox.Type;
			TouchEvent_ObjSetFocus();
		}		
		
		//TimeMinuteTextBox
	if((touch.x>=TimeMinuteTextBox.Location.x)&&(touch.x<(TimeMinuteTextBox.Location.x+TimeMinuteTextBox.Size.width-8))&&\
			(touch.y>=TimeMinuteTextBox.Location.y)&&(touch.y<TimeMinuteTextBox.Location.y+TimeMinuteTextBox.Size.high))
		{
		EventType=TextBox_Type;
		Focus=&TimeMinuteTextBox.Type;
			TouchEvent_ObjSetFocus();
		}			
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

////if(EventType==0)
////	Focus=0;
}
