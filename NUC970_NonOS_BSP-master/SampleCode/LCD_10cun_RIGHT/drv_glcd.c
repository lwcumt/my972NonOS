
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "main.h"
#include "sys.h"
#include "string.h"

#include "drv_glcd.h"
#include "file.h"
#include "lcd_config.h"

#define C_GLCD_CLK_PER_LINE     (C_GLCD_H_SIZE + C_GLCD_H_PULSE + C_GLCD_H_FRONT_PORCH + C_GLCD_H_BACK_PORCH)
#define C_GLCD_LINES_PER_FRAME  (C_GLCD_V_SIZE + C_GLCD_V_PULSE + C_GLCD_V_FRONT_PORCH + C_GLCD_V_BACK_PORCH)
#define C_GLCD_PIX_CLK          (36MHZ)





char Bcd[5];

/*************************************************************************
 * Function Name: GLCD_Cursor_Cnfg
 * Parameters:
 *
 * Return: none
 *
 * Description: Configure the cursor
 *
 *************************************************************************/
void GLCD_Cursor_Cfg(int Cfg)
{
//////  CRSR_CFG = Cfg;
}
/*************************************************************************
 * Function Name: GLCD_Cursor_En
 * Parameters: cursor - Cursor Number
 *
 * Return: none
 *
 * Description: Enable Cursor
 *
 *************************************************************************/
void GLCD_Cursor_En(int cursor)
{
//////  CRSR_CTRL_bit.CrsrNum = cursor;
//////  CRSR_CTRL_bit.CrsrOn = 1;
}

/*************************************************************************
 * Function Name: GLCD_Cursor_Dis
 * Parameters: None
 *
 * Return: none
 *
 * Description: Disable Cursor
 *
 *************************************************************************/
void GLCD_Cursor_Dis(int cursor)
{
////  CRSR_CTRL_bit.CrsrOn = 0;
}

/*************************************************************************
 * Function Name: GLCD_Move_Cursor
 * Parameters: x - cursor x position
 *             y - cursor y position
 *
 * Return: none
 *
 * Description: Moves cursor on position (x,y). Negativ values are posible.
 *
 *************************************************************************/
void GLCD_Move_Cursor(int x, int y)
{
//////  if(0 <= x)
//////  {//no clipping
//////    CRSR_CLIP_bit.CrsrClipX = 0;
//////    CRSR_XY_bit.CrsrX = x;
//////  }
//////  else
//////  {//clip x
//////    CRSR_CLIP_bit.CrsrClipX = -x;
//////    CRSR_XY_bit.CrsrX = 0;
//////  }

//////  if(0 <= y)
//////  {//no clipping
//////    CRSR_CLIP_bit.CrsrClipY = 0;
//////    CRSR_XY_bit.CrsrY = y;
//////  }
//////  else
//////  {//clip y
//////    CRSR_CLIP_bit.CrsrClipY = -y;
//////    CRSR_XY_bit.CrsrY = 0;
//////  }
}

/*************************************************************************
 * Function Name: GLCD_Copy_Cursor
 * Parameters: pCursor - pointer to cursor conts image
 *             cursor - cursor Number (0,1,2 or 3)
 *                      for 64x64(size 256) pix cursor always use 0
 *             size - cursor size in words
 * Return: none
 *
 * Description: Copy Cursor from const image to LCD RAM image
 *
 *************************************************************************/
void GLCD_Copy_Cursor (const Int32U *pCursor, int cursor, int size)
{
	int i;
   Int32U * pDst = (Int32U *)LCD_VRAM_BASE_ADDR;
   pDst += cursor*64;

   for(i = 0; i < size ; i++) *pDst++ = *pCursor++;
}
/*************************************************************************
 * 函数: GLCD_Init
 * 参数: 无
 * 返回: 无
 * 描述: 显示屏控制器初始化
 *************************************************************************/
void GLCD_Init (void)
{
	pInt8U u8FrameBufPtr;
// Configure multi-function pin for LCD interface
    //GPG6 (CLK), GPG7 (HSYNC)
    outpw(REG_SYS_GPG_MFPL, (inpw(REG_SYS_GPG_MFPL)& ~0xFF000000) | 0x22000000);
    //GPG8 (VSYNC), GPG9 (DEN)
    outpw(REG_SYS_GPG_MFPH, (inpw(REG_SYS_GPG_MFPH)& ~0xFF) | 0x22);

    //DATA pin
    //GPA0 ~ GPA7 (DATA0~7)
    outpw(REG_SYS_GPA_MFPL, 0x22222222);
    //GPA8 ~ GPA15 (DATA8~15)
    outpw(REG_SYS_GPA_MFPH, 0x22222222);
    //GPD8~D15 (DATA16~23)
   // outpw(REG_SYS_GPD_MFPH, (inpw(REG_SYS_GPD_MFPH)& ~0xFFFFFFFF) | 0x22222222);

    // LCD clock is selected from UPLL and divide to 20MHz
    outpw(REG_CLK_DIVCTL1, (inpw(REG_CLK_DIVCTL1) & ~0xff1f) | 0x818);
		
		
		    // Init LCD interface for E50A2V1 LCD module
    vpostLCMInit(0);
    // Set scale to 1:1
    vpostVAScalingCtrl(1, 0, 1, 0, VA_SCALE_INTERPOLATION);

    // Set display color depth

    vpostSetVASrc(VA_SRC_RGB565);


    // Get pointer of video frame buffer
    // Note: before get pointer of frame buffer, must set display color depth first
    u8FrameBufPtr = Lcd_Set_DisBufAdd(SDRAM0_BASE_ADDR);
    // Start video and OSD
    vpostVAStartTrigger();
  
}

