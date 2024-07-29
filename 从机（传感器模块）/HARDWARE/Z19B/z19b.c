#include "z19b.h"
 
#if EN_USART_CO2_RX   //���ʹ���˽���
//����3�жϷ������
//ע��,��ȡUSARTx->SR�ܱ���Ī������Ĵ���   	
u8 USART_CO2_RX_BUF[USART_CO2_REC_LEN];     //���ջ���,���USART_REC_LEN���ֽ�.
//����״̬
//bit15��������ɱ�־
//bit14��	���յ�0x0d
//bit13~0��	���յ�����Ч�ֽ���Ŀ
u16 USART_CO2_RX_STA=0;       //����״̬���	  
u8 usart_co2_tx[9]={0xFF,0x01,0x86,0x00,0x00,0x00,0x00,0x00,0x79};
u8 usart_co2_rx[9];
u8 t=0;

void co2_uart_init(u32 bound)
{
  //GPIO�˿�����
  GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);//ʹ��GPIOAʱ��
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3, ENABLE);	//ʹ��USART3ʱ��
  
	//USART3_TX   GPIOB.11
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11; //PB.11
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;	//�����������
  GPIO_Init(GPIOB, &GPIO_InitStructure);//��ʼ��GPIOB.11
   
  //USART3_RX	  GPIOB.10��ʼ��
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;//PB.10
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;//��������
  GPIO_Init(GPIOB, &GPIO_InitStructure);//��ʼ��GPIOB.10  

  //Usart3 NVIC ����
  NVIC_InitStructure.NVIC_IRQChannel = USART3_IRQn;
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

  USART_Init(USART3, &USART_InitStructure); //��ʼ������3
  USART_ITConfig(USART3, USART_IT_RXNE, ENABLE);//�������ڽ����ж�
  USART_Cmd(USART3, ENABLE);                    //ʹ�ܴ���3

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
void USART3_IRQHandler(void)                	//����2�жϷ������
{
	u8 Res;
	if(USART_GetITStatus(USART3, USART_IT_RXNE)!= RESET)  //�����ж�(���յ������ݱ�����0x0d 0x0a��β)
	{
		Res=USART_ReceiveData(USART3);	//��ȡ���յ�������
		usart_co2_rx[t]=Res;
		t++;   		 
  } 
} 
#endif	

