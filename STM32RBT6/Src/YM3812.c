/**
 ******************************************************************************
 * @file		YM3812.c
 * @brief       Program using YM3812
 * @version		V 3.0
 * @authors		Schotborgh, Oehlers en van Renswoude
 * @date		6-1-2020
 ******************************************************************************
 * @details		In this code functions will be written to program YM3812 chip.
 * 				First the code to for the basic programming to write data(in bits) is written.
 * 				Following are the different functions will be found here.
 ******************************************************************************
 */
/**
 * @addtogroup	YM
 * @{
 */


#include "includes.h"

/**
 * @fn		uint8_t YM_WRITE_Databus(uint8_t chip, uint8_t address, uint8_t data)
 * @brief 	Function to time the writing of the addresses and data to the YM3812 chip 1,2,3 and 4.
 * @details In this function data can be send to the 4 different YM3812's. With the parameter 'chip' can be selected
 * 			which chip can be programmed. If the chip is selected, first the address from parameter 'address' will be send to
 * 			the YM3812 using the function YM_WriteBits. Following will the data from the parameter 'data' be send to the YM3812.
 * 			If the parameter chip is out of bound. the error 'NO_CHIP_SELECT' will be returned.
 * @param  	chip	Wich chip is selected
 * @param 	address	What is the address for the incoming data
 * @param 	data	What is the data to write
 * @var 	i
 * @return 	iError
 *
 */
uint8_t YM_WRITE_Databus(uint8_t chip, uint8_t address, uint8_t data)
{
	uint8_t iError = 0;
	uint8_t i;

	if (chip == 1) // Check if chip 1 is selected, then write the address and data to this chip
	{

		HAL_GPIO_WritePin(GPIOC,YM_A0,GPIO_PIN_RESET);
		YM_WriteBits(address);
		HAL_GPIO_WritePin(GPIOA,YM_CS_1,GPIO_PIN_RESET);
		HAL_GPIO_WritePin(GPIOC,YM_WR,GPIO_PIN_RESET);
		for(i=0; i<0x06; i++);							//0x05   1us
		HAL_GPIO_WritePin(GPIOA,YM_CS_1,GPIO_PIN_SET);
		HAL_GPIO_WritePin(GPIOC,YM_WR,GPIO_PIN_SET);
		for(i=0; i<0x22; i++);							//0x05   4us hold address time
		HAL_GPIO_WritePin(GPIOC,YM_A0,GPIO_PIN_SET);
		YM_WriteBits(data);
		HAL_GPIO_WritePin(GPIOA,YM_CS_1,GPIO_PIN_RESET);
		HAL_GPIO_WritePin(GPIOC,YM_WR,GPIO_PIN_RESET);
		for(i=0; i<0x06; i++);							//0x05   1us
		HAL_GPIO_WritePin(GPIOA,YM_CS_1,GPIO_PIN_SET);
		HAL_GPIO_WritePin(GPIOC,YM_WR,GPIO_PIN_SET);
		for(i=0; i<0xDD; i++);							//0x05   23us hold data time
	}

	if (chip == 2) // Check if chip 2 is selected, then write the address and data to this chip
	{
		HAL_GPIO_WritePin(GPIOC,YM_A0,GPIO_PIN_RESET);
		YM_WriteBits(address);
		HAL_GPIO_WritePin(GPIOC,YM_CS_2|YM_WR,GPIO_PIN_RESET);
		for(i=0; i<0x06; i++);							//0x05   1us
		HAL_GPIO_WritePin(GPIOC,YM_CS_2|YM_WR,GPIO_PIN_SET);
		for(i=0; i<0x22; i++);							//0x05   4us hold address time
		HAL_GPIO_WritePin(GPIOC,YM_A0,GPIO_PIN_SET);
		YM_WriteBits(data);
		HAL_GPIO_WritePin(GPIOC,YM_CS_2|YM_WR,GPIO_PIN_RESET);
		for(i=0; i<0x06; i++);							//0x05   1us
		HAL_GPIO_WritePin(GPIOC,YM_CS_2|YM_WR,GPIO_PIN_SET);
		for(i=0; i<0xDD; i++);							//0x05   23us hold data time
	}


	if (chip == 3) // Check if chip 3 is selected, then write the address and data to this chip
	{
		HAL_GPIO_WritePin(GPIOC,YM_A0,GPIO_PIN_RESET);
		YM_WriteBits(address);
		HAL_GPIO_WritePin(GPIOC,YM_CS_3|YM_WR,GPIO_PIN_RESET);
		for(i=0; i<0x06; i++);							//0x05   1us
		HAL_GPIO_WritePin(GPIOC,YM_CS_3|YM_WR,GPIO_PIN_SET);
		for(i=0; i<0x22; i++);							//0x05   4us hold address time
		HAL_GPIO_WritePin(GPIOC,YM_A0,GPIO_PIN_SET);
		YM_WriteBits(data);
		HAL_GPIO_WritePin(GPIOC,YM_CS_3|YM_WR,GPIO_PIN_RESET);
		for(i=0; i<0x06; i++);							//0x05   1us
		HAL_GPIO_WritePin(GPIOC,YM_CS_3|YM_WR,GPIO_PIN_SET);
		for(i=0; i<0xDD; i++);							//0x05   23us hold data time
	}

	if (chip == 4) // Check if chip 4 is selected, then write the address and data to this chip
	{
		HAL_GPIO_WritePin(GPIOC,YM_A0,GPIO_PIN_RESET);
		YM_WriteBits(address);
		HAL_GPIO_WritePin(GPIOC,YM_CS_4|YM_WR,GPIO_PIN_RESET);
		for(i=0; i<0x06; i++);							//0x05   1us
		HAL_GPIO_WritePin(GPIOC,YM_CS_4|YM_WR,GPIO_PIN_SET);
		for(i=0; i<0x22; i++);							//0x05   4us hold address time
		HAL_GPIO_WritePin(GPIOC,YM_A0,GPIO_PIN_SET);
		YM_WriteBits(data);
		HAL_GPIO_WritePin(GPIOC,YM_CS_4|YM_WR,GPIO_PIN_RESET);
		for(i=0; i<0x06; i++);							//0x05   1us
		HAL_GPIO_WritePin(GPIOC,YM_CS_4|YM_WR,GPIO_PIN_SET);
		for(i=0; i<0xDD; i++);							//0x05   23us hold data time
	}

	else
		iError = NO_CHIP_SELECT;

	return iError;
}

