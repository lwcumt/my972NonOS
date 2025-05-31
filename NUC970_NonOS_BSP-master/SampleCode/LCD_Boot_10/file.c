#include"file.h"
#include "drv_glcd.h"
//#include "comm.h"


FILES iFiles;
FILES iFilesTemp;
FILE_SECTOR_INFO iFileSectorInfo;
//FILE_NAME iFileName;

FILE_NAME iFileName;
FOLDER_NAME iFileFolder;
FOLDER_NAME iFilesFolderTemp;

unsigned short FileNum;
unsigned char FolderName[128];//目录名称
unsigned int FileStartSector;
unsigned short SectorInUser[2048];
unsigned char NameTemp[128];

unsigned char BootFolder;

//unsigned short sys_tick;





void Nand_Format(void)
{
volatile Int32U block;
Int8U Err_f;
unsigned short *nfiv;
Nf_InvalidCou=0;
nfiv=(unsigned short*)&iFileSectorInfo.iFileInvalidSector;
for(block=0;block<NF_BLOCKS;block++)
   *(nfiv+block)=0xffff;

for(block=0;block<NF_BLOCKS;block++)
  {
 // Err_f=Nand_EraseBlock((block));//*NF_BLOCK_PAGES));
  Err_f=Nand_EraseBlock((block*NF_BLOCK_PAGES));
  if(Err_f==1)
    {
	nfiv[Nf_InvalidCou++]=block;
	}
  }   
  


for(block=42;block<2048;block++)  //后续块未使用
	{
	SectorInUser[block]=UNUSER;
	}

File_CreateStartSector();
}

//******************************
void Nand_FillPage_SDbuf(unsigned short page,unsigned int length,unsigned char filldata)  //填充 sdram块复制区中的一页
{
int i;
unsigned char *pSDbuf;
pSDbuf=(unsigned char *)NF_SECTOR_SDRAM_BUF;
pSDbuf+=(page*FILE_INFO_LENGTH)+(iFileFolder.iFileFolderPage*2048);

for(i=0;i<length;i++)//填充一页
	{
	*pSDbuf++=filldata;
	}
}

void Nand_WritePage_SDbuf(unsigned short page,unsigned int length,unsigned char *wpdata) //从wpdata 写入 sdram块复制区中 一页
{
int i;
unsigned char *pSDbuf;
pSDbuf=(unsigned char *)NF_SECTOR_SDRAM_BUF;
//pSDbuf+=page*FILE_INFO_LENGTH;
pSDbuf+=(page*FILE_INFO_LENGTH)+(iFileFolder.iFileFolderPage*2048);

for(i=0;i<length;i++)//填充一页
	{
	*pSDbuf++=*wpdata++;
	}
}




unsigned char FileOpen(unsigned char *fname,unsigned char *ramadd)
{




}



unsigned char FileClose(unsigned char *fhandle)
{





}



unsigned char FileWrite(unsigned char *fhandle,unsigned int length)
{
int page;
int wpage;
unsigned char *copyptr;
int cblock;

if(length>=NF_PAGE_BYTES)
	wpage=length/NF_PAGE_BYTES;
else 
 wpage=0;

copyptr=(unsigned char *)DOWNFILE_SDRAM_ADD;
cblock=iFiles.FileAddress;

while(1)
	{
	for(page=0;page<NF_PAGE_BYTES;page++)
		{
		Nand_Write_1Page(copyptr,cblock*NF_BLOCK_BYTES+page*NF_PAGE_BYTES);
		copyptr+=NF_PAGE_BYTES;
		if(wpage>0)
			{
			wpage--;
			}
		else
			return 1;
		}
	cblock++;	
	}
}




unsigned char FileRead(unsigned char *fname,unsigned char *ramadd)
{


unsigned int sector;
unsigned int length;
int i=0;
int n=0;
/*
if(fname[i++]=='\\')
	{//带目录访问
	while(fname[i++]!='\\')
		{
		FolderName[i-1]=fname[i-1];
		}
	FolderName[i-1]=0;

	while(fname[i++]!=0)
		{
		fname[n++]=fname[i-1];
		}
	fname[n]=0;

	ChangeFileName(fname);

	}
*/
if(File_Find(fname)==1)
	{//已存在
	sector=iFilesTemp.FileAddress;
	length=iFilesTemp.FileLength;
	Nand_ReadDates(ramadd,sector*NF_BLOCK_BYTES,length);
	//NF_Read(sector*NF_BLOCK_BYTES,length,ramadd);//读取字库
	return 1;
	}
else
	{//文件不存在创建
	
	return 0;
	}
}


