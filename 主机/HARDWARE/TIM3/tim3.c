#include "tim3.h"
#include "delay.h"
//#include "usart.h" 
//#include "key.h"
//#include "tim5.h"
// GPIOA.7
#include "led.h"
u8 TIM3_finish = STOPP;
u16 TIM3_step = 0;
int mb2;
//TIM3 CH2

void TIM3_init(u16 arr2,u16 psc2)
{
  GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_OCInitTypeDef  TIM_OCInitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);	//��1?��?������?��3����?��
 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO|RCC_APB2Periph_GPIOF|RCC_APB2Periph_GPIOA, ENABLE);  //��1?��GPIO��a����o��?�䨮?AFIO����?��
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOE,GPIO_PinSource2);

  TIM_DeInit(TIM3);
	
	TIM_TimeBaseStructure.TIM_Period = arr2; //����???��??��????��D?��??t���㨨????����?��??��??����????��??��?��?����??��	 ??��y��?5000?a500ms
	TIM_TimeBaseStructure.TIM_Prescaler =psc2; //����??��?�������?aTIMx����?��?��?��3y��y��??�衤??��?��  10Khz��???��y?��?��  
	TIM_TimeBaseStructure.TIM_ClockDivision = 0; //����??����?����???:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM?����???��y?�꨺?
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure); //?��?YTIM_TimeBaseInitStruct?D???����?2?��y3?��??��TIMx��?����???����y�̣�??
 
	TIM_ITConfig(TIM3,TIM_IT_Update,ENABLE ); //��1?��???����?TIM3?D??,?��D��?��D??D??


  //����????��y???a?�䨮?��?3?1|?��,��?3?TIM3 CH2��?PWM??3?2��D?	GPIOA.7
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7; //TIM_CH2
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;  //?�䨮?��?������?3?
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);//3?��??��GPIO
	
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;//|GPIO_Pin_4;//dir��??��oe3?��??�� 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;   
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOF, &GPIO_InitStructure);//3?��??��GPIO
	
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0; //TIM_CH2
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;;  //?�䨮?��?������?3?
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);//3?��??��GPIO
//		GPIO_Init(GPIOB, &GPIO_InitStructure);					//?��?Y����?��2?��y3?��??��GPIOC
//	GPIO_SetBits(GPIOB,GPIO_Pin_0);		
	
	
	PUSH_OE2 = 0;
	PUSH_DIR2 =1 ;
	//3?��??��TIM3 Channel 2 PWM?�꨺?	 
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2; //?????������?��?�꨺?:TIM??3??��?���̡�???�꨺?2
 	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //����??��?3?��1?��
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High; //��?3???D?:TIM��?3?����????D???
	TIM_OCInitStructure.TIM_Pulse = arr2>>1;
	TIM_OC2Init(TIM3, &TIM_OCInitStructure);  //?��?YT???����?2?��y3?��??����a����TIM3 OC2
	TIM_ITConfig(TIM3,TIM_IT_Update,ENABLE ); //��1?��???����?TIM3?D??,?��D��?��D??D??

	NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;  //TIM3?D??
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;  //?��??��??��??0??
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;  //�䨮��??��??3??
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //IRQ�����̨���?��1?��
	NVIC_Init(&NVIC_InitStructure);  //?��?YNVIC_InitStruct?D???����?2?��y3?��??����a����NVIC??��??��
	
	TIM_Cmd(TIM3, DISABLE);  //TIM3
}


void TIM3_rote(int num2,u16 speed2)//num2 ??3?��y ��?speed2?��?��
{
	if( TIM3_finish == STOPP)
	{
		TIM3_finish = 1;
		if(num2<0)
		{
		num2 = -num2;
		PUSH_DIR2 = 0;
		}
		else
		{
		PUSH_DIR2 = 1;
		}
	  mb2 = num2;
	  TIM3_step = 0;
	  TIM_SetAutoreload(TIM3,speed2);  //��??��??����???��
	  TIM_Cmd(TIM3, ENABLE);  //��1?��TIM3
	}
}



void TIM3_IRQHandler(void) 
{
	if (TIM_GetITStatus(TIM3, TIM_IT_Update) != RESET) //?��2��???����?TIM?D??���騦����?��?:TIM ?D???�� 
		{
			if(TIM3_finish!=STOPP)
			{
			TIM3_step++;
			if(TIM3_step == mb2)
			 {
				 TIM3_finish = STOPP;
		    TIM3_step = 0;
				TIM3_finish = STOPP;
				TIM_Cmd(TIM3, DISABLE);
       
			 }
		 }
		TIM_ClearITPendingBit(TIM3, TIM_IT_Update);  //??3yTIMx��??D??��y��|����??:TIM ?D???��
		}		
}
