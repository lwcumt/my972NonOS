#include "app_workloop.h"



#include "comm_fx_plc.h"
#include "pic_exec.h"

#include "process_main.h"

#include "key.h"


#include "app_modbus_motion.h"


#include "pcf8563.h"
#include "timer.h"


#include "app_modbus.h"
#include "keyboard.h"

#include "optimize_cut.h"
#include "app_modbus_fxplc.h"

#include "app_fx_plc.h"
#include "plc_ext_form.h"

#include "app_modbus_test.h"

#include "App_Modbus_Motion_972.h"


//新的工作循环体
//替换原有的main 函数中的主循环体
void App_WorkLoop(void)
{
int Cou=0;
	
while(1)
		{
		if(Ms_Flag!=0)
				{
				Ms_Flag=0;	
					
	//			App_Modbus_Test_Task();				
		//		Modbus_Servo_Link_Flag=1;//强制伺服连接  测试用			
				App_Modbus_Task_Ready_Flag=0;//  测试用
					
					
				App_Servo_Check_CutEnb();//电机停止后的允许裁切判断
			
				App_Modbus_Motion_CheckTarget();//运动目标值检测是否到位
					
					App_Modbus_Servo_CheckStop();
			
				//AutoBackToForward();//多后退6mm后再向前//不需要再多后退
			
					
//				ElectricWheelOn_flag=1;//强制手轮打开  //无需主机电子手轮，放在伺服上做了
				//App_ModBus_Motion_ElectricWheel_Run();//无需主机电子手轮，放在伺服上做了
			
		  	App_Modbus_FXPlc_AutoCnt_Check();	//自动裁切判断			
				
				#ifdef FX_PLC
				if(APP_MODBUS_PLC==1)// APP_MODUBS_PLC 为0 时，使用板载IO 去掉PLC功能，屏幕触控不入
						{
						if(WorkMode==AUTO_MODE)
							{//自动模式下有效
								if(OptimizeCut_Enb_Flag==0)
								{//压纸弹出运行模式
								YaZhi_Run_Check_Enter();
								YaZhi_Process_RunCheck();//压纸程序运行检测
								}
							else
								{//优化裁切模式
									OptimizeCut_X05_RunCheck();//检测半周触发信号
								}
							}

							App_FX_Plc_Run();//运行通讯，自动压力保存等动作
						}
				else
						{
					//	ModBus_Servo_Status_Dis();
						}		
						
				ModBus_Servo_Plc_Status_Dis();
				#endif
						
				if(Touch_code==0)
					Keyboard_scan();//键盘板扫描	

				#ifdef CAP_TOUCH
				//电容屏
				GtpCheckTime++;
				if(GtpCheckTime>15)
					{
					GtpCheckTime=0;
				 if(KeyboardDown_flag==0)
							Gtp_Touch_Scan();//电容屏触摸
					}			 
				#else
					if(KeyboardDown_flag==0) //电阻屏
							TouchScan_Uart(); //触摸串口				
				#endif
					
				//键移调用
	      ShiftKeyExec();//

				AllSensor_IN_Get();  //输入端口检测

				if(MotorType>=MOTOR_AC_SERVO) 
					{
					ACServoAlarm_exec();  //交流伺服  警报  处理
					}				
					
				//有故障报警
				if((EncoderErr_flag==1)||(ACServoDrvErr_flag==1))
					{
					Cou++;
					if(Cou>=200)
						{
						Cou=0;
						BellOUT_ANTI;  ///故障 蜂鸣----
						} 
					}					
					
				App_WorkLoop_WorkModeRun();//主工作界面处理
				App_WorkLoop_InitModeRun();//开机界面处理
					
				Plc_Form_DisUpdata();//红外线显示
			  App_Modbus_Motion_Loop_Run(); //运动控制的处理 SERVO + PLC  
					
				App_Motion_Runing_Check_Limit_Sensor();
				}//if(Ms_Flag!=0)
		}
}



unsigned char Ms100_t=0;;

