#include "cal_form.h"


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
#include "bmp.h"



PICTUREBOX CAL_1_PictureBox=
{
PictureBox_Type,//unsigned char Type;
TRUE,//unsigned char Enabled;
TRUE,
FALSE,//unsigned char Focus
22,90,//LOCATION Location;	//定位
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
"CAL_1.bmp",
0
};



PICTUREBOX CAL_2_PictureBox=
{
PictureBox_Type,//unsigned char Type;
TRUE,//unsigned char Enabled;
TRUE,
FALSE,//unsigned char Focus
116,90,//LOCATION Location;	//定位
48,48,//SIZE Size; //总大小
(255<<16)+(255<<8),//unsigned int picturebkColor;
255,//unsigned int textboxSelectColor;
0,//unsigned int textColor;
None,//unsigned int textbkColor;	//背景色
16,//unsigned short FontWidth;//字体宽度
16,//unsigned short FontHigh;
0,//index
6,//MaxCount
"CAL_2",
"CAL_2.bmp",
0
};



PICTUREBOX CAL_3_PictureBox=
{
PictureBox_Type,//unsigned char Type;
TRUE,//unsigned char Enabled;
TRUE,
FALSE,//unsigned char Focus
210,90,//LOCATION Location;	//定位
48,48,//SIZE Size; //总大小
(255<<16)+(255<<8),//unsigned int picturebkColor;
255,//unsigned int textboxSelectColor;
0,//unsigned int textColor;
None,//unsigned int textbkColor;	//背景色
16,//unsigned short FontWidth;//字体宽度
16,//unsigned short FontHigh;
0,//index
6,//MaxCount
"CAL_3",
"CAL_3.bmp",
0
};



PICTUREBOX CAL_4_PictureBox=
{
PictureBox_Type,//unsigned char Type;
TRUE,//unsigned char Enabled;
TRUE,
FALSE,//unsigned char Focus
22,150,//LOCATION Location;	//定位
48,48,//SIZE Size; //总大小
(255<<16)+(255<<8),//unsigned int picturebkColor;
255,//unsigned int textboxSelectColor;
0,//unsigned int textColor;
None,//unsigned int textbkColor;	//背景色
16,//unsigned short FontWidth;//字体宽度
16,//unsigned short FontHigh;
0,//index
6,//MaxCount
"CAL_1",
"CAL_4.bmp",
0
};



PICTUREBOX CAL_5_PictureBox=
{
PictureBox_Type,//unsigned char Type;
TRUE,//unsigned char Enabled;
TRUE,
FALSE,//unsigned char Focus
116,150,//LOCATION Location;	//定位
48,48,//SIZE Size; //总大小
(255<<16)+(255<<8),//unsigned int picturebkColor;
255,//unsigned int textboxSelectColor;
0,//unsigned int textColor;
None,//unsigned int textbkColor;	//背景色
16,//unsigned short FontWidth;//字体宽度
16,//unsigned short FontHigh;
0,//index
6,//MaxCount
"CAL_5",
"CAL_5.bmp",
0
};



PICTUREBOX CAL_6_PictureBox=
{
PictureBox_Type,//unsigned char Type;
TRUE,//unsigned char Enabled;
TRUE,
FALSE,//unsigned char Focus
210,150,//LOCATION Location;	//定位
48,48,//SIZE Size; //总大小
(255<<16)+(255<<8),//unsigned int picturebkColor;
255,//unsigned int textboxSelectColor;
0,//unsigned int textColor;
None,//unsigned int textbkColor;	//背景色
16,//unsigned short FontWidth;//字体宽度
16,//unsigned short FontHigh;
0,//index
6,//MaxCount
"CAL_1",
"CAL_6.bmp",
0
};



PICTUREBOX CAL_7_PictureBox=
{
PictureBox_Type,//unsigned char Type;
TRUE,//unsigned char Enabled;
TRUE,
FALSE,//unsigned char Focus
22,210,//LOCATION Location;	//定位
48,48,//SIZE Size; //总大小
(255<<16)+(255<<8),//unsigned int picturebkColor;
255,//unsigned int textboxSelectColor;
0,//unsigned int textColor;
None,//unsigned int textbkColor;	//背景色
16,//unsigned short FontWidth;//字体宽度
16,//unsigned short FontHigh;
0,//index
6,//MaxCount
"CAL_7",
"CAL_7.bmp",
0
};



PICTUREBOX CAL_8_PictureBox=
{
PictureBox_Type,//unsigned char Type;
TRUE,//unsigned char Enabled;
TRUE,
FALSE,//unsigned char Focus
116,210,//LOCATION Location;	//定位
48,48,//SIZE Size; //总大小
(255<<16)+(255<<8),//unsigned int picturebkColor;
255,//unsigned int textboxSelectColor;
0,//unsigned int textColor;
None,//unsigned int textbkColor;	//背景色
16,//unsigned short FontWidth;//字体宽度
16,//unsigned short FontHigh;
0,//index
6,//MaxCount
"CAL_8",
"CAL_8.bmp",
0
};


PICTUREBOX CAL_9_PictureBox=
{
PictureBox_Type,//unsigned char Type;
TRUE,//unsigned char Enabled;
TRUE,
FALSE,//unsigned char Focus
210,210,//LOCATION Location;	//定位
48,48,//SIZE Size; //总大小
(255<<16)+(255<<8),//unsigned int picturebkColor;
255,//unsigned int textboxSelectColor;
0,//unsigned int textColor;
None,//unsigned int textbkColor;	//背景色
16,//unsigned short FontWidth;//字体宽度
16,//unsigned short FontHigh;
0,//index
6,//MaxCount
"CAL_9",
"CAL_9.bmp",
0
};


PICTUREBOX CAL_0_PictureBox=
{
PictureBox_Type,//unsigned char Type;
TRUE,//unsigned char Enabled;
TRUE,
FALSE,//unsigned char Focus
116,270,//LOCATION Location;	//定位
48,48,//SIZE Size; //总大小
(255<<16)+(255<<8),//unsigned int picturebkColor;
255,//unsigned int textboxSelectColor;
0,//unsigned int textColor;
None,//unsigned int textbkColor;	//背景色
16,//unsigned short FontWidth;//字体宽度
16,//unsigned short FontHigh;
0,//index
6,//MaxCount
"CAL_0",
"CAL_0.bmp",
0
};



PICTUREBOX CAL_ADD_PictureBox=
{
PictureBox_Type,//unsigned char Type;
TRUE,//unsigned char Enabled;
TRUE,
FALSE,//unsigned char Focus
304,90,//LOCATION Location;	//定位
48,48,//SIZE Size; //总大小
(255<<16)+(255<<8),//unsigned int picturebkColor;
255,//unsigned int textboxSelectColor;
0,//unsigned int textColor;
None,//unsigned int textbkColor;	//背景色
16,//unsigned short FontWidth;//字体宽度
16,//unsigned short FontHigh;
0,//index
6,//MaxCount
"CAL_ADD",
"CAL_ADD.bmp",
0
};



PICTUREBOX CAL_SUB_PictureBox=
{
PictureBox_Type,//unsigned char Type;
TRUE,//unsigned char Enabled;
TRUE,
FALSE,//unsigned char Focus
304,150,//LOCATION Location;	//定位
48,48,//SIZE Size; //总大小
(255<<16)+(255<<8),//unsigned int picturebkColor;
255,//unsigned int textboxSelectColor;
0,//unsigned int textColor;
None,//unsigned int textbkColor;	//背景色
16,//unsigned short FontWidth;//字体宽度
16,//unsigned short FontHigh;
0,//index
6,//MaxCount
"CAL_SUB",
"CAL_SUB.bmp",
0
};



