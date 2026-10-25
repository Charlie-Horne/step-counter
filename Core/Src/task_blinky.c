/*
 * task_blinky.c
 *
 *  Created on: Mar 6, 2025
 *      Author: tdo56
 */

#include "task_blinky.h"
#include "gpio.h"

void blinky_task_execute(void)
{
	HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_5);
}
