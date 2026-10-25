/*
 * task_display_goal.c
 *
 *  Created on: Apr 3, 2025
 *      Author: tdo56
 */


#include "ssd1306.h"
#include "ssd1306_fonts.h"
#include "stdio.h"
//#include "task_joystick.h"
//#include "task_buttons.h"
//#include "task_calc_steps.h"
#include "calc.h"

static char goal_buffer[15];
static uint16_t step_goal;
static uint16_t steps;

void display_goal(void)
{
	ssd1306_Fill(Black);
	step_goal = CALC_get_step_goal();
	steps = CALC_get_steps();
	snprintf(goal_buffer, 15, "%-5d/%-5d", steps, step_goal);
	ssd1306_SetCursor(0, 20);
	ssd1306_WriteString(goal_buffer, Font_11x18, White);
	snprintf(goal_buffer, 15, "Goal Progress");
	ssd1306_SetCursor(0, 00);
	ssd1306_WriteString(goal_buffer, Font_7x10, White);

	ssd1306_DrawCircle(74, 55, 3, White);
	ssd1306_DrawCircle(64, 55, 3, White);
	ssd1306_FillCircle(54, 55, 3, White);
}
