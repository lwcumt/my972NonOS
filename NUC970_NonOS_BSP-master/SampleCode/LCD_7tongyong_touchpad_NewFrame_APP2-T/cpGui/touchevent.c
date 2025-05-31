#include "touchevent.h"
#include "datagui.h"

BUTTON *EventButton;
CHECKBOX *EventCheckBox;
TEXTBOX *TextBox;

unsigned char EventType;



void TouchEvent(TOUCH touch)
{
BUTTON buttemp;

touch.x-=10;
touch.y-=8;
MainForm_Event(touch);
SetupForm_Event(touch);
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
