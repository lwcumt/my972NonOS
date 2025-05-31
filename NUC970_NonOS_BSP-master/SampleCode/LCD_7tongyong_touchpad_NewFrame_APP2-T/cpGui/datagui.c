#include "datagui.h"

#include "drv_glcd.h"
#include "word_lib.h"


#include "gpio.h"
#include "drv_glcd.h"
#include "chndot.h"

#include "string.h"


unsigned char *Focus; 
unsigned char *OldFocus;
unsigned char *FormActive[128];



								
BUTTON Button1={Button_Type,\
								TRUE,
								50,400,\
								120,36,\
								(240<<16)+(240<<8)+240,\
								16,\
								32,
								"OK"};
	
BUTTON Button2={Button_Type,\
								TRUE,
								180,400,\
								120,36,\
								(240<<16)+(240<<8)+240,\
								16,\
								32,
								"Cancel"};								
								

								
BUTTON SaveButton={Button_Type,\
								TRUE,
								50,400,\
								100,36,\
								(240<<16)+(240<<8)+240,\
								16,\
								32,
								"Save"};

BUTTON BTNum1={Button_Type,\
								TRUE,
								400,380,\
								48,48,\
								(240<<16)+(240<<8)+240,\
								16,\
								32,
								"1"};	

BUTTON BTNum2={Button_Type,\
								TRUE,
								456,380,\
								48,48,\
								(240<<16)+(240<<8)+240,\
								16,\
								32,
								"2"};	

BUTTON BTNum3={Button_Type,\
								TRUE,
								512,380,\
								48,48,\
								(240<<16)+(240<<8)+240,\
								16,\
								32,
								"3"};	
BUTTON BTNum4={Button_Type,\
								TRUE,
								400,436,\
								48,48,\
								(240<<16)+(240<<8)+240,\
								16,\
								32,
								"4"};	

BUTTON BTNum5={Button_Type,\
								TRUE,
								456,436,\
								48,48,\
								(240<<16)+(240<<8)+240,\
								16,\
								32,
								"5"};	
BUTTON BTNum6={Button_Type,\
								TRUE,
								512,436,\
								48,48,\
								(240<<16)+(240<<8)+240,\
								16,\
								32,
								"6"};	
BUTTON BTNum7={Button_Type,\
								TRUE,
								400,492,\
								48,48,\
								(240<<16)+(240<<8)+240,\
								16,\
								32,
								"7"};	


BUTTON BTNum8={Button_Type,\
								TRUE,
								456,492,\
								48,48,\
								(240<<16)+(240<<8)+240,\
								16,\
								32,
								"8"};	


BUTTON BTNum9={Button_Type,\
								TRUE,
								512,492,\
								48,48,\
								(240<<16)+(240<<8)+240,\
								16,\
								32,
								"9"};	

BUTTON BTClear={Button_Type,\
								TRUE,
								400,548,\
								48,48,\
								(240<<16)+(240<<8)+240,\
								16,\
								32,
								"C"};	
					
BUTTON BTNum0={Button_Type,\
								TRUE,
								456,548,\
								48,48,\
								(240<<16)+(240<<8)+240,\
								16,\
								32,
								"0"};	

BUTTON BTDot={Button_Type,\
								TRUE,
								512,548,\
								48,48,\
								(240<<16)+(240<<8)+240,\
								16,\
								32,
								"."};									
								
LABEL Label1={Label_Type,
							TRUE,
							10,500,
						6*24,24,
						0,
						None,
						24,24,
						"Label1"
					};
	
LABEL TimeLabel={Label_Type,
							TRUE,
							800-15*16,(32-24)/2,
						15*16+8,24,	
						0xffffff,
						255,
						24,24,
					"22:22:22"
					};					
					
LABEL MainFormLabel={Label_Type,
							TRUE,
							10,(32-24)/2,
						128,24,	
						0xffffff,
						255,
						24,24,
					"Home"
					};	

					