/*************************************************************************
 * 函数: GLCD_ClearBuffer
 * 参数: Int32U BufferBassAddr（显示缓冲区地址）
 * 返回: 无
 * 描述: 清屏
 *************************************************************************/
void GLCD_ClearBuffer(Int32U BufferBassAddr)
{
/*
for(volatile Int32U i = 0; i<C_GLCD_H_SIZE*C_GLCD_V_SIZE*2; i++)
*(volatile Int16U *)(LCD_VRAM_BASE_ADDR + i) = 0xffff;
*/
	 Int32U i ;
   pInt16U p = (pInt16U) malloc(sizeof(Int16U) * C_GLCD_V_SIZE); 
   for(i = 0; i<C_GLCD_V_SIZE; i++)
   p[i]=0xffff;
   for(i= 0; i<C_GLCD_H_SIZE; i++)
   {
   pInt16U sor = (pInt16U) p;
   pInt16U  ptr=(pInt16U)(BufferBassAddr+C_GLCD_V_SIZE*i*2);
   memcpy(ptr,sor,C_GLCD_V_SIZE*2);
   }
    free(p);
}


/*************************************************************************
 * 函数: GLCD_Buffer_Fill
 * 参数: Int16U  color（填充色）
 * 返回: 无
 * 描述: 填充整个屏幕的颜色
 *************************************************************************/
void GLCD_Buffer_Fill(Int16U color)
{
 pInt16U add;
	 Int32U i;
add=(pInt16U)LCD_VRAM_BASE_ADDR;

///*
for(i = 0; i<C_GLCD_H_SIZE*C_GLCD_V_SIZE*2; i++)
*add++=color;
//*(volatile Int16U *)(LCD_VRAM_BASE_ADDR + i) = color;
//*/
  /*
  pInt16U p = (pInt16U) malloc(sizeof(Int16U) * C_GLCD_V_SIZE); 
   for(volatile Int32U i = 0; i<C_GLCD_V_SIZE; i++)
   p[i]=color;
   for(volatile Int32U i = 0; i<C_GLCD_H_SIZE; i++)
   {
   pInt16U sor = (pInt16U) p;
   pInt16U  ptr=(pInt16U)(LCD_VRAM_BASE_ADDR+C_GLCD_V_SIZE*i*2);
   memcpy(ptr,sor,C_GLCD_V_SIZE*2);
   }
   free(p);*/
}


/*************************************************************************
 * 函数: DrawLine
 * 参数: Int32U x1（起点X）,Int32U y1（起点Y）,Int32U x2（终点X）,Int32U y2（终点Y）,Int16U color（颜色）
 * 返回: 无
 * 描述: 绘制直线
 *************************************************************************/
 void DrawLine(Int32S x1,Int32S y1,Int32S x2,Int32S y2,Int16U color)
 {
	  Int32U i ;
 if(x1==x2)
 {
     if(y2>=y1)
     {
         for(i = y1; i<=y2; i++)
         PutPixel(x1,i,color);
     }
     else
     {
         for(i = y2; i<=y1; i++)
         PutPixel(x1,i,color);
     }
 }
 else
 {
     if(y1==y2)
	 {
	  if(x2>=x1)
     {
         for(i= x1; i<=x2; i++)
         PutPixel(i,y1,color);
     }
     else
     {
         for(i = x2; i<=x1; i++)
         PutPixel(i,y1,color);
     }
	 }
 }
 }
