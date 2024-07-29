#include "z19b.h"
 
#if EN_USART_CO2_RX   //如果使能了接收
//串口3中断服务程序
//注意,读取USARTx->SR能避免莫名其妙的错误   	
u8 USART_CO2_RX_BUF[USART_CO2_REC_LEN];     //接收缓冲,最大USART_REC_LEN个字节.
//接收状态
//bit15，接收完成标志
//bit14，	接收到0x0d
//bit13~0，	接收到的有效字节数目
u16 USART_CO2_RX_STA=0;       //接收状态标记	  
u8 usart_co2_tx[9]={0xFF,0x01,0x86,0x00,0x00,0x00,0x00,0x00,0x79};
u8 usart_co2_rx[9];
u8 t=0;

void co2_uart_init(u32 bound)
{
  //GPIO端口设置
  GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);//使能GPIOA时钟
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3, ENABLE);	//使能USART3时钟
  
	//USART3_TX   GPIOB.11
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11; //PB.11
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;	//复用推挽输出
  GPIO_Init(GPIOB, &GPIO_InitStructure);//初始化GPIOB.11
   
  //USART3_RX	  GPIOB.10初始化
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;//PB.10
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;//浮空输入
  GPIO_Init(GPIOB, &GPIO_InitStructure);//初始化GPIOB.10  

  //Usart3 NVIC 配置
  NVIC_InitStructure.NVIC_IRQChannel = USART3_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=3 ;//抢占优先级3
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;		//子优先级3
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQ通道使能
	NVIC_Init(&NVIC_InitStructure);	//根据指定的参数初始化VIC寄存器
  
   //USART 初始化设置

	USART_InitStructure.USART_BaudRate = bound;//串口波特率
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;//字长为8位数据格式
	USART_InitStructure.USART_StopBits = USART_StopBits_1;//一个停止位
	USART_InitStructure.USART_Parity = USART_Parity_No;//无奇偶校验位
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//无硬件数据流控制
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//收发模式

  USART_Init(USART3, &USART_InitStructure); //初始化串口3
  USART_ITConfig(USART3, USART_IT_RXNE, ENABLE);//开启串口接受中断
  USART_Cmd(USART3, ENABLE);                    //使能串口3

}

u8 CO2_Get_Date(void)
{
	u8 i;
	u8 rec;
	for(i=0;i<9;i++)
	{
		USART_SendData(USART3,usart_co2_tx[i]);
		while(USART_GetFlagStatus(USART3,USART_FLAG_TXE)==RESET);
	}
	rec=usart_co2_rx[2]*256+usart_co2_rx[3];	
	return rec;
}
void USART3_IRQHandler(void)                	//串口2中断服务程序
{
	u8 Res;
	if(USART_GetITStatus(USART3, USART_IT_RXNE)!= RESET)  //接收中断(接收到的数据必须是0x0d 0x0a结尾)
	{
		Res=USART_ReceiveData(USART3);	//读取接收到的数据
		usart_co2_rx[t]=Res;
		t++;   		 
  } 
} 
#endif	