CHECKBOX CheckBox1={
CheckBox_Type,//unsigned char Type;
TRUE,//unsigned char Enabled;
10,340,//LOCATION Location;	//定位
90,24,//SIZE Size; //总大小
(240<<16)+(240<<8)+240, //unsigned int checkBoxColor;
(250<<16)+250,//unsigned int checkBoxSelectColor;
0,//unsigned int textColor;
cSystemColor,//unsigned int bkColor;	//背景色
16,//unsigned short FontWidth;//字体宽度
16,//unsigned short FontHigh;
	FALSE,
"CheckBox"//char Text[32];	
};	
		

RADIOBUTTON RadioButton1=
{
RadioButton_Type,//unsigned char Type;
TRUE,//unsigned char Enabled;
150,340,//LOCATION Location;	//定位
90,32,//SIZE Size; //总大小
(240<<16)+(240<<8)+240, //unsigned int checkBoxColor;
(250<<16)+250,//unsigned int checkBoxSelectColor;
0,//unsigned int textColor;
cSystemColor,//unsigned int bkColor;	//背景色
24,//unsigned short FontWidth;//字体宽度
24,//unsigned short FontHigh;
FALSE,
"RadioBut"//char Text[32];		
};


TEXTBOX TextBox1=
{
TextBox_Type,//unsigned char Type;
TRUE,//unsigned char Enabled;
FALSE,//unsigned char Focus
200,200,//LOCATION Location;	//定位
100,20,//SIZE Size; //总大小
(255<<16)+(255<<8),//unsigned int textboxColor;
255,//unsigned int textboxSelectColor;
0,//unsigned int textColor;
None,//unsigned int bkColor;	//背景色
16,//unsigned short FontWidth;//字体宽度
16,//unsigned short FontHigh;
0,//index
6,//MaxCount
"textbox1"	
};


PICTUREBOX PictureBox1=
{
PictureBox_Type,//unsigned char Type;
TRUE,//unsigned char Enabled;
TRUE,
FALSE,//unsigned char Focus
10,200,//LOCATION Location;	//定位
35,42,//SIZE Size; //总大小
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
(unsigned int *)F1UP_sdram
};


void Ascii_Printf1632(unsigned char *ct,unsigned short x,unsigned short y,unsigned short tcolor,unsigned short bcolor)
{	
ASCII_Printf(ct,ASCII1632_MODE,ASCII1632_WIDTH,ASCII1632_HIGH,ASCII1632,x,y,tcolor,bcolor); 	
}


void Ascii_Printf1632_OneChar_NoFill(unsigned char *ct,unsigned short x,unsigned short y,unsigned short tcolor)
{	
ASCII_Printf_OneChar_NoFill(ct,ASCII1632_MODE,ASCII1632_WIDTH,ASCII1632_HIGH,ASCII1632,x,y,tcolor); 	
}

void cpGui_ChangeText(char *type,char *text)
{
while(*text!=0)
{
*type=*text++;
	type++;
}
*type=0;
}



unsigned short cpGui_ColorChange(unsigned int color)
{
 unsigned short color16b=0;
	unsigned char r,g,b;
	r=color>>16;
	g=color>>8;
	b=color;
	r>>=3;
	g>>=2;
	b>>=3;
	color16b=r;
	color16b<<=6;	
	color16b|=g;
	color16b<<=5;
	color16b|=b;
	return color16b;
}

