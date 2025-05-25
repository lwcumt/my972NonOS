#include "net_process.h"
#include "lwip/tcp.h"

#include "netif/ethernetif.h"
#include "netif/etharp.h"
#include "lwip/init.h"
#include "lwip/tcp.h"
#include "lwip/stats.h"
#include "lwip/memp.h"
#include "lwip/timers.h"
#include "net_config.h"


#include "string.h"
#include "stdio.h"
//#include "tcpclient.h"
#include "drv_glcd.h"

#include"key.h"

#include"m25pe16.h"
#include"chndot.h"

#include"io.h"
#include "timer.h"

#include "pic_exec.h"

#include  "test_io.h"

#include "port.h"
#include "servo.h"
#include "name_input.h"
#include"keyboard.h"
#include "file.h"
#include "string.h"
#include "tcpserver.h"
#include "message.h"



 NetConfig_t nNetConfig_t;


struct tcp_pcb *Tcp_Queue_pcb=NULL;
char Tcp_Server_SendBuf[2048];
uint8_t Tcp_Server_RecvBuf[10*1024];

u8 Send_DisBuf_Flag=0;
unsigned char *pSend_DisBuf;
int Send_DisBuf_Length;
int Send_DisBuf_Time=0;
int Send_DisBuf_DelayTime=0;
uint8_t Net_RecvData_Flag=0;

uint16_t Net_Recv_ProgNum=0;
uint16_t Net_Recv_KnifeNum=0;
uint16_t Net_Recv_PageCou=0;
uint16_t Net_Recv_Page=0;

//接收文件相关
uint8_t Net_Recv_File_StepCou;//接收步骤
uint8_t Net_Recv_File_Flag=0;
uint8_t Net_Recv_File_HeadEnter_Flag=0;
uint32_t Net_Recv_File_Length=0;
char Net_Recv_File_FileName[256];
uint32_t Net_Recv_File_Cou=0;
uint8_t Net_Recv_File_Buf[2*1024];//2M空间
uint8_t * pNet_Recv_File_Buf;


uint8_t * pNet_Recv;

uint32_t Send_DisBuf_Cou;
uint8_t Net_RecvType;

uint8_t WBuf[6*1024];

uint32_t Net_Recv_TimeOut=0;



struct ip_addr gw, ipaddr, netmask;
struct netif netif;

