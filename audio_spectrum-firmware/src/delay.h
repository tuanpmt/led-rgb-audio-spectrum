#ifndef _DELAY_H_
#define _DELAY_H_

#include "typedef.h"
#include <stm32f10x.h>

void DELAY_nop(u16 nopNumber);
void delay_us(u32 time);
void delay_ms(u32 time);

#endif
