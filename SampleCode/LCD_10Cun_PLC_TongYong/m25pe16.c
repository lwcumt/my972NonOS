#include"m25pe16.h"



Int8U Chip_id[20];


unsigned char df_page_bits;
unsigned int df_page_lenth;
unsigned char WBUFF[28];
unsigned char RBUFF[528];

unsigned char W25Q16_Mode=0;//??¨¨? M25PE16 ?¡ê¨º?

unsigned char W25Q16WRBuf[8192];//?¨¢D¡ä?o3???
 unsigned long spiflashID=0;
 
 int OldSector=-1;

//--------------------?¨¢2¨´¡Á¡Â---------------------
void Read_DevID(void)//?¨¢id
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


spiflashID=SpiFlash_Read_DevID();
	if((spiflashID==0x00EF4015)||(spiflashID==0x00EF7015))
	{//W25Q16 ?¨¢D¡ä?¡ê¨º?
		W25Q16_Mode=1;
		
	}
	else{
		spiflashID=Chip_id[0]<<16;
		spiflashID+=Chip_id[1]<<8;
			spiflashID+=Chip_id[2]<<8;
		W25Q16_Mode=0;
	}
		
	
}

Int8U Read_Status(void)//---?¨¢¡Á¡ä¨¬?
{
Int8U reg;
FlashChip_En;
SpiTranserByte(READ_STATUS_COMM);
reg=SpiTranserByte(0);
FlashChip_Dis;
return reg;
}

