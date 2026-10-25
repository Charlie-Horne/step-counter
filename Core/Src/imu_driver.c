/*
 * imu_driver.c
 *
 *  Created on: May 21, 2025
 *      Author: tdo56
 */


#include "imu_driver.h"
#include "imu_lsm6ds.h"

static uint8_t acc_x_low = 0;
static uint8_t acc_x_high = 0;

static uint8_t acc_y_low = 0;
static uint8_t acc_y_high = 0;

static uint8_t acc_z_low = 0;
static uint8_t acc_z_high = 0;

static int16_t acc_x = 0;
static int16_t acc_y = 0;
static int16_t acc_z = 0;

void IMU_init(void)
{
	imu_lsm6ds_write_byte(CTRL1_XL, CTRL1_XL_HIGH_PERFORMANCE);
}

void IMU_update(void)
{
	acc_x_low = imu_lsm6ds_read_byte(OUTX_L_XL);
	acc_x_high = imu_lsm6ds_read_byte(OUTX_H_XL);

	acc_y_low = imu_lsm6ds_read_byte(OUTY_L_XL);
	acc_y_high = imu_lsm6ds_read_byte(OUTY_H_XL);

	acc_z_low = imu_lsm6ds_read_byte(OUTZ_L_XL);
	acc_z_high = imu_lsm6ds_read_byte(OUTZ_H_XL);

	acc_x = (int16_t)(acc_x_high << 8) | acc_x_low;
	acc_y = (int16_t)(acc_y_high << 8) | acc_y_low;
	acc_z = (int16_t)(acc_z_high << 8) | acc_z_low;

}

//offsets applied to raw data
int16_t IMU_get_x(void)
{
	return acc_x+600;
}

int16_t IMU_get_y(void)
{
	return acc_y+200;
}

int16_t IMU_get_z(void)
{
	return acc_z-700;
}

int32_t IMU_get_mag(void)
{
	int32_t acc_mag;
	int16_t xaxis;
	int16_t yaxis;
	int16_t zaxis;
	xaxis = IMU_get_x();
	yaxis = IMU_get_y();
	zaxis = IMU_get_z();

	acc_mag = (xaxis * xaxis + yaxis * yaxis + zaxis * zaxis)/10000;

	return acc_mag;
}
