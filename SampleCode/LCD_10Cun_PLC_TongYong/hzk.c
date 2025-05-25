#include "main.h"
#include "hzk.h"
#include "spi.h"

Int8U HanZi[32];
Int8U AT45db161[8];
void HZK_Read( char *hzp,unsigned char distype)  //读取汉字库中汉字点阵 distype 0:正常 1:反相
{
unsigned char i,hzk_temp[2];
int LowPointer,HighPointer;
int Pointer;
//unsigned int templ,temph;
hzk_temp[0]=hzp[0];
hzk_temp[1]=hzp[1];

if(hzk_temp[0]>0xa0&&hzk_temp[1]>0xa0)
	{
    hzk_temp[0]=hzk_temp[0]-0xa1;      //计算汉字点阵在字库中的起始地址
    hzk_temp[1]=hzk_temp[1]-0xa1;
    LowPointer=(int)hzk_temp[0]*94+(int)hzk_temp[1];
    Pointer=LowPointer*32;
    HighPointer=Pointer>>8;
//SpiChipSelect(1);  //选通芯片
    //    FIO0CLR = SPI0_SEL;
AT45DB_ArrayRead_Start(Pointer);
/*
SpiTranserByte(0xE8);
//	SpiTranserByte(AT45db041_ContArray_Read_Commd);
    //    AT45db161[0] = AT45db041_ContArray_Read_Commd;
	SpiTranserByte((unsigned char)(HighPointer>>8));
    //    AT45db161[1] = (unsigned char)(HighPointer>>8);
	SpiTranserByte((unsigned char)HighPointer);
    //    AT45db161[2] = (unsigned char)HighPointer;
	SpiTranserByte((unsigned char)Pointer);
    //    AT45db161[3] = (unsigned char)Pointer;
	SpiTranserByte(0);
    //    AT45db161[4] = 0x00;
	SpiTranserByte(0);
    //    AT45db161[5] = 0x00;
	SpiTranserByte(0);
    //    AT45db161[6] = 0x00;
	SpiTranserByte(0);
    //    AT45db161[7] = 0x00;
      //  SPISend(AT45db161,8);*/
    for(i=0;i<32;i++)               //读取点阵信息
         {
		 HanZi[i]=AT45DB_Read();
          }
       // SPIReceive( HanZi, 32);
	AT45DB_End();//(void)  //片释放
    //FIO0SET = SPI0_SEL;
   if(distype) for(i=0;i<32;i++) HanZi[i]=~HanZi[i];  //反相显示
	}
else
    {
        Pointer=(unsigned long)hzk_temp[0]*16+ASCIIADD;
    HighPointer=Pointer>>8;
	SpiChipSelect(1);  //选通芯片
    //FIO0CLR = SPI0_SEL;
	SpiTranserByte(AT45db041_ContArray_Read_Commd);
    //    AT45db161[0] = AT45db041_ContArray_Read_Commd;
	SpiTranserByte((unsigned char)(HighPointer>>8));
    //    AT45db161[1] = (unsigned char)(HighPointer>>8);
	SpiTranserByte((unsigned char)HighPointer);
    //    AT45db161[2] = (unsigned char)HighPointer;
	SpiTranserByte((unsigned char)Pointer);
    //    AT45db161[3] = (unsigned char)Pointer;
	SpiTranserByte(0);
    //    AT45db161[4] = 0x00;
	SpiTranserByte(0);
    //    AT45db161[5] = 0x00;
	SpiTranserByte(0);
    //    AT45db161[6] = 0x00;
	SpiTranserByte(0);
    //    AT45db161[7] = 0x00;
      //  SPISend(AT45db161,8);
    for(i=0;i<32;i++)               //读取点阵信息
         {
		 HanZi[i]=SpiTranserByte(0);
          }
       // SPIReceive( HanZi, 16);
		SpiChipSelect(0);  //释放芯片
//        FIO0SET = SPI0_SEL;
        if(distype) for(i=0;i<16;i++) HanZi[i]=~HanZi[i];  //反相显示
	}
}