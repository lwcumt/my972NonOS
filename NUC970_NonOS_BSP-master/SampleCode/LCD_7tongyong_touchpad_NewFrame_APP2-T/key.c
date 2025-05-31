/*

键扫描   1MS进入一次


*/

#include"key.h"

#include"m25pe16.h"
#include"chndot.h"

#include"io.h"
#include "timer.h"

#include "pic_exec.h"

#include  "test_io.h"

#include "port.h"
#include "servo.h"
#include "name_input.h"
#include "file.h"

//#define WHITE_COLOR 0xffff



#define BLACK_COLOR 0
#define WHITE_COLOR 0xffff
#define RED_COLOR 0xf800
#define BLUE_COLOR 0x001f
#define GREEN_COLOR 0x7e0
#define VIOLET_COLOR 0xf81f
#define YELLOW_COLOR 0xffe0
#define QINGSE_COLOR 0x07ff


#define DOT32  32  //汉字32*32点阵  
#define DOT32MODE 128+2


Int8U SetTime_flag;//时间设定使能
Int8U LongExec_flag;//长按标志

Int16U Year_temp;//时间
Int8U  Month_temp;
Int8U  Date_temp;
Int8U  Hour_temp;
Int8U  Min_temp;

Int8U TimeBit[10];
Int8U TimeBit_Sel;
Int8U TimeBit_Last;

const Int16U DisPosX[10]={Year1_X,Year0_X,Month1_X,Month0_X,Date1_X,Date0_X,Hour1_X,Hour0_X,Min1_X,Min0_X};
const Int16U DisPosY[10]={Year1_Y,Year0_Y,Month1_Y,Month0_Y,Date1_Y,Date0_Y,Hour1_Y,Hour0_Y,Min1_Y,Min0_Y};


//unsigned  long int  yuandiancn ;
int nian;
unsigned char yue,ri,shi,feng;
 int KeyCode;  //键代码
int KeyCode_Temp;
 int KeyDownTime;  //键扫下计时
 int KeyLongDownTime;  //键长时间按下计时
 char KeyDown_Flag;   //键按下标志位
 char KeyExec_Flag;   //键处理标志位
 char KeyLongDown_Flag;
 unsigned char InputBuf[30];
 unsigned char InputCou,flagdaobiaoji,flaghsd,flagqsd;
unsigned long int lcdchicun[6],lcdchengxuhaoma[2],ymuqiancn;
 unsigned char flagdot,program4,daohao,flagyici;
  unsigned long int weizhicn[200];
  unsigned long int   yvbcd4,yhoujixian,chengxuweizhi[100];
 unsigned long int I,lcdnumber,zongchang,biaoqian,dengfeng,feibian,dzongchang,fengshu,dfshu;
  unsigned long int Rswanwei,Rwanwei,Rqianwei,Rbaiwei,Rshiwei,Rgewei,sw,qb,sg,mubiao;
   unsigned char bcd[3],qbcd[3],hbcd[5];
  unsigned long int swanwei1,wanwei1,qianwei1,baiwei1,shiwei1,gewei1,sw2,qb2,sg2;
   unsigned  char flagyd,flagqyx, poweon_flag,flagshanchu;
  unsigned char flagchengxu;
	Int16U n;
 unsigned  char   chengxuhaoma, huamian,zhishi,flagrun,flagkeysong,flagdanwei;
 unsigned  char flagjia,flagjian,flagcheng,flagchu;
  unsigned long int qianjixian,zhongjixian,houjixian,jizhun,vbcd4,zongshu,dfchangdu,mada;
   unsigned  char flagbz[200],flagzhiyou;
unsigned long int vbcd;
   unsigned  char flaggong,qianjinflag,houtuiflag;
//**************脉冲发送变量**********************//
unsigned char status,flagyunxing8;         //
unsigned char step_ground;   //
unsigned char step_add;      //
unsigned char qianjin,houtui;
unsigned char   flagqyx,  t0zhongduan;



unsigned long int yushu;
unsigned long int speedup_steps;
unsigned long int speedup_steps_B;
unsigned long int rollsteps;     
unsigned char flagtingji7,flagtingji8;

unsigned long int qianjincn,houtuicn;
unsigned long int  tempqianjin1, temphoutui1; 


 
 void lcdweizhicn( unsigned long int x0, unsigned long int y0,unsigned long int chicun);
 void lcdweizhicnH( unsigned long int x0, unsigned long int y0,unsigned long int chicun);
void lcdNUMBER( unsigned long int x0, unsigned long int y0,unsigned char chicun);
void lcdNUMBERH( unsigned long int x0, unsigned long int y0,unsigned char chicun);
void lcdhaoma( unsigned long int x0, unsigned long int y0,unsigned char chicun);
void chengxudu();
 void lcdzhishi();
void lcdnian( unsigned long int x0, unsigned long int y0,unsigned int  chicun); 
 void lcdpage1();
 
 
Int8U CalcNoNumInput_flag; 
 
unsigned char num_cou=0;
unsigned char Size_temp[8];
unsigned char CalcInput_Text[24];
unsigned char CalcResult_Text[24];
unsigned char CalcInput_cou;

unsigned char CalcSign_order;
unsigned char CalcTemp_cou;
Int32U CalcData_temp;
unsigned long int InputSize=0;

Int8U Dot_flag;

unsigned char WorkStart_flag;
unsigned char Comment_flag;
unsigned char flagyunxing;


pInt8U  pKnife_data;

KNIFE_DATA OneKnife_data;
START_DAY Start_days;

unsigned int Total_size=0;//总长
unsigned int Label_size=0;//标签长
unsigned int Waste_size=0;//废边
unsigned int Divide_num=0;//等分数
 

unsigned char cursor_temp;
unsigned long int maichongdangliang,xxmuqiancn;

Int16U Pro_num;



Int8U PromptDis_flag;
Int8U StartPassInput_flag=0;

Int32U PassCode;
Int32U PassCheck;

Int8U PassCheckDis_flag;

Int8U Year_before,Month_before,Day_before;
Int8U TimeAhead_flag; //时间提前 标志

Int8U PaperCutEnb_signal;
Int16U Past_days;

Int8U Sign_flag;
Int8U Minus_flag;
Int8U Arithmetic_mode; //运算模式
Int8U StartCheck_mode;
Int8U OutSensorOK_flag;
//Int8U RunToCusor_flag;
Int32U Zpulse_cou;
Int32U Z_Pulse;

Int8U Board_TestMod;
Int8U TouchCalcu_mode;


Int8U CalcResultDis_flag;
Int8U AutoRoute_flag;
Int8U Manual_page;

Int8U CheckModeOK_flag;


Int8U ManualMoveMode;


Int8U Stop_F_Remind_flag;

Int8U BellStart_flag;
Int8U TargetBell_flag;
Int16U TargetBell_time;
Int8U TargetBell_mode;

Int8U AllKnifeSet_flag;

unsigned  char flagyd;
unsigned char flagchengxu,flagkey,flagtime1;

Int8U AC_MotorSPD; //AC  motor  speed
Int8U PressCircle_mode=0;


void BellOn_Enb(void)
{
labatime=0;
BellOUT_ON;flaglaba=1;
}


void KeyScan(void)  //键扫描   1MS进入一次
{
unsigned long int j;  

Key_Enable(ENABLE);
if(KeyDown_Flag==0)
	{
//	KeyCode=KEYIO;   //读入键码  不同的端口状态修改此行
	if(KeyCheck()!=0)   //判断是否有键按下
		{
		KeyDown_Flag=1;    //置键按下标志位
		KeyDownTime=0;
		}
	}
else
	{
	if(KeyExec_Flag==0)
		{
	//	KeyCode=KEYIO;   //读入键码  不同的端口状态修改此行
		if(KeyCheck()!=0)   //判断是否有键按下
			{
			KeyDownTime++;
			if(KeyDownTime>=50)  //按下键 去抖动10MS
				{
				KeyDownTime=0;
				KeyReadCode();//读取键值 
				KeyCode_Temp=KeyCode;

				////////////////////////////
                                  flagkeysong=0;
				//  以下为键按下处理
				////////////////////////////
				switch(Board_TestMod)
					{
					case 0:
					case TEST_TOUCH:
					case TEST_HELP:
						KeyExec(KeyCode); //调键处理
							break;
					case TEST_BOARD://测试 模式  3
						BellOn_Enb();
						KeyDis_sel(KeyCode_Temp,1);  //***************按键显示 
							break;
					case TEST_MOTOR_TYPE://设定  档位4
						BellOn_Enb();
						ShiftSpeed_SetExec(KeyCode); 
							break;
					}
				KeyExec_Flag=1; //置键处理标志位
				}
			}
		else
			{  //抖动引起。退出
			KeyDown_Flag=0;
			}
		}
	else
		{
//		KeyCode=KEYIO;   //读入键码  不同的端口状态修改此行
		if(KeyCheck()==0)   //判断是否有键按下		if(KeyCode==0)
			{
			KeyDownTime++;
			if(KeyDownTime>=50)  //------------释放键 去抖动10MS
				{
				KeyDown_Flag=0;   //清按下标志位
				KeyExec_Flag=0;   //清键处理标志位
				KeyLongDownTime=0;  //清键长按计时
				KeyCode=0;
				//KeyLongDown_Flag=0;
                 LongExec_flag=0;  
				////////////////////////////
				GoFrontEn_flag=0;
				GoBackEn_flag=0;
				GoFast_flag=0;
				if(Board_TestMod==TEST_BOARD)
					{
					KeyDis_sel(KeyCode_Temp,0); //***************按键显示
					MoveStop();
					RLOUT1_OFF; RLOUT1_1_OFF;   // 允许裁切
					}
					
				//----------------------------------------
				
				
				 ACMotor_ReleaseStop();  //-------
				 	
				}
			}
		else
			{
			KeyDownTime=0;
			
			if(LongExec_flag==0)
			    {
				  KeyReadCode();//读取键值
				  MultiKey_exec(KeyCode);  //组合键处理
				  //if(KeyCode!=KeyCode_Temp)
				   //  {
					 
					// }
				}
			
			if(KeyLongDownTime<KEYLONGDOWNTIMEDATA)
				{
				KeyLongDownTime++;
                }             
			else//----------长按处理------------
			   {
			   if(LongExec_flag==0)
			      {
				  LongExec_flag=1;
				  //KeyReadCode();//读取键值
				  LongKey_exec(KeyCode , KeyCode_Temp);  //长按键处理
				  }
			   }
								
			}
		}
	}
Key_Enable(DISABLE);
}


void NumKey_exec(Int8U num)
{
if(WorkStart_flag==1)
	{
	if(Run_flag==0)
		{
		if(CalcResultDis_flag==1)
			{
			ClrCalcNums_text(CalcInput_Text,CAL_INPUT); //清计算器 输入框
			CalcInput_cou=0;
			num_cou=0;
			CalcResultDis_flag=0;  //结果显示 标志
			CalcSign_order=0;//首个运算符 位置
			}
		if(num_cou>7)num_cou=0;
		if(num_cou<7)
			{
			if(num_cou==0)
				GLCD_SetWindow_Fill( SIZE_WINDOW_X+24, SIZE_WINDOW_Y, SIZE_WINDOW_X+120, SIZE_WINDOW_Y+30, 0xfffff, 0xffff);//尺寸输入框
			//if(CalcNoNumInput_flag==1)
				CalcNoNumInput_flag=0;	
			if(num!='.')
				{
				Size_temp[num_cou++]=num;
				if(InputTouch_flag==0)
					{
					InputNum_dis(Size_temp,num_cou);
					}
				else//--------------------计算器
					{
					CalcInput_Text[CalcInput_cou++]=num;
					CalcInputNums_dis(CalcInput_Text);	
					}
				}
			else
				{
				if(Dot_flag==0)	
					{
					Dot_flag=1;
					Size_temp[num_cou++]=num;
					if(InputTouch_flag==0)
						{
						InputNum_dis(Size_temp,num_cou);
						}
					else//--------------------计算器
						{
						CalcInput_Text[CalcInput_cou++]=num;
						CalcInputNums_dis(CalcInput_Text);	
						}
					}
				}
			}
		
		}
	else
		{
						
		}
	}
else
	{
	if(PassCheckDis_flag==1) 
		{
		if(num_cou<6)
			{
			Size_temp[num_cou++]=num;
			PassWord_dis(Size_temp,num_cou);//密码
			}	
		}
	}		
}

void ClearCalculatorInput(void) //清零计算器 输入
{
CalcNoNumInput_flag=1;
//num_cou=0;
Dot_flag=0;
CalcSign_order=0;//首个运算符 位置
CalcData_temp=0;
CalcResultDis_flag=0;
ClrCalcNums_text(CalcInput_Text,CAL_INPUT); //清计算器 输入框
ClrCalcNums_text(CalcResult_Text,CAL_RESULT); //清计算器 结果框
CalcInputNums_dis(CalcInput_Text);  //输入框 显示
CalcInput_cou=0;
CalcResultNums_dis(CalcResult_Text);//结果框 显示
}
void CalcuInClear_exec(void)     //清除 计算器
{
CurrentArea_recover3(CALCUL_WIN_X,CALCUL_WIN_Y,CALCUL_WIDE,CALCUL_HIGH);
InputTouch_flag=0;
Dot_flag=0;
num_cou=0;
//CalcSign_order=0;//首个运算符 位置
//CalcData_temp=0;
CalcResultDis_flag=0;
}

void CurrentToCalc_input(void)  //当前尺寸  转换为 计算器显示数据
{
volatile Int32U valu_temp;
Int8U current_flag;//dot;
KNIFE_DATA Knife_datas;
if((WorkMode==MANUAL_MODE)||(WorkMode==TEACH_MODE))  // 手动|示教 模式	默认当前尺寸
	{
	current_flag =1;
	}
else		//列表框 尺寸
	{
	if(Knife_order>1)
		{
		GetOneKnife_datas(Pro_data.pro_num, Knife_order-1, (pInt8U)&Knife_datas);//取出一刀 数据
		if((Knife_datas.size>=Size_MIN_num)&&(Knife_datas.size<=Size_MAX_num))  //当前尺寸  有效
			{
			current_flag =0;	
			if(Unit==UNIT_MM)//mm
				{
				valu_temp=Knife_datas.size*10;
				}
			else //inch
				{
				valu_temp=Knife_datas.size;
				}
			}
		else
			{
			current_flag =1;	//valu_temp==0;
			}
		}
	else
		{
		current_flag =1;	//valu_temp==0;
		}	
	}
if(current_flag ==1)		//当前尺寸
	{
	if(Unit==UNIT_MM)//mm
		{
		if(InTargetPosit_flag==1) 	//目标位置
			valu_temp=TargetSize_temp;
		else	
			valu_temp=CurrentSize;
		
		valu_temp*=10;
		}
	else  //inch
		{
		if(InTargetPosit_flag==1)  	//目标位置
			valu_temp=TargetSize_inch;
		else	
			valu_temp=CurrentSize*100/254;
		}
	}
//if(valu_temp!=0)
	DataConvert_to_Text(valu_temp,CalcInput_Text); //转换为 显示数据
}


void ShowTouchWind(void)//弹出触摸window
{
ClrInput_function();//清零 输入框
	//弹出 计算器
CalcNoNumInput_flag=1;
Dot_flag=0;
CalcSign_order=0;//首个运算符 位置
CalcData_temp=0;
CalcResultDis_flag=0;
num_cou=0;
if(Sign_flag==1)//清除 加,减号
	{
	GLCD_SetWindow_Fill( SIZE_WINDOW_X, SIZE_WINDOW_Y, SIZE_WINDOW_X+120, SIZE_WINDOW_Y+30, 0xfffff, 0xffff);//尺寸输入框
	Sign_flag=0;
	}

CalcInput_cou=0;
Calculator_Window();  //计算器 按钮	
ClrCalcNums_text(CalcInput_Text,CAL_INPUT); //清计算器 输入框
ClrCalcNums_text(CalcResult_Text,CAL_RESULT); //清计算器 结果框 
CalcInputNums_dis(CalcInput_Text);  //输入框 显示
CalcResultNums_dis(CalcResult_Text);//结果框 显示
InputTouch_flag=1;
}
//------------
void ArithmeticInputSize(void)  //对当前尺寸 算数计算
{
volatile Int32U newsize_temp=0,prev_data;
volatile Int8U Flg_chg=0,flag_now;
if(Knife_order<MAIX_Knife)	//刀数据 未满
	{
	CheckInputNums();
	if(InputSize>0)
		{
		pKnife_data=(pInt8U)&OneKnife_data;
		GetOneKnife_datas(Pro_data.pro_num, Knife_order, pKnife_data);// 读取当前刀 尺寸
		prev_data=OneKnife_data.size;
		switch(Arithmetic_mode)
			{
			case 0:
					break;
			case PLUS_SIGN: //  +
				newsize_temp=prev_data+InputSize;
					break;
			case MINUS_SIGN: //  -	
				if(prev_data>InputSize)
					newsize_temp=prev_data-InputSize;
				else
					newsize_temp=0;
					break;
			case MULT_SIGN: //*	
				newsize_temp=prev_data*InputSize;
				if(Unit!=UNIT_MM)
					{
					newsize_temp/=1000;
					}	
				else
					{
					newsize_temp/=100;
					}
					break;
			case DIV_SIGN:  //  除/
				if(Unit!=UNIT_MM)
					{
					newsize_temp=prev_data*1000;
					}	
				else
					{
					newsize_temp=prev_data*100;
					}
				newsize_temp=newsize_temp/InputSize;
					break;
			}
			
		if((newsize_temp<Size_MIN_num)||(newsize_temp>Size_MAX_num))//超出范围
			{
			//num_cou=0;
			GLCD_SetWindow_Fill( SIZE_WINDOW_X, SIZE_WINDOW_Y, SIZE_WINDOW_X+120, SIZE_WINDOW_Y+30, 0xfffff, 0xffff);//尺寸输入框
			PromptDis_flag=0;
			GLCD_SetWindow_Fill( REMIND_WINDOW_X, REMIND_WINDOW_Y, REMIND_WINDOW_X+REMIND_LENGTH, REMIND_WINDOW_Y+30, 0xfffff, 0xffff);//提示框
			switch(Language)
				{
				case CHN_HAN:
						Printf24("输入尺寸超过极限!",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,RED_COLOR,0,0xffff);
								break;
				case ENGLISH:
						Printf24("Data exceeds limit!",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,RED_COLOR,0,0xffff);
								break;
				}
			// // if(InputTouch_flag==1)   //触摸下
				// // {
				// // ClearCalculatorInput(); //清零计算器 输入
				// // }	
			}
		else   //数据有效		
			{
			// // if(Unit==UNIT_MM)//mm
				// // {
				// // TargetSize=d_temp;
				// // NewInput_dis(TargetSize);
				// // }
			// // else
				// // {
				// // TargetSize_inch=d_temp;
				// // TargetSize=TargetSize_inch*2.54;
				// // NewInput_dis(TargetSize_inch);
				// // }

			
			//----保存数据----------------
			if(Knife_order<=Knife_sum)  //不是 最后一刀 000.00
				{
				Knife_order++;
				GetOneKnife_datas(Pro_data.pro_num, Knife_order, pKnife_data);// 读取  下一刀
				OneKnife_data.size=newsize_temp;  //尺寸修改
				//SaveOneKnife_datas(Pro_data.pro_num, Knife_order , pKnife_data);//保存一刀数据
				if(Knife_order<=Knife_sum)// 未超过最后一刀
					{
					if(OneKnife_data.k_flag==KNIFE_FLAG)
						{
						if(newsize_temp>prev_data)
							{
							OneKnife_data.k_flag=0; //刀 标志清除
							Flg_chg=1;
							flag_now=OneKnife_data.k_flag;
							}
						}
					}
				SaveOneKnife_datas(Pro_data.pro_num, Knife_order , pKnife_data);//保存一刀数据
				if((Knife_order+1)<=Knife_sum)
					{
					GetOneKnife_datas(Pro_data.pro_num, Knife_order+1, pKnife_data);// 当前光标的下一刀 数据
					 if(OneKnife_data.k_flag==KNIFE_FLAG) //刀 标志
						{
						if(OneKnife_data.size>newsize_temp)
							{
							OneKnife_data.k_flag=0;	//清除 刀 标志
							if(Flg_chg==1)
								{
								Flg_chg=3;
								}
							else
								{
								Flg_chg=2;
								}
							SaveOneKnife_datas(Pro_data.pro_num, Knife_order+1 , pKnife_data);//保存下一刀	
							}
						}
					}
				else
					{
					
					}
					
				//---------显示----
				if(Knife_order>Knife_sum)//更新步骤 总刀数
					{
					Knife_sum=Knife_order;
									SaveKnife_sum(Pro_data.pro_num);//刀数 保存
					}
				StepNum_dis(Knife_sum,Knife_order);//步骤更新	
				//--------刀数据 显示
				if(cursor_row<(PAGE_KNIFE-1))
					{
					CursorMov_dis(cursor_row, 0);//红色光标消失
					OneKnifeDataSel_dis(Knife_order-1, cursor_row,0);  //一刀数据 高亮显示
					cursor_row++;
					CursorMov_dis(cursor_row, 1);//红色光标下移显示
					OneKnifeDataSel_dis(Knife_order, cursor_row,RED_COLOR);  //一刀数据 高亮显示
					if(InputTouch_flag==0) //	 非 触摸计算器 下
						{
						switch(Flg_chg)
							{
							case 1:
								PushFlag_dis(cursor_row,flag_now); // 标记图片 显示
								break;
							case 2:
								PushFlag_dis(cursor_row+1,OneKnife_data.k_flag); //光标处 标记图片 显示
								break;
							case 3:
								PushFlag_dis(cursor_row,flag_now); // 标记图片 显示
								PushFlag_dis(cursor_row+1,OneKnife_data.k_flag); //光标处 标记图片 显示
								break;
							}
						}
					}
				else   //页底
					{
					Size_1page_dis(Knife_order-(PAGE_KNIFE-1),0);//一页尺寸显示
					}
				}
				
				 
			PromptNum_dis();//输入范围 提示
			PromptDis_flag=1;	
			GLCD_SetWindow_Fill( SIZE_WINDOW_X, SIZE_WINDOW_Y, SIZE_WINDOW_X+120, SIZE_WINDOW_Y+30, 0xfffff, 0xffff);//尺寸输入框 符号	
			}
			
		ClrInput_function();//清零 输入框
		Arithmetic_mode=0;
		}
	}
}


void ShiftSpeed_SetExec(Int32U keycode)  //机器类型，档速设定键处理
{
switch(keycode)
	{
	case DENGJU_KEY_CODE:       //向上箭头
		if(MotorType>0)
			{
			SpeedLevelSel_dis(MotorType--,0);
			SpeedLevelSel_dis(MotorType,1);
			SaveMachineType(); //保存  机器类型
			}
		break;
	case DENGFENG_KEY_CODE:   //向下箭头	
		if(MotorType<6)
			{
			SpeedLevelSel_dis(MotorType++,0);
			SpeedLevelSel_dis(MotorType,1);
			SaveMachineType(); //保存  机器类型
			}
		break;
	case DOWN_KEY_CODE:   // 确定	
		break;
	}
}
void LongKey_exec(Int32U keycode,Int32U key_temp)  //长按键处理
{
if(keycode==key_temp)
	 {
	 switch(keycode)
		 {
		 case FIVE_KEY_CODE:  //删除
			  BellOn_Enb();
			  if(WorkStart_flag==1)
				 {
				 if(Run_flag==0)
					{
					if(InputTouch_flag==0)
						{
						if((WorkMode==PROG_MODE)||(WorkMode==TEACH_MODE)||(WorkMode==AUTO_MODE))//编程,示教画面下
						  {
						  if(Knife_order<=Knife_sum)
							 {
							  ClrBuf_datas(Pro_data.pro_num, Knife_order, Knife_sum );//清零
							  SaveBuf_datas(Pro_data.pro_num, Knife_order, Knife_sum );//保存
							  Size_1page_dis(Knife_order,cursor_row);//显示一页

							  if(Knife_order>1)
								{
								Knife_sum=Knife_order-1;
								}
							  else
								{
								Knife_sum=1;
								}
							  SaveKnife_sum(Pro_data.pro_num);//刀数 保存
							  StepNum_dis(Knife_sum,Knife_order);//步骤更新
							 }
						  }
						}
					}
				  else
					{
					
					}
				 }
					  break;
		 case ONE_KEY_CODE:		// F 功能按键
			  BellOn_Enb();
			  if(WorkStart_flag==1)
				 {
				 if(Run_flag==0)
					{
					if(InputTouch_flag==0)
						{
						switch(WorkMode)
							{
							case AUTO_MODE://  自动模式下
								WorkMode=AUTO_TO_SELF_MODE;   //自动-->自刀过度 模式
								PaperCutEnb_signal=1;
								SelfEnterPage_dis();
									break;
							case SELF_CUT_MODE:  //		自刀主 模式
								//------------返回第一刀
								ClrInput_function();//清零 输入框 
								CursorMov_dis(cursor_row, 0);//红色光标消失
								cursor_row=0;
								CursorMov_dis(cursor_row, 1);//红色光标显示
								Knife_order=1;//
								Size_1page_dis(Knife_order,0);//一页尺寸显示
								if(Knife_order<=Knife_sum)
									StepOrder_dis(Knife_order);//步骤更新 
								PromptNum_dis();//输入范围	
								PromptDis_flag=1; 	
									break;
							case SELF_RULER_MODE://自刀 基准
							case SELF_TOOLS_MODE://自刀 参数
								PaperCutEnb_signal=1;
								CurrentArea_recover2(MIDDLE_PAGE_X , MIDDLE_PAGE_Y,  M_PAGE_WIDE, M_PAGE_HIGH);
								WorkMode=SELF_CUT_MODE;  //进入   ----------自刀主 模式
								AutoKnife_dis(SELF_KNIFE_X,SELF_KNIFE_Y);//自刀
								//------------返回第一刀
								ClrInput_function();//清零 输入框 
								CursorMov_dis(cursor_row, 0);//红色光标消失
								cursor_row=0;
								CursorMov_dis(cursor_row, 1);//红色光标显示
								Knife_order=1;//
								Size_1page_dis(Knife_order,0);//一页尺寸显示
								if(Knife_order<=Knife_sum)
									StepOrder_dis(Knife_order);//步骤更新 
								PromptNum_dis();//输入范围	
								PromptDis_flag=1; 	
									break;
							case SELF_PLUS_MODE: //自刀 F3++
								PaperCutEnb_signal=1;
								F3_plus_dis(0);
								WorkMode=SELF_CUT_MODE;
								//------------返回第一刀
								ClrInput_function();//清零 输入框 
								CursorMov_dis(cursor_row, 0);//红色光标消失
								cursor_row=0;
								CursorMov_dis(cursor_row, 1);//红色光标显示
								Knife_order=1;//
								Size_1page_dis(Knife_order,0);//一页尺寸显示
								if(Knife_order<=Knife_sum)
									StepOrder_dis(Knife_order);//步骤更新 
								PromptNum_dis();//输入范围	
								PromptDis_flag=1; 	
									break;
							case SELF_MINUS_MODE://自刀 F4--
								PaperCutEnb_signal=1;
								F4_minus_dis(0);
								WorkMode=SELF_CUT_MODE;
								//------------返回第一刀
								ClrInput_function();//清零 输入框 
								CursorMov_dis(cursor_row, 0);//红色光标消失
								cursor_row=0;
								CursorMov_dis(cursor_row, 1);//红色光标显示
								Knife_order=1;//
								Size_1page_dis(Knife_order,0);//一页尺寸显示
								if(Knife_order<=Knife_sum)
									StepOrder_dis(Knife_order);//步骤更新 
								PromptNum_dis();//输入范围	
								PromptDis_flag=1; 	
									break;
							}
						}
					}
				  else
					{
					
					}
				 }
					break;
		 }
	 }
}

void MultiKey_exec(Int32U keycode)  //组合键处理
{
Int16U knife;
Int8U knife_set_flag=0;
pInt8U pbuf;
Int32U offset;
Int16U j;
switch (keycode)
	 {
	 case ONE_KEY_CODE+NINE_KEY_CODE:		//F 功能按键 + 1 ***********
			LongExec_flag=1;	
			KeyExec(AUTO_KEY_CODE);	//F1  code
				break;
	 case ONE_KEY_CODE+MOVE_KEY_CODE:		// F 功能按键 +2************
			LongExec_flag=1;	
			KeyExec(READ_KEY_CODE);	//F2  code
				break;
	 case ONE_KEY_CODE+DELETE_KEY_CODE:		//F 功能按键 + 3 ***********
			LongExec_flag=1;	
			KeyExec(RETURN_KEY_CODE);	//F3  code
				break;
	 case ONE_KEY_CODE+EIGHT_KEY_CODE:		// F 功能按键 +4************
			LongExec_flag=1;	
			KeyExec(MANUAL_KEY_CODE);	//F4  code
				break;
				
	 case ONE_KEY_CODE+NO_KEY_CODE:		  //F 功能按键 + 5 ***********刀标志
			BellOn_Enb();
			LongExec_flag=1;	
			if(WorkStart_flag==1)
				{
				if(Run_flag==0)
				  {
				  if(InputTouch_flag==0)
					 {
					  switch(WorkMode)
						  {
						  case PROG_MODE://编程画面下
						  case TEACH_MODE://示教画面下
							//----保存数据----------------
							 if(Knife_order>1)
								{
								 pKnife_data=(pInt8U)&OneKnife_data;
								 GetOneKnife_datas(Pro_data.pro_num, Knife_order-1, pKnife_data);//
								 InputSize=OneKnife_data.size;
								 GetOneKnife_datas(Pro_data.pro_num, Knife_order, pKnife_data);//
								 if((OneKnife_data.size<InputSize)&&(OneKnife_data.size>0))//小于 前一刀
									{
									if(OneKnife_data.k_flag!=KNIFE_FLAG) //
										{
										OneKnife_data.k_flag=KNIFE_FLAG;//  设定 刀标志
										}
									else
										{
										OneKnife_data.k_flag=0;// 清除 标志
										}
									PushFlag_dis(cursor_row,OneKnife_data.k_flag); //显示----
									SaveOneKnife_datas(Pro_data.pro_num, Knife_order , pKnife_data);//保存一刀数据
									PromptNum_dis();//输入范围
									PromptDis_flag=1;
									}
								 else
									{
									PromptDis_flag=0;
									GLCD_SetWindow_Fill(REMIND_WINDOW_X, REMIND_WINDOW_Y, REMIND_WINDOW_X+REMIND_LENGTH, REMIND_WINDOW_Y+30, 0xfffff, 0xffff);//提示框
									switch(Language)
										{
										case CHN_HAN:
											Printf24("此刀标志设定无效!",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,RED_COLOR,0,0xffff);
												break;
										case ENGLISH:
											Printf24("Invalid Mark!",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,RED_COLOR,0,0xffff);
												break;
										}
									}
									
								}
							 else
								{
								PromptDis_flag=0;
								GLCD_SetWindow_Fill( REMIND_WINDOW_X, REMIND_WINDOW_Y, REMIND_WINDOW_X+REMIND_LENGTH, REMIND_WINDOW_Y+30, 0xfffff, 0xffff);//提示框
								switch(Language)
										{
										case CHN_HAN:
											Printf24("此刀标志设定无效!",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,RED_COLOR,0,0xffff);
												break;
										case ENGLISH:
											Printf24("Invalid Mark!",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,RED_COLOR,0,0xffff);
												break;
										}
								}
								break;
						  case AUTO_MODE://自动 主模式下
								pKnife_data=(pInt8U)&OneKnife_data;
								GetOneKnife_datas(Pro_data.pro_num, Knife_order, pKnife_data);//
								if(OneKnife_data.size>0)
									{
									if(OneKnife_data.k_flag!=PRE_AUTO_FLAG)  //自动循环图标
										{
										OneKnife_data.k_flag=PRE_AUTO_FLAG;//  设定 标志
										}
									else
										{
										OneKnife_data.k_flag=0;// 清除 标志
										}
									PushFlag_dis(cursor_row,OneKnife_data.k_flag); //显示----
									// RenewModifyDate();	//更新时间信息-.-.-.-.-.-.-.-.-.-.-.-.-.-
									SaveOneKnife_datas(Pro_data.pro_num, Knife_order , pKnife_data);//保存一刀数据
									PromptNum_dis();//输入范围
									PromptDis_flag=1;
									}
						  		break;
						  }
					 }
				  }
				else//运行中
				  {
				  
				  }
				}
				break;
	 case ONE_KEY_CODE+ PROG_KEY_CODE: //F 功能按键 +  数字0************ 批量 刀标志
			BellOn_Enb();
			LongExec_flag=1;
			if(WorkStart_flag==1)
				{
				if(Run_flag==0)
				  {
				  if(InputTouch_flag==0)
					 {
					  switch(WorkMode)
						  {
						  case PROG_MODE://编程画面下
						  case TEACH_MODE://示教画面下
								knife=2;
								
								if(Pro_data.pro_num<=(PROG_GROPU1+1))  //前301个prog
								   {
								   offset=PROG_BYTES1*(Pro_data.pro_num-1);
								   }
								else//后  199
								   {
								   offset=PROG_BYTES1*PROG_GROPU1+(Pro_data.pro_num-PROG_GROPU1-1)*PROG_BYTES2;
								   }
								pbuf=(pInt8U)(K_SIZE_sdram+offset+2+(knife-1)*5+4);//程序基地址
								
							//----  处理所有刀  标志-------------
								pKnife_data=(pInt8U)&OneKnife_data;
								
								GetOneKnife_datas(Pro_data.pro_num, knife-1, pKnife_data);//
								while(knife<=Knife_sum)
									{
									
									if(AllKnifeSet_flag==0)//设定 所有刀标志
										{
										
										InputSize=OneKnife_data.size;
										GetOneKnife_datas(Pro_data.pro_num, knife, pKnife_data);//
										if((OneKnife_data.size<InputSize)&&(OneKnife_data.size>0))//小于 前一刀
											{
											if(OneKnife_data.k_flag!=KNIFE_FLAG) 
												{
												//OneKnife_data.k_flag=KNIFE_FLAG;  
												//SaveOneKnife_datas(Pro_data.pro_num,knife , pKnife_data);//保存一刀数据
												//*pbuf=*(pKnife_data+4);
												*pbuf=KNIFE_FLAG;
												}
											}
										pbuf+=5;
										}
									else	 //清除  所有刀标志
										{
										GetOneKnife_datas(Pro_data.pro_num, knife, pKnife_data);//
										if(OneKnife_data.k_flag==KNIFE_FLAG) 
											{
											//OneKnife_data.k_flag=0;// 清除 标志
											//SaveOneKnife_datas(Pro_data.pro_num,knife , pKnife_data);//保存一刀数据
											*pbuf=0;
											}
										pbuf+=5;	
										}
									knife_set_flag=1;	
											
									knife++;	
									}
									
									
									
									
									
									if(AllKnifeSet_flag==0)
										AllKnifeSet_flag=1;
									else
										AllKnifeSet_flag=0;
										
								if(knife_set_flag==1)   //更新  显示---------
									{
									SaveBuf_datas(Pro_data.pro_num, 1, Knife_sum );//保存
									//------------返回第一刀
									ClrInput_function();//清零 输入框 
									CursorMov_dis(cursor_row, 0);//红色光标消失
									cursor_row=0;
									CursorMov_dis(cursor_row, 1);//红色光标显示
									Knife_order=1;//
									Size_1page_dis(Knife_order,0);//一页尺寸显示
									if(Knife_order<=Knife_sum)
										StepOrder_dis(Knife_order);//步骤更新	
									//PromptNum_dis();//输入范围
									//PromptDis_flag=1;	
									}
									break;
						  }
					 }
				  }
				}
				break;
	 case DENGJU_KEY_CODE+MOVE_KEY_CODE:	//向上箭头+2  脉冲当量 设定
			BellOn_Enb();
			LongExec_flag=1;
			if(WorkStart_flag==1)
			  {
			   if(MotorType<MOTOR_DC_SERVO)    //变频器--
				  {
				  if(Run_flag==0)
					 {
					 if(InputTouch_flag==0)
						{
						 switch(WorkMode)
							{
							case MANUAL_MODE: //手动模式
								if(Sign_flag==1)
									{
									num_cou=0;
									GLCD_SetWindow_Fill( SIZE_WINDOW_X, SIZE_WINDOW_Y, SIZE_WINDOW_X+120, SIZE_WINDOW_Y+30, 0xfffff, 0xffff);//尺寸输入框
									Sign_flag=0;
									}
								 WorkMode=MANUAL_PULSE_MODE;
								 PulseDegreePage_dis();
								 PromptDis_flag=0;
								 ClrInput_function();//清零 输入框
								 Para_sel=Pulse_degree;
									break;
							}
						}	
					 }
				   else	//运行中
					 {
					 }
				  }
			  }
				break;
	 case DENGFENG_KEY_CODE+YES_KEY_CODE://向下箭头+8 密码模式
			BellOn_Enb();
			LongExec_flag=1;
			if(WorkStart_flag==1)
			  {
			  if(Run_flag==0)
				 {
				 if(InputTouch_flag==0)
					{
					switch(WorkMode)
						{
						case MANUAL_MODE: //手动模式
							if(Sign_flag==1)
								{
								num_cou=0;
								GLCD_SetWindow_Fill( SIZE_WINDOW_X, SIZE_WINDOW_Y, SIZE_WINDOW_X+120, SIZE_WINDOW_Y+30, 0xfffff, 0xffff);//尺寸输入框
								Sign_flag=0;
								}
							 WorkMode=MANUAL_PASS_MODE;
							 PassCodePage_dis();
							 PromptDis_flag=0;
							 ClrInput_function();//清零 输入框
							 ACServoAlarmExec_flag=0;
							 break;
						}
					}	
				 }
			  else
				 {
				 
				 }
			  }
				break; 
	 case ONE_KEY_CODE+INSERT_KEY_CODE:   //        F功能按键+6 ----------示教模式
			BellOn_Enb();
			LongExec_flag=1;
			if(WorkStart_flag==1)
			  {
			  if(Run_flag==0)
				 {
				 if(InputTouch_flag==0)
					{
					switch(WorkMode)
						{
						case TEACH_LABEL_MODE: //标签
						case TEACH_DIVIDE_MODE: //等分
						case TEACH_PRO_MODE: //程序选择
							CurrentArea_recover2(MIDDLE_PAGE_X, MIDDLE_PAGE_Y,  M_PAGE_WIDE, M_PAGE_HIGH);
							
						case AUTO_MODE://自动 主模式下************
						case SELF_CUT_MODE://自刀主画面下
						case MANUAL_MODE:// 手动 主模式
							
						case PROG_MODE://编程 主模式下
							WorkMode=TEACH_MODE;  //示教模式
							TeachPage_dis();
							PromptNum_dis();//输入范围	
							PromptDis_flag=1; 
						case TEACH_MODE: //示教主模式	
							//------------返回第一刀
							PaperCutEnb_signal=1;
							ClrInput_function();//清零 输入框 
							CursorMov_dis(cursor_row, 0);//红色光标消失
							cursor_row=0;
							CursorMov_dis(cursor_row, 1);//红色光标显示
							Knife_order=1;//
							Size_1page_dis(Knife_order,0);//一页尺寸显示
							if(Knife_order<=Knife_sum)
								StepOrder_dis(Knife_order);//步骤更新
								
							ACServoAlarmExec_flag=0;	
							if(Sign_flag==1)
								{
								num_cou=0;
								GLCD_SetWindow_Fill( SIZE_WINDOW_X, SIZE_WINDOW_Y, SIZE_WINDOW_X+120, SIZE_WINDOW_Y+30, 0xfffff, 0xffff);//尺寸输入框
								Sign_flag=0;
								}
								break;
						}	
					}
				 }
			  else
				 {
				 
				 }
			  }
				break;
	 case DENGJU_KEY_CODE+DELETE_KEY_CODE:  //	向上箭头+3  档位选择
			BellOn_Enb();
			LongExec_flag=1;	
			if(WorkStart_flag==0)  //未进入工作状态
				{
				switch(MotorType)
					{
					case MOTOR_FREQ_5_SPD_RST:
					case MOTOR_FREQ_3_SPD:
					case MOTOR_FREQ_3_SPD_RST:
					case MOTOR_AC_SERVO:
						if((StartCheck_mode<2)||(StartCheck_mode==4))
							CheckModeOK_flag=1;
						else	
							CheckModeOK_flag=0;
							break;
					case MOTOR_DC_SERVO:
					case MOTOR_DC670_SERVO:
					case MOTOR_DC670_SERVO_ZHU:
					// case MOTOR_AC_SERVO:
						if(StartCheck_mode<5)	
							CheckModeOK_flag=1;
						else	
							CheckModeOK_flag=0;
							break;
					default:
							CheckModeOK_flag=0;
							break;
					}	
				if(CheckModeOK_flag==1)
					{
					if(Board_TestMod==0)
						{
						Board_TestMod=TEST_MOTOR_TYPE;     //电机类型设定  模式
						GLCD_Buffer_Fill(0xffff);
						SpeedLevelSel_dis(0,0);    //电机类型 显示
						SpeedLevelSel_dis(1,0);    //电机类型 显示
						SpeedLevelSel_dis(2,0);    //电机类型 显示
						SpeedLevelSel_dis(3,0);    //电机类型 显示
						SpeedLevelSel_dis(4,0);    //电机类型 显示
						SpeedLevelSel_dis(5,0);    //电机类型 显示
						SpeedLevelSel_dis(6,0);    //电机类型 显示
						SpeedLevelSel_dis(MotorType,1);
						}
					}	
				}
				break;
	case DENGJU_KEY_CODE+NINE_KEY_CODE:			//向上箭头+1  脉冲当量 设定
			BellOn_Enb();
			LongExec_flag=1;
			if(WorkStart_flag==1)
			  {
			   if((MotorType>=MOTOR_DC_SERVO)&&(MotorType<=MOTOR_DC670_SERVO_ZHU))    //DC伺服--
				  {
				  if(Run_flag==0)
					 {
					 if(InputTouch_flag==0)
						{
						 switch(WorkMode)
							{
							case MANUAL_MODE: //手动模式
								if(Sign_flag==1)
									{
									num_cou=0;
									GLCD_SetWindow_Fill( SIZE_WINDOW_X, SIZE_WINDOW_Y, SIZE_WINDOW_X+120, SIZE_WINDOW_Y+30, 0xfffff, 0xffff);//尺寸输入框
									Sign_flag=0;
									}
								 WorkMode=MANUAL_SERVO_C_MODE;   //直流伺服 C 参数
								 Servo_C_DataPage();//直流伺服 ‘C’参数
								 PromptDis_flag=0;
								 Para_sel=0;
								 ClrInput_function();//清零 输入框
									break;
							}
						}	
					 }
				   else	//运行中
					 {
					 }
				  }
			  }
			else
			  {//--------------------------触摸校准
				KeyExec(AUTO_KEY_CODE);	//F1  code
			  }
				break;
	case ONE_KEY_CODE+REV_KEY_CODE:   //    ***************F功能按键+ “+/*”
			BellOn_Enb();
			LongExec_flag=1;
			if(WorkStart_flag==1)  
				{
				if(Run_flag==0)
					{
					if(InputTouch_flag==0)
						{
						switch(WorkMode)
							{
							//case MANUAL_MODE:   //手动
							case PROG_MODE:	//编程模式
							case TEACH_MODE:   //示教模式
								if(Sign_flag==0)         //* 号
									{
									ClrInput_function();//清零 输入框
									Printf24(" *",SIZE_WINDOW_X,SIZE_WINDOW_Y,RED_COLOR,1,0xffff);
									Sign_flag=1;
									Minus_flag=0;
									Arithmetic_mode=MULT_SIGN;//  "*"
									} 
								else               //清除 *号
									{
									num_cou=0;
									GLCD_SetWindow_Fill( SIZE_WINDOW_X, SIZE_WINDOW_Y, SIZE_WINDOW_X+120, SIZE_WINDOW_Y+30, 0xfffff, 0xffff);//尺寸输入框
									Sign_flag=0;
									Arithmetic_mode=NO_SIGN;//---0
									}
									break;
							}
						}
					else    //计算器 弹出模式
						{
						CalculatorValue_exec('*');	
						}
					
					}	
				} 	
				break;
	case ONE_KEY_CODE+OPTION_KEY_CODE:   //    ***************F功能按键+ “-/除”
			BellOn_Enb();
			LongExec_flag=1;
			if(WorkStart_flag==1)  
				{
				if(Run_flag==0)
					{
					if(InputTouch_flag==0)
						{
						switch(WorkMode)
							{
							//case MANUAL_MODE:   //手动
							case PROG_MODE:	//编程模式
							case TEACH_MODE:   //示教模式
								if(Sign_flag==0)         //除 号
									{
									ClrInput_function();//清零 输入框
									Printf24(" /",SIZE_WINDOW_X,SIZE_WINDOW_Y,RED_COLOR,1,0xffff);
									Sign_flag=1;
									Minus_flag=0;
									Arithmetic_mode=DIV_SIGN;//  "/"
									} 
								else               //清除 *号
									{
									num_cou=0;
									GLCD_SetWindow_Fill( SIZE_WINDOW_X, SIZE_WINDOW_Y, SIZE_WINDOW_X+120, SIZE_WINDOW_Y+30, 0xfffff, 0xffff);//尺寸输入框
									Sign_flag=0;
									Arithmetic_mode=NO_SIGN;//---0
									}
									break;
							}
						}
					else    //计算器 弹出模式
						{
						CalculatorValue_exec('/');	
						}
					
					}	
				} 	
				break;			
	 }
}

void KeyExec(Int32U keycode)  //键处理
{
Int32U d_temp=0;
Int32U target_temp;
Int32U input_temp,perv_data;
	 
Int16U x,y,gap,back_color,line_color;

Int16U knife,K_temp;
Int8U knife_set_flag=0,Flg_chg=0,flag_now;
pInt8U pbuf;
Int32U offset;
Int16U ServMaxSpd1,ServMaxSpd2;

BellOn_Enb();
switch(keycode)
	{
	//case tst_KEY_CODE: //停止
	case STOP_KEY_CODE: //停止
		if(WorkStart_flag==1)
			{
			if(Run_flag==1)  //运行中
				{
				if(AutoCutStart_flag==0)
					{
					switch(MotorType)
						{
						case MOTOR_FREQ_5_SPD_RST:
						case MOTOR_FREQ_3_SPD:
						case MOTOR_FREQ_3_SPD_RST:
							SelfLockEn_flag=0; //取消自锁
							ToTargetStop_flag=0;
							MoveStop();
							ForceStop_flag=0;
							BackStop_flag=0;
							Backward_flag=0;
							Forward_flag=0;	
							RunStop_flag=0;
								break;
						case MOTOR_DC_SERVO:
						case MOTOR_DC670_SERVO:
						case MOTOR_DC670_SERVO_ZHU:
							DCServoStop();  //停止运行
							ServoPressStop_flag=0;
							DcServoGoTarget_flag=0;
							BellStart_flag=0;
								break;
						case MOTOR_AC_SERVO:
							ACServoStop();
								break;
						}
					Run_flag=0;	
					InTargetPosit_flag=0;	//目标位置
					AutoPushRun_flag=0; //自动推纸 运行
					TargetSize=0;
					TargetSize_temp=0;
					BeforeKnife_offset_in=0;
					if(InputTouch_flag==0)
						ClrInput_function();//清零 输入框
					//PaperCutEnb_signal=1;	
					AutoRoute_flag=0;
					RLOUT1_OFF;    // 允许裁切
					}
				}
			else
				{
				if(MotorType<MOTOR_DC_SERVO)
					{
					if(FreqMotorStop_flag==0)  //强制  停止
						{
						SelfLockEn_flag=0; //取消自锁
						ToTargetStop_flag=0;
						MoveStop();
						ForceStop_flag=0;
						BackStop_flag=0;
						Backward_flag=0;
						Forward_flag=0;	
						RunStop_flag=0;
						
						InTargetPosit_flag=0;	//目标位置
						AutoPushRun_flag=0; //自动推纸 运行
						TargetSize=0;
						TargetSize_temp=0;
						BeforeKnife_offset_in=0;
						if(InputTouch_flag==0)
							ClrInput_function();//清零 输入框
						//PaperCutEnb_signal=1;	
						AutoRoute_flag=0;
						RLOUT1_OFF; RLOUT1_1_OFF;   // 允许裁切
						}
					}
				}
			}	
			break;
    case NINE_KEY_CODE+MOVE_KEY_CODE:
			break; 
	case   	0xffff000c: //电子手轮  开关
		if(WorkStart_flag==1)
			{
			if(Run_flag==0)
				{
				if(MotorType==MOTOR_AC_SERVO)
					{
					switch(WorkMode)
						{
						case AUTO_MODE://自动
						case MANUAL_MODE:   //手动
							ElectricWheelOn_flag=!ElectricWheelOn_flag;
							SaveElectricWheelSwitch();//电子手轮
							ElectricalWheel_dis();  //电子手轮  开关状态
								break;
						}
					}
				}
			}
			break; 
    case   	0xffff0007://MUL_TOUCH_CODE    乘法  *
		if(WorkStart_flag==1)
			{
			if(Run_flag==0)
				{
				if(InputTouch_flag==1)
					{
					CalculatorValue_exec('*');
					}
				}
			}	
			break;
   	case	0xffff0008:  //   DIV_TOUCH_CODE  除法/
		if(WorkStart_flag==1)
			{
			if(Run_flag==0)
				{
				if(InputTouch_flag==1)
					{
					CalculatorValue_exec('/');
					}
				}
			}
			break;
	case	0xffff0009:  //     EQU_TOUCH_CODE       结果 =  
		if(WorkStart_flag==1)
			{
			if(Run_flag==0)
				{
				if(InputTouch_flag==1)
					{
					if(WorkMode == TEACH_MODE)	//=======示教 模式========  运行到当前 值
						{
						if(CheckInputNums()==1)// 输入 有效
							{
							if(InputSize!=CurrentSize)
								{
								if(Unit==UNIT_MM)//mm
									{
									TargetSize=InputSize;
									}
								else
									{
									TargetSize_inch=InputSize;
									TargetSize=TargetSize_inch*2.54;
									}
								TargetSize_temp=TargetSize;
								switch(MotorType)
									{
									case MOTOR_FREQ_5_SPD_RST:
									case MOTOR_FREQ_3_SPD:
									case MOTOR_FREQ_3_SPD_RST:
										 SelfLockEn_flag=0;
										 ToTargetStop_flag=0;
										 MoveSpeed=0;
										 MoveSpeedCtrl();  //运行速度控制
											break;
									case MOTOR_DC_SERVO:
									case MOTOR_DC670_SERVO:
									case MOTOR_DC670_SERVO_ZHU:
										 ServoSendCou=0;
										 DcServoStartRun_exec(TargetSize);
										// SelfLockEn_flag=0;
											break;
									case MOTOR_AC_SERVO:
										 ACMotorRunStart(TargetSize);
										// SelfLockEn_flag=0;
											break;		
									}
								Run_flag=1;
								RunStop_flag=0;
								InTargetPosit_flag=0;	//目标位置
								OneCutRoutine_flag=0; // 清 裁切 循环标志
								AutoCutStart_flag=0;
								PromptNum_dis();
								}
							}				
						}
					else
						{
						if(CalcResultDis_flag==0)
							{
							CalcGetValue_exec();
							}	
						}
					}
				}
			}
			break;		
	case 0xffff0001:	//INPUT_TOUCH_CODE	 输入框 触摸 
		if(WorkStart_flag==1)
			{
			if(Run_flag==0)
				{
				ClrInput_function();//清零 输入框
				if(InputTouch_flag==0)  //进入触摸 计算器输入
					{
					CalcNoNumInput_flag=1;
					Dot_flag=0;
					CalcSign_order=0;//首个运算符 位置
					CalcData_temp=0;
					CalcResultDis_flag=0;
					num_cou=0;
					if(Sign_flag==1)//清除 加,减号
						{
						GLCD_SetWindow_Fill( SIZE_WINDOW_X, SIZE_WINDOW_Y, SIZE_WINDOW_X+120, SIZE_WINDOW_Y+30, 0xfffff, 0xffff);//尺寸输入框
						Sign_flag=0;
						}
					
					CalcInput_cou=0;
					Calculator_Window();  //计算器 按钮	
					ClrCalcNums_text(CalcInput_Text,CAL_INPUT); //清计算器 输入框
					ClrCalcNums_text(CalcResult_Text,CAL_RESULT); //清计算器 结果框 
					CalcInputNums_dis(CalcInput_Text);  //输入框 显示
					CalcResultNums_dis(CalcResult_Text);//结果框 显示
					InputTouch_flag=1;
					}
				else         //退出
					{
					//CalcInput_cou=0;
					CalcuInClear_exec();     //清除 计算器
					switch(WorkMode)
						{
						case AUTO_TOOLS_MODE:
						case MANUAL_TOOLS_MODE:
						case SELF_TOOLS_MODE:
							back_color=0xef9f;
							x=PARA_START_X1+PARA_COL_WIDE,y=PARA_START_Y,gap=30;
							if(PramSel_Page<1)	//page 1
								{
								//if(Para_sel<7)
								//	{
									ParameterPage_dis(7, 0);
									if((MotorType>=MOTOR_DC_SERVO)&&(MotorType<=MOTOR_DC670_SERVO_ZHU))
										{
										ParameterPage_dis(8, 0);
										ParameterPage_dis(9, 0);
										}
									else if(MotorType==MOTOR_AC_SERVO)	
										{
										ParameterPage_dis(8, 0);
										}
									ParameterPage_dis(Para_sel, 1);
								//	}
								switch(Language)
									{
									case CHN_HAN:
										Printf24("压纸停机:   ",x,y,BLACK_COLOR,1,back_color);y+=gap;
										if((MotorType>=MOTOR_DC_SERVO)&&(MotorType<=MOTOR_DC670_SERVO_ZHU))
											{
											Printf24("最大速度:   ",x,y,BLACK_COLOR,1,back_color);y+=gap;
											Printf24("点动速度:   ",x,y,BLACK_COLOR,1,back_color);
											}
										else if(MotorType==MOTOR_AC_SERVO)
											{
											Printf24("运行速度:   ",x,y,BLACK_COLOR,1,back_color);y+=gap;
											}	
											break;
									case ENGLISH:
										Printf24("Press-Stop:",x,y,BLACK_COLOR,1,back_color);y+=gap;
										if((MotorType>=MOTOR_DC_SERVO)&&(MotorType<=MOTOR_DC670_SERVO_ZHU))
											{
											Printf24("Max-speed:",x,y,BLACK_COLOR,1,back_color);y+=gap;
											Printf24("Jog-speed:",x,y,BLACK_COLOR,1,back_color);
											}
										else if(MotorType==MOTOR_AC_SERVO)
											{
											Printf24("Run-speed:",x,y,BLACK_COLOR,1,back_color);y+=gap;
											}
											break;
									}			
								}
							else	//page 2
								{
									
								}
							
							break;
						
						case  PROG_MODE://编程画面下
						case AUTO_MODE://自动主画面下
						case AUTO_PLUS_MODE://自动F3++
						case AUTO_MINUS_MODE://自动F4--
						case TEACH_MODE://示教 模式
						case AUTO_TO_SELF_MODE:   //自动-->自刀过度 模式
						case SELF_CUT_MODE:  //自刀主 模式
						case SELF_PLUS_MODE: //自刀 F3++
						case SELF_MINUS_MODE://自刀 F4--
							if(Knife_order>Knife_sum)
								 K_temp=Knife_order-1;
							 else
								 K_temp=Knife_order;
							ProgressBar_dis(Knife_sum,K_temp);  //进度条 显示
							KnifeUp_flag=0;
							KnifeDown_flag=0;
							PressUp_flag=0;
							PressDown_flag=0;
							A_Down_flag=0;
							B_Down_flag=0;
							A_Up_flag=0;
							B_Up_flag=0;
							IR_Up_flag=0;
							IR_Down_flag=0;
							//--------------更新显示刀——推纸标志
							// CursorMov_dis(cursor_row, 0);//红色光标消失
							// cursor_row=0;
							// CursorMov_dis(cursor_row, 1);//红色光标显示
							//Knife_order=1;//
							Size_1page_dis(Knife_order-cursor_row,0);//一页尺寸显示
							break;
						}
					}
				}
			else   //运行中
				{
				
				}
		    }
        	break;      
	case ONE_KEY_CODE:		// F 功能按键******************
		if(WorkStart_flag==0)  //未进入工作状态
			{
			switch(MotorType)
				{
				case MOTOR_FREQ_5_SPD_RST:
				case MOTOR_FREQ_3_SPD:
				case MOTOR_FREQ_3_SPD_RST:
				case MOTOR_AC_SERVO:
						if((StartCheck_mode<2)||(StartCheck_mode==4))
							CheckModeOK_flag=1;
						else
							CheckModeOK_flag=0;
						break;
				case MOTOR_DC_SERVO:
				case MOTOR_DC670_SERVO:
				case MOTOR_DC670_SERVO_ZHU:
						if(StartCheck_mode<2)
							CheckModeOK_flag=1;
						else
							CheckModeOK_flag=0;
						break;
				// case MOTOR_AC_SERVO:
						// if(StartCheck_mode<3)
							// CheckModeOK_flag=1;
						// else
							// CheckModeOK_flag=0;
						// break;		
				default:
						CheckModeOK_flag=0;
						break;
				}
			if(CheckModeOK_flag==1)
				{
				if(Board_TestMod==0)
					{
					Board_TestMod=TEST_BOARD;     //主板测试  模式
					GLCD_Buffer_Fill(0xffff);
					IO_InputDisInit();  //Io 输入口初始值
					KeyDis_Init();//按键显示初始化
					}
				else if(Board_TestMod==TEST_BOARD)
					{
					
					}
				}
			}
		else
			{
			if(Run_flag==1)  //运行中
				{
				if(AutoCutStart_flag==0)
					{
					switch(MotorType)
						{
						case MOTOR_FREQ_5_SPD_RST:
						case MOTOR_FREQ_3_SPD:
						case MOTOR_FREQ_3_SPD_RST:
							SelfLockEn_flag=0; //取消自锁
							ToTargetStop_flag=0;
							MoveStop();
							ForceStop_flag=0;
							BackStop_flag=0;
							Backward_flag=0;
							Forward_flag=0;	
							RunStop_flag=0;
								break;
						case MOTOR_DC_SERVO:
						case MOTOR_DC670_SERVO:
						case MOTOR_DC670_SERVO_ZHU:
							DCServoStop();  //停止运行
							ServoPressStop_flag=0;
							DcServoGoTarget_flag=0;
							BellStart_flag=0;
								break;
						case MOTOR_AC_SERVO:
							ACServoStop();
								break;		
						}
					Run_flag=0;	
					InTargetPosit_flag=0;	//目标位置
					AutoPushRun_flag=0; //自动推纸 运行
					TargetSize=0;
					TargetSize_temp=0;
					BeforeKnife_offset_in=0;
					if(InputTouch_flag==0)
						ClrInput_function();//清零 输入框
					AutoRoute_flag=0;	
					RLOUT1_OFF; RLOUT1_1_OFF;   // 允许裁切
					}
				}
			else
				{
				if(MotorType<MOTOR_DC_SERVO)
					{
					if(FreqMotorStop_flag==0)  //强制  停止
						{
						SelfLockEn_flag=0; //取消自锁
						ToTargetStop_flag=0;
						MoveStop();
						ForceStop_flag=0;
						BackStop_flag=0;
						Backward_flag=0;
						Forward_flag=0;	
						RunStop_flag=0;
						
						InTargetPosit_flag=0;	//目标位置
						AutoPushRun_flag=0; //自动推纸 运行
						TargetSize=0;
						TargetSize_temp=0;
						BeforeKnife_offset_in=0;
						if(InputTouch_flag==0)
							ClrInput_function();//清零 输入框
						//PaperCutEnb_signal=1;	
						AutoRoute_flag=0;
						}
					}
				}
			}
  	         break;
	case TWO_KEY_CODE:		//手动****************
        if(WorkStart_flag==1)  
			{
			if(Run_flag==0)
			    {
				if(InputTouch_flag==0)
					{
					switch(WorkMode)
						{
						case PROG_MODE://编程 主模式下********
						case TEACH_MODE://示教 模式
						case AUTO_MODE://自动 主模式下*******
						case SELF_CUT_MODE://自刀主画面下
							WorkMode=MANUAL_MODE;  //进入 手动模式
							ManualModePage_dis();
							ClrInput_function();//清零 输入框
							PromptNum_dis();//输入范围
							PromptDis_flag=1; 
							PaperCutEnb_signal=1;
							ACServoAlarmExec_flag=0;
							if(Sign_flag==1)//清除 加,减号
								{
								GLCD_SetWindow_Fill( SIZE_WINDOW_X, SIZE_WINDOW_Y, SIZE_WINDOW_X+120, SIZE_WINDOW_Y+30, 0xfffff, 0xffff);//尺寸输入框
								Sign_flag=0;
								}
							break;
						case MANUAL_TOOLS_MODE:// 手动 参数模式
						case MANUAL_RULER_MODE://手动 基准模式
						case MANUAL_CLOCK_MODE://手动 时钟模式
						case MANUAL_PULSE_MODE://手动 脉冲设定模式
						case MANUAL_PASS_MODE://手动 密码模式
						case MANUAL_SERVO_C_MODE://手动直流伺服 C 参数 
							WorkMode=MANUAL_MODE;//返回    ---------手动 主模式
							Para_sel=0;
							CurrentArea_recover2(MIDDLE_PAGE_X , MIDDLE_PAGE_Y, M_PAGE_WIDE, M_PAGE_HIGH);
							Manual_dis(MANUAL_X,MANUAL_Y);//手动
						case MANUAL_MODE:   //手动	
							if(Sign_flag==1)
								{
								num_cou=0;
								GLCD_SetWindow_Fill( SIZE_WINDOW_X, SIZE_WINDOW_Y, SIZE_WINDOW_X+120, SIZE_WINDOW_Y+30, 0xfffff, 0xffff);//尺寸输入框
								Sign_flag=0;
								}	
							PromptNum_dis();//输入范围
							PromptDis_flag=1;
							ClrInput_function();//清零 输入框
							ACServoAlarmExec_flag=0;
							break;		
						}		
					}
				else   //计算器
					{
					
					}
			    }
			else //运行中
			    {
				if(AutoCutStart_flag==0)
					{
					switch(MotorType)
						{
						case MOTOR_FREQ_5_SPD_RST:
						case MOTOR_FREQ_3_SPD:
						case MOTOR_FREQ_3_SPD_RST:
							ForceStop_flag=1;
							stop_time=0;
								break;
						case MOTOR_DC_SERVO:
						case MOTOR_DC670_SERVO:
						case MOTOR_DC670_SERVO_ZHU:
							DCServoStop();  //停止运行
							ServoPressStop_flag=0;
							DcServoGoTarget_flag=0;
							BellStart_flag=0;
							//************
							Run_flag=0;	
							InTargetPosit_flag=0;	//目标位置
							AutoPushRun_flag=0; //自动推纸 运行
							TargetSize=0;
							TargetSize_temp=0;
							BeforeKnife_offset_in=0;
							AutoRoute_flag=0;
								break;
						case MOTOR_AC_SERVO:
							ACServoStop();
							//************
							Run_flag=0;	
							InTargetPosit_flag=0;	//目标位置
							AutoPushRun_flag=0; //自动推纸 运行
							TargetSize=0;
							TargetSize_temp=0;
							BeforeKnife_offset_in=0;
							AutoRoute_flag=0;
								break;
						}
					// TargetSize=0;
					// TargetSize_temp=0;
					// BeforeKnife_offset_in=0;
					if(InputTouch_flag==0)
						ClrInput_function();//清零 输入框
					}
				}
			}
  	     break;   
	case THREE_KEY_CODE:		//自动******************
		if(WorkStart_flag==1)
			{
			if(Run_flag==0)
			    {
				if(InputTouch_flag==0)
					{
					switch(WorkMode)
						{
						case PROG_MODE://编程 主模式下
						case TEACH_MODE://示教 模式
						case MANUAL_MODE:// 手动 主模式
							if(Sign_flag==1)
								{
								num_cou=0;
								GLCD_SetWindow_Fill( SIZE_WINDOW_X, SIZE_WINDOW_Y, SIZE_WINDOW_X+120, SIZE_WINDOW_Y+30, 0xfffff, 0xffff);//尺寸输入框
								Sign_flag=0;
								}
						case SELF_CUT_MODE://自刀主画面下
							WorkMode=AUTO_MODE;//进入 自动模式
							PaperCutEnb_signal=1;
							PressCircle_mode=0;
							AutoModePage_dis();
							PromptNum_dis();//输入范围	
							PromptDis_flag=1; 
						case AUTO_MODE://自动 主模式下
							//------------返回第一刀
							ClrInput_function();//清零 输入框 
							CursorMov_dis(cursor_row, 0);//红色光标消失
							cursor_row=0;
							CursorMov_dis(cursor_row, 1);//红色光标显示
							Knife_order=1;//
							Size_1page_dis(Knife_order,0);//一页尺寸显示
							if(Knife_order<=Knife_sum)
								StepOrder_dis(Knife_order);//步骤更新
							PromptNum_dis();//输入范围	
							PromptDis_flag=1;  
							ACServoAlarmExec_flag=0;
							
							F0Button_dis(AllKnifeSet_flag);  //F0 所有 刀 标记 按钮/
							break;
							//自动模式------------------------------------------
						case AUTO_RULER_MODE:	//基准模式
						case AUTO_TOOLS_MODE:	 //参数模式	
							Para_sel=0;
							WorkMode=AUTO_MODE;//返回    自动 主模式
							PaperCutEnb_signal=1;
							PressCircle_mode=0;
							CurrentArea_recover2(MIDDLE_PAGE_X , MIDDLE_PAGE_Y,  M_PAGE_WIDE, M_PAGE_HIGH);
							Auto_dis(AUTO_X, AUTO_Y); //自动
							//------------返回第一刀
							ClrInput_function();//清零 输入框 
							CursorMov_dis(cursor_row, 0);//红色光标消失
							cursor_row=0;
							CursorMov_dis(cursor_row, 1);//红色光标显示
							Knife_order=1;//
							Size_1page_dis(Knife_order,0);//一页尺寸显示
							if(Knife_order<=Knife_sum)
								StepOrder_dis(Knife_order);//步骤更新
							PromptNum_dis();//输入范围	
							PromptDis_flag=1; 
							ACServoAlarmExec_flag=0;
							break;
						case AUTO_PLUS_MODE:// F3++
							WorkMode=AUTO_MODE;//返回
							PaperCutEnb_signal=1;
							PressCircle_mode=0;
							F3_plus_dis(0);
							//------------返回第一刀
							ClrInput_function();//清零 输入框 
							CursorMov_dis(cursor_row, 0);//红色光标消失
							cursor_row=0;
							CursorMov_dis(cursor_row, 1);//红色光标显示
							Knife_order=1;//
							Size_1page_dis(Knife_order,0);//一页尺寸显示
							if(Knife_order<=Knife_sum)
								StepOrder_dis(Knife_order);//步骤更新
							PromptNum_dis();//输入范围	
							PromptDis_flag=1;
							ACServoAlarmExec_flag=0;
							break;
						case AUTO_MINUS_MODE:// F4--
							WorkMode=AUTO_MODE;//返回
							PaperCutEnb_signal=1;
							PressCircle_mode=0;
							F4_minus_dis(0);
							//------------返回第一刀
							ClrInput_function();//清零 输入框 
							CursorMov_dis(cursor_row, 0);//红色光标消失
							cursor_row=0;
							CursorMov_dis(cursor_row, 1);//红色光标显示
							Knife_order=1;//
							Size_1page_dis(Knife_order,0);//一页尺寸显示
							if(Knife_order<=Knife_sum)
								StepOrder_dis(Knife_order);//步骤更新
							PromptNum_dis();//输入范围	
							PromptDis_flag=1;	
							ACServoAlarmExec_flag=0;
							break;	
						}		
					}
				else  //计算器
					{
					
					}
				}
			else //运行中
			    {
				if(AutoCutStart_flag==0)
					{
					switch(MotorType)
						{
						case MOTOR_FREQ_5_SPD_RST:
						case MOTOR_FREQ_3_SPD:
						case MOTOR_FREQ_3_SPD_RST:
							ForceStop_flag=1;
							stop_time=0;
								break;
						case MOTOR_DC_SERVO:
						case MOTOR_DC670_SERVO:
						case MOTOR_DC670_SERVO_ZHU:
							DCServoStop();  //停止运行
							ServoPressStop_flag=0;
							DcServoGoTarget_flag=0;
							BellStart_flag=0;
							//************
							Run_flag=0;	
							InTargetPosit_flag=0;	//目标位置
							AutoPushRun_flag=0; //自动推纸 运行
							TargetSize=0;
							TargetSize_temp=0;
							BeforeKnife_offset_in=0;
							AutoRoute_flag=0;
								break;
						case MOTOR_AC_SERVO:
							ACServoStop();
							//************
							Run_flag=0;	
							InTargetPosit_flag=0;	//目标位置
							AutoPushRun_flag=0; //自动推纸 运行
							TargetSize=0;
							TargetSize_temp=0;
							BeforeKnife_offset_in=0;
							AutoRoute_flag=0;
								break;
						}
					// TargetSize=0;
					// TargetSize_temp=0;
					// BeforeKnife_offset_in=0;
					if(InputTouch_flag==0)
						ClrInput_function();//清零 输入框 
					}				
				}
			}
  	     break;
	case FOUR_KEY_CODE:	//编程按键******************进入  编程 主模式
		if(WorkStart_flag==1)
		   {
		   if(Run_flag==0)
			    {
				if(InputTouch_flag==0)
					{
					switch(WorkMode)
						{
						case PROG_LABEL_MODE: //标签
						case PROG_DIVIDE_MODE: //等分
						case PROG_PRO_MODE: //程序选择
							WorkMode=PROG_MODE;
							CurrentArea_recover2(MIDDLE_PAGE_X, MIDDLE_PAGE_Y,  M_PAGE_WIDE, M_PAGE_HIGH);
							PorgSet_sel=0;
							//------------返回第一刀
							ClrInput_function();//清零 输入框 
							CursorMov_dis(cursor_row, 0);//红色光标消失
							cursor_row=0;
							CursorMov_dis(cursor_row, 1);//红色光标显示
							Knife_order=1;//
							Size_1page_dis(Knife_order,0);//一页尺寸显示
							if(Knife_order<=Knife_sum)
								StepOrder_dis(Knife_order);//步骤更新
							PromptNum_dis();//输入范围
							PromptDis_flag=1;
							PaperCutEnb_signal=1;
							ACServoAlarmExec_flag=0;
							if(Sign_flag==1)//清除 加,减号
								{
								GLCD_SetWindow_Fill( SIZE_WINDOW_X, SIZE_WINDOW_Y, SIZE_WINDOW_X+120, SIZE_WINDOW_Y+30, 0xfffff, 0xffff);//尺寸输入框
								Sign_flag=0;
								}
							Program_dis(PROGRAM_X,PROGRAM_Y);   //±à3ì
								break;
						case AUTO_MODE://自动 主模式下************
						case SELF_CUT_MODE://自刀主画面下
						case TEACH_MODE://示教 模式
						case MANUAL_MODE:// 手动 主模式
							if(Sign_flag==1)
								{
								num_cou=0;
								GLCD_SetWindow_Fill( SIZE_WINDOW_X, SIZE_WINDOW_Y, SIZE_WINDOW_X+120, SIZE_WINDOW_Y+30, 0xfffff, 0xffff);//尺寸输入框
								Sign_flag=0;
								}
							WorkMode=PROG_MODE;
							ProgModePage_dis();// 回到 编程模式
							 
						case PROG_MODE: //编程 主模式
								//------------返回第一刀
							ClrInput_function();//清零 输入框 
							CursorMov_dis(cursor_row, 0);//红色光标消失
							cursor_row=0;
							CursorMov_dis(cursor_row, 1);//红色光标显示
							Knife_order=1;//
							Size_1page_dis(Knife_order,0);//一页尺寸显示
							if(Knife_order<=Knife_sum)
								StepOrder_dis(Knife_order);//步骤更新
							PromptNum_dis();//输入范围
							PromptDis_flag=1;
							PaperCutEnb_signal=1;
							ACServoAlarmExec_flag=0;
							if(Sign_flag==1)//清除 加,减号
								{
								GLCD_SetWindow_Fill( SIZE_WINDOW_X, SIZE_WINDOW_Y, SIZE_WINDOW_X+120, SIZE_WINDOW_Y+30, 0xfffff, 0xffff);//尺寸输入框
								Sign_flag=0;
								}
								break;
						}		
					}
				else  //计算器 弹出模式
					{
					
					}
					 
			    }
			else
			    {
				if(AutoCutStart_flag==0)
					{
					switch(MotorType)
						{
						case MOTOR_FREQ_5_SPD_RST:
						case MOTOR_FREQ_3_SPD:
						case MOTOR_FREQ_3_SPD_RST:
							ForceStop_flag=1;
							stop_time=0;
								break;
						case MOTOR_DC_SERVO:
						case MOTOR_DC670_SERVO:
						case MOTOR_DC670_SERVO_ZHU:
							DCServoStop();  //停止运行
							ServoPressStop_flag=0;
							DcServoGoTarget_flag=0;
							BellStart_flag=0;
							//************
							Run_flag=0;	
							InTargetPosit_flag=0;	//目标位置
							AutoPushRun_flag=0; //自动推纸 运行
							TargetSize=0;
							TargetSize_temp=0;
							BeforeKnife_offset_in=0;
							AutoRoute_flag=0;
								break;
						case MOTOR_AC_SERVO:
							ACServoStop();
							//************
							Run_flag=0;	
							InTargetPosit_flag=0;	//目标位置
							AutoPushRun_flag=0; //自动推纸 运行
							TargetSize=0;
							TargetSize_temp=0;
							BeforeKnife_offset_in=0;
							AutoRoute_flag=0;
								break;
						}
					//TargetSize=0;
					//TargetSize_temp=0;
					//BeforeKnife_offset_in=0;
					if(InputTouch_flag==0)
						ClrInput_function();//清零 输入框 		
					}
				}
		   }
		  break;
    case AUTO_KEY_CODE:       // F1**********************
		if(WorkStart_flag==1)
			{
			if(Run_flag==0)
			    {
				if(InputTouch_flag==0)
					{
					switch(WorkMode)
						{
						case PROG_MODE://编程  主画面下
							if(Sign_flag==1)//清除 加,减号
								{
								GLCD_SetWindow_Fill( SIZE_WINDOW_X, SIZE_WINDOW_Y, SIZE_WINDOW_X+120, SIZE_WINDOW_Y+30, 0xfffff, 0xffff);//尺寸输入框
								Sign_flag=0;
								}
							WorkMode=PROG_LABEL_MODE; //--------打开标签 页
							LabelPage_dis();  
							Total_size=0;//总长
							Label_size=0;//标签长
							Waste_size=0;//废边
							PorgSet_sel=0;
							PromptNum_dis();//输入范围
							PromptDis_flag=1;
							ACServoAlarmExec_flag=0;
							break;
						case TEACH_MODE://示教 模式
							if(Sign_flag==1)//清除 加,减号
								{
								GLCD_SetWindow_Fill( SIZE_WINDOW_X, SIZE_WINDOW_Y, SIZE_WINDOW_X+120, SIZE_WINDOW_Y+30, 0xfffff, 0xffff);//尺寸输入框
								Sign_flag=0;
								}
							WorkMode=TEACH_LABEL_MODE; //--------打开标签 页
							LabelPage_dis();  
							Total_size=0;//总长
							Label_size=0;//标签长
							Waste_size=0;//废边
							PorgSet_sel=0;
							PromptNum_dis();//输入范围
							PromptDis_flag=1;
							ACServoAlarmExec_flag=0;
							break;
						case PROG_LABEL_MODE://已 打开   标签********************
							WorkMode=PROG_MODE;//------------退出返回到编程主 画面 
							CurrentArea_recover2(MIDDLE_PAGE_X , MIDDLE_PAGE_Y,  M_PAGE_WIDE, M_PAGE_HIGH); 
							Program_dis(PROGRAM_X,PROGRAM_Y);   //编程
							PorgSet_sel=0;
							//if(Knife_order<MAIX_Knife-2) //至少最后3刀
							//  {
							if((Total_size*Label_size*Waste_size)!=0)//设定有效
								Label_function();          
							// }
							PromptNum_dis();//输入范围
							PromptDis_flag=1;
							//PaperCutEnb_signal=1;
							ACServoAlarmExec_flag=0;
							break;
						case TEACH_LABEL_MODE://已 打开   标签********************
							WorkMode=TEACH_MODE;//------------退出返回到示教主 画面 
							PaperCutEnb_signal=1;
							CurrentArea_recover2(MIDDLE_PAGE_X , MIDDLE_PAGE_Y,  M_PAGE_WIDE, M_PAGE_HIGH); 
							Teach_dis(TEACH_X,TEACH_Y);   //示教
							PorgSet_sel=0;
							//if(Knife_order<MAIX_Knife-2) //至少最后3刀
							//  {
							if((Total_size*Label_size*Waste_size)!=0)//设定有效
								Label_function();          
							// }
							PromptNum_dis();//输入范围
							PromptDis_flag=1;
							ACServoAlarmExec_flag=0;
							break;
						case PROG_DIVIDE_MODE: //已 进入 等分页*******************
							WorkMode=PROG_MODE;//--------------退出返回到编程主 画面 
							CurrentArea_recover2(MIDDLE_PAGE_X , MIDDLE_PAGE_Y,  M_PAGE_WIDE, M_PAGE_HIGH);
							Program_dis(PROGRAM_X,PROGRAM_Y);   //编程
							PorgSet_sel=0;
							if((Total_size*Divide_num)!=0)//设定等分有效
							  {
							  Divide_function();//
							  }
							PromptNum_dis();//输入范围
							PromptDis_flag=1;  
							//PaperCutEnb_signal=1;
							ACServoAlarmExec_flag=0;
							break;
						case TEACH_DIVIDE_MODE: //已 进入 等分页*******************
							WorkMode=TEACH_MODE;//--------------退出返回到示教主 画面 
							PaperCutEnb_signal=1;
							CurrentArea_recover2(MIDDLE_PAGE_X , MIDDLE_PAGE_Y,  M_PAGE_WIDE, M_PAGE_HIGH);
							Teach_dis(TEACH_X,TEACH_Y);   //示教
							PorgSet_sel=0;
							if((Total_size*Divide_num)!=0)//设定等分有效
							  {
							  Divide_function();//
							  }
							PromptNum_dis();//输入范围
							PromptDis_flag=1;  
							ACServoAlarmExec_flag=0;
							break;		
						case PROG_PRO_MODE:	//已在 程序选择画面**************	
							WorkMode=PROG_MODE;//--------------退出返回到编程主 画面 
							if((Pro_num>0)&&(Pro_num<=MAIX_PROG))// 有效  更新一个程序，并显示 
								{
								 cursor_temp=0;
								 ExportOnePro_dis(Pro_num);  //更新一个 程序 
								 Program_dis(PROGRAM_X,PROGRAM_Y);   //编程
								}
							PromptNum_dis();//输入范围
							PromptDis_flag=1;
							//PaperCutEnb_signal=1;
							ACServoAlarmExec_flag=0;
							break;
						case TEACH_PRO_MODE:	//已在 程序选择画面**************	
							WorkMode=TEACH_MODE;//--------------退出返回到示教主 画面 
							PaperCutEnb_signal=1;
							if((Pro_num>0)&&(Pro_num<=MAIX_PROG))// 有效  更新一个程序，并显示 
								{
								 cursor_temp=0;
								 ExportOnePro_dis(Pro_num);  //更新一个 程序 
								 Teach_dis(TEACH_X,TEACH_Y);   //示教
								}
							PromptNum_dis();//输入范围
							PromptDis_flag=1;	
							ACServoAlarmExec_flag=0;
							break;		
						case AUTO_MODE://自动 主模式下	
							WorkMode=AUTO_RULER_MODE; //基准
							RulerPage_dis(); //基准 画面
							PromptNum_dis();//输入范围
							PromptDis_flag=1;
							ACServoAlarmExec_flag=0;
							break;
						case SELF_CUT_MODE://自刀主画面下	
							WorkMode=SELF_RULER_MODE; //基准
							RulerPage_dis(); //基准 画面
							PromptNum_dis();//输入范围
							PromptDis_flag=1;
							ACServoAlarmExec_flag=0;
							break;
						case MANUAL_MODE:  // 手动模式
							if(Sign_flag==1)
								{
								num_cou=0;
								GLCD_SetWindow_Fill( SIZE_WINDOW_X, SIZE_WINDOW_Y, SIZE_WINDOW_X+120, SIZE_WINDOW_Y+30, 0xfffff, 0xffff);//尺寸输入框
								Sign_flag=0;
								}
							WorkMode=MANUAL_TOOLS_MODE;//进入  手动----参数模式*****************
							ToolsPage_dis(); //参数画面
							Para_sel=0;
							PromptDis_flag=0;
							ACServoAlarmExec_flag=0;							
							break;
						case MANUAL_PULSE_MODE://手动 脉冲设定模式
							Pulse_degree=Para_sel;
							Save_degree();
							WorkMode=MANUAL_MODE;//返回    ---------手动 主模式
							Para_sel=0;
							CurrentArea_recover2(MIDDLE_PAGE_X , MIDDLE_PAGE_Y,  M_PAGE_WIDE, M_PAGE_HIGH);
							Manual_dis(MANUAL_X,MANUAL_Y);//手动
							PromptNum_dis();//输入范围
							PromptDis_flag=1;
							ACServoAlarmExec_flag=0;
							break;
						}
					}
				else  //计算器 弹出模式
					{
					
					}
				
				}
			else  //运行中
			    {
				if(AutoCutStart_flag==0)
					{
					switch(MotorType)
						{
						case MOTOR_FREQ_5_SPD_RST:
						case MOTOR_FREQ_3_SPD:
						case MOTOR_FREQ_3_SPD_RST:
							ForceStop_flag=1;
							stop_time=0;
								break;
						case MOTOR_DC_SERVO:
						case MOTOR_DC670_SERVO:
						case MOTOR_DC670_SERVO_ZHU:
							DCServoStop();  //停止运行
							ServoPressStop_flag=0;
							DcServoGoTarget_flag=0;
							BellStart_flag=0;
							//************
							Run_flag=0;	
							InTargetPosit_flag=0;	//目标位置
							AutoPushRun_flag=0; //自动推纸 运行
							TargetSize=0;
							TargetSize_temp=0;
							BeforeKnife_offset_in=0;
							AutoRoute_flag=0;
								break;
						case MOTOR_AC_SERVO:
							ACServoStop();
							//************
							Run_flag=0;	
							InTargetPosit_flag=0;	//目标位置
							AutoPushRun_flag=0; //自动推纸 运行
							TargetSize=0;
							TargetSize_temp=0;
							BeforeKnife_offset_in=0;
							AutoRoute_flag=0;
								break;
						}
					// TargetSize=0;
					// TargetSize_temp=0;
					// BeforeKnife_offset_in=0;
					}
				}	
			if(InputTouch_flag==0)	
				ClrInput_function();//清零 输入框  
			}
		else//--------------------------触摸校准
			{
			switch(MotorType)
				{
				case MOTOR_FREQ_5_SPD_RST:
				case MOTOR_FREQ_3_SPD:
				case MOTOR_FREQ_3_SPD_RST:
						if((StartCheck_mode<2)||(StartCheck_mode==4))
							CheckModeOK_flag=1;
						else
							CheckModeOK_flag=0;
						break;
				case MOTOR_DC_SERVO:
				case MOTOR_DC670_SERVO:
				case MOTOR_DC670_SERVO_ZHU:
						if(StartCheck_mode<2)
							CheckModeOK_flag=1;
						else
							CheckModeOK_flag=0;
						break;
				case MOTOR_AC_SERVO:
						if(StartCheck_mode<5)
							CheckModeOK_flag=1;
						else
							CheckModeOK_flag=0;
						break;		
				default:
							CheckModeOK_flag=0;
						break;
				}	
			if(CheckModeOK_flag==1)
				{
				if(Board_TestMod==0) //非测试 模式-------
					{
					Board_TestMod=TEST_TOUCH; //触摸校准 模式使能
					GLCD_Buffer_Fill(0xffff);
					x=200,y=150,back_color=WHITE_COLOR;
					switch(Language)
						{
						case CHN_HAN:
							Printf24("请触摸红色'十'字光标所在位置!",x,y,0,1,back_color);
								break;
						case ENGLISH:	
							Printf24("Please touch the red 'cross'!",x,y,0,1,back_color);
								break;
						}
					TouchCalcu_mode=0;
					Draw_cross(TOUCH_X1,TOUCH_Y1,RED_COLOR);
					}
				else if(Board_TestMod==TEST_TOUCH)
					{
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
					ServoDisconnect_flag=0;
					}
				}
			}
  	     break;
    case READ_KEY_CODE:       // F2*******************退出
		if(WorkStart_flag==1)
		   {
			if(Run_flag==0)
			    {
				if(InputTouch_flag==0)
					{
					switch(WorkMode)
						{
						case PROG_MODE://编程画面下
							if(Sign_flag==1)//清除 加,减号
								{
								GLCD_SetWindow_Fill( SIZE_WINDOW_X, SIZE_WINDOW_Y, SIZE_WINDOW_X+120, SIZE_WINDOW_Y+30, 0xfffff, 0xffff);//尺寸输入框
								Sign_flag=0;
								}
							WorkMode=PROG_DIVIDE_MODE;//进入---------等分模式  
							DividePage_dis();  
							Total_size=0;//总长
							Divide_num=0;//等分数
							PorgSet_sel=0;
							PromptNum_dis();//输入范围
							PromptDis_flag=1;
							ACServoAlarmExec_flag=0;
							break;
						case TEACH_MODE://示教画面下
							if(Sign_flag==1)//清除 加,减号
								{
								GLCD_SetWindow_Fill( SIZE_WINDOW_X, SIZE_WINDOW_Y, SIZE_WINDOW_X+120, SIZE_WINDOW_Y+30, 0xfffff, 0xffff);//尺寸输入框
								Sign_flag=0;
								}
							WorkMode=TEACH_DIVIDE_MODE;//进入---------等分模式  
							DividePage_dis();  
							Total_size=0;//总长
							Divide_num=0;//等分数
							PorgSet_sel=0;
							PromptNum_dis();//输入范围
							PromptDis_flag=1;
							ACServoAlarmExec_flag=0;
							break;		
						case PROG_LABEL_MODE://已在 标签画面		
						case PROG_DIVIDE_MODE://已在 等分画面 		
						case PROG_PRO_MODE://已在  程序选择画面
							cursor_temp=0;		
							WorkMode=PROG_MODE;//------------------退出返回到编程主 画面
							PorgSet_sel=0;
							CurrentArea_recover2(MIDDLE_PAGE_X , MIDDLE_PAGE_Y,  M_PAGE_WIDE, M_PAGE_HIGH);
							Program_dis(PROGRAM_X,PROGRAM_Y);   //编程
							PromptNum_dis();//输入范围
							PromptDis_flag=1;
							//PaperCutEnb_signal=1;
							ACServoAlarmExec_flag=0;
							break;
						case TEACH_LABEL_MODE://已在 标签画面		
						case TEACH_DIVIDE_MODE://已在 等分画面 		
						case TEACH_PRO_MODE://已在  程序选择画面
							cursor_temp=0;		
							WorkMode=TEACH_MODE;//------------------退出返回到示教主 画面
							PaperCutEnb_signal=1;
							PorgSet_sel=0;
							CurrentArea_recover2(MIDDLE_PAGE_X , MIDDLE_PAGE_Y,  M_PAGE_WIDE, M_PAGE_HIGH);
							Teach_dis(TEACH_X,TEACH_Y);   //示教
							PromptNum_dis();//输入范围
							PromptDis_flag=1;
							ACServoAlarmExec_flag=0;
							break;		
						//*********************************************	
						case AUTO_MODE://自动 主模式下		
							WorkMode=AUTO_TOOLS_MODE;//进入  自动 ----参数模式*****************
							ToolsPage_dis(); //参数画面
							Para_sel=0;
							PromptDis_flag=0;
							ACServoAlarmExec_flag=0;
							break;
						case AUTO_RULER_MODE:	//基准模式		
						case AUTO_TOOLS_MODE:// 已在  自动 -------参数模式
							WorkMode=AUTO_MODE;//返回    ---------自动 主模式
							Para_sel=0;
							PaperCutEnb_signal=1;
							CurrentArea_recover2(MIDDLE_PAGE_X , MIDDLE_PAGE_Y,  M_PAGE_WIDE, M_PAGE_HIGH);
							Auto_dis(AUTO_X, AUTO_Y); //自动
							PromptNum_dis();//输入范围
							PromptDis_flag=1;
							ACServoAlarmExec_flag=0;
							break;
						case AUTO_PLUS_MODE:// F3++
							WorkMode=AUTO_MODE;//返回
							PaperCutEnb_signal=1;
							F3_plus_dis(0);
							PromptNum_dis();//输入范围
							PromptDis_flag=1;
							ACServoAlarmExec_flag=0;
							break;
						case AUTO_MINUS_MODE:// F4--
							WorkMode=AUTO_MODE;//返回
							PaperCutEnb_signal=1;
							PressCircle_mode=0;
							F4_minus_dis(0);
							PromptNum_dis();//输入范围
							PromptDis_flag=1;
							ACServoAlarmExec_flag=0;
							break;
						//****************自刀
						case SELF_CUT_MODE://自刀 主模式下		
							WorkMode=SELF_TOOLS_MODE;//进入 自刀  ----参数模式*****************
							ToolsPage_dis(); //参数画面
							Para_sel=0;
							PromptDis_flag=0;
							ACServoAlarmExec_flag=0;
							break;
						case SELF_RULER_MODE:	//基准模式		
						case SELF_TOOLS_MODE:// 已在 自刀  -------参数模式
							WorkMode=SELF_CUT_MODE;//返回    ---------自刀 主模式
							Para_sel=0;
							PaperCutEnb_signal=1;
							CurrentArea_recover2(MIDDLE_PAGE_X , MIDDLE_PAGE_Y,  M_PAGE_WIDE, M_PAGE_HIGH);
							AutoKnife_dis(SELF_KNIFE_X, SELF_KNIFE_Y); //自刀
							PromptNum_dis();//输入范围
							PromptDis_flag=1;
							ACServoAlarmExec_flag=0;
							break;
						case SELF_PLUS_MODE:// F3++
							WorkMode=SELF_CUT_MODE;//返回
							PaperCutEnb_signal=1;
							F3_plus_dis(0);
							PromptNum_dis();//输入范围
							PromptDis_flag=1;
							ACServoAlarmExec_flag=0;
							break;
						case SELF_MINUS_MODE:// F4--
							WorkMode=SELF_CUT_MODE;//返回
							PaperCutEnb_signal=1;
							F4_minus_dis(0);
							PromptNum_dis();//输入范围
							PromptDis_flag=1;
							ACServoAlarmExec_flag=0;
							break;	
						//*******************************
						case MANUAL_MODE: //手动
							if(Sign_flag==1)
								{
								num_cou=0;
								GLCD_SetWindow_Fill( SIZE_WINDOW_X, SIZE_WINDOW_Y, SIZE_WINDOW_X+120, SIZE_WINDOW_Y+30, 0xfffff, 0xffff);//尺寸输入框
								Sign_flag=0;
								}
							WorkMode=MANUAL_RULER_MODE; //基准
							RulerPage_dis(); //基准 画面
							PromptNum_dis();//输入范围
							PromptDis_flag=1;
							ACServoAlarmExec_flag=0;
							break;
						case MANUAL_TOOLS_MODE:// 手动 参数模式
						case MANUAL_RULER_MODE://手动 基准模式
						case MANUAL_CLOCK_MODE://手动 时钟模式
						case MANUAL_PULSE_MODE://手动 脉冲设定模式
						case MANUAL_PASS_MODE://手动 密码模式
						case MANUAL_SERVO_C_MODE:   //手动直流伺服 C 参数 
							WorkMode=MANUAL_MODE;//返回    ---------手动 主模式
							Para_sel=0;
							CurrentArea_recover2(MIDDLE_PAGE_X , MIDDLE_PAGE_Y,  M_PAGE_WIDE, M_PAGE_HIGH);
							Manual_dis(MANUAL_X,MANUAL_Y);//手动
							PromptNum_dis();//输入范围
							PromptDis_flag=1;
							ACServoAlarmExec_flag=0;
							break;
						}
					}
				else  //计算器 弹出模式
					{
					CalcuInClear_exec();     //清除 计算器
					switch(WorkMode)
						{
						case AUTO_TOOLS_MODE:
						case MANUAL_TOOLS_MODE:
						case SELF_TOOLS_MODE:
							back_color=0xef9f;
							x=PARA_START_X1+PARA_COL_WIDE,y=PARA_START_Y,gap=30;
							if(PramSel_Page<1)	//page 1
								{
							//if(Para_sel<7)
							//	{
								ParameterPage_dis(7, 0);
								if((MotorType>=MOTOR_DC_SERVO)&&(MotorType<=MOTOR_DC670_SERVO_ZHU))
									{
									ParameterPage_dis(8, 0);
									ParameterPage_dis(9, 0);
									}
								else if(MotorType==MOTOR_AC_SERVO)	
									{
									ParameterPage_dis(8, 0);
									}
								ParameterPage_dis(Para_sel, 1);
							//	}
							switch(Language)
								{
								case CHN_HAN:
									Printf24("压纸停机:   ",x,y,BLACK_COLOR,1,back_color);y+=gap;
									if((MotorType>=MOTOR_DC_SERVO)&&(MotorType<=MOTOR_DC670_SERVO_ZHU))
										{
										Printf24("最大速度:   ",x,y,BLACK_COLOR,1,back_color);y+=gap;
										Printf24("点动速度:   ",x,y,BLACK_COLOR,1,back_color);
										}
									else if(MotorType==MOTOR_AC_SERVO)
										{
										Printf24("运行速度:   ",x,y,BLACK_COLOR,1,back_color);y+=gap;
										}
										break;
								case ENGLISH:
									Printf24("Press-Stop:",x,y,BLACK_COLOR,1,back_color);y+=gap;
									if((MotorType>=MOTOR_DC_SERVO)&&(MotorType<=MOTOR_DC670_SERVO_ZHU))
										{
										Printf24("Max-speed:",x,y,BLACK_COLOR,1,back_color);y+=gap;
										Printf24("Jog-speed:",x,y,BLACK_COLOR,1,back_color);
										}
									else if(MotorType==MOTOR_AC_SERVO)
										{
										Printf24("Run-speed:",x,y,BLACK_COLOR,1,back_color);y+=gap;
										}
										break;
								}	
								}
							else	//page 2
								{
									
								}
							break;
						
						case  PROG_MODE://编程画面下
						case AUTO_MODE://自动主画面下
						case AUTO_PLUS_MODE://自动F3++
						case AUTO_MINUS_MODE://自动F4--
						case TEACH_MODE://示教 模式
						case AUTO_TO_SELF_MODE:   //自动-->自刀过度 模式
						case SELF_CUT_MODE:  //自刀主 模式
						case SELF_PLUS_MODE: //自刀 F3++
						case SELF_MINUS_MODE://自刀 F4--
							if(Knife_order>Knife_sum)
								 K_temp=Knife_order-1;
							 else
								 K_temp=Knife_order;
							ProgressBar_dis(Knife_sum,K_temp);  //进度条 显示
							KnifeUp_flag=0;
							KnifeDown_flag=0;
							PressUp_flag=0;
							PressDown_flag=0;
							A_Down_flag=0;
							B_Down_flag=0;
							A_Up_flag=0;
							B_Up_flag=0;
							IR_Up_flag=0;
							IR_Down_flag=0;
							//--------------更新显示刀——推纸标志
							// CursorMov_dis(cursor_row, 0);//红色光标消失
							// cursor_row=0;
							// CursorMov_dis(cursor_row, 1);//红色光标显示
							//Knife_order=1;//
							Size_1page_dis(Knife_order-cursor_row,0);//一页尺寸显示
							break;	
						}
					}
				}
			else  //运行中
			    {
				if(InputTouch_flag==0)
					{
					if(AutoCutStart_flag==0)
						{
						switch(MotorType)
							{
							case MOTOR_FREQ_5_SPD_RST:
							case MOTOR_FREQ_3_SPD:
							case MOTOR_FREQ_3_SPD_RST:
								ForceStop_flag=1;
								stop_time=0;
									break;
							case MOTOR_DC_SERVO:
							case MOTOR_DC670_SERVO:
							case MOTOR_DC670_SERVO_ZHU:
								DCServoStop();  //停止运行
								ServoPressStop_flag=0;
								DcServoGoTarget_flag=0;
								BellStart_flag=0;
								//************
								Run_flag=0;	
								InTargetPosit_flag=0;	//目标位置
								AutoPushRun_flag=0; //自动推纸 运行
								TargetSize=0;
								TargetSize_temp=0;
								BeforeKnife_offset_in=0;
								AutoRoute_flag=0;
									break;
							case MOTOR_AC_SERVO:
								ACServoStop();
								//************
								Run_flag=0;	
								InTargetPosit_flag=0;	//目标位置
								AutoPushRun_flag=0; //自动推纸 运行
								TargetSize=0;
								TargetSize_temp=0;
								BeforeKnife_offset_in=0;
								AutoRoute_flag=0;
									break;
							}	
						// TargetSize=0;
						// TargetSize_temp=0;
						// BeforeKnife_offset_in=0;
						}
					}
				else
					CalcuInClear_exec();     //清除 计算器
				}		
			ClrInput_function();//清零 输入框
		   }
		else  
		   {
		   switch(MotorType)
				{
					case MOTOR_FREQ_5_SPD_RST:
					case MOTOR_FREQ_3_SPD:
					case MOTOR_FREQ_3_SPD_RST:
						if((StartCheck_mode<2)||(StartCheck_mode==4))
							CheckModeOK_flag=1;	
						else
							CheckModeOK_flag=0;
						break;
					case MOTOR_DC_SERVO:
					case MOTOR_DC670_SERVO:
					case MOTOR_DC670_SERVO_ZHU:
						if(StartCheck_mode<2)
							CheckModeOK_flag=1;	
						else
							CheckModeOK_flag=0;
						break;
					case MOTOR_AC_SERVO:
						if(StartCheck_mode<5)
							CheckModeOK_flag=1;	
						else
							CheckModeOK_flag=0;
						break;	
					default:
							CheckModeOK_flag=0;
						break;
				}	
			if(CheckModeOK_flag==1)
				{
				if(Board_TestMod==0)       //-------------帮助模式---
					{
					Manual_page=0;
					Comment_dis_page(Manual_page);//注释1
					Board_TestMod=TEST_HELP;
					}
				else if(Board_TestMod==TEST_HELP)
					{
					Bmp_Decode((Int32U)START_PIC_sdram, 0, 0, (pInt16U)SDRAM0_BASE_ADDR); //显示开机画面
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
					
					Board_TestMod=0;Manual_page=0;
					ServoDisconnect_flag=0;
					}
				}
		   }
  	     break;
    case RETURN_KEY_CODE:      //F3************选择 程序号
		if(WorkStart_flag==1)
		   {
			if(Run_flag==0)
			    {
				if(InputTouch_flag==0)
					{
					switch(WorkMode)
						{
						case PROG_MODE:
							if(Sign_flag==1)//清除 加,减号
								{
								GLCD_SetWindow_Fill( SIZE_WINDOW_X, SIZE_WINDOW_Y, SIZE_WINDOW_X+120, SIZE_WINDOW_Y+30, 0xfffff, 0xffff);//尺寸输入框
								Sign_flag=0;
								}
							WorkMode=PROG_PRO_MODE;//进入 -----------选择程序模式
							SelProgPage_dis(); //程序 选择 画面显示
							PromptDis_flag=0;
							Pro_num=1;
							cursor_temp=0;
							Prog_1page_dis(Pro_num, 0);//===程序---数据显示
							TableDis_startcol=RIGHT_ARROW_X;
							CursorMov_dis(cursor_temp,1);//红色光标
							//ClrInput_function();//清零 输入框
							ACServoAlarmExec_flag=0;
							break;
						case TEACH_MODE:
							if(Sign_flag==1)//清除 加,减号
								{
								GLCD_SetWindow_Fill( SIZE_WINDOW_X, SIZE_WINDOW_Y, SIZE_WINDOW_X+120, SIZE_WINDOW_Y+30, 0xfffff, 0xffff);//尺寸输入框
								Sign_flag=0;
								}
							WorkMode=TEACH_PRO_MODE;//进入 -----------选择程序模式
							SelProgPage_dis(); //程序 选择 画面显示
							PromptDis_flag=0;
							Pro_num=1;
							cursor_temp=0;
							Prog_1page_dis(Pro_num, 0);//===程序---数据显示
							TableDis_startcol=RIGHT_ARROW_X;
							CursorMov_dis(cursor_temp,1);//红色光标
							//ClrInput_function();//清零 输入框
							ACServoAlarmExec_flag=0;
							break;		
						case AUTO_MODE://自动 主模式下************
							//ClrInput_function();//清零 输入框
							WorkMode=AUTO_PLUS_MODE;  //F3++
							F3_plus_dis(1);//  ++
							break;
						case AUTO_PLUS_MODE:  //F3++		
							WorkMode=AUTO_MODE;//返回
							PaperCutEnb_signal=1;
							PressCircle_mode=0;
							F3_plus_dis(0);
							break;
						case SELF_CUT_MODE://自刀 主模式下************
							WorkMode=SELF_PLUS_MODE;  //F3++
							F3_plus_dis(1);//  ++
							break;
						case SELF_PLUS_MODE:  //F3++		
							WorkMode=SELF_CUT_MODE;//返回
							PaperCutEnb_signal=1;
							F3_plus_dis(0);
							break;		
						case MANUAL_MODE: //手动-----------------------
							if(Sign_flag==1)
								{
								num_cou=0;
								GLCD_SetWindow_Fill( SIZE_WINDOW_X, SIZE_WINDOW_Y, SIZE_WINDOW_X+120, SIZE_WINDOW_Y+30, 0xfffff, 0xffff);//尺寸输入框
								Sign_flag=0;
								}
							WorkMode=MANUAL_CLOCK_MODE; // 时钟 模式
							Para_sel=0;PromptDis_flag=0;
							ClockPage_dis();
							Year_before=Year,Month_before=Month,Day_before=Dom; //当前时间 暂存
							ACServoAlarmExec_flag=0;
							break;
						}
					}
				else  //计算器 弹出模式
					{
					
					}
						
			    }
			else  //运行中
			    {
				if(AutoCutStart_flag==0)
					{
					switch(MotorType)
						{
						case MOTOR_FREQ_5_SPD_RST:
						case MOTOR_FREQ_3_SPD:
						case MOTOR_FREQ_3_SPD_RST:
							ForceStop_flag=1;
							stop_time=0;
								break;
						case MOTOR_DC_SERVO:
						case MOTOR_DC670_SERVO:
						case MOTOR_DC670_SERVO_ZHU:
							DCServoStop();  //停止运行
							ServoPressStop_flag=0;
							DcServoGoTarget_flag=0;
							BellStart_flag=0;
							//************
							Run_flag=0;	
							InTargetPosit_flag=0;	//目标位置
							AutoPushRun_flag=0; //自动推纸 运行
							TargetSize=0;
							TargetSize_temp=0;
							BeforeKnife_offset_in=0;
							AutoRoute_flag=0;
								break;
						case MOTOR_AC_SERVO:
								ACServoStop();
							//************
							Run_flag=0;	
							InTargetPosit_flag=0;	//目标位置
							AutoPushRun_flag=0; //自动推纸 运行
							TargetSize=0;
							TargetSize_temp=0;
							BeforeKnife_offset_in=0;
							AutoRoute_flag=0;
									break;
						}
					// TargetSize=0;
					// TargetSize_temp=0;
					// BeforeKnife_offset_in=0;
					}
				}
			if(InputTouch_flag==0)
				ClrInput_function();//清零 输入框
		   }
  	     break;    
	case MANUAL_KEY_CODE:   // F4************** 推纸/刀  标志
		if(WorkStart_flag==1)
		   {
		    if(Run_flag==0)
			    {
				if(InputTouch_flag==0)
					{
					switch(WorkMode)
						{
						case PROG_MODE://编程 主画面下
						case TEACH_MODE://示教 主画面下
							if(Sign_flag==1)//清除 加,减号
								{
								GLCD_SetWindow_Fill( SIZE_WINDOW_X, SIZE_WINDOW_Y, SIZE_WINDOW_X+120, SIZE_WINDOW_Y+30, 0xfffff, 0xffff);//尺寸输入框
								Sign_flag=0;
								}
								
							if(num_cou>0)
								{
								if(CheckInputNums()==1)// 输入 有效
									{
									//----保存数据----------------
									if(Knife_order>Knife_sum)//更新步骤 总刀数
										{
										Knife_sum=Knife_order;
										}
									pKnife_data=(pInt8U)&OneKnife_data;
									GetOneKnife_datas(Pro_data.pro_num, Knife_order, pKnife_data);//
									OneKnife_data.size=InputSize;  //尺寸修改
									if(OneKnife_data.k_flag!=PUSH_FLAG) //
										{
										OneKnife_data.k_flag=PUSH_FLAG;//  设定 标志
										}
									else
										{
										OneKnife_data.k_flag=0;// 清除 标志
										}
									SaveOneKnife_datas(Pro_data.pro_num, Knife_order , pKnife_data);//保存一刀数据
									//-----显示
									PushFlag_dis(cursor_row,OneKnife_data.k_flag); //显示----
									KnifeSize_dis(cursor_row,InputSize,0);//尺寸
									StepNum_dis(Knife_sum,Knife_order);//步骤更新
									if(Knife_order<MAIX_Knife)            //刀序递增
										{
										Knife_order++;
										if(cursor_row<(PAGE_KNIFE-1))
											{
											CursorMov_dis(cursor_row, 0);//红色光标消失
											OneKnifeDataSel_dis(Knife_order-1, cursor_row,0);  //一刀数据 高亮显示
											cursor_row++;
											CursorMov_dis(cursor_row, 1);//红色光标下移显示
											OneKnifeDataSel_dis(Knife_order, cursor_row,RED_COLOR);  //一刀数据 高亮显示
											}
										else   //页底
											{
											Size_1page_dis(Knife_order-(PAGE_KNIFE-1),0);//一页尺寸显示
											}	
										}
									else
										{
										OneKnifeDataSel_dis(Knife_order, cursor_row,RED_COLOR);  //一刀数据 高亮显示
										}
									}
								ClrInput_function();//清零 输入框
								}
							else  //已 输入数据
								{
								pKnife_data=(pInt8U)&OneKnife_data;
								GetOneKnife_datas(Pro_data.pro_num, Knife_order, pKnife_data);//
								if(OneKnife_data.size>0)
									{
									if(OneKnife_data.k_flag!=PUSH_FLAG) //
										{
										OneKnife_data.k_flag=PUSH_FLAG;//  设定 标志
										}
									else
										{
										OneKnife_data.k_flag=0;// 清除 标志
										}
									PushFlag_dis(cursor_row,OneKnife_data.k_flag); //显示----
									SaveOneKnife_datas(Pro_data.pro_num, Knife_order , pKnife_data);//保存一刀数据
									PromptNum_dis();//输入范围
									PromptDis_flag=1;
									}
								else
									{
						//GLCD_SetWindow_Fill( REMIND_WINDOW_X, REMIND_WINDOW_Y, REMIND_WINDOW_X+360, REMIND_WINDOW_Y+30, 0xfffff, 0xffff);//提示框
						//Printf24("输入数值范围    到",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,RED_COLOR,0,0xffff);
									}
								}	
							break;
						case AUTO_MODE://自动 主模式下************
							ClrInput_function();//清零 输入框
							WorkMode=AUTO_MINUS_MODE;// F4--
							F4_minus_dis(1);//--
							break;
						case AUTO_MINUS_MODE:// F4--		 
							WorkMode=AUTO_MODE;//返回
							PaperCutEnb_signal=1;
							PressCircle_mode=0;
							F4_minus_dis(0);
							ClrInput_function();//清零 输入框
							break;
						case SELF_CUT_MODE://自刀 主模式下************
							ClrInput_function();//清零 输入框
							WorkMode=SELF_MINUS_MODE;// F4--
							F4_minus_dis(1);//--
							break;
						case SELF_MINUS_MODE:// F4--		 
							WorkMode=SELF_CUT_MODE;//返回
							PaperCutEnb_signal=1;
							F4_minus_dis(0);
							ClrInput_function();//清零 输入框
							break;
						case MANUAL_MODE: //电子手轮 开关
							if(MotorType==MOTOR_AC_SERVO)
								{
								ElectricWheelOn_flag=!ElectricWheelOn_flag;
								SaveElectricWheelSwitch();//电子手轮
								ElectricalWheel_dis();  //电子手轮  开关状态
								}
							
							break;
						}		

					}
				else  //计算器 弹出模式
					{
					
					}
			    }
			else  //运行中
			    {
				if(AutoCutStart_flag==0)
					{
					switch(MotorType)
						{
						case MOTOR_FREQ_5_SPD_RST:
						case MOTOR_FREQ_3_SPD:
						case MOTOR_FREQ_3_SPD_RST:
							ForceStop_flag=1;
							stop_time=0;
								break;
						case MOTOR_DC_SERVO:
						case MOTOR_DC670_SERVO:
						case MOTOR_DC670_SERVO_ZHU:
							DCServoStop();  //停止运行
							ServoPressStop_flag=0;
							DcServoGoTarget_flag=0;
							BellStart_flag=0;
							//************
							Run_flag=0;	
							InTargetPosit_flag=0;	//目标位置
							AutoPushRun_flag=0; //自动推纸 运行
							TargetSize=0;
							TargetSize_temp=0;
							BeforeKnife_offset_in=0;
							AutoRoute_flag=0;
								break;
						case MOTOR_AC_SERVO:
								ACServoStop();
							//************
							Run_flag=0;	
							InTargetPosit_flag=0;	//目标位置
							AutoPushRun_flag=0; //自动推纸 运行
							TargetSize=0;
							TargetSize_temp=0;
							BeforeKnife_offset_in=0;
							AutoRoute_flag=0;
									break;
						}
					// TargetSize=0;
					// TargetSize_temp=0;
					//BeforeKnife_offset_in=0;
					if(InputTouch_flag==0)
						ClrInput_function();//清零 输入框	
					}		
				}
		   }
  	     break;  
    case PROG_KEY_CODE:     // 0  **************
			NumKey_exec(0);
			break;
    case NINE_KEY_CODE:		// 1**************
			NumKey_exec(1);
			break;
	case MOVE_KEY_CODE:     // 2**************
			NumKey_exec(2);
			break;
	case DELETE_KEY_CODE:      //3*************
			NumKey_exec(3);
			break;
	case EIGHT_KEY_CODE:		//4***********
			NumKey_exec(4);
			break;
	case NO_KEY_CODE:      // 5******************
			NumKey_exec(5);
			break;   
	case INSERT_KEY_CODE:      //6****************
			NumKey_exec(6);
			break;
	case SEVEN_KEY_CODE:	//7 **************
			NumKey_exec(7);
			break;         
    case YES_KEY_CODE:    // 8*************          
			NumKey_exec(8);
			break;
	case SUB_KEY_CODE:   // 9************
			NumKey_exec(9);
			break;
    case ADD_KEY_CODE:   //  点“.”***************
			NumKey_exec('.');
			 break;   
	case SIX_KEY_CODE:		// clear 功能C********
        if(WorkStart_flag==1)
				{
				if(Run_flag==0)
					{
					Dot_flag=0;
					if(num_cou>0)
						ClrInput_function();//清零 输入框
					if(InputTouch_flag==0)
						{
						if(WorkMode==AUTO_TO_SELF_MODE)  //自动-->自刀过度 模式
							{
							if(ReEnterAutoKnife_dis==0) //非重入 提示  显示
								{
								WorkMode=AUTO_MODE;//返回 自动主
								PaperCutEnb_signal=1;
								PressCircle_mode=0;
								CurrentArea_recover2(SELF_PROMP_X,SELF_PROMP_Y,SELF_PROMP_X+300,SELF_PROMP_Y+120);
								}
							else   //再次  进入 第一刀
								{
								if(InputTouch_flag==1)  //	  触摸 下
									CalcuInClear_exec();     //清除 计算器
								WorkMode=SELF_CUT_MODE;  //进入   ----------自刀主 模式
								CurrentArea_recover2(SELF_PROMP_X,SELF_PROMP_Y,SELF_PROMP_X+300,SELF_PROMP_Y+120);
								AutoKnife_dis(SELF_KNIFE_X,SELF_KNIFE_Y);//自刀
								//------------返回第一刀
								ClrInput_function();//清零 输入框 
								CursorMov_dis(cursor_row, 0);//红色光标消失
								cursor_row=0;
								CursorMov_dis(cursor_row, 1);//红色光标显示
								Knife_order=1;//
								Size_1page_dis(Knife_order,0);//一页尺寸显示
								if(Knife_order<=Knife_sum)
									StepOrder_dis(Knife_order);//步骤更新 
									
								LastAutoKnife_order=1;
								ReEnterAutoKnife_dis=0;
								}
							}
						}
					else
						{
						if(CalcNoNumInput_flag==0)//  计算器已经输入 数据
							{
							ClearCalculatorInput(); //清零计算器 输入
							}
						}
					}
				else
					{
									
					}
				} 
		else
				{
				switch(MotorType)
					{
					case MOTOR_FREQ_5_SPD_RST:
					case MOTOR_FREQ_3_SPD:
					case MOTOR_FREQ_3_SPD_RST:
					case MOTOR_AC_SERVO:
		//			case MOTOR_AC_SERVO670:
						if(StartCheck_mode==1)  //推纸器 复位启动
							{
							CurrentArea_recover3(PUSH_RESET_PROMPT_X1, PUSH_RESET_PROMPT_Y1, PUSH_RESET_PROMPT_WIDE, PUSH_RESET_PROMPT_HIGH);
							StartCheck_mode=3;//2;
							PusherResetTime=0;
							}
						else if(StartCheck_mode==4)
							{
							 if(PassCheckDis_flag==1)//清零
								{
								GLCD_SetWindow_Fill(PASSCODE_INPUT_X, PASSCODE_INPUT_Y, PASSCODE_INPUT_X+100, PASSCODE_INPUT_Y+30, 0xfffff, 0xffff);
								for(num_cou=0;num_cou<8;num_cou++)
									{
									Size_temp[num_cou++]=0;
									}
								num_cou=0;
								}
							}
							break;
					case MOTOR_DC_SERVO:
							break;
					}	
				}
  	     break;   
	case NEXTKNIFE_KEY_CODE:   //前进按键***************
        if(WorkStart_flag==1)  
			{
			if(Run_flag==0)
				{
				switch(WorkMode)
					{
					case PROG_MODE://编程画面下
					case TEACH_MODE://示教画面下
					case AUTO_MODE://自动主画面下
					case SELF_CUT_MODE://自刀主画面下
					case MANUAL_MODE:   //手动
						if(Sign_flag==1)
							{
							num_cou=0;
							GLCD_SetWindow_Fill( SIZE_WINDOW_X, SIZE_WINDOW_Y, SIZE_WINDOW_X+120, SIZE_WINDOW_Y+30, 0xfffff, 0xffff);//尺寸输入框
							Sign_flag=0;
							}
                                                qianjinflag=1;
						GoFrontEn_flag=1;
						GoFast_flag=0;
						SelfLockEn_flag=0; //取消自锁
						InTargetPosit_flag=0;	//目标位置
						JogRunMode=0;
						ForceStop_flag=0;
						TargetSize=0;
						DcServoGoTarget_flag=0;
						//ClrInput_function();//清零 输入框
							break;
					}
				}
			}
		else
			{
			switch(MotorType)
				{
				case MOTOR_FREQ_5_SPD_RST:
				case MOTOR_FREQ_3_SPD:
				case MOTOR_FREQ_3_SPD_RST:
					if((StartCheck_mode<2)||(StartCheck_mode==3)||(StartCheck_mode==4))
						{
						GoFrontEn_flag=1;
						GoFast_flag=0;
						ManualMoveMode=0;
						}
						break;
				case MOTOR_DC_SERVO:
						break;
				case MOTOR_AC_SERVO:
//				case MOTOR_AC_SERVO670:
					if(StartCheck_mode<=2)
						{
						GoFrontEn_flag=1;
						GoFast_flag=0;
						ManualMoveMode=0;
						}
						break;
				}		
			}
  	     break;
	case FAST_FWD_TOUCH_CODE:	//快进
		if(WorkStart_flag==1)  
			{
			if(Run_flag==0)
				{
				switch(WorkMode)
					{
					// case PROG_MODE://编程画面下
					// case TEACH_MODE://示教画面下
					// case AUTO_MODE://自动主画面下
					// case SELF_CUT_MODE://自刀主画面下
					case MANUAL_MODE:   //手动
						if((MotorType<MOTOR_DC_SERVO)||(MotorType>=MOTOR_AC_SERVO))
							{
							if(Sign_flag==1)
								{
								num_cou=0;
								GLCD_SetWindow_Fill( SIZE_WINDOW_X, SIZE_WINDOW_Y, SIZE_WINDOW_X+120, SIZE_WINDOW_Y+30, 0xfffff, 0xffff);//尺寸输入框
								Sign_flag=0;
								}
													qianjinflag=1;
							GoFrontEn_flag=1;
							GoFast_flag=1;
							SelfLockEn_flag=0; //取消自锁
							InTargetPosit_flag=0;	//目标位置
							JogRunMode=0;
							ForceStop_flag=0;
							TargetSize=0;
							DcServoGoTarget_flag=0;
							}
						//ClrInput_function();//清零 输入框
							break;
					}
				}
			}
			break;
	case ADJUST_KEY_CODE:     //后退按键**************
        if(WorkStart_flag==1)  
			{
			if(Run_flag==0)
				{
				switch(WorkMode)
					{
					case PROG_MODE://编程画面下
					case TEACH_MODE://示教画面下
					case AUTO_MODE://自动主画面下
					case SELF_CUT_MODE://自刀主画面下
					case MANUAL_MODE:   //手动
						if(Sign_flag==1)
							{
							num_cou=0;
							GLCD_SetWindow_Fill( SIZE_WINDOW_X, SIZE_WINDOW_Y, SIZE_WINDOW_X+120, SIZE_WINDOW_Y+30, 0xfffff, 0xffff);//尺寸输入框
							Sign_flag=0;
							}
                                                houtuiflag=1;
						GoBackEn_flag=1;
						GoFast_flag=0;
						SelfLockEn_flag=0; //取消自锁
						ToTargetStop_flag=0;
						InTargetPosit_flag=0;	//目标位置
						JogRunMode=0;
						ForceStop_flag=0;
						TargetSize=0;
						DcServoGoTarget_flag=0;
						//ClrInput_function();//清零 输入框
							break;
					}
				}
			} 
		else
			{
			switch(MotorType)
				{
				case MOTOR_FREQ_5_SPD_RST:
				case MOTOR_FREQ_3_SPD:
				case MOTOR_FREQ_3_SPD_RST:
					if((StartCheck_mode<2)||(StartCheck_mode==3)||(StartCheck_mode==4))
						{
						GoBackEn_flag=1;
						GoFast_flag=0;
						ManualMoveMode=0;
						}
						break;
				case MOTOR_DC_SERVO:
						break;
				case MOTOR_AC_SERVO:
	//			case MOTOR_AC_SERVO670:
					if(StartCheck_mode<=2)
						{
						GoBackEn_flag=1;
						GoFast_flag=0;
						ManualMoveMode=0;
						}	
						break;
				}	
			}
  	     break;
	case FAST_BACK_TOUCH_CODE:	//快退
		if(WorkStart_flag==1)  
			{
			if(Run_flag==0)
				{
				switch(WorkMode)
					{
					// case PROG_MODE://编程画面下
					// case TEACH_MODE://示教画面下
					// case AUTO_MODE://自动主画面下
					// case SELF_CUT_MODE://自刀主画面下
					case MANUAL_MODE:   //手动
						if((MotorType<MOTOR_DC_SERVO)||(MotorType>=MOTOR_AC_SERVO))
							{
							if(Sign_flag==1)
								{
								num_cou=0;
								GLCD_SetWindow_Fill( SIZE_WINDOW_X, SIZE_WINDOW_Y, SIZE_WINDOW_X+120, SIZE_WINDOW_Y+30, 0xfffff, 0xffff);//尺寸输入框
								Sign_flag=0;
								}
													houtuiflag=1;
							GoBackEn_flag=1;
							GoFast_flag=1;
							SelfLockEn_flag=0; //取消自锁
							ToTargetStop_flag=0;
							InTargetPosit_flag=0;	//目标位置
							JogRunMode=0;
							ForceStop_flag=0;
							TargetSize=0;
							DcServoGoTarget_flag=0;
							}
						//ClrInput_function();//清零 输入框
							break;
					}
				}
			}
  	     break;
    case REV_KEY_CODE:   //  “+/*”  ***************
        if(WorkStart_flag==1)  
			{
			if(Run_flag==0)
			    {
				if(InputTouch_flag==0)
					{
					switch(WorkMode)
						{
						case MANUAL_MODE:   //手动
						case PROG_MODE:	//编程模式
							if(Sign_flag==0)         //加 号
								{
								ClrInput_function();//清零 输入框
								Printf24(" +",SIZE_WINDOW_X,SIZE_WINDOW_Y,RED_COLOR,1,0xffff);
								Sign_flag=1;
								Minus_flag=0;
								Arithmetic_mode=PLUS_SIGN;//  "+"
								} 
							else               //清除 加号
								{
								num_cou=0;
								GLCD_SetWindow_Fill( SIZE_WINDOW_X, SIZE_WINDOW_Y, SIZE_WINDOW_X+120, SIZE_WINDOW_Y+30, 0xfffff, 0xffff);//尺寸输入框
								Sign_flag=0;
								Arithmetic_mode=NO_SIGN;//---0
								}
								break;
						case TEACH_MODE:   //示教模式
							ShowTouchWind();//弹出触摸window
							CalculatorValue_exec('+');
								break;
						}
					}
				else    //计算器 弹出模式
					{
					CalculatorValue_exec('+');	
					}
				
				}	
            } 
         break;        
    case OPTION_KEY_CODE:    //减号  “-/除”  *************
       if(WorkStart_flag==1)  
			{
			if(Run_flag==0)
			    {
				if(InputTouch_flag==0)
					{
					switch(WorkMode)
						{
						case MANUAL_MODE:   //手动
						case PROG_MODE:	//编程模式
							if(Sign_flag==0)         //"-" 号
								{
								ClrInput_function();//清零 输入框
								Printf24(" -",SIZE_WINDOW_X,SIZE_WINDOW_Y,RED_COLOR,1,0xffff);
								Sign_flag=1;
								Minus_flag=1;
								Arithmetic_mode=MINUS_SIGN;//  "-"
								} 
							else               //清除 "-"
								{
								num_cou=0;
								GLCD_SetWindow_Fill( SIZE_WINDOW_X, SIZE_WINDOW_Y, SIZE_WINDOW_X+120, SIZE_WINDOW_Y+30, 0xfffff, 0xffff);//尺寸输入框
								Sign_flag=0;
								Arithmetic_mode=NO_SIGN;//---0
								}
								break;
						case TEACH_MODE:   //示教模式
							ShowTouchWind();//弹出触摸window
							CalculatorValue_exec('-');
								break;
						}
					}	
				else    //计算器 弹出模式
					{
					CalculatorValue_exec('-');	
					}		
				}	
            }       
  	     break;
    case ZERO_KEY_CODE:	//C插入功能************
		if(WorkStart_flag==1)
		  {
		   if(Run_flag==0)
			 {
			 switch(WorkMode)
				{
				case PROG_MODE://编程画面下
				case TEACH_MODE://示教画面下
				case AUTO_MODE://自动主画面下
				case SELF_CUT_MODE://自刀主画面下
					if(num_cou>0)
						{
						if(CheckInputNums()==1)// 输入 有效
							{
							if(Knife_order<=Knife_sum)
								{
								if(Knife_sum<MAIX_Knife)
									{
									Knife_sum++;
									InsertOneKnife(Pro_data.pro_num, Knife_order);
									pKnife_data=(pInt8U)&OneKnife_data;
									// GetOneKnife_datas(Knife_order, pKnife_data);//
									OneKnife_data.size=InputSize;  //尺寸修改
									OneKnife_data.k_flag=NO_FLAG;  //清除 标志
									SaveOneKnife_datas(Pro_data.pro_num, Knife_order , pKnife_data);//保存一刀数据
										//------------------//下一刀 清除刀 标记
									if((Knife_order+1)<=Knife_sum)
										{
										GetOneKnife_datas(Pro_data.pro_num, Knife_order+1, pKnife_data);//下一刀
										if(OneKnife_data.k_flag==KNIFE_FLAG) //刀 标志
											{
											if(OneKnife_data.size>InputSize)
												{
												OneKnife_data.k_flag=0;	//清除刀 标记
												SaveOneKnife_datas(Pro_data.pro_num, Knife_order+1 , pKnife_data);//保存一刀数据
												}
											}
										}
									//-----显示
									//KnifeSize_dis(cursor_row,InputSize);//尺寸
									StepNum_dis(Knife_sum,Knife_order);//步骤更新
									Size_1page_dis(Knife_order,cursor_row);
									}
								else  //程序数据已满，不可插入
									{
									PromptDis_flag=0;
									GLCD_SetWindow_Fill( REMIND_WINDOW_X, REMIND_WINDOW_Y, REMIND_WINDOW_X+REMIND_LENGTH, REMIND_WINDOW_Y+30, 0xfffff, 0xffff);//提示框
									switch(Language)
										{
										case CHN_HAN:
											Printf24("程序刀数已满,不可插入!",REMIND_WINDOW_X,REMIND_WINDOW_Y+5,RED_COLOR,0,0xffff);
											break;
										case ENGLISH:
											Printf24("Data full,no inserting!",REMIND_WINDOW_X,REMIND_WINDOW_Y+5,RED_COLOR,0,0xffff);
											break;
										}
									}
								}
							else
								{
								PromptDis_flag=0;
								GLCD_SetWindow_Fill( REMIND_WINDOW_X, REMIND_WINDOW_Y, REMIND_WINDOW_X+REMIND_LENGTH, REMIND_WINDOW_Y+30, 0xfffff, 0xffff);//提示框
								switch(Language)
									{
									case CHN_HAN:
										Printf24("输入后请按确定键!",REMIND_WINDOW_X,REMIND_WINDOW_Y+5,RED_COLOR,0,0xffff);
											break;
									case ENGLISH:
										Printf24("Press ENTER,please!",REMIND_WINDOW_X,REMIND_WINDOW_Y+5,RED_COLOR,0,0xffff);
											break;
									}
								}
							}
						if(InputTouch_flag==0)  //	 非 触摸计算器 下
							ClrInput_function();//清零 输入框
						} 		
							break;
				case AUTO_TOOLS_MODE://  参数设置
				case SELF_TOOLS_MODE://  参数设置
				case MANUAL_TOOLS_MODE:// 手动 参数模式
					if(PramSel_Page<1)	//page 1
						{
						switch(Para_sel)
							{
							case 3://语言
								Language++;
								if(Language>1)
									Language=0;
								//***********界面语言更新
								switch(Language)
									{
									case CHN_HAN:
										x=PARA_START_X1,y=PARA_START_Y,gap=30;back_color=0xef9f;
										Printf24("前极限:     ",x,y,BLACK_COLOR,1,back_color);y+=gap;
										Printf24("中极限:    ",x,y,BLACK_COLOR,1,back_color);y+=gap;
										Printf24("后极限:    ",x,y,BLACK_COLOR,1,back_color);y+=gap;
										Printf24("语言:    ",x,y,BLACK_COLOR,1,back_color);  y+=gap;
										Printf24("单位:",x,y,BLACK_COLOR,1,back_color);  y+=gap;
										Printf24("提前量:  ",x,y,BLACK_COLOR,1,back_color);y+=gap;
										//Printf24("标准距离:   ",x,y,BLACK_COLOR,1,back_color);
										Printf24("推纸距离:   ",x,y,BLACK_COLOR,1,back_color);
										if(InputTouch_flag==0)  //	 非 触摸计算器 下
											{
											x+=PARA_COL_WIDE;y=PARA_START_Y;
											Printf24("压纸停机:   ",x,y,BLACK_COLOR,1,back_color);y+=gap;
											ParameterPage_dis(7, 0);
											if((MotorType>=MOTOR_DC_SERVO)&&(MotorType<=MOTOR_DC670_SERVO_ZHU))
												{
												Printf24("最大速度:   ",x,y,BLACK_COLOR,1,back_color);y+=gap;
												Printf24("点动速度:   ",x,y,BLACK_COLOR,1,back_color);
												}
											else if(MotorType==MOTOR_AC_SERVO)
												{
												Printf24("运行速度:   ",x,y,BLACK_COLOR,1,back_color);y+=gap;
												}
											else
												{
												Printf24("误差范围:   ",x,y,BLACK_COLOR,1,back_color);y+=gap;
												}
											}
										x=PROG_X,y=PROG_Y;back_color=0xce79;
										Printf24(" 程序  ",x,y,BLACK_COLOR,1,back_color);
										x=STEP_X;//
										Printf24("步骤",x,y,BLACK_COLOR,1,back_color);//
										break;
									case ENGLISH:	
										x=PARA_START_X1,y=PARA_START_Y,gap=30;back_color=0xef9f;
										Printf24("Front-limit:",x,y,BLACK_COLOR,1,back_color);y+=gap;
										Printf24("Midd-limit:",x,y,BLACK_COLOR,1,back_color);y+=gap;
										Printf24("Back-limit:",x,y,BLACK_COLOR,1,back_color);y+=gap;
										Printf24("Language:",x,y,BLACK_COLOR,1,back_color);  y+=gap;
										Printf24("Unit:",x,y,BLACK_COLOR,1,back_color);  y+=gap;
										Printf24("Advanced:",x,y,BLACK_COLOR,1,back_color);y+=gap;
										Printf24("Push-distan:",x,y,BLACK_COLOR,1,back_color);
										if(InputTouch_flag==0)  //	 非 触摸计算器 下
											{
											x+=PARA_COL_WIDE;y=PARA_START_Y;
											Printf24("Press-Stop:",x,y,BLACK_COLOR,1,back_color);y+=gap;
											ParameterPage_dis(7, 0);
											if((MotorType>=MOTOR_DC_SERVO)&&(MotorType<=MOTOR_DC670_SERVO_ZHU))
												{
												Printf24("Max-speed:",x,y,BLACK_COLOR,1,back_color);y+=gap;
												Printf24("Jog-speed:",x,y,BLACK_COLOR,1,back_color);
												}
											else if(MotorType==MOTOR_AC_SERVO)
												{
												Printf24("Run-speed:",x,y,BLACK_COLOR,1,back_color);y+=gap;
												}
											else
												{
												Printf24("err range:  ",x,y,BLACK_COLOR,1,back_color);y+=gap;
												}
											}
										x=PROG_X,y=PROG_Y;back_color=0xce79;
										Printf24("Process",x,y,BLACK_COLOR,1,back_color);
										x=STEP_X;//
										Printf24("Step",x,y,BLACK_COLOR,1,back_color);
										break;
									}
								ParameterPage_dis(Para_sel, 1);
								if(InputTouch_flag==1)  //	  触摸计算器 下
									{
									Button_dis(BUTT_INSERT, 1); //触摸 按钮 显示
									Button_dis(BUTT_EXIT, 0); //触摸 按钮 显示
									Button_dis(BUTT_ENTER, 0); //触摸 按钮 显示
									}
								SaveLanguage();
								break;
							case 4: //单位
								Unit++;
								if(Unit>1)//mm
									{
									Unit=0;
									Size_MIN_num=Size_MIN;
									Size_MAX_num=Size_MAX;	
									if(InTargetPosit_flag==1)  //目标位置
										{
										TargetSize=CurrentSize_temp;
										}
									}
								else
									{
									Size_MIN_num=Size_MIN*100/254;
									Size_MAX_num=Size_MAX*100/254;	
									if(InTargetPosit_flag==1)  //	目标位置
										{
										TargetSize_inch=CurrentSize*100/254;
										}
									}
								CurrentSize_dis(CurrentSize); //当前尺寸 更新显示
								CurrUint_dis(Unit);  //当前尺寸 单位
								FrontKnifeUint_dis(Unit);  //当前尺寸 单位
								if(BeforeKnifeNo_flag==0)
									FrontKnifeSize_dis(BeforeKnifeSize);
								ParameterPage_dis(0, 0);
								ParameterPage_dis(1, 0);
								ParameterPage_dis(2, 0);
								ParameterPage_dis(5, 0);
								ParameterPage_dis(6, 0);
								
								ParameterPage_dis(Para_sel, 1);	
								SaveUnit();	
								break;
							case 7:  //压纸 停机
								if(PressValid_flag==0)
									PressValid_flag=1;
								else 
									PressValid_flag=0;
								if(InputTouch_flag==0)  //	  触摸计算器 下
									ParameterPage_dis(Para_sel, 1);	
								SavePressValid_flag();	
								break;
							}	
						}
					else	//page 2
						{
						switch(Para2_sel)	
							{
							case 0://光电选
								if(IR_SensorStus==0)
										IR_SensorStus=1;
									else
										IR_SensorStus=0;
									if(InputTouch_flag==0)  //	  !触摸计算器 下
										ParameterPage2_dis(Para2_sel, 1);	
									SaveIRValidStatus();	
								break;
							case 2://	前极限
								if(Front_LimitValid_flag==0)
									Front_LimitValid_flag=1;//有效
								else
									Front_LimitValid_flag=0;
								if(InputTouch_flag==0)  //	  !触摸计算器 下
									ParameterPage2_dis(Para2_sel, 1);	
								SaveFrontValidStatus();	
								break;
							case 3://	中极限
								if(Middle_LimitValid_flag==0)
									Middle_LimitValid_flag=1;//有效
								else
									Middle_LimitValid_flag=0;
								if(InputTouch_flag==0)  //	  !触摸计算器 下
									ParameterPage2_dis(Para2_sel, 1);	
								SaveMiddleValidStatus();	
								break;
							case 4://	后极限
								if(Back_LimitValid_flag==0)
									Back_LimitValid_flag=1;//有效
								else
									Back_LimitValid_flag=0;
								if(InputTouch_flag==0)  //	  !触摸计算器 下
									ParameterPage2_dis(Para2_sel, 1);	
								SaveBackValidStatus();	
								break;
							}
						}
							break;
				case MANUAL_PASS_MODE: //手动 密码设置
					if(PassModeOk_flag==1)
						{
						if(Para_sel==0)
							{
							if(FirstDayValid_flag==1)
								{
								FirstDayValid_flag=0;
								if(SecondDayValid_flag==1)  //进入 二次计时
									{
									Start_days.year=Year;
									Start_days.month=Month;
									Start_days.day=Dom;
									SaveWorkDays(); //起始 时间保存
									}
								}
							else  //---------时间生效
								{
								FirstDayValid_flag=1;
								Start_days.year=Year;
								Start_days.month=Month;
								Start_days.day=Dom;
								SaveWorkDays(); //起始 时间保存
								}
							SaveFirstDays_flag();	
							}
						else
							{
							if(SecondDayValid_flag==1)
								SecondDayValid_flag=0;
							else if(FirstDayValid_flag==1) //前一次 已设定有效
								SecondDayValid_flag=1;
							SaveSecondDays_flag();	
							}
						PassDaysSet_dis(Para_sel, 1);//天数设定
						}
				}			
			 }
		   else
			 {
									
			 }
		  }
  	        break;
    case FIVE_KEY_CODE:		//删除按键*************
        if(WorkStart_flag==1)
		  {
		  if(Run_flag==0)
			 {
			 switch(WorkMode)
				{
				case PROG_MODE://编程画面下
				case TEACH_MODE://示教画面下
				case AUTO_MODE://自动主画面下
				case SELF_CUT_MODE://自刀主画面下
					if(Knife_order<=Knife_sum)
						{
						DeleteOneKnife(Pro_data.pro_num, Knife_order);      //删除一刀
						//Size_1page_dis(Knife_order,cursor_row);
						if(Knife_sum>1)
							{
							Knife_sum--;
							SaveKnife_sum(Pro_data.pro_num);
							StepNum_dis(Knife_sum,Knife_order);//步骤更新
							PromptDis_flag=0;
							GLCD_SetWindow_Fill( REMIND_WINDOW_X, REMIND_WINDOW_Y, REMIND_WINDOW_X+REMIND_LENGTH, REMIND_WINDOW_Y+30, 0xfffff, 0xffff);//提示框
							switch(Language)
								{
								case CHN_HAN:
									Printf24("长按超过5秒，删除全部!",REMIND_WINDOW_X,REMIND_WINDOW_Y+5,RED_COLOR,0,0xffff);
										break;
								case ENGLISH:
									Printf24("Long-press 5 sec,deleate all!",REMIND_WINDOW_X,REMIND_WINDOW_Y+5,RED_COLOR,0,0xffff);
										break;
								}
								
							if(Knife_order<=Knife_sum)
								{
								pKnife_data=(pInt8U)&OneKnife_data;
								if(Knife_order>1)
									{
									GetOneKnife_datas(Pro_data.pro_num, Knife_order-1, pKnife_data);//前一刀
									perv_data=OneKnife_data.size;
									}
								else
									{
									perv_data=0;
									}
								GetOneKnife_datas(Pro_data.pro_num, Knife_order, pKnife_data);// 当前刀
								Flg_chg=0;
								if(OneKnife_data.k_flag==KNIFE_FLAG) //刀 标志
									{
									if(OneKnife_data.size>perv_data)
										{
										OneKnife_data.k_flag=0;//清除 刀 标志
										Flg_chg=1;
										flag_now=OneKnife_data.k_flag;	//当前标记 暂存
										SaveOneKnife_datas(Pro_data.pro_num, Knife_order , pKnife_data);//保存一刀数据
										}
									}	
								}
							}
						Size_1page_dis(Knife_order,cursor_row);
						if(InputTouch_flag==0) //----非 触摸计算器-更新标记
							{
							if(Flg_chg==1)
								{
								PushFlag_dis(cursor_row,flag_now); //光标处  标记图片 显示
								}
							}
						}
							break;
				}	
			 }
		   else
			 {
									
			 }
		  }
  	     break;	  
    case UP_KEY_CODE:    ///////////运行按键*******************  
      qianjinflag=0;
        houtuiflag=0;
        if(WorkStart_flag==1)  
			{
			if(Run_flag==0)
			    {
				switch(WorkMode)
					{
					case MANUAL_MODE:   //手动
						if(Sign_flag==1)  //相对 运行
							{
							if(num_cou>0)	
								{
								if(num_cou<8)
									{
									CheckInputNums();
									if(Unit==UNIT_MM)//mm
										{
										if(InTargetPosit_flag==1)  //	目标位置
											target_temp=TargetSize_temp;
										else	
											target_temp=CurrentSize;
										}
									else  //inch
										{
										if(InTargetPosit_flag==1)  //	目标位置
											target_temp=TargetSize_inch;
										else	
											target_temp=CurrentSize*100/254;
										}
									
									if(Minus_flag==1) //减“-”
										{
										if(target_temp>InputSize)
											{
											d_temp=target_temp-InputSize;
											}
										else//超出范围
											{
											num_cou=0;
											GLCD_SetWindow_Fill( SIZE_WINDOW_X, SIZE_WINDOW_Y, SIZE_WINDOW_X+120, SIZE_WINDOW_Y+30, 0xfffff, 0xffff);//尺寸输入框
											PromptDis_flag=0;
											GLCD_SetWindow_Fill( REMIND_WINDOW_X, REMIND_WINDOW_Y, REMIND_WINDOW_X+REMIND_LENGTH, REMIND_WINDOW_Y+30, 0xfffff, 0xffff);//提示框
											switch(Language)
													{
													case CHN_HAN:
															Printf24("输入尺寸超过极限!",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,RED_COLOR,0,0xffff);
															break;
													case ENGLISH:
															Printf24("Data exceeds limit!",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,RED_COLOR,0,0xffff);
															break;
													}
											if(InputTouch_flag==1)   //触摸下
												{
												ClearCalculatorInput(); //清零计算器 输入
												}		
											}
										}	
									else     //加  “+”
										{
										d_temp=target_temp+InputSize;
										}	
									
									if((d_temp<Size_MIN_num)||(d_temp>Size_MAX_num))//超出范围
										{
										num_cou=0;
										GLCD_SetWindow_Fill( SIZE_WINDOW_X, SIZE_WINDOW_Y, SIZE_WINDOW_X+120, SIZE_WINDOW_Y+30, 0xfffff, 0xffff);//尺寸输入框
										PromptDis_flag=0;
										GLCD_SetWindow_Fill( REMIND_WINDOW_X, REMIND_WINDOW_Y, REMIND_WINDOW_X+REMIND_LENGTH, REMIND_WINDOW_Y+30, 0xfffff, 0xffff);//提示框
										switch(Language)
											{
											case CHN_HAN:
													Printf24("输入尺寸超过极限!",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,RED_COLOR,0,0xffff);
															break;
											case ENGLISH:
													Printf24("Data exceeds limit!",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,RED_COLOR,0,0xffff);
															break;
											}
										if(InputTouch_flag==1)   //触摸下
											{
											ClearCalculatorInput(); //清零计算器 输入
											}	
										}
									else   //数据有效	 
										{
										if(Unit==UNIT_MM)//mm
											{
											TargetSize=d_temp;
											NewInput_dis(TargetSize);
											}
										else
											{
											TargetSize_inch=d_temp;
											TargetSize=TargetSize_inch*2.54;
											NewInput_dis(TargetSize_inch);
											}
									
										PromptNum_dis();//输入范围 提示
										PromptDis_flag=1;
										num_cou=8;
										if(TargetSize!=CurrentSize)  //-------------运行
										//if(1)
											{
											TargetSize_temp=TargetSize;
											switch(MotorType)
												{
												case MOTOR_FREQ_5_SPD_RST:
												case MOTOR_FREQ_3_SPD:
												case MOTOR_FREQ_3_SPD_RST:
													 SelfLockEn_flag=0;
													 ToTargetStop_flag=0;
													 MoveSpeed=0;
													 MoveSpeedCtrl();  //运行速度控制
														break;
												case MOTOR_DC_SERVO:
												case MOTOR_DC670_SERVO:
												case MOTOR_DC670_SERVO_ZHU:
													ServoSendCou=0;
													 DcServoStartRun_exec(TargetSize);
													// SelfLockEn_flag=0;
														break;
												case MOTOR_AC_SERVO:
													ACMotorRunStart(TargetSize);
														break;		
												}
											Run_flag=1;
											RunStop_flag=0;
											AutoCutStart_flag=0;
											InTargetPosit_flag=0;	//目标位置
											OneCutRoutine_flag=0; // 清 裁切 循环标志
											AutoCutStart_flag=0;
											PromptNum_dis();
											}
										}
									Sign_flag=0;
									}
									
								}
							}
						else
							{
							if(num_cou>0)	
								{
								if(num_cou<8)
									{
									if(CheckInputNums()==1)// 输入 有效
										{
										if(InputTouch_flag==0)  //	 非 触摸计算器 下
											num_cou=8;
										if(InputSize!=CurrentSize)
										//if(1)
											{
											if(Unit==UNIT_MM)//mm
												{
												TargetSize=InputSize;
												}
											else
												{
												TargetSize_inch=InputSize;
												TargetSize=TargetSize_inch*2.54;
												}
											TargetSize_temp=TargetSize;
											switch(MotorType)
												{
												case MOTOR_FREQ_5_SPD_RST:
												case MOTOR_FREQ_3_SPD:
												case MOTOR_FREQ_3_SPD_RST:
													 SelfLockEn_flag=0;
													 ToTargetStop_flag=0;
													 MoveSpeed=0;
													 MoveSpeedCtrl();  //运行速度控制
														break;
												case MOTOR_DC_SERVO:
												case MOTOR_DC670_SERVO:
												case MOTOR_DC670_SERVO_ZHU:
													 ServoSendCou=0;
													 DcServoStartRun_exec(TargetSize);
													// SelfLockEn_flag=0;
														break;
												case MOTOR_AC_SERVO:
													 ACMotorRunStart(TargetSize);
													// SelfLockEn_flag=0;
														break;		
												}
											Run_flag=1;
											RunStop_flag=0;
											InTargetPosit_flag=0;	//目标位置
											OneCutRoutine_flag=0; // 清 裁切 循环标志
											AutoCutStart_flag=0;
											PromptNum_dis();
											}
										}
									else  //无效
										{
										ClrInput_function();//清零 输入框
										}
									}
								else          //已 输入数据  直接运行
									{
									if(TargetSize_temp!=CurrentSize)
									//if(1)
										{
										TargetSize=TargetSize_temp;
										switch(MotorType)
											{
											case MOTOR_FREQ_5_SPD_RST:
											case MOTOR_FREQ_3_SPD:
											case MOTOR_FREQ_3_SPD_RST:
												 SelfLockEn_flag=0;
												 ToTargetStop_flag=0;
												 MoveSpeed=0;
												 MoveSpeedCtrl();  //运行速度控制
													break;
											case MOTOR_DC_SERVO:
											case MOTOR_DC670_SERVO:
											case MOTOR_DC670_SERVO_ZHU:
												 ServoSendCou=0;
												 DcServoStartRun_exec(TargetSize);
												// SelfLockEn_flag=0;
													break;
											case MOTOR_AC_SERVO:
												 ACMotorRunStart(TargetSize);
													break;		
											}
										Run_flag=1;
										RunStop_flag=0;
										InTargetPosit_flag=0;	//目标位置
										OneCutRoutine_flag=0; // 清 裁切 循环标志
										AutoCutStart_flag=0;
										PromptNum_dis();
										}
									}
								}
							else
								{
								//ClrInput_function();//清零 输入框
								//CheckInputNums();
								}
							}	
							break;
					case AUTO_MODE://自动  主画面下
					case SELF_CUT_MODE://自刀 主画面下
					//case TEACH_MODE://示教画面下
						OneCutRoutine_flag=0; // 清 裁切 循环标志
						AutoRun_start();   //运行至 光标处
							break;
					case TEACH_MODE://示教 模式
						if(num_cou>0)	
							{
							if(num_cou<8)
								{
								if(CheckInputNums()==1)// 输入 有效
									{
									if(InputTouch_flag==0)  //	 非 触摸计算器 下
										num_cou=8;
									if(InputSize!=CurrentSize)
									//if(1)
										{
										if(Unit==UNIT_MM)//mm
											{
											TargetSize=InputSize;
											}
										else
											{
											TargetSize_inch=InputSize;
											TargetSize=TargetSize_inch*2.54;
											}
										TargetSize_temp=TargetSize;
										switch(MotorType)
											{
											case MOTOR_FREQ_5_SPD_RST:
											case MOTOR_FREQ_3_SPD:
											case MOTOR_FREQ_3_SPD_RST:
												 SelfLockEn_flag=0;
												 ToTargetStop_flag=0;
												 MoveSpeed=0;
												 MoveSpeedCtrl();  //运行速度控制
													break;
											case MOTOR_DC_SERVO:
											case MOTOR_DC670_SERVO:
											case MOTOR_DC670_SERVO_ZHU:
												 ServoSendCou=0;
												 DcServoStartRun_exec(TargetSize);
												// SelfLockEn_flag=0;
													break;
											case MOTOR_AC_SERVO:
												 ACMotorRunStart(TargetSize);
												// SelfLockEn_flag=0;
													break;		
											}
										Run_flag=1;
										RunStop_flag=0;
										InTargetPosit_flag=0;	//目标位置
										OneCutRoutine_flag=0; // 清 裁切 循环标志
										AutoCutStart_flag=0;
										PromptNum_dis();
										}
									}
								else  //无效
									{
									ClrInput_function();//清零 输入框
									}
								}
							else          //已 输入数据  直接运行
								{
								if(TargetSize_temp!=CurrentSize)
								//if(1)
									{
									TargetSize=TargetSize_temp;
									switch(MotorType)
										{
										case MOTOR_FREQ_5_SPD_RST:
										case MOTOR_FREQ_3_SPD:
										case MOTOR_FREQ_3_SPD_RST:
											 SelfLockEn_flag=0;
											 ToTargetStop_flag=0;
											 MoveSpeed=0;
											 MoveSpeedCtrl();  //运行速度控制
												break;
										case MOTOR_DC_SERVO:
										case MOTOR_DC670_SERVO:
										case MOTOR_DC670_SERVO_ZHU:
											 ServoSendCou=0;
											 DcServoStartRun_exec(TargetSize);
											// SelfLockEn_flag=0;
												break;
										case MOTOR_AC_SERVO:
											 ACMotorRunStart(TargetSize);
												break;		
										}
									Run_flag=1;
									RunStop_flag=0;
									InTargetPosit_flag=0;	//目标位置
									OneCutRoutine_flag=0; // 清 裁切 循环标志
									AutoCutStart_flag=0;
									PromptNum_dis();
									}
								}
							}
						else
							{
							OneCutRoutine_flag=0; // 清 裁切 循环标志
							AutoRun_start();   //运行至 光标处
							}
							break;
					}
				}	
            else
				{
				
				}
			}
		else
			{
			switch(MotorType)
				{
				case MOTOR_FREQ_5_SPD_RST:
				case MOTOR_FREQ_3_SPD:
				case MOTOR_FREQ_3_SPD_RST:
					if(StartCheck_mode==4)
						{
						if(Board_TestMod==0)       //-----
							{
							if(PassCodeEn_flag==0)
								{
								MoveSpeed=2;
								SetMotorSpeed(MoveSpeed);//中高速
								MoveBack(); //后退
								CurrentArea_recover2(REMIND_WINDOW_X, REMIND_WINDOW_Y, START_PROM_WIDE, START_PROM_HIGH);
								switch(Language)
									{
									case CHN_HAN:
											Printf24("运行....",RUN_DIS_X,RUN_DIS_Y,RED_COLOR,1,0xffff);
												break;
									case ENGLISH:
											Printf24("Runing....",RUN_DIS_X,RUN_DIS_Y,RED_COLOR,1,0xffff);
												break;
									}
								StartCheck_mode++;
								CodeSensorTime_AB=0;
								}
							else   //密码 启动
								{
								if(PassCheckDis_flag==0) //密码提示 ------显示
									{
									PassCheckDis_flag=1;
									switch(Language)
										{
										case CHN_HAN:
												Printf24("有效使用时间到，请输入密码！",PASSCODE_X,PASSCODE_Y,RED_COLOR,1,0xffff);
													break;
										case ENGLISH:
												Printf24("Your hour is up,enter passcode",PASSCODE_X,PASSCODE_Y,RED_COLOR,1,0xffff);
													break;
										}
									PassCheck_dis(PASSCODE_X+400,PASSCODE_Y);
									GLCD_SetWindow_Fill(PASSCODE_INPUT_X, PASSCODE_INPUT_Y, PASSCODE_INPUT_X+100, PASSCODE_INPUT_Y+30, 0xfffff, 0xffff);
									}
								}
							}
						}
						break;
				case MOTOR_DC_SERVO:
				case MOTOR_DC670_SERVO:
				case MOTOR_DC670_SERVO_ZHU:
					if(StartCheck_mode==1)
						{
						if(Board_TestMod==0)       //-----
							{
							if(PassCodeEn_flag==0)
								{
								CurrentSize=OriginalSize;
								//if(SearchZero_flag==0)   //未归0
									ServoSetCommd(SERVO_COMMD_R,STAT_30H,CurrentSize);  //启动寻零
								CurrentArea_recover2(REMIND_WINDOW_X, REMIND_WINDOW_Y, START_PROM_WIDE, START_PROM_HIGH);
								switch(Language)
									{
									case CHN_HAN:
											Printf24("运行....",RUN_DIS_X,RUN_DIS_Y,RED_COLOR,1,0xffff);
												break;
									case ENGLISH:
											Printf24("Runing....",RUN_DIS_X,RUN_DIS_Y,RED_COLOR,1,0xffff);
												break;
									}
								StartCheck_mode++;
								}
							else   //密码 启动
								{
								if(PassCheckDis_flag==0) //密码提示 ------显示
									{
									PassCheckDis_flag=1;
									switch(Language)
										{
										case CHN_HAN:
												Printf24("有效使用时间到，请输入密码！",PASSCODE_X,PASSCODE_Y,RED_COLOR,1,0xffff);
													break;
										case ENGLISH:
												Printf24("Your hour is up,enter passcode",PASSCODE_X,PASSCODE_Y,RED_COLOR,1,0xffff);
													break;
										}
									PassCheck_dis(PASSCODE_X+400,PASSCODE_Y);
									GLCD_SetWindow_Fill(PASSCODE_INPUT_X, PASSCODE_INPUT_Y, PASSCODE_INPUT_X+100, PASSCODE_INPUT_Y+30, 0xfffff, 0xffff);
									}
								}
							}
						}
						break;
				case MOTOR_AC_SERVO:
					if(StartCheck_mode==4)
						{
						if(Board_TestMod==0)       //-----
							{
							if(PassCodeEn_flag==0)
								{
								ACServoMoveBack_MID_SPD();  //交流伺服  中速后退
								CurrentArea_recover2(REMIND_WINDOW_X, REMIND_WINDOW_Y, START_PROM_WIDE, START_PROM_HIGH);
								switch(Language)
									{
									case CHN_HAN:
											Printf24("运行....",RUN_DIS_X,RUN_DIS_Y,RED_COLOR,1,0xffff);
												break;
									case ENGLISH:
											Printf24("Runing....",RUN_DIS_X,RUN_DIS_Y,RED_COLOR,1,0xffff);
												break;
									}
								StartCheck_mode++;
								CodeSensorTime_AB=0;
								}
							else   //密码 启动
								{
								if(PassCheckDis_flag==0) //密码提示 ------显示
									{
									PassCheckDis_flag=1;
									switch(Language)
										{
										case CHN_HAN:
												Printf24("有效使用时间到，请输入密码！",PASSCODE_X,PASSCODE_Y,RED_COLOR,1,0xffff);
													break;
										case ENGLISH:
												Printf24("Your hour is up,enter passcode",PASSCODE_X,PASSCODE_Y,RED_COLOR,1,0xffff);
													break;
										}
									PassCheck_dis(PASSCODE_X+400,PASSCODE_Y);
									GLCD_SetWindow_Fill(PASSCODE_INPUT_X, PASSCODE_INPUT_Y, PASSCODE_INPUT_X+100, PASSCODE_INPUT_Y+30, 0xfffff, 0xffff);
									}
								}
							}
						}
						break;
				}	
			}
			
  	     break;  
	case DOWN_KEY_CODE:   // 确定************** 
		if(WorkStart_flag==1)
		  {
		  if(Run_flag==0)
			 {
			 switch(WorkMode)
					{
					case PROG_MODE://编程画面下
					case TEACH_MODE://示教画面下
					case AUTO_MODE://自动主画面下
					case SELF_CUT_MODE://自刀主画面下
						if(Sign_flag==0)
							{
							if(num_cou>0)
							  {
							  if(CheckInputNums()==1)// 输入 有效
								 {
								 //----保存数据----------------
								 if(Knife_order>Knife_sum)//更新步骤 总刀数
									{
									Knife_sum=Knife_order;
									}
								 pKnife_data=(pInt8U)&OneKnife_data;
								 if(Knife_order>1)
									{
									GetOneKnife_datas(Pro_data.pro_num, Knife_order-1, pKnife_data);//前一刀
									perv_data=OneKnife_data.size;
									}
								 else
									{
									perv_data=0;
									}
								 GetOneKnife_datas(Pro_data.pro_num, Knife_order, pKnife_data);//
								 OneKnife_data.size=InputSize;  //尺寸修改
								 Flg_chg=0;
								 if((OneKnife_data.k_flag&0xf)==KNIFE_FLAG) //刀 标志
									{
									if(InputSize>perv_data)
										{
										OneKnife_data.k_flag=0;//清除 刀 标志
										Flg_chg=1;
										flag_now=OneKnife_data.k_flag;	//当前标记 暂存
										}
									}
								 SaveOneKnife_datas(Pro_data.pro_num, Knife_order , pKnife_data);//保存一刀数据
								 if(Knife_order<Knife_sum)// 不是最后一刀
									{
									GetOneKnife_datas(Pro_data.pro_num, Knife_order+1, pKnife_data);// 下一刀 数据
									 if(OneKnife_data.k_flag==KNIFE_FLAG) //刀 标志
										{
										if(OneKnife_data.size>InputSize)
											{
											OneKnife_data.k_flag=0;	//清除 刀 标志
											if(Flg_chg==1)
												{
												Flg_chg=3;
												}
											else
												{
												Flg_chg=2;
												}
											SaveOneKnife_datas(Pro_data.pro_num, Knife_order+1 , pKnife_data);//保存下一刀	
											}
										}
									}
									
									//-----显示
								 KnifeSize_dis(cursor_row,InputSize,0);//尺寸
								 if(Knife_order<MAIX_Knife)            //刀序递增
									{
									if((WorkMode==PROG_MODE)||(WorkMode==TEACH_MODE))
										{
										Knife_order++;
										StepNum_dis(Knife_sum,Knife_order);//步骤更新
										if(cursor_row<(PAGE_KNIFE-1))
											{
											CursorMov_dis(cursor_row, 0);//红色光标消失
											OneKnifeDataSel_dis(Knife_order-1, cursor_row,0);  //一刀数据 高亮显示
											cursor_row++;
											CursorMov_dis(cursor_row, 1);//红色光标下移显示
											OneKnifeDataSel_dis(Knife_order, cursor_row,RED_COLOR);  //一刀数据 高亮显示
											if(InputTouch_flag==0) //---非 触摸计算器-更新标记 
												{
												switch(Flg_chg)
													{
													case 1:
														PushFlag_dis(cursor_row-1,flag_now); // 标记图片 显示
														break;
													case 2:
														PushFlag_dis(cursor_row,OneKnife_data.k_flag); //光标处 标记图片 显示
														break;
													case 3:
														PushFlag_dis(cursor_row-1,flag_now); // 标记图片 显示
														PushFlag_dis(cursor_row,OneKnife_data.k_flag); //光标处 标记图片 显示
														break;
													}
												}
											}
										else   //页底
											{
											Size_1page_dis(Knife_order-(PAGE_KNIFE-1),0);//一页尺寸显示
											}
										}
									else
										{
										StepNum_dis(Knife_sum,Knife_order);//步骤更新
										KnifeSize_dis(cursor_row,InputSize,RED_COLOR);//尺寸
										if(InputTouch_flag==0) //----非 触摸计算器-更新标记
											{
											switch(Flg_chg)
												{
												case 1:
													PushFlag_dis(cursor_row,flag_now); // 标记图片 显示
													break;
												case 2:
													PushFlag_dis(cursor_row+1,OneKnife_data.k_flag); //光标处 标记图片 显示
													break;
												case 3:
													PushFlag_dis(cursor_row,flag_now); // 标记图片 显示
													PushFlag_dis(cursor_row+1,OneKnife_data.k_flag); //光标处 标记图片 显示
													break;
												}
											}
										}
									}
								else
									{
									OneKnifeDataSel_dis(Knife_order, cursor_row,RED_COLOR);  //一刀数据 高亮显示
									if(InputTouch_flag==0) //----非 触摸计算器-更新标记
										{
										if(Flg_chg==1)
											{
											PushFlag_dis(cursor_row,flag_now); //光标处  标记图片 显示
											}
										}
									}
								 }
							//if(InputTouch_flag==0)  //	 非 触摸计算器 下	 
								ClrInput_function();//清零 输入框
							 }
							}
						else
							{
							if(num_cou>0)
								{
								ArithmeticInputSize(); //对当前尺寸 算数计算
								Sign_flag=0;
								}
							}
						   break;
					case PROG_LABEL_MODE:		//标签 模式**********************************
						if(num_cou>0)
						   {
						   LabelEnter_exec();//标签 三组 数据设定确认
						   }  
						else
						   {
						   if((Total_size*Label_size*Waste_size)!=0)//设定有效
								{
								if(InputTouch_flag==0)    //非 触摸计算器 下
									{
									WorkMode=PROG_MODE;         //------------------退出返回到编程主 画面 
									CurrentArea_recover2(MIDDLE_PAGE_X , MIDDLE_PAGE_Y,  M_PAGE_WIDE, M_PAGE_HIGH);
									Program_dis(PROGRAM_X,PROGRAM_Y);   //编程
									Label_function();
									PorgSet_sel=0;
									//PaperCutEnb_signal=1;
									}
								else
									CalcuInClear_exec();     //清除 计算器
								}
						   } 
						   break;
					case TEACH_LABEL_MODE:		//标签 模式**********************************
						if(num_cou>0)
							{
							LabelEnter_exec();//标签 三组 数据设定确认
							}  
						else
							{
							if((Total_size*Label_size*Waste_size)!=0)//设定有效
								{
								if(InputTouch_flag==0)    //非 触摸计算器 下
									{
									WorkMode=TEACH_MODE;         //------------------退出返回到示教主 画面 
									PaperCutEnb_signal=1;
									CurrentArea_recover2(MIDDLE_PAGE_X , MIDDLE_PAGE_Y,  M_PAGE_WIDE, M_PAGE_HIGH);
									Teach_dis(TEACH_X,TEACH_Y);   //示教
									Label_function();
									PorgSet_sel=0;
									}
								else
									CalcuInClear_exec();     //清除 计算器	
								}
							} 
						   break;		   
					case PROG_DIVIDE_MODE:	//等分模式***************************************	
						if(num_cou>0)
						   {
						   DivideEnter_exec();//等分 数据设定确认
						   }
						else
						   {
						   if((Total_size*Divide_num)!=0)//设定等分有效
								{
								if(InputTouch_flag==0)    //非 触摸计算器 下
									{
									WorkMode=PROG_MODE;           //------------------退出返回到编程主 画面
									CurrentArea_recover2(MIDDLE_PAGE_X , MIDDLE_PAGE_Y,  M_PAGE_WIDE, M_PAGE_HIGH);
									Program_dis(PROGRAM_X,PROGRAM_Y);   //编程
									Divide_function();//
									PorgSet_sel=0;
									//PaperCutEnb_signal=1;
									}
								else
									CalcuInClear_exec();     //清除 计算器	
								}
						   }
						   break;
					case TEACH_DIVIDE_MODE:	//等分模式***************************************	
						if(num_cou>0)
						   {
						   DivideEnter_exec();//等分 数据设定确认
						   }
						else
						   {
						   if((Total_size*Divide_num)!=0)//设定等分有效
								{
								if(InputTouch_flag==0)    //非 触摸计算器 下
									{
									WorkMode=TEACH_MODE;           //------------------退出返回到示教主 画面
									PaperCutEnb_signal=1;
									CurrentArea_recover2(MIDDLE_PAGE_X , MIDDLE_PAGE_Y,  M_PAGE_WIDE, M_PAGE_HIGH);
									Teach_dis(TEACH_X,TEACH_Y);   //示教
									Divide_function();//
									PorgSet_sel=0;
									}
								else
									CalcuInClear_exec();     //清除 计算器		
								}
						   }
						   break;		   
					case PROG_PRO_MODE:	//程序选择*****************************	   
						if(num_cou>0)
							{
							  ProEnter_exec();//程序选择 输入确认
							}
						else
							{
							 if((Pro_num>0)&&(Pro_num<=MAIX_PROG))// 有效  更新一个程序，并显示--------------------
								{
								if(InputTouch_flag==0)    //非 触摸计算器 下
									{
									cursor_temp=0;
									ExportOnePro_dis(Pro_num);  //更新一个 程序   
									//----------返回编程画面
									WorkMode=PROG_MODE; 
									Program_dis(PROGRAM_X,PROGRAM_Y);   //编程
									//PaperCutEnb_signal=1;
									}
								else
									CalcuInClear_exec();     //清除 计算器
								}
							}	
							break;
					case TEACH_PRO_MODE:	//程序选择*****************************	   
						if(num_cou>0)
							{
							  ProEnter_exec();//程序选择 输入确认
							}
						else
							{
							 if((Pro_num>0)&&(Pro_num<=MAIX_PROG))// 有效  更新一个程序，并显示--------------------
								{
								if(InputTouch_flag==0)    //非 触摸计算器 下
									{
									cursor_temp=0;
									ExportOnePro_dis(Pro_num);  //更新一个 程序   
									//----------返回示教
									WorkMode=TEACH_MODE; 
									PaperCutEnb_signal=1;
									Teach_dis(TEACH_X,TEACH_Y);   //示教
									}
								else
									CalcuInClear_exec();     //清除 计算器
								}
							}	
							break;			
					case AUTO_PLUS_MODE:  //F3++
						if(num_cou>0)
							{
							if(Knife_order<=Knife_sum)
							   {
							   if(CheckInputNums()==1)
									{
									F3_AutoAdd_exec(InputSize);  
									if(InputTouch_flag==0)  //	 非 触摸计算器 下
										ClrInput_function();//清零 输入框
									else	//触摸 下
										CalcuInClear_exec();     //清除 计算器
									WorkMode=AUTO_MODE;
									PaperCutEnb_signal=1;
									PressCircle_mode=0;
									F3_plus_dis(0);	
									}	
							   }
							}
							break;
					case AUTO_MINUS_MODE:// F4--
						if(num_cou>0)
							{
							if(Knife_order<=Knife_sum)
							   {
							   if(CheckInputNums()==1)
									{
									F4_AutoSub_exec(InputSize);  //F4--  批量数据 自减
									if(InputTouch_flag==0)  //	 非 触摸计算器 下
										ClrInput_function();//清零 输入框
									else	//触摸 下
										CalcuInClear_exec();     //清除 计算器	
									WorkMode=AUTO_MODE;//返回
									PaperCutEnb_signal=1;
									PressCircle_mode=0;
									F4_minus_dis(0);
									}
							   }
							}
							break;
					case SELF_PLUS_MODE:  //F3++
						if(num_cou>0)
							{
							if(Knife_order<=Knife_sum)
							   {
							   if(CheckInputNums()==1)
									{
									F3_AutoAdd_exec(InputSize);  
									F3_plus_dis(0);	
									if(InputTouch_flag==0)  //	 非 触摸计算器 下
										ClrInput_function();//清零 输入框
									else	//触摸 下
										CalcuInClear_exec();     //清除 计算器	
									WorkMode=SELF_CUT_MODE;
									}
							   }
							}
							break;
					case SELF_MINUS_MODE:// F4--
						if(num_cou>0)
							{
							if(Knife_order<=Knife_sum)
							   {
							   if(CheckInputNums()==1)
									{
									F4_AutoSub_exec(InputSize);  //F4--  批量数据 自减
									if(InputTouch_flag==0)  //	 非 触摸计算器 下 
										ClrInput_function();//清零 输入框
									else	//触摸 下
										CalcuInClear_exec();     //清除 计算器	
									WorkMode=SELF_CUT_MODE;//返回
									F4_minus_dis(0);
									}
							   }
							}
							break;			
					case AUTO_RULER_MODE://自动 基准
					case SELF_RULER_MODE://自刀 基准
					case MANUAL_RULER_MODE://手动 基准模式
						if(num_cou>0)
							{
							if(CheckInputNums()==1)
								{
								if(Unit!=UNIT_MM)//mm
									InputSize*=2.54;
									
									//********************************=============
									SelfLockEn_flag=0;
									ToTargetStop_flag=0;
									InTargetPosit_flag=0;	//目标位置
									//OneCutRoutine_flag=0; // 清 裁切 循环标志
								switch(MotorType)
									{
									case MOTOR_FREQ_5_SPD_RST:
									case MOTOR_FREQ_3_SPD:
									case MOTOR_FREQ_3_SPD_RST:
									//****************************==============
										MoveStop();
										TargetSize=0;
										TargetSize_temp=0;
										BeforeKnife_offset_in=0;
										Run_flag=0;
										
										OriginalSize=OriginalSize+InputSize-(muqiancn/1000);
										muqiancn=InputSize*1000;
										CurrentSize=InputSize;
											break;
									case MOTOR_DC_SERVO:
									case MOTOR_DC670_SERVO:
									case MOTOR_DC670_SERVO_ZHU:
										DcServoGoTarget_flag=0;
										
										OriginalSize=OriginalSize+InputSize-CurrentSize;
										CurrentSize=InputSize;
										ServoSetCommd(SERVO_COMMD_P,STAT_30H,CurrentSize);
											break;
									case MOTOR_AC_SERVO:	
										OriginalSize=OriginalSize+InputSize-CurrentSize;
										CurrentSize=InputSize;
											break;
									}		
								
								//if(InputSize!=TargetSize_temp)
								//	{
									SaveOriginalSize();  //保存原点尺寸
								//	}
								
								if(InputTouch_flag==1)  //	  触摸 下
									CalcuInClear_exec();     //清除 计算器
								//-----------------自动返回 主模式	
								CurrentArea_recover2(MIDDLE_PAGE_X , MIDDLE_PAGE_Y,  M_PAGE_WIDE, M_PAGE_HIGH);
								if(WorkMode==AUTO_RULER_MODE)   //自动下
									{
									WorkMode=AUTO_MODE;//返回    自动 主模式
									PaperCutEnb_signal=1;
									PressCircle_mode=0;
									Auto_dis(AUTO_X, AUTO_Y); //自动
									//PromptNum_dis();//输入范围
									//PromptDis_flag=1;
									}
								else if(WorkMode==MANUAL_RULER_MODE)  //手动下
									{
									WorkMode=MANUAL_MODE;//返回    手动 主模式
									Manual_dis(MANUAL_X,MANUAL_Y);//手动
									// PromptDis_flag=0;
									// GLCD_SetWindow_Fill( REMIND_WINDOW_X, REMIND_WINDOW_Y, REMIND_WINDOW_X+REMIND_LENGTH, REMIND_WINDOW_Y+30, 0xfffff, 0xffff);//提示框
									}
								else if(WorkMode==SELF_RULER_MODE)   //自刀下	
									{
									WorkMode=SELF_CUT_MODE;//返回    自刀 主模式
									PaperCutEnb_signal=1;
									AutoKnife_dis(SELF_KNIFE_X,SELF_KNIFE_Y); //自刀
									}
								PromptNum_dis();//输入范围
								PromptDis_flag=1;
								}
							ClrInput_function();//清零 输入框
							}
						else
							{						 
							}
							 break;
					case AUTO_TOOLS_MODE://自动  参数设置
					case SELF_TOOLS_MODE://自刀  参数设置
					case MANUAL_TOOLS_MODE:// 手动 参数模式
						if(num_cou>0)
							{
							if((CheckInputNums()==1))
								{
								if(PramSel_Page<1)	//page 1
									{
								if(Para_sel<8)
									{
									if(Unit==UNIT_MM)
										{
										if(Para_sel!=5)
											input_temp=InputSize/100*100;
										else
											input_temp=InputSize;
										}
									else
										{
										input_temp=InputSize*2.54;
										}
									}
								else	
									input_temp=InputSize;
								switch(Para_sel)
									{
									case 0: //前极限		
										if((input_temp>=FRONT_LIM_MIN)&&(input_temp<=FRONT_LIM_MAX))
											{
											FrontLimit=input_temp;
											SaveFrontLimit();
											if(OIN4_PIN==0)  //托板 信号
												{
												Size_MIN=FrontLimit;
												if(Unit==UNIT_MM)
													Size_MIN_num=Size_MIN;
												else
													Size_MIN_num=Size_MIN*100/254;
												}
											if(Para_sel<6)
												{
												ParameterPage_dis(Para_sel++, 0);
												ParameterPage_dis(Para_sel, 1);
												}
											}
										else
											{
											PromptDis_flag=0;
											GLCD_SetWindow_Fill( REMIND_WINDOW_X, REMIND_WINDOW_Y, REMIND_WINDOW_X+REMIND_LENGTH, REMIND_WINDOW_Y+30, 0xfffff, 0xffff);//提示框
											switch(Language)
												{
												case CHN_HAN:
													Printf24("输入尺寸超过极限!",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,RED_COLOR,0,0xffff);
														break;
												case ENGLISH:
													Printf24("Data exceeds limit!",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,RED_COLOR,0,0xffff);
												break;
												}
											if(InputTouch_flag==1)   //触摸下
												{
												ClearCalculatorInput(); //清零计算器 输入
												num_cou=0;
												}	
											}
											break;
									case 1: //中极限
										if((input_temp>=MIDD_LIM_MIN)&&(input_temp<=MIDD_LIM_MAX))
											{
											MiddleLimit=input_temp;
											SaveMiddleLimit();
											if(OIN4_PIN!=0)  //托板 信号
												{
												Size_MIN=MiddleLimit;
												if(Unit==UNIT_MM)
													Size_MIN_num=Size_MIN;
												else
													Size_MIN_num=Size_MIN*100/254;
												}
											if(Para_sel<6)
												{
												ParameterPage_dis(Para_sel++, 0);
												ParameterPage_dis(Para_sel, 1);
												}
											}
										else
											{
											PromptDis_flag=0;
											GLCD_SetWindow_Fill( REMIND_WINDOW_X, REMIND_WINDOW_Y, REMIND_WINDOW_X+REMIND_LENGTH, REMIND_WINDOW_Y+30, 0xfffff, 0xffff);//提示框
											switch(Language)
												{
												case CHN_HAN:
													Printf24("输入尺寸超过极限!",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,RED_COLOR,0,0xffff);
														break;
												case ENGLISH:
													Printf24("Data exceeds limit!",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,RED_COLOR,0,0xffff);
												break;
												}
											if(InputTouch_flag==1)   //触摸下
												{
												ClearCalculatorInput(); //清零计算器 输入
												num_cou=0;
												}	
											}	
											break;	
									case 2: //后极限
										if((input_temp>=BACK_LIM_MIN)&&(input_temp<=BACK_LIM_MAX))
											{
											BackLimit=input_temp;
											SaveBackLimit();
											Size_MAX=BackLimit;
											if(Unit==UNIT_MM)
												Size_MAX_num=Size_MAX;
											else
												Size_MAX_num=Size_MAX*100/254;
											if(Para_sel<6)
												{
												ParameterPage_dis(Para_sel++, 0);
												ParameterPage_dis(Para_sel, 1);
												}
											}
										else
											{
											PromptDis_flag=0;
											GLCD_SetWindow_Fill( REMIND_WINDOW_X, REMIND_WINDOW_Y, REMIND_WINDOW_X+REMIND_LENGTH, REMIND_WINDOW_Y+30, 0xfffff, 0xffff);//提示框
											 switch(Language)
												{
												case CHN_HAN:
													Printf24("输入尺寸超过极限!",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,RED_COLOR,0,0xffff);
														break;
												case ENGLISH:
													Printf24("Data exceeds limit!",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,RED_COLOR,0,0xffff);
												break;
												}
											if(InputTouch_flag==1)   //触摸下
												{
												ClearCalculatorInput(); //清零计算器 输入
												num_cou=0;
												}	
											}
											break;
									case 5: //提前量
										if((input_temp>=1)&&(input_temp<=100))
											{
											Aheader=input_temp;
											SaveAheader();
											if(Para_sel<6)
												{
												ParameterPage_dis(Para_sel++, 0);
												ParameterPage_dis(Para_sel, 1);
												}
											}
										else
											{
											PromptDis_flag=0;
											GLCD_SetWindow_Fill( REMIND_WINDOW_X, REMIND_WINDOW_Y, REMIND_WINDOW_X+REMIND_LENGTH, REMIND_WINDOW_Y+30, 0xfffff, 0xffff);//提示框
											switch(Language)
												{
												case CHN_HAN:
													Printf24("输入尺寸超过极限!",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,RED_COLOR,0,0xffff);
														break;
												case ENGLISH:
													Printf24("Data exceeds limit!",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,RED_COLOR,0,0xffff);
												break;
												}
											if(InputTouch_flag==1)   //触摸下
												{
												ClearCalculatorInput(); //清零计算器 输入
												num_cou=0;
												}	
											}
											break;	
									case 6:  //自动推纸  距离
										if(input_temp<=AUTO_PUSH_DISTAN)
											{
											AutoPushDistance=input_temp;
											SavePushDistance();
											ParameterPage_dis(Para_sel, 1);
											}
										else
											{
											PromptDis_flag=0;
											GLCD_SetWindow_Fill( REMIND_WINDOW_X, REMIND_WINDOW_Y, REMIND_WINDOW_X+REMIND_LENGTH, REMIND_WINDOW_Y+30, 0xfffff, 0xffff);//提示框
											switch(Language)
												{
												case CHN_HAN:
													Printf24("输入尺寸超过极限!",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,RED_COLOR,0,0xffff);
														break;
												case ENGLISH:
													Printf24("Data exceeds limit!",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,RED_COLOR,0,0xffff);
												break;
												}
											if(InputTouch_flag==1)   //触摸下
												{
												ClearCalculatorInput(); //清零计算器 输入
												num_cou=0;
												}	
											}	
											break;	
									case 8:		//最大运行 速度
										if((MotorType>=MOTOR_DC_SERVO)&&(MotorType<=MOTOR_DC670_SERVO_ZHU))   //------------------直流  伺服
											{
											if(MotorType==MOTOR_DC670_SERVO_ZHU)
												{
												ServMaxSpd1=5;ServMaxSpd2=20;
												}
											else
												{
												ServMaxSpd1=13;ServMaxSpd2=20;
												}
											if((input_temp>=ServMaxSpd1)&&(input_temp<=ServMaxSpd2))
												{
												ServoSpeed_order=input_temp;
												SaveMovSpeed();
												ServoSetCommd(SERVO_COMMD_S,STAT_30H,SERVO_SPEED[ServoSpeed_order]);  //设定伺服最大速
												if(InputTouch_flag==1)   //触摸下
													{
													CalcuInClear_exec();     //清除 计算器
													}	
												ParameterPage_dis(Para_sel, 1);
												}
											else
												{
												PromptDis_flag=0;
												GLCD_SetWindow_Fill( REMIND_WINDOW_X, REMIND_WINDOW_Y, REMIND_WINDOW_X+REMIND_LENGTH, REMIND_WINDOW_Y+30, 0xfffff, 0xffff);//提示框
												switch(Language)
													{
													case CHN_HAN:
														Printf24("输入数据超过极限!",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,RED_COLOR,0,0xffff);
															break;
													case ENGLISH:
														Printf24("Data exceeds limit!",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,RED_COLOR,0,0xffff);
													break;
													}
												if(InputTouch_flag==1)   //触摸下
													{
													ClearCalculatorInput(); //清零计算器 输入
													num_cou=0;
													}	
												}	
											}
										else if(MotorType==MOTOR_AC_SERVO)  //*************交流 伺服
											{
												if(input_temp<=32)
												{
												AC_MotorSPD=input_temp;
												SaveACMotorSpeed();   //交流伺服 速度
												GetAC_MotorSpeed();  //交流伺服  速度判定
												if(InputTouch_flag==1)   //触摸下
													{
													CalcuInClear_exec();     //清除 计算器
													}	
												ParameterPage_dis(Para_sel, 1);
												}
											else
												{
												PromptDis_flag=0;
												GLCD_SetWindow_Fill( REMIND_WINDOW_X, REMIND_WINDOW_Y, REMIND_WINDOW_X+REMIND_LENGTH, REMIND_WINDOW_Y+30, 0xfffff, 0xffff);//提示框
												switch(Language)
													{
													case CHN_HAN:
														Printf24("输入数据超过极限!",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,RED_COLOR,0,0xffff);
															break;
													case ENGLISH:
														Printf24("Data exceeds limit!",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,RED_COLOR,0,0xffff);
													break;
													}
												if(InputTouch_flag==1)   //触摸下
													{
													ClearCalculatorInput(); //清零计算器 输入
													num_cou=0;
													}	
												}
											}
										else
										{//新加 误差范围
										if((input_temp>=20)&&(input_temp<=100))
											{
											DisWuCha=input_temp;
											SaveDisWuCha();
											ParameterPage_dis(Para_sel, 0);
											ParameterPage_dis(Para_sel, 1);

											}
										else
											{
											PromptDis_flag=0;
											GLCD_SetWindow_Fill( REMIND_WINDOW_X, REMIND_WINDOW_Y, REMIND_WINDOW_X+REMIND_LENGTH, REMIND_WINDOW_Y+30, 0xfffff, 0xffff);//提示框
											switch(Language)
												{
												case CHN_HAN:
													Printf24("输入尺寸超过极限!",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,RED_COLOR,0,0xffff);
														break;
												case ENGLISH:
													Printf24("Data exceeds limit!",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,RED_COLOR,0,0xffff);
												break;
												}
											if(InputTouch_flag==1)   //触摸下
												{
												ClearCalculatorInput(); //清零计算器 输入
												num_cou=0;
												}	
											}											
											
										}
										
											break;
									case 9:		//点动 速度
										if((input_temp<=20)&&(input_temp>=10))
											{
											JogSpeed_order=input_temp;
											SaveJogSpeed();
											//ServoSetCommd(SERVO_COMMD_S,STAT_30H,SERVO_SPEED[ServoSpeed_order]);  //设定伺服最大速
											if(InputTouch_flag==1)   //触摸下
												{
												CalcuInClear_exec();     //清除 计算器
												}	
											ParameterPage_dis(Para_sel, 1);
											}
										else
											{
											PromptDis_flag=0;
											GLCD_SetWindow_Fill( REMIND_WINDOW_X, REMIND_WINDOW_Y, REMIND_WINDOW_X+REMIND_LENGTH, REMIND_WINDOW_Y+30, 0xfffff, 0xffff);//提示框
											switch(Language)
												{
												case CHN_HAN:
													Printf24("输入数据超过极限!",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,RED_COLOR,0,0xffff);
														break;
												case ENGLISH:
													Printf24("Data exceeds limit!",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,RED_COLOR,0,0xffff);
												break;
												}
											if(InputTouch_flag==1)   //触摸下
												{
												ClearCalculatorInput(); //清零计算器 输入
												num_cou=0;
												}	
											}	
											break;		
									}
								}
								else//page 2
									{
									input_temp=InputSize;	
									switch(Para2_sel)
										{
										case 0:
											
											break;
										case 1:	//Jog-speed
											if((input_temp>0)&&(input_temp<=5))//
												{
												JogLevel=input_temp;
												SaveACJogLevel();
												ParameterPage2_dis(Para2_sel, 1);
												}
											break;	
										}
									}
								}
							else
								num_cou=0;
							if(InputTouch_flag==0)  //	 非 触摸计算器 下	
								ClrInput_function();//清零 输入框	
							}
							break;
					case MANUAL_SERVO_C_MODE:// 手动直流伺服 C 参数 
						if(num_cou>0)
							{
							if((CheckInputNums()==1))
								{
								input_temp=InputSize;
								switch(Para_sel)
									{
									case 0: //位置环增益	
										if((input_temp>=1)&&(input_temp<=99))
											{
											if(PositRing_Gain!=input_temp)
												{
												PositRing_Gain=input_temp;
												ServoSetCommd(SERVO_COMMD_C,STAT_11H,PositRing_Gain);
												}
											
											if(Para_sel<6)
												{
												ServoParameter_dis(Para_sel++, 0);
												ServoParameter_dis(Para_sel, 1);
												}
											}
										else
											{
											PromptDis_flag=0;
											GLCD_SetWindow_Fill( REMIND_WINDOW_X, REMIND_WINDOW_Y, REMIND_WINDOW_X+REMIND_LENGTH, REMIND_WINDOW_Y+30, 0xfffff, 0xffff);//提示框
											switch(Language)
												{
												case CHN_HAN:
													Printf24("输入数据超过极限!",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,RED_COLOR,0,0xffff);
														break;
												case ENGLISH:
													Printf24("Data exceeds limit!",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,RED_COLOR,0,0xffff);
												break;
												}
											if(InputTouch_flag==1)   //触摸下
												{
												ClearCalculatorInput(); //清零计算器 输入
												num_cou=0;
												}	
											}
											break;
									case 1: //位置环微分
										if((input_temp>=1)&&(input_temp<=99))
											{
											if(PositRing_Diff!=input_temp)
												{
												PositRing_Diff=input_temp;
												ServoSetCommd(SERVO_COMMD_C,STAT_21H,PositRing_Diff);
												}
											
											if(Para_sel<6)
												{
												ServoParameter_dis(Para_sel++, 0);
												ServoParameter_dis(Para_sel, 1);
												}
											}
										else
											{
											PromptDis_flag=0;
											GLCD_SetWindow_Fill( REMIND_WINDOW_X, REMIND_WINDOW_Y, REMIND_WINDOW_X+REMIND_LENGTH, REMIND_WINDOW_Y+30, 0xfffff, 0xffff);//提示框
											switch(Language)
												{
												case CHN_HAN:
													Printf24("输入数据超过极限!",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,RED_COLOR,0,0xffff);
														break;
												case ENGLISH:
													Printf24("Data exceeds limit!",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,RED_COLOR,0,0xffff);
												break;
												}
											if(InputTouch_flag==1)   //触摸下
												{
												ClearCalculatorInput(); //清零计算器 输入
												num_cou=0;
												}	
											}	
											break;	
									case 2: //位置环积分
										if((input_temp>=1)&&(input_temp<=99))
											{
											if(PositRing_Integral!=input_temp)
												{
												PositRing_Integral=input_temp;
												ServoSetCommd(SERVO_COMMD_C,STAT_31H,PositRing_Integral);
												}
												
											if(Para_sel<6)
												{
												ServoParameter_dis(Para_sel++, 0);
												ServoParameter_dis(Para_sel, 1);
												}
											}
										else
											{
											PromptDis_flag=0;
											GLCD_SetWindow_Fill( REMIND_WINDOW_X, REMIND_WINDOW_Y, REMIND_WINDOW_X+REMIND_LENGTH, REMIND_WINDOW_Y+30, 0xfffff, 0xffff);//提示框
											 switch(Language)
												{
												case CHN_HAN:
													Printf24("输入数据超过极限!",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,RED_COLOR,0,0xffff);
														break;
												case ENGLISH:
													Printf24("Data exceeds limit!",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,RED_COLOR,0,0xffff);
												break;
												}
											if(InputTouch_flag==1)   //触摸下
												{
												ClearCalculatorInput(); //清零计算器 输入
												num_cou=0;
												}	
											}
											break;
									case 3: //速度环增益
										if((input_temp>=1)&&(input_temp<=99))
											{
											if(SpeedRing_Gain!=input_temp)
												{
												SpeedRing_Gain=input_temp;
												ServoSetCommd(SERVO_COMMD_C,STAT_41H,SpeedRing_Gain);
												}
												
											if(Para_sel<6)
												{
												ServoParameter_dis(Para_sel++, 0);
												ServoParameter_dis(Para_sel, 1);
												}
											}
										else
											{
											PromptDis_flag=0;
											GLCD_SetWindow_Fill( REMIND_WINDOW_X, REMIND_WINDOW_Y, REMIND_WINDOW_X+REMIND_LENGTH, REMIND_WINDOW_Y+30, 0xfffff, 0xffff);//提示框
											switch(Language)
												{
												case CHN_HAN:
													Printf24("输入数据超过极限!",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,RED_COLOR,0,0xffff);
														break;
												case ENGLISH:
													Printf24("Data exceeds limit!",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,RED_COLOR,0,0xffff);
												break;
												}
											if(InputTouch_flag==1)   //触摸下
												{
												ClearCalculatorInput(); //清零计算器 输入
												num_cou=0;
												}	
											}
											break;	
									case 4:  //速度环微分
										if((input_temp>=1)&&(input_temp<=99))
											{
											if(SpeedRing_Diff!=input_temp)
												{
												SpeedRing_Diff=input_temp;
												ServoSetCommd(SERVO_COMMD_C,STAT_51H,SpeedRing_Diff);
												}
												
											if(Para_sel<6)
												{
												ServoParameter_dis(Para_sel++, 0);
												ServoParameter_dis(Para_sel, 1);
												}
											}
										else
											{
											PromptDis_flag=0;
											GLCD_SetWindow_Fill( REMIND_WINDOW_X, REMIND_WINDOW_Y, REMIND_WINDOW_X+REMIND_LENGTH, REMIND_WINDOW_Y+30, 0xfffff, 0xffff);//提示框
											switch(Language)
												{
												case CHN_HAN:
													Printf24("输入数据超过极限!",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,RED_COLOR,0,0xffff);
														break;
												case ENGLISH:
													Printf24("Data exceeds limit!",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,RED_COLOR,0,0xffff);
												break;
												}
											if(InputTouch_flag==1)   //触摸下
												{
												ClearCalculatorInput(); //清零计算器 输入
												num_cou=0;
												}	
											}	
											break;	
									case 5:		//速度环积分
										if((input_temp>=1)&&(input_temp<=99))
											{
											if(SpeedRing_Integral!=input_temp)
												{
												SpeedRing_Integral=input_temp;
												ServoSetCommd(SERVO_COMMD_C,STAT_61H,SpeedRing_Integral);
												}
												
											if(Para_sel<6)
												{
												ServoParameter_dis(Para_sel++, 0);
												ServoParameter_dis(Para_sel, 1);
												}
											}
										else
											{
											PromptDis_flag=0;
											GLCD_SetWindow_Fill( REMIND_WINDOW_X, REMIND_WINDOW_Y, REMIND_WINDOW_X+REMIND_LENGTH, REMIND_WINDOW_Y+30, 0xfffff, 0xffff);//提示框
											switch(Language)
												{
												case CHN_HAN:
													Printf24("输入数据超过极限!",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,RED_COLOR,0,0xffff);
														break;
												case ENGLISH:
													Printf24("Data exceeds limit!",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,RED_COLOR,0,0xffff);
												break;
												}
											if(InputTouch_flag==1)   //触摸下
												{
												ClearCalculatorInput(); //清零计算器 输入
												num_cou=0;
												}	
											}	
											break;
									case 6:		//减速比
										if((input_temp>=1)&&(input_temp<=3))
											{
											if(SpeedDown_Ratio!=input_temp)
												{
												SpeedDown_Ratio=input_temp;
												ServoSetScrew(Screw_Pitch ,SpeedDown_Ratio);  //螺距设定
												Save_PitchRatio();
												}
											ServoParameter_dis(Para_sel, 1);
											}
										else
											{
											PromptDis_flag=0;
											GLCD_SetWindow_Fill( REMIND_WINDOW_X, REMIND_WINDOW_Y, REMIND_WINDOW_X+REMIND_LENGTH, REMIND_WINDOW_Y+30, 0xfffff, 0xffff);//提示框
											switch(Language)
												{
												case CHN_HAN:
													Printf24("输入数据超过极限!",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,RED_COLOR,0,0xffff);
														break;
												case ENGLISH:
													Printf24("Data exceeds limit!",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,RED_COLOR,0,0xffff);
												break;
												}
											if(InputTouch_flag==1)   //触摸下
												{
												ClearCalculatorInput(); //清零计算器 输入
												num_cou=0;
												}	
											}	
											break;	
									case 7:		//螺距
										if((input_temp==10)||(input_temp==12))
											{
											if(Screw_Pitch!=input_temp)
												{
												Screw_Pitch=input_temp;
												ServoSetScrew(Screw_Pitch ,SpeedDown_Ratio);  //螺距设定
												Save_PitchRatio();
												}
											if(InputTouch_flag==1)   //触摸下
												{
												CalcuInClear_exec();     //清除 计算器
												}	
											ServoParameter_dis(Para_sel, 1);
											}
										else
											{
											PromptDis_flag=0;
											GLCD_SetWindow_Fill( REMIND_WINDOW_X, REMIND_WINDOW_Y, REMIND_WINDOW_X+REMIND_LENGTH, REMIND_WINDOW_Y+30, 0xfffff, 0xffff);//提示框
											switch(Language)
												{
												case CHN_HAN:
													Printf24("输入数据超过极限!",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,RED_COLOR,0,0xffff);
														break;
												case ENGLISH:
													Printf24("Data exceeds limit!",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,RED_COLOR,0,0xffff);
												break;
												}
											if(InputTouch_flag==1)   //触摸下
												{
												ClearCalculatorInput(); //清零计算器 输入
												num_cou=0;
												}	
											}	
											break;			
									}
								}
							else
								num_cou=0;
							if(InputTouch_flag==0)  //	 非 触摸计算器 下	
								ClrInput_function();//清零 输入框	
							}
							break;
					case MANUAL_CLOCK_MODE: //手动 时钟模式
						if(num_cou>0)
							{
							if((CheckInputNums()==1))
								{
								switch(Para_sel)
									{
									case 0:  //年
										if(InputSize<100)
											{
											Year=(Int8U)((InputSize/10)<<4|(InputSize%10));
											write_time();//-------------时间设定值保存写入
											TimeSetSel_dis(Para_sel++, 0);
											TimeSetSel_dis(Para_sel, 1);
											}	
											break;
									case 1: //月
										if((InputSize<13)&&(InputSize>0))
											{
											Month=(Int8U)((InputSize/10)<<4|(InputSize%10));
											write_time();//-------------时间设定值保存写入
											TimeSetSel_dis(Para_sel++, 0);
											TimeSetSel_dis(Para_sel, 1);
											}
											break;
									case 2:  //日
										if((InputSize<32)&&(InputSize>0))
											{
											Dom=(Int8U)((InputSize/10)<<4|(InputSize%10));
											write_time();//-------------时间设定值保存写入
											TimeSetSel_dis(Para_sel++, 0);
											TimeSetSel_dis(Para_sel, 1);
											}
											break;
									case 3: //小时
										if(InputSize<24)
											{
											Hour=(Int8U)((InputSize/10)<<4|(InputSize%10));
											write_time();//-------------时间设定值保存写入
											TimeSetSel_dis(Para_sel++, 0);
											TimeSetSel_dis(Para_sel, 1);
											}	
											break;
									case 4: //分钟
										if(InputSize<60)
											{
											Min=(Int8U)((InputSize/10)<<4|(InputSize%10));
											write_time();//-------------时间设定值保存写入
											TimeSetSel_dis(Para_sel, 1);
											}
										
											break;		
									}
								if(Year<Year_before)//时间 提前 判断------------------
									TimeAhead_flag=1;	
								else if(Year==Year_before)
									{
									if(Month<Month_before)
										{
										TimeAhead_flag=1;
										}
									else if(Month==Month_before)	
										{
										if(Dom<Day_before)
											TimeAhead_flag=1;
										else
											TimeAhead_flag=0;
										}
									else
										TimeAhead_flag=0;
									}
								else
									{
									TimeAhead_flag=0;
									}
									
								if(TimeAhead_flag==1) //时间 提前
									{
									Start_days.year=Year;
									Start_days.month=Month;
									Start_days.day=Dom;
									SaveWorkDays();//起始 时间保存
									
									if(FirstDayValid_flag==1)// 剩余天数修改
										{		 
										if(FirstDays>Past_days)
											{
											Past_days++;
											FirstDays-=Past_days;
											}
										else
											{
											FirstDays=0;
											}
										SaveFirstDays();	
										}
									else if(SecondDayValid_flag==1)
										{	
										if(SecondDays>Past_days)
											{
											Past_days++;
											SecondDays-=Past_days;
											}
										else
											SecondDays=0;
										SaveSecondDays();
										}
									}
								}
							else
								num_cou=0;
							if(InputTouch_flag==0)  //	 非 触摸计算器 下	
								ClrInput_function();//清零 输入框 
							}
							break;
					case MANUAL_PULSE_MODE://手动 脉冲当量  设定保存
						 if(num_cou>0)
							{
							if(CheckInputNums()==1)
								{
								if(InputSize<12)
									{
									if(InputTouch_flag==1)  //	  触摸 下
										CalcuInClear_exec();     //清除 计算器
									SelPulseDegree_dis(Para_sel, 0); //脉冲设定
									Para_sel=InputSize;
									SelPulseDegree_dis(Para_sel,1);
									}
								}
							else
								num_cou=0;
							if(InputTouch_flag==0)  //	 非 触摸计算器 下	
								ClrInput_function();//清零 输入框 
							}
						 else
							{
							if(InputTouch_flag==0)  //	非  触摸 下
								{
								Pulse_degree=Para_sel;
								Save_degree();
								WorkMode=MANUAL_MODE;//返回    ---------手动 主模式
								Para_sel=0;
								CurrentArea_recover2(MIDDLE_PAGE_X , MIDDLE_PAGE_Y, M_PAGE_WIDE, M_PAGE_HIGH);
								Manual_dis(MANUAL_X,MANUAL_Y);//手动
								PromptNum_dis();//输入范围
								PromptDis_flag=1;
								}
							}
							break;
					case MANUAL_PASS_MODE: //手动 密码设置
						 if(num_cou>0)
							{
							if(PassModeIn_flag==0)  //密码确认
								{
								PassModeIn_flag=1;
								if(CheckInputNums()==1)
									{
									if(InputSize==PASS_MOD_CODE) //密码正确
										{
										if(InputTouch_flag==1)  //	  触摸 下
											CalcuInClear_exec();     //清除 计算器
										PassSet_dis(); //密码 设置界面
										Para_sel=0;
										PassModeOk_flag=1;
										}
									}
								}
							else            //天数 设定
								{
								if(PassModeOk_flag==1)  //已进入  密码模式
									{
									if(CheckInputNums()==1)
										{
										if((InputSize>0)&&(InputSize<=300)) //数据有效 保存
											{
											if(Para_sel==0)  //第一次 时间
												{
												FirstDays=InputSize;
												SaveFirstDays();
												if(FirstDayValid_flag==1)
													{
													Start_days.year=Year;
													Start_days.month=Month;
													Start_days.day=Dom;
													SaveWorkDays();//起始 时间保存
													}
												}
											else   //第二次时间
												{
												SecondDays=InputSize;
												SaveSecondDays();
												}
											PassDaysSet_dis(Para_sel, 1);
											}
										}
									}	
								}
							if(InputTouch_flag==0)  //	 非 触摸计算器 下	
								ClrInput_function();//清零 输入框
							}
							break;
					case AUTO_TO_SELF_MODE:   //自动-->自刀过度 模式
						if(InputTouch_flag==1)  //	  触摸 下
							CalcuInClear_exec();     //清除 计算器
						Int16U color=0xef9f;
						if(LastAutoKnife_order<2)    //--------首次  进入  不提示
							{
							WorkMode=SELF_CUT_MODE;  //进入   ----------自刀主 模式
							CurrentArea_recover2(SELF_PROMP_X,SELF_PROMP_Y,SELF_PROMP_X+300,SELF_PROMP_Y+120);
							AutoKnife_dis(SELF_KNIFE_X,SELF_KNIFE_Y);//自刀
							//------------返回第一刀
							ClrInput_function();//清零 输入框 
							CursorMov_dis(cursor_row, 0);//红色光标消失
							cursor_row=0;
							CursorMov_dis(cursor_row, 1);//红色光标显示
							Knife_order=1;//
							Size_1page_dis(Knife_order,0);//一页尺寸显示
							if(Knife_order<=Knife_sum)
								StepOrder_dis(Knife_order);//步骤更新 
							CancelCutflagButton_dis(); //取消显示  刀 标记 按钮
							GLCD_SetWindow_Fill(F5_PRE_FLG_X,F5_PRE_FLG_Y,F5_PRE_FLG_X+48,F5_PRE_FLG_Y+48,color,color);//空白F5 flag
							}
						else  //重新 进入自刀模式
							{
							if(ReEnterAutoKnife_dis==0) //提示  显示
								{
								ReEnterAutoKnife_dis=1;
								AutoCutLastKnifeLoad_dis();
								}
							else
								{
								ReEnterAutoKnife_dis=0;
								
								WorkMode=SELF_CUT_MODE;  //进入   ----------自刀主 模式
								CurrentArea_recover2(SELF_PROMP_X,SELF_PROMP_Y,SELF_PROMP_X+300,SELF_PROMP_Y+120);
								AutoKnife_dis(SELF_KNIFE_X,SELF_KNIFE_Y);//自刀
								//------------返回之前刀
								Knife_order=LastAutoKnife_order;//
								ClrInput_function();//清零 输入框 
								CursorMov_dis(cursor_row, 0);//红色光标消失
								cursor_row=0;
								CursorMov_dis(cursor_row, 1);//红色光标显示
								
								Size_1page_dis(Knife_order,0);//一页尺寸显示
								if(Knife_order<=Knife_sum)
									StepOrder_dis(Knife_order);//步骤更新 
								LastAutoKnife_order=1;
								CancelCutflagButton_dis(); //取消显示  刀 标记 按钮
								GLCD_SetWindow_Fill(F5_PRE_FLG_X,F5_PRE_FLG_Y,F5_PRE_FLG_X+48,F5_PRE_FLG_Y+48,color,color);//空白F5 flag
								}
							}
							break;
					case MANUAL_MODE:   //手动主模式  确认无效
						if(num_cou>0)
							{
							PromptDis_flag=0;
							GLCD_SetWindow_Fill( REMIND_WINDOW_X, REMIND_WINDOW_Y, REMIND_WINDOW_X+REMIND_LENGTH, REMIND_WINDOW_Y+30, 0xfffff, 0xffff);//提示框
							switch(Language)
								{
								case CHN_HAN:
										Printf24("手动模式下,请按运行键!",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,RED_COLOR,0,0xffff);
											break;
								case ENGLISH:
										Printf24("On this mode,press RUN key!",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,RED_COLOR,0,0xffff);
											break;
								}
							}
						
							break;
					}			
			 }
		  else
			 {
									
			 }
		  }
		else
		  {
		  switch(MotorType)
				{
				case MOTOR_FREQ_5_SPD_RST:
				case MOTOR_FREQ_3_SPD:
				case MOTOR_FREQ_3_SPD_RST:
					 if(StartCheck_mode==1)  //推纸器 复位启动
						 {
						 MoveSpeed=3;
						 SetMotorSpeed(MoveSpeed);//中速
						 MoveForward();//前进
						 PusherResetTime=0;
						 CurrentArea_recover3(PUSH_RESET_PROMPT_X1, PUSH_RESET_PROMPT_Y1, PUSH_RESET_PROMPT_WIDE, PUSH_RESET_PROMPT_HIGH);
						 StartCheck_mode++;
						 PushRstKey_flag=1;
						 }
					 else if(StartCheck_mode==4)
						 {
						 if(PassCheckDis_flag==1) //开机 密码下
							 {
							 if(num_cou>0)
								{
								if(CheckInputNums()==1)
									{
									if(StartPassInput_flag==0)
										{
										StartPassInput_flag=1;
										if(InputSize==PassCode)//密码正确   
											{
											PassCodeEn_flag=0;
											//PassCheckDis_flag=0;
											
										//-----------时间更新
											if(FirstDayValid_flag==1) //首次 时间限制 有效
												{
												FirstDayValid_flag=0;
												SaveFirstDays_flag(); //清除 首次有效
												if(SecondDayValid_flag==1) //第二次 计时开始
													{
													Start_days.year=Year;
													Start_days.month=Month;
													Start_days.day=Dom;
													SaveWorkDays();//起始 时间保存
													}
												}
											else if(SecondDayValid_flag==1)    //第二次 有效
												{
												SecondDayValid_flag=0;
												SaveSecondDays_flag();
												}
											//---------开机 工作
											switch(Language)
												{
												case CHN_HAN:
															Printf24("密码输入正确！欢迎继续使用！  ",PASSCODE_X,PASSCODE_Y,RED_COLOR,1,0xffff);
																break;
												case ENGLISH:
															Printf24("Password is correct,Welcome to use!    ",PASSCODE_X,PASSCODE_Y,RED_COLOR,1,0xffff);
																break;
												}
											if(StartCheck_mode==4)
												{
												MoveSpeed=2;
												SetMotorSpeed(MoveSpeed);//中高速
												MoveBack(); //后退
												CurrentArea_recover2(REMIND_WINDOW_X, REMIND_WINDOW_Y, START_PROM_WIDE, START_PROM_HIGH);
												switch(Language)
													{
													case CHN_HAN:
															Printf24("运行....",RUN_DIS_X,RUN_DIS_Y,RED_COLOR,1,0xffff);
																break;
													case ENGLISH:
															Printf24("Runing....",RUN_DIS_X,RUN_DIS_Y,RED_COLOR,1,0xffff);
																break;
													}
												StartCheck_mode++;
												}
											}
										}
								
									}
								 for(num_cou=0;num_cou<8;num_cou++)
									{
									Size_temp[num_cou++]=0;
									}
								 num_cou=0;	
								}
							 }
						 }
						break;
				case MOTOR_DC_SERVO:
				case MOTOR_DC670_SERVO:
				case MOTOR_DC670_SERVO_ZHU:
					if(StartCheck_mode==1)
						 {
						 if(PassCheckDis_flag==1) //开机 密码下
							 {
							 if(num_cou>0)
								{
								if(CheckInputNums()==1)
									{
									if(StartPassInput_flag==0)
										{
										StartPassInput_flag=1;
										if(InputSize==PassCode)//密码正确   
											{
											PassCodeEn_flag=0;
											//PassCheckDis_flag=0;
											
										//-----------时间更新
											if(FirstDayValid_flag==1) //首次 时间限制 有效
												{
												FirstDayValid_flag=0;
												SaveFirstDays_flag(); //清除 首次有效
												if(SecondDayValid_flag==1) //第二次 计时开始
													{
													Start_days.year=Year;
													Start_days.month=Month;
													Start_days.day=Dom;
													SaveWorkDays();//起始 时间保存
													}
												}
											else if(SecondDayValid_flag==1)    //第二次 有效
												{
												SecondDayValid_flag=0;
												SaveSecondDays_flag();
												}
											//---------开机 工作
											switch(Language)
												{
												case CHN_HAN:
															Printf24("密码输入正确！欢迎继续使用！  ",PASSCODE_X,PASSCODE_Y,RED_COLOR,1,0xffff);
																break;
												case ENGLISH:
															Printf24("Password is correct,Welcome to use!    ",PASSCODE_X,PASSCODE_Y,RED_COLOR,1,0xffff);
																break;
												}
												
											
											CurrentSize=OriginalSize;
											//if(SearchZero_flag==0)   //未归0
											ServoSetCommd(SERVO_COMMD_R,STAT_30H,CurrentSize);  //启动寻零
											CurrentArea_recover2(REMIND_WINDOW_X, REMIND_WINDOW_Y, START_PROM_WIDE, START_PROM_HIGH);
											switch(Language)
												{
												case CHN_HAN:
														Printf24("运行....",RUN_DIS_X,RUN_DIS_Y,RED_COLOR,1,0xffff);
															break;
												case ENGLISH:
														Printf24("Runing....",RUN_DIS_X,RUN_DIS_Y,RED_COLOR,1,0xffff);
															break;
												}
											StartCheck_mode++;	
											}
										}
								
									}
								 for(num_cou=0;num_cou<8;num_cou++)
									{
									Size_temp[num_cou++]=0;
									}
								 num_cou=0;	
								}
							 }
						 }
						break;
				case MOTOR_AC_SERVO:
					if(StartCheck_mode==1)  //推纸器 复位启动
						{
						ACMotorGoForward();//前进
						// PusherResetTime=0;
						qianjincn=0;
						 CurrentArea_recover3(PUSH_RESET_PROMPT_X1, PUSH_RESET_PROMPT_Y1, PUSH_RESET_PROMPT_WIDE, PUSH_RESET_PROMPT_HIGH);
						 StartCheck_mode++;
						 PushRstKey_flag=1;
						}
					else if(StartCheck_mode==4)//if(StartCheck_mode==2)
						 {
						 if(PassCheckDis_flag==1) //开机 密码下
							 {
							 if(num_cou>0)
								{
								if(CheckInputNums()==1)
									{
									if(StartPassInput_flag==0)
										{
										StartPassInput_flag=1;
										if(InputSize==PassCode)//密码正确   
											{
											PassCodeEn_flag=0;
											//PassCheckDis_flag=0;
											
										//-----------时间更新
											if(FirstDayValid_flag==1) //首次 时间限制 有效
												{
												FirstDayValid_flag=0;
												SaveFirstDays_flag(); //清除 首次有效
												if(SecondDayValid_flag==1) //第二次 计时开始
													{
													Start_days.year=Year;
													Start_days.month=Month;
													Start_days.day=Dom;
													SaveWorkDays();//起始 时间保存
													}
												}
											else if(SecondDayValid_flag==1)    //第二次 有效
												{
												SecondDayValid_flag=0;
												SaveSecondDays_flag();
												}
											//---------开机 工作
											switch(Language)
												{
												case CHN_HAN:
															Printf24("密码输入正确！欢迎继续使用！  ",PASSCODE_X,PASSCODE_Y,RED_COLOR,1,0xffff);
																break;
												case ENGLISH:
															Printf24("Password is correct,Welcome to use!    ",PASSCODE_X,PASSCODE_Y,RED_COLOR,1,0xffff);
																break;
												}
												
											
											ACServoMoveBack_MID_SPD();  //交流伺服  中速后退
											CurrentArea_recover2(REMIND_WINDOW_X, REMIND_WINDOW_Y, START_PROM_WIDE, START_PROM_HIGH);
											switch(Language)
												{
												case CHN_HAN:
														Printf24("运行....",RUN_DIS_X,RUN_DIS_Y,RED_COLOR,1,0xffff);
															break;
												case ENGLISH:
														Printf24("Runing....",RUN_DIS_X,RUN_DIS_Y,RED_COLOR,1,0xffff);
															break;
												}
											StartCheck_mode++;	
											}
										}
								
									}
								 for(num_cou=0;num_cou<8;num_cou++)
									{
									Size_temp[num_cou++]=0;
									}
								 num_cou=0;	
								}
							 }
						 }
						break;
				}	
		 
		  }	
  	     break;          
    case DENGFENG_KEY_CODE:  //向下箭头按键**************下翻页
		if(WorkStart_flag==1)
		  {
		  if(Run_flag==0)
			 {
			 switch(WorkMode)
				{
				case PROG_MODE://编程画面下
				case TEACH_MODE://示教画面下
				case AUTO_MODE://自动主画面下
				case AUTO_PLUS_MODE:  //F3++
				case AUTO_MINUS_MODE:// F4--
				case SELF_CUT_MODE://自刀主画面下
				case SELF_PLUS_MODE:  //自刀F3++
				case SELF_MINUS_MODE://自刀 F4--
					if((Knife_order==Knife_sum)&&(Knife_order==1))
						{
						pKnife_data=(pInt8U)&OneKnife_data;
						GetOneKnife_datas(Pro_data.pro_num, Knife_order, pKnife_data);//
						if((OneKnife_data.size>=Size_MIN_num)&&(OneKnife_data.size<=Size_MAX_num))
							CursorDown_inTable();//**** 光标下移 显示 数据
						}
					else
						CursorDown_inTable();//**** 光标下移 显示 数据
						   break;
				case PROG_LABEL_MODE://标签 下--------------------------
				case TEACH_LABEL_MODE://标签 下--------------------------
					 if(PorgSet_sel<2)
						{
						LabelSel_dis(PorgSet_sel,0);PorgSet_sel++;
						LabelSel_dis(PorgSet_sel,1);
						}
							break;
				case PROG_DIVIDE_MODE://等分 下--------------------------
				case TEACH_DIVIDE_MODE://等分 下--------------------------
					 if(PorgSet_sel<1)
						{
						DivideSel_dis(PorgSet_sel,0);PorgSet_sel++;
						DivideSel_dis(PorgSet_sel,1);
						}
							break;
				case PROG_PRO_MODE:    //程序选择----------------------
				case TEACH_PRO_MODE:    //程序选择----------------------
					if(InputTouch_flag==0)  //	 非 触摸计算器 下
						{
						  if(Pro_num>=MAIX_PROG)//返回第一个 pro
							  {
							  Pro_num=1;
							  CursorMov_dis(cursor_temp,0);//光标
							  cursor_temp=0;
							  CursorMov_dis(cursor_temp,1);//
							  Prog_1page_dis(Pro_num, 0);//===程序---数据显示
							  }
						  else
							  {
							  Pro_num++;
							  if(cursor_temp<(PAGE2_KNIFE-1))
								 {
								 CursorMov_dis(cursor_temp,0);//光标
								 cursor_temp++;
								 CursorMov_dis(cursor_temp,1);//
								 }
							  else// 下一页
								 {
								 CursorMov_dis(cursor_temp,0);//光标
								 cursor_temp=0;
								 CursorMov_dis(cursor_temp,1);//
								 Prog_1page_dis(Pro_num, 0);//===程序---数据显示
								 }
							  }
						}
						     break;
				case AUTO_TOOLS_MODE://  参数设置  下移
				case SELF_TOOLS_MODE://  参数设置  下移
				case MANUAL_TOOLS_MODE:// 手动 参数模式
					if(InputTouch_flag==0)  //	 非 触摸计算器 下
						{
						if((MotorType>=MOTOR_DC_SERVO)&&(MotorType<=MOTOR_DC670_SERVO_ZHU))
							{
							if(PramSel_Page<1)	//page 1
								{
								if(Para_sel<9)
									{
									ParameterPage_dis(Para_sel++, 0);
									ParameterPage_dis(Para_sel, 1);
									}
								else
									{
									PramSel_Page++;
									ToolsPage2_dis(); //参数 page2
									}
								}
							else	//page 2
								{
								if(Para2_sel<4)
									{
									ParameterPage2_dis(Para2_sel++, 0);
									ParameterPage2_dis(Para2_sel, 1);
									}
								}
							}
						else if(MotorType==MOTOR_AC_SERVO)
							{
							if(PramSel_Page<1)	//page 1
								{
								if(Para_sel<8)
									{
									ParameterPage_dis(Para_sel++, 0);
									ParameterPage_dis(Para_sel, 1);
									}
								else
									{
									PramSel_Page++;
									ToolsPage2_dis(); //参数 page2
									}
								}
							else	//page 2
								{
								if(Para2_sel<4)
									{
									ParameterPage2_dis(Para2_sel++, 0);
									ParameterPage2_dis(Para2_sel, 1);
									}
								
								}
							}
						else
							{
							if(PramSel_Page<1)	//page 1
								{
								if(Para_sel<8)
									{
									ParameterPage_dis(Para_sel++, 0);
									ParameterPage_dis(Para_sel, 1);
									}
								else
									{
									PramSel_Page++;
									ToolsPage2_dis(); //参数 page2
									}
								}
							else	//page 2
								{
								if(Para2_sel<4)
									{
									ParameterPage2_dis(Para2_sel++, 0);
									ParameterPage2_dis(Para2_sel, 1);
									}
								
								}
							}
						}
					else
						{
						if(Para_sel<6)
							{
							ParameterPage_dis(Para_sel++, 0);
							ParameterPage_dis(Para_sel, 1);
							}
						}
							break;
				case MANUAL_SERVO_C_MODE:// 手动直流伺服 C 参数 
					 if(InputTouch_flag==0)  //	 非 触摸计算器 下
						{
						if(Para_sel<7)
							{
							ServoParameter_dis(Para_sel++, 0);
							ServoParameter_dis(Para_sel, 1);
							}
						}
					else
						{
						if(Para_sel<6)
							{
							ServoParameter_dis(Para_sel++, 0);
							ServoParameter_dis(Para_sel, 1);
							}
						}
						     break;
				case MANUAL_CLOCK_MODE: //手动 时钟模式	
					 if(Para_sel<4)
						{
						TimeSetSel_dis(Para_sel++, 0);
						TimeSetSel_dis(Para_sel, 1);
						}
						     break;
				case MANUAL_PULSE_MODE://手动 脉冲当量	
					 if(Para_sel<11)
						{
						SelPulseDegree_dis(Para_sel++, 0); //脉冲设定
						SelPulseDegree_dis(Para_sel, 1);
						}
							break;
				case MANUAL_PASS_MODE: //手动 密码设置
					 if(PassModeOk_flag==1)
						{
						if(Para_sel<1)
							{
							PassDaysSet_dis(Para_sel++, 0); //天数
							PassDaysSet_dis(Para_sel, 1); //天数
							}
						}
						break;
				}			
			 }
		 
		  } 
		else
		  {
		  if(Board_TestMod==TEST_HELP)
			 {
			 if(Manual_page<1)        //下一页  帮助
				{
				Manual_page++;
				Comment_dis_page(Manual_page);
				}
			 }
		  }
  	     break;         
	case DENGJU_KEY_CODE:  //向上箭头按键**************上翻页
		if(WorkStart_flag==1)
		  {
		  if(Run_flag==0)
			 {
			switch(WorkMode)
				{
				case PROG_MODE://编程画面下
				case TEACH_MODE://示教画面下
				case AUTO_MODE://自动主画面下
				case AUTO_PLUS_MODE:  //F3++
				case AUTO_MINUS_MODE:// F4--
				case SELF_CUT_MODE://自刀主画面下
				case SELF_PLUS_MODE:  //自刀F3++
				case SELF_MINUS_MODE://自刀 F4--
					if(Knife_order>1)
						{
						Knife_order--;
						if(cursor_row>0)
							{
							CursorMov_dis(cursor_row, 0);//红色光标消失
							OneKnifeDataSel_dis(Knife_order+1, cursor_row,0);  //一刀数据 高亮显示
							cursor_row--;
							CursorMov_dis(cursor_row, 1);//红色光标上移显示
							OneKnifeDataSel_dis(Knife_order, cursor_row,RED_COLOR);  //一刀数据 高亮显示
							}
						else  //页眉
							{
							Size_1page_dis(Knife_order,0);//一页尺寸显示
							}	
						}
					else     //指向 最后一刀
						{
						Knife_order=Knife_sum;
						if(Knife_order>PAGE_KNIFE)
							{
							Size_1page_dis(Knife_order,0);//一页尺寸显示
							CursorMov_dis(cursor_row, 0);//红色光标消失
							cursor_row=0;
							CursorMov_dis(cursor_row, 1);//红色光标显示  在开头
							}
						else
							{
							CursorMov_dis(cursor_row, 0);//红色光标消失
							OneKnifeDataSel_dis(1, cursor_row,0);  //一刀数据 高亮显示
							cursor_row=Knife_order-1;
							CursorMov_dis(cursor_row, 1);//红色光标显示  在开头
							OneKnifeDataSel_dis(Knife_order, cursor_row,RED_COLOR);  //一刀数据 高亮显示
							}
						}
					if(Knife_order<=Knife_sum)
						StepOrder_dis(Knife_order);//步骤更新
					PromptNum_dis();//输入范围
					PromptDis_flag=1;
						 break;
				case PROG_LABEL_MODE://标签 下--------------------------
				case TEACH_LABEL_MODE://标签 下--------------------------
					 if(PorgSet_sel>0)
						{
						LabelSel_dis(PorgSet_sel,0);PorgSet_sel--;
						LabelSel_dis(PorgSet_sel,1);
						}
							break;
				case PROG_DIVIDE_MODE://等分 下--------------------------
				case TEACH_DIVIDE_MODE://等分 下--------------------------
					 if(PorgSet_sel>0)
						{
						DivideSel_dis(PorgSet_sel,0);PorgSet_sel--;
						DivideSel_dis(PorgSet_sel,1);
						}
							break;
				case PROG_PRO_MODE:    //程序选择----------------------
				case TEACH_PRO_MODE:    //程序选择----------------------
					if(InputTouch_flag==0)  //	 非 触摸计算器 下
						{
						  if(Pro_num<2)//返回最后 pro
							  {
							  Pro_num=MAIX_PROG;
							  CursorMov_dis(cursor_temp,0);//光标
							  cursor_temp=MAIX_PROG%PAGE2_KNIFE;
							  if(cursor_temp<1)
								 cursor_temp=PAGE2_KNIFE;
							  cursor_temp--;
							  CursorMov_dis(cursor_temp,1);//
							  Prog_1page_dis(Pro_num-cursor_temp, 0);//===程序---数据显示
							  }
						  else
							  {
							  Pro_num--;
							  if(cursor_temp>0)//
								 {
								 CursorMov_dis(cursor_temp,0);//光标
								 cursor_temp--;
								 CursorMov_dis(cursor_temp,1);//
								 }
							  else//上一页
								 {
								 CursorMov_dis(cursor_temp,0);//光标
								 cursor_temp=PAGE2_KNIFE-1;
								 CursorMov_dis(cursor_temp,1);//
								 Prog_1page_dis(Pro_num-(PAGE2_KNIFE-1), 0);//===程序---数据显示
								 }
							  }
						}	  
						     break;
				case AUTO_TOOLS_MODE://  参数设置  上移
				case SELF_TOOLS_MODE://  参数设置  上移
				case MANUAL_TOOLS_MODE:// 手动 参数模式
					if(PramSel_Page<1)	//page 1
						{
						if(Para_sel>0)
							{
							if(InputTouch_flag==0)  //	 非 触摸计算器 下
								{
								ParameterPage_dis(Para_sel--, 0);
								ParameterPage_dis(Para_sel, 1);	
								}
							else
								{
								if(Para_sel>6)
									Para_sel--;
								else 
									ParameterPage_dis(Para_sel--, 0);
								if(Para_sel<7)
									ParameterPage_dis(Para_sel, 1);	
								}
							}	
						}
					else	//page 2
						{
						if(Para2_sel>0)
							{
							if(InputTouch_flag==0)  //	 非 触摸计算器 下
								{
								ParameterPage2_dis(Para2_sel--, 0);
								ParameterPage2_dis(Para2_sel, 1);	
								}
							else
								{
								if(Para2_sel>6)
									Para2_sel--;
								else 
									ParameterPage2_dis(Para2_sel--, 0);
								if(Para2_sel<7)
									ParameterPage2_dis(Para2_sel, 1);	
								}
							}
						else 
							{
							if(InputTouch_flag==0)  //	 非 触摸计算器 下
								{
								PramSel_Page--;	
								ToolsPage1_dis(); //参数 page1
								}
							}
						}
							 break;
				case MANUAL_SERVO_C_MODE:// 手动直流伺服 C 参数 
					if(Para_sel>0)
						{
						if(InputTouch_flag==0)  //	 非 触摸计算器 下
							{
							ServoParameter_dis(Para_sel--, 0);
							ServoParameter_dis(Para_sel, 1);	
							}
						else
							{
							if(Para_sel>6)
								Para_sel--;
							else 
								ServoParameter_dis(Para_sel--, 0);
							if(Para_sel<7)
								ServoParameter_dis(Para_sel, 1);	
							}
						}
						     break;
				case MANUAL_CLOCK_MODE: //手动 时钟模式	
					if(Para_sel>0)
						{
						TimeSetSel_dis(Para_sel--, 0);
						TimeSetSel_dis(Para_sel, 1);
						}
							break;
				case MANUAL_PULSE_MODE://手动 脉冲当量	
					if(Para_sel>0)
						{
						SelPulseDegree_dis(Para_sel--, 0); //脉冲设定
						SelPulseDegree_dis(Para_sel, 1);
						}
							break;
				case MANUAL_PASS_MODE: //手动 密码设置
					if(PassModeOk_flag==1)
						{
						if(Para_sel>0)
							{
							PassDaysSet_dis(Para_sel--, 0); //天数
							PassDaysSet_dis(Para_sel, 1); //天数
							}
						}
						break;				
				}			
			 }
		   else
			 {
									
			 }
		  }        
		else
		  {
		  if(Board_TestMod==TEST_HELP)
			 {
			 if(Manual_page>0)        //上一页  帮助
				{
				Manual_page--;
				Comment_dis_page(Manual_page);
				}
			 }
		  }
  	     break; 
	
             
    case  ONE_KEY_CODE + YES_KEY_CODE://F 功能按键 +  数字8  **************
        
           
             break;    
    case  ONE_KEY_CODE + OPTION_KEY_CODE://F 功能按键 +  “-/除”  **************
                
           break;       
          
    case ONE_KEY_CODE +  REV_KEY_CODE://F 功能按键 +  “+/*”  **************
          
          break;
    case ONE_KEY_CODE + ADD_KEY_CODE://F 功能按键 +  “.”  **************
           
          break;  
	case ONE_KEY_CODE+MOVE_KEY_CODE:		// F 功能按键 +2******************注释图标
          
  	         break;     
    case ONE_KEY_CODE +DELETE_KEY_CODE:		//F 功能按键 + 3   选择一个程序***************** 
           
             break;
    case     ONE_KEY_CODE+NINE_KEY_CODE:		//F 功能按键 +  数字1************
               
             break;
	case     ONE_KEY_CODE+ SUB_KEY_CODE:    //F 功能按键 +  数字9************
             
             break;   
    case     ONE_KEY_CODE+EIGHT_KEY_CODE :   //F 功能按键 +  数字4************
             
          
            break;
    case     ONE_KEY_CODE+ PROG_KEY_CODE: //F 功能按键 +  数字0************
          
            break;
    case     ONE_KEY_CODE+NO_KEY_CODE :   //F 功能按键 +  数字5  **************
            
          break;
    case     ONE_KEY_CODE+ SEVEN_KEY_CODE:  //F 功能按键 +  数字7  **************
           
          break;
	case DENGJU_KEY_CODE+NINE_KEY_CODE://向上箭头 + 1  ************
		
		break; 
    case DENGJU_KEY_CODE+INSERT_KEY_CODE://向上箭头 + 6  ************    
                
		break;
	case 0xffff000d:  //F0CUT_TOUCH_CODE		F0 批量 刀标志 按钮
			if(WorkStart_flag==1)
				{
				if(Run_flag==0)
				  {
				  if(InputTouch_flag==0)
					 {
					  switch(WorkMode)
						  {
						  // case PROG_MODE://编程画面下
						  // case TEACH_MODE://示教画面下
							case  AUTO_MODE://自动主画面下
								knife=2;
								
								if(Pro_data.pro_num<=(PROG_GROPU1+1))  //前301个prog
								   {
								   offset=PROG_BYTES1*(Pro_data.pro_num-1);
								   }
								else//后  199
								   {
								   offset=PROG_BYTES1*PROG_GROPU1+(Pro_data.pro_num-PROG_GROPU1-1)*PROG_BYTES2;
								   }
								pbuf=(pInt8U)(K_SIZE_sdram+offset+2+(knife-1)*5+4);//程序基地址
								
							//----  处理所有刀  标志-------------
								pKnife_data=(pInt8U)&OneKnife_data;
								
								GetOneKnife_datas(Pro_data.pro_num, knife-1, pKnife_data);//
								while(knife<=Knife_sum)
									{
									if(AllKnifeSet_flag==0)//设定 所有刀标志
										{
										
										InputSize=OneKnife_data.size;
										GetOneKnife_datas(Pro_data.pro_num, knife, pKnife_data);//
										if((OneKnife_data.size<InputSize)&&(OneKnife_data.size>0))//小于 前一刀
											{
											if(OneKnife_data.k_flag!=KNIFE_FLAG) 
												{
												//OneKnife_data.k_flag=KNIFE_FLAG;  
												//SaveOneKnife_datas(Pro_data.pro_num,knife , pKnife_data);//保存一刀数据
												//*pbuf=*(pKnife_data+4);
												*pbuf=KNIFE_FLAG;
												}
											}
										pbuf+=5;
										}
									else	 //清除  所有刀标志
										{
										GetOneKnife_datas(Pro_data.pro_num, knife, pKnife_data);//
										if(OneKnife_data.k_flag==KNIFE_FLAG) 
											{
											//OneKnife_data.k_flag=0;// 清除 标志
											//SaveOneKnife_datas(Pro_data.pro_num,knife , pKnife_data);//保存一刀数据
											*pbuf=0;
											}
										pbuf+=5;	
										}
									knife_set_flag=1;	
											
									knife++;	
									}
									
									
									
									if(AllKnifeSet_flag==0)
										AllKnifeSet_flag=1;
									else
										AllKnifeSet_flag=0;
										
								if(knife_set_flag==1)   //更新  显示---------
									{
									SaveBuf_datas(Pro_data.pro_num, 1, Knife_sum );//保存
									//------------返回第一刀
									ClrInput_function();//清零 输入框 
									CursorMov_dis(cursor_row, 0);//红色光标消失
									cursor_row=0;
									CursorMov_dis(cursor_row, 1);//红色光标显示
									Knife_order=1;//
									Size_1page_dis(Knife_order,0);//一页尺寸显示
									if(Knife_order<=Knife_sum)
										StepOrder_dis(Knife_order);//步骤更新	
									//PromptNum_dis();//输入范围
									//PromptDis_flag=1;	
									}
								// F5Button_dis( );  //F5 一个 刀 标记 按钮
								F0Button_dis(AllKnifeSet_flag);  //F0 所有 刀 标记 按钮/
									break;
						  }
					 }
				  }
				}
		break;
	case 0xffff000e:  //F5CUT_TOUCH_CODE		F5 1个  刀标志 按钮	
			if(WorkStart_flag==1)
				{
				if(Run_flag==0)
				  {
				  if(InputTouch_flag==0)
					 {
					  switch(WorkMode)
						  {
						  case PROG_MODE://编程画面下
						  // case TEACH_MODE://示教画面下
						  case AUTO_MODE://自动主画面下
							//----保存数据----------------
							 if(Knife_order>1)
								{
								 pKnife_data=(pInt8U)&OneKnife_data;
								 GetOneKnife_datas(Pro_data.pro_num, Knife_order-1, pKnife_data);//
								 InputSize=OneKnife_data.size;
								 GetOneKnife_datas(Pro_data.pro_num, Knife_order, pKnife_data);//
								 if((OneKnife_data.size<InputSize)&&(OneKnife_data.size>0))//小于 前一刀
									{
									if(OneKnife_data.k_flag!=KNIFE_FLAG) //
										{
										OneKnife_data.k_flag=KNIFE_FLAG;//  设定 刀标志
										}
									else
										{
										OneKnife_data.k_flag=0;// 清除 标志
										}
									PushFlag_dis(cursor_row,OneKnife_data.k_flag); //显示----
									SaveOneKnife_datas(Pro_data.pro_num, Knife_order , pKnife_data);//保存一刀数据
									PromptNum_dis();//输入范围
									PromptDis_flag=1;
									F5Button_dis(OneKnife_data.k_flag);  //F5 一个 刀 标记 按钮
									}
								 else
									{
									PromptDis_flag=0;
									GLCD_SetWindow_Fill(REMIND_WINDOW_X, REMIND_WINDOW_Y, REMIND_WINDOW_X+REMIND_LENGTH, REMIND_WINDOW_Y+30, 0xfffff, 0xffff);//提示框
									switch(Language)
										{
										case CHN_HAN:
											Printf24("此刀标志设定无效!",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,RED_COLOR,0,0xffff);
												break;
										case ENGLISH:
											Printf24("Invalid Mark!",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,RED_COLOR,0,0xffff);
												break;
										}
									}
									
								}
							 else
								{
								PromptDis_flag=0;
								GLCD_SetWindow_Fill( REMIND_WINDOW_X, REMIND_WINDOW_Y, REMIND_WINDOW_X+REMIND_LENGTH, REMIND_WINDOW_Y+30, 0xfffff, 0xffff);//提示框
								switch(Language)
										{
										case CHN_HAN:
											Printf24("此刀标志设定无效!",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,RED_COLOR,0,0xffff);
												break;
										case ENGLISH:
											Printf24("Invalid Mark!",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,RED_COLOR,0,0xffff);
												break;
										}
								}
								break;
						  }
					 }
				  }
				else//运行中
				  {
				  
				  }
				}
		break;
    }            
	
}

int KeyCheck(void)
{
int i;
int  c;

KEY_COL1_CLR();
KEY_COL2_CLR();
KEY_COL3_CLR();
KEY_COL4_CLR();
KEY_COL5_CLR();
//KEY_COL6_CLR();
i=500;
while(i--);
	// // GPIO_SetBit(GPIOI, KEY_COL6);
			// // GPIO_SetBit(GPIOH, BIT11);
	// // GPIO_SetBit(GPIOH, BIT12);
	// // GPIO_SetBit(GPIOH, BIT13);
	// // GPIO_SetBit(GPIOH, BIT14);
	// // GPIO_SetBit(GPIOH, BIT15);
	
c=(~GPIO_ReadPort(KEYIO))&KEY_CODE_MASK;
if(KEY_COL6_IN()==0)
	c|=0x1;
KEY_COL1_SET();
KEY_COL2_SET();
KEY_COL3_SET();
KEY_COL4_SET();
KEY_COL5_SET();
//KEY_COL6_SET();
return(c);
}

void KeyReadCode(void)
{
	int i;
int keycodetemp;
KeyCode=0;
	i=500;
while(i--);
KEY_COL1_CLR();
i=500;
while(i--);
keycodetemp=(~GPIO_ReadPort(KEYIO))&KEY_CODE_MASK;
if(KEY_COL6_IN()==0)
	keycodetemp|=0x1;
if(keycodetemp!=0)
	KeyCode=keycodetemp|0x4000000;
KEY_COL1_SET();
i=500;
while(i--);
KEY_COL2_CLR();
i=500;
while(i--);
keycodetemp=(~GPIO_ReadPort(KEYIO))&KEY_CODE_MASK;
if(KEY_COL6_IN()==0)
	keycodetemp|=0x1;
if(keycodetemp!=0)
	KeyCode+=(keycodetemp|0x8000000);
	//KeyCode=keycodetemp|0x10000000;
KEY_COL2_SET();
i=500;
while(i--);
KEY_COL3_CLR();
i=500;
while(i--);
keycodetemp=(~GPIO_ReadPort(KEYIO))&KEY_CODE_MASK;
if(KEY_COL6_IN()==0)
	keycodetemp|=0x1;
if(keycodetemp!=0)
	KeyCode+=(keycodetemp|0x10000000);
	//  KeyCode=keycodetemp|0x20000000;
KEY_COL3_SET();
i=500;
while(i--);
KEY_COL4_CLR();
i=500;
while(i--);
keycodetemp=(~GPIO_ReadPort(KEYIO))&KEY_CODE_MASK;
if(KEY_COL6_IN()==0)
	keycodetemp|=0x1;
if(keycodetemp!=0)
	KeyCode+=(keycodetemp|0x20000000);
//		KeyCode=keycodetemp|0x40000000;
KEY_COL4_SET();
i=500;
while(i--);
KEY_COL5_CLR();
i=500;
while(i--);
keycodetemp=(~GPIO_ReadPort(KEYIO))&KEY_CODE_MASK;
if(KEY_COL6_IN()==0)
	keycodetemp|=0x1;
if(keycodetemp!=0)
	KeyCode+=(keycodetemp|0x40000000);
//	  KeyCode=keycodetemp|0x80000000;
KEY_COL5_SET();
i=500;
while(i--);
/*
KEY_COL6_CLR();
i=500;
while(i--);
keycodetemp=(~GPIO_ReadPort(KEYIO))&KEY_CODE_MASK;
if(keycodetemp!=0)
	KeyCode+=(keycodetemp|0x80000000);
//	  KeyCode=keycodetemp|0x80000000;
KEY_COL6_SET();
*/
keyChangeCode();
}


void keyChangeCode(void)
{
Int32U ktemp;
Int16U kctemp;

Int32U kbuf;

ktemp=KeyCode&0xff000000;
kctemp=KeyCode&0xF801;

KeyCode=0;
/*
	if(ktemp&0x04000000)
	{
	//case 0x04000000:	//第一列

				if(kctemp&0x8000)
				KeyCode+=RETURN_KEY_CODE;
				else

				if(kctemp& 0x4000)//://第二行
				KeyCode+=READ_KEY_CODE;
				else
				if(kctemp& 0x2000)//://第三行
					KeyCode+=AUTO_KEY_CODE;
					else
				if(kctemp& 0x1000)//://第四行
				KeyCode+=FIVE_KEY_CODE;
				else

				if(kctemp& 0x0800)//://第五行
				KeyCode+=ZERO_KEY_CODE;
				else

				if(kctemp& 0x0001)//:	//第六行
				KeyCode+=MANUAL_KEY_CODE;

	}

		if(ktemp&0x08000000)
	{
	//case 0x08000000:	//第二列

				if(kctemp&0x8000)////第一行
				KeyCode+=NEXTKNIFE_KEY_CODE;
				else
				
				if(kctemp&0x4000)////第二行
				KeyCode+=ADD_KEY_CODE;
				else
					
				if(kctemp&0x2000)////第三行
					KeyCode+=PROG_KEY_CODE;
					else
					
				if(kctemp&0x1000)////第四行
				KeyCode+=SIX_KEY_CODE;
				else
					
				if(kctemp&0x0800)////第五行
				KeyCode+=ONE_KEY_CODE;
					else
				if(kctemp&0x0001)//	//第六行
				KeyCode+=UP_KEY_CODE;

	//	break;
	}

			if(ktemp&0x10000000)
	{
	//case 0x10000000:	//第三列

				if(kctemp&0x8000)////第一行
				KeyCode+=ADJUST_KEY_CODE;
				else

				if(kctemp&0x4000)////第二行
				KeyCode+=SUB_KEY_CODE;
				else

				if(kctemp&0x2000)////第三行
					KeyCode+=YES_KEY_CODE;
					else

				if(kctemp&0x1000)////第四行
				KeyCode+=SEVEN_KEY_CODE;
				else

				if(kctemp&0x0800)////第五行
				KeyCode+=TWO_KEY_CODE;
				else

				if(kctemp&0x0001)//	//第六行
				KeyCode+=DOWN_KEY_CODE;


		//break;
	}

				if(ktemp&0x20000000)
	{
	//case 0x20000000:	//第四列

				if(kctemp&0x8000)////第一行
				KeyCode+=OPTION_KEY_CODE;
				else

				if(kctemp&0x4000)////第二行
				KeyCode+=INSERT_KEY_CODE;
				else

				if(kctemp&0x2000)////第三行
					KeyCode+=NO_KEY_CODE;
					else

				if(kctemp&0x1000)////第四行
				KeyCode+=EIGHT_KEY_CODE;
				else

				if(kctemp&0x0800)////第五行
				KeyCode+=THREE_KEY_CODE;
				else

				if(kctemp&0x0001)//	//第六行
				KeyCode+=DENGFENG_KEY_CODE;

	//	break;
	}

				if(ktemp&0x40000000)
	{
					//case 0x40000000:	//第五列

				if(kctemp&0x8000)////第一行
				KeyCode+=REV_KEY_CODE;
				else
				if(kctemp&0x4000)////第二行
				KeyCode+=DELETE_KEY_CODE;
				else

				if(kctemp&0x2000)////第三行
					KeyCode+=MOVE_KEY_CODE;
					else

				if(kctemp&0x1000)////第四行
				KeyCode+=NINE_KEY_CODE;
				else

				if(kctemp&0x0800)////第五行
				KeyCode+=FOUR_KEY_CODE;
				else

				if(kctemp&0x0001)//	//第六行
				KeyCode+=DENGJU_KEY_CODE;

//		break;
	}

	*/


switch(ktemp)
	{
	case 0x04000000:	//第一列
		switch(kctemp)
				{
				case 0x8000://第一行
				KeyCode=RETURN_KEY_CODE;
					break;
				case 0x4000://第二行
				KeyCode=READ_KEY_CODE;
					break;
				case 0x2000://第三行
					KeyCode=AUTO_KEY_CODE;
					break;
				case 0x1000://第四行
				KeyCode=FIVE_KEY_CODE;
					break;
				case 0x0800://第五行
				KeyCode=ZERO_KEY_CODE;
					break;
				case 0x0001:	//第六行
				KeyCode=MANUAL_KEY_CODE;
					break;				
				}
		break;

	case 0x08000000:	//第二列
		switch(kctemp)
				{
				case 0x8000://第一行
				KeyCode=NEXTKNIFE_KEY_CODE;
					break;
				case 0x4000://第二行
				KeyCode=ADD_KEY_CODE;
					break;
				case 0x2000://第三行
					KeyCode=PROG_KEY_CODE;
					break;
				case 0x1000://第四行
				KeyCode=SIX_KEY_CODE;
					break;
				case 0x0800://第五行
				KeyCode=ONE_KEY_CODE;
					break;
				case 0x0001:	//第六行
				KeyCode=UP_KEY_CODE;
					break;		
					
				case 0x0800+0x2000://组合键
					KeyCode=ONE_KEY_CODE+ PROG_KEY_CODE; //F 功能按键 +  数字0************ 批量 刀标志
				break;
				}
		break;

	case 0x10000000:	//第三列
		switch(kctemp)
				{
				case 0x8000://第一行
				KeyCode=ADJUST_KEY_CODE;
					break;
				case 0x4000://第二行
				KeyCode=SUB_KEY_CODE;
					break;
				case 0x2000://第三行
					KeyCode=YES_KEY_CODE;
					break;
				case 0x1000://第四行
				KeyCode=SEVEN_KEY_CODE;
					break;
				case 0x0800://第五行
				KeyCode=TWO_KEY_CODE;
					break;
				case 0x0001:	//第六行
				KeyCode=DOWN_KEY_CODE;
					break;				
				}
		break;

	case 0x20000000:	//第四列
		switch(kctemp)
				{
				case 0x8000://第一行
				KeyCode=OPTION_KEY_CODE;
					break;
				case 0x4000://第二行
				KeyCode=INSERT_KEY_CODE;
					break;
				case 0x2000://第三行
					KeyCode=NO_KEY_CODE;
					break;
				case 0x1000://第四行
				KeyCode=EIGHT_KEY_CODE;
					break;
				case 0x0800://第五行
				KeyCode=THREE_KEY_CODE;
					break;
				case 0x0001:	//第六行
				KeyCode=DENGFENG_KEY_CODE;
					break;				
				}
		break;

	case 0x40000000:	//第五列
		switch(kctemp)
				{
				case 0x8000://第一行
				KeyCode=REV_KEY_CODE;
					break;
				case 0x4000://第二行
				KeyCode=DELETE_KEY_CODE;
					break;
				case 0x2000://第三行
					KeyCode=MOVE_KEY_CODE;
					break;
				case 0x1000://第四行
				KeyCode=NINE_KEY_CODE;
					break;
				case 0x0800://第五行
				KeyCode=FOUR_KEY_CODE;
					break;
				case 0x0001:	//第六行
				KeyCode=DENGJU_KEY_CODE;
					break;		
				case 0x0001+0x2000://组合键
				KeyCode=DENGJU_KEY_CODE+MOVE_KEY_CODE;	//向上箭头+2  脉冲当量 设定	 
				break;

				case 0x0001+0x4000://组合键
					KeyCode=DENGJU_KEY_CODE+DELETE_KEY_CODE;  //	向上箭头+3  档位选择
					break;
				case 0x0001+0x1000://组合键
					KeyCode=DENGJU_KEY_CODE+NINE_KEY_CODE;			//向上箭头+1  脉冲当量 设定
				break;
				}
		break;

	case 0x30000000:	//组合键
		switch(kctemp)
				{
				case 0x2001:
					KeyCode=DENGFENG_KEY_CODE+YES_KEY_CODE;//向下箭头+8 密码模式
					break;

				}
		break;
	case 0x08000000+0x40000000:
		switch(kctemp)
				{
				case 0x0800+0x1000:
					 KeyCode=ONE_KEY_CODE+NINE_KEY_CODE;		//F 功能按键 + 1 ***********
				break;

				case 0x0800+0x2000:
					  KeyCode=ONE_KEY_CODE+MOVE_KEY_CODE;		// F 功能按键 +2************
				break;

				case 0x0800+0x4000:
					KeyCode=ONE_KEY_CODE+DELETE_KEY_CODE;		//F 功能按键 + 3 ***********
				break;
			case 0x0800+0x8000:
					KeyCode=ONE_KEY_CODE+REV_KEY_CODE;   //    ***************F功能按键+ “+/*”
			break;

						case 0x0800+0x0001:
					KeyCode=ONE_KEY_CODE+DENGJU_KEY_CODE;  //F+向上箭头		----左
			break;				
				}
		break;

	case 0x08000000+0x20000000:
		switch(kctemp)
				{
				case 0x0800+0x1000:
					KeyCode=ONE_KEY_CODE+EIGHT_KEY_CODE;		// F 功能按键 +4************	
				break;

				case 0x0800+0x2000:
					  KeyCode=ONE_KEY_CODE+NO_KEY_CODE;		  //F 功能按键 + 5 ***********刀标志
				break;

				case 0x0800+0x4000:
					KeyCode=ONE_KEY_CODE+INSERT_KEY_CODE;   //        F功能按键+6 ----------示教模式
				break;
				

				case 0x0800+0x8000:
					KeyCode=ONE_KEY_CODE+OPTION_KEY_CODE;   //    ***************F功能按键+ “-/除”
					break;
				
			case 0x0800+0x0001:
				KeyCode=ONE_KEY_CODE+DENGFENG_KEY_CODE;  //F+向下箭头		----右
			break;
				
				}
		break;
/*
		case 0x08000000+0x40000000:
		switch(kctemp)
				{
			case 0x0800+0x8000:
					KeyCode=ONE_KEY_CODE+REV_KEY_CODE;   //    ***************F功能按键+ “+/ *”
			break;

						case 0x0800+0x0001:
					KeyCode=ONE_KEY_CODE+DENGJU_KEY_CODE;  //F+向上箭头		----左
			break;
				}

			break;

		case 0x08000000+0x20000000:
		switch(kctemp)
				{
			case 0x0800+0x0001:
				KeyCode=ONE_KEY_CODE+DENGFENG_KEY_CODE;  //F+向下箭头		----右
			break;


				}

			break;
*/
		/*
	
	
	 
	 		
	 
	 
	 
	 
	 
 	

	
	
	
	*/
	}


}


void Key_Enable(unsigned char enb)
{
}

void KeyInit(void)  //键端口初始化
{
/*
KEY_COL1_DIR_OUT();
KEY_COL2_DIR_OUT();
KEY_COL3_DIR_OUT();
KEY_COL4_DIR_OUT();
KEY_COL5_DIR_OUT();
KEY_COL6_DIR_OUT();
*/
	/***
		GPIO_CloseBit(GPIOI, KEY_COL6);
	GPIO_CloseBit(GPIOH, BIT11);
	GPIO_CloseBit(GPIOH, BIT12);
		GPIO_CloseBit(GPIOH, BIT13);
	GPIO_CloseBit(GPIOH, BIT14);
		GPIO_CloseBit(GPIOH, BIT15);

KEY_COL1_SET();
KEY_COL2_SET();
KEY_COL3_SET();
KEY_COL4_SET();
KEY_COL5_SET();
//KEY_COL6_SET();
	
	GPIO_OpenBit(GPIOI, KEY_COL6, DIR_INPUT, PULL_UP);
	GPIO_SetBit(GPIOI, KEY_COL6);

			GPIO_SetBit(GPIOH, BIT11);
	GPIO_OpenBit(GPIOH, BIT11, DIR_INPUT, PULL_UP);

		GPIO_SetBit(GPIOH, BIT12);
	GPIO_OpenBit(GPIOH, BIT12, DIR_INPUT, PULL_UP);

		GPIO_SetBit(GPIOH, BIT13);
	GPIO_OpenBit(GPIOH, BIT13, DIR_INPUT, PULL_UP);

		GPIO_SetBit(GPIOH, BIT14);
	GPIO_OpenBit(GPIOH, BIT14, DIR_INPUT, PULL_UP);

		GPIO_SetBit(GPIOH, BIT15);
	GPIO_OpenBit(GPIOH, BIT15, DIR_INPUT, PULL_UP);
**/
GPIO_CloseBit(GPIOI, 1);
	GPIO_CloseBit(GPIOI,2);
	GPIO_CloseBit(GPIOI, 3);
	GPIO_CloseBit(GPIOI, 4);
	GPIO_CloseBit(GPIOI, 5);
	GPIO_CloseBit(GPIOI, 6);
	
		GPIO_CloseBit(GPIOI, KEY_COL6);
	
	GPIO_CloseBit(GPIOH, BIT11);
	GPIO_CloseBit(GPIOH, BIT12);
		GPIO_CloseBit(GPIOH, BIT13);
	GPIO_CloseBit(GPIOH, BIT14);
		GPIO_CloseBit(GPIOH, BIT15);

	
KEY_COL1_DIR_OUT();
KEY_COL2_DIR_OUT();
KEY_COL3_DIR_OUT();
KEY_COL4_DIR_OUT();
KEY_COL5_DIR_OUT();
	
////////KEY_COL1_SET();
////////KEY_COL2_SET();
////////KEY_COL3_SET();
////////KEY_COL4_SET();
////////KEY_COL5_SET();
//KEY_COL6_SET();
	
	GPIO_SetBit(GPIOI, KEY_COL6);
	GPIO_OpenBit(GPIOI, KEY_COL6, DIR_INPUT, PULL_UP);
	GPIO_SetBit(GPIOI, KEY_COL6);


	GPIO_SetBit(GPIOH, BIT11);
	GPIO_OpenBit(GPIOH, BIT11, DIR_INPUT, PULL_UP);
	GPIO_SetBit(GPIOH, BIT11);	

		GPIO_SetBit(GPIOH, BIT12);
	GPIO_OpenBit(GPIOH, BIT12, DIR_INPUT, PULL_UP);
	GPIO_SetBit(GPIOH, BIT12);	

		GPIO_SetBit(GPIOH, BIT13);
	GPIO_OpenBit(GPIOH, BIT13, DIR_INPUT, PULL_UP);
	GPIO_SetBit(GPIOH, BIT13);	

		GPIO_SetBit(GPIOH, BIT14);
	GPIO_OpenBit(GPIOH, BIT14, DIR_INPUT, PULL_UP);
	GPIO_SetBit(GPIOH, BIT14);	

		GPIO_SetBit(GPIOH, BIT15);
	GPIO_OpenBit(GPIOH, BIT15, DIR_INPUT, PULL_UP);
	GPIO_SetBit(GPIOH, BIT15);	

	
//KEYIO_DDR&=0xfc1FFFFF;
//PINMODE7&=0xffc00ffff;
}






void ClrInput_function(void)//清零 输入框
{
for(num_cou=0;num_cou<8;num_cou++)
	 {
		Size_temp[num_cou++]=0;
	 }
num_cou=0; // nn=0;temp=0;
CalcTemp_cou=num_cou;
Dot_flag=0;
GLCD_SetWindow_Fill( SIZE_WINDOW_X+24, SIZE_WINDOW_Y, SIZE_WINDOW_X+120, SIZE_WINDOW_Y+30, 0xfffff, 0xffff);//尺寸输入框
}
//************************************************************************************
void SaveOneKnife_datas(Int16U prog,Int16U order,pInt8U pdatas)//保存一刀数据
{
pInt8U pbuf;
Int32U add,sd_add,offset,i;
if(prog<=(PROG_GROPU1+1))  //前301个prog
   {
   offset=PROG_BYTES1*(prog-1);
   }
else//后  199
   {
   offset=PROG_BYTES1*PROG_GROPU1+(prog-PROG_GROPU1-1)*PROG_BYTES2;
   }
sd_add=K_SIZE_sdram+offset+2;//刀数据 buf基地址
   
pbuf=(pInt8U)&Knife_sum;
add=DATA_SAVE_OFFSET+offset;//刀数据 spi基地址
//********************总刀数变更  则  Knife_sum 保存
if(Knife_sum_before!=Knife_sum)
	{
	Knife_sum_before=Knife_sum;
	Write_25pe_data(pbuf,     add,      2);
	}
//********************刀数据 保存
pbuf=(pInt8U)(sd_add+(order-1)*5);//刀数据 buf地址
add=add+2+(order-1)*5;
for(i=0;i<5;i++)
   {
   *(pbuf+i)=*(pdatas+i);      //更新 缓存
   }
Write_25pe_data(pbuf,     add,      5);
}

void GetOneKnife_datas(Int16U prog,Int16U order ,pInt8U pdatas)//从sdram读入一刀数据
{
pInt8U pbuf;
Int8U i;
Int32U sd_add,offset;
if(prog<=(PROG_GROPU1+1))  //前301个prog
   {
   offset=PROG_BYTES1*(prog-1);
   }
else//后  199
   {
   offset=PROG_BYTES1*PROG_GROPU1+(prog-PROG_GROPU1-1)*PROG_BYTES2;
   }
sd_add=K_SIZE_sdram+offset+2;//刀数据 buf基地址
pbuf=(pInt8U)(sd_add+(order-1)*5); //刀数据 buf地址
for(i=0;i<5;i++)
   {
   *pdatas++=*pbuf++;
   }
}
void PutOneKnife_datas(Int16U prog,Int16U order ,pInt8U pdatas)//向sdram存入一刀数据
{
pInt8U pbuf;
Int32U add,sd_add,offset,i;
if(prog<=(PROG_GROPU1+1))  //前301个prog
   {
   offset=PROG_BYTES1*(prog-1);
   }
else//后  199
   {
   offset=PROG_BYTES1*PROG_GROPU1+(prog-PROG_GROPU1-1)*PROG_BYTES2;
   }
sd_add=K_SIZE_sdram+offset+2;//刀数据 buf基地址
   
pbuf=(pInt8U)(sd_add+(order-1)*5);//刀数据 buf地址
for(i=0;i<5;i++)
   {
   *pbuf++=*pdatas++;      //更新 缓存
   }
}

void SaveBuf_datas(Int16U prog,Int16U order1, Int16U order2)//保存 order1到 order2  buf区的数据到spi
{
pInt8U pbuf,psave;
Int32U add,sd_add,offset,n;
if(prog<=(PROG_GROPU1+1))  //前301个prog
   {
   offset=PROG_BYTES1*(prog-1);
   }
else//后  199
   {
   offset=PROG_BYTES1*PROG_GROPU1+(prog-PROG_GROPU1-1)*PROG_BYTES2;
   }
sd_add=K_SIZE_sdram+offset+2;//刀数据 buf基地址
pbuf=(pInt8U)(sd_add+(order1-1)*5);
add=DATA_SAVE_OFFSET+offset+2;//刀数据 spi基地址
add=add+(order1-1)*5;
if(order2>=order1)//
   {
   n=(order2-order1+1)*5;
   Write_25pe_data(pbuf,     add,      n);
   }
}

void ClrBuf_datas(Int16U prog,Int16U order1, Int16U order2)//清零 order1到 order2  buf区的数据   
{
pInt8U pbuf;
Int32U n,lenth,sd_add,offset;
if(prog<=(PROG_GROPU1+1))  //前301个prog
   {
   offset=PROG_BYTES1*(prog-1);
   }
else//后  199
   {
   offset=PROG_BYTES1*PROG_GROPU1+(prog-PROG_GROPU1-1)*PROG_BYTES2;
   }
sd_add=K_SIZE_sdram+offset+2;//刀数据 buf基地址
pbuf=(pInt8U)(sd_add+(order1-1)*5);
lenth=(order2-order1+1)*5;
for(n=0;n<lenth;n++)
   {
   *pbuf++=0;
   }
}


//-----参数 部分存取
void ReadPro_perameter(pInt8U pdata)//读取 程序 段 号码
{
Int8U d;
Int32U add;
add=PRO_NUM_25PEADD;//地址

FastRead_Datas_Start(add);
for(d=0;d<4;d++)
   {
   *pdata++=ReadFlash_Datas();
   }
FlashChip_Dis;
}

void SavePro_data(pInt8U pdata)//保存 程序 段 号码
{
Int32U add;
add=PRO_NUM_25PEADD;//地址

Write_25pe_data(pdata, add, 4);
}

void GetKnife_sum(Int16U prog)//读一个程序的 刀数
{
Int32U offset;
pInt8U pbuf,pdata;
Int16U max_sum;
Int16U sum_temp;
if(prog<=(PROG_GROPU1+1))  //前301个prog
   {
   offset=PROG_BYTES1*(prog-1);
   max_sum=MAIX_KNIFE1;
   }
else//后  199
   {
   offset=PROG_BYTES1*PROG_GROPU1+(prog-PROG_GROPU1-1)*PROG_BYTES2;
   max_sum=MAIX_KNIFE2;
   }
pbuf=(pInt8U)(K_SIZE_sdram+offset);//程序基地址
pdata=(pInt8U)&sum_temp;
*pdata=*pbuf;
*(pdata+1)=*(pbuf+1);
if((sum_temp<1)||(sum_temp>max_sum))
   {
   Knife_sum=1;
   *pbuf++=*pdata++;
   *pbuf=*pdata;
   }
else
	{
	*pdata++=*pbuf++;
	*pdata=*pbuf;
	Knife_sum=sum_temp;
	}
   
}

void SaveKnife_sum(Int16U prog)//保存一个程序的 刀数
{
Int32U offset,add;
pInt8U pbuf,pdata;
if(prog<=(PROG_GROPU1+1))  //前301个prog
   {
   offset=PROG_BYTES1*(prog-1);
   }
else//后  199
   {
   offset=PROG_BYTES1*PROG_GROPU1+(prog-PROG_GROPU1-1)*PROG_BYTES2;
   }
pbuf=(pInt8U)(K_SIZE_sdram+offset);//程序基地址
pdata=(pInt8U)&Knife_sum;
*pbuf=*pdata++;
*(pbuf+1)=*pdata;
add=DATA_SAVE_OFFSET+offset;

Write_25pe_data((pInt8U)pbuf, add, 2);
}

void ReadOnePro_datas(Int16U pro_order) //spi读一个 程序数据 到 buf
{
pInt8U pbuf;
Int32U i;
Int32U offset,add;
if(pro_order<=(PROG_GROPU1+1))  //前301个prog
   {
   offset=PROG_BYTES1*(pro_order-1);
   }
else//后  199
   {
   offset=PROG_BYTES1*PROG_GROPU1+(pro_order-PROG_GROPU1-1)*PROG_BYTES2;
   }
pbuf=(pInt8U)(K_SIZE_sdram+offset);//一个pro的 buf基地址
add=DATA_SAVE_OFFSET+offset;
FastRead_Datas_Start(add);
for(i=0;i<Knife_sum*5+2;i++)
   {
   *pbuf++=ReadFlash_Datas();
   }
FlashChip_Dis;
}

void ReadAllPro_head(void)// 读所有程序头+第一刀  至 buf
{
pInt8U pbuf,pdata;
Int32U add,cou,i;
Int16U k_sum_temp=1;
Int16U max_sum;
cou=1;

pdata=(pInt8U)&k_sum_temp;
pbuf=(pInt8U)K_SIZE_sdram;

add=DATA_SAVE_OFFSET;
while(cou<=MAIX_PROG)
	{
	FastRead_Datas_Start(add);
	for(i=0;i<5+2;i++)
	   {
		*(pbuf+i)=ReadFlash_Datas();
	   }
	FlashChip_Dis;
	
	if(cou<=PROG_GROPU1)//前 300个pro
	   {
	   max_sum=MAIX_KNIFE1;//999
	   }
	else
	   {
	   max_sum=MAIX_KNIFE2;//399
	   } 
	
	*pdata=*pbuf;
	*(pdata+1)=*(pbuf+1);
	if((k_sum_temp<1)||(k_sum_temp>max_sum))//未初始化
	   {
	   k_sum_temp=1;
	   *pbuf=*pdata;
	   *(pbuf+1)=*(pdata+1);
	   for(i=2;i<7;i++)
	      {
		  *(pbuf+i)=0;
	      }
	   Write_25pe_data(pbuf, add, 7);
	   }
	
	cou++;   
	if(cou>PROG_GROPU1+1)
	   {
	   pbuf=(pInt8U)(K_SIZE_sdram+PROG_BYTES1*PROG_GROPU1+PROG_BYTES2*(cou-PROG_GROPU1-1));
       add=DATA_SAVE_OFFSET+PROG_BYTES1*PROG_GROPU1+PROG_BYTES2*(cou-PROG_GROPU1-1);
	   }
	else
	   {
	   pbuf=(pInt8U)(K_SIZE_sdram+PROG_BYTES1*(cou-1));
       add=DATA_SAVE_OFFSET+PROG_BYTES1*(cou-1);
	   }
	 
	}
}


void ReadDatas_to_sdram(void)///刀数据读入sdram
{
Int32U add,d,sum;
KNIFE_DATA Knife_datas;
pInt8U pdata;
//pdata=(pInt8U)K_SIZE_sdram;
add=DATA_SAVE_OFFSET;
/*
FastRead_Datas_Start(add);
for(d=0;d<20;d++)
   {
   *pdata++=ReadFlash_Datas();
   }
FlashChip_Dis;
//-------------------------------------初始化 判断
Pro_data.pro_num=1;//当前程序 号1
pdata=(pInt8U)&Knife_datas;
GetOneKnife_datas( 1 , pdata);//取出第一刀 
*/
pdata=(pInt8U)&Pro_data;
ReadPro_perameter(pdata);  //读取 参数 
//************当前pro 参数
 if(Pro_data.pro_num<=PROG_GROPU1)//前 300个pro
   {
   MAIX_Knife=MAIX_KNIFE1;//999
   }
 else
   {
   MAIX_Knife=MAIX_KNIFE2;//399
   } 

if((Pro_data.pro_sum<1)||(Pro_data.pro_sum>500))//程序数 无效，则初始化
  {
  Pro_data.pro_num=1;//当前程序 号1
  Pro_data.pro_sum=1;//程序 总数
  Knife_sum=1;//总 刀数
  pdata=(pInt8U)&Pro_data;
  SavePro_data(pdata);
  
  ClrBuf_datas(Pro_data.pro_num, 1,MAIX_Knife);  //清零 刀数据buf
  pdata=(pInt8U)K_SIZE_sdram;
  *pdata++=1;            //刀数 1
  *pdata++=0;
  /*
  for(d=0;d<400;d++)          //清零所有 程序
     {
     pdata=(pInt8U)K_SIZE_sdram;
	 Write_25pe_data(pdata, add, PROG_BYTES1);
	 add+=PROG_BYTES1;
	 }*/
  
  /*
  Chip_Erase();
  volatile Int32U tt=10000;
  while(tt--);*/
  }
else //  有效 读取pro
  {
  //Knife_sum=1;
  // Pro_data.pro_num=4;
  //Pro_data.pro_sum=2;
  ReadAllPro_head();  ///读所有 程序 的head
  GetKnife_sum(Pro_data.pro_num); //获取前程序 刀数
 // ReadOnePro_datas(Pro_data.pro_num);//读取 当前pro
  ClrBuf_datas(Pro_data.pro_num, 1,MAIX_Knife);  //清零 刀数据buf
  
  //Knife_sum=100;
  ReadOnePro_datas(Pro_data.pro_num);//读取 一个pro
  
  CheckKnifeSum_exec();  //--------------总刀数    核对
  Knife_sum_before=Knife_sum;
  }
 
   
}





void Prog_1page_dis(Int16U prog,Int16U line)//一页程序显示
{
//pInt8U pbuf;
KNIFE_DATA Knife_datas;
Int16U x,y,back_color=0xef9f;

while(line<PAGE2_KNIFE)
	{
	if(prog<=MAIX_PROG)
		{
		GetOneKnife_datas(prog, 1 , (pInt8U)&Knife_datas);//取出一刀 数据
		KnifeOrder_dis(line, prog,0);//序号
		KnifeSize_dis(line,Knife_datas.size,0);//尺寸
		prog++;
		}
	else//已无数据
		{
		x=TableDis_startcol;
		y=RIGHT_ARROW_Y+(line%PAGE_KNIFE)*45;
	    GLCD_SetWindow_Fill( x, y, x+243, y+45, back_color, back_color);//尺寸输入
		}
	
	line++;
	}
}

void Size_1page_dis(Int16U start_order,Int16U row)//一页尺寸显示
{
//Int16U n;
//pInt8U pbuf;
KNIFE_DATA Knife_datas;
Int16U x1,y1,x2,y2,back_color=0xef9f;
//Int8U sel_flag=0;

//pbuf=(pInt8U)(K_SIZE_sdram+(start_order*5));
while(row<PAGE_KNIFE)
   {
   if(start_order<=MAIX_Knife)
      {
		if(row==cursor_row)  //光标处
			{
			Knife_datas.k_flag=OneKnifeDataSel_dis(start_order, row,RED_COLOR);  //一刀数据 高亮显示
			//sel_flag=1;
			}
		else
			{
			GetOneKnife_datas(Pro_data.pro_num, start_order , (pInt8U)&Knife_datas);//取出一刀 数据
			 KnifeOrder_dis(row, start_order,0);//序号
			//-----------------步骤(尺寸)错误 判断 
			if((Knife_datas.size<Size_MIN_num)||(Knife_datas.size>Size_MAX_num))
				{
				Knife_datas.size=0;
				Knife_datas.k_flag=0;
				if(Knife_sum>=start_order)
					{
					if(start_order>1)
						Knife_sum=start_order-1;
					else
						Knife_sum=1;
					Knife_sum_before=Knife_sum;
					SaveKnife_sum(Pro_data.pro_num);//刀数 保存 
					StepNum_dis(Knife_sum,start_order);//步骤更新
					}
				}
			if(start_order>Knife_sum)	//最后一个步骤 之后仍有数据 则清除
				{
				if(Knife_datas.size>0)
					{
					Knife_datas.size=0;
					Knife_datas.k_flag=0;
					}
				}
				
			KnifeSize_dis(row,Knife_datas.size,0);//尺寸
			}
      
		if(InputTouch_flag==0)  //	 非 触摸计算器 下
			PushFlag_dis(row,Knife_datas.k_flag); // 推纸 标志 
	  }
   else
      {
	  x1=RIGHT_ARROW_X;
      y1=RIGHT_ARROW_Y+row*45;
	  y2=y1+45;
	  if(InputTouch_flag==0)  //	 非 触摸计算器 下
		  x2=RED_KNIFE_X+25;
	  else
		  x2=CALCUL_WIN_X-3;
	  GLCD_SetWindow_Fill( x1, y1, x2, y2, back_color, back_color);//
	  }
   start_order++;
   row++;
   }
}

void DeleteOneKnife(Int16U prog,Int16U knife)       //删除一刀
{
pInt8U pbuf_k1,pbuf_k2;
Int32U offset,add,n,num;
if(prog<=(PROG_GROPU1+1))  //前301个prog
   {
   offset=PROG_BYTES1*(prog-1);
   }
else//后  199
   {
   offset=PROG_BYTES1*PROG_GROPU1+(prog-PROG_GROPU1-1)*PROG_BYTES2;
   }
pbuf_k1=(pInt8U)(K_SIZE_sdram+offset+2+(knife-1)*5);//当前刀 buf基地址
pbuf_k2=pbuf_k1+5;        //下一刀 

num=Knife_sum-knife;
if(num>0)
   {
   for(n=0;n<num*5;n++)
     {
     *pbuf_k1++=*pbuf_k2++;
     }
	*pbuf_k1++=0;// 最后一刀
	*pbuf_k1++=0;
	*pbuf_k1++=0;
	*pbuf_k1++=0;
	*pbuf_k1=0;
   if(knife==1)  //第一刀
	  {
	  pKnife_data=(pInt8U)&OneKnife_data;
	  GetOneKnife_datas(prog, knife, pKnife_data);
	  if(OneKnife_data.k_flag==KNIFE_FLAG)
		 {
		 OneKnife_data.k_flag=NO_FLAG;  //清除 标志
		 SaveOneKnife_datas(prog, knife , pKnife_data);//保存一刀数据
		 }
	  } 
	
   pbuf_k1=(pInt8U)(K_SIZE_sdram+offset+2+(knife-1)*5);//当前刀 buf基地址
   add=DATA_SAVE_OFFSET+offset+2+(knife-1)*5;//
   Write_25pe_data(pbuf_k1,     add,      (num+1)*5);
   }
else// 最后一刀
   {
   *(pbuf_k1+0)=0;
   *(pbuf_k1+1)=0;
   *(pbuf_k1+2)=0;
   *(pbuf_k1+3)=0;
   *(pbuf_k1+4)=0;
   SaveOneKnife_datas(prog, knife,pbuf_k1);
   }
}

void InsertOneKnife(Int16U prog,Int16U knife)       //插入一刀
{
pInt8U pbuf_k1,pbuf_k2;
Int32U offset,add,n,num;
if(prog<=(PROG_GROPU1+1))  //前301个prog
   {
   offset=PROG_BYTES1*(prog-1);
   }
else//后  199
   {
   offset=PROG_BYTES1*PROG_GROPU1+(prog-PROG_GROPU1-1)*PROG_BYTES2;
   }
pbuf_k1=(pInt8U)(K_SIZE_sdram+offset+2+(Knife_sum-1)*5);//最后一刀 buf基地址
pbuf_k2=pbuf_k1+5;        //后一刀

pbuf_k1+=4;
pbuf_k2+=4;
num=Knife_sum-knife+1;

for(n=0;n<num*5;n++)
   {
   *pbuf_k2--=*pbuf_k1--;
   }   
pbuf_k1=(pInt8U)(K_SIZE_sdram+offset+2+(knife)*5);//当前刀 buf基地址
add=DATA_SAVE_OFFSET+offset+2+(knife)*5;//
Write_25pe_data(pbuf_k1,     add,      num*5);   
}

Int8U CheckInputNums(void)  //输入尺寸 计算
{
Int8U nn,num_bits;
pInt8U Size;
Int32U temp=0;
nn=0;
Dot_flag=0;
if(InputTouch_flag==0)
	{
	Size=Size_temp;
	num_bits=num_cou;
	}
else    //触摸 输入下
	{
	if(CalcResultDis_flag==0) //  未运算
		{
		CalcGetValue_exec();  //得输入结果
		}
	if(CalcResultDis_flag==1)  //已得到  结果
		{
		Size=CalcResult_Text;
		num_bits=CalcInput_cou;
		}
	else
		return 0;
	}
while(nn<num_bits)
	{
	  if(Size[nn]!='.')
		{
		 temp=temp*10+Size[nn];
		 nn++;
		}
	  else//.
	    {
		nn++;
		break;
		}
	}
//----
if(nn>=num_bits)//无小数部分
	{
	 switch(WorkMode)
		 {
		 case PROG_MODE://编程画面下
		 case TEACH_MODE://示教画面下
		 
		 case AUTO_MODE://自动主画面下
		 case SELF_CUT_MODE://自刀主画面下
		 case MANUAL_MODE:   //手动
				if(Unit==UNIT_MM)
					{
					InputSize=temp*100;
					}
				else
					{
					InputSize=temp*1000;
					}
				if((InputSize<Size_MIN_num)||(InputSize>Size_MAX_num))//超出范围
					{
					PromptDis_flag=0;
					GLCD_SetWindow_Fill( REMIND_WINDOW_X, REMIND_WINDOW_Y, REMIND_WINDOW_X+REMIND_LENGTH, REMIND_WINDOW_Y+30, 0xfffff, 0xffff);//提示框
					switch(Language)
						{
						case CHN_HAN:
							Printf24("输入尺寸超过极限！",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,RED_COLOR,0,0xffff);
								break;
						case ENGLISH:
							Printf24("Data exceeds limit!",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,RED_COLOR,0,0xffff);
								break;
						}
					if(InputTouch_flag==1)   //触摸下
						{
						ClearCalculatorInput(); //清零计算器 输入
						}
					return 0;
					}
				else   //正确	 
					{
					PromptNum_dis();//输入范围 提示
					PromptDis_flag=1;
					return 1;
					}	
					break;
		case PROG_LABEL_MODE://	编程 标签	
		case TEACH_LABEL_MODE:// 示教 标签	
		case PROG_DIVIDE_MODE://编程 等分
		case TEACH_DIVIDE_MODE://示教 等分
		case AUTO_RULER_MODE://自动 基准
		case SELF_RULER_MODE://自刀 基准
		case MANUAL_RULER_MODE://手动 基准模式	
				if(PorgSet_sel<1)
					{
					if(Unit==UNIT_MM)
						{
						InputSize=temp*100;
						}
					else
						{
						InputSize=temp*1000;
						}
					if((InputSize<Size_MIN_num)||(InputSize>Size_MAX_num))//超出范围
						{
						PromptDis_flag=0;
						GLCD_SetWindow_Fill( REMIND_WINDOW_X, REMIND_WINDOW_Y, REMIND_WINDOW_X+REMIND_LENGTH, REMIND_WINDOW_Y+30, 0xfffff, 0xffff);//提示框
						switch(Language)
							{
							case CHN_HAN:
								Printf24("输入尺寸超过极限！",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,RED_COLOR,0,0xffff);
								break;
							case ENGLISH:
								Printf24("Data exceeds limit!",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,RED_COLOR,0,0xffff);
								break;
							}
						if(InputTouch_flag==1)   //触摸下
							{
							ClearCalculatorInput(); //清零计算器 输入
							}
						return 0;
						}
					else   //正确	 
						{
						PromptNum_dis();//输入范围 提示
						PromptDis_flag=1;
						return 1;
						}	
					}
				else
					{
					if((WorkMode&0x0f)==(PROG_DIVIDE_MODE&0x0f))//等分
						{
						InputSize=temp;
						if((InputSize>0)&&(InputSize<=1000))
							return 1;
						return 0;	
						}
					else
						{
						if(Unit==UNIT_MM)
							{
							InputSize=temp*100;
							}
						else
							{
							InputSize=temp*1000;
							}
						if((InputSize>0)&&(InputSize<=Size_MAX_num))   //正确
							{
							return 1;
							}
						else
							{
							PromptDis_flag=0;
							GLCD_SetWindow_Fill( REMIND_WINDOW_X, REMIND_WINDOW_Y, REMIND_WINDOW_X+REMIND_LENGTH, REMIND_WINDOW_Y+30, 0xfffff, 0xffff);//提示框
							switch(Language)
								{
								case CHN_HAN:
									Printf24("输入尺寸超过极限！",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,RED_COLOR,0,0xffff);
									break;
								case ENGLISH:
									Printf24("Data exceeds limit!",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,RED_COLOR,0,0xffff);
									break;
								}
							}
						return 0;		
						}
					return 0;		
					}
					break;
		case PROG_PRO_MODE:    //程序选择----------------------
		case TEACH_PRO_MODE:    //程序选择----------------------
				if((temp>0)&&(temp<=MAIX_PROG))// 有效
					{
					InputSize=temp;
					return 1;
					}
				return 0;	
					break;
				
		case AUTO_TOOLS_MODE://自动  参数设置
		case SELF_TOOLS_MODE://自刀  参数设置
		case MANUAL_TOOLS_MODE:// 手动 参数模式
				if(PramSel_Page<1)	//page 1
					{
				if(Para_sel>7)
					{
					InputSize=temp;
					}
				else if(Para_sel<7)
					{
					if(Unit==UNIT_MM)
						{
						InputSize=temp*100;
						}
					else
						{
						InputSize=temp*1000;
						}
					}
					}
				else	//page 2
					{
					if(Para2_sel<2)
						{
						InputSize=temp; 
						}
					else 
						{
						//if(Unit==UNIT_MM)
							// {
							// InputSize=temp*100;
							// }
						// else
							// {
							// InputSize=temp*1000;
							// }
						}
					}
				return 1;	
					break;
		case AUTO_PLUS_MODE:  //F3++
		case AUTO_MINUS_MODE:// F4--
		case SELF_PLUS_MODE:  //F3++
		case SELF_MINUS_MODE:// F4--
				if(Unit==UNIT_MM)
					{
					InputSize=temp*100;
					}
				else
					{
					InputSize=temp*1000;
					}
				return 1;	
				 	break;
		case MANUAL_CLOCK_MODE: //手动 时钟模式			
		case MANUAL_PASS_MODE: //密码模式
		case MANUAL_PULSE_MODE://手动 脉冲当量
		case MANUAL_SERVO_C_MODE:// 手动直流伺服 C 参数 
				 InputSize=temp;
				 return 1;
					break;
		 }
	if(PassCheckDis_flag==1)	
		{
		InputSize=temp;
		return 1;
		}
	return 0; 
	}
else   //有小数部分
    {
	temp=temp*10+Size[nn];
	nn++;
	temp*=10;
	if(nn<num_bits)
	    temp+=Size[nn++];
	if(Unit!=UNIT_MM)
	   {
	    temp*=10;
		if(nn<num_bits)
			temp+=Size[nn];
	   } 
		
	InputSize=temp;
	 switch(WorkMode)
		 {
		 case PROG_MODE://编程画面下
		 case TEACH_MODE://示教画面下
		 case AUTO_MODE://自动主画面下
		 case SELF_CUT_MODE://自刀主画面下 
		 case MANUAL_MODE:   //手动
				if((InputSize<Size_MIN_num)||(InputSize>Size_MAX_num))//超出范围
					{
					PromptDis_flag=0;
					GLCD_SetWindow_Fill( REMIND_WINDOW_X, REMIND_WINDOW_Y, REMIND_WINDOW_X+REMIND_LENGTH, REMIND_WINDOW_Y+30, 0xfffff, 0xffff);//提示框
					switch(Language)
						{
						case CHN_HAN:
							Printf24("输入尺寸超过极限！",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,RED_COLOR,0,0xffff);
								break;
						case ENGLISH:
							Printf24("Data exceeds limit!",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,RED_COLOR,0,0xffff);
								break;
						}
					if(InputTouch_flag==1)   //触摸下
						{
						ClearCalculatorInput(); //清零计算器 输入
						}
					return 0;
					}
				else   //正确	 
					{
					PromptNum_dis();//输入范围 提示
					PromptDis_flag=1;
					return 1;
					}	
					break;
		case PROG_LABEL_MODE://	编程 标签	
		case TEACH_LABEL_MODE:// 示教 标签	
		case PROG_DIVIDE_MODE://编程 等分
		case TEACH_DIVIDE_MODE://示教 等分
		case AUTO_RULER_MODE://自动 基准
		case SELF_RULER_MODE://自刀 基准
		case MANUAL_RULER_MODE://手动 基准模式
				if(PorgSet_sel<1)
					{
					if((InputSize<Size_MIN_num)||(InputSize>Size_MAX_num))//超出范围
						{
						PromptDis_flag=0;
						GLCD_SetWindow_Fill( REMIND_WINDOW_X, REMIND_WINDOW_Y, REMIND_WINDOW_X+REMIND_LENGTH, REMIND_WINDOW_Y+30, 0xfffff, 0xffff);//提示框
						switch(Language)
							{
							case CHN_HAN:
								Printf24("输入尺寸超过极限！",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,RED_COLOR,0,0xffff);
								break;
							case ENGLISH:
								Printf24("Data exceeds limit!",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,RED_COLOR,0,0xffff);
								break;
							}
						if(InputTouch_flag==1)   //触摸下
							{
							ClearCalculatorInput(); //清零计算器 输入
							}	
						return 0;
						}
					else   //正确	 
						{
						PromptNum_dis();//输入范围 提示
						PromptDis_flag=1;
						return 1;
						}	
					}
				else
					{
					if((WorkMode&0x0f)==(PROG_DIVIDE_MODE&0x0f))  //等分
						{
						if(Unit==UNIT_MM)
							{
							InputSize=temp/100;
							}
						else
							{
							InputSize=temp/1000;
							}
						if((InputSize>0)&&(InputSize<=1000))
							return 1;
						return 0;	
						}
					else
						{
						InputSize=temp;
						if((InputSize>0)&&(InputSize<=Size_MAX_num))   //正确
							return 1;
						else
							{
							PromptDis_flag=0;
							GLCD_SetWindow_Fill( REMIND_WINDOW_X, REMIND_WINDOW_Y, REMIND_WINDOW_X+REMIND_LENGTH, REMIND_WINDOW_Y+30, 0xfffff, 0xffff);//提示框
							switch(Language)
								{
								case CHN_HAN:
									Printf24("输入尺寸超过极限！",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,RED_COLOR,0,0xffff);
									break;
								case ENGLISH:
									Printf24("Data exceeds limit!",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,RED_COLOR,0,0xffff);
									break;
								}
							}
						return 0;	
						}
					return 0;	
					}
				return 0;	
					break;
		case PROG_PRO_MODE:    //程序选择----------------------
		case TEACH_PRO_MODE:    //程序选择----------------------
				if(Unit==UNIT_MM)
					{
					InputSize=temp/100;
					}
				else
					{
					InputSize=temp/1000;
					}
				if((InputSize>0)&&(InputSize<=MAIX_PROG))// 有效
					{
					return 1;
					}
				return 0;	
					break;	
					
		case AUTO_TOOLS_MODE://自动  参数设置
		case SELF_TOOLS_MODE://自刀  参数设置
		case MANUAL_TOOLS_MODE:// 手动 参数模式
				if(Para_sel>8)
					{
					if(Unit==UNIT_MM)
						{
						InputSize=temp/100;
						}
					else
						{
						InputSize=temp/1000;
						}
					}
				return 1;	
					break;
		case AUTO_PLUS_MODE:  //F3++
		case AUTO_MINUS_MODE:// F4--
		case SELF_PLUS_MODE:  //F3++
		case SELF_MINUS_MODE:// F4--
				return 1;	
					break;
		case MANUAL_CLOCK_MODE: //手动 时钟模式
		case MANUAL_PASS_MODE: //密码模式	
		case MANUAL_PULSE_MODE://手动 脉冲当量
		case MANUAL_SERVO_C_MODE:// 手动直流伺服 C 参数 
				if(Unit==UNIT_MM)
					{
					InputSize=temp/100;
					}
				else
					{
					InputSize=temp/1000;
					}
				return 1;	
					break;
		 }
	return 0; 
	}
}

void LabelSel_dis(Int8U sel, Int8U flag)
{
switch(sel)
	{
	case 0://总长
		ProgSet_dis(Total_size, TOTAL_SIZE_X,  TOTAL_SIZE_Y,flag);
		if(flag==1)
			{
			PromptNum_dis();//输入范围
			PromptDis_flag=1;
			}
			break;
	case 1:	//标签长
		ProgSet_dis(Label_size, LABEL_SIZE_X,  LABEL_SIZE_Y,flag);
		if(flag==1)
			{
			PromptNum_dis();//输入范围
			// PromptDis_flag=1;
			PromptDis_flag=0;
			Printf24("0   ",REMIND_WINDOW_X+180,REMIND_WINDOW_Y+5,RED_COLOR,1,0xffff);
			}
			break;
	case 2://废边	
		ProgSet_dis(Waste_size, WASTE_SIZE_X,  WASTE_SIZE_Y,flag);
		if(flag==1)
			{
			PromptNum_dis();//输入范围
			// PromptDis_flag=1;
			PromptDis_flag=0;
			Printf24("0   ",REMIND_WINDOW_X+180,REMIND_WINDOW_Y+5,RED_COLOR,1,0xffff);
			}
			break;
	}
}

void Label_function(void)  //标签功能
{
Int16U order;
Int32U data,offset,add;
pInt8U pbuf;
Int8U j;

order=Knife_order;
pKnife_data=(pInt8U)&OneKnife_data;
//GetOneKnife_datas(order, pKnife_data);
if(Pro_data.pro_num<=(PROG_GROPU1+1))  //前301个prog
   {
   offset=PROG_BYTES1*(Pro_data.pro_num-1);
   }
else//后  199
   {
   offset=PROG_BYTES1*PROG_GROPU1+(Pro_data.pro_num-PROG_GROPU1-1)*PROG_BYTES2;
   }
pbuf=(pInt8U)(K_SIZE_sdram+offset+2+order*5);//程序基地址
add=DATA_SAVE_OFFSET+offset+2+order*5;

OneKnife_data.size=Total_size;  //尺寸修改
OneKnife_data.k_flag=NO_FLAG;  //清除 标志
SaveOneKnife_datas(Pro_data.pro_num, order++ , pKnife_data);//保存一刀数据
data=Total_size;
while(order<=MAIX_Knife)
	{
	if(data>Label_size)
	   {
	    data-=Label_size;
		if((data>=Size_MIN_num)&&(data<=Size_MAX_num))//数据有效
		  {
	      OneKnife_data.size=data;
		 // SaveOneKnife_datas(order++ , pKnife_data);//保存
		  for(j=0;j<5;j++)
			 {
			 *pbuf++=*(pKnife_data+j);
			 }
		  order++;
		  if(data>Waste_size)
		     {
			 data-=Waste_size;
			 if((data>=Size_MIN_num)&&(data<=Size_MAX_num))//数据有效
				{
				OneKnife_data.size=data;
				//SaveOneKnife_datas(order++ , pKnife_data);//保存
				for(j=0;j<5;j++)
					{
					*pbuf++=*(pKnife_data+j);
					}
			    order++;
				}
		     else
				break;
			 }
		  else
			 {
			 break;
			 }
	      }
		else
		  break;
	   }
	else
	   {
	   break;
	   }
	}
	
//-----显示
//CurrentArea_recover2(MIDDLE_PAGE_X , MIDDLE_PAGE_Y,  800, 269); //退出 标签画面
//  ------------更新编程 数据 显示
if(order>=Knife_sum)
   {
   if(order<=MAIX_Knife)
      {
	  Knife_sum=order-1;
	  }
   else
	  {
	  Knife_sum=MAIX_Knife;
	  }
   }
SaveKnife_sum(Pro_data.pro_num);//刀数 保存  
StepNum_dis(Knife_sum,Knife_order);//步骤更新
Size_1page_dis(Knife_order,cursor_row);	
SaveBuf_datas(Pro_data.pro_num,  Knife_order+1,  order-1); //保存
PromptNum_dis();//输入范围 提示
PromptDis_flag=1;
}

void CursorDown_inTable(void) //**** 光标下移 显示 数据
{
if(Knife_order<=MAIX_Knife)
	{
	if(Knife_order>Knife_sum) //回到 第一刀循环
		{
		CursorMov_dis(cursor_row, 0);//红色光标消失
		cursor_row=0;
		CursorMov_dis(cursor_row, 1);//红色光标显示
		Knife_order=1;//
		Size_1page_dis(Knife_order,0);//一页尺寸显示
		}	
	else
		{
		if(Knife_order==Knife_sum)
			{
			if(AutoRoute_flag==1) //自动 回到 第一刀循环
				{
				CursorMov_dis(cursor_row, 0);//红色光标消失
				cursor_row=0;
				CursorMov_dis(cursor_row, 1);//红色光标显示
				Knife_order=1;
				Size_1page_dis(Knife_order,0);//一页尺寸显示
				}
			else
				{
				Knife_order++;
				if(Knife_order<=MAIX_Knife)   //999 以内
					{
					if(cursor_row<(PAGE_KNIFE-1))
						{
						CursorMov_dis(cursor_row, 0);//红色光标消失
						OneKnifeDataSel_dis(Knife_order-1, cursor_row,0);  //一刀数据 高亮显示
						cursor_row++;
						CursorMov_dis(cursor_row, 1);//红色光标下移显示
						OneKnifeDataSel_dis(Knife_order, cursor_row,RED_COLOR);  //一刀数据 高亮显示
						}
					else   //页底
						{
						Size_1page_dis(Knife_order-(PAGE_KNIFE-1),0);//一页尺寸显示
						}
					}
				else  //999刀  回到 第一刀循环
					{
					CursorMov_dis(cursor_row, 0);//红色光标消失
					cursor_row=0;
					CursorMov_dis(cursor_row, 1);//红色光标显示
					Knife_order=1;
					Size_1page_dis(Knife_order,0);//一页尺寸显示
					}
				}
			}
		else
			{
			Knife_order++;
			if(Knife_order<=MAIX_Knife)   //999 以内
				{
				if(cursor_row<(PAGE_KNIFE-1))
					{
					CursorMov_dis(cursor_row, 0);//红色光标消失
					OneKnifeDataSel_dis(Knife_order-1, cursor_row,0);  //一刀数据 高亮显示
					cursor_row++;
					CursorMov_dis(cursor_row, 1);//红色光标下移显示
					OneKnifeDataSel_dis(Knife_order, cursor_row,RED_COLOR);  //一刀数据 高亮显示
					}
				else   //页底
					{
					Size_1page_dis(Knife_order-(PAGE_KNIFE-1),0);//一页尺寸显示
					}
				}
			else  //999刀  回到 第一刀循环
				{
				CursorMov_dis(cursor_row, 0);//红色光标消失
				cursor_row=0;
				CursorMov_dis(cursor_row, 1);//红色光标显示
				Knife_order=1;
				Size_1page_dis(Knife_order,0);//一页尺寸显示
				}
			}
		}
	if(Knife_order<=Knife_sum+1)
		StepOrder_dis(Knife_order);//步骤更新
	PromptNum_dis();//输入范围
	PromptDis_flag=1;
	}
}




void DivideSel_dis(Int8U sel, Int8U flag)
{
switch(sel)
	{
	case 0://总长
		ProgSet_dis(Total_size, DIVIDE_TOTAL_X,  DIVIDE_TOTAL_Y,flag);//
		if(flag==1)
			{
			PromptNum_dis();//输入范围
			PromptDis_flag=1;
			}
			break;
	case 1: //等分数
		ProgSet_dis(Divide_num, DIVIDE_NUM_X,  DIVIDE_NUM_Y,flag);
		if(flag==1)
			{
			PromptDis_flag=0;
			GLCD_SetWindow_Fill( REMIND_WINDOW_X, REMIND_WINDOW_Y, REMIND_WINDOW_X+REMIND_LENGTH, REMIND_WINDOW_Y+30, 0xfffff, 0xffff);//提示框
			switch(Language)
				{
				case CHN_HAN:
					Printf24("输入数值范围        到",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,BLACK_COLOR,0,0xffff);
						break;
				case ENGLISH:	
					Printf24("Data range          to",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,BLACK_COLOR,0,0xffff);
						break;
				}
			Printf24("1        1000",REMIND_WINDOW_X+180,REMIND_WINDOW_Y+5,RED_COLOR,0,0xffff);
			}
			break;
	}
}



void LabelEnter_exec(void) //标签 三组 数据设定确认
{
switch(PorgSet_sel)
	{
		case 0://总长
				if(CheckInputNums()==1)//数据有效
					{
					if(Total_size!=InputSize)
						{
						Total_size=InputSize;
						LabelSel_dis(PorgSet_sel++,0);
						LabelSel_dis(PorgSet_sel,1);
						}
					else
						{
						if(Label_size*Waste_size>=0) //数据 已经输入完毕
							{
							if(InputTouch_flag==1)   //触摸下  计算器 弹出框消失
								{
								CalcuInClear_exec();     //清除 计算器
								}
							}
						}
					}
				else
					num_cou=0;
					break;
		case 1://标签
				if(CheckInputNums()==1)//数据有效
					{
					if(Label_size!=InputSize)
						{
						Label_size=InputSize;//
						LabelSel_dis(PorgSet_sel++,0);
						LabelSel_dis(PorgSet_sel,1);
						}
					else
						{
						if(Total_size*Waste_size>0)
							{
							if(InputTouch_flag==1)   //触摸下  计算器 弹出框消失
								{
								CalcuInClear_exec();     //清除 计算器
								}
							}
						}
					}
				else
					num_cou=0;
					break;
		case 2://
				if(CheckInputNums()==1)//数据有效
					{
					if(Waste_size!=InputSize)
						{
						Waste_size=InputSize;//
						LabelSel_dis(PorgSet_sel,1);
						}
					else
						{
						if(Total_size*Label_size>0)
							{
							if(InputTouch_flag==1)   //触摸下  计算器 弹出框消失
								{
								CalcuInClear_exec();     //清除 计算器
								}
							}
						}
					}
				else
					num_cou=0;
					break; 
	}
if(InputTouch_flag==0)  //	 非 触摸计算器 下	
	ClrInput_function();//清零 输入框 		
}

void DivideEnter_exec(void) //等分 数据设定确认
{
Int32U d_num;
switch(PorgSet_sel)
	{
		case 0://总长
				if(CheckInputNums()==1)//数据有效
					{
					if(Total_size!=InputSize)
						{
						Total_size=InputSize;
						DivideSel_dis(PorgSet_sel,0);PorgSet_sel++;
						DivideSel_dis(PorgSet_sel,1);
						}
					else
						{
						if(Divide_num>0)
							{
							if(InputTouch_flag==1)   //触摸下  计算器 弹出框消失
								{
								CalcuInClear_exec();     //清除 计算器
								}
							}
						}
					}
				else
					num_cou=0;
					break;
		case 1://等分数
				if(CheckInputNums()==1)//数据有效
					{
					if(Divide_num!=InputSize)
						{
						Divide_num=InputSize;
						DivideSel_dis(PorgSet_sel,1);
						}
					else
						{
						if(Total_size>0)
							{
							if(InputTouch_flag==1)   //触摸下  计算器 弹出框消失
								{
								CalcuInClear_exec();     //清除 计算器
								}
							}
						}
					}
				else
					{
					num_cou=0;
					//GLCD_SetWindow_Fill( REMIND_WINDOW_X, REMIND_WINDOW_Y, REMIND_WINDOW_X+360, REMIND_WINDOW_Y+30, 0xfffff, 0xffff);//提示框
					//Printf24("输入数值范围出错!",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,RED_COLOR,0,0xffff);
					}
					break;
		
	}
if(InputTouch_flag==0)  //	 非 触摸计算器 下	
	ClrInput_function();//清零 输入框 		
}


void Divide_function(void)  //等分功能
{
Int16U order;
Int32U data,offset,add,d_size;
pInt8U pbuf;
Int8U j;

order=Knife_order;
pKnife_data=(pInt8U)&OneKnife_data;
//GetOneKnife_datas(order, pKnife_data);
if(Pro_data.pro_num<=(PROG_GROPU1+1))  //前301个prog
   {
   offset=PROG_BYTES1*(Pro_data.pro_num-1);
   }
else//后  199
   {
   offset=PROG_BYTES1*PROG_GROPU1+(Pro_data.pro_num-PROG_GROPU1-1)*PROG_BYTES2;
   }
pbuf=(pInt8U)(K_SIZE_sdram+offset+2+order*5);//程序基地址
add=DATA_SAVE_OFFSET+offset+2+order*5;

OneKnife_data.size=Total_size;  //尺寸修改
OneKnife_data.k_flag=NO_FLAG;  //清除 标志
SaveOneKnife_datas(Pro_data.pro_num, order++ , pKnife_data);//保存一刀数据
data=Total_size;
d_size=Total_size/Divide_num;
while(order<=MAIX_Knife)
	{
	if(data>d_size)
	   {
	    data-=d_size;
		if((data>=Size_MIN_num)&&(data<=Size_MAX_num))//数据有效
		  {
	      OneKnife_data.size=data;
		 // SaveOneKnife_datas(order++ , pKnife_data);//保存
		  for(j=0;j<5;j++)
			 {
			 *pbuf++=*(pKnife_data+j);
			 }
		  order++;
	      }
		else
		  break;
	   }
	else
	   {
	   break;
	   }
	}
	
//-----显示
//CurrentArea_recover2(MIDDLE_PAGE_X , MIDDLE_PAGE_Y,  800, 269); //退出 标签画面
//  ------------更新编程 数据 显示
if(order>=Knife_sum)
   {
   if(order<=MAIX_Knife)
      {
	  Knife_sum=order-1;
	  }
   else
	  {
	  Knife_sum=MAIX_Knife;
	  }
   }
SaveKnife_sum(Pro_data.pro_num);//刀数 保存  
StepNum_dis(Knife_sum,Knife_order);//步骤更新
Size_1page_dis(Knife_order,cursor_row);	
SaveBuf_datas(Pro_data.pro_num, Knife_order+1,  order-1); //保存
PromptNum_dis();//输入范围 提示
PromptDis_flag=1;
}

void ProEnter_exec(void)  //程序选择 输入确认
{
Int32U temp;
if(CheckInputNums()==1)// 有效
   {
    //GLCD_SetWindow_Fill( REMIND_WINDOW_X, REMIND_WINDOW_Y, REMIND_WINDOW_X+360, REMIND_WINDOW_Y+30, 0xfffff, 0xffff);//提示框
	//Printf24("输入数值范围    到",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,BLACK_COLOR,0,0xffff);
	//Printf24("1    500",REMIND_WINDOW_X+165,REMIND_WINDOW_Y+5,RED_COLOR,0,0xffff);
	if(InputTouch_flag==1)   //触摸下  计算器 弹出框消失
		{
		CalcuInClear_exec();     //清除 计算器
		}
	//----光标 跳转
	Pro_num=InputSize;//当前 程序号
	temp=InputSize%PAGE2_KNIFE;
	CursorMov_dis(cursor_temp,0);//光标
	if(temp<1)
	   temp=PAGE2_KNIFE;
	cursor_temp=temp-1;
	  
	CursorMov_dis(cursor_temp,1);//
	Prog_1page_dis(Pro_num-temp+1, 0);//===程序---数据显示
   }
else
   {
   num_cou=0;
  // PromptDis_flag=0;
  // GLCD_SetWindow_Fill( REMIND_WINDOW_X, REMIND_WINDOW_Y, REMIND_WINDOW_X+360, REMIND_WINDOW_Y+30, 0xfffff, 0xffff);//提示框
//	Printf24("输入数值范围出错!",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,RED_COLOR,0,0xffff);
   }
if(InputTouch_flag==0)  //	 非 触摸计算器 下
	ClrInput_function();//清零 输入框   
}

void ExportOnePro_dis(Int16U prog) //更新 显示一个程序-------------
{
Int16U x1,x2,y,back_color=0xef9f;
pInt8U pdata;

CurrentArea_recover2(MIDDLE_PAGE_X , MIDDLE_PAGE_Y, M_PAGE_WIDE, M_PAGE_HIGH);
x1=RIGHT_ARROW_X;
y=RIGHT_ARROW_Y;
x2=RED_KNIFE_X+25;
GLCD_SetWindow_Fill( x1, y, x2, y+225, back_color, back_color);//
//************当前pro 参数
Pro_data.pro_num=prog;
pdata=(pInt8U)&Pro_data;
SavePro_data(pdata);
if(prog<=PROG_GROPU1)//前 300个pro
   {
   MAIX_Knife=MAIX_KNIFE1;//999
   }
else
   {
   MAIX_Knife=MAIX_KNIFE2;//399
   } 
ReadOnePro_datas(prog);//读取 当前pro
ClrBuf_datas(prog, 1,MAIX_Knife);  //清零 刀数据buf
GetKnife_sum(prog); //获取前程序 刀数
 // Knife_sum=6;
ReadOnePro_datas(prog);//读取 一个pro

CheckKnifeSum_exec();  //--------------总刀数    核对
Knife_sum_before=Knife_sum;
//-------------更新 显示
cursor_temp=0;
Knife_order=1;
cursor_row=0;     // 在首行 显示 箭头
Size_1page_dis(Knife_order, 0);  
CursorMov_dis(cursor_row,1);//红色箭头  
ProNum_dis(prog);// 程序号 
StepNum_dis(Knife_sum,Knife_order);// 步骤号  总刀数-序号

PromptDis_flag=1;
PromptNum_dis();
LastAutoKnife_order=1;
}

void F3_AutoAdd_exec(Int32U add_data)  //F3++  批量数据 自加
{
Int16U order;
Int32U data;

order=Knife_order;
pKnife_data=(pInt8U)&OneKnife_data;
GetOneKnife_datas(Pro_data.pro_num, order, pKnife_data);
data=OneKnife_data.size+add_data;

if((data<=Size_MAX_num)&&(data>=Size_MIN_num)) //范围 内
	{
	PromptNum_dis();//输入范围 提示
	PromptDis_flag=1;
	OneKnife_data.size=data;
	SaveOneKnife_datas(Pro_data.pro_num, order++ , pKnife_data);//保存一刀数据
	
	while(order<=Knife_sum)
		{
		//pKnife_data=(pInt8U)&OneKnife_data;
		GetOneKnife_datas(Pro_data.pro_num, order-1, pKnife_data);//上一刀
		data=OneKnife_data.size;
		GetOneKnife_datas(Pro_data.pro_num, order, pKnife_data);//当前刀
		
		if(OneKnife_data.size>data)
			{
			//order++;
			break;
			}
		else
			{
			data=OneKnife_data.size+add_data;
			if((data>Size_MAX_num)||(data<Size_MIN_num)) //超出范围
			   {
			   order++;
			   break;
			   }
			else
			   {
			   OneKnife_data.size=data;
			   PutOneKnife_datas(Pro_data.pro_num, order, pKnife_data); //缓存 一刀数据
			   }
			}
		order++;
		}
	order--;
	//SaveKnife_sum(Pro_data.pro_num);//刀数 保存 
	StepNum_dis(Knife_sum,order);//步骤更新
	if(order-Knife_order+cursor_row>(PAGE_KNIFE-1)) //下页
		{
		CursorMov_dis(cursor_row, 0);//红色光标消失
		cursor_row=0;
		CursorMov_dis(cursor_row, 1);//红色光标显示
		Size_1page_dis(order,cursor_row);	
		}
	else
		{
		Size_1page_dis(Knife_order,cursor_row);
		CursorMov_dis(cursor_row, 0);//红色光标消失
		cursor_row+=order-Knife_order;
		CursorMov_dis(cursor_row, 1);//红色光标显示	
		}	
	SaveBuf_datas(Pro_data.pro_num, Knife_order+1,  order); //保存
	Knife_order=order;
	PromptNum_dis();//输入范围 提示	
	PromptDis_flag=1;
	}
}

void F4_AutoSub_exec(Int32U add_data)  //F4--  批量数据 自减
{
Int16U order;
Int32U data;

order=Knife_order;
pKnife_data=(pInt8U)&OneKnife_data;
GetOneKnife_datas(Pro_data.pro_num, order, pKnife_data);
if(OneKnife_data.size>add_data)
  {
  data=OneKnife_data.size-add_data;
  if((data<=Size_MAX_num)&&(data>=Size_MIN_num)) //范围 内
	 {
	 PromptNum_dis();//输入范围 提示
	 PromptDis_flag=1;
	 OneKnife_data.size=data;
	 SaveOneKnife_datas(Pro_data.pro_num, order++ , pKnife_data);//保存一刀数据
	
	 while(order<=Knife_sum)
		{
		//pKnife_data=(pInt8U)&OneKnife_data;
		GetOneKnife_datas(Pro_data.pro_num, order-1, pKnife_data);//上一刀
		data=OneKnife_data.size;
		GetOneKnife_datas(Pro_data.pro_num, order, pKnife_data);//当前刀
		if(OneKnife_data.size>data)
			{
			//order++;
			break;
			}
		else
			{
			if(OneKnife_data.size>add_data)
				{
				data=OneKnife_data.size-add_data;
				if((data>Size_MAX_num)||(data<Size_MIN_num)) //超出范围
					{
					order++;
					break;
					}
				else
					{
					OneKnife_data.size=data;
					PutOneKnife_datas(Pro_data.pro_num, order, pKnife_data); //缓存 一刀数据
					}
				}
			else
				break;
			}
		order++;
		}
	 order--;
	 //SaveKnife_sum(Pro_data.pro_num);//刀数 保存 
	 StepNum_dis(Knife_sum,order);//步骤更新
	 if(order-Knife_order+cursor_row>(PAGE_KNIFE-1)) //下页
		{
		CursorMov_dis(cursor_row, 0);//红色光标消失
		cursor_row=0;
		CursorMov_dis(cursor_row, 1);//红色光标显示
		Size_1page_dis(order,cursor_row);	
		}
	 else
		{
		Size_1page_dis(Knife_order,cursor_row);
		CursorMov_dis(cursor_row, 0);//红色光标消失
		cursor_row+=order-Knife_order;
		CursorMov_dis(cursor_row, 1);//红色光标显示	
		}	
 	 SaveBuf_datas(Pro_data.pro_num, Knife_order+1,  order); //保存
	 Knife_order=order;
	 PromptNum_dis();//输入范围 提示
	 PromptDis_flag=1;
	 }
  } 
   
}

void ReadOriginalSize(void)  //读取原点尺寸
{
pInt8U psize;
Int32U add;
Int16U n;
psize=(pInt8U)&OriginalSize;
add=ORIGINAL_25PEADD;

FastRead_Datas_Start(add);
for(n=0;n<4;n++)
	{
	*psize++=ReadFlash_Datas();
	}
FlashChip_Dis;
if(OriginalSize>999999)
	OriginalSize=123450;
}
void SaveOriginalSize(void)  //保存原点尺寸
{
pInt8U psize;
Int32U add;
psize=(pInt8U)&OriginalSize;
add=ORIGINAL_25PEADD;
Write_25pe_data(psize, add, 4);
}


void ReadFrontLimit(void)  //读取前极限
{
pInt8U psize;
Int32U add,temp;
Int16U n;
psize=(pInt8U)&FrontLimit;
add=ORIGINAL_25PEADD+4;

FastRead_Datas_Start(add);
for(n=0;n<4;n++)
	{
	*psize++=ReadFlash_Datas();
	}
FlashChip_Dis;
temp=FrontLimit;
if((temp<FRONT_LIM_MIN)||(temp>FRONT_LIM_MAX))
	{
	FrontLimit=3000;
	}
}
void SaveFrontLimit(void)  //保存前极限
{
pInt8U psize;
Int32U add;
psize=(pInt8U)&FrontLimit;
add=ORIGINAL_25PEADD+4;
Write_25pe_data(psize, add, 4);
}

void ReadMiddleLimit(void)  //读取中极限
{
pInt8U psize;
Int32U add,temp;
Int16U n;
psize=(pInt8U)&MiddleLimit;
add=ORIGINAL_25PEADD+8;

FastRead_Datas_Start(add);
for(n=0;n<4;n++)
	{
	*psize++=ReadFlash_Datas();
	}
FlashChip_Dis;
if((MiddleLimit<MIDD_LIM_MIN)||(MiddleLimit>MIDD_LIM_MAX))
	{
	MiddleLimit=8000;
	}
}
void SaveMiddleLimit(void)  //保存中极限
{
pInt8U psize;
Int32U add;
psize=(pInt8U)&MiddleLimit;
add=ORIGINAL_25PEADD+8;
Write_25pe_data(psize, add, 4);
}

void ReadBackLimit(void)  //读取后极限
{
pInt8U psize;
Int32U add,temp;
Int16U n;
psize=(pInt8U)&BackLimit;
add=ORIGINAL_25PEADD+12;

FastRead_Datas_Start(add);
for(n=0;n<4;n++)
	{
	*psize++=ReadFlash_Datas();
	}
FlashChip_Dis;
if((BackLimit<BACK_LIM_MIN)||(BackLimit>BACK_LIM_MAX))
	{
	BackLimit=138000;
	}
}
void SaveBackLimit(void)  //保存后极限
{
pInt8U psize;
Int32U add;
psize=(pInt8U)&BackLimit;
add=ORIGINAL_25PEADD+12;
Write_25pe_data(psize, add, 4);
}

void ReadLanguage(void)//读取语言
{
pInt8U psize;
Int32U add;
Int16U n;
psize=(pInt8U)&Language;
add=ORIGINAL_25PEADD+16;

FastRead_Datas_Start(add);

*psize=ReadFlash_Datas();
FlashChip_Dis;
if(Language>1)
	Language=0;
}
void SaveLanguage(void)  //保存语言
{
pInt8U psize;
Int32U add;
psize=(pInt8U)&Language;
add=ORIGINAL_25PEADD+16;
Write_25pe_data(psize, add, 1);
}

void ReadUnit(void)//读取单位
{
pInt8U psize;
Int32U add;
Int16U n;
psize=(pInt8U)&Unit;
add=ORIGINAL_25PEADD+18;

FastRead_Datas_Start(add);
*psize=ReadFlash_Datas();
FlashChip_Dis;	
if(Unit>UNIT_MIL)
	Unit=UNIT_MM;
}
void SaveUnit(void)  //保存单位
{
pInt8U psize;
Int32U add;
psize=(pInt8U)&Unit;
add=ORIGINAL_25PEADD+18;
Write_25pe_data(psize, add, 1);
}

void ReadAheader(void)//读取提前量
{
pInt8U psize;
Int32U add;
Int16U n;
psize=(pInt8U)&Aheader;
add=ORIGINAL_25PEADD+20;

FastRead_Datas_Start(add);
for(n=0;n<4;n++)
	{
	*psize++=ReadFlash_Datas();
	}
FlashChip_Dis;
if((Aheader<1)||(Aheader>100))
	{
	Aheader=25;
	}
}

void SaveAheader(void)  //保存提前量
{
pInt8U psize;
Int32U add;
psize=(pInt8U)&Aheader;
add=ORIGINAL_25PEADD+20;
Write_25pe_data(psize, add, 4);
}



void ReadDisWuCha(void)//读误差范围
{
pInt8U psize;
Int32U add;
Int16U n;
psize=(pInt8U)&DisWuCha;
add=ORIGINAL_25PEADD+24;

FastRead_Datas_Start(add);
for(n=0;n<4;n++)
	{
	*psize++=ReadFlash_Datas();
	}
FlashChip_Dis;
if((DisWuCha<20)||(DisWuCha>100))
	{
	DisWuCha=20;
	}
}

void SaveDisWuCha(void)//保存误差范围
{
pInt8U psize;
Int32U add;
psize=(pInt8U)&DisWuCha;
add=ORIGINAL_25PEADD+24;
Write_25pe_data(psize, add, 4);
	
}

/*
void ReadStanDistance(void)//读取标准距离
{
pInt8U psize;
Int32U add;
Int16U n;
psize=(pInt8U)&StanDistance;
add=ORIGINAL_25PEADD+24;

FastRead_Datas_Start(add);
for(n=0;n<4;n++)
	{
	*psize++=ReadFlash_Datas();
	}
FlashChip_Dis;
}
void SaveStanDistance(void)  //保存标准距离
{
pInt8U psize;
Int32U add;
psize=(pInt8U)&StanDistance;
add=ORIGINAL_25PEADD+24;
Write_25pe_data(psize, add, 4);
}*/

void Read_degree(void)
{
Int32U add;
add=ORIGINAL_25PEADD+30;

FastRead_Datas_Start(add);
Pulse_degree=ReadFlash_Datas();
FlashChip_Dis;
}
void Save_degree(void)
{
Int32U add;
pInt8U psize;
add=ORIGINAL_25PEADD+30;
psize=(pInt8U)&Pulse_degree;
Write_25pe_data(psize, add, 1);
}

void SetPulse_degree(void)  //设定脉冲当量
{
if(Pulse_degree>11)
	Pulse_degree=0;
switch(Pulse_degree)
	{
	case 0:
		maichongdangliang=5000;
		Z_Pulse=50;
		break;
	case 1:
		maichongdangliang=6000;
		Z_Pulse=50;
		break;	
	case 2:
		maichongdangliang=4000;
		Z_Pulse=50;
		break;
	case 3:
		maichongdangliang=9000;
		Z_Pulse=50;
		break;	
	case 4:
		maichongdangliang=5000;
		Z_Pulse=60;
		break;
	case 5:
		maichongdangliang=4166;
		Z_Pulse=60;
		break;	
	case 6:
		maichongdangliang=3333;
		Z_Pulse=60;
		break;
	case 7:
		maichongdangliang=7500;
		Z_Pulse=60;
		break;		
	case 8:
		maichongdangliang=2500;
		Z_Pulse=100;
		break;
	case 9:
		maichongdangliang=3000;
		Z_Pulse=100;
		break;	
	case 10:
		maichongdangliang=2083;
		Z_Pulse=120;
		break;		
	case 11:
		maichongdangliang=2500;
		Z_Pulse=120;
		break;	
	}	
	Z_Pulse*=4;
}



void SaveFirstDays(void)
{
Int32U add;
pInt8U psize;
add=ORIGINAL_25PEADD+32;
psize=(pInt8U)&FirstDays;
Write_25pe_data(psize, add, 4);
}
void ReadFirstDays(void)
{
Int32U add;
pInt8U psize;
add=ORIGINAL_25PEADD+32;
psize=(pInt8U)&FirstDays;

FastRead_Datas_Start(add);
for(n=0;n<4;n++)
	{
	*psize++=ReadFlash_Datas();
	}
FlashChip_Dis;
if(FirstDays>300)
	FirstDays=0;
}

void SaveSecondDays(void)
{
Int32U add;
pInt8U psize;
add=ORIGINAL_25PEADD+36;
psize=(pInt8U)&SecondDays;
Write_25pe_data(psize, add, 4);
}
void ReadSecondDays(void)
{
Int32U add;
pInt8U psize;
add=ORIGINAL_25PEADD+36;
psize=(pInt8U)&SecondDays;

FastRead_Datas_Start(add);
for(n=0;n<4;n++)
	{
	*psize++=ReadFlash_Datas();
	}
FlashChip_Dis;
if(SecondDays>300)
	SecondDays=0;
}

void SaveFirstDays_flag(void)
{
Int32U add;
pInt8U psize;
add=ORIGINAL_25PEADD+40;
psize=(pInt8U)&FirstDayValid_flag;
Write_25pe_data(psize, add, 1);
}
void ReadFirstDays_flag(void)
{
Int32U add;
pInt8U psize;
add=ORIGINAL_25PEADD+40;
psize=(pInt8U)&FirstDayValid_flag;

FastRead_Datas_Start(add);
for(n=0;n<1;n++)
	{
	*psize++=ReadFlash_Datas();
	}
FlashChip_Dis;
if(FirstDayValid_flag>1)
	FirstDayValid_flag=0;
}

void SaveSecondDays_flag(void)
{
Int32U add;
pInt8U psize;
add=ORIGINAL_25PEADD+41;
psize=(pInt8U)&SecondDayValid_flag;
Write_25pe_data(psize, add, 1);
}
void ReadSecondDays_flag(void)
{
Int32U add;
pInt8U psize;
add=ORIGINAL_25PEADD+41;
psize=(pInt8U)&SecondDayValid_flag;

FastRead_Datas_Start(add);
for(n=0;n<1;n++)
	{
	*psize++=ReadFlash_Datas();
	}
FlashChip_Dis;
if(SecondDayValid_flag>1)
	SecondDayValid_flag=0;
}

void ReadWorkDays(void)
{
Int32U add;
pInt8U psize;
add=ORIGINAL_25PEADD+42;
psize=(pInt8U)&Start_days;

FastRead_Datas_Start(add);
for(n=0;n<6;n++)
	{
	*psize++=ReadFlash_Datas();
	}
FlashChip_Dis;
}
void SaveWorkDays(void)
{
Int32U add;
pInt8U psize;
add=ORIGINAL_25PEADD+42;
psize=(pInt8U)&Start_days;
Write_25pe_data(psize, add, 6);
}

void ReadPushDistance(void)//读取自动推纸距离
{
pInt8U psize;
Int32U add;
Int16U n;
psize=(pInt8U)&AutoPushDistance;
add=ORIGINAL_25PEADD+50;

FastRead_Datas_Start(add);
for(n=0;n<4;n++)
	{
	*psize++=ReadFlash_Datas();
	}
FlashChip_Dis;
if(AutoPushDistance>AUTO_PUSH_DISTAN)
	AutoPushDistance=10000;
}
void SavePushDistance(void)  //保存自动推纸距离
{
pInt8U psize;
Int32U add;
psize=(pInt8U)&AutoPushDistance;
add=ORIGINAL_25PEADD+50;
Write_25pe_data(psize, add, 4);
}
/*
void ReadSpeedLevel(void)  //读取 速度档位数
{
Int32U add;
add=ORIGINAL_25PEADD+54;
FastRead_Datas_Start(add);
MotorSpeed_level=ReadFlash_Datas();
FlashChip_Dis;
if(MotorSpeed_level>2)
	MotorSpeed_level=0;
}
void SaveSpeedLevel(void)  //保存 速度档位数
{
pInt8U psize;
Int32U add;
psize=(pInt8U)&MotorSpeed_level;
add=ORIGINAL_25PEADD+54;
Write_25pe_data(psize, add, 1);
}*/
void ReadMachineType(void)  //机器类型
{
Int32U add;
add=ORIGINAL_25PEADD+54;
FastRead_Datas_Start(add);
MotorType=ReadFlash_Datas();
FlashChip_Dis;
if(MotorType>MOTOR_AC_SERVO)
	MotorType=MOTOR_FREQ_5_SPD_RST;	//0  ------变频器5挡
}
void SaveMachineType(void)  //机器类型
{
pInt8U psize;
Int32U add;
psize=(pInt8U)&MotorType;
add=ORIGINAL_25PEADD+54;
Write_25pe_data(psize, add, 1);
}

void ReadPressValid_flag(void)  //压纸 有效标志
{
Int32U add;
add=ORIGINAL_25PEADD+55;
FastRead_Datas_Start(add);
PressValid_flag=ReadFlash_Datas();
FlashChip_Dis;
if(PressValid_flag>1)
	PressValid_flag=0;
}
void SavePressValid_flag(void)
{
pInt8U psize;
Int32U add;
psize=(pInt8U)&PressValid_flag;
add=ORIGINAL_25PEADD+55;
Write_25pe_data(psize, add, 1);
}


void ReadACMotorSpeed(void)   //交流伺服 速度
{
Int32U add;
add=ORIGINAL_25PEADD+60;
FastRead_Datas_Start(add);
AC_MotorSPD=ReadFlash_Datas();
FlashChip_Dis;
if(AC_MotorSPD>32)//
	AC_MotorSPD=0;
}

void SaveACMotorSpeed(void)   //交流伺服 速度
{
pInt8U psize;
Int32U add;
psize=(pInt8U)&AC_MotorSPD;
add=ORIGINAL_25PEADD+60;
Write_25pe_data(psize, add, 1);
}

void ReadElectricWheelSwitch(void)//电子手轮
{
Int32U add;
// pInt8U pdata;
add=ORIGINAL_25PEADD+61;
FastRead_Datas_Start(add);
ElectricWheelOn_flag=ReadFlash_Datas();
FlashChip_Dis;
if(ElectricWheelOn_flag>1)
	ElectricWheelOn_flag=0;
}
void SaveElectricWheelSwitch(void)//电子手轮
{
Int32U add;
pInt8U pdata;
add=ORIGINAL_25PEADD+61;
pdata=(pInt8U)&ElectricWheelOn_flag;
Write_25pe_data(pdata, add, 1);
}

void ReadIRValidStatus(void)	//IR set
{
Int32U add;
// pInt8U pdata;
add=ORIGINAL_25PEADD+62;
FastRead_Datas_Start(add);
IR_SensorStus=ReadFlash_Datas();
FlashChip_Dis;
if(IR_SensorStus>1)
	IR_SensorStus=0;
}
void SaveIRValidStatus(void)
{
Int32U add;
pInt8U pdata;
add=ORIGINAL_25PEADD+62;
pdata=(pInt8U)&IR_SensorStus;
Write_25pe_data(pdata, add, 1);
}

void ReadACJogLevel(void)//ACJog
{
Int32U add;
// pInt8U pdata;
add=ORIGINAL_25PEADD+63;
FastRead_Datas_Start(add);
JogLevel=ReadFlash_Datas();
FlashChip_Dis;
if((JogLevel>5)||(JogLevel<1))
	JogLevel=1;
}
void SaveACJogLevel(void)//ACJog 
{
Int32U add;
pInt8U pdata;
add=ORIGINAL_25PEADD+63;
pdata=(pInt8U)&JogLevel;
Write_25pe_data(pdata, add, 1);
}

void ReadFrontValidStatus(void)//前极限valid
{
Int32U add;
// pInt8U pdata;
add=ORIGINAL_25PEADD+64;
FastRead_Datas_Start(add);
Front_LimitValid_flag=ReadFlash_Datas();
FlashChip_Dis;
}
void SaveFrontValidStatus(void)//
{
Int32U add;
pInt8U pdata;
add=ORIGINAL_25PEADD+64;
pdata=(pInt8U)&Front_LimitValid_flag;
Write_25pe_data(pdata, add, 1);	
}
void ReadMiddleValidStatus(void)//前极限valid
{
Int32U add;
// pInt8U pdata;
add=ORIGINAL_25PEADD+65;
FastRead_Datas_Start(add);
Middle_LimitValid_flag=ReadFlash_Datas();
FlashChip_Dis;
}
void SaveMiddleValidStatus(void)//
{
Int32U add;
pInt8U pdata;
add=ORIGINAL_25PEADD+65;
pdata=(pInt8U)&Middle_LimitValid_flag;
Write_25pe_data(pdata, add, 1);	
}
void ReadBackValidStatus(void)//前极限valid
{
Int32U add;
// pInt8U pdata;
add=ORIGINAL_25PEADD+66;
FastRead_Datas_Start(add);
Back_LimitValid_flag=ReadFlash_Datas();
FlashChip_Dis;
}
void SaveBackValidStatus(void)//
{
Int32U add;
pInt8U pdata;
add=ORIGINAL_25PEADD+66;
pdata=(pInt8U)&Back_LimitValid_flag;
Write_25pe_data(pdata, add, 1);	
}

//*******
void GeneratePassCode(void) //密码生成
{
Int32U temp;
srand(sys_tick);
temp=rand();
while(temp>100000)
	{
	temp=rand();
	}
	
//PassCheck=temp%100000;
PassCheck=temp;
PassCode=PASSCODE_formula(PassCheck);
}

void PassCheck_dis(Int16U x, Int16U y) //密码提示
{
Int8U num[6],n=0;
Int16U color=0xfc00;
GeneratePassCode();//密码生成
num[n++]=PassCheck/10000;
num[n++]=(PassCheck/1000)%10;
num[n++]=(PassCheck/100)%10;
num[n++]=(PassCheck/10)%10;
num[n++]=PassCheck%10;
for(n=0;n<5;n++)
	{
	num[n]+=48;
	}
num[n]=0;
Printf24(num,x,y,color,1,0xffff);//
}

Int16U Caluate_Days(void)
{
Int16U y1,m1,d1;
Int16U y2,m2,d2,time,days=0;
ReadWorkDays();
read_time();
y1=((Year>>4)&0x0f)*10+(Year&0x0f);
m1=((Month>>4)&0x0f)*10+(Month&0x0f);
d1=((Dom>>4)&0x0f)*10+(Dom&0x0f);
y2=((Start_days.year>>4)&0x0f)*10+(Start_days.year&0x0f);
m2=((Start_days.month>>4)&0x0f)*10+(Start_days.month&0x0f);
d2=((Start_days.day>>4)&0x0f)*10+(Start_days.day&0x0f);
if(y1>=y2)//时间正确
	{
	time=y1-y2;
	if(time>1)
		days=400; //时间到
	else
		{
		if(time>0)
		   {
		   days=(12-m2+1)*30-d2;//年前 剩余天数
		   days+=(m1-1)*30+d1;
		   }
		else //年内
		   {
		   if(m1>=m2)
			   {
			   time=m1-m2;
			   if(time>0)
				   {
					days=time*30+d1-d2;
				   }
			   else	
				   {
				   if(d1>=d2)
				      days=d1-d2;
				   }
			   }
		   }
		}
	}
return days;	
}

void DaysTime_check(void)
{
Int16U days;
//x=PASSCODE_X,y=PASSCODE_Y;
if(FirstDayValid_flag==1) //首次 时间限制 有效
	{
	days=Caluate_Days();
	Past_days=days; 
	if(Past_days>=FirstDays)// 时间 到
		{
		PassCodeEn_flag=1;
		}
	}
else
	{
	if(SecondDayValid_flag==1)
		{
		days=Caluate_Days();
		Past_days=days;  
		if(Past_days>=SecondDays)// 时间 到
			{
			PassCodeEn_flag=1;
			}
		}
	}
}

void RunTo_cursor(void) //运行至 光标处
{
pInt8U pKdata;
Int32U size_data;

pKdata=(pInt8U)&OneKnife_data;
GetOneKnife_datas(Pro_data.pro_num, Knife_order, pKdata);//
size_data=OneKnife_data.size;
if((size_data>=Size_MIN_num)&&(size_data<=Size_MAX_num))//数据有效
	{
	
	//SelfLockEn_flag=0;
	//ToTargetStop_flag=0;
	//if(1)
	if(size_data!=CurrentSize)
		{
		if(Unit==UNIT_MM)//mm
			{
			TargetSize=size_data;
			}
		else
			{
			TargetSize_inch=size_data;
			TargetSize=TargetSize_inch*2.54;
			}
			/////////////////////////////前10mm 结束///推纸////////////////////////////
		if((OneKnife_data.k_flag==PUSH_FLAG)&&(Knife_order<Knife_sum))//推纸 位置提前10mm 结束
			{
			if(CurrentSize>TargetSize)
				{
				if(CurrentSize-TargetSize>=1000)
					{
					TargetSize+=1000;
					}
				}
			else
				{
				if(TargetSize-CurrentSize>=1000)
					{
					TargetSize-=1000;
					}
				}
			}	
		TargetSize_temp=TargetSize;
		switch(MotorType)
			{
			case MOTOR_FREQ_5_SPD_RST:
			case MOTOR_FREQ_3_SPD:
			case MOTOR_FREQ_3_SPD_RST:
				 SelfLockEn_flag=0;
				 ToTargetStop_flag=0;
				 MoveSpeed=0;
				 MoveSpeedCtrl();  //运行速度控制
					break;
			case MOTOR_DC_SERVO:
			case MOTOR_DC670_SERVO:
			case MOTOR_DC670_SERVO_ZHU:
				 ServoSendCou=0;
				 DcServoStartRun_exec(TargetSize);
				// SelfLockEn_flag=0;
					break;
			case MOTOR_AC_SERVO:
				 ACMotorRunStart(TargetSize);
					break;		
			}
		RunStop_flag=0;
		Run_flag=1;
		InTargetPosit_flag=0;	//目标位置
		AutoCutStart_flag=0;
		PromptNum_dis();
		}
	}
}
void AutoRun_start(void)
{
pInt8U pKdata;
Int32U size_data,size_now;

pKdata=(pInt8U)&OneKnife_data;
GetOneKnife_datas(Pro_data.pro_num, Knife_order, pKdata);//
size_data=OneKnife_data.size;
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
if((size_data>=Size_MIN_num)&&(size_data<=Size_MAX_num))//数据有效
	{
	if(size_now==size_data)
		AutoRun_AutoPush_exec();  // 自动 循环运行
	else 
		RunTo_cursor();//    运行到当前刀
	}
}



//===================================计算器===========================
void Calcul_Nums(Int8U a_n1,Int8U a_n2,Int8U b_n1,Int8U b_n2, Int8U sign)  //输入框内数据  运算（3位小数即*1000） 得结果存入CalcData_temp
{
Int8U i,j,num_a[8],num_b[8];
Int64U d_temp1,d_temp2;
Int32U data;
d_temp1=0;
i=a_n1;
while(i<=a_n2)
	{
	if(CalcInput_Text[i]!='.')
		{
		d_temp1=d_temp1*10+CalcInput_Text[i];
		i++;
		}
	else
		{
		i++;
		break;
		}
	}
j=0;	
while(j<3)
	{
	if(i<=a_n2)
		{
		d_temp1=d_temp1*10+CalcInput_Text[i];
		i++;
		}
	else
		{
		d_temp1*=10;
		}
	j++;
	}	
//----------
d_temp2=0;
i=b_n1;
while(i<=b_n2)
	{
	if(CalcInput_Text[i]!='.')
		{
		d_temp2=d_temp2*10+CalcInput_Text[i];
		i++;
		}
	else
		{
		i++;
		break;
		}
	}
j=0;	
while(j<3)
	{
	if(i<=b_n2)
		{
		d_temp2=d_temp2*10+CalcInput_Text[i];
		i++;
		}
	else
		{
		d_temp2*=10;
		}
	j++;
	}	
switch(sign)
	{
	case '+':
		data=d_temp1+d_temp2;
		break;
	case '-':
		if(d_temp1>=d_temp2)         //无符号 防止溢出
			data=d_temp1-d_temp2;   
		else
			data=0;
		break;
	case '*':
		data=(d_temp1*d_temp2)/1000;
		break;
	case '/':
		data=d_temp1*1000/d_temp2;
		break;	
	}
CalcData_temp=data;
}

void DataConvert_to_Text(Int32U data_temp,pInt8U str_text)  //data_temp 转换成bcd 字符
{
Int8U i=0,j,n;
Int8U nums[12];
nums[i++]=data_temp/100000000;
nums[i++]=(data_temp/10000000)%10;
nums[i++]=(data_temp/1000000)%10;
nums[i++]=(data_temp/100000)%10;
nums[i++]=(data_temp/10000)%10;
nums[i++]=(data_temp/1000)%10;
nums[i++]='.';
nums[i++]=(data_temp/100)%10;
nums[i++]=(data_temp/10)%10;
nums[i++]=data_temp%10;
//nums[i]=0xff;
j=0;i=7;
while(j<6)
	{
	if(nums[j]==0)
		j++;
	else
		break;
	}
while(i<10)
	{
	if(nums[i]==0)
		i++;
	else
		break;	
	}	
//****	
n=0;CalcInput_cou=0;
if(i>=10)  //无小数部分
	{
	if(j>5)   //  整数部分 全为 0
		{
		str_text[n++]=0;
		CalcInput_cou=1;
		while(n<24)
			str_text[n++]=0xff;
		}
	else
		{    //整数部分  非0
		while(n<24)
			{
			if(j<6)
				{
				str_text[n++]=nums[j];
				CalcInput_cou++;
				j++;
				}
			else
				{
				str_text[n++]=0xff;
				}
			}
		}
	}	
else
	{
	if(j>5)//  整数部分 全为 0
		{
		j=5;
		}
	while(n<24)
		{
		if(j<10)
			{
			str_text[n++]=nums[j];
			CalcInput_cou++;
			j++;
			}
		else
			{
			str_text[n++]=0xff;
			}
		}
	}	
}

void CalculatorValue_exec(Int8U sign)  //根据 符号计算值 处理
{
Int8U sign_temp;
Int32U datas;
Int8U last_num;
num_cou=0;
Dot_flag=0;
if(CalcResultDis_flag==1)   //   已得到  运算结果 
	{
	last_num=CalcResult_Text[CalcInput_cou-1];   //结果框 最后一个字符
	}
else
	{
	last_num=CalcInput_Text[CalcInput_cou-1];   //输入框  最后一个字符
	}
	
if(CalcNoNumInput_flag==1)         //首字母  为符号
	{
	CalcNoNumInput_flag=0;
	CurrentToCalc_input();  //当前尺寸 数据更新到计算器
	CalcSign_order=CalcInput_cou; //符号 位置
	CalcInput_Text[CalcInput_cou++]=sign;
	CalcInputNums_dis(CalcInput_Text);
	}
else
	{
	if(last_num<42)  // 输入为 数字
		{
		if(CalcSign_order<1)  //-----------首个运算符  只显示
			{
			if(CalcResultDis_flag==1)   //   已得到  运算结果        
				{
				CalcResultDis_flag=0;  //结果显示 标志
				ClrCalcNums_text(CalcInput_Text,CAL_INPUT); 
				DataConvert_to_Text(CalcData_temp,CalcInput_Text);  //运算结果 更新到  输入框
				}
			CalcSign_order=CalcInput_cou; //符号 位置
			CalcInput_Text[CalcInput_cou++]=sign;
			CalcInputNums_dis(CalcInput_Text);
			}
		else            //-------------连续运算  
			{
			if(CalcResultDis_flag==1)   //   已得到  运算结果        
				{
				CalcResultDis_flag=0;  //结果显示 标志
				}
			else
				{
				sign_temp=CalcInput_Text[CalcSign_order];   //读取运算符
				Calcul_Nums(0,CalcSign_order-1  ,CalcSign_order+1,CalcInput_cou-1,sign_temp);//计算 两个数据结果 CalcData_temp
				}
			ClrCalcNums_text(CalcInput_Text,CAL_INPUT); //清计算器 输入框
			DataConvert_to_Text(CalcData_temp,CalcInput_Text);  //运算结果 更新到  输入框
			if(CalcInput_cou==0)
				CalcInput_cou++;
			CalcSign_order=CalcInput_cou; //首个运算符号 位置
			CalcInput_Text[CalcInput_cou++]=sign;
			CalcInputNums_dis(CalcInput_Text);
			}
		}
	}	

}

void CalcGetValue_exec(void)             //= 运算 所得结果
{
Int8U signal;
Dot_flag=0;
if((CalcInput_Text[CalcInput_cou-1]<42)&&(CalcInput_cou>0))  //输入框为数字 非运算符
	{
	if(CalcSign_order>0)  //计算 所得 结果
		{
		signal=CalcInput_Text[CalcSign_order];  //运算符 
		Calcul_Nums(0,CalcSign_order-1  ,CalcSign_order+1,CalcInput_cou-1,signal);//计算 两个数据结果 CalcData_temp
		}
	else  // 直接显示 到 结果框
		{
		CalcInput_Text[CalcInput_cou]=0;
		Calcul_Nums(0,CalcInput_cou-1,CalcInput_cou,CalcInput_cou,'+');//计算 ”单个数据+0“结果 CalcData_temp
		}
	//-------------运算结果显示
	ClrCalcNums_text(CalcResult_Text,CAL_RESULT); //清计算器 结果框
	DataConvert_to_Text(CalcData_temp,CalcResult_Text);  //运算结果	 转换为字符	
	CalcResultNums_dis(CalcResult_Text);//结果框 显示	
	
	CalcResultDis_flag=1;
	}
}
//===================================计算器===========================

void AutoRun_AutoPush_exec(void)  // 自动 循环运行
{
pInt8U pKdata;
Int32U size_data;
Int32U size_dd,data,AutoPush_num;
pKdata=(pInt8U)&OneKnife_data;
AutoRoute_flag=1;
if((AutoPushDistance>AUTO_PUSH_NO)&&(AutoPushDistance<=AUTO_PUSH_DISTAN))  //自动推纸 有效
	{
	if(AutoPushRun_flag==0)   //未运行到 自动推纸 距离
		{
		GetOneKnife_datas(Pro_data.pro_num, Knife_order, pKdata);//
		size_data=OneKnife_data.size;
		GetOneKnife_datas(Pro_data.pro_num, Knife_order+1, pKdata);//
		
		if(size_data<OneKnife_data.size)  //当前<下一刀      
			{
			if((size_data>=Size_MIN_num)&&(size_data<=Size_MAX_num))  //当前尺寸  有效
				{
				if(Unit==UNIT_MM)//mm
					AutoPush_num=AutoPushDistance;
				else	
					AutoPush_num=AutoPushDistance*100/254;
				if(size_data>AutoPush_num)
					{
					size_dd=size_data-AutoPush_num;
					if(size_dd>Size_MIN_num)
						data=size_dd;
					else
						data=Size_MIN_num;
					
					if(Unit==UNIT_MM)//mm
						{
						TargetSize=data;
						}
					else
						{
						TargetSize_inch=data;
						TargetSize=TargetSize_inch*2.54;
						}
					if(CurrentSize!=TargetSize)
						{
						TargetSize_temp=TargetSize;
						switch(MotorType)
							{
							case MOTOR_FREQ_5_SPD_RST:
							case MOTOR_FREQ_3_SPD:
							case MOTOR_FREQ_3_SPD_RST:
								 SelfLockEn_flag=0;
								 ToTargetStop_flag=0;
								 MoveSpeed=0;
								 MoveSpeedCtrl();  //运行速度控制
									break;
							case MOTOR_DC_SERVO:
							case MOTOR_DC670_SERVO:
							case MOTOR_DC670_SERVO_ZHU:
								 ServoSendCou=0;
								 DcServoStartRun_exec(TargetSize);
								// SelfLockEn_flag=0;
									break;
							case MOTOR_AC_SERVO:
								 ACMotorRunStart(TargetSize);
									break;		
							}
						Run_flag=1;
						RunStop_flag=0;
						InTargetPosit_flag=0;	//目标位置
						AutoPushRun_flag=1;
						AutoCutStart_flag=0;
						CursorDown_inTable();//**** 光标下移 显示 数据
						PromptNum_dis();
						}
					
					}
				else
					{
					if(Unit==UNIT_MM)//mm
						{
						TargetSize=Size_MIN_num;
						}
					else
						{
						TargetSize_inch=Size_MIN_num;
						TargetSize=TargetSize_inch*2.54;
						}
						/////////////////////////////前10mm 结束///推纸////////////////////////////
					if((OneKnife_data.k_flag==PUSH_FLAG)&&(Knife_order<Knife_sum))// 位置提前10mm 结束
						{
						if(CurrentSize>TargetSize)
							{
							if(CurrentSize-TargetSize>=1000)
								{
								TargetSize+=1000;
								}
							}
						else
							{
							if(TargetSize-CurrentSize>=1000)
								{
								TargetSize-=1000;
								}
							}
						}
					if(CurrentSize!=TargetSize)	
						{
						TargetSize_temp=TargetSize;	
						switch(MotorType)
							{
							case MOTOR_FREQ_5_SPD_RST:
							case MOTOR_FREQ_3_SPD:
							case MOTOR_FREQ_3_SPD_RST:
								 SelfLockEn_flag=0;
								 ToTargetStop_flag=0;
								 MoveSpeed=0;
								 MoveSpeedCtrl();  //运行速度控制
									break;
							case MOTOR_DC_SERVO:
							case MOTOR_DC670_SERVO:
							case MOTOR_DC670_SERVO_ZHU:
								ServoSendCou=0;
								 DcServoStartRun_exec(TargetSize);
								// SelfLockEn_flag=0;
									break;
							case MOTOR_AC_SERVO:
								ACMotorRunStart(TargetSize);
								// SelfLockEn_flag=0;
									break;
							}
						Run_flag=1;
						RunStop_flag=0;
						InTargetPosit_flag=0;	//目标位置
						AutoPushRun_flag=1;
						AutoCutStart_flag=0;
						CursorDown_inTable();//**** 光标下移 显示 数据
						PromptNum_dis();

						}
					}
				}
			}
		else//直接  运行到 下一刀
			{
			CursorDown_inTable();//**** 光标下移 显示 数据
			RunTo_cursor();//    运行到下一刀
			AutoPushRun_flag=0;
			}
		}
	}
else   //直接  运行到 下一刀
	{
	CursorDown_inTable();//**** 光标下移 显示 数据
	RunTo_cursor();//    运行到下一刀
	AutoPushRun_flag=0;
	}	
AutoRoute_flag=0;	
}

void StopMotorExec(void)  //变频  motor停止
{
ForceStop_flag=0;
BackStop_flag=0;
Backward_flag=0;
Forward_flag=0;	
//SelfLockEn_flag=0; //取消自锁


Run_flag=0;	
InTargetPosit_flag=0;	//目标位置
//AutoPushRun_flag=0; //自动推纸 运行
//TargetSize=0;
//TargetSize_temp=0;
//BeforeKnife_offset_in=0;
if(InputTouch_flag==0)
	{
//	ClrInput_function();//清零 输入框
	}
//PaperCutEnb_signal=1;	
//AutoRoute_flag=0;                                                        
}



void CheckKnifeSum_exec(void)  //--------------总刀数    核对
{
pInt8U pKdata;
Int32U size_data;
Int32U size_temp;
Int16U knife_temp;

pKdata=(pInt8U)&OneKnife_data;
GetOneKnife_datas(Pro_data.pro_num, Knife_sum, pKdata);//读取 最后一刀
size_data=OneKnife_data.size;
if((size_data>=Size_MIN_num)&&(size_data<=Size_MAX_num))  //当前尺寸  有效  （往下查找）-----这种情况  无影响
	{
	knife_temp=Knife_sum+1;
	while(knife_temp<=MAIX_Knife)
		{
		GetOneKnife_datas(Pro_data.pro_num,knife_temp , pKdata);//读取 下一刀  (正确应为0)
		size_temp=OneKnife_data.size;
		if((size_temp>=Size_MIN_num)&&(size_temp<=Size_MAX_num))  //当前尺寸  有效
			{
			knife_temp++;
			}
		else
			{
			break;
			}
		}
		
	if(knife_temp>Knife_sum+1)//刀数不对  更新
		{
		Knife_sum=knife_temp-1;
		SaveKnife_sum(Pro_data.pro_num);//刀数 保存  
		if(WorkStart_flag==1)
			StepNum_dis(Knife_sum,Knife_order);//步骤更新
		}
	}
else	//尺寸无效   （往上查找）
	{
	knife_temp=Knife_sum-1;
	while(knife_temp>1)
		{
		GetOneKnife_datas(Pro_data.pro_num,knife_temp , pKdata);//读取 前一刀  (正确应在极限范围)
		size_temp=OneKnife_data.size;
		if((size_temp>=Size_MIN_num)&&(size_temp<=Size_MAX_num))  //当前尺寸  有效
			{
			break;
			}
		else
			{
			knife_temp--;
			}
		}
	if(knife_temp<1)
		{
		if(Knife_sum!=1)
			{
			Knife_sum=1;
			SaveKnife_sum(Pro_data.pro_num);//刀数 保存  
			ClrBuf_datas(Pro_data.pro_num, 1,MAIX_Knife);  //清零 刀数据buf
			ReadOnePro_datas(Pro_data.pro_num);//读取 当前pro
			if(WorkStart_flag==1)
				StepNum_dis(Knife_sum,Knife_order);//步骤更新
			}
		}
	else
		{
		Knife_sum=knife_temp;
		SaveKnife_sum(Pro_data.pro_num);//刀数 保存
		ClrBuf_datas(Pro_data.pro_num, 1,MAIX_Knife);  //清零 刀数据buf
		ReadOnePro_datas(Pro_data.pro_num);//读取 当前pro
		if(WorkStart_flag==1)
			StepNum_dis(Knife_sum,Knife_order);//步骤更新
		}
	}
}



void GetAC_MotorSpeed(void)  //交流伺服  速度判定
{
Int16U j;
//ReadACMotorSpeed();
switch(AC_MotorSPD)
	{
	case 0:   //0--速度
			for(j=0;j<120;j++)
				waitTemp[j]=waitTb1[j];
			break;
	case 1:   //1--速度
			for(j=0;j<120;j++)
				waitTemp[j]=waitTb2[j];
			break;	
	case 2:   //2--速度
			for(j=0;j<120;j++)
				waitTemp[j]=waitTb3[j];
			break;
	case 3:   //3--速度
			for(j=0;j<120;j++)
				waitTemp[j]=waitTb4[j];
			break;	
	case 4:   //4--速度
			for(j=0;j<120;j++)
				waitTemp[j]=waitTb5[j];
			break;
	case 5:   //5--速度
			for(j=0;j<120;j++)
				waitTemp[j]=waitTb6[j];
			break;	
	case 6:   //6--速度
			for(j=0;j<120;j++)
				waitTemp[j]=waitTb7[j];
			break;	
	case 7:   //7--速度
			for(j=0;j<120;j++)
				waitTemp[j]=waitTb8[j];
			break;	
	case 8:   //8--速度
			for(j=0;j<120;j++)
				waitTemp[j]=waitTb9[j];
			break;
	case 9:   //9--速度
			for(j=0;j<120;j++)
				waitTemp[j]=waitTb10[j];
			break;	
	case 10:   //10--速度
			for(j=0;j<120;j++)
				waitTemp[j]=waitTb11[j];
			break;
	case 11:   //11--速度
			for(j=0;j<120;j++)
				waitTemp[j]=waitTb12[j];
			break;		
	//******************************++++++++++++++++++++++++++++++++++			
	case 12:   //2--速度
			for(j=0;j<120;j++)
				waitTemp[j]=waitTb13[j];
			break;
	case 13:   //3--速度
			for(j=0;j<120;j++)
				waitTemp[j]=waitTb14[j];
			break;	
	case 14:   //4--速度
			for(j=0;j<120;j++)
				waitTemp[j]=waitTb15[j];
			break;
	case 15:   //5--速度
			for(j=0;j<120;j++)
				waitTemp[j]=waitTb16[j];
			break;	
	case 16:   //6--速度
			for(j=0;j<120;j++)
				waitTemp[j]=waitTb17[j];
			break;	
	case 17:   //7--速度
			for(j=0;j<120;j++)
				waitTemp[j]=waitTb18[j];
			break;	
	case 18:   //8--速度
			for(j=0;j<120;j++)
				waitTemp[j]=waitTb19[j];
			break;
	case 19:   //9--速度
			for(j=0;j<120;j++)
				waitTemp[j]=waitTb20[j];
			break;	
	case 20:   //10--速度
			for(j=0;j<120;j++)
				waitTemp[j]=waitTb21[j];
			break;
	case 21:   //11--速度
			for(j=0;j<120;j++)
				waitTemp[j]=waitTb22[j];
			break;				
	case 22:   //10--速度
			for(j=0;j<120;j++)
				waitTemp[j]=waitTb23[j];
			break;
	case 23:   //11--速度
			for(j=0;j<120;j++)
				waitTemp[j]=waitTb24[j];
			break;			
//************20180516			
	case 24:   //11--速度
			for(j=0;j<120;j++)
				waitTemp[j]=waitTb25[j];
			break;				
	case 25:   //10--速度
			for(j=0;j<120;j++)
				waitTemp[j]=waitTb26[j];
			break;
	case 26:   //11--速度
			for(j=0;j<120;j++)
				waitTemp[j]=waitTb27[j];
			break;					
	case 27:   //10--速度
			for(j=0;j<120;j++)
				waitTemp[j]=waitTb28[j];
			break;
	case 28:   //11--速度
			for(j=0;j<120;j++)
				waitTemp[j]=waitTb29[j];
			break;			
	case 29:   //11--速度
			for(j=0;j<120;j++)
				waitTemp[j]=waitTb30[j];
			break;				
	case 30:   //10--速度
			for(j=0;j<120;j++)
				waitTemp[j]=waitTb31[j];
			break;
	case 31:   //11--速度
			for(j=0;j<120;j++)
				waitTemp[j]=waitTb32[j];
			break;	
	case 32:   //11--速度
			for(j=0;j<120;j++)
				waitTemp[j]=waitTb33[j];
			break;	
	}
}