/*************************************************************************
 * 函数: GLCD_DrawLine
 * 参数: Int32U x1（起点X）,Int32U y1（起点Y）,Int32U x2（终点X）,Int32U y2（终点Y）,Int16U color（颜色）
 * 返回: 无
 * 描述: 绘制线条
 *************************************************************************/
 void GLCD_DrawLine(Int32S x1,Int32S y1,Int32S x2,Int32S y2,Int16U color)
 {
 Int32S dx,dy,e;
 if((x1==x2)||(y1==y2))
 {
 DrawLine(x1,y1,x2,y2,color);
 }
 else
 {
	dx=x2-x1;
	dy=y2-y1;

	if(dx>=0)
	{
		if(dy >= 0) // dy>=0
		{
			if(dx>=dy) // 1/8 octant
			{
				e=dy-dx/2;
				while(x1<=x2)
				{
					PutPixel(x1,y1,color);
					if(e>0){y1+=1;e-=dx;}	
					x1+=1;
					e+=dy;
				}
			}
			else		// 2/8 octant
			{
				e=dx-dy/2;
				while(y1<=y2)
				{
					PutPixel(x1,y1,color);
					if(e>0){x1+=1;e-=dy;}	
					y1+=1;
					e+=dx;
				}
			}
		}
		else		   // dy<0
		{
			dy=-dy;   // dy=abs(dy)

			if(dx>=dy) // 8/8 octant
			{
				e=dy-dx/2;
				while(x1<=x2)
				{
					PutPixel(x1,y1,color);
					if(e>0){y1-=1;e-=dx;}	
					x1+=1;
					e+=dy;
				}
			}
			else		// 7/8 octant
			{
				e=dx-dy/2;
				while(y1>=y2)
				{
					PutPixel(x1,y1,color);
					if(e>0){x1+=1;e-=dy;}	
					y1-=1;
					e+=dx;
				}
			}
		}	
	}
	else // <0
	{
		dx=-dx;		// =abs(dx)
		if(dy >= 0) // dy>=0
		{
			if(dx>=dy) // 4/8 octant
			{
				e=dy-dx/2;
				while(x1>=x2)
				{
					PutPixel(x1,y1,color);
					if(e>0){y1+=1;e-=dx;}	
					x1-=1;
					e+=dy;
				}
			}
			else		// 3/8 octant
			{
				e=dx-dy/2;
				while(y1<=y2)
				{
					PutPixel(x1,y1,color);
					if(e>0){x1-=1;e-=dy;}	
					y1+=1;
					e+=dx;
				}
			}
		}
		else		   // dy<0
		{
			dy=-dy;   // dy=abs(dy)

			if(dx>=dy) // 5/8 octant
			{
				e=dy-dx/2;
				while(x1>=x2)
				{
					PutPixel(x1,y1,color);
					if(e>0){y1-=1;e-=dx;}	
					x1-=1;
					e+=dy;
				}
			}
			else		// 6/8 octant
			{
				e=dx-dy/2;
				while(y1>=y2)
				{
					PutPixel(x1,y1,color);
					if(e>0){x1-=1;e-=dy;}	
					y1 = y1-1;
					e+=dx;
				}
			}
		}	
	} 
}	
 }
 
 
 /*************************************************************************
 * 函数: PutPixel
 * 参数: Int32U x（X坐标）,Int32U y（Y坐标）,Int32U color（颜色）
 * 返回: 无
 * 描述: 绘制一个点
 *************************************************************************/
 void PutPixel(Int32U x,Int32U y,Int16U color)
{
    if(x < C_GLCD_H_SIZE && y < C_GLCD_V_SIZE)
      *(volatile Int16U *)(LCD_VRAM_BASE_ADDR + x * 2 + 2*C_GLCD_H_SIZE* y) = color;
}


 /*************************************************************************
 * 函数: GLCD_SetWindow
 * 参数: Int32S x1（起点X坐标）,Int32S y1（起点Y坐标）,Int32S x2（对角点X坐标）,
 *		 Int32S y2（对角点Y坐标）,Int32U Linecolor（线色）
 * 返回: 无
 * 描述: 绘制一个矩形
 *************************************************************************/
 void GLCD_SetWindow(Int32S x1,Int32S y1,Int32S x2,Int32S y2,Int16U Linecolor)
 {
     GLCD_DrawLine(x1,y1,x2,y1,Linecolor);
	 GLCD_DrawLine(x2,y1,x2,y2,Linecolor);
	 GLCD_DrawLine(x2,y2,x1,y2,Linecolor);
	 GLCD_DrawLine(x1,y2,x1,y1,Linecolor);
 }
 /*************************************************************************
 * 函数: GLCD_SetWindow_Fill
 * 参数: Int32S x1（起点X坐标）,Int32S y1（起点Y坐标）,Int32S x2（对角点X坐标）,
 *		 Int32S y2（对角点Y坐标）,Int32U Linecolor（线色）,Int32U Windowcolor（窗体填充色）
 * 返回: 无
 * 描述: 绘制一个矩形并填充
 *************************************************************************/
 void GLCD_SetWindow_Fill(Int32S x1,Int32S y1,Int32S x2,Int32S y2,Int16U Linecolor,Int16U Windowcolor)
 {
	  Int32U i;
	 if(y2!=y1)
	 {
		if(y2>y1)
		{
			for(i = y2-y1-1; i; i--)
			{
				PutBlockColor(x1,x2,y2-i,Windowcolor);
			}
		}
		else
		{
			for(i= y1-y2-1; i; i--)
			{
				PutBlockColor(x1,x2,y1-i,Windowcolor);
			}
		}
		GLCD_DrawLine(x1,y1,x2,y1,Linecolor);
	    GLCD_DrawLine(x2,y1,x2,y2,Linecolor);
	    GLCD_DrawLine(x2,y2,x1,y2,Linecolor);
	    GLCD_DrawLine(x1,y2,x1,y1,Linecolor);
	 }
	 else
	 {
	 }
	 
 }

 
 
  /*************************************************************************
 * 函数: PutBlockColor
 * 参数: Int32S x1（填充线起点）,Int32S x2（填充色终点）,Int32S y（填充Y坐标）,Int16U color（填充色）
 * 返回: 无
 * 描述: 沿X填充线
 *************************************************************************/
