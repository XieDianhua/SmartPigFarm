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

  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);	//那1?邦?“那㊣?¯3那㊣?車
 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO|RCC_APB2Periph_GPIOF|RCC_APB2Periph_GPIOA, ENABLE);  //那1?邦GPIO赤a谷豕o赤?∩車?AFIO那㊣?車
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOE,GPIO_PinSource2);

  TIM_DeInit(TIM3);
	
	TIM_TimeBaseStructure.TIM_Period = arr2; //谷豕???迆??辰????邦D?那??t℅～豕????‘米?℅??‘??℅～????∩??¯?邦?迆米??米	 ??那y米?5000?a500ms
	TIM_TimeBaseStructure.TIM_Prescaler =psc2; //谷豕??車?角∩℅¯?aTIMx那㊣?車?米?那3y那y米??∟﹞??米?米  10Khz米???那y?米?那  
	TIM_TimeBaseStructure.TIM_ClockDivision = 0; //谷豕??那㊣?車﹞???:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM?辰谷???那y?㏒那?
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure); //?迄?YTIM_TimeBaseInitStruct?D???“米?2?那y3?那??‘TIMx米?那㊣???迄那y米ㄓ??
 
	TIM_ITConfig(TIM3,TIM_IT_Update,ENABLE ); //那1?邦???“米?TIM3?D??,?那D赤?邦D??D??


  //谷豕????辰y???a?∩車?那?3?1|?邦,那?3?TIM3 CH2米?PWM??3?2“D?	GPIOA.7
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7; //TIM_CH2
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;  //?∩車?赤?赤足那?3?
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);//3?那??‘GPIO
	
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;//|GPIO_Pin_4;//dir辰??～oe3?那??‘ 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;   
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOF, &GPIO_InitStructure);//3?那??‘GPIO
	
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0; //TIM_CH2
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;;  //?∩車?赤?赤足那?3?
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);//3?那??‘GPIO
//		GPIO_Init(GPIOB, &GPIO_InitStructure);					//?迄?Y谷豕?“2?那y3?那??‘GPIOC
//	GPIO_SetBits(GPIOB,GPIO_Pin_0);		
	
	
	PUSH_OE2 = 0;
	PUSH_DIR2 =1 ;
	//3?那??‘TIM3 Channel 2 PWM?㏒那?	 
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2; //?????“那㊣?¯?㏒那?:TIM??3??赤?豕米¯???㏒那?2
 	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //㊣豕??那?3?那1?邦
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High; //那?3???D?:TIM那?3?㊣豕????D???
	TIM_OCInitStructure.TIM_Pulse = arr2>>1;
	TIM_OC2Init(TIM3, &TIM_OCInitStructure);  //?迄?YT???“米?2?那y3?那??‘赤a谷豕TIM3 OC2
	TIM_ITConfig(TIM3,TIM_IT_Update,ENABLE ); //那1?邦???“米?TIM3?D??,?那D赤?邦D??D??

	NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;  //TIM3?D??
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;  //?豕??車??豕??0??
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;  //∩車車??豕??3??
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //IRQ赤“米角㊣?那1?邦
	NVIC_Init(&NVIC_InitStructure);  //?迄?YNVIC_InitStruct?D???“米?2?那y3?那??‘赤a谷豕NVIC??∩??¯
	
	TIM_Cmd(TIM3, DISABLE);  //TIM3
}


void TIM3_rote(int num2,u16 speed2)//num2 ??3?那y ㏒?speed2?迄?豕
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
	  TIM_SetAutoreload(TIM3,speed2);  //℅??‘??℅～???米
	  TIM_Cmd(TIM3, ENABLE);  //那1?邦TIM3
	}
}



void TIM3_IRQHandler(void) 
{
	if (TIM_GetITStatus(TIM3, TIM_IT_Update) != RESET) //?足2谷???“米?TIM?D??﹞⊿谷迆車?﹞?:TIM ?D???∩ 
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
		TIM_ClearITPendingBit(TIM3, TIM_IT_Update);  //??3yTIMx米??D??∩y∩|角赤??:TIM ?D???∩
		}		
}
