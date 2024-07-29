#ifndef _Z19B_H
#define _Z19B_H

#include "sys.h" 

#define USART_CO2_REC_LEN  			200  	//定义最大接收字节数 200
#define EN_USART_CO2_RX 			1		//使能（1）/禁止（0）串口1接收


extern u8  USART_CO2_RX_BUF[USART_CO2_REC_LEN]; //接收缓冲,最大USART_REC_LEN个字节.末字节为换行符 
extern u16 USART_CO2_RX_STA;         		//接收状态标记	
//如果想串口中断接收，请不要注释以下宏定义
void co2_uart_init(u32 bound);
u8 CO2_Get_Date(void);
#endif