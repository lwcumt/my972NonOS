

#include"touch.h"
#include"tsc2046.h"

#include"key.h"
#include"m25pe16.h"
#include"io.h"
#include "port.h"





Int16U Touch_down_time;
Int16U Touch_release_time;
Int16U Touch_long_time;
Int8U Touch_down_flag; 
Int8U Touch_exec_flag; 
Int8U Touch_long_exec_flag; 
Int8U Touch_start_flag;

TOUCH TouchAD_LU;
TOUCH TouchAD_LD;
TOUCH TouchAD_RU;
TOUCH TouchAD_RD;
TOUCH TouchAD_MID;

TOUCH Touch_Pos;

Int32U TouchDegree_x;
Int32U TouchDegree_y;

Int32U Touch_code;
Int32U TouchLong_code;


//-----touch校准 系数
unsigned int A0;
unsigned int A1;
unsigned int A2;
unsigned int A3;
unsigned int A4;
unsigned int A5;
unsigned int A6;

// Int16U touchAD_x[5];
// Int16U touchAD_y[5];


void Read_TouchDatas(void)
{
pInt8U pdata;
Int32U add;
Int8U n;
add=ORIGINAL_25PEADD+80;//80+4*7	=	80+28
pdata=(pInt8U)&A0;
FastRead_Datas_Start(add);
for(n=0;n<4;n++)
	{
	*pdata++=ReadFlash_Datas();
	}
pdata=(pInt8U)&A1;
for(n=0;n<4;n++)
	{
	*pdata++=ReadFlash_Datas();
	}
pdata=(pInt8U)&A2;
for(n=0;n<4;n++)
	{
	*pdata++=ReadFlash_Datas();
	}
pdata=(pInt8U)&A3;
for(n=0;n<4;n++)
	{
	*pdata++=ReadFlash_Datas();
	}
pdata=(pInt8U)&A4;
for(n=0;n<4;n++)
	{
	*pdata++=ReadFlash_Datas();
	}
pdata=(pInt8U)&A5;
for(n=0;n<4;n++)
	{
	*pdata++=ReadFlash_Datas();
	}
pdata=(pInt8U)&A6;
for(n=0;n<4;n++)
	{
	*pdata++=ReadFlash_Datas();
	}
FlashChip_Dis;
/***
pdata=(pInt8U)&TouchDegree_x;
FastRead_Datas_Start(add);
for(n=0;n<4;n++)
	{
	*pdata++=ReadFlash_Datas();
	}
pdata=(pInt8U)&TouchDegree_y;	
for(n=0;n<4;n++)
	{
	*pdata++=ReadFlash_Datas();
	}
pdata=(pInt8U)&TouchAD_MID;
for(n=0;n<8;n++)
	{
	*pdata++=ReadFlash_Datas();
	}	
FlashChip_Dis;
if((TouchDegree_x<100000)||(TouchDegree_x>300000)
	||(TouchDegree_y<100000)||(TouchDegree_y>200000)
	||(TouchAD_MID.x<1800)||(TouchAD_MID.x>2200)
	||(TouchAD_MID.y<1500)||(TouchAD_MID.y>2200))       //未校准 值
	{
	TouchDegree_x=TOU_DEGREE_X;
	TouchDegree_y=TOU_DEGREE_Y;
	TouchAD_MID.x=TOU_OFFSET_X;
	TouchAD_MID.y=TOU_OFFSET_Y;
	}
	***/
}
void Save_TouchDatas(void)
{
pInt8U pdata;
Int32U add;
add=ORIGINAL_25PEADD+80;	//80+4*7	=	80+28
pdata=(pInt8U)&A0;
Write_25pe_data(pdata, add, 4);add+=4;
pdata=(pInt8U)&A1;
Write_25pe_data(pdata, add, 4);add+=4;
pdata=(pInt8U)&A2;
Write_25pe_data(pdata, add, 4);add+=4;
pdata=(pInt8U)&A3;
Write_25pe_data(pdata, add, 4);add+=4;
pdata=(pInt8U)&A4;
Write_25pe_data(pdata, add, 4);add+=4;
pdata=(pInt8U)&A5;
Write_25pe_data(pdata, add, 4);add+=4;
pdata=(pInt8U)&A6;
Write_25pe_data(pdata, add, 4);add+=4;
/***
pdata=(pInt8U)&TouchDegree_x;
Write_25pe_data(pdata, add, 4);add+=4;
pdata=(pInt8U)&TouchDegree_y;
Write_25pe_data(pdata, add, 4);add+=4;
pdata=(pInt8U)&TouchAD_MID;
Write_25pe_data(pdata, add, 8);
****/
}


void ToucScan(void)
{
if(Touch_down_flag==0)
	{
	if(Touch_start_flag==0)
		{
		if(TOUCH_INT_PIN==0)
		//if(TouchAD_get()==1)//触摸有效
			{
			Touch_start_flag=1;
			Touch_down_time=0;
			}
		}
	else
		{
		Touch_down_time++;
		if(Touch_down_time>=30)
			{
			Touch_down_time=0;
			Touch_down_flag=1;
			Touch_start_flag=0;
			}
		}
	}
else
	{
	if(Touch_exec_flag==0)
		{
		//if(TOUCH_INT_PIN==0)
		if(TouchAD_get()==1)//触摸有效
			{
			Touch_down_time++;
			if(Touch_down_time>=TOU_SHAKE_TIME)
				{
				Touch_down_time=0;
				Touch_release_time=0;
				LED2_ON;
				Touch_exec_flag=1;
				Touch_long_time=0;
				//if(TouchAD_get()==1)//触摸有效
					{
					if(Board_TestMod<=TEST_TOUCH)	//非 主板 端口测试
						TouchKey_exec();  //触摸键  处理
					}
			
				}
			}	
		else
			{
			Touch_down_flag=0;
			}
		}
	else  //等待释放
		{
		if(TOUCH_INT_PIN!=0)   //中断引脚  释放
			{
			Touch_release_time++;
			if(Touch_release_time>TOU_SHAKE_TIME)
				{LED2_OFF;
				Touch_release_time=0;
				Touch_exec_flag=0;
				Touch_down_flag=0;
				Touch_long_exec_flag=0;
				GoFrontEn_flag=0;
				GoBackEn_flag=0;
				//---------------------------
				if(TouchLong_code==0)
					TouchButton_dis(Touch_code,0);  //触摸键  显示
				else
					TouchButton_dis(TouchLong_code,0);  //触摸键  显示
				Touch_code=0;//-------释放后 清触摸键值
				ACMotor_ReleaseStop();
				}
			}
		else  //引脚有干扰时   扫描值    释放
			{
			Touch_release_time=0;
			if(TouchAD_get()!=1)//触摸
				{
				Touch_down_time++;
				if(Touch_down_time>=TOU_SHAKE_TIME)
					{LED2_OFF;
					Touch_exec_flag=0;
					Touch_down_flag=0;
					Touch_long_exec_flag=0;
					GoFrontEn_flag=0;
					GoBackEn_flag=0;
					//---------------------------
					if(TouchLong_code==0)
						TouchButton_dis(Touch_code,0);  //触摸键  显示
					else
						TouchButton_dis(TouchLong_code,0);  //触摸键  显示
					Touch_code=0;//-------释放后 清触摸键值
					ACMotor_ReleaseStop();
					}
				}
			else
				{
				Touch_down_time=0;
				//----------未释放
				// if(TouchAD_get()==1)//触摸有效
					// {
					if(Board_TestMod==TEST_BOARD)  //主板功能测试mode-------------------------------
						{
						GetTouch_pos();
						if(Touch_Pos.x>=C_GLCD_H_SIZE)
							Touch_Pos.x=C_GLCD_H_SIZE-1;
						if(Touch_Pos.y>=C_GLCD_V_SIZE)
							Touch_Pos.y=C_GLCD_V_SIZE-1;
						PutPixel(Touch_Pos.x,Touch_Pos.y,RED_COLOR);//手写
						}
					else
						{
						Touch_long_time++;
						if(Touch_long_time>=TOUCH_ERR_TIME)  ////---------------------------触摸  按下时间过长，强制释放
							{	
							if(TouchLong_code==0)
								TouchButton_dis(Touch_code,0);  //触摸键  显示
							else
								TouchButton_dis(TouchLong_code,0);  //触摸键  显示
							Touch_code=0;//-------释放后 清触摸键值
							
							Touch_exec_flag=0;
							Touch_down_flag=0;
							Touch_long_exec_flag=0;
							GoFrontEn_flag=0;
							GoBackEn_flag=0;
							}
						}
					//}
				}
			}
		
		}
	}
}