void cpGui_CreateCheckBox(CHECKBOX checkbox)
{
unsigned short bcolor;
unsigned char bkflag=1;
unsigned short ty_step;
if(checkbox.bkColor&None)
	bkflag=0;
else
	GLCD_SetWindow_Fill(checkbox.Location.x,checkbox.Location.y,checkbox.Location.x+checkbox.Size.width,checkbox.Location.y+checkbox.Size.high,cpGui_ColorChange(checkbox.bkColor),cpGui_ColorChange(checkbox.bkColor));	

if(checkbox.Checked==FALSE)
{
GLCD_SetWindow_Fill(checkbox.Location.x+2,checkbox.Location.y+2,checkbox.Location.x+checkbox.Size.high-2,checkbox.Location.y+checkbox.Size.high-2,BLACK_COLOR,cpGui_ColorChange(checkbox.checkBoxColor));
	
bcolor=cpGui_ColorChange(checkbox.checkBoxColor);
//GLCD_Circle_Fill(checkbox.Location.x+checkbox.Size.high/2-2,checkbox.Location.y+checkbox.Size.high/2,checkbox.Size.high/2-2,BLACK_COLOR,cpGui_ColorChange(checkbox.checkBoxColor));
bcolor=cpGui_ColorChange(checkbox.checkBoxColor-0x181818);	
GLCD_SetWindow_Fill(checkbox.Location.x+2+2,checkbox.Location.y+2+2,checkbox.Location.x+checkbox.Size.high-2-2,checkbox.Location.y+checkbox.Size.high-2-2,bcolor,bcolor);
bcolor=cpGui_ColorChange(checkbox.checkBoxColor-0x252525);	
GLCD_SetWindow_Fill(checkbox.Location.x+2+4,checkbox.Location.y+2+4,checkbox.Location.x+checkbox.Size.high-2-4,checkbox.Location.y+checkbox.Size.high-2-4,bcolor,bcolor);
}
else
{
GLCD_SetWindow_Fill(checkbox.Location.x+2,checkbox.Location.y+2,checkbox.Location.x+checkbox.Size.high-2,checkbox.Location.y+checkbox.Size.high-2,BLACK_COLOR,cpGui_ColorChange(checkbox.checkBoxColor));
	
bcolor=cpGui_ColorChange(checkbox.checkBoxColor);
//GLCD_Circle_Fill(checkbox.Location.x+checkbox.Size.high/2-2,checkbox.Location.y+checkbox.Size.high/2,checkbox.Size.high/2-2,BLACK_COLOR,cpGui_ColorChange(checkbox.checkBoxColor));
bcolor=cpGui_ColorChange(checkbox.checkBoxColor-0x181818);	
GLCD_SetWindow_Fill(checkbox.Location.x+2+2,checkbox.Location.y+2+2,checkbox.Location.x+checkbox.Size.high-2-2,checkbox.Location.y+checkbox.Size.high-2-2,bcolor,bcolor);
bcolor=cpGui_ColorChange(checkbox.checkBoxColor-0x252525);	
GLCD_SetWindow_Fill(checkbox.Location.x+2+4,checkbox.Location.y+2+4,checkbox.Location.x+checkbox.Size.high-2-4,checkbox.Location.y+checkbox.Size.high-2-4,bcolor,bcolor);

GLCD_DrawLine(checkbox.Location.x+5,checkbox.Location.y+checkbox.Size.high/2-2,checkbox.Location.x+checkbox.Size.high/2-2,checkbox.Location.y+checkbox.Size.high-6,cpGui_ColorChange(checkbox.checkBoxSelectColor));// BLACK_COLOR);				
GLCD_DrawLine(checkbox.Location.x+5,checkbox.Location.y+checkbox.Size.high/2+1-2,checkbox.Location.x+2+checkbox.Size.high/2-2,checkbox.Location.y+checkbox.Size.high-6+1,cpGui_ColorChange(checkbox.checkBoxSelectColor));// BLACK_COLOR);				
GLCD_DrawLine(checkbox.Location.x+5,checkbox.Location.y+checkbox.Size.high/2+2-2,checkbox.Location.x+2+checkbox.Size.high/2-2,checkbox.Location.y+checkbox.Size.high-6+2,cpGui_ColorChange(checkbox.checkBoxSelectColor));// BLACK_COLOR);				
	

GLCD_DrawLine(checkbox.Location.x+checkbox.Size.high/2,checkbox.Location.y+checkbox.Size.high-7,checkbox.Location.x+2+checkbox.Size.high-4,checkbox.Location.y+3,cpGui_ColorChange(checkbox.checkBoxSelectColor));// BLACK_COLOR);				
GLCD_DrawLine(checkbox.Location.x+checkbox.Size.high/2,checkbox.Location.y+checkbox.Size.high-7+1,checkbox.Location.x+2+checkbox.Size.high-4,checkbox.Location.y+3+1,cpGui_ColorChange(checkbox.checkBoxSelectColor));// BLACK_COLOR);					
GLCD_DrawLine(checkbox.Location.x+checkbox.Size.high/2,checkbox.Location.y+checkbox.Size.high-7+2,checkbox.Location.x+2+checkbox.Size.high-4,checkbox.Location.y+3+2,cpGui_ColorChange(checkbox.checkBoxSelectColor));// BLACK_COLOR);					

}

ty_step=((checkbox.Size.high-checkbox.FontHigh)/2);

switch(checkbox.FontWidth)
		{
		case 5:
			break;
		case 8:
			break;
		case 16:
			Printf16(checkbox.Text,checkbox.Location.x+checkbox.Size.high+2,checkbox.Location.y+ty_step,checkbox.textColor,bkflag,cpGui_ColorChange(checkbox.bkColor));
			break;
		case 24:
			Printf24(checkbox.Text,checkbox.Location.x+checkbox.Size.high+2,checkbox.Location.y+ty_step,checkbox.textColor,bkflag,cpGui_ColorChange(checkbox.bkColor));
			break;
		case 32:
			Printf32(checkbox.Text,checkbox.Location.x+checkbox.Size.high+2,checkbox.Location.y+ty_step,checkbox.textColor,bkflag,cpGui_ColorChange(checkbox.bkColor));
			break;	
		}
	
}