void PutBlockColor(Int32S x1,Int32S x2,Int32S y,Int16U color)//LCD_VRAM_BASE_ADDR
{
	pInt16U pBuffer;
	 Int32U i;
	if(x2!=x1)
	{
		if(x2>x1)
		{
			pBuffer = (pInt16U)(((C_GLCD_H_SIZE*y+x1)*2)+2+LCD_VRAM_BASE_ADDR);
			for(i = x2-x1-1; i; i--)
			{
				*pBuffer++ = color;
			}
		}
		else
		{
			pBuffer = (pInt16U)((C_GLCD_H_SIZE*y+x2)*2+LCD_VRAM_BASE_ADDR);
			for(i = x1-x2-1; i; i--)
			{
				*pBuffer++ = color;
			}
		}
	}
	else
	{
	}
}


 /*************************************************************************
 * 函数: GLCD_Circle
 * 参数:Int32S centerx（圆心X坐标）, Int32S centery（圆心Y坐标）, 
 *		Int32U radius（半径）,Int16U Linecolor（圆线色）
 * 返回: 无
 * 描述: 绘制一个不填充的圆形
 *************************************************************************/
void GLCD_Circle(Int32S centerx, Int32S centery, Int32U radius,Int16U Linecolor)//bresenham画圆算法
{
	Int32S x = 0;
	Int32S y = radius;
	Int32S delta = 2*(1-radius);
	Int32S direction;
	while (y >= 0) 
	{
		PutPixel(centerx+x, centery+y, Linecolor);
		PutPixel(centerx-x, centery+y, Linecolor);
		PutPixel(centerx-x, centery-y, Linecolor);
		PutPixel(centerx+x, centery-y, Linecolor);
		if (delta < 0) 
		{
			if ((2*(delta+y)-1) < 0) 
			{
				direction = 1;
			}
			else 
			{
				direction = 2;
			}
		}
		else if(delta > 0) 
		{
			if ((2*(delta-x)-1) <= 0) 
			{
				direction = 2;
			}
			else 
			{
				direction = 3;
			}
		}
		else 
		{
			direction=2;
		}
  
		switch(direction) 
		{
			case 1:
				x++;
				delta += (2*x+1);
			break;
			case 2:
				x++;
				y--;
				delta += 2*(x-y+1);
			break;
			case 3:
				y--;
				delta += (-2*y+1);
			break;
		}

	}
}
  /*************************************************************************
 * 函数: GLCD_Circle_Fill
 * 参数: Int32S centerx（圆心X坐标）, Int32S centery（圆心Y坐标）, Int32U radius（半径）, 
 *		 Int16U Linecolor（圆线色）, Int16U Boardcolor（填充色）
 * 返回: 无
 * 描述: 绘制一个带填充颜色的圆形
 *************************************************************************/
void GLCD_Circle_Fill(Int32S centerx, Int32S centery, Int32U radius, Int16U Linecolor, Int16U Boardcolor)//bresenham画圆算法
{
	Int32S x = 0;
	Int32S y = radius-1;
	Int32S delta = 2*(-radius);
	Int32S direction;
	while (y >= 0)//填充 
	{
		GLCD_DrawLine(centerx+x, centery+y, centerx+x, centery-y, Boardcolor);
		GLCD_DrawLine(centerx-x, centery+y, centerx-x, centery-y, Boardcolor);
		if (delta < 0) 
		{
			if ((2*(delta+y)-1) < 0) 
			{
				direction = 1;
			}
			else 
			{
				direction = 2;
			}
		}
		else if(delta > 0) 
		{
			if ((2*(delta-x)-1) <= 0) 
			{
				direction = 2;
			}
			else 
			{
				direction = 3;
			}
		}
		else 
		{
			direction=2;
		}
  
		switch(direction) 
		{
			case 1:
				x++;
				delta += (2*x+1);
			break;
			case 2:
				x++;
				y--;
				delta += 2*(x-y+1);
			break;
			case 3:
				y--;
				delta += (-2*y+1);
			break;
		}

	}
	
	
	 x = 0;
	 y = radius;
	 delta = 2*(1-radius);
	while (y >= 0)//画外部圆 
	{
		PutPixel(centerx+x, centery+y, Linecolor);
		PutPixel(centerx-x, centery+y, Linecolor);
		PutPixel(centerx-x, centery-y, Linecolor);
		PutPixel(centerx+x, centery-y, Linecolor);
		if (delta < 0) 
		{
			if ((2*(delta+y)-1) < 0) 
			{
				direction = 1;
			}
			else 
			{
				direction = 2;
			}
		}
		else if(delta > 0) 
		{
			if ((2*(delta-x)-1) <= 0) 
			{
				direction = 2;
			}
			else 
			{
				direction = 3;
			}
		}
		else 
		{
			direction=2;
		}
  
		switch(direction) 
		{
			case 1:
				x++;
				delta += (2*x+1);
			break;
			case 2:
				x++;
				y--;
				delta += 2*(x-y+1);
			break;
			case 3:
				y--;
				delta += (-2*y+1);
			break;
		}

	}
}



 /*************************************************************************
 * 函数: GLCD_Triangle
 * 参数:Int32S x1（点1X坐标）,Int32S y1（点1Y坐标）,Int32S x2（点2X坐标）,Int32S y2（点2Y坐标）,
		Int32S x3（点3X坐标）,Int32S y3（点3Y坐标）,Int16U Linecolor（三角线色）
 * 返回: 无
 * 描述: 绘制一个不填充的三角形
 *************************************************************************/
