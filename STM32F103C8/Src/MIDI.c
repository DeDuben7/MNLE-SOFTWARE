/*
*********************************************************************************************************
*
* Filename      : MIDI.C
* Version       : V1.00
* Programmer(s) : Julian Schotborgh
*
*  24-10-19 Opstart midi.c en maken midi_proc() - JS
*  25-10-19 Aanpassen functie op nieuw ontwerp. - JS
*********************************************************************************************************
*/

#include "includes.h"

int i = 0;  //counter
uint8_t FUNC_VAR[2]; // binnengekomen data voor de functies
uint8_t DATA[2]; // binnengekomen data voor de functies
char MIDI_FUNC; // variabele om fucntie nibble op te slaan
char MIDI_CHANNEL; // variabele om channel nibble op te slaan
int err = 0; // error variabele
uint8_t NOTE_ON_FLAG;
uint8_t NOTE_OFF_FLAG;
uint8_t NOTE_PROG_CHANGE_FLAG;
uint8_t NOTE_CONT_CHANGE_FLAG;

int MIDI_PROC(uint8_t MIDI_MSG)
{

	if(MIDI_MSG & 128)
	{
		i = 0;
		DATA[0] = 0;
		DATA[1] = 0;
		if((MIDI_MSG & 0xF0) == 144)
		{
			NOTE_ON_FLAG = 1;
		}
		else if((MIDI_MSG & 0xF0) == 128)
		{
			NOTE_OFF_FLAG = 1;
		}
		else if((MIDI_MSG & 0xF0) == 192)
		{
			NOTE_PROG_CHANGE_FLAG = 1;
		}
		else if((MIDI_MSG & 0xF0) == 176)
		{
			NOTE_CONT_CHANGE_FLAG = 1;
		}
	}
	else
	{
		if(NOTE_ON_FLAG == 1)
		{

			err = 0;
			DATA[i++] = MIDI_MSG;
			uint8_t Test = 255;
			if(i==2)
			{
//				HAL_UART_Transmit_IT(&huart2, &DATA[0], 1);
//				HAL_Delay(50);
//				HAL_UART_Transmit_IT(&huart2, &DATA[1], 1);
//				HAL_Delay(50);
//				HAL_UART_Transmit_IT(&huart2, &Test, 1);
//				HAL_Delay(50);
				YM_NOTE_ON(0,DATA[0],DATA[1]);
				NOTE_ON_FLAG = 0;
			}
			return err;
		}
		else if(NOTE_OFF_FLAG == 1)
		{
			err = 0;
			DATA[i++] = MIDI_MSG;
			if(i==2)
			{
			//	YM_NOTE_ON(0,DATA[0],0);
				NOTE_OFF_FLAG = 0;
			}
			return err;
		}
		else if(NOTE_PROG_CHANGE_FLAG == 1)
		{
			err = 0;
				DATA[i++] = MIDI_MSG;
				if(i==2)
				{
//					NOTE_PROG_CHANGE(MIDI_CHANNEL,FUNC_VAR[0],0);
//					NOT_PROG_CHANGE = 0;
				}
				return err;

		}
		else if(NOTE_CONT_CHANGE_FLAG == 1)
		{
			err = 0;
			DATA[i++] = MIDI_MSG;
			if(i==2)
			{
//				NOTE_CONT_CHANGE(MIDI_CHANNEL,FUNC_VAR[0],0);
				NOTE_CONT_CHANGE_FLAG = 0;
			}
			return err;

		}
	}
}


