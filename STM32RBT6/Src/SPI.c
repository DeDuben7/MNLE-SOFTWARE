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

uint8_t SPI_DATA_RX;			/**< Byte for the SPI RX data */
uint8_t OPCODE_WRITE = 0x40;	/**< Opcode for writing data to an IO expander */
uint8_t OPCODE_READ = 0x41;		/**< Opcode for reading data from an IO expander */

/**
  ******************************************************************************
  * @brief			SPI transmit function.
  * @headerfile 	includes.h ""
  * @param 			8 bit address variable
  * @param 			8 bit data variable
  * @param 			8 bit device variable
  * @val			None
  * @return None	iError
  ******************************************************************************
  * @details		This function transmits an SPI message to a specified IO
  * 				expander.
  ******************************************************************************
  */
uint8_t SPI_Transmit(uint8_t addr, uint8_t data, uint8_t device)
{
	uint8_t iError = 0;

	if(device == IO_EXP_1)
	{
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, GPIO_PIN_RESET);
		HAL_SPI_Transmit_IT(&hspi2, &OPCODE_WRITE, 1);
		HAL_SPI_Transmit_IT(&hspi2, &addr, 1);
		HAL_SPI_Transmit_IT(&hspi2, &data, 1);
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
  * @brief			SPI receive function.
  * @headerfile 	includes.h ""
  * @param 			8 bit address variable
  * @param 			8 bit device variable
  * @val			None
  * @return			iError
  ******************************************************************************
  * @details		This function reads a byte of data from a specified
  * 				IO expander.
  ******************************************************************************
  */
uint8_t SPI_Receive(uint8_t addr, uint8_t device)
{
	uint8_t iError = 0;

	if(device == IO_EXP_1)
	{
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, GPIO_PIN_RESET);
		HAL_SPI_Transmit_IT(&hspi2, &OPCODE_READ, 1);
		HAL_SPI_Transmit_IT(&hspi2, &addr, 1);
		HAL_SPI_Receive(&hspi2, &SPI_DATA_RX, 1, HAL_MAX_DELAY);
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, GPIO_PIN_SET);
	}

	else if(device == IO_EXP_2)
	{

	}

	else
		return iError;

	return iError;
}

