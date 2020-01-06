/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2019 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
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
/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

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

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define YM_WR GPIO_PIN_13
#define YM_WR_GPIO_Port GPIOC
#define YM_A0 GPIO_PIN_14
#define YM_A0_GPIO_Port GPIOC
#define YM_RST GPIO_PIN_15
#define YM_RST_GPIO_Port GPIOC
#define IO_1 GPIO_PIN_0
#define IO_1_GPIO_Port GPIOC
#define IO_2 GPIO_PIN_1
#define IO_2_GPIO_Port GPIOC
#define IO_3 GPIO_PIN_2
#define IO_3_GPIO_Port GPIOC
#define IO_4 GPIO_PIN_3
#define IO_4_GPIO_Port GPIOC
#define IO_5 GPIO_PIN_0
#define IO_5_GPIO_Port GPIOA
#define IO_6 GPIO_PIN_1
#define IO_6_GPIO_Port GPIOA
#define SPI_INT_A_2 GPIO_PIN_2
#define SPI_INT_A_2_GPIO_Port GPIOA
#define SPI_INT_B_2 GPIO_PIN_3
#define SPI_INT_B_2_GPIO_Port GPIOA
#define ADC_1 GPIO_PIN_4
#define ADC_1_GPIO_Port GPIOA
#define ADC_2 GPIO_PIN_5
#define ADC_2_GPIO_Port GPIOA
#define ADC_3 GPIO_PIN_6
#define ADC_3_GPIO_Port GPIOA
#define VOL_1 GPIO_PIN_7
#define VOL_1_GPIO_Port GPIOA
#define VOL_2 GPIO_PIN_4
#define VOL_2_GPIO_Port GPIOC
#define VOL_3 GPIO_PIN_5
#define VOL_3_GPIO_Port GPIOC
#define VOL_4 GPIO_PIN_0
#define VOL_4_GPIO_Port GPIOB
#define VOL_TOT GPIO_PIN_1
#define VOL_TOT_GPIO_Port GPIOB
#define SPI_LCD_CS GPIO_PIN_12
#define SPI_LCD_CS_GPIO_Port GPIOB
#define SPI_NSS_2 GPIO_PIN_6
#define SPI_NSS_2_GPIO_Port GPIOC
#define SPI_NSS_1 GPIO_PIN_7
#define SPI_NSS_1_GPIO_Port GPIOC
#define SPI_RST GPIO_PIN_8
#define SPI_RST_GPIO_Port GPIOC
#define SPI_INT_A_1 GPIO_PIN_9
#define SPI_INT_A_1_GPIO_Port GPIOA
#define SPI_INT_B_1 GPIO_PIN_10
#define SPI_INT_B_1_GPIO_Port GPIOA
#define YM_CS_1 GPIO_PIN_15
#define YM_CS_1_GPIO_Port GPIOA
#define YM_CS_2 GPIO_PIN_10
#define YM_CS_2_GPIO_Port GPIOC
#define YM_CS_3 GPIO_PIN_11
#define YM_CS_3_GPIO_Port GPIOC
#define YM_CS_4 GPIO_PIN_12
#define YM_CS_4_GPIO_Port GPIOC
#define YM_D0 GPIO_PIN_2
#define YM_D0_GPIO_Port GPIOD
#define YM_D1 GPIO_PIN_3
#define YM_D1_GPIO_Port GPIOB
#define YM_D2 GPIO_PIN_4
#define YM_D2_GPIO_Port GPIOB
#define YM_D3 GPIO_PIN_5
#define YM_D3_GPIO_Port GPIOB
#define YM_D4 GPIO_PIN_6
#define YM_D4_GPIO_Port GPIOB
#define YM_D5 GPIO_PIN_7
#define YM_D5_GPIO_Port GPIOB
#define YM_D6 GPIO_PIN_8
#define YM_D6_GPIO_Port GPIOB
#define YM_D7 GPIO_PIN_9
#define YM_D7_GPIO_Port GPIOB
/* USER CODE BEGIN Private defines */
ADC_HandleTypeDef hadc1;

SPI_HandleTypeDef hspi2;

UART_HandleTypeDef huart2;

typedef struct
{
	uint8_t Waveform;
	uint8_t AM;
	uint8_t Vibrato;
	uint8_t Pedal_Sustain;
	uint8_t ModFreqMult;
	uint8_t Volume;
	uint8_t Attack;
	uint8_t Decay;
	uint8_t Sustain;
	uint8_t Release;
	uint8_t KSR;
	uint8_t ScalingLevel;
}Operator;

/* Struct om data op te slaan per voice channel ------------------------------*/
typedef struct
{
	uint8_t Enable;
	uint8_t KEY_Numb;
	uint16_t F_Numb;
	uint8_t Octave;
	uint8_t Velocity;
	uint8_t i_tel;

}pVCH;

/* Struct om data op te slaan per chip channel -------------------------------*/
typedef struct
{
	uint8_t AM_Depth;
	uint8_t Vib_Depth;
	uint8_t Feedback;
	uint8_t ModulatieMode;

	Operator OP1;
	Operator OP2;
}*pCCH;

uint8_t YM_PitchValue;
extern pCCH CCH[4];
/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
