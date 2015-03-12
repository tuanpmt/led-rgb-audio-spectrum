#include "hw_config.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

U32 *sample;
U32 fftOutput[SAMPLE_NO + 2];
//U8 freqMap[] = {6, 10, 14, 18, 24, 28, 34, 38, 44, 48, 52, 58, 62, 68, 72, 78, 82, 88, 92, 102, 6, 10, 14, 18, 24, 28, 34, 38, 44, 48, 52, 58}; //400-8000
//U8 freqMap[] = {4, 8, 10, 14, 18, 22, 24, 28, 32, 36, 40, 44, 48, 52, 56, 60, 64, 68, 72, 76}; //200-6000
//U8 freqMap[] = {24, 28, 34, 38, 44, 48, 52, 6, 10, 14, 18, 58, 62, 68, 72, 78, 82, 88, 92, 102}; //400-8000
U8 freqMap[] = {4, 6, 8, 10, 14, 18, 22, 24, 28, 32, 36, 38, 42, 46, 50, 54, 56, 60, 64, 68, 70, 74, 78, 82, 84, 88, 92, 96, 98, 102, 106, 110, 114, 116}; //150-1000[10] 1000-8000[10]
//U8 freqMap[] = {84, 88, 92, 96, 98, 102, 106, 110, 114, 116, 4, 6, 8, 10, 14, 18, 22, 24, 28, 32, 36, 38, 42, 46, 50, 54, 56, 60, 64, 68, 70, 74, 78, 82}; //150-1000[10] 1000-8000[10]
int comp (const void * elem1, const void * elem2) 
{
    int f = *((int*)elem1);
    int s = *((int*)elem2);
    if (f > s) return  1;
    if (f < s) return -1;
    return 0;
}
U8 arrMax[30];
U8 freqIndex = 0;

int main()
{
	int32_t amplitude, i, j;
	SYS_Init();

	while(1) {

		if((sample = SAMPLE_Available()) != 0) {
			memset(fftOutput, 0, SAMPLE_NO + 2);
			Window16to32b_real((int *)sample, Hamming128_16b, SAMPLE_NO);
			FFT128Real_32b((int *)fftOutput, (int *)sample);
			// convert complex output to magnitude
			magnitude32_32bIn((int *)(fftOutput+2), SAMPLE_NO/2-1);  //DC and Fs/2 bins are already real (can be negative!)
			SAMPLE_NewConvertion();
			
			for(i=0;i<32;i++){
				amplitude = ((fftOutput[freqMap[i]]+16384)>>15)-3;
				if(i<3) {
					if(amplitude > 3) amplitude -= 3;
				}
				if(amplitude > 16) amplitude = 16;
				if(amplitude<0) amplitude = 0;
				LED_SetMax(i, amplitude);
			}

		}
		LED_Manage();
	}
}
