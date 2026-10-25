/*
 * calculations.c
 *
 *  Created on: May 21, 2025
 *      Author: tdo56
 */

#include "calc.h"
#include "display.h"
#include "joystick_driver.h"
#include "pot_driver.h"
#include "peak_detection.h"
#include "state.h"

static uint16_t steps = 0;
static uint16_t step_goal = 1000;
static uint16_t increment_ratio = 0;
static uint16_t increment_amount = 1;
static uint16_t threshold = 40000;

void CALC_test_mode_counter(void)
{
	if (steps > step_goal)
	{
		steps = step_goal;
	}

	uint16_t displacement_y = 0;

	increment_amount = (step_goal)/(80); //goal divide by Hz (80)
	joystickDirection_t direction_y = JOYSTICK_get_direction("y");
	displacement_y = JOYSTICK_get_displacement("y");
	increment_ratio = displacement_y;
	if (direction_y == JOYSTICK_UP)
	{
		if (steps + (increment_amount*increment_ratio)/100 <= step_goal)
		{
			steps += (uint16_t)(increment_amount*increment_ratio)/100;
		} else {
			steps = step_goal;
		}
	}
	if (direction_y == JOYSTICK_DOWN)
	{
		if (steps - (increment_amount*increment_ratio)/100 >= 0)
		{
			steps -= (uint16_t)(increment_amount*increment_ratio)/100;
		} else {
			steps = 0;
		}
	}
}

void CALC_update(void)
{
	if (STATE_get_state() == TEST_MODE)
	{
		CALC_test_mode_counter();
	}

	if (PD_check_peak(threshold))
	{
		steps += 1;
	}
}

void CALC_set_goal(void)
{
	step_goal = POT_get_step_goal();
}

uint16_t CALC_get_steps(void)
{
	return steps;
}

uint16_t CALC_get_step_goal(void)
{
	return step_goal;
}
