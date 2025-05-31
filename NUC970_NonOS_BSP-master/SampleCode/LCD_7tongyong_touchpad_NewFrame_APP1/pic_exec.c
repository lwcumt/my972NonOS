

#include "pic_exec.h"


//#include"realtime.h"

#include"bmp.h"
#include"file.h"
#include"word_lib.h"

#include"servo.h"
#include"chndot.h"
#include"key.h"
#include"port.h"
#include"name_input.h"


unsigned int  DisWuCha;


Int16U cursor_row;//光标 位置(行)
Int16U  TableDis_startcol;//起始列

Int16U Knife_order; //当前刀号
Int16U Knife_sum;//总刀数
Int16U Knife_sum_before;//总刀数  校正
Int16U MAIX_Knife;//最多刀数

//Int16U Process_num;//当前程序 号
//Int16U MaixProcess_num;//最大 程序号

PROG_SEG Pro_data;//程序 段 号


unsigned char PorgSet_sel;

unsigned char BeforeKnifeNo_flag;

unsigned short WorkMode;

Int32U CurrentSize;
Int32U BeforeKnifeSize;
Int32U BeforeKnife_offset;
Int32U BeforeKnife_offset_in;
Int32U OriginalSize;//原点
Int32U CurrentSize_temp;

Int8U Unit;//单位
Int8U Language;//语言
Int8U PressValid_flag;//

Int32U FrontLimit;
Int32U MiddleLimit;
Int32U BackLimit;
Int32U Aheader;
Int32U StanDistance;

Int8U Pulse_degree;
Int8U PassModeIn_flag=0;
Int8U PassModeOk_flag=0;

Int32U Size_MIN;
Int32U Size_MAX;
Int32U Size_MIN_num;
Int32U Size_MAX_num;
Int32U FirstDays;
Int32U SecondDays;
Int32U AutoPushDistance;
Int8U FirstDayValid_flag;
Int8U SecondDayValid_flag;

Int8U PassCodeEn_flag;
//Int8U SelfCutEnter_flag;

const Int8U PulseDegree[12][3]={"0","1","2","3","4","5","6","7","8","9","10","11"};
const Int8U PulseResolut[12][4]={"50","50","50","50","60","60","60","60","100","100","120","120"};
const Int8U ScrowResolut[12][3]={"10","12","8","18","12","10","8","18","10","12","10","12"};

Int32U TargetSize;
Int32U TargetSize_temp;
Int32U TargetSize_inch;

Int8U Forward_flag;
Int8U Backward_flag;

Int8U Run_flag;
Int8U BackStop_flag;
Int8U ForceStop_flag;
Int8U RunStop_flag;

Int8U MoveSpeed;
Int8U SelfLockEn_flag;
Int8U InTargetPosit_flag;

Int8U GoFrontEn_flag;
Int8U GoBackEn_flag;
Int8U GoFast_flag;
Int8U JogRunMode;
Int8U EncoderErr_flag;

Int8U RunDisplay_flag;
Int8U AutoPushRun_flag;
Int8U AutoCutExec_flag;
Int8U AutoCutStart_flag;
Int8U OneCutRoutine_flag;

Int8U PusherResetMove_flag;
Int16U PusherResetTime;


Int32U stop_time;


Int8U MotorType;

Int8U PushRstKey_flag;
Int8U ProcessRatio;

Int8U InputTouch_flag;
Int16U CodeSensorTime_AB;
Int8U CutPermit_flag;

Int8U ServoPressStop_flag;//伺服压纸 停机

Int8U DcServoGoTarget_flag;

Int16U LastAutoKnife_order;//  自刀 的前一刀
Int8U ReEnterAutoKnife_dis;  //再次进入自刀  提示

Int8U ACServoDrvErr_flag;
Int8U ACServoAlarmExec_flag;

Int8U ElectricWheelOn_flag; //电子手轮

Int32U current_inch;
Int8U MotorRun_flag;

Int8U GoDirMode=0;

Int8U InputMode;
Int16U ProNumGroup[MAIX_PROG+2];

const pInt8U NAME_flag={"name"};

extern PROCESS_HEAD Pro_head_temp;//

Int8U PramSel_Page;//参数 列表页
Int8U Para_sel;
Int8U Para2_sel;//2 列表项
Int8U IR_SensorStus;

Int8U JogLevel;// Jog速度




Int8U BmpJudge(Int32U Bmp_add)
{
struct BMP_HEADER head_temp;
struct BMP_INFO info_temp;
pInt8U p =(pInt8U)Bmp_add;
Int8U type;
	head_temp.lBmp_Data_Offset		= *(p+13)<<24;
	head_temp.lBmp_Data_Offset	   |= *(p+12)<<16;
	head_temp.lBmp_Data_Offset	   |= *(p+11)<<8;
	head_temp.lBmp_Data_Offset	   |= *(p+10);
	
	info_temp.lBmp_Width				= *(p+21)<<24;
	info_temp.lBmp_Width			   |= *(p+20)<<16;
	info_temp.lBmp_Width			   |= *(p+19)<<8;
	info_temp.lBmp_Width			   |= *(p+18);
	
	info_temp.lBmp_Height			= *(p+25)<<24;
	info_temp.lBmp_Height		   |= *(p+24)<<16;
	info_temp.lBmp_Height		   |= *(p+23)<<8;
	info_temp.lBmp_Height		   |= *(p+22);
	
	info_temp.iBit_Count				= *(p+28);

	type=info_temp.iBit_Count>>3;
	if((type<2)||(type>4))
		{
		return 0;	
		}
	return 1;
}

//*****************读取文件
void ReadFiles(void)
{
//FileFolderRead("开机画面.bmp",(unsigned char*)START_PIC_sdram);//读开机画面
FileFolderRead("Power.bmp",(unsigned char*)START_PIC_sdram);//读开机画面
if(BmpJudge((Int32U)START_PIC_sdram)==0)
FileFolderRead("bPower.bmp",(unsigned char*)START_PIC_sdram);//读开机画面

//GLCD_SetWindow_Fill(30,450,600,479,BLACK_COLOR,BLACK_COLOR);//*******************************
FileFolderRead("背景.bmp",(unsigned char*)WOEK_BACK_dis);//读背景
if(BmpJudge((Int32U)WOEK_BACK_dis)==0)
FileFolderRead("b背景.bmp",(unsigned char*)WOEK_BACK_dis);//读背景
GLCD_SetWindow_Fill(0,0,799,479,BLACK_COLOR,BLACK_COLOR);//*******************************
switch(Language)
	{
	case CHN_HAN:
		FileFolderRead("编程.bmp",(unsigned char*)PROGRAM_sdram);
		if(BmpJudge((Int32U)PROGRAM_sdram)==0)
		FileFolderRead("b编程.bmp",(unsigned char*)PROGRAM_sdram);//
		FileFolderRead("标签.bmp",(unsigned char*)LABELS_sdram);
		if(BmpJudge((Int32U)LABELS_sdram)==0)
		FileFolderRead("b标签.bmp",(unsigned char*)LABELS_sdram);//
		FileFolderRead("参数.bmp",(unsigned char*)PARAMETER_sdram);//
		if(BmpJudge((Int32U)PARAMETER_sdram)==0)
		FileFolderRead("b参数.bmp",(unsigned char*)PARAMETER_sdram);//
		FileFolderRead("尺.bmp",(unsigned char*)RULER_sdram);//
		if(BmpJudge((Int32U)RULER_sdram)==0)
		FileFolderRead("b尺.bmp",(unsigned char*)RULER_sdram);//
		FileFolderRead("等分.bmp",(unsigned char*)DIVIDE_sdram);//
		if(BmpJudge((Int32U)DIVIDE_sdram)==0)
		FileFolderRead("b等分.bmp",(unsigned char*)DIVIDE_sdram);//
		FileFolderRead("时钟.bmp",(unsigned char*)WATCH_sdram);//
		if(BmpJudge((Int32U)WATCH_sdram)==0)
		FileFolderRead("b时钟.bmp",(unsigned char*)WATCH_sdram);//
		FileFolderRead("示教.bmp",(unsigned char*)TEACH_sdram);//
		if(BmpJudge((Int32U)TEACH_sdram)==0)
		FileFolderRead("b示教.bmp",(unsigned char*)TEACH_sdram);//
		FileFolderRead("手动.bmp",(unsigned char*)MANUAL_sdram);//
		if(BmpJudge((Int32U)MANUAL_sdram)==0)
		FileFolderRead("b手动.bmp",(unsigned char*)MANUAL_sdram);//
		FileFolderRead("自动.bmp",(unsigned char*)AUTO_sdram);//
		if(BmpJudge((Int32U)AUTO_sdram)==0)
		FileFolderRead("b自动.bmp",(unsigned char*)AUTO_sdram);//
		FileFolderRead("选择程序.bmp",(unsigned char*)SELECT_PRO_sdram);//
		if(BmpJudge((Int32U)SELECT_PRO_sdram)==0)
		FileFolderRead("b选择程序.bmp",(unsigned char*)SELECT_PRO_sdram);//
		FileFolderRead("自刀.bmp",(unsigned char*)AUTO_KNIFE_sdram);//
		if(BmpJudge((Int32U)AUTO_KNIFE_sdram)==0)
		FileFolderRead("b自刀.bmp",(unsigned char*)AUTO_KNIFE_sdram);//
		FileFolderRead("脉冲当量.bmp",(unsigned char*)PULSE_DEGREE_sdram);//
		if(BmpJudge((Int32U)PULSE_DEGREE_sdram)==0)
		FileFolderRead("b脉冲当量.bmp",(unsigned char*)PULSE_DEGREE_sdram);//
		FileFolderRead("锁.bmp",(unsigned char*)LOCK_sdram);//
		if(BmpJudge((Int32U)LOCK_sdram)==0)
		FileFolderRead("b锁.bmp",(unsigned char*)LOCK_sdram);//
		FileFolderRead("标签功能.bmp",(unsigned char*)LABEL_FUN_sdram);//
		if(BmpJudge((Int32U)LABEL_FUN_sdram)==0)
		FileFolderRead("b标签功能.bmp",(unsigned char*)LABEL_FUN_sdram);//
		FileFolderRead("程序.bmp",(unsigned char*)PROCESS_sdram);//
		if(BmpJudge((Int32U)PROCESS_sdram)==0)
		FileFolderRead("b程序.bmp",(unsigned char*)PROCESS_sdram);//
		FileFolderRead("工具.bmp",(unsigned char*)TOOLS_sdram);//
		if(BmpJudge((Int32U)TOOLS_sdram)==0)
		FileFolderRead("b工具.bmp",(unsigned char*)TOOLS_sdram);//
		FileFolderRead("等分功能.bmp",(unsigned char*)DIVIDE_FUN_sdram);//
		if(BmpJudge((Int32U)DIVIDE_FUN_sdram)==0)
		FileFolderRead("b等分功能.bmp",(unsigned char*)DIVIDE_FUN_sdram);//
		FileFolderRead("基准功能.bmp",(unsigned char*)RULER_FUN_sdram);//
		if(BmpJudge((Int32U)RULER_FUN_sdram)==0)
		FileFolderRead("b基准功能.bmp",(unsigned char*)RULER_FUN_sdram);//
		FileFolderRead("日历.bmp",(unsigned char*)CALENDAR_sdram);//
		if(BmpJudge((Int32U)CALENDAR_sdram)==0)
		FileFolderRead("b日历.bmp",(unsigned char*)CALENDAR_sdram);//
		FileFolderRead("输入尺寸.bmp",(unsigned char*)INPUT_SIZE_sdram);//
		if(BmpJudge((Int32U)INPUT_SIZE_sdram)==0)
		FileFolderRead("b输入尺寸.bmp",(unsigned char*)INPUT_SIZE_sdram);//
		FileFolderRead("提示栏.bmp",(unsigned char*)REMIND_sdram);//
		if(BmpJudge((Int32U)REMIND_sdram)==0)
		FileFolderRead("b提示栏.bmp",(unsigned char*)REMIND_sdram);//
		FileFolderRead("推纸_刀.bmp",(unsigned char*)PUSH_KNIFE_sdram);//
		if(BmpJudge((Int32U)PUSH_KNIFE_sdram)==0)
		FileFolderRead("b推纸_刀.bmp",(unsigned char*)PUSH_KNIFE_sdram);//
		FileFolderRead("位置.bmp",(unsigned char*)POSITION_sdram);//
		if(BmpJudge((Int32U)POSITION_sdram)==0)
		FileFolderRead("b位置.bmp",(unsigned char*)POSITION_sdram);//
		FileFolderRead("序号.bmp",(unsigned char*)ORDER_sdram);//
		if(BmpJudge((Int32U)ORDER_sdram)==0)
		FileFolderRead("b序号.bmp",(unsigned char*)ORDER_sdram);//
			break;
	case ENGLISH:
		FileFolderRead("编程EN.bmp",(unsigned char*)PROGRAM_EN_sdram);
		if(BmpJudge((Int32U)PROGRAM_EN_sdram)==0)
		FileFolderRead("b编程EN.bmp",(unsigned char*)PROGRAM_EN_sdram);//
		FileFolderRead("标签EN.bmp",(unsigned char*)LABELS_EN_sdram);
		if(BmpJudge((Int32U)LABELS_EN_sdram)==0)
		FileFolderRead("b标签EN.bmp",(unsigned char*)LABELS_EN_sdram);//
		FileFolderRead("参数EN.bmp",(unsigned char*)PARAMETER_EN_sdram);//
		if(BmpJudge((Int32U)PARAMETER_EN_sdram)==0)
		FileFolderRead("b参数EN.bmp",(unsigned char*)PARAMETER_EN_sdram);//
		FileFolderRead("基准EN.bmp",(unsigned char*)BENCH_EN_sdram);//
		if(BmpJudge((Int32U)BENCH_EN_sdram)==0)
		FileFolderRead("b基准EN.bmp",(unsigned char*)BENCH_EN_sdram);//
		FileFolderRead("等分EN.bmp",(unsigned char*)DIVIDE_EN_sdram);//
		if(BmpJudge((Int32U)DIVIDE_EN_sdram)==0)
		FileFolderRead("b等分EN.bmp",(unsigned char*)DIVIDE_EN_sdram);//
		FileFolderRead("时钟EN.bmp",(unsigned char*)WATCH_EN_sdram);//
		if(BmpJudge((Int32U)WATCH_EN_sdram)==0)
		FileFolderRead("b时钟EN.bmp",(unsigned char*)WATCH_EN_sdram);//
		FileFolderRead("示教EN.bmp",(unsigned char*)TEACH_EN_sdram);//
		if(BmpJudge((Int32U)TEACH_EN_sdram)==0)
		FileFolderRead("b示教EN.bmp",(unsigned char*)TEACH_EN_sdram);//
		FileFolderRead("手动EN.bmp",(unsigned char*)MANUAL_EN_sdram);//
		if(BmpJudge((Int32U)MANUAL_EN_sdram)==0)
		FileFolderRead("b手动EN.bmp",(unsigned char*)MANUAL_EN_sdram);//
		FileFolderRead("自动EN.bmp",(unsigned char*)AUTO_EN_sdram);//
		if(BmpJudge((Int32U)AUTO_EN_sdram)==0)
		FileFolderRead("b自动EN.bmp",(unsigned char*)AUTO_EN_sdram);//
		FileFolderRead("选择程序EN.bmp",(unsigned char*)SELECT_PRO_EN_sdram);//
		if(BmpJudge((Int32U)SELECT_PRO_EN_sdram)==0)
		FileFolderRead("b选择程序EN.bmp",(unsigned char*)SELECT_PRO_EN_sdram);//
		FileFolderRead("自刀EN.bmp",(unsigned char*)AUTO_KNIFE_EN_sdram);//
		if(BmpJudge((Int32U)AUTO_KNIFE_EN_sdram)==0)
		FileFolderRead("b自刀EN.bmp",(unsigned char*)AUTO_KNIFE_EN_sdram);//
		FileFolderRead("脉冲当量EN.bmp",(unsigned char*)PULSE_DEGREE_EN_sdram);//
		if(BmpJudge((Int32U)PULSE_DEGREE_EN_sdram)==0)
		FileFolderRead("b脉冲当量EN.bmp",(unsigned char*)PULSE_DEGREE_EN_sdram);//
		FileFolderRead("锁EN.bmp",(unsigned char*)LOCK_EN_sdram);//
		if(BmpJudge((Int32U)LOCK_EN_sdram)==0)
		FileFolderRead("b锁EN.bmp",(unsigned char*)LOCK_EN_sdram);//
		FileFolderRead("标签功能EN.bmp",(unsigned char*)LABEL_FUN_EN_sdram);//
		if(BmpJudge((Int32U)LABEL_FUN_EN_sdram)==0)
		FileFolderRead("b标签功能EN.bmp",(unsigned char*)LABEL_FUN_EN_sdram);//
		FileFolderRead("程序EN.bmp",(unsigned char*)PROCESS_EN_sdram);//
		if(BmpJudge((Int32U)PROCESS_EN_sdram)==0)
		FileFolderRead("b程序EN.bmp",(unsigned char*)PROCESS_EN_sdram);//
		FileFolderRead("工具.bmp",(unsigned char*)TOOLS_EN_sdram);//
		if(BmpJudge((Int32U)TOOLS_EN_sdram)==0)
		FileFolderRead("b工具.bmp",(unsigned char*)TOOLS_EN_sdram);//
		FileFolderRead("等分功能EN.bmp",(unsigned char*)DIVIDE_FUN_EN_sdram);//
		if(BmpJudge((Int32U)DIVIDE_FUN_EN_sdram)==0)
		FileFolderRead("b等分功能EN.bmp",(unsigned char*)DIVIDE_FUN_EN_sdram);//
		FileFolderRead("基准功能EN.bmp",(unsigned char*)RULER_FUN_EN_sdram);//
		if(BmpJudge((Int32U)RULER_FUN_EN_sdram)==0)
		FileFolderRead("b基准功能EN.bmp",(unsigned char*)RULER_FUN_EN_sdram);//
		FileFolderRead("日历.bmp",(unsigned char*)CALENDAR_EN_sdram);//
		if(BmpJudge((Int32U)CALENDAR_EN_sdram)==0)
		FileFolderRead("b日历.bmp",(unsigned char*)CALENDAR_EN_sdram);//
		FileFolderRead("输入尺寸EN.bmp",(unsigned char*)INPUT_SIZE_EN_sdram);//
		if(BmpJudge((Int32U)INPUT_SIZE_EN_sdram)==0)
		FileFolderRead("b输入尺寸EN.bmp",(unsigned char*)INPUT_SIZE_EN_sdram);//
		FileFolderRead("提示栏EN.bmp",(unsigned char*)REMIND_EN_sdram);//
		if(BmpJudge((Int32U)REMIND_EN_sdram)==0)
		FileFolderRead("b提示栏EN.bmp",(unsigned char*)REMIND_EN_sdram);//
		FileFolderRead("推纸_刀EN.bmp",(unsigned char*)PUSH_KNIFE_EN_sdram);//
		if(BmpJudge((Int32U)PUSH_KNIFE_EN_sdram)==0)
		FileFolderRead("b推纸_刀EN.bmp",(unsigned char*)PUSH_KNIFE_EN_sdram);//
		FileFolderRead("位置EN.bmp",(unsigned char*)POSITION_EN_sdram);//
		if(BmpJudge((Int32U)POSITION_EN_sdram)==0)
		FileFolderRead("b位置EN.bmp",(unsigned char*)POSITION_EN_sdram);//
		FileFolderRead("序号EN.bmp",(unsigned char*)ORDER_EN_sdram);//
		if(BmpJudge((Int32U)ORDER_EN_sdram)==0)
		FileFolderRead("b序号EN.bmp",(unsigned char*)ORDER_EN_sdram);//
			break;
	}

FileFolderRead("F1up.bmp",(unsigned char*)F1UP_sdram);//
if(BmpJudge((Int32U)F1UP_sdram)==0)
FileFolderRead("bF1up.bmp",(unsigned char*)F1UP_sdram);//
FileFolderRead("F2up.bmp",(unsigned char*)F2UP_sdram);//
if(BmpJudge((Int32U)F2UP_sdram)==0)
FileFolderRead("bF2up.bmp",(unsigned char*)F2UP_sdram);//
FileFolderRead("F3up.bmp",(unsigned char*)F3UP_sdram);//
if(BmpJudge((Int32U)F3UP_sdram)==0)
FileFolderRead("bF3up.bmp",(unsigned char*)F3UP_sdram);//
FileFolderRead("F4up.bmp",(unsigned char*)F4UP_sdram);//
if(BmpJudge((Int32U)F4UP_sdram)==0)
FileFolderRead("bF4up.bmp",(unsigned char*)F4UP_sdram);//
FileFolderRead("F2退出up.bmp",(unsigned char*)F2_OUT_UP_sdram);//
if(BmpJudge((Int32U)F2_OUT_UP_sdram)==0)
FileFolderRead("bF2退出up.bmp",(unsigned char*)F2_OUT_UP_sdram);//
FileFolderRead("F1尺子up.bmp",(unsigned char*)F1_RULER_UP_sdram);//
if(BmpJudge((Int32U)F1_RULER_UP_sdram)==0)
FileFolderRead("bF1尺子up.bmp",(unsigned char*)F1_RULER_UP_sdram);//
FileFolderRead("F2工具up.bmp",(unsigned char*)F2_TOOLS_UP_sdram);//
if(BmpJudge((Int32U)F2_TOOLS_UP_sdram)==0)
FileFolderRead("bF2工具up.bmp",(unsigned char*)F2_TOOLS_UP_sdram);//

FileFolderRead("F1工具up_manual.bmp",(unsigned char*)F1_Manual_TOOLS_UP_sdram);//
if(BmpJudge((Int32U)F1_Manual_TOOLS_UP_sdram)==0)
FileFolderRead("bF1工具up_manual.bmp",(unsigned char*)F1_Manual_TOOLS_UP_sdram);//
FileFolderRead("F2up_manual.bmp",(unsigned char*)F2_Manual_RULER_UP_sdram);//
if(BmpJudge((Int32U)F2_Manual_RULER_UP_sdram)==0)
FileFolderRead("bF2up_manual.bmp",(unsigned char*)F2_Manual_RULER_UP_sdram);//


FileFolderRead("完成.bmp",(unsigned char*)FINISHED_sdram);//
if(BmpJudge((Int32U)FINISHED_sdram)==0)
FileFolderRead("b完成.bmp",(unsigned char*)FINISHED_sdram);//
//FileFolderRead("示教模式.bmp",(unsigned char*)TEACH_MOD_sdram);//
//FileFolderRead("自刀模式.bmp",(unsigned char*)AUTO_KNIFE_MOD_sdram);//
FileFolderRead("刀上.bmp",(unsigned char*)KNIFE_UP_sdram);//
if(BmpJudge((Int32U)KNIFE_UP_sdram)==0)
FileFolderRead("b刀上.bmp",(unsigned char*)KNIFE_UP_sdram);//
FileFolderRead("刀下.bmp",(unsigned char*)KNIFE_DOWN_sdram);//
if(BmpJudge((Int32U)KNIFE_DOWN_sdram)==0)
FileFolderRead("b刀下.bmp",(unsigned char*)KNIFE_DOWN_sdram);//
FileFolderRead("压上.bmp",(unsigned char*)PRESS_UP_sdram);//
if(BmpJudge((Int32U)PRESS_UP_sdram)==0)
FileFolderRead("b压上.bmp",(unsigned char*)PRESS_UP_sdram);//
FileFolderRead("压下.bmp",(unsigned char*)PRESS_DOWN_sdram);//
if(BmpJudge((Int32U)PRESS_DOWN_sdram)==0)
FileFolderRead("b压下.bmp",(unsigned char*)PRESS_DOWN_sdram);//
FileFolderRead("红色A.bmp",(unsigned char*)RED_A_sdram);//
if(BmpJudge((Int32U)RED_A_sdram)==0)
FileFolderRead("b红色A.bmp",(unsigned char*)RED_A_sdram);//
FileFolderRead("红色B.bmp",(unsigned char*)RED_B_sdram);//
if(BmpJudge((Int32U)RED_B_sdram)==0)
FileFolderRead("b红色B.bmp",(unsigned char*)RED_B_sdram);//
FileFolderRead("黑色A.bmp",(unsigned char*)BLACK_A_sdram);//
if(BmpJudge((Int32U)BLACK_A_sdram)==0)
FileFolderRead("b黑色A.bmp",(unsigned char*)BLACK_A_sdram);//
FileFolderRead("黑色B.bmp",(unsigned char*)BLACK_B_sdram);//
if(BmpJudge((Int32U)BLACK_B_sdram)==0)
FileFolderRead("b黑色B.bmp",(unsigned char*)BLACK_B_sdram);//
FileFolderRead("红线.bmp",(unsigned char*)RED_LINE_sdram);//
if(BmpJudge((Int32U)RED_LINE_sdram)==0)
FileFolderRead("b红线.bmp",(unsigned char*)RED_LINE_sdram);//
FileFolderRead("手红外.bmp",(unsigned char*)HAND_IR_sdram);//
if(BmpJudge((Int32U)HAND_IR_sdram)==0)
FileFolderRead("b手红外.bmp",(unsigned char*)HAND_IR_sdram);//
FileFolderRead("刀前.bmp",(unsigned char*)FRONT_KNIFE_sdram);//
if(BmpJudge((Int32U)FRONT_KNIFE_sdram)==0)
FileFolderRead("b刀前.bmp",(unsigned char*)FRONT_KNIFE_sdram);//
FileFolderRead("红刀.bmp",(unsigned char*)RED_KNIFE_F_sdram);//
if(BmpJudge((Int32U)RED_KNIFE_F_sdram)==0)
FileFolderRead("b红刀.bmp",(unsigned char*)RED_KNIFE_F_sdram);//
FileFolderRead("推纸.bmp",(unsigned char*)PUSH_PAPER_F_sdram);//
if(BmpJudge((Int32U)PUSH_PAPER_F_sdram)==0)
FileFolderRead("b推纸.bmp",(unsigned char*)PUSH_PAPER_F_sdram);//
FileFolderRead("压纸循环标记.bmp",(unsigned char*)PRE_AUTO_F_sdram);//
if(BmpJudge((Int32U)PRE_AUTO_F_sdram)==0)
FileFolderRead("b压纸循环标记.bmp",(unsigned char*)PRE_AUTO_F_sdram);//
FileFolderRead("进度.bmp",(unsigned char*)SCHEDULE_sdram);//
if(BmpJudge((Int32U)SCHEDULE_sdram)==0)
FileFolderRead("b进度.bmp",(unsigned char*)SCHEDULE_sdram);//
FileFolderRead("进度位置.bmp",(unsigned char*)SCHEDULE_DOT_sdram);//
if(BmpJudge((Int32U)SCHEDULE_DOT_sdram)==0)
FileFolderRead("b进度位置.bmp",(unsigned char*)SCHEDULE_DOT_sdram);//
FileFolderRead("右箭头.bmp",(unsigned char*)RIGHT_ARROW_sdram);//
if(BmpJudge((Int32U)RIGHT_ARROW_sdram)==0)
FileFolderRead("b右箭头.bmp",(unsigned char*)RIGHT_ARROW_sdram);//
FileFolderRead("时间条.bmp",(unsigned char*)TIME_COL_sdram);//
if(BmpJudge((Int32U)TIME_COL_sdram)==0)
FileFolderRead("b时间条.bmp",(unsigned char*)TIME_COL_sdram);//
FileFolderRead("推纸器.bmp",(unsigned char*)PUSH_PAPER_TOOL_sdram);//
if(BmpJudge((Int32U)PUSH_PAPER_TOOL_sdram)==0)
FileFolderRead("b推纸器.bmp",(unsigned char*)PUSH_PAPER_TOOL_sdram);//
//FileFolderRead("取消up.bmp",(unsigned char*)CANCEL_UP_sdram);//
//FileFolderRead("取消down.bmp",(unsigned char*)CANCEL_DOWN_sdram);//
//FileFolderRead("确定up.bmp",(unsigned char*)ENTER_UP_sdram);//
//FileFolderRead("确定down.bmp",(unsigned char*)ENTER_DOWN_sdram);//
FileFolderRead("停止up.bmp",(unsigned char*)STOP_UP_sdram);//
if(BmpJudge((Int32U)STOP_UP_sdram)==0)
FileFolderRead("b停止up.bmp",(unsigned char*)STOP_UP_sdram);//
//FileFolderRead("停止down.bmp",(unsigned char*)STOP_DOWN_sdram);//
FileFolderRead("运行up.bmp",(unsigned char*)RUN_UP_sdram);//
if(BmpJudge((Int32U)RUN_UP_sdram)==0)
FileFolderRead("b运行up.bmp",(unsigned char*)RUN_UP_sdram);//
//FileFolderRead("运行down.bmp",(unsigned char*)RUN_DOWN_sdram);//

FileFolderRead("中间活页.bmp",(unsigned char*)MIDDLE_PAGE_sdram);//
if(BmpJudge((Int32U)MIDDLE_PAGE_sdram)==0)
FileFolderRead("b中间活页.bmp",(unsigned char*)MIDDLE_PAGE_sdram);//
FileFolderRead("左边活页.bmp",(unsigned char*)LEFT_PAGE_sdram);//
if(BmpJudge((Int32U)LEFT_PAGE_sdram)==0)
FileFolderRead("b左边活页.bmp",(unsigned char*)LEFT_PAGE_sdram);//
FileFolderRead("删除up.bmp",(unsigned char*)DELETE_UP_sdram);//
if(BmpJudge((Int32U)DELETE_UP_sdram)==0)
FileFolderRead("b删除up.bmp",(unsigned char*)DELETE_UP_sdram);//
FileFolderRead("全删up.bmp",(unsigned char*)DELETE_ALL_UP_sdram);//
if(BmpJudge((Int32U)DELETE_ALL_UP_sdram)==0)
FileFolderRead("b全删up.bmp",(unsigned char*)DELETE_ALL_UP_sdram);//
FileFolderRead("鸭梨.bmp",(unsigned char*)PEAR_sdram);//
if(BmpJudge((Int32U)PEAR_sdram)==0)
FileFolderRead("b鸭梨.bmp",(unsigned char*)PEAR_sdram);//
FileFolderRead("F键up.bmp",(unsigned char*)F_KEY_UP_sdram);//
if(BmpJudge((Int32U)F_KEY_UP_sdram)==0)
FileFolderRead("bF键up.bmp",(unsigned char*)F_KEY_UP_sdram);//
FileFolderRead("后退up.bmp",(unsigned char*)BACK_PAGE_UP_sdram);//
if(BmpJudge((Int32U)BACK_PAGE_UP_sdram)==0)
FileFolderRead("b后退up.bmp",(unsigned char*)BACK_PAGE_UP_sdram);//
FileFolderRead("前进up.bmp",(unsigned char*)FRONT_PAGE_UP_sdram);//
if(BmpJudge((Int32U)FRONT_PAGE_UP_sdram)==0)
FileFolderRead("b前进up.bmp",(unsigned char*)FRONT_PAGE_UP_sdram);//
FileFolderRead("上箭头up.bmp",(unsigned char*)UP_ARROW_UP_sdram);//
if(BmpJudge((Int32U)UP_ARROW_UP_sdram)==0)
FileFolderRead("b上箭头up.bmp",(unsigned char*)UP_ARROW_UP_sdram);//
FileFolderRead("下箭头up.bmp",(unsigned char*)DOWN_ARROW_UP_sdram);//
if(BmpJudge((Int32U)DOWN_ARROW_UP_sdram)==0)
FileFolderRead("b下箭头up.bmp",(unsigned char*)DOWN_ARROW_UP_sdram);//
FileFolderRead("F3++up.bmp",(unsigned char*)F3_PLUS_UP_sdram);//
if(BmpJudge((Int32U)F3_PLUS_UP_sdram)==0)
FileFolderRead("bF3++up.bmp",(unsigned char*)F3_PLUS_UP_sdram);//
FileFolderRead("F3时钟up.bmp",(unsigned char*)F3_CLOCK_UP_sdram);//
if(BmpJudge((Int32U)F3_CLOCK_UP_sdram)==0)
FileFolderRead("bF3时钟up.bmp",(unsigned char*)F3_CLOCK_UP_sdram);//
FileFolderRead("F4--up.bmp",(unsigned char*)F4_MINUS_UP_sdram);//
if(BmpJudge((Int32U)F4_MINUS_UP_sdram)==0)
FileFolderRead("bF4--up.bmp",(unsigned char*)F4_MINUS_UP_sdram);//
//FileFolderRead("F5刀up.bmp",(unsigned char*)F5_CUT_UP_sdram);//

FileFolderRead("锁 钥匙.bmp",(unsigned char*)LOCK_KEY_sdram);//
if(BmpJudge((Int32U)LOCK_KEY_sdram)==0)
FileFolderRead("b锁 钥匙.bmp",(unsigned char*)LOCK_KEY_sdram);//
FileFolderRead("左右箭头.bmp",(unsigned char*)L_R_ARROW_sdram);//
if(BmpJudge((Int32U)L_R_ARROW_sdram)==0)
FileFolderRead("b左右箭头.bmp",(unsigned char*)L_R_ARROW_sdram);//
FileFolderRead("F5压纸循环up.bmp",(unsigned char*)F5_PRE_FLG_BUTT_UP_sdram);//
if(BmpJudge((Int32U)F5_PRE_FLG_BUTT_UP_sdram)==0)
FileFolderRead("bF5压纸循环up.bmp",(unsigned char*)F5_PRE_FLG_BUTT_UP_sdram);//

FileFolderRead("wheel0.bmp",(unsigned char*)WHEEL0_sdram);//
if(BmpJudge((Int32U)WHEEL0_sdram)==0)
FileFolderRead("bwheel0.bmp",(unsigned char*)WHEEL0_sdram);//
FileFolderRead("wheel1.bmp",(unsigned char*)WHEEL1_sdram);//
if(BmpJudge((Int32U)WHEEL1_sdram)==0)
FileFolderRead("bwheel1.bmp",(unsigned char*)WHEEL1_sdram);//
FileFolderRead("F4_0.bmp",(unsigned char*)F4_WHEEL0_sdram);//
if(BmpJudge((Int32U)F4_WHEEL0_sdram)==0)
FileFolderRead("bF4_0.bmp",(unsigned char*)F4_WHEEL0_sdram);//
FileFolderRead("F4_1.bmp",(unsigned char*)F4_WHEEL1_sdram);//
if(BmpJudge((Int32U)F4_WHEEL1_sdram)==0)
FileFolderRead("bF4_1.bmp",(unsigned char*)F4_WHEEL1_sdram);//
//FileFolderRead("clock.bmp",(unsigned char*)test_sdram);//
FileFolderRead("F5_YES.bmp",(unsigned char*)F5_YESCUT_sdram);//
if(BmpJudge((Int32U)F5_YESCUT_sdram)==0)
FileFolderRead("bF5_YES.bmp",(unsigned char*)F5_YESCUT_sdram);//
FileFolderRead("F5_NO.bmp",(unsigned char*)F5_NOCUT_sdram);//
if(BmpJudge((Int32U)F5_NOCUT_sdram)==0)
FileFolderRead("bF5_NO.bmp",(unsigned char*)F5_NOCUT_sdram);//
FileFolderRead("F0ALL_YES.bmp",(unsigned char*)F0_YESALLCUT_sdram);//
if(BmpJudge((Int32U)F0_YESALLCUT_sdram)==0)
FileFolderRead("bF0ALL_YES.bmp",(unsigned char*)F0_YESALLCUT_sdram);//
FileFolderRead("F0ALL_NO.bmp",(unsigned char*)F0_NOALLCUT_sdram);//
if(BmpJudge((Int32U)F0_NOALLCUT_sdram)==0)
FileFolderRead("bF0ALL_NO.bmp",(unsigned char*)F0_NOALLCUT_sdram);//

FileFolderRead("快进up.bmp",(unsigned char*)FAST_FORWD_UP_sdram);
if(BmpJudge((Int32U)FAST_FORWD_UP_sdram)==0)
FileFolderRead("b快进up.bmp",(unsigned char*)FAST_FORWD_UP_sdram);
FileFolderRead("快退up.bmp",(unsigned char*)FAST_BACK_UP_sdram);
if(BmpJudge((Int32U)FAST_BACK_UP_sdram)==0)
FileFolderRead("b快退up.bmp",(unsigned char*)FAST_BACK_UP_sdram);

//-------English

}