//正常工作模式下的运行
void App_WorkLoop_WorkModeRun(void)
{
if(WorkStart_flag==1)  //进入工作状态
	     {	 
		 BellTwice_exec();  //蜂鸣  两声
		 
////////////		if(MotorType>=MOTOR_AC_SERVO)
////////////			{
////////////			ACMotorGetCurrentSize();  // 交流伺服   尺寸计算
////////////			}
	 
	 //************以下日期时间显示
    Ms100_t++;
    if(Ms100_t>=200)
             {
             Ms100_t=0;
						 read_time();
						 Time_dis();
             } 
						 
						 
						 

		
		//*************
		switch(WorkMode)
			{
			// case  PROG_MODE://编程画面下
			case AUTO_MODE://自动主画面下
			case AUTO_PLUS_MODE://自动F3++
			case AUTO_MINUS_MODE://自动F4--
			case MANUAL_MODE:// 手动 模式
			case TEACH_MODE://示教 模式
			case AUTO_TO_SELF_MODE:   //自动-->自刀过度 模式
			case SELF_CUT_MODE:  //自刀主 模式
			case TEACH_PLUS_MODE: //示教 F3++
			case TEACH_MINUS_MODE://示教 F4--
			
				switch(MotorType)
					{
					case MOTOR_AC_SERVO:											
							NewKnife_sign_mod=3;//++++++++++++++++++++++++++
							if(CutPaper_IN1==0) //  刀 下--------------------
								 {
								 AllKnifeUp_flag=0;//----00000
								 CutRelease_time=0;
								 if(KnifeDown_flag==0)
									{
									KnifeDown_flag=1;
									KnifeUp_flag=0;
										Knife_Down_dis( KNIFE_UP_X,  KNIFE_UP_Y);//刀下
									}
								if(Run_flag==0)
									{
									if(PaperCutEnb_signal==2)
										{
										if(OneKnife_sign_mod==1)
											OneKnife_sign_mod++;
										}
									}
								KnifeSensorInMachine_dis(1);//刀 传感器位置 示意
								 }
							 else
								 {
								 AllKnifeUp_flag=1;//----11111
								 if(KnifeUp_flag==0)
									{
									KnifeDown_flag=0;
									KnifeUp_flag=1;
										Knife_Up_dis(KNIFE_UP_X,KNIFE_UP_Y);//刀上
									if(PressStopDis_flag==1)//压纸停机 提示
										{
										PressStopDis_flag=0;
										PromptNum_dis();//输入范围
										PromptDis_flag=1;
										}	
									}
								 if(Run_flag==0)
									{
									if(PaperCutEnb_signal==2)
										{
										if((OneKnife_sign_mod==0)||(OneKnife_sign_mod==2))
											{
											OneKnife_sign_mod++;
											if(OneKnife_sign_mod==3)
												CutRelease_time=0;
											}
										}
									}	
								KnifeSensorInMachine_dis(0);//刀 传感器位置 示意
								 }
								 
							 if(PressPaper_IN!=0) //压纸 下--------------------
								 {
								 CutRelease_time=0;
								 AllPressUp_flag=0;//----000
								 if(PressDown_flag==0)
									{
									PressDown_flag=1;
									PressUp_flag=0;
									Press_Down_dis(PRESS_UP_X,PRESS_UP_Y);//压纸 下
									
									}
								if(Run_flag==0)
									{
									if(PaperCutEnb_signal==2)
										{
										if(OnePress_sign_mod==1)
											OnePress_sign_mod++;
										}
									if((WorkMode == AUTO_MODE)||(WorkMode == SELF_CUT_MODE))//自动主画面下+自刀
										{
										if(PressCircle_mode == 0)
											PressCircle_mode++;
										}
									}
								PressSensorInMachine_dis(1);//压纸 传感器位置 示意
								 }
							 else
								 {
								 AllPressUp_flag=1;//----111
								 if(PressUp_flag==0)
									{
									PressDown_flag=0;
									PressUp_flag=1;
										Press_Up_dis(PRESS_UP_X,PRESS_UP_Y);//压上
									if(PressStopDis_flag==1)//压纸停机 提示
										{
										PressStopDis_flag=0;
										PromptNum_dis();//输入范围
										PromptDis_flag=1;
										}
									
									}
								if(Run_flag==0)
									{
									if(PaperCutEnb_signal==2)
										{
										if((OnePress_sign_mod==0)||(OnePress_sign_mod==2))
											{
											OnePress_sign_mod++;
											if(OnePress_sign_mod==3)
												CutRelease_time=0;
											}
										}
									if((WorkMode == AUTO_MODE)||(WorkMode == SELF_CUT_MODE))//自动主画面下+自刀
										{
										if(PressCircle_mode == 1)
											PressCircle_mode++;
										}
									}
								PressSensorInMachine_dis(0);//压纸 传感器位置 示意
								 }
								 
								 
								 if((Run_flag!=0)&&(qianjin!=0))//当前进状态下，压低的话，停止运行  2024-08-26
											{
												if(PressDown_flag!=0)
													{
														ACServoStop();																					

														Run_flag=0;	
														InTargetPosit_flag=0;	//目标位置
														AutoPushRun_flag=0; //自动推纸 运行
														TargetSize=0;
														TargetSize_temp=0;
														 BeforeKnife_offset_in=0;
																			// if(ButtonTouch_mode==0)
																				// ClrInput_function();//清零 输入框
														AutoRoute_flag=0; 		
													}
												
											}
		
								break;	

					}
					
					 
					 if(IRsensor_IN==0) //红外  下----------------------
						 {
						 if(IR_Down_flag==0)
							{
							IR_Down_flag=1;
							IR_Up_flag=0;
							}
							
							
						if(WorkMode==SELF_CUT_MODE)//自刀主画面下
							{
							//#if 0  //--------((((((((((
							if(Run_flag==1)  //运行中
								{
////////////								if(IRChgWorkmodeValid_flag!=0)	//红外--切换工作模式20180110
////////////									{
////////////									if(AutoCutStart_flag==0)
////////////										{
////////////										 switch(MotorType)
////////////											{
////////////											case MOTOR_AC_SERVO:
////////////											case MOTOR_AC_SERVO_REV:
////////////												ACServoStop();
////////////												
////////////													break;
////////////											}
////////////										Run_flag=0;	
////////////										InTargetPosit_flag=0;	//目标位置
////////////										AutoPushRun_flag=0; //自动推纸 运行
////////////										TargetSize=0;
////////////										TargetSize_temp=0;
////////////										BeforeKnife_offset_in=0;
////////////										// if(ButtonTouch_mode==0)
////////////											// ClrInput_function();//清零 输入框
////////////										AutoRoute_flag=0; 
////////////										}	
////////////									}
								AutoCutDisable_flag=1;
								}
							else
								{
								if(OneKnife_sign_mod>0)	//	||(OnePress_sign_mod>0)
									AutoCutDisable_flag=1;		
								}
								
							if(CutEnBegin_flag==1)
								{
								CutEnBegin_flag=0;
								BellOUT_OFF;
								RLOUT4_ON;
								#ifdef FX_PLC
									if(APP_MODBUS_PLC==1)// APP_MODUBS_PLC 为0 时，使用板载IO
										FX_Plc_EnbAutoCut_Flag=1;
						#endif
								AutoCutStart_flag=0;
								RunStop_flag=0;
								//Run_flag=0;
								}
							
							LastAutoKnife_order=Knife_order;
////////////							if(IRChgWorkmodeValid_flag!=0)	//红外--切换工作模式20180110
////////////								{/****20170818***/
////////////								WorkMode=AUTO_MODE;//自动主
////////////								AutoModePage_dis(); //返回 ----------- 自动
////////////								//------------返回第一刀
////////////								// // ClrInput_function();//清零 输入框 
////////////								CursorKnife_dis(cursor_row, 0);//红色光标消失
////////////								cursor_row=0;
////////////								CursorKnife_dis(cursor_row, 1);//红色光标显示
////////////								Knife_order=1;//
////////////								Size_1page_dis(Knife_order,0);//一页尺寸显示
////////////								if(Knife_order<=OnePro_head.pro_knifeSUM)
////////////									StepOrder_dis(Knife_order);//步骤更新 
////////////								}
							}
						 }
					 else
						 {
						 if(IR_Up_flag==0)
							{
							IR_Up_flag=1;
							IR_Down_flag=0;
							}
						 }
					
				
					//************************
					if(PaperCutEnb_signal==1)
						{
						PaperCutEnb_signal++;
						OneKnife_sign_mod=0;
						NewKnife_sign_mod=0;
						OnePress_sign_mod=0;
						}
					else if(PaperCutEnb_signal==2)	
						{
						if((OneKnife_sign_mod==3)&&(OnePress_sign_mod==3)&&(NewKnife_sign_mod==3))  //一个裁切循环
							{
							PressCircle_mode=0;PressFlagRunCou=0;	
							if((AllPressUp_flag==1)&&(AllKnifeUp_flag==1))
								{
								CutPressRoll_flag=1;
							//**************刀前 尺寸更新
								if(Run_flag==0)
									{
									if(InTargetPosit_flag==1)	//目标位置
										{
										if(Unit!=UNIT_MM)//inch
											BeforeKnife_offset_in=TargetSize_inch;
										}
									BeforeKnife_offset=CurrentSize_temp;
										if(YaZhi_Process_Flag==0)//非压纸处理时入
												FrontKnifeSize_dis(0);
									BeforeKnifeNo_flag=0;
									BeforeKnifeSize=0;
									}
							//------
								if(WorkMode==TEACH_MODE)//示教 模式--------更新一个数据
									{
									RenewOneKnife_data();//CurrentSize
									}
								else if((WorkMode==AUTO_MODE)||(WorkMode==SELF_CUT_MODE))  //自动 自刀 模式
									{
									if(Run_flag==0)
										{
										if((GoFrontEn_flag==0)&&(GoBackEn_flag==0))
											{
											volatile pInt8U pdata=(pInt8U)&OneKnife_data;
											volatile Int32U size_now;
											GetOneKnife_datas(Pro_data.pro_num, Knife_order, pdata);//
											if(Unit==UNIT_MM)//mm
												{
												if(InTargetPosit_flag==1) 	//目标位置
													size_now=TargetSize_temp;
												else	
													size_now=CurrentSize;
												}
											else
												{
												if(InTargetPosit_flag==1) 	//目标位置
													size_now=TargetSize_inch;
												else	
													size_now=CurrentSize*100/254;
												}	
											if(size_now==OneKnife_data.size)
												{
												if(MotorType<MOTOR_AC_SERVO)
													{
													if(ToTargetStop_flag==1)
														{
														// if(InTargetPosit_flag==1)	//已停在 目标位置		20171017屏蔽
															AutoRun_AutoPush_exec();  // 自动 循环运行
														}
													else   //非 自锁
														AutoRun_AutoPush_exec();  // 自动 循环运行
													}
												else	
													AutoRun_AutoPush_exec();  // 自动 循环运行
												}											
											OneCutRoutine_flag=1;
											}
										}
									}
								OneKnife_sign_mod=0;
								NewKnife_sign_mod=0;
								OnePress_sign_mod=0;
								CutPressRoll_flag=0;
								}
							else
								{
								
								}
								
							}
						else
							{
							// // if(MotorType!=MOTOR_DC670_SERVO)
								NewKnife_sign_mod=0;
							if(((OneKnife_sign_mod&0x3)==3)||((OnePress_sign_mod&0x3)==3)||((NewKnife_sign_mod&0x3)==3))
								{
								CutRelease_time++;
								if(CutRelease_time>2000)   //超时 裁切信号消失
									{
									CutRelease_time=0;
									OneKnife_sign_mod=0;
									NewKnife_sign_mod=0;
									OnePress_sign_mod=0;
									CutPressRoll_flag=0;
									}
								}
							}
						}
					
					//--------------------------------------------压纸循环
					if(Run_flag==0)
						{
						if((WorkMode == AUTO_MODE)||(WorkMode == SELF_CUT_MODE))
							{
							if(PressCircle_mode== 2)
								{
								PressCircle_mode=0;
									
								if((YaZhi_Process_Flag==0)&&(OptimizeCut_Enb_Flag==0)) //已进入，退出  优化裁切不入
										{
										PressSignalFlagRun();
										}
								   //PressSignalFlagRun();
								}
							}
						}
						
					//------------
					OutLimit_check(); //外部限位	
							break;	
			case MANUAL_IO_TEST_MODE:	//测试端口
					IOinputTest();//IO  输入测试*******
							break;	
			}	
					 
			
		
		DisplayFlashTime++;
		if(DisplayFlashTime>=2)
			{
			DisplayFlashTime=0;
			NowSizeNum_dis();  // 尺寸实时 显示
			}
		 
		if(Carrier_IN==0)  //托板 信号
			{
			if(Hold_Down_flag==0)
				{
				Hold_Down_flag=1;
				Hold_Up_flag=0;
				Size_MIN=FrontLimit;
				if(Unit==UNIT_MM)
					Size_MIN_num=Size_MIN;
				else
					Size_MIN_num=Size_MIN*100/254;
				if(PromptDis_flag==1)
					PromptNum_dis();
				}
			}
		else
			{
			if(Hold_Up_flag==0)
				{
				Hold_Up_flag=1;
				Hold_Down_flag=0;
				Size_MIN=MiddleLimit;
				if(Unit==UNIT_MM)
					Size_MIN_num=Size_MIN;
				else
					Size_MIN_num=Size_MIN*100/254;
				if(PromptDis_flag==1)
					PromptNum_dis();
				}
			}  
		
		 
		//******************运行控制	
		if(Run_flag==1)
			{
			if(RunStop_flag==0)
				{
				switch(MotorType) 
					{
					case MOTOR_AC_SERVO:
						ACMotorRunning_ctrl(); //交流伺服 运行控制
						AC_MotorRuningLimit_ctrl();  //运行中  到外部信号 停止
								break;
					}
				}
			
			}	
		else 		
			{
			if(RunStop_flag==1)
				{//自动减速停止后				
				switch(MotorType)
					{
					case MOTOR_AC_SERVO:
						stop_time++;
						if(stop_time>150)	
							{
							RunStop_flag=0;
							if(AutoPushRun_flag==1)   //自动  推纸 结束后--------------------------------
								{
								//CursorDown_inTable();//**** 光标下移 显示 数据
								RunTo_cursor();//    运行到当前刀
								AutoPushRun_flag=0;
								}
							else   //------------停止在 目标位置
								{
									
								//////////////////////////////////////////
								//压纸程序处理
								YaZhi_CheckData();
																		
								TargetBell_flag=1;  //蜂鸣器 启动
								TargetBell_mode=0;

								if(YaZhi_Process_Flag==0)
										{
										AutoCutPush_exec();  //自动裁切	
										//OneCutRoutine_flag=0;
										InTargetPosit_flag=1;	//在目标位置
										
										//-----------
										if(WorkMode == AUTO_MODE)//自动
											{
											if(Knife_order==OnePro_head.pro_knifeSUM)	//运行到 last刀
												{
												if(AmendSwitch_flag==1)//偏移量 运行模式 开启-----------------------------------------------
													{
													// AmendSize=0;
													// AmendStartRun_flag=0;
													AmendOver_flag=1;	//偏移量 运行模式 over
													}
												}
											else//(Knife_order==1)	//运行到 第一刀	
												{
												AmendOver_flag=0;
												}
											}
										}
								
								}
							}
							
							break;
					}		
				}
			else
				{
	//			Joggle_GoFast(); //点动

				CutEnable_Exec();  //裁切 操作 

				AirBed_Exec();//气阀控制
				}
			} 			
		}
}


