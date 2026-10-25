/*
 * task_serial.h
 *
 *  Created on: Mar 19, 2025
 *      Author: tdo56
 */

#include "stdio.h"
#include "stdlib.h"
#include "task_serial.h"
#include "usart.h"
#include "buttons.h"
#include "joystick_driver.h"
#include "imu_driver.h"
#include "peak_detection.h"

uint8_t serialToggle = 1;
char imu_buffer[20];

int32_t imu_mag;
uint16_t displacement;
uint8_t get_serial_toggle(void)
{
	return serialToggle;
}
void serial_task_execute(void)
{
	if (serialToggle == 1)
	{
		imu_mag = IMU_get_mag();

		//snprintf(imu_buffer, 16, "magnitude:");
		//HAL_UART_Transmit(&huart2, imu_buffer, 16, HAL_MAX_DELAY);
		snprintf(imu_buffer, 20, ">mag:%d\r\n", imu_mag);
		HAL_UART_Transmit(&huart2, imu_buffer, 20, HAL_MAX_DELAY);

		/*snprintf(imu_buffer, 20, "%d", PD_check_peak(40000));
		HAL_UART_Transmit(&huart2, imu_buffer, 20, HAL_MAX_DELAY);*/
	}
}
