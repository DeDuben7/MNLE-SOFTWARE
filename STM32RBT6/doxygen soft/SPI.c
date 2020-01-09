/**
  ******************************************************************************
  * @file			SPI.c
  * @brief        	Handles SPI communications
  * @version		V1.00
  * @authors		Oehlers, van Renswoude and Schotborgh
  * @date			06-01-2020
  ******************************************************************************
  * @details
  ******************************************************************************
*/
/**
 * @addtogroup	SPI
 * @{
 */
#include "includes.h"

uint8_t SPI_DATA_RX;			/**< Byte for the SPI RX data */
uint8_t OPCODE_WRITE = 0x40;	/**< Opcode for writing data to an IO expander */
uint8_t OPCODE_READ = 0x41;		/**< Opcode for reading data from an IO expander */

/**
  * @fn			uint8_t SPI_Transmit(uint8_t addr, uint8_t data, uint8_t device)
  * @brief		SPI transmit function.
  * @details	This function transmits an SPI message to a specified IO
  * 			expander.
  * @param 		addr	eight bit value with the adress for transmiting the data
  * @param 		data	eight bit value with the data to be transmitted
  * @param 		device	eight bit value with the device that needs to recieve the data
  * @return 	iError
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
  * @fn			uint8_t SPI_Receive(uint8_t addr, uint8_t device)
  * @brief		SPI receive function.
  * @details	This function reads a byte of data from a specified
  * 			IO expander.
  * @param 		addr	eight bit value with the addres for recieving data
  * @param 		device	eight bit value with the device ID for recieving data
  * @return		iError
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
/**
 * @}
 */