/**
 * @fn		uint8_t YM_WriteBits(uint8_t data)
 * @brief 	Function for writing bits to the YM3812 chip.
 * @details This program writes data to the YM3812. First the parameter 'data' is compared with 8 bits. If this
 * 			comparison gives a high output then the Data pins D0-D7 are added to the variable 'wridata'. Then the
 * 			variable 'wridata' will be send to the register GPIOB->BSRR.
 * @param 	data_t	data to be written
 * @var		uint16_t wridata
 * 			EXOR the data with the data pin, setting the pin using BSSR
 * @return 	iError
 */
uint8_t YM_WriteBits(uint8_t data)
{
	uint8_t iError = 0;
	uint16_t wridata = 0;

	HAL_GPIO_WritePin(GPIOD, YM_D0, GPIO_PIN_RESET);

	// Check which pins need to be set
	if(data & 1)
		//		wridata |= YM_D0;
		HAL_GPIO_WritePin(GPIOD, YM_D0, GPIO_PIN_SET);


	if(data & 2)
		wridata |= YM_D1;

	if(data & 4)
		wridata |= YM_D2;

	if(data & 8)
		wridata |= YM_D3;

	if(data & 16)
		wridata |= YM_D4;

	if(data & 32)
		wridata |= YM_D5;

	if(data & 64)
		wridata |= YM_D6;

	if(data & 128)
		wridata |= YM_D7;

	// Write the byte to the databus
	GPIOB->BSRR = wridata  | (~wridata << 16U);
	wridata = 0;


	return iError;
}

// Create 9 voice channel structs for storing the data of each voice channel
pVCH VCH[9]; /**< Create 9 voice channel structs for storing the data of each voice channel **/

