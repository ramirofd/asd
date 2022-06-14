/**
  ******************************************************************************
  * @file    main.c
  * @author  Ac6
  * @version V1.0
  * @date    01-December-2013
  * @brief   Default main function.
  ******************************************************************************
*/

#include "bsp.h"

int main(void)
{
	BSP_Init();

	MOTOR_Set(MOTOR_1, 1000, MOTOR_ON);
	MOTOR_Set(MOTOR_2, 2000, MOTOR_ON);
	MOTOR_Set(MOTOR_3, 3000, MOTOR_ON);
	MOTOR_Set(MOTOR_4, 4000, MOTOR_ON);
	SERIAL_Init();



	for(;;){
		//BSP_StatusLED_Set();
//		BSP_Delay(500);
		//BSP_StatusLED_Reset();
		//BSP_Delay(500);

	}
}
