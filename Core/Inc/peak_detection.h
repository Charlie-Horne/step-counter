/*
 * peak_detection.h
 *
 *  Created on: May 21, 2025
 *      Author: tdo56
 */

#ifndef INC_PEAK_DETECTION_H_
#define INC_PEAK_DETECTION_H_

#include <stdbool.h>

void PD_init(void);
bool PD_check_peak(int32_t max_threshold);

#endif /* INC_PEAK_DETECTION_H_ */
