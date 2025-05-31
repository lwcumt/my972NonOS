////////////////////////
//   按键 驱动程序
////////////////////////

//----------空间：			2M==2097152
//----------参数占用预留；	500
//----------剩余(2M-参数):  2M-500=2096652

//-----------总刀数据：		1897500+500*100=1947500
//-----------reserve：		149152


#ifndef __KEY_H

#define __KEY_H

#include "main.h"
//#include "sys.h"
#include "uart.h"
#include"drv_glcd.h"

#include "pcf8563.h"
#include "touch.h"

#define KEYIO_DDR  GPIOH 
#define KEYPUL_IO GPIOH




#define KEYIO GPIOH  //键盘口定义



#define KEY_COL1 BIT6			//列1
#define KEY_COL1_DIR_OUT()  (GPIO_OpenBit(GPIOI, KEY_COL1, DIR_OUTPUT, NO_PULL_UP))
#define KEY_COL1_CLR()	{(GPIO_CloseBit(GPIOI, KEY_COL1));\
						(GPIO_OpenBit(GPIOI, KEY_COL1, DIR_OUTPUT, NO_PULL_UP));\
						GPIO_ClrBit(GPIOI, KEY_COL1);}

#define KEY_COL1_SET()	{(GPIO_CloseBit(GPIOI, KEY_COL1));\
						(GPIO_OpenBit(GPIOI, KEY_COL1, DIR_INPUT, NO_PULL_UP));\
						GPIO_SetBit(GPIOI, KEY_COL1);}

#define KEY_COL2 BIT5			//列2
#define KEY_COL2_DIR_OUT()  (GPIO_OpenBit(GPIOI, KEY_COL2, DIR_OUTPUT, NO_PULL_UP))
#define KEY_COL2_CLR()	{(GPIO_CloseBit(GPIOI, KEY_COL2));\
						(GPIO_OpenBit(GPIOI, KEY_COL2, DIR_OUTPUT, NO_PULL_UP));\
						GPIO_ClrBit(GPIOI, KEY_COL2);}

#define KEY_COL2_SET()	{(GPIO_CloseBit(GPIOI, KEY_COL2));\
						(GPIO_OpenBit(GPIOI, KEY_COL2, DIR_INPUT, NO_PULL_UP));\
						GPIO_SetBit(GPIOI, KEY_COL2);}

#define KEY_COL3 BIT4			//列3
#define KEY_COL3_DIR_OUT()  (GPIO_OpenBit(GPIOI, KEY_COL3, DIR_OUTPUT, NO_PULL_UP))
#define KEY_COL3_CLR()	{(GPIO_CloseBit(GPIOI, KEY_COL3));\	
						(GPIO_OpenBit(GPIOI, KEY_COL3, DIR_OUTPUT, NO_PULL_UP));\
						GPIO_ClrBit(GPIOI, KEY_COL3);}

#define KEY_COL3_SET()	{(GPIO_CloseBit(GPIOI, KEY_COL3));\	
						(GPIO_OpenBit(GPIOI, KEY_COL3, DIR_INPUT, NO_PULL_UP));\
						GPIO_SetBit(GPIOI, KEY_COL3);}



#define KEY_COL4 BIT3			//列4
#define KEY_COL4_DIR_OUT()  (GPIO_OpenBit(GPIOI, KEY_COL4, DIR_OUTPUT, NO_PULL_UP))
#define KEY_COL4_CLR()	{(GPIO_CloseBit(GPIOI, KEY_COL4));\	
						(GPIO_OpenBit(GPIOI, KEY_COL4, DIR_OUTPUT, NO_PULL_UP));\
						GPIO_ClrBit(GPIOI, KEY_COL4);}

#define KEY_COL4_SET()	{(GPIO_CloseBit(GPIOI, KEY_COL4));\	
						(GPIO_OpenBit(GPIOI, KEY_COL4, DIR_INPUT, NO_PULL_UP));\
						GPIO_SetBit(GPIOI, KEY_COL4);}

#define KEY_COL5 BIT2			//列5
#define KEY_COL5_DIR_OUT()  (GPIO_OpenBit(GPIOI, KEY_COL5, DIR_OUTPUT, NO_PULL_UP))
#define KEY_COL5_CLR()	{(GPIO_CloseBit(GPIOI, KEY_COL5));\	
						(GPIO_OpenBit(GPIOI, KEY_COL5, DIR_OUTPUT, NO_PULL_UP));\
						GPIO_ClrBit(GPIOI, KEY_COL5);}