void GLCD_Triangle(Int32S x1,Int32S y1,Int32S x2,Int32S y2,
						Int32S x3,Int32S y3,Int16U Linecolor)
{
	GLCD_DrawLine(x1,y1,x2,y2,Linecolor);
	GLCD_DrawLine(x1,y1,x3,y3,Linecolor);
	GLCD_DrawLine(x3,y3,x2,y2,Linecolor);
}

 /*************************************************************************
 * 函数: GLCD_Triangle
 * 参数:Int32S x1（点1X坐标）,Int32S y1（点1Y坐标）,Int32S x2（点2X坐标）,Int32S y2（点2Y坐标）,
		Int32S x3（点3X坐标）,Int32S y3（点3Y坐标）,Int16U Linecolor（三角线色）,Int16U Boardcolor（填充色）
 * 返回: 无
 * 描述: 绘制一个不填充的三角形
 *************************************************************************/
void GLCD_Triangle_Fill(Int32S x1,Int32S y1,Int32S x2,Int32S y2,
						Int32S x3,Int32S y3,Int16U Linecolor,Int16U Boardcolor)
{
 Int32S dx,dy,e,tempx,tempy,tempx1,tempy1,tempx2,tempy2;
 if((x1==x2)||(y1==y2))
 {
 }
 else
 {
	if((x1==x3)||(y1==y3))
	{
		tempx=x2;
		tempy=y2;
		x2=x3;
		y2=y3;
		x3=tempx;
		y3=tempy;
	}
	else
	{
		if((x2==x3)||(y2==y3))
		{
			tempx=x1;
			tempy=y1;
			x1=x3;
			y1=y3;
			x3=tempx;
			y3=tempy;
		}
		else
		{
		}
	}
 }

	tempx=x3;
	tempy=y3;
	tempx1=x1;
	tempy1=y1;
	tempx2=x2;
	tempy2=y2;
	
	dx=x2-x1;
	dy=y2-y1;
	if(dx>=0)
	{
		if(dy >= 0) // dy>=0
		{
			if(dx>=dy) // 1/8 octant
			{
				e=dy-dx/2;
				while(x1<=x2)
				{
					PutPixel(x1,y1,Linecolor);
					GLCD_DrawLine(x1,y1,x3,y3,Boardcolor);
					if(e>0){y1+=1;e-=dx;}	
					x1+=1;
					e+=dy;
				}
			}
			else		// 2/8 octant
			{
				e=dx-dy/2;
				while(y1<=y2)
				{
					PutPixel(x1,y1,Linecolor);
					GLCD_DrawLine(x1,y1,x3,y3,Boardcolor);
					if(e>0){x1+=1;e-=dy;}	
					y1+=1;
					e+=dx;
				}
			}
		}
		else		   // dy<0
		{
			dy=-dy;   // dy=abs(dy)

			if(dx>=dy) // 8/8 octant
			{
				e=dy-dx/2;
				while(x1<=x2)
				{
					PutPixel(x1,y1,Linecolor);
					GLCD_DrawLine(x1,y1,x3,y3,Boardcolor);
					if(e>0){y1-=1;e-=dx;}	
					x1+=1;
					e+=dy;
				}
			}
			else		// 7/8 octant
			{
				e=dx-dy/2;
				while(y1>=y2)
				{
					PutPixel(x1,y1,Linecolor);
					GLCD_DrawLine(x1,y1,x3,y3,Boardcolor);
					if(e>0){x1+=1;e-=dy;}	
					y1-=1;
					e+=dx;
				}
			}
		}	
	}
	else // <0
	{
		dx=-dx;		// =abs(dx)
		if(dy >= 0) // dy>=0
		{
			if(dx>=dy) // 4/8 octant
			{
				e=dy-dx/2;
				while(x1>=x2)
				{
					PutPixel(x1,y1,Linecolor);
					GLCD_DrawLine(x1,y1,x3,y3,Boardcolor);
					if(e>0){y1+=1;e-=dx;}	
					x1-=1;
					e+=dy;
				}
			}
			else		// 3/8 octant
			{
				e=dx-dy/2;
				while(y1<=y2)
				{
					PutPixel(x1,y1,Linecolor);
					GLCD_DrawLine(x1,y1,x3,y3,Boardcolor);
					if(e>0){x1-=1;e-=dy;}	
					y1+=1;
					e+=dx;
				}
			}
		}
		else		   // dy<0
		{
			dy=-dy;   // dy=abs(dy)

			if(dx>=dy) // 5/8 octant
			{
				e=dy-dx/2;
				while(x1>=x2)
				{
					PutPixel(x1,y1,Linecolor);
					GLCD_DrawLine(x1,y1,x3,y3,Boardcolor);
					if(e>0){y1-=1;e-=dx;}	
					x1-=1;
					e+=dy;
				}
			}
			else		// 6/8 octant
			{
				e=dx-dy/2;
				while(y1>=y2)
				{
					PutPixel(x1,y1,Linecolor);
					GLCD_DrawLine(x1,y1,x3,y3,Boardcolor);
					if(e>0){x1-=1;e-=dy;}	
					y1 = y1-1;
					e+=dx;
				}
			}
		}	
	}
	GLCD_DrawLine(tempx1,tempy1,tempx2,tempy2,Linecolor);
	GLCD_DrawLine(tempx1,tempy1,tempx,tempy,Linecolor);
	GLCD_DrawLine(tempx,tempy,tempx2,tempy2,Linecolor);
}

 /*************************************************************************
 * 函数: GLCD_Display_BMP
 * 参数:pInt8U bmpaddr（BMP图像地址）,Int32U x（显示起点X坐标）,Int32U y（显示起点Y坐标）
 * 返回: 无
 * 描述: 绘制BMP图片
 *************************************************************************/
