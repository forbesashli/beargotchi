/*
 * seven_seg.h
 *
 *  Created on: Jun 7, 2025
 *      Author: Ashli
 * Header file for seven seg 'abstraction'
 */
#include "main.h"
#include "string.h"
#include "cmsis_os.h"
#include "math.h"
#ifndef INC_SEVEN_SEG_H_
#define INC_SEVEN_SEG_H_

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Inputs:
 * - SEVEN_SEG_PIN pin configuration
 * - int state, one or off, 0 for off , 1 for on
 *
 */
void writeSevenSegPin(SEVEN_SEG_PIN pin, int state);

void writeSevenSeg(int digit, int place);

void writeNumToSevenSeg(int number);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* INC_SEVEN_SEG_H_ */