#define KEY_COL5_SET()	{(GPIO_CloseBit(GPIOI, KEY_COL5));\	
						(GPIO_OpenBit(GPIOI, KEY_COL5, DIR_INPUT, NO_PULL_UP));\
						GPIO_SetBit(GPIOI, KEY_COL5);}

#define KEY_COL6 BIT1			//列6
#define KEY_COL6_DIR_OUT()  (GPIO_OpenBit(GPIOI, KEY_COL6, DIR_OUTPUT, NO_PULL_UP))
#define KEY_COL6_CLR()	{(GPIO_CloseBit(GPIOI, KEY_COL6));\	
						(GPIO_OpenBit(GPIOI, KEY_COL6, DIR_OUTPUT, NO_PULL_UP));\
						GPIO_ClrBit(GPIOI, KEY_COL6);}


#define KEY_COL6_SET()	{(GPIO_CloseBit(GPIOI, KEY_COL6));\	
						(GPIO_OpenBit(GPIOI, KEY_COL6, DIR_INPUT, PULL_UP));\
						GPIO_SetBit(GPIOI, KEY_COL6);}

	#define KEY_COL6_IN() (GPIO_ReadBit(GPIOI,KEY_COL6))					
						

#define KEY_CODE_MASK 0xf800



/*
#define ZERO_KEY_CODE	0x8200000	//零号键
#define ONE_KEY_CODE	0x8400000	//一号键
#define TWO_KEY_CODE	0x8800000	//二号键
#define THREE_KEY_CODE	0x9000000	//三号键
#define FOUR_KEY_CODE	0xa000000	//四号键
#define FIVE_KEY_CODE	0xc000000	//五号键

#define SIX_KEY_CODE	0x10200000	//六号键
#define SEVEN_KEY_CODE	0x10400000	//七号键
#define EIGHT_KEY_CODE	0x10800000	//八号键
#define NINE_KEY_CODE	0x11000000	//九号键
#define AUTO_KEY_CODE 0x12000000 // AUTO 键码  第一列 第一键 
#define PROG_KEY_CODE 0x14000000 // PROGRAM 键码  第三列 第六键

#define YES_KEY_CODE 0x20200000   // yes 键码 第二列 第六键
#define NO_KEY_CODE 0x20400000     // no 键码  第三例  第一键
#define MOVE_KEY_CODE 0x20800000  // move 键码 第三列 第二键
#define READ_KEY_CODE 0x21000000    // 查阅 键码  第三列  第三键
#define ADD_KEY_CODE 0x22000000  //  +键 码  第三列 第四键
#define SUB_KEY_CODE	0x24000000 // - 键码  第三列 第五键


#define INSERT_KEY_CODE 0x40200000     //插入键码
#define DELETE_KEY_CODE 0x40400000     //删除键码
#define RETURN_KEY_CODE 0x40800000     //返回键码
#define NEXTKINFE_KEY_CODE 0x41000000  //下一刀键码
#define ADJUST_KEY_CODE 0x42000000    //基准键码
#define OPTION_KEY_CODE 0x44000000   //OPTION 键码

#define REV_KEY_CODE 0x80200000  //  REVIEW 键码  第四列 第一键
#define MANUAL_KEY_CODE 0x80400000  // MANUAL 键码  第四列 第二键
#define UP_KEY_CODE 0x80800000   // ↑ 键码  第四列 第三键
#define DOWN_KEY_CODE 0x81000000  // ↓ 键码  第四列 第四键   
#define DENGFENG_KEY_CODE 0x82000000 //等分键码
#define DENGJU_KEY_CODE 0x84000000  //等距键码

*/
#define tst_KEY_CODE	0x4c00000	//******
#define STOP_KEY_CODE	0xaa55000	//******


#define ZERO_KEY_CODE	0x4200000	//零号键
#define ONE_KEY_CODE	0x4400000	//一号键
#define TWO_KEY_CODE	0x4800000	//二号键
#define THREE_KEY_CODE	0x5000000	//三号键
#define FOUR_KEY_CODE	0x6000000	//四号键

#define FIVE_KEY_CODE	0x8200000	//五号键
#define SIX_KEY_CODE	0x8400000	//六号键
#define SEVEN_KEY_CODE	0x8800000	//七号键
#define EIGHT_KEY_CODE	0x9000000	//八号键
#define NINE_KEY_CODE	0xa000000	//九号键

#define AUTO_KEY_CODE 0x10200000 // AUTO 键码  第一列 第一键 
#define PROG_KEY_CODE 0x10400000 // PROGRAM 键码  第三列 第六键
#define YES_KEY_CODE  0x10800000   // yes 键码 第二列 第六键
#define NO_KEY_CODE   0x11000000     // no 键码  第三例  第一键
#define MOVE_KEY_CODE 0x12000000  // move 键码 第三列 第二键

