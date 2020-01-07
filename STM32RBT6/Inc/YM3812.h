/*
* Filename      : YM3812.c
* Version       : V1.00
* Programmer(s) : Schotburgh, Oehlers en van Renswoude
*/

#ifndef YM3812_H_
#define YM3812_H_

#include "includes.h"


#define ON 	1	/**< Defines On 	to 	1 */
#define OFF 0	/**< Defines Off to 	0 */

//Function declarations for the YM3812
uint8_t YM_WRITE_Databus(uint8_t chips, uint8_t adress, uint8_t data);
uint8_t YM_WriteBits(uint8_t data);
uint8_t YM_NOTE_ON(uint8_t VCH_Num);
uint8_t YM_NOTE_OFF(uint8_t KEY_NUMBER, uint8_t VELOCITY);
uint8_t YM_PITCH(uint8_t KeyNumber, uint8_t Velocity);
void YM_SET_Def();
void YM_RESET();

#endif /* YM3812_H_ */
