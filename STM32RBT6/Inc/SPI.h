/**
  ******************************************************************************
  * @file			SPI.h
  * @brief        	Header for SPI.c file.
  * @version		V1.00
  * @authors		Oehlers, van Renswoude and Schotborgh
  * @date			06-01-2020
  ******************************************************************************
  * @details		This file contains the common defines of the application.
  ******************************************************************************
*/

#ifndef SPI_H_
#define SPI_H_

#define IO_EXP_1 0
#define IO_EXP_2 1

uint8_t SPI_Transmit(uint8_t addr, uint8_t data, uint8_t device);
uint8_t SPI_Receive(uint8_t addr, uint8_t device);

#endif /* SPI_H_ */

