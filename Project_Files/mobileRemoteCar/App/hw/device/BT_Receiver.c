/*
 * bluetoothSlave.c
 *
 *  Created on: Aug 2, 2024jmnion
 *      Author: Lee JaePyeong
 */

#include "BT_Receiver.h"

uint8_t MRC_rxBuffer[4] = {0,};
volatile uint16_t MRC_handleValue = 0;
volatile uint16_t MRC_accelValue = 0;

void MRC_BT_init(){
//	Abortion of Rx IT needs to BT works repeatedly
	HAL_UART_AbortReceive_IT(&huart6);
	HAL_UART_Receive_IT(&huart6, MRC_rxBuffer, sizeof(MRC_rxBuffer));
};

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart){
	HAL_UART_AbortReceive_IT(&huart6);
	if(huart->Instance == USART6){
//		Constructing 16-bits data from ADC
		MRC_accelValue 	 = (MRC_rxBuffer[1] << 8 | MRC_rxBuffer[0]);
		MRC_handleValue  = (MRC_rxBuffer[3] << 8 | MRC_rxBuffer[2]);
		HAL_UART_Receive_IT(&huart6, MRC_rxBuffer, sizeof(MRC_rxBuffer));
	}
};

uint16_t MRC_BT_getHandleValue(){
	return MRC_handleValue;
};

uint16_t MRC_BT_getAccelValue(){
	return MRC_accelValue;
};