void cpGui_CreateRadioButton(RADIOBUTTON radiobutton)
{
unsigned short bcolor;
unsigned char bkflag=1;
	unsigned short ty_step;
if(radiobutton.bkColor&None)
	bkflag=0;
else
	GLCD_SetWindow_Fill(radiobutton.Location.x,radiobutton.Location.y,radiobutton.Location.x+radiobutton.Size.width,radiobutton.Location.y+radiobutton.Size.high,cpGui_ColorChange(radiobutton.bkColor),cpGui_ColorChange(radiobutton.bkColor));	

if(radiobutton.Checked==FALSE)
{
bcolor=cpGui_ColorChange(radiobutton.radiobuttonColor);
GLCD_Circle_Fill(radiobutton.Location.x+radiobutton.Size.high/2-2,radiobutton.Location.y+radiobutton.Size.high/2,radiobutton.Size.high/2-2,BLACK_COLOR,cpGui_ColorChange(radiobutton.radiobuttonColor));
bcolor=cpGui_ColorChange(radiobutton.radiobuttonColor-0x181818);	
GLCD_Circle_Fill(radiobutton.Location.x+radiobutton.Size.high/2-2,radiobutton.Location.y+radiobutton.Size.high/2,radiobutton.Size.high/2-4,bcolor,bcolor);
bcolor=cpGui_ColorChange(radiobutton.radiobuttonColor-0x252525);	
GLCD_Circle_Fill(radiobutton.Location.x+radiobutton.Size.high/2-2,radiobutton.Location.y+radiobutton.Size.high/2,radiobutton.Size.high/2-6,bcolor,bcolor);
}
else
{
bcolor=cpGui_ColorChange(radiobutton.radiobuttonColor);
GLCD_Circle_Fill(radiobutton.Location.x+radiobutton.Size.high/2-2,radiobutton.Location.y+radiobutton.Size.high/2,radiobutton.Size.high/2-2,BLACK_COLOR,cpGui_ColorChange(radiobutton.radiobuttonColor));	
bcolor=cpGui_ColorChange(radiobutton.radiobuttonSelectColor-0x180018);	
GLCD_Circle_Fill(radiobutton.Location.x+radiobutton.Size.high/2-2,radiobutton.Location.y+radiobutton.Size.high/2,radiobutton.Size.high/2-4,bcolor,bcolor);
bcolor=cpGui_ColorChange(radiobutton.radiobuttonSelectColor-0x250025);	
GLCD_Circle_Fill(radiobutton.Location.x+radiobutton.Size.high/2-2,radiobutton.Location.y+radiobutton.Size.high/2,radiobutton.Size.high/2-6,bcolor,bcolor);		
}

ty_step=((radiobutton.Size.high-radiobutton.FontHigh)/2);
switch(radiobutton.FontWidth)
		{
		case 5:
			break;
		case 8:
			break;
		case 16:
			Printf16(radiobutton.Text,radiobutton.Location.x+radiobutton.Size.high+2,radiobutton.Location.y+ty_step,radiobutton.textColor,bkflag,cpGui_ColorChange(radiobutton.bkColor));
			break;
		case 24:
			Printf24(radiobutton.Text,radiobutton.Location.x+radiobutton.Size.high+2,radiobutton.Location.y+ty_step,radiobutton.textColor,bkflag,cpGui_ColorChange(radiobutton.bkColor));
			break;
		case 32:
			Printf32(radiobutton.Text,radiobutton.Location.x+radiobutton.Size.high+2,radiobutton.Location.y+ty_step,radiobutton.textColor,bkflag,cpGui_ColorChange(radiobutton.bkColor));
			break;	
		}
	

}

