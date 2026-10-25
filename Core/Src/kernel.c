/*
 * kernel.c
 *
 *  Created on: May 21, 2025
 *      Author: tdo56
 */


#include "kernel.h"
#include "stm32c0xx_hal.h"
#include <string.h>

static kernelTask_t tasks[MAX_TASKS];

void KERNEL_init(void)
{
	memset(tasks, 0, sizeof(tasks));
}

bool KERNEL_add_task(task_t task, uint8_t frequency_hz)
{
	if (task == 0 || frequency_hz == 0) return false;
	uint32_t period = 1000U / frequency_hz;
	if (period == 0) period = 1;

	for (int i = 0; i < MAX_TASKS; i++)
	{
		if (!tasks[i].active)
		{
			tasks[i].task = task;
			tasks[i].period_ms = period;
			tasks[i].next_ms = HAL_GetTick() + period;
			tasks[i].active = true;
			return true;
		}
	}
	return false;
}

void KERNEL_run(void)
{
	uint32_t time_ms = HAL_GetTick();
	for (int i = 0; i < MAX_TASKS; i++)
	{
		if (!tasks[i].active) continue;

		if (time_ms >= tasks[i].next_ms)
		{
			tasks[i].task();
			tasks[i].next_ms += tasks[i].period_ms;
			//incase we get behind
			if ((time_ms - tasks[i].next_ms) >= 0)
			{
				tasks[i].next_ms = time_ms + tasks[i].period_ms;
			}
		}
	}
}
