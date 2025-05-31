
#include "port.h"

#include "io.h"

Int8U OutFront_limit;
Int8U OutMiddle_limit;
Int8U OutBack_limit;
Int8U Wheel_limit;

Int8U outF_flag;
Int8U outM_flag;
Int8U outB_flag;
Int8U Wheel_flag;
Int8U OriginalError_flag;
Int8U BackLimitError_flag;

Int16U outLimF_time;
Int16U outLimM_time;
Int16U outLimB_time;
Int16U handwheel_time;

Int8U KnifeUp_flag;
Int8U KnifeDown_flag;
Int8U KnifeUp2_flag;
Int8U KnifeDown2_flag;
Int8U PressUp_flag;
Int8U PressDown_flag;
Int8U A_Down_flag;
Int8U B_Down_flag;
Int8U A_Up_flag;
Int8U B_Up_flag;
Int8U IR_Up_flag;
Int8U IR_Down_flag;

//---------------------------
Int8U FrontLimit_IN;
Int8U MiddleLimit_IN;
Int8U BackLimit_IN;

Int8U HandWheel_IN;
Int8U IRsensor_IN;
Int8U Carrier_IN;
Int8U CutPaper_IN1;
Int8U CutPaper_IN2;
Int8U PressPaper_IN;
Int8U Original_IN;
Int8U Encoder_A_IN;
Int8U Encoder_B_IN;

Int8U OIN1_PIN_down_flag;
Int8U OIN1_PIN_up_flag;
Int16U OIN1_PIN_time;

Int8U OIN2_PIN_down_flag;
Int8U OIN2_PIN_up_flag;
Int16U OIN2_PIN_time;

Int8U OIN3_PIN_down_flag;
Int8U OIN3_PIN_up_flag;
Int16U OIN3_PIN_time;

Int8U OIN8_PIN_down_flag;
Int8U OIN8_PIN_up_flag;
Int16U OIN8_PIN_time;

//----
Int8U AllKnifeUp_flag;
Int8U AllPressUp_flag;

//---------out  limit  valid_flag
Int8U OutFrontLimNoValid_flag;
Int8U OutMiddLimNoValid_flag;
Int8U OutBackLimNoValid_flag;

void AllSensor_IN_Get(void)
{
if(OIN2_PIN==0) //  刀 下---0
	{
	OIN2_PIN_up_flag=0;
	if(OIN2_PIN_down_flag==0)
		{
		OIN2_PIN_time=0;
		OIN2_PIN_down_flag=1;
		}
	else
		{
		OIN2_PIN_time++;
		if(OIN2_PIN_time>=(CHECK_IO_TIME))
			{
			OIN2_PIN_time=0;
			CutPaper_IN1=0;
			OIN2_PIN_down_flag=0;
			}
		}
	}
else	//刀 下---1
	{
	OIN2_PIN_down_flag=0;
	if(OIN2_PIN_up_flag==0)
		{
		OIN2_PIN_time=0;
		OIN2_PIN_up_flag=1;
		}
	else
		{
		OIN2_PIN_time++;
		if(OIN2_PIN_time>=(CHECK_IO_TIME))
			{
			OIN2_PIN_time=0;
			CutPaper_IN1=1;
			OIN2_PIN_up_flag=0;
			}
		}
	}
if(MotorType==MOTOR_AC_SERVO670)		//交流670  刀2（z）
	{
	if(OIN8_PIN==0) //  
		{
		OIN8_PIN_up_flag=0;
		if(OIN8_PIN_down_flag==0)
			{
			OIN8_PIN_time=0;
			OIN8_PIN_down_flag=1;
			}
		else
			{
			OIN8_PIN_time++;
			if(OIN8_PIN_time>=(CHECK_IO_TIME+10))
				{
				OIN8_PIN_time=0;
				CutPaper_IN2=0;
				OIN8_PIN_down_flag=0;
				}
			}
		}
	else	//
		{
		OIN8_PIN_down_flag=0;
		if(OIN8_PIN_up_flag==0)
			{
			OIN8_PIN_time=0;
			OIN8_PIN_up_flag=1;
			}
		else
			{
			OIN8_PIN_time++;
			if(OIN8_PIN_time>=(CHECK_IO_TIME+10))
				{
				OIN8_PIN_time=0;
				CutPaper_IN2=1;
				OIN8_PIN_up_flag=0;
				}
			}
		}
	}
	//-----------------
if(OIN3_PIN==0) //压纸 下---
	{
	OIN3_PIN_up_flag=0;
	if(OIN3_PIN_down_flag==0)
		{
		OIN3_PIN_time=0;
		OIN3_PIN_down_flag=1;
		}
	else
		{
		OIN3_PIN_time++;
		if(OIN3_PIN_time>=(CHECK_IO_TIME))
			{
			OIN3_PIN_time=0;
			PressPaper_IN=0;
			OIN3_PIN_down_flag=0;
			}
		}
	}
	
else	
	{
	OIN3_PIN_down_flag=0;
	if(OIN3_PIN_up_flag==0)
		{
		OIN3_PIN_time=0;
		OIN3_PIN_up_flag=1;
		}
	else
		{
		OIN3_PIN_time++;
		if(OIN3_PIN_time>=(CHECK_IO_TIME))
			{
			OIN3_PIN_time=0;
			PressPaper_IN=1;
			OIN3_PIN_up_flag=0;
			}
		}
	}
	
if(OIN5_PIN==0) //红外  下---------
	IRsensor_IN=0;
else
	IRsensor_IN=1;
	
if(OIN4_PIN==0)  //托板 信号
	Carrier_IN=0;
else
	Carrier_IN=1;

if(OutFrontLimNoValid_flag==0)
	{
	if(OIN11_PIN==0)   //外部前限位
		FrontLimit_IN=0;
	else
		FrontLimit_IN=1;
	}
else	//无效
	{
	FrontLimit_IN=0;
	}

if(OutMiddLimNoValid_flag==0)	
	{
	if(OIN12_PIN==0)	//外部中限位
		MiddleLimit_IN=0;
	else	
		MiddleLimit_IN=1;
	}
else	//无效
	{
	MiddleLimit_IN=0;
	}

if(OutBackLimNoValid_flag==0)
	{
	if(OIN13_PIN==0) //外部后限位
		BackLimit_IN=0;
	else	
		BackLimit_IN=1;
	}
else	//无效
	{
	BackLimit_IN=0;
	}

if(OIN14_PIN==0)  //手轮
	HandWheel_IN=0;
else
	HandWheel_IN=1;
	
if(OIN6_PIN==0)  //编码器 A
	Encoder_A_IN=0;
else
	Encoder_A_IN=1;
	
if(OIN7_PIN==0)  //编码器 B
	Encoder_B_IN=0;
else
	Encoder_B_IN=1;
}


