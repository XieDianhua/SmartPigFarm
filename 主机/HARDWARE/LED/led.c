#include "led.h"

//���ȵ�ƽIO�����
void LED_Init(void)
{
 GPIO_InitTypeDef  GPIO_InitStructure;
 	
 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOG, ENABLE);	 //ʹ��P.G�˿�ʱ��
	
 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15;	//PG.13��PG.14��PG.15�˿�����
 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //�������
 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO���ٶ�Ϊ50MHz
 GPIO_Init(GPIOG, &GPIO_InitStructure);					 //�����趨������ʼ��PG.13��PG.14��PG.15
 GPIO_ResetBits(GPIOG,GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15);		//PG.13��PG.14��PG.15��ʼ����Ϊ�����
}
 
