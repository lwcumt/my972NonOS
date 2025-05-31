#include "nand_config.h"
#include "nandflash.h"

/*-----------------------------------------------------------------------------
 * Define some constants for BCH
 *---------------------------------------------------------------------------*/
// define the total padding bytes for 512/1024 data segment
#define BCH_PADDING_LEN_512     32
#define BCH_PADDING_LEN_1024    64
// define the BCH parity code lenght for 512 bytes data pattern
#define BCH_PARITY_LEN_T4  8
#define BCH_PARITY_LEN_T8  15
#define BCH_PARITY_LEN_T12 23
#define BCH_PARITY_LEN_T15 29
// define the BCH parity code lenght for 1024 bytes data pattern
#define BCH_PARITY_LEN_T24 45


#define BCH_T15   0x00400000
#define BCH_T12   0x00200000
#define BCH_T8    0x00100000
#define BCH_T4    0x00080000
#define BCH_T24   0x00040000

 Int8U Nand_Config(void)
 {
	 
  /* initialize nand_chip data structure */
  //  nand->IO_ADDR_R = (void *)REG_NANDDATA;
   // nand->IO_ADDR_W = (void *)REG_NANDDATA;

  

    /* initial NAND controller */
    outpw(REG_CLK_HCLKEN, (inpw(REG_CLK_HCLKEN) | 0x300000));

    /* select NAND function pins */

        /* Set GPC0~14 for NAND */
        outpw(REG_SYS_GPC_MFPL, 0x55555555);
        outpw(REG_SYS_GPC_MFPH, 0x05555555);


    // Enable SM_EN
    outpw(REG_FMI_CTL, NAND_EN);
    outpw(REG_NANDTMCTL, 0x20305);

    // Enable SM_CS0
    outpw(REG_NANDCTL, (inpw(REG_NANDCTL)&(~0x06000000))|0x02000000);
    outpw(REG_NANDECTL, 0x1); /* un-lock write protect */

    // NAND Reset
    outpw(REG_NANDCTL, inpw(REG_NANDCTL) | 0x1);    // software reset
    while (inpw(REG_NANDCTL) & 0x1);
    outpw(REG_NANDCTL, (inpw(REG_NANDCTL)&(~0x30000)) + 0x10000);//2048byte /page
		
		Nand_Reset();
		Nand_ReadID();
	if(NandID==0xecf10095)
		return 0;
	else 
		return 1;

 }