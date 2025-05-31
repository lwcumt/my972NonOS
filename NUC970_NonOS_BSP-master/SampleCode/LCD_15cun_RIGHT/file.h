/*
文件系统头





*/





#ifndef _FILE_NEWSTRUCT_H
#define _FILE_NEWSTRUCT_H


//#include<stdlib.h>
#include "main.h"

#include "file.h"


#include"nandflash.h"


//#define NAND_FREE 0xffff    //页为空标志数据


#define FILE_INFO_START_PAGE      0//10   //第十页
#define FILE_INFO_LENGTH          256  //文件信息长度

#define FILE_INFO_NUMS_1PAGE          (NF_PAGE_BYTES/FILE_INFO_LENGTH)  //页文件信息 个数	8


//#define FILE_NAME_LENGTH          128

#define FILE_MAXNUM    128  //最大文件数

// #define FILE_NUMS                 128  //最大文件数
// #define FILE_START_SECTOR          10 +FILE_INFO_START_SECTOR//从第十块开始写文件

#define FILE_FOLD_MAX		6//6个文件夹
#define FILE_FOLD_PAGES		((FILE_MAXNUM/FILE_INFO_NUMS_1PAGE)+4)	//=20  1个文件夹20页



#define FILE_SAVE_UNUSER_SECTOR (FILE_INFO_START_SECTOR+5)
#define FILE_SAVE_BOOTAPP_SECTOR  (FILE_INFO_START_SECTOR+8)
#define FILE_SAVE_SECTOR  (10+FILE_INFO_START_SECTOR) //从第十块开始写文件

#define UNUSER 0xffff

#define INUSER 0


//************sdram 文件缓冲区
#define NF_SECTOR_SDRAM_BUF      0x80800000//(SDRAM0_BASE_ADDR+0x180000) //nand块 sdram缓冲区 0x81300000//

#define DOWNFILE_SDRAM_ADD       (NF_SECTOR_SDRAM_BUF+0x100000)  //下载文件的buf地址





//#define FILE_DEBUG_ON 


#define TYPE_INFO 0x01   //信息头类型
#define TYPE_DIR 0x02    //目录类型
#define TYPE_FILE 0x03   //文件类型

#define SECTOR_USER 0xAAAA    
#define SECTOR_NOUSER 0x5555

#define SECTOR_BAD_USER 0xAA55


#define SECTOR_BAD 0xAAAA
#define SECTOR_OK  0x5555


#define FILE_INFO_START_SECTOR     32//信号块号码
#define FILE_DIR_START_SECTOR      48  //目录开始块
#define FILE_FILE_START_SECTOR     64 //文件从第64块开始保存


#define MAX_BAD_SECTOR_COUNT  16	//最大坏连接坏块数量

#define MAX_SECTOR   2048

extern uint32_t NAND_Blocks;
extern uint32_t 	File_Write_Cou;


typedef union 
{
unsigned char fName512[256];
struct 
	{
	uint8_t FileType;		//类型 
	char FileName[128]; //文件名
	uint32_t FileLength; //文件长度
	uint32_t FileSectorAddr;//文件所在块地址
	};
}FILES_N;



typedef union 
{
unsigned char dirName512[512];
 struct
{
uint8_t FileType;
char DirName[128];
int FileNum;
uint32_t StartSectorAddr;	
uint32_t EndSectorAddr;	
	
};
}FILE_FOLDER;



typedef struct
{
uint8_t FileType;
uint16_t  BadSector[2048];   //坏块记录缓存
uint16_t UserSector[2048];  //使用的块记录缓存
uint16_t StartSectorAddr;	 //超始块地址
}SECTOR_INFO;

extern FILES_N nFiles;
extern SECTOR_INFO Sector_Info;

extern FILE_FOLDER File_Folder;




typedef union 
{
unsigned char fName256[256];
struct
	{
	unsigned char FileName[128];
	unsigned int FileLength;
	unsigned int FileAdd_Sector;//
// unsigned char FileTempBuf[16];	
	};
}FILES;



typedef struct 
{
unsigned short iFileSectorTable;
unsigned short iFileStartSector;
unsigned short iFileInvalidSector[1024];
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

extern unsigned char *FolderName;//目录名称
extern unsigned int FileStartSector;

extern unsigned short SectorInUser[1024];
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
extern unsigned char FileRead(char *fname,unsigned char *ramadd);
extern unsigned char FileFolderRead(unsigned char *str,unsigned char *buff);
extern unsigned char File_CreateStartSector(void); //创建一个起始块用于保存系统参数
extern void File_GetSectorTable(void); //读取起始块和坏块

extern unsigned int  File_GetFreeSector_New(void);  //获取可用块//新改动，适用目录
extern unsigned int  File_GetFreeSector(void);  //获取可用块

extern unsigned char File_Delete(unsigned char *fname); //删除一个文件

extern unsigned char File_Create( char *fname);  //创键一个文件
extern unsigned int File_CreateFolder( char *fname);  //创键一个文件夹

extern unsigned int File_Find(char *fname);  //查找一个文件是否存在 返回一个地址
extern unsigned int File_FindFolder(char *folder);  //查找一个文件夹是否存在 返回一个地址

extern void SaveUnUserSector(void);
extern void LoadUnUserSector(void);

extern void FileWirte_Boot(void);
extern unsigned char FileLoadBootApp(void);    //装载启动APP  返回启动APP顺序
extern void  FileWriteBootApp(unsigned char banum) ;   //装载启动APP
extern void ChangeFileName(unsigned char * name);
extern void ChangeFileName1(unsigned char * name);


//初始化
void File_Init(void);

void File_Test(void);

//新加的函数

//*************************************************
//保存 信息头
int  Save_Sector_Info(void);

//*************************************************
//调入 信息头
int Load_Sector_Info(void);

 //获取FREE SECTOR 
 int File_GetFreeSector_N(unsigned int flen);
void File_Debug(char *str,uint8_t flag);

#endif 
