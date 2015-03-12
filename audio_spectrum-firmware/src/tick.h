#ifndef _TICK_H_
#define _TICK_H_

/* Includes ------------------------------------------------------------------*/
#ifdef STM32L1XX_MD
#include "stm32l1xx.h"
#else
#include "stm32f10x.h"
#endif /* STM32L1XX_MD */
#include "typedef.h"
#include "misc.h"
//extern uint32_t SystemCoreClock;
#include "stm32f10x_gpio.h"
#include "misc.h"


typedef const void* TICK_HANDLE;

void TICK_Init(void);
TICK_HANDLE TICK_Create(void (*vtimerCallback)(U64 currentTimerValue), U64 interval);
I8 TICK_Delete(TICK_HANDLE vtimerHandle);
#endif
