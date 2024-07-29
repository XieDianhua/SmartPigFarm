#include "bh1750.h"
#include "delay.h"

void BH_DateSend(u8 command)
{
    do{
    IIC_Start();                      //��ʼ�ź�
    IIC_Send_Byte(BHAddWrite);       //����д�����������ĵ�ַ
    }while(IIC_Wait_Ack());           //�ȴ�Ӧ��
    IIC_Send_Byte(command);          //��������
    IIC_Wait_Ack();                   //�ȴ�Ӧ��
    IIC_Stop();                       //��ֹ�ź�
} 

u8 BH_DateRead(void)
{
	u8 buf;
	IIC_Start();                      //��ʼ�ź�
	IIC_Send_Byte(BHAddRead);         //���Ͷ�ȡ���������ĵ�ַ
	IIC_Wait_Ack();                   //�ȴ�Ӧ��
	buf=IIC_Read_Byte(1);             //��ȡ����
	buf=buf<<8;                       //��ȡ������߰�λ����
	buf+=0x00ff&IIC_Read_Byte(0);     //��ȡ������ڰ�λ����
	IIC_Stop();                       //��ֹ�ź�
	return buf; 
}

//u16 BH_Measure()
//{
//	u16 buffer;
//	BH_DateSend(BHPowOn);    //��ģ��ȴ�����ָ��
//	BH_DateSend(BHReset);    //��λģ��
//	BH_DateSend(BHModeH2);   //ѡ�����ģʽ
//	delay_ms(180);
//	buffer=BH_DateRead()/1.2;//��ȡ�����ݳ���1.2�͵õ���λlx�Ĺ�ǿ�ȼ��ֵ
//	return buffer;
//}