unsigned char  FileFolderRead(unsigned char *str,unsigned char *buff)
{
unsigned char fname[128];
int i;
i=0;
if(*str=='\\')   //带目录读
	{
	return FileRead(str,buff);
	}
else
	{
	switch(BootFolder)
		{
		case 1:
			fname[i++]='\\';
			fname[i++]='A';
			fname[i++]='P';
			fname[i++]='P';
			fname[i++]='1';
			fname[i++]='\\';
			while(*str!=0)
			{
			fname[i++]=*str++;
			}
			fname[i]=*str;
			return FileRead(fname,buff);
			break;
		case 2:
			fname[i++]='\\';
			fname[i++]='A';
			fname[i++]='P';
			fname[i++]='P';
			fname[i++]='2';
			fname[i++]='\\';
			while(*str!=0)
			{
			fname[i++]=*str++;
			}
			fname[i]=*str;
			return FileRead(fname,buff);
			break;
		case 3:
			fname[i++]='\\';
			fname[i++]='A';
			fname[i++]='P';
			fname[i++]='P';
			fname[i++]='3';
			fname[i++]='\\';
			while(*str!=0)
			{
			fname[i++]=*str++;
			}
			fname[i]=*str;
			return FileRead(fname,buff);
			break;
		case 4:
			fname[i++]='\\';
			fname[i++]='A';
			fname[i++]='P';
			fname[i++]='P';
			fname[i++]='4';
			fname[i++]='\\';
			while(*str!=0)
			{
			fname[i++]=*str++;
			}
			fname[i]=*str;
			return FileRead(fname,buff);
			break;
		case 5:
			fname[i++]='\\';
			fname[i++]='A';
			fname[i++]='P';
			fname[i++]='P';
			fname[i++]='5';
			fname[i++]='\\';
			while(*str!=0)
			{
			fname[i++]=*str++;
			}
			fname[i]=*str;
			return FileRead(fname,buff);
			break;
		case 6:
			fname[i++]='\\';
			fname[i++]='A';
			fname[i++]='P';
			fname[i++]='P';
			fname[i++]='6';
			fname[i++]='\\';
			while(*str!=0)
			{
			fname[i++]=*str++;
			}
			fname[i]=*str;
			return FileRead(fname,buff);
			break;
		default:
			fname[i++]='\\';
			fname[i++]='A';
			fname[i++]='P';
			fname[i++]='P';
			fname[i++]='1';
			fname[i++]='\\';
			while(*str!=0)
			{
			fname[i++]=*str++;
			}
			fname[i]=*str;
			return FileRead(fname,buff);
			break;
		}
	}
}


unsigned int  File_GetFreeSector_New(void)  //获取可用块//新改动，适用目录
{
unsigned int usesector;//可用块
unsigned int sector;
unsigned int needsector;//文件需要使用的块
unsigned int i;
unsigned char free_flag;

unsigned char *sd;
unsigned int page=0;
unsigned int pagecou;
unsigned int add;
unsigned char filefree_flag=0;
unsigned char *nametemp;

unsigned int oldusesector;
int n;
int fn;


FileNum=0;

//sector=iFileSectorInfo.iFileStartSector;
sector=FileStartSector;

fn=FILE_MAXNUM/(NF_PAGE_BYTES /FILE_INFO_LENGTH);

for(i=0;i<fn;i++)
	{
//	add=sector*NF_BLOCK_BYTES+page*NF_PAGE_BYTES;
          add=sector*NF_BLOCK_BYTES+page*NF_PAGE_BYTES+iFileFolder.iFileFolderPage*2048;
	for(pagecou=0;pagecou< NF_PAGE_BYTES /FILE_INFO_LENGTH;pagecou++)
		{
		sd=(unsigned char*)&iFilesTemp;
//		Nand_ReadDates(sd,add,FILE_INFO_LENGTH);
		Nand_ReadDates(sd,add,128+4+4);
	//	NF_Read(add,FILE_INFO_LENGTH,sd);	
		if(FileNum==0)
			{
			filefree_flag=0;
			}
		else
			{
			filefree_flag=1;
			for(n=0;n<32;n++)
				{
				if(*sd++!=0xff)
					{
					filefree_flag=0;
					break;
					}

				}
			if(filefree_flag==1)
				break;
			}

		FileNum++;
		add+=FILE_INFO_LENGTH;
		}
	if(filefree_flag==1)
		break;
	if(FileNum>=FILE_MAXNUM)
		{
		break;
		}

	page++;
	if(page>=NF_PAGE_BYTES)
		{
		page=0;
		sector++;
		}
	}//for(i=0;i<FILE_MAXNUM;i++) 查找文件名


if(iFiles.FileLength>=NF_BLOCK_BYTES) //取当前要写文件长度
	{
	needsector=iFiles.FileLength;
	needsector/=NF_BLOCK_BYTES;
	}
else
	needsector=0;

needsector++;//需要的块

File_GetStartSector();//读取起始块信息
usesector=FILE_SAVE_SECTOR;
sector=usesector;

//usesector=0;
while(1)
	{
	if(SectorInUser[sector]==UNUSER)
		{
		free_flag=1;
		for(i=0;i<needsector;i++)
			{
			if(SectorInUser[sector+i]!=UNUSER)//跳开被使用的块
				{
				free_flag=0;
				break;
				}
			}
		}

	if(free_flag==1)
		{
		for(i=0;i<needsector;i++)
			{
			if(iFileSectorInfo.iFileInvalidSector[sector+i]!=UNUSER)//跳开坏块
				{
				free_flag=0;
				break;
				}
			}

		if(free_flag==1)
			break;
		}

	sector++;
	if(sector>1024)
		{
		break;
		}
	}


if(free_flag==1)
	{
	for(i=0;i<needsector;i++)
			{
			SectorInUser[sector+i]=0;  //使用块占用
			}
	usesector=sector;
	return usesector;
	}
else
	{
	return 0;
	}
}




