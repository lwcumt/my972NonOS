#ifndef __M25PE16_H
#define __M25PE16_H

#include "main.h"
#include "spi_config.h"


//-----命令
#define WRITE_EN_COMM          0x06  //写使能
#define WRITE_DIS_COMM         0x04   //写禁止

#define READ_CHIP_ID_COMM      0x9F//读id  24bytes
#define READ_STATUS_COMM       0x05//读状态寄存器
#define WRITE_STATUS_COMM      0x01//写状态寄存器
#define WRITE_LOCK_REG_COMM    0xE5//
#define READ_LOCK_REG_COMM     0xE8
#define READ_DATA_COMM         0x03//读数据
#define FAST_READ_DATA_COMM    0x0B//快速读数据

#define PAGE_WRITE_COMM        0x0A//页写
#define PAGE_PROGRAM_COMM      0x02//页编程
#define PAGE_ERASE_COMM        0xDB//页擦除
#define BLOCK_ERASE_COMM       0xD8//块擦除
#define SECTOR_ERASE_COMM      0x20//扇区擦除
#define CHIP_ERASE_COMM        0xC7//整片擦除

#define DEEP_POWER_DOWN_COMM   0xB9
#define DEEP_POWER_UP_COMM    0xAB


#define FlashChip_En   SPI0_SEL_EN  //选通芯片
#define FlashChip_Dis  SPI0_SEL_DIS  //释放

//-------------flash芯片参数
#define PAGE_SIZE      256//页大小
#define SECTOR_SIZE   (PAGE_SIZE*16)//扇区大小=16页    4k
#define BLOCK_SIZE     (SECTOR_SIZE*16)//块大小=16扇区  64k

extern Int8U Chip_id[20];//读芯片id码       （20 80 15 10 ……开头）


//【****************读操作**********************】
void Read_DevID(void);
Int8U Read_Status(void);//---读状态
Int8U Wait_Busy(void);//忙判断  1:忙

void Read_Datas_Start(Int32U  add);//读启动   （add:字节地址）
void FastRead_Datas_Start(Int32U  add);//快读启动   （add:字节地址）
Int8U ReadFlash_Datas(void);//读数据

//【***************写操作**********************】
void Write_En(void);//使能 写
void Write_Dis(void);//禁止 写


//*****页编程（编程一页）
void Page_Program(pInt8U   wbuf,   Int32U   page,   Int16U   length);//wbuf：待写数据缓冲区，page：起始页地址，length：数据长度<=256
//*****页写（写入一页）
void Page_Write(pInt8U   wbuf,   Int32U   page,   Int16U   length);//wbuf：待写数据缓冲区，page：起始页地址，length：数据长度<=256
//*****字节写（向任意地址写入若干字节，但须小于一页）
void Bytes_Write(pInt8U   wbuf,   Int32U  add,   Int16U   length);//wbuf：待写数据缓冲区，add：起始字节地址，length：数据长度<=256


//【************擦除操作***********************】
void Chip_Erase(void);//*****整片擦除
void Page_Erase(Int32U   page);//*****页擦除       page：页地址
void Sector_Erase(Int32U   sector);//*****扇区擦除
void Block_Erase(Int32U   block);//*****块擦除
#endif
