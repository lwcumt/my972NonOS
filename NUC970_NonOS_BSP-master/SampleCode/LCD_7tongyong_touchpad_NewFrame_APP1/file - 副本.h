/*
文件系统头





*/





#ifndef _FILE_H
#define _FILE_H


//#include<stdlib.h>
#include "main.h"

#include"nandflash.h"



//#define NAND_FREE 0xffff    //页为空标志数据
/*
#define FILE_INFO_START_SECTOR     32//信号块号码
#define FILE_INFO_START_PAGE      10   //第十页
#define FILE_INFO_LENGTH          256  //文件信息长度

#define FILE_INFO_NUMS_1PAGE          (NF_PAGE_BYTES/FILE_INFO_LENGTH)  //页文件信息 个数


//#define FILE_NAME_LENGTH          128

#define FILE_NUMS                 128  //最大文件数
#define FILE_START_SECTOR          10 +FILE_INFO_START_SECTOR//从第十块开始写文件
*/
//************sdram 文件缓冲区
#define NF_SECTOR_SDRAM_BUF      0x80800000//(SDRAM0_BASE_ADDR+0x180000) //nand块 sdram缓冲区 0x81300000//

#define DOWNFILE_SDRAM_ADD       (NF_SECTOR_SDRAM_BUF+0x200000)  //下载文件的buf地址


#define MEM_PAGE_FREE 0xffff    //页为空标志数据

#define FILE_INFO_START_SECTOR  32//信号块号码
// #define FILE_INFO_PAGE_NUM 0   //第十页
#define FILE_INFO_START_PAGE     0// 10   //第十页
#define FILE_INFO_LENGTH          256  //文件信息长度

#define FILE_INFO_LENGTH          256  //文件信息长度
#define FILE_MAXNUM    128  //最大文件数


#define FILE_SAVE_UNUSER_SECTOR (FILE_INFO_START_SECTOR+5)
#define FILE_SAVE_BOOTAPP_SECTOR  (FILE_INFO_START_SECTOR+8)
#define FILE_SAVE_SECTOR  (10+FILE_INFO_START_SECTOR) //从第十块开始写文件

#define UNUSER 0xffff

#define INUSER 0

typedef struct 
{
unsigned char FileName[128];
unsigned int FileLength;
unsigned int FileAddress;//
unsigned char FileTempBuf[16];
}FILES;



typedef struct 
{
unsigned short iFileStartSector;
unsigned short iFileInvalidSector[2048];
}FILE_SECTOR_INFO;


typedef struct 
{
unsigned int iFileNameSector;
unsigned int iFileNamePage;
unsigned int iFileNameAddress;
unsigned int iFileNameIndex;
}FILE_NAME;


typedef struct 
{
unsigned int iFileFolderSector;
unsigned int iFileFolderPage;
unsigned int iFileFolderAddress;
unsigned int iFileFolderIndex;
}FOLDER_NAME;


extern FILES iFiles;
extern FILES iFilesTemp;
extern FILE_SECTOR_INFO iFileSectorInfo;

extern FILE_NAME iFileNameAdd;
extern unsigned short FileNum;
extern FILE_NAME iFileName;
extern FOLDER_NAME iFileFolder;

extern unsigned char FolderName[128];//目录名称
extern unsigned int FileStartSector;

extern unsigned short SectorInUser[2048];
extern unsigned char NameTemp[128];

extern unsigned char BootFolder;

//extern unsigned short sys_tick;


void Nand_Format(void);
//******************************
void Nand_FillPage_SDbuf(unsigned short page,unsigned int length,unsigned char filldata); //填充 sdram块复制区中的一页
void Nand_WritePage_SDbuf(unsigned short page,unsigned int length,unsigned char *wpdata); //从wpdata 写入 sdram块复制区中 一页

extern unsigned char FileOpen(unsigned char *fname,unsigned char *ramadd);
extern unsigned char FileClose(unsigned char *fhandle);
extern unsigned char FileWrite(unsigned char *fhandle,unsigned int length);
extern unsigned char FileRead(unsigned char *fname,unsigned char *ramadd);
extern unsigned char FileFolderRead(unsigned char *str,unsigned char *buff);
extern unsigned char File_CreateStartSector(void); //创建一个起始块用于保存系统参数
extern void File_GetStartSector(void); //读取起始块和坏块

extern unsigned int  File_GetFreeSector_New(void);  //获取可用块//新改动，适用目录
extern unsigned int  File_GetFreeSector(void);  //获取可用块

extern unsigned char File_Delete(unsigned char *fname); //删除一个文件

extern unsigned char File_Create(unsigned char *fname);  //创键一个文件
extern unsigned char File_CreateFolder(unsigned char *fname);  //创键一个文件夹

extern unsigned int File_Find(unsigned char *fname);  //查找一个文件是否存在 返回一个地址
extern unsigned int File_FindFolder(unsigned char *folder);  //查找一个文件夹是否存在 返回一个地址

extern void SaveUnUserSector(void);
extern void LoadUnUserSector(void);

extern void FileWirte_Boot(void);
extern unsigned char FileLoadBootApp(void);    //装载启动APP  返回启动APP顺序
extern void  FileWriteBootApp(unsigned char banum) ;   //装载启动APP
extern void ChangeFileName(unsigned char * name);
extern void ChangeFileName1(unsigned char * name);
#endif 
