#ifndef __M25PE16_H
#define __M25PE16_H

#include "main.h"
#include "spi_config.h"


//-----?¨¹¨¢?
#define WRITE_EN_COMM          0x06  //D¡ä¨º1?¨¹
#define WRITE_DIS_COMM         0x04   //D¡ä???1

#define READ_CHIP_ID_COMM      0x9F//?¨¢id  24bytes
#define READ_STATUS_COMM       0x05//?¨¢¡Á¡ä¨¬???¡ä??¡Â
#define WRITE_STATUS_COMM      0x01//D¡ä¡Á¡ä¨¬???¡ä??¡Â
#define WRITE_LOCK_REG_COMM    0xE5//
#define READ_LOCK_REG_COMM     0xE8
#define READ_DATA_COMM         0x03//?¨¢¨ºy?Y
#define FAST_READ_DATA_COMM    0x0B//?¨¬?¨´?¨¢¨ºy?Y

#define PAGE_WRITE_COMM        0x0A//¨°3D¡ä
#define PAGE_PROGRAM_COMM      0x02//¨°3¡À¨¤3¨¬
#define PAGE_ERASE_COMM        0xDB//¨°32¨¢3y
#define BLOCK_ERASE_COMM       0xD8//?¨¦2¨¢3y
#define SECTOR_ERASE_COMM      0x20//¨¦¨¨??2¨¢3y
#define CHIP_ERASE_COMM        0xC7//????2¨¢3y

#define DEEP_POWER_DOWN_COMM   0xB9
#define DEEP_POWER_UP_COMM    0xAB


#define FlashChip_En   SPI0_SEL_EN  //??¨ª¡§D???
#define FlashChip_Dis  SPI0_SEL_DIS  //¨º¨ª¡¤?

//-------------flashD???2?¨ºy
#define PAGE_SIZE      256//¨°3¡ä¨®D?
#define SECTOR_SIZE   (PAGE_SIZE*16)//¨¦¨¨??¡ä¨®D?=16¨°3    4k
#define BLOCK_SIZE     (SECTOR_SIZE*16)//?¨¦¡ä¨®D?=16¨¦¨¨??  64k

extern Int8U Chip_id[20];//?¨¢D???id??       ¡ê¡§20 80 15 10 ?-?-?a¨ª¡¤¡ê?


extern unsigned char df_page_bits;
extern unsigned int df_page_lenth;
extern unsigned char WBUFF[28];
extern unsigned char RBUFF[528];


//??****************?¨¢2¨´¡Á¡Â**********************??
void Read_DevID(void);
Int8U Read_Status(void);//---?¨¢¡Á¡ä¨¬?
Int8U Wait_Busy(void);//?|?D??  1:?|

void Read_Datas_Start(Int32U  add);//?¨¢???¡¥   ¡ê¡§add:¡Á??¨²¦Ì??¡¤¡ê?
void FastRead_Datas_Start(Int32U  add);//?¨¬?¨¢???¡¥   ¡ê¡§add:¡Á??¨²¦Ì??¡¤¡ê?
Int8U ReadFlash_Datas(void);//?¨¢¨ºy?Y

//??***************D¡ä2¨´¡Á¡Â**********************??
void Write_En(void);//¨º1?¨¹ D¡ä
void Write_Dis(void);//???1 D¡ä


//*****¨°3¡À¨¤3¨¬¡ê¡§¡À¨¤3¨¬¨°?¨°3¡ê?
void Page_Program(pInt8U   wbuf,   Int32U   page,   Int16U   length);//wbuf¡êo¡äyD¡ä¨ºy?Y?o3???¡ê?page¡êo?e¨º?¨°3¦Ì??¡¤¡ê?length¡êo¨ºy?Y3¡è?¨¨<=256
//*****¨°3D¡ä¡ê¡§D¡ä¨¨?¨°?¨°3¡ê?
void Page_Write(pInt8U   wbuf,   Int32U   page,   Int16U   length);//wbuf¡êo¡äyD¡ä¨ºy?Y?o3???¡ê?page¡êo?e¨º?¨°3¦Ì??¡¤¡ê?length¡êo¨ºy?Y3¡è?¨¨<=256
//*****¡Á??¨²D¡ä¡ê¡§?¨°¨¨?¨°a¦Ì??¡¤D¡ä¨¨?¨¨??¨¦¡Á??¨²¡ê?¦Ì?D?D?¨®¨²¨°?¨°3¡ê?
void Bytes_Write(pInt8U   wbuf,   Int32U  add,   Int16U   length);//wbuf¡êo¡äyD¡ä¨ºy?Y?o3???¡ê?add¡êo?e¨º?¡Á??¨²¦Ì??¡¤¡ê?length¡êo¨ºy?Y3¡è?¨¨<=256


