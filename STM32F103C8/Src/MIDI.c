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
char MIDI_FUNC; // variabele om fucntie nibble op te slaan
char MIDI_CHANNEL; // variabele om channel nibble op te slaan
int err = 0; // error variabele

void MIDI_PROC(uint8_t MIDI_MSG)
{

	if(MIDI_MSG & 128)
	{
		MIDI_CHANNEL = MIDI_MSG & 0x0F; // lsb bits van byte omzetten in nibble
		MIDI_FUNC = (MIDI_MSG & 0xF0)>>4; // msb bits van byte omzetten in nibble
		i = 0;
		return;
	}

	if(!(MIDI_MSG & 128))
	{
		FUNC_VAR[i++] = MIDI_MSG;
	}

	if(MIDI_FUNC == PROG_CHANGE && i == 1)
	{
		//err = YM_PROG_CHANGE(MIDI_CHANNEL,FUNC_VAR[0]);
		i = 0;
		return;
	}

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
				FUNC_VAR[0] = 0;
				FUNC_VAR[1] = 0;
				i=0;
				break;
			case NOTE_ON:
				HAL_UART_Transmit_IT(&huart2, &FUNC_VAR[0], 1);
				err = YM_NOTE_ON(MIDI_CHANNEL,FUNC_VAR[0],FUNC_VAR[1]);
				//HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_13);
				//HAL_UART_Transmit_IT(&huart2, "noteon", 6);
				FUNC_VAR[0] = 0;
				FUNC_VAR[1] = 0;
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
}
