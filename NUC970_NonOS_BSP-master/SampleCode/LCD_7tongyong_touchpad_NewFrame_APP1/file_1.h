


#ifndef _FILE_H
#define _FILE_H


#include"nandflash.h"



//#define NAND_FREE 0xffff    //页为空标志数据

#define FILE_INFO_START_SECTOR     0 //信号块号码
#define FILE_INFO_START_PAGE      10   //第十页
#define FILE_INFO_LENGTH           256 // (128+8)//文件信息长度

#define FILE_INFO_NUMS_1PAGE          (NF_PAGE_BYTES/FILE_INFO_LENGTH)  //页文件信息 个数


//#define FILE_NAME_LENGTH          128

#define FILE_NUMS                 128  //最大文件数
#define FILE_START_SECTOR          10 //从第十块开始写文件

//************sdram 文件缓冲区
#define NF_SECTOR_SDRAM_BUF       0x80100000//nand块 sdram缓冲区

#define DOWNFILE_SDRAM_ADD       0x80200000  //下载文件的buf地址

/***


typedef struct 
{
unsigned char FileName[128];
unsigned int FileLength;
unsigned int FileAdd_Sector;//
}FILES;
**/

typedef union
{
unsigned char fName256[256];
struct 
	{
	unsigned char FileName[128];
	unsigned int FileLength;
	unsigned int FileAdd_Sector;//
	};
} FILES;



typedef struct 
{
unsigned short iFileStartSector;
unsigned short iFileSectorTable[1024];
}FILE_STORE_INFO;


typedef struct 
{
unsigned int iFileNameSector;
unsigned int iFileNamePage;
unsigned int iFileNameAddress;
unsigned int iFileNameIndex;
}FILE_NAME;




extern FILES iFiles;
extern FILES iFilesTemp;
extern FILE_STORE_INFO iFileSectorInfo;

extern FILE_NAME iFileName;
extern unsigned short FileNum;



void Nand_Format(void);
//******************************
void Nand_FillPage_SDbuf(unsigned short page,unsigned int length,unsigned char filldata); //填充 sdram块复制区中的一页
void Nand_WritePage_SDbuf(unsigned short page,unsigned int length,unsigned char *wpdata); //从wpdata 写入 sdram块复制区中 一页


unsigned char FileWrite(FILES file,  unsigned char *pSDbuf);//fhandle????????????
unsigned char FileRead(unsigned char *fname,unsigned char *buf);
unsigned int  File_GetFreeSector(void);  //获取可用块
unsigned char File_CreateStartSector(void); //创建一个起始块用于保存系统参数
void File_GetStartSector(void); //读取起始块和坏块
unsigned char File_Delete(unsigned char *fname); //删除一个文件
unsigned char File_Create(unsigned char *fname);  //创键一个文件
unsigned int File_Find(unsigned char *fname);  //查找一个文件是否存在 返回一个地址

extern void ChangeFileName1(unsigned char * name);
extern void ChangeFileName1(unsigned char * name);


#endif