#ifndef _USART3_H_
#define _USART3_H_

#include "sys.h"//其中包含了stm32主头文件

typedef unsigned char bool;//定义布尔类型

#define USART3_REC_LEN 200 //定义最大接收字节  200

extern u16 USART3_RX_STA;	//串口3接收状态标志，通过最后两位判断接收状态
extern u8 USART3_RX_BUF[USART3_REC_LEN];//接收缓冲，最大USART3_REC_LEN个字节,末字节为换行符
extern u8 endFlag;

extern void usart3_init(u32 bound);
#endif