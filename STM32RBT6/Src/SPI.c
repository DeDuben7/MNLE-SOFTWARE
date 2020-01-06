/**
  ******************************************************************************
  * @file			SPI.c
  * @brief        	Header for main.c file.
  *               	This file contains the common defines of the application.
  * @version		V1.00
  * @authors		Oehlers, van Renswoude and Schotborgh
  * @date			06-01-2020
  ******************************************************************************
  * @details
  ******************************************************************************
*/

#include "includes.h"

uint8_t SPI_DATA_RX;			/**<  */
uint8_t OPCODE_WRITE = 0x40;	/**<  */
uint8_t OPCODE_READ = 0x41;		/**<  */

/**
  ******************************************************************************
  * @brief			The application entry point.
  * @headerfile x.h ""
  * @param 			None
  * @val
  * @return None
  ******************************************************************************
  * @details
  ******************************************************************************
  */
uint8_t SPI_Transmit(uint8_t addr, uint8_t data, uint8_t device)
{
	uint8_t iError = 0;

	if(device == LCD)
	{

	}

	else if(device == IO_EXP_1)
	{
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, GPIO_PIN_RESET);
		HAL_SPI_Transmit_IT(&hspi1, &OPCODE_WRITE, 1);
		HAL_SPI_Transmit_IT(&hspi1, &addr, 1);
		HAL_SPI_Transmit_IT(&hspi1, &data, 1);
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, GPIO_PIN_SET);
	}

	else if(device == IO_EXP_2)
	{

	}

	else
		return iError;

	return iError;
}

/**
  ******************************************************************************
  * @brief			The application entry point.
  * @headerfile x.h ""
  * @param 			None
  * @val
  * @return None
  ******************************************************************************
  * @details
  ******************************************************************************
  */
uint8_t SPI_Receive(uint8_t addr, uint8_t device)
{
	uint8_t iError = 0;

	if(device == LCD)
	{

	}

	else if(device == IO_EXP_1)
	{
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, GPIO_PIN_RESET);
		HAL_SPI_Transmit_IT(&hspi1, &OPCODE_READ, 1);
		HAL_SPI_Transmit_IT(&hspi1, &addr, 1);
		HAL_SPI_Receive(&hspi1, &SPI_DATA_RX, 1, HAL_MAX_DELAY);
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, GPIO_PIN_SET);
	}

	else if(device == IO_EXP_2)
	{

	}

	else
		return iError;

	return iError;
}

