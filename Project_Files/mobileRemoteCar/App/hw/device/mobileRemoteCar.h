/*
 * mobileRemoteCar.h
 *
 *  Created on: Jul 31, 2024
 *      Author: Lee JaePyeong
 */

#ifndef HW_DEVICE_MOBILEREMOTECAR_H_
#define HW_DEVICE_MOBILEREMOTECAR_H_

#include "hw.h"

// Threshold of direction comes from ultrasonic sensor
#define EMERGENCY_BRAKE_TH 10

void MRC_init();
void MRC_drive(uint16_t handleValue, uint16_t accelValue);
void MRC_motorDrive(uint8_t idx, bool dir, uint16_t duty);
void MRC_emergencyBrakeAllMotors();
uint16_t MRC_getFrontRightMotorDuty();
uint16_t MRC_getFrontLeftMotorDuty();
uint16_t MRC_getBackMotorDuty();
uint8_t MRC_getDistance();
#endif /* HW_DEVICE_MOBILEREMOTECAR_H_ */
