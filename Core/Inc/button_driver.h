/*
 * button_driver.h
 *
 *  Created on: May 17, 2025
 *      Author: tdo56
 *
 * This driver acts as an interlayer between the provided buttons module and the program
 */

#ifndef INC_BUTTON_DRIVER_H_
#define INC_BUTTON_DRIVER_H_

#include "buttons.h"

#define LONG_PRESS_TIME_MS 1000
#define DOUBLE_PRESS_WINDOW_MS 500

typedef enum {
	NONE,
	PRESSED,
	DOUBLE_PRESS,
	LONG_PRESS
} buttonEvent_t;

void BUTTON_init(void);
void BUTTON_update_state(void);
buttonEvent_t BUTTON_get_event(buttonName_t name);

#endif /* INC_BUTTON_DRIVER_H_ */
