#ifndef TEST_IO_H
#define TEST_IO_H

#include "main.h"
#include"io.h"
#include"drv_glcd.h"
#include"key.h"


#define START_X     30//10
#define START_Y     50

#define Num_W    110
#define Num_H    60


//按键测试输出显示位置定义*********
#define DISKEY_W   80
#define DISKEY_H   60

#define COL_0  START_X//10   //列
#define COL_1  (COL_0+DISKEY_W)   //列
#define COL_2  (COL_1+DISKEY_W)
#define COL_3  (COL_2+DISKEY_W)
#define COL_4  (COL_3+DISKEY_W)
#define COL_5  (COL_4+DISKEY_W)
#define COL_6  (COL_5+DISKEY_W)
#define COL_7  (COL_6+DISKEY_W)
#define COL_8  (COL_7+DISKEY_W)
#define COL_9  (COL_8+DISKEY_W)
#define COL_10 (COL_9+DISKEY_W)
#define COL_11 (COL_10+DISKEY_W)

#define ROW_1  240  //行
#define ROW_2  (ROW_1+DISKEY_H)  
#define ROW_3  (ROW_2+DISKEY_H)  
#define ROW_4  (ROW_3+DISKEY_H)  
#define ROW_5  (ROW_4+DISKEY_H)  
#define ROW_6  (ROW_5+DISKEY_H)  
  

#define DOWN_COL   GREEN_COLOR
#define UP_COL     0xf03f



#define IO_STUS_W	90//100
#define IO_STUS_H	45//30

#define IO_STUS_X1 110//80
#define IO_STUS_Y1 250//200
#define IO_STUS_X2 (IO_STUS_X1+IO_STUS_W)
#define IO_STUS_X3 (IO_STUS_X2+IO_STUS_W)
#define IO_STUS_X4 (IO_STUS_X3+IO_STUS_W)
#define IO_STUS_X5 (IO_STUS_X4+IO_STUS_W)
#define IO_STUS_X6 (IO_STUS_X5+IO_STUS_W)
#define IO_STUS_X7 (IO_STUS_X6+IO_STUS_W)
//y
#define IO_STUS_Y2 (IO_STUS_Y1+IO_STUS_H)
#define IO_STUS_Y3 (IO_STUS_Y2+IO_STUS_H)
#define IO_STUS_Y4 (IO_STUS_Y3+IO_STUS_H)
#define IO_STUS_Y5 (IO_STUS_Y4+IO_STUS_H)
#define IO_STUS_Y6 (IO_STUS_Y5+IO_STUS_H)
#define IO_STUS_Y7 (IO_STUS_Y6+IO_STUS_H)


#define T_DISKEY_W   60
#define T_DISKEY_H   30
#define TSTMOD_COL_0  110  //列
#define TSTMOD_COL_1  (TSTMOD_COL_0+T_DISKEY_W)   //列
#define TSTMOD_COL_2  (TSTMOD_COL_1+T_DISKEY_W)
#define TSTMOD_COL_3  (TSTMOD_COL_2+T_DISKEY_W)
#define TSTMOD_COL_4  (TSTMOD_COL_3+T_DISKEY_W)
#define TSTMOD_COL_5  (TSTMOD_COL_4+T_DISKEY_W)
#define TSTMOD_COL_6  (TSTMOD_COL_5+T_DISKEY_W)
#define TSTMOD_COL_7  (TSTMOD_COL_6+T_DISKEY_W)
#define TSTMOD_COL_8  (TSTMOD_COL_7+T_DISKEY_W)
#define TSTMOD_COL_9  (TSTMOD_COL_8+T_DISKEY_W)
#define TSTMOD_COL_10 (TSTMOD_COL_9+T_DISKEY_W)
#define TSTMOD_COL_11 (TSTMOD_COL_10+T_DISKEY_W)

#define TSTMOD_ROW_1  340//350  //行
#define TSTMOD_ROW_2  (TSTMOD_ROW_1+T_DISKEY_H)  
#define TSTMOD_ROW_3  (TSTMOD_ROW_2+T_DISKEY_H)  
#define TSTMOD_ROW_4  (TSTMOD_ROW_3+T_DISKEY_H)  
#define TSTMOD_ROW_5  (TSTMOD_ROW_4+T_DISKEY_H)  
#define TSTMOD_ROW_6  (TSTMOD_ROW_5+T_DISKEY_H)  


extern Int8U Borard1_2;//选择硬件版本
   




void KeyDis(Int8U num,Int16U Xp,Int16U Yp,Int8U Keydown);   //测试键盘输入
void KeyDis_sel(Int32U Keycode,Int8U Keydown);//按键状态显示


#endif
