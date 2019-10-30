/*
 * YM3812.h
 *
 *  Created on: 25 okt. 2019
 *      Author: Ruben
 */

#ifndef YM3812_H_
#define YM3812_H_

#include "includes.h"

<<<<<<< HEAD
=======

>>>>>>> f4a785b284f1f2546d5c9ddb6d42c29c97522663
#define A0 	GPIO_PIN_8 		//GPIOB
#define WR 	GPIO_PIN_9 		//GPIOB
#define RST GPIO_PIN_8 		//GPIOA
#define CS1 GPIO_PIN_12 	//GPIOA
<<<<<<< HEAD
//#define CS2 GPIO_PIN_11 	//GPIOA
//#define CS3 GPIO_PIN_10 	//GPIOA
//#define CS4 GPIO_PIN_9 		//GPIOA
//#define D0 	GPIO_PIN_13 	//GPIOA - Voor nu GPIOC
//#define D1 	GPIO_PIN_14 	//GPIOA - Voor nu GPIOC
#define D0 GPIO_PIN_10
#define D1 GPIO_PIN_9
=======
#define CS2 GPIO_PIN_11 	//GPIOA
#define CS3 GPIO_PIN_10 	//GPIOA
#define CS4 GPIO_PIN_9 		//GPIOA
#define D0 	GPIO_PIN_13 	//GPIOA - Voor nu GPIOC
#define D1 	GPIO_PIN_14 	//GPIOA - Voor nu GPIOC
>>>>>>> f4a785b284f1f2546d5c9ddb6d42c29c97522663
#define D2 	GPIO_PIN_15 	//GPIOA
#define D3 	GPIO_PIN_3 		//GPIOB
#define D4 	GPIO_PIN_4 		//GPIOB
#define D5 	GPIO_PIN_5 		//GPIOB
#define D6 	GPIO_PIN_6 		//GPIOB
#define D7 	GPIO_PIN_7 		//GPIOB
<<<<<<< HEAD

uint8_t YM_WRITE_Databus(uint8_t chips, uint8_t addr_select, uint8_t data);
uint8_t YM_WriteBits(uint8_t data);
=======
>>>>>>> f4a785b284f1f2546d5c9ddb6d42c29c97522663

#endif /* YM3812_H_ */
