#include"sdcopy.h"
#include "sd_config.h"
#include "ff.h"
#include "file.h"
#include "word_lib.h"
#include "nandflash.h"
#include "chndot.h"
#include "drv_glcd.h"

int Rrca;
int filetotalnum;
int filewritenum;

int FileWriteCounter=0;

unsigned char filename_buf[128];


void SDInsert_Check(void)
{
int i;
int n;
int 	validocr;
int	ocrtries;
unsigned int  buff1[516];
  //SD_CMDRESP_T resp;
  unsigned int sblk;
  sblk=1;

 // if (SD_CD_IN() == FALSE)
// {
//  //Printf24("SD卡已插入，正在拷贝文件........",810,50,RED_COLOR,1,0xffff);

 BellOUT_ON;
 i=1000000;
 while(i--);
 i=1000000;
 while(i--);
  i=1000000;
 while(i--);
  i=1000000;
 while(i--);
  i=1000000;
 while(i--);
 BellOUT_OFF;

	if(GPIO_ReadBit(GPIOD,BIT6)==0)
	{

	//SD_PWR_ON();
	SD_main();

   SD_FileReadAndWriteToNandFlash();//读取文件并写入NANDFLASH

		//SD_Close();//关闭SD卡
		  i=1000000;
 while(i--);
	SD_PWR_OFF();
	}

//  }
 }




	


