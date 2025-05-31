

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



Int16U cursor_row;//光标 位置(行)
Int16U  TableDis_startcol;//起始列

Int16U Knife_order; //当前刀号
Int16U Knife_sum_before;//总刀数
Int16U MAX_Knife;//最多刀数

//Int16U Process_num;//当前程序 号
//Int16U MaixProcess_num;//最大 程序号

PROG_SEG Pro_data;//程序 段 号

PROCESS_HEAD OnePro_head;//
PROCESS_HEAD Pro_head_temp;//
KNIFE_DATA OneKnife_data;
START_DAY Start_days;

Int16U ProNumGroup[MAX_PROG+2];
Int16U prog_order;

unsigned char PorgSet_sel;

unsigned char BeforeKnifeNo_flag;

unsigned short WorkMode;
unsigned short WorkMode_temp;

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

const PROCESS_HEAD ProHead_default={{0}, {0}, 0,0,0, 1};
const pInt8U NAME_flag={"name"};

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

Int8U ButtonTouch_mode;
Int16U CodeSensorTime_AB;
Int8U CutPermit_flag;

Int8U ServoPressStop_flag;//伺服压纸 停机

Int8U DcServoGoTarget_flag;

Int16U LastAutoKnife_order;//  自刀 的前一刀
Int8U ReEnterAutoKnife_dis;  //再次进入自刀  提示

Int8U ACServoDrvErr_flag;
Int8U ACServoAlarmExec_flag;

Int8U ElectricWheelOn_flag; //电子手轮

// Int8U F4Mode_flag;
Int32U current_inch;
Int8U MotorRun_flag;

Int8U InputMode;

Int8U DivideValue_flag;
Int8U DisAllProgMode;

Int8U KnifeSensorMode;//knife press sensor 
Int8U PressSensorMode;

Int32U AirOffDistance;//关气阀距离

Int8U AirOffOK_flag;//

//Int8U AirOffStart_flag;

Int8U IR_SensorStus;
//-----------------------偏移量运行 模式
Int8U AmendSwitch_flag;
// Int8U AmendModeEnb_flag;
Int8U AmendStartRun_flag;
Int32U AmendSize;
Int8U AmendPlus_flag;

Int8U CutPressRoll_flag;


Int8U PageKf_Size_flag;//每页刀数flag
Int8U PageKf_Size;//每页刀数
Int8U Kf_Line_HIGH;//行高

Int8U AmendOver_flag;

Int8U Para_sel;
Int8U PramSel_Page;//参数 列表页
Int8U Para2_sel;//2 列表项
Int32U Step_Size; //步进距离

Int32U VirtualTargetSizeGap;
Int8U IRChgWorkmodeValid_flag;//红外切换工作模式标记

Int16U PressFlagRunCou;
Int16U AutoPressWork_Time;
Int8U AutoPressWork_TimeSet;
Int8U AutoPressWork_flag;

Int8U SetModeEnbByCode_flag;

Int8U ReadAir_flag;
Int8U Air_flag_temp;

Int16U AutoModeKnifeOrder_temp;


Int8U BmpJudge(Int32U Bmp_add)
{
struct BMP_HEADER head_temp;
struct BMP_INFO info_temp;
pInt8U p =(pInt8U)Bmp_add;
Int8U type;
/***
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
		}**/
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
//GLCD_SetWindow_Fill(0,0,799,479,BLACK_COLOR,BLACK_COLOR);//*******************************
// GLCD_Buffer_Fill(0);
FileFolderRead("右箭头.bmp",(unsigned char*)RIGHT_ARROW_sdram);//
if(BmpJudge((Int32U)RIGHT_ARROW_sdram)==0)
FileFolderRead("b右箭头.bmp",(unsigned char*)RIGHT_ARROW_sdram);//
FileFolderRead("滚动条.bmp",(unsigned char*)SCHEDULE_sdram);
if(BmpJudge((Int32U)SCHEDULE_sdram)==0)
FileFolderRead("b滚动条.bmp",(unsigned char*)SCHEDULE_sdram);
//-------------------------------mode up

FileFolderRead("手动模式up.bmp",(unsigned char*)MANUAL_MOD_UP_sdram);
if(BmpJudge((Int32U)MANUAL_MOD_UP_sdram)==0)
FileFolderRead("b手动模式up.bmp",(unsigned char*)MANUAL_MOD_UP_sdram);
FileFolderRead("自动模式up.bmp",(unsigned char*)AUTO_MOD_UP_sdram);
if(BmpJudge((Int32U)AUTO_MOD_UP_sdram)==0)
FileFolderRead("b自动模式up.bmp",(unsigned char*)AUTO_MOD_UP_sdram);
FileFolderRead("查看模式up.bmp",(unsigned char*)FIND_MOD_UP_sdram);
if(BmpJudge((Int32U)FIND_MOD_UP_sdram)==0)
FileFolderRead("b查看模式up.bmp",(unsigned char*)FIND_MOD_UP_sdram);
//-------------------------------mode down
FileFolderRead("手动模式down.bmp",(unsigned char*)MANUAL_MOD_DOWN_sdram);
if(BmpJudge((Int32U)MANUAL_MOD_DOWN_sdram)==0)
FileFolderRead("b手动模式down.bmp",(unsigned char*)MANUAL_MOD_DOWN_sdram);
FileFolderRead("自动模式down.bmp",(unsigned char*)AUTO_MOD_DOWN_sdram);
if(BmpJudge((Int32U)AUTO_MOD_DOWN_sdram)==0)
FileFolderRead("b自动模式down.bmp",(unsigned char*)AUTO_MOD_DOWN_sdram);
FileFolderRead("查看模式down.bmp",(unsigned char*)FIND_MOD_DOWN_sdram);
if(BmpJudge((Int32U)FIND_MOD_DOWN_sdram)==0)
FileFolderRead("b查看模式down.bmp",(unsigned char*)FIND_MOD_DOWN_sdram);

FileFolderRead("主电源开up.bmp",(unsigned char*)POWER_ON_UP_sdram);
FileFolderRead("主电源开down.bmp",(unsigned char*)POWER_ON_DOWN_sdram);
FileFolderRead("主电源关up.bmp",(unsigned char*)POWER_OFF_UP_sdram);
FileFolderRead("主电源关down.bmp",(unsigned char*)POWER_OFF_DOWN_sdram);
FileFolderRead("电源黑.bmp",(unsigned char*)POWER_CTRL_sdram);
FileFolderRead("对刀灯on.bmp",(unsigned char*)LIGHT_KNIFE_DOWN_sdram);
FileFolderRead("对刀灯off.bmp",(unsigned char*)LIGHT_KNIFE_UP_sdram);
FileFolderRead("灯控.bmp",(unsigned char*)LIGHT_CTRL_sdram);
FileFolderRead("照明灯on.bmp",(unsigned char*)LIGHT_LED_DOWN_sdram);
FileFolderRead("照明灯off.bmp",(unsigned char*)LIGHT_LED_UP_sdram);
FileFolderRead("正常裁切on.bmp",(unsigned char*)NORMAL_KNIFE_DOWN_sdram);
FileFolderRead("正常裁切off.bmp",(unsigned char*)NORMAL_KNIFE_UP_sdram);
FileFolderRead("手动刀on.bmp",(unsigned char*)MANUAL_KNIFE_DOWN_sdram);
FileFolderRead("手动刀off.bmp",(unsigned char*)MANUAL_KNIFE_UP_sdram);
FileFolderRead("电动刀on.bmp",(unsigned char*)ELECTRIC_KNIFE_DOWN_sdram);
FileFolderRead("电动刀off.bmp",(unsigned char*)ELECTRIC_KNIFE_UP_sdram);
FileFolderRead("风泵关.bmp",(unsigned char*)PUMP_OFF_UP_sdram);
FileFolderRead("风泵开.bmp",(unsigned char*)PUMP_ON_UP_sdram);

FileFolderRead("示教按钮.bmp",(unsigned char*)TEACH_MOD_BUTT_sdram);
if(BmpJudge((Int32U)TEACH_MOD_BUTT_sdram)==0)
FileFolderRead("b示教按钮.bmp",(unsigned char*)TEACH_MOD_BUTT_sdram);
FileFolderRead("自刀按钮.bmp",(unsigned char*)AUTOCUT_MOD_BUTT_sdram);
if(BmpJudge((Int32U)AUTOCUT_MOD_BUTT_sdram)==0)
FileFolderRead("b自刀按钮.bmp",(unsigned char*)AUTOCUT_MOD_BUTT_sdram);
FileFolderRead("推纸.bmp",(unsigned char*)PUSH_BUTT_sdram);
if(BmpJudge((Int32U)PUSH_BUTT_sdram)==0)
FileFolderRead("b推纸.bmp",(unsigned char*)PUSH_BUTT_sdram);
//------------
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
FileFolderRead("红线.bmp",(unsigned char*)IR_LINE_sdram);//红外
if(BmpJudge((Int32U)IR_LINE_sdram)==0)
FileFolderRead("b红线.bmp",(unsigned char*)IR_LINE_sdram);//红外
FileFolderRead("手红外.bmp",(unsigned char*)IR_CUT_sdram);//红外断开
if(BmpJudge((Int32U)IR_CUT_sdram)==0)
FileFolderRead("b手红外.bmp",(unsigned char*)IR_CUT_sdram);//红外断开
//----
//------------------------------F1,2,3...
FileFolderRead("F1标签.bmp",(unsigned char*)F1_LABELS_UP_sdram);
if(BmpJudge((Int32U)F1_LABELS_UP_sdram)==0)
FileFolderRead("bF1标签.bmp",(unsigned char*)F1_LABELS_UP_sdram);
FileFolderRead("F2等分.bmp",(unsigned char*)F2_DIVIDE_UP_sdram);
if(BmpJudge((Int32U)F2_DIVIDE_UP_sdram)==0)
FileFolderRead("bF2等分.bmp",(unsigned char*)F2_DIVIDE_UP_sdram);
FileFolderRead("F3插入.bmp",(unsigned char*)F3_INSERT_UP_sdram);
if(BmpJudge((Int32U)F3_INSERT_UP_sdram)==0)
FileFolderRead("bF3插入.bmp",(unsigned char*)F3_INSERT_UP_sdram);
// FileFolderRead("F3程序.bmp",(unsigned char*)F3_SELECT_PRO_UP_sdram);
FileFolderRead("F4删除.bmp",(unsigned char*)F4_DELETE_UP_sdram);
if(BmpJudge((Int32U)F4_DELETE_UP_sdram)==0)
FileFolderRead("bF4删除.bmp",(unsigned char*)F4_DELETE_UP_sdram);
FileFolderRead("F5++.bmp",(unsigned char*)F5_ADD_UP_sdram);
if(BmpJudge((Int32U)F5_ADD_UP_sdram)==0)
FileFolderRead("bF5++.bmp",(unsigned char*)F5_ADD_UP_sdram);
FileFolderRead("F6--.bmp",(unsigned char*)F6_SUB_UP_sdram);
if(BmpJudge((Int32U)F6_SUB_UP_sdram)==0)
FileFolderRead("bF6--.bmp",(unsigned char*)F6_SUB_UP_sdram);

// FileFolderRead("F5删除所有刀up.bmp",(unsigned char*)F5_DELETEALL_UP_sdram);
FileFolderRead("F1完成.bmp",(unsigned char*)F1_OK_UP_sdram);
if(BmpJudge((Int32U)F1_OK_UP_sdram)==0)
FileFolderRead("bF1完成.bmp",(unsigned char*)F1_OK_UP_sdram);
FileFolderRead("F2退出.bmp",(unsigned char*)F2_EXIT_UP_sdram);
if(BmpJudge((Int32U)F2_EXIT_UP_sdram)==0)
FileFolderRead("bF2退出.bmp",(unsigned char*)F2_EXIT_UP_sdram);
FileFolderRead("左右箭头up.bmp",(unsigned char*)L_R_ARROW_sdram);//
if(BmpJudge((Int32U)L_R_ARROW_sdram)==0)
FileFolderRead("b左右箭头up.bmp",(unsigned char*)L_R_ARROW_sdram);//
FileFolderRead("F2等分数up.bmp",(unsigned char*)F2_DIVNUM_UP_sdram);
if(BmpJudge((Int32U)F2_DIVNUM_UP_sdram)==0)
FileFolderRead("bF2等分数up.bmp",(unsigned char*)F2_DIVNUM_UP_sdram);
FileFolderRead("F2等分数down.bmp",(unsigned char*)F2_DIVNUM_DOWN_sdram);
if(BmpJudge((Int32U)F2_DIVNUM_DOWN_sdram)==0)
FileFolderRead("bF2等分数down.bmp",(unsigned char*)F2_DIVNUM_DOWN_sdram);
FileFolderRead("F3等分值up.bmp",(unsigned char*)F3_DIVDATA_UP_sdram);
if(BmpJudge((Int32U)F3_DIVDATA_UP_sdram)==0)
FileFolderRead("bF3等分值up.bmp",(unsigned char*)F3_DIVDATA_UP_sdram);
FileFolderRead("F3等分值down.bmp",(unsigned char*)F3_DIVDATA_DOWN_sdram);
if(BmpJudge((Int32U)F3_DIVDATA_DOWN_sdram)==0)
FileFolderRead("bF3等分值down.bmp",(unsigned char*)F3_DIVDATA_DOWN_sdram);
FileFolderRead("F4退出.bmp",(unsigned char*)F4_EXIT_UP_sdram);
if(BmpJudge((Int32U)F4_EXIT_UP_sdram)==0)
FileFolderRead("bF4退出.bmp",(unsigned char*)F4_EXIT_UP_sdram);
FileFolderRead("上箭头up.bmp",(unsigned char*)UP_ARROW_UP_sdram);//
if(BmpJudge((Int32U)UP_ARROW_UP_sdram)==0)
FileFolderRead("b上箭头up.bmp",(unsigned char*)UP_ARROW_UP_sdram);//
FileFolderRead("下箭头up.bmp",(unsigned char*)DOWN_ARROW_UP_sdram);//
if(BmpJudge((Int32U)DOWN_ARROW_UP_sdram)==0)
FileFolderRead("b下箭头up.bmp",(unsigned char*)DOWN_ARROW_UP_sdram);//
//查找子模式------
FileFolderRead("F1查看.bmp",(unsigned char*)F1_LOOK_UP_sdram);
if(BmpJudge((Int32U)F1_LOOK_UP_sdram)==0)
FileFolderRead("bF1查看.bmp",(unsigned char*)F1_LOOK_UP_sdram);
FileFolderRead("F2时间排序up.bmp",(unsigned char*)F2_BY_TIME_UP_sdram);
if(BmpJudge((Int32U)F2_BY_TIME_UP_sdram)==0)
FileFolderRead("bF2时间排序up.bmp",(unsigned char*)F2_BY_TIME_UP_sdram);
FileFolderRead("F2时间排序down.bmp",(unsigned char*)F2_BY_TIME_DOWN_sdram);
if(BmpJudge((Int32U)F2_BY_TIME_DOWN_sdram)==0)
FileFolderRead("bF2时间排序down.bmp",(unsigned char*)F2_BY_TIME_DOWN_sdram);
FileFolderRead("F3号码排序up.bmp",(unsigned char*)F3_BY_NUM_UP_sdram);
if(BmpJudge((Int32U)F3_BY_NUM_UP_sdram)==0)
FileFolderRead("bF3号码排序up.bmp",(unsigned char*)F3_BY_NUM_UP_sdram);
FileFolderRead("F3号码排序down.bmp",(unsigned char*)F3_BY_NUM_DOWN_sdram);
if(BmpJudge((Int32U)F3_BY_NUM_DOWN_sdram)==0)
FileFolderRead("bF3号码排序down.bmp",(unsigned char*)F3_BY_NUM_DOWN_sdram);
FileFolderRead("F4删除一个程序up.bmp",(unsigned char*)F4_DELETE_ONE_PRO_UP_sdram);
if(BmpJudge((Int32U)F4_DELETE_ONE_PRO_UP_sdram)==0)
FileFolderRead("bF4删除一个程序up.bmp",(unsigned char*)F4_DELETE_ONE_PRO_UP_sdram);
FileFolderRead("F5删除所有程序up.bmp",(unsigned char*)F5_DELETE_ALL_PRO_UP_sdram);
if(BmpJudge((Int32U)F5_DELETE_ALL_PRO_UP_sdram)==0)
FileFolderRead("bF5删除所有程序up.bmp",(unsigned char*)F5_DELETE_ALL_PRO_UP_sdram);

FileFolderRead("F1中文输入up.bmp",(unsigned char*)F1_PINYIN_UP_sdram);
if(BmpJudge((Int32U)F1_PINYIN_UP_sdram)==0)
FileFolderRead("bF1中文输入up.bmp",(unsigned char*)F1_PINYIN_UP_sdram);
FileFolderRead("F1中文输入down.bmp",(unsigned char*)F1_PINYIN_DOWN_sdram);
if(BmpJudge((Int32U)F1_PINYIN_DOWN_sdram)==0)
FileFolderRead("bF1中文输入down.bmp",(unsigned char*)F1_PINYIN_DOWN_sdram);
FileFolderRead("F2字母输入up.bmp",(unsigned char*)F2_CHAR_UP_sdram);
if(BmpJudge((Int32U)F2_CHAR_UP_sdram)==0)
FileFolderRead("bF2字母输入up.bmp",(unsigned char*)F2_CHAR_UP_sdram);
FileFolderRead("F2字母输入down.bmp",(unsigned char*)F2_CHAR_DOWN_sdram);
if(BmpJudge((Int32U)F2_CHAR_DOWN_sdram)==0)
FileFolderRead("bF2字母输入down.bmp",(unsigned char*)F2_CHAR_DOWN_sdram);
FileFolderRead("F3数字输入up.bmp",(unsigned char*)F3_NUM_UP_sdram);
if(BmpJudge((Int32U)F3_NUM_UP_sdram)==0)
FileFolderRead("bF3数字输入up.bmp",(unsigned char*)F3_NUM_UP_sdram);
FileFolderRead("F3数字输入down.bmp",(unsigned char*)F3_NUM_DOWN_sdram);
if(BmpJudge((Int32U)F3_NUM_DOWN_sdram)==0)
FileFolderRead("bF3数字输入down.bmp",(unsigned char*)F3_NUM_DOWN_sdram);
//-------
FileFolderRead("F1参数.bmp",(unsigned char*)F1_PARAMETER_sdram);
if(BmpJudge((Int32U)F1_PARAMETER_sdram)==0)
FileFolderRead("bF1参数.bmp",(unsigned char*)F1_PARAMETER_sdram);
FileFolderRead("F2基准.bmp",(unsigned char*)F2_RULER_sdram);
if(BmpJudge((Int32U)F2_RULER_sdram)==0)
FileFolderRead("bF2基准.bmp",(unsigned char*)F2_RULER_sdram);
FileFolderRead("F3时钟.bmp",(unsigned char*)F3_CLOCK_sdram);
if(BmpJudge((Int32U)F3_CLOCK_sdram)==0)
FileFolderRead("bF3时钟.bmp",(unsigned char*)F3_CLOCK_sdram);
FileFolderRead("F4wheel0.bmp",(unsigned char*)F4_WHEEL0_sdram);
if(BmpJudge((Int32U)F4_WHEEL0_sdram)==0)
FileFolderRead("bF4wheel0.bmp",(unsigned char*)F4_WHEEL0_sdram);
FileFolderRead("F4wheel1.bmp",(unsigned char*)F4_WHEEL1_sdram);
if(BmpJudge((Int32U)F4_WHEEL1_sdram)==0)
FileFolderRead("bF4wheel1.bmp",(unsigned char*)F4_WHEEL1_sdram);
FileFolderRead("F5脉冲当量up.bmp",(unsigned char*)F5_PULSE_UP_sdram);
if(BmpJudge((Int32U)F5_PULSE_UP_sdram)==0)
FileFolderRead("bF5脉冲当量up.bmp",(unsigned char*)F5_PULSE_UP_sdram);
FileFolderRead("F6测试IO.bmp",(unsigned char*)F6_TST_IO_sdram);
if(BmpJudge((Int32U)F6_TST_IO_sdram)==0)
FileFolderRead("bF6测试IO.bmp",(unsigned char*)F6_TST_IO_sdram);


//------------------------------flag pic
FileFolderRead("红刀flag.bmp",(unsigned char*)RED_KNIFE_F_sdram);//
if(BmpJudge((Int32U)RED_KNIFE_F_sdram)==0)
FileFolderRead("b红刀flag.bmp",(unsigned char*)RED_KNIFE_F_sdram);//
FileFolderRead("推纸flag.bmp",(unsigned char*)PUSH_PAPER_F_sdram);//
if(BmpJudge((Int32U)PUSH_PAPER_F_sdram)==0)
FileFolderRead("b推纸flag.bmp",(unsigned char*)PUSH_PAPER_F_sdram);//
FileFolderRead("理纸flag.bmp",(unsigned char*)SORT_PAPER_F_sdram);//
if(BmpJudge((Int32U)SORT_PAPER_F_sdram)==0)
FileFolderRead("b理纸flag.bmp",(unsigned char*)SORT_PAPER_F_sdram);//
FileFolderRead("压纸flag.bmp",(unsigned char*)PRE_PAPER_F_sdram);//
if(BmpJudge((Int32U)PRE_PAPER_F_sdram)==0)
FileFolderRead("b压纸flag.bmp",(unsigned char*)PRE_PAPER_F_sdram);//
FileFolderRead("气垫flag.bmp",(unsigned char*)AIR_BED_F_sdram);//
if(BmpJudge((Int32U)AIR_BED_F_sdram)==0)
FileFolderRead("b气垫flag.bmp",(unsigned char*)AIR_BED_F_sdram);//
//------------------------------flag button
FileFolderRead("气垫按钮.bmp",(unsigned char*)AIR_BED_BUTT_sdram);//
if(BmpJudge((Int32U)AIR_BED_BUTT_sdram)==0)
FileFolderRead("b气垫按钮.bmp",(unsigned char*)AIR_BED_BUTT_sdram);//
FileFolderRead("压纸按钮.bmp",(unsigned char*)PRE_PAPER_BUTT_sdram);//
if(BmpJudge((Int32U)PRE_PAPER_BUTT_sdram)==0)
FileFolderRead("b压纸按钮.bmp",(unsigned char*)PRE_PAPER_BUTT_sdram);//
FileFolderRead("理纸按钮.bmp",(unsigned char*)SORT_PAPER_BUTT_sdram);//
if(BmpJudge((Int32U)SORT_PAPER_BUTT_sdram)==0)
FileFolderRead("b理纸按钮.bmp",(unsigned char*)SORT_PAPER_BUTT_sdram);//
FileFolderRead("推纸按钮.bmp",(unsigned char*)PUSH_PAPER_BUTT_sdram);//
if(BmpJudge((Int32U)PUSH_PAPER_BUTT_sdram)==0)
FileFolderRead("b推纸按钮.bmp",(unsigned char*)PUSH_PAPER_BUTT_sdram);//
FileFolderRead("红刀按钮.bmp",(unsigned char*)RED_KNIFE_BUTT_sdram);//
if(BmpJudge((Int32U)RED_KNIFE_BUTT_sdram)==0)
FileFolderRead("b红刀按钮.bmp",(unsigned char*)RED_KNIFE_BUTT_sdram);//
FileFolderRead("批量刀按钮.bmp",(unsigned char*)ALL_KNIFE_BUTT_sdram);//
if(BmpJudge((Int32U)ALL_KNIFE_BUTT_sdram)==0)
FileFolderRead("b批量刀按钮.bmp",(unsigned char*)ALL_KNIFE_BUTT_sdram);//
// FileFolderRead("F6退出.bmp",(unsigned char*)F6_EXIT_BUTT_sdram);//
FileFolderRead("确定up.bmp",(unsigned char*)ENTER_BUTT_sdram);	//ok
if(BmpJudge((Int32U)ENTER_BUTT_sdram)==0)
FileFolderRead("b确定up.bmp",(unsigned char*)ENTER_BUTT_sdram);	//ok
//------------------------------F1,2,3...sub-mode pic
switch(Language)
	{
	case CHN_HAN:
		FileFolderRead("标签模式pic.bmp",(unsigned char*)F1_LABEL_MOD_PIC_sdram);
		if(BmpJudge((Int32U)F1_LABEL_MOD_PIC_sdram)==0)
		FileFolderRead("b标签模式pic.bmp",(unsigned char*)F1_LABEL_MOD_PIC_sdram);
		FileFolderRead("等分数模式pic.bmp",(unsigned char*)F2_DIVIDE_MOD_PIC1_sdram);
		if(BmpJudge((Int32U)F2_DIVIDE_MOD_PIC1_sdram)==0)
		FileFolderRead("b等分数模式pic.bmp",(unsigned char*)F2_DIVIDE_MOD_PIC1_sdram);
		FileFolderRead("等分值模式pic.bmp",(unsigned char*)F3_DIVIDE_MOD_PIC2_sdram);
		if(BmpJudge((Int32U)F3_DIVIDE_MOD_PIC2_sdram)==0)
		FileFolderRead("b等分值模式pic.bmp",(unsigned char*)F3_DIVIDE_MOD_PIC2_sdram);
		FileFolderRead("基准模式pic.bmp",(unsigned char*)F1_RULER_MOD_PIC_sdram);
		if(BmpJudge((Int32U)F1_RULER_MOD_PIC_sdram)==0)
		FileFolderRead("b基准模式pic.bmp",(unsigned char*)F1_RULER_MOD_PIC_sdram);
		break;
	default:
		FileFolderRead("标签模式picEN.bmp",(unsigned char*)F1_LABEL_MOD_PIC_sdram);
		if(BmpJudge((Int32U)F1_LABEL_MOD_PIC_sdram)==0)
		FileFolderRead("b标签模式picEN.bmp",(unsigned char*)F1_LABEL_MOD_PIC_sdram);
		FileFolderRead("等分数模式picEN.bmp",(unsigned char*)F2_DIVIDE_MOD_PIC1_sdram);
		if(BmpJudge((Int32U)F2_DIVIDE_MOD_PIC1_sdram)==0)
		FileFolderRead("b等分数模式picEN.bmp",(unsigned char*)F2_DIVIDE_MOD_PIC1_sdram);
		FileFolderRead("等分值模式picEN.bmp",(unsigned char*)F3_DIVIDE_MOD_PIC2_sdram);
		if(BmpJudge((Int32U)F3_DIVIDE_MOD_PIC2_sdram)==0)
		FileFolderRead("b等分值模式picEN.bmp",(unsigned char*)F3_DIVIDE_MOD_PIC2_sdram);
		FileFolderRead("基准模式picEN.bmp",(unsigned char*)F1_RULER_MOD_PIC_sdram);
		if(BmpJudge((Int32U)F1_RULER_MOD_PIC_sdram)==0)
		FileFolderRead("b基准模式picEN.bmp",(unsigned char*)F1_RULER_MOD_PIC_sdram);
		break;
	}	
FileFolderRead("参数模式pic.bmp",(unsigned char*)F2_DATAS_MOD_PIC_sdram);
if(BmpJudge((Int32U)F2_DATAS_MOD_PIC_sdram)==0)
FileFolderRead("b参数模式pic.bmp",(unsigned char*)F2_DATAS_MOD_PIC_sdram);
FileFolderRead("时钟模式pic.bmp",(unsigned char*)F3_CLOCK_MOD_PIC_sdram);
if(BmpJudge((Int32U)F3_CLOCK_MOD_PIC_sdram)==0)
FileFolderRead("b时钟模式pic.bmp",(unsigned char*)F3_CLOCK_MOD_PIC_sdram);
FileFolderRead("密码模式pic.bmp",(unsigned char*)PASSWORD_MOD_PIC_sdram);
if(BmpJudge((Int32U)PASSWORD_MOD_PIC_sdram)==0)
FileFolderRead("b密码模式pic.bmp",(unsigned char*)PASSWORD_MOD_PIC_sdram);

FileFolderRead("列表模式pic.bmp",(unsigned char*)MAIN_TABLE_PIC_sdram);
if(BmpJudge((Int32U)MAIN_TABLE_PIC_sdram)==0)
FileFolderRead("b列表模式pic.bmp",(unsigned char*)MAIN_TABLE_PIC_sdram);
FileFolderRead("机器图.bmp",(unsigned char*)MACHINE_PIC_sdram);
if(BmpJudge((Int32U)MACHINE_PIC_sdram)==0)
FileFolderRead("b机器图.bmp",(unsigned char*)MACHINE_PIC_sdram);

//--------
FileFolderRead("运行up.bmp",(unsigned char*)RUN_BUTT_sdram);//
if(BmpJudge((Int32U)RUN_BUTT_sdram)==0)
FileFolderRead("b运行up.bmp",(unsigned char*)RUN_BUTT_sdram);//
FileFolderRead("停止up.bmp",(unsigned char*)STOP_UP_sdram);
if(BmpJudge((Int32U)STOP_UP_sdram)==0)
FileFolderRead("b停止up.bmp",(unsigned char*)STOP_UP_sdram);
// FileFolderRead("上档键up.bmp",(unsigned char*)SHIFT_BUTT_UP_sdram);//
// FileFolderRead("上档键down.bmp",(unsigned char*)SHIFT_BUTT_DOWN_sdram);//
FileFolderRead("进.bmp",(unsigned char*)FRONT_PAGE_UP_sdram);//
if(BmpJudge((Int32U)FRONT_PAGE_UP_sdram)==0)
FileFolderRead("b进.bmp",(unsigned char*)FRONT_PAGE_UP_sdram);//
FileFolderRead("退.bmp",(unsigned char*)BACK_PAGE_UP_sdram);//
if(BmpJudge((Int32U)BACK_PAGE_UP_sdram)==0)
FileFolderRead("b退.bmp",(unsigned char*)BACK_PAGE_UP_sdram);//
FileFolderRead("快进.bmp",(unsigned char*)FAST_FORWD_UP_sdram);
FileFolderRead("快退.bmp",(unsigned char*)FAST_BACK_UP_sdram);


// FileFolderRead("F4wheel0.bmp",(unsigned char*)F4_WHEEL0_sdram);//
// FileFolderRead("F4wheel1.bmp",(unsigned char*)F4_WHEEL1_sdram);//
// FileFolderRead("F5wheel0.bmp",(unsigned char*)F5_WHEEL0_sdram);//
// FileFolderRead("F5wheel1.bmp",(unsigned char*)F5_WHEEL1_sdram);//
FileFolderRead("S6amend_off.bmp",(unsigned char*)DATA_AMEND0_sdram);//
if(BmpJudge((Int32U)DATA_AMEND0_sdram)==0)
FileFolderRead("bS6amend_off.bmp",(unsigned char*)DATA_AMEND0_sdram);//
FileFolderRead("S6amend_on.bmp",(unsigned char*)DATA_AMEND1_sdram);//
if(BmpJudge((Int32U)DATA_AMEND1_sdram)==0)
FileFolderRead("bS6amend_on.bmp",(unsigned char*)DATA_AMEND1_sdram);//

FileFolderRead("全删up.bmp",(unsigned char*)DELETE_ALL_UP_sdram);//
if(BmpJudge((Int32U)DELETE_ALL_UP_sdram)==0)
FileFolderRead("b全删up.bmp",(unsigned char*)DELETE_ALL_UP_sdram);//

//-----计算器图标--
FileFolderRead("计算器win.bmp",(unsigned char*)CAL_WIND_sdram);
//-------up
FileFolderRead("cal-0.bmp",(unsigned char*)CAL_0_UP_sdram);
FileFolderRead("cal-1.bmp",(unsigned char*)CAL_1_UP_sdram);
FileFolderRead("cal-2.bmp",(unsigned char*)CAL_2_UP_sdram);
FileFolderRead("cal-3.bmp",(unsigned char*)CAL_3_UP_sdram);
FileFolderRead("cal-4.bmp",(unsigned char*)CAL_4_UP_sdram);
FileFolderRead("cal-5.bmp",(unsigned char*)CAL_5_UP_sdram);
FileFolderRead("cal-6.bmp",(unsigned char*)CAL_6_UP_sdram);
FileFolderRead("cal-7.bmp",(unsigned char*)CAL_7_UP_sdram);
FileFolderRead("cal-8.bmp",(unsigned char*)CAL_8_UP_sdram);
FileFolderRead("cal-9.bmp",(unsigned char*)CAL_9_UP_sdram);
FileFolderRead("cal-clr.bmp",(unsigned char*)CAL_CLR_UP_sdram);
FileFolderRead("cal-dot.bmp",(unsigned char*)CAL_DOT_UP_sdram);
FileFolderRead("cal-add.bmp",(unsigned char*)CAL_ADD_UP_sdram);
FileFolderRead("cal-sub.bmp",(unsigned char*)CAL_SUB_UP_sdram);
FileFolderRead("cal-mul.bmp",(unsigned char*)CAL_MUL_UP_sdram);
FileFolderRead("cal-div.bmp",(unsigned char*)CAL_DIV_UP_sdram);
FileFolderRead("cal-equ.bmp",(unsigned char*)CAL_EQU_UP_sdram);
FileFolderRead("cal-ok.bmp",(unsigned char*)CAL_OK_UP_sdram);
//-------down
FileFolderRead("cal-0_down.bmp",(unsigned char*)CAL_0_DOWN_sdram);
FileFolderRead("cal-1_down.bmp",(unsigned char*)CAL_1_DOWN_sdram);
FileFolderRead("cal-2_down.bmp",(unsigned char*)CAL_2_DOWN_sdram);
FileFolderRead("cal-3_down.bmp",(unsigned char*)CAL_3_DOWN_sdram);
FileFolderRead("cal-4_down.bmp",(unsigned char*)CAL_4_DOWN_sdram);
FileFolderRead("cal-5_down.bmp",(unsigned char*)CAL_5_DOWN_sdram);
FileFolderRead("cal-6_down.bmp",(unsigned char*)CAL_6_DOWN_sdram);
FileFolderRead("cal-7_down.bmp",(unsigned char*)CAL_7_DOWN_sdram);
FileFolderRead("cal-8_down.bmp",(unsigned char*)CAL_8_DOWN_sdram);
FileFolderRead("cal-9_down.bmp",(unsigned char*)CAL_9_DOWN_sdram);
FileFolderRead("cal-clr_down.bmp",(unsigned char*)CAL_CLR_DOWN_sdram);
FileFolderRead("cal-dot_down.bmp",(unsigned char*)CAL_DOT_DOWN_sdram);
FileFolderRead("cal-add_down.bmp",(unsigned char*)CAL_ADD_DOWN_sdram);
FileFolderRead("cal-sub_down.bmp",(unsigned char*)CAL_SUB_DOWN_sdram);
FileFolderRead("cal-mul_down.bmp",(unsigned char*)CAL_MUL_DOWN_sdram);
FileFolderRead("cal-div_down.bmp",(unsigned char*)CAL_DIV_DOWN_sdram);
FileFolderRead("cal-equ_down.bmp",(unsigned char*)CAL_EQU_DOWN_sdram);
FileFolderRead("cal-ok_down.bmp",(unsigned char*)CAL_OK_DOWN_sdram);

//--add flags
FileFolderRead("标记wind.bmp",(unsigned char*)ALL_FLAGS_WIN_sdram);//标记wind
FileFolderRead("otherflags.bmp",(unsigned char*)OTHER_SET_F_sdram);//标记符号
FileFolderRead("气垫无flag.bmp",(unsigned char*)NO_AIR_BED_F_sdram);//无气垫标记号
}

