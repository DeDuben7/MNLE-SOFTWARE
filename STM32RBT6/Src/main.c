/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file			main.c
  * @brief        	Header for main.c file.
  *               	This file contains the common defines of the application.
  * @version		V1.00
  * @authors		Oehlers, van Renswoude and Schotborgh
  * @date			06-01-2020
  ******************************************************************************
  * @details
  ******************************************************************************
*/
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "includes.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/


/* USER CODE BEGIN PV */
uint8_t ReceiveFlag = FALSE;	/**< flag to indicate whether a uart message is received */
uint8_t data;					/**< byte for storing the received uart data */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_ADC1_Init(void);
static void MX_SPI2_Init(void);
static void MX_USART3_UART_Init(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
  * @fn			int main(void)
  * @brief		The application entry point.
  * @details	This is the main function from which the software runs.
  * 			The main function contains all the needed initializations
  */
int main(void)
{
  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */
  

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_ADC1_Init();
  MX_SPI2_Init();
  MX_USART3_UART_Init();
  /* USER CODE BEGIN 2 */

  YM_RESET();  // reset the YM3812 chips
  YM_SET_Def(); // set the default settings for the YM3812 chips
  HAL_Delay(200);
  HAL_UART_Receive_IT(&huart3, &data, 1); // enable the receive under interrupt mode for UART2
  // Setting YM_CS pins
  HAL_GPIO_WritePin(GPIOC,YM_CS_2|YM_CS_3|YM_CS_4,GPIO_PIN_SET);
  HAL_GPIO_WritePin(GPIOA, YM_CS_1 ,GPIO_PIN_SET);

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
	  if(ReceiveFlag) // if the receiveflag is set, reset the flag and call the MIDI_PROC function
	  {
		  ReceiveFlag = FALSE;
		  MIDI_PROC(data);
		  HAL_GPIO_WritePin(GPIOC, IO_1, GPIO_PIN_SET);
	  }
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */
}

/**
  * @fn			void SystemClock_Config(void)
  * @brief		System clock configuration.
  * @details	This function configures the system clock to the right speeds.
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};
  RCC_PeriphCLKInitTypeDef PeriphClkInit = {0};

  /** Initializes the CPU, AHB and APB busses clocks 
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.HSEPredivValue = RCC_HSE_PREDIV_DIV1;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL9;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB busses clocks 
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    Error_Handler();
  }
  PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_ADC;
  PeriphClkInit.AdcClockSelection = RCC_ADCPCLK2_DIV6;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @fn			static void MX1_ADC1_Init(void)
  * @brief		ADC configuration.
  * @details	This function configures the ADC.
  */
static void MX_ADC1_Init(void)
{

  /* USER CODE BEGIN ADC1_Init 0 */

  /* USER CODE END ADC1_Init 0 */

  ADC_ChannelConfTypeDef sConfig = {0};

  /* USER CODE BEGIN ADC1_Init 1 */

  /* USER CODE END ADC1_Init 1 */
  /** Common config 
  */
  hadc1.Instance = ADC1;
  hadc1.Init.ScanConvMode = ADC_SCAN_DISABLE;
  hadc1.Init.ContinuousConvMode = DISABLE;
  hadc1.Init.DiscontinuousConvMode = DISABLE;
  hadc1.Init.ExternalTrigConv = ADC_SOFTWARE_START;
  hadc1.Init.DataAlign = ADC_DATAALIGN_RIGHT;
  hadc1.Init.NbrOfConversion = 1;
  if (HAL_ADC_Init(&hadc1) != HAL_OK)
  {
    Error_Handler();
  }
  /** Configure Regular Channel 
  */
  sConfig.Channel = ADC_CHANNEL_4;
  sConfig.Rank = ADC_REGULAR_RANK_1;
  sConfig.SamplingTime = ADC_SAMPLETIME_1CYCLE_5;
  if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /** Configure Regular Channel 
  */
  if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN ADC1_Init 2 */

  /* USER CODE END ADC1_Init 2 */

}

/**
  * @fn			static void MX_SPI2_Init(void)
  * @brief		SPI configuration.
  * @details	This function configures the right SPI bus for usage.
  */
static void MX_SPI2_Init(void)
{

  /* USER CODE BEGIN SPI2_Init 0 */

  /* USER CODE END SPI2_Init 0 */

  /* USER CODE BEGIN SPI2_Init 1 */

  /* USER CODE END SPI2_Init 1 */
  /* SPI2 parameter configuration*/
  hspi2.Instance = SPI2;
  hspi2.Init.Mode = SPI_MODE_MASTER;
  hspi2.Init.Direction = SPI_DIRECTION_2LINES;
  hspi2.Init.DataSize = SPI_DATASIZE_8BIT;
  hspi2.Init.CLKPolarity = SPI_POLARITY_LOW;
  hspi2.Init.CLKPhase = SPI_PHASE_1EDGE;
  hspi2.Init.NSS = SPI_NSS_SOFT;
  hspi2.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_2;
  hspi2.Init.FirstBit = SPI_FIRSTBIT_MSB;
  hspi2.Init.TIMode = SPI_TIMODE_DISABLE;
  hspi2.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
  hspi2.Init.CRCPolynomial = 10;
  if (HAL_SPI_Init(&hspi2) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN SPI2_Init 2 */

  /* USER CODE END SPI2_Init 2 */

}

/**
  * @fn			static void MX_USART3_UART_Init(void)
  * @brief		UART configuration.
  * @details	This function configures the right UART bus for usage.
  */
static void MX_USART3_UART_Init(void)
{

  /* USER CODE BEGIN USART3_Init 0 */

  /* USER CODE END USART3_Init 0 */

  /* USER CODE BEGIN USART3_Init 1 */

  /* USER CODE END USART3_Init 1 */
  huart3.Instance = USART3;
  huart3.Init.BaudRate = 32500;
  huart3.Init.WordLength = UART_WORDLENGTH_8B;
  huart3.Init.StopBits = UART_STOPBITS_1;
  huart3.Init.Parity = UART_PARITY_NONE;
  huart3.Init.Mode = UART_MODE_TX_RX;
  huart3.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart3.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart3) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART3_Init 2 */
  HAL_NVIC_SetPriority(USART3_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(USART3_IRQn);
  /* USER CODE END USART3_Init 2 */

}

/**
  * @fn			static void MX_GPIO_Init(void)
  * @brief		GPIO configuration.
  * @details	This functionn configures the right GPIO pins
  * 			with the right settings.
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOD_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOC, YM_WR|YM_A0|YM_RST|IO_1
                          |IO_2|IO_3|IO_4|SPI_NSS_1
                          |SPI_RST|YM_CS_2|YM_CS_3|YM_CS_4, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, IO_5|IO_6|SPI_INT_A_2|SPI_INT_B_2
                          |SPI_INT_A_1|SPI_INT_B_1|YM_CS_1, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, SPI_LCD_CS|YM_D2|YM_D3|YM_D4
                          |YM_D5|YM_D6|YM_D7, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(YM_D0_GPIO_Port, YM_D0, GPIO_PIN_RESET);


  /*Configure GPIO pins : YM_WR_Pin YM_A0_Pin YM_RST_Pin IO_1_Pin 
                           IO_2_Pin IO_3_Pin IO_4_Pin SPI_NSS_1_Pin 
                           SPI_RST_Pin YM_CS_2_Pin YM_CS_3_Pin YM_CS_4_Pin */
  GPIO_InitStruct.Pin = YM_WR|YM_A0|YM_RST|IO_1
                          |IO_2|IO_3|IO_4|SPI_NSS_1|SPI_NSS_2
                          |SPI_RST|YM_CS_2|YM_CS_3|YM_CS_4;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  /*Configure GPIO pins : IO_5_Pin IO_6_Pin SPI_INT_A_2_Pin SPI_INT_B_2_Pin 
                           SPI_INT_A_1_Pin SPI_INT_B_1_Pin YM_CS_1_Pin */
  GPIO_InitStruct.Pin = IO_5|IO_6|SPI_INT_A_2|SPI_INT_B_2
                          |SPI_INT_A_1|SPI_INT_B_1|YM_CS_1;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pins : SPI_LCD_CS_Pin YM_D2_Pin YM_D3_Pin YM_D4_Pin 
                           YM_D5_Pin YM_D6_Pin YM_D7_Pin */
  GPIO_InitStruct.Pin = SPI_LCD_CS|YM_D1|YM_D2|YM_D3|YM_D4
                          |YM_D5|YM_D6|YM_D7;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pin : YM_D0_Pin */
  GPIO_InitStruct.Pin = YM_D0;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
  HAL_GPIO_Init(YM_D0_GPIO_Port, &GPIO_InitStruct);


}

/* USER CODE BEGIN 4 */
/**
  * @fn			void USART_IRQHandler(void)
  * @brief		Interrupt handler.
  * @details	This function handles UART interrupts and calls the
  * 			callback function.
  */
void USART3_IRQHandler(void)
{
	HAL_UART_IRQHandler(&huart3); // calls the callback function
}

/**
  * @fn			void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
  * @brief		UART callback function.
  * @details	This function is called by the UART interrupt handler and
  * 			sets the receive flag.
  */
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
	if (huart->Instance == USART3)
	{
		ReceiveFlag = TRUE;						// set the receiveflag
		HAL_UART_Receive_IT(&huart3, &data, 1); // enable receive under interrupt mode again
	}
}

/**
 *@mainpage 				RETROSYNTH
 * @section intro_sec		Introduction
 *							This Doxygen is for the people who want to recreate the RETROSYNTH.
 *							The doxygen is dedicated to explain the software. There will be extra comments in the software itself.
 *							Good luck on recreating!
 *
 *							Regards,
 *
 *							Oehlers, van Renswoude and Schotborgh
 */

/* USER CODE END 4 */

/**
  * @fn			void Error_Handler(void)
  * @brief		Error handler.
  * @details	This function is called when an error occurs. It will show
  * 			the error on the LCD.
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */

  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{ 
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     tex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
