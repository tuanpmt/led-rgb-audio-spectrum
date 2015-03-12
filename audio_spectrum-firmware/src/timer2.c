#include "timer2.h"

static u8 sampleAvailable;

void SAMPLE_Init(void){
	uint16_t TIM2ARRValue;
	TIM_TimeBaseInitTypeDef timerInitStructure; 
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
	
	TIM2ARRValue = (uint32_t)(SystemCoreClock/20000); /* Audio Sample Rate = 20KHz */

	timerInitStructure.TIM_Prescaler = 0;
	timerInitStructure.TIM_CounterMode = TIM_CounterMode_Up;
	timerInitStructure.TIM_Period = TIM2ARRValue;
	timerInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;
	timerInitStructure.TIM_RepetitionCounter = 0;
	TIM_TimeBaseInit(TIM2, &timerInitStructure);
	
	  /* Set the timer auto reload value dependent on the audio frequency */  
	TIM_SetAutoreload(TIM2, TIM2ARRValue); /* 22.KHz = 32MHz / 1454 */  
	
	  /* TIM2 TRGO selection */
	 TIM_SelectOutputTrigger(TIM2, TIM_TRGOSource_Update); 
	
	  /* Enable TIM2 update interrupt */
	 TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE);
		
	 NVIC_Config(TIM2_IRQn, 0, ENABLE);
	 TIM_Cmd(TIM2, ENABLE);

}

void TIM2_IRQHandler(void)
{
   static U16 cc;
   static u8 term;

   term^=1;
  if (TIM_GetITStatus(TIM2, TIM_IT_Update) != RESET)
  {
    /* Clear TIM2 update interrupt */
    TIM_ClearITPendingBit(TIM2, TIM_IT_Update);

	GPIO_WriteBit(GPIOB,GPIO_Pin_11,term);
	FFT_input[cc++] =ADC_Read();
	if(cc==128){
	   sampleAvailable =1;
	   SAMPLE_Pause();
	   cc=0;
	}

  }
}

void SAMPLE_Resum(void){
	 TIM_Cmd(TIM2, ENABLE);
}
void SAMPLE_Pause(void){
	 TIM_Cmd(TIM2,DISABLE);
}
u8 SAMPLE_State(void){
 	if(sampleAvailable){
	 	sampleAvailable=0;
		return 1;
	}
	else{
		return 0;
	}
}
