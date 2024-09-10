#include "buzzer.h"
//PB14 p1 25

void BUZZER_Init(void){ //蜂鸣器的接口初始化

	HAL_GPIO_WritePin(BUZZER_GPIO_Port,BUZZER_Pin,(GPIO_PinState)(1)); //蜂鸣器接口输出高电平1	
	HAL_Delay(100);
	HAL_GPIO_WritePin(BUZZER_GPIO_Port,BUZZER_Pin,(GPIO_PinState)(0)); 	
}

void BUZZER_BEEP1(void){ //蜂鸣器发声
		HAL_GPIO_WritePin(BUZZER_GPIO_Port,BUZZER_Pin,(GPIO_PinState)(1));  //蜂鸣器接口输出高电平1
}
void BUZZER_OFF(void){//关闭蜂鸣器
HAL_GPIO_WritePin(BUZZER_GPIO_Port,BUZZER_Pin,(GPIO_PinState)(0));  //蜂鸣器接口输出低电平0	
}
 

