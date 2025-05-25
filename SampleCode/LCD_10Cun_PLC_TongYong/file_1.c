
#include "file.h"

#include "timer.h"



FILES iFiles;
FILES iFilesTemp;
FILE_STORE_INFO iFileSectorInfo;
FILE_NAME iFileName;

unsigned short FileNum;


void Nand_Format(void)
{
volatile Int32U block;
Int8U Err_f;
Nf_InvalidCou=0;

for(block=0;block<NF_BLOCKS;block++)
   InvalidBlock[block]=0xffff;

for(block=0;block<NF_BLOCKS;block++)
  {
  Err_f=Nand_EraseBlock(block);
  if(Err_f==1)
    {
	InvalidBlock[Nf_InvalidCou++]=block;
	}
  }   
  
File_CreateStartSector();
}

//******************************
void Nand_FillPage_SDbuf(unsigned short page,unsigned int length,unsigned char filldata)  //填充 sdram块复制区中的一页
{
int i;
unsigned char *pSDbuf;
pSDbuf=(unsigned char *)NF_SECTOR_SDRAM_BUF;
pSDbuf+=page*FILE_INFO_LENGTH;

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
pSDbuf+=page*FILE_INFO_LENGTH;

for(i=0;i<length;i++)//填充一页
	{
	*pSDbuf++=*wpdata++;
	}
}

//------------99999999999999999999999999999999999999999999
void Nand_FillFileInfo_SDbuf(unsigned short num,unsigned int length,unsigned char filldata)  //填充 sdram块复制区中的一页
{
int i,page,add;
unsigned char *pSDbuf;
Int16U page_offset;
pSDbuf=(unsigned char *)NF_SECTOR_SDRAM_BUF;

page=num/FILE_INFO_NUMS_1PAGE;
page_offset=num%FILE_INFO_NUMS_1PAGE;
add=page*NF_PAGE_BYTES+page_offset*FILE_INFO_LENGTH;
pSDbuf+=add;
for(i=0;i<length;i++)//填充一页
	{
	*pSDbuf++=filldata;
	}
}
void Nand_WriteFileInfo_SDbuf(unsigned short num,unsigned int length,unsigned char *wpdata) //从wpdata 写入 sdram块复制区中 一页
{
int i,page,add;
unsigned char *pSDbuf;
Int16U page_offset;
pSDbuf=(unsigned char *)NF_SECTOR_SDRAM_BUF;

page=num/FILE_INFO_NUMS_1PAGE;
page_offset=num%FILE_INFO_NUMS_1PAGE;
add=page*NF_PAGE_BYTES+page_offset*FILE_INFO_LENGTH;
pSDbuf+=add;
for(i=0;i<length;i++)//填充一页
	{
	*pSDbuf++=*wpdata++;
	}
}



unsigned char FileWrite(FILES file,  unsigned char *pSDbuf)//从  pSDbuf  缓存开始写入 nand
{
int b,block_add;
int p,page_add;
int block_sum=0;
int page_sum=0;
int length;
unsigned char s=0;

//***********文件大小
length=file.FileLength;
block_sum=length>>NF_BLOCK_BITS;
page_sum=length>>NF_PAGE_BITS;
//*********文件地址 起始 块，页  
block_add=file.FileAdd_Sector;
page_add=block_add*NF_BLOCK_PAGES;

//***************先擦除块
for(b=0;b<=block_sum;b++)
	{
	s=Nand_EraseBlock(block_add++);//擦除一块
	//if(s==1)
	//	break;
	}
//if(s==1) return s;	
//*************再写入页
for(p=0;p<=page_sum;p++)
	{
	s=Nand_Write_1Page(pSDbuf, page_add++);//写一页
	pSDbuf+=NF_PAGE_BYTES;
	if(s==1)
		break;
	}	
return s;
}

