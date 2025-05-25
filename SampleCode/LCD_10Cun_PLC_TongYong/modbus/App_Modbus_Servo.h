#ifndef _APP_MODBUS_SERVO_H
#define _APP_MODBUS_SERVO_H




#define MODBUS_SERVO

#define SERVO_CONTROL_ON 0xFF00
#define SERVO_CONTROL_OFF 0x0000



#define SERVO_Y6 0x0506
#define SERVO_Y7 0x0507


extern unsigned char Servo_Send_Enb_Flag;

extern unsigned char Modbus_Servo_X_Status[2][8];

extern unsigned char Modbus_Servo_Limit_Sensor_Status;

extern unsigned char Modbus_Servo_Calibration_Flag;
extern unsigned int Modbus_Servo_Calibration_RumTime;

extern int Modbus_Servo_Err_Cnt;
extern int Modbus_Servo_Send_Cnt;


extern unsigned short Modbus_Servo_Small_Gear;
extern unsigned short Modbus_Servo_Big_Gear;
extern unsigned short Modbus_Servo_DaoChen;

extern unsigned char Modebus_Servo_RUN_DIR_Set_Flag;//0:正转 1：反转


extern unsigned char Modbus_Servo_Set_Config_Flag;//配置大小齿轮比和导程


extern unsigned char App_Modbus_Servo_Set_AddSubTime_Flag;//设定加减时间，清0可以重新发送

extern unsigned char App_ModeBus_Servo_Set_HandWheel_Flag;//设定手轮倍速  清0可以重新发送

//初始化
void App_Modebus_Servo_Init(void);


//保存螺距导程  新版本
void App_Save_Modbus_Servo_CFG(void);

//调入螺距导程 新版本
void App_Load_Modbus_Servo_CFG(void);
	
//设置配置参数   小齿轮，大齿轮，导程
void App_Modbus_Servo_Set_Config(void);

void App_Modbus_Decode(unsigned char *rbuf,int len);

//伺服驱动解码
void App_Modbus_Servo_Decode(void);

//读取当前位置
void App_Modebus_Servo_Read_Cur_Position(void);



//校基准


unsigned char App_Modbus_Servo_Calibration(int cal_dimension);

//设定起点位置
void App_Modebus_Servo_Set_Start_Position(float start_position);
//运行到目标位置
void App_Modebus_Servo_Run(float speed,float target);
//设定运行速度
void App_Modebus_Servo_Set_Speed(float speed);
//设定手轮倍率  
void App_Modbus_Servo_Set_HandWheel(unsigned short handwheel_x);


//设定加减速时间
void App_Modbus_Servo_Set_AddSubTime(void);


//设定电机运行方向
void App_Modbus_Servo_MotorRunDir_Set(void);


//设定 加速时间
void App_Modbus_Servo_Set_Speed_AddTime(unsigned short speed_addtime);
//设定减速时间
void App_Modbus_Servo_Set_Speed_SubTime(unsigned short speed_subtime);
//正转 启或停
void App_Modbus_Servo_Ahead_RunAndStop(float speed,unsigned short control_bits);
//反转 启或停
void App_Modbus_Servo_Back_RunAndStop(float speed,unsigned short control_bits);

//停止 启或停
void App_Modbus_Servo_Stop(unsigned short control_bits);



//置零点
void App_Modbus_Servo_Set_ZeroPosition(void);
//读故障代码
void App_Modbus_Servo_Alarm_Read(void);
//清故障代码
void App_Modbus_Servo_Alarm_Clear(void);


//读X状态
void App_Modbus_Servo_Read_X(void);

//写Y状态
void App_Modbus_Servo_Write_Y(unsigned short ynum,unsigned short ysta);
//读Y状态
void App_Modbus_Servo_Read_Y(void);


void  App_Modbus_Servo_Read_1406(void);

//判断伺服是否停止 运行状态下 如当前值，过1秒后。不变，则发送停止

void App_Modbus_Servo_CheckStop(void);

#endif
