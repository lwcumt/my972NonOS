
#include"comm.h"
#include"chndot.h"

#include"down_status.h"
#include "uart_config.h"
#include "drv_glcd.h"
#include "file.h"




unsigned char Rec_Data[60];
int CommCou;
char CommHead_Flag;  //接收帧头标志位
char CommFrame_Flag; //接收帧标志位
char CommCommd;   //命令
int CommAdder;   //地址
int CommFileLenth; //文件长度
int CommLengthTemp; //
char CommEnd_Flag;  //帧结束标志位
int BMP_Hight;
int BMP_Width;
int BMP_Bit;
int BMP_highttemp1;
int BMP_widthtemp1;
int ColorData[10];
int ColorCou;
char PicDisplay_Flag;
int R,G,B;
int Color;



pInt16U fPtr;
unsigned char *dfPtr;

void CommExec(Int8U rx_data)
{
int i;
char a;
char stemp[8];
	Int32U m;
	Int32U n;
if(CommHead_Flag==0)
	{
//	CommCou++;
	BellOUT_OFF;//BellOUT_OFF;
	Rec_Data[CommCou++]=rx_data;//读取数据
	if(CommCou>1)
		{
		if((Rec_Data[0]==0xaa)&&(Rec_Data[1]==0x55))
			{
			CommHead_Flag=1;  //帧头正确
			}
		else
			{
			CommCou=0;//重新接收
			CommHead_Flag=0;
			CommFrame_Flag=0;
			}
		}
	else
		{
		if((Rec_Data[0]!=0xaa))
			{
			CommCou=0;//重新接收
			CommHead_Flag=0;
			CommFrame_Flag=0;
			}
		}
	}
else
	{
    if(CommFrame_Flag==0)
		{//接收帧命令
	    Rec_Data[CommCou++]=rx_data; //读取数据
		if(CommCou>=10)
			{
			a=0;
			for(i=0;i<9;i++)
				a^=Rec_Data[i];//校验和 
			if(a==Rec_Data[9])
				{
				CommFrame_Flag=1; //帧正确

				CommCommd=Rec_Data[COMMCOMMDADD]; //读命令

				CommAdder=Rec_Data[COMMADDERADD];    //读地址
				CommAdder<<=8;
				CommAdder|=(Rec_Data[COMMADDERADD+1]&0xff);
				CommAdder<<=8;
				CommAdder|=(Rec_Data[COMMADDERADD+2]&0xff);


				CommFileLenth=Rec_Data[COMMLENTHADD];  //读长度
				CommFileLenth<<=8;
				CommFileLenth|=(Rec_Data[COMMLENTHADD+1]&0xff);
				CommFileLenth<<=8;
				CommFileLenth|=(Rec_Data[COMMLENTHADD+2]&0xff);
                                
                                
				//if(CommFileLenth>1152054)
				//	CommFileLenth--;
//				CommFileLenth--;

				switch(CommCommd)
					{
					case COMMD_WRITE_BMP_FLASH:
						CommFrame_Flag=1;  //允许接收数据
						 
						CommCou=0;
						break;
					case COMMD_WRITE_FILE_FLASH:
						CommFrame_Flag=1;	//允许接收数据
						CommCou=0;
						break;
					case COMMD_READ_FLASH_SDRAM:	//直接返回   从FLASH读到SDRAM
					    CommCou=0;
						CommHead_Flag=0;
						CommFrame_Flag=0;
						CommEnd_Flag=1;//置结束
						break;
					case COMMD_WRITE_SDRAM_FLASH:	//直接返回   把SDRAM写到FLASH
					    CommCou=0;
						CommHead_Flag=0;
						CommFrame_Flag=0;
						CommEnd_Flag=1;//置结束
						break;
					case COMMD_ERASE_FLASH:	//直接返回		擦除FLASH
					    CommCou=0;
						CommHead_Flag=0;
						CommFrame_Flag=0;
						CommEnd_Flag=1;//置结束
						break;
					case COMMD_CLR_SCREEN:	//直接返回     清屏
					    CommCou=0;
						CommHead_Flag=0;
						CommFrame_Flag=0;
						CommEnd_Flag=1;//置结束
						break;
					case COMMD_DISPLAY_BMP:    //直接返回   显示图片
					    CommCou=0;
						CommHead_Flag=0;
						CommFrame_Flag=0;
						CommEnd_Flag=1;//置结束
						break;
					case COMMD_WRITE_SPI_FLASH: //允许接收数据 
						CommFrame_Flag=1;  //允许接收数据
						fPtr=(pInt16U)(0x80100000);
						CommCou=0;
						
						GLCD_SetWindow_Fill(20,175,300,220,0,0);
						ASCII_Printf("LoadingBuf",ASCII1632_MODE,ASCII1632_WIDTH,ASCII1632_HIGH,ASCII1632,40,180,0xffff,0);
						
						ASCII_Printf("TOTAL",ASCII1632_MODE,ASCII1632_WIDTH,ASCII1632_HIGH,ASCII1632,310,185,0,0xffff);
						GLCD_SetWindow(400,175,540,220,0);
						//Datas_dis(CommFileLenth, 405 , 185  );
						ASCII_Printf("NOW",ASCII1632_MODE,ASCII1632_WIDTH,ASCII1632_HIGH,ASCII1632,550,185,0xf800,0);
						GLCD_SetWindow(605,175,750,220,0x001f);
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
						CommFrame_Flag=1;  //允许接收数据
						dfPtr=(unsigned char *)(DOWNFILE_SDRAM_ADD); //下载的地址
						CommCou=0;
						CommLengthTemp=0;
						//pcou=0;
						//DownSchedule_dis( CommFileLenth);

						stemp[0]=0xaa;
						stemp[1]=0;
						UART0_SendStr(stemp);
						break;
					case DOWNFILE_FILE_SEND_NAME :// 0x24 //发送一个文件名
						CommFrame_Flag=1;  //允许接收数据
						dfPtr=(unsigned char *)(DOWNFILE_SDRAM_ADD); //下载的地址
						CommCou=0;
						CommLengthTemp=0;
						//pcou=0;
						stemp[0]=0xaa;
						stemp[1]=0;
						UART0_SendStr(stemp);
//                        UART0_SendStr("准备传送");
						break;

					case DOWNFILE_FILE_FORMAT: //系统格式化
					    CommCou=0;
						CommLengthTemp=0;
						CommHead_Flag=0;
						CommFrame_Flag=0;
						CommEnd_Flag=1;//置结束
						break;

///*
					case DOWNFILE_FILE_BOOT:
						CommFrame_Flag=1;  //允许接收数据
						dfPtr=(unsigned char *)(DOWNFILE_SDRAM_ADD); //下载的地址
						CommCou=0;
						CommLengthTemp=0;
//						pcou=0;
						//DownSchedule_dis( CommFileLenth);
						
						stemp[0]=0xaa;
						stemp[1]=0;
						UART0_SendStr(stemp);						
						break;

					case DOWNFILE_FILE_APP:
						CommFrame_Flag=1;  //允许接收数据
						dfPtr=(unsigned char *)(DOWNFILE_SDRAM_ADD); //下载的地址
						CommCou=0;
						CommLengthTemp=0;
		//				pcou=0;
						//DownSchedule_dis( CommFileLenth);
						
						stemp[0]=0xaa;
						stemp[1]=0;
						UART0_SendStr(stemp);
						break;//*/
					}
				}
			else
				{
				CommCou=0;
				CommHead_Flag=0;
				}
			}
		}
	else
		{//帧头完毕 开始接收数据
	    switch(CommCommd)
			{
			case COMMD_WRITE_BMP_FLASH:
					if(PicDisplay_Flag==0)
							{
							Rec_Data[CommCou++]=rx_data; //读取数据
							if(CommCou>=0x36)
								{
								Int32U n=0;
								BMP_Hight = Rec_Data[0x19];
								BMP_Hight <<= 8;
								BMP_Hight += Rec_Data[0x18];
								BMP_Hight <<= 8;
								BMP_Hight += Rec_Data[0x17];
								BMP_Hight <<= 8;
								BMP_Hight += Rec_Data[0x16];
								
								BMP_Width = Rec_Data[0x15];
								BMP_Width <<= 8;
								BMP_Width +=Rec_Data[0x14];
								BMP_Width <<= 8;
								BMP_Width += Rec_Data[0x13];
								BMP_Width <<= 8;
								BMP_Width += Rec_Data[0x12];
								
								BMP_Bit = Rec_Data[0x1d];
								BMP_Bit <<= 8;
								BMP_Bit += Rec_Data[0x1c];
								
								BMP_highttemp1 = BMP_Hight;
								BMP_widthtemp1= 0;
								ColorCou=0;
								PicDisplay_Flag=1;
								}
							}
						else
							{//显示
							ColorData[ColorCou++]=rx_data;
							CommCou++;
							
							if(ColorCou>=3)
								{
								ColorCou=0;
								R = ColorData[0];
								G = ColorData[1];
								B = ColorData[2];
								R>>=3;
								G>>=2;
								B>>=3;
								Color=R;
								Color|=(G<<5);
								Color|=(B<<11);
								PutPixel(BMP_widthtemp1,BMP_highttemp1-1,Color);
								BMP_widthtemp1++;
								if(BMP_widthtemp1>=BMP_Width)
									{
									BMP_highttemp1--;
									BMP_widthtemp1 = 0;
									if(BMP_highttemp1==0)
										{
										//						WordProgram(noraddr++,(Int16U)BMP_hight);
										//						WordProgram(noraddr++,(Int16U)BMP_width);
										for( n = 0;n<BMP_Hight;n++)
											{
											for(m = 0;m<BMP_Width;m++)
												{
												//								WordProgram( noraddr++,*(volatile Int16U *)(0xA0000000 + m * 2 + 2*800* n));
												}
											}
										//GLCD_Display_BMP((pInt16U)(0x81000000+noraddrtemp),0,0);
										}
									}
								}
							}
				break;
			case COMMD_WRITE_SPI_FLASH:  //写文件到SPI 
				*fPtr++=rx_data;
				CommCou++;
				
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
					*dfPtr++=rx_data;
					CommCou++;
					CommLengthTemp++;
					break;
			case DOWNFILE_FILE_SEND_NAME :// 0x24 //发送一个文件名
					*dfPtr++=rx_data;
					CommCou++;
					CommLengthTemp++;
					break;
					
			case DOWNFILE_FILE_BOOT:
					*dfPtr++=rx_data;
					CommCou++;
					CommLengthTemp++;
					break;
			case DOWNFILE_FILE_APP:
					*dfPtr++=rx_data;
					CommCou++;
					CommLengthTemp++;
					break;
			}


  // 	    pInt16U  ptr=(pInt16U)(LCD_VRAM_BASE_ADDR+CommCou*2); 
//		*ptr=rx_data;
	//	CommCou++;
		if(CommCou>=CommFileLenth)
			{
			switch(CommCommd)
				{
				case DOWNFILE_FILE_SEND_NAME :// 0x24 //发送一个文件名
					*dfPtr=0;  //插入0
                    // Printf_Us1("传送完毕");
					break;
				}
			CommCou=0;
			CommHead_Flag=0;
			CommFrame_Flag=0;
			PicDisplay_Flag=0;
			ColorCou=0;
			CommEnd_Flag=1;//置结束
			//BellOUT_ON;
			}
		}
	}

}