void StartPic_dis(void)//开机画面显示
{
Int32U i;
/*
pInt32U source_Ptr=(pInt32U)malloc(1024);
for(volatile Int32U i=0;i<256;i++)	//1k
	{
	source_Ptr[i]=0xffffffff;
	}
for(volatile Int32U i=0;i<24*1024;i++)//24k
	{
	pInt32U dest_Ptr=(pInt32U)(df_zk_sdram+i*1024);//           0xa0600000  //字库2M
	memcpy(dest_Ptr,source_Ptr,1024);
	}
free(source_Ptr);
*/
pInt32U dest_Ptr=(pInt32U)df_zk_sdram;//           0xa0600000  //字库2M
for(i=0;i<10*1024*256;i++)//24k
	{
	*dest_Ptr++=0xffffffff;
	}

FileRead("字库_0x20000.FON",(unsigned char *)df_zk_sdram);//
Printf16("Copyright(c)lwcumt-ver.202003,All Rights Reserved.",10,10,RED_COLOR,0,0xffff);
FileFolderRead("鸭梨.bmp",(unsigned char*)PEAR_sdram);//
switch(Language)
	{
	case CHN_HAN:
		Printf24("电脑自检，数据加载.....需要6秒，请稍等！",COMPUTER_TEST_HINT_X,COMPUTER_TEST_HINT_Y,RED_COLOR,1,0xffff);
			break;
	case ENGLISH:	
		Printf24("Computer is self-checking,loading data....",COMPUTER_TEST_HINT_X,COMPUTER_TEST_HINT_Y-100,RED_COLOR,1,0xffff);
		Printf24("Please wait 6 seconds!",COMPUTER_TEST_HINT_X,COMPUTER_TEST_HINT_Y,RED_COLOR,1,0xffff);
			break;
	case INDONSIA:	//印尼
		Printf24("Self test komputer, loading data....",COMPUTER_TEST_HINT_X,COMPUTER_TEST_HINT_Y-100,RED_COLOR,1,0xffff);
		Printf24("Silahkan tunggu 6 detik!",COMPUTER_TEST_HINT_X,COMPUTER_TEST_HINT_Y,RED_COLOR,1,0xffff);
			break;
	case PORTUGAL:	//葡萄牙
		Printf24("computador de autoteste,carregamento....",COMPUTER_TEST_HINT_X,COMPUTER_TEST_HINT_Y-100,RED_COLOR,1,0xffff);
		Printf24("Por favor, aguarde seis segundo!",COMPUTER_TEST_HINT_X,COMPUTER_TEST_HINT_Y,RED_COLOR,1,0xffff);
			break;
	case SPANISH: //西班牙
		Printf24("Computer autotest,los datos se cargan....",COMPUTER_TEST_HINT_X,COMPUTER_TEST_HINT_Y-100,RED_COLOR,1,0xffff);
		Printf24("Por favor, espere 6 segundos!",COMPUTER_TEST_HINT_X,COMPUTER_TEST_HINT_Y,RED_COLOR,1,0xffff);
			break;
	}
	//=++++++++++++++++202003增加
Printf32("欢迎使用玉丰机械！",10,50,RED_COLOR,0,0xffff);

//FileFolderRead("开机画面.bmp",(unsigned char*)START_PIC_sdram);//读开机画面
Pear_dis(PEAR_X, PEAR_Y);//鸭梨
ReadFiles();  //读取 图标文件
Bmp_Decode((Int32U)START_PIC_sdram, 0, 0, (pInt16U)SDRAM0_BASE_ADDR); //显示开机画面

RLOUT1_OFF;  RLOUT1_1_OFF;  // 允许裁切
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

//*************************模式  名  显示***************
void ModeName_dis(Int16U mode)//各模式 name+++++++++++
{
//Bmp_Decode((Int32U)PROGRAM_MOD_sdram, x, y, (pInt16U)SDRAM0_BASE_ADDR);
Int16U x,y,back_color,line_color;
//.........................解释 框
back_color=MODE_NAME_COLOR,	line_color=YELLOW_COLOR;  //模式解释 框
GLCD_SetWindow_Fill(MODE_NAME_X1,MODE_NAME_Y1,MODE_NAME_X2,MODE_NAME_Y2,back_color,back_color);
x=MODE_NAME_X1+2;y=MODE_NAME_Y1+0;
switch(mode)
	{
	case READ_PRO_MODE://查找模式
		switch(Language)
			{
			case CHN_HAN:
				x+=12*5;
				Printf24("查找模式",x,y,line_color,1,back_color);
					break;
			case ENGLISH:
			case INDONSIA:	//印尼
			case PORTUGAL:	//葡萄牙
			case SPANISH: //西班牙
				x+=12*5;
				Printf24("Find mode",x,y,line_color,1,back_color);
					break;
			}
			break;
	case AUTO_MODE:
		switch(Language)
			{
			case CHN_HAN:
				x+=12*5;
				Printf24("自动模式",x,y,line_color,1,back_color);
					break;
			case ENGLISH:
				x+=12*5;
				Printf24("Auto mode",x,y,line_color,1,back_color);
					break;
			case INDONSIA:	//印尼
				x+=12*2;
				Printf24("Mode otomatis",x,y,line_color,1,back_color);
					break;
			case PORTUGAL:	//葡萄牙
				// x+=12*2;
				Printf24("O modo automá   ",x,y,line_color,1,back_color);
				Printf24("             tico",x,y,line_color,0,back_color);//automático
					break;
			case SPANISH: //西班牙
				Printf24("El modo automá   ",x,y,line_color,1,back_color);
				Printf24("              tico",x,y,line_color,0,back_color);//automático
					break;
			}
			break;	
	case MANUAL_MODE:
		switch(Language)
			{
			case CHN_HAN:
				x+=12*5;
				Printf24("手动模式",x,y,line_color,1,back_color);
					break;
			case ENGLISH:
				x+=12*3;	
				Printf24("Manual mode",x,y,line_color,1,back_color);
					break;
			case INDONSIA:	//印尼
				x+=12*3;		
				Printf24("Mode manual",x,y,line_color,1,back_color);
					break;
			case PORTUGAL:	//葡萄牙
				x+=12*2;		
				Printf24("modo manual",x,y,line_color,1,back_color);
					break;
			case SPANISH: //西班牙
				// x+=12*2;		
				Printf24("El modo manual",x,y,line_color,1,back_color);
					break;
			}	
			break;	
	case TEACH_MODE:
		switch(Language)
			{
			case CHN_HAN:
				x+=12*5;
				Printf24("示教模式",x,y,line_color,1,back_color);
					break;
			case ENGLISH:
				x+=12*5;
				Printf24("Teach mode",x,y,line_color,1,back_color);
					break;
			case INDONSIA:	//印尼	
				x+=12*2;
				Printf24("Mode ajarkan",x,y,line_color,1,back_color);
					break;
			case PORTUGAL:	//葡萄牙
				x+=12*2;		
				Printf24("Modo Teach",x,y,line_color,1,back_color);
					break;
			case SPANISH: //西班牙
				x+=12*2;		
				Printf24("Modo Teach",x,y,line_color,1,back_color);
					break;
			}
			break;
	case SELF_CUT_MODE:
		switch(Language)
			{
			case CHN_HAN:
				x+=12*5;
				Printf24("自刀模式",x,y,line_color,1,back_color);
					break;
			case ENGLISH:	
				x+=12*3;
				Printf24("Auto-Cut mode",x,y,line_color,1,back_color);
					break;
			case INDONSIA:	//印尼		
				Printf24("Mode Pemoton-Otomat",x,y,line_color,1,back_color);
					break;
			case PORTUGAL:	//葡萄牙
				// x+=12*2;		
				Printf24("Modo Cortar Auto",x,y,line_color,1,back_color);
					break;
			case SPANISH: //西班牙	
				Printf24("corte automá ",x,y,line_color,1,back_color);
				Printf24("            tico",x,y,line_color,0,back_color);//automático
					break;
			}	
			break;
	case HELP_MODE:
		switch(Language)
			{
			case CHN_HAN:
				x+=12*5;
				Printf24("帮助模式",x,y,line_color,1,back_color);
					break;
			case ENGLISH:
				x+=12*5;	
				Printf24("Help mode",x,y,line_color,1,back_color);
					break;
			case INDONSIA:	//印尼
				x+=12*2;
				Printf24("Bantuan Mode",x,y,line_color,1,back_color);
					break;
			case PORTUGAL:	//葡萄牙
				x+=12*2;		
				Printf24("Modo de Ajuda",x,y,line_color,1,back_color);
					break;
			case SPANISH: //西班牙
				//x+=12*2;		
				Printf24("el modo de ayuda",x,y,line_color,1,back_color);
					break;	
			}	
			break;
	//--------------------------------------------------------------------		
	case AUTO_LABEL_MODE:
	case TEACH_LABEL_MODE:
		switch(Language)
			{
			case CHN_HAN:
				x+=12*5;
				Printf24("标签模式",x,y,line_color,1,back_color);
					break;
			case ENGLISH:
				x+=12*4;	
				Printf24("Label mode",x,y,line_color,1,back_color);
					break;
			case INDONSIA:	//印尼	
				x+=12*5;
				Printf24("Tag Modus",x,y,line_color,1,back_color);
					break;
			case PORTUGAL:	//葡萄牙
				// x+=12*2;		
				Printf24("O modo etiqueta",x,y,line_color,1,back_color);
					break;
			case SPANISH: //西班牙	
				Printf24("modo de Label",x,y,line_color,1,back_color);
					break;
			}	
			break;
	case AUTO_DIVIDE_MODE:
	case TEACH_DIVIDE_MODE:
		switch(Language)
			{
			case CHN_HAN:
				x+=12*5;
				Printf24("等分模式",x,y,line_color,1,back_color);
					break;
			case ENGLISH:
				x+=12*4;	
				Printf24("Divide mode",x,y,line_color,1,back_color);
					break;
			case INDONSIA:	//印尼
				x+=12*2;	
				Printf24("Modus aliquots",x,y,line_color,1,back_color);
					break;
			case PORTUGAL:	//葡萄牙
				// x+=12*2;		
				Printf24("modo de Alí",x,y,line_color,1,back_color); // Alíquotas
				Printf24("quotas",x+(11*12),y,line_color,1,back_color);
					break;
			case SPANISH: //西班牙
				Printf24("modo de alícuotas",x,y,line_color,1,back_color);
					break;
			}	
			break;
	// // case TEACH_PRO_MODE:
		// // switch(Language)
			// // {
			// // case CHN_HAN:
				// // x+=12*5;
				// // Printf24("程序模式",x,y,line_color,1,back_color);
					// // break;
			// // case ENGLISH:
				// // x+=12*3;	
				// // Printf24("Procedure mode",x,y,line_color,1,back_color);
					// // break;
			// // case INDONSIA:	//印尼	
				// // x+=12*3;	
				// // Printf24("Mode Program",x,y,line_color,1,back_color);
					// // break;
			// // case PORTUGAL:	//葡萄牙
				// // // x+=12*2;		
				// // Printf24("Modo de Programa",x,y,line_color,1,back_color);
					// // break;
			// // case SPANISH: //西班牙	
				// // x+=12*3;	
				// // Printf24("Modo Programa",x,y,line_color,1,back_color);
					// // break;
			// // }	
			break;
	case READ_PRO_MESS_MODE:
	// // case TEACH_PRO_MESS_MODE:
		switch(Language)
			{
			case CHN_HAN:
				x+=12*3;	
				Printf24("程序名模式",x,y,line_color,1,back_color);
					break;
			case ENGLISH:
				x+=12*3;		
				Printf24("Pro-Name mode",x,y,line_color,1,back_color);
					break;
			case INDONSIA:	//印尼	
				Printf24("Mode nama-Program",x,y,line_color,1,back_color);
					break;
			case PORTUGAL:	//葡萄牙
				// x+=12*2;		
				Printf24("nome do programa",x,y,line_color,1,back_color);
					break;
			case SPANISH: //西班牙	
				Printf24("nombre del programa",x,y,line_color,1,back_color);
					break;	
			}	
			break;
	case AUTO_FLAG_MODE:
	case TEACH_FLAG_MODE:
		switch(Language)
			{
			case CHN_HAN:
				x+=12*2;	
				Printf24("标记设定模式",x,y,line_color,1,back_color);
					break;
			case ENGLISH:	
				x+=12*2;	
				Printf24("Set Marker mode",x,y,line_color,1,back_color);
					break;
			case INDONSIA:	//印尼	
				Printf24("Tandai-Pengatu mode",x,y,line_color,1,back_color);
					break;
			case PORTUGAL:	//葡萄牙
				// x+=12*2;		
				Printf24("Modo Mark Set",x,y,line_color,1,back_color);
					break;
			case SPANISH: //西班牙	
				Printf24("Modo Marcos Set",x,y,line_color,1,back_color);
					break;
			}	
			break;
	// // case AUTO_RULER_MODE:
	case MANUAL_RULER_MODE:
	// // case SELF_RULER_MODE:
		switch(Language)
			{
			case CHN_HAN:
				x+=12*5;	
				Printf24("基准模式",x,y,line_color,1,back_color);
					break;
			case ENGLISH:	
				x+=12*2;	
				Printf24("Reference mode",x,y,line_color,1,back_color);
					break;
			case INDONSIA:	//印尼
				// x+=12*2;		
				Printf24("Modus referensi",x,y,line_color,1,back_color);
					break;
			case PORTUGAL:	//葡萄牙
				// x+=12*2;		
				Printf24("modo Referê   ",x,y,line_color,1,back_color);	//Referência
				Printf24("           ncia",x,y,line_color,0,back_color);
					break;
			case SPANISH: //西班牙	
				Printf24("Referencia Modo",x,y,line_color,1,back_color);
					break;
			}
			break;
	// // case AUTO_TOOLS_MODE:
	case MANUAL_TOOLS_MODE:
	// // case SELF_TOOLS_MODE:
		switch(Language)
			{
			case CHN_HAN:
				x+=12*5;	
				Printf24("参数模式",x,y,line_color,1,back_color);
					break;
			case ENGLISH:	
				x+=12*2;	
				Printf24("Parameter mode",x,y,line_color,1,back_color);
					break;
			case INDONSIA:	//印尼	
				// x+=12*2;	
				Printf24("Modus parameter",x,y,line_color,1,back_color);
					break;
			case PORTUGAL:	//葡萄牙
				// x+=12*2;		
				Printf24("modo Par metros",x,y,line_color,1,back_color);	//Parametros
				ASCII_Printf("a",ASCII24_MODE,12,24,PUTAO_ZK24_XOR, x+(8*12),y,line_color,back_color);
					break;
			case SPANISH: //西班牙
				Printf24("modo de Pará  ",x,y,line_color,1,back_color);
				Printf24("            metros",x,y,line_color,0,back_color);//Parámetros
					break;
			}	
			break;
	case AUTO_PLUS_MODE:
	case TEACH_PLUS_MODE:
		switch(Language)
			{
			case CHN_HAN:
				x+=12*5;	
				Printf24("自加模式",x,y,line_color,1,back_color);
					break;
			case ENGLISH:	
				x+=12*3;	
				Printf24("Auto-Add mode",x,y,line_color,1,back_color);
					break;
			case INDONSIA:	//印尼
				x+=12*2;		
				Printf24("Modus meningkat",x,y,line_color,1,back_color);
					break;
			case PORTUGAL:	//葡萄牙
				x+=12*2;		
				Printf24("modo add Batch",x,y,line_color,1,back_color);	//
					break;
			case SPANISH: //西班牙
				x+=12*2;		
				Printf24("modo por lotes",x,y,line_color,1,back_color);	//
					break;
			}	
			break;
	case AUTO_MINUS_MODE:
	case TEACH_MINUS_MODE:
		switch(Language)
			{
			case CHN_HAN:
				x+=12*5;	
				Printf24("自减模式",x,y,line_color,1,back_color);
					break;
			case ENGLISH:	
				x+=12*3;	
				Printf24("Auto-Sub mode",x,y,line_color,1,back_color);
					break;
			case INDONSIA:	//印尼	
				x+=12*3;	
				Printf24("Modus kurang",x,y,line_color,1,back_color);
					break;
			case PORTUGAL:	//葡萄牙
				x+=12*2;		
				Printf24("modo Batch Menos",x,y,line_color,1,back_color);	//
					break;
			case SPANISH: //西班牙
				// x+=12*2;		
				Printf24("modo Menos lotes",x,y,line_color,1,back_color);	//
					break;
			}	
			break;
	case MANUAL_CLOCK_MODE:
		switch(Language)
			{
			case CHN_HAN:
				x+=12*5;	
				Printf24("时间模式",x,y,line_color,1,back_color);
					break;
			case ENGLISH:	
				x+=12*2;	
				Printf24("Calendar mode",x,y,line_color,1,back_color);
					break;
			case INDONSIA:	//印尼
				x+=12*2;		
				Printf24("Kalender Modus",x,y,line_color,1,back_color);
					break;
			case PORTUGAL:	//葡萄牙
				x+=12*2;		
				Printf24("Modo tempo",x,y,line_color,1,back_color);	//
					break;
			case SPANISH: //西班牙
				x+=12*2;		
				Printf24("modo de hora",x,y,line_color,1,back_color);	//
					break;
			}	
			break;
	case MANUAL_PULSE_MODE:  //设定脉冲当量
		switch(Language)
			{
			case CHN_HAN:
				x+=12*2;	
				Printf24("脉冲当量模式",x,y,line_color,1,back_color);
					break;
			case ENGLISH:
				x+=12*2;		
				Printf24("Pulse-Equ mode",x,y,line_color,1,back_color);
					break;
			case INDONSIA:	//印尼	
				Printf24("Mode Pulse setara",x,y,line_color,1,back_color);
					break;
			case PORTUGAL:	//葡萄牙
				// x+=12*2;		
				Printf24("pulso equivalente",x,y,line_color,1,back_color);	//
					break;
			case SPANISH: //西班牙
				// x+=12*2;		
				Printf24("equivalente pulso",x,y,line_color,1,back_color);	//
					break;
			}		
			break;
	case MANUAL_SERVO_C_MODE:	//直流伺服 C 参数
		switch(Language)
			{
			case CHN_HAN:
				x+=12*2;	
				Printf24("‘C’参数模式",x,y,line_color,1,back_color);
					break;
			case ENGLISH:	
				x+=12*2;	
				Printf24("Servo 'C' data ",x,y,line_color,1,back_color);
					break;
			case INDONSIA:	//印尼	
				Printf24("Mode 'C' parameter",x,y,line_color,1,back_color);
					break;
			case PORTUGAL:	//葡萄牙
				// x+=12*2;		
				Printf24("par metros Servo",x,y,line_color,1,back_color);	// Parametros
				ASCII_Printf("a",ASCII24_MODE,12,24,PUTAO_ZK24_XOR, x+(3*12),y,line_color,back_color);
					break;
			case SPANISH: //西班牙
				Printf24("pará ",x,y,line_color,1,back_color);
				Printf24("    metros servo C",x,y,line_color,0,back_color);//parámetros
					break;
			}	
			break;
	case MANUAL_PASS_MODE:  //密码
		switch(Language)
			{
			case CHN_HAN:
				x+=12*5;	
				Printf24("密码模式",x,y,line_color,1,back_color);
					break;
			case ENGLISH:
				x+=12*3;		
				Printf24("Password mode",x,y,line_color,1,back_color);
					break;
			case INDONSIA:	//印尼
				x+=12*2;		
				Printf24("Modus cipher",x,y,line_color,1,back_color);
					break;
			case PORTUGAL:	//葡萄牙
				// x+=12*2;		
				Printf24("modo de senha",x,y,line_color,1,back_color);	
					break;
			case SPANISH: //西班牙	
				Printf24("modo de contrase?a",x,y,line_color,1,back_color);
				ASCII_Printf("n",ASCII24_MODE,12,24,PUTAO_ZK24_XOR, x+(16*12),y,line_color,back_color);
					break;
			}	
			break;
	case MANUAL_IO_TEST_MODE:  //io测试模式
		switch(Language)
			{
			case CHN_HAN:
				x+=12*2;	
				Printf24("端口测试模式",x,y,line_color,1,back_color);
					break;
			case ENGLISH:
			case INDONSIA:	//印尼
			case PORTUGAL:	//葡萄牙
			case SPANISH: //西班牙	
				x+=12*2;	
				Printf24("IO test mode",x,y,line_color,1,back_color);
					break;
			}	
			break;		
	}
}

//==================================图片定义============================================
void Pear_dis(Int16U x, Int16U y)//鸭梨
{
Bmp_Decode((Int32U)PEAR_sdram, x, y, (pInt16U)SDRAM0_BASE_ADDR);
}
void MiddlePage_dis(void)//中间活页
{
Int16U x1,y1,x2,y2;
Int16U fill_color=TEXT_TAB_BACK_COLOR;

x1=MIDDLE_PAGE_X,y1=MIDDLE_PAGE_Y;//+20;
x2=x1+M_PAGE_WIDE-1,y2=MIDDLE_PAGE_Y+M_PAGE_HIGH-1;//320;
GLCD_SetWindow_Fill(x1,y1,x2,y2, fill_color,fill_color);// GLCD_SetWindow_Fill(x1,y1,x2,y2, 0,0);

// GLCD_SetWindow_Fill(SCHEDULE_X,SCHEDULE_Y,SCHEDULE_X+SCHEDULE_WIDE+0,SCHEDULE_Y+SCHEDULE_HIGH,fill_color,fill_color);  //覆盖 进度条
}
//-------------F1,2,3...mode fun pic
void F1LabelFunPic_dis(Int16U x, Int16U y)//F1标签模式pic
{
Bmp_Decode((Int32U)F1_LABEL_MOD_PIC_sdram, x, y, (pInt16U)SDRAM0_BASE_ADDR);
}
void F2DivideNumPic_dis(Int16U x, Int16U y)//F2等分数模式pic
{
Bmp_Decode((Int32U)F2_DIVIDE_MOD_PIC1_sdram, x, y, (pInt16U)SDRAM0_BASE_ADDR);
}
void F3DivideValuePic_dis(Int16U x, Int16U y)//F3等分值模式pic
{
Bmp_Decode((Int32U)F3_DIVIDE_MOD_PIC2_sdram, x, y, (pInt16U)SDRAM0_BASE_ADDR);
}
void F1RulerFunPic_dis(Int16U x, Int16U y)//F1基准模式pic
{
Bmp_Decode((Int32U)F1_RULER_MOD_PIC_sdram, x, y, (pInt16U)SDRAM0_BASE_ADDR);
}
void F2DatasFunPic_dis(Int16U x, Int16U y)//F2参数模式pic
{
Bmp_Decode((Int32U)F2_DATAS_MOD_PIC_sdram, x, y, (pInt16U)SDRAM0_BASE_ADDR);
}
void F3ClockFunPic_dis(Int16U x, Int16U y)//F3日历模式pic
{
Bmp_Decode((Int32U)F3_CLOCK_MOD_PIC_sdram, x, y, (pInt16U)SDRAM0_BASE_ADDR);
}
void PsswordFunPic_dis(Int16U x,Int16U y)//密码功能模式pic
{
Bmp_Decode((Int32U)PASSWORD_MOD_PIC_sdram, x, y, (pInt16U)SDRAM0_BASE_ADDR);
}
//-----***************主模式 5

void ManualIconUp_dis(Int16U x,Int16U y)//手动up
{
Bmp_Decode((Int32U)MANUAL_MOD_UP_sdram, x, y, (pInt16U)SDRAM0_BASE_ADDR);
}
void ManualIconDown_dis(Int16U x,Int16U y)//手动down
{
Bmp_Decode((Int32U)MANUAL_MOD_DOWN_sdram, x, y, (pInt16U)SDRAM0_BASE_ADDR);
}
void AutoIconUp_dis(Int16U x,Int16U y)//自动up
{
Bmp_Decode((Int32U)AUTO_MOD_UP_sdram, x, y, (pInt16U)SDRAM0_BASE_ADDR);
}
void AutoIconDown_dis(Int16U x,Int16U y)//自动down
{
Bmp_Decode((Int32U)AUTO_MOD_DOWN_sdram, x, y, (pInt16U)SDRAM0_BASE_ADDR);
}
void FindIconUp_dis(Int16U x,Int16U y)//find up
{
Bmp_Decode((Int32U)FIND_MOD_UP_sdram, x, y, (pInt16U)SDRAM0_BASE_ADDR);
}
void FindIconDown_dis(Int16U x,Int16U y)//find down
{
Bmp_Decode((Int32U)FIND_MOD_DOWN_sdram, x, y, (pInt16U)SDRAM0_BASE_ADDR);
}
void TeachModeButton_dis(Int16U x,Int16U y)//示教按钮
{
Bmp_Decode((Int32U)TEACH_MOD_BUTT_sdram, x, y, (pInt16U)SDRAM0_BASE_ADDR);	
}
void AutoCutMOdeButton_dis(Int16U x,Int16U y)//自刀按钮
{
Bmp_Decode((Int32U)AUTOCUT_MOD_BUTT_sdram, x, y, (pInt16U)SDRAM0_BASE_ADDR);	
}
///
void PushButton_dis(Int16U x,Int16U y)//推纸
{
Bmp_Decode((Int32U)PUSH_BUTT_sdram, x, y, (pInt16U)SDRAM0_BASE_ADDR);	
}

//------------------------------=====power ctrl==========

void PowerOnUp_dis(Int16U x,Int16U y)//电源绿up
{
Bmp_Decode((Int32U)POWER_ON_UP_sdram, x, y, (pInt16U)SDRAM0_BASE_ADDR);	
}
void PowerOnDown_dis(Int16U x,Int16U y)//电源绿down
{
Bmp_Decode((Int32U)POWER_ON_DOWN_sdram, x, y, (pInt16U)SDRAM0_BASE_ADDR);	
}
void PowerOffUp_dis(Int16U x,Int16U y)//电源红up
{
Bmp_Decode((Int32U)POWER_OFF_UP_sdram, x, y, (pInt16U)SDRAM0_BASE_ADDR);	
}
void PowerOffDown_dis(Int16U x,Int16U y)//电源红down
{
Bmp_Decode((Int32U)POWER_OFF_DOWN_sdram, x, y, (pInt16U)SDRAM0_BASE_ADDR);	
}
void PowerBlack_dis(Int16U x,Int16U y)//电源黑
{
Bmp_Decode((Int32U)POWER_CTRL_sdram, x, y, (pInt16U)SDRAM0_BASE_ADDR);	
}

void LightKnifeOn_dis(Int16U x,Int16U y)//对刀灯on
{
Bmp_Decode((Int32U)LIGHT_KNIFE_DOWN_sdram, x, y, (pInt16U)SDRAM0_BASE_ADDR);	
}
void LightKnifeOff_dis(Int16U x,Int16U y)//对刀灯off
{
Bmp_Decode((Int32U)LIGHT_KNIFE_UP_sdram, x, y, (pInt16U)SDRAM0_BASE_ADDR);	
}
void LightLEDOn_dis(Int16U x,Int16U y)//照明灯on
{
Bmp_Decode((Int32U)LIGHT_LED_DOWN_sdram, x, y, (pInt16U)SDRAM0_BASE_ADDR);	
}
void LightLEDOff_dis(Int16U x,Int16U y)//照明灯off
{
Bmp_Decode((Int32U)LIGHT_LED_UP_sdram, x, y, (pInt16U)SDRAM0_BASE_ADDR);	
}
void LightCtrl_dis(Int16U x,Int16U y)//灯0
{
Bmp_Decode((Int32U)LIGHT_CTRL_sdram, x, y, (pInt16U)SDRAM0_BASE_ADDR);	
}

void NormalKnifeUp_dis(Int16U x,Int16U y)//正常裁切up
{
Bmp_Decode((Int32U)NORMAL_KNIFE_UP_sdram, x, y, (pInt16U)SDRAM0_BASE_ADDR);	
}
void NormalKnifeDown_dis(Int16U x,Int16U y)//正常裁切down
{
Bmp_Decode((Int32U)NORMAL_KNIFE_DOWN_sdram, x, y, (pInt16U)SDRAM0_BASE_ADDR);	
}
void ElectricKnifeUp_dis(Int16U x,Int16U y)//电动换刀up
{
Bmp_Decode((Int32U)ELECTRIC_KNIFE_UP_sdram, x, y, (pInt16U)SDRAM0_BASE_ADDR);	
}
void ElectricKnifeDown_dis(Int16U x,Int16U y)//电动换刀
{
Bmp_Decode((Int32U)ELECTRIC_KNIFE_DOWN_sdram, x, y, (pInt16U)SDRAM0_BASE_ADDR);	
}
void ManualKnifeUp_dis(Int16U x,Int16U y)//手动换刀up
{
Bmp_Decode((Int32U)MANUAL_KNIFE_UP_sdram, x, y, (pInt16U)SDRAM0_BASE_ADDR);	
}
void ManualKnifeDown_dis(Int16U x,Int16U y)//手动换刀
{
Bmp_Decode((Int32U)MANUAL_KNIFE_DOWN_sdram, x, y, (pInt16U)SDRAM0_BASE_ADDR);	
}
void PumpOff_dis(Int16U x,Int16U y)//风泵 关up
{
Bmp_Decode((Int32U)PUMP_OFF_UP_sdram, x, y, (pInt16U)SDRAM0_BASE_ADDR);	
}
void PumpOn_dis(Int16U x,Int16U y)//风泵 开up
{
Bmp_Decode((Int32U)PUMP_ON_UP_sdram, x, y, (pInt16U)SDRAM0_BASE_ADDR);	
}


//*****************F1,F2,F3,....Icon
void F1LabelIconUp_dis(Int16U x,Int16U y)//F1标签up
{
Bmp_Decode((Int32U)F1_LABELS_UP_sdram, x, y, (pInt16U)SDRAM0_BASE_ADDR);
}
void F2DivideIconUp_dis(Int16U x,Int16U y)//F2等分up
{
Bmp_Decode((Int32U)F2_DIVIDE_UP_sdram, x, y, (pInt16U)SDRAM0_BASE_ADDR);
}
void F3InsertIconUp_dis(Int16U x,Int16U y)//F3插入
{
Bmp_Decode((Int32U)F3_INSERT_UP_sdram, x, y, (pInt16U)SDRAM0_BASE_ADDR);	
}
void F4DeleteIconUp_dis(Int16U x,Int16U y)//F4 删除up
{
Bmp_Decode((Int32U)F4_DELETE_UP_sdram, x, y, (pInt16U)SDRAM0_BASE_ADDR);	
}
void F5AddIconUp_dis(Int16U x,Int16U y)//F5++
{
Bmp_Decode((Int32U)F5_ADD_UP_sdram, x, y, (pInt16U)SDRAM0_BASE_ADDR);
}
void F6SubIconUp_dis(Int16U x,Int16U y)//F6--
{
Bmp_Decode((Int32U)F6_SUB_UP_sdram, x, y, (pInt16U)SDRAM0_BASE_ADDR);
}







void F5DeleteAllKnifeIconUp_dis(Int16U x,Int16U y)//删除所有刀 数据F5
{
// Bmp_Decode((Int32U)F5_DELETEALL_UP_sdram, x, y, (pInt16U)SDRAM0_BASE_ADDR);
}

void F1OkIconUp_dis(Int16U x,Int16U y)//F1完成
{
Bmp_Decode((Int32U)F1_OK_UP_sdram, x, y, (pInt16U)SDRAM0_BASE_ADDR);
}
void F2ExitIconUp_dis(Int16U x,Int16U y)//F2退出
{
Bmp_Decode((Int32U)F2_EXIT_UP_sdram, x, y, (pInt16U)SDRAM0_BASE_ADDR);
}
void L_R_Arrow_dis(Int16U x, Int16U y)//左右箭头
{
Bmp_Decode((Int32U)L_R_ARROW_sdram, x, y, (pInt16U)SDRAM0_BASE_ADDR);
}
void F2DivNumIconUp_dis(Int16U x,Int16U y)//F2等分数up
{
Bmp_Decode((Int32U)F2_DIVNUM_UP_sdram, x, y, (pInt16U)SDRAM0_BASE_ADDR);
}
void F2DivNumIconDown_dis(Int16U x,Int16U y)//F2等分数down
{
Bmp_Decode((Int32U)F2_DIVNUM_DOWN_sdram, x, y, (pInt16U)SDRAM0_BASE_ADDR);
}
void F3DivDataIconUp_dis(Int16U x,Int16U y)//F3等分值up
{
Bmp_Decode((Int32U)F3_DIVDATA_UP_sdram, x, y, (pInt16U)SDRAM0_BASE_ADDR);
}
void F3DivDataIconDown_dis(Int16U x,Int16U y)//F3等分值down
{
Bmp_Decode((Int32U)F3_DIVDATA_DOWN_sdram, x, y, (pInt16U)SDRAM0_BASE_ADDR);
}
//--------pinyin--
void F1ShowMessIconUp_dis(Int16U x,Int16U y)//F1 查看mess
{
Bmp_Decode((Int32U)F1_LOOK_UP_sdram, x, y, (pInt16U)SDRAM0_BASE_ADDR);
}
void F2ByTimeIconUp_dis(Int16U x,Int16U y)//F2 按时间排列up
{
Bmp_Decode((Int32U)F2_BY_TIME_UP_sdram, x, y, (pInt16U)SDRAM0_BASE_ADDR);
}
void F2ByTimeIconDown_dis(Int16U x,Int16U y)//F2 按时间排列down
{
Bmp_Decode((Int32U)F2_BY_TIME_DOWN_sdram, x, y, (pInt16U)SDRAM0_BASE_ADDR);
}
void F3ByNumIconUp_dis(Int16U x,Int16U y)//F3 按序号排列up
{
Bmp_Decode((Int32U)F3_BY_NUM_UP_sdram, x, y, (pInt16U)SDRAM0_BASE_ADDR);
}
void F3ByNumIconDown_dis(Int16U x,Int16U y)//F3 按序号排列down
{
Bmp_Decode((Int32U)F3_BY_NUM_DOWN_sdram, x, y, (pInt16U)SDRAM0_BASE_ADDR);
}
void F4DeleteOneProIconUp_dis(Int16U x,Int16U y)//F4删除一个pro
{
Bmp_Decode((Int32U)F4_DELETE_ONE_PRO_UP_sdram, x, y, (pInt16U)SDRAM0_BASE_ADDR);
}
void F5DeleteAllProIconUp_dis(Int16U x,Int16U y)//F5删除所有pro
{
Bmp_Decode((Int32U)F5_DELETE_ALL_PRO_UP_sdram, x, y, (pInt16U)SDRAM0_BASE_ADDR);
}
void F1PinyinIconUp_dis(Int16U x,Int16U y)//F1拼音输入up
{
Bmp_Decode((Int32U)F1_PINYIN_UP_sdram, x, y, (pInt16U)SDRAM0_BASE_ADDR);
}
void F1PinyinIconDown_dis(Int16U x,Int16U y)//F1拼音输入down
{
Bmp_Decode((Int32U)F1_PINYIN_DOWN_sdram, x, y, (pInt16U)SDRAM0_BASE_ADDR);
}
void F2CharIconUp_dis(Int16U x,Int16U y)//F2字母输入up
{
Bmp_Decode((Int32U)F2_CHAR_UP_sdram, x, y, (pInt16U)SDRAM0_BASE_ADDR);
}
void F2CharIconDown_dis(Int16U x,Int16U y)//F2字母输入down
{
Bmp_Decode((Int32U)F2_CHAR_DOWN_sdram, x, y, (pInt16U)SDRAM0_BASE_ADDR);
}
void F3NumIconUp_dis(Int16U x,Int16U y)//F3数字输入up
{
Bmp_Decode((Int32U)F3_NUM_UP_sdram, x, y, (pInt16U)SDRAM0_BASE_ADDR);
}
void F3NumIconDown_dis(Int16U x,Int16U y)//F3数字输入down
{
Bmp_Decode((Int32U)F3_NUM_DOWN_sdram, x, y, (pInt16U)SDRAM0_BASE_ADDR);
}
void F4ExitIconUp_dis(Int16U x,Int16U y)//F4退出
{
Bmp_Decode((Int32U)F4_EXIT_UP_sdram, x, y, (pInt16U)SDRAM0_BASE_ADDR);
}
void EnterButtUp_dis(Int16U x, Int16U y)//OK butt 确定
{
Bmp_Decode((Int32U)ENTER_BUTT_sdram, x, y, (pInt16U)SDRAM0_BASE_ADDR);
}
//--------------------

void F1ParamaterIconUp_dis(Int16U x,Int16U y)//F1参数
{
Bmp_Decode((Int32U)F1_PARAMETER_sdram, x, y, (pInt16U)SDRAM0_BASE_ADDR);
}
void F2RulerIconUp_dis(Int16U x,Int16U y)//基准F2
{
Bmp_Decode((Int32U)F2_RULER_sdram, x, y, (pInt16U)SDRAM0_BASE_ADDR);
}
void F3ClockIconUp_dis(Int16U x,Int16U y)//F3时间
{
Bmp_Decode((Int32U)F3_CLOCK_sdram, x, y, (pInt16U)SDRAM0_BASE_ADDR);
}
void F4Wheel0_dis(Int16U x, Int16U y)//F4 电子手轮关0
{
Bmp_Decode((Int32U)F4_WHEEL0_sdram, x, y, (pInt16U)SDRAM0_BASE_ADDR);
}
void F4Wheel1_dis(Int16U x, Int16U y)//F4 电子手轮关1
{
Bmp_Decode((Int32U)F4_WHEEL1_sdram, x, y, (pInt16U)SDRAM0_BASE_ADDR);
}
void F5Wheel0_dis(Int16U x, Int16U y)//F5 电子手轮开0
{
// Bmp_Decode((Int32U)F5_WHEEL0_sdram, x, y, (pInt16U)SDRAM0_BASE_ADDR);
}
void F5Wheel1_dis(Int16U x, Int16U y)//F5 电子手轮开1
{
// Bmp_Decode((Int32U)F5_WHEEL1_sdram, x, y, (pInt16U)SDRAM0_BASE_ADDR);
} 
void F5PulseSetIconUp_dis(Int16U x,Int16U y)//F5脉冲当量
{
Bmp_Decode((Int32U)F5_PULSE_UP_sdram, x, y, (pInt16U)SDRAM0_BASE_ADDR);
}


//**********
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
void IR_LINE_dis(Int16U x, Int16U y)//红外线
{
Bmp_Decode((Int32U)IR_LINE_sdram, x, y, (pInt16U)SDRAM0_BASE_ADDR);
}
void IR_CUT_dis(Int16U x, Int16U y)//红外断开
{
Bmp_Decode((Int32U)IR_CUT_sdram, x, y, (pInt16U)SDRAM0_BASE_ADDR);
}


void RightArrow_dis(Int16U x,Int16U y)//右箭头 -->
{
//x=RIGHT_ARROW_X,y=RIGHT_ARROW_Y;
Bmp_Decode((Int32U)RIGHT_ARROW_sdram, x, y, (pInt16U)SDRAM0_BASE_ADDR);
}
void Schedule_dis(Int16U x, Int16U y)//进度条
{
Bmp_Decode((Int32U)SCHEDULE_sdram, x, y, (pInt16U)SDRAM0_BASE_ADDR);
}

//---------------------标记 图片
void RedKnifeF_dis(Int16U x, Int16U y)//红刀 标志
{
Bmp_Decode((Int32U)RED_KNIFE_F_sdram, x, y, (pInt16U)SDRAM0_BASE_ADDR);
}
void PushPaperF_dis(Int16U x, Int16U y)//推纸 标志
{
Bmp_Decode((Int32U)PUSH_PAPER_F_sdram, x, y, (pInt16U)SDRAM0_BASE_ADDR);
}
void SortPaperF_dis(Int16U x, Int16U y)//理纸 标志
{
Bmp_Decode((Int32U)SORT_PAPER_F_sdram, x, y, (pInt16U)SDRAM0_BASE_ADDR);
}
void PressPaperF_dis(Int16U x, Int16U y)//压纸 标志
{
Bmp_Decode((Int32U)PRE_PAPER_F_sdram, x, y, (pInt16U)SDRAM0_BASE_ADDR);
}
void AirBedF_dis(Int16U x, Int16U y)//气垫 标志
{
Bmp_Decode((Int32U)AIR_BED_F_sdram, x, y, (pInt16U)SDRAM0_BASE_ADDR);
}
//--add flags
void NoAirBedF_dis(Int16U x, Int16U y)//无气垫 标志
{
Bmp_Decode((Int32U)NO_AIR_BED_F_sdram, x, y, (pInt16U)SDRAM0_BASE_ADDR);
}
void OtherSetF_dis(Int16U x, Int16U y)//其他标记
{
Bmp_Decode((Int32U)OTHER_SET_F_sdram, x, y, (pInt16U)SDRAM0_BASE_ADDR);
}
void AllFlagsWind_dis(Int16U x, Int16U y)//标记wind
{
Bmp_Decode((Int32U)ALL_FLAGS_WIN_sdram, x, y, (pInt16U)SDRAM0_BASE_ADDR);
}
/**
//---------button
void F1AirBedButt_dis(Int16U x, Int16U y)//F1气垫butt 
{
Bmp_Decode((Int32U)AIR_BED_BUTT_sdram, x, y, (pInt16U)SDRAM0_BASE_ADDR);
}
void F2PrePaperButt_dis(Int16U x, Int16U y)//F2压纸butt 
{
Bmp_Decode((Int32U)PRE_PAPER_BUTT_sdram, x, y, (pInt16U)SDRAM0_BASE_ADDR);
}
void F3SortPaperButt_dis(Int16U x, Int16U y)//F3理纸butt 
{
Bmp_Decode((Int32U)SORT_PAPER_BUTT_sdram, x, y, (pInt16U)SDRAM0_BASE_ADDR);
}
void F4PushPaperButt_dis(Int16U x, Int16U y)//F4推纸butt 
{
Bmp_Decode((Int32U)PUSH_PAPER_BUTT_sdram, x, y, (pInt16U)SDRAM0_BASE_ADDR);
}
void F5RedKnifeButt_dis(Int16U x, Int16U y)//F5红刀butt 
{
Bmp_Decode((Int32U)RED_KNIFE_BUTT_sdram, x, y, (pInt16U)SDRAM0_BASE_ADDR);
}
void AllKnifeButt_dis(Int16U x, Int16U y)//全部刀butt ++++++++++++++
{
Bmp_Decode((Int32U)ALL_KNIFE_BUTT_sdram, x, y, (pInt16U)SDRAM0_BASE_ADDR);
}
**/
// void F6ExitButtUp_dis(Int16U x, Int16U y)//F6Exit butt 
// {
// Bmp_Decode((Int32U)F6_EXIT_BUTT_sdram, x, y, (pInt16U)SDRAM0_BASE_ADDR);
// }

void DatasTableFunPic_dis(Int16U x, Int16U y)//列表模式pic
{
	Bmp_Decode((Int32U)MAIN_TABLE_PIC_sdram, x, y, (pInt16U)SDRAM0_BASE_ADDR);
}





//---机器图片
void MachinePic_dis(Int16U x, Int16U y)//手动模式下 机器图片
{
Bmp_Decode((Int32U)MACHINE_PIC_sdram, x, y, (pInt16U)SDRAM0_BASE_ADDR);
}

void DeleteAll_Up_dis(Int16U x, Int16U y)//删除所有up
{
Bmp_Decode((Int32U)DELETE_ALL_UP_sdram, x, y, (pInt16U)SDRAM0_BASE_ADDR);
}
// void ShiftButtonUp_dis(Int16U x, Int16U y)//上档按钮shift
// {
// Bmp_Decode((Int32U)SHIFT_BUTT_UP_sdram, x, y, (pInt16U)SDRAM0_BASE_ADDR);
// }
// void ShiftButtonDown_dis(Int16U x, Int16U y)//上档按钮shift
// {
// Bmp_Decode((Int32U)SHIFT_BUTT_DOWN_sdram, x, y, (pInt16U)SDRAM0_BASE_ADDR);
// }
//-------
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
void FastFWD_Up_dis(Int16U x, Int16U y)//快进up
{
Bmp_Decode((Int32U)FAST_FORWD_UP_sdram, x, y, (pInt16U)SDRAM0_BASE_ADDR);
}
void FastBACK_Up_dis(Int16U x, Int16U y)//快退up
{
Bmp_Decode((Int32U)FAST_BACK_UP_sdram, x, y, (pInt16U)SDRAM0_BASE_ADDR);
}

void StopButtonUp_dis(Int16U x, Int16U y)//停止up
{
Bmp_Decode((Int32U)STOP_UP_sdram, x, y, (pInt16U)SDRAM0_BASE_ADDR);
}
void RunButtonUp_dis(Int16U x, Int16U y)//运行按钮
{
Bmp_Decode((Int32U)RUN_BUTT_sdram, x, y, (pInt16U)SDRAM0_BASE_ADDR);
}

//------计算器图片----
void CalcWind_dis(Int16U x, Int16U y)//计算器框
{
Bmp_Decode((Int32U)CAL_WIND_sdram, x, y, (pInt16U)SDRAM0_BASE_ADDR);	
}
//-----计算器-buttons
void CalButton0_up_dis(Int16U x, Int16U y)//0
{
Bmp_Decode((Int32U)CAL_0_UP_sdram, x, y, (pInt16U)SDRAM0_BASE_ADDR);
}
void CalButton1_up_dis(Int16U x, Int16U y)//1
{
Bmp_Decode((Int32U)CAL_1_UP_sdram, x, y, (pInt16U)SDRAM0_BASE_ADDR);
}
void CalButton2_up_dis(Int16U x, Int16U y)//2
{
Bmp_Decode((Int32U)CAL_2_UP_sdram, x, y, (pInt16U)SDRAM0_BASE_ADDR);
}
void CalButton3_up_dis(Int16U x, Int16U y)//3
{
Bmp_Decode((Int32U)CAL_3_UP_sdram, x, y, (pInt16U)SDRAM0_BASE_ADDR);
}
void CalButton4_up_dis(Int16U x, Int16U y)//4
{
Bmp_Decode((Int32U)CAL_4_UP_sdram, x, y, (pInt16U)SDRAM0_BASE_ADDR);
}
void CalButton5_up_dis(Int16U x, Int16U y)//5
{
Bmp_Decode((Int32U)CAL_5_UP_sdram, x, y, (pInt16U)SDRAM0_BASE_ADDR);
}
void CalButton6_up_dis(Int16U x, Int16U y)//6
{
Bmp_Decode((Int32U)CAL_6_UP_sdram, x, y, (pInt16U)SDRAM0_BASE_ADDR);
}
void CalButton7_up_dis(Int16U x, Int16U y)//7
{
Bmp_Decode((Int32U)CAL_7_UP_sdram, x, y, (pInt16U)SDRAM0_BASE_ADDR);
}
void CalButton8_up_dis(Int16U x, Int16U y)//8
{
Bmp_Decode((Int32U)CAL_8_UP_sdram, x, y, (pInt16U)SDRAM0_BASE_ADDR);
}
void CalButton9_up_dis(Int16U x, Int16U y)//9
{
Bmp_Decode((Int32U)CAL_9_UP_sdram, x, y, (pInt16U)SDRAM0_BASE_ADDR);
}
void CalButtonDot_up_dis(Int16U x, Int16U y)//.
{
Bmp_Decode((Int32U)CAL_DOT_UP_sdram, x, y, (pInt16U)SDRAM0_BASE_ADDR);
}
void CalButtonClr_up_dis(Int16U x, Int16U y)//clr
{
Bmp_Decode((Int32U)CAL_CLR_UP_sdram, x, y, (pInt16U)SDRAM0_BASE_ADDR);
}
void CalButtonAdd_up_dis(Int16U x, Int16U y)//+
{
Bmp_Decode((Int32U)CAL_ADD_UP_sdram, x, y, (pInt16U)SDRAM0_BASE_ADDR);
}
void CalButtonSub_up_dis(Int16U x, Int16U y)//-
{
Bmp_Decode((Int32U)CAL_SUB_UP_sdram, x, y, (pInt16U)SDRAM0_BASE_ADDR);
}
void CalButtonMul_up_dis(Int16U x, Int16U y)//*
{
Bmp_Decode((Int32U)CAL_MUL_UP_sdram, x, y, (pInt16U)SDRAM0_BASE_ADDR);
}
void CalButtonDiv_up_dis(Int16U x, Int16U y)//div
{
Bmp_Decode((Int32U)CAL_DIV_UP_sdram, x, y, (pInt16U)SDRAM0_BASE_ADDR);
}
void CalButtonEqu_up_dis(Int16U x, Int16U y)//=
{
Bmp_Decode((Int32U)CAL_EQU_UP_sdram, x, y, (pInt16U)SDRAM0_BASE_ADDR);
}
void CalButtonOk_up_dis(Int16U x, Int16U y)//ok
{
Bmp_Decode((Int32U)CAL_OK_UP_sdram, x, y, (pInt16U)SDRAM0_BASE_ADDR);
}
//--------down button
void CalButton0_down_dis(Int16U x, Int16U y)//0
{
Bmp_Decode((Int32U)CAL_0_DOWN_sdram, x, y, (pInt16U)SDRAM0_BASE_ADDR);
}
void CalButton1_down_dis(Int16U x, Int16U y)//1
{
Bmp_Decode((Int32U)CAL_1_DOWN_sdram, x, y, (pInt16U)SDRAM0_BASE_ADDR);
}
void CalButton2_down_dis(Int16U x, Int16U y)//2
{
Bmp_Decode((Int32U)CAL_2_DOWN_sdram, x, y, (pInt16U)SDRAM0_BASE_ADDR);
}
void CalButton3_down_dis(Int16U x, Int16U y)//3
{
Bmp_Decode((Int32U)CAL_3_DOWN_sdram, x, y, (pInt16U)SDRAM0_BASE_ADDR);
}
void CalButton4_down_dis(Int16U x, Int16U y)//4
{
Bmp_Decode((Int32U)CAL_4_DOWN_sdram, x, y, (pInt16U)SDRAM0_BASE_ADDR);
}
void CalButton5_down_dis(Int16U x, Int16U y)//5
{
Bmp_Decode((Int32U)CAL_5_DOWN_sdram, x, y, (pInt16U)SDRAM0_BASE_ADDR);
}
void CalButton6_down_dis(Int16U x, Int16U y)//6
{
Bmp_Decode((Int32U)CAL_6_DOWN_sdram, x, y, (pInt16U)SDRAM0_BASE_ADDR);
}
void CalButton7_down_dis(Int16U x, Int16U y)//7
{
Bmp_Decode((Int32U)CAL_7_DOWN_sdram, x, y, (pInt16U)SDRAM0_BASE_ADDR);
}
void CalButton8_down_dis(Int16U x, Int16U y)//8
{
Bmp_Decode((Int32U)CAL_8_DOWN_sdram, x, y, (pInt16U)SDRAM0_BASE_ADDR);
}
void CalButton9_down_dis(Int16U x, Int16U y)//9
{
Bmp_Decode((Int32U)CAL_9_DOWN_sdram, x, y, (pInt16U)SDRAM0_BASE_ADDR);
}
void CalButtonDot_down_dis(Int16U x, Int16U y)//.
{
Bmp_Decode((Int32U)CAL_DOT_DOWN_sdram, x, y, (pInt16U)SDRAM0_BASE_ADDR);
}
void CalButtonClr_down_dis(Int16U x, Int16U y)//clr
{
Bmp_Decode((Int32U)CAL_CLR_DOWN_sdram, x, y, (pInt16U)SDRAM0_BASE_ADDR);
}
void CalButtonAdd_down_dis(Int16U x, Int16U y)//+
{
Bmp_Decode((Int32U)CAL_ADD_DOWN_sdram, x, y, (pInt16U)SDRAM0_BASE_ADDR);
}
void CalButtonSub_down_dis(Int16U x, Int16U y)//-
{
Bmp_Decode((Int32U)CAL_SUB_DOWN_sdram, x, y, (pInt16U)SDRAM0_BASE_ADDR);
}
void CalButtonMul_down_dis(Int16U x, Int16U y)//*
{
Bmp_Decode((Int32U)CAL_MUL_DOWN_sdram, x, y, (pInt16U)SDRAM0_BASE_ADDR);
}
void CalButtonDiv_down_dis(Int16U x, Int16U y)//div
{
Bmp_Decode((Int32U)CAL_DIV_DOWN_sdram, x, y, (pInt16U)SDRAM0_BASE_ADDR);
}
void CalButtonEqu_down_dis(Int16U x, Int16U y)//=
{
Bmp_Decode((Int32U)CAL_EQU_DOWN_sdram, x, y, (pInt16U)SDRAM0_BASE_ADDR);
}
void CalButtonOk_down_dis(Int16U x, Int16U y)//ok
{
Bmp_Decode((Int32U)CAL_OK_DOWN_sdram, x, y, (pInt16U)SDRAM0_BASE_ADDR);
}

//------------复合按钮显示---------------
void MainPowerOnButt_dis(Int8U down_flag)	//主电源开
{
if(down_flag == 0)
	{
		PowerOnUp_dis( MAIN_PWR_ON_X, MAIN_PWR_ON_Y);//电源绿up
	}
else
	{
		PowerOnDown_dis( MAIN_PWR_ON_X, MAIN_PWR_ON_Y);//电源绿down
	}
}
void MainPowerOffButt_dis(Int8U down_flag)	//主电源关
{
if(down_flag == 0)
	{
		PowerOffUp_dis( MAIN_PWR_OFF_X, MAIN_PWR_OFF_Y);//电源
	}
else
	{
		PowerOffDown_dis( MAIN_PWR_OFF_X, MAIN_PWR_OFF_Y);//电源
	}
}

void LEDKnifeButt_dis(Int8U down_flag)	//对刀灯
{
if(down_flag == 0)
	{
		LightKnifeOff_dis( LED_KNIFE_X, LED_KNIFE_Y);//对刀灯off
	}
else
	{
		LightKnifeOn_dis( LED_KNIFE_X, LED_KNIFE_Y);//对刀灯on
	}	
}
void LEDBrightButt_dis(Int8U down_flag)	//照明灯
{
if(down_flag == 0)
	{
		LightLEDOff_dis( LED_LED_X, LED_LED_Y);//照明灯 off
	}
else
	{
		LightLEDOn_dis( LED_LED_X, LED_LED_Y);//照明灯on
	}		
}
void AllFlagButt_dis(Int8U dis_flag)	//all标记 按钮显示
{
		/***
Int16U x,y,back_color=F1_6BUTT_BACK_COLOR;
if(dis_flag == 0)
	{
	x=ALL_FLAG_WIN_BASE_X,y=ALL_FLAG_WIN_BASE_Y;
	GLCD_SetWindow_Fill(x,y,x+ALL_FLAG_WIN_WIDE,y+ALL_FLAG_WIN_HIGH, back_color,back_color);//空白列表
	}
else
	{
	 F1AirBedButt_dis( F1_AIR_BED_X,  F1_AIR_BED_Y);//F1气垫butt 
	 F2PrePaperButt_dis( F2_PRE_PAPER_X,  F2_PRE_PAPER_Y);//F2压纸butt 
	 F3SortPaperButt_dis( F3_SORT_PAPER_X,  F3_SORT_PAPER_Y);//F3理纸butt 
	 F4PushPaperButt_dis( F4_PUSH_PAPER_X,  F4_PUSH_PAPER_Y);//F4推纸butt 
	 F5RedKnifeButt_dis( F5_RED_KNIFE_X,  F5_RED_KNIFE_Y);//F5红刀butt 
	 AllKnifeButt_dis( S5_ALL_KNIFE_X,  S5_ALL_KNIFE_Y);//全部刀butt 
	}
	 ***/
}
void Run_StopButt_dis(void)	//运行up  +  停止up
{
RunButtonUp_dis(RUN_BUTT_X,RUN_BUTT_Y);//运行up
StopButtonUp_dis(STOP_X,STOP_Y);//停止up
}

void NormalKnifeButt_dis(void)	//正常裁切
{
	NormalKnifeDown_dis(CHG_KNIFE_NORMAL_X ,CHG_KNIFE_NORMAL_Y );//正常裁切down
	ElectricKnifeUp_dis( CHG_KNIFE_ELECT_X, CHG_KNIFE_ELECT_Y);//电动换刀up
	ManualKnifeUp_dis( CHG_KNIFE_MANUAL_X, CHG_KNIFE_MANUAL_Y);//手动换刀up
}
void ElectricKnifeButt_dis(void)	//电动换刀
{
	NormalKnifeUp_dis(CHG_KNIFE_NORMAL_X ,CHG_KNIFE_NORMAL_Y );//正常裁切up
	ElectricKnifeDown_dis( CHG_KNIFE_ELECT_X, CHG_KNIFE_ELECT_Y);//电动换刀down
	ManualKnifeUp_dis( CHG_KNIFE_MANUAL_X, CHG_KNIFE_MANUAL_Y);//手动换刀up
}
void ManualKnifeButt_dis(void)	//手动换刀
{
	NormalKnifeUp_dis(CHG_KNIFE_NORMAL_X ,CHG_KNIFE_NORMAL_Y );//正常裁切up
	ElectricKnifeUp_dis( CHG_KNIFE_ELECT_X, CHG_KNIFE_ELECT_Y);//电动换刀up
	ManualKnifeDown_dis( CHG_KNIFE_MANUAL_X, CHG_KNIFE_MANUAL_Y);//手动换刀down
}

void ElectricalWheel_dis(void)  //电子手轮  开关状态
{
if(MotorType>=MOTOR_AC_SERVO)
	{
	if(ElectricWheelOn_flag==0)
		{
		// if(WorkMode==MANUAL_MODE)
			 F4Wheel0_dis(F4_WHEEL_BUTT_X,F4_WHEEL_BUTT_Y);
		// else if(WorkMode==AUTO_MODE)
			//F5Wheel0_dis(F5_WHEEL_BUTT_X,F5_WHEEL_BUTT_Y);
		}
	else	
		{
		// if(WorkMode==MANUAL_MODE)
			 F4Wheel1_dis(F4_WHEEL_BUTT_X,F4_WHEEL_BUTT_Y);
		// else if(WorkMode==AUTO_MODE) 
		//	F5Wheel1_dis(F5_WHEEL_BUTT_X,F5_WHEEL_BUTT_Y);
		}
	}
}

void S6Amend0_dis(Int16U x, Int16U y)//修改偏移量----------------------
{
Bmp_Decode((Int32U)DATA_AMEND0_sdram, x, y, (pInt16U)SDRAM0_BASE_ADDR);
} 
void S6Amend1_dis(Int16U x, Int16U y)//修改偏移量----------------------
{
Bmp_Decode((Int32U)DATA_AMEND1_sdram, x, y, (pInt16U)SDRAM0_BASE_ADDR);
} 
void AmendButtonFlag_dis(void)	//F6修改数据偏移量
{
if(MotorType>=MOTOR_AC_SERVO)
	{
	if(WorkMode==AUTO_MODE)
		{
			/****xxxxxxxxxxxxxxxx20191030
		if(AmendSwitch_flag==0)
			S6Amend0_dis( S6_AMEND_BUTT_X,  S6_AMEND_BUTT_Y);//修改偏移量
		else
			S6Amend1_dis( S6_AMEND_BUTT_X,  S6_AMEND_BUTT_Y);//修改偏移量
		**/
		}
	}
}
void F6IoTestButton_dis(Int16U x, Int16U y)	//io  test
{
Bmp_Decode((Int32U)F6_TST_IO_sdram, x, y, (pInt16U)SDRAM0_BASE_ADDR);
}

void CursorSizeName(void)	//标称尺寸
{
Int16U x=MARK_LABEL_X,y=MARK_LABEL_Y,b_color=YELLOW_COLOR;
switch(Language)
	{
	case CHN_HAN:
		Printf24("标称位置 ",x,y,BLACK_COLOR,1,b_color);
			break;
	case ENGLISH:
		
	case INDONSIA:	//印尼
		
	case PORTUGAL:	//葡萄牙
		
	case SPANISH: //西班牙
		Printf24("IndexSize",x,y,BLACK_COLOR,1,b_color);
			break;
	}		
}
void CursorSize_dis(Int32U size)	//标称尺寸  显示***************
{
Int8U num[8],k;
Int16U x,y,back_color=WIN_DOWN_BACK_COLOR;
x=MARK_LABEL_DATA_X;
y=MARK_LABEL_DATA_Y;

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
// Printf24(num,x,y,BLACK_COLOR,1,back_color);
// ASCII_Printf(num,120+1,24,40,ASCII_bold24x40, x,y,BLACK_COLOR,back_color);
ASCII_Printf(num,64+1,16,32,ASCII_bold16x32, x,y,WHITE_COLOR,back_color);
}

void StepMoveButt_dis(Int32U size)	//步进button 显示
{
Int16U x1,y1,x2,y2,line_color,back_color,num_color;
Int8U c_num[8]={0},n=0,k;
x1=STEP_MOV_BUTT_X,y1=STEP_MOV_BUTT_Y;
x2=x1+STEP_MOV_BUTT_WIDE,y2=y1+STEP_MOV_BUTT_HIGH;
line_color=0,back_color=BLUE_COLOR,num_color=WHITE_COLOR;
GLCD_SetWindow_Fill(x1,y1,x2,y2,line_color,back_color);//

if(Unit!=UNIT_MM)//inch  单位
	 size=size*100/254;
c_num[n++]=size/100000;
c_num[n++]=(size/10000)%10;
c_num[n++]=(size/1000)%10;
c_num[n++]=(size/100)%10;
c_num[n++]='.';
c_num[n++]=(size/10)%10;
c_num[n++]=(size)%10;
c_num[n++]=0;
if(Unit!=UNIT_MM)//inc
	{
	c_num[4]=c_num[3];
	c_num[3]='.';
	}
for(n=0;n<7;n++)
	{
	if(c_num[n]!='.')
		c_num[n] += 48;
	}
n=0;
while(c_num[n]!='.')
	{
	if(c_num[n] == '0')
		{
		n++;
		}
	else
		break;
	}
k=0;
if(n>0)
	{
	if(c_num[n]=='.')
		n--;
	while(c_num[k]!=0)
		{
		c_num[k] = c_num[k+n];
		k++;
		}
	c_num[k]=0;
	}
Printf24(c_num,x1+5,y1+3,num_color,1,back_color);//
}

//-------------*****模式icon间 切换 显示******------------------(icon+name)
void ProTableIcon_dis(void)	//程序列表模式下 icon显示
{
F1ShowMessIconUp_dis(F1_BUTTON_X,F1_BUTTON_Y);//F1 查看mess
 F2ByTimeIconUp_dis(F2_BUTTON_X,F2_BUTTON_Y);//F2 按时间排列up  20180523????
switch(DisAllProgMode)
	{
	case PRO_BY_NUM://按序号
			// F2ByTimeIconUp_dis(F2_BUTTON_X,F2_BUTTON_Y);//F2 按时间排列up
			F3ByNumIconDown_dis(F3_BUTTON_X,F3_BUTTON_Y);//F3 按序号排列down
			break;
	case PRO_BY_TIME://按时间
			// F2ByTimeIconDown_dis(F2_BUTTON_X,F2_BUTTON_Y);//F2 按时间排列down
			F3ByNumIconUp_dis(F3_BUTTON_X,F3_BUTTON_Y);//F3 按序号排列up
			break;	
	}
F4DeleteOneProIconUp_dis(F4_BUTTON_X,F4_BUTTON_Y);//F4删除一个pro
F5DeleteAllProIconUp_dis(F5_BUTTON_X,F5_BUTTON_Y);//F5删除所有pro
// F6ExitButtUp_dis(F6_BUTTON_X,F6_BUTTON_Y);//F6Exit butt 标志
}
void ProMessIcon_dis(void)	//输入法模式 icon显示
{
switch(InputMode)
	{
	case PINYIN_INPUT:	//拼音输入
			F1PinyinIconDown_dis(F1_BUTTON_X,F1_BUTTON_Y);//F1拼音输入down---------
			F2CharIconUp_dis(F2_BUTTON_X,F2_BUTTON_Y);//F2字母输入up
			F3NumIconUp_dis(F3_BUTTON_X,F3_BUTTON_Y);//F3数字输入up
			F4ExitIconUp_dis(F4_BUTTON_X,F4_BUTTON_Y);//F4up退出
			break;
	case CHAR_INPUT:	//字母输入
			F1PinyinIconUp_dis(F1_BUTTON_X,F1_BUTTON_Y);//F1拼音输入up
			F2CharIconDown_dis(F2_BUTTON_X,F2_BUTTON_Y);//F2字母输入down---------
			F3NumIconUp_dis(F3_BUTTON_X,F3_BUTTON_Y);//F3数字输入up
			F4ExitIconUp_dis(F4_BUTTON_X,F4_BUTTON_Y);//F4up退出
			break;	
	case NUMBER_INPUT:	//数字 输入
			F1PinyinIconUp_dis(F1_BUTTON_X,F1_BUTTON_Y);//F1拼音输入up
			F2CharIconUp_dis(F2_BUTTON_X,F2_BUTTON_Y);//F2字母输入up
			F3NumIconDown_dis(F3_BUTTON_X,F3_BUTTON_Y);//F3数字输入down---------
			F4ExitIconUp_dis(F4_BUTTON_X,F4_BUTTON_Y);//F4up退出
			break;		
	}
}

//================子模式  icon显示==============================
void SubModeIcon_dis(Int16U mode)
{
Int16U x1,y1,x2,y2,back_color;
//清除F1-F6 button 显示*****************
back_color=F1_6BUTT_BACK_COLOR;
x1=F1_BUTTON_X,y1=F1_BUTTON_Y;
x2=x1+FICONBUTT_WIDE,y2=y1+FICONBUTT_GAP_V*6-4;
GLCD_SetWindow_Fill(x1,y1,x2,y2,back_color,back_color);//空白F1,2,3...
// // AllFlagButt_dis( 0);	//all标记 按钮显示清除
/****
//--------------清除方向箭,F0,F5
if((mode!=PROG_PRO_MODE)&&(mode!=TEACH_PRO_MODE)
	&&(mode!=PROG_PRO_MESS_MODE)&&(mode!=TEACH_PRO_MESS_MODE)//程序 信息
	&&(mode!=MANUAL_MODE))	
	{
	x1=BACK_PAGE_X,y1=BACK_PAGE_Y;
	x2=FRONT_PAGE_X+F1_4_WIDE,y2=y1+60;
	back_color=TEXT_TAB_BACK_COLOR;
	GLCD_SetWindow_Fill(x1,y1,x2,y2,back_color,back_color);  //隐藏方向箭头,F0,F5 .....
	}***/
//--------------清除Delete all+ amend
back_color=WIN_DOWN_BACK_COLOR;
x1=DELETE_ALL_X,y1=DELETE_ALL_Y;
x2=S6_AMEND_BUTT_X+DELETE_ALL_BUT_WIDE,y2=DELETE_ALL_Y+DELETE_ALL_BUT_HIGH;
GLCD_SetWindow_Fill(x1,y1,x2,y2,back_color,back_color);  //delete all.....
//--------------，运行.......
x1=STOP_X,y1=RUN_BUTT_Y;
x2=RUN_BUTT_X+RUN_BUTT_WIDE,y2=STOP_Y+RUN_BUTT_HIGH;
GLCD_SetWindow_Fill(x1,y1,x2,y2,back_color,back_color);  //，运行..
//--------------，进退.......
x1=BACK_PAGE_X,y1=BACK_PAGE_Y;
x2=FAST_FWD_X+JOG_BUTT_WIDE,y2=FRONT_PAGE_Y+JOG_BUTT_HIGH;
GLCD_SetWindow_Fill(x1,y1,x2,y2,back_color,back_color);  //，前进，后退..

//-----work mode
switch(mode)
	{
	
	case MANUAL_MODE:	//手动模式..............
			//----------F
			// // ShiftButtonUp_dis(SHIFT_BUTT_X,SHIFT_BUTT_Y);	//shift上档 按钮
			//F1,2,3,4......
			F1ParamaterIconUp_dis(F1_BUTTON_X,F1_BUTTON_Y);//F1参数
			F2RulerIconUp_dis(F2_BUTTON_X,F2_BUTTON_Y);//F2基准butt
			F3ClockIconUp_dis(F3_BUTTON_X,F3_BUTTON_Y);//F3时间
			// if(MotorType<MOTOR_DC_SERVO)    //变频器--
				// F4PulseSetIconUp_dis(F4_BUTTON_X,F4_BUTTON_Y);//F4脉冲当量
			// else
				ElectricalWheel_dis();  //电子手轮  开关状态
			if(MotorType<MOTOR_AC_SERVO)    //变频器--(MotorType<MOTOR_DC_SERVO) 
				F5PulseSetIconUp_dis(F5_BUTTON_X,F5_BUTTON_Y);//F5脉冲当量
			F6IoTestButton_dis(F6_BUTTON_X,F6_BUTTON_Y);// io test
			StepMoveButt_dis(Step_Size);	//步进button 显示
			//---------
			Run_StopButt_dis();	//运行up  +  停止up
			FrontPage_Up_dis( FRONT_PAGE_X,  FRONT_PAGE_Y);//前进up
			BackPage_Up_dis( BACK_PAGE_X,  BACK_PAGE_Y);//后退up
			FastFWD_Up_dis(FAST_FWD_X , FAST_FWD_Y );//快进up
			FastBACK_Up_dis( FAST_BACK_X,  FAST_BACK_Y);//快退up
			break;
	case AUTO_MODE://自动模式..............	
			// // AllFlagButt_dis( 1);	//all标记 按钮显示
			AmendButtonFlag_dis();	//F6修改数据偏移量
	case TEACH_MODE:		//示教模式..............
			//----------F
			// // ShiftButtonUp_dis(SHIFT_BUTT_X,SHIFT_BUTT_Y);	//shift上档 按钮
			DeleteAll_Up_dis(DELETE_ALL_X,DELETE_ALL_Y);
			//F1,2,3,4......
			F1LabelIconUp_dis(F1_BUTTON_X,F1_BUTTON_Y);//F1标签up
			F2DivideIconUp_dis(F2_BUTTON_X,F2_BUTTON_Y);//F2等分up
			F3InsertIconUp_dis(F3_BUTTON_X,F3_BUTTON_Y);//F3插入
			F4DeleteIconUp_dis(F4_BUTTON_X,F4_BUTTON_Y);//F4 删除up
			F5AddIconUp_dis(F5_BUTTON_X,F5_BUTTON_Y);//F5++
			F6SubIconUp_dis(F6_BUTTON_X,F6_BUTTON_Y);//F6--
			//---------
			Run_StopButt_dis();	//运行up  +  停止up
			FrontPage_Up_dis( FRONT_PAGE_X,  FRONT_PAGE_Y);//前进up
			BackPage_Up_dis( BACK_PAGE_X,  BACK_PAGE_Y);//后退up
			FastFWD_Up_dis(FAST_FWD_X , FAST_FWD_Y );//快进up
			FastBACK_Up_dis( FAST_BACK_X,  FAST_BACK_Y);//快退up
			break;
	case READ_PRO_MODE:		//查找模式......程序选择....
			if(SetModeEnbByCode_flag==1)
				{
				UpArrow_Up_dis( PRO_UP_ARROW_X,  PRO_UP_ARROW_Y);//上箭头up
				DownArrow_Up_dis( PRO_DOWN_ARROW_X,  PRO_DOWN_ARROW_Y);//下箭头up
				EnterButtUp_dis(ENTER_OK_BUTT_X, ENTER_OK_BUTT_Y);//OK butt 确定
				ProTableIcon_dis();	//程序列表模式下 icon显示
				}
			break;
	case SELF_CUT_MODE:		//自刀模式...............
			//---------
			Run_StopButt_dis();	//运行up  +  停止up
			FrontPage_Up_dis( FRONT_PAGE_X,  FRONT_PAGE_Y);//前进up
			BackPage_Up_dis( BACK_PAGE_X,  BACK_PAGE_Y);//后退up
			FastFWD_Up_dis(FAST_FWD_X , FAST_FWD_Y );//快进up
			FastBACK_Up_dis( FAST_BACK_X,  FAST_BACK_Y);//快退up
			break;
	//---自动...下Fx...........
	case AUTO_LABEL_MODE:		 //标签
	case TEACH_LABEL_MODE:		 //标签
			F1OkIconUp_dis(F1_BUTTON_X,F1_BUTTON_Y);//F1完成
			F2ExitIconUp_dis(F2_BUTTON_X,F2_BUTTON_Y);//F2up退出
			UpArrow_Up_dis( LAB_UP_ARROW_X,  LAB_UP_ARROW_Y);//上箭头up
			DownArrow_Up_dis( LAB_DOWN_ARROW_X,  LAB_DOWN_ARROW_Y);//下箭头up
			//---------
			F1LabelFunPic_dis(LABEL_FUN_PIC_X,LABEL_FUN_PIC_Y);//标签功能pic
			break;
	case AUTO_DIVIDE_MODE:		 //	等分
	case TEACH_DIVIDE_MODE:	 //等分	
			UpArrow_Up_dis( DIV_UP_ARROW_X,  DIV_UP_ARROW_Y);//上箭头up
			DownArrow_Up_dis( DIV_DOWN_ARROW_X,  DIV_DOWN_ARROW_Y);//下箭头up
			//---------
			if(DivideValue_flag==0) //等分数功能
				{
				F1OkIconUp_dis(F1_BUTTON_X,F1_BUTTON_Y);//F1完成
				F2DivNumIconDown_dis(F2_BUTTON_X,F2_BUTTON_Y);//F2等分数down------
				F3DivDataIconUp_dis(F3_BUTTON_X,F3_BUTTON_Y);//F3等分值up
				F4ExitIconUp_dis(F4_BUTTON_X,F4_BUTTON_Y);//F4up退出
				//------------
				F2DivideNumPic_dis(DIVIDE_FUN_PIC_X,DIVIDE_FUN_PIC_Y);//等分数功能 pic
				}
			else	//等分值
				{
				F1OkIconUp_dis(F1_BUTTON_X,F1_BUTTON_Y);//完成
				F2DivNumIconUp_dis(F2_BUTTON_X,F2_BUTTON_Y);//F2等分数up
				F3DivDataIconDown_dis(F3_BUTTON_X,F3_BUTTON_Y);//F3等分值down---
				F4ExitIconUp_dis(F4_BUTTON_X,F4_BUTTON_Y);//F4up退出
				//------------
				F3DivideValuePic_dis(DIVIDE_FUN_PIC_X,DIVIDE_FUN_PIC_Y);//等分值功能 pic
				}
			break;
	//---编程 .............
			
	// // case TEACH_PRO_MODE:	//程序选择
			// // UpArrow_Up_dis( PRO_UP_ARROW_X,  PRO_UP_ARROW_Y);//上箭头up
			// // DownArrow_Up_dis( PRO_DOWN_ARROW_X,  PRO_DOWN_ARROW_Y);//下箭头up
			// // EnterButtUp_dis(ENTER_OK_BUTT_X, ENTER_OK_BUTT_Y);//OK butt 确定
			// // ProTableIcon_dis();	//程序列表模式下 icon显示
			// // break;
	case READ_PRO_MESS_MODE:	 //程序 信息
	// // case TEACH_PRO_MESS_MODE:	//程序 信息
			ProMessIcon_dis();	//输入法模式 icon显示
			break;	
	//-- 手动--
	// // case AUTO_RULER_MODE:  //基准
	case MANUAL_RULER_MODE:  //基准
	// // case SELF_RULER_MODE:  //基准
			F1OkIconUp_dis(F1_BUTTON_X,F1_BUTTON_Y);//F1完成
			F2ExitIconUp_dis(F2_BUTTON_X,F2_BUTTON_Y);//F2up退出
			//---------
			// F1RulerFunPic_dis(RULER_FUN_PIC_X,RULER_FUN_PIC_Y);//基准功能pic	
			break;	
	// // case AUTO_TOOLS_MODE:    //参数
	case MANUAL_TOOLS_MODE:    //参数
	// // case SELF_TOOLS_MODE:    //参数
			F1OkIconUp_dis(F1_BUTTON_X,F1_BUTTON_Y);//F1完成
			F2ExitIconUp_dis(F2_BUTTON_X,F2_BUTTON_Y);//F2up退出
			UpArrow_Up_dis( LAB_UP_ARROW_X,  LAB_UP_ARROW_Y);//上箭头up
			DownArrow_Up_dis( LAB_DOWN_ARROW_X,  LAB_DOWN_ARROW_Y);//下箭头up
			L_R_Arrow_dis(L_R_ARROW_X, L_R_ARROW_Y);//左右箭头
			//---------
			F2DatasFunPic_dis(SETDATA_FUN_PIC_X,SETDATA_FUN_PIC_Y);//参数功能pic
			break;	
	case MANUAL_CLOCK_MODE://时间模式
			F1OkIconUp_dis(F1_BUTTON_X,F1_BUTTON_Y);//F1完成
			F2ExitIconUp_dis(F2_BUTTON_X,F2_BUTTON_Y);//F2up退出
			UpArrow_Up_dis( LAB_UP_ARROW_X,  LAB_UP_ARROW_Y);//上箭头up
			DownArrow_Up_dis( LAB_DOWN_ARROW_X,  LAB_DOWN_ARROW_Y);//下箭头up
			//---------
			F3ClockFunPic_dis(CLOCK_FUN_PIC_X,CLOCK_FUN_PIC_Y);//F3时钟模式pic	
			break;
	case MANUAL_PULSE_MODE:  //设定脉冲当量
			F1OkIconUp_dis(F1_BUTTON_X,F1_BUTTON_Y);//F1完成
			F2ExitIconUp_dis(F2_BUTTON_X,F2_BUTTON_Y);//F2up退出
			UpArrow_Up_dis( LAB_UP_ARROW_X,  LAB_UP_ARROW_Y);//上箭头up
			DownArrow_Up_dis( LAB_DOWN_ARROW_X,  LAB_DOWN_ARROW_Y);//下箭头up
			break;
	case MANUAL_SERVO_C_MODE:	//直流伺服 C 参数
			F1OkIconUp_dis(F1_BUTTON_X,F1_BUTTON_Y);//F1完成
			F2ExitIconUp_dis(F2_BUTTON_X,F2_BUTTON_Y);//F2up退出
			UpArrow_Up_dis( LAB_UP_ARROW_X,  LAB_UP_ARROW_Y);//上箭头up
			DownArrow_Up_dis( LAB_DOWN_ARROW_X,  LAB_DOWN_ARROW_Y);//下箭头up
			break;	
	case MANUAL_PASS_MODE:   //密码
			F1OkIconUp_dis(F1_BUTTON_X,F1_BUTTON_Y);//F1完成
			F2ExitIconUp_dis(F2_BUTTON_X,F2_BUTTON_Y);//F2up退出
			UpArrow_Up_dis( LAB_UP_ARROW_X,  LAB_UP_ARROW_Y);//上箭头up
			DownArrow_Up_dis( LAB_DOWN_ARROW_X,  LAB_DOWN_ARROW_Y);//下箭头up
			L_R_Arrow_dis(L_R_ARROW_X, L_R_ARROW_Y);//左右箭头
			//---------
			//PsswordFunPic_dis(PASSWORD_FUN_PIC_X,PASSWORD_FUN_PIC_Y);//密码功能模式pic
			break;		
	case MANUAL_IO_TEST_MODE:   //io测试模式
			//F1OkIconUp_dis(F1_BUTTON_X,F1_BUTTON_Y);//F1完成
			F2ExitIconUp_dis(F2_BUTTON_X,F2_BUTTON_Y);//F2up退出
			//---------
			break;		
	}
//.........................解释 框
if(WorkMode_temp!=mode)
	{
	WorkMode_temp=mode;
	ModeName_dis(mode);
	//-------------红外----
	IR_Up_flag=0;
	IR_Down_flag=0;
	}
}
void MainModeIcon_dis(Int16U mode)	// ------------主模式 icon显示 PragramModeIcon_dis
{
Int16U x,y,back_color;
switch(mode)
	{
	case MANUAL_MODE:	//手动模式..............
			MachinePic_dis(MACHINE_PIC_X,MACHINE_PIC_Y);//手动模式下 机器图片
			ManualIconDown_dis(MANUAL_BUTT_X, MANUAL_BUTT_Y);//手动up
			AutoIconUp_dis(AUTO_BUTT_X,AUTO_BUTT_Y);//自动up
			FindIconUp_dis(FIND_BUTT_X,FIND_BUTT_Y);//查找up
			break;
	case AUTO_MODE://自动模式..............
			ManualIconUp_dis(MANUAL_BUTT_X, MANUAL_BUTT_Y);//手动up
			AutoIconDown_dis(AUTO_BUTT_X,AUTO_BUTT_Y);//自动up
			FindIconUp_dis(FIND_BUTT_X,FIND_BUTT_Y);//查找up
			DatasTableFunPic_dis( TABLE_FUN_PIC_X,  TABLE_FUN_PIC_Y);//列表模式pic
			break;
	case READ_PRO_MODE:		//查找模式..............
			ManualIconUp_dis(MANUAL_BUTT_X, MANUAL_BUTT_Y);//手动up
			AutoIconUp_dis(AUTO_BUTT_X,AUTO_BUTT_Y);//自动up
			FindIconDown_dis(FIND_BUTT_X,FIND_BUTT_Y);//查找up
			break;
	case SELF_CUT_MODE:  //自刀主 模式
	case TEACH_MODE://示教 模式
			ManualIconUp_dis(MANUAL_BUTT_X, MANUAL_BUTT_Y);//手动up
			AutoIconUp_dis(AUTO_BUTT_X,AUTO_BUTT_Y);//自动up
			FindIconUp_dis(FIND_BUTT_X,FIND_BUTT_Y);//查找up
			break;
	}
// RunButtonDisExec();	//运行 按钮 显示处理
//-----sub mode
SubModeIcon_dis(mode);//--------子模式  icon显示
}


//-----------各个 模式下 画面内容page  显示************************
void ClrSizeTable_dis(void)	//清除 刀数据列表
{
Int16U x1,y1,x2,y2,back_color;
back_color=TEXT_TAB_BACK_COLOR;
x1=RIGHT_ARROW_X,y1=RIGHT_ARROW_Y;
x2=DATA_TABLE_END_X,y2=RIGHT_ARROW_Y+Kf_Line_HIGH*PageKf_Size-20;
GLCD_SetWindow_Fill(x1,y1,x2,y2,back_color,back_color);//空白列表
}
void ProgModePage_dis(void)  //编程模式 部分画面更新++++++++++
{
// ClrSizeTable_dis();//刀数据 列表空白
MiddlePage_dis();//空白
//主模式......
MainModeIcon_dis(WorkMode);//编程模式..............

//---------------Schedule
Schedule_dis(SCHEDULE_X,SCHEDULE_Y);//进度
ProgressBar_dis(OnePro_head.pro_knifeSUM,Knife_order);  //进度条 显示
}
void AutoModePage_dis(void) //自动模式 部分画面显示++++++++++++
{
// ClrSizeTable_dis();//刀数据 列表空白
MiddlePage_dis();//空白
//主模式......
MainModeIcon_dis(WorkMode);//自动模式.........

//---------------Schedule
Schedule_dis(SCHEDULE_X,SCHEDULE_Y);//进度
ProgressBar_dis(OnePro_head.pro_knifeSUM,Knife_order);  //进度条 显示
}
void AutoCutModePage_dis(void) //自刀模式 部分画面显示+++++++++++
{
// ClrSizeTable_dis();//刀数据 列表空白
MiddlePage_dis();//空白
//主模式......
MainModeIcon_dis(WorkMode);//自刀模式...........
//---------------Schedule
Schedule_dis(SCHEDULE_X,SCHEDULE_Y);//进度
ProgressBar_dis(OnePro_head.pro_knifeSUM,Knife_order);  //进度条 显示
}
void ManualModePage_dis(void)  //手动模式 部分画面++++++++++++
{
// ClrSizeTable_dis();//刀数据 列表空白
MiddlePage_dis();//空白
//主模式......

MainModeIcon_dis(WorkMode);//手动模式........

// color=0x9cd3;
// GLCD_SetWindow_Fill(F4_X,F4_Y,F4_X+48,F4_Y+48,color,color);  //隐藏F4
// color=0xce79;
// GLCD_SetWindow_Fill(DELETE_X,DELETE_Y,DELETE_X+272,DELETE_Y+32,color,color);//隐藏DELETE

// ElectricalWheel_dis();  //电子手轮  开关状态
// Manual_dis(MANUAL_X,MANUAL_Y);
}
void TeachModePage_dis(void)   //示教模式  部分页面++++++++++++
{
// ClrSizeTable_dis();//刀数据 列表空白
MiddlePage_dis();//空白
//主模式......
MainModeIcon_dis(WorkMode);//示教模式...........
// FrontPage_Up_dis( FRONT_PAGE_X,  FRONT_PAGE_Y);//前一页up
// BackPage_Up_dis( BACK_PAGE_X,  BACK_PAGE_Y);//后一页up
// UpArrow_Up_dis( UP_ARROW_X,  UP_ARROW_Y);//上箭头up
// DownArrow_Up_dis( DOWN_ARROW_X,  DOWN_ARROW_Y);//下箭头up

// color=0xce79;
// GLCD_SetWindow_Fill(STOP_X,STOP_Y,STOP_X+82,STOP_Y+32,color,color);

//---------------Schedule
Schedule_dis(SCHEDULE_X,SCHEDULE_Y);//进度
ProgressBar_dis(OnePro_head.pro_knifeSUM,Knife_order);  //进度条 显示
}



//**************************************编程 下
void ProgSet_dis(Int32U size, Int16U x, Int16U y, Int8U set_flag)// 参数设定页内 选项数据显示
{
Int8U num[8],k,int_flag=0;//0xef9f;
Int16U back_color=TEXT_TAB_BACK_COLOR; //文本页  背景色
switch(WorkMode)
	{
	case AUTO_LABEL_MODE://已在 标签画面		
	case TEACH_LABEL_MODE://已在 标签画面		
	// // case PROG_DIVIDE_MODE://已在 等分画面 		
	case TEACH_DIVIDE_MODE://已在 等分画面 		
	case AUTO_DIVIDE_MODE://已在 等分画面 		
		
	// // case AUTO_TOOLS_MODE:// 已在  自动 -------参数模式
	// // case SELF_TOOLS_MODE:// 已在  自刀 -------参数模式
	case MANUAL_TOOLS_MODE:// 手动 参数模式
			
		if((WorkMode==AUTO_DIVIDE_MODE)||(WorkMode==TEACH_DIVIDE_MODE)) //等分
			{
			if(DivideValue_flag==0)//等分数
				{
				if(PorgSet_sel==1)
					{
					num[0]=size/1000+48;
					num[1]=(size/100)%10+48;
					num[2]=(size/10)%10+48;
					num[3]=size%10+48;
					// num[4]=' ';
					// num[5]=' ';
					// num[6]=' ';
					num[4]=0;
					int_flag=1;
					}
				else
					int_flag=0;
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
   Printf24(num,x,y,WHITE_COLOR,1,BLUE_COLOR);//
   }
else 
   {
	Printf24(num,x,y,BLACK_COLOR,1,back_color);//
   }
}

void ProgSetNull_dis(Int16U x, Int16U y, Int8U set_flag)//参数不显示----------20190114
{
Int16U tx_wide=88;
Int16U back_color=TEXT_TAB_BACK_COLOR; //文本页  背景色
Int16U front_color=BLACK_COLOR;
if(set_flag==1)//
   {
   back_color=BLUE_COLOR;
   front_color=RED_COLOR;
   //**********提示--无效********
	switch(Language)
		{
		case CHN_HAN:
			Printf24("此版本无效!     ",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,BLACK_COLOR,0,0xffff);
			break;
		case ENGLISH:
		case INDONSIA:	//印尼	
		case PORTUGAL:	//葡萄牙
		case SPANISH: //西班牙	
			Printf24("invalid!",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,BLACK_COLOR,0,0xffff);
			break;
		}	
   }
else 
   {
	back_color=TEXT_TAB_BACK_COLOR;
	front_color=BLUE_COLOR;   
   }
   //---------
GLCD_SetWindow_Fill( x, y, x+tx_wide+16, y+24, TEXT_TAB_BACK_COLOR, TEXT_TAB_BACK_COLOR);//clear text win   
switch(Language)
	{
	case CHN_HAN:
		Printf24(" 无 ",x,y,front_color,1,back_color); //
			break;
	case ENGLISH:
	case INDONSIA:	//印尼
	case PORTUGAL:	//葡萄牙
	case SPANISH: //西班牙
		Printf24("null",x,y,front_color,1,back_color); //
			break;
	}
}

void F1_LabelPage_dis(void)  //F1--标签模式 画面显示.........................
{
volatile Int16U x,y,gap;
Int16U back_color;
x=TOTAL_SIZE_X-150,y=TOTAL_SIZE_Y,gap=ROW_GAP1;
CurrentArea_save2(MIDDLE_PAGE_X , MIDDLE_PAGE_Y,  M_PAGE_WIDE, M_PAGE_HIGH);
MiddlePage_dis();//中间活页

SubModeIcon_dis(WorkMode);   //标签模式
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
	case INDONSIA:	//印尼
		Printf24("Total-Panja:",x,y,BLACK_COLOR,0,0xffff);y+=gap;
		Printf24("Label：",x,y,BLACK_COLOR,0,0xffff);y+=gap;
		Printf24("Memangkas：",x,y,BLACK_COLOR,0,0xffff);
			break;
	case PORTUGAL:	//葡萄牙
		Printf24("Total:",x,y,BLACK_COLOR,0,0xffff);y+=gap;
		Printf24("etiqueta:",x,y,BLACK_COLOR,0,0xffff);y+=gap;
		Printf24("descartar:",x,y,BLACK_COLOR,0,0xffff);
			break;
	case SPANISH: //西班牙
		Printf24("longitud:",x,y,BLACK_COLOR,0,0xffff);y+=gap;
		Printf24("etiqueta:",x,y,BLACK_COLOR,0,0xffff);y+=gap;
		Printf24("descartar:",x,y,BLACK_COLOR,0,0xffff);
			break;
	}	
ProgSet_dis( 0, TOTAL_SIZE_X,  TOTAL_SIZE_Y,1);//
ProgSet_dis( 0, LABEL_SIZE_X,  LABEL_SIZE_Y,0);
ProgSet_dis( 0, WASTE_SIZE_X,  WASTE_SIZE_Y,0);
}

void F2_DividePage_dis(void)  //F2--等分模式 画面显示
{
// volatile Int16U x,y,gap;
// Int16U back_color;
// x=TOTAL_SIZE_X-150,y=TOTAL_SIZE_Y,gap=ROW_GAP2;
CurrentArea_save2(MIDDLE_PAGE_X , MIDDLE_PAGE_Y,  M_PAGE_WIDE, M_PAGE_HIGH);
MiddlePage_dis();//中间活页
DivideValue_flag=0;
DivideTypeSelExec();	//等分 类型  选择........

}

void SearchProgPage_dis(void) //F3--程序选择 画面显示
{
volatile Int16U x,y,i;
Int16U line_color=BLACK_COLOR,back_color=TEXT_TAB_BACK_COLOR;
x=F3_PRO_CAPTION_X,y=F3_PRO_CAPTION_Y;
// CurrentArea_save2(MIDDLE_PAGE_X , MIDDLE_PAGE_Y,  M_PAGE_WIDE, M_PAGE_HIGH);
MiddlePage_dis();//中间活页
//主模式......
DisAllProgMode=PRO_BY_NUM;
MainModeIcon_dis(WorkMode);//程序选择模式
// SubModeIcon_dis(WorkMode);   
switch(Language)
	{
	case CHN_HAN:
		Printf16("序号        名称",x,y,line_color,0,back_color);	x+=300;
		Printf16("步骤        修改日期",x,y,line_color,0,back_color);
			break;
	case ENGLISH:	
		Printf16("Order       Name",x,y,line_color,0,back_color);	x+=300;
		Printf16("Step        Modified",x,y,line_color,0,back_color);
			break;
	case INDONSIA:	//印尼	
		Printf16("Tidak.      Nama",x,y,line_color,0,back_color);	x+=300;
		Printf16("Langkah     Modifikasi",x,y,line_color,0,back_color);
			break;
	case PORTUGAL:	//葡萄牙
		Printf16("N?o.        Nome",x,y,line_color,0,back_color);	
		ASCII_Printf("a",ASCII16_MODE,8,16,PUTAO_ZK16,x+8,y,line_color,back_color);
		x+=300;
		Printf16("Passo    	  Data",x,y,line_color,0,back_color);
			break;
	case SPANISH: //西班牙
		Printf16("No.        Nombre",x,y,line_color,0,back_color);	
		x+=300;
		Printf16("Paso    	  Fecha",x,y,line_color,0,back_color);
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
		case INDONSIA:	//印尼
				Printf24("Rentang nilai      untuk",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,BLACK_COLOR,0,0xffff);
						break;
		case PORTUGAL:	//葡萄牙
				Printf16("Intervalo de dados           --",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,BLACK_COLOR,0,0xffff);
						break;
		case SPANISH: //西班牙
				Printf16("Rango de datos               --",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,BLACK_COLOR,0,0xffff);
						break;
		}
Printf24("1          500",REMIND_WINDOW_X+180,REMIND_WINDOW_Y+5,RED_COLOR,0,0xffff);

//-------------------------程序列表初始化
for(i=1;i<=MAX_PROG;i++)
	ProNumGroup[i]=i;
prog_order=1;
}

//F4 添加标记 功能
void AllFlagRemind(void)	//F4 标记模式提示
{
GLCD_SetWindow_Fill( REMIND_WINDOW_X, REMIND_WINDOW_Y, REMIND_WINDOW_X+REMIND_LENGTH, REMIND_WINDOW_Y+30, 0xfffff, 0xffff);//提示框
switch(Language)
		{
		case CHN_HAN:
			Printf16("S1-推纸,S2-理纸,S3-压纸,S4-刀,S5-多刀",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,BLACK_COLOR,0,0xffff);
				break;
		case ENGLISH:	
		case PORTUGAL:	//葡萄牙
		case SPANISH: //西班牙
				//break;
		case INDONSIA:	//印尼
			//Printf16("F1-udara,F2-memukul,F3-mengat,F4-Dorong,F5-pisau",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,BLACK_COLOR,0,0xffff);
			Printf16("S1-PUSH,S2-SORT,S3-PRE,S4-KNIFE,S5-KNIFES",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,BLACK_COLOR,0,0xffff);
				break;
		}
}

//F4标记模式进入
void Set_AllFlagWind_In(Int8U row)
{
/***	
volatile Int16U x,y,x1,x2,x3,y1,y2;
Int16U back_color;
Int16U fill_color,line_color;
fill_color=0xFF5b,line_color=BLUE_COLOR;
ButtonTouch_mode=TOU_MODE_F4;
x=ALL_FLAG_WIN_BASE_X;
y=ALL_FLAG_WIN_BASE_Y+row*Kf_Line_HIGH;
CurrentArea_save1(x,y, ALL_FLAG_WIN_WIDE,ALL_FLAG_WIN_HIGH);
GLCD_SetWindow_Fill(x, y, x+ALL_FLAG_WIN_WIDE-1, y+ALL_FLAG_WIN_HIGH-1, line_color, fill_color);
x1=F1_AIR_BED_X,y1=F1_AIR_BED_Y+row*Kf_Line_HIGH;
F1AirBedButt_dis(x1, y1);//F1气垫butt 标志
x2=x1+FLAG_BUTT_GAPX;
F2PrePaperButt_dis(x2, y1);//F2压纸butt 标志
x3=x2+FLAG_BUTT_GAPX;
F3SortPaperButt_dis(x3, y1);//F3理纸butt 标志
y2=y1+FLAG_BUTT_GAPY;
F4PushPaperButt_dis(x1, y2);//F4推纸butt 标志
F5RedKnifeButt_dis(x2, y2);//F5红刀butt 标志
F6ExitButtUp_dis(x3, y2);//F6Exit butt 标志
***/
volatile Int16U x,y;
x=ALL_FLAG_WIN_BASE_X;
y=ALL_FLAG_WIN_BASE_Y;
CurrentArea_save1(x,y, ALL_FLAG_WIN_WIDE,ALL_FLAG_WIN_HIGH);
if(WorkMode==AUTO_MODE)
	WorkMode=AUTO_FLAG_MODE;	//标记 模式
else
	WorkMode=TEACH_FLAG_MODE;	//标记 模式
ButtonTouch_mode=TOU_MODE_F4;
ModeName_dis(WorkMode);//mode name
AllFlagsWind_dis( x,  y);//标记wind
AllFlagRemind();	//F4 标记模式提示
/***
//ttttset测试位置标定-----
x=S1_PUSH_PAPER_X,y=S1_PUSH_PAPER_Y;
GLCD_SetWindow(x,y,	x+ALL_FLAG_BUTT_WIDE,y+ALL_FLAG_BUTT_HIGH,0);y=S2_SORT_PAPER_Y;
GLCD_SetWindow(x,y,	x+ALL_FLAG_BUTT_WIDE,y+ALL_FLAG_BUTT_HIGH,0);y=S3_PRE_PAPER_Y;
GLCD_SetWindow(x,y,	x+ALL_FLAG_BUTT_WIDE,y+ALL_FLAG_BUTT_HIGH,0);y=S4_RED_KNIFE_Y;
GLCD_SetWindow(x,y,	x+ALL_FLAG_BUTT_WIDE,y+ALL_FLAG_BUTT_HIGH,0);y=S5_ALL_KNIFE_Y;
GLCD_SetWindow(x,y,	x+ALL_FLAG_BUTT_WIDE,y+ALL_FLAG_BUTT_HIGH,0);y=S6_CLR_FLG_Y;
GLCD_SetWindow(x,y,	x+ALL_FLAG_BUTT_WIDE,y+ALL_FLAG_BUTT_HIGH,0);
x=F2_CLOSE_FLAG_WIN_X,y=F2_CLOSE_FLAG_WIN_Y;
GLCD_SetWindow(x,y,	x+F2_CLOSE_FLAG_WIN_WIDE,y+F2_CLOSE_FLAG_WIN_HIGH,0);
**/
}

void Set_AllFlagWind_Exit(Int8U row)
{
volatile Int16U x,y;
x=ALL_FLAG_WIN_BASE_X;
y=ALL_FLAG_WIN_BASE_Y;
CurrentArea_recover1(x,y, ALL_FLAG_WIN_WIDE,ALL_FLAG_WIN_HIGH);
if(WorkMode==AUTO_FLAG_MODE)//PROG_FLAG_MODE
	{
	WorkMode=AUTO_MODE;//PROG_MODE;		//编程 模式
	}
else
	{
	WorkMode=TEACH_MODE;	//示教 模式
	}
ButtonTouch_mode=0;
ProgressBar_dis(OnePro_head.pro_knifeSUM,Knife_order);  //进度条 显示
ModeName_dis(WorkMode);//mode name
PromptNum_dis();//输入范围
PromptDis_flag=1;
}


//******************************************手 ，自动 ，自刀 下
void ParameterPage1_dis(Int8U sel, Int8U flag) //参数 设置显示1
{
volatile Int16U x,y,gap,tx_wide=88;
Int16U front_color,back_color;
gap=PARA_ROW_GAP;x=PARA_START_X2+(sel/7)*PARA_COL_WIDE;
Int32U temp;
if(flag==1)
    {
	front_color=WHITE_COLOR;//;
	back_color=BLUE_COLOR;
	}
else
	{
	front_color=BLACK_COLOR;
	back_color=TEXT_TAB_BACK_COLOR;//0xef9f;
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
				case INDONSIA:	//印尼
					Printf24("Rentang nilai      untuk",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,BLACK_COLOR,0,0xffff);
						break;
				case PORTUGAL:	//葡萄牙
					Printf16("Intervalo de dados           --",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,BLACK_COLOR,0,0xffff);
						break;
				case SPANISH: //西班牙
					Printf16("Rango de datos               --",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,BLACK_COLOR,0,0xffff);
						break;
				}
			if(Unit==UNIT_MM)
				Printf24("15         120",REMIND_WINDOW_X+180,REMIND_WINDOW_Y+5,RED_COLOR,0,0xffff);//80
			else
				Printf24("0.6        4.72",REMIND_WINDOW_X+180,REMIND_WINDOW_Y+5,RED_COLOR,0,0xffff);//3.15
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
				case INDONSIA:	//印尼
					Printf24("Rentang nilai      untuk",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,BLACK_COLOR,0,0xffff);
						break;
				case PORTUGAL:	//葡萄牙
					Printf16("Intervalo de dados           --",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,BLACK_COLOR,0,0xffff);
						break;
				case SPANISH: //西班牙
					Printf16("Rango de datos               --",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,BLACK_COLOR,0,0xffff);
						break;
				}
			if(Unit==UNIT_MM)
				Printf24("30     	   150",REMIND_WINDOW_X+180,REMIND_WINDOW_Y+5,RED_COLOR,0,0xffff);
			else
				Printf24("1.19        5.9",REMIND_WINDOW_X+180,REMIND_WINDOW_Y+5,RED_COLOR,0,0xffff);
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
				case INDONSIA:	//印尼
					Printf24("Rentang nilai      untuk",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,BLACK_COLOR,0,0xffff);
						break;
				case PORTUGAL:	//葡萄牙
					Printf16("Intervalo de dados           --",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,BLACK_COLOR,0,0xffff);
						break;
				case SPANISH: //西班牙
					Printf16("Rango de datos               --",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,BLACK_COLOR,0,0xffff);
						break;
				}
			if(Unit==UNIT_MM)	
				Printf24("500        2200",REMIND_WINDOW_X+180,REMIND_WINDOW_Y+5,RED_COLOR,0,0xffff);
			else
				Printf24("23.63      86.61",REMIND_WINDOW_X+180,REMIND_WINDOW_Y+5,RED_COLOR,0,0xffff);
			}
		break;
	case 3:
		GLCD_SetWindow_Fill( x, y, x+tx_wide, y+24, TEXT_TAB_BACK_COLOR, TEXT_TAB_BACK_COLOR);//clear text win
		switch(Language)
			{
			case CHN_HAN:
				Printf24(" 中文",x,y,front_color,1,back_color); //语言
					break;
			case ENGLISH:
				Printf24("English",x,y,front_color,1,back_color); //语言
					break;
			case INDONSIA:
				Printf24("Indones",x,y,front_color,1,back_color); //语言
					break;		
			case PORTUGAL:	//葡萄牙
				Printf24("Portuga",x,y,front_color,1,back_color); //语言
				// Printf16("portuguê",x,y,front_color,1,back_color); //语言
				// Printf16("        s",x,y,front_color,0,back_color); //语言
					break;
			case SPANISH: //西班牙
				Printf24("Espa?a",x,y,front_color,1,back_color); //语言
				ASCII_Printf("n",ASCII24_MODE,12,24,PUTAO_ZK24,x+12*4,y,front_color, back_color);
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
				case INDONSIA:	//印尼
					Printf16("Tekan tombol Insert untuk beralih bahasa",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,BLACK_COLOR,0,0xffff);
						break;	
				case PORTUGAL:	//葡萄牙
					Printf16("Pressione a tecla Insert para alternar idiomas",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,BLACK_COLOR,0,0xffff);
						break;	
				case SPANISH: //西班牙
					Printf16("Pulse la tecla Insertar para interruptor",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,BLACK_COLOR,0,0xffff);
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
				case INDONSIA:	//印尼
					Printf16("Tekan tombol Insert untuk beralih unit",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,BLACK_COLOR,0,0xffff);
						break;	
				case PORTUGAL:	//葡萄牙
					Printf16("Pressione a tecla Insert para comutar a unidade",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,BLACK_COLOR,0,0xffff);
						break;	
				case SPANISH: //西班牙	
					Printf16("Pulse la tecla Insert para cambiar la unidad",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,BLACK_COLOR,0,0xffff);
						break;		
				}
			}	
		break;
	case 5:  //提前量
		if(Unit==UNIT_MM)//mm  单位
			temp=Aheader;
		else
			temp=Aheader*100/254;
		if(MotorType<MOTOR_AC_SERVO)
			{
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
					case INDONSIA:	//印尼
						Printf24("Rentang nilai      untuk",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,BLACK_COLOR,0,0xffff);
							break;
					case PORTUGAL:	//葡萄牙
						Printf16("Intervalo de dados           --",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,BLACK_COLOR,0,0xffff);
							break;
					case SPANISH: //西班牙
						Printf16("Rango de datos               --",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,BLACK_COLOR,0,0xffff);
							break;
					}
				if(Unit==UNIT_MM)
					Printf24("0         1",REMIND_WINDOW_X+200,REMIND_WINDOW_Y+5,RED_COLOR,0,0xffff);
				else
					Printf24("0        0.038",REMIND_WINDOW_X+200,REMIND_WINDOW_Y+5,RED_COLOR,0,0xffff);
				}	
			}
		else//交流伺服
			{
			ProgSetNull_dis( x,  y,  flag);//参数不显示----------20190114
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
				case INDONSIA:	//印尼
					Printf24("Efekti    -    ,cacat  0-    ",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,BLACK_COLOR,0,0xffff);
						break;
				case PORTUGAL:	//葡萄牙
				case SPANISH: //西班牙
					Printf24("eficaz    -   ,invá            ",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,BLACK_COLOR,0,0xffff);
					Printf24("                   li",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,BLACK_COLOR,0,0xffff);//inválido
					Printf24("                     do(0-     )",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,BLACK_COLOR,0,0xffff);//inválido
						break;
				}
			if(Unit==UNIT_MM)
				Printf24("11   500            10",REMIND_WINDOW_X+85,REMIND_WINDOW_Y+5,RED_COLOR,0,0xffff);
			else
				Printf24("0.44  19            0.4",REMIND_WINDOW_X+82,REMIND_WINDOW_Y+5,RED_COLOR,0,0xffff);	
			}
		break;
	case 7:  //压纸有效 标志
		GLCD_SetWindow_Fill( x, y, x+tx_wide+16, y+24, TEXT_TAB_BACK_COLOR, TEXT_TAB_BACK_COLOR);//clear text win
		if(PressValid_flag==0)
			{
			switch(Language)
				{
				case CHN_HAN:
					Printf24(" 无效  ",x,y,front_color,1,back_color); //
						break;
				case ENGLISH:
					Printf24("Invalid",x,y,front_color,1,back_color); //
						break;
				case INDONSIA:	//印尼
					Printf24(" Cacat ",x,y,front_color,1,back_color); //
						break;
				case PORTUGAL:	//葡萄牙
				case SPANISH: //西班牙
					Printf24("invá   ",x,y,front_color,1,back_color); //
					Printf24("    li",x,y,front_color,0,back_color); //inválido
					Printf24("      do",x,y,front_color,0,back_color); //
						break;
				}		
			}
		else 
			{
			switch(Language)
				{
				case CHN_HAN:
					Printf24(" 有效 ",x,y,front_color,1,back_color); //
						break;
				case ENGLISH:
					Printf24("Valid ",x,y,front_color,1,back_color); //
						break;
				case INDONSIA:	//印尼
					Printf24("Efekti",x,y,front_color,1,back_color); //
						break;
				case PORTUGAL:	//葡萄牙
				case SPANISH: //西班牙
					Printf24("eficaz",x,y,front_color,1,back_color); //
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
				case INDONSIA:	//印尼	
					Printf16("Tekan tombol Insert,Platen berhenti",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,BLACK_COLOR,0,0xffff);
					break;
				case PORTUGAL:	//葡萄牙
					Printf16("Pressione a tecla Insert, a fun??o comuta??o",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,BLACK_COLOR,0,0xffff);
					ASCII_Printf("ca",ASCII16_MODE,8,16,PUTAO_ZK16, REMIND_WINDOW_X+10+(31*8),REMIND_WINDOW_Y+5,BLACK_COLOR,0xffff);
					ASCII_Printf("ca",ASCII16_MODE,8,16,PUTAO_ZK16, REMIND_WINDOW_X+10+(41*8),REMIND_WINDOW_Y+5,BLACK_COLOR,0xffff);
					break;
				case SPANISH: //西班牙
					Printf16("Pulse la tecla Insert cambiar stop",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,BLACK_COLOR,0,0xffff);
					break;
				}
			}
		break;	
	case 8: //	关气阀距离-------
		if(Unit==UNIT_MM)//mm  单位
			temp=AirOffDistance;
		else
			temp=AirOffDistance*100/254;
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
				case INDONSIA:	//印尼
					Printf24("Rentang nilai      untuk",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,BLACK_COLOR,0,0xffff);
					break;
				case PORTUGAL:	//葡萄牙
					Printf16("Intervalo de dados           --",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,BLACK_COLOR,0,0xffff);
						break;
				case SPANISH: //西班牙
					Printf16("Rango de datos               --",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,BLACK_COLOR,0,0xffff);
						break;
				}
			if(Unit==UNIT_MM)
				Printf24("0           10",REMIND_WINDOW_X+200,REMIND_WINDOW_Y+5,RED_COLOR,0,0xffff);
			else
				Printf24("0           0.4",REMIND_WINDOW_X+200,REMIND_WINDOW_Y+5,RED_COLOR,0,0xffff);	
			}
		break;	
		//--------------------------------直流伺服设定速度
	case 9: //	最大速度+红外有效
		switch(MotorType)
			{
			case MOTOR_FREQ_5_SPD_RST:
			case MOTOR_FREQ_3_SPD:
			case MOTOR_FREQ_3_SPD_RST:	//变频
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
						case INDONSIA:	//印尼
							Printf24("Tinggi",x,y,front_color,1,back_color); //
								break;
						case PORTUGAL:	//葡萄牙
						case SPANISH: //西班牙
							Printf24("alto",x,y,front_color,1,back_color); //
								break;
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
						case INDONSIA:	//印尼
							Printf24("Rendah",x,y,front_color,1,back_color); //
								break;
						case PORTUGAL:	//葡萄牙
							Printf24("baixo",x,y,front_color,1,back_color); //
								break;
						case SPANISH: //西班牙
							Printf24("bajo",x,y,front_color,1,back_color); //
								break;
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
						case INDONSIA:	//印尼	
							Printf16("Tekan tombol Insert,Switching Status IR",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,BLACK_COLOR,0,0xffff);
							break;
						case PORTUGAL:	//葡萄牙
							Printf16("Pressione a tecla Insert para ligar o sinal IR",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,BLACK_COLOR,0,0xffff);
							break;
						case SPANISH: //西班牙
							Printf16("Pulse la tecla Insert para cambiar IR",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,BLACK_COLOR,0,0xffff);
							break;
						}
					}
					break;
			// // case MOTOR_DC_SERVO:
			// // case MOTOR_DC670_SERVO:
				// // if(Unit==UNIT_MM)//mm  单位
					// // temp=ServoSpeed_order*100;
				// // else
					// // temp=ServoSpeed_order*1000;
				// // ProgSet_dis(temp,  x,  y,  flag);
				// // //-----------------------------提示
				// // if(flag==1)
					// // {
					// // switch(Language)
						// // {
						// // case CHN_HAN:
							// // Printf24("输入数据范围        到",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,BLACK_COLOR,0,0xffff);
							// // break;
						// // case ENGLISH:	
							// // Printf24("Data range          to ",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,BLACK_COLOR,0,0xffff);
							// // break;
						// // case INDONSIA:	//印尼
							// // Printf24("Rentang nilai      untuk",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,BLACK_COLOR,0,0xffff);
							// // break;
						// // case PORTUGAL:	//葡萄牙
							// // Printf16("Intervalo de dados           --",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,BLACK_COLOR,0,0xffff);
							// // break;
						// // case SPANISH: //西班牙
							// // Printf16("Rango de datos               --",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,BLACK_COLOR,0,0xffff);
							// // break;
						// // }
					// // Printf24("13       20",REMIND_WINDOW_X+200,REMIND_WINDOW_Y+5,RED_COLOR,0,0xffff);	
					// // }	
					// // break;
			case MOTOR_AC_SERVO:
			case MOTOR_AC_SERVO_REV:
				if(Unit==UNIT_MM)//mm  单位
					temp=AC_MotorSPD*100;
				else
					temp=AC_MotorSPD*1000;
				ProgSet_dis(temp,  x,  y,  flag);
				//-----------------------------提示
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
						case INDONSIA:	//印尼
							Printf24("Rentang nilai      untuk",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,BLACK_COLOR,0,0xffff);
							break;
						case PORTUGAL:	//葡萄牙
							Printf16("Intervalo de dados           --",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,BLACK_COLOR,0,0xffff);
							break;
						case SPANISH: //西班牙
							Printf16("Rango de datos               --",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,BLACK_COLOR,0,0xffff);
							break;
						}
					Printf24("0        32",REMIND_WINDOW_X+200,REMIND_WINDOW_Y+5,RED_COLOR,0,0xffff);	
					}
					break;
			}		
		break;
	case 10: //	点动速度
		switch(MotorType)
			{
			case MOTOR_FREQ_5_SPD_RST:
			case MOTOR_FREQ_3_SPD:
			case MOTOR_FREQ_3_SPD_RST:	//变频
				
					break;
			// // case MOTOR_DC_SERVO:
			// // case MOTOR_DC670_SERVO:
				// // ProgSet_dis(JogSpeed_order*100,  x,  y,  flag);
				// // if(flag==1)
					// // {
					// // switch(Language)
						// // {
						// // case CHN_HAN:
							// // Printf24("输入数据范围        到",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,BLACK_COLOR,0,0xffff);
							// // break;
						// // case ENGLISH:	
							// // Printf24("Data range          to ",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,BLACK_COLOR,0,0xffff);
							// // break;
						// // case INDONSIA:	//印尼
							// // Printf24("Rentang nilai      untuk",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,BLACK_COLOR,0,0xffff);
							// // break;
						// // case PORTUGAL:	//葡萄牙
							// // Printf16("Intervalo de dados           --",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,BLACK_COLOR,0,0xffff);
							// // break;
						// // case SPANISH: //西班牙
							// // Printf16("Rango de datos               --",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,BLACK_COLOR,0,0xffff);
							// // break;
						// // }
					// // Printf24("10       20",REMIND_WINDOW_X+200,REMIND_WINDOW_Y+5,RED_COLOR,0,0xffff);
					// // }	
					// // break;
			case MOTOR_AC_SERVO:
			case MOTOR_AC_SERVO_REV:
				GLCD_SetWindow_Fill( x, y, x+tx_wide, y+24, TEXT_TAB_BACK_COLOR, TEXT_TAB_BACK_COLOR);//clear text win
				if(IR_SensorStus==1)		//红外  有效电平
					{
					switch(Language)
						{
						case CHN_HAN:
							Printf24("高有效",x,y,front_color,1,back_color); //
								break;
						case ENGLISH:
							Printf24("High  ",x,y,front_color,1,back_color); //
								break;
						case INDONSIA:	//印尼
							Printf24("Tinggi",x,y,front_color,1,back_color); //
								break;
						case PORTUGAL:	//葡萄牙
						case SPANISH: //西班牙
							Printf24("alto",x,y,front_color,1,back_color); //
								break;
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
						case INDONSIA:	//印尼
							Printf24("Rendah",x,y,front_color,1,back_color); //
								break;
						case PORTUGAL:	//葡萄牙
							Printf24("baixo",x,y,front_color,1,back_color); //
								break;
						case SPANISH: //西班牙
							Printf24("bajo",x,y,front_color,1,back_color); //
								break;
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
						case INDONSIA:	//印尼	
							Printf16("Tekan tombol Insert,Switching Status IR",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,BLACK_COLOR,0,0xffff);
							break;
						case PORTUGAL:	//葡萄牙
							Printf16("Pressione a tecla Insert para ligar o sinal IR",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,BLACK_COLOR,0,0xffff);
							break;
						case SPANISH: //西班牙
							Printf16("Pulse la tecla Insert para cambiar IR",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,BLACK_COLOR,0,0xffff);
							break;
						}
					}
					break;
			}	
		break;	
		/***
	case 11: //	//红外  有效电平
		switch(MotorType)
			{
			case MOTOR_FREQ_5_SPD_RST:
			case MOTOR_FREQ_3_SPD:
			case MOTOR_FREQ_3_SPD_RST:	//变频
				
					break;
			case MOTOR_DC_SERVO:
			case MOTOR_DC670_SERVO:
				y+=gap*2;
				if(IR_SensorStus==1)		//红外  有效电平
					{
					switch(Language)
						{
						case CHN_HAN:
							Printf24("高有效",x,y,front_color,1,back_color); //
								break;
						case ENGLISH:
							Printf24("High  ",x,y,front_color,1,back_color); //
								break;
						case INDONSIA:	//印尼
							Printf24("Tinggi",x,y,front_color,1,back_color); //
								break;
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
							Printf24("Low   ",x,y,front_color,1,back_color); //
								break;
						case INDONSIA:	//印尼
							Printf24("Rendah",x,y,front_color,1,back_color); //
								break;
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
						case INDONSIA:	//印尼	
							Printf16("Tekan tombol Insert,Switching Status IR",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,BLACK_COLOR,0,0xffff);
							break;
						}
					}
					
				break;
			case MOTOR_AC_SERVO:
				break;
			}	
		break;	***/
	}
}

