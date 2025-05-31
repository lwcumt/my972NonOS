#ifndef _LCD_BRIGHT_H
#define _LCD_BRIGHT_H


#include "main.h"
//#include "sys.h"
#include "uart.h"
#include"drv_glcd.h"

#include "pcf8563.h"
#include "touch.h"



#define LCD_BRI_PWM_DDR  GPIOHD
#define LCD_BRI_PWM_IO GPIOD

#define LCD_BRI_PWM_PIN BIT14
#define LCD_BRI_PWM_IO_SET() (GPIO_OpenBit(LCD_BRI_PWM_IO, LCD_BRI_PWM_PIN, DIR_OUTPUT, NO_PULL_UP))


#define LCD_BRI_PWM_LOW() (GPIO_ClrBit(LCD_BRI_PWM_IO, LCD_BRI_PWM_PIN))
#define LCD_BRI_PWM_HIGH() (GPIO_SetBit(LCD_BRI_PWM_IO, LCD_BRI_PWM_PIN))


void Lcd_SetBirght(unsigned char percentage);
//void Lcd_Bri_Pwm_Init(INT timer_num);


#endif