/* network initialization function.*/
void net_init(void)
{
int i;
char sname[]="netconfig.ini";
	if(FileRead("netconfig.ini",(unsigned char *)nNetConfig_t.netconfig_buf)==0)//直接读取到联合结构体
		{//没有读到配置文件
			nNetConfig_t.Net_Gw_Add[0]=0;
			nNetConfig_t.Net_Gw_Add[1]=0;
			nNetConfig_t.Net_Gw_Add[2]=0;
			nNetConfig_t.Net_Gw_Add[3]=0;
			
			
			nNetConfig_t.Net_Ip_Add[0]=192;
			nNetConfig_t.Net_Ip_Add[1]=168;
			nNetConfig_t.Net_Ip_Add[2]=1;
			nNetConfig_t.Net_Ip_Add[3]=18;//默认IP为  192.168.0.18
			
			nNetConfig_t.Net_Mask_Add[0]=255;
			nNetConfig_t.Net_Mask_Add[1]=255;
			nNetConfig_t.Net_Mask_Add[2]=255;
			nNetConfig_t.Net_Mask_Add[3]=0;//默认MASK   255.255.255.0
			
			
			nNetConfig_t.Net_Mac_Add[0]=0x31;
			nNetConfig_t.Net_Mac_Add[1]=0x00;
			nNetConfig_t.Net_Mac_Add[2]=0x10;
			nNetConfig_t.Net_Mac_Add[3]=0x68;
			nNetConfig_t.Net_Mac_Add[4]=0x47;
			nNetConfig_t.Net_Mac_Add[5]=0x58;


			my_mac_addr0[0]=0x31;
			my_mac_addr0[1]=0x00;
			my_mac_addr0[2]=0x10;
			my_mac_addr0[3]=0x68;
			my_mac_addr0[4]=0x47;
			my_mac_addr0[5]=0x58;


			nNetConfig_t.Net_ServerPort=1929;//默认服务器端口
			nNetConfig_t.MachineNum=1;
			memcpy(nNetConfig_t.MachineName,"机台1",5);
			nNetConfig_t.MachineName[5]=0;
			
			memcpy((uint8_t*)DOWNFILE_SDRAM_ADD,nNetConfig_t.netconfig_buf,128);//
			
			iFiles.FileLength=128;

			File_Create("netconfig.ini");//初始化信息条数为0		
			//Net_Mac_Add[0]=0x31;
			
		}
	else
		{//读到配置文件
			
		}
////////		//测试用  for(i=0;i<128;i++) 段
////////		for(i=0;i<128;i++)
////////		nNetConfig_t.netconfig_buf[i]=0;//
////////		
////////		if(FileRead("netconfig.ini",(unsigned char *)nNetConfig_t.netconfig_buf)!=0)
////////					ASCII_Printf("Load netconfig.init is OK", ASCII1632_MODE, ASCII1632_WIDTH, ASCII1632_HIGH, ASCII1632, 350, 300, 0xffff, 0);
	
    // LwIP needs a timer @ 100Hz. To use another timer source, please modify sys_now() in sys_arch.c as well
   sysStartTimer(TIMER0, 10000, PERIODIC_MODE);  
    
#ifdef USE_DHCP

    IP4_ADDR(&gw, 0, 0, 0, 0);
    IP4_ADDR(&ipaddr, 0, 0, 0, 0);
    IP4_ADDR(&netmask, 0, 0, 0, 0);

#else

    IP4_ADDR(&gw, nNetConfig_t.Net_Gw_Add[0],nNetConfig_t.Net_Gw_Add[1],nNetConfig_t.Net_Gw_Add[2],nNetConfig_t.Net_Gw_Add[3]);//0.0.0.0  默认 
    IP4_ADDR(&ipaddr, nNetConfig_t.Net_Ip_Add[0], nNetConfig_t.Net_Ip_Add[1], nNetConfig_t.Net_Ip_Add[2], nNetConfig_t.Net_Ip_Add[3]);//192.168.0.18 默认
    IP4_ADDR(&netmask, nNetConfig_t.Net_Mask_Add[0], nNetConfig_t.Net_Mask_Add[1], nNetConfig_t.Net_Mask_Add[2], nNetConfig_t.Net_Mask_Add[3]);//255.255.255.0  默认

#endif

    lwip_init();
    // To use EMAC1, change ethernetif_init0 to ethernetif_init1
    netif_add(&netif, &ipaddr, &netmask, &gw, NULL, ethernetif_init1, ethernet_input);    
    netif_set_default(&netif);

#ifdef USE_DHCP
    dhcp_start(&netif);
#else
    netif_set_up(&netif);
#endif
}


