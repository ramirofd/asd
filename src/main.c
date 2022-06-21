/**
  ******************************************************************************
  * @file    main.c
  * @author  Ac6
  * @version V1.0
  * @date    01-December-2013
  * @brief   Default main function.
  ******************************************************************************
*/

#include <stdio.h>
#include <string.h>

#include "bsp.h"


int main(void)
{
	BSP_Init();

//	MOTOR_Set(MOTOR_1, 1000, MOTOR_ON);
//	MOTOR_Set(MOTOR_2, 2000, MOTOR_ON);
//	MOTOR_Set(MOTOR_3, 3000, MOTOR_ON);
//	MOTOR_Set(MOTOR_4, 4000, MOTOR_ON);
	SERIAL_Init();
	char *cmd;
	char *name;
	char *cereal_a;
	char *cereal_b;
	for(;;){
		if(SERIAL_Available()) {
			char *data = (char *)SERIAL_GetData();
			cmd = strtok(data, ":");
			if(strcmp(cmd, "or")==0) {
				name = strtok(NULL, ",");
				cereal_a = strtok(NULL, ",");
				cereal_b = strtok(NULL, ";");
				MOTOR_Set(MOTOR_1, atoi(cereal_a)*1000, MOTOR_ON);
				MOTOR_Set(MOTOR_2, atoi(cereal_b)*1000, MOTOR_ON);
			}

		}
	}
}
