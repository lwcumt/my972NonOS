#include "lcd_bright.h"
//#include "nuc970.h"

//#include "sys.h"
//#include "pwm.h"




unsigned char LcdBrightPwm=0;
unsigned char LcdBrightPwmCou=0;



void Lcd_SetBirght(unsigned char percentage)
{
LCD_BRI_PWM_IO_SET();
LCD_BRI_PWM_HIGH();
//Lcd_Bri_Pwm_Init(PWM_TIMER2);
}







/*
void Lcd_Bri_Pwm_Init(INT timer_num)
{
//	/*
	    typePWMVALUE pwmvalue;
    typePWMSTATUS PWMSTATUS;
  //  INT nLoop=0;
 //   INT nStatus=0;
  //  INT nInterruptInterval=0;
    PWMSTATUS.PDR=0;
    PWMSTATUS.InterruptFlag=FALSE;

	
    pwmInit();
    pwmOpen(timer_num);
	
	    // Change PWM Timer setting
    pwmIoctl(timer_num, SET_CSR, 0, CSRD16);
    pwmIoctl(timer_num, SET_CP, 0, 249);
    pwmIoctl(timer_num, SET_DZI, 0, 0);
    pwmIoctl(timer_num, SET_INVERTER, 0, PWM_INVOFF);
    pwmIoctl(timer_num, SET_MODE, 0, PWM_TOGGLE);
    pwmIoctl(timer_num, DISABLE_DZ_GENERATOR, 0, 0);
    pwmIoctl(timer_num, ENABLE_PWMGPIOOUTPUT, PWM_TIMER2, PWM2_GPA14);
	
    pwmvalue.field.cnr=59999;
    pwmvalue.field.cmr=4999;
    pwmWrite(timer_num, (PUCHAR)(&pwmvalue), sizeof(pwmvalue));

   // sysprintf("PWM Timer%d one shot mode test\nPWM. Timer interrupt will occure soon.", timer_num);

    //Start PWM Timer
    pwmIoctl(timer_num, START_PWMTIMER, 0, 0);

	 //* /
}


*/
