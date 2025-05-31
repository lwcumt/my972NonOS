
#ifndef _BMP_H
#define _BMP_H

#include "main.h"
struct BMP_HEADER
{
	unsigned int  iFile_Type;		// 0~1byte
	unsigned long lFile_Size;		// 2
	//rsv 2bytes						// 6
	//rsv 2bytes						// 8
	unsigned long lBmp_Data_Offset;	//offset=10
};

struct BMP_INFO
{
	unsigned long lInfo_Size;		// 14
	unsigned long lBmp_Width;		// 18
	unsigned long lBmp_Height;		// 22
	//2bytes							//26
	unsigned int  iBit_Count;		// 28
	//2bytes							// 30
	unsigned long lImage_Size;		// 32
	unsigned long lXPels_Per_Meter;	// 36
	unsigned long lYPels_Per_Meter;	// 40
	//4bytes
};

void Get_Bmp_Info(Int32U Bmp_add);
void Bmp_Decode(Int32U Bmp_add,Int16U StartX,Int16U StartY,pInt16U PicBase_RAM);

#endif
