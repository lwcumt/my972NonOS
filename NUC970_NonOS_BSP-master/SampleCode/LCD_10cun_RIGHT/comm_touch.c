

#include "comm_touch.h"
#include "io.h"
//#include "tsc2046.h"
#include"key.h"


Int8U TouchConnect_flag;
Int8U TouchConnectSend_flag;

Int16U TouchConnectWaitTime;

Int8U TouchReady_flag;

 

Int8U TouchCommMode;
Int8U TouchCommCMD_Down_flag;
Int8U TouchCommCMD_Up_flag;

Int8U TouCommPosGet_flag;

Int8U Txbuf[20]={0};
Int16U TouComm_X;
Int16U TouComm_X_temp;
Int16U TouComm_Y;
Int16U TouComm_Y_temp;


Int8U TouDown_Comm_flag;
Int8U TouExec_Comm_flag;
Int16U TouDownLongTime;

Int8U CheckLink_Cou;

Int8U TouchCommLongdownExec_flag;


void Comm_TouchScr(Int8U data)
{
Int8U dtemp;
dtemp=data;
if(TouchConnect_flag == 0)
	{
	if(TouchConnectSend_flag == 1)
		{
		switch(TouchCommMode)
			{
			case 0:
				if(dtemp == 0xa)
					{
					TouchCommMode++;
					}
					break;
			case 1:
				if(dtemp == 0x01)
					{
					TouchCommMode++;
					}
				else
					TouchCommMode=0;
					break;
			case 2:
				if(dtemp == 0x41)
					{
					TouchConnect_flag=1;
					LED2_ON;
					TouchConnectWaitTime=0;
					TouchReady_flag=0;
					}
				TouchCommMode=0;
					break;
			}
		}
	}		
else		
	{
	if(TouchReady_flag == 1)//touchscreen 已经连接上
		{
		switch(TouchCommMode)
			{
			case 0:
				if(dtemp == 0x81)
					{
					TouchCommMode++;
					TouchCommCMD_Down_flag=1;
					}
				else if(dtemp == 0x80)
					{
					TouchCommCMD_Up_flag=1;	TouchCommCMD_Down_flag=0;
					TouchCommMode++;
					}
				else
					TouchCommMode=0;
					break;
			case 1:
				if(dtemp>0x10)
					TouchCommMode=0;
				else
					{
					TouComm_X_temp=(Int16U)dtemp<<7;
					TouchCommMode++;
					}
					break;
			case 2:
				TouComm_X_temp+=(dtemp&0x7f);
				TouchCommMode++;
					break;
			case 3:
				TouComm_Y_temp=(Int16U)dtemp<<7;
				TouchCommMode++;
					break;
			case 4:
				TouComm_Y_temp+=(dtemp&0x7f);
				if(TouCommPosGet_flag == 0)		//获取有效数据
					{
					TouCommPosGet_flag=1;
					TouComm_X=TouComm_X_temp;
					TouComm_Y=TouComm_Y_temp;	
					}
				
				TouchCommMode=0;
					break;
			}	
		}
	}
}




