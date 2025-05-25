#ifndef _APP_PLC_H
#define _APP_PLC_H
#include "main.h"


#define PLC_CONTACT_OFF '0' //触点为OFF
#define PLC_CONTACT_ON '1'  //触点为ON

#define PLC_DAO_ON '0'
#define PLC_DAO_OFF '1'

#define PLC_YA_ON '0'
#define PLC_YA_OFF '1'

#define PLC_ALIMIT_ON '0'
#define PLC_ALIMIT_OFF '1'

#define PLC_BLIMIT_ON '0'
#define PLC_BLIMIT_OFF '1'

#define PLC_IR_ON '0'
#define PLC_IR_OFF '1'

#define PLC_IO_ON '0'
#define PLC_IO_OFF '1'


#define PLC_SAVE_ADD 200  //PLC DT 数据保存的地址

#define HW_DAO_IN_BUFADD 0x11
//#define HW_SHOULUN_IN_BUFADD 0x0A
#define HW_YA_IN_BUFADD 0x12
#define HW_TUOBAN_IN_BUFADD 0x13
#define HW_IR_IN_BUFADD 0x00
#define HW_ALIMIT_IN_BUFADD 0x14
#define HW_BLIMIT_IN_BUFADD 0x15


#define PLC_COMM_OK 0
#define PLC_COMM_ERR 1
#define PLC_COMM_TIMEOUT 2

#define PLC_COMM_TIMEOUT_DATA 1000   //2


extern char Plc_SendBuf[128];


extern unsigned short Plc_DT_Data_t[32];

extern unsigned char  Plc_ReadContactChannel;//当前读取的通道
extern char Plc_X_Status[64][1];//PLC输入触点状态
extern char Plc_Y_Status[64][1];//PLC输出触点状态
extern char Plc_X_Old_Status[64][1];//PLC输入触点状态
extern char Plc_Y_Old_Status[64][1];//PLC输出触点状态
extern unsigned char Plc_Poll_Enb_Flag;

extern unsigned char App_Plc_WCS_Return_Ok_Flag;
extern unsigned char Plc_Send_WCS_Flag;
extern unsigned char Plc_Send_WCS_TimeOut;

extern unsigned char Plc_Send_DT_Data_Flag;

extern unsigned int  Plc_Comm_TimeOut;
extern unsigned char Plc_Comm_Status;


extern unsigned char XD_XE_Flag;




//PLC通讯初始化
void App_Plc_Init(void);
void App_Plc_Send_DT_Data(void);


void App_Plc_TimeOut_Exec(void);


void Read_PLC_DT_Data(pInt8U pdata);
void Save_PLC_DT_Data(pInt8U pdata);



//PLC 状态查询
void App_Plc_PollReadStatus(void);
void App_Plc_CheckStatus_DisHint(void);

//PLC发送帧
void App_Plc_SendFrame(char *cmd, char *datcode,unsigned int channel,char sta);

//读取数据
void App_Plc_ReadData(char *cmd, char *datcode,unsigned int startadd,unsigned int entadd);
//写入数据
void App_Plc_WriteData(char *cmd, char *datcode,unsigned int startadd,unsigned int endadd);
//PLC解码
void App_Plc_DeCode(char *rbuf);


//校验
unsigned char App_Plc_CheckSum (char *cbuf);
//检验校验码是否正确   正确返回0，错误返回1
unsigned char App_Plc_CheckedCHK(char *cbuf);

#endif

