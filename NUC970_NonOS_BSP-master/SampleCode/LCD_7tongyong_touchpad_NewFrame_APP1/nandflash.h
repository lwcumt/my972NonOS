
#ifndef _NANDFLASH_H
#define _NANDFLASH_H

#include "main.h"



//-----------*********nand 类型 预定义**************
#define   HY27US0856         0
#define   K9F1G08            1
//------------ID
#define K9FXX_ID			    0xECF10000	/* Byte 3 and 2 only */ 
#define HY27US08561A_ID			0xAD750000	/* 32MB */ 

//#define  NAND_TYPE  HY27US0856
#define  NAND_TYPE  K9F1G08
//------------***********nand 结构定义**************

#if  NAND_TYPE==HY27US0856//----------HY27US08561A ------- 32MB
	#define NF_PAGE_BYTES      512  //页数据大小   Byte
	#define NF_PAGE_BITS       9  //页地址位数   bit
	#define NF_BLOCK_PAGES     32  //一块32页
	#define NF_BLOCK_BYTES    (NF_PAGE_BYTES*NF_BLOCK_PAGES) //块数据大小  16K
	#define NF_BLOCK_BITS     14 //块地址位数  bit
	#define NF_BLOCKS          2048   //2048块
	
	//#define NF_PAGE_SIZE      (NF_PAGE_BYTES+16)  //页空间大小   528 Byte
	//#define NF_BLOCK_SIZE     (NF_PAGE_SIZE*NF_BLOCK_PAGES) //块空间大小  16K+16*32
	
	#define PAGE_MASK     (NF_PAGE_BYTES-1)//一页mask

#elif NAND_TYPE==K9F1G08//----------HY27US08561A ------- 128MB
	#define NF_PAGE_BYTES      2048  //页大小   2K
	#define NF_SECTOR_BYTES      512  //扇区大小   512
	#define NF_PAGE_BITS       11  //页地址位数
	#define NF_BLOCK_PAGES     64  //一块64页
	#define NF_BLOCK_BYTES    (NF_PAGE_BYTES*NF_BLOCK_PAGES) //块大小  128K
	#define NF_BLOCK_BITS     17 //块地址位数  bit
	#define NF_BLOCKS          1024   //最大1024块

	#define PAGE_MASK     (NF_PAGE_BYTES-1)//一页mask

#endif
//******************nand 命令定义******************
#if  NAND_TYPE==HY27US0856//----------HY27US08561A ------- 32MB
	#define   READ1_LOW_CMMD           0x00//低256字节
	#define   READ1_HIGH_CMMD          0x01//高256字节
	#define   READ2_CMMD               0x50//
	#define   READ_ID_CMMD             0x90//读id
	#define   RESET_CMMD               0xff//复位

	#define   PAGE_PROGRAM_CMMD1       0x80//页编程1st
	#define   PAGE_PROGRAM_CMMD2       0x10//页编程2st

	#define   COPY_BACK_PRG_CMMD1      0x00//1st
	#define   COPY_BACK_PRG_CMMD2      0x8A//2st
	#define   COPY_BACK_PRG_CMMD3      0x10//3st

	#define   BLOCK_ERASE_CMMD1        0x60//1st
	#define   BLOCK_ERASE_CMMD2        0xD0//2st

	#define   READ_STATUS_CMMD         0x70//
	#define   LOCK_BLOCK_CMMD          0x2A//
	#define   LOCK_TIGHT_CMMD          0x2C//
	#define   ULOCK_START_CMMD         0x23//
	#define   ULOCK_END_CMMD           0x24//
	#define   READ_LOCK_CMMD           0x7A//

#elif NAND_TYPE==K9F1G08//----------K9F1G08 ------- 128MB
	#define   READ_CMMD1              0x00
	#define   READ_CMMD2              0x30
	
	#define   READ_COPYBACK_COMMD1     0x00
	#define   READ_COPYBACK_COMMD2     0x35
	
	#define   READ_ID_CMMD             0x90//读id
	#define   RESET_CMMD               0xff//复位
	
	#define   PAGE_PROGRAM_CMMD1       0x80//页编程1st
	#define   PAGE_PROGRAM_CMMD2       0x10//页编程2st

	#define   COPY_BACK_PRG_CMMD1      0x85//1st
	#define   COPY_BACK_PRG_CMMD2      0x10//2st
	
	#define   BLOCK_ERASE_CMMD1        0x60//1st
	#define   BLOCK_ERASE_CMMD2        0xD0//2st
	
	#define   READ_STATUS_CMMD         0x70//
	

