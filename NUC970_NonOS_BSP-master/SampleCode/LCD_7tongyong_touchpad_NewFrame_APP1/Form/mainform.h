#ifndef _SETUP_FORM_H
#define _SETUP_FORM_H

#include "main.h"
#include "datagui.h"
#include "pic_exec.h"
#include "drv_glcd.h"

#include "key.h"
#include "touch.h"
#include "tsc2046.h"
#include "gtp.h"
#include "pic_exec.h"
#include "comm_touch.h"

extern TEXTBOX ServerTextBox;
extern TEXTBOX ServerPortTextBox;
extern TEXTBOX TimeYearTextBox;
extern TEXTBOX TimeMouthTextBox;
extern TEXTBOX TimeDayTextBox;
extern TEXTBOX TimeHourTextBox;
extern TEXTBOX TimeMinuteTextBox;

	

extern void MainFormInit(void);
extern void Test_Main(void);
extern void RealTime_Dis(void);

extern void MainForm_Event(TOUCH touch);



#endif
