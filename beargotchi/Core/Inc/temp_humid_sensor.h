/*
 * temp_humid_sensor.h
 *
 *  Created on: Jun 10, 2025
 *      Author: Ashli
 *
 *  File for DHT11 'abstraction'
 */

#include "main.h"
#include "cmsis_os.h"

#ifndef INC_TEMP_HUMID_SENSOR_H_
#define INC_TEMP_HUMID_SENSOR_H_

/**
 * listen for the 50 us and then the length of the high portion, return if it is 0 or 1 bit
 */
int read_bit(SEVEN_SEG_PIN pin);


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

void dht11_request_data(SEVEN_SEG_PIN data_pin);

/**
 * configure the pin to input and recieve the 40 bits of data
 */
int* dht11_read_data(SEVEN_SEG_PIN data_pin);

void float_to_bytes(float message, uint8_t *arr);

/**
 * calculate expected parity 
 * return 0 if passes, 1 if not equal 
 */
int dht11_check_parity(float message);

/**
 * conver the 8 bits stored in the array to a float value given the start and stop index
 */
float eight_bit_to_float(int* arr, int start_index, int end_index);

#endif /* INC_TEMP_HUMID_SENSOR_H_ */