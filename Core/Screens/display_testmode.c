/*
 * task_display_testmode.c
 *
 *  Created on: Apr 8, 2025
 *      Author: Charl
 */

#include "ssd1306.h"
#include "ssd1306_fonts.h"
//#include "task_joystick.h"
//#include "task_calc_steps.h"
#include <stdio.h>
#include <stdint.h>
//#include "task_imu.h"
//#include "task_peak_detection.h"


static int32_t current_stepcount = 0;
static uint16_t pot_num;



static char testmode_buffer[20];

void display_testmode(void)
{
	ssd1306_Fill(Black);
	current_stepcount = CALC_get_steps();
	/*current_stepcount = get_imu_x();
	//snprintf(testmode_buffer, 20, "%-5d steps", current_stepcount);
	snprintf(testmode_buffer, 20, "%ld", current_stepcount);
	ssd1306_SetCursor(0, 25);
	ssd1306_WriteString(testmode_buffer, Font_7x10, White);

	current_stepcount = get_imu_y();
	//snprintf(testmode_buffer, 20, "%-5d steps", current_stepcount);
	snprintf(testmode_buffer, 20, "%ld", current_stepcount);
	ssd1306_SetCursor(0, 35);
	ssd1306_WriteString(testmode_buffer, Font_7x10, White);

	current_stepcount = get_imu_z();
	//snprintf(testmode_buffer, 20, "%-5d steps", current_stepcount);
	snprintf(testmode_buffer, 20, "%ld", current_stepcount);
	ssd1306_SetCursor(0, 45);
	ssd1306_WriteString(testmode_buffer, Font_7x10, White);

	current_stepcount = get_mag();
	//snprintf(testmode_buffer, 20, "%-5d steps", current_stepcount);
	snprintf(testmode_buffer, 20, "%ld", current_stepcount);
	ssd1306_SetCursor(50, 35);
	ssd1306_WriteString(testmode_buffer, Font_7x10, White);*/

	snprintf(testmode_buffer, 20, "%-5d steps", current_stepcount);
	ssd1306_SetCursor(0, 20);
	ssd1306_WriteString(testmode_buffer, Font_11x18, White);

	snprintf(testmode_buffer, 20, "Test Mode");
	ssd1306_SetCursor(0, 0);
	ssd1306_WriteString(testmode_buffer, Font_7x10, White);

	snprintf(testmode_buffer, 20, "Set Steps:");
	ssd1306_SetCursor(0, 10);
	ssd1306_WriteString(testmode_buffer, Font_7x10, White);
}


