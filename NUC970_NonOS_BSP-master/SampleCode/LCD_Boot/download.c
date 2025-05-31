
#include"download.h"

#include"down_status.h"
#include"m25pe16.h"

#include"word_lib.h"
#include"pic_exec.h"
#include "uart_config.h"

Int16U tt;

Int32U Page=0; 

void DownFile_Exec(void)	//文件下载处理
{
	char stemp[8];
	pInt16U ptr;

if(CommFrame_Flag==1)
	{/*
	stemp[0]=CommLengthTemp/1000000+0x30;
	stemp[1]=(CommLengthTemp%1000000)/100000+0x30;
	stemp[2]=(CommLengthTemp%1000000)%100000/10000+0x30;
	stemp[3]=(CommLengthTemp%1000000)%100000%10000/1000+0x30;
	stemp[4]=(CommLengthTemp%1000000)%100000%10000%1000/100+0x30;
	stemp[5]=(CommLengthTemp%1000000)%100000%10000%1000%100/10+0x30;
	stemp[6]=(CommLengthTemp%1000000)%100000%10000%1000%100%10+0x30;
	stemp[7]=0;
	Printf24(stemp,100+24*18,66,0,1,0xf7a2);*/
	tt++;
	if(tt>=200)
	  {
	  tt=0;
	  GLCD_SetWindow_Fill(610,185,738,215,0xffff,0xffff);
	  Datas_dis( CommLengthTemp, 610,185);
	  }
	
	}


//以下为通信处理，先不用理会。
   if(CommEnd_Flag==1)
	  {//帧结束 
	  CommEnd_Flag=0;
      
	//Datas_dis( CommLengthTemp, 610,185);
     GLCD_SetWindow_Fill(610,185,738,215,0xffff,0xffff);
	  Datas_dis( CommLengthTemp, 610,185);
	  switch(CommCommd)
		  {
		  case COMMD_WRITE_BMP_FLASH:	

				  break;
		  case COMMD_WRITE_FILE_FLASH:

				  break;
		  case COMMD_READ_FLASH_SDRAM:	//直接返回   从FLASH读到SDRAM

				  break;
		  case COMMD_WRITE_SDRAM_FLASH:	//直接返回   把SDRAM写到FLASH

				  break;
		  case COMMD_ERASE_FLASH:	//直接返回		擦除FLASH

				  break;
		  case COMMD_CLR_SCREEN:	//直接返回     清屏

				  break;
		  case COMMD_DISPLAY_BMP:    //直接返回   显示图片

				  break;
		  case COMMD_WRITE_SPI_FLASH: //允许接收数据 
				fPtr=(pInt16U)0xa0100000;
		         Page=CommAdder;
				 Page*=528;
				 Page>>=8;
				 
			LED2_ON; 
			    GLCD_SetWindow_Fill(20,175,300,220,0x1f,0x1f);
				ASCII_Printf("LoadingSpiFlash",ASCII1632_MODE,ASCII1632_WIDTH,ASCII1632_HIGH,ASCII1632,30,180,0xffff,0);  
				volatile Int32U i,d;
				Int8U Rx_buf[300];
				 //-------------------------flash操作修改-------------------
				  for(i=0;i<=CommFileLenth/256;i++)
					  {
					   for(d=0;d<256;d++)
						  {
						   Rx_buf[d]=(Int8U)((Int16U)*fPtr&0xff);
//						   RBuf[d1]=(Int8U)(Int16U)*fPtr&0xff;
						   fPtr++;
						  }
					   Page_Write(Rx_buf,   Page++,   256);
					  
					  //---------------------显示进度
					   GLCD_SetWindow_Fill(610,185,738,215,0xffff,0xffff);
                       Datas_dis(Page<<8, 610 , 185  ); 
					  }	  
			LED2_OFF;		  
				GLCD_SetWindow_Fill(20,175,300,220,0x07e0,0x07e0);
			  ASCII_Printf("LoadingOK",ASCII1632_MODE,ASCII1632_WIDTH,ASCII1632_HIGH,ASCII1632,40,180,0xffff,0);
				  break;

		  //*****************************************************
		  //新增传送文件处理
		  case DOWNFILE_FILE_DELETE   ://  0x20 //删除一个文件  
				break;
		  case DOWNFILE_FILE_CREATE   ://0x21 //建立一个文件  
				break;
		  case DOWNFILE_FILE_CREATE_DIR:// 0x22 //建立一个目    
				break;
		  case DOWNFILE_FILE_SEND      :// 0x23 //发送一个文件 		

				iFiles.FileLength=CommFileLenth;//读取文件长度	
				File_Create(iFiles.FileName);//建立文件
				FileRead("字库_0x20000.FON",(unsigned char *)df_zk_sdram);
				Printf24("下载完毕!",400,350,0,1,0xf7a2);
		  		stemp[0]=0xaa;
				stemp[1]=0;
				UART0_SendStr(stemp);	
				break;
		  case DOWNFILE_FILE_SEND_NAME :// 0x24 //发送一个文件名
				dfPtr=(unsigned char *)DOWNFILE_SDRAM_ADD;
				unsigned char *ifiles=(unsigned char *)iFiles.FileName;

				//GLCD_Buffer_Fill(BLUE_COLOR);

				while(*dfPtr!=0)
					{
					*ifiles++=*dfPtr++;
					}
				 *ifiles=0;
				
				Printf24("下载....",400,350,0,1,0xf7a2);
				Printf24(iFiles.FileName,350,300,0,1,0xf7a2);
					stemp[0]=0xaa;
					stemp[1]=0;
					UART0_SendStr(stemp);
				break;

		  case DOWNFILE_FILE_FORMAT: //系统格式化
				Nand_Format();//删除并标记坏块
			//	uartWrite(3, "FormatOK\r\n", 10);
			//	uartWrite(3, "FormatOK\r\n", 10);
			//UART0_SendStr("Format OK");
			UART0_SendStr("Format OKahjdjdhfhahl**************************************\r\n");
				stemp[0]=0xaa;
				stemp[1]=0;
				UART0_SendStr(stemp);    
//				File_Create("开机.bmp");
//			    File_GetStartSector();//  
				break;
		  case DOWNFILE_FILE_BOOT://写入BOOT
				break;
		  case DOWNFILE_FILE_APP:  //写入APP
/*
				FileWriteToSPI(CommAdder);
				Printf24("下载完毕:",100,66,0,1,0xf7a2);
				stemp[0]=0xaa;
				stemp[1]=0;
				UART0_SendStr(stemp); */
//				FileWriteToSPI(CommAdder);
				break;
		  }
	  }



//以上开机下载图片
//**************************************

}

