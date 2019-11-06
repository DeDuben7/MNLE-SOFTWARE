#include "includes.h"

uint8_t YM_WRITE_Databus(uint8_t chips, uint8_t addr_select, uint8_t data)
{
	uint8_t iError = 0;
	uint8_t i;

	if (chips & 1)
	{

		HAL_GPIO_WritePin(GPIOA,A0,addr_select);
		for(i=0; i<0x07; i++);							//0x05
//		HAL_GPIO_WritePin(GPIOA,CS1,GPIO_PIN_RESET);
		HAL_GPIO_WritePin(GPIOA,WR,GPIO_PIN_RESET);
		YM_WriteBits(data);
		for(i=0; i<0x50; i++);							//0x50
//		HAL_Delay(1);
//		HAL_GPIO_WritePin(GPIOA,CS1,GPIO_PIN_SET);
		HAL_GPIO_WritePin(GPIOA,WR,GPIO_PIN_SET);
		for(i=0; i<0x07; i++);
		HAL_GPIO_WritePin(GPIOA,A0,!addr_select);

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
	uint16_t wridata = 0;

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

	GPIOB->BSRR = wridata | (~wridata << 16U);
	wridata = 0;

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

//pVCH VCH;
pVCH VCH[9];

uint8_t KP;


uint8_t YM_NOTE_ON(uint8_t MIDI_CHANNEL, uint8_t KEY_NUMBER, uint8_t VELOCITY)
{
	uint8_t iError = 0;
	int i;
	KP = KEY_NUMBER;

//	VCH.F_Numb = F_Number[KEY_NUMBER % 12];
//	VCH.Octave = (KEY_NUMBER/12)-1;
//	VCH.Velocity = VELOCITY >> 1;
//
//	YM_WRITE_Databus(1,0,0xB0);
//	YM_WRITE_Databus(1,1,0x00);
//	YM_WRITE_Databus(1,0,0xA0);
//	YM_WRITE_Databus(1,1,VCH.F_Numb & 0xFF);
//	YM_WRITE_Databus(1,0,0xB0);
//	YM_WRITE_Databus(1,1,(0x20 | (VCH.Octave << 2)) | ((VCH.F_Numb & 0x300) >> 8));

	for(i=0;i<9;i++)
	{
		if(VCH[i].Enable == FALSE || VCH[i].KEY_Numb == KEY_NUMBER)
		{
			VCH[i].Enable 	= TRUE;
			VCH[i].KEY_Numb = KEY_NUMBER;
			VCH[i].F_Numb 	= F_Number[KEY_NUMBER % 12];
			VCH[i].Octave 	= (KEY_NUMBER/12)-1;
			VCH[i].Velocity = VELOCITY >> 1;
			VCH[i].i_tel  	= i;

			YM_WRITE_Databus(1,0,0xA0+i);
			YM_WRITE_Databus(1,1,VCH[i].F_Numb & 0xFF);
			YM_WRITE_Databus(1,0,0xB0+i);
			YM_WRITE_Databus(1,1,(0x20 | (VCH[i].Octave << 2)) | ((VCH[i].F_Numb & 0x300) >> 8));
			return iError;
		}
	}

	return iError;
}

uint8_t YM_NOTE_OFF(uint8_t KEY_NUMBER, uint8_t VELOCITY)
{
	uint8_t iError = 0;
	int i;

//	if(KP == KEY_NUMBER)
//	{
//		HAL_UART_Transmit_IT(&huart2, &KEY_NUMBER, 1);
//
//		YM_WRITE_Databus(1,0,0xB0);
//		YM_WRITE_Databus(1,1,0x00);
//	}


	for(i=0;i<9;i++)
	{
		if(VCH[i].KEY_Numb == KEY_NUMBER && VCH[i].Enable == TRUE)
		{
			YM_WRITE_Databus(1,0,0xA0+i);
			YM_WRITE_Databus(1,1,0x00);
			YM_WRITE_Databus(1,0,0xB0+i);
			YM_WRITE_Databus(1,1,0x00);
			VCH[i].KEY_Numb = 0;
			VCH[i].Octave 	= 0;
			VCH[i].Velocity = 0;
			VCH[i].F_Numb 	= 0;
			VCH[i].Enable 	= FALSE;
		}
	}

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

//uint8_t YM_WriteBits(uint8_t data)
//{
//	uint8_t iError = 0;
//	uint8_t i = 0;
//
//	uint16_t W_Data = 0;
//
//	for(i=0; i<7; i++)
//	{
//		if(data & 1<<i){
//			W_Data |= D0 << i;
//		}
//		if(i==6){
//			if(data & 128){
//				W_Data |= D7;
//			}
//		}
//	}
//
//	GPIOB->BSRR = W_Data | (~W_Data << 16U);
//	W_Data = 0;
//return iError;
//}


//uint8_t YM_NOTE_ON_OFF(uint8_t MIDI_CHANNEL, uint8_t KEY_NUMBER, uint8_t VELOCITY, uint8_t STATE)
//{
//	uint8_t iError = 0;
//	uint8_t i;
//	for(i=0;i<9;i++)
//	{
//		if((VCH[i].Enable == FALSE || VCH[i].KEY_Numb == KEY_NUMBER) && STATE == ON)
//		{
//			VCH[i].Enable 	= TRUE;
//			VCH[i].KEY_Numb = KEY_NUMBER;
//			VCH[i].F_Numb 	= F_Number[KEY_NUMBER % 12];
//			VCH[i].Octave 	= (KEY_NUMBER/12)-1;
//			VCH[i].Velocity = VELOCITY >> 1;
//			VCH[i].i_tel  	= i;
//
//			YM_NOTE_ON(VCH[i].Octave, VCH[i].F_Numb, VCH[i].Velocity, VCH[i].i_tel);
//		}
//		else if((VCH[i].Enable == TRUE && VCH[i].KEY_Numb == KEY_NUMBER) && STATE == OFF)
//		{
//			VCH[i].i_tel  	= i;
//			YM_NOTE_OFF(VCH[i].i_tel);
//		}
//		else
//		{
//			return iError;
//		}
//	}
//	return iError;
//}
//
//uint8_t YM_NOTE_ON(uint8_t OCTAVE, uint16_t F_NUMBER, uint8_t VELOCITY, uint8_t i)
//{
//	uint8_t iError = 0;
//
//	YM_WRITE_Databus(1,0,0xB0);
//	YM_WRITE_Databus(1,1,0x00);
//	YM_WRITE_Databus(1,0,0xA0);
//	YM_WRITE_Databus(1,1,F_NUMBER & 0xFF);
//	YM_WRITE_Databus(1,0,0xB0);
//	YM_WRITE_Databus(1,1,(0x20 | (OCTAVE << 2)) | ((F_NUMBER & 0x300) >> 8));
//
//	return iError;
//}
//
//uint8_t YM_NOTE_OFF(uint8_t i)
//{
//	uint8_t iError = 0;
//
//	YM_WRITE_Databus(1,0,0xA0+i);
//	YM_WRITE_Databus(1,1,0x00);
//	YM_WRITE_Databus(1,0,0xB0+i);
//	YM_WRITE_Databus(1,1,0x00);
//	VCH[i].KEY_Numb = 0;
//	VCH[i].Octave 	= 0;
//	VCH[i].Velocity = 0;
//	VCH[i].F_Numb 	= 0;
//	VCH[i].Enable 	= FALSE;
//
//	return iError;
//}
