#include "sample.h"
U32 adcSample[SAMPLE_NO], sampleNo = 0, sampleAvailable = 0;
void SAMPLE_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
  ADC_InitTypeDef ADC_InitStructure;

	RCC_ADCCLKConfig(RCC_PCLK2_Div6);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
	
	/* RB1/AN9*/
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
  GPIO_Init(GPIOB, &GPIO_InitStructure);
	
	/* Time base configuration */
  TIM_TimeBaseStructInit(&TIM_TimeBaseStructure);
  TIM_TimeBaseStructure.TIM_Period = (SystemCoreClock / 20000) - 1; // 44100 KHz
  TIM_TimeBaseStructure.TIM_Prescaler = 0;
  TIM_TimeBaseStructure.TIM_ClockDivision = 0;
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
	
  TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);
	
	
  /* TIM2 TRGO selection */
  //TIM_SelectOutputTrigger(TIM3, TIM_TRGOSource_Update); // ADC_ExternalTrigConv_T2_TRGO
	
  /* PCLK2 is the APB2 clock */
  /* ADCCLK = PCLK2/6 = 72/6 = 12MHz*/
  RCC_ADCCLKConfig(RCC_PCLK2_Div6);

  /* Enable ADC1 clock so that we can talk to it */
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);
  /* Put everything back to power-on defaults */
  ADC_DeInit(ADC1);

  /* ADC1 Configuration ------------------------------------------------------*/
  /* ADC1 and ADC2 operate independently */
  ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;
  /* Disable the scan conversion so we do one at a time */
  ADC_InitStructure.ADC_ScanConvMode = DISABLE;
  /* Don't do contimuous conversions - do them on demand */
  ADC_InitStructure.ADC_ContinuousConvMode = DISABLE;
  /* Start conversin by software, not an external trigger */
  ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;
  /* Conversions are 12 bit - put them in the lower 12 bits of the result */
  ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;
  /* Say how many channels would be used by the sequencer */
  ADC_InitStructure.ADC_NbrOfChannel = 1;

  /* Now do the setup */
  ADC_Init(ADC1, &ADC_InitStructure);
  /* Enable ADC1 */
  ADC_Cmd(ADC1, ENABLE);

  /* Enable ADC1 reset calibaration register */
  ADC_ResetCalibration(ADC1);
  /* Check the end of ADC1 reset calibration register */
  while(ADC_GetResetCalibrationStatus(ADC1));
  /* Start ADC1 calibaration */
  ADC_StartCalibration(ADC1);
  /* Check the end of ADC1 calibration */
  while(ADC_GetCalibrationStatus(ADC1));
	
	TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE);
	NVIC_Config(TIM2_IRQn, 1, ENABLE);
  /* TIM2 enable counter */
  TIM_Cmd(TIM2, ENABLE);
	
}
U32* SAMPLE_Available(void)
{
	if(sampleAvailable){
		sampleAvailable = 0;
		return adcSample;
	}
	return 0;
}
void SAMPLE_NewConvertion(void)
{
	TIM_Cmd(TIM2, ENABLE);
}
void TIM2_IRQHandler(void)
{
	if (TIM_GetITStatus(TIM2, TIM_IT_Update) != RESET)
  {
    /* Clear TIM2 update interrupt */
    TIM_ClearITPendingBit(TIM2, TIM_IT_Update);
		ADC_RegularChannelConfig(ADC1, ADC_Channel_9, 1, ADC_SampleTime_1Cycles5);
		ADC_SoftwareStartConvCmd(ADC1, ENABLE);
	  // Wait until conversion completion
	  while(ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC) == RESET);
	  // Get the conversion value
		adcSample[sampleNo] = ADC_GetConversionValue(ADC1);
		sampleNo++;
		if(sampleNo > 127) {
			sampleNo = 0;
			sampleAvailable = 1;
			TIM_Cmd(TIM2, DISABLE);
		}
	}
}

