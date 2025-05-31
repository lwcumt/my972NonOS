
#ifndef _KEYBOARD_H
#define _KEYBOARD_H

//#include"board.h"
#include"main.h"

#define K_DOWN	1
#define K_UP	0

//-------------------------------------键盘 码----------------------
#define k_0 20//1
#define k_1 7//2       
#define k_2 8//3
#define k_3 9//4
#define k_4 11//5
#define k_5 12//6
#define k_6 13//7
#define k_7 15//8
#define k_8 16//9
#define k_9 17//10
#define k_shift 31//11
#define k_equal 32//12
#define k_add 26//13
#define k_sub 27//14
#define k_cancel 21//15
#define k_dot 19//16
#define k_program 28//17
#define k_manual 44//18
#define k_auto 30//19
#define k_enter 45//20
#define k_insert 29//21
#define k_delete 34//22
#define k_modify 35//23
#define k_pgup 36//24
#define k_pgdown 37//25
#define k_pushpap 18//26
#define k_procedure 14//27
#define k_backspace 10//28
#define k_run 38//29
#define k_stop 33//30
#define k_ahead 24//31
#define k_back 25//32
#define k_up 39//33
#define k_down 40//34
#define k_right 42//35
#define k_left 41//36
#define k_f1 1//37
#define k_f2 2//38
#define k_f3 3//39
#define k_f4 4//40
#define k_f5 5//41
#define k_f6 6//42
#define k_help 43//43

#define k_fast_back		46 //  *
#define k_mul	47 //  *
#define k_div	48  // 除  /
#define k_fast_ahead	49 //  快进
// #define k_jostle 10  //  推纸


//---------新增加 组合键
#define k_fun_program		51	//shift+编程==示教
#define k_fun_auto		52	//shift+自动==自刀
#define k_fun_ahead		53	//shift+前进==快进
#define k_fun_back		54	//shift+后退==快退
#define k_fun_0			55	//shift+0==
#define k_fun_1			56	//shift+1==
#define k_fun_f5			57	//shift+F5==
#define k_fun_8			58	//shift+8==

#define k_fun_right		k_right	//shift+左==右
#define k_fun_pgup		k_pgup	//page up
#define k_fun_pgdown	k_pgdown	//page down


extern Int8U KeyboardLink_flag;
extern Int8U KeyLinkDis_flag;

extern Int8U KeyboardDown_flag;


//-----------
extern Int8U KeyCodeFrameOk_flag;

extern Int8U ShiftKey_flag;
extern Int16U shift_time;

typedef struct
{
Int8U keycode;
Int8U keyflag;
} KEY_DATA;



void KeyboardCode_exec(void);



#endif