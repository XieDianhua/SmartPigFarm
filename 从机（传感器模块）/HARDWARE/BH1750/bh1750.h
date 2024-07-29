#ifndef _BH1750_H_
#define _BH1750_H_

#include "myiic.h"

//指令集
/*************************************************************/
#define BHAddWrite     0x46      //L写地址
#define BHAddRead      0x47      //L读地址
#define BHPowDown      0x00      //关闭模块
#define BHPowOn        0x01      //打开模块等待测量指令
#define BHReset        0x07      //重置
#define BHModeH1       0x10      //高分辨率模式1
#define BHModeH2       0x11      //高分辨率模式2
#define BHModeL        0x13      //连续低分辨率模式
#define BHSigModeH     0x20      //一次高分辨率模式1
#define BHSigModeH2    0x21      //一次高分辨率模式2
#define BHSigModeL     0x23      //一次低分辨率模式
/*************************************************************/

void BH_DateSend(u8 command);
u8 BH_DateRead(void);
//u16 BH_Measure(void);
#endif