/*
 * pot_Driver.c
 *
 *  Created on: May 21, 2025
 *      Author: tdo56
 */

#include "pot_driver.h"
#include "adc_driver.h"

void POT_init(void);

uint16_t POT_get_step_goal(void)
{
	uint16_t raw_value = ADC_get_data(POTENTIOMETER);

	// Clamp the raw value to avoid out of bounds errors
	if (raw_value < 111) {
		return 500;       // Minimum step_goal
	}
	if (raw_value > 4095) {
		return 15000;     // Maximum step_goal
	}

	uint32_t scaled = 500 + ((uint32_t)(raw_value - 111) * 14500) / 3984;
	return ((scaled + 50) / 100) * 100;
}
