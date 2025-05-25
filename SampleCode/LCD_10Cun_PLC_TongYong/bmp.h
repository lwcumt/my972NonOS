
#ifndef _BMP_H
#define _BMP_H

#include "main.h"
__packed struct BMP_HEADER
{
	Int16U  bmp_Type;								//2b  0~1byte
	Int32U file_Size;								//4b  2-5
	Int16U rsv1;//rsv 2bytes						//2b  6
	Int16U rsv2;//rsv 2bytes						//2b  8
	Int32U lBmp_Data_Offset;						//4b 10-13    ++
};			//14b

__packed struct BMP_INFO
{
	struct BMP_HEADER head;	//14b
	Int32U lInfo_Size;		//4b  14
	Int32U lBmp_Width;		//4b  18    ++
	Int32S lBmp_Height;		//4b  22    ++
	Int16U Planes;     		//2bytes	26	颜色平面数 =1					
	Int16U  iBit_Count;		// 28    ++
	Int32U PressType;//4bytes	30						
	Int32U lImage_Size;		//4b 34
	Int32U lXPels_Per_Meter;//4b 38
	Int32U lYPels_Per_Meter;//4b 42
	Int32U ColorUsed;		//4b 46
	Int32U ColorImportant;		//4b 50
};  //54



void Get_Bmp_Info(Int32U Bmp_add);
void Bmp_Decode(Int32U Bmp_add,Int16U StartX,Int16U StartY,pInt16U PicBase_RAM);

#endif