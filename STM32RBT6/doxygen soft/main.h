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
ADC_HandleTypeDef hadc1;		/**< handle for adc functions */

SPI_HandleTypeDef hspi2;		/**< handle for spi functions */

UART_HandleTypeDef huart3;		/**< handle for the uart function */
/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define YM_WR GPIO_PIN_13			/**< GPIO init value define */
#define YM_WR_GPIO_Port GPIOC		/**< GPIO init value define */
#define YM_A0 GPIO_PIN_14			/**< GPIO init value define */
#define YM_A0_GPIO_Port GPIOC		/**< GPIO init value define */
#define YM_RST GPIO_PIN_15			/**< GPIO init value define */
#define YM_RST_GPIO_Port GPIOC		/**< GPIO init value define */
#define IO_1 GPIO_PIN_0				/**< GPIO init value define */
#define IO_1_GPIO_Port GPIOC		/**< GGPIO init value define */
#define IO_2 GPIO_PIN_1				/**< GPIO init value define */
#define IO_2_GPIO_Port GPIOC		/**< GPIO init value define */
#define IO_3 GPIO_PIN_2				/**< GPIO init value define */
#define IO_3_GPIO_Port GPIOC		/**< GPIO init value define */
#define IO_4 GPIO_PIN_3				/**< GPIO init value define */
#define IO_4_GPIO_Port GPIOC		/**< GPIO init value define */
#define IO_5 GPIO_PIN_0				/**< GPIO init value define */
#define IO_5_GPIO_Port GPIOA		/**< GPIO init value define */
#define IO_6 GPIO_PIN_1				/**< GPIO init value define */
#define IO_6_GPIO_Port GPIOA		/**< GPIO init value define */
#define SPI_INT_A_2 GPIO_PIN_2		/**< GPIO init value define */
#define SPI_INT_A_2_GPIO_Port GPIOA	/**< GPIO init value define */
#define SPI_INT_B_2 GPIO_PIN_3		/**< GPIO init value define */
#define SPI_INT_B_2_GPIO_Port GPIOA	/**< GPIO init value define */
#define ADC_1 GPIO_PIN_4			/**< GPIO init value define */
#define ADC_1_GPIO_Port GPIOA		/**< GPIO init value define */
#define ADC_2 GPIO_PIN_5			/**< GPIO init value define */
#define ADC_2_GPIO_Port GPIOA		/**< GPIO init value define */
#define ADC_3 GPIO_PIN_6			/**< GPIO init value define */
#define ADC_3_GPIO_Port GPIOA		/**< GPIO init value define */
#define VOL_1 GPIO_PIN_7			/**< GPIO init value define */
#define VOL_1_GPIO_Port GPIOA		/**< GPIO init value define */
#define VOL_2 GPIO_PIN_4			/**< GPIO init value define */
#define VOL_2_GPIO_Port GPIOC		/**< GPIO init value define */
#define VOL_3 GPIO_PIN_5			/**< GPIO init value define */
#define VOL_3_GPIO_Port GPIOC		/**< GPIO init value define */
#define VOL_4 GPIO_PIN_0			/**< GPIO init value define */
#define VOL_4_GPIO_Port GPIOB		/**< GPIO init value define */
#define VOL_TOT GPIO_PIN_1			/**< GPIO init value define */
#define VOL_TOT_GPIO_Port GPIOB		/**< GPIO init value define */
#define SPI_LCD_CS GPIO_PIN_12		/**< GPIO init value define */
#define SPI_LCD_CS_GPIO_Port GPIOB	/**< GPIO init value define */
#define SPI_NSS_2 GPIO_PIN_6		/**< GPIO init value define */
#define SPI_NSS_2_GPIO_Port GPIOC	/**< GPIO init value define */
#define SPI_NSS_1 GPIO_PIN_7		/**< GPIO init value define */
#define SPI_NSS_1_GPIO_Port GPIOC	/**< GPIO init value define */
#define SPI_RST GPIO_PIN_8			/**< GPIO init value define */
#define SPI_RST_GPIO_Port GPIOC		/**< GPIO init value define */
#define SPI_INT_A_1 GPIO_PIN_9		/**< GPIO init value define */
#define SPI_INT_A_1_GPIO_Port GPIOA	/**< GPIO init value define */
#define SPI_INT_B_1 GPIO_PIN_10		/**< GPIO init value define */
#define SPI_INT_B_1_GPIO_Port GPIOA	/**< GPIO init value define */
#define YM_CS_1 GPIO_PIN_15			/**< GPIO init value define */
#define YM_CS_1_GPIO_Port GPIOA		/**< GPIO init value define */
#define YM_CS_2 GPIO_PIN_10			/**< GPIO init value define */
#define YM_CS_2_GPIO_Port GPIOC		/**< GPIO init value define */
#define YM_CS_3 GPIO_PIN_11			/**< GPIO init value define */
#define YM_CS_3_GPIO_Port GPIOC		/**< GPIO init value define */
#define YM_CS_4 GPIO_PIN_12			/**< GPIO init value define */
#define YM_CS_4_GPIO_Port GPIOC		/**< GPIO init value define */
#define YM_D0 GPIO_PIN_2			/**< GPIO init value define */
#define YM_D0_GPIO_Port GPIOD		/**< GPIO init value define */
#define YM_D1 GPIO_PIN_3			/**< GPIO init value define */
#define YM_D1_GPIO_Port GPIOB		/**< GPIO init value define */
#define YM_D2 GPIO_PIN_4			/**< GPIO init value define */
#define YM_D2_GPIO_Port GPIOB		/**< GPIO init value define */
#define YM_D3 GPIO_PIN_5			/**< GPIO init value define */
#define YM_D3_GPIO_Port GPIOB		/**< GPIO init value define */
#define YM_D4 GPIO_PIN_6			/**< GPIO init value define */
#define YM_D4_GPIO_Port GPIOB		/**< GPIO init value define */
#define YM_D5 GPIO_PIN_7			/**< GPIO init value define */
#define YM_D5_GPIO_Port GPIOB		/**< GPIO init value define */
#define YM_D6 GPIO_PIN_8			/**< GPIO init value define */
#define YM_D6_GPIO_Port GPIOB		/**< GPIO init value define */
#define YM_D7 GPIO_PIN_9			/**< GPIO init value define */
#define YM_D7_GPIO_Port GPIOB		/**< GPIO init value define */

/* USER CODE BEGIN Private defines */

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

uint8_t YM_PitchValue;	/**< Variable for storing the pitchvalue from the pitchwheel  */
extern pCCH CCH[4];		/**< four variables for the effects settings structs of each chip channel */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