void TouchKey_exec(void)
{
// volatile Int16U tAD,gap;
volatile Int16U T_X[5],T_Y[5];

double  x, y, x2, y2, xy, z, zx, zy;
double det, a, b, c, e, f, i;
double scaling = 65536.0;//500.0;//65536.0;
Int8U n;
volatile Int16U diff;

if(Board_TestMod==TEST_TOUCH)//校准处理
	{
	switch(TouchCalcu_mode)
		{
			/***
		case 0://左上
			TouchAD_LU.x=TouchAD.x;
			TouchAD_LU.y=TouchAD.y;
			Draw_cross(TOUCH_X1,TOUCH_Y1,WHITE_COLOR);
			Draw_cross(TOUCH_X2,TOUCH_Y2,RED_COLOR);
			TouchCalcu_mode++;
				break;
		case 1://左下
			TouchAD_LD.x=TouchAD.x;
			TouchAD_LD.y=TouchAD.y;
			Draw_cross(TOUCH_X2,TOUCH_Y2,WHITE_COLOR);
			Draw_cross(TOUCH_X3,TOUCH_Y3,RED_COLOR);
			TouchCalcu_mode++;
			
				break;
		case 2://右下
			TouchAD_RD.x=TouchAD.x;
			TouchAD_RD.y=TouchAD.y;
			Draw_cross(TOUCH_X3,TOUCH_Y3,WHITE_COLOR);
			Draw_cross(TOUCH_X4,TOUCH_Y4,RED_COLOR);
			TouchCalcu_mode++;	
				break;
		case 3://右上
			TouchAD_RU.x=TouchAD.x;
			TouchAD_RU.y=TouchAD.y;
			Draw_cross(TOUCH_X4,TOUCH_Y4,WHITE_COLOR);
			Draw_cross(TOUCH_X_MID,TOUCH_Y_MID,RED_COLOR);
			#ifdef	LCD_TOUCH_REVERSE
			//tAD=((TouchAD_LU.x+TouchAD_LD.x)>>1)-((TouchAD_RU.x+TouchAD_RD.x)>>1);
				tAD=((TouchAD_RU.x+TouchAD_RD.x)>>1)-((TouchAD_LU.x+TouchAD_LD.x)>>1);
			#else
				tAD=((TouchAD_LU.x+TouchAD_LD.x)>>1)-((TouchAD_RU.x+TouchAD_RD.x)>>1);
			#endif	
			gap=TOUCH_X3-TOUCH_X1;
			TouchDegree_x=gap*1000000/tAD;
			#ifdef	LCD_TOUCH_REVERSE
			//tAD=((TouchAD_LU.y+TouchAD_RU.y)>>1)-((TouchAD_LD.y+TouchAD_RD.y)>>1);
				tAD=((TouchAD_LD.y+TouchAD_RD.y)>>1)-((TouchAD_LU.y+TouchAD_RU.y)>>1);
			#else
				tAD=((TouchAD_LU.y+TouchAD_RU.y)>>1)-((TouchAD_LD.y+TouchAD_RD.y)>>1);
			#endif	
			gap=TOUCH_Y2-TOUCH_Y1;
			TouchDegree_y=gap*1000000/tAD;
			TouchCalcu_mode++;
				break;
		case 4://中心
			TouchAD_MID.x=TouchAD.x;
			TouchAD_MID.y=TouchAD.y;
			Draw_cross(TOUCH_X_MID,TOUCH_Y_MID,WHITE_COLOR);
			Save_TouchDatas();//-------------------保存校准值
			//---------
			Bmp_Decode((Int32U)START_PIC_sdram, 0, 0, (pInt16U)SDRAM0_BASE_ADDR); //显示开机画面
			Board_TestMod=0;
			RunDisplay_flag=0;
			outF_flag=0;
			outM_flag=0;
			outB_flag=0;
			Wheel_flag=0;
			OutFront_limit=0;
			OutMiddle_limit=0;
			OutBack_limit=0;
			Wheel_limit=0;
			OriginalError_flag=0;
			BackLimitError_flag=0;StartCheck_mode=0;
				break;
				***/
		case 0://左上
				for(n=0;n<5;n++)
					{
					T_X[n] = T_Y[n] = 0;
					}
				x = y = x2 = y2 = xy = 0;
				Draw_cross(TOUCH_X1,TOUCH_Y1,WHITE_COLOR);
				Draw_cross(TOUCH_X2,TOUCH_Y2,RED_COLOR);
					break;
		case 1://左下
			
			Draw_cross(TOUCH_X2,TOUCH_Y2,WHITE_COLOR);
			Draw_cross(TOUCH_X3,TOUCH_Y3,RED_COLOR);
				break;
		case 2://右下
			Draw_cross(TOUCH_X3,TOUCH_Y3,WHITE_COLOR);
			Draw_cross(TOUCH_X4,TOUCH_Y4,RED_COLOR);
				break;
		case 3://右上
			Draw_cross(TOUCH_X4,TOUCH_Y4,WHITE_COLOR);
			Draw_cross(TOUCH_X_MID,TOUCH_Y_MID,RED_COLOR);
			
				break;
		case 4://中心
			Draw_cross(TOUCH_X_MID,TOUCH_Y_MID,WHITE_COLOR);
			
				break;
		}
	if(TouchCalcu_mode<5)
		{
		T_X[TouchCalcu_mode]=TouchAD.x;
		T_Y[TouchCalcu_mode]=TouchAD.y;
		TouchCalcu_mode++;
		}
		//------------touch screen  5 point 校准-------算法------
	if(TouchCalcu_mode>=5)
		{
		//------------save touch set ad
		// for(n=0;n<5;n++)
			// {
			// touchAD_x[n]=T_X[n];
			// touchAD_y[n]=T_Y[n];
			// }
		// SaveTouchAD();	//5点 保存值
		//----------------
		for(n=0;n<5;n++)
			{
			x += (double)T_X[n];
			y += (double)T_Y[n];
			x2 += (double)(T_X[n]*T_X[n]);
			y2 += (double)(T_Y[n]*T_Y[n]);
			xy += (double)(T_X[n]*T_Y[n]);
			}
		det = 5*(x2*y2 - xy*xy) + x*(xy*y - x*y2) + y*(x*xy - y*x2);
			
		a = ((x2*y2) - (xy*xy))/det;
		b = ((xy*y) - (x*y2))/det;
		c = ((x*xy) - (y*x2))/det;
		e = ((5*y2) - (y*y))/det;
		f = ((x*y) - (5*xy))/det;
		i = ((5*x2) - (x*x))/det;
		
		z = zx = zy = 0;//-------------------------------------
		z += (double)(TOUCH_X1+TOUCH_X2+TOUCH_X3+TOUCH_X4+TOUCH_X_MID);
		zx += (double)(TOUCH_X1*T_X[0]);
		zy += (double)(TOUCH_X1*T_Y[0]);
		
		zx += (double)(TOUCH_X2*T_X[1]);
		zy += (double)(TOUCH_X2*T_Y[1]);
		
		zx += (double)(TOUCH_X3*T_X[2]);
		zy += (double)(TOUCH_X3*T_Y[2]);
		
		zx += (double)(TOUCH_X4*T_X[3]);
		zy += (double)(TOUCH_X4*T_Y[3]);
		
		zx += (double)(TOUCH_X_MID*T_X[4]);
		zy += (double)(TOUCH_X_MID*T_Y[4]);
		
		A0 = (int)(((a*z) + (b*zx) + (c*zy))*(scaling));
		A1 = (int)(((b*z) + (e*zx) + (f*zy))*(scaling));
		A2 = (int)(((c*z) + (f*zx) + (i*zy))*(scaling));
		
		z = zx = zy = 0;//-------------------------------------
		z += (double)(TOUCH_Y1+TOUCH_Y2+TOUCH_Y3+TOUCH_Y4+TOUCH_Y_MID);
		zx += (double)(TOUCH_Y1*T_X[0]);
		zy += (double)(TOUCH_Y1*T_Y[0]);

		zx += (double)(TOUCH_Y2*T_X[1]);
		zy += (double)(TOUCH_Y2*T_Y[1]);

		zx += (double)(TOUCH_Y3*T_X[2]);
		zy += (double)(TOUCH_Y3*T_Y[2]);

		zx += (double)(TOUCH_Y4*T_X[3]);
		zy += (double)(TOUCH_Y4*T_Y[3]);

		zx += (double)(TOUCH_Y_MID*T_X[4]);
		zy += (double)(TOUCH_Y_MID*T_Y[4]);
		
		A3 = (int)(((a*z) + (b*zx) + (c*zy))*(scaling));
		A4 = (int)(((b*z) + (e*zx) + (f*zy))*(scaling));
		A5 = (int)(((c*z) + (f*zx) + (i*zy))*(scaling));
		
		A6 = (int)scaling; 
		
		//--------保存 退出-----------------------------
		Save_TouchDatas();//-------------------保存校准值
		//---------
		Bmp_Decode((Int32U)START_PIC_sdram, 0, 0, (pInt16U)SDRAM0_BASE_ADDR); //显示开机画面
		Board_TestMod=0;
		RunDisplay_flag=0;
		outF_flag=0;
		outM_flag=0;
		outB_flag=0;
		Wheel_flag=0;
		OutFront_limit=0;
		OutMiddle_limit=0;
		OutBack_limit=0;
		Wheel_limit=0;
		OriginalError_flag=0;
		BackLimitError_flag=0;StartCheck_mode=0;
		}
	}
else
	{
	GetTouchKeyCode();// 获得触摸 键值
	//************************************触摸按钮 显示 处理*********
	if(TouchLong_code==0)
		TouchButton_dis(Touch_code,1);  //触摸键  显示
	else
		TouchButton_dis(TouchLong_code,1);  //触摸键  显示
	//************************触摸键 功能处理**********************
	if(Touch_code!=0)
		{
		if(TouchLong_code==0)
			{
			KeyExec(Touch_code); //调键处理
			MultiKey_exec(Touch_code);//原 组合键处理
			}
		else
			LongKey_exec(TouchLong_code,TouchLong_code);  //原 长按键处理
		}
	}
}

