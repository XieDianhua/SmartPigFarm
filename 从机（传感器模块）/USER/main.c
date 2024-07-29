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
	u8 temperature;//温度值 	    
	u8 humidity;   //湿度值
	u16 co2_value;	 //CO2值
	u16 h2s_value;	 //H2S值
	u16 sun_lx;		 //光照强度值

	delay_init();	    	 //延时函数初始化	  
  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//设置中断优先级分组为组2：2位抢占优先级，2位响应优先级
	uart_init(115200);	 //串口1初始化为115200，用来显示
	RS485_Init(115200);	 //485串口2
	LED_Init();		  		 //初始化与LED连接的硬件接口 
	co2_uart_init(9600); //初始化CO2传感器
	Adc_Init();          //初始化ADC
	IIC_Init();					 //初始化IIC接口
	while(DHT11_Init()); //检测DHT11是否存在	
	BH_DateSend(BHPowOn);    //打开模块等待测量指令
	BH_DateSend(BHReset);    //复位模块
	BH_DateSend(BHModeH2);   //选择测量模式
	while(1)
	{	    	
			/******************获取传感器值********************/
			DHT11_Read_Data(&temperature,&humidity);	//温湿度
			co2_value = CO2_Get_Date();//CO2
			h2s_value = Get_Average(ADC_Channel_1,10);//H2S
			sun_lx = BH_DateRead();//光照
			
			Send_Date[0] = temperature;//把温度值赋值给发送数组的第一位
		
			Send_Date[1] = humidity;	 //赋值湿度值
		
			Send_Date[2] = (u8)(co2_value>>8);//发送高八位0101 0101 0011 0110    0000 0000 0101 0101
			Send_Date[3] = (u8)co2_value;//发送低八位
		
			Send_Date[4] = (u8)(h2s_value>>8);
			Send_Date[5] = (u8)h2s_value;
			
			Send_Date[6] = (u8)(sun_lx>>8);
			Send_Date[7] = (u8)sun_lx;
		
		//调试区	
			printf("湿度=%d\r\n",humidity);
			printf("温度=%d\r\n",temperature);
			printf("Send_Date[4]=%d\r\n",(Send_Date[4]<<8)+Send_Date[5]);
			printf("h2s=%d\r\n",h2s_value);
			printf("光照=%d\r\n",sun_lx);
			printf("CO2=%d\r\n",co2_value);
		//	printf("后光照=%d\r\n",(Send_Date[6]<<8)+Send_Date[7]);
	}
			
		
}