void ParameterPage2_dis(Int8U sel, Int8U flag) //参数 设置显示2
{
volatile Int16U x,y,gap,tx_wide=88;
Int16U front_color,back_color;
gap=PARA_ROW_GAP;x=PARA_START_X2+(sel/7)*PARA_COL_WIDE;
Int32U temp;
if(flag==1)
    {
	front_color=WHITE_COLOR;//;
	back_color=BLUE_COLOR;
	}
else
	{
	front_color=BLACK_COLOR;
	back_color=TEXT_TAB_BACK_COLOR;//0xef9f;
	}
y=PARA_START_Y+gap*(sel%7);
GLCD_SetWindow_Fill( REMIND_WINDOW_X, REMIND_WINDOW_Y, REMIND_WINDOW_X+REMIND_LENGTH, REMIND_WINDOW_Y+30, 0xfffff, 0xffff);//提示框

switch(sel)
	{
	case 0://步进距离
		if(Unit==UNIT_MM)//mm  单位
			temp=Step_Size; 
		else
			temp=Step_Size*100/254;
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
				case INDONSIA:	//印尼
					Printf24("Rentang nilai      untuk",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,BLACK_COLOR,0,0xffff);
					break;
				case PORTUGAL:	//葡萄牙
					Printf16("Intervalo de dados           --",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,BLACK_COLOR,0,0xffff);
						break;
				case SPANISH: //西班牙
					Printf16("Rango de datos               --",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,BLACK_COLOR,0,0xffff);
						break;
				}
			if(Unit==UNIT_MM)
				Printf24("0          900",REMIND_WINDOW_X+200,REMIND_WINDOW_Y+5,RED_COLOR,0,0xffff);
			else
				Printf24("0           35",REMIND_WINDOW_X+200,REMIND_WINDOW_Y+5,RED_COLOR,0,0xffff);	
			}
			break;
	case 1://误差掩盖值
		if(Unit==UNIT_MM)//mm  单位
			temp=VirtualTargetSizeGap; 
		else
			temp=VirtualTargetSizeGap*100/254;
		if(MotorType<MOTOR_AC_SERVO)  //变频器--
			{
			ProgSet_dis(temp,  x,  y,  flag);
			if(flag==1)
				{
				if(Unit==UNIT_MM)
					{
					switch(Language)
						{
						case CHN_HAN:
							Printf24("输入数据范围        到",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,BLACK_COLOR,0,0xffff);
							break;
						case ENGLISH:	
							Printf24("Data range          to ",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,BLACK_COLOR,0,0xffff);
							break;
						case INDONSIA:	//印尼
							Printf24("Rentang nilai      untuk",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,BLACK_COLOR,0,0xffff);
							break;
						case PORTUGAL:	//葡萄牙
							Printf16("Intervalo de dados           --",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,BLACK_COLOR,0,0xffff);
								break;
						case SPANISH: //西班牙
							Printf16("Rango de datos               --",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,BLACK_COLOR,0,0xffff);
								break;
						}	
					Printf24("0.3       1",REMIND_WINDOW_X+200,REMIND_WINDOW_Y+5,RED_COLOR,0,0xffff);
					}
				else
					{
					switch(Language)
						{
						case CHN_HAN:
							Printf24("请到公制下输入！",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,RED_COLOR,0,0xffff);
							break;
						case ENGLISH:
						case INDONSIA:	//印尼
						case PORTUGAL:	//葡萄牙
						case SPANISH: //西班牙
							Printf24("Input in mm！",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,RED_COLOR,0,0xffff);
								break;
						}	
					}	
				}	
			}
		else//交流伺服
			{
			ProgSetNull_dis( x,  y,  flag);//参数不显示----------20190114
			}
			break;
	case 2://红外切换工作模式
		GLCD_SetWindow_Fill(x, y, x+tx_wide, y+24, TEXT_TAB_BACK_COLOR, TEXT_TAB_BACK_COLOR);//clear text win
		if(IRChgWorkmodeValid_flag!=0)
			{
			switch(Language)
				{
				case CHN_HAN:
					Printf24("有效",x,y,front_color,1,back_color); //
						break;
				default:
					Printf24("valid",x,y,front_color,1,back_color); //
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
				default:
					Printf24("invalid",x,y,front_color,1,back_color); //
						break;
				}	
			}
		if(flag==1)
			{
			switch(Language)
				{
				case CHN_HAN:
					Printf24("按插入设置IR切换工作模式",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,BLACK_COLOR,0,0xffff);
					break;
				case ENGLISH:	
				case INDONSIA:	//印尼
				case PORTUGAL:	//葡萄牙
				case SPANISH: //西班牙
					Printf24("press INSERT change IR",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,BLACK_COLOR,0,0xffff);
						break;
				}	
			}
			break;
	case 3: //autopress time
		switch(MotorType)
			{
			case MOTOR_FREQ_5_SPD_RST:
			case MOTOR_FREQ_3_SPD:
			case MOTOR_FREQ_3_SPD_RST:	//变频
				ProgSetNull_dis( x,  y,  flag);//参数不显示----------20190114
					break;
			case MOTOR_AC_SERVO:
			case MOTOR_AC_SERVO_REV:
					if(Unit==UNIT_MM)//mm  单位
						temp=AutoPressWork_TimeSet*100;
					else
						temp=AutoPressWork_TimeSet*1000;
					ProgSet_dis(temp,  x,  y,  flag);
					//-----------------------------提示
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
							case INDONSIA:	//印尼
								Printf24("Rentang nilai      untuk",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,BLACK_COLOR,0,0xffff);
								break;
							case PORTUGAL:	//葡萄牙
								Printf16("Intervalo de dados           --",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,BLACK_COLOR,0,0xffff);
								break;
							case SPANISH: //西班牙
								Printf16("Rango de datos               --",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,BLACK_COLOR,0,0xffff);
								break;
							}
						Printf24("1        10",REMIND_WINDOW_X+200,REMIND_WINDOW_Y+5,RED_COLOR,0,0xffff);	
						}
					break;
			}
		break;		
	}
}

