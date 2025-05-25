#ifndef _APP_MODBUS_PLC_H
#define _APP_MODBUS_PLC_H


#define PLC_CONTROL_ON 0xFF00
#define PLC_CONTROL_OFF 0x0000


#define M_ON 0xFF00
#define M_OFF 0x0000

#define PLC_2N_X_ADDER 0  //X 位元件 0-63  64个IO
#define PLC_2N_Y_ADDER 300 //Y 位元件 300 - 363  64 个Y
#define PLC_2N_M_ADDER 4000  //M 位元件 4000 - 7071  M0 - M3071  
#define PLC_2N_D_ADDER 0    //字元件 0-5999  D0 D5999  


#define PLC_MODE_NONE 0
#define PLC_MODE_3U 1
#define PLC_MODE_2N 2
#define PLC_MODE_SERVO 3

extern unsigned char PLC_Run_Mode;

extern unsigned char PLC_X_Status[8][8];
extern unsigned char PLC_Y_Status[8][8];
extern unsigned char PLC_M_Status[8][8];

extern unsigned int Modbus_PLC_AutoCut_SetTime;//自动裁切设定时间

extern unsigned char Modbus_PLC_D20_DownCutTime;//D20 下刀时间


void App_Modbus_Plc_Init(void);
//保存自动裁切时间 和下刀时间  新版本
void App_Save_Modbus_PLC_CFG(void);

//调入自动裁切时间 和下刀时间
void App_Load_Modbus_PLC_CFG(void);

void App_Modbus_FxPlc_Decode(void);


void App_Modbus_Plc_Read_X_Status(unsigned short x_add,unsigned char num);
void App_Modbus_Plc_Read_Y_Status(unsigned short y_add,unsigned char y_num);

void App_Modbus_Plc_Write_Y_Status(unsigned short y_add,unsigned short y_status);
void App_Modbus_Plc_Write_M_Status(unsigned short m_add,unsigned short m_status);


extern unsigned char Modbus_Plc_M280_Send_Flag;
void App_Modbus_Plc_Write_M280_FastCutMode(void);//M280 快速裁切模式

extern unsigned char Modbus_Plc_D20_Send_Flag;//D20 下刀时间 ，清0 可以重复发送

void App_Modbus_Plc_Write_D20_DownCutTime(void);		//D20 下刀时间发送,   清0 可以重复发送
//写D20数据
void App_Modbus_Plc_Write_D_Data(unsigned short d_add,unsigned short d_data);



//为了兼容原来的程序编译
unsigned char App_Plc_SendFrame_Process(char* cmd,char * ctype,unsigned char sta,char str_c);
#endif
