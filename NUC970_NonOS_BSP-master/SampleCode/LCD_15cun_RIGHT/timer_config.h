#ifndef _TIMER_CONFIG_H
#define _TIMER_CONFIG_H


#include "main.h"

extern void ETMR0_IRQHandler(void);
extern void ETMR1_IRQHandler(void);

extern void Timer0_Config(void);
extern void Timer1_Config(void);

extern void ETimer0_Close(void);
extern void ETimer1_Close(void);


#endif
