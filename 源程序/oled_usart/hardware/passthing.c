#include "passthing.h"
#include "oled.h"
#include "buzzer.h"
#include "environment.h"

//PB5 p1 7

struct keys key[2]={0,0,0};

u8 pass_flag;
int pass_tick;
int button_tick;
char text_pass[21];
/*u8 is_PASSED(void){ //
	if(HAL_GPIO_ReadPin(PASSTHINGPORT,PASSTHING)==SET) return 0;
	else 										return 1;
		
		
}
*/
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
	if(GPIO_Pin==PASSTHING){//光电槽位开关使用中断来触发，如果触发则将物体通过标识位pass_flag为1，在主函数中进行相应操作。
		switch(page){
			
			case 0:{
				pass_tick=5;
				pass_flag=1;
			
				if(buzzer_flag) buzzer_sin=1;
				else buzzer_sin=0;
				
				sprintf(text_pass," something passed %d ",pass_tick);
				 OLED_ShowStr(0,line6_1,(u8 *)text_pass,1);
				OLED_AreaToggle(0,line6_1,20*6,8);
			}
			break;
			case 1:{
				pass_flag=1;
				if(buzzer_flag) buzzer_sin=1;
				else buzzer_sin=0;			
			}
			break;
			default:
			break;

		}

	}
	
	

}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim){
	
	if(htim->Instance==TIM2)
	{
		key[0].key_sta=HAL_GPIO_ReadPin(key1_GPIO_Port,key1_Pin);
		key[1].key_sta=HAL_GPIO_ReadPin(key2_GPIO_Port,key2_Pin);
		
		for(int i=0;i<2;i++){//按钮消抖
		
			switch (key[i].judge_sta)
			{
				case 0:
				{
					if(key[i].key_sta==0) key[i].judge_sta=1;
				}
				break;
				
				case 1:
				{
					if(key[i].key_sta==0) {
						key[i].judge_sta=2;
						key[i].single_flag=1;
						
					}
				}
				break;	
				case 2:
				{
					if(key[i].key_sta==1) {
						key[i].judge_sta=0;
						
						
					}
				}
				break;	
				
			}
		
		
		}
		//OLED_RefreshRAM();
	}
	
	

}


