/*
 * ap.c
 *
 *  Created on: Jul 22, 2024
 *      Author: Lee JaePyeong
 */

#include "ap.h"

uint16_t handleValue;
uint16_t accelValue;
uint8_t distanceValue;

void AP_setup(){
	HW_init();

//	Initialized Value set by threshold + 1 for preventing deadlock
	distanceValue = EMERGENCY_BRAKE_TH + 1;
};

void AP_loop(){
	while (1){
//		Ultrasonic sensor working with PWM Triggering
		distanceValue = MRC_getDistance();
		if (distanceValue <= EMERGENCY_BRAKE_TH){
			MRC_emergencyBrakeAllMotors();
		}
		else{
//			Get ADC values from controller
			handleValue = MRC_BT_getHandleValue();
			accelValue 	= MRC_BT_getAccelValue();

//			Accelerating and Steering
			MRC_drive(handleValue, accelValue);
		}
		HAL_Delay(10);
	}
};
