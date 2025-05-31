
#include <stdio.h>
#include "board.h"
#include "sdram_32M_16bit_drv.h"

#define NORFLASH_BASE_ADDR 0x81000000

#if   SYS_FREQ == (72MHZ)
#define SDRAM_PERIOD          13.8  // 72MHz
#elif   SYS_FREQ == (57MHZ)
#define SDRAM_PERIOD          17.4  // 57.6MHz
#elif SYS_FREQ == (48MHZ)
#define SDRAM_PERIOD          20.8  // 48MHz
#elif SYS_FREQ == (36MHZ)
#define SDRAM_PERIOD          27.8  // 36MHz
#elif SYS_FREQ == (24MHZ)
#define SDRAM_PERIOD          41.7  // 24MHz
#else
#error Frequency not defined
#endif

#define P2C(Period)           (((Period<SDRAM_PERIOD)?0:(Int32U)((Flo32)Period/SDRAM_PERIOD))+1)

#define SDRAM_REFRESH         7813
#define SDRAM_TRP             20
#define SDRAM_TRAS            45
#define SDRAM_TAPR            1
#define SDRAM_TDAL            3
#define SDRAM_TWR             3
#define SDRAM_TRC             65
#define SDRAM_TRFC            66
#define SDRAM_TXSR            67
#define SDRAM_TRRD            15
#define SDRAM_TMRD            3

/*************************************************************************
 * Function Name: SDRAM_Init
 * Parameters: none
 *
 * Return: none
 *
 * Description: SDRAM controller and memory init
 *
 *************************************************************************/
void SDRAM_Init (void)
{
  // Assign pins to SDRAM controller
  PCONP_bit.PCEMC = 1;
  EMCCONTROL      = 1;         // enable EMC 

  PINSEL5 &= BIN32(11110000,11111100,11111100,11000000);
  PINSEL5 |= BIN32(00000101,00000001,00000001,00010101);
  PINMODE5&= BIN32(11110000,11111100,11111100,11000000);
  PINMODE5|= BIN32(00001010,00000010,00000010,00101010);
  PINSEL6  = BIN32(01010101,01010101,01010101,01010101);
  PINMODE6 = BIN32(10101010,10101010,10101010,10101010);
 
  PINSEL8 &= BIN32(00000000,00000000,00000000,00000000);
  PINSEL8 |= BIN32(01010101,01010101,01010101,01010101);
  PINMODE8&= BIN32(00000000,00000000,00000000,00000000);
  PINMODE8|= BIN32(10101010,10101010,10101010,10101010);
  PINSEL9 &= BIN32(00111111,11110000,11111100,00000000);
  PINSEL9 |= BIN32(01000000,00000101,00000001,01010101);
  PINMODE9&= BIN32(00111111,11110000,11111100,00000000);
  PINMODE9|= BIN32(10000000,00001010,00000010,10101010);
  // Init SDRAM controller
  // Enable EMC clock

  EMCDINAMICRDCFG = 1;
  EMCDYNAMICRASCAS0_bit.CAS = 3;
  EMCDYNAMICRASCAS0_bit.RAS = 3;
  EMCDYNAMICRP = P2C(SDRAM_TRP);
  EMCDYNAMICRAS = P2C(SDRAM_TRAS);
  EMCDYNAMICSREX = P2C(SDRAM_TXSR);
  EMCDYNAMICAPR = SDRAM_TAPR;
  EMCDYNAMICDAL = SDRAM_TDAL+P2C(SDRAM_TRP);
  EMCDYNAMICWR = SDRAM_TWR;
  EMCDYNAMICRC = P2C(SDRAM_TRC);
  EMCDYNAMICRFC = P2C(SDRAM_TRFC);
  EMCDYNAMICXSR = P2C(SDRAM_TXSR);
  EMCDYNAMICRRD = P2C(SDRAM_TRRD);
  EMCDYNAMICMRD = SDRAM_TMRD;
  EMCDYNAMICCFG0 = 0x0000280;        //4 banks, row length = 12, column length = 8
  // JEDEC General SDRAM Initialization Sequence
  // DELAY to allow power and clocks to stabilize ~100 us
  // NOP
  EMCDINAMICCTRL = 0x0183;
  for(volatile Int32U i = 200*30; i;i--);
  // PALL
  EMCDINAMICCTRL_bit.I = 2;
  EMCDINAMICRFR = 1;
  for(volatile Int32U i= 128; i; --i); // > 128 clk
  EMCDINAMICRFR = P2C(SDRAM_REFRESH) >> 4;
  // COMM
  EMCDINAMICCTRL_bit.I = 1;
  // Burst 8, Sequential, CAS-2
  volatile unsigned long Dummy = *(volatile unsigned short *)
                                  (0xa0000000 + (0x33UL << (11)));//(Int32U)SDRAM0_BASE_ADDR
  // NORM
  EMCDINAMICCTRL = 0x0000;
  EMCDYNAMICCFG0_bit.B = 1;
  for(volatile Int32U i = 10000; i;i--);
  
    //FLASH ROM set
  EMCSTATICCNFG1     = 0x00000081;
  EMCSTATICWAITWEN1  = 0x00000002;
  EMCSTATICWAITOEN1  = 0x00000002;
  EMCSTATICWAITRD1   = 0x0000001f;
  EMCSTATICWAITPG1   = 0x0000001f;
  EMCSTATICWAITWR1   = 0x0000001f;
  EMCSTATICWAITTURN1 = 0x0000000f;
  for(volatile Int32U i = 10000; i;i--);
}


