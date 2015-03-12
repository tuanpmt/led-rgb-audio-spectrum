#include <stdlib.h>
#include "tick.h"
#include "hw_config.h"
#include "typedef.h"

static volatile U32 internalTicks;

#define TICK__DisableInt()		NVIC_Config(SysTick_IRQn, TICK_PRIORITY, DISABLE);
#define TICK__EnableInt()			NVIC_Config(SysTick_IRQn, TICK_PRIORITY, ENABLE);

typedef struct _TICK{
	struct _TICK* next;
	void (*pCallback)(U64 currentTimerValue); // function to be called
	U64 interval; // callback interval
	U64 currCnt; // current count value
}TICK;

U64 vtimerValue = 0;

TICK* vtimerHead = 0;
TICK* vtimerTail = 0;



void TICK_Init(void)
{
	SysTick_CLKSourceConfig(SysTick_CLKSource_HCLK);
 	SysTick_Config(SystemCoreClock/1000); //Tick every 1ms
	internalTicks = 0;
	
	vtimerHead = 0;
	vtimerTail = 0;
	
	NVIC_Config(SysTick_IRQn, TICK_PRIORITY, ENABLE);
	NVIC_SetPriority(SysTick_IRQn, TICK_PRIORITY);
	
}


/**
 * Create a Virtual timer object
 * @param vtimerCallback this function will be call when the timer expired
 * @param interval callback interval, base on the rate of VTIMER resolution. Set interval = 0 to disable
 * @return handle to the newly created VTIMER
 */
TICK_HANDLE TICK_Create(void (*vtimerCallback)(U64 currentTimerValue), U64 interval)
{
	TICK* newNode = 0;

	if (vtimerCallback){
		newNode = malloc(sizeof(TICK));
		
		if(newNode){
			newNode->pCallback = vtimerCallback;
			newNode->interval = newNode->currCnt = interval;
			newNode->next = 0;
			
			TICK__DisableInt();
			
			if(vtimerTail == 0){
				vtimerHead = vtimerTail = newNode;
			}else{
				vtimerTail->next = newNode;
				vtimerTail = newNode;
			}
			
			TICK__EnableInt();
		}
	}

	return (TICK_HANDLE) newNode;
}

	 /*******************************************************************************
* Function Name  : SysTick_Handler
* Description    : This function handles SysTick Handler.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/



/**
 * Delete a VTIMER object and release all allocated memory
 * @param vtimerHandle handle to a VTIMER object
 * @return 0 if OK
 */
I8 TICK_Delete(TICK_HANDLE vtimerHandle)
{
	TICK *pTmr, *prev;

	if (vtimerHandle == 0)
		return -1;

	if (vtimerHead == 0)
		return -1;

	TICK__DisableInt();

	if((pTmr = vtimerHead) == (TICK*) vtimerHandle){ // remove head
		if (vtimerHead == vtimerTail){
			vtimerHead = vtimerTail = 0;
		}else{
			vtimerHead = pTmr->next;
		}
	}else 
		for (prev = vtimerHead, pTmr = vtimerHead->next; pTmr != 0; prev = pTmr, pTmr = pTmr->next){ // search within the list
			if (pTmr == (TICK*) vtimerHandle){ // found it
				prev->next = pTmr->next;
				if (vtimerTail == pTmr){ // adjust tail
					vtimerTail = prev;
				}
				break;
			}
		}
	
	TICK__EnableInt();
	
	if(pTmr){
		free(pTmr);
	}

	return pTmr != 0;
}


void SysTick_Handler()
{
	TICK *pTmr;

	vtimerValue++;

	for(pTmr = vtimerHead; pTmr != 0; pTmr = pTmr->next){
		if(pTmr->interval != 0){
			if (--pTmr->currCnt == 0){
				pTmr->currCnt = pTmr->interval;
				(*pTmr->pCallback)(vtimerValue);
			}
		}
	}
}

