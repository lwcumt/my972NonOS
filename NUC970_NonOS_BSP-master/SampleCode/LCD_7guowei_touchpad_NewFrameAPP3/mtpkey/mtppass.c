#include "mtppass.h"
unsigned int MtpKeydat[8];

unsigned int MTPUserData=0x78;
unsigned int MTPKey[8]={
0x885a2130,
0x1b345870,
0x97546211,
0x21cafdea,
0x5eafdc23,
0x78deaa9a,
0x885ad671,
0x987cbe19
};

static void dump_mtp_status()
{
	int    cnt;
	UINT8  user_data;
	int i;
	unsigned int *keyptr;
	keyptr=MTP->KEY;
	for(i=0;i<8;i++)
	MtpKeydat[i]=*keyptr++;
	
    sysprintf("MTP_STATUS: 0x%x\n", MTP->STATUS);
    if (MTP->STATUS & MTP_STATUS_MTPEN)
    	sysprintf(" ENABLED");
    if (MTP->STATUS & MTP_STATUS_KEYVALID)
    	sysprintf(" KEY_VALID");
    if (MTP->STATUS & MTP_STATUS_NONPRG)
    	sysprintf(" NO_KEY");
    if (MTP->STATUS & MTP_STATUS_LOCKED)
    	sysprintf(" LOCKED");
    if (MTP->STATUS & MTP_STATUS_PRGFAIL)
    	sysprintf(" PROG_FAIL");
    if (MTP->STATUS & MTP_STATUS_BUSY)
    	sysprintf(" BUSY");
    cnt = MTP_GetPrgCount();
    if (cnt >= 0)
    	sysprintf("  PRGCNT=%d\n", MTP_GetPrgCount());
    else
    	sysprintf("\n");
    
    if (MTP_GetUserData(&user_data) == MTP_RET_OK)
    	sysprintf("USER_DATA: 0x%x\n", user_data);
    
    sysprintf("MTP Key is %s.\n", MTP_IsKeyLocked() ? "locked" : "not locked");
}


void ReadMtpKey(void)
{
#ifdef MTPCODE
	MtpKey_Program();
#endif
	
if (MTP_Enable() != MTP_RET_OK)
				{
					sysprintf("Failed to enable MTP!\n");

				}

	dump_mtp_status();

}



void MtpKey_Program(void)
{

if (MTP_Program(MTPKey,MTPUserData) == MTP_RET_OK)
		sysprintf("MTP key program done.\n");
else
		sysprintf("Failed to program MTP key!\n");	
while(1);	
}


