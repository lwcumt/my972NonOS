#ifndef _GTP_H
#define _GTP_H

#include "main.h"


#define TOUCH_H_SIZE 800		//定义触屏分辩率
#define TOUCH_V_SIZE 600


#define LEFT 0
#define RIGHT 1

#define TOUCH_ORIGIN RIGHT

#define TOUCH_SHIFT_X 8
#define TOUCH_SHIFT_Y 6

//#define GTP_TYPE "911"
#define GTP_TYPE "928"

#define GTP_PD_PIN           BIT14
#define GTP_PD_DIR_OUT()   (GPIO_OpenBit(GPIOG, GTP_PD_PIN, DIR_OUTPUT, NO_PULL_UP))
#define GTP_PD_Low()	  GPIO_ClrBit(GPIOG,GTP_PD_PIN)
#define GTP_PD_High()	  GPIO_SetBit(GPIOG,GTP_PD_PIN)

#define GTP_INT_PIN  BIT13
#define GTP_INT_DIR_IN()     (GPIO_OpenBit(GPIOG, GTP_INT_PIN, DIR_INPUT, NO_PULL_UP))
#define GTP_INT_DIR_IN_UP()  (GPIO_OpenBit(GPIOG, GTP_INT_PIN, DIR_INPUT, PULL_UP))
#define GTP_INT_IN()       GPIO_ReadBit(GPIOG,GTP_INT_PIN)

#define GT911_DEVADD 0x14

#define GTP_REG_SENSOR_ID				0x814A



//IO操作函数	 
#define GT_RST    		PCout(13)	//GT911复位引脚
#define GT_INT    		PCin(1)		//GT911中断引脚	
   	
 
//I2C读写命令	
#define GT_CMD_WR 		0X28     	//写命令
#define GT_CMD_RD 		0X29		//读命令
  
//GT911 部分寄存器定义 
#define GT_CTRL_REG 	0X8040   	//GT911控制寄存器
#define GT_CFGS_REG 	0X8047   	//GT911配置起始地址寄存器
#define GT_CHECK_REG 	0X80FF   	//GT911校验和寄存器
#define GT_PID_REG 		0X8140   	//GT911产品ID寄存器

#define GT_GSTID_REG 	0X814E   	//GT911当前检测到的触摸情况
#define GT_TP1_REG 		0X8150  	//第一个触摸点数据地址
#define GT_TP2_REG 		0X8158		//第二个触摸点数据地址
#define GT_TP3_REG 		0X8160		//第三个触摸点数据地址
#define GT_TP4_REG 		0X8168		//第四个触摸点数据地址
#define GT_TP5_REG 		0X8170		//第五个触摸点数据地址  
 
 

 #define GT911_READ_XY_REG 0x814E	/* 坐标寄存器 */

#define GT911_CLEARBUF_REG 0x814E	/* 清除坐标寄存器 */

#define GT911_CONFIG_REG	0x8047	/* 配置参数寄存器 */

#define GT911_COMMAND_REG 0x8040 /* 实时命令 */

#define GT911_PRODUCT_ID_REG 0x8140 /*productid*/

#define GT911_VENDOR_ID_REG 0x814A /* 当前模组选项信息 */

#define GT911_CONFIG_VERSION_REG 0x8047 /* 配置文件版本号 */

#define GT911_CONFIG_CHECKSUM_REG 0x80FF /* 配置文件校验码 */

#define GT911_FIRMWARE_VERSION_REG 0x8144 /* 固件版本号 */




#define  TP_PRES_DOWN 1
#define TP_CATH_PRES 2


extern Int8U GtpCheckTime;
typedef struct{
Int8U sta;
Int8U touchtype;
Int16U x[16];
Int16U y[16];
}Gtp_T;



typedef struct

{

Int8U Enable;

Int8U i2c_addr;

Int8U TouchpointFlag;

Int8U Touchkey1trackid;

Int16U X1;

Int16U Y1;

Int16U S1;

Int8U Touchkey2trackid;

Int16U X2;

Int16U Y2;

Int16U S2;

Int8U Touchkey3trackid;

Int16U X3;

Int16U Y3;

Int16U S3;

Int8U Touchkey4trackid;

Int16U X4;

Int16U Y4;

Int16U S4;

Int8U Touchkey5trackid;

Int16U X5;

Int16U Y5;

Int16U S5;

}GT911_T;



extern Gtp_T tp_dev;


Int8U GT911_ReadStatue(void);
Int16U GT911_ReadFirmwareVersion(void);
void GT911_Soft_Reset(void);
void GT911_InitHard(void);
void GT911_Reset_Sequence(void);


Int8U GT911_Send_Cfg(Int8U mode);
Int8U GT911_WR_Reg(Int16U reg,Int8U *buf,Int8U len);
void GT911_RD_Reg(Int16U reg,Int8U *buf,Int8U len); 
Int8U GT911_Init(void);


extern Int8U GT911_Scan(void);
Int8U GT911_Scan_OLD(Int8U mode);


//void GT911_Scan(void);


void Gtp_IO_Init(void);

#endif

