#include "password_form.h"

#include "touchevent.h"

#include "string.h"
#include "stdio.h"
#include "stdlib.h"
#include "string.h"


//#include "tcpclient.h"
#include "drv_glcd.h"

#include "key.h"

#include "m25pe16.h"
#include "chndot.h"

#include"io.h"
#include "timer.h"

#include "pic_exec.h"

#include  "test_io.h"

#include "port.h"
#include "servo.h"
#include "name_input.h"
#include "keyboard.h"
#include "file.h"

//#include "plc_ext_form.h"



					
TEXTBOX PassWord_TextBox=
{
TextBox_Type,//unsigned char Type;
TRUE,//unsigned char Enabled;
	FALSE,//unsigned char Focus
412-112,234+78-84,//LOCATION Location;	//定位
200,28,//SIZE Size; //总大小
	0,
(255<<16)+(255<<8),//unsigned int textboxColor;
255,//unsigned int textboxSelectColor;
0,//unsigned int textColor;
(255<<16)+(255<<8),//unsigned int bkColor;	//背景色
24,//unsigned short FontWidth;//字体宽度
24,//unsigned short FontHigh;
0,//index
6,//MaxCount
""	
};


LABEL PassWord_PassCheckLabel={Label_Type,
							TRUE,
							480-112,234+48-84,
						64,24,	
						RED_COLOR,
						cSystemColor,
						24,24,
					""
					};


LABEL PassWord_FormLabel={Label_Type,
							TRUE,
							50+5,(32-24)/2+50,
						128,24,	
						0xffffff,
						255,
						24,24,
					"有效使用时间到，请输入密码！"
					};	

					BUTTON BTOk={Button_Type,\
								TRUE,
								512,548,\
								48,48,\
								(240<<16)+(240<<8)+240,\
								16,\
								32,
								"OK"};	
					
								
#define PASSWORD_FORM_SHOW 1

uint8_t Password_Form_Show_Flag=0;
								
								
uint32_t Machine_User_Count=0; //设备使用次数
					
//uint8_t Modify_Flag=0;
								
								uint8_t Machine_Set_UserCount_Flag=0;
uint32_t Machine_Set_UserCount_Time=0;
								

void Password_Form_Init(void)
{
uint16_t * totalcou;
	char tempstr[32];
	int len;
//char mfcouname[]="\\Msg\\msgcou.bin";
	
MachineUserCount_Check(); //先检查一下使用资数
	
if(PassCodeEn_flag==0)//非使用时间到，退出
		{//显示随机数	
			
			return;
		}
	
FormActive[0]=PASSWORD_FORM_SHOW;//显示 信处窗口
Password_Form_Show_Flag=1;
	
Focus=0;
	

PassWord_TextBox.Focus=FALSE;

	

CurrentArea_save1(262-112,234-84,500,300);
	
GLCD_SetWindow_Fill(262-112,234-84,262+500-1-112,234+300-1-84,cpGui_ColorChange(cSystemColor),cpGui_ColorChange(cSystemColor));//.Location.x,label.Location.y,label.Location.x+label.Size.width,label.Location.y+label.Size.high,cpGui_ColorChange(label.bkColor),cpGui_ColorChange(label.bkColor));				
GLCD_SetWindow_Fill(262-112,234-84,262+500-1-112,234+31-84,cpGui_ColorChange(255),cpGui_ColorChange(255));	

	////显示字的窗体
//GLCD_SetWindow_Fill(51,50+32+1,750-1-120,550-1,WHITE_COLOR,WHITE_COLOR);	


		
Password_Form_Label_ChangeText();	
len=strlen(PassWord_FormLabel.Text);
len*=12;

PassWord_FormLabel.Location.x=(800-len)/2;
PassWord_FormLabel.Location.y=234+4-84;

cpGui_CreateLabel(PassWord_FormLabel);


if(PassCodeEn_flag==1)
		{//显示随机数			
		GeneratePassCode();//密码生成
		sprintf(PassWord_PassCheckLabel.Text,"%d",PassCheck);
		cpGui_CreateLabel(PassWord_PassCheckLabel);	
		}
//显示 PassWord  TextBox
cpGui_CreateTextBox(&PassWord_TextBox);	

Focus=&PassWord_TextBox.Type;//获取焦点
TouchEvent_ObjSetFocus();

	BTNum0.Location.x=280+70-112;
	BTNum0.Location.y=360-84;
	cpGui_CreateButton(&BTNum0);
		
		
BTNum1.Location.x=336+70-112;
BTNum1.Location.y=360-84;
cpGui_CreateButton(&BTNum1);
	
//		cpGui_CreateButton(&Wifi_Default_Button);
//	cpGui_CreateButton(&Wifi_TXRX_Button);

	BTNum2.Location.x=392+70-112;
	BTNum2.Location.y=360-84;
		cpGui_CreateButton(&BTNum2);
	
	BTNum3.Location.x=448+70-112;
	BTNum3.Location.y=360-84;
		cpGui_CreateButton(&BTNum3);
	
	BTNum4.Location.x=504+70-112;
	BTNum4.Location.y=360-84;
	cpGui_CreateButton(&BTNum4);
		
		
	BTClear.Location.x=560+70-112;
	BTClear.Location.y=360-84;
	cpGui_CreateButton(&BTClear);


	BTNum5.Location.x=280+70-112;
	BTNum5.Location.y=420-84;		
		cpGui_CreateButton(&BTNum5);
		
		BTNum6.Location.x=336+70-112;
	BTNum6.Location.y=420-84;
		cpGui_CreateButton(&BTNum6);
		
		BTNum7.Location.x=392+70-112;
		BTNum7.Location.y=420-84;
		cpGui_CreateButton(&BTNum7);
		
		
		BTNum8.Location.x=448+70-112;
		BTNum8.Location.y=420-84;
		cpGui_CreateButton(&BTNum8);
		
		BTNum9.Location.x=504+70-112;
		BTNum9.Location.y=420-84;
		cpGui_CreateButton(&BTNum9);
		

	BTOk.Location.x=560+70-112;
	BTOk.Location.y=420-84;
	cpGui_CreateButton(&BTOk);	
	

	
OldFocus=0;
}


