

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
Int16U MAIX_Knife;//最多刀数

//Int16U Process_num;//当前程序 号
//Int16U MaixProcess_num;//最大 程序号

PROG_SEG Pro_data;//程序 段 号

PROCESS_HEAD OnePro_head;//
PROCESS_HEAD Pro_head_temp;//


Int16U ProNumGroup[MAIX_PROG+2];
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
Int8U InputMode;

Int8U LabelTime_flag;//label次数
Int32U LabelTime;//label次数
unsigned int Total_size=0;//总长
unsigned int Label_size=0;//标签长
unsigned int Waste_size=0;//废边
unsigned int Divide_num=0;//等分数
Int8U DisAllProgMode;


//*****************读取文件
void ReadFiles(void)
{
//FileFolderRead("开机画面.bmp",(unsigned char*)START_PIC_sdram);//读开机画面
FileFolderRead("Power.bmp",(unsigned char*)START_PIC_sdram);//读开机画面

//GLCD_SetWindow_Fill(30,450,600,479,BLACK_COLOR,BLACK_COLOR);//*******************************

FileFolderRead("背景.bmp",(unsigned char*)WOEK_BACK_dis);//读背景
GLCD_SetWindow_Fill(0,0,799,479,BLACK_COLOR,BLACK_COLOR);//*******************************


FileFolderRead("标签功能.bmp",(unsigned char*)LABEL_FUN_sdram);//
// FileFolderRead("程序.bmp",(unsigned char*)PROCESS_sdram);//
FileFolderRead("参数功能.bmp",(unsigned char*)TOOLS_sdram);//
FileFolderRead("等分功能.bmp",(unsigned char*)DIVIDE_FUN_sdram);//
FileFolderRead("基准功能.bmp",(unsigned char*)RULER_FUN_sdram);//
FileFolderRead("日历功能.bmp",(unsigned char*)CALENDAR_sdram);//
FileFolderRead("密码功能.bmp",(unsigned char*)LOCK_KEY_sdram);//

FileFolderRead("F1标签up.bmp",(unsigned char*)F1_LABELS_UP_sdram);//
FileFolderRead("F2等分up.bmp",(unsigned char*)F2_DIVIDE_UP_sdram);//
FileFolderRead("F3程序up.bmp",(unsigned char*)F3_SELECT_PRO_UP_sdram);//
FileFolderRead("F1查看.bmp",(unsigned char*)F1_LOOK_UP_sdram);
FileFolderRead("F2时间排序up.bmp",(unsigned char*)F2_BY_TIME_UP_sdram);
FileFolderRead("F2时间排序down.bmp",(unsigned char*)F2_BY_TIME_DOWN_sdram);
FileFolderRead("F3号码排序up.bmp",(unsigned char*)F3_BY_NUM_UP_sdram);
FileFolderRead("F3号码排序down.bmp",(unsigned char*)F3_BY_NUM_DOWN_sdram);
FileFolderRead("F4删除一个程序up.bmp",(unsigned char*)F4_DELETE_ONE_PRO_UP_sdram);
FileFolderRead("F5删除所有程序up.bmp",(unsigned char*)F5_DELETE_ALL_PRO_UP_sdram);
FileFolderRead("F1中文输入up.bmp",(unsigned char*)F1_PINYIN_UP_sdram);
FileFolderRead("F1中文输入down.bmp",(unsigned char*)F1_PINYIN_DOWN_sdram);
FileFolderRead("F2字母输入up.bmp",(unsigned char*)F2_CHAR_UP_sdram);
FileFolderRead("F2字母输入down.bmp",(unsigned char*)F2_CHAR_DOWN_sdram);
FileFolderRead("F3数字输入up.bmp",(unsigned char*)F3_NUM_UP_sdram);
FileFolderRead("F3数字输入down.bmp",(unsigned char*)F3_NUM_DOWN_sdram);
FileFolderRead("F4退出.bmp",(unsigned char*)F4_EXIT_UP_sdram);
FileFolderRead("F6退出.bmp",(unsigned char*)F6_EXIT_BUTT_sdram);//

FileFolderRead("F4推纸up.bmp",(unsigned char*)F4_PUSH_UP_sdram);//
FileFolderRead("F2退出up.bmp",(unsigned char*)F2_OUT_UP_sdram);//
FileFolderRead("F1基准up.bmp",(unsigned char*)F1_RULER_UP_sdram);//
FileFolderRead("F2参数up.bmp",(unsigned char*)F2_TOOLS_UP_sdram);//
FileFolderRead("F1完成up.bmp",(unsigned char*)F1_FINISHED_sdram);//
//FileFolderRead("示教模式.bmp",(unsigned char*)TEACH_MOD_sdram);//
//FileFolderRead("自刀模式.bmp",(unsigned char*)AUTO_KNIFE_MOD_sdram);//
FileFolderRead("刀上.bmp",(unsigned char*)KNIFE_UP_sdram);//
FileFolderRead("刀下.bmp",(unsigned char*)KNIFE_DOWN_sdram);//
FileFolderRead("压上.bmp",(unsigned char*)PRESS_UP_sdram);//
FileFolderRead("压下.bmp",(unsigned char*)PRESS_DOWN_sdram);//
// FileFolderRead("红色A.bmp",(unsigned char*)RED_A_sdram);//
// FileFolderRead("红色B.bmp",(unsigned char*)RED_B_sdram);//
// FileFolderRead("黑色A.bmp",(unsigned char*)BLACK_A_sdram);//
// FileFolderRead("黑色B.bmp",(unsigned char*)BLACK_B_sdram);//
FileFolderRead("红线.bmp",(unsigned char*)RED_LINE_sdram);//
FileFolderRead("手红外.bmp",(unsigned char*)HAND_IR_sdram);//
// FileFolderRead("刀前.bmp",(unsigned char*)FRONT_KNIFE_sdram);//
FileFolderRead("红刀图标.bmp",(unsigned char*)RED_KNIFE_F_sdram);//
FileFolderRead("推纸图标.bmp",(unsigned char*)PUSH_PAPER_F_sdram);//
FileFolderRead("压纸循环标记.bmp",(unsigned char*)PRE_AUTO_F_sdram);//
FileFolderRead("滚动条.bmp",(unsigned char*)SCHEDULE_sdram);//
FileFolderRead("arrow.bmp",(unsigned char*)CURSOR_sdram);//
// FileFolderRead("时间条.bmp",(unsigned char*)TIME_COL_sdram);//
// FileFolderRead("推纸器.bmp",(unsigned char*)PUSH_PAPER_TOOL_sdram);//
//FileFolderRead("取消up.bmp",(unsigned char*)CANCEL_UP_sdram);//
//FileFolderRead("取消down.bmp",(unsigned char*)CANCEL_DOWN_sdram);//
//FileFolderRead("确定up.bmp",(unsigned char*)ENTER_UP_sdram);//
//FileFolderRead("确定down.bmp",(unsigned char*)ENTER_DOWN_sdram);//
FileFolderRead("停止up.bmp",(unsigned char*)STOP_UP_sdram);//
//FileFolderRead("停止down.bmp",(unsigned char*)STOP_DOWN_sdram);//
FileFolderRead("运行up.bmp",(unsigned char*)RUN_UP_sdram);//
//FileFolderRead("运行down.bmp",(unsigned char*)RUN_DOWN_sdram);//
// FileFolderRead("输入尺寸.bmp",(unsigned char*)INPUT_SIZE_sdram);//
// FileFolderRead("提示栏.bmp",(unsigned char*)REMIND_sdram);//
// FileFolderRead("推纸_刀.bmp",(unsigned char*)PUSH_KNIFE_sdram);//
// FileFolderRead("位置.bmp",(unsigned char*)POSITION_sdram);//
// FileFolderRead("序号.bmp",(unsigned char*)ORDER_sdram);//
// FileFolderRead("中间活页.bmp",(unsigned char*)MIDDLE_PAGE_sdram);//
// FileFolderRead("左边活页.bmp",(unsigned char*)LEFT_PAGE_sdram);//
FileFolderRead("删除up.bmp",(unsigned char*)DELETE_UP_sdram);//
FileFolderRead("全删up.bmp",(unsigned char*)DELETE_ALL_UP_sdram);//
// FileFolderRead("鸭梨.bmp",(unsigned char*)PEAR_sdram);//
FileFolderRead("FF键up.bmp",(unsigned char*)F_KEY_UP_sdram);//
FileFolderRead("前进up.bmp",(unsigned char*)FRONT_PAGE_UP_sdram);//
FileFolderRead("后退up.bmp",(unsigned char*)BACK_PAGE_UP_sdram);//
FileFolderRead("上箭头up.bmp",(unsigned char*)UP_ARROW_UP_sdram);//
FileFolderRead("下箭头up.bmp",(unsigned char*)DOWN_ARROW_UP_sdram);//
FileFolderRead("F3++up.bmp",(unsigned char*)F3_PLUS_UP_sdram);//
FileFolderRead("F3时钟up.bmp",(unsigned char*)F3_CLOCK_UP_sdram);//
FileFolderRead("F4--up.bmp",(unsigned char*)F4_MINUS_UP_sdram);//
FileFolderRead("F5刀up.bmp",(unsigned char*)F5_CUT_UP_sdram);//
FileFolderRead("F0全刀up.bmp",(unsigned char*)F0_ALLCUT_UP_sdram);//
// FileFolderRead("脉冲当量.bmp",(unsigned char*)PULSE_DEGREE_sdram);//
// FileFolderRead("锁.bmp",(unsigned char*)LOCK_sdram);//
FileFolderRead("左右箭头up.bmp",(unsigned char*)L_R_ARROW_sdram);//
FileFolderRead("F5压纸循环up.bmp",(unsigned char*)F5_PRE_FLG_BUTT_UP_sdram);//

// FileFolderRead("wheel0.bmp",(unsigned char*)WHEEL0_sdram);//
// FileFolderRead("wheel1.bmp",(unsigned char*)WHEEL1_sdram);//
FileFolderRead("F4wheel0.bmp",(unsigned char*)F4_WHEEL0_sdram);//
FileFolderRead("F4wheel1.bmp",(unsigned char*)F4_WHEEL1_sdram);//
// // FileFolderRead("F5_YES.bmp",(unsigned char*)F5_YESCUT_sdram);//
// // FileFolderRead("F5_NO.bmp",(unsigned char*)F5_NOCUT_sdram);//
// // FileFolderRead("F0ALL_YES.bmp",(unsigned char*)F0_YESALLCUT_sdram);//
// // FileFolderRead("F0ALL_NO.bmp",(unsigned char*)F0_NOALLCUT_sdram);//
FileFolderRead("F4脉冲当量up.bmp",(unsigned char*)F4_PULSE_UP_sdram);

FileFolderRead("F3标签次数up.bmp",(unsigned char*)LABEL_TIME_F3_UP_sdram);//
FileFolderRead("F3标签次数down.bmp",(unsigned char*)LABEL_TIME_F3_DOWN_sdram);//
FileFolderRead("F4标签废边up.bmp",(unsigned char*)LABEL_DESERT_F4_UP_sdram);//
FileFolderRead("F4标签废边down.bmp",(unsigned char*)LABEL_DESERT_F4_DOWN_sdram);//
FileFolderRead("快进up.bmp",(unsigned char*)FAST_FORWD_UP_sdram);
FileFolderRead("快退up.bmp",(unsigned char*)FAST_BACK_UP_sdram);
FileFolderRead("运行BIGup.bmp",(unsigned char*)RUN_BIG_BUTT_UP_sdram);
FileFolderRead("停止BIGup.bmp",(unsigned char*)STOP_BIG_BUTT_UP_sdram);
// FileFolderRead("上箭头LITTup.bmp",(unsigned char*)UP_ARROW_PRO_sdram);
// FileFolderRead("下箭头LITTup.bmp",(unsigned char*)DOWN_ARROW_PRO_sdram);
FileFolderRead("确定up.bmp",(unsigned char*)ENTER_BUTT_sdram);	//ok
}

void StartPic_dis(void)//开机画面显示
{
	volatile Int32U i;
	/*
pInt32U source_Ptr=(pInt32U)malloc(1024);
for(i=0;i<256;i++)	//1k
	{
	source_Ptr[i]=0xffffffff;
	}
for(i=0;i<24*1024;i++)//24k
	{
	pInt32U dest_Ptr=(pInt32U)(df_zk_sdram+i*1024);//           0xa0600000  //字库2M
	memcpy(dest_Ptr,source_Ptr,1024);
	}
	*/
//free(source_Ptr);

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
	case PORTUGAL:	//葡萄牙
		Printf24("computador de autoteste,carregamento....",40,430,RED_COLOR,1,0xffff);
		Printf24("Por favor, aguarde seis segundo!",40,550,RED_COLOR,1,0xffff);
			break;	
	case FRENCH:	//法语
		Printf24("CONTROLE AUTO EN COURS, CHARGEMENT DONNEES,",40,430,RED_COLOR,1,0xffff);
		Printf24("ATTENDRE 6 SECONDES !",40,550,RED_COLOR,1,0xffff);
			break;	
	}

//FileFolderRead("开机画面.bmp",(unsigned char*)START_PIC_sdram);//读开机画面
Pear_dis(PEAR_X, PEAR_Y);//鸭梨
ReadFiles();  //读取 图标文件
Bmp_Decode((Int32U)START_PIC_sdram, 0, 0, (pInt16U)SDRAM0_BASE_ADDR); //显示开机画面

