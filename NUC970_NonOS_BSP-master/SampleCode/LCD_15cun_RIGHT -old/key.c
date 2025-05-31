/*

键扫描   1MS进入一次


*/

#include"key.h"
//#include"at45dbnew.h"
#include"m25pe16.h"
#include"chndot.h"
//#include"realtime.h"
#include"io.h"
#include "timer.h" //  此行需恢复

#include "pic_exec.h"

#include "test_io.h"
#include "modbus.h"


#include"port.h"
#include"servo.h"
#include"keyboard.h"

#include"name_input.h"

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


unsigned int Total_size=0;//总长
unsigned int Label_size=0;//标签长
unsigned int Waste_size=0;//废边
unsigned int Divide_num=0;//等分数
 

unsigned char cursor_pro;
unsigned long int maichongdangliang,xxmuqiancn;





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
Int32U Z_Pulse_before;
Int8U Z_Pulse_start_flag;
Int8U Z_Pulse_err_flag;
Int32U PulseAB_Z_current;
Int8U PulseAB_Z_save_time=0;

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
Int8U SubLine_flag;

Int16U FirstKnife_num;
Int16U LastKnife_num_temp;

Int8U MainMode_temp;
Int8U F5AllKnifeF_SetFlag;

Int8U PressCircle_mode=0;
Int8U AutoCutDisable_flag=0;


void BellOn_Enb(void)
{
labatime=0;
 BellOUT_ON;flaglaba=1;
}


void KeyScan(void)  //键扫描   1MS进入一次
{
unsigned long int j;  

// // Key_Enable(ENABLE);
// // if(KeyDown_Flag==0)
	// // {
// // //	KeyCode=KEYIO;   //读入键码  不同的端口状态修改此行
	// // if(KeyCheck()!=0)   //判断是否有键按下
		// // {
		// // KeyDown_Flag=1;    //置键按下标志位
		// // KeyDownTime=0;
		// // }
	// // }
// // else
	// // {
	// // if(KeyExec_Flag==0)
		// // {
	// // //	KeyCode=KEYIO;   //读入键码  不同的端口状态修改此行
		// // if(KeyCheck()!=0)   //判断是否有键按下
			// // {
			// // KeyDownTime++;
			// // if(KeyDownTime>=20)  //按下键 去抖动10MS
				// // {
				// // KeyDownTime=0;
				// // KeyReadCode();//读取键值 
				// // KeyCode_Temp=KeyCode;

				// // ////////////////////////////
                                  // // flagkeysong=0;
				// // //  以下为键按下处理
				// // ////////////////////////////
				// // switch(Board_TestMod)
					// // {
					// // case 0:
					// // case TEST_TOUCH:
					// // case TEST_ICON:
						// // KeyExec(KeyCode); //调键处理
							// // break;
					// // case TEST_BOARD://测试 模式  3
						// // BellOn_Enb();
						// // KeyDis_sel(KeyCode_Temp,1);  //***************按键显示 
							// // break;
					// // case TEST_SYS_TYPE://设定  档位4
						// // BellOn_Enb();
						// // ShiftSpeed_SetExec(KeyCode); 
							// // break;
					// // }
				// // KeyExec_Flag=1; //置键处理标志位
				// // }
			// // }
		// // else
			// // {  //抖动引起。退出
			// // KeyDown_Flag=0;
			// // }
		// // }
	// // else
		// // {
// // //		KeyCode=KEYIO;   //读入键码  不同的端口状态修改此行
		// // if(KeyCheck()==0)   //判断是否有键按下		if(KeyCode==0)
			// // {
			// // KeyDownTime++;
			// // if(KeyDownTime>=10)  //------------释放键 去抖动10MS
				// // {
				// // KeyDown_Flag=0;   //清按下标志位
				// // KeyExec_Flag=0;   //清键处理标志位
				// // KeyLongDownTime=0;  //清键长按计时
				// // //KeyLongDown_Flag=0;
                 // // LongExec_flag=0;  
				// // ////////////////////////////
				// // GoFrontEn_flag=0;
				// // GoBackEn_flag=0;
				// // if(Board_TestMod==TEST_BOARD)
					// // {
					// // KeyDis_sel(KeyCode_Temp,0); //***************按键显示
					// // MoveStop();
					// // RLOUT1_OFF;    // 允许裁切
					// // }
					
				// // //----------------------------------------
				
				
				 // // ACMotor_ReleaseStop();  //-------
				 	
				// // }
			// // }
		// // else
			// // {
			// // KeyDownTime=0;
			
			// // if(LongExec_flag==0)
			    // // {
				  // // KeyReadCode();//读取键值
				  // // MultiKey_exec(KeyCode);  //组合键处理
				  // // //if(KeyCode!=KeyCode_Temp)
				   // // //  {
					 
					// // // }
				// // }
			
			// // if(KeyLongDownTime<KEYLONGDOWNTIMEDATA)
				// // {
				// // KeyLongDownTime++;
                // // }             
			// // else//----------长按处理------------
			   // // {
			   // // if(LongExec_flag==0)
			      // // {
				  // // LongExec_flag=1;
				  // // //KeyReadCode();//读取键值
				  // // LongKey_exec(KeyCode , KeyCode_Temp);  //长按键处理
				  // // }
			   // // }
								
			// // }
		// // }
	// // }
// // Key_Enable(DISABLE);
}

void NumKey_exec(Int8U num)
{
Int8U c_t;
volatile Int16U temp=0;
if(WorkStart_flag==1)
	{
	if(Run_flag==0)
		{
		if(WorkMode==READ_PRO_MESS_MODE)
			{
			ProNameInput_dis(num);	//输入法
			}
		else
			{
			if(CalcResultDis_flag==1)
				{
				ClrCalcNums_text(CalcInput_Text,CAL_INPUT); //清计算器 输入框
				CalcInput_cou=0;
				num_cou=0;
				CalcResultDis_flag=0;  //结果显示 标志
				CalcSign_order=0;//首个运算符 位置
				}
			if(num_cou<7)//
				{		
				CalcNoNumInput_flag=0;	
				if(num!='.')
					{
					CalcInput_Text[CalcInput_cou++]=num;
					CalcInputNums_dis(CalcInput_Text);	
					num_cou++;
					}
				else
					{
					if(Dot_flag==0)	
						{
						Dot_flag=1;
						CalcInput_Text[CalcInput_cou++]=num;
						CalcInputNums_dis(CalcInput_Text);	
						num_cou++;
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
	else if(Board_TestMod==TEST_SYS_WORD)//  系统版本选择  密码
		{
		if((num_cou<6)&&(num!='.'))
			{
			Size_temp[num_cou++]=num;
			SysBoardNum_dis(Size_temp,num_cou);//密码
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
num_cou=0;
}
void CalcuInClear_exec(void)     //清除 计算器
{
// CurrentArea_recover3(CALCUL_WIN_X,CALCUL_WIN_Y,CALCUL_WIDE,CALCUL_HIGH);
// ButtonTouch_mode=0;
// Dot_flag=0;
// num_cou=0;

// CalcResultDis_flag=0;
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


//------------
void ArithmeticInputSize(void)  //对当前尺寸 算数计算
{
volatile Int32U newsize_temp=0,prev_data;
volatile Int8U Flg_chg=0,flag_now;
if((Knife_order<=MAX_Knife)&&(Knife_order>1))	//刀数据 未满
	{
	CheckInputNums();
	if(InputSize>0)
		{
		pKnife_data=(pInt8U)&OneKnife_data;
		GetOneKnife_datas(Pro_data.pro_num, Knife_order-1, pKnife_data);// 读取当前刀 尺寸
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
			GLCD_SetWindow_Fill( SIZE_WINDOW_X, SIZE_WINDOW_Y, SIZE_WINDOW_X+SIZE_WINDOW_WIDE, SIZE_WINDOW_Y+SIZE_WINDOW_HIGH, 0xfffff, 0xffff);//尺寸输入框
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
				case INDONSIA:	//印尼	
						Printf24("Input data melebihi batas",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,RED_COLOR,0,0xffff);
								break;
				case PORTUGAL:	//葡萄牙
						Printf16("Dados de entrada excede o limite",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,RED_COLOR,0,0xffff);
						break;
				case SPANISH: //西班牙
						Printf16("Los datos de entrada excede el límite",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,RED_COLOR,0,0xffff);
						break;
				}
			
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
			RenewModifyDate();	//更新时间信息-.-.-.-.-.-.-.-.-.-.-.-.-.-
			//----保存数据----------------
			GetOneKnife_datas(Pro_data.pro_num, Knife_order, pKnife_data);// 读取  当前刀
			OneKnife_data.size=newsize_temp;  //尺寸修改
			if((OneKnife_data.k_flag&0xf)==KNIFE_FLAG)
				{
				if(newsize_temp>prev_data)
					{
					OneKnife_data.k_flag&=0xf0; //刀 标志清除
					Flg_chg=1;
					flag_now=OneKnife_data.k_flag;
					}
				}
			SaveOneKnife_datas(Pro_data.pro_num, Knife_order , pKnife_data);//保存一刀数据
			//************next
			if((Knife_order+1)<=OnePro_head.pro_knifeSUM)
				{
				GetOneKnife_datas(Pro_data.pro_num, Knife_order+1, pKnife_data);// 当前光标的下一刀 数据
				 if((OneKnife_data.k_flag&0xf)==KNIFE_FLAG) //刀 标志
					{
					if(OneKnife_data.size>newsize_temp)
						{
						OneKnife_data.k_flag&=0xf0;	//清除 刀 标志
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
			//---------显示----	
			if(Knife_order>OnePro_head.pro_knifeSUM)//更新步骤 总刀数
				{
				OnePro_head.pro_knifeSUM=Knife_order;		//
				SavePro_headInfo(Pro_data.pro_num, (pInt8U)&OnePro_head);
				}
			if(Knife_order<MAX_Knife)	//刀数据 未满---------------下移
				{
				Knife_order++;
				if(cursor_row<(PageKf_Size-1))
					{
					CursorKnife_dis(cursor_row, 0);//红色光标消失
					OneKnifeDataSel_dis(Knife_order-1, cursor_row,0);  //一刀数据 高亮消失
					cursor_row++;
					CursorKnife_dis(cursor_row, 1);//红色光标下移显示
					OneKnifeDataSel_dis(Knife_order, cursor_row,RED_COLOR);  //一刀数据 高亮显示
					// // if((ButtonTouch_mode==0)||(ButtonTouch_mode==TOU_MODE_F4)) //	 非 触摸计算器 下
					if(ButtonTouch_mode==0) //	 非 触摸计算器 下
						{
						switch(Flg_chg)
							{
							case 1:
								AllFlagPic_dis(cursor_row,flag_now); // 标记图片 显示
								break;
							case 2:
								AllFlagPic_dis(cursor_row+1,OneKnife_data.k_flag); //光标处 标记图片 显示
								break;
							case 3:
								AllFlagPic_dis(cursor_row,flag_now); // 标记图片 显示
								AllFlagPic_dis(cursor_row+1,OneKnife_data.k_flag); //光标处 标记图片 显示
								break;
							}
						}
					}
				else   //页底
					{
					Size_1page_dis(Knife_order-(PageKf_Size-1),0);//一页尺寸显示
					}
				}
			StepNum_dis(OnePro_head.pro_knifeSUM,Knife_order);//步骤更新	
			//--------刀数据 显示	
			/***
			if(Knife_order<=OnePro_head.pro_knifeSUM)  //刀数 未新增加 000.00
				{
				Knife_order++;
				GetOneKnife_datas(Pro_data.pro_num, Knife_order, pKnife_data);// 读取  下一刀
				OneKnife_data.size=newsize_temp;  //尺寸修改
				if(Knife_order<=OnePro_head.pro_knifeSUM)// 未超过最后一刀
					{
					if((OneKnife_data.k_flag&0xf)==KNIFE_FLAG)
						{
						if(newsize_temp>prev_data)
							{
							OneKnife_data.k_flag&=0xf0; //刀 标志清除
							Flg_chg=1;
							flag_now=OneKnife_data.k_flag;
							}
						}
					}
				SaveOneKnife_datas(Pro_data.pro_num, Knife_order , pKnife_data);//保存一刀数据
				if((Knife_order+1)<=OnePro_head.pro_knifeSUM)
					{
					GetOneKnife_datas(Pro_data.pro_num, Knife_order+1, pKnife_data);// 当前光标的下一刀 数据
					 if((OneKnife_data.k_flag&0xf)==KNIFE_FLAG) //刀 标志
						{
						if(OneKnife_data.size>newsize_temp)
							{
							OneKnife_data.k_flag&=0xf0;	//清除 刀 标志
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
				if(Knife_order>OnePro_head.pro_knifeSUM)//更新步骤 总刀数
					{
					OnePro_head.pro_knifeSUM=Knife_order;		//
					SavePro_headInfo(Pro_data.pro_num, (pInt8U)&OnePro_head);
					}
				StepNum_dis(OnePro_head.pro_knifeSUM,Knife_order);//步骤更新	
				//--------刀数据 显示	
				
				if(cursor_row<(PageKf_Size-1))
					{
					CursorKnife_dis(cursor_row, 0);//红色光标消失
					OneKnifeDataSel_dis(Knife_order-1, cursor_row,0);  //一刀数据 高亮消失
					cursor_row++;
					CursorKnife_dis(cursor_row, 1);//红色光标下移显示
					OneKnifeDataSel_dis(Knife_order, cursor_row,RED_COLOR);  //一刀数据 高亮显示
					if((ButtonTouch_mode==0)||(ButtonTouch_mode==TOU_MODE_F4)) //	 非 触摸计算器 下
						{
						switch(Flg_chg)
							{
							case 1:
								AllFlagPic_dis(cursor_row,flag_now); // 标记图片 显示
								break;
							case 2:
								AllFlagPic_dis(cursor_row+1,OneKnife_data.k_flag); //光标处 标记图片 显示
								break;
							case 3:
								AllFlagPic_dis(cursor_row,flag_now); // 标记图片 显示
								AllFlagPic_dis(cursor_row+1,OneKnife_data.k_flag); //光标处 标记图片 显示
								break;
							}
						}
					}
				else   //页底
					{
					Size_1page_dis(Knife_order-(PageKf_Size-1),0);//一页尺寸显示
					}
				}
				**/
				 
			PromptNum_dis();//输入范围 提示
			PromptDis_flag=1;	
			GLCD_SetWindow_Fill( SIZE_WINDOW_X, SIZE_WINDOW_Y, SIZE_WINDOW_X+SIZE_WINDOW_WIDE, SIZE_WINDOW_Y+SIZE_WINDOW_HIGH, 0xfffff, 0xffff);//尺寸输入框 符号	
			}
			
		}
	}
ClrInput_function();//清零 输入框
Arithmetic_mode=0;
}


/***
void ShowTouchWind(void)//弹出触摸window
{
// ClrInput_function();//清零 输入框
	//弹出 计算器
CalcNoNumInput_flag=1;
Dot_flag=0;
CalcSign_order=0;//首个运算符 位置
CalcData_temp=0;
CalcResultDis_flag=0;
num_cou=0;
if(Sign_flag==1)//清除 加,减号
	{
	// GLCD_SetWindow_Fill( SIZE_WINDOW_X, SIZE_WINDOW_Y, SIZE_WINDOW_X+SIZE_WINDOW_WIDE, SIZE_WINDOW_Y+SIZE_WINDOW_HIGH, 0xfffff, 0xffff);//尺寸输入框
	Sign_flag=0;
	}

CalcInput_cou=0;
Calculator_Window();  //计算器 按钮	
ClrCalcNums_text(CalcInput_Text,CAL_INPUT); //清计算器 输入框
ClrCalcNums_text(CalcResult_Text,CAL_RESULT); //清计算器 结果框 
CalcInputNums_dis(CalcInput_Text);  //输入框 显示
CalcResultNums_dis(CalcResult_Text);//结果框 显示
ButtonTouch_mode=TOU_MODE_CALC;
}**/

void KeyExec(Int32U keycode)  //键处理....................................
{
Int32U d_temp=0;
Int32U target_temp;
Int32U input_temp,perv_data;
	 
Int16U x,y,gap,back_color,line_color,tx_wide=148;

Int16U g,K_temp;
Int8U knife_set_flag=0,Flg_chg=0,flag_now;
pInt8U pbuf;
Int32U offset;
volatile Int32U current_temp,step_temp;
BellOn_Enb();
switch(keycode)
	{
	case SHIFT_KEY_CODE:	//shift--
			if(ShiftKey_flag==1)
				{//shift------ 提示
				// if(ButtonTouch_mode==TOU_MODE_F4)
					// {
					// GLCD_SetWindow_Fill( REMIND_WINDOW_X, REMIND_WINDOW_Y, REMIND_WINDOW_X+REMIND_LENGTH, REMIND_WINDOW_Y+30, 0xfffff, 0xffff);//提示框
					// switch(Language)
							// {
							// case CHN_HAN:
								// Printf16("shift+F5,添加/清除全刀标记",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,BLACK_COLOR,0,0xffff);
									// break;
							// case ENGLISH:	
								// Printf16("shift+F5,set/clr all Knife-flag",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,BLACK_COLOR,0,0xffff);
									// break;
							// case INDONSIA:	//印尼	
								// Printf16("shift+F5,menambah/menghapus K-flag",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,BLACK_COLOR,0,0xffff);
									// break;
							// case PORTUGAL:	//葡萄牙
								// Printf16("shift+F5,Modificar todas as tags KNIF",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,BLACK_COLOR,0,0xffff);
									// break;
							// case SPANISH: //西班牙
								// Printf16("shift+F5,Modificar Todos los tags KNIF",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,BLACK_COLOR,0,0xffff);
									// break;
							// }
					// }
				}
				break;
	case SHIFT_0_KEY_CODE:	//shift+0------ 气垫标记
			if(WorkStart_flag==1)
			  {
			  if(Run_flag==0)
				 {
				 if(WorkMode==AUTO_MODE)//自动--  主画面下
					AllFlagSetExec(AIR_FLAG); //设定 气垫标记
				 }	
			  }
			  break;		
	case SHIFT_1_KEY_CODE:	//shift+1------ 压纸标记
			if(WorkStart_flag==1)
			  {
			  if(Run_flag==0)
				 {
				 if(WorkMode==AUTO_MODE)//自动--  主画面下
					AllFlagSetExec(PRESS_FLAG); //设定  压纸标记
				 }	
			  }
			  break;	  
	case SHIFT_2_KEY_CODE:	//shift+2------ 理纸标记
			if(WorkStart_flag==1)
			  {
			  if(Run_flag==0)
				 {
				 if(WorkMode==AUTO_MODE)//自动--  主画面下
					AllFlagSetExec(SORT_FLAG); //设定  理纸标记
				 }	
			  }
			  break;	
	case SHIFT_3_KEY_CODE:	//shift+3------ 推纸标记
			if(WorkStart_flag==1)
			  {
			  if(Run_flag==0)
				 {
				 if(WorkMode==AUTO_MODE)//自动--  主画面下
					AllFlagSetExec(PUSH_FLAG); //设定  推纸标记
				 }	
			  }
			  break;	
	case SHIFT_4_KEY_CODE:	//shift+4------ 刀标记
			if(WorkStart_flag==1)
			  {
			  if(Run_flag==0)
				 {
				 if(WorkMode==AUTO_MODE)//自动--  主画面下
					AllFlagSetExec(KNIFE_FLAG); //设定  刀标记
				 }	
			  }
			  break;
	case SHIFT_5_KEY_CODE:	//shift+5------ 添加所有刀标记
			if(WorkStart_flag==1)
			  {
			  if(Run_flag==0)
				 {
				 if(WorkMode==AUTO_MODE)//自动--  主画面下
					{
					if(F5AllKnifeF_SetFlag==0)
						F5AllKnifeF_SetFlag=1;
					else
						F5AllKnifeF_SetFlag=0;
					// Set_AllFlagWind_Exit(FlagTouRow_num-1);	//退出标记框
					AllKnifeFlagExec(F5AllKnifeF_SetFlag);	//添加， --所有刀标记
					}
				 }	
			  }
			  break;	
	case SHIFT_6_KEY_CODE:	//shift+6------ 修改数据偏移量
			if(WorkStart_flag==1)
			  {
			  if(Run_flag==0)
				 {
				 if(WorkMode==AUTO_MODE)//自动--  主画面下
					{
					if(ElectricWheelOn_flag==1)	//手轮  有效时
						{
						AmendSwitch_flag=!AmendSwitch_flag;
						if(AmendSwitch_flag==0)
							{
							AmendStartRun_flag=0;
							AmendSize=0;
							}
						AmendButtonFlag_dis();	//F6修改数据偏移量
						}
					}
				 }	
			  }
			  break;	
	case TEACH_TOUCH_CODE:		//示教 模式 
	case SHIFT_LEFT_KEY_CODE:        //shift+左  == 示教模式
			if(WorkStart_flag==1)
			  {
			   if(Run_flag==0)
				 {
					switch(WorkMode)
						{
						case TEACH_LABEL_MODE: //标签
						case TEACH_DIVIDE_MODE: //等分
						// // case TEACH_PRO_MODE: //程序选择
							CurrentArea_recover2(MIDDLE_PAGE_X, MIDDLE_PAGE_Y,  M_PAGE_WIDE, M_PAGE_HIGH);
						case AUTO_MODE://自动 主模式下************
						case MANUAL_MODE:// 手动 主模式
						case SELF_CUT_MODE://自刀主画面下
							WorkMode=TEACH_MODE;  //示教模式
							TeachModePage_dis();//示教模式page
							PromptNum_dis();//输入范围	
							PromptDis_flag=1; 
						case TEACH_MODE: //示教主模式	
							//------------返回第一刀
							PaperCutEnb_signal=1;
							// // ClrInput_function();//清零 输入框 
							CursorKnife_dis(cursor_row, 0);//红色光标消失
							cursor_row=0;
							CursorKnife_dis(cursor_row, 1);//红色光标显示
							Knife_order=1;//
							Size_1page_dis(Knife_order,0);//一页尺寸显示
							if(Knife_order<=OnePro_head.pro_knifeSUM)
								StepOrder_dis(Knife_order);//步骤更新
								
							ACServoAlarmExec_flag=0;
								break;
						case TEACH_PLUS_MODE:// F5++
							WorkMode=TEACH_MODE;//返回
							PaperCutEnb_signal=1;
							PressCircle_mode=0;
							F5_plus_dis(0);
							//------------返回第一刀
							// // ClrInput_function();//清零 输入框 
							CursorKnife_dis(cursor_row, 0);//红色光标消失
							cursor_row=0;
							CursorKnife_dis(cursor_row, 1);//红色光标显示
							Knife_order=1;//
							Size_1page_dis(Knife_order,0);//一页尺寸显示
							if(Knife_order<=OnePro_head.pro_knifeSUM)
								StepOrder_dis(Knife_order);//步骤更新
							PromptNum_dis();//输入范围	
							PromptDis_flag=1;
							ACServoAlarmExec_flag=0;
							break;
						case TEACH_MINUS_MODE:// F6--
							WorkMode=TEACH_MODE;//返回
							PaperCutEnb_signal=1;
							PressCircle_mode=0;
							F6_minus_dis(0);
							//------------返回第一刀
							// // ClrInput_function();//清零 输入框 
							CursorKnife_dis(cursor_row, 0);//红色光标消失
							cursor_row=0;
							CursorKnife_dis(cursor_row, 1);//红色光标显示
							Knife_order=1;//
							Size_1page_dis(Knife_order,0);//一页尺寸显示
							if(Knife_order<=OnePro_head.pro_knifeSUM)
								StepOrder_dis(Knife_order);//步骤更新
							PromptNum_dis();//输入范围	
							PromptDis_flag=1;	
							ACServoAlarmExec_flag=0;
							break;	
						}
				 }
			  else
				 {
				 
				 }
			  }
			  break;
			  break;		  
	case SHIFT_8_KEY_CODE:	//shift+8------ 密码 模式
			if(WorkStart_flag==1)
			  {
			  if(Run_flag==0)
				 {
					switch(WorkMode)
						{
						case MANUAL_MODE: //手动模式
							if(Sign_flag==1)
								{
								num_cou=0;
								GLCD_SetWindow_Fill( SIZE_WINDOW_X, SIZE_WINDOW_Y, SIZE_WINDOW_X+SIZE_WINDOW_WIDE, SIZE_WINDOW_Y+SIZE_WINDOW_HIGH, 0xfffff, 0xffff);//尺寸输入框
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
			  else
				 {
				 
				 }
			  }
				break;
			  
	case SHIFT_RIGHT_KEY_CODE:        //shift+右  == 自刀模式
	case AUTOCUT_TOUCH_CODE:	//自刀 模式
			if(WorkStart_flag==1)
				 {
				 if(Run_flag==0)
					{
						switch(WorkMode)
							{
							
							case AUTO_MODE://  自动模式下
							case MANUAL_MODE:// 手动 模式
							case TEACH_MODE://示教 模式
								MainMode_temp=WorkMode;
								WorkMode=AUTO_TO_SELF_MODE;   //自动-->自刀过度 模式
								PaperCutEnb_signal=1;
								SelfEnterPage_dis();
								// // ButtonTouch_mode=TOU_MODE_AUTOCUT_IN;
									break;
							case SELF_CUT_MODE:  //		自刀主 模式
								//------------返回第一刀
								// // ClrInput_function();//清零 输入框 
								CursorKnife_dis(cursor_row, 0);//红色光标消失
								cursor_row=0;
								CursorKnife_dis(cursor_row, 1);//红色光标显示
								Knife_order=1;//
								Size_1page_dis(Knife_order,0);//一页尺寸显示
								if(Knife_order<=OnePro_head.pro_knifeSUM)
									StepOrder_dis(Knife_order);//步骤更新 
								PromptNum_dis();//输入范围	
								PromptDis_flag=1; 	
									break;
									/****
							case SELF_RULER_MODE://自刀 基准
							case SELF_TOOLS_MODE://自刀 参数
								PaperCutEnb_signal=1;
								CurrentArea_recover2(MIDDLE_PAGE_X , MIDDLE_PAGE_Y,  M_PAGE_WIDE, M_PAGE_HIGH);
								WorkMode=SELF_CUT_MODE;  //进入   ----------自刀主 模式
								SubModeIcon_dis(WorkMode); //自刀模式
								//------------返回第一刀
								// // ClrInput_function();//清零 输入框 
								CursorKnife_dis(cursor_row, 0);//红色光标消失
								cursor_row=0;
								CursorKnife_dis(cursor_row, 1);//红色光标显示
								Knife_order=1;//
								Size_1page_dis(Knife_order,0);//一页尺寸显示
								if(Knife_order<=OnePro_head.pro_knifeSUM)
									StepOrder_dis(Knife_order);//步骤更新 
								PromptNum_dis();//输入范围	
								PromptDis_flag=1; 	
									break;
									****/
							}
					}
				  else
					{
					
					}
				 }
					break;
	case HELP_KEY_CODE:         //帮助----------
		if(WorkStart_flag==0)
			{
			switch(MotorType)
				{
					case MOTOR_FREQ_5_SPD_RST:
					case MOTOR_FREQ_3_SPD:
					case MOTOR_FREQ_3_SPD_RST:
					case MOTOR_AC_SERVO:
					case MOTOR_AC_SERVO_REV:
					case MOTOR_AC_A6_SERVO:
						if((StartCheck_mode<2)||(StartCheck_mode==4))
							CheckModeOK_flag=1;	
						else
							CheckModeOK_flag=0;
						break;
					// // case MOTOR_DC_SERVO:
					// // case MOTOR_DC670_SERVO:
						// // if(StartCheck_mode<2)
							// // CheckModeOK_flag=1;	
						// // else
							// // CheckModeOK_flag=0;
						// // break;
					// case MOTOR_AC_SERVO:
					// case MOTOR_AC_SERVO_REV:
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
				switch(Board_TestMod)
					{
					case TEST_NO: //非帮助 模式-------
						Board_TestMod=TEST_HELP; //帮助 模式  进入
						StartHelpMode_dis();
						break;
					case TEST_TOUCH:	
					case TEST_ICON:	
					case TEST_BOARD:	
					case TEST_SYS_WORD:	
					case TEST_PAGE_LINE:	
						num_cou=0; //
					case TEST_HELP:  //帮助 模式下
						Bmp_Decode((Int32U)START_PIC_sdram, 0, 0, (pInt16U)LCD_VRAM_BASE_ADDR); //显示开机画面
						Board_TestMod=TEST_NO;
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
						KeyLinkDis_flag=0;
						PassCheckDis_flag=0;
						break;
					}
				}
			}
			break;
	case PROC_KEY_CODE:   //程序 选择		(查找模式)
		if(WorkStart_flag==1)
			{
			if(Run_flag==0)  //
				{
					switch(WorkMode)
						{
						case TEACH_MODE://示教 模式
								
						case AUTO_MODE://自动主画面下	
						case MANUAL_MODE:// 手动 模式
								WorkMode=READ_PRO_MODE;	// 进入 -----------选择程序模式(查找模式)
								SearchProgPage_dis(); //程序 选择 画面显示
								PromptDis_flag=0;
								//prog_order=1;
								TableDis_startcol=PROC_NUM_X;
								cursor_pro=0;
								CursorPro_dis(cursor_pro,1);//pro光标
								Prog_1page_dis(prog_order, cursor_pro);//===程序---数据显示
								OneProgHeadInfo_dis(cursor_pro ,  prog_order, 1);	//一条程序 显示
								ClearCalculatorInput(); //清零计算器 输入//ClrInput_function();//清零 输入框
								ACServoAlarmExec_flag=0;
								break;	
						}
				}
			}	
			break;
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
						// // case MOTOR_DC_SERVO:
						// // case MOTOR_DC670_SERVO:
							// // DCServoStop();  //停止运行
							// // ServoPressStop_flag=0;
							// // DcServoGoTarget_flag=0;
							// // BellStart_flag=0;
								// // break;
						case MOTOR_AC_SERVO:
						case MOTOR_AC_SERVO_REV:
						case MOTOR_AC_A6_SERVO:
							ACServoStop();
								break;
						}
					Run_flag=0;	
					InTargetPosit_flag=0;	//目标位置
					AutoPushRun_flag=0; //自动推纸 运行
					AirOffOK_flag=0;
					PressUp_flag=0;
					PressDown_flag=0;
					TargetSize=0;
					// TargetSize_temp=0;
					BeforeKnife_offset_in=0;
					if(ButtonTouch_mode==0)
						// ClrInput_function();//清零 输入框
					//PaperCutEnb_signal=1;	
					AutoRoute_flag=0;
					if(ACServoDrvErr_flag==0)
						{
						RLOUT1_OFF; RLOUT1_1_OFF;   // 允许裁切	
						}
						
					}
				}
			else
				{
				if(MotorType<MOTOR_AC_SERVO)	//(MotorType<MOTOR_DC_SERVO)
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
						// TargetSize_temp=0;
						BeforeKnife_offset_in=0;
						if(ButtonTouch_mode==0)
							// ClrInput_function();//清零 输入框
						//PaperCutEnb_signal=1;	
						AutoRoute_flag=0;
						if(ACServoDrvErr_flag==0)
							{
							RLOUT1_OFF; RLOUT1_1_OFF;   // 允许裁切
							}
						}
					}
					//----
					if(WorkMode==SELF_CUT_MODE) //自刀主画面下--------返回自动
						{
						if(CutEnBegin_flag==1)
							{
							CutEnBegin_flag=0;
							BellOUT_OFF;
							RLOUT4_ON;
							AutoCutStart_flag=0;
							RunStop_flag=0;
							//Run_flag=0;
							}
						
						LastAutoKnife_order=Knife_order;
						WorkMode=AUTO_MODE;//自动主
						AutoModePage_dis(); //返回 ----------- 自动
						//------------返回第一刀
						// // ClrInput_function();//清零 输入框 
						CursorKnife_dis(cursor_row, 0);//红色光标消失
						cursor_row=0;
						CursorKnife_dis(cursor_row, 1);//红色光标显示
						Knife_order=1;//
						Size_1page_dis(Knife_order,0);//一页尺寸显示
						if(Knife_order<=OnePro_head.pro_knifeSUM)
							StepOrder_dis(Knife_order);//步骤更新 
						}
				}
			}	
			break;
     /**
	case WHEEL_SWITCH_TOUCH_CODE: //0xffff000c 电子手轮  开关
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
							ElectricalWheel_dis();  //电子手轮  开关状态
								break;
						}
					}
				}
			}
			break; **/
    case   	MUL_KEY_CODE: //MUL_TOUCH_CODE   0xffff0007 乘法  *
		if(WorkStart_flag==1)
			{
			if(Run_flag==0)
				{
				CalculatorValue_exec('*');
				}
			}	
			break;
   	case	DIV_KEY_CODE:  //   DIV_TOUCH_CODE 0xffff0008 除法/
		if(WorkStart_flag==1)
			{
			if(Run_flag==0)
				{
				CalculatorValue_exec('/');
				}
			}
			break;
	case	EQUAL_KEY_CODE:  //     EQU_TOUCH_CODE 0xffff0009      结果 =  
		if(WorkStart_flag==1)
			{
			if(Run_flag==0)
				{
				if(CalcResultDis_flag==0)
					{
					CalcGetValue_exec();
					}
				}
			}
			break;		
	case INPUT_TOUCH_CODE:	//0xffff0001	 输入框 =====触摸 
		if(WorkStart_flag==1)
			{
			if(Run_flag==0)
				{
				ClrInput_function();//清零 输入框
				if(ButtonTouch_mode==0)  //进入触摸 计算器输入
					{
					switch(WorkMode)
						{
						case AUTO_TO_SELF_MODE:  //自动-->自刀过度 模式
						// // case PROG_PRO_MESS_MODE:	//程序名称		 
						// // case TEACH_PRO_MESS_MODE:	
						case PROG_DEL_ALL_SIZE_MODE://	删除所有尺寸
						case TEACH_DEL_ALL_SIZE_MODE://	删除所有尺寸
						// // case PROG_DEL_ALL_PRO_MODE://删除所有pro
						// // case TEACH_DEL_ALL_PRO_MODE://删除所有pro
						case MANUAL_IO_TEST_MODE:// IO 测试模式--------
							break;
						default:	//弹出 计算器
							// CalcNoNumInput_flag=1;
							// Dot_flag=0;
							// CalcSign_order=0;//首个运算符 位置
							// CalcData_temp=0;
							// CalcResultDis_flag=0;
							// num_cou=0;
							// if(Sign_flag==1)//清除 加,减号
								// {
								// GLCD_SetWindow_Fill( SIZE_WINDOW_X, SIZE_WINDOW_Y, SIZE_WINDOW_X+SIZE_WINDOW_WIDE, SIZE_WINDOW_Y+SIZE_WINDOW_HIGH, 0xfffff, 0xffff);//尺寸输入框
								// Sign_flag=0;
								// }
							
							// CalcInput_cou=0;
							// Calculator_Window();  //计算器 按钮	
							// ClrCalcNums_text(CalcInput_Text,CAL_INPUT); //清计算器 输入框
							// ClrCalcNums_text(CalcResult_Text,CAL_RESULT); //清计算器 结果框 
							// CalcInputNums_dis(CalcInput_Text);  //输入框 显示
							// CalcResultNums_dis(CalcResult_Text);//结果框 显示
							// ButtonTouch_mode=TOU_MODE_CALC;
							break;
						}
					}
				else if(ButtonTouch_mode==TOU_MODE_CALC)         //退出
					{
					//CalcInput_cou=0;
					CalcuInClear_exec();     //清除 计算器
					switch(WorkMode)
						{
						// // case AUTO_TOOLS_MODE:
						case MANUAL_TOOLS_MODE:
						// // case SELF_TOOLS_MODE:
							back_color=TEXT_TAB_BACK_COLOR;
							x=PARA_START_X1+PARA_COL_WIDE,y=PARA_START_Y,gap=PARA_ROW_GAP;
							if(PramSel_Page<1)	//page 1
								{
								ParameterPage1_dis(7, 0);
								ParameterPage1_dis(8, 0);
								if(MotorType<MOTOR_AC_SERVO)	
									{
									ParameterPage1_dis(9, 0);
									}
								else 
									{
									ParameterPage1_dis(9, 0);
									ParameterPage1_dis(10, 0);
									}
								ParameterPage1_dis(Para_sel, 1);
								GLCD_SetWindow_Fill( x, y, x+tx_wide, y+(gap*4-10), TEXT_TAB_BACK_COLOR, TEXT_TAB_BACK_COLOR);//clear text win
								switch(Language)
									{
									case CHN_HAN:
										Printf24("压纸停机:  ",x,y,BLACK_COLOR,1,back_color);y+=gap;
										Printf24("关气距离:  ",x,y,BLACK_COLOR,1,back_color);y+=gap;
										switch(MotorType)
											{
											case MOTOR_FREQ_5_SPD_RST:
											case MOTOR_FREQ_3_SPD:
											case MOTOR_FREQ_3_SPD_RST:
												Printf24("光电选择:  ",x,y,BLACK_COLOR,1,back_color);
													break;
											// // case MOTOR_DC_SERVO:
											// // case MOTOR_DC670_SERVO:
												// // Printf24("最大速度:  ",x,y,BLACK_COLOR,1,back_color);y+=gap;
												// // Printf24("点动速度:  ",x,y,BLACK_COLOR,1,back_color);
													// // break;
											case MOTOR_AC_SERVO:
											case MOTOR_AC_SERVO_REV:
											case MOTOR_AC_A6_SERVO:
												Printf24("运行速度:  ",x,y,BLACK_COLOR,1,back_color);y+=gap;
												Printf24("光电选择:  ",x,y,BLACK_COLOR,1,back_color);
													break;
											}
											break;
									case ENGLISH:
										Printf24("Press-Stop:",x,y,BLACK_COLOR,1,back_color);y+=gap;
										Printf24("AirOff-dist:",x,y,BLACK_COLOR,1,back_color);y+=gap;
										switch(MotorType)
											{
											case MOTOR_FREQ_5_SPD_RST:
											case MOTOR_FREQ_3_SPD:
											case MOTOR_FREQ_3_SPD_RST:
												Printf24("IR-Set:  ",x,y,BLACK_COLOR,1,back_color);
													break;
											// // case MOTOR_DC_SERVO:
											// // case MOTOR_DC670_SERVO:
												// // Printf24("Max-speed:",x,y,BLACK_COLOR,1,back_color);y+=gap;
												// // Printf24("Jog-speed:",x,y,BLACK_COLOR,1,back_color);
													// // break;
											case MOTOR_AC_SERVO:
											case MOTOR_AC_SERVO_REV:
											case MOTOR_AC_A6_SERVO:
												Printf24("Run-speed:",x,y,BLACK_COLOR,1,back_color);y+=gap;
												Printf24("IR-Set:  ",x,y,BLACK_COLOR,1,back_color);
													break;
											}
											break;
									case INDONSIA:	//印尼
										Printf24("Plat-bawah:",x,y,BLACK_COLOR,1,back_color);y+=gap;
										Printf24("Off gas da:",x,y,BLACK_COLOR,1,back_color);y+=gap;
										switch(MotorType)
											{
											case MOTOR_FREQ_5_SPD_RST:
											case MOTOR_FREQ_3_SPD:
											case MOTOR_FREQ_3_SPD_RST:
												Printf24("Set-IR: ",x,y,BLACK_COLOR,1,back_color);
													break;
											// // case MOTOR_DC_SERVO:
											// // case MOTOR_DC670_SERVO:
												// // Printf24("Tercepat:",x,y,BLACK_COLOR,1,back_color);y+=gap;
												// // Printf24("Jog-kecep:",x,y,BLACK_COLOR,1,back_color);
													// // break;
											case MOTOR_AC_SERVO:
											case MOTOR_AC_SERVO_REV:
											case MOTOR_AC_A6_SERVO:
												Printf24("Kecepa-lari:",x,y,BLACK_COLOR,1,back_color);y+=gap;
												Printf24("Set-IR: ",x,y,BLACK_COLOR,1,back_color);
													break;
											}
											break;
									case PORTUGAL:	//葡萄牙
										Printf24("encerra:",x,y,BLACK_COLOR,1,back_color);y+=gap;
										Printf24("Off Air:",x,y,BLACK_COLOR,1,back_color);y+=gap;
										switch(MotorType)
											{
											case MOTOR_FREQ_5_SPD_RST:
											case MOTOR_FREQ_3_SPD:
											case MOTOR_FREQ_3_SPD_RST:
												Printf24("estado IR:",x,y,BLACK_COLOR,1,back_color);
													break;
											// // case MOTOR_DC_SERVO:
											// // case MOTOR_DC670_SERVO:
												// // Printf24("Veloci-má  ",x,y,BLACK_COLOR,1,back_color);
												// // Printf24("          x:",x,y,BLACK_COLOR,0,back_color);y+=gap;
												// // Printf24("Veloci-Jog:",x,y,BLACK_COLOR,1,back_color);
													// // break;
											case MOTOR_AC_SERVO:
											case MOTOR_AC_SERVO_REV:
											case MOTOR_AC_A6_SERVO:
												Printf16("Veloci-corrida:",x,y,BLACK_COLOR,1,back_color);y+=gap;
												Printf24("estado IR:",x,y,BLACK_COLOR,1,back_color);
													break;
											}
											break;
									case SPANISH: //西班牙
										Printf24("cierre:",x,y,BLACK_COLOR,1,back_color);y+=gap;
										Printf24("Off Air:",x,y,BLACK_COLOR,1,back_color);y+=gap;
										switch(MotorType)
											{
											case MOTOR_FREQ_5_SPD_RST:
											case MOTOR_FREQ_3_SPD:
											case MOTOR_FREQ_3_SPD_RST:
												Printf24("estado IR:",x,y,BLACK_COLOR,1,back_color);
													break;
											// // case MOTOR_DC_SERVO:
											// // case MOTOR_DC670_SERVO:
												// // Printf24("Veloci-má  ",x,y,BLACK_COLOR,1,back_color);
												// // Printf24("          x:",x,y,BLACK_COLOR,0,back_color);y+=gap;
												// // Printf24("Veloci-Jog:",x,y,BLACK_COLOR,1,back_color);
													// // break;
											case MOTOR_AC_SERVO:
											case MOTOR_AC_SERVO_REV:
											case MOTOR_AC_A6_SERVO:
												Printf16("Veloci-corrida:",x,y,BLACK_COLOR,1,back_color);y+=gap;
												Printf24("estado IR:",x,y,BLACK_COLOR,1,back_color);
													break;
											}
											break;
									}		
								}
							break;
						
						case  PROG_MODE://编程画面下
						case AUTO_MODE://自动主画面下
						case AUTO_PLUS_MODE://自动F5++
						case AUTO_MINUS_MODE://自动F6--
						case TEACH_MODE://示教 模式
						//case AUTO_TO_SELF_MODE:   //自动-->自刀过度 模式
						case SELF_CUT_MODE:  //自刀主 模式
						case TEACH_PLUS_MODE: //自刀 F5++
						case TEACH_MINUS_MODE://自刀 F6--
							 if(Knife_order>OnePro_head.pro_knifeSUM)
								 K_temp=Knife_order-1;
							 else
								 K_temp=Knife_order;
							//StepOrder_dis(Knife_order);//步骤更新
							ProgressBar_dis(OnePro_head.pro_knifeSUM,K_temp);  //进度条 显示
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
							// CursorKnife_dis(cursor_row, 0);//红色光标消失
							// cursor_row=0;
							// CursorKnife_dis(cursor_row, 1);//红色光标显示
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
	/*****
	case ONE_KEY_CODE:		// F 功能按键******************
		if(WorkStart_flag==0)  //未进入工作状态
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
						if(StartCheck_mode<2)
							CheckModeOK_flag=1;
						else
							CheckModeOK_flag=0;
						break;
				case MOTOR_AC_SERVO:
						if(StartCheck_mode<3)
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
							MoveStop();
							ForceStop_flag=0;
							BackStop_flag=0;
							Backward_flag=0;
							Forward_flag=0;	
							SelfLockEn_flag=0; //取消自锁
							ToTargetStop_flag=0;
							RunStop_flag=0;
								break;
						case MOTOR_DC_SERVO:
						case MOTOR_DC670_SERVO:
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
					if(ButtonTouch_mode==0)
						ClrInput_function();//清零 输入框
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
						MoveStop();
						ForceStop_flag=0;
						BackStop_flag=0;
						Backward_flag=0;
						Forward_flag=0;	
						SelfLockEn_flag=0; //取消自锁
						ToTargetStop_flag=0;
						RunStop_flag=0;
						
						InTargetPosit_flag=0;	//目标位置
						AutoPushRun_flag=0; //自动推纸 运行
						TargetSize=0;
						TargetSize_temp=0;
						BeforeKnife_offset_in=0;
						if(ButtonTouch_mode==0)
							ClrInput_function();//清零 输入框
						//PaperCutEnb_signal=1;	
						AutoRoute_flag=0;
						}
					}
				}
			}
  	         break;
			 ****/
	case TWO_KEY_CODE:		//手动****************
        if(WorkStart_flag==1)  
			{
			if(Run_flag==0)
			    {
				switch(WorkMode)
					{
					// // case PROG_MODE://编程 主模式下********
					case TEACH_MODE://示教 模式
					case AUTO_MODE://自动 主模式下*******
					case SELF_CUT_MODE://自刀主画面下
					case READ_PRO_MODE:// 程序查找 主画面下
						WorkMode=MANUAL_MODE;  //进入 手动模式
						ManualModePage_dis();
						KnifeSensorMode=0;
						PressSensorMode=0;
						// // ClrInput_function();//清零 输入框
						PromptNum_dis();//输入范围
						PromptDis_flag=1; 
						PaperCutEnb_signal=1;
						ACServoAlarmExec_flag=0;
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
						SubModeIcon_dis(WorkMode); //手动mode name
						KnifeSensorMode=0;
						PressSensorMode=0;
					case MANUAL_MODE:   //手动
						PromptNum_dis();//输入范围
						PromptDis_flag=1;
						// // ClrInput_function();//清零 输入框
						ACServoAlarmExec_flag=0;
						break;		
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
						// // case MOTOR_DC_SERVO:
						// // case MOTOR_DC670_SERVO:
							// // DCServoStop();  //停止运行
							// // ServoPressStop_flag=0;
							// // DcServoGoTarget_flag=0;
							// // BellStart_flag=0;
							// // //************
							// // Run_flag=0;	
							// // InTargetPosit_flag=0;	//目标位置
							// // AutoPushRun_flag=0; //自动推纸 运行
							// // TargetSize=0;
							// // TargetSize_temp=0;
							// // BeforeKnife_offset_in=0;
							// // AutoRoute_flag=0;
								// // break;
						case MOTOR_AC_SERVO:
						case MOTOR_AC_SERVO_REV:
						case MOTOR_AC_A6_SERVO:
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
					
					}
				}
			}
  	     break;   
	case THREE_KEY_CODE:		//自动******************
		if(WorkStart_flag==1)
			{
			if(Run_flag==0)
			    {
					switch(WorkMode)
						{
						// // case PROG_MODE://编程 主模式下
						case TEACH_MODE://示教 模式
						case MANUAL_MODE:// 手动 主模式
						case SELF_CUT_MODE://自刀主画面下	
						case READ_PRO_MODE:// 程序查找 主画面下
							WorkMode=AUTO_MODE;//进入 自动模式
							PaperCutEnb_signal=1;
							PressCircle_mode=0;
							AutoModePage_dis();
							PromptNum_dis();//输入范围	
							PromptDis_flag=1; 
						case AUTO_MODE://自动 主模式下
							//------------返回第一刀
							// // ClrInput_function();//清零 输入框 
							CursorKnife_dis(cursor_row, 0);//红色光标消失
							cursor_row=0;
							CursorKnife_dis(cursor_row, 1);//红色光标显示
							Knife_order=1;//
							Size_1page_dis(Knife_order,0);//一页尺寸显示
							if(Knife_order<=OnePro_head.pro_knifeSUM)
								StepOrder_dis(Knife_order);//步骤更新
							PromptNum_dis();//输入范围	
							PromptDis_flag=1;  
							ACServoAlarmExec_flag=0;
							break;
						case AUTO_LABEL_MODE: //标签
						case AUTO_DIVIDE_MODE: //等分
							WorkMode=AUTO_MODE;//返回    自动 主模式
							CurrentArea_recover2(MIDDLE_PAGE_X, MIDDLE_PAGE_Y,  M_PAGE_WIDE, M_PAGE_HIGH);
							SubModeIcon_dis(WorkMode);   //自动模式name
							PorgSet_sel=0;
							//------------返回第一刀
							// // ClrInput_function();//清零 输入框 
							CursorKnife_dis(cursor_row, 0);//红色光标消失
							cursor_row=0;
							CursorKnife_dis(cursor_row, 1);//红色光标显示
							Knife_order=1;//
							Size_1page_dis(Knife_order,0);//一页尺寸显示
							if(Knife_order<=OnePro_head.pro_knifeSUM)
								StepOrder_dis(Knife_order);//步骤更新
							PromptNum_dis();//输入范围
							PromptDis_flag=1;
							PaperCutEnb_signal=1;
							PressCircle_mode=0;
							ACServoAlarmExec_flag=0;	
							break;
							//自动模式------------------------------------------
						// // case AUTO_RULER_MODE:	//基准模式
						// // case AUTO_TOOLS_MODE:	 //参数模式	
							// // Para_sel=0;
							// // WorkMode=AUTO_MODE;//返回    自动 主模式
							// // PaperCutEnb_signal=1;
							// // PressCircle_mode=0;
							// // CurrentArea_recover2(MIDDLE_PAGE_X , MIDDLE_PAGE_Y,  M_PAGE_WIDE, M_PAGE_HIGH);
							// // SubModeIcon_dis(WorkMode); //自动
							// // //------------返回第一刀
							// // ClrInput_function();//清零 输入框 
							// // CursorKnife_dis(cursor_row, 0);//红色光标消失
							// // cursor_row=0;
							// // CursorKnife_dis(cursor_row, 1);//红色光标显示
							// // Knife_order=1;//
							// // Size_1page_dis(Knife_order,0);//一页尺寸显示
							// // if(Knife_order<=OnePro_head.pro_knifeSUM)
								// // StepOrder_dis(Knife_order);//步骤更新
							// // PromptNum_dis();//输入范围	
							// // PromptDis_flag=1; 
							// // ACServoAlarmExec_flag=0;
							// // break;
						case AUTO_PLUS_MODE:// F5++
							WorkMode=AUTO_MODE;//返回
							PaperCutEnb_signal=1;
							PressCircle_mode=0;
							F5_plus_dis(0);
							//------------返回第一刀
							// // ClrInput_function();//清零 输入框 
							CursorKnife_dis(cursor_row, 0);//红色光标消失
							cursor_row=0;
							CursorKnife_dis(cursor_row, 1);//红色光标显示
							Knife_order=1;//
							Size_1page_dis(Knife_order,0);//一页尺寸显示
							if(Knife_order<=OnePro_head.pro_knifeSUM)
								StepOrder_dis(Knife_order);//步骤更新
							PromptNum_dis();//输入范围	
							PromptDis_flag=1;
							ACServoAlarmExec_flag=0;
							break;
						case AUTO_MINUS_MODE:// F6--
							WorkMode=AUTO_MODE;//返回
							PaperCutEnb_signal=1;
							PressCircle_mode=0;
							F6_minus_dis(0);
							//------------返回第一刀
							// // ClrInput_function();//清零 输入框 
							CursorKnife_dis(cursor_row, 0);//红色光标消失
							cursor_row=0;
							CursorKnife_dis(cursor_row, 1);//红色光标显示
							Knife_order=1;//
							Size_1page_dis(Knife_order,0);//一页尺寸显示
							if(Knife_order<=OnePro_head.pro_knifeSUM)
								StepOrder_dis(Knife_order);//步骤更新
							PromptNum_dis();//输入范围	
							PromptDis_flag=1;	
							ACServoAlarmExec_flag=0;
							break;	
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
						// // case MOTOR_DC_SERVO:
						// // case MOTOR_DC670_SERVO:
							// // DCServoStop();  //停止运行
							// // ServoPressStop_flag=0;
							// // DcServoGoTarget_flag=0;
							// // BellStart_flag=0;
							// // //************
							// // Run_flag=0;	
							// // InTargetPosit_flag=0;	//目标位置
							// // AutoPushRun_flag=0; //自动推纸 运行
							// // TargetSize=0;
							// // TargetSize_temp=0;
							// // BeforeKnife_offset_in=0;
							// // AutoRoute_flag=0;
								// // break;
						case MOTOR_AC_SERVO:
						case MOTOR_AC_SERVO_REV:
						case MOTOR_AC_A6_SERVO:
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
					}				
				}
			}
  	     break;
		 /****
	case FOUR_KEY_CODE:	//编程按键******************进入  编程 主模式
		if(WorkStart_flag==1)
		   {
		   if(Run_flag==0)
			    {
				if(ButtonTouch_mode==0)
					{
					switch(WorkMode)
						{
						case PROG_LABEL_MODE: //标签
						case PROG_DIVIDE_MODE: //等分
							WorkMode=PROG_MODE;
							CurrentArea_recover2(MIDDLE_PAGE_X, MIDDLE_PAGE_Y,  M_PAGE_WIDE, M_PAGE_HIGH);
							SubModeIcon_dis(WorkMode);   //编程模式name
							PorgSet_sel=0;
							//------------返回第一刀
							ClrInput_function();//清零 输入框 
							CursorKnife_dis(cursor_row, 0);//红色光标消失
							cursor_row=0;
							CursorKnife_dis(cursor_row, 1);//红色光标显示
							Knife_order=1;//
							Size_1page_dis(Knife_order,0);//一页尺寸显示
							if(Knife_order<=OnePro_head.pro_knifeSUM)
								StepOrder_dis(Knife_order);//步骤更新
							PromptNum_dis();//输入范围
							PromptDis_flag=1;
							PaperCutEnb_signal=1;
							ACServoAlarmExec_flag=0;
							if(Sign_flag==1)//清除 加,减号
								{
								GLCD_SetWindow_Fill( SIZE_WINDOW_X, SIZE_WINDOW_Y, SIZE_WINDOW_X+SIZE_WINDOW_WIDE, SIZE_WINDOW_Y+SIZE_WINDOW_HIGH, 0xfffff, 0xffff);//尺寸输入框
								Sign_flag=0;
								}
								break;
						case AUTO_MODE://自动 主模式下************
						case SELF_CUT_MODE://自刀主画面下
						case TEACH_MODE://示教 模式
						case MANUAL_MODE:// 手动 主模式
							if(Sign_flag==1)
								{
								num_cou=0;
								GLCD_SetWindow_Fill( SIZE_WINDOW_X, SIZE_WINDOW_Y, SIZE_WINDOW_X+SIZE_WINDOW_WIDE, SIZE_WINDOW_Y+SIZE_WINDOW_HIGH, 0xfffff, 0xffff);//尺寸输入框
								Sign_flag=0;
								}
							WorkMode=PROG_MODE;
							ProgModePage_dis();// 回到 编程模式
							 
						case PROG_MODE: //编程 主模式
								//------------返回第一刀
							ClrInput_function();//清零 输入框 
							CursorKnife_dis(cursor_row, 0);//红色光标消失
							cursor_row=0;
							CursorKnife_dis(cursor_row, 1);//红色光标显示
							Knife_order=1;//
							Size_1page_dis(Knife_order,0);//一页尺寸显示
							if(Knife_order<=OnePro_head.pro_knifeSUM)
								StepOrder_dis(Knife_order);//步骤更新
							PromptNum_dis();//输入范围
							PromptDis_flag=1;
							PaperCutEnb_signal=1;
							ACServoAlarmExec_flag=0;
							if(Sign_flag==1)//清除 加,减号
								{
								GLCD_SetWindow_Fill( SIZE_WINDOW_X, SIZE_WINDOW_Y, SIZE_WINDOW_X+SIZE_WINDOW_WIDE, SIZE_WINDOW_Y+SIZE_WINDOW_HIGH, 0xfffff, 0xffff);//尺寸输入框
								Sign_flag=0;
								}
								break;
						}		
					}
				else if(ButtonTouch_mode==TOU_MODE_CALC)  //计算器 弹出模式
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
						case MOTOR_AC_SERVO_REV:
						case MOTOR_AC_A6_SERVO:
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
					if(ButtonTouch_mode==0)
						ClrInput_function();//清零 输入框 		
					}
				}
		   }
		  break;
		  ****/
    case AUTO_KEY_CODE:       // F1**********************
		if(WorkStart_flag==1)
			{
			if(Run_flag==0)
			    {
				switch(WorkMode)
					{
					case AUTO_MODE://自动 主模式下	
						WorkMode=AUTO_LABEL_MODE; //--------打开标签 页
						F1_LabelPage_dis();  
						Total_size=0;//总长
						Label_size=0;//标签长
						Waste_size=0;//废边
						PorgSet_sel=0;
						PromptNum_dis();//输入范围
						PromptDis_flag=1;
						ACServoAlarmExec_flag=0;
						break;
					case TEACH_MODE://示教 模式
						WorkMode=TEACH_LABEL_MODE; //--------打开标签 页
						F1_LabelPage_dis();  
						Total_size=0;//总长
						Label_size=0;//标签长
						Waste_size=0;//废边
						PorgSet_sel=0;
						PromptNum_dis();//输入范围
						PromptDis_flag=1;
						ACServoAlarmExec_flag=0;
						break;
						
					case AUTO_LABEL_MODE://已 打开   标签********************
						WorkMode=AUTO_MODE;//------------退出返回到自动主 画面 
						CurrentArea_recover2(MIDDLE_PAGE_X , MIDDLE_PAGE_Y,  M_PAGE_WIDE, M_PAGE_HIGH); 
						SubModeIcon_dis(WorkMode);   //自动模式name
						PorgSet_sel=0;
						//if(Knife_order<MAX_Knife-2) //至少最后3刀
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
						SubModeIcon_dis(WorkMode);   //示教模式name
						PorgSet_sel=0;
						//if(Knife_order<MAX_Knife-2) //至少最后3刀
						//  {
						if((Total_size*Label_size*Waste_size)!=0)//设定有效
							Label_function();          
						// }
						PromptNum_dis();//输入范围
						PromptDis_flag=1;
						ACServoAlarmExec_flag=0;
						break;
					case AUTO_DIVIDE_MODE: //已 进入 等分页*******************
						WorkMode=AUTO_MODE;//--------------退出返回到自动主 画面 
						CurrentArea_recover2(MIDDLE_PAGE_X , MIDDLE_PAGE_Y,  M_PAGE_WIDE, M_PAGE_HIGH);
						SubModeIcon_dis(WorkMode);   //自动模式name
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
						SubModeIcon_dis(WorkMode);   //示教模式name
						PorgSet_sel=0;
						if((Total_size*Divide_num)!=0)//设定等分有效
						  {
						  Divide_function();//
						  }
						PromptNum_dis();//输入范围
						PromptDis_flag=1;  
						ACServoAlarmExec_flag=0;
						break;		
					
					case READ_PRO_MODE:		//	已在 程序选择画面**************	
						WorkMode=READ_PRO_MESS_MODE;//--------------显示程序详细 信息
						ProMessageModify_mode(prog_order);	//程序名修改 模式
						break;
					case TEACH_PRO_MODE:	//已在 程序选择画面**************	
						// WorkMode=TEACH_PRO_MESS_MODE;//--------------显示程序详细 信息
						// ProMessageModify_mode(prog_order);	//程序名修改 模式
						break;	
					case READ_PRO_MESS_MODE:
						InputMode=PINYIN_INPUT;
						ProMessIcon_dis();	//输入法模式 icon显示
						InputStus_dis(InputMode);	//输入法  选择(拼音)
						break;
					// // case TEACH_PRO_MESS_MODE:
						// // InputMode=PINYIN_INPUT;
						// // ProMessIcon_dis();	//输入法模式 icon显示
						// // InputStus_dis(InputMode);	//输入法  选择(拼音)
						// // break;	
					// // case AUTO_MODE://自动 主模式下	
						// // WorkMode=AUTO_RULER_MODE; //基准
						// // F2_RulerPage_dis(); //基准 画面
						// // PromptNum_dis();//输入范围
						// // PromptDis_flag=1;
						// // ACServoAlarmExec_flag=0;
						// // break;
					// // case AUTO_TOOLS_MODE:// 已在  自动 -------参数模式
						// // WorkMode=AUTO_MODE;//返回    ---------自动 主模式
						// // Para_sel=0;
						// // PaperCutEnb_signal=1;
						// // CurrentArea_recover2(MIDDLE_PAGE_X , MIDDLE_PAGE_Y,  M_PAGE_WIDE, M_PAGE_HIGH);
						// // SubModeIcon_dis(WorkMode); //自动mode name
						// // PromptNum_dis();//输入范围
						// // PromptDis_flag=1;
						// // ACServoAlarmExec_flag=0;
						// // break;
						/***
					case SELF_CUT_MODE://自刀主画面下	
						WorkMode=SELF_RULER_MODE; //基准
						F2_RulerPage_dis(); //基准 画面
						PromptNum_dis();//输入范围
						PromptDis_flag=1;
						ACServoAlarmExec_flag=0;
						ReadCurrentSize_A6Coder();//读取当前 A6编码器值
						break;
					case SELF_TOOLS_MODE:// 已在 自刀  -------参数模式
						WorkMode=SELF_CUT_MODE;//返回    ---------自刀 主模式
						Para_sel=0;
						CurrentArea_recover2(MIDDLE_PAGE_X , MIDDLE_PAGE_Y,  M_PAGE_WIDE, M_PAGE_HIGH);
						SubModeIcon_dis(WorkMode); //自刀模式
						PromptNum_dis();//输入范围
						PromptDis_flag=1;
						ACServoAlarmExec_flag=0;
						break;
						****/
					case MANUAL_MODE:  // 手动模式
						WorkMode=MANUAL_TOOLS_MODE;//进入  手动----参数模式*****************
						F1_ToolsPage_dis(); //参数画面
						Para_sel=0;
						PromptDis_flag=0;
						ACServoAlarmExec_flag=0;
						ReadCurrentSize_A6Coder();//读取当前 A6编码器值
						
						break;
					case MANUAL_PULSE_MODE://手动 脉冲设定模式
						Pulse_degree=Para_sel;
						Save_degree();
						WorkMode=MANUAL_MODE;//返回    ---------手动 主模式
						Para_sel=0;
						CurrentArea_recover2(MIDDLE_PAGE_X , MIDDLE_PAGE_Y,  M_PAGE_WIDE, M_PAGE_HIGH);
						SubModeIcon_dis(WorkMode);   //手动模式name
						PromptNum_dis();//输入范围
						PromptDis_flag=1;
						ACServoAlarmExec_flag=0;
						break;
					case MANUAL_TOOLS_MODE:// 手动 参数模式
					case MANUAL_CLOCK_MODE://手动 时钟模式
					case MANUAL_PASS_MODE://手动 密码模式
					case MANUAL_SERVO_C_MODE:   //手动直流伺服 C 参数 
						WorkMode=MANUAL_MODE;//返回    ---------手动 主模式
						Para_sel=0;
						CurrentArea_recover2(MIDDLE_PAGE_X , MIDDLE_PAGE_Y,  M_PAGE_WIDE, M_PAGE_HIGH);
						SubModeIcon_dis(WorkMode); //手动mode name
						PromptNum_dis();//输入范围
						PromptDis_flag=1;
						ACServoAlarmExec_flag=0;
						break;	
					//-------基准 完成 返回
					// // case AUTO_RULER_MODE://自动 基准
					// // case SELF_RULER_MODE://自刀 基准
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
									// // case MOTOR_DC_SERVO:
									// // case MOTOR_DC670_SERVO:
										// // DcServoGoTarget_flag=0;
										
										// // OriginalSize=OriginalSize+InputSize-CurrentSize;
										// // CurrentSize=InputSize;
										// // ServoSetCommd(SERVO_COMMD_P,STAT_30H,CurrentSize);
											// // break;
									case MOTOR_AC_SERVO:	
									case MOTOR_AC_SERVO_REV:	
										OriginalSize=OriginalSize+InputSize-CurrentSize;
										CurrentSize=InputSize;
											break;
									case MOTOR_AC_A6_SERVO:
										StartInitSize=StartInitSize+InputSize-CurrentSize;
										OriginalSize=InputSize;
										SaveA6OriginalBenchMark();//A6基准 保存
											break;	
									}
								SaveOriginalSize();  //保存原点尺寸
								
								
								//-----------------自动返回 主模式	
								CurrentArea_recover2(MIDDLE_PAGE_X , MIDDLE_PAGE_Y,  M_PAGE_WIDE, M_PAGE_HIGH);
								// // if(WorkMode==AUTO_RULER_MODE)   //自动下
									// // {
									// // WorkMode=AUTO_MODE;//返回    自动 主模式
									// // PaperCutEnb_signal=1;
									// // }
								// // else
								if(WorkMode==MANUAL_RULER_MODE)  //手动下
									{
									WorkMode=MANUAL_MODE;//返回    手动 主模式
									}
								// // else if(WorkMode==SELF_RULER_MODE)   //自刀下	
									// // {
									// // WorkMode=SELF_CUT_MODE;//返回    自刀 主模式
									// // PaperCutEnb_signal=1;
									// // }
								SubModeIcon_dis(WorkMode); //主模式icon
								PromptNum_dis();//输入范围
								PromptDis_flag=1;
								}
							
							}
						else
							{	
							
							}
							 break;						
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
						// // case MOTOR_DC_SERVO:
						// // case MOTOR_DC670_SERVO:
							// // DCServoStop();  //停止运行
							// // ServoPressStop_flag=0;
							// // DcServoGoTarget_flag=0;
							// // BellStart_flag=0;
							// // //************
							// // Run_flag=0;	
							// // InTargetPosit_flag=0;	//目标位置
							// // AutoPushRun_flag=0; //自动推纸 运行
							// // AirOffOK_flag=0;
							// // PressUp_flag=0;
							// // PressDown_flag=0;
							// // TargetSize=0;
							// // TargetSize_temp=0;
							// // BeforeKnife_offset_in=0;
							// // AutoRoute_flag=0;
								// // break;
						case MOTOR_AC_SERVO:
						case MOTOR_AC_SERVO_REV:
						case MOTOR_AC_A6_SERVO:
							ACServoStop();
							//************
							Run_flag=0;	
							InTargetPosit_flag=0;	//目标位置
							AutoPushRun_flag=0; //自动推纸 运行
							AirOffOK_flag=0;
							PressUp_flag=0;
							PressDown_flag=0;
							TargetSize=0;
							TargetSize_temp=0;
							BeforeKnife_offset_in=0;
							AutoRoute_flag=0;
								break;
						}
					
					}
				}	
			}
		else//--------------------------触摸校准
			{
			if(Board_TestMod==TEST_HELP)
				{
				Board_TestMod=TEST_TOUCH; //触摸校准 模式使能
				GLCD_Buffer_Fill(0xffff);
				x=200,y=150,back_color=WHITE_COLOR;
				switch(Language)
					{
					case CHN_HAN:
						Printf24("请用针尖触摸红色'十'字光标所在位置!",x,y,0,1,back_color);
							break;
					case ENGLISH:	
						Printf24("Please touch the red 'cross'!",x,y,0,1,back_color);
							break;
					case INDONSIA:	//印尼	
						Printf24("Silakan Sentuh kata merah 'sepuluh' pada",x,y,0,1,back_color);y+=30;
						Printf24(" lokasi kursor",x,y,0,1,back_color);
							break;
					case PORTUGAL:	//葡萄牙
						Printf24("Por favor,toque a posi??o do cursor vermelho!",x,y,0,1,back_color);
						ASCII_Printf("ca",ASCII24_MODE,12,24,PUTAO_ZK24,x+12*23,y,0,back_color);
							break;
					case SPANISH: //西班牙
						Printf24("Por favor,toque la posició ",x,y,0,1,back_color);
						Printf24("                          n del cursor!",x,y,0,0,back_color);
							break;
					}
				TouchCalcu_mode=0;
				Draw_cross(TOUCH_X1,TOUCH_Y1,RED_COLOR);
				}
			else if(Board_TestMod==TEST_TOUCH)
				{
				StartHelpMode_dis();
				Board_TestMod=TEST_HELP;
				}
			}
  	     break;
    case READ_KEY_CODE:       // F2*******************退出
		if(WorkStart_flag==1)
		   {
			if(Run_flag==0)
			    {
				// // if(ButtonTouch_mode==0)
					// // {
					switch(WorkMode)
						{
						case TEACH_MODE://示教画面下
							WorkMode=TEACH_DIVIDE_MODE;//进入---------等分模式  
							F2_DividePage_dis();  
							Total_size=0;//总长
							Divide_num=0;//等分数
							PorgSet_sel=0;
							PromptNum_dis();//输入范围
							PromptDis_flag=1;
							ACServoAlarmExec_flag=0;
							break;
						case TEACH_LABEL_MODE://已在 标签画面	
							cursor_pro=0;		
							WorkMode=TEACH_MODE;//------------------退出返回到示教主 画面
							PaperCutEnb_signal=1;
							PorgSet_sel=0;
							CurrentArea_recover2(MIDDLE_PAGE_X , MIDDLE_PAGE_Y,  M_PAGE_WIDE, M_PAGE_HIGH);
							SubModeIcon_dis(WorkMode);   //示教模式name
							PromptNum_dis();//输入范围
							PromptDis_flag=1;
							ACServoAlarmExec_flag=0;
							break;		
						case TEACH_DIVIDE_MODE://已在 等分画面 
							if(DivideValue_flag==1)	//等分值 模式
								{
								DivideValue_flag=0;//进入 等分数 模式
								DivideTypeSelExec();	//等分 类型  选择........
								}
							break;
						case TEACH_PLUS_MODE:// F5++
							WorkMode=TEACH_MODE;//返回
							PaperCutEnb_signal=1;
							PressCircle_mode=0;
							F5_plus_dis(0);
							PromptNum_dis();//输入范围
							PromptDis_flag=1;
							ACServoAlarmExec_flag=0;
							break;
						case TEACH_MINUS_MODE:// F6--
							WorkMode=TEACH_MODE;//返回
							PaperCutEnb_signal=1;
							PressCircle_mode=0;
							F6_minus_dis(0);
							PromptNum_dis();//输入范围
							PromptDis_flag=1;
							ACServoAlarmExec_flag=0;
							break;
						//*********************************************	
						case READ_PRO_MODE://  程序模式
							ReorderProByDate_dis();	//按时间排序 程序列表
							break;
						case READ_PRO_MESS_MODE:
							InputMode=CHAR_INPUT;
							ProMessIcon_dis();	//输入法模式 icon显示
							InputStus_dis(InputMode);	//输入法  选择(字母)
							break;
						
							
						//*********************************************	
						case AUTO_MODE://自动 主模式下		
							// // WorkMode=AUTO_TOOLS_MODE;//进入   ----参数模式*****************
							// // F1_ToolsPage_dis(); //参数画面
							// // Para_sel=0;
							// // PromptDis_flag=0;
							// // ACServoAlarmExec_flag=0;
							WorkMode=AUTO_DIVIDE_MODE;//进入--------自动-等分模式  
							F2_DividePage_dis();  
							Total_size=0;//总长
							Divide_num=0;//等分数
							PorgSet_sel=0;
							PromptNum_dis();//输入范围
							PromptDis_flag=1;
							ACServoAlarmExec_flag=0;
							break;		
						case AUTO_LABEL_MODE://已在 标签画面
							cursor_pro=0;		
							WorkMode=AUTO_MODE;//------------------退出返回到自动主 画面
							PorgSet_sel=0;
							CurrentArea_recover2(MIDDLE_PAGE_X , MIDDLE_PAGE_Y,  M_PAGE_WIDE, M_PAGE_HIGH);
							SubModeIcon_dis(WorkMode);   //编程模式name
							PromptNum_dis();//输入范围
							PromptDis_flag=1;
							//PaperCutEnb_signal=1;
							ACServoAlarmExec_flag=0;
							break;
						case AUTO_DIVIDE_MODE://已在 等分画面 
							if(DivideValue_flag==1)	//等分值 模式
								{
								DivideValue_flag=0;//进入 等分数 模式
								DivideTypeSelExec();	//等分 类型  选择........
								}
							break;	
						// // case AUTO_RULER_MODE:	//基准模式		
						// // case AUTO_TOOLS_MODE:// 已在  自动 -------参数模式
							// // WorkMode=AUTO_MODE;//返回    ---------自动 主模式
							// // Para_sel=0;
							// // PaperCutEnb_signal=1;
							// // PressCircle_mode=0;
							// // CurrentArea_recover2(MIDDLE_PAGE_X , MIDDLE_PAGE_Y,  M_PAGE_WIDE, M_PAGE_HIGH);
							// // SubModeIcon_dis(WorkMode); //自动mode name
							// // PromptNum_dis();//输入范围
							// // PromptDis_flag=1;
							// // ACServoAlarmExec_flag=0;
							// // break;
						case AUTO_PLUS_MODE:// F5++
							WorkMode=AUTO_MODE;//返回
							PaperCutEnb_signal=1;
							PressCircle_mode=0;
							F5_plus_dis(0);
							PromptNum_dis();//输入范围
							PromptDis_flag=1;
							ACServoAlarmExec_flag=0;
							break;
						case AUTO_MINUS_MODE:// F6--
							WorkMode=AUTO_MODE;//返回
							PaperCutEnb_signal=1;
							PressCircle_mode=0;
							F6_minus_dis(0);
							PromptNum_dis();//输入范围
							PromptDis_flag=1;
							ACServoAlarmExec_flag=0;
							break;
						//****************自刀
						/****
						case SELF_CUT_MODE://自刀 主模式下		
							WorkMode=SELF_TOOLS_MODE;//进入 自刀  ----参数模式*****************
							F1_ToolsPage_dis(); //参数画面
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
							SubModeIcon_dis(WorkMode); //自刀模式
							PromptNum_dis();//输入范围
							PromptDis_flag=1;
							ACServoAlarmExec_flag=0;
							break;
							****/
						//*******************************
						case MANUAL_MODE: //手动
							WorkMode=MANUAL_RULER_MODE; //基准
							F2_RulerPage_dis(); //基准 画面
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
						case MANUAL_IO_TEST_MODE: //IO mode
							WorkMode=MANUAL_MODE;//返回    ---------手动 主模式
							Para_sel=0;
							CurrentArea_recover2(MIDDLE_PAGE_X , MIDDLE_PAGE_Y,  M_PAGE_WIDE, M_PAGE_HIGH);
							SubModeIcon_dis(WorkMode); //手动mode name
							PromptNum_dis();//输入范围
							PromptDis_flag=1;
							ACServoAlarmExec_flag=0;
							break;
						}
					// // }
				// // else if(ButtonTouch_mode==TOU_MODE_CALC)  //计算器 弹出模式
					// // {
					// // if(WorkMode==PROG_MODE)//编程  主画面下
						// // {
						// // AllFlagSetExec_Calc(PRESS_FLAG); //计算器 标记设定	
						// // }
					// // else
						// // {
						// // CalcuInClear_exec();     //清除 计算器
						// // switch(WorkMode)
							// // {
							// // // // case AUTO_TOOLS_MODE:
							// // case MANUAL_TOOLS_MODE:
							// // // // case SELF_TOOLS_MODE:
								// // back_color=TEXT_TAB_BACK_COLOR;	//0xef9f;
								// // x=PARA_START_X1+PARA_COL_WIDE,y=PARA_START_Y,gap=PARA_ROW_GAP;
								// // if(PramSel_Page<1)	//page 1
									// // {
									// // ParameterPage1_dis(7, 0);
									// // ParameterPage1_dis(8, 0);
									// // if((MotorType==MOTOR_DC_SERVO)||(MotorType==MOTOR_DC670_SERVO))
										// // {
										// // ParameterPage1_dis(9, 0);
										// // ParameterPage1_dis(10, 0);
										// // // ParameterPage1_dis(11, 0);
										// // }
									// // else if(MotorType>=MOTOR_AC_SERVO)	
										// // {
										// // ParameterPage1_dis(9, 0);
										// // ParameterPage1_dis(10, 0);
										// // }
									// // else if(MotorType<MOTOR_DC_SERVO)
										// // {
										// // ParameterPage1_dis(9, 0);
										// // }
									// // ParameterPage1_dis(Para_sel, 1);
									// // GLCD_SetWindow_Fill( x, y, x+tx_wide, y+(gap*4-10), TEXT_TAB_BACK_COLOR, TEXT_TAB_BACK_COLOR);//clear text win
									// // switch(Language)
										// // {
										// // case CHN_HAN:
											// // Printf24("压纸停机:  ",x,y,BLACK_COLOR,1,back_color);y+=gap;
											// // Printf24("关气距离:  ",x,y,BLACK_COLOR,1,back_color);y+=gap;
											// // switch(MotorType)
												// // {
												// // case MOTOR_FREQ_5_SPD_RST:
												// // case MOTOR_FREQ_3_SPD:
												// // case MOTOR_FREQ_3_SPD_RST:
													// // Printf24("光电选择:  ",x,y,BLACK_COLOR,1,back_color);
														// // break;
												// // case MOTOR_DC_SERVO:
												// // case MOTOR_DC670_SERVO:
													// // Printf24("最大速度:  ",x,y,BLACK_COLOR,1,back_color);y+=gap;
													// // Printf24("点动速度:  ",x,y,BLACK_COLOR,1,back_color);
														// // break;
												// // case MOTOR_AC_SERVO:
												// // case MOTOR_AC_SERVO_REV:
													// // Printf24("运行速度:  ",x,y,BLACK_COLOR,1,back_color);y+=gap;
													// // Printf24("光电选择:  ",x,y,BLACK_COLOR,1,back_color);
														// // break;
												// // }
												// // break;
										// // case ENGLISH:
											// // Printf24("Press-Stop: ",x,y,BLACK_COLOR,1,back_color);y+=gap;
											// // Printf24("AirOff-dist:",x,y,BLACK_COLOR,1,back_color);y+=gap;
											// // switch(MotorType)
												// // {
												// // case MOTOR_FREQ_5_SPD_RST:
												// // case MOTOR_FREQ_3_SPD:
												// // case MOTOR_FREQ_3_SPD_RST:
													// // Printf24("IR-Set:  ",x,y,BLACK_COLOR,1,back_color);
														// // break;
												// // case MOTOR_DC_SERVO:
												// // case MOTOR_DC670_SERVO:
													// // Printf24("Max-speed:",x,y,BLACK_COLOR,1,back_color);y+=gap;
													// // Printf24("Jog-speed:",x,y,BLACK_COLOR,1,back_color);
														// // break;
												// // case MOTOR_AC_SERVO:
												// // case MOTOR_AC_SERVO_REV:
													// // Printf24("Run-speed:",x,y,BLACK_COLOR,1,back_color);y+=gap;
													// // Printf24("IR-Set:  ",x,y,BLACK_COLOR,1,back_color);
														// // break;
												// // }
												// // break;
										// // case INDONSIA:	//印尼
											// // Printf24("Plat-bawah:",x,y,BLACK_COLOR,1,back_color);y+=gap;
											// // Printf24("Off gas da: ",x,y,BLACK_COLOR,1,back_color);y+=gap;
											// // switch(MotorType)
												// // {
												// // case MOTOR_FREQ_5_SPD_RST:
												// // case MOTOR_FREQ_3_SPD:
												// // case MOTOR_FREQ_3_SPD_RST:
													// // Printf24("Set-IR: ",x,y,BLACK_COLOR,1,back_color);
														// // break;
												// // case MOTOR_DC_SERVO:
												// // case MOTOR_DC670_SERVO:
													// // Printf24("Tercepat:",x,y,BLACK_COLOR,1,back_color);y+=gap;
													// // Printf24("Jog-kecep:",x,y,BLACK_COLOR,1,back_color);
														// // break;
												// // case MOTOR_AC_SERVO:
												// // case MOTOR_AC_SERVO_REV:
													// // Printf24("Kecepa-lari:",x,y,BLACK_COLOR,1,back_color);y+=gap;
													// // Printf24("Set-IR: ",x,y,BLACK_COLOR,1,back_color);
														// // break;
												// // }
												// // break;
										// // case PORTUGAL:	//葡萄牙
											// // Printf24("encerra:",x,y,BLACK_COLOR,1,back_color);y+=gap;
											// // Printf24("Off Air:",x,y,BLACK_COLOR,1,back_color);y+=gap;
											// // switch(MotorType)
												// // {
												// // case MOTOR_FREQ_5_SPD_RST:
												// // case MOTOR_FREQ_3_SPD:
												// // case MOTOR_FREQ_3_SPD_RST:
													// // Printf24("estado IR:",x,y,BLACK_COLOR,1,back_color);
														// // break;
												// // case MOTOR_DC_SERVO:
												// // case MOTOR_DC670_SERVO:
													// // Printf24("Veloci-má  ",x,y,BLACK_COLOR,1,back_color);
													// // Printf24("          x:",x,y,BLACK_COLOR,0,back_color);y+=gap;
													// // Printf24("Veloci-Jog:",x,y,BLACK_COLOR,1,back_color);
														// // break;
												// // case MOTOR_AC_SERVO:
												// // case MOTOR_AC_SERVO_REV:
													// // Printf16("Veloci-corrida:",x,y,BLACK_COLOR,1,back_color);y+=gap;
													// // Printf24("estado IR:",x,y,BLACK_COLOR,1,back_color);
														// // break;
												// // }
												// // break;
										// // case SPANISH: //西班牙
											// // Printf24("cierre:",x,y,BLACK_COLOR,1,back_color);y+=gap;
											// // Printf24("Off Air:",x,y,BLACK_COLOR,1,back_color);y+=gap;
											// // switch(MotorType)
												// // {
												// // case MOTOR_FREQ_5_SPD_RST:
												// // case MOTOR_FREQ_3_SPD:
												// // case MOTOR_FREQ_3_SPD_RST:
													// // Printf24("estado IR:",x,y,BLACK_COLOR,1,back_color);
														// // break;
												// // case MOTOR_DC_SERVO:
												// // case MOTOR_DC670_SERVO:
													// // Printf24("Veloci-má  ",x,y,BLACK_COLOR,1,back_color);
													// // Printf24("          x:",x,y,BLACK_COLOR,0,back_color);y+=gap;
													// // Printf24("Veloci-Jog:",x,y,BLACK_COLOR,1,back_color);
														// // break;
												// // case MOTOR_AC_SERVO:
												// // case MOTOR_AC_SERVO_REV:
													// // Printf16("Veloci-corrida:",x,y,BLACK_COLOR,1,back_color);y+=gap;
													// // Printf24("estado IR:",x,y,BLACK_COLOR,1,back_color);
														// // break;
												// // }
												// // break;		
										// // }	
									// // }
								// // break;
							
							// // case  PROG_MODE://编程画面下
							// // case AUTO_MODE://自动主画面下
							// // case AUTO_PLUS_MODE://自动F5++
							// // case AUTO_MINUS_MODE://自动F6--
							// // case TEACH_MODE://示教 模式
							// // case AUTO_TO_SELF_MODE:   //自动-->自刀过度 模式
							// // case SELF_CUT_MODE:  //自刀主 模式
							// // case TEACH_PLUS_MODE: //自刀 F5++
							// // case TEACH_MINUS_MODE://自刀 F6--
								// // if(Knife_order>OnePro_head.pro_knifeSUM)
									 // // K_temp=Knife_order-1;
								 // // else
									 // // K_temp=Knife_order;
								// // ProgressBar_dis(OnePro_head.pro_knifeSUM,K_temp);  //进度条 显示
								// // KnifeUp_flag=0;
								// // KnifeDown_flag=0;
								// // PressUp_flag=0;
								// // PressDown_flag=0;
								// // A_Down_flag=0;
								// // B_Down_flag=0;
								// // A_Up_flag=0;
								// // B_Up_flag=0;
								// // IR_Up_flag=0;
								// // IR_Down_flag=0;
								// // //--------------更新显示刀——推纸标志
								
								// // Size_1page_dis(Knife_order-cursor_row,0);//一页尺寸显示
								// // break;	
							// // }
						// // }
					// // }
				// // else if(ButtonTouch_mode==TOU_MODE_F4)  // 标记 弹出框
					// // {
					// // AllFlagSetExec(PRESS_FLAG); //设定 压纸标记
					// // }
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
							// // case MOTOR_DC_SERVO:
							// // case MOTOR_DC670_SERVO:
								// // DCServoStop();  //停止运行
								// // ServoPressStop_flag=0;
								// // DcServoGoTarget_flag=0;
								// // BellStart_flag=0;
								// // //************
								// // Run_flag=0;	
								// // InTargetPosit_flag=0;	//目标位置
								// // AutoPushRun_flag=0; //自动推纸 运行
								// // TargetSize=0;
								// // TargetSize_temp=0;
								// // BeforeKnife_offset_in=0;
								// // AutoRoute_flag=0;
									// // break;
							case MOTOR_AC_SERVO:
							case MOTOR_AC_SERVO_REV:
							case MOTOR_AC_A6_SERVO:
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
			// // ClrInput_function();//清零 输入框
		   }
		else  
		   {
			if(Board_TestMod==TEST_HELP)
				{
				Manual_page=0;
				Comment_dis_page(Manual_page);//注释1
				Board_TestMod=TEST_ICON;
				}
			else if(Board_TestMod==TEST_ICON)
				{
				StartHelpMode_dis();
				Board_TestMod=TEST_HELP;
				Manual_page=0;
				}
		   }
  	     break;
    case RETURN_KEY_CODE:      //F3************
		if(WorkStart_flag==1)
		   {
			if(Run_flag==0)
			    {
					switch(WorkMode)
						{
						
						case AUTO_DIVIDE_MODE://已在 等分画面 
						case TEACH_DIVIDE_MODE://已在 等分画面 
							if(DivideValue_flag==0)	//等分数 模式
								{
								DivideValue_flag=1;//进入 等分值 模式
								DivideTypeSelExec();	//等分 类型  选择........
								}
							break;
						case READ_PRO_MODE://  已在选择程序模式	顺序显示	
						// // case TEACH_PRO_MODE:	//已在选择程序模式	顺序显示
							DisAllProgMode=PRO_BY_NUM;
							ProTableIcon_dis();	//程序列表模式下 icon显示
							for(g=1;g<=MAX_PROG;g++)
								ProNumGroup[g]=g;
							prog_order=1;
							CursorPro_dis(cursor_pro,0);//pro光标
							cursor_pro=0;
							Prog_1page_dis(prog_order, cursor_pro);//===程序---数据显示
							TableDis_startcol=PROC_NUM_X;
							CursorPro_dis(cursor_pro,1);//pro光标
							OneProgHeadInfo_dis(cursor_pro ,  prog_order, 1);	//一条程序 显示
							break;
						case READ_PRO_MESS_MODE:
							InputMode=NUMBER_INPUT;
							ProMessIcon_dis();	//输入法模式 icon显示
							InputStus_dis(InputMode);	//输入法  选择(数字)
							break;
							
						
						case TEACH_MODE:	
						case AUTO_MODE://自动 主模式下************  插入
							//ClrInput_function();//清零 输入框
							// // WorkMode=AUTO_PLUS_MODE;  //F5++
							// // F5_plus_dis(1);//  ++
							if(num_cou>0)
								{
								if(CheckInputNums()==1)// 输入 有效
									{
									if(Knife_order<=OnePro_head.pro_knifeSUM)
										{
										if(OnePro_head.pro_knifeSUM<MAX_Knife)
											{
											OnePro_head.pro_knifeSUM++;
											InsertOneKnife(Pro_data.pro_num, Knife_order);
											pKnife_data=(pInt8U)&OneKnife_data;
											// GetOneKnife_datas(Knife_order, pKnife_data);//
											OneKnife_data.size=InputSize;  //尺寸修改
											OneKnife_data.k_flag=NO_FLAG;  //清除 标志
											SaveOneKnife_datas(Pro_data.pro_num, Knife_order , pKnife_data);//保存一刀数据
											//------------------//下一刀 清除刀 标记
											if((Knife_order+1)<=OnePro_head.pro_knifeSUM)
												{
												GetOneKnife_datas(Pro_data.pro_num, Knife_order+1, pKnife_data);//下一刀
												if((OneKnife_data.k_flag&0xf)==KNIFE_FLAG) //刀 标志
													{
													if(OneKnife_data.size>InputSize)
														{
														OneKnife_data.k_flag&=0xf0;	//清除刀 标记
														SaveOneKnife_datas(Pro_data.pro_num, Knife_order+1 , pKnife_data);//保存一刀数据
														}
													}
												}
											//-----显示
											//KnifeSize_dis(cursor_row,InputSize);//尺寸
											StepNum_dis(OnePro_head.pro_knifeSUM,Knife_order);//步骤更新
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
												case INDONSIA:	//印尼
													Printf16("Penuh, tidak dapat dimasukkan",REMIND_WINDOW_X,REMIND_WINDOW_Y+5,RED_COLOR,0,0xffff);
													break;
												case PORTUGAL:	//葡萄牙
													Printf16("Dados estácheio, n?o pode entrar",REMIND_WINDOW_X,REMIND_WINDOW_Y+5,RED_COLOR,0,0xffff);
													ASCII_Printf("a",ASCII16_MODE,8,16,PUTAO_ZK16,REMIND_WINDOW_X+8*19,REMIND_WINDOW_Y+5,RED_COLOR,0xffff);
													break;
												case SPANISH: //西班牙
													Printf16("No puede insertar datos se ha llenado",REMIND_WINDOW_X,REMIND_WINDOW_Y+5,RED_COLOR,0,0xffff);
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
											case INDONSIA:	//印尼
												Printf16("Tekan tombol OK setelah masukan",REMIND_WINDOW_X,REMIND_WINDOW_Y+5,RED_COLOR,0,0xffff);
													break;	
											case PORTUGAL:	//葡萄牙
												Printf24("Clique no bot?o OK",REMIND_WINDOW_X,REMIND_WINDOW_Y+5,RED_COLOR,0,0xffff);
												ASCII_Printf("a",ASCII24_MODE,12,24,PUTAO_ZK24,REMIND_WINDOW_X+12*13,REMIND_WINDOW_Y+5,RED_COLOR,0xffff);
													break;	
											case SPANISH: //西班牙
												Printf24("Haga clic en el botó",REMIND_WINDOW_X,REMIND_WINDOW_Y+5,RED_COLOR,0,0xffff);
												Printf24("                    n OK",REMIND_WINDOW_X,REMIND_WINDOW_Y+5,RED_COLOR,0,0xffff);
													break;	
											}
										}
									}
								} 		
							break;
							
						case MANUAL_MODE: //手动-----------------------
							WorkMode=MANUAL_CLOCK_MODE; // 时钟 模式
							Para_sel=0;PromptDis_flag=0;
							ClockPage_dis();
							Year_before=Year,Month_before=Month,Day_before=Dom; //当前时间 暂存
							ACServoAlarmExec_flag=0;
							break;
						}
				// // else if(ButtonTouch_mode==TOU_MODE_CALC)  //计算器 弹出模式
					// // {
					// // if(WorkMode==PROG_MODE)//编程  主画面下
						// // {
						// // AllFlagSetExec_Calc(SORT_FLAG); //计算器 标记设定	
						// // }
					// // }
				// // else if(ButtonTouch_mode==TOU_MODE_F4)  // 标记 弹出框	
					// // {
					// // AllFlagSetExec(SORT_FLAG); //设定 理纸标记
					// // }
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
						// // case MOTOR_DC_SERVO:
						// // case MOTOR_DC670_SERVO:
							// // DCServoStop();  //停止运行
							// // ServoPressStop_flag=0;
							// // DcServoGoTarget_flag=0;
							// // BellStart_flag=0;
							// // //************
							// // Run_flag=0;	
							// // InTargetPosit_flag=0;	//目标位置
							// // AutoPushRun_flag=0; //自动推纸 运行
							// // TargetSize=0;
							// // TargetSize_temp=0;
							// // BeforeKnife_offset_in=0;
							// // AutoRoute_flag=0;
								// // break;
						case MOTOR_AC_SERVO:
						case MOTOR_AC_SERVO_REV:
						case MOTOR_AC_A6_SERVO:
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
		    }
		else
			{
			if(Board_TestMod==TEST_HELP)
				{
				Board_TestMod=TEST_BOARD;     //主板测试  模式****************************
				GLCD_Buffer_Fill(0xffff);
				IO_InputDisInit();  //Io 输入口初始值
				KeyDis_Init();//按键显示初始化
				}
			else if(Board_TestMod==TEST_BOARD)
				{
				// StartHelpMode_dis();
				// Board_TestMod=TEST_HELP;
				}
			}
  	     break;    
	case MANUAL_KEY_CODE:   // F4************** 
		if(WorkStart_flag==1)
		   {
		    if(Run_flag==0)
			    {
					switch(WorkMode)
						{
							/***
						case PROG_MODE://编程 主画面下
							AllFlagSetExec(PUSH_FLAG); //设定 推纸标记// Set_AllFlagWind_In();  //F4 标记位	模式
							FirstKnife_num=0;
							LastKnife_num_temp=0;
								// // ClrInput_function();//清零 输入框
							break;**/
						case AUTO_DIVIDE_MODE://已在 等分画面 
							cursor_pro=0;		
							WorkMode=AUTO_MODE;//------------------退出返回到自动主 画面
							PorgSet_sel=0;
							CurrentArea_recover2(MIDDLE_PAGE_X , MIDDLE_PAGE_Y,  M_PAGE_WIDE, M_PAGE_HIGH);
							SubModeIcon_dis(WorkMode);   //编程模式name
							PromptNum_dis();//输入范围
							PromptDis_flag=1;
							ACServoAlarmExec_flag=0;
							break;
						case TEACH_DIVIDE_MODE://已在 等分画面
							cursor_pro=0;		
							WorkMode=TEACH_MODE;//------------------退出返回到示教主 画面
							PaperCutEnb_signal=1;
							PorgSet_sel=0;
							CurrentArea_recover2(MIDDLE_PAGE_X , MIDDLE_PAGE_Y,  M_PAGE_WIDE, M_PAGE_HIGH);
							SubModeIcon_dis(WorkMode);   //示教模式name
							PromptNum_dis();//输入范围
							PromptDis_flag=1;
							ACServoAlarmExec_flag=0;
							break;
						case READ_PRO_MODE:		// 程序模式
						// // case TEACH_PRO_MODE:	//F3程序列表 模式
							DeleteOneProg(cursor_pro, prog_order);		//F6--删除一个程序
							break;
						case READ_PRO_MESS_MODE: //程序信息模式
						// // case TEACH_PRO_MESS_MODE: //程序信息模式
							F4MessageMode_Exit(); //退出  程序信息模式
							SubModeIcon_dis(WorkMode);   //程序选择模式
							break;	
						case TEACH_MODE://示教 主画面下
						case AUTO_MODE://自动 主模式下************删除一刀
							// // ClrInput_function();//清零 输入框
							// // WorkMode=AUTO_MINUS_MODE;// F6--
							// // F6_minus_dis(1);//--
							if(Knife_order<=OnePro_head.pro_knifeSUM)
								{
								DeleteOneKnife(Pro_data.pro_num, Knife_order);      //删除一刀
								if(OnePro_head.pro_knifeSUM>1)
									{
									OnePro_head.pro_knifeSUM--;
									SavePro_headInfo(Pro_data.pro_num, (pInt8U)&OnePro_head);
									StepNum_dis(OnePro_head.pro_knifeSUM,Knife_order);//步骤更新
									
									if(Knife_order<=OnePro_head.pro_knifeSUM)
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
										if((OneKnife_data.k_flag&0xf)==KNIFE_FLAG) //刀 标志
											{
											if(OneKnife_data.size>perv_data)
												{
												OneKnife_data.k_flag&=0xf0;//清除 刀 标志
												Flg_chg=1;
												flag_now=OneKnife_data.k_flag;	//当前标记 暂存
												SaveOneKnife_datas(Pro_data.pro_num, Knife_order , pKnife_data);//保存一刀数据
												}
											}	
										}
									}
								Size_1page_dis(Knife_order,cursor_row);
								
								if(Flg_chg==1)
									{
									AllFlagPic_dis(cursor_row,flag_now); //光标处  标记图片 显示
									}
								}
							break;
						
						case MANUAL_MODE: //电子手轮 开关
							if(MotorType>=MOTOR_AC_SERVO)
								{
								ElectricWheelOn_flag=!ElectricWheelOn_flag;
								SaveElectricWheelSwitch();//电子手轮
								ElectricalWheel_dis();  //电子手轮  开关状态
								}
							break;
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
						// // case MOTOR_DC_SERVO:
						// // case MOTOR_DC670_SERVO:
							// // DCServoStop();  //停止运行
							// // ServoPressStop_flag=0;
							// // DcServoGoTarget_flag=0;
							// // BellStart_flag=0;
							// // //************
							// // Run_flag=0;	
							// // InTargetPosit_flag=0;	//目标位置
							// // AutoPushRun_flag=0; //自动推纸 运行
							// // TargetSize=0;
							// // TargetSize_temp=0;
							// // BeforeKnife_offset_in=0;
							// // AutoRoute_flag=0;
								// // break;
						case MOTOR_AC_SERVO:
						case MOTOR_AC_SERVO_REV:
						case MOTOR_AC_A6_SERVO:
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
					}		
				}
		   }
		else
			{
			if(Board_TestMod==TEST_HELP)
				{
				Board_TestMod=TEST_SYS_WORD;   
				SysBoardSelect_dis();  //系统版本选择 密码进入****************************
				}
			else if(Board_TestMod==TEST_SYS_WORD)
				{
				for(num_cou=0;num_cou<8;num_cou++)
					 {
					 Size_temp[num_cou++]=0;
					 }
				num_cou=0; //;  //系统版本选择   退出
				StartHelpMode_dis();
				Board_TestMod=TEST_HELP;
				}
			}
		
  	     break; 
	case F6_KEY_CODE:	//F6
			F6_KeyExec();//F6  处理
			break;
	case F5_KEY_CODE:	//F5
			F5_KeyExec();//F5  处理
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
					/***
					if(num_cou>0)
						ClrInput_function();//清零 输入框
					if(ButtonTouch_mode==0)
						{
						switch(WorkMode)
							{
							case AUTO_TO_SELF_MODE:  //自动-->自刀过度 模式
									
									break;
							case PROG_PRO_MESS_MODE: //程序信息模式
							case TEACH_PRO_MESS_MODE: //程序信息模式
									ClrInputName_exec();		//清除输入操作	
									break;
							case PROG_DEL_ALL_PRO_MODE://删除所有pro
							case TEACH_DEL_ALL_PRO_MODE://删除所有pro
							case PROG_DEL_ALL_SIZE_MODE://	删除所有尺寸
							case TEACH_DEL_ALL_SIZE_MODE://	删除所有尺寸
									DeleteAllExitWind();	//退出全删 提示框	
									break;
							}
						}
					else if(ButtonTouch_mode==TOU_MODE_CALC)
						{
						if(CalcNoNumInput_flag==0)//  计算器已经输入 数据
							{
							ClearCalculatorInput(); //清零计算器 输入
							}
						}
					else if(ButtonTouch_mode==TOU_MODE_AUTOCUT_IN) //自动-->自刀过度  	提示
						{
						ButtonTouch_mode=0;
						if(WorkMode==AUTO_TO_SELF_MODE)  //自动-->自刀过度 模式
							{
							if(ReEnterAutoKnife_dis==0) //非重入 提示  显示
								{
								// WorkMode=AUTO_MODE;//返回 自动主
								WorkMode=MainMode_temp;//返回 之前模式
								PaperCutEnb_signal=1;
								PressCircle_mode=0;
								CurrentArea_recover2(SELF_PROMP_X,SELF_PROMP_Y,SELF_PROMP_WIDE,SELF_PROMP_HIGH);
								}
							else   //再次  进入 第一刀
								{
								if(ButtonTouch_mode==TOU_MODE_CALC)  //	  触摸 下
									CalcuInClear_exec();     //清除 计算器
								WorkMode=SELF_CUT_MODE;  //进入   ----------自刀主 模式
								CurrentArea_recover2(SELF_PROMP_X,SELF_PROMP_Y,SELF_PROMP_WIDE,SELF_PROMP_HIGH);
								AutoCutModePage_dis(); //自刀模式 部分画面显示
								//------------返回第一刀
								ClrInput_function();//清零 输入框 
								CursorKnife_dis(cursor_row, 0);//红色光标消失
								cursor_row=0;
								CursorKnife_dis(cursor_row, 1);//红色光标显示
								Knife_order=1;//
								Size_1page_dis(Knife_order,0);//一页尺寸显示
								if(Knife_order<=OnePro_head.pro_knifeSUM)
									StepOrder_dis(Knife_order);//步骤更新 
									
								LastAutoKnife_order=1;
								ReEnterAutoKnife_dis=0;
								AutoCutDisable_flag=0;
								}
							}
						}
						***/
					switch(WorkMode)
						{
						case AUTO_TO_SELF_MODE:  //自动-->自刀过度 模式
								if(ReEnterAutoKnife_dis==0) //非重入 提示  显示
									{
									// WorkMode=AUTO_MODE;//返回 自动主
									WorkMode=MainMode_temp;//返回 之前模式
									PaperCutEnb_signal=1;
									PressCircle_mode=0;
									CurrentArea_recover2(SELF_PROMP_X,SELF_PROMP_Y,SELF_PROMP_WIDE,SELF_PROMP_HIGH);
									}
								else   //再次  进入 第一刀
									{
									WorkMode=SELF_CUT_MODE;  //进入   ----------自刀主 模式
									CurrentArea_recover2(SELF_PROMP_X,SELF_PROMP_Y,SELF_PROMP_WIDE,SELF_PROMP_HIGH);
									AutoCutModePage_dis(); //自刀模式 部分画面显示
									//------------返回第一刀
									// // ClrInput_function();//清零 输入框 
									CursorKnife_dis(cursor_row, 0);//红色光标消失
									cursor_row=0;
									CursorKnife_dis(cursor_row, 1);//红色光标显示
									Knife_order=1;//
									Size_1page_dis(Knife_order,0);//一页尺寸显示
									if(Knife_order<=OnePro_head.pro_knifeSUM)
										StepOrder_dis(Knife_order);//步骤更新 
										
									LastAutoKnife_order=1;
									ReEnterAutoKnife_dis=0;
									}
								break;
						case READ_PRO_MESS_MODE: //程序信息模式
						// // case TEACH_PRO_MESS_MODE: //程序信息模式
								ClrInputName_exec();		//清除输入操作	
								break;
						case READ_DEL_ALL_PRO_MODE://删除所有pro
						// // case TEACH_DEL_ALL_PRO_MODE://删除所有pro
						case AUTO_DEL_ALL_SIZE_MODE://	删除所有尺寸
						case TEACH_DEL_ALL_SIZE_MODE://	删除所有尺寸
								DeleteAllExitWind();	//退出全删 提示框	
								break;
						default :
								if(CalcNoNumInput_flag==0)//  计算器已经输入 数据
								{
								ClearCalculatorInput(); //清零计算器 输入
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
					case MOTOR_AC_SERVO:
					case MOTOR_AC_SERVO_REV:
					case MOTOR_AC_A6_SERVO:
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
					// // case MOTOR_DC_SERVO:
							// // break;
					}
				ClrSysBoardNum_dis(); //清除 系统选择  密码	>>>>>>>>>>>>>>>>>>>>
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
						// if(Sign_flag==1)
							// {
							// num_cou=0;
							// GLCD_SetWindow_Fill( SIZE_WINDOW_X, SIZE_WINDOW_Y, SIZE_WINDOW_X+SIZE_WINDOW_WIDE, SIZE_WINDOW_Y+SIZE_WINDOW_HIGH, 0xfffff, 0xffff);//尺寸输入框
							// Sign_flag=0;
							// }
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
				// // case MOTOR_DC_SERVO:
				// // case MOTOR_DC670_SERVO:
					// // if(StartCheck_mode<2)
						// // {
						// // GoFrontEn_flag=1;
						// // GoFast_flag=0;
						// // ManualMoveMode=0;
						// // }
						// // break;
				case MOTOR_AC_SERVO:
				case MOTOR_AC_SERVO_REV:
				case MOTOR_AC_A6_SERVO:
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
	case FAST_AHEAD_KEY_CODE:   //快进按键***************
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
						       qianjinflag=1;
						GoFrontEn_flag=1;
						GoFast_flag=1;
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
						GoFast_flag=1;
						ManualMoveMode=0;
						}
						break;
				// // case MOTOR_DC_SERVO:
				// // case MOTOR_DC670_SERVO:
					// // if(StartCheck_mode<2)
						// // {
						// // GoFrontEn_flag=1;
						// // GoFast_flag=1;
						// // ManualMoveMode=0;
						// // }
						// // break;
				case MOTOR_AC_SERVO:
				case MOTOR_AC_SERVO_REV:
				case MOTOR_AC_A6_SERVO:
					if(StartCheck_mode<=2)
						{
						GoFrontEn_flag=1;
						GoFast_flag=1;
						ManualMoveMode=0;
						}
						break;
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
				// // case MOTOR_DC_SERVO:
				// // case MOTOR_DC670_SERVO:
					// // if(StartCheck_mode<2)
						// // {
						// // GoBackEn_flag=1;
						// // GoFast_flag=0;
						// // ManualMoveMode=0;
						// // }
						// // break;
				case MOTOR_AC_SERVO:
				case MOTOR_AC_SERVO_REV:
				case MOTOR_AC_A6_SERVO:
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
	case FAST_BACK_KEY_CODE:     //快退按键**************
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
						GoFast_flag=1;
						ManualMoveMode=0;
						}
						break;
				// // case MOTOR_DC_SERVO:
				// // case MOTOR_DC670_SERVO:
					// // if(StartCheck_mode<2)
						// // {
						// // GoBackEn_flag=1;
						// // GoFast_flag=1;
						// // ManualMoveMode=0;
						// // }
						// // break;
				case MOTOR_AC_SERVO:
				case MOTOR_AC_SERVO_REV:
				case MOTOR_AC_A6_SERVO:
					if(StartCheck_mode<=2)
						{
						GoBackEn_flag=1;
						GoFast_flag=1;
						ManualMoveMode=0;
						}
						break;
				}	
			}
  	     break;	 
    case REV_KEY_CODE:   //  “+”  ***************
        if(WorkStart_flag==1)  
			{
			if(Run_flag==0)
			    {
				CalculatorValue_exec('+');	
				}	
            } 
         break;        
    case OPTION_KEY_CODE:    //减号  “-/除”  *************
       if(WorkStart_flag==1)  
			{
			if(Run_flag==0)
			    {
				CalculatorValue_exec('-');	
				// else if(ButtonTouch_mode==TOU_MODE_F4)//标记  模式
					// {
					// NumKey_exec('-');
					// }
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
				// // case PROG_MODE://编程画面下
				case TEACH_MODE://示教画面下
				case AUTO_MODE://自动主画面下
				case SELF_CUT_MODE://自刀主画面下
					
							break;
				// // case AUTO_TOOLS_MODE://  参数设置
				// // case SELF_TOOLS_MODE://  参数设置
				case MANUAL_TOOLS_MODE:// 手动 参数模式
					if(PramSel_Page<1)	//page 1
						{
						switch(Para_sel)
							{
							case 3://语言
								Language++;
								if(Language>3)
									Language=0;
								//***********界面语言更新
								x=PARA_START_X1,y=PARA_START_Y;back_color=TEXT_TAB_BACK_COLOR,gap=PARA_ROW_GAP;//
								GLCD_SetWindow_Fill(x,y,x+145,y+(PARA_ROW_GAP*7)-20,back_color,back_color);
								GLCD_SetWindow_Fill( x, y, x+tx_wide, y+(gap*7-10), TEXT_TAB_BACK_COLOR, TEXT_TAB_BACK_COLOR);//clear text win
								switch(Language)
									{
									case CHN_HAN:
										x=PARA_START_X1,y=PARA_START_Y,gap=PARA_ROW_GAP;//0xef9f;
										Printf24("前极限:    ",x,y,BLACK_COLOR,1,back_color);y+=gap;
										Printf24("中极限:    ",x,y,BLACK_COLOR,1,back_color);y+=gap;
										Printf24("后极限:    ",x,y,BLACK_COLOR,1,back_color);y+=gap;
										Printf24("语言:    ",x,y,BLACK_COLOR,1,back_color);  y+=gap;
										Printf24("单位:   ",x,y,BLACK_COLOR,1,back_color);  y+=gap;
										Printf24("提前量:  ",x,y,BLACK_COLOR,1,back_color);y+=gap;
										//Printf24("标准距离:   ",x,y,BLACK_COLOR,1,back_color);
										Printf24("推纸距离:  ",x,y,BLACK_COLOR,1,back_color);
										if(ButtonTouch_mode==0)  //	 非 触摸计算器 下
											{
											x+=PARA_COL_WIDE;y=PARA_START_Y;
											GLCD_SetWindow_Fill( x, y, x+tx_wide, y+(gap*4-10), TEXT_TAB_BACK_COLOR, TEXT_TAB_BACK_COLOR);//clear text win
											Printf24("压纸停机: ",x,y,BLACK_COLOR,1,back_color);y+=gap;
											Printf24("关气距离: ",x,y,BLACK_COLOR,1,back_color);y+=gap;
											ParameterPage1_dis(7, 0);
											
											switch(MotorType)
												{
												case MOTOR_FREQ_5_SPD_RST:
												case MOTOR_FREQ_3_SPD:
												case MOTOR_FREQ_3_SPD_RST:
													Printf24("光电选择:  ",x,y,BLACK_COLOR,1,back_color);
													ParameterPage1_dis(9, 0);
														break;
												// // case MOTOR_DC_SERVO:
												// // case MOTOR_DC670_SERVO:
													// // Printf24("最大速度:  ",x,y,BLACK_COLOR,1,back_color);y+=gap;
													// // Printf24("点动速度:  ",x,y,BLACK_COLOR,1,back_color);
													// // // ParameterPage1_dis(11, 0);
														// // break;
												case MOTOR_AC_SERVO:
												case MOTOR_AC_SERVO_REV:
												case MOTOR_AC_A6_SERVO:
													Printf24("运行速度:  ",x,y,BLACK_COLOR,1,back_color);y+=gap;
													Printf24("光电选择:  ",x,y,BLACK_COLOR,1,back_color);
													ParameterPage1_dis(10, 0);
														break;
												}
											}
										x=PROG_X,y=PROG_Y;back_color=STEP_BACK_COLOR;
										GLCD_SetWindow_Fill( x, y, x+100, y+24, back_color,back_color);//clear text win
										Printf16(" 程序  ",x,y,BLACK_COLOR,1,back_color);
										x=STEP_X;//
										GLCD_SetWindow_Fill( x, y, x+100, y+24, back_color,back_color);//clear text win
										Printf16(" 步骤  ",x,y,BLACK_COLOR,1,back_color);//
										break;
									case ENGLISH:	
										x=PARA_START_X1,y=PARA_START_Y,gap=PARA_ROW_GAP;//back_color=TEXT_TAB_BACK_COLOR;//0xef9f;
										Printf24("Front-limit:",x,y,BLACK_COLOR,1,back_color);y+=gap;
										Printf24("Midd-limit: ",x,y,BLACK_COLOR,1,back_color);y+=gap;
										Printf24("Back-limit: ",x,y,BLACK_COLOR,1,back_color);y+=gap;
										Printf24("Language:   ",x,y,BLACK_COLOR,1,back_color);  y+=gap;
										Printf24("Unit:       ",x,y,BLACK_COLOR,1,back_color);  y+=gap;
										Printf24("Advanced:   ",x,y,BLACK_COLOR,1,back_color);y+=gap;
										Printf24("Push-distan:",x,y,BLACK_COLOR,1,back_color);
										if(ButtonTouch_mode==0)  //	 非 触摸计算器 下
											{
											x+=PARA_COL_WIDE;y=PARA_START_Y;
											GLCD_SetWindow_Fill( x, y, x+tx_wide, y+(gap*4-10), TEXT_TAB_BACK_COLOR, TEXT_TAB_BACK_COLOR);//clear text win
											Printf24("Press-Stop:",x,y,BLACK_COLOR,1,back_color);y+=gap;
											Printf24("AirOff-dist:",x,y,BLACK_COLOR,1,back_color);y+=gap;
											ParameterPage1_dis(7, 0);
											switch(MotorType)
												{
												case MOTOR_FREQ_5_SPD_RST:
												case MOTOR_FREQ_3_SPD:
												case MOTOR_FREQ_3_SPD_RST:
													Printf24("IR-Set:  ",x,y,BLACK_COLOR,1,back_color);
													ParameterPage1_dis(9, 0);
														break;
												// // case MOTOR_DC_SERVO:
												// // case MOTOR_DC670_SERVO:
													// // Printf24("Max-speed:",x,y,BLACK_COLOR,1,back_color);y+=gap;
													// // Printf24("Jog-speed:",x,y,BLACK_COLOR,1,back_color);
													// // // ParameterPage1_dis(11, 0);
														// // break;
												case MOTOR_AC_SERVO:
												case MOTOR_AC_SERVO_REV:
												case MOTOR_AC_A6_SERVO:
													Printf24("Run-speed:",x,y,BLACK_COLOR,1,back_color);y+=gap;
													Printf24("IR-Set:  ",x,y,BLACK_COLOR,1,back_color);
													ParameterPage1_dis(10, 0);
														break;
												}
											}
										x=PROG_X,y=PROG_Y;back_color=STEP_BACK_COLOR;
										GLCD_SetWindow_Fill( x, y, x+100, y+24, back_color,back_color);//clear text win
										Printf16("Process",x,y,BLACK_COLOR,1,back_color);
										x=STEP_X;//
										GLCD_SetWindow_Fill( x, y, x+100, y+24, back_color,back_color);//clear text win
										Printf16(" Step  ",x,y,BLACK_COLOR,1,back_color);
										break;
									case INDONSIA:	//印尼
										x=PARA_START_X1,y=PARA_START_Y,gap=PARA_ROW_GAP;//back_color=TEXT_TAB_BACK_COLOR;//0xef9f;
										Printf24("Sete-batas:",x,y,BLACK_COLOR,1,back_color);y+=gap;
										Printf24("Dala-batas:",x,y,BLACK_COLOR,1,back_color);y+=gap;
										Printf24("Sebe-batas:",x,y,BLACK_COLOR,1,back_color);y+=gap;
										Printf24("Bahasa:",x,y,BLACK_COLOR,1,back_color);  y+=gap;
										Printf24("Satuan:",x,y,BLACK_COLOR,1,back_color);  y+=gap;
										Printf24("Memajukan:",x,y,BLACK_COLOR,1,back_color);y+=gap;
										Printf24("Doro-jarak:",x,y,BLACK_COLOR,1,back_color);
										if(ButtonTouch_mode==0)  //	 非 触摸计算器 下
											{
											x+=PARA_COL_WIDE;y=PARA_START_Y;
											GLCD_SetWindow_Fill( x, y, x+tx_wide, y+(gap*4-10), TEXT_TAB_BACK_COLOR, TEXT_TAB_BACK_COLOR);//clear text win
											Printf24("Plat-bawah:",x,y,BLACK_COLOR,1,back_color);y+=gap;
											Printf24("Off gas da: ",x,y,BLACK_COLOR,1,back_color);y+=gap;
											ParameterPage1_dis(7, 0);
											switch(MotorType)
												{
												case MOTOR_FREQ_5_SPD_RST:
												case MOTOR_FREQ_3_SPD:
												case MOTOR_FREQ_3_SPD_RST:
													Printf24("Set-IR: ",x,y,BLACK_COLOR,1,back_color);
													ParameterPage1_dis(9, 0);
														break;
												// // case MOTOR_DC_SERVO:
												// // case MOTOR_DC670_SERVO:
													// // Printf24("Tercepat:",x,y,BLACK_COLOR,1,back_color);y+=gap;
													// // Printf24("Jog-kecep:",x,y,BLACK_COLOR,1,back_color);
													// // // ParameterPage1_dis(11, 0);
														// // break;
												case MOTOR_AC_SERVO:
												case MOTOR_AC_SERVO_REV:
												case MOTOR_AC_A6_SERVO:
													Printf24("Kecepa-lari:",x,y,BLACK_COLOR,1,back_color);y+=gap;
													Printf24("Set-IR: ",x,y,BLACK_COLOR,1,back_color);
													ParameterPage1_dis(10, 0);
														break;
												}
											}
										x=PROG_X,y=PROG_Y;back_color=STEP_BACK_COLOR;
										GLCD_SetWindow_Fill( x, y, x+100, y+24, back_color,back_color);//clear text win
										Printf16("Program",x,y,BLACK_COLOR,1,back_color);
										x=STEP_X;//
										GLCD_SetWindow_Fill( x, y, x+100, y+24, back_color,back_color);//clear text win
										Printf16("Langkah",x,y,BLACK_COLOR,1,back_color);
										break;	
									case PORTUGAL:	//葡萄牙
										x=PARA_START_X1,y=PARA_START_Y,gap=PARA_ROW_GAP;//back_color=TEXT_TAB_BACK_COLOR;//0xef9f;
										Printf24("O ex-limite:",x,y,BLACK_COLOR,1,back_color);y+=gap;
										Printf24("Intermedi:",x,y,BLACK_COLOR,1,back_color);y+=gap;
										Printf24("apó        ",x,y,BLACK_COLOR,1,back_color);
										Printf24("   s-limite:",x,y,BLACK_COLOR,0,back_color);y+=gap;
										Printf24("lí    ",x,y,BLACK_COLOR,1,back_color); 
										Printf24("  ngua:",x,y,BLACK_COLOR,0,back_color);  y+=gap;
										Printf24("unidade:",x,y,BLACK_COLOR,1,back_color);  y+=gap;
										Printf24("antes:",x,y,BLACK_COLOR,1,back_color);y+=gap;
										Printf24("distancia:",x,y,BLACK_COLOR,1,back_color);
										if(ButtonTouch_mode==0)  //	 非 触摸计算器 下
											{
											x+=PARA_COL_WIDE;y=PARA_START_Y;
											GLCD_SetWindow_Fill( x, y, x+tx_wide, y+(gap*4-10), TEXT_TAB_BACK_COLOR, TEXT_TAB_BACK_COLOR);//clear text win
											Printf24("encerra:",x,y,BLACK_COLOR,1,back_color);y+=gap;
											Printf24("Off Air:",x,y,BLACK_COLOR,1,back_color);y+=gap;
											ParameterPage1_dis(7, 0);
											switch(MotorType)
												{
												case MOTOR_FREQ_5_SPD_RST:
												case MOTOR_FREQ_3_SPD:
												case MOTOR_FREQ_3_SPD_RST:
													Printf24("estado IR:",x,y,BLACK_COLOR,1,back_color);
													ParameterPage1_dis(9, 0);
														break;
												// // case MOTOR_DC_SERVO:
												// // case MOTOR_DC670_SERVO:
													// // Printf24("Veloci-má  ",x,y,BLACK_COLOR,1,back_color);
													// // Printf24("          x:",x,y,BLACK_COLOR,0,back_color);y+=gap;
													// // Printf24("Veloci-Jog:",x,y,BLACK_COLOR,1,back_color);
													// // // ParameterPage1_dis(11, 0);
														// // break;
												case MOTOR_AC_SERVO:
												case MOTOR_AC_SERVO_REV:
												case MOTOR_AC_A6_SERVO:
													Printf16("Veloci-corrida:",x,y,BLACK_COLOR,1,back_color);y+=gap;
													Printf24("estado IR:",x,y,BLACK_COLOR,1,back_color);
													ParameterPage1_dis(10, 0);
														break;
												}
											}
										x=PROG_X,y=PROG_Y;back_color=STEP_BACK_COLOR;
										GLCD_SetWindow_Fill( x, y, x+100, y+24, back_color,back_color);//clear text win
										Printf16("Programa",x,y,BLACK_COLOR,1,back_color);
										x=STEP_X;//
										GLCD_SetWindow_Fill( x, y, x+100, y+24, back_color,back_color);//clear text win
										Printf16(" Passo ",x,y,BLACK_COLOR,1,back_color);
										break;	
									case SPANISH: //西班牙
										x=PARA_START_X1,y=PARA_START_Y,gap=PARA_ROW_GAP;
										Printf24("lí      ",x,y,BLACK_COLOR,1,back_color);//límite
										Printf24("  mite ex:",x,y,BLACK_COLOR,0,back_color);y+=gap;
										Printf24("lí      ",x,y,BLACK_COLOR,1,back_color);//límite
										Printf24("  mite Medio:",x,y,BLACK_COLOR,0,back_color);y+=gap;
										Printf24("Tras el lí",x,y,BLACK_COLOR,1,back_color);//límite
										Printf24("          m",x,y,BLACK_COLOR,0,back_color);y+=gap;
										Printf24("idioma",x,y,BLACK_COLOR,1,back_color); 
										y+=gap;
										Printf24("unidad:",x,y,BLACK_COLOR,1,back_color);  y+=gap;
										Printf24("avanzar:",x,y,BLACK_COLOR,1,back_color);y+=gap;
										//Printf24("标准距离:   ",x,y,BLACK_COLOR,1,back_color);
										Printf24("distancia:",x,y,BLACK_COLOR,1,back_color);
										if(ButtonTouch_mode==0)  //	 非 触摸计算器 下
											{
											x+=PARA_COL_WIDE;y=PARA_START_Y;
											GLCD_SetWindow_Fill( x, y, x+tx_wide, y+(gap*4-10), TEXT_TAB_BACK_COLOR, TEXT_TAB_BACK_COLOR);//clear text win
											Printf24("cierre:",x,y,BLACK_COLOR,1,back_color);y+=gap;
											Printf24("Off Air:",x,y,BLACK_COLOR,1,back_color);y+=gap;
											ParameterPage1_dis(7, 0);
											switch(MotorType)
												{
												case MOTOR_FREQ_5_SPD_RST:
												case MOTOR_FREQ_3_SPD:
												case MOTOR_FREQ_3_SPD_RST:
													Printf24("estado IR:",x,y,BLACK_COLOR,1,back_color);
													ParameterPage1_dis(9, 0);
														break;
												// // case MOTOR_DC_SERVO:
												// // case MOTOR_DC670_SERVO:
													// // Printf24("Veloci-má  ",x,y,BLACK_COLOR,1,back_color);
													// // Printf24("          x:",x,y,BLACK_COLOR,0,back_color);y+=gap;
													// // Printf24("Veloci-Jog:",x,y,BLACK_COLOR,1,back_color);
													// // // ParameterPage1_dis(11, 0);
														// // break;
												case MOTOR_AC_SERVO:
												case MOTOR_AC_SERVO_REV:
												case MOTOR_AC_A6_SERVO:
													Printf16("Veloci-corrida:",x,y,BLACK_COLOR,1,back_color);y+=gap;
													Printf24("estado IR:",x,y,BLACK_COLOR,1,back_color);
													ParameterPage1_dis(10, 0);
														break;
												}
											}
										x=PROG_X,y=PROG_Y;back_color=STEP_BACK_COLOR;
										GLCD_SetWindow_Fill( x, y, x+100, y+24, back_color,back_color);//clear text win
										Printf16("Programa",x,y,BLACK_COLOR,1,back_color);
										x=STEP_X;//
										GLCD_SetWindow_Fill( x, y, x+100, y+24, back_color,back_color);//clear text win
										Printf16(" Paso ",x,y,BLACK_COLOR,1,back_color);
										break;	
									}
								ParameterPage1_dis(Para_sel, 1);
								if(ButtonTouch_mode==TOU_MODE_CALC)  //	  触摸计算器 下
									{
									Button_dis(BUTT_INSERT, 1); //触摸 按钮 显示
									Button_dis(BUTT_EXIT, 0); //触摸 按钮 显示
									Button_dis(BUTT_ENTER, 0); //触摸 按钮 显示
									}
								//.........................解释 框
								ModeName_dis(WorkMode);	
								CursorSizeName();	//标称尺寸
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
								ParameterPage1_dis(0, 0);
								ParameterPage1_dis(1, 0);
								ParameterPage1_dis(2, 0);
								ParameterPage1_dis(5, 0);
								ParameterPage1_dis(6, 0);
								if(ButtonTouch_mode==0)  //	 非 触摸计算器 下
									{
									ParameterPage1_dis(8, 0);
									if(MotorType>=MOTOR_AC_SERVO)
										{
										ParameterPage1_dis(9, 0);
										}
									}
									
								ParameterPage1_dis(Para_sel, 1);	
								SaveUnit();	
								break;
							case 7:  //压纸 停机
								if(PressValid_flag==0)
									PressValid_flag=1;
								else 
									PressValid_flag=0;
								if(ButtonTouch_mode==0)  //	  !触摸计算器 下
									ParameterPage1_dis(Para_sel, 1);	
								SavePressValid_flag();	
								break;
							case 9:
								if(MotorType<MOTOR_AC_SERVO)	//(MotorType<MOTOR_DC_SERVO)
									{
									if(IR_SensorStus==0)
										IR_SensorStus=1;
									else
										IR_SensorStus=0;
									if(ButtonTouch_mode==0)  //	  !触摸计算器 下
										ParameterPage1_dis(Para_sel, 1);	
									SaveIRValidStatus();
									}
								break;
							case 10:
								if(MotorType>=MOTOR_AC_SERVO)
									{
									if(IR_SensorStus==0)
										IR_SensorStus=1;
									else
										IR_SensorStus=0;
									if(ButtonTouch_mode==0)  //	  !触摸计算器 下
										ParameterPage1_dis(Para_sel, 1);	
									SaveIRValidStatus();	
									}
								break;	
								/***
							case 11:
								if((MotorType<MOTOR_AC_SERVO)&&(MotorType>MOTOR_FREQ_3_SPD_RST))
									{
									if(IR_SensorStus==0)
										IR_SensorStus=1;
									else
										IR_SensorStus=0;
									if(ButtonTouch_mode==0)  //	  !触摸计算器 下
										ParameterPage1_dis(Para_sel, 1);	
									SaveIRValidStatus();	
									}
								break;	
								***/
							}
						}
					else	//page 2
						{
						switch(Para2_sel)
							{
							case 2:	//红外切换工作模式标记
								if(IRChgWorkmodeValid_flag!=0)
									IRChgWorkmodeValid_flag=0;
								else
									IRChgWorkmodeValid_flag=1;
								SaveIRChgWorkmodeValid();
								ParameterPage2_dis(Para2_sel, 1);	
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
				case TEACH_MODE://示教画面下
				case AUTO_MODE://自动主画面下
				// case SELF_CUT_MODE://自刀主画面下
					DeleteAllData_hintWind();	//删除所有数据  提示框
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
							if(num_cou>0)	
								{
								if(num_cou<8)
									{
									if(CheckInputNums()==1)// 输入 有效
										{
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
												// // case MOTOR_DC_SERVO:
												// // case MOTOR_DC670_SERVO:
													 // // ServoSendCou=0;
													 // // DcServoStartRun_exec(TargetSize);
													// // // SelfLockEn_flag=0;
														// // break;
												case MOTOR_AC_SERVO:
												case MOTOR_AC_SERVO_REV:
												case MOTOR_AC_A6_SERVO:
													 ACMotorRunStart(TargetSize);
													// SelfLockEn_flag=0;
														break;		
												}
											Run_flag=1;
											RunStop_flag=0;
											InTargetPosit_flag=0;	//目标位置
											OneCutRoutine_flag=0; // 清 裁切 循环标志
											AutoCutStart_flag=0;
											AirOffOK_flag=0;
											PressUp_flag=0;
											PressDown_flag=0;
											PromptNum_dis();
											}
										}
									else  //无效
										{
										ClrInput_function();//清零 输入框
										}
									ClearCalculatorInput(); //清零计算器 输入	
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
											// // case MOTOR_DC_SERVO:
											// // case MOTOR_DC670_SERVO:
												 // // ServoSendCou=0;
												 // // DcServoStartRun_exec(TargetSize);
												// // // SelfLockEn_flag=0;
													// // break;
											case MOTOR_AC_SERVO:
											case MOTOR_AC_SERVO_REV:
											case MOTOR_AC_A6_SERVO:
												 ACMotorRunStart(TargetSize);
													break;		
											}
										Run_flag=1;
										RunStop_flag=0;
										InTargetPosit_flag=0;	//目标位置
										OneCutRoutine_flag=0; // 清 裁切 循环标志
										AutoCutStart_flag=0;
										AirOffOK_flag=0;
										PressUp_flag=0;
										PressDown_flag=0;
										PromptNum_dis();
										}
									}
								}
							else
								{
								//ClrInput_function();//清零 输入框
								//CheckInputNums();
								}
								
							break;
					case SELF_CUT_MODE://自刀 主画面下
					//case TEACH_MODE://示教画面下
						OneCutRoutine_flag=0; // 清 裁切 循环标志
						AutoRun_start();   //运行至 光标处
							break;
					case TEACH_MODE://示教 模式
					// case AUTO_MODE://自动  主画面下 20180831
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
											GLCD_SetWindow_Fill( SIZE_WINDOW_X, SIZE_WINDOW_Y, SIZE_WINDOW_X+SIZE_WINDOW_WIDE, SIZE_WINDOW_Y+SIZE_WINDOW_HIGH, 0xfffff, 0xffff);//尺寸输入框
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
													case INDONSIA:	//印尼
															Printf16("Input data melebihi batas",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,RED_COLOR,0,0xffff);
															break;
													case PORTUGAL:	//葡萄牙
															Printf16("Dados de entrada excede o limite",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,RED_COLOR,0,0xffff);
															break;
													case SPANISH: //西班牙
															Printf16("Los datos de entrada excede el límite",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,RED_COLOR,0,0xffff);
															break;
													}
											if(ButtonTouch_mode==TOU_MODE_CALC)   //触摸下
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
										GLCD_SetWindow_Fill( SIZE_WINDOW_X, SIZE_WINDOW_Y, SIZE_WINDOW_X+SIZE_WINDOW_WIDE, SIZE_WINDOW_Y+SIZE_WINDOW_HIGH, 0xfffff, 0xffff);//尺寸输入框
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
											case INDONSIA:	//印尼
													Printf16("Input data melebihi batas",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,RED_COLOR,0,0xffff);
															break;
											case PORTUGAL:	//葡萄牙
													Printf16("Dados de entrada excede o limite",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,RED_COLOR,0,0xffff);
													break;
											case SPANISH: //西班牙
													Printf16("Los datos de entrada excede el límite",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,RED_COLOR,0,0xffff);
													break;
											}
										if(ButtonTouch_mode==TOU_MODE_CALC)   //触摸下
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
										TargetSize_temp=TargetSize;
										if(TargetSize!=CurrentSize)  //-------------运行
										//if(1)
											{
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
												// // case MOTOR_DC_SERVO:
												// // case MOTOR_DC670_SERVO:
													// // ServoSendCou=0;
													 // // DcServoStartRun_exec(TargetSize);
													// // // SelfLockEn_flag=0;
														// // break;
												case MOTOR_AC_SERVO:
												case MOTOR_AC_SERVO_REV:
												case MOTOR_AC_A6_SERVO:
													ACMotorRunStart(TargetSize);
														break;		
												}
											Run_flag=1;
											RunStop_flag=0;
											AutoCutStart_flag=0;
											InTargetPosit_flag=0;	//目标位置
											OneCutRoutine_flag=0; // 清 裁切 循环标志
											AutoCutStart_flag=0;
											AirOffOK_flag=0;
											PressUp_flag=0;
											PressDown_flag=0;
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
										if(ButtonTouch_mode==0)  //	 非 触摸计算器 下
											num_cou=8;
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
										if(InputSize!=CurrentSize)
											{
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
												// // case MOTOR_DC_SERVO:
												// // case MOTOR_DC670_SERVO:
													 // // ServoSendCou=0;
													 // // DcServoStartRun_exec(TargetSize);
													// // // SelfLockEn_flag=0;
														// // break;
												case MOTOR_AC_SERVO:
												case MOTOR_AC_SERVO_REV:
												case MOTOR_AC_A6_SERVO:
													 ACMotorRunStart(TargetSize);
													// SelfLockEn_flag=0;
														break;		
												}
											Run_flag=1;
											RunStop_flag=0;
											InTargetPosit_flag=0;	//目标位置
											OneCutRoutine_flag=0; // 清 裁切 循环标志
											AutoCutStart_flag=0;
											AirOffOK_flag=0;
											PressUp_flag=0;
											PressDown_flag=0;
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
											// // case MOTOR_DC_SERVO:
											// // case MOTOR_DC670_SERVO:
												 // // ServoSendCou=0;
												 // // DcServoStartRun_exec(TargetSize);
												// // // SelfLockEn_flag=0;
													// // break;
											case MOTOR_AC_SERVO:
											case MOTOR_AC_SERVO_REV:
											case MOTOR_AC_A6_SERVO:
												 ACMotorRunStart(TargetSize);
													break;		
											}
										Run_flag=1;
										RunStop_flag=0;
										InTargetPosit_flag=0;	//目标位置
										OneCutRoutine_flag=0; // 清 裁切 循环标志
										AutoCutStart_flag=0;
										AirOffOK_flag=0;
										PressUp_flag=0;
										PressDown_flag=0;
										PromptNum_dis();
										}
									}
								}
							else
								{
								OneCutRoutine_flag=0; // 清 裁切 循环标志
								AutoRun_start();   //运行至 光标处
								}
							}
							break;
					case AUTO_MODE://自动  主画面下
						if(num_cou>0)
							{
							ClearCalculatorInput(); //清零计算器 输入
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
					if(Board_TestMod==0)  
						{
						if((StartCheck_mode==4)||(StartCheck_mode==5))    //-------------4: 后极限ok 进入---------5: only后极限异常进入
							{
							if(PassCodeEn_flag==0)
								{
								CurrentArea_recover2(START_PROMPT_X2, START_PROMPT_Y2, START_PROM_WIDE, START_PROM_HIGH);
								switch(Language)
									{
									case CHN_HAN:
											Printf24("运行....",RUN_DIS_X,RUN_DIS_Y,RED_COLOR,1,0xffff);
												break;
									case ENGLISH:
											Printf24("Runing....",RUN_DIS_X,RUN_DIS_Y,RED_COLOR,1,0xffff);
												break;
									case INDONSIA:	//印尼		
											Printf24("Menjalankan....",RUN_DIS_X,RUN_DIS_Y,RED_COLOR,1,0xffff);
												break;
									case PORTUGAL:	//葡萄牙	
											Printf24("Motor funcionando....",RUN_DIS_X,RUN_DIS_Y,RED_COLOR,1,0xffff);
												break;
									case SPANISH: //西班牙
											Printf24("Motor en marcha....",RUN_DIS_X,RUN_DIS_Y,RED_COLOR,1,0xffff);
												break;
									}
								CodeSensorTime_AB=0;
								MoveSpeed=2;
								SetMotorSpeed(MoveSpeed);//中高速
								//////////////
								if(StartCheck_mode==4) //-------------4: 后极限ok 进入
									{
									StartCheck_mode=9;
									MoveBack(); //后退>>>>
									}
								else				//---------5: only后极限异常进入
									{
									StartCheck_mode=6;
									MoveForward(); //前进<<<<
									}
								}
							else   //密码 启动
								{
								if(PassCheckDis_flag==0) //密码提示 ------显示
									{
									PassCheckDis_flag=1;
									GLCD_SetWindow_Fill(PASSCODE_X,PASSCODE_Y ,PASSCODE_X+500,PASSCODE_Y+24, 0xffff,0xffff);
									switch(Language)
										{
										case CHN_HAN:
												Printf24("有效使用时间到，请输入密码！",PASSCODE_X,PASSCODE_Y,RED_COLOR,1,0xffff);
													break;
										case ENGLISH:
												Printf24("Your hour is up,enter passcode",PASSCODE_X,PASSCODE_Y,RED_COLOR,1,0xffff);
													break;
										case INDONSIA:	//印尼
												Printf24("Gunakan waktu untuk,Masukkan sandi Anda",PASSCODE_X,PASSCODE_Y,RED_COLOR,1,0xffff);
													break;	
										case PORTUGAL:	//葡萄牙	
												Printf24("Use o tempo para digitar a senha",PASSCODE_X,PASSCODE_Y,RED_COLOR,1,0xffff);
													break;		
										}
									PassCheck_dis(PASS_HINT_X,PASS_HINT_Y);
									GLCD_SetWindow_Fill(PASSCODE_INPUT_X, PASSCODE_INPUT_Y, PASSCODE_INPUT_X+100, PASSCODE_INPUT_Y+30, 0xfffff, 0xffff);
									}
								}
							}
						}
						break;
				// // case MOTOR_DC_SERVO:
				// // case MOTOR_DC670_SERVO:
					// // if(StartCheck_mode==1)
						// // {
						// // if(Board_TestMod==0)       //-----
							// // {
							// // if(PassCodeEn_flag==0)
								// // {
								// // CurrentSize=OriginalSize;
								// // //if(SearchZero_flag==0)   //未归0
									// // ServoSetCommd(SERVO_COMMD_R,STAT_30H,CurrentSize);  //启动寻零
								// // CurrentArea_recover2(START_PROMPT_X2, START_PROMPT_Y2, START_PROM_WIDE, START_PROM_HIGH);
								// // switch(Language)
									// // {
									// // case CHN_HAN:
											// // Printf24("运行....",RUN_DIS_X,RUN_DIS_Y,RED_COLOR,1,0xffff);
												// // break;
									// // case ENGLISH:
											// // Printf24("Runing....",RUN_DIS_X,RUN_DIS_Y,RED_COLOR,1,0xffff);
												// // break;
									// // case INDONSIA:	//印尼		
											// // Printf24("Menjalankan....",RUN_DIS_X,RUN_DIS_Y,RED_COLOR,1,0xffff);
												// // break;
									// // case PORTUGAL:	//葡萄牙	
											// // Printf24("Motor funcionando....",RUN_DIS_X,RUN_DIS_Y,RED_COLOR,1,0xffff);
												// // break;
									// // }
								// // StartCheck_mode++;
								// // }
							// // else   //密码 启动
								// // {
								// // if(PassCheckDis_flag==0) //密码提示 ------显示
									// // {
									// // PassCheckDis_flag=1;
									// // GLCD_SetWindow_Fill(PASSCODE_X,PASSCODE_Y ,PASSCODE_X+500,PASSCODE_Y+24, 0xffff,0xffff);
									// // switch(Language)
										// // {
										// // case CHN_HAN:
												// // Printf24("有效使用时间到，请输入密码！",PASSCODE_X,PASSCODE_Y,RED_COLOR,1,0xffff);
													// // break;
										// // case ENGLISH:
												// // Printf24("Your hour is up,enter passcode",PASSCODE_X,PASSCODE_Y,RED_COLOR,1,0xffff);
													// // break;
										// // case INDONSIA:	//印尼
												// // Printf24("Gunakan waktu untuk,Masukkan sandi Anda",PASSCODE_X,PASSCODE_Y,RED_COLOR,1,0xffff);
													// // break;	
										// // case PORTUGAL:	//葡萄牙	
												// // Printf24("Use o tempo para digitar a senha",PASSCODE_X,PASSCODE_Y,RED_COLOR,1,0xffff);
													// // break;	
										// // }
									// // PassCheck_dis(PASS_HINT_X,PASS_HINT_Y);
									// // GLCD_SetWindow_Fill(PASSCODE_INPUT_X, PASSCODE_INPUT_Y, PASSCODE_INPUT_X+100, PASSCODE_INPUT_Y+30, 0xfffff, 0xffff);
									// // }
								// // }
							// // }
						// // }
						// // break;
				case MOTOR_AC_SERVO:
				case MOTOR_AC_SERVO_REV:
				case MOTOR_AC_A6_SERVO:
					if(Board_TestMod==0)  
						{     
						if((StartCheck_mode==4)||(StartCheck_mode==5))    //-------------4: 后极限ok 进入---------5: only后极限异常进入
							{
							if(PassCodeEn_flag==0)
								{
								CurrentArea_recover2(START_PROMPT_X2, START_PROMPT_Y2, START_PROM_WIDE, START_PROM_HIGH);
								switch(Language)
									{
									case CHN_HAN:
											Printf24("运行....",RUN_DIS_X,RUN_DIS_Y,RED_COLOR,1,0xffff);
												break;
									case ENGLISH:
											Printf24("Runing....",RUN_DIS_X,RUN_DIS_Y,RED_COLOR,1,0xffff);
												break;
									case INDONSIA:	//印尼		
											Printf24("Menjalankan....",RUN_DIS_X,RUN_DIS_Y,RED_COLOR,1,0xffff);
												break;
									case PORTUGAL:	//葡萄牙	
											Printf24("Motor funcionando....",RUN_DIS_X,RUN_DIS_Y,RED_COLOR,1,0xffff);
												break;
									}
								//////////////
								if(MotorType<MOTOR_AC_A6_SERVO)
									{
									if(StartCheck_mode==4) //-------------4: 后极限ok 进入
										{
										StartCheck_mode=9;
										ACServoMoveBack_MID_SPD();  //交流伺服  中速后退>>>>
										}
									else				//---------5: only后极限异常进入
										{
										StartCheck_mode=6;
										ACServoMoveFwd_MID_SPD();  //交流伺服  中速前进<<<<
										}
									}
								else
									{
									StartCheck_mode	=13;//直接进入工作界面---------20171123
									}
								}
							else   //密码 启动
								{
								if(PassCheckDis_flag==0) //密码提示 ------显示
									{
									PassCheckDis_flag=1;
									GLCD_SetWindow_Fill(PASSCODE_X,PASSCODE_Y ,PASSCODE_X+500,PASSCODE_Y+24, 0xffff,0xffff);
									switch(Language)
										{
										case CHN_HAN:
												Printf24("有效使用时间到，请输入密码！",PASSCODE_X,PASSCODE_Y,RED_COLOR,1,0xffff);
													break;
										case ENGLISH:
												Printf24("Your hour is up,enter passcode",PASSCODE_X,PASSCODE_Y,RED_COLOR,1,0xffff);
													break;
										case INDONSIA:	//印尼
												Printf24("Gunakan waktu untuk,Masukkan sandi Anda",PASSCODE_X,PASSCODE_Y,RED_COLOR,1,0xffff);
													break;	
										case PORTUGAL:	//葡萄牙	
												Printf24("Use o tempo para digitar a senha",PASSCODE_X,PASSCODE_Y,RED_COLOR,1,0xffff);
													break;	
										}
									PassCheck_dis(PASS_HINT_X,PASS_HINT_Y);
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
					// // case PROG_MODE://编程画面下
					case TEACH_MODE://示教画面下
					case AUTO_MODE://自动主画面下
					case SELF_CUT_MODE://自刀主画面下
					// // case PROG_FLAG_MODE:	//标记 模式.........
						if(Sign_flag==0)
							{
							if(num_cou>0)
							  {
							  if(CheckInputNums()==1)// 输入 有效
								 {
								 RenewModifyDate();	//更新时间信息-.-.-.-.-.-.-.-.-.-.-.-.-.-
								 //----保存数据----------------
								 if(Knife_order>OnePro_head.pro_knifeSUM)//更新步骤 总刀数
									{
									OnePro_head.pro_knifeSUM=Knife_order;
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
										OneKnife_data.k_flag&=0xf0;//清除 刀 标志
										Flg_chg=1;
										flag_now=OneKnife_data.k_flag;	//当前标记 暂存
										}
									}
								 SaveOneKnife_datas(Pro_data.pro_num, Knife_order , pKnife_data);//保存一刀数据
								 if(Knife_order<OnePro_head.pro_knifeSUM)// 不是最后一刀
									{
									GetOneKnife_datas(Pro_data.pro_num, Knife_order+1, pKnife_data);// 下一刀 数据
									 if((OneKnife_data.k_flag&0xf)==KNIFE_FLAG) //刀 标志
										{
										if(OneKnife_data.size>InputSize)
											{
											OneKnife_data.k_flag&=0xf0;	//清除 刀 标志
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
								 if(Knife_order<MAX_Knife)            //刀序递增
									{
									// if((WorkMode==PROG_MODE)||(WorkMode==TEACH_MODE))
										// {
										Knife_order++;
										StepNum_dis(OnePro_head.pro_knifeSUM,Knife_order);//步骤更新
										if(cursor_row<(PageKf_Size-1))
											{
											CursorKnife_dis(cursor_row, 0);//红色光标消失
											OneKnifeDataSel_dis(Knife_order-1, cursor_row,0);  //一刀数据 高亮显示
											cursor_row++;
											CursorKnife_dis(cursor_row, 1);//红色光标下移显示
											OneKnifeDataSel_dis(Knife_order, cursor_row,RED_COLOR);  //一刀数据 高亮显示
												switch(Flg_chg)
													{
													case 1:
														AllFlagPic_dis(cursor_row-1,flag_now); // 标记图片 显示
														break;
													case 2:
														AllFlagPic_dis(cursor_row,OneKnife_data.k_flag); //光标处 标记图片 显示
														break;
													case 3:
														AllFlagPic_dis(cursor_row-1,flag_now); // 标记图片 显示
														AllFlagPic_dis(cursor_row,OneKnife_data.k_flag); //光标处 标记图片 显示
														break;
													}
											}
										else   //页底
											{
											Size_1page_dis(Knife_order-(PageKf_Size-1),0);//一页尺寸显示
											}
										// }
									// else
										// {
										// StepNum_dis(OnePro_head.pro_knifeSUM,Knife_order);//步骤更新
										// KnifeSize_dis(cursor_row,InputSize,RED_COLOR);//尺寸
										// if((ButtonTouch_mode==0)||(ButtonTouch_mode==TOU_MODE_F4)) //----非 触摸计算器-更新标记
											// {
											// switch(Flg_chg)
												// {
												// case 1:
													// AllFlagPic_dis(cursor_row,flag_now); // 标记图片 显示
													// break;
												// case 2:
													// AllFlagPic_dis(cursor_row+1,OneKnife_data.k_flag); //光标处 标记图片 显示
													// break;
												// case 3:
													// AllFlagPic_dis(cursor_row,flag_now); // 标记图片 显示
													// AllFlagPic_dis(cursor_row+1,OneKnife_data.k_flag); //光标处 标记图片 显示
													// break;
												// }
											// }
										// }
									}
								else
									{
									OneKnifeDataSel_dis(Knife_order, cursor_row,RED_COLOR);  //一刀数据 高亮显示
										if(Flg_chg==1)
											{
											AllFlagPic_dis(cursor_row,flag_now); //光标处  标记图片 显示
											}
									}
								 }
								// ClrInput_function();//清零 输入框
								ClearCalculatorInput(); //清零计算器 输入
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
					case AUTO_LABEL_MODE:		//标签 模式**********************************
						if(num_cou>0)
						   {
						   LabelEnter_exec();//标签 三组 数据设定确认
						   }  
						else
						   {
						   if((Total_size*Label_size*Waste_size)!=0)//设定有效
								{
									WorkMode=AUTO_MODE;         //------------------退出返回到主 画面 
									CurrentArea_recover2(MIDDLE_PAGE_X , MIDDLE_PAGE_Y,  M_PAGE_WIDE, M_PAGE_HIGH);
									//ClrSizeTable_dis();//刀数据 列表空白
									SubModeIcon_dis(WorkMode);   //模式name
									Label_function();
									PorgSet_sel=0;
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
									WorkMode=TEACH_MODE;         //------------------退出返回到示教主 画面 
									PaperCutEnb_signal=1;
									CurrentArea_recover2(MIDDLE_PAGE_X , MIDDLE_PAGE_Y,  M_PAGE_WIDE, M_PAGE_HIGH);
									SubModeIcon_dis(WorkMode);   //示教
									Label_function();
									PorgSet_sel=0;
								}
							} 
						   break;		   
					case AUTO_DIVIDE_MODE:	//等分模式***************************************	
						if(num_cou>0)
						   {
						   DivideEnter_exec();//等分 数据设定确认
						   }
						else
						   {
						   if((Total_size*Divide_num)!=0)//设定等分有效
								{
									WorkMode=AUTO_MODE;           //------------------退出返回到主 画面
									CurrentArea_recover2(MIDDLE_PAGE_X , MIDDLE_PAGE_Y,  M_PAGE_WIDE, M_PAGE_HIGH);
									SubModeIcon_dis(WorkMode);   //编程模式name
									Divide_function();//
									PorgSet_sel=0;
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
									WorkMode=TEACH_MODE;           //------------------退出返回到示教主 画面
									PaperCutEnb_signal=1;
									CurrentArea_recover2(MIDDLE_PAGE_X , MIDDLE_PAGE_Y,  M_PAGE_WIDE, M_PAGE_HIGH);
									SubModeIcon_dis(WorkMode);   //示教
									Divide_function();//
									PorgSet_sel=0;
								}
						   }
						   break;		   
					case READ_PRO_MODE:	//程序选择*****************************	   
						if(num_cou>0)
							{
							  ProEnter_exec();//程序选择 输入确认
							}
						else
							{
							 if((prog_order>0)&&(prog_order<=MAX_PROG))// 有效  更新一个程序，并显示--------------------
								{
									cursor_pro=0;  
									//----------返回编程画面
									WorkMode=AUTO_MODE; 
									ExportOnePro_dis(prog_order);  //更新一个 程序 
									//PaperCutEnb_signal=1;
								}
							}	
							break;
					
					case READ_PRO_MESS_MODE: //程序信息模式
					// // case TEACH_PRO_MESS_MODE: //程序信息模式
						if(EnterInput_exec(cursor_pro, prog_order)==1)		//输入 确定	
							{
							SubModeIcon_dis(WorkMode);   //程序选择模式
							if(Pro_data.pro_num==ProNumGroup[prog_order])	//更新当前程序名
								{
								GetPro_headInfo(Pro_data.pro_num, (pInt8U)&OnePro_head); //获取前程序 头信息
								OneProNum_dis(Pro_data.pro_num, OnePro_head);// 程序号
								}
							}
							break;
					case AUTO_PLUS_MODE:  //F5++
						if(num_cou>0)
							{
							if(Knife_order<=OnePro_head.pro_knifeSUM)
							   {
							   if(CheckInputNums()==1)
									{
									F5_AutoAdd_exec(InputSize);  
									ClearCalculatorInput(); //清零计算器 输入
									WorkMode=AUTO_MODE;
									PaperCutEnb_signal=1;
									PressCircle_mode=0;
									F5_plus_dis(0);	
									}	
							   }
							}
							break;
					case AUTO_MINUS_MODE:// F6--
						if(num_cou>0)
							{
							if(Knife_order<=OnePro_head.pro_knifeSUM)
							   {
							   if(CheckInputNums()==1)
									{
									F6_AutoSub_exec(InputSize);  //F6--  批量数据 自减
									ClearCalculatorInput(); //清零计算器 输入
									WorkMode=AUTO_MODE;//返回
									PaperCutEnb_signal=1;
									PressCircle_mode=0;
									F6_minus_dis(0);
									}
							   }
							}
							break;
					case TEACH_PLUS_MODE:  //F5++
						if(num_cou>0)
							{
							if(Knife_order<=OnePro_head.pro_knifeSUM)
							   {
							   if(CheckInputNums()==1)
									{
									F5_AutoAdd_exec(InputSize);  
									ClearCalculatorInput(); //清零计算器 输入
									WorkMode=TEACH_MODE;
									PaperCutEnb_signal=1;
									PressCircle_mode=0;
									F5_plus_dis(0);	
									}	
							   }
							}
							break;
					case TEACH_MINUS_MODE:// F6--
						if(num_cou>0)
							{
							if(Knife_order<=OnePro_head.pro_knifeSUM)
							   {
							   if(CheckInputNums()==1)
									{
									F6_AutoSub_exec(InputSize);  //F6--  批量数据 自减
									ClearCalculatorInput(); //清零计算器 输入
									WorkMode=TEACH_MODE;//返回
									PaperCutEnb_signal=1;
									PressCircle_mode=0;
									F6_minus_dis(0);
									}
							   }
							}
							break;	
					// // case AUTO_RULER_MODE://自动 基准
					// // case SELF_RULER_MODE://自刀 基准
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
									// // case MOTOR_DC_SERVO:
									// // case MOTOR_DC670_SERVO:
										// // DcServoGoTarget_flag=0;
										
										// // OriginalSize=OriginalSize+InputSize-CurrentSize;
										// // CurrentSize=InputSize;
										// // ServoSetCommd(SERVO_COMMD_P,STAT_30H,CurrentSize);
											// // break;
									case MOTOR_AC_SERVO:	
									case MOTOR_AC_SERVO_REV:	
										OriginalSize=OriginalSize+InputSize-CurrentSize;
										CurrentSize=InputSize;
											break;
									case MOTOR_AC_A6_SERVO:	
										StartInitSize=StartInitSize+InputSize-CurrentSize;
										OriginalSize=InputSize;
										SaveA6OriginalBenchMark();//A6基准 保存
											break;
									}		
								
								//if(InputSize!=TargetSize_temp)
								//	{
									SaveOriginalSize();  //保存原点尺寸
								//	}
								
								//-----------------自动返回 主模式	
								CurrentArea_recover2(MIDDLE_PAGE_X , MIDDLE_PAGE_Y,  M_PAGE_WIDE, M_PAGE_HIGH);
								// // if(WorkMode==AUTO_RULER_MODE)   //自动下
									// // {
									// // WorkMode=AUTO_MODE;//返回    自动 主模式
									// // PaperCutEnb_signal=1;
									// // PressCircle_mode=0;
									// // }
								// // else
									if(WorkMode==MANUAL_RULER_MODE)  //手动下
									{
									WorkMode=MANUAL_MODE;//返回    手动 主模式
									}
								// // else if(WorkMode==SELF_RULER_MODE)   //自刀下	
									// // {
									// // WorkMode=SELF_CUT_MODE;//返回    自刀 主模式
									// // PaperCutEnb_signal=1;
									// // }
								SubModeIcon_dis(WorkMode); //主模式icon
								PromptNum_dis();//输入范围
								PromptDis_flag=1;
								}
							ClearCalculatorInput(); //清零计算器 输入  ClrInput_function();//清零 输入框
							}
						else
							{						 
							}
							 break;
					// // case AUTO_TOOLS_MODE://自动  参数设置
					// // case SELF_TOOLS_MODE://自刀  参数设置
					case MANUAL_TOOLS_MODE:// 手动 参数模式
						if(num_cou>0)
							{
							if((CheckInputNums()==1))
								{
								if(PramSel_Page<1)	//page 1
									{
									if(Para_sel<9)
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
													ParameterPage1_dis(Para_sel++, 0);
													ParameterPage1_dis(Para_sel, 1);
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
													case INDONSIA:	//印尼
														Printf16("Input data melebihi batas",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,RED_COLOR,0,0xffff);
																break;
													case PORTUGAL:	//葡萄牙
															Printf16("Dados de entrada excede o limite",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,RED_COLOR,0,0xffff);
															break;
													case SPANISH: //西班牙
															Printf16("Los datos de entrada excede el límite",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,RED_COLOR,0,0xffff);
															break;
													}
												if(ButtonTouch_mode==TOU_MODE_CALC)   //触摸下
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
													ParameterPage1_dis(Para_sel++, 0);
													ParameterPage1_dis(Para_sel, 1);
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
													case INDONSIA:	//印尼
														Printf16("Input data melebihi batas",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,RED_COLOR,0,0xffff);
															break;
													case PORTUGAL:	//葡萄牙
															Printf16("Dados de entrada excede o limite",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,RED_COLOR,0,0xffff);
															break;												
													case SPANISH: //西班牙
															Printf16("Los datos de entrada excede el límite",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,RED_COLOR,0,0xffff);
															break;

													}
												if(ButtonTouch_mode==TOU_MODE_CALC)   //触摸下
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
													ParameterPage1_dis(Para_sel++, 0);
													ParameterPage1_dis(Para_sel, 1);
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
													case INDONSIA:	//印尼
														Printf16("Input data melebihi batas",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,RED_COLOR,0,0xffff);
															break;
													case PORTUGAL:	//葡萄牙
															Printf16("Dados de entrada excede o limite",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,RED_COLOR,0,0xffff);
															break;											
													case SPANISH: //西班牙
															Printf16("Los datos de entrada excede el límite",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,RED_COLOR,0,0xffff);
															break;
													}
												if(ButtonTouch_mode==TOU_MODE_CALC)   //触摸下
													{
													ClearCalculatorInput(); //清零计算器 输入
													num_cou=0;
													}	
												}
												break;
										case 5: //提前量
											if(MotorType<MOTOR_AC_SERVO)  //*************变频
												{
												if((input_temp>=1)&&(input_temp<=100))
													{
													Aheader=input_temp;
													SaveAheader();
													if(Para_sel<6)
														{
														ParameterPage1_dis(Para_sel++, 0);
														ParameterPage1_dis(Para_sel, 1);
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
														case INDONSIA:	//印尼
															Printf16("Input data melebihi batas",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,RED_COLOR,0,0xffff);
																break;
														case PORTUGAL:	//葡萄牙
																Printf16("Dados de entrada excede o limite",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,RED_COLOR,0,0xffff);
																break;											
														case SPANISH: //西班牙
																Printf16("Los datos de entrada excede el límite",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,RED_COLOR,0,0xffff);
																break;
														}
													if(ButtonTouch_mode==TOU_MODE_CALC)   //触摸下
														{
														ClearCalculatorInput(); //清零计算器 输入
														num_cou=0;
														}	
													}
												}
												break;	
										case 6:  //自动推纸  距离
											if(input_temp<=AUTO_PUSH_DISTAN)
												{
												AutoPushDistance=input_temp;
												SavePushDistance();
												ParameterPage1_dis(Para_sel, 1);
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
													case INDONSIA:	//印尼
														Printf16("Input data melebihi batas",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,RED_COLOR,0,0xffff);
															break;
													case PORTUGAL:	//葡萄牙
															Printf16("Dados de entrada excede o limite",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,RED_COLOR,0,0xffff);
															break;											
													case SPANISH: //西班牙
															Printf16("Los datos de entrada excede el límite",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,RED_COLOR,0,0xffff);
															break;
													}
												if(ButtonTouch_mode==TOU_MODE_CALC)   //触摸下
													{
													ClearCalculatorInput(); //清零计算器 输入
													num_cou=0;
													}	
												}	
												break;
										case 8:	//关气阀 距离
											if(input_temp<1000)
												{
												if(input_temp<100)
													AirOffDistance=0;
												else
													AirOffDistance=input_temp;
												SaveAirOffDistance();	//关气阀 距离
												if(ButtonTouch_mode==0)  //
													ParameterPage1_dis(Para_sel, 1);
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
													case INDONSIA:	//印尼
														Printf16("Input data melebihi batas",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,RED_COLOR,0,0xffff);
																break;
													case PORTUGAL:	//葡萄牙
															Printf16("Dados de entrada excede o limite",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,RED_COLOR,0,0xffff);
															break;											
													case SPANISH: //西班牙
															Printf16("Los datos de entrada excede el límite",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,RED_COLOR,0,0xffff);
															break;
													}
												if(ButtonTouch_mode==TOU_MODE_CALC)   //触摸下
													{
													ClearCalculatorInput(); //清零计算器 输入
													num_cou=0;
													}	
												}	
												break;	
										case 9:		//最大运行 速度
											// // if((MotorType==MOTOR_DC_SERVO)||(MotorType==MOTOR_DC670_SERVO))   //------------------直流  伺服
												// // {
												// // if((input_temp<=20)&&(input_temp>=13))
													// // {
													// // ServoSpeed_order=input_temp;
													// // SaveMovSpeed();
													// // ServoSetCommd(SERVO_COMMD_S,STAT_30H,SERVO_SPEED[ServoSpeed_order]);  //设定伺服最大速
													// // if(ButtonTouch_mode==TOU_MODE_CALC)   //触摸下
														// // {
														// // CalcuInClear_exec();     //清除 计算器
														// // }	
													// // ParameterPage1_dis(Para_sel, 1);
													// // }
												// // else
													// // {
													// // PromptDis_flag=0;
													// // GLCD_SetWindow_Fill( REMIND_WINDOW_X, REMIND_WINDOW_Y, REMIND_WINDOW_X+REMIND_LENGTH, REMIND_WINDOW_Y+30, 0xfffff, 0xffff);//提示框
													// // switch(Language)
														// // {
														// // case CHN_HAN:
															// // Printf24("输入数据超过极限!",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,RED_COLOR,0,0xffff);
																// // break;
														// // case ENGLISH:
															// // Printf24("Data exceeds limit!",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,RED_COLOR,0,0xffff);
																// // break;
														// // case INDONSIA:	//印尼
															// // Printf16("Input data melebihi batas",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,RED_COLOR,0,0xffff);
																// // break;
														// // case PORTUGAL:	//葡萄牙
															// // Printf16("Dados de entrada excede o limite",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,RED_COLOR,0,0xffff);
															// // break;											
														// // case SPANISH: //西班牙
															// // Printf16("Los datos de entrada excede el límite",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,RED_COLOR,0,0xffff);
															// // break;
														// // }
													// // if(ButtonTouch_mode==TOU_MODE_CALC)   //触摸下
														// // {
														// // ClearCalculatorInput(); //清零计算器 输入
														// // num_cou=0;
														// // }	
													// // }	
												// // }else 
											
											if(MotorType>=MOTOR_AC_SERVO)  //*************交流 伺服
												{
												if(input_temp<=32)
													{
													AC_MotorSPD=input_temp;
													SaveACMotorSpeed();   //交流伺服 速度
													GetAC_MotorSpeed();  //交流伺服  速度判定
													if(ButtonTouch_mode==TOU_MODE_CALC)   //触摸下
														{
														CalcuInClear_exec();     //清除 计算器
														}	
													ParameterPage1_dis(Para_sel, 1);
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
														case INDONSIA:	//印尼
															Printf16("Input data melebihi batas",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,RED_COLOR,0,0xffff);
																break;
														case PORTUGAL:	//葡萄牙
																Printf16("Dados de entrada excede o limite",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,RED_COLOR,0,0xffff);
																break;											
														case SPANISH: //西班牙
																Printf16("Los datos de entrada excede el límite",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,RED_COLOR,0,0xffff);
																break;
														}
													if(ButtonTouch_mode==TOU_MODE_CALC)   //触摸下
														{
														ClearCalculatorInput(); //清零计算器 输入
														num_cou=0;
														}	
													}
												}
											
												break;
												/****
										case 10:		//点动 速度
											if((input_temp<=20)&&(input_temp>=10))
												{
												JogSpeed_order=input_temp;
												SaveJogSpeed();
												//ServoSetCommd(SERVO_COMMD_S,STAT_30H,SERVO_SPEED[ServoSpeed_order]);  //设定伺服最大速
												if(ButtonTouch_mode==TOU_MODE_CALC)   //触摸下
													{
													CalcuInClear_exec();     //清除 计算器
													}	
												ParameterPage1_dis(Para_sel, 1);
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
													case INDONSIA:	//印尼
														Printf16("Input data melebihi batas",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,RED_COLOR,0,0xffff);
															break;
													case PORTUGAL:	//葡萄牙
														Printf16("Dados de entrada excede o limite",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,RED_COLOR,0,0xffff);
															break;											
													case SPANISH: //西班牙
														Printf16("Los datos de entrada excede el límite",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,RED_COLOR,0,0xffff);
															break;
													}
												if(ButtonTouch_mode==TOU_MODE_CALC)   //触摸下
													{
													ClearCalculatorInput(); //清零计算器 输入
													num_cou=0;
													}	
												}	
												break;		***/
										}
									}
								else	//page 2
									{
									if(Para2_sel<1)
										{
										if(Unit==UNIT_MM)
											{
											input_temp=InputSize/100*100;
											}
										else
											{
											input_temp=InputSize*2.54;
											}
										}
									else
										{
										
										}
									switch(Para2_sel)
										{
										case 0:		// 步进距离
											if((input_temp<=MAX_STEP_SIZE)&&(input_temp>=0))
												{
												Step_Size=input_temp;
												SaveStepDistance(); // 步进距离
												ParameterPage2_dis(Para2_sel++, 0);
												ParameterPage2_dis(Para2_sel, 1);
												}
												break;
										case 1://误差掩盖值
											if(MotorType<MOTOR_AC_SERVO)  //*************变频
												{
												if(Unit==UNIT_MM)
													{
													if((InputSize>=30)&&(InputSize<=100))	//	20171017屏蔽
														{
														VirtualTargetSizeGap=InputSize;
														SaveVirtualTargetSizeGap();
														ParameterPage2_dis(Para2_sel, 1);
														}
													}
												}
												break;
										}
									}
								}
							else
								num_cou=0;
							if(ButtonTouch_mode==0)  //	 非 触摸计算器 下	
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
												case INDONSIA:	//印尼
													Printf16("Input data melebihi batas",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,RED_COLOR,0,0xffff);
														break;
												case PORTUGAL:	//葡萄牙
														Printf16("Dados de entrada excede o limite",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,RED_COLOR,0,0xffff);
														break;											
												case SPANISH: //西班牙
														Printf16("Los datos de entrada excede el límite",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,RED_COLOR,0,0xffff);
														break;
												}
											if(ButtonTouch_mode==TOU_MODE_CALC)   //触摸下
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
												case INDONSIA:	//印尼
													Printf16("Input data melebihi batas",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,RED_COLOR,0,0xffff);
														break;
												case PORTUGAL:	//葡萄牙
														Printf16("Dados de entrada excede o limite",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,RED_COLOR,0,0xffff);
														break;											
												case SPANISH: //西班牙
														Printf16("Los datos de entrada excede el límite",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,RED_COLOR,0,0xffff);
														break;
												}
											if(ButtonTouch_mode==TOU_MODE_CALC)   //触摸下
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
												case INDONSIA:	//印尼
													Printf16("Input data melebihi batas",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,RED_COLOR,0,0xffff);
														break;
												case PORTUGAL:	//葡萄牙
														Printf16("Dados de entrada excede o limite",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,RED_COLOR,0,0xffff);
														break;											
												case SPANISH: //西班牙
														Printf16("Los datos de entrada excede el límite",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,RED_COLOR,0,0xffff);
														break;
												}
											if(ButtonTouch_mode==TOU_MODE_CALC)   //触摸下
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
												case INDONSIA:	//印尼
													Printf16("Input data melebihi batas",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,RED_COLOR,0,0xffff);
														break;
												case PORTUGAL:	//葡萄牙
														Printf16("Dados de entrada excede o limite",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,RED_COLOR,0,0xffff);
														break;											
												case SPANISH: //西班牙
														Printf16("Los datos de entrada excede el límite",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,RED_COLOR,0,0xffff);
														break;
												}
											if(ButtonTouch_mode==TOU_MODE_CALC)   //触摸下
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
												case INDONSIA:	//印尼
													Printf16("Input data melebihi batas",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,RED_COLOR,0,0xffff);
														break;
												case PORTUGAL:	//葡萄牙
														Printf16("Dados de entrada excede o limite",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,RED_COLOR,0,0xffff);
														break;											
												case SPANISH: //西班牙
														Printf16("Los datos de entrada excede el límite",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,RED_COLOR,0,0xffff);
														break;
												}
											if(ButtonTouch_mode==TOU_MODE_CALC)   //触摸下
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
												case INDONSIA:	//印尼
													Printf16("Input data melebihi batas",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,RED_COLOR,0,0xffff);
														break;
												case PORTUGAL:	//葡萄牙
														Printf16("Dados de entrada excede o limite",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,RED_COLOR,0,0xffff);
														break;											
												case SPANISH: //西班牙
														Printf16("Los datos de entrada excede el límite",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,RED_COLOR,0,0xffff);
														break;
												}
											if(ButtonTouch_mode==TOU_MODE_CALC)   //触摸下
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
												case INDONSIA:	//印尼
													Printf16("Input data melebihi batas",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,RED_COLOR,0,0xffff);
														break;
												case PORTUGAL:	//葡萄牙
														Printf16("Dados de entrada excede o limite",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,RED_COLOR,0,0xffff);
														break;											
												case SPANISH: //西班牙
														Printf16("Los datos de entrada excede el límite",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,RED_COLOR,0,0xffff);
														break;
												}
											if(ButtonTouch_mode==TOU_MODE_CALC)   //触摸下
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
											if(ButtonTouch_mode==TOU_MODE_CALC)   //触摸下
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
												case INDONSIA:	//印尼
													Printf16("Input data melebihi batas",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,RED_COLOR,0,0xffff);
														break;
												case PORTUGAL:	//葡萄牙
														Printf16("Dados de entrada excede o limite",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,RED_COLOR,0,0xffff);
														break;											
												case SPANISH: //西班牙
														Printf16("Los datos de entrada excede el límite",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,RED_COLOR,0,0xffff);
														break;
												}
											if(ButtonTouch_mode==TOU_MODE_CALC)   //触摸下
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
							if(ButtonTouch_mode==0)  //	 非 触摸计算器 下	
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
							ClearCalculatorInput(); //清零计算器 输入	ClrInput_function();//清零 输入框 
							}
							break;
					case MANUAL_PULSE_MODE://手动 脉冲当量  设定保存
						 if(num_cou>0)
							{
							if(CheckInputNums()==1)
								{
								if(InputSize<12)
									{
									SelPulseDegree_dis(Para_sel, 0); //脉冲设定
									Para_sel=InputSize;
									SelPulseDegree_dis(Para_sel,1);
									}
								}
							else
								num_cou=0;
							ClearCalculatorInput(); //清零计算器 输入 ClrInput_function();//清零 输入框 
							}
						 else
							{
							if(ButtonTouch_mode==0)  //	非  触摸 下
								{
								Pulse_degree=Para_sel;
								Save_degree();
								WorkMode=MANUAL_MODE;//返回    ---------手动 主模式
								Para_sel=0;
								CurrentArea_recover2(MIDDLE_PAGE_X , MIDDLE_PAGE_Y, M_PAGE_WIDE, M_PAGE_HIGH);
								SubModeIcon_dis(WorkMode);   //手动模式name
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
							ClearCalculatorInput(); //清零计算器 输入  ClrInput_function();//清零 输入框
							}
							break;
					case AUTO_TO_SELF_MODE:   //自动-->自刀过度 模式
						
						if(LastAutoKnife_order<2)    //--------首次  进入  不提示
							{
							WorkMode=SELF_CUT_MODE;  //进入   ----------自刀主 模式
							CurrentArea_recover2(SELF_PROMP_X,SELF_PROMP_Y,SELF_PROMP_WIDE,SELF_PROMP_HIGH);
							AutoCutModePage_dis(); //自刀模式 部分画面显示
							//------------返回第一刀
							// // ClrInput_function();//清零 输入框 
							CursorKnife_dis(cursor_row, 0);//红色光标消失
							cursor_row=0;
							CursorKnife_dis(cursor_row, 1);//红色光标显示
							Knife_order=1;//
							Size_1page_dis(Knife_order,0);//一页尺寸显示
							if(Knife_order<=OnePro_head.pro_knifeSUM)
								StepOrder_dis(Knife_order);//步骤更新 
							AutoCutDisable_flag=0;
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
								// // if(ButtonTouch_mode==TOU_MODE_AUTOCUT_IN) //自动-->自刀过度  	提示
									// // ButtonTouch_mode=0;
								WorkMode=SELF_CUT_MODE;  //进入   ----------自刀主 模式
								CurrentArea_recover2(SELF_PROMP_X,SELF_PROMP_Y,SELF_PROMP_WIDE,SELF_PROMP_HIGH);
								AutoCutModePage_dis(); //自刀模式 部分画面显示
								//------------返回之前刀
								Knife_order=LastAutoKnife_order;//
								// // ClrInput_function();//清零 输入框 
								CursorKnife_dis(cursor_row, 0);//红色光标消失
								cursor_row=0;
								CursorKnife_dis(cursor_row, 1);//红色光标显示
								
								Size_1page_dis(Knife_order,0);//一页尺寸显示
								if(Knife_order<=OnePro_head.pro_knifeSUM)
									StepOrder_dis(Knife_order);//步骤更新 
								LastAutoKnife_order=1;
							AutoCutDisable_flag=0;
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
								case INDONSIA:	//印尼
										Printf24("Mode Manual,tekan tombol Run",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,RED_COLOR,0,0xffff);
											break;
								case PORTUGAL:	//葡萄牙
										Printf24("Pressione a tecla Run",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,RED_COLOR,0,0xffff);
											break;
								}
							}
						
							break;
							//---------------全删 功能
					case READ_DEL_ALL_PRO_MODE://删除所有pro
					// // case TEACH_DEL_ALL_PRO_MODE://删除所有pro
						//------1
						DeleteAllExitWind();	//退出全删 提示框
						//------2
						DeleteAllProg();		//F5 删除所有程序
							break;
					case AUTO_DEL_ALL_SIZE_MODE://	删除所有尺寸
					case TEACH_DEL_ALL_SIZE_MODE://	删除所有尺寸
						//------1
						DeleteAllExitWind();	//退出全删 提示框
						//------2
						Knife_order=1;
						ClrBuf_datas(Pro_data.pro_num, Knife_order, OnePro_head.pro_knifeSUM );//清零
						SaveBuf_datas(Pro_data.pro_num, Knife_order, OnePro_head.pro_knifeSUM );//保存
						CursorKnife_dis(cursor_row, 0);//红色光标消失
						cursor_row=0;
						CursorKnife_dis(cursor_row, 1);//红色光标显示
						Size_1page_dis(Knife_order,cursor_row);//显示一页

						OnePro_head.pro_knifeSUM=1;
						SavePro_headInfo(Pro_data.pro_num, (pInt8U)&OnePro_head);//刀数 保存
						StepNum_dis(OnePro_head.pro_knifeSUM,Knife_order);//步骤更新
							break;
					}
			ClearCalculatorInput(); //清零计算器 输入20180925
			 }
		  else
			 {
									
			 }
		  }
		else
		  {
		  if(Board_TestMod==TEST_NO)
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
					 else if((StartCheck_mode==4)||(StartCheck_mode==5))
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
											GLCD_SetWindow_Fill(PASSCODE_X,PASSCODE_Y ,PASSCODE_X+500,PASSCODE_Y+24, 0xffff,0xffff);
											switch(Language)
												{
												case CHN_HAN:
															Printf24("密码输入正确！欢迎继续使用！  ",PASSCODE_X,PASSCODE_Y,RED_COLOR,1,0xffff);
																break;
												case ENGLISH:
															Printf24("Password is correct,Welcome to use!    ",PASSCODE_X,PASSCODE_Y,RED_COLOR,1,0xffff);
																break;
												case INDONSIA:	//印尼
															Printf24("Password benar! selamat datang!    ",PASSCODE_X,PASSCODE_Y,RED_COLOR,1,0xffff);
																break;
												case PORTUGAL:	//葡萄牙
															Printf24("A senha está correta! bem-vindo    ",PASSCODE_X,PASSCODE_Y,RED_COLOR,1,0xffff);
																break;
												}
											//////////////////////////////	
											CurrentArea_recover2(START_PROMPT_X2, START_PROMPT_Y2, START_PROM_WIDE, START_PROM_HIGH);
											switch(Language)
												{
												case CHN_HAN:
														Printf24("运行....",RUN_DIS_X,RUN_DIS_Y,RED_COLOR,1,0xffff);
															break;
												case ENGLISH:
														Printf24("Runing....",RUN_DIS_X,RUN_DIS_Y,RED_COLOR,1,0xffff);
															break;
												case INDONSIA:	//印尼		
														Printf24("Menjalankan....",RUN_DIS_X,RUN_DIS_Y,RED_COLOR,1,0xffff);
															break;
												case PORTUGAL:	//葡萄牙	
														Printf24("Motor funcionando....",RUN_DIS_X,RUN_DIS_Y,RED_COLOR,1,0xffff);
															break;
												}
											MoveSpeed=2;
											SetMotorSpeed(MoveSpeed);//中高速
											if(StartCheck_mode==4)//-------------4: 后极限ok 进入
												{
												MoveBack(); 	//后退>>>>
												StartCheck_mode=9;//++;
												}
											else				//---------5: only后极限异常进入
												{
												StartCheck_mode=6;
												MoveForward(); //前进<<<<
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
				// // case MOTOR_DC_SERVO:
				// // case MOTOR_DC670_SERVO:
					// // if(StartCheck_mode==1)
						 // // {
						 // // if(PassCheckDis_flag==1) //开机 密码下
							 // // {
							 // // if(num_cou>0)
								// // {
								// // if(CheckInputNums()==1)
									// // {
									// // if(StartPassInput_flag==0)
										// // {
										// // StartPassInput_flag=1;
										// // if(InputSize==PassCode)//密码正确   
											// // {
											// // PassCodeEn_flag=0;
											// // //PassCheckDis_flag=0;
											
										// // //-----------时间更新
											// // if(FirstDayValid_flag==1) //首次 时间限制 有效
												// // {
												// // FirstDayValid_flag=0;
												// // SaveFirstDays_flag(); //清除 首次有效
												// // if(SecondDayValid_flag==1) //第二次 计时开始
													// // {
													// // Start_days.year=Year;
													// // Start_days.month=Month;
													// // Start_days.day=Dom;
													// // SaveWorkDays();//起始 时间保存
													// // }
												// // }
											// // else if(SecondDayValid_flag==1)    //第二次 有效
												// // {
												// // SecondDayValid_flag=0;
												// // SaveSecondDays_flag();
												// // }
											// // //---------开机 工作
											// // GLCD_SetWindow_Fill(PASSCODE_X,PASSCODE_Y ,PASSCODE_X+500,PASSCODE_Y+24, 0xffff,0xffff);
											// // switch(Language)
												// // {
												// // case CHN_HAN:
															// // Printf24("密码输入正确！欢迎继续使用！  ",PASSCODE_X,PASSCODE_Y,RED_COLOR,1,0xffff);
																// // break;
												// // case ENGLISH:
															// // Printf24("Password is correct,Welcome to use!    ",PASSCODE_X,PASSCODE_Y,RED_COLOR,1,0xffff);
																// // break;
												// // case INDONSIA:	//印尼
															// // Printf24("Password benar! selamat datang!   ",PASSCODE_X,PASSCODE_Y,RED_COLOR,1,0xffff);
																// // break;
												// // case PORTUGAL:	//葡萄牙
															// // Printf24("A senha está correta! bem-vindo   ",PASSCODE_X,PASSCODE_Y,RED_COLOR,1,0xffff);
																// // break;
												// // }
												
											
											// // CurrentSize=OriginalSize;
											// // //if(SearchZero_flag==0)   //未归0
											// // ServoSetCommd(SERVO_COMMD_R,STAT_30H,CurrentSize);  //启动寻零
											// // CurrentArea_recover2(START_PROMPT_X2, START_PROMPT_Y2, START_PROM_WIDE, START_PROM_HIGH);
											// // switch(Language)
												// // {
												// // case CHN_HAN:
														// // Printf24("运行....",RUN_DIS_X,RUN_DIS_Y,RED_COLOR,1,0xffff);
															// // break;
												// // case ENGLISH:
														// // Printf24("Runing....",RUN_DIS_X,RUN_DIS_Y,RED_COLOR,1,0xffff);
															// // break;
												// // case INDONSIA:	//印尼		
														// // Printf24("Menjalankan....",RUN_DIS_X,RUN_DIS_Y,RED_COLOR,1,0xffff);
															// // break;
												// // case PORTUGAL:	//葡萄牙	
														// // Printf24("Motor funcionando....",RUN_DIS_X,RUN_DIS_Y,RED_COLOR,1,0xffff);
															// // break;
												// // }
											// // StartCheck_mode++;	
											// // }
										// // }
								
									// // }
								 // // for(num_cou=0;num_cou<8;num_cou++)
									// // {
									// // Size_temp[num_cou++]=0;
									// // }
								 // // num_cou=0;	
								// // }
							 // // }
						 // // }
						// // break;
				case MOTOR_AC_SERVO:
				case MOTOR_AC_SERVO_REV:
				case MOTOR_AC_A6_SERVO:
					if(StartCheck_mode==1)  //推纸器 复位启动
						{
						ACMotorGoForward();//前进
						// PusherResetTime=0;
						qianjincn=0;
						 CurrentArea_recover3(PUSH_RESET_PROMPT_X1, PUSH_RESET_PROMPT_Y1, PUSH_RESET_PROMPT_WIDE, PUSH_RESET_PROMPT_HIGH);
						 StartCheck_mode++;
						 PushRstKey_flag=1;
						}
					else if((StartCheck_mode==4)||(StartCheck_mode==5))
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
											GLCD_SetWindow_Fill(PASSCODE_X,PASSCODE_Y ,PASSCODE_X+500,PASSCODE_Y+24, 0xffff,0xffff);
											switch(Language)
												{
												case CHN_HAN:
															Printf24("密码输入正确！欢迎继续使用！  ",PASSCODE_X,PASSCODE_Y,RED_COLOR,1,0xffff);
																break;
												case ENGLISH:
															Printf24("Password is correct,Welcome to use!    ",PASSCODE_X,PASSCODE_Y,RED_COLOR,1,0xffff);
																break;
												case INDONSIA:	//印尼
															Printf24("Password benar! selamat datang!    ",PASSCODE_X,PASSCODE_Y,RED_COLOR,1,0xffff);
																break;
												case PORTUGAL:	//葡萄牙
															Printf24("A senha está correta! bem-vindo    ",PASSCODE_X,PASSCODE_Y,RED_COLOR,1,0xffff);
																break;
												}
												///////////////////////////////////////////
											CurrentArea_recover2(START_PROMPT_X2, START_PROMPT_Y2, START_PROM_WIDE, START_PROM_HIGH);
											switch(Language)
												{
												case CHN_HAN:
														Printf24("运行....",RUN_DIS_X,RUN_DIS_Y,RED_COLOR,1,0xffff);
															break;
												case ENGLISH:
														Printf24("Runing....",RUN_DIS_X,RUN_DIS_Y,RED_COLOR,1,0xffff);
															break;
												case INDONSIA:	//印尼		
														Printf24("Menjalankan....",RUN_DIS_X,RUN_DIS_Y,RED_COLOR,1,0xffff);
															break;
												case PORTUGAL:	//葡萄牙	
														Printf24("Motor funcionando....",RUN_DIS_X,RUN_DIS_Y,RED_COLOR,1,0xffff);
															break;
												}
											if(MotorType<MOTOR_AC_A6_SERVO)
												{
												if(StartCheck_mode==4) //-------------4: 后极限ok 进入
													{
													StartCheck_mode=9;
													ACServoMoveBack_MID_SPD();  //交流伺服  中速后退>>>>
													}
												else				//---------5: only后极限异常进入
													{
													StartCheck_mode=6;
													ACServoMoveFwd_MID_SPD();  //交流伺服  中速前进<<<<
													}	
												}
											else
												{
												StartCheck_mode	=13;//直接进入工作界面---------20171123
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
				}	
			 }
		  else   //if(Board_TestMod==TEST_SYS_WORD)
			 {
			 EnterSysBoardNum(); // 系统 选择模式  密码
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
				
				case TEACH_MODE://示教画面下
				case TEACH_PLUS_MODE:  //自刀F5++
				case TEACH_MINUS_MODE://自刀 F6--
				case AUTO_MODE://自动主画面下
				case AUTO_PLUS_MODE:  //F5++
				case AUTO_MINUS_MODE:// F6--
				case SELF_CUT_MODE://自刀主画面下
				case PROG_FLAG_MODE:	//标记 模式
				case TEACH_FLAG_MODE:	//标记 模式
						if((Knife_order==OnePro_head.pro_knifeSUM)&&(Knife_order==1))
							{
							pKnife_data=(pInt8U)&OneKnife_data;
							GetOneKnife_datas(Pro_data.pro_num, Knife_order, pKnife_data);//
							if((OneKnife_data.size>=Size_MIN_num)&&(OneKnife_data.size<=Size_MAX_num))
								CursorDown_inTable();//**** 光标下移 显示 数据
							}
						else
							CursorDown_inTable();//**** 光标下移 显示 数据	
						
						   break;
				case AUTO_LABEL_MODE://标签 下--------------------------
				case TEACH_LABEL_MODE://标签 下--------------------------
					 if(PorgSet_sel<2)
						{
						LabelSel_dis(PorgSet_sel,0);PorgSet_sel++;
						LabelSel_dis(PorgSet_sel,1);
						}
							break;
				case AUTO_DIVIDE_MODE://等分 下--------------------------
				case TEACH_DIVIDE_MODE://等分 下--------------------------
					 if(PorgSet_sel<1)
						{
						DivideSel_dis(PorgSet_sel,0);PorgSet_sel++;
						DivideSel_dis(PorgSet_sel,1);
						}
							break;
				case READ_PRO_MODE:    //程序选择----------------------
				// // case TEACH_PRO_MODE:    //程序选择----------------------
						  if(prog_order>=MAX_PROG)//返回第一个 pro
							  {
							  // Pro_num111=1;
							  prog_order=1;
							  CursorPro_dis(cursor_pro,0);//光标
							  cursor_pro=0;
							  CursorPro_dis(cursor_pro,1);//
							  Prog_1page_dis(prog_order, 0);//===程序---数据显示
							  OneProgHeadInfo_dis(cursor_pro ,  prog_order, 1);	//一条程序 显示1
							  }
						  else
							  {
							  prog_order++;
							  if(cursor_pro<(PROGS_1PAGE-1))
								 {
								 CursorPro_dis(cursor_pro,0);//光标
								 OneProgHeadInfo_dis(cursor_pro ,  prog_order-1, 0);	//一条程序 显示0
								 cursor_pro++;
								 CursorPro_dis(cursor_pro,1);//
								 OneProgHeadInfo_dis(cursor_pro ,  prog_order, 1);	//一条程序 显示1
								 }
							  else// 下一页
								 {
								 CursorPro_dis(cursor_pro,0);//光标
								 cursor_pro=0;
								 CursorPro_dis(cursor_pro,1);//
								 Prog_1page_dis(prog_order, 0);//===程序---数据显示
								 OneProgHeadInfo_dis(cursor_pro ,  prog_order, 1);	//一条程序 显示
								 }
							  }
						     break;
				case READ_PRO_MESS_MODE:			 
				// // case TEACH_PRO_MESS_MODE:	
						DirKeySelInput_exec(KEY_DOWN);
						
							break;
				// // case AUTO_TOOLS_MODE://  参数设置  下移
				// // case SELF_TOOLS_MODE://  参数设置  下移
				case MANUAL_TOOLS_MODE:// 手动 参数模式
					if(ButtonTouch_mode==0)  //	 非 触摸计算器 下
						{
						switch(MotorType)
							{
							case MOTOR_FREQ_5_SPD_RST:
							case MOTOR_FREQ_3_SPD:
							case MOTOR_FREQ_3_SPD_RST:
								if(PramSel_Page<1)	//page 1
									{
									if(Para_sel<9)
										{
										ParameterPage1_dis(Para_sel++, 0);
										ParameterPage1_dis(Para_sel, 1);
										}
									else
										{
										PramSel_Page++;
										ParamPage2_dis(); //参数 page2
										}
									}
								else	//page 2
									{
									if(Para2_sel<2)
										{
										ParameterPage2_dis(Para2_sel++, 0);
										ParameterPage2_dis(Para2_sel, 1);
										}
									}
									
									break;
							// // case MOTOR_DC_SERVO:
							// // case MOTOR_DC670_SERVO:
								// // if(PramSel_Page<1)	//page 1
									// // {
									// // if(Para_sel<10)
										// // {
										// // ParameterPage1_dis(Para_sel++, 0);
										// // ParameterPage1_dis(Para_sel, 1);
										// // }
									// // else
										// // {
										// // PramSel_Page++;
										// // ParamPage2_dis(); //参数 page2
										// // }
									// // }
								// // else	//page 2
									// // {
									// // if(Para2_sel<1)
										// // {
										// // ParameterPage2_dis(Para2_sel++, 0);
										// // ParameterPage2_dis(Para2_sel, 1);
										// // }
									// // }
									// // break;
							case MOTOR_AC_SERVO:
							case MOTOR_AC_SERVO_REV:
							case MOTOR_AC_A6_SERVO:
								if(PramSel_Page<1)	//page 1
									{
									if(Para_sel<10)
										{
										ParameterPage1_dis(Para_sel++, 0);
										ParameterPage1_dis(Para_sel, 1);
										}
									else
										{
										PramSel_Page++;
										ParamPage2_dis(); //参数 page2
										}
									}
								else	//page 2
									{
									if(Para2_sel<2)
										{
										ParameterPage2_dis(Para2_sel++, 0);
										ParameterPage2_dis(Para2_sel, 1);
										}
									}
								
									break;
							}
						}
					else if(ButtonTouch_mode==TOU_MODE_CALC)
						{
						if(PramSel_Page<1)	//page 1
							{
							if(Para_sel<6)
								{
								ParameterPage1_dis(Para_sel++, 0);
								ParameterPage1_dis(Para_sel, 1);
								}	
							}
						else	//page 2
							{
							if(Para2_sel<2)
								{
								ParameterPage2_dis(Para2_sel++, 0);
								ParameterPage2_dis(Para2_sel, 1);
								}
							}
						}
							break;
				case MANUAL_SERVO_C_MODE:// 手动直流伺服 C 参数 
					 if(ButtonTouch_mode==0)  //	 非 触摸计算器 下
						{
						if(Para_sel<7)
							{
							ServoParameter_dis(Para_sel++, 0);
							ServoParameter_dis(Para_sel, 1);
							}
						}
					else if(ButtonTouch_mode==TOU_MODE_CALC)
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
				case MANUAL_MODE: //手动	+++++++++步进
						if(InTargetPosit_flag==1)  //	目标位置
							{
							if(Unit==UNIT_MM)//mm
								{
								current_temp=TargetSize_temp;
								}
							else // inch
								{
								current_temp=TargetSize_inch;
								}
							}
						else 
							{
							if(Unit==UNIT_MM)//mm
								{
								current_temp=CurrentSize;
								}
							else // inch
								{
								current_temp=CurrentSize*100/254;
								}
							}
						step_temp = Step_Size;
						if(Unit!=UNIT_MM)//
							step_temp = Step_Size*100/254;
						if((current_temp>step_temp)&&(current_temp-step_temp)>Size_MIN_num)	//步进 有效
							{
							if(Unit==UNIT_MM)//mm
								{
								TargetSize = current_temp-step_temp;
								}
							else	//inch
								{
								TargetSize_inch = current_temp-step_temp;
								TargetSize = TargetSize_inch*2.54;
								}
							if(TargetSize!=CurrentSize)  //-------------运行
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
									// // case MOTOR_DC_SERVO:
									// // case MOTOR_DC670_SERVO:
										// // ServoSendCou=0;
										 // // DcServoStartRun_exec(TargetSize);
										// // // SelfLockEn_flag=0;
											// // break;
									case MOTOR_AC_SERVO:
									case MOTOR_AC_SERVO_REV:
									case MOTOR_AC_A6_SERVO:
										ACMotorRunStart(TargetSize);
											break;		
									}
								Run_flag=1;
								RunStop_flag=0;
								AutoCutStart_flag=0;
								InTargetPosit_flag=0;	//目标位置
								OneCutRoutine_flag=0; // 清 裁切 循环标志
								AutoCutStart_flag=0;
								AirOffOK_flag=0;
								PressUp_flag=0;
								PressDown_flag=0;
								PromptNum_dis();
								ClearCalculatorInput(); //清零计算器 输入
								}	
							}				
						break;
				}			
			 }
		 
		  } 
		else
		  {
		  if(Board_TestMod==TEST_SYS_TYPE)//主板 工作系统选择
			{
			if(MotorType<5)
				{
				SpeedLevelSel_dis(MotorType++,0);
				SpeedLevelSel_dis(MotorType,1);
				SaveMachineType(); //保存  机器类型
		 		}
			}
		  else if(Board_TestMod==TEST_PAGE_LINE)//
			{
			if(PageKf_Size_flag<PAGE_7_LINE)
				{
				PageLine_Set(PageKf_Size_flag++, 0);	//每页行数显示
				PageLine_Set(PageKf_Size_flag, 1);	//每页行数显示
				SavePageKf_Size();
				PageKf_Size_Init();	//每页 刀数初始化
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
				
				case TEACH_MODE://示教画面下
				case AUTO_MODE://自动主画面下
				case AUTO_PLUS_MODE:  //F5++
				case AUTO_MINUS_MODE:// F6--
				case SELF_CUT_MODE://自刀主画面下
				case TEACH_PLUS_MODE:  //自刀F5++
				case TEACH_MINUS_MODE://自刀 F6--
				case PROG_FLAG_MODE:	//标记 模式
				case TEACH_FLAG_MODE:	//标记 模式
						if(Knife_order>1)
							{
							Knife_order--;
							if(cursor_row>0)
								{
								CursorKnife_dis(cursor_row, 0);//红色光标消失
								OneKnifeDataSel_dis(Knife_order+1, cursor_row,0);  //一刀数据 高亮显示
								cursor_row--;
								CursorKnife_dis(cursor_row, 1);//红色光标上移显示
								OneKnifeDataSel_dis(Knife_order, cursor_row,RED_COLOR);  //一刀数据 高亮显示
								}
							else  //页眉
								{
								Size_1page_dis(Knife_order,0);//一页尺寸显示
								}	
							}
						else     //指向 最后一刀
							{
							Knife_order=OnePro_head.pro_knifeSUM;
							if(Knife_order>PageKf_Size)
								{
								Size_1page_dis(Knife_order,0);//一页尺寸显示
								CursorKnife_dis(cursor_row, 0);//红色光标消失
								cursor_row=0;
								CursorKnife_dis(cursor_row, 1);//红色光标显示  在开头
								}
							else
								{
								CursorKnife_dis(cursor_row, 0);//红色光标消失
								OneKnifeDataSel_dis(1, cursor_row,0);  //一刀数据 高亮显示
								cursor_row=Knife_order-1;
								CursorKnife_dis(cursor_row, 1);//红色光标显示  在开头
								OneKnifeDataSel_dis(Knife_order, cursor_row,RED_COLOR);  //一刀数据 高亮显示
								}
							}
						if(Knife_order<=OnePro_head.pro_knifeSUM)
							StepOrder_dis(Knife_order);//步骤更新
						switch(WorkMode)
							{
							case AUTO_PLUS_MODE:  //F5++
							case AUTO_MINUS_MODE:// F6--
							case TEACH_PLUS_MODE://自刀F5++
							case TEACH_MINUS_MODE://自刀 F6--
									break;
							default:
								PromptNum_dis();//输入范围
								PromptDis_flag=1;
									break;
							}
						 break;
				case AUTO_LABEL_MODE://标签 下--------------------------
				case TEACH_LABEL_MODE://标签 下--------------------------
					 if(PorgSet_sel>0)
						{
						LabelSel_dis(PorgSet_sel,0);PorgSet_sel--;
						LabelSel_dis(PorgSet_sel,1);
						}
							break;
				case AUTO_DIVIDE_MODE://等分 下--------------------------
				case TEACH_DIVIDE_MODE://等分 下--------------------------
					 if(PorgSet_sel>0)
						{
						DivideSel_dis(PorgSet_sel,0);PorgSet_sel--;
						DivideSel_dis(PorgSet_sel,1);
						}
							break;
				case READ_PRO_MODE:    //程序选择----------------------
				// // case TEACH_PRO_MODE:    //程序选择----------------------
						  if(prog_order<2)//返回最后 pro
							  {
							  prog_order=MAX_PROG;
							  CursorPro_dis(cursor_pro,0);//光标
							  cursor_pro=MAX_PROG%PROGS_1PAGE;
							  if(cursor_pro<1)
								 cursor_pro=PROGS_1PAGE;
							  cursor_pro--;
							  CursorPro_dis(cursor_pro,1);//
							  Prog_1page_dis(prog_order-cursor_pro, 0);//===程序---数据显示
							  OneProgHeadInfo_dis(cursor_pro ,  prog_order, 1);	//一条程序 显示1
							  }
						  else
							  {
							  prog_order--;
							  if(cursor_pro>0)//
								 {
								 CursorPro_dis(cursor_pro,0);//光标
								 OneProgHeadInfo_dis(cursor_pro ,  prog_order+1, 0);	//一条程序 显示0
								 cursor_pro--;
								 CursorPro_dis(cursor_pro,1);//
								 OneProgHeadInfo_dis(cursor_pro ,  prog_order, 1);	//一条程序 显示1
								 }
							  else//上一页
								 {
								 CursorPro_dis(cursor_pro,0);//光标
								 cursor_pro=PROGS_1PAGE-1;
								 CursorPro_dis(cursor_pro,1);//
								 Prog_1page_dis(prog_order-(PROGS_1PAGE-1), 0);//===程序---数据显示
								 OneProgHeadInfo_dis(cursor_pro ,  prog_order, 1);	//一条程序 显示1
								 }
							  }
						     break;
				case READ_PRO_MESS_MODE:			 
				// // case TEACH_PRO_MESS_MODE:	
					
						DirKeySelInput_exec(KEY_UP);
							break;
				// // case AUTO_TOOLS_MODE://  参数设置  上移
				// // case SELF_TOOLS_MODE://  参数设置  上移
				case MANUAL_TOOLS_MODE:// 手动 参数模式
					if(PramSel_Page<1)	//page 1
						{
						if(Para_sel>0)
							{
							if(ButtonTouch_mode==0)  //	 非 触摸计算器 下
								{
								ParameterPage1_dis(Para_sel--, 0);
								ParameterPage1_dis(Para_sel, 1);	
								}
							else if(ButtonTouch_mode==TOU_MODE_CALC)
								{
								if(Para_sel>6)
									Para_sel--;
								else 
									ParameterPage1_dis(Para_sel--, 0);
								if(Para_sel<7)
									ParameterPage1_dis(Para_sel, 1);	
								}
							}
						}
					else	//page 2
						{
						if(Para2_sel>0)
							{
							if(ButtonTouch_mode==0)  //	 非 触摸计算器 下
								{
								ParameterPage2_dis(Para2_sel--, 0);
								ParameterPage2_dis(Para2_sel, 1);	
								}
							else if(ButtonTouch_mode==TOU_MODE_CALC)
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
							if(ButtonTouch_mode==0)  //	 非 触摸计算器 下
								{
								PramSel_Page--;	
								ParamPage1_dis(); //参数 page1
								}
							}
						}
					
							 break;
				case MANUAL_SERVO_C_MODE:// 手动直流伺服 C 参数 
					if(Para_sel>0)
						{
						if(ButtonTouch_mode==0)  //	 非 触摸计算器 下
							{
							ServoParameter_dis(Para_sel--, 0);
							ServoParameter_dis(Para_sel, 1);	
							}
						else if(ButtonTouch_mode==TOU_MODE_CALC)
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
		  if(Board_TestMod==TEST_SYS_TYPE)//主板 工作系统选择
			{
			if(MotorType>0)
				{
				SpeedLevelSel_dis(MotorType--,0);
				SpeedLevelSel_dis(MotorType,1);
				SaveMachineType(); //保存  机器类型
		  		}
			}
		  else if(Board_TestMod==TEST_PAGE_LINE)//
			{
			if(PageKf_Size_flag>PAGE_5_LINE)
				{
				PageLine_Set(PageKf_Size_flag--, 0);	//每页行数显示
				PageLine_Set(PageKf_Size_flag, 1);	//每页行数显示
				SavePageKf_Size();
				PageKf_Size_Init();	//每页 刀数初始化
				}
			}
		  }
  	     break; 
    case PGUP_KEY_CODE:	//上页   -----------
		if(WorkStart_flag==0)
			{
			if(Board_TestMod==TEST_ICON)
				{
				if(Manual_page>0)        //上一页  帮助
					{
					Manual_page--;
					Comment_dis_page(Manual_page);
					}
				}
			}
		else
			{
			PageUpExec();	//上翻页
			}
			break;
	case PGDOWN_KEY_CODE:	//下页   -----------
		if(WorkStart_flag==0)
			{
			if(Board_TestMod==TEST_ICON)
				{
				if(Manual_page<1)        //下一页  帮助
					{
					Manual_page++;
					Comment_dis_page(Manual_page);
					}
				}
			}
		else
			{
			PageDownExec();	//下翻页
			}
			break;
	case LEFT_KEY_CODE:	// 左
		if(WorkStart_flag==1)
		  {
		  if(Run_flag==0)
			 {
			 switch(WorkMode)
				{
				case READ_PRO_MESS_MODE:			 
				// // case TEACH_PRO_MESS_MODE:	
						DirKeySelInput_exec(KEY_LEFT);
						
						break;
				}
			 }
		  }	 
		
             break; 
	case RIGHT_KEY_CODE:	// 右
		if(WorkStart_flag==1)
		  {
		  if(Run_flag==0)
			 {
			 switch(WorkMode)
				{
				case READ_PRO_MESS_MODE:			 
				// // case TEACH_PRO_MESS_MODE:
						DirKeySelInput_exec(KEY_RIGHT);
						
						break;
				}
			 }
		  }	 	
             break;		 
    case ALL_FLAG_KEY_CODE:       //标记设定
		if(WorkStart_flag==1)
		  {
		  if(Run_flag==0)
			 {
			
			 }
		  }	 	
			break;    
     case  ONE_KEY_CODE + YES_KEY_CODE: //F 功能按键 +  数字8  **************       
             break;    
    case  ONE_KEY_CODE + OPTION_KEY_CODE: //F 功能按键 +  “-/除”  **************
                
           break;       
          
    case ONE_KEY_CODE +  REV_KEY_CODE: //F 功能按键 +  “+/*”  **************
          
          break;
    case ONE_KEY_CODE + ADD_KEY_CODE: //F 功能按键 +  “.”  **************
           
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
		
    }            
	
}

/****
int KeyCheck(void)
{
int i;
int  c;
KEY_COL1_CLR();
KEY_COL2_CLR();
KEY_COL3_CLR();
KEY_COL4_CLR();
KEY_COL5_CLR();
KEY_COL6_CLR();
i=100;
while(i--);
c=(~KEYIO)&KEY_CODE_MASK;
KEY_COL1_SET();
KEY_COL2_SET();
KEY_COL3_SET();
KEY_COL4_SET();
KEY_COL5_SET();
KEY_COL6_SET();
return(c);
}
void KeyReadCode(void)
{
	int i;
int keycodetemp;
KeyCode=0;
KEY_COL1_CLR();
i=500;
while(i--);
keycodetemp=(~KEYIO)&KEY_CODE_MASK;
if(keycodetemp!=0)
	KeyCode=keycodetemp|0x4000000;
KEY_COL1_SET();

KEY_COL2_CLR();
i=500;
while(i--);
keycodetemp=(~KEYIO)&KEY_CODE_MASK;
if(keycodetemp!=0)
	KeyCode+=(keycodetemp|0x8000000);
	//KeyCode=keycodetemp|0x10000000;
KEY_COL2_SET();

KEY_COL3_CLR();
i=500;
while(i--);
keycodetemp=(~KEYIO)&KEY_CODE_MASK;
if(keycodetemp!=0)
	KeyCode+=(keycodetemp|0x10000000);
	//  KeyCode=keycodetemp|0x20000000;
KEY_COL3_SET();

KEY_COL4_CLR();
i=500;
while(i--);
keycodetemp=(~KEYIO)&KEY_CODE_MASK;
if(keycodetemp!=0)
	KeyCode+=(keycodetemp|0x20000000);
//		KeyCode=keycodetemp|0x40000000;
KEY_COL4_SET();

KEY_COL5_CLR();
i=500;
while(i--);
keycodetemp=(~KEYIO)&KEY_CODE_MASK;
if(keycodetemp!=0)
	KeyCode+=(keycodetemp|0x40000000);
//	  KeyCode=keycodetemp|0x80000000;
KEY_COL5_SET();


KEY_COL6_CLR();
i=500;
while(i--);
keycodetemp=(~KEYIO)&KEY_CODE_MASK;
if(keycodetemp!=0)
	KeyCode+=(keycodetemp|0x80000000);
//	  KeyCode=keycodetemp|0x80000000;
KEY_COL6_SET();


}
void Key_Enable(unsigned char enb)
{
}****/
void KeyInit(void)  //键端口初始化
{
  /*
KEY_COL1_SET();
KEY_COL2_SET();
KEY_COL3_SET();
KEY_COL4_SET();
KEY_COL5_SET();
KEY_COL6_SET();
//KEYIO_DDR&=0xfc1FFFFF;
PINMODE7&=0xffc00ffff;
  */
}






void ClrInput_function(void)//清零 输入框
{
for(num_cou=0;num_cou<8;num_cou++)
	 {
		Size_temp[num_cou++]=0;
	 }
num_cou=0; //
// CalcTemp_cou=num_cou;
Dot_flag=0;
SubLine_flag=0; //间隔符‘-’
// GLCD_SetWindow_Fill( SIZE_WINDOW_X+SIGN_2WIDE, SIZE_WINDOW_Y, SIZE_WINDOW_X+SIZE_WINDOW_WIDE, SIZE_WINDOW_Y+SIZE_WINDOW_HIGH, 0xfffff, 0xffff);//尺寸输入框
}
//************************************************************************************
void SaveOneKnife_datas(Int16U prog,Int16U order,pInt8U pdatas)//保存当前程序一刀数据+info
{
pInt8U pbuf,phead;
Int32U add,sd_add,offset,i;
if(prog<=(PROG_GROPU1+1))  //前301个prog
   {
   offset=PROG_BYTES1*(prog-1);
   }
else//后  199
   {
   offset=PROG_BYTES1*PROG_GROPU1+(prog-PROG_GROPU1-1)*PROG_BYTES2;
   }
sd_add=K_SIZE_sdram+offset;//程序数据 buf基地址 

pbuf=(pInt8U)sd_add;
add=DATA_SAVE_OFFSET+offset;//刀数据 spi基地址
phead=(pInt8U)&OnePro_head;
//********************总刀数变更  则  info 保存
if(Knife_sum_before!=OnePro_head.pro_knifeSUM)
	{
	Knife_sum_before=OnePro_head.pro_knifeSUM;
	for(i=0;i<PRO_HEAD_BYTES;i++)
		{
		*(pbuf+i)=*(phead+i);
		}
	Write_25pe_data(phead,     add,     PRO_HEAD_BYTES);	
	}
//********************刀数据 保存
pbuf=(pInt8U)(sd_add+PRO_HEAD_BYTES+(order-1)*5);//刀数据 buf地址
add=add+PRO_HEAD_BYTES+(order-1)*5;
for(i=0;i<5;i++)
   {
   *(pbuf+i)=*(pdatas+i);      //更新 缓存
   }
Write_25pe_data(pdatas,     add,      5);
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
sd_add=K_SIZE_sdram+offset+PRO_HEAD_BYTES;//刀数据 buf基地址
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
sd_add=K_SIZE_sdram+offset+PRO_HEAD_BYTES;//刀数据 buf基地址
   
pbuf=(pInt8U)(sd_add+(order-1)*5);//刀数据 buf地址
for(i=0;i<5;i++)
   {
   *pbuf++=*pdatas++;      //更新 缓存
   }
}

void SaveBuf_datas(Int16U prog,Int16U order1, Int16U order2)//保存 order1到 order2  buf区的数据到spi
{
pInt8U pbuf,psave;
Int32U add,sd_add,offset,i;
if(prog<=(PROG_GROPU1+1))  //前301个prog
   {
   offset=PROG_BYTES1*(prog-1);
   }
else//后  199
   {
   offset=PROG_BYTES1*PROG_GROPU1+(prog-PROG_GROPU1-1)*PROG_BYTES2;
   }
sd_add=K_SIZE_sdram+offset+PRO_HEAD_BYTES;//刀数据 buf基地址
pbuf=(pInt8U)(sd_add+(order1-1)*5);
add=DATA_SAVE_OFFSET+offset+PRO_HEAD_BYTES;//刀数据 spi基地址
add=add+(order1-1)*5;
if(order2>=order1)//
   {
   i=(order2-order1+1)*5;
   Write_25pe_data(pbuf,     add,      i);
   }
}

void ClrBuf_datas(Int16U prog,Int16U order1, Int16U order2)//清零 order1到 order2  buf区的数据   
{
pInt8U pbuf;
Int32U i,lenth,sd_add,offset;
if(prog<=(PROG_GROPU1+1))  //前301个prog
   {
   offset=PROG_BYTES1*(prog-1);
   }
else//后  199
   {
   offset=PROG_BYTES1*PROG_GROPU1+(prog-PROG_GROPU1-1)*PROG_BYTES2;
   }
sd_add=K_SIZE_sdram+offset+PRO_HEAD_BYTES;//刀数据 buf基地址
pbuf=(pInt8U)(sd_add+(order1-1)*5);
lenth=(order2-order1+1)*5;
for(i=0;i<lenth;i++)
   {
   *pbuf++=0;
   }
}


//-----参数 部分存取
void ReadPro_perameter(pInt8U pdata)//读取 程序 段 号码xxxxxxxxxxx
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

void SavePro_data(pInt8U pdata)//保存 程序 段 号码xxxxxxxxxxx
{
Int32U add;
add=PRO_NUM_25PEADD;//地址

Write_25pe_data(pdata, add, 4);
}

void GetPro_headInfo(Int16U prog, pInt8U pdata)//sdram 读一个程序头(程序名+ 时间 +刀数 )
{
Int32U offset;
pInt8U pbuf,pProHead;
Int16U max_sum,i;
//Int16U sum_temp;
PROCESS_HEAD head_temp;
pProHead=(pInt8U) &head_temp;
if(prog<=(PROG_GROPU1+1))  //前301个prog
   {
   offset=PROG_BYTES1*(prog-1);
   max_sum=MAX_KNIFE1;
   }
else//后  199
   {
   offset=PROG_BYTES1*PROG_GROPU1+(prog-PROG_GROPU1-1)*PROG_BYTES2;
   max_sum=MAX_KNIFE2;
   }
pbuf=(pInt8U)(K_SIZE_sdram+offset);//程序基地址
// pdata=(pInt8U)&OnePro_head;
for(i=0;i<PRO_HEAD_BYTES;i++)
	{
	*(pdata+i)=*(pbuf+i);	
	*(pProHead+i)=*(pbuf+i);	//加载 程序头
	}
pProHead=(pInt8U) &ProHead_default;
if((head_temp.pro_knifeSUM<1)||(head_temp.pro_knifeSUM>max_sum))	//程序头 判断
   {
   // //-------名字
   // OnePro_head.pro_name[0]=0xff;
   // OnePro_head.pro_name[1]=0xff;
   // OnePro_head.pro_name[2]=0xff;
   // OnePro_head.pro_name[3]=0xff;
   // //-------时间
   // OnePro_head.pro_year=0;
   // OnePro_head.pro_month=0;
   // OnePro_head.pro_day=0;
   // //----刀数
   // OnePro_head.pro_knifeSUM=1;
   
   for(i=0;i<PRO_HEAD_BYTES;i++)		//更新缓存sdram
		{
		*pbuf++=*pProHead;
		*pdata++=*pProHead++;
		}
   }
else
	{
	
	}
}

void SavePro_headInfo(Int16U prog, pInt8U pdata)//spi保存一个程序的 头(程序名+ 时间 +刀数 )
{
Int32U offset,add;
pInt8U pbuf;
Int16U i;
if(prog<=(PROG_GROPU1+1))  //前301个prog
   {
   offset=PROG_BYTES1*(prog-1);
   }
else//后  199
   {
   offset=PROG_BYTES1*PROG_GROPU1+(prog-PROG_GROPU1-1)*PROG_BYTES2;
   }
pbuf=(pInt8U)(K_SIZE_sdram+offset);//程序基地址
//pdata=(pInt8U)&OnePro_head;
for(i=0;i<PRO_HEAD_BYTES;i++)		//更新buf
	{
	*(pbuf+i)=*(pdata+i);
	}
	
add=DATA_SAVE_OFFSET+offset;
Write_25pe_data((pInt8U)pbuf, add, PRO_HEAD_BYTES);
// Write_25pe_data((pInt8U)pdata, add, PRO_HEAD_BYTES);	//保存
}

void ReadOnePro_datas(Int16U prog) //spi读一个 程序数据 到 buf
{
pInt8U pbuf;
Int32U i;
Int32U offset,add;
if(prog<=(PROG_GROPU1+1))  //前301个prog
   {
   offset=PROG_BYTES1*(prog-1);
   }
else//后  199
   {
   offset=PROG_BYTES1*PROG_GROPU1+(prog-PROG_GROPU1-1)*PROG_BYTES2;
   }
pbuf=(pInt8U)(K_SIZE_sdram+offset);//一个pro的 buf基地址
add=DATA_SAVE_OFFSET+offset;
FastRead_Datas_Start(add);
for(i=0;i<OnePro_head.pro_knifeSUM*5+PRO_HEAD_BYTES;i++)
   {
   *pbuf++=ReadFlash_Datas();
   }
FlashChip_Dis;
}

void ReadAllPro_head_data1(void)// 读所有程序头+第一刀  至 buf
{
pInt8U pbuf,pdata;
Int32U add,pro_cou,i;
// Int16U k_sum_temp=1;
Int16U max_sum;
Int8U err_flag=0;

PROCESS_HEAD head_temp;
pro_cou=1;

pdata=(pInt8U)&head_temp;
pbuf=(pInt8U)K_SIZE_sdram;

add=DATA_SAVE_OFFSET;
while(pro_cou<=MAX_PROG)
	{
	FastRead_Datas_Start(add);
	for(i=0;i<5+PRO_HEAD_BYTES;i++)
	   {
		*(pbuf+i)=ReadFlash_Datas();
		*(pdata+i)=*(pbuf+i);
	   }
	FlashChip_Dis;
	
	if(pro_cou<=PROG_GROPU1)//前 300个pro
	   {
	   max_sum=MAX_KNIFE1;//999
	   }
	else
	   {
	   max_sum=MAX_KNIFE2;//399
	   } 
	
	pdata=(pInt8U)&ProHead_default;
	if((head_temp.pro_knifeSUM<1)||(head_temp.pro_knifeSUM>max_sum))//未初始化
		err_flag=1;
		/***
	if(err_flag==0)
		{
		if(((head_temp.pro_year>>4)&0xf)>9)
			err_flag=1;
		}
	if(err_flag==0)
		{
		if((head_temp.pro_year&0xf)>9)
			err_flag=1;
		}
	if(err_flag==0)
		{
		if(((head_temp.pro_month>>4)&0xf)>9)
			err_flag=1;
		}
	if(err_flag==0)
		{
		if((head_temp.pro_month&0xf)>9)
			err_flag=1;
		}	
	if(err_flag==0)
		{
		if(((head_temp.pro_day>>4)&0xf)>9)
			err_flag=1;
		}
	if(err_flag==0)
		{
		if((head_temp.pro_day&0xf)>9)
			err_flag=1;
		}	
		**/
	if(err_flag==1)
	   {
	   for(i=0;i<PRO_HEAD_BYTES;i++)		//更新缓存sdram
			{
			*(pbuf+i)=*(pdata+i);
			}
	   for(;i<PRO_HEAD_BYTES+5;i++)
	       {
		   *(pbuf+i)=0;
	       }
	   Write_25pe_data(pbuf, add, PRO_HEAD_BYTES+5);
		}
	
	pro_cou++;   
	if(pro_cou>PROG_GROPU1+1)
	   {
	   pbuf=(pInt8U)(K_SIZE_sdram+PROG_BYTES1*PROG_GROPU1+PROG_BYTES2*(pro_cou-PROG_GROPU1-1));
       add=DATA_SAVE_OFFSET+PROG_BYTES1*PROG_GROPU1+PROG_BYTES2*(pro_cou-PROG_GROPU1-1);
	   }
	else
	   {
	   pbuf=(pInt8U)(K_SIZE_sdram+PROG_BYTES1*(pro_cou-1));
       add=DATA_SAVE_OFFSET+PROG_BYTES1*(pro_cou-1);
	   }
	pdata=(pInt8U)&head_temp;
	}
}

void RenewModifyDate(void)	//更新时间信息-.-.-.-.-.-.-.-.-.-.-.-.-.-
{
OnePro_head.pro_year=Year;	//(Year>>4)*10+(Year&0x0f);
OnePro_head.pro_month=Month;	//(Month>>4)*10+(Month&0x0f);
OnePro_head.pro_day=Dom;	//(Dom>>4)*10+(Dom&0x0f);
SavePro_headInfo(Pro_data.pro_num, (pInt8U)&OnePro_head);	//保存
}


void ReadDatas_to_sdram(void)///刀数据读入sdram
{
Int32U add,d,sum;
KNIFE_DATA Knife_datas;
pInt8U pdata,pbuf,p_head;
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
   MAX_Knife=MAX_KNIFE1;//999
   }
 else
   {
   MAX_Knife=MAX_KNIFE2;//399
   } 

if((Pro_data.pro_sum<1)||(Pro_data.pro_sum>MAX_PROG))//程序数 无效，则初始化
  {
  Pro_data.pro_num=1;//当前程序 号1
  Pro_data.pro_sum=1;//程序 总数
  // OnePro_head.pro_knifeSUM=1;//总 刀数
  pdata=(pInt8U)&Pro_data;
  SavePro_data(pdata);
  
  // //-------名字
   // OnePro_head.pro_name[0]=0xff;
   // OnePro_head.pro_name[1]=0xff;
   // OnePro_head.pro_name[2]=0xff;
   // OnePro_head.pro_name[3]=0xff;
   // //-------时间
   // OnePro_head.pro_year=0;
   // OnePro_head.pro_month=0;
   // OnePro_head.pro_day=0;
   // //----刀数
   // OnePro_head.pro_knifeSUM=1;	
   pbuf=(pInt8U)K_SIZE_sdram;
   pdata=(pInt8U)&OnePro_head;
   p_head=(pInt8U)&ProHead_default;
   for(d=0;d<PRO_HEAD_BYTES;d++)
		{
		*pbuf++=*p_head;
		*pdata++=*p_head++;
		}
  ClrBuf_datas(Pro_data.pro_num, 1,MAX_Knife);  //清零 刀数据buf
  
  
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
  //OnePro_head.pro_knifeSUM=1;
  // Pro_data.pro_num=4;
  //Pro_data.pro_sum=2;
  ReadAllPro_head_data1();  ///读所有 程序 	head + data1
  GetPro_headInfo(Pro_data.pro_num, (pInt8U)&OnePro_head); //获取前程序 头信息
 // ReadOnePro_datas(Pro_data.pro_num);//读取 当前pro
  ClrBuf_datas(Pro_data.pro_num, 1,MAX_Knife);  //清零 刀数据buf
  
  //OnePro_head.pro_knifeSUM=100;
  ReadOnePro_datas(Pro_data.pro_num);//读取 一个pro
  
  CheckKnifeSum_exec();  //--------------总刀数    核对
  Knife_sum_before=OnePro_head.pro_knifeSUM;
	//---------程序有效 更新时间
  // GetOneKnife_datas(Pro_data.pro_num, 1 , (pInt8U)&Knife_datas);//取出一刀 数据
  // if(Knife_datas.size>0)
	  // {
	  read_time();
	  RenewModifyDate();	//更新时间信息-.-.-.-.-.-.-.-.-.-.-.-.-.-
	  // }
  }
 
 /*
  pdata=(pInt8U)K_SIZE_sdram;
  add=DATA_SAVE_OFFSET;
  if(Pro_data.pro_sum<=PROG_GROPU1)
    {
	sum=PROG_BYTES1*Pro_data.pro_sum;
	}
  else
    {
	sum=PROG_BYTES1*PROG_GROPU1+(Pro_data.pro_sum-PROG_GROPU1)*PROG_BYTES2;
	}
  FastRead_Datas_Start(add);
  for(d=0;d<sum;d++)
    {
     *pdata++=ReadFlash_Datas();
    }
  FlashChip_Dis;   
  } */
  
}




void OneProgHeadInfo_dis(Int8U row, Int16U p_order, Int8U mark_flag)	//一条程序 显示
{
Int16U color;
PROCESS_HEAD Pro_head;
if(mark_flag==0)
	{
	color=BLACK_COLOR;
	}
else
	{
	color=RED_COLOR;
	}
GetPro_headInfo(ProNumGroup[p_order],  (pInt8U)&Pro_head);//sdram 读一个程序头(程序名+ 时间 +刀数 )
ProgOrder_dis(row, ProNumGroup[p_order], color);//--------显示一个 程序号
ProgName_dis(row,  Pro_head, color);//-----------------------显示一个程序名
ProgStep_dis(row, Pro_head, color);//-----------------------显示步骤数
ProgDate_dis(row, Pro_head, color);//-----------------------显示日期
}

void Prog_1page_dis(Int16U p_order,Int16U line)//一页程序显示
{
//pInt8U pbuf;
PROCESS_HEAD Pro_head;
Int16U x1,y1,x2,y2,back_color=TEXT_TAB_BACK_COLOR;
x1=PROC_NUM_X; y1=PROC_NUM_Y;
x2=(MIDDLE_PAGE_X+M_PAGE_WIDE)-10; y2=y1+(PROTEXT_HIGH*PROGS_1PAGE);
GLCD_SetWindow_Fill(x1, y1, x2, y2, back_color, back_color);//
while(line<PROGS_1PAGE)
	{
	if(p_order<=MAX_PROG)
		{
		// GetOneKnife_datas(ProNumGroup[prog_order], 1 , (pInt8U)&Knife_datas);//取出一刀 数据
		// KnifeOrder_dis(line, ProNumGroup[prog_order],0);//序号
		// KnifeSize_dis(line,Knife_datas.size,0);//尺寸
		GetPro_headInfo(ProNumGroup[p_order],  (pInt8U)&Pro_head);//sdram 读一个程序头(程序名+ 时间 +刀数 )
		ProgOrder_dis(line, ProNumGroup[p_order], 0);//--------显示一个 程序号
		ProgName_dis(line,  Pro_head, 0);//-----------------------显示一个程序名
		ProgStep_dis(line, Pro_head, 0);//-----------------------显示步骤数
		ProgDate_dis(line, Pro_head, 0);//-----------------------显示日期
		p_order++;
		}
	else//已无数据
		{
		// x=PROC_NUM_X;
		// y=RIGHT_ARROW_Y+(line%PAGE_KNIFE)*SIZETEXT_HIGH;
	    // GLCD_SetWindow_Fill( x, y, x+500, y+SIZETEXT_HIGH, back_color, back_color);//尺寸输入
		}
	
	line++;
	}
}

void Size_1page_dis(Int16U start_order,Int16U row)//一页尺寸显示
{
//Int16U n;
//pInt8U pbuf;
KNIFE_DATA Knife_datas;
Int16U x1,y1,x2,y2,back_color=TEXT_TAB_BACK_COLOR;//0xef9f;
//Int8U sel_flag=0;

//pbuf=(pInt8U)(K_SIZE_sdram+(start_order*5));
while(row<PageKf_Size)
   {
   if(start_order<=MAX_Knife)
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
			// if((Knife_datas.size<Size_MIN_num)||(Knife_datas.size>Size_MAX_num))
			if(0)		//*****************************************************************2015--12--31---
				{
				Knife_datas.size=0;
				Knife_datas.k_flag=0;
				if(OnePro_head.pro_knifeSUM>=start_order)
					{
					if(start_order>1)
						OnePro_head.pro_knifeSUM=start_order-1;
					else
						OnePro_head.pro_knifeSUM=1;
					Knife_sum_before=OnePro_head.pro_knifeSUM;
					SavePro_headInfo(Pro_data.pro_num, (pInt8U)&OnePro_head);	//保存**
					StepNum_dis(OnePro_head.pro_knifeSUM,start_order);//步骤更新
					}
				}
			if(start_order>OnePro_head.pro_knifeSUM)	//最后一个步骤 之后仍有数据 则清除
				{
				if(Knife_datas.size>0)
					{
					Knife_datas.size=0;
					Knife_datas.k_flag=0;
					}
				}
				
			KnifeSize_dis(row,Knife_datas.size,0);//尺寸
			}
      
		if((ButtonTouch_mode==0)||(ButtonTouch_mode==TOU_MODE_F4)) //	 非 触摸计算器 下
			AllFlagPic_dis(row,Knife_datas.k_flag); // 推纸 标志 
	  }
   else
      {
	  x1=RIGHT_ARROW_X;
      y1=RIGHT_ARROW_Y+row*Kf_Line_HIGH;
	  y2=y1+Kf_Line_HIGH-20;
	  if(ButtonTouch_mode==0)  //	 非 触摸计算器 下
		  x2=TABLE_END_COL;
	  else if(ButtonTouch_mode==TOU_MODE_CALC)
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
pbuf_k1=(pInt8U)(K_SIZE_sdram+offset+PRO_HEAD_BYTES+(knife-1)*5);//当前刀 buf基地址
pbuf_k2=pbuf_k1+5;        //下一刀 

num=OnePro_head.pro_knifeSUM-knife;
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
	  if((OneKnife_data.k_flag&0x0f)==KNIFE_FLAG)
		 {
		 // OneKnife_data.k_flag=NO_FLAG;  //清除 标志
		 OneKnife_data.k_flag&=0xf0;  //清除 标志
		 SaveOneKnife_datas(prog, knife , pKnife_data);//保存一刀数据
		 }
	  } 
	
   pbuf_k1=(pInt8U)(K_SIZE_sdram+offset+PRO_HEAD_BYTES+(knife-1)*5);//当前刀 buf基地址
   add=DATA_SAVE_OFFSET+offset+PRO_HEAD_BYTES+(knife-1)*5;//
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
pbuf_k1=(pInt8U)(K_SIZE_sdram+offset+PRO_HEAD_BYTES+(OnePro_head.pro_knifeSUM-1)*5);//最后一刀 buf基地址
pbuf_k2=pbuf_k1+5;        //后一刀

pbuf_k1+=4;
pbuf_k2+=4;
num=OnePro_head.pro_knifeSUM-knife+1;

for(n=0;n<num*5;n++)
   {
   *pbuf_k2--=*pbuf_k1--;
   }   
pbuf_k1=(pInt8U)(K_SIZE_sdram+offset+PRO_HEAD_BYTES+(knife)*5);//当前刀 buf基地址
add=DATA_SAVE_OFFSET+offset+PRO_HEAD_BYTES+(knife)*5;//
Write_25pe_data(pbuf_k1,     add,      num*5);   
}

Int8U CheckInputNums(void)  //输入尺寸 计算
{
Int8U nn,num_bits;
pInt8U Size;
Int32U temp=0;
nn=0;
Dot_flag=0;
if(WorkStart_flag==0)// if((ButtonTouch_mode==0)||(ButtonTouch_mode==TOU_MODE_F4)) // 标记框模式
	{
	Size=Size_temp;
	num_bits=num_cou;	
	}
else					// else if(ButtonTouch_mode==TOU_MODE_CALC)    //触摸 输入下
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
		 
		 case TEACH_MODE://示教画面下
		 case AUTO_MODE://自动主画面下
		 // // case SELF_CUT_MODE://自刀主画面下
		 case MANUAL_MODE:   //手动
		 case PROG_FLAG_MODE:		//标记 模式
		 case TEACH_FLAG_MODE:		//标记 模式
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
						case INDONSIA:	//印尼
							Printf16("Input data melebihi batas",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,RED_COLOR,0,0xffff);
								break;
						case PORTUGAL:	//葡萄牙
								Printf16("Dados de entrada excede o limite",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,RED_COLOR,0,0xffff);
								break;											
						case SPANISH: //西班牙
								Printf16("Los datos de entrada excede el límite",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,RED_COLOR,0,0xffff);
								break;
						}
					// if(ButtonTouch_mode==TOU_MODE_CALC)   //触摸下
						// {
						ClearCalculatorInput(); //清零计算器 输入
						// }
					return 0;
					}
				else   //正确	 
					{
					PromptNum_dis();//输入范围 提示
					PromptDis_flag=1;
					return 1;
					}	
					break;
		case AUTO_LABEL_MODE://	编程 标签	
		case TEACH_LABEL_MODE:// 示教 标签	
		case AUTO_DIVIDE_MODE://编程 等分
		case TEACH_DIVIDE_MODE://示教 等分
		// // case AUTO_RULER_MODE://自动 基准
		// // case SELF_RULER_MODE://自刀 基准
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
							case INDONSIA:	//印尼
								Printf16("Input data melebihi batas",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,RED_COLOR,0,0xffff);
									break;
							case PORTUGAL:	//葡萄牙
									Printf16("Dados de entrada excede o limite",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,RED_COLOR,0,0xffff);
									break;											
							case SPANISH: //西班牙
									Printf16("Los datos de entrada excede el límite",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,RED_COLOR,0,0xffff);
									break;
							}
						// if(ButtonTouch_mode==TOU_MODE_CALC)   //触摸下
							// {
							ClearCalculatorInput(); //清零计算器 输入
							// }
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
					if((WorkMode&0x0f)==(AUTO_DIVIDE_MODE&0x0f))//等分
						{
						InputSize=temp;
						if(DivideValue_flag==0)
							{
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
							if(InputSize<=Size_MAX_num)   //正确
								{
								PromptNum_dis();//输入范围 提示
								PromptDis_flag=1;
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
									case INDONSIA:	//印尼
										Printf16("Input data melebihi batas",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,RED_COLOR,0,0xffff);
										break;
									case PORTUGAL:	//葡萄牙
										Printf16("Dados de entrada excede o limite",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,RED_COLOR,0,0xffff);
										break;											
									case SPANISH: //西班牙
										Printf16("Los datos de entrada excede el límite",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,RED_COLOR,0,0xffff);
										break;
									}
								return 0;
								}
							}
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
								case INDONSIA:	//印尼
									Printf16("Input data melebihi batas",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,RED_COLOR,0,0xffff);
										break;
								case PORTUGAL:	//葡萄牙
										Printf16("Dados de entrada excede o limite",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,RED_COLOR,0,0xffff);
										break;											
								case SPANISH: //西班牙
										Printf16("Los datos de entrada excede el límite",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,RED_COLOR,0,0xffff);
										break;
								}
							}
						return 0;		
						}
					return 0;		
					}
					break;
		case READ_PRO_MODE:    //程序选择----------------------
		// // case TEACH_PRO_MODE:    //程序选择----------------------
				if((temp>0)&&(temp<=MAX_PROG))// 有效
					{
					InputSize=temp;
					return 1;
					}
				return 0;	
					break;
				
		// // case AUTO_TOOLS_MODE://自动  参数设置
		// // case SELF_TOOLS_MODE://自刀  参数设置
		case MANUAL_TOOLS_MODE:// 手动 参数模式
				if(PramSel_Page<1)	//page 1
					{
					if(Para_sel>8)
						{
						InputSize=temp;
						}
					else //if(Para_sel<7)
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
						if(Unit==UNIT_MM)
							{
							InputSize=temp*100;
							}
						else
							{
							InputSize=temp*1000;
							}
						}
					else 
						{
						// InputSize=temp;
						}
					}
				return 1;	
					break;
		case AUTO_PLUS_MODE:  //F5++
		case AUTO_MINUS_MODE:// F6--
		case TEACH_PLUS_MODE:  //F5++
		case TEACH_MINUS_MODE:// F6--
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
		 // // case SELF_CUT_MODE://自刀主画面下 
		 case MANUAL_MODE:   //手动
		 case PROG_FLAG_MODE:		//标记 模式
		 case TEACH_FLAG_MODE:		//标记 模式
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
						case INDONSIA:	//印尼
							Printf16("Input data melebihi batas",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,RED_COLOR,0,0xffff);
								break;
						case PORTUGAL:	//葡萄牙
								Printf16("Dados de entrada excede o limite",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,RED_COLOR,0,0xffff);
								break;											
						case SPANISH: //西班牙
								Printf16("Los datos de entrada excede el límite",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,RED_COLOR,0,0xffff);
								break;
						}
					// if(ButtonTouch_mode==TOU_MODE_CALC)   //触摸下
						// {
						ClearCalculatorInput(); //清零计算器 输入
						// }
					return 0;
					}
				else   //正确	 
					{
					PromptNum_dis();//输入范围 提示
					PromptDis_flag=1;
					return 1;
					}	
					break;
		case AUTO_LABEL_MODE://	编程 标签	
		case TEACH_LABEL_MODE:// 示教 标签	
		case AUTO_DIVIDE_MODE://编程 等分
		case TEACH_DIVIDE_MODE://示教 等分
		// // case AUTO_RULER_MODE://自动 基准
		// // case SELF_RULER_MODE://自刀 基准
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
							case INDONSIA:	//印尼
								Printf16("Input data melebihi batas",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,RED_COLOR,0,0xffff);
									break;
							case PORTUGAL:	//葡萄牙
									Printf16("Dados de entrada excede o limite",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,RED_COLOR,0,0xffff);
									break;											
							case SPANISH: //西班牙
									Printf16("Los datos de entrada excede el límite",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,RED_COLOR,0,0xffff);
									break;
							}
						// if(ButtonTouch_mode==TOU_MODE_CALC)   //触摸下
							// {
							ClearCalculatorInput(); //清零计算器 输入
							// }	
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
					if((WorkMode&0x0f)==(AUTO_DIVIDE_MODE&0x0f))  //等分
						{
						if(DivideValue_flag==0)	//等分数
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
							if(InputSize<=Size_MAX_num)   //正确
								{
								PromptNum_dis();//输入范围 提示
								PromptDis_flag=1;
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
									case INDONSIA:	//印尼
										Printf16("Input data melebihi batas",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,RED_COLOR,0,0xffff);
											break;
									case PORTUGAL:	//葡萄牙
											Printf16("Dados de entrada excede o limite",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,RED_COLOR,0,0xffff);
											break;											
									case SPANISH: //西班牙
											Printf16("Los datos de entrada excede el límite",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,RED_COLOR,0,0xffff);
											break;
									}
								return 0;
								}
							}
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
								case INDONSIA:	//印尼
									Printf16("Input data melebihi batas",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,RED_COLOR,0,0xffff);
										break;
								case PORTUGAL:	//葡萄牙
										Printf16("Dados de entrada excede o limite",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,RED_COLOR,0,0xffff);
										break;											
								case SPANISH: //西班牙
										Printf16("Los datos de entrada excede el límite",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,RED_COLOR,0,0xffff);
										break;
								}
							}
						return 0;	
						}
					return 0;	
					}
				return 0;	
					break;
		case READ_PRO_MODE:    //程序选择----------------------
		// // case TEACH_PRO_MODE:    //程序选择----------------------
				if(Unit==UNIT_MM)
					{
					InputSize=temp/100;
					}
				else
					{
					InputSize=temp/1000;
					}
				if((InputSize>0)&&(InputSize<=MAX_PROG))// 有效
					{
					return 1;
					}
				return 0;	
					break;	
					
		// // case AUTO_TOOLS_MODE://自动  参数设置
		// // case SELF_TOOLS_MODE://自刀  参数设置
		case MANUAL_TOOLS_MODE:// 手动 参数模式
				if(PramSel_Page<1)	//page 1
					{
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
					}
				else	//page 2
					{
					
					}
				return 1;	
					break;
		case AUTO_PLUS_MODE:  //F5++
		case AUTO_MINUS_MODE:// F6--
		case TEACH_PLUS_MODE:  //F5++
		case TEACH_MINUS_MODE:// F6--
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

void LabelSel_dis(Int8U sel, Int8U flag) //标签页  设定选择
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
			Printf24("0    ",REMIND_WINDOW_X+180,REMIND_WINDOW_Y+5,RED_COLOR,1,0xffff);
			}
			break;
	case 2://废边	
		ProgSet_dis(Waste_size, WASTE_SIZE_X,  WASTE_SIZE_Y,flag);
		if(flag==1)
			{
			PromptNum_dis();//输入范围
			//PromptDis_flag=1;
			PromptDis_flag=0;
			//GLCD_SetWindow_Fill( REMIND_WINDOW_X, REMIND_WINDOW_Y, REMIND_WINDOW_X+REMIND_LENGTH, REMIND_WINDOW_Y+30, 0xfffff, 0xffff);
			Printf24("0    ",REMIND_WINDOW_X+180,REMIND_WINDOW_Y+5,RED_COLOR,1,0xffff);
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
pbuf=(pInt8U)(K_SIZE_sdram+offset+PRO_HEAD_BYTES+order*5);//程序基地址
add=DATA_SAVE_OFFSET+offset+PRO_HEAD_BYTES+order*5;

OneKnife_data.size=Total_size;  //尺寸修改
OneKnife_data.k_flag=NO_FLAG;  //清除 标志
SaveOneKnife_datas(Pro_data.pro_num, order++ , pKnife_data);//保存一刀数据
data=Total_size;
while(order<=MAX_Knife)
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
RenewModifyDate();	//更新时间信息-.-.-.-.-.-.-.-.-.-.-.-.-.-	
//-----显示
//CurrentArea_recover2(MIDDLE_PAGE_X , MIDDLE_PAGE_Y,  800, 269); //退出 标签画面
//  ------------更新编程 数据 显示
if(order>=OnePro_head.pro_knifeSUM)
   {
   if(order<=MAX_Knife)
      {
	  OnePro_head.pro_knifeSUM=order-1;
	  }
   else
	  {
	  OnePro_head.pro_knifeSUM=MAX_Knife;
	  }
   }
SavePro_headInfo(Pro_data.pro_num, (pInt8U)&OnePro_head);//刀数 保存  
StepNum_dis(OnePro_head.pro_knifeSUM,Knife_order);//步骤更新
Size_1page_dis(Knife_order,cursor_row);	
SaveBuf_datas(Pro_data.pro_num,  Knife_order+1,  order-1); //保存
PromptNum_dis();//输入范围 提示
PromptDis_flag=1;
}

void CursorDown_inTable(void) //**** 光标下移 显示 数据
{
if(Knife_order<=MAX_Knife)
	{
	if(Knife_order>OnePro_head.pro_knifeSUM) //回到 第一刀循环
		{
		CursorKnife_dis(cursor_row, 0);//红色光标消失
		cursor_row=0;
		CursorKnife_dis(cursor_row, 1);//红色光标显示
		Knife_order=1;//
		Size_1page_dis(Knife_order,0);//一页尺寸显示
		}	
	else
		{
		if(Knife_order==OnePro_head.pro_knifeSUM)
			{
			if(AutoRoute_flag==1) //自动 回到 第一刀循环
				{
				CursorKnife_dis(cursor_row, 0);//红色光标消失
				cursor_row=0;
				CursorKnife_dis(cursor_row, 1);//红色光标显示
				Knife_order=1;
				Size_1page_dis(Knife_order,0);//一页尺寸显示
				}
			else
				{
				Knife_order++;
				if(Knife_order<=MAX_Knife)   //999 以内
					{
					if(cursor_row<(PageKf_Size-1))
						{
						CursorKnife_dis(cursor_row, 0);//红色光标消失
						OneKnifeDataSel_dis(Knife_order-1, cursor_row,0);  //一刀数据 高亮显示
						cursor_row++;
						CursorKnife_dis(cursor_row, 1);//红色光标下移显示
						OneKnifeDataSel_dis(Knife_order, cursor_row,RED_COLOR);  //一刀数据 高亮显示
						}
					else   //页底
						{
						Size_1page_dis(Knife_order-(PageKf_Size-1),0);//一页尺寸显示
						}
					}
				else  //999刀  回到 第一刀循环
					{
					CursorKnife_dis(cursor_row, 0);//红色光标消失
					cursor_row=0;
					CursorKnife_dis(cursor_row, 1);//红色光标显示
					Knife_order=1;
					Size_1page_dis(Knife_order,0);//一页尺寸显示
					}
				}
			}
		else
			{
			Knife_order++;
			if(Knife_order<=MAX_Knife)   //999 以内
				{
				if(cursor_row<(PageKf_Size-1))
					{
					CursorKnife_dis(cursor_row, 0);//红色光标消失
					OneKnifeDataSel_dis(Knife_order-1, cursor_row,0);  //一刀数据 高亮显示
					cursor_row++;
					CursorKnife_dis(cursor_row, 1);//红色光标下移显示
					OneKnifeDataSel_dis(Knife_order, cursor_row,RED_COLOR);  //一刀数据 高亮显示
					}
				else   //页底
					{
					Size_1page_dis(Knife_order-(PageKf_Size-1),0);//一页尺寸显示
					}
				}
			else  //999刀  回到 第一刀循环
				{
				CursorKnife_dis(cursor_row, 0);//红色光标消失
				cursor_row=0;
				CursorKnife_dis(cursor_row, 1);//红色光标显示
				Knife_order=1;
				Size_1page_dis(Knife_order,0);//一页尺寸显示
				}
			}
		}
	if(Knife_order<=OnePro_head.pro_knifeSUM+1)
		StepOrder_dis(Knife_order);//步骤更新
	// if(ButtonTouch_mode!=TOU_MODE_F4)
		// {
		// switch(WorkMode)
			// {
			// case AUTO_PLUS_MODE:  //F5++
			// case AUTO_MINUS_MODE:// F6--
			// case SELF_PLUS_MODE://自刀F5++
			// case SELF_MINUS_MODE://自刀 F6--
					// break;
			// default:
				PromptNum_dis();//输入范围
				PromptDis_flag=1;
					// break;
			// }
		// }
	}
}

void PageUpExec(void)	//上翻页
{
Int8U chg_flag=0;
if(Run_flag==0)
	{
	switch(WorkMode)
		{
		
		case TEACH_MODE://示教画面下
		case AUTO_MODE://自动主画面下
		
		case SELF_CUT_MODE://自刀主画面下
		
		case PROG_FLAG_MODE:	//标记 模式
		case TEACH_FLAG_MODE:	//标记 模式
			if(Knife_order>PageKf_Size)
				{
				CursorKnife_dis(cursor_row, 0);//红色光标消失
				cursor_row=0;
				CursorKnife_dis(cursor_row, 1);//红色光标显示
				Knife_order-=PageKf_Size;
				Size_1page_dis(Knife_order,0);//一页尺寸显示
				chg_flag=1;
				}
			else
				{
				if(Knife_order>1)
					{
					CursorKnife_dis(cursor_row, 0);//红色光标消失
					cursor_row=0;
					CursorKnife_dis(cursor_row, 1);//红色光标显示
					Knife_order=1;
					Size_1page_dis(Knife_order,0);//一页尺寸显示
					chg_flag=1;
					}
				}
					break;
		case READ_PRO_MODE:    //程序选择----------------------
		// // case TEACH_PRO_MODE:    //程序选择----------------------
				if(prog_order>PROGS_1PAGE)
					{
					prog_order=prog_order-PROGS_1PAGE-cursor_pro;
					CursorPro_dis(cursor_pro,0);//光标
					cursor_pro=0;
					CursorPro_dis(cursor_pro,1);//
					Prog_1page_dis(prog_order, 0);//===程序---数据显示
					OneProgHeadInfo_dis(cursor_pro ,  prog_order, 1);	//一条程序 显示1
					}
					 break;
		}
	if(chg_flag==1)
		{
		if(Knife_order<=OnePro_head.pro_knifeSUM+1)
			StepOrder_dis(Knife_order);//步骤更新
		// if(ButtonTouch_mode!=TOU_MODE_F4)
			// {
			PromptNum_dis();//输入范围
			PromptDis_flag=1;
			// }
		}
	}	
}
void PageDownExec(void)	//下翻页
{
Int8U chg_flag=0;
Int16U temp;
if(Run_flag==0)
	{
	switch(WorkMode)
		{
		
		case TEACH_MODE://示教画面下
		case AUTO_MODE://自动主画面下
		case SELF_CUT_MODE://自刀主画面下
		
		case PROG_FLAG_MODE:	//标记 模式
		case TEACH_FLAG_MODE:	//标记 模式
			temp=PageKf_Size-1-cursor_row;
			temp+=Knife_order;
			if(temp+PageKf_Size<=OnePro_head.pro_knifeSUM)	//至少 剩余1页 未显示
				{
				CursorKnife_dis(cursor_row, 0);//红色光标消失
				cursor_row=0;
				CursorKnife_dis(cursor_row, 1);//红色光标显示
				Knife_order+=PageKf_Size;
				Size_1page_dis(Knife_order,0);//一页尺寸显示
				chg_flag=1;
				}
			else	//剩下不足一页
				{
				if(temp<OnePro_head.pro_knifeSUM)
					{
					CursorKnife_dis(cursor_row, 0);//红色光标消失
					cursor_row=0;
					CursorKnife_dis(cursor_row, 1);//红色光标显示
					Knife_order=OnePro_head.pro_knifeSUM;
					Size_1page_dis(Knife_order,0);//一页尺寸显示
					chg_flag=1;
					}
				}
					break;
		case READ_PRO_MODE:    //程序选择----------------------
		// // case TEACH_PRO_MODE:    //程序选择----------------------
				temp=prog_order+PROGS_1PAGE-cursor_pro;
				if(temp<=MAX_PROG)
					{
					CursorPro_dis(cursor_pro,0);//光标
					cursor_pro=0;
					CursorPro_dis(cursor_pro,1);//
					prog_order=temp;
					Prog_1page_dis(prog_order, 0);//===程序---数据显示
					OneProgHeadInfo_dis(cursor_pro ,  prog_order, 1);	//一条程序 显示1
					}
					 break;
		}
	if(chg_flag==1)
		{
		if(Knife_order<=OnePro_head.pro_knifeSUM+1)
			StepOrder_dis(Knife_order);//步骤更新
		// if(ButtonTouch_mode!=TOU_MODE_F4)
			// {
			PromptNum_dis();//输入范围
			PromptDis_flag=1;
			// }
		}	
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
			if(DivideValue_flag==0)
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
					case INDONSIA:	//印尼
						Printf24("Rentang nilai      untuk",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,BLACK_COLOR,0,0xffff);
								break;
					case PORTUGAL:	//葡萄牙
						Printf16("Intervalo de dados           --",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,BLACK_COLOR,0,0xffff);
						break;
					}
				Printf24("1         1000",REMIND_WINDOW_X+180,REMIND_WINDOW_Y+5,RED_COLOR,0,0xffff);
				}
			else
				{
				PromptNum_dis();//输入范围
				//PromptDis_flag=1;
				PromptDis_flag=0;
				Printf24("0   ",REMIND_WINDOW_X+180,REMIND_WINDOW_Y+5,RED_COLOR,1,0xffff);
				}
			}
			break;
	}
}

void DivideTypeSelExec(void)	//等分 类型  选择........
{
volatile Int16U x,y,gap;
Int16U back_color=TEXT_TAB_BACK_COLOR; //文本页  背景色
x=TOTAL_SIZE_X-150,y=TOTAL_SIZE_Y,gap=ROW_GAP2;
GLCD_SetWindow_Fill(x,y, x+250,y+gap*2, back_color,back_color);
if(DivideValue_flag==1)	//等分值功能
	{
	//左边
	switch(Language)
		{
		case CHN_HAN:
			Printf24("总长：",x,y,BLACK_COLOR,1,back_color);y+=gap;
			Printf24("等分值：",x,y,BLACK_COLOR,1,back_color);
				break;
		case ENGLISH:	
			Printf24("Total size：",x,y,BLACK_COLOR,1,back_color);y+=gap;
			Printf24("Div-Value：",x,y,BLACK_COLOR,1,back_color);
				break;
		case INDONSIA:	//印尼
			Printf24("Panjangnya：",x,y,BLACK_COLOR,1,back_color);y+=gap;
			Printf24("Aliquots：",x,y,BLACK_COLOR,1,back_color);
				break;
		case PORTUGAL:	//葡萄牙
			Printf24("Total：",x,y,BLACK_COLOR,1,back_color);y+=gap;
			Printf24("Alí    ",x,y,BLACK_COLOR,1,back_color);
			Printf24("   quotas:",x,y,BLACK_COLOR,0,back_color);//Alíquotas
				break;
		}
	}
else		//等分数
	{
	//左边
	switch(Language)
		{
		case CHN_HAN:
			Printf24("总长：",x,y,BLACK_COLOR,1,back_color);y+=gap;
			Printf24("等分数：",x,y,BLACK_COLOR,1,back_color);
				break;
		case ENGLISH:	
			Printf24("Total size：",x,y,BLACK_COLOR,1,back_color);y+=gap;
			Printf24("Div-Num：",x,y,BLACK_COLOR,1,back_color);
				break;
		case INDONSIA:	//印尼
			Printf24("Panjangnya：",x,y,BLACK_COLOR,1,back_color);y+=gap;
			Printf24("Aliquots：",x,y,BLACK_COLOR,1,back_color);
				break;
		case PORTUGAL:	//葡萄牙
			Printf24("Total：",x,y,BLACK_COLOR,1,back_color);y+=gap;
			Printf24("Alí    ",x,y,BLACK_COLOR,1,back_color);
			Printf24("   quotas:",x,y,BLACK_COLOR,0,back_color);//Alíquotas
				break;
		}
	}
Total_size=0;//总长
Divide_num=0;//等分数
PorgSet_sel=0;
ProgSet_dis( 0, DIVIDE_TOTAL_X,  DIVIDE_TOTAL_Y,1);//
PorgSet_sel=1;
ProgSet_dis( 0, DIVIDE_NUM_X,  DIVIDE_NUM_Y,0);
PorgSet_sel=0;
PromptNum_dis();//输入范围
PromptDis_flag=1;
SubModeIcon_dis(WorkMode);   //等分模式
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
								// // CalcuInClear_exec();     //清除 计算器
							ClearCalculatorInput(); //清零计算器 输入
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
								// // CalcuInClear_exec();     //清除 计算器
							ClearCalculatorInput(); //清零计算器 输入
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
								// // CalcuInClear_exec();     //清除 计算器
							ClearCalculatorInput(); //清零计算器 输入
							}
						}
					}
				else
					num_cou=0;
					break; 
	}
	
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
								// // CalcuInClear_exec();     //清除 计算器
							ClearCalculatorInput(); //清零计算器 输入
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
								// // CalcuInClear_exec();     //清除 计算器
							ClearCalculatorInput(); //清零计算器 输入	
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
// if(ButtonTouch_mode==0)  //	 非 触摸计算器 下	
	// ClrInput_function();//清零 输入框 		
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
pbuf=(pInt8U)(K_SIZE_sdram+offset+PRO_HEAD_BYTES+order*5);//程序基地址
add=DATA_SAVE_OFFSET+offset+PRO_HEAD_BYTES+order*5;

OneKnife_data.size=Total_size;  //尺寸修改
OneKnife_data.k_flag=NO_FLAG;  //清除 标志
SaveOneKnife_datas(Pro_data.pro_num, order++ , pKnife_data);//保存一刀数据
if(DivideValue_flag==0)
	{
	data=Total_size;
	d_size=Total_size/Divide_num;
	}
else
	{
	data=Total_size;
	d_size=Divide_num;
	}
while(order<=MAX_Knife)
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
RenewModifyDate();	//更新时间信息-.-.-.-.-.-.-.-.-.-.-.-.-.-
//-----显示
//CurrentArea_recover2(MIDDLE_PAGE_X , MIDDLE_PAGE_Y,  800, 269); //退出 标签画面
//  ------------更新编程 数据 显示
if(order>=OnePro_head.pro_knifeSUM)
   {
   if(order<=MAX_Knife)
      {
	  OnePro_head.pro_knifeSUM=order-1;
	  }
   else
	  {
	  OnePro_head.pro_knifeSUM=MAX_Knife;
	  }
   }
SavePro_headInfo(Pro_data.pro_num, (pInt8U)&OnePro_head);//刀数 保存  
StepNum_dis(OnePro_head.pro_knifeSUM,Knife_order);//步骤更新
Size_1page_dis(Knife_order,cursor_row);	
SaveBuf_datas(Pro_data.pro_num, Knife_order+1,  order-1); //保存
PromptNum_dis();//输入范围 提示
PromptDis_flag=1;
}


void ProEnter_exec(void)  //程序选择 输入确认
{
Int32U temp,i;
if(CheckInputNums()==1)// 有效
   {
	ClearCalculatorInput(); //清零计算器 输入// // CalcuInClear_exec();     //清除 计算器
	
	if(ProNumGroup[prog_order]!=InputSize)	//判断 程序 号码
		{
		for(i=1;i<=MAX_PROG;i++)
			{
			if(ProNumGroup[i]==InputSize)
				{
				prog_order=i;
				break;
				}
			}
		}	
	//----光标 跳转
	//prog_order=InputSize;//当前 程序号
	temp=prog_order%PROGS_1PAGE;
	CursorPro_dis(cursor_pro,0);//光标
	if(temp<1)
	   temp=PROGS_1PAGE;
	cursor_pro=temp-1;
	  
	CursorPro_dis(cursor_pro,1);//
	Prog_1page_dis(prog_order-temp+1, 0);//===程序---数据显示
	OneProgHeadInfo_dis(cursor_pro ,  prog_order, 1);	//一条程序 显示1
   }
else
   {
   num_cou=0;
  // PromptDis_flag=0;
  // GLCD_SetWindow_Fill( REMIND_WINDOW_X, REMIND_WINDOW_Y, REMIND_WINDOW_X+360, REMIND_WINDOW_Y+30, 0xfffff, 0xffff);//提示框
//	Printf24("输入数值范围出错!",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,RED_COLOR,0,0xffff);
   }
// if(ButtonTouch_mode==0)  //	 非 触摸计算器 下
	// ClrInput_function();//清零 输入框   
}

void ExportOnePro_dis(Int16U p_order) //更新 显示一个程序-------------
{
Int16U prog;
Int16U x1,x2,y1,y2,back_color=TEXT_TAB_BACK_COLOR;//0xef9f;
pInt8U pdata;
KNIFE_DATA Knife_datas;

// // CurrentArea_recover2(MIDDLE_PAGE_X , MIDDLE_PAGE_Y, M_PAGE_WIDE, M_PAGE_HIGH);
// // ClrSizeTable_dis();//刀数据 列表空白
AutoModePage_dis(); //自动模式 部分画面显示
//************当前pro 参数
prog=ProNumGroup[p_order];
Pro_data.pro_num=prog;
pdata=(pInt8U)&Pro_data;
SavePro_data(pdata);
if(prog<=PROG_GROPU1)//前 300个pro
   {
   MAX_Knife=MAX_KNIFE1;//999
   }
else
   {
   MAX_Knife=MAX_KNIFE2;//399
   } 
//ReadOnePro_datas(prog);//读取 当前pro
ClrBuf_datas(prog, 1,MAX_Knife);  //清零 刀数据buf
GetPro_headInfo(prog,(pInt8U)&OnePro_head); //获取前程序 刀数
 // OnePro_head.pro_knifeSUM=6;
ReadOnePro_datas(prog);//读取 一个pro

CheckKnifeSum_exec();  //--------------总刀数    核对
Knife_sum_before=OnePro_head.pro_knifeSUM;
//---------程序有效 更新时间
//GetOneKnife_datas(prog, 1 , (pInt8U)&Knife_datas);//取出一刀 数据
// if(Knife_datas.size>0)
	// {
	RenewModifyDate();	//更新时间信息-.-.-.-.-.-.-.-.-.-.-.-.-.-
	// }
//-------------更新 显示
cursor_pro=0;
Knife_order=1;
cursor_row=0;     // 在首行 显示 箭头
Size_1page_dis(Knife_order, 0);  
CursorKnife_dis(cursor_row,1);//红色箭头  
OneProNum_dis(prog, OnePro_head);// 程序号 
StepNum_dis(OnePro_head.pro_knifeSUM,Knife_order);// 步骤号  总刀数-序号

PromptDis_flag=1;
PromptNum_dis();
LastAutoKnife_order=1;
}

void ReorderProByDate_dis(void)	//(按时间排序) 程序列表
{
Int16U p,	l,t,flag;
volatile Int32U date[MAX_PROG+2],temp;
pInt8U pdata;
PROCESS_HEAD pro_Head;

pdata=(pInt8U)&pro_Head;
DisAllProgMode=PRO_BY_TIME;
ProTableIcon_dis();	//程序列表模式下 icon显示
for(p=1;p<=MAX_PROG;p++)
	{
	GetPro_headInfo(ProNumGroup[p],  pdata);//sdram 读一个程序头(程序名+ 时间 +刀数 )
	date[p]=(pro_Head.pro_year<<16)|(pro_Head.pro_month<<8)|pro_Head.pro_day;
	}
/****	
for(l=1;l<MAX_PROG;l++)
	{
	for(t=l+1;t<=MAX_PROG;t++)		//选择法
		{
		if(date[t]>date[l])
			{
			temp=date[t];
			date[t]=date[l];
			date[l]=temp;
			
			temp=ProNumGroup[t];
			ProNumGroup[t]=ProNumGroup[l];
			ProNumGroup[l]=temp;
			}
		}
	}
	***/
for(l=1;l<MAX_PROG;l++)
	{
	flag=0;
	for(t=1;t<=MAX_PROG-l;t++)		//冒泡法
		{
		if(date[t]<date[t+1])
			{
			flag=1;
			temp=date[t];
			date[t]=date[t+1];
			date[t+1]=temp;
			
			temp=ProNumGroup[t];
			ProNumGroup[t]=ProNumGroup[t+1];
			ProNumGroup[t+1]=temp;
			}
		}
	if(flag==0)
		break;
	}

//--------显示
prog_order=1;
CursorPro_dis(cursor_pro,0);//pro光标
cursor_pro=0;
Prog_1page_dis(prog_order, cursor_pro);//= 一页程序---数据显示
TableDis_startcol=PROC_NUM_X;
CursorPro_dis(cursor_pro,1);//pro光标
OneProgHeadInfo_dis(cursor_pro ,  prog_order, 1);	//一条程序 显示
//ClrInput_function();//清零 输入框
}

void DeleteOneProg(Int8U cursor, Int16U p_order)		//F4 ----删除一个程序
{
//PROCESS_HEAD pro_head;
// GetPro_headInfo(ProNumGroup[p_order],  (pInt8U)&Pro_head_temp);//sdram 读一个程序头(程序名+ 时间 +刀数 )
//清除信息头并保存 head_info=0
SavePro_headInfo(ProNumGroup[p_order], (pInt8U)&ProHead_default);
//清除4刀数据并保存
ClrBuf_datas(ProNumGroup[p_order], 1,4);
SaveBuf_datas(ProNumGroup[p_order], 1,4); 
//从新 显示
OneProgHeadInfo_dis(cursor,  p_order, 1);	//一条程序 显示1
if(ProNumGroup[p_order]==Pro_data.pro_num)	//当前程序 已打开
	{
	//====更新当前程序 信息OnePro_head
	GetPro_headInfo(Pro_data.pro_num,  (pInt8U)&OnePro_head);//sdram 读一个程序头(程序名+ 时间 +刀数 )
	Knife_sum_before=OnePro_head.pro_knifeSUM;	//步骤清除=1
	//-----步骤--更新 显示
	OneProNum_dis(Pro_data.pro_num, OnePro_head);// 程序号 
	Knife_order=1;
	StepNum_dis(OnePro_head.pro_knifeSUM,Knife_order);// 步骤号  总刀数-序号
	}
}
void DeleteAllProg(void)	//(Int8U cursor, Int16U p_order)		//F5--- 删除所有程序
{
Int16U c=1;
Int8U row=0;
//********************删除前  提示***********
GLCD_SetWindow_Fill( REMIND_WINDOW_X, REMIND_WINDOW_Y, REMIND_WINDOW_X+REMIND_LENGTH, REMIND_WINDOW_Y+30, 0xfffff, 0xffff);//提示框
switch(Language)
		{
		case CHN_HAN:
				Printf24("正在删除,需要6秒...",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,BLACK_COLOR,0,0xffff);
						break;
		case ENGLISH:	
				Printf24("Deleting,Please wait",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,BLACK_COLOR,0,0xffff);
						break;
		case INDONSIA:	//印尼
				Printf24("Menghapus, silakan tunggu",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,BLACK_COLOR,0,0xffff);
						break;
		case PORTUGAL:	//葡萄牙
				Printf24("Apagando, 6 segundo",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,BLACK_COLOR,0,0xffff);
						break;
		}
while(c<=MAX_PROG)	//清除信息头并保存 head_info=0
	{
	SavePro_headInfo(c, (pInt8U)&ProHead_default);
	//清除4刀数据并保存
	ClrBuf_datas(c, 1,2);
	SaveBuf_datas(c, 1,2); 
	//-------------------------程序列表
	ProNumGroup[c]=c;
	c++;
	}
//********************删除结束  提示***********
GLCD_SetWindow_Fill( REMIND_WINDOW_X, REMIND_WINDOW_Y, REMIND_WINDOW_X+REMIND_LENGTH, REMIND_WINDOW_Y+30, 0xfffff, 0xffff);//提示框
switch(Language)
		{
		case CHN_HAN:
				Printf24("输入数值范围        到",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,BLACK_COLOR,0,0xffff);
						break;
		case ENGLISH:	
				Printf24("Data range          to",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,BLACK_COLOR,0,0xffff);
						break;
		case INDONSIA:	//印尼
				Printf24("Rentang nilai      untuk",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,BLACK_COLOR,0,0xffff);
						break;
		case PORTUGAL:	//葡萄牙
			Printf16("Intervalo de dados           --",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,BLACK_COLOR,0,0xffff);
			break;
		}
Printf24("1         500",REMIND_WINDOW_X+180,REMIND_WINDOW_Y+5,RED_COLOR,0,0xffff);

/**
//包括当前程序 则更新当前 显示----------------------
// if(Pro_data.pro_num>=ProNumGroup[p_order])
	// {
//====更新当前程序 信息OnePro_head
**/
GetPro_headInfo(Pro_data.pro_num,  (pInt8U)&OnePro_head);//sdram 读一个程序头(程序名+ 时间 +刀数 )
Knife_sum_before=OnePro_head.pro_knifeSUM;	//步骤清除=1
//-----步骤--更新 显示
OneProNum_dis(Pro_data.pro_num, OnePro_head);// 程序号 
Knife_order=1;
StepNum_dis(OnePro_head.pro_knifeSUM,Knife_order);// 步骤号  总刀数-序号

//	程序列表 更新显示-------------------------
CursorPro_dis(cursor_pro,0);//光标0
cursor_pro=0;
CursorPro_dis(cursor_pro,1);//

prog_order=1;
Prog_1page_dis(prog_order, 0);//===程序---数据显示
OneProgHeadInfo_dis(cursor_pro,  prog_order, 1);	//一条程序 显示1
}



void F5_AutoAdd_exec(Int32U add_data)  //F5++  批量数据 自加
{
Int16U order;
Int32U data;
Int16U ord_temp;

order=Knife_order;
pKnife_data=(pInt8U)&OneKnife_data;
GetOneKnife_datas(Pro_data.pro_num, order, pKnife_data);
data=OneKnife_data.size+add_data;
ord_temp=cursor_row;

if((data<=Size_MAX_num)&&(data>=Size_MIN_num)) //范围 内
	{
	PromptNum_dis();//输入范围 提示
	PromptDis_flag=1;
	OneKnife_data.size=data;
	SaveOneKnife_datas(Pro_data.pro_num, order++ , pKnife_data);//保存一刀数据
	
	while(order<=OnePro_head.pro_knifeSUM)
		{
		//pKnife_data=(pInt8U)&OneKnife_data;
		GetOneKnife_datas(Pro_data.pro_num, order-1, pKnife_data);//上一刀
		data=OneKnife_data.size;
		GetOneKnife_datas(Pro_data.pro_num, order, pKnife_data);//当前刀
		
		if(OneKnife_data.size>data-add_data)
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
	//SavePro_headInfo(Pro_data.pro_num);//刀数 保存 
	StepNum_dis(OnePro_head.pro_knifeSUM,order);//步骤更新
	if(order-Knife_order+cursor_row>(PageKf_Size-1)) //下页
		{
		CursorKnife_dis(cursor_row, 0);//红色光标消失
		cursor_row=0;
		CursorKnife_dis(cursor_row, 1);//红色光标显示
		Size_1page_dis(order,cursor_row);	
		}
	else
		{
		CursorKnife_dis(cursor_row, 0);//红色光标消失
		cursor_row+=order-Knife_order;
		CursorKnife_dis(cursor_row, 1);//红色光标显示	
		Size_1page_dis(Knife_order,ord_temp);	//
		}	
	SaveBuf_datas(Pro_data.pro_num, Knife_order+1,  order); //保存
	Knife_order=order;
	PromptNum_dis();//输入范围 提示	
	PromptDis_flag=1;
	RenewModifyDate();	//更新时间信息-.-.-.-.-.-.-.-.-.-.-.-.-.-
	}
}

void F6_AutoSub_exec(Int32U add_data)  //F6--  批量数据 自减
{
Int16U order;
Int32U data;
Int16U ord_temp;

order=Knife_order;
pKnife_data=(pInt8U)&OneKnife_data;
GetOneKnife_datas(Pro_data.pro_num, order, pKnife_data);
ord_temp=cursor_row;
if(OneKnife_data.size>add_data)
  {
  data=OneKnife_data.size-add_data;
  if((data<=Size_MAX_num)&&(data>=Size_MIN_num)) //范围 内
	 {
	 PromptNum_dis();//输入范围 提示
	 PromptDis_flag=1;
	 OneKnife_data.size=data;
	 SaveOneKnife_datas(Pro_data.pro_num, order++ , pKnife_data);//保存一刀数据
	
	 while(order<=OnePro_head.pro_knifeSUM)
		{
		//pKnife_data=(pInt8U)&OneKnife_data;
		GetOneKnife_datas(Pro_data.pro_num, order-1, pKnife_data);//上一刀
		data=OneKnife_data.size;
		GetOneKnife_datas(Pro_data.pro_num, order, pKnife_data);//当前刀
		if(OneKnife_data.size>data+add_data)
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
	 //SavePro_headInfo(Pro_data.pro_num);//刀数 保存 
	 StepNum_dis(OnePro_head.pro_knifeSUM,order);//步骤更新
	 if(order-Knife_order+cursor_row>(PageKf_Size-1)) //下页
		{
		CursorKnife_dis(cursor_row, 0);//红色光标消失
		cursor_row=0;
		CursorKnife_dis(cursor_row, 1);//红色光标显示
		Size_1page_dis(order,cursor_row);	
		}
	 else
		{
		CursorKnife_dis(cursor_row, 0);//红色光标消失
		cursor_row+=order-Knife_order;
		CursorKnife_dis(cursor_row, 1);//红色光标显示	
		Size_1page_dis(Knife_order,ord_temp);	
		}	
 	 SaveBuf_datas(Pro_data.pro_num, Knife_order+1,  order); //保存
	 Knife_order=order;
	 PromptNum_dis();//输入范围 提示
	 PromptDis_flag=1;
	 RenewModifyDate();	//更新时间信息-.-.-.-.-.-.-.-.-.-.-.-.-.-
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
if(Language>3)
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
	AutoPushDistance=0;	//10000;20180917
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
if(MotorType>MOTOR_AC_A6_SERVO)
	MotorType=MOTOR_FREQ_3_SPD_RST;	//0  ------变频器3挡
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
Int32U add;Int16U n;
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

void ReadAirOffDistance(void)	//关气阀 距离
{
Int16U n;
Int32U add;
pInt8U pdata;
add=ORIGINAL_25PEADD+110;
pdata=(pInt8U)&AirOffDistance;
FastRead_Datas_Start(add);
for(n=0;n<4;n++)
	{
	*pdata++=ReadFlash_Datas();
	}
FlashChip_Dis;
if((AirOffDistance>1000)||(AirOffDistance<100))
	AirOffDistance=0;
}
void SaveAirOffDistance(void)	//关气阀 距离
{
Int16U n;
Int32U add;
pInt8U pdata;
add=ORIGINAL_25PEADD+110;
pdata=(pInt8U)&AirOffDistance;
Write_25pe_data(pdata, add, 4);
}

void ReadElectricWheelSwitch(void)//电子手轮
{
Int32U add;
// pInt8U pdata;
add=ORIGINAL_25PEADD+115;
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
add=ORIGINAL_25PEADD+115;
pdata=(pInt8U)&ElectricWheelOn_flag;
Write_25pe_data(pdata, add, 1);
}

void ReadIRValidStatus(void)	//IR set
{
Int32U add;
// pInt8U pdata;
add=ORIGINAL_25PEADD+116;
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
add=ORIGINAL_25PEADD+116;
pdata=(pInt8U)&IR_SensorStus;
Write_25pe_data(pdata, add, 1);
}


void ReadPageKf_Size(void)	//每页 刀数据
{
Int32U add;
add=ORIGINAL_25PEADD+117;
FastRead_Datas_Start(add);
PageKf_Size_flag=ReadFlash_Datas();
FlashChip_Dis;
if(PageKf_Size_flag>1)
	PageKf_Size_flag=0;
}
void SavePageKf_Size(void)
{
Int32U add;
pInt8U pdata;
add=ORIGINAL_25PEADD+117;
pdata=(pInt8U)&PageKf_Size_flag;
Write_25pe_data(pdata, add, 1);
}


void ReadStepDistance(void) // 步进距离
{
pInt8U pdata;
Int8U n;
Int32U add;
pdata=(pInt8U)&Step_Size;
add=ORIGINAL_25PEADD+118;
FastRead_Datas_Start(add);
for(n=0;n<4;n++)
	{
	*pdata++=ReadFlash_Datas();
	}
FlashChip_Dis;
if(Step_Size>MAX_STEP_SIZE)
	Step_Size=1000;
}
void SaveStepDistance(void) // 步进距离
{
Int32U add;
pInt8U pdata;
add=ORIGINAL_25PEADD+118;
pdata=(pInt8U)&Step_Size;
Write_25pe_data(pdata, add, 4);
}

void ReadCurrentPulseAB(void)		//	当前脉冲 当量
{
pInt8U pdata;	
Int8U n;
Int32U add;
pdata=(pInt8U)&PulseAB_Z_current;
add=ORIGINAL_25PEADD+122;
FastRead_Datas_Start(add);
for(n=0;n<4;n++)
	{
	*pdata++=ReadFlash_Datas();
	}
FlashChip_Dis;
if(PulseAB_Z_current>0xffff)
	PulseAB_Z_current=0;
}
void SaveCurrentPulseAB(void)		//	当前脉冲 当量
{
pInt8U pdata;	
Int8U n;
Int32U add;
pdata=(pInt8U)&PulseAB_Z_current;
add=ORIGINAL_25PEADD+122;
Write_25pe_data(pdata, add, 4);
}

void ReadVirtualTargetSizeGap(void)		//虚拟目标值
{
pInt8U pdata;	
Int8U n;
Int32U add;
pdata=(pInt8U)&VirtualTargetSizeGap;
add=ORIGINAL_25PEADD+126;
FastRead_Datas_Start(add);
for(n=0;n<4;n++)
	{
	*pdata++=ReadFlash_Datas();
	}
FlashChip_Dis;
if((VirtualTargetSizeGap>100)||(VirtualTargetSizeGap<30))	//	20171017屏蔽
	{
	VirtualTargetSizeGap=40;
	}
// if(MotorType!=MOTOR_FREQ_3_SPD_RST)
	// VirtualTargetSizeGap=40;
}
void SaveVirtualTargetSizeGap(void)
{
pInt8U pdata;	
Int8U n;
Int32U add;
pdata=(pInt8U)&VirtualTargetSizeGap;
add=ORIGINAL_25PEADD+126;
Write_25pe_data(pdata, add, 4);
}

void ReadIRChgWorkmodeValid(void)	//红外切换工作模式标记
{
pInt8U pdata;	
Int8U n;
Int32U add;
add=ORIGINAL_25PEADD+135;
FastRead_Datas_Start(add);	
IRChgWorkmodeValid_flag=ReadFlash_Datas();
FlashChip_Dis;
if(IRChgWorkmodeValid_flag!=1)
	IRChgWorkmodeValid_flag=0;
}
void SaveIRChgWorkmodeValid(void)	//
{
pInt8U pdata;	
Int8U n;
Int32U add;
pdata=(pInt8U)&IRChgWorkmodeValid_flag;
add=ORIGINAL_25PEADD+135;
Write_25pe_data(pdata, add, 1);	
}
void ReadA6MarkBenchSize(void)//A6 编码器 基准值(6 Byte)
{
pInt8U pdata;	
Int8U n;
Int32U add;
pdata=(pInt8U)&Modbus_A6_JiZhunDesmion;
add=ORIGINAL_25PEADD+130;
FastRead_Datas_Start(add);
for(n=0;n<4;n++)
	{
	*pdata++=ReadFlash_Datas();
	}
pdata=(pInt8U)&Modbus_A6_JiZhunQuan;	
for(n=0;n<2;n++)
	{
	*pdata++=ReadFlash_Datas();
	}
FlashChip_Dis;
}
void SaveA6MarkBenchSize(void)//A6 编码器 基准值(6 Byte)
{
pInt8U pdata;	
Int8U n;
Int32U add;
pdata=(pInt8U)&Modbus_A6_JiZhunDesmion;
add=ORIGINAL_25PEADD+130;
Write_25pe_data(pdata, add, 4);	
pdata=(pInt8U)&Modbus_A6_JiZhunQuan;
Write_25pe_data(pdata, add+4, 2);	
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
Int8U go_flag=0;

pKdata=(pInt8U)&OneKnife_data;
GetOneKnife_datas(Pro_data.pro_num, Knife_order, pKdata);//
size_data=OneKnife_data.size;
if((size_data>=Size_MIN_num)&&(size_data<=Size_MAX_num))//数据有效
	{
	//SelfLockEn_flag=0;
	//ToTargetStop_flag=0;
	//if(1)
	if(InTargetPosit_flag==1)
		{
		if(Unit==UNIT_MM)//mm
			{
			if(size_data!=TargetSize)
				{
				go_flag=1;
				}
			else
				{
				go_flag=2;
				}
			}
		else
			{
			if(size_data!=TargetSize_inch)
				{
				go_flag=1;
				}
			else
				{
				go_flag=2;
				}
			}
		}
	else
		{
		if(size_data!=CurrentSize)
			{
			go_flag=1;
			}
		}
	//------
	if(go_flag == 1)
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
		if(((OneKnife_data.k_flag&0x0f)==PUSH_FLAG)&&(Knife_order<OnePro_head.pro_knifeSUM))//推纸 位置提前10mm 结束
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
		//-----------------偏移量运行控制----------
		if(CutPressRoll_flag==1)	//裁切循环 模式
			{
			if(AmendStartRun_flag==1)
				{
				if(AmendPlus_flag == 1)
					TargetSize +=AmendSize;
				else
					TargetSize-=AmendSize;
				}
			}
		else	//直接key运行----取消 ---偏移量 运行控制
			{	
			if(AmendStartRun_flag==1)
				{
				AmendStartRun_flag=0;
				AmendSize=0;
				//----------更新 显示F6
				// AmendSwitch_flag=0;
				// AmendButtonFlag_dis();
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
			// // case MOTOR_DC_SERVO:
			// // case MOTOR_DC670_SERVO:
				 // // ServoSendCou=0;
				 // // DcServoStartRun_exec(TargetSize);
				// // // SelfLockEn_flag=0;
					// // break;
			case MOTOR_AC_SERVO:
			case MOTOR_AC_SERVO_REV:
			case MOTOR_AC_A6_SERVO:
				ACMotorRunStart(TargetSize);
					break;		
			}
		RunStop_flag=0;
		Run_flag=1;
		InTargetPosit_flag=0;	//目标位置
		AutoCutStart_flag=0;
		AirOffOK_flag=0;
		PressUp_flag=0;
		PressDown_flag=0;
		PromptNum_dis();
		}
	// else if(go_flag==2)
		// {
		// AutoRun_AutoPush_exec();  // 自动 向下循环运行
		// }
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
		AutoRun_AutoPush_exec();  // 自动 向下循环运行
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
	CurrentToCalc_input();  //当前-1尺寸 数据更新到计算器
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
							// // case MOTOR_DC_SERVO:
							// // case MOTOR_DC670_SERVO:
								 // // ServoSendCou=0;
								 // // DcServoStartRun_exec(TargetSize);
								// // // SelfLockEn_flag=0;
									// // break;
							case MOTOR_AC_SERVO:
							case MOTOR_AC_SERVO_REV:
							case MOTOR_AC_A6_SERVO:
								 ACMotorRunStart(TargetSize);
									break;		
							}
						Run_flag=1;
						RunStop_flag=0;
						InTargetPosit_flag=0;	//目标位置
						AutoPushRun_flag=1;
						AutoCutStart_flag=0;
						AirOffOK_flag=0;
						PressUp_flag=0;
						PressDown_flag=0;
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
					if(((OneKnife_data.k_flag&0x0f)==PUSH_FLAG)&&(Knife_order<OnePro_head.pro_knifeSUM))// 位置提前10mm 结束
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
							// // case MOTOR_DC_SERVO:
							// // case MOTOR_DC670_SERVO:
								// // ServoSendCou=0;
								 // // DcServoStartRun_exec(TargetSize);
								// // // SelfLockEn_flag=0;
									// // break;
							case MOTOR_AC_SERVO:
							case MOTOR_AC_SERVO_REV:
							case MOTOR_AC_A6_SERVO:
								ACMotorRunStart(TargetSize);
								// SelfLockEn_flag=0;
									break;
							}
						Run_flag=1;
						RunStop_flag=0;
						InTargetPosit_flag=0;	//目标位置
						AutoPushRun_flag=1;
						AutoCutStart_flag=0;
						//AirOffOK_flag=0;
						CursorDown_inTable();//**** 光标下移 显示 数据
						PromptNum_dis();

						}
					}
				}
			}
		else//直接  运行到 下一刀
			{
			
			//-------------------偏移量 运行控制------------------------------------------------------11111
			if(CutPressRoll_flag==1)	//裁切循环 模式
				{
				if(AmendSwitch_flag==1)
					{
					if(AmendOver_flag==0)
						{
						if(size_data>CurrentSize)	//负向偏移偏移量保存
							{
							AmendPlus_flag=0;
							AmendSize=size_data-CurrentSize;
							}
						else		//正向
							{
							AmendPlus_flag=1;
							AmendSize=CurrentSize-size_data;
							}
						AmendStartRun_flag=1;
						}
					else
						{
						AmendSize=0;
						AmendStartRun_flag=0;
						}
					}
				}
			CursorDown_inTable();//**** 光标下移 显示 数据
			RunTo_cursor();//    运行到下一刀
			
			AutoPushRun_flag=0;
			}
		}
	}
else   //直接  运行到 下一刀
	{
	//-------------------偏移量 运行控制------------------------------------------------------11111
	GetOneKnife_datas(Pro_data.pro_num, Knife_order, pKdata);//
	size_data=OneKnife_data.size;
	GetOneKnife_datas(Pro_data.pro_num, Knife_order+1, pKdata);//
	if(size_data>OneKnife_data.size)	//下一刀<当前
		{
		if(CutPressRoll_flag==1)	//裁切循环 模式
			{
			if(AmendSwitch_flag==1)
				{
				if(AmendOver_flag==0)
					{
					if(size_data>CurrentSize)	//负向偏移偏移量保存
						{
						AmendPlus_flag=0;
						AmendSize=size_data-CurrentSize;
						}
					else		//正向
						{
						AmendPlus_flag=1;
						AmendSize=CurrentSize-size_data;
						}
					AmendStartRun_flag=1;
					}
				else
					{
					AmendSize=0;
					AmendStartRun_flag=0;
					}
				}
			}
		}
	else	//下一刀>当前
		{
		if(AmendStartRun_flag==1)	//取消 ---偏移量 运行控制
			{
			AmendStartRun_flag=0;
			AmendSize=0;
			//----------更新 显示F6
			// AmendSwitch_flag=0;
			// AmendButtonFlag_dis();
			}
		}
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
GetOneKnife_datas(Pro_data.pro_num, OnePro_head.pro_knifeSUM, pKdata);//读取 最后一刀
size_data=OneKnife_data.size;
if((size_data>=Size_MIN_num)&&(size_data<=Size_MAX_num))  //当前尺寸  有效  （往下查找）-----这种情况  无影响
	{
	knife_temp=OnePro_head.pro_knifeSUM+1;
	while(knife_temp<=MAX_Knife)
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
		
	if(knife_temp>OnePro_head.pro_knifeSUM+1)//刀数不对  更新
		{
		OnePro_head.pro_knifeSUM=knife_temp-1;
		SavePro_headInfo(Pro_data.pro_num, (pInt8U)&OnePro_head);//刀数 保存  
		if(WorkStart_flag==1)
			StepNum_dis(OnePro_head.pro_knifeSUM,Knife_order);//步骤更新
		}
	}
else	//尺寸无效   （往上查找）
	{
	knife_temp=OnePro_head.pro_knifeSUM-1;
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
		if(OnePro_head.pro_knifeSUM!=1)
			{
			OnePro_head.pro_knifeSUM=1;
			SavePro_headInfo(Pro_data.pro_num, (pInt8U)&OnePro_head);//刀数 保存  
			ClrBuf_datas(Pro_data.pro_num, 1,MAX_Knife);  //清零 刀数据buf
			ReadOnePro_datas(Pro_data.pro_num);//读取 当前pro
			if(WorkStart_flag==1)
				StepNum_dis(OnePro_head.pro_knifeSUM,Knife_order);//步骤更新
			}
		}
	else
		{
		OnePro_head.pro_knifeSUM=knife_temp;
		SavePro_headInfo(Pro_data.pro_num, (pInt8U)&OnePro_head);//刀数 保存
		ClrBuf_datas(Pro_data.pro_num, 1,MAX_Knife);  //清零 刀数据buf
		ReadOnePro_datas(Pro_data.pro_num);//读取 当前pro
		if(WorkStart_flag==1)
			StepNum_dis(OnePro_head.pro_knifeSUM,Knife_order);//步骤更新
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
	//************20180516		fast	
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




void DeleteAllData_hintWind(void)	//删除所有数据  提示框
{
Int16U line_color,fill_color;
//------------
CurrentArea_save1(DEL_ALL_WIN_X,DEL_ALL_WIN_Y, DEL_ALL_WIN_WIDE,DEL_ALL_WIN_HIGH);
line_color=RED_COLOR,fill_color=PRO_MESS_COLOR1;
GLCD_SetWindow_Fill(DEL_ALL_WIN_X, DEL_ALL_WIN_Y,DEL_ALL_WIN_X+DEL_ALL_WIN_WIDE-1 ,DEL_ALL_WIN_Y+DEL_ALL_WIN_HIGH-1 , line_color, fill_color);
fill_color=BLUE_COLOR;
switch(Language)
	{
	case CHN_HAN:
		Printf24("是否删除全部数据?",DEL_ALL_HINT_X,DEL_ALL_HINT_Y,BLACK_COLOR,0,fill_color);
		Printf24("确定",DEL_ALL_OK_X,DEL_ALL_OK_Y,BLACK_COLOR,1,fill_color);
		Printf24("取消",DEL_ALL_CANCEL_X,DEL_ALL_CANCEL_Y,BLACK_COLOR,1,fill_color);
			break;
	case ENGLISH:	
		Printf24("Delete all the data?",DEL_ALL_HINT_X,DEL_ALL_HINT_Y,BLACK_COLOR,0,fill_color);
		Printf24("OK",DEL_ALL_OK_X,DEL_ALL_OK_Y,BLACK_COLOR,1,fill_color);
		Printf24("Cancel",DEL_ALL_CANCEL_X,DEL_ALL_CANCEL_Y,BLACK_COLOR,1,fill_color);
			break;
	case INDONSIA:	//印尼
		Printf16("Apakah akan menghapus semua data",DEL_ALL_HINT_X,DEL_ALL_HINT_Y,BLACK_COLOR,0,fill_color);
		Printf24("Ya",DEL_ALL_OK_X,DEL_ALL_OK_Y,BLACK_COLOR,1,fill_color);
		Printf24("Membatal",DEL_ALL_CANCEL_X,DEL_ALL_CANCEL_Y,BLACK_COLOR,1,fill_color);
			break;
	case PORTUGAL:	//葡萄牙
		Printf16("Seja para excluir todos os dados",DEL_ALL_HINT_X,DEL_ALL_HINT_Y,BLACK_COLOR,0,fill_color);
		Printf24("OK",DEL_ALL_OK_X,DEL_ALL_OK_Y,BLACK_COLOR,1,fill_color);
		Printf24("Cancelar",DEL_ALL_CANCEL_X,DEL_ALL_CANCEL_Y,BLACK_COLOR,1,fill_color);
			break;
	}
switch(WorkMode)
	{
	case READ_PRO_MODE:
			WorkMode=READ_DEL_ALL_PRO_MODE;
			break;
	case TEACH_PRO_MODE:
			// WorkMode=TEACH_DEL_ALL_PRO_MODE;
			break;
	// case PROG_MODE:
			// WorkMode=PROG_DEL_ALL_SIZE_MODE;
			// break;
	case TEACH_MODE:
			WorkMode=TEACH_DEL_ALL_SIZE_MODE;
			break;		
	case AUTO_MODE:
			WorkMode=AUTO_DEL_ALL_SIZE_MODE; 
				break;
	}	
}
void DeleteAllExitWind(void)	//退出全删 提示框
{
CurrentArea_recover1(DEL_ALL_WIN_X,DEL_ALL_WIN_Y, DEL_ALL_WIN_WIDE,DEL_ALL_WIN_HIGH);
switch(WorkMode)
	{
	case READ_DEL_ALL_PRO_MODE:
			WorkMode=READ_PRO_MODE;
			break;
	// // case TEACH_DEL_ALL_PRO_MODE:
			// // WorkMode=TEACH_PRO_MODE;
			// // break;
	// // case PROG_DEL_ALL_SIZE_MODE:
			// // WorkMode=PROG_MODE;
			// // break;
	case TEACH_DEL_ALL_SIZE_MODE:
			WorkMode=TEACH_MODE;
			break;		
	case AUTO_DEL_ALL_SIZE_MODE:
			WorkMode=AUTO_MODE;
			break;		
	}
}

void F5_KeyExec(void)//F5  处理 
{
if(WorkStart_flag==1)
    {
	if(Run_flag==0)
		{
		// if(ButtonTouch_mode==0)//未有  弹出页
			// {
			switch(WorkMode)
				{
				
				case READ_PRO_MODE:
				// // case TEACH_PRO_MODE:	//程序列表 模式
						DeleteAllData_hintWind();	//删除所有数据  提示框
							break;
				case AUTO_MODE:
						WorkMode=AUTO_PLUS_MODE;  //F5++
						F5_plus_dis(1);//  ++	
							break;
				case AUTO_PLUS_MODE:  //F5++		
						WorkMode=AUTO_MODE;//返回
						PaperCutEnb_signal=1;
						PressCircle_mode=0;
						F5_plus_dis(0);
							break;
				case TEACH_MODE:
						WorkMode=TEACH_PLUS_MODE;  //F5++
						F5_plus_dis(1);//  ++	
							break;
				case TEACH_PLUS_MODE:  //F5++		
						WorkMode=TEACH_MODE;//返回
						PaperCutEnb_signal=1;
						PressCircle_mode=0;
						F5_plus_dis(0);
							break;
				case MANUAL_MODE:
						if(MotorType<MOTOR_AC_SERVO)    //变频器--
							{
							 WorkMode=MANUAL_PULSE_MODE;
							 PulseDegreePage_dis();
							 PromptDis_flag=0;
							 // // ClrInput_function();//清零 输入框
							 Para_sel=Pulse_degree;	//脉冲当量 设定
							 }
							break;
							
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
				// // case MOTOR_DC_SERVO:
				// // case MOTOR_DC670_SERVO:
					// // DCServoStop();  //停止运行
					// // ServoPressStop_flag=0;
					// // DcServoGoTarget_flag=0;
					// // BellStart_flag=0;
					// // //************
					// // Run_flag=0;	
					// // InTargetPosit_flag=0;	//目标位置
					// // AutoPushRun_flag=0; //自动推纸 运行
					// // TargetSize=0;
					// // TargetSize_temp=0;
					// // BeforeKnife_offset_in=0;
					// // AutoRoute_flag=0;
						// // break;
				case MOTOR_AC_SERVO:
				case MOTOR_AC_SERVO_REV:
				case MOTOR_AC_A6_SERVO:
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
			
			// if(ButtonTouch_mode==0)
				// ClrInput_function();//清零 输入框	
			}		
		}
    }
else 
	{
	if(Board_TestMod==TEST_HELP)
		{
		PageLineSet_dis();  //每页行数 ****************************
		Board_TestMod=TEST_PAGE_LINE;   
		}
	else if(Board_TestMod==TEST_PAGE_LINE)
		{
		StartHelpMode_dis();
		Board_TestMod=TEST_HELP;
		}
	}
}

void F6_KeyExec(void)//F6  处理
{
if(WorkStart_flag==1)
   {
	if(Run_flag==0)
		{
		// if(ButtonTouch_mode==0)//未有  弹出页
			// {
			switch(WorkMode)
				{
				// case PROG_PRO_MODE:		//F3 程序模式
						// WorkMode=PROG_MODE;//------------------退出返回到编程主 画面
						// //PorgSet_sel=0;
						// CurrentArea_recover2(MIDDLE_PAGE_X , MIDDLE_PAGE_Y,  M_PAGE_WIDE, M_PAGE_HIGH);
						// SubModeIcon_dis(WorkMode);   //编程 模式name
						// if(Knife_order==1)// ----程序已被删除---------
							// {
							// //------------返回第一刀
							// ClrInput_function();//清零 输入框 
							// CursorKnife_dis(cursor_row, 0);//红色光标消失
							// cursor_row=0;
							// CursorKnife_dis(cursor_row, 1);//红色光标显示
							// Size_1page_dis(Knife_order,0);//一页尺寸显示
							// }
							
						// PromptNum_dis();//输入范围
						// PromptDis_flag=1;
						// PaperCutEnb_signal=1;
						// ACServoAlarmExec_flag=0;
						// break;
				case TEACH_PRO_MODE:		//F3 程序模式
						WorkMode=TEACH_MODE;//------------------退出返回到示教主 画面
						//PorgSet_sel=0;
						CurrentArea_recover2(MIDDLE_PAGE_X , MIDDLE_PAGE_Y,  M_PAGE_WIDE, M_PAGE_HIGH);
						SubModeIcon_dis(WorkMode);   //模式name
						if(Knife_order==1)// ----程序已被删除---------
							{
							//------------返回第一刀
							ClrInput_function();//清零 输入框 
							CursorKnife_dis(cursor_row, 0);//红色光标消失
							cursor_row=0;
							CursorKnife_dis(cursor_row, 1);//红色光标显示
							Size_1page_dis(Knife_order,0);//一页尺寸显示
							}
							
						PromptNum_dis();//输入范围
						PromptDis_flag=1;
						PaperCutEnb_signal=1;
						ACServoAlarmExec_flag=0;
						break;	
				case AUTO_MODE:
						// // if(MotorType>=MOTOR_AC_SERVO)
							// // {
							// // if(ElectricWheelOn_flag==1)	//手轮  有效时
								// // {
								// // AmendSwitch_flag=!AmendSwitch_flag;
								// // if(AmendSwitch_flag==0)
									// // {
									// // AmendStartRun_flag=0;
									// // AmendSize=0;
									// // }
								// // AmendButtonFlag_dis();	//F6修改数据偏移量
								// // }
							// // }
							WorkMode=AUTO_MINUS_MODE;// F6--
							F6_minus_dis(1);//--
						break;	
				case AUTO_MINUS_MODE:// F6--		 
							WorkMode=AUTO_MODE;//返回
							PaperCutEnb_signal=1;
							PressCircle_mode=0;
							F6_minus_dis(0);
							break;	
				case TEACH_MODE:
							WorkMode=TEACH_MINUS_MODE;// F6--
							F6_minus_dis(1);//--
						break;	
				case TEACH_MINUS_MODE:// F6--		 
							WorkMode=TEACH_MODE;//返回
							PaperCutEnb_signal=1;
							PressCircle_mode=0;
							F6_minus_dis(0);
							break;
				case MANUAL_MODE:
						Para_sel=0;
						PromptDis_flag=0;
						ACServoAlarmExec_flag=0;
						
						WorkMode=MANUAL_IO_TEST_MODE;//---------------io测试模式
						SubModeIcon_dis(WorkMode); //IO mode name
						F6_TestIO_dis();
						break;	
				}	
			// }
		// else if(ButtonTouch_mode==TOU_MODE_CALC)  //计算器 弹出模式
			// {
			
			// }
		// else if(ButtonTouch_mode==TOU_MODE_F4)  // 标记 弹出框		F6  退出标记 显示
			// {
			// Set_AllFlagWind_Exit(FlagTouRow_num-1);	//退出标记  显示
			// ClrInput_function();//清零 输入框	
			// }
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
				// // case MOTOR_DC_SERVO:
				// // case MOTOR_DC670_SERVO:
					// // DCServoStop();  //停止运行
					// // ServoPressStop_flag=0;
					// // DcServoGoTarget_flag=0;
					// // BellStart_flag=0;
					// // //************
					// // Run_flag=0;	
					// // InTargetPosit_flag=0;	//目标位置
					// // AutoPushRun_flag=0; //自动推纸 运行
					// // TargetSize=0;
					// // TargetSize_temp=0;
					// // BeforeKnife_offset_in=0;
					// // AutoRoute_flag=0;
						// // break;
				case MOTOR_AC_SERVO:
				case MOTOR_AC_SERVO_REV:
				case MOTOR_AC_A6_SERVO:
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
			
			// if(ButtonTouch_mode==0)
				// ClrInput_function();//清零 输入框	
			}		
		}
   }

}

void AllFlagSetExec(Int8U flag) //F4 标记设定  处理................
{
volatile Int16U first_num,last_num;
Int16U knife_begin,knife_end;
pInt8U pbuf;
Int32U offset;
Int32U size_temp,size_now,knife_temp=0;
Int8U renew_flag=0;
// // if(ButtonTouch_mode==TOU_MODE_F4)  // 标记 弹出框
	// // Set_AllFlagWind_Exit(FlagTouRow_num-1);	//退出标记框  

pKnife_data=(pInt8U)&OneKnife_data;
if((LastKnife_num_temp!=FirstKnife_num)&&(LastKnife_num_temp>0))		//  批量数据
	{
	if(LastKnife_num_temp>FirstKnife_num)
		{
		first_num=FirstKnife_num;
		last_num=LastKnife_num_temp;
		}
	else
		{
		first_num=LastKnife_num_temp;
		last_num=FirstKnife_num;
		}
		
	if(first_num<=OnePro_head.pro_knifeSUM)//范围有效
		{
		knife_begin=first_num;
		if(last_num<OnePro_head.pro_knifeSUM)
			knife_end=last_num;
		else
			knife_end=OnePro_head.pro_knifeSUM;
		if(Pro_data.pro_num<=(PROG_GROPU1+1))  //前301个prog
		   {
		   offset=PROG_BYTES1*(Pro_data.pro_num-1);
		   }
		else//后  199
		   {
		   offset=PROG_BYTES1*PROG_GROPU1+(Pro_data.pro_num-PROG_GROPU1-1)*PROG_BYTES2;
		   }
		pbuf=(pInt8U)(K_SIZE_sdram+offset+PRO_HEAD_BYTES+(knife_begin-1)*5+4);//程序基地址
		
		GetOneKnife_datas(Pro_data.pro_num, knife_begin, pKnife_data);//
		// // if(OneKnife_data.size>0)
			// // {
			// // }
		//-----------------先判断当前是否 已有标记
		switch(flag)
			{
			case PUSH_FLAG:		//推纸 标志
			case SORT_FLAG:	  // 理纸
			case PRESS_FLAG:    // 压纸
				if((OneKnife_data.k_flag&0x0f)!=flag) //设定 标志
					{
					while(knife_begin<=knife_end)
						{
						*pbuf&=0xf0;
						*pbuf|=flag;
						pbuf+=5;
						knife_begin++;
						renew_flag=1;
						}		
					}
				else	// 清除 标志
					{
					while(knife_begin<=knife_end)
						{
						*pbuf&=0xf0;
						pbuf+=5;
						knife_begin++;
						renew_flag=1;
						}
					}
					break;
			case AIR_FLAG:      //气垫
				if((OneKnife_data.k_flag&0xf0)!=flag) //
					{
					while(knife_begin<=knife_end)
						{
						*pbuf&=0x0f;
						*pbuf|=flag;
						pbuf+=5;
						knife_begin++;
						renew_flag=1;
						}	
					}
				else
					{
					while(knife_begin<=knife_end)
						{
						*pbuf&=0x0f;
						pbuf+=5;
						knife_begin++;
						renew_flag=1;
						}
					}
					break;
			case  KNIFE_FLAG:     //刀  标志
				if(knife_begin<2)	//修正---- 使从第二刀 开始
					{
					//pbuf=(pInt8U)(K_SIZE_sdram+offset+PRO_HEAD_BYTES+knife_begin*5+4);//程序基地址
					GetOneKnife_datas(Pro_data.pro_num, 2, pKnife_data);//  ----从第2刀判断
					}
				if((OneKnife_data.k_flag&0x0f)!=flag) //设定 标志
					{
					if(knife_begin<2)	//修正---- 使从第二刀 开始
						{
						 knife_begin=2;
						 pbuf=(pInt8U)(K_SIZE_sdram+offset+PRO_HEAD_BYTES+(knife_begin-1)*5+4);//程序基地址
						size_now=0xffffffff;
						}
					else
						{
						GetOneKnife_datas(Pro_data.pro_num, knife_begin-1, pKnife_data);//前 一刀
						size_now=OneKnife_data.size;
						}
					//------------
					while(knife_begin<=knife_end)
						{
						size_temp=size_now;
						GetOneKnife_datas(Pro_data.pro_num, knife_begin, pKnife_data);//当前 刀
						size_now=OneKnife_data.size;
						if(size_now<size_temp)//小于 前一刀
							{
							*pbuf&=0xf0;
							*pbuf|=flag;	//KNIFE_FLAG;
							//OneKnife_data.k_flag=KNIFE_FLAG;  
							//SaveOneKnife_datas(Pro_data.pro_num,knife , pKnife_data);//保存一刀数据
							//*pbuf=*(pKnife_data+4);
							}
						pbuf+=5;
						knife_begin++;
						renew_flag=1;
						}
					}
				else	//去除 所有刀 标记
					{
					//------------
					while(knife_begin<=knife_end)
						{
						GetOneKnife_datas(Pro_data.pro_num, knife_begin, pKnife_data);//当前 刀
						if((OneKnife_data.k_flag&0x0f)==flag) //
							{
							*pbuf&=0xf0;
							}
						pbuf+=5;
						knife_begin++;
						renew_flag=1;
						}
					}
					break;
			}
		
		//****************更新  显示区
		if(renew_flag==1)
			{
			RenewModifyDate();	//更新时间信息-.-.-.-.-.-.-.-.-.-.-.-.-.-
			// SaveBuf_datas(Pro_data.pro_num, 1, OnePro_head.pro_knifeSUM );//保存
			SaveBuf_datas(Pro_data.pro_num, first_num, knife_end);//保存
			//------------返回第一刀
			//ClrInput_function();//清零 输入框 
			CursorKnife_dis(cursor_row, 0);//红色光标消失
			cursor_row=0;
			CursorKnife_dis(cursor_row, 1);//红色光标显示
			Knife_order=1;//
			Size_1page_dis(Knife_order,0);//一页尺寸显示
			if(Knife_order<=OnePro_head.pro_knifeSUM)
				StepOrder_dis(Knife_order);//步骤更新	
			// if((WorkMode==PROG_FLAG_MODE)||(WorkMode==TEACH_FLAG_MODE))//标记 模式
				// AllFlagRemind();	//F4 标记模式提示	
			}
		}
	}
else//单个 标记	+====当前光标处
	{
	if(SubLine_flag==0)
		{
		if(num_cou>0)
			{
			if(CheckInputNums()==1)// 输入 有效	
				knife_temp=InputSize;  //尺寸修改
			num_cou=0;
			}
		}
	
	GetOneKnife_datas(Pro_data.pro_num, Knife_order, pKnife_data);
	if(knife_temp>0)
		{
		OneKnife_data.size=knife_temp;
		renew_flag=1;
		}
	if(OneKnife_data.size>0)
		{
		switch(flag)
			{
			case PUSH_FLAG:		//推纸 标志
			case SORT_FLAG:	  // 理纸
			case PRESS_FLAG:    // 压纸
				if((OneKnife_data.k_flag&0x0f)!=flag) //
					{
					OneKnife_data.k_flag&=0xf0;
					OneKnife_data.k_flag|=flag;//  设定 标志
					}
				else
					{
					OneKnife_data.k_flag&=0xf0;// 清除 标志
					}
				renew_flag=1;
					break;
			case AIR_FLAG:      //气垫
				if((OneKnife_data.k_flag&0xf0)!=flag) //
					{
					OneKnife_data.k_flag&=0x0f;
					OneKnife_data.k_flag|=flag;//  设定 标志
					}
				else
					{
					OneKnife_data.k_flag&=0x0f;// 清除 标志
					}
				renew_flag=1;
					break;
			case  KNIFE_FLAG:     //刀  标志	
				if(Knife_order>1)
					{
					GetOneKnife_datas(Pro_data.pro_num, Knife_order-1, pKnife_data);//前 一刀
					size_temp=OneKnife_data.size;
					GetOneKnife_datas(Pro_data.pro_num, Knife_order, pKnife_data);//当前 尺寸
					if(knife_temp>0)
						{
						OneKnife_data.size=knife_temp;
						renew_flag=1;
						}
					if(OneKnife_data.size<size_temp)
						{
						if((OneKnife_data.k_flag&0x0f)!=flag) //
							{
							OneKnife_data.k_flag&=0xf0;
							OneKnife_data.k_flag|=flag;//  设定 标志
							}
						else
							{
							OneKnife_data.k_flag&=0xf0;// 清除 标志
							}
						renew_flag=1;
						}
					}
					break;
			}
		if(renew_flag==1)
			{
			RenewModifyDate();	//更新时间信息-.-.-.-.-.-.-.-.-.-.-.-.-.-
			AllFlagPic_dis(cursor_row,OneKnife_data.k_flag); //显示----
			if(knife_temp>0)
				{
				if(Knife_order>OnePro_head.pro_knifeSUM)//更新步骤 总刀数
					{
					OnePro_head.pro_knifeSUM=Knife_order;		//
					//SavePro_headInfo(Pro_data.pro_num, (pInt8U)&OnePro_head);
					}
				KnifeSize_dis(cursor_row, knife_temp, RED_COLOR);//-------------- 更新显示一个尺寸
				}
			SaveOneKnife_datas(Pro_data.pro_num, Knife_order , pKnife_data);//保存一刀数据
			// OneKnifeDataSel_dis(Knife_order, cursor_row,RED_COLOR);  //一刀数据 高亮显示
			// PromptNum_dis();//输入范围
			// PromptDis_flag=1;
			
			//---------显示----	
			if(Knife_order<MAX_Knife)	//刀数据 未满---------------下移
				{
				Knife_order++;
				if(cursor_row<(PageKf_Size-1))
					{
					CursorKnife_dis(cursor_row, 0);//红色光标消失
					OneKnifeDataSel_dis(Knife_order-1, cursor_row,0);  //一刀数据 高亮消失
					cursor_row++;
					CursorKnife_dis(cursor_row, 1);//红色光标下移显示
					OneKnifeDataSel_dis(Knife_order, cursor_row,RED_COLOR);  //一刀数据 高亮显示
					}
				else   //页底
					{
					Size_1page_dis(Knife_order-(PageKf_Size-1),0);//一页尺寸显示
					}
				}
			StepNum_dis(OnePro_head.pro_knifeSUM,Knife_order);//步骤更新
			
			// if((WorkMode==PROG_FLAG_MODE)||(WorkMode==TEACH_FLAG_MODE))//标记 模式
				// AllFlagRemind();	//F4 标记模式提示
			}
		}
	}
// // ClrInput_function();//清零 输入框	
LastKnife_num_temp=FirstKnife_num=0;
}

void AllKnifeFlagExec(Int8U dis)	//添加，清除 --所有刀标记
{
Int16U knife;
pInt8U pbuf;
Int32U offset,size_temp;
Int8U chg_flag=0;
//-----------
pKnife_data=(pInt8U)&OneKnife_data;
if(dis==1)//添加 刀标记
	{
	if(OnePro_head.pro_knifeSUM>1)
		{
		knife=2;
		if(Pro_data.pro_num<=(PROG_GROPU1+1))  //前301个prog
		   {
		   offset=PROG_BYTES1*(Pro_data.pro_num-1);
		   }
		else//后  199
		   {
		   offset=PROG_BYTES1*PROG_GROPU1+(Pro_data.pro_num-PROG_GROPU1-1)*PROG_BYTES2;
		   }
		pbuf=(pInt8U)(K_SIZE_sdram+offset+PRO_HEAD_BYTES+(knife-1)*5+4);//程序基地址
		//***********
		GetOneKnife_datas(Pro_data.pro_num, knife-1, pKnife_data);//前 1刀
		while(knife<=OnePro_head.pro_knifeSUM)
			{
			size_temp=OneKnife_data.size;
			GetOneKnife_datas(Pro_data.pro_num, knife, pKnife_data);//当前 刀
			if(OneKnife_data.size<size_temp)
				{
				*pbuf&=0xf0;
				*pbuf|=KNIFE_FLAG;     //刀  标志
				chg_flag=1;
				}
			pbuf+=5;	
			knife++;
			}
		}
	}
else	//清除 刀标记
	{
	knife=1;
	if(Pro_data.pro_num<=(PROG_GROPU1+1))  //前301个prog
	   {
	   offset=PROG_BYTES1*(Pro_data.pro_num-1);
	   }
	else//后  199
	   {
	   offset=PROG_BYTES1*PROG_GROPU1+(Pro_data.pro_num-PROG_GROPU1-1)*PROG_BYTES2;
	   }
	pbuf=(pInt8U)(K_SIZE_sdram+offset+PRO_HEAD_BYTES+(knife-1)*5+4);//程序基地址
	//**************
	while(knife<=OnePro_head.pro_knifeSUM)
		{
		GetOneKnife_datas(Pro_data.pro_num, knife, pKnife_data);//当前 刀
		if((OneKnife_data.k_flag&0x0f)==KNIFE_FLAG)   //刀  标志
			{
			*pbuf&=0xf0;
			chg_flag=1;
			}
		pbuf+=5;	
		knife++;	
		}
	}
if(chg_flag==1)
	{
	chg_flag=0;
	RenewModifyDate();	//更新时间信息-.-.-.-.-.-.-.-.-.-.-.-.-.-
	//****************更新  显示区
	SaveBuf_datas(Pro_data.pro_num, 1, OnePro_head.pro_knifeSUM );//保存
	//------------返回第一刀 
	CursorKnife_dis(cursor_row, 0);//红色光标消失
	cursor_row=0;
	CursorKnife_dis(cursor_row, 1);//红色光标显示
	Knife_order=1;//
	Size_1page_dis(Knife_order,0);//一页尺寸显示
	if(Knife_order<=OnePro_head.pro_knifeSUM)
		StepOrder_dis(Knife_order);//步骤更新	
	// AllFlagRemind();	//F4 标记模式提示
	}
}


void ProMessageModify_mode(Int16U p_order)	//程序信息修改 模式
{
Int16U x1,y1,x2,y2,gap_x=40,gap_y=180;
Int16U line_color,fill_color;
Int8U nums[45],n=0,check=0;
pInt8U pName;

InputMode=PINYIN_INPUT;
SubModeIcon_dis(WorkMode);   //输入法 模式
//------------
CurrentArea_save1(PRO_MESS_X,PRO_MESS_Y, PRO_MESS_WIDE,PRO_MESS_HIGH);
//-----------左页
line_color=fill_color=PRO_MESS_COLOR1;
x1=PRO_MESS_X,y1=PRO_MESS_Y;
x2=x1+(PRO_MESS_WIDE/2),y2=y1+PRO_MESS_HIGH-1;
GLCD_SetWindow_Fill(x1, y1, x2, y2, line_color, fill_color);
//-----------右页
line_color=fill_color=PRO_MESS_COLOR2;
x1=x2;
x2=PRO_MESS_X+PRO_MESS_WIDE-1;
GLCD_SetWindow_Fill(x1, y1, x2, y2, line_color, fill_color);
//------------间隔
x2=x1;
line_color=0;
GLCD_DrawLine(x1, y1+30, x2, y2-30, line_color);
//-------------外框
line_color=BLUE_COLOR;
x1=PRO_MESS_X,y1=PRO_MESS_Y;
x2=x1+PRO_MESS_WIDE-1,y2=y1+PRO_MESS_HIGH-1;
GLCD_SetWindow(x1,y1,x2,y2,line_color);
GetPro_headInfo(ProNumGroup[p_order],  (pInt8U)&Pro_head_temp);//sdram 读一个程序头(程序名+ 时间 +刀数 )
	//****************************************
// InputMode=CHAR_INPUT;
InputStus_dis(InputMode);	//输入法  选择
ClrNameWindow();
//-----------TOUCH KEY
for(n=0;n<=24;n++)
	{
	InputKEY_BUTT_dis(n, 0); //触摸 按钮 显示
	}

//---------------------------提示输入程序名-----------
GLCD_SetWindow_Fill( REMIND_WINDOW_X, REMIND_WINDOW_Y, REMIND_WINDOW_X+REMIND_LENGTH, REMIND_WINDOW_Y+30, 0xfffff, 0xffff);//提示框
switch(Language)
	{
	case CHN_HAN:
		Printf24("输入文字,更改程序名",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,BLACK_COLOR,0,0xffff);
		break;
	case ENGLISH:	
		Printf24("Modify the program name",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,BLACK_COLOR,0,0xffff);
		break;
	case INDONSIA:	//印尼
		Printf24("Memodifikasi nama program",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,BLACK_COLOR,0,0xffff);
		break;
	case PORTUGAL:	//葡萄牙
		Printf24("Digite o texto, muda o nome",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,BLACK_COLOR,0,0xffff);
		break;
	}
}




void PageKf_Size_Init(void)	//每页 刀数初始化
{
ReadPageKf_Size();
switch(PageKf_Size_flag)
	{
	case PAGE_5_LINE: //5 line 
			PageKf_Size=5;
			Kf_Line_HIGH=60;//75//行高
			break;
	case PAGE_7_LINE: //5 line 
			PageKf_Size=7;
			Kf_Line_HIGH=40;//45;//行高
			break;
	}
}


void AllFlagSetExec_Calc(Int8U flag) //计算器 标记设定  处理................
{
volatile Int16U first_num,last_num;
Int16U knife_begin,knife_end;
pInt8U pbuf;
Int32U offset;
Int32U size_temp,size_now,knife_temp=0;
Int8U renew_flag=0;


pKnife_data=(pInt8U)&OneKnife_data;
if((LastKnife_num_temp!=FirstKnife_num)&&(LastKnife_num_temp>0))		//  批量数据
	{
	if(LastKnife_num_temp>FirstKnife_num)
		{
		first_num=FirstKnife_num;
		last_num=LastKnife_num_temp;
		}
	else
		{
		first_num=LastKnife_num_temp;
		last_num=FirstKnife_num;
		}
		
	if(first_num<=OnePro_head.pro_knifeSUM)//范围有效
		{
		knife_begin=first_num;
		if(last_num<OnePro_head.pro_knifeSUM)
			knife_end=last_num;
		else
			knife_end=OnePro_head.pro_knifeSUM;
		if(Pro_data.pro_num<=(PROG_GROPU1+1))  //前301个prog
		   {
		   offset=PROG_BYTES1*(Pro_data.pro_num-1);
		   }
		else//后  199
		   {
		   offset=PROG_BYTES1*PROG_GROPU1+(Pro_data.pro_num-PROG_GROPU1-1)*PROG_BYTES2;
		   }
		pbuf=(pInt8U)(K_SIZE_sdram+offset+PRO_HEAD_BYTES+(knife_begin-1)*5+4);//程序基地址
		
		GetOneKnife_datas(Pro_data.pro_num, knife_begin, pKnife_data);//
		// // if(OneKnife_data.size>0)
			// // {
			// // }
		//-----------------先判断当前是否 已有标记
		switch(flag)
			{
			case PUSH_FLAG:		//推纸 标志
			case SORT_FLAG:	  // 理纸
			case PRESS_FLAG:    // 压纸
				if((OneKnife_data.k_flag&0x0f)!=flag) //设定 标志
					{
					while(knife_begin<=knife_end)
						{
						*pbuf&=0xf0;
						*pbuf|=flag;
						pbuf+=5;
						knife_begin++;
						renew_flag=1;
						}		
					}
				else	// 清除 标志
					{
					while(knife_begin<=knife_end)
						{
						*pbuf&=0xf0;
						pbuf+=5;
						knife_begin++;
						renew_flag=1;
						}
					}
					break;
			case AIR_FLAG:      //气垫
				if((OneKnife_data.k_flag&0xf0)!=flag) //
					{
					while(knife_begin<=knife_end)
						{
						*pbuf&=0x0f;
						*pbuf|=flag;
						pbuf+=5;
						knife_begin++;
						renew_flag=1;
						}	
					}
				else
					{
					while(knife_begin<=knife_end)
						{
						*pbuf&=0x0f;
						pbuf+=5;
						knife_begin++;
						renew_flag=1;
						}
					}
					break;
			case  KNIFE_FLAG:     //刀  标志
				if(knife_begin<2)	//修正---- 使从第二刀 开始
					{
					//pbuf=(pInt8U)(K_SIZE_sdram+offset+PRO_HEAD_BYTES+knife_begin*5+4);//程序基地址
					GetOneKnife_datas(Pro_data.pro_num, 2, pKnife_data);//  ----从第2刀判断
					}
				if((OneKnife_data.k_flag&0x0f)!=flag) //设定 标志
					{
					if(knife_begin<2)	//修正---- 使从第二刀 开始
						{
						 knife_begin=2;
						 pbuf=(pInt8U)(K_SIZE_sdram+offset+PRO_HEAD_BYTES+(knife_begin-1)*5+4);//程序基地址
						size_now=0xffffffff;
						}
					else
						{
						GetOneKnife_datas(Pro_data.pro_num, knife_begin-1, pKnife_data);//前 一刀
						size_now=OneKnife_data.size;
						}
					//------------
					while(knife_begin<=knife_end)
						{
						size_temp=size_now;
						GetOneKnife_datas(Pro_data.pro_num, knife_begin, pKnife_data);//当前 刀
						size_now=OneKnife_data.size;
						if(size_now<size_temp)//小于 前一刀
							{
							*pbuf&=0xf0;
							*pbuf|=flag;	//KNIFE_FLAG;
							//OneKnife_data.k_flag=KNIFE_FLAG;  
							//SaveOneKnife_datas(Pro_data.pro_num,knife , pKnife_data);//保存一刀数据
							//*pbuf=*(pKnife_data+4);
							}
						pbuf+=5;
						knife_begin++;
						renew_flag=1;
						}
					}
				else	//去除 所有刀 标记
					{
					//------------
					while(knife_begin<=knife_end)
						{
						GetOneKnife_datas(Pro_data.pro_num, knife_begin, pKnife_data);//当前 刀
						if((OneKnife_data.k_flag&0x0f)==flag) //
							{
							*pbuf&=0xf0;
							}
						pbuf+=5;
						knife_begin++;
						renew_flag=1;
						}
					}
					break;
			}
		
		//****************更新  显示区
		if(renew_flag==1)
			{
			RenewModifyDate();	//更新时间信息-.-.-.-.-.-.-.-.-.-.-.-.-.-
			// SaveBuf_datas(Pro_data.pro_num, 1, OnePro_head.pro_knifeSUM );//保存
			SaveBuf_datas(Pro_data.pro_num, first_num, knife_end);//保存
			//------------返回第一刀
			//ClrInput_function();//清零 输入框 
			CursorKnife_dis(cursor_row, 0);//红色光标消失
			cursor_row=0;
			CursorKnife_dis(cursor_row, 1);//红色光标显示
			Knife_order=1;//
			Size_1page_dis(Knife_order,0);//一页尺寸显示
			if(Knife_order<=OnePro_head.pro_knifeSUM)
				StepOrder_dis(Knife_order);//步骤更新	
			// if((WorkMode==PROG_FLAG_MODE)||(WorkMode==TEACH_FLAG_MODE))//标记 模式
			// AllFlagRemind();	//F4 标记模式提示	
			}
		}
	}
else//单个 标记	+====当前光标处
	{
	if(SubLine_flag==0)
		{
		if(num_cou>0)
			{
			if(CheckInputNums()==1)// 输入 有效	
				knife_temp=InputSize;  //尺寸修改
			num_cou=0;
			}
		}
		
	//--------计算器 消失--
	// CalcuInClear_exec();     //清除 计算器	180917
	
	GetOneKnife_datas(Pro_data.pro_num, Knife_order, pKnife_data);
	if(knife_temp>0)
		{
		OneKnife_data.size=knife_temp;
		renew_flag=1;
		}
	if(OneKnife_data.size>0)
		{
		switch(flag)
			{
			case PUSH_FLAG:		//推纸 标志
			case SORT_FLAG:	  // 理纸
			case PRESS_FLAG:    // 压纸
				if((OneKnife_data.k_flag&0x0f)!=flag) //
					{
					OneKnife_data.k_flag&=0xf0;
					OneKnife_data.k_flag|=flag;//  设定 标志
					}
				else
					{
					OneKnife_data.k_flag&=0xf0;// 清除 标志
					}
				renew_flag=1;
					break;
			case AIR_FLAG:      //气垫
				if((OneKnife_data.k_flag&0xf0)!=flag) //
					{
					OneKnife_data.k_flag&=0x0f;
					OneKnife_data.k_flag|=flag;//  设定 标志
					}
				else
					{
					OneKnife_data.k_flag&=0x0f;// 清除 标志
					}
				renew_flag=1;
					break;
			case  KNIFE_FLAG:     //刀  标志	
				if(Knife_order>1)
					{
					GetOneKnife_datas(Pro_data.pro_num, Knife_order-1, pKnife_data);//前 一刀
					size_temp=OneKnife_data.size;
					GetOneKnife_datas(Pro_data.pro_num, Knife_order, pKnife_data);//当前 尺寸
					if(knife_temp>0)
						{
						OneKnife_data.size=knife_temp;
						renew_flag=1;
						}
					if(OneKnife_data.size<size_temp)
						{
						if((OneKnife_data.k_flag&0x0f)!=flag) //
							{
							OneKnife_data.k_flag&=0xf0;
							OneKnife_data.k_flag|=flag;//  设定 标志
							}
						else
							{
							OneKnife_data.k_flag&=0xf0;// 清除 标志
							}
						renew_flag=1;
						}
					}
					break;
			}
		if(renew_flag==1)
			{
			RenewModifyDate();	//更新时间信息-.-.-.-.-.-.-.-.-.-.-.-.-.-
			AllFlagPic_dis(cursor_row,OneKnife_data.k_flag); //显示----
			if(knife_temp>0)
				{
				if(Knife_order>OnePro_head.pro_knifeSUM)//更新步骤 总刀数
					{
					OnePro_head.pro_knifeSUM=Knife_order;		//
					//SavePro_headInfo(Pro_data.pro_num, (pInt8U)&OnePro_head);
					}
				KnifeSize_dis(cursor_row, knife_temp, RED_COLOR);//-------------- 更新显示一个尺寸
				}
			SaveOneKnife_datas(Pro_data.pro_num, Knife_order , pKnife_data);//保存一刀数据
			// OneKnifeDataSel_dis(Knife_order, cursor_row,RED_COLOR);  //一刀数据 高亮显示
			// PromptNum_dis();//输入范围
			// PromptDis_flag=1;
			
			//---------显示----	
			if(Knife_order<MAX_Knife)	//刀数据 未满---------------下移
				{
				Knife_order++;
				if(cursor_row<(PageKf_Size-1))
					{
					CursorKnife_dis(cursor_row, 0);//红色光标消失
					OneKnifeDataSel_dis(Knife_order-1, cursor_row,0);  //一刀数据 高亮消失
					cursor_row++;
					CursorKnife_dis(cursor_row, 1);//红色光标下移显示
					OneKnifeDataSel_dis(Knife_order, cursor_row,RED_COLOR);  //一刀数据 高亮显示
					}
				else   //页底
					{
					Size_1page_dis(Knife_order-(PageKf_Size-1),0);//一页尺寸显示
					}
				}
			StepNum_dis(OnePro_head.pro_knifeSUM,Knife_order);//步骤更新
			
			// if((WorkMode==PROG_FLAG_MODE)||(WorkMode==TEACH_FLAG_MODE))//标记 模式
				// AllFlagRemind();	//F4 标记模式提示
			}
		}
	}
// // ClrInput_function();//清零 输入框	
LastKnife_num_temp=FirstKnife_num=0;
}

