#ifndef __TIM3_H
#define __TIM3_H

//PB0方向		PF2使能		PA7信号
#include "sys.h"
#define YES 1
#define NO 0
#define PUSH_DIR2 PBout(0) 
#define PUSH_OE2 PFout(2) 
#define STOPP 0


extern u8 tim3_finish;

void TIM3_init(u16 arr2,u16 psc2);

void TIM3_half(u16 speed2);

void TIM3_rote(int num2,u16 speed2);




#endif


