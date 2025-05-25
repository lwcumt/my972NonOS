#ifndef _NET_PROCESS_H
#define _NET_PROCESS_H

#include "main.h"

#include "lwip/tcp.h"


#define MACHINE_TYPE "LCD_8"


typedef union 
{
unsigned char netconfig_buf[128];
struct
	{
	uint8_t Net_Ip_Add[4];
	uint8_t Net_Mask_Add[4];
	uint8_t Net_Gw_Add[4];	
	uint8_t Net_Mac_Add[8];
	uint16_t Net_ServerPort;//服务器默认端口
	uint16_t MachineNum;
	uint8_t MachineName[64];
	};
}NetConfig_t;


extern NetConfig_t nNetConfig_t;


//////extern uint8_t Net_Gw_Add[4];
//////extern uint8_t Net_Ip_Add[4];
//////extern uint8_t Net_Mask_Add[4];
//////extern uint8_t Net_Mac_Add[8];

extern int Send_DisBuf_Time;
extern int Send_DisBuf_DelayTime;

extern uint32_t Net_Recv_File_Length;
extern char Net_Recv_File_FileName[256];

extern uint32_t Net_Recv_TimeOut;

/* network initialization function.*/
void net_init(void);
void Net_Process_DeCode(struct tcp_pcb *pcb,uint8_t * net_recvdata);

uint8_t Net_Recv_File_Process(void);

void Net_Process_SendDisBuf(void);
void Read_OneKnifeDataToBuf(unsigned char *buf,uint16_t knifenum);
void SavePro_NetRecv_headInfo(Int16U prog, pInt8U pdata);//spi保存一个程序的 头(程序名+ 时间 +刀数 );
#endif
