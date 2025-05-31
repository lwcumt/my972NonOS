


#ifndef _PIC_EXEC_H
#define _PIC_EXEC_H

#include"main.h"
#include "file.h"


//----------- 区块背景颜色------------
#define TEXT_TAB_BACK_COLOR		0xE71C
#define TEXT_TAB_FRONT_COLOR	0xFFE6//YELLOW_COLOR
#define CURREN_STEP_BACK_COLOR	0xCF5D	//当前size背景色
#define CURREN_UNIT_BACK_COLOR	0x3AB0	//当前单位背景色
#define FRONT_KNIFE_BACK_COLOR	CURREN_STEP_BACK_COLOR
#define STEP_BACK_COLOR		  CURREN_STEP_BACK_COLOR//
#define WIN_DOWN_BACK_COLOR		0xCE79//底部背景色

#define F1_4_WIDE	48
#define F1_4_HIGH	48

#define F_KEY_WIDE	35//56
#define F_KEY_HIGH	35//46

#define FORWARD_WIDE	F1_4_WIDE
#define FORWARD_HIGH	F1_4_HIGH

#define DELETE_WIDE		50
#define DELETE_HIGH		25
//-------计算器 弹出框
#define CALCUL_WIN_X	325//320
#define CALCUL_WIN_Y	105
#define CALCUL_WIDE		472//412
#define CALCUL_HIGH		336//280
#define CALCUL_COLOR	0x879e

#define CALCUL_TEXT_X	(CALCUL_WIN_X+5)
#define CALCUL_TEXT_Y	(CALCUL_WIN_Y+5)
#define CALCUL_TEXT_H	30
#define CALCUL_TEXT_W	450//390
#define CALCUL_TEXT_END	(CALCUL_TEXT_X+CALCUL_TEXT_W-12)

#define CALCUL_RESULT_X	(CALCUL_TEXT_X+160)
#define CALCUL_RESULT_Y	(CALCUL_TEXT_Y+CALCUL_TEXT_H+5)
#define CALCUL_RESULT_H	30
#define CALCUL_RESULT_W	275//225
//
#define BUTT_WIDE	75//65
#define BUTT_HIGH	60//55//45
#define BUTT_GAP1	5
#define BUTT_GAP2	5
#define BUTT_X1		(CALCUL_WIN_X+5)
#define BUTT_X2		(BUTT_X1+BUTT_WIDE+BUTT_GAP1)
#define BUTT_X3		(BUTT_X2+BUTT_WIDE+BUTT_GAP1)
#define BUTT_X4		(BUTT_X3+BUTT_WIDE+BUTT_GAP1)
#define BUTT_X5		(BUTT_X4+BUTT_WIDE+BUTT_GAP1)
#define BUTT_X6		(BUTT_X5+BUTT_WIDE+BUTT_GAP1)


#define BUTT_Y1		(CALCUL_RESULT_Y+30+5)
#define BUTT_Y2		(BUTT_Y1+BUTT_HIGH+BUTT_GAP2)
#define BUTT_Y3		(BUTT_Y2+BUTT_HIGH+BUTT_GAP2)
#define BUTT_Y4		(BUTT_Y3+BUTT_HIGH+BUTT_GAP2)
#define BUTT_Y5		(BUTT_Y4+BUTT_HIGH+BUTT_GAP2)
//方向箭头
#define BUTT_WIDE_ARROW	60//50
#define BUTT_HIGH_ARROW	125//95

//--------软键盘 按钮编码定义
#define BUTT_INSERT	0
#define BUTT_EXIT	1
#define BUTT_EQU	2
#define BUTT_ENTER	3
#define BUTT_RUN	4
#define BUTT_CLEAR	5
#define BUTT_DOT	6
#define BUTT_MUL	7
#define BUTT_DIV	8
#define BUTT_PLUS	9
#define BUTT_0	10
#define BUTT_1	11
#define BUTT_2	12
#define BUTT_3	13
#define BUTT_4	14
#define BUTT_5	15
#define BUTT_6	16
#define BUTT_7	17
#define BUTT_8	18
#define BUTT_9	19
#define BUTT_SUB	20
#define BUTT_UP		21
#define BUTT_DOWN	22

// #define BUTT_SPAC	23
#define BUTT_LEFT	23
#define BUTT_RIGHT	24



//------------文件缓存地址--------
#define  PIC_DIS_SAVE1		(DOWNFILE_SDRAM_ADD+0x200000)//0xa0400000    //当前显示区块 暂存区1
#define  PIC_DIS_SAVE2		(PIC_DIS_SAVE1+0x100000)//0xa047d000    //当前显示区块 暂存区2
#define  PIC_DIS_SAVE3		(PIC_DIS_SAVE2+0x100000)//0xa0500000    //当前显示区块 暂存区3
#define  PIC_DIS_SAVE4		(PIC_DIS_SAVE3+0x100000)//0xa057d000    //当前显示区块 暂存区4


#define  df_zk_sdram        (PIC_DIS_SAVE4+0x100000)//0xa0600000             //字库2M

#define  START_PIC_sdram   (df_zk_sdram+0x200000)  //0xa0600000         //开机图片


#define  WOEK_BACK_dis     (START_PIC_sdram+1152100)        //工作背景

//------------------子模式图片
#define	 FUN_PIC_SIZE	190800
#define  LABEL_FUN_sdram	(WOEK_BACK_dis+1152100)//标签功能
#define  PROCESS_sdram		(LABEL_FUN_sdram+FUN_PIC_SIZE) //程序
#define  TOOLS_sdram		(PROCESS_sdram+FUN_PIC_SIZE) //工具
#define  DIVIDE_FUN_sdram	(TOOLS_sdram+FUN_PIC_SIZE) //等分功能
#define  RULER_FUN_sdram		(DIVIDE_FUN_sdram+FUN_PIC_SIZE) //基准功能
#define  CALENDAR_sdram		(RULER_FUN_sdram+FUN_PIC_SIZE) //日历
#define  LOCK_KEY_sdram		(CALENDAR_sdram+FUN_PIC_SIZE) //锁 钥匙
//***********************************F1,2,3,4...
#define	 F1_PIC_SIZE		6970
#define  F1_LABELS_UP_sdram			(LOCK_KEY_sdram+FUN_PIC_SIZE)//F1up
#define  F2_DIVIDE_UP_sdram			(F1_LABELS_UP_sdram+F1_PIC_SIZE)//F1up
#define  F3_SELECT_PRO_UP_sdram			(F2_DIVIDE_UP_sdram+F1_PIC_SIZE)//F1up
#define  F4_PUSH_UP_sdram			(F3_SELECT_PRO_UP_sdram+F1_PIC_SIZE)//F1up
#define  F1_FINISHED_sdram		(F4_PUSH_UP_sdram+F1_PIC_SIZE)//完成
#define  F2_OUT_UP_sdram	(F1_FINISHED_sdram+F1_PIC_SIZE) //F2退出up
#define  L_R_ARROW_sdram	(F2_OUT_UP_sdram+F1_PIC_SIZE)//左右箭头

