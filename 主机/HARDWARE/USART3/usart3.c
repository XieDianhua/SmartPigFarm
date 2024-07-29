#include "usart3.h"

u16 USART3_RX_STA=0;//串口3接收状态标志，通过最后两位判断接收状态
u8 USART3_RX_BUF[USART3_REC_LEN];//接收缓冲，最大USART3_REC_LEN个字节,末字节为换行符
u8 endFlag=0;
//USART3初始化
void usart3_init(u32 bound){
	
	GPIO_InitTypeDef GPIO_InitStructure;//定义GPIO结构体
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3,ENABLE);// 使能USART3时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE); //	使能GPIO.B时钟
	
	//USART3_TX		GPIOB.10
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10; //PA.10
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;	//复用推挽输出
  GPIO_Init(GPIOB, &GPIO_InitStructure);//初始化GPIOB.10
	
	//USART3_RX	  GPIOB.11
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;//PB11
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;//浮空输入
  GPIO_Init(GPIOB, &GPIO_InitStructure);//初始化GPIOB.11
	
	//USART 初始化设置
	USART_InitStructure.USART_BaudRate = bound;//串口波特率
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;//字长为8位数据格式
	USART_InitStructure.USART_StopBits = USART_StopBits_1;//一个停止位
	USART_InitStructure.USART_Parity = USART_Parity_No;//无奇偶校验位
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//无硬件数据流控制
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//收发模式
	
	//初始化串口3
	USART_Init(USART3,&USART_InitStructure);
	
	//开启串口接收中断
	USART_ITConfig(USART3, USART_IT_RXNE, ENABLE);
	
	//使能串口3
	USART_Cmd(USART3,ENABLE);
	
	//USART3 NVIC 配置
  NVIC_InitStructure.NVIC_IRQChannel = USART3_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=3 ;//抢占优先级3
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;		//子优先级3
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQ通道使能
	NVIC_Init(&NVIC_InitStructure);	//根据指定的参数初始化VIC寄存器 
}

//接收中断服务函数
void USART3_IRQHandler(void) {
	
	u8 res;//这里为什么是u8而不是u16
	static u8 len=0;
	
	if(USART_GetITStatus(USART3,USART_IT_RXNE) == SET) {	//接收中断，如果接收了
		res = USART_ReceiveData(USART3);//读取接收到的数据
		
		if(res==0x0d&&endFlag==0) {
			endFlag=0x01;
			return;
		}
		if(res == 0x0a&&endFlag==1) {
			endFlag=0x02;
			len=0;
		}
		else {
			USART3_RX_BUF[len++]=res;
		}
		
	}	
}