void StartPic_dis(void)//开机画面显示
{
	Int32U i;
	pInt32U dest_Ptr;
pInt32U source_Ptr=(pInt32U)malloc(1024);
for(i=0;i<256;i++)	//1k
	{
	source_Ptr[i]=0xffffffff;
	}
for (i=0;i<10*1024;i++)//24k		10m
	{
	dest_Ptr=(pInt32U)(df_zk_sdram+i*1024);//           0xa0600000  //字库2M
	memcpy(dest_Ptr,source_Ptr,1024);
	}
free(source_Ptr);

FileRead("字库_0x20000.FON",(unsigned char *)df_zk_sdram);//
FileFolderRead("鸭梨.bmp",(unsigned char*)PEAR_sdram);//
switch(Language)
	{
	case CHN_HAN:
		Printf24("电脑自检，数据加载.....需要6秒，请稍等！",40,450,RED_COLOR,1,0xffff);
			break;
	case ENGLISH:	
		Printf24("Computer is self-checking,loading data....",40,420,RED_COLOR,1,0xffff);
		Printf24("Please wait 6 seconds!",40,450,RED_COLOR,1,0xffff);
			break;
	}

//FileFolderRead("开机画面.bmp",(unsigned char*)START_PIC_sdram);//读开机画面
Pear_dis(PEAR_X, PEAR_Y);//鸭梨
ReadFiles();  //读取 图标文件
Bmp_Decode((Int32U)START_PIC_sdram, 0, 0, (pInt16U)SDRAM0_BASE_ADDR); //显示开机画面

RLOUT1_OFF; RLOUT1_1_OFF;   // 允许裁切

}

//************************显示图片  小图标定义
void FirstBack_dis(void)//工作 背景
{
Bmp_Decode((Int32U)WOEK_BACK_dis, 0, 0, (pInt16U)SDRAM0_BASE_ADDR);
//pInt16U pbuf,pdis;
//pbuf=(pInt16U)(WOEK_BACK_dis+4);
//pdis=(pInt16U)SDRAM0_BASE_ADDR;
//memcpy(pdis,pbuf,800*480*2); 
}

void Program_dis(Int16U x, Int16U y)//编程
{
Int32U buf_add=(Int32U)PROGRAM_sdram;
switch(Language)	
	{
	case CHN_HAN:
			buf_add=(Int32U)PROGRAM_sdram;
			break;
	case ENGLISH:
			buf_add=(Int32U)PROGRAM_EN_sdram;
			break;		
	}
Bmp_Decode(buf_add, x, y, (pInt16U)SDRAM0_BASE_ADDR);
}
void Label_dis(Int16U x, Int16U y)//标签
{
Int32U buf_add=(Int32U)LABELS_sdram;
switch(Language)	
	{
	case CHN_HAN:
			buf_add=(Int32U)LABELS_sdram;
			break;
	case ENGLISH:
			buf_add=(Int32U)LABELS_EN_sdram;
			break;		
	}
Bmp_Decode(buf_add, x, y, (pInt16U)SDRAM0_BASE_ADDR);
}
void Parameter_dis(Int16U x, Int16U y)//参数
{
Int32U buf_add=(Int32U)PARAMETER_sdram;
switch(Language)	
	{
	case CHN_HAN:
			buf_add=(Int32U)PARAMETER_sdram;
			break;
	case ENGLISH:
			buf_add=(Int32U)PARAMETER_EN_sdram;
			break;		
	}
Bmp_Decode(buf_add, x, y, (pInt16U)SDRAM0_BASE_ADDR);
}
void Ruler_dis(Int16U x, Int16U y)//尺
{
Int32U buf_add=(Int32U)RULER_sdram;
switch(Language)	
	{
	case CHN_HAN:
			buf_add=(Int32U)RULER_sdram;
			break;
	case ENGLISH:
			buf_add=(Int32U)BENCH_EN_sdram;
			break;		
	}
Bmp_Decode(buf_add, x, y, (pInt16U)SDRAM0_BASE_ADDR);
}
void Divide_dis(Int16U x, Int16U y)//等分
{
Int32U buf_add=(Int32U)DIVIDE_sdram;
switch(Language)	
	{
	case CHN_HAN:
			buf_add=(Int32U)DIVIDE_sdram;
			break;
	case ENGLISH:
			buf_add=(Int32U)DIVIDE_EN_sdram;
			break;		
	}
Bmp_Decode(buf_add, x, y, (pInt16U)SDRAM0_BASE_ADDR);
}
void Watch_dis(Int16U x, Int16U y)//时钟
{
Int32U buf_add=(Int32U)WATCH_sdram;
switch(Language)	
	{
	case CHN_HAN:
			buf_add=(Int32U)WATCH_sdram;
			break;
	case ENGLISH:
			buf_add=(Int32U)WATCH_EN_sdram;
			break;		
	}
Bmp_Decode(buf_add, x, y, (pInt16U)SDRAM0_BASE_ADDR);
}
void Teach_dis(Int16U x, Int16U y)//示教
{
Int32U buf_add=(Int32U)TEACH_sdram;
switch(Language)	
	{
	case CHN_HAN:
			buf_add=(Int32U)TEACH_sdram;
			break;
	case ENGLISH:
			buf_add=(Int32U)TEACH_EN_sdram;
			break;		
	}
Bmp_Decode(buf_add, x, y, (pInt16U)SDRAM0_BASE_ADDR);
}
void Manual_dis(Int16U x, Int16U y)//手动
{
Int32U buf_add=(Int32U)MANUAL_sdram;
switch(Language)	
	{
	case CHN_HAN:
			buf_add=(Int32U)MANUAL_sdram;
			break;
	case ENGLISH:
			buf_add=(Int32U)MANUAL_EN_sdram;
			break;		
	}
Bmp_Decode(buf_add, x, y, (pInt16U)SDRAM0_BASE_ADDR);
}
void Auto_dis(Int16U x, Int16U y)//自动
{
Int32U buf_add=(Int32U)AUTO_sdram;
switch(Language)	
	{
	case CHN_HAN:
			buf_add=(Int32U)AUTO_sdram;
			break;
	case ENGLISH:
			buf_add=(Int32U)AUTO_EN_sdram;
			break;		
	}
Bmp_Decode(buf_add, x, y, (pInt16U)SDRAM0_BASE_ADDR);
}
void SelectPro_dis(Int16U x, Int16U y)//选择程序
{
Int32U buf_add=(Int32U)SELECT_PRO_sdram;
switch(Language)	
	{
	case CHN_HAN:
			buf_add=(Int32U)SELECT_PRO_sdram;
			break;
	case ENGLISH:
			buf_add=(Int32U)SELECT_PRO_EN_sdram;
			break;		
	}
Bmp_Decode(buf_add, x, y, (pInt16U)SDRAM0_BASE_ADDR);
}
void AutoKnife_dis(Int16U x, Int16U y)//自刀
{
Int32U buf_add=(Int32U)AUTO_KNIFE_sdram;
switch(Language)	
	{
	case CHN_HAN:
			buf_add=(Int32U)AUTO_KNIFE_sdram;
			break;
	case ENGLISH:
			buf_add=(Int32U)AUTO_KNIFE_EN_sdram;
			break;		
	}
Bmp_Decode(buf_add, x, y, (pInt16U)SDRAM0_BASE_ADDR);
}
void LabelFun_dis(Int16U x, Int16U y)//标签功能
{
Int32U buf_add=(Int32U)LABEL_FUN_sdram;
switch(Language)	
	{
	case CHN_HAN:
			buf_add=(Int32U)LABEL_FUN_sdram;
			break;
	case ENGLISH:
			buf_add=(Int32U)LABEL_FUN_EN_sdram;
			break;		
	}
Bmp_Decode(buf_add, x, y, (pInt16U)SDRAM0_BASE_ADDR);
}
void Process_dis(Int16U x, Int16U y)//程序
{
Int32U buf_add=(Int32U)PROCESS_sdram;
switch(Language)	
	{
	case CHN_HAN:
			buf_add=(Int32U)PROCESS_sdram;
			break;
	case ENGLISH:
			buf_add=(Int32U)PROCESS_EN_sdram;
			break;		
	}
Bmp_Decode(buf_add, x, y, (pInt16U)SDRAM0_BASE_ADDR);
}
void Tools_dis(Int16U x, Int16U y)//工具
{
Int32U buf_add=(Int32U)TOOLS_sdram;
switch(Language)	
	{
	case CHN_HAN:
			buf_add=(Int32U)TOOLS_sdram;
			break;
	case ENGLISH:
			buf_add=(Int32U)TOOLS_EN_sdram;
			break;		
	}
Bmp_Decode(buf_add, x, y, (pInt16U)SDRAM0_BASE_ADDR);
}
void DivideFun_dis(Int16U x, Int16U y)//等分功能
{
Int32U buf_add=(Int32U)DIVIDE_FUN_sdram;
switch(Language)	
	{
	case CHN_HAN:
			buf_add=(Int32U)DIVIDE_FUN_sdram;
			break;
	case ENGLISH:
			buf_add=(Int32U)DIVIDE_FUN_EN_sdram;
			break;		
	}
Bmp_Decode(buf_add, x, y, (pInt16U)SDRAM0_BASE_ADDR);
}
void RulerFun_dis(Int16U x, Int16U y)//基准功能
{
Int32U buf_add=(Int32U)RULER_FUN_sdram;
switch(Language)	
	{
	case CHN_HAN:
			buf_add=(Int32U)RULER_FUN_sdram;
			break;
	case ENGLISH:
			buf_add=(Int32U)RULER_FUN_EN_sdram;
			break;		
	}
Bmp_Decode(buf_add, x, y, (pInt16U)SDRAM0_BASE_ADDR);
}
void Calendar_dis(Int16U x, Int16U y)//日历
{
Int32U buf_add=(Int32U)CALENDAR_sdram;
switch(Language)	
	{
	case CHN_HAN:
			buf_add=(Int32U)CALENDAR_sdram;
			break;
	case ENGLISH:
			buf_add=(Int32U)CALENDAR_EN_sdram;
			break;		
	}
Bmp_Decode(buf_add, x, y, (pInt16U)SDRAM0_BASE_ADDR);
}
void F1up_dis(Int16U x, Int16U y)//F1up
{
Bmp_Decode((Int32U)F1UP_sdram, x, y, (pInt16U)SDRAM0_BASE_ADDR);
}
void F2up_dis(Int16U x, Int16U y)//F2up
{
Bmp_Decode((Int32U)F2UP_sdram, x, y, (pInt16U)SDRAM0_BASE_ADDR);
}

//新加  手动状态下F1 工具   F2 尺子
void F1up_Manual_dis(Int16U x, Int16U y)//F1up
{
Bmp_Decode((Int32U)F1_Manual_TOOLS_UP_sdram, x, y, (pInt16U)SDRAM0_BASE_ADDR);
}

void F2up_Manual_dis(Int16U x, Int16U y)//F2up
{
Bmp_Decode((Int32U)F2_Manual_RULER_UP_sdram, x, y, (pInt16U)SDRAM0_BASE_ADDR);
}


void F3up_dis(Int16U x, Int16U y)//F3up
{
Bmp_Decode((Int32U)F3UP_sdram, x, y, (pInt16U)SDRAM0_BASE_ADDR);
}
void F4up_dis(Int16U x, Int16U y)//F4up
{
Bmp_Decode((Int32U)F4UP_sdram, x, y, (pInt16U)SDRAM0_BASE_ADDR);
}
void Finish_dis(Int16U x, Int16U y)//完成
{
Bmp_Decode((Int32U)FINISHED_sdram, x, y, (pInt16U)SDRAM0_BASE_ADDR);
}
void F1Ruler_Up_dis(Int16U x, Int16U y)//F1尺子up
{
Bmp_Decode((Int32U)F1_RULER_UP_sdram, x, y, (pInt16U)SDRAM0_BASE_ADDR);
}
void F2Tools_Up_dis(Int16U x, Int16U y)//F2工具up
{
Bmp_Decode((Int32U)F2_TOOLS_UP_sdram, x, y, (pInt16U)SDRAM0_BASE_ADDR);
}
void F2out_Up_dis(Int16U x, Int16U y)//F2退出up
{
Bmp_Decode((Int32U)F2_OUT_UP_sdram, x, y, (pInt16U)SDRAM0_BASE_ADDR);
}
void TeachMode_dis(Int16U x, Int16U y)//示教模式
{
Bmp_Decode((Int32U)TEACH_MOD_sdram, x, y, (pInt16U)SDRAM0_BASE_ADDR);
}
void AutoKnifeMode_dis(Int16U x, Int16U y)//自刀模式
{
Bmp_Decode((Int32U)AUTO_KNIFE_MOD_sdram, x, y, (pInt16U)SDRAM0_BASE_ADDR);
}
void Knife_Up_dis(Int16U x, Int16U y)//刀上
{
Bmp_Decode((Int32U)KNIFE_UP_sdram, x, y, (pInt16U)SDRAM0_BASE_ADDR);
}
void Knife_Down_dis(Int16U x, Int16U y)//刀下
{
Bmp_Decode((Int32U)KNIFE_DOWN_sdram, x, y, (pInt16U)SDRAM0_BASE_ADDR);
}
void Press_Up_dis(Int16U x, Int16U y)//压上
{
Bmp_Decode((Int32U)PRESS_UP_sdram, x, y, (pInt16U)SDRAM0_BASE_ADDR);
}
void Press_Down_dis(Int16U x, Int16U y)//压下
{
Bmp_Decode((Int32U)PRESS_DOWN_sdram, x, y, (pInt16U)SDRAM0_BASE_ADDR);
}



void Red_A_dis(Int16U x, Int16U y)//红色A
{
// Bmp_Decode((Int32U)RED_A_sdram, x, y, (pInt16U)SDRAM0_BASE_ADDR);
}
void Red_B_dis(Int16U x, Int16U y)//红色B
{
// Bmp_Decode((Int32U)RED_B_sdram, x, y, (pInt16U)SDRAM0_BASE_ADDR);
}
void Black_A_dis(Int16U x, Int16U y)//黑色A
{
// Bmp_Decode((Int32U)BLACK_A_sdram, x, y, (pInt16U)SDRAM0_BASE_ADDR);
}
void Black_B_dis(Int16U x, Int16U y)//黑色B
{
// Bmp_Decode((Int32U)BLACK_B_sdram, x, y, (pInt16U)SDRAM0_BASE_ADDR);
}
void RedLine_dis(Int16U x, Int16U y)//红线
{
Bmp_Decode((Int32U)RED_LINE_sdram, x, y, (pInt16U)SDRAM0_BASE_ADDR);
}
void Hand_IR_dis(Int16U x, Int16U y)//手 红外
{
Bmp_Decode((Int32U)HAND_IR_sdram, x, y, (pInt16U)SDRAM0_BASE_ADDR);
}

