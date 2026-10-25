/*
 * task_serial.h
 *
 *  Created on: Mar 19, 2025
 *      Author: tdo56
 */

#ifndef INC_TASK_SERIAL_H_
#define INC_TASK_SERIAL_H_

#include <stdint.h>

extern uint8_t serialToggle;

void serial_toggle(void);
void serial_task_execute(void);
#endif /* INC_TASK_SERIAL_H_ */