#define READ_KEY_CODE   0x20200000    // 查阅 键码  第三列  第三键
#define ADD_KEY_CODE    0x20400000  //  +键 码  第三列 第四键
#define SUB_KEY_CODE	0x20800000 // - 键码  第三列 第五键
#define INSERT_KEY_CODE 0x21000000     //插入键码
#define DELETE_KEY_CODE 0x22000000     //删除键码

#define RETURN_KEY_CODE		 0x40200000     //返回键码
#define NEXTKNIFE_KEY_CODE	 0x40400000  //下一刀键码
#define ADJUST_KEY_CODE		 0x40800000    //基准键码
#define OPTION_KEY_CODE		 0x41000000   //OPTION 键码
#define REV_KEY_CODE		 0x42000000  //  REVIEW 键码  第四列 第一键

#define MANUAL_KEY_CODE		 0x80200000  // MANUAL 键码  第四列 第二键
#define UP_KEY_CODE			 0x80400000   // ↑ 键码  第四列 第三键
#define DOWN_KEY_CODE		 0x80800000  // ↓ 键码  第四列 第四键   
#define DENGFENG_KEY_CODE	 0x81000000 //等分键码
#define DENGJU_KEY_CODE		 0x82000000  //等距键码

#define ENABLE 1
#define DISABLE 0

#define KEYLONGDOWNTIMEDATA 2000  // 长按下时间值   本例为5S

//-------------------------------------------------------------
#define LEFT_KEY_CODE       0xffff1008 //左
#define RIGHT_KEY_CODE       0xffff1009 //右

//------------时间框位置
#define Tx_1  50
#define Ty_1  2 
#define SpaceX  50
#define SpaceY  50
#define Gap   20

#define Tx_2  (Tx_1+SpaceX+Gap)
#define Ty_2  Ty_1

#define Tx_3  (Tx_2+SpaceX+Gap)
#define Ty_3  Ty_1

#define Tx_4  (Tx_3+SpaceX+Gap*2)
#define Ty_4  Ty_1

#define Tx_5  (Tx_4+SpaceX+Gap)
#define Ty_5  Ty_1

#define LineY  (Ty_1+24)//间隔线

#define Line1_Y  (Ty_1+20)//冒号线
#define Line2_Y  (Line1_Y+15)//冒号线
//---------时间数字位置
#define TimNum_Y 17

#define Year1_X  (Tx_1+4)//Year   S
#define Year1_Y  (TimNum_Y)

#define Year0_X  (Tx_1+24)//Year   G
#define Year0_Y  (Year1_Y)

#define Month1_X  (Tx_2+4)//Month
#define Month1_Y  (Year1_Y)

#define Month0_X  (Tx_2+24)
#define Month0_Y  (Year1_Y)

#define Date1_X  (Tx_3+4)//Date
#define Date1_Y  (Year1_Y)

#define Date0_X  (Tx_3+24)
#define Date0_Y  (Year1_Y)

#define Hour1_X  (Tx_4+4)//Hour
#define Hour1_Y  (Year1_Y)

#define Hour0_X  (Tx_4+24)
#define Hour0_Y  (Year1_Y)

#define Min1_X  (Tx_5+4)//Min
#define Min1_Y  (Year1_Y)

#define Min0_X  (Tx_5+24)
#define Min0_Y  (Year1_Y)



//-------------------刀 数据
#define DATA_SAVE_OFFSET    500//  spi 刀数据 起始地址
#define PRO_NUM_25PEADD		0//  程序 段 参数保存地址
#define ORIGINAL_25PEADD	10//  原点保存地址(设定参数)

//-尺寸限定
//#define SIZE_MIN	 	3000
//#define SIZE_MAIX      145000


//****************功能测试  模式------
#define TEST_NO   0
#define TEST_TOUCH  1
#define TEST_HELP   2
#define TEST_BOARD   3
#define TEST_MOTOR_TYPE  4

// ---------passcode
#define PASS_MOD_CODE		111111//687610 //密码模式 
#define PASSCODE_formula(code)  (code*2+2)  //密码算法

//--------------------------
#define NO_SIGN		0   //   
#define PLUS_SIGN	1   //  +
#define MINUS_SIGN	2   //  -
#define MULT_SIGN	3   //  *
#define DIV_SIGN	4   //  /