unsigned int  File_GetFreeSector(void)  //获取可用块
{
int i;
unsigned char *sd;
unsigned int sector;
unsigned int page=0;
unsigned int pagecou;
unsigned int add;
unsigned char filefree_flag=0;
unsigned char *nametemp;

unsigned int oldusesector;
unsigned int usesector;
int n;
int fn;

FileNum=0;

File_GetStartSector();//读取起始块信息

usesector=FILE_SAVE_SECTOR;

//sector=iFileSectorInfo.iFileStartSector;
sector=FileStartSector;

fn=FILE_MAXNUM/(NF_PAGE_BYTES /FILE_INFO_LENGTH);

for(i=0;i<fn;i++)
	{
	add=sector*NF_BLOCK_BYTES+page*NF_PAGE_BYTES;
	for(pagecou=0;pagecou< NF_PAGE_BYTES /FILE_INFO_LENGTH;pagecou++)
		{
		sd=(unsigned char*)&iFilesTemp;
//		Nand_ReadDates(sd,add,FILE_INFO_LENGTH);
		Nand_ReadDates(sd,add,128+4+4);
	//	NF_Read(add,FILE_INFO_LENGTH,sd);	
		if(FileNum==0)
			{
			filefree_flag=0;
			}
		else
			{
			filefree_flag=1;
			for(n=0;n<32;n++)
				{
				if(*sd++!=0xff)
					{
					filefree_flag=0;
					break;
					}

				}
			if(filefree_flag==1)
				break;
			}

		FileNum++;
		add+=FILE_INFO_LENGTH;
		}
	if(filefree_flag==1)
		break;
	if(FileNum>=FILE_MAXNUM)
		{
		break;
		}

	page++;
	if(page>=NF_PAGE_BYTES)
		{
		page=0;
		sector++;
		}
	}//for(i=0;i<FILE_MAXNUM;i++) 查找文件名



Nf_InvalidCou=0;
while(1)
	{//检测坏块
	if(iFileSectorInfo.iFileInvalidSector[Nf_InvalidCou]==0xffff)
		break;
	Nf_InvalidCou++;
	}


//sector=iFileSectorInfo.iFileStartSector;
sector=FileStartSector;

page=0;
int filenum=FileNum;
if(filefree_flag==1)
	{//有空间
	if(filenum>0)
		{
        filenum--;
		add=sector*NF_BLOCK_BYTES+page*NF_PAGE_BYTES+filenum*FILE_INFO_LENGTH; //读上一个数据
		sd=(unsigned char*)&iFilesTemp;
		Nand_ReadDates(sd,add,128+4+4);
//		Nand_ReadDates(sd,add,FILE_INFO_LENGTH);
	//	NF_Read(add,FILE_INFO_LENGTH,sd);	

		if(filenum==0)
			{
			iFilesTemp.FileLength=1024;
			iFilesTemp.FileAddress=42;
			}

		if(iFilesTemp.FileLength>=NF_BLOCK_BYTES)
			{
			oldusesector=iFilesTemp.FileLength;
			oldusesector/=NF_BLOCK_BYTES;
//			oldusesector=(iFilesTemp.FileLength/NF_BLOCK_BYTES);//计算上一个文件所占用的块
			}
		else
			oldusesector=0;

		oldusesector++;

		usesector=iFilesTemp.FileAddress+oldusesector;//得到当前一个块


		if(iFiles.FileLength>=NF_BLOCK_BYTES) //取当前要写文件长度
			{
			sector=iFiles.FileLength;
			sector/=NF_BLOCK_BYTES;
//			sector=(iFiles.FileLength/NF_BLOCK_BYTES);//计算当前要写文件占用的块
			}
		else
			sector=0;

		sector++;

		if(Nf_InvalidCou>0)
			{
			while(1)
				{
				for(i=0;i<Nf_InvalidCou;i++)
					{
					if(usesector<=iFileSectorInfo.iFileInvalidSector[i])
						{
						usesector=iFileSectorInfo.iFileInvalidSector[i]+1;
						if(usesector==iFileSectorInfo.iFileStartSector) //跳开起始块
							usesector++;
						if((usesector+sector)<iFileSectorInfo.iFileInvalidSector[i+1])
							{
							return usesector; //返回当前可用块	
							}

						}
					else
						{
						if(usesector==iFileSectorInfo.iFileStartSector)//跳开起始块
							usesector++;
						if((usesector+sector)<iFileSectorInfo.iFileInvalidSector[i+1])
							{
							return usesector; //返回当前可用块	
							}
						}
					}			
				}
			}
		else
			return usesector;//返回当前可用块
			
		}
	else
		{//第一个文件
		usesector=FILE_SAVE_SECTOR;
		if(iFiles.FileLength>=NF_BLOCK_BYTES) //取当前要写文件长度
			{
			sector=iFiles.FileLength;
			sector/=NF_BLOCK_BYTES;
//			sector=(iFiles.FileLength/NF_BLOCK_BYTES);//计算当前要写文件占用的块
			}
		else
			sector=0;

		sector++;
                
		if(Nf_InvalidCou>0)
			{
			while(1)
				{
				for(i=0;i<Nf_InvalidCou;i++)
					{
					if(usesector<=iFileSectorInfo.iFileInvalidSector[i])
						{
						usesector=iFileSectorInfo.iFileInvalidSector[i]+1;
						if(usesector==iFileSectorInfo.iFileStartSector)
							usesector++;
						if((usesector+sector)<iFileSectorInfo.iFileInvalidSector[i+1])
							{
							return usesector; //返回当前可用块	
							}

						}
					else
						{
						if(usesector==iFileSectorInfo.iFileStartSector)
							usesector++;
						if((usesector+sector)<iFileSectorInfo.iFileInvalidSector[i+1])
							{
							return usesector; //返回当前可用块	
							}
						}
					}			
				}
			}
		else
			return usesector;//返回当前可用块


		}
	}
else
	{//无空间



	}

}




