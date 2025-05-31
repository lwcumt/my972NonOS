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
#include "spi_config.h"
#include "uart_config.h"

#include "comm.h"
#include "chndot.h"
#include "drv_glcd.h"
#include "pic.h"
#include "pic_exec.h"
#include "down_status.h"
#include "download.h"
#include "file.h"
#include "word_lib.h"

#include "servo.h"
#include "bmp.h"
#include "nandflash.h"
#include "timer.h"
#include "port.h"
#include "touch.h"
#include "tsc2046.h"

#include "name_input.h"
#include "pinyin.h"
#include "nand_config.h"
#include "i2c_config.h"
#include "gtp.h"

#include "sdh.h"
#include "ff.h"
#include "diskio.h"

#include "sd_config.h"
#include "sdcopy.h"
#include "gtp_touch.h"
#include "comm_touch.h"

#include "sysiotest.h"

#include "datagui.h"
#include "touchevent.h"
#include "waveform.h"
#include "setupform.h"
#include "mainform.h"

#include "key.h"
#include "process_main.h"
#include "mtppass.h"



Int32U uFlashID;




#define DISPLAY_RGB565
//#define DISPLAY_RGB888



__align(32) uint32_t u32CursorBuf[512];

int32_t main(void)
{
    uint8_t *u8FrameBufPtr, *u8OSDFrameBufPtr, i;

    *((volatile unsigned int *)REG_AIC_MDCR)=0xFFFFFFFF;  // disable all interrupt channel
    *((volatile unsigned int *)REG_AIC_MDCRH)=0xFFFFFFFF;  // disable all interrupt channel

	
//	ASCII_Printf("App Init...!",ASCII1632_MODE,ASCII1632_WIDTH,ASCII1632_HIGH,ASCII1632,0,0,0,0xffff);
    outpw(REG_CLK_HCLKEN, 0x0527);
    outpw(REG_CLK_PCLKEN0, 0);
    outpw(REG_CLK_PCLKEN1, 0);

    sysDisableCache();
	  sysInvalidCache();


    sysFlushCache(I_D_CACHE);
		sysSetMMUMappingMethod(MMU_DIRECT_MAPPING);
    sysEnableCache(CACHE_WRITE_BACK);
		outpw(REG_CLK_PCLKEN0, 8);
    sysInitializeUART();
	


    
	//	IO_Test();
	//	I2C_Test();
	sysprintf("App is Runing...\r\n");
		Sys_DevInit();////系统初始化
		sysprintf("Device Init...\r\n");
			KeyInit();

////    /* enable MTP clock */
////	outpw(REG_CLK_PCLKEN1, inpw(REG_CLK_PCLKEN1) | (1 << 26));
////			ReadMtpKey();
////			
			
		#ifdef CAP_TOUCH			//touch.h 里定义
		
		Gtp_IO_Init();//电容触摸屏初始化
				 
		#else
				Uart8_Init();//-------touchcomm    触摸通讯  UART8	
		#endif
			
			
		//while(Nand_Config()!=0);//nand 初始化	
		Nand_Config();File_Init();
		//SD_main();
		SDInsert_Check();
		//Nand_Config();
		Lcd_SetBirght(0);
		GLCD_Buffer_Fill(BLUE_COLOR);
	//	Test_Main();
		
	//	ASCII_Printf("Goto Main...",ASCII1632_MODE,ASCII1632_WIDTH,ASCII1632_HIGH,ASCII1632,0,0,0,0xffff);
////	SysIO_Test();//输出 IO测试
		
//FileRead("字库_0x20000.FON",(unsigned char *)df_zk_sdram);
 //ASCII_Printf("LoadingOK",ASCII1632_MODE,ASCII1632_WIDTH,ASCII1632_HIGH,ASCII1632,40,180,0xffff,0);
		Process_Main();//////跳转到老7寸程序 处理
    while(1)
		{
		CheckOp_IN();
		read_time();
		}
}
/*** (C) COPYRIGHT 2015 Nuvoton Technology Corp. ***/

