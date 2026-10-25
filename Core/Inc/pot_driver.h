/*
 * pot_driver.h
 *
 *  Created on: May 21, 2025
 *      Author: tdo56
 */

#ifndef INC_POT_DRIVER_H_
#define INC_POT_DRIVER_H_

#include <stdint.h>

void POT_init(void);
uint16_t POT_get_step_goal(void);

#endif /* INC_POT_DRIVER_H_ */
