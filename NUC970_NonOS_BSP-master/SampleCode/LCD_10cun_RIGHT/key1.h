////////////////////////
//   按键 驱动程序
////////////////////////



#ifndef __KEY_H

#define __KEY_H

#include "main.h"
#include "sys.h"
#include "uart.h"
#include"drv_glcd.h"

#define KEYIO_DDR FIO3DIR
#define KEYPUL_IO FIO3PIN

#define KEYIO FIO3PIN  //键盘口定义




#define KEY_COL1 31			//列1
#define KEY_COL1_DIR_OUT()  FIO3DIR |= 1ul<<KEY_COL1
#define KEY_COL1_CLR()	FIO3CLR |= 1ul<<KEY_COL1
#define KEY_COL1_SET()	FIO3SET |= 1ul<<KEY_COL1

#define KEY_COL2 30			//列2
#define KEY_COL2_DIR_OUT()  FIO3DIR |= 1ul<<KEY_COL2
#define KEY_COL2_CLR()	FIO3CLR |= 1ul<<KEY_COL2
#define KEY_COL2_SET()	FIO3SET |= 1ul<<KEY_COL2

#define KEY_COL3 29			//列3
#define KEY_COL3_DIR_OUT()  FIO3DIR |= 1ul<<KEY_COL3
#define KEY_COL3_CLR()	FIO3CLR |= 1ul<<KEY_COL3
#define KEY_COL3_SET()	FIO3SET |= 1ul<<KEY_COL3

#define KEY_COL4 28			//列4
#define KEY_COL4_DIR_OUT()  FIO3DIR |= 1ul<<KEY_COL4
#define KEY_COL4_CLR()	FIO3CLR |= 1ul<<KEY_COL4
#define KEY_COL4_SET()	FIO3SET |= 1ul<<KEY_COL4

#define KEY_COL5 27			//列5
#define KEY_COL5_DIR_OUT()  FIO3DIR |= 1ul<<KEY_COL5
#define KEY_COL5_CLR()	FIO3CLR |= 1ul<<KEY_COL5
#define KEY_COL5_SET()	FIO3SET |= 1ul<<KEY_COL5


#define KEY_COL6 26			//列6
#define KEY_COL6_DIR_OUT()  FIO3DIR |= 1ul<<KEY_COL6
#define KEY_COL6_CLR()	FIO3CLR |= 1ul<<KEY_COL6
#define KEY_COL6_SET()	FIO3SET |= 1ul<<KEY_COL6

#define KEY_CODE_MASK 0x03e00000



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
#define NEXTKINFE_KEY_CODE	 0x40400000  //下一刀键码
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

#define KEYLONGDOWNTIMEDATA 800  // 长按下时间值   本例为0.8S

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
extern void KeyExec(void);  //键处理
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
extern   unsigned char step_add;      //
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












#endif



