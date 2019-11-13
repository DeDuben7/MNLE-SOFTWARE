/*
* Filename      : MIDI.c
* Version       : V1.00
<<<<<<< HEAD
* Programmer(s) : Julian Schotborgh
*
*  24-10-19 Opstart midi.c en maken midi_proc() - JS
*  25-10-19 Aanpassen functie op nieuw ontwerp. - JS
*********************************************************************************************************
=======
* Programmer(s) : Schotburgh, Oehlers en van Renswoude
>>>>>>> YM_dev_brian
*/

#include "includes.h"

<<<<<<< HEAD
int i = 0;  //counter
uint8_t FUNC_VAR[2]; // binnengekomen data voor de functies
char MIDI_FUNC; // variabele om fucntie nibble op te slaan
char MIDI_CHANNEL; // variabele om channel nibble op te slaan
int err = 0; // error variabele

void MIDI_PROC(uint8_t MIDI_MSG)
{
	if(i == 2)
	{
		switch(MIDI_FUNC) // switch om data naar goeie YM functie te sturen
		{
			case PITCH:
				//err = YM_PITCH(MIDI_CHANNEL,FUNC_VAR[1]);
				i=0;
				break;
			case NOTE_OFF:
				//err = YM_NOTE_ON(MIDI_CHANNEL,FUNC_VAR[0],0);
				//HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_13);
				//HAL_UART_Transmit(&huart2, "noteoff", 7, 100);
				i=0;
				break;
			case NOTE_ON:
				//err = YM_NOTE_ON(MIDI_CHANNEL,FUNC_VAR[0],FUNC_VAR[1]);
				HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_13);
				//HAL_UART_Transmit_IT(&huart2, "noteon", 6);
				i=0;
				break;
			case CONT_CHANGE:
				//err = YM_CONT_CHANGE(MIDI_CHANNEL,FUNC_VAR[0],FUNC_VAR[1]);
				//HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_13);
				//HAL_UART_Transmit(&huart2, "cont", 4, 100);
				i=0;
				break;
			default:
				//err = NO_FUNC;
				return;
		}
	}

	if(MIDI_MSG & 128)
	{
		MIDI_CHANNEL = (char)(MIDI_MSG & 0x0F); // lsb bits van byte omzetten in nibble
		MIDI_FUNC = (char)((MIDI_MSG & 0xF0)>>4); // msb bits van byte omzetten in nibble
		return;
	}

	else if(!(MIDI_MSG & 128))
	{
		FUNC_VAR[i++] = MIDI_MSG;
	}

	if(MIDI_FUNC == PROG_CHANGE && i == 1)
	{
		//err = YM_PROG_CHANGE(MIDI_CHANNEL,FUNC_VAR[0]);
		i = 0;
		return;
	}


=======
int i = 0;  			// Counter variable for MIDI_PROC function
uint8_t DATA[2]; 		// Array for storing incoming data
char MIDI_FUNC; 		// Variable for storing the function nibble
char MIDI_CHANNEL; 		// Variable for storing the channel nibble

// Some flags for receiving different messages
uint8_t NOTE_ON_FLAG;
uint8_t NOTE_OFF_FLAG;
uint8_t NOTE_PROG_CHANGE_FLAG;
uint8_t NOTE_CONT_CHANGE_FLAG;

/**
  * @brief Function for processing MIDI messages
  * @retval iError
  */
uint8_t MIDI_PROC(uint8_t MIDI_MSG)
{
	uint8_t iError;

	if(MIDI_MSG & 128) // Check if this is the first byte of a message
	{
		// Reset the variables
		i = 0;
		DATA[0] = 0;
		DATA[1] = 0;

		// Check the function of the message
		if((MIDI_MSG & 0xF0) == 144)
			NOTE_ON_FLAG = 1;

		else if((MIDI_MSG & 0xF0) == 128)
			NOTE_OFF_FLAG = 1;

		else if((MIDI_MSG & 0xF0) == 192)
			NOTE_PROG_CHANGE_FLAG = 1;

		else if((MIDI_MSG & 0xF0) == 176)
			NOTE_CONT_CHANGE_FLAG = 1;
	}

	else // If the received byte isn't the first byte of a message, process the byte
	{
		if(NOTE_ON_FLAG == 1) 		// If the message was Note On
		{
			iError = 0;
			DATA[i++] = MIDI_MSG; 	// Store the data

			if(i==2)				// If the last byte is received
			{
				YM_NOTE_ON(0,DATA[0],DATA[1]); // Call the Note On function
				NOTE_ON_FLAG = 0;
			}
			return iError;
		}

		else if(NOTE_OFF_FLAG == 1)	// If the message was Note Off
		{
			iError = 0;
			DATA[i++] = MIDI_MSG;	// Store the data

			if(i==2)				// If the last byte is received
			{
				YM_NOTE_OFF(DATA[0],DATA[1]); // Call the Note Off function
				NOTE_OFF_FLAG = 0;
			}
			return iError;
		}

		else if(NOTE_PROG_CHANGE_FLAG == 1) // If the message was Program change
		{
			iError = 0;
			DATA[i++] = MIDI_MSG;			// Store the data

			if(i==2)						// If the last byte is received
			{
//					NOTE_PROG_CHANGE(MIDI_CHANNEL,FUNC_VAR[0],0); // Call the PROG_CHANGE function
//					NOT_PROG_CHANGE = 0;
			}
			return iError;
		}

		else if(NOTE_CONT_CHANGE_FLAG == 1) // If the message was Control change
		{
			iError = 0;
			DATA[i++] = MIDI_MSG;			// Store the data

			if(i==2)						// If the last byte is received
			{
//				NOTE_CONT_CHANGE(MIDI_CHANNEL,FUNC_VAR[0],0); // Call the CONT_CHANGE function
//				NOTE_CONT_CHANGE_FLAG = 0;
			}
			return iError;
		}
	}
	return iError;
>>>>>>> YM_dev_brian
}
