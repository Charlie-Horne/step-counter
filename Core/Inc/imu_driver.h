/*
 * imu_driver.h
 *
 *  Created on: May 21, 2025
 *      Author: tdo56
 */

#ifndef INC_IMU_DRIVER_H_
#define INC_IMU_DRIVER_H_

#include <stdint.h>

void IMU_init(void);
void IMU_update(void);
int16_t IMU_get_x(void);
int16_t IMU_get_y(void);
int16_t IMU_get_z(void);
int32_t IMU_get_mag(void);

#endif /* INC_IMU_DRIVER_H_ */
