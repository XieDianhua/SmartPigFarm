#include "tim5.h"
#include "delay.h"
#include "led.h"

u8 TIM5_finish = STOP;
u16 TIM5_step = 0;
int mb;
//TIM5 CH2

void TIM5_init(u16 arr,u16 psc)
{
  GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_OCInitTypeDef  TIM_OCInitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM5, ENABLE);	//ʹ�ܶ�ʱ��5ʱ��
 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA| RCC_APB2Periph_GPIOF|RCC_APB2Periph_AFIO, ENABLE);  //ʹ��GPIO����͸���AFIOʱ��

  TIM_DeInit(TIM5);
	
	TIM_TimeBaseStructure.TIM_Period = arr; //��������һ�������¼�װ�����Զ���װ�ؼĴ������ڵ�ֵ	 ������5000Ϊ500ms
	TIM_TimeBaseStructure.TIM_Prescaler =psc; //����������ΪTIMxʱ��Ƶ�ʳ�����Ԥ��Ƶֵ  10Khz�ļ���Ƶ��  
	TIM_TimeBaseStructure.TIM_ClockDivision = 0; //����ʱ�ӷָ�:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM���ϼ���ģʽ
	TIM_TimeBaseInit(TIM5, &TIM_TimeBaseStructure); //����TIM_TimeBaseInitStruct��ָ���Ĳ�����ʼ��TIMx��ʱ�������λ
 
	TIM_ITConfig(TIM5,TIM_IT_Update,ENABLE); //ʹ��ָ����TIM5�ж�,��������ж�


  //���ø�����Ϊ�����������,���TIM5 CH2��PWM���岨��	GPIOA.1
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1; //TIM_CH2
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;  //�����������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);//��ʼ��GPIO
	
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3|GPIO_Pin_5;//dir�Լ�oe��ʼ�� 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;   
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOF, &GPIO_InitStructure);//��ʼ��GPIO
	PUSH_OE = 0;
	PUSH_DIR =1 ;
	//��ʼ��TIM5 Channel 2 PWMģʽ	 
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2; //ѡ��ʱ��ģʽ:TIM�����ȵ���ģʽ2
 	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //�Ƚ����ʹ��
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High; //�������:TIM����Ƚϼ��Ը�
	TIM_OCInitStructure.TIM_Pulse = arr>>1;
	TIM_OC2Init(TIM5, &TIM_OCInitStructure);  //����Tָ���Ĳ�����ʼ������TIM5 OC2
	TIM_ITConfig(TIM5,TIM_IT_Update,ENABLE ); //ʹ��ָ����TIM3�ж�,��������ж�

	NVIC_InitStructure.NVIC_IRQChannel = TIM5_IRQn;  //TIM3�ж�
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;  //��ռ���ȼ�0��
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;  //�����ȼ�3��
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //IRQͨ����ʹ��
	NVIC_Init(&NVIC_InitStructure);  //����NVIC_InitStruct��ָ���Ĳ�����ʼ������NVIC�Ĵ���
	
	TIM_Cmd(TIM5, DISABLE);  //TIM5
}


void TIM5_rote(int num,u16 speed)//num ������ ��speed�ٶ�
{
	//TIM_Cmd(TIM5, ENABLE);  //ʹ��TIM5
	if( TIM5_finish == STOP)
	{
		TIM5_finish = 1;
		if(num<0)
		{
		num = -num;
		PUSH_DIR = 0;
		}
		else
		{
		PUSH_DIR = 1;
		}
	  mb = num;
	  TIM5_step = 0;
	  TIM_SetAutoreload(TIM5,speed);  //�Զ���װ��ֵ
	  TIM_Cmd(TIM5, ENABLE);  //ʹ��TIM5
	}
}



void TIM5_IRQHandler(void) {
	if (TIM_GetITStatus(TIM5, TIM_IT_Update) != RESET) //���ָ����TIM�жϷ������:TIM �ж�Դ 
		{
			if(TIM5_finish!=STOP)
			{
			TIM5_step++;
				 
			if(TIM5_step == mb)
			 {
				 TIM5_finish = STOP;
		    TIM5_step = 0;
				TIM5_finish = STOP;
				TIM_Cmd(TIM5, DISABLE);
       
			 }
		 }
		TIM_ClearITPendingBit(TIM5, TIM_IT_Update);  //���TIMx���жϴ�����λ:TIM �ж�Դ
		}		
}



