
//#include "board.h"
//#include "sys.h"
//#include"at45dbnew.h"
//#include "extm_drv.h"

#include "main.h"

#include "drv_glcd.h"

#ifndef __PIC_H
#define __PIC_H





extern void DrawPic_SDRAM(long sect,int x,int y,int picwidth,int pichigh);
extern void DrawPic_IntFlash16(const Int16U *pic,int x,int y,int picwidth,int pichigh);
extern void DrawPic_DATAFLASH(long sect,int x,int y,int picwidth,int pichigh);
extern void LoadDataFlashToSDRAM(pInt16U p,int da,  int dlenth);

extern const Int16U PIC_TEST[];
extern const Int16U PIC_REDTUIPROCESSBAR[];
extern const Int16U PIC_TUIPROCESSBAR[];

//刀上图标  64*64
extern const Int16U PIC_DAOSHANG[];

//刀下图标  64*64  
extern const Int16U PIC_DAOXIA[];

//压上图标  64*64
extern const Int16U PIC_YASHANG[];
extern const Int16U PIC_YAXIA[];
extern const Int16U PIC_TUIZHIQI[];

extern const Int16U PIC_BEIJING[];
extern const Int16U PIC_SHOUZHNAG[];
extern const Int16U PIC_REDDAO[];
extern const Int16U PIC_GREENDAO[];

#endif


