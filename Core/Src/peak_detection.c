/*
 * peak_detection.c
 *
 *  Created on: May 21, 2025
 *      Author: tdo56
 */

#include <stdint.h>
#include <stdbool.h>
#include "imu_driver.h"
#include "stm32c0xx_hal.h"

#define WINDOW_SIZE     16
#define COOLDOWN_MS    250

static int32_t  mag_buffer[WINDOW_SIZE];
static uint8_t  buf_index;
static bool     buffer_filled;
static uint32_t last_detection_ms = 0;

void PD_init(void) {
    for (uint8_t i = 0; i < WINDOW_SIZE; i++)
    {
        mag_buffer[i] = 0;
    }

    buf_index         = 0;
    buffer_filled     = false;
    last_detection_ms = 0;
}

bool PD_check_peak(int32_t max_threshold) {
    uint32_t now = HAL_GetTick();
    int32_t mag = 0;

    mag = IMU_get_mag();

    mag_buffer[buf_index++] = mag;
    if (buf_index >= WINDOW_SIZE) {
        buf_index = 0;
        buffer_filled = true;
    }

    if (!buffer_filled) {
        return false;
    }

    if ((now - last_detection_ms) < COOLDOWN_MS) {
        return false;
    }

    if (mag > max_threshold) {
        last_detection_ms = now;
        return true;
    }

    return false;
}