void ParamPage1_dis(void) //参数 page1
{
volatile Int16U x,y,gap,n,tx_wide=122;
Int16U back_color=TEXT_TAB_BACK_COLOR;	//0xef9f;
x=PARA_START_X1,y=PARA_START_Y,gap=PARA_ROW_GAP;
MiddlePage_dis();//中间活页
SubModeIcon_dis(WorkMode);   //参数模式
GLCD_SetWindow_Fill( x, y, x+tx_wide, y+(gap*7-10), TEXT_TAB_BACK_COLOR, TEXT_TAB_BACK_COLOR);//clear text win
switch(Language)
	{
	case CHN_HAN:
		Printf16("前极限:    ",x,y,BLACK_COLOR,1,back_color);y+=gap;
		Printf16("中极限:    ",x,y,BLACK_COLOR,1,back_color);y+=gap;
		Printf16("后极限:    ",x,y,BLACK_COLOR,1,back_color);y+=gap;
		Printf16("语言:    ",x,y,BLACK_COLOR,1,back_color);  y+=gap;
		Printf16("单位:",x,y,BLACK_COLOR,1,back_color);  y+=gap;
		Printf16("提前量:  ",x,y,BLACK_COLOR,1,back_color);y+=gap;
		//Printf16("标准距离:   ",x,y,BLACK_COLOR,1,back_color);
		Printf16("推纸距离:   ",x,y,BLACK_COLOR,1,back_color);
		x+=PARA_COL_WIDE;y=PARA_START_Y;
		GLCD_SetWindow_Fill( x, y, x+tx_wide, y+(gap*4-10), TEXT_TAB_BACK_COLOR, TEXT_TAB_BACK_COLOR);//clear text win
		Printf16("压纸停机:   ",x,y,BLACK_COLOR,1,back_color);y+=gap;
		Printf16("关气距离:   ",x,y,BLACK_COLOR,1,back_color);y+=gap;
		switch(MotorType)
			{
			case MOTOR_FREQ_5_SPD_RST:
			case MOTOR_FREQ_3_SPD:
			case MOTOR_FREQ_3_SPD_RST:
				Printf16("光电选择:   ",x,y,BLACK_COLOR,1,back_color);
					break;
			// // case MOTOR_DC_SERVO:
			// // case MOTOR_DC670_SERVO:
				// // Printf16("最大速度:   ",x,y,BLACK_COLOR,1,back_color);y+=gap;
				// // Printf16("点动速度:   ",x,y,BLACK_COLOR,1,back_color);
					// // break;
			case MOTOR_AC_SERVO:
			case MOTOR_AC_SERVO_REV:
				Printf16("运行速度:   ",x,y,BLACK_COLOR,1,back_color);y+=gap;
				Printf16("光电选择:   ",x,y,BLACK_COLOR,1,back_color);
					break;
			}
			break;
	case ENGLISH:	
		Printf16("Front-limit:",x,y,BLACK_COLOR,1,back_color);y+=gap;
		Printf16("Midd-limit:",x,y,BLACK_COLOR,1,back_color);y+=gap;
		Printf16("Back-limit:",x,y,BLACK_COLOR,1,back_color);y+=gap;
		Printf16("Language:",x,y,BLACK_COLOR,1,back_color);  y+=gap;
		Printf16("Unit:",x,y,BLACK_COLOR,1,back_color);  y+=gap;
		Printf16("Advanced:",x,y,BLACK_COLOR,1,back_color);y+=gap;
		Printf16("Push-distan:",x,y,BLACK_COLOR,1,back_color);
		x+=PARA_COL_WIDE;y=PARA_START_Y;
		GLCD_SetWindow_Fill( x, y, x+tx_wide, y+(gap*4-10), TEXT_TAB_BACK_COLOR, TEXT_TAB_BACK_COLOR);//clear text win
		Printf16("Press-Stop:",x,y,BLACK_COLOR,1,back_color);y+=gap;
		Printf16("AirOff-dist:",x,y,BLACK_COLOR,1,back_color);y+=gap;
		switch(MotorType)
			{
			case MOTOR_FREQ_5_SPD_RST:
			case MOTOR_FREQ_3_SPD:
			case MOTOR_FREQ_3_SPD_RST:
				Printf16("IR-Set:   ",x,y,BLACK_COLOR,1,back_color);
					break;
			// // case MOTOR_DC_SERVO:
			// // case MOTOR_DC670_SERVO:
				// // Printf16("Max-speed:",x,y,BLACK_COLOR,1,back_color);y+=gap;
				// // Printf16("Jog-speed:",x,y,BLACK_COLOR,1,back_color);
					// // break;
			case MOTOR_AC_SERVO:
			case MOTOR_AC_SERVO_REV:
				Printf16("Run-speed:",x,y,BLACK_COLOR,1,back_color);y+=gap;
				Printf16("IR-Set:   ",x,y,BLACK_COLOR,1,back_color);
					break;
			}
			break;
	case INDONSIA:	//印尼
		Printf16("Sete-batas:",x,y,BLACK_COLOR,1,back_color);y+=gap;
		Printf16("Dala-batas:",x,y,BLACK_COLOR,1,back_color);y+=gap;
		Printf16("Sebe-batas:",x,y,BLACK_COLOR,1,back_color);y+=gap;
		Printf16("Bahasa:",x,y,BLACK_COLOR,1,back_color);  y+=gap;
		Printf16("Satuan:",x,y,BLACK_COLOR,1,back_color);  y+=gap;
		Printf16("Memajukan:",x,y,BLACK_COLOR,1,back_color);y+=gap;
		Printf16("Doro-jarak:",x,y,BLACK_COLOR,1,back_color);
		x+=PARA_COL_WIDE;y=PARA_START_Y;
		GLCD_SetWindow_Fill( x, y, x+tx_wide, y+(gap*4-10), TEXT_TAB_BACK_COLOR, TEXT_TAB_BACK_COLOR);//clear text win
		Printf16("Plat-bawah:",x,y,BLACK_COLOR,1,back_color);y+=gap;
		Printf16("Off gas da: ",x,y,BLACK_COLOR,1,back_color);y+=gap;
		switch(MotorType)
			{
			case MOTOR_FREQ_5_SPD_RST:
			case MOTOR_FREQ_3_SPD:
			case MOTOR_FREQ_3_SPD_RST:
				Printf16("Set-IR:  ",x,y,BLACK_COLOR,1,back_color);
					break;
			// // case MOTOR_DC_SERVO:
			// // case MOTOR_DC670_SERVO:
				// // Printf16("Tercepat:",x,y,BLACK_COLOR,1,back_color);y+=gap;
				// // Printf16("Jog-kecep:",x,y,BLACK_COLOR,1,back_color);
					// // break;
			case MOTOR_AC_SERVO:
			case MOTOR_AC_SERVO_REV:
				Printf16("Kecepa-lari:",x,y,BLACK_COLOR,1,back_color);y+=gap;
				Printf16("Set-IR:  ",x,y,BLACK_COLOR,1,back_color);
					break;
			}
			break;	
	case PORTUGAL:	//葡萄牙
		Printf16("O ex-limite:",x,y,BLACK_COLOR,1,back_color);y+=gap;
		Printf16("Intermedi:",x,y,BLACK_COLOR,1,back_color);y+=gap;
		Printf16("apó        ",x,y,BLACK_COLOR,1,back_color);
		Printf16("   s-limite:",x,y,BLACK_COLOR,0,back_color);y+=gap;
		Printf16("lí    ",x,y,BLACK_COLOR,1,back_color); 
		Printf16("  ngua:",x,y,BLACK_COLOR,0,back_color);  y+=gap;
		Printf16("unidade:",x,y,BLACK_COLOR,1,back_color);  y+=gap;
		Printf16("antes:",x,y,BLACK_COLOR,1,back_color);y+=gap;
		//Printf16("标准距离:   ",x,y,BLACK_COLOR,1,back_color);
		Printf16("distancia:",x,y,BLACK_COLOR,1,back_color);
		x+=PARA_COL_WIDE;y=PARA_START_Y;
		GLCD_SetWindow_Fill( x, y, x+tx_wide, y+(gap*4-10), TEXT_TAB_BACK_COLOR, TEXT_TAB_BACK_COLOR);//clear text win
		Printf16("encerra:",x,y,BLACK_COLOR,1,back_color);y+=gap;
		Printf16("Off Air:",x,y,BLACK_COLOR,1,back_color);y+=gap;
		switch(MotorType)
			{
			case MOTOR_FREQ_5_SPD_RST:
			case MOTOR_FREQ_3_SPD:
			case MOTOR_FREQ_3_SPD_RST:
				Printf16("estado IR:",x,y,BLACK_COLOR,1,back_color);
					break;
			// // case MOTOR_DC_SERVO:
			// // case MOTOR_DC670_SERVO:
				// // Printf16("Veloci-má  ",x,y,BLACK_COLOR,1,back_color);
				// // Printf16("          x:",x,y,BLACK_COLOR,0,back_color);y+=gap;
				// // Printf16("Veloci-Jog:",x,y,BLACK_COLOR,1,back_color);
					// // break;
			case MOTOR_AC_SERVO:
			case MOTOR_AC_SERVO_REV:
				Printf16("Veloci-corrida:",x,y,BLACK_COLOR,1,back_color);y+=gap;
				Printf16("estado IR:",x,y,BLACK_COLOR,1,back_color);
					break;
			}
			break;	
	case SPANISH: //西班牙
		Printf16("lí      ",x,y,BLACK_COLOR,1,back_color);//límite
		Printf16("  mite ex:",x,y,BLACK_COLOR,0,back_color);y+=gap;
		Printf16("lí      ",x,y,BLACK_COLOR,1,back_color);//límite
		Printf16("  mite Medio:",x,y,BLACK_COLOR,0,back_color);y+=gap;
		Printf16("Tras el lí",x,y,BLACK_COLOR,1,back_color);//límite
		Printf16("          m",x,y,BLACK_COLOR,0,back_color);y+=gap;
		Printf16("idioma",x,y,BLACK_COLOR,1,back_color); 
		y+=gap;
		Printf16("unidad:",x,y,BLACK_COLOR,1,back_color);  y+=gap;
		Printf16("avanzar:",x,y,BLACK_COLOR,1,back_color);y+=gap;
		//Printf16("标准距离:   ",x,y,BLACK_COLOR,1,back_color);
		Printf16("distancia:",x,y,BLACK_COLOR,1,back_color);
		x+=PARA_COL_WIDE;y=PARA_START_Y;
		GLCD_SetWindow_Fill( x, y, x+tx_wide, y+(gap*4-10), TEXT_TAB_BACK_COLOR, TEXT_TAB_BACK_COLOR);//clear text win
		Printf16("cierre:",x,y,BLACK_COLOR,1,back_color);y+=gap;
		Printf16("Off Air:",x,y,BLACK_COLOR,1,back_color);y+=gap;
		switch(MotorType)
			{
			case MOTOR_FREQ_5_SPD_RST:
			case MOTOR_FREQ_3_SPD:
			case MOTOR_FREQ_3_SPD_RST:
				Printf16("estado IR:",x,y,BLACK_COLOR,1,back_color);
					break;
			// // case MOTOR_DC_SERVO:
			// // case MOTOR_DC670_SERVO:
				// // Printf16("Veloci-má  ",x,y,BLACK_COLOR,1,back_color);
				// // Printf16("          x:",x,y,BLACK_COLOR,0,back_color);y+=gap;
				// // Printf16("Veloci-Jog:",x,y,BLACK_COLOR,1,back_color);
					// // break;
			case MOTOR_AC_SERVO:
			case MOTOR_AC_SERVO_REV:
				Printf16("Veloci-corrida:",x,y,BLACK_COLOR,1,back_color);y+=gap;
				Printf16("estado IR:",x,y,BLACK_COLOR,1,back_color);
					break;
			}
			break;	
	}
switch(MotorType)
	{
	case MOTOR_FREQ_5_SPD_RST:
	case MOTOR_FREQ_3_SPD:
	case MOTOR_FREQ_3_SPD_RST:
			for(n=0;n<=9;n++)
				ParameterPage1_dis(n, 0);
			break;
	// // case MOTOR_DC_SERVO:
	// // case MOTOR_DC670_SERVO:
			// // // for(n=1;n<=11;n++)
			// // for(n=0;n<=10;n++)
				// // ParameterPage1_dis(n, 0);
			// // break;
	case MOTOR_AC_SERVO:	
	case MOTOR_AC_SERVO_REV:	
			for(n=0;n<=10;n++)
				ParameterPage1_dis(n, 0);
			break;
	}		 
ParameterPage1_dis(Para_sel, 1);
}

