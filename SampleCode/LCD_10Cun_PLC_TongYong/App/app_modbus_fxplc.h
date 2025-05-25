#ifndef _APP_MODBUS_FXPLC_H
#define _APP_MODBUS_FXPLC_H

#include "main.h"


#define M_BASE_ADDD 0x0000


#define APP_MODBUS_PLC 1


extern unsigned char  Modbus_PLC_Link_Flag;
extern int Modbus_PlcTimeOut;


//–¥M√¸¡Ó  ÷–∂œ÷––¥£¨≤ª“™≤È—Ø√¸¡Ó
void App_Modbus_FXPlc_M_CTRL_Interrupt(char *msta,unsigned int madd);


void App_Modbus_FXPlc_AutoCnt_Check(void);

//–¥M√¸¡Ó
void App_Modbus_FXPlc_M_CTRL(char *msta,unsigned int madd);

//–¥D√¸¡Ó
void App_Modbus_FXPlc_D_Write(unsigned int dadd,unsigned int ddata);


//Õ®∂¡≥¨ ±ºÏ≤‚
void App_Modbus_PLC_TimeOut(void);


#endif