unsigned char FileRead(unsigned char *fname,unsigned char *buf)//读取文件到sdbuf
{
unsigned int fileAdd;
unsigned int filePage;
unsigned int length;
//unsigned char ram[NF_PAGE_BYTES];

if(File_Find(fname)==1)
	{//已存在
	length=iFilesTemp.FileLength;
	fileAdd=iFilesTemp.FileAdd_Sector<<NF_BLOCK_BITS;
	Nand_ReadDates(buf,fileAdd,length);
	/*
	filePage=iFilesTemp.FileAdd_Sector*NF_BLOCK_PAGES;
	while(length>0)
	   {
	    Nand_Read_1page(ram,filePage++);
	    if(length<NF_PAGE_BYTES)
	      {
		  memcpy(buf,ram,length);
		  length=0;
		  }
	    else
	      {
		  memcpy(buf,ram,NF_PAGE_BYTES);
		  length-=NF_PAGE_BYTES;
		  buf+=NF_PAGE_BYTES;
		  }
	   }*/
	return 1;
	}
else
	{//文件不存在创建
	return 0;
	}
}

unsigned int  File_GetFreeSector(void)  //获取可用块区域 首地址sector
{
int i;
unsigned char *f_buf;
unsigned int sector;
unsigned int page=0;
unsigned int f_num;
unsigned int n_add;
unsigned char filefree_flag=0;
unsigned char *nametemp;

unsigned int oldusesector=0;
unsigned int usesector;
int n;
int info_pages;

FileNum=0;

File_GetStartSector();//读取起始块信息

//usesector=FILE_START_SECTOR;
usesector=0;//+++++++++++++++++++++

sector=iFileSectorInfo.iFileStartSector;

info_pages=FILE_NUMS/FILE_INFO_NUMS_1PAGE;

for(i=0;i<info_pages;i++)     //读所有文件信息
	{
	n_add=sector*NF_BLOCK_BYTES+page*NF_PAGE_BYTES;
	for(f_num=0;f_num< FILE_INFO_NUMS_1PAGE;f_num++)//读一页文件信息
		{
		f_buf=(unsigned char*)&iFilesTemp;
		//NF_Read(n_add,FILE_INFO_LENGTH,f_buf);	
		Nand_ReadDates(f_buf,n_add,FILE_INFO_LENGTH);//读取一个文件信息
		filefree_flag=1;
		for(n=0;n<32;n++)
			{
			if(*f_buf++!=0xff)            //信息域已有文件（非空）    ....继续查找
				{
				filefree_flag=0;
				break;
				}
			}
		if(filefree_flag==1)
			break;

		FileNum++;
		n_add+=FILE_INFO_LENGTH;
		}
	if(filefree_flag==1)
		break;
	if(FileNum>=FILE_NUMS)
		{
		break;
		}
	page++;
	if(page>=NF_BLOCK_PAGES)//执行不到------------文件名信息只有16 page，不满一块
		{
		page=0;
		sector++;
		}
	}

Nf_InvalidCou=0;
while(1)
	{//检测坏块
	if(iFileSectorInfo.iFileSectorTable[Nf_InvalidCou]==0xffff)  //计算坏块个数
		break;
	Nf_InvalidCou++;
	}

sector=iFileSectorInfo.iFileStartSector;
page=0;
int filenum=FileNum;
if(filefree_flag==1)
	{//有空间
	if(filenum>0)
		{
        filenum--;
		n_add=sector*NF_BLOCK_BYTES+page*NF_PAGE_BYTES+filenum*FILE_INFO_LENGTH; //读上一个文件 信息
		f_buf=(unsigned char*)&iFilesTemp;
		Nand_ReadDates(f_buf,n_add,FILE_INFO_LENGTH);

		oldusesector=iFilesTemp.FileLength>>NF_BLOCK_BITS;//  计算上一个文件所占用的块 FileLength/NF_BLOCK_BYTES
		oldusesector++;
		usesector=iFilesTemp.FileAdd_Sector+oldusesector;//得 当前文件的块

		sector=iFiles.FileLength>>NF_BLOCK_BITS;//计算当前要写文件占用的块  FileLength/NF_BLOCK_BYTES
		sector++;

		if(Nf_InvalidCou>0)
			{
			while(1)
				{
				for(i=0;i<Nf_InvalidCou;i++)
					{
					if(usesector<=iFileSectorInfo.iFileSectorTable[i])
						{
						usesector=iFileSectorInfo.iFileSectorTable[i]+1;
						if(usesector==iFileSectorInfo.iFileStartSector) //跳开起始块
							usesector++;
						if((usesector+sector)<iFileSectorInfo.iFileSectorTable[i+1])
							{
							return usesector; //返回当前可用块	
							}
						}
					else
						{
						if(usesector==iFileSectorInfo.iFileStartSector)//跳开起始块
							usesector++;
						if((usesector+sector)<iFileSectorInfo.iFileSectorTable[i+1])
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
		usesector=FILE_START_SECTOR;//++++++++++++++++++++++++++++
		sector=iFiles.FileLength>>NF_BLOCK_BITS;//计算当前要写文件占用的块
		sector++;
                
		if(Nf_InvalidCou>0)
			{
			while(1)
				{
				for(i=0;i<Nf_InvalidCou;i++)
					{
					if(usesector<=iFileSectorInfo.iFileSectorTable[i])
						{
						usesector=iFileSectorInfo.iFileSectorTable[i]+1;
						if(usesector==iFileSectorInfo.iFileStartSector)
							usesector++;
						//起始块空闲且完好，则判断后续容量---
						if((usesector+sector)<iFileSectorInfo.iFileSectorTable[i+1])//连续有用块 空间充足
							{
							return usesector; //返回当前可用块	
							}
						}
					else
						{
						if(usesector==iFileSectorInfo.iFileStartSector)
							usesector++;
						if((usesector+sector)<iFileSectorInfo.iFileSectorTable[i+1])//连续有用块 空间充足
							{
							return usesector; //返回当前可用块	
							}
						}
					}			
				}
			}
		else
			return usesector;//无坏块 返回当前可用块
		}
	}
else
	{//无空间
	return 0;//++++++++++++++
	}

}

unsigned char File_CreateStartSector(void) //产生 并保存 系统块信息 
{
unsigned short s_sector;
//unsigned int *f_buf;
unsigned short *nfiv;
int i;

srand(sys_tick);
while(1)
	{
	s_sector=rand();
	s_sector/=NF_BLOCK_PAGES;
	if((s_sector<NF_BLOCKS)&&(s_sector>0)) //判断是否为正常的数据块 ，并与坏块判断		99999999999999999
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
		}
	}
//s_sector=0;
iFileSectorInfo.iFileStartSector=s_sector;

nfiv=(unsigned short *)iFileSectorInfo.iFileSectorTable;   //------更新文件块信息
for(i=0;i<NF_BLOCKS;i++)
	{
	*nfiv++=InvalidBlock[i];
	}

unsigned char *f_buf=(unsigned char*)&iFileSectorInfo.iFileStartSector;
unsigned int p_add;
p_add=FILE_INFO_START_SECTOR*NF_BLOCK_PAGES;
p_add+=FILE_INFO_START_PAGE;//  计算页地址
i=Nand_Write_1Page(f_buf,p_add);//写一页 块信息
//i=Nand_WriteBytes(f_buf,FILE_INFO_START_SECTOR*NF_BLOCK_BYTES+FILE_INFO_START_PAGE*NF_PAGE_BYTES); //写入块信息头
if(i==1)
	return 1; //写头错误
else
	return 0;//正确
}

void File_GetStartSector(void) //读取一页 系统块信息
{
unsigned char *block_inf=(unsigned char*)&iFileSectorInfo.iFileStartSector;
unsigned int p_add;
p_add=FILE_INFO_START_SECTOR*NF_BLOCK_PAGES;
p_add+=FILE_INFO_START_PAGE;//  计算页地址
Nand_Read_1page(block_inf, p_add);//读一页 块信息
//Nand_ReadDates(block_inf,FILE_INFO_START_SECTOR*NF_BLOCK_BYTES+FILE_INFO_START_PAGE*NF_PAGE_BYTES,NF_PAGE_BYTES);
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
unsigned char *nametemp;
unsigned char *fnametemp;
unsigned int sector,wsector;
int i;

fnametemp=(unsigned char *)&iFiles.FileName;

if(File_Find(fname)==1)
	{//已存在更新
	Nand_ReadBlock(iFileName.iFileNameSector,(unsigned char *)NF_SECTOR_SDRAM_BUF);//读取 文件name信息
	sector=iFileName.iFileNameSector;
	Nand_EraseBlock(sector);
	Nand_FillFileInfo_SDbuf(FileNum,FILE_INFO_LENGTH,0xff); //删除原有的信息 包括文件名、长度，地址
	iFiles.FileAdd_Sector=iFilesTemp.FileAdd_Sector;//获取可用块

	Nand_WriteFileInfo_SDbuf(FileNum,FILE_INFO_LENGTH,fnametemp);
	Nand_WriteBlock(iFileName.iFileNameSector,(unsigned char *)NF_SECTOR_SDRAM_BUF);

	FileWrite(iFilesTemp, (unsigned char *)DOWNFILE_SDRAM_ADD);
	}
else
	{//文件不存在创建
	Nand_ReadBlock(iFileName.iFileNameSector,(unsigned char *)NF_SECTOR_SDRAM_BUF);//读取 文件name信息
	sector=File_GetFreeSector();//获取可用块
	if(sector!=0)//有空间
	  {
	  iFiles.FileAdd_Sector=sector;
	  Nand_EraseBlock(iFileName.iFileNameSector);

	  //Nand_FillPage_SDbuf(FileNum,FILE_INFO_LENGTH,0xff); //删除原有的信息 包括文件名、长度，地址
	  Nand_WriteFileInfo_SDbuf(FileNum,FILE_INFO_LENGTH,fnametemp);
	//  File_GetStartSector();//读取起始块信息
      Nand_WriteBlock(iFileName.iFileNameSector,(unsigned char *)NF_SECTOR_SDRAM_BUF);
	//  File_GetStartSector();//读取起始块信息
	
	  FileWrite(iFiles, (unsigned char *)DOWNFILE_SDRAM_ADD);
	 // File_GetStartSector();//读取起始块信息
	  }
	}
}


unsigned int File_Find(unsigned char *fname)  //查找一个文件是否存在    并产生 文件名 地址
{
int p;
unsigned char *f_buf;
unsigned short sector;
unsigned short page=0;
unsigned short f_num;
unsigned int n_add;
unsigned char namematch_flag=0;
unsigned char *nametemp;
int info_pages;
//int FileNum=0;

File_GetStartSector();//读取起始块信息

FileNum=0;//文件计数清零

sector=iFileSectorInfo.iFileStartSector;

info_pages=FILE_NUMS/FILE_INFO_NUMS_1PAGE;  //文件信息占用 总页数

for(p=0;p<info_pages;p++)
	{
	n_add=sector*NF_BLOCK_BYTES+page*NF_PAGE_BYTES;  //文件名信息 起始地址
	for(f_num=0;f_num< FILE_INFO_NUMS_1PAGE;f_num++)//判断一页内文件名
		{
		f_buf=(unsigned char*)&iFilesTemp;	
		Nand_ReadDates(f_buf,n_add,FILE_INFO_LENGTH);
//		f_buf=(unsigned char*)&filetemp->FileName;
		nametemp=(unsigned char *)fname;
		namematch_flag = 1; 
		while(*nametemp!=0)
			{
			if(*nametemp++ != *f_buf++)
				{
				namematch_flag = 0; 
				break;
				}
			}
		if(namematch_flag==1)
			break;
		FileNum++;
		n_add+=FILE_INFO_LENGTH;
		}

	if(namematch_flag==1)  //找到文件
		break;

	if(FileNum>=FILE_NUMS) //搜索完 全部文件
		break;

	page++;
	if(page>=NF_BLOCK_PAGES)	//执行不到------------文件名信息只有16 page，不满一块
		{
		page=0;
		sector++;
		}
	}

iFileName.iFileNameSector=sector;//nand内 块地址
/* //9999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999 */
// iFileName.iFileNamePage=page;  //块内 页偏移
// iFileName.iFileNameAddress=n_add; //nand内 绝对地址
// iFileName.iFileNameIndex=p;  //文件所处位置(文件名信息 内的页序)

if(namematch_flag==1)
	{
	return 1;  //找到文件
	}
else
	{
	return 0; //找不到对应文件
	}
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
		//		Printf24("下载....",400,350,0,1,0xf7a2);
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
		//		Printf24("下载....",400,350,0,1,0xf7a2);
		//		Printf24(iFiles.FileName,350,300,0,1,0xf7a2);

}
