/**************************************************************************//**
* @file     main.c
* @version  V1.00
* $Revision: 2 $
* $Date: 15/06/12 9:11a $
* @brief    NUC970 LCD sample source file
*
* @note
* Copyright (C) 2015 Nuvoton Technology Corp. All rights reserved.
*****************************************************************************/
#include <stdio.h>
#include <string.h>

#include "main.h"

#include "chndot.h"
#include "drv_glcd.h"

#include "pic_exec.h"
#include "down_status.h"

#include "file.h"
#include "io.h"

#include "bmp.h"
#include "nandflash.h"
#include "timer.h"
#include "port.h"

#include "nand_config.h"
#include "io.h"

#include "chndot.h"

unsigned char *dfPtr;

Int32U uFlashID;


#define SDRAM_BASE_ADDR 0x80000000
#define VECTOR_BASE_ADDR 0x00100000

#define TIME_BCOL   0xCE79 //

#define DISPLAY_RGB565
//#define DISPLAY_RGB888

#define EXT_SDRAM 0x00000000//0x00000058// 0x80000000//0x8003285c
typedef void (*fnc) (void);
const fnc AppEntry = (fnc)EXT_SDRAM;

unsigned char SecTemp;   

unsigned char Sec,Min,Hour,Dow,Dom,Month;
int Doy,Year;


Int32U CommFileLenth;
int Uart3_Data;
int Uart8Data;
int Uart9Data;




__align(32) uint32_t u32CursorBuf[512];

void Time_dis(void);//
 void SDRAM_Init(void);

int32_t main(void)
{
	
	unsigned char spi_Data[16];
unsigned int temptime;
unsigned char NFBuf[4096];
pInt32U cp1,cp2;

  //int j,n,k;
 int BarCou;
 Int32U j;
Int16U d,Ms100t;   
Int16U Cou=0;
unsigned char tempbootfolder;
unsigned char otherbootfolder;
int NumberCou;
				 
pInt16U ptr;//				 
Int32U temp;
	
    uint8_t *u8FrameBufPtr, *u8OSDFrameBufPtr;
Int32U i;

    *((volatile unsigned int *)REG_AIC_MDCR)=0xFFFFFFFF;  // disable all interrupt channel
    *((volatile unsigned int *)REG_AIC_MDCRH)=0xFFFFFFFF;  // disable all interrupt channel

    outpw(REG_CLK_HCLKEN, 0x0527);
    outpw(REG_CLK_PCLKEN0, 0);
    outpw(REG_CLK_PCLKEN1, 0);

    sysDisableCache();
    sysFlushCache(I_D_CACHE);
    sysEnableCache(CACHE_WRITE_BACK);
			outpw(REG_CLK_PCLKEN0, 8);
    sysInitializeUART();
	

//SDRAM_Init();

		BellOUT_DirInit;
//  BellOUT_ON;
	//	GLCD_Buffer_Fill(0);
 //   GLCD_Init();
	//	  BellOUT_OFF;
		
	//	IO_Test();
	//	I2C_Test();
	//	Sys_DevInit();////系统初始化
	//		KeyInit();
	//	Gtp_IO_Init();
		while(Nand_Config()!=0);//nand 初始化	
		//SD_main();

		
//	GLCD_Buffer_Fill(BLUE_COLOR);
//FileRead("字库_0x20000.FON",(unsigned char *)df_zk_sdram);
 //ASCII_Printf("LoadingOK",ASCII1632_MODE,ASCII1632_WIDTH,ASCII1632_HIGH,ASCII1632,40,180,0xffff,0);
	//	Process_Main();//////跳转到老7寸程序 处理
 

 BellOUT_ON;
 i=1000000;
 while(i--);
 BellOUT_OFF;
  i=1000000;
 while(i--);
 BellOUT_ON;
  i=1000000;
 while(i--);
 BellOUT_OFF;

 
BootFolder=FileLoadBootApp()-0x30;
if((BootFolder<1)||(BootFolder>6))//如果启动项不是1-6个应用序号，强制从第1个读取资源文件
	{
	BootFolder=1;
	}

if((FileFolderRead("APP.bin",(unsigned char*)SDRAM_BASE_ADDR)==1))//&&(FileFolderRead("Vector.bin",(unsigned char*)VECTOR_BASE_ADDR)==1))
{
  ASCII_Printf("App Load Ok!",ASCII1632_MODE,ASCII1632_WIDTH,ASCII1632_HIGH,ASCII1632,360,220,0,0xffff);
}
else
{
tempbootfolder=BootFolder;
otherbootfolder=8;
BootFolder=8;
while(1)
	{
	for(i=1;i<7;i++)
		{
		BootFolder=i;
			if(FileFolderRead("APP.bin",(unsigned char*)SDRAM_BASE_ADDR)==1)
		//if((FileFolderRead("APP.bin",(unsigned char*)SDRAM_BASE_ADDR)==1)&&(FileFolderRead("Vector.bin",(unsigned char*)VECTOR_BASE_ADDR)==1))
			{                        
       break;
			}
		}
 if((BootFolder<7)&&(i<7))
          break;
 
 ASCII_Printf("NoAPPFile",ASCII1632_MODE,ASCII1632_WIDTH,ASCII1632_HIGH,ASCII1632,360,220,0,0xffff);
	while(1)
		{
		 BellOUT_ON;
		 i=1000000;
		 while(i--);
		 BellOUT_OFF;
		 i=1000000;
		 while(i--);
	//	ASCII_Printf("No APP FILE!",ASCII1632_MODE,ASCII1632_WIDTH,ASCII1632_HIGH,ASCII1632,310,185,0,0xffff);
		}
	}
}


////cp2=(Int32U*)0;
////cp1=(Int32U*)SDRAM_BASE_ADDR;
////for(i=0;i<64;i++)
////  {
////  *cp2++=*cp1++;  
////  }

 AppEntry();
//GoToJumpAddress(App_add, MACH_TYPE);  //跳转地址到应用程序

//StartPic_dis();//显示开机画面
//Uart_mod=0;

	while(1)
	{

   }
 }

 
 void SDRAM_Init(void)
 {
	outpw((pInt32U)0xB0000220,0x01000000);
outpw((pInt32U)0xB0000264 , 0xC0000018);
outpw((pInt32U)0xB0000220 , 0x01000018);
outpw((pInt32U)0xB00000B8 , 0x000FFFFF);
outpw((pInt32U)0xB0001800 , 0x00030476);
outpw((pInt32U)0xB0001804 , 0x00000021);
outpw((pInt32U)0xB0001804 , 0x00000023);
outpw((pInt32U)0xB0001804 , 0x00000027);
outpw((pInt32U)0xB0001818 , 0x00000132);
outpw((pInt32U)0xB000181C , 0x00004000);
outpw((pInt32U)0xB0001810 , 0x0000000E);
outpw((pInt32U)0xB0001804 , 0x0000002B);
outpw((pInt32U)0xB0001804 , 0x0000002B);
outpw((pInt32U)0xB0001804 , 0x0000002B);
outpw((pInt32U)0xB0001818 , 0x00000032);
outpw((pInt32U)0xB000181C , 0x00004381);
outpw((pInt32U)0xB000181C , 0x00004001);
outpw((pInt32U)0xB0001804 , 0x00000020);
outpw((pInt32U)0xB0001834 , 0x00888800);
outpw((pInt32U)0xB0001834 , 0x00888800);

	 
	 
 }


