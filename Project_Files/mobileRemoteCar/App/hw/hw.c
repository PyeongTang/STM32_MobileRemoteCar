/*
 * hw.c
 *
 *  Created on: Jul 22, 2024
 *      Author: Lee JaePyeong
 */

#include "hw.h"

//Declared at uart.c
//Declared Externally for initialize

void HW_init(){
	MRC_BT_init();
	MRC_init();
}

void delay(uint32_t time_ms){
	HAL_Delay(time_ms);
};

uint32_t millis(void){
	return HAL_GetTick();
};

uint32_t HW_abs(uint32_t x, uint32_t y){
	if (x >= y) return x - y;
	else 		return y - x;
}
