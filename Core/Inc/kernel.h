/*
 * kernel.h
 *
 *  Created on: May 21, 2025
 *      Author: tdo56
 */

#ifndef INC_KERNEL_H_
#define INC_KERNEL_H_

#include <stdint.h>
#include <stdbool.h>

#define MAX_TASKS 12

typedef void (*task_t)(void);

typedef struct {
	task_t task;
	uint32_t period_ms;
	uint32_t next_ms;
	bool active;
} kernelTask_t;

void KERNEL_init(void);
bool KERNEL_add_task(task_t task, uint8_t frequency_hz);
void KERNEL_run(void);

#endif /* INC_KERNEL_H_ */