/****************************************************************************
* 名    称：ChipTmpErase()
* 功    能：芯片全片擦除。
* 入口参数：无
* 出口参数：返回TRUE表示操作成功，返回FALSE表示操作失败
****************************************************************************/
Int8U  ChipErase(void) 
{  
    pInt16U ipTmp;
    Int16U  itemp1,itemp2;
    ipTmp = (pInt16U)(NORFLASH_BASE_ADDR+0x5555*2);
    *ipTmp = 0xaa;			// 第一个写周期，地址0x5555，数据0xAA
    ipTmp = (pInt16U)(NORFLASH_BASE_ADDR+0x2aaa*2);
    *ipTmp = 0x55;			// 第二个写周期，地址0x2aaa，数据0x55
    ipTmp = (pInt16U)(NORFLASH_BASE_ADDR+0x5555*2);
    *ipTmp = 0x80;			// 第三个写周期，地址0x5555，数据0x80
    ipTmp = (pInt16U)(NORFLASH_BASE_ADDR+0x5555*2);
    *ipTmp = 0xaa;			// 第四个写周期，地址0x5555，数据0xAA
    ipTmp = (pInt16U)(NORFLASH_BASE_ADDR+0x2aaa*2);
    *ipTmp = 0x55;			// 第五个写周期，地址0x2aaa，数据0x55
    ipTmp = (pInt16U)(NORFLASH_BASE_ADDR+0x5555*2);
	*ipTmp = 0x10;			// 第六个写周期，地址0x5555，数据0x10
        
    itemp1=1;
    itemp2=2;
    while((itemp1 != itemp2))				// 等待操作完成 (若编程操作没有完成，每次读操作DQ6会跳变)
	{
	itemp1=*ipTmp;
	itemp2=*ipTmp;
	}
    return(TRUE);
}



/****************************************************************************
* 名    称：WordProgram()
* 功    能：半字(16位)数据编程。
* 入口参数：Addr		编程地址(SST39VF1601内部地址)	
*           Data		编程数据
* 出口参数：返回TRUE表示操作成功，返回FALSE表示操作失败
****************************************************************************/
Int8U  WordProgram(Int32U iAddr, Int16U iData) 
{  
     pInt16U ipTmp;
    Int16U  itemp1,itemp2;
    ipTmp = (pInt16U)(NORFLASH_BASE_ADDR+0x5555*2);	// 转换地址0x5555
    *ipTmp = 0xaa;			// 第一个写周期，地址0x5555，数据0xAA
    ipTmp = (pInt16U)(NORFLASH_BASE_ADDR+0x2aaa*2);
    *ipTmp = 0x55;			// 第二个写周期，地址0x2aaa，数据0x55
    ipTmp = (pInt16U)(NORFLASH_BASE_ADDR+0x5555*2);
    *ipTmp = 0xa0;			// 第三个写周期，地址0x5555，数据0xA0
	
    ipTmp = (pInt16U) (NORFLASH_BASE_ADDR + iAddr*2);
    *ipTmp = iData;				// 第四个写周期，地址Addr，数据Data
 
 itemp1=1;
   itemp2=2;
    while(itemp1 != itemp2)// 等待操作完成 (若编程操作没有完成，每次读操作DQ6会跳变)
	{
	itemp1=*ipTmp;
	itemp2=*ipTmp;
	}	
    return(TRUE);
}




Int16U NorflashRead(Int32U ADDR)
{
    pInt8U ipTmp;
	Int16U  itemp;
		ipTmp=(pInt8U) (NORFLASH_BASE_ADDR + ADDR);
		itemp=*ipTmp;
		ipTmp=(pInt8U) (NORFLASH_BASE_ADDR + ADDR+1);
		itemp=itemp<<8;
		itemp+=*ipTmp;
		return(itemp);
}