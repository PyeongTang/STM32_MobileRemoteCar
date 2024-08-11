/*
 * bluetoothSlave.h
 *
 *  Created on: Aug 2, 2024
 *      Author: Lee JaePyeong
 */

#ifndef HW_DEVICE_BT_RECEIVER_H_
#define HW_DEVICE_BT_RECEIVER_H_

#include "hw.h"

void MRC_BT_init();
uint16_t MRC_BT_getHandleValue();
uint16_t MRC_BT_getAccelValue();

#endif /* HW_DEVICE_BT_RECEIVER_H_ */
