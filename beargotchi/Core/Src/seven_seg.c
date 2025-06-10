/*
 * seven_seg.c
 *
 *  Created on: Jun 7, 2025
 *      Author: Ashli
 *
 *  File for 7 segment display 'abstraction'
 */

#include "seven_seg.h"

// Segment encoding: 0bDP_G_F_E_D_C_B_A
const uint8_t seven_seg_digits[10] = {
    0b00111111, // 0
    0b00000110, // 1
    0b01011011, // 2
    0b01001111, // 3
    0b01100110, // 4
    0b01101101, // 5
    0b01111101, // 6
    0b00000111, // 7
    0b01111111, // 8
    0b01101111  // 9
};

static const SEVEN_SEG_PIN digit_pins[8] = {
    {.PORT = GPIOA,.PIN_NUM = GPIO_PIN_15}, // A
    {.PORT = GPIOB,.PIN_NUM = GPIO_PIN_8}, // B
    {.PORT = GPIOB,.PIN_NUM = GPIO_PIN_5}, // C
    {.PORT = GPIOA,.PIN_NUM = GPIO_PIN_4}, // D
    {.PORT = GPIOF,.PIN_NUM = GPIO_PIN_3}, // E
    {.PORT = GPIOB,.PIN_NUM = GPIO_PIN_12}, // F
    {.PORT = GPIOD,.PIN_NUM = GPIO_PIN_14}, // G
    {.PORT = GPIOD,.PIN_NUM = GPIO_PIN_15}, // Dp
};

static const SEVEN_SEG_PIN place_planes[4] = {
    {.PORT = GPIOB,.PIN_NUM = GPIO_PIN_9}, // D1
    {.PORT = GPIOC,.PIN_NUM = GPIO_PIN_6}, // D2
    {.PORT = GPIOB, .PIN_NUM = GPIO_PIN_15}, //D3
    {.PORT = GPIOC,.PIN_NUM = GPIO_PIN_7} // D4
};

void writeSevenSegPin(SEVEN_SEG_PIN pin, int state) {
    HAL_GPIO_WritePin(pin.PORT, pin.PIN_NUM, state);
}

void writeOnePlaceOne(void){
    writeSevenSegPin(digit_pins[0], 1);
    writeSevenSegPin(digit_pins[1], 0);
    writeSevenSegPin(digit_pins[2], 0);
    writeSevenSegPin(digit_pins[3], 1);
    writeSevenSegPin(digit_pins[4], 1);
    writeSevenSegPin(digit_pins[5], 1);
    writeSevenSegPin(digit_pins[6], 1);
    writeSevenSegPin(digit_pins[7], 1);
    writeSevenSegPin(place_planes[0], 0);
    writeSevenSegPin(place_planes[1], 0);
    writeSevenSegPin(place_planes[2], 0);
    writeSevenSegPin(place_planes[3], 1);  
}

void writeTwoPlaceTwo(void){
    writeSevenSegPin(digit_pins[0], 0);
    writeSevenSegPin(digit_pins[1], 0);
    writeSevenSegPin(digit_pins[2], 1);
    writeSevenSegPin(digit_pins[3], 0);
    writeSevenSegPin(digit_pins[4], 0);
    writeSevenSegPin(digit_pins[5], 1);
    writeSevenSegPin(digit_pins[6], 0);
    writeSevenSegPin(digit_pins[7], 1);
    writeSevenSegPin(place_planes[0], 0);
    writeSevenSegPin(place_planes[1], 0);
    writeSevenSegPin(place_planes[2], 1);
    writeSevenSegPin(place_planes[3], 0);  
}

void writeThreePlaceThree(void){
    writeSevenSegPin(digit_pins[0], 0);
    writeSevenSegPin(digit_pins[1], 0);
    writeSevenSegPin(digit_pins[2], 0);
    writeSevenSegPin(digit_pins[3], 0);
    writeSevenSegPin(digit_pins[4], 1);
    writeSevenSegPin(digit_pins[5], 1);
    writeSevenSegPin(digit_pins[6], 0);
    writeSevenSegPin(digit_pins[7], 1);
    writeSevenSegPin(place_planes[0], 0);
    writeSevenSegPin(place_planes[1], 1);
    writeSevenSegPin(place_planes[2], 0);
    writeSevenSegPin(place_planes[3], 0);  
}


void writeFourPlaceFour(void){
    writeSevenSegPin(digit_pins[0], 1);
    writeSevenSegPin(digit_pins[1], 0);
    writeSevenSegPin(digit_pins[2], 0);
    writeSevenSegPin(digit_pins[3], 1);
    writeSevenSegPin(digit_pins[4], 1);
    writeSevenSegPin(digit_pins[5], 0);
    writeSevenSegPin(digit_pins[6], 0);
    writeSevenSegPin(digit_pins[7], 1);
    writeSevenSegPin(place_planes[0], 1);
    writeSevenSegPin(place_planes[1], 0);
    writeSevenSegPin(place_planes[2], 0);
    writeSevenSegPin(place_planes[3], 0);  
}