void GetCutSensorIN(void)		//DC servo motor sensor
{
//**********刀1
if(OIN2_PIN==0) //  刀 下---0
	{
	OIN2_PIN_up_flag=0;
	if(OIN2_PIN_down_flag==0)
		{
		OIN2_PIN_time=0;
		OIN2_PIN_down_flag=1;
		}
	else
		{
		OIN2_PIN_time++;
		if(OIN2_PIN_time>=(CHECK_IO_TIME+10))
			{
			OIN2_PIN_time=0;
			CutPaper_IN1=0;
			OIN2_PIN_down_flag=0;
			}
		}
	}
else	//刀 下---1
	{
	OIN2_PIN_down_flag=0;
	if(OIN2_PIN_up_flag==0)
		{
		OIN2_PIN_time=0;
		OIN2_PIN_up_flag=1;
		}
	else
		{
		OIN2_PIN_time++;
		if(OIN2_PIN_time>=(CHECK_IO_TIME+10))
			{
			OIN2_PIN_time=0;
			CutPaper_IN1=1;
			OIN2_PIN_up_flag=0;
			}
		}
	}
if(MotorType==MOTOR_DC670_SERVO_ZHU)	//*************原点 信号  改为 刀2
	{
	if(OIN1_PIN==0) //  刀 下---0
		{
		OIN1_PIN_up_flag=0;
		if(OIN1_PIN_down_flag==0)
			{
			OIN1_PIN_time=0;
			OIN1_PIN_down_flag=1;
			}
		else
			{
			OIN1_PIN_time++;
			if(OIN1_PIN_time>=(CHECK_IO_TIME+10))
				{
				OIN1_PIN_time=0;
				CutPaper_IN2=0;
				OIN1_PIN_down_flag=0;
				}
			}
		}
	else	//刀 下---1
		{
		OIN1_PIN_down_flag=0;
		if(OIN1_PIN_up_flag==0)
			{
			OIN1_PIN_time=0;
			OIN1_PIN_up_flag=1;
			}
		else
			{
			OIN1_PIN_time++;
			if(OIN1_PIN_time>=(CHECK_IO_TIME+10))
				{
				OIN1_PIN_time=0;
				CutPaper_IN2=1;
				OIN1_PIN_up_flag=0;
				}
			}
		}
	}					
}