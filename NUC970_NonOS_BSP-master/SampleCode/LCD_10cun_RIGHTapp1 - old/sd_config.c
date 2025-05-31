#include "sd_config.h"



#include "ff.h"
#include "diskio.h"
#include "file.h"
#include "nandflash.h"


#define BUFF_SIZE       (64*1024)

static UINT blen = BUFF_SIZE;
DWORD acc_size;                         /* Work register for fs command */
WORD acc_files, acc_dirs;
FILINFO Finfo;

char Line[256];                         /* Console input buffer */
#if _USE_LFN
char Lfname[512];
#endif

__align(32) BYTE Buff_Pool[BUFF_SIZE] ;       /* Working buffer */

BYTE  *Buff;

void timer_init()
{
    sysprintf("timer_init() To do...\n");
}

uint32_t get_timer_value()
{
    sysprintf("get_timer_value() To do...\n");
    return 1;
}
BYTE SD_Drv; // select SD0

void  dump_buff_hex(uint8_t *pucBuff, int nBytes)
{
    int     nIdx, i;

    nIdx = 0;
    while (nBytes > 0) {
        sysprintf("0x%04X  ", nIdx);
        for (i = 0; i < 16; i++)
            sysprintf("%02x ", pucBuff[nIdx + i]);
        sysprintf("  ");
        for (i = 0; i < 16; i++) {
            if ((pucBuff[nIdx + i] >= 0x20) && (pucBuff[nIdx + i] < 127))
                sysprintf("%c", pucBuff[nIdx + i]);
            else
                sysprintf(".");
            nBytes--;
        }
        nIdx += 16;
        sysprintf("\n");
    }
    sysprintf("\n");
}


/*--------------------------------------------------------------------------*/
/* Monitor                                                                  */

/*----------------------------------------------*/
/* Get a value of the string                    */
/*----------------------------------------------*/
/*  "123 -5   0x3ff 0b1111 0377  w "
        ^                           1st call returns 123 and next ptr
           ^                        2nd call returns -5 and next ptr
                   ^                3rd call returns 1023 and next ptr
                          ^         4th call returns 15 and next ptr
                               ^    5th call returns 255 and next ptr
                                  ^ 6th call fails and returns 0
*/

int xatoi (         /* 0:Failed, 1:Successful */
    TCHAR **str,    /* Pointer to pointer to the string */
    long *res       /* Pointer to a variable to store the value */
)
{
    unsigned long val;
    unsigned char r, s = 0;
    TCHAR c;


    *res = 0;
    while ((c = **str) == ' ') (*str)++;    /* Skip leading spaces */

    if (c == '-') {     /* negative? */
        s = 1;
        c = *(++(*str));
    }

    if (c == '0') {
        c = *(++(*str));
        switch (c) {
        case 'x':       /* hexadecimal */
            r = 16;
            c = *(++(*str));
            break;
        case 'b':       /* binary */
            r = 2;
            c = *(++(*str));
            break;
        default:
            if (c <= ' ') return 1; /* single zero */
            if (c < '0' || c > '9') return 0;   /* invalid char */
            r = 8;      /* octal */
        }
    } else {
        if (c < '0' || c > '9') return 0;   /* EOL or invalid char */
        r = 10;         /* decimal */
    }

    val = 0;
    while (c > ' ') {
        if (c >= 'a') c -= 0x20;
        c -= '0';
        if (c >= 17) {
            c -= 7;
            if (c <= 9) return 0;   /* invalid char */
        }
        if (c >= r) return 0;       /* invalid char for current radix */
        val = val * r + c;
        c = *(++(*str));
    }
    if (s) val = 0 - val;           /* apply sign if needed */

    *res = val;
    return 1;
}


/*----------------------------------------------*/
/* Dump a block of byte array                   */