unsigned int  File_GetFreeFolder(void)  //获取可用块
{
int i;
unsigned char *sd;
unsigned int sector;
unsigned int page=0;
unsigned int pagecou;
unsigned int add;
unsigned char filefree_flag=0;
unsigned char *nametemp;

unsigned int oldusesector;
unsigned int usesector;
int n;
int fn;

FileNum=0;

File_GetStartSector();//读取起始块信息



//usesector=FILE_SAVE_SECTOR;

sector=iFileSectorInfo.iFileStartSector;

//fn=FILE_MAXNUM/(NF_PAGE_BYTES /FILE_INFO_LENGTH);

fn=2;
for(i=0;i<fn*3;i++)
	{
	add=sector*NF_BLOCK_BYTES+page*NF_PAGE_BYTES;
	//for(pagecou=0;pagecou< NF_PAGE_BYTES /FILE_INFO_LENGTH;pagecou++)
		//{
		sd=(unsigned char*)&iFilesTemp;
//		Nand_ReadDates(sd,add,FILE_INFO_LENGTH);
		Nand_ReadDates(sd,add,128+4+4);
	//	NF_Read(add,FILE_INFO_LENGTH,sd);	
		filefree_flag=1;
		for(n=0;n<32;n++)
			{
			if(*sd++!=0xff)
				{
				filefree_flag=0;
				break;
				}

			}
	//	if(filefree_flag==1)
	//		break;

	//	FileNum++;
	//	add+=FILE_INFO_LENGTH;
	//	}
	if(filefree_flag==1)
		break;
	//if(FileNum>=FILE_MAXNUM)
	//	{
	//	break;
	//	}

	page+=20;
	if(page>=60)
		{
		page=0;
		sector++;
		}

		/*
	page++;
	if(page>=NF_PAGE_BYTES)
		{
		page=0;
		sector++;
		}*/
	}//for(i=0;i<FILE_MAXNUM;i++) 查找文件名


iFileFolder.iFileFolderSector=sector;//取对应块
iFileFolder.iFileFolderPage=page;  //取对应页
iFileFolder.iFileFolderAddress=add; //取对应地址
iFileFolder.iFileFolderIndex=i;  //文件所处位置

if(filefree_flag==1)
	{
	return 1;  //找到文件
	}
else
	{
	return 0; //找不到对应文件
	}
}


unsigned char File_CreateStartSector(void) //创建一个起始块用于保存系统参数
{
unsigned short s_sector;
//unsigned int *sd;
unsigned short *nfiv;
int i;
unsigned int x;
//srand(sys_tick);
while(1)
	{
	s_sector=rand();
	s_sector/=NF_PAGE_BYTES;

//	s_sector=rand();
//	s_sector/=64;

	if((s_sector>2)&&(s_sector<32))
		break;
/*
	if(s_sector<NF_BLOCKS) //判断是否为正常的数据块 ，并与坏块判断
		{
		if(Nf_InvalidCou>0)
			{
			for(i=0;i<Nf_InvalidCou;i++)
				{
				if(s_sector==InvalidBlock[i])
					break;

				}
			if(i==Nf_InvalidCou)//与坏块不相等，记录起始块地址
				break;
			}
		else
			break;//无坏块。直接记录起始块地址
		}*/
	}//while(1)


iFileSectorInfo.iFileStartSector=s_sector;
/*
nfiv=(unsigned short *)iFileSectorInfo.iFileInvalidSector;

for(i=0;i<NF_BLOCKS;i++)
	{
	*nfiv++=InvalidBlock[i];
	}*/
x=FILE_INFO_START_SECTOR;
unsigned char *sd=(unsigned char*)&iFileSectorInfo.iFileStartSector;
i=Nand_Write_1Page(sd,x*128*1024); //写入块信息头


SaveUnUserSector();  //保存未使用块

//i=Nand_Write_1Page(sd,(FILE_INFO_START_SECTOR*NF_BLOCK_BYTES+FILE_INFO_PAGE_NUM*NF_PAGE_BYTES)); //写入块信息头

File_GetStartSector();
if(i==1)
	return 1; //写头错误
else
	return 0;//正确

}

void SaveUnUserSector(void)
{
	unsigned int x;
x=FILE_SAVE_UNUSER_SECTOR;

//Nand_EraseBlock((x));//*NF_BLOCK_PAGES));
Nand_EraseBlock((x*NF_BLOCK_PAGES));
unsigned char *sd=(unsigned char*)&SectorInUser;
Nand_Write_1Page(sd,x*128*1024); //写入块信息头

}

void LoadUnUserSector(void)
{
	unsigned int x;
x=FILE_SAVE_UNUSER_SECTOR;
unsigned char *sd=(unsigned char*)&SectorInUser;
Nand_ReadDates(sd,x*128*1024,2048);

}



void File_GetStartSector(void) //读取起始块和坏块
{
unsigned char *sd=(unsigned char*)&iFileSectorInfo.iFileStartSector;
unsigned int x;
////Printf24("目录查找_读取起始块",0,0,0,1,0xf7a2);
x=FILE_INFO_START_SECTOR;
Nand_ReadDates(sd,x*128*1024,2000);
////Printf24("目录查找_装载未使用块",0,0,0,1,0xf7a2);
LoadUnUserSector();
////Printf24("目录查找_完成",0,0,0,1,0xf7a2);

//Nand_ReadDates(sd,FILE_INFO_START_SECTOR*NF_BLOCK_BYTES+FILE_INFO_PAGE_NUM*NF_PAGE_BYTES,2000);

//NF_Read(FILE_INFO_START_SECTOR*NF_BLOCK_BYTES+FILE_INFO_PAGE_NUM*NF_PAGE_BYTES,2048,sd);//读取字库

}


unsigned char File_Delete(unsigned char *fname) //删除一个文件
{
FILE_NAME *fnd;
if(File_Find(fname)==1)//先查找文件是否存在
	{//已存在

	return 1;
	}
else
	{//文件不存在返回
	return 0;

	}
}