void FrontKnife_dis(Int16U x, Int16U y)//刀前
{
Bmp_Decode((Int32U)FRONT_KNIFE_sdram, x, y, (pInt16U)SDRAM0_BASE_ADDR);
}
void RedKnifeF_dis(Int16U x, Int16U y)//红刀 标志
{
Bmp_Decode((Int32U)RED_KNIFE_F_sdram, x, y, (pInt16U)SDRAM0_BASE_ADDR);
}
void PushPaperF_dis(Int16U x, Int16U y)//推纸 标志
{
Bmp_Decode((Int32U)PUSH_PAPER_F_sdram, x, y, (pInt16U)SDRAM0_BASE_ADDR);
}
void AutoRoutePRE_dis(Int16U x, Int16U y)//k自动循环 标志
{
Bmp_Decode((Int32U)PRE_AUTO_F_sdram, x, y, (pInt16U)SDRAM0_BASE_ADDR);
}

void Schedule_dis(Int16U x, Int16U y)//进度
{
Bmp_Decode((Int32U)SCHEDULE_sdram, x, y, (pInt16U)SDRAM0_BASE_ADDR);
}
void SchedulePot_dis(Int16U x, Int16U y)//进度位置
{
Bmp_Decode((Int32U)SCHEDULE_DOT_sdram, x, y, (pInt16U)SDRAM0_BASE_ADDR);
}
void RightArrow_dis(Int16U x, Int16U y)//右箭头 -->
{
Bmp_Decode((Int32U)RIGHT_ARROW_sdram, x, y, (pInt16U)SDRAM0_BASE_ADDR);
}
void TimeCol_dis(Int16U x, Int16U y)//时间条
{
Bmp_Decode((Int32U)TIME_COL_sdram, x, y, (pInt16U)SDRAM0_BASE_ADDR);
}
void PushPaperTool_dis(Int16U x, Int16U y)//推纸器
{
Bmp_Decode((Int32U)PUSH_PAPER_TOOL_sdram, x, y, (pInt16U)SDRAM0_BASE_ADDR);
}

void Cancel_Up_dis(Int16U x, Int16U y)//取消up
{
Bmp_Decode((Int32U)CANCEL_UP_sdram, x, y, (pInt16U)SDRAM0_BASE_ADDR);
}
void Cancel_Down_dis(Int16U x, Int16U y)//取消down
{
Bmp_Decode((Int32U)CANCEL_DOWN_sdram, x, y, (pInt16U)SDRAM0_BASE_ADDR);
}
void Enter_Up_dis(Int16U x, Int16U y)//确定up
{
Bmp_Decode((Int32U)ENTER_UP_sdram, x, y, (pInt16U)SDRAM0_BASE_ADDR);
}
void Enter_Down_dis(Int16U x, Int16U y)//确定down
{
Bmp_Decode((Int32U)ENTER_DOWN_sdram, x, y, (pInt16U)SDRAM0_BASE_ADDR);
}
void Stop_Up_dis(Int16U x, Int16U y)//停止up
{
Bmp_Decode((Int32U)STOP_UP_sdram, x, y, (pInt16U)SDRAM0_BASE_ADDR);
}
void Stop_Down_dis(Int16U x, Int16U y)//停止down
{
Bmp_Decode((Int32U)STOP_DOWN_sdram, x, y, (pInt16U)SDRAM0_BASE_ADDR);
}
void Run_Up_dis(Int16U x, Int16U y)//运行up
{
Bmp_Decode((Int32U)RUN_UP_sdram, x, y, (pInt16U)SDRAM0_BASE_ADDR);
}
void Run_Down_dis(Int16U x, Int16U y)//运行down
{
Bmp_Decode((Int32U)RUN_DOWN_sdram, x, y, (pInt16U)SDRAM0_BASE_ADDR);
}

void InputSize_dis(Int16U x, Int16U y)//输入尺寸
{
Int32U buf_add=(Int32U)INPUT_SIZE_sdram;
switch(Language)	
	{
	case CHN_HAN:
			buf_add=(Int32U)INPUT_SIZE_sdram;
			break;
	case ENGLISH:
			buf_add=(Int32U)INPUT_SIZE_EN_sdram;
			break;		
	}
Bmp_Decode(buf_add, x, y, (pInt16U)SDRAM0_BASE_ADDR);
}
void Remind_dis(Int16U x, Int16U y)//提示栏
{
Int32U buf_add=(Int32U)REMIND_sdram;
switch(Language)	
	{
	case CHN_HAN:
			buf_add=(Int32U)REMIND_sdram;
			break;
	case ENGLISH:
			buf_add=(Int32U)REMIND_EN_sdram;
			break;		
	}
Bmp_Decode(buf_add, x, y, (pInt16U)SDRAM0_BASE_ADDR);
}

void PushKnife_dis(Int16U x, Int16U y)//推纸/刀
{
Int32U buf_add=(Int32U)PUSH_KNIFE_sdram;
switch(Language)	
	{
	case CHN_HAN:
			buf_add=(Int32U)PUSH_KNIFE_sdram;
			break;
	case ENGLISH:
			buf_add=(Int32U)PUSH_KNIFE_EN_sdram;
			break;		
	}
Bmp_Decode(buf_add, x, y, (pInt16U)SDRAM0_BASE_ADDR);
}
void Position_dis(Int16U x, Int16U y)//位置
{
Int32U buf_add=(Int32U)POSITION_sdram;
switch(Language)	
	{
	case CHN_HAN:
			buf_add=(Int32U)POSITION_sdram;
			break;
	case ENGLISH:
			buf_add=(Int32U)POSITION_EN_sdram;
			break;		
	}
Bmp_Decode(buf_add, x, y, (pInt16U)SDRAM0_BASE_ADDR);
}
void Order_dis(Int16U x, Int16U y)//序号
{
Int32U buf_add=(Int32U)ORDER_sdram;
switch(Language)	
	{
	case CHN_HAN:
			buf_add=(Int32U)ORDER_sdram;
			break;
	case ENGLISH:
			buf_add=(Int32U)ORDER_EN_sdram;
			break;		
	}
Bmp_Decode(buf_add, x, y, (pInt16U)SDRAM0_BASE_ADDR);
}

void MiddlePage_dis(Int16U x, Int16U y)//中间活页
{
Bmp_Decode((Int32U)MIDDLE_PAGE_sdram, x, y, (pInt16U)SDRAM0_BASE_ADDR);
}
void LeftPage_dis(Int16U x, Int16U y)//左边活页
{
Bmp_Decode((Int32U)LEFT_PAGE_sdram, x, y, (pInt16U)SDRAM0_BASE_ADDR);
}

void Delete_Up_dis(Int16U x, Int16U y)//删除up
{
Bmp_Decode((Int32U)DELETE_UP_sdram, x, y, (pInt16U)SDRAM0_BASE_ADDR);
}
void DeleteAll_Up_dis(Int16U x, Int16U y)//全删up
{
Bmp_Decode((Int32U)DELETE_ALL_UP_sdram, x, y, (pInt16U)SDRAM0_BASE_ADDR);
}
void Pear_dis(Int16U x, Int16U y)//鸭梨
{
Bmp_Decode((Int32U)PEAR_sdram, x, y, (pInt16U)SDRAM0_BASE_ADDR);
}
void Fkey_Up_dis(Int16U x, Int16U y)//F键up
{
Bmp_Decode((Int32U)F_KEY_UP_sdram, x, y, (pInt16U)SDRAM0_BASE_ADDR);
}
void FrontPage_Up_dis(Int16U x, Int16U y)//前进up
{
Bmp_Decode((Int32U)FRONT_PAGE_UP_sdram, x, y, (pInt16U)SDRAM0_BASE_ADDR);
}
void BackPage_Up_dis(Int16U x, Int16U y)//后退up
{
Bmp_Decode((Int32U)BACK_PAGE_UP_sdram, x, y, (pInt16U)SDRAM0_BASE_ADDR);
}
void UpArrow_Up_dis(Int16U x, Int16U y)//上箭头up
{
Bmp_Decode((Int32U)UP_ARROW_UP_sdram, x, y, (pInt16U)SDRAM0_BASE_ADDR);
}
void DownArrow_Up_dis(Int16U x, Int16U y)//下箭头up
{
Bmp_Decode((Int32U)DOWN_ARROW_UP_sdram, x, y, (pInt16U)SDRAM0_BASE_ADDR);
}
void F3plus_Up_dis(Int16U x, Int16U y)//F3++up
{
Bmp_Decode((Int32U)F3_PLUS_UP_sdram, x, y, (pInt16U)SDRAM0_BASE_ADDR);
}
void F3clock_Up_dis(Int16U x, Int16U y)//F3时钟up
{
Bmp_Decode((Int32U)F3_CLOCK_UP_sdram, x, y, (pInt16U)SDRAM0_BASE_ADDR);
}
void F4minus_Up_dis(Int16U x, Int16U y)//F4--up
{
Bmp_Decode((Int32U)F4_MINUS_UP_sdram, x, y, (pInt16U)SDRAM0_BASE_ADDR);
}
void F5cut_Up_dis(Int16U x, Int16U y)//F5刀up
{
Bmp_Decode((Int32U)F5_CUT_UP_sdram, x, y, (pInt16U)SDRAM0_BASE_ADDR);
}
void PulseDegree_dis(Int16U x, Int16U y)//脉冲当量
{
Int32U buf_add=(Int32U)PULSE_DEGREE_sdram;
switch(Language)	
	{
	case CHN_HAN:
			buf_add=(Int32U)PULSE_DEGREE_sdram;
			break;
	case ENGLISH:
			buf_add=(Int32U)PULSE_DEGREE_EN_sdram;
			break;		
	}
Bmp_Decode(buf_add, x, y, (pInt16U)SDRAM0_BASE_ADDR);
}
void Lock_dis(Int16U x, Int16U y)//锁
{
Int32U buf_add=(Int32U)LOCK_sdram;
switch(Language)	
	{
	case CHN_HAN:
			buf_add=(Int32U)LOCK_sdram;
			break;
	case ENGLISH:
			buf_add=(Int32U)LOCK_EN_sdram;
			break;		
	}
Bmp_Decode(buf_add, x, y, (pInt16U)SDRAM0_BASE_ADDR);
}
void LockKey_dis(Int16U x, Int16U y)//锁 钥匙
{
Bmp_Decode((Int32U)LOCK_KEY_sdram, x, y, (pInt16U)SDRAM0_BASE_ADDR);
}
void L_R_Arrow_dis(Int16U x, Int16U y)//左右箭头
{
Bmp_Decode((Int32U)L_R_ARROW_sdram, x, y, (pInt16U)SDRAM0_BASE_ADDR);
}
void FastFWD_Up_dis(Int16U x, Int16U y)//快进up
{
Bmp_Decode((Int32U)FAST_FORWD_UP_sdram, x, y, (pInt16U)SDRAM0_BASE_ADDR);
}
void FastBACK_Up_dis(Int16U x, Int16U y)//快退up
{
Bmp_Decode((Int32U)FAST_BACK_UP_sdram, x, y, (pInt16U)SDRAM0_BASE_ADDR);
}
void F4Wheel0_dis(Int16U x, Int16U y)//F4 电子手轮关0
{
Bmp_Decode((Int32U)F4_WHEEL0_sdram, x, y, (pInt16U)SDRAM0_BASE_ADDR);
}

void F4Wheel1_dis(Int16U x, Int16U y)//F4 电子手轮开1
{
Bmp_Decode((Int32U)F4_WHEEL1_sdram, x, y, (pInt16U)SDRAM0_BASE_ADDR);
}

void Wheel0_dis(Int16U x, Int16U y)//手轮关0 指示
{
Bmp_Decode((Int32U)WHEEL0_sdram, x, y, (pInt16U)SDRAM0_BASE_ADDR);
}

void Wheel1_dis(Int16U x, Int16U y)//手轮开1 指示
{
Bmp_Decode((Int32U)WHEEL1_sdram, x, y, (pInt16U)SDRAM0_BASE_ADDR);
}

void F0ALLCUT_YES_dis(Int16U x, Int16U y)//F0 标记所有刀 标记
{
Bmp_Decode((Int32U)F0_YESALLCUT_sdram, x, y, (pInt16U)SDRAM0_BASE_ADDR);
}
void F0ALLCUT_NO_dis(Int16U x, Int16U y)//F0 取消所有刀 标记XXXXXXXXXXX
{
Bmp_Decode((Int32U)F0_NOALLCUT_sdram, x, y, (pInt16U)SDRAM0_BASE_ADDR);
}

void F5CUT_YES_dis(Int16U x, Int16U y)//F5 标记一个 刀 标记
{
Bmp_Decode((Int32U)F5_YESCUT_sdram, x, y, (pInt16U)SDRAM0_BASE_ADDR);
}
void F5CUT_NO_dis(Int16U x, Int16U y)//F5 取消一个 刀 标记XXXXXXXXXXX
{
Bmp_Decode((Int32U)F5_NOCUT_sdram, x, y, (pInt16U)SDRAM0_BASE_ADDR);
}
void F5PreCircleButt_Up_dis(Int16U x, Int16U y)//F5压纸循环button up
{
Bmp_Decode((Int32U)F5_PRE_FLG_BUTT_UP_sdram, x, y, (pInt16U)SDRAM0_BASE_ADDR);
}

void F5Button_dis(Int8U flag)  //F5 一个 刀 标记 按钮/
{
if((WorkMode==AUTO_MODE)||(WorkMode==PROG_MODE))//自动主画面下
	{
	if(InputTouch_flag==0) //非触摸下
		{
		if(flag==KNIFE_FLAG) //刀 标志
			{
			F5CUT_NO_dis(F5_CUTYES_X, F5_CUTYES_Y);//F5 取消一个 刀 标记
			}
		else
			{
			F5CUT_YES_dis(F5_CUTYES_X, F5_CUTYES_Y);//F5 标记一个 刀 标记
			}
		}
	}
}

void F0Button_dis(Int8U flag)  //F0 所有 刀 标记 按钮//////////////
{
if(WorkMode==AUTO_MODE)//自动主画面下
	{
	if(InputTouch_flag==0) //非触摸下
		{
		if(flag==1) //刀 标志
			{
			F0ALLCUT_NO_dis(F0_CUTYES_X, F0_CUTYES_Y);//F0 取消 所有刀 标记
			}
		else
			{
			F0ALLCUT_YES_dis(F0_CUTYES_X, F0_CUTYES_Y);//F0 标记 所有刀 标记
			}
		}
	}
}

void CancelCutflagButton_dis(void)  //取消显示  刀 标记 按钮
{
Int16U x,y,back_color=0xef9f;
x=F5_CUTYES_X;
y=F5_CUTYES_Y;
GLCD_SetWindow_Fill( x, y, x+215, y+31, back_color, back_color);//图标消失
}



void ElectricalWheel_dis(void)  //电子手轮  开关状态
{
if(MotorType==MOTOR_AC_SERVO)
	{
	if(ElectricWheelOn_flag==0)
		{
		Wheel0_dis(WHEEL_STA_X, WHEEL_STA_Y);
		if(WorkMode==MANUAL_MODE)
			F4Wheel0_dis(F4_WHEEL_X,F4_WHEEL_Y);
		}
	else	
		{
		Wheel1_dis(WHEEL_STA_X, WHEEL_STA_Y);
		if(WorkMode==MANUAL_MODE)
			F4Wheel1_dis(F4_WHEEL_X,F4_WHEEL_Y);
		}
	}
}
void DeleteWheelStus(void)	//电子手轮  取消显示
{
Int16U x,y;
Int16U color=0xef9f;
x=WHEEL_STA_X,y=WHEEL_STA_Y;
GLCD_SetWindow_Fill(x,y,x+64,y+64,color,color);//
}

//-----------各个 模式下 画面内容page  显示************************
void ProgModePage_dis(void)  //编程模式 部分画面更新
{
Int16U x1,y1,x2,y2,color;
color=0xef9f;
x1=RIGHT_ARROW_X,y1=RIGHT_ARROW_Y;
x2=RED_KNIFE_X+25,y2=RIGHT_ARROW_Y+225;
GLCD_SetWindow_Fill(x1,y1,x2,y2,color,color);//空白列表
GLCD_SetWindow_Fill(F5_PRE_FLG_X,F5_PRE_FLG_Y,F5_PRE_FLG_X+48,F5_PRE_FLG_Y+48,color,color);//空白F5 flag
F1up_dis(F1_X,F1_Y);//F1
F2up_dis(F2_X,F2_Y);
F3up_dis(F3_X,F3_Y);
F4up_dis(F4_X,F4_Y);
Program_dis(PROGRAM_X,PROGRAM_Y);   //编程
if(TOUCH_ENB==1)
{
FrontPage_Up_dis( FRONT_PAGE_X,  FRONT_PAGE_Y);//前一页up
BackPage_Up_dis( BACK_PAGE_X,  BACK_PAGE_Y);//后一页up
UpArrow_Up_dis( UP_ARROW_X,  UP_ARROW_Y);//上箭头up
DownArrow_Up_dis( DOWN_ARROW_X,  DOWN_ARROW_Y);//下箭头up
}
//color=0x2e3b;
color=0xce79;
GLCD_SetWindow_Fill(STOP_X,STOP_Y,STOP_X+82,STOP_Y+32,color,color);
if(TOUCH_ENB==1)
{
//////Delete_Up_dis( DELETE_X, DELETE_Y );//删除up
//////DeleteAll_Up_dis( DELETE_ALL_X, DELETE_ALL_Y);//全删up


CancelCutflagButton_dis(); //取消显示  刀 标记 按钮
	}
DeleteWheelStus();	//电子手轮  取消显示
}
void AutoModePage_dis(void) //自动模式 部分画面显示
{
Int16U x1,y1,x2,y2,color;
color=0xef9f;
x1=RIGHT_ARROW_X,y1=RIGHT_ARROW_Y;
x2=RED_KNIFE_X+25,y2=RIGHT_ARROW_Y+225;
GLCD_SetWindow_Fill(x1,y1,x2,y2,color,color);//空白列表

Auto_dis(AUTO_X, AUTO_Y); //自动模式
F1Ruler_Up_dis(F1_RULER_X, F1_RULER_Y);//F1 尺子
F2Tools_Up_dis(F2_TOOLS_X, F2_TOOLS_Y);//F2 工具
F3plus_Up_dis(F3_PLUS_X, F3_PLUS_Y);//F3++
F4minus_Up_dis(F4_MINUS_X, F4_MINUS_Y);//F4--

if(TOUCH_ENB==1)
{
FrontPage_Up_dis( FRONT_PAGE_X,  FRONT_PAGE_Y);//前一页up
BackPage_Up_dis( BACK_PAGE_X,  BACK_PAGE_Y);//后一页up
UpArrow_Up_dis( UP_ARROW_X,  UP_ARROW_Y);//上箭头up
DownArrow_Up_dis( DOWN_ARROW_X,  DOWN_ARROW_Y);//下箭头up
F5PreCircleButt_Up_dis(F5_PRE_FLG_X,F5_PRE_FLG_Y);
}
//color=0x2e3b;
color=0xce79;
GLCD_SetWindow_Fill(DELETE_X,DELETE_Y,DELETE_X+180,DELETE_Y+32,color,color);
//Delete_Up_dis( DELETE_X, DELETE_Y );//删除up
//DeleteAll_Up_dis( DELETE_ALL_X, DELETE_ALL_Y);//全删up
if(TOUCH_ENB==1)
{
Run_Up_dis(RUN_X,RUN_Y);//运行up
Stop_Up_dis(STOP_X,STOP_Y);//停止up
}
ElectricalWheel_dis();  //电子手轮  开关状态
}

void ManualModePage_dis(void)  //手动模式
{
Int16U x1,y1,x2,y2,color;
color=0xef9f;
x1=RIGHT_ARROW_X,y1=RIGHT_ARROW_Y;
x2=RED_KNIFE_X+25,y2=RIGHT_ARROW_Y+225;
GLCD_SetWindow_Fill(x1,y1,x2,y2,color,color);//空白列表
GLCD_SetWindow_Fill(F5_PRE_FLG_X,F5_PRE_FLG_Y,F5_PRE_FLG_X+48,F5_PRE_FLG_Y+48,color,color);//空白F5 flag
x1=FRONT_PAGE_X,y1=UP_ARROW_Y;
x2=DOWN_ARROW_X+50,y2=DOWN_ARROW_Y+50;
GLCD_SetWindow_Fill(x1,y1,x2,y2,color,color);  //隐藏方向箭头
	
if(TOUCH_ENB==1)
{
FrontPage_Up_dis( MAN_FRONT_PAGE_X,  MAN_FRONT_PAGE_Y);//前一页up
BackPage_Up_dis( MAN_BACK_PAGE_X,  MAN_BACK_PAGE_Y);//后一页up
FastFWD_Up_dis(MAN_FAST_FWD_X, MAN_FAST_FWD_Y);//快进up
FastBACK_Up_dis(MAN_FAST_BACK_X, MAN_FAST_BACK_Y);//快退up
Stop_Up_dis(MAN_STOP_X,MAN_STOP_Y);//停止up
}

//color=0x1b1b;
color=0x9cd3;
//F1Ruler_Up_dis(F1_RULER_X, F1_RULER_Y);//F1 尺子
//F2Tools_Up_dis(F2_TOOLS_X, F2_TOOLS_Y);//F2 工具
	
F1up_Manual_dis(F1_RULER_X, F1_RULER_Y);//F1 工具
F2up_Manual_dis(F2_TOOLS_X, F2_TOOLS_Y);//F2 尺子

F3clock_Up_dis(F3_CLOCK_X,F3_CLOCK_Y);  //F3时钟

GLCD_SetWindow_Fill(F4_X,F4_Y,F4_X+48,F4_Y+48,color,color);
//color=0x2e3b;
color=0xce79;
GLCD_SetWindow_Fill(DELETE_X,DELETE_Y,DELETE_X+272,DELETE_Y+32,color,color);
//Stop_Up_dis(STOP_X,STOP_Y);//停止up
ElectricalWheel_dis();  //电子手轮  开关状态
Manual_dis(MANUAL_X,MANUAL_Y);
CancelCutflagButton_dis(); //取消显示  刀 标记 按钮
}

void TeachPage_dis(void)   //示教模式  页面
{
Int16U x1,y1,x2,y2,color;
color=0xef9f;
x1=RIGHT_ARROW_X,y1=RIGHT_ARROW_Y;
x2=RED_KNIFE_X+25,y2=RIGHT_ARROW_Y+225;
GLCD_SetWindow_Fill(x1,y1,x2,y2,color,color);//空白列表
GLCD_SetWindow_Fill(F5_PRE_FLG_X,F5_PRE_FLG_Y,F5_PRE_FLG_X+48,F5_PRE_FLG_Y+48,color,color);//空白F5 flag

F1up_dis(F1_X,F1_Y);//F1
F2up_dis(F2_X,F2_Y);
F3up_dis(F3_X,F3_Y);
F4up_dis(F4_X,F4_Y);
Teach_dis(TEACH_X,TEACH_Y);   //示教

FrontPage_Up_dis( FRONT_PAGE_X,  FRONT_PAGE_Y);//前一页up
BackPage_Up_dis( BACK_PAGE_X,  BACK_PAGE_Y);//后一页up
UpArrow_Up_dis( UP_ARROW_X,  UP_ARROW_Y);//上箭头up
DownArrow_Up_dis( DOWN_ARROW_X,  DOWN_ARROW_Y);//下箭头up
//color=0x2e3b;
color=0xce79;
GLCD_SetWindow_Fill(STOP_X,STOP_Y,STOP_X+82,STOP_Y+32,color,color);
	if(TOUCH_ENB==1)
	{
//////Delete_Up_dis( DELETE_X, DELETE_Y );//删除up
//////DeleteAll_Up_dis( DELETE_ALL_X, DELETE_ALL_Y);//全删up
	}
CancelCutflagButton_dis(); //取消显示  刀 标记 按钮
DeleteWheelStus();	//电子手轮  取消显示
}


//**************************************编程 下
void ProgSet_dis(Int32U size, Int16U x, Int16U y, Int8U set_flag)// 参数设定页内 尺寸显示
{
Int8U num[8],k,int_flag=0;
Int16U back_color=0xef9f;
switch(WorkMode)
	{
	case PROG_LABEL_MODE://已在 标签画面		
	case TEACH_LABEL_MODE://已在 标签画面		
	case PROG_DIVIDE_MODE://已在 等分画面 		
	case TEACH_DIVIDE_MODE://已在 等分画面 		
	//case PROG_PRO_MODE://已在  程序选择画面
	//case AUTO_RULER_MODE:	//基准模式		
	case AUTO_TOOLS_MODE:// 已在  自动 -------参数模式
	case SELF_TOOLS_MODE:// 已在  自刀 -------参数模式
	case MANUAL_TOOLS_MODE:// 手动 参数模式
			
		if(((WorkMode==PROG_DIVIDE_MODE)||(WorkMode==TEACH_DIVIDE_MODE))&&(PorgSet_sel==1)) //等分数
			{
			if(PorgSet_sel==1)
				{
				num[0]=size/1000+48;
				num[1]=(size/100)%10+48;
				num[2]=(size/10)%10+48;
				num[3]=size%10+48;
				num[4]=0;
				int_flag=1;
				}
			else
				int_flag=0;
			}	
		else
			{
			int_flag=0;
			}
			//------------------------
		if(int_flag==0)	// 带小数
			{
			num[0]=size/100000;
			num[1]=(size/10000)%10;
			num[2]=(size/1000)%10;
			num[3]=(size/100)%10;
			num[4]='.';
			num[5]=(size/10)%10;
			num[6]=size%10;
			num[7]=0;
			if(Unit!=UNIT_MM)//mm
				{
				num[4]=num[3];
				num[3]='.';
				}
			for(k=0;k<7;k++)
				{
				if(num[k]!='.')
					num[k]+=48;
				}
			}
			break;
	case MANUAL_CLOCK_MODE: //手动 时间 模式
			num[0]=((size>>4)&0x0F)+48;
			num[1]=(size&0x0F)+48;
			num[2]=0;
			break;
	case MANUAL_PASS_MODE://密码模式
			num[0]=size/100+48;
			num[1]=(size/10)%10+48;
			num[2]=size%10+48;
			num[3]=0;
			break;
	case MANUAL_SERVO_C_MODE:			//直流伺服 C 参数
			num[0]=size/1000+48;
			num[1]=(size/100)%10+48;
			num[2]=(size/10)%10+48;
			num[3]=size%10+48;
			num[4]=0;
			break;
	}

if(set_flag==1)
   {
   Printf24(num,x,y,back_color,1,BLACK_COLOR);//
   }
else
   {
   Printf24(num,x,y,BLACK_COLOR,1,back_color);//
   }
}

