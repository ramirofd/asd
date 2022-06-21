/*
 * serial.h
 *
 *  Created on: 10 jun. 2022
 *      Author: ramir
 */

#ifndef SERIAL_H_
#define SERIAL_H_

#include <stdint.h>

void SERIAL_Init(void);
void SERIAL_Write(uint8_t *data,  uint16_t size);
int SERIAL_Available();
uint8_t* SERIAL_GetData();


#endif /* SERIAL_H_ */
