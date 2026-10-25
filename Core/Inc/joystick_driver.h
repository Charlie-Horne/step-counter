/*
 * joystick_driver.h
 *
 *  Created on: May 21, 2025
 *      Author: tdo56
 */

#ifndef INC_JOYSTICK_DRIVER_H_
#define INC_JOYSTICK_DRIVER_H_

#include <stdint.h>

typedef enum {
	JOYSTICK_UP,
	JOYSTICK_DOWN,
	JOYSTICK_LEFT,
	JOYSTICK_RIGHT,
	JOYSTICK_REST
} joystickDirection_t;

void JOYSTICK_init(void);
joystickDirection_t JOYSTICK_get_direction(char* axis);
uint8_t JOYSTICK_get_displacement(char* axis);

#endif /* INC_JOYSTICK_DRIVER_H_ */
