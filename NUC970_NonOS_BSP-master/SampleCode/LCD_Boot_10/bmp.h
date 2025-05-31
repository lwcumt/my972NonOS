
#ifndef _BMP_H
#define _BMP_H

#include "main.h"


void Get_Bmp_Info(Int32U Bmp_add);
void Bmp_Decode(Int32U Bmp_add,Int16U StartX,Int16U StartY,pInt16U PicBase_RAM);

#endif