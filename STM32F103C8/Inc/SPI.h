/*
 * SPI.h
 *
 *  Created on: 9 dec. 2019
 *      Author: Ruben
 */

#ifndef SPI_H_
#define SPI_H_

uint8_t SPI_Transmit(uint8_t addr, uint8_t data, uint8_t device);
uint8_t SPI_Receive(uint8_t addr, uint8_t device);

#endif /* SPI_H_ */
