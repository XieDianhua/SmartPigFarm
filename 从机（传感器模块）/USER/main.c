/*
*@author:dianhua xie
*/
#include "led.h"
#include "delay.h"
#include "usart.h"
#include "dht11.h"
#include "z19b.h"
#include "mq135.h"
#include "myiic.h"
#include "bh1750.h"
#include "rs485.h" 

u8 Send_Date[8] = {0};

int main(void)
{	 		 
	u8 temperature;//�¶�ֵ 	    
	u8 humidity;   //ʪ��ֵ
	u16 co2_value;	 //CO2ֵ
	u16 h2s_value;	 //H2Sֵ
	u16 sun_lx;		 //����ǿ��ֵ

	delay_init();	    	 //��ʱ������ʼ��	  
  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//�����ж����ȼ�����Ϊ��2��2λ��ռ���ȼ���2λ��Ӧ���ȼ�
	uart_init(115200);	 //����1��ʼ��Ϊ115200��������ʾ
	RS485_Init(115200);	 //485����2
	LED_Init();		  		 //��ʼ����LED���ӵ�Ӳ���ӿ� 
	co2_uart_init(9600); //��ʼ��CO2������
	Adc_Init();          //��ʼ��ADC
	IIC_Init();					 //��ʼ��IIC�ӿ�
	while(DHT11_Init()); //���DHT11�Ƿ����	
	BH_DateSend(BHPowOn);    //��ģ��ȴ�����ָ��
	BH_DateSend(BHReset);    //��λģ��
	BH_DateSend(BHModeH2);   //ѡ�����ģʽ
	while(1)
	{	    	
			/******************��ȡ������ֵ********************/
			DHT11_Read_Data(&temperature,&humidity);	//��ʪ��
			co2_value = CO2_Get_Date();//CO2
			h2s_value = Get_Average(ADC_Channel_1,10);//H2S
			sun_lx = BH_DateRead();//����
			
			Send_Date[0] = temperature;//���¶�ֵ��ֵ����������ĵ�һλ
		
			Send_Date[1] = humidity;	 //��ֵʪ��ֵ
		
			Send_Date[2] = (u8)(co2_value>>8);//���͸߰�λ0101 0101 0011 0110    0000 0000 0101 0101
			Send_Date[3] = (u8)co2_value;//���͵Ͱ�λ
		
			Send_Date[4] = (u8)(h2s_value>>8);
			Send_Date[5] = (u8)h2s_value;
			
			Send_Date[6] = (u8)(sun_lx>>8);
			Send_Date[7] = (u8)sun_lx;
		
		//������	
			printf("ʪ��=%d\r\n",humidity);
			printf("�¶�=%d\r\n",temperature);
			printf("Send_Date[4]=%d\r\n",(Send_Date[4]<<8)+Send_Date[5]);
			printf("h2s=%d\r\n",h2s_value);
			printf("����=%d\r\n",sun_lx);
			printf("CO2=%d\r\n",co2_value);
		//	printf("�����=%d\r\n",(Send_Date[6]<<8)+Send_Date[7]);
	}
			
		
}




