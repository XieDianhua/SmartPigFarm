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

/*串口屏显示*/
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
	delay_init(); //延时函数初始化
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); //设置NVIC中断分组2:2位抢占优先级，2位响应优先级
	uart_init(115200); //初始化串口1
	usart3_init(115200); //8266串口波特率为115200
	RS485_Init(115200);//
	LED_Init();		//相关GPIO端口初始化
	TIM4_PWM_Init(7199,199);//舵机
	TIM5_init(2000,71);	
  TIM3_init(2000,71);
	
	
	while(1) {	//不断扫描
		gizwitsControlProcess();	//app调控
		uploadToServer();			  	//通过APP上传当前状态数据至云端
		
		//发送数据到串口屏，记住格式
		senddata(0,tempVlaue);//温度
		senddata(1,humiVlaue);//湿度
		senddata(2,lightVlaue);//光照
		senddata(3,nh3_Vlaue);//氨气
		senddata(4,400);//CO2
		senddata(5,nh3_Vlaue);//氨气
		if(endFlag != 0x02)
		{
			if(lightVlaue<100)
			{
				TIM_SetCompare1(TIM4,860);//遮阳开
			} 
			if(lightVlaue>=150) 
			{	
				TIM_SetCompare1(TIM4,180);//遮阳关
			}
		}		
	}
}
