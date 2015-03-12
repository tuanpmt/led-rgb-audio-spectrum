#ifndef _SAMPLE_H_
#define _SAMPLE_H_
#include "hw_config.h"
#define SAMPLE_NO	128

void SAMPLE_Init(void);
U32* SAMPLE_Available(void);
void SAMPLE_NewConvertion(void);
#endif

