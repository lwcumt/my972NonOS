

#ifndef _TSC2046_H
#define _TSC2046_H

#include"main.h"


#define TOU_CS		  BIT4
#define TOUCH_CS_DIROUT (GPIO_OpenBit(GPIOG, TOU_CS, DIR_OUTPUT, NO_PULL_UP))
#define TOUCH_EN()      GPIO_SetBit(GPIOG, TOU_CS)  //´¥ÃþÆ¬Ñ¡
#define TOUCH_DIS()      GPIO_ClrBit(GPIOG, TOU_CS)
//#define TOUCH_CS_PIN  (FIO0PIN&(1ul<<TOU_CS))

#define INT           BIT5
#define TOUCH_INT_IN   (GPIO_OpenBit(GPIOG, INT, DIR_INPUT, NO_PULL_UP))
#define TOUCH_INT_PIN  GPIO_ReadBit(GPIOG,INT)

#define BUSY  BIT4
#define BUSY_DIRIN     (GPIO_OpenBit(GPIOG, BUSY, DIR_INPUT, NO_PULL_UP))
#define BUSY_PIN       GPIO_ReadBit(GPIOG,BUSY)


//-------------------
#define TOU_GET_X	0xD0
#define TOU_GET_Y	0x90

#define TOU_GET_Z1	0xB0
#define TOU_GET_Z2	0xC0


#define LCD_HEIGHT 	C_GLCD_V_SIZE
#define LCD_WIDTH  	C_GLCD_H_SIZE

#define TOUCH_MAX	4050	
#define TOUCH_MIN	80//50	
#define TOUCH_Z1 	120
	

typedef struct
{
Int16U x;
Int16U y;
Int16U z1;
Int16U z2;
//Int16U y_z;
//Int16U x_z;
Int16U zz;
} TOUCH;

extern TOUCH TouchAD;


void TouchInit(void);

Int8U TchScr_Get(void);

#endif