#define  F1_RULER_UP_sdram	(L_R_ARROW_sdram+F1_PIC_SIZE)//F1尺子up
#define  F2_TOOLS_UP_sdram	(F1_RULER_UP_sdram+F1_PIC_SIZE)//F2工具up
#define  F3_PLUS_UP_sdram	(F2_TOOLS_UP_sdram+F1_PIC_SIZE)//F3++up
#define  F3_CLOCK_UP_sdram	(F3_PLUS_UP_sdram+F1_PIC_SIZE)//F3时钟up
#define  F4_MINUS_UP_sdram	(F3_CLOCK_UP_sdram+F1_PIC_SIZE)//F4--up
#define  F5_CUT_UP_sdram	(F4_MINUS_UP_sdram+F1_PIC_SIZE)//F5刀
#define  F0_ALLCUT_UP_sdram	(F5_CUT_UP_sdram+F1_PIC_SIZE)//F0刀
#define  F5_PRE_FLG_BUTT_UP_sdram (F0_ALLCUT_UP_sdram+F1_PIC_SIZE)//压纸 循环button
// #define  TEACH_MOD_sdram	(F5_CUT_UP_sdram+F1_PIC_SIZE)//示教模式
// #define  AUTO_KNIFE_MOD_sdram	(TEACH_MOD_sdram+12100)//自刀模式
//程序选择
#define  F1_LOOK_UP_sdram		(F5_PRE_FLG_BUTT_UP_sdram+F1_PIC_SIZE)//F1查看 程序信息up
#define  F2_BY_TIME_UP_sdram	(F1_LOOK_UP_sdram+F1_PIC_SIZE)//F2 按时间 显示up
#define  F2_BY_TIME_DOWN_sdram	(F2_BY_TIME_UP_sdram+F1_PIC_SIZE)//F2 按时间 显示down
#define  F3_BY_NUM_UP_sdram		(F2_BY_TIME_DOWN_sdram+F1_PIC_SIZE)//F3 按序号 显示up
#define  F3_BY_NUM_DOWN_sdram	(F3_BY_NUM_UP_sdram+F1_PIC_SIZE)//F3 按序号 显示down
#define  F4_DELETE_ONE_PRO_UP_sdram	(F3_BY_NUM_DOWN_sdram+F1_PIC_SIZE)//F4删除一个pro
#define  F5_DELETE_ALL_PRO_UP_sdram	(F4_DELETE_ONE_PRO_UP_sdram+F1_PIC_SIZE)//F5删除所有pro
//程序信息
#define	 F1_PINYIN_UP_sdram		(F5_DELETE_ALL_PRO_UP_sdram+F1_PIC_SIZE)//拼音输入up
#define	 F1_PINYIN_DOWN_sdram		(F1_PINYIN_UP_sdram+F1_PIC_SIZE)//拼音输入down
#define	 F2_CHAR_UP_sdram		(F1_PINYIN_DOWN_sdram+F1_PIC_SIZE)//字母输入up
#define	 F2_CHAR_DOWN_sdram		(F2_CHAR_UP_sdram+F1_PIC_SIZE)//字母输入down
#define	 F3_NUM_UP_sdram		(F2_CHAR_DOWN_sdram+F1_PIC_SIZE)//数字输入up
#define	 F3_NUM_DOWN_sdram		(F3_NUM_UP_sdram+F1_PIC_SIZE)//数字输入down
#define  F4_EXIT_UP_sdram		(F3_NUM_DOWN_sdram+F1_PIC_SIZE)//F4退出up
#define	 F6_EXIT_BUTT_sdram		(F4_EXIT_UP_sdram+F1_PIC_SIZE) //F6退出 按钮
#define	 ENTER_BUTT_sdram		(F6_EXIT_BUTT_sdram+F1_PIC_SIZE) //确定 按钮

#define  KNIFE_UP_sdram		(ENTER_BUTT_sdram+F1_PIC_SIZE)//刀上
#define  KNIFE_DOWN_sdram	(KNIFE_UP_sdram+1954)//刀下
#define  PRESS_UP_sdram		(KNIFE_DOWN_sdram+1954)//压上
#define  PRESS_DOWN_sdram	(PRESS_UP_sdram+1954)//压下
#define  RED_LINE_sdram		(PRESS_DOWN_sdram+1954)   //红线
#define  HAND_IR_sdram		(RED_LINE_sdram+1954) //手 红外

#define  FRONT_PAGE_UP_sdram	(HAND_IR_sdram+1954)//前进
#define  BACK_PAGE_UP_sdram		(FRONT_PAGE_UP_sdram+F1_PIC_SIZE)//后退up
#define  UP_ARROW_UP_sdram		(BACK_PAGE_UP_sdram+F1_PIC_SIZE)//上箭头up
#define  DOWN_ARROW_UP_sdram		(UP_ARROW_UP_sdram+F1_PIC_SIZE)//下箭头up
#define  FAST_FORWD_UP_sdram	(DOWN_ARROW_UP_sdram+F1_PIC_SIZE)	//快进up
#define  FAST_BACK_UP_sdram		(FAST_FORWD_UP_sdram+F1_PIC_SIZE) 	//快退up


#define	 F4_WHEEL0_sdram		(FAST_BACK_UP_sdram+F1_PIC_SIZE) //电子手轮开关0
#define	 F4_WHEEL1_sdram		(F4_WHEEL0_sdram+F1_PIC_SIZE) //电子手轮开关1

#define	 F4_PULSE_UP_sdram		(F4_WHEEL1_sdram+F1_PIC_SIZE)	//F4脉冲当量

