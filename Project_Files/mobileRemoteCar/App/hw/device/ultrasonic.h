/*
 * ultrasonic.h
 *
 *  Created on: Aug 1, 2024
 *      Author: Lee JaePyeong
 */

#ifndef HW_DEVICE_ULTRASONIC_H_
#define HW_DEVICE_ULTRASONIC_H_

#include "hw.h"
#include "tim.h"

extern uint16_t inputCapturedRisingCounterValue;
extern uint16_t inputCapturedFallingCounterValue;
extern uint16_t echoHighCounterValue;
extern uint8_t captureFlag;
extern uint8_t distance;

void ULTRA_init();
void HAL_TIM_IC_CaptureCallback(TIM_HandleTypeDef *htim);
void HAL_TIM_OC_DelayElapsedCallback(TIM_HandleTypeDef *htim);
uint8_t ULTRA_getDistance();

#endif /* HW_DEVICE_ULTRASONIC_H_ */
