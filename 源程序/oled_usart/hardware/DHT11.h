#ifndef __DHT11__
#define __DHT11__

#include "main.h"



#define DHT11_HIGH     HAL_GPIO_WritePin(GPIOB, DHT11_Pin,	GPIO_PIN_SET) //����ߵ�ƽ
#define DHT11_LOW      HAL_GPIO_WritePin(GPIOB, DHT11_Pin, GPIO_PIN_RESET)//����͵�ƽ
#define DHT11_IO_IN      HAL_GPIO_ReadPin(GPIOB, DHT11_Pin)//��ȡIO�ڵ�ƽ

void DHT11_OUT(void);	
												
void DHT11_IN(void);                          //DHT11_Data IO����Ϊ����ģʽ
void DHT11_Start(void);				          //����������ʼ�ź�
uint8_t DHT11_Check(void);                    //DHT11������Ӧ�ź�
uint8_t DHT11_Read_Bit(void);                 //��ȡDHT11һ��BIT������
uint8_t DHT11_Read_Byte(void);                //��ȡDHT11һ��Byte������
uint8_t DHT11_Read_Data(uint8_t* temp , uint8_t* humi);  //��ȡDHT11ʪ�Ⱥ��¶ȵ�����
void DHT_init(void);
void DHT_do(void);








#endif /* __DHT11__ */
