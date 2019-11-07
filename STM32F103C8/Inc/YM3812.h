/*
 * YM3812.h
 *
 *  Created on: 25 okt. 2019
 *      Author: Ruben
 */

#ifndef YM3812_H_
#define YM3812_H_

#include "includes.h"

#define RST 	GPIO_PIN_8 		//GPIOA
#define A0 		GPIO_PIN_10		//GPIOA
#define WR		GPIO_PIN_9		//GPIOA
#define CS_1  	GPIO_PIN_11		//GPIOA
#define CS_2 	GPIO_PIN_12 	//GPIOA
//#define CS_3  				//GPIOA
//#define CS_4 	GPIO_PIN_10 	//GPIOA

#define D0 	GPIO_PIN_8		//GPIOB
#define D1 	GPIO_PIN_9		//GPIOB
#define D2 	GPIO_PIN_12 	//GPIOB
#define D3 	GPIO_PIN_3 		//GPIOB
#define D4 	GPIO_PIN_4 		//GPIOB
#define D5 	GPIO_PIN_5 		//GPIOB
#define D6 	GPIO_PIN_6 		//GPIOB
#define D7 	GPIO_PIN_7 		//GPIOB

//#define D0 	GPIO_PIN_3		//GPIOB
//#define D1 	GPIO_PIN_4		//GPIOB
//#define D2 	GPIO_PIN_5	 	//GPIOB
//#define D3 	GPIO_PIN_6 		//GPIOB
//#define D4 	GPIO_PIN_7 		//GPIOB
//#define D5 	GPIO_PIN_8 		//GPIOB
//#define D6 	GPIO_PIN_9 		//GPIOB
//#define D7 	GPIO_PIN_12		//GPIOB

#define ON 	1
#define OFF 0

uint8_t YM_WRITE_Databus(uint8_t chips, uint8_t adress, uint8_t data);
uint8_t YM_WriteBits(uint8_t data);
uint8_t YM_NOTE_ON(uint8_t MIDI_CHANNEL, uint8_t KEY_NUMBER, uint8_t VELOCITY);
uint8_t YM_NOTE_OFF(uint8_t KEY_NUMBER, uint8_t VELOCITY);
void YM_SET_Def();
void YM_RESET();

#endif /* YM3812_H_ */
