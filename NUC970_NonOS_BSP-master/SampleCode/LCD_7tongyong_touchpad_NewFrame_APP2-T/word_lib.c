
#include"word_lib.h"
#include "string.h"
#include"main.h"

unsigned char HanZi[156];//32*32的汉字缓冲区



//////////////////////////////////
/*
函数：ZK_Read16
参数：*hzp 指向区位码
返回：无
描述：根据读取点阵到指定的数组HanZi中
*/
//////////////////////////////////
void ZK_Read16(unsigned char *hzp)  //读取汉字库中汉字点阵 distype 0:正常 1:反相
{
unsigned char hzk_temp[2];
Int32U Pointer;
hzk_temp[0]=hzp[0];
hzk_temp[1]=hzp[1];
if(hzk_temp[0]>0xa0&&hzk_temp[1]>0xa0)
	{
    hzk_temp[0]=hzk_temp[0]-0xa1;      //计算汉字点阵在字库中的起始地址
    hzk_temp[1]=hzk_temp[1]-0xa1;
    Pointer=hzk_temp[0]*94+hzk_temp[1];
    Pointer=Pointer<<5;
	memcpy(HanZi,(unsigned char*)(Pointer+ZK16_sdram),32);
	}
else
    {                       //****ASCII字符
	}
}

//////////////////////////////////
/*
函数：HZK_Printf16
参数：x,y:汉字显示起始点 color：汉字的颜色 b:是否需要填充色 fillcolor：填充色
返回：无
描述：显示数组HanZi中的点阵到指定位置
*/
//////////////////////////////////
void HZK_Printf16(unsigned int x,unsigned int y,unsigned short int color,
				 unsigned char b,unsigned short int fillcolor)
{
int i;
int j,m;
	unsigned char temp;
	pInt16U ptr;
	pInt8U  psr = HanZi;
		ptr=(pInt16U)(LCD_VRAM_BASE_ADDR + (y*C_GLCD_H_SIZE + x )*2);
		for(j=0; j<16; j++)
			{
			for(i=0; i<2; i++)
				{	    
				temp = *psr++;
				for(m=0; m<8; m++)
					{
					if(temp&0x01)		
						*ptr++ = color;
					else
                    {
                        if(b==0)					
						ptr++;
						else
						*ptr++ = fillcolor;
					}
					temp>>=1;
					}
				}
			y++;
			ptr=(pInt16U)(LCD_VRAM_BASE_ADDR + (y*C_GLCD_H_SIZE + x )*2);		
			}	
}

//////////////////////////////////
/*
函数：ZF_Read16
参数：*hzp 指向区位码
返回：无
描述：根据读取点阵到指定的数组HanZi中
*/
//////////////////////////////////
void ZF_Read16(unsigned char *zfp)  //读取汉字库中汉字点阵 distype 0:正常 1:反相
{
Int32U Pointer;
if(*zfp < 0x80)
	{
    Pointer=*zfp;
    Pointer=Pointer<<4;
	memcpy(HanZi,(unsigned char*)(Pointer+ZF16_sdram),16);
	}
else
    {                       //****ASCII字符
	}
}

//////////////////////////////////
/*
函数：ZF_Printf16
参数：x,y:汉字显示起始点 color：汉字的颜色 b:是否需要填充色 fillcolor：填充色
返回：无
描述：显示数组HanZi中的点阵到指定位置
*/
//////////////////////////////////
void ZF_Printf16(unsigned int x,unsigned int y,unsigned short int color,
				 unsigned char b,unsigned short int fillcolor)
{
int i;
int j,m;
	unsigned char temp;
	pInt16U ptr;
	pInt8U  psr = HanZi;
		ptr=(pInt16U)(LCD_VRAM_BASE_ADDR + (y*C_GLCD_H_SIZE + x )*2);
		for(j=0; j<16; j++)
			{
			for(i=0; i<1; i++)
				{	    
				temp = *psr++;
				for(m=0; m<8; m++)
					{
					if(temp&0x01)		
						*ptr++ = color;
					else
                    {
                        if(b==0)					
						ptr++;
						else
						*ptr++ = fillcolor;
					}
					temp>>=1;
					}
				}
			y++;
			ptr=(pInt16U)(LCD_VRAM_BASE_ADDR + (y*C_GLCD_H_SIZE + x )*2);		
			}	
}


