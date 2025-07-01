/*
 * temp_humid_sensor.h
 *
 *  Created on: Jun 10, 2025
 *      Author: Ashli
 *
 *  File for DHT11 'abstraction', note: need a hardware based timer, because the ticks in are in ms and need us precision
 */

#include "main.h"
#include "cmsis_os.h"

#ifndef INC_TEMP_HUMID_SENSOR_H_
#define INC_TEMP_HUMID_SENSOR_H_

void delay_us (uint16_t us, TIM_HandleTypeDef *timer);


/**
 * listen for the 50 us and then the length of the high portion, return if it is 0 or 1 bit
 */
int read_bit(SEVEN_SEG_PIN pin, TIM_HandleTypeDef *timer);


/**
 * Set the pin to output mode (for cleanliness)
 */

void set_pin_output_mode(SEVEN_SEG_PIN pin);

/**
 * Set the pin to input mode (for cleanliness)
 */

void set_pin_input_mode(SEVEN_SEG_PIN pin);

/**
 * have MCU take control of the line, and pull it down for 18 ms to tell the sensor it wants data
 */

bool dht11_request_data(SEVEN_SEG_PIN data_pin, TIM_HandleTypeDef *timer);

/**
 * configure the pin to input and recieve the 40 bits of data
 */
int* dht11_read_data(SEVEN_SEG_PIN data_pin, TIM_HandleTypeDef *timer);

/**
 * Convert 8 bits stored in the array to a byte value given the start index
 */
uint8_t bits_to_byte(const int* arr, int start_index);

/**
 * Parse the 40-bit DHT11 data array into humidity and temperature values.
 * Returns true if checksum is valid, false otherwise.
 */
bool dht11_parse_data(const int* arr, float* humidity, float* temperature);

#endif /* INC_TEMP_HUMID_SENSOR_H_ */