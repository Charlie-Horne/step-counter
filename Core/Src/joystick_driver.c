/*
 * joystick_driver.c
 *
 *  Created on: May 21, 2025
 *      Author: tdo56
 */


#include "joystick_driver.h"
#include "adc_driver.h"
#include <string.h>
#include <stdlib.h>

static uint16_t joystick_centers[2];
static uint16_t joystick_deadzone = 700;
static uint16_t joystick_min[2] = {340, 400};
static uint16_t joystick_max[2] = {4080, 4000};

static uint16_t x_raw = 0;
static uint16_t y_raw = 0;

void JOYSTICK_init(void)
{
	joystick_centers[0] = ADC_get_data(JOYSTICK_X);
	joystick_centers[1] = ADC_get_data(JOYSTICK_Y);
}

joystickDirection_t JOYSTICK_get_direction(char* axis)
{
	ADC_update();
	x_raw = ADC_get_data(JOYSTICK_X);
	y_raw = ADC_get_data(JOYSTICK_Y);

	joystickDirection_t direction;

	if (strcmp(axis, "x") == 0)
	{
		if (x_raw > (joystick_centers[0] + joystick_deadzone))
		{
			direction = JOYSTICK_LEFT;
		}
		else if (x_raw < (joystick_centers[0] - joystick_deadzone))
		{
			direction = JOYSTICK_RIGHT;
		}
		else
		{
			direction = JOYSTICK_REST;
		}
	}

	if (strcmp(axis, "y") == 0)
	{
		if (y_raw > (joystick_centers[1] + joystick_deadzone))
		{
			direction = JOYSTICK_DOWN;
		}
		else if (y_raw < (joystick_centers[1] - joystick_deadzone))
		{
			direction = JOYSTICK_UP;
		}
		else
		{
			direction = JOYSTICK_REST;
		}
	}

	return direction;
}

uint8_t JOYSTICK_get_displacement(char* axis)
{
    int16_t raw_value;
    uint8_t axis_index;

    if (strcmp(axis, "x") == 0)
    {
        axis_index = 2;
        raw_value = x_raw;
    }
    else if (strcmp(axis, "y") == 0)
    {
        axis_index = 1;
        raw_value = y_raw;
    }
    else
    {
        return 0;
    }

    if (abs(raw_value - joystick_centers[axis_index]) <= joystick_deadzone)
    {
        return 0;
    }

    uint16_t percentage = 0;

    if (raw_value > joystick_centers[axis_index]) /*Positive displacement*/
    {
        int16_t effectiveCenter = joystick_centers[axis_index] + joystick_deadzone;
        int16_t effectiveRange = joystick_max[axis_index] - effectiveCenter;
        if (effectiveRange > 0)
        {
            percentage = (uint16_t)(100 * (raw_value - effectiveCenter) / effectiveRange);
        }
    }
    else /*Negative Displacement*/
    {
        int16_t effectiveCenter = joystick_centers[axis_index] - joystick_deadzone;
        int16_t effectiveRange = effectiveCenter - joystick_min[axis_index];
        if (effectiveRange > 0)
        {
            percentage = (uint16_t)(100 * (effectiveCenter - raw_value) / effectiveRange);
        }
    }

    if (percentage > 100)
    {
        percentage = 100;
    }

    return percentage;
}