void ParamPage2_dis(void) //参数 page2
{
volatile Int16U x,y,gap,n,tx_wide=122;
Int16U back_color=TEXT_TAB_BACK_COLOR;	//0xef9f;
x=PARA_START_X1,y=PARA_START_Y,gap=PARA_ROW_GAP;
MiddlePage_dis();//中间活页
SubModeIcon_dis(WorkMode);   //参数模式
GLCD_SetWindow_Fill( x, y, x+tx_wide, y+(gap*7-10), TEXT_TAB_BACK_COLOR, TEXT_TAB_BACK_COLOR);//clear text win
switch(Language)
	{
	case CHN_HAN:
		Printf16("步进距离:   ",x,y,BLACK_COLOR,1,back_color);y+=gap;
		Printf16("误差范围:   ",x,y,BLACK_COLOR,1,back_color);y+=gap;
		Printf16("IR切换模式:    ",x,y,BLACK_COLOR,1,back_color);y+=gap;
		Printf16("自压时间:   ",x,y,BLACK_COLOR,1,back_color);y+=gap;
			break;
	case ENGLISH:
	case INDONSIA:	//印尼	
	case PORTUGAL:	//葡萄牙
	case SPANISH: //西班牙
		Printf16("step-dist:   ",x,y,BLACK_COLOR,1,back_color);y+=gap;
		Printf16("Vir_Gap:    ",x,y,BLACK_COLOR,1,back_color);y+=gap;
		Printf16("IR change:    ",x,y,BLACK_COLOR,1,back_color);y+=gap;
		Printf16("Press—Time:  ",x,y,BLACK_COLOR,1,back_color);y+=gap;
			break;
	}
Para2_sel=0;
for(n=0;n<=3;n++)
	ParameterPage2_dis(n, 0);
ParameterPage2_dis(Para2_sel, 1);
}

void F1_ToolsPage_dis(void) //参数 画面
{
CurrentArea_save2(MIDDLE_PAGE_X , MIDDLE_PAGE_Y,  M_PAGE_WIDE, M_PAGE_HIGH);
PramSel_Page=0;
Para_sel=0;
ParamPage1_dis();/**
//-----------------20191115
SetModeEnbByCode_flag=0;
GLCD_SetWindow_Fill(REMIND_WINDOW_X, REMIND_WINDOW_Y, REMIND_WINDOW_X+REMIND_LENGTH, REMIND_WINDOW_Y+30, 0xfffff, 0xffff);//提示框
switch(Language)
	{
	case CHN_HAN:
		Printf24("请输入密码!",REMIND_WINDOW_X,REMIND_WINDOW_Y+5,RED_COLOR,0,0xffff);
			break;
	case ENGLISH:	
		Printf24("Enter passcode!",REMIND_WINDOW_X,REMIND_WINDOW_Y+5,RED_COLOR,0,0xffff);
			break;
	case INDONSIA:	//印尼
		Printf24("Masukkan sandi Anda",REMIND_WINDOW_X,REMIND_WINDOW_Y+5,RED_COLOR,0,0xffff);
			break;
	case PORTUGAL:	//葡萄牙
		Printf24("Por favor, digite uma senha",REMIND_WINDOW_X,REMIND_WINDOW_Y+5,RED_COLOR,0,0xffff);
			break;
	case SPANISH: //西班牙
		Printf24("Introduzca la contrase?a",REMIND_WINDOW_X,REMIND_WINDOW_Y+5,RED_COLOR,0,0xffff);
		ASCII_Printf("n",ASCII24_MODE,12,24,PUTAO_ZK24,REMIND_WINDOW_X+12*22,REMIND_WINDOW_Y+5,RED_COLOR,0xffff);
			break;
	}
Printf32("请输入密码!",150,250,RED_COLOR,0,0xffff);**/
}

void F2_RulerPage_dis(void) //基准 画面
{
CurrentArea_save2(MIDDLE_PAGE_X , MIDDLE_PAGE_Y,  M_PAGE_WIDE, M_PAGE_HIGH);
MiddlePage_dis();//中间活页
SubModeIcon_dis(WorkMode);   //基准模式
//-----------------20191115
SetModeEnbByCode_flag=0;
GLCD_SetWindow_Fill(REMIND_WINDOW_X, REMIND_WINDOW_Y, REMIND_WINDOW_X+REMIND_LENGTH, REMIND_WINDOW_Y+30, 0xfffff, 0xffff);//提示框
switch(Language)
	{
	case CHN_HAN:
		Printf24("请输入密码!",REMIND_WINDOW_X,REMIND_WINDOW_Y+5,RED_COLOR,0,0xffff);
			break;
	case ENGLISH:	
		Printf24("Enter passcode!",REMIND_WINDOW_X,REMIND_WINDOW_Y+5,RED_COLOR,0,0xffff);
			break;
	case INDONSIA:	//印尼
		Printf24("Masukkan sandi Anda",REMIND_WINDOW_X,REMIND_WINDOW_Y+5,RED_COLOR,0,0xffff);
			break;
	case PORTUGAL:	//葡萄牙
		Printf24("Por favor, digite uma senha",REMIND_WINDOW_X,REMIND_WINDOW_Y+5,RED_COLOR,0,0xffff);
			break;
	case SPANISH: //西班牙
		Printf24("Introduzca la contrase?a",REMIND_WINDOW_X,REMIND_WINDOW_Y+5,RED_COLOR,0,0xffff);
		ASCII_Printf("n",ASCII24_MODE,12,24,PUTAO_ZK24,REMIND_WINDOW_X+12*22,REMIND_WINDOW_Y+5,RED_COLOR,0xffff);
			break;
	}
Printf32("请输入6位密码!",150,250,RED_COLOR,0,0xffff);
}

void F5_plus_dis(Int8U flag)	//F5++
{
if(flag==1)
	{
	// Printf32("++",SIZE_WINDOW_X,SIZE_WINDOW_Y,RED_COLOR,1,0xffff);
	GLCD_SetWindow_Fill( REMIND_WINDOW_X, REMIND_WINDOW_Y, REMIND_WINDOW_X+REMIND_LENGTH, REMIND_WINDOW_Y+30, 0xfffff, 0xffff);//提示框
	switch(Language)
		{
		case CHN_HAN:
				Printf24("再按F5++,退出",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,BLACK_COLOR,0,0xffff);
						break;
		case ENGLISH:	
				Printf24("Press F5++ to exit",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,BLACK_COLOR,0,0xffff);
						break;
		case INDONSIA:	//印尼	
				Printf24("Tekan F5++ untuk keluar",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,BLACK_COLOR,0,0xffff);
						break;
		case PORTUGAL:	//葡萄牙
				Printf24("imprensa F5++,desistir",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,BLACK_COLOR,0,0xffff);
						break;
		case SPANISH: //西班牙
				Printf24("prensa F5++,dejar de",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,BLACK_COLOR,0,0xffff);
						break;
		}
	//.........................解释 框
	ModeName_dis(WorkMode);	
	}
else
	{
	// Printf32("++",SIZE_WINDOW_X,SIZE_WINDOW_Y,0xffff,1,0xffff);
	PromptNum_dis();//输入范围
	PromptDis_flag=1;
	//.........................解释 框
	ModeName_dis(WorkMode);	
	}
}
void F6_minus_dis(Int8U flag)	//F6--
{
if(flag==1)
	{
	// Printf32("--",SIZE_WINDOW_X,SIZE_WINDOW_Y,RED_COLOR,1,0xffff);
	GLCD_SetWindow_Fill( REMIND_WINDOW_X, REMIND_WINDOW_Y, REMIND_WINDOW_X+REMIND_LENGTH, REMIND_WINDOW_Y+30, 0xfffff, 0xffff);//提示框
	switch(Language)
		{
		case CHN_HAN:
				Printf24("再按F6--,退出",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,BLACK_COLOR,0,0xffff);
						break;
		case ENGLISH:	
				Printf24("Press F6-- to exit",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,BLACK_COLOR,0,0xffff);
						break;
		case INDONSIA:	//印尼	
				Printf24("Tekan F6-- untuk keluar",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,BLACK_COLOR,0,0xffff);
						break;
		case PORTUGAL:	//葡萄牙
				Printf24("imprensa F6--,desistir",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,BLACK_COLOR,0,0xffff);
						break;
		case SPANISH: //西班牙
				Printf24("prensa F6--,dejar de",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,BLACK_COLOR,0,0xffff);
						break;
		}
	//.........................解释 框
	ModeName_dis(WorkMode);	
	}
else
	{
	// Printf32("--",SIZE_WINDOW_X,SIZE_WINDOW_Y,0xffff,1,0xffff);
	PromptNum_dis();//输入范围
	PromptDis_flag=1;
	//.........................解释 框
	ModeName_dis(WorkMode);	
	}
}

//手动********************
void TimeSetSel_dis(Int8U sel, Int8U flag) //时间 设定 显示
{
volatile Int16U x,y,gap;
Int16U front_color,back_color;
gap=CLOCK_GAP_Y;x=CLOCK_DATA_X+120;
if(flag==1)
    {
	front_color=WHITE_COLOR;//;
	back_color=BLUE_COLOR;
	}
else
	{
	front_color=BLACK_COLOR;
	back_color=TEXT_TAB_BACK_COLOR;//0xef9f;
	}
y=CLOCK_DATA_Y+gap*sel;
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
				case INDONSIA:	//印尼
					Printf24("Rentang nilai      untuk",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,BLACK_COLOR,0,0xffff);
					break;
				case PORTUGAL:	//葡萄牙
					Printf16("Intervalo de dados           --",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,BLACK_COLOR,0,0xffff);
					break;
				case SPANISH: //西班牙
					Printf16("Rango de datos               --",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,BLACK_COLOR,0,0xffff);
						break;
				}
			Printf24("0        99",REMIND_WINDOW_X+200,REMIND_WINDOW_Y+5,RED_COLOR,0,0xffff);
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
				case INDONSIA:	//印尼
					Printf24("Rentang nilai      untuk",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,BLACK_COLOR,0,0xffff);
					break;
				case PORTUGAL:	//葡萄牙
					Printf16("Intervalo de dados           --",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,BLACK_COLOR,0,0xffff);
					break;
				case SPANISH: //西班牙
					Printf16("Rango de datos               --",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,BLACK_COLOR,0,0xffff);
						break;
				}
			Printf24("1        12",REMIND_WINDOW_X+200,REMIND_WINDOW_Y+5,RED_COLOR,0,0xffff);
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
				case INDONSIA:	//印尼
					Printf24("Rentang nilai      untuk",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,BLACK_COLOR,0,0xffff);
					break;
				case PORTUGAL:	//葡萄牙
					Printf16("Intervalo de dados           --",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,BLACK_COLOR,0,0xffff);
					break;
				case SPANISH: //西班牙
					Printf16("Rango de datos               --",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,BLACK_COLOR,0,0xffff);
						break;
				}
			Printf24("1        31",REMIND_WINDOW_X+200,REMIND_WINDOW_Y+5,RED_COLOR,0,0xffff);
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
				case INDONSIA:	//印尼
					Printf24("Rentang nilai      untuk",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,BLACK_COLOR,0,0xffff);
					break;
				case PORTUGAL:	//葡萄牙
					Printf16("Intervalo de dados           --",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,BLACK_COLOR,0,0xffff);
					break;
				case SPANISH: //西班牙
					Printf16("Rango de datos               --",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,BLACK_COLOR,0,0xffff);
						break;
				}
			Printf24("0        23",REMIND_WINDOW_X+200,REMIND_WINDOW_Y+5,RED_COLOR,0,0xffff);
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
				case INDONSIA:	//印尼
					Printf24("Rentang nilai      untuk",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,BLACK_COLOR,0,0xffff);
					break;
				case PORTUGAL:	//葡萄牙
					Printf16("Intervalo de dados           --",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,BLACK_COLOR,0,0xffff);
					break;
				case SPANISH: //西班牙
					Printf16("Rango de datos               --",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,BLACK_COLOR,0,0xffff);
						break;
				}
			Printf24("0        59",REMIND_WINDOW_X+200,REMIND_WINDOW_Y+5,RED_COLOR,0,0xffff);
			}
		break;
	
	}
}

void ClockPage_dis(void)  //F3手动 时钟	
{
volatile Int16U x,y,gap,n;
 x=CLOCK_DATA_X,y=CLOCK_DATA_Y,gap=CLOCK_GAP_Y;
CurrentArea_save2(MIDDLE_PAGE_X , MIDDLE_PAGE_Y,  M_PAGE_WIDE, M_PAGE_HIGH);
MiddlePage_dis();//中间活页
SubModeIcon_dis(WorkMode);   //时钟模式
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
	case INDONSIA:	//印尼
		Printf24("Tahun:  20",x,y,BLACK_COLOR,0,0xffff);y+=gap;
		Printf24("Bulan:",x,y,BLACK_COLOR,0,0xffff);y+=gap;
		Printf24("hari:",x,y,BLACK_COLOR,0,0xffff);y+=gap;
		Printf24("Jam:",x,y,BLACK_COLOR,0,0xffff);y+=gap;
		Printf24("Menit:",x,y,BLACK_COLOR,0,0xffff);
			break;
	case PORTUGAL:	//葡萄牙
		Printf24("ano:   20",x,y,BLACK_COLOR,0,0xffff);y+=gap;
		Printf24("mê ",x,y,BLACK_COLOR,0,0xffff);
		Printf24("  s:",x,y,BLACK_COLOR,0,0xffff);y+=gap;//mês
		Printf24("dia:",x,y,BLACK_COLOR,0,0xffff);y+=gap;
		Printf24("tempo:",x,y,BLACK_COLOR,0,0xffff);y+=gap;
		Printf24("minuto:",x,y,BLACK_COLOR,0,0xffff);
			break;
	case SPANISH: //西班牙
		Printf24("ano:   20",x,y,BLACK_COLOR,0,0xffff);
		ASCII_Printf("n",ASCII24_MODE,12,24,PUTAO_ZK24,x+12,y,BLACK_COLOR,0xffff);y+=gap;
		Printf24("mes:",x,y,BLACK_COLOR,0,0xffff);y+=gap;//mês
		Printf24("dia:",x,y,BLACK_COLOR,0,0xffff);y+=gap;
		Printf24("hora:",x,y,BLACK_COLOR,0,0xffff);y+=gap;
		Printf24("minuto:",x,y,BLACK_COLOR,0,0xffff);
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
MiddlePage_dis();//中间活页
SubModeIcon_dis(WorkMode);   //参数模式
//左边
switch(Language)
	{
	case CHN_HAN:
		Printf16("脉冲当量|编码器分辨率|丝杆螺距",x,y,0xFc00,0,0xffff);
			break;
	case ENGLISH:	
		Printf16("Pulse-Equ  Resolution   Distance",x,y,0xFc00,0,0xffff);
			break;
	case INDONSIA:	//印尼
		Printf16("Pulse-setara Resolusi Screw-jarak",x-25,y,0xFc00,0,0xffff);
			break;
	case PORTUGAL:	//葡萄牙	
		Printf16("Pulso-Equ  resolu??o    passo",x,y,0xFc00,0,0xffff);
		ASCII_Printf("ca",ASCII16_MODE,8,16,PUTAO_ZK16, x+8*17,y,0xFc00,0xffff);
			break;
	case SPANISH: //西班牙	
		Printf16("Pulso-Equ  resoluci    paso",x,y,0xFc00,0,0xffff);
			break;
	}
x=PULSE_SET_X2;
switch(Language)
	{
	case CHN_HAN:
		Printf16("脉冲当量|编码器分辨率|丝杆螺距",x,y,0xFc00,0,0xffff);
			break;
	case ENGLISH:	
		Printf16("Pulse-Equ  Resolution   Distance",x,y,0xFc00,0,0xffff);
			break;
	case INDONSIA:	//印尼
		Printf16("Pulse-setara Resolusi Screw-jarak",x,y,0xFc00,0,0xffff);
			break;
	case PORTUGAL:	//葡萄牙	
		Printf16("Pulso-Equ  resolu??o    passo",x,y,0xFc00,0,0xffff);
		ASCII_Printf("ca",ASCII16_MODE,8,16,PUTAO_ZK16, x+8*17,y,0xFc00,0xffff);
			break;
	case SPANISH: //西班牙	
		Printf16("Pulso-Equ  resoluci    paso",x,y,0xFc00,0,0xffff);
			break;
	}
x=PULSE_SET_X1+15;
y=PULSE_SET_Y;
for(n=0;n<12;n++)
	{
	if(n==6)
	   {
	   x=PULSE_SET_X2+15;
	   y=PULSE_SET_Y+PULSE_GAP_Y;
	   }
	else
	   {
	   y+=PULSE_GAP_Y;
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
	case INDONSIA:	//印尼
		Printf24("Masuk Pulse setara!",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,BLACK_COLOR,0,0xffff);
			break;
	case PORTUGAL:	//葡萄牙
		Printf24("Entrada de pulso equivalente!",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,BLACK_COLOR,0,0xffff);
			break;
	case SPANISH: //西班牙
		Printf24("Entrada de pulsos equivalente!",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,BLACK_COLOR,0,0xffff);
			break;
	}
x=PULSE_SET_X2-10,y=PULSE_SET_Y+20;
GLCD_DrawLine( x, y, x, y+210, BLUE_COLOR);
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
	front_color=TEXT_TAB_BACK_COLOR;
	}
if(sel>5)
	{
	x=PULSE_SET_X2+10;
	}
sel%=6;
y=PULSE_SET_Y+PULSE_GAP_Y*(sel+1);
GLCD_SetWindow( x, y, x+WW, y+HH, front_color);
}

//------------自刀
void SelfEnterPage_dis(void)//自刀模式 进入 ---------提示
{
Int16U x,y;
Int16U front_color,back_color;
x=SELF_PROMP_X,y=SELF_PROMP_Y;
front_color=RED_COLOR,back_color=0xffff;
CurrentArea_save2(x , y,  SELF_PROMP_WIDE, SELF_PROMP_HIGH);
GLCD_SetWindow_Fill( x, y, x+SELF_PROMP_WIDE-1, y+SELF_PROMP_HIGH-1, BLUE_COLOR, 0xfffff);x+=10,y+=5;
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
	case INDONSIA:	//印尼
		Printf24("Modus pemotongan otomatis",x,y,front_color,1,back_color);y+=30;
		Printf24("sangat berbahaya!",x,y,front_color,1,back_color);x+=20,y+=50;
		Printf24("Ya",x,y,front_color,1,back_color);x+=130;
		Printf24("Membatal",x,y,front_color,1,back_color);
			break;
	case PORTUGAL:	//葡萄牙
		Printf16("Este modo é muito perigoso",x,y,front_color,1,back_color);y+=30;
		Printf16("Pressione o bot?o OK para entrar",x,y,front_color,1,back_color);
		ASCII_Printf("a",ASCII16_MODE,8,16,PUTAO_ZK16, x+8*15,y,front_color,back_color);x+=20,y+=50;
		Printf24("OK",x,y,front_color,1,back_color);x+=130;
		Printf24("Cancelar",x,y,front_color,1,back_color);
			break;
	case SPANISH: //西班牙
		Printf16("Este modo es muy peligroso",x,y,front_color,1,back_color);y+=30;
		Printf16("Pulse el botón OK para entrar",x,y,front_color,1,back_color);x+=20,y+=50;
		Printf24("OK",x,y,front_color,1,back_color);x+=130;
		Printf24("Cancelar",x,y,front_color,1,back_color);
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
GLCD_SetWindow_Fill( x, y, x+SELF_PROMP_WIDE-1, y+SELF_PROMP_HIGH-1, BLUE_COLOR, 0xfffff);x+=20,y+=5;
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
		Printf24("Continue the last",x,y,front_color,1,back_color);y+=30;
		Printf24("Auto-Cut step?",x,y,front_color,1,back_color);x+=40,y+=50;
		Printf24("OK",x,y,front_color,1,back_color);x+=120;
		Printf24("Cancel",x,y,front_color,1,back_color);
			break;
	case INDONSIA:	//印尼
		Printf24("Apakah akan melanjutkan ",x,y,front_color,1,back_color);y+=30;
		Printf24("langkah-langkah sebelumnya?",x,y,front_color,1,back_color);x+=40,y+=50;
		Printf24("Ya",x,y,front_color,1,back_color);x+=130;
		Printf24("Membatal",x,y,front_color,1,back_color);
			break;
	case PORTUGAL:	//葡萄牙
		Printf24("Se continuar a opera??o",x,y,front_color,1,back_color);
		ASCII_Printf("ca",ASCII24_MODE,12,24,PUTAO_ZK24, x+12*20,y,front_color,back_color);y+=30;
		Printf24("anterior?",x,y,front_color,1,back_color);x+=20,y+=50;
		Printf24("OK",x,y,front_color,1,back_color);x+=130;
		Printf24("Cancelar",x,y,front_color,1,back_color);
			break;
	case SPANISH: //西班牙
		Printf24("Ya sea para continuar",x,y,front_color,1,back_color);//Ya sea para continuar la ejecución
		y+=30;
		Printf24("la ejecució",x,y,front_color,1,back_color);//ejecución
		Printf24("           n?",x,y,front_color,0,back_color);x+=20,y+=50;
		Printf24("OK",x,y,front_color,1,back_color);x+=130;
		Printf24("Cancelar",x,y,front_color,1,back_color);
			break;
	}

}

