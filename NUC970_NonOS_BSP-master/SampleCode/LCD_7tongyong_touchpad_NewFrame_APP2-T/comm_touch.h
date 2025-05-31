

#ifndef  _COMM_TOUCH_H
#define  _COMM_TOUCH_H


#include "touch.h"


#define	TOU_AD_MAX	2040
#define	TOU_AD_MIN	20


extern Int16U TouDownLongTime;

void Comm_TouchScr(Int8U data);

void TouchScan_Uart(void);





#endif
