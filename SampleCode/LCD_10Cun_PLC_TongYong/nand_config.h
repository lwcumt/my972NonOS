#ifndef _NAND_CONFIG_H
#define _NAND_CONFIG_H

#include "main.h"

#define NAND_EN     0x08
#define READYBUSY   (0x01 << 18)
#define ENDADDR     (0x80000000)

extern Int8U Nand_Config(void);

#endif 