//---------伺服 参数设置  --
void ServoParameter_dis(Int8U sel, Int8U flag) //参数 设置显示
{
volatile Int16U x,y,gap;
Int16U front_color,back_color;
gap=PARA_ROW_GAP;x=PARA_START_X2+(sel/7)*PARA_COL_WIDE;
Int32U temp;
if(flag==1)
    {
	front_color=WHITE_COLOR;
	back_color=BLUE_COLOR;
	}
else
	{
	front_color=BLACK_COLOR;
	back_color=TEXT_TAB_BACK_COLOR;
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
				case INDONSIA:	//印尼
					Printf24("Rentang nilai      untuk",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,BLACK_COLOR,0,0xffff);
					break;
				case PORTUGAL:	//葡萄牙
					Printf16("Intervalo de dados           --",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,BLACK_COLOR,0,0xffff);
					break;
				case SPANISH: //西班牙
					Printf16("Rango de datos               --",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,BLACK_COLOR,0,0xffff);
						break;
				}
			Printf24("1       99",REMIND_WINDOW_X+200,REMIND_WINDOW_Y+5,RED_COLOR,0,0xffff);
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
				case INDONSIA:	//印尼
					Printf24("Rentang nilai      untuk",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,BLACK_COLOR,0,0xffff);
					break;
				case PORTUGAL:	//葡萄牙
					Printf16("Intervalo de dados           --",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,BLACK_COLOR,0,0xffff);
					break;
				case SPANISH: //西班牙
					Printf16("Rango de datos               --",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,BLACK_COLOR,0,0xffff);
						break;
				}
			Printf24("1       99",REMIND_WINDOW_X+200,REMIND_WINDOW_Y+5,RED_COLOR,0,0xffff);
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
				case INDONSIA:	//印尼
					Printf24("Rentang nilai      untuk",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,BLACK_COLOR,0,0xffff);
					break;
				case PORTUGAL:	//葡萄牙
					Printf16("Intervalo de dados           --",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,BLACK_COLOR,0,0xffff);
					break;
				case SPANISH: //西班牙
					Printf16("Rango de datos               --",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,BLACK_COLOR,0,0xffff);
						break;
				}
			Printf24("1       99",REMIND_WINDOW_X+200,REMIND_WINDOW_Y+5,RED_COLOR,0,0xffff);
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
				case INDONSIA:	//印尼
					Printf24("Rentang nilai      untuk",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,BLACK_COLOR,0,0xffff);
					break;
				case PORTUGAL:	//葡萄牙
					Printf16("Intervalo de dados           --",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,BLACK_COLOR,0,0xffff);
					break;
				case SPANISH: //西班牙
					Printf16("Rango de datos               --",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,BLACK_COLOR,0,0xffff);
						break;
				}
			Printf24("1       99",REMIND_WINDOW_X+200,REMIND_WINDOW_Y+5,RED_COLOR,0,0xffff);
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
				case INDONSIA:	//印尼
					Printf24("Rentang nilai      untuk",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,BLACK_COLOR,0,0xffff);
					break;
				case PORTUGAL:	//葡萄牙
					Printf16("Intervalo de dados           --",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,BLACK_COLOR,0,0xffff);
					break;
				case SPANISH: //西班牙
					Printf16("Rango de datos               --",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,BLACK_COLOR,0,0xffff);
						break;
				}
			Printf24("1       99",REMIND_WINDOW_X+200,REMIND_WINDOW_Y+5,RED_COLOR,0,0xffff);
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
				case INDONSIA:	//印尼
					Printf24("Rentang nilai      untuk",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,BLACK_COLOR,0,0xffff);
					break;
				case PORTUGAL:	//葡萄牙
					Printf16("Intervalo de dados           --",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,BLACK_COLOR,0,0xffff);
					break;
				case SPANISH: //西班牙
					Printf16("Rango de datos               --",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,BLACK_COLOR,0,0xffff);
						break;
				}
			Printf24("1       99",REMIND_WINDOW_X+200,REMIND_WINDOW_Y+5,RED_COLOR,0,0xffff);
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
				case INDONSIA:	//印尼
					Printf24("Rentang nilai      untuk",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,BLACK_COLOR,0,0xffff);
					break;
				case PORTUGAL:	//葡萄牙
					Printf16("Intervalo de dados           --",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,BLACK_COLOR,0,0xffff);
					break;
				case SPANISH: //西班牙
					Printf16("Rango de datos               --",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,BLACK_COLOR,0,0xffff);
						break;
				}
			Printf24("1       3",REMIND_WINDOW_X+200,REMIND_WINDOW_Y+5,RED_COLOR,0,0xffff);
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
				case INDONSIA:	//印尼
					Printf24("Input data (            )",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,BLACK_COLOR,0,0xffff);
					break;
				case PORTUGAL:	//葡萄牙
					Printf24("Input data (            )",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,BLACK_COLOR,0,0xffff);
					break;
				case SPANISH: //西班牙
					Printf24("datos Input(            )",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,BLACK_COLOR,0,0xffff);
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
Int16U back_color=TEXT_TAB_BACK_COLOR;;
 x=PARA_START_X1,y=PARA_START_Y,gap=PARA_ROW_GAP;
CurrentArea_save2(MIDDLE_PAGE_X , MIDDLE_PAGE_Y,  M_PAGE_WIDE, M_PAGE_HIGH);
MiddlePage_dis();//中间活页
SubModeIcon_dis(WorkMode);   // ‘C’参数模式
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
		Printf24("Speed-diff:",x,y,BLACK_COLOR,1,back_color);y+=gap;
		Printf24("Speed-inte:",x,y,BLACK_COLOR,1,back_color);y+=gap;
		
		Printf24("Reduc-ratio:",x,y,BLACK_COLOR,1,back_color);
		x+=PARA_COL_WIDE;y=PARA_START_Y;
		Printf24("Screw_Pitch:",x,y,BLACK_COLOR,1,back_color);
			break;
	case INDONSIA:	//印尼
		Printf24("Lokasi-gain:",x,y,BLACK_COLOR,1,back_color);y+=gap;
		Printf24("Lokasi-difer:",x,y,BLACK_COLOR,1,back_color);y+=gap;
		Printf24("Lokasi-integ:",x,y,BLACK_COLOR,1,back_color);y+=gap;
		Printf24("Kecepa-gain:",x,y,BLACK_COLOR,1,back_color);y+=gap;
		Printf24("Kecepa-diff:",x,y,BLACK_COLOR,1,back_color);y+=gap;
		Printf24("Kecepa-inte:",x,y,BLACK_COLOR,1,back_color);y+=gap;
		
		Printf24("Rasio reduksi:",x,y,BLACK_COLOR,1,back_color);
		x+=PARA_COL_WIDE;y=PARA_START_Y;
		Printf24("Screw-jarak:",x,y,BLACK_COLOR,1,back_color);
			break;
	case PORTUGAL:	//葡萄牙
		Printf24("Posi??o Gain:",x,y,BLACK_COLOR,1,back_color);
		ASCII_Printf("ca",ASCII24_MODE,12,24,PUTAO_ZK24, x+12*4,y,BLACK_COLOR,back_color);y+=gap;
		Printf24("Posi??o difer:",x,y,BLACK_COLOR,1,back_color);
		ASCII_Printf("ca",ASCII24_MODE,12,24,PUTAO_ZK24, x+12*4,y,BLACK_COLOR,back_color);y+=gap;
		Printf24("Posi??o Pontos:",x,y,BLACK_COLOR,1,back_color);
		ASCII_Printf("ca",ASCII24_MODE,12,24,PUTAO_ZK24, x+12*4,y,BLACK_COLOR,back_color);y+=gap;
		Printf24("Veloc-gain:",x,y,BLACK_COLOR,1,back_color);y+=gap;
		Printf24("Veloc-diff:",x,y,BLACK_COLOR,1,back_color);y+=gap;
		Printf24("Veloc-inte:",x,y,BLACK_COLOR,1,back_color);y+=gap;
		
		Printf16("rá              ",x,y,BLACK_COLOR,1,back_color);
		Printf16("  cio de redu??o:",x,y,BLACK_COLOR,0,back_color);//rácio
		ASCII_Printf("ca",ASCII16_MODE,8,16,PUTAO_ZK16, x+8*13,y,BLACK_COLOR,back_color);
		x+=PARA_COL_WIDE;y=PARA_START_Y;
		Printf24("Screw-jarak:",x,y,BLACK_COLOR,1,back_color);
			break;
	case SPANISH: //西班牙
		Printf24("Posici- Gain:",x,y,BLACK_COLOR,1,back_color);	//posición
		y+=gap;
		Printf24("Posici-Difer:",x,y,BLACK_COLOR,1,back_color);y+=gap;
		Printf24("Posici-Integ:",x,y,BLACK_COLOR,1,back_color);y+=gap;
		Printf24("Veloc-Gain:",x,y,BLACK_COLOR,1,back_color);y+=gap;
		Printf24("Veloc-Difer:",x,y,BLACK_COLOR,1,back_color);y+=gap;
		Printf24("Veloc-Integ:",x,y,BLACK_COLOR,1,back_color);y+=gap;
		
		Printf16("Ratio de reducció",x,y,BLACK_COLOR,1,back_color);
		Printf16("                 n",x,y,BLACK_COLOR,0,back_color);//reducción
		x+=PARA_COL_WIDE;y=PARA_START_Y;
		Printf24("Screw-brea:",x,y,BLACK_COLOR,1,back_color);
			break;
	}
	 
for(n=1;n<8;n++)
	ServoParameter_dis(n, 0);
ServoParameter_dis(0, 1);
}

void PassCodePage_dis(void)  //密码模式 启动界面
{
CurrentArea_save2(MIDDLE_PAGE_X , MIDDLE_PAGE_Y,  M_PAGE_WIDE, M_PAGE_HIGH);
MiddlePage_dis();//中间活页
SubModeIcon_dis(WorkMode);   //密码模式
GLCD_SetWindow_Fill(REMIND_WINDOW_X, REMIND_WINDOW_Y, REMIND_WINDOW_X+REMIND_LENGTH, REMIND_WINDOW_Y+30, 0xfffff, 0xffff);//提示框
switch(Language)
	{
	case CHN_HAN:
		Printf24("请输入密码!",REMIND_WINDOW_X,REMIND_WINDOW_Y+5,RED_COLOR,0,0xffff);
			break;
	case ENGLISH:	
		Printf24("Enter passcode!",REMIND_WINDOW_X,REMIND_WINDOW_Y+5,RED_COLOR,0,0xffff);
			break;
	case INDONSIA:	//印尼
		Printf24("Masukkan sandi Anda",REMIND_WINDOW_X,REMIND_WINDOW_Y+5,RED_COLOR,0,0xffff);
			break;
	case PORTUGAL:	//葡萄牙
		Printf24("Por favor, digite uma senha",REMIND_WINDOW_X,REMIND_WINDOW_Y+5,RED_COLOR,0,0xffff);
			break;
	case SPANISH: //西班牙
		Printf24("Introduzca la contrase?a",REMIND_WINDOW_X,REMIND_WINDOW_Y+5,RED_COLOR,0,0xffff);
		ASCII_Printf("n",ASCII24_MODE,12,24,PUTAO_ZK24,REMIND_WINDOW_X+12*22,REMIND_WINDOW_Y+5,RED_COLOR,0xffff);
			break;
	}
}
void PassSet_dis(void) //密码 设置界面
{
Int16U x,y,gap;
x=PASS_TIME1_X,y=PASS_TIME1_Y,gap=PASS_TIME_GAP;

PsswordFunPic_dis(PASSWORD_FUN_PIC_X,PASSWORD_FUN_PIC_Y);//密码功能模式pic
switch(Language)
	{
	case CHN_HAN:
		Printf24("第一次关机天数:",x,y,BLACK_COLOR,0,0xffff);y+=gap;
			break;
	case ENGLISH:	
		Printf24("First valid days:",x,y,BLACK_COLOR,0,0xffff);y+=gap;
			break;
	case INDONSIA:	//印尼
		Printf24("pertama kalinya hari:",x,y,BLACK_COLOR,0,0xffff);y+=gap;
			break;
	case PORTUGAL:	//葡萄牙
		Printf24("O nú                     ",x,y,BLACK_COLOR,0,0xffff);
		Printf24("    mero de dias eficaz 1:",x,y,BLACK_COLOR,0,0xffff);y+=gap; //número
			break;
	case SPANISH: //西班牙
		Printf24("Nú              ",x,y,BLACK_COLOR,0,0xffff);//Número de días
		Printf24("  mero de dí    ",x,y,BLACK_COLOR,0,0xffff); //
		Printf24("            as 1:",x,y,BLACK_COLOR,0,0xffff);y+=gap; //
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
	case INDONSIA:	//印尼
		Printf24("Kedua hari:",x,y,BLACK_COLOR,0,0xffff);y+=gap;
			break;
	case PORTUGAL:	//葡萄牙
		Printf24("O nú                     ",x,y,BLACK_COLOR,0,0xffff);
		Printf24("    mero de dias eficaz 2:",x,y,BLACK_COLOR,0,0xffff);y+=gap;
			break;
	case SPANISH: //西班牙
		Printf24("Nú              ",x,y,BLACK_COLOR,0,0xffff);//Número de días
		Printf24("  mero de dí    ",x,y,BLACK_COLOR,0,0xffff); //
		Printf24("            as 2:",x,y,BLACK_COLOR,0,0xffff);y+=gap; //
			break;
	}
PassDaysSet_dis( 1, 0);
PassDaysSet_dis( 0, 1);
}

void PassDaysSet_dis(Int8U sel,Int8U flag)//天数设定
{
volatile Int16U x,y,gap;
Int16U front_color,back_color;
gap=PASS_TIME_GAP;x=PASS_TIME1_X+20;
if(flag==1)
    {
	front_color=WHITE_COLOR;
	back_color=BLUE_COLOR;
	}
else
	{
	front_color=BLACK_COLOR;
	back_color=TEXT_TAB_BACK_COLOR;
	}
y=PASS_TIME1_Y+40+gap*sel;
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
				case INDONSIA:	//印尼
					Printf24("Input Data,Tekan tombol Insert",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,BLACK_COLOR,0,0xffff);
						break;
				case PORTUGAL:	//葡萄牙
					Printf16("Os dados de entrada, pressione a tecla Insert",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,BLACK_COLOR,0,0xffff);
						break;
				case SPANISH: //西班牙
					Printf16("ngrese el nú ",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,BLACK_COLOR,0,0xffff);
					Printf16("            mero de dí ",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,BLACK_COLOR,0,0xffff);
					Printf16("                      as, pulse la tecla Insert",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,BLACK_COLOR,0,0xffff);
						break;
				}
			}
		x+=36;
		GLCD_SetWindow_Fill( x, y, x+144, y+24, TEXT_TAB_BACK_COLOR, TEXT_TAB_BACK_COLOR);//clear text win
		if(FirstDayValid_flag==1)
			{
			switch(Language)
				{
				case CHN_HAN:
					Printf24("(有效)",x,y,front_color,1,back_color); 
						break;
				case ENGLISH:	
					Printf24("(Valid) ",x,y,front_color,1,back_color); 
						break;
				case INDONSIA:	//印尼
					Printf24("(Efekti) ",x,y,front_color,1,back_color); 
						break;
				case PORTUGAL:	//葡萄牙 
				case SPANISH: //西班牙
					Printf24("(eficaz)",x,y,front_color,1,back_color); 
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
				case INDONSIA:	//印尼
					Printf24("(Cacat)",x,y,front_color,1,back_color); 
						break;
				case PORTUGAL:	//葡萄牙
				case SPANISH: //西班牙
					Printf24("(invá    ",x,y,front_color,1,back_color); //inválido
					Printf24("     lido)",x,y,front_color,0,back_color); //inválido
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
				case INDONSIA:	//印尼
					Printf24("Input Data,Tekan tombol Insert",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,BLACK_COLOR,0,0xffff);
						break;
				case PORTUGAL:	//葡萄牙
					Printf16("Os dados de entrada, pressione a tecla Insert",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,BLACK_COLOR,0,0xffff);
						break;
				case SPANISH: //西班牙
					Printf16("ngrese el nú ",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,BLACK_COLOR,0,0xffff);
					Printf16("            mero de dí ",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,BLACK_COLOR,0,0xffff);
					Printf16("                      as, pulse la tecla Insert",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,BLACK_COLOR,0,0xffff);
						break;
				}
			}
		x+=36;
		GLCD_SetWindow_Fill( x, y, x+144, y+24, TEXT_TAB_BACK_COLOR, TEXT_TAB_BACK_COLOR);//clear text win
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
				case INDONSIA:	//印尼
					Printf24("(Efekti)  ",x,y,front_color,1,back_color); 
						break;  
				case PORTUGAL:	//葡萄牙
				case SPANISH: //西班牙
					Printf24("(eficaz)",x,y,front_color,1,back_color); 
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
				case INDONSIA:	//印尼
					Printf24("(Cacat)",x,y,front_color,1,back_color); 
						break;
				case PORTUGAL:	//葡萄牙
				case SPANISH: //西班牙
					Printf24("(invá    ",x,y,front_color,1,back_color); //inválido
					Printf24("     lido)",x,y,front_color,0,back_color); //inválido
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
back_color=STEP_BACK_COLOR;
FirstBack_dis();//底层背景

//TimeCol_dis(TIME_COL_X,TIME_COL_Y);//时间条

// // MainPowerOnButt_dis( 0);	//主电源开
// // PowerBlack_dis( MAIN_PWR_CTRL_X, MAIN_PWR_CTRL_Y);//电源黑
// // MainPowerOffButt_dis( 0);	//主电源关

// // LEDKnifeButt_dis( 1);	//对刀灯
// // LightCtrl_dis( LED_CTRL_X, LED_CTRL_Y);//灯0
// // LEDBrightButt_dis( 0);	//照明灯

// // PumpOn_dis( PUMP_ON_X, PUMP_ON_Y);//风泵 开up
// // PumpOff_dis( PUMP_OFF_X, PUMP_OFF_Y);//风泵 关up

// ElectricKnifeButt_dis();	//电动换刀   20190513

Schedule_dis(SCHEDULE_X,SCHEDULE_Y);//进度
ProgressBar_dis(OnePro_head.pro_knifeSUM,Knife_order);  //进度条 显示
xp=PROG_X,yp=PROG_Y;
switch(Language)
	{
	case CHN_HAN:
		Printf16(" 程序  ",xp,yp,BLACK_COLOR,1,back_color);
			break;
	case ENGLISH:	
		Printf16("Process",xp,yp,BLACK_COLOR,1,back_color);
			break;
	case INDONSIA:	//印尼语
		Printf16("Program",xp,yp,BLACK_COLOR,1,back_color);
			break;	
	case PORTUGAL:	//葡萄牙
	case SPANISH: //西班牙
		Printf16("Programa",xp,yp,BLACK_COLOR,1,back_color);
			break;		
	}
xp=STEP_X;//
switch(Language)
	{
	case CHN_HAN:
		Printf16(" 步骤  ",xp,yp,BLACK_COLOR,1,back_color);//
			break;
	case ENGLISH:	
		Printf16(" Step  ",xp,yp,BLACK_COLOR,1,back_color);
			break;
	case INDONSIA:	//印尼语
		Printf16("Langkah",xp,yp,BLACK_COLOR,1,back_color);
			break;
	case PORTUGAL:	//葡萄牙
		Printf16("Passo",xp,yp,BLACK_COLOR,1,back_color);
			break;	
	case SPANISH: //西班牙
		Printf16("Paso",xp,yp,BLACK_COLOR,1,back_color);
			break;	
	}
OneProNum_dis(Pro_data.pro_num, OnePro_head);// 程序号
StepNum_dis(OnePro_head.pro_knifeSUM,Knife_order);// 步骤号  总刀数-序号

//Order_dis(ORDER_X,ORDER_Y);//序号
//Position_dis(POSITION_X,POSITION_Y);//位置
//PushKnife_dis(PUSH_KNIFE_X,PUSH_KNIFE_Y);//推纸——刀

//PushPaperTool_dis(PUSH_PAPER_TOOL_X,PUSH_PAPER_TOOL_Y);//推纸器
CurrentSize_dis(CurrentSize); //当前尺寸 更新显示
CurrUint_dis(Unit);  //当前尺寸 单位


CursorSizeName();	//标称尺寸
PushButton_dis(PUSH_BUTT_X, PUSH_BUTT_Y);//推纸

TeachModeButton_dis( TEACH_BUTT_X, TEACH_BUTT_Y);//示教按钮
AutoCutMOdeButton_dis( AUTOCUT_BUTT_X, AUTOCUT_BUTT_Y);//自刀按钮

//Knife_Up_dis(KNIFE_X,KNIFE_Y);//刀上
//Press_Up_dis(PRESS_UP_X,PRESS_UP_Y);//压上

//Red_A_dis(RED_A_X,RED_A_Y);//红A
//Red_B_dis(RED_B_X,RED_B_Y);//红B
//Hand_IR_dis(HAND_IR_X,HAND_IR_Y);//手红外


//主模式 ---
MainModeIcon_dis(WorkMode);//自动模式..............

Calculator_Window();  //计算器

CalcNoNumInput_flag=1;
//Run_Up_dis(RUN_X,RUN_Y);//运行up
//Stop_Up_dis(STOP_X,STOP_Y);//停止up

}

