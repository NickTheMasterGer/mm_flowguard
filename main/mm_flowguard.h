#pragma once

#include <freertos/FreeRTOS.h>
#include "esp_log.h"


#define MM_FLOWGUARD_STACKSIZE 2048
#define MM_FLOWGUARD_PRIO 2

#define GPIO_OUTPUT_IO_0    22
#define GPIO_OUTPUT_IO_1    23
#define GPIO_OUTPUT_PIN_SEL  ((1ULL<<GPIO_OUTPUT_IO_0) | (1ULL<<GPIO_OUTPUT_IO_1))
#define GPIO_INPUT_IO_0     2
#define GPIO_INPUT_IO_1     15
#define GPIO_INPUT_PIN_SEL  ((1ULL<<GPIO_INPUT_IO_0) | (1ULL<<GPIO_INPUT_IO_1))
#define ESP_INTR_FLAG_DEFAULT 0


struct mm_flowguard {   // Structure declaration
    int64_t offtime;//in ms
    int64_t offtime_old;//in ms
    int sensor_threashold; //in ms
    uint32_t valve;
    int sensor;
    int trapcounter;
    int timer;
    int state;
}; // End the structure with a semicolon 

extern struct mm_flowguard fg;
extern TaskHandle_t th_mm_flowguard;

void mm_flowguard_entry_func(void);
void mm_flowguard_main(void *arg);