unsigned char File_Create(unsigned char *fname)  //创键一个文件
{
 unsigned char nametemp[64];
unsigned char *fnametemp=(unsigned char *)&iFiles.FileName;
unsigned int sector,wsector;
unsigned int startsector;
int i=0;
int n=0;
int filenumtemp;
unsigned char *sd;
unsigned int length;
unsigned char folder=0;

	unsigned char x;
	x=0;
while(fname[x]!=0)
{
  nametemp[x]=fname[x];
  x++;
  
}
  nametemp[x]=fname[x];

i=0;
if(fname[i++]=='\\')
	{//带目录访问
	folder=1;
	while(fname[i++]!='\\')
		{
		FolderName[n++]=fname[i-1];
		}
	FolderName[n]=0;
        n=0;
	while(fname[i++]!=0)
		{
		NameTemp[n++]=fname[i-1];
		}
	NameTemp[n]=0;

	length=iFiles.FileLength;
	//iFiles.FileLength=1024;
//	ChangeFileName(fname); //转换名称
	//Printf24("创建目录",0,0,0,1,0xf7a2);
	File_CreateFolder(FolderName);//创建目录
	File_FindFolder(FolderName);
	startsector=iFileFolder.iFileFolderSector;//获取目录块地址
	FileStartSector=startsector;
	iFiles.FileLength=length;
		
	//Printf24("文件名称",0,0,0,1,0xf7a2);
	n=0;
	while(NameTemp[n]!=0)
		{
		iFiles.FileName[n]=NameTemp[n];
		n++;
		}
	iFiles.FileName[n]=NameTemp[n];
	
	}
else
	{//	
	File_GetStartSector();//读取起始块信息
	startsector=iFileSectorInfo.iFileStartSector+2;//无目录文件起始块
	FileStartSector=startsector;
    length=iFiles.FileLength;
	iFileFolder.iFileFolderPage=0;
	}


//Printf24("是否有文",0,0,0,1,0xf7a2);
fnametemp=(unsigned char *)&iFiles.FileName;

if(File_Find((unsigned char *)nametemp)==1)
	{//已存在更新
		//Printf24("已有文件",0,0,0,1,0xf7a2);
         // iFiles.FileAddress=iFilesTemp.FileAddress;
		if(iFilesTemp.FileLength>=NF_BLOCK_BYTES)
				{
				sector=iFilesTemp.FileLength;
				sector/=NF_BLOCK_BYTES;
				}
		else
				sector=0;

		sector++;

		for(i=0;i<sector;i++)
			{
			SectorInUser[i+iFilesTemp.FileAddress]=UNUSER;  //清除块占用
			}


		SaveUnUserSector();


		filenumtemp=FileNum;
	//	iFiles.FileAddress=File_GetFreeSector_New();//iFilesTemp.FileAddress;//获取可用块
	//	if(iFiles.FileAddress>=42)
	//		{
	
		iFiles.FileAddress=File_GetFreeSector_New();//iFilesTemp.FileAddress;//获取可用块

                FileNum=filenumtemp;
		Nand_ReadBlock(startsector,(unsigned char *)NF_SECTOR_SDRAM_BUF);//读取 文件name信息
	//	sector=startsector;
		//Nand_EraseBlock((sector));//*NF_BLOCK_PAGES));
		Nand_EraseBlock((startsector*NF_BLOCK_PAGES));
		Nand_FillPage_SDbuf(FileNum,FILE_INFO_LENGTH,0xff); //删除原有的信息 包括文件名、长度，地址  跳出目录块
              // 
                Nand_WritePage_SDbuf(FileNum,FILE_INFO_LENGTH,fnametemp);
		Nand_WriteBlock(startsector,(unsigned char *)NF_SECTOR_SDRAM_BUF);	

		
	//	sd=(unsigned char*)&iFilesTemp;
	//	Nand_ReadDates(sd,iFileName.iFileNameAddress,FILE_INFO_LENGTH);


		

		/*	if(iFiles.FileLength>=NF_BLOCK_BYTES)
				{
				sector=iFiles.FileLength;
				sector/=NF_BLOCK_BYTES;
				}
			else
				sector=0;
			sector++;*/

			wsector=iFiles.FileAddress;
			for(i=0;i<sector;i++)
				{
				//Nand_EraseBlock(((wsector+i)));//*NF_BLOCK_PAGES));
				Nand_EraseBlock(((wsector+i)*NF_BLOCK_PAGES));
				}
			FileWrite(0,iFiles.FileLength);
			
		//	File_GetStartSector();
			SaveUnUserSector();
		//	}
	}
else
	{//文件不存在创建
		//Printf24("新建文件",0,0,0,1,0xf7a2);
	iFiles.FileLength=length;
//	if(folder==1)
		iFiles.FileAddress=File_GetFreeSector_New();//File_GetFreeSector();//获取可用块
	//else
	//	iFiles.FileAddress=File_GetFreeSector();//File_GetFreeSector();//获取可用块
	if(iFiles.FileAddress>=42)
		{
		//Printf24("保存未块",0,0,0,1,0xf7a2);
		SaveUnUserSector();
		//Printf24("读取起块",0,0,0,1,0xf7a2);
    File_GetStartSector();//读取起始块信息
		//Printf24("读取信息",0,0,0,1,0xf7a2);
			
		Nand_ReadBlock(startsector,(unsigned char *)NF_SECTOR_SDRAM_BUF);//读取 文件name信息
		sector=startsector;
             //   Nand_EraseBlock((sector));//*NF_BLOCK_PAGES));      
		//Printf24("删除信块",0,0,0,1,0xf7a2);			
		Nand_EraseBlock((sector*NF_BLOCK_PAGES));
		Nand_FillPage_SDbuf(FileNum,FILE_INFO_LENGTH,0xff); //删除原有的信息 包括文件名、长度，地址
		Nand_WritePage_SDbuf(FileNum,FILE_INFO_LENGTH,fnametemp);
		File_GetStartSector();//读取起始块信息

	    Nand_WriteBlock(startsector,(unsigned char *)NF_SECTOR_SDRAM_BUF);     
	    Nand_ReadBlock(startsector,(unsigned char *)NF_SECTOR_SDRAM_BUF);//读取 文件name信息
        
		File_GetStartSector();//读取起始块信息
		
		if(iFiles.FileLength>=NF_BLOCK_BYTES)
			{
			sector=iFiles.FileLength;
			sector/=NF_BLOCK_BYTES;
			}
		else
			sector=0;
		sector++;
		wsector=iFiles.FileAddress;
		for(i=0;i<sector;i++)
			{
			//Nand_EraseBlock(((wsector+i)));//*NF_BLOCK_PAGES));
			Nand_EraseBlock(((wsector+i)*NF_BLOCK_PAGES));
			}

		File_GetStartSector();//读取起始块信息
		//Printf24("写入长度",0,0,0,1,0xf7a2);
		FileWrite(0,iFiles.FileLength);
		
		File_GetStartSector();//读取起始块信息
		}
	}
}


