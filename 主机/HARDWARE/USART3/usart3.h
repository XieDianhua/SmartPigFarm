#ifndef _USART3_H_
#define _USART3_H_

#include "sys.h"//���а�����stm32��ͷ�ļ�

typedef unsigned char bool;//���岼������

#define USART3_REC_LEN 200 //�����������ֽ�  200

extern u16 USART3_RX_STA;	//����3����״̬��־��ͨ�������λ�жϽ���״̬
extern u8 USART3_RX_BUF[USART3_REC_LEN];//���ջ��壬���USART3_REC_LEN���ֽ�,ĩ�ֽ�Ϊ���з�
extern u8 endFlag;

extern void usart3_init(u32 bound);
#endif