
#include "stm32f4xx.h"
#include "stm32f4xx_hal.h"
#include "bsp.h"
#include "motor.h"

#define STATUS_LED_PIN					GPIO_PIN_12
#define STATUS_LED_PORT					GPIOD
#define STATUS_LED_CLK_ENABLE()			__HAL_RCC_GPIOD_CLK_ENABLE()
#define STATUS_LED_CLK_DISABLE()		__HAL_RCC_GPIOD_CLK_DISABLE()

void BSP_StatusLED_Init();

void BSP_Init() {
	HAL_Init();
	//BSP_StatusLED_Init();
	MOTOR_Init();
}

void BSP_StatusLED_Init() {
	GPIO_InitTypeDef GPIO_InitStruct;

	STATUS_LED_CLK_ENABLE();

	GPIO_InitStruct.Pin = STATUS_LED_PIN;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_PULLUP;
	GPIO_InitStruct.Speed = GPIO_SPEED_FAST;

	HAL_GPIO_Init(STATUS_LED_PORT, &GPIO_InitStruct);

	HAL_GPIO_WritePin(STATUS_LED_PORT, STATUS_LED_PIN, GPIO_PIN_RESET);
}

void BSP_StatusLED_Set() {
	HAL_GPIO_WritePin(STATUS_LED_PORT, STATUS_LED_PIN, GPIO_PIN_SET);
}

void BSP_StatusLED_Reset() {
	HAL_GPIO_WritePin(STATUS_LED_PORT, STATUS_LED_PIN, GPIO_PIN_RESET);
}

void BSP_Delay(uint32_t ms) {
	HAL_Delay(ms);
}
