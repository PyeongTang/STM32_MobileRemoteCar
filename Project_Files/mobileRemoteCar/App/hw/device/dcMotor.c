/*
 * dcMotor.c
 *
 *  Created on: Jul 31, 2024
 *      Author: Lee JaePyeong
 */


#include "dcMotor.h"

void DCMOTOR_init(	DCMOTOR*			_INST,\
					GPIO_TypeDef* 		_IN1_GPIO_PORT,\
					uint16_t 			_IN1_GPIO_PIN,\
					GPIO_TypeDef* 		_IN2_GPIO_PORT,\
					uint16_t 			_IN2_GPIO_PIN,\
					TIM_HandleTypeDef* 	_EN_TIMER_HANDLER,\
					DCMOTOR_DEVICE_IDX	_deviceIdx
					){
	_INST->IN1_GPIO_PORT 	= _IN1_GPIO_PORT;
	_INST->IN1_GPIO_PIN  	= _IN1_GPIO_PIN;
	_INST->IN2_GPIO_PORT 	= _IN2_GPIO_PORT;
	_INST->IN2_GPIO_PIN  	= _IN2_GPIO_PIN;
	_INST->EN_TIMER_HANDLER = _EN_TIMER_HANDLER;
	_INST->deviceIdx		= _deviceIdx;
};

void DCMOTOR_setDirection(DCMOTOR* _INST, DCMOTOR_DIRECTION _DIR){
	if (_DIR == FORWARD){
		HAL_GPIO_WritePin(	_INST->IN1_GPIO_PORT,\
							_INST->IN1_GPIO_PIN,\
							GPIO_PIN_RESET);

		HAL_GPIO_WritePin(	_INST->IN2_GPIO_PORT,\
							_INST->IN2_GPIO_PIN,\
							GPIO_PIN_SET);
	}
	else if (_DIR == BACKWARD){
		HAL_GPIO_WritePin(	_INST->IN1_GPIO_PORT,\
							_INST->IN1_GPIO_PIN,\
							GPIO_PIN_SET);

		HAL_GPIO_WritePin(	_INST->IN2_GPIO_PORT,\
							_INST->IN2_GPIO_PIN,\
							GPIO_PIN_RESET);
	}
};

void DCMOTOR_emergencyBrake(DCMOTOR* _INST){
	HAL_GPIO_WritePin(	_INST->IN1_GPIO_PORT,\
						_INST->IN1_GPIO_PIN,\
						GPIO_PIN_RESET);

	HAL_GPIO_WritePin(	_INST->IN2_GPIO_PORT,\
						_INST->IN2_GPIO_PIN,\
						GPIO_PIN_RESET);
};

void DCMOTOR_setDuty(DCMOTOR* _INST, uint16_t dutyValue){
	if 	(_INST->deviceIdx == DCMOTOR_BACK){
		_INST->EN_TIMER_HANDLER->Instance->CCR1 = dutyValue;
//		__HAL_TIM_SET_COMPARE(_INST->EN_TIMER_HANDLER, TIM_CHANNEL_1, dutyValue);
	}
	else if (_INST->deviceIdx == DCMOTOR_FRONT_RIGHT){
		_INST->EN_TIMER_HANDLER->Instance->CCR2 = dutyValue;
	}
	else if (_INST->deviceIdx == DCMOTOR_FRONT_LEFT){
		_INST->EN_TIMER_HANDLER->Instance->CCR3 = dutyValue;
	}
};