void GetTouch_pos(void) //得到触摸 坐标
{
	/****
volatile Int32U offset,temp;
//---------------------x
if(TouchAD.x>TouchAD_MID.x)
	{
	offset=(TouchAD.x-TouchAD_MID.x)*TouchDegree_x;
	temp=offset/1000000;
	if(temp>TOUCH_X_MID)
		Touch_Pos.x=0;
	else
		{
		#ifdef	LCD_TOUCH_REVERSE
		//Touch_Pos.x=TOUCH_X_MID-temp;
			Touch_Pos.x=TOUCH_X_MID+temp;
		#else
			Touch_Pos.x=TOUCH_X_MID-temp;
		#endif	
		}
	}
else
	{
	offset=(TouchAD_MID.x-TouchAD.x)*TouchDegree_x;
	temp=offset/1000000;
	#ifdef	LCD_TOUCH_REVERSE
	//Touch_Pos.x=TOUCH_X_MID+temp;
		Touch_Pos.x=TOUCH_X_MID-temp;
	#else
		Touch_Pos.x=TOUCH_X_MID+temp;
	#endif	
	if(Touch_Pos.x>C_GLCD_H_SIZE)
		Touch_Pos.x=C_GLCD_H_SIZE;
	}	
//----------------------y	
if(TouchAD.y>TouchAD_MID.y)
	{
	offset=(TouchAD.y-TouchAD_MID.y)*TouchDegree_y;
	temp=offset/1000000;
	if(temp>TOUCH_Y_MID)
		Touch_Pos.y=0;
	else
		{
		#ifdef	LCD_TOUCH_REVERSE
		//Touch_Pos.y=TOUCH_Y_MID-temp;
			Touch_Pos.y=TOUCH_Y_MID+temp;
		#else
			Touch_Pos.y=TOUCH_Y_MID-temp;
		#endif	
		}
	}
else
	{
	offset=(TouchAD_MID.y-TouchAD.y)*TouchDegree_y;
	temp=offset/1000000;
	#ifdef	LCD_TOUCH_REVERSE
	//Touch_Pos.y=TOUCH_Y_MID+temp;
		Touch_Pos.y=TOUCH_Y_MID-temp;
	#else
		Touch_Pos.y=TOUCH_Y_MID+temp;
	#endif	
	if(Touch_Pos.y>C_GLCD_V_SIZE)
		Touch_Pos.y=C_GLCD_V_SIZE;
	}	
	***/
Touch_Pos.x=TouchAD.x;//(A0 + A1*TouchAD.x + A2*TouchAD.y ) / A6;
Touch_Pos.y=TouchAD.y;//(A3 + A4*TouchAD.x + A5*TouchAD.y ) / A6;


////////Touch_Pos.x=(A0 + A1*TouchAD.x + A2*TouchAD.y ) / A6;
////////Touch_Pos.y=(A3 + A4*TouchAD.x + A5*TouchAD.y ) / A6;
}

