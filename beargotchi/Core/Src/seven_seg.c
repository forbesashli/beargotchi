/*
 * seven_seg.c
 *
 *  Created on: Jun 7, 2025
 *      Author: Ashli
 *
 *  File for 7 segment display 'abstraction'
 */

#include "seven_seg.h"

#define NUM_SEGMENTS 4
// Segment encoding: 0bDP_G_F_E_D_C_B_A
const uint8_t seven_seg_digits[10] = {
    0b11000000, // 0
    0b11111001, // 1
    0b10100100, // 2
    0b10110000, // 3
    0b10011001, // 4
    0b10010010, // 5
    0b10000010, // 6
    0b11111000, // 7
    0b10000000, // 8
    0b10010000  // 9
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

void writeSevenSeg(int digit, int place){

    uint8_t shift = seven_seg_digits[digit];
    for (int i = 0 ; i < 8; i++){
        writeSevenSegPin(digit_pins[i], (shift >> i) & 1);
    }
    for (int i = 0; i < NUM_SEGMENTS; i++){
        if (i == place){
            writeSevenSegPin(place_planes[i], 1);
        }
        else{
            writeSevenSegPin(place_planes[i], 0);
        }
    }
}

void writeNumToSevenSeg(int number){
    int display = number;
    int divisor;
    int digit; 
    for (int i = 3 ; i >=0; i--){
        divisor = pow(10,i);
        digit = display/divisor;
        display = display%divisor;

        writeSevenSeg(digit, i);
        // osDelay(4);
        HAL_Delay(4); // Delay to allow the display to update
    }
}