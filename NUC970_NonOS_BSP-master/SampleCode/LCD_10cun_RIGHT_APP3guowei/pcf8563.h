#ifndef PCF8563_H
#define PCF8563_H

#include "main.h"


#define PCF8563_DEV_ADD 0x51   //–æ∆¨µÿ÷∑

extern unsigned char Sec,Min,Hour,Dow,Dom,Month;
extern int Doy,Year;



extern void write_time(void);
extern void read_time(void);

extern void I2C_WriteData(unsigned char devadd,unsigned char iadd,unsigned char d);
extern unsigned char  I2C_ReadData(unsigned char devadd,unsigned char iadd);
#endif
