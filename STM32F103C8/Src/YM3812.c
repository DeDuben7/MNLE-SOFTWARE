#include "includes.h"

uint8_t YM_WRITE_Databus(uint8_t chip, uint8_t address, uint8_t data)
{
	uint8_t iError = 0;
	uint8_t i;

	if (chip == 1)
	{
		HAL_GPIO_WritePin(GPIOA,CS_2,GPIO_PIN_SET);
		HAL_GPIO_WritePin(GPIOA,A0,GPIO_PIN_RESET);
		YM_WriteBits(address);
		HAL_GPIO_WritePin(GPIOA,CS_1|WR,GPIO_PIN_RESET);
		for(i=0; i<0x06; i++);							//0x05   1us
		HAL_GPIO_WritePin(GPIOA,CS_1|WR,GPIO_PIN_SET);
		for(i=0; i<0x22; i++);							//0x05   4us
		HAL_GPIO_WritePin(GPIOA,A0,GPIO_PIN_SET);
		YM_WriteBits(data);
		HAL_GPIO_WritePin(GPIOA,CS_1|WR,GPIO_PIN_RESET);
		for(i=0; i<0x06; i++);							//0x05   1us
		HAL_GPIO_WritePin(GPIOA,CS_1|WR,GPIO_PIN_SET);
		for(i=0; i<0xDD; i++);							//0x05   23us
	}

	if (chip == 2)
	{
		HAL_GPIO_WritePin(GPIOA,CS_1,GPIO_PIN_SET);
		HAL_GPIO_WritePin(GPIOA,A0,GPIO_PIN_RESET);
		YM_WriteBits(address);
		HAL_GPIO_WritePin(GPIOA,CS_1|CS_2|WR,GPIO_PIN_RESET);
		for(i=0; i<0x06; i++);							//0x05   1us
		HAL_GPIO_WritePin(GPIOA,CS_1|CS_2|WR,GPIO_PIN_SET);
		for(i=0; i<0x22; i++);							//0x05   4us
		HAL_GPIO_WritePin(GPIOA,A0,GPIO_PIN_SET);
		YM_WriteBits(data);
		HAL_GPIO_WritePin(GPIOA,CS_1|CS_2|WR,GPIO_PIN_RESET);
		for(i=0; i<0x06; i++);							//0x05   1us
		HAL_GPIO_WritePin(GPIOA,CS_1|CS_2|WR,GPIO_PIN_SET);
		for(i=0; i<0xDD; i++);							//0x05   23us
	}

	/*
	if (chip & 4)
	{
		HAL_GPIO_WritePin(GPIOA,A0,GPIO_PIN_RESET);
		YM_WriteBits(address);
		HAL_GPIO_WritePin(GPIOA,CS_3,GPIO_PIN_RESET);
		HAL_GPIO_WritePin(GPIOA,WR,GPIO_PIN_RESET);
		for(i=0; i<0x06; i++);							//0x05   1us
		HAL_GPIO_WritePin(GPIOA,WR,GPIO_PIN_SET);
		HAL_GPIO_WritePin(GPIOA,CS_3,GPIO_PIN_SET);
		for(i=0; i<0x22; i++);							//0x05   4us
		HAL_GPIO_WritePin(GPIOA,A0,GPIO_PIN_SET);
		YM_WriteBits(data);
		HAL_GPIO_WritePin(GPIOA,CS_3,GPIO_PIN_RESET);
		HAL_GPIO_WritePin(GPIOA,WR,GPIO_PIN_RESET);
		for(i=0; i<0x06; i++);							//0x05   1us
		HAL_GPIO_WritePin(GPIOA,WR,GPIO_PIN_SET);
		HAL_GPIO_WritePin(GPIOA,CS_3,GPIO_PIN_SET);
		for(i=0; i<0xDD; i++);							//0x05   23us
	}

	if (chip & 8)
	{
		HAL_GPIO_WritePin(GPIOA,A0,GPIO_PIN_RESET);
		YM_WriteBits(address);
		HAL_GPIO_WritePin(GPIOA,CS_4,GPIO_PIN_RESET);
		HAL_GPIO_WritePin(GPIOA,WR,GPIO_PIN_RESET);
		for(i=0; i<0x06; i++);							//0x05   1us
		HAL_GPIO_WritePin(GPIOA,WR,GPIO_PIN_SET);
		HAL_GPIO_WritePin(GPIOA,CS_4,GPIO_PIN_SET);
		for(i=0; i<0x22; i++);							//0x05   4us
		HAL_GPIO_WritePin(GPIOA,A0,GPIO_PIN_SET);
		YM_WriteBits(data);
		HAL_GPIO_WritePin(GPIOA,CS_4,GPIO_PIN_RESET);
		HAL_GPIO_WritePin(GPIOA,WR,GPIO_PIN_RESET);
		for(i=0; i<0x06; i++);							//0x05   1us
		HAL_GPIO_WritePin(GPIOA,WR,GPIO_PIN_SET);
		HAL_GPIO_WritePin(GPIOA,CS_4,GPIO_PIN_SET);
		for(i=0; i<0xDD; i++);							//0x05   23us
	}
	*/
	else
		iError = NO_CHIP_SELECT;

	return iError;
}

