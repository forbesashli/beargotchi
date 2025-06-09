/*
 * seven_seg.c
 *
 *  Created on: Jun 7, 2025
 *      Author: Ashli
 *
 *  File for 7 segment display
 */

#include "seven_seg.h"


void writeSevenSegPin(SEVEN_SEG_PIN pin, int state) {
    HAL_GPIO_WritePin(pin.PORT, pin.PIN_NUM, state);
}