/**
 * @fn		uint8_t YM_NOTE_ON(uint8_t VCH_Num)
 * @brief 	Function to activate a note.
 * @details In this function the notes will be activated for all the chips. The register of A0
 * 			and B0 will be written in this code. Because the frequency is in a size of 10 bit, the
 * 			frequency is written via 2 registers. The 8 LSB to A0 and the 2 MSB to B0.
 * @param 	VCH_Num Tells the YM in wich voicechannel the tone can be stored.
 * @return 	iError
 */

uint8_t YM_NOTE_ON(uint8_t VCH_Num)
{
	uint8_t iError = 0;

	YM_WRITE_Databus(1,0xA0+VCH_Num,VCH[VCH_Num].F_Numb & 0xFF); // Set the lower byte of the frequency for chip 1
	YM_WRITE_Databus(1,0xB0+VCH_Num,(0x20 | (VCH[VCH_Num].Octave << 2)) | ((VCH[VCH_Num].F_Numb & 0x300) >> 8)); // Set the two most significant bits of the frequency, the octave and the note on for chip 2
	YM_WRITE_Databus(2,0xA0+VCH_Num,VCH[VCH_Num].F_Numb & 0xFF); // Set the lower byte of the frequency for chip 1
	YM_WRITE_Databus(2,0xB0+VCH_Num,(0x20 | (VCH[VCH_Num].Octave << 2)) | ((VCH[VCH_Num].F_Numb & 0x300) >> 8)); // Set the two most significant bits of the frequency, the octave and the note on for chip 2
	YM_WRITE_Databus(3,0xA0+VCH_Num,VCH[VCH_Num].F_Numb & 0xFF); // Set the lower byte of the frequency for chip 1
	YM_WRITE_Databus(3,0xB0+VCH_Num,(0x20 | (VCH[VCH_Num].Octave << 2)) | ((VCH[VCH_Num].F_Numb & 0x300) >> 8)); // Set the two most significant bits of the frequency, the octave and the note on for chip 2
	YM_WRITE_Databus(4,0xA0+VCH_Num,VCH[VCH_Num].F_Numb & 0xFF); // Set the lower byte of the frequency for chip 1
	YM_WRITE_Databus(4,0xB0+VCH_Num,(0x20 | (VCH[VCH_Num].Octave << 2)) | ((VCH[VCH_Num].F_Numb & 0x300) >> 8)); // Set the two most significant bits of the frequency, the octave and the note on for chip 2



	return iError;
}

/**
 * @fn		uint8_t YM_NOTE_OFF(uint8_t Key_Number, uint8_t Velocity)
 * @brief 	Function to turn a note off.
 * @details In this function the notes will be de-activated for all the chips. The register of A0-A9(9 voices)
 * 			and B0-B9(9 voices) will be written in this code. In the forloop every voicing will be checked if they are
 * 			enabled, if so this voice will be written with a data of '0'. This sets the voicing off.
 * @param 	Key_Number  Wich Key is pressed
 * @param 	Velocity	At wich speed is the key pressed
 * @return 	iError
 */
