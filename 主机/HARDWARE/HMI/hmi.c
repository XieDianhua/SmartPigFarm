#include "hmi.h"
#include "usart.h"
#include "rs485.h"
#include "tim3.h"
#include "tim5.h"
#include "led.h"

////�������������ش���
//void hmiControlProcess(void) {
//	u8 sunShadeCtrl=0;
//	u8 i=0;
//	 
//	if((recBuffer[5]==0xff)&&(recBuffer[6]==0xff)&&(recBuffer[7]==0xff)) {	//ȷ��������ɣ��������������ݽ�����Ϊ��0xff,0xff,0xff"
//		
//		if(recBuffer[0]==0x71) {
//			switch (recBuffer[1]) {
//				case 0:TIM3_rote(5000,1000);TIM5_rote(5000,1000);//�η��		���
//					break;
//				case 1:TIM3_rote(-5000,1000);TIM5_rote(-5000,1000);//�η��		�ұ�
//					break;
//				case 2:sunShadeCtrl=!sunShadeCtrl;//����
//					if(sunShadeCtrl==1)
//						TIM_SetCompare1(TIM4,860);
//					else
//						TIM_SetCompare1(TIM4,180);
//					break;
//				case 3:waterPump=!waterPump;//��ˮ
//					break;
//				case 4://����
//					break;
//				case 5:exhaust=!exhaust;//����
//					break;
//				case 6:aeration=!aeration;//ͨ�罵��
//					break;
//			}
//			for(i=0;i<8;i++) {
//				recBuffer[i]=0;
//			}
//		}
//	}
//}

//���������ϱ���������
void uploadToHmi(void) {
	printf("n0.val=%d",tempVlaue);
	endBit();
	printf("n1.val=%d",humiVlaue);
	endBit();
	printf("n2.val=%d",co2_Vlaue);
	endBit();
	printf("n3.val=%d",nh3_Vlaue);
	endBit();
	printf("n4.val=%d",lightVlaue);
	endBit();
}

//�������ݽ���λ
void endBit(void) {
	u8 i=0;
	for(i=0;i<3;i++) {
		USART_SendData(USART1,0xff);
		while(!USART_GetFlagStatus(USART1,USART_IT_TXE));
	}
}