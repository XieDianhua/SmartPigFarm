#include "led.h"

//风扇电平IO输出口
void LED_Init(void)
{
 GPIO_InitTypeDef  GPIO_InitStructure;
 	
 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOG, ENABLE);	 //使能P.G端口时钟
	
 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15;	//PG.13、PG.14、PG.15端口配置
 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //推挽输出
 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO口速度为50MHz
 GPIO_Init(GPIOG, &GPIO_InitStructure);					 //根据设定参数初始化PG.13、PG.14、PG.15
 GPIO_ResetBits(GPIOG,GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15);		//PG.13、PG.14、PG.15初始设置为输出低
}
 