void Password_Form_Label_ChangeText(void)
{
int len;
//PassCodeEn_flag=0;
if(PassCodeEn_flag==0)
	{
	switch(Language)
				{
				case CHN_HAN:
				//	len=strlen("Standard use, safety first！");
				//	memcpy(PassWord_FormLabel.Text,"Standard use, safety first！",len);
				
					len=strlen("规范使用，安全第一！");
					memcpy(PassWord_FormLabel.Text,"规范使用，安全第一！",len);
					PassWord_FormLabel.Text[len]=0;
					break;
				case ENGLISH:
					len=strlen("Standard use, safety first！");
					memcpy(PassWord_FormLabel.Text,"Standard use, safety first！",len);
					PassWord_FormLabel.Text[len]=0;
					break;
				case INDONSIA:	//印尼
					len=strlen("Standard use, safety first！");
					memcpy(PassWord_FormLabel.Text,"Standard use, safety first！",len);
					PassWord_FormLabel.Text[len]=0;
					break;
				case PORTUGAL:	//葡萄牙	
					len=strlen("Standard use, safety first！");
					memcpy(PassWord_FormLabel.Text,"Standard use, safety first！",len);
					PassWord_FormLabel.Text[len]=0;
					break;
			}				
	}
	else
	{
										switch(Language)
											{
											case CHN_HAN:
												len=strlen("有效使用时间到，请输入密码!");
											  memcpy(PassWord_FormLabel.Text,"有效使用时间到，请输入密码!",len);
												PassWord_FormLabel.Text[len]=0;
												//	Printf24("有效使用时间到，请输入密码！",PASSCODE_X,PASSCODE_Y,RED_COLOR,1,0xffff);
														break;
											case ENGLISH:
												len=strlen("Your hour is up,enter passcode");
											  memcpy(PassWord_FormLabel.Text,"Your hour is up,enter passcode",len);
												PassWord_FormLabel.Text[len]=0;
											
												//	Printf24("Your hour is up,enter passcode",PASSCODE_X,PASSCODE_Y,RED_COLOR,1,0xffff);
														break;
											case INDONSIA:	//印尼
												len=strlen("Gunakan waktu untuk,Masukkan sandi Anda");
											  memcpy(PassWord_FormLabel.Text,"Gunakan waktu untuk,Masukkan sandi Anda",len);		
												PassWord_FormLabel.Text[len]=0;											
												//	Printf24("Gunakan waktu untuk,Masukkan sandi Anda",PASSCODE_X,PASSCODE_Y,RED_COLOR,1,0xffff);
														break;	
											case PORTUGAL:	//葡萄牙	
												len=strlen("Use o tempo para digitar a senha");
											  memcpy(PassWord_FormLabel.Text,"Use o tempo para digitar a senha",len);			
												PassWord_FormLabel.Text[len]=0;
													//Printf24("Use o tempo para digitar a senha",PASSCODE_X,PASSCODE_Y,RED_COLOR,1,0xffff);
														break;	
											}
										}
}



