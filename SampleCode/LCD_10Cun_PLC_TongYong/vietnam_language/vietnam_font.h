#ifndef __VIETNAM_FONT_H
#define __VIETNAM_FONT_H

#define VIETNAM_FUN_EN     1   //越南语 功能 开关


extern unsigned char const Viet_Font24_Pic_1[];  // 
extern unsigned char const Viet_Font24_Pic_2[];  // 
extern unsigned char const Viet_Font24_Pic_63[]; // 

void vietnam_print(unsigned char *pic,int x,int y,unsigned short fcolor,unsigned char bflag,unsigned int bkcolor);

#endif