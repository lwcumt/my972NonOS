


#include"down_status.h"


Int8U Data_HEX[8];

void Number_dis(Int8U num,  Int16U Xp,   Int16U Yp)
{
switch(num)
      {
	  case 0:
	       ASCII_Printf("0",ASCII1632_MODE,ASCII1632_WIDTH,ASCII1632_HIGH,ASCII1632,Xp,Yp,0,0xffff);
		   break;
	  case 1:
	       ASCII_Printf("1",ASCII1632_MODE,ASCII1632_WIDTH,ASCII1632_HIGH,ASCII1632,Xp,Yp,0,0xffff);
		   break;
	  case 2:
	       ASCII_Printf("2",ASCII1632_MODE,ASCII1632_WIDTH,ASCII1632_HIGH,ASCII1632,Xp,Yp,0,0xffff);
		   break;
	  case 3:
	       ASCII_Printf("3",ASCII1632_MODE,ASCII1632_WIDTH,ASCII1632_HIGH,ASCII1632,Xp,Yp,0,0xffff);
		   break;
	  case 4:
	       ASCII_Printf("4",ASCII1632_MODE,ASCII1632_WIDTH,ASCII1632_HIGH,ASCII1632,Xp,Yp,0,0xffff);
		   break;
	  case 5:
	       ASCII_Printf("5",ASCII1632_MODE,ASCII1632_WIDTH,ASCII1632_HIGH,ASCII1632,Xp,Yp,0,0xffff);
		   break;
	  case 6:
	       ASCII_Printf("6",ASCII1632_MODE,ASCII1632_WIDTH,ASCII1632_HIGH,ASCII1632,Xp,Yp,0,0xffff);
		   break;
	  case 7:
	       ASCII_Printf("7",ASCII1632_MODE,ASCII1632_WIDTH,ASCII1632_HIGH,ASCII1632,Xp,Yp,0,0xffff);
		   break;
	  case 8:
	       ASCII_Printf("8",ASCII1632_MODE,ASCII1632_WIDTH,ASCII1632_HIGH,ASCII1632,Xp,Yp,0,0xffff);
		   break;
	  case 9:
	       ASCII_Printf("9",ASCII1632_MODE,ASCII1632_WIDTH,ASCII1632_HIGH,ASCII1632,Xp,Yp,0,0xffff);
		   break;
	  case 0xa:
	       ASCII_Printf("a",ASCII1632_MODE,ASCII1632_WIDTH,ASCII1632_HIGH,ASCII1632,Xp,Yp,0,0xffff);
		   break;
	  case 0xb:
	       ASCII_Printf("b",ASCII1632_MODE,ASCII1632_WIDTH,ASCII1632_HIGH,ASCII1632,Xp,Yp,0,0xffff);
		   break;
	  case 0xc:
	       ASCII_Printf("c",ASCII1632_MODE,ASCII1632_WIDTH,ASCII1632_HIGH,ASCII1632,Xp,Yp,0,0xffff);
		   break;
	  case 0xd:
	       ASCII_Printf("d",ASCII1632_MODE,ASCII1632_WIDTH,ASCII1632_HIGH,ASCII1632,Xp,Yp,0,0xffff);
		   break;
	  case 0xe:
	       ASCII_Printf("e",ASCII1632_MODE,ASCII1632_WIDTH,ASCII1632_HIGH,ASCII1632,Xp,Yp,0,0xffff);
		   break;
	 case 0xf:
	       ASCII_Printf("f",ASCII1632_MODE,ASCII1632_WIDTH,ASCII1632_HIGH,ASCII1632,Xp,Yp,0,0xffff);
		   break;
	  }
}

void Datas_dis(Int32U data,  Int16U Xp,   Int16U Yp)
{
Int8U n,Xn=16;
Int16U X,Y;


Y=Yp;

Data_HEX[0]=(Int8U)data&0x0f;
Data_HEX[1]=(Int8U)(data>>4&0x0f);
Data_HEX[2]=(Int8U)(data>>8&0x0f);
Data_HEX[3]=(Int8U)(data>>12&0x0f);
Data_HEX[4]=(Int8U)(data>>16&0x0f);
Data_HEX[5]=(Int8U)(data>>20&0x0f);
Data_HEX[6]=(Int8U)(data>>24&0x0f);
Data_HEX[7]=(Int8U)(data>>28&0x0f);

for(n=0;n<8;n++)
   {
   X=Xp+Xn*n;
   Number_dis(Data_HEX[7-n],  X,    Y);
   
   }


}


void DownSchedule_dis(Int32U length)
{
GLCD_SetWindow_Fill(310,175,750,220,0xffff,0xffff);
ASCII_Printf("TOTAL",ASCII1632_MODE,ASCII1632_WIDTH,ASCII1632_HIGH,ASCII1632,310,185,0,0xffff);
GLCD_SetWindow(400,175,540,220,0);
Datas_dis(length, 405 , 185  );
ASCII_Printf("NOW",ASCII1632_MODE,ASCII1632_WIDTH,ASCII1632_HIGH,ASCII1632,550,185,0xf800,0xffff);
GLCD_SetWindow(605,175,750,220,0x001f);
}