RLOUT1_OFF;    // 允许裁切

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
back_color=MODE_NAME_COLOR,	line_color=WHITE_COLOR;  //模式解释 框
GLCD_SetWindow_Fill(MODE_NAME_X1,MODE_NAME_Y1,MODE_NAME_X2,MODE_NAME_Y2,back_color,back_color);
x=MODE_NAME_X1+10;y=MODE_NAME_Y1+4;
switch(mode)
	{
	case PROG_MODE:
		switch(Language)
			{
			case CHN_HAN:
				x+=12*5;
				Printf24("编程模式",x,y,line_color,1,back_color);
					break;
			case ENGLISH:
				x+=12*5;
				Printf24("Edit mode",x,y,line_color,1,back_color);
					break;
			case INDONSIA:	//印尼
				Printf24("Mode pemrograman",x,y,line_color,1,back_color);
					break;
			case PORTUGAL:	//葡萄牙
				Printf24("modo de edi??o",x,y,line_color,1,back_color);
				ASCII_Printf("ca",ASCII24_MODE,12,24,PUTAO_ZK24, x+(11*12),y,line_color,back_color);
					break;	
			case FRENCH:	//法语
				Printf24("MODE PROGRAMMATION",x,y,line_color,1,back_color);
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
			case FRENCH:	//法语
				x+=12*5;
				Printf24("MODE AUTO",x,y,line_color,1,back_color);
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
			case FRENCH:	//法语
				x+=12*3;	
				Printf24("MODE MANUEL",x,y,line_color,1,back_color);
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
			case FRENCH:	//法语
				x+=12*5;
				Printf24("MODE DEMO",x,y,line_color,1,back_color);
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
			case FRENCH:	//法语
				Printf24("MODE COUPE AUTO",x,y,line_color,1,back_color);
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
			case FRENCH:	//法语
				x+=12*5;	
				Printf24("MODE AIDE",x,y,line_color,1,back_color);
					break;
			}	
			break;
	//--------------------------------------------------------------------		
	case PROG_LABEL_MODE:
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
			case FRENCH:	//法语	
				Printf24("MODE ETIQUETTE",x,y,line_color,1,back_color);
					break;
			}	
			break;
	case PROG_DIVIDE_MODE:
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
			case FRENCH:	//法语	
				x+=12*2;	
				Printf24("MODE ALIQUOTE",x,y,line_color,1,back_color);
					break;
			}	
			break;
	case PROG_PRO_MODE:
	case TEACH_PRO_MODE:
		switch(Language)
			{
			case CHN_HAN:
				x+=12*5;
				Printf24("程序模式",x,y,line_color,1,back_color);
					break;
			case ENGLISH:
				x+=12*3;	
				Printf24("Procedure mode",x,y,line_color,1,back_color);
					break;
			case INDONSIA:	//印尼	
				x+=12*3;	
				Printf24("Mode Program",x,y,line_color,1,back_color);
					break;
			case PORTUGAL:	//葡萄牙
				// x+=12*2;		
				Printf24("Modo de Programa",x,y,line_color,1,back_color);
					break;
			case FRENCH:	//法语	
				x+=12*3;	
				Printf24("MODE PROGRAMME",x,y,line_color,1,back_color);
					break;
			}	
			break;
	case PROG_PRO_MESS_MODE:
	case TEACH_PRO_MESS_MODE:
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
			case FRENCH:	//法语	
				Printf24("MODE NOM PROGRAMME",x,y,line_color,1,back_color);
					break;
			}	
			break;
	case PROG_FLAG_MODE:
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
			case FRENCH:	//法语	
				Printf24("MODE CONFIG MARQUAGE",x,y,line_color,1,back_color);
					break;
			}	
			break;
	case AUTO_RULER_MODE:
	case MANUAL_RULER_MODE:
	case SELF_RULER_MODE:
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
				x+=12*2;		
				Printf24("Modus referensi",x,y,line_color,1,back_color);
					break;
			case PORTUGAL:	//葡萄牙
				// x+=12*2;		
				Printf24("modo Referê   ",x,y,line_color,1,back_color);	//Referência
				Printf24("           ncia",x,y,line_color,0,back_color);
					break;
			case FRENCH:	//法语	
				x+=12*2;	
				Printf24("MODE PAR DEFAUT",x,y,line_color,1,back_color);
					break;	
			}
			break;
	case AUTO_TOOLS_MODE:
	case MANUAL_TOOLS_MODE:
	case SELF_TOOLS_MODE:
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
				x+=12*2;	
				Printf24("Modus parameter",x,y,line_color,1,back_color);
					break;
			case PORTUGAL:	//葡萄牙
				// x+=12*2;		
				Printf24("modo Par metros",x,y,line_color,1,back_color);	//Parametros
				ASCII_Printf("a",ASCII24_MODE,12,24,PUTAO_ZK24_XOR, x+(8*12),y,line_color,back_color);
					break;
			case FRENCH:	//法语		
				x+=12*2;	
				Printf24("MODE PARAMETRE",x,y,line_color,1,back_color);
					break;
			}	
			break;
	case AUTO_PLUS_MODE:
	case SELF_PLUS_MODE:
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
			case FRENCH:	//法语		
				Printf24("MODE AUTO ADDI",x,y,line_color,1,back_color);	//
					break;
			}	
			break;
	case AUTO_MINUS_MODE:
	case SELF_MINUS_MODE:
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
			case FRENCH:	//法语		
				Printf24("MODE AUTO REDUC",x,y,line_color,1,back_color);	//
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
			case FRENCH:	//法语		
				Printf24("MODE CALENDRIER",x,y,line_color,1,back_color);	//
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
			case FRENCH:	//法语	
				Printf16("MODE IMPULSION EQUIVALENT",x,y,line_color,1,back_color);	//
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
			case FRENCH:	//法语	
				Printf24("MODE PARAMETRE 'C'",x,y,line_color,1,back_color);
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
			case FRENCH:	//法语		
				Printf16("MODE MOT DE PASSE",x,y,line_color,1,back_color);	
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
// Bmp_Decode((Int32U)MIDDLE_PAGE_sdram, x, y, (pInt16U)SDRAM0_BASE_ADDR);
x1=MIDDLE_PAGE_X,y1=MIDDLE_PAGE_Y+5;
x2=x1+M_PAGE_WIDE-35,y2=MIDDLE_PAGE_Y+250;
GLCD_SetWindow_Fill(x1,y1,x2,y2, fill_color,fill_color);
// GLCD_SetWindow_Fill(SCHEDULE_X,SCHEDULE_Y,SCHEDULE_X+SCHEDULE_WIDE+0,SCHEDULE_Y+SCHEDULE_HIGH,fill_color,fill_color);  //覆盖 进度条
}

//-------------F1,2,3...mode fun pic
void F1LabelFunPic_dis(Int16U x, Int16U y)//标签功能
{
Bmp_Decode((Int32U)LABEL_FUN_sdram, x, y, (pInt16U)SDRAM0_BASE_ADDR);
}
void F2DivideFunPic_dis(Int16U x, Int16U y)//等分功能
{
Bmp_Decode((Int32U)DIVIDE_FUN_sdram, x, y, (pInt16U)SDRAM0_BASE_ADDR);
}
void F1RulerFunPic_dis(Int16U x, Int16U y)//基准功能
{
Bmp_Decode((Int32U)RULER_FUN_sdram, x, y, (pInt16U)SDRAM0_BASE_ADDR);
}
void F2DatasFunPic_dis(Int16U x, Int16U y)//F2参数功能
{
Bmp_Decode((Int32U)TOOLS_sdram, x, y, (pInt16U)SDRAM0_BASE_ADDR);
}
void F3ClockFunPic_dis(Int16U x, Int16U y)//F3日历功能
{
Bmp_Decode((Int32U)CALENDAR_sdram, x, y, (pInt16U)SDRAM0_BASE_ADDR);
}

void PsswordFunPic_dis(Int16U x, Int16U y)//密码功能模式pic
{
Bmp_Decode((Int32U)LOCK_KEY_sdram, x, y, (pInt16U)SDRAM0_BASE_ADDR);
}
//*****************F1,F2,F3,....Icon
void F1LabelIconUp_dis(Int16U x,Int16U y)//F1标签up
{
Bmp_Decode((Int32U)F1_LABELS_UP_sdram, x, y, (pInt16U)SDRAM0_BASE_ADDR);
}
void F2DivideIconUp_dis(Int16U x, Int16U y)//F2等分up
{
Bmp_Decode((Int32U)F2_DIVIDE_UP_sdram, x, y, (pInt16U)SDRAM0_BASE_ADDR);
}
void F3ProjectIconUp_dis(Int16U x, Int16U y)//F3程序up
{
Bmp_Decode((Int32U)F3_SELECT_PRO_UP_sdram, x, y, (pInt16U)SDRAM0_BASE_ADDR);
}
void F4PushIconUp_dis(Int16U x, Int16U y)//F4up
{
Bmp_Decode((Int32U)F4_PUSH_UP_sdram, x, y, (pInt16U)SDRAM0_BASE_ADDR);
}

void F1OkIconUp_dis(Int16U x, Int16U y)//F1完成
{
Bmp_Decode((Int32U)F1_FINISHED_sdram, x, y, (pInt16U)SDRAM0_BASE_ADDR);
}
void F2out_Up_dis(Int16U x, Int16U y)//F2退出up
{
Bmp_Decode((Int32U)F2_OUT_UP_sdram, x, y, (pInt16U)SDRAM0_BASE_ADDR);
}
void L_R_Arrow_dis(Int16U x, Int16U y)//左右箭头
{
Bmp_Decode((Int32U)L_R_ARROW_sdram, x, y, (pInt16U)SDRAM0_BASE_ADDR);
}
void F3LabelTime_Up_dis(Int16U x, Int16U y)//F3 标签次数up
{
Bmp_Decode((Int32U)LABEL_TIME_F3_UP_sdram, x, y, (pInt16U)SDRAM0_BASE_ADDR);
}
void F3LabelTime_Down_dis(Int16U x, Int16U y)//F3 标签次数down
{
Bmp_Decode((Int32U)LABEL_TIME_F3_DOWN_sdram, x, y, (pInt16U)SDRAM0_BASE_ADDR);
}

void F4LabelDesert_Up_dis(Int16U x, Int16U y)//F4 标签up
{
Bmp_Decode((Int32U)LABEL_DESERT_F4_UP_sdram, x, y, (pInt16U)SDRAM0_BASE_ADDR);
}
void F4LabelDesert_Down_dis(Int16U x, Int16U y)//F4 标签down
{
Bmp_Decode((Int32U)LABEL_DESERT_F4_DOWN_sdram, x, y, (pInt16U)SDRAM0_BASE_ADDR);
}



