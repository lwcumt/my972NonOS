#ifndef _SDCOPY_H
#define _SDCOPY_H
#include"main.h"

extern void SDInsert_Check(void);
extern void SD_FileReadAndWriteToNandFlash(void);

extern Int8U mf_scan_files(Int8U * path);
#endif