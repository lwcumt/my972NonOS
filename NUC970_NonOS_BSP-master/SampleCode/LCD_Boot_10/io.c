
#include"io.h"

//#include "spi_config.h"
#include "drv_glcd.h"


void IO_Init(void)
{
	
RLOUT1_OFF;
RLOUT2_OFF;
RLOUT3_OFF;
RLOUT4_OFF;
RLOUT5_OFF;
RLOUT4_1_OFF;


RLOUT1_DirInit;
RLOUT2_DirInit;
RLOUT3_DirInit;
RLOUT4_DirInit;
RLOUT4_1_DirInit;
RLOUT5_DirInit;
/*
RLOUT1_ON;
RLOUT2_ON;
RLOUT3_ON;
RLOUT4_ON;
RLOUT5_ON;
RLOUT4_1_ON;
*/


OOUT1_OFF;
OOUT2_OFF;
OOUT3_OFF;
OOUT4_OFF;

OOUT1_DirInit;
OOUT2_DirInit;
OOUT3_DirInit;
OOUT4_DirInit;
/*
OOUT1_ON;
OOUT2_ON;
OOUT3_ON;
OOUT4_ON;
*/
	  LED2_DirInit;
  LED2_OFF;
  
BellOUT_DirInit;
	
	M_ZIN_DirInit;
  OIN1_DirInit;
  OIN2_DirInit;
  OIN3_DirInit;
  OIN4_DirInit;
  OIN5_DirInit;
  OIN6_DirInit;
  OIN7_DirInit;// ‰»Î
  OIN8_DirInit;
  OIN9_DirInit;
  OIN10_DirInit;
  OIN11_DirInit;
  OIN12_DirInit;
  OIN13_DirInit;
  OIN14_DirInit;
	
	
}

void IO_Test(void)
{

}


void CheckOp_IN(void)
{
if(M_ZIN_PIN)
	RLOUT1_OFF;
else
	RLOUT1_ON;

if(OIN1_PIN)
	RLOUT2_OFF;
else
	RLOUT2_ON;
	

if(OIN2_PIN)
	RLOUT3_OFF;
else
	RLOUT3_ON;


if(OIN3_PIN)
	RLOUT4_OFF;
else
	RLOUT4_ON;


if(OIN4_PIN)
	RLOUT4_1_OFF;
else
	RLOUT4_1_ON;


if(OIN5_PIN)
	RLOUT5_OFF;
else
	RLOUT5_ON;

if(OIN6_PIN)
	OOUT1_OFF;
else
	OOUT1_ON;


if(OIN7_PIN)
	OOUT2_OFF;
else
	OOUT2_ON;


if(OIN8_PIN)
	OOUT3_OFF;
else
	OOUT3_ON;

if(OIN9_PIN)
	OOUT4_OFF;
else
	OOUT4_ON;

if(OIN10_PIN)
	OOUT1_OFF;
else
	OOUT1_ON;


if(OIN11_PIN)
	OOUT2_OFF;
else
	OOUT2_ON;


if(OIN12_PIN)
	OOUT3_OFF;
else
	OOUT3_ON;

if(OIN13_PIN)
	OOUT4_OFF;
else
	OOUT4_ON;

}



void I2C_Init(void)
{
////int rtval;
////    /* Configure multi function pins to I2C0 &   I2C1 */
////    outpw(REG_SYS_GPG_MFPL, (inpw(REG_SYS_GPG_MFPL) & ~0xff00) | 0x8800);



////    i2cInit(1);

////    rtval = i2cOpen((PVOID)I2CNUM_1);
////    if(rtval < 0) {

////		rtval=100;
////      //  sysprintf("Open I2C0 error!\n");
////      //  goto exit_test;
////    }
////    i2cIoctl(I2CNUM_1, I2C_IOC_SET_DEV_ADDRESS, PCF8563_DEV_ADD, 0);  /* On 910 EV board, set 0x50 for I2C0 */
////    i2cIoctl(I2CNUM_1, I2C_IOC_SET_SPEED, 400, 0);
}






void I2C_Test(void)
{
	
////Sec=0;
////Min=0x35;
////Hour=0x0;
////Dom=0x4;
////Month=0x7;
////Year=0x17;
////write_time();
}



void Sys_DevInit(void)
{
////IO_Init();
////Spi_Init();
////I2C_Init();
////Uart3_Init();
////GLCD_Init();

}