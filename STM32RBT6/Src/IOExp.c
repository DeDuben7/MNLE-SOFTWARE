/*
 * IOEXP.c
 *
 *  Created on: 2 dec. 2019
 *      Author: Brian & Ruben
 */
#include "includes.h"

uint8_t IODIR_A		=	0x00;
uint8_t IODIR_B		=	0x01;
uint8_t GPINTEN_A 	=	0x04;
uint8_t GPINTEN_B 	=	0x05;
uint8_t IOCON_A		=	0x0A;
uint8_t IOCON_B		=	0x0B;
uint8_t GPPU_A		=	0x0C;
uint8_t GPPU_B		=	0x0D;
uint8_t INTCAP_A 	=	0x10;
uint8_t INTCAP_B 	=	0x11;
uint8_t GPIO_A		=	0x12;
uint8_t GPIO_B		=	0x13;

void UI_RESET(void)
{
	// reset the IO expanders
	HAL_GPIO_WritePin(GPIOB,GPIO_PIN_13,GPIO_PIN_RESET);
	HAL_Delay(100);
	HAL_GPIO_WritePin(GPIOB,GPIO_PIN_13,GPIO_PIN_SET);
}

void UI_INIT(void)
{
	UI_RESET();

	//init chip one port A
	SPI_Transmit(IOCON_A	,0x20, IO_EXP_1); // disable sequential mode, int polarity active high
	SPI_Transmit(IODIR_A	,0xFF, IO_EXP_1); // configure all pins as input
	SPI_Transmit(GPINTEN_A	,0xFF, IO_EXP_1); // configure all pins for interrupt on change
	SPI_Transmit(GPPU_A		,0xFF, IO_EXP_1); // configure all pins to have a pull up resistor

	//init chip one port B
	SPI_Transmit(IOCON_B	,0x20, IO_EXP_1); // disable sequential mode, int polarity active high
	SPI_Transmit(IODIR_B	,0xFF, IO_EXP_1); // configure all pins as input
	SPI_Transmit(GPINTEN_B	,0xFF, IO_EXP_1); // configure all pins for interrupt on change
	SPI_Transmit(GPPU_B		,0xFF, IO_EXP_1); // configure all pins to have a pull up resistor

	//init chip two port A
	SPI_Transmit(IOCON_A	,0x20, IO_EXP_2); // disable sequential mode, int polarity active high
	SPI_Transmit(IODIR_A	,0xFF, IO_EXP_2); // configure all pins as input
	SPI_Transmit(GPINTEN_A	,0xFF, IO_EXP_2); // configure all pins for interrupt on change
	SPI_Transmit(GPPU_A		,0xFF, IO_EXP_2); // configure all pins to have a pull up resistor


	//init chip two port B
	SPI_Transmit(IOCON_B	,0x20, IO_EXP_2); // disable sequential mode, int polarity active high
	SPI_Transmit(IODIR_B	,0xFF, IO_EXP_2); // configure all pins as input
	SPI_Transmit(GPINTEN_B	,0xFF, IO_EXP_2); // configure all pins for interrupt on change
	SPI_Transmit(GPPU_B		,0xFF, IO_EXP_2); // configure all pins to have a pull up resistor
}

uint8_t UI_PROC()
{
	uint8_t iError;



	return iError;
}