#define  LABEL_DESERT_F4_UP_sdram	(F4_PULSE_UP_sdram+F1_PIC_SIZE)
#define  LABEL_DESERT_F4_DOWN_sdram	(LABEL_DESERT_F4_UP_sdram+F1_PIC_SIZE)
#define  LABEL_TIME_F3_UP_sdram		(LABEL_DESERT_F4_DOWN_sdram+F1_PIC_SIZE)//标签次数
#define  LABEL_TIME_F3_DOWN_sdram	(LABEL_TIME_F3_UP_sdram+F1_PIC_SIZE)//标签次数

// #define  FRONT_KNIFE_sdram	(F4_WHEEL1_sdram+F1_PIC_SIZE)//刀前
#define  RED_KNIFE_F_sdram	(LABEL_TIME_F3_DOWN_sdram+F1_PIC_SIZE)//(FRONT_KNIFE_sdram+3050)//红刀
#define	 PRE_AUTO_F_sdram		(RED_KNIFE_F_sdram+1200)//k 自动循环---------------------------------
#define  PUSH_PAPER_F_sdram (PRE_AUTO_F_sdram+1256)//推纸
#define  SCHEDULE_sdram		(PUSH_PAPER_F_sdram+1785)//进度
#define  SCHEDULE_DOT_sdram	(SCHEDULE_sdram+16700)//进度位置
#define  RIGHT_ARROW_sdram	(SCHEDULE_DOT_sdram+600)// 右箭头 -->
#define  TIME_COL_sdram		(RIGHT_ARROW_sdram+720) //时间条
#define  PUSH_PAPER_TOOL_sdram	(TIME_COL_sdram+75910) //推纸器

#define  CANCEL_UP_sdram  	(PUSH_PAPER_TOOL_sdram+98648) //取消up
#define  CANCEL_DOWN_sdram  (CANCEL_UP_sdram+7750) //取消down
#define  ENTER_UP_sdram		(CANCEL_DOWN_sdram+7750)//确定up
#define  ENTER_DOWN_sdram	(ENTER_UP_sdram+7750)//确定down
#define  STOP_UP_sdram		(ENTER_DOWN_sdram+7750)//停止up
#define  STOP_DOWN_sdram	(STOP_UP_sdram+7750)//停止down
#define  RUN_UP_sdram		(STOP_DOWN_sdram+7750)//运行up
#define  RUN_DOWN_sdram		(RUN_UP_sdram+7750)//运行down

#define  INPUT_SIZE_sdram	(RUN_DOWN_sdram+7750) //输入尺寸
#define  REMIND_sdram		(INPUT_SIZE_sdram+9900)//提示栏

#define  PUSH_KNIFE_sdram	(REMIND_sdram+9900) //推纸/刀
#define  POSITION_sdram		(PUSH_KNIFE_sdram+5700)//位置
#define  ORDER_sdram		(POSITION_sdram+5700)  //序号

#define  MIDDLE_PAGE_sdram	(ORDER_sdram+5700)//中间活页
#define  LEFT_PAGE_sdram	(MIDDLE_PAGE_sdram+693656)// 左边活页

#define  DELETE_UP_sdram		(LEFT_PAGE_sdram+693656)//删除up
#define  DELETE_ALL_UP_sdram	(DELETE_UP_sdram+8000)//全删up
#define  PEAR_sdram			(DELETE_ALL_UP_sdram+8000)//鸭梨

#define  F_KEY_UP_sdram		(PEAR_sdram+86940) //F键up

// #define  WHEEL0_sdram		(F4_WHEEL1_sdram+F1_PIC_SIZE)//手轮关0
// #define  WHEEL1_sdram		(WHEEL0_sdram+12345)//手轮开1
// #define  test_sdram		(WHEEL1_sdram+12345)//手轮开1

// #define  F0_YESALLCUT_sdram		(WHEEL1_sdram+12345)//F0 all刀标记+
// #define  F0_NOALLCUT_sdram		(F0_YESALLCUT_sdram+7750)//F0 all刀标记-
// #define  F5_YESCUT_sdram	(F0_NOALLCUT_sdram+7750)//F5 刀标记+
// #define  F5_NOCUT_sdram		(F5_YESCUT_sdram+7750)//F5 刀标记-

#define  CURSOR_sdram		(F_KEY_UP_sdram+4785)		//光标
#define  RUN_BIG_BUTT_UP_sdram		(CURSOR_sdram+3128)	//运行big
#define  STOP_BIG_BUTT_UP_sdram		(RUN_BIG_BUTT_UP_sdram+7256)	//停止big
// #define  UP_ARROW_PRO_sdram		(STOP_BIG_BUTT_UP_sdram+7256)	//up pro
// #define  DOWN_ARROW_PRO_sdram		(UP_ARROW_PRO_sdram+2816)	//down pro

//++++++++++++++english
#define  LABEL_FUN_EN_sdram	(STOP_BIG_BUTT_UP_sdram+7256)//标签功能

#define  DIVIDE_FUN_EN_sdram	(LABEL_FUN_EN_sdram+FUN_PIC_SIZE) //等分功能
#define  RULER_FUN_EN_sdram		(DIVIDE_FUN_EN_sdram+FUN_PIC_SIZE) //基准功能
//---------------------------------
#define  K_SIZE_sdram		(RULER_FUN_EN_sdram+FUN_PIC_SIZE)//0x82000000       //刀数据 缓存区


//**************图片显示位置定义*******
//右箭头-->
#define  SIZETEXT_HIGH	45  //尺寸列表 行距
#define  SIZEWORD_HIGH	(32-1)  //尺寸列表 行距
#define  PROTEXT_HIGH	45//35  //程序列表 行距
#define  RIGHT_ARROW_X	45
#define  RIGHT_ARROW_Y	160//190
//列表右边页 起始位置
#define  RIGHT_PAGE_X	400//360  
//进度条
#define  SCHEDULE_X		390//710
#define  SCHEDULE_Y		165
#define  SCHEDULE_WIDE	20
#define  SCHEDULE_HIGH	200//334
//进度块
#define  SCHEDULE_DOT_X	(SCHEDULE_X+4)
#define  SCHEDULE_DOT_Y	(SCHEDULE_Y+35)//143

//模式 解释 框
#define	 MODE_NAME_COLOR	0x1256//深蓝色0x3339
#define  MODE_NAME_X1	350
#define  MODE_NAME_Y1	409
#define  MODE_NAME_X2	(MODE_NAME_X1+250)
#define  MODE_NAME_Y2	(MODE_NAME_Y1+32)


//------------------中间活页---------------------------
#define  MIDDLE_PAGE_X	RIGHT_ARROW_X
#define  MIDDLE_PAGE_Y	140//
//----------------活页大小
#define  M_PAGE_WIDE	750
#define  M_PAGE_HIGH	260//289