void cpGui_CreatePictureBox(PICTUREBOX *picturebox)
{
//FileFolderRead(picturebox->ImageName,(unsigned char*)START_PIC_sdram);//读图片文件
//Bmp_Decode((Int32U)START_PIC_sdram, picturebox->Location.x,picturebox->Location.y,(pInt16U)SDRAM0_BASE_ADDR); //显竖画面
	
//FileFolderRead(picturebox->ImageName,(unsigned char*)START_PIC_sdram);//读图片文件
Bmp_Decode(picturebox->picAdder, picturebox->Location.x,picturebox->Location.y,(pInt16U)SDRAM0_BASE_ADDR); //显竖画面
}


int cpGui_TextBox_AddText(TEXTBOX *textbox,char *text)
{
char *tbtext;
	if(textbox->Index>=textbox->MaxCount)
		return -1;
	tbtext=textbox->Text;
	tbtext+=textbox->Index;
while(*text!=0)
{
*tbtext=*text++;	
	tbtext++;
textbox->Index++;
}
*tbtext=0;
cpGui_CreateTextBox(textbox);
}


//CreateTextBox
void cpGui_CreateTextBox(TEXTBOX *textbox)
{
unsigned char bkflag=1;
unsigned short textstartx,textstarty;
if(textbox->bkColor&None)
	bkflag=0;
//else
//GLCD_SetWindow_Fill(textbox.Location.x,textbox.Location.y,textbox.Location.x+textbox.Size.width,textbox.Location.y+textbox.Size.high,cpGui_ColorChange(textbox.bkColor),cpGui_ColorChange(textbox.bkColor));	

GLCD_SetWindow_Fill(textbox->Location.x,textbox->Location.y,textbox->Location.x+textbox->Size.width,textbox->Location.y+textbox->Size.high,cpGui_ColorChange(textbox->textboxColor),cpGui_ColorChange(textbox->textboxColor));	

if(textbox->Focus==FALSE)
{
DrawLine(textbox->Location.x,textbox->Location.y,textbox->Location.x,textbox->Location.y+textbox->Size.high,BLACK_COLOR);
DrawLine(textbox->Location.x,textbox->Location.y,textbox->Location.x+textbox->Size.width,textbox->Location.y,BLACK_COLOR);
}
else
{
DrawLine(textbox->Location.x,textbox->Location.y,textbox->Location.x,textbox->Location.y+textbox->Size.high,cpGui_ColorChange(255+(180<<8)));
DrawLine(textbox->Location.x+1,textbox->Location.y,textbox->Location.x+1,textbox->Location.y+textbox->Size.high,cpGui_ColorChange(255+(180<<8)));
DrawLine(textbox->Location.x,textbox->Location.y,textbox->Location.x+textbox->Size.width,textbox->Location.y,cpGui_ColorChange(255+(180<<8)));
DrawLine(textbox->Location.x,textbox->Location.y+1,textbox->Location.x+textbox->Size.width,textbox->Location.y+1,cpGui_ColorChange(255+(180<<8)));
	
DrawLine(textbox->Location.x+textbox->Size.width,textbox->Location.y,textbox->Location.x+textbox->Size.width,textbox->Location.y+textbox->Size.high,cpGui_ColorChange(255+(180<<8)));
DrawLine(textbox->Location.x+textbox->Size.width-1,textbox->Location.y,textbox->Location.x+textbox->Size.width-1,textbox->Location.y+textbox->Size.high,cpGui_ColorChange(255+(180<<8)));
	
DrawLine(textbox->Location.x,textbox->Location.y+textbox->Size.high,textbox->Location.x+textbox->Size.width,textbox->Location.y+textbox->Size.high,cpGui_ColorChange(255+(180<<8)));
DrawLine(textbox->Location.x,textbox->Location.y+textbox->Size.high-1,textbox->Location.x+textbox->Size.width,textbox->Location.y+textbox->Size.high-1,cpGui_ColorChange(255+(180<<8)));	
}

textbox->Index=strlen(textbox->Text);
if(textbox->Text[0]==0)
	return;

textstartx=textbox->Location.x+3;
textstarty=textbox->Location.y+(textbox->Size.high-textbox->FontHigh)/2;
switch(textbox->FontWidth)
		{
		case 5:
			break;
		case 8:
			break;
		case 16:
			Printf16(textbox->Text,textstartx,textstarty,textbox->textColor,bkflag,cpGui_ColorChange(textbox->bkColor));
			break;
		case 24:
			Printf24(textbox->Text,textstartx,textstarty,textbox->textColor,bkflag,cpGui_ColorChange(textbox->bkColor));
			break;
		case 32:
			Printf32(textbox->Text,textstartx,textstarty,textbox->textColor,bkflag,cpGui_ColorChange(textbox->bkColor));
			break;	
		}
}



