/*
 * Delay.c
 *
 *  Created on: 30.01.2019
 *      Author: degne
 */

#include "Delay.h"
#include "stm32f0xx_rcc.h"


static uint32_t TickCount = 0;


void InitializeSysTick(void)
{
	SysTick_Config(SystemCoreClock / 1000);
	NVIC_SetPriority(SysTick_IRQn, 0);
	NVIC_EnableIRQ(SysTick_IRQn);
}

uint32_t GetTick(void)
{
	return TickCount;
}

void IncrementTick(void)
{
	TickCount++;
}

void Delay_ms(uint32_t const delay)
{
	uint32_t start = GetTick();

	while (GetTick() < (start + delay));
}

void Delay_sec(uint32_t const delay)
{
	uint32_t start = GetTick();

	while (GetTick() < (start + 1000 * delay));
}
