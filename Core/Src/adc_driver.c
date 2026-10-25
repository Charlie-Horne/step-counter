/*
 * adc_driver.c
 *
 *  Created on: May 21, 2025
 *      Author: tdo56
 */


#include "adc_driver.h"
#include "adc.h"

static uint16_t raw_data[3] = {0};

void ADC_init(void)
{
	HAL_ADC_Start_DMA(&hadc1, (uint32_t*)raw_data, 3);
}

void ADC_update(void)
{
	HAL_ADC_Start_DMA(&hadc1, (uint32_t*)raw_data, 3);
}

uint16_t ADC_get_data(adcData_t name)
{
	return raw_data[name];
}
