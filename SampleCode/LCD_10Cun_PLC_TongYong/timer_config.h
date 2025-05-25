#ifndef _TIMER_CONFIG_H
#define _TIMER_CONFIG_H


#include "main.h"

void ETMR0_IRQHandler(void);
void ETMR1_IRQHandler(void);
void ETMR2_IRQHandler(void);

void Timer0_Config(void);
void Timer1_Config(void);
void Timer2_Config(void);

void ETimer0_Close(void);
void ETimer1_Close(void);
void ETimer2_Close(void);



#endif
