#include "i2c_config.h"
#include "io.h"
#include "gtp.h"

void I2C0_Init(void)
{
int rtval;
    /* Configure multi function pins to I2C0 &   I2C1 */
    outpw(REG_SYS_GPG_MFPL, (inpw(REG_SYS_GPG_MFPL) & ~0x00ff) | 0x88);
    i2cInit(0);

    rtval = i2cOpen((PVOID)I2CNUM_0);
    if(rtval < 0) {

		rtval=100;
      //  sysprintf("Open I2C0 error!\n");
      //  goto exit_test;
    }
    i2cIoctl(I2CNUM_0, I2C_IOC_SET_DEV_ADDRESS, GT911_DEVADD, 0);  /* On 910 EV board, set 0x50 for I2C0 */
    i2cIoctl(I2CNUM_0, I2C_IOC_SET_SPEED, 400, 0);
}



void I2C0_WriteData(unsigned char devadd,unsigned char iadd,unsigned char d)
{

i2cIoctl(I2CNUM_0, I2C_IOC_SET_SUB_ADDRESS, iadd, 1);
i2cWrite(I2CNUM_0,&d, 1);

}



unsigned char  I2C0_ReadData(unsigned char devadd,unsigned char iadd)
{
unsigned char rdata;
i2cIoctl(I2CNUM_0, I2C_IOC_SET_SUB_ADDRESS, iadd, 1);
i2cRead(I2CNUM_0, &rdata, 1);
return rdata;
}


void I2C0_Test(vodi)
{
I2C0_Init();



}