uint8_t YM_WriteBits(uint8_t data)
{
	uint8_t iError = 0;
	uint16_t wridata = 0;

	if(data & 1)
		wridata |= D0;

	if(data & 2)
		wridata |= D1;

	if(data & 4)
		wridata |= D2;

	if(data & 8)
		wridata |= D3;

	if(data & 16)
		wridata |= D4;

	if(data & 32)
		wridata |= D5;

	if(data & 64)
		wridata |= D6;

	if(data & 128)
		wridata |= D7;

	GPIOB->BSRR = wridata | (~wridata << 16U);
	wridata = 0;

	return iError;
}

int F_Number[12] =
{0x157,0x16B,0x181,0x198,0x1B0,0x1CA,0x1E5,0x202,0x220,0x241,0x263,0x287};

//pVCH VCH;
pVCH VCH[9];

uint8_t YM_NOTE_ON(uint8_t MIDI_CHANNEL, uint8_t KEY_NUMBER, uint8_t VELOCITY)
{
	uint8_t iError = 0;
	int i;

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

			YM_WRITE_Databus(1,0xA0+i,VCH[i].F_Numb & 0xFF);
			YM_WRITE_Databus(1,0xB0+i,(0x20 | (VCH[i].Octave << 2)) | ((VCH[i].F_Numb & 0x300) >> 8));
			YM_WRITE_Databus(2,0xA0+i,VCH[i].F_Numb & 0xFF);
			YM_WRITE_Databus(2,0xB0+i,(0x20 | (VCH[i].Octave << 2)) | ((VCH[i].F_Numb & 0x300) >> 8));

			return iError;
		}
	}

	return iError;
}

uint8_t YM_NOTE_OFF(uint8_t KEY_NUMBER, uint8_t VELOCITY)
{
	uint8_t iError = 0;
	int i;

	for(i=0;i<9;i++)
	{
		if(VCH[i].KEY_Numb == KEY_NUMBER && VCH[i].Enable == TRUE)
		{

			YM_WRITE_Databus(1,0xA0+i,0);
			YM_WRITE_Databus(1,0xB0+i,0);
			YM_WRITE_Databus(2,0xA0+i,0);
			YM_WRITE_Databus(2,0xB0+i,0);

			VCH[i].KEY_Numb = 0;
			VCH[i].Octave 	= 0;
			VCH[i].Velocity = 0;
			VCH[i].F_Numb 	= 0;
			VCH[i].Enable 	= FALSE;
		}
	}

	return iError;
}

#include "includes.h"

void YM_RESET()
{
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_8, RESET);
	HAL_Delay(1);
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_8, SET);
	HAL_Delay(1);
}

uint8_t op1[9] = {0,1,2,8,9,10,16,17,18};
uint8_t op2[9] = {3,4,5,11,12,13,19,20,21};

void YM_SET_Def()
{
	int i;

	YM_WRITE_Databus(1,0x01,0x20);
	YM_WRITE_Databus(2,0x01,0x20);

	for(i=0;i<9;i++)
	{
		YM_WRITE_Databus(1,0x20 + op1[i],0x01);
		YM_WRITE_Databus(1,0x40 + op1[i],0x01);
		YM_WRITE_Databus(1,0x60 + op1[i],0x10);
		YM_WRITE_Databus(1,0x80 + op1[i],0x77);
		YM_WRITE_Databus(1,0xE0 + op1[i],0x03);

		YM_WRITE_Databus(1,0x20 + op2[i],0x01);
		YM_WRITE_Databus(1,0x40 + op2[i],0x01);
		YM_WRITE_Databus(1,0x60 + op2[i],0x10);
		YM_WRITE_Databus(1,0x80 + op2[i],0x77);
		YM_WRITE_Databus(1,0xE0 + op2[i],0x03);
	}

	for(i=0;i<9;i++)
	{
		YM_WRITE_Databus(2,0x20 + op1[i],0x01);
		YM_WRITE_Databus(2,0x40 + op1[i],0x01);
		YM_WRITE_Databus(2,0x60 + op1[i],0xF0);
		YM_WRITE_Databus(2,0x80 + op1[i],0x77);
		YM_WRITE_Databus(2,0xE0 + op1[i],0x02);

		YM_WRITE_Databus(2,0x20 + op2[i],0x01);
		YM_WRITE_Databus(2,0x40 + op2[i],0x01);
		YM_WRITE_Databus(2,0x60 + op2[i],0xF0);
		YM_WRITE_Databus(2,0x80 + op2[i],0x77);
		YM_WRITE_Databus(2,0xE0 + op2[i],0x02);
	}
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