PICTUREBOX CAL_MUL_PictureBox=
{
PictureBox_Type,//unsigned char Type;
TRUE,//unsigned char Enabled;
TRUE,
FALSE,//unsigned char Focus
304,210,//LOCATION Location;	//定位
48,48,//SIZE Size; //总大小
(255<<16)+(255<<8),//unsigned int picturebkColor;
255,//unsigned int textboxSelectColor;
0,//unsigned int textColor;
None,//unsigned int textbkColor;	//背景色
16,//unsigned short FontWidth;//字体宽度
16,//unsigned short FontHigh;
0,//index
6,//MaxCount
"CAL_MUL",
"CAL_MUL.bmp",
0
};



PICTUREBOX CAL_DIV_PictureBox=
{
PictureBox_Type,//unsigned char Type;
TRUE,//unsigned char Enabled;
TRUE,
FALSE,//unsigned char Focus
304,270,//LOCATION Location;	//定位
48,48,//SIZE Size; //总大小
(255<<16)+(255<<8),//unsigned int picturebkColor;
255,//unsigned int textboxSelectColor;
0,//unsigned int textColor;
None,//unsigned int textbkColor;	//背景色
16,//unsigned short FontWidth;//字体宽度
16,//unsigned short FontHigh;
0,//index
6,//MaxCount
"CAL_DIV",
"CAL_DIV.bmp",
0
};



PICTUREBOX CAL_EQU_PictureBox=
{
PictureBox_Type,//unsigned char Type;
TRUE,//unsigned char Enabled;
TRUE,
FALSE,//unsigned char Focus
22,330,//LOCATION Location;	//定位
48,48,//SIZE Size; //总大小
(255<<16)+(255<<8),//unsigned int picturebkColor;
255,//unsigned int textboxSelectColor;
0,//unsigned int textColor;
None,//unsigned int textbkColor;	//背景色
16,//unsigned short FontWidth;//字体宽度
16,//unsigned short FontHigh;
0,//index
6,//MaxCount
"CAL_EQU",
"CAL_EQU.bmp",
0
};



PICTUREBOX CAL_YES_PictureBox=
{
PictureBox_Type,//unsigned char Type;
TRUE,//unsigned char Enabled;
TRUE,
FALSE,//unsigned char Focus
210,330,//LOCATION Location;	//定位
48,48,//SIZE Size; //总大小
(255<<16)+(255<<8),//unsigned int picturebkColor;
255,//unsigned int textboxSelectColor;
0,//unsigned int textColor;
None,//unsigned int textbkColor;	//背景色
16,//unsigned short FontWidth;//字体宽度
16,//unsigned short FontHigh;
0,//index
6,//MaxCount
"CAL_YES",
"CAL_YES.bmp",
0
};



PICTUREBOX CAL_C_PictureBox=
{
PictureBox_Type,//unsigned char Type;
TRUE,//unsigned char Enabled;
TRUE,
FALSE,//unsigned char Focus
22,270,//LOCATION Location;	//定位
48,48,//SIZE Size; //总大小
(255<<16)+(255<<8),//unsigned int picturebkColor;
255,//unsigned int textboxSelectColor;
0,//unsigned int textColor;
None,//unsigned int textbkColor;	//背景色
16,//unsigned short FontWidth;//字体宽度
16,//unsigned short FontHigh;
0,//index
6,//MaxCount
"CAL_C",
"CAL_C.bmp",
0
};



PICTUREBOX CAL_DOT_PictureBox=
{
PictureBox_Type,//unsigned char Type;
TRUE,//unsigned char Enabled;
TRUE,
FALSE,//unsigned char Focus
210,270,//LOCATION Location;	//定位
48,48,//SIZE Size; //总大小
(255<<16)+(255<<8),//unsigned int picturebkColor;
255,//unsigned int textboxSelectColor;
0,//unsigned int textColor;
None,//unsigned int textbkColor;	//背景色
16,//unsigned short FontWidth;//字体宽度
16,//unsigned short FontHigh;
0,//index
6,//MaxCount
"CAL_DOT",
"CAL_DOT.bmp",
0
};


#define CAL_DIS_X  398
#define CAL_DIS_Y  95


//BUTTON


//CAL_BT1
BUTTON CAL_BTNum1={Button_Type,\
								TRUE,
								CAL_DIS_X+16,CAL_DIS_Y+8+36+55,\
								88,50,\
								(240<<16)+(240<<8)+240,\
								16,\
								32,
								"1"};	

//CAL_BT2
BUTTON CAL_BTNum2={Button_Type,\
								TRUE,
								CAL_DIS_X+16+94,CAL_DIS_Y+8+36+55,\
								88,50,\
								(240<<16)+(240<<8)+240,\
								16,\
								32,
								"2"};	

//CAL_BT3
BUTTON CAL_BTNum3={Button_Type,\
								TRUE,
								CAL_DIS_X+16+94+94,CAL_DIS_Y+8+36+55,\
								88,50,\
								(240<<16)+(240<<8)+240,\
								16,\
								32,
								"3"};	

//CAL_BT_ADD
BUTTON CAL_BT_ADD={Button_Type,\
								TRUE,
								CAL_DIS_X+16+94+94+94,CAL_DIS_Y+8+36+55,\
								88,50,\
								(240<<16)+(240<<8)+240,\
								16,\
								32,
								"+"};	
								

//CAL_BT4
BUTTON CAL_BTNum4={Button_Type,\
								TRUE,
								CAL_DIS_X+16,CAL_DIS_Y+8+36+55+55,\
								88,50,\
								(240<<16)+(240<<8)+240,\
								16,\
								32,
								"4"};	

//CAL_BT5
BUTTON CAL_BTNum5={Button_Type,\
								TRUE,
								CAL_DIS_X+16+94,CAL_DIS_Y+8+36+55+55,\
								88,50,\
								(240<<16)+(240<<8)+240,\
								16,\
								32,
								"5"};	

//CAL_BT6
BUTTON CAL_BTNum6={Button_Type,\
								TRUE,
								CAL_DIS_X+16+94+94,CAL_DIS_Y+8+36+55+55,\
								88,50,\
								(240<<16)+(240<<8)+240,\
								16,\
								32,
								"6"};	

								
//CAL_BT_SUB
BUTTON CAL_BT_SUB={Button_Type,\
								TRUE,
								CAL_DIS_X+16+94+94+94,CAL_DIS_Y+8+36+55+55,\
								88,50,\
								(240<<16)+(240<<8)+240,\
								16,\
								32,
								"-"};	

								
//CAL_BT7
BUTTON CAL_BTNum7={Button_Type,\
								TRUE,
								CAL_DIS_X+16,CAL_DIS_Y+8+36+55+55+55,\
								88,50,\
								(240<<16)+(240<<8)+240,\
								16,\
								32,
								"7"};	

//CAL_BT8
BUTTON CAL_BTNum8={Button_Type,\
								TRUE,
								CAL_DIS_X+16+94,CAL_DIS_Y+8+36+55+55+55,\
								88,50,\
								(240<<16)+(240<<8)+240,\
								16,\
								32,
								"8"};	

//CAL_BT9
BUTTON CAL_BTNum9={Button_Type,\
								TRUE,
								CAL_DIS_X+16+94+94,CAL_DIS_Y+8+36+55+55+55,\
								88,50,\
								(240<<16)+(240<<8)+240,\
								16,\
								32,
								"9"};	

//CAL_BT_MUL
BUTTON CAL_BT_MUL={Button_Type,\
								TRUE,
								CAL_DIS_X+16+94+94+94,CAL_DIS_Y+8+36+55+55+55,\
								88,50,\
								(240<<16)+(240<<8)+240,\
								16,\
								32,
								"*"};									

