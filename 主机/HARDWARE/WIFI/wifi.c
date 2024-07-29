#include "wifi.h"
#include "usart3.h"
#include "rs485.h"
#include "delay.h"
#include "usart.h"
#include "time4.h"
#include "tim3.h"
#include "tim5.h"

dataPoint* getDataStructure=0;			//存放从8266得到的命令及数据  必须初始化
dataPoint  currentDataStructure;	//存放系统当前状态数据
lastDataPoint lastDataStructure={0,0,0,0,0};	//存放系统上一次状态数据，默认为0，关闭
u8* uploadToServerPonit=(u8*)&currentDataStructure;	//用于上传数据

//调控部分处理
void gizwitsControlProcess(void) {
	
	if(endFlag==0x02) { // esp8266接收完成
		getDataStructure=(dataPoint*)USART3_RX_BUF;//将缓冲区数据转换成已定义结构体格式数据
		
		//排气
		if(getDataStructure->valuefan != lastDataStructure.valuefan) {
			if(getDataStructure->valuefan == 0x01) {
				GPIO_SetBits(GPIOG,GPIO_Pin_13);	
			}
			else {
				GPIO_ResetBits(GPIOG,GPIO_Pin_13);				
			}
			currentDataStructure.valuefan=getDataStructure->valuefan;//得到系统当前状态数据
			lastDataStructure.valuefan=getDataStructure->valuefan;	 //当前数据变成下次参考数据
		}
		
		//洒水
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
		
		//遮阳
		if(getDataStructure->valuesun_louver != lastDataStructure.valuesun_louver) {
			if(getDataStructure->valuesun_louver == 0x01) {
				TIM_SetCompare1(TIM4,860);//开
			}
			else {
				TIM_SetCompare1(TIM4,180);//关
			}
			currentDataStructure.valuesun_louver=getDataStructure->valuesun_louver;
			lastDataStructure.valuesun_louver=getDataStructure->valuesun_louver;
		}
		
		//通风
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
		
		//刮粪
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

//获取传感器数据
void getSensorData(void) {
	RS485_TX_EN=1;	//设置为发送模式
	delay_ms(10);
	USART2->DR=0x01;//主从收发协议，先发送0x01
	while((USART2->SR&0X40)==0);//等待发送完成
	
	RS485_TX_EN=0;	//设置为接收模式
	if(convertFlag) {
		dataConver();
		convertFlag=0;	
	}
}

//得到各环境参数值
void dataConver(void) {
	tempVlaue=sensorData[0];
	humiVlaue=sensorData[1];
	co2_Vlaue=(sensorData[2]<<8)+sensorData[3];
	nh3_Vlaue=(sensorData[4]<<8)+sensorData[5];
	lightVlaue=(sensorData[6]<<8)+sensorData[7];
}

//将系统当前状态上传到云端
void uploadToServer(void) {
	
	u8 len;
	getSensorData();//获取传感器数据
	currentDataStructure.valuetemp=tempVlaue;
	currentDataStructure.valuehumidity=humiVlaue;
	currentDataStructure.valueco2_ppm=400;
	currentDataStructure.valuenh3_ppm=nh3_Vlaue;
	currentDataStructure.valuelight=lightVlaue;
	
	for(len=0;len<sizeof(dataPoint);len++) {
		USART_SendData(USART3,uploadToServerPonit[len]);//有疑问
		while(USART_GetFlagStatus(USART3,USART_FLAG_TC)!=SET);
	}
}