unsigned char File_CreateFolder(unsigned char *fname)  //创键一个文件夹
{

unsigned char *nametemp;
unsigned char *fnametemp=(unsigned char *)&iFiles.FileName;
unsigned int sector,wsector;
int i=0;
int n=0;
/*
if(fname[i++]=='\\')
	{//带目录访问
	while(fname[i++]!='\\')
		{
		FolderName[i-1]=fname[i-1];
		}
	FolderName[i-1]=0;

	while(fname[i++]!=0)
		{
		fname[n++]=fname[i-1];
		}
	fname[n]=0;
	ChangeFileName(fname);
	}
*/
ChangeFileName(fname);


fnametemp=(unsigned char *)&iFiles.FileName;

if(File_FindFolder(fname)==1)
	{//已存在更新
	/*
	Nand_ReadBlock(iFileName.iFileNameSector,(unsigned char *)NF_SECTOR_SDRAM_BUF);//读取 文件name信息
	sector=iFileName.iFileNameSector;
	Nand_EraseBlock((sector*NF_BLOCK_PAGES));
	Nand_FillPage_SDbuf(FileNum,FILE_INFO_LENGTH,0xff); //删除原有的信息 包括文件名、长度，地址
	iFiles.FileAddress=iFilesTemp.FileAddress;//获取可用块
	Nand_WritePage_SDbuf(FileNum,FILE_INFO_LENGTH,fnametemp);
	Nand_WriteBlock(iFileName.iFileNameSector,(unsigned char *)NF_SECTOR_SDRAM_BUF);
	if(iFilesTemp.FileLength>=NF_BLOCK_BYTES)
		{
		sector=iFilesTemp.FileLength;
		sector/=NF_BLOCK_BYTES;
		}
	else
		sector=0;
	sector++;
	wsector=iFiles.FileAddress;
	for(i=0;i<sector;i++)
		{
		Nand_EraseBlock(((wsector+i)*NF_BLOCK_PAGES));
		}
	FileWrite(0,iFiles.FileLength);*/
	}
else
	{//文件夹不存在创建
	File_GetStartSector();//读取起始块信息
	if(File_GetFreeFolder()==1)//有空间
		{
		Nand_ReadBlock(iFileFolder.iFileFolderSector,(unsigned char *)NF_SECTOR_SDRAM_BUF);//读取 文件name信息
		//
		sector=iFileFolder.iFileFolderSector;
		
		//Nand_EraseBlock((sector));//*NF_BLOCK_PAGES));
		Nand_EraseBlock((sector*NF_BLOCK_PAGES));
		Nand_FillPage_SDbuf(0,FILE_INFO_LENGTH,0xff); //删除原有的信息 包括文件名、长度，地址
		Nand_WritePage_SDbuf(0,FILE_INFO_LENGTH,fnametemp);


		Nand_WriteBlock(iFileFolder.iFileFolderSector,(unsigned char *)NF_SECTOR_SDRAM_BUF);     
		Nand_ReadBlock(iFileFolder.iFileFolderSector,(unsigned char *)NF_SECTOR_SDRAM_BUF);//读取 文件name信息
		}     
	}
}



