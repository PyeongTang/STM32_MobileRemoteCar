/*
 * mobileRemoteCar.c
 *
 *  Created on: Jul 31, 2024
 *      Author: Lee JaePyeong
 */

#include "mobileRemoteCar.h"

// Each motors using pwm of timer 3
extern TIM_HandleTypeDef htim3;

const int INPUT_ADC_MAX = 4095;
const int INPUT_ADC_MID = 2018;
const int INPUT_ADC_MIN = 0;

const int DCMOTOR_DUTY_MAX = 4095;
const int DCMOTOR_DUTY_MID = 2048;
const int DCMOTOR_DUTY_MIN = 0;

DCMOTOR MRC_frontMotorLeft;
DCMOTOR MRC_frontMotorRight;
DCMOTOR MRC_backMotor;

DCMOTOR_DIRECTION MRC_direction;
float MRC_baseDuty;

uint16_t frontRightMotorDuty;
uint16_t frontLeftMotorDuty;
uint16_t backMotorDuty;

uint16_t accelIntensity;
float handleIntensity;

void MRC_init(){

//	Initialize Ultrasonic Sensor
  ULTRA_init();

//	Initialize Front and Back Motors
  DCMOTOR_init(&MRC_frontMotorLeft,\
		  	  FRONT_L_IN1_GPIO_Port,\
		  	  FRONT_L_IN1_Pin,\
		  	  FRONT_L_IN2_GPIO_Port,\
		  	  FRONT_L_IN2_Pin,\
		  	  &htim3,\
		  	  DCMOTOR_FRONT_LEFT);

  DCMOTOR_init(&MRC_frontMotorRight,\
		  	  FRONT_R_IN1_GPIO_Port,\
		  	  FRONT_R_IN1_Pin,\
		  	  FRONT_R_IN2_GPIO_Port,\
		  	  FRONT_R_IN2_Pin,\
		  	  &htim3,\
		  	  DCMOTOR_FRONT_RIGHT);

  DCMOTOR_init(&MRC_backMotor,\
		  	  BACK_IN1_GPIO_Port,\
		  	  BACK_IN1_Pin,\
		  	  BACK_IN2_GPIO_Port,\
		  	  BACK_IN2_Pin,\
		  	  &htim3,\
		  	  DCMOTOR_BACK);

  frontRightMotorDuty = 0;
  frontLeftMotorDuty = 0;
  backMotorDuty = 0;

//  Initialize PWM Channel of Timers
  HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_1);
  HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_2);
  HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_3);

  htim3.Instance->CCR1 = 0;
  htim3.Instance->CCR2 = 0;
  htim3.Instance->CCR3 = 0;
};

void MRC_drive(uint16_t handleValue, uint16_t accelValue){
//	AccelIntensity can be 0 ~ 2,077 or 0 ~ 2,018
	accelIntensity = HW_abs(accelValue, INPUT_ADC_MID);

//	Determine direction
	if (accelValue > INPUT_ADC_MID)
		MRC_direction = FORWARD;

	else if (accelValue <= INPUT_ADC_MID)
		MRC_direction = BACKWARD;

//	Determine acceleration
	MRC_baseDuty =  (DCMOTOR_DUTY_MIN + \
					((float)accelIntensity / (float)INPUT_ADC_MID) * \
					(float)(DCMOTOR_DUTY_MAX - DCMOTOR_DUTY_MIN));

//	Determine level of steering
	handleIntensity = (float)(handleValue - INPUT_ADC_MID) / (float)INPUT_ADC_MID;

//	Steering can be done with difference between left and right motor rpm
	frontLeftMotorDuty  = (uint16_t)(MRC_baseDuty  * (1.0 + handleIntensity));
	frontRightMotorDuty = (uint16_t)(MRC_baseDuty  * (1.0 - handleIntensity));

//	Clipping edge values
	if (frontLeftMotorDuty  > DCMOTOR_DUTY_MAX) {frontLeftMotorDuty  = DCMOTOR_DUTY_MAX;}
	if (frontLeftMotorDuty  < DCMOTOR_DUTY_MIN) {frontLeftMotorDuty  = DCMOTOR_DUTY_MIN;}
	if (frontRightMotorDuty > DCMOTOR_DUTY_MAX) {frontRightMotorDuty = DCMOTOR_DUTY_MAX;}
	if (frontRightMotorDuty < DCMOTOR_DUTY_MIN) {frontRightMotorDuty = DCMOTOR_DUTY_MIN;}

//	Determining back motor pwm value can be done with mean value of fronts
	backMotorDuty 		= (frontRightMotorDuty / 2) + (frontLeftMotorDuty / 2);

//	Set motor direction
	DCMOTOR_setDirection(&MRC_backMotor, 		MRC_direction);
	DCMOTOR_setDirection(&MRC_frontMotorRight, 	MRC_direction);
	DCMOTOR_setDirection(&MRC_frontMotorLeft, 	MRC_direction);

//	Set motor rpm
	DCMOTOR_setDuty(&MRC_frontMotorRight, 		frontRightMotorDuty);
	DCMOTOR_setDuty(&MRC_frontMotorLeft, 		frontLeftMotorDuty);
	DCMOTOR_setDuty(&MRC_backMotor, 			backMotorDuty);
};

void MRC_emergencyBrakeAllMotors(){
	DCMOTOR_emergencyBrake(&MRC_frontMotorRight);
	DCMOTOR_emergencyBrake(&MRC_frontMotorLeft);
	DCMOTOR_emergencyBrake(&MRC_backMotor);
};

void MRC_motorDrive(uint8_t idx, bool dir, uint16_t duty){
	if (idx == DCMOTOR_BACK){
		DCMOTOR_setDirection(&MRC_backMotor, 		dir);
		DCMOTOR_setDuty		(&MRC_backMotor, 		duty);
	}
	else if (idx == DCMOTOR_FRONT_RIGHT){
		DCMOTOR_setDirection(&MRC_frontMotorRight, 	dir);
		DCMOTOR_setDuty		(&MRC_frontMotorRight, 	duty);
	}
	else if (idx == DCMOTOR_FRONT_LEFT){
		DCMOTOR_setDirection(&MRC_frontMotorLeft, 	dir);
		DCMOTOR_setDuty		(&MRC_frontMotorLeft, 	duty);
	}
}

uint16_t MRC_getFrontRightMotorDuty(){
	return frontRightMotorDuty;
}

uint16_t MRC_getFrontLeftMotorDuty(){
	return frontLeftMotorDuty;
}

uint16_t MRC_getBackMotorDuty(){
	return backMotorDuty;
}

uint8_t MRC_getDistance(){
	return ULTRA_getDistance();
}
