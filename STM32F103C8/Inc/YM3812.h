/*
 * YM3812.h
 *
 *  Created on: 25 okt. 2019
 *      Author: Ruben
 */

#ifndef YM3812_H_
#define YM3812_H_

#include "includes.h"


#define A0 	GPIO_PIN_10		//GPIOA
#define WR 	GPIO_PIN_9 		//GPIOA
#define RST GPIO_PIN_8 		//GPIOA
#define CS1 GPIO_PIN_12 	//GPIOA
//#define CS2 GPIO_PIN_11 	//GPIOA
//#define CS3 GPIO_PIN_10 	//GPIOA
//#define CS4 GPIO_PIN_9 	//GPIOA

#define D0 	GPIO_PIN_8		//GPIOB
#define D1 	GPIO_PIN_9		//GPIOB
#define D2 	GPIO_PIN_12 	//GPIOB
#define D3 	GPIO_PIN_3 		//GPIOB
#define D4 	GPIO_PIN_4 		//GPIOB
#define D5 	GPIO_PIN_5 		//GPIOB
#define D6 	GPIO_PIN_6 		//GPIOB
#define D7 	GPIO_PIN_7 		//GPIOB

uint8_t YM_WRITE_Databus(uint8_t chips, uint8_t addr_select, uint8_t data);
uint8_t YM_WriteBits(uint8_t data);

/* Frequency array om het F-number te genereren.
F Number	Frequency
			(decimal)	Note
16B			277.2		C#
181			293.7		D
198			311.1		D#
1B0			329.6		E
1CA			349.2		F
1E5			370.0		F#
202			392.0		G
220			415.3		G#
241			440.0		A
263			466.2		A#
287			493.9		B
2AE			523.3		C
*/





#endif /* YM3812_H_ */
