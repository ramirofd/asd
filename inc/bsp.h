#include "stdint.h"
#include "motor.h"
#include "serial.h"

void BSP_Init();
void BSP_StatusLED_Set();
void BSP_StatusLED_Reset();
void BSP_Delay(uint32_t ms);
void Error_Handler(void);

