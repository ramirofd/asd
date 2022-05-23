/*
 * motor.c
 *
 *  Created on: 21 may. 2022
 *      Author: Yasmin
 */

#include "motor.h"
#include "stm32f4xx.h"
#include "stm32f4xx_hal.h"

typedef struct {
	MOTOR_TypeDef motor;
	uint32_t	  timer;
	GPIO_TypeDef  *gpio;
	uint16_t	  pin;
} MOTOR_Status;


static MOTOR_Status motors[4] = {
		{.motor = MOTOR_1, .timer = 0, .gpio = GPIOD, .pin = GPIO_PIN_12},
		{.motor = MOTOR_2, .timer = 0, .gpio = GPIOD, .pin = GPIO_PIN_13},
		{.motor = MOTOR_3, .timer = 0, .gpio = GPIOD, .pin = GPIO_PIN_14},
		{.motor = MOTOR_4, .timer = 0, .gpio = GPIOD, .pin = GPIO_PIN_15}
};

void MOTOR_Init(void) {
	GPIO_InitTypeDef GPIO_InitStruct;

	__HAL_RCC_GPIOD_CLK_ENABLE();

	uint16_t pins = GPIO_PIN_12 | GPIO_PIN_13 | GPIO_PIN_14 | GPIO_PIN_15;

	GPIO_InitStruct.Pin = pins;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_LOW;

	HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);

	HAL_GPIO_WritePin(GPIOD, pins, GPIO_PIN_RESET);
}

void MOTOR_Set(MOTOR_TypeDef motor, uint32_t time, MOTOR_State state) {
	GPIO_TypeDef  *gpio = NULL;
	uint16_t pin = 0;

	switch (motor) {
	case MOTOR_1:
		motors[0].timer = time;
		gpio = motors[0].gpio;
		pin = motors[0].pin;
		break;
	case MOTOR_2:
		motors[1].timer = time;
		gpio = motors[1].gpio;
		pin = motors[1].pin;
		break;
	case MOTOR_3:
		motors[2].timer = time;
		gpio = motors[2].gpio;
		pin = motors[2].pin;
		break;
	case MOTOR_4:
		motors[3].timer = time;
		gpio = motors[3].gpio;
		pin = motors[3].pin;
		break;
	default:
		return;
	}


	HAL_GPIO_WritePin(gpio, pin, state == MOTOR_OFF ? GPIO_PIN_RESET: GPIO_PIN_SET);

}

void MOTOR_Callback(void) {
	for (size_t i = 0; i < 4; i++) {
		if (motors[i].timer) {
			motors[i].timer--;
			if (!motors[i].timer) {
				 MOTOR_Set(motors[i].motor, 0, MOTOR_OFF);
			}
		}

	}
}



