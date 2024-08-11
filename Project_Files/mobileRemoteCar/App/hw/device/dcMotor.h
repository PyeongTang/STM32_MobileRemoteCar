/*
 * dcMotor.h
 *
 *  Created on: Jul 31, 2024
 *      Author: Lee JaePyeong
 */

#ifndef HW_DEVICE_DCMOTOR_H_
#define HW_DEVICE_DCMOTOR_H_

#include "hw.h"

#define DCMOTOR_MAX_DUTY 4095
#define DCMOTOR_MIN_DUTY 1433
#define DCMOTOR_NUM_STEP DCMOTOR_MAX_DUTY - DCMOTOR_MIN_DUTY
#define DCMOTOR_NEUTRAL_DUTY  (DCMOTOR_MAX_DUTY + DCMOTOR_MIN_DUTY) / 2

typedef struct{
	GPIO_TypeDef* 		IN1_GPIO_PORT;
	uint16_t 			IN1_GPIO_PIN;
	GPIO_PinState		IN1_PIN_STATE;

	GPIO_TypeDef* 		IN2_GPIO_PORT;
	uint16_t 			IN2_GPIO_PIN;
	GPIO_PinState		IN2_PIN_STATE;

	TIM_HandleTypeDef*	EN_TIMER_HANDLER;
	uint16_t			MAX_DUTY_VALUE;

	uint8_t				deviceIdx; // Same as TimerChannel
} DCMOTOR;

typedef enum{
	BACKWARD = 0,
	FORWARD
} DCMOTOR_DIRECTION;

typedef enum{
	DCMOTOR_BACK = 1,
	DCMOTOR_FRONT_RIGHT,
	DCMOTOR_FRONT_LEFT
} DCMOTOR_DEVICE_IDX;

void DCMOTOR_init(	DCMOTOR*			_INST,\
					GPIO_TypeDef* 		_IN1_GPIO_PORT,\
					uint16_t 			_IN1_GPIO_PIN,\
					GPIO_TypeDef* 		_IN2_GPIO_PORT,\
					uint16_t 			_IN2_GPIO_PIN,\
					TIM_HandleTypeDef* 	_EN_TIMER_HANDLER,\
					DCMOTOR_DEVICE_IDX	_deviceIdx
					);

void DCMOTOR_setDirection(DCMOTOR* _INST, DCMOTOR_DIRECTION _DIR);
void DCMOTOR_emergencyBrake(DCMOTOR* _INST);
void DCMOTOR_setDuty(DCMOTOR* _INST, uint16_t dutyValue);

#endif /* HW_DEVICE_DCMOTOR_H_ */
