/*
 * temp_humid_sensor.c
 *
 *  Created on: Jun 10, 2025
 *      Author: Ashli
 *
 *  File for DHT11 'abstraction'
 */

#include "temp_humid_sensor.h"
#define COM_LENGTH_S 40
#define S_TO_MS(t) (t)/1000
#define NUM_BITS 40 // DHT11 sends 40 bits (5 bytes)

void delay_us (uint16_t us, TIM_HandleTypeDef *timer)
{
	__HAL_TIM_SET_COUNTER(timer,0);  // set the counter value a 0
	while (__HAL_TIM_GET_COUNTER(timer) < us); // wait for the counter to reach the us input in the parameter
}

void set_pin_output_mode(SEVEN_SEG_PIN pin){
    GPIO_InitTypeDef GPIO_InitStruct = {0};
    GPIO_InitStruct.Pin = pin.PIN_NUM;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL; // pull up resistor is on the bread board
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(pin.PORT, &GPIO_InitStruct);
}

void set_pin_input_mode(SEVEN_SEG_PIN pin){
    GPIO_InitTypeDef GPIO_InitStruct = {0};
    GPIO_InitStruct.Pin = pin.PIN_NUM;
    GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
    GPIO_InitStruct.Pull = GPIO_NOPULL; // pull up resistor is on the bread board
    HAL_GPIO_Init(pin.PORT, &GPIO_InitStruct);
}

bool dht11_request_data(SEVEN_SEG_PIN data_pin, TIM_HandleTypeDef *timer){
    
    set_pin_output_mode(data_pin);
    HAL_GPIO_WritePin(data_pin.PORT, data_pin.PIN_NUM, 0);
    HAL_Delay(18);
    HAL_GPIO_WritePin(data_pin.PORT, data_pin.PIN_NUM,1);
    delay_us(40, timer);
    set_pin_input_mode(data_pin);
    return true;
}

bool listen_for_state(SEVEN_SEG_PIN pin, GPIO_PinState state, uint32_t timeout_us, TIM_HandleTypeDef *timer){
    // Wait for pin to change from 'state' within timeout_us microseconds
    uint32_t elapsed = 0;
    while (HAL_GPIO_ReadPin(pin.PORT, pin.PIN_NUM) == state) {
        delay_us(1, timer); // Use your delay_us, pass timer if needed
        elapsed++;
        if (elapsed >= timeout_us) {
            HD44780_Clear();
            HD44780_PrintStr("second state failed");
            HAL_Delay (1000);
            return false;
        }
    }
    return true;
}

int read_bit(SEVEN_SEG_PIN pin, TIM_HandleTypeDef *timer){
    
    delay_us(40, timer);
    int ret_val = -1;

    if (HAL_GPIO_ReadPin(pin.PORT, pin.PIN_NUM) == GPIO_PIN_SET){
        ret_val = 1;
    }else if (HAL_GPIO_ReadPin(pin.PORT, pin.PIN_NUM) == GPIO_PIN_RESET){
        ret_val = 0;
    }
    else{
        ret_val = -1;
    }
    return ret_val;
}

int* dht11_read_data(SEVEN_SEG_PIN data_pin, TIM_HandleTypeDef *timer){

    int* arr = (int*)malloc(NUM_BITS * sizeof(int));
    if (arr == NULL) {
        return NULL;
    }

    for(int i = 0; i < NUM_BITS; i++){
        delay_us(40, timer);
        int bit = read_bit(data_pin, timer);
        if (bit == -1) {
            free(arr);
            return NULL;
        }else{
            arr[i] = bit;
        }
    }
    return arr;
}

// Convert 8 bits (starting at start_index) to a byte
uint8_t bits_to_byte(const int* arr, int start_index) {
    uint8_t value = 0;
    for (int i = 0; i < 8; i++) {
        value = (value << 1) | (arr[start_index + i] & 1);
    }
    return value;
}

// Parse DHT11 bit array into humidity and temperature
// Returns true if checksum is valid, false otherwise
bool dht11_parse_data(const int* arr, float* humidity, float* temperature) {
    if (!arr || !humidity || !temperature) return false;
    uint8_t hum_int = bits_to_byte(arr, 0);
    uint8_t hum_dec = bits_to_byte(arr, 8);
    uint8_t temp_int = bits_to_byte(arr, 16);
    uint8_t temp_dec = bits_to_byte(arr, 24);
    uint8_t checksum = bits_to_byte(arr, 32);
    uint8_t sum = hum_int + hum_dec + temp_int + temp_dec;
    // if (sum != checksum) return false;
    *humidity = (float)hum_int + ((float)hum_dec) / 10.0f;
    *temperature = (float)temp_int + ((float)temp_dec) / 10.0f;
    return true;
}