void put_dump (
    const unsigned char* buff,  /* Pointer to the byte array to be dumped */
    unsigned long addr,         /* Heading address value */
    int cnt                     /* Number of bytes to be dumped */
)
{
    int i;


    sysprintf("%08x ", addr);

    for (i = 0; i < cnt; i++)
        sysprintf(" %02x", buff[i]);

    sysprintf(" ");
    for (i = 0; i < cnt; i++)
        sysPutChar((TCHAR)((buff[i] >= ' ' && buff[i] <= '~') ? buff[i] : '.'));

    sysprintf("\n");
}


/*--------------------------------------------------------------------------*/
/* Monitor                                                                  */
/*--------------------------------------------------------------------------*/

static
FRESULT scan_files (
    char* path      /* Pointer to the path name working buffer */
)
{
    DIR dirs;
    FRESULT res;
    BYTE i;
    char *fn;


    if ((res = f_opendir(&dirs, path)) == FR_OK) {
        i = strlen(path);
        while (((res = f_readdir(&dirs, &Finfo)) == FR_OK) && Finfo.fname[0]) {
            if (_FS_RPATH && Finfo.fname[0] == '.') continue;
#if _USE_LFN
            fn = *Finfo.lfname ? Finfo.lfname : Finfo.fname;
#else
            fn = Finfo.fname;
#endif
            if (Finfo.fattrib & AM_DIR) {
                acc_dirs++;
                *(path+i) = '/';
                strcpy(path+i+1, fn);
                res = scan_files(path);
                *(path+i) = '\0';
                if (res != FR_OK) break;
            } else {
                /*              sysprintf("%s/%s\n", path, fn); */
                acc_files++;
                acc_size += Finfo.fsize;
            }
        }
    }

    return res;
}



void put_rc (FRESULT rc)
{
    const TCHAR *p =
        _T("OK\0DISK_ERR\0INT_ERR\0NOT_READY\0NO_FILE\0NO_PATH\0INVALID_NAME\0")
        _T("DENIED\0EXIST\0INVALID_OBJECT\0WRITE_PROTECTED\0INVALID_DRIVE\0")
        _T("NOT_ENABLED\0NO_FILE_SYSTEM\0MKFS_ABORTED\0TIMEOUT\0LOCKED\0")
        _T("NOT_ENOUGH_CORE\0TOO_MANY_OPEN_FILES\0");
    //FRESULT i;
    uint32_t i;
    for (i = 0; (i != (UINT)rc) && *p; i++) {
        while(*p++) ;
    }
    sysprintf(_T("rc=%d FR_%s\n"), (UINT)rc, p);
}

/*----------------------------------------------*/
/* Get a line from the input                    */
/*----------------------------------------------*/

void get_line (char *buff, int len)
{
    TCHAR c;
    int idx = 0;



    for (;;) {
        c = sysGetChar();
        sysPutChar(c);
        if (c == '\r') break;
        if ((c == '\b') && idx) idx--;
        if ((c >= ' ') && (idx < len - 1)) buff[idx++] = c;
    }
    buff[idx] = 0;

    sysPutChar('\n');

}


