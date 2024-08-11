/*
 * ultrasonic.c
 *
 *  Created on: Aug 1, 2024
 *      Author: Lee JaePyeong
 */


#include "ultrasonic.h"

uint16_t inputCapturedRisingCounterValue;
uint16_t inputCapturedFallingCounterValue;
uint16_t echoHighCounterValue;
uint8_t captureFlag;
uint8_t distance;

void ULTRA_init(){
	inputCapturedRisingCounterValue = 0;
	inputCapturedFallingCounterValue = 0;
	echoHighCounterValue = 0;
	captureFlag = 0;
	distance = 0;
//	TRIG
	HAL_TIM_Base_Start_IT(&htim1);
	HAL_TIM_PWM_Start_IT(&htim1, TIM_CHANNEL_3);
//	EHCO
	HAL_TIM_Base_Start_IT(&htim2);
	HAL_TIM_IC_Start_IT(&htim2, TIM_CHANNEL_2);
};

void HAL_TIM_IC_CaptureCallback(TIM_HandleTypeDef *htim){
	if (htim->Channel == HAL_TIM_ACTIVE_CHANNEL_2){
		if (captureFlag == 0){
			inputCapturedRisingCounterValue = HAL_TIM_ReadCapturedValue(&htim2, TIM_CHANNEL_2);
			captureFlag = 1;
			__HAL_TIM_SET_CAPTUREPOLARITY(&htim2, TIM_CHANNEL_2, TIM_INPUTCHANNELPOLARITY_FALLING);
		}
		else if (captureFlag == 1){
			inputCapturedFallingCounterValue = HAL_TIM_ReadCapturedValue(&htim2, TIM_CHANNEL_2);
			__HAL_TIM_SET_COUNTER(&htim2, 0);
			if (inputCapturedFallingCounterValue > inputCapturedRisingCounterValue){
				echoHighCounterValue = inputCapturedFallingCounterValue - inputCapturedRisingCounterValue;
			}
			else if (inputCapturedRisingCounterValue > inputCapturedFallingCounterValue){
				echoHighCounterValue = 0xFFFF - inputCapturedRisingCounterValue + inputCapturedFallingCounterValue;
			}
			distance = echoHighCounterValue/58;
			captureFlag = 0;
			__HAL_TIM_SET_CAPTUREPOLARITY(&htim2, TIM_CHANNEL_2, TIM_INPUTCHANNELPOLARITY_RISING);
			__HAL_TIM_DISABLE_IT(&htim2, TIM_IT_CC2);
		}
	}
};

void HAL_TIM_OC_DelayElapsedCallback(TIM_HandleTypeDef *htim){
	if (htim->Instance == TIM1){
		if (htim->Channel == HAL_TIM_ACTIVE_CHANNEL_3){
			__HAL_TIM_ENABLE_IT(&htim2, TIM_IT_CC2);
		}
	}
};

uint8_t ULTRA_getDistance(){
	return distance;
};
