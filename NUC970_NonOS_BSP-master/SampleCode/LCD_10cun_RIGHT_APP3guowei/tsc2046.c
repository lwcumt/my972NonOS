
#include "tsc2046.h"

TOUCH TouchAD;



void delays(Int32U d)
{
while(d--);
}


void TouchInit(void)
{
 TOUCH_CS_DIROUT;
 TOUCH_DIS();
 
 TOUCH_INT_IN;//Pen输入
 //ADS7843_busy_in;
  BUSY_DIRIN;
  
//////  SPITOUCH_MO_OUT;
//////  SPITOUCH_SCK_OUT;
//////  SPITOUCH_MI_IN;
}

/*
Int8U TchScr_Get(void)
{
//获得触摸点坐标
Int32U temp,tou_temp[10];
Int16U x,y,max_temp,min_temp;
Int8U t,min=0,max=0,dd=50;

TOUCH_EN();//打开
delays(dd);//-------------------------------------------------------------------X
for(t=0;t<10;t++)//采样8次
	{
	SpiTranserByte(TOU_GET_X);
	delays(dd);
	temp=SpiTranserByte(0);//读取采样值高8位
	temp<<=5;
	temp|=(SpiTranserByte(0)>>3)&0x0f;//读取采样值低4位
	tou_temp[t]=temp;
	if(t==0)
		{
		max_temp=temp;
		min_temp=temp;
		}
	else
		{
		if(temp>max_temp)
			{
			max_temp=temp;
			max=t;
			}
		if(temp<min_temp)
			{
			min_temp=temp;
			min=t;
			}
		}
	}
if(max!=min)
	{
	for(t=0,temp=0;t<10;t++)
		{
		if((t!=max)&&(t!=min))
			temp+=tou_temp[t];
		}
	TouchAD.x=temp>>3;
	}
else
	TouchAD.x=temp;
if((TouchAD.x>TOUCH_MAX)||(TouchAD.x<TOUCH_MIN))
	return 0;
//-------------------------------------------------------------------Y
for(t=0;t<10;t++)//采样8次
	{
	SpiTranserByte(TOU_GET_Y);
	delays(dd);
	temp=SpiTranserByte(0);//读取采样值高8位
	temp<<=5;
	temp|=(SpiTranserByte(0)>>3)&0x0f;//读取采样值低4位
	tou_temp[t]=temp;
	if(t==0)
		{
		max_temp=temp;
		min_temp=temp;
		}
	else
		{
		if(temp>max_temp)
			{
			max_temp=temp;
			max=t;
			}
		if(temp<min_temp)
			{
			min_temp=temp;
			min=t;
			}
		}
	}
if(max!=min)
	{
	for(t=0,temp=0;t<10;t++)
		{
		if((t!=max)&&(t!=min))
			temp+=tou_temp[t];
		}
	TouchAD.y=temp>>3;
	}
else
	TouchAD.y=temp;
if((TouchAD.y>TOUCH_MAX)||(TouchAD.y<TOUCH_MIN))
	return 0;	
//-------------------------------------------------Z1
for(t=0;t<10;t++)//采样8次
	{
	SpiTranserByte(TOU_GET_Z1);
	delays(dd);
	temp=SpiTranserByte(0);//读取采样值高8位
	temp<<=5;
	temp|=(SpiTranserByte(0)>>3)&0x0f;//读取采样值低4位
	tou_temp[t]=temp;
	if(t==0)
		{
		max_temp=temp;
		min_temp=temp;
		}
	else
		{
		if(temp>max_temp)
			{
			max_temp=temp;
			max=t;
			}
		if(temp<min_temp)
			{
			min_temp=temp;
			min=t;
			}
		}
	}
if(max!=min)
	{
	for(t=0,temp=0;t<10;t++)
		{
		if((t!=max)&&(t!=min))
			temp+=tou_temp[t];
		}
	TouchAD.z1=temp>>3;
	}
else
	TouchAD.z1=temp;	
if((TouchAD.z1>TOUCH_MAX)||(TouchAD.z1<TOUCH_MIN))
	return 0;	
//-------------------------------------------------
for(t=0;t<10;t++)//采样8次
	{
	SpiTranserByte(TOU_GET_Z2);
	delays(dd);
	temp=SpiTranserByte(0);//读取采样值高8位
	temp<<=5;
	temp|=(SpiTranserByte(0)>>3)&0x0f;//读取采样值低4位
	tou_temp[t]=temp;
	if(t==0)
		{
		max_temp=temp;
		min_temp=temp;
		}
	else
		{
		if(temp>max_temp)
			{
			max_temp=temp;
			max=t;
			}
		if(temp<min_temp)
			{
			min_temp=temp;
			min=t;
			}
		}
	}
if(max!=min)
	{
	for(t=0,temp=0;t<10;t++)
		{
		if((t!=max)&&(t!=min))
			temp+=tou_temp[t];
		}
	TouchAD.z2=temp>>3;
	}
else
	TouchAD.z2=temp;	
if((TouchAD.z2>TOUCH_MAX)||(TouchAD.z2<TOUCH_MIN))
	return 0;	
TOUCH_DIS();
if((TouchAD.x>TouchAD.z2)||(TouchAD.x<TouchAD.z1))
	return 0;
else
	return 1;
}
*/

 /*****
Int8U TouchAD_get(void)
{//获得触摸点坐标
// Flo64 rati;
Int16U zz,x_z,z_y;
Int32U temp,tou_temp[10];
Int16U x,y,max_temp,min_temp;
Int8U t,min=0,max=0,dd=10;

// while(SPI0_SEL_PIN==0); 
// //-----------关闭片内spi

// PCONP_bit.PCSSP0= 1;
// SSP0CR1_bit.SSE =0;//1:SSP使能  
// PCONP_bit.PCSSP0= 0;  
// PINSEL0 = PINSEL0&BIN32(00111111,11111111,11111111,11111111);
// PINSEL1 = PINSEL1&BIN32(11111111,11111111,11111111,11000011);
// SPI0_SCK_CLR;delays(50);

 //---------------------
TOUCH_EN();//打开
delays(30);//-------------------------------------------------------------------X
for(t=0;t<10;t++)//采样8次
	{
	SpiTouch_writeB(TOU_GET_X);
	delays(dd);
	temp=SpiTouch_read();//读取采样值12位
	tou_temp[t]=temp;
	if(t==0)
		{
		max_temp=temp;
		min_temp=temp;
		}
	else
		{
		if(temp>max_temp)
			{
			max_temp=temp;
			max=t;
			}
		if(temp<min_temp)
			{
			min_temp=temp;
			min=t;
			}
		}
	}
if(max!=min)
	{
	for(t=0,temp=0;t<10;t++)
		{
		if((t!=max)&&(t!=min))
			temp+=tou_temp[t];
		}
	TouchAD.x=temp>>3;
	}
else
	TouchAD.x=temp;
if((TouchAD.x>TOUCH_MAX)||(TouchAD.x<TOUCH_MIN))
	{
	TOUCH_DIS();
	return 0;
	}
//-------------------------------------------------------------------Y
for(t=0;t<10;t++)//采样8次
	{
	SpiTouch_writeB(TOU_GET_Y);
	delays(dd);
	temp=SpiTouch_read();//读取采样值12位
	tou_temp[t]=temp;
	if(t==0)
		{
		max_temp=temp;
		min_temp=temp;
		}
	else
		{
		if(temp>max_temp)
			{
			max_temp=temp;
			max=t;
			}
		if(temp<min_temp)
			{
			min_temp=temp;
			min=t;
			}
		}
	}
if(max!=min)
	{
	for(t=0,temp=0;t<10;t++)
		{
		if((t!=max)&&(t!=min))
			temp+=tou_temp[t];
		}
	TouchAD.y=temp>>3;
	}
else
	TouchAD.y=temp;
if((TouchAD.y>TOUCH_MAX)||(TouchAD.y<TOUCH_MIN))
	{
	TOUCH_DIS();
	return 0;
	}	
//-------------------------------------------------Z1
for(t=0;t<10;t++)//采样8次
	{
	SpiTouch_writeB(TOU_GET_Z1);
	delays(dd);
	temp=SpiTouch_read();//读取采样值12位
	tou_temp[t]=temp;
	if(t==0)
		{
		max_temp=temp;
		min_temp=temp;
		}
	else
		{
		if(temp>max_temp)
			{
			max_temp=temp;
			max=t;
			}
		if(temp<min_temp)
			{
			min_temp=temp;
			min=t;
			}
		}
	}
if(max!=min)
	{
	for(t=0,temp=0;t<10;t++)
		{
		if((t!=max)&&(t!=min))
			temp+=tou_temp[t];
		}
	TouchAD.z1=temp>>3;
	}
else
	TouchAD.z1=temp;	
if((TouchAD.z1>TOUCH_MAX)||(TouchAD.z1<TOUCH_MIN))
	{
	TOUCH_DIS();
	return 0;	
	}
//-------------------------------------------------
for(t=0;t<10;t++)//采样8次
	{
	SpiTouch_writeB(TOU_GET_Z2);
	delays(dd);
	temp=SpiTouch_read();//读取采样值12位
	tou_temp[t]=temp;
	if(t==0)
		{
		max_temp=temp;
		min_temp=temp;
		}
	else
		{
		if(temp>max_temp)
			{
			max_temp=temp;
			max=t;
			}
		if(temp<min_temp)
			{
			min_temp=temp;
			min=t;
			}
		}
	}
if(max!=min)
	{
	for(t=0,temp=0;t<10;t++)
		{
		if((t!=max)&&(t!=min))
			temp+=tou_temp[t];
		}
	TouchAD.z2=temp>>3;
	}
else
	TouchAD.z2=temp;	
if((TouchAD.z2>TOUCH_MAX)||(TouchAD.z2<TOUCH_MIN))
	{
	TOUCH_DIS();
	return 0;
	}	
TOUCH_DIS();


if((TouchAD.z2>3500)&&(TouchAD.z1<1000)&&(TouchAD.x<2000)&&(TouchAD.y>3400))
	return 0;
	return 1;
}
***/