Int8U Wait_Busy(void)//?|?D??  1:?|
{
Int8U st;Int16U i=0;

while(i<0x1fff)
  {
   st=Read_Status();
   if((st&0x01)!=0)//?|
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


void Read_Datas_Start(Int32U  add)//?¨¢???¡¥   ¡ê¡§add:¡Á??¨²¦Ì??¡¤¡ê?
{
//Spi0_start();  
	
	if(W25Q16_Mode==1)
	{//W25Q16 ?¡ê¨º?
		SpiFlash_Read_Datas_Start(add);		
		return;
	}

	
Wait_Busy();////?|?D??

FlashChip_En;

SpiTranserByte(READ_DATA_COMM);//?¨¢¨º1?¨¹
SpiTranserByte((add>>16)&0xff);//?e¨º?¦Ì??¡¤
SpiTranserByte((add>>8)&0xff);
SpiTranserByte(add&0xff);

}

void FastRead_Datas_Start(Int32U  add)//?¨¬?¨¢???¡¥   ¡ê¡§add:¡Á??¨²¦Ì??¡¤¡ê?
{
//Spi0_start();   
		if(W25Q16_Mode==1)
	{//W25Q16 ?¡ê¨º?
		SpiFlash_FastRead_Datas_Start(add);		
		return;
	}
	

	
	
Wait_Busy();////?|?D??

FlashChip_En;

SpiTranserByte(FAST_READ_DATA_COMM);//?¨¢¨º1?¨¹
SpiTranserByte((add>>16)&0xff);//?e¨º?¦Ì??¡¤
SpiTranserByte((add>>8)&0xff);
SpiTranserByte(add&0xff);
SpiTranserByte(0);
}

Int8U ReadFlash_Datas(void)//?¨¢¨ºy?Y
{
return(SpiTranserByte(0));
}

//----------------------2¨¢3y2¨´¡Á¡Â-----------
void Page_Erase(Int32U   page)//*****¨°32¨¢3y
{
	
if(W25Q16_Mode==1)
	{//W25Q16 ?¡ê¨º?
		SpiFlash_Page_Erase(page);//		
		return;
	}
	
	
Wait_Busy();
Write_En();//D¡ä¨º1?¨¹

FlashChip_En;
SpiTranserByte(PAGE_ERASE_COMM);//2¨¢3y
SpiTranserByte((page>>8)&0xff);//
SpiTranserByte(page&0xff);
SpiTranserByte(0);
FlashChip_Dis;
}

void Sector_Erase(Int32U   sector)//*****¨¦¨¨??2¨¢3y
{
	
if(W25Q16_Mode==1)
	{//W25Q16 ?¡ê¨º?
		SpiFlash_Sector_Erase(sector);//		
		return;
	}
	
	
Wait_Busy();
Write_En();//D¡ä¨º1?¨¹

FlashChip_En;
SpiTranserByte(SECTOR_ERASE_COMM);//2¨¢3y
sector<<=4;
SpiTranserByte((sector>>8)&0xff);//
SpiTranserByte(sector&0xff);
SpiTranserByte(0);
FlashChip_Dis;
}

void Block_Erase(Int32U   block)//*****?¨¦2¨¢3y
{
	
	if(W25Q16_Mode==1)
	{//W25Q16 ?¡ê¨º?
		SpiFlash_Block_Erase(block);//		
		return;
	}
	
Wait_Busy();
Write_En();//D¡ä¨º1?¨¹

FlashChip_En;
SpiTranserByte(BLOCK_ERASE_COMM);//2¨¢3y
SpiTranserByte(block&0xff);//
SpiTranserByte(0);
SpiTranserByte(0);
FlashChip_Dis;
}

void Chip_Erase(void)//*****????2¨¢3y
{
		if(W25Q16_Mode==1)
	{//W25Q16 ?¡ê¨º?
		SpiFlash_Chip_Erase();//		
		return;
	}
	
	
	
Wait_Busy();
Write_En();//D¡ä¨º1?¨¹

FlashChip_En;
SpiTranserByte(CHIP_ERASE_COMM);//2¨¢3y
FlashChip_Dis;
}

//--------------------D¡ä2¨´¡Á¡Â----------------------

void Write_En(void)//D¡ä¨º1?¨¹
{
			if(W25Q16_Mode==1)
	{//W25Q16 ?¡ê¨º?
		SpiFlash_Write_En();//		
		return;
	}
	
	
FlashChip_En;
SpiTranserByte(WRITE_EN_COMM);
FlashChip_Dis;
}

void Write_Dis(void)//D¡ä???1
{
	
if(W25Q16_Mode==1)
	{//W25Q16 ?¡ê¨º?
		SpiFlash_Write_Dis();//		
		return;
	}
	
FlashChip_En;
SpiTranserByte(WRITE_DIS_COMM);
FlashChip_Dis;
}

void Page_Program(pInt8U   wbuf,   Int32U   page,   Int16U   length)//*****¨°3¡À¨¤3¨¬
{
Int16U n;
	
	if(W25Q16_Mode==1)
	{//W25Q16 ?¡ê¨º?
		SpiFlash_Page_Program(wbuf,page,length);//		
		return;
	}
	
		
	
	
Page_Erase(page);//?¨¨2¨¢3y
Wait_Busy();
Wait_Busy();
Write_En();//D¡ä¨º1?¨¹

FlashChip_En;
SpiTranserByte(PAGE_PROGRAM_COMM);//¡À¨¤3¨¬?¨¹¨¢?
SpiTranserByte((page>>8)&0xff);//
SpiTranserByte(page&0xff);
SpiTranserByte(0);

for(n=0;n<length;n++)
  {
   SpiTranserByte(*wbuf);
   wbuf++;
  }

FlashChip_Dis;
//Write_Dis();//D¡ä???1
}


void Page_Write(pInt8U   wbuf,   Int32U   page,   Int16U   length)//*****¨°3D¡ä
{
Int16U n;
	
		if(W25Q16_Mode==1)
	{//W25Q16 ?¡ê¨º?
		SpiFlash_Page_Program(wbuf,page,length);//		
		return;
	}
	
	
Wait_Busy();
Write_En();//D¡ä¨º1?¨¹

FlashChip_En;
SpiTranserByte(PAGE_WRITE_COMM);//D¡ä?¨¹¨¢?
SpiTranserByte((page>>8)&0xff);//
SpiTranserByte(page&0xff);
SpiTranserByte(0);

for(n=0;n<length;n++)
  {
   SpiTranserByte(*wbuf);
   wbuf++;
  }

FlashChip_Dis;
//Write_Dis();//D¡ä???1
}

void Bytes_Write(pInt8U   wbuf,   Int32U  add,   Int16U   length)//*****¡Á??¨²D¡ä
{
Int16U n;
	
	
if(W25Q16_Mode==1)
	{//W25Q16 ?¡ê¨º?
		SpiFlash_Bytes_Write(wbuf,add,length);//		
		return;
	}
	
	
Wait_Busy();
Write_En();//D¡ä¨º1?¨¹
FlashChip_En;
SpiTranserByte(PAGE_WRITE_COMM);//D¡ä?¨¹¨¢?
SpiTranserByte((add>>16)&0xff);//
SpiTranserByte((add>>8)&0xff);
SpiTranserByte(add&0xff);

for(n=0;n<length;n++)
  {
   SpiTranserByte(*wbuf);
   wbuf++;
  }

FlashChip_Dis;
//Write_Dis();//D¡ä???1
}


//***************************D¡ä¨¨?¨°a3¡è?¨¨¨ºy?Y*****
void Write_25pe_data(pInt8U   wbuf,   Int32U  add,   Int32U   size)//*****¡Á??¨²D¡ä
{
Int32U offset;
Int32U reamin;
//Spi0_start(); 
offset=add&0xff;
reamin=PAGE_SIZE-offset;
	
	
	if(W25Q16_Mode==1)
	{//W25Q16 ?¡ê¨º?
		Write_25pe_data_W25Q16(wbuf,add,size);//		
		return;
	}

if(size<=reamin)//2?1?¨°?¨°3
  {
  Bytes_Write(wbuf, add, size);
  }
else
  {         //3?3?¨°?¨°3
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


//***************************D¡ä¨¨?¨°a3¡è?¨¨¨ºy?Y*****
//??¨¨Y W25Q16  
void Write_25pe_data_W25Q16(pInt8U   wbuf,   Int32U  add,   Int32U   size)//*****¡Á??¨²D¡ä
{
		

unsigned int  length1,length2;
unsigned int  sector=0;
	
unsigned int  addpage,addpagetemp;
	
unsigned char needtwosector=0;
	 int wrbuf_startadd=0;
	int n=0;
	int reamin=0;
	
	unsigned char *	wfbuf;
	
	addpage=add/256;			//¨º¦Ì?¨º¦Ì?¨°3
	addpagetemp=add%256;
	
	if(addpage>=16)
	{
		sector=addpage/16;//????SECOTR	
	}
	else
	{
		sector=0;
	}
	
	
	
wrbuf_startadd=add-sector*4096;

reamin=4096-wrbuf_startadd;
	
if(reamin<size)
		{			
				SpiFlash_Read_Data(sector*SECTOR_SIZE,W25Q16WRBuf,4096);//?¨¢¨¨?8K¡À?¡¤Y
				for(n=wrbuf_startadd;n<4096;n++)
					{
						W25Q16WRBuf[n]=*wbuf++;	
					}
			//	W25Q16WRBuf[wrbuf_startadd++]=*wbuf++;	
				SpiFlash_Sector_Erase(sector);
					
				addpage=sector*16;
				wfbuf=W25Q16WRBuf;
				for(n=0;n<16;n++)//D¡ä¨¨?8K¨ºy?Y
					{	
					SpiFlash_Page_Program(wfbuf,   addpage++,   256);	
					wfbuf+=256;
					}
				
				size-=reamin;
					
				while(size>0)
				 {			 
					sector++;
					 
					SpiFlash_Read_Data(sector*SECTOR_SIZE,W25Q16WRBuf,4096);//?¨¢¨¨?8K¡À?¡¤Y
					if(size>=4096)
					 {
						for(n=0;n<4096;n++)
							{
							W25Q16WRBuf[n]=*wbuf++;	
							}
			
						SpiFlash_Sector_Erase(sector);
						
						addpage=sector*16;
						wfbuf=W25Q16WRBuf;
						for(n=0;n<16;n++)//D¡ä¨¨?8K¨ºy?Y
							{	
							SpiFlash_Page_Program(wfbuf,   addpage++,   256);	
							wfbuf+=256;
							}
						size-=4096;
						}
				else
						{	
						for(n=0;n<size;n++)
							{
							W25Q16WRBuf[n]=*wbuf++;	
							}
						SpiFlash_Sector_Erase(sector);			
						addpage=sector*16;
						wfbuf=W25Q16WRBuf;
						for(n=0;n<16;n++)//D¡ä¨¨?8K¨ºy?Y
							{	
							SpiFlash_Page_Program(wfbuf,   addpage++,   256);	
							wfbuf+=256;
							}
						size=0;							
						}
			 }

		////////////	SpiFlash_Read_Data(sector*SECTOR_SIZE,W25Q16WRBuf,8192);//?¨¢¨¨?8K¡À?¡¤Y
		////////////	for(n=0;n<size;n++)
		////////////	{
		////////////			
		////////////	}
		////////////	
		////////////	SpiFlash_Sector_Erase(sector);
		////////////	SpiFlash_Sector_Erase(sector+1);//¨¦?3y2??¨¦¨¨??	
		////////////	
		////////////		addpage=sector*16;
		////////////	wfbuf=W25Q16WRBuf;
		////////////		for(n=0;n<32;n++)//D¡ä¨¨?8K¨ºy?Y
		////////////		{	
		////////////		 SpiFlash_Page_Program(wfbuf,   addpage++,   256);	
		////////////			wfbuf+=256;
		////////////			
		////////////		}
		}
else
		{		
		SpiFlash_Read_Data(sector*SECTOR_SIZE,W25Q16WRBuf,4096);//?¨¢¨¨?4K¡À?¡¤Y
		for(n=0;n<size;n++)
			{
				W25Q16WRBuf[wrbuf_startadd++]=*wbuf++;		
			}	
				SpiFlash_Sector_Erase(sector);
			
				wfbuf=W25Q16WRBuf;
			addpage=sector*16;
				for(n=0;n<16;n++)
				{	
				 SpiFlash_Page_Program(wfbuf,   addpage++,   256);	
				wfbuf+=256;
				}
		}
}




//??¨¨Y45DB D¡ä¡¤¡§

//======================================
void Write45db_2Pages(pInt8U   wbuf,   Int32U  page)
{
Int32U add,addtemp,pp;
Int16U length1,length2;

	
	if(W25Q16_Mode==1)
	{//W25Q16 ?¡ê¨º?
		Write45db_2Pages_W25Q16(wbuf,page);//		
		return;
	}
	
	
add=page*528;//????¦Ì??¡¤
addtemp=add%256;
if(addtemp!=0)//¨®D¨¢?¨ª¡¤
   {
   length1=256-addtemp;
   Bytes_Write(wbuf,    add,    length1);//*****¡Á??¨²D¡ä
   add+=length1;
   wbuf+=length1;
   Bytes_Write(wbuf,    add,    256);//*****¡Á??¨²D¡ä
   add+=256;
   wbuf+=256;
   length2=528-256-length1;
   if(length2<=256)//?¡ä3?1y1¨°3
     Bytes_Write(wbuf,    add,    length2);//*****¡Á??¨²D¡ä
   else
     {
	 Bytes_Write(wbuf,    add,    256);//*****¡Á??¨²D¡ä
	 add+=256;
     wbuf+=256;
	 length2-=256;
	 Bytes_Write(wbuf,    add,    length2);//*****¡Á??¨²D¡ä
	 }
   
   }
else//??¨°3
   {
   pp=add>>8;//¦Ì?¨°3¦Ì??¡¤
   Page_Write(wbuf,   pp,   256);//*****¨°31D¡ä
   wbuf+=256;
   pp++;
   Page_Write(wbuf,   pp,   256);//*****¨°32D¡ä
   add+=512;
   wbuf+=256;
   Bytes_Write(wbuf,    add,    528-512);//*****¨°33¡Á??¨²D¡ä
   }
}

//======================================

//??¨¨Y W25Q16  

void Write45db_2Pages_W25Q16(pInt8U   wbuf,   Int32U  page)
{
			
unsigned int add,addtemp,pp;
unsigned int  length1,length2;
unsigned int  sector=0;
	
unsigned int  addpage,addpagetemp;
	
unsigned char needtwosector=0;
	unsigned int wrbuf_startadd=0;
	int n=0;
	unsigned char * wfbuf;
	
add=page*528;//????¦Ì??¡¤
addtemp=add%256;
	
	addpage=add/256;			//¨º¦Ì?¨º¦Ì?¨°3
	addpagetemp=add%256;
	
	if(addpage>=16)
	{
		sector=addpage/16;//????SECOTR	
	}
	else
	{
		sector=0;
	}
	
wrbuf_startadd=add-sector*4096;
	
if((4096-wrbuf_startadd)<528)
		{
			SpiFlash_Read_Data(sector*SECTOR_SIZE,W25Q16WRBuf,8192);//?¨¢¨¨?8K¡À?¡¤Y
			for(n=0;n<528;n++)
			{
				W25Q16WRBuf[wrbuf_startadd++]=*wbuf++;		
			}
			
			SpiFlash_Sector_Erase(sector);
			SpiFlash_Sector_Erase(sector+1);//¨¦?3y2??¨¦¨¨??	
			
			addpage=sector*16;
			wfbuf=W25Q16WRBuf;
			for(n=0;n<32;n++)//D¡ä¨¨?8K¨ºy?Y
				{	
				 SpiFlash_Page_Program(wfbuf,   addpage++,   256);	
					wfbuf+=256;			
				}
		}
else
		{		
		SpiFlash_Read_Data(sector*SECTOR_SIZE,W25Q16WRBuf,4096);//?¨¢¨¨?4K¡À?¡¤Y
		for(n=0;n<528;n++)
			{
				W25Q16WRBuf[wrbuf_startadd++]=*wbuf++;		
			}	
				SpiFlash_Sector_Erase(sector);
			
			addpage=sector*16;
			wfbuf=W25Q16WRBuf;
				for(n=0;n<16;n++)//D¡ä¨¨?4K ¨ºy?Y
				{	
				 SpiFlash_Page_Program(wfbuf,   addpage++,   256);	
					wfbuf+=256;
				}
		}
}


//***************************************************
//***************************************************
// W 25Q 16 ?y?¡¥

unsigned char Spi_WriteReadByte(unsigned char Txdata)
{

	return (SpiTranserByte(Txdata));
//return(SPI1_SendByte(Txdata));


/*
	Spi_WriteByte(SPI1,Txdata);
	
	return(Spi_ReadByte(SPI1));

	*/
}




void SpiFlash_Chip_En(void)     //??¨ª¡§D???
{
//*********************************************************
// ¨°¨°SPI1 ?¨²¦Ì? MOSI?¡éMISO?¡éSCLK¨°y??¨®?¡Á¨¹??¨ºy?Y?¡ä¨®?¡ê??¨´¨°?¦Ì¡À¨º1¨®?SPI1¨º¡À¡ê?¡À?D??D??IO?¡ê
//  ?¨²¨º1¨®?SPI¨º¡À?¡ê¨¨?1?2??D??EBI????EBI2¨´¡Á¡Â¡ê??¨¦?¨¹3???????D??¨¤?¨²?¡ê¡À?D??¨²¨º¨ª¡¤?SPI1???? o¨®?D????EBI?¡ê¨º?
//unsigned char i=100;


//while(i--);
	FlashChip_En;

//SpiFlash_CS=0;// CS ¨°y????¦Ì¨ª 
}


void SpiFlash_Chip_Dis(void)   //¨º¨ª¡¤?
{
//unsigned char i=50;
	FlashChip_Dis;
//SpiFlash_CS=1;// CS¨°y??????
//?D????EBI?¡ê¨º? 

//while(i--);

}



//////void SPI1_Init(void)
//////{
//////	SPI_Open(SPI1, SPI_MASTER,SPI_MODE_0,8,2000000);
//////	//SYS_MFP_P14_Msk|
//////	SYS->P1_MFP &= ~(SYS_MFP_P15_Msk | SYS_MFP_P16_Msk | SYS_MFP_P17_Msk);		//IO?D?? ¦Ì?SPI?¡ê¨º?
//////  SYS->P1_MFP |=  SYS_MFP_P15_MOSI_0 | SYS_MFP_P16_MISO_0 | SYS_MFP_P17_SPICLK0;
//////	//SYS_MFP_P14_SPISS0|
//////	SPI_EnableAutoSS(SPI1, SPI_SS, SPI_SS_ACTIVE_LOW);
//////}


//--------------------?¨¢2¨´¡Á¡Â---------------------
unsigned long SpiFlash_Read_DevID(void)//?¨¢id  
{
unsigned long id;
unsigned long MID,MT,MC;
FlashChip_En;
	//SpiFlash_CS=0;

Spi_WriteReadByte(READ_CHIP_ID_COMM);//¡¤¡é?¨ª?¨¢ID?¨¹¨¢?
MID=Spi_WriteReadByte(0);
MT=Spi_WriteReadByte(0);	
MC=Spi_WriteReadByte(0);
MID=MID<<16;
MT=MT<<8;
id=MID|MT|MC;
//	id<<=8;
//	id+=Spi_ReadByte(SPI1);
//id= (unsigned int)Spi_ReadByte(SPI1)<<8;//?¨¢¨¨?IO
//id|= Spi_ReadByte(SPI1);
FlashChip_Dis;//SpiFlash_CS=1;
return id;
}


unsigned char SpiFlash_Read_Status(void)//---?¨¢¡Á¡ä¨¬?
{
unsigned char reg;
SpiFlash_Chip_En();
Spi_WriteReadByte( READ_STATUS_COMM);//¡¤¡é?¨ª?¨¢¡Á¡ä¨¬??¨¹¨¢?
//while(SPI_IS_BUSY(SPI1));//¦Ì¨¨¡äy¡¤¡é?¨ª¨ª¨º3¨¦

reg=Spi_WriteReadByte(0); //?¨¢¨¨?¡Á¡ä¨¬?
SpiFlash_Chip_Dis();
return reg;  
}

unsigned char SpiFlash_Wait_Busy(void)//?|?D??  1:?|
{
unsigned char st;uint16_t i=0;
while(i<0x1fff)
  {
   st=SpiFlash_Read_Status();
   if((st&0x01)!=0)//?|
     {
     i++;
     }
   else 
     break;
  }
if(i>=0x1fff) 
   return 1;//3?¨º¡À3?¡ä¨ª ¡¤¦Ì??
else
   return 0;//?y3¡ê
}


void SpiFlash_Read_Datas_Start(unsigned long  add)//?¨¢???¡¥   ¡ê¡§add:¡Á??¨²¦Ì??¡¤¡ê?
{
SpiFlash_Wait_Busy();//?|?D??

SpiFlash_Chip_En();
Spi_WriteReadByte(READ_DATA_COMM);//¡¤¡é?¨ª?¨¢¨ºy?Y?¨¹¨¢?
Spi_WriteReadByte((add>>16)&0xff);//?e¨º?¦Ì??¡¤
Spi_WriteReadByte( (add>>8)&0xff);
Spi_WriteReadByte( add&0xff);
//while(SPI_IS_BUSY(SPI1));//¦Ì¨¨¡äy¡¤¡é?¨ª¨ª¨º3¨¦
}

void SpiFlash_FastRead_Datas_Start(unsigned long  add)//?¨¬?¨¢???¡¥   ¡ê¡§add:¡Á??¨²¦Ì??¡¤¡ê?
{
unsigned char BACK=1;
while(BACK)
{BACK=SpiFlash_Wait_Busy();}//?|?D??
//SpiFlash_Wait_Busy();//?|?D??
SpiFlash_Chip_En();
Spi_WriteReadByte( FAST_READ_DATA_COMM);//¡¤¡é?¨ª?¨¬?¨´?¨¢?¨¹¨¢?
Spi_WriteReadByte( (add>>16)&0xff);//?e¨º?¦Ì??¡¤
Spi_WriteReadByte( (add>>8)&0xff);
Spi_WriteReadByte( add&0xff);
Spi_WriteReadByte( 0);
//while(SPI_IS_BUSY(SPI1));//¦Ì¨¨¡äy¡¤¡é?¨ª¨ª¨º3¨¦
}

void SpiFlash_Read_Data(unsigned long add ,unsigned char *rbuf,unsigned int len)
{
	int cnt;
	
	SpiFlash_FastRead_Datas_Start(add);
	for(cnt=0;cnt<len;cnt++)
		*rbuf++=Spi_WriteReadByte(0);	
	SpiFlash_Chip_Dis();
}




unsigned char SpiFlash_Read_Datas(void)//?¨¢¨ºy?Y
{
	
	return(Spi_WriteReadByte(0));
	
////SPI_TRIGGER(SPI1); //¡ä£¤¡¤¡é¨°???
////while(SPI_IS_BUSY(SPI1));	
////return(SPI_READ_RX0(SPI1));//?¨¢¨¨?¨ºy?Y2¡é¡¤¦Ì??
}

//----------------------2¨¢3y2¨´¡Á¡Â-----------
void SpiFlash_Page_Erase(unsigned long   page)//*****¨°32¨¢3y
{
SpiFlash_Wait_Busy();//?|?D??
SpiFlash_Write_En();//D¡ä¨º1?¨¹

SpiFlash_Chip_En();
Spi_WriteReadByte( PAGE_ERASE_COMM);//2¨¢3y
Spi_WriteReadByte( (page>>16)&0xff);//
Spi_WriteReadByte( (page>>8)&0xff);
Spi_WriteReadByte( page&0xff);
//while(SPI_IS_BUSY(SPI1));//¦Ì¨¨¡äy¡¤¡é?¨ª¨ª¨º3¨¦
SpiFlash_Chip_Dis();
}

void SpiFlash_Sector_Erase(unsigned long   sector)//*****¨¦¨¨??2¨¢3y
{
SpiFlash_Wait_Busy();//?|?D??
SpiFlash_Write_En();//D¡ä¨º1?¨¹

SpiFlash_Chip_En();
Spi_WriteReadByte( SECTOR_ERASE_COMM);//2¨¢3y
sector<<=4;
Spi_WriteReadByte( (sector>>8)&0xff);//
Spi_WriteReadByte( sector&0xff);
Spi_WriteReadByte( 0);
//while(SPI_IS_BUSY(SPI1));//¦Ì¨¨¡äy¡¤¡é?¨ª¨ª¨º3¨¦
SpiFlash_Chip_Dis();
}

void SpiFlash_Block_Erase(unsigned long   block)//*****?¨¦2¨¢3y
{
SpiFlash_Wait_Busy();//?|?D??
SpiFlash_Write_En();//D¡ä¨º1?¨¹
SpiFlash_Chip_En();
Spi_WriteReadByte( BLOCK_ERASE_COMM);//2¨¢3y
Spi_WriteReadByte( block&0xff);//
Spi_WriteReadByte( 0);
Spi_WriteReadByte( 0);
//while(SPI_IS_BUSY(SPI1));//¦Ì¨¨¡äy¡¤¡é?¨ª¨ª¨º3¨¦
SpiFlash_Chip_Dis();
}

void SpiFlash_Chip_Erase(void)//*****????2¨¢3y
{
SpiFlash_Wait_Busy();//?|?D??
SpiFlash_Write_En();//D¡ä¨º1?¨¹
SpiFlash_Chip_En();
Spi_WriteReadByte(CHIP_ERASE_COMM);//2¨¢3y
//while(SPI_IS_BUSY(SPI1));//¦Ì¨¨¡äy¡¤¡é?¨ª¨ª¨º3¨¦
SpiFlash_Chip_Dis();
SpiFlash_Wait_Busy();//?|?D??
}

//--------------------D¡ä2¨´¡Á¡Â----------------------

void SpiFlash_Write_En(void)//D¡ä¨º1?¨¹
{
SpiFlash_Chip_En();
Spi_WriteReadByte( WRITE_EN_COMM);//¡¤¡é?¨ªD¡ä?¨ºD¨ª?¨¹¨¢?
//while(SPI_IS_BUSY(SPI1));//¦Ì¨¨¡äy¡¤¡é?¨ª¨ª¨º3¨¦
SpiFlash_Chip_Dis();
}

void SpiFlash_Write_Dis(void)//D¡ä???1
{
SpiFlash_Chip_En();
Spi_WriteReadByte( WRITE_DIS_COMM); //¡¤¡é?¨ªD¡ä???1?¨¹¨¢?
//while(SPI_IS_BUSY(SPI1));//¦Ì¨¨¡äy¡¤¡é?¨ª¨ª¨º3¨¦
SpiFlash_Chip_Dis();
}

void SpiFlash_Page_Program(unsigned char *wbuf,   unsigned long   page,   uint16_t   length)//*****¨°3¡À¨¤3¨¬
{
uint16_t n;
unsigned char BACK=1;
while(BACK)
{BACK=SpiFlash_Wait_Busy();}//?|?D??
	
SpiFlash_Write_En();//D¡ä¨º1?¨¹

SpiFlash_Chip_En();
Spi_WriteReadByte( PAGE_PROGRAM_COMM);//¡À¨¤3¨¬?¨¹¨¢?
Spi_WriteReadByte( (page>>8)&0xff);//
Spi_WriteReadByte( page&0xff);
Spi_WriteReadByte( 0);
//while(SPI_IS_BUSY(SPI1));//¦Ì¨¨¡äy¡¤¡é?¨ª¨ª¨º3¨¦

for(n=0;n<length;n++)
  {
   Spi_WriteReadByte( *wbuf++);
  }

//while(SPI_IS_BUSY(SPI1));//¦Ì¨¨¡äy¡¤¡é?¨ª¨ª¨º3¨¦
SpiFlash_Chip_Dis();
//SpiFlash_Write_Dis();//D¡ä???1
}




void SpiFlash_SectorOfPage_Erase(unsigned long page)
{
unsigned long write_page=0;	
	
unsigned long sector=0;
unsigned int bufofpage=0;
	
unsigned char * pwrbuf;
	unsigned char wrcnt=0;
	
		if(W25Q16_Mode==0)
	{//W25Q16 ?¡ê¨º?
		
		return;
	}
	
if(page>=16)
	{
		sector=page/16;//????SECOTR	
	}
	
	if(OldSector!=sector)	
		{
			OldSector=sector;
			SpiFlash_Sector_Erase(sector);//¨¦?3y¦Ì¡À?¡ã¨¦¨¨??
		}
		
}


//*****************************
//¨°??? M25PE16 ¡Á¡§¨®? ¡ä?D????¨¦¦Ì£¤¡Á??¨²2¨¢D¡ä

void SpiFlash_Page_Write(unsigned char *wbuf,   unsigned long   page,   uint16_t   length)//*****¨°3D¡ä
{
uint16_t n;

		
	//	/*
SpiFlash_Wait_Busy();//?|?D??
SpiFlash_Write_En();//D¡ä¨º1?¨¹

SpiFlash_Chip_En();
Spi_WriteReadByte( PAGE_WRITE_COMM);//D¡ä?¨¹¨¢?
Spi_WriteReadByte( (page>>8)&0xff);//
Spi_WriteReadByte( page&0xff);
Spi_WriteReadByte( 0);

for(n=0;n<length;n++)
  {
   Spi_WriteReadByte( *wbuf++);
  }
//while(SPI_IS_BUSY(SPI1));//¦Ì¨¨¡äy¡¤¡é?¨ª¨ª¨º3¨¦
SpiFlash_Chip_Dis();
		
	//	*/
}


 




void SpiFlash_Bytes_Write(unsigned char *wbuf,   unsigned long  add,   uint16_t   length)//*****¡Á??¨²D¡ä
{
uint16_t n;
SpiFlash_Wait_Busy();//?|?D??
SpiFlash_Write_En();//D¡ä¨º1?¨¹
SpiFlash_Chip_En();
Spi_WriteReadByte( PAGE_WRITE_COMM);//D¡ä?¨¹¨¢?
Spi_WriteReadByte( (add>>16)&0xff);//
Spi_WriteReadByte( (add>>8)&0xff);
Spi_WriteReadByte( add&0xff);

for(n=0;n<length;n++)
  {
   Spi_WriteReadByte( *wbuf++);
  }

//while(SPI_IS_BUSY(SPI1));//¦Ì¨¨¡äy¡¤¡é?¨ª¨ª¨º3¨¦
SpiFlash_Chip_Dis();

}


