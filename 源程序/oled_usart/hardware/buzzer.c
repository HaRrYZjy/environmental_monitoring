#include "buzzer.h"
//PB14 p1 25

void BUZZER_Init(void){ //�������Ľӿڳ�ʼ��

	HAL_GPIO_WritePin(BUZZER_GPIO_Port,BUZZER_Pin,(GPIO_PinState)(1)); //�������ӿ�����ߵ�ƽ1	
	HAL_Delay(100);
	HAL_GPIO_WritePin(BUZZER_GPIO_Port,BUZZER_Pin,(GPIO_PinState)(0)); 	
}

void BUZZER_BEEP1(void){ //����������
		HAL_GPIO_WritePin(BUZZER_GPIO_Port,BUZZER_Pin,(GPIO_PinState)(1));  //�������ӿ�����ߵ�ƽ1
}
void BUZZER_OFF(void){//�رշ�����
HAL_GPIO_WritePin(BUZZER_GPIO_Port,BUZZER_Pin,(GPIO_PinState)(0));  //�������ӿ�����͵�ƽ0	
}
 

