#ifndef _SD_CONFIG_H
#define _SD_CONFIG_H

#include "main.h"
#include "ff.h"


extern FIL file1;
extern FIL file2;        /* File objects */
extern void SD_main(void);

#define SD_PWR BIT7 
#define SD_PWR_DIR()  (GPIO_OpenBit(GPIOD, SD_PWR, DIR_OUTPUT, NO_PULL_UP))
#define SD_PWR_ON()   GPIO_ClrBit(GPIOD, SD_PWR)
#define SD_PWR_OFF()   GPIO_SetBit(GPIOD, SD_PWR)

#endif 
