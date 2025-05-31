#ifndef __COMM_H
#define __COMM_H

//#include"board.h"
//#include"sys.h"
//#include"uart.h"
//#include"drv_glcd.h"
//#include"writenorflash.h"
//#include"io.h"
//#include"file.h"

#include "main.h"



#define COMMHEAD1 0xaa
#define COMMHEAD2 0x55
#define COMMD_WRITE_BMP_FLASH 0x1
#define COMMD_WRITE_FILE_FLASH 0x2
#define COMMD_READ_FLASH_SDRAM 0x3
#define COMMD_WRITE_SDRAM_FLASH 0x4
#define COMMD_ERASE_FLASH 0x5
#define COMMD_CLR_SCREEN 0x6
#define COMMD_DISPLAY_BMP 0x7
#define COMMD_WRITE_SPI_FLASH 0x8


#define COMMCOMMDADD 2
#define COMMADDERADD 3
#define COMMLENTHADD 6




#define DOWNFILE_FILE_DELETE     0x20 //删除一个文件
#define DOWNFILE_FILE_CREATE     0x21 //建立一个文件
#define DOWNFILE_FILE_CREATE_DIR 0x22 //建立一个目
#define DOWNFILE_FILE_SEND       0x23 //发送一个文件
#define DOWNFILE_FILE_SEND_NAME  0x24 //发送一个文件名
#define DOWNFILE_FILE_FORMAT     0x25 //系统格式化
#define DOWNFILE_FILE_BOOT       0x26 //下载BOOTLOAD
#define DOWNFILE_FILE_APP		 0x27 //下载APP





extern unsigned char Rec_Data[60];
extern int CommCou;
extern char CommHead_Flag;  //接收帧头标志位
extern char CommFrame_Flag; //接收帧标志位
extern char CommCommd;   //命令
extern int CommAdder;   //地址
extern int CommFileLenth; //文件长度
extern int CommLengthTemp;
extern char CommEnd_Flag;  //帧结束标志位

extern int BMP_Hight;
extern int BMP_Width;
extern int BMP_Bit;
extern int BMP_highttemp1;
extern int BMP_widthtemp1;

extern int ColorData[10];
extern int ColorCou;

extern char PicDisplay_Flag;
extern int R,G,B;
extern int Color;

extern unsigned short *fPtr;

extern unsigned char *dfPtr;

extern void CommExec(unsigned char rx_data);

#endif