//尺寸输入框
#define  SIZE_WINDOW_X	20
#define  SIZE_WINDOW_Y	408
#define  SIZE_WINDOW_WIDE	120
#define  SIZE_WINDOW_HIGH	30
#define  SIGN_2WIDE		24
//提示框
#define  REMIND_WINDOW_X	SIZE_WINDOW_X
#define  REMIND_WINDOW_Y	446
#define  REMIND_LENGTH		450//380  //提示框长度

// #define  RIGHT_PAGE_X	360//380  //右边页 起始位置
//故障提示框大小
#define  START_PROM_WIDE	600
#define  START_PROM_HIGH	30
//开机第一行故障 提示
#define	 START_PROMPT_X1	REMIND_WINDOW_X
#define	 START_PROMPT_Y1	(REMIND_WINDOW_Y-50)
//推纸器复位 提示
#define  PUSH_RESET_PROMPT_X1	200
#define  PUSH_RESET_PROMPT_Y1	50
#define  PUSH_RESET_PROMPT_WIDE	450
#define  PUSH_RESET_PROMPT_HIGH	80
#define  PUSH_RESET_OK_X		(PUSH_RESET_PROMPT_X1+50)
#define  PUSH_RESET_OK_Y		(PUSH_RESET_PROMPT_Y1+50)
#define  PUSH_RESET_CANCEL_X	(PUSH_RESET_OK_X+200)
#define  PUSH_RESET_CANCEL_Y	PUSH_RESET_OK_Y
//鸭梨
#define  PEAR_X		330
#define  PEAR_Y		140



#define  PROG_X		40//程序
#define  PROG_Y		80//80
#define  STEP_X		(PROG_X+165)//步骤
#define  STEP_Y		PROG_Y

#define  PROG_NUM_X		(PROG_X+100)//程序号
#define  PROG_NUM_Y		PROG_Y
#define  STEP_NUM_X		(STEP_X+100)//步骤号
#define  STEP_NUM_Y		PROG_Y

//程序名
#define  PRO_NAME_DIS_COLOR	 CURREN_UNIT_BACK_COLOR//0x3AB0
#define  PRO_NAME_DIS_X		35
#define  PRO_NAME_DIS_Y		35
//******************尺寸显示
//刀前尺寸
#define  FRONT_KNIFE_X	450//470
#define  FRONT_KNIFE_Y	61//65
//当前尺寸 
#define CURR_SIZE_X		480//490 //当前尺寸 显示位置
#define CURR_SIZE_Y		45
#define FRONT_KNIF_X	510//535
#define FRONT_KNIF_Y	95//FRONT_KNIFE_Y
//--------------功能ICON--------------------
//标签功能
#define  LABEL_FUN_X	  	360
#define  LABEL_FUN_Y		152//141
//等分功能
#define  DIVIDE_FUN_X	  	LABEL_FUN_X
#define  DIVIDE_FUN_Y	  	LABEL_FUN_Y
//程序
#define  PROCESS_X	  	LABEL_FUN_X
#define  PROCESS_Y		LABEL_FUN_Y
//工具
#define  TOOLS_X	  	LABEL_FUN_X
#define  TOOLS_Y	  	LABEL_FUN_Y
//基准功能
#define  RULER_FUN_X	  	LABEL_FUN_X
#define  RULER_FUN_Y	  	LABEL_FUN_Y
//日历
#define  CALENDA_X	  	LABEL_FUN_X
#define  CALENDA_Y	  	LABEL_FUN_Y
//锁 钥匙
#define  LOCK_KEY_X		LABEL_FUN_X
#define  LOCK_KEY_Y		LABEL_FUN_Y


//-----F1,F2,F3,...
#define	 ICONBUTT_GAP_V		58

#define  F1LABEL_BUTT_X		705
#define  F1LABEL_BUTT_Y		150  //F1标签按钮
#define  F2DIVIDE_BUTT_X	F1LABEL_BUTT_X
#define  F2DIVIDE_BUTT_Y	(F1LABEL_BUTT_Y+ICONBUTT_GAP_V)  //F2等分按钮
#define  F3PROJECT_BUTT_X	F1LABEL_BUTT_X
#define  F3PROJECT_BUTT_Y	(F2DIVIDE_BUTT_Y+ICONBUTT_GAP_V)  //F3程序按钮
#define  F4PUSHFLAG_BUTT_X		F1LABEL_BUTT_X
#define  F4PUSHFLAG_BUTT_Y		(F3PROJECT_BUTT_Y+ICONBUTT_GAP_V)  //F4切换按钮
// // #define  F5DELETE_BUTT_X		F1LABEL_BUTT_X
// // #define  F5DELETE_BUTT_Y		(F4PUSHFLAG_BUTT_Y+ICONBUTT_GAP_V)  //F5  按钮
// // #define  F6EXIT_BUTT_X		F1LABEL_BUTT_X
// // #define  F6EXIT_BUTT_Y		(F5DELETE_BUTT_Y+ICONBUTT_GAP_V)  //F6
// // #define	 F4_WHEEL_BUTT_X		F1LABEL_BUTT_X  //F4电子手轮  
// // #define	 F4_WHEEL_BUTT_Y		F4PUSHFLAG_BUTT_Y
// // #define	 F5_WHEEL_BUTT_X		F1LABEL_BUTT_X  //F4电子手轮  
// // #define	 F5_WHEEL_BUTT_Y		F5DELETE_BUTT_Y


//F1尺子up
#define  F1_RULER_X	 F1LABEL_BUTT_X
#define  F1_RULER_Y	 F1LABEL_BUTT_Y
//F2工具up
#define  F2_TOOLS_X	 F2DIVIDE_BUTT_X
#define  F2_TOOLS_Y	 F2DIVIDE_BUTT_Y
//F3++up
#define  F3_PLUS_X	 F3PROJECT_BUTT_X
#define  F3_PLUS_Y	 F3PROJECT_BUTT_Y
//F4--up
#define  F4_MINUS_X	 F4PUSHFLAG_BUTT_X
#define  F4_MINUS_Y	 F4PUSHFLAG_BUTT_Y
//F3时钟up
#define  F3_CLOCK_X	 F3PROJECT_BUTT_X
#define  F3_CLOCK_Y	 F3PROJECT_BUTT_Y
 //F4电子手轮  
