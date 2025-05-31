#include "spi_config.h"

Int8U fdata[16];

void Spi_Init(void)
{

	Int8U d;
Int32U add;
pInt8U testdata;
	int i;

    /* Configure multi function pins to SPI0 */
    outpw(REG_SYS_GPB_MFPL, (inpw(REG_SYS_GPB_MFPL) & ~0xff000000) | 0xBB000000);
    outpw(REG_SYS_GPB_MFPH, (inpw(REG_SYS_GPB_MFPH) & ~0xFFF000ff) | 0xBBB000BB);
	SPI0_SEL_DIS;
	SPI0_SEL_OUT;

    spiInit(1);
    spiOpen(1);



    // set spi interface speed to 2MHz
    spiIoctl(1, SPI_IOC_SET_SPEED, 20000000, 0);
    // set transfer length to 8-bit
    spiIoctl(1, SPI_IOC_SET_TX_BITLEN, 8, 0);
    // set transfer mode to mode-0
    spiIoctl(1, SPI_IOC_SET_MODE, 0, 0);

    // check flash id
   uFlashID = SpiFlash_ReadMidDid();
	 
	 Read_DevID();


for(i=0;i<16;i++)
	fdata[i]=i+0x30;


add=1024;//µØÖ·

Write_25pe_data(fdata, add, 4);



testdata=fdata;
add=1024;//µØÖ·

FastRead_Datas_Start(add);
for(d=0;d<4;d++)
   {
   *testdata++=ReadFlash_Datas();
   }
FlashChip_Dis;







}



char SpiTranserByte(char ch)
{
//  while ( !(S0SPSR & SPI_F) );
        spiWrite(1, 0, ch);
        spiIoctl(1, SPI_IOC_TRIGGER, 0, 0);
        while(spiGetBusyStatus(1));
        return(spiRead(1, 0));
}


uint16_t SpiFlash_ReadMidDid(void)
{
    uint8_t u8RxData[2];

    // /CS: active
  // spiIoctl(1, SPI_IOC_ENABLE_SS, SPI_SS_SS0, 0);

	FlashChip_En;

    // send Command: 0x90, Read Manufacturer/Device ID
    spiWrite(1, 0, 0x90);
    spiIoctl(1, SPI_IOC_TRIGGER, 0, 0);
    while(spiGetBusyStatus(1));

    // send 24-bit '0', dummy
    spiWrite(1, 0, 0x00);
    spiIoctl(1, SPI_IOC_TRIGGER, 0, 0);
    while(spiGetBusyStatus(1));

    spiWrite(1, 0, 0x00);
    spiIoctl(1, SPI_IOC_TRIGGER, 0, 0);
    while(spiGetBusyStatus(1));

    spiWrite(1, 0, 0x00);
    spiIoctl(1, SPI_IOC_TRIGGER, 0, 0);
    while(spiGetBusyStatus(1));

    // receive 16-bit
    spiWrite(1, 0, 0x00);
    spiIoctl(1, SPI_IOC_TRIGGER, 0, 0);
    while(spiGetBusyStatus(1));
    u8RxData[0] = spiRead(0, 0);

    spiWrite(1, 0, 0x00);
    spiIoctl(1, SPI_IOC_TRIGGER, 0, 0);
    while(spiGetBusyStatus(1));
    u8RxData[1] = spiRead(0, 0);

    // /CS: de-active

	FlashChip_Dis;
    //spiIoctl(1, SPI_IOC_DISABLE_SS, SPI_SS_SS0, 0);

    return ( (u8RxData[0]<<8) | u8RxData[1] );
}