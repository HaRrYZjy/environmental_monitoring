#ifndef __ENVIRONMENT_H__
#define __ENVIRONMENT_H__

#include "main.h"
extern u8 page;
extern u8 line;
extern u8 buzzer_flag;
extern u8 buzzer_sin;
extern int buzzer_tick;

#define main_page 0
#define setting_page 1
#define threshold_page 2
#define threshold_set 3

#define no_line 0
#define main_page_setting_line 8

#define setting_page_BUZZER_line 1
#define setting_page_back_line 8
#define setting_page_threshold 7

#define threshold_temperature_line 0
#define threshold_humidity_line 1
#define threshold_Light_line 2
#define threshold_add 3
#define threshold_sub 4


void PASS_DO1(void);
void DHT_init(void);
void DHT_do1(void);
void Light_do1(void);
void key_do1(void);
void page2_init(void);
void BUZZER_do(void);
#endif //__ENVIRONMENT_H__