void GLCD_Display_BMP(pInt16U bmpaddr,Int32U x,Int32U y)
{
	
	 Int32U n;
	 Int32U i;
/*
  struct ST_ImgFileHead    //total 14(0xE) bytes 
{                        //offset,size(byte) 
        Int8S format[2];  // 0x00 , 0x2;  固定为"BM" 
        Int32U file_size;  // 0x02 , 0x4;  整个文件大小;注意是大字节序还是小字节序,实际BMP格式中是小字节序 
        Int16S reserved1;   // 0x06 , 0x2;  保留,必须为0 
		Int16S reserved2;   // 0x08 , 0x2;  保留,必须为0 
        Int32U data_offset;  // 0x0A , 0x4;  图象数据的偏移,看后面的图象信息头的多少定,图象信息头大小
						//为0x28则本字段值为0x36,本字段的值实际上为"图象信息头长度+14+调色板信息长度" 
}ST_ImgFileHead;                                        
                                                                                 
struct ST_ImgInfHead        //total 40(0x28) bytes;  图象信息头 
{                                         
        Int32U img_inf_size;  // 0x0E , 0x4;  图象信息头的大小,
							//基本上是0x28,但也不一定,读取位图的时候这个值最好读出来 
        Int32U width;        // 0x12 , 0x4;  位图宽度,以像素为单位 
        Int32U height;       // 0x16 , 0x4;  位图高度,以像素为单位 
        Int16U  planes;      // 0x1A , 0x2;  位图位平面数,固定为1 
        Int16U  pixel_bit_width;// 0x1C , 0x2;  像素位宽: 1,4,8,16,24,32可选 
        Int32U  compression;  // 0x1E , 0x4;  压缩方式,从枚举的压缩方式中选一种 
        Int32U img_size;     // 0x22 , 0x4;  图象数据大小,以字节为单位,必须是4的倍数 
        Int32U h_resolution;  // 0x26 , 0x4;  水平分辨率,用像素/米表示 
        Int32U v_resolution; // 0x2A , 0x4;  垂直分辨率,用像素/米表示 
        Int32U colors;      // 0x2E , 0x4;  位图使用的颜色数 
        Int32U important;  // 0x32 , 0x4;  指定重要的颜色数,该域的值为颜色总数或者0时表示所有颜色都一样重要 
}ST_ImgInfHead; 
*/
//Int32U data_offset;  // 0x0A , 0x4;  图象数据的偏移,看后面的图象信息头的多少定,图象信息头大小
						//为0x28则本字段值为0x36,本字段的值实际上为"图象信息头长度+14+调色板信息长度"
Int16U width;        // 0x12 , 0x4;  位图宽度,以像素为单位 
Int16U height;       // 0x16 , 0x4;  位图高度,以像素为单位 
//Int16U pixel_bit_width;// 0x1C , 0x2;  像素位宽: 1,4,8,16,24,32可选
//Int32U compression;
//Int16U color;
//Int32S ytemp;
//ytemp=y;
/*
data_offset = *(bmpaddr + 0x0d);
data_offset <<= 8;
data_offset = *(bmpaddr + 0x0c);
data_offset <<= 8;
data_offset = *(bmpaddr + 0x0b);
data_offset <<= 8;
data_offset = *(bmpaddr + 0x0a);

width = *(bmpaddr + 0x15);
width <<= 8;
width = *(bmpaddr + 0x14);
width <<= 8;
width = *(bmpaddr + 0x13);
width <<= 8;
width = *(bmpaddr + 0x12);

height = *(bmpaddr + 0x19);
height <<= 8;
height = *(bmpaddr + 0x18);
height <<= 8;
height = *(bmpaddr + 0x17);
height <<= 8;
height = *(bmpaddr + 0x16);

pixel_bit_width = *(bmpaddr + 0x1d);
pixel_bit_width <<= 8;
pixel_bit_width += *(bmpaddr + 0x1c);

compression = *(bmpaddr + 0x21);
compression <<= 8;
compression = *(bmpaddr + 0x20);
compression <<= 8;
compression = *(bmpaddr + 0x1f);
compression <<= 8;
compression = *(bmpaddr + 0x2e);
*/
height = *bmpaddr++;

width = *bmpaddr++;

//pInt16U p = (pInt16U) malloc(sizeof(Int16U) * width);//开辟图像一行的堆空间
	for( i =y; i<height+y; i++)//height 为高度，height控制显示行数，ytemp控制当前y坐标
	{
		//pInt16U sor = (pInt16U) p;//定义一行图像的源内存空间
		pInt16U ptr = (pInt16U)(LCD_VRAM_BASE_ADDR+(C_GLCD_H_SIZE*i+x)*2);//定义一行图像的目的空间
		for( n =0; n < width; n++)//复制一行的数据
	    {
			*ptr++=*bmpaddr++;//把数据放到开辟的堆空间   *bmpaddr++
	    }
		//memcpy(ptr,sor,sizeof(Int16U) * width);
	}
//free(p);
/*
if(pixel_bit_width==0x0010)//16位色
{
    if(compression==0x0003)//5:6:5
    {
       Int32U m;
       Int32U n;
	   pInt16U p = (pInt16U) malloc(sizeof(Int16U) * width);//开辟图像一行的堆空间 
	    for( m = height; m; m--,ytemp++)
	    {
			pInt16U sor = (pInt16U) p;
			pInt16U ptr = (pInt16U)(LCD_VRAM_BASE_ADDR+(C_GLCD_H_SIZE*ytemp+x)*2);
	        for(  n =0; n < width; n++)
	        {
			    color = *(bmpaddr + data_offset + ((m-1)*width+n)*2+1);
                color <<=8;
                color = *(bmpaddr + data_offset + ((m-1)*width+n)*2);
				p[n]=color;
	        }
			memcpy(ptr,sor,sizeof(Int16U) * width);
	    }
		free(p);
    }
    else//1:5:5:5
    {
       Int32U m;
       Int32U n;
       Int32U colortemp1;
       Int32U colortemp2;
	   pInt16U p = (pInt16U) malloc(sizeof(Int16U) * width);//开辟图像一行的堆空间
		for( m = height; m; m--,ytemp++)//height 为高度，height控制显示行数，ytemp控制当前y坐标
	    {
			pInt16U sor = (pInt16U) p;//定义一行图像的源内存空间
			pInt16U ptr = (pInt16U)(LCD_VRAM_BASE_ADDR+(C_GLCD_H_SIZE*ytemp+x)*2);//定义一行图像的目的空间
			for(  n =0; n < width; n++)//复制一行的数据
	        {
			    color = *(bmpaddr + data_offset + ((m-1)*width+n)*2+1);//读取高字节数据 
                color <<=9;
                colortemp1 = *(bmpaddr + data_offset+ ((m-1)*width+n)*2);//读取低字节数据 
			    colortemp2 = colortemp1;
				colortemp2 &=0x3e0;
				colortemp2 <<=1;
				colortemp2 +=colortemp1&0x1f;
				color += colortemp2;
				p[n]=color;//把数据放到开辟的堆空间
	        }
			memcpy(ptr,sor,sizeof(Int16U) * width);
	    }
		free(p);
    }
}
else
{
}
*/
}