void PromptNum_dis(void)  //输入数据范围 提示
{
Int8U num[15],str1[8],str2[8],i,j;
Int16U x,y;
i=0;
Int32U max,min;
if(Run_flag==1)
	{
	if((WorkMode==AUTO_MODE)||(WorkMode==SELF_CUT_MODE))  //自动 自刀 模式
		{
		if(Z_Pulse_err_flag==0)
			{
			GLCD_SetWindow_Fill( REMIND_WINDOW_X, REMIND_WINDOW_Y, REMIND_WINDOW_X+REMIND_LENGTH, REMIND_WINDOW_Y+30, 0xfffff, 0xffff);//提示框
			switch(Language)
				{
				case CHN_HAN:
					Printf24("按'停止键'停止！",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,BLACK_COLOR,0,0xffff);
						break;
				case ENGLISH:	
					Printf24("Press 'STOP' to stop it!",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,BLACK_COLOR,0,0xffff);
						break;
				case INDONSIA:	//印尼语
					Printf24("Tekan 'berhenti tombol' Berhenti",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,BLACK_COLOR,0,0xffff);
						break;
				case PORTUGAL:	//葡萄牙
					Printf16("Pressione 'bot?o de parada de' Stop!",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,BLACK_COLOR,0,0xffff);
					ASCII_Printf("a",ASCII16_MODE,8,16,PUTAO_ZK16, REMIND_WINDOW_X+10+8*14,REMIND_WINDOW_Y+5,BLACK_COLOR,0xffff);
						break;
				case SPANISH: //西班牙
					Printf16("Pulse el botó ",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,BLACK_COLOR,0,0xffff);
					Printf16("             n de parada!",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,BLACK_COLOR,0,0xffff);
						break;
				}
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
		case INDONSIA:	//印尼
			Printf24("Rentang nilai      untuk",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,BLACK_COLOR,0,0xffff);
				break;
		case PORTUGAL:	//葡萄牙
			Printf16("Intervalo de dados           --",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,BLACK_COLOR,0,0xffff);
			break;
		case SPANISH: //西班牙
			Printf16("Rango de datos               --",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,BLACK_COLOR,0,0xffff);
				break;
		}

	x=REMIND_WINDOW_X+180,y=REMIND_WINDOW_Y+5;
	Printf24(str1,x,y,RED_COLOR,0,0xffff);
	Printf24(str2,x+120,y,RED_COLOR,0,0xffff);
	}

}


void TextWindow_dis(void)  //文本输入框
{
// GLCD_SetWindow_Fill( SIZE_WINDOW_X, SIZE_WINDOW_Y, SIZE_WINDOW_X+120, SIZE_WINDOW_Y+30, 0xfffff, 0xffff);//尺寸输入
GLCD_SetWindow_Fill( SIZE_WINDOW_X, SIZE_WINDOW_Y, SIZE_WINDOW_X+SIZE_WINDOW_WIDE, SIZE_WINDOW_Y+SIZE_WINDOW_HIGH, 0xfffff, 0xffff);//尺寸输入
PromptNum_dis();
}



void Comment_dis_page(Int8U page)//注释
{
GLCD_Buffer_Fill(0xffff);
volatile Int16U x,y,gap=10,gap1,gap2;
Int8U start_x=50,start_y=20;
switch(page)
	{
	case 0:
		x=start_x+gap,y=start_y+gap;
		gap1=65,gap2=80;
		F1LabelIconUp_dis(x,y);//F1
		x+=gap1;
		switch(Language)
			{
			case CHN_HAN:
					Printf24("标签",x,y+20,BLACK_COLOR,0,0xffff);
					break;
			default:
					Printf24("label",x,y+20,BLACK_COLOR,0,0xffff);
					break;
			}

		x+=gap2;
		F2DivideIconUp_dis(x,y);
		x+=gap1;
		switch(Language)
			{
			case CHN_HAN:
					Printf24("等分",x,y+20,BLACK_COLOR,0,0xffff);
					break;
			default:
					Printf24("Divide",x,y+20,BLACK_COLOR,0,0xffff);
					break;
			}
		

		x+=gap2;
		F3InsertIconUp_dis(x,y);//F3插入
		x+=gap1;
		switch(Language)
			{
			case CHN_HAN:
					Printf24("插入",x,y+20,BLACK_COLOR,0,0xffff);
					break;
			default:
					Printf24("Inser",x,y+20,BLACK_COLOR,0,0xffff);
					break;
			}
		

		x+=gap2;
		F4DeleteIconUp_dis( x, y);//F4 删除up
		x+=gap1;
		switch(Language)
			{
			case CHN_HAN:
					Printf24("删除",x,y+20,BLACK_COLOR,0,0xffff);
					break;
			default:
					Printf24("Del",x,y+20,BLACK_COLOR,0,0xffff);
					break;
			}
		

		x+=gap2;
		F5AddIconUp_dis(x,y);
		x+=gap1;
		switch(Language)
			{
			case CHN_HAN:
					Printf24("自加",x,y+20,BLACK_COLOR,0,0xffff);
					break;
			default:
					Printf24("add",x,y+20,BLACK_COLOR,0,0xffff);
					break;
			}
		
		
				
		// // // *********************第二行
		x=start_x+gap;y+=70;
		gap1=65,gap2=80;
		UpArrow_Up_dis(x,y);
		x+=gap1;
		switch(Language)
			{
			case CHN_HAN:
					Printf24("向上",x,y+20,BLACK_COLOR,0,0xffff);
					break;
			default:
					Printf24("Up",x,y+20,BLACK_COLOR,0,0xffff);
					break;
			}
		

		x+=gap2;
		F6SubIconUp_dis(x,y);
		x+=gap1;
		switch(Language)
			{
			case CHN_HAN:
					Printf24("自减",x,y+20,BLACK_COLOR,0,0xffff);
					break;
			default:
					Printf24("sub",x,y+20,BLACK_COLOR,0,0xffff);
					break;
			}
		
		
		x+=gap2;
		F2RulerIconUp_dis(x,y);
		x+=gap1;
		switch(Language)
			{
			case CHN_HAN:
					Printf24("基准",x,y+20,BLACK_COLOR,0,0xffff);
					break;
			default:
					Printf24("bench",x,y+20,BLACK_COLOR,0,0xffff);
					break;
			}
		
		
		x+=gap2;
		F1ParamaterIconUp_dis(x,y);
		x+=gap1;
		switch(Language)
			{
			case CHN_HAN:
					Printf24("参数",x,y+20,BLACK_COLOR,0,0xffff);
					break;
			default:
					Printf24("param",x,y+20,BLACK_COLOR,0,0xffff);
					break;
			}
		
		
		x+=gap2;
		F3ClockIconUp_dis(x,y);
		x+=gap1;
		switch(Language)
			{
			case CHN_HAN:
					Printf24("时间",x,y+20,BLACK_COLOR,0,0xffff);
					break;
			default:
					Printf24("clock",x,y+20,BLACK_COLOR,0,0xffff);
					break;
			}
		
		
		
		// // *********************第三行
		x=start_x+gap;y+=70;
		gap1=65,gap2=80;
		L_R_Arrow_dis(x,y);
		x+=gap1;
		switch(Language)
			{
			case CHN_HAN:
					Printf24("切换",x,y+20,BLACK_COLOR,0,0xffff);
					break;
			default:
					Printf24("change",x,y+20,BLACK_COLOR,0,0xffff);
					break;
			}
		
		
		x+=gap2;
		DownArrow_Up_dis(x,y);
		x+=gap1;
		switch(Language)
			{
			case CHN_HAN:
					Printf24("向下",x,y+20,BLACK_COLOR,0,0xffff);
					break;
			default:
					Printf24("down",x,y+20,BLACK_COLOR,0,0xffff);
					break;
			}
		
		
		x+=gap2;
		F1OkIconUp_dis(x,y);//F1完成
		x+=gap1;
		switch(Language)
			{
			case CHN_HAN:
					Printf24("完成",x,y+20,BLACK_COLOR,0,0xffff);
					break;
			default:
					Printf24("ok",x,y+20,BLACK_COLOR,0,0xffff);
					break;
			}
		
		
		x+=gap2;
		F2ExitIconUp_dis(x,y);//F2退出
		x+=gap1;
		switch(Language)
			{
			case CHN_HAN:
					Printf24("退出",x,y+20,BLACK_COLOR,0,0xffff);
					break;
			default:
					Printf24("exit",x,y+20,BLACK_COLOR,0,0xffff);
					break;
			}
		
		
		x+=gap2;
		F2DivNumIconUp_dis(x,y);//F2等分数
		x+=gap1;
		switch(Language)
			{
			case CHN_HAN:
					Printf24("等分数",x,y+20,BLACK_COLOR,0,0xffff);
					break;
			default:
					Printf24("div-sum",x,y+20,BLACK_COLOR,0,0xffff);
					break;
			}
		
		
		// // *********************第四行
		x=start_x+gap;y+=70;
		gap1=65,gap2=120;
		F5PulseSetIconUp_dis(x,y);//脉冲当量
		x+=gap1;
		switch(Language)
			{
			case CHN_HAN:
					Printf24("脉冲当量",x,y+20,BLACK_COLOR,0,0xffff);
					break;
			default:
					Printf24("pulse",x,y+20,BLACK_COLOR,0,0xffff);
					break;
			}
		
		
		x+=gap2;
		F6IoTestButton_dis(x,y);
		x+=gap1;
		switch(Language)
			{
			case CHN_HAN:
					Printf24("端口测试",x,y+20,BLACK_COLOR,0,0xffff);
					break;
			default:
					Printf24("IO-test",x,y+20,BLACK_COLOR,0,0xffff);
					break;
			}
		
		
		x+=gap2;
		F3DivDataIconUp_dis(x,y);//等分值
		x+=gap1;
		switch(Language)
			{
			case CHN_HAN:
					Printf24("等分值",x,y+20,BLACK_COLOR,0,0xffff);
					break;
			default:
					Printf24("div-value",x,y+20,BLACK_COLOR,0,0xffff);
					break;
			}
		
		
		x+=gap2;
		F1ShowMessIconUp_dis(x,y);//F1 查看mess
		x+=gap1;
		switch(Language)
			{
			case CHN_HAN:
					Printf24("程序名称",x,y+20,BLACK_COLOR,0,0xffff);
					break;
			default:
					Printf24("prog-name",x,y+20,BLACK_COLOR,0,0xffff);
					break;
			}
		
		
		// // *********************第五行
		x=start_x+gap;y+=70;
		gap1=65,gap2=120;
		F2ByTimeIconUp_dis(x,y);//按时间排序
		x+=gap1;
		switch(Language)
			{
			case CHN_HAN:
					Printf24("按时间显示",x,y+20,BLACK_COLOR,0,0xffff);
					break;
			default:
					Printf24("time-order",x,y+20,BLACK_COLOR,0,0xffff);
					break;
			}
		
		
		x+=gap2;
		F3ByNumIconUp_dis(x,y);//F3 按序号排列
		x+=gap1;
		switch(Language)
			{
			case CHN_HAN:
					Printf24("按序号显示",x,y+20,BLACK_COLOR,0,0xffff);
					break;
			default:
					Printf24("num-order",x,y+20,BLACK_COLOR,0,0xffff);
					break;
			}
		
		
		x+=gap2;
		F4ExitIconUp_dis(x,y);
		x+=gap1;
		switch(Language)
			{
			case CHN_HAN:
					Printf24("退出",x,y+20,BLACK_COLOR,0,0xffff);
					break;
			default:
					Printf24("exit",x,y+20,BLACK_COLOR,0,0xffff);
					break;
			}
		
		
		x+=gap2;
		F4DeleteOneProIconUp_dis(x,y);//F4删除一个pro
		x+=gap1;
		switch(Language)
			{
			case CHN_HAN:
					Printf24("删除程序",x,y+20,BLACK_COLOR,0,0xffff);
					break;
			default:
					Printf24("delete-pro",x,y+20,BLACK_COLOR,0,0xffff);
					break;
			}
		
		
		// *********************第六行
		x=start_x+gap;y+=70;
		gap1=65,gap2=120;
		F5DeleteAllProIconUp_dis(x,y);//F5删除所有
		x+=gap1;
		switch(Language)
			{
			case CHN_HAN:
					Printf24("全删程序",x,y+20,BLACK_COLOR,0,0xffff);
					break;
			default:
					Printf24("delete-all",x,y+20,BLACK_COLOR,0,0xffff);
					break;
			}
		
		
		x+=gap2;
		F1PinyinIconUp_dis(x,y);//F1拼音输入
		x+=gap1;
		switch(Language)
			{
			case CHN_HAN:
					Printf24("拼音输入",x,y+20,BLACK_COLOR,0,0xffff);
					break;
			default:
					Printf24("pinyin-in",x,y+20,BLACK_COLOR,0,0xffff);
					break;
			}
		
		
		x+=gap2;
		F2CharIconUp_dis(x,y);
		x+=gap1;
		switch(Language)
			{
			case CHN_HAN:
					Printf24("字母输入",x,y+20,BLACK_COLOR,0,0xffff);
					break;
			default:
					Printf24("char-in",x,y+20,BLACK_COLOR,0,0xffff);
					break;
			}
		
		
		x+=gap2;
		F3NumIconUp_dis(x,y);
		x+=gap1;
		switch(Language)
			{
			case CHN_HAN:
					Printf24("数字输入",x,y+20,BLACK_COLOR,0,0xffff);
					break;
			default:
					Printf24("num-in",x,y+20,BLACK_COLOR,0,0xffff);
					break;
			}
		
			/***	
		// *********************第7行
		x=start_x+gap;y+=70;
		gap1=65,gap2=120;
		F5RedKnifeButt_dis(x,y);
		x+=gap1;
		switch(Language)
			{
			case CHN_HAN:
					Printf24("刀按钮",x,y+20,BLACK_COLOR,0,0xffff);
					break;
			default:
					Printf24("cutter",x,y+20,BLACK_COLOR,0,0xffff);
					break;
			}
		
		x+=gap2;
		F2PrePaperButt_dis(x,y);
		x+=gap1;
		switch(Language)
			{
			case CHN_HAN:
					Printf24("压纸按钮",x,y+20,BLACK_COLOR,0,0xffff);
					break;
			default:
					Printf24("press",x,y+20,BLACK_COLOR,0,0xffff);
					break;
			}
		
		x+=gap2;
		F4PushPaperButt_dis(x,y);//
		x+=gap1;
		switch(Language)
			{
			case CHN_HAN:
					Printf24("推纸按钮",x,y+20,BLACK_COLOR,0,0xffff);
					break;
			default:
					Printf24("pusher",x,y+20,BLACK_COLOR,0,0xffff);
					break;
			}
		
		x+=gap2;
		F3SortPaperButt_dis(x,y);
		x+=gap1;
		switch(Language)
			{
			case CHN_HAN:
					Printf24("理纸按钮",x,y+20,BLACK_COLOR,0,0xffff);
					break;
			default:
					Printf24("sort",x,y+20,BLACK_COLOR,0,0xffff);
					break;
			}
		**/

		// // *********************第七行
		// // x=start_x+gap;y+=70;
		// // gap1=65,gap2=120;
		// // F3AddIconUp_dis(x,y);
		// // x+=gap1;
		// // Printf24("自加",x,y+20,BLACK_COLOR,0,0xffff);
		
		// // x+=gap2;
		// // F4SubIconUp_dis(x,y);
		// // x+=gap1;
		// // Printf24("自减",x,y+20,BLACK_COLOR,0,0xffff);

		// // x+=gap2;
		// // F4PulseSetIconUp_dis(x,y);
		// // x+=gap1;
		// // Printf24("脉冲当量",x,y+20,BLACK_COLOR,0,0xffff);
		
		
		// // *********************第四行
		// // // x=start_x+gap;y+=80;
		// // // Divide_dis(x,y);
		// // // x+=gap1;
		// // // Printf24("等分",x,y+35,BLACK_COLOR,0,0xffff);

		// // // x+=gap2;
		// // // Teach_dis(x,y);
		// // // x+=gap1;
		// // // Printf24("示教",x,y+35,BLACK_COLOR,0,0xffff);

		// // // x+=gap2;
		// // // Watch_dis(x,y);
		// // // x+=gap1;
		// // // Printf24("时间",x,y+35,BLACK_COLOR,0,0xffff);

		// // *********************第五行
		// // // x=start_x+gap;y+=80;
		// // // Ruler_dis(x,y);
		// // // x+=gap1;
		// // // Printf24("尺子",x,y+35,BLACK_COLOR,0,0xffff);

		// // // x+=gap2;
		// // // Auto_dis(x,y);
		// // // x+=gap1;
		// // // Printf24("自动",x,y+35,BLACK_COLOR,0,0xffff);

		// // // x+=gap2;
		// // // Manual_dis(x,y);
		// // // x+=gap1;
		// // // Printf24("手动",x,y+35,BLACK_COLOR,0,0xffff);

		// // *********************第六行
		// // // x=start_x+gap;y+=80;
		// // // AutoKnife_dis(x,y);
		// // // x+=gap1;
		// // // Printf24("自刀",x,y+35,BLACK_COLOR,0,0xffff);

		// // // x+=gap2;
		// // // SelectPro_dis(x,y);
		// // // x+=gap1;
		// // // Printf24("选择程序",x,y+35,BLACK_COLOR,0,0xffff);
// // // */
		// ------------页码
		switch(Language)
			{
			case CHN_HAN:
					Printf24("1/2 页",350,F2_PAGE_UP_Y,BLACK_COLOR,1,0xffff);
					Printf24("上一页",F2_PAGE_UP_X,F2_PAGE_UP_Y,BLUE_COLOR,1,0xffff);
					Printf24("下一页",F2_PAGE_DOWN_X,F2_PAGE_DOWN_Y,BLUE_COLOR,1,0xffff);
					Printf24("返回《",F2_RET_HELP_X,F2_RET_HELP_Y,BLUE_COLOR,1,0xffff);
					break;
			default:
					Printf24("1/2 pgae",350,F2_PAGE_UP_Y,BLACK_COLOR,1,0xffff);
					Printf24("before",F2_PAGE_UP_X,F2_PAGE_UP_Y,BLUE_COLOR,1,0xffff);
					Printf24("next",F2_PAGE_DOWN_X,F2_PAGE_DOWN_Y,BLUE_COLOR,1,0xffff);
					Printf24("back《",F2_RET_HELP_X,F2_RET_HELP_Y,BLUE_COLOR,1,0xffff);
					break;
			}
		

		break;
	 case 1:
		x=start_x+gap,y=start_y+gap;
		gap1=65,gap2=120;
		F4Wheel0_dis(x,y);
		x+=gap1;
		switch(Language)
			{
			case CHN_HAN:
					Printf24("手轮关",x,y+20,BLACK_COLOR,0,0xffff);
					break;
			default:
					Printf24("wheel-off",x,y+20,BLACK_COLOR,0,0xffff);
					break;
			}
		

		x+=gap2;
		F4Wheel1_dis(x,y);
		x+=gap1;
		switch(Language)
			{
			case CHN_HAN:
					Printf24("手轮开",x,y+5,BLACK_COLOR,0,0xffff);
					break;
			default:
					Printf24("wheel-on",x,y+5,BLACK_COLOR,0,0xffff);
					break;
			}
		
		
		x+=gap2;
		RedKnifeF_dis(x,y);//
		x+=gap1;
		switch(Language)
			{
			case CHN_HAN:
					Printf24("刀图标",x,y+5,BLACK_COLOR,0,0xffff);
					break;
			default:
					Printf24("cut-flag",x,y+5,BLACK_COLOR,0,0xffff);
					break;
			}
		
		
		x+=gap2;
		PushPaperF_dis(x,y);
		x+=gap1;
		switch(Language)
			{
			case CHN_HAN:
					Printf24("推纸图标",x,y+5,BLACK_COLOR,0,0xffff);
					break;
			default:
					Printf24("push-flag",x,y+5,BLACK_COLOR,0,0xffff);
					break;
			}
		
		
		// *********************第二行
		x=start_x+gap,y=y+70;
		gap1=65,gap2=120;
		SortPaperF_dis(x,y);
		x+=gap1;
		switch(Language)
			{
			case CHN_HAN:
					Printf24("理纸图标",x,y+5,BLACK_COLOR,0,0xffff);
					break;
			default:
					Printf24("sort-flag",x,y+5,BLACK_COLOR,0,0xffff);
					break;
			}
		
				
		x+=gap2;
		PressPaperF_dis(x,y);
		x+=gap1;
		switch(Language)
			{
			case CHN_HAN:
					Printf24("压纸图标",x,y+5,BLACK_COLOR,0,0xffff);
					break;
			default:
					Printf24("press-flag",x,y+5,BLACK_COLOR,0,0xffff);
					break;
			}
		
		
		x+=gap2;
		AirBedF_dis(x,y);//
		x+=gap1;
		switch(Language)
			{
			case CHN_HAN:
					Printf24("气垫图标",x,y+5,BLACK_COLOR,0,0xffff);
					break;
			default:
					Printf24("air-flag",x,y+5,BLACK_COLOR,0,0xffff);
					break;
			}
		
		
		x+=gap2;
		Knife_Up_dis(x,y);
		x+=gap1;
		switch(Language)
			{
			case CHN_HAN:
					Printf24("刀上",x,y+5,BLACK_COLOR,0,0xffff);
					break;
			default:
					Printf24("cut-up",x,y+5,BLACK_COLOR,0,0xffff);
					break;
			}
		
		
		
		// *********************第3行
		x=start_x+gap,y=y+70;
		gap1=65,gap2=120;
		Knife_Down_dis(x,y);
		x+=gap1;
		switch(Language)
			{
			case CHN_HAN:
					Printf24("刀下",x,y+5,BLACK_COLOR,0,0xffff);
					break;
			default:
					Printf24("cut-down",x,y+5,BLACK_COLOR,0,0xffff);
					break;
			}
		
		
		x+=gap2;
		Press_Up_dis(x,y);
		x+=gap1;
		switch(Language)
			{
			case CHN_HAN:
					Printf24("压上",x,y+5,BLACK_COLOR,0,0xffff);
					break;
			default:
					Printf24("press-up",x,y+5,BLACK_COLOR,0,0xffff);
					break;
			}
		
		/**
		x+=gap2;
		F1AirBedButt_dis(x,y);
		x+=gap1;
		switch(Language)
			{
			case CHN_HAN:
					Printf24("气垫按钮",x,y+20,BLACK_COLOR,0,0xffff);
					break;
			default:
					Printf24("air-button",x,y+20,BLACK_COLOR,0,0xffff);
					break;
			}
		**/
		
		// // *********************第三行
		// // x=start_x+gap,y=y+70;
		// // gap1=65,gap2=120;
		
		
		// // *********************第四行
		// // x=start_x+gap,y=y+70;
		// // gap1=70,gap2=120;
		// // Press_Down_dis(x,y);
		// // x+=gap1;
		// // Printf24("压下",x,y+5,BLACK_COLOR,0,0xffff);

		// // x+=gap2;
		// // RunButtonUp_dis(x,y);
		// // x+=gap1;
		// // Printf24("运行",x,y+5,BLACK_COLOR,0,0xffff);

		// // x+=gap2;
		// // ShiftButtonUp_dis(x,y);
		// // x+=gap1;
		// // Printf24("换挡",x,y+5,BLACK_COLOR,0,0xffff);

		// // *********************第五行
		// // x=start_x+gap,y=y+70;
		// // gap1=70,gap2=120;
		// // F4Wheel0_dis(x,y);
		// // x+=gap1;
		// // Printf24("手轮关闭",x,y+5,BLACK_COLOR,0,0xffff);

		// // x+=gap2;
		// // F4Wheel1_dis(x,y);
		// // x+=gap1;
		// // Printf24("手轮打开",x,y+5,BLACK_COLOR,0,0xffff);		
		
		// // x+=gap2;
		// // IR_LINE_dis(x,y);//红线
		// // x+=gap1;
		// // Printf24("红外线",x,y+5,BLACK_COLOR,0,0xffff);		
		
		// // x+=gap2;
		// // IR_CUT_dis(x,y);//红线
		// // x+=gap1;
		// // Printf24("红外断开",x,y+5,BLACK_COLOR,0,0xffff);		
		
		// // *********************第六行
		// // // x=start_x+gap;y+=80;
		// // // gap1=90,gap2=80;
		// // // Wheel1_dis(x,y);
		// // // x+=gap1;
		// // // Printf24("手轮开",x,y+5,BLACK_COLOR,0,0xffff);

		
		
		// // *********************第七行
		// // // x=start_x+gap;y+=70;
		
		// ------------页码
		switch(Language)
			{
			case CHN_HAN:
					Printf24("2/2 页",350,F2_PAGE_UP_Y,BLACK_COLOR,1,0xffff);
					Printf24("上一页",F2_PAGE_UP_X,F2_PAGE_UP_Y,BLUE_COLOR,1,0xffff);
					Printf24("下一页",F2_PAGE_DOWN_X,F2_PAGE_DOWN_Y,BLUE_COLOR,1,0xffff);
					Printf24("返回《",F2_RET_HELP_X,F2_RET_HELP_Y,BLUE_COLOR,1,0xffff);
					break;
			default:
					Printf24("2/2 page",350,F2_PAGE_UP_Y,BLACK_COLOR,1,0xffff);
					Printf24("before",F2_PAGE_UP_X,F2_PAGE_UP_Y,BLUE_COLOR,1,0xffff);
					Printf24("next",F2_PAGE_DOWN_X,F2_PAGE_DOWN_Y,BLUE_COLOR,1,0xffff);
					Printf24("back《",F2_RET_HELP_X,F2_RET_HELP_Y,BLUE_COLOR,1,0xffff);
					break;
			}
		

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

void CurrentArea_save4(Int16U x,Int16U y, Int16U Wide,Int16U High)//暂存  当前区域 画面4
{
pInt16U pDis,pBuf;
volatile Int16U h,w;
pDis=(pInt16U)(SDRAM0_BASE_ADDR+(y*C_GLCD_H_SIZE+x)*2);
pBuf=(pInt16U)PIC_DIS_SAVE4;
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
void CurrentArea_recover4(Int16U x, Int16U y, Int16U Wide,Int16U High)//恢复  当前区域 画面4
{
pInt16U pDis,pBuf;
volatile Int16U h,w;
pDis=(pInt16U)(SDRAM0_BASE_ADDR+(y*C_GLCD_H_SIZE+x)*2);
pBuf=(pInt16U)PIC_DIS_SAVE4;
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
pInt8U Err_XXX="XXXXXXX";

x=CURR_SIZE_X;
y=CURR_SIZE_Y;
back_color=CURREN_STEP_BACK_COLOR;
if(ACServoDrvErr_flag==0)
	{
	if(Unit!=UNIT_MM)//inch
		{
		//if(SelfLockEn_flag==1)  //自锁
			//{
			switch(MotorType)
				{
				case MOTOR_FREQ_5_SPD_RST:
				case MOTOR_FREQ_3_SPD:
				case MOTOR_FREQ_3_SPD_RST:
					 Virture_size=VirtualTargetSizeGap;
						break;
				// // case MOTOR_DC_SERVO:
				// // case MOTOR_DC670_SERVO:
					 // // Virture_size=DC_VIRTURE_SIZE;
						// // break;
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
	Printf32(num,x,y,0,1,back_color);
	//ASCII_Printf(num,224+1,28,56,ASCII_28x56, x,y,0xffff,back_color);
	//ASCII_Printf(num,192+1,32,48,ASCII_32x48, x,y,0,back_color);
	}
else		//警报 不显示尺寸
	{
	// ASCII_Printf(Err_XXX,192+1,32,48,ASCII_32x48, x,y,RED_COLOR,back_color);
	Printf32(Err_XXX,x,y,RED_COLOR,1,back_color);
	}
}


void FrontKnifeUint_dis(Int8U unit)  //刀前尺寸 单位--------------
{
Int16U x,y,back_color=CURREN_UNIT_BACK_COLOR;
x=FRONT_KNIFE_X+120;//200;
y=FRONT_KNIFE_Y+5;
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
}

void FrontKnifeSize_dis(Int32U size)//刀前尺寸-----------------
{
Int8U num[8],k;
Int16U x,y,back_color=FRONT_KNIFE_BACK_COLOR;
x=FRONT_KNIFE_X;
y=FRONT_KNIFE_Y;
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
Printf24(num,x,y,BLACK_COLOR,1,back_color);
//ASCII_Printf(num,108+1,20,36,ASCII_20x36, x,y,0,back_color);
}
void FrontKnifeSize_NOdis(void)
{
Int16U x,y,back_color=0xf78a;
x=FRONT_KNIFE_X;
y=FRONT_KNIFE_Y;
// GLCD_SetWindow_Fill(x-1, y, x+140, y+36, back_color, back_color);
GLCD_SetWindow_Fill(x-1, y, x+100, y+30, back_color, back_color);
}


void InputNum_dis(pInt8U nums,Int8U cou) //输入框内  尺寸输入显示
{
Int8U num_temp[8],n=0;
Int16U x,y,back_color,f_color;
back_color=WHITE_COLOR;f_color=0;
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
// Printf24(num_temp,SIZE_WINDOW_X+25,SIZE_WINDOW_Y+5,BLACK_COLOR,1,0xffff);
x=SIZE_WINDOW_X+SIGN_2WIDE;	y=SIZE_WINDOW_Y+2;
ASCII_Printf(num_temp,108+1,20,36,ASCII_20x36, x,y,f_color,back_color);
}

void CursorPro_dis(Int8U row, Int8U show_flag)// 程序号 蓝色箭头 光标
{
Int16U x,y,back_color=TEXT_TAB_BACK_COLOR;//0xef9f;
if(row<PROGS_1PAGE)
   {
   TableDis_startcol=PRO_RIGHT_ARROW_X;
   }
else
   {
   TableDis_startcol=RIGHT_PAGE_X;
   }
x=TableDis_startcol;
y=PRO_RIGHT_ARROW_Y+(row%PROGS_1PAGE)*PROTEXT_HIGH+10;
if(show_flag==1)//显示
   {
   RightArrow_dis(x,y);
   }
else
   {
   GLCD_SetWindow_Fill( x, y, x+PRO_ARROW_WIDE, y+PRO_ARROW_HIGH, back_color, back_color);//消失
   }
}

void ProgOrder_dis(Int16U row, Int16U order,Int16U num_color)//一个 程序号--------显示
{
Int8U num[5],k;
Int16U x,y,back_color=TEXT_TAB_BACK_COLOR;//0xef9f;
if(row<PROGS_1PAGE)
   {
   TableDis_startcol=PROC_NUM_X;
   }
else
   {
   // TableDis_startcol=RIGHT_PAGE_X+25;	//xxxxxxxxxxxx
   }
x=TableDis_startcol;
y=PROC_NUM_Y+(row%PROGS_1PAGE)*PROTEXT_HIGH;

num[0]=order/100;
num[1]=(order/10)%10;
num[2]=order%10;
num[3]=0;
for(k=0;k<3;k++)
  {
  num[k]+=48;
  }
Printf24(num,x,y,num_color,1,back_color);//序号
//ASCII_Printf(num,114+1,18,38,ASCII_bold18x38, x,y,num_color,back_color);
}
void ProgName_dis(Int16U row, PROCESS_HEAD pro_head,Int16U num_color)//-----------------------显示一个程序名
{
Int8U k=0,check=0;
Int16U x,y,back_color=TEXT_TAB_BACK_COLOR,x2;//0xef9f;
pInt8U pName;
pName=pro_head.pro_name_flag;
if(row<PROGS_1PAGE)
   {
   TableDis_startcol=PROC_NAME_X;
   }
else
   {
   // TableDis_startcol=RIGHT_PAGE_X+25;	//xxxxxxxxxxxx
   }
x=TableDis_startcol;
y=PROC_NAME_Y+(row%PROGS_1PAGE)*PROTEXT_HIGH;
while(*(NAME_flag+k)!='\0')
	{
	if(*(NAME_flag+k)==*(pName+k))
		check++;
	else
		break;
	k++;
	}
x2=PROC_STEP_X-10;
//***********显示 程序名字
pName=pro_head.pro_name;
GLCD_SetWindow_Fill(x, y, x2, y+PROTEXT_HIGH, back_color, back_color);//清除名称
if(check>=4)	//if(*pName!=0)//已命名
	{
	//限制长度-----
	k=0;
	while(*(pName+k)!='\0')
		{
		k++;
		if(k>20)
			{
			*(pName+k)='\0';
			*(pName+k-1)='.';
			*(pName+k-2)='.';
			*(pName+k-3)='.';
			break;
			}
		}
	Printf16(pName,x,y,num_color,1,back_color);//显示名称
	}
}
void ProgStep_dis(Int16U row, PROCESS_HEAD pro_head,Int16U num_color)//-----------------------显示步骤数
{
Int8U num[5],k;
Int16U x,y,back_color=TEXT_TAB_BACK_COLOR;//0xef9f;
Int16U step;
step=pro_head.pro_knifeSUM;
if(row<PROGS_1PAGE)
   {
   TableDis_startcol=PROC_STEP_X;
   }
else
   {
   // TableDis_startcol=RIGHT_PAGE_X+25;	//xxxxxxxxxxxx
   }
x=TableDis_startcol;
y=PROC_STEP_Y+(row%PROGS_1PAGE)*PROTEXT_HIGH;

num[0]=step/100;
num[1]=(step/10)%10;
num[2]=step%10;
num[3]=0;
for(k=0;k<3;k++)
  {
  num[k]+=48;
  }
Printf24(num,x,y,num_color,1,back_color);//
}
void ProgDate_dis(Int16U row, PROCESS_HEAD pro_head,Int16U num_color)//-----------------------显示日期
{
Int8U num[12],k;
Int8U year,month,day;
Int16U x,y,back_color=TEXT_TAB_BACK_COLOR;//0xef9f;
if(row<PROGS_1PAGE)
   {
   TableDis_startcol=PROC_DATE_X;
   }
else
   {
   // TableDis_startcol=RIGHT_PAGE_X+25;	//xxxxxxxxxxxx
   }
x=TableDis_startcol;
y=PROC_DATE_Y+(row%PROGS_1PAGE)*PROTEXT_HIGH;

year=pro_head.pro_year;
month=pro_head.pro_month;
day=pro_head.pro_day;
k=0;
if(year==0&&month==0&&day==0)
	{
	num[k++]='0';
	}
else
	{
	num[k++]='2';
	}
num[k++]='0';
num[k++]=((year>>4)&0xf)+48;
num[k++]=(year&0xf)+48;
num[k++]='-';
num[k++]=((month>>4)&0xf)+48;
num[k++]=(month&0xf)+48;
num[k++]='-';
num[k++]=((day>>4)&0xf)+48;
num[k++]=(day&0xf)+48;
num[k++]=0;
Printf24(num,x,y,num_color,1,back_color);//
}

void CursorKnife_dis(Int8U row, Int8U show_flag)// 刀数据 蓝色箭头 光标
{
Int16U x,y,back_color=TEXT_TAB_BACK_COLOR;//0xef9f;
if(row>(PageKf_Size-1))
   {
   TableDis_startcol=RIGHT_PAGE_X;
   }
else
   {
   TableDis_startcol=RIGHT_ARROW_X;
   }
x=TableDis_startcol;
y=RIGHT_ARROW_Y+(row%PageKf_Size)*Kf_Line_HIGH;
if(show_flag==1)//显示
   {
   RightArrow_dis(x,y);
   }
else
   {
   GLCD_SetWindow_Fill( x, y, x+RIGHT_ARROW_WIDE, y+RIGHT_ARROW_HIGH, back_color, back_color);//消失
   }
}

void KnifeOrder_dis(Int16U row, Int16U order,Int16U num_color)//-----------------------显示一个序号
{
Int8U num[5],k;
Int16U x,y,back_color=TEXT_TAB_BACK_COLOR;//0xef9f;
if(row>(PageKf_Size-1))
   {
   TableDis_startcol=RIGHT_PAGE_X;
   }
else
   {
   TableDis_startcol=RIGHT_ARROW_X;
   }
x=TableDis_startcol+RIGHT_ARROW_WIDE;
y=RIGHT_ARROW_Y+(row%PageKf_Size)*Kf_Line_HIGH;

num[0]=order/100;
num[1]=(order/10)%10;
num[2]=order%10;
num[3]=0;
for(k=0;k<3;k++)
  {
  num[k]+=48;
  }
//===============
if(num_color==RED_COLOR)
	{
	back_color=TEXT_TAB_FRONT_COLOR;
	num_color=0;
	}
else
	{
	}
GLCD_SetWindow_Fill( x, y, x+100, y+TEXT_LINE_H, back_color, back_color);
switch(PageKf_Size_flag)
	{
	case PAGE_5_LINE:	//5 line
		// ASCII_Printf(num,114+1,18,38,ASCII_bold18x38, x,y,num_color,back_color);
		 ASCII_Printf(num,64+1,16,32,ASCII_bold16x32, x,y,num_color,back_color);
		//Printf32(num,x,y,num_color,1,back_color);//序号
		break;
	case PAGE_7_LINE:	//7 line
		Printf32(num,x,y,num_color,1,back_color);//序号
		break;
	}
}

void KnifeSize_dis(Int16U row,  Int32U Knife_size,Int16U num_color)//--------------显示一个尺寸
{
Int8U num[8],k;
Int16U x,y,back_color=TEXT_TAB_BACK_COLOR;//0xef9f;
Int32U size_inc;
if(row>(PageKf_Size-1))
   {
   TableDis_startcol=RIGHT_PAGE_X;
   }
else
   {
   TableDis_startcol=RIGHT_ARROW_X;
   }  
x=TableDis_startcol+100;
y=RIGHT_ARROW_Y+(row%PageKf_Size)*Kf_Line_HIGH;

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
//===============
if(num_color==RED_COLOR)
	{
	back_color=TEXT_TAB_FRONT_COLOR;
	num_color=0;
	}
switch(PageKf_Size_flag)
	{
	case PAGE_5_LINE:	//5 line
		// ASCII_Printf(num,120+1,24,40,ASCII_bold24x40, x,y,num_color,back_color);
		ASCII_Printf(num,64+1,16,32,ASCII_bold16x32, x,y,num_color,back_color);
		break;
	case PAGE_7_LINE:	//7 line
		Printf32(num,x,y,num_color,1,back_color);//
		break;
	}
ReadAir_flag=0;
}

void AllFlagPic_dis(Int8U row,  Int8U Knife_flag)//-------(2个)  标志显示
{
Int16U x1,y1,x2,y2,back_color=TEXT_TAB_BACK_COLOR;
x1=AIR_FLAG_PIC_X;
y1=AIR_FLAG_PIC_Y+row*Kf_Line_HIGH;
x2=TABLE_END_COL;
y2=y1+FLAG_PIC_HIGH;
GLCD_SetWindow_Fill(x1, y1, x2, y2, back_color, back_color);//图标消失
x1=RED_KNIFE_PIC_X;
switch(Knife_flag&0x0F)
	{
	case PUSH_FLAG:  //推纸图标显示
		PushPaperF_dis(x1,y1);
			break;
	case SORT_FLAG:   // 理纸
		SortPaperF_dis(x1,y1);
			break;
	case PRESS_FLAG:   // 压纸
		PressPaperF_dis(x1,y1);
			break;		
	case KNIFE_FLAG:  //刀图标		
		RedKnifeF_dis(x1,y1);
			break;
	case FLAG_FLAG:
		OtherSetF_dis( x1, y1);//其他标记
			break;
	}
x1=AIR_FLAG_PIC_X;
switch(Knife_flag&0xF0)	
	{
	case AIR_FLAG: //气垫  标志位
		AirBedF_dis(x1,y1);
			break;
	case NOAIR_FLAG: //无气垫  标志位
		NoAirBedF_dis(x1,y1);
			break;
	}
ReadAir_flag=0;
}

Int8U OneKnifeDataSel_dis(Int16U knife,Int8U row,Int16U num_color)  //一刀数据 高亮显示
{
KNIFE_DATA Knife_datas;
GetOneKnife_datas(Pro_data.pro_num, knife , (pInt8U)&Knife_datas);//取出一刀 数据
//-----------------步骤(尺寸)错误 判断 
// if((Knife_datas.size<Size_MIN_num)||(Knife_datas.size>Size_MAX_num))
	/*****************************************************************2015--12--31---
if(0)		
	{
	Knife_datas.size=0;
	Knife_datas.k_flag=0;
	if(OnePro_head.pro_knifeSUM>=knife)
		{
		if(knife>1)
			OnePro_head.pro_knifeSUM=knife-1;
		else
			OnePro_head.pro_knifeSUM=1;
		Knife_sum_before=OnePro_head.pro_knifeSUM;
		SavePro_headInfo(Pro_data.pro_num, (pInt8U)&OnePro_head);	//保存**
		StepNum_dis(OnePro_head.pro_knifeSUM, knife);//步骤更新
		}
	}**/
if(knife>OnePro_head.pro_knifeSUM)	//最后一个步骤 之后仍有数据 则清除
	{
	if(Knife_datas.size>0)
		{
		Knife_datas.size=0;
		Knife_datas.k_flag=0;
		}
	}	
KnifeOrder_dis(row, knife,num_color);//序号
KnifeSize_dis(row,  Knife_datas.size, num_color);//--------------显示一个尺寸
if((ButtonTouch_mode==0)||(ButtonTouch_mode==TOU_MODE_F4)) //	 非 触摸计算器 下
	AllFlagPic_dis(row,Knife_datas.k_flag); //  标志  
CursorSize_dis(Knife_datas.size);	//标称尺寸  显示=============
return Knife_datas.k_flag;
}

void OneProNum_dis(Int16U pro_order, PROCESS_HEAD pro_head) //程序号码显示
{
Int16U x,y,back_color,line_color;//=0x2E3B;
Int8U num[4],k=0,check=0;
pInt8U pName=pro_head.pro_name_flag;
back_color=STEP_BACK_COLOR;
x=PROG_NUM_X,y=PROG_NUM_Y;
num[0]=pro_order/100;
num[1]=(pro_order/10)%10;
num[2]=pro_order%10;
num[3]=0;
for(k=0;k<3;k++)
   {
   num[k]+=48;
   }
Printf16(num,x,y,BLACK_COLOR,1,back_color);//程序
x=PRO_NAME_DIS_X, y=PRO_NAME_DIS_Y;
line_color=back_color=PRO_NAME_DIS_COLOR;
//***********显示 程序名字
k=0;
while(*(NAME_flag+k)!='\0')
	{
	if(*(NAME_flag+k)==*(pName+k))
		check++;
	else
		break;
	k++;
	}
GLCD_SetWindow_Fill(x, y, x+(PRONAME_SIZE*12), y+25, line_color, back_color);//清除名称
if(check>=4)//已命名
	{
	pName=pro_head.pro_name;
	line_color=GREEN_COLOR;
	Printf24(pName,x,y,line_color,1,back_color);//显示名称
	}
}

void StepNum_dis(Int16U step_sum,Int16U step_order) //步骤号码显示(总刀数-刀号)
{
Int16U x,y,back_color;//=0x2E3B;
Int8U num[8],k;
back_color=STEP_BACK_COLOR;//----------
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
Printf16(num,x,y,BLACK_COLOR,1,back_color);// 步骤
// if(ButtonTouch_mode==0)  //	 非 触摸计算器 下
	// {
	switch(WorkMode)
		{
		case AUTO_MODE://自动主画面下
		case AUTO_PLUS_MODE://自动F5++
		case AUTO_MINUS_MODE://自动F6--
		
		case TEACH_MODE://示教 模式
		case AUTO_TO_SELF_MODE:   //自动-->自刀过度 模式
		case SELF_CUT_MODE:  //自刀主 模式
		case TEACH_PLUS_MODE: //自刀 F5++
		case TEACH_MINUS_MODE://自刀 F6--
			ProgressBar_dis(step_sum, step_order);//进度条 显示
			break;
		}	
	// }
}

void StepOrder_dis(Int16U step_order)//(-刀号)  步骤显示
{
Int16U x,y,back_color;//=0x2E3B;
Int8U num[4],k;
back_color=STEP_BACK_COLOR;//----------
x=STEP_NUM_X+32,y=STEP_NUM_Y;
num[0]=step_order/100;
num[1]=(step_order/10)%10;
num[2]=step_order%10;
num[3]=0;
for(k=0;k<3;k++)
   {
   num[k]+=48;
   }
Printf16(num,x,y,BLACK_COLOR,1,back_color);// 步骤
// if(ButtonTouch_mode==0)  //	 非 触摸计算器 下
	// {
	switch(WorkMode)
		{
		case AUTO_MODE://自动主画面下
		case AUTO_PLUS_MODE://自动F5++
		case AUTO_MINUS_MODE://自动F6--
		
		case TEACH_MODE://示教 模式
		case AUTO_TO_SELF_MODE:   //自动-->自刀过度 模式
		case SELF_CUT_MODE:  //自刀主 模式
		case TEACH_PLUS_MODE: //自刀 F5++
		case TEACH_MINUS_MODE://自刀 F6--
			ProgressBar_dis(OnePro_head.pro_knifeSUM,Knife_order);  //进度条 显示
			break;
		}	
	// }
}










void MoveForward(void)//前进
{
MotorRun_flag=1;
switch(MotorType)
	{
	case MOTOR_FREQ_5_SPD_RST: //----5档速 
		RLOUT3_ON;   //   后退断开
		RLOUT2_OFF;  //   前进闭合
		
		RLOUT5_OFF;  //   刹车闭合------------5档
		break;
	case MOTOR_FREQ_3_SPD: //----3 档速	
	case MOTOR_FREQ_3_SPD_RST: //----3 档速+复位	
		RLOUT2_OFF; // RLOUT3_OFF; //   刹车闭合
		OOUT2_OFF;  //	前进 闭合
		OOUT1_ON;  //  后退 断开
		
		break;
	}
if(SelfLockEn_flag == 0) //  未定位--
	{
	RLOUT1_ON;   RLOUT1_1_ON; // 允许裁切断开	
	}
else
	{
	// if(PressDown_flag == 0)// 压纸 未下			20170927
		// RLOUT1_ON;    // 允许裁切断开
	}
CutPermit_flag=0;	
}
void MoveBack(void) //后退
{
MotorRun_flag=1;
switch(MotorType)
	{
	case MOTOR_FREQ_5_SPD_RST: //----5档速
		RLOUT3_OFF;//   后退闭合
		RLOUT2_ON;

		RLOUT5_OFF;  //   刹车闭合------------5档
		break;
	case MOTOR_FREQ_3_SPD: //----3 档速	
	case MOTOR_FREQ_3_SPD_RST: //----3 档速+复位	
		RLOUT2_OFF; // RLOUT3_OFF; //   刹车闭合
		OOUT1_OFF;  //	后退 闭合
		OOUT2_ON;  //  前进 断开
		
		break;
	}	
if(SelfLockEn_flag == 0) //  未定位--
	{
	RLOUT1_ON;   RLOUT1_1_ON; // 允许裁切断开	
	}
else
	{
	// if(PressDown_flag == 0)// 压纸 未下			20170927
		// RLOUT1_ON;    // 允许裁切断开
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
			RLOUT2_ON;  //RLOUT3_ON;  //   刹车断开
			RLOUT1_OFF; RLOUT1_1_OFF;   // 允许裁切	
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
			case MOTOR_FREQ_5_SPD_RST: //----5 档速
				OOUT1_ON;
				OOUT3_ON;
				OOUT4_OFF;  
					break;
			case MOTOR_FREQ_3_SPD: //----3 档速	
			case MOTOR_FREQ_3_SPD_RST: //----3 档速+复位		
				OOUT3_ON;
				OOUT4_OFF; 
					break;
			}
		//RLOUT1_ON;    // 允许裁切断开
			break;
	case 2: //中高速
		switch(MotorType)
			{
			case MOTOR_FREQ_5_SPD_RST: //----5 档速
				OOUT1_ON;
				OOUT3_OFF;
				OOUT4_OFF;  
					break;
			case MOTOR_FREQ_3_SPD: //----3 档速	
			case MOTOR_FREQ_3_SPD_RST: //----3 档速+复位		
				OOUT3_OFF;
				OOUT4_OFF; 
					break;
			}
		//RLOUT1_ON;    // 允许裁切断开
			break;	
	case 3: //中速
		switch(MotorType)
			{
			case MOTOR_FREQ_5_SPD_RST: //----5 档速
				OOUT1_OFF;
				OOUT3_OFF;
				OOUT4_ON;  
					break;
			case MOTOR_FREQ_3_SPD: //----3 档速	
			case MOTOR_FREQ_3_SPD_RST: //----3 档速+复位		
				//OOUT3_OFF;
				//OOUT4_OFF; 
				OOUT3_OFF;
				OOUT4_ON;
					break;
			}
		//RLOUT1_ON;    // 允许裁切断开
			break;
	case 4: //低速
		switch(MotorType)
			{
			case MOTOR_FREQ_5_SPD_RST: //----5 档速
				OOUT1_ON;
				OOUT3_OFF;
				OOUT4_ON;  
					break;
			case MOTOR_FREQ_3_SPD: //----3 档速	
			case MOTOR_FREQ_3_SPD_RST: //----3 档速+复位		
				OOUT3_OFF;
				OOUT4_ON; 
					break;
			}
		//RLOUT1_ON;    // 允许裁切断开
			break;
	case 5://复位
		switch(MotorType)
			{
			case MOTOR_FREQ_5_SPD_RST: //----5 档速
				OOUT1_OFF;
				OOUT3_ON;
				OOUT4_ON; 
					break;
			//case 1://----3 档速	
			case MOTOR_FREQ_3_SPD_RST: //----3 档速+复位		
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
		if(MoveSpeed!=2)
			{
			MoveSpeed=2;//1;
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
				if(temp>1200) //12-80  中高速
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
						// if(temp>50)//0.5-6 低速	20170927
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
						// else
							// {
							// if(Run_flag==0)
								// {
								// if(MoveSpeed!=3)
									// {
									// MoveSpeed=3;
									// SetMotorSpeed(MoveSpeed);
									// }
									// MoveBack();  //后退
									// Forward_flag=0;
									// Backward_flag=1;
								// }
							// else
								// {
						
								// }
							// }
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



void SpeedLevelSel_dis(Int8U motor,Int8U set_flag)    //电机驱动类型 显示
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
x=200,y=200;gap=40;
switch(motor)
	{
	case MOTOR_FREQ_5_SPD_RST://五档速带复位
		switch(Language)
			{
			case CHN_HAN:
				Printf24("1------五档速带复位",x,y,F_color,1,B_color);
				break;
			case ENGLISH:
			case INDONSIA:	//印尼
			case PORTUGAL:	//葡萄牙
			case SPANISH: //西班牙
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
			case INDONSIA:	//印尼
			case PORTUGAL:	//葡萄牙
			case SPANISH: //西班牙
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
			case INDONSIA:	//印尼
			case PORTUGAL:	//葡萄牙
			case SPANISH: //西班牙
				Printf24("3------3 gears and rest",x,y,F_color,1,B_color);
				break;
			}
		break;
		
	case MOTOR_AC_SERVO:	 		//交流伺服	
		y+=gap*3;
		switch(Language)
			{
			case CHN_HAN:
				Printf24("4------交流伺服正向(1:2)",x,y,F_color,1,B_color);
				break;
			case ENGLISH:
			case INDONSIA:	//印尼
			case PORTUGAL:	//葡萄牙
			case SPANISH: //西班牙
				Printf24("4------AC servo Forward(1:2)",x,y,F_color,1,B_color);
				break;
			}
		break;	
	case MOTOR_AC_SERVO_REV:	 		//交流伺服	
		y+=gap*4;
		switch(Language)
			{
			case CHN_HAN:
				Printf24("5------交流伺服反向(1:1)",x,y,F_color,1,B_color);
				break;
			case ENGLISH:
			case INDONSIA:	//印尼
			case PORTUGAL:	//葡萄牙
			case SPANISH: //西班牙
				Printf24("5------AC servo Reverse(1:1)",x,y,F_color,1,B_color);
				break;
			}
		break;	
	}
}

void NewInput_dis(Int32U size)
{
Int8U num[8],n=0;
Int16U x,y,back_color,f_color;
back_color=WHITE_COLOR;f_color=0;

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
GLCD_SetWindow_Fill( SIZE_WINDOW_X, SIZE_WINDOW_Y, SIZE_WINDOW_X+SIZE_WINDOW_WIDE, SIZE_WINDOW_Y+SIZE_WINDOW_HIGH, 0xfffff, 0xffff);//尺寸输入
// Printf24(num,SIZE_WINDOW_X+25,SIZE_WINDOW_Y+5,BLACK_COLOR,1,0xffff);
x=SIZE_WINDOW_X+SIGN_2WIDE;	y=SIZE_WINDOW_Y+2;
ASCII_Printf(num,108+1,20,36,ASCII_20x36, x,y,f_color,back_color);
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
// gap1=10,gap2=20,gap3=25;
gap1=10,gap2=10,gap3=10;
/*****
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
	 case BUTT_EQU:
			x=BUTT_X1;
			y=BUTT_Y5;
			GLCD_SetWindow_Fill(x,y,x+BUTT_WIDE*2+BUTT_GAP_X,y+BUTT_HIGH,butt_color,butt_color);
			x+=gap3*2;y+=gap2;
			Printf24("=",x,y,num_color,0,0xffff);
			break;
	 case BUTT_ENTER:
			x=BUTT_X3;
			y=BUTT_Y5;
			GLCD_SetWindow_Fill(x,y,x+BUTT_WIDE*2+BUTT_GAP_X,y+BUTT_HIGH,butt_color,butt_color);
			x+=gap3*2;y+=gap2;
			switch(Language)
				{
				case CHN_HAN:
						Printf16("确认",x,y,num_color,0,0xffff);
						break;
				case ENGLISH:
				case PORTUGAL:	//葡萄牙
				case SPANISH: //西班牙
						Printf16(" OK",x,y,num_color,0,0xffff);
						break;
				case INDONSIA:	//印尼
						Printf16(" Ya",x,y,num_color,0,0xffff);
						break;
				}
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
	 case BUTT_PLUS:
			x=BUTT_X4;
			y=BUTT_Y1;
			GLCD_SetWindow_Fill(x,y,x+BUTT_WIDE,y+BUTT_HIGH,butt_color,butt_color);
			x+=gap3;y+=gap2;
			Printf24("+",x,y,num_color,0,0xffff);
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
	 case BUTT_SUB:
			x=BUTT_X4;
			y=BUTT_Y2;
			GLCD_SetWindow_Fill(x,y,x+BUTT_WIDE,y+BUTT_HIGH,butt_color,butt_color);
			x+=gap3;y+=gap2;
			Printf24("-",x,y,num_color,0,0xffff);
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
	 case BUTT_MUL:
			x=BUTT_X4;
			y=BUTT_Y3;
			GLCD_SetWindow_Fill(x,y,x+BUTT_WIDE,y+BUTT_HIGH,butt_color,butt_color);
			x+=gap3;y+=gap2;
			Printf24("*",x,y,num_color,0,0xffff);
			break;
			
	 case BUTT_CLEAR:
			x=BUTT_X1;
			y=BUTT_Y4;
			GLCD_SetWindow_Fill(x,y,x+BUTT_WIDE,y+BUTT_HIGH,butt_color,butt_color);
			x+=gap3;y+=gap2;
			Printf24("C",x,y,num_color,0,0xffff);
			break;
	 case BUTT_0:
			x=BUTT_X2;
			y=BUTT_Y4;
			GLCD_SetWindow_Fill(x,y,x+BUTT_WIDE,y+BUTT_HIGH,butt_color,butt_color);
			x+=gap3;y+=gap2;
			Printf24("0",x,y,num_color,0,0xffff);
			break;	
	 case BUTT_DOT:
			x=BUTT_X3;
			y=BUTT_Y4;
			GLCD_SetWindow_Fill(x,y,x+BUTT_WIDE,y+BUTT_HIGH,butt_color,butt_color);
			x+=gap3;y+=gap2;
			Printf24(".",x,y,num_color,0,0xffff);
			break;		
	 case BUTT_DIV:
			x=BUTT_X4;
			y=BUTT_Y4;
			GLCD_SetWindow_Fill(x,y,x+BUTT_WIDE,y+BUTT_HIGH,butt_color,butt_color);
			x+=gap3;y+=gap2;
			Printf24("/",x,y,num_color,0,0xffff);
			break;
	}
*****/	
	
if(down_flag==1)  //按下后
	{
	switch(b_num)
		{
		case BUTT_EQU:
				CalButtonEqu_down_dis(BUTT_X1,BUTT_Y5);
				break;
		 case BUTT_ENTER:
				CalButtonOk_down_dis(BUTT_X3,BUTT_Y5);
				break;
		 case BUTT_1:
				CalButton1_down_dis(BUTT_X1,BUTT_Y1);
				break;		
		 case BUTT_2:
				CalButton2_down_dis(BUTT_X2,BUTT_Y1);
				break;		
		 case BUTT_3:
				CalButton3_down_dis(BUTT_X3,BUTT_Y1);
				break;	
		 case BUTT_PLUS:
				CalButtonAdd_down_dis(BUTT_X4,BUTT_Y1);
				break;	
		 case BUTT_4:
				CalButton4_down_dis(BUTT_X1,BUTT_Y2);
				break;		
		 case BUTT_5:
				CalButton5_down_dis(BUTT_X2,BUTT_Y2);
				break;		
		 case BUTT_6:
				CalButton6_down_dis(BUTT_X3,BUTT_Y2);
				break;		
		 case BUTT_SUB:
				CalButtonSub_down_dis(BUTT_X4,BUTT_Y2);
				break;		
		 case BUTT_7:
				CalButton7_down_dis(BUTT_X1,BUTT_Y3);
				break;		
		 case BUTT_8:
				CalButton8_down_dis(BUTT_X2,BUTT_Y3);
				break;		
		 case BUTT_9:
				CalButton9_down_dis(BUTT_X3,BUTT_Y3);
				break;	
		 case BUTT_MUL:
				CalButtonMul_down_dis(BUTT_X4,BUTT_Y3);
				break;
				
		 case BUTT_CLEAR:
				CalButtonClr_down_dis(BUTT_X1,BUTT_Y4);
				break;
		 case BUTT_0:
				CalButton0_down_dis(BUTT_X2,BUTT_Y4);
				break;	
		 case BUTT_DOT:
				CalButtonDot_down_dis(BUTT_X3,BUTT_Y4);
				break;		
		 case BUTT_DIV:
				CalButtonDiv_down_dis(BUTT_X4,BUTT_Y4);
				break;
		}
	}
else
	{
	switch(b_num)
		{
		case BUTT_EQU:
				CalButtonEqu_up_dis(BUTT_X1,BUTT_Y5);
				break;
		 case BUTT_ENTER:
				CalButtonOk_up_dis(BUTT_X3,BUTT_Y5);
				break;
		 case BUTT_1:
				CalButton1_up_dis(BUTT_X1,BUTT_Y1);
				break;		
		 case BUTT_2:
				CalButton2_up_dis(BUTT_X2,BUTT_Y1);
				break;		
		 case BUTT_3:
				CalButton3_up_dis(BUTT_X3,BUTT_Y1);
				break;	
		 case BUTT_PLUS:
				CalButtonAdd_up_dis(BUTT_X4,BUTT_Y1);
				break;	
		 case BUTT_4:
				CalButton4_up_dis(BUTT_X1,BUTT_Y2);
				break;		
		 case BUTT_5:
				CalButton5_up_dis(BUTT_X2,BUTT_Y2);
				break;		
		 case BUTT_6:
				CalButton6_up_dis(BUTT_X3,BUTT_Y2);
				break;		
		 case BUTT_SUB:
				CalButtonSub_up_dis(BUTT_X4,BUTT_Y2);
				break;		
		 case BUTT_7:
				CalButton7_up_dis(BUTT_X1,BUTT_Y3);
				break;		
		 case BUTT_8:
				CalButton8_up_dis(BUTT_X2,BUTT_Y3);
				break;		
		 case BUTT_9:
				CalButton9_up_dis(BUTT_X3,BUTT_Y3);
				break;	
		 case BUTT_MUL:
				CalButtonMul_up_dis(BUTT_X4,BUTT_Y3);
				break;
				
		 case BUTT_CLEAR:
				CalButtonClr_up_dis(BUTT_X1,BUTT_Y4);
				break;
		 case BUTT_0:
				CalButton0_up_dis(BUTT_X2,BUTT_Y4);
				break;	
		 case BUTT_DOT:
				CalButtonDot_up_dis(BUTT_X3,BUTT_Y4);
				break;		
		 case BUTT_DIV:
				CalButtonDiv_up_dis(BUTT_X4,BUTT_Y4);
				break;
		}
	}	


}

void CalcInputNums_dis(pInt8U nums)//计算公式  文本框
{
Int16U x,y,num_color=0;
Int8U i,break_flag=0;
Int8U Num[24];
i=0;
while((*nums!=0xff)&&(i<24))
	{
	if(*nums<'*')  //---数字  '*'==42(ascii)
		{
		Num[i++]=*nums+48;	
		nums++;
		}
	else		//---符号
		{
		if(*nums!='.')	//运算符
			{
			Num[i++]=*nums;	
			nums++;
			break_flag=1;
			break;	
			}
		else		//'.'小数点
			{
			Num[i++]=*nums;	
			nums++;	
			}
		}
	}
Num[i]=0;
x=CALCUL_TEXT_END-(16*i),y=CALCUL_TEXT_Y+2;//5;
// Printf32(Num,x,y,num_color,1,0xffff);	
ASCII_Printf(Num,64+1,16,32,ASCII_bold16x32,x,y,num_color,0xffff);	
//----------第二行算式-------------
if(break_flag==1)
	{
	i=0;
	while((*nums!=0xff)&&(i<24))
		{
		if(*nums<'*')  //---数字   '*'==42(ascii)
			{
			Num[i++]=*nums+48;	
			nums++;
			}
		else		//---符号
			{
			Num[i++]=*nums;	
			nums++;
			}
		}
	if(i>0)//有数字
		{
		Num[i]=0;
		x=CALCUL_TEXT_END-(16*i),y+=32;
		// Printf32(Num,x,y,num_color,1,0xffff);		
		ASCII_Printf(Num,64+1,16,32,ASCII_bold16x32,x,y,num_color,0xffff);		
		}
	}
}

void CalcResultNums_dis(pInt8U nums)//结果  文本框
{
Int16U x,y,num_color=0;
Int8U i;
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
x=CALCUL_TEXT_END-(16*i),y=CALCUL_RESULT_Y+2;//5;
// Printf32(Num,x,y,num_color,1,0xffff);	
ASCII_Printf(Num,64+1,16,32,ASCII_bold16x32, x,y,num_color,0xffff);
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
Int16U L_color=BLUE_COLOR,Fill_color=CALCUL_COLOR,wide,high;
// if(WorkMode==PROG_MODE)//编程画面下
	// {
	// wide=CALCUL_WIDE;
	// high=CALCUL_HIGH;
	// }
// else
	// {
	// wide=CALCUL_WIDE;
	// high=CALCUL_HIGH-70;
	// }
// CurrentArea_save3(CALCUL_WIN_X , CALCUL_WIN_Y,  CALCUL_WIDE, CALCUL_HIGH);
// GLCD_SetWindow_Fill(CALCUL_WIN_X,CALCUL_WIN_Y,CALCUL_WIN_X+wide-1,CALCUL_WIN_Y+high-1 ,L_color,Fill_color);

CalcWind_dis(CALCUL_WIN_X , CALCUL_WIN_Y );//计算器框

//按钮显示
while(n<=22)
	{
	// if(WorkMode==MANUAL_MODE)  // 手动模式
		// {
		// if(n==BUTT_ENTER)
			// n++;
		// }
	// else
		// {
		// if(n==BUTT_RUN)
			// n++;
		// }
	Button_dis(n++, 0); //触摸 按钮 显示
	}
// if(WorkMode==PROG_MODE)//编程画面下
	// {
	// n=BUTT_F1;
	// while(n<=BUTT_F5)
		// {
		// Button_dis(n++, 0); //触摸 按钮 显示	
		// }
	// }	
ClrCalcNums_text(CalcInput_Text,CAL_INPUT); //清计算器 输入框
ClrCalcNums_text(CalcResult_Text,CAL_RESULT); //清计算器 结果框 
CalcInputNums_dis(CalcInput_Text);  //输入框 显示
CalcResultNums_dis(CalcResult_Text);//结果框 显示
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
	case PORTUGAL:	//葡萄牙
	case SPANISH: //西班牙
		Printf24("Whether Paper-Pusher is in the end!",PUSH_RESET_PROMPT_X1+1,PUSH_RESET_PROMPT_Y1+5,BLACK_COLOR,1,0xffff);
		Printf24("OK",PUSH_RESET_OK_X,PUSH_RESET_OK_Y,BLACK_COLOR,1,0xffff);
		Printf24("Cancel",PUSH_RESET_CANCEL_X,PUSH_RESET_CANCEL_Y,BLACK_COLOR,1,0xffff);
		break;
	case INDONSIA:	//印尼	
		Printf24("Apakah mendorong kertas di final!",PUSH_RESET_PROMPT_X1+1,PUSH_RESET_PROMPT_Y1+5,BLACK_COLOR,1,0xffff);
		Printf24("Ya",PUSH_RESET_OK_X,PUSH_RESET_OK_Y,BLACK_COLOR,1,0xffff);
		Printf24("Membatal",PUSH_RESET_CANCEL_X,PUSH_RESET_CANCEL_Y,BLACK_COLOR,1,0xffff);
		break;
	}	
}

void ProgressBar_dis(Int16U total, Int16U now)  //进度条 显示
{
Int8U ratio;
Int16U line_x,y1,y2;
Int16U color;
if(now<=total)
	{
	ratio=now*100/total;
	line_x=SCHEDULE_DOT_X1+6;
	if(1)//(ratio!=ProcessRatio)
		{
		if(ProcessRatio!=0xff)    //不是 开始
			{
			color=TEXT_TAB_BACK_COLOR;			//color=0xf78a;
			y1=SCHEDULE_DOT_Y+ProcessRatio;
			y2=y1+18;
			GLCD_SetWindow_Fill(SCHEDULE_DOT_X1,y1, SCHEDULE_DOT_X2,y2 ,color,color);//清除 进度块
			// DrawLine( SCHEDULE_DOT_X+8, y1, SCHEDULE_DOT_X+15, y2, 0);
			GLCD_SetWindow_Fill(line_x,y1, line_x+2,y2 ,0,0);//
			}
		//**************
		ProcessRatio=ratio;
		color=0x3339;
		y1=SCHEDULE_DOT_Y+ProcessRatio;
		y2=y1+18;
		GLCD_SetWindow_Fill(SCHEDULE_DOT_X1,y1, SCHEDULE_DOT_X2,y2 ,color,color);//更新 进度块
		}
	}

}


void InputKEY_BUTT_dis(Int8U b_num,Int8U down_flag) //触摸 key 显示--------输入法
{
Int16U butt_color,num_color;
Int16U x,y,gap_x,gap_y,gap_x1,gap_y1;
gap_x=25,gap_x1=20,gap_y=8,gap_y1=24;
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
	case BUTT_1:	//
			x=TOUBUTT_X1;
			y=TOUBUTT_Y1;
			GLCD_SetWindow_Fill(x,y,x+TOUBUTT_WIDE,y+TOUBUTT_HIGH,butt_color,butt_color);
			y+=gap_y;
			Printf24("1",x+gap_x,y,num_color,0,0xffff);
			y+=gap_y1;
			Printf16(",",x+gap_x1,y,num_color,0,0xffff);
			break;		
	case BUTT_2:	//
			x=TOUBUTT_X2;
			y=TOUBUTT_Y1;
			GLCD_SetWindow_Fill(x,y,x+TOUBUTT_WIDE,y+TOUBUTT_HIGH,butt_color,butt_color);
			y+=gap_y;
			Printf24("2",x+gap_x,y,num_color,0,0xffff);
			y+=gap_y1;
			Printf16("abc",x+gap_x1,y,num_color,0,0xffff);
			break;		
	case BUTT_3:	//
			x=TOUBUTT_X3;
			y=TOUBUTT_Y1;
			GLCD_SetWindow_Fill(x,y,x+TOUBUTT_WIDE,y+TOUBUTT_HIGH,butt_color,butt_color);
			y+=gap_y;
			Printf24("3",x+gap_x,y,num_color,0,0xffff);
			y+=gap_y1;
			Printf16("def",x+gap_x1,y,num_color,0,0xffff);
			break;		
	case BUTT_UP:	//  up
			x=TOUBUTT_X4;
			y=TOUBUTT_Y1;
			GLCD_SetWindow_Fill(x,y,x+TOUBUTT_WIDE,y+TOUBUTT_HIGH,butt_color,butt_color);
			x+=gap_x;y+=30;
			GLCD_Triangle_Fill(x,y, x+10,y-15, x+20,y ,num_color,num_color);
			break;	
			//--------------------------------2  line
	case BUTT_4:	//
			x=TOUBUTT_X1;
			y=TOUBUTT_Y2;
			GLCD_SetWindow_Fill(x,y,x+TOUBUTT_WIDE,y+TOUBUTT_HIGH,butt_color,butt_color);
			y+=gap_y;
			Printf24("4",x+gap_x,y,num_color,0,0xffff);
			y+=gap_y1;
			Printf16("ghi",x+gap_x1,y,num_color,0,0xffff);
			break;		
	case BUTT_5:	//
			x=TOUBUTT_X2;
			y=TOUBUTT_Y2;
			GLCD_SetWindow_Fill(x,y,x+TOUBUTT_WIDE,y+TOUBUTT_HIGH,butt_color,butt_color);
			y+=gap_y;
			Printf24("5",x+gap_x,y,num_color,0,0xffff);
			y+=gap_y1;
			Printf16("jkl",x+gap_x1,y,num_color,0,0xffff);
			break;		
	case BUTT_6:	//
			x=TOUBUTT_X3;
			y=TOUBUTT_Y2;
			GLCD_SetWindow_Fill(x,y,x+TOUBUTT_WIDE,y+TOUBUTT_HIGH,butt_color,butt_color);
			y+=gap_y;
			Printf24("6",x+gap_x,y,num_color,0,0xffff);
			y+=gap_y1;
			Printf16("mno",x+gap_x1,y,num_color,0,0xffff);
			break;		
	case BUTT_DOWN:	//   down
			x=TOUBUTT_X4;
			y=TOUBUTT_Y2;
			GLCD_SetWindow_Fill(x,y,x+TOUBUTT_WIDE,y+TOUBUTT_HIGH,butt_color,butt_color);
			x+=gap_x;y+=30;
			GLCD_Triangle_Fill(x,y, x+10,y+15, x+20,y ,num_color,num_color);
			break;	
			//--------------------------------3  line
	case BUTT_7:	//
			x=TOUBUTT_X1;
			y=TOUBUTT_Y3;
			GLCD_SetWindow_Fill(x,y,x+TOUBUTT_WIDE,y+TOUBUTT_HIGH,butt_color,butt_color);
			y+=gap_y;
			Printf24("7",x+gap_x,y,num_color,0,0xffff);
			y+=gap_y1;
			Printf16("pqrs",x+gap_x1,y,num_color,0,0xffff);
			break;		
	case BUTT_8:	//
			x=TOUBUTT_X2;
			y=TOUBUTT_Y3;
			GLCD_SetWindow_Fill(x,y,x+TOUBUTT_WIDE,y+TOUBUTT_HIGH,butt_color,butt_color);
			y+=gap_y;
			Printf24("8",x+gap_x,y,num_color,0,0xffff);
			y+=gap_y1;
			Printf16("tuv",x+gap_x1,y,num_color,0,0xffff);
			break;		
	case BUTT_9:	//
			x=TOUBUTT_X3;
			y=TOUBUTT_Y3;
			GLCD_SetWindow_Fill(x,y,x+TOUBUTT_WIDE,y+TOUBUTT_HIGH,butt_color,butt_color);
			y+=gap_y;
			Printf24("9",x+gap_x,y,num_color,0,0xffff);
			y+=gap_y1;
			Printf16("wxyz",x+gap_x1,y,num_color,0,0xffff);
			break;		
	case BUTT_LEFT:	//  <--左
			x=TOUBUTT_X4;
			y=TOUBUTT_Y3;
			GLCD_SetWindow_Fill(x,y,x+TOUBUTT_WIDE,y+TOUBUTT_HIGH,butt_color,butt_color);
			x+=gap_x;y+=30;
			GLCD_Triangle_Fill(x,y, x+15,y-10, x+15,y+10 ,num_color,num_color);
			break;	
			//--------------------------------4  line
	case BUTT_CLEAR:	//clear
			x=TOUBUTT_X1;
			y=TOUBUTT_Y4;
			GLCD_SetWindow_Fill(x,y,x+TOUBUTT_WIDE,y+TOUBUTT_HIGH,butt_color,butt_color);
			x+=gap_x;y+=gap_y;
			Printf24("C",x,y,num_color,0,0xffff);
			break;		
	// case BUTT_SPAC:	//空格
	case BUTT_0:	//空格
			x=TOUBUTT_X2;
			y=TOUBUTT_Y4;
			GLCD_SetWindow_Fill(x,y,x+TOUBUTT_WIDE,y+TOUBUTT_HIGH,butt_color,butt_color);
			y+=gap_y;
			Printf24("0",x+gap_x,y,num_color,0,0xffff);
			x+=gap_x,y+=gap_y1;
			GLCD_SetWindow_Fill(x,y,x+20,y+8,  num_color,num_color);
			GLCD_SetWindow_Fill(x+3,y,x+20-3,y+8-3,  butt_color,butt_color);
			break;		
	case BUTT_ENTER:	//确定
			x=TOUBUTT_X3;
			y=TOUBUTT_Y4;
			GLCD_SetWindow_Fill(x,y,x+TOUBUTT_WIDE,y+TOUBUTT_HIGH,butt_color,butt_color);
			x+=15;y+=30;
			// Printf24("OK",x,y,num_color,0,0xffff);
			GLCD_Triangle_Fill(x,y, x+15,y-10, x+15,y+10 ,num_color,num_color);
			x+=15,y-=1;
			GLCD_SetWindow_Fill(x,y, x+20,y+3 ,num_color,num_color);
			x+=20;y+=3;
			GLCD_SetWindow_Fill(x,y, x+3,y-10 ,num_color,num_color);
			break;		
	case BUTT_RIGHT:	//  -->右
			x=TOUBUTT_X4;
			y=TOUBUTT_Y4;
			GLCD_SetWindow_Fill(x,y,x+TOUBUTT_WIDE,y+TOUBUTT_HIGH,butt_color,butt_color);
			x+=gap_x;y+=30;
			GLCD_Triangle_Fill(x,y-10, x,y+10, x+15,y ,num_color,num_color);
			break;	
	default:
			break;
	}
}



void StartHelpMenu_sel(Int8U sel, Int8U dis_flag)//开机系统  帮助界面
{
Int8U dis_buf[5]={0};
Int16U F_color,B_color,x,y,gap;
F_color=RED_COLOR;
B_color=WHITE_COLOR;
switch(Language)
	{
	case CHN_HAN:
		Printf24("触摸校准+",HELP_CORRECT_X,HELP_CORRECT_Y,F_color,1,B_color);
		Printf24("返回《",HELP_RET_X,HELP_RET_Y,F_color,1,B_color);
		break;
	case ENGLISH:
	case INDONSIA:	//印尼
	case PORTUGAL:	//葡萄牙
	case SPANISH: //西班牙
		Printf24("Touch calibrate+",HELP_CORRECT_X,HELP_CORRECT_Y,F_color,1,B_color);
		Printf24("Back《",HELP_RET_X,HELP_RET_Y,F_color,1,B_color);
		break;
	}	

if(dis_flag==1)
	{
	F_color=WHITE_COLOR;
	B_color=BLUE_COLOR;
	}
else
	{
	F_color=BLUE_COLOR;
	B_color=WHITE_COLOR;
	}
x=HELP_F1_X,y=HELP_F1_Y;gap=HELP_GAP_Y;
switch(sel)
	{
	case 1://F1  触摸校准
		switch(Language)
			{
			case CHN_HAN:
				Printf24("F1------触摸校准",x,y,F_color,1,B_color);
				break;
			case ENGLISH:
				Printf24("F1------Touch calibration",x,y,F_color,1,B_color);
				break;
			case INDONSIA:	//印尼
				Printf24("F1------sentuh Kalibrasi",x,y,F_color,1,B_color);
				break;
			case PORTUGAL:	//葡萄牙
				Printf24("F1------Toque em Calibra??o",x,y,F_color,1,B_color);
				ASCII_Printf("ca",ASCII24_MODE,12,24,PUTAO_ZK24, x+12*24,y,F_color,B_color);
				break;
			case SPANISH: //西班牙
				Printf24("F1------Calibració ",x,y,F_color,1,B_color);
				Printf24("                  n Pantalla tactil",x,y,F_color,0,B_color);
				break;
			}	
		break;
	case 2://F2		图标注释
		y+=gap;
		switch(Language)
			{
			case CHN_HAN:
				Printf24("F2------图标注释",x,y,F_color,1,B_color);
				break;
			case ENGLISH:
				Printf24("F2------Icon Comment",x,y,F_color,1,B_color);
				break;
			case INDONSIA:	//印尼
				Printf24("F2------gambar komentar",x,y,F_color,1,B_color);
				break;
			case PORTUGAL:	//葡萄牙
				Printf24("F2------í	             ",x,y,F_color,1,B_color);
				Printf24("         cone comentá",x,y,F_color,0,B_color);	//ícone comentário
				Printf24("                     rio",x,y,F_color,0,B_color);	//ícone comentário
				break;
			case SPANISH: //西班牙
				Printf24("F2------Picture Notes",x,y,F_color,1,B_color);
				break;
			}		
		break;
	case 3://	F3	端口测试---
		y+=gap*2;
		switch(Language)
			{
			case CHN_HAN:
				Printf24("F3------硬件测试",x,y,F_color,1,B_color);
				break;
			case ENGLISH:
				Printf24("F3------Board test",x,y,F_color,1,B_color);
				break;
			case INDONSIA:	//印尼
				Printf24("F3------uji Dewan",x,y,F_color,1,B_color);
				break;
			case PORTUGAL:	//葡萄牙
			case SPANISH: //西班牙
				Printf24("F3------port Test",x,y,F_color,1,B_color);
				break;
			}
		break;
	case 4://	F4	系统选择---
		y+=gap*3;
		switch(Language)
			{
			case CHN_HAN:
				Printf24("F4------系统选择(警告：非专业人员,禁止操作!)",x,y,F_color,1,B_color);
				break;
			case ENGLISH:
				Printf24("F4------System select(Warning:Non-professionals,",x,y,F_color,1,B_color);
				Printf24("prohibited actions)",x+150,y+30,F_color,1,B_color);
				break;
			case INDONSIA:	//印尼
				Printf24("F4----Seleksi sistem(Peringatan: non-profesional,",x,y,F_color,1,B_color);
				Printf24("dilarang tindakan)",x+150,y+30,F_color,1,B_color);
				break;
			case PORTUGAL:	//葡萄牙
				Printf24("F4----Selec??o do sistema(Aviso: n?o-profissionais",x,y,F_color,1,B_color);
				ASCII_Printf("ca",ASCII24_MODE,12,24,PUTAO_ZK24, x+12*11,y,F_color,B_color);
				ASCII_Printf("a",ASCII24_MODE,12,24,PUTAO_ZK24, x+12*34,y,F_color,B_color);
				Printf24(",para proibir a opera??o!)",x+150,y+30,F_color,1,B_color);
				ASCII_Printf("ca",ASCII24_MODE,12,24,PUTAO_ZK24, x+150+12*21,y+30,F_color,B_color);
				break;
			case SPANISH: //西班牙
				Printf24("F4----sistema Selecció ",x,y,F_color,1,B_color);
				Printf24("                      n(Aviso: Los no ",x,y,F_color,0,B_color);
				
				Printf24("profesionales, para prohibir la operació",x+50,y+30,F_color,1,B_color);
				Printf24("                                        n)",x+50,y+30,F_color,0,B_color);
				break;
			}
		break;
	case 5://	F5	每页列表行数---
		y+=gap*4;
		switch(Language)
			{
			case CHN_HAN:
				Printf24("F5------每页列表行数",x,y,F_color,1,B_color);
				break;
			case ENGLISH:
			case INDONSIA:	//印尼
			case PORTUGAL:	//葡萄牙
			case SPANISH: //西班牙
				Printf24("F5------Page sizes",x,y,F_color,1,B_color);
				break;
			}
		break;
	case 6://编码器 线数
		dis_buf[0]=PulseAB_Z_current/100+48;
		dis_buf[1]=(PulseAB_Z_current/10)%10+48;
		dis_buf[2]=PulseAB_Z_current%10+48;
		y+=gap*5;
		switch(Language)
			{
			case CHN_HAN:
				Printf24("编码器：       线",x,y,F_color,1,B_color);
				break;
			case ENGLISH:
			case INDONSIA:	//印尼
			case PORTUGAL:	//葡萄牙
			case SPANISH: //西班牙
				Printf24("Encoder:",x,y,F_color,1,B_color);
				break;
			}
		Printf24(dis_buf,x+120,y,F_color,1,B_color);
		break;
	}
}

void StartHelpMode_dis(void)
{
Int8U p;
GLCD_Buffer_Fill(WHITE_COLOR);//
for(p=1;p<6;p++)
	StartHelpMenu_sel(p,0);
}

void Num_Keyboard_Tou_dis(Int8U b_num,Int8U down_flag) //触摸 key 显示
{
Int16U butt_color,num_color;
Int16U x,y,gap_word_x,gap_word_y;
if(down_flag==1)  //按下后
	{
	butt_color=GREEN_COLOR;
	num_color=RED_COLOR;
	}
else
	{
	butt_color=0x9fff;
	num_color=0;
	}gap_word_x=30,gap_word_y=20;
switch(b_num)
	{
	case BUTT_1:
			x=KEY_BUT_X1;
			y=KEY_BUT_Y1;
			GLCD_SetWindow_Fill(x,y,x+KEY_BUT_WIDE,y+KEY_BUT_HIGH,butt_color,butt_color);
			x+=gap_word_x;y+=gap_word_y;
			Printf24("1",x,y,num_color,0,0xffff);
			break;	
	case BUTT_2:
			x=KEY_BUT_X2;
			y=KEY_BUT_Y1;
			GLCD_SetWindow_Fill(x,y,x+KEY_BUT_WIDE,y+KEY_BUT_HIGH,butt_color,butt_color);
			x+=gap_word_x;y+=gap_word_y;
			Printf24("2",x,y,num_color,0,0xffff);
			break;		
	case BUTT_3:
			x=KEY_BUT_X3;
			y=KEY_BUT_Y1;
			GLCD_SetWindow_Fill(x,y,x+KEY_BUT_WIDE,y+KEY_BUT_HIGH,butt_color,butt_color);
			x+=gap_word_x;y+=gap_word_y;
			Printf24("3",x,y,num_color,0,0xffff);
			break;		
//--------			
	case BUTT_4:
			x=KEY_BUT_X1;
			y=KEY_BUT_Y2;
			GLCD_SetWindow_Fill(x,y,x+KEY_BUT_WIDE,y+KEY_BUT_HIGH,butt_color,butt_color);
			x+=gap_word_x;y+=gap_word_y;
			Printf24("4",x,y,num_color,0,0xffff);
			break;	
	case BUTT_5:
			x=KEY_BUT_X2;
			y=KEY_BUT_Y2;
			GLCD_SetWindow_Fill(x,y,x+KEY_BUT_WIDE,y+KEY_BUT_HIGH,butt_color,butt_color);
			x+=gap_word_x;y+=gap_word_y;
			Printf24("5",x,y,num_color,0,0xffff);
			break;		
	case BUTT_6:
			x=KEY_BUT_X3;
			y=KEY_BUT_Y2;
			GLCD_SetWindow_Fill(x,y,x+KEY_BUT_WIDE,y+KEY_BUT_HIGH,butt_color,butt_color);
			x+=gap_word_x;y+=gap_word_y;
			Printf24("6",x,y,num_color,0,0xffff);
			break;				
//--------			
	case BUTT_7:
			x=KEY_BUT_X1;
			y=KEY_BUT_Y3;
			GLCD_SetWindow_Fill(x,y,x+KEY_BUT_WIDE,y+KEY_BUT_HIGH,butt_color,butt_color);
			x+=gap_word_x;y+=gap_word_y;
			Printf24("7",x,y,num_color,0,0xffff);
			break;	
	case BUTT_8:
			x=KEY_BUT_X2;
			y=KEY_BUT_Y3;
			GLCD_SetWindow_Fill(x,y,x+KEY_BUT_WIDE,y+KEY_BUT_HIGH,butt_color,butt_color);
			x+=gap_word_x;y+=gap_word_y;
			Printf24("8",x,y,num_color,0,0xffff);
			break;		
	case BUTT_9:
			x=KEY_BUT_X3;
			y=KEY_BUT_Y3;
			GLCD_SetWindow_Fill(x,y,x+KEY_BUT_WIDE,y+KEY_BUT_HIGH,butt_color,butt_color);
			x+=gap_word_x;y+=gap_word_y;
			Printf24("9",x,y,num_color,0,0xffff);
			break;						
//--------			
	case BUTT_CLEAR:
			x=KEY_BUT_X1;
			y=KEY_BUT_Y4;
			GLCD_SetWindow_Fill(x,y,x+KEY_BUT_WIDE,y+KEY_BUT_HIGH,butt_color,butt_color);
			x+=gap_word_x;y+=gap_word_y;
			Printf24("C",x,y,num_color,0,0xffff);
			break;	
	case BUTT_0:
			x=KEY_BUT_X2;
			y=KEY_BUT_Y4;
			GLCD_SetWindow_Fill(x,y,x+KEY_BUT_WIDE,y+KEY_BUT_HIGH,butt_color,butt_color);
			x+=gap_word_x;y+=gap_word_y;
			Printf24("0",x,y,num_color,0,0xffff);
			break;		
	case BUTT_ENTER:
			x=KEY_BUT_X3;
			y=KEY_BUT_Y4;
			GLCD_SetWindow_Fill(x,y,x+KEY_BUT_WIDE,y+KEY_BUT_HIGH,butt_color,butt_color);
			x+=gap_word_x;y+=gap_word_y;
			Printf24("OK",x,y,num_color,0,0xffff);
			break;			
	}
}

void SysBoardSelect_dis(void)  //系统版本 进入
{
Int16U x,y;
Int8U n=0;
x=SYSBD_HINT_X,y=SYSBD_HINT_Y;
GLCD_Buffer_Fill(0xffff);
switch(Language)
	{
	case CHN_HAN:
		Printf24("请输入密码：",x,y,BLACK_COLOR,0,0xffff);
			break;
	case ENGLISH:	
		Printf24("Enter password,please:",x,y,BLACK_COLOR,0,0xffff);
			break;
	case INDONSIA:	//印尼
		Printf24("Masukkan sandi Anda:",x,y,BLACK_COLOR,0,0xffff);
			break;
	case PORTUGAL:	//葡萄牙
		Printf24("Por favor, digite uma senha:",x,y,BLACK_COLOR,0,0xffff);
			break;
	case SPANISH: //西班牙
		Printf24("Introduzca la contrase?a",x,y,BLACK_COLOR,0,0xffff);
		ASCII_Printf("n",ASCII24_MODE,12,24,PUTAO_ZK24,x+12*22,y,BLACK_COLOR,0xffff);
			break;
	}
GLCD_SetWindow_Fill(SYSBD_WORD_X, SYSBD_WORD_Y, SYSBD_WORD_X+120, SYSBD_WORD_Y+30, RED_COLOR, 0xffff);	
switch(Language)
	{
	case CHN_HAN:
		Printf24("返回《",HELP_RET_X,HELP_RET_Y,RED_COLOR,1,0xffff);
			break;
	case ENGLISH:	
	case INDONSIA:	//印尼
	case PORTUGAL:	//葡萄牙
	case SPANISH: //西班牙
		Printf24("Back《",HELP_RET_X,HELP_RET_Y,RED_COLOR,1,0xffff);
			break;
	}
while(n<22)
	{
	Num_Keyboard_Tou_dis( n++, 0); //触摸 key 显示
	}
}	

void SysBoardNum_dis(pInt8U p_num,Int8U cou)
{
Int8U passnums[8],n=0;
for(n=0;n<cou;n++)
	{
	if(*p_num!='.')
		{
		passnums[n]=*p_num+48;
		}
	p_num++;
	}
passnums[n]=0;
Printf24(passnums,SYSBD_WORD_X+10,SYSBD_WORD_Y+5,BLACK_COLOR,1,0xffff);
}

void ClrSysBoardNum_dis(void)
{
if(num_cou>0)
	{
	for(num_cou=0;num_cou<8;num_cou++)
		 {
		 Size_temp[num_cou++]=0;
		 }
	num_cou=0; //
	GLCD_SetWindow_Fill(SYSBD_WORD_X, SYSBD_WORD_Y, SYSBD_WORD_X+120, SYSBD_WORD_Y+30, RED_COLOR, 0xffff);	
	}
}

void EnterSysBoardNum(void)
{
Int32U code_temp=0,n;
if(Board_TestMod==TEST_SYS_WORD)
	{
	if(num_cou>0)
		{
		for(n=0;n<num_cou;n++)
			{
			code_temp=code_temp*10+Size_temp[n];
			}
		if(code_temp==SYSBD_PASSWORD)	 //密码  正确，则进入系统版本选择
			{
			Board_TestMod=TEST_SYS_TYPE;
			GLCD_Buffer_Fill(0xffff);
			SpeedLevelSel_dis(0,0);    //电机驱动类型 显示
			SpeedLevelSel_dis(1,0);    //电机驱动类型 显示
			SpeedLevelSel_dis(2,0);    //电机驱动类型 显示
			SpeedLevelSel_dis(3,0);    //电机驱动类型 显示
			SpeedLevelSel_dis(4,0);    //电机驱动类型 显示
			SpeedLevelSel_dis(5,0);    //电机驱动类型 显示
			SpeedLevelSel_dis(6,0);    //电机驱动类型 显示
			SpeedLevelSel_dis(MotorType,1);
			UpArrow_Up_dis( VER_SEL_UP_X,  VER_SEL_UP_Y);//上箭头up
			DownArrow_Up_dis( VER_SEL_DOWN_X,  VER_SEL_DOWN_Y);//下箭头up
			}
		else   //error
			{
			GLCD_SetWindow_Fill(SYSBD_WORD_X, SYSBD_WORD_Y, SYSBD_WORD_X+120, SYSBD_WORD_Y+30, RED_COLOR, 0xffff);	
			}
		for(num_cou=0;num_cou<8;num_cou++)
			 {
			 Size_temp[num_cou++]=0;
			 }
		num_cou=0; //	
		}

	}
}

void KnifeSensorInMachine_dis(Int8U down_flag)//刀 传感器位置 示意
{
Int16U x,y,color;
Int8U r=3;
x=KNIFE_SENSOR_X,y=KNIFE_SENSOR_Y;
// if(ButtonTouch_mode==0)
	// {
	if(WorkMode==MANUAL_MODE)// 手动 模式
		{
		if(down_flag==0)//上
			{
			if(KnifeSensorMode!=1)
				{
				KnifeSensorMode=1;
				color=TEXT_TAB_BACK_COLOR;
				GLCD_Circle_Fill( x, y, r, color, color);
				}
			}
		else		//下
			{
			if(KnifeSensorMode!=2)
				{
				KnifeSensorMode=2;
				color=RED_COLOR;
				GLCD_Circle_Fill( x, y, r, color, color);
				}
			}
		}
	// }	
}
void PressSensorInMachine_dis(Int8U down_flag)//压纸 传感器位置 示意
{
Int16U x,y,color;
Int8U r=3;
x=PRESS_SENSOR_X,y=PRESS_SENSOR_Y;
// if(ButtonTouch_mode==0)
	// {
	if(WorkMode==MANUAL_MODE)// 手动 模式
		{
		if(down_flag==0)//上
			{
			if(PressSensorMode!=1)
				{
				PressSensorMode=1;
				color=TEXT_TAB_BACK_COLOR;
				GLCD_Circle_Fill( x, y, r, color, color);
				}
			}
		else		//下
			{
			if(PressSensorMode!=2)
				{
				PressSensorMode=2;
				color=RED_COLOR;
				GLCD_Circle_Fill( x, y, r, color, color);
				}
			}
		}
	// }
}


void PageLine_Set(Int8U line_set,Int8U set_flag)	//每页行数显示
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
x=200,y=200;gap=40;
switch(line_set)
	{
	case PAGE_5_LINE: //5 line 
			switch(Language)
				{
				case CHN_HAN:
					Printf24("每页显示5行",x,y,F_color,1,B_color);
						break;
				case ENGLISH:	
				case INDONSIA:	//印尼
				case PORTUGAL:	//葡萄牙
				case SPANISH: //西班牙
					Printf24("5 lines a page",x,y,F_color,1,B_color);
						break;
				}
			break;
	case PAGE_7_LINE: //7 line  
			y+=gap;
			switch(Language)
				{
				case CHN_HAN:
					Printf24("每页显示7行",x,y,F_color,1,B_color);
						break;
				case ENGLISH:	
				case INDONSIA:	//印尼
				case PORTUGAL:	//葡萄牙
				case SPANISH: //西班牙
					Printf24("7 lines a page",x,y,F_color,1,B_color);
						break;
				}
			break;
	}
}
void PageLineSet_dis(void)	//每页行数 设置  -------界面
{
Int16U x,y;
GLCD_Buffer_Fill(0xffff);
switch(Language)
	{
	case CHN_HAN:
		Printf24("返回《",HELP_RET_X,HELP_RET_Y,RED_COLOR,1,0xffff);
			break;
	case ENGLISH:	
	case INDONSIA:	//印尼
	case PORTUGAL:	//葡萄牙
	case SPANISH: //西班牙
		Printf24("Back《",HELP_RET_X,HELP_RET_Y,RED_COLOR,1,0xffff);
			break;
	}
PageLine_Set(PAGE_5_LINE, 0);	//每页行数显示
PageLine_Set(PAGE_7_LINE, 0);	//每页行数显示

PageLine_Set(PageKf_Size_flag, 1);	// 
UpArrow_Up_dis( LINE_SET_UP_X,  LINE_SET_UP_Y);//上箭头up
DownArrow_Up_dis( LINE_SET_DOWN_X,  LINE_SET_DOWN_Y);//下箭头up
}

//-----------测试端口模式
void F6_TestIO_dis(void)
{
CurrentArea_save2(MIDDLE_PAGE_X , MIDDLE_PAGE_Y,  M_PAGE_WIDE, M_PAGE_HIGH);
MiddlePage_dis();//中间活页
IO_InputDisInit();
KeyDis_Init();//按键显示初始化
}


//-------------当前所有标记clr初始化
Int8U ClrAllFlagsInit(KNIFE_DATA* pknife_data )
{
Int8U change_flag=0;
if((pknife_data->size >= Size_MIN_num)&&(pknife_data->size <= Size_MAX_num))//数据有效
	{
		//-----标记未初始化
	if((pknife_data->k_flag&0xf)==0)//--几个标记未定
		{
		pknife_data->k_flag|= FLAG_FLAG;//标记待设定
		change_flag=1;
		}
	if((pknife_data->k_flag&0xf0)==0)//气垫未设定
		{
		pknife_data->k_flag|= NOAIR_FLAG;//无气垫
		change_flag=1;
		}	
	}
else	//0000==无数据
	{
	if(pknife_data->k_flag!=0)
		{
		pknife_data->k_flag=0;
		change_flag=1;	
		}
	}
return change_flag;
}

void LongTouchZoneDis(Int16U x, Int16U y, Int16U w,Int16U h, Int8U jog_flag)
{
	CurrentArea_save4(x,y, w,h);
	if(jog_flag == 0)
		Printf24("Long",x,y,0xffff,1,RED_COLOR);
	else
		Printf24("Jog",x,y,0,1,BLUE_COLOR);
	// GLCD_SetWindow_Fill(x,y,x+w-1,y+h-1,0,0);
}


//-----------------20191115
void SearchProgPagePassWord_dis(void) //F3--程序选择
{
//------
SetModeEnbByCode_flag=0;
MiddlePage_dis();//中间活页
//主模式......
// DisAllProgMode=PRO_BY_NUM;
MainModeIcon_dis(WorkMode);//程序选择模式
GLCD_SetWindow_Fill(REMIND_WINDOW_X, REMIND_WINDOW_Y, REMIND_WINDOW_X+REMIND_LENGTH, REMIND_WINDOW_Y+30, 0xfffff, 0xffff);//提示框
switch(Language)
	{
	case CHN_HAN:
		Printf24("请输入密码!",REMIND_WINDOW_X,REMIND_WINDOW_Y+5,RED_COLOR,0,0xffff);
			break;
	case ENGLISH:	
		Printf24("Enter passcode!",REMIND_WINDOW_X,REMIND_WINDOW_Y+5,RED_COLOR,0,0xffff);
			break;
	case INDONSIA:	//印尼
		Printf24("Masukkan sandi Anda",REMIND_WINDOW_X,REMIND_WINDOW_Y+5,RED_COLOR,0,0xffff);
			break;
	case PORTUGAL:	//葡萄牙
		Printf24("Por favor, digite uma senha",REMIND_WINDOW_X,REMIND_WINDOW_Y+5,RED_COLOR,0,0xffff);
			break;
	case SPANISH: //西班牙
		Printf24("Introduzca la contrase?a",REMIND_WINDOW_X,REMIND_WINDOW_Y+5,RED_COLOR,0,0xffff);
		ASCII_Printf("n",ASCII24_MODE,12,24,PUTAO_ZK24,REMIND_WINDOW_X+12*22,REMIND_WINDOW_Y+5,RED_COLOR,0xffff);
			break;
	}
Printf32("请输入6位密码!",150,250,RED_COLOR,0,0xffff);	
}
