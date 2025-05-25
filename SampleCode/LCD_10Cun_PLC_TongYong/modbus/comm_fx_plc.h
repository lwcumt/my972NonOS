#ifndef _COMM_FX_PLC_H
#define _COMM_FX_PLC_H

#include "main.h"

#define FX_PLC 


#define PLC_ACK 0x06
#define PLC_NAK 0x15


#define FX_CMD_READ '0'				//读
#define FX_CMD_WRITE '1'  		//写

#define FX_CMD_FORCE_ON '7'		//强制ON
#define FX_CMD_FORCE_OFF '8'	//强制OFF



//******************
//D 区地址


#define D_BASE_ADD 0x1000 

#define M_BASE_ADD 0x0100

//D 区地址  结束
//******************


//#######################
// X 区地址

#define X000_7 0x0080
#define X010_7 0x0081
#define X020_7 0x0082
#define X030_7 0x0083
#define X040_7 0x0084
#define X050_7 0x0085
#define X060_7 0x0086
#define X070_7 0x0087

#define X100_7 0x0088
#define X110_7 0x0089
#define X120_7 0x008A
#define X130_7 0x008B
#define X140_7 0x008C
#define X150_7 0x008D
#define X160_7 0x008E
#define X170_7 0x008F


//#######################



//#######################
// Y 区地址

#define Y000_7 0x00A0
#define Y010_7 0x00A1
#define Y020_7 0x00A2
#define Y030_7 0x00A3
#define Y040_7 0x00A4
#define Y050_7 0x00A5
#define Y060_7 0x00A6
#define Y070_7 0x00A7

#define Y100_7 0x00A8
#define Y110_7 0x00A9
#define Y120_7 0x00AA
#define Y130_7 0x00AB
#define Y140_7 0x00AC
#define Y150_7 0x00AD
#define Y160_7 0x00AE
#define Y170_7 0x00AF


//#######################



//Y输出强制区位址
#define Y000 0x0500		//共Y000-007
#define Y010 0x0508		//共Y010-017  后面类推
#define Y020 0x0510
#define Y030 0x0518
#define Y040 0x0520
#define Y050 0x0528
#define Y060 0x0530
#define Y070 0x0538

#define Y100 0x0540
#define Y110 0x0548
#define Y120 0x0550
#define Y130 0x0558
#define Y140 0x0560
#define Y150 0x0568
#define Y160 0x0570
#define Y170 0x0578




//****************
//M 区地址   强制区

#define M96 0x0860

//  主机停止 M100断开  M101 闭合
//  主机启动 M100闭合  M101 断开
#define M100   (M96+(100-96))
#define M101	 (M100+1)


//风泵停止  M102断开 M103 闭合
//风泵启动  M102闭合 M103断开

#define M102	 (M101+1)
#define M103	 (M102+1)
#define M104	 (M103+1)


#define M192  0x08c0

//点动换刀 M200闭合

#define M200  (M192+(200-192))

//电动换刀 M201 闭合

#define M201  (M200+1)
#define M202  (M201+1)


//优化裁切   M210
#define M210  (M200+10)

//快速裁切    M230
#define M230  (M200+30)



#define M280 0x0800


#define M288 0x0920

//允许裁切 M300 
#define M300  (M288+(300-288))

//自动裁切  M301
#define M301  (M300+1)


//气阀  M302
#define M302  (M301+1)

//理纸  M303
#define M303  (M302+1)

//压纸1   M304
#define M304  (M303+1)

//压纸2   M305
#define M305  (M304+1)


#define M370_R 370/8  //+M_BASE_ADD



//M 区地址结束
//*************************


//////extern unsigned char FX_PLC_X_Status[18];  //每个字节对应8个IO  X00-X07
//////extern unsigned char FX_PLC_Y_Status[18];	 //每个字节对应8个IO  Y00-X07

extern unsigned char Fx_Plc_RecvCnt;

extern unsigned char Fx_Plc_RecvBuf[32];
extern char FX_Plc_Comm_Status;

void Comm_FX_Plc_Exec(void);

unsigned int SwapAdder(unsigned int add);

void ServoSend_Test(void);


//读 数据
void Comm_FX_Plc_Read(unsigned int adder,unsigned char len);
//写数据
void Comm_FX_Plc_Write(unsigned int adder,unsigned char *dbuf,unsigned char len);


//读取X状态
void Comm_FX_Plc_Read_X_Status(unsigned short xadd,unsigned char len);

//读取Y状态
void Comm_FX_Plc_Read_Y_Status(unsigned short xadd,unsigned char len);

//读取M状态
void Comm_FX_Plc_Read_M_Status(unsigned short madd,unsigned char len);


//读D区数据
void Comm_FX_Plc_Read_D_Area(unsigned int adder,unsigned char len);
//写D区数据
void Comm_FX_Plc_Write_D_Area(unsigned int adder,unsigned char *dbuf,unsigned char len);

//////void Comm_FX_Plc_Read(unsigned int adder,unsigned char len);
//////void Comm_FX_Plc_Write(unsigned int adder,unsigned char *dbuf,unsigned char len);
void Comm_FX_Plc_ForceON(unsigned int adder);
void Comm_FX_Plc_ForceOFF(unsigned int adder);

void CommExec_FX_Plc(unsigned char  rx);
void Comm_FX_Plc_Send(void);
void Comm_FX_Plc_SendStr(char *sbuf);
void Comm_FX_Plc_SendBuf(unsigned char *sbuf,unsigned char len);
void FX_PLC_SendFrame(char cmd,unsigned int adder,unsigned char *dbuf,unsigned int len);

#endif
