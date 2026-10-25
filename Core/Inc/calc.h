/*
 * calculations.h
 *
 *  Created on: May 21, 2025
 *      Author: timca
 */

#ifndef INC_CALC_H_
#define INC_CALC_H_

#include <stdint.h>

void CALC_update(void);
void CALC_set_goal(void);
uint16_t CALC_get_steps(void);
uint16_t CALC_get_step_goal(void);

#endif /* INC_CALC_H_ */
