#ifndef __DHT11__
#define __DHT11__

#include "main.h"



#define DHT11_HIGH     HAL_GPIO_WritePin(GPIOB, DHT11_Pin,	GPIO_PIN_SET) //输出高电平
#define DHT11_LOW      HAL_GPIO_WritePin(GPIOB, DHT11_Pin, GPIO_PIN_RESET)//输出低电平
#define DHT11_IO_IN      HAL_GPIO_ReadPin(GPIOB, DHT11_Pin)//读取IO口电平

void DHT11_OUT(void);	
												
void DHT11_IN(void);                          //DHT11_Data IO设置为输入模式
void DHT11_Start(void);				          //主机发出起始信号
uint8_t DHT11_Check(void);                    //DHT11发送响应信号
uint8_t DHT11_Read_Bit(void);                 //读取DHT11一个BIT的数据
uint8_t DHT11_Read_Byte(void);                //读取DHT11一个Byte的数据
uint8_t DHT11_Read_Data(uint8_t* temp , uint8_t* humi);  //读取DHT11湿度和温度的数据
void DHT_init(void);
void DHT_do(void);








#endif /* __DHT11__ */
