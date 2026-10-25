/*
 * task_led.c
 *
 *  Created on: Mar 19, 2025
 *      Author: tdo56
 */


#include <led.h>
#include "rgb.h"
#include "button_driver.h"
#include "calc.h"

static uint16_t steps = 0;
static uint16_t goal = 0;
static uint16_t percentage = 0;

void LED_init(void)
{
	rgb_colour_all_on();
}

void LED_update(void)
{
	steps = CALC_get_steps();
	goal = CALC_get_step_goal();

	percentage = (steps*100)/goal;

    if (percentage >= 75)
    {
        rgb_led_on(RGB_DOWN);
    }
    else
    {
    	rgb_led_off(RGB_DOWN);
    }

    if (percentage >= 50)
    {
		rgb_led_on(RGB_RIGHT);
	}
	else
	{
		rgb_led_off(RGB_RIGHT);
	}

    if (percentage >= 100)
    {
		rgb_led_on(RGB_LEFT);
	}
	else
	{
		rgb_led_off(RGB_LEFT);
	}
}
