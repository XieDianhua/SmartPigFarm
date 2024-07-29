#include "mq135.h"
#include "delay.h"

void Adc_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStruct;
	ADC_InitTypeDef ADC_InitStruct;
	
	//使能PA口和ADC1时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_ADC1,ENABLE);
	
	//GPIO配置
	GPIO_InitStruct.GPIO_Mode=GPIO_Mode_AIN;
	GPIO_InitStruct.GPIO_Pin=GPIO_Pin_1;
	GPIO_Init(GPIOA,&GPIO_InitStruct);//初始化GPIO
	
	
	RCC_ADCCLKConfig(RCC_PCLK2_Div6);//预分频
	ADC_DeInit(ADC1);//复位ADC
	
	ADC_InitStruct.ADC_ContinuousConvMode=DISABLE;//是否开启连续转换
	ADC_InitStruct.ADC_DataAlign=ADC_DataAlign_Right;//对齐方式
	ADC_InitStruct.ADC_ExternalTrigConv=ADC_ExternalTrigConv_None;//软件触发
	ADC_InitStruct.ADC_Mode=ADC_Mode_Independent;//独立模式
	ADC_InitStruct.ADC_NbrOfChannel=1;
	ADC_InitStruct.ADC_ScanConvMode=DISABLE;//是否开启扫描中断
	
	ADC_Init(ADC1,&ADC_InitStruct);//初始化ADC
	
	ADC_Cmd(ADC1,ENABLE);//使能ADC
	
	ADC_ResetCalibration(ADC1); 
	
	while(ADC_GetResetCalibrationStatus(ADC1));
	
	ADC_StartCalibration(ADC1); 
	
	while(ADC_GetCalibrationStatus(ADC1));
}

u16 Get_Adc(u8 ch)
{
	ADC_RegularChannelConfig(ADC1,ch,1,ADC_SampleTime_239Cycles5);
	ADC_SoftwareStartConvCmd(ADC1,ENABLE);
	while(ADC_GetFlagStatus(ADC1,ADC_FLAG_EOC)==RESET);//转换完成
	return ADC_GetConversionValue(ADC1);
}

u16 Get_Average(u8 ch,u8 time)
{
	u8 i;
	u16 adc_value=0;
	for(i=0;i<time;i++)
	{
		adc_value+=Get_Adc(ch);
		delay_ms(5);
	}
	adc_value/=time;
	return adc_value;
}