void LabelPage_dis(void)  //标签模式 画面显示
{
volatile Int16U x,y,gap;
 x=80,y=200,gap=50;
CurrentArea_save2(MIDDLE_PAGE_X , MIDDLE_PAGE_Y,  M_PAGE_WIDE, M_PAGE_HIGH);
MiddlePage_dis(MIDDLE_PAGE_X,MIDDLE_PAGE_Y);//中间活页
PushPaperTool_dis(PUSH_PAPER_TOOL_X,PUSH_PAPER_TOOL_Y);//推纸器
FrontKnife_dis(FRONT_KNIFE_X,FRONT_KNIFE_Y);//刀前
CurrentSize_dis(CurrentSize_temp); //当前尺寸 更新显示
CurrUint_dis(Unit);  //当前尺寸 单位
if(BeforeKnifeNo_flag==0)
	FrontKnifeSize_dis(BeforeKnifeSize);

LabelFun_dis(LABEL_FUN_X,LABEL_FUN_Y);//标签功能
Label_dis(LABELS_X,LABELS_Y);//标签
Finish_dis(FINISHED_X,FINISHED_Y);//完成
F2out_Up_dis(F2OUT_X,F2OUT_Y);//F2up退出
if(TOUCH_ENB==1)
{
UpArrow_Up_dis( SUB_UP_ARROW_X,  SUB_UP_ARROW_Y);//上箭头up
DownArrow_Up_dis( SUB_DOWN_ARROW_X,  SUB_DOWN_ARROW_Y);//下箭头up
}
				//左边
switch(Language)
	{
	case CHN_HAN:
		Printf24("总长：",x,y,BLACK_COLOR,0,0xffff);y+=gap;
		Printf24("标签：",x,y,BLACK_COLOR,0,0xffff);y+=gap;
		Printf24("废边：",x,y,BLACK_COLOR,0,0xffff);
			break;
	case ENGLISH:
		Printf24("Total len:",x,y,BLACK_COLOR,0,0xffff);y+=gap;
		Printf24("Label：",x,y,BLACK_COLOR,0,0xffff);y+=gap;
		Printf24("Waste：",x,y,BLACK_COLOR,0,0xffff);
			break;
	}	
ProgSet_dis( 0, TOTAL_SIZE_X,  TOTAL_SIZE_Y,1);//
ProgSet_dis( 0, LABEL_SIZE_X,  LABEL_SIZE_Y,0);
ProgSet_dis( 0, WASTE_SIZE_X,  WASTE_SIZE_Y,0);
}

void DividePage_dis(void)  //等分模式 画面显示
{
volatile Int16U x,y,gap;
 x=80,y=200,gap=60;
CurrentArea_save2(MIDDLE_PAGE_X , MIDDLE_PAGE_Y,  M_PAGE_WIDE, M_PAGE_HIGH);
MiddlePage_dis(MIDDLE_PAGE_X,MIDDLE_PAGE_Y);//中间活页
PushPaperTool_dis(PUSH_PAPER_TOOL_X,PUSH_PAPER_TOOL_Y);//推纸器
FrontKnife_dis(FRONT_KNIFE_X,FRONT_KNIFE_Y);//刀前
CurrentSize_dis(CurrentSize_temp); //当前尺寸 更新显示
CurrUint_dis(Unit);  //当前尺寸 单位
if(BeforeKnifeNo_flag==0)
	FrontKnifeSize_dis(BeforeKnifeSize);

DivideFun_dis(DIVIDE_FUN_X,DIVIDE_FUN_Y);//等分功能
Divide_dis(DIVIDE_X,DIVIDE_Y);//等分
Finish_dis(FINISHED_X,FINISHED_Y);//完成
F2out_Up_dis(F2OUT_X,F2OUT_Y);//F2up退出

if(TOUCH_ENB==1)
{
UpArrow_Up_dis( SUB_UP_ARROW_X,  SUB_UP_ARROW_Y);//上箭头up
DownArrow_Up_dis( SUB_DOWN_ARROW_X,  SUB_DOWN_ARROW_Y);//下箭头up
}
//左边
switch(Language)
	{
	case CHN_HAN:
		Printf24("总长：",x,y,BLACK_COLOR,0,0xffff);y+=gap;
		Printf24("等分数：",x,y,BLACK_COLOR,0,0xffff);
			break;
	case ENGLISH:	
		Printf24("Total len：",x,y,BLACK_COLOR,0,0xffff);y+=gap;
		Printf24("Divider：",x,y,BLACK_COLOR,0,0xffff);
			break;
	}


ProgSet_dis( 0, DIVIDE_TOTAL_X,  DIVIDE_TOTAL_Y,1);//
PorgSet_sel=1;
ProgSet_dis( 0, DIVIDE_NUM_X,  DIVIDE_NUM_Y,0);
PorgSet_sel=0;
}

void SelProgPage_dis(void) //程序 选择 画面显示
{
volatile Int16U x,y;
 x=90,y=115;
CurrentArea_save2(MIDDLE_PAGE_X , MIDDLE_PAGE_Y,  M_PAGE_WIDE, M_PAGE_HIGH);
MiddlePage_dis(MIDDLE_PAGE_X,MIDDLE_PAGE_Y);//中间活页
PushPaperTool_dis(PUSH_PAPER_TOOL_X,PUSH_PAPER_TOOL_Y);//推纸器
FrontKnife_dis(FRONT_KNIFE_X,FRONT_KNIFE_Y);//刀前
CurrentSize_dis(CurrentSize_temp); //当前尺寸 更新显示
CurrUint_dis(Unit);  //当前尺寸 单位
if(BeforeKnifeNo_flag==0)
	FrontKnifeSize_dis(BeforeKnifeSize);

SelectPro_dis(SELECT_PRO_X,SELECT_PRO_Y); //选择程序
Finish_dis(FINISHED_X,FINISHED_Y);//完成
F2out_Up_dis(F2OUT_X,F2OUT_Y);//F2up退出
if(TOUCH_ENB==1)
{
UpArrow_Up_dis( SUB_UP_ARROW_X,  SUB_UP_ARROW_Y);//上箭头up
DownArrow_Up_dis( SUB_DOWN_ARROW_X,  SUB_DOWN_ARROW_Y);//下箭头up
}

//左边
switch(Language)
	{
	case CHN_HAN:
		Printf16("程序号码      第一刀数据",x,y,YELLOW_COLOR,0,0xffff);
			break;
	case ENGLISH:	
		Printf16("Process      First data",x,y,YELLOW_COLOR,0,0xffff);
			break;
	}
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
Printf24("1        500",REMIND_WINDOW_X+180,REMIND_WINDOW_Y+5,RED_COLOR,0,0xffff);
}

//******************************************手 ，自动 ，自刀 下
void ParameterPage_dis(Int8U sel, Int8U flag) //参数 设置显示
{
volatile Int16U x,y,gap;
Int16U front_color,back_color;
gap=30;x=PARA_START_X2+(sel/7)*PARA_COL_WIDE;
Int32U temp;
if(flag==1)
    {
	front_color=0xef9f;
	back_color=BLACK_COLOR;
	}
else
	{
	front_color=BLACK_COLOR;
	back_color=0xef9f;
	}
y=PARA_START_Y+gap*(sel%7);
GLCD_SetWindow_Fill( REMIND_WINDOW_X, REMIND_WINDOW_Y, REMIND_WINDOW_X+REMIND_LENGTH, REMIND_WINDOW_Y+30, 0xfffff, 0xffff);//提示框

switch(sel)
	{
	case 0:
		if(Unit==UNIT_MM)
			{
			temp=FrontLimit;
			}
		else
			{
			temp=FrontLimit*100/254;
			}
		ProgSet_dis(temp,  x,  y,  flag); //前极限
		if(flag==1)
			{
			switch(Language)
				{
				case CHN_HAN:
					Printf24("输入数值范围        到",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,BLACK_COLOR,0,0xffff);
						break;
				case ENGLISH:	
					Printf24("Data range          to",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,BLACK_COLOR,0,0xffff);
						break;
				}
			if(Unit==UNIT_MM)
				Printf24("15       80",REMIND_WINDOW_X+180,REMIND_WINDOW_Y+5,RED_COLOR,0,0xffff);
			else
				Printf24("0.6      3.15",REMIND_WINDOW_X+180,REMIND_WINDOW_Y+5,RED_COLOR,0,0xffff);
			}
		break;
	case 1:
		if(Unit==UNIT_MM)
			temp=MiddleLimit;
		else
			temp=MiddleLimit*100/254;
		ProgSet_dis(temp,  x,  y,  flag); //中极限
		if(flag==1)
			{
			switch(Language)
				{
				case CHN_HAN:
					Printf24("输入数值范围        到",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,BLACK_COLOR,0,0xffff);
						break;
				case ENGLISH:	
					Printf24("Data range          to",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,BLACK_COLOR,0,0xffff);
						break;
				}
			if(Unit==UNIT_MM)
				Printf24("30     	150",REMIND_WINDOW_X+180,REMIND_WINDOW_Y+5,RED_COLOR,0,0xffff);
			else
				Printf24("1.19      5.9",REMIND_WINDOW_X+180,REMIND_WINDOW_Y+5,RED_COLOR,0,0xffff);
			}
		break;
	case 2:
		if(Unit==UNIT_MM)
			temp=BackLimit;
		else
			temp=BackLimit*100/254;
		ProgSet_dis(temp,  x,  y,  flag); //后极限
		if(flag==1)
			{
			switch(Language)
				{
				case CHN_HAN:
					Printf24("输入机器型号        到",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,BLACK_COLOR,0,0xffff);
						break;
				case ENGLISH:	
					Printf24("Machine type        to",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,BLACK_COLOR,0,0xffff);
						break;
				}
			if(Unit==UNIT_MM)	
				Printf24("600      2200",REMIND_WINDOW_X+180,REMIND_WINDOW_Y+5,RED_COLOR,0,0xffff);
			else
				Printf24("23.63    86.61",REMIND_WINDOW_X+180,REMIND_WINDOW_Y+5,RED_COLOR,0,0xffff);
			}
		break;
	case 3:
		switch(Language)
			{
			case CHN_HAN:
				Printf24("中文   ",x,y,front_color,1,back_color); //语言
					break;
			case ENGLISH:
				Printf24("English",x,y,front_color,1,back_color); //语言
					break;
			}
		if(flag==1)
			{
			switch(Language)
				{
				case CHN_HAN:
					Printf24("按插入键,切换语言!           ",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,BLACK_COLOR,0,0xffff);
					break;
				case ENGLISH:	
					Printf24("Press INSERT,change language!",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,BLACK_COLOR,0,0xffff);
					break;
				}	
			}	
		break;
	case 4:
		if(Unit==UNIT_MM)//mm  单位
			{
			//GLCD_SetWindow_Fill(x,y,front_color,1,back_color);
			Printf24("mm",x,y,front_color,1,back_color); //
			}
		else
			{
			Printf24("in",x,y,front_color,1,back_color); //
			}
		if(flag==1)
			{
			switch(Language)
				{
				case CHN_HAN:
					Printf24("按插入键,切换公英制!",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,BLACK_COLOR,0,0xffff);
					break;
				case ENGLISH:	
					Printf24("Press INSERT,change unit!",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,BLACK_COLOR,0,0xffff);
					break;
				}
			}	
		break;
	case 5:  //提前量
		if(Unit==UNIT_MM)//mm  单位
			temp=Aheader;
		else
			temp=Aheader*100/254;
		ProgSet_dis(temp,  x,  y,  flag);
		if(flag==1)
			{
			switch(Language)
				{
				case CHN_HAN:
					Printf24("输入数据范围        到",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,BLACK_COLOR,0,0xffff);
					break;
				case ENGLISH:	
					Printf24("Data range          to ",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,BLACK_COLOR,0,0xffff);
					break;
				}
			if(Unit==UNIT_MM)
				Printf24("0       1",REMIND_WINDOW_X+200,REMIND_WINDOW_Y+5,RED_COLOR,0,0xffff);
			else
				Printf24("0      0.038",REMIND_WINDOW_X+200,REMIND_WINDOW_Y+5,RED_COLOR,0,0xffff);
			}
		break;
		/*
	case 6://标准距离
		ProgSet_dis(StanDistance,  x,  y,  flag);
		if(flag==1)
			{
			switch(Language)
				{
				case CHN_HAN:
					Printf24("原点开关距离z脉冲距离     ",REMIND_WINDOW_X,REMIND_WINDOW_Y+5,BLACK_COLOR,0,0xffff);
					break;
				case ENGLISH:	
					Printf24("Distance from orignal to Z",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,BLACK_COLOR,0,0xffff);
					break;
				}
			}
		break;*/
	case 6://自动推纸距离
		if(Unit==UNIT_MM)//mm  单位
			temp=AutoPushDistance;
		else
			temp=AutoPushDistance*100/254;
		ProgSet_dis(temp,  x,  y,  flag);
		if(flag==1)
			{
			switch(Language)
				{
				case CHN_HAN:
					Printf24("有效(     -     ),无效(0-     )",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,BLACK_COLOR,0,0xffff);
					break;
				case ENGLISH:	
					Printf24("Valid(    -   ),Invalid(0-    )",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,BLACK_COLOR,0,0xffff);
					break;
				}
			if(Unit==UNIT_MM)
				Printf24("11   500            10",REMIND_WINDOW_X+85,REMIND_WINDOW_Y+5,RED_COLOR,0,0xffff);
			else
				Printf24("0.44  19            0.4",REMIND_WINDOW_X+82,REMIND_WINDOW_Y+5,RED_COLOR,0,0xffff);	
			}
		break;
	case 7:  //压纸有效 标志
		if(PressValid_flag==0)
			{
			switch(Language)
				{
				case CHN_HAN:
					Printf24("无效   ",x,y,front_color,1,back_color); //
						break;
				case ENGLISH:
					Printf24("Invalid",x,y,front_color,1,back_color); //
						break;
				}		
			}
		else 
			{
			switch(Language)
				{
				case CHN_HAN:
					Printf24("有效   ",x,y,front_color,1,back_color); //
						break;
				case ENGLISH:
					Printf24("Valid  ",x,y,front_color,1,back_color); //
						break;
				}	
			}
		if(flag==1)	
			{
			switch(Language)
				{
				case CHN_HAN:
					Printf24("按插入键,切换压纸停机功能!     ",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,BLACK_COLOR,0,0xffff);
					break;
				case ENGLISH:	
					Printf24("Press INSERT,change Press-Stop!",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,BLACK_COLOR,0,0xffff);
					break;
				}
			}
		break;	
		//--------------------------------直流伺服设定速度
	case 8: //	最大速度
		if((MotorType>=MOTOR_DC_SERVO)&&(MotorType<=MOTOR_DC670_SERVO_ZHU))
			{
			if(Unit==UNIT_MM)//mm  单位
				temp=ServoSpeed_order*100;
			else
				temp=ServoSpeed_order*1000;
			ProgSet_dis(temp,  x,  y,  flag);
			}
		else if(MotorType==MOTOR_AC_SERVO)
			{
			if(Unit==UNIT_MM)//mm  单位
				temp=AC_MotorSPD*100;
			else
				temp=AC_MotorSPD*1000;
			ProgSet_dis(temp,  x,  y,  flag);
			}
		else
			{//误差范围
			temp=DisWuCha;
			ProgSet_dis(temp,  x,  y,  flag);
			if(flag==1)
				{
				switch(Language)
					{
					case CHN_HAN:
						Printf24("输入数据范围        到",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,BLACK_COLOR,0,0xffff);
						break;
					case ENGLISH:	
						Printf24("Data range          to ",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,BLACK_COLOR,0,0xffff);
						break;
					}
				if((MotorType>=MOTOR_DC_SERVO)&&(MotorType<=MOTOR_DC670_SERVO_ZHU))
					{
					if(MotorType==MOTOR_DC670_SERVO_ZHU)
						Printf24("5     20",REMIND_WINDOW_X+200,REMIND_WINDOW_Y+5,RED_COLOR,0,0xffff);
					else
						Printf24("13     20",REMIND_WINDOW_X+200,REMIND_WINDOW_Y+5,RED_COLOR,0,0xffff);
					}
				else if(MotorType==MOTOR_AC_SERVO)	
					Printf24("0      24",REMIND_WINDOW_X+200,REMIND_WINDOW_Y+5,RED_COLOR,0,0xffff);
				else
					{
						Printf24("0.20      1.00",REMIND_WINDOW_X+180,REMIND_WINDOW_Y+5,RED_COLOR,0,0xffff);
					}
				}	
				
			break;
			}
		if(flag==1)
			{
			switch(Language)
				{
				case CHN_HAN:
					Printf24("输入数据范围        到",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,BLACK_COLOR,0,0xffff);
					break;
				case ENGLISH:	
					Printf24("Data range          to ",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,BLACK_COLOR,0,0xffff);
					break;
				}
			if((MotorType>=MOTOR_DC_SERVO)&&(MotorType<=MOTOR_DC670_SERVO_ZHU))
				{
				if(MotorType==MOTOR_DC670_SERVO_ZHU)
					Printf24("5     20",REMIND_WINDOW_X+200,REMIND_WINDOW_Y+5,RED_COLOR,0,0xffff);
				else
					Printf24("13     20",REMIND_WINDOW_X+200,REMIND_WINDOW_Y+5,RED_COLOR,0,0xffff);
				}
			else if(MotorType==MOTOR_AC_SERVO)	
				Printf24("0      32",REMIND_WINDOW_X+200,REMIND_WINDOW_Y+5,RED_COLOR,0,0xffff);
			}	
		break;
	case 9: //	点动速度
		ProgSet_dis(JogSpeed_order*100,  x,  y,  flag);
		if(flag==1)
			{
			switch(Language)
				{
				case CHN_HAN:
					Printf24("输入数据范围        到",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,BLACK_COLOR,0,0xffff);
					break;
				case ENGLISH:	
					Printf24("Data range          to ",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,BLACK_COLOR,0,0xffff);
					break;
				}
			Printf24("10     20",REMIND_WINDOW_X+200,REMIND_WINDOW_Y+5,RED_COLOR,0,0xffff);
			}	
		break;	
	}
}

void ParameterPage2_dis(Int8U sel, Int8U flag) //参数 设置显示
{
volatile Int16U x,y,gap,tx_wide=88;
Int16U front_color,back_color,TEXT_TAB_BACK_COLOR=0xef9f;
gap=30;x=PARA_START_X2+(sel/7)*PARA_COL_WIDE;
Int32U temp;
if(flag==1)
    {
	front_color=0xef9f;
	back_color=BLACK_COLOR;
	}
else
	{
	front_color=BLACK_COLOR;
	back_color=0xef9f;
	}
y=PARA_START_Y+gap*(sel%7);
GLCD_SetWindow_Fill( REMIND_WINDOW_X, REMIND_WINDOW_Y, REMIND_WINDOW_X+REMIND_LENGTH, REMIND_WINDOW_Y+30, 0xfffff, 0xffff);//提示框

switch(sel)	
	{
	case 0://IR
		GLCD_SetWindow_Fill( x, y, x+tx_wide, y+24, TEXT_TAB_BACK_COLOR, TEXT_TAB_BACK_COLOR);//clear text win
			if(IR_SensorStus==1)		//红外  有效电平
				{
				switch(Language)
					{
					case CHN_HAN:
						Printf24("高有效",x,y,front_color,1,back_color); //
							break;
					case ENGLISH:
						Printf24("High ",x,y,front_color,1,back_color); //
							break;
					// case INDONSIA:	//印尼
						// Printf24("Tinggi",x,y,front_color,1,back_color); //
							// break;
					// case PORTUGAL:	//葡萄牙
					// case SPANISH: //西班牙
						// Printf24("alto",x,y,front_color,1,back_color); //
							// break;
					}		
				}
			else
				{
				switch(Language)
					{
					case CHN_HAN:
						Printf24("低有效",x,y,front_color,1,back_color); //
							break;
					case ENGLISH:
						Printf24("Low  ",x,y,front_color,1,back_color); //
							break;
					// case INDONSIA:	//印尼
						// Printf24("Rendah",x,y,front_color,1,back_color); //
							// break;
					// case PORTUGAL:	//葡萄牙
						// Printf24("baixo",x,y,front_color,1,back_color); //
							// break;
					// case SPANISH: //西班牙
						// Printf24("bajo",x,y,front_color,1,back_color); //
							// break;
					}		
				}
			if(flag==1)	
				{
				switch(Language)
					{
					case CHN_HAN:
						Printf24("按插入键,切换光电有效电平!     ",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,BLACK_COLOR,0,0xffff);
						break;
					case ENGLISH:	
						Printf24("Press INSERT,change IR status!",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,BLACK_COLOR,0,0xffff);
						break;
					// case INDONSIA:	//印尼	
						// Printf16("Tekan tombol Insert,Switching Status IR",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,BLACK_COLOR,0,0xffff);
						// break;
					// case PORTUGAL:	//葡萄牙
						// Printf16("Pressione a tecla Insert para ligar o sinal IR",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,BLACK_COLOR,0,0xffff);
						// break;
					// case SPANISH: //西班牙
						// Printf16("Pulse la tecla Insert para cambiar IR",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,BLACK_COLOR,0,0xffff);
						// break;
					}
				}
				break;
	case 1://Jog-speed
		if(Unit==UNIT_MM)//mm  单位
			temp=JogLevel*100;
		else
			temp=JogLevel*1000;
		ProgSet_dis(temp,  x,  y,  flag);
		if(flag==1)
			{
			switch(Language)
				{
				case CHN_HAN:
					Printf24("输入数据范围        到",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,BLACK_COLOR,0,0xffff);
					break;
				case ENGLISH:	
					Printf24("Data range          to ",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,BLACK_COLOR,0,0xffff);
					break;
				}
			Printf24("1     5",REMIND_WINDOW_X+200,REMIND_WINDOW_Y+5,RED_COLOR,0,0xffff);//5 档
			}	
				break;
	case 2://前极限 有效设置
		GLCD_SetWindow_Fill( x, y, x+tx_wide, y+24, TEXT_TAB_BACK_COLOR, TEXT_TAB_BACK_COLOR);//clear text win
		if(Front_LimitValid_flag!=0)
			{
			switch(Language)
					{
					case CHN_HAN:
						Printf24("有效",x,y,front_color,1,back_color); //
							break;
					case ENGLISH:
						Printf24("Valid",x,y,front_color,1,back_color); //
							break;
					
					}		
			}
		else
			{
			switch(Language)
					{
					case CHN_HAN:
						Printf24("无效",x,y,front_color,1,back_color); //
							break;
					case ENGLISH:
						Printf24("Invalid",x,y,front_color,1,back_color); //
							break;
					
					}		
			}
		if(flag==1)	
				{
				switch(Language)
					{
					case CHN_HAN:
						Printf24("按插入键,切换前极限有效",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,BLACK_COLOR,0,0xffff);
						break;
					case ENGLISH:	
						Printf24("Press INSERT,change F-limit",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,BLACK_COLOR,0,0xffff);
						break;
					}
				}
				break;
	case 3://中极限 有效设置
		GLCD_SetWindow_Fill( x, y, x+tx_wide, y+24, TEXT_TAB_BACK_COLOR, TEXT_TAB_BACK_COLOR);//clear text win
		if(Middle_LimitValid_flag!=0)
			{
			switch(Language)
					{
					case CHN_HAN:
						Printf24("有效",x,y,front_color,1,back_color); //
							break;
					case ENGLISH:
						Printf24("Valid",x,y,front_color,1,back_color); //
							break;
					
					}		
			}
		else
			{
			switch(Language)
					{
					case CHN_HAN:
						Printf24("无效",x,y,front_color,1,back_color); //
							break;
					case ENGLISH:
						Printf24("Invalid",x,y,front_color,1,back_color); //
							break;
					
					}		
			}
		if(flag==1)	
				{
				switch(Language)
					{
					case CHN_HAN:
						Printf24("按插入键,切换中极限有效",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,BLACK_COLOR,0,0xffff);
						break;
					case ENGLISH:	
						Printf24("Press INSERT,change M-limit",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,BLACK_COLOR,0,0xffff);
						break;
					}
				}
				break;
	case 4://后极限 有效设置
		GLCD_SetWindow_Fill( x, y, x+tx_wide, y+24, TEXT_TAB_BACK_COLOR, TEXT_TAB_BACK_COLOR);//clear text win
		if(Back_LimitValid_flag!=0)
			{
			switch(Language)
					{
					case CHN_HAN:
						Printf24("有效",x,y,front_color,1,back_color); //
							break;
					case ENGLISH:
						Printf24("Valid",x,y,front_color,1,back_color); //
							break;
					
					}		
			}
		else
			{
			switch(Language)
					{
					case CHN_HAN:
						Printf24("无效",x,y,front_color,1,back_color); //
							break;
					case ENGLISH:
						Printf24("Invalid",x,y,front_color,1,back_color); //
							break;
					
					}		
			}
		if(flag==1)	
				{
				switch(Language)
					{
					case CHN_HAN:
						Printf24("按插入键,切换后极限有效",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,BLACK_COLOR,0,0xffff);
						break;
					case ENGLISH:	
						Printf24("Press INSERT,change B-limit",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,BLACK_COLOR,0,0xffff);
						break;
					}
				}
				break;
	}
}

