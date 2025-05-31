
#ifndef TIMER_H
#define TIMER_H

#include"drv_glcd.h"
//#include"board.h"
#define EXTMODE1 1
#define EXTPOLAR1 1
#define EINT1 1


extern  unsigned char  chengxu_Flag,xianshi_Flag, flagyqjixian, flagyzjixian, flagyhjixian;

extern int chengxuTime,xianshitime,labatime;

extern  unsigned long int dem;
extern char flagone;
extern Int32U MsTime;
extern char Ms_Flag, sysflag;
extern  unsigned char a,b,xa,xb,xa1,xb1,xz,xs,senor;
extern   unsigned  long int  muqiancn,xsmuqiancn,yuandiancn; ;
extern  unsigned  char chushihua,flaglaba,flagqianjin,flaghoutui,flaghq,daowei,tmpzidong;
//extern  unsigned  char chushihua;  
extern Int32U sys_tick;

extern Int32U Current_last;
extern Int32U MotorSpeed;
extern Int8U ToTargetStop_flag;

extern Int8U CutEnBegin_flag;
extern Int16U CutDelayTime;

extern Int8U FreqMotorStop_flag;

extern unsigned char  flagbeep;
extern Int8U flagshoulun;



extern Int32U waitTemp[120];
extern Int8U LowerAC_SPD_flag;
extern unsigned int const  waitTb1[120],waitTb2[120],waitTb3[120],waitTb4[120],waitTb5[120],waitTb6[120],waitTb7[120],waitTb8[120],
                          waitTb9[120],waitTb10[120],waitTb11[120],waitTb12[120],waitTb13[120],waitTb14[120],waitTb15[120],waitTb16[120],waitTb17[120],waitTb18[120],
                          waitTb19[120],waitTb20[120],waitTb21[120],waitTb22[120],waitTb23[120],waitTb24[120],waitTb25[120],waitTb26[120],waitTb27[120];

void TMR0_IRQHandler(void);  //定时器0中断ISR
void Timer0Init(void);   //定时器0初始化
void Timer0Disable(void);  //定时器0禁止

void TMR1_IRQHandler(void);  //定时器1中断ISR	
void Timer1Init(void);		//定时器1初始化
void Timer1Disable(void);  //定时器1禁止

void ExtInt1IntrHandler(void);  //外部中断ISR
void ExtInt1Init(void);  //外部中断初始化


#endif














/*
#ifndef TIMER_H
#define TIMER_H

void Timer0IntrHandler(void);
void Timer0Init(void);

#endif
*/