void SDH_IRQHandler(void)
{
    unsigned int volatile isr;

    // FMI data abort interrupt
    if (inpw(REG_SDH_GINTSTS) & SDH_GINTSTS_DTAIF_Msk) {
        /* ResetAllEngine() */
        outpw(REG_SDH_GCTL, inpw(REG_SDH_GCTL) | SDH_GCTL_GCTLRST_Msk);
        outpw(REG_SDH_GINTSTS, SDH_GINTSTS_DTAIF_Msk);
    }

    //----- SD interrupt status
    isr = inpw(REG_SDH_INTSTS);
    if (isr & SDH_INTSTS_BLKDIF_Msk) {      // block down
        _sd_SDDataReady = TRUE;
        outpw(REG_SDH_INTSTS, SDH_INTSTS_BLKDIF_Msk);
    }

    if (isr & SDH_INTSTS_CDIF0_Msk) { // port 0 card detect
        //----- SD interrupt status
        // it is work to delay 50 times for SD_CLK = 200KHz
        {
            volatile int i;         // delay 30 fail, 50 OK
            for (i=0; i<0x500; i++);   // delay to make sure got updated value from REG_SDISR.
            isr = inpw(REG_SDH_INTSTS);
        }

#ifdef _USE_DAT3_DETECT_
        if (!(isr & SDH_INTSTS_CDSTS0_Msk)) {
            SD0.IsCardInsert = FALSE;
            sysprintf("\nCard Remove!\n");
            SD_Close_Disk(0);
        } else {
            SD_Open_Disk(SD_PORT0 | CardDetect_From_DAT3);
        }
#else
        if (isr & SDH_INTSTS_CDSTS0_Msk) {
            SD0.IsCardInsert = FALSE;   // SDISR_CD_Card = 1 means card remove for GPIO mode
            sysprintf("\nCard Remove!\n");
            SD_Close_Disk(0);
        } else {
            SD_Open_Disk(SD_PORT0 | CardDetect_From_GPIO);
        }
#endif

        outpw(REG_SDH_INTSTS, SDH_INTSTS_CDIF0_Msk);
    }

    if (isr & SDH_INTSTS_CDIF1_Msk) { // port 1 card detect
        //----- SD interrupt status
        // it is work to delay 50 times for SD_CLK = 200KHz
        {
            volatile int i;         // delay 30 fail, 50 OK
            for (i=0; i<0x500; i++);   // delay to make sure got updated value from REG_SDISR.
            isr = inpw(REG_SDH_INTSTS);
        }

#ifdef _USE_DAT3_DETECT_
        if (!(isr & SDH_INTSTS_CDSTS1_Msk)) {
            SD0.IsCardInsert = FALSE;
            sysprintf("\nCard Remove!\n");
            SD_Close_Disk(1);
        } else {
            SD_Open_Disk(SD_PORT1 | CardDetect_From_DAT3);
        }
#else
        if (isr & SDH_INTSTS_CDSTS1_Msk) {
            SD0.IsCardInsert = FALSE;   // SDISR_CD_Card = 1 means card remove for GPIO mode
            sysprintf("\nCard Remove!\n");
            SD_Close_Disk(1);
        } else {
            SD_Open_Disk(SD_PORT1 | CardDetect_From_GPIO);
        }
#endif

        outpw(REG_SDH_INTSTS, SDH_INTSTS_CDIF1_Msk);
    }

    // CRC error interrupt
    if (isr & SDH_INTSTS_CRCIF_Msk) {
        if (!(isr & SDH_INTSTS_CRC16_Msk)) {
            //sysprintf("***** ISR sdioIntHandler(): CRC_16 error !\n");
            // handle CRC error
        } else if (!(isr & SDH_INTSTS_CRC7_Msk)) {
            extern unsigned int _sd_uR3_CMD;
            if (! _sd_uR3_CMD) {
                //sysprintf("***** ISR sdioIntHandler(): CRC_7 error !\n");
                // handle CRC error
            }
        }
        outpw(REG_SDH_INTSTS, SDH_INTSTS_CRCIF_Msk);      // clear interrupt flag
    }
}

void SDH_Init(void)
{
    /* enable SDH */
    outpw(REG_CLK_HCLKEN, inpw(REG_CLK_HCLKEN) | 0x40000000);

    /* select multi-function-pin */
    /* SD Port 0 -> PD0~7 */
    outpw(REG_SYS_GPD_MFPL, 0x06666666);
    SD_Drv = 0;
	
	/*

#if 0 // port 1
    ///* initial SD1 pin -> PE2~9 * /
    outpw(REG_SYS_GPE_MFPL, inpw(REG_SYS_GPE_MFPL) & ~0xffffff00 | 0x66666600);
    outpw(REG_SYS_GPE_MFPH, inpw(REG_SYS_GPE_MFPH) & ~0x000000ff | 0x00000066);

   // /* initial SD1 pin -> PH6~13 * /
    outpw(REG_SYS_GPH_MFPL, inpw(REG_SYS_GPH_MFPL) & ~0xff000000 | 0x66000000);
    outpw(REG_SYS_GPH_MFPH, inpw(REG_SYS_GPH_MFPH) & ~0x00ffffff | 0x00666666);

    ///* initial SD1 pin -> PI5~10, 12~13 * /
    outpw(REG_SYS_GPI_MFPL, inpw(REG_SYS_GPI_MFPL) & ~0xfff00000 | 0x44400000);
    outpw(REG_SYS_GPI_MFPH, inpw(REG_SYS_GPI_MFPH) & ~0x00ff0fff | 0x00440444);
    SD_Drv = 1;
#endif
*/

}


