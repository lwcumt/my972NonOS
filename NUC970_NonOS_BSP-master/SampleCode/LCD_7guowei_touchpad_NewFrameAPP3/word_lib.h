
#ifndef _WORD_LIB_H
#define _WORD_LIB_H

#include "drv_glcd.h"
#include"download.h"

#include "pic_exec.h"
//#define zk_nf_addr 0x20000
#define zk_nf_length ((2+4+5+128+288+512)*2048)

#define ZF16_sdram (df_zk_sdram)
#define ZF24_sdram (ZF16_sdram+2048*2)
#define ZF32_sdram (ZF24_sdram+2048*4)

#define ZK16_sdram (ZF32_sdram+2048*5)
#define ZK24_sdram (ZK16_sdram+2048*128)
#define ZK32_sdram (ZK24_sdram+2048*288)



extern unsigned char HanZi[];//32*32µÄºº×Ö»º³åÇø


void ZK_Read16(unsigned char *hzp);
void HZK_Printf16(unsigned int x,unsigned int y,unsigned short int color,
				 unsigned char b,unsigned short int fillcolor);
				 
void ZF_Read16(unsigned char *zfp);
void ZF_Printf16(unsigned int x,unsigned int y,unsigned short int color,
				 unsigned char b,unsigned short int fillcolor);
				 
void ZK_Read24(unsigned char *hzp);
void HZK_Printf24(unsigned int x,unsigned int y,unsigned short int color,
				 unsigned char b,unsigned short int fillcolor);
				 
void ZF_Read24(unsigned char *zfp);
void ZF_Printf24(unsigned int x,unsigned int y,unsigned short int color,
				 unsigned char b,unsigned short int fillcolor);
				 
void ZK_Read32(unsigned char *hzp);
void HZK_Printf32(unsigned int x,unsigned int y,unsigned short int color,
				 unsigned char b,unsigned short int fillcolor);
				 
void ZF_Read32(unsigned char *zfp);				 
void ZF_Printf32(unsigned int x,unsigned int y,unsigned short int color,
				 unsigned char b,unsigned short int fillcolor);
				 
				 
				 
				 
extern void Printf16(unsigned char *chn,unsigned int x,
              unsigned int y,unsigned short int color,
			  unsigned char b,unsigned short int fillcolor);
extern void Printf32(unsigned char *chn,unsigned int x,
              unsigned int y,unsigned short int color,
			  unsigned char b,unsigned short int fillcolor);
extern void Printf24(unsigned char *chn,unsigned int x,
              unsigned int y,unsigned short int color,
			  unsigned char b,unsigned short int fillcolor);





#endif