void App_WorkLoop_InitModeRun(void)
{
if(WorkStart_flag==0)  //未进入工作状态	开机后的初始画面
	{
	if(Board_TestMod==0)//非功能测试模式
			{
			if(APP_MODBUS_MOTION==1)
					{		//没进入前，不处理
						if(RunDisplay_flag==0)
						{
							RunDisplay_flag=1;
									GLCD_SetWindow_Fill( START_PROMPT_X2, START_PROMPT_Y2, START_PROMPT_X2-1+START_PROM_WIDE, START_PROMPT_Y2-1+30, 0xffff, 0xffff);//提示框
							switch(Language)
							{
								case CHN_HAN:
									Printf24("电脑检测完成,请按运行键!>点此处",START_PROMPT_X2,START_PROMPT_Y2+5,RED_COLOR,1,0xffff);
									break;
								case ENGLISH:
									Printf24("Computer testing OK, press the RUN key!",START_PROMPT_X2,START_PROMPT_Y2+5,RED_COLOR,1,0xffff);
									break;
								case INDONSIA:
									Printf24("Tes komputer OK, tekan tombol RUN!",START_PROMPT_X2,START_PROMPT_Y2+5,RED_COLOR,1,0xffff);
									break;
								
							}
						}
					}
			else
					{					
					switch(MotorType)
						{
						case MOTOR_AC_SERVO:	
							if(ACServoDrvErr_flag==0)
								ACServoWorkStart_check();  //交流伺服  工作模式前  准备
							else	
								{
								
								}
								break;
						}
					}
			}
	}	
}
