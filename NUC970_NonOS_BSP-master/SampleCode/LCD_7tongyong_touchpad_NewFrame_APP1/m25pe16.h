#ifndef __M25PE16_H
#define __M25PE16_H

#include "main.h"
#include "spi_config.h"


//-----ÃüÁî
#define WRITE_EN_COMM          0x06  //Ð´Ê¹ÄÜ
#define WRITE_DIS_COMM         0x04   //Ð´½ûÖ¹

#define READ_CHIP_ID_COMM      0x9F//¶Áid  24bytes
#define READ_STATUS_COMM       0x05//¶Á×´Ì¬¼Ä´æÆ÷
#define WRITE_STATUS_COMM      0x01//Ð´×´Ì¬¼Ä´æÆ÷
#define WRITE_LOCK_REG_COMM    0xE5//
#define READ_LOCK_REG_COMM     0xE8
#define READ_DATA_COMM         0x03//¶ÁÊý¾Ý
#define FAST_READ_DATA_COMM    0x0B//¿ìËÙ¶ÁÊý¾Ý

#define PAGE_WRITE_COMM        0x0A//Ò³Ð´
#define PAGE_PROGRAM_COMM      0x02//Ò³±à³Ì
#define PAGE_ERASE_COMM        0xDB//Ò³²Á³ý
#define BLOCK_ERASE_COMM       0xD8//¿é²Á³ý
#define SECTOR_ERASE_COMM      0x20//ÉÈÇø²Á³ý
#define CHIP_ERASE_COMM        0xC7//ÕûÆ¬²Á³ý

#define DEEP_POWER_DOWN_COMM   0xB9
#define DEEP_POWER_UP_COMM    0xAB


#define FlashChip_En   SPI0_SEL_EN  //Ñ¡Í¨Ð¾Æ¬
#define FlashChip_Dis  SPI0_SEL_DIS  //ÊÍ·Å

//-------------flashÐ¾Æ¬²ÎÊý
#define PAGE_SIZE      256//Ò³´óÐ¡
#define SECTOR_SIZE   (PAGE_SIZE*16)//ÉÈÇø´óÐ¡=16Ò³    4k
#define BLOCK_SIZE     (SECTOR_SIZE*16)//¿é´óÐ¡=16ÉÈÇø  64k

extern Int8U Chip_id[20];//¶ÁÐ¾Æ¬idÂë       £¨20 80 15 10 ¡­¡­¿ªÍ·£©


//¡¾****************¶Á²Ù×÷**********************¡¿
void Read_DevID(void);
Int8U Read_Status(void);//---¶Á×´Ì¬
Int8U Wait_Busy(void);//Ã¦ÅÐ¶Ï  1:Ã¦

void Read_Datas_Start(Int32U  add);//¶ÁÆô¶¯   £¨add:×Ö½ÚµØÖ·£©
void FastRead_Datas_Start(Int32U  add);//¿ì¶ÁÆô¶¯   £¨add:×Ö½ÚµØÖ·£©
Int8U ReadFlash_Datas(void);//¶ÁÊý¾Ý

//¡¾***************Ð´²Ù×÷**********************¡¿
void Write_En(void);//Ê¹ÄÜ Ð´
void Write_Dis(void);//½ûÖ¹ Ð´


//*****Ò³±à³Ì£¨±à³ÌÒ»Ò³£©
void Page_Program(pInt8U   wbuf,   Int32U   page,   Int16U   length);//wbuf£º´ýÐ´Êý¾Ý»º³åÇø£¬page£ºÆðÊ¼Ò³µØÖ·£¬length£ºÊý¾Ý³¤¶È<=256
//*****Ò³Ð´£¨Ð´ÈëÒ»Ò³£©
void Page_Write(pInt8U   wbuf,   Int32U   page,   Int16U   length);//wbuf£º´ýÐ´Êý¾Ý»º³åÇø£¬page£ºÆðÊ¼Ò³µØÖ·£¬length£ºÊý¾Ý³¤¶È<=256
//*****×Ö½ÚÐ´£¨ÏòÈÎÒâµØÖ·Ð´ÈëÈô¸É×Ö½Ú£¬µ«ÐëÐ¡ÓÚÒ»Ò³£©
void Bytes_Write(pInt8U   wbuf,   Int32U  add,   Int16U   length);//wbuf£º´ýÐ´Êý¾Ý»º³åÇø£¬add£ºÆðÊ¼×Ö½ÚµØÖ·£¬length£ºÊý¾Ý³¤¶È<=256


//¡¾************²Á³ý²Ù×÷***********************¡¿
void Chip_Erase(void);//*****ÕûÆ¬²Á³ý
void Page_Erase(Int32U   page);//*****Ò³²Á³ý       page£ºÒ³µØÖ·
void Sector_Erase(Int32U   sector);//*****ÉÈÇø²Á³ý
void Block_Erase(Int32U   block);//*****¿é²Á³ý


extern void Write_25pe_data(pInt8U   wbuf,   Int32U  add,   Int32U   size); //*****×Ö½ÚÐ
#endif