Int8U mf_scan_files(Int8U * path) 
{ 

	int delayt;
int delayi;
	DIR dir;
	FILINFO fileinfo;

	Int16U ReadValue;
	FATFS fs;            // Work area (file system object) for logical drive
	FIL fsrc;      			// file objects
//	Int8U buffer[2048]; 		// file copy buffer
	UINT br;         		// File R/W count
	Int8U i=0;
	Int8U n;
	char a;
unsigned char pathname[64];
	unsigned char namelength;
	i=0;
	a='X';
	
if(strcmp(path,"0:/APP1")==0)
	BootFolder=1;
if(strcmp(path,"0:/APP2")==0)
	BootFolder=2;
if(strcmp(path,"0:/APP3")==0)
	BootFolder=3;

if(strcmp(path,"0:/APP4")==0)
	BootFolder=4;

if(strcmp(path,"0:/APP5")==0)
	BootFolder=5;

if(strcmp(path,"0:/APP6")==0)
	BootFolder=6;
	


	while(path[i]!=0)
	{
	pathname[i]=path[i];
  i++;		
	namelength=i;
	}
	filetotalnum=0;
   filewritenum=0;

FRESULT res;	   
    char *fn;   /* This function is assuming non-Unicode cfg. */ 
	
#if _USE_LFN 
 	fileinfo.lfsize = _MAX_LFN * 2 + 1; 
	 char name[255*2+1];//.lfsize];
fileinfo.lfname =( char*)&name; //mymalloc(SRAMIN,fileinfo.lfsize); 
#endif	   

    res = f_opendir(&dir,(const char*)path); //打开一个目录 
    if (res == FR_OK)  
{	

while(1) 
{ 
        res = f_readdir(&dir, &fileinfo);                   //读取目录下的一个文件 
        if (res != FR_OK || fileinfo.fname[0] == 0) break;  //错误了/到末尾了,退出 
        //if (fileinfo.fname[0] == '.') continue;             //忽略上级目录 
#if _USE_LFN 
        	fn = *fileinfo.lfname ? fileinfo.lfname: fileinfo.fname; 
#else	    
        	fn = fileinfo.fname; 
#endif	                                              /* It is a file. */ 
	
	filetotalnum++;
	n=namelength;

   pathname[n++]='\\';
	i=0;
   while(fn[i]!=0)
	{

	pathname[n++]=fn[i++];
	}
	pathname[n]=fn[i];

//pathname[0]=pathname[1];
   res = f_open(&file1, (char*)pathname, FA_OPEN_EXISTING | FA_READ);	 //打上图片文件名

  if(res==FR_NO_FILE||res==FR_INVALID_NAME){

  }
  else
  {
		//Printf24("读取文件",0,0,0,1,0xf7a2);
	iFiles.FileLength=file1.fsize;
    res = f_read(&file1, (unsigned char *)DOWNFILE_SDRAM_ADD, file1.fsize, &br);
		f_close(&file1);
//Printf24("读取完毕",0,0,0,1,0xf7a2);
    filewritenum++;
	//ChangeFileName((unsigned char*)fn);
	ChangeFileName1((unsigned char*)pathname);
		//Printf24("文件名称",0,0,0,1,0xf7a2);
	 GLCD_SetWindow_Fill(350, 300, 750, 380, BLUE_COLOR, BLUE_COLOR);
	 Printf24(iFiles.FileName,350,300,0,1,0xf7a2);
	
	
//	 Printf24(pathname,350,200,0,1,0xf7a2);
		
		for(delayt=0;delayt<100000;delayt++);

		
		if(strcmp((char*)fn,"字库_0x20000.FON")!=0)
			if(strcmp((char*)fn,".")!=0)
				if(strcmp((char*)fn,"..")!=0)
				{
				File_Create(iFiles.FileName);//建立文件
				////////+b  更改名字----
				/**
				if(BootFolder==1)
				{
				memset(filename_buf,0,128);
				filename_buf[0]='\\';
				filename_buf[1]='A';
				filename_buf[2]='P';
				filename_buf[3]='P';
				filename_buf[4]=BootFolder+0x30;
				filename_buf[5]='\\';//BootFolder+0x30;
				filename_buf[6]='b';
				memcpy(&filename_buf[7],fn,strlen(fn));
				ChangeFileName(filename_buf);	
				 GLCD_SetWindow_Fill(350, 300, 750, 380, BLUE_COLOR, BLUE_COLOR);
				 Printf24(iFiles.FileName,350,300,0,1,0xf7a2);
				 File_Create(iFiles.FileName);//建立文件+b
				}
				**/
					if(BootFolder==1)	
					{
						/*
						if(FileFolderRead(fn,(unsigned char*)START_PIC_sdram)==0)//读开机画面
						{
							memset(filename_buf,0,128);
						filename_buf[0]='\\';
						filename_buf[1]='A';
						filename_buf[2]='P';
						filename_buf[3]='P';
						filename_buf[4]=BootFolder+0x30;
						filename_buf[5]='\\';//BootFolder+0x30;
						filename_buf[6]='b';
						memcpy(&filename_buf[7],fn,strlen(fn));
						ChangeFileName(filename_buf);	
						 GLCD_SetWindow_Fill(350, 300, 750, 380, BLUE_COLOR, BLUE_COLOR);
						 Printf24(iFiles.FileName,350,300,0,1,0xf7a2);
						 File_Create(iFiles.FileName);//建立文件+b
						}*/
					}
				
			/****3 time write
			FileWriteCounter=0;
				while(1)
					{
					ChangeFileName1((unsigned char*)pathname);
				File_Create(iFiles.FileName);//建立文件
						for(delayt=0;delayt<100000;delayt++);
						for(delayt=0;delayt<100000;delayt++);

					if(FileFolderRead(fn,(unsigned char*)START_PIC_sdram)!=0)//读开机画面
						break;

					FileWriteCounter++;
					if(FileWriteCounter>3)
						{//写入3次出错，显示错误的文件名
						FileWriteCounter=0;
					    Printf24("文件写入错误：",350,360,0,1,0xf7a2);
						Printf24(iFiles.FileName,350+8+7*24,360,0,1,0xf7a2);



						memset(filename_buf,0,128);
						filename_buf[0]='\\';
						filename_buf[1]='A';
						filename_buf[2]='P';
						filename_buf[3]='P';
						filename_buf[4]=BootFolder+0x30;
						filename_buf[5]='\\';//BootFolder+0x30;
						filename_buf[6]='B';
						memcpy(&filename_buf[7],fn,strlen(fn));

						ChangeFileName(filename_buf);
//						memcpy(&iFiles.FileName,filename_buf,strlen(filename_buf));
				//		Printf24(filename_buf,350,300,0,1,0xf7a2);	

						for(delayi=0;delayi<100;delayi++)
							for(delayt=0;delayt<200000;delayt++);

				//		Printf24(iFiles.FileName,350,300,0,1,0xf7a2);	
						File_Create(iFiles.FileName);//建立文件


						for(delayi=0;delayi<100;delayi++)
							for(delayt=0;delayt<200000;delayt++);

						break;
						}
					for(delayt=0;delayt<100000;delayt++);
					}	
					***/
				}
//Printf24("写入完成",0,0,0,1,0xf7a2);
	  }

   
}  
    }	   
//myfree(SRAMIN,fileinfo.lfname); 

    return res;	   
}


	


