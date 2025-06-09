/*
 * seven_seg.h
 *
 *  Created on: Jun 7, 2025
 *      Author: Ashli
 * Header file for seven seg 'abstraction'
 */
#include "main.h"
#include "string.h"
#ifndef INC_SEVEN_SEG_H_
#define INC_SEVEN_SEG_H_

typedef struct {
    GPIO_TypeDef* PORT;   // pointer to the GPIO port (e.g., GPIOB)
    uint16_t PIN_NUM;     // the pin number (e.g., GPIO_PIN_9)
} SEVEN_SEG_PIN;


/**
 * Inputs:
 * - SEVEN_SEG_PIN pin configuration
 * - int state, one or off, 0 for off , 1 for on
 *
 */
void writeSevenSegPin(SEVEN_SEG_PIN pin, int state);

#endif /* INC_SEVEN_SEG_H_ */