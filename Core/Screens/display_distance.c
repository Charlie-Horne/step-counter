/*
 * task_display_distance.c
 *
 *  Created on: Apr 3, 2025
 *      Author: tdo56
 */


#include <display_distance.h>
#include "ssd1306.h"
#include "ssd1306_fonts.h"
#include "stdio.h"
//#include "task_calc_steps.h"
#include "calc.h"
#include "joystick_driver.h"

#define STEP_LENGTH 0.9
#define MM_PER_YARD 0.914

static char distance_buffer[19];
static units_t units = KILOMETERS;

static uint16_t km = 0;
static uint16_t m = 0;
static uint16_t yd = 0;

static int held = 0;

void step_to_km(uint16_t steps)
{
	uint16_t distance = 0;
	distance = steps * STEP_LENGTH;
	km = distance / 1000;
	m = distance % 1000;
	snprintf(distance_buffer, 19, "%d.%03d km", km, m);
}

void step_to_yd(uint16_t steps)
{
	uint16_t distance = 0;
	distance = steps * STEP_LENGTH;
	yd = distance / MM_PER_YARD;
	snprintf(distance_buffer, 19, "%-5d yards", yd);
}

void display_distance(void)
{
	uint16_t steps = 0;

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

	steps = CALC_get_steps();

	if (units == KILOMETERS)
	{
		step_to_km(steps);
	}
	else if (units == YARDS)
	{
		step_to_yd(steps);
	}

	ssd1306_Fill(Black);
	ssd1306_SetCursor(0, 20);
	ssd1306_WriteString(distance_buffer, Font_11x18, White);
	snprintf(distance_buffer, 19, "Distance Traveled");
	ssd1306_SetCursor(0, 0);
	ssd1306_WriteString(distance_buffer, Font_7x10, White);

	ssd1306_DrawCircle(74, 55, 3, White);
	ssd1306_FillCircle(64, 55, 3, White);
	ssd1306_DrawCircle(54, 55, 3, White);
}