//////////////////////////////////
/*
函数：ZK_Read24
参数：*hzp 指向区位码
返回：无
描述：根据读取点阵到指定的数组HanZi中
*/
//////////////////////////////////
void ZK_Read24(unsigned char *hzp)
{
    unsigned char hzk_temp[2];
    Int32U Pointer;
    hzk_temp[0]=hzp[0];
    hzk_temp[1]=hzp[1];
    if(hzk_temp[0]>0xa0&&hzk_temp[1]>0xa0)
	{
        hzk_temp[0]=hzk_temp[0]-0xa1;      //计算汉字点阵在字库中的起始地址
        hzk_temp[1]=hzk_temp[1]-0xa1;
        Pointer=hzk_temp[0]*94+hzk_temp[1];
        Pointer=Pointer*72;
	    memcpy(HanZi,(unsigned char*)(Pointer+ZK24_sdram),72);
	}
    else
    {                       //****ASCII字符
	}
}
//////////////////////////////////
/*
函数：HZK_Printf24
参数：x,y:汉字显示起始点 color：汉字的颜色 b:是否需要填充色 fillcolor：填充色
返回：无
描述：显示数组HanZi中的点阵到指定位置
*/
//////////////////////////////////
void HZK_Printf24(unsigned int x,unsigned int y,unsigned short int color,
				 unsigned char b,unsigned short int fillcolor)
{
int i;
int j,m;
	unsigned char temp;
	pInt16U ptr;
	pInt8U  psr = HanZi;
		ptr=(pInt16U)(LCD_VRAM_BASE_ADDR + (y*C_GLCD_H_SIZE + x )*2);
		for(j=0; j<24; j++)
			{
			for(i=0; i<3; i++)
				{	    
				temp = *psr++;
				for(m=0; m<8; m++)
					{
					if(temp&0x01)		
						*ptr++ = color;
					else
                    {
                        if(b==0)					
						ptr++;
						else
						*ptr++ = fillcolor;
					}
					temp>>=1;
					}
				}
			y++;
			ptr=(pInt16U)(LCD_VRAM_BASE_ADDR + (y*C_GLCD_H_SIZE + x )*2);		
			}	
}
//////////////////////////////////
/*
函数：ZK_Read24
参数：*hzp 指向区位码
返回：无
描述：根据读取点阵到指定的数组HanZi中
*/
//////////////////////////////////
void ZF_Read24(unsigned char *zfp)  //读取汉字库中汉字点阵 distype 0:正常 1:反相
{
Int32U Pointer;
if(*zfp < 0x80)
	{
    Pointer=*zfp;
    Pointer=Pointer*48;
	memcpy(HanZi,(unsigned char*)(Pointer+ZF24_sdram),48);
	}
else
    {                       //****ASCII字符
	}
}

//////////////////////////////////
/*
函数：HZK_Printf24
参数：x,y:汉字显示起始点 color：汉字的颜色 b:是否需要填充色 fillcolor：填充色
返回：无
描述：显示数组HanZi中的点阵到指定位置
*/

//////////////////////////////////
void ZF_Printf24(unsigned int x,unsigned int y,unsigned short int color,
				 unsigned char b,unsigned short int fillcolor)
{
int i;
int j,m;
	unsigned char temp;
	pInt16U ptr;
	pInt8U  psr = HanZi;
		ptr=(pInt16U)(LCD_VRAM_BASE_ADDR + (y*C_GLCD_H_SIZE + x )*2);
		for(j=0; j<24; j++)
			{
			for(i=0; i<2; i++)
				{	    
				temp = *psr++;
				for(m=0; m<8; m++)
					{
					if(temp&0x01)		
						*ptr++ = color;
					else
                    {
                        if(b==0)					
						ptr++;
						else
						*ptr++ = fillcolor;
					}
					temp>>=1;
					}
				}
			y++;
			ptr=(pInt16U)(LCD_VRAM_BASE_ADDR + (y*C_GLCD_H_SIZE + x )*2);		
			}	
}


//////////////////////////////////
/*
函数：ZK_Read32
参数：*hzp 指向区位码
返回：无
描述：根据读取点阵到指定的数组HanZi中
*/
//////////////////////////////////
void ZK_Read32(unsigned char *hzp)  //读取汉字库中汉字点阵 distype 0:正常 1:反相
{
unsigned char hzk_temp[2];
Int32U Pointer;
hzk_temp[0]=hzp[0];
hzk_temp[1]=hzp[1];
if(hzk_temp[0]>0xa0&&hzk_temp[1]>0xa0)
	{
    hzk_temp[0]=hzk_temp[0]-0xa1;      //计算汉字点阵在字库中的起始地址
    hzk_temp[1]=hzk_temp[1]-0xa1;
    Pointer=hzk_temp[0]*94+hzk_temp[1];
    Pointer=Pointer<<7;
	memcpy(HanZi,(unsigned char*)(Pointer+ZK32_sdram),128);
	}
else
    {                       //****ASCII字符
	}
}


