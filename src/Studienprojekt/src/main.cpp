/*
 * main.cpp
 *
 *  Created on: 29.01.2019
 *      Author: degne
 */

#include "stm32f0xx_rcc.h"
#include "LED.h"
#include "VCOM.h"
#include "TFT_Display.h"
#include "Color.h"
#include "Fonts/Font_Helvetica_24.h"
#include "Delay.h"

void SetupSystemClockPLL();
void Initialize_Hardware();
void ErrorFunc();
static void Animation();

int main()
{
	SetupSystemClockPLL();
	InitializeSysTick();
	Initialize_Hardware();

	char string[] = "System clock and hardware initialized successfully.\r\n";

	VCOM_Send(string);

	TFT_ClearScreen();
	TFT_SetFont(&Font_Helvetica_24);

	PositionType a =
	{ 0, 0 };

	char str[] = "Hello world";

	TFT_DrawString(&a, str);

	while (1)
	{
		Animation();
	}

	return 0;
}

void SetupSystemClockPLL()
{
	RCC_DeInit();
	RCC_HSEConfig(RCC_HSE_ON);

	if (RCC_WaitForHSEStartUp() == ERROR)
		ErrorFunc();

	RCC_PLLConfig(RCC_PLLSource_HSE, RCC_PLLMul_6);
	RCC_PLLCmd(ENABLE);

	RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK);
}

void Initialize_Hardware()
{
	LED_Initialize();
	VCOM_Initialize();
	TFT_Reset();
	TFT_Initialize();
	TFT_ClearScreen();
}

void ErrorFunc()
{
	LED_On(Red);
	while (1);
}

static void Animation()
{
	LED_On(Red);
	Delay_ms(200);
	LED_On(Yellow);
	Delay_ms(200);
	LED_On(Green);
	Delay_ms(600);
	LED_Off(Red);
	Delay_ms(200);
	LED_Off(Yellow);
	Delay_ms(200);
	LED_Off(Green);
	Delay_ms(600);
}
