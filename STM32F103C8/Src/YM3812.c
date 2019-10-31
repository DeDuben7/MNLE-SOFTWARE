#include "includes.h"

uint8_t YM_WRITE_Databus(uint8_t chips, uint8_t addr_select, uint8_t data)
{
	uint8_t iError = 0;

	if (chips & 1)
	{
//		HAL_UART_Transmit_IT(&huart2, &addr_select, 1);
//		HAL_Delay(50);
//		HAL_UART_Transmit_IT(&huart2, &data, 1);
//		HAL_Delay(50);
//		HAL_UART_Transmit_IT(&huart2, &Test, 1);
//		HAL_Delay(50);
		HAL_GPIO_WritePin(GPIOA,A0,addr_select);
//		HAL_GPIO_WritePin(GPIOA,CS1,GPIO_PIN_RESET);
		HAL_GPIO_WritePin(GPIOA,WR,GPIO_PIN_RESET);
		YM_WriteBits(data);
		HAL_Delay(1);
//		HAL_GPIO_WritePin(GPIOA,CS1,GPIO_PIN_SET);
		HAL_GPIO_WritePin(GPIOA,WR,GPIO_PIN_SET);
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
	uint16_t wdata, wrdata, wridata;
	uint8_t iError = 0;
	uint8_t i;

//	for(i=0; i<8; i++){
//		if(data & (1<<i))
//		{
//			wdata |= (1 << i);
//		}
//	wrdata = wdata;
//	}
//	HAL_UART_Transmit_IT(&huart2, &wrdata, 2);

	if(data & 1) {
		wridata |= D0;
	}
	if(data & 2){
		wridata |= D1;
	}
	if(data & 4){
		wridata |= D2;
	}
	if(data & 8){
		wridata |= D3;
	}
	if(data & 16){
		wridata |= D4;
	}
	if(data & 32){
		wridata |= D5;
	}
	if(data & 64){
		wridata |= D6;
	}
	if(data & 128){
		wridata |= D7;
	}

	HAL_UART_Transmit_IT(&huart2, &wridata, 2);
	HAL_GPIO_WritePin(GPIOA,wridata,1);
//	wrdata = 0;
	wridata = 0;
//	HAL_GPIO_WritePin(GPIOB,D0,(data & 1));
//	HAL_GPIO_WritePin(GPIOB,D1,(data & 2));
//	HAL_GPIO_WritePin(GPIOB,D2,(data & 4));
//	HAL_GPIO_WritePin(GPIOB,D3,(data & 8));
//	HAL_GPIO_WritePin(GPIOB,D4,(data & 16));
//	HAL_GPIO_WritePin(GPIOB,D5,(data & 32));
//	HAL_GPIO_WritePin(GPIOB,D6,(data & 64));
//	HAL_GPIO_WritePin(GPIOB,D7,(data & 128));

	return iError;
}

/*

uint8_t YM_WRITE_ADDR(uint8_t addr)
{
	uint8_t iError;

	return iError;
}
*/
/*
uint8_t YM_WRITE_DATA(uint8_t data)
{
	uint8_t iError;

	return iError;
}
*/
/*
uint8_t YM_DEF_INIT()
{
	uint8_t iError;

	return iError;
}
*/
int F_Number[12] =
{0x157,0x16B,0x181,0x198,0x1B0,0x1CA,0x1E5,0x202,0x220,0x241,0x263,0x287};

pVCH VCH;

uint8_t YM_NOTE_ON(uint8_t MIDI_CHANNEL, uint8_t KEY_NUMBER, uint8_t VELOCITY)
{

	uint8_t iError = 0;

	VCH.F_Numb = F_Number[KEY_NUMBER % 12];
	VCH.Octave = (KEY_NUMBER/12)-1;
	VCH.Velocity = VELOCITY >> 1;

//	uint8_t Test = 255;
//	uint8_t byte = 1;
//	uint8_t byte1 = VCH.F_Numb & 0xFF;
//	uint8_t byte2 = VCH.Octave;
//	uint8_t byte3 = KEY_NUMBER;
//	uint8_t byte4 = (0x20 | (VCH.Octave << 2)) | (((VCH.F_Numb & 0x300) >> 8));
//	HAL_UART_Transmit_IT(&huart2, &byte1, 1);
//	HAL_Delay(50);
//	HAL_UART_Transmit_IT(&huart2, &byte2, 1);
//	HAL_Delay(50);
//	HAL_UART_Transmit_IT(&huart2, &byte3, 1);
//	HAL_Delay(50);
//	HAL_UART_Transmit_IT(&huart2, &byte4, 1);
//	HAL_Delay(50);
////	HAL_UART_Transmit_IT(&huart2, &byte, 1);
////	HAL_Delay(50);
//	HAL_UART_Transmit_IT(&huart2, &Test, 1);
//	HAL_Delay(50);

	YM_WRITE_Databus(1,0,0xB0);
	YM_WRITE_Databus(1,1,0x00);
	YM_WRITE_Databus(1,0,0xA0);
	YM_WRITE_Databus(1,1,VCH.F_Numb & 0xFF);
	YM_WRITE_Databus(1,0,0xB0);
	YM_WRITE_Databus(1,1,(0x20 | (VCH.Octave << 2)) | ((VCH.F_Numb & 0x300) >> 8));

	return iError;
}

/*
uint8_t YM_CONT_CHANGE(uint8_t data)
{
	uint8_t iError;

	return iError;
}
*/
/*
uint8_t YM_PROG_CHANGE(uint8_t data)
{
	uint8_t iError;

	return iError;
}
*/
/*
uint8_t YM_PITCH(uint8_t pitch)
{
	uint8_t iError;

	return iError;
}
*/
