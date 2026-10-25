/*
 * task_display_setgoal.c
 *
 *  Created on: Apr 18, 2025
 *      Author: charliehorne
 */
#include "ssd1306.h"
#include "ssd1306_fonts.h"
#include "stdio.h"
#include "pot_driver.h"
//#include "task_buttons.h"

static char setgoal_buffer[15];
static uint16_t step_goal;


void display_set_goal(void)
{
	ssd1306_Fill(Black);
	step_goal = POT_get_step_goal();

	snprintf(setgoal_buffer, 15, "%-5d steps", step_goal);
	ssd1306_SetCursor(0, 20);
	ssd1306_WriteString(setgoal_buffer, Font_11x18, White);


	snprintf(setgoal_buffer, 15, "Set Goal");
	ssd1306_SetCursor(0, 00);
	ssd1306_WriteString(setgoal_buffer, Font_7x10, White);
}