void Net_Process_DeCode(struct tcp_pcb *pcb,uint8_t * net_recvdata)
{
unsigned char * pdu;
	
int length=0;
uint8_t strtemp[64];
uint32_t knife_num=0;
uint32_t *pknum;
uint16_t recvlength=0;
uint8_t * pdn;
	
Tcp_Queue_pcb=pcb;	
	
if(Net_Recv_File_Process()!=0)
	return;//判断是否为接收文件	

if(Net_RecvData_Flag==1)
		{
////////		 pdn=(uint8_t*)Tcp_Server_RecvBuf;
////////		 
////////		 pdn+=Net_Recv_PageCou*1024;
////////	   
////////			memcpy(pdn,net_recvdata,1024);	
			
		memcpy(pNet_Recv,net_recvdata,Tcp_RecvLength);
		pNet_Recv+=Tcp_RecvLength;
		
		Net_Recv_PageCou+=Tcp_RecvLength;
			
    //memcpy(Tcp_Server_RecvBuf,net_recvdata,1024);		
		
			
							
		Net_Recv_PageCou++;
		if(Net_Recv_PageCou>=Net_Recv_Page)
			{
				
			Net_RecvData_Flag=0;	

		 pdn=(uint8_t*)K_SIZE_sdram;				
		 if(Net_Recv_ProgNum<301)
		 {
			pdn+=(Net_Recv_ProgNum-1)*(999*5+100);
			memcpy(pdn,Tcp_Server_RecvBuf,999*5+100);
		 }
		 else
		 {
		 pdn+=PROG_BYTES1*PROG_GROPU1+(Net_Recv_ProgNum-PROG_GROPU1-1)*PROG_BYTES2;//(Net_Recv_ProgNum-300-1)*(399*5+100)+300*(999*5+100);	 			
		 memcpy(pdn,Tcp_Server_RecvBuf,399*5+100);			 
		 }
		 
		 SavePro_NetRecv_headInfo(Net_Recv_ProgNum, (pInt8U)&OnePro_head);//刀数 保存  
			SaveBuf_datas(Net_Recv_ProgNum, 1,  Net_Recv_KnifeNum); //保存
		 
		 if(Net_Recv_ProgNum==prog_order)
		 {
			 cursor_pro=0;  
			//----------返回编程画面
				WorkMode=AUTO_MODE; 
				ExportOnePro_dis(prog_order);  //更新一个 程序 		 
			}
				
////////			//knife_num=((uint32_t)Tcp_Server_RecvBuf[93]<<24)+((uint32_t)Tcp_Server_RecvBuf[92]<<16)+((uint32_t)Tcp_Server_RecvBuf[91]<<8)+((uint32_t)Tcp_Server_RecvBuf[90]);
////////			OnePro_head.pro_knifeSUM=Net_Recv_KnifeNum;

////////			CursorKnife_dis(cursor_row, 0);//红色光标消失
////////			cursor_row=0;
////////			CursorKnife_dis(cursor_row, 1);//红色光标显示
////////			Knife_order=1;//
////////			Size_1page_dis(Knife_order,0);//一页尺寸显示
////////			if(Knife_order<=OnePro_head.pro_knifeSUM)
////////			StepOrder_dis(Knife_order);//步骤更新
////////			PromptNum_dis();//输入范围	
////////			PromptDis_flag=1;  								
				
			}
						//	sprintf(strtemp,"%d",knife_num);
					//		ASCII_Printf(strtemp, ASCII1632_MODE, ASCII1632_WIDTH, ASCII1632_HIGH, ASCII1632, 350, 300, 0xffff, 0);
		//ASCII_Printf("Knife Recv", ASCII1632_MODE, ASCII1632_WIDTH, ASCII1632_HIGH, ASCII1632, 350, 300, 0xffff, 0);
	//	CursorPro_dis(cursor_pro,1);//

//	OneProgHeadInfo_dis(1 ,  prog_order, 1);	//一条程序 显示1		
		return;	
		}
		
length=strlen(net_recvdata);
if(length>10)
	{			
	if(strcmp(net_recvdata,"{\"Get:MachineType\"}")==0)
		{//?????
			length=strlen("MachineType:");
		memcpy(Tcp_Server_SendBuf,"MachineType:",length);
		memcpy(&Tcp_Server_SendBuf[length],MACHINE_TYPE,strlen(MACHINE_TYPE));
		length+=strlen(MACHINE_TYPE);
			
		App_Tcp_Write(pcb,Tcp_Server_SendBuf,length,1);
		}

	if(strcmp(net_recvdata,"{\"Get:DisPlayBuf\"}")==0)
		{//?????
		length=strlen("DisPlayBuf:");
		memcpy(Tcp_Server_SendBuf,"DisPlayBuf:",length);
		App_Tcp_Write(pcb,Tcp_Server_SendBuf,length,1);
		Send_DisBuf_Flag=1;
		Send_DisBuf_Length=800*600*2;
		Send_DisBuf_Cou=0;
		pSend_DisBuf=(unsigned char *)LCD_VRAM_BASE_ADDR;
		Send_DisBuf_Time=0;
		Send_DisBuf_DelayTime=50;//延时10mS后发送数据
			return;
		}		
		
		
		if(strcmp(net_recvdata,"{\"Set:DisPlay_Pause\"}")==0)//显示发送暂停
		{//?????
		length=strlen("DisPlay_Pause:");
		memcpy(Tcp_Server_SendBuf,"DisPlay_Pause:",length);
		App_Tcp_Write(pcb,Tcp_Server_SendBuf,length,1);
		Send_DisBuf_Flag=0;
		Send_DisBuf_Length=800*600*2;
		Send_DisBuf_Cou=0;
		pSend_DisBuf=(unsigned char *)LCD_VRAM_BASE_ADDR;
		Send_DisBuf_Time=0;
		Send_DisBuf_DelayTime=50;//延时10mS后发送数据
			return;
		}		

		
	if(strcmp(net_recvdata,"{\"Get:ProgramData\"}")==0)//传递单刀数据
		{//?????
		length=strlen("ProgramData:");
		memcpy(Tcp_Server_SendBuf,"ProgramData:",length);
		App_Tcp_Write(pcb,Tcp_Server_SendBuf,length,1);
			
		Send_DisBuf_Flag=1;
		Net_RecvType=2;
			
		Send_DisBuf_Length=999*5+100+2;		
			
		Send_DisBuf_Cou=0;
			
		
			
		pSend_DisBuf=(unsigned char *)WBuf;
			
		*pSend_DisBuf++=Pro_data.pro_num;
		*pSend_DisBuf++=Pro_data.pro_num>>8;
			
			
		 pdn=(uint8_t*)K_SIZE_sdram;				
		 if(prog_order<301)
		 {
			pdn+=(Pro_data.pro_num-1)*(999*5+100);
			memcpy(pSend_DisBuf,pdn,999*5+100);
		 }
		 else
		 {
		 pdn+=PROG_BYTES1*PROG_GROPU1+(Pro_data.pro_num-PROG_GROPU1-1)*PROG_BYTES2;//(Net_Recv_ProgNum-300-1)*(399*5+100)+300*(999*5+100);	 			
		 memcpy(pSend_DisBuf,pdn,399*5+100);			 
		 }
		 
			
		pSend_DisBuf=(unsigned char *)WBuf;			
			
		Send_DisBuf_Time=0;
		Send_DisBuf_DelayTime=50;//延时10mS后发送数据
			
			/*
		Send_DisBuf_Flag=1;
		Send_DisBuf_Length=800*600*2;
		pSend_DisBuf=(unsigned char *)LCD_VRAM_BASE_ADDR;
			Send_DisBuf_Time=0;
			Send_DisBuf_DelayTime=10;//延时10mS后发送数据			
			*/
		return;
			
		}	
		
	
	if(strcmp(net_recvdata,"{\"Get:AllKnifeData\"}")==0)//传递所有刀数据
		{//?????
		length=strlen("AllKnifeData:");
		memcpy(Tcp_Server_SendBuf,"AllKnifeData:",length);
		App_Tcp_Write(pcb,Tcp_Server_SendBuf,length,1);
			
			

			
			/*
		Send_DisBuf_Flag=1;
		Send_DisBuf_Length=800*600*2;
		pSend_DisBuf=(unsigned char *)LCD_VRAM_BASE_ADDR;
			Send_DisBuf_Time=0;
			Send_DisBuf_DelayTime=10;//延时10mS后发送数据			
			*/
		}			
		
		memcpy(strtemp,net_recvdata,20);
		strtemp[20]=0;
		
		
	if(strcmp(strtemp,"{\"Set:OneKnifeData\"}")==0)//传递所有刀数据
		{//?????
			
	//	ASCII_Printf("Knife Recv", ASCII1632_MODE, ASCII1632_WIDTH, ASCII1632_HIGH, ASCII1632, 350, 300, 0xffff, 0);
		strtemp[0]=net_recvdata[21];
		strtemp[1]=net_recvdata[22];
		strtemp[2]=net_recvdata[23];
		strtemp[3]=net_recvdata[24];
		strtemp[4]=0;
			
//////		ASCII_Printf(strtemp, ASCII1632_MODE, ASCII1632_WIDTH, ASCII1632_HIGH, ASCII1632, 400, 300, 0xffff, 0);
			
		Net_Recv_ProgNum=(uint16_t)(strtemp[0]-0x30)*1000+(uint16_t)(strtemp[1]-0x30)*100+(uint16_t)(strtemp[2]-0x30)*10+(uint16_t)(strtemp[3]-0x30);
			
		strtemp[0]=net_recvdata[26];
		strtemp[1]=net_recvdata[27];
		strtemp[2]=net_recvdata[28];
		strtemp[3]=net_recvdata[29];
		strtemp[4]=0;
			
////////		ASCII_Printf(strtemp, ASCII1632_MODE, ASCII1632_WIDTH, ASCII1632_HIGH, ASCII1632, 400, 340, 0xffff, 0);
			
		Net_Recv_KnifeNum=(uint16_t)(strtemp[0]-0x30)*1000+(uint16_t)(strtemp[1]-0x30)*100+(uint16_t)(strtemp[2]-0x30)*10+(uint16_t)(strtemp[3]-0x30);
		
		
//////						sprintf(strtemp,"%d",	Net_Recv_KnifeNum);
//////							ASCII_Printf(strtemp, ASCII1632_MODE, ASCII1632_WIDTH, ASCII1632_HIGH, ASCII1632, 400, 400, 0xffff, 0);
					
			
		Net_RecvData_Flag=1;
		
		Net_RecvType=1;
		
		pNet_Recv=(uint8_t*)Tcp_Server_RecvBuf;							
		Net_Recv_PageCou=0;		
		Net_Recv_Page=Net_Recv_KnifeNum * 5 + 100;
								
		
		
			/*
		length=strlen("AllKnifeData:");
		memcpy(Tcp_Server_SendBuf,"AllKnifeData:",length);
		App_Tcp_Write(pcb,Tcp_Server_SendBuf,length,1);
			*/
			
			/*
		Send_DisBuf_Flag=1;
		Send_DisBuf_Length=800*600*2;
		pSend_DisBuf=(unsigned char *)LCD_VRAM_BASE_ADDR;
			Send_DisBuf_Time=0;
			Send_DisBuf_DelayTime=10;//延时10mS后发送数据			
			*/
		}
		
	if(strcmp(strtemp,"{\"Get:NetConfig\"}")==0)//传递所有刀数据
		{//?????
		length=strlen("NetConfig:");
		memcpy(Tcp_Server_SendBuf,"NetConfig:",length);
		App_Tcp_Write(pcb,Tcp_Server_SendBuf,length,1);
			
		Send_DisBuf_Flag=1;
		//Net_RecvType=2;
			
		Send_DisBuf_Length=18;		
			
		Send_DisBuf_Cou=0;
			
		
			
		pSend_DisBuf=(unsigned char *)WBuf;
			
		*pSend_DisBuf++=  nNetConfig_t.Net_Gw_Add[0];
		*pSend_DisBuf++= 	nNetConfig_t.Net_Gw_Add[1];
		*pSend_DisBuf++=  nNetConfig_t.Net_Gw_Add[2];
		*pSend_DisBuf++= 	nNetConfig_t.Net_Gw_Add[3];
			
			
		*pSend_DisBuf++= 	nNetConfig_t.Net_Ip_Add[0];//=192;
		*pSend_DisBuf++= 	nNetConfig_t.Net_Ip_Add[1];//=168;
		*pSend_DisBuf++= 	nNetConfig_t.Net_Ip_Add[2];//=3;
		*pSend_DisBuf++= 	nNetConfig_t.Net_Ip_Add[3];//=18;//默认IP为  192.168.0.18
			
		*pSend_DisBuf++= nNetConfig_t.Net_Mask_Add[0];//=255;
		*pSend_DisBuf++= 	nNetConfig_t.Net_Mask_Add[1];//=255;
		*pSend_DisBuf++= 	nNetConfig_t.Net_Mask_Add[2];//=255;
		*pSend_DisBuf++= 	nNetConfig_t.Net_Mask_Add[3];//=0;//默认MASK   255.255.255.0
			
		*pSend_DisBuf++= 	nNetConfig_t.Net_Mac_Add[0];//=0x31;
		*pSend_DisBuf++= 	nNetConfig_t.Net_Mac_Add[1];//=0x00;
		*pSend_DisBuf++= 	nNetConfig_t.Net_Mac_Add[2];//=0x10;
		*pSend_DisBuf++= 	nNetConfig_t.Net_Mac_Add[3];//=0x68;
		*pSend_DisBuf++= 	nNetConfig_t.Net_Mac_Add[4];//=0x47;
		*pSend_DisBuf++= 	nNetConfig_t.Net_Mac_Add[5];//=0x58;
			
		pSend_DisBuf=(unsigned char *)WBuf;			
			
		Send_DisBuf_Time=0;
		Send_DisBuf_DelayTime=50;//延时10mS后发送数据
			
			/*
		Send_DisBuf_Flag=1;
		Send_DisBuf_Length=800*600*2;
		pSend_DisBuf=(unsigned char *)LCD_VRAM_BASE_ADDR;
			Send_DisBuf_Time=0;
			Send_DisBuf_DelayTime=10;//延时10mS后发送数据			
			*/
		return;
			
		}
		
		
	}			
}