void cpGui_CreateLabel(LABEL label)
{
unsigned char bkflag=1;
if(label.bkColor&None)
	bkflag=0;
else
	GLCD_SetWindow_Fill(label.Location.x,label.Location.y,label.Location.x+label.Size.width,label.Location.y+label.Size.high,cpGui_ColorChange(label.bkColor),cpGui_ColorChange(label.bkColor));	
if(label.Text[0]==0)
	return;
switch(label.FontWidth)
		{
		case 5:
			break;
		case 8:
			break;
		case 16:
			Printf16(label.Text,label.Location.x,label.Location.y,label.textColor,bkflag,cpGui_ColorChange(label.bkColor));
			break;
		case 24:
			Printf24(label.Text,label.Location.x,label.Location.y,label.textColor,bkflag,cpGui_ColorChange(label.bkColor));
			break;
		case 32:
			Printf32(label.Text,label.Location.x,label.Location.y,label.textColor,bkflag,cpGui_ColorChange(label.bkColor));
			break;	
		}
}

	
void cpGui_CreateButton(BUTTON button)
{
unsigned int tcolor;
int i;
unsigned short cstep;
unsigned char length;
	char text;
unsigned short tx,ty,tendx,tendy;
	char *tbuf;
tcolor=button.bkColor;	
cstep=(button.Size.high-4)/10;
length=strlen(button.Text);
	

//Draw  back fill
GLCD_SetWindow_Fill(button.Location.x,button.Location.y,button.Location.x+button.Size.width,button.Location.y+button.Size.high,BLACK_COLOR,cpGui_ColorChange(button.bkColor));	
if(button.Enabled==TRUE)			
for(i=1;i<=6;i++)
	{
	tcolor-=0x181818;
	tendy=button.Location.y+button.Size.high/2+i*cstep;
	if(tendy>=(button.Location.y+button.Size.high-2))
		tendy=button.Location.y+button.Size.high-2;
	GLCD_SetWindow_Fill(button.Location.x+2,button.Location.y+button.Size.high/2+(i-1)*cstep,button.Location.x+button.Size.width-2,tendy,cpGui_ColorChange(tcolor),cpGui_ColorChange(tcolor));				
	}	
	
//  TEXT  	
if((button.Size.width>button.FontWidth)&&(button.Size.high>button.FontHigh))
	{
		//tx=button.Location.x+button.FontWidth*5-2*button.FontWidth;
	//	length*button.FontWidth
		tx=button.Location.x+button.Size.width/2-length*button.FontWidth/2;//.FontWidth*5-2*button.FontWidth;
		if((tx<button.Location.x)||(tx>button.Location.x+button.Size.width))
			tx=button.Location.x+2;

		ty=button.Location.y+button.Size.high/2-button.FontHigh/2;//.FontWidth*5-2*button.FontWidth;
		if((ty<button.Location.y)||(ty>button.Location.y+button.Size.high))
			tx=button.Location.y+2;
		
	//	ty=button.Location.y+20-button.FontWidth;
		tbuf=button.Text;
	while(1)
		{		
		text=*tbuf++;
		if(text==0)
			break;
		if(button.Enabled==TRUE)
			Ascii_Printf1632_OneChar_NoFill(&text,tx,ty,BLACK_COLOR);		
		else
				Ascii_Printf1632_OneChar_NoFill(&text,tx,ty,cpGui_ColorChange(cDisabledColor));		
	//	Ascii_Printf1632(button.Text,tx,ty,BLACK_COLOR,button.bkColor);
	 	 tx+=button.FontWidth;		
		 if(tx>(button.Location.x+button.Size.width-16))
			break;
		}	
	}
}