extern int KeyCode;  //键代码
extern int KeyDownTime;  //键扫下计时
extern int KeyLongDownTime;  //键长时间按下计时
extern char KeyDown_Flag;   //键按下标志位
extern char KeyExec_Flag;   //键处理标志位
extern char KeyLongDown_Flag;
extern unsigned char InputBuf[30];
extern unsigned char InputCou;
extern int KeyCode_Temp;
extern unsigned long int vbcd;
extern void KeyScan(void);  //键扫描  1MS进入一次
extern void KeyExec(Int32U keycode);  //键处理
extern void LongKey_exec(Int32U keycode,Int32U key_temp);  //长按键处理
extern void MultiKey_exec(Int32U keycode);  //组合键处理
extern int KeyCheck(void);
extern void KeyReadCode(void);
extern void Key_Enable(unsigned char enb);
extern void KeyInit(void);  //键端口初始化
 extern void lcdpage1(void);
extern  void lcdnian( unsigned long int x0, unsigned long int y0,unsigned int  chicun); 
extern  void lcdhaoma( unsigned long int x0, unsigned long int y0,unsigned char chicun);
extern  void chengxudu(void);
extern  void lcdweizhicn( unsigned long int x0, unsigned long int y0,unsigned long int chicun);
extern  void lcdweizhicnH( unsigned long int x0, unsigned long int y0,unsigned long int chicun);
 extern void lcdzhishi(void);

extern  unsigned  long int  vbcd4,  qianjixian,zhongjixian,houjixian,jizhun,mubiao ;
extern  unsigned char bcd[3],qbcd[3],hbcd[5];
extern   unsigned char status,flagyunxing8,flagrun,huamian,flagshanchu;         //
extern   unsigned char step_ground;   //
extern   unsigned char step_add,qianjinflag,houtuiflag;      //
extern   unsigned char qianjin,houtui,huamian,daohao,flagdanwei;
extern   unsigned char   flagqyx,  t0zhongduan, poweon_flag,senor;
extern    unsigned  char flaggong,flaghsd,flagqsd;
extern    unsigned char flagchengxu,flagkeysong,flagzhiyou;
extern     unsigned  char flagjia,flagjian,flagcheng,flagchu;
extern    unsigned long int yushu,mada;
extern    unsigned long int speedup_steps;
extern    unsigned long int speedup_steps_B;
extern    unsigned long int rollsteps;     
extern    unsigned char flagtingji7,flagtingji8,flagbz[200],chengxuhaoma;

extern    unsigned long int qianjincn,houtuicn,weizhicn[200],ymuqiancn;
extern    unsigned long int  tempqianjin1, temphoutui1; 




extern  unsigned char Comment_flag;
extern unsigned char WorkStart_flag;
extern unsigned char flagyunxing;


extern Int8U PromptDis_flag;
extern unsigned long int maichongdangliang,xxmuqiancn;
extern Int32U PassCode;
extern Int8U PaperCutEnb_signal;
extern Int8U StartCheck_mode;
extern Int8U OutSensorOK_flag;
extern Int32U Zpulse_cou;
extern Int32U Z_Pulse;

//extern Int8U RunToCusor_flag;

extern Int8U BellStart_flag;
extern Int8U Board_TestMod;
extern Int8U TouchCalcu_mode;
extern Int8U InputTouch_flag;

extern Int8U PassCheckDis_flag;

extern Int8U AutoRoute_flag;

extern Int8U ManualMoveMode;
extern Int8U Stop_F_Remind_flag;

extern Int8U TargetBell_flag;
extern Int16U TargetBell_time;
extern Int8U TargetBell_mode;

extern unsigned  char flagyd;
extern unsigned char flagchengxu,flagkey,flagtime1;
extern Int8U AC_MotorSPD; //AC  motor  speed

extern Int8U RunEnb_flag;
extern Int8U PressCircle_mode;

//******************************************
void ClrInput_function(void);//清零 输入框

void SaveOneKnife_datas(Int16U prog,Int16U order ,pInt8U pdatas);//保存一刀数据
void GetOneKnife_datas(Int16U prog,Int16U order ,pInt8U pdatas);//从sdram读取一刀数据
void SaveBuf_datas(Int16U prog,Int16U order1, Int16U order2);//保存 order1到 order2  buf区的数据到spi
void ClrBuf_datas(Int16U prog,Int16U order1, Int16U order2);//清零 order1到 order2  buf区的数据

void GetPro_headInfo(Int16U prog, pInt8U pdata);//sdram 读一个程序头(程序名+ 时间 +刀数 )
void OneProgHeadInfo_dis(Int8U row, Int16U p_order, Int8U mark_flag);	//一条程序 显示

void Size_1page_dis(Int16U start_order,Int16U row);//一页尺寸显示

