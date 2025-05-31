
#ifndef __TOUCHEVENT_H

#define __TOUCHEVENT_H


#include "main.h"
#include "tsc2046.h"

#include "datagui.h"
#include "setupform.h"
#include "waveform.h"
#include "mainform.h"


#define TOUCH_UP 0
#define TOUCH_DOWN 1

extern BUTTON *EventButton;
extern CHECKBOX *EventCheckBox;
extern TEXTBOX *TextBox;

extern unsigned char EventType;


extern void TouchEvent(TOUCH touch);	
extern void TouchEvent_ObjSetFocus(void);
extern void TouchEvent_ObjAddText(char *text);

#endif
