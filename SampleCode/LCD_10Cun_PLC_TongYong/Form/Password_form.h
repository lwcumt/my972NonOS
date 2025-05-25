#ifndef _PASSWORD_FORM_H
#define _PASSWORD_FORM_H

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


#define USER_PASSWORD "688882"

extern uint8_t Password_Form_Show_Flag;

extern uint8_t Machine_Set_UserCount_Flag;
extern uint32_t Machine_Set_UserCount_Time;

void Password_Form_Init(void);
void Password_Form_Label_ChangeText(void);
void Password_SetForm_Enter_Event(TOUCH touch);

void Password_Form_Event(TOUCH touch);

#endif
