#include"m25pe16.h"

Int8U Chip_id[20];

//--------------------¶Á²Ù×÷---------------------
void Read_DevID(void)//¶Áid
{
Int8U i;
FlashChip_En;
SpiTranserByte(READ_CHIP_ID_COMM);
Chip_id[0]=SpiTranserByte(0);
Chip_id[1]=SpiTranserByte(0);
Chip_id[2]=SpiTranserByte(0);

for(i=3;i<20;i++)
Chip_id[i]=SpiTranserByte(0);

FlashChip_Dis;
}

Int8U Read_Status(void)//---¶Á×´Ì¬
{
Int8U reg;
FlashChip_En;
SpiTranserByte(READ_STATUS_COMM);
reg=SpiTranserByte(0);
FlashChip_Dis;
return reg;
}

Int8U Wait_Busy(void)//Ã¦ÅÐ¶Ï  1:Ã¦
{
Int8U st;Int16U i=0;

while(i<0x1fff)
  {
   st=Read_Status();
   if((st&0x01)!=0)//Ã¦
     {
     i++;
     }
   else 
     break;
  }
if(i>=0x1fff) 
   return 1;
else
   return 0;
}


void Read_Datas_Start(Int32U  add)//¶ÁÆô¶¯   £¨add:×Ö½ÚµØÖ·£©
{
//Spi0_start();  
Wait_Busy();////Ã¦ÅÐ¶Ï

FlashChip_En;

SpiTranserByte(READ_DATA_COMM);//¶ÁÊ¹ÄÜ
SpiTranserByte((add>>16)&0xff);//ÆðÊ¼µØÖ·
SpiTranserByte((add>>8)&0xff);
SpiTranserByte(add&0xff);

}

void FastRead_Datas_Start(Int32U  add)//¿ì¶ÁÆô¶¯   £¨add:×Ö½ÚµØÖ·£©
{
//Spi0_start();   
Wait_Busy();////Ã¦ÅÐ¶Ï

FlashChip_En;

SpiTranserByte(FAST_READ_DATA_COMM);//¶ÁÊ¹ÄÜ
SpiTranserByte((add>>16)&0xff);//ÆðÊ¼µØÖ·
SpiTranserByte((add>>8)&0xff);
SpiTranserByte(add&0xff);
SpiTranserByte(0);
}

Int8U ReadFlash_Datas(void)//¶ÁÊý¾Ý
{
return(SpiTranserByte(0));
}

//----------------------²Á³ý²Ù×÷-----------
void Page_Erase(Int32U   page)//*****Ò³²Á³ý
{
Wait_Busy();
Write_En();//Ð´Ê¹ÄÜ

FlashChip_En;
SpiTranserByte(PAGE_ERASE_COMM);//²Á³ý
SpiTranserByte((page>>8)&0xff);//
SpiTranserByte(page&0xff);
SpiTranserByte(0);
FlashChip_Dis;
}

void Sector_Erase(Int32U   sector)//*****ÉÈÇø²Á³ý
{
Wait_Busy();
Write_En();//Ð´Ê¹ÄÜ

FlashChip_En;
SpiTranserByte(SECTOR_ERASE_COMM);//²Á³ý
sector<<=4;
SpiTranserByte((sector>>8)&0xff);//
SpiTranserByte(sector&0xff);
SpiTranserByte(0);
FlashChip_Dis;
}

void Block_Erase(Int32U   block)//*****¿é²Á³ý
{
Wait_Busy();
Write_En();//Ð´Ê¹ÄÜ

FlashChip_En;
SpiTranserByte(BLOCK_ERASE_COMM);//²Á³ý
SpiTranserByte(block&0xff);//
SpiTranserByte(0);
SpiTranserByte(0);
FlashChip_Dis;
}

void Chip_Erase(void)//*****ÕûÆ¬²Á³ý
{
Wait_Busy();
Write_En();//Ð´Ê¹ÄÜ

FlashChip_En;
SpiTranserByte(CHIP_ERASE_COMM);//²Á³ý
FlashChip_Dis;
}

//--------------------Ð´²Ù×÷----------------------

void Write_En(void)//Ð´Ê¹ÄÜ
{
FlashChip_En;
SpiTranserByte(WRITE_EN_COMM);
FlashChip_Dis;
}

void Write_Dis(void)//Ð´½ûÖ¹
{
FlashChip_En;
SpiTranserByte(WRITE_DIS_COMM);
FlashChip_Dis;
}

void Page_Program(pInt8U   wbuf,   Int32U   page,   Int16U   length)//*****Ò³±à³Ì
{
Int16U n;
Page_Erase(page);//ÏÈ²Á³ý
Wait_Busy();
Wait_Busy();
Write_En();//Ð´Ê¹ÄÜ

FlashChip_En;
SpiTranserByte(PAGE_PROGRAM_COMM);//±à³ÌÃüÁî
SpiTranserByte((page>>8)&0xff);//
SpiTranserByte(page&0xff);
SpiTranserByte(0);

for(n=0;n<length;n++)
  {
   SpiTranserByte(*wbuf);
   wbuf++;
  }

FlashChip_Dis;
//Write_Dis();//Ð´½ûÖ¹
}


void Page_Write(pInt8U   wbuf,   Int32U   page,   Int16U   length)//*****Ò³Ð´
{
Int16U n;
Wait_Busy();
Write_En();//Ð´Ê¹ÄÜ

FlashChip_En;
SpiTranserByte(PAGE_WRITE_COMM);//Ð´ÃüÁî
SpiTranserByte((page>>8)&0xff);//
SpiTranserByte(page&0xff);
SpiTranserByte(0);

for(n=0;n<length;n++)
  {
   SpiTranserByte(*wbuf);
   wbuf++;
  }

FlashChip_Dis;
//Write_Dis();//Ð´½ûÖ¹
}

void Bytes_Write(pInt8U   wbuf,   Int32U  add,   Int16U   length)//*****×Ö½ÚÐ´
{
Int16U n;
Wait_Busy();
Write_En();//Ð´Ê¹ÄÜ
FlashChip_En;
SpiTranserByte(PAGE_WRITE_COMM);//Ð´ÃüÁî
SpiTranserByte((add>>16)&0xff);//
SpiTranserByte((add>>8)&0xff);
SpiTranserByte(add&0xff);

for(n=0;n<length;n++)
  {
   SpiTranserByte(*wbuf);
   wbuf++;
  }

FlashChip_Dis;
//Write_Dis();//Ð´½ûÖ¹
}


//***************************Ð´ÈÎÒâ³¤¶ÈÊý¾Ý*****
void Write_25pe_data(pInt8U   wbuf,   Int32U  add,   Int32U   size)//*****×Ö½ÚÐ´
{
Int32U offset;
Int32U reamin;
//Spi0_start(); 
offset=add&0xff;
reamin=PAGE_SIZE-offset;

if(size<=reamin)//²»¹»Ò»Ò³
  {
  Bytes_Write(wbuf, add, size);
  }
else
  {         //³¬³öÒ»Ò³
  Bytes_Write(wbuf, add, reamin);
  size-=reamin;
  wbuf+=reamin;
  add+=reamin;
  while(size>0)
     {
	 if(size>=PAGE_SIZE)
	   {
	   Bytes_Write(wbuf, add, PAGE_SIZE);
	   size-=PAGE_SIZE;
	   wbuf+=PAGE_SIZE;
	   add+=PAGE_SIZE;
	   }
	 else
	   {
	   Bytes_Write(wbuf, add, size);
	   size=0;
	   }
	 }
  }  
}
