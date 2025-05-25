#ifndef _OPTIMIZE_CUT_H
#define _OPTIMIZE_CUT_H

#include "main.h"



extern unsigned short OptimizeCut_DelayTime;//优化裁切延时  //需要保存

extern unsigned char OptimizeCut_Enb_Flag;//优化裁切 允许

extern unsigned char Optimize_Cut_DelayTime_DownLoad_Flag;

extern unsigned char FastCut_Enb_Flag;


void OptimizeCut_LoadData(void);			//装载的优化裁切延时数据
void OptimizeCut_SaveData(void);			//保存的优化裁切延时数据
#endif