void SD_FileReadAndWriteToNandFlash(void)
{
	Int16U ReadValue;
	FATFS fs;            // Work area (file system object) for logical drive
	FIL fsrc;      			// file objects
//	Int8U buffer[2048]; 		// file copy buffer
	FRESULT res;         // FatFs function common result code
	UINT br;         		// File R/W count
	Int16U r_data,g_data,b_data;	
	Int32U	 tx,ty;//temp;
	Int8U fbuf[10]=0;
    TCHAR		sd_path[] = { '0', ':', 0 };    /* SD drive started from 0 */
	unsigned char BootAppFileCou;

/*

   BootAppFileCou=0;
  f_mount(0, &fs);
  res = f_open(&fsrc, "Boot.bin", FA_OPEN_EXISTING | FA_READ);	 //打上图片文件名
  if(res==FR_NO_FILE||res==FR_INVALID_NAME){
     f_mount(0, NULL);
  }
  else
  {
	BootAppFileCou++;
		f_close(&fsrc);
	f_mount(0, NULL);
   }
*/



f_mount(&fs,sd_path, 1);	


res = f_open(&file1, "0:/SysFormat.ini", FA_OPEN_EXISTING | FA_READ);
	 
if(res==FR_NO_FILE||res==FR_INVALID_NAME)
   f_mount(&fs,sd_path, 0);//no file
	else
		
{
	iFiles.FileLength=file1.fsize;
    res = f_read(&file1, fbuf, file1.fsize, &br);
	f_close(&file1);	
	if(strcmp(fbuf,"1")==0)
		{
	  GLCD_SetWindow_Fill(350, 300, 750, 380, BLUE_COLOR, BLUE_COLOR);
	 ASCII_Printf("Formating", ASCII1632_MODE, ASCII1632_WIDTH, ASCII1632_HIGH, ASCII1632, 350, 300, 0xffff, 0);
	Nand_Format();//删除并标记坏块
		}
}

 	

  GLCD_SetWindow_Fill(350, 300, 750, 380, BLUE_COLOR, BLUE_COLOR);
 ASCII_Printf("Now Starting Copy File", ASCII1632_MODE, ASCII1632_WIDTH, ASCII1632_HIGH, ASCII1632, 350, 300, 0xffff, 0);

f_mount(&fs,sd_path, 1);
res = f_open(&file1, "0:/字库_0x20000.FON", FA_OPEN_EXISTING | FA_READ);
	 
  if(res==FR_NO_FILE||res==FR_INVALID_NAME){
  f_mount(&fs,sd_path, 0);
  }
  else
  {
	iFiles.FileLength=file1.fsize;
    res = f_read(&file1, (unsigned char *)DOWNFILE_SDRAM_ADD, file1.fsize, &br);
	f_close(&file1);

	ChangeFileName("字库_0x20000.FON");
	//NandEccWrite_Flag=0;
	File_Create(iFiles.FileName);//建立文件
	  }





/*
   res = f_open(&file1, "Power.bmp", FA_OPEN_EXISTING | FA_READ);
	 
  if(res==FR_NO_FILE||res==FR_INVALID_NAME){
   //f_mount(fs,sd_path, 0);
  }
  else
  {
	iFiles.FileLength=file1.fsize;
    res = f_read(&file1, (unsigned char *)DOWNFILE_SDRAM_ADD, file1.fsize, &br);
	f_close(&file1);

	ChangeFileName("Power.bmp");
	//NandEccWrite_Flag=0;
	File_Create(iFiles.FileName);//建立文件
	  }

return;

*/


res = f_open(&file1, "0:/AppStartFile.ini", FA_OPEN_EXISTING | FA_READ);
	 
  if(res==FR_NO_FILE||res==FR_INVALID_NAME){
  f_mount(&fs,sd_path, 0);
  }
  else
  {
	iFiles.FileLength=file1.fsize;
    res = f_read(&file1, (unsigned char *)DOWNFILE_SDRAM_ADD, file1.fsize, &br);
	f_close(&file1);

	ChangeFileName("AppStartFile.ini");
	//NandEccWrite_Flag=0;
	File_Create(iFiles.FileName);//建立文件
	  }


/*
   f_mount(0, &fs);
   res = f_open(&fsrc, "AppStartFile.ini", FA_OPEN_EXISTING | FA_READ);	 //打上图片文件名
  if(res==FR_NO_FILE||res==FR_INVALID_NAME){
     f_mount(0, NULL);
  }
  else
  {
	iFiles.FileLength=fsrc.fsize;
    res = f_read(&fsrc, (unsigned char *)DOWNFILE_SDRAM_ADD, fsrc.fsize, &br);
	f_close(&fsrc);
	f_mount(0, NULL);
 
	ChangeFileName("AppStartFile.ini");
	NandEccWrite_Flag=0;
	File_Create(iFiles.FileName);//建立文件
	  }

*/

 FileRead("字库_0x20000.FON",(unsigned char *)df_zk_sdram);

//f_mount(0, &fs);

//mf_scan_files("0:");
mf_scan_files("0:/APP1");
mf_scan_files("0:/APP2");
mf_scan_files("0:/APP3");
mf_scan_files("0:/APP4");
mf_scan_files("0:/APP5");
mf_scan_files("0:/APP6");
//f_mount(0, NULL);

///*
/*
    f_mount(0, &fs);
  res = f_open(&fsrc, "Boot.bin", FA_OPEN_EXISTING | FA_READ);	 //打上图片文件名
  if(res==FR_NO_FILE||res==FR_INVALID_NAME){
     f_mount(0, NULL);
  }
  else
  {
	CommFileLenth=iFiles.FileLength=fsrc.fsize;

    res = f_read(&fsrc, (unsigned char *)DOWNFILE_SDRAM_ADD, fsrc.fsize, &br);
	f_close(&fsrc);
	f_mount(0, NULL);
 

      NandEccWrite_Flag=1;
				FileWirte_Boot();
 NandEccWrite_Flag=0;
*/
//////// delay(10000);


////////// */

////////  GLCD_SetWindow_Fill(350, 300, 750, 380, BLUE_COLOR, BLUE_COLOR);
//////// Printf24("文件拷贝完成，请移除SD卡！！！",350,300,0,1,0xf7a2);
//................. 
// 一共92个文件
}




