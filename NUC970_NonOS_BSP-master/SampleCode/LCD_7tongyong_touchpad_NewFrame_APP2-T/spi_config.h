#ifndef _SPI_CONFIG_H
#define _SPI_CONFIG_H
#include "main.h"
#include "m25pe16.h"

//**********spi0**********
#define SPI0_SEL		BIT12

#define SPI0_SEL_OUT   (GPIO_OpenBit(GPIOB, SPI0_SEL, DIR_OUTPUT, NO_PULL_UP))
#define SPI0_SEL_IN    (GPIO_OpenBit(GPIOB, SPI0_SEL, DIR_INPUT, NO_PULL_UP))
#define SPI0_SEL_EN     GPIO_ClrBit(GPIOB, SPI0_SEL)//片选使能
#define SPI0_SEL_DIS    GPIO_SetBit(GPIOB, SPI0_SEL)
//#define SPI0_SEL_PIN   (FIO0PIN&SPI0_SEL)

//**********spi0**********

/*
#define SPI0_SEL		(1 << 16)		// P0.16   CS   /

#define SPI0_SEL_OUT   FIO0DIR |=SPI0_SEL
#define SPI0_SEL_IN    FIO0DIR &=~(SPI0_SEL)
#define SPI0_SEL_EN    FIO0CLR |=SPI0_SEL//片选使能
#define SPI0_SEL_DIS   FIO0SET |=SPI0_SEL
#define SPI0_SEL_PIN   (FIO0PIN&SPI0_SEL)

*/


extern void Spi_Init(void);

extern char SpiTranserByte(char ch);

extern uint16_t SpiFlash_ReadMidDid(void);

#endif