#define	 F4_WHEEL_BUTT_X		F1LABEL_BUTT_X 
#define	 F4_WHEEL_BUTT_Y		F4PUSHFLAG_BUTT_Y

//---------------------------
//后退up
#define	 BACK_PAGE_X	440
#define	 BACK_PAGE_Y	340
//前进
#define	 FRONT_PAGE_X	(BACK_PAGE_X+60)
#define	 FRONT_PAGE_Y	BACK_PAGE_Y

//F5单刀
#define  F5_CUT_X		(FRONT_PAGE_X+60)//450
#define  F5_CUT_Y		FRONT_PAGE_Y//210

//F0所有刀
#define  F0_ALL_CUT_X	(F5_CUT_X+60)
#define  F0_ALL_CUT_Y	FRONT_PAGE_Y

//刀上
#define  KNIFE_X		150
#define  KNIFE_Y		 408
//刀下
#define  KNIFE_DOWN_X		KNIFE_X
#define  KNIFE_DOWN_Y		KNIFE_Y

//刀上1
#define  KNIFE1_X		(KNIFE_X+30)
#define  KNIFE1_Y		KNIFE_Y
//刀下1
#define  KNIFE1_DOWN_X		KNIFE1_X
#define  KNIFE1_DOWN_Y		KNIFE1_Y
//压上
#define  PRESS_X		(KNIFE1_X+30)
#define  PRESS_Y		KNIFE_Y
//压下
#define  PRESS_DOWN_X		(PRESS_X)
#define  PRESS_DOWN_Y		(PRESS_Y)
//手红外
#define  HAND_IR_X		(PRESS_X+30)
#define  HAND_IR_Y		KNIFE_Y
//红线
#define  RED_LINE_X		HAND_IR_X
#define  RED_LINE_Y		HAND_IR_Y

//F键up
#define  F_KEY_X		(HAND_IR_X+30)
#define  F_KEY_Y		KNIFE_Y


//手动模式下      后退键
#define  MAN_BACK_PAGE_X	100 
#define  MAN_BACK_PAGE_Y	180//200 
//手动模式下       前进
#define  MAN_FRONT_PAGE_X	(MAN_BACK_PAGE_X+120)
#define  MAN_FRONT_PAGE_Y	MAN_BACK_PAGE_Y


//快退
#define	MAN_FAST_BACK_X MAN_BACK_PAGE_X
#define MAN_FAST_BACK_Y (MAN_BACK_PAGE_Y+120)
//快进up
#define	MAN_FAST_FWD_X	MAN_FRONT_PAGE_X
#define	MAN_FAST_FWD_Y	MAN_FAST_BACK_Y


//删除up
#define  DELETE_X		620//630
#define  DELETE_Y		410
//全删up
#define  DELETE_ALL_X	(DELETE_X+80)
#define  DELETE_ALL_Y	DELETE_Y
//运行up
#define  RUN_X		DELETE_X//270
#define  RUN_Y		(DELETE_Y+40)
//停止up
#define  STOP_X		DELETE_ALL_X
#define  STOP_Y		RUN_Y

#define  RUN_BIG_WIDE	60
#define  RUN_BIG_HIGH	40
//运行1up
#define  RUN_BIG_X		620
#define  RUN_BIG_Y		420
//停止1up
#define  STOP_BIG_X		(RUN_BIG_X+90)
#define  STOP_BIG_Y		RUN_BIG_Y

//红刀flag
#define  RED_KNIFE_X	340//350
#define  RED_KNIFE_Y	170
//推纸flag
#define  PUSH_FLAG_X	RED_KNIFE_X
#define  PUSH_FLAG_Y	RED_KNIFE_Y


//--------------------子模式F1,2.....
//完成up
#define  FINISHED_X	  	650
#define  FINISHED_Y		150
//F2退出up
#define  F2OUT_X		FINISHED_X
#define  F2OUT_Y		(FINISHED_Y+58)
//左右箭头
#define  L_R_ARROW_X	FINISHED_X
#define  L_R_ARROW_Y	(F2OUT_Y+58)
//子菜单 向上
#define  SUB_UP_ARROW_X	(FINISHED_X+58)
#define  SUB_UP_ARROW_Y	 F2OUT_Y
//子菜单 向下
#define  SUB_DOWN_ARROW_X	SUB_UP_ARROW_X
#define  SUB_DOWN_ARROW_Y	L_R_ARROW_Y
//子菜单 F3标签次数
#define  F3_LABEL_TIME_X	FINISHED_X
#define  F3_LABEL_TIME_Y	(F2OUT_Y+58)
//子菜单 F4标签废边
#define  F4_LABEL_DESERT_X	FINISHED_X
#define  F4_LABEL_DESERT_Y	(F3_LABEL_TIME_Y+58)






//F3下   F5，F6
#define  F5DELETE_BUTT_X	DELETE_X
#define  F5DELETE_BUTT_Y	DELETE_Y  //F5  按钮
#define  F6EXIT_BUTT_X		DELETE_ALL_X
#define  F6EXIT_BUTT_Y		DELETE_ALL_Y  //F6  按钮
//确定
#define  ENTER_OK_BUTT_X	F6EXIT_BUTT_X
#define  ENTER_OK_BUTT_Y	F6EXIT_BUTT_Y




//--------F1标签页
#define TOTAL_SIZE_X 	220
#define TOTAL_SIZE_Y 	200
#define ROW_GAP1		50
#define ROW_GAP2		60

#define LABEL_SIZE_X 	TOTAL_SIZE_X
#define LABEL_SIZE_Y 	(TOTAL_SIZE_Y+ROW_GAP1)
#define WASTE_SIZE_X 	TOTAL_SIZE_X
#define WASTE_SIZE_Y 	(LABEL_SIZE_Y+ROW_GAP1)
//--------F2等分页
#define DIVIDE_TOTAL_X	220
#define DIVIDE_TOTAL_Y	200
#define DIVIDE_NUM_X	DIVIDE_TOTAL_X//等分数
#define DIVIDE_NUM_Y	(DIVIDE_TOTAL_Y+ROW_GAP2)


//F3 程序列表------ 显示 
#define ARROW_WIDE	32
#define PROC_NUM_X	(RIGHT_ARROW_X+ARROW_WIDE)
#define PROC_NUM_Y	(RIGHT_ARROW_Y+10)
#define PROC_NAME_X	(PROC_NUM_X+60)
#define PROC_NAME_Y	PROC_NUM_Y
#define PROC_STEP_X	(PROC_NAME_X+320)
#define PROC_STEP_Y	PROC_NUM_Y
#define PROC_DATE_X (PROC_STEP_X+70)
#define PROC_DATE_Y	PROC_NUM_Y
// 程序 信息 显示
#define PRO_MESS_COLOR1 0xFF5b
#define PRO_MESS_COLOR2 0xFFff

