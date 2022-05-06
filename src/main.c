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
	for(;;){
		BSP_StatusLED_Set();
		BSP_Delay(500);
		BSP_StatusLED_Reset();
		BSP_Delay(500);
	}
}