Int8U TouchAD_get(void)
{//获得触摸点坐标
// Flo64 rati;
Int16U zz,x_z,z_y;
Int32U temp_x=0,temp_y=0,temp_z1=0,temp_z2=0;
// Int16U x[8],y[8],z1[8],z2[8];
Int8U t,dd=10;

 //---------------------
TOUCH_EN();//打开
delays(20);//-----------------------------------------------------------------
for(t=0;t<8;t++)//采样8次
	{
////////	SpiTouch_writeB(TOU_GET_X);
////////	delays(dd);
////////	temp_x+=SpiTouch_read();//读取采样值12位
	delays(dd);
	//------------------
////////	SpiTouch_writeB(TOU_GET_Y);
////////	delays(dd);
////////	temp_y+=SpiTouch_read();//读取采样值12位
	delays(dd);
	//------------------
////////	SpiTouch_writeB(TOU_GET_Z1);
////////	delays(dd);
////////	temp_z1+=SpiTouch_read();//读取采样值12位
////////	delays(dd);
////////	//------------------
////////	SpiTouch_writeB(TOU_GET_Z2);
////////	delays(dd);
////////	temp_z2+=SpiTouch_read();//读取采样值12位
	delays(dd);
	}
TOUCH_DIS();
//-----------------------------------
TouchAD.x=temp_x>>3;
if((TouchAD.x>TOUCH_MAX)||(TouchAD.x<TOUCH_MIN))
	{
	return 0;
	}
TouchAD.y=temp_y>>3;
if((TouchAD.y>TOUCH_MAX)||(TouchAD.y<TOUCH_MIN))
	{
	return 0;
	}
TouchAD.z1=temp_z1>>3;
if((TouchAD.z1>TOUCH_MAX)||(TouchAD.z1<TOUCH_MIN))
	{
	return 0;
	}
TouchAD.z2=temp_z2>>3;
if((TouchAD.z2>TOUCH_MAX)||(TouchAD.z2<TOUCH_MIN))
	{
	return 0;
	}
TouchAD.zz=TouchAD.z2-TouchAD.z1;
//-------------------------
//rat=(Flo64)TouchAD.x/(Flo64)TouchAD.z1;
if((TouchAD.zz>3200)&&(TouchAD.x>1500)&&(TouchAD.y>1500))//(TouchAD.z1<120))
	return 0;

return 1;
}