void Time_dis(void)
{
	
//////	
//////volatile Int16U px,py;
//////volatile Int16U gap1,gap2,gap3;
//////Int16U Num_color,Back_color;
//////     
//////px=530;
//////py=2;
//////gap1=50,gap2=12,gap3=24;
//////Num_color=BLACK_COLOR;
//////Back_color=TIME_BCOL;
//////if(Sec!=SecTemp)
//////	{
//////	SecTemp=Sec;
//////   Bcd[0]=2+48;
//////   Bcd[1]=0+48;
//////   Bcd[2]=(Year>>4)+48;
//////   Bcd[3]=(Year&0xf)+48;
//////   Bcd[4]=0;
//////   Printf24(Bcd,px,py,Num_color,1,Back_color);px+=gap1;
//////   Printf24("-",px,py,Num_color,1,Back_color);px+=gap2;
//////   
//////   Bcd[0]=(Month>>4)+48;
//////   Bcd[1]=(Month&0xf)+48;
//////   Bcd[2]=0;
//////   Bcd[3]=0;
//////   Bcd[4]=0;
//////   Printf24(Bcd,px,py,Num_color,1,Back_color);px+=gap3;
//////   Printf24("-",px,py,Num_color,1,Back_color);px+=gap2;

//////   Bcd[0]=(Dom>>4)+48;
//////   Bcd[1]=(Dom&0xf)+48;
//////   Bcd[2]=0;
//////   Bcd[3]=0;
//////   Bcd[4]=0;
//////   Printf24(Bcd,px,py,Num_color,1,Back_color);px+=gap1;

//////   Bcd[0]=(Hour>>4)+48;
//////   Bcd[1]=(Hour&0xf)+48;
//////   Bcd[2]=0;
//////   Bcd[3]=0;
//////   Bcd[4]=0;
//////   Printf24(Bcd,px,py,Num_color,1,Back_color);px+=gap3;
//////   Printf24(":",px,py,Num_color,1,Back_color);px+=gap2;

//////   Bcd[0]=(Min>>4)+48;
//////   Bcd[1]=(Min&0xf)+48;
//////   Bcd[2]=0;
//////   Bcd[3]=0;
//////   Bcd[4]=0;
//////   Printf24(Bcd,px,py,Num_color,1,Back_color);px+=gap3;
//////   Printf24(":",px,py,Num_color,1,Back_color);px+=gap2;
//////   
//////   Bcd[0]=(Sec>>4)+48;
//////   Bcd[1]=(Sec&0xf)+48;
//////   Printf24(Bcd,px,py,Num_color,1,Back_color);
//////	}
}