//??************2¨¢3y2¨´¡Á¡Â***********************??
void Chip_Erase(void);//*****????2¨¢3y
void Page_Erase(Int32U   page);//*****¨°32¨¢3y       page¡êo¨°3¦Ì??¡¤
void Sector_Erase(Int32U   sector);//*****¨¦¨¨??2¨¢3y
void Block_Erase(Int32U   block);//*****?¨¦2¨¢3y


//======================================
void Write45db_2Pages(pInt8U   wbuf,   Int32U  page);
extern void Write_25pe_data(pInt8U   wbuf,   Int32U  add,   Int32U   size); //*****¡Á??¨²?


extern  unsigned long spiflashID;

#define SpiFlash_CS PH7

extern unsigned int SF_ChipID;
extern unsigned char Chip_id[20];//?¨¢D???id??       ¡ê¡§20 80 15 10 ?-?-?a¨ª¡¤¡ê?

extern unsigned int SpiFlashPageCou;

//extern void SPI0_Init(void);

extern unsigned char Spi_WriteReadByte(unsigned char Txdata);



//---------------------------------
extern void SpiFlash_Chip_En(void);
extern void SpiFlash_Chip_Dis(void);   //¨º¨ª¡¤?

//??****************?¨¢2¨´¡Á¡Â**********************??

extern unsigned long SpiFlash_Read_DevID(void);
extern unsigned char SpiFlash_Read_Status(void);//---?¨¢¡Á¡ä¨¬?
extern unsigned char SpiFlash_Wait_Busy(void);//?|?D??  1:?|

extern void SpiFlash_Read_Datas_Start(unsigned long  add);//?¨¢???¡¥   ¡ê¡§add:¡Á??¨²¦Ì??¡¤¡ê?
extern void SpiFlash_FastRead_Datas_Start(unsigned long  add);//?¨¬?¨¢???¡¥   ¡ê¡§add:¡Á??¨²¦Ì??¡¤¡ê?

void SpiFlash_Read_Data(unsigned long add ,unsigned char *rbuf,unsigned int len);

extern unsigned char SpiFlash_Read_Datas(void);//?¨¢¦Ì£¤??¡Á??¨²¨ºy?Y  8???¡ê¨º?

void Write45db_2Pages_W25Q16(pInt8U   wbuf,   Int32U  page);

//??¨¨YW25Q16
void Write_25pe_data_W25Q16(pInt8U   wbuf,   Int32U  add,   Int32U   size);//*****¡Á??¨²D¡ä


//??***************D¡ä2¨´¡Á¡Â**********************??
void SpiFlash_Write_En(void);//¨º1?¨¹ D¡ä
void SpiFlash_Write_Dis(void);//???1 D¡ä


//*****¨°3¡À¨¤3¨¬¡ê¡§¡À¨¤3¨¬¨°?¨°3¡ê?
void SpiFlash_Page_Program(unsigned char *wbuf,   unsigned long   page,   uint16_t   length);//wbuf¡êo¡äyD¡ä¨ºy?Y?o3???¡ê?page¡êo?e¨º?¨°3¦Ì??¡¤¡ê?length¡êo¨ºy?Y3¡è?¨¨<=256
//*****¨°3D¡ä¡ê¡§D¡ä¨¨?¨°?¨°3¡ê?
void SpiFlash_Page_Write(unsigned char *wbuf,   unsigned long   page,   uint16_t   length);//wbuf¡êo¡äyD¡ä¨ºy?Y?o3???¡ê?page¡êo?e¨º?¨°3¦Ì??¡¤¡ê?length¡êo¨ºy?Y3¡è?¨¨<=256
//*****¡Á??¨²D¡ä¡ê¡§?¨°¨¨?¨°a¦Ì??¡¤D¡ä¨¨?¨¨??¨¦¡Á??¨²¡ê?¦Ì?D?D?¨®¨²¨°?¨°3¡ê?
void SpiFlash_Bytes_Write(unsigned char *wbuf,   unsigned long  add,   uint16_t   length);//wbuf¡êo¡äyD¡ä¨ºy?Y?o3???¡ê?add¡êo?e¨º?¡Á??¨²¦Ì??¡¤¡ê?length¡êo¨ºy?Y3¡è?¨¨<=256


//??************2¨¢3y2¨´¡Á¡Â***********************??
void SpiFlash_Chip_Erase(void);//*****????2¨¢3y
void SpiFlash_Page_Erase(unsigned long   page);//*****¨°32¨¢3y       page¡êo¨°3¦Ì??¡¤
void SpiFlash_Sector_Erase(unsigned long   sector);//*****¨¦¨¨??2¨¢3y
void SpiFlash_Block_Erase(unsigned long   block);//*****?¨¦2¨¢3y
//***************************D¡ä¨¨?¨°a3¡è?¨¨¨ºy?Y*****
void Write_25pe_data(uint8_t *wbuf,   uint32_t  add,   uint32_t   size);//*****¡Á??¨²D¡ä

void SpiFlash_SectorOfPage_Erase(unsigned long page);

#endif
