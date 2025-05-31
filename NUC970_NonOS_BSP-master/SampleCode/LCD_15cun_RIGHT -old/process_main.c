
#include <stdio.h>
#include "main.h"
#include "sys.h"

#include "drv_glcd.h"
//#include "pwm.h"
#include "timer.h"
#include "uart.h"
#include "io.h"
#include "spi.h"
#include "hzk.h"
#include"comm.h"
#include"chndot.h"
//#include"realtime.h"
#include"key.h"
//#include"pic.h"
//#include"processbar.h"
#include"i2c.h"
#include"pcf8563.h"


//#include "mcp4921.h"//DA4921

#include"m25pe16.h"
//#include"new_display.h"
#include "pic_exec.h"
#include"touch.h"
#include"download.h"

#include"word_lib.h"

#include "test_io.h"

#include "port.h"

#include"servo.h"
//#include "comm_touch.h"
#include "uart_config.h"
#include "lcd_config.h"
#include "spi_config.h"
#include "nand_config.h"
#include "file.h"
#include "gtp.h"

#include "keyboard.h"

#include "sysiotest.h"

#include "modbus.h"


//	#define TIME_BCOL   0xCE79 //


/*

#include"main.h"
#include "arm926ej_cp15_drv.h"
#include "ttbl.h"
#include"bmp.h"
#include"uart.h"
#include"seor1.c"
#define uchar unsigned char
#define uint unsigned int

*/

//#define TIME_BCOL   0x9CD3 //




Int8U Flash_flag;//显示刷新标志
Int8U DisInit_flag;//显示初始画面标志

Int8U DAchanel;//DA输入选择


char hz[]="我";
extern Int8U HanZi[32];
extern  Int32U Rcv_New ;						// 为1时表明接收到新数据
extern  Int32U    Snd_N   ;						// 记录接收数据完毕后，需发送数据的个数
//extern  Int8U	  Rcv_Buf[0x80];	// 字符接收数组	

//extern  unsigned  char    chengxuhaoma   ;
//extern  unsigned  long int  vbcd4,  qianjixian,zhongjixian,houjixian,jizhun ;
 extern unsigned long int   chengxuweizhi[100];
// extern unsigned  char flagbz[200];
  unsigned long int Rswanwei1,Rwanwei1,Rqianwei1,Rbaiwei1,Rshiwei1,Rgewei1,sw1,qb1,sg1;
  
  unsigned long int swanwei3,wanwei3,qianwei3,baiwei3,shiwei3,gewei3;   
  
 unsigned long int daoqiancn,daoqiancn1,xsdaoqiancn;
 unsigned  char tmpdao,tmpdao1,flagcishu,tmpya,tmpya1,flagdao,flagya; 
// unsigned char bcd[3],qbcd[3],hbcd[5];
 unsigned long int fanqqianwei,fanqbaiwei,fanzqianwei,fanzbaiwei,fanhswwei,fanhwwei,fanhqianwei,fanhbaiwei;
 unsigned char tuobanbcd[3];
volatile Int32U Rcv_Num;


 unsigned  char flagcut,flagoneci,flagonly;
 
Int16U BarCou1=0;
Int8U BarCou2=0;

Int32U Cou_press;


Int8U buff[280];

Int8U RBuf[2100];




Int8U Hold_Up_flag;
Int8U Hold_Down_flag;

Int8U OnePress_sign_mod;
Int8U OneKnife_sign_mod;
Int8U NewKnife_sign_mod;

Int32U CutRelease_time;







Int8U Asensor_temp;
Int8U Bsensor_temp;
Int8U ABsensor_temp;


Int8U PressStopDis_flag;



Int16U AutoCutTime;


Int16U orig_wait_time;

Int16U ServoStopTime;

Int16U DisplayFlashTime;


Int8U Z_PulseIN;

unsigned char SecTemp;   


Int16U on_gap,off_gap;  //蜂鸣时间


Int16U ForceStopTime;
Int32U ForceStopSize;

extern unsigned char BootFolder;
Int8U FrontLimitDis_flag;

/*************************************************************************
 * Function Name: main
 * Parameters: none
 *
 * Return: none
 *
 * Description: main
 *

 *************************************************************************/
 /*
void DrawPic_IntFlash16(const Int16U *pic,int x,int y,int picwidth,int pichigh);

void LoadDataFlashToSDRAM(pInt16U p,int da,  int dlenth);

void DrawPic_SDRAM(long sect,int x,int y,int picwidth,int    pichigh);

void DrawPic_DATAFLASH(long sect,int x,int y,int picwidth,int pichigh);
*/

 
void IOinputTest1_2(void);//IO  输入测试********1.2  
void IOinputTest1_3(void);//IO  输入测试********1.3  
void Dis_init(void);//初始显示画面

void Time_dis(void);//
Int16U Caluate_Days(void);
void PassCheck_dis(Int16U x, Int16U y); //密码提示

void RenewOneKnife_data(void);

void OutLimit_check(void); //外部限位 
void Joggle_GoFast(void);
void FreqRuningLimit_ctrl(void);  //运行中  外部信号
void FreqWorkStart_check(void);  //工作模式前  准备
Int8U PressStop_check(void);//压纸停机  判断
void CutEnable_Exec(void);  //裁切 操作
void AutoCutPush_exec(void);  //自动裁切
void ServoWorkStart_check(void);  //工作模式前  准备
void ServoRunning_ctrl(void); //直流伺服 运行控制
void ACServoWorkStart_check(void);  //交流伺服  工作模式前  准备

void BellTwice_exec(void);  //蜂鸣  两声

void ACMotorGetCurrentSize(void);  // 交流伺服   尺寸计算
void ACMotorRunning_ctrl(void);//交流伺服运行  控制
void AC_MotorRuningLimit_ctrl(void);  //运行中  到外部信号 停止

void NowSizeNum_dis(void);

void ACMotor_GetZpulse(void);
void ACServoAlarm_exec(void);  //交流伺服  警报  处理



// #define SDRAM_BASE_ADDR 0x80000000
// #define VECTOR_BASE_ADDR 0x80100000



/* Prototype for external IRQ handler */
void lpc32xx_irq_handler(void);
void workstartexec(void);

////void delay(unsigned int  cnt)
////{
////    unsigned int  i = cnt;
////    while (i != 0) i--;
////    return;
////}


