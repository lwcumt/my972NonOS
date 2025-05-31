
#ifndef TEST_IO_H
#define TEST_IO_H

#include "main.h"
#include"io.h"
#include"drv_glcd.h"
#include"key.h"


#define START_X     10
#define START_Y     50

#define Num_W    110
#define Num_H    60


//按键测试输出显示位置定义*********
#define COL_0  10   //列
#define COL_1  (COL_0+100)   //列
#define COL_2  (COL_1+100)
#define COL_3  (COL_2+100)
#define COL_4  (COL_3+100)
#define COL_5  (COL_4+100)
#define COL_6  (COL_5+100)
#define COL_7  (COL_6+50)
#define COL_8  (COL_7+50)

#define ROW_1  240  //行
#define ROW_2  (ROW_1+60)  
#define ROW_3  (ROW_2+60)  
#define ROW_4  (ROW_3+60)  
  

#define DOWN_COL   GREEN_COLOR
#define UP_COL     0xf03f


extern Int8U Borard1_2;//选择硬件版本
   




void KeyDis(Int8U num,Int16U Xp,Int16U Yp,Int8U Keydown);   //测试键盘输入
void KeyDis_sel(Int32U Keycode,Int8U Keydown);//按键状态显示


#endif