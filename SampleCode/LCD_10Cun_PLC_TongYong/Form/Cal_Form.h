#ifndef _CAL_FORM_H
#define _CAL_FORM_H

#include "main.h"
#include "datagui.h"
#include "pic_exec.h"
#include "drv_glcd.h"

#include "key.h"
#include "touch.h"
#include "tsc2046.h"
#include "gtp.h"
#include "pic_exec.h"
#include "timer.h"

extern uint8_t Cal_Form_Show_Flag;

void CAL_Form_LoadPic(void);
void CAL_Form_Init(void);

//ÊÂ¼þ
void Cal_Form_Event(TOUCH touch);

void Cal_Form_Manual_Exit(void);


#endif