void ToolsPage1_dis(void) //参数 画面1
{
volatile Int16U x,y,gap,n=0;
Int16U back_color=0xef9f;
 x=PARA_START_X1,y=PARA_START_Y,gap=30;

MiddlePage_dis(MIDDLE_PAGE_X,MIDDLE_PAGE_Y);//中间活页

	
Tools_dis(TOOLS_X, TOOLS_Y);//工具
Parameter_dis(PARAMETER_X,PARAMETER_Y);//参数
F2out_Up_dis(F2OUT_X,F2OUT_Y);//F2up退出
if(TOUCH_ENB==1)
{
L_R_Arrow_dis(L_R_ARROW_X, L_R_ARROW_Y);//左右箭头
UpArrow_Up_dis( SUB_UP_ARROW_X,  SUB_UP_ARROW_Y);//上箭头up
DownArrow_Up_dis( SUB_DOWN_ARROW_X,  SUB_DOWN_ARROW_Y);//下箭头up
}
switch(Language)
	{
	case CHN_HAN:
		Printf24("前极限:     ",x,y,BLACK_COLOR,1,back_color);y+=gap;
		Printf24("中极限:    ",x,y,BLACK_COLOR,1,back_color);y+=gap;
		Printf24("后极限:    ",x,y,BLACK_COLOR,1,back_color);y+=gap;
		Printf24("语言:    ",x,y,BLACK_COLOR,1,back_color);  y+=gap;
		Printf24("单位:",x,y,BLACK_COLOR,1,back_color);  y+=gap;
		Printf24("提前量:  ",x,y,BLACK_COLOR,1,back_color);y+=gap;
		//Printf24("标准距离:   ",x,y,BLACK_COLOR,1,back_color);
		Printf24("推纸距离:   ",x,y,BLACK_COLOR,1,back_color);
		x+=PARA_COL_WIDE;y=PARA_START_Y;
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
		else
			{
			Printf24("误差范围:   ",x,y,BLACK_COLOR,1,back_color);y+=gap;
			}
			break;
	case ENGLISH:	
		Printf24("Front-limit:",x,y,BLACK_COLOR,1,back_color);y+=gap;
		Printf24("Midd-limit:",x,y,BLACK_COLOR,1,back_color);y+=gap;
		Printf24("Back-limit:",x,y,BLACK_COLOR,1,back_color);y+=gap;
		Printf24("Language:",x,y,BLACK_COLOR,1,back_color);  y+=gap;
		Printf24("Unit:",x,y,BLACK_COLOR,1,back_color);  y+=gap;
		Printf24("Advanced:",x,y,BLACK_COLOR,1,back_color);y+=gap;
		Printf24("Push-distan:",x,y,BLACK_COLOR,1,back_color);
		x+=PARA_COL_WIDE;y=PARA_START_Y;
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
		else
			{
			Printf24("err range:  ",x,y,BLACK_COLOR,1,back_color);y+=gap;
			}
			break;
	}
switch(MotorType)
	{
	case MOTOR_FREQ_5_SPD_RST:
	case MOTOR_FREQ_3_SPD:
	case MOTOR_FREQ_3_SPD_RST:
			for(n=0;n<=8;n++)
				ParameterPage_dis(n, 0);
			break;
	case MOTOR_DC_SERVO:
	case MOTOR_DC670_SERVO:
	case MOTOR_DC670_SERVO_ZHU:
			for(n=0;n<=9;n++)
				ParameterPage_dis(n, 0);
			break;
	case MOTOR_AC_SERVO:	
			for(n=0;n<=8;n++)
				ParameterPage_dis(n, 0);
			break;
	}		 

ParameterPage_dis(Para_sel, 1);
}

void ToolsPage2_dis(void) //参数 画面2
{
volatile Int16U x,y,gap,n;
Int16U back_color=0xef9f;
 x=PARA_START_X1,y=PARA_START_Y,gap=30;

MiddlePage_dis(MIDDLE_PAGE_X,MIDDLE_PAGE_Y);//中间活页
// PushPaperTool_dis(PUSH_PAPER_TOOL_X,PUSH_PAPER_TOOL_Y);//推纸器
// FrontKnife_dis(FRONT_KNIFE_X,FRONT_KNIFE_Y);//刀前
// CurrentSize_dis(CurrentSize_temp); //当前尺寸 更新显示
// CurrUint_dis(Unit);  //当前尺寸 单位
// if(BeforeKnifeNo_flag==0)
	// FrontKnifeSize_dis(BeforeKnifeSize);
	
Tools_dis(TOOLS_X, TOOLS_Y);//工具
// Parameter_dis(PARAMETER_X,PARAMETER_Y);//参数
F2out_Up_dis(F2OUT_X,F2OUT_Y);//F2up退出
switch(Language)
	{
	case CHN_HAN:
		Printf24("光电选择:  ",x,y,BLACK_COLOR,1,back_color);y+=gap;
		Printf24("手动速度:  ",x,y,BLACK_COLOR,1,back_color);y+=gap;
		Printf24("外部前极限: ",x,y,BLACK_COLOR,1,back_color);y+=gap;
		Printf24("外部中极限: ",x,y,BLACK_COLOR,1,back_color);y+=gap;
		Printf24("外部后极限: ",x,y,BLACK_COLOR,1,back_color);y+=gap;
			break;
	case ENGLISH:
		Printf24("IR-set:   ",x,y,BLACK_COLOR,1,back_color);y+=gap;
		Printf24("JogLevel:  ",x,y,BLACK_COLOR,1,back_color);y+=gap;
		Printf24("Out-Flimit：",x,y,BLACK_COLOR,1,back_color);y+=gap;
		Printf24("Out-Mlimit：",x,y,BLACK_COLOR,1,back_color);y+=gap;
		Printf24("Out-Blimit：",x,y,BLACK_COLOR,1,back_color);y+=gap;
			break;
	}
Para2_sel=0;
for(n=0;n<=4;n++)
	ParameterPage2_dis(n, 0);
ParameterPage2_dis(Para2_sel, 1);
}

void ToolsPage_dis(void) //参数 画面--
{
CurrentArea_save2(MIDDLE_PAGE_X , MIDDLE_PAGE_Y,  M_PAGE_WIDE, M_PAGE_HIGH);
PushPaperTool_dis(PUSH_PAPER_TOOL_X,PUSH_PAPER_TOOL_Y);//推纸器
FrontKnife_dis(FRONT_KNIFE_X,FRONT_KNIFE_Y);//刀前
CurrentSize_dis(CurrentSize_temp); //当前尺寸 更新显示
CurrUint_dis(Unit);  //当前尺寸 单位
if(BeforeKnifeNo_flag==0)
	FrontKnifeSize_dis(BeforeKnifeSize);	
PramSel_Page=0;
Para_sel=0;
ToolsPage1_dis();
}

void RulerPage_dis(void) //基准 画面
{
CurrentArea_save2(MIDDLE_PAGE_X , MIDDLE_PAGE_Y,  M_PAGE_WIDE, M_PAGE_HIGH);
MiddlePage_dis(MIDDLE_PAGE_X,MIDDLE_PAGE_Y);//中间活页
PushPaperTool_dis(PUSH_PAPER_TOOL_X,PUSH_PAPER_TOOL_Y);//推纸器
FrontKnife_dis(FRONT_KNIFE_X,FRONT_KNIFE_Y);//刀前
CurrentSize_dis(CurrentSize_temp); //当前尺寸 更新显示
CurrUint_dis(Unit);  //当前尺寸 单位
if(BeforeKnifeNo_flag==0)
	FrontKnifeSize_dis(BeforeKnifeSize);
	
Ruler_dis(RULER_X,RULER_Y);//尺
F2out_Up_dis(F2OUT_X,F2OUT_Y);//F2up退出
RulerFun_dis(RULER_FUN_X, RULER_FUN_Y);//基准功能
}

void F3_plus_dis(Int8U flag)
{
if(flag==1)
	Printf24("++",SIZE_WINDOW_X,SIZE_WINDOW_Y,RED_COLOR,1,0xffff);
else
	Printf24("++",SIZE_WINDOW_X,SIZE_WINDOW_Y,0xffff,1,0xffff);
}
void F4_minus_dis(Int8U flag)
{
if(flag==1)
	Printf24("--",SIZE_WINDOW_X,SIZE_WINDOW_Y,RED_COLOR,1,0xffff);
else
	Printf24("--",SIZE_WINDOW_X,SIZE_WINDOW_Y,0xffff,1,0xffff);
}

//手动********************
void TimeSetSel_dis(Int8U sel, Int8U flag) //时间 设定 显示
{
volatile Int16U x,y,gap;
Int16U front_color,back_color;
gap=35;x=PARA_START_X2+20;
if(flag==1)
    {
	front_color=0xef9f;
	back_color=BLACK_COLOR;
	}
else
	{
	front_color=BLACK_COLOR;
	back_color=0xef9f;
	}
y=PARA_START_Y+20+gap*sel;
GLCD_SetWindow_Fill( REMIND_WINDOW_X, REMIND_WINDOW_Y, REMIND_WINDOW_X+REMIND_LENGTH, REMIND_WINDOW_Y+30, 0xfffff, 0xffff);//提示框

switch(sel)
	{
	case 0://年		
		ProgSet_dis(Year,  x,  y,  flag); //
		if(flag==1)
			{
			switch(Language)
				{
				case CHN_HAN:
					Printf24("输入数值范围        到",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,BLACK_COLOR,0,0xffff);
					break;
				case ENGLISH:	
					Printf24("Data range          to",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,BLACK_COLOR,0,0xffff);
					break;
				}
			Printf24("0      99",REMIND_WINDOW_X+200,REMIND_WINDOW_Y+5,RED_COLOR,0,0xffff);
			}
		break;
	case 1://月
		ProgSet_dis(Month,  x,  y,  flag); //
		if(flag==1)
			{
			switch(Language)
				{
				case CHN_HAN:
					Printf24("输入数值范围        到",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,BLACK_COLOR,0,0xffff);
					break;
				case ENGLISH:	
					Printf24("Data range          to",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,BLACK_COLOR,0,0xffff);
					break;
				}
			Printf24("1      12",REMIND_WINDOW_X+200,REMIND_WINDOW_Y+5,RED_COLOR,0,0xffff);
			}
		break;
	case 2://日
		ProgSet_dis(Dom,  x,  y,  flag); //
		if(flag==1)
			{
			switch(Language)
				{
				case CHN_HAN:
					Printf24("输入数值范围        到",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,BLACK_COLOR,0,0xffff);
					break;
				case ENGLISH:	
					Printf24("Data range          to",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,BLACK_COLOR,0,0xffff);
					break;
				}
			Printf24("1      31",REMIND_WINDOW_X+200,REMIND_WINDOW_Y+5,RED_COLOR,0,0xffff);
			}
		break;
	case 3://小时
		ProgSet_dis(Hour,  x,  y,  flag); //
		if(flag==1)
			{
			switch(Language)
				{
				case CHN_HAN:
					Printf24("输入数值范围        到",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,BLACK_COLOR,0,0xffff);
					break;
				case ENGLISH:	
					Printf24("Data range          to",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,BLACK_COLOR,0,0xffff);
					break;
				}
			Printf24("0      23",REMIND_WINDOW_X+200,REMIND_WINDOW_Y+5,RED_COLOR,0,0xffff);
			}
		break;
	case 4://分钟
		ProgSet_dis(Min,  x,  y,  flag); //
		if(flag==1)
			{
			switch(Language)
				{
				case CHN_HAN:
					Printf24("输入数值范围        到",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,BLACK_COLOR,0,0xffff);
					break;
				case ENGLISH:	
					Printf24("Data range          to",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,BLACK_COLOR,0,0xffff);
					break;
				}
			Printf24("0      59",REMIND_WINDOW_X+200,REMIND_WINDOW_Y+5,RED_COLOR,0,0xffff);
			}
		break;
	
	}
}

void ClockPage_dis(void)  //手动 时钟
{
volatile Int16U x,y,gap,n;
 x=130,y=170,gap=35;
CurrentArea_save2(MIDDLE_PAGE_X , MIDDLE_PAGE_Y,  M_PAGE_WIDE, M_PAGE_HIGH);
MiddlePage_dis(MIDDLE_PAGE_X,MIDDLE_PAGE_Y);//中间活页
PushPaperTool_dis(PUSH_PAPER_TOOL_X,PUSH_PAPER_TOOL_Y);//推纸器
FrontKnife_dis(FRONT_KNIFE_X,FRONT_KNIFE_Y);//刀前
CurrentSize_dis(CurrentSize_temp); //当前尺寸 更新显示
CurrUint_dis(Unit);  //当前尺寸 单位
if(BeforeKnifeNo_flag==0)
	FrontKnifeSize_dis(BeforeKnifeSize);

F2out_Up_dis(F2OUT_X,F2OUT_Y);//F2up退出
if(TOUCH_ENB==1)
{
UpArrow_Up_dis( SUB_UP_ARROW_X,  SUB_UP_ARROW_Y);//上箭头up
DownArrow_Up_dis( SUB_DOWN_ARROW_X,  SUB_DOWN_ARROW_Y);//下箭头up
}
Calendar_dis(CALENDA_X,CALENDA_Y); //日历
Watch_dis(WATCH_X,WATCH_Y);
switch(Language)
	{
	case CHN_HAN:
		Printf24("年:   20",x,y,BLACK_COLOR,0,0xffff);y+=gap;
		Printf24("月:",x,y,BLACK_COLOR,0,0xffff);y+=gap;
		Printf24("日:",x,y,BLACK_COLOR,0,0xffff);y+=gap;
		Printf24("小时:",x,y,BLACK_COLOR,0,0xffff);y+=gap;
		Printf24("分钟:",x,y,BLACK_COLOR,0,0xffff);
			break;
	case ENGLISH:	
		Printf24("Year:  20",x,y,BLACK_COLOR,0,0xffff);y+=gap;
		Printf24("Month:",x,y,BLACK_COLOR,0,0xffff);y+=gap;
		Printf24("Day:",x,y,BLACK_COLOR,0,0xffff);y+=gap;
		Printf24("Hour:",x,y,BLACK_COLOR,0,0xffff);y+=gap;
		Printf24("Min:",x,y,BLACK_COLOR,0,0xffff);
			break;
	}
for(n=1;n<5;n++)
	{
	TimeSetSel_dis(n, 0);
	}
TimeSetSel_dis(0, 1);	
}

void PulseDegreePage_dis(void)  //脉冲当量 设置页面
{
volatile Int16U x,y,n;
pInt8U pStr;
 x=PULSE_SET_X1,y=PULSE_SET_Y;
CurrentArea_save2(MIDDLE_PAGE_X , MIDDLE_PAGE_Y,  M_PAGE_WIDE, M_PAGE_HIGH);
MiddlePage_dis(MIDDLE_PAGE_X,MIDDLE_PAGE_Y);//中间活页
PushPaperTool_dis(PUSH_PAPER_TOOL_X,PUSH_PAPER_TOOL_Y);//推纸器
FrontKnife_dis(FRONT_KNIFE_X,FRONT_KNIFE_Y);//刀前
CurrentSize_dis(CurrentSize_temp); //当前尺寸 更新显示
CurrUint_dis(Unit);  //当前尺寸 单位
if(BeforeKnifeNo_flag==0)
	FrontKnifeSize_dis(BeforeKnifeSize);

F2out_Up_dis(F2OUT_X,F2OUT_Y);//F2up退出
Finish_dis(FINISHED_X,FINISHED_Y);//完成
UpArrow_Up_dis( SUB_UP_ARROW_X,  SUB_UP_ARROW_Y);//上箭头up
DownArrow_Up_dis( SUB_DOWN_ARROW_X,  SUB_DOWN_ARROW_Y);//下箭头up
PulseDegree_dis(PULSE_DEG_X,  PULSE_DEG_Y);//脉冲当量
//左边
switch(Language)
	{
	case CHN_HAN:
		Printf16("脉冲当量  编码器分辨率  丝杆螺距",x,y,0xFc00,0,0xffff);
			break;
	case ENGLISH:	
		Printf16("Pulse-Equ  Resolution   Distance",x,y,0xFc00,0,0xffff);
			break;
	}
x=PULSE_SET_X2;
switch(Language)
	{
	case CHN_HAN:
		Printf16("脉冲当量  编码器分辨率  丝杆螺距",x,y,0xFc00,0,0xffff);
			break;
	case ENGLISH:	
		Printf16("Pulse-Equ  Resolution   Distance",x,y,0xFc00,0,0xffff);
			break;
	}
x=PULSE_SET_X1+20;
y=PULSE_SET_Y;
for(n=0;n<12;n++)
	{
	if(n==6)
	   {
	   x=PULSE_SET_X2+20;
	   y=PULSE_SET_Y+30;
	   }
	else
	   {
	   y+=30;
	   }   
	Printf24((pInt8U)PulseDegree[n],x,y,0,0,0xffff);
	Printf24((pInt8U)PulseResolut[n],x+80,y,0,0,0xffff);
	Printf24((pInt8U)ScrowResolut[n],x+180,y,0,0,0xffff);
	}
SelPulseDegree_dis(Pulse_degree, 1); //脉冲设定
GLCD_SetWindow_Fill( REMIND_WINDOW_X, REMIND_WINDOW_Y, REMIND_WINDOW_X+REMIND_LENGTH, REMIND_WINDOW_Y+30, 0xfffff, 0xffff);//提示框
switch(Language)
	{
	case CHN_HAN:
		Printf24("请输入脉冲当量!",REMIND_WINDOW_X,REMIND_WINDOW_Y+5,BLACK_COLOR,0,0xffff);	
			break;
	case ENGLISH:	
		Printf24("Enter pulse equivalent!",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,BLACK_COLOR,0,0xffff);
			break;
	}
}

void SelPulseDegree_dis(Int8U sel,Int8U flag)
{
volatile Int16U x,y,HH,WW;
Int16U front_color;
HH=26,WW=220;x=PULSE_SET_X1+10;
if(flag==1)
    {
	front_color=RED_COLOR;
	}
else
	{
	front_color=0xef9f;
	}
if(sel>5)
	{
	x=PULSE_SET_X2+10;
	}
sel%=6;
y=PULSE_SET_Y+30*(sel+1);
GLCD_SetWindow( x, y, x+WW, y+HH, front_color);
}

//------------自刀
void SelfEnterPage_dis(void)//自刀模式 进入 提示
{
Int16U x,y;
Int16U front_color,back_color;
x=SELF_PROMP_X,y=SELF_PROMP_Y;
front_color=RED_COLOR,back_color=0xffff;
CurrentArea_save2(x , y,  x+300, y+120);
GLCD_SetWindow_Fill( x, y, x+300, y+120, BLUE_COLOR, 0xfffff);x+=20,y+=5;
GLCD_SetWindow(SELF_OK_X,SELF_OK_Y,SELF_OK_X+SELF_OK_WIDE, SELF_OK_Y+SELF_OK_HIGH, 0x0);//确定 按钮
GLCD_SetWindow(SELF_CANCEL_X,SELF_CANCEL_Y,SELF_CANCEL_X+SELF_OK_WIDE, SELF_CANCEL_Y+SELF_OK_HIGH, 0x0);//取消 按钮
switch(Language)
	{
	case CHN_HAN:
		Printf24("自刀模式高度危险，请",x,y,front_color,1,back_color);y+=30;
		Printf24("按“确定”键进入！",x,y,front_color,1,back_color);x+=40,y+=50;
		Printf24("确认",x,y,front_color,1,back_color);x+=120;
		Printf24("取消",x,y,front_color,1,back_color);
			break;
	case ENGLISH:	
		Printf24("Auto-Cut mode is so",x,y,front_color,1,back_color);y+=30;
		Printf24("dangerous, press ENTER!",x,y,front_color,1,back_color);x+=40,y+=50;
		Printf24("OK",x,y,front_color,1,back_color);x+=120;
		Printf24("Cancel",x,y,front_color,1,back_color);
			break;
	}

}

void AutoCutLastKnifeLoad_dis(void)  //自刀模式 再次进入 恢复之前 刀序
{
Int16U x,y;
Int16U front_color,back_color;
x=SELF_PROMP_X,y=SELF_PROMP_Y;
front_color=RED_COLOR,back_color=0xffff;
//CurrentArea_save2(x , y,  x+300, y+120);
GLCD_SetWindow_Fill( x, y, x+300, y+120, BLUE_COLOR, 0xfffff);x+=20,y+=5;
GLCD_SetWindow(SELF_OK_X,SELF_OK_Y,SELF_OK_X+SELF_OK_WIDE, SELF_OK_Y+SELF_OK_HIGH, 0x0);//确定 按钮
GLCD_SetWindow(SELF_CANCEL_X,SELF_CANCEL_Y,SELF_CANCEL_X+SELF_OK_WIDE, SELF_CANCEL_Y+SELF_OK_HIGH, 0x0);//取消 按钮
switch(Language)
	{
	case CHN_HAN:
		Printf24("是否继续执行之前的",x,y,front_color,1,back_color);y+=30;
		Printf24("自刀步骤？",x,y,front_color,1,back_color);x+=40,y+=50;
		Printf24("确认",x,y,front_color,1,back_color);x+=120;
		Printf24("取消",x,y,front_color,1,back_color);
			break;
	case ENGLISH:	
		Printf24("Do you continue to last",x,y,front_color,1,back_color);y+=30;
		Printf24("Auto-Cut step?",x,y,front_color,1,back_color);x+=40,y+=50;
		Printf24("OK",x,y,front_color,1,back_color);x+=120;
		Printf24("Cancel",x,y,front_color,1,back_color);
			break;
	}

}

