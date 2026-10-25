/*
 * task_display_steps.c
 *
 *  Created on: Apr 3, 2025
 *      Author: tdo56
 */

#include "ssd1306.h"
#include "ssd1306_fonts.h"
#include "stdio.h"
//#include "task_calc_steps.h"
#include "calc.h"
#include "joystick_driver.h"

static char step_buffer[15];
static uint16_t units = 0;

static int held = 0;

void display_steps(void)
{
	uint16_t steps = 0;
	uint16_t goal = 0;
	steps = CALC_get_steps();
	goal = CALC_get_step_goal();

	joystickDirection_t direction_y = JOYSTICK_get_direction("y");
	if (direction_y == JOYSTICK_REST)
	{
		held = 0;
	}
	if ((direction_y == JOYSTICK_UP) && (held == 0))
	{
		units = (units + 1) % 2;
		held = 1;
	}

	ssd1306_Fill(Black);
	snprintf(step_buffer, 15, "%-5d %s", units == 0 ? steps : (steps*100)/goal, units == 0 ? "steps" : "%    ");
	ssd1306_SetCursor(0, 20);
	ssd1306_WriteString(step_buffer, Font_11x18, White);
	snprintf(step_buffer, 15, "Current Steps");
	ssd1306_SetCursor(0, 00);
	ssd1306_WriteString(step_buffer, Font_7x10, White);

	ssd1306_FillCircle(74, 55, 3, White);
	ssd1306_DrawCircle(64, 55, 3, White);
	ssd1306_DrawCircle(54, 55, 3, White);
}

