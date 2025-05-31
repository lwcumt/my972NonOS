
#ifndef _DOWNLOAD_H
#define _DOWNLOAD_H

#include"comm.h"
#include"nandflash.h"
//#include"nf_table.h"
#include"file.h"






/*
typedef struct {

	unsigned char bCommHead:8;
	unsigned char bCommCommd:8;
	unsigned int iCommLength:32;
	unsigned char bCommChecksum:8;

} DOWNFILE_COMM_HEAD; // GCC
*/

extern void DownFile_Exec(void);

//extern void FileWriteToSPI(unsigned int add);//д�뵽SPIFLASH


#endif
