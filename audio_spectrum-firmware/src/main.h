#include "fft.h"

#define FFT_N 128
int FFT_input[FFT_N];				// input arrayv
int FFT_output[FFT_N+2];			// one extra element
unsigned short FFT_window[FFT_N/2];	//first half of symetrical window 0Q16 unsigned

void fft_Convert(void);