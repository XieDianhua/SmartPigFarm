#include "usart3.h"
#include "delay.h"
#include "wifi.h"
#include "led.h"
#include "usart.h"
#include "rs485.h"
#include "time4.h"
#include "tim3.h"
#include "tim5.h"
#include "hmi.h"

/*��������ʾ*/
void senddata(u8 nam,u16 data)
{
	u16 a;
	switch(nam)
	{
		case 0:printf("n0.val=%d",data);break;
		case 1:printf("n1.val=%d",data);break;
		case 2:printf("n2.val=%d",data);break;
		case 3:printf("n3.val=%d",data);break;
		case 4:printf("n4.val=%d",data);break;
	}
	
	while(!USART_GetFlagStatus(USART1,USART_FLAG_TC)); 
	for(a=0;a<3;a++) 
	 {
	  USART_SendData(USART1,0xff);
    while(!USART_GetFlagStatus(USART1,USART_FLAG_TC)); 
	 }
 } 

int main(void) {
	delay_init(); //��ʱ������ʼ��
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); //����NVIC�жϷ���2:2λ��ռ���ȼ���2λ��Ӧ���ȼ�
	uart_init(115200); //��ʼ������1
	usart3_init(115200); //8266���ڲ�����Ϊ115200
	RS485_Init(115200);//
	LED_Init();		//���GPIO�˿ڳ�ʼ��
	TIM4_PWM_Init(7199,199);//���
	TIM5_init(2000,71);	
  TIM3_init(2000,71);
	
	
	while(1) {	//����ɨ��
		gizwitsControlProcess();	//app����
		uploadToServer();			  	//ͨ��APP�ϴ���ǰ״̬�������ƶ�
		
		//�������ݵ�����������ס��ʽ
		senddata(0,tempVlaue);//�¶�
		senddata(1,humiVlaue);//ʪ��
		senddata(2,lightVlaue);//����
		senddata(3,nh3_Vlaue);//����
		senddata(4,400);//CO2
		senddata(5,nh3_Vlaue);//����
		if(endFlag != 0x02)
		{
			if(lightVlaue<100)
			{
				TIM_SetCompare1(TIM4,860);//������
			} 
			if(lightVlaue>=150) 
			{	
				TIM_SetCompare1(TIM4,180);//������
			}
		}		
	}
}
