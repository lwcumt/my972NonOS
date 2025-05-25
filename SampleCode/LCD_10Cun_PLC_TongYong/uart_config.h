#ifndef _UART_CONFIG_H
#define _UART_CONFIG_H

#include "main.h"
#include "uart.h"

#define   UART0_INT		6 
#define   UART2_INT		VIC_UART2//28 

#define   UART0_PRIORITY    4//6
#define   UART2_PRIORITY    6

#define   Baud1        115200//57600//
#define   Baud2        19200//57600//

#define   Baud02        9600//



extern   UART_T param;
extern Int8U Uart3_Data;
extern Int8U Uart9Data;
extern Int8U Uart8Data;
extern Int8U Uart6Data;
extern Int8U Uart_mod;


extern void Uart3_Init(void);
extern void Uart8_Init(void);
extern void Uart9_Init(void);
extern  void Uart3_Test(void);


/*********************************************************************************************************
** 函数名称 ：UART0_SendByte
** 函数功能 ：以查询方式发送一字节数据
** 入口参数 ：dat	要发送的数据
** 出口参数 ：无
*********************************************************************************************************/
void UART0_SendByte(char dat);

/**********************************************************************************************************
** 函数名称 ：UART0_SendStr
** 函数功能 ：向串口发送一字符串
** 入口参数 ：str	要发送的字符串的指针
** 出口参数 ：无
**********************************************************************************************************/
void UART0_SendStr(char *str);

/*********************************************************************************************************
** 函数名称 ：UART0_SendBuf
** 函数功能 ：向串口发送数据
** 入口参数 ：uint32  snd_n：  发送数据的个数。snd_n 小于8
**			  uint8* RcvBufPt：缓存地址  
** 出口参数 ：无
**********************************************************************************************************/
void UART0_SendBuf(pInt8U RcvBufPt, Int32U snd_n);

/*********************************************************************************************************
** 函数名称 ：IRQ_UART0
** 函数功能 ：串口0接收中断服务程序
** 入口参数 ：无
** 出口参数 ：无
*******************************************************************************************************/
void UART0IntrHandler(void);
/*********************************************************************************************************
** 函数名称 ：UART0_Init
** 函数功能 ：令串口0完成全部初始化工作
** 入口参数 ：无
** 出口参数 ：无
*********************************************************************************************************/
void UART0_Init(void);
void UART3_Init(void);

extern void UART8_SendByte(char dat);
extern void UART8_SendStr(char *str);
extern void UART8_SendBuf(pInt8U RcvBufPt, Int32U snd_n);
extern void UART8IntrHandler(void);

extern void UART9_SendByte(char dat);
extern void UART9_SendStr(char *str);
extern void UART9_SendBuf(pInt8U RcvBufPt, Int32U snd_n);
extern void UART9IntrHandler(void);

////extern void UART3_SendStr(char *str);//为兼容原有UART 号映射到UART9 



#endif
