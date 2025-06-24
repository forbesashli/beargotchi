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
#define NUM_BITS 32 // 4*8

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

void dht11_request_data(SEVEN_SEG_PIN data_pin){
    
    set_pin_output_mode(data_pin);

    uint32_t tick;
 
    tick = osKernelGetTickCount(); 
    tick += 180;
    HAL_GPIO_WritePin(data_pin.PORT, data_pin.PIN_NUM, 0);
    osDelayUntil(tick);
    return true;
}

bool listen_for_state(SEVEN_SEG_PIN pin, GPIO_PinState state, uint32_t time){
    
    uint32_t start_tick = osKernelGetTickCount(); 

    // time in us 
    const uint32_t timeout = time - osKernelGetSysTimerFreq() / 1000000u;

    while(HAL_GPIO_ReadPin(pin.PORT, pin.PIN_NUM) == state){
        if (osKernelGetTickCount() - start_tick  > timeout){
            return false;
        }
    }
    return true;

}

int read_bit(SEVEN_SEG_PIN pin){
    
    uint32_t tick_count = 0;
    uint64_t tick_frequency = osKernelGetSysTimerFreq(); // Use uint64_t for potential larger frequencies
    uint64_t microseconds;
    uint32_t start_tick = osKernelGetTickCount();
    while(HAL_GPIO_ReadPin(pin.PORT, pin.PIN_NUM) == GPIO_PIN_SET){
        tick_count++;
    }

    uint32_t time= (tick_count - start_tick)*1000000 / tick_frequency;

    if (time < 26){
        return -1; // bad
    }
    else if (time < 30){
        return 0;
    }
    else if (time < 70){
        return 1;
    }
    else{
        return -1; // bad
    }
}

int* dht11_read_data(SEVEN_SEG_PIN data_pin){
    set_pin_input_mode(data_pin);


    listen_for_state(data_pin, GPIO_PIN_RESET, 80);
    listen_for_state(data_pin, GPIO_PIN_SET, 80);

    int* arr = (int*)malloc(NUM_BITS * sizeof(int));
    if (arr == NULL) {
       
        return NULL;
    }

    for(int i = 0; i < NUM_BITS; i++){
        if (listen_for_state(data_pin, GPIO_PIN_RESET, 50)){
            arr[i] = read_bit(data_pin); //read in the bit 
        }
        else{
            return NULL;
        }
    }

    return arr;
}

float eight_bit_to_float(int* arr, int start_index, int end_index){
    int value= 0;
    for (int i = start_index; i < end_index; i++){
        value = (value << 1) | (arr[i] & 1);
    }
    return (float)value;
}

int dht11_check_parity(float message){

    return 0;
}
 