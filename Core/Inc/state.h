/*
 * state.h
 *
 *  Created on: May 22, 2025
 *      Author: timca
 */

#ifndef INC_STATE_H_
#define INC_STATE_H_

typedef enum {
	CURRENT_STEPS,
	DISTANCE_TRAVELLED,
	GOAL_PROGRESS,
	SET_GOAL,
	TEST_MODE
} state_t;

void STATE_update(void);
state_t STATE_get_state(void);

#endif /* INC_STATE_H_ */
