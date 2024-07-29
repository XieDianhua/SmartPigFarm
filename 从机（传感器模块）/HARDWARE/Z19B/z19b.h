#ifndef _Z19B_H
#define _Z19B_H

#include "sys.h" 

#define USART_CO2_REC_LEN  			200  	//�����������ֽ��� 200
#define EN_USART_CO2_RX 			1		//ʹ�ܣ�1��/��ֹ��0������1����


extern u8  USART_CO2_RX_BUF[USART_CO2_REC_LEN]; //���ջ���,���USART_REC_LEN���ֽ�.ĩ�ֽ�Ϊ���з� 
extern u16 USART_CO2_RX_STA;         		//����״̬���	
//����봮���жϽ��գ��벻Ҫע�����º궨��
void co2_uart_init(u32 bound);
u8 CO2_Get_Date(void);
#endif