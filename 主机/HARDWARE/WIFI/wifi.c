#include "wifi.h"
#include "usart3.h"
#include "rs485.h"
#include "delay.h"
#include "usart.h"
#include "time4.h"
#include "tim3.h"
#include "tim5.h"

dataPoint* getDataStructure=0;			//��Ŵ�8266�õ����������  �����ʼ��
dataPoint  currentDataStructure;	//���ϵͳ��ǰ״̬����
lastDataPoint lastDataStructure={0,0,0,0,0};	//���ϵͳ��һ��״̬���ݣ�Ĭ��Ϊ0���ر�
u8* uploadToServerPonit=(u8*)&currentDataStructure;	//�����ϴ�����

//���ز��ִ���
void gizwitsControlProcess(void) {
	
	if(endFlag==0x02) { // esp8266�������
		getDataStructure=(dataPoint*)USART3_RX_BUF;//������������ת�����Ѷ���ṹ���ʽ����
		
		//����
		if(getDataStructure->valuefan != lastDataStructure.valuefan) {
			if(getDataStructure->valuefan == 0x01) {
				GPIO_SetBits(GPIOG,GPIO_Pin_13);	
			}
			else {
				GPIO_ResetBits(GPIOG,GPIO_Pin_13);				
			}
			currentDataStructure.valuefan=getDataStructure->valuefan;//�õ�ϵͳ��ǰ״̬����
			lastDataStructure.valuefan=getDataStructure->valuefan;	 //��ǰ���ݱ���´βο�����
		}
		
		//��ˮ
		if(getDataStructure->valuespray != lastDataStructure.valuespray) {
			if(getDataStructure->valuespray == 0x01) {
				GPIO_SetBits(GPIOG,GPIO_Pin_14);	
			}
			else {
				GPIO_ResetBits(GPIOG,GPIO_Pin_14);			
			}
			currentDataStructure.valuespray=getDataStructure->valuespray;
			lastDataStructure.valuespray=getDataStructure->valuespray;
		}
		
		//����
		if(getDataStructure->valuesun_louver != lastDataStructure.valuesun_louver) {
			if(getDataStructure->valuesun_louver == 0x01) {
				TIM_SetCompare1(TIM4,860);//��
			}
			else {
				TIM_SetCompare1(TIM4,180);//��
			}
			currentDataStructure.valuesun_louver=getDataStructure->valuesun_louver;
			lastDataStructure.valuesun_louver=getDataStructure->valuesun_louver;
		}
		
		//ͨ��
		if(getDataStructure->valueexhaust_air != lastDataStructure.valueexhaust_air) {
			if(getDataStructure->valueexhaust_air == 0x01) {
				GPIO_SetBits(GPIOG,GPIO_Pin_15);
			}
			else {
				GPIO_ResetBits(GPIOG,GPIO_Pin_15);
			}
			currentDataStructure.valueexhaust_air=getDataStructure->valueexhaust_air;
		  lastDataStructure.valueexhaust_air=getDataStructure->valueexhaust_air;
		}
		
		//�η�
		if(getDataStructure->valueclean != lastDataStructure.valueclean) {
			if(getDataStructure->valueclean == 0x01) {
				TIM3_rote(-5000,1000);TIM5_rote(5000,1000);
			}
			if(getDataStructure->valueclean == 0x00) {
				TIM3_rote(5000,1000);TIM5_rote(-5000,1000);
			}
			currentDataStructure.valueclean=getDataStructure->valueclean;
		  lastDataStructure.valueclean=getDataStructure->valueclean;
		}
		endFlag=0;
	}
}

//��ȡ����������
void getSensorData(void) {
	RS485_TX_EN=1;	//����Ϊ����ģʽ
	delay_ms(10);
	USART2->DR=0x01;//�����շ�Э�飬�ȷ���0x01
	while((USART2->SR&0X40)==0);//�ȴ��������
	
	RS485_TX_EN=0;	//����Ϊ����ģʽ
	if(convertFlag) {
		dataConver();
		convertFlag=0;	
	}
}

//�õ�����������ֵ
void dataConver(void) {
	tempVlaue=sensorData[0];
	humiVlaue=sensorData[1];
	co2_Vlaue=(sensorData[2]<<8)+sensorData[3];
	nh3_Vlaue=(sensorData[4]<<8)+sensorData[5];
	lightVlaue=(sensorData[6]<<8)+sensorData[7];
}

//��ϵͳ��ǰ״̬�ϴ����ƶ�
void uploadToServer(void) {
	
	u8 len;
	getSensorData();//��ȡ����������
	currentDataStructure.valuetemp=tempVlaue;
	currentDataStructure.valuehumidity=humiVlaue;
	currentDataStructure.valueco2_ppm=400;
	currentDataStructure.valuenh3_ppm=nh3_Vlaue;
	currentDataStructure.valuelight=lightVlaue;
	
	for(len=0;len<sizeof(dataPoint);len++) {
		USART_SendData(USART3,uploadToServerPonit[len]);//������
		while(USART_GetFlagStatus(USART3,USART_FLAG_TC)!=SET);
	}
}

