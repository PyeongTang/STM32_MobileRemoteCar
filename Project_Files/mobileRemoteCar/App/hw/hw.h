/*
 * hw.h
 *
 *  Created on: Jul 22, 2024
 *      Author: Lee JaePyeong
 */

#ifndef HW_HW_H_
#define HW_HW_H_

//Upper Layer
#include "hw_def.h"

//Include Hardware Headers Here
#include "BT_Receiver.h"
#include "dcMotor.h"
#include "mobileRemoteCar.h"
#include "usart.h"
#include "ultrasonic.h"

void HW_init();
void delay(uint32_t time_ms);
uint32_t millis(void);
uint32_t HW_abs(uint32_t x, uint32_t y);

#endif /* HW_HW_H_ */