//---------伺服 参数设置  --
void ServoParameter_dis(Int8U sel, Int8U flag) //参数 设置显示
{
volatile Int16U x,y,gap;
Int16U front_color,back_color;
gap=30;x=PARA_START_X2+(sel/7)*PARA_COL_WIDE;
Int32U temp;
if(flag==1)
    {
	front_color=0xef9f;
	back_color=BLACK_COLOR;
	}
else
	{
	front_color=BLACK_COLOR;
	back_color=0xef9f;
	}
y=PARA_START_Y+gap*(sel%7);
GLCD_SetWindow_Fill( REMIND_WINDOW_X, REMIND_WINDOW_Y, REMIND_WINDOW_X+REMIND_LENGTH, REMIND_WINDOW_Y+30, 0xfffff, 0xffff);//提示框

switch(sel)
	{
	case 0:  //位置环增益
		ProgSet_dis(PositRing_Gain,  x,  y,  flag);
		if(flag==1)
			{
			switch(Language)
				{
				case CHN_HAN:
					Printf24("输入数据范围       到",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,BLACK_COLOR,0,0xffff);
					break;
				case ENGLISH:	
					Printf24("Data range         to ",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,BLACK_COLOR,0,0xffff);
					break;
				}
			Printf24("1     99",REMIND_WINDOW_X+200,REMIND_WINDOW_Y+5,RED_COLOR,0,0xffff);
			}	
		break;
	case 1://位置环微分
		ProgSet_dis(PositRing_Diff,  x,  y,  flag);
		if(flag==1)
			{
			switch(Language)
				{
				case CHN_HAN:
					Printf24("输入数据范围       到",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,BLACK_COLOR,0,0xffff);
					break;
				case ENGLISH:	
					Printf24("Data range         to ",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,BLACK_COLOR,0,0xffff);
					break;
				}
			Printf24("1     99",REMIND_WINDOW_X+200,REMIND_WINDOW_Y+5,RED_COLOR,0,0xffff);
			}	
		break;
	case 2://位置环积分
		ProgSet_dis(PositRing_Integral,  x,  y,  flag);
		if(flag==1)
			{
			switch(Language)
				{
				case CHN_HAN:
					Printf24("输入数据范围       到",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,BLACK_COLOR,0,0xffff);
					break;
				case ENGLISH:	
					Printf24("Data range         to ",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,BLACK_COLOR,0,0xffff);
					break;
				}
			Printf24("1     99",REMIND_WINDOW_X+200,REMIND_WINDOW_Y+5,RED_COLOR,0,0xffff);
			}	
		break;	
	case 3:  //速度环增益
		ProgSet_dis(SpeedRing_Gain,  x,  y,  flag);
		if(flag==1)
			{
			switch(Language)
				{
				case CHN_HAN:
					Printf24("输入数据范围       到",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,BLACK_COLOR,0,0xffff);
					break;
				case ENGLISH:	
					Printf24("Data range         to ",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,BLACK_COLOR,0,0xffff);
					break;
				}
			Printf24("1     99",REMIND_WINDOW_X+200,REMIND_WINDOW_Y+5,RED_COLOR,0,0xffff);
			}	
		break;
	case 4://速度环微分
		ProgSet_dis(SpeedRing_Diff,  x,  y,  flag);
		if(flag==1)
			{
			switch(Language)
				{
				case CHN_HAN:
					Printf24("输入数据范围       到",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,BLACK_COLOR,0,0xffff);
					break;
				case ENGLISH:	
					Printf24("Data range         to ",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,BLACK_COLOR,0,0xffff);
					break;
				}
			Printf24("1     99",REMIND_WINDOW_X+200,REMIND_WINDOW_Y+5,RED_COLOR,0,0xffff);
			}	
		break;
	case 5://速度环积分
		ProgSet_dis(SpeedRing_Integral,  x,  y,  flag);
		if(flag==1)
			{
			switch(Language)
				{
				case CHN_HAN:
					Printf24("输入数据范围       到",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,BLACK_COLOR,0,0xffff);
					break;
				case ENGLISH:	
					Printf24("Data range         to ",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,BLACK_COLOR,0,0xffff);
					break;
				}
			Printf24("1     99",REMIND_WINDOW_X+200,REMIND_WINDOW_Y+5,RED_COLOR,0,0xffff);
			}	
		break;	
	case 6://减速比
		ProgSet_dis(SpeedDown_Ratio,  x,  y,  flag);
		if(flag==1)
			{
			switch(Language)
				{
				case CHN_HAN:
					Printf24("输入数据范围       到",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,BLACK_COLOR,0,0xffff);
					break;
				case ENGLISH:	
					Printf24("Data range         to ",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,BLACK_COLOR,0,0xffff);
					break;
				}
			Printf24("1     3",REMIND_WINDOW_X+200,REMIND_WINDOW_Y+5,RED_COLOR,0,0xffff);
			}	
		break;		
	case 7://螺距
		ProgSet_dis(Screw_Pitch,  x,  y,  flag);
		if(flag==1)
			{
			switch(Language)
				{
				case CHN_HAN:
					Printf24("输入数据选择(           )",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,BLACK_COLOR,0,0xffff);
					break;
				case ENGLISH:	
					Printf24("Data select(            )",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,BLACK_COLOR,0,0xffff);
					break;
				}
			Printf24("10  ,  12",REMIND_WINDOW_X+180,REMIND_WINDOW_Y+5,RED_COLOR,0,0xffff);
			}	
		break;		
	}
}	
void Servo_C_DataPage(void)   //直流伺服 ‘C’参数
{
volatile Int16U x,y,gap,n;
Int16U back_color=0xef9f;;
 x=PARA_START_X1,y=PARA_START_Y,gap=30;
CurrentArea_save2(MIDDLE_PAGE_X , MIDDLE_PAGE_Y,  M_PAGE_WIDE, M_PAGE_HIGH);
MiddlePage_dis(MIDDLE_PAGE_X,MIDDLE_PAGE_Y);//中间活页
PushPaperTool_dis(PUSH_PAPER_TOOL_X,PUSH_PAPER_TOOL_Y);//推纸器
FrontKnife_dis(FRONT_KNIFE_X,FRONT_KNIFE_Y);//刀前
CurrentSize_dis(CurrentSize_temp); //当前尺寸 更新显示
CurrUint_dis(Unit);  //当前尺寸 单位
if(BeforeKnifeNo_flag==0)
	FrontKnifeSize_dis(BeforeKnifeSize);
	
Tools_dis(TOOLS_X, TOOLS_Y);//工具
Parameter_dis(PARAMETER_X,PARAMETER_Y);//参数
F2out_Up_dis(F2OUT_X,F2OUT_Y);//F2up退出
//L_R_Arrow_dis(L_R_ARROW_X, L_R_ARROW_Y);//左右箭头
UpArrow_Up_dis( SUB_UP_ARROW_X,  SUB_UP_ARROW_Y);//上箭头up
DownArrow_Up_dis( SUB_DOWN_ARROW_X,  SUB_DOWN_ARROW_Y);//下箭头up
switch(Language)
	{
	case CHN_HAN:
		Printf24("位置增益:   ",x,y,BLACK_COLOR,1,back_color);y+=gap;
		Printf24("位置微分:   ",x,y,BLACK_COLOR,1,back_color);y+=gap;
		Printf24("位置积分:   ",x,y,BLACK_COLOR,1,back_color);y+=gap;
		Printf24("速度增益:   ",x,y,BLACK_COLOR,1,back_color);y+=gap;
		Printf24("速度微分:   ",x,y,BLACK_COLOR,1,back_color);y+=gap;
		Printf24("速度积分:   ",x,y,BLACK_COLOR,1,back_color);y+=gap;
		
		Printf24("减速比:      ",x,y,BLACK_COLOR,1,back_color);
		x+=PARA_COL_WIDE;y=PARA_START_Y;
		Printf24("螺距 :      ",x,y,BLACK_COLOR,1,back_color);
			break;
	case ENGLISH:	
		Printf24("Posit-gain:",x,y,BLACK_COLOR,1,back_color);y+=gap;
		Printf24("Posit-diff:",x,y,BLACK_COLOR,1,back_color);y+=gap;
		Printf24("Posit-inte:",x,y,BLACK_COLOR,1,back_color);y+=gap;
		Printf24("Speed-gain:",x,y,BLACK_COLOR,1,back_color);y+=gap;
		Printf24("Posit-diff:",x,y,BLACK_COLOR,1,back_color);y+=gap;
		Printf24("Posit-inte:",x,y,BLACK_COLOR,1,back_color);y+=gap;
		
		Printf24("Reduc-ratio:",x,y,BLACK_COLOR,1,back_color);
		x+=PARA_COL_WIDE;y=PARA_START_Y;
		Printf24("Screw_Pitch:",x,y,BLACK_COLOR,1,back_color);
			break;
	}
	 
for(n=1;n<8;n++)
	ServoParameter_dis(n, 0);
ServoParameter_dis(0, 1);
}

void PassCodePage_dis(void)  //密码模式 启动界面
{
CurrentArea_save2(MIDDLE_PAGE_X , MIDDLE_PAGE_Y,  M_PAGE_WIDE, M_PAGE_HIGH);
MiddlePage_dis(MIDDLE_PAGE_X,MIDDLE_PAGE_Y);//中间活页
PushPaperTool_dis(PUSH_PAPER_TOOL_X,PUSH_PAPER_TOOL_Y);//推纸器
FrontKnife_dis(FRONT_KNIFE_X,FRONT_KNIFE_Y);//刀前
CurrentSize_dis(CurrentSize_temp); //当前尺寸 更新显示
CurrUint_dis(Unit);  //当前尺寸 单位
if(BeforeKnifeNo_flag==0)
	FrontKnifeSize_dis(BeforeKnifeSize);

F2out_Up_dis(F2OUT_X,F2OUT_Y);//F2up退出
L_R_Arrow_dis(L_R_ARROW_X, L_R_ARROW_Y);//左右箭头
UpArrow_Up_dis( SUB_UP_ARROW_X,  SUB_UP_ARROW_Y);//上箭头up
DownArrow_Up_dis( SUB_DOWN_ARROW_X,  SUB_DOWN_ARROW_Y);//下箭头up
Lock_dis(LOCK_X, LOCK_Y); //锁
GLCD_SetWindow_Fill( REMIND_WINDOW_X, REMIND_WINDOW_Y, REMIND_WINDOW_X+REMIND_LENGTH, REMIND_WINDOW_Y+30, 0xfffff, 0xffff);//提示框
switch(Language)
	{
	case CHN_HAN:
		Printf24("请输入密码!",REMIND_WINDOW_X,REMIND_WINDOW_Y+5,RED_COLOR,0,0xffff);
			break;
	case ENGLISH:	
		Printf24("Enter passcode!",REMIND_WINDOW_X,REMIND_WINDOW_Y+5,RED_COLOR,0,0xffff);
			break;
	}
	
//Printf24(")",REMIND_WINDOW_X+240,REMIND_WINDOW_Y+5,RED_COLOR,0,0xffff);	
}
void PassSet_dis(void) //密码 设置界面
{
Int16U x,y,gap;
x=80,y=200,gap=80;
LockKey_dis(LOCK_KEY_X, LOCK_KEY_Y); //锁 钥匙
switch(Language)
	{
	case CHN_HAN:
		Printf24("第一次关机天数:",x,y,BLACK_COLOR,0,0xffff);y+=gap;
			break;
	case ENGLISH:	
		Printf24("First valid days:",x,y,BLACK_COLOR,0,0xffff);y+=gap;
			break;
	}
switch(Language)
	{
	case CHN_HAN:
		Printf24("第二次关机天数:",x,y,BLACK_COLOR,0,0xffff);y+=gap;
			break;
	case ENGLISH:	
		Printf24("Second valid days:",x,y,BLACK_COLOR,0,0xffff);y+=gap;
			break;
	}
PassDaysSet_dis( 1, 0);
PassDaysSet_dis( 0, 1);
}

void PassDaysSet_dis(Int8U sel,Int8U flag)//天数设定
{
volatile Int16U x,y,gap;
Int16U front_color,back_color;
gap=80;x=150;
if(flag==1)
    {
	front_color=0xef9f;
	back_color=BLACK_COLOR;
	}
else
	{
	front_color=BLACK_COLOR;
	back_color=0xef9f;
	}
y=230+gap*sel;
GLCD_SetWindow_Fill( REMIND_WINDOW_X, REMIND_WINDOW_Y, REMIND_WINDOW_X+REMIND_LENGTH, REMIND_WINDOW_Y+30, 0xfffff, 0xffff);//提示框

switch(sel)
	{
	case 0://第一次 天数		
		ProgSet_dis(FirstDays,  x,  y,  flag); //
		if(flag==1)
			{
			switch(Language)
				{
				case CHN_HAN:
					Printf24("输入天数,按插入键生效!",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,BLACK_COLOR,0,0xffff);
						break;
				case ENGLISH:	
					Printf24("Enter days,press INSERT",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,BLACK_COLOR,0,0xffff);
						break;
				}
			}
		x+=36;
		if(FirstDayValid_flag==1)
			{
			switch(Language)
				{
				case CHN_HAN:
					Printf24("(有效)",x,y,front_color,1,back_color); 
						break;
				case ENGLISH:	
					Printf24("(Valid)  ",x,y,front_color,1,back_color); 
						break;
				}
			}
		else
			{
			switch(Language)
				{
				case CHN_HAN:
					Printf24("(无效)",x,y,front_color,1,back_color); 
						break;
				case ENGLISH:	
					Printf24("(Invalid)",x,y,front_color,1,back_color); 
						break;
				}
			}
		break;
	case 1://第二次 天数
		ProgSet_dis(SecondDays,  x,  y,  flag); //
		if(flag==1)
			{
			switch(Language)
				{
				case CHN_HAN:
					Printf24("输入天数,按插入键生效!",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,BLACK_COLOR,0,0xffff);
						break;
				case ENGLISH:	
					Printf24("Enter days,press INSERT",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,BLACK_COLOR,0,0xffff);
						break;
				}
			}
		x+=36;
		if(SecondDayValid_flag==1)
			{
			switch(Language)
				{
				case CHN_HAN:
					Printf24("(有效)",x,y,front_color,1,back_color); 
						break;
				case ENGLISH:	
					Printf24("(Valid)  ",x,y,front_color,1,back_color); 
						break;
				}
			}
		else
			{
			switch(Language)
				{
				case CHN_HAN:
					Printf24("(无效)",x,y,front_color,1,back_color); 
						break;
				case ENGLISH:	
					Printf24("(Invalid)",x,y,front_color,1,back_color); 
						break;
				}
			}
		break;
	}
}

void  PassWord_dis(pInt8U nums,Int8U cou) //密码输入显示
{
Int8U num_temp[8],n=0;

for(n=0;n<cou;n++)
   {
   num_temp[n]=nums[n];
   if(num_temp[n]!='.')
     {
	 num_temp[n]+=48;
	 }
   }
num_temp[cou]=0;
//GLCD_SetWindow_Fill( SIZE_WINDOW_X, SIZE_WINDOW_Y, SIZE_WINDOW_X+120, SIZE_WINDOW_Y+30, 0xfffff, 0xffff);//尺寸输入
Printf24(num_temp,PASSCODE_INPUT_X+10,PASSCODE_INPUT_Y+5,BLACK_COLOR,1,0xffff);
}


//*************************图片拼接 显示
void WorkPic_dis(void)  //工作画面显示
{
volatile Int16U xp,yp,back_color;
back_color=0xce79;
FirstBack_dis();//底层背景

TimeCol_dis(TIME_COL_X,TIME_COL_Y);//时间条

Schedule_dis(SCHEDULE_X,SCHEDULE_Y);//进度
//SchedulePot_dis(SCHEDULE_DOT_X,SCHEDULE_DOT_Y);//进度块
ProgressBar_dis(Knife_sum,Knife_order);  //进度条 显示
xp=PROG_X,yp=PROG_Y;
switch(Language)
	{
	case CHN_HAN:
		Printf24(" 程序  ",xp,yp,BLACK_COLOR,1,back_color);
			break;
	case ENGLISH:	
		Printf24("Process",xp,yp,BLACK_COLOR,1,back_color);
			break;
	}
xp=STEP_X;//
switch(Language)
	{
	case CHN_HAN:
		Printf24("步骤",xp,yp,BLACK_COLOR,1,back_color);//
			break;
	case ENGLISH:	
		Printf24("Step",xp,yp,BLACK_COLOR,1,back_color);
			break;
	}
ProNum_dis(Pro_data.pro_num);// 程序号
StepNum_dis(Knife_sum,Knife_order);// 步骤号  总刀数-序号

Order_dis(ORDER_X,ORDER_Y);//序号
Position_dis(POSITION_X,POSITION_Y);//位置
PushKnife_dis(PUSH_KNIFE_X,PUSH_KNIFE_Y);//推纸——刀

PushPaperTool_dis(PUSH_PAPER_TOOL_X,PUSH_PAPER_TOOL_Y);//推纸器
CurrentSize_dis(CurrentSize); //当前尺寸 更新显示
CurrUint_dis(Unit);  //当前尺寸 单位

FrontKnife_dis(FRONT_KNIFE_X,FRONT_KNIFE_Y);//刀前
/*
RightArrow_dis(RIGHT_ARROW_X,RIGHT_ARROW_Y);//右箭头

RedKnifeF_dis(RED_KNIFE_X,RED_KNIFE_Y); yp=RED_KNIFE_Y+30; //红刀

*/
Knife_Up_dis(KNIFE_X,KNIFE_Y);//刀上
Press_Up_dis(PRESS_X,PRESS_Y);//压上

Red_A_dis(RED_A_X,RED_A_Y);//红A
Red_B_dis(RED_B_X,RED_B_Y);//红B
Hand_IR_dis(HAND_IR_X,HAND_IR_Y);//手红外
//RedLine_dis(RED_LINE_X,RED_LINE_Y);//红线
// ElectricalWheel_dis();  //电子手轮  开关状态
if(TOUCH_ENB==1)
{
FrontPage_Up_dis( FRONT_PAGE_X,  FRONT_PAGE_Y);//前一页up
BackPage_Up_dis( BACK_PAGE_X,  BACK_PAGE_Y);//后一页up
UpArrow_Up_dis( UP_ARROW_X,  UP_ARROW_Y);//上箭头up
DownArrow_Up_dis( DOWN_ARROW_X,  DOWN_ARROW_Y);//下箭头up
}

F1up_dis(F1_X,F1_Y);//F1
F2up_dis(F2_X,F2_Y);
F3up_dis(F3_X,F3_Y);
F4up_dis(F4_X,F4_Y);

InputSize_dis(INPUT_SIZE_X,INPUT_SIZE_Y);//输入尺寸
Remind_dis(REMIND_X,REMIND_Y); //提示栏
TextWindow_dis();   //白色文本框
//MiddlePage_dis(MIDDLE_PAGE_X,MIDDLE_PAGE_Y);//中间活页
//LeftPage_dis(LEFT_PAGE_X,LEFT_PAGE_Y);//左边活页

//Cancel_Up_dis(CANCEL_X,CANCEL_Y);//取消up
//Enter_Up_dis(ENTER_X,ENTER_Y);//确定up
//Run_Up_dis(RUN_X,RUN_Y);//运行up
//Stop_Up_dis(STOP_X,STOP_Y);//停止up
if(TOUCH_ENB==1)
{
//////Delete_Up_dis( DELETE_X, DELETE_Y );//删除up
//////DeleteAll_Up_dis( DELETE_ALL_X, DELETE_ALL_Y);//全删up
Fkey_Up_dis( F_KEY_X, F_KEY_Y);//F键up
}

Program_dis(PROGRAM_X,PROGRAM_Y);   //编程
}

void PromptNum_dis(void)  //输入数据范围 提示
{
Int8U num[15],str1[8],str2[8],i,j;
Int16U x,y;
i=0;
Int32U max,min;
if(Run_flag==1)
	{
	if((WorkMode==AUTO_MODE)||(WorkMode==SELF_CUT_MODE)||(WorkMode==TEACH_MODE))  //自动 自刀 模式
		{
		GLCD_SetWindow_Fill( REMIND_WINDOW_X, REMIND_WINDOW_Y, REMIND_WINDOW_X+REMIND_LENGTH, REMIND_WINDOW_Y+30, 0xfffff, 0xffff);//提示框
		switch(Language)
			{
			case CHN_HAN:
				Printf24("按键盘F键停止！",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,BLACK_COLOR,0,0xffff);
					break;
			case ENGLISH:	
				Printf24("Press 'F' key can stop!",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,BLACK_COLOR,0,0xffff);
					break;
			}
		}
	}
else
	{
	if(Unit==UNIT_MM)
		{
		num[i++]=Size_MIN/100000;
		num[i++]=(Size_MIN/10000)%10;
		num[i++]=(Size_MIN/1000)%10;
		num[i++]=(Size_MIN/100)%10;

		num[i++]=Size_MAX/100000;
		num[i++]=(Size_MAX/10000)%10;
		num[i++]=(Size_MAX/1000)%10;
		num[i++]=(Size_MAX/100)%10;

		i=0;j=0;
		while(num[i]==0) 
			{
			i++;
			}
		while(i<4)
			{
			str1[j++]=num[i++]+48;
			}
		str1[j]=0;	
		i=4;j=0;	
		while(num[i]==0) 
			{
			i++;
			}
		while(i<8)
			{
			str2[j++]=num[i++]+48;
			}
		str2[j]=0;
		}
	else
		{
		min=Size_MIN*100/254;
		max=Size_MAX*100/254;
		num[i++]=min/100000;
		num[i++]=(min/10000)%10;
		num[i++]=(min/1000)%10;
		num[i++]='.';
		num[i++]=(min/100)%10;
		num[i++]=(min/10)%10;
		num[i++]=min%10;
		
		num[i++]=max/100000;
		num[i++]=(max/10000)%10;
		num[i++]=(max/1000)%10;
		num[i++]='.';
		num[i++]=(max/100)%10;
		num[i++]=(max/10)%10;
		num[i++]=max%10;
		i=0;j=0;
		while(num[i]==0) 
			{
			i++;
			}
		if(i>2)i=2;	
		while(i<7)
			{
			if(i!=3)
				str1[j++]=num[i++]+48;
			else
				str1[j++]=num[i++];
			}
		str1[j]=0;	
		i=7;j=0;	
		while(num[i]==0) 
			{
			i++;
			}
		if(i>9)i=9;		
		while(i<14)
			{
			if(i!=10)
				str2[j++]=num[i++]+48;
			else
				str2[j++]=num[i++];
			}
		str2[j]=0;
		}

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

	x=REMIND_WINDOW_X+180,y=REMIND_WINDOW_Y+5;
	Printf24(str1,x,y,RED_COLOR,0,0xffff);
	Printf24(str2,x+100,y,RED_COLOR,0,0xffff);
	}

}


void TextWindow_dis(void)  //文本输入框
{
GLCD_SetWindow_Fill( SIZE_WINDOW_X, SIZE_WINDOW_Y, SIZE_WINDOW_X+120, SIZE_WINDOW_Y+30, 0xfffff, 0xffff);//尺寸输入
PromptNum_dis();
}



void Comment_dis_page(Int8U page)//注释
{
GLCD_Buffer_Fill(0xffff);
volatile Int16U x,y,gap=10,gap1,gap2;
Int8U start_x=0,start_y=0;
switch(page)
	{
	case 0:
		x=start_x+gap,y=start_y+gap;
		gap1=50,gap2=110;
		F1up_dis(x,y);//F1
		x+=gap1;
		Printf24("标签",x,y+20,BLACK_COLOR,0,0xffff);

		x+=gap2;
		F2up_dis(x,y);
		x+=gap1;
		Printf24("等分",x,y+20,BLACK_COLOR,0,0xffff);

		x+=gap2;
		F3up_dis(x,y);
		x+=gap1;
		Printf24("程序",x,y+20,BLACK_COLOR,0,0xffff);

		x+=gap2;
		F4up_dis(x,y);
		x+=gap1;
		Printf24("推纸功能",x,y+20,BLACK_COLOR,0,0xffff);

		x+=gap2;
		Finish_dis(x,y);
		x+=gap1;
		Printf24("完成",x,y+20,BLACK_COLOR,0,0xffff);
		
		//*********************第二行
		x=start_x+gap;y+=70;
		gap1=50,gap2=110;
		F1Ruler_Up_dis(x,y);
		x+=gap1;
		Printf24("基准",x,y+20,BLACK_COLOR,0,0xffff);
		
		x+=gap2;
		F2Tools_Up_dis(x,y);
		x+=gap1;
		Printf24("参数",x,y+20,BLACK_COLOR,0,0xffff);
		
		x+=gap2;
		F3clock_Up_dis(x,y);
		x+=gap1;
		Printf24("时间",x,y+20,BLACK_COLOR,0,0xffff);
		
		x+=gap2;
		F3plus_Up_dis(x,y);
		x+=gap1;
		Printf24("自加",x,y+20,BLACK_COLOR,0,0xffff);
		
		x+=gap2;
		F4minus_Up_dis(x,y);
		x+=gap1;
		Printf24("自减",x,y+20,BLACK_COLOR,0,0xffff);
		
		//*********************第三行
		x=start_x+gap;y+=70;
		gap1=50,gap2=110;
		F2out_Up_dis(x,y);
		x+=gap1;
		Printf24("退出",x,y+20,BLACK_COLOR,0,0xffff);
		
		x+=gap2;
		UpArrow_Up_dis(x,y);
		x+=gap1;
		Printf24("向上",x,y+20,BLACK_COLOR,0,0xffff);
		
		x+=gap2;
		DownArrow_Up_dis(x,y);
		x+=gap1;
		Printf24("向下",x,y+20,BLACK_COLOR,0,0xffff);
		
		x+=gap2;
		BackPage_Up_dis(x,y);
		x+=gap1;
		Printf24("前进",x,y+20,BLACK_COLOR,0,0xffff);
		
		x+=gap2;
		FrontPage_Up_dis(x,y);
		x+=gap1;
		Printf24("后退",x,y+20,BLACK_COLOR,0,0xffff);
		
		//*********************第四行
		x=start_x+gap;y+=70;
		gap1=50,gap2=110;
		L_R_Arrow_dis(x,y);
		x+=gap1;
		Printf24("换档",x,y+20,BLACK_COLOR,0,0xffff);
		
		x+=gap2;
		Fkey_Up_dis(x,y);
		x+=gap1;
		Printf24("F键",x+20,y+20,BLACK_COLOR,0,0xffff);
		
		x+=gap2;
		Hand_IR_dis(x,y);
		x+=gap1;
		Printf24("红外",x,y+20,BLACK_COLOR,0,0xffff);
		
		x+=gap2;
		FrontKnife_dis(x,y);
		x+=gap1;
		Printf24("刀前",x,y+20,BLACK_COLOR,0,0xffff);
		
		x+=gap2;
		RedKnifeF_dis(x,y);
		x+=gap1;
		Printf24("刀标志",x,y+20,BLACK_COLOR,0,0xffff);
		
		//*********************第五行
		x=start_x+gap;y+=70;
		gap1=50,gap2=110;
		Red_A_dis(x,y);
		x+=gap1;
		Printf24("A信号",x,y+20,BLACK_COLOR,0,0xffff);
		
		x+=gap2;
		Red_B_dis(x,y);
		x+=gap1;
		Printf24("B信号",x,y+20,BLACK_COLOR,0,0xffff);
		
		x+=gap2;
		PushPaperF_dis(x,y);
		x+=gap1-10;
		Printf24("推纸标志",x,y+20,BLACK_COLOR,0,0xffff);
		
		gap1=90,gap2=130;
		x+=gap2;
		Delete_Up_dis(x,y);
		x+=gap1;
		Printf24("删除",x,y+5,BLACK_COLOR,0,0xffff);
		
		gap1=50,gap2=90;
		x+=gap2;
		F4Wheel0_dis(x,y);
		x+=gap1;
		Printf24("手轮关",x,y+5,BLACK_COLOR,0,0xffff);
		
		//*********************第六行
		x=start_x+gap;y+=70;
		gap1=90,gap2=80;
		DeleteAll_Up_dis(x,y);
		x+=gap1;
		Printf24("全删",x,y+5,BLACK_COLOR,0,0xffff);
		
		x+=gap2;
		Run_Up_dis(x,y);
		x+=gap1;
		Printf24("运行",x,y+5,BLACK_COLOR,0,0xffff);

		x+=gap2;
		Stop_Up_dis(x,y);
		x+=gap1;
		Printf24("停止",x,y+5,BLACK_COLOR,0,0xffff);
		
		gap1=140;
		x+=gap2;
		PulseDegree_dis(x,y);
		x+=gap1;
		Printf24("脉冲当量",x,y+5,BLACK_COLOR,0,0xffff);
		
		//*********************第七行
		x=start_x+gap;y+=50;
		gap1=90,gap2=80;
		Wheel0_dis(x,y);
		x+=gap1;
		Printf24("手轮关",x,y+5,BLACK_COLOR,0,0xffff);
		/*
		Printf24("编程",x,y+35,BLACK_COLOR,0,0xffff);

		x+=gap2;
		Label_dis(x,y);
		x+=gap1;
		Printf24("标签",x,y+35,BLACK_COLOR,0,0xffff);

		x+=gap2;// *********************第六行
		x=start_x+gap;y+=80;
		Parameter_dis(x,y);
		x+=gap1;
		Printf24("参数",x,y+35,BLACK_COLOR,0,0xffff);

		// *********************第四行
		x=start_x+gap;y+=80;
		Divide_dis(x,y);
		x+=gap1;
		Printf24("等分",x,y+35,BLACK_COLOR,0,0xffff);

		x+=gap2;
		Teach_dis(x,y);
		x+=gap1;
		Printf24("示教",x,y+35,BLACK_COLOR,0,0xffff);

		x+=gap2;
		Watch_dis(x,y);
		x+=gap1;
		Printf24("时间",x,y+35,BLACK_COLOR,0,0xffff);

		// *********************第五行
		x=start_x+gap;y+=80;
		Ruler_dis(x,y);
		x+=gap1;
		Printf24("尺子",x,y+35,BLACK_COLOR,0,0xffff);

		x+=gap2;
		Auto_dis(x,y);
		x+=gap1;
		Printf24("自动",x,y+35,BLACK_COLOR,0,0xffff);

		x+=gap2;
		Manual_dis(x,y);
		x+=gap1;
		Printf24("手动",x,y+35,BLACK_COLOR,0,0xffff);

		// *********************第六行
		x=start_x+gap;y+=80;
		AutoKnife_dis(x,y);
		x+=gap1;
		Printf24("自刀",x,y+35,BLACK_COLOR,0,0xffff);

		x+=gap2;
		SelectPro_dis(x,y);
		x+=gap1;
		Printf24("选择程序",x,y+35,BLACK_COLOR,0,0xffff);
*/
		//------------页码
		Printf24("1/2 页",350,450,BLACK_COLOR,1,0xffff);

		break;
	case 1:
		x=start_x+gap,y=start_y+gap;
		gap1=50,gap2=110;
		Knife_Up_dis(x,y);//
		x+=gap1;
		Printf24("刀上",x,y+20,BLACK_COLOR,0,0xffff);

		x+=gap2;
		Knife_Down_dis(x,y);
		x+=gap1;
		Printf24("刀下",x,y+20,BLACK_COLOR,0,0xffff);

		x+=gap2;
		Press_Up_dis(x,y);
		x+=gap1;
		Printf24("压上",x,y+20,BLACK_COLOR,0,0xffff);

		x+=gap2;
		Press_Down_dis(x,y);
		x+=gap1;
		Printf24("压下",x,y+20,BLACK_COLOR,0,0xffff);

		x+=gap2;
		F4Wheel1_dis(x,y);
		x+=gap1;
		Printf24("手轮开",x,y+5,BLACK_COLOR,0,0xffff);
		//*********************第二行
		x=start_x+gap;y+=70;
		gap1=140,gap2=120;
		Program_dis(x,y);
		x+=gap1;
		Printf24("编程模式",x,y+35,BLACK_COLOR,0,0xffff);

		x+=gap2;
		Label_dis(x,y);
		x+=gap1;
		Printf24("标签模式",x,y+35,BLACK_COLOR,0,0xffff);

		x+=gap2;
		Parameter_dis(x,y);
		x+=gap1;
		Printf24("参数模式",x,y+35,BLACK_COLOR,0,0xffff);

		//*********************第三行
		x=start_x+gap;y+=80;
		Divide_dis(x,y);
		x+=gap1;
		Printf24("等分模式",x,y+35,BLACK_COLOR,0,0xffff);

		x+=gap2;
		Teach_dis(x,y);
		x+=gap1;
		Printf24("示教模式",x,y+35,BLACK_COLOR,0,0xffff);

		x+=gap2;
		Watch_dis(x,y);
		x+=gap1;
		Printf24("时间模式",x,y+35,BLACK_COLOR,0,0xffff);

		//*********************第四行
		x=start_x+gap;y+=80;
		Ruler_dis(x,y);
		x+=gap1;
		Printf24("基准模式",x,y+35,BLACK_COLOR,0,0xffff);

		x+=gap2;
		Auto_dis(x,y);
		x+=gap1;
		Printf24("自动模式",x,y+35,BLACK_COLOR,0,0xffff);

		x+=gap2;
		Manual_dis(x,y);
		x+=gap1;
		Printf24("手动模式",x,y+35,BLACK_COLOR,0,0xffff);

		//*********************第五行
		x=start_x+gap;y+=80;
		AutoKnife_dis(x,y);
		x+=gap1;
		Printf24("自刀模式",x,y+35,BLACK_COLOR,0,0xffff);

		x+=gap2;
		SelectPro_dis(x,y);
		x+=gap1;
		Printf24("选择程序",x,y+35,BLACK_COLOR,0,0xffff);

		x+=gap2;
		Lock_dis(x,y);
		x+=gap1;
		Printf24("密码模式",x,y+35,BLACK_COLOR,0,0xffff);		
		
		//*********************第六行
		x=start_x+gap;y+=80;
		gap1=90,gap2=80;
		Wheel1_dis(x,y);
		x+=gap1;
		Printf24("手轮开",x,y+5,BLACK_COLOR,0,0xffff);

		
		
		//*********************第七行
		x=start_x+gap;y+=70;
		
		//------------页码
		Printf24("2/2 页",350,450,BLACK_COLOR,1,0xffff);

		break;	
	}

}


