#include "environment.h"
#include "passthing.h"
#include "oled.h"
#include "DHT11.h"
#include "BUZZER.h"
#include "usart.h"
#include "adc.h"

//PB6 p1 8 SCL
//PB7 p1 9 SDA
//PB5 p1 7 PASS
 //PB1 p1 3 LIGHT
 //PB13 p1 24 DHT
 //PB14 p1 25 BUZZER
 
char text_env[21];//oled字符缓存
uint8_t temperature = 1;  //温度
uint8_t humidity = 1;     //湿度
u8 page=0;//页面
u8 line=1;//选中目标
u8 line_p=threshold_add;//选择调节阈值的目标
u8 buzzer_flag=1;//蜂鸣器全局开关
u8 buzzer_sin=0;//蜂鸣器开关
int buzzer_tick=0;//蜂鸣器滴答

u8 temperature_t=30,humidity_t=90;///////温湿度阈值
float Light_t=2000;///////光敏阈值

void PASS_DO1(void){//显示物体通过情况并显示在oled上
	switch (page)
	{
////////////////////////初始界面		
	case main_page:{
		
		if(pass_flag&&pass_tick>0){
		
		  //OLED_RefreshRAM();
		  
		  sprintf(text_env," something passed %d ",pass_tick);
		 OLED_ShowStr(0,line6_1,(u8 *)text_env,1);
		OLED_AreaToggle(0,line6_1,20*6,8);
		  //printf("something passed %d\r\n",pass_tick);
		  pass_tick--;

	}
	  else{
		  pass_tick=5;
		  pass_flag=0;
		  sprintf(text_env,"   nothing passed   ");
		  OLED_ShowStr(0,line6_1,(u8 *)text_env,1);
		  //OLED_RefreshRAM();
		  //printf("nothing passed\r\n");
	 	}
	}

		break;
////////////////////////设置界面	
	case setting_page://后续可加功能
	{
		if(pass_flag){


			pass_flag=0;
		}
	}
		break;

	case setting_page_threshold:{//后续可加功能

	}	
		break;

	default:
		break;
	}
	


}

void DHT_init(void){//温湿度传感器初始化
	while(DHT11_Read_Data(&temperature,&humidity)){
			//printf("you loser!\r\n");
			sprintf(text_env,"Connect DHT...     ");
			OLED_ShowStr(0,line1_1,(u8 *)text_env,1);
			OLED_RefreshRAM();
			HAL_Delay(500);
			
		}
		OLED_ClearRAM();
		//printf("you win!\r\n");
		sprintf(text_env,"Connect successful! ");
		OLED_ShowStr(0,line1_1,(u8 *)text_env,1);
		OLED_RefreshRAM();



}

void DHT_do1(void){//测量温湿度并将数据显示在oled上

	switch (page)
	{
//////////////////////////////////初始界面	
	case main_page:{
		
		if(!DHT11_Read_Data(&temperature,&humidity)){
			
		  sprintf(text_env,"H: %d %% T: %d 'C",humidity,temperature);
		  OLED_ShowStr(0,line2_1,(u8 *)text_env,1);

			
		  //printf("humidityis:%d %% temperature is %d��\r\n",humidity,temperature);
			
			if(humidity>humidity_t||temperature>temperature_t){//判断温湿度是否大于阈值
                
					if(buzzer_flag) buzzer_sin=1;//蜂鸣器开关标志打开，在执行BUZZER_do();时会使蜂鸣器报警
					else buzzer_sin=0;
                
					if(humidity>humidity_t&&temperature>temperature_t){
						
							sprintf(text_env,"HIGH H   HIGH T     ");//温湿度都大于阈值，显示HIGH H   HIGH T
							OLED_ShowStr(0,line4_1,(u8 *)text_env,1);	
					
					}
					else if(humidity>humidity_t)
					{
							sprintf(text_env,"HIGH H              ");//湿度大于阈值显示HIGH H 
							OLED_ShowStr(0,line4_1,(u8 *)text_env,1);
					
					
					}
					else if(temperature>temperature_t)
					{
							sprintf(text_env,"HIGH T              ");//温度大于阈值显示HIGH T
							OLED_ShowStr(0,line4_1,(u8 *)text_env,1);												
					
					}
			}
			
			else{
				
			  sprintf(text_env,"                    ");
			  OLED_ShowStr(0,line4_1,(u8 *)text_env,1);		
				
			}
		  //HAL_Delay(50);
		  }
	  
          else{//如果没有检测到数据，进行错误显示
			
		  sprintf(text_env,"H:-- %% T:-- 'C  ");
		  OLED_ShowStr(0,line2_1,(u8 *)text_env,1);
			//OLED_RefreshRAM();
			HAL_Delay(500);
		}
	}
		break;
//////////////////////////////////设置界面
	case setting_page:{

	}
	break;

	case setting_page_threshold:{

	}	
		break;
		
	default:
		break;
	}

 

}


