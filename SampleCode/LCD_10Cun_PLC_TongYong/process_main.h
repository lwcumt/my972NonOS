#ifndef _PROCESS_MAIN_H
#define _PROCESS_MAIN_H

#include "main.h"


extern Int32U CutRelease_time;

extern Int8U AllKnifeUp_flag;
extern Int8U AllPressUp_flag;

extern Int8U PressUp_flag;
extern Int8U PressDown_flag;

extern Int8U PaperCutEnb_signal;
extern Int8U IR_Up_flag;
extern Int8U IR_Down_flag;

extern Int8U PressCircle_mode;
extern Int8U AutoCutDisable_flag;





extern Int8U AutoRoute_flag;

extern Int8U OnePress_sign_mod;
extern Int8U OneKnife_sign_mod;
extern Int8U NewKnife_sign_mod;

//---------------------------
extern Int8U FrontLimit_IN;
extern Int8U MiddleLimit_IN;
extern Int8U BackLimit_IN;

extern Int8U HandWheel_IN;
extern Int8U IRsensor_IN;
extern Int8U Carrier_IN;
extern Int8U CutPaper_IN1;
extern Int8U CutPaper_IN2;
extern Int8U PressPaper_IN;
extern Int8U Original_IN;
extern Int8U Encoder_A_IN;
extern Int8U Encoder_B_IN;



extern Int8U KnifeUp_flag;
extern Int8U KnifeDown_flag;
extern Int8U KnifeUp2_flag;
extern Int8U KnifeDown2_flag;


extern Int8U OIN2_PIN_down_flag;
extern Int8U OIN2_PIN_up_flag;
extern Int16U OIN2_PIN_time;

extern Int8U OIN3_PIN_down_flag;
extern Int8U OIN3_PIN_up_flag;
extern Int16U OIN3_PIN_time;


extern Int8U OIN5_PIN_down_flag;
extern Int8U OIN5_PIN_up_flag;
extern Int16U OIN5_PIN_time;


extern Int8U Hold_Up_flag;
extern Int8U Hold_Down_flag;



extern Int8U BellStart_flag;
extern Int8U TargetBell_flag;
extern Int16U TargetBell_time;
extern Int8U TargetBell_mode;

extern Int8U PressStopDis_flag;

extern Int16U DisplayFlashTime;



void AutoCutPush_exec(void);  //自动裁切 与推纸

#endif