uint8_t  Net_Recv_File_Process(void)
{
	/*
	//接收文件相关
uint8_t Net_Recv_File_StepCou;//接收步骤
uint8_t Net_Recv_File_Flag=0;
uint8_t Net_Recv_File_HeadEnter_Flag=0;
uint32_t Net_Recv_File_Length=0;
char Net_Recv_File_FileName[256];
uint32_t Net_Recv_File_Cou=0;
uint8_t Net_Recv_File_Buf[2048*2048];//2M空间
	
*/
int length;
uint8_t strtemp[64];
	if(Net_Recv_File_Flag==0)
		{
			
		memcpy(strtemp,lwip_server_buf,13);
		strtemp[13]=0;
		if(strcmp(strtemp,"{\"Send:Msg\"}")==0)//传递所有刀数据
		{//?????
			
		Net_Recv_File_Flag=1;//置接收文件标志
			Net_Recv_TimeOut=0;
		Net_Recv_File_StepCou=1;
		//sprintf(strtemp,"%d",	Send_DisBuf_Cou);
			
		length=strlen("Ask_Ok");//回复应答
		memcpy(Tcp_Server_SendBuf,"Ask_Ok",length);
		App_Tcp_Write(Tcp_Queue_pcb,Tcp_Server_SendBuf,length,1);
			
			
	//ASCII_Printf("Now Recv File", ASCII1632_MODE, ASCII1632_WIDTH, ASCII1632_HIGH, ASCII1632, 400, 400, 0xffff, 0);			
		return 1;
		}
		else
		{
			Net_Recv_File_StepCou=0;
			return 0;
		}
		
	}
else
	{
	switch(Net_Recv_File_StepCou)
		{
		case 1://接收文件名
			if(Net_Recv_TimeOut>3*1000)
					{//接收超时
					Net_Recv_File_StepCou=0;
					Net_Recv_File_Flag=0;
					return 1;						
					}
			Net_Recv_TimeOut=0;
			memcpy(Net_Recv_File_FileName,lwip_server_buf,Tcp_RecvLength);
			Net_Recv_File_FileName[Tcp_RecvLength]=0;
			Net_Recv_File_StepCou++;		//跳转到接收长度
		//	Printf24(Net_Recv_File_FileName,10,100,RED_COLOR,0,0xffff);
			
			length=strlen("Ask_Ok");//回复应答
			memcpy(Tcp_Server_SendBuf,"Ask_Ok",length);
			App_Tcp_Write(Tcp_Queue_pcb,Tcp_Server_SendBuf,length,1);
					
			break;
		case 2://接收文件长度
			
			if(Net_Recv_TimeOut>3*1000)
					{//接收超时
					Net_Recv_File_StepCou=0;
					Net_Recv_File_Flag=0;
					return 1;						
					}		
						Net_Recv_TimeOut=0;
			if(Tcp_RecvLength!=8)
				{	//长度出错，退出
				Net_Recv_File_StepCou=0;
				Net_Recv_File_Flag=0;
				return 1;
				}
				
				
			//	strtemp
				
				Net_Recv_File_Length=(uint32_t)((lwip_server_buf[0]-0x30))*10000000;
				Net_Recv_File_Length+=(uint32_t)((lwip_server_buf[1]-0x30))*1000000;
				Net_Recv_File_Length+=(uint32_t)((lwip_server_buf[2]-0x30))*100000;
				Net_Recv_File_Length+=(uint32_t)((lwip_server_buf[3]-0x30))*10000;
				Net_Recv_File_Length+=(uint32_t)((lwip_server_buf[4]-0x30))*1000;
				Net_Recv_File_Length+=(uint32_t)((lwip_server_buf[5]-0x30))*100;
				Net_Recv_File_Length+=(uint32_t)((lwip_server_buf[6]-0x30))*10;
				Net_Recv_File_Length+=(uint32_t)((lwip_server_buf[7]-0x30));
				
			/*
			Net_Recv_File_Length=lwip_server_buf[0];
			Net_Recv_File_Length<<=8;
			Net_Recv_File_Length+=lwip_server_buf[1];
			Net_Recv_File_Length<<=8;
			Net_Recv_File_Length+=lwip_server_buf[2];
			Net_Recv_File_Length<<=8;
			Net_Recv_File_Length+=lwip_server_buf[3];				
				*/
			Net_Recv_File_Cou=0;
			pNet_Recv_File_Buf=(uint8_t*)DOWNFILE_SDRAM_ADD;	
			Net_Recv_File_StepCou++;		//跳转到接收数据	
				
	//		sprintf(strtemp,"%d",	Net_Recv_File_Length);
	//	ASCII_Printf(strtemp, ASCII1632_MODE, ASCII1632_WIDTH, ASCII1632_HIGH, ASCII1632, 400, 432, 0xffff, 0);		
							length=strlen("Ask_Ok");//回复应答
			memcpy(Tcp_Server_SendBuf,"Ask_Ok",length);
			App_Tcp_Write(Tcp_Queue_pcb,Tcp_Server_SendBuf,length,1);
			break;
		case 3://接收文件数据
			if(Net_Recv_TimeOut>3*1000)
					{//接收超时
					Net_Recv_File_StepCou=0;
					Net_Recv_File_Flag=0;
					return 1;						
					}			
						Net_Recv_TimeOut=0;
			memcpy(pNet_Recv_File_Buf,lwip_server_buf,Tcp_RecvLength);		
			Net_Recv_File_Cou+=Tcp_RecvLength;
		  if(Net_Recv_File_Cou>=Net_Recv_File_Length)
					{//长度已到,结束
					Net_Recv_File_StepCou=0;
					Net_Recv_File_Flag=0;					
						
						
					Message_Msg_Update(lwip_server_buf);//新信息保存
						
				//	Message_Msg_File_Save();//进行信息保存
						
					}		
	//		sprintf(strtemp,"%d",	Net_Recv_File_Cou);
	//		ASCII_Printf(strtemp, ASCII1632_MODE, ASCII1632_WIDTH, ASCII1632_HIGH, ASCII1632, 400, 464, 0xffff, 0);							
			return 1;
			break;	
		}
	}
}