#define PRO_MESS_X		45//70
#define PRO_MESS_Y		(PROC_NUM_Y-35)
#define PRO_MESS_WIDE	650
#define PRO_MESS_HIGH	270

#define INPUT_NAME_WIN_X	(PRO_MESS_X+330)
#define INPUT_NAME_WIN_Y	(PRO_MESS_Y+40)
#define INPUT_NAME_WIDE		315
#define INPUT_NAME_HIGH		50

#define INPUT_SEL_X		(INPUT_NAME_WIN_X+10)
#define INPUT_SEL_Y		(INPUT_NAME_WIN_Y+INPUT_NAME_HIGH+5)
#define INPUT_SEL_GAP	30
#define INPUT_SEL_ROW	4

#define INPUT_WORD_COL	10
#define INPUT_WORD_GAP	30
#define INPUT_LIB_X		INPUT_SEL_X
#define INPUT_LIB_Y		(INPUT_SEL_Y+INPUT_SEL_GAP*4+5)


//---------输入法 touch键盘key
#define TOUBUTT_WIDE	75//65
#define TOUBUTT_HIGH	58
#define TOUBUTT_GAPX	5
#define TOUBUTT_GAPY	5
#define TOUBUTT_X1		(PRO_MESS_X+5)
#define TOUBUTT_X2		(TOUBUTT_X1+TOUBUTT_WIDE+TOUBUTT_GAPX)
#define TOUBUTT_X3		(TOUBUTT_X2+TOUBUTT_WIDE+TOUBUTT_GAPX)
#define TOUBUTT_X4		(TOUBUTT_X3+TOUBUTT_WIDE+TOUBUTT_GAPX)



#define TOUBUTT_Y1		(PRO_MESS_Y+10)
#define TOUBUTT_Y2		(TOUBUTT_Y1+TOUBUTT_HIGH+TOUBUTT_GAPY)
#define TOUBUTT_Y3		(TOUBUTT_Y2+TOUBUTT_HIGH+TOUBUTT_GAPY)
#define TOUBUTT_Y4		(TOUBUTT_Y3+TOUBUTT_HIGH+TOUBUTT_GAPY)



//-----------F2-参数页
#define PARA_START_X1		60//70
#define PARA_START_X2		220
#define PARA_START_Y		160//150
#define PARA_COL_WIDE		300
#define PARA_ROW_GAP		30
//--
#define PULSE_SET_X1		60
#define PULSE_SET_X2		360
#define PULSE_SET_Y		160//150
//----------F3时钟 数据页
#define CLOCK_DATA_X	120
#define CLOCK_DATA_Y	170//200	
#define CLOCK_GAP_Y		35//PARA_ROW_GAP	


//-----password  时间
#define PASS_TIME1_X	100		//参数位置
#define PASS_TIME1_Y	200
#define PASS_TIME_GAP	100//80
//------passcode 界面
#define PASSCODE_X		100//220
#define PASSCODE_Y		240
#define PASS_HINT_X		(PASSCODE_X+550)
#define PASS_HINT_Y		PASSCODE_Y

#define PASSCODE_INPUT_X	(PASSCODE_X+200)
#define PASSCODE_INPUT_Y	(PASSCODE_Y+50)
//******自刀提示
#define SELF_PROMP_X	100
#define SELF_PROMP_Y	200
#define SELF_PROMP_WIDE 350
#define SELF_PROMP_HIGH 150
//自刀OK
#define SELF_OK_X		(SELF_PROMP_X+20)
#define SELF_OK_Y		(SELF_PROMP_Y+75)
#define SELF_OK_WIDE	130//110
#define SELF_OK_HIGH	40
//自刀 取消
#define SELF_CANCEL_X	(SELF_OK_X+140)
#define SELF_CANCEL_Y	SELF_OK_Y
//--开机 run 提示
#define RUN_DIS_X		400//550
#define RUN_DIS_Y		REMIND_WINDOW_Y


//-----------start jog  开机 Jog运行
#define START_JOG_WIDE		130
#define START_JOG_HIGH		50

#define START_JOG_BACK_X	650
#define START_JOG_BACK_Y	400

#define START_JOG_FORW_X	(START_JOG_BACK_X+80)
#define START_JOG_FORW_Y	START_JOG_BACK_Y


//----删除全部 提示框
#define DEL_ALL_WIN_X	420
#define DEL_ALL_WIN_Y	250
#define DEL_ALL_WIN_WIDE	300
#define DEL_ALL_WIN_HIGH	100
//delete all 提示
#define DEL_ALL_HINT_X	(DEL_ALL_WIN_X+10)
#define DEL_ALL_HINT_Y	(DEL_ALL_WIN_Y+10)
//删除 ok
#define DEL_ALL_OK_X	(DEL_ALL_WIN_X+50)
#define DEL_ALL_OK_Y	(DEL_ALL_HINT_Y+40)
//删除 cancel
#define DEL_ALL_CANCEL_X	(DEL_ALL_OK_X+120)
#define DEL_ALL_CANCEL_Y	DEL_ALL_OK_Y



//模式-----------------------
#define PROG_MODE		0x10//编程模式
#define AUTO_MODE		0x20//
#define MANUAL_MODE		0x30
#define TEACH_MODE		0x40
#define SELF_CUT_MODE	0x50
#define HELP_MODE		0x60


//编程子模式
#define PROG_LABEL_MODE		0x11//标签
#define PROG_DIVIDE_MODE	0x12//等分
#define PROG_PRO_MODE		0x13//程序选择
#define PROG_PRO_MESS_MODE	0x131//程序 信息
#define PROG_DEL_ALL_PRO_MODE	0x132//	删除所有pro
#define PROG_DEL_ALL_SIZE_MODE	0x133//	删除所有尺寸

