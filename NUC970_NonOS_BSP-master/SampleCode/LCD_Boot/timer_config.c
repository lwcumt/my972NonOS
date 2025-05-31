#include "timer_config.h"

#include "timer.h"


Int32U SysSec=0;

void ETMR0_IRQHandler(void)
{

Timer0IntrHandler();

/*
	
	  MsTime++;
  if(MsTime>=20)
	{
	 MsTime=0;
	 Ms_Flag=1;
	}
	*/

    // clear timer interrupt flag
    ETIMER_ClearIntFlag(0);
}


void ETMR1_IRQHandler(void)
{

Timer1IntrHandler();

/*
	
  MsTime++;
  if(MsTime>=20)
	{
	 MsTime=0;
	 Ms_Flag=1;
	}
	*/

    // clear timer interrupt flag
    ETIMER_ClearIntFlag(1);
}

void Timer0_Config(void)
{

    outpw(REG_CLK_PCLKEN0, inpw(REG_CLK_PCLKEN0) | (1 << 4)); // Enable ETIMER0 engine clock

    // Set timer frequency to 1HZ
    ETIMER_Open(0, ETIMER_PERIODIC_MODE, 20000);

    // Enable timer interrupt
    ETIMER_EnableInt(0);
    sysInstallISR(HIGH_LEVEL_SENSITIVE | IRQ_LEVEL_1, ETMR0_IRQn, (PVOID)ETMR0_IRQHandler);
    sysSetLocalInterrupt(ENABLE_IRQ);
    sysEnableInterrupt(ETMR0_IRQn);

    // Start Timer 0
    ETIMER_Start(0);

}




void Timer1_Config(void)
{

    outpw(REG_CLK_PCLKEN0, inpw(REG_CLK_PCLKEN0) | (1 << 5)); // Enable ETIMER0 engine clock

    // Set timer frequency to 1HZ
    ETIMER_Open(1, ETIMER_PERIODIC_MODE, 5000);

    // Enable timer interrupt
    ETIMER_EnableInt(1);
    sysInstallISR(HIGH_LEVEL_SENSITIVE | IRQ_LEVEL_1, ETMR1_IRQn, (PVOID)ETMR1_IRQHandler);
    sysSetLocalInterrupt(ENABLE_IRQ);
    sysEnableInterrupt(ETMR1_IRQn);

    // Start Timer 0
    ETIMER_Start(1);

}



void ETimer0_Close(void)
{
ETIMER_Close(0);
}

void ETimer1_Close(void)
{
ETIMER_Close(1);
}

