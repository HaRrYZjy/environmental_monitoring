/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f1xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "gpio.h"
#include  "string.h"
#include <stdio.h>
/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */
#define u8 uint8_t
#define u16 uint16_t	
#define        ADC_CHANNEL        1        //ͨ����
#define        ADC_NUMBER        3        //һ��ͨ����Ÿ���
#define        ADC_LENGTH        (ADC_NUMBER * ADC_CHANNEL)
extern uint16_t    adcbuff[ADC_LENGTH]; 
/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */
void Delay_us(uint32_t udelay);
/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define key2_Pin GPIO_PIN_0
#define key2_GPIO_Port GPIOA
#define key1_Pin GPIO_PIN_1
#define key1_GPIO_Port GPIOA
#define DHT11_Pin GPIO_PIN_13
#define DHT11_GPIO_Port GPIOB
#define BUZZER_Pin GPIO_PIN_14
#define BUZZER_GPIO_Port GPIOB

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
