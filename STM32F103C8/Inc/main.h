/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file			main.h
  * @brief        	Header for main.c file.
  * @version		V1.00
  * @authors		Oehlers, van Renswoude and Schotborgh
  * @date			06-01-2020
  ******************************************************************************
  * @details		This file contains the common defines of the application.
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
/* USER CODE BEGIN Private defines */
/* Private variables ---------------------------------------------------------*/
ADC_HandleTypeDef hadc1; /**< handle for adc functions */

SPI_HandleTypeDef hspi1; /**< handle for spi functions */

TIM_HandleTypeDef htim1; /**< handle for the timer functions */

UART_HandleTypeDef huart2; /**< handle for the uart function */

typedef struct /**< structure for storing the effect settings of each chip channel */
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

typedef struct /**< Structure for storing the data of each voice channel */
{
	uint8_t Enable;
	uint8_t KEY_Numb;
	uint16_t F_Numb;
	uint8_t Octave;
	uint8_t Velocity;
	uint8_t i_tel;

}pVCH;

typedef struct /**< structure for storing the effect settings of each operator */
{
	uint8_t AM_Depth;
	uint8_t Vib_Depth;
	uint8_t Feedback;
	uint8_t ModulatieMode;

	Operator OP1;
	Operator OP2;
}*pCCH;

uint8_t YM_PitchValue; /**< Variable for storing the pitchvalue from the pitchwheel  */
extern pCCH CCH[4]; /**< four variables for the effects settings structs of each chip channel */
/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