void SavePro_NetRecv_headInfo(Int16U prog, pInt8U pdata)//spi保存一个程序的 头(程序名+ 时间 +刀数 )
{
Int32U offset,add;
pInt8U pbuf;
Int16U i;
if(prog<=(PROG_GROPU1+1))  //前301个prog
   {
   offset=PROG_BYTES1*(prog-1);
   }
else//后  199
   {
   offset=PROG_BYTES1*PROG_GROPU1+(prog-PROG_GROPU1-1)*PROG_BYTES2;
   }
pbuf=(pInt8U)(K_SIZE_sdram+offset);//程序基地址
//pdata=(pInt8U)&OnePro_head;
//////////for(i=0;i<PRO_HEAD_BYTES;i++)		//更新buf
//////////	{
//////////	*(pbuf+i)=*(pdata+i);
//////////	}
	
add=DATA_SAVE_OFFSET+offset;
Write_25pe_data((pInt8U)pbuf, add, PRO_HEAD_BYTES);
// Write_25pe_data((pInt8U)pdata, add, PRO_HEAD_BYTES);	//保存
}


void Net_Process_SendDisBuf(void)
{
	int len;
char strtemp[64];
//unsigned char * pdu;pdu=(unsigned char *)LCD_VRAM_BASE_ADDR;
if(Send_DisBuf_Flag==1)
	{
		
	if(Send_DisBuf_DelayTime>0)
		{
			Send_DisBuf_DelayTime--;
			return;
		}
	//while(pSend_DisBuf<(LCD_VRAM_BASE_ADDR+800*600*2))
	//{
		
	len = tcp_sndbuf(Tcp_Queue_pcb);
	if(len<2000)
		return;
		
	App_Tcp_Write(Tcp_Queue_pcb,pSend_DisBuf,1024,1);
		Send_DisBuf_Cou+=1024;
	pSend_DisBuf+=1024;
	//	Send_DisBuf_Flag=0;
////////								sprintf(strtemp,"%d",	Send_DisBuf_Cou);
////////							ASCII_Printf(strtemp, ASCII1632_MODE, ASCII1632_WIDTH, ASCII1632_HIGH, ASCII1632, 400, 400, 0xffff, 0);
	//}
		
//////			if(Send_DisBuf_Cou>=10*1024)//;//LCD_VRAM_BASE_ADDR+Send_DisBuf_Length))
//////			Send_DisBuf_Flag=0;
	if(Send_DisBuf_Cou>=Send_DisBuf_Length)//;//LCD_VRAM_BASE_ADDR+Send_DisBuf_Length))
			Send_DisBuf_Flag=0;	
	
	}
}


void Read_OneKnifeDataToBuf(unsigned char *buf,uint16_t knifenum)
{

	
}




