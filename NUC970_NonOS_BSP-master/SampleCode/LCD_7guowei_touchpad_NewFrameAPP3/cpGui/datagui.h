#ifndef _DATA_GUI_H
#define _DATA_GUI_H


#include "main.h"

//////#define USER_NEW_FRAME

#define CAPCHG_CLEAR_PAGE 1
#define CAPCHG_SHOW_CHARGING_PAGE 2
#define CAPCHG_SHOW_DISCHARGING_PAGE 3


#define CAP_CHG_PIN           BIT5
#define CAP_CHG_DIR_OUT()   (GPIO_OpenBit(GPIOA, CAP_CHG_PIN, DIR_OUTPUT, NO_PULL_UP))
#define CAP_CHG_OFF()	  GPIO_ClrBit(GPIOA,CAP_CHG_PIN)
#define CAP_CHG_ON()	  GPIO_SetBit(GPIOA,CAP_CHG_PIN)


#define CAP_DISCHG_PIN           BIT6
#define CAP_DISCHG_DIR_OUT()   (GPIO_OpenBit(GPIOA, CAP_DISCHG_PIN, DIR_OUTPUT, NO_PULL_UP))
#define CAP_DISCHG_OFF()	  GPIO_ClrBit(GPIOA,CAP_DISCHG_PIN)
#define CAP_DISCHG_ON()	  GPIO_SetBit(GPIOA,CAP_DISCHG_PIN)

#define CAPCHG_DISCHARG_ERR 1
#define CAPCHG_CHARG_ERR 2

/*
            chartArea1.Name = "ChartArea1";
            this.chart1.ChartAreas.Add(chartArea1);
            legend1.Name = "Legend1";
            this.chart1.Legends.Add(legend1);
            this.chart1.Location = new System.Drawing.Point(372, 404);
            this.chart1.Name = "chart1";
            series1.ChartArea = "ChartArea1";
            series1.Legend = "Legend1";
            series1.Name = "???";
            this.chart1.Series.Add(series1);
            this.chart1.Size = new System.Drawing.Size(830, 250);
            this.chart1.TabIndex = 13;
            this.chart1.Text = "chart1";
						
						*/
						
#define Button_Type 1
#define PictureBox_Type 2
#define TextBox_Type 3
#define Label_Type 4
#define Chart_Type 5
#define CheckBox_Type 6
#define RadioButton_Type 7

#define cSystemColor (240<<16)+(240<<8)+240

#define None (1<<24)

#define cDisabledColor (160<<16)+(160<<8)+160
		
typedef struct
{
unsigned short x;
unsigned short y;
}LOCATION;

typedef struct
{
unsigned short width;
unsigned short high;	
}SIZE;


//chart 控件
typedef struct 
{
unsigned char Type;
unsigned char Enabled;
LOCATION Location;	//定位
SIZE Size; //总大小
unsigned int bkColor;	//背景色
unsigned short FontWidth;//字体宽度
unsigned short FontHigh;
unsigned short RowData;
unsigned char RowStep;
unsigned short ColData;
unsigned char ColStep;	
	
//数据层
unsigned short ScaleView;//
unsigned short LineWidth;
unsigned int LineColor;	
}CHART;

//button 控件
typedef struct 
{
unsigned char Type;
unsigned char Enabled;
LOCATION Location;	//定位
SIZE Size; //总大小
unsigned int bkColor;	//背景色
unsigned short FontWidth;//字体宽度
unsigned short FontHigh;
char Text[16];	
}BUTTON;

//label 控件
typedef struct 
{
unsigned char Type;
unsigned char Enabled;
LOCATION Location;	//定位
SIZE Size; //总大小
unsigned int textColor;
unsigned int bkColor;	//背景色
unsigned short FontWidth;//字体宽度
unsigned short FontHigh;
char Text[32];	
}LABEL;