void Process_Main(void)
{
  // Init MMU
//int i;
unsigned char spi_Data[16];
unsigned int temptime;
unsigned char NFBuf[4096];
pInt32U cp1,cp2;

  //int j,n,k;
  int BarCou;
   Int32U i,j;
	Int16U d,Ms100t;   
				 Int16U Cou=0;
          int NumberCou;
				 
pInt16U ptr;//				 
Int32U temp;

//////  disable_irq();
//////  /* Initialize interrupt system */
//////  int_initialize(0xFFFFFFFF);

//////  /* Install standard IRQ dispatcher at ARM IRQ vector */
//////  int_install_arm_vec_handler(IRQ_VEC, (PFV) lpc32xx_irq_handler);

//////  /* Enable IRQ interrupts in the ARM core */
//////  enable_irq();

//////IO_Init();
//////LCD_Init();
//////delay(100000);
//////LCD_6BIT_PIN_SET();

//////GLCD_Buffer_Fill(BLUE_COLOR);
////////P3_OUTP_SET=0x1;
////////UART2_Init();
//////SD_PW_OFF();
////////SD_PW_ON();


//////// pInt8U ps=(pInt8U)malloc(1024);



//////Spi_Init();

//////Read_DevID();

//////Nand_Init();

Nand_Reset();
Nand_ReadID();
// Read_DevID();


////////I2C_Init();
/*
Nand_Format();
iFiles.FileLength=0;
asector=File_GetFreeSector_New();
iFiles.FileLength=10;
asector=File_GetFreeSector_New();
iFiles.FileLength=130*1024;
asector=File_GetFreeSector_New();
iFiles.FileLength=256*1024;
asector=File_GetFreeSector_New();
iFiles.FileLength=830*1024;
asector=File_GetFreeSector_New();
asector=File_GetFreeSector_New();
asector=File_GetFreeSector_New();
asector=File_GetFreeSector_New();
*/
//Nand_Format();//删除并标记坏块
//////SDInsert_Check();//检测是否有SD卡插入


/*
FileWriteBootApp(1+0x30);//应写入为ASCII
FileLoadBootApp(); //读出的是ASCII
*/


BootFolder=FileLoadBootApp()-0x30;
if((BootFolder<1)||(BootFolder>6))//如果启动项不是1-6个应用序号，强制从第1个读取资源文件
	{
	BootFolder=1;
	}
// BootFolder=1;


/*

FileFolderRead("Power.bmp",(unsigned char*)START_PIC_sdram);//读开机画面
BootFolder=2;
FileFolderRead("Power.bmp",(unsigned char*)START_PIC_sdram);//读开机画面
BootFolder=1;
FileFolderRead("Power.bmp",(unsigned char*)START_PIC_sdram);//读开机画面
BootFolder=2;
FileFolderRead("Power.bmp",(unsigned char*)START_PIC_sdram);//读开机画面

*/


/*
for(i=0;i<1024;i++)
	{
	Nand_EraseBlock((i*NF_BLOCK_BYTES)>>11);
	Nand_FillPage_SDbuf(FileNum,128*1024,i); //删除原有的信息 包括文件名、长度，地址  跳出目录块
	Nand_WriteBlock(i,(unsigned char *)NF_SECTOR_SDRAM_BUF);
	Nand_ReadBlock(i,(unsigned char *)NF_SECTOR_SDRAM_BUF);//读取 文件name信息
	}
//SDInsert_Check();//检测是否有SD卡插入
for(i=0;i<1024;i++)
	{
//	Nand_EraseBlock((startsector*NF_BLOCK_BYTES)>>11);
	//Nand_FillPage_SDbuf(FileNum,128*1024,0xa5); //删除原有的信息 包括文件名、长度，地址  跳出目录块
//	Nand_WriteBlock(startsector,(unsigned char *)NF_SECTOR_SDRAM_BUF);
	Nand_ReadBlock(i,(unsigned char *)NF_SECTOR_SDRAM_BUF);//读取 文件name信息
	Nand_EraseBlock((i*NF_BLOCK_BYTES)>>11);
	Nand_ReadBlock(i,(unsigned char *)NF_SECTOR_SDRAM_BUF);//读取 文件name信息
	}
		
		*/
			



//File_Create("\\APP_1\\test.txt");

//Nand_ReadBlock(5,(unsigned char *)NF_SECTOR_SDRAM_BUF);//读取 文件name信息
/*
Nand_Format();//删除并标记坏块

File_CreateFolder("APP_1");//"\\APP_1\\test.txt");
File_CreateFolder("APP_2");//"\\APP_1\\test.txt");
File_CreateFolder("APP_3");//"\\APP_1\\test.txt");
File_CreateFolder("APP_4");//"\\APP_1\\test.txt");
File_CreateFolder("APP_5");//"\\APP_1\\test.txt");
File_CreateFolder("APP_6");//"\\APP_1\\test.txt");

File_FindFolder("APP_6");
File_FindFolder("APP_2");
File_FindFolder("APP_4");
File_FindFolder("APP_1");
File_FindFolder("APP_5");
File_FindFolder("APP_3");


File_Create("\\APP_1\\test.txt");
File_FindFolder("test.txt");

FileRead("Boot_App_1.bin",(unsigned char*)DOWNFILE_SDRAM_ADD);
FileRead("\\APP_1\\test.txt",(unsigned char*)DOWNFILE_SDRAM_ADD);
FileRead("Boot_App_1.bin",(unsigned char*)DOWNFILE_SDRAM_ADD);
FileRead("Vector.bin",(unsigned char*)VECTOR_BASE_ADDR);
*/
////////AOUT1_SET();
////////AOUT2_SET();
////////AOUT3_SET();
////////AOUT4_SET();
////////AOUT5_SET();

/*
AOUT1_CLR();
AOUT2_CLR();
AOUT3_CLR();
AOUT4_CLR();
AOUT5_CLR();

*/
/*
RLOUT1_OFF ;
RLOUT2_OFF ;
RLOUT3_OFF ;
RLOUT4_OFF ;
RLOUT5_OFF ;

RLOUT1_ON;
RLOUT2_ON ;
RLOUT3_ON ;
RLOUT4_ON ;
RLOUT5_ON ;



AOUT1_SET();
AOUT2_SET();
AOUT3_SET();
AOUT4_SET();
AOUT5_SET();

AOUT1_CLR();
AOUT2_CLR();
AOUT3_CLR();
AOUT4_CLR();
AOUT5_CLR();

M_DOUT_OFF;
M_POUT_OFF;

M_DOUT_ON;
M_POUT_ON;
*/

unsigned char  OutFlag;
OutFlag=0;


Timer0Init();



//////PWR_CTRL|=(1<<1);
//////PWR_CTRL&=~(Int32U)(1<<5);//PWR_CTRL|=(1<<5);

//******************************************



 Rcv_Num=0;
 CommCou=0;
 //AT45DB_Init(AT45DB161);  //初始化DATAFLASH
 
 BellOUT_ON;
 i=1000000;
 while(i--);
 BellOUT_OFF;
  i=1000000;
 while(i--);
 BellOUT_ON;
  i=1000000;
 while(i--);
 BellOUT_OFF;
 
////////////////////////////////////////////////////////////////

//*****************************************************************************测试图片  显示效果
//Dis_init();//初始显示画面


//SD_LOAD_DirIn;

GLCD_Buffer_Fill(0);

//KeyDis_Init();//按键显示初始化	
	
//SPIInit();	
ReadLanguage();
//while(NandflashInit()!=0);//nand 初始化	
/*
if(SD_LOAD_PIN==0)	//sd下载文件
{
GLCD_Buffer_Fill(0xffff);
DiskFiles_To_NandFlash();
while(1);
}
*/
#if CODE_APP_SAVE==1		//code save--------------------------------
	CodeAppExec();
	while(1);
#else

// if(DecodeAppExec() == 0)	//等待解码	99999999999999999999999999999999999
// {
// while(1);
// }


//BootFolder=5;
StartPic_dis();//显示开机画面



ReadMachineType(); //机器类型
switch(MotorType)
	{
	case MOTOR_FREQ_5_SPD_RST:
	case MOTOR_FREQ_3_SPD:
	case MOTOR_FREQ_3_SPD_RST: 
	Uart_mod=0;
				on_gap=120;
				off_gap=80;
					break;
	// // case MOTOR_DC_SERVO:
	// // case MOTOR_DC670_SERVO:
				// // Uart_mod=1;//伺服串口 通讯
				// // ReadMovSpeed();
				// // ReadJogSpeed();  //速度
				// // Read_PitchRatio();  //螺距 速比
				// // on_gap=500;
				// // off_gap=1000;
					// // break;
	case MOTOR_AC_A6_SERVO:
			//------A6---参数---
				Uart_mod=2;//测试通讯-------------
				ModBusIO_Init();
				ModBus_CommCou=0;
				//ModBus_CrcTest();
				// Modbus_A6_LoadSetData();
				Modbus_A6_LuoJu=10;
				ReadA6MarkBenchSize();//A6 编码器 基准值(6 Byte)
				// Modbus_A6_LoadErrData();//调入上次错误代码    	-------20171124 去掉
				ReadCurrentSize_A6Coder();//读取当前 A6编码器值
	case MOTOR_AC_SERVO:	
	case MOTOR_AC_SERVO_REV:
				//------------通用AC---
				ReadACMotorSpeed();
				GetAC_MotorSpeed();   //交流伺服  速度判定
				ReadElectricWheelSwitch();//电子手轮
				on_gap=120;
				off_gap=80;
					break;
	}
  //uart0
	
//UART2_Init();//485
//UART1_Init();//key51
//UART5_Init();//----------------------------touchcomm


ReadUnit();
ReadOriginalSize();
ReadFrontLimit();
ReadMiddleLimit();
ReadBackLimit();

Size_MAX=BackLimit;
if(Unit==UNIT_MM)
	Size_MAX_num=Size_MAX;
else
	Size_MAX_num=Size_MAX*100/254;
if(Carrier_IN==0)  //托板 信号
	Size_MIN=FrontLimit;
else
	Size_MIN=MiddleLimit;
if(Unit==UNIT_MM)
	Size_MIN_num=Size_MIN;
else
	Size_MIN_num=Size_MIN*100/254;
		


ReadDatas_to_sdram();   //刀数据 ----读取
//ReadStanDistance();

Read_TouchDatas();

ReadAheader();

Read_degree();
SetPulse_degree();
ReadCurrentPulseAB();

ReadFirstDays();
ReadSecondDays();
ReadFirstDays_flag();
ReadSecondDays_flag();
ReadPushDistance();
ReadAirOffDistance();	//关气阀 距离

ReadPressValid_flag();  //压纸 有效标志
ReadIRValidStatus();//IR status
ReadStepDistance(); // 步进距离


DaysTime_check();

CurrentArea_save1(START_PROMPT_X1, START_PROMPT_Y1,   START_PROM_WIDE, START_PROM_HIGH);
CurrentArea_save2(START_PROMPT_X2, START_PROMPT_Y2,   START_PROM_WIDE, START_PROM_HIGH);

Timer0Init();

	
PageKf_Size_Init();	//每页 刀数设定
ReadVirtualTargetSizeGap();		//虚拟目标值
ReadIRChgWorkmodeValid();	//红外切换工作模式标记


while(1)
   {
   //ACMotor_GetZpulse();
   
   if(Ms_Flag!=0)
	  {
	  Ms_Flag=0;
	  if(Touch_code==0)
		Keyboard_scan();
	  if(KeyboardDown_flag==0)
		 // ToucScan(); 
		TouchScan_Uart(); 
      ShiftKeyExec();//
	  
	  // // if((MotorType<MOTOR_DC_SERVO)||(MotorType>=MOTOR_AC_SERVO)) //变频器 3种
		 // // {
		 AllSensor_IN_Get();   //端口检测
		 // // }
	  // // else
		 // // {
		 // // GetCutSensorIN();   //端口检测
		 // // }
	  if(MotorType>=MOTOR_AC_SERVO) 
		 {
		 ACServoAlarm_exec();  //交流伺服  警报  处理
		 if(MotorType==MOTOR_AC_A6_SERVO)	//A6 处理
			{
			if((Run_flag==0)&&(GoBackEn_flag==0)&&(GoFrontEn_flag==0))
				{
				 ModbusComm_CtrlExec();//--------20170524	
		 		}
			  else
				{
				if(SendCmdOn_flag==1)
					{
					ModBus_Comm_LinkErr=0;//通讯连接错误 清除
					SendCmdOn_flag=0;
					}
				}
			}
		 }
		 
	  if((EncoderErr_flag==1)||(ACServoDrvErr_flag==1))
			{
			Cou++;
			if(Cou>=200)
				{
				Cou=0;
				if(ModBus_Comm_LinkErr==0)
				BellOUT_ANTI;  ///故障 蜂鸣----
			 //  LED2_ANTI; 
				} 
			}
			
			
			
	  //************************************************************************************************************
	  if(WorkStart_flag==1)  //进入工作状态
	     {	 
		 BellTwice_exec();  //蜂鸣  两声
		 
		if(MotorType>=MOTOR_AC_SERVO)
			{
			ACMotorGetCurrentSize();  // 交流伺服   尺寸计算
			}
	 
	 //************以下日期时间显示
         Ms100t++;
         if(Ms100t>=200)
             {
             Ms100t=0;
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
					case MOTOR_FREQ_5_SPD_RST:	
					case MOTOR_FREQ_3_SPD:	
					case MOTOR_FREQ_3_SPD_RST:
					case MOTOR_AC_SERVO:
					case MOTOR_AC_SERVO_REV:
					case MOTOR_AC_A6_SERVO:
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
									// switch(MotorType)
										// {
										// case MOTOR_FREQ_5_SPD_RST://----5档速 
												// break;
										// case MOTOR_FREQ_3_SPD://----3 档速	
										// case MOTOR_FREQ_3_SPD_RST://----3 档速+复位
											// RLOUT2_ON;;//气阀断开
												// break;
										// }
									if(MotorType>MOTOR_FREQ_5_SPD_RST)
										RLOUT3_ON;// RLOUT2_ON;//气阀断开
									}
								if(Run_flag==0)
									{
									if(PaperCutEnb_signal==2)
										{
										if(OnePress_sign_mod==1)
											OnePress_sign_mod++;
										}
									if(WorkMode == AUTO_MODE)//自动主画面下
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
									// switch(MotorType)
										// {
										// case MOTOR_FREQ_5_SPD_RST://----5档速 
												// break;
										// case MOTOR_FREQ_3_SPD://----3 档速	
										// case MOTOR_FREQ_3_SPD_RST://----3 档速+复位
												// RLOUT2_OFF;//气阀闭合
												// break;
										// }
									if(MotorType>MOTOR_FREQ_5_SPD_RST)
										{
										if((WorkMode==TEACH_MODE)||(WorkMode==AUTO_MODE)||(WorkMode==SELF_CUT_MODE))
											{
											if(AirOffOK_flag==0)
												RLOUT3_OFF;// RLOUT2_OFF;//气阀闭合
											}
										else
											RLOUT3_OFF;//RLOUT2_OFF;//气阀闭合
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
									if(WorkMode == AUTO_MODE)//自动主画面下
										{
										if(PressCircle_mode == 1)
											PressCircle_mode++;
										}
									}
								PressSensorInMachine_dis(0);//压纸 传感器位置 示意
								 }
									
								break;
					// // case MOTOR_DC_SERVO:
							// // NewKnife_sign_mod=3;//++++++++++++++++++++++++++
							// // if(CutPaper_IN2==0) //  刀 下--------------------
								 // // {
								 // // AllKnifeUp_flag=0;//----00000
								 // // CutRelease_time=0;
								 // // if(KnifeDown2_flag==0)
									// // {
									// // KnifeDown2_flag=1;
									// // KnifeUp2_flag=0;
										// // Knife_Down_dis( KNIFE_UP_X,  KNIFE_UP_Y);//刀下
									// // }
								// // if(Run_flag==0)
									// // {
									// // if(PaperCutEnb_signal==2)
										// // {
										// // if(OneKnife_sign_mod==1)
											// // OneKnife_sign_mod++;
										// // }
									// // }
								// // KnifeSensorInMachine_dis(1);//刀 传感器位置 示意
								 // // }
							 // // else
								 // // {
								 // // AllKnifeUp_flag=1;//----11111
								 // // if(KnifeUp2_flag==0)
									// // {
									// // KnifeDown2_flag=0;
									// // KnifeUp2_flag=1;
										// // Knife_Up_dis(KNIFE_UP_X,KNIFE_UP_Y);//刀上
									// // if(PressStopDis_flag==1)//压纸停机 提示
										// // {
										// // PressStopDis_flag=0;
										// // PromptNum_dis();//输入范围
										// // PromptDis_flag=1;
										// // }	
									// // }
								// // if(Run_flag==0)
									// // {
									// // if(PaperCutEnb_signal==2)
										// // {
										// // if((OneKnife_sign_mod==0)||(OneKnife_sign_mod==2))
											// // {
											// // OneKnife_sign_mod++;
											// // if(OneKnife_sign_mod==3)
												// // CutRelease_time=0;
											// // }
										// // }
									// // }
								// // KnifeSensorInMachine_dis(0);//刀 传感器位置 示意
								 // // }
								 
							 // // if(PressPaper_IN!=0) //压纸 下--------------------
								 // // {
								 // // AllPressUp_flag=0;//----000
								 // // CutRelease_time=0;
								 // // if(PressDown_flag==0)
									// // {
									// // PressDown_flag=1;
									// // PressUp_flag=0;
										// // Press_Down_dis(PRESS_UP_X,PRESS_UP_Y);//压纸 下
									// // //气阀断开
									// // }
								// // if(Run_flag==0)
									// // {
									// // if(PaperCutEnb_signal==2)
										// // {
										// // if(OnePress_sign_mod==1)
											// // OnePress_sign_mod++;
										// // }
									// // if(WorkMode == AUTO_MODE)//自动主画面下
										// // {
										// // if(PressCircle_mode == 0)
											// // PressCircle_mode++;
										// // }
									// // }
								// // PressSensorInMachine_dis(1);//压纸 传感器位置 示意
								 // // }
							 // // else
								 // // {
								 // // AllPressUp_flag=1;//----111
								 // // if(PressUp_flag==0)
									// // {
									// // PressDown_flag=0;
									// // PressUp_flag=1;
										// // Press_Up_dis(PRESS_UP_X,PRESS_UP_Y);//压上
									// // if(PressStopDis_flag==1)//压纸停机 提示
										// // {
										// // PressStopDis_flag=0;
										// // PromptNum_dis();//输入范围
										// // PromptDis_flag=1;
										// // }
									// // //气阀闭合
									// // }
								 // // if(Run_flag==0)
									// // {
									 // // if(PaperCutEnb_signal==2)
										// // {
										// // if((OnePress_sign_mod==0)||(OnePress_sign_mod==2))
											// // {
											// // OnePress_sign_mod++;
											// // if(OnePress_sign_mod==3)
												// // CutRelease_time=0;
											// // }
										// // }
									// // if(WorkMode == AUTO_MODE)//自动主画面下
										// // {
										// // if(PressCircle_mode == 1)
											// // PressCircle_mode++;
										// // }
									// // }
								// // PressSensorInMachine_dis(0);//压纸 传感器位置 示意
								 // // }
										
						 		// // break;
					// // case MOTOR_DC670_SERVO: 
							// // if(CutPaper_IN1!=0) //  刀 下--------------------
								 // // {
								 // // AllKnifeUp_flag=0;//----00000
								 // // CutRelease_time=0;
								 // // if(KnifeDown_flag==0)
									// // {
									// // KnifeDown_flag=1;
									// // KnifeUp_flag=0;
										// // Knife_Down_dis( KNIFE1_UP_X,  KNIFE1_UP_Y);//刀下
									// // }
								// // if(Run_flag==0)
									// // {
									// // if(PaperCutEnb_signal==2)
										// // {
										// // if(NewKnife_sign_mod==1)
											// // NewKnife_sign_mod++;
										// // }
									// // }
								// // //KnifeSensorInMachine_dis(1);//刀 传感器位置 示意
								 // // }
							 // // else
								 // // {
								 // // if(KnifeUp2_flag==1)
									// // AllKnifeUp_flag=1;//----11111
								 // // if(KnifeUp_flag==0)
									// // {
									// // KnifeDown_flag=0;
									// // KnifeUp_flag=1;
										// // Knife_Up_dis(KNIFE1_UP_X,KNIFE1_UP_Y);//刀上
									// // if(PressStopDis_flag==1)//压纸停机 提示
										// // {
										// // PressStopDis_flag=0;
										// // PromptNum_dis();//输入范围
										// // PromptDis_flag=1;
										// // }	
									// // }
								// // if(Run_flag==0)
									// // {
									// // if(PaperCutEnb_signal==2)
										// // {
										// // if((NewKnife_sign_mod==0)||(NewKnife_sign_mod==2))
											// // {
											// // NewKnife_sign_mod++;
											// // if(NewKnife_sign_mod==3)
												// // CutRelease_time=0;
											// // }
										// // }
									// // }
								// // //KnifeSensorInMachine_dis(0);//刀 传感器位置 示意
								 // // }
								 
							// // if(CutPaper_IN2==0) //  刀 下--------------------
								 // // {
								 // // AllKnifeUp_flag=0;//----00000
								 // // CutRelease_time=0;
								 // // if(KnifeDown2_flag==0)
									// // {
									// // KnifeDown2_flag=1;
									// // KnifeUp2_flag=0;
										// // Knife_Down_dis( KNIFE_UP_X,  KNIFE_UP_Y);//刀下
									// // }
								// // if(Run_flag==0)
									// // {
									// // if(PaperCutEnb_signal==2)
										// // {
										// // if(OneKnife_sign_mod==1)
											// // OneKnife_sign_mod++;
										// // }
									// // }
								// // KnifeSensorInMachine_dis(1);//刀 传感器位置 示意
								 // // }
							 // // else
								 // // {
								 // // if(KnifeUp_flag==1)
									// // AllKnifeUp_flag=1;//----11111
								 // // if(KnifeUp2_flag==0)
									// // {
									// // KnifeDown2_flag=0;
									// // KnifeUp2_flag=1;
										// // Knife_Up_dis(KNIFE_UP_X,KNIFE_UP_Y);//刀上
									// // if(PressStopDis_flag==1)//压纸停机 提示
										// // {
										// // PressStopDis_flag=0;
										// // PromptNum_dis();//输入范围
										// // PromptDis_flag=1;
										// // }	
									// // }
								// // if(Run_flag==0)
									// // {
									// // if(PaperCutEnb_signal==2)
										// // {
										// // if((OneKnife_sign_mod==0)||(OneKnife_sign_mod==2))
											// // {
											// // OneKnife_sign_mod++;
											// // if(OneKnife_sign_mod==3)
												// // CutRelease_time=0;
											// // }
										// // }
									// // }
								// // KnifeSensorInMachine_dis(0);//刀 传感器位置 示意
								 // // }
								 
							 // // if(PressPaper_IN!=0) //压纸 下--------------------
								 // // {
								 // // AllPressUp_flag=0;//----000
								 // // CutRelease_time=0;
								 // // if(PressDown_flag==0)
									// // {
									// // PressDown_flag=1;
									// // PressUp_flag=0;
										// // Press_Down_dis(PRESS_UP_X,PRESS_UP_Y);//压纸 下
									
									// // }
								 // // if(Run_flag==0)
									// // {
									// // if(PaperCutEnb_signal==2)
										// // {
										// // if(OnePress_sign_mod==1)
											// // OnePress_sign_mod++;
										// // }
									// // if(WorkMode == AUTO_MODE)//自动主画面下
										// // {
										// // if(PressCircle_mode == 0)
											// // PressCircle_mode++;
										// // }
									// // }
								// // PressSensorInMachine_dis(1);//压纸 传感器位置 示意
								 // // }
							 // // else
								 // // {
								 // // AllPressUp_flag=1;//----111
								 // // if(PressUp_flag==0)
									// // {
									// // PressDown_flag=0;
									// // PressUp_flag=1;
										// // Press_Up_dis(PRESS_UP_X,PRESS_UP_Y);//压上
									// // if(PressStopDis_flag==1)//压纸停机 提示
										// // {
										// // PressStopDis_flag=0;
										// // PromptNum_dis();//输入范围
										// // PromptDis_flag=1;
										// // }
									
									// // }
								// // if(Run_flag==0)
									// // {
									// // if(PaperCutEnb_signal==2)
										// // {
										// // if((OnePress_sign_mod==0)||(OnePress_sign_mod==2))
											// // {
											// // OnePress_sign_mod++;
											// // if(OnePress_sign_mod==3)
												// // CutRelease_time=0;
											// // }
										// // }
									// // if(WorkMode == AUTO_MODE)//自动主画面下
										// // {
										// // if(PressCircle_mode == 1)
											// // PressCircle_mode++;
										// // }
									// // }
								// // PressSensorInMachine_dis(0);//压纸 传感器位置 示意
								 // // }
										
						 		// // break;
					}
					/****
					 if(Encoder_A_IN==0) //编码器A 下--------------------
						 {
						 if(A_Down_flag==0)
							{
							A_Down_flag=1;
							A_Up_flag=0;
							// // if(InputTouch_flag==0)
								// // Red_A_dis(RED_A_X,RED_A_Y);//红A
							}
						 }
					 else
						 {
						 if(A_Up_flag==0)
							{
							A_Down_flag=0;
							A_Up_flag=1;
							// // if(InputTouch_flag==0)
								// // Black_A_dis(RED_A_X,RED_A_Y);//黑A
							}
						 }
					 if(Encoder_B_IN==0) //编码器B 下--------------------
						 {
						 if(B_Down_flag==0)
							{
							B_Down_flag=1;
							B_Up_flag=0;
							// // if(InputTouch_flag==0)
								// // Red_B_dis(RED_B_X,RED_B_Y);//红B
							}
						 }
					 else
						 {
						 if(B_Up_flag==0)
							{
							B_Down_flag=0;
							B_Up_flag=1;
							// // if(InputTouch_flag==0)
								// // Black_B_dis(RED_B_X,RED_B_Y);//黑B
							}
							}
						 }**/
					 
					 if(IRsensor_IN==0) //红外  下----------------------
						 {
						 if(IR_Down_flag==0)
							{
							IR_Down_flag=1;
							IR_Up_flag=0;
							// if(ButtonTouch_mode==0)
								IR_CUT_dis(IR_X,IR_Y); //手红外
							}
						if(WorkMode==SELF_CUT_MODE)//自刀主画面下
							{
							//#if 0  //--------((((((((((
							if(Run_flag==1)  //运行中
								{
								if(IRChgWorkmodeValid_flag!=0)	//红外--切换工作模式20180110
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
													break;
											// // case MOTOR_DC_SERVO:
											// // case MOTOR_DC670_SERVO:
												// // DCServoStop();  //停止运行
													// // break;
											case MOTOR_AC_SERVO:
											case MOTOR_AC_SERVO_REV:
												ACServoStop();
												
													break;
											}
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
								AutoCutStart_flag=0;
								RunStop_flag=0;
								//Run_flag=0;
								}
							
							LastAutoKnife_order=Knife_order;
							if(IRChgWorkmodeValid_flag!=0)	//红外--切换工作模式20180110
								{/****20170818***/
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
					 else
						 {
						 if(IR_Up_flag==0)
							{
							IR_Up_flag=1;
							IR_Down_flag=0;
							// if(ButtonTouch_mode==0)
								IR_LINE_dis(IR_X,IR_Y);//红线
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
							PressCircle_mode=0;
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
											//RunToCusor_flag=1;
											//if(AutoCutStart_flag==0)  //未启动 裁切 则 标记一个循序
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
						if(WorkMode == AUTO_MODE)
							{
							if(PressCircle_mode== 2)
								{
								PressCircle_mode=0;
								volatile pInt8U pdata=(pInt8U)&OneKnife_data;
								GetOneKnife_datas(Pro_data.pro_num, Knife_order, pdata);//
								if((OneKnife_data.k_flag&0x0f)==PRESS_FLAG) //压纸 标志  则自动走到下一刀
									{
									AutoRun_AutoPush_exec();
									}
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
					case MOTOR_FREQ_5_SPD_RST:
					case MOTOR_FREQ_3_SPD:
					case MOTOR_FREQ_3_SPD_RST:
						if(ForceStop_flag==0)
							{
							if(BackStop_flag==0)
								{
								if((OutMiddle_limit==0))	//20170904
									MoveSpeedCtrl();
								else
									{
									if(Forward_flag==0)
									MoveSpeedCtrl();
								}
								}
							else
								{
								stop_time++;
								if(stop_time>=500)  //后退结束 等待
									{
									BackStop_flag=0;
									Backward_flag=0;
									}
								}
							FreqRuningLimit_ctrl();  //运行中  外部信号	
							}
						else  //手动 减速停止
							{
							stop_time++;
							if(stop_time>300)
								{
								stop_time=0;
								if(MoveSpeed<4)  //减速
									{
									MoveSpeed++;
									SetMotorSpeed(MoveSpeed);
									}
								else
									{      //停止
									//MoveSpeed=5;
									//SetMotorSpeed(MoveSpeed);
									SelfLockEn_flag=0; //取消自锁
									ToTargetStop_flag=0;
									MoveStop();
									ForceStop_flag=0;
									BackStop_flag=0;
									Backward_flag=0;
									Forward_flag=0;
									Run_flag=0;
									InTargetPosit_flag=0;	//目标位置
									TargetSize=0;
									TargetSize_temp=0;
									BeforeKnife_offset_in=0;
									AutoPushRun_flag=0; //自动推纸 运行
									AutoRoute_flag=0;
									RunStop_flag=0;
									AirOffOK_flag=0;
									}
								}
							}

								break;
					// // case MOTOR_DC_SERVO:
					// // case MOTOR_DC670_SERVO:
						// // ServoRunning_ctrl(); //直流伺服 运行控制
								// // break;
					case MOTOR_AC_SERVO:
					case MOTOR_AC_SERVO_REV:
					case MOTOR_AC_A6_SERVO:
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
				//if(AutoCutStart_flag==0)//  自动裁切 未启动
				//	{
				//	stop_time++;
					//if(stop_time>1)
						//{
				
				switch(MotorType)
					{
					case MOTOR_FREQ_5_SPD_RST:
					case MOTOR_FREQ_3_SPD:
					case MOTOR_FREQ_3_SPD_RST:
						if(CurrentSize>TargetSize)
							{
							temp=CurrentSize-TargetSize;
							}
						else
							{
							temp=TargetSize-CurrentSize;
							}
						if(temp<VirtualTargetSizeGap)  //误差允许范围  ------自锁确认
							{
							//Run_flag=0;
							
							if(AutoPushRun_flag==1)   //自动  推纸 结束后--------------------------------
								{
								//CursorDown_inTable();//**** 光标下移 显示 数据
								RunTo_cursor();//    运行到下一刀
								AutoPushRun_flag=0;
								}
							else   //------------停止在 目标位置
								{/*
								switch(MotorType) //3档速不带复位   （不自锁）
									{
									case MOTOR_FREQ_5_SPD_RST:
									case MOTOR_FREQ_3_SPD_RST:
									//		SelfLockEn_flag=1;
												break;
									}*/
								TargetBell_flag=1;  //蜂鸣器 启动
								TargetBell_mode=0;
								
								RLOUT1_OFF; RLOUT1_1_OFF;   // 允许裁切 启动	
								AutoCutPush_exec();  //自动裁切	
								//OneCutRoutine_flag=0;
								InTargetPosit_flag=1;	//在目标位置
								
								}
							}
						RunStop_flag=0;	
							break;
					// // case MOTOR_DC_SERVO:
					// // case MOTOR_DC670_SERVO:
						// // stop_time++;
						// // if(stop_time>300)
							// // {
							// // RunStop_flag=0;
							// // if(CurrentSize>TargetSize)
								// // {
								// // temp=CurrentSize-TargetSize;
								// // }
							// // else
								// // {
								// // temp=TargetSize-CurrentSize;
								// // }
							// // if(temp<DC_VIRTURE_SIZE)  //到目标位置
								// // {
								// // if(AutoPushRun_flag==1)   //自动  推纸 结束后--------------------------------
									// // {
									// // //CursorDown_inTable();//**** 光标下移 显示 数据
									// // RunTo_cursor();//    运行到下一刀
									// // AutoPushRun_flag=0;
									// // }
								// // else   //------------停止在 目标位置
									// // {
									// // if(BellStart_flag==0)
										// // {
										// // TargetBell_flag=1;  //蜂鸣器 启动
										// // TargetBell_mode=0;
										// // }
									// // BellStart_flag=0;
									
									// // RLOUT1_OFF;    // 允许裁切 启动	
									// // AutoCutPush_exec();  //自动裁切	
									// // //OneCutRoutine_flag=0;
									// // InTargetPosit_flag=1;	//在目标位置
									// // }
								// // }
							// // else
								// // {
								// // if(ServoAutoPushFinish_flag==1)
									// // {
									// // ServoAutoPushFinish_flag=0;
									// // if(AutoPushRun_flag==1)   //自动  推纸 结束后--------------------------------
										// // {
										// // //CursorDown_inTable();//**** 光标下移 显示 数据
										// // RunTo_cursor();//    运行到下一刀
										// // AutoPushRun_flag=0;
										// // }
									// // }
								// // else//直流伺服 模式    到极限停止后
									// // {
									// // Run_flag=0;
									// // InTargetPosit_flag=0;	//目标位置
									// // TargetSize=0;
									// // BeforeKnife_offset_in=0;
									// // AutoPushRun_flag=0;
									// // DcServoGoTarget_flag=0;
									// // }
								// // }	
							// // }
							// // break;
					case MOTOR_AC_SERVO:
					case MOTOR_AC_SERVO_REV:
						stop_time++;
						if(stop_time>150)	
							{
							RunStop_flag=0;
							if(AutoPushRun_flag==1)   //自动  推纸 结束后--------------------------------
								{
								//CursorDown_inTable();//**** 光标下移 显示 数据
								RunTo_cursor();//    运行到下一刀
								AutoPushRun_flag=0;
								}
							else   //------------停止在 目标位置
								{
								TargetBell_flag=1;  //蜂鸣器 启动
								TargetBell_mode=0;
								if(ACServoDrvErr_flag==0)
									{
									RLOUT1_OFF;RLOUT1_1_OFF;    // 允许裁切 启动	
									}
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
							
							break;
					case MOTOR_AC_A6_SERVO:
						stop_time++;
						if(stop_time>=150)	
							{
							stop_time=150;	
							RunStop_flag=0;
							if(AutoPushRun_flag==1)   //自动  推纸 结束后--------------------------------
								{
								//CursorDown_inTable();//**** 光标下移 显示 数据
								RunTo_cursor();//    运行到下一刀
								AutoPushRun_flag=0;
								}
							else   //------------停止在 目标位置
								{
								if(A6CoderEqual_flag==0)//当前尺寸==A6编码器值
									{
									ACMotorStopCheck();	//不等 ，则修正实际尺寸
									}
								else	//尺寸正确
									{
									TargetBell_flag=1;  //蜂鸣器 启动
									TargetBell_mode=0;
									if(ACServoDrvErr_flag==0)
										RLOUT1_OFF;    // 允许裁切 启动	
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
					
						
						
						
						//if(AutoCutStart_flag==0)	
						//	RunStop_flag=0;
					//	}
					//}
				//else   //自动裁切  中
				//	{
					//AutoCutPush_exec();  //自动裁切
				//	}
				
				}
			else
				{
				Joggle_GoFast(); //点动
				/*
				if(SelfLockEn_flag==1)  
					{
					if(Wheel_limit==1)
						{
						SelfLockEn_flag=0;//自锁 取消
						ToTargetStop_flag=0;
						TargetSize=0;
						BeforeKnife_offset_in=0;
						InTargetPosit_flag=0;	//清目标位置
						}
					}*/
				CutEnable_Exec();  //裁切 操作 
				// // if((MotorType==MOTOR_DC_SERVO)||(MotorType==MOTOR_DC670_SERVO))
					// // {
					// // if(DcServoGoTarget_flag==1)
						// // {
						// // if(Wheel_limit==1)   //手轮
							// // DcServoGoTarget_flag=0;
						// // }
					// // }	
				}
			} 
			
		 }  
	  else              //进入工作模式前  准备-------------------
		 {
		 if(Board_TestMod==0)//非功能测试模式
			{
			switch(MotorType)
				{
				case MOTOR_FREQ_5_SPD_RST:
				case MOTOR_FREQ_3_SPD:
				case MOTOR_FREQ_3_SPD_RST:
					FreqWorkStart_check();
					Joggle_GoFast(); //点动
					CutEnable_Exec();  //裁切 操作 
						break;
				// // case MOTOR_DC_SERVO:
				// // case MOTOR_DC670_SERVO:
					// // ServoWorkStart_check();  //工作模式前  准备
						// // break;
				case MOTOR_AC_SERVO:	
				case MOTOR_AC_SERVO_REV:	
				case MOTOR_AC_A6_SERVO:	
					if(ACServoDrvErr_flag==0)
						ACServoWorkStart_check();  //交流伺服  工作模式前  准备
					else	
						{
						/***
						if(KeyLinkDis_flag==0)
							{
							KeyLinkDis_flag=1;
							GLCD_SetWindow_Fill(KEYBOARD_CHECK_X,KEYBOARD_CHECK_Y,KEYBOARD_CHECK_X+START_PROM_WIDE-1, KEYBOARD_CHECK_Y+START_PROM_HIGH-1, 0xfffff, 0xffff);
							if(KeyboardLink_flag==0) //
								{
								switch(Language)
									{
									case CHN_HAN:
											Printf24("键盘未连接!",KEYBOARD_CHECK_X,KEYBOARD_CHECK_Y+5,RED_COLOR,1,0xffff);
											break;
									case ENGLISH:
											Printf24("Keyboard is off!",KEYBOARD_CHECK_X,KEYBOARD_CHECK_Y+5,RED_COLOR,1,0xffff);
											break;
									case INDONSIA:	//印尼
											Printf24("Keyboard tidak terhubung!",KEYBOARD_CHECK_X,KEYBOARD_CHECK_Y+5,RED_COLOR,1,0xffff);
											break;
									case PORTUGAL:	//葡萄牙
											Printf24("O teclado n?o está conectado!",KEYBOARD_CHECK_X,KEYBOARD_CHECK_Y+5,RED_COLOR,1,0xffff);
											ASCII_Printf("a",ASCII24_MODE,12,24,PUTAO_ZK24, KEYBOARD_CHECK_X+(11*12),KEYBOARD_CHECK_Y+5,RED_COLOR,0xffff);
											break;
									}
								}
							else
								{
								switch(Language)
									{
									case CHN_HAN:
											Printf24("键盘连接正常!",KEYBOARD_CHECK_X,KEYBOARD_CHECK_Y+5,RED_COLOR,1,0xffff);
											break;
									case ENGLISH:
											Printf24("Keyboard is OK!",KEYBOARD_CHECK_X,KEYBOARD_CHECK_Y+5,RED_COLOR,1,0xffff);
											break;
									case INDONSIA:	//印尼
											Printf24("Keyboard dihubungkan!",KEYBOARD_CHECK_X,KEYBOARD_CHECK_Y+5,RED_COLOR,1,0xffff);
											break;
									case PORTUGAL:	//葡萄牙
											Printf24("Teclado conectado corretamente!",KEYBOARD_CHECK_X,KEYBOARD_CHECK_Y+5,RED_COLOR,1,0xffff);
											break;
									}
								}
							}
							**/
						}
						break;
				}
			}
		 }
     
	  //-----------------------------------------------以下 测试模式用
	 if(Board_TestMod==TEST_BOARD)	//主板 端口测试 
	     {
		 /*
		 if(Borard1_2==1)
            IOinputTest1_2();//IO  输入测试********
	     else
	        IOinputTest1_3();//IO  输入测试********
			*/
		 IOinputTest();//IO  输入测试*******	
	     }
	  
	 //-------------------串口通信-----处理----------------
	 switch(Uart_mod)
		 {
		 case 0:
			DownFile_Exec();  //*******************数据  下载
			break;
		 case 1:  //伺服通讯
			ServoRev_Exec(); 
			break;
		 }
      }  
 
   

			
   }

#endif
}
   

   



void Time_dis(void)
{
volatile Int16U px,py;
volatile Int16U gap1,gap2,gap3;
Int16U Num_color,Back_color;
     
px=30;
//py=20;
py=0;
gap1=50,gap2=12,gap3=24;
Num_color=WHITE_COLOR;
Back_color=BLACK_COLOR;
if(Sec!=SecTemp)
	{
	SecTemp=Sec;
   Bcd[0]=2+48;
   Bcd[1]=0+48;
   Bcd[2]=(Year>>4)+48;
   Bcd[3]=(Year&0xf)+48;
   Bcd[4]=0;
   Printf24(Bcd,px,py,Num_color,1,Back_color);px+=gap1;
   Printf24("-",px,py,Num_color,1,Back_color);px+=gap2;
   
   Bcd[0]=(Month>>4)+48;
   Bcd[1]=(Month&0xf)+48;
   Bcd[2]=0;
   Bcd[3]=0;
   Bcd[4]=0;
   Printf24(Bcd,px,py,Num_color,1,Back_color);px+=gap3;
   Printf24("-",px,py,Num_color,1,Back_color);px+=gap2;

   Bcd[0]=(Dom>>4)+48;
   Bcd[1]=(Dom&0xf)+48;
   Bcd[2]=0;
   Bcd[3]=0;
   Bcd[4]=0;
   Printf24(Bcd,px,py,Num_color,1,Back_color);px+=gap1;

   Bcd[0]=(Hour>>4)+48;
   Bcd[1]=(Hour&0xf)+48;
   Bcd[2]=0;
   Bcd[3]=0;
   Bcd[4]=0;
   Printf24(Bcd,px,py,Num_color,1,Back_color);px+=gap3;
   Printf24(":",px,py,Num_color,1,Back_color);px+=gap2;

   Bcd[0]=(Min>>4)+48;
   Bcd[1]=(Min&0xf)+48;
   Bcd[2]=0;
   Bcd[3]=0;
   Bcd[4]=0;
   Printf24(Bcd,px,py,Num_color,1,Back_color);px+=gap3;
   Printf24(":",px,py,Num_color,1,Back_color);px+=gap2;
   
   Bcd[0]=(Sec>>4)+48;
   Bcd[1]=(Sec&0xf)+48;
   Printf24(Bcd,px,py,Num_color,1,Back_color);
	}
}

void CutEnable_Exec(void)  //裁切 允许操作
{
if(CutPermit_flag==0)//-------------
	{
	if(InTargetPosit_flag==0)
		{
		if((GoFrontEn_flag==0)&&(GoBackEn_flag==0))
			{
			switch(MotorType)
				{
				case MOTOR_FREQ_5_SPD_RST:
				case MOTOR_FREQ_3_SPD:
				case MOTOR_FREQ_3_SPD_RST:
					if(FreqMotorStop_flag==1)  //已经停止  后
						{
						RLOUT1_OFF; RLOUT1_1_OFF;   // 允许裁切
						CutPermit_flag=1;
						}
						break;
				// // case MOTOR_DC_SERVO:	
				// // case MOTOR_DC670_SERVO:
					// // if(ServoMoving_flag==0)
						// // {
						// // RLOUT1_OFF;    // 允许裁切
						// // CutPermit_flag=1;
						// // }
						// // break;
				case MOTOR_AC_SERVO:
				case MOTOR_AC_SERVO_REV:
				case MOTOR_AC_A6_SERVO:
					if(ACServoDrvErr_flag==0)
						{
						RLOUT1_OFF; RLOUT1_1_OFF;   // 允许裁切
						}
						
					CutPermit_flag=1;
						break;
				}		
			}
		}
	}
	
}

void AutoCutPush_exec(void)  //自动裁切 与推纸
{
if((WorkMode==SELF_CUT_MODE)||(WorkMode==AUTO_MODE)||(WorkMode==TEACH_MODE))  //自刀,自动 示教主模式
	{
	if((OneKnife_data.k_flag&0x0f)==PUSH_FLAG) //推纸 标志  则自动走到下一刀
		{
		AutoRun_AutoPush_exec();
		OneCutRoutine_flag=1;
		}
	else
		{
		if(OneCutRoutine_flag==1) //一个裁切循环 后
			{
			if((OneKnife_data.k_flag&0x0f)==KNIFE_FLAG) //刀 标志
				{
				if(WorkMode==SELF_CUT_MODE)
					{
					if(AutoCutDisable_flag==0)//自刀标记有效
						{
					if(AutoCutStart_flag==0)
						{
							// volatile Int32U tt=5000000;
								volatile Int32U tt=5000;
						while(tt--);
						RLOUT4_OFF;
						AutoCutTime=0;
						AutoCutStart_flag=1;//自动 裁切 启动
						BellOUT_ON;
						//Run_flag=1;//---------------------------------------------------
						CutEnBegin_flag=1;
						CutDelayTime=0;
						
						TargetBell_flag=0;  //2 bell 
						TargetBell_mode=0;
						}
					
					}
					else
						{
						AutoCutDisable_flag=0;
						}	
					}
				}
			OneCutRoutine_flag=0;
			}
		else
			{
			}
		}
	// // if((MotorType>MOTOR_FREQ_5_SPD_RST)&&(MotorType<MOTOR_DC_SERVO)||(MotorType>=MOTOR_AC_SERVO))
	if(MotorType<=MOTOR_AC_SERVO_REV)	//气垫标志  则到位断开气阀
		{
		if((OneKnife_data.k_flag&0xf0)==AIR_FLAG) //气垫 标志	则断开
			{
			RLOUT3_ON;//RLOUT2_ON;//气阀断开
			AirOffOK_flag=1; //气垫FLAG	断气标志
			}
		else		//闭合
			{
			//RLOUT3_OFF;//RLOUT2_OFF;//气阀闭合
			AirOffOK_flag=0;
			}	
		PressUp_flag=0;
		PressDown_flag=0;
		}
	}
}

void RenewOneKnife_data(void)
{
pInt8U pKdata;
Int32U data;
//----保存数据----------------
if(Unit==UNIT_MM)//
	{
	data=CurrentSize_temp;
	}
else	//inch
	{
	data=current_inch;
	}
if(Knife_order>OnePro_head.pro_knifeSUM)//更新步骤 总刀数
	{
	OnePro_head.pro_knifeSUM=Knife_order;
	}
pKdata=(pInt8U)&OneKnife_data;
GetOneKnife_datas(Pro_data.pro_num, Knife_order, pKdata);//
OneKnife_data.size=data;  //尺寸修改
// OneKnife_data.k_flag&=0xf0;  //清除 标志
OneKnife_data.k_flag=NO_FLAG;  //清除 标志
SaveOneKnife_datas(Pro_data.pro_num, Knife_order , pKdata);//保存一刀数据
	//-----显示
KnifeSize_dis(cursor_row,data,0);//尺寸
if(Knife_order<MAX_Knife)           //刀序递增
	{
	Knife_order++;
	StepNum_dis(OnePro_head.pro_knifeSUM,Knife_order);//步骤更新
	if(cursor_row<(PageKf_Size-1))
		{
		CursorKnife_dis(cursor_row, 0);//红色光标消失
		OneKnifeDataSel_dis(Knife_order-1, cursor_row,0);  //一刀数据 ---高亮显示
		cursor_row++;
		CursorKnife_dis(cursor_row, 1);//红色光标下移显示
		OneKnifeDataSel_dis(Knife_order, cursor_row,RED_COLOR);  //一刀数据 高亮显示
		}
	else   //页底
		{
		Size_1page_dis(Knife_order-(PageKf_Size-1),0);//一页尺寸显示
		}	
	}
						
}

void OutLimit_check(void) //外部限位 手轮
{
Int16U x,y;
Int32U coce_temp=0;
Int8U dis_buf[5]={0};
if(MotorType>=MOTOR_AC_SERVO)
	Wheel_limit=0;
if(outF_flag==0)//**************外部前限位
	{
	if(FrontLimit_IN!=0)
		{
		outLimF_time=0;
		outF_flag=1;
		}
	}
else
	{
	if(OutFront_limit==0)
		{
		if(FrontLimit_IN!=0)
			{
			outLimF_time++;
			if(outLimF_time>=20)
				{
				OutFront_limit=1;
				PromptDis_flag=0;
				if(WorkStart_flag==1)
					{
					x=REMIND_WINDOW_X,y=REMIND_WINDOW_Y;
					GLCD_SetWindow_Fill( x, y, x+REMIND_LENGTH, y+30, 0xfffff, 0xffff);//提示框
					switch(Language)
						{
						case CHN_HAN:
							Printf24("前限位断开!",x,y+5,RED_COLOR,1,0xffff);
								break;
						case ENGLISH:
							Printf24("Front-Limit is off!",x,y+5,RED_COLOR,1,0xffff);
								break;
						case INDONSIA:	//印尼
							Printf24("Lepaskan batas depan!",x,y+5,RED_COLOR,1,0xffff);
								break;
						case PORTUGAL:	//葡萄牙
							Printf24("A primeira parada édesconectada",x,y+5,RED_COLOR,1,0xffff);
								break;
						}
					}
				else
					{
					switch(MotorType)
						{
						case MOTOR_FREQ_5_SPD_RST:
						case MOTOR_FREQ_3_SPD:
						case MOTOR_FREQ_3_SPD_RST:
							if(StartCheck_mode<12)		
								{
								if(BackLimit_IN!=0)	//前后同时
									{
									x=START_PROMPT_X2,y=START_PROMPT_Y2;
									GLCD_SetWindow_Fill( x, y, x-1+START_PROM_WIDE, y-1+30, 0xfffff, 0xffff);//提示
									switch(Language)
										{
										case CHN_HAN:
											Printf24("前限位断开!",x,y+5,RED_COLOR,1,0xffff);
												break;
										case ENGLISH:
											Printf24("Front-Limit is off!",x,y+5,RED_COLOR,1,0xffff);
												break;
										case INDONSIA:	//印尼
											Printf24("Lepaskan batas depan!",x,y+5,RED_COLOR,1,0xffff);
												break;
										case PORTUGAL:	//葡萄牙
											Printf24("A primeira parada édesconectada",x,y+5,RED_COLOR,1,0xffff);
												break;
										}	
									}
								}
							else
								{
								x=START_PROMPT_X2,y=START_PROMPT_Y2;
								GLCD_SetWindow_Fill( x, y, x-1+START_PROM_WIDE, y-1+30, 0xfffff, 0xffff);//提示
								switch(Language)
									{
									case CHN_HAN:
										Printf24("前限位断开!",x,y+5,RED_COLOR,1,0xffff);
											break;
									case ENGLISH:
										Printf24("Front-Limit is off!",x,y+5,RED_COLOR,1,0xffff);
											break;
									case INDONSIA:	//印尼
										Printf24("Lepaskan batas depan!",x,y+5,RED_COLOR,1,0xffff);
											break;
									case PORTUGAL:	//葡萄牙
										Printf24("A primeira parada édesconectada",x,y+5,RED_COLOR,1,0xffff);
											break;
									}	
								}
										break;
						// // case MOTOR_DC_SERVO:
						// // case MOTOR_DC670_SERVO:
								// // x=START_PROMPT_X2,y=START_PROMPT_Y2;
								// // GLCD_SetWindow_Fill( x, y, x-1+START_PROM_WIDE, y-1+30, 0xfffff, 0xffff);//提示
								// // switch(Language)
									// // {
									// // case CHN_HAN:
										// // Printf24("前限位断开!",x,y+5,RED_COLOR,1,0xffff);
											// // break;
									// // case ENGLISH:
										// // Printf24("Front-Limit is off!",x,y+5,RED_COLOR,1,0xffff);
											// // break;
									// // case INDONSIA:	//印尼
										// // Printf24("Lepaskan batas depan!",x,y+5,RED_COLOR,1,0xffff);
											// // break;
									// // case PORTUGAL:	//葡萄牙
										// // Printf24("A primeira parada édesconectada",x,y+5,RED_COLOR,1,0xffff);
											// // break;
									// // }	
										// // break;
						case MOTOR_AC_SERVO:
						case MOTOR_AC_SERVO_REV:	
						case MOTOR_AC_A6_SERVO:	
							if(StartCheck_mode<11)		
								{
								if(BackLimit_IN!=0)	//前后同时
									{
									x=START_PROMPT_X2,y=START_PROMPT_Y2;
									GLCD_SetWindow_Fill( x, y, x-1+START_PROM_WIDE, y-1+30, 0xfffff, 0xffff);//提示
									switch(Language)
										{
										case CHN_HAN:
											Printf24("前限位断开!",x,y+5,RED_COLOR,1,0xffff);
												break;
										case ENGLISH:
											Printf24("Front-Limit is off!",x,y+5,RED_COLOR,1,0xffff);
												break;
										case INDONSIA:	//印尼
											Printf24("Lepaskan batas depan!",x,y+5,RED_COLOR,1,0xffff);
												break;
										case PORTUGAL:	//葡萄牙
											Printf24("A primeira parada édesconectada",x,y+5,RED_COLOR,1,0xffff);
												break;
										}	
									}
								}
							else
								{
								x=START_PROMPT_X2,y=START_PROMPT_Y2;
								GLCD_SetWindow_Fill( x, y, x-1+START_PROM_WIDE, y-1+30, 0xfffff, 0xffff);//提示
								switch(Language)
									{
									case CHN_HAN:
										Printf24("前限位断开!",x,y+5,RED_COLOR,1,0xffff);
											break;
									case ENGLISH:
										Printf24("Front-Limit is off!",x,y+5,RED_COLOR,1,0xffff);
											break;
									case INDONSIA:	//印尼
										Printf24("Lepaskan batas depan!",x,y+5,RED_COLOR,1,0xffff);
											break;
									case PORTUGAL:	//葡萄牙
										Printf24("A primeira parada édesconectada",x,y+5,RED_COLOR,1,0xffff);
											break;
									}	
								}
										break;
						}
					}
				}
			}		
		}
	else
		{
		if(FrontLimit_IN==0)
			{
			OutFront_limit=0;
			outF_flag=0;
			if(WorkStart_flag==1)
				{
				PromptDis_flag=1;
				PromptNum_dis();
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
						if(StartCheck_mode<3)
							{
							if(BackLimit_IN!=0)	//前后同时
								{
								CurrentArea_recover2(START_PROMPT_X2, START_PROMPT_Y2,    START_PROM_WIDE, START_PROM_HIGH);
								if((Wheel_limit==1)||(OutMiddle_limit==1))  //中极限  手轮
									{
									Wheel_limit=0;
									OutMiddle_limit=0;
									outM_flag=0;
									Wheel_flag=0;
									}	
								}
							}
									break;
					// // case MOTOR_DC_SERVO:
					// // case MOTOR_DC670_SERVO:
						// // CurrentArea_recover2(START_PROMPT_X2, START_PROMPT_Y2,    START_PROM_WIDE, START_PROM_HIGH);
						// // if((Wheel_limit==1)||(OutMiddle_limit==1))  //中极限  手轮
							// // {
							// // Wheel_limit=0;
							// // OutMiddle_limit=0;
							// // outM_flag=0;
							// // Wheel_flag=0;
							// // }	
									// // break;	
					}
				
				}
			}
		}
	}
if(outM_flag==0)//**************外部中限位
	{
	if(MiddleLimit_IN!=0)
		{
		outLimM_time=0;
		outM_flag=1;
		}
	}
else
	{
	if(OutMiddle_limit==0)
		{
		if(MiddleLimit_IN!=0)
			{
			outLimM_time++;
			if(outLimM_time>=20)
				{
				OutMiddle_limit=1;
				PromptDis_flag=0;
				if(WorkStart_flag==1)
					{
					x=REMIND_WINDOW_X,y=REMIND_WINDOW_Y;
					GLCD_SetWindow_Fill( x, y, x+REMIND_LENGTH, y+30, 0xfffff, 0xffff);//提示框
					}
				else
					{
					x=START_PROMPT_X2,y=START_PROMPT_Y2;
					GLCD_SetWindow_Fill( x, y, x-1+START_PROM_WIDE, y-1+30, 0xfffff, 0xffff);//提示
					}
					switch(Language)
						{
						case CHN_HAN:
							Printf24("中限位断开!",x,y+5,RED_COLOR,1,0xffff);
								break;
						case ENGLISH:
							Printf24("Middle-Limit is off!",x,y+5,RED_COLOR,1,0xffff);
								break;
						case INDONSIA:	//印尼
							Printf24("Lepaskan batas!",x,y+5,RED_COLOR,1,0xffff);
								break;
						case PORTUGAL:	//葡萄牙
							Printf24("Desligue o limite intermediá",x,y+5,RED_COLOR,1,0xffff);
							Printf24("                            rio!",x,y+5,RED_COLOR,0,0xffff);	//intermediário
								break;
						}
					}
					
				}
			}
	else
		{
		if(MiddleLimit_IN==0)
			{
			OutMiddle_limit=0;
			outM_flag=0;
			if(WorkStart_flag==1)
				{
				PromptDis_flag=1;
				PromptNum_dis();
				}
			else
				{
				CurrentArea_recover2(START_PROMPT_X2, START_PROMPT_Y2,    START_PROM_WIDE, START_PROM_HIGH);
				if((Wheel_limit==1)||(OutFront_limit==1))  //前极限  手轮
					{
					Wheel_limit=0;
					OutFront_limit=0;
					outF_flag=0;
					Wheel_flag=0;
					}
				}
			}
		}
	}
if(outB_flag==0)//**************外部后限位
	{
	if(BackLimit_IN!=0)
		{
		outLimB_time=0;
		outB_flag=1;
		}
	}
else
	{
	if(OutBack_limit==0)
		{
		if(BackLimit_IN!=0)
			{
			outLimB_time++;
			if(outLimB_time>=20)
				{
				OutBack_limit=1;
				PromptDis_flag=0;
				if(WorkStart_flag==1)
					{
					GLCD_SetWindow_Fill( REMIND_WINDOW_X, REMIND_WINDOW_Y, REMIND_WINDOW_X+REMIND_LENGTH, REMIND_WINDOW_Y+30, 0xfffff, 0xffff);//提示框
					switch(Language)
							{
							case CHN_HAN:
									Printf24("后限位断开!",REMIND_WINDOW_X,REMIND_WINDOW_Y+5,RED_COLOR,1,0xffff);
									break;
							case ENGLISH:
									Printf24("Back-Limit is off!",REMIND_WINDOW_X,REMIND_WINDOW_Y+5,RED_COLOR,1,0xffff);
									break;
							case INDONSIA:	//印尼
									Printf24("Setelah melepaskan batas!",REMIND_WINDOW_X,REMIND_WINDOW_Y+5,RED_COLOR,1,0xffff);
									break;
							case PORTUGAL:	//葡萄牙
									Printf24("Desligue o limite traseiro!",REMIND_WINDOW_X,REMIND_WINDOW_Y+5,RED_COLOR,1,0xffff);
									break;
							}
					}
				else
					{
					if(senor==1)
						{
							//---------------------------
						GLCD_SetWindow_Fill(START_PROMPT_X1, START_PROMPT_Y1, START_PROMPT_X1+START_PROM_WIDE-1, START_PROMPT_Y1+START_PROM_HIGH-1, 0xfffff, 0xffff);//提示
						switch(Language)
							{
							case CHN_HAN:
									Printf24("后限位断开!",START_PROMPT_X1,START_PROMPT_Y1+5,RED_COLOR,1,0xffff);
									break;
							case ENGLISH:
									Printf24("Back-Limit is off!",START_PROMPT_X1,START_PROMPT_Y1+5,RED_COLOR,1,0xffff);
									break;
							case INDONSIA:	//印尼
									Printf24("Setelah melepaskan batas!",START_PROMPT_X1,START_PROMPT_Y1+5,RED_COLOR,1,0xffff);
									break;
							case PORTUGAL:	//葡萄牙
									Printf24("Desligue o limite traseiro!",START_PROMPT_X1,START_PROMPT_Y1+5,RED_COLOR,1,0xffff);
									break;
							}
						}
					}
				}
			}
		}
	else
		{
		if(BackLimit_IN==0)
			{
			OutBack_limit=0;
			outB_flag=0;
			if(WorkStart_flag==1)
				{
				PromptDis_flag=1;
				PromptNum_dis();
				}
			else
				{
				//---------------------------
				if(senor==1)
					CurrentArea_recover1(START_PROMPT_X1, START_PROMPT_Y1,  START_PROM_WIDE, START_PROM_HIGH);
				}
			}
		}
	}

if(MotorType<MOTOR_AC_SERVO)//(MotorType<MOTOR_DC_SERVO)
	{
	if(Wheel_flag==0)//**************手轮
		{
		if(HandWheel_IN==0)
			{
			handwheel_time=0;
			Wheel_flag=1;
			}
		}
	else
		{
		if(Wheel_limit==0)
			{
			if(HandWheel_IN==0)
				{
				handwheel_time++;
				if(handwheel_time>=20)
					{
					Wheel_limit=1;
					PromptDis_flag=0;
									qianjinflag=1;
					if(WorkStart_flag==1)
						{
						x=REMIND_WINDOW_X,y=REMIND_WINDOW_Y;
						GLCD_SetWindow_Fill( x, y, x+REMIND_LENGTH, y+30, 0xfffff, 0xffff);//提示框
						}
					else
						{
						x=START_PROMPT_X2,y=START_PROMPT_Y2;
						GLCD_SetWindow_Fill( x, y, x-1+START_PROM_WIDE, y-1+30, 0xfffff, 0xffff);//提示
						}
						switch(Language)
							{
							case CHN_HAN:
								Printf24("手轮状态!",x,y+5,RED_COLOR,1,0xffff);
									break;
							case ENGLISH:
								Printf24("HandWheel mode!",x,y+5,RED_COLOR,1,0xffff);
									break;
							case INDONSIA:	//印尼
								Printf24("Negara Handwheel!",x,y+5,RED_COLOR,1,0xffff);
									break;
							case PORTUGAL:	//葡萄牙
								Printf24("Estado Volante!",x,y+5,RED_COLOR,1,0xffff);
									break;
							}	
					//************************刹车闭合
						switch(MotorType)
								{
								case MOTOR_FREQ_5_SPD_RST:	//----5档速
										RLOUT5_OFF;  //   刹车闭合
										RLOUT1_ON; RLOUT1_1_ON;   // 允许裁切断开
										break;
								case MOTOR_FREQ_3_SPD:	//----3 档速	
								case MOTOR_FREQ_3_SPD_RST:	//----3 档速+复位	
										RLOUT2_OFF;  //   刹车闭合
										RLOUT1_ON;  RLOUT1_1_ON;   // 允许裁切断开
										break;
								}
					}
				}
			}
		else
			{
			if(HandWheel_IN!=0)
				{
				Wheel_limit=0;
				Wheel_flag=0;
				if(WorkStart_flag==1)
					{
					PromptDis_flag=1;
					PromptNum_dis();
					}
				else
					{
					CurrentArea_recover2(START_PROMPT_X2, START_PROMPT_Y2,    START_PROM_WIDE, START_PROM_HIGH);
					if((OutMiddle_limit==1)||(OutFront_limit==1))  //前极限  手轮
						{
						OutMiddle_limit=0;
						OutFront_limit=0;
						outF_flag=0;
						outM_flag=0;
						}
					}
				//***************************刹车断开
				if(MotorRun_flag==0)
					{
						switch(MotorType)
								{
								case MOTOR_FREQ_5_SPD_RST:	//----5档速
										RLOUT5_ON;  //   刹车断开
										RLOUT1_OFF; RLOUT1_1_OFF;    // 允许裁切
										break;
								case MOTOR_FREQ_3_SPD:	//----3 档速	
								case MOTOR_FREQ_3_SPD_RST:	//----3 档速+复位	
										RLOUT2_ON;  //   刹车断开
										RLOUT1_OFF;  RLOUT1_1_OFF;  // 允许裁切
										break;
								}
					}
				}
			}
		}	
		
	}
// // if((MotorType==MOTOR_DC_SERVO)||(MotorType==MOTOR_DC670_SERVO))//直流私服
	// // {
	// // if(WorkStart_flag==1)
		// // {
		// // if(Wheel_flag==0)//**************手轮
			// // {
			// // if(HandWheel_IN==0)
				// // {
				// // handwheel_time=0;
				// // Wheel_flag=1;
				// // }
			// // }
		// // else
			// // {
			// // if(Wheel_limit==0)
				// // {
				// // if(HandWheel_IN==0)
					// // {
					// // handwheel_time++;
					// // if(handwheel_time>=20)
						// // {
						// // Wheel_limit=1;
						// // PromptDis_flag=0;
							// // GLCD_SetWindow_Fill( REMIND_WINDOW_X, REMIND_WINDOW_Y, REMIND_WINDOW_X+REMIND_LENGTH, REMIND_WINDOW_Y+30, 0xfffff, 0xffff);//提示框
						// // switch(Language)
							// // {
							// // case CHN_HAN:
									// // Printf24("手轮状态!",REMIND_WINDOW_X,REMIND_WINDOW_Y+5,RED_COLOR,1,0xffff);
									// // break;
							// // case ENGLISH:
									// // Printf24("HandWheel mode!",REMIND_WINDOW_X,REMIND_WINDOW_Y+5,RED_COLOR,1,0xffff);
									// // break;
							// // case INDONSIA:	//印尼
									// // Printf24("Negara Handwheel!",REMIND_WINDOW_X,REMIND_WINDOW_Y+5,RED_COLOR,1,0xffff);
									// // break;
							// // case PORTUGAL:	//葡萄牙
									// // Printf24("Estado Volante!",REMIND_WINDOW_X,REMIND_WINDOW_Y+5,RED_COLOR,1,0xffff);
									// // break;
							// // }
// // //------------------------------清除运行 状态--
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
						// // }
					// // }
				// // }
			// // else
				// // {
				// // if(HandWheel_IN!=0)
					// // {
					// // Wheel_limit=0;
					// // Wheel_flag=0;
					// // //if(WorkStart_flag==1)
					// // //	{
						// // PromptDis_flag=1;
						// // PromptNum_dis();
					// // //	}
					
					// // }
				// // }
			// // }	
		// // }
	// // }

if(WorkStart_flag==1)	
	{
	if(OutFront_limit==1)
		{
		if(PromptDis_flag==1)
			{
			PromptDis_flag=0;
			GLCD_SetWindow_Fill( REMIND_WINDOW_X, REMIND_WINDOW_Y, REMIND_WINDOW_X+REMIND_LENGTH, REMIND_WINDOW_Y+30, 0xfffff, 0xffff);//提示框
			switch(Language)
				{
				case CHN_HAN:
						Printf24("前限位断开!",REMIND_WINDOW_X,REMIND_WINDOW_Y+5,RED_COLOR,1,0xffff);
							break;
				case ENGLISH:
						Printf24("Front-Limit is off!",REMIND_WINDOW_X,REMIND_WINDOW_Y+5,RED_COLOR,1,0xffff);
							break;
				case INDONSIA:	//印尼
						Printf24("Lepaskan batas depan!",REMIND_WINDOW_X,REMIND_WINDOW_Y+5,RED_COLOR,1,0xffff);
							break;
				case PORTUGAL:	//葡萄牙
						Printf24("A primeira parada édesconectada",REMIND_WINDOW_X,REMIND_WINDOW_Y+5,RED_COLOR,1,0xffff);
						break;
				}
			}
		}
	else if(OutMiddle_limit==1)
			{
			if(PromptDis_flag==1)
				{
				PromptDis_flag=0;
				GLCD_SetWindow_Fill( REMIND_WINDOW_X, REMIND_WINDOW_Y, REMIND_WINDOW_X+REMIND_LENGTH, REMIND_WINDOW_Y+30, 0xfffff, 0xffff);//提示框
				switch(Language)
					{
					case CHN_HAN:
							Printf24("中限位断开!",REMIND_WINDOW_X,REMIND_WINDOW_Y+5,RED_COLOR,1,0xffff);
							break;
					case ENGLISH:
							Printf24("Middle-Limit is off!",REMIND_WINDOW_X,REMIND_WINDOW_Y+5,RED_COLOR,1,0xffff);
							break;
					case INDONSIA:	//印尼
							Printf24("Lepaskan batas!",REMIND_WINDOW_X,REMIND_WINDOW_Y+5,RED_COLOR,1,0xffff);
							break;
					case PORTUGAL:	//葡萄牙
							Printf24("Desligue o limite intermediá   ",REMIND_WINDOW_X,REMIND_WINDOW_Y+5,RED_COLOR,1,0xffff);
							Printf24("                            rio!",REMIND_WINDOW_X,REMIND_WINDOW_Y+5,RED_COLOR,0,0xffff);	//intermediário
							break;
					}
				}
			}
	else if(OutBack_limit==1)
			{
			if(PromptDis_flag==1)
				{
				PromptDis_flag=0;
				GLCD_SetWindow_Fill( REMIND_WINDOW_X, REMIND_WINDOW_Y, REMIND_WINDOW_X+REMIND_LENGTH, REMIND_WINDOW_Y+30, 0xfffff, 0xffff);//提示框
				switch(Language)
					{
					case CHN_HAN:
							Printf24("后限位断开!",REMIND_WINDOW_X,REMIND_WINDOW_Y+5,RED_COLOR,1,0xffff);
							break;
					case ENGLISH:
							Printf24("Back-Limit is off!",REMIND_WINDOW_X,REMIND_WINDOW_Y+5,RED_COLOR,1,0xffff);
							break;
					case INDONSIA:	//印尼
							Printf24("Setelah melepaskan batas!",REMIND_WINDOW_X,REMIND_WINDOW_Y+5,RED_COLOR,1,0xffff);
							break;
					case PORTUGAL:	//葡萄牙
							Printf24("Desligue o limite traseiro!",REMIND_WINDOW_X,REMIND_WINDOW_Y+5,RED_COLOR,1,0xffff);
							break;
					}	
				}
			}
	else if(Wheel_limit==1)
			{
			if(MotorType<MOTOR_AC_SERVO)
				{
				if(PromptDis_flag==1)
					{
					PromptDis_flag=0;
					GLCD_SetWindow_Fill( REMIND_WINDOW_X, REMIND_WINDOW_Y, REMIND_WINDOW_X+REMIND_LENGTH, REMIND_WINDOW_Y+30, 0xfffff, 0xffff);//提示框
					switch(Language)
						{
						case CHN_HAN:
								Printf24("手轮状态!",REMIND_WINDOW_X,REMIND_WINDOW_Y+5,RED_COLOR,1,0xffff);
									break;
						case ENGLISH:
								Printf24("HandWheel mode!",REMIND_WINDOW_X,REMIND_WINDOW_Y+5,RED_COLOR,1,0xffff);
									break;
						case INDONSIA:	//印尼
								Printf24("Negara Handwheel!",REMIND_WINDOW_X,REMIND_WINDOW_Y+5,RED_COLOR,1,0xffff);
									break;
						case PORTUGAL:	//葡萄牙
								Printf24("Estado Volante!",REMIND_WINDOW_X,REMIND_WINDOW_Y+5,RED_COLOR,1,0xffff);
								break;
						}	
					}
				}
			}
	else if(Z_Pulse_err_flag==1)	//----------------编码器  pule 故障
		{
		if(MotorType<MOTOR_AC_SERVO)	//(MotorType<MOTOR_DC_SERVO)
			{
			coce_temp=(Z_code_error+3)/4;
			dis_buf[0]=	(coce_temp/100)+48;
			dis_buf[1]=	(coce_temp/10)%10+48;
			dis_buf[2]=	(coce_temp%10)+48;
			if(coce_temp!=PulseAB_Z_current)
				{
				PulseAB_Z_current=coce_temp;
				if(PulseAB_Z_save_time<10)
					{
					PulseAB_Z_save_time++;
					SaveCurrentPulseAB();	//保存当前  编码器线数
					}
				}
			
			if(PromptDis_flag==1)
					{
					PromptDis_flag=0;
					GLCD_SetWindow_Fill( REMIND_WINDOW_X, REMIND_WINDOW_Y, REMIND_WINDOW_X+REMIND_LENGTH, REMIND_WINDOW_Y+30, 0xfffff, 0xffff);//提示框
					switch(Language)
						{
						case CHN_HAN:
								Printf24("编码器不匹配!:        线",REMIND_WINDOW_X,REMIND_WINDOW_Y+5,RED_COLOR,1,0xffff);
									break;
						case ENGLISH:
						case INDONSIA:	//印尼
						case PORTUGAL:	//葡萄牙
								Printf16("Encoder not match!:",REMIND_WINDOW_X,REMIND_WINDOW_Y+5,RED_COLOR,1,0xffff);
								break;
						}	
					Printf24(dis_buf,REMIND_WINDOW_X+200,REMIND_WINDOW_Y+5,RED_COLOR,1,0xffff);
					}
			}
		}
	else if(Z_Pulse_err_flag==0)	//----------------编码器  pule
		{
		if(PulseAB_Z_current!=(Z_Pulse>>2))
			{
			PulseAB_Z_current=Z_Pulse>>2;
			SaveCurrentPulseAB();	//保存set  编码器线数
			}
		}
	}
else
	{
	/***
	if(KeyLinkDis_flag==0)
		{
		KeyLinkDis_flag=1;
		GLCD_SetWindow_Fill(KEYBOARD_CHECK_X,KEYBOARD_CHECK_Y,KEYBOARD_CHECK_X+START_PROM_WIDE-1, KEYBOARD_CHECK_Y+START_PROM_HIGH-1, 0xfffff, 0xffff);
		if(KeyboardLink_flag==0) //
			{
			switch(Language)
				{
				case CHN_HAN:
						Printf24("键盘未连接!",KEYBOARD_CHECK_X,KEYBOARD_CHECK_Y+5,RED_COLOR,1,0xffff);
						break;
				case ENGLISH:
						Printf24("Keyboard is off!",KEYBOARD_CHECK_X,KEYBOARD_CHECK_Y+5,RED_COLOR,1,0xffff);
						break;
				case INDONSIA:	//印尼
						Printf24("Keyboard tidak terhubung!",KEYBOARD_CHECK_X,KEYBOARD_CHECK_Y+5,RED_COLOR,1,0xffff);
						break;
				case PORTUGAL:	//葡萄牙
						Printf24("O teclado n?o está conectado!",KEYBOARD_CHECK_X,KEYBOARD_CHECK_Y+5,RED_COLOR,1,0xffff);
						ASCII_Printf("a",ASCII24_MODE,12,24,PUTAO_ZK24, KEYBOARD_CHECK_X+(11*12),KEYBOARD_CHECK_Y+5,RED_COLOR,0xffff);
						break;
				}
			}
		else
			{
			switch(Language)
				{
				case CHN_HAN:
						Printf24("键盘连接正常!",KEYBOARD_CHECK_X,KEYBOARD_CHECK_Y+5,RED_COLOR,1,0xffff);
						break;
				case ENGLISH:
						Printf24("Keyboard is OK!",KEYBOARD_CHECK_X,KEYBOARD_CHECK_Y+5,RED_COLOR,1,0xffff);
						break;
				case INDONSIA:	//印尼
						Printf24("Keyboard dihubungkan!",KEYBOARD_CHECK_X,KEYBOARD_CHECK_Y+5,RED_COLOR,1,0xffff);
						break;
				case PORTUGAL:	//葡萄牙
						Printf24("Teclado conectado corretamente!",KEYBOARD_CHECK_X,KEYBOARD_CHECK_Y+5,RED_COLOR,1,0xffff);
						break;
				}
			}
		}
		**/
	}
}

void Joggle_GoFast(void)
{
Int32U sp_temp;
switch(MotorType)
	{
	case MOTOR_FREQ_5_SPD_RST:
	case MOTOR_FREQ_3_SPD:
	case MOTOR_FREQ_3_SPD_RST:
		switch(JogRunMode)
			{
			case 0:   //前进 后退 ------启动
				if(GoFrontEn_flag==1)   //前进-----------
					{
					if(CurrentSize>Size_MIN)
						{
						sp_temp=CurrentSize-Size_MIN;
						if((sp_temp>50)&&(OutFront_limit==0))
							{
							if((sp_temp<5000)||(OutMiddle_limit==1))  //50mm  中限位
								{
								MoveSpeed=4;// 低速
								}
							else
								{
								if(GoFast_flag==1)
									MoveSpeed=1;    //高速
								else
									MoveSpeed=3;	//  中速
								}
							SetMotorSpeed(MoveSpeed);
							MoveForward();//前进
							JogRunMode=1;
							//Run_flag=1;
							}
						}
					}
				else if(GoBackEn_flag==1) //后退--------
					{
					if(Size_MAX>CurrentSize)
						{
						sp_temp=Size_MAX-CurrentSize;
						if((sp_temp>50)||(OutBack_limit==0))
							{
							if(sp_temp<5000)
								{
								MoveSpeed=4;// 低速
								}
							else
								{
								if(GoFast_flag==1)
									MoveSpeed=1;    //高速
								else
									MoveSpeed=3;	//  中速
								}
							SetMotorSpeed(MoveSpeed);
							MoveBack(); //后退
							JogRunMode=4;
							//Run_flag=1;
							}
						}
					}
					break;
			case 1:  //高速 前进
				if(GoFrontEn_flag==1)
					{
					if(Wheel_limit!=1)
						{
						if(PressStop_check()==0)
							{
							sp_temp=CurrentSize-Size_MIN;
							if(OutFront_limit==0)  //
								{
								if(sp_temp>VirtualTargetSizeGap)
									{
									if((sp_temp<5000)||(OutMiddle_limit==1))  //50mm  中限位
										{
										MoveSpeed=4;// 低速
										SetMotorSpeed(MoveSpeed);
										JogRunMode=2;
										}
									}
								else  //电子前极限 停止
									{
									MoveStop();
									JogRunMode=3;
									//Run_flag=0;
									}
								}
							else  //外部前限位   停止
								{
								//MoveSpeed=5;
								//SetMotorSpeed(MoveSpeed);
								MoveStop();//==============================
								JogRunMode=3;
								//ForceStop_flag=1;
								}
							}
						else         //压纸  停机
							{
							MoveStop();
							JogRunMode=3;
							}
						}
					else  //
						{
						MoveStop();
						JogRunMode=3;
						}
					}
				else  //按键释放 停止
					{
					//MoveSpeed=5;
					//SetMotorSpeed(MoveSpeed);
					MoveStop();//==============================
					JogRunMode=3;
					//ForceStop_flag=1;
					}
						break;
			case 2:  //低速  前进
				if(GoFrontEn_flag==1)
					{
					if(Wheel_limit!=1)
						{
						if(PressStop_check()==0)
							{
							sp_temp=CurrentSize-Size_MIN;
							if((sp_temp<VirtualTargetSizeGap)||(OutFront_limit==1))//到前限位    停止
								{
								MoveStop();
								JogRunMode=3;
								//Run_flag=0;
								}
							}
						else   //压纸  停机
							{
							MoveStop();
							JogRunMode=3;
							//Run_flag=0;
							}
						}
					else
						{
						MoveStop();
						JogRunMode=3;
						//Run_flag=0;
						}
					}
				else  //按键释放 停止
					{
					MoveStop();
					JogRunMode=3;
					//Run_flag=0;
					}
						break;
			case 3:  //前进停止后
				
						break;
			case 4:  //高速 后退
				if(GoBackEn_flag==1)
					{
					if(Wheel_limit!=1)
						{
						sp_temp=Size_MAX-CurrentSize;
						if(OutBack_limit==0)
							{
							if(sp_temp>VirtualTargetSizeGap)
								{
								if(sp_temp<5000)
									{
									MoveSpeed=4;// 低速
									SetMotorSpeed(MoveSpeed);
									JogRunMode=5;
									}
								}
							else//电子后极限 停止
								{
								MoveStop();
								JogRunMode=6;
								Run_flag=0;
								}
							}
						else  //外部 后极限  停止
							{
							//MoveSpeed=5;
							//SetMotorSpeed(MoveSpeed);
							MoveStop();//========================
							JogRunMode=6;
							//ForceStop_flag=1;
							}
						}
					else
						{
						MoveStop();//========================
						JogRunMode=6;
						}
					}
				else//按键释放 停止
					{
					//MoveSpeed=5;
					//SetMotorSpeed(MoveSpeed);
					MoveStop();//========================
					JogRunMode=6;
					//ForceStop_flag=1;
					}
						break;			
			case 5: //低速 后退
				if(GoBackEn_flag==1)
					{
					if(Wheel_limit!=1)
						{
						sp_temp=Size_MAX-CurrentSize;
						if((sp_temp<VirtualTargetSizeGap)||(OutBack_limit==1))  //停止
							{
							MoveStop();
							JogRunMode=6;
							Run_flag=0;
							}
						}
					else
						{
						MoveStop();
						JogRunMode=6;
						}
					}
				else//按键释放 停止
					{
					MoveStop();
					JogRunMode=6;
					Run_flag=0;
					}
						break;
			case 6: //后退停止后
				
						break;
			}
			break;
	// // case MOTOR_DC_SERVO:
	// // case MOTOR_DC670_SERVO:
		// // switch(JogRunMode)
			// // {
			// // case 0:
				// // if(ServoMoving_flag==0)
					// // {
					// // if(GoFrontEn_flag==1)   //前进--------
						// // {
						// // sp_temp=Size_MIN;
						// // DCServoMove_To(sp_temp,JOG_MOVE);
						// // JogRunMode++;
						// // }
					// // else if(GoBackEn_flag==1)  //后退--------
						// // {
						// // sp_temp=Size_MAX;
						// // DCServoMove_To(sp_temp,JOG_MOVE);
						// // JogRunMode=4;
						// // }
					// // }
					// // break;
			// // case 1:		//前进--------中
				// // if(GoFrontEn_flag==0)   
					// // {
					// // //if(ServoMoving_flag==1)
						// // DCServoStop();  //停止运行
					// // JogRunMode++;	
					// // ServoStopTime=0;
					// // }
				// // else
					// // {
					// // if(PressStop_check()!=0) //压纸 停机
						// // {
						// // DCServoStop();  //停止运行
						// // JogRunMode++;	
						// // ServoStopTime=0;
						// // }
					// // }
					// // break;
			// // case 2: //前进 停止后------
				// // if(ServoMoving_flag==1)
					// // {
					// // ServoStopTime++;
					// // if(ServoStopTime>=1400)
						// // {
						// // DCServoStop();  //停止运行
						// // ServoStopTime=0;
						// // }
					// // }
				// // else
					// // {
					// // JogRunMode++;
					// // }
					// // break;
			// // case 3:
					// // break;
			// // //----------------------------------------------后退---------		
			// // case 4:		//后退--------中
				// // if(GoBackEn_flag==0)   
					// // {
					// // //if(ServoMoving_flag==1)
						// // DCServoStop();  //停止运行
					// // JogRunMode++;
					// // ServoStopTime=0;	
					// // }
					// // break;
			// // case 5:	//后退 停止后------
				// // if(ServoMoving_flag==1)
					// // {
					// // ServoStopTime++;
					// // if(ServoStopTime>=1400)
						// // {
						// // DCServoStop();  //停止运行
						// // ServoStopTime=0;
						// // }
					// // }
				// // else
					// // {
					// // JogRunMode++;
					// // }
					// // break;
			// // case 6:
					// // break;
			// // }
		
			// // break;
	case MOTOR_AC_SERVO:
	case MOTOR_AC_SERVO_REV:
	case MOTOR_AC_A6_SERVO:
		switch(JogRunMode)
			{
			case 0:
				if(GoFrontEn_flag==1)   //前进-----------
					{
					if(CurrentSize>Size_MIN)
						{
						sp_temp=CurrentSize-Size_MIN;
						if((sp_temp>50)&&(OutFront_limit==0))
							{
							if((sp_temp<5000)||(OutMiddle_limit==1))  //50mm  中限位
								{
								ACMotorGoForward();	//前进
								}
							else
							{
							if(GoFast_flag==1)
								ACMotorGoFastForward();  // 快进
							else
									ACMotorGoForward();	//前进
								}
							JogRunMode=1;
							}
						}
					}
				else if(GoBackEn_flag==1) //后退--------
					{
					if(Size_MAX>CurrentSize)
						{
						sp_temp=Size_MAX-CurrentSize;
						if((sp_temp>50)||(OutBack_limit==0))
							{
							if(sp_temp<5000)
								{
								ACMotorGoBack();  //后退
								}
							else
							{
							if(GoFast_flag==1)
								ACMotorGoFastBack();  //快退
							else
								ACMotorGoBack();  //后退
								}
							JogRunMode=4;
							//Run_flag=1;
							}
						}
					}
				break;
			case 1:  //前进 中
				if(GoFrontEn_flag==1)
					{
					if(PressStop_check()==0)
						{
						if(OutFront_limit==1)//到前限位    停止----------------------
							{
							ACServoStop();  //交流伺服	停止
							JogRunMode=3;
							}
						else
							{
							if(OutMiddle_limit==1)  //中 限位
								{
								if(Hold_Up_flag==1)  //托板  高  停止-----------------------
									{
									ACServoStop();  //交流伺服	停止
									JogRunMode=3;
									}
								}
							else
								{
								if(CurrentSize<(Size_MIN+4000)&&CurrentSize>Size_MIN)
									{
									AC_ChangeSPD();  //速度改变
									JogRunMode=2;
									}
								else
									{
									if(CurrentSize<(Size_MIN+1)&&flagqyx==1)  //电子  极限--------------------
										{
										ACServoStop();  //交流伺服	停止
										JogRunMode=3;
										}
									}

								}
							}
						}
					else   //压纸  停机
						{
						ACServoStop();  //交流伺服	停止
						JogRunMode=3;
						//Run_flag=0;
						}
					}
				else
					{
					ACServoStop();  //交流伺服	停止
					JogRunMode=3;
					}
				break;
			case 2:  //前进   低速
				if(GoFrontEn_flag==1)
					{
					if(PressStop_check()==0)
						{
						if(OutFront_limit==1)//到前限位    停止
							{
							ACServoStop();  //交流伺服	停止
							JogRunMode=3;
							}
						else
							{
							if(OutMiddle_limit==1)  //中 限位
								{
								if(Hold_Up_flag==1)  //托板  高  停止-----------------------
									{
									ACServoStop();  //交流伺服	停止
									JogRunMode=3;
									}
								}
							else
								{
								if(CurrentSize<(Size_MIN+1)&&flagqyx==1)  //电子  极限
									{
									ACServoStop();  //交流伺服	停止
									JogRunMode=3;
									}
								}
							}
						}
					else   //压纸  停机
						{
						ACServoStop();  //交流伺服	停止
						JogRunMode=3;
						//Run_flag=0;
						}
					}
				else
					{
					ACServoStop();  //交流伺服	停止
					JogRunMode=3;
					}	
				break;
			case 3:   //前进  停止后
				
				break;
			case 4:  //后退 运行
				if(GoBackEn_flag==1)
					{
					if(OutBack_limit==1)  //后限位  停止
						{
						ACServoStop();  //交流伺服	停止
						JogRunMode=5;
						}
					else
						{
						if(CurrentSize>=Size_MAX&&flagqyx==2)
							{
							ACServoStop();  //交流伺服	停止
							JogRunMode=5;
							}
						}
					}
				else
					{
					ACServoStop();  //交流伺服	停止
					JogRunMode=5;
					}
				break;
			case 5:  //停止 后
				break;
			}
			break;
	}

}

void FreqRuningLimit_ctrl(void)  //运行中  到外部信号 停止
{
Int32U tt;
if(Wheel_limit!=1)
	{
	if(Backward_flag==1)  //后退
		{
		// tt=Size_MAX-CurrentSize;
		// if((tt<VirtualTargetSizeGap)||(OutBack_limit==1))  //停止
		if(OutBack_limit==1)  //停止
			{
			SelfLockEn_flag=0; //取消自锁
			ToTargetStop_flag=0;
			MoveStop();
			ForceStop_flag=0;
			BackStop_flag=0;
			Backward_flag=0;
			Forward_flag=0;
			Run_flag=0;
			InTargetPosit_flag=0;	//目标位置
			TargetSize=0;
			BeforeKnife_offset_in=0;
			AutoPushRun_flag=0;
			}
		}
	else //if(Forward_flag==1)    //前进
		{
		if(PressStop_check()==0)
			{
			// tt=CurrentSize-Size_MIN;
			// if((tt<VirtualTargetSizeGap)||(OutFront_limit==1))//到前限位    停止
			if(OutFront_limit==1)//到前限位    停止
				{
				SelfLockEn_flag=0; //取消自锁
				ToTargetStop_flag=0;
				MoveStop();
				ForceStop_flag=0;
				BackStop_flag=0;
				Backward_flag=0;
				Forward_flag=0;
				Run_flag=0;
				InTargetPosit_flag=0;	//目标位置
				TargetSize=0;
				BeforeKnife_offset_in=0;
				AutoPushRun_flag=0;
				}
			else
				{
				// if(TargetSize<Size_MIN)
				if(TargetSize<MiddleLimit)
					{
					// tt=MiddleLimit-TargetSize;
					// if((tt<5000)||(OutMiddle_limit==1))
					if(OutMiddle_limit==1)
						{
						if(MoveSpeed!=4)
							{
							MoveSpeed=4;
							SetMotorSpeed(MoveSpeed);
							}
						}
					}
				}

			}
		else //压纸停机
			{
			SelfLockEn_flag=0; //取消自锁
			ToTargetStop_flag=0;
			MoveStop();
			ForceStop_flag=0;
			BackStop_flag=0;
			Backward_flag=0;
			Forward_flag=0;
			Run_flag=0;
			InTargetPosit_flag=0;	//目标位置
			TargetSize=0;
			BeforeKnife_offset_in=0;
			AutoPushRun_flag=0;
			}
		}
	}
else
	{
	SelfLockEn_flag=0; //取消自锁
	ToTargetStop_flag=0;
	MoveStop();
	ForceStop_flag=0;
	BackStop_flag=0;
	Backward_flag=0;
	Forward_flag=0;
	Run_flag=0;
	InTargetPosit_flag=0;	//目标位置
	TargetSize=0;
	BeforeKnife_offset_in=0;
	AutoPushRun_flag=0;
	}
}

void ServoRunning_ctrl(void) //直流伺服 运行控制
{
Int32U speed_servo;
Int32U temp;
if(ServoStartDelayTime<1000)
	{
	ServoStartDelayTime++;
	if(ServoStartDelayTime>=900)
		{
		if(ServoSendCou<1)
			{
			if(NowSize_last>CurrentSize)
				speed_servo=NowSize_last-CurrentSize;
			else
				speed_servo=CurrentSize-NowSize_last;
			if(speed_servo<1)
				DcServoStartRun_exec(TargetSize);
			ServoSendCou++;
			}
		}
	ForceStopTime=0;
	}
else    //运行起来 后
	{
	if(ServoMoving_flag==0)  //  已停止---------
		{
		if(CurrentSize==TargetSize)//自动停止---------
			{
			RunStop_flag=1;
			stop_time=0;
			ServoPressStop_flag=0;
			Run_flag=0;
			}
		else		//限位 强制停止----------
			{
			if(ForceStopTime<1200)
				ForceStopTime++;
				//--------------
			if(ForceStopTime==800)
				{
				ForceStopSize=CurrentSize;
				}
			else
				{
				if(ForceStopTime==1000)
					{
					if(ForceStopSize==CurrentSize)
						{
						RunStop_flag=1;
						stop_time=0;
						ServoPressStop_flag=0;
						Run_flag=0;
						}
					}
				}
			}
		}
	else
		{
		if(ServoPressStop_flag==0)
			{
			
			
			if(AutoPushRun_flag==1)//自动  推纸 --------------------------------
				{
				if(CurrentSize<=TargetSize+300)
					{
					ServoAutoPushFinish_flag=1;
					
					RunStop_flag=1;
					stop_time=200;
					Run_flag=0;
					}
				}
			
			if(CurrentSize>TargetSize) //前进中
				{
				if(PressStop_check()!=0) //压纸 停机----------
					{
					DCServoStop();  //停止运行
					ServoPressStop_flag=1;
					}
				}
			
			}
		
		}
		
	if(ServoBack_flag==1)   //后退中
		{
		if(CurrentSize>=(TargetSize+300))
			{
			if(ChangeTarget_flag==0)
				{
				DCServoMove_To(TargetSize,RUN_MOVE);
				ChangeTarget_flag=1;
				ServoBack_flag=0;
				}
			}
		}

	//------------提前bell
	if(AutoPushRun_flag==0)
		{
		if(ServoBack_flag==0)   //
			{
			if(BellStart_flag==0)
				{
				if(CurrentSize>TargetSize)
					{
					temp=CurrentSize-TargetSize;
					}
				else
					{
					temp=TargetSize-CurrentSize;
					}
				if(temp<100)  //提前位置
					{
					BellStart_flag=1;
					
					TargetBell_flag=1;  //蜂鸣器 启动
					TargetBell_mode=0;
					}
				}
			}
		
		}
	}
}

void FreqWorkStart_check(void)  //工作模式前  准备
{
if(StartCheck_mode!=10)
	OutLimit_check(); //外部限位

switch(StartCheck_mode)
	{
	case 0:
			if(senor==1)    //1   原点正常
				{
				if(OriginalError_flag==1)
					{
					CurrentArea_recover1(START_PROMPT_X1, START_PROMPT_Y1,    START_PROM_WIDE, START_PROM_HIGH);
					OriginalError_flag=0;//原点故障  清除
					BackLimitError_flag=0;
					RunDisplay_flag=0;         //后极限正常  则检测运行键/////////////////
					PushRstKey_flag=0; 
					}
				if(OutBack_limit==1)//后限位断开
					{
					if(BackLimitError_flag==0)
						{
						GLCD_SetWindow_Fill(START_PROMPT_X1, START_PROMPT_Y1, START_PROMPT_X1+START_PROM_WIDE-1, START_PROMPT_Y1+START_PROM_HIGH-1, 0xfffff, 0xffff);//提示
						switch(Language)
							{
							case CHN_HAN:
									Printf24("后限位断开!",START_PROMPT_X1,START_PROMPT_Y1+5,RED_COLOR,1,0xffff);
									break;
							case ENGLISH:
									Printf24("Back-Limit is off!",START_PROMPT_X1,START_PROMPT_Y1+5,RED_COLOR,1,0xffff);
									break;
							case INDONSIA:	//印尼
									Printf24("Setelah melepaskan batas!",START_PROMPT_X1,START_PROMPT_Y1+5,RED_COLOR,1,0xffff);
									break;
							case PORTUGAL:	//葡萄牙
									Printf24("Desligue o limite traseiro!",START_PROMPT_X1,START_PROMPT_Y1+5,RED_COLOR,1,0xffff);
									break;
							}
						BackLimitError_flag=1;
						}
					if(OutFront_limit==0)
						{
						StartCheck_mode=3;
						RunDisplay_flag=0;         //前极限正常  则检测运行键/////////////////
						PushRstKey_flag=0; 
						}
					}
				else  //2   后极限正常
					{
					// if((BackLimitError_flag|OriginalError_flag)==1)
					if(BackLimitError_flag==1)
						CurrentArea_recover1(START_PROMPT_X1, START_PROMPT_Y1,    START_PROM_WIDE, START_PROM_HIGH);
					BackLimitError_flag=0;//后极限故障  清除
					OriginalError_flag=0;//原点故障  清除
					StartCheck_mode=3;    
					RunDisplay_flag=0;         //后极限正常  则检测运行键/////////////////
					PushRstKey_flag=0; 
					}
				FrontLimitDis_flag=0;
				}
			else     //原点故障
				{
				if(OriginalError_flag==0)
						{
						GLCD_SetWindow_Fill(START_PROMPT_X1, START_PROMPT_Y1,   START_PROMPT_X1+START_PROM_WIDE-1, START_PROMPT_Y1+START_PROM_HIGH-1, 0xfffff, 0xffff);//提示
						switch(Language)
							{
							case CHN_HAN:
									Printf24("原点故障!",START_PROMPT_X1,START_PROMPT_Y1+5,RED_COLOR,1,0xffff);
									break;
							case ENGLISH:
									Printf24("Original fault!",START_PROMPT_X1,START_PROMPT_Y1+5,RED_COLOR,1,0xffff);
									break;
							case INDONSIA:	//印尼
									Printf24("Asal kesalahan!",START_PROMPT_X1,START_PROMPT_Y1+5,RED_COLOR,1,0xffff);
									break;	
							case PORTUGAL:	//葡萄牙
									Printf24("come ando falha!",START_PROMPT_X1,START_PROMPT_Y1+5,RED_COLOR,1,0xffff);
									ASCII_Printf("c",ASCII24_MODE,12,24,PUTAO_ZK24, START_PROMPT_X1+(4*12),START_PROMPT_Y1+5,RED_COLOR,0xffff);
									break;	
							}	
						OriginalError_flag=1;
						}
				// if((BackLimitError_flag|OriginalError_flag)==1)
						// CurrentArea_recover1(START_PROMPT_X1, START_PROMPT_Y1,    START_PROM_WIDE, START_PROM_HIGH);
				BackLimitError_flag=0;//后极限故障  清除
				// OriginalError_flag=0;//原点故障  清除	
				// PushResetPrompt_dis();  //开机 推纸器 复位  提示
				// StartCheck_mode++;
				// PushRstKey_flag=0;	
				if(RunDisplay_flag==1)	
					{
					CurrentArea_recover2(START_PROMPT_X2, START_PROMPT_Y2,    START_PROM_WIDE, START_PROM_HIGH);
					RunDisplay_flag=0;
					}
				}
				
				break;
	case 1:		//等待 推纸器  复位启动（确定键）
			// if((OutBack_limit==0)&&(senor==1)) //原点 后极限 复位正常
			if(senor==1) //原点  复位正常
				{			//复位 提示  消失
				CurrentArea_recover3(PUSH_RESET_PROMPT_X1, PUSH_RESET_PROMPT_Y1, PUSH_RESET_PROMPT_WIDE, PUSH_RESET_PROMPT_HIGH);
				StartCheck_mode=0;//3;    
				RunDisplay_flag=0;         //后极限正常  则检测运行键////////////////////
				PushRstKey_flag=0;
				}
			else
				{
				// // if((OutBack_limit^senor)!=1)
					// // {
					// // CurrentArea_recover3(PUSH_RESET_PROMPT_X1, PUSH_RESET_PROMPT_Y1, PUSH_RESET_PROMPT_WIDE, PUSH_RESET_PROMPT_HIGH);
					// // StartCheck_mode=0;
					// // }
				}
				break;
	case 2:		// 推纸器  复位中
			PusherResetTime++;
			if(PusherResetTime>=6000) //8s
				{
				MoveStop();
				StartCheck_mode++;
				RunDisplay_flag=0;//后极限正常  则检测运行键////////////////////
				if((OutBack_limit==0)&&(senor==1)) //原点 后极限 复位正常
					{
					CurrentArea_recover1(START_PROMPT_X1, START_PROMPT_Y1,    START_PROM_WIDE, START_PROM_HIGH);
					OriginalError_flag=0;//原点故障  清除
					}
				else
					{
					StartCheck_mode=0; //未复位 则重新检测
					PushRstKey_flag=0;
					}
				}
				break;	
		//--------------------------------------------------------------------------------------------------
	case 3:			//
			if(OutBack_limit==0)//if((OutFront_limit==0)&&(OutMiddle_limit==0)&&(Wheel_limit==0))//等待其他 极限正常  则检测 (运行键)
				{
				if((OutMiddle_limit==0)&&(Wheel_limit==0))
					{
					if(senor==1)
						{
						if(OutBack_limit==0)
							{
							if(PushRstKey_flag==0)
								{
								if(RunDisplay_flag==0)
									{
									RunDisplay_flag=1;
									GLCD_SetWindow_Fill( START_PROMPT_X2, START_PROMPT_Y2, START_PROMPT_X2-1+START_PROM_WIDE, START_PROMPT_Y2-1+30, 0xfffff, 0xffff);//提示框
									switch(Language)
										{
										case CHN_HAN:
												Printf24("电脑检测完成,请按运行键!>点此处",START_PROMPT_X2,START_PROMPT_Y2+5,RED_COLOR,1,0xffff);
													break;
										case ENGLISH:
												Printf24("Computer testing OK, press the RUN key!",START_PROMPT_X2,START_PROMPT_Y2+5,RED_COLOR,1,0xffff);
													break;
										case INDONSIA:	//印尼
												Printf24("Tes komputer lengkap, tekan tombol Run!",START_PROMPT_X2,START_PROMPT_Y2+5,RED_COLOR,1,0xffff);
													break;
										case PORTUGAL:	//葡萄牙
												Printf16("Computador auto-teste estiver concluí",START_PROMPT_X2,START_PROMPT_Y2+5,RED_COLOR,1,0xffff);
												Printf16("                                     do, pressione o bot o de execu  o!",START_PROMPT_X2,START_PROMPT_Y2+5,RED_COLOR,0,0xffff);
												ASCII_Printf("a",ASCII16_MODE,8,16,PUTAO_ZK16, START_PROMPT_X2+(56*8),START_PROMPT_Y2+5,RED_COLOR,0xffff);
												ASCII_Printf("ca",ASCII16_MODE,8,16,PUTAO_ZK16, START_PROMPT_X2+(67*8),START_PROMPT_Y2+5,RED_COLOR,0xffff);
												break;
										}
									}
								StartCheck_mode++;
								}
							else  //-------------推纸器自动复位后
								{
								if(PassCodeEn_flag==0)
									{
									MoveSpeed=2;
									SetMotorSpeed(MoveSpeed);//中高速
									MoveBack(); //后退
									//CurrentArea_recover2(REMIND_WINDOW_X, REMIND_WINDOW_Y, START_PROM_WIDE, START_PROM_HIGH);
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
									StartCheck_mode=9;//5
									CodeSensorTime_AB=0;
									}
								else   //-------------启动  密码提示
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
									StartCheck_mode++;
									}
								}
							}
						else
							{
							StartCheck_mode=0;
							}
						//---------20150629
						if(OriginalError_flag==1)
							{
							CurrentArea_recover1(START_PROMPT_X1, START_PROMPT_Y1,    START_PROM_WIDE, START_PROM_HIGH);
							OriginalError_flag=0;//原点故障  清除
							}
						}
					}
				else//RunDisplay_flag=0;
					StartCheck_mode=0;
				}
			else	//后极限异常
				{
				if(OutFront_limit==0)//前极限ok
					{
					StartCheck_mode	=5;
					}
				else
					{
					StartCheck_mode	=0;
					GLCD_SetWindow_Fill(START_PROMPT_X2 , START_PROMPT_Y2,START_PROMPT_X2-1+START_PROM_WIDE, START_PROMPT_Y2-1+30, 0xfffff, 0xffff);//提示
					switch(Language)
						{
						case CHN_HAN:
							Printf24("前限位断开!",START_PROMPT_X2,START_PROMPT_Y2+5,RED_COLOR,1,0xffff);
								break;
						case ENGLISH:
							Printf24("Front-Limit is off!",START_PROMPT_X2,START_PROMPT_Y2+5,RED_COLOR,1,0xffff);
								break;
						case INDONSIA:	//印尼
							Printf24("Lepaskan batas depan!",START_PROMPT_X2,START_PROMPT_Y2+5,RED_COLOR,1,0xffff);
								break;
						case PORTUGAL:	//葡萄牙
							Printf24("A primeira parada édesconectada",START_PROMPT_X2,START_PROMPT_Y2+5,RED_COLOR,1,0xffff);
								break;
						}	
					}
				}
				break;
	case 4:  //等待   运行键按下   中-------------------------后极限ok 进入
			if(OutBack_limit==1)// if((OutFront_limit==1)||(OutMiddle_limit==1)||(Wheel_limit==1)||(OutBack_limit==1)||(senor==0))
				{                //后极限有异常
				RunDisplay_flag=0;//清除运行提示
				if(senor==0)//if((OutBack_limit==1)||(senor==0))
					{
					if((OutFront_limit==0)&&(OutMiddle_limit==0)&&(Wheel_limit==0))
						{
						CurrentArea_recover2(START_PROMPT_X2, START_PROMPT_Y2,    START_PROM_WIDE, START_PROM_HIGH);	
						}
					}
				StartCheck_mode=0;
				}
				
			if(OutFront_limit==1)//前极限异常
				{
				if(FrontLimitDis_flag==0)
					{
					FrontLimitDis_flag=1;
					GLCD_SetWindow_Fill(START_PROMPT_X2 , START_PROMPT_Y2,START_PROMPT_X2-1+START_PROM_WIDE, START_PROMPT_Y2-1+30, 0xfffff, 0xffff);//提示
					switch(Language)
						{
						case CHN_HAN:
							Printf24("前限位断开!",START_PROMPT_X2,START_PROMPT_Y2+5,RED_COLOR,1,0xffff);
								break;
						case ENGLISH:
							Printf24("Front-Limit is off!",START_PROMPT_X2,START_PROMPT_Y2+5,RED_COLOR,1,0xffff);
								break;
						case INDONSIA:	//印尼
							Printf24("Lepaskan batas depan!",START_PROMPT_X2,START_PROMPT_Y2+5,RED_COLOR,1,0xffff);
								break;
						case PORTUGAL:	//葡萄牙
							Printf24("A primeira parada édesconectada",START_PROMPT_X2,START_PROMPT_Y2+5,RED_COLOR,1,0xffff);
								break;
						}	
					}
				}
			else//
				{
				if(FrontLimitDis_flag==1)	
					{
					FrontLimitDis_flag=0;
					StartCheck_mode=0;
					}
				}
				break;
	case 5:   //等待   运行键按下   中-------------------------only后极限异常进入	
				if(OutFront_limit==1)//前极限异常
					{
					StartCheck_mode	=0;
					GLCD_SetWindow_Fill(START_PROMPT_X2 , START_PROMPT_Y2,START_PROMPT_X2-1+START_PROM_WIDE, START_PROMPT_Y2-1+30, 0xfffff, 0xffff);//提示
					switch(Language)
						{
						case CHN_HAN:
							Printf24("前限位断开!",START_PROMPT_X2,START_PROMPT_Y2+5,RED_COLOR,1,0xffff);
								break;
						case ENGLISH:
							Printf24("Front-Limit is off!",START_PROMPT_X2,START_PROMPT_Y2+5,RED_COLOR,1,0xffff);
								break;
						case INDONSIA:	//印尼
							Printf24("Lepaskan batas depan!",START_PROMPT_X2,START_PROMPT_Y2+5,RED_COLOR,1,0xffff);
								break;
						case PORTUGAL:	//葡萄牙
							Printf24("A primeira parada édesconectada",START_PROMPT_X2,START_PROMPT_Y2+5,RED_COLOR,1,0xffff);
								break;
						}
					}
				else		//前极限---ok 恢复
					{
					if(RunDisplay_flag==0)
						{
						RunDisplay_flag=1;
						GLCD_SetWindow_Fill( START_PROMPT_X2, START_PROMPT_Y2, START_PROMPT_X2-1+START_PROM_WIDE, START_PROMPT_Y2-1+30, 0xfffff, 0xffff);//提示框
						switch(Language)
							{
							case CHN_HAN:
									Printf24("电脑检测完成,请按运行键!>点此处",START_PROMPT_X2,START_PROMPT_Y2+5,RED_COLOR,1,0xffff);
										break;
							case ENGLISH:
									Printf24("Computer testing OK, press the RUN key!",START_PROMPT_X2,START_PROMPT_Y2+5,RED_COLOR,1,0xffff);
										break;
							case INDONSIA:	//印尼
									Printf24("Tes komputer lengkap, tekan tombol Run!",START_PROMPT_X2,START_PROMPT_Y2+5,RED_COLOR,1,0xffff);
										break;
							case PORTUGAL:	//葡萄牙
									Printf16("Computador auto-teste estiver concluí",START_PROMPT_X2,START_PROMPT_Y2+5,RED_COLOR,1,0xffff);
									Printf16("                                     do, pressione o bot o de execu  o!",START_PROMPT_X2,START_PROMPT_Y2+5,RED_COLOR,0,0xffff);
									ASCII_Printf("a",ASCII16_MODE,8,16,PUTAO_ZK16, START_PROMPT_X2+(56*8),START_PROMPT_Y2+5,RED_COLOR,0xffff);
									ASCII_Printf("ca",ASCII16_MODE,8,16,PUTAO_ZK16, START_PROMPT_X2+(67*8),START_PROMPT_Y2+5,RED_COLOR,0xffff);
									break;
							}
						}
					if(OutBack_limit==0)
						{
						StartCheck_mode--;//前、后极限都正常
						}
					}
				break;
				
	case 6:  //前进   中-----后极限异常 进入			
			if(OutFront_limit==1)//前极限
				{
				MoveStop();
				StartCheck_mode=0;
				}
			else
				{
				stop_time=0;
				StartCheck_mode++;
				}
				break;
	case 7:			
			if(OutFront_limit==1)//前极限
				{
				MoveStop();
				StartCheck_mode=0;
				}
			else
				{
				stop_time++;
				if(stop_time>=6000)
					{
					stop_time=0;
					MoveStop();
					if(OutBack_limit==0)
						StartCheck_mode++;
					else
						StartCheck_mode=0;
					}
				}
				break;
	case 8:			//前进一段距离， 后极限	恢复正常后----------	开始  后退正常开机步骤
			stop_time++;
			if(stop_time>=1000)
				{
				stop_time=0;
				if(PassCodeEn_flag==0)
					{
					MoveSpeed=2;
					SetMotorSpeed(MoveSpeed);//中高速
					MoveBack(); //后退
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
					StartCheck_mode++;
					CodeSensorTime_AB=0;
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
				break;
							//--------------------------//////////////////////////0000000000000000000000000000000000000000000///////////////////////////
	case 9://5:  //高速后退   中-----后极限ok 进入     
			//if((OutFront_limit==0)&&(OutMiddle_limit==0)&&(Wheel_limit==0)&&(OutBack_limit==0))
			if(OutBack_limit==0)
				{
				if(senor==0)
					{
					StartCheck_mode+=3;
					stop_time=0;
					}
				else
					{
					if(CodeSensorTime_AB==0)
						{
						Asensor_temp=Encoder_A_IN;
						Bsensor_temp=Encoder_B_IN;
						ABsensor_temp=0;
						}
					if(CodeSensorTime_AB<5000)//5s
						{
						CodeSensorTime_AB++;
						if(Asensor_temp!=Encoder_A_IN)
							ABsensor_temp|=1;
						if(Bsensor_temp!=Encoder_B_IN)
							ABsensor_temp|=2;
						}
					else
						{
						if(ABsensor_temp<3)  //编码器故障
							{
							GLCD_SetWindow_Fill( START_PROMPT_X2, START_PROMPT_Y2, START_PROMPT_X2-1+START_PROM_WIDE, START_PROMPT_Y2-1+30, 0xfffff, 0xffff);//提示框
							switch(Language)
								{
								case CHN_HAN:
										Printf24("编码器故障!",START_PROMPT_X2,START_PROMPT_Y2+5,RED_COLOR,1,0xffff);
											break;
								case ENGLISH:
										Printf24("Encoder fault!",START_PROMPT_X2,START_PROMPT_Y2+5,RED_COLOR,1,0xffff);
											break;
								case INDONSIA:	//印尼
										Printf24("Encoder kesalahan!",START_PROMPT_X2,START_PROMPT_Y2+5,RED_COLOR,1,0xffff);
											break;
								case PORTUGAL:	//葡萄牙
										Printf24("Culpa Encoder!",START_PROMPT_X2,START_PROMPT_Y2+5,RED_COLOR,1,0xffff);
											break;
								}
							MoveStop();
							StartCheck_mode++;
							//RunDisplay_flag=0;//清除运行提示
							}
						}
					}
				}
			else   //后极限 异常
				{
				stop_time=0;
				// MoveStop();
				StartCheck_mode+=2;
				}
				break;
	case 10://6:  // 编码器故障   停止----------
			
				break;
				
	case 11:	//----delay---- 增加 后限位&原点 判断-----------------20160123
			if(stop_time<2000)
				{
				stop_time++;
				if(senor==0)//正常到 原点
					{
					StartCheck_mode+=2;
					stop_time=0;
					}	
				}
			else//超出时间差   
				{
				// if(OutBack_limit==1)// 仍然异常
					// {
					stop_time=0;
					MoveStop();
					StartCheck_mode=0;   //停止
					// }
				}
				break;
	case 12://7:  // 去抖动	
			// if((OutFront_limit==0)&&(OutMiddle_limit==0)&&(Wheel_limit==0)&&(OutBack_limit==0))
			if(senor==0)
				{
				stop_time++;
				if(stop_time>=20)
					{
					stop_time=0;
					MoveStop();
					StartCheck_mode++;
					}
				}
			else
				{
				stop_time=0;
				}
				break;
	case 13://8:  //停止后 
			// if((OutFront_limit==0)&&(OutMiddle_limit==0)&&(Wheel_limit==0))
				stop_time++;	
				if(stop_time>=1000)
					{
					MoveSpeed=4;
					SetMotorSpeed(MoveSpeed);  //低速
					MoveForward();//前进
					StartCheck_mode++;
					}
				break;	
	case 14://9:  //低速前进   中
			// if((OutFront_limit==0)&&(OutMiddle_limit==0)&&(Wheel_limit==0)&&(OutBack_limit==0))
			if((OutFront_limit==0)&&(OutMiddle_limit==0)&&(Wheel_limit==0))
				{
				if(senor==1)
					{
					stop_time=0;
					StartCheck_mode++;
					}
				}
			else//极限异常
				{
				MoveStop();
				StartCheck_mode=0;
				}	
				break;
	case 15:  //	  原点为高
			// if((OutFront_limit==0)&&(OutMiddle_limit==0)&&(Wheel_limit==0)&&(OutBack_limit==0))
			if((OutFront_limit==0)&&(OutMiddle_limit==0)&&(Wheel_limit==0))
				{
				if(senor==1)
					{
					stop_time++;	
					if(stop_time>=20)  // Z 脉冲  计数启动
						{
						stop_time=0;
						Zpulse_cou=0;
						StartCheck_mode++;
						}
					}
				else
					{
					stop_time=0;
					}
				}
			else//极限异常
				{
				MoveStop();
				StartCheck_mode=0;
				}		
				break;
	case 16:  //Z脉冲 为高
			// if((OutFront_limit==0)&&(OutMiddle_limit==0)&&(Wheel_limit==0)&&(OutBack_limit==0))
			if((OutFront_limit==0)&&(OutMiddle_limit==0)&&(Wheel_limit==0))
				{
				if(xz==1)
					{
					MoveStop();
					stop_time=0;
					StartCheck_mode++;
					if(Zpulse_cou>(Z_Pulse*2))  //编码器 错误
						{
						EncoderErr_flag=1;
						}
					}
				}
			else//极限异常
				{
				MoveStop();
				StartCheck_mode=0;
				}	
				break;	
	case 17:	         //停止后   进入工作画面
			stop_time++;	
			if(stop_time>=50)
				{
				WorkStart_flag=1;
				WorkMode=AUTO_MODE;//PROG_MODE;//进入 工作画面
				PaperCutEnb_signal=1;
				// TableDis_startcol=RIGHT_ARROW_X; //数据显示起始列
				Knife_order=1;cursor_row=0;     // 在首行 显示 箭头
				ProcessRatio=0xff;
				WorkPic_dis();  //进入 工作画面
				PromptDis_flag=1;
				Size_1page_dis(Knife_order, 0);
				CursorKnife_dis(0,1);//红色光标
				muqiancn=OriginalSize*1000;
				CurrentSize=OriginalSize;
				//Current_last=CurrentSize;
				if(EncoderErr_flag==1)
					{
					PromptDis_flag=0;
					GLCD_SetWindow_Fill( REMIND_WINDOW_X, REMIND_WINDOW_Y, REMIND_WINDOW_X+REMIND_LENGTH, REMIND_WINDOW_Y+30, 0xfffff, 0xffff);//提示框
					switch(Language)
						{
						case CHN_HAN:
							Printf24("尺寸错误,请检查编码器!",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,RED_COLOR,0,0xffff);
									break;
						case ENGLISH:	
							Printf24("Error size,check encoder!",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,RED_COLOR,0,0xffff);
									break;
						case INDONSIA:	//印尼
							Printf16("Salah ukuran,silahkan cek encoder!",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,RED_COLOR,0,0xffff);
									break;
						case PORTUGAL:	//葡萄牙
							Printf16("Tamanho errado,verifique o encoder!",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,RED_COLOR,0,0xffff);
									break;
						}
					}
				}
				break;	
	}
	
//**********************电机手动 控制 复位	
switch(ManualMoveMode)
	{
	case 0:
		if((StartCheck_mode<2)||(StartCheck_mode==4)||(StartCheck_mode==5))
			{
			
			if(GoFrontEn_flag==1)
				{
				if((Wheel_limit==0)&&(OutFront_limit==0))//正常
					{
					if(GoFast_flag==1)
						MoveSpeed=1;    //高速
					else
						MoveSpeed=3;	//  中速
					SetMotorSpeed(MoveSpeed);
					//--------
					MoveForward();//前进
					ManualMoveMode++;
					}
				}
			else if(GoBackEn_flag==1)
				{
				if((Wheel_limit==0)&&(OutBack_limit==0))//正常
					{
					if(GoFast_flag==1)
						MoveSpeed=1;    //高速
					else
						MoveSpeed=3;	//  中速
					SetMotorSpeed(MoveSpeed);
					//--------
					MoveBack();//后退
					ManualMoveMode=3;
					}
				}
			}
			break;
	case 1://前进---------
		if(GoFrontEn_flag==0)	//jog 释放
			{
			MoveSpeed=0;
			MoveStop();
			ManualMoveMode++;
			}
		else
			{
			if((Wheel_limit==1)||(OutFront_limit==1))// 极限异常
				{
				MoveSpeed=0;
				MoveStop();
				ManualMoveMode++;
				}
			}
			break;
	case 2:
			break;
	case 3:
		if(GoBackEn_flag==0)
			{
			MoveSpeed=0;
			MoveStop();
			ManualMoveMode++;
			}
		else
			{
			if((Wheel_limit==1)||(OutBack_limit==1))// 极限异常
				{
				MoveSpeed=0;
				MoveStop();
				ManualMoveMode++;
				}
			}
			break;
	case 4:
			break;		
	}

}

void NowSizeNum_dis(void)//***************************尺寸 显示
{
Int32U size_temp,offset,curr_target;
//------------当前--------------
if(CurrentSize_temp!=CurrentSize)
	{
	if(CurrentSize>TargetSize)
		{
		size_temp=CurrentSize-TargetSize;
		}
	else
		{
		size_temp=TargetSize-CurrentSize;
		}
		
	switch(MotorType)
		{
		case MOTOR_FREQ_5_SPD_RST:
		case MOTOR_FREQ_3_SPD:
		case MOTOR_FREQ_3_SPD_RST:
				if(size_temp>=VirtualTargetSizeGap)
					{
					CurrentSize_temp=CurrentSize;
			/*
					if(SelfLockEn_flag==1)  //自锁 启动-------------------
						{
						MoveSpeed=0;
						MoveSpeedCtrl();  //运行速度控制
						Run_flag=1;
						RunStop_flag=0;
						InTargetPosit_flag=0;	//清目标位置
						}
						*/
					CurrentSize_dis(CurrentSize_temp); //当前尺寸 更新显示
					}
				else 
					{
					if(CurrentSize_temp!=TargetSize)
						{
						CurrentSize_temp=TargetSize;
						CurrentSize_dis(CurrentSize_temp); //当前尺寸 更新显示
						if(MotorType==MOTOR_FREQ_3_SPD)		//20171017
							InTargetPosit_flag=1;	//目标位置
						}
					}
					//---------------气阀控制
				if(MotorType>MOTOR_FREQ_5_SPD_RST)
					{
					if(AirOffDistance>0)	//关气阀距离有效
						{
						if(AirOffOK_flag==0)	//气阀断开 未启动
							{
							if(Forward_flag==1)	//向前
								{
								if(size_temp<=AirOffDistance)
									{
									if(SelfLockEn_flag==0)
										{
										AirOffOK_flag=1;
										RLOUT3_ON;	//RLOUT2_ON;	//气阀断开
										}
									}
								}
							}
						}
					}
				
				break;
		// // case MOTOR_DC_SERVO:
		// // case MOTOR_DC670_SERVO:
				// // if(DcServoGoTarget_flag==1)
					// // {
					// // if(size_temp>DC_VIRTURE_SIZE)
						// // {
						// // CurrentSize_temp=CurrentSize;
						// // CurrentSize_dis(CurrentSize_temp); //当前尺寸 直接显示
						// // }
					// // else
						// // {
						// // if(ServoBack_flag==0)
							// // {
							// // if(CurrentSize_temp!=TargetSize)
								// // {
								// // CurrentSize_temp=TargetSize;
								// // CurrentSize_dis(CurrentSize_temp); //当前尺寸 更新显示
								// // }
							// // }
						// // else
							// // {
							// // CurrentSize_temp=CurrentSize;
							// // CurrentSize_dis(CurrentSize_temp); //当前尺寸 直接显示
							// // }
						// // }
					// // }
				// // else   //直接显示
					// // {
					// // CurrentSize_temp=CurrentSize;
					// // CurrentSize_dis(CurrentSize_temp); //当前尺寸 直接显示
					// // }
				// // break;
		case MOTOR_AC_SERVO:
		case MOTOR_AC_SERVO_REV:
		case MOTOR_AC_A6_SERVO:
				CurrentSize_temp=CurrentSize;
				CurrentSize_dis(CurrentSize_temp); //当前尺寸 直接显示
				
					//---------------气阀控制
				if(AirOffDistance>0)	//关气阀距离有效
					{
					if(AirOffOK_flag==0)	//气阀断开 未启动
						{
						if(qianjin==1)//向前
							{
							if(size_temp<=AirOffDistance)
								{
								if(SelfLockEn_flag==0)
									{
									AirOffOK_flag=1;
									RLOUT3_ON;	//RLOUT2_ON;	//气阀断开
									}
								}
							}
						}
					}
					
				break;
		}	
		
	
		
	}
//*****------刀前--------------
if(CurrentSize_temp<=BeforeKnife_offset)
	{//LED2_OFF;
	if(Unit==UNIT_MM)
		{
		size_temp=BeforeKnife_offset-CurrentSize_temp;
		}
	else	//inch
		{
		if(BeforeKnife_offset_in>0)
			{
			offset=BeforeKnife_offset_in;
			}
		else
			{
			offset=BeforeKnife_offset*100/254;
			}
		if(CurrentSize_temp==(Int32U)(TargetSize_inch*2.54))
			{
			curr_target=TargetSize_inch;
			}
		else
			{
			curr_target=CurrentSize_temp*100/254;
			}
		size_temp=offset-curr_target;
		}
		
	if(size_temp!=BeforeKnifeSize)
		{
		BeforeKnifeSize=size_temp;
		FrontKnifeSize_dis(BeforeKnifeSize);
		if(BeforeKnifeNo_flag==1)  //刀前 显示
			{
			BeforeKnifeNo_flag=0;
			}
		}
	}
else
	{//LED2_ON;
	if(BeforeKnifeNo_flag==0)  //刀前 显示 去除
		{														//testing---------------------
		BeforeKnifeSize=0xffffffff;
		FrontKnifeSize_NOdis();
		BeforeKnifeNo_flag=1;
		}
	}	
}

Int8U PressStop_check(void)//压纸停机  判断
{
Int8U flag;
if(PressValid_flag==0) //压纸 无效
	flag=0;
else
	{
	if((AllPressUp_flag==1)&&(AllKnifeUp_flag==1))
		flag=0;
	else 
		{
		if(AllPressUp_flag==0)
			flag=1;   //压纸故障
		else
			flag=2;  //刀信号故障
		}
		
	}
if(flag!=0)
	{
	PromptDis_flag=0;
	GLCD_SetWindow_Fill( REMIND_WINDOW_X, REMIND_WINDOW_Y, REMIND_WINDOW_X+REMIND_LENGTH, REMIND_WINDOW_Y+30, 0xfffff, 0xffff);//提示框
		if(flag==1)
			{
			switch(Language)
				{
				case CHN_HAN:
						Printf24("压纸不在最高点!",REMIND_WINDOW_X,REMIND_WINDOW_Y+5,RED_COLOR,1,0xffff);
						break;
				case ENGLISH:
						Printf16("Press-Paper isn't in highest!",REMIND_WINDOW_X,REMIND_WINDOW_Y+5,RED_COLOR,1,0xffff);
						break;
				case INDONSIA:	//印尼
						Printf16("Pelat bukanlah titik tertinggi!",REMIND_WINDOW_X,REMIND_WINDOW_Y+5,RED_COLOR,1,0xffff);
						break;
				case PORTUGAL:	//葡萄牙
						Printf16("Platen n?o éo ponto o mais alto!",REMIND_WINDOW_X,REMIND_WINDOW_Y+5,RED_COLOR,1,0xffff);
						ASCII_Printf("a",ASCII16_MODE,8,16,PUTAO_ZK16,REMIND_WINDOW_X+8*8,REMIND_WINDOW_Y+5,RED_COLOR, 0xffff);
						break;
				}
			}
		else
			{
			switch(Language)
				{
				case CHN_HAN:
						Printf24("刀信号故障!",REMIND_WINDOW_X,REMIND_WINDOW_Y+5,RED_COLOR,1,0xffff);
						break;
				case ENGLISH:
						Printf24("Knife signal error!",REMIND_WINDOW_X,REMIND_WINDOW_Y+5,RED_COLOR,1,0xffff);
						break;
				case INDONSIA:	//印尼
						Printf24("Kegagalan sinyal Knife!",REMIND_WINDOW_X,REMIND_WINDOW_Y+5,RED_COLOR,1,0xffff);
						break;
				case PORTUGAL:	//葡萄牙
						Printf24("Falha de sinal Lamina!",REMIND_WINDOW_X,REMIND_WINDOW_Y+5,RED_COLOR,1,0xffff);
						ASCII_Printf("a",ASCII24_MODE,12,24,PUTAO_ZK24_XOR,REMIND_WINDOW_X+12*16,REMIND_WINDOW_Y+5,RED_COLOR, 0xffff);
						break;
				}
			}
	PressStopDis_flag=1;
	}
return flag;	
}


void ServoWorkStart_check(void)  //直流伺服  工作模式前  准备
{
	//ServoDrvInitOK_flag=1;StartCheck_mode=4;
if(ServoDrvInitOK_flag==0)
	{
	ServoDrvSet_Init();//驱动器 初始化
	StartCheck_mode=0;
	RunDisplay_flag=0;
	BackLimitError_flag=0;
	//--------
	/***
	if(KeyLinkDis_flag==0)
		{
		KeyLinkDis_flag=1;
		GLCD_SetWindow_Fill(KEYBOARD_CHECK_X,KEYBOARD_CHECK_Y,KEYBOARD_CHECK_X+START_PROM_WIDE-1, KEYBOARD_CHECK_Y+START_PROM_HIGH-1, 0xfffff, 0xffff);
		if(KeyboardLink_flag==0) //
			{
			switch(Language)
				{
				case CHN_HAN:
						Printf24("键盘未连接!",KEYBOARD_CHECK_X,KEYBOARD_CHECK_Y+5,RED_COLOR,1,0xffff);
						break;
				case ENGLISH:
						Printf24("Keyboard is off!",KEYBOARD_CHECK_X,KEYBOARD_CHECK_Y+5,RED_COLOR,1,0xffff);
						break;
				case INDONSIA:	//印尼
						Printf24("Keyboard tidak terhubung!",KEYBOARD_CHECK_X,KEYBOARD_CHECK_Y+5,RED_COLOR,1,0xffff);
						break;
				case PORTUGAL:	//葡萄牙
						Printf24("O teclado n?o está conectado!",KEYBOARD_CHECK_X,KEYBOARD_CHECK_Y+5,RED_COLOR,1,0xffff);
						ASCII_Printf("a",ASCII24_MODE,12,24,PUTAO_ZK24, KEYBOARD_CHECK_X+(11*12),KEYBOARD_CHECK_Y+5,RED_COLOR,0xffff);
						break;
				}
			}
		else
			{
			switch(Language)
				{
				case CHN_HAN:
						Printf24("键盘连接正常!",KEYBOARD_CHECK_X,KEYBOARD_CHECK_Y+5,RED_COLOR,1,0xffff);
						break;
				case ENGLISH:
						Printf24("Keyboard is OK!",KEYBOARD_CHECK_X,KEYBOARD_CHECK_Y+5,RED_COLOR,1,0xffff);
						break;
				case INDONSIA:	//印尼
						Printf24("Keyboard dihubungkan!",KEYBOARD_CHECK_X,KEYBOARD_CHECK_Y+5,RED_COLOR,1,0xffff);
						break;
				case PORTUGAL:	//葡萄牙
						Printf24("Teclado conectado corretamente!",KEYBOARD_CHECK_X,KEYBOARD_CHECK_Y+5,RED_COLOR,1,0xffff);
						break;
				}
			}
		}
		**/
	}
else
	{
	if(StartCheck_mode!=3)
		OutLimit_check(); //外部限位
	switch(StartCheck_mode)
		{
		case 0:
			if(OutBack_limit==1)
				{
				if(BackLimitError_flag==0)
					{
					GLCD_SetWindow_Fill(START_PROMPT_X1, START_PROMPT_Y1, START_PROMPT_X1+START_PROM_WIDE-1, START_PROMPT_Y1+START_PROM_HIGH-1, 0xfffff, 0xffff);//提示
					switch(Language)
						{
						case CHN_HAN:
								Printf24("后限位断开!",START_PROMPT_X1,START_PROMPT_Y1+5,RED_COLOR,1,0xffff);
								break;
						case ENGLISH:
								Printf24("Back-Limit is off!",START_PROMPT_X1,START_PROMPT_Y1+5,RED_COLOR,1,0xffff);
								break;
						case INDONSIA:	//印尼	
								Printf24("Setelah melepaskan batas!",START_PROMPT_X1,START_PROMPT_Y1+5,RED_COLOR,1,0xffff);
								break;
						case PORTUGAL:	//葡萄牙
								Printf24("Desligue o limite traseiro!",START_PROMPT_X1,START_PROMPT_Y1+5,RED_COLOR,1,0xffff);
								break;
						}
					BackLimitError_flag=1;
					}
				if(RunDisplay_flag==1)
					{
					RunDisplay_flag=0;
					if((OutFront_limit==0)&&(OutMiddle_limit==0)&&(Wheel_limit==0))  //其他极限正常
						CurrentArea_recover2(START_PROMPT_X2, START_PROMPT_Y2,    START_PROM_WIDE, START_PROM_HIGH);
					}
				}
			else
				{
				if(BackLimitError_flag==1)
					{
					BackLimitError_flag=0;
					CurrentArea_recover1(START_PROMPT_X1, START_PROMPT_Y1,    START_PROM_WIDE, START_PROM_HIGH);
					}
				}
				
			if((OutFront_limit==1)||(OutMiddle_limit==1)||(Wheel_limit==1)||(OutBack_limit==1))  //极限异常
				{
				RunDisplay_flag=0;
				}
			else
				{
				if(RunDisplay_flag==0)
					{
					RunDisplay_flag=1;
					GLCD_SetWindow_Fill( START_PROMPT_X2, START_PROMPT_Y2, START_PROMPT_X2-1+START_PROM_WIDE, START_PROMPT_Y2-1+30, 0xfffff, 0xffff);//提示框
					switch(Language)
						{
						case CHN_HAN:
								Printf24("电脑检测完成,请按运行键!>点此处",START_PROMPT_X2,START_PROMPT_Y2+5,RED_COLOR,1,0xffff);
									break;
						case ENGLISH:
								Printf24("Computer testing OK, press the RUN key!",START_PROMPT_X2,START_PROMPT_Y2+5,RED_COLOR,1,0xffff);
									break;
						case INDONSIA:	//印尼
								Printf24("Tes komputer lengkap, tekan tombol Run!",START_PROMPT_X2,START_PROMPT_Y2+5,RED_COLOR,1,0xffff);
									break;
						case PORTUGAL:	//葡萄牙
								Printf16("Computador auto-teste estiver concluí",START_PROMPT_X2,START_PROMPT_Y2+5,RED_COLOR,1,0xffff);
								Printf16("                                     do, pressione o bot o de execu  o!",START_PROMPT_X2,START_PROMPT_Y2+5,RED_COLOR,0,0xffff);
								ASCII_Printf("a",ASCII16_MODE,8,16,PUTAO_ZK16, START_PROMPT_X2+(56*8),START_PROMPT_Y2+5,RED_COLOR,0xffff);
								ASCII_Printf("ca",ASCII16_MODE,8,16,PUTAO_ZK16, START_PROMPT_X2+(67*8),START_PROMPT_Y2+5,RED_COLOR,0xffff);
								break;
						}
					StartCheck_mode++;	
					orig_wait_time=0;
					}
				}
					break;
		case 1:   //极限正常  则等待运行键    按下
			if((OutFront_limit==1)||(OutMiddle_limit==1)||(Wheel_limit==1)||(OutBack_limit==1))  //极限异常
				StartCheck_mode--;
					break;
		case 2: //延时 
			orig_wait_time++;
			if(orig_wait_time>=300)
				{
				StartCheck_mode++;
				}
					break;
			
		case 3:			//归原点	运行中
			if(SearchZero_flag==1)   //已经  归原点	
				{
				orig_wait_time=0;
				StartCheck_mode++;
				}
			else
				{
				//if((OutFront_limit==1)||(OutMiddle_limit==1)||(Wheel_limit==1)||(OutBack_limit==1))  //极限异常
				//	{
				//	StartCheck_mode=0;
				//	}
				}	
					break;
		case 4://等待一会 进入开机
			orig_wait_time++;
			if(orig_wait_time>=500)
				{
				WorkStart_flag=1;
				WorkMode=AUTO_MODE;//进入 工作画面
				PaperCutEnb_signal=1;
				// TableDis_startcol=RIGHT_ARROW_X; //数据显示起始列
				Knife_order=1;cursor_row=0;     // 在首行 显示 箭头
				ProcessRatio=0xff;
				WorkPic_dis();  //进入 工作画面
				PromptDis_flag=1;
				Size_1page_dis(Knife_order, 0);
				CursorKnife_dis(0,1);//红色光标
				
				}
					break;
					
		}
	}
	//------jog-------电机手动 控制 复位	
switch(ManualMoveMode)
	{
	case 0:
		if(StartCheck_mode<2)
			{
			if(GoFrontEn_flag==1)
				{
				if(OutFront_limit==0)//正常
					{
					if(ServoMoving_flag==0)
						{
						DCServoMove_To(Size_MIN,JOG_MOVE);//--------//前进
						ManualMoveMode++;
						}
					}
				}
			else if(GoBackEn_flag==1)
				{
				if(OutBack_limit==0)//正常
					{
					if(ServoMoving_flag==0)
						{
						DCServoMove_To(Size_MAX,JOG_MOVE);//--------//后退
						ManualMoveMode=4;
						}
					}
				}
			}
			break;
	case 1://前进---------
		if(GoFrontEn_flag==0)	//jog 释放
			{
			DCServoStop();  //停止运行
			ServoStopTime=0;
			ManualMoveMode++;
}
		
			break;
	case 2: //前进 停止后------
		if(ServoMoving_flag==1)
			{
			ServoStopTime++;
			if(ServoStopTime>=1400)
				{
				DCServoStop();  //停止运行
				ServoStopTime=0;
				}
			}
		else
			{
			ManualMoveMode++;
			}
			break;
	case 3:
			break;
	case 4:	//后退--
		if(GoBackEn_flag==0)
			{
			DCServoStop();  //停止运行
			ServoStopTime=0;
			ManualMoveMode++;
			}
		
			break;
	case 5://后退--停止后------
		if(ServoMoving_flag==1)
			{
			ServoStopTime++;
			if(ServoStopTime>=1400)
				{
				DCServoStop();  //停止运行
				ServoStopTime=0;
				}
			}
		else
			{
			ManualMoveMode++;
			}
			break;
	case 6:
			break;		
	}
}


void BellTwice_exec(void)  //蜂鸣  两声
{
if(TargetBell_flag==1)
	{
	switch(TargetBell_mode)
		{
		case 0:
			BellOUT_ON;
			TargetBell_time=0;
			TargetBell_mode++;
				break;
		case 1:
			TargetBell_time++;
			if(TargetBell_time>=on_gap)
				{
				TargetBell_time=0;
				BellOUT_OFF;
				TargetBell_mode++;
				}
				break;
		case 2:
			TargetBell_time++;
			if(TargetBell_time>=off_gap)
				{
				TargetBell_time=0;
				BellOUT_ON;
				TargetBell_mode++;
				}
				break;
		case 3:
			TargetBell_time++;
			if(TargetBell_time>=on_gap)
				{
				TargetBell_time=0;
				BellOUT_OFF;
				TargetBell_flag=0;
				}
				break;		
		}
	}
}
 
void ACServoWorkStart_check(void)  //交流伺服  工作模式前  准备
{
Int32U i;
if(StartCheck_mode<11)	//6
	OutLimit_check(); //外部限位
if(OIN1_PIN!=0)   //原点    1
	{  
	senor=1;
	}
else   //原点   0
	{
	senor=0;
	} 
switch(StartCheck_mode)
	{
	case 0:
		stop_time=0;
			if(senor==1)    //1   原点正常
				{
				if(OriginalError_flag==1)
					{
					CurrentArea_recover1(START_PROMPT_X1, START_PROMPT_Y1,    START_PROM_WIDE, START_PROM_HIGH);
					OriginalError_flag=0;//原点故障  清除
					BackLimitError_flag=0;
					RunDisplay_flag=0;         //后极限正常  则检测运行键/////////////////
					PushRstKey_flag=0; 
					}
				if(OutBack_limit==1)//后限位断开
					{
					if(BackLimitError_flag==0)
						{
						GLCD_SetWindow_Fill(START_PROMPT_X1, START_PROMPT_Y1, START_PROMPT_X1+START_PROM_WIDE-1, START_PROMPT_Y1+START_PROM_HIGH-1, 0xfffff, 0xffff);//提示
						switch(Language)
							{
							case CHN_HAN:
									Printf24("后限位断开!",START_PROMPT_X1,START_PROMPT_Y1+5,RED_COLOR,1,0xffff);
									break;
							case ENGLISH:
									Printf24("Back-Limit is off!",START_PROMPT_X1,START_PROMPT_Y1+5,RED_COLOR,1,0xffff);
									break;
							case INDONSIA:	//印尼
									Printf24("Setelah melepaskan batas!",START_PROMPT_X1,START_PROMPT_Y1+5,RED_COLOR,1,0xffff);
									break;
							case PORTUGAL:	//葡萄牙
									Printf24("Desligue o limite traseiro!",START_PROMPT_X1,START_PROMPT_Y1+5,RED_COLOR,1,0xffff);
									break;
							}
						BackLimitError_flag=1;
						}
					if(OutFront_limit==0)
						{
						StartCheck_mode=3;
						RunDisplay_flag=0;         //前极限正常  则检测运行键/////////////////
						PushRstKey_flag=0; 
						}
					}
				else  //2   后极限正常
					{
					// if((BackLimitError_flag|OriginalError_flag)==1)
					if(BackLimitError_flag==1)
						CurrentArea_recover1(START_PROMPT_X1, START_PROMPT_Y1,    START_PROM_WIDE, START_PROM_HIGH);
					BackLimitError_flag=0;//后极限故障  清除
					OriginalError_flag=0;//原点故障  清除
					StartCheck_mode=3;    
					// StartCheck_mode++;    
					RunDisplay_flag=0;         //后极限正常  则检测运行键/////////////////
					PushRstKey_flag=0; 
					}
				FrontLimitDis_flag=0;
				}
			else     //原点故障
				{
				if(OriginalError_flag==0)
						{
						GLCD_SetWindow_Fill(START_PROMPT_X1, START_PROMPT_Y1,   START_PROMPT_X1+START_PROM_WIDE-1, START_PROMPT_Y1+START_PROM_HIGH-1, 0xfffff, 0xffff);//提示
						switch(Language)
							{
							case CHN_HAN:
									Printf24("原点故障!",START_PROMPT_X1,START_PROMPT_Y1+5,RED_COLOR,1,0xffff);
									break;
							case ENGLISH:
									Printf24("Original fault!",START_PROMPT_X1,START_PROMPT_Y1+5,RED_COLOR,1,0xffff);
									break;
							case INDONSIA:	//印尼
									Printf24("Asal kesalahan!",START_PROMPT_X1,START_PROMPT_Y1+5,RED_COLOR,1,0xffff);
									break;
							case PORTUGAL:	//葡萄牙
									Printf24("come ando falha!",START_PROMPT_X1,START_PROMPT_Y1+5,RED_COLOR,1,0xffff);
									ASCII_Printf("c",ASCII24_MODE,12,24,PUTAO_ZK24, START_PROMPT_X1+(4*12),START_PROMPT_Y1+5,RED_COLOR,0xffff);
									break;
							}	
						OriginalError_flag=1;
						}
				BackLimitError_flag=0;//后极限故障  清除	
				// PushResetPrompt_dis();  //开机 推纸器 复位  提示
				// StartCheck_mode++;
				// PushRstKey_flag=0;
				if(RunDisplay_flag==1)	
					{
					CurrentArea_recover2(START_PROMPT_X2, START_PROMPT_Y2,    START_PROM_WIDE, START_PROM_HIGH);
					RunDisplay_flag=0;
					}
				}	
			break;
	case 1:	//等待 推纸器  复位启动（确定键）
			if(senor==1) //原点 后极限 复位正常
				{			//复位 提示  消失
				CurrentArea_recover3(PUSH_RESET_PROMPT_X1, PUSH_RESET_PROMPT_Y1, PUSH_RESET_PROMPT_WIDE, PUSH_RESET_PROMPT_HIGH);
				StartCheck_mode=0;//3;    
				RunDisplay_flag=0;         //后极限正常  则检测运行键////////////////////
				PushRstKey_flag=0;
				}
			else
				{
				
				}
				break;
	case 2:		// 推纸器  复位中
			if(qianjincn>=20000) //8s
				{
				ACServoStop();
				StartCheck_mode++;
				RunDisplay_flag=0;//后极限正常  则检测运行键////////////////////
				if((OutBack_limit==0)&&(senor==1)) //原点 后极限 复位正常
					{
					CurrentArea_recover1(START_PROMPT_X1, START_PROMPT_Y1,    START_PROM_WIDE, START_PROM_HIGH);
					OriginalError_flag=0;//原点故障  清除
					}
				else
					{
					StartCheck_mode=0; //未复位 则重新检测
					PushRstKey_flag=0;
					}
				}
			break;
	case 3:	//--------------case 1:
			if(OutBack_limit==0)
				{
				if(OutMiddle_limit==0)   //
					{
					if(senor==1)   //信号  正常   提示运行
						{
						if(OutBack_limit==0)
							{
							if(PushRstKey_flag==0)
								{
								if(RunDisplay_flag==0)
									{
									RunDisplay_flag=1;
									GLCD_SetWindow_Fill( START_PROMPT_X2, START_PROMPT_Y2, START_PROMPT_X2-1+START_PROM_WIDE, START_PROMPT_Y2-1+30, 0xfffff, 0xffff);//提示框
									switch(Language)
										{
										case CHN_HAN:
												Printf24("电脑检测完成,请按运行键!>点此处",START_PROMPT_X2,START_PROMPT_Y2+5,RED_COLOR,1,0xffff);
													break;
										case ENGLISH:
												Printf24("Computer testing OK, press the RUN key!",START_PROMPT_X2,START_PROMPT_Y2+5,RED_COLOR,1,0xffff);
													break;
										case INDONSIA:	//印尼
												Printf24("Tes komputer lengkap, tekan tombol Run!",START_PROMPT_X2,START_PROMPT_Y2+5,RED_COLOR,1,0xffff);
													break;
										case PORTUGAL:	//葡萄牙
												Printf16("Computador auto-teste estiver concluí",START_PROMPT_X2,START_PROMPT_Y2+5,RED_COLOR,1,0xffff);
												Printf16("                                     do, pressione o bot o de execu  o!",START_PROMPT_X2,START_PROMPT_Y2+5,RED_COLOR,0,0xffff);
												ASCII_Printf("a",ASCII16_MODE,8,16,PUTAO_ZK16, START_PROMPT_X2+(56*8),START_PROMPT_Y2+5,RED_COLOR,0xffff);
												ASCII_Printf("ca",ASCII16_MODE,8,16,PUTAO_ZK16, START_PROMPT_X2+(67*8),START_PROMPT_Y2+5,RED_COLOR,0xffff);
													break;
										}
									StartCheck_mode++;
									}
								}
							else  //-------------推纸器自动复位后
								{
								if(PassCodeEn_flag==0)
									{
									ACServoMoveBack_MID_SPD();  //交流伺服  中速后退
									//CurrentArea_recover2(REMIND_WINDOW_X, REMIND_WINDOW_Y, START_PROM_WIDE, START_PROM_HIGH);
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
									StartCheck_mode=9;//5;
									}
								else   //-------------启动  密码提示
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
									StartCheck_mode++;
									}
								}
							}
						else
							StartCheck_mode=0;
						//---------20150629
						if(OriginalError_flag==1)
							{
							CurrentArea_recover1(START_PROMPT_X1, START_PROMPT_Y1,    START_PROM_WIDE, START_PROM_HIGH);
							OriginalError_flag=0;//原点故障  清除
							}
						}
					else
						{
						// StartCheck_mode=0;
						}	
					}
				else
					StartCheck_mode=0;
				}
			else	//后极限异常
				{
				if(OutFront_limit==0)//前极限ok
					{
					StartCheck_mode	=5;
					}
				else
					{
					StartCheck_mode	=0;
					GLCD_SetWindow_Fill(START_PROMPT_X2 , START_PROMPT_Y2,START_PROMPT_X2-1+START_PROM_WIDE, START_PROMPT_Y2-1+30, 0xfffff, 0xffff);//提示
					switch(Language)
						{
						case CHN_HAN:
							Printf24("前限位断开!",START_PROMPT_X2,START_PROMPT_Y2+5,RED_COLOR,1,0xffff);
								break;
						case ENGLISH:
							Printf24("Front-Limit is off!",START_PROMPT_X2,START_PROMPT_Y2+5,RED_COLOR,1,0xffff);
								break;
						case INDONSIA:	//印尼
							Printf24("Lepaskan batas depan!",START_PROMPT_X2,START_PROMPT_Y2+5,RED_COLOR,1,0xffff);
								break;
						case PORTUGAL:	//葡萄牙
							Printf24("A primeira parada édesconectada",START_PROMPT_X2,START_PROMPT_Y2+5,RED_COLOR,1,0xffff);
								break;
						}	
					}
				}
			break;
	case 4://2等待   运行键按下   中--------------------------------------------------后极限ok 进入
			if(OutBack_limit==1)// if((OutFront_limit==1)||(OutMiddle_limit==1)||(Wheel_limit==1)||(OutBack_limit==1)||(senor==0))
				{                //后极限有异常
				RunDisplay_flag=0;//清除运行提示
				if(senor==0)//if((OutBack_limit==1)||(senor==0))
					{
					if((OutFront_limit==0)&&(OutMiddle_limit==0))
						{
						CurrentArea_recover2(START_PROMPT_X2, START_PROMPT_Y2,    START_PROM_WIDE, START_PROM_HIGH);	
						}
					}
				StartCheck_mode=0;
				}
				
			if(OutFront_limit==1)//前极限异常
				{
				if(FrontLimitDis_flag==0)
					{
					FrontLimitDis_flag=1;
					GLCD_SetWindow_Fill(START_PROMPT_X2 , START_PROMPT_Y2,START_PROMPT_X2-1+START_PROM_WIDE, START_PROMPT_Y2-1+30, 0xfffff, 0xffff);//提示
					switch(Language)
						{
						case CHN_HAN:
							Printf24("前限位断开!",START_PROMPT_X2,START_PROMPT_Y2+5,RED_COLOR,1,0xffff);
								break;
						case ENGLISH:
							Printf24("Front-Limit is off!",START_PROMPT_X2,START_PROMPT_Y2+5,RED_COLOR,1,0xffff);
								break;
						case INDONSIA:	//印尼
							Printf24("Lepaskan batas depan!",START_PROMPT_X2,START_PROMPT_Y2+5,RED_COLOR,1,0xffff);
								break;
						case PORTUGAL:	//葡萄牙
							Printf24("A primeira parada édesconectada",START_PROMPT_X2,START_PROMPT_Y2+5,RED_COLOR,1,0xffff);
								break;
						}	
					}
				}
			else//
				{
				if(FrontLimitDis_flag==1)	
					{
					FrontLimitDis_flag=0;
					StartCheck_mode=0;
					}
				}
			break;	
	case 5://等待   运行键按下   中-------------------------only后极限异常进入	
			if(OutFront_limit==1)//前极限异常
				{
				StartCheck_mode	=0;
				GLCD_SetWindow_Fill(START_PROMPT_X2 , START_PROMPT_Y2,START_PROMPT_X2-1+START_PROM_WIDE, START_PROMPT_Y2-1+30, 0xfffff, 0xffff);//提示
				switch(Language)
					{
					case CHN_HAN:
						Printf24("前限位断开!",START_PROMPT_X2,START_PROMPT_Y2+5,RED_COLOR,1,0xffff);
							break;
					case ENGLISH:
						Printf24("Front-Limit is off!",START_PROMPT_X2,START_PROMPT_Y2+5,RED_COLOR,1,0xffff);
							break;
					case INDONSIA:	//印尼
						Printf24("Lepaskan batas depan!",START_PROMPT_X2,START_PROMPT_Y2+5,RED_COLOR,1,0xffff);
							break;
					case PORTUGAL:	//葡萄牙
						Printf24("A primeira parada édesconectada",START_PROMPT_X2,START_PROMPT_Y2+5,RED_COLOR,1,0xffff);
							break;
					}
				}
			else		//前极限---ok 恢复
				{
				if(RunDisplay_flag==0)
					{
					RunDisplay_flag=1;
					GLCD_SetWindow_Fill( START_PROMPT_X2, START_PROMPT_Y2, START_PROMPT_X2-1+START_PROM_WIDE, START_PROMPT_Y2-1+30, 0xfffff, 0xffff);//提示框
					switch(Language)
						{
						case CHN_HAN:
								Printf24("电脑检测完成,请按运行键!>点此处",START_PROMPT_X2,START_PROMPT_Y2+5,RED_COLOR,1,0xffff);
									break;
						case ENGLISH:
								Printf24("Computer testing OK, press the RUN key!",START_PROMPT_X2,START_PROMPT_Y2+5,RED_COLOR,1,0xffff);
									break;
						case INDONSIA:	//印尼
								Printf24("Tes komputer lengkap, tekan tombol Run!",START_PROMPT_X2,START_PROMPT_Y2+5,RED_COLOR,1,0xffff);
									break;
						case PORTUGAL:	//葡萄牙
								Printf16("Computador auto-teste estiver concluí",START_PROMPT_X2,START_PROMPT_Y2+5,RED_COLOR,1,0xffff);
								Printf16("                                     do, pressione o bot o de execu  o!",START_PROMPT_X2,START_PROMPT_Y2+5,RED_COLOR,0,0xffff);
								ASCII_Printf("a",ASCII16_MODE,8,16,PUTAO_ZK16, START_PROMPT_X2+(56*8),START_PROMPT_Y2+5,RED_COLOR,0xffff);
								ASCII_Printf("ca",ASCII16_MODE,8,16,PUTAO_ZK16, START_PROMPT_X2+(67*8),START_PROMPT_Y2+5,RED_COLOR,0xffff);
								break;
						}
					}
				if(OutBack_limit==0)
					{
					StartCheck_mode--;//前、后极限都正常
					}
				}
			
			break;
	case 6:  //前进   中-----后极限异常 进入			
			if(OutFront_limit==1)//前极限
				{
				ACServoStop();
				StartCheck_mode=0;
				}
			else
				{
				stop_time=0;
				StartCheck_mode++;
				}
				break;
	case 7:			
			if(OutFront_limit==1)//前极限
				{
				ACServoStop();
				StartCheck_mode=0;
				}
			else
				{
				stop_time++;
				if(stop_time>=6000)
					{
					stop_time=0;
					ACServoStop();
					if(OutBack_limit==0)
						StartCheck_mode++;
					else
						StartCheck_mode=0;
					}
				}
				break;
	case 8:			//前进一段距离， 后极限	恢复正常后----------	开始  后退正常开机步骤
			stop_time++;
			if(stop_time>=1000)
				{
				stop_time=0;
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
					ACServoMoveBack_MID_SPD();  //交流伺服  中速后退>>>>
					StartCheck_mode++;	
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
				break;
		//--------------------------//////////////////////////0000000000000000000000000000000000000000000///////////////////////////
	case 9://5-----运行键按下   后          -----后极限ok 进入
			if(OutBack_limit==0)  //if((OutFront_limit==0)&&(OutMiddle_limit==0))
				{
				if(senor==0&&status==2)
					{
					ACServoMoveBack_LOW_SPD();  //交流伺服  低速后退
					StartCheck_mode++;
					}
				}
			else   //极限异常
				{
				if(stop_time<2000)
					{
					stop_time++;
					if(senor==0&&status==2)		//原点也低 ----- 则 正常
						{
						ACServoMoveBack_LOW_SPD();  //交流伺服  低速后退
						StartCheck_mode++;
						}
					}
				else	//超时  error
					{
					ACServoStop(); 
					StartCheck_mode=0;	
					}
				}
			break;
	case 10://6://-----	 低速后退
			if(OutBack_limit==0)  //if((OutFront_limit==0)&&(OutMiddle_limit==0))
				{
				if(senor==0&&status==8)   //前进
					{
					i=8000000;
					while(i--);
					flagqyx=0;  
					qianjin=1;  
					houtui=0; 
					
					step_add=20;
					 Timer1Init();
				   Timer0Disable(); 
					status=10;   
					
					StartCheck_mode+=2;
					}  
				}
			else   //极限异常
				{
				stop_time=0;
				StartCheck_mode++;
				}	
			break;
	case 11:	//----delay---- 增加 后限位&原点 判断-----------------20160123
			if(stop_time<2000)
				{
				stop_time++;
				if(senor==0&&status==8)   //前进
					{
					i=8000000;
					while(i--);
					flagqyx=0;  
					qianjin=1;  
					houtui=0; 
					
					step_add=20;
					 Timer1Init();
				   Timer0Disable(); 
					status=10;   
					
					StartCheck_mode++;
					}  
				}
			else//超出时间差   
				{
				// if(OutBack_limit==1)// 仍然异常
					// {
					stop_time=0;
					ACServoStop(); 
					StartCheck_mode=0;   //停止
					// }
				}
			
			break;
	case 12://7:  //前进------检测 z  信号   停止
			// if((OutFront_limit==0)&&(OutMiddle_limit==0)&&(OutBack_limit==0))
			if((OutFront_limit==0)&&(OutMiddle_limit==0))
				{
					if(senor==1&&status==10)
						{
						//if(Z_PulseIN==0) //z  信号   停止
						while(M_ZIN_PIN!=0); //z  信号   停止
						//	{
							 Timer1Disable();
							 status=12;
							 poweon_flag=0;
							chushihua=1;
							qianjincn=0;
							 houtuicn=0; 
							 flagtingji8=1; 
							houtui=0;
							qianjin=1;
						//--------------------------------------------
							Timer0Init();
							StartCheck_mode++;
							stop_time=0;
						//	}
						}
					
				}
			else   //极限异常
				{
				ACServoStop(); 
				StartCheck_mode=0;
				}	
			break;
	case 13://8:
			stop_time++;
			if(stop_time>=100)
				{
				stop_time=100;
				if(MotorType==MOTOR_AC_A6_SERVO)	//A6 ----mode
					{
					if(ModBus_CodeDataMode==0x11)//读取完毕
						{
						A6_CalCurSize();
						CurrentSize=CurrentSize_A6Coder;
						StartInitSize=CurrentSize;	//开机初始尺寸
						StartCheck_mode++;
						}
					}
                else   
					{
					CurrentSize=OriginalSize;	
					StartCheck_mode++;
					}
				}
			break;	
	case 14://
                    WorkStart_flag=1;
					WorkMode=AUTO_MODE;//进入 工作画面
					PaperCutEnb_signal=1;
					// TableDis_startcol=RIGHT_ARROW_X; //数据显示起始列
					Knife_order=1;cursor_row=0;     // 在首行 显示 箭头
					ProcessRatio=0xff;
					WorkPic_dis();  //进入 工作画面
					PromptDis_flag=1;
					Size_1page_dis(Knife_order, 0);
					CursorKnife_dis(0,1);//红色光标
					CurrentSize=OriginalSize;
					
			break;	
	}
	
	//**********************电机手动 控制 复位	
switch(ManualMoveMode)
	{
	case 0:
		if(StartCheck_mode<=2)
			{
			if(GoFrontEn_flag==1)
				{
				// if((OutMiddle_limit==0)&&(OutFront_limit==0))//前、中 极限正常
				if(OutFront_limit==0)//前 极限正常
					{
					ACMotorGoForward();//前进
					//--------
					ManualMoveMode++;
					}
				}
			else if(GoBackEn_flag==1)
				{
				if(OutBack_limit==0)//正常
					{
					ACMotorGoBack();  //后退
					//--------
					ManualMoveMode=3;
					}
				}
			}
			break;
	case 1://前进---------
		if(GoFrontEn_flag==0)	//jog 释放
			{
			ACServoStop();  //交流伺服	停止
			ManualMoveMode++;
			}
		else
			{
			// if((OutMiddle_limit==1)||(OutFront_limit==1))// 前、中 极限异常
			if(OutFront_limit==1)// 前 极限异常
				{
				ACServoStop();  //交流伺服	停止
				ManualMoveMode++;
				}
			}
			break;
	case 2:
			break;
	case 3:
		if(GoBackEn_flag==0)
			{
			ACServoStop();  //交流伺服	停止
			ManualMoveMode++;
			}
		else
			{
			if(OutBack_limit==1)// 极限异常
				{
				ACServoStop();  //交流伺服	停止
				ManualMoveMode++;
				}
			}
			break;
	case 4:
			break;		
	}
}

void ACMotorGetCurrentSize(void)  // 交流伺服   尺寸计算
{
if(MotorType<MOTOR_AC_A6_SERVO)
	{
	if(qianjincn>houtuicn)
		{  
		CurrentSize=OriginalSize-((qianjincn-houtuicn)/2);
		} 
	else
		{  
		CurrentSize=OriginalSize+((houtuicn-qianjincn)/2);
		} 
	}
else
	{
	if(A6CoderCorrectRun_flag==0)
		{
		if(qianjincn>houtuicn)
			{  
			CurrentSize=StartInitSize-((qianjincn-houtuicn)/2);//OriginalSize
			} 
		else
			{  
			CurrentSize=StartInitSize+((houtuicn-qianjincn)/2);
			} 	
		}
	else
		{
		CurrentSize=TargetSize;
		}
	}
	
if(flagtingji8==1)
	{
	if(qianjincn>houtuicn)
		{
		qianjincn=qianjincn-houtuicn;
		houtuicn=0;
		yushu=qianjincn%2;
		}
	else
		{
		houtuicn=houtuicn-qianjincn;
		qianjincn=0;
		yushu=houtuicn%2;
		}
		
	}	
}

void ACMotorRunning_ctrl(void)//交流伺服运行  控制
{
Int32U i;
if(houtui==1&&flagtingji8==1&&flagyd==0)
    {   
	 i=400000;
	 while(i--);
	 
	   houtui=0;
	   qianjin=1; 
	   flagqyx=0;
	   flagtingji8=0;
	   flagyunxing8=1;
	   
	   rollsteps=2400;
	   step_ground=11; 
  
	  speedup_steps=30;
	   speedup_steps_B=speedup_steps;
	   rollsteps=(rollsteps- speedup_steps*22)+2;
	   status=1;           

	step_add=1; 
	Timer1Init();
	Timer0Disable();
           
    }
   /////////////////////////////////////////////////////////////////// 
if(flagtingji8==1&&qianjin==1&&t0zhongduan==0)
    {  
         Timer0Init();
         t0zhongduan=1;
          /*
		if(flagbeep==1&&qianjin==1)
			{
			  flagbeep=0;
			   BellOUT_ON;
			  flagbeep1=1;	  
			}  
			*/
		
	if(OIN2_PIN)   //如果第一路光藕输入为高?
        {
        if(!OIN3_PIN)   //如果第一路光藕输入为高?
            {     
             flagshoulun=0;
            }
             
        }		
         
    RunStop_flag=1;
	stop_time=0;
	Run_flag=0;	
	A6CoderCorrectMode=0;//矫正尺寸
    }
}

void AC_MotorRuningLimit_ctrl(void)  //运行中  到外部信号 停止
{
if(houtui==1)   //--------------后退
	{
	if(OutBack_limit==1)  //后限位  停止
		{
		ACServoStop();  //交流伺服	停止
		Run_flag=0;
		InTargetPosit_flag=0;	//目标位置
		TargetSize=0;
		BeforeKnife_offset_in=0;
		AutoPushRun_flag=0;
		}
		/*****----------------------------
	else
		{
		if(CurrentSize>=Size_MAX&&flagqyx==2)
			{
			ACServoStop();  //交流伺服	停止
			Run_flag=0;
			InTargetPosit_flag=0;	//
			TargetSize=0;
			BeforeKnife_offset_in=0;
			AutoPushRun_flag=0;
			}
		}
		-----------------------------****/
	}
else
	{
	if(qianjin==1)  //-------------前进  
		{
		if(PressStop_check()==0)
			{
			if(OutFront_limit==1)//到前限位    停止----------------------
				{
				ACServoStop();  //交流伺服	停止
				Run_flag=0;
				InTargetPosit_flag=0;	//
				TargetSize=0;
				BeforeKnife_offset_in=0;
				AutoPushRun_flag=0;
				}
			else
				{
				if(OutMiddle_limit==1)  //中 限位
					{
					if(Hold_Up_flag==1)  //托板  高  停止-----------------------
						{
						ACServoStop();  //交流伺服	停止
						Run_flag=0;
						InTargetPosit_flag=0;	//
						TargetSize=0;
						BeforeKnife_offset_in=0;
						AutoPushRun_flag=0;
						}
					}
				else
					{
					if(CurrentSize<(Size_MIN+4000)&&CurrentSize>Size_MIN)
						{
						if(LowerAC_SPD_flag==0)
							{
							AC_ChangeSPD();  //速度改变
							LowerAC_SPD_flag=1;
							}
						}
					else
						{
						if(CurrentSize<(Size_MIN+1)&&flagqyx==1)  //电子  极限--------------------
							{
							ACServoStop();  //交流伺服	停止
							Run_flag=0;
							InTargetPosit_flag=0;	//
							TargetSize=0;
							BeforeKnife_offset_in=0;
							AutoPushRun_flag=0;
							}
						}

					}
				}
			}
		else   //压纸  停机
			{
			ACServoStop();  //交流伺服	停止
			Run_flag=0;
			InTargetPosit_flag=0;	//
			TargetSize=0;
			BeforeKnife_offset_in=0;
			AutoPushRun_flag=0;
			}
		}
	}
}


void ACMotor_GetZpulse(void)
{
if(MotorType>=MOTOR_AC_SERVO)
	{
	if(WorkStart_flag==0)
		{
		if(Board_TestMod==0)//
			{
			if(StartCheck_mode==5)
				{
				Ms_Flag=1;
				if(M_ZIN_PIN==0) //z  信号
					Z_PulseIN=0;
				else
					Z_PulseIN=1;
				}
			}
		}
	}
}
 
 
void ACServoAlarm_exec(void)  //交流伺服  警报  处理
{
pInt8U Err_XXX="XXXXXXX";
Int8U ErrCode[10]=0;
if(Board_TestMod==0)//非功能测试模式
	{
	if(ACServoDrvErr_flag==0)
		{
		if(OIN9_PIN!=0)
			{
			ModBus_AcErr_Type=AC_ERR_Z;
			ACServoDrvErr_flag=1;
			ACServoAlarmExec_flag=0;
			}
		else
			{//通讯、 驱动器err code
			if(ModBus_ACErr!=0)
				{
				ModBus_AcErr_Type=AC_ERR_CODE;
				ModBus_AcErr_HisData[0]=ModBus_ACErr;
				// Modbus_A6_SaveErrData();	//保存错误代码	-------20171124 去掉
				ACServoAlarmExec_flag=0;
				ACServoDrvErr_flag=1;
				}
			if(ModBus_Comm_LinkErr==1)
				{
				ModBus_AcErr_Type=AC_ERR_LINK;
				ACServoDrvErr_flag=1;
				ACServoAlarmExec_flag=0;
				}
			}	
		}	
	else
		{        //警报  处理
		if(ACServoAlarmExec_flag==0)
			{
			if(WorkStart_flag==0)  
				{
				GLCD_SetWindow_Fill( START_PROMPT_X2, START_PROMPT_Y2, START_PROMPT_X2-1+START_PROM_WIDE, START_PROMPT_Y2-1+30, 0xfffff, 0xffff);//提示框
				switch(ModBus_AcErr_Type)
					{
					case AC_ERR_Z:	//Z_Pulse错误
							switch(Language)
								{
								case CHN_HAN:
									Printf24("交流伺服驱动器报警Z!",START_PROMPT_X2,START_PROMPT_Y2+5,RED_COLOR,1,0xffff);
											break;
								case ENGLISH:
								case INDONSIA:	//印尼
									Printf24("AC servo drive alarm!",START_PROMPT_X2,START_PROMPT_Y2+5,RED_COLOR,1,0xffff);
											break;
								case PORTUGAL:	//葡萄牙
									Printf24("Alarme Servo drive!",START_PROMPT_X2,START_PROMPT_Y2+5,RED_COLOR,1,0xffff);
											break;
								}
								break;
					case AC_ERR_CODE://驱动器err code
								ErrCode[0]='E';
								ErrCode[1]='r';
								ErrCode[2]='r';
								ErrCode[3]=':';
								ErrCode[4]=(ModBus_ACErr>>8)/10+0x30;
								ErrCode[5]=(ModBus_ACErr>>8)%10+0x30;
								ErrCode[6]='.';
								ErrCode[7]=(unsigned char)ModBus_ACErr/10+0x30;
								ErrCode[8]=(unsigned char)ModBus_ACErr%10+0x30;
								ErrCode[9]=0;
								Printf24("Drv alarm",START_PROMPT_X2,START_PROMPT_Y2+5,RED_COLOR,1,0xffff);
								Printf24(ErrCode,START_PROMPT_X2+10*24,START_PROMPT_Y2+5,RED_COLOR,0,0xffff);
								break;
					case AC_ERR_LINK://通讯错误
							switch(Language)
								{
								case CHN_HAN:
									Printf24("驱动器通讯错误!重启动",START_PROMPT_X2,START_PROMPT_Y2+5,RED_COLOR,1,0xffff);
											break;
								case ENGLISH:	
								case INDONSIA:	//印尼	
								case PORTUGAL:	//葡萄牙
									Printf24("Driver communication Error!",START_PROMPT_X2,START_PROMPT_Y2+5,RED_COLOR,1,0xffff);
											break;
								}
								break;
					}
				
				ACServoAlarmExec_flag=1;
				if(MotorType<MOTOR_AC_A6_SERVO)
					{
					if(StartCheck_mode>2)
						ACServoStop();  //交流伺服	停止
					}
				StartCheck_mode=0;
				}
			else		//进入工作状态
				{
				PromptDis_flag=0;
				GLCD_SetWindow_Fill( REMIND_WINDOW_X, REMIND_WINDOW_Y, REMIND_WINDOW_X+REMIND_LENGTH, REMIND_WINDOW_Y+30, 0xfffff, 0xffff);//提示框
					switch(ModBus_AcErr_Type)
					{
					case AC_ERR_Z:	//Z_Pulse错误
							switch(Language)
								{
								case CHN_HAN:
									Printf24("交流伺服驱动器报警Z!",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,RED_COLOR,0,0xffff);
											break;
								case ENGLISH:	
								case INDONSIA:	//印尼	
									Printf24("AC servo drive alarm!",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,RED_COLOR,0,0xffff);
											break;
								case PORTUGAL:	//葡萄牙
									Printf24("Alarme Servo drive!",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,RED_COLOR,0,0xffff);
											break;
								}
							Printf32(Err_XXX,CURR_SIZE_X,CURR_SIZE_Y,RED_COLOR,1,CURREN_STEP_BACK_COLOR);
								break;
					case AC_ERR_CODE://驱动器err code
								ErrCode[0]='E';
								ErrCode[1]='r';
								ErrCode[2]='r';
								ErrCode[3]=':';
								ErrCode[4]=(ModBus_ACErr>>8)/10+0x30;
								ErrCode[5]=(ModBus_ACErr>>8)%10+0x30;
								ErrCode[6]='.';
								ErrCode[7]=(unsigned char)ModBus_ACErr/10+0x30;
								ErrCode[8]=(unsigned char)ModBus_ACErr%10+0x30;
								ErrCode[9]=0;
								Printf24("Drv alarm",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,RED_COLOR,0,0xffff);
								Printf24(ErrCode,REMIND_WINDOW_X+10*24,REMIND_WINDOW_Y+5,RED_COLOR,0,0xffff);
								break;
					case AC_ERR_LINK://通讯错误
							switch(Language)
								{
								case CHN_HAN:
									Printf24("驱动器通讯错误!重启动",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,RED_COLOR,0,0xffff);
											break;
								case ENGLISH:	
								case INDONSIA:	//印尼	
								case PORTUGAL:	//葡萄牙
									Printf24("Driver communication Error!",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,RED_COLOR,0,0xffff);
											break;
								}
								break;
					}
				ACServoAlarmExec_flag=1;
				if((Run_flag==1)||(GoFrontEn_flag==1)||(GoBackEn_flag==1))
					{
					if(ModBus_AcErr_Type!=AC_ERR_LINK)	
						{
					ACServoStop();  //交流伺服	停止
				//RLOUT1_ON;    // 允许裁切断开
						}
					}
				}
			}
		else	//警报处理完---
			{
			if(WorkStart_flag==1)  
				{
				if((OIN9_PIN==0)&&(ModBus_Comm_LinkErr==0)&&(ModBus_ACErr==0))	//警报修复
					{
					ACServoDrvErr_flag	=0;
					ModBus_AcErr_Type	=0;
					GLCD_SetWindow_Fill( REMIND_WINDOW_X, REMIND_WINDOW_Y, REMIND_WINDOW_X+REMIND_LENGTH, REMIND_WINDOW_Y+30, 0xfffff, 0xffff);//提示框
					Printf24("Driver ok!",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,RED_COLOR,0,0xffff);
					BellOUT_OFF;
					}	
				}
			}
		}
	}
else
	{
	if(ACServoDrvErr_flag==1)
		{
		ACServoDrvErr_flag=0;
		ACServoAlarmExec_flag=0;
		}
	}
} 

void ACMotorStopCheck(void)	//修正实际尺寸
{
Int32U data_off;
RunStop_flag=1;	
switch(A6CoderCorrectMode)
	{
	case 0:
		A6CoderCorrectTime=0;
		A6CoderCorrectMode++;
			break;
	case 1:		
		A6CoderCorrectTime++;
		if(A6CoderCorrectTime>=200)
			{
			A6CoderCorrectTime=0;
			ReadCurrentSize_A6Coder();//读取当前 A6编码器值
			A6CoderCorrectMode++;
			}
			break;
	case 2://等待 读取编码器值
		if(ModBus_CodeDataMode==0x11)//读取完毕
			{
			A6_CalCurSize();	
			if(CurrentSize_A6Coder>(TargetSize+3))//实际值偏大
				{
				data_off=CurrentSize_A6Coder-TargetSize;
				ACMotorRunStart(TargetSize-data_off);
				A6CoderCorrectRun_flag=1;//矫正运行
				//*****
				RunStop_flag=0;
				Run_flag=1;
				InTargetPosit_flag=0;	//目标位置
				AutoCutStart_flag=0;
				AirOffOK_flag=0;
				PressUp_flag=0;
				}
			else if(CurrentSize_A6Coder<(TargetSize-3))//实际值偏小
				{
				data_off=TargetSize-CurrentSize_A6Coder;
				ACMotorRunStart(TargetSize+data_off);
				A6CoderCorrectRun_flag=1;//矫正运行
				//*****
				RunStop_flag=0;
				Run_flag=1;
				InTargetPosit_flag=0;	//目标位置
				AutoCutStart_flag=0;
				AirOffOK_flag=0;
				PressUp_flag=0;
				}
			else	//相等
				{
				A6CoderEqual_flag=1;	
				A6CoderCorrectRun_flag=0;//矫正结束
				}	
			A6CoderCorrectMode=0;
			}
		else	//未读到数据
			{
			if(ModBus_Comm_LinkErr==1)	//通讯错误--------->默认ok
				{
				A6CoderEqual_flag=1;	
				A6CoderCorrectRun_flag=0;//矫正结束
				A6CoderCorrectMode=0;
				}
				
			}
			break;	
		
	}	
}


