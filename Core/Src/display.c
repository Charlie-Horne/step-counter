/*
 * display.c
 *
 *  Created on: May 21, 2025
 *      Author: tdo56
 */


#include "display.h"
#include "ssd1306.h"
#include "button_driver.h"
#include "joystick_driver.h"
#include "calc.h"
#include "display_steps.h"
#include "display_distance.h"
#include "display_goal.h"
#include "display_setgoal.h"
#include "display_testmode.h"
#include "state.h"

void DISPLAY_init(void)
{
	ssd1306_Init();
}

void DISPLAY_update(void)
{
	state_t state = STATE_get_state();
	switch (state) {
	case CURRENT_STEPS:
		display_steps();
		break;
	case DISTANCE_TRAVELLED:
		display_distance();
		break;
	case GOAL_PROGRESS:
		display_goal();
		break;
	case SET_GOAL:
		display_set_goal();
		break;
	case TEST_MODE:
		display_testmode();
		break;
	}

	ssd1306_UpdateScreen();
}
