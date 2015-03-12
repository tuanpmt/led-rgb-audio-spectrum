#ifndef _HW_CONFIG_H_
#define _HW_CONFIG_H_
#include <stdint.h>
#include "stm32f10x.h"
#include "led.h"
#include "sample.h"
#include "fft.h"

#define TICK_PRIORITY 3
void SYS_Init(void);
void NVIC_Config(uint8_t NVIC_IRQChannel, uint8_t NVIC_IRQChannelPreemptionPriority, FunctionalState newState);
#endif