void CurrentArea_save1(Int16U x,Int16U y, Int16U Wide,Int16U High)//暂存  当前区域 画面1
{
pInt16U pDis,pBuf;
volatile Int16U h,w;
pDis=(pInt16U)(SDRAM0_BASE_ADDR+(y*C_GLCD_H_SIZE+x)*2);
pBuf=(pInt16U)PIC_DIS_SAVE1;
for(h=0;h<High;h++)
  {
  for(w=0;w<Wide;w++)
    {
	*pBuf++=*pDis++;
	}
	y++;
	pDis=(pInt16U)(SDRAM0_BASE_ADDR+(y*C_GLCD_H_SIZE+x)*2);
  }
}
void CurrentArea_recover1(Int16U x, Int16U y, Int16U Wide,Int16U High)//恢复  当前区域 画面1
{
pInt16U pDis,pBuf;
volatile Int16U h,w;
pDis=(pInt16U)(SDRAM0_BASE_ADDR+(y*C_GLCD_H_SIZE+x)*2);
pBuf=(pInt16U)PIC_DIS_SAVE1;
for(h=0;h<High;h++)
  {
  for(w=0;w<Wide;w++)
    {
	*pDis++=*pBuf++;
	}
	y++;
	pDis=(pInt16U)(SDRAM0_BASE_ADDR+(y*C_GLCD_H_SIZE+x)*2);
  }
}

void CurrentArea_save2(Int16U x,Int16U y, Int16U Wide,Int16U High)//暂存  当前区域 画面2
{
pInt16U pDis,pBuf;
volatile Int16U h,w;
pDis=(pInt16U)(SDRAM0_BASE_ADDR+(y*C_GLCD_H_SIZE+x)*2);
pBuf=(pInt16U)PIC_DIS_SAVE2;
for(h=0;h<High;h++)
  {
  for(w=0;w<Wide;w++)
    {
	*pBuf++=*pDis++;
	}
	y++;
	pDis=(pInt16U)(SDRAM0_BASE_ADDR+(y*C_GLCD_H_SIZE+x)*2);
  }
}
void CurrentArea_recover2(Int16U x, Int16U y, Int16U Wide,Int16U High)//恢复  当前区域 画面2
{
pInt16U pDis,pBuf;
volatile Int16U h,w;
pDis=(pInt16U)(SDRAM0_BASE_ADDR+(y*C_GLCD_H_SIZE+x)*2);
pBuf=(pInt16U)PIC_DIS_SAVE2;
for(h=0;h<High;h++)
  {
  for(w=0;w<Wide;w++)
    {
	*pDis++=*pBuf++;
	}
	y++;
	pDis=(pInt16U)(SDRAM0_BASE_ADDR+(y*C_GLCD_H_SIZE+x)*2);
  }
}

void CurrentArea_save3(Int16U x,Int16U y, Int16U Wide,Int16U High)//暂存  当前区域 画面3
{
pInt16U pDis,pBuf;
volatile Int16U h,w;
pDis=(pInt16U)(SDRAM0_BASE_ADDR+(y*C_GLCD_H_SIZE+x)*2);
pBuf=(pInt16U)PIC_DIS_SAVE3;
for(h=0;h<High;h++)
  {
  for(w=0;w<Wide;w++)
    {
	*pBuf++=*pDis++;
	}
	y++;
	pDis=(pInt16U)(SDRAM0_BASE_ADDR+(y*C_GLCD_H_SIZE+x)*2);
  }
}
void CurrentArea_recover3(Int16U x, Int16U y, Int16U Wide,Int16U High)//恢复  当前区域 画面3
{
pInt16U pDis,pBuf;
volatile Int16U h,w;
pDis=(pInt16U)(SDRAM0_BASE_ADDR+(y*C_GLCD_H_SIZE+x)*2);
pBuf=(pInt16U)PIC_DIS_SAVE3;
for(h=0;h<High;h++)
  {
  for(w=0;w<Wide;w++)
    {
	*pDis++=*pBuf++;
	}
	y++;
	pDis=(pInt16U)(SDRAM0_BASE_ADDR+(y*C_GLCD_H_SIZE+x)*2);
  }
}
//**************************
void CurrentSize_dis(Int32U size)//当前尺寸---------------
{
Int8U num[8],k;
Int16U x,y,back_color=0x02FB;
Int8U Virture_size;

x=CURR_SIZE_X;
y=CURR_SIZE_Y;
back_color=0x9CD3;
if(Unit!=UNIT_MM)//inch
	{
	//if(SelfLockEn_flag==1)  //自锁
		//{
		switch(MotorType)
			{
			case MOTOR_FREQ_5_SPD_RST:
			case MOTOR_FREQ_3_SPD:
			case MOTOR_FREQ_3_SPD_RST:
				 Virture_size=MARGIN_SIZE;
					break;
			case MOTOR_DC_SERVO:
			case MOTOR_DC670_SERVO:
			case MOTOR_DC670_SERVO_ZHU:
				 Virture_size=DC_VIRTURE_SIZE;
					break;
			}
		if(DcServoGoTarget_flag==0)
			{
			if(CurrentSize>TargetSize)
				{
				if(CurrentSize-TargetSize<Virture_size)
					size=TargetSize_inch;
				else
					size=size*100/254;
				}
			else
				{
				if(TargetSize-CurrentSize<Virture_size)
					size=TargetSize_inch;
				else
					size=size*100/254;	
				}
			}
		else
			{
			size=size*100/254;
			}
		//}
	current_inch=size;
	}

if(size>1000000)
	{
	size=0;  //溢出-->0
	}
num[0]=size/100000;
num[1]=(size/10000)%10;
num[2]=(size/1000)%10;
num[3]=(size/100)%10;
num[4]='.';
num[5]=(size/10)%10;
num[6]=size%10;
num[7]=0;
if(Unit!=UNIT_MM)//inch
	{
	num[4]=num[3];
	num[3]='.';
	}
for(k=0;k<7;k++)
  {
  if(num[k]!='.')
     num[k]+=48;
  }
//Printf32(num,x,y,0xffff,1,back_color);
//ASCII_Printf(num,224+1,28,56,ASCII_28x56, x,y,0xffff,back_color);
ASCII_Printf(num,192+1,32,48,ASCII_32x48, x,y,0,back_color);
}


void FrontKnifeUint_dis(Int8U unit)  //刀前尺寸 单位--------------
{
Int16U x,y,back_color=0x9CD3;
x=FRONT_KNIF_X+160;
y=FRONT_KNIF_Y+5;
GLCD_SetWindow_Fill(x, y, x+40, y+25, back_color, back_color);
if(unit==UNIT_MM)//mm
   {
   Printf24("mm",x,y,BLACK_COLOR,1,back_color);
   }
else
   {
   Printf24("in",x,y,BLACK_COLOR,1,back_color);
   }
}
void CurrUint_dis(Int8U unit)  //当前尺寸 单位-----------------
{/*
Int16U x,y,back_color=0x02FB;
x=CURR_SIZE_X+180;
y=CURR_SIZE_Y+10;
back_color=BLUE_COLOR;
//GLCD_SetWindow_Fill(x, y, x+40, y+25, back_color, back_color);
if(unit==UNIT_MM)//mm
   {
   Printf24("mm",x,y,0xffff,1,back_color);
   }
else
   {
   Printf24("in",x,y,0xffff,1,back_color);
   }*/
FrontKnifeUint_dis(unit);//刀前尺寸 单位
GoDirMode=0;
}

void FrontKnifeSize_dis(Int32U size)//刀前尺寸-----------------
{
Int8U num[8],k;
Int16U x,y,back_color=0xf78a;
x=FRONT_KNIF_X;
y=FRONT_KNIF_Y;
//if(Unit!=UNIT_MM)//inch
//	{
//	if(BeforeKnife_offset_in<1)
//		size=size*100/254;
//	}
num[0]=size/100000;
num[1]=(size/10000)%10;
num[2]=(size/1000)%10;
num[3]=(size/100)%10;
num[4]='.';
num[5]=(size/10)%10;
num[6]=size%10;
num[7]=0;
if(Unit!=UNIT_MM)//inch
	{
	num[4]=num[3];
	num[3]='.';
	}
for(k=0;k<7;k++)
  {
  if(num[k]!='.')
     num[k]+=48;
  }
//Printf24(num,x,y,BLACK_COLOR,1,back_color);
ASCII_Printf(num,108+1,20,36,ASCII_20x36, x,y,0,back_color);
}
void FrontKnifeSize_NOdis(void)
{
Int16U x,y,back_color=0xf78a;
x=FRONT_KNIF_X;
y=FRONT_KNIF_Y;
GLCD_SetWindow_Fill(x-1, y, x+140, y+36, back_color, back_color);
}


void InputNum_dis(pInt8U nums,Int8U cou) //输入框内  尺寸输入显示
{
Int8U num_temp[8],n=0;

for(n=0;n<cou;n++)
   {
   num_temp[n]=nums[n];
   if((num_temp[n]!='.')&&(num_temp[n]!='-'))
     {
	 num_temp[n]+=48;
	 }
   }
num_temp[cou]=0;
//GLCD_SetWindow_Fill( SIZE_WINDOW_X, SIZE_WINDOW_Y, SIZE_WINDOW_X+120, SIZE_WINDOW_Y+30, 0xfffff, 0xffff);//尺寸输入
Printf24(num_temp,SIZE_WINDOW_X+25,SIZE_WINDOW_Y+5,BLACK_COLOR,1,0xffff);
}

void CursorMov_dis(Int8U row, Int8U show_flag)//红色光标
{
Int16U x,y,back_color=0xef9f;
if(row>(PAGE_KNIFE-1))
   {
   TableDis_startcol=RIGHT_PAGE_X;
   }
else
   {
   TableDis_startcol=RIGHT_ARROW_X;
   }
x=TableDis_startcol;
y=RIGHT_ARROW_Y+15+(row%PAGE_KNIFE)*45;
if(show_flag==1)//显示
   {
   RightArrow_dis(x,y);
   }
else
   {
   GLCD_SetWindow_Fill( x, y, x+15, y+15, back_color, back_color);//消失
   }
}


void KnifeOrder_dis(Int16U row, Int16U order,Int16U num_color)//-----------------------显示一个序号
{
Int8U num[5],k;
Int16U x,y,back_color=0xef9f;
if(row>(PAGE_KNIFE-1))
   {
   TableDis_startcol=RIGHT_PAGE_X;
   }
else
   {
   TableDis_startcol=RIGHT_ARROW_X;
   }
x=TableDis_startcol+18;
y=RIGHT_ARROW_Y+(row%PAGE_KNIFE)*45;

num[0]=order/100;
num[1]=(order/10)%10;
num[2]=order%10;
num[3]=0;
for(k=0;k<3;k++)
  {
  num[k]+=48;
  }
//Printf32(num,x,y,num_color,1,back_color);//序号
ASCII_Printf(num,114+1,18,38,ASCII_bold18x38, x,y,num_color,back_color);
}

void KnifeSize_dis(Int16U row,  Int32U Knife_size,Int16U num_color)//--------------显示一个尺寸
{
Int8U num[8],k;
Int16U x,y,back_color=0xef9f;
//Int32U size_inc;
if(row>(PAGE_KNIFE-1))
   {
   TableDis_startcol=RIGHT_PAGE_X;
   }
else
   {
   TableDis_startcol=RIGHT_ARROW_X;
   }  
x=TableDis_startcol+95;
y=RIGHT_ARROW_Y+(row%PAGE_KNIFE)*45;

num[0]=Knife_size/100000;
num[1]=(Knife_size/10000)%10;
num[2]=(Knife_size/1000)%10;
num[3]=(Knife_size/100)%10;
num[4]='.';
num[5]=(Knife_size/10)%10;
num[6]=Knife_size%10;
num[7]=0;
if(Unit!=UNIT_MM)
	{
	num[4]=num[3];
	num[3]='.';
	}
for(k=0;k<7;k++)
	{
	if(num[k]!='.')
		num[k]+=48;
	}
//Printf32(num,x,y,BLACK_COLOR,1,back_color);//尺寸显示
ASCII_Printf(num,120+1,24,40,ASCII_bold24x40, x,y,num_color,back_color);
}

void PushFlag_dis(Int8U row,  Int8U Knife_flag)//-------一个 推纸 标志显示
{
Int16U x,y,back_color=0xef9f;
x=RED_KNIFE_X;
y=RIGHT_ARROW_Y+10+row*45;
GLCD_SetWindow_Fill( x, y, x+25, y+25, back_color, back_color);//图标消失
switch(Knife_flag)
	{
	case PUSH_FLAG:  //推纸图标显示
			PushPaperF_dis(x,y);
			break;
	case KNIFE_FLAG:  //刀图标		
			RedKnifeF_dis(x,y);
			break;
	case PRE_AUTO_FLAG:  //自动循环图标		
			AutoRoutePRE_dis(x,y);//k自动循环 标志
			break;
	}
}

Int8U OneKnifeDataSel_dis(Int16U knife,Int8U row,Int16U num_color)  //一刀数据 高亮显示
{
KNIFE_DATA Knife_datas;
GetOneKnife_datas(Pro_data.pro_num, knife , (pInt8U)&Knife_datas);//取出一刀 数据
KnifeOrder_dis(row, knife,num_color);//序号
//-----------------步骤(尺寸)错误 判断 
if((Knife_datas.size<Size_MIN_num)||(Knife_datas.size>Size_MAX_num))
	{
	Knife_datas.size=0;
	Knife_datas.k_flag=0;
	if(Knife_sum>=knife)
		{
		if(knife>1)
			Knife_sum=knife-1;
		else
			Knife_sum=1;
		Knife_sum_before=Knife_sum;
		SaveKnife_sum(Pro_data.pro_num);//刀数 保存 
		StepNum_dis(Knife_sum, knife);//步骤更新
		}
	}
if(knife>Knife_sum)	//最后一个步骤 之后仍有数据 则清除
	{
	if(Knife_datas.size>0)
		{
		Knife_datas.size=0;
		Knife_datas.k_flag=0;
		}
	}	
KnifeSize_dis(row,  Knife_datas.size, num_color);//--------------显示一个尺寸
if(num_color==RED_COLOR)
	F5Button_dis(Knife_datas.k_flag);  //F5 一个 刀 标记 按钮
return Knife_datas.k_flag;
}

void ProNum_dis(Int16U pro_order) //程序号码显示
{
Int16U x,y,back_color=0x2E3B;
Int8U num[4],k;
back_color=0xce79;//----------
x=PROG_NUM_X,y=PROG_NUM_Y;
num[0]=pro_order/100;
num[1]=(pro_order/10)%10;
num[2]=pro_order%10;
num[3]=0;
for(k=0;k<3;k++)
   {
   num[k]+=48;
   }
Printf24(num,x,y,BLACK_COLOR,1,back_color);//程序
}

void StepNum_dis(Int16U step_sum,Int16U step_order) //步骤号码显示(总刀数-刀号)
{
Int16U x,y,back_color=0x2E3B;
Int8U num[8],k;
back_color=0xce79;//----------
x=STEP_NUM_X,y=STEP_NUM_Y;
num[0]=step_sum/100;
num[1]=(step_sum/10)%10;
num[2]=step_sum%10;
num[3]='-';
num[4]=step_order/100;
num[5]=(step_order/10)%10;
num[6]=step_order%10;
num[7]=0;
for(k=0;k<7;k++)
   {
   if(k!=3)
     num[k]+=48;
   }
Printf24(num,x,y,BLACK_COLOR,1,back_color);// 步骤
if(InputTouch_flag==0)  //	 非 触摸计算器 下
	{
	switch(WorkMode)
		{
		case  PROG_MODE://编程画面下
		case AUTO_MODE://自动主画面下
		case AUTO_PLUS_MODE://自动F3++
		case AUTO_MINUS_MODE://自动F4--
		
		case TEACH_MODE://示教 模式
		case AUTO_TO_SELF_MODE:   //自动-->自刀过度 模式
		case SELF_CUT_MODE:  //自刀主 模式
		case SELF_PLUS_MODE: //自刀 F3++
		case SELF_MINUS_MODE://自刀 F4--
			ProgressBar_dis(step_sum, step_order);//进度条 显示
			break;
		}	
	}
}

void StepOrder_dis(Int16U step_order)//(-刀号)  步骤显示
{
Int16U x,y,back_color=0x2E3B;
Int8U num[4],k;
back_color=0xce79;//----------
x=STEP_NUM_X+48,y=STEP_NUM_Y;
num[0]=step_order/100;
num[1]=(step_order/10)%10;
num[2]=step_order%10;
num[3]=0;
for(k=0;k<3;k++)
   {
   num[k]+=48;
   }
Printf24(num,x,y,BLACK_COLOR,1,back_color);// 步骤
if(InputTouch_flag==0)  //	 非 触摸计算器 下
	{
	switch(WorkMode)
		{
		case  PROG_MODE://编程画面下
		case AUTO_MODE://自动主画面下
		case AUTO_PLUS_MODE://自动F3++
		case AUTO_MINUS_MODE://自动F4--
		
		case TEACH_MODE://示教 模式
		case AUTO_TO_SELF_MODE:   //自动-->自刀过度 模式
		case SELF_CUT_MODE:  //自刀主 模式
		case SELF_PLUS_MODE: //自刀 F3++
		case SELF_MINUS_MODE://自刀 F4--
			ProgressBar_dis(Knife_sum,Knife_order);  //进度条 显示
			break;
		}	
	}
}


void MoveForward(void)//前进
{
MotorRun_flag=1;
switch(MotorType)
	{
	case MOTOR_FREQ_5_SPD_RST://----5档速 
		RLOUT3_ON;   //   后退断开
		RLOUT2_OFF;  //   前进闭合
		
		RLOUT5_OFF;  //   刹车闭合------------5档
		break;
	case MOTOR_FREQ_3_SPD://----3 档速	
	case MOTOR_FREQ_3_SPD_RST://----3 档速+复位	
		RLOUT3_OFF;  //   刹车闭合
		OOUT2_OFF;  //	前进 闭合
		OOUT1_ON;  //  后退 断开
		
		break;
	}
if(SelfLockEn_flag == 0) //  未定位--
	{
	RLOUT1_ON; RLOUT1_1_ON;   // 允许裁切断开
	}
else
	{
	if(PressDown_flag == 0)// 压纸 未下
		{
		RLOUT1_ON; RLOUT1_1_ON;   // 允许裁切断开
		}
	}
CutPermit_flag=0;	
}
void MoveBack(void) //后退
{
MotorRun_flag=1;
switch(MotorType)
	{
	case MOTOR_FREQ_5_SPD_RST://----5档速
		RLOUT3_OFF;//   后退闭合
		RLOUT2_ON;

		RLOUT5_OFF;  //   刹车闭合------------5档
		break;
	case MOTOR_FREQ_3_SPD://----3 档速	
	case MOTOR_FREQ_3_SPD_RST://----3 档速+复位	
		RLOUT3_OFF;  //   刹车闭合
		OOUT1_OFF;  //	后退 闭合
		OOUT2_ON;  //  前进 断开
		
		break;
	}
if(SelfLockEn_flag == 0) //  未定位--
		{
		RLOUT1_ON; RLOUT1_1_ON;   // 允许裁切断开
		}
else
	{
	if(PressDown_flag == 0)// 压纸 未下
		{
		RLOUT1_ON; RLOUT1_1_ON;   // 允许裁切断开
		}
	}
CutPermit_flag=0;		
}

void MoveStop(void)
{
MotorRun_flag=0;
switch(MotorType)
	{
	case MOTOR_FREQ_5_SPD_RST: //----5档速
		OOUT1_ON;
		OOUT3_ON;
		OOUT4_ON; 

		RLOUT2_ON;  //   前进
		RLOUT3_ON;//   后退
		if(Wheel_limit==0)
			{
			RLOUT5_ON;  //   刹车断开------------5档
			RLOUT1_OFF; RLOUT1_1_OFF;   // 允许裁切	
			}
		break;
	case MOTOR_FREQ_3_SPD: //----3 档速	
	case MOTOR_FREQ_3_SPD_RST: //----3 档速+复位
		if(Wheel_limit==0)
			{
			RLOUT3_ON;  //   刹车断开
			RLOUT1_OFF; RLOUT1_1_OFF;    // 允许裁切	
			}
		OOUT1_ON;  //	后退 断开
		OOUT2_ON;  //  前进 断开
		
		OOUT3_ON;
		OOUT4_ON;//速度归零
		break;
	}
// RLOUT1_OFF;    // 允许裁切	
MoveSpeed=0;
}

