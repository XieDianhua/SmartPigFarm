#ifndef __TIM5_H
#define __TIM5_H

//PF5方向		 PF3使能		PA1信号
#include "sys.h"
#define YES 1
#define NO 0
#define PUSH_DIR PFout(5)  //推动电机的方向口
#define PUSH_OE PFout(3) 
#define STOP 0


extern u8 tim5_finish;

void TIM5_init(u16 arr,u16 psc);

void TIM5_half(u16 speed);

void TIM5_rote(int num,u16 speed);

//void TIM5_INIT(void);


#endif