void Password_SetForm_Enter_Event(TOUCH touch)
{
	BUTTON buttemp;
int textlength;
int i;
int dotcou;
uint8_t formaterr_flag=0;
	

touch.x+=5;
touch.y+=10;	
	
	
if(WorkStart_flag==1)//if(FormActive[0]==PLC_SET_FORM_SHOW)
	{		
	
	if(touch.status==TOUCH_DOWN)
		{
		if((touch.x>=F5_BUTTON_X)&&(touch.x<F5_BUTTON_X+40)&&\
			(touch.y>=F5_BUTTON_Y)&&(touch.y<F5_BUTTON_Y+48))
			{			
////////			if(Fast_Knife_Status!=0)//换刀模式不入
////////				return;
			
			if(Run_flag==1)
					return;//电机运行时退出
				
//////			if((Manual_Knife_Status!=0)||(Motor_Knife_Status!=0))//换刀状态下不入
//////				return;
			if(WorkMode==SELF_CUT_MODE)//自刀模式不入
				return;
			if(WorkMode!=MANUAL_MODE)//非手动模式不入
				return; 
				
////////			if((Pressure_Set_Status!=0))
////////				{
////////				return;
////////				}					

////////			if((CutKnife_Set_Status!=0))
////////				{
////////					return;
////////					
////////				}
				

			
			if(Machine_Set_UserCount_Flag==0)
			{
				Machine_Set_UserCount_Flag=1;
				Machine_Set_UserCount_Time=0;
				
				BellOn_Enb();
				//Touch_code=SHIFT_8_KEY_CODE;	//F5_KEY_CODE;		//F5 20191209
				//KeyExec(Touch_code); //调键处理------------
			}
				

			
			}
			
		}
else
		{					
		if(Machine_Set_UserCount_Flag==1)
			{
				Machine_Set_UserCount_Flag=0;
				if(Machine_Set_UserCount_Time>=5000)
				{

				Touch_code=SHIFT_8_KEY_CODE;	//F5_KEY_CODE;		//F5 20191209
				KeyExec(Touch_code); //调键处理------------
				}
			Machine_Set_UserCount_Time=0;				
			}
			
		switch(EventType[FormActive[0]])
				{
				case Button_Type:
		//		buttemp=*EventButton;
				if(EventButton!=NULL)
				{
					//if(strcmp(EventButton->Text,"Default"))
				//	{
				//		WIFI_DEFAULT_HIGH();
					//}
					cpGui_Button_UpDown(EventButton,TOUCH_UP);
				}
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
	
	
}


//事件
void Password_Form_Event(TOUCH touch)
{
BUTTON buttemp;
int textlength;
int i;
int dotcou;
uint8_t formaterr_flag=0;
touch.x+=10;
	touch.y+=10;
	if(FormActive[0]==PASSWORD_FORM_SHOW)
		{
		if(touch.status==TOUCH_DOWN)
			{
			EventType[FormActive[0]]=0;
			EventButton=NULL;
			
			
		
			
	//BTNum0

		if((touch.x>=BTNum0.Location.x)&&(touch.x<BTNum0.Location.x+BTNum0.Size.width)&&\
				(touch.y>=BTNum0.Location.y)&&(touch.y<BTNum0.Location.y+BTNum0.Size.high))
			{
			BellOn_Enb();
			cpGui_Button_UpDown(&BTNum0,TOUCH_DOWN);
			EventButton=&BTNum0;
				EventType[FormActive[0]]=Button_Type;
				TouchEvent_ObjAddText("0");
			//	cpGui_TextBox_AddText(&TextBox1,"0");
			}


	//BTNum1

		if((touch.x>=BTNum1.Location.x)&&(touch.x<BTNum1.Location.x+BTNum1.Size.width)&&\
				(touch.y>=BTNum1.Location.y)&&(touch.y<BTNum1.Location.y+BTNum1.Size.high))
			{
				BellOn_Enb();
			cpGui_Button_UpDown(&BTNum1,TOUCH_DOWN);
			EventButton=&BTNum1;
				EventType[FormActive[0]]=Button_Type;
				TouchEvent_ObjAddText("1");
			//	cpGui_TextBox_AddText(&TextBox1,"1");
			}



	//BTNum2

		if((touch.x>=BTNum2.Location.x)&&(touch.x<BTNum2.Location.x+BTNum2.Size.width)&&\
				(touch.y>=BTNum2.Location.y)&&(touch.y<BTNum2.Location.y+BTNum2.Size.high))
			{
			BellOn_Enb();
			cpGui_Button_UpDown(&BTNum2,TOUCH_DOWN);
			EventButton=&BTNum2;
			EventType[FormActive[0]]=Button_Type;
			TouchEvent_ObjAddText("2");
				//cpGui_TextBox_AddText(&TextBox1,"2");
			}


	//BTNum3

		if((touch.x>=BTNum3.Location.x)&&(touch.x<BTNum3.Location.x+BTNum3.Size.width)&&\
				(touch.y>=BTNum3.Location.y)&&(touch.y<BTNum3.Location.y+BTNum3.Size.high))
			{
				BellOn_Enb();
			cpGui_Button_UpDown(&BTNum3,TOUCH_DOWN);
			EventButton=&BTNum3;
				EventType[FormActive[0]]=Button_Type;
				TouchEvent_ObjAddText("3");
			//	cpGui_TextBox_AddText(&TextBox1,"3");
			}


	//BTNum4

		if((touch.x>=BTNum4.Location.x)&&(touch.x<BTNum4.Location.x+BTNum4.Size.width)&&\
				(touch.y>=BTNum4.Location.y)&&(touch.y<BTNum4.Location.y+BTNum4.Size.high))
			{
				BellOn_Enb();
			cpGui_Button_UpDown(&BTNum4,TOUCH_DOWN);
			EventButton=&BTNum4;
				EventType[FormActive[0]]=Button_Type;
				TouchEvent_ObjAddText("4");
				//cpGui_TextBox_AddText(&TextBox1,"4");
			}


	//BTNum5

		if((touch.x>=BTNum5.Location.x)&&(touch.x<BTNum5.Location.x+BTNum5.Size.width)&&\
				(touch.y>=BTNum5.Location.y)&&(touch.y<BTNum5.Location.y+BTNum5.Size.high))
			{
			BellOn_Enb();
			cpGui_Button_UpDown(&BTNum5,TOUCH_DOWN);
			EventButton=&BTNum5;
			EventType[FormActive[0]]=Button_Type;
			TouchEvent_ObjAddText("5");
				//cpGui_TextBox_AddText(&TextBox1,"5");
			}


	//BTNum6

		if((touch.x>=BTNum6.Location.x)&&(touch.x<BTNum6.Location.x+BTNum6.Size.width)&&\
				(touch.y>=BTNum6.Location.y)&&(touch.y<BTNum6.Location.y+BTNum6.Size.high))
			{
				BellOn_Enb();
			cpGui_Button_UpDown(&BTNum6,TOUCH_DOWN);
			EventButton=&BTNum6;
				EventType[FormActive[0]]=Button_Type;
				TouchEvent_ObjAddText("6");
				//cpGui_TextBox_AddText(&TextBox1,"6");
			}



	//BTNum7

		if((touch.x>=BTNum7.Location.x)&&(touch.x<BTNum7.Location.x+BTNum7.Size.width)&&\
				(touch.y>=BTNum7.Location.y)&&(touch.y<BTNum7.Location.y+BTNum7.Size.high))
			{
				BellOn_Enb();
			cpGui_Button_UpDown(&BTNum7,TOUCH_DOWN);
			EventButton=&BTNum7;
				EventType[FormActive[0]]=Button_Type;
				TouchEvent_ObjAddText("7");
				//cpGui_TextBox_AddText(&TextBox1,"7");
			}


	//BTNum8

		if((touch.x>=BTNum8.Location.x)&&(touch.x<BTNum8.Location.x+BTNum8.Size.width)&&\
				(touch.y>=BTNum8.Location.y)&&(touch.y<BTNum8.Location.y+BTNum8.Size.high))
			{
				BellOn_Enb();
			cpGui_Button_UpDown(&BTNum8,TOUCH_DOWN);
			EventButton=&BTNum8;
				EventType[FormActive[0]]=Button_Type;
				TouchEvent_ObjAddText("8");
				//cpGui_TextBox_AddText(&TextBox1,"8");
			}


	//BTNum9

		if((touch.x>=BTNum9.Location.x)&&(touch.x<BTNum9.Location.x+BTNum9.Size.width)&&\
				(touch.y>=BTNum9.Location.y)&&(touch.y<BTNum9.Location.y+BTNum9.Size.high))
			{
				BellOn_Enb();
			cpGui_Button_UpDown(&BTNum9,TOUCH_DOWN);
			EventButton=&BTNum9;
				EventType[FormActive[0]]=Button_Type;
				TouchEvent_ObjAddText("9");
				//cpGui_TextBox_AddText(&TextBox1,"9");
			}
			
	//BTClear
		if((touch.x>=BTClear.Location.x)&&(touch.x<BTClear.Location.x+BTClear.Size.width)&&\
				(touch.y>=BTClear.Location.y)&&(touch.y<BTClear.Location.y+BTClear.Size.high))
			{
				BellOn_Enb();
			cpGui_Button_UpDown(&BTClear,TOUCH_DOWN);
			EventButton=&BTClear;
				EventType[FormActive[0]]=Button_Type;
				
				TouchEvent_ObjAddText("");
			//cpGui_ChangeText(&TextBox1.Text,"");
			//	TextBox1.Index=0;
			//cpGui_CreateTextBox(&TextBox1);
		
			}				
			
	//BTOk

		if((touch.x>=BTOk.Location.x)&&(touch.x<BTOk.Location.x+BTOk.Size.width)&&\
				(touch.y>=BTOk.Location.y)&&(touch.y<BTOk.Location.y+BTOk.Size.high))
			{
				BellOn_Enb();
				cpGui_Button_UpDown(&BTOk,TOUCH_DOWN);
				EventButton=&BTOk;
				EventType[FormActive[0]]=Button_Type;	
				
				if(PassCodeEn_flag==1)
					{					//有效时间到
						if(atoi(PassWord_TextBox.Text)==SuperPassCode)
						{//超级密码，取消使用限制
							
							Setting_User_Count[0]=0xA55A;			//超级密码	 标志位
							Setting_User_Count[1]=0x5AA5;			//超级密码	 标志位							
							SaveWorkDays();							
							
							PassCodeEn_flag=0;
							PassCheckDis_flag=0;
							
							EventButton=NULL;//&MessageBT;
							FormActive[0]=0;
							Password_Form_Show_Flag=0;
							EventType[FormActive[0]]=NULL;//Button_Type;							
							CurrentArea_recover1(262-112,234-84,500,300);	
							
						}
						else
							{
							if(atoi(PassWord_TextBox.Text)== PassCode)
							{//密码正确，退出
								
						  Setting_User_Count[1]=0; //普通密码 使用次数加1
							SaveWorkDays();									
								
							PassCodeEn_flag=0;
							PassCheckDis_flag=0;
									
													
							EventButton=NULL;//&MessageBT;
							FormActive[0]=0;
							Password_Form_Show_Flag=0;
							EventType[FormActive[0]]=NULL;//Button_Type;							
							CurrentArea_recover1(262-112,234-84,500,300);								
							}
						else
							{//不正确，清除 输入框，继续输入
								TouchEvent_ObjAddText("");
							}
						}
					}
				else
					{
					if(strcmp(PassWord_TextBox.Text,USER_PASSWORD)==0)
							{
							EventButton=NULL;//&MessageBT;
							FormActive[0]=0;
							Password_Form_Show_Flag=0;
							EventType[FormActive[0]]=NULL;//Button_Type;							
							CurrentArea_recover1(262-112,234-84,500,300);									
							}
					else
							{
								TouchEvent_ObjAddText("");
							}
					}	
			}
			

		
		
		//PassWord_TextBox
		if((touch.x>=PassWord_TextBox.Location.x)&&(touch.x<(PassWord_TextBox.Location.x+PassWord_TextBox.Size.width-8))&&\
				(touch.y>=PassWord_TextBox.Location.y)&&(touch.y<PassWord_TextBox.Location.y+PassWord_TextBox.Size.high))
			{
			BellOn_Enb();
			EventType[FormActive[0]]=TextBox_Type;
			Focus=&PassWord_TextBox.Type;
			TouchEvent_ObjSetFocus();
				//	KeyBoard_Init();
				return;
			}	
		}
		
			

	else
		{
		switch(EventType[FormActive[0]])
			{
			case Button_Type:
	//		buttemp=*EventButton;
			if(EventButton!=NULL)
			{
				//if(strcmp(EventButton->Text,"Default"))
			//	{
			//		WIFI_DEFAULT_HIGH();
				//}
				cpGui_Button_UpDown(EventButton,TOUCH_UP);
			}
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
}