void SetMotorSpeed(Int8U speed_sel)//设定速度
{
switch(speed_sel)
	{
	case 1: //最快速度
		switch(MotorType)
			{
			case MOTOR_FREQ_5_SPD_RST://----5 档速
				OOUT1_ON;
				OOUT3_ON;
				OOUT4_OFF;  
					break;
			case MOTOR_FREQ_3_SPD://----3 档速	
			case MOTOR_FREQ_3_SPD_RST://----3 档速+复位		
				OOUT3_ON;
				OOUT4_OFF; 
					break;
			}
		//RLOUT1_ON;    // 允许裁切断开
			break;
	case 2: //中高速
		switch(MotorType)
			{
			case MOTOR_FREQ_5_SPD_RST://----5 档速
				OOUT1_ON;
				OOUT3_OFF;
				OOUT4_OFF;  
					break;
			case MOTOR_FREQ_3_SPD://----3 档速	
			case MOTOR_FREQ_3_SPD_RST://----3 档速+复位		
				OOUT3_OFF;
				OOUT4_OFF; 
					break;
			}
		//RLOUT1_ON;    // 允许裁切断开
			break;	
	case 3: //中速
		switch(MotorType)
			{
			case MOTOR_FREQ_5_SPD_RST://----5 档速
				OOUT1_OFF;
				OOUT3_OFF;
				OOUT4_ON;  
					break;
			case MOTOR_FREQ_3_SPD://----3 档速	
			case MOTOR_FREQ_3_SPD_RST://----3 档速+复位		
				OOUT3_OFF;
				OOUT4_OFF; 
				//OOUT3_OFF;
				// OOUT4_ON;
					break;
			}
		//RLOUT1_ON;    // 允许裁切断开
			break;
	case 4: //低速
		switch(MotorType)
			{
			case MOTOR_FREQ_5_SPD_RST://----5 档速
				OOUT1_ON;
				OOUT3_OFF;
				OOUT4_ON;  
					break;
			case MOTOR_FREQ_3_SPD://----3 档速	
			case MOTOR_FREQ_3_SPD_RST://----3 档速+复位		
				OOUT3_OFF;
				OOUT4_ON; 
					break;
			}
		//RLOUT1_ON;    // 允许裁切断开
			break;
	case 5://复位
		switch(MotorType)
			{
			case MOTOR_FREQ_5_SPD_RST://----5 档速
				OOUT1_OFF;
				OOUT3_ON;
				OOUT4_ON; 
					break;
			//case 1://----3 档速	
			case MOTOR_FREQ_3_SPD_RST://----3 档速+复位		
				OOUT3_ON;
				OOUT4_ON; 
					break;
			}
		//RLOUT1_ON;    // 允许裁切断开
			break;
	}
}

void MoveSpeedCtrl(void)    //
{
Int32U temp;
if(TargetSize>=CurrentSize)
	{  
	temp=TargetSize-CurrentSize;
	if(temp<2500)  //中速后退	//高速后退
		{
		if(MoveSpeed!=3)
			{
			MoveSpeed=3;//1;
			SetMotorSpeed(MoveSpeed);
			}
		}
	else	// 高速后退
	    {
		if(MoveSpeed!=1)
			{
			MoveSpeed=1;
			SetMotorSpeed(MoveSpeed);
			}
		}
	if(Backward_flag==0)
		{
		Forward_flag=0;
		Backward_flag=1;
		MoveBack();  //后退
		}
	}
else if(TargetSize<CurrentSize)
	{
	if(TargetSize>=Size_MIN)
		{
		temp=CurrentSize-TargetSize;
		if(Backward_flag==0)
			{
			if(temp>8000)  //80-  高速 前进
				{
				if(MoveSpeed!=1)
					{
					MoveSpeed=1;
					SetMotorSpeed(MoveSpeed);
					}
				if(Forward_flag==0)
					{
					MoveForward();//前进
					Forward_flag=1;
					}
				}
			else
				{
				if(temp>2000) //12-80  中高速
					{
					if(MoveSpeed!=2)
						{
						MoveSpeed=2;
						SetMotorSpeed(MoveSpeed);
						}
					if(Forward_flag==0)
						{
						MoveForward();//前进
						Forward_flag=1;
						}
					}
				else
					{
					if(temp>600) //6-12  中速
						{
						if(MoveSpeed!=3)
							{
							MoveSpeed=3;
							SetMotorSpeed(MoveSpeed);
							}
						if(Forward_flag==0)
							{
							MoveForward();//前进
							Forward_flag=1;
							}
						}
					else
						{
						if(temp>50)//0.5-6 低速
							{
							if(MoveSpeed!=4)
								{
								MoveSpeed=4;
								SetMotorSpeed(MoveSpeed);
								}
							if(Forward_flag==0)
								{
								MoveForward();//前进
								Forward_flag=1;
								}
							}
						else
							{
							if(Run_flag==0)
								{
								if(MoveSpeed!=3)
									{
									MoveSpeed=3;
									SetMotorSpeed(MoveSpeed);
									}
									MoveBack();  //后退
									Forward_flag=0;
									Backward_flag=1;
								}
							else
								{
						
								}
							}
						}
					}
				}
			}
		}
	else    //前极限  12//50mm处 低速
		{
		temp=CurrentSize-Size_MIN;
		if(temp<1200)
			{
			if(Backward_flag==0)
				{
				if(MoveSpeed<4)
					{
					MoveSpeed=4;
					SetMotorSpeed(MoveSpeed);
					}
				if(Forward_flag==0)
					{
					MoveForward();//前进
					Forward_flag=1;
					}	
				}
			}
		}
	}
}



void SpeedLevelSel_dis(Int8U motor,Int8U set_flag)    //电机类型 显示
{
Int16U F_color,B_color,x,y,gap;
if(set_flag==1)
	{
	F_color=WHITE_COLOR;
	B_color=BLUE_COLOR;
	}
else
	{
	F_color=BLUE_COLOR;
	B_color=WHITE_COLOR;
	}
x=200,y=150;gap=40;
switch(motor)
	{
	case MOTOR_FREQ_5_SPD_RST://五档速带复位
		switch(Language)
			{
			case CHN_HAN:
				Printf24("1------五档速带复位",x,y,F_color,1,B_color);
				break;
			case ENGLISH:
				Printf24("1------5 gears and rest",x,y,F_color,1,B_color);
				break;
			}	
		break;
	case MOTOR_FREQ_3_SPD://三档速
		y+=gap;
		switch(Language)
			{
			case CHN_HAN:
				Printf24("2------三档速",x,y,F_color,1,B_color);
				break;
			case ENGLISH:
				Printf24("2------3 gears",x,y,F_color,1,B_color);
				break;
			}		
		break;
	case MOTOR_FREQ_3_SPD_RST://三档速带复位	
		y+=gap*2;
		switch(Language)
			{
			case CHN_HAN:
				Printf24("3------三档速带复位",x,y,F_color,1,B_color);
				break;
			case ENGLISH:
				Printf24("3------3 gears and rest",x,y,F_color,1,B_color);
				break;
			}
		break;
	case MOTOR_DC_SERVO:	 		//直流伺服	
		y+=gap*3;
		switch(Language)
			{
			case CHN_HAN:
				Printf24("4------直流伺服",x,y,F_color,1,B_color);
				break;
			case ENGLISH:
				Printf24("4------DC servo",x,y,F_color,1,B_color);
				break;
			}
		break;
	case MOTOR_DC670_SERVO:	 		//直流伺服	670
		y+=gap*4;
		switch(Language)
			{
			case CHN_HAN:
				Printf24("5------直流伺服670",x,y,F_color,1,B_color);
				break;
			case ENGLISH:
				Printf24("5------DC servo 670",x,y,F_color,1,B_color);
				break;
			}
		break;
	case MOTOR_DC670_SERVO_ZHU:	 		//直流伺服	670朱
		y+=gap*5;
		switch(Language)
			{
			case CHN_HAN:
				Printf24("6------直流伺服670朱",x,y,F_color,1,B_color);
				break;
			case ENGLISH:
				Printf24("6------DC servo 670 ZHU",x,y,F_color,1,B_color);
				break;
			}
		break;	
	case MOTOR_AC_SERVO:	 		//交流伺服	
		y+=gap*6;
		switch(Language)
			{
			case CHN_HAN:
				Printf24("7------交流伺服",x,y,F_color,1,B_color);
				break;
			case ENGLISH:
				Printf24("7------AC servo",x,y,F_color,1,B_color);
				break;
			}
		break;	
	}
}

void NewInput_dis(Int32U size)
{
Int8U num[8],n=0;
num[n++]=size/100000;
num[n++]=(size/10000)%10;
num[n++]=(size/1000)%10;
num[n++]=(size/100)%10;
num[n++]='.';
num[n++]=(size/10)%10;
num[n]=size%10;
if(Unit!=UNIT_MM)//mm
	{
	num[4]=num[3];
	num[3]='.';
	}
for(n=0;n<7;n++)
	{
	if(num[n]!='.')
		{
		num[n]+=48;
		}
	}
num[n]=0;
GLCD_SetWindow_Fill( SIZE_WINDOW_X, SIZE_WINDOW_Y, SIZE_WINDOW_X+120, SIZE_WINDOW_Y+30, 0xfffff, 0xffff);//尺寸输入
Printf24(num,SIZE_WINDOW_X+25,SIZE_WINDOW_Y+5,BLACK_COLOR,1,0xffff);
}

void Draw_cross(Int16U x,Int16U y,Int16U color)
{
Int16U x1,y1,len=30,ww=2;
x1=x-15;y1=y;
GLCD_SetWindow_Fill(x1, y1, x1+len, y1+ww, color, color);
x1=x;y1=y-15;
GLCD_SetWindow_Fill(x1, y1, x1+ww, y1+len, color, color);
}

void Button_dis(Int8U b_num,Int8U down_flag) //触摸 按钮 显示
{
Int16U butt_color,num_color;
Int16U x,y,gap1,gap2,gap3;
gap1=10,gap2=20,gap3=25;
if(down_flag==1)  //按下后
	{
	butt_color=GREEN_COLOR;
	num_color=RED_COLOR;
	}
else
	{
	butt_color=0x9fff;
	num_color=0;
	}
switch(b_num)
	{
	 case BUTT_INSERT:
			x=BUTT_X5;
			y=BUTT_Y1;
			GLCD_SetWindow_Fill(x,y,x+BUTT_WIDE,y+BUTT_HIGH,butt_color,butt_color);
			y+=gap2;
			switch(Language)
				{
				case CHN_HAN:
						x+=gap1;
						Printf24("插入",x,y,num_color,0,0xffff);
						break;
				case ENGLISH:
						Printf24(" INSE",x,y,num_color,0,0xffff);
						break;
				}
			break;
	 case BUTT_EXIT:
			x=BUTT_X5;
			y=BUTT_Y2;
			GLCD_SetWindow_Fill(x,y,x+BUTT_WIDE,y+BUTT_HIGH,butt_color,butt_color);
			y+=gap2;
			switch(Language)
				{
				case CHN_HAN:
						x+=gap1;
						Printf24("退出",x,y,num_color,0,0xffff);
						break;
				case ENGLISH:
						Printf24(" EXIT",x,y,num_color,0,0xffff);
						break;
				}
			break;
	 case BUTT_EQU:
			x=BUTT_X5;
			y=BUTT_Y3;
			GLCD_SetWindow_Fill(x,y,x+BUTT_WIDE,y+BUTT_HIGH,butt_color,butt_color);
			x+=gap3;y+=gap2;
			Printf24("=",x,y,num_color,0,0xffff);
			break;
	 case BUTT_ENTER:
			x=BUTT_X5;
			y=BUTT_Y4;
			GLCD_SetWindow_Fill(x,y,x+BUTT_WIDE,y+BUTT_HIGH,butt_color,butt_color);
			y+=gap2;
			switch(Language)
				{
				case CHN_HAN:
						x+=gap1;
						Printf24("确认",x,y,num_color,0,0xffff);
						break;
				case ENGLISH:
						Printf24(" ENT",x,y,num_color,0,0xffff);
						break;
				}
			break;
	 case BUTT_RUN:
			x=BUTT_X5;
			y=BUTT_Y4;
			GLCD_SetWindow_Fill(x,y,x+BUTT_WIDE,y+BUTT_HIGH,butt_color,butt_color);
			x+=gap1;y+=gap2;
			switch(Language)
				{
				case CHN_HAN:
						Printf24("运行",x,y,num_color,0,0xffff);
						break;
				case ENGLISH:
						Printf24(" RUN",x,y,num_color,0,0xffff);
						break;
				}
			break;
	 case BUTT_CLEAR:
			x=BUTT_X1;
			y=BUTT_Y4;
			GLCD_SetWindow_Fill(x,y,x+BUTT_WIDE,y+BUTT_HIGH,butt_color,butt_color);
			x+=gap3;y+=gap2;
			Printf24("C",x,y,num_color,0,0xffff);
			break;
	 case BUTT_DOT:
			x=BUTT_X3;
			y=BUTT_Y4;
			GLCD_SetWindow_Fill(x,y,x+BUTT_WIDE,y+BUTT_HIGH,butt_color,butt_color);
			x+=gap3;y+=gap2;
			Printf24(".",x,y,num_color,0,0xffff);
			break;
	 case BUTT_MUL:
			x=BUTT_X4;
			y=BUTT_Y3;
			GLCD_SetWindow_Fill(x,y,x+BUTT_WIDE,y+BUTT_HIGH,butt_color,butt_color);
			x+=gap3;y+=gap2;
			Printf24("*",x,y,num_color,0,0xffff);
			break;
	 case BUTT_DIV:
			x=BUTT_X4;
			y=BUTT_Y4;
			GLCD_SetWindow_Fill(x,y,x+BUTT_WIDE,y+BUTT_HIGH,butt_color,butt_color);
			x+=gap3;y+=gap2;
			Printf24("/",x,y,num_color,0,0xffff);
			break;
	 case BUTT_PLUS:
			x=BUTT_X4;
			y=BUTT_Y1;
			GLCD_SetWindow_Fill(x,y,x+BUTT_WIDE,y+BUTT_HIGH,butt_color,butt_color);
			x+=gap3;y+=gap2;
			Printf24("+",x,y,num_color,0,0xffff);
			break;
	 case BUTT_SUB:
			x=BUTT_X4;
			y=BUTT_Y2;
			GLCD_SetWindow_Fill(x,y,x+BUTT_WIDE,y+BUTT_HIGH,butt_color,butt_color);
			x+=gap3;y+=gap2;
			Printf24("-",x,y,num_color,0,0xffff);
			break;		
	 case BUTT_0:
			x=BUTT_X2;
			y=BUTT_Y4;
			GLCD_SetWindow_Fill(x,y,x+BUTT_WIDE,y+BUTT_HIGH,butt_color,butt_color);
			x+=gap3;y+=gap2;
			Printf24("0",x,y,num_color,0,0xffff);
			break;		
	 case BUTT_1:
			x=BUTT_X1;
			y=BUTT_Y1;
			GLCD_SetWindow_Fill(x,y,x+BUTT_WIDE,y+BUTT_HIGH,butt_color,butt_color);
			x+=gap3;y+=gap2;
			Printf24("1",x,y,num_color,0,0xffff);
			break;		
	 case BUTT_2:
			x=BUTT_X2;
			y=BUTT_Y1;
			GLCD_SetWindow_Fill(x,y,x+BUTT_WIDE,y+BUTT_HIGH,butt_color,butt_color);
			x+=gap3;y+=gap2;
			Printf24("2",x,y,num_color,0,0xffff);
			break;		
	 case BUTT_3:
			x=BUTT_X3;
			y=BUTT_Y1;
			GLCD_SetWindow_Fill(x,y,x+BUTT_WIDE,y+BUTT_HIGH,butt_color,butt_color);
			x+=gap3;y+=gap2;
			Printf24("3",x,y,num_color,0,0xffff);
			break;		
	 case BUTT_4:
			x=BUTT_X1;
			y=BUTT_Y2;
			GLCD_SetWindow_Fill(x,y,x+BUTT_WIDE,y+BUTT_HIGH,butt_color,butt_color);
			x+=gap3;y+=gap2;
			Printf24("4",x,y,num_color,0,0xffff);
			break;		
	 case BUTT_5:
			x=BUTT_X2;
			y=BUTT_Y2;
			GLCD_SetWindow_Fill(x,y,x+BUTT_WIDE,y+BUTT_HIGH,butt_color,butt_color);
			x+=gap3;y+=gap2;
			Printf24("5",x,y,num_color,0,0xffff);
			break;		
	 case BUTT_6:
			x=BUTT_X3;
			y=BUTT_Y2;
			GLCD_SetWindow_Fill(x,y,x+BUTT_WIDE,y+BUTT_HIGH,butt_color,butt_color);
			x+=gap3;y+=gap2;
			Printf24("6",x,y,num_color,0,0xffff);
			break;		
	 case BUTT_7:
			x=BUTT_X1;
			y=BUTT_Y3;
			GLCD_SetWindow_Fill(x,y,x+BUTT_WIDE,y+BUTT_HIGH,butt_color,butt_color);
			x+=gap3;y+=gap2;
			Printf24("7",x,y,num_color,0,0xffff);
			break;		
	 case BUTT_8:
			x=BUTT_X2;
			y=BUTT_Y3;
			GLCD_SetWindow_Fill(x,y,x+BUTT_WIDE,y+BUTT_HIGH,butt_color,butt_color);
			x+=gap3;y+=gap2;
			Printf24("8",x,y,num_color,0,0xffff);
			break;		
	 case BUTT_9:
			x=BUTT_X3;
			y=BUTT_Y3;
			GLCD_SetWindow_Fill(x,y,x+BUTT_WIDE,y+BUTT_HIGH,butt_color,butt_color);
			x+=gap3;y+=gap2;
			Printf24("9",x,y,num_color,0,0xffff);
			break;	
	case BUTT_UP:
			x=BUTT_X6;
			y=BUTT_Y1;
			GLCD_SetWindow_Fill(x,y,x+BUTT_WIDE_ARROW,y+BUTT_HIGH_ARROW,butt_color,butt_color);
			x+=15;y+=BUTT_HIGH+15;
			//Printf24("<",x,y,num_color,0,0xffff);
			GLCD_Triangle_Fill(x,y, x+10,y-15, x+20,y ,num_color,num_color);
			break;	
	case BUTT_DOWN:
			x=BUTT_X6;
			y=BUTT_Y3;
			GLCD_SetWindow_Fill(x,y,x+BUTT_WIDE_ARROW,y+BUTT_HIGH_ARROW,butt_color,butt_color);
			x+=15;y+=BUTT_HIGH-5;
			//Printf24(">",x,y,num_color,0,0xffff);
			GLCD_Triangle_Fill(x,y, x+10,y+15, x+20,y ,num_color,num_color);
			break;		
	}
}

void CalcInputNums_dis(pInt8U nums)//计算公式  文本框
{
Int16U x,y,num_color=0;
Int8U i,n;
Int8U Num[24];
i=0;
while((*nums!=0xff)&&(i<24))
	{
	if(*nums<'*')  //  '*'==42(ascii)
		Num[i++]=*nums+48;
	else
		Num[i++]=*nums;
	nums++;
	}
Num[i]=0;
x=CALCUL_TEXT_END-(12*i),y=CALCUL_TEXT_Y+5;
Printf24(Num,x,y,num_color,1,0xffff);	
}

void CalcResultNums_dis(pInt8U nums)//结果  文本框
{
Int16U x,y,num_color=0;
Int8U i,n;
Int8U Num[24];
i=0;
while((*nums!=0xff)&&(i<24))
	{
	if(*nums<'*')  //  '*'==42(ascii)
		Num[i++]=*nums+48;
	else
		Num[i++]=*nums;
	nums++;
	}
Num[i]=0;
x=CALCUL_TEXT_END-10-(12*i),y=CALCUL_RESULT_Y+5;
Printf24(Num,x,y,num_color,1,0xffff);	
}

void ClrCalcNums_text(pInt8U pText,Int8U text_sel) //计算器数据 清除
{
Int8U i;
Int16U L_color=BLUE_COLOR,Fill_color=0xffff;
*pText++=0;
for(i=1;i<24;i++)
	{
	*pText++=0xff;
	}
if(text_sel==CAL_INPUT) //计算器 输入框
	{
	GLCD_SetWindow_Fill(CALCUL_TEXT_X,CALCUL_TEXT_Y,CALCUL_TEXT_X+CALCUL_TEXT_W,CALCUL_TEXT_Y+CALCUL_TEXT_H,L_color,Fill_color);//数字输入区
	}
else   //结果 框
	{
	GLCD_SetWindow_Fill(CALCUL_RESULT_X,CALCUL_RESULT_Y,CALCUL_RESULT_X+CALCUL_RESULT_W,CALCUL_RESULT_Y+CALCUL_RESULT_H,L_color,Fill_color);//结果显示区
	}	
}

void Calculator_Window(void)  //计算器
{
Int8U n=0;
Int16U L_color=BLUE_COLOR,Fill_color=CALCUL_COLOR;
CurrentArea_save3(CALCUL_WIN_X , CALCUL_WIN_Y,  CALCUL_WIDE, CALCUL_HIGH);
GLCD_SetWindow_Fill(CALCUL_WIN_X,CALCUL_WIN_Y,CALCUL_WIN_X+CALCUL_WIDE-1,CALCUL_WIN_Y+CALCUL_HIGH-1 ,L_color,Fill_color);

//按钮显示
while(n<=22)
	{
	if(WorkMode==MANUAL_MODE)  // 手动模式
		{
		if(n==BUTT_ENTER)
			n++;
		}
	else
		{
		if(n==BUTT_RUN)
			n++;
		}
	Button_dis(n++, 0); //触摸 按钮 显示
	}
}

void PushResetPrompt_dis(void)  //开机 推纸器 复位  提示
{
Int16U L_color,Fill_color;
L_color=BLUE_COLOR,Fill_color=0xffff;
CurrentArea_save3(PUSH_RESET_PROMPT_X1, PUSH_RESET_PROMPT_Y1, PUSH_RESET_PROMPT_WIDE, PUSH_RESET_PROMPT_WIDE);
GLCD_SetWindow_Fill(PUSH_RESET_PROMPT_X1, PUSH_RESET_PROMPT_Y1, PUSH_RESET_PROMPT_X1+PUSH_RESET_PROMPT_WIDE-1, 
					PUSH_RESET_PROMPT_Y1+PUSH_RESET_PROMPT_HIGH-1,L_color,Fill_color);//
switch(Language)
	{
	case CHN_HAN:
		Printf24("推纸器是否在最后!",PUSH_RESET_PROMPT_X1+80,PUSH_RESET_PROMPT_Y1+5,BLACK_COLOR,1,0xffff);
		Printf24("确定",PUSH_RESET_OK_X,PUSH_RESET_OK_Y,BLACK_COLOR,1,0xffff);
		Printf24("取消",PUSH_RESET_CANCEL_X,PUSH_RESET_CANCEL_Y,BLACK_COLOR,1,0xffff);
		break;
	case ENGLISH:	
		Printf24("Whether Paper-Pusher is in the end!",PUSH_RESET_PROMPT_X1+1,PUSH_RESET_PROMPT_Y1+5,BLACK_COLOR,1,0xffff);
		Printf24("OK",PUSH_RESET_OK_X,PUSH_RESET_OK_Y,BLACK_COLOR,1,0xffff);
		Printf24("Cancel",PUSH_RESET_CANCEL_X,PUSH_RESET_CANCEL_Y,BLACK_COLOR,1,0xffff);
		break;
	}	
}

void ProgressBar_dis(Int16U total, Int16U now)  //进度条 显示
{
Int8U ratio;
Int16U x1,x2,y1,y2;
Int16U color;
if(now<=total)
	{
	ratio=now*200/total;
	x1=SCHEDULE_DOT_X,x2=x1+12;
	if(1)//(ratio!=ProcessRatio)
		{
		if(ProcessRatio!=0xff)    //不是 开始
			{
			color=0xf78a;
			y1=SCHEDULE_DOT_Y+ProcessRatio;
			y2=y1+12;
			GLCD_SetWindow_Fill(x1,y1, x2,y2 ,color,color);//清除 进度块
			
			}
		//**************
		ProcessRatio=ratio;
		color=0;
		y1=SCHEDULE_DOT_Y+ProcessRatio;
		y2=y1+12;
		GLCD_SetWindow_Fill(x1,y1, x2,y2 ,color,color);//更新 进度块
		}
	}

}

void MoveDirArrow_dis(Int8U dir)
{
Int16U x,y,f_color,b_color;
f_color=RED_COLOR,b_color=0x9CD3;
x=MOV_DIR_X,y=MOV_DIR_Y;
if(dir == 0)//前进
	{
	if(GoDirMode != 1)
		{
		GoDirMode=1;
		GLCD_SetWindow_Fill(x,y,x+20,y+20,b_color,b_color);
		GLCD_Triangle_Fill(x,y, x+19,y, x+10,y+15,f_color,f_color);
		}
	}
else
	{
	if(GoDirMode != 2)
		{
		GoDirMode=2;
		GLCD_SetWindow_Fill(x,y,x+20,y+20,b_color,b_color);
		GLCD_Triangle_Fill(x,y+15, x+19,y+15, x+10,y,f_color,f_color);
		}
	}
}
