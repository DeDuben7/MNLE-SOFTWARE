
#include "includes.h"

uint8_t YM_WRITE_Databus(uint8_t chips, uint8_t addr_select, uint8_t data)
{
	uint8_t iError = 0;

	if (chips & 1)
	{
		HAL_GPIO_WritePin(GPIOB,A0,addr_select);
//		HAL_Delay(1);
		HAL_GPIO_WritePin(GPIOA,CS1,GPIO_PIN_RESET);
		HAL_GPIO_WritePin(GPIOB,WR,GPIO_PIN_RESET);
//		HAL_Delay(1);
		YM_WriteBits(data);
		//HAL_Delay(1);
		HAL_GPIO_WritePin(GPIOA,CS1,GPIO_PIN_SET);
		HAL_GPIO_WritePin(GPIOB,WR,GPIO_PIN_SET);
		//HAL_Delay(1);
	}
	/*else if (chips & 2)
	{
		HAL_GPIO_WritePin(GPIOB,A0,addr_select);
		HAL_GPIO_WritePin(GPIOA,CS2,GPIO_PIN_RESET);
		HAL_GPIO_WritePin(GPIOB,WR,GPIO_PIN_RESET);
		YM_WriteBits(data);
		HAL_GPIO_WritePin(GPIOA,CS2,GPIO_PIN_SET);
		HAL_GPIO_WritePin(GPIOB,WR,GPIO_PIN_SET);
	}
	else if (chips & 4)
	{
		HAL_GPIO_WritePin(GPIOB,A0,addr_select);
		HAL_GPIO_WritePin(GPIOA,CS3,GPIO_PIN_RESET);
		HAL_GPIO_WritePin(GPIOB,WR,GPIO_PIN_RESET);
		YM_WriteBits(data);
		HAL_GPIO_WritePin(GPIOA,CS3,GPIO_PIN_SET);
		HAL_GPIO_WritePin(GPIOB,WR,GPIO_PIN_SET);
	}
	else if (chips & 8)
	{
		HAL_GPIO_WritePin(GPIOB,A0,addr_select);
		HAL_GPIO_WritePin(GPIOA,CS4,GPIO_PIN_RESET);
		HAL_GPIO_WritePin(GPIOB,WR,GPIO_PIN_RESET);
		YM_WriteBits(data);
		HAL_GPIO_WritePin(GPIOA,CS4,GPIO_PIN_SET);
		HAL_GPIO_WritePin(GPIOB,WR,GPIO_PIN_SET);
	}*/
	else iError = NO_CHIP_SELECT;

	return iError;
}

uint8_t YM_WriteBits(uint8_t data)
{
	uint8_t iError = 0;

	HAL_GPIO_WritePin(GPIOC,D0,(data & 1));
	HAL_GPIO_WritePin(GPIOC,D1,(data & 2));
	HAL_GPIO_WritePin(GPIOA,D2,(data & 4));
	HAL_GPIO_WritePin(GPIOB,D3,(data & 8));
	HAL_GPIO_WritePin(GPIOB,D4,(data & 16));
	HAL_GPIO_WritePin(GPIOB,D5,(data & 32));
	HAL_GPIO_WritePin(GPIOB,D6,(data & 64));
	HAL_GPIO_WritePin(GPIOB,D7,(data & 128));

	return iError;
}

/*

uint8_t YM_WRITE_ADDR(uint8_t addr)
{
	uint8_t iError;

	return iError;
}

uint8_t YM_WRITE_DATA(uint8_t data)
{
	uint8_t iError;

	return iError;
}

uint8_t YM_DEF_INIT()
{
	uint8_t iError;

	return iError;
}

uint8_t YM_NOTE_ON(uint8_t status)
{
	uint8_t iError;

	return iError;
}

uint8_t YM_CONT_CHANGE(uint8_t data)
{
	uint8_t iError;

	return iError;
}

uint8_t YM_PROG_CHANGE(uint8_t data)
{
	uint8_t iError;

	return iError;
}

uint8_t YM_PITCH(uint8_t pitch)
{
	uint8_t iError;

	return iError;
}
*/