void GetTouchKeyCode(void) //获取 触摸键值
{
Touch_code=0,TouchLong_code=0;
GetTouch_pos();	     //-----------------获得 触摸坐标位值-------------------------
if(WorkStart_flag==0)  //未进入工作状态
	{
	if((Touch_Pos.y>=START_Y1)&&(Touch_Pos.y<=START_Y2))
		{
		if((Touch_Pos.x>=START_X1)&&(Touch_Pos.x<=START_X2))
			Touch_code=START_TOUCH_CODE;      //开机 运行
		}
	else if((Touch_Pos.y>=PUSH_RESET_OK_Y1)&&(Touch_Pos.y<=PUSH_RESET_OK_Y2))//推纸器 复位 提示
		{
		if((Touch_Pos.x>=PUSH_RESET_OK_X1)&&(Touch_Pos.x<=PUSH_RESET_OK_X2))
			Touch_code=PUSH_OK_TOUCH_CODE; //OK
		else if((Touch_Pos.x>=PUSH_RESET_CANCEL_X1)&&(Touch_Pos.x<=PUSH_RESET_CANCEL_X2))
			Touch_code=PUSH_CANCEL_TOUCH_CODE;//cancel	
		}
		//------------Jog按钮
	if(OutBack_limit==1)
		{
		if((Touch_Pos.y>=START_JOG_BACK_Y1)&&(Touch_Pos.y<=START_JOG_BACK_Y2))
			{
			if((Touch_Pos.x>=START_JOG_BACK_X1)&&(Touch_Pos.x<=START_JOG_BACK_X2))
				Touch_code=ADJUST_KEY_CODE;    //后退按键
			else if((Touch_Pos.x>=START_JOG_FORW_X1)&&(Touch_Pos.x<=START_JOG_FORW_X2))
				Touch_code=NEXTKNIFE_KEY_CODE;  //前进按键
			}
		}
	if(Board_TestMod == 0)// start
		{
		if((Touch_Pos.x>=START_F1_TOU_X1)&&(Touch_Pos.x<=START_F1_TOU_X2))
			{
			if((Touch_Pos.y>=START_F1_TOU_Y1)&&(Touch_Pos.y<=START_F1_TOU_Y2))
				Touch_code=AUTO_KEY_CODE;       // F1
			}
		}
	}
else
	{
	if(Touch_code==0)
		{
		if((Touch_Pos.y>=DELETE_Y1)&&(Touch_Pos.y<=DELETE_Y2))	
			{
			if((Touch_Pos.x>=INPUT_X1)&&(Touch_Pos.x<=INPUT_X2))
				Touch_code=INPUT_TOUCH_CODE; //输入框 触摸键
			}	
		// if((WorkMode&MANUAL_MODE)==MANUAL_MODE)  //手动模式
			// {
			// if((Touch_Pos.y>=MAN_STOP_Y1)&&(Touch_Pos.y<=MAN_STOP_Y2))	
				// {
				// if((Touch_Pos.x>=MAN_STOP_X1)&&(Touch_Pos.x<=MAN_STOP_X2))	
					// Touch_code=STOP_TOUCH_CODE; //停止 触摸键
				// }
			// }
		
		if(InputTouch_flag==0)
			{
			if(Touch_code==0)
				{
				switch(WorkMode)
					{
					case  PROG_MODE://编程画面下
					case AUTO_MODE://自动主画面下
					case AUTO_PLUS_MODE://自动F3++
					case AUTO_MINUS_MODE://自动F4--
					case TEACH_MODE://示教 模式
					// case AUTO_TO_SELF_MODE:   //自动-->自刀过度 模式
					case SELF_CUT_MODE:  //自刀主 模式
					case SELF_PLUS_MODE: //自刀 F3++
					case SELF_MINUS_MODE://自刀 F4--
						if(Touch_Pos.y>=F_KEY_Y1)
							{
							
							if((Touch_Pos.x>=F_KEY_X1)&&(Touch_Pos.x<=F_KEY_X2))
								{
								if(Touch_Pos.y<=F_KEY_Y2)
									Touch_code=F_TOUCH_CODE;    //F 键 触摸
								}
							else if((Touch_Pos.x>=WORK_MODE_X1)&&(Touch_Pos.x<=WORK_MODE_X2))
								{
								if(Touch_Pos.y<=WORK_MODE_Y2)
									Touch_code=MODE_TOUCH_CODE;        //模式 切换按钮
								}
							if((WorkMode==PROG_MODE)||(WorkMode==TEACH_MODE))
								{
								if((Touch_Pos.x>=DELETE_X1)&&(Touch_Pos.x<=DELETE_X2))	
									{
									if((Touch_Pos.y>=DELETE_Y1)&&(Touch_Pos.y<=DELETE_Y2))
										Touch_code=FIVE_KEY_CODE;		//删除按键
									else if((Touch_Pos.y>=RUN_Y1)&&(Touch_Pos.y<=RUN_Y2))	
										Touch_code=UP_KEY_CODE;   ///////////运行
									}
								else if((Touch_Pos.x>=DELETE_ALL_X1)&&(Touch_Pos.x<=DELETE_ALL_X2))
									{
									if((Touch_Pos.y>=DELETE_Y1)&&(Touch_Pos.y<=DELETE_Y2))
										Touch_code=DELETE_ALL_TOUCH_CODE;//全删 触摸键
									else if((Touch_Pos.y>=STOP_Y1)&&(Touch_Pos.y<=STOP_Y2))	
										Touch_code=STOP_TOUCH_CODE; //停止 触摸键
									}
								}
							else
								{	// 运行 停止 big button
								if((Touch_Pos.y>=RUN_BIG_Y1)&&(Touch_Pos.y<=RUN_BIG_Y2))
									{
									if((Touch_Pos.x>=RUN_BIG_X1)&&(Touch_Pos.x<=RUN_BIG_X2))
										Touch_code=UP_KEY_CODE;   ///////////运行
									else if((Touch_Pos.x>=STOP_BIG_X1)&&(Touch_Pos.x<=STOP_BIG_X2))
										Touch_code=STOP_TOUCH_CODE; //停止 触摸键
									}
								}
							
							}
						else
							{
							if((Touch_Pos.x>=UP_TO_X1)&&(Touch_Pos.x<=UP_TO_X2))
								{
								if((Touch_Pos.y>=UP_TO_Y1)&&(Touch_Pos.y<=UP_TO_Y2))
									Touch_code=DENGJU_KEY_CODE;  //向上箭头按键
								else if((Touch_Pos.y>=DOWN_TO_Y1)&&(Touch_Pos.y<=DOWN_TO_Y2))
									Touch_code=DENGFENG_KEY_CODE;  //向下箭头
								}
							else if((Touch_Pos.x>=BACKWARD_X1)&&(Touch_Pos.x<=F0CUT_BUTTON_X2))
								{
								if((Touch_Pos.y>=FORWARD_Y1)&&(Touch_Pos.y<=FORWARD_Y2))
									{
									if((Touch_Pos.x>=FORWARD_X1)&&(Touch_Pos.x<=FORWARD_X2))
										Touch_code=NEXTKNIFE_KEY_CODE;  //前进按键
									else if((Touch_Pos.x>=BACKWARD_X1)&&(Touch_Pos.x<=BACKWARD_X2))
										Touch_code=ADJUST_KEY_CODE;    //后退按键
									else if((Touch_Pos.x>=F5CUT_BUTTON_X1)&&(Touch_Pos.x<=F5CUT_BUTTON_X2))
										Touch_code=F5CUT_TOUCH_CODE;   //F5  刀 标记
									else if((Touch_Pos.x>=F0CUT_BUTTON_X1)&&(Touch_Pos.x<=F0CUT_BUTTON_X2))
										Touch_code=F0CUT_TOUCH_CODE;   //F0  刀 标记
									}
								}
							else if((Touch_Pos.x>=F1_LABEL_X1)&&(Touch_Pos.x<=F1_LABEL_X2))  //F1~F4	
								{
								if((Touch_Pos.y>=F1_LABEL_Y1)&&(Touch_Pos.y<=F1_LABEL_Y2))
									Touch_code=AUTO_KEY_CODE;       // F1
								else if((Touch_Pos.y>=F2_DIVIDE_Y1)&&(Touch_Pos.y<=F2_DIVIDE_Y2))
									Touch_code=READ_KEY_CODE;       // F2
								else if((Touch_Pos.y>=F3_PROG_Y1)&&(Touch_Pos.y<=F3_PROG_Y2))
									Touch_code=RETURN_KEY_CODE;      //F3
								else if((Touch_Pos.y>=F4_PUSH_Y1)&&(Touch_Pos.y<=F4_PUSH_Y2))
									Touch_code=MANUAL_KEY_CODE;   // F4
								}
							}
								break;
					case AUTO_TO_SELF_MODE:   //自动-->自刀过度 模式
						if((Touch_Pos.y>=SELF_OK_Y1)&&(Touch_Pos.y<=SELF_OK_Y2))
							{
							if((Touch_Pos.x>=SELF_OK_X1)&&(Touch_Pos.x<=SELF_OK_X2))
								Touch_code=DOWN_KEY_CODE;   // 确定
							else if((Touch_Pos.x>=SELF_CANCEL_X1)&&(Touch_Pos.x<=SELF_CANCEL_X2))	
								Touch_code=SIX_KEY_CODE;	// clear 功能  取消
							}
								break;		
					/****
						if((Touch_Pos.x>=F_KEY_X1)&&(Touch_Pos.x<=F_KEY_X2))
							{
							if((Touch_Pos.y>=F_KEY_Y1)&&(Touch_Pos.y<=F_KEY_Y2))
								Touch_code=F_TOUCH_CODE;    //F 键 触摸
							}
						if((Touch_Pos.x>=F1_LABEL_X1)&&(Touch_Pos.x<=F1_LABEL_X2))  //F1~F4
							{
							if((Touch_Pos.y>=F1_LABEL_Y1)&&(Touch_Pos.y<=F1_LABEL_Y2))
								Touch_code=AUTO_KEY_CODE;       // F1
							else if((Touch_Pos.y>=F2_DIVIDE_Y1)&&(Touch_Pos.y<=F2_DIVIDE_Y2))
								Touch_code=READ_KEY_CODE;       // F2
							else if((Touch_Pos.y>=F3_PROG_Y1)&&(Touch_Pos.y<=F3_PROG_Y2))
								Touch_code=RETURN_KEY_CODE;      //F3
							else if((Touch_Pos.y>=F4_PUSH_Y1)&&(Touch_Pos.y<=F4_PUSH_Y2))
								Touch_code=MANUAL_KEY_CODE;   // F4
							}
						if((Touch_Pos.y>=FORWARD_Y1)&&(Touch_Pos.y<=FORWARD_Y2))
							{
							if((Touch_Pos.x>=FORWARD_X1)&&(Touch_Pos.x<=FORWARD_X2))
								Touch_code=NEXTKNIFE_KEY_CODE;  //前进按键
							else if((Touch_Pos.x>=BACKWARD_X1)&&(Touch_Pos.x<=BACKWARD_X2))
								Touch_code=ADJUST_KEY_CODE;    //后退按键
							else if((Touch_Pos.x>=UP_TO_X1)&&(Touch_Pos.x<=UP_TO_X2))
								Touch_code=DENGJU_KEY_CODE;  //向上箭头按键
							else if((Touch_Pos.x>=DOWN_TO_X1)&&(Touch_Pos.x<=DOWN_TO_X2))
								Touch_code=DENGFENG_KEY_CODE;  //向下箭头
							}
						if((Touch_Pos.y>=DELETE_Y1)&&(Touch_Pos.y<=DELETE_Y2))	
							{
							if((WorkMode==PROG_MODE)||(WorkMode==TEACH_MODE))
								{
								if((Touch_Pos.x>=DELETE_X1)&&(Touch_Pos.x<=DELETE_X2))	
									Touch_code=FIVE_KEY_CODE;		//删除按键
								else if((Touch_Pos.x>=DELETE_ALL_X1)&&(Touch_Pos.x<=DELETE_ALL_X2))
									Touch_code=DELETE_ALL_TOUCH_CODE;//全删 触摸键
								}
							}
						if(WorkMode==AUTO_TO_SELF_MODE)  //自动-->自刀过度 模式	
							{
							if((Touch_Pos.y>=SELF_OK_Y1)&&(Touch_Pos.y<=SELF_OK_Y2))
								{
								if((Touch_Pos.x>=SELF_OK_X1)&&(Touch_Pos.x<=SELF_OK_X2))
									Touch_code=DOWN_KEY_CODE;   // 确定
								else if((Touch_Pos.x>=SELF_CANCEL_X1)&&(Touch_Pos.x<=SELF_CANCEL_X2))	
									Touch_code=SIX_KEY_CODE;	// clear 功能  取消
								}
							}
						if(WorkMode==AUTO_MODE)
							{
							// // if(MotorType==MOTOR_AC_SERVO)
								// // {
								// // if((Touch_Pos.x>=WHEEL_SWITCH_X1)&&(Touch_Pos.x<=WHEEL_SWITCH_X2))
									// // {
									// // if((Touch_Pos.y>=WHEEL_SWITCH_Y1)&&(Touch_Pos.y<=WHEEL_SWITCH_Y2))
										// // Touch_code=WHEEL_SWITCH_TOUCH_CODE;   //电子手轮 开关指示
									// // }
								// // }
							// // if((Touch_Pos.y>=F0CUT_BUTTON_Y1)&&(Touch_Pos.y<=F0CUT_BUTTON_Y2))	
								// // {
								// // if((Touch_Pos.x>=F0CUT_BUTTON_X1)&&(Touch_Pos.x<=F0CUT_BUTTON_X2))
									// // {
									// // Touch_code=F0CUT_TOUCH_CODE;   //F0  刀 标记
									// // }
								// // else if((Touch_Pos.x>=F5CUT_BUTTON_X1)&&(Touch_Pos.x<=F5CUT_BUTTON_X2))
									// // {
									// // Touch_code=F5CUT_TOUCH_CODE;   //F5 刀 标记
									// // }
								// // }
							}
						****/
							break;
					case MANUAL_MODE:// 手动 模式
						if(Touch_Pos.y>=F_KEY_Y1)
							{
							//if(Touch_Pos.y<=WORK_MODE_Y2)
								
							if((Touch_Pos.x>=F_KEY_X1)&&(Touch_Pos.x<=F_KEY_X2))
								Touch_code=F_TOUCH_CODE;    //F 键 触摸
							else if((Touch_Pos.x>=WORK_MODE_X1)&&(Touch_Pos.x<=WORK_MODE_X2))
								Touch_code=MODE_TOUCH_CODE;        //模式 切换按钮
							// 运行 停止 big button
							if((Touch_Pos.y>=RUN_BIG_Y1)&&(Touch_Pos.y<=RUN_BIG_Y2))
								{
								if((Touch_Pos.x>=RUN_BIG_X1)&&(Touch_Pos.x<=RUN_BIG_X2))
									Touch_code=UP_KEY_CODE;   ///////////运行
								else if((Touch_Pos.x>=STOP_BIG_X1)&&(Touch_Pos.x<=STOP_BIG_X2))
									Touch_code=STOP_TOUCH_CODE; //停止 触摸键
								}	
								
							}
						else
							{
							if((Touch_Pos.x>=MAN_BACKWARD_X1)&&(Touch_Pos.x<=MAN_FORWARD_X2))
								{
								if((Touch_Pos.y>=MAN_FORWARD_Y1)&&(Touch_Pos.y<=MAN_FORWARD_Y2))
									{
									if((Touch_Pos.x>=MAN_FORWARD_X1)&&(Touch_Pos.x<=MAN_FORWARD_X2))
										Touch_code=NEXTKNIFE_KEY_CODE;  //前进按键
									else if((Touch_Pos.x>=MAN_BACKWARD_X1)&&(Touch_Pos.x<=MAN_BACKWARD_X2))
										Touch_code=ADJUST_KEY_CODE;    //后退按键
									}
								else if((Touch_Pos.y>=MAN_FAST_BACK_Y1)&&(Touch_Pos.y<=MAN_FAST_BACK_Y2))
									{
									if((Touch_Pos.x>=MAN_FAST_BACK_X1)&&(Touch_Pos.x<=MAN_FAST_BACK_X2))
										Touch_code=FAST_BACK_TOUCH_CODE;	//快退-----------------------....
									else if((Touch_Pos.x>=MAN_FAST_FWD_X1)&&(Touch_Pos.x<=MAN_FAST_FWD_X2))
										Touch_code=FAST_FWD_TOUCH_CODE;	//快进---------------------------....
									}
								}
							else if((Touch_Pos.x>=F1_LABEL_X1)&&(Touch_Pos.x<=F1_LABEL_X2))  //F1~F4	
								{
								if((Touch_Pos.y>=F1_LABEL_Y1)&&(Touch_Pos.y<=F1_LABEL_Y2))
									Touch_code=AUTO_KEY_CODE;       // F1
								else if((Touch_Pos.y>=F2_DIVIDE_Y1)&&(Touch_Pos.y<=F2_DIVIDE_Y2))
									Touch_code=READ_KEY_CODE;       // F2
								else if((Touch_Pos.y>=F3_PROG_Y1)&&(Touch_Pos.y<=F3_PROG_Y2))
									Touch_code=RETURN_KEY_CODE;      //F3
								else if((Touch_Pos.y>=F4_PUSH_Y1)&&(Touch_Pos.y<=F4_PUSH_Y2))
									Touch_code=MANUAL_KEY_CODE;   // F4
								}
							}
								break;
						/*
						if((Touch_Pos.x>=F_KEY_X1)&&(Touch_Pos.x<=F_KEY_X2))
							{
							if((Touch_Pos.y>=F_KEY_Y1)&&(Touch_Pos.y<=F_KEY_Y2))
								Touch_code=F_TOUCH_CODE;    //F 键 触摸
							}
						if((Touch_Pos.x>=F1_LABEL_X1)&&(Touch_Pos.x<=F1_LABEL_X2))  //F1~F4
							{
							// // if((Touch_Pos.y>=F1_LABEL_Y1)&&(Touch_Pos.y<=F1_LABEL_Y2))
								// // Touch_code=AUTO_KEY_CODE;       // F1
							// // else if((Touch_Pos.y>=F2_DIVIDE_Y1)&&(Touch_Pos.y<=F2_DIVIDE_Y2))
								// // Touch_code=READ_KEY_CODE;       // F2
							// // else if((Touch_Pos.y>=F3_PROG_Y1)&&(Touch_Pos.y<=F3_PROG_Y2))
								// // Touch_code=RETURN_KEY_CODE;      //F3
							// // else if((Touch_Pos.y>=F4_PUSH_Y1)&&(Touch_Pos.y<=F4_PUSH_Y2))
								// // Touch_code=MANUAL_KEY_CODE;   // F4
							}
						if(MotorType==MOTOR_AC_SERVO)
							{
							// // if((Touch_Pos.x>=WHEEL_SWITCH_X1)&&(Touch_Pos.x<=WHEEL_SWITCH_X2))
								// // {
								// // if((Touch_Pos.y>=WHEEL_SWITCH_Y1)&&(Touch_Pos.y<=WHEEL_SWITCH_Y2))
									// // Touch_code=WHEEL_SWITCH_TOUCH_CODE;   //电子手轮 开关指示
								// // }
							}
							
						if((Touch_Pos.y>=FORWARD_Y1)&&(Touch_Pos.y<=FORWARD_Y2))
							{
							if((Touch_Pos.x>=FORWARD_X1)&&(Touch_Pos.x<=FORWARD_X2))
								Touch_code=NEXTKNIFE_KEY_CODE;  //前进按键
							else if((Touch_Pos.x>=BACKWARD_X1)&&(Touch_Pos.x<=BACKWARD_X2))
								Touch_code=ADJUST_KEY_CODE;    //后退按键
							}*/
							break;
					case PROG_LABEL_MODE: //标签
					case TEACH_LABEL_MODE://示教 标签
						if(Touch_Pos.y>=F_KEY_Y1)
							{
							// if((Touch_Pos.y>=WORK_MODE_Y1)&&(Touch_Pos.y<=WORK_MODE_Y2))
							if(Touch_Pos.y<=WORK_MODE_Y2)
								{
								if((Touch_Pos.x>=F_KEY_X1)&&(Touch_Pos.x<=F_KEY_X2))
									Touch_code=F_TOUCH_CODE;    //F 键 触摸
								else if((Touch_Pos.x>=WORK_MODE_X1)&&(Touch_Pos.x<=WORK_MODE_X2))
									Touch_code=MODE_TOUCH_CODE;        //模式 切换按钮
								// else if((Touch_Pos.x>=DELETE_X1)&&(Touch_Pos.x<=DELETE_X2))	
									// Touch_code=FIVE_KEY_CODE;		//删除按键
								// else if((Touch_Pos.x>=DELETE_ALL_X1)&&(Touch_Pos.x<=DELETE_ALL_X2))
									// Touch_code=DELETE_ALL_TOUCH_CODE;//全删 触摸键
								}
							}
						else
							{
							if((Touch_Pos.x>=F1_FINISH_X1)&&(Touch_Pos.x<=F1_FINISH_X2))  //
								{
								if((Touch_Pos.y>=F1_FINISH_Y1)&&(Touch_Pos.y<=F1_FINISH_Y2))
									Touch_code=AUTO_KEY_CODE;       // F1   完成
								else if((Touch_Pos.y>=F2_CANCEL_Y1)&&(Touch_Pos.y<=F2_CANCEL_Y2))
									Touch_code=READ_KEY_CODE;       // F2 退出
								else if((Touch_Pos.y>=F3_LABEL_TIME_Y1)&&(Touch_Pos.y<=F3_LABEL_TIME_Y2))	
									Touch_code=RETURN_KEY_CODE;      //F3 标签次数模式
								else if((Touch_Pos.y>=F4_LABEL_DESERT_Y1)&&(Touch_Pos.y<=F4_LABEL_DESERT_Y2))	
									Touch_code=MANUAL_KEY_CODE;   // F4标签废边模式
								}
							if((Touch_Pos.x>=SUB_UP_TO_X1)&&(Touch_Pos.x<=SUB_UP_TO_X2))  //	
								{
								if((Touch_Pos.y>=SUB_UP_TO_Y1)&&(Touch_Pos.y<=SUB_UP_TO_Y2))
									Touch_code=DENGJU_KEY_CODE;  //向上箭头
								else if((Touch_Pos.y>=SUB_DOWN_TO_Y1)&&(Touch_Pos.y<=SUB_DOWN_TO_Y2))	
									Touch_code=DENGFENG_KEY_CODE; //向下箭头
								}
							}
								break;
					case PROG_DIVIDE_MODE://等分
					case AUTO_RULER_MODE://自动 基准
					case AUTO_TOOLS_MODE://自动 参数
					case MANUAL_RULER_MODE://手动 基准
					case MANUAL_TOOLS_MODE://手动 参数
					case MANUAL_CLOCK_MODE://手动 时间
					case MANUAL_PULSE_MODE://手动 脉冲当量
					case MANUAL_PASS_MODE://手动 密码设定
					case MANUAL_SERVO_C_MODE:// 手动直流伺服 C 参数 
					// case TEACH_LABEL_MODE://示教 标签
					case TEACH_DIVIDE_MODE://示教 等分
					case SELF_RULER_MODE://自刀 基准
					case SELF_TOOLS_MODE://自刀 参数
						if(Touch_Pos.y>=F_KEY_Y1)
							{
							// if((Touch_Pos.y>=WORK_MODE_Y1)&&(Touch_Pos.y<=WORK_MODE_Y2))
							if(Touch_Pos.y<=WORK_MODE_Y2)
								{
								if((Touch_Pos.x>=F_KEY_X1)&&(Touch_Pos.x<=F_KEY_X2))
									Touch_code=F_TOUCH_CODE;    //F 键 触摸
								else if((Touch_Pos.x>=WORK_MODE_X1)&&(Touch_Pos.x<=WORK_MODE_X2))
									Touch_code=MODE_TOUCH_CODE;        //模式 切换按钮
								// else if((Touch_Pos.x>=DELETE_X1)&&(Touch_Pos.x<=DELETE_X2))	
									// Touch_code=FIVE_KEY_CODE;		//删除按键
								// else if((Touch_Pos.x>=DELETE_ALL_X1)&&(Touch_Pos.x<=DELETE_ALL_X2))
									// Touch_code=DELETE_ALL_TOUCH_CODE;//全删 触摸键
								}
							}
						else
							{
							if((Touch_Pos.x>=F1_FINISH_X1)&&(Touch_Pos.x<=F1_FINISH_X2))  //
								{
								if((Touch_Pos.y>=F1_FINISH_Y1)&&(Touch_Pos.y<=F1_FINISH_Y2))
									Touch_code=AUTO_KEY_CODE;       // F1   完成
								else if((Touch_Pos.y>=F2_CANCEL_Y1)&&(Touch_Pos.y<=F2_CANCEL_Y2))
									Touch_code=READ_KEY_CODE;       // F2 退出
								else if((Touch_Pos.y>=INSERT_Y1)&&(Touch_Pos.y<=INSERT_Y2))	
									Touch_code=ZERO_KEY_CODE;	//C插入
								}
							if((Touch_Pos.x>=SUB_UP_TO_X1)&&(Touch_Pos.x<=SUB_UP_TO_X2))  //	
								{
								if((Touch_Pos.y>=SUB_UP_TO_Y1)&&(Touch_Pos.y<=SUB_UP_TO_Y2))
									Touch_code=DENGJU_KEY_CODE;  //向上箭头
								else if((Touch_Pos.y>=SUB_DOWN_TO_Y1)&&(Touch_Pos.y<=SUB_DOWN_TO_Y2))	
									Touch_code=DENGFENG_KEY_CODE; //向下箭头
								}
							}
								break;
					case PROG_PRO_MODE://程序选择
					case TEACH_PRO_MODE://示教 程序
						if(Touch_Pos.y>=F_KEY_Y1)
							{
							if((Touch_Pos.x>=F5DELETE_BUTT_X1)&&(Touch_Pos.x<=F5DELETE_BUTT_X2))
								Touch_code=ONE_KEY_CODE+NO_KEY_CODE;		  //F 功能按键 + 5
							// else if((Touch_Pos.x>=F6EXIT_BUTT_X1)&&(Touch_Pos.x<=F6EXIT_BUTT_X2))
								// Touch_code=ONE_KEY_CODE+INSERT_KEY_CODE;  //        F功能按键+6
							else if((Touch_Pos.x>=ENTER_OK_BUTT_X1)&&(Touch_Pos.x<=ENTER_OK_BUTT_X2))	
								Touch_code=DOWN_KEY_CODE;  // 确定
							else if((Touch_Pos.x>=WORK_MODE_X1)&&(Touch_Pos.x<=WORK_MODE_X2))
								Touch_code=MODE_TOUCH_CODE;        //模式 切换按钮
							// else if((Touch_Pos.x>=UP_ARROW_PRO_X1)&&(Touch_Pos.x<=UP_ARROW_PRO_X2))
								// Touch_code=DENGJU_KEY_CODE;  //向上箭头
							// else if((Touch_Pos.x>=DOWN_ARROW_PRO_X1)&&(Touch_Pos.x<=DOWN_ARROW_PRO_X2))
								// Touch_code=DENGFENG_KEY_CODE;  //向下箭头
							}
						else 
							{
							if((Touch_Pos.x>=F1_LABEL_X1)&&(Touch_Pos.x<=F1_LABEL_X2))  //F1~F4	
								{
								if((Touch_Pos.y>=F1_LABEL_Y1)&&(Touch_Pos.y<=F1_LABEL_Y2))
									Touch_code=AUTO_KEY_CODE;       // F1
								else if((Touch_Pos.y>=F2_DIVIDE_Y1)&&(Touch_Pos.y<=F2_DIVIDE_Y2))
									Touch_code=READ_KEY_CODE;       // F2
								else if((Touch_Pos.y>=F3_PROG_Y1)&&(Touch_Pos.y<=F3_PROG_Y2))
									Touch_code=RETURN_KEY_CODE;      //F3
								else if((Touch_Pos.y>=F4_PUSH_Y1)&&(Touch_Pos.y<=F4_PUSH_Y2))
									Touch_code=MANUAL_KEY_CODE;   // F4
								}
							else if((Touch_Pos.x>=UP_TO_X1)&&(Touch_Pos.x<=UP_TO_X2))
								{
								if((Touch_Pos.y>=UP_TO_Y1)&&(Touch_Pos.y<=UP_TO_Y2))
									Touch_code=DENGJU_KEY_CODE;  //向上箭头按键
								else if((Touch_Pos.y>=DOWN_TO_Y1)&&(Touch_Pos.y<=DOWN_TO_Y2))
									Touch_code=DENGFENG_KEY_CODE;  //向下箭头
								}
							}
								break;
					case PROG_PRO_MESS_MODE:			 
					case TEACH_PRO_MESS_MODE:		//程序名  模式
						if(Touch_Pos.y>=F_KEY_Y1)
							{
							if((Touch_Pos.x>=WORK_MODE_X1)&&(Touch_Pos.x<=WORK_MODE_X2))
								Touch_code=MODE_TOUCH_CODE;        //模式 切换按钮
							}
						else 
							{
							if((Touch_Pos.x>=F1_LABEL_X1)&&(Touch_Pos.x<=F1_LABEL_X2))  //F1~F4	
								{
								if((Touch_Pos.y>=F1_LABEL_Y1)&&(Touch_Pos.y<=F1_LABEL_Y2))
									Touch_code=AUTO_KEY_CODE;       // F1
								else if((Touch_Pos.y>=F2_DIVIDE_Y1)&&(Touch_Pos.y<=F2_DIVIDE_Y2))
									Touch_code=READ_KEY_CODE;       // F2
								else if((Touch_Pos.y>=F3_PROG_Y1)&&(Touch_Pos.y<=F3_PROG_Y2))
									Touch_code=RETURN_KEY_CODE;      //F3
								else if((Touch_Pos.y>=F4_PUSH_Y1)&&(Touch_Pos.y<=F4_PUSH_Y2))
									Touch_code=MANUAL_KEY_CODE;   // F4
								}
								//keyboard button------------
							else if((Touch_Pos.x>=TOU_BUTT_ONE_X1)&&(Touch_Pos.x<=TOU_BUTT_ONE_X2))
								{
								if((Touch_Pos.y>=TOU_BUTT_ONE_Y1)&&(Touch_Pos.y<=TOU_BUTT_ONE_Y2))
									Touch_code=NINE_KEY_CODE;		// 1
								else if((Touch_Pos.y>=TOU_BUTT_FOUR_Y1)&&(Touch_Pos.y<=TOU_BUTT_FOUR_Y2))
									Touch_code=EIGHT_KEY_CODE;		//4
								else if((Touch_Pos.y>=TOU_BUTT_SEVEN_Y1)&&(Touch_Pos.y<=TOU_BUTT_SEVEN_Y2))
									Touch_code=SEVEN_KEY_CODE;	//7
								else if((Touch_Pos.y>=TOU_BUTT_CLR_Y1)&&(Touch_Pos.y<=TOU_BUTT_CLR_Y2))
									Touch_code=SIX_KEY_CODE;		// clear
								}
							else if((Touch_Pos.x>=TOU_BUTT_TWO_X1)&&(Touch_Pos.x<=TOU_BUTT_TWO_X2))
								{
								if((Touch_Pos.y>=TOU_BUTT_TWO_Y1)&&(Touch_Pos.y<=TOU_BUTT_TWO_Y2))
									Touch_code=MOVE_KEY_CODE;     // 2
								else if((Touch_Pos.y>=TOU_BUTT_FIVE_Y1)&&(Touch_Pos.y<=TOU_BUTT_FIVE_Y2))
									Touch_code=NO_KEY_CODE;     // 5
								else if((Touch_Pos.y>=TOU_BUTT_EIGHT_Y1)&&(Touch_Pos.y<=TOU_BUTT_EIGHT_Y2))
									Touch_code=YES_KEY_CODE;    // 8
								else if((Touch_Pos.y>=TOU_BUTT_ZERO_Y1)&&(Touch_Pos.y<=TOU_BUTT_ZERO_Y2))
									Touch_code=PROG_KEY_CODE;    // 0
								}
							else if((Touch_Pos.x>=TOU_BUTT_THREE_X1)&&(Touch_Pos.x<=TOU_BUTT_THREE_X2))
								{
								if((Touch_Pos.y>=TOU_BUTT_THREE_Y1)&&(Touch_Pos.y<=TOU_BUTT_THREE_Y2))
									Touch_code=DELETE_KEY_CODE;      //3
								else if((Touch_Pos.y>=TOU_BUTT_SIX_Y1)&&(Touch_Pos.y<=TOU_BUTT_SIX_Y2))
									Touch_code=INSERT_KEY_CODE;      //6
								else if((Touch_Pos.y>=TOU_BUTT_NINE_Y1)&&(Touch_Pos.y<=TOU_BUTT_NINE_Y2))
									Touch_code=SUB_KEY_CODE;  // 9
								else if((Touch_Pos.y>=TOU_BUTT_OK_Y1)&&(Touch_Pos.y<=TOU_BUTT_OK_Y2))
									Touch_code=DOWN_KEY_CODE;  // 确定
								}
							else if((Touch_Pos.x>=TOU_BUTT_UP_X1)&&(Touch_Pos.x<=TOU_BUTT_UP_X2))
								{
								if((Touch_Pos.y>=TOU_BUTT_UP_Y1)&&(Touch_Pos.y<=TOU_BUTT_UP_Y2))
									Touch_code=DENGJU_KEY_CODE;  //向上箭头
								else if((Touch_Pos.y>=TOU_BUTT_DOWN_Y1)&&(Touch_Pos.y<=TOU_BUTT_DOWN_Y2))
									Touch_code=DENGFENG_KEY_CODE;  //向下箭头
								else if((Touch_Pos.y>=TOU_BUTT_LEFT_Y1)&&(Touch_Pos.y<=TOU_BUTT_LEFT_Y2))
									Touch_code=LEFT_KEY_CODE;      //左---------------------------------
								else if((Touch_Pos.y>=TOU_BUTT_RIGHT_Y1)&&(Touch_Pos.y<=TOU_BUTT_RIGHT_Y2))
									Touch_code=RIGHT_KEY_CODE;      //右-------------------------------
								}
							}
								break;
					case PROG_DEL_ALL_PRO_MODE://删除所有pro  模式
					case TEACH_DEL_ALL_PRO_MODE://删除所有pro
						if((Touch_Pos.y>=DEL_ALL_OK_Y1)&&(Touch_Pos.y<=DEL_ALL_OK_Y2))
							{
							if((Touch_Pos.x>=DEL_ALL_OK_X1)&&(Touch_Pos.x<=DEL_ALL_OK_X2)) 
								Touch_code=DOWN_KEY_CODE;   // 确定
							else if((Touch_Pos.x>=DEL_ALL_CANCEL_X1)&&(Touch_Pos.x<=DEL_ALL_CANCEL_X2))
								Touch_code=SIX_KEY_CODE;		// clear
							}		
							break;
					}
				}
			}
		else   //计数器弹出框 
			{
			if((Touch_Pos.y>=CALC_ONE_Y1)&&(Touch_Pos.y<=CALC_ONE_Y2)) //row1
				{
				if((Touch_Pos.x>=CALC_ONE_X1)&&(Touch_Pos.x<=CALC_ONE_X2))
					{
					Touch_code=NINE_KEY_CODE;		// 1
					}
				else if((Touch_Pos.x>=CALC_TWO_X1)&&(Touch_Pos.x<=CALC_TWO_X2))
					{
					Touch_code=MOVE_KEY_CODE;		// 2
					}
				else if((Touch_Pos.x>=CALC_THREE_X1)&&(Touch_Pos.x<=CALC_THREE_X2))
					{
					Touch_code=DELETE_KEY_CODE;      //3
					}
				else if((Touch_Pos.x>=CALC_PLUS_X1)&&(Touch_Pos.x<=CALC_PLUS_X2))
					{
					Touch_code=REV_KEY_CODE;   //  +
					}	
				else if((Touch_Pos.x>=CALC_INS_X1)&&(Touch_Pos.x<=CALC_INS_X2))
					{
					Touch_code=ZERO_KEY_CODE;	//C插入
					}
				}
			else if((Touch_Pos.y>=CALC_FOUR_Y1)&&(Touch_Pos.y<=CALC_FOUR_Y2))  //row2
				{
				if((Touch_Pos.x>=CALC_FOUR_X1)&&(Touch_Pos.x<=CALC_FOUR_X2))
					{
					Touch_code=EIGHT_KEY_CODE;		//4
					}
				else if((Touch_Pos.x>=CALC_FIVE_X1)&&(Touch_Pos.x<=CALC_FIVE_X2))	
					{
					Touch_code=NO_KEY_CODE;      // 5
					}
				else if((Touch_Pos.x>=CALC_SIX_X1)&&(Touch_Pos.x<=CALC_SIX_X2))	
					{
					Touch_code=INSERT_KEY_CODE;      //6
					}
				else if((Touch_Pos.x>=CALC_SUB_X1)&&(Touch_Pos.x<=CALC_SUB_X2))	
					{
					Touch_code=OPTION_KEY_CODE;    //减号  -
					}
				else if((Touch_Pos.x>=CALC_EXIT_X1)&&(Touch_Pos.x<=CALC_EXIT_X2))	
					{
					Touch_code=READ_KEY_CODE;       // F2*******************退出
					}
				}
			else if((Touch_Pos.y>=CALC_SEVEN_Y1)&&(Touch_Pos.y<=CALC_SEVEN_Y2))  //row3
				{
				if((Touch_Pos.x>=CALC_SEVEN_X1)&&(Touch_Pos.x<=CALC_SEVEN_X2))
					{
					Touch_code=SEVEN_KEY_CODE;	//7
					}
				else if((Touch_Pos.x>=CALC_EIGHT_X1)&&(Touch_Pos.x<=CALC_EIGHT_X2))	
					{
					Touch_code=YES_KEY_CODE;    // 8
					}
				else if((Touch_Pos.x>=CALC_NINE_X1)&&(Touch_Pos.x<=CALC_NINE_X2))	
					{
					Touch_code=SUB_KEY_CODE;   // 9
					}
				else if((Touch_Pos.x>=CALC_MUL_X1)&&(Touch_Pos.x<=CALC_MUL_X2))	
					{
					Touch_code=MUL_TOUCH_CODE;  // *
					}
				else if((Touch_Pos.x>=CALC_EQU_X1)&&(Touch_Pos.x<=CALC_EQU_X2))	
					{
					Touch_code=EQU_TOUCH_CODE;  //==
					}
				}	
			else if((Touch_Pos.y>=CALC_C_Y1)&&(Touch_Pos.y<=CALC_C_Y2))  //row4
				{
				if((Touch_Pos.x>=CALC_C_X1)&&(Touch_Pos.x<=CALC_C_X2))
					{
					Touch_code=SIX_KEY_CODE;		// clear 功能C
					}
				else if((Touch_Pos.x>=CALC_ZERO_X1)&&(Touch_Pos.x<=CALC_ZERO_X2))	
					{
					Touch_code=PROG_KEY_CODE;     // 0 
					}
				else if((Touch_Pos.x>=CALC_DOT_X1)&&(Touch_Pos.x<=CALC_DOT_X2))	
					{
					Touch_code=ADD_KEY_CODE;   //  点“.”
					}
				else if((Touch_Pos.x>=CALC_DIV_X1)&&(Touch_Pos.x<=CALC_DIV_X2))	
					{
					Touch_code=DIV_TOUCH_CODE;  // 除 /
					}
				else if((Touch_Pos.x>=CALC_ENTER_X1)&&(Touch_Pos.x<=CALC_ENTER_X2))	
					{
					Touch_code=DOWN_KEY_CODE;   // 确定	
					if(WorkMode==MANUAL_MODE)// 手动 模式
						Touch_code=UP_KEY_CODE;   ///////////运行
					}
				}
			//else if((Touch_Pos.x>=F_KEY_X1)&&(Touch_Pos.x<=F_KEY_X2))
			//	{
			//	if((Touch_Pos.y>=F_KEY_Y1)&&(Touch_Pos.y<=F_KEY_Y2))
			//		Touch_code=F_TOUCH_CODE;    //F 键 触摸
			//	}
			if((Touch_Pos.x>=CALC_UP_X1)&&(Touch_Pos.x<=CALC_UP_X2))  //最后一列
				{
				if((Touch_Pos.y>=CALC_UP_Y1)&&(Touch_Pos.y<=CALC_UP_Y2))
					Touch_code=DENGJU_KEY_CODE;  //向上箭头按键
				else if((Touch_Pos.y>=CALC_DOWN_Y1)&&(Touch_Pos.y<=CALC_DOWN_Y2))
					Touch_code=DENGFENG_KEY_CODE; //向下箭头	
				}
				//------
			if((Touch_Pos.x>=F_KEY_X1)&&(Touch_Pos.x<=F_KEY_X2))
				{	
				if((Touch_Pos.y>=F_KEY_Y1)&&(Touch_Pos.y<=F_KEY_Y2))
					Touch_code=F_TOUCH_CODE;    //F 键 触摸
				}
				/***
			if((Touch_Pos.y>=RUN_Y1)&&(Touch_Pos.y<=RUN_Y2))
				{
				if((Touch_Pos.x>=RUN_X1)&&(Touch_Pos.x<=RUN_X2))	
					Touch_code=UP_KEY_CODE;   ///////////运行
				else if((Touch_Pos.x>=STOP_X1)&&(Touch_Pos.x<=STOP_X2))	
					Touch_code=STOP_TOUCH_CODE; //停止 触摸键
				}
				***/
			if(WorkMode==MANUAL_MODE)// 手动 模式
				{
				if((Touch_Pos.y>=MAN_FORWARD_Y1)&&(Touch_Pos.y<=MAN_FORWARD_Y2))
					{
					if((Touch_Pos.x>=MAN_FORWARD_X1)&&(Touch_Pos.x<=MAN_FORWARD_X2))
						Touch_code=NEXTKNIFE_KEY_CODE;  //前进按键
					else if((Touch_Pos.x>=MAN_BACKWARD_X1)&&(Touch_Pos.x<=MAN_BACKWARD_X2))
						Touch_code=ADJUST_KEY_CODE;    //后退按键
					}
				else if((Touch_Pos.y>=MAN_FAST_BACK_Y1)&&(Touch_Pos.y<=MAN_FAST_BACK_Y2))
					{
					if((Touch_Pos.x>=MAN_FAST_BACK_X1)&&(Touch_Pos.x<=MAN_FAST_BACK_X2))
						Touch_code=FAST_BACK_TOUCH_CODE;	//快退-----------------------....
					else if((Touch_Pos.x>=MAN_FAST_FWD_X1)&&(Touch_Pos.x<=MAN_FAST_FWD_X2))
						Touch_code=FAST_FWD_TOUCH_CODE;	//快进---------------------------....
					}
				}
			}
		}
	}
//*************************************************	特殊 键值转换
if(Touch_code!=0)
	{
	if((Touch_code&0xffff0000)==0xffff0000)  //纯 触摸键(特殊)-----------------------------则转为键盘对应码
		{
		switch(Touch_code)
			{
			case PUSH_OK_TOUCH_CODE:	//推纸器 复位 OK
				Touch_code=DOWN_KEY_CODE;  // 确定
					break;
			case PUSH_CANCEL_TOUCH_CODE:	//推纸器 复位 CANCEL
				Touch_code=SIX_KEY_CODE;		// clear 功能C
					break;	
			case START_TOUCH_CODE:  //开机 运行
				Touch_code=UP_KEY_CODE;   ///////////运行
					break;
			case MODE_TOUCH_CODE:  //  -----------------模式切换
				switch(WorkMode)
					{
					case PROG_MODE://编程画面下
							Touch_code=THREE_KEY_CODE;		//自动按键
							break;
					case PROG_LABEL_MODE: //标签
					case PROG_DIVIDE_MODE://等分
					case PROG_PRO_MODE://程序选择
							Touch_code=FOUR_KEY_CODE;	//编程按键
							break;
					case AUTO_MODE://自动主画面下	
							Touch_code=TWO_KEY_CODE;		//手动按键
							break;
					case AUTO_RULER_MODE://自动 基准
					case AUTO_TOOLS_MODE://自动 参数	
					case AUTO_PLUS_MODE://自动F3++
					case AUTO_MINUS_MODE://自动F4--
							Touch_code=THREE_KEY_CODE;		//自动按键
							break;
					case MANUAL_MODE:// 手动 模式		
							Touch_code=FOUR_KEY_CODE;	//编程按键
							break;
					case MANUAL_RULER_MODE://手动 基准
					case MANUAL_TOOLS_MODE://手动 参数
					case MANUAL_CLOCK_MODE://手动 时间
					case MANUAL_PULSE_MODE://手动 脉冲当量
					case MANUAL_PASS_MODE://手动 密码设定	
					case MANUAL_SERVO_C_MODE:// 手动直流伺服 C 参数 
							Touch_code=TWO_KEY_CODE;		//手动按键
							break;
					case TEACH_LABEL_MODE://示教 标签
					case TEACH_DIVIDE_MODE://示教 等分
					case TEACH_PRO_MODE://示教 程序
							Touch_code=ONE_KEY_CODE+INSERT_KEY_CODE;  //        F功能按键+6 ----------示教
							break;
					case SELF_RULER_MODE://自刀 基准
					case SELF_TOOLS_MODE://自刀 参数
					case SELF_PLUS_MODE: //自刀 F3++
					case SELF_MINUS_MODE://自刀 F4--
					case SELF_CUT_MODE: //自刀 模式
							TouchLong_code=ONE_KEY_CODE;	// F 功能按键
							break;
					case PROG_PRO_MESS_MODE:	//程序名 输入
					case TEACH_PRO_MESS_MODE:
							Touch_code=MANUAL_KEY_CODE;   // F4    退出
							break;
					}
					break;
			case DELETE_ALL_TOUCH_CODE://全删 按钮
				TouchLong_code=FIVE_KEY_CODE;		//删除按键
					break;
			case STOP_TOUCH_CODE://停止	 按钮	
				Touch_code=STOP_KEY_CODE; //停止
					break;
			case F_TOUCH_CODE:    //F 键
				if(Run_flag==0)
					{
					switch(WorkMode)
						{
						case PROG_MODE://编程画面下
							Touch_code=ONE_KEY_CODE+INSERT_KEY_CODE;  //        F功能按键+6 ----------示教模式
								break;
						case AUTO_MODE://自动主画面下 
							TouchLong_code=ONE_KEY_CODE;	// F 功能按键   进入自刀
								break;
						case TEACH_MODE:  //示教模式		
							Touch_code=FOUR_KEY_CODE;	//编程按键
								break;
						case SELF_CUT_MODE: //自刀 模式
							Touch_code=THREE_KEY_CODE;		//自动
								break;
						}
					}
				else
					{
					Touch_code=ONE_KEY_CODE;	// F 功能按键 
					}
					break;
			case F0CUT_TOUCH_CODE:  //F0 刀标志 按钮
					switch(WorkMode)
						{
						case PROG_MODE://编程画面下
						case TEACH_MODE:  //示教模式	
							Touch_code=ONE_KEY_CODE+ PROG_KEY_CODE;//F 功能按键 +  数字0************ 批量 刀标志
								break;
						}
					break;
			case F5CUT_TOUCH_CODE:  //F5 1个刀标志 按钮
					switch(WorkMode)
						{
						case PROG_MODE://编程画面下
						case TEACH_MODE:  //示教模式	
						case AUTO_MODE://自动主画面下=========	
							Touch_code=ONE_KEY_CODE+NO_KEY_CODE;		  //F 功能按键 + 5 ***********刀标志
								break;
						}
					break;
			}
		}
	}
}

