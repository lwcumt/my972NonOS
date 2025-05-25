#ifndef _APP_MODBUS_972_H
#define _APP_MODBUS_972_H



#define SERVO_ADDER 0x01

#define PLC_ADDER 0x02
#define PLC_3U_ADDER 0x02




#define PLC_READ_X  1
#define PLC_READ_Y  2


#define SERVO_READ_X 3
#define SERVO_READ_Y 4



#define MCT_SERVO_READ_CUR_POSITION 5  //读当前位置
#define MCT_SERVO_SET_START_POSITION 6  //设置当前位置
#define MCT_SERVO_RUN_TO_TARGET_POSITION 7  //运行到目标位置

#define MCT_SERVO_RUN_TO_CONTROL 8
#define MCT_SERVO_AHEAD_RUN_CONTROL 9
#define MCT_SERVO_BACK_RUN_CONTROL 10
#define MCT_SERVO_SET_ZERO_CONTROL 11

#define MCT_SERVO_ALARM_READ 12
#define MCT_SERVO_ALARM_CLEAR 13

#define MCT_ERVO_SET_CONFIG 14

#define MCT_SERVO_WRITE_Y 15


#define PLC_WRITE_Y  16
#define PLC_WRITE_M  17
#define PLC_WRITE_D  18

#define MCT_SERVO_READ_VISION 19

#define SERVO_READ_1406 22


//PLC  地址相关定义

// 0x01  位读
// 0x05  位写


#define M_BASE_ADDD 0x0000


//软件元件 位寻址
#define PLC_M_BIT_BASE_ADDER  0x0000	//0x0000～0x1DFF M0～M7679 
#define PLC_Y_BIT_BASE_ADDER  0x3300	//0x3300～0x33FF Y0～Y377  	 可读写
#define PLC_X_BIT_BASE_ADDER  0x3400	//0x3400～0x34FF  X0～X377   只读


// 0x03  字读
// 0x06  字写

//软件元件 字寻址
#define PLC_D_BASE_ADDER  0x0000	//0x0000～0x1F3F D0～D7999
#define PLC_M_BASE_ADDER  0xA478	//0xA478～0xA657 M0～M7679 
#define PLC_Y_BASE_ADDER  0xA7A8	//0xA7A8～0xA7B7 Y0～Y377  	 可读写
#define PLC_X_BASE_ADDER  0xA7B8	//0xA7B8～0xA7C7  X0～X377   只读

//PLC  地址相关定义   结束



typedef union 
{
float union_float;
unsigned int union_uint;
unsigned char  union_byte[4];
}FloatAndByte;



//PLC IO
//////extern unsigned char PLC_X_Status[128];
//////extern unsigned char PLC_Y_Status[128];
//////extern unsigned char PLC_M_Status[128];

//Modbus Servo IO
extern unsigned char ModbusServo_X_Status[64];
extern unsigned char ModbusServo_Y_Status[64];
extern unsigned char PLC_X_READ_OK_Flag;



extern unsigned char Modubs_Cmd_Type;

extern FloatAndByte FAB;

extern float Servo_Cur_Position;



void App_Modbus_Test(void);

//Modbus Task
void App_Modbus_Task(void);





void  App_Modbus_Get_CurrentSize(void);

//Servo 相关


// IEEE 754  float to Buf
void Float_To_ByteBuf(float fn,unsigned char * bbuf);
// IEEE 754  Buf To float
float ByteBuf_To_Float(unsigned char *bbuf);



//伺服驱动解码
//void App_Modbus_Servo_Decode(void);


//PLC  相关

//PLC 解码
//void App_Modbus_FxPlc_Decode(void);

//写M命令
//void App_Modbus_FXPlc_M_CTRL(char *msta,unsigned int madd);


#endif

