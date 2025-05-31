//unsigned char AsciiChar[16];
#define ASCIIADD 0x40000
#define AT45db041_ContArray_Read_Commd 0xE8 //连续读命令 SPI模式3
#define AT45db041_MMPage_Read_Commd 0xD2  //主存储页读命令 SPI模式3
#define AT45db041_Buf1_Read_Commd 0xD4  //读缓冲区1数据命令  SPI模式3
#define AT45db041_Buf2_Read_Commd 0xD6  //读缓冲区2数据命令  SPI模式3
#define AT45db041_Status_Read_Commd 0xD7   //读状态寄存器命令   SPI模式3

#define AT45db041_Buf1_Write_Commd 0x84  //向缓冲区1写数据命令
#define AT45db041_Buf2_Write_Commd 0x87  //向缓冲区2写数据命令

#define AT45db041_Buf1MM_ProErase_Commd 0x83  //缓冲区1写数据到主存储页并擦除该主存储页命令
#define AT45db041_Buf2MM_ProErase_Commd 0x86  //缓冲区2写数据到主存储页并擦除该主存储页命令
#define AT45db041_Buf1ToMM_Pro_Commd 0x88  //缓冲区1写数据到主存储页命令
#define AT45db041_Buf2ToMM_Pro_Commd 0x89  //缓冲区2写数据到主存储页命令
#define AT45db041_Page_Erase_Commd 0x81  //页擦除命令
#define AT45db041_Block_Erase_commd 0x50  //块擦除命令

#define AT45db041_Buf1WriteAndMM_Commd 0x82  //向缓冲区1和主存储页写数据并擦除该主存储页命令
#define AT45db041_Buf2WriteAndMM_Commd 0x85  //向缓冲区2和主存储页写数据并擦除该主存储页命令


#define AT45db041_MMToBuf1_Tran_Commd 0x53  //指定页到BUFFER1数据转移命令
#define AT45db041_MMToBuf2_Tran_Commd 0x55  //指定页到BUFFER2数据转移命令

#define AT45db041_MMToBuf1_Comp_Commd 0x60  //指定页与BUFFER1数据比较命令
#define AT45db041_MMToBuf2_Comp_Commd 0x61  //指定页与BUFFER2数据比较命令

#define AT45db041_APageBuff1_Rewr_Commd 0x58  //向指定页从BUFFER1中重写命令
#define AT45db041_APageBuff2_Rewr_Commd 0x59  //向指定页从BUFFER2中重写命令

void HZK_Read( char *hzp,unsigned char distype);  //读取汉字库中汉字点阵 distype 0:正常 1:反相