//CAL_BT_CLEAR
BUTTON CAL_BT_CLEAR={Button_Type,\
								TRUE,
								CAL_DIS_X+16,CAL_DIS_Y+8+36+55+55+55+55,\
								88,50,\
								(240<<16)+(240<<8)+240,\
								16,\
								32,
								"C"};	

								
//CAL_BT0
BUTTON CAL_BTNum0={Button_Type,\
								TRUE,
								CAL_DIS_X+16+94,CAL_DIS_Y+8+36+55+55+55+55,\
								88,50,\
								(240<<16)+(240<<8)+240,\
								16,\
								32,
								"0"};	

//CAL_BT_DOT
BUTTON CAL_BT_DOT={Button_Type,\
								TRUE,
								CAL_DIS_X+16+94+94,CAL_DIS_Y+8+36+55+55+55+55,\
								88,50,\
								(240<<16)+(240<<8)+240,\
								16,\
								32,
								"."};	

//CAL_BT_DIV
BUTTON CAL_BT_DIV={Button_Type,\
								TRUE,
								CAL_DIS_X+16+94+94+94,CAL_DIS_Y+8+36+55+55+55+55,\
								88,50,\
								(240<<16)+(240<<8)+240,\
								16,\
								32,
								"/"};	

						

//CAL_UP_ARROW
BUTTON CAL_BT_UP_ARROW={Button_Type,\
								TRUE,
								CAL_DIS_X+16,CAL_DIS_Y+8+36+55+55+55+55+55,\
								40,50,\
								(240<<16)+(240<<8)+240,\
								16,\
								32,
								"↑"};	

//CAL_DOWN_ARROW
BUTTON CAL_BT_DOWN_ARROW={Button_Type,\
								TRUE,
								CAL_DIS_X+16+40+10,CAL_DIS_Y+8+36+55+55+55+55+55,\
								40,50,\
								(240<<16)+(240<<8)+240,\
								16,\
								32,
								"↓"};	

//CAL_BT_EQU
BUTTON CAL_BT_EQU={Button_Type,\
								TRUE,
								CAL_DIS_X+16+100,CAL_DIS_Y+8+36+55+55+55+55+55,\
								130,50,\
								(240<<16)+(240<<8)+240,\
								16,\
								32,
								"="};	

//CAL_BT YES
BUTTON CAL_BT_YES={Button_Type,\
								TRUE,
								CAL_DIS_X+16+94+94+20+32,CAL_DIS_Y+8+36+55+55+55+55+55,\
								130,50,\
								(240<<16)+(240<<8)+240,\
								16,\
								32,
								"YES"};	







/*
//CAL_BT0
BUTTON CAL_BT={Button_Type,\
								TRUE,
								456,548,\
								48,48,\
								(240<<16)+(240<<8)+240,\
								16,\
								32,
								"0"};	

//CAL_BT0
BUTTON CAL_BTNum0={Button_Type,\
								TRUE,
								456,548,\
								48,48,\
								(240<<16)+(240<<8)+240,\
								16,\
								32,
								"0"};									
*/


TEXTBOX CalInput_TextBox=
{
TextBox_Type,//unsigned char Type;
TRUE,//unsigned char Enabled;
	FALSE,//unsigned char Focus
CAL_DIS_X+16,CAL_DIS_Y+8+50,//LOCATION Location;	//定位
370,36,//SIZE Size; //总大小
1,
(255<<16)+(255<<8),//unsigned int textboxColor;
255,//unsigned int textboxSelectColor;
0,//unsigned int textColor;
(255<<16)+(255<<8),//unsigned int bkColor;	//背景色
32,//unsigned short FontWidth;//字体宽度
32,//unsigned short FontHigh;
0,//index
7,//MaxCount
""	
};


#define CAL_FORM_SHOW 2

uint8_t Cal_Form_Show_Flag=0;
					
//uint8_t Modify_Flag=0;