unsigned int File_Find(unsigned char *fname)  //查找一个文件是否存在 返回一个地址
{
int i;
unsigned char *sd;
unsigned short sector;
unsigned short page=0;
unsigned short pagecou;
unsigned int add;
unsigned char namematch_flag=0;
 unsigned char *nametemp;
int fn;
//int FileNum=0;



//unsigned char *nametemp;
unsigned char *fnametemp=(unsigned char *)&iFiles.FileName;
unsigned int wsector;
unsigned int startsector;
unsigned int length;
//int i=0;
int n=0;
i=0;
if(fname[i++]=='\\')
	{//带目录访问
	//Printf24("分离目录",0,0,0,1,0xf7a2);
	while(fname[i++]!='\\')
		{
		FolderName[n]=fname[i-1];
			n++;
		}
	FolderName[n]=0;

	//Printf24("分离文件",0,0,0,1,0xf7a2);
  n=0;
	while(fname[i++]!=0)
		{
		fname[n]=fname[i-1];
		n++;
		}
	fname[n]=0;

	length=iFiles.FileLength;
	//iFiles.FileLength=1024;
//	ChangeFileName(fname); //转换名称
	//File_CreateFolder(FolderName);//创建目录
//	File_FindFolder(FolderName);
//startsector=iFileFolder.iFileFolderSector;//获取目录块地址
//	FileStartSector=startsector;
	//Printf24("转换名称",0,0,0,1,0xf7a2);

//	iFiles.FileLength=0;
	ChangeFileName(fname); //转换名称
//	File_CreateFolder(FolderName);//创建目录
		//Printf24("查找目录",0,0,0,1,0xf7a2);
	if(File_FindFolder(FolderName)==1)
		{
			//Printf24("目录存在",0,0,0,1,0xf7a2);
		startsector=iFileFolder.iFileFolderSector;//获取目录块地址
		FileStartSector=startsector;
		iFiles.FileLength=length;
		}
	else
		{
		//Printf24("没有目录",0,0,0,1,0xf7a2);
		iFiles.FileLength=length;
		return 0;//找不到文件
		File_GetStartSector();//读取起始块信息
		startsector=iFileSectorInfo.iFileStartSector+2;//无目录文件起始块
		}
	}
else
	{//	
	File_GetStartSector();//读取起始块信息
	startsector=iFileSectorInfo.iFileStartSector+2;//无目录文件起始块
	FileStartSector=startsector;
        length=iFiles.FileLength;
		iFileFolder.iFileFolderPage=0;
	}



File_GetStartSector();//读取起始块信息

FileNum=0;//文件计数清零

sector=startsector;//iFileSectorInfo.iFileStartSector;

fn=FILE_MAXNUM/(NF_PAGE_BYTES /FILE_INFO_LENGTH);
//Printf24("开始查找",0,0,0,1,0xf7a2);
for(i=0;i<fn;i++)
	{
	add=sector*NF_BLOCK_BYTES+page*NF_PAGE_BYTES+iFileFolder.iFileFolderPage*2048;
	for(pagecou=0;pagecou< NF_PAGE_BYTES /FILE_INFO_LENGTH;pagecou++)
		{
		sd=(unsigned char*)&iFilesTemp;
		Nand_ReadDates(sd,add,128+4+4);
//		Nand_ReadDates(sd,add,FILE_INFO_LENGTH);
		//NF_Read(add,FILE_INFO_LENGTH,sd);	
//		sd=(unsigned char*)&filetemp->FileName;
		nametemp=(unsigned char *)fname;
		if(FileNum==0)
			{
			namematch_flag = 0; 
			}
		else
			{
		namematch_flag = 1; 
		while(*nametemp!=0)
			{
			if(*nametemp++ != *sd++)
				{
				namematch_flag = 0; 
				break;
				}
			}
		if(namematch_flag==1)
			break;
			}
		FileNum++;
		add+=FILE_INFO_LENGTH;
		}

	if(namematch_flag==1)
		break;

	if(FileNum>=FILE_MAXNUM)
		{
	//	FileNum=1;
		break;
		}

	page++;
	//if((page%20)==0)
	//	{
		//FileNum=0;
		//}
	if(page>=NF_PAGE_BYTES)
		{
		page=0;
		sector++;
		}
	}//for(i=0;i<FILE_MAXNUM;i++) 查找文件名

iFileName.iFileNameSector=sector;//取对应块
iFileName.iFileNamePage=page;  //取对应页
iFileName.iFileNameAddress=add; //取对应地址
iFileName.iFileNameIndex=i;  //文件所处位置

if(namematch_flag==1)
	{
	return 1;  //找到文件
	}
else
	{
	return 0; //找不到对应文件
	}
}




unsigned int File_FindFolder(unsigned char *folder)  //查找一个文件夹是否存在 返回一个地址
{
int i;
unsigned char *sd;
unsigned short sector;
unsigned short page=0;
unsigned short pagecou;
unsigned int add;
unsigned char namematch_flag=0;
 unsigned char *nametemp;
int fn;
//int FileNum=0;
		//Printf24("                     ",0,0,0,1,0xf7a2);
//Printf24("目录查找进入",0,0,0,1,0xf7a2);
File_GetStartSector();//读取起始块信息
		//Printf24("                     ",0,0,0,1,0xf7a2);
//Printf24("目录查找读取起始志信息",0,0,0,1,0xf7a2);
FileNum=0;//文件计数清零

sector=iFileSectorInfo.iFileStartSector;

fn=FILE_MAXNUM/(NF_PAGE_BYTES /FILE_INFO_LENGTH);
fn=2;//共可建6个目录，可以供6个APP 
for(i=0;i<fn*3;i++)
	{
	add=sector*NF_BLOCK_BYTES+page*NF_PAGE_BYTES;
	//for(pagecou=0;pagecou< NF_PAGE_BYTES /FILE_INFO_LENGTH;pagecou++)
	//	{
		sd=(unsigned char*)&iFilesTemp;
			//Printf24("                     ",0,0,0,1,0xf7a2);
		//Printf24("目录查找读取NAND",0,0,0,1,0xf7a2);
		Nand_ReadDates(sd,add,128+4+4);
//		Nand_ReadDates(sd,add,FILE_INFO_LENGTH);
			//Printf24("                     ",0,0,0,1,0xf7a2);
		//Printf24("目录查找是否匹配",0,0,0,1,0xf7a2);
		nametemp=(unsigned char *)folder;
		namematch_flag = 1; 
		while(*nametemp!=0)
			{
			if(*nametemp++ != *sd++)
				{
				namematch_flag = 0; 
				break;
				}
			}
		if(namematch_flag==1)
			break;
	//	FileNum++;
	//	add+=FILE_INFO_LENGTH;
	//		}

	if(namematch_flag==1)
		break;

	//if(FileNum>=FILE_MAXNUM)
		//{
	//	break;
	//	}
	
	page+=20; //每个目录占用20页  3个目录占用一个块 
	if(page>=60)
		{
		page=0;
		sector++;
		}

	/*
	page++;
	if(page>=NF_PAGE_BYTES)
		{
		page=0;
		sector++;
		}
		*/
	}//for(i=0;i<FILE_MAXNUM;i++) 查找文件名

iFileFolder.iFileFolderSector=sector;//取对应块
iFileFolder.iFileFolderPage=page;  //取对应页
iFileFolder.iFileFolderAddress=add; //取对应地址
iFileFolder.iFileFolderIndex=i;  //文件所处位置
	//Printf24("                     ",0,0,0,1,0xf7a2);
//Printf24("目录查找完毕",0,0,0,1,0xf7a2);
if(namematch_flag==1)
	{
	return 1;  //找到文件
	}
else
	{
	return 0; //找不到对应文件
	}
}



