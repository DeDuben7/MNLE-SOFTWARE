/*
* Filename      : YM3812.c
* Version       : V1.00
* Programmer(s) : Schotburgh, Oehlers en van Renswoude
*/

#include "includes.h"

/**
  * @brief Function for writing addresses and data to the YM3812 chips
  * @retval iError
  */
uint8_t YM_WRITE_Databus(uint8_t chip, uint8_t address, uint8_t data)
{
	uint8_t iError = 0;
	uint8_t i;

	if (chip == 1) // Check if chip 1 is selected, then write the address and data to this chip
	{
		HAL_GPIO_WritePin(GPIOA,CS_2,GPIO_PIN_SET);
		HAL_GPIO_WritePin(GPIOA,A0,GPIO_PIN_RESET);
		YM_WriteBits(address);
		HAL_GPIO_WritePin(GPIOA,CS_1|WR,GPIO_PIN_RESET);
		for(i=0; i<0x06; i++);							//0x05   1us
		HAL_GPIO_WritePin(GPIOA,CS_1|WR,GPIO_PIN_SET);
		for(i=0; i<0x22; i++);							//0x05   4us hold address time
		HAL_GPIO_WritePin(GPIOA,A0,GPIO_PIN_SET);
		YM_WriteBits(data);
		HAL_GPIO_WritePin(GPIOA,CS_1|WR,GPIO_PIN_RESET);
		for(i=0; i<0x06; i++);							//0x05   1us
		HAL_GPIO_WritePin(GPIOA,CS_1|WR,GPIO_PIN_SET);
		for(i=0; i<0xDD; i++);							//0x05   23us hold data time
	}

	if (chip == 2) // Check if chip 2 is selected, then write the address and data to this chip
	{
		HAL_GPIO_WritePin(GPIOA,CS_1,GPIO_PIN_SET);
		HAL_GPIO_WritePin(GPIOA,A0,GPIO_PIN_RESET);
		YM_WriteBits(address);
		HAL_GPIO_WritePin(GPIOA,CS_2|WR,GPIO_PIN_RESET);
		for(i=0; i<0x06; i++);							//0x05   1us
		HAL_GPIO_WritePin(GPIOA,CS_2|WR,GPIO_PIN_SET);
		for(i=0; i<0x22; i++);							//0x05   4us hold address time
		HAL_GPIO_WritePin(GPIOA,A0,GPIO_PIN_SET);
		YM_WriteBits(data);
		HAL_GPIO_WritePin(GPIOA,CS_2|WR,GPIO_PIN_RESET);
		for(i=0; i<0x06; i++);							//0x05   1us
		HAL_GPIO_WritePin(GPIOA,CS_2|WR,GPIO_PIN_SET);
		for(i=0; i<0xDD; i++);							//0x05   23us hold data time
	}

	/*
	if (chip & 4) // Check if chip 3 is selected, then write the address and data to this chip
	{
		HAL_GPIO_WritePin(GPIOA,A0,GPIO_PIN_RESET);
		YM_WriteBits(address);
		HAL_GPIO_WritePin(GPIOA,CS_3,GPIO_PIN_RESET);
		HAL_GPIO_WritePin(GPIOA,WR,GPIO_PIN_RESET);
		for(i=0; i<0x06; i++);							//0x05   1us
		HAL_GPIO_WritePin(GPIOA,WR,GPIO_PIN_SET);
		HAL_GPIO_WritePin(GPIOA,CS_3,GPIO_PIN_SET);
		for(i=0; i<0x22; i++);							//0x05   4us hold address time
		HAL_GPIO_WritePin(GPIOA,A0,GPIO_PIN_SET);
		YM_WriteBits(data);
		HAL_GPIO_WritePin(GPIOA,CS_3,GPIO_PIN_RESET);
		HAL_GPIO_WritePin(GPIOA,WR,GPIO_PIN_RESET);
		for(i=0; i<0x06; i++);							//0x05   1us
		HAL_GPIO_WritePin(GPIOA,WR,GPIO_PIN_SET);
		HAL_GPIO_WritePin(GPIOA,CS_3,GPIO_PIN_SET);
		for(i=0; i<0xDD; i++);							//0x05   23us hold data time
	}

	if (chip & 8) // Check if chip 4 is selected, then write the address and data to this chip
	{
		HAL_GPIO_WritePin(GPIOA,A0,GPIO_PIN_RESET);
		YM_WriteBits(address);
		HAL_GPIO_WritePin(GPIOA,CS_4,GPIO_PIN_RESET);
		HAL_GPIO_WritePin(GPIOA,WR,GPIO_PIN_RESET);
		for(i=0; i<0x06; i++);							//0x05   1us
		HAL_GPIO_WritePin(GPIOA,WR,GPIO_PIN_SET);
		HAL_GPIO_WritePin(GPIOA,CS_4,GPIO_PIN_SET);
		for(i=0; i<0x22; i++);							//0x05   4us hold address time
		HAL_GPIO_WritePin(GPIOA,A0,GPIO_PIN_SET);
		YM_WriteBits(data);
		HAL_GPIO_WritePin(GPIOA,CS_4,GPIO_PIN_RESET);
		HAL_GPIO_WritePin(GPIOA,WR,GPIO_PIN_RESET);
		for(i=0; i<0x06; i++);							//0x05   1us
		HAL_GPIO_WritePin(GPIOA,WR,GPIO_PIN_SET);
		HAL_GPIO_WritePin(GPIOA,CS_4,GPIO_PIN_SET);
		for(i=0; i<0xDD; i++);							//0x05   23us hold data time
	}
	*/
	else
		iError = NO_CHIP_SELECT;

	return iError;
}

