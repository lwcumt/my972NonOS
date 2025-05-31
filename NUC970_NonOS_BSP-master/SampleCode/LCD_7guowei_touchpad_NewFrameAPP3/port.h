

#ifndef _PORT_H
#define _PORT_H


#include "main.h"

#include"pic_exec.h"



#define CHECK_IO_TIME 10

extern Int8U OutFront_limit;
extern Int8U OutMiddle_limit;
extern Int8U OutBack_limit;
extern Int8U Wheel_limit;

extern Int8U outF_flag;
extern Int8U outM_flag;
extern Int8U outB_flag;
extern Int8U Wheel_flag;
extern Int8U OriginalError_flag;
extern Int8U BackLimitError_flag;
extern Int16U outLimF_time;
extern Int16U outLimM_time;
extern Int16U outLimB_time;
extern Int16U handwheel_time;

extern Int8U KnifeUp_flag;
extern Int8U KnifeDown_flag;
extern Int8U KnifeUp2_flag;
extern Int8U KnifeDown2_flag;
extern Int8U PressUp_flag;
extern Int8U PressDown_flag;
extern Int8U A_Down_flag;
extern Int8U B_Down_flag;
extern Int8U A_Up_flag;
extern Int8U B_Up_flag;
extern Int8U IR_Up_flag;
extern Int8U IR_Down_flag;
//------------------------------
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

//----
extern Int8U AllKnifeUp_flag;
extern Int8U AllPressUp_flag;

//---------out  limit  valid_flag
extern Int8U Front_LimitValid_flag;
extern Int8U Middle_LimitValid_flag;
extern Int8U Back_LimitValid_flag;

#endif