#define PROG_FLAG_MODE		0x14//标记 模式
//自动子模式
#define AUTO_RULER_MODE  0x21//基准
#define AUTO_TOOLS_MODE  0x22 //参数
#define AUTO_PLUS_MODE   0x23//F3++
#define AUTO_MINUS_MODE  0x24//F4--
#define AUTO_TO_SELF_MODE 0x25
//手动子模式
#define MANUAL_RULER_MODE  0x31//基准
#define MANUAL_TOOLS_MODE  0x32//
#define MANUAL_CLOCK_MODE  0x33
#define MANUAL_PULSE_MODE  0x34//设定脉冲当量
#define MANUAL_PASS_MODE   0x35//密码
#define MANUAL_SERVO_C_MODE   0x36//直流伺服 C 参数
//示教子模式
#define TEACH_LABEL_MODE	0x41//标签
#define TEACH_DIVIDE_MODE	0x42//等分
#define TEACH_PRO_MODE		0x43//程序选择
#define TEACH_PRO_MESS_MODE	0x431//程序 信息
#define TEACH_DEL_ALL_PRO_MODE	0x432//	删除所有pro
#define TEACH_DEL_ALL_SIZE_MODE	0x433//	删除所有尺寸

#define TEACH_FLAG_MODE		0x44//标记 模式
//自刀子模式
#define SELF_RULER_MODE  0x51//基准
#define SELF_TOOLS_MODE  0x52 //参数
#define SELF_PLUS_MODE   0x53//F3++
#define SELF_MINUS_MODE  0x54//F4--

//单位
#define UNIT_MM		0//公
#define UNIT_MIL	1//英
//语言
#define CHN_HAN    0
#define ENGLISH    1
#define PORTUGAL   2
#define FRENCH   3
#define SPANISH	   4
#define INDONSIA	   5
//极限
#define FRONT_LIM_MIN		(15*100)
#define FRONT_LIM_MAX		(80*100)
//#define FRONT_LIM_MIN_in	(590)
//#define FRONT_LIM_MAX_in	(3149)

#define MIDD_LIM_MIN		(30*100)
#define MIDD_LIM_MAX		(150*100)
//#define MIDD_LIM_MIN_in		(1181)
//#define MIDD_LIM_MAX_in		(5905)

#define BACK_LIM_MIN		(600*100)
#define BACK_LIM_MAX		(2200*100)
//#define BACK_LIM_MIN_in		(23622)
//#define BACK_LIM_MAX_in		(86614)
#define AUTO_PUSH_DISTAN	(500*100)
#define AUTO_PUSH_NO		(10*100)

#define MARGIN_SIZE		45//25
#define DC_VIRTURE_SIZE 1500

//---------------------触摸 十字
#define TOUCH_X1	40
#define TOUCH_Y1	40

#define TOUCH_X2	TOUCH_X1
#define TOUCH_Y2	440

#define TOUCH_X3	760
#define TOUCH_Y3	TOUCH_Y2

#define TOUCH_X4	TOUCH_X3
#define TOUCH_Y4	TOUCH_Y1

#define TOUCH_X_MID	(C_GLCD_H_SIZE>>1)
#define TOUCH_Y_MID	(C_GLCD_V_SIZE>>1)

//---计算器 text
#define CAL_INPUT	0  //数字输入框
#define CAL_RESULT	1   //结果框


//-----------主板控制类型
#define  MOTOR_FREQ_5_SPD_RST	0  //变频器 5挡速+复位
#define  MOTOR_FREQ_3_SPD		1  //变频器 3挡速
#define  MOTOR_FREQ_3_SPD_RST	2  //变频器 3挡速+复位
#define	 MOTOR_DC_SERVO	 		3//直流伺服
#define	 MOTOR_DC670_SERVO	 	4//直流伺服670
#define	 MOTOR_DC670_SERVO_ZHU	5//直流伺服670zhu
#define	 MOTOR_AC_SERVO	 		6//交流伺服
#define	 MOTOR_AC_SERVO670 		7//交流伺服670
//刀数
#define MAIX_KNIFE1		999  //总刀数1-999
#define MAIX_KNIFE2		399  //总刀数1-399

#define PRO_HEAD_BYTES    100
//每个程序长度
#define PROG_BYTES1		((MAIX_KNIFE1*5)+PRO_HEAD_BYTES)//MAIX_KNIFE1 刀数据 +2byte刀数
#define PROG_BYTES2		((MAIX_KNIFE2*5)+PRO_HEAD_BYTES)

#define PROG_GROPU1		300  //前300个程序
#define MAIX_PROG		500//共500个程序

//*************************************************


#define	PAGE_KNIFE	5		//每页刀数
// #define	PAGE2_KNIFE	(PAGE_KNIFE*2)		//2页刀数
#define	PROGS_1PAGE	5		//每页 程序
//*****************************************

//------*********标识符 预定义
#define NO_FLAG		0
#define PUSH_FLAG   1   //推纸 标志位定义
#define KNIFE_FLAG  2   //刀  标志位定义
#define PRE_AUTO_FLAG 3	//k自动循环

//----输入法 定义
#define NUMBER_INPUT	0
#define CHAR_INPUT		1
#define PINYIN_INPUT	2
//*****************************************
#define NAME_BYTE	90

//---程序列表 顺序
#define PRO_BY_NUM	0//按序号
#define PRO_BY_TIME	1//按时间

typedef struct
{
Int8U pro_name_flag[5];
Int8U pro_name[NAME_BYTE];//程序名90B
Int8U pro_year;	//调用时间
Int8U pro_month;//调用时间
Int8U pro_day;	//调用时间
Int16U pro_knifeSUM;//刀数
} PROCESS_HEAD;		//程序头格式(100B)

typedef struct 
{
Int32U size;
Int8U  k_flag;
} KNIFE_DATA;
typedef struct
{
Int16U year;
Int16U month;
Int16U day;
} START_DAY;


extern PROCESS_HEAD OnePro_head;//
extern PROCESS_HEAD Pro_head_temp;//
extern KNIFE_DATA OneKnife_data;
extern START_DAY Start_days;
extern const PROCESS_HEAD ProHead_default;

extern const pInt8U NAME_flag;

typedef struct
{
Int16U pro_num;//程序号
Int16U pro_sum;//程序总数
//Int8U step_num;// 
//Int8U seg_sum;// 
} PROG_SEG;    //程序 段 参数

extern Int16U cursor_row;////光标 位置(行)
extern Int16U  TableDis_startcol;//起始列

extern Int16U ProNumGroup[MAIX_PROG+2];
extern Int16U prog_order;


extern Int16U Knife_order;//当前刀号
extern Int16U Knife_sum_before;//总刀数  校正
extern Int16U MAIX_Knife;//最多刀数

//extern Int16U Process_num;//当前程序 号
//extern Int16U MaixProcess_num;//最大 程序号
extern PROG_SEG Pro_data;//程序 段 号


