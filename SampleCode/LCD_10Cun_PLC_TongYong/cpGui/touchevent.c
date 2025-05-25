#include "touchevent.h"
#include "datagui.h"

////#include "keyborad.h"

#include "stdio.h"
#include "stdlib.h"
#include "string.h"

#include "word_lib.h"


////#include "messageform.h"
////#include "setupform.h"

#include "password_form.h"
#include "cal_form.h"


BUTTON *EventButton;
CHECKBOX *EventCheckBox;
TEXTBOX *TextBox;

unsigned char EventType[128];

unsigned char CursorEvent_Flag=FALSE;
unsigned int EventListen_Time=0;

#include "port.h"

#include "app_plc.h"
#include "App_plc_ext_form.h"

int CiShuLongDown_Time=0;

void TouchEvent(TOUCH touch)
{
BUTTON buttemp;

touch.x-=10;
touch.y-=8;
	
if(WorkStart_flag==0)
	{
	Password_Form_Event(touch);	
	}
else
	{
	
	Password_SetForm_Enter_Event(touch);
	}	
	
			if((Manual_Knife_Status==0)&&(Fast_Knife_Status==0)&&(Motor_Knife_Status==0)&&(Knife_Change_Status==0)&&(Pressure_Set_Status==0)&&(YaZhi_Process_Flag==0)&&(FX_PLC_IO_Dis_Flag==0))
				{	
				Cal_Form_Event(touch);
				}
	
			

#ifdef PLC_3U
							if((Password_Form_Show_Flag==0)&&(Cal_Form_Show_Flag==0))
						{
						Plc_Ext_Form_Event(touch);	
						}
	#endif	
	
	
////////MessageForm_Event(touch);
////////SetupForm_Event(touch);
	/*
WaveForm_Event(touch);
SetupForm_Event(touch);
NetSetForm_Event(touch);
GLForm_Event(touch);
KeyBoard_Event(touch);
	*/
}



void CiShuTouch(TOUCH touch)
{
if(touch.status==TOUCH_DOWN)
			{
		//	EventType[FormActive[0]]=0;
	//		EventButton=NULL;
			
			
		
	//长按5秒，清次数
	if(cishu>0)
				{

			if((touch.x>=MARK_LABEL_DATA_X)&&(touch.x<MARK_LABEL_DATA_X+100)&&\
					(touch.y>=MARK_LABEL_DATA_Y)&&(touch.y<MARK_LABEL_DATA_Y+60))
				{
					
					CiShuLongDown_Time++;
					if(CiShuLongDown_Time>=25)
					{
						
						CiShuLongDown_Time=0;
						cishu=0;
						cishu_old=-1;
						BellOn_Enb();
						
						SaveCiShu();//保存次数
					}

				}
			else
				CiShuLongDown_Time=0;

			}
		}		
	
	
}


void EventListen(void)
{
EventListen_Time++;
if(EventListen_Time>500)
	{
	EventListen_Time=0;
	if(CursorEvent_Flag==FALSE)
		CursorEvent_Flag=TRUE;
	else
		CursorEvent_Flag=FALSE;
	CursorEvent_Flash(CursorEvent_Flag);
	}
}


void TouchEvent_ObjSetFocus(void)
{
if(Focus!=OldFocus)
	{
	if(OldFocus==0)
		{
		switch(*Focus)
		{
				case TextBox_Type:
				TextBox=Focus;
				TextBox->Focus=TRUE;		
				cpGui_CreateTextBox(TextBox);	
						break;
		}
		}
	else
		{
		switch(*OldFocus)
		{
		case TextBox_Type:
				TextBox=OldFocus;
				TextBox->Focus=FALSE;
				cpGui_CreateTextBox(TextBox);
		
				TextBox=Focus;
				TextBox->Focus=TRUE;		
				cpGui_CreateTextBox(TextBox);
			break;
			
		}
	}
	OldFocus=Focus;		
	}
}
	
void TouchEvent_ObjAddText(char *text)
{
	if(Focus==0)
		return;
		switch(*Focus)
		{
			case Button_Type:
			EventButton=Focus;
			EventButton->Enabled=TRUE;
				break;
			case TextBox_Type:
				TextBox=Focus;
					if(*text==0)
				{
					cpGui_ChangeText(TextBox->Text,text);
				TextBox->Index=0;
				}	
			else		
				cpGui_TextBox_AddText(TextBox,text);
			cpGui_CreateTextBox(TextBox);

	//	//cpGui_CreateTextBox(&TextBox1);
				break;	
		}	
}