void FileWirte_Boot(void)
{
unsigned short*wrbuff16;
unsigned short tmp16,tmp16i;
unsigned short wbbuf[2048];
unsigned char *dptr;

Int32U ptw,p;

Nand_EraseBlock(((0*NF_BLOCK_PAGES)));//擦除0块
Nand_EraseBlock(((1*NF_BLOCK_PAGES)));//擦除1块

/* Setup FLASH config See UM10326 section 2.2.3.2 */

wrbuff16=(Int16U*)&wbbuf;//iFileSectorInfo.iFileInvalidSector;//.iFilesTempTemp1;
for(p=0;p<2048;p++)
	wrbuff16[p]=0;


  tmp16 = 0x00; /* 16-Bit NAND still not supported */

    tmp16 |= 1 << 2;
	/*
    if (geom.address_cycles > 4)
    {
      tmp16 |= 1 << 1;
    }

	*/

  tmp16 |= (~tmp16 & 0x0F) << 4;
  tmp16i = 0xFF - tmp16;
  wrbuff16[0] = tmp16;
  wrbuff16[2] = tmp16i;
  wrbuff16[4] = tmp16;
  wrbuff16[6] = tmp16i;

  ptw = CommFileLenth / NF_PAGE_BYTES;
  if ((ptw *NF_PAGE_BYTES) < CommFileLenth)
  {
	ptw++;
  }
  ptw++; /* Include non-used sector */

  tmp16 = (Int16U) ptw;
  tmp16i = 0x00FF - tmp16;
  wrbuff16[8] = tmp16;
  wrbuff16[10] = tmp16i;
  wrbuff16[12] = tmp16;
  wrbuff16[14] = tmp16i;
  wrbuff16[16] = tmp16;
  wrbuff16[18] = tmp16i;
  wrbuff16[20] = tmp16;
  wrbuff16[22] = tmp16i;
  wrbuff16[24] = 0x00AA; /* Good block marker for page #0 ICR only */

  Nand_Write_1Page((unsigned char*)&wbbuf,0);//iFileSectorInfo.iFileInvalidSector, 0);//写入ICR

//  unsigned char *block_inf=(unsigned char*)&wbbuf;//iFileSectorInfo.iFileInvalidSector;

//Nand_Read_1page(block_inf, 0);//读一页 块信息

dfPtr=(unsigned char *)(DOWNFILE_SDRAM_ADD);
for(p=1;p<ptw;p++)
	{
	Nand_Write_1Page(dfPtr, p);//写入BOOT
	dfPtr+=NF_PAGE_BYTES;
	}	


//Nand_Read_1page(block_inf, 1);//读一页 块信息

  Nand_Write_1Page((unsigned char*)&wbbuf, 0+64);//写入ICR

dfPtr=(unsigned char *)(DOWNFILE_SDRAM_ADD);
for(p=1;p<ptw;p++)
	{
	Nand_Write_1Page(dfPtr, p+64);//写入BOOT
	dfPtr+=NF_PAGE_BYTES;
	}	


//block_inf=(unsigned char*)&wbbuf;//iFileSectorInfo.iFileInvalidSector;

//Nand_Read_1page(block_inf, 1+64);//读一页 块信息
}



unsigned char FileLoadBootApp(void)    //装载启动APP  返回启动APP顺序
{

unsigned char *bap;
bap=(unsigned char*)DOWNFILE_SDRAM_ADD;
 FileRead("AppStartFile.ini",bap);
return bap[0];
}

void  FileWriteBootApp(unsigned char banum)    //装载启动APP
{
unsigned char *bap;
bap=(unsigned char *)DOWNFILE_SDRAM_ADD;
*bap=banum;

	iFiles.FileLength=1;
	ChangeFileName("AppStartFile.ini");
	NandEccWrite_Flag=0;
	File_Create(iFiles.FileName);//建立文件
}



void ChangeFileName(unsigned char * name)
{
		//		dfPtr=(unsigned char *)DOWNFILE_SDRAM_ADD;
				unsigned char *ifiles=(unsigned char *)iFiles.FileName;

				//GLCD_Buffer_Fill(BLUE_COLOR);
                               // int n;
                              //  for(n=0;n<CommFileLenth;n++)
                             //   {
                            //     *ifiles++=*dfPtr++; 
                             //   }

				while(*name!=0)
					{
					*ifiles++=*name++;
					}//*/
				 *ifiles=0;
				

		//		FileRead("字库_0x20000.FON",(unsigned char *)df_zk_sdram);
		//		//Printf24("下载....",400,350,0,1,0xf7a2);
		//		Printf24(iFiles.FileName,350,300,0,1,0xf7a2);

}

void ChangeFileName1(unsigned char * name)
{
		//		dfPtr=(unsigned char *)DOWNFILE_SDRAM_ADD;
				unsigned char *ifiles=(unsigned char *)iFiles.FileName;

				//GLCD_Buffer_Fill(BLUE_COLOR);
                               // int n;
                              //  for(n=0;n<CommFileLenth;n++)
                             //   {
                            //     *ifiles++=*dfPtr++; 
                             //   }
				
				name++;
				name++;
				//*name='\\';
				while(*name!=0)
					{
					*ifiles++=*name++;
					}//*/
				 *ifiles=0;
                 ifiles=(unsigned char *)iFiles.FileName;
                                *ifiles='\\';

		//		FileRead("字库_0x20000.FON",(unsigned char *)df_zk_sdram);
		//		//Printf24("下载....",400,350,0,1,0xf7a2);
		//		Printf24(iFiles.FileName,350,300,0,1,0xf7a2);

}
