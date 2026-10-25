/*
 * state.c
 *
 *  Created on: May 22, 2025
 *      Author: timca
 */

#include "state.h"
#include "joystick_driver.h"
#include "button_driver.h"

static state_t state = CURRENT_STEPS;
static int held = 0;
static int last_state = 0;
static buttonEvent_t SW2_state = NONE;
static buttonEvent_t SWJ_state = NONE;

void STATE_update(void)
{
	joystickDirection_t direction_x = JOYSTICK_get_direction("x");
	SW2_state = BUTTON_get_event(DOWN);
	SWJ_state = BUTTON_get_event(JOYSTICK);

	//testmode logic
	if (SW2_state == DOUBLE_PRESS)
	{
		if (state != TEST_MODE && state != SET_GOAL)
		{
			last_state = state;
			state = TEST_MODE;
			SW2_state = NONE;
		}
		else
		{
			state = last_state;
		}
	}

	//goal set logic
	if (state == GOAL_PROGRESS)
	{
		if (SWJ_state == LONG_PRESS)
		{
			last_state = state;
			state      = SET_GOAL;
			SWJ_state     = NONE;
		}
	}
	else if (state == SET_GOAL)
	{
		if (SWJ_state == PRESSED)
		{
			state  = GOAL_PROGRESS;
			SWJ_state = NONE;
		}
		else if (SWJ_state == LONG_PRESS)
		{
			CALC_set_goal();
			state    = GOAL_PROGRESS;
			SWJ_state   = NONE;
		}
	}

	//goal progress, distance, steps logic
	if (state <= GOAL_PROGRESS)
	{
		if (direction_x == JOYSTICK_REST)
		{
			held = 0;
		}
		else if (direction_x == JOYSTICK_LEFT && !held && SWJ_state == NONE)
		{
			state = (state + 1) % 3;
			held = 1;
		}
		else if (direction_x == JOYSTICK_RIGHT && !held && SWJ_state == NONE)
		{
			state = (state == 0) ? GOAL_PROGRESS : state - 1;
			held = 1;
		}
	}
}

state_t STATE_get_state(void)
{
	return state;
}