//函数名称:LCD_PutAscii
//功能:显示一个ASCII码
//参数:*HzData  ASCII码数据;StartX,StartY ASCII 字符显示起始坐标;LineColor字符颜色;FillColor背景颜色
//返回值:无
//修改历史:
//版本 	日期	作者	改动内容及原因
//V1.0 2008.1.11	MAGICOE 基本功能完成
void LCD_PutAscii(pInt8U HzData,Int32U StartX,Int32U StartY,Int32U LineColor,Int32U FillColor)
{
	Int8U i,j,m;
	Int32U temp;
	pInt8U HzDataTemp;
	Int32U OffSet;
	Int32U Ch1;

	//Ch1 = *HzData;
	//OffSet = (Ch1 - 32)*16;	
	//HzDataTemp = (pInt8U)asciidot + OffSet;

	pInt16U char_wr_ptr = (pInt16U)LCD_VRAM_BASE_ADDR;
	char_wr_ptr = char_wr_ptr + (StartY-1)*C_GLCD_V_SIZE + StartX - 1;	

	for(j=0; j<16; j++)
	{
		for(i=0; i<1; i++)
		{	
			temp = 0x0000;    
			//temp |= *(HzData++) << 8;
			temp |= *(HzData++);
			for(m=0; m<8; m++)
			{
				if((temp >> m)&0x01)		
				*char_wr_ptr++ = LineColor;
				else						
				*char_wr_ptr++ = FillColor; 

			}
			//HzDataTemp = HzDataTemp + 1;
		}
		StartY++;
		char_wr_ptr = (pInt16U)LCD_VRAM_BASE_ADDR;
		char_wr_ptr = char_wr_ptr + (StartY-1)*C_GLCD_V_SIZE + StartX - 1;			
	}	
}


