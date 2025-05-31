#include "sysiotest.h"
#include "io.h"


void SysIO_Test(void)
{
int sysiotesttime=0;
	int stesttime=0;
AOUT1_CLR();
AOUT2_CLR();
AOUT3_CLR();
AOUT4_CLR();
AOUT5_CLR();
RLOUT1_OFF;
RLOUT2_OFF;
RLOUT3_OFF;
RLOUT4_OFF;
RLOUT1_1_OFF;
RLOUT5_OFF;
stesttime=5000000;
while(stesttime--);
	stesttime=0;
while(1)
	{
	stesttime++;
	if(stesttime>1000000)
	{
		stesttime=0;
		sysiotesttime++;
	switch(sysiotesttime)
			{
		case 1:
			AOUT1_SET();
			break;
		
		case 2:
			AOUT2_SET();
			break;

				case 3:
			AOUT3_SET();
			break;
				
		case 4:
			AOUT4_SET();
			break;

				case 5:
			AOUT5_SET();
			break;
				
				
		case 6:
			RLOUT1_OFF;
			break;		

		case 7:
			RLOUT2_OFF;
			break;	

				case 8:
			RLOUT3_OFF;
			break;	
		
				
		case 9:
			RLOUT4_OFF;
			break;	

			case 10:
			RLOUT1_1_OFF;
			break;	
				
			case 11:
			RLOUT5_OFF;
			break;	


		case 12:
			AOUT1_CLR();
			break;
		
		case 13:
			AOUT2_CLR();
			break;

				case 14:
			AOUT3_CLR();
			break;
				
		case 15:
			AOUT4_CLR();
			break;

				case 16:
			AOUT5_CLR();
			break;
				
				
		case 17:
			RLOUT1_ON;
			break;		

		case 18:
			RLOUT2_ON;
			break;	

				case 19:
			RLOUT3_ON;
			break;	
		
				
		case 20:
			RLOUT4_ON;
			break;	

			case 21:
			RLOUT1_1_ON;
			break;	
				
			case 22:
			RLOUT5_ON;
			break;	
			
			}
		if(sysiotesttime>=22)
			sysiotesttime=0;
		}
	}

}
