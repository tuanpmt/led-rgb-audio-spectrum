#include "delay.h"
#include "typedef.h"

void DELAY_nop(u16 nopNumber){
	while(nopNumber--);
}
void delay_us(u32 time){ 		    //System clock is 72 000 000
	u32 i;
	while(time--){			//2 chu ky			//6.5us
		i=11;				//1 chu ky
		while(i--);			//2 chu ky		   //72/5 ~15
	}  
}

void delay_ms(u32 time){
   while(time--){
   		delay_us(1000);
   }
}