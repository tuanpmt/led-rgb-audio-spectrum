

//include: 
#include <stdlib.h>
#include <stm32f10x.h>
#include "typedef.h"

extern int FFT_input[128];


void SAMPLE_Init(void);
void TIM2_IRQHandler(void);
void SAMPLE_Resum(void);
void SAMPLE_Pause(void);
u8 SAMPLE_State(void);