void TouchButton_dis(Int32U code,Int8U down_flag)  //触摸  按钮显示
{
Int8U key_num=0xff;
Int8U t_butt_flag=0;
if(code!=0)
	{
	if(InputTouch_flag==1)	//计算器  下
		t_butt_flag=1;
	else	//非计算器  
		{
		if((WorkMode==PROG_PRO_MESS_MODE)||(WorkMode==TEACH_PRO_MESS_MODE))
			t_butt_flag=1;
		}
	if(t_butt_flag==1)		//触摸 小键盘 模式
		{
		switch(code)
			{
			case NINE_KEY_CODE:		// 1
					key_num=BUTT_1;
					break;
			case MOVE_KEY_CODE:		// 2
					key_num=BUTT_2;
					break;
			case DELETE_KEY_CODE:      //3		
					key_num=BUTT_3;
					break;
			case EIGHT_KEY_CODE:		//4	
					key_num=BUTT_4;
					break;
			case NO_KEY_CODE:		//5	
					key_num=BUTT_5;
					break;	
			case INSERT_KEY_CODE:      //6
					key_num=BUTT_6;
					break;	
			case SEVEN_KEY_CODE:	//7
					key_num=BUTT_7;
					break;
			case YES_KEY_CODE:    // 8	
					key_num=BUTT_8;
					break;	
			case SUB_KEY_CODE:   // 9
					key_num=BUTT_9;
					break;	
			case PROG_KEY_CODE:     // 0 
					key_num=BUTT_0;
					break;
			case ADD_KEY_CODE:   //  点“.”
					key_num=BUTT_DOT;
					break;
			case SIX_KEY_CODE:		// clear 功能C
					key_num=BUTT_CLEAR;
					break;
			case REV_KEY_CODE:   //  +		
					key_num=BUTT_PLUS;
					break;
			case OPTION_KEY_CODE:    //减号  -
					key_num=BUTT_SUB;
					break;
			case MUL_TOUCH_CODE:  // *
					key_num=BUTT_MUL;
					break;	
			case DIV_TOUCH_CODE:  // 除 /
					key_num=BUTT_DIV;
					break;	
			case ZERO_KEY_CODE:	//C插入
					key_num=BUTT_INSERT;
					break;
			case READ_KEY_CODE:       // F2*******************退出	
					if(down_flag==1)
						key_num=BUTT_EXIT;
					break;	
			case EQU_TOUCH_CODE:  //=
					key_num=BUTT_EQU;
					break;	
			case DOWN_KEY_CODE:   // 确定
						key_num=BUTT_ENTER;
					break;
			case UP_KEY_CODE:    ///////////运行		
					//if(down_flag==1)
					if(WorkMode==MANUAL_MODE)// 手动 模式
						key_num=BUTT_RUN;
					break;
			case DENGJU_KEY_CODE:  //向上箭头按键
					key_num=BUTT_UP;
					break;
			case DENGFENG_KEY_CODE: //向下箭头		
					key_num=BUTT_DOWN;
					break;
			case LEFT_KEY_CODE:	// 左	
					key_num=BUTT_LEFT;
					break;
			case RIGHT_KEY_CODE:	// 右
					key_num=BUTT_RIGHT;
					break;
			}
		if(key_num!=0xff)
			{
			if(InputTouch_flag==1)	//计算器  下
				Button_dis(key_num, down_flag); //触摸 按钮 显示
			else	//非计算器  
				InputKEY_BUTT_dis(key_num, down_flag); //触摸 key 显示--------输入法
			}
		}
	
	}
}