void LabelModeButton_dis(void)//标签模式 下 按钮
{
if(LabelTime_flag==0)
	{//废边模式
		F3LabelTime_Up_dis(F3_LABEL_TIME_X,F3_LABEL_TIME_Y);
		F4LabelDesert_Down_dis(F4_LABEL_DESERT_X,F4_LABEL_DESERT_Y);
	}
else	//次数模式
	{
		F3LabelTime_Down_dis(F3_LABEL_TIME_X,F3_LABEL_TIME_Y);
		F4LabelDesert_Up_dis(F4_LABEL_DESERT_X,F4_LABEL_DESERT_Y);
	}
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
void F6ExitButtUp_dis(Int16U x, Int16U y)//F6Exit butt 
{
Bmp_Decode((Int32U)F6_EXIT_BUTT_sdram, x, y, (pInt16U)SDRAM0_BASE_ADDR);
}
void EnterButtUp_dis(Int16U x, Int16U y)//OK butt 确定
{
Bmp_Decode((Int32U)ENTER_BUTT_sdram, x, y, (pInt16U)SDRAM0_BASE_ADDR);
}

void F1RulerIconUp_dis(Int16U x, Int16U y)//基准F1
{
Bmp_Decode((Int32U)F1_RULER_UP_sdram, x, y, (pInt16U)SDRAM0_BASE_ADDR);
}
void F2ParamaterIconUp_dis(Int16U x, Int16U y)//F2参数
{
Bmp_Decode((Int32U)F2_TOOLS_UP_sdram, x, y, (pInt16U)SDRAM0_BASE_ADDR);
}
void F3ClockIconUp_dis(Int16U x, Int16U y)//F3时间
{
Bmp_Decode((Int32U)F3_CLOCK_UP_sdram, x, y, (pInt16U)SDRAM0_BASE_ADDR);
}
void F3AddIconUp_dis(Int16U x, Int16U y)//F3++up
{
Bmp_Decode((Int32U)F3_PLUS_UP_sdram, x, y, (pInt16U)SDRAM0_BASE_ADDR);
}
void F4SubIconUp_dis(Int16U x, Int16U y)//F4--up
{
Bmp_Decode((Int32U)F4_MINUS_UP_sdram, x, y, (pInt16U)SDRAM0_BASE_ADDR);
}
void F4PulseSetIconUp_dis(Int16U x,Int16U y)//F4脉冲当量
{
Bmp_Decode((Int32U)F4_PULSE_UP_sdram, x, y, (pInt16U)SDRAM0_BASE_ADDR);
}
void F5CutIcon_Up_dis(Int16U x, Int16U y)//F5刀up
{
Bmp_Decode((Int32U)F5_CUT_UP_sdram, x, y, (pInt16U)SDRAM0_BASE_ADDR);
}
void F0CutAllIcon_Up_dis(Int16U x, Int16U y)//F0全刀up
{
Bmp_Decode((Int32U)F0_ALLCUT_UP_sdram, x, y, (pInt16U)SDRAM0_BASE_ADDR);
}
void F5PreCircleButt_Up_dis(Int16U x, Int16U y)//F5压纸循环button up
{
Bmp_Decode((Int32U)F5_PRE_FLG_BUTT_UP_sdram, x, y, (pInt16U)SDRAM0_BASE_ADDR);
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
void RedLine_dis(Int16U x, Int16U y)//红线
{
Bmp_Decode((Int32U)RED_LINE_sdram, x, y, (pInt16U)SDRAM0_BASE_ADDR);
}
void Hand_IR_dis(Int16U x, Int16U y)//手 红外
{
Bmp_Decode((Int32U)HAND_IR_sdram, x, y, (pInt16U)SDRAM0_BASE_ADDR);
}

void RightArrow_dis(Int16U x, Int16U y)//右箭头 -->
{
Bmp_Decode((Int32U)CURSOR_sdram, x, y, (pInt16U)SDRAM0_BASE_ADDR);
}
void Schedule_dis(Int16U x, Int16U y)//进度
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
void AutoRoutePRE_dis(Int16U x, Int16U y)//k自动循环 标志
{
Bmp_Decode((Int32U)PRE_AUTO_F_sdram, x, y, (pInt16U)SDRAM0_BASE_ADDR);
}


void Stop_Up_dis(Int16U x, Int16U y)//停止up
{
Bmp_Decode((Int32U)STOP_UP_sdram, x, y, (pInt16U)SDRAM0_BASE_ADDR);
}
void Stop_Down_dis(Int16U x, Int16U y)//停止down
{
// Bmp_Decode((Int32U)STOP_DOWN_sdram, x, y, (pInt16U)SDRAM0_BASE_ADDR);
}
void Run_Up_dis(Int16U x, Int16U y)//运行up
{
Bmp_Decode((Int32U)RUN_UP_sdram, x, y, (pInt16U)SDRAM0_BASE_ADDR);
}
void Run_Down_dis(Int16U x, Int16U y)//运行down
{
// Bmp_Decode((Int32U)RUN_DOWN_sdram, x, y, (pInt16U)SDRAM0_BASE_ADDR);
}
void RunBIG_Up_dis(Int16U x, Int16U y)//运行1up
{
Bmp_Decode((Int32U)RUN_BIG_BUTT_UP_sdram, x, y, (pInt16U)SDRAM0_BASE_ADDR);
}
void StopBIG_Up_dis(Int16U x, Int16U y)//停止1up
{
Bmp_Decode((Int32U)STOP_BIG_BUTT_UP_sdram, x, y, (pInt16U)SDRAM0_BASE_ADDR);
}




void Delete_Up_dis(Int16U x, Int16U y)//删除up
{
Bmp_Decode((Int32U)DELETE_UP_sdram, x, y, (pInt16U)SDRAM0_BASE_ADDR);
}
void DeleteAll_Up_dis(Int16U x, Int16U y)//全删up
{
Bmp_Decode((Int32U)DELETE_ALL_UP_sdram, x, y, (pInt16U)SDRAM0_BASE_ADDR);
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




void ElectricalWheel_dis(void)  //电子手轮  开关状态
{
if(MotorType>=MOTOR_AC_SERVO)
	{
	if(ElectricWheelOn_flag==0)
		{
		// Wheel0_dis(WHEEL_STA_X, WHEEL_STA_Y);
		if(WorkMode==MANUAL_MODE)
			F4Wheel0_dis(F4_WHEEL_BUTT_X,F4_WHEEL_BUTT_Y);
		}
	else	
		{
		// Wheel1_dis(WHEEL_STA_X, WHEEL_STA_Y);
		if(WorkMode==MANUAL_MODE)
			F4Wheel1_dis(F4_WHEEL_BUTT_X,F4_WHEEL_BUTT_Y);
		}
	}
}

//-------------*****模式icon间 切换 显示******------------------(icon+name)
void ProTableIcon_dis(void)	//程序列表模式下 icon显示
{
F1ShowMessIconUp_dis(F1LABEL_BUTT_X,F1LABEL_BUTT_Y);//F1 查看mess
switch(DisAllProgMode)
	{
	case PRO_BY_NUM://按序号
			F2ByTimeIconUp_dis(F2DIVIDE_BUTT_X,F2DIVIDE_BUTT_Y);//F2 按时间排列up
			F3ByNumIconDown_dis(F3PROJECT_BUTT_X,F3PROJECT_BUTT_Y);//F3 按序号排列down
			break;
	case PRO_BY_TIME://按时间
			F2ByTimeIconDown_dis(F2DIVIDE_BUTT_X,F2DIVIDE_BUTT_Y);//F2 按时间排列down
			F3ByNumIconUp_dis(F3PROJECT_BUTT_X,F3PROJECT_BUTT_Y);//F3 按序号排列up
			break;	
	}
F4DeleteOneProIconUp_dis(F4PUSHFLAG_BUTT_X,F4PUSHFLAG_BUTT_Y);//F4删除一个pro
F5DeleteAllProIconUp_dis(F5DELETE_BUTT_X,F5DELETE_BUTT_Y);//F5删除所有pro
// F6ExitButtUp_dis(F6EXIT_BUTT_X,F6EXIT_BUTT_Y);//F6Exit butt 标志
EnterButtUp_dis(ENTER_OK_BUTT_X, ENTER_OK_BUTT_Y);//OK butt 确定
// UP_ARROW_ProgSel_dis(UP_ARROW_PRO_X , UP_ARROW_PRO_Y);// 程序选择  上箭头
// DOWN_ARROW_ProgSel_dis(DOWN_ARROW_PRO_X , DOWN_ARROW_PRO_Y);// 程序选择  下箭头
}
void ProMessIcon_dis(void)	//输入法模式 icon显示
{
switch(InputMode)
	{
	case PINYIN_INPUT:	//拼音输入
			F1PinyinIconDown_dis(F1LABEL_BUTT_X,F1LABEL_BUTT_Y);//F1拼音输入down---------
			F2CharIconUp_dis(F2DIVIDE_BUTT_X,F2DIVIDE_BUTT_Y);//F2字母输入up
			F3NumIconUp_dis(F3PROJECT_BUTT_X,F3PROJECT_BUTT_Y);//F3数字输入up
			F4ExitIconUp_dis(F4PUSHFLAG_BUTT_X,F4PUSHFLAG_BUTT_Y);//F4up退出
			break;
	case CHAR_INPUT:	//字母输入
			F1PinyinIconUp_dis(F1LABEL_BUTT_X,F1LABEL_BUTT_Y);//F1拼音输入up
			F2CharIconDown_dis(F2DIVIDE_BUTT_X,F2DIVIDE_BUTT_Y);//F2字母输入down---------
			F3NumIconUp_dis(F3PROJECT_BUTT_X,F3PROJECT_BUTT_Y);//F3数字输入up
			F4ExitIconUp_dis(F4PUSHFLAG_BUTT_X,F4PUSHFLAG_BUTT_Y);//F4up退出
			break;	
	case NUMBER_INPUT:	//数字 输入
			F1PinyinIconUp_dis(F1LABEL_BUTT_X,F1LABEL_BUTT_Y);//F1拼音输入up
			F2CharIconUp_dis(F2DIVIDE_BUTT_X,F2DIVIDE_BUTT_Y);//F2字母输入up
			F3NumIconDown_dis(F3PROJECT_BUTT_X,F3PROJECT_BUTT_Y);//F3数字输入down---------
			F4ExitIconUp_dis(F4PUSHFLAG_BUTT_X,F4PUSHFLAG_BUTT_Y);//F4up退出
			break;		
	}
}
void SubModeIcon_dis(Int16U mode)//================子模式  icon显示
{
Int16U x1,y1,x2,y2,back_color;
//清除F1-F6 button 显示*****************
back_color=TEXT_TAB_BACK_COLOR;
x1=F1LABEL_BUTT_X,y1=F1LABEL_BUTT_Y;
x2=x1+50,y2=y1+ICONBUTT_GAP_V*4-10;
GLCD_SetWindow_Fill(x1,y1,x2,y2,back_color,back_color);//空白F1,2,3...
//--------------清除方向箭,F0,F5
if((mode!=PROG_PRO_MODE)&&(mode!=TEACH_PRO_MODE)
	&&(mode!=PROG_PRO_MESS_MODE)&&(mode!=TEACH_PRO_MESS_MODE))	//程序 信息
	{
	x1=BACK_PAGE_X,y1=BACK_PAGE_Y;
	x2=F0_ALL_CUT_X+50,y2=F0_ALL_CUT_Y+50;
	GLCD_SetWindow_Fill(x1,y1,x2,y2,back_color,back_color);  //隐藏方向箭头,F0,F5 .....
	}
//--------------清除F
back_color=WIN_DOWN_BACK_COLOR;
x1=F_KEY_X,y1=F_KEY_Y;
x2=F_KEY_X+F_KEY_WIDE*2,y2=F_KEY_Y+F_KEY_HIGH;
GLCD_SetWindow_Fill(x1,y1,x2,y2,back_color,back_color);  //F.....
//--------------删除，运行.......
x1=DELETE_X,y1=DELETE_Y;
x2=STOP_BIG_X+RUN_BIG_WIDE,y2=RUN_Y+DELETE_HIGH;
GLCD_SetWindow_Fill(x1,y1,x2,y2,back_color,back_color);  //删除，运行..
//-----work mode
switch(mode)
	{
	case PROG_MODE://编程模式..............
	case TEACH_MODE:		//示教模式..............
			//----------F
			Fkey_Up_dis( F_KEY_X, F_KEY_Y);//F键up
			//方向----------
			FrontPage_Up_dis( FRONT_PAGE_X,  FRONT_PAGE_Y);//前进up
			BackPage_Up_dis( BACK_PAGE_X,  BACK_PAGE_Y);//后退up
			F5CutIcon_Up_dis(F5_CUT_X,F5_CUT_Y); //F5一刀up
			F0CutAllIcon_Up_dis(F0_ALL_CUT_X,F0_ALL_CUT_Y); //全刀up
			//F1,2,3,4......
			F1LabelIconUp_dis(F1LABEL_BUTT_X,F1LABEL_BUTT_Y);//F1标签up
			F2DivideIconUp_dis(F2DIVIDE_BUTT_X,F2DIVIDE_BUTT_Y);//F2等分up
			F3ProjectIconUp_dis(F3PROJECT_BUTT_X,F3PROJECT_BUTT_Y);//F3程序up
			F4PushIconUp_dis(F4PUSHFLAG_BUTT_X,F4PUSHFLAG_BUTT_Y);//推纸按钮up
			// // F5DeleteAllKnifeIconUp_dis(F5DELETE_BUTT_X,F5DELETE_BUTT_Y);//	删除所有刀数据
			//------------
			Delete_Up_dis( DELETE_X, DELETE_Y );//删除up
			DeleteAll_Up_dis( DELETE_ALL_X, DELETE_ALL_Y);//全删up
			//------------
			if(mode==TEACH_MODE)//示教模式.
				{
				Run_Up_dis(RUN_X,RUN_Y);//运行up
				Stop_Up_dis(STOP_X,STOP_Y);//停止up
				}
			break;
	case MANUAL_MODE:	//手动模式..............
			//----------F
			Fkey_Up_dis( F_KEY_X, F_KEY_Y);//F键up
			//方向----------手动下的显示。。。。。。
			FrontPage_Up_dis( MAN_FRONT_PAGE_X,  MAN_FRONT_PAGE_Y);//前进up--------------
			BackPage_Up_dis( MAN_BACK_PAGE_X,  MAN_BACK_PAGE_Y);//后退up-------------------
			if((MotorType<MOTOR_DC_SERVO)||(MotorType>=MOTOR_AC_SERVO))
				{
				FastFWD_Up_dis(MAN_FAST_FWD_X, MAN_FAST_FWD_Y);//快进up
				FastBACK_Up_dis(MAN_FAST_BACK_X, MAN_FAST_BACK_Y);//快退up
				}
			//F1,2,3,4......
			F1RulerIconUp_dis(F1LABEL_BUTT_X,F1LABEL_BUTT_Y);//F1基准butt
			F2ParamaterIconUp_dis(F2DIVIDE_BUTT_X,F2DIVIDE_BUTT_Y);//F2参数
			F3ClockIconUp_dis(F3PROJECT_BUTT_X,F3PROJECT_BUTT_Y);//F3时间
			ElectricalWheel_dis();  //电子手轮  开关状态
			if(MotorType<MOTOR_DC_SERVO)    //变频器--
				F4PulseSetIconUp_dis(F4PUSHFLAG_BUTT_X,F4PUSHFLAG_BUTT_Y);//F4脉冲当量
			// // else
			//----------------
			RunBIG_Up_dis(RUN_BIG_X, RUN_BIG_Y);//运行1up
			StopBIG_Up_dis(STOP_BIG_X, STOP_BIG_Y);//停止1up
			break;	
	case AUTO_MODE://自动模式..............
	case SELF_CUT_MODE:		//自刀模式..............
			//----------F
			Fkey_Up_dis( F_KEY_X, F_KEY_Y);//F键up
			//方向----------
			FrontPage_Up_dis( FRONT_PAGE_X,  FRONT_PAGE_Y);//前进up
			BackPage_Up_dis( BACK_PAGE_X,  BACK_PAGE_Y);//后退up
			if(mode == AUTO_MODE)
				F5PreCircleButt_Up_dis(F5_CUT_X,F5_CUT_Y);//F5压纸循环button
			//F1,2,3,4......
			F1RulerIconUp_dis(F1LABEL_BUTT_X,F1LABEL_BUTT_Y);//F1基准butt
			F2ParamaterIconUp_dis(F2DIVIDE_BUTT_X,F2DIVIDE_BUTT_Y);//F2参数
			F3AddIconUp_dis(F3PROJECT_BUTT_X,F3PROJECT_BUTT_Y);//F3++
			F4SubIconUp_dis(F4PUSHFLAG_BUTT_X,F4PUSHFLAG_BUTT_Y);//F4--
			// // ElectricalWheel_dis();  //电子手轮  开关状态
			//----------------
			RunBIG_Up_dis(RUN_BIG_X, RUN_BIG_Y);//运行1up
			StopBIG_Up_dis(STOP_BIG_X, STOP_BIG_Y);//停止1up
			break;
	//---编程 示教..............
	case PROG_LABEL_MODE:		 //标签
	case TEACH_LABEL_MODE:		 //标签
			F1OkIconUp_dis(FINISHED_X,FINISHED_Y);//完成
			F2out_Up_dis(F2OUT_X,F2OUT_Y);//F2up退出
			UpArrow_Up_dis( SUB_UP_ARROW_X,  SUB_UP_ARROW_Y);//上箭头up
			DownArrow_Up_dis( SUB_DOWN_ARROW_X,  SUB_DOWN_ARROW_Y);//下箭头up
			LabelModeButton_dis();//标签模式 下 按钮
			//---------
			F1LabelFunPic_dis(LABEL_FUN_X,LABEL_FUN_Y);//标签功能
			break;
	case PROG_DIVIDE_MODE:	 //等分
	case TEACH_DIVIDE_MODE:	 //等分
			F1OkIconUp_dis(FINISHED_X,FINISHED_Y);//完成
			F2out_Up_dis(F2OUT_X,F2OUT_Y);//F2up退出
			UpArrow_Up_dis( SUB_UP_ARROW_X,  SUB_UP_ARROW_Y);//上箭头up
			DownArrow_Up_dis( SUB_DOWN_ARROW_X,  SUB_DOWN_ARROW_Y);//下箭头up
			//---------
			F2DivideFunPic_dis(DIVIDE_FUN_X,DIVIDE_FUN_Y);//等分功能 pic
			// // if(DivideValue_flag==0) //等分数功能
				// // {
				// // F1OkIconUp_dis(F1LABEL_BUTT_X,F1LABEL_BUTT_Y);//F1完成
				// // F2DivNumIconDown_dis(F2DIVIDE_BUTT_X,F2DIVIDE_BUTT_Y);//F2等分数down------
				// // F3DivDataIconUp_dis(F3PROJECT_BUTT_X,F3PROJECT_BUTT_Y);//F3等分值up
				// // F4ExitIconUp_dis(F4PUSHFLAG_BUTT_X,F4PUSHFLAG_BUTT_Y);//F4up退出
				// // //------------
				// // F2DivideNumPic_dis(DIVIDE_FUN_PIC_X,DIVIDE_FUN_PIC_Y);//等分数功能 pic
				// // }
			// // else	//等分值
				// // {
				// // F1OkIconUp_dis(F1LABEL_BUTT_X,F1LABEL_BUTT_Y);//完成
				// // F2DivNumIconUp_dis(F2DIVIDE_BUTT_X,F2DIVIDE_BUTT_Y);//F2等分数up
				// // F3DivDataIconDown_dis(F3PROJECT_BUTT_X,F3PROJECT_BUTT_Y);//F3等分值down---
				// // F4ExitIconUp_dis(F4PUSHFLAG_BUTT_X,F4PUSHFLAG_BUTT_Y);//F4up退出
				// // //------------
				// // F3DivideValuePic_dis(DIVIDE_FUN_PIC_X,DIVIDE_FUN_PIC_Y);//等分值功能 pic
				// // }
			break;
	case PROG_PRO_MODE:	//程序选择
	case TEACH_PRO_MODE:	//程序选择
			ProTableIcon_dis();	//程序列表模式下 icon显示
			break;
	case PROG_PRO_MESS_MODE:	 //程序 信息
	case TEACH_PRO_MESS_MODE:	//程序 信息
			ProMessIcon_dis();	//输入法模式 icon显示
			
			break;	
	//--自动， 手动
	case AUTO_RULER_MODE:  //基准
	case MANUAL_RULER_MODE:  //基准
	case SELF_RULER_MODE:  //基准
			F2out_Up_dis(F2OUT_X,F2OUT_Y);//F2up退出
			//---------
			F1RulerFunPic_dis(RULER_FUN_X, RULER_FUN_Y);//基准功能pic
			// // F1OkIconUp_dis(F1LABEL_BUTT_X,F1LABEL_BUTT_Y);//F1完成
			// // F2ExitIconUp_dis(F2DIVIDE_BUTT_X,F2DIVIDE_BUTT_Y);//F2up退出
			// // //---------
			// // F1RulerFunPic_dis(RULER_FUN_PIC_X,RULER_FUN_PIC_Y);//基准功能pic	
			break;	
	case AUTO_TOOLS_MODE:    //参数
	case MANUAL_TOOLS_MODE:    //参数
	case SELF_TOOLS_MODE:    //参数
			F2out_Up_dis(F2OUT_X,F2OUT_Y);//F2up退出
			L_R_Arrow_dis(L_R_ARROW_X, L_R_ARROW_Y);//左右箭头
			UpArrow_Up_dis( SUB_UP_ARROW_X,  SUB_UP_ARROW_Y);//上箭头up
			DownArrow_Up_dis( SUB_DOWN_ARROW_X,  SUB_DOWN_ARROW_Y);//下箭头up
			// // F1OkIconUp_dis(F1LABEL_BUTT_X,F1LABEL_BUTT_Y);//F1完成
			// // F2ExitIconUp_dis(F2DIVIDE_BUTT_X,F2DIVIDE_BUTT_Y);//F2up退出
			//---------
			F2DatasFunPic_dis(TOOLS_X, TOOLS_Y);//参数功能pic
			break;	
	case MANUAL_CLOCK_MODE://时间模式
			F2out_Up_dis(F2OUT_X,F2OUT_Y);//F2up退出
			UpArrow_Up_dis( SUB_UP_ARROW_X,  SUB_UP_ARROW_Y);//上箭头up
			DownArrow_Up_dis( SUB_DOWN_ARROW_X,  SUB_DOWN_ARROW_Y);//下箭头up
			//---------
			F3ClockFunPic_dis(CALENDA_X,CALENDA_Y); //日历
			// // F1OkIconUp_dis(F1LABEL_BUTT_X,F1LABEL_BUTT_Y);//F1完成
			// // F2ExitIconUp_dis(F2DIVIDE_BUTT_X,F2DIVIDE_BUTT_Y);//F2up退出
			// // //---------
			// // F3ClockFunPic_dis(CLOCK_FUN_PIC_X,CLOCK_FUN_PIC_Y);//F3时钟模式pic	
			break;
	case MANUAL_PULSE_MODE:  //设定脉冲当量
			F2out_Up_dis(F2OUT_X,F2OUT_Y);//F2up退出
			F1OkIconUp_dis(FINISHED_X,FINISHED_Y);//完成
			UpArrow_Up_dis( SUB_UP_ARROW_X,  SUB_UP_ARROW_Y);//上箭头up
			DownArrow_Up_dis( SUB_DOWN_ARROW_X,  SUB_DOWN_ARROW_Y);//下箭头up
			// PulseDegree_dis(PULSE_DEG_X,  PULSE_DEG_Y);//脉冲当量
			// // F1OkIconUp_dis(F1LABEL_BUTT_X,F1LABEL_BUTT_Y);//F1完成
			// // F2ExitIconUp_dis(F2DIVIDE_BUTT_X,F2DIVIDE_BUTT_Y);//F2up退出
			break;
	case MANUAL_SERVO_C_MODE:	//直流伺服 C 参数
			F2out_Up_dis(F2OUT_X,F2OUT_Y);//F2up退出
			UpArrow_Up_dis( SUB_UP_ARROW_X,  SUB_UP_ARROW_Y);//上箭头up
			DownArrow_Up_dis( SUB_DOWN_ARROW_X,  SUB_DOWN_ARROW_Y);//下箭头up
			//---------
			F2DatasFunPic_dis(TOOLS_X, TOOLS_Y);//参数功能pic
			// // F1OkIconUp_dis(F1LABEL_BUTT_X,F1LABEL_BUTT_Y);//F1完成
			// // F2ExitIconUp_dis(F2DIVIDE_BUTT_X,F2DIVIDE_BUTT_Y);//F2up退出
			break;	
	case MANUAL_PASS_MODE:   //密码
			// // F1OkIconUp_dis(F1LABEL_BUTT_X,F1LABEL_BUTT_Y);//F1完成
			// // F2ExitIconUp_dis(F2DIVIDE_BUTT_X,F2DIVIDE_BUTT_Y);//F2up退出
			F2out_Up_dis(F2OUT_X,F2OUT_Y);//F2up退出
			L_R_Arrow_dis(L_R_ARROW_X, L_R_ARROW_Y);//左右箭头
			UpArrow_Up_dis( SUB_UP_ARROW_X,  SUB_UP_ARROW_Y);//上箭头up
			DownArrow_Up_dis( SUB_DOWN_ARROW_X,  SUB_DOWN_ARROW_Y);//下箭头up
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
	case PROG_MODE://编程模式..............
			//-------main mode
			
			break;
	case MANUAL_MODE:	//手动模式..............
			
			break;
	case AUTO_MODE://自动模式..............
			
			break;
	case SELF_CUT_MODE:		//自刀模式..............
			
			break;
	case TEACH_MODE:		//示教模式..............
			
			break;
	}
// // RunButtonDisExec();	//运行 按钮 显示处理
//-----sub mode
SubModeIcon_dis(mode);//--------子模式  icon显示
}

//-----------各个 模式下 画面内容page  显示************************
void ClrSizeTable_dis(void)	//清除 刀数据列表
{
Int16U x1,y1,x2,y2,back_color;
back_color=TEXT_TAB_BACK_COLOR;
x1=RIGHT_ARROW_X,y1=RIGHT_ARROW_Y;
x2=RED_KNIFE_X+25,y2=RIGHT_ARROW_Y+SIZETEXT_HIGH*5-10;
GLCD_SetWindow_Fill(x1,y1,x2,y2,back_color,back_color);//空白列表
}
void ProgModePage_dis(void)  //编程模式 部分画面更新++++++++++
{
ClrSizeTable_dis();//刀数据 列表空白
//主模式......
MainModeIcon_dis(WorkMode);//编程模式..............

//---------------Schedule
Schedule_dis(SCHEDULE_X,SCHEDULE_Y);//进度
ProgressBar_dis(OnePro_head.pro_knifeSUM,Knife_order);  //进度条 显示
}
void AutoModePage_dis(void) //自动模式 部分画面显示++++++++++++
{
ClrSizeTable_dis();//刀数据 列表空白
//主模式......
MainModeIcon_dis(WorkMode);//自动模式.........

//---------------Schedule
Schedule_dis(SCHEDULE_X,SCHEDULE_Y);//进度
ProgressBar_dis(OnePro_head.pro_knifeSUM,Knife_order);  //进度条 显示
}
void AutoCutModePage_dis(void) //自刀模式 部分画面显示+++++++++++
{
ClrSizeTable_dis();//刀数据 列表空白
//主模式......
MainModeIcon_dis(WorkMode);//自刀模式...........
//---------------Schedule
Schedule_dis(SCHEDULE_X,SCHEDULE_Y);//进度
ProgressBar_dis(OnePro_head.pro_knifeSUM,Knife_order);  //进度条 显示
}
void ManualModePage_dis(void)  //手动模式 部分画面++++++++++++
{
Int16U x1,y1,x2,y2,color;
color=TEXT_TAB_BACK_COLOR;
ClrSizeTable_dis();//刀数据 列表空白
GLCD_SetWindow_Fill(SCHEDULE_X,SCHEDULE_Y,SCHEDULE_X+SCHEDULE_WIDE+0,SCHEDULE_Y+SCHEDULE_HIGH,color,color);  //覆盖 进度条
// MiddlePage_dis();//空白
//主模式......
MainModeIcon_dis(WorkMode);//手动模式........

}

void TeachModePage_dis(void)   //示教模式  部分页面++++++++++++
{
ClrSizeTable_dis();//刀数据 列表空白
//主模式......
MainModeIcon_dis(WorkMode);//示教模式...........

FrontPage_Up_dis( FRONT_PAGE_X,  FRONT_PAGE_Y);//前进up
BackPage_Up_dis( BACK_PAGE_X,  BACK_PAGE_Y);//后退up

//---------------Schedule
Schedule_dis(SCHEDULE_X,SCHEDULE_Y);//进度
ProgressBar_dis(OnePro_head.pro_knifeSUM,Knife_order);  //进度条 显示
}


//**************************************编程 下
void ProgSet_dis(Int32U size, Int16U x, Int16U y, Int8U set_flag)// 参数设定页内 尺寸显示
{
Int8U num[8],k,int_flag=0;
Int16U back_color=TEXT_TAB_BACK_COLOR;
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
			
		if((WorkMode==PROG_DIVIDE_MODE)||(WorkMode==TEACH_DIVIDE_MODE)) //等分
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
		else if((WorkMode==PROG_LABEL_MODE)||(WorkMode==TEACH_LABEL_MODE)) //标签
			{
			if(PorgSet_sel==2)
				{
				if(LabelTime_flag==1)
					{//标签次数模式
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

void F1_LabelSetName_dis(void)	//标签项 名称
{
volatile Int16U x,y,gap;
Int32U	prama_3st_temp;
// Int16U back_color=TEXT_TAB_BACK_COLOR;
 // x=80,y=200,gap=50;
 x=TOTAL_SIZE_X-150,y=TOTAL_SIZE_Y,gap=ROW_GAP1;
ClrSizeTable_dis();//刀数据 列表空白
switch(Language)
	{
	case CHN_HAN:
		Printf24("总长：",x,y,BLACK_COLOR,0,0xffff);y+=gap;
		Printf24("标签：",x,y,BLACK_COLOR,0,0xffff);y+=gap;
		if(LabelTime_flag==0)
			{//废边模式
			Printf24("废边：",x,y,BLACK_COLOR,0,0xffff);
			}
		else	
			{//次数模式
			Printf24("次数：",x,y,BLACK_COLOR,0,0xffff);	
			}
			break;
	case ENGLISH:
		Printf24("Total len:",x,y,BLACK_COLOR,0,0xffff);y+=gap;
		Printf24("Label：",x,y,BLACK_COLOR,0,0xffff);y+=gap;
		if(LabelTime_flag==0)
			{//废边模式
			Printf24("Waste：",x,y,BLACK_COLOR,0,0xffff);
			}
		else	
			{//次数模式
			Printf24("Time：",x,y,BLACK_COLOR,0,0xffff);	
			}
			break;
	case PORTUGAL:	//葡萄牙
		Printf24("Total:",x,y,BLACK_COLOR,0,0xffff);y+=gap;
		Printf24("etiqueta:",x,y,BLACK_COLOR,0,0xffff);y+=gap;
		if(LabelTime_flag==0)
			{//废边模式
			Printf24("descartar:",x,y,BLACK_COLOR,0,0xffff);
			}
		else	
			{//次数模式
			Printf24("vezes: ",x,y,BLACK_COLOR,0,0xffff);	
			}
			break;	
	case FRENCH:	//法语
		Printf16("LONGUEUR TOTAL:",x,y,BLACK_COLOR,0,0xffff);y+=gap;
		Printf16("ETIQUETTE:",x,y,BLACK_COLOR,0,0xffff);y+=gap;
		if(LabelTime_flag==0)
			{//废边模式
			Printf16("CHUTE PAPIER:",x,y,BLACK_COLOR,0,0xffff);
			}
		else	
			{//次数模式
			Printf16("NOMBRE DE FOIS:",x,y,BLACK_COLOR,0,0xffff);	
			}
			break;	
	}
Total_size=0;//总长
Label_size=0;//标签长
Waste_size=0;//废边	
LabelTime=0;//次数	
if(LabelTime_flag==0)
	{//废边模式
	prama_3st_temp=Waste_size;
	}
else
	{
	prama_3st_temp=LabelTime;
	}
PorgSet_sel=0;
ProgSet_dis( Total_size, TOTAL_SIZE_X,  TOTAL_SIZE_Y,1);PorgSet_sel++;
ProgSet_dis( Label_size, LABEL_SIZE_X,  LABEL_SIZE_Y,0);PorgSet_sel++;
ProgSet_dis( prama_3st_temp, WASTE_SIZE_X,  WASTE_SIZE_Y,0);		//废边 ------次数-----	
PorgSet_sel=0;
}

void F1_LabelPage_dis(void)  //标签模式 画面显示
{
// volatile Int16U x,y,gap;
 // x=80,y=200,gap=50;
CurrentArea_save2(MIDDLE_PAGE_X , MIDDLE_PAGE_Y,  M_PAGE_WIDE, M_PAGE_HIGH);
MiddlePage_dis();//中间活页

LabelTime_flag=0;
SubModeIcon_dis(WorkMode);   //标签模式

				//左边
F1_LabelSetName_dis();	//标签项 名称
// ProgSet_dis( 0, TOTAL_SIZE_X,  TOTAL_SIZE_Y,1);//
// ProgSet_dis( 0, LABEL_SIZE_X,  LABEL_SIZE_Y,0);
// ProgSet_dis( 0, WASTE_SIZE_X,  WASTE_SIZE_Y,0);
}

void F2_DividePage_dis(void)  //F2--等分模式 画面显示
{
volatile Int16U x,y,gap;
 x=80,y=200,gap=60;
CurrentArea_save2(MIDDLE_PAGE_X , MIDDLE_PAGE_Y,  M_PAGE_WIDE, M_PAGE_HIGH);
MiddlePage_dis();//中间活页

Total_size=0;//总长
Divide_num=0;//等分数

SubModeIcon_dis(WorkMode);   //等分模式
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
	case PORTUGAL:	//葡萄牙
		Printf24("Total：",x,y,BLACK_COLOR,1,0xffff);y+=gap;
		Printf24("Alí    ",x,y,BLACK_COLOR,1,0xffff);
		Printf24("   quotas:",x,y,BLACK_COLOR,0,0xffff);//Alíquotas
			break;
	case FRENCH:	//法语	
		Printf16("LONGUEUR TOTAL:",x,y,BLACK_COLOR,0,0xffff);y+=gap;
		Printf16("NOMBRE ALIQUOTE:",x,y,BLACK_COLOR,0,0xffff);
			break;
	}
PorgSet_sel=0;
ProgSet_dis( Total_size, DIVIDE_TOTAL_X,  DIVIDE_TOTAL_Y,1);//
PorgSet_sel=1;
ProgSet_dis( Divide_num, DIVIDE_NUM_X,  DIVIDE_NUM_Y,0);
PorgSet_sel=0;
}

void F3_SelProgPage_dis(void) //F3--程序选择 画面显示
{
volatile Int16U x,y,i;
Int16U line_color=BLACK_COLOR,back_color=TEXT_TAB_BACK_COLOR;
 x=90,y=150;
CurrentArea_save2(MIDDLE_PAGE_X , MIDDLE_PAGE_Y,  M_PAGE_WIDE, M_PAGE_HIGH);
MiddlePage_dis();//中间活页

DisAllProgMode=PRO_BY_NUM;
SubModeIcon_dis(WorkMode);   //程序选择模式

switch(Language)
	{
	case CHN_HAN:
		Printf16("序号        名称",x,y,line_color,0,back_color);	x+=380;
		Printf16("步骤        修改日期",x,y,line_color,0,back_color);
			break;
	case ENGLISH:	
		Printf16("Order       Name",x,y,line_color,0,back_color);	x+=380;
		Printf16("Step        Modified",x,y,line_color,0,back_color);
			break;
	case PORTUGAL:	//葡萄牙
		Printf16("N?o.        Nome",x,y,line_color,0,back_color);	
		ASCII_Printf("a",ASCII16_MODE,8,16,PUTAO_ZK16,x+8,y,line_color,back_color);
		x+=380;
		Printf16("Passo    	  Data",x,y,line_color,0,back_color);
			break;
	case FRENCH:	//法语	
		Printf16("NUMERO        NOM",x,y,line_color,0,back_color);	x+=380;
		Printf16("PROCEDURE     MODIF DATE",x,y,line_color,0,back_color);
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
		case PORTUGAL:	//葡萄牙
				Printf16("Intervalo de dados           --",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,BLACK_COLOR,0,0xffff);
				break;
		case FRENCH:	//法语	
				Printf24("VALEUR           	--",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,BLACK_COLOR,0,0xffff);
				break;
		}
Printf24("1        500",REMIND_WINDOW_X+180,REMIND_WINDOW_Y+5,RED_COLOR,0,0xffff);
//-------------------------程序列表
for(i=1;i<=MAIX_PROG;i++)
	ProNumGroup[i]=i;
prog_order=1;
}

//******************************************手 ，自动 ，自刀 下
void ParameterPage_dis(Int8U sel, Int8U flag) //参数 设置显示
{
volatile Int16U x,y,gap,tx_wide=88;
Int16U front_color,back_color;
gap=PARA_ROW_GAP;x=PARA_START_X2+(sel/7)*PARA_COL_WIDE;
Int32U temp;
if(flag==1)
    {
	front_color=TEXT_TAB_BACK_COLOR;
	back_color=BLACK_COLOR;
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
				case PORTUGAL:	//葡萄牙
					Printf16("Intervalo de dados           --",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,BLACK_COLOR,0,0xffff);
						break;
				case FRENCH:	//法语	
					Printf24("VALEUR           	--",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,BLACK_COLOR,0,0xffff);
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
				case PORTUGAL:	//葡萄牙
					Printf16("Intervalo de dados           --",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,BLACK_COLOR,0,0xffff);
						break;
				case FRENCH:	//法语	
					Printf24("VALEUR           	--",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,BLACK_COLOR,0,0xffff);
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
				case PORTUGAL:	//葡萄牙
					Printf16("Intervalo de dados           --",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,BLACK_COLOR,0,0xffff);
						break;
				case FRENCH:	//法语	
					Printf24("VALEUR           	--",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,BLACK_COLOR,0,0xffff);
						break;
				}
			if(Unit==UNIT_MM)	
				Printf24("600      2200",REMIND_WINDOW_X+180,REMIND_WINDOW_Y+5,RED_COLOR,0,0xffff);
			else
				Printf24("23.63    86.61",REMIND_WINDOW_X+180,REMIND_WINDOW_Y+5,RED_COLOR,0,0xffff);
			}
		break;
	case 3:
		GLCD_SetWindow_Fill( x, y, x+tx_wide, y+24, TEXT_TAB_BACK_COLOR, TEXT_TAB_BACK_COLOR);//clear text win
		switch(Language)
			{
			case CHN_HAN:
				Printf24("中文    ",x,y,front_color,1,back_color); //语言
					break;
			case ENGLISH:
				Printf24("English ",x,y,front_color,1,back_color); //语言
					break;	
			case PORTUGAL:	//葡萄牙
				Printf24("Portuga ",x,y,front_color,1,back_color); //语言
				// Printf16("portuguê",x,y,front_color,1,back_color); //语言
				// Printf16("        s",x,y,front_color,0,back_color); //语言
					break;
			case FRENCH:	//法语
				Printf24("Fran?ais",x,y,front_color,1,back_color); //语言
				ASCII_Printf("c",ASCII24_MODE,12,24,PUTAO_ZK24,x+12*4,y,front_color,back_color);
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
				case PORTUGAL:	//葡萄牙
					Printf16("Pressione a tecla Insert para alternar idiomas",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,BLACK_COLOR,0,0xffff);
						break;	
				case FRENCH:	//法语
					Printf16("APPUYER SUR 'INSERER' POUR CHANGER LA LANGUE",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,BLACK_COLOR,0,0xffff);
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
				case PORTUGAL:	//葡萄牙
					Printf16("Pressione a tecla Insert para comutar a unidade",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,BLACK_COLOR,0,0xffff);
					break;		
				case FRENCH:	//法语
					Printf16("APPUYER SUR 'INSERER' POUR CHANGER L'UNITE",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,BLACK_COLOR,0,0xffff);
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
				case PORTUGAL:	//葡萄牙
					Printf16("Intervalo de dados           --",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,BLACK_COLOR,0,0xffff);
					break;	
				case FRENCH:	//法语
					Printf24("VALEUR            -- ",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,BLACK_COLOR,0,0xffff);
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
					Printf24("有效(     -     ),无效( 0-      )",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,BLACK_COLOR,0,0xffff);
					break;
				case ENGLISH:	
					Printf24("Valid(    -    ),Invalid(0-    )",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,BLACK_COLOR,0,0xffff);
					break;
				case PORTUGAL:	//葡萄牙
				// case SPANISH: //西班牙
					Printf24("eficaz    -   ,invá            ",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,BLACK_COLOR,0,0xffff);
					Printf24("                   li",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,BLACK_COLOR,0,0xffff);//inválido
					Printf24("                     do(0-     )",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,BLACK_COLOR,0,0xffff);//inválido
						break;
				case FRENCH:	//法语
					Printf16("VALABLE(      -      ),NON VALABLE( 0-      )",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,BLACK_COLOR,0,0xffff);
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
					Printf24("无效   ",x,y,front_color,1,back_color); //
						break;
				case ENGLISH:
					Printf24("Invalid",x,y,front_color,1,back_color); //
						break;
				case PORTUGAL:	//葡萄牙
				// case SPANISH: //西班牙
					Printf24("invá   ",x,y,front_color,1,back_color); //
					Printf24("    li",x,y,front_color,0,back_color); //inválido
					Printf24("      do",x,y,front_color,0,back_color); //
						break;
				case FRENCH:	//法语
					Printf16("NON VALABLE",x,y,front_color,1,back_color); //
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
				case PORTUGAL:	//葡萄牙
				// case SPANISH: //西班牙
					Printf24("eficaz",x,y,front_color,1,back_color); //
						break;
				case FRENCH:	//法语
					Printf24("VALABLE",x,y,front_color,1,back_color); //
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
				case PORTUGAL:	//葡萄牙
					Printf16("Pressione a tecla Insert, a fun??o comuta??o",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,BLACK_COLOR,0,0xffff);
					ASCII_Printf("ca",ASCII16_MODE,8,16,PUTAO_ZK16, REMIND_WINDOW_X+10+(31*8),REMIND_WINDOW_Y+5,BLACK_COLOR,0xffff);
					ASCII_Printf("ca",ASCII16_MODE,8,16,PUTAO_ZK16, REMIND_WINDOW_X+10+(41*8),REMIND_WINDOW_Y+5,BLACK_COLOR,0xffff);
					break;
				case FRENCH:	//法语
					Printf16("APPUYER SUR 'INSERER', FONCTION PRESSE - ARRET",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,BLACK_COLOR,0,0xffff);
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
		else if(MotorType>=MOTOR_AC_SERVO)
			{
			if(Unit==UNIT_MM)//mm  单位
				temp=AC_MotorSPD*100;
			else
				temp=AC_MotorSPD*1000;
			ProgSet_dis(temp,  x,  y,  flag);
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
				case PORTUGAL:	//葡萄牙
					Printf16("Intervalo de dados           --",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,BLACK_COLOR,0,0xffff);
					break;
				case FRENCH:	//法语
					Printf24("VALEUR           -- ",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,BLACK_COLOR,0,0xffff);
					break;
				}
			if((MotorType>=MOTOR_DC_SERVO)&&(MotorType<=MOTOR_DC670_SERVO_ZHU))
				{
				if(MotorType==MOTOR_DC670_SERVO_ZHU)
					Printf24("5     20",REMIND_WINDOW_X+200,REMIND_WINDOW_Y+5,RED_COLOR,0,0xffff);
				else
					Printf24("13     20",REMIND_WINDOW_X+200,REMIND_WINDOW_Y+5,RED_COLOR,0,0xffff);
				}
			else if(MotorType>=MOTOR_AC_SERVO)	
				Printf24("0      20",REMIND_WINDOW_X+200,REMIND_WINDOW_Y+5,RED_COLOR,0,0xffff);
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
				case PORTUGAL:	//葡萄牙
					Printf16("Intervalo de dados           --",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,BLACK_COLOR,0,0xffff);
					break;
				case FRENCH:	//法语
					Printf24("VALEUR           -- ",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,BLACK_COLOR,0,0xffff);
					break;
				}
			Printf24("10     20",REMIND_WINDOW_X+200,REMIND_WINDOW_Y+5,RED_COLOR,0,0xffff);
			}	
		break;	
	}
}

void F2_ToolsPage_dis(void) //参数 画面
{
volatile Int16U x,y,gap,n,tx_wide=148;
Int16U back_color=TEXT_TAB_BACK_COLOR;	//0xef9f;
 x=PARA_START_X1,y=PARA_START_Y,gap=PARA_ROW_GAP;
CurrentArea_save2(MIDDLE_PAGE_X , MIDDLE_PAGE_Y,  M_PAGE_WIDE, M_PAGE_HIGH);
MiddlePage_dis();//中间活页

SubModeIcon_dis(WorkMode);   //参数模式

GLCD_SetWindow_Fill( x, y, x+tx_wide, y+(gap*7-10), TEXT_TAB_BACK_COLOR, TEXT_TAB_BACK_COLOR);//clear text win
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
		GLCD_SetWindow_Fill( x, y, x+tx_wide, y+(gap*4-10), TEXT_TAB_BACK_COLOR, TEXT_TAB_BACK_COLOR);//clear text win
		Printf24("压纸停机:   ",x,y,BLACK_COLOR,1,back_color);y+=gap;
		if((MotorType>=MOTOR_DC_SERVO)&&(MotorType<=MOTOR_DC670_SERVO_ZHU))
			{
			Printf24("最大速度:   ",x,y,BLACK_COLOR,1,back_color);y+=gap;
			Printf24("点动速度:   ",x,y,BLACK_COLOR,1,back_color);
			}
		else if(MotorType>=MOTOR_AC_SERVO)
			{
			Printf24("运行速度:   ",x,y,BLACK_COLOR,1,back_color);y+=gap;
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
		GLCD_SetWindow_Fill( x, y, x+tx_wide, y+(gap*4-10), TEXT_TAB_BACK_COLOR, TEXT_TAB_BACK_COLOR);//clear text win
		Printf24("Press-Stop:",x,y,BLACK_COLOR,1,back_color);y+=gap;
		if((MotorType>=MOTOR_DC_SERVO)&&(MotorType<=MOTOR_DC670_SERVO_ZHU))
			{
			Printf24("Max-speed:",x,y,BLACK_COLOR,1,back_color);y+=gap;
			Printf24("Jog-speed:",x,y,BLACK_COLOR,1,back_color);
			}
		else if(MotorType>=MOTOR_AC_SERVO)
			{
			Printf24("Run-speed:",x,y,BLACK_COLOR,1,back_color);y+=gap;
			}
			break;
	case PORTUGAL:	//葡萄牙
		Printf24("O ex-limite:",x,y,BLACK_COLOR,1,back_color);y+=gap;
		Printf24("Intermedi:",x,y,BLACK_COLOR,1,back_color);y+=gap;
		Printf24("apó        ",x,y,BLACK_COLOR,1,back_color);
		Printf24("   s-limite:",x,y,BLACK_COLOR,0,back_color);y+=gap;
		Printf24("lí    ",x,y,BLACK_COLOR,1,back_color); 
		Printf24("  ngua:",x,y,BLACK_COLOR,0,back_color);  y+=gap;
		Printf24("unidade:",x,y,BLACK_COLOR,1,back_color);  y+=gap;
		Printf24("antes:",x,y,BLACK_COLOR,1,back_color);y+=gap;
		Printf24("distancia:",x,y,BLACK_COLOR,1,back_color);
		x+=PARA_COL_WIDE;y=PARA_START_Y;
		GLCD_SetWindow_Fill( x, y, x+tx_wide, y+(gap*4-10), TEXT_TAB_BACK_COLOR, TEXT_TAB_BACK_COLOR);//clear text win
		Printf24("encerra:",x,y,BLACK_COLOR,1,back_color);y+=gap;
		if((MotorType>=MOTOR_DC_SERVO)&&(MotorType<=MOTOR_DC670_SERVO_ZHU))
			{
			Printf24("Veloci-má  ",x,y,BLACK_COLOR,1,back_color);
			Printf24("          x:",x,y,BLACK_COLOR,0,back_color);y+=gap;
			Printf24("Veloci-Jog:",x,y,BLACK_COLOR,1,back_color);
			}
		else if(MotorType>=MOTOR_AC_SERVO)
			{
			Printf16("Veloci-corrida:",x,y,BLACK_COLOR,1,back_color);y+=gap;
			}
			break;
	
	case FRENCH:	//法语
		Printf24("LIMITE AV:",x,y,BLACK_COLOR,1,back_color);y+=gap;
		Printf16("LIMITE CENTRE:",x,y,BLACK_COLOR,1,back_color);y+=gap;
		Printf24("LIMITE AR:",x,y,BLACK_COLOR,1,back_color);y+=gap;
		Printf24("LANGUE:   ",x,y,BLACK_COLOR,1,back_color);  y+=gap;
		Printf24("UNITE:",x,y,BLACK_COLOR,1,back_color);  y+=gap;
		Printf16("PRE AVANCEMENT",x,y,BLACK_COLOR,1,back_color);y+=gap;
		//Printf24("标准距离:   ",x,y,BLACK_COLOR,1,back_color);
		Printf16("DISTANCE D'EQUERRE:",x,y,BLACK_COLOR,1,back_color);
		x+=PARA_COL_WIDE;y=PARA_START_Y;
		GLCD_SetWindow_Fill( x, y, x+tx_wide, y+(gap*4-10), TEXT_TAB_BACK_COLOR, TEXT_TAB_BACK_COLOR);//clear text win
		Printf24("PRESSE-ARRET:",x,y,BLACK_COLOR,1,back_color);y+=gap;
		if((MotorType>=MOTOR_DC_SERVO)&&(MotorType<=MOTOR_DC670_SERVO_ZHU))
			{
			Printf24("VITESSE MAXI:",x,y,BLACK_COLOR,1,back_color);y+=gap;
			Printf16("VITESSE COUP PAR COUP:",x,y,BLACK_COLOR,1,back_color);
			}
		else if(MotorType>=MOTOR_AC_SERVO)
			{
			Printf16("VITESSE TRAVAIL:",x,y,BLACK_COLOR,1,back_color);y+=gap;
			}
			break;
	}
switch(MotorType)
	{
	case MOTOR_FREQ_5_SPD_RST:
	case MOTOR_FREQ_3_SPD:
	case MOTOR_FREQ_3_SPD_RST:
			for(n=1;n<=7;n++)
				ParameterPage_dis(n, 0);
			break;
	case MOTOR_DC_SERVO:
	case MOTOR_DC670_SERVO:
	case MOTOR_DC670_SERVO_ZHU:
			for(n=1;n<=9;n++)
				ParameterPage_dis(n, 0);
			break;
	case MOTOR_AC_SERVO:	
	case MOTOR_AC_SERVO670:	
			for(n=1;n<=8;n++)
				ParameterPage_dis(n, 0);
			break;
	}		 

ParameterPage_dis(0, 1);
}

void F1_RulerPage_dis(void) //基准 画面
{
CurrentArea_save2(MIDDLE_PAGE_X , MIDDLE_PAGE_Y,  M_PAGE_WIDE, M_PAGE_HIGH);
MiddlePage_dis();//中间活页

SubModeIcon_dis(WorkMode);   //基准模式
	
}

void F3_plus_dis(Int8U flag)	//F3++
{
if(flag==1)
	{
	Printf24("++",SIZE_WINDOW_X,SIZE_WINDOW_Y,RED_COLOR,1,0xffff);
	GLCD_SetWindow_Fill( REMIND_WINDOW_X, REMIND_WINDOW_Y, REMIND_WINDOW_X+REMIND_LENGTH, REMIND_WINDOW_Y+30, 0xfffff, 0xffff);//提示框
	switch(Language)
		{
		case CHN_HAN:
				Printf24("再按F3++,退出",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,BLACK_COLOR,0,0xffff);
						break;
		case ENGLISH:	
				Printf24("Press F3++ to exit",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,BLACK_COLOR,0,0xffff);
						break;
		// // case INDONSIA:	//印尼	
				// // Printf24("Tekan F3++ untuk keluar",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,BLACK_COLOR,0,0xffff);
						// // break;
		case PORTUGAL:	//葡萄牙
				Printf24("imprensa F3++,desistir",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,BLACK_COLOR,0,0xffff);
						break;
		// // case SPANISH: //西班牙
				// // Printf24("prensa F3++,dejar de",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,BLACK_COLOR,0,0xffff);
						// // break;
		case FRENCH:	//法语
				Printf16("APPUYER SUR F3++ POUR QUITTER",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,BLACK_COLOR,0,0xffff);
						break;
		}
	//.........................解释 框
	ModeName_dis(WorkMode);	
	}
else
	{
	Printf24("++",SIZE_WINDOW_X,SIZE_WINDOW_Y,0xffff,1,0xffff);
	PromptNum_dis();//输入范围
	PromptDis_flag=1;
	//.........................解释 框
	ModeName_dis(WorkMode);	
	}
}
void F4_minus_dis(Int8U flag)	//F4--
{
if(flag==1)
	{
	Printf24("--",SIZE_WINDOW_X,SIZE_WINDOW_Y,RED_COLOR,1,0xffff);
	GLCD_SetWindow_Fill( REMIND_WINDOW_X, REMIND_WINDOW_Y, REMIND_WINDOW_X+REMIND_LENGTH, REMIND_WINDOW_Y+30, 0xfffff, 0xffff);//提示框
	switch(Language)
		{
		case CHN_HAN:
				Printf24("再按F4--,退出",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,BLACK_COLOR,0,0xffff);
						break;
		case ENGLISH:	
				Printf24("Press F4-- to exit",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,BLACK_COLOR,0,0xffff);
						break;
		// // case INDONSIA:	//印尼	
				// // Printf24("Tekan F4-- untuk keluar",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,BLACK_COLOR,0,0xffff);
						// // break;
		case PORTUGAL:	//葡萄牙
				Printf24("imprensa F4--,desistir",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,BLACK_COLOR,0,0xffff);
						break;
		// // case SPANISH: //西班牙
				// // Printf24("prensa F4--,dejar de",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,BLACK_COLOR,0,0xffff);
						// // break;
		case FRENCH:	//法语
				Printf16("APPUYER SUR F4-- POUR QUITTER",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,BLACK_COLOR,0,0xffff);
						break;
		}
	//.........................解释 框
	ModeName_dis(WorkMode);	
	}
else
	{
	Printf24("--",SIZE_WINDOW_X,SIZE_WINDOW_Y,0xffff,1,0xffff);
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
	front_color=TEXT_TAB_BACK_COLOR;
	back_color=BLACK_COLOR;
	}
else
	{
	front_color=BLACK_COLOR;
	back_color=TEXT_TAB_BACK_COLOR;
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
				case PORTUGAL:	//葡萄牙
					Printf16("Intervalo de dados           --",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,BLACK_COLOR,0,0xffff);
					break;
				case FRENCH:	//法语
					Printf24("VALEUR           	--",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,BLACK_COLOR,0,0xffff);
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
				case PORTUGAL:	//葡萄牙
					Printf16("Intervalo de dados           --",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,BLACK_COLOR,0,0xffff);
					break;
				case FRENCH:	//法语
					Printf24("VALEUR           	--",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,BLACK_COLOR,0,0xffff);
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
				case PORTUGAL:	//葡萄牙
					Printf16("Intervalo de dados           --",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,BLACK_COLOR,0,0xffff);
					break;
				case FRENCH:	//法语
					Printf24("VALEUR           	--",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,BLACK_COLOR,0,0xffff);
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
				case PORTUGAL:	//葡萄牙
					Printf16("Intervalo de dados           --",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,BLACK_COLOR,0,0xffff);
					break;
				case FRENCH:	//法语
					Printf24("VALEUR           	--",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,BLACK_COLOR,0,0xffff);
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
				case PORTUGAL:	//葡萄牙
					Printf16("Intervalo de dados           --",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,BLACK_COLOR,0,0xffff);
					break;
				case FRENCH:	//法语
					Printf24("VALEUR           	--",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,BLACK_COLOR,0,0xffff);
					break;
				}
			Printf24("0      59",REMIND_WINDOW_X+200,REMIND_WINDOW_Y+5,RED_COLOR,0,0xffff);
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
	case PORTUGAL:	//葡萄牙
		Printf24("ano:   20",x,y,BLACK_COLOR,0,0xffff);y+=gap;
		Printf24("mê ",x,y,BLACK_COLOR,0,0xffff);
		Printf24("  s:",x,y,BLACK_COLOR,0,0xffff);y+=gap;//mês
		Printf24("dia:",x,y,BLACK_COLOR,0,0xffff);y+=gap;
		Printf24("tempo:",x,y,BLACK_COLOR,0,0xffff);y+=gap;
		Printf24("minuto:",x,y,BLACK_COLOR,0,0xffff);
			break;
	case FRENCH:	//法语
		Printf24("ANNEE:  20",x,y,BLACK_COLOR,0,0xffff);y+=gap;
		Printf24("MOIS:",x,y,BLACK_COLOR,0,0xffff);y+=gap;
		Printf24("JOUR:",x,y,BLACK_COLOR,0,0xffff);y+=gap;
		Printf24("HEURE:",x,y,BLACK_COLOR,0,0xffff);y+=gap;
		Printf24("MINUTE:",x,y,BLACK_COLOR,0,0xffff);
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
		Printf16("脉冲当量  编码器分辨率  丝杆螺距",x,y,0xFc00,0,0xffff);
			break;
	case ENGLISH:	
		Printf16("Pulse-Equ  Resolution   Distance",x,y,0xFc00,0,0xffff);
			break;
	case PORTUGAL:	//葡萄牙	
		Printf16("Pulso-Equ  resolu??o    passo",x,y,0xFc00,0,0xffff);
		ASCII_Printf("ca",ASCII16_MODE,8,16,PUTAO_ZK16, x+8*17,y,0xFc00,0xffff);
			break;
	case FRENCH:	//法语
		Printf16("IMPULSION-EQU RESOLUTION  PAS-DE-VIS",x,y,0xFc00,0,0xffff);
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
	case PORTUGAL:	//葡萄牙	
		Printf16("Pulso-Equ  resolu??o    passo",x,y,0xFc00,0,0xffff);
		ASCII_Printf("ca",ASCII16_MODE,8,16,PUTAO_ZK16, x+8*17,y,0xFc00,0xffff);
			break;
	case FRENCH:	//法语
		Printf16("IMPULSION-EQU RESOLUTION  PAS-DE-VIS",x,y,0xFc00,0,0xffff);
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
	case PORTUGAL:	//葡萄牙
		Printf24("Entrada de pulso equivalente!",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,BLACK_COLOR,0,0xffff);
			break;
	case FRENCH:	//法语
		Printf24("SAISIR IMPULSION EQUIVALENT!",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,BLACK_COLOR,0,0xffff);
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
	front_color=TEXT_TAB_BACK_COLOR;
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
CurrentArea_save2(x , y,  SELF_PROMP_WIDE, SELF_PROMP_HIGH);
GLCD_SetWindow_Fill( x, y, x+SELF_PROMP_WIDE-1, y+SELF_PROMP_HIGH-1, BLUE_COLOR, 0xfffff);x+=10,y+=5;
GLCD_SetWindow(SELF_OK_X,SELF_OK_Y,SELF_OK_X+SELF_OK_WIDE, SELF_OK_Y+SELF_OK_HIGH, 0x0);//确定 按钮
GLCD_SetWindow(SELF_CANCEL_X,SELF_CANCEL_Y,SELF_CANCEL_X+SELF_OK_WIDE, SELF_CANCEL_Y+SELF_OK_HIGH, 0x0);//取消 按钮
switch(Language)
	{
	case CHN_HAN:
		Printf24("自刀模式高度危险,请",x,y,front_color,1,back_color);y+=30;
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
	case PORTUGAL:	//葡萄牙
		Printf16("Este modo é muito perigoso",x,y,front_color,1,back_color);y+=30;
		Printf16("Pressione o bot?o OK para entrar",x,y,front_color,1,back_color);
		ASCII_Printf("a",ASCII16_MODE,8,16,PUTAO_ZK16, x+8*15,y,front_color,back_color);x+=20,y+=50;
		Printf24("OK",x,y,front_color,1,back_color);x+=130;
		Printf24("Cancelar",x,y,front_color,1,back_color);
			break;
	case FRENCH:	//法语
		Printf16("ATTENTION MODE COUPE AUTO,",x,y,front_color,1,back_color);y+=30;
		Printf16("APPUYER 'CONFIRMER ' POUR ACCEDER!",x,y,front_color,1,back_color);x+=20,y+=50;
		Printf24("CONFIRMER",x,y,front_color,1,back_color);x+=150;
		Printf24("ANNULER",x,y,front_color,1,back_color);
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
	case PORTUGAL:	//葡萄牙
		Printf24("Se continuar a opera??o",x,y,front_color,1,back_color);
		ASCII_Printf("ca",ASCII24_MODE,12,24,PUTAO_ZK24, x+12*20,y,front_color,back_color);y+=30;
		Printf24("anterior?",x,y,front_color,1,back_color);x+=20,y+=50;
		Printf24("OK",x,y,front_color,1,back_color);x+=130;
		Printf24("Cancelar",x,y,front_color,1,back_color);
			break;
	case FRENCH:	//法语
		Printf24("VOULEZ-VOUS CONTINUER?",x,y,front_color,1,back_color);y+=30;
		Printf24("CONFIRMER",x,y,front_color,1,back_color);x+=150;
		Printf24("ANNULER",x,y,front_color,1,back_color);
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
	front_color=TEXT_TAB_BACK_COLOR;
	back_color=BLACK_COLOR;
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
				case PORTUGAL:	//葡萄牙
					Printf16("Intervalo de dados           --",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,BLACK_COLOR,0,0xffff);
					break;
				case FRENCH:	//法语
					Printf24("VALEUR            -- ",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,BLACK_COLOR,0,0xffff);
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
				case PORTUGAL:	//葡萄牙
					Printf16("Intervalo de dados           --",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,BLACK_COLOR,0,0xffff);
					break;
				case FRENCH:	//法语
					Printf24("VALEUR            -- ",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,BLACK_COLOR,0,0xffff);
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
				case PORTUGAL:	//葡萄牙
					Printf16("Intervalo de dados           --",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,BLACK_COLOR,0,0xffff);
					break;
				case FRENCH:	//法语
					Printf24("VALEUR            -- ",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,BLACK_COLOR,0,0xffff);
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
				case PORTUGAL:	//葡萄牙
					Printf16("Intervalo de dados           --",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,BLACK_COLOR,0,0xffff);
					break;
				case FRENCH:	//法语
					Printf24("VALEUR            -- ",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,BLACK_COLOR,0,0xffff);
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
				case PORTUGAL:	//葡萄牙
					Printf16("Intervalo de dados           --",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,BLACK_COLOR,0,0xffff);
					break;
				case FRENCH:	//法语
					Printf24("VALEUR            -- ",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,BLACK_COLOR,0,0xffff);
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
				case PORTUGAL:	//葡萄牙
					Printf16("Intervalo de dados           --",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,BLACK_COLOR,0,0xffff);
					break;
				case FRENCH:	//法语
					Printf24("VALEUR            -- ",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,BLACK_COLOR,0,0xffff);
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
				case PORTUGAL:	//葡萄牙
					Printf16("Intervalo de dados           --",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,BLACK_COLOR,0,0xffff);
					break;
				case FRENCH:	//法语
					Printf24("VALEUR            -- ",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,BLACK_COLOR,0,0xffff);
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
				case PORTUGAL:	//葡萄牙
					Printf24("Input data (            )",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,BLACK_COLOR,0,0xffff);
					break;
				case FRENCH:	//法语	
					Printf24("SELECTIONNER(            )",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,BLACK_COLOR,0,0xffff);
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
	case FRENCH:	//法语	
		Printf24("GAIN POSITION:",x,y,BLACK_COLOR,1,back_color);y+=gap;
		Printf16("DIFFERENTIEL POSITION:",x,y,BLACK_COLOR,1,back_color);y+=gap;
		Printf16("INTEGRATION POSITION:",x,y,BLACK_COLOR,1,back_color);y+=gap;
		Printf24("GAIN VITESSE:",x,y,BLACK_COLOR,1,back_color);y+=gap;
		Printf16("DIFFERENTIEL VITESSE:",x,y,BLACK_COLOR,1,back_color);y+=gap;
		Printf16("INTEGRATION VITESSE:",x,y,BLACK_COLOR,1,back_color);y+=gap;
		
		Printf16("RATIO REDUCTION VITESSE:",x,y,BLACK_COLOR,1,back_color);
		x+=PARA_COL_WIDE;y=PARA_START_Y;
		Printf24("PAS DE VIS:",x,y,BLACK_COLOR,1,back_color);
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

GLCD_SetWindow_Fill( REMIND_WINDOW_X, REMIND_WINDOW_Y, REMIND_WINDOW_X+REMIND_LENGTH, REMIND_WINDOW_Y+30, 0xfffff, 0xffff);//提示框
switch(Language)
	{
	case CHN_HAN:
		Printf24("请输入密码!",REMIND_WINDOW_X,REMIND_WINDOW_Y+5,RED_COLOR,0,0xffff);
			break;
	case ENGLISH:	
		Printf24("Enter passcode!",REMIND_WINDOW_X,REMIND_WINDOW_Y+5,RED_COLOR,0,0xffff);
			break;
	case PORTUGAL:	//葡萄牙
		Printf24("Por favor, digite uma senha",REMIND_WINDOW_X,REMIND_WINDOW_Y+5,RED_COLOR,0,0xffff);
			break;
	case FRENCH:	//法语
		Printf24("ENTRER MOT DE PASSE!",REMIND_WINDOW_X,REMIND_WINDOW_Y+5,RED_COLOR,0,0xffff);
			break;
	}
	
//Printf24(")",REMIND_WINDOW_X+240,REMIND_WINDOW_Y+5,RED_COLOR,0,0xffff);	
}
void PassSet_dis(void) //密码 设置界面
{
Int16U x,y,gap;
// x=80,y=200,gap=80;
x=PASS_TIME1_X,y=PASS_TIME1_Y,gap=PASS_TIME_GAP;
PsswordFunPic_dis(LOCK_KEY_X, LOCK_KEY_Y); //密码功能模式pic
switch(Language)
	{
	case CHN_HAN:
		Printf24("第一次关机天数:",x,y,BLACK_COLOR,0,0xffff);y+=gap;
			break;
	case ENGLISH:	
		Printf24("First valid days:",x,y,BLACK_COLOR,0,0xffff);y+=gap;
			break;
	case PORTUGAL:	//葡萄牙
		Printf24("O nú                     ",x,y,BLACK_COLOR,0,0xffff);
		Printf24("    mero de dias eficaz 1:",x,y,BLACK_COLOR,0,0xffff);y+=gap; //número
			break;
	case FRENCH:	//法语	
		Printf24("NOMBRE JOURS ARRET 1ER FOIS:",x,y,BLACK_COLOR,0,0xffff);y+=gap;
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
	case PORTUGAL:	//葡萄牙
		Printf24("O nú                     ",x,y,BLACK_COLOR,0,0xffff);
		Printf24("    mero de dias eficaz 2:",x,y,BLACK_COLOR,0,0xffff);y+=gap;
			break;
	case FRENCH:	//法语
		Printf24("NOMBRE JOURS ARRET 2EME FOIS:",x,y,BLACK_COLOR,0,0xffff);y+=gap;
			break;
	}
PassDaysSet_dis( 1, 0);
PassDaysSet_dis( 0, 1);
}

void PassDaysSet_dis(Int8U sel,Int8U flag)//天数设定
{
volatile Int16U x,y,gap;
Int16U front_color,back_color;
// gap=80;x=150;
gap=PASS_TIME_GAP;x=PASS_TIME1_X+20;
if(flag==1)
    {
	front_color=TEXT_TAB_BACK_COLOR;
	back_color=BLACK_COLOR;
	}
else
	{
	front_color=BLACK_COLOR;
	back_color=TEXT_TAB_BACK_COLOR;
	}
// y=230+gap*sel;
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
				case PORTUGAL:	//葡萄牙
					Printf16("Os dados de entrada, pressione a tecla Insert",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,BLACK_COLOR,0,0xffff);
						break;
				case FRENCH:	//法语
					Printf16("ENTRER NOMBRE JOUR ET CONFIRMER!",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,BLACK_COLOR,0,0xffff);
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
					Printf24("(Valid)  ",x,y,front_color,1,back_color); 
						break;
				case PORTUGAL:	//葡萄牙 
				// case SPANISH: //西班牙
					Printf24("(eficaz)",x,y,front_color,1,back_color); 
						break; 
				case FRENCH:	//法语
					Printf24("(VALABLE)  ",x,y,front_color,1,back_color); 
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
				case PORTUGAL:	//葡萄牙
				// case SPANISH: //西班牙
					Printf24("(invá    ",x,y,front_color,1,back_color); //inválido
					Printf24("     lido)",x,y,front_color,0,back_color); //inválido
						break; 
				case FRENCH:	//法语
					Printf24("(NON VALABLE)",x,y,front_color,1,back_color); 
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
				case PORTUGAL:	//葡萄牙
					Printf16("Os dados de entrada, pressione a tecla Insert",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,BLACK_COLOR,0,0xffff);
						break;
				case FRENCH:	//法语
					Printf16("ENTRER NOMBRE JOUR ET CONFIRMER",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,BLACK_COLOR,0,0xffff);
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
				case PORTUGAL:	//葡萄牙 
				// case SPANISH: //西班牙
					Printf24("(eficaz)",x,y,front_color,1,back_color); 
						break; 
				case FRENCH:	//法语
					Printf24("(VALABLE)  ",x,y,front_color,1,back_color); 
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
				case PORTUGAL:	//葡萄牙
				// case SPANISH: //西班牙
					Printf24("(invá    ",x,y,front_color,1,back_color); //inválido
					Printf24("     lido)",x,y,front_color,0,back_color); //inválido
						break;   
				case FRENCH:	//法语
					Printf24("(NON VALABLE)",x,y,front_color,1,back_color); 
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

// TimeCol_dis(TIME_COL_X,TIME_COL_Y);//时间条

Schedule_dis(SCHEDULE_X,SCHEDULE_Y);//进度
ProgressBar_dis(OnePro_head.pro_knifeSUM,Knife_order);  //进度条 显示
xp=PROG_X,yp=PROG_Y;
switch(Language)
	{
	case CHN_HAN:
		Printf24(" 程序  ",xp,yp,BLACK_COLOR,1,back_color);
			break;
	case ENGLISH:	
		Printf24("Process",xp,yp,BLACK_COLOR,1,back_color);
			break;	
	case PORTUGAL:	//葡萄牙
	// case SPANISH: //西班牙
		Printf24("Programa",xp,yp,BLACK_COLOR,1,back_color);
			break;	 
	case FRENCH:	//法语
		Printf16("PROGRAMME",xp,yp,BLACK_COLOR,1,back_color);
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
	case PORTUGAL:	//葡萄牙
		Printf24("Passo",xp,yp,BLACK_COLOR,1,back_color);
			break;	 
	case FRENCH:	//法语
		Printf16("PROCEDURE",xp,yp,BLACK_COLOR,1,back_color);
			break;	
	}
OneProNum_dis(Pro_data.pro_num, OnePro_head);// 程序号
StepNum_dis(OnePro_head.pro_knifeSUM,Knife_order);// 步骤号  总刀数-序号

// Order_dis(ORDER_X,ORDER_Y);//序号
// Position_dis(POSITION_X,POSITION_Y);//位置
// PushKnife_dis(PUSH_KNIFE_X,PUSH_KNIFE_Y);//推纸——刀

// PushPaperTool_dis(PUSH_PAPER_TOOL_X,PUSH_PAPER_TOOL_Y);//推纸器
CurrentSize_dis(CurrentSize); //当前尺寸 更新显示
CurrUint_dis(Unit);  //当前尺寸 单位

// FrontKnife_dis(FRONT_KNIFE_X,FRONT_KNIFE_Y);//刀前
/*
RightArrow_dis(RIGHT_ARROW_X,RIGHT_ARROW_Y);//右箭头

RedKnifeF_dis(RED_KNIFE_X,RED_KNIFE_Y); yp=RED_KNIFE_Y+30; //红刀

*/
Knife_Up_dis(KNIFE_X,KNIFE_Y);//刀上
Press_Up_dis(PRESS_X,PRESS_Y);//压上

// Red_A_dis(RED_A_X,RED_A_Y);//红A
// Red_B_dis(RED_B_X,RED_B_Y);//红B
Hand_IR_dis(HAND_IR_X,HAND_IR_Y);//手红外
// // ElectricalWheel_dis();  //电子手轮  开关状态

// FrontPage_Up_dis( FRONT_PAGE_X,  FRONT_PAGE_Y);//前进up
// BackPage_Up_dis( BACK_PAGE_X,  BACK_PAGE_Y);//后退up
// UpArrow_Up_dis( UP_ARROW_X,  UP_ARROW_Y);//上箭头up
// DownArrow_Up_dis( DOWN_ARROW_X,  DOWN_ARROW_Y);//下箭头up

//主模式 ---
MainModeIcon_dis(WorkMode);//编程模式..............

// InputSize_dis(INPUT_SIZE_X,INPUT_SIZE_Y);//输入尺寸
// Remind_dis(REMIND_X,REMIND_Y); //提示栏
TextWindow_dis();   //白色文本框

//Cancel_Up_dis(CANCEL_X,CANCEL_Y);//取消up
//Enter_Up_dis(ENTER_X,ENTER_Y);//确定up
//Run_Up_dis(RUN_X,RUN_Y);//运行up
//Stop_Up_dis(STOP_X,STOP_Y);//停止up

// // Delete_Up_dis( DELETE_X, DELETE_Y );//删除up
// // DeleteAll_Up_dis( DELETE_ALL_X, DELETE_ALL_Y);//全删up
// Fkey_Up_dis( F_KEY_X, F_KEY_Y);//F键up

// Program_dis(PROGRAM_X,PROGRAM_Y);   //编程
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
			case PORTUGAL:	//葡萄牙	
				Printf16("Pressione fun??o 'F' para parar",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,BLACK_COLOR,0,0xffff);
				ASCII_Printf("ca",ASCII16_MODE,8,16,PUTAO_ZK16, REMIND_WINDOW_X+(14*8),REMIND_WINDOW_Y+5,BLACK_COLOR,0xffff);
					break;	 
			case FRENCH:	//法语
				Printf16("APPUYER 'F' POUR ARRETER!",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,BLACK_COLOR,0,0xffff);
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
		case PORTUGAL:	//葡萄牙
			Printf16("Intervalo de dados           --",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,BLACK_COLOR,0,0xffff);
				break;
		case FRENCH:	//法语
			Printf24("VALEUR           	--",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,BLACK_COLOR,0,0xffff);
			break;
		}

	x=REMIND_WINDOW_X+180,y=REMIND_WINDOW_Y+5;
	Printf24(str1,x,y,RED_COLOR,0,0xffff);
	Printf24(str2,x+100,y,RED_COLOR,0,0xffff);
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
Int8U start_x=0,start_y=0;
switch(page)
	{
	case 0:
		x=start_x+gap,y=start_y+gap;
		gap1=50,gap2=110;
		F1LabelIconUp_dis(x,y);//F1
		x+=gap1;
		Printf24("标签",x,y+20,BLACK_COLOR,0,0xffff);

		x+=gap2;
		F2DivideIconUp_dis(x,y);
		x+=gap1;
		Printf24("等分",x,y+20,BLACK_COLOR,0,0xffff);

		x+=gap2;
		F3ProjectIconUp_dis(x,y);
		x+=gap1;
		Printf24("程序",x,y+20,BLACK_COLOR,0,0xffff);

		x+=gap2;
		F4PushIconUp_dis(x,y);
		x+=gap1;
		Printf24("推纸功能",x,y+20,BLACK_COLOR,0,0xffff);

		x+=gap2;
		F1OkIconUp_dis(x,y);
		x+=gap1;
		Printf24("完成",x,y+20,BLACK_COLOR,0,0xffff);
		
		//*********************第二行
		x=start_x+gap;y+=70;
		gap1=50,gap2=110;
		F1RulerIconUp_dis(x,y);
		x+=gap1;
		Printf24("基准",x,y+20,BLACK_COLOR,0,0xffff);
		
		x+=gap2;
		F2ParamaterIconUp_dis(x,y);
		x+=gap1;
		Printf24("参数",x,y+20,BLACK_COLOR,0,0xffff);
		
		x+=gap2;
		F3ClockIconUp_dis(x,y);
		x+=gap1;
		Printf24("时间",x,y+20,BLACK_COLOR,0,0xffff);
		
		x+=gap2;
		F3AddIconUp_dis(x,y);
		x+=gap1;
		Printf24("自加",x,y+20,BLACK_COLOR,0,0xffff);
		
		x+=gap2;
		F4SubIconUp_dis(x,y);
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
		Printf24("红外断",x,y+20,BLACK_COLOR,0,0xffff);
		
		x+=gap2;
		RedLine_dis(x,y);// FrontKnife_dis(x,y);
		x+=gap1;
		// Printf24("刀前",x,y+20,BLACK_COLOR,0,0xffff);
		Printf24("红外通",x,y+20,BLACK_COLOR,0,0xffff);
		
		x+=gap2;
		RedKnifeF_dis(x,y);
		x+=gap1;
		Printf24("刀标志",x,y+20,BLACK_COLOR,0,0xffff);
		
		//*********************第五行
		x=start_x+gap;y+=70;
		gap1=50,gap2=110;
		// Red_A_dis(x,y);
		F5CutIcon_Up_dis(x,y);
		x+=gap1;
		// Printf24("A信号",x,y+20,BLACK_COLOR,0,0xffff);
		Printf24("F5刀标记",x,y+20,BLACK_COLOR,0,0xffff);
		
		x+=gap2;
		// Red_B_dis(x,y);
		F0CutAllIcon_Up_dis(x,y);
		x+=gap1;
		// Printf24("B信号",x,y+20,BLACK_COLOR,0,0xffff);
		Printf24("F0全标记",x,y+20,BLACK_COLOR,0,0xffff);
		
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
		// PulseDegree_dis(x,y);
		F4LabelDesert_Up_dis(x,y);
		x+=gap1;
		Printf24("标签废边",x,y+5,BLACK_COLOR,0,0xffff);
		
		//*********************第七行
		x=start_x+gap;y+=50;
		gap1=90,gap2=80;
		// // Wheel0_dis(x,y);
		F3LabelTime_Up_dis(x,y);
		x+=gap1;
		Printf24("标签次数",x,y+5,BLACK_COLOR,0,0xffff);
		/*
		Printf24("编程",x,y+35,BLACK_COLOR,0,0xffff);

		x+=gap2;
		Label_dis(x,y);
		x+=gap1;
		Printf24("标签",x,y+35,BLACK_COLOR,0,0xffff);

		x+=gap2;//*********************第六行
		x=start_x+gap;y+=80;
		Parameter_dis(x,y);
		x+=gap1;
		Printf24("参数",x,y+35,BLACK_COLOR,0,0xffff);

		//*********************第四行
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

		//*********************第五行
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

		//*********************第六行
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
		// Program_dis(x,y);
		RightArrow_dis(x,y);
		x+=gap1;
		Printf24("光标",x,y+35,BLACK_COLOR,0,0xffff);

		
		/****
		
		x+=gap2;
		// // Label_dis(x,y);
		x+=gap1;
		Printf24("标签模式",x,y+35,BLACK_COLOR,0,0xffff);

		x+=gap2;
		// Parameter_dis(x,y);
		x+=gap1;
		Printf24("参数模式",x,y+35,BLACK_COLOR,0,0xffff);

		//*********************第三行
		x=start_x+gap;y+=80;
		// // Divide_dis(x,y);
		x+=gap1;
		Printf24("等分模式",x,y+35,BLACK_COLOR,0,0xffff);

		x+=gap2;
		// // Teach_dis(x,y);
		x+=gap1;
		Printf24("示教模式",x,y+35,BLACK_COLOR,0,0xffff);

		x+=gap2;
		// // Watch_dis(x,y);
		x+=gap1;
		Printf24("时间模式",x,y+35,BLACK_COLOR,0,0xffff);

		//*********************第四行
		x=start_x+gap;y+=80;
		// // Ruler_dis(x,y);
		x+=gap1;
		Printf24("基准模式",x,y+35,BLACK_COLOR,0,0xffff);

		x+=gap2;
		// // Auto_dis(x,y);
		x+=gap1;
		Printf24("自动模式",x,y+35,BLACK_COLOR,0,0xffff);

		x+=gap2;
		// // Manual_dis(x,y);
		x+=gap1;
		Printf24("手动模式",x,y+35,BLACK_COLOR,0,0xffff);

		//*********************第五行
		x=start_x+gap;y+=80;
		// // AutoKnife_dis(x,y);
		x+=gap1;
		Printf24("自刀模式",x,y+35,BLACK_COLOR,0,0xffff);

		x+=gap2;
		// // SelectPro_dis(x,y);
		x+=gap1;
		Printf24("选择程序",x,y+35,BLACK_COLOR,0,0xffff);

		x+=gap2;
		// // Lock_dis(x,y);
		x+=gap1;
		Printf24("密码模式",x,y+35,BLACK_COLOR,0,0xffff);		
		
		//*********************第六行
		x=start_x+gap;y+=80;
		gap1=90,gap2=80;
		// // Wheel1_dis(x,y);
		x+=gap1;
		Printf24("手轮开",x,y+5,BLACK_COLOR,0,0xffff);

		**/
		
		
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

x=CURR_SIZE_X;
y=CURR_SIZE_Y;
back_color=CURREN_STEP_BACK_COLOR;
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
// Printf32(num,x,y,0,1,back_color);
//ASCII_Printf(num,224+1,28,56,ASCII_28x56, x,y,0xffff,back_color);
//ASCII_Printf(num,192+1,32,48,ASCII_32x48, x,y,0,back_color);
// ASCII_Printf(num,64+1,16,32,ASCII_bold16x32, x,y,0,back_color);
ASCII_Printf(num,120+1,24,40,ASCII_bold24x40, x,y,0,back_color);

}


void FrontKnifeUint_dis(Int8U unit)  //刀前尺寸 单位--------------
{
Int16U x,y,back_color=CURREN_UNIT_BACK_COLOR;
x=FRONT_KNIF_X+200;
y=35;//FRONT_KNIF_Y+5;
GLCD_SetWindow_Fill(x, y, x+40, y+25, back_color, back_color);
if(unit==UNIT_MM)//mm
   {
   Printf24("mm",x,y,WHITE_COLOR,1,back_color);
   }
else
   {
   Printf24("in",x,y,WHITE_COLOR,1,back_color);
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
Printf24(num,x,y,BLACK_COLOR,1,back_color);
// ASCII_Printf(num,108+1,20,36,ASCII_20x36, x,y,0,back_color);
}
void FrontKnifeSize_NOdis(void)
{
Int16U x,y,back_color=FRONT_KNIFE_BACK_COLOR;
x=FRONT_KNIF_X;
y=FRONT_KNIF_Y;
GLCD_SetWindow_Fill(x-1, y, x+100, y+25, back_color, back_color);
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

////////////////////////
void CursorPro_dis(Int8U row, Int8U show_flag)// 程序号 蓝色箭头 光标
{
Int16U x,y,back_color=TEXT_TAB_BACK_COLOR;//0xef9f;
if(row<PROGS_1PAGE)
   {
   TableDis_startcol=RIGHT_ARROW_X;
   }
else
   {
   TableDis_startcol=RIGHT_PAGE_X;
   }
x=TableDis_startcol;
y=RIGHT_ARROW_Y+(row%PROGS_1PAGE)*PROTEXT_HIGH+10;
if(show_flag==1)//显示
   {
   RightArrow_dis(x,y);
   }
else
   {
   GLCD_SetWindow_Fill( x, y, x+32, y+32, back_color, back_color);//消失
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
   TableDis_startcol=RIGHT_PAGE_X+25;	//xxxxxxxxxxxx
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
Printf32(num,x,y,num_color,1,back_color);//序号
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
   TableDis_startcol=RIGHT_PAGE_X+25;	//xxxxxxxxxxxx
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
x2=PROC_STEP_X-80;
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
	Printf24(pName,x,y,num_color,1,back_color);//显示名称
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
   TableDis_startcol=RIGHT_PAGE_X+25;	//xxxxxxxxxxxx
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
Printf32(num,x,y,num_color,1,back_color);//
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
   TableDis_startcol=RIGHT_PAGE_X+25;	//xxxxxxxxxxxx
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
Printf32(num,x,y,num_color,1,back_color);//
}



void CursorKnife_dis(Int8U row, Int8U show_flag)// 刀数据 蓝色箭头 光标
{
Int16U x,y,back_color=TEXT_TAB_BACK_COLOR;
if(row>(PAGE_KNIFE-1))
   {
   TableDis_startcol=RIGHT_PAGE_X;
   }
else
   {
   TableDis_startcol=RIGHT_ARROW_X;
   }
x=TableDis_startcol;
// y=RIGHT_ARROW_Y+15+(row%PAGE_KNIFE)*SIZETEXT_HIGH;
y=RIGHT_ARROW_Y+(row%PAGE_KNIFE)*SIZETEXT_HIGH;
if(show_flag==1)//显示
   {
   RightArrow_dis(x,y);
   }
else
   {
   // GLCD_SetWindow_Fill( x, y, x+15, y+15, back_color, back_color);//消失
   GLCD_SetWindow_Fill( x, y, x+32, y+SIZEWORD_HIGH, back_color, back_color);//消失
   }
}


void KnifeOrder_dis(Int16U row, Int16U order,Int16U num_color)//-----------------------显示一个序号
{
Int8U num[5],k;
Int16U x,y,back_color=TEXT_TAB_BACK_COLOR;
if(row>(PAGE_KNIFE-1))
   {
   TableDis_startcol=RIGHT_PAGE_X;
   }
else
   {
   TableDis_startcol=RIGHT_ARROW_X;
   }
x=TableDis_startcol+ARROW_WIDE;
y=RIGHT_ARROW_Y+(row%PAGE_KNIFE)*SIZETEXT_HIGH;

num[0]=order/100;
num[1]=(order/10)%10;
num[2]=order%10;
num[3]=0;
for(k=0;k<3;k++)
  {
  num[k]+=48;
  }
//Printf32(num,x,y,num_color,1,back_color);//序号
//===============
if(num_color==RED_COLOR)
	{
	back_color=TEXT_TAB_FRONT_COLOR;
	num_color=0;
	}
else
	{
	GLCD_SetWindow_Fill( x, y, x+100, y+SIZEWORD_HIGH, TEXT_TAB_BACK_COLOR, TEXT_TAB_BACK_COLOR);
	}
// ASCII_Printf(num,114+1,18,38,ASCII_bold18x38, x,y,num_color,back_color);
ASCII_Printf(num,64+1,16,32,ASCII_bold16x32, x,y,num_color,back_color);
}

void KnifeSize_dis(Int16U row,  Int32U Knife_size,Int16U num_color)//--------------显示一个尺寸
{
Int8U num[8],k;
Int16U x,y,back_color=TEXT_TAB_BACK_COLOR;
Int32U size_inc;
if(row>(PAGE_KNIFE-1))
   {
   TableDis_startcol=RIGHT_PAGE_X;
   }
else
   {
   TableDis_startcol=RIGHT_ARROW_X;
   }  
x=TableDis_startcol+120;//95;
y=RIGHT_ARROW_Y+(row%PAGE_KNIFE)*SIZETEXT_HIGH;

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

// Printf32(num,x,y,BLACK_COLOR,1,back_color);//尺寸显示
// ASCII_Printf(num,120+1,24,40,ASCII_bold24x40, x,y,num_color,back_color);
ASCII_Printf(num,64+1,16,32,ASCII_bold16x32, x,y,num_color,back_color);
}

void PushFlag_dis(Int8U row,  Int8U Knife_flag)//-------一个 推纸 标志显示
{
Int16U x,y,back_color=TEXT_TAB_BACK_COLOR;
x=RED_KNIFE_X;
y=RIGHT_ARROW_Y+10+row*SIZETEXT_HIGH;
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
Int16U x,y,back_color=TEXT_TAB_BACK_COLOR;
GetOneKnife_datas(Pro_data.pro_num, knife , (pInt8U)&Knife_datas);//取出一刀 数据
//===============
if(row>(PAGE_KNIFE-1))
   {
   TableDis_startcol=RIGHT_PAGE_X;
   }
else
   {
   TableDis_startcol=RIGHT_ARROW_X;
   }
x=TableDis_startcol+ARROW_WIDE;
y=RIGHT_ARROW_Y+(row%PAGE_KNIFE)*SIZETEXT_HIGH;
if(num_color==RED_COLOR)
	back_color=TEXT_TAB_FRONT_COLOR;
GLCD_SetWindow_Fill( x, y, x+100, y+SIZEWORD_HIGH, back_color, back_color);
//===============
KnifeOrder_dis(row, knife,num_color);//序号
//-----------------步骤(尺寸)错误 判断 
if((Knife_datas.size<Size_MIN_num)||(Knife_datas.size>Size_MAX_num))
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
	}
if(knife>OnePro_head.pro_knifeSUM)	//最后一个步骤 之后仍有数据 则清除
	{
	if(Knife_datas.size>0)
		{
		Knife_datas.size=0;
		Knife_datas.k_flag=0;
		}
	}	
KnifeSize_dis(row,  Knife_datas.size, num_color);//--------------显示一个尺寸
// // if(num_color==RED_COLOR)
	// // F5Button_dis(Knife_datas.k_flag);  //F5 一个 刀 标记 按钮
return Knife_datas.k_flag;
}

void OneProNum_dis(Int16U pro_order, PROCESS_HEAD pro_head) //程序号码显示
{
Int16U x,y,back_color=0x2E3B,line_color;
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
Printf24(num,x,y,BLACK_COLOR,1,back_color);//程序
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
Int16U x,y,back_color=0x2E3B;
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
back_color=STEP_BACK_COLOR;//----------
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
			ProgressBar_dis(OnePro_head.pro_knifeSUM,Knife_order);  //进度条 显示
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
	RLOUT1_ON;    // 允许裁切断开
else
	{
	if(PressDown_flag == 0)// 压纸 未下
		RLOUT1_ON;    // 允许裁切断开
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
	RLOUT1_ON;    // 允许裁切断开
else
	{
	if(PressDown_flag == 0)// 压纸 未下
		RLOUT1_ON;    // 允许裁切断开
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
			RLOUT1_OFF;    // 允许裁切	
			}
		break;
	case MOTOR_FREQ_3_SPD: //----3 档速	
	case MOTOR_FREQ_3_SPD_RST: //----3 档速+复位
		if(Wheel_limit==0)
			{
			RLOUT3_ON;  //   刹车断开
			RLOUT1_OFF;    // 允许裁切	
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
				// OOUT3_OFF;
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
Int32U temp,temp2;
if(TargetSize>=CurrentSize)
	{  
	temp2=Size_MAX-CurrentSize;
	if(temp2>=5000)//未达到 后极限
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
		}
	else //后极限  50mm处 低速
		{
		if(MoveSpeed!=4)
			{
			MoveSpeed=4;//低速
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
x=200,y=100;gap=40;
switch(motor)
	{
	case MOTOR_FREQ_5_SPD_RST://五档速带复位
		switch(Language)
			{
			case CHN_HAN:
				Printf24("1------五档速带复位",x,y,F_color,1,B_color);
				break;
			case ENGLISH:
			case PORTUGAL:	//葡萄牙
			case FRENCH:	//法语	
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
			case PORTUGAL:	//葡萄牙
			case FRENCH:	//法语	
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
			case PORTUGAL:	//葡萄牙
			case FRENCH:	//法语	
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
			case PORTUGAL:	//葡萄牙
			case FRENCH:	//法语	
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
			case PORTUGAL:	//葡萄牙
			case FRENCH:	//法语	
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
			case PORTUGAL:	//葡萄牙
			case FRENCH:	//法语	
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
			case PORTUGAL:	//葡萄牙
			case FRENCH:	//法语	
				Printf24("7------AC servo",x,y,F_color,1,B_color);
				break;
			}
		break;		
	case MOTOR_AC_SERVO670:	 		//交流伺服	670
		y+=gap*7;
		switch(Language)
			{
			case CHN_HAN:
				Printf24("8------交流伺服670",x,y,F_color,1,B_color);
				break;
			case ENGLISH:
			case PORTUGAL:	//葡萄牙
			case FRENCH:	//法语	
				Printf24("8------AC servo 670",x,y,F_color,1,B_color);
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
GLCD_SetWindow_Fill( SIZE_WINDOW_X, SIZE_WINDOW_Y, SIZE_WINDOW_X+SIZE_WINDOW_WIDE, SIZE_WINDOW_Y+SIZE_WINDOW_HIGH, 0xfffff, 0xffff);//尺寸输入
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
				case PORTUGAL:	//葡萄牙
						Printf24(" INSE",x,y,num_color,0,0xffff);
						break;
				case FRENCH:	//法语	
						Printf24("INSERER",x,y,num_color,0,0xffff);
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
				case PORTUGAL:	//葡萄牙
						Printf24(" EXIT",x,y,num_color,0,0xffff);
						break;
				case FRENCH:	//法语	
						Printf24("QUITTER",x,y,num_color,0,0xffff);
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
				case PORTUGAL:	//葡萄牙
				case FRENCH:	//法语
						Printf24(" OK",x,y,num_color,0,0xffff);
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
				case PORTUGAL:	//葡萄牙
						Printf24(" RUN",x,y,num_color,0,0xffff);
						break;
				case FRENCH:	//法语
						Printf24("EXECUT",x,y,num_color,0,0xffff);
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
	case PORTUGAL:	//葡萄牙
	case FRENCH:	//法语
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
	ratio=now*100/total;
	x1=SCHEDULE_DOT_X,x2=x1+12;
	if(1)//(ratio!=ProcessRatio)
		{
		if(ProcessRatio!=0xff)    //不是 开始
			{/*
			color=0xf78a;
			y1=SCHEDULE_DOT_Y+ProcessRatio;
			y2=y1+12;
			GLCD_SetWindow_Fill(x1,y1, x2,y2 ,color,color);//清除 进度块
			*/
			color=TEXT_TAB_BACK_COLOR;
			y1=SCHEDULE_DOT_Y+ProcessRatio;
			y2=y1+25;
			GLCD_SetWindow_Fill(x1,y1, x2,y2 ,color,color);//清除 进度块
			// DrawLine( SCHEDULE_DOT_X+5, y1, SCHEDULE_DOT_X+5, y2, 0);
			color=0x0193;
			GLCD_SetWindow_Fill(SCHEDULE_DOT_X+5, y1, SCHEDULE_DOT_X+5+2, y2, color,color);
			}
		//**************
		ProcessRatio=ratio;
		color=0x0193;
		y1=SCHEDULE_DOT_Y+ProcessRatio;
		y2=y1+25;
		GLCD_SetWindow_Fill(x1,y1, x2,y2 ,color,color);//更新 进度块
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


