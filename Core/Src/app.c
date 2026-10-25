/*
 * app.c
 *
 *  Created on: Feb 27, 2025
 *      Author: tdo56
 */

#include "led.h"
#include "pwm_driver.h"
#include "app.h"
#include "gpio.h"
#include "tim.h"
#include "kernel.h"
#include "task_blinky.h"
#include "task_serial.h"
#include "peak_detection.h"
#include "button_driver.h"
#include "display.h"
#include "adc_driver.h"
#include "joystick_driver.h"
#include "imu_driver.h"
#include "calc.h"
#include "state.h"


#define BLINK_LED_FREQUENCY_HZ 2
#define DISPLAY_FREQUENCY_HZ 12
#define SERIAL_PRINT_FREQUENCY_HZ 20
#define PWM_UPDATE_FREQUENCY_HZ 6
#define CALC_STEPS_FREQUENCY_HZ 80
#define USER_INPUT_UPDATE_FREQUENCY 1000

void app_main(void)
{
	PD_init();
	BUTTON_init();
	ADC_init();
	JOYSTICK_init();
	DISPLAY_init();
	IMU_init();
	LED_init();
	PWM_init();

	KERNEL_init();

	KERNEL_add_task(blinky_task_execute, BLINK_LED_FREQUENCY_HZ);
	KERNEL_add_task(ADC_update, USER_INPUT_UPDATE_FREQUENCY);
	KERNEL_add_task(DISPLAY_update, DISPLAY_FREQUENCY_HZ);
	KERNEL_add_task(IMU_update, USER_INPUT_UPDATE_FREQUENCY);
	KERNEL_add_task(CALC_update, CALC_STEPS_FREQUENCY_HZ);
	KERNEL_add_task(BUTTON_update_state, USER_INPUT_UPDATE_FREQUENCY);
	KERNEL_add_task(serial_task_execute, SERIAL_PRINT_FREQUENCY_HZ);
	KERNEL_add_task(PWM_update, PWM_UPDATE_FREQUENCY_HZ);
	KERNEL_add_task(LED_update, DISPLAY_FREQUENCY_HZ);
	KERNEL_add_task(STATE_update, USER_INPUT_UPDATE_FREQUENCY);

	while (1)
	  {
		KERNEL_run();
	  }
}

