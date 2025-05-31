
#include "code.h"

#include "file.h"
#include "key.h"
#include"m25pe16.h"
#include "chndot.h"



BOARD_CODE MainBoard_Code;




Int8U decodeApp_flag;


void ReadAppCode(pInt8U pdata)
{
// pInt8U pdata;
Int32U add,n;
add=ORIGINAL_25PEADD+CODE_ADD;
FastRead_Datas_Start(add);
for(n=0;n<20;n++)
	{
	*pdata++=ReadFlash_Datas();
	}
FlashChip_Dis;
}

void SaveAppCode(pInt8U pdata)
{
Int32U add,n;
add=ORIGINAL_25PEADD+CODE_ADD;
Write_25pe_data(pdata, add, 20);
}

Int8U DecodeAppExec(void)
{
Int8U i=0,codeErr_flag=1;
// Int16U b_arry[10]={0};
Int32U block=5;
BOARD_CODE code_temp;
pInt8U pCode1,pCode2;
File_GetSectorTable(); //读取nand 系统块信息
if(iFileSectorInfo.iFileStartSector != 0xffff)
	{
	while(i<10)
		{
			if(iFileSectorInfo.iFileInvalidSector[i]!=0xffff)
				block+=iFileSectorInfo.iFileInvalidSector[i++];
			else 
				break;
		}
	MainBoard_Code.nand_blocks=block;
	MainBoard_Code.core_ID[0]=SERIAL_ID0;
	MainBoard_Code.core_ID[1]=SERIAL_ID1;
	MainBoard_Code.core_ID[2]=SERIAL_ID2;
	MainBoard_Code.core_ID[3]=SERIAL_ID3;
	pCode1=(pInt8U)&code_temp;
	pCode2=(pInt8U)&MainBoard_Code;
	ReadAppCode(pCode1);
	for(i=0;i<20;i++)
		{
		if(*pCode1++ != *pCode2++)
			break;
		}
	if(i >= 20)
		return 1;
	}
// Printf32("非法操作，程序无效！",300,200,RED_COLOR,1,WHITE_COLOR);
ASCII_Printf("Invalid Programme!",64+1,16,32,ASCII1632, 300,200,RED_COLOR,WHITE_COLOR);
return 0;
}


void CodeAppExec(void)
{
Int8U i=0;
Int32U block=5;
File_GetSectorTable(); //读取nand 系统块信息
if(iFileSectorInfo.iFileStartSector == 0xffff)	//未格式化
	{
	Nand_Format();
	}
//---code----------
while(i<10)
	{
		if(iFileSectorInfo.iFileInvalidSector[i]!=0xffff)
			block+=iFileSectorInfo.iFileInvalidSector[i++];
		else 
			break;
	}
MainBoard_Code.nand_blocks=block;
MainBoard_Code.core_ID[0]=SERIAL_ID0;
MainBoard_Code.core_ID[1]=SERIAL_ID1;
MainBoard_Code.core_ID[2]=SERIAL_ID2;
MainBoard_Code.core_ID[3]=SERIAL_ID3;
SaveAppCode((pInt8U)&MainBoard_Code);
// Printf32("code ok！",300,200,RED_COLOR,1,WHITE_COLOR);
ASCII_Printf("Code OK!",64+1,16,32,ASCII1632, 300,200,RED_COLOR,WHITE_COLOR);
}



