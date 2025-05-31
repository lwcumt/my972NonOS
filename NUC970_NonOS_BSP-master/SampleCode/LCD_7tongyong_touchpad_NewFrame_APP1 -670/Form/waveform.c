#include "waveform.h"

CHART chart1={Chart_Type,\
								TRUE,
								0,10,\
								100,50,\
								WHITE_COLOR,\
								16,\
								32,
								80,\
								4,\
								10,\
								5,\
								50, //ScaleView
								2,
								(255<<16)
								};



void WaveFormInit(void)
{
unsigned short dbuf[20];
*FormActive[0]=2;
GLCD_SetWindow_Fill(0,32,799,479,cpGui_ColorChange(cSystemColor),cpGui_ColorChange(cSystemColor));//.Location.x,label.Location.y,label.Location.x+label.Size.width,label.Location.y+label.Size.high,cpGui_ColorChange(label.bkColor),cpGui_ColorChange(label.bkColor));				
		dbuf[0]=200;
		dbuf[1]=210;
		dbuf[2]=180;
		dbuf[3]=160;
		dbuf[4]=280;
		dbuf[5]=300;
		dbuf[6]=100;
		dbuf[7]=50;
		dbuf[8]=500;
		dbuf[9]=788;
	   dbuf[10]=80;
cpGui_ChartRedraw(chart1,dbuf,10);	
cpGui_ChangeText(&MainFormLabel.Text,"设备状态");
cpGui_CreateLabel(MainFormLabel);	
	
	
FileFolderRead("Wave_64x64.bmp",(unsigned char*)START_PIC_sdram);//读开机画面
Bmp_Decode((Int32U)START_PIC_sdram, 60, 480-64-2-10, (pInt16U)SDRAM0_BASE_ADDR); //显示开机画面

FileFolderRead("Note_64x64.bmp",(unsigned char*)START_PIC_sdram);//读开机画面
Bmp_Decode((Int32U)START_PIC_sdram, 60+1*64+8, 480-64-2, (pInt16U)SDRAM0_BASE_ADDR); //显示开机画面

FileFolderRead("Setup_64x64.bmp",(unsigned char*)START_PIC_sdram);//读开机画面
Bmp_Decode((Int32U)START_PIC_sdram, 60+2*64+8, 480-64-2, (pInt16U)SDRAM0_BASE_ADDR); //显示开机画面


FileFolderRead("Net_64x64.bmp",(unsigned char*)START_PIC_sdram);//读开机画面
Bmp_Decode((Int32U)START_PIC_sdram, 60+3*64+8, 480-64-2, (pInt16U)SDRAM0_BASE_ADDR); //显示开机画面

FileFolderRead("Save_64x64.bmp",(unsigned char*)START_PIC_sdram);//读开机画面
Bmp_Decode((Int32U)START_PIC_sdram, 60+4*64+8, 480-64-2, (pInt16U)SDRAM0_BASE_ADDR); //显示开机画面

FileFolderRead("Riss_64x64.bmp",(unsigned char*)START_PIC_sdram);//读开机画面
Bmp_Decode((Int32U)START_PIC_sdram, 60+5*64+8, 480-64-2, (pInt16U)SDRAM0_BASE_ADDR); //显示开机画面

FileFolderRead("Clock_64x64.bmp",(unsigned char*)START_PIC_sdram);//读开机画面
Bmp_Decode((Int32U)START_PIC_sdram, 60+6*64+8, 480-64-2, (pInt16U)SDRAM0_BASE_ADDR); //显示开机画面

//cpGui_ChangeText(&PictureBox1.ImageName,"F1标签.bmp");
//cpGui_CreatePictureBox(&PictureBox1);
		
}