#endif
//----------***********nand操作地址*****************
#define NANDFLASH_COMMAND_ADDR  (Int32U)0x82200000
/// Address for transferring address bytes to the nandflash.
#define NANDFLASH_ADDRESS_ADDR  (Int32U)0x82400000
/// Address for transferring data bytes to the nandflash.
#define NANDFLASH_DATA_ADDR     (Int32U)0x82000000
//#define NANDFLASH_READ_ADDR     (Int32U)0x80000000





//-----------************nand管脚定义*********************
#define NAND_CS2  (1<<25)//     (1<<14)//p2.14  片选
//#define NAND_CS_DIROUT  FIO2DIR |=NAND_CS2
#define NAND_CS_EN()  outpw(REG_NANDCTL, (inpw(REG_NANDCTL)&(~0x06000000))|0x00000000);
//outpw(REG_NANDCTL,~NAND_CS2)    // FIO2CLR = NAND_CS2
#define NAND_CS_DIS()   outpw(REG_NANDCTL, (inpw(REG_NANDCTL)&(~0x06000000))|0x02000000);
//outpw(REG_NANDCTL,NAND_CS2)  //FIO2SET = NAND_CS2

//////#define NAND_RB         15//p2.15       忙
//////#define NAND_RB_DIRIN   FIO2DIR &=~(1ul<<NAND_RB)
//////#define NAND_RB_PIN     (FIO2PIN &(1ul<<NAND_RB))







extern unsigned int NandID;//nand id

extern pInt8U pNF_ComdAdd;   //命令
extern pInt8U pNF_AddrAdd;  //地址
extern pInt8U pNF_DataAdd;   //数据

extern Int8U NandEccWrite_Flag;


extern Int16U InvalidBlock[NF_BLOCKS];//坏块存储
extern unsigned short Nf_InvalidCou;

//---------------nand 读写-------------
void NF_WriteCOMMD(Int8U cmd);//写 命令
void NF_WriteADDR(Int32U add);//写 地址
void NF_WriteDATA(Int8U data);//写 数据 DATA
void NF_WriteBUFF(Int8U data);//写 数据BUFF
Int8U NF_ReadDATA(void);//写 数据
void NF_WaitBusy(void);//-------------------忙等待

//----------------------nand  数据操作--------------
Int8U Nand_ReadStatus(void);//读状态0x70
void Nand_ReadID(void);//读id
void Nand_Reset(void);//复位nand



Int8U Nand_EraseBlock(Int32U block);//块擦除
Int8U Nand_WriteBytes(pInt8U databuf,Int32U nandadd);//向绝对地址写 数据 ------------     nandadd：nand绝对地址           databuf:数据缓存区
extern Int8U Nand_Write_1Page_1(pInt8U databuf,Int32U page);//=====***=====写一整数页 数据 -    page：整页地址           databuf:数据缓存区
Int8U Nand_Write_1Page(pInt8U databuf,Int32U page);//=====***=====写一整数页 数据 -    page：整页地址           databuf:数据缓存区

void Nand_Read_1page(pInt8U databuf,Int32U page);//=======****====读一整数页数据 -    page:整数页(按2k Byte)
void Nand_ReadBytes(pInt8U databuf,Int32U nandadd,Int32U size);//读<=1page数据 -------------- nandadd:绝对地址
void Nand_ReadDates(pInt8U databuf,Int32U nandadd,Int32U size);// 读任意地址，任意长度 数据#############################

void Nand_ReadBlock(unsigned int block,unsigned char *pSDbuf); //读取一块 至sdram 缓冲区
void Nand_WriteBlock(unsigned int block,unsigned char *pSDbuf);//sdram数据回写到nand一块
//void Nand_Format(void);

//******************************
//void Nand_FillPage_SDbuf(unsigned short page,unsigned int length,unsigned char filldata); //填充 sdram块复制区中的一页
//void Nand_WritePage_SDbuf(unsigned short page,unsigned int length,unsigned char *wpdata); //从wpdata 写入 sdram块复制区中 一页


#endif
