#include "sys.h"
#include "usart.h"	 
#include "time.h"
#include "tim5.h"
#include "tim3.h"

#define KEY1 PGout(13) 
#define KEY2 PGout(14)
#define KEY3 PGout(15)

u8 KEY4=0;
//////////////////////////////////////////////////////////////////
//�������´���,֧��printf����,������Ҫѡ��use MicroLIB	  
#if 1
#pragma import(__use_no_semihosting)             
//��׼����Ҫ��֧�ֺ���                 
struct __FILE 
{ 
	int handle; 

}; 

FILE __stdout;       
//����_sys_exit()�Ա���ʹ�ð�����ģʽ    
_sys_exit(int x) 
{ 
	x = x; 
} 
//�ض���fputc���� 
int fputc(int ch, FILE *f)
{      
	while((USART1->SR&0X40)==0);//ѭ������,ֱ���������   
    USART1->DR = (u8) ch;      
	return ch;
}
#endif 


void uart_init(u32 bound){
  //GPIO�˿�����
  GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	 
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1|RCC_APB2Periph_GPIOA, ENABLE);	//ʹ��USART1��GPIOAʱ��
  
	//USART1_TX   GPIOA.9
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9; //PA.9
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;	//�����������
  GPIO_Init(GPIOA, &GPIO_InitStructure);//��ʼ��GPIOA.9
   
  //USART1_RX	  GPIOA.10��ʼ��
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;//PA10
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;//��������
  GPIO_Init(GPIOA, &GPIO_InitStructure);//��ʼ��GPIOA.10  

  //Usart1 NVIC ����
  NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=3 ;//��ռ���ȼ�3
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;		//�����ȼ�3
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQͨ��ʹ��
	NVIC_Init(&NVIC_InitStructure);	//����ָ���Ĳ�����ʼ��VIC�Ĵ���
  
   //USART ��ʼ������

	USART_InitStructure.USART_BaudRate = bound;//���ڲ�����
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;//�ֳ�Ϊ8λ���ݸ�ʽ
	USART_InitStructure.USART_StopBits = USART_StopBits_1;//һ��ֹͣλ
	USART_InitStructure.USART_Parity = USART_Parity_No;//����żУ��λ
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//��Ӳ������������
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//�շ�ģʽ

  USART_Init(USART1, &USART_InitStructure); //��ʼ������1
  USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);//�������ڽ����ж�
  USART_Cmd(USART1, ENABLE);                    //ʹ�ܴ���1 

}

u8 buff[8];
u8 flag=0;
void USART1_IRQHandler(void)                	//����1�жϷ������
{
	u8 Res;
	static u8 i=0,j=0;
	if(USART_GetITStatus(USART1, USART_IT_RXNE) != RESET)  //�����ж�
	{
			 Res =USART_ReceiveData(USART1);	//��ȡ���յ�������				 
   } 
   
		buff[i]=Res;
		i++;
		if(Res==0xff&&j==0)
		{
			j=1;return;
		}
		if(Res==0xff&&j==1)
		{
			j=2;return;
		}
		if(Res==0xff&&j==2)
		{
			j=0;i=0;flag=!flag;
			if(buff[0]==0x71)
			{
			 switch(buff[1])
			 {
				 case 0x00:TIM3_rote(-5000,1000);TIM5_rote(5000,1000);break;//�η����
				 case 0x01:TIM3_rote(5000,1000); TIM5_rote(-5000,1000);break;//�η��ұ�
				 case 0x02:KEY4=!KEY4;
					         if(KEY4==0)	
										 TIM_SetCompare1(TIM4,860); // 		MG996R��� PC7 //������
									 else 
										 TIM_SetCompare1(TIM4,180); // 		MG996R��� PC7 //������
									 break;
				 case 0x03:KEY2=!KEY2;break;//��ˮ
				 case 0x05:KEY3=!KEY3;break;//����
				 case 0x06:KEY1=!KEY1;break;//����
									 
			 }			 
		 }
		
		}
} 	

