/*
 * task_pwm.c
 *
 *  Created on: Mar 19, 2025
 *      Author: tdo56
 */


#include <pwm_driver.h>
#include "pwm.h"
#include "tim.h"
#include "calc.h"

static int dutyIndex = 0;
static int buzzerIndex = 26;
static uint16_t steps = 0;
static uint16_t goal = 0;
static int beep = 0;

void PWM_init(void)
{
	HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_3);
	HAL_TIM_PWM_Start(&htim16, TIM_CHANNEL_1);
    pwm_setDutyCycle(&htim2, TIM_CHANNEL_3, dutyIndex * 10);
    pwm_setDutyCycle(&htim2, TIM_CHANNEL_3, 0);
}

void PWM_update(void)
{
    steps = CALC_get_steps();
    goal = CALC_get_step_goal();

	dutyIndex = ((steps*100)/goal)*4;
	dutyIndex = (dutyIndex > 100) ? 100 : dutyIndex;
	pwm_setDutyCycle(&htim2, TIM_CHANNEL_3, dutyIndex);

	if (steps >= goal) {
	    if (beep < 6) {
	        pwm_setDutyCycle(&htim16, TIM_CHANNEL_1, buzzerIndex - beep);
	        beep++;
	    } else {
	        pwm_setDutyCycle(&htim16, TIM_CHANNEL_1, 0);
	    }
	} else {
	    beep = 0;
	    pwm_setDutyCycle(&htim16, TIM_CHANNEL_1, 0);
	}
}