void DeleteOneKnife(Int16U prog,Int16U knife);      //删除一刀
void InsertOneKnife(Int16U prog,Int16U knife);       //插入一刀
void SavePro_headInfo(Int16U prog, pInt8U pdata);//spi保存一个程序的 头(程序名+ 时间 +刀数 )

Int8U CheckInputNums(void);  //输入尺寸 计算

void LabelSel_dis(Int8U sel, Int8U flag);
void DivideSel_dis(Int8U sel, Int8U flag);
void CursorDown_inTable(void); //**** 光标下移 显示 数据

void Label_function(void);  //标签功能
void Divide_function(void);  //等分功能
void LabelEnter_exec(void); //标签 三组 数据设定确认
void DivideEnter_exec(void); //等分 数据设定确认

void Prog_1page_dis(Int16U prog,Int16U line);//一页程序显示
void ProEnter_exec(void);  //程序选择 输入确认

void ExportOnePro_dis(Int16U p_order); //更新 显示一个程序-------------
void ReorderProByDate_dis(void);	//按时间排序 程序列表
void DeleteOneProg(Int8U cursor, Int16U p_order);		//F4 ----删除一个程序
void DeleteAllProg(void);		//F5--- 删除所有程序

void F3_AutoAdd_exec(Int32U add_data);  //F3++  批量数据 自加
void F4_AutoSub_exec(Int32U add_data); //F4--  批量数据 自减

void ReadFrontLimit(void);  //读取前极限
void SaveFrontLimit(void);  //保存前极限
void ReadMiddleLimit(void);  //读取中极限
void SaveMiddleLimit(void);  //保存中极限
void ReadBackLimit(void);  //读取后极限
void SaveBackLimit(void);  //保存后极限
void ReadLanguage(void);//读取语言
void SaveLanguage(void); //保存语言
void ReadUnit(void);//读取单位
void SaveUnit(void);  //保存单位
void ReadAheader(void);//读取提前量
void SaveAheader(void);  //保存提前量
void Read_degree(void);
void Save_degree(void);
void ReadPushDistance(void);//读取自动推纸距离
void SavePushDistance(void);  //保存自动推纸距离
void ReadSpeedLevel(void);  //读取 速度档位数
void SaveSpeedLevel(void);  //保存 速度档位数
void ReadPressValid_flag(void);  //压纸 有效标志
void SavePressValid_flag(void);
void ReadMachineType(void);  //机器类型
void SaveMachineType(void);  //机器类型

void SaveOriginalSize(void);  //保存原点尺寸
void SetPulse_degree(void);  //设定脉冲当量
void GeneratePassCode(void);
void PassCheck_dis(Int16U x, Int16U y); //密码提示

void SaveFirstDays(void);
void ReadFirstDays(void);
void SaveSecondDays(void);
void ReadSecondDays(void);
void SaveFirstDays_flag(void);
void ReadFirstDays_flag(void);
void SaveSecondDays_flag(void);
void ReadSecondDays_flag(void);
void SaveWorkDays(void);


void ReadACMotorSpeed(void);   //交流伺服 速度
void SaveACMotorSpeed(void);   //交流伺服 速度
void ReadElectricWheelSwitch(void);//电子手轮
void SaveElectricWheelSwitch(void);//电子手轮
void DaysTime_check(void);

void RunTo_cursor(void); //运行至 光标处
void AutoRun_start(void);


void CalcData_input_to_text(Int32U data_temp,pInt8U str_text);  //转换成bcd 数

void CalculatorValue_exec(Int8U sign);  //计算值 处理
void Calcul_Nums(Int8U a_n1,Int8U a_n2,Int8U b_n1,Int8U b_n2, Int8U sign);  //输入框内数据  运算 得结果存入CalcData_temp
void DataConvert_to_Text(Int32U data_temp,pInt8U str_text);  //计算器输入 转换成bcd 数

void CalcGetValue_exec(void);             //= 运算 所得结果

void ShiftSpeed_SetExec(Int32U keycode);  //档速设定键处理
void AutoRun_AutoPush_exec(void);  // 自动 循环运行

void StopMotorExec(void);


void CheckKnifeSum_exec(void);  //--------------总刀数    核对

void GetAC_MotorSpeed(void);  //交流伺服  速度判定
void ProMessageModify_mode(Int16U p_order);	//程序信息修改 模式
void DeleteAllExitWind(void);	//退出全删 提示框
void RenewModifyDate(void);	//更新时间信息-.-.-.-.-.-.-.-.-.-.-.-.-.-
void DeleteAllData_hintWind(void);	//删除所有数据  提示框
#endif