//////////////////////////////////
/*
函数：HZK_Printf32
参数：x,y:汉字显示起始点 color：汉字的颜色 b:是否需要填充色 fillcolor：填充色
返回：无
描述：显示数组HanZi中的点阵到指定位置
*/
//////////////////////////////////
void HZK_Printf32(unsigned int x,unsigned int y,unsigned short int color,
				 unsigned char b,unsigned short int fillcolor)
{
int i;
int j,m;
	unsigned char temp;
	pInt16U ptr;
	pInt8U  psr = HanZi;
		ptr=(pInt16U)(LCD_VRAM_BASE_ADDR + (y*C_GLCD_H_SIZE + x )*2);
		for(j=0; j<32; j++)
			{
			for(i=0; i<4; i++)
				{	    
				temp = *psr++;
				for(m=0; m<8; m++)
					{
					if(temp&0x01)		
						*ptr++ = color;
					else
                    {
                        if(b==0)					
						ptr++;
						else
						*ptr++ = fillcolor;
					}
					temp>>=1;
					}
				}
			y++;
			ptr=(pInt16U)(LCD_VRAM_BASE_ADDR + (y*C_GLCD_H_SIZE + x )*2);		
			}	
}

//////////////////////////////////
/*
函数：ZK_Read32
参数：*hzp 指向区位码
返回：无
描述：根据读取点阵到指定的数组HanZi中
*/
//////////////////////////////////
void ZF_Read32(unsigned char *zfp)  //读取汉字库中汉字点阵 distype 0:正常 1:反相
{
Int32U Pointer;
if(*zfp < 0x80)
	{
    Pointer=*zfp;
    Pointer=Pointer<<6;
	memcpy(HanZi,(unsigned char*)(Pointer+ZF32_sdram),64);
	}
else
    {                       //****ASCII字符
	}
}

//////////////////////////////////
/*
函数：HZK_Printf32
参数：x,y:汉字显示起始点 color：汉字的颜色 b:是否需要填充色 fillcolor：填充色
返回：无
描述：显示数组HanZi中的点阵到指定位置
*/
//////////////////////////////////
void ZF_Printf32(unsigned int x,unsigned int y,unsigned short int color,
				 unsigned char b,unsigned short int fillcolor)
{
int i;
int j,m;
	unsigned char temp;
	pInt16U ptr;
	pInt8U  psr = HanZi;
		ptr=(pInt16U)(LCD_VRAM_BASE_ADDR + (y*C_GLCD_H_SIZE + x )*2);
		for(j=0; j<32; j++)
			{
			for(i=0; i<2; i++)
				{	    
				temp = *psr++;
				for(m=0; m<8; m++)
					{
					if(temp&0x01)		
						*ptr++ = color;
					else
                    {
                        if(b==0)					
						ptr++;
						else
						*ptr++ = fillcolor;
					}
					temp>>=1;
					}
				}
			y++;
			ptr=(pInt16U)(LCD_VRAM_BASE_ADDR + (y*C_GLCD_H_SIZE + x )*2);		
			}	
}




void Printf16(unsigned char *chn,unsigned int x,
              unsigned int y,unsigned short int color,
			  unsigned char b,unsigned short int fillcolor)
{
    unsigned short int xtemp,ytemp;
    xtemp = x;
    ytemp = y;
    unsigned char *p_quwei=chn;
	do{
	
    if(*p_quwei<0x80)
		{
			ZF_Read16(p_quwei);
			ZF_Printf16(xtemp,ytemp,color,b,fillcolor);
			  xtemp += 8;
			  p_quwei++;
		}
		else
		{
			ZK_Read16(p_quwei);
			HZK_Printf16(xtemp,ytemp,color,b,fillcolor);
			xtemp += 16;
			p_quwei++;
			p_quwei++;
		}
	}while(*p_quwei != 0);
}

void Printf24(unsigned char *chn,unsigned int x,
              unsigned int y,unsigned short int color,
			  unsigned char b,unsigned short int fillcolor)
{
    unsigned short int xtemp,ytemp;
    xtemp = x;
    ytemp = y;
    unsigned char *p_quwei=chn;
	do{
	
    if(*p_quwei<0x80)
		{
			ZF_Read24(p_quwei);
			ZF_Printf24(xtemp,ytemp,color,b,fillcolor);
			  xtemp += 12;
			  p_quwei++;
		}
		else
		{
			ZK_Read24(p_quwei);
			HZK_Printf24(xtemp,ytemp,color,b,fillcolor);
			xtemp += 24;
			p_quwei++;
			p_quwei++;
		}
	}while(*p_quwei != 0);
}
void Printf32(unsigned char *chn,unsigned int x,
              unsigned int y,unsigned short int color,
			  unsigned char b,unsigned short int fillcolor)
{
    unsigned short int xtemp,ytemp;
    xtemp = x;
    ytemp = y;
    unsigned char *p_quwei=chn;
	do
		{
		if(*p_quwei<0x80)
			{
			ZF_Read32(p_quwei);
			ZF_Printf32(xtemp,ytemp,color,b,fillcolor);
			  xtemp += 16;
			  p_quwei++;
			}
		else
			{
			ZK_Read32(p_quwei);
			HZK_Printf32(xtemp,ytemp,color,b,fillcolor);
			xtemp += 32;
			p_quwei++;
			p_quwei++;
			}
		}
	while(*p_quwei != 0);
}