/*---------------------------------------------------------*/
/* User Provided RTC Function for FatFs module             */
/*---------------------------------------------------------*/
/* This is a real time clock service to be called from     */
/* FatFs module. Any valid time must be returned even if   */
/* the system does not support an RTC.                     */
/* This function is not required in read-only cfg.         */

unsigned long get_fattime (void)
{
    unsigned long tmr;

    tmr=0x00000;

    return tmr;
}


 FIL file1, file2;        /* File objects */

/*----------------------------------------------------------------------------
  MAIN function
 *----------------------------------------------------------------------------*/
void SD_main(void)
{
    char        *ptr, *ptr2;
    long        p1, p2, p3;
    BYTE        *buf;
    FATFS       *fs;              /* Pointer to file system object */
	//	FATFS fs1; 
    TCHAR       sd_path[] ="0:"; //{ '0', ':', 0 };    /* SD drive started from 0 */
   // FRESULT     res;UINT br;
    DIR dir;                /* Directory object */
    UINT s1, s2, cnt;
		
    static const BYTE ft[] = {0, 12, 16, 32};
    DWORD ofs = 0, sect = 0;
/*
    sysInitializeUART();
    sysprintf("\n");
    sysprintf("===============================================\n");
    sysprintf("          SDH/SD Card Testing                  \n");
    sysprintf("===============================================\n");

    sysDisableCache();
    sysInvalidCache();
    sysSetMMUMappingMethod(MMU_DIRECT_MAPPING);
    sysEnableCache(CACHE_WRITE_BACK);

    Buff = (BYTE *)((UINT32)&Buff_Pool[0] | 0x80000000);  // /* use non-cache buffer *
*/
    SDH_Init();
	

    sysInstallISR(HIGH_LEVEL_SENSITIVE|IRQ_LEVEL_1, SDH_IRQn, (PVOID)SDH_IRQHandler);
    /* enable CPSR I bit */
    sysSetLocalInterrupt(ENABLE_IRQ);
    sysEnableInterrupt(SDH_IRQn);

    /*--- init timer ---*/
    sysSetTimerReferenceClock (TIMER0, 12000000);
    sysStartTimer(TIMER0, 100, PERIODIC_MODE);

    sysprintf("\n\nNUC970 SD FATFS TEST!\n");
    SD_SetReferenceClock(300000);
    SD_Open_Disk(SD_PORT0 | CardDetect_From_GPIO);
    f_chdrive(sd_path);          /* set default path */
//SD_FileReadAndWriteToNandFlash();//¿½±´SDÎÄ¼þ

/*
  // f_mount(fs,sd_path, 1);
		// res = f_open(&file1, "test.txt", FA_OPEN_EXISTING | FA_READ);
	 res = f_open(&file1, "×Ö¿â_0x20000.FON", FA_OPEN_EXISTING | FA_READ);
	 
 //  res = f_open(&fsrc,"×Ö¿â_0x20000.FON", FA_OPEN_EXISTING | FA_READ);	 //???????
  if(res==FR_NO_FILE||res==FR_INVALID_NAME){
   //f_mount(fs,sd_path, 0);
  }
  else
  {
	iFiles.FileLength=file1.fsize;
    res = f_read(&file1, (unsigned char *)DOWNFILE_SDRAM_ADD, fsrc.fsize, &br);
	f_close(&file1);

 Nand_Format();//É¾³ý²¢±ê¼Ç»µ¿é
	ChangeFileName("test.txt");
	//NandEccWrite_Flag=0;
	File_Create(iFiles.FileName);//????
	  }

	  */

    

}



/*** (C) COPYRIGHT 2015 Nuvoton Technology Corp. ***/
