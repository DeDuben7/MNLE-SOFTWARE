/*
* Filename      : MIDI.c
* Version       : V1.00
* Programmer(s) : Schotburgh, Oehlers en van Renswoude
*/

#include "includes.h"

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
}
