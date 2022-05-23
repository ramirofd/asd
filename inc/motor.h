/*
 * motor.h
 *
 *  Created on: 21 may. 2022
 *      Author: Yasmin
 */

#ifndef MOTOR_H_
#define MOTOR_H_


#include <stdint.h>


typedef enum {
	MOTOR_1,
	MOTOR_2,
	MOTOR_3,
	MOTOR_4
} MOTOR_TypeDef;

typedef enum {
  MOTOR_ON,
  MOTOR_OFF
} MOTOR_State;


void MOTOR_Init(void);
void MOTOR_Set(MOTOR_TypeDef, uint32_t, MOTOR_State);
void MOTOR_Callback(void);


#endif /* MOTOR_H_ */