void cpGui_Button_UpDown(BUTTON button,unsigned char sta)
{
unsigned int tcolor,bcolor;
int i;
unsigned short cstep;
unsigned char length;
	char text;
unsigned short tx,ty;
	char *tbuf;

if(button.Enabled==FALSE)
	return;

if(sta==0)
	{
	cpGui_CreateButton(button);
		return;
	}


bcolor=(216<<16)+(238<<8)+250;
tcolor=(120<<16)+(189<<8)+226;	
cstep=(button.Size.high-4)/2;
length=strlen(button.Text);
//Draw  back fill
GLCD_SetWindow_Fill(button.Location.x,button.Location.y,button.Location.x+button.Size.width,button.Location.y+button.Size.high,BLACK_COLOR,cpGui_ColorChange(bcolor));	
for(i=1;i<2;i++)
	{
	tcolor-=0x181818;
	GLCD_SetWindow_Fill(button.Location.x+2,button.Location.y+button.Size.high/2+(i-1)*cstep,button.Location.x+button.Size.width-2,button.Location.y+button.Size.high/2+i*cstep,cpGui_ColorChange(tcolor),cpGui_ColorChange(tcolor));				
	}	
if((button.Size.width>button.FontWidth)&&(button.Size.high>button.FontHigh))
	{
		//tx=button.Location.x+button.FontWidth*5-2*button.FontWidth;
	//	length*button.FontWidth
		tx=button.Location.x+button.Size.width/2-length*button.FontWidth/2;//.FontWidth*5-2*button.FontWidth;
		if((tx<button.Location.x)||(tx>button.Location.x+button.Size.width))
			tx=button.Location.x+2;

		ty=button.Location.y+button.Size.high/2-button.FontHigh/2;//.FontWidth*5-2*button.FontWidth;
		if((ty<button.Location.y)||(ty>button.Location.y+button.Size.high))
			tx=button.Location.y+2;		
	//	ty=button.Location.y+20-button.FontWidth;
		tbuf=button.Text;
	while(1)
		{		
		text=*tbuf++;
		if(text==0)
			break;
		if(button.Enabled==TRUE)
			Ascii_Printf1632_OneChar_NoFill(&text,tx,ty,BLACK_COLOR);		
		else
				Ascii_Printf1632_OneChar_NoFill(&text,tx,ty,cpGui_ColorChange(cDisabledColor));				
//	  Ascii_Printf1632_OneChar_NoFill(&text,tx,ty,BLACK_COLOR);		
	//	Ascii_Printf1632(button.Text,tx,ty,BLACK_COLOR,button.bkColor);
	 	 tx+=button.FontWidth;		
		 if(tx>(button.Location.x+button.Size.width-16))
			break;
		}	
	}	
	
}