//函数名称:LCD_PutHz
//功能:显示一个汉字
//参数:*HzData汉字数据;StartX,StartY汉字显示起始坐标;LineColor汉字颜色;FillColor背景颜色
//返回值:无
//修改历史:
//版本 	日期	作者	改动内容及原因
//V1.0 2008.1.11	MAGICOE 基本功能完成
void LCD_PutHz(pInt8U HzData,Int32U StartX,Int32U StartY,Int32U LineColor,Int32U FillColor)
{
	Int8U i,j,m;
	Int32U temp;
	pInt16U char_wr_ptr;
	char_wr_ptr =(pInt16U)( LCD_VRAM_BASE_ADDR + (StartY*C_GLCD_H_SIZE + StartX)*2);
		
	for(j=0; j<16; j++)
	{
		for(i=0; i<2; i++)
		{	
			temp = 0x0000;    
			temp = *HzData;
			for(m=0; m<8; m++)
			{
				if(temp&0x01)		

				*char_wr_ptr++ = LineColor;
				else						
				char_wr_ptr++ ;//= FillColor;
				temp>>=1;
			}
			HzData = HzData ++;
		}
		StartY++;
		char_wr_ptr = (pInt16U)LCD_VRAM_BASE_ADDR;
		char_wr_ptr = char_wr_ptr + (StartY-1)*C_GLCD_H_SIZE + StartX - 1;				
	}
}

void DrawString(pInt8U HzData,Int32U StartX,Int32U StartY,Int32U LineColor,Int32U FillColor)
{

	while(1)
	{
		if (*HzData == 0)
		{
			return;
		}
		if (*HzData > 0x80)			//汉字
		{
	   		LCD_PutHz(HzData,StartX,StartY,LineColor,FillColor);
			StartX += 16;
			HzData += 2; 
			if (StartX >= 472) {StartX = 0; StartY += 16;} 
			if (StartY == 272) {StartY = 0;} 			
		}
		else   						//英文字符
		{
			LCD_PutAscii(HzData,StartX,StartY,LineColor,FillColor);
			StartX += 8;
			HzData += 1;
			if (StartX >= 476) {StartX = 0; StartY += 16;}   
			if (StartY == 272) {StartY = 0;}  			
		}
	}
}


void LoadNumber(char n,int x,int y)
	  {
//	   int i;
	  DrawPic_SDRAM(n*BASESECTORSIZE*528,x,y,48,64);
	  }

void LoadNumber1632(char n,int x,int y)
	{
	DrawPic_SDRAM((n+NUM1632_RED_ADD)*BASESECTORSIZE*528,x,y,16,32);
	}

void LoadNumber2448(char n,int x,int y)
	{
	DrawPic_SDRAM((n+NUM2448_BALCK_ADD)*BASESECTORSIZE*528,x,y,24,48);
	}

void LoadNumber2448H(char n,int x,int y)
	{
	DrawPic_SDRAM((n+NUM2448_RED_ADD)*BASESECTORSIZE*528,x,y,24,48);
	}

void LoadNumber3264(char n,int x,int y)
	{
	DrawPic_SDRAM((n+NUM3264_ADD)*BASESECTORSIZE*528,x,y,32,64);
	}





void LoadHG(int x,int y)
{
DrawPic_SDRAM(HENGGANG_ADD*528,x,y,16,32);

}

void LoadMH(int x,int y)
{
DrawPic_SDRAM(MAOHAO_ADD*528,x,y,16,32);
}

void LoadDH16(int x,int y)
{
DrawPic_SDRAM(DOT1632_ADD*528,x,y,16,32);
}
void LoadDH24(int x,int y)
{
DrawPic_SDRAM(DOT2448_ADD*528,x,y,24,48);
}

void Loaddao(int x,int y)
{
DrawPic_SDRAM(DAO_ADD*528,x,y,48,48);

}

void Loadzhishi(int x,int y)
{
DrawPic_SDRAM(SHOUZHI_ADD*528,x,y,48,48);

}

void Loadtui(int x,int y)
{
DrawPic_SDRAM(TUIZHI_ADD*528,x,y,48,48);

}

void Loadkong(int x,int y)
{
DrawPic_SDRAM(KONGBAI_ADD*528,x,y,48,48);

}


void Loaddaoup(int x,int y)
{
DrawPic_SDRAM(DAOSHANG_ADD*528,x,y,48,48);

}

void Loaddaodown(int x,int y)
{
DrawPic_SDRAM(DAOXIA_ADD*528,x,y,48,48);

}


void Loadyazhiup(int x,int y)
{
DrawPic_SDRAM(YASHANG_ADD*528,x,y,48,48);

}

void Loadyazhidown(int x,int y)
{
DrawPic_SDRAM(YAXIA_ADD*528,x,y,48,48);

}


   


/*
#define SHOUZHANG_ADD 660
#define BEIJING_ADD 670
#define REDDAO_ADD 680
#define LUDAO_ADD 690*/