void TouchScan_Uart(void)
{
//	TouchConnect_flag=1;
if(TouchConnect_flag == 0)	//检测触摸屏是否连接
	{
	if(TouchConnectSend_flag == 0)
		{
		 TouchConnectSend_flag=1;
		 Txbuf[0]=0xa;
		 Txbuf[1]=0x1;
		 Txbuf[2]=0x41;
		 Txbuf[3]=0;
		 UART8_SendStr(Txbuf);
		 TouchCommMode=0;
		 TouchConnectWaitTime=0;
		}
	else 
		{
		TouchConnectWaitTime++;
		if(TouchConnectWaitTime>=500)
			{
			TouchConnectSend_flag=0;
			/****
			CheckLink_Cou++;
			if(CheckLink_Cou>=5)	//超过5次无应答
				{
				TouchConnect_flag=1;
				}
			****/
			}
		}
	}
else	//触摸 已连接
	{
	if(TouchReady_flag == 0)
		{
		TouchConnectWaitTime++;
		if(TouchConnectWaitTime>=500) //检测 结束
			{
			TouchConnectWaitTime=0;
			TouchReady_flag=1;
			LED2_OFF;
			}	
		}
	else		//触摸 位置处理
		{
		if(TouDown_Comm_flag == 0)
			{
			if(TouCommPosGet_flag == 1)		//======获取触摸数据
				{
				if(TouchCommCMD_Down_flag == 1)// ----按下的命令
					{
					if((TouComm_X>TOU_AD_MIN)&&(TouComm_X<TOU_AD_MAX)&&(TouComm_Y>TOU_AD_MIN)&&(TouComm_Y<TOU_AD_MAX))	//触摸按下  有效
						{
						LED2_ON;
						TouchAD.x =TouComm_X;
						TouchAD.y =TouComm_Y;	//读取 x,y 值
						TouDown_Comm_flag=1;
						TouchKey_exec();  //````````````````触摸键  处理``````````
						TouDownLongTime=0;TouchCommLongdownExec_flag=0;
						}
					TouchCommCMD_Down_flag=0;
					}
				TouCommPosGet_flag = 0;
				}
			}
		else	//等待 释放
			{
			if(TouchCommCMD_Up_flag == 1)	//=====释放的命令
				{
				LED2_OFF;
						//释放  处理
				TouchCommCMD_Up_flag =0;TouchCommCMD_Down_flag=0;
				TouDown_Comm_flag=0;
				TouCommPosGet_flag = 0;
				//、、、、、、、、、、
				GoFrontEn_flag=0;
				GoBackEn_flag=0;
				// ---------------------------
				LongTouchUp_Exec();//长按释放-----20190531
				
				TouchButton_dis(Touch_code_temp,0);  //触摸键  显示
				Touch_code_temp=0;//-------释放后 清触摸键值
				Touch_code=0;
				ACMotor_ReleaseStop();
				}
			else	//未释放---
				{
				switch(Board_TestMod)
					{
					case 0:
							if(TouCommPosGet_flag == 1)		//======获取触摸数据
								{
								if(TouchCommCMD_Down_flag == 1)// ----按下的命令
									{
									if(TouchCommLongdownExec_flag==0)
										{
										if((TouComm_X>TOU_AD_MIN)&&(TouComm_X<TOU_AD_MAX)&&(TouComm_Y>TOU_AD_MIN)&&(TouComm_Y<TOU_AD_MAX))	//触摸按下  有效
											{
											TouDownLongTime++;
											if(TouDownLongTime>=100)
												{
												TouchAD.x =TouComm_X;
												TouchAD.y =TouComm_Y;	//读取 x,y 值	
												//---------touch-long down exec
												TouchCommLongdownExec_flag=1;
											//	TouchKey_exec();  //````````````````触摸键  处理``````````
												LongTouchDown_Exec(); //20190531
												}
											}	
										}
									TouchCommCMD_Down_flag=0;
									}
								TouCommPosGet_flag=0;
								}
								break;	
					case TEST_BOARD:
							if(TouCommPosGet_flag == 1)		//======获取触摸数据
								{
								if(TouchCommCMD_Down_flag == 1)// ----按下的命令
									{
									if((TouComm_X>TOU_AD_MIN)&&(TouComm_X<TOU_AD_MAX)&&(TouComm_Y>TOU_AD_MIN)&&(TouComm_Y<TOU_AD_MAX))	//触摸按下  有效
										{
										TouchAD.x =TouComm_X;
										TouchAD.y =TouComm_Y;	//读取 x,y 值
										//`````````````````````
										GetTouch_pos();
										if(Touch_Pos.x>=C_GLCD_H_SIZE)
											Touch_Pos.x=C_GLCD_H_SIZE-1;
										if(Touch_Pos.y>=C_GLCD_V_SIZE)
											Touch_Pos.y=C_GLCD_V_SIZE-1;
										PutPixel(Touch_Pos.x,Touch_Pos.y,RED_COLOR);//手写
										}
									TouchCommCMD_Down_flag=0;
									}
								TouCommPosGet_flag = 0;
								}
								break;
					default:
							TouDownLongTime++;
							if(TouDownLongTime>=TOUCH_ERR_TIME)  ////---------------------------触摸  按下时间过长，强制释放
								{	
								TouDown_Comm_flag=0;
								TouCommPosGet_flag = 0;TouchCommCMD_Down_flag=0;
								//、、、、、、、、、、
								GoFrontEn_flag=0;
								GoBackEn_flag=0;	
								TouchButton_dis(Touch_code_temp,0);  //触摸键  显示
								Touch_code_temp=0;//-------释放后 清触摸键值
								Touch_code=0;
								ACMotor_ReleaseStop();
								}
								break;		
					}
					/***
				if(Board_TestMod==TEST_BOARD)  //主板功能测试mode-------------------------------
					{
					if(TouCommPosGet_flag == 1)		//======获取触摸数据
						{
						if(TouchCommCMD_Down_flag == 1)// ----按下的命令
							{
							if((TouComm_X>TOU_AD_MIN)&&(TouComm_X<TOU_AD_MAX)&&(TouComm_Y>TOU_AD_MIN)&&(TouComm_Y<TOU_AD_MAX))	//触摸按下  有效
								{
								TouchAD.x =TouComm_X;
								TouchAD.y =TouComm_Y;	//读取 x,y 值
								//`````````````````````
								GetTouch_pos();
								if(Touch_Pos.x>=C_GLCD_H_SIZE)
									Touch_Pos.x=C_GLCD_H_SIZE-1;
								if(Touch_Pos.y>=C_GLCD_V_SIZE)
									Touch_Pos.y=C_GLCD_V_SIZE-1;
								PutPixel(Touch_Pos.x,Touch_Pos.y,RED_COLOR);//手写
								}
							TouchCommCMD_Down_flag=0;
							}
						TouCommPosGet_flag = 0;
						}
					
					}
				else
					{
					TouDownLongTime++;
					if(TouDownLongTime>=TOUCH_ERR_TIME)  ////---------------------------触摸  按下时间过长，强制释放
						{	
						TouDown_Comm_flag=0;
						TouCommPosGet_flag = 0;TouchCommCMD_Down_flag=0;
						//、、、、、、、、、、
						GoFrontEn_flag=0;
						GoBackEn_flag=0;	
						TouchButton_dis(Touch_code,0);  //触摸键  显示
						Touch_code=0;//-------释放后 清触摸键值
						ACMotor_ReleaseStop();
						}
					}***/
				}
			}
		}
	}
}