/**
  * @brief Function for writing 8 bits of data to the databus of the YM3812 at the same time
  * @retval iError
  */
uint8_t YM_WriteBits(uint8_t data)
{
	uint8_t iError = 0;
	uint16_t wridata = 0;

	// Check which pins need to be set
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

	// Write the byte to the databus
	GPIOB->BSRR = wridata | (~wridata << 16U);
	wridata = 0;

	return iError;
}

// Create 9 voice channel structs for storing the data of each voice channel
pVCH VCH[9];

/**
  * @brief Function for setting notes on different voice channels in the YM3812
  * @retval iError
  */
uint8_t YM_NOTE_ON(uint8_t VCH_Num)
{
	uint8_t iError = 0;

	YM_WRITE_Databus(1,0xA0+VCH_Num,VCH[VCH_Num].F_Numb & 0xFF); // Set the lower byte of the frequency for chip 1
	YM_WRITE_Databus(1,0xB0+VCH_Num,(0x20 | (VCH[VCH_Num].Octave << 2)) | ((VCH[VCH_Num].F_Numb & 0x300) >> 8)); // Set the two most significant bits of the frequency, the octave and the note on for chip 2
	YM_WRITE_Databus(2,0xA0+VCH_Num,VCH[VCH_Num].F_Numb & 0xFF); // Set the lower byte of the frequency for chip 1
	YM_WRITE_Databus(2,0xB0+VCH_Num,(0x20 | (VCH[VCH_Num].Octave << 2)) | ((VCH[VCH_Num].F_Numb & 0x300) >> 8)); // Set the two most significant bits of the frequency, the octave and the note on for chip 2

	return iError;
}

/**
  * @brief Function for setting notes off different voice channels in the YM3812
  * @retval iError
  */
uint8_t YM_NOTE_OFF(uint8_t KEY_NUMBER, uint8_t VELOCITY)
{
	uint8_t iError = 0;
	int i;

	for(i=0;i<9;i++) // Check which voice channel needs to be set off
	{
		if(VCH[i].KEY_Numb == KEY_NUMBER && VCH[i].Enable == TRUE)
		{
			// Disable the voice channel on all the chips
			YM_WRITE_Databus(1,0xA0+i,0);
			YM_WRITE_Databus(1,0xB0+i,0);
			YM_WRITE_Databus(2,0xA0+i,0);
			YM_WRITE_Databus(2,0xB0+i,0);

			// Reset the voice channel struct
			VCH[i].KEY_Numb = 0;
			VCH[i].Octave 	= 0;
			VCH[i].Velocity = 0;
			VCH[i].F_Numb 	= 0;
			VCH[i].Enable 	= FALSE;
		}
	}

	return iError;
}

// Array with F-numbers, these represent the notes in one octave
int F_Number[16] = {0x134,0x146,0x15A,0x16E,0x184,0x19B,0x1B4,0x1CE,0x1E9,0x206,0x225,0x246,0x268,0x28D,0x2B4,0x2DD};