void CAL_Form_LoadPic(void)
{
	
FileRead("字库_0x20000.FON",(unsigned char *)df_zk_sdram);	
	
//按扭1
if(File_Find("\\APP1\\CAL_1.bmp")==1)//查找文件名是否存在
	{//已存在  读取文件到内存 buf		
	CAL_1_PictureBox.picAdder=(unsigned char *)malloc(nFiles_Temp.FileLength+1);			
	FileFolderRead("CAL_1.bmp",CAL_1_PictureBox.picAdder);//读开机画面
//	cpGui_CreatePictureBox(&CAL_1_PictureBox);		
	}	
	
//按扭2
if(File_Find("\\APP1\\CAL_2.bmp")==1)//查找文件名是否存在
	{//已存在  读取文件到内存 buf		
	CAL_2_PictureBox.picAdder=(unsigned char *)malloc(nFiles_Temp.FileLength+1);			
	FileFolderRead("CAL_2.bmp",CAL_2_PictureBox.picAdder);//读开机画面
//	cpGui_CreatePictureBox(&CAL_1_PictureBox);		
	}	

//按扭3
if(File_Find("\\APP1\\CAL_3.bmp")==1)//查找文件名是否存在
	{//已存在  读取文件到内存 buf		
	CAL_3_PictureBox.picAdder=(unsigned char *)malloc(nFiles_Temp.FileLength+1);			
	FileFolderRead("CAL_3.bmp",CAL_3_PictureBox.picAdder);//读开机画面
//	cpGui_CreatePictureBox(&CAL_1_PictureBox);		
	}	

//按扭4
if(File_Find("\\APP1\\CAL_4.bmp")==1)//查找文件名是否存在
	{//已存在  读取文件到内存 buf		
	CAL_4_PictureBox.picAdder=(unsigned char *)malloc(nFiles_Temp.FileLength+1);			
	FileFolderRead("CAL_4.bmp",CAL_4_PictureBox.picAdder);//读开机画面
//	cpGui_CreatePictureBox(&CAL_1_PictureBox);		
	}	

//按扭5
if(File_Find("\\APP1\\CAL_5.bmp")==1)//查找文件名是否存在
	{//已存在  读取文件到内存 buf		
	CAL_5_PictureBox.picAdder=(unsigned char *)malloc(nFiles_Temp.FileLength+1);			
	FileFolderRead("CAL_5.bmp",CAL_5_PictureBox.picAdder);//读开机画面
//	cpGui_CreatePictureBox(&CAL_1_PictureBox);		
	}	

//按扭6
if(File_Find("\\APP1\\CAL_6.bmp")==1)//查找文件名是否存在
	{//已存在  读取文件到内存 buf		
	CAL_6_PictureBox.picAdder=(unsigned char *)malloc(nFiles_Temp.FileLength+1);			
	FileFolderRead("CAL_6.bmp",CAL_6_PictureBox.picAdder);//读开机画面
//	cpGui_CreatePictureBox(&CAL_1_PictureBox);		
	}	

//按扭7
if(File_Find("\\APP1\\CAL_7.bmp")==1)//查找文件名是否存在
	{//已存在  读取文件到内存 buf		
	CAL_7_PictureBox.picAdder=(unsigned char *)malloc(nFiles_Temp.FileLength+1);			
	FileFolderRead("CAL_7.bmp",CAL_7_PictureBox.picAdder);//读开机画面
//	cpGui_CreatePictureBox(&CAL_1_PictureBox);		
	}	

//按扭8
if(File_Find("\\APP1\\CAL_8.bmp")==1)//查找文件名是否存在
	{//已存在  读取文件到内存 buf		
	CAL_8_PictureBox.picAdder=(unsigned char *)malloc(nFiles_Temp.FileLength+1);			
	FileFolderRead("CAL_8.bmp",CAL_8_PictureBox.picAdder);//读开机画面
//	cpGui_CreatePictureBox(&CAL_1_PictureBox);		
	}	

//按扭9
if(File_Find("\\APP1\\CAL_9.bmp")==1)//查找文件名是否存在
	{//已存在  读取文件到内存 buf		
	CAL_9_PictureBox.picAdder=(unsigned char *)malloc(nFiles_Temp.FileLength+1);			
	FileFolderRead("CAL_9.bmp",CAL_9_PictureBox.picAdder);//读开机画面
//	cpGui_CreatePictureBox(&CAL_1_PictureBox);		
	}	

//按扭0
if(File_Find("\\APP1\\CAL_0.bmp")==1)//查找文件名是否存在
	{//已存在  读取文件到内存 buf		
	CAL_0_PictureBox.picAdder=(unsigned char *)malloc(nFiles_Temp.FileLength+1);			
	FileFolderRead("CAL_0.bmp",CAL_0_PictureBox.picAdder);//读开机画面
//	cpGui_CreatePictureBox(&CAL_1_PictureBox);		
	}	

//按扭C
if(File_Find("\\APP1\\CAL_C.bmp")==1)//查找文件名是否存在
	{//已存在  读取文件到内存 buf		
	CAL_C_PictureBox.picAdder=(unsigned char *)malloc(nFiles_Temp.FileLength+1);			
	FileFolderRead("CAL_C.bmp",CAL_C_PictureBox.picAdder);//读开机画面
//	cpGui_CreatePictureBox(&CAL_1_PictureBox);		
	}	

//按扭DOT
if(File_Find("\\APP1\\CAL_DOT.bmp")==1)//查找文件名是否存在
	{//已存在  读取文件到内存 buf		
	CAL_DOT_PictureBox.picAdder=(unsigned char *)malloc(nFiles_Temp.FileLength+1);			
	FileFolderRead("CAL_DOT.bmp",CAL_DOT_PictureBox.picAdder);//读开机画面
//	cpGui_CreatePictureBox(&CAL_1_PictureBox);		
	}	

//按扭+
if(File_Find("\\APP1\\CAL_ADD.bmp")==1)//查找文件名是否存在
	{//已存在  读取文件到内存 buf		
	CAL_ADD_PictureBox.picAdder=(unsigned char *)malloc(nFiles_Temp.FileLength+1);			
	FileFolderRead("CAL_ADD.bmp",CAL_ADD_PictureBox.picAdder);//读开机画面
//	cpGui_CreatePictureBox(&CAL_1_PictureBox);		
	}	

//按扭SUB
if(File_Find("\\APP1\\CAL_SUB.bmp")==1)//查找文件名是否存在
	{//已存在  读取文件到内存 buf		
	CAL_SUB_PictureBox.picAdder=(unsigned char *)malloc(nFiles_Temp.FileLength+1);			
	FileFolderRead("CAL_SUB.bmp",CAL_SUB_PictureBox.picAdder);//读开机画面
//	cpGui_CreatePictureBox(&CAL_1_PictureBox);		
	}	

//按扭MUL
if(File_Find("\\APP1\\CAL_MUL.bmp")==1)//查找文件名是否存在
	{//已存在  读取文件到内存 buf		
	CAL_MUL_PictureBox.picAdder=(unsigned char *)malloc(nFiles_Temp.FileLength+1);			
	FileFolderRead("CAL_MUL.bmp",CAL_MUL_PictureBox.picAdder);//读开机画面
//	cpGui_CreatePictureBox(&CAL_1_PictureBox);		
	}	

//按扭DIV
if(File_Find("\\APP1\\CAL_DIV.bmp")==1)//查找文件名是否存在
	{//已存在  读取文件到内存 buf		
	CAL_DIV_PictureBox.picAdder=(unsigned char *)malloc(nFiles_Temp.FileLength+1);			
	FileFolderRead("CAL_DIV.bmp",CAL_DIV_PictureBox.picAdder);//读开机画面
//	cpGui_CreatePictureBox(&CAL_1_PictureBox);		
	}	

//按扭EQU
if(File_Find("\\APP1\\CAL_EQU.bmp")==1)//查找文件名是否存在
	{//已存在  读取文件到内存 buf		
	CAL_EQU_PictureBox.picAdder=(unsigned char *)malloc(nFiles_Temp.FileLength+1);			
	FileFolderRead("CAL_EQU.bmp",CAL_EQU_PictureBox.picAdder);//读开机画面
//	cpGui_CreatePictureBox(&CAL_1_PictureBox);		
	}	

//按扭YES
if(File_Find("\\APP1\\CAL_YES.bmp")==1)//查找文件名是否存在
	{//已存在  读取文件到内存 buf		
	CAL_YES_PictureBox.picAdder=(unsigned char *)malloc(nFiles_Temp.FileLength+1);			
	FileFolderRead("CAL_YES.bmp",CAL_YES_PictureBox.picAdder);//读开机画面
//	cpGui_CreatePictureBox(&CAL_1_PictureBox);		
	}	
	
}


