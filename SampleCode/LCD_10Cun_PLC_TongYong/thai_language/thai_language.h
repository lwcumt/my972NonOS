#ifndef _THAI_LANGUAGE_H
#define _THAI_LANGUAGE_H

extern unsigned short const Thai_Font17_Pic_ZiDao1[];
extern unsigned short const Thai_Font17_Pic_ZiDao2[];

extern unsigned short const Thai_Font17_Pic_ShiFouJiXuZiDao1[];
extern unsigned short const Thai_Font17_Pic_ShiFouJiXuZiDao2[];
extern unsigned short const Thai_Font17_Pic_TZQ[] ;

extern unsigned short const Thai_Font17_Pic_ACSERVO_ERR[];

void Thai_Test(void);
void ThaiFont_Read(char *thai_char);
void ThaiFont_Read24(char *thai_char);
void Printf_Thai(char *thai_str,int x,int y,int discolor,unsigned char bfill,int backcolor);
void Printf_Thai24(char *thai_str,int x,int y,int discolor,unsigned char bfill,int backcolor);

void Thai_Printf12(unsigned int x,unsigned int y,unsigned short int color,
				 unsigned char b,unsigned short int fillcolor);

void Thai_Printf24(unsigned int x,unsigned int y,unsigned short int color,
				 unsigned char b,unsigned short int fillcolor);

//*******************************************
// ͼƬģʽ
void Thai_Draw(unsigned short *tpic,int x,int y,unsigned short fcolor,unsigned char bflag,unsigned int bkcolor);

#endif