uint8_t YM_PITCH(uint8_t KeyNumber, uint8_t Velocity)
{
	uint8_t iError = 0;
	uint8_t VCH_Num;
	uint8_t ArrayNumb = (KeyNumber % 12) + 2;

	if(KeyNumber == 0)
	{
		// Alleen pitch change
		for(VCH_Num=0;VCH_Num<9;VCH_Num++)
		{
			if(VCH[VCH_Num].Enable == TRUE)
			{
				ArrayNumb = (VCH[VCH_Num].KEY_Numb % 12) + 2;

				if(YM_PitchValue < 64) // benden naar beneden
				{
					VCH[VCH_Num].F_Numb = F_Number[ArrayNumb] - ((64 - YM_PitchValue) * (F_Number[ArrayNumb] - F_Number[ArrayNumb - 2]))/63;
				}

				else // benden naar boven
				{
					VCH[VCH_Num].F_Numb = F_Number[ArrayNumb] + ((YM_PitchValue - 64) * (F_Number[ArrayNumb + 2] - F_Number[ArrayNumb]))/63;
				}

				YM_NOTE_ON(VCH_Num);
			}
		}
	}

	else
	{
		// Nieuwe noot
		for(VCH_Num=0;VCH_Num<9;VCH_Num++) // Check for each voice channel if it is in use
		{
			if(VCH[VCH_Num].Enable == FALSE || VCH[VCH_Num].KEY_Numb == KeyNumber) // If the voice channel is not used
			{
				// Set the variables of the voice channel
				VCH[VCH_Num].Enable 	= TRUE;
				VCH[VCH_Num].KEY_Numb 	= KeyNumber;
				VCH[VCH_Num].Octave 	= (KeyNumber/12)-1;
				VCH[VCH_Num].Velocity 	= Velocity >> 1;

				if(YM_PitchValue < 64) // benden naar beneden
				{
					VCH[VCH_Num].F_Numb = F_Number[ArrayNumb] - ((64 - YM_PitchValue) * (F_Number[ArrayNumb] - F_Number[ArrayNumb - 2]))/63;
				}

				else // benden naar boven
				{
					VCH[VCH_Num].F_Numb = F_Number[ArrayNumb] + ((YM_PitchValue - 64) * (F_Number[ArrayNumb + 2] - F_Number[ArrayNumb]))/63;
				}

				YM_NOTE_ON(VCH_Num);

				return iError;
			}
		}
	}

	return iError;
}

/**
  * @brief Function for resetting the YM3812
  * @retval iError
  */
void YM_RESET()
{
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_8, RESET);
	HAL_Delay(1);
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_8, SET);
	HAL_Delay(1);
}

// Arrays with the different numbers for the operator addresses
uint8_t op1[9] = {0,1,2,8,9,10,16,17,18};
uint8_t op2[9] = {3,4,5,11,12,13,19,20,21};

/**
  * @brief Function for setting some default settings in the YM3812
  * @retval iError
  */
void YM_SET_Def()
{
	int i; // Counter variable

	YM_WRITE_Databus(1,0x01,0x20); // Enable multiple waveforms on chip 1
	YM_WRITE_Databus(2,0x01,0x20); // Enable multiple waveforms on chip 2

	// Set the default settings for chip 1
	for(i=0;i<9;i++)
	{
		YM_WRITE_Databus(1,0x20 + op1[i],0x01); // set the multiplier to 1
		YM_WRITE_Databus(1,0x40 + op1[i],0x00); // set the volume to the loudest volume possible
		YM_WRITE_Databus(1,0x60 + op1[i],0xF0); // Set the attack to fast and the decay to slow
		YM_WRITE_Databus(1,0x80 + op1[i],0x77); // Set the sustain and release to medium
		YM_WRITE_Databus(1,0xE0 + op1[i],0x03); // Set the waveform to a kind of sawtooth wave

		YM_WRITE_Databus(1,0x20 + op2[i],0x01); // set the multiplier to 1
		YM_WRITE_Databus(1,0x40 + op2[i],0x00); // set the volume to the loudest volume possible
		YM_WRITE_Databus(1,0x60 + op2[i],0xF0); // Set the attack to fast and the decay to slow
		YM_WRITE_Databus(1,0x80 + op2[i],0x77); // Set the sustain and release to medium
		YM_WRITE_Databus(1,0xE0 + op2[i],0x03); // Set the waveform to a kind of sawtooth wave
	}

	// Set the default settings for chip 2
	for(i=0;i<9;i++)
	{
		YM_WRITE_Databus(2,0x20 + op1[i],0x01); // set the multiplier to 1
		YM_WRITE_Databus(2,0x40 + op1[i],0x00); // set the volume to the loudest volume possible
		YM_WRITE_Databus(2,0x60 + op1[i],0xF0); // Set the attack to fast and the decay to slow
		YM_WRITE_Databus(2,0x80 + op1[i],0x77); // Set the sustain and release to medium
		YM_WRITE_Databus(2,0xE0 + op1[i],0x00); // Set the waveform to a sine wave that is made fully positive

		YM_WRITE_Databus(2,0x20 + op2[i],0x01); // set the multiplier to 1
		YM_WRITE_Databus(2,0x40 + op2[i],0x00); // set the volume to the loudest volume possible
		YM_WRITE_Databus(2,0x60 + op2[i],0xF0); // Set the attack to fast and the decay to slow
		YM_WRITE_Databus(2,0x80 + op2[i],0x77); // Set the sustain and release to medium
		YM_WRITE_Databus(2,0xE0 + op2[i],0x00); // Set the waveform to a sine wave that is made fully positive
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
