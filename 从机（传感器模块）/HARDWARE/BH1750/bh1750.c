#include "bh1750.h"
#include "delay.h"

void BH_DateSend(u8 command)
{
    do{
    IIC_Start();                      //起始信号
    IIC_Send_Byte(BHAddWrite);       //发送写入数据器件的地址
    }while(IIC_Wait_Ack());           //等待应答
    IIC_Send_Byte(command);          //发送命令
    IIC_Wait_Ack();                   //等待应答
    IIC_Stop();                       //终止信号
} 

u8 BH_DateRead(void)
{
	u8 buf;
	IIC_Start();                      //开始信号
	IIC_Send_Byte(BHAddRead);         //发送读取数据器件的地址
	IIC_Wait_Ack();                   //等待应答
	buf=IIC_Read_Byte(1);             //读取数据
	buf=buf<<8;                       //读取并保存高八位数据
	buf+=0x00ff&IIC_Read_Byte(0);     //读取并保存第八位数据
	IIC_Stop();                       //终止信号
	return buf; 
}

//u16 BH_Measure()
//{
//	u16 buffer;
//	BH_DateSend(BHPowOn);    //打开模块等待测量指令
//	BH_DateSend(BHReset);    //复位模块
//	BH_DateSend(BHModeH2);   //选择测量模式
//	delay_ms(180);
//	buffer=BH_DateRead()/1.2;//读取的数据除以1.2就得到单位lx的光强度检测值
//	return buffer;
//}