void TouchEvent_ObjBackspaceText()
{
	if(Focus==0)
		return;
		switch(*Focus)
		{
			case Button_Type:
			EventButton=Focus;
			EventButton->Enabled=TRUE;
				break;
			case TextBox_Type:
				TextBox=Focus;
			TextBox->Index=strlen(TextBox->Text);
				if(TextBox->Index>0)
			{
					TextBox->Index--;
		TextBox->Text[TextBox->Index]=0;
			}

/*
					if(*text==0)
				{
					cpGui_ChangeText(TextBox->Text,text);
				TextBox->Index=0;
				}	
			else		
				cpGui_TextBox_AddText(TextBox,text);

				*/

			cpGui_CreateTextBox(TextBox);

	//	//cpGui_CreateTextBox(&TextBox1);
				break;	
		}	
}

void CursorEvent_Flash(unsigned char fflag)
{
int cursorlength;
unsigned char bkflag=1;
unsigned short textstartx,textstarty;


if(Focus==0)
	return;
if(FormActive[0]==8)
{
switch(*Focus)
	{
			case Button_Type:
			EventButton=Focus;
			EventButton->Enabled=TRUE;
				break;
			case TextBox_Type:
//////				TextBox=&KeyBoradInput_TextBox;
//////			cursorlength=strlen(TextBox->Text);

//////			if(TextBox->bkColor&None)
//////			bkflag=0;
//////			switch(TextBox->FontWidth)
//////				{
//////				case 5:
//////					break;
//////				case 8:
//////					break;
//////				case 16:
//////					textstartx=TextBox->Location.x+3+cursorlength*8;
//////					textstarty=TextBox->Location.y+(TextBox->Size.high-TextBox->FontHigh)/2;
//////					if(fflag==FALSE)
//////						Printf16(" ",textstartx,textstarty,TextBox->textColor,bkflag,cpGui_ColorChange(TextBox->bkColor));
//////					else
//////						Printf16("|",textstartx,textstarty,TextBox->textColor,bkflag,cpGui_ColorChange(TextBox->bkColor));
//////					break;
//////				case 24:
//////					textstartx=TextBox->Location.x+3+cursorlength*12;
//////					textstarty=TextBox->Location.y+(TextBox->Size.high-TextBox->FontHigh)/2;
//////					if(fflag==FALSE)
//////						Printf24(" ",textstartx,textstarty,TextBox->textColor,bkflag,cpGui_ColorChange(TextBox->bkColor));
//////					else
//////						Printf24("|",textstartx,textstarty,TextBox->textColor,bkflag,cpGui_ColorChange(TextBox->bkColor));
//////					break;
//////				case 32:
//////					textstartx=TextBox->Location.x+3+cursorlength*16;
//////					textstarty=TextBox->Location.y+(TextBox->Size.high-TextBox->FontHigh)/2;
//////					if(fflag==FALSE)
//////						Printf32(" ",textstartx,textstarty,TextBox->textColor,bkflag,cpGui_ColorChange(TextBox->bkColor));
//////					else
//////						Printf32("|",textstartx,textstarty,TextBox->textColor,bkflag,cpGui_ColorChange(TextBox->bkColor));
//////					break;	
//////				}			
				
				break;

	}	
}
else
{
switch(*Focus)
	{
			case Button_Type:
			EventButton=Focus;
			EventButton->Enabled=TRUE;
				break;
			case TextBox_Type:
				TextBox=Focus;
			cursorlength=strlen(TextBox->Text);

			if(TextBox->bkColor&None)
			bkflag=0;


			switch(TextBox->FontWidth)
				{
				case 5:
					break;
				case 8:
					break;
				case 16:
					textstartx=TextBox->Location.x+3+cursorlength*8;
					textstarty=TextBox->Location.y+(TextBox->Size.high-TextBox->FontHigh)/2;
					if(fflag==FALSE)
						Printf16(" ",textstartx,textstarty,TextBox->textColor,bkflag,cpGui_ColorChange(TextBox->bkColor));
					else
						Printf16("|",textstartx,textstarty,TextBox->textColor,bkflag,cpGui_ColorChange(TextBox->bkColor));
					break;
				case 24:
					textstartx=TextBox->Location.x+3+cursorlength*12;
					textstarty=TextBox->Location.y+(TextBox->Size.high-TextBox->FontHigh)/2;
					if(fflag==FALSE)
						Printf24(" ",textstartx,textstarty,TextBox->textColor,bkflag,cpGui_ColorChange(TextBox->bkColor));
					else
						Printf24("|",textstartx,textstarty,TextBox->textColor,bkflag,cpGui_ColorChange(TextBox->bkColor));
					break;
				case 32:
					textstartx=TextBox->Location.x+3+cursorlength*16;
					textstarty=TextBox->Location.y+(TextBox->Size.high-TextBox->FontHigh)/2;
					if(fflag==FALSE)
						Printf32(" ",textstartx,textstarty,TextBox->textColor,bkflag,cpGui_ColorChange(TextBox->bkColor));
					else
						Printf32("|",textstartx,textstarty,TextBox->textColor,bkflag,cpGui_ColorChange(TextBox->bkColor));
					break;	
				}			
				
				break;

	}
}
}