extern unsigned char PorgSet_sel;

//extern unsigned char cursor_temp;
extern unsigned short WorkMode;

extern unsigned char BeforeKnifeNo_flag;

extern Int32U CurrentSize;
extern Int32U BeforeKnifeSize;
extern Int32U BeforeKnife_offset;
extern Int32U BeforeKnife_offset_in;
extern Int32U OriginalSize;//原点
extern Int32U CurrentSize_temp;

extern Int8U Unit;//单位
extern Int8U Language;//语言
extern Int8U PressValid_flag;//

extern Int32U FrontLimit;
extern Int32U MiddleLimit;
extern Int32U BackLimit;
extern Int32U Aheader;
extern Int32U StanDistance;
extern Int8U Pulse_degree;
extern Int8U PassModeIn_flag;
extern Int8U PassModeOk_flag;

extern Int32U Size_MIN;
extern Int32U Size_MAX;
extern Int32U Size_MIN_num;
extern Int32U Size_MAX_num;
extern Int32U FirstDays;
extern Int32U SecondDays;
extern Int32U AutoPushDistance;

extern Int8U FirstDayValid_flag;
extern Int8U SecondDayValid_flag;

extern Int8U PassCodeEn_flag;
//extern Int8U SelfCutEnter_flag;
extern Int32U TargetSize;
extern Int32U TargetSize_temp;
extern Int32U TargetSize_inch;

extern Int8U Forward_flag;
extern Int8U Backward_flag;

extern Int8U Run_flag;
extern Int8U BackStop_flag;
extern Int8U ForceStop_flag;
extern Int8U RunStop_flag;
extern Int32U stop_time;

extern Int8U MoveSpeed;
extern Int8U SelfLockEn_flag;
extern Int8U InTargetPosit_flag;

extern Int8U GoFrontEn_flag;
extern Int8U GoBackEn_flag;
extern Int8U GoFast_flag;
extern Int8U JogRunMode;
extern Int8U EncoderErr_flag;

extern Int8U RunDisplay_flag;
extern Int8U AutoPushRun_flag;


extern Int8U AutoCutExec_flag;
extern Int8U AutoCutStart_flag;
extern Int8U OneCutRoutine_flag;

extern Int8U PusherResetMove_flag;
extern Int16U PusherResetTime;


extern Int8U MotorType;
extern Int8U PushRstKey_flag;

extern Int8U InputTouch_flag;
extern Int8U ProcessRatio;
extern Int16U CodeSensorTime_AB;
extern Int8U CutPermit_flag;

extern Int8U ServoPressStop_flag;
extern Int8U DcServoGoTarget_flag;

extern Int16U LastAutoKnife_order;//  自刀 的前一刀
extern Int8U ReEnterAutoKnife_dis;  //再次进入自刀  提示

extern Int8U ACServoDrvErr_flag;
extern Int8U ACServoAlarmExec_flag;

extern Int8U ElectricWheelOn_flag; //电子手轮
extern Int8U MotorRun_flag;
extern Int8U InputMode;

extern Int32U current_inch;

extern Int8U LabelTime_flag;//label次数
extern Int32U LabelTime;//label次数
extern unsigned int Total_size;//总长
extern unsigned int Label_size;//标签长
extern unsigned int Waste_size;//废边
extern unsigned int Divide_num;//等分数
extern Int8U DisAllProgMode;

extern Int8U PramSel_Page;//
extern Int8U Para_sel;// 
extern Int8U Para2_sel;//2
extern Int8U IR_SensorStus;
extern Int8U JogLevel;// Jog??

//****************
void StartPic_dis(void);//开机画面显示

void WorkPic_dis(void);  //工作画面显示
void TextWindow_dis(void); //文本输入框
void Pear_dis(Int16U x, Int16U y);//鸭梨


void CurrentArea_save1(Int16U x,Int16U y, Int16U Wide,Int16U High);//暂存  当前区域 画面1
void CurrentArea_save2(Int16U x,Int16U y, Int16U Wide,Int16U High);//暂存  当前区域 画面2
void CurrentArea_save3(Int16U x,Int16U y, Int16U Wide,Int16U High);//暂存  当前区域 画面3
void CurrentArea_recover1(Int16U x, Int16U y, Int16U Wide,Int16U High);//恢复  当前区域 画面1
void CurrentArea_recover2(Int16U x, Int16U y, Int16U Wide,Int16U High);//恢复  当前区域 画面2
void CurrentArea_recover3(Int16U x, Int16U y, Int16U Wide,Int16U High);//恢复  当前区域 画面3

void InputNum_dis(pInt8U nums,Int8U cou); //尺寸输入显示

void OneProNum_dis(Int16U pro_order, PROCESS_HEAD pro_head); //程序号码显示
void StepNum_dis(Int16U step_sum,Int16U step_order); //步骤号码显示
void KnifeOrder_dis(Int16U row, Int16U order,Int16U num_color);//-----------------------显示一个序号
void KnifeSize_dis(Int16U row,  Int32U Knife_size,Int16U num_color);//--------------显示一个尺寸
void PushFlag_dis(Int8U row,  Int8U Knife_flag);//-------一个 推纸 标志显示

Int8U OneKnifeDataSel_dis(Int16U knife,Int8U row,Int16U num_color);  //一刀数据 高亮显示

void ProgSet_dis(Int32U size, Int16U x, Int16U y, Int8U set_flag);// 标签页内 尺寸显示
void LabelSel_dis(Int8U sel, Int8U flag);
void DivideSel_dis(Int8U sel, Int8U flag);

void CurrentSize_dis(Int32U size);//当前尺寸
void FrontKnifeSize_dis(Int32U size);//刀前尺寸
void CurrUint_dis(Int8U unit);  //当前尺寸 单位
void FrontKnifeUint_dis(Int8U unit);  //当前尺寸 单位
void ParameterPage_dis(Int8U sel, Int8U flag); //参数 设置显示
void TimeSetSel_dis(Int8U sel, Int8U flag); //时间 设定 显示

void PromptNum_dis(void);  //输入数据范围 提示
void SelPulseDegree_dis(Int8U sel,Int8U flag); //脉冲设定
void PassDaysSet_dis(Int8U sel,Int8U flag);//天数设定

void SetMotorSpeed(Int8U speed_sel);//设定速度
void Draw_cross(Int16U x,Int16U y,Int16U color);

void ProgressBar_dis(Int16U total, Int16U now);  //进度条 显示


#endif

