/*
 * adc_driver.h
 *
 *  Created on: May 21, 2025
 *      Author: tdo56
 *
 * This driver updates and retrieves the raw data from the ADC
 */

#ifndef INC_ADC_DRIVER_H_
#define INC_ADC_DRIVER_H_

#include <stdint.h>

typedef enum {
	POTENTIOMETER,
	JOYSTICK_Y,
	JOYSTICK_X
} adcData_t;

void ADC_init(void);
void ADC_update(void);
uint16_t ADC_get_data(adcData_t name);

#endif /* INC_ADC_DRIVER_H_ */
