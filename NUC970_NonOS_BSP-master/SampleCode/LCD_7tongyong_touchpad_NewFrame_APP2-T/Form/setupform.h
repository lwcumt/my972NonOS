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

extern TEXTBOX ServerTextBox;
extern TEXTBOX ServerPortTextBox;
extern TEXTBOX TimeYearTextBox;
extern TEXTBOX TimeMonthTextBox;
extern TEXTBOX TimeDayTextBox;
extern TEXTBOX TimeHourTextBox;
extern TEXTBOX TimeMinuteTextBox;

	

extern void SetupFormInit(void);
extern void SetupForm_Event(TOUCH touch);


#endif
