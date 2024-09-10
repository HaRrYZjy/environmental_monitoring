#ifndef __PASSTHING_H_
#define  __PASSTHING_H_
#include "main.h"


#define PASSTHINGPORT	GPIOB	//定义IO接口
#define PASSTHING	GPIO_PIN_5	//定义IO接口

#define BUTTONPORT	GPIOA	//定义IO接口
#define BUTTON1	GPIO_PIN_1	//定义IO接口

#define BUTTONPORT	GPIOA	//定义IO接口
#define BUTTON2	GPIO_PIN_0	//定义IO接口

struct keys
{
		u8 judge_sta;
		u8 key_sta;
		u8 single_flag;
	
	
};

extern struct keys key[2];
extern u8 pass_flag;
extern int pass_tick;
//u8 is_PASSED(void);
//void detect_do(void);
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin);
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim);
//void PASS_DO(void);	    
#endif /*__DETECT_H_*/

