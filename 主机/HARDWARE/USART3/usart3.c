#include "usart3.h"

u16 USART3_RX_STA=0;//����3����״̬��־��ͨ�������λ�жϽ���״̬
u8 USART3_RX_BUF[USART3_REC_LEN];//���ջ��壬���USART3_REC_LEN���ֽ�,ĩ�ֽ�Ϊ���з�
u8 endFlag=0;
//USART3��ʼ��
void usart3_init(u32 bound){
	
	GPIO_InitTypeDef GPIO_InitStructure;//����GPIO�ṹ��
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3,ENABLE);// ʹ��USART3ʱ��
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE); //	ʹ��GPIO.Bʱ��
	
	//USART3_TX		GPIOB.10
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10; //PA.10
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;	//�����������
  GPIO_Init(GPIOB, &GPIO_InitStructure);//��ʼ��GPIOB.10
	
	//USART3_RX	  GPIOB.11
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;//PB11
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;//��������
  GPIO_Init(GPIOB, &GPIO_InitStructure);//��ʼ��GPIOB.11
	
	//USART ��ʼ������
	USART_InitStructure.USART_BaudRate = bound;//���ڲ�����
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;//�ֳ�Ϊ8λ���ݸ�ʽ
	USART_InitStructure.USART_StopBits = USART_StopBits_1;//һ��ֹͣλ
	USART_InitStructure.USART_Parity = USART_Parity_No;//����żУ��λ
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//��Ӳ������������
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//�շ�ģʽ
	
	//��ʼ������3
	USART_Init(USART3,&USART_InitStructure);
	
	//�������ڽ����ж�
	USART_ITConfig(USART3, USART_IT_RXNE, ENABLE);
	
	//ʹ�ܴ���3
	USART_Cmd(USART3,ENABLE);
	
	//USART3 NVIC ����
  NVIC_InitStructure.NVIC_IRQChannel = USART3_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=3 ;//��ռ���ȼ�3
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;		//�����ȼ�3
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQͨ��ʹ��
	NVIC_Init(&NVIC_InitStructure);	//����ָ���Ĳ�����ʼ��VIC�Ĵ��� 
}

//�����жϷ�����
void USART3_IRQHandler(void) {
	
	u8 res;//����Ϊʲô��u8������u16
	static u8 len=0;
	
	if(USART_GetITStatus(USART3,USART_IT_RXNE) == SET) {	//�����жϣ����������
		res = USART_ReceiveData(USART3);//��ȡ���յ�������
		
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