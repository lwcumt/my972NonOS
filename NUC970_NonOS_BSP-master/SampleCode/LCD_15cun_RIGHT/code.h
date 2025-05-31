

#ifndef _CODE_H
#define _CODE_H


#include "main.h"

#define CODE_ADD	400

#define SERIAL_ID0 0
#define SERIAL_ID1 1
#define SERIAL_ID2  2
#define SERIAL_ID3  3

typedef struct
{
	Int32U nand_blocks;
	Int32U core_ID[4];
} BOARD_CODE;



Int8U DecodeAppExec(void);
void CodeAppExec(void);

#endif