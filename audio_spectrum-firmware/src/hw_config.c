#include "hw_config.h"
#include "stm32f10x.h"
#include "tick.h"

void SYS_Init(void)
{
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4);
	__enable_irq();

	SAMPLE_Init();
	//TICK_Init();
	LED_Init();
	
}

void NVIC_Config(uint8_t NVIC_IRQChannel, uint8_t NVIC_IRQChannelPreemptionPriority, FunctionalState newState)
{
	NVIC_InitTypeDef NVIC_InitStructure;
	/*
	  	Configurate Interrupt RX
	*/
	NVIC_InitStructure.NVIC_IRQChannel = NVIC_IRQChannel;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = NVIC_IRQChannelPreemptionPriority;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = newState;
	NVIC_Init(&NVIC_InitStructure);
}