void CAL_Form_Init(void)
{
	char str[32];
//CAL_Form_LoadPic();
	//FileFolderRead("CAL_1.bmp",(unsigned char*)START_PIC_sdram);//读开机画面
//FileFolderRead("CAL_1.bmp",(unsigned char*)START_PIC_sdram);//读到缓存	
	///*

//	*/
//Bmp_Decode((Int32U)START_PIC_sdram, 100,100,(pInt16U)SDRAM0_BASE_ADDR); //显竖画面
//	return;
	
	/*
cpGui_CreatePictureBox(&CAL_1_PictureBox);
cpGui_CreatePictureBox(&CAL_2_PictureBox);
cpGui_CreatePictureBox(&CAL_3_PictureBox);
cpGui_CreatePictureBox(&CAL_ADD_PictureBox);	
	
cpGui_CreatePictureBox(&CAL_4_PictureBox);
cpGui_CreatePictureBox(&CAL_5_PictureBox);	
cpGui_CreatePictureBox(&CAL_6_PictureBox);
cpGui_CreatePictureBox(&CAL_SUB_PictureBox);
	
cpGui_CreatePictureBox(&CAL_7_PictureBox);
cpGui_CreatePictureBox(&CAL_8_PictureBox);
cpGui_CreatePictureBox(&CAL_9_PictureBox);
cpGui_CreatePictureBox(&CAL_MUL_PictureBox);

cpGui_CreatePictureBox(&CAL_C_PictureBox);
cpGui_CreatePictureBox(&CAL_0_PictureBox);
cpGui_CreatePictureBox(&CAL_DOT_PictureBox);
cpGui_CreatePictureBox(&CAL_DIV_PictureBox);

cpGui_CreatePictureBox(&CAL_EQU_PictureBox);	
cpGui_CreatePictureBox(&CAL_YES_PictureBox);
*/


CurrentArea_save5(CAL_DIS_X,CAL_DIS_Y+50,400,420-30);



FormActive[0]=CAL_FORM_SHOW;//显示 信处窗口
Cal_Form_Show_Flag=1;
Focus=0;

GLCD_SetWindow_Fill(CAL_DIS_X,CAL_DIS_Y+50,CAL_DIS_X+400-1,CAL_DIS_Y+420-1-30,cpGui_ColorChange(cDisabledColor),cpGui_ColorChange(cDisabledColor));//.Location.x,label.Location.y,label.Location.x+label.Size.width,label.Location.y+label.Size.high,cpGui_ColorChange(label.bkColor),cpGui_ColorChange(label.bkColor));				

//显示 PassWord  TextBox
cpGui_CreateTextBox(&CalInput_TextBox);	

Focus=&CalInput_TextBox.Type;//获取焦点
TouchEvent_ObjSetFocus();


//BUTTON 1
//	CAL_BTNum1.Location.x=560+70-112;
//	CAL_BTNum1.Location.y=360-84;
	cpGui_CreateButton(&CAL_BTNum1);
	
	//BUTTON 2
	//CAL_BTNum2.Location.x=560+70-112;
	//CAL_BTNum2.Location.y=360-84;
	cpGui_CreateButton(&CAL_BTNum2);

//BUTTON 3
	//CAL_BTNum3.Location.x=560+70-112;
//	CAL_BTNum3.Location.y=360-84;
	cpGui_CreateButton(&CAL_BTNum3);
	
	//BUTTON +
	//	CAL_BT_ADD.Location.x=560+70-112;
	//CAL_BT_ADD.Location.y=360-84;
	cpGui_CreateButton(&CAL_BT_ADD);
	
	//BUTTON 4
//	CAL_BTNum4.Location.x=560+70-112;
//	CAL_BTNum4.Location.y=360-84;
	cpGui_CreateButton(&CAL_BTNum4);
	
	//BUTTON 5
//	CAL_BTNum5.Location.x=560+70-112;
//	CAL_BTNum5.Location.y=360-84;
	cpGui_CreateButton(&CAL_BTNum5);

//BUTTON 6
//	CAL_BTNum6.Location.x=560+70-112;
//	CAL_BTNum6.Location.y=360-84;
	cpGui_CreateButton(&CAL_BTNum6);
	
	//BUTTON -
//		CAL_BT_SUB.Location.x=560+70-112;
//	CAL_BT_SUB.Location.y=360-84;
	cpGui_CreateButton(&CAL_BT_SUB);
	
	//BUTTON 7
//	CAL_BTNum7.Location.x=560+70-112;
//	CAL_BTNum7.Location.y=360-84;
	cpGui_CreateButton(&CAL_BTNum7);
	
	//BUTTON 8
//	CAL_BTNum8.Location.x=560+70-112;
//	CAL_BTNum8.Location.y=360-84;
	cpGui_CreateButton(&CAL_BTNum8);

//BUTTON 9
//	CAL_BTNum9.Location.x=560+70-112;
//	CAL_BTNum9.Location.y=360-84;
	cpGui_CreateButton(&CAL_BTNum9);
	
	//BUTTON *
	//	CAL_BT_MUL.Location.x=560+70-112;
	//CAL_BT_MUL.Location.y=360-84;
	cpGui_CreateButton(&CAL_BT_MUL);
	
	//BUTTON C
	//CAL_BT_CLEAR.Location.x=560+70-112;
//	CAL_BT_CLEAR.Location.y=360-84;
	cpGui_CreateButton(&CAL_BT_CLEAR);
	
	//BUTTON 0
//	CAL_BTNum0.Location.x=560+70-112;
//	CAL_BTNum0.Location.y=360-84;
	cpGui_CreateButton(&CAL_BTNum0);

//BUTTON .
	//CAL_BT_DOT.Location.x=560+70-112;
	//CAL_BT_DOT.Location.y=360-84;
	cpGui_CreateButton(&CAL_BT_DOT);
	
	//BUTTON /
//		CAL_BT_DIV.Location.x=560+70-112;
//	CAL_BT_DIV.Location.y=360-84;
	cpGui_CreateButton(&CAL_BT_DIV);
	
//BUTTON =
//	CAL_BT_EQU.Location.x=560+70-112;
//	CAL_BT_EQU.Location.y=360-84;

	cpGui_CreateButton(&CAL_BT_UP_ARROW);
	cpGui_CreateButton(&CAL_BT_DOWN_ARROW);
	
	cpGui_CreateButton(&CAL_BT_EQU);
	
	//BUTTON YES
//	CAL_BT_YES.Location.x=560+70-112;
//	CAL_BT_YES.Location.y=360-84;
	cpGui_CreateButton(&CAL_BT_YES);			
	
	
	
}




