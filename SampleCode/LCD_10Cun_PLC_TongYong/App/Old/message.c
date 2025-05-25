#include "message.h"

//#include "net_process.h"
//#include "lwip/tcp.h"
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
//#include "tcpserver.h"



void Message_Save(void)
{
	
	
	
}

void Message_Load(void)
{
	
	
	
}


void Message_Reader(char * message_date)
{
	
	
}



void Message_NewIn(uint8_t m_newcout)
{
GLCD_Circle_Fill(780-16, 600-24,10,RED_COLOR,RED_COLOR);// centerx, Int32S centery, Int32U radius, Int16U Linecolor, Int16U Boardcolor)//bresenhamª≠‘≤À„∑®
//m_newcout++;
		
			if(m_newcout<10)
			{
				Bcd[0]=m_newcout+0x30;
				Bcd[1]=0;
				Printf16((char*)Bcd,780-16-2, 600-32,WHITE_COLOR,0,BLUE_COLOR);
			}
		else
			{
			Bcd[0]=m_newcout/10+0x30;
			Bcd[1]=m_newcout%10+0x30;
			Bcd[2]=0;
			Printf16((char*)Bcd,780-16-8, 600-32,WHITE_COLOR,0,BLUE_COLOR);
			}		
}



