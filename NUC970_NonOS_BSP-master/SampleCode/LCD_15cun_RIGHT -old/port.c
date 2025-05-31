
#include "port.h"

#include "io.h"
#include"pic_exec.h"

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

Int8U OIN2_PIN_down_flag;
Int8U OIN2_PIN_up_flag;
Int16U OIN2_PIN_time;

Int8U OIN3_PIN_down_flag;
Int8U OIN3_PIN_up_flag;
Int16U OIN3_PIN_time;


Int8U OIN5_PIN_down_flag;
Int8U OIN5_PIN_up_flag;
Int16U OIN5_PIN_time;

//----
Int8U AllKnifeUp_flag;
Int8U AllPressUp_flag;

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
		if(OIN2_PIN_time>=CHECK_IO_TIME)
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
		if(OIN2_PIN_time>=CHECK_IO_TIME)
			{
			OIN2_PIN_time=0;
			CutPaper_IN1=1;
			OIN2_PIN_up_flag=0;
			}
		}
	}
	
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
		if(OIN3_PIN_time>=CHECK_IO_TIME)
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
		if(OIN3_PIN_time>=CHECK_IO_TIME)
			{
			OIN3_PIN_time=0;
			PressPaper_IN=1;
			OIN3_PIN_up_flag=0;
			}
		}
	}

if(IR_SensorStus==0)	//low IR
	{
	if(OIN5_PIN_down_flag==0)
		{
	if(OIN5_PIN==0)
			{
			OIN5_PIN_time++;
			if(OIN5_PIN_time>=CHECK_IO_TIME)
				{
				OIN5_PIN_time=0;
		IRsensor_IN=0; //红外  有效---------
				OIN5_PIN_down_flag=1;
				}
			}
	else
			{
			OIN5_PIN_time=0;IRsensor_IN=1;
			}
		}
	else
		{
		if(OIN5_PIN!=0)	
			{
			OIN5_PIN_time++;
			if(OIN5_PIN_time>=CHECK_IO_TIME)
				{
				OIN5_PIN_time=0;
				IRsensor_IN=1; //红外  有效---------
				OIN5_PIN_down_flag=0;
				}
			}
		else
			{
			OIN5_PIN_time=0;
			}
		}
	}
else			//high IR
	{
	if(OIN5_PIN_down_flag==0)
		{
	if(OIN5_PIN!=0)
			{
			OIN5_PIN_time++;
			if(OIN5_PIN_time>=CHECK_IO_TIME)
				{
				OIN5_PIN_time=0;
		IRsensor_IN=0; //红外  有效---------
				OIN5_PIN_down_flag=1;
				}
			}
	else
			{
			OIN5_PIN_time=0;IRsensor_IN=1;
			}
		}
	else
		{
		if(OIN5_PIN==0)	
			{
			OIN5_PIN_time++;
			if(OIN5_PIN_time>=CHECK_IO_TIME)
				{
				OIN5_PIN_time=0;
				IRsensor_IN=1; //红外  有效---------
				OIN5_PIN_down_flag=0;
				}
			}
		else
			{
			OIN5_PIN_time=0;
			}
		}
	// if(OIN5_PIN!=0)
		// IRsensor_IN=0; //红外  有效---------
	// else
		// IRsensor_IN=1;
	}
	
if(OIN4_PIN==0)  //托板 信号
	Carrier_IN=0;
else
	Carrier_IN=1;

	
if(OIN11_PIN==0)   //外部前限位
	FrontLimit_IN=0;
else
	FrontLimit_IN=1;
	
// if(OIN12_PIN==0)	//外部中限位
	 MiddleLimit_IN=0;
// else	
	// MiddleLimit_IN=1;

if(OIN13_PIN==0) //外部后限位
	BackLimit_IN=0;
else	
	BackLimit_IN=1;	

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


void GetCutSensorIN(void)
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
		if(OIN2_PIN_time>=CHECK_IO_TIME)
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
		if(OIN2_PIN_time>=CHECK_IO_TIME)
			{
			OIN2_PIN_time=0;
			CutPaper_IN1=1;
			OIN2_PIN_up_flag=0;
			}
		}
	}
}
