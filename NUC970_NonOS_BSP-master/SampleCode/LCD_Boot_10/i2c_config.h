#ifndef _I2C_CONFIG_H
#define _I2C_CONFIG_H

#include "main.h"

extern void I2C0_Init(void);
extern void I2C0_WriteData(unsigned char devadd,unsigned char iadd,unsigned char d);
extern unsigned char  I2C0_ReadData(unsigned char devadd,unsigned char iadd);

#endif
