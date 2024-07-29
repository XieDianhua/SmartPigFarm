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

  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM5, ENABLE);	//使能定时器5时钟
 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA| RCC_APB2Periph_GPIOF|RCC_APB2Periph_AFIO, ENABLE);  //使能GPIO外设和复用AFIO时钟

  TIM_DeInit(TIM5);
	
	TIM_TimeBaseStructure.TIM_Period = arr; //设置在下一个更新事件装入活动的自动重装载寄存器周期的值	 计数到5000为500ms
	TIM_TimeBaseStructure.TIM_Prescaler =psc; //设置用来作为TIMx时钟频率除数的预分频值  10Khz的计数频率  
	TIM_TimeBaseStructure.TIM_ClockDivision = 0; //设置时钟分割:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM向上计数模式
	TIM_TimeBaseInit(TIM5, &TIM_TimeBaseStructure); //根据TIM_TimeBaseInitStruct中指定的参数初始化TIMx的时间基数单位
 
	TIM_ITConfig(TIM5,TIM_IT_Update,ENABLE); //使能指定的TIM5中断,允许更新中断


  //设置该引脚为复用输出功能,输出TIM5 CH2的PWM脉冲波形	GPIOA.1
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1; //TIM_CH2
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;  //复用推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);//初始化GPIO
	
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3|GPIO_Pin_5;//dir以及oe初始化 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;   
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOF, &GPIO_InitStructure);//初始化GPIO
	PUSH_OE = 0;
	PUSH_DIR =1 ;
	//初始化TIM5 Channel 2 PWM模式	 
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2; //选择定时器模式:TIM脉冲宽度调制模式2
 	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //比较输出使能
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High; //输出极性:TIM输出比较极性高
	TIM_OCInitStructure.TIM_Pulse = arr>>1;
	TIM_OC2Init(TIM5, &TIM_OCInitStructure);  //根据T指定的参数初始化外设TIM5 OC2
	TIM_ITConfig(TIM5,TIM_IT_Update,ENABLE ); //使能指定的TIM3中断,允许更新中断

	NVIC_InitStructure.NVIC_IRQChannel = TIM5_IRQn;  //TIM3中断
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;  //先占优先级0级
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;  //从优先级3级
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //IRQ通道被使能
	NVIC_Init(&NVIC_InitStructure);  //根据NVIC_InitStruct中指定的参数初始化外设NVIC寄存器
	
	TIM_Cmd(TIM5, DISABLE);  //TIM5
}


void TIM5_rote(int num,u16 speed)//num 脉冲数 ，speed速度
{
	//TIM_Cmd(TIM5, ENABLE);  //使能TIM5
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
	  TIM_SetAutoreload(TIM5,speed);  //自动重装载值
	  TIM_Cmd(TIM5, ENABLE);  //使能TIM5
	}
}



void TIM5_IRQHandler(void) {
	if (TIM_GetITStatus(TIM5, TIM_IT_Update) != RESET) //检查指定的TIM中断发生与否:TIM 中断源 
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
		TIM_ClearITPendingBit(TIM5, TIM_IT_Update);  //清除TIMx的中断待处理位:TIM 中断源
		}		
}



