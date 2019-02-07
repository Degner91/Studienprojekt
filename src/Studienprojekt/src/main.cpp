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
#include "W5500.h"
#include <stdio.h>

WIZnet_W5500 w5500;

static uint8_t MAC_Address[] = { 0xCA, 0xFE, 0xBA, 0xBE, 0x22, 0x06 };

static void SystemClockConfig();
static void ErrorFunc();
static void Animation();

int main()
{
	SystemClockConfig();
	InitializeSysTick();
	LED_Initialize();
	VCOM_Initialize();
	TFT_Reset();
	TFT_Initialize();
	TFT_ClearScreen();
	TFT_SetFont(&Font_Helvetica_24);
	TFT_SetBackgroundColor(TFT_COLOUR_WHITE);
	TFT_SetForegroundColor(TFT_COLOUR_BLACK);

	char buffer[16];

	w5500.Initialize(MAC_Address);
	uint8_t vernum = 0;
	PositionType a =
	{ 0, 0 };

	vernum = w5500.ReadVersionNumber();
	snprintf(buffer, 16, "VN: %d", vernum);
	TFT_DrawString(&a, buffer);

	if (!w5500.TestMACWrite(MAC_Address))
		ErrorFunc();

	while (1)
	{
		Animation();
	}

	return 0;
}

static void SystemClockConfig()
{
	RCC_DeInit();
	RCC_HSEConfig(RCC_HSE_ON);

	if (RCC_WaitForHSEStartUp() == ERROR)
		ErrorFunc();

	RCC_PLLConfig(RCC_PLLSource_HSE, RCC_PLLMul_6);
	RCC_PLLCmd(ENABLE);

	RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK);
}

static void ErrorFunc()
{
	LED_On(Red);
	while (1)
	{
		LED_Toggle(Red);
		Delay_ms(50);
	}
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
