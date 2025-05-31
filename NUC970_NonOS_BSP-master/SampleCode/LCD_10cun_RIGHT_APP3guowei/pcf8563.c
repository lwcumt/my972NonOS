
#include "pcf8563.h"


unsigned char Sec,Min,Hour,Dow,Dom,Month;
int Doy,Year;

void write_time(void)
{
    unsigned char w_t_temp;

	I2C_WriteData(PCF8563_DEV_ADD,0,0);
	I2C_WriteData(PCF8563_DEV_ADD,1,0);
	I2C_WriteData(PCF8563_DEV_ADD,2,Sec);
	I2C_WriteData(PCF8563_DEV_ADD,3,Min);//Twi_w_oneByte(3,w_t_temp);
	I2C_WriteData(PCF8563_DEV_ADD,4,Hour);//Twi_w_oneByte(4,w_t_temp);
	I2C_WriteData(PCF8563_DEV_ADD,5,Dom);//Twi_w_oneByte(5,w_t_temp);
	

	I2C_WriteData(PCF8563_DEV_ADD,6,Dow);//Twi_w_oneByte(6,w_t_temp);

	I2C_WriteData(PCF8563_DEV_ADD,7,Month);//Twi_w_oneByte(7,w_t_temp);
	

	I2C_WriteData(PCF8563_DEV_ADD,8,Year);//Twi_w_oneByte(8,w_t_temp);
}


void read_time(void)
{
unsigned char i;
    unsigned char r_t_temp[7];
//    Twi_r_Bytes(r_t_temp,7,2);

	for(i=2;i<9;i++)
		{
		r_t_temp[i-2]=I2C_ReadData(PCF8563_DEV_ADD,i);
		}

Sec=r_t_temp[0]&0x7f;//***
Min=r_t_temp[1]&0x7f;
Hour=r_t_temp[2]&0x3f;
Dom=r_t_temp[3]&0x3f;
Dow=r_t_temp[4];
Month=r_t_temp[5]&0x1f;
Year=r_t_temp[6];
}



void I2C_WriteData(unsigned char devadd,unsigned char iadd,unsigned char d)
{

i2cIoctl(I2CNUM_1, I2C_IOC_SET_SUB_ADDRESS, iadd, 1);
i2cWrite(I2CNUM_1,&d, 1);

}



unsigned char  I2C_ReadData(unsigned char devadd,unsigned char iadd)
{
unsigned char rdata;
i2cIoctl(I2CNUM_1, I2C_IOC_SET_SUB_ADDRESS, iadd, 1);
i2cRead(I2CNUM_1, &rdata, 1);
return rdata;
}