// Chart  about
void cpGui_CreateChart(CHART chart)
{
unsigned char bcd[6];

int i;
unsigned short charthigh,chartwidth;

	
charthigh=chart.Size.high-36-20;//chart.Location.y+20;
chartwidth=chart.Size.width-36-chart.FontWidth*5+8;//-chart.Location.x+chart.FontWidth*5+8;
	
	
//Draw  back fill
GLCD_SetWindow_Fill(chart.Location.x,chart.Location.y,chart.Location.x+chart.Size.width,chart.Location.y+chart.Size.high,chart.bkColor,chart.bkColor);

//Draw Row Line 
GLCD_DrawLine(chart.Location.x+chart.FontWidth*5, chart.Location.y+20,chart.Location.x+chart.Size.width-36,chart.Location.y+20,BLACK_COLOR);		
	for(i=1;i<chart.RowStep;i++)
	{
	GLCD_DrawLine(chart.Location.x+chart.FontWidth*5, chart.Location.y+20+((charthigh/chart.RowStep)*i),chart.Location.x+chart.Size.width-36,chart.Location.y+20+((charthigh/chart.RowStep)*i),BLACK_COLOR);			
	}
GLCD_DrawLine(chart.Location.x+chart.FontWidth*5, chart.Location.y+chart.Size.high-36,chart.Location.x+chart.Size.width-36,chart.Location.y+chart.Size.high-36,BLACK_COLOR);		

//Draw Col Line 	
GLCD_DrawLine(chart.Location.x+chart.FontWidth*5+8, chart.Location.y+20,chart.Location.x+chart.FontWidth*5+8,chart.Location.y+chart.Size.high-28,BLACK_COLOR);	
	for(i=1;i<chart.ColStep;i++)
	{
	GLCD_DrawLine(chart.Location.x+chart.FontWidth*5+8+((chartwidth/chart.ColStep)*i), chart.Location.y+20,chart.Location.x+chart.FontWidth*5+8+((chartwidth/chart.ColStep)*i),chart.Location.y+chart.Size.high-28,BLACK_COLOR);		
//	GLCD_DrawLine(chart.Location.x+chart.FontWidth*5, chart.Location.y+20+((chartwidth/chart.ColStep)*i),chart.Location.x+chart.Size.width-36,chart.Location.y+20+((chartwidth/chart.ColStep)*i),BLACK_COLOR);			
	}	
GLCD_DrawLine(chart.Location.x+chart.Size.width-36, chart.Location.y+20,chart.Location.x+chart.Size.width-36,chart.Location.y+chart.Size.high-28,BLACK_COLOR);		
	
bcd[0]=chart.RowData/10000+0x30;
bcd[1]=chart.RowData%10000/1000+0x30;
bcd[2]=chart.RowData%10000%1000/100+0x30;
bcd[3]=chart.RowData%10000%1000%100/10+0x30;
bcd[4]=chart.RowData%10000%1000%100%10+0x30;
bcd[5]=0;
	
while(1)
	{
	if(bcd[0]==0x30)
		{
			for(i=0;i<5;i++)
				{
				bcd[i]=bcd[i+1];
				}
		}		
	else
		break;		
	}

Ascii_Printf1632("80",chart.Location.x+chart.FontWidth*5-2*chart.FontWidth,chart.Location.y+20-chart.FontWidth,BLACK_COLOR,chart.bkColor);
Ascii_Printf1632("0",chart.Location.x+chart.FontWidth*5-1*chart.FontWidth,chart.Location.y+chart.Size.high-36-chart.FontWidth,BLACK_COLOR,chart.bkColor);
	
}

void cpGui_ChartRedraw(CHART chart,unsigned short *buf,unsigned short length)
{
int i;
int n;
//unsigned short charthigh;
	unsigned short chartwidth;
unsigned short chartstartx,chartstarty;
unsigned short chartdrawxsetp;//,chartdrawysetp;
unsigned short oldx,oldy,newx,newy;

//charthigh=chart.Size.high-36-20;//chart.Location.y+20;
chartwidth=chart.Size.width-36-chart.FontWidth*5+8;//-chart.Location.x+chart.FontWidth*5+8;
	
chartdrawxsetp=chartwidth/chart.ScaleView;	
//chartdrawysetp=800/charthigh;//.ScaleView;	

chartstartx=chart.Location.x+chart.FontWidth*5+8+(chartdrawxsetp/2);
chartstarty=chart.Location.y+chart.Size.high-36-2;
	
cpGui_CreateChart(chart);//绘制基本层
if(length>0)
	{
	oldx=chartstartx;
	oldy=chartstarty-buf[0]/4;
	newx=oldx;//+chartdrawxsetp;
	newy=oldy;
	for(n=0;n<chart.LineWidth;n++)
		PutPixel(oldx+n,oldy+n,cpGui_ColorChange(chart.LineColor));
	for(i=1;i<length;i++)
		{
		newx+=chartdrawxsetp;
		newy=chartstarty-buf[i]/4;
		for(n=0;n<chart.LineWidth;n++)
			GLCD_DrawLine(oldx+n, oldy+n,newx+n,newy+n,cpGui_ColorChange(chart.LineColor));	
		oldx=newx;//chartdrawxsetp;
		oldy=newy;
		}	
	}
}







