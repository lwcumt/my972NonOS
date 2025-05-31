
/*****************************************控制  参数-----------------------------

‘Z’螺距设置	‘30’	‘1200’或‘1000’	
‘R’启动寻零	‘30’	指定寻零后的初始位置	
‘P’重新定位	‘30’	重新定义当前的位置数值	
‘G’定点运动	‘30’	指定运动的目标位置	

‘J’JOG运动	‘30’	忽略数据，终止运动	
			‘31’	向前运动，单位RPM，取值400~1600	
			‘32’	向后运动，单位RPM，取值400~1600	
‘M’静止模式	‘31’	位置模式静止	
			‘32’	速度模式静止	
‘K’继电控制	‘30’	‘00xxxx’表示四个继电器	
			
‘S’推纸速度	‘30’	按照转速给定，单位RPM，取值1000~1600	
		-------------------------------------	
‘Q’编码器检测 ‘30’	编码器检测运动停止
			  ‘31’	编码器检测运动启动
‘L’限位屏蔽	  ‘30’	使能所有限位开关
			  ‘31’	屏蔽后极限
			  ‘32’	屏蔽中极限
			  ‘33’	屏蔽前极限
			  ‘34’	屏蔽托板				  
		--------------------------------------
‘C’参数调整	‘10’	位置环增益参数降低（取值范围0~9）	
			‘11’	位置环增益参数增大	
			‘20’	位置环微分参数降低	
			‘21’	位置环微分参数增大	
			‘30’	位置环积分参数降低	
			‘31’	位置环积分参数增大	
			‘40’	速度环增益参数降低（取值范围0~9）	
			‘41’	速度环增益参数增大	
			‘50’	速度环微分参数降低	
			‘51’	速度环微分参数增大	
			‘60’	速度环积分参数降低	
			‘61’	速度环积分参数增大
		--------------------------------------
 Z自由螺距设定	 31	 1201．马达一圈的距离		
******************************************/

/************返回数据--------------------------------------------------------
T数据格式：（%Txyz080000X）
		*x  代表三个行程开关屏蔽状态的二进制(后极限、中极限、前极限)
		*y  代表三个行程开关状态的二进制编码(后极限、中极限、前极限)
		*z	代表三个行程开关状态的二进制编码(托板、切刀、压纸)
		*080000 电机当前位置
		*X 	异或值
F数据格式：（%FABii+xxxxX）
		*A：表示设定的螺距速比，0～5，与设定表一致；
		*B：寻零完成标志，N表示未完成寻零，D表示已完成寻零；R表示运行中
		*ii：两位电流绝对值，“10”表示10A
		*+xxxx：当前速度值，一字节表示符号，后面为具体速度数值；
		*X：前11位数据的异或值
C/D数据格式：  C--（%C7X262645XP）		D--（%D7X262645XP）
		*7 是2个io状态	当红外为高 7	红外为低是 3
		*X 是通讯命令动作，S 是手轮动作
		*C数据时:
					26  位置环增益
					26  位置环微分
					45  位置环积分
		*D数据时:
					26  速度环增益
					26  速度环微分
					45  速度环积分	
		*X	固定字母
		*P 	校验和			
**********************************************/

#ifndef _SERVO_H
#define _SERVO_H

#include"main.h"


#define SERVO_COMMD_HEAD 	'%'
#define SERVO_COMMD_END 	'B'

#define SERVO_COMMD_Z 		'Z' //螺距设置
#define SERVO_COMMD_R 		'R' //启动录零
#define SERVO_COMMD_P 		'P' //重新定位
#define SERVO_COMMD_G		'G' //定点运动
#define SERVO_COMMD_J 		'J' //JOG运动

#define SERVO_COMMD_M 		'M' //静止模式

#define SERVO_COMMD_K 		'K' //继电控制
#define SERVO_COMMD_S 		'S' //推纸速度

#define SERVO_COMMD_C		'C' //参数调整
//----------------
#define SERVO_COMMD_Q		'Q' //编码器检测
#define SERVO_COMMD_L		'L' //限位屏蔽开关


#define SERVO_COMM_LENGTH 	12   //帧长度

//------------
#define STAT_10H	"10"
#define STAT_11H	"11"
#define STAT_20H	"20"
#define STAT_21H	"21"
#define STAT_30H	"30"
#define STAT_31H	"31"
#define STAT_32H	"32"
#define STAT_33H	"33"
#define STAT_34H	"34"
#define STAT_40H	"40"
#define STAT_41H	"41"
#define STAT_50H	"50"
#define STAT_51H	"51"
#define STAT_60H	"60"
#define STAT_61H	"61"



//运行类型  设定-----------------------
#define	RUN_MOVE	0
#define	JOG_MOVE	1

extern unsigned int const SERVO_SPEED[];


//extern Int8U ServoCommData_Tx[15];
extern Int8U ServoCommData_Rx[15];


typedef struct
{
Int8U head;
Int8U commd;
Int8U stus[2];
//Int8U stus_2;
Int8U data[6];
Int8U check;
Int8U end;
Int8U end_mark;
} SERVO_CTRL;


extern Int8U ServoSpeed_order;  //运行速度
extern Int8U JogSpeed_order;  //点动速度
extern Int8U SpeedDown_Ratio;//减速比
extern Int8U Screw_Pitch;  //螺距
//------C
extern Int8U PositRing_Gain;
extern Int8U PositRing_Diff;
extern Int8U PositRing_Integral;
//------D 数据
extern Int8U SpeedRing_Gain;
extern Int8U SpeedRing_Diff;
extern Int8U SpeedRing_Integral;

//---------------------------------
extern Int8U ServoRecvOk_flag;
extern Int8U ServoDisconnect_flag;
extern Int8U ServoDrvInit_flag;
extern Int8U ServoDrvInitOK_flag;
extern Int8U ServoMoving_flag;


//-------F 数据----
extern Int8U SearchZero_flag;
extern Int8U OriginalReset_flag;


extern Int16U ServoNow_Speed;

extern Int16U ServoStartDelayTime;

extern Int8U ServoSendCou;

extern Int32U NowSize_last;
extern Int8U ChangeTarget_flag;
extern Int8U ServoBack_flag;
extern Int8U ServoAutoPushFinish_flag;










#endif