void Light_do1(void){//光照强度的显示

switch (page)
	{
//////////////////////////////////初始界面
	case main_page:{
			int i;
			//Get_ADC_Sample();
			for(i=0;i<ADC_LENGTH;i++){
				adc_vol+=adcbuff[i];
			}
			adc_vol=adc_vol/3.000*3300/4096;//读取adc数值
			sprintf(text_env,"L:%.3f mv",adc_vol);
		  OLED_ShowStr(0,line3_1,(u8 *)text_env,1);
		  //OLED_RefreshRAM();
		  //printf("light intensity:%.3f mv\r\n",adc_vol);
            if(adc_vol>Light_t){//数值>2000mv打开蜂鸣器报警，并在oled上显示Too Dark!
		
			if(buzzer_flag) buzzer_sin=1;
			sprintf(text_env,"Too Dark!           ");
			OLED_ShowStr(0,line5_1,(u8 *)text_env,1);
		}
		
		else {
			
			sprintf(text_env,"                    ");
			OLED_ShowStr(0,line5_1,(u8 *)text_env,1);
		}

		}
		
		break;
//////////////////////////////////设置界面	

	case setting_page:{

	}
	break;

	case setting_page_threshold:{

	}	
		break;
		
	default:
	break;
}

}

void key_do1(void){//按钮操作功能
	


	switch (page)
		{
	//////////////////////////////////初始界面
		case main_page:{
			if(key[0].single_flag)
			{
				if(line!=main_page_setting_line){
					sprintf(text_env," setting            ");//选中setting选项
					OLED_ShowStr(0,line8_1,(u8 *)text_env,1);
					OLED_AreaToggle(0,line8_1,9*6,8);
					line=main_page_setting_line;
				}
				else{
					OLED_AreaToggle(0,line8_1,9*6,8);
					line=0;//取消选中setting选项
				}

				key[0].single_flag=0;//清除按下按钮标志，等待下一次按钮触发
			}
			
			if(key[1].single_flag){
				if(line==main_page_setting_line){//点击setting选项进入设置界面
				
					page=setting_page;
					OLED_ClearRAM();
					OLED_RefreshRAM();
					line=setting_page_BUZZER_line;
					page2_init();	
				}
				key[1].single_flag=0;//清除按下按钮标志，等待下一次按钮触发
			}			
		}
		
			break;
	//////////////////////////////////设置界面	
		case setting_page:{
			
		if(key[0].single_flag)
		{
			
			switch (line)
			{
	 ////////////////////////
			case setting_page_back_line:{//选中开关蜂鸣器（buzzer ON/OFF:ON）选项

			
				OLED_AreaToggle(0,line8_1,5*6,8);
				
				if(buzzer_flag){

					sprintf(text_env,"buzzer ON/OFF:ON    ");
				OLED_ShowStr(0,line1_1,(u8 *)text_env,1);	

				}
				else{

					sprintf(text_env,"buzzer ON/OFF:OFF    ");
				OLED_ShowStr(0,line1_1,(u8 *)text_env,1);
				

				}
					OLED_AreaToggle(0,line1_1,18*6,8);
					line=setting_page_BUZZER_line;//下一次选中目标
			}

				break;

	 ////////////////////////
			case setting_page_BUZZER_line:{///选中调节阈值（threshold set）选项

				OLED_AreaToggle(0,line1_1,18*6,8);
				sprintf(text_env,"threshold set        ");
				OLED_ShowStr(0,line2_1,(u8 *)text_env,1);
				OLED_AreaToggle(0,line2_1,14*6,8);
				line=setting_page_threshold;
			}

				break;
			case setting_page_threshold:{//选择返回（back）选项

				OLED_AreaToggle(0,line2_1,14*6,8);
				sprintf(text_env,"back                 ");
				OLED_ShowStr(0,line8_1,(u8 *)text_env,1);
				OLED_AreaToggle(0,line8_1,5*6,8);
				line=setting_page_back_line;

			}

				break;				
			default:line=no_line;
				break;
			}

			key[0].single_flag=0;
		}
		
		if(key[1].single_flag){//按下第二个按钮，达到点击选择的功能
			switch(line){
	     ///////////////////////		
				case setting_page_back_line:{//点击back选项，返回主页面
					page=0;
					OLED_ClearRAM();
					//OLED_RefreshRAM();
					line=0;
				sprintf(text_env," setting            ");
				OLED_ShowStr(0,line8_1,(u8 *)text_env,1);
				}

					break;


	     ////////////////////////
				case setting_page_BUZZER_line:{//点击开关蜂鸣器（buzzer ON/OFF:ON）选项，关闭蜂鸣器报警
					
					if(buzzer_flag) buzzer_flag=0;//buzzer_flag为全局蜂鸣器使能开关
					else buzzer_flag=1;
					if(buzzer_flag){
						sprintf(text_env,"buzzer ON/OFF:ON    ");
						OLED_ShowStr(0,line1_1,(u8 *)text_env,1);	
						OLED_AreaToggle(0,line1_1,18*6,8);
					}
					else{
						sprintf(text_env,"buzzer ON/OFF:OFF   ");
						OLED_ShowStr(0,line1_1,(u8 *)text_env,1);
						OLED_AreaToggle(0,line1_1,18*6,8);
					}				
				}
					
					break;	
				case setting_page_threshold:{//点击选中调节阈值（threshold set）选项，进入阈值设置界面
					page=threshold_page;
					OLED_ClearRAM();
					OLED_RefreshRAM();
					line=threshold_temperature_line;

					sprintf(text_env,"temperature: %d     ",temperature_t);//阈值设置界面显示的初始化
					OLED_ShowStr(0,line1_1,(u8 *)text_env,1);
					OLED_AreaToggle(0,line1_1,15*6,8);	
					sprintf(text_env,"humidity: %d         ",humidity_t);
					OLED_ShowStr(0,line2_1,(u8 *)text_env,1);
					sprintf(text_env,"Light: %.3f          ",Light_t);
					OLED_ShowStr(0,line3_1,(u8 *)text_env,1);	
					sprintf(text_env,"    +         -      ");//4~6
					OLED_ShowStr(0,line6_1,(u8 *)text_env,1);		
					sprintf(text_env,"back                 ");
				    OLED_ShowStr(0,line8_1,(u8 *)text_env,1);								
				}	
				break;

			default:line=no_line;
				break;				
			
			}
			key[1].single_flag=0;
			}					
	}

		break;
    ////////////////选择阈值设置界面，会显示当前温度，湿度，光照强度的阈值
		case threshold_page:{
			if(key[0].single_flag)
			{
				switch (line)
				{

				case setting_page_back_line:{//选中温度阈值调节（temperature: ）
					OLED_AreaToggle(0,line8_1,5*6,8);
					sprintf(text_env,"temperature: %d      ",temperature_t);
					OLED_ShowStr(0,line1_1,(u8 *)text_env,1);
					OLED_AreaToggle(0,line1_1,15*6,8);
					line=threshold_temperature_line;

				}
				break;	

				case threshold_temperature_line:{//选中湿度阈值调节（humidity: ）
					
					OLED_AreaToggle(0,line1_1,15*6,8);
					sprintf(text_env,"humidity: %d         ",humidity_t);
					OLED_ShowStr(0,line2_1,(u8 *)text_env,1);
					OLED_AreaToggle(0,line2_1,13*6,8);
					line=threshold_humidity_line;

				}
					break;
				
				case threshold_humidity_line:{//选中光强阈值调节（Light:）

					OLED_AreaToggle(0,line2_1,13*6,8);
					sprintf(text_env,"Light: %.3f          ",Light_t);
					OLED_ShowStr(0,line3_1,(u8 *)text_env,1);					
					OLED_AreaToggle(0,line3_1,16*6,8);
					line=threshold_Light_line;
				}
					break;

				case threshold_Light_line:{//选中返回选项（back）

					OLED_AreaToggle(0,line3_1,16*6,8);
					sprintf(text_env,"back                 ");
				    OLED_ShowStr(0,line8_1,(u8 *)text_env,1);						
					OLED_AreaToggle(0,line8_1,5*6,8);
					line=setting_page_back_line;

				}
					break;		

				default:
					break;
				}
				key[0].single_flag=0;
			}
			
			if(key[1].single_flag){
				
				switch (line)
				{
				case threshold_temperature_line:{//点击温度阈值设置（temperature:），进入设置数值界面

					OLED_AreaToggle(0,line1_1,15*6,8);
					sprintf(text_env,"temperature: %d      ",temperature_t);
					OLED_ShowStr(0,line1_1,(u8 *)text_env,1);					
					OLED_AreaToggle(13*6,line1_1,4*6,8);

					sprintf(text_env,"    +         -      ");//4~6,14~16
					OLED_ShowStr(0,line6_1,(u8 *)text_env,1);	
					OLED_AreaToggle(4*6,line6_1,3*6,8);
					page=threshold_set;
					line_p=threshold_add;

				}
					break;
				case threshold_humidity_line:{//点击湿度阈值设置（humidity:），进入设置数值界面

					OLED_AreaToggle(0,line2_1,13*6,8);	
					sprintf(text_env,"humidity: %d         ",humidity_t);
					OLED_ShowStr(0,line2_1,(u8 *)text_env,1);
					OLED_AreaToggle(10*6,line2_1,4*6,8);

					sprintf(text_env,"    +         -      ");//4~6,14~16
					OLED_ShowStr(0,line6_1,(u8 *)text_env,1);	
					OLED_AreaToggle(4*6,line6_1,3*6,8);
					page=threshold_set;
					line_p=threshold_add;

				}
					break;
				case threshold_Light_line:{//点击光照强度阈值设置（Light: ），进入设置数值界面

					OLED_AreaToggle(0,line3_1,16*6,8);
					sprintf(text_env,"Light: %.3f          ",Light_t);
					OLED_ShowStr(0,line3_1,(u8 *)text_env,1);					
					OLED_AreaToggle(7*6,line3_1,10*6,8);

					sprintf(text_env,"    +         -      ");//4~6,14~16
					OLED_ShowStr(0,line6_1,(u8 *)text_env,1);	
					OLED_AreaToggle(4*6,line6_1,3*6,8);
					page=threshold_set;
					line_p=threshold_add;
				}
					break;

				case setting_page_back_line:{//点击返回（back）选项，返回设置界面
					page=setting_page;
					OLED_ClearRAM();
					OLED_RefreshRAM();
					line=setting_page_BUZZER_line;
					page2_init();	

				}
					break;

				default:
					break;
				}
				key[1].single_flag=0;
			}		

		}
		break;
///////////////////////阈值数值设置界面，可以进行数值阈值的调节通过点击“+”，“-”来实现阈值数值的调节
		case threshold_set:{
		if(key[0].single_flag)
			{
				switch (line_p)
				{

				case setting_page_back_line:{//选择“+”选项

					OLED_AreaToggle(0,line8_1,5*6,8);
					sprintf(text_env,"    +         -      ");//4~6,14~16
					OLED_ShowStr(0,line6_1,(u8 *)text_env,1);	
					OLED_AreaToggle(4*6,line6_1,3*6,8);		
					line_p=threshold_add;

				}

					break;
				case threshold_add:{//选择“-”选项

					OLED_AreaToggle(4*6,line6_1,6*6,8);
					sprintf(text_env,"    +         -      ");//4~6,14~16
					OLED_ShowStr(0,line6_1,(u8 *)text_env,1);	
					OLED_AreaToggle(14*6,line6_1,3*6,8);		
					line_p=threshold_sub;

				}
					break;
				case threshold_sub:{//选择返回“back”选项
					OLED_AreaToggle(14*6,line6_1,3*6,8);
					sprintf(text_env,"back                 ");
				    OLED_ShowStr(0,line8_1,(u8 *)text_env,1);						
					OLED_AreaToggle(0,line8_1,5*6,8);
					line_p=setting_page_back_line;
				}
					break;

				default:
					break;
				}

				key[0].single_flag=0;
			}
			
			if(key[1].single_flag){
				switch (line_p)
				{

				case threshold_add:{//点击“+”选项，增加选中的阈值
                    
                    //判断选中的是什么数据，并进行增加阈值
					if(line==threshold_temperature_line){
						temperature_t+=1;
						sprintf(text_env,"temperature: %d      ",temperature_t);
						OLED_ShowStr(0,line1_1,(u8 *)text_env,1);	
						OLED_AreaToggle(13*6,line1_1,4*6,8);
					}
					else if(line==threshold_humidity_line){
						humidity_t+=1;
						sprintf(text_env,"humidity: %d         ",humidity_t);
						OLED_ShowStr(0,line2_1,(u8 *)text_env,1);
						OLED_AreaToggle(10*6,line2_1,4*6,8);
					}
					else{//light
						Light_t+=100;
						sprintf(text_env,"Light: %.3f          ",Light_t);
						OLED_ShowStr(0,line3_1,(u8 *)text_env,1);					
						OLED_AreaToggle(7*6,line3_1,10*6,8);

					}

				}
					break;
				case threshold_sub:{//点击“-”选项，减少选中的阈值
                    //判断选中的是什么数据，并进行减少阈值
					if(line==threshold_temperature_line){
						temperature_t-=1;
						sprintf(text_env,"temperature: %d      ",temperature_t);
						OLED_ShowStr(0,line1_1,(u8 *)text_env,1);	
						OLED_AreaToggle(13*6,line1_1,4*6,8);
					}
					else if(line==threshold_humidity_line){
						humidity_t-=1;
						sprintf(text_env,"humidity: %d         ",humidity_t);
						OLED_ShowStr(0,line2_1,(u8 *)text_env,1);
						OLED_AreaToggle(10*6,line2_1,4*6,8);
					}
					else{//light
						Light_t-=100;
						sprintf(text_env,"Light: %.3f          ",Light_t);
						OLED_ShowStr(0,line3_1,(u8 *)text_env,1);					
						OLED_AreaToggle(7*6,line3_1,10*6,8);

					}

				}
					break;

				case setting_page_back_line:{//点击返回选项（back），返回选择阈值设置界面
					page=threshold_page;
					OLED_ClearRAM();
					OLED_RefreshRAM();
					line=threshold_temperature_line;

					sprintf(text_env,"temperature: %d     ",temperature_t);
					OLED_ShowStr(0,line1_1,(u8 *)text_env,1);
					OLED_AreaToggle(0,line1_1,15*6,8);	
					sprintf(text_env,"humidity: %d         ",humidity_t);
					OLED_ShowStr(0,line2_1,(u8 *)text_env,1);
					sprintf(text_env,"Light: %.3f          ",Light_t);
					OLED_ShowStr(0,line3_1,(u8 *)text_env,1);	
					sprintf(text_env,"    +         -      ");//4~6
					OLED_ShowStr(0,line6_1,(u8 *)text_env,1);		
					sprintf(text_env,"back                 ");
				    OLED_ShowStr(0,line8_1,(u8 *)text_env,1);							

				}
					break;				
				default:
					break;
				}

				key[1].single_flag=0;
			}			

		}
		break;

		default:
		break;
	}
	


}
///////////////////在此之前在所有超过阈值产生的报警信号都会先进行检测全局蜂鸣器开关（buzzer_flag）是否开启，若开启才会产生报警信号（buzzer_sin）
void BUZZER_do(void){
	if(buzzer_tick>0||buzzer_sin)//判断是否打开蜂鸣器报警，buzzer_tick可以调节蜂鸣器响的时间
	{

		if(buzzer_sin){
			
			buzzer_tick=2;
			buzzer_sin=0;
			BUZZER_BEEP1();			
		}
		if(buzzer_tick>0){
			buzzer_tick--;
		}

	
	}
	else{
	
		BUZZER_OFF();
	}
}

void page2_init(void){//设置界面的初始化


		if(buzzer_flag){
			sprintf(text_env,"buzzer ON/OFF:ON");
			OLED_ShowStr(0,line1_1,(u8 *)text_env,1);	
		
		}
		else{
			sprintf(text_env,"buzzer ON/OFF:OFF");
			OLED_ShowStr(0,line1_1,(u8 *)text_env,1);
		
		}

		sprintf(text_env,"threshold set        ");
		OLED_ShowStr(0,line2_1,(u8 *)text_env,1);

		sprintf(text_env," back                ");
		OLED_ShowStr(0,line8_1,(u8 *)text_env,1);
		OLED_AreaToggle(0,line1_1,18*6,8);

}