//checkbox 控件
typedef struct 
{
unsigned char Type;
unsigned char Enabled;
LOCATION Location;	//定位
SIZE Size; //总大小
unsigned int checkBoxColor;
unsigned int checkBoxSelectColor;
unsigned int textColor;
unsigned int bkColor;	//背景色
unsigned short FontWidth;//字体宽度
unsigned short FontHigh;
unsigned char Checked;
char Text[32];	
}CHECKBOX;



//radiobutton 控件
typedef struct 
{
unsigned char Type;
unsigned char Enabled;
LOCATION Location;	//定位
SIZE Size; //总大小
unsigned int radiobuttonColor;
unsigned int radiobuttonSelectColor;
unsigned int textColor;
unsigned int bkColor;	//背景色
unsigned short FontWidth;//字体宽度
unsigned short FontHigh;
unsigned char Checked;
char Text[32];	
}RADIOBUTTON;


//textbox 控件
typedef struct 
{
unsigned char Type;
unsigned char Enabled;
unsigned char Focus;   //Focus 
LOCATION Location;	//定位
SIZE Size; //总大小
unsigned int textboxColor;
unsigned int textboxSelectColor;
unsigned int textColor;
unsigned int bkColor;	//背景色
unsigned short FontWidth;//字体宽度
unsigned short FontHigh;
unsigned short Index;//当前索引
unsigned short  MaxCount;
char Text[64];	
}TEXTBOX;


//picturebox 控件
typedef struct 
{
unsigned char Type;
unsigned char Enabled;
unsigned char TouchEnabled;
unsigned char Focus;   //Focus 
LOCATION Location;	//定位
SIZE Size; //总大小
unsigned int picturebkColor;
unsigned int textboxSelectColor;
unsigned int textColor;
unsigned int textbkColor;	//背景色
unsigned short FontWidth;//字体宽度
unsigned short FontHigh;
unsigned short Index;
unsigned short  MaxCount;
char Text[64];	
char ImageName[32];
unsigned int picAdder;
}PICTUREBOX;


typedef union{
	int i;
	char b;
////PICTUREBOX;
//TEXTBOX;
}CONTROLBOX;




extern BUTTON Button1;

extern BUTTON Button2;
extern BUTTON BTNum0;
extern BUTTON BTNum1;
extern BUTTON BTNum2;
extern BUTTON BTNum3;
extern BUTTON BTNum4;
extern BUTTON BTNum5;
extern BUTTON BTNum6;
extern BUTTON BTNum7;
extern BUTTON BTNum8;
extern BUTTON BTNum9;
extern BUTTON BTClear;
extern BUTTON BTDot;
extern BUTTON SaveButton;

extern LABEL MainFormLabel;

extern LABEL Label1;
extern LABEL TimeLabel;
extern CHECKBOX CheckBox1;
extern RADIOBUTTON RadioButton1;
extern TEXTBOX TextBox1;
extern PICTUREBOX PictureBox1;


extern unsigned char *Focus; 
extern unsigned char *OldFocus;
extern unsigned char *FormActive[128];


extern unsigned short cpGui_ColorChange(unsigned int color);
extern void cpGui_ChangeText(char *type,char *text);

extern void cpGui_CreateChart(CHART chart);
extern void cpGui_ChartRedraw(CHART chart,unsigned short *buf,unsigned short length);

extern void cpGui_CreateButton(BUTTON button);
extern void cpGui_Button_UpDown(BUTTON button,unsigned char sta);

extern void cpGui_CreateLabel(LABEL label);

extern void cpGui_CreateCheckBox(CHECKBOX checkbox);
extern void cpGui_CreateRadioButton(RADIOBUTTON radiobutton);

extern void cpGui_CreatePictureBox(PICTUREBOX *picturebox);

extern int cpGui_TextBox_AddText(TEXTBOX *textbox,char *text);
extern void cpGui_CreateTextBox(TEXTBOX *textbox);



#endif 