uint8_t YM_NOTE_OFF(uint8_t Key_Number, uint8_t Velocity)
{
	uint8_t iError = 0;
	int i;

	for(i=0;i<9;i++) // Check which voice channel needs to be set off
	{
		if(VCH[i].KEY_Numb == Key_Number && VCH[i].Enable == TRUE)
		{
			// Disable the voice channel on all the chips
			YM_WRITE_Databus(1,0xA0+i,0);
			YM_WRITE_Databus(1,0xB0+i,0);
			YM_WRITE_Databus(2,0xA0+i,0);
			YM_WRITE_Databus(2,0xB0+i,0);
			YM_WRITE_Databus(3,0xA0+i,0);
			YM_WRITE_Databus(3,0xB0+i,0);
			YM_WRITE_Databus(4,0xA0+i,0);
			YM_WRITE_Databus(4,0xB0+i,0);

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
int F_Number[16] = {0x134,0x146,0x15A,0x16E,0x184,0x19B,0x1B4,0x1CE,0x1E9,0x206,0x225,0x246,0x268,0x28D,0x2B4,0x2DD}; /**< Array with F-numbers representing notes in one octave */


/**
 * @fn			uint8_t YM_PITCH(uint8_t KeyNumber, uint8_t Velocity)
 * @brief 		Function for change the pitch.
 * @details 	First there will be a check if a note is activated(Keynumber == 0). If not the note given with the paramater 'KeyNumber'
 * 				will be played. If a note is allready activated, this note will be changed to the given note from the parameter.
 * @param 		KeyNumber Wich key is pressed
 * @param		Velocity  At wich speed is the key pressed.
 * @var 		uint8_t VCH_Num
 * @var			uint8_t ArrayNumb
 * @return 		uint8_t iError
 */
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
				VCH[VCH_Num].Enable = TRUE;
				VCH[VCH_Num].KEY_Numb = KeyNumber;
				VCH[VCH_Num].Octave = (KeyNumber/12)-1;
				VCH[VCH_Num].Velocity = Velocity >> 1;

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
 * @fn		void YM_RESET()
 * @brief 	Function for resetting the YM's.
 * @details The YM's need to get an reset trigger before uploading any code. This function resets and set the reset pin to trigger the YM's.
 */
void YM_RESET()
{
	HAL_GPIO_WritePin(GPIOC, YM_RST, RESET);
	HAL_Delay(1);
	HAL_GPIO_WritePin(GPIOC, YM_RST, SET);
	HAL_Delay(1);
}

// Arrays with the different numbers for the operator addresses
uint8_t op1[9] = {0,1,2,8,9,10,16,17,18}; /**< Array with addresses for the first YM operators */
uint8_t op2[9] = {3,4,5,11,12,13,19,20,21}; /**< Array with adresses for the second YM operators*/

/**
 * @fn void YM_SET_Def()
 * @brief Function for setting the YM's to default settings.
 * @details Setting the YM's to default settings, so it's playable when code is uploaded.
 */
void YM_SET_Def()
{
	int i; // Counter variable

	//int sound[11] = {0x07,0x4F,0xF2,0x60,0x00,0x08,0x12,0x00,0xF2,0x72,0x00}; //bells
	int sound1[11] = {0x01,0x1D,0xF2,0xEF,0x00,0x0A,0x01,0x00,0xF5,0x78,0x00}; //bass1
	//int sound[11] = {0xC1, 0x4F, 0xB1, 0x53, 0x03, 0x06, 0xE0, 0x00, 0x12, 0x74, 0x03}; //bass2
	int sound[11] = {0x20, 0x90, 0xF1, 0x9E, 0x02, 0x0C, 0x11, 0x00, 0xF1, 0x5B, 0x03}; //epiano

	YM_WRITE_Databus(1,0x01,0x20); // Enable multiple waveforms on chip 1
	//YM_WRITE_Databus(2,0x01,0x20); // Enable multiple waveforms on chip 2

	// Set the default settings for chip 1
	for(i=0;i<9;i++)
	{
		YM_WRITE_Databus(1,0x20 + op1[i],sound[0]); // set the multiplier to 1
		YM_WRITE_Databus(1,0x40 + op1[i],sound[1]); // set the volume to the loudest volume possible
		YM_WRITE_Databus(1,0x60 + op1[i],sound[2]); // Set the attack to fast and the decay to slow
		YM_WRITE_Databus(1,0x80 + op1[i],sound[3]); // Set the sustain and release to medium
		YM_WRITE_Databus(1,0xE0 + op1[i],sound[4]); // Set the waveform to a kind of sawtooth wave

		YM_WRITE_Databus(1,0xC0 + i,sound[5]); // Set the waveform to a kind of sawtooth wave

		YM_WRITE_Databus(1,0x20 + op2[i],sound[6]); // set the multiplier to 1
		YM_WRITE_Databus(1,0x40 + op2[i],sound[7]); // set the volume to the loudest volume possible
		YM_WRITE_Databus(1,0x60 + op2[i],sound[8]); // Set the attack to fast and the decay to slow
		YM_WRITE_Databus(1,0x80 + op2[i],sound[9]); // Set the sustain and release to medium
		YM_WRITE_Databus(1,0xE0 + op2[i],sound[10]); // Set the waveform to a kind of sawtooth wave


	}

	// Set the default settings for chip 2
	for(i=0;i<9;i++)
	{
		YM_WRITE_Databus(2,0x20 + op1[i],sound1[0]); // set the multiplier to 1
		YM_WRITE_Databus(2,0x40 + op1[i],sound1[1]); // set the volume to the loudest volume possible
		YM_WRITE_Databus(2,0x60 + op1[i],sound1[2]); // Set the attack to fast and the decay to slow
		YM_WRITE_Databus(2,0x80 + op1[i],sound1[3]); // Set the sustain and release to medium
		YM_WRITE_Databus(2,0xE0 + op1[i],sound1[4]); // Set the waveform to a kind of sawtooth wave

		YM_WRITE_Databus(2,0xC0 + i,sound1[5]); // Set the waveform to a kind of sawtooth wave

		YM_WRITE_Databus(2,0x20 + op2[i],sound1[6]); // set the multiplier to 1
		YM_WRITE_Databus(2,0x40 + op2[i],sound1[7]); // set the volume to the loudest volume possible
		YM_WRITE_Databus(2,0x60 + op2[i],sound1[8]); // Set the attack to fast and the decay to slow
		YM_WRITE_Databus(2,0x80 + op2[i],sound1[9]); // Set the sustain and release to medium
		YM_WRITE_Databus(2,0xE0 + op2[i],sound1[10]); // Set the waveform to a kind of sawtooth wave
	}
	for(i=0;i<9;i++)
	{
		YM_WRITE_Databus(3,0x20 + op1[i],0x01); // set the multiplier to 1
		YM_WRITE_Databus(3,0x40 + op1[i],0x00); // set the volume to the loudest volume possible
		YM_WRITE_Databus(3,0x60 + op1[i],0xF0); // Set the attack to fast and the decay to slow
		YM_WRITE_Databus(3,0x80 + op1[i],0x77); // Set the sustain and release to medium
		YM_WRITE_Databus(3,0xE0 + op1[i],0x00); // Set the waveform to a sine wave that is made fully positive

		YM_WRITE_Databus(3,0x20 + op2[i],0x01); // set the multiplier to 1
		YM_WRITE_Databus(3,0x40 + op2[i],0x00); // set the volume to the loudest volume possible
		YM_WRITE_Databus(3,0x60 + op2[i],0xF0); // Set the attack to fast and the decay to slow
		YM_WRITE_Databus(3,0x80 + op2[i],0x77); // Set the sustain and release to medium
		YM_WRITE_Databus(3,0xE0 + op2[i],0x00); // Set the waveform to a sine wave that is made fully positive
	}
	for(i=0;i<9;i++)
	{
		YM_WRITE_Databus(4,0x20 + op1[i],0x01); // set the multiplier to 1
		YM_WRITE_Databus(4,0x40 + op1[i],0x00); // set the volume to the loudest volume possible
		YM_WRITE_Databus(4,0x60 + op1[i],0xF0); // Set the attack to fast and the decay to slow
		YM_WRITE_Databus(4,0x80 + op1[i],0x77); // Set the sustain and release to medium
		YM_WRITE_Databus(4,0xE0 + op1[i],0x00); // Set the waveform to a sine wave that is made fully positive

		YM_WRITE_Databus(4,0x20 + op2[i],0x01); // set the multiplier to 1
		YM_WRITE_Databus(4,0x40 + op2[i],0x00); // set the volume to the loudest volume possible
		YM_WRITE_Databus(4,0x60 + op2[i],0xF0); // Set the attack to fast and the decay to slow
		YM_WRITE_Databus(4,0x80 + op2[i],0x77); // Set the sustain and release to medium
		YM_WRITE_Databus(4,0xE0 + op2[i],0x00); // Set the waveform to a sine wave that is made fully positive
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
/**
 * @}
 */
