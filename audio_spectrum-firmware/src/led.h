#ifndef _LED_H_
#define _LED_H_

//include: 
#include <stdlib.h>
#include <stm32f10x.h>
#include "typedef.h"
#include "delay.h"

//Define:
#define RDATA_PIN	   	GPIO_Pin_15
#define RDATA_PORT	   	GPIOB
#define RCC_RDATA		RCC_APB2Periph_GPIOB
#define RDATA_H			GPIO_SetBits(RDATA_PORT, RDATA_PIN);
#define RDATA_L			GPIO_ResetBits(RDATA_PORT, RDATA_PIN);

#define RSCK_PIN		GPIO_Pin_13
#define RSCK_PORT		GPIOB
#define RCC_RSCK		RCC_APB2Periph_GPIOB
#define ROW_CLK()		GPIO_SetBits(RSCK_PORT, RSCK_PIN);DELAY_nop(10);GPIO_ResetBits(RSCK_PORT, RSCK_PIN); 


#define RLE_PIN			GPIO_Pin_14
#define RLE_PORT		GPIOB
#define RCC_RLE			RCC_APB2Periph_GPIOB
#define ROW_LATCH()		GPIO_SetBits(RLE_PORT, RLE_PIN);DELAY_nop(10);GPIO_ResetBits(RLE_PORT, RLE_PIN); 
		
/////////////

#define CSCK_PIN		GPIO_Pin_12
#define CSCK_PORT		GPIOB
#define RCC_CSCK		RCC_APB2Periph_GPIOB
#define COL_CLK()		 GPIO_SetBits(CSCK_PORT, CSCK_PIN); DELAY_nop(10); GPIO_ResetBits(CSCK_PORT, CSCK_PIN);
		

#define CLE_PIN			GPIO_Pin_8
#define CLE_PORT		GPIOA
#define RCC_CLE			RCC_APB2Periph_GPIOA
#define COL_LATCH()		GPIO_SetBits(CLE_PORT, CLE_PIN);DELAY_nop(10);  GPIO_ResetBits(CLE_PORT, CLE_PIN);
//#define CLE_L			

#define AUIN_PIN		GPIO_Pin_1
#define AUIN_PORT		GPIOB
#define RCC_AUIN		RCC_APB2Periph_GPIOB

#define LED_SDATA(x)	GPIO_WriteBit(GPIOA, GPIO_Pin_7, (BitAction)x)
#define LED_SCK_H()		GPIO_SetBits(GPIOA, GPIO_Pin_5)
#define LED_SCK_L()		GPIO_ResetBits(GPIOA, GPIO_Pin_5)
#define LED_SLE_H()		GPIO_SetBits(GPIOB, GPIO_Pin_0)
#define LED_SLE_L()		GPIO_ResetBits(GPIOB, GPIO_Pin_0)
#define LED_CK_H()		GPIO_SetBits(GPIOB, GPIO_Pin_12)
#define LED_CK_L()		GPIO_ResetBits(GPIOB, GPIO_Pin_12)
#define LED_LE_H()		GPIO_SetBits(GPIOA, GPIO_Pin_8)
#define LED_LE_L()		GPIO_ResetBits(GPIOA, GPIO_Pin_8)
//Funtion prototype:
void LED_Init(void);
void LED_Scan(void);
void LED_ActiveScan(U64 tick);
void LED_WriteColumn(u16 data, u8 columnIndex);
void LED_WriteRow(u32 data, u8 rowIndex);

void LED_WritePixel(U8 x, U8 y, U8 R, U8 G, U8 B);
void Led_Transmit(u8 data);
void LED_Clear(void);
void LED_Manage(void);
void LED_SetMax(U8 col, U8 val);
#endif