//事件
void Cal_Form_Event(TOUCH touch)
{
BUTTON buttemp;
int textlength;
int i;
int dotcou;
uint8_t formaterr_flag=0;
touch.x+=10;
	touch.y+=10;
	if(FormActive[0]==CAL_FORM_SHOW)
		{
		if(touch.status==TOUCH_DOWN)
			{
			EventType[FormActive[0]]=0;
			EventButton=NULL;
			
			
		
			
	//BTNum0

		if((touch.x>=CAL_BTNum0.Location.x)&&(touch.x<CAL_BTNum0.Location.x+CAL_BTNum0.Size.width)&&\
				(touch.y>=CAL_BTNum0.Location.y)&&(touch.y<CAL_BTNum0.Location.y+CAL_BTNum0.Size.high))
			{
			BellOn_Enb();
			cpGui_Button_UpDown(&CAL_BTNum0,TOUCH_DOWN);
			EventButton=&CAL_BTNum0;
				EventType[FormActive[0]]=Button_Type;
				TouchEvent_ObjAddText("0");
				
													if(ShiftKey_flag==1)
										Touch_code_temp=SHIFT_0_KEY_CODE;//shift+0
									else	
										Touch_code_temp=PROG_KEY_CODE;     // 0  **********
									
									KeyExec(Touch_code_temp);
			//	cpGui_TextBox_AddText(&TextBox1,"0");
			}


	//BTNum1

		if((touch.x>=CAL_BTNum1.Location.x)&&(touch.x<CAL_BTNum1.Location.x+CAL_BTNum1.Size.width)&&\
				(touch.y>=CAL_BTNum1.Location.y)&&(touch.y<CAL_BTNum1.Location.y+CAL_BTNum1.Size.high))
			{
				BellOn_Enb();
			cpGui_Button_UpDown(&CAL_BTNum1,TOUCH_DOWN);
			EventButton=&CAL_BTNum1;
				EventType[FormActive[0]]=Button_Type;
				TouchEvent_ObjAddText("1");
				
				Touch_code_temp=NINE_KEY_CODE;		// 1
			
				KeyExec(Touch_code_temp);
			//	cpGui_TextBox_AddText(&TextBox1,"1");
			}



	//BTNum2

		if((touch.x>=CAL_BTNum2.Location.x)&&(touch.x<CAL_BTNum2.Location.x+CAL_BTNum2.Size.width)&&\
				(touch.y>=CAL_BTNum2.Location.y)&&(touch.y<CAL_BTNum2.Location.y+CAL_BTNum2.Size.high))
			{
			BellOn_Enb();
			cpGui_Button_UpDown(&CAL_BTNum2,TOUCH_DOWN);
			EventButton=&CAL_BTNum2;
			EventType[FormActive[0]]=Button_Type;
			TouchEvent_ObjAddText("2");
				
			Touch_code_temp=MOVE_KEY_CODE;		// 2			
				KeyExec(Touch_code_temp);
				//cpGui_TextBox_AddText(&TextBox1,"2");
			}


	//BTNum3

		if((touch.x>=CAL_BTNum3.Location.x)&&(touch.x<CAL_BTNum3.Location.x+CAL_BTNum3.Size.width)&&\
				(touch.y>=CAL_BTNum3.Location.y)&&(touch.y<CAL_BTNum3.Location.y+CAL_BTNum3.Size.high))
			{
				BellOn_Enb();
			cpGui_Button_UpDown(&CAL_BTNum3,TOUCH_DOWN);
			EventButton=&CAL_BTNum3;
				EventType[FormActive[0]]=Button_Type;
				TouchEvent_ObjAddText("3");
				Touch_code_temp=DELETE_KEY_CODE;      //3
				KeyExec(Touch_code_temp);
			//	cpGui_TextBox_AddText(&TextBox1,"3");
			}


	//BTNum4

		if((touch.x>=CAL_BTNum4.Location.x)&&(touch.x<CAL_BTNum4.Location.x+CAL_BTNum4.Size.width)&&\
				(touch.y>=CAL_BTNum4.Location.y)&&(touch.y<CAL_BTNum4.Location.y+CAL_BTNum4.Size.high))
			{
				BellOn_Enb();
			cpGui_Button_UpDown(&CAL_BTNum4,TOUCH_DOWN);
			EventButton=&CAL_BTNum4;
				EventType[FormActive[0]]=Button_Type;
				TouchEvent_ObjAddText("4");
				Touch_code_temp=EIGHT_KEY_CODE;		//4
				KeyExec(Touch_code_temp);
				//cpGui_TextBox_AddText(&TextBox1,"4");
			}


	//BTNum5

		if((touch.x>=CAL_BTNum5.Location.x)&&(touch.x<CAL_BTNum5.Location.x+CAL_BTNum5.Size.width)&&\
				(touch.y>=CAL_BTNum5.Location.y)&&(touch.y<CAL_BTNum5.Location.y+CAL_BTNum5.Size.high))
			{
			BellOn_Enb();
			cpGui_Button_UpDown(&CAL_BTNum5,TOUCH_DOWN);
			EventButton=&CAL_BTNum5;
			EventType[FormActive[0]]=Button_Type;
			TouchEvent_ObjAddText("5");
				Touch_code_temp=NO_KEY_CODE;      // 5
				KeyExec(Touch_code_temp);
				//cpGui_TextBox_AddText(&TextBox1,"5");
			}


	//BTNum6

		if((touch.x>=CAL_BTNum6.Location.x)&&(touch.x<CAL_BTNum6.Location.x+CAL_BTNum6.Size.width)&&\
				(touch.y>=CAL_BTNum6.Location.y)&&(touch.y<CAL_BTNum6.Location.y+CAL_BTNum6.Size.high))
			{
				BellOn_Enb();
			cpGui_Button_UpDown(&CAL_BTNum6,TOUCH_DOWN);
			EventButton=&CAL_BTNum6;
				EventType[FormActive[0]]=Button_Type;
				TouchEvent_ObjAddText("6");
				Touch_code_temp=INSERT_KEY_CODE;      //6
				KeyExec(Touch_code_temp);
				//cpGui_TextBox_AddText(&TextBox1,"6");
			}



	//BTNum7

		if((touch.x>=CAL_BTNum7.Location.x)&&(touch.x<CAL_BTNum7.Location.x+CAL_BTNum7.Size.width)&&\
				(touch.y>=CAL_BTNum7.Location.y)&&(touch.y<CAL_BTNum7.Location.y+CAL_BTNum7.Size.high))
			{
				BellOn_Enb();
			cpGui_Button_UpDown(&CAL_BTNum7,TOUCH_DOWN);
			EventButton=&CAL_BTNum7;
				EventType[FormActive[0]]=Button_Type;
				TouchEvent_ObjAddText("7");
				Touch_code_temp=SEVEN_KEY_CODE;	//7
				KeyExec(Touch_code_temp);
				//cpGui_TextBox_AddText(&TextBox1,"7");
			}


	//BTNum8

		if((touch.x>=CAL_BTNum8.Location.x)&&(touch.x<CAL_BTNum8.Location.x+CAL_BTNum8.Size.width)&&\
				(touch.y>=CAL_BTNum8.Location.y)&&(touch.y<CAL_BTNum8.Location.y+CAL_BTNum8.Size.high))
			{
				BellOn_Enb();
			cpGui_Button_UpDown(&CAL_BTNum8,TOUCH_DOWN);
			EventButton=&CAL_BTNum8;
				EventType[FormActive[0]]=Button_Type;
				TouchEvent_ObjAddText("8");
					Touch_code_temp=YES_KEY_CODE;    // 8
				KeyExec(Touch_code_temp);
		//		NumKey_exec(9);
				//cpGui_TextBox_AddText(&TextBox1,"8");
			}


	//BTNum9

		if((touch.x>=CAL_BTNum9.Location.x)&&(touch.x<CAL_BTNum9.Location.x+CAL_BTNum9.Size.width)&&\
				(touch.y>=CAL_BTNum9.Location.y)&&(touch.y<CAL_BTNum9.Location.y+CAL_BTNum9.Size.high))
			{
				BellOn_Enb();
			cpGui_Button_UpDown(&CAL_BTNum9,TOUCH_DOWN);
			EventButton=&CAL_BTNum9;
				EventType[FormActive[0]]=Button_Type;
				TouchEvent_ObjAddText("9");
					Touch_code_temp=SUB_KEY_CODE;   // 9
				KeyExec(Touch_code_temp);
				//cpGui_TextBox_AddText(&TextBox1,"9");
			}
			
	//BTClear
		if((touch.x>=CAL_BT_CLEAR.Location.x)&&(touch.x<CAL_BT_CLEAR.Location.x+CAL_BT_CLEAR.Size.width)&&\
				(touch.y>=CAL_BT_CLEAR.Location.y)&&(touch.y<CAL_BT_CLEAR.Location.y+CAL_BT_CLEAR.Size.high))
			{
				BellOn_Enb();
			cpGui_Button_UpDown(&CAL_BT_CLEAR,TOUCH_DOWN);
			EventButton=&CAL_BT_CLEAR;
				EventType[FormActive[0]]=Button_Type;
				
				TouchEvent_ObjAddText("");
				TouchEvent_ObjAddText("0");
				
				Touch_code_temp=SIX_KEY_CODE;		// clear 功能C
				KeyExec(Touch_code_temp);
			//cpGui_ChangeText(&TextBox1.Text,"");
			//	TextBox1.Index=0;
			//cpGui_CreateTextBox(&TextBox1);
		
			}		

				//BT DOT
		if((touch.x>=CAL_BT_DOT.Location.x)&&(touch.x<CAL_BT_DOT.Location.x+CAL_BT_DOT.Size.width)&&\
				(touch.y>=CAL_BT_DOT.Location.y)&&(touch.y<CAL_BT_DOT.Location.y+CAL_BT_DOT.Size.high))
			{
				BellOn_Enb();
			cpGui_Button_UpDown(&CAL_BT_DOT,TOUCH_DOWN);
			EventButton=&CAL_BT_DOT;
				EventType[FormActive[0]]=Button_Type;
				
				TouchEvent_ObjAddText(".");
				Touch_code_temp=ADD_KEY_CODE;   //  点“.”
				KeyExec(Touch_code_temp);
			//cpGui_ChangeText(&TextBox1.Text,"");
			//	TextBox1.Index=0;
			//cpGui_CreateTextBox(&TextBox1);
		
			}	
			
				//BT UP_ ARROW
		if((touch.x>=CAL_BT_UP_ARROW.Location.x)&&(touch.x<CAL_BT_UP_ARROW.Location.x+CAL_BT_UP_ARROW.Size.width)&&\
				(touch.y>=CAL_BT_UP_ARROW.Location.y)&&(touch.y<CAL_BT_UP_ARROW.Location.y+CAL_BT_UP_ARROW.Size.high))
			{
				if((WorkMode==AUTO_MODE)||(WorkMode==TEACH_MODE))//自动和示教模式有效
				{
				BellOn_Enb();
			cpGui_Button_UpDown(&CAL_BT_UP_ARROW,TOUCH_DOWN);
			EventButton=&CAL_BT_UP_ARROW;
				EventType[FormActive[0]]=Button_Type;				
			//	TouchEvent_ObjAddText("");
				Touch_code_temp=DENGJU_KEY_CODE;  //==
				KeyExec(Touch_code_temp);		
				}
			}		
			
				//BT DOWN_ ARROW
		if((touch.x>=CAL_BT_DOWN_ARROW.Location.x)&&(touch.x<CAL_BT_DOWN_ARROW.Location.x+CAL_BT_DOWN_ARROW.Size.width)&&\
				(touch.y>=CAL_BT_DOWN_ARROW.Location.y)&&(touch.y<CAL_BT_DOWN_ARROW.Location.y+CAL_BT_DOWN_ARROW.Size.high))
			{
							if((WorkMode==AUTO_MODE)||(WorkMode==TEACH_MODE))//自动和示教模式有效
				{
				BellOn_Enb();
			cpGui_Button_UpDown(&CAL_BT_DOWN_ARROW,TOUCH_DOWN);
			EventButton=&CAL_BT_DOWN_ARROW;
				EventType[FormActive[0]]=Button_Type;				
			//	TouchEvent_ObjAddText("");
				Touch_code_temp=DENGFENG_KEY_CODE;  //==
				KeyExec(Touch_code_temp);		
				}
			}	
			
				//BT EQU
		if((touch.x>=CAL_BT_EQU.Location.x)&&(touch.x<CAL_BT_EQU.Location.x+CAL_BT_EQU.Size.width)&&\
				(touch.y>=CAL_BT_EQU.Location.y)&&(touch.y<CAL_BT_EQU.Location.y+CAL_BT_EQU.Size.high))
			{
				BellOn_Enb();
			cpGui_Button_UpDown(&CAL_BT_EQU,TOUCH_DOWN);
			EventButton=&CAL_BT_EQU;
				EventType[FormActive[0]]=Button_Type;				
			//	TouchEvent_ObjAddText("");
				Touch_code_temp=EQU_TOUCH_CODE;  //==
				KeyExec(Touch_code_temp);
				
				//读取结果显示
				i=0;
				while((CalcResult_Text[i]!=0xff)&&(i<24))
		//	while(CalcResult_Text[i]!)
				{
					
				if(CalcResult_Text[i]<'*')  //  '*'==42(ascii)
					CalInput_TextBox.Text[i]=CalcResult_Text[i]+48;
				else
					CalInput_TextBox.Text[i]=CalcResult_Text[i];
				i++;
				}
				CalInput_TextBox.Text[i]=0;
				cpGui_CreateTextBox(TextBox);//更新显示

	
			//cpGui_ChangeText(&TextBox1.Text,"");
			//	TextBox1.Index=0;
			//cpGui_CreateTextBox(&TextBox1);
		
			}				
			
				//BT ADD
		if((touch.x>=CAL_BT_ADD.Location.x)&&(touch.x<CAL_BT_ADD.Location.x+CAL_BT_ADD.Size.width)&&\
				(touch.y>=CAL_BT_ADD.Location.y)&&(touch.y<CAL_BT_ADD.Location.y+CAL_BT_ADD.Size.high))
			{
				BellOn_Enb();
			cpGui_Button_UpDown(&CAL_BT_ADD,TOUCH_DOWN);
			EventButton=&CAL_BT_ADD;
				EventType[FormActive[0]]=Button_Type;
				
				TouchEvent_ObjAddText("+");
				
				Touch_code_temp=REV_KEY_CODE;   //  +
					KeyExec(Touch_code_temp);
			//cpGui_ChangeText(&TextBox1.Text,"");
			//	TextBox1.Index=0;
			//cpGui_CreateTextBox(&TextBox1);
		
			}			
			
				//BT SUB
		if((touch.x>=CAL_BT_SUB.Location.x)&&(touch.x<CAL_BT_SUB.Location.x+CAL_BT_SUB.Size.width)&&\
				(touch.y>=CAL_BT_SUB.Location.y)&&(touch.y<CAL_BT_SUB.Location.y+CAL_BT_SUB.Size.high))
			{
				BellOn_Enb();
			cpGui_Button_UpDown(&CAL_BT_SUB,TOUCH_DOWN);
			EventButton=&CAL_BT_SUB;
				EventType[FormActive[0]]=Button_Type;
				
				TouchEvent_ObjAddText("-");
				Touch_code_temp=OPTION_KEY_CODE;    //减号  -
					KeyExec(Touch_code_temp);
			//cpGui_ChangeText(&TextBox1.Text,"");
			//	TextBox1.Index=0;
			//cpGui_CreateTextBox(&TextBox1);		
			}		

			
							//BT MUL
		if((touch.x>=CAL_BT_MUL.Location.x)&&(touch.x<CAL_BT_MUL.Location.x+CAL_BT_MUL.Size.width)&&\
				(touch.y>=CAL_BT_MUL.Location.y)&&(touch.y<CAL_BT_MUL.Location.y+CAL_BT_MUL.Size.high))
			{
				BellOn_Enb();
			cpGui_Button_UpDown(&CAL_BT_MUL,TOUCH_DOWN);
			EventButton=&CAL_BT_MUL;
				EventType[FormActive[0]]=Button_Type;
				
				TouchEvent_ObjAddText("*");
					Touch_code_temp=MUL_TOUCH_CODE;  // *
					KeyExec(Touch_code_temp);
			//cpGui_ChangeText(&TextBox1.Text,"");
			//	TextBox1.Index=0;
			//cpGui_CreateTextBox(&TextBox1);		
			}	
			
			
							//BT DIV
		if((touch.x>=CAL_BT_DIV.Location.x)&&(touch.x<CAL_BT_DIV.Location.x+CAL_BT_DIV.Size.width)&&\
				(touch.y>=CAL_BT_DIV.Location.y)&&(touch.y<CAL_BT_DIV.Location.y+CAL_BT_DIV.Size.high))
			{
				BellOn_Enb();
			cpGui_Button_UpDown(&CAL_BT_DIV,TOUCH_DOWN);
			EventButton=&CAL_BT_DIV;
				EventType[FormActive[0]]=Button_Type;
				
				TouchEvent_ObjAddText("/");
					Touch_code_temp=DIV_TOUCH_CODE;  // 除 /
					KeyExec(Touch_code_temp);
			//cpGui_ChangeText(&TextBox1.Text,"");
			//	TextBox1.Index=0;
			//cpGui_CreateTextBox(&TextBox1);		
			}		

			
	//BT YES

		if((touch.x>=CAL_BT_YES.Location.x)&&(touch.x<CAL_BT_YES.Location.x+CAL_BT_YES.Size.width)&&\
				(touch.y>=CAL_BT_YES.Location.y)&&(touch.y<CAL_BT_YES.Location.y+CAL_BT_YES.Size.high))
			{
				BellOn_Enb();
				cpGui_Button_UpDown(&CAL_BT_YES,TOUCH_DOWN);
				EventButton=&CAL_BT_YES;
				EventType[FormActive[0]]=Button_Type;	
				
				TouchEvent_ObjAddText("");
				TouchEvent_ObjAddText("0");

				
				Touch_code_temp=DOWN_KEY_CODE;   // 确定	
				KeyExec(Touch_code_temp);
				

				
			}
			
		//Cal_TextBox
		if((touch.x>=CalInput_TextBox.Location.x)&&(touch.x<(CalInput_TextBox.Location.x+CalInput_TextBox.Size.width-8))&&\
				(touch.y>=CalInput_TextBox.Location.y)&&(touch.y<CalInput_TextBox.Location.y+CalInput_TextBox.Size.high))
			{
			BellOn_Enb();
			EventButton=NULL;//&MessageBT;
			FormActive[0]=0;
			Cal_Form_Show_Flag=0;
			EventType[FormActive[0]]=NULL;//Button_Type;							
						//	(150,150,500,300);		
			CurrentArea_recover5(CAL_DIS_X,CAL_DIS_Y+50,400,420-30);			

				switch(WorkMode)
				{
										case  PROG_MODE://编程画面下
						case AUTO_MODE://自动主画面下
						case AUTO_PLUS_MODE://自动F5++
						case AUTO_MINUS_MODE://自动F6--
						case TEACH_MODE://示教 模式
						//case AUTO_TO_SELF_MODE:   //自动-->自刀过度 模式
						case SELF_CUT_MODE:  //自刀主 模式
						case TEACH_PLUS_MODE: //自刀 F5++
						case TEACH_MINUS_MODE://自刀 F6--
							Schedule_dis(SCHEDULE_X,SCHEDULE_Y);//进度
							ProgressBar_dis(OnePro_head.pro_knifeSUM,Knife_order);  //进度条 显示
							//StepOrder_dis(Knife_order);//步骤更新
//////							 	if(Cal_Form_Show_Flag==0)
//////									{
//////									ProgressBar_dis(OnePro_head.pro_knifeSUM,K_temp);  //进度条 显示
//////									}
									break;
								}
			GLCD_SetWindow_Fill(CALCUL_RESULT_X,CALCUL_RESULT_Y,CALCUL_RESULT_X+CALCUL_RESULT_W,CALCUL_RESULT_Y+CALCUL_RESULT_H,BLUE_COLOR,0xffff);//结果显示区
			CalcResultNums_dis(CalcResult_Text);//恢复结果显示
			//	return;
			}	//			
			
		
		//F3 插入 自动模式下有效
		if((touch.x>=F3_BUTTON_X)&&(touch.x<(F3_BUTTON_X+35))&&\
				(touch.y>=F3_BUTTON_Y)&&(touch.y<F3_BUTTON_Y+40))
			{
			if(WorkMode==AUTO_MODE)//自动模式有效
				{
				BellOn_Enb();
				EventButton=NULL;//&MessageBT;

				TouchEvent_ObjAddText("");
				TouchEvent_ObjAddText("0");
				
				Touch_code_temp=RETURN_KEY_CODE;   //F3 插入
				KeyExec(Touch_code_temp);
				}				
			}

			
		//F4 删除 自动模式下有效
		if((touch.x>=F4_BUTTON_X)&&(touch.x<(F4_BUTTON_X+35))&&\
				(touch.y>=F4_BUTTON_Y)&&(touch.y<F4_BUTTON_Y+40))
			{
			if(WorkMode==AUTO_MODE)//自动模式有效
				{
				BellOn_Enb();
				EventButton=NULL;//&MessageBT;

				TouchEvent_ObjAddText("");
				TouchEvent_ObjAddText("0");
				
				Touch_code_temp=MANUAL_KEY_CODE;   //F4 删除
				KeyExec(Touch_code_temp);
				}				
			}

				
			

		//快进触摸
		if((touch.x>=FAST_FWD_X)&&(touch.x<(FAST_FWD_X+70))&&\
				(touch.y>=FAST_FWD_Y)&&(touch.y<FAST_FWD_Y+45))
			{
							if(WorkMode==MANUAL_MODE)//手动模式有效
			{
			BellOn_Enb();
			EventButton=NULL;//&MessageBT;
				
			Touch_code_temp=FAST_AHEAD_KEY_CODE;   //快进-----
			KeyExec(Touch_code_temp);
			}
				
			}
			
		//快退触摸
		if((touch.x>=FAST_BACK_X)&&(touch.x<(FAST_BACK_X+70))&&\
				(touch.y>=FAST_BACK_Y)&&(touch.y<FAST_BACK_Y+45))
			{
							if(WorkMode==MANUAL_MODE)//手动模式有效
			{
			BellOn_Enb();
			EventButton=NULL;//&MessageBT;
				
			Touch_code_temp=FAST_BACK_KEY_CODE;     //快退------------------
			KeyExec(Touch_code_temp);
			}
				
			}
			
		//前进触摸
		if((touch.x>=FRONT_PAGE_X)&&(touch.x<(FRONT_PAGE_X+70))&&\
				(touch.y>=FRONT_PAGE_Y)&&(touch.y<FRONT_PAGE_Y+45))
			{
							if(WorkMode==MANUAL_MODE)//手动模式有效
			{
							BellOn_Enb();
			EventButton=NULL;//&MessageBT;
				
			Touch_code_temp=NEXTKNIFE_KEY_CODE;  //前进按键
			KeyExec(Touch_code_temp);
			}
			}

		//后退触摸
		if((touch.x>=BACK_PAGE_X)&&(touch.x<(BACK_PAGE_X+70))&&\
				(touch.y>=BACK_PAGE_Y)&&(touch.y<BACK_PAGE_Y+45))
			{
							if(WorkMode==MANUAL_MODE)//手动模式有效
			{
							BellOn_Enb();
			EventButton=NULL;//&MessageBT;
				
			Touch_code_temp=ADJUST_KEY_CODE;    //后退按键
			KeyExec(Touch_code_temp);
			}
			}
			
		//停止触摸
		if((touch.x>=STOP_X)&&(touch.x<(STOP_X+70))&&\
				(touch.y>=STOP_Y)&&(touch.y<STOP_Y+45))
			{
			if(WorkMode==MANUAL_MODE)//手动模式有效
			{				
							BellOn_Enb();
			EventButton=NULL;//&MessageBT;
				
			Touch_code_temp=STOP_KEY_CODE; //停止 触摸键
			KeyExec(Touch_code_temp);
			}
				
			}

		//运行触摸
		if((touch.x>=RUN_BUTT_X)&&(touch.x<(RUN_BUTT_X+70))&&\
				(touch.y>=RUN_BUTT_Y)&&(touch.y<RUN_BUTT_Y+45))
			{
			if(WorkMode==MANUAL_MODE)//手动模式有效
			{
			BellOn_Enb();
			EventButton=NULL;//&MessageBT;
			
			TouchEvent_ObjAddText("");
			TouchEvent_ObjAddText("0");
				
			Touch_code_temp=UP_KEY_CODE;   ///////////运行按键
			KeyExec(Touch_code_temp);			
			}				
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
else
	{
		if(WorkMode!=READ_PRO_MESS_MODE)//程序名修改时不弹出
		{
		if((touch.x>=600)&&(touch.x<750)&&\
				(touch.y>=CalInput_TextBox.Location.y-50)&&(touch.y<(CalInput_TextBox.Location.y-50+40)))
			{				
			if(touch.status==TOUCH_DOWN)
				{
					//设置、自加、自减、自刀、查找模式不入
				if((WorkMode!=MANUAL_TOOLS_MODE)&&(WorkMode!=AUTO_PLUS_MODE)&&(WorkMode!=TEACH_PLUS_MODE)&&(WorkMode!=AUTO_MINUS_MODE)\
					&&(WorkMode!=TEACH_MINUS_MODE)	&&(WorkMode!=SELF_CUT_MODE)&&(WorkMode!=READ_PRO_MODE)&&(WorkMode!=MANUAL_PASS_MODE))							
					{
					if(Cal_Form_Show_Flag==0)
						{
						BellOn_Enb();				
						EventType[FormActive[0]]=0;
						EventButton=NULL;
						CAL_Form_Init();
						}
					}		
				}				
		//	cpGui_Button_UpDown(&CAL_BTNum0,TOUCH_DOWN);
	//		EventButton=&CAL_BTNum0;
		//		EventType[FormActive[0]]=Button_Type;
		//		TouchEvent_ObjAddText("0");
			//	cpGui_TextBox_AddText(&TextBox1,"0");
			}
		}
	}
}


void Cal_Form_Manual_Exit(void)
{
if(Cal_Form_Show_Flag!=0)
		{
		//	BellOn_Enb();
			EventButton=NULL;//&MessageBT;
			FormActive[0]=0;
			Cal_Form_Show_Flag=0;
			EventType[FormActive[0]]=NULL;//Button_Type;							
						//	(150,150,500,300);		
			CurrentArea_recover5(CAL_DIS_X,CAL_DIS_Y+50,400,420-30);			
		}	
	
}
