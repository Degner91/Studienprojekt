/*
 * main.cpp
 *
 *  Created on: 29.01.2019
 *      Author: degne
 */

#include "stm32f0xx_rcc.h"
#include "LED.h"
#include "Button.h"
#include "VCOM.h"
#include "W5500.h"
#include "TFT_Display.h"
#include "Color.h"
#include "Fonts/Font_Helvetica_16.h"
#include "Fonts/Font_Helvetica_24.h"
#include "Delay.h"
#include <stdio.h>

static LED & leds = LED::GetInstance();
static Button & buttons = Button::GetInstance();
static VCOM & vcom = VCOM::GetInstance();
static TFT_Display & display = TFT_Display::GetInstance();
static WIZnet_W5500 & w5500 = WIZnet_W5500::GetInstance();

static uint8_t MAC_Address[] =
{ 0xB1, 0x6B, 0x00, 0xBD, 0xBA, 0xBE };

static void SystemClockConfig();
static void ErrorFunc();

enum Screen
{
	MAIN,
	MAC,
	DETAILS
};

static uint32_t cnt = 0;

static void PrintScreen(Screen s);
static void PrintFooter(Screen s);

int main()
{
	// Core initialization
	SystemClockConfig();
	InitializeSysTick();

	// HW initialization
	leds.Initialize();
	leds.On(LED::RED);
	buttons.Initialize();
	vcom.Initialize();
	display.Initialize();
	w5500.Initialize();

	leds.Off(LED::RED);
	leds.On(LED::YELLOW);

	// HW configuration
	display.SetFont(&Font_Helvetica_24);
	display.SetBackgroundColor(TFT_COLOUR_WHITE);
	display.SetForegroundColor(TFT_COLOUR_BLACK);
	display.ClearScreen();
	w5500.Configure(MAC_Address);

	// get ip address by dhcp

	if (!w5500.OpenSocket()) ErrorFunc();

	leds.Off(LED::YELLOW);
	leds.On(LED::GREEN);

	Screen currentScreen = MAIN;
	Button::Button_Name lastBtn = Button::NOBTN;

	while (1)
	{
		// Evaluate next ethernet frame
		// w5500.ReceiveFrame(frame, framelength);
		// DecodeEthFrame(frame);
		PrintScreen(currentScreen);
		Delay_sec(1);

		lastBtn = buttons.GetState();

		switch (lastBtn)
		{
		case Button::WAKEUP:
			if (currentScreen == MAC && cnt > 0)
				cnt--;
			break;

		case Button::USER0:
			if (currentScreen == MAIN || currentScreen == DETAILS)
				currentScreen = MAC;
			else
				currentScreen = DETAILS;
			break;

		case Button::USER1:
			if (currentScreen == MAC)
				cnt++;
			break;

		default:
			continue;
		}
	}

	w5500.CloseSocket();
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
	leds.Off(LED::ALL);

	while (1)
	{
		leds.Toggle(LED::RED);
		Delay_ms(50);
	}
}

static void PrintScreen(Screen s)
{
	PositionType t = { 0, 0};
	char buffer[16];

	display.ClearScreen();

	switch (s)
	{
	case MAIN:
		snprintf(buffer, 16, "Main Screen");
		break;

	case MAC:
		snprintf(buffer, 16, "MAC Screen %lu", cnt);
		break;

	case DETAILS:
		snprintf(buffer, 16, "Details Screen");
		break;

	default:
		break;
	}

	display.DrawString(&t, buffer);

	PrintFooter(s);
}

static void PrintFooter(Screen s)
{
	// Draw line
	PositionType ls = { 0, 286 };
	PositionType le = { 240, 286 };
	display.DrawLine(&ls, &le);

	// Print footer text
	PositionType t = { 0, 288 };

	switch (s)
	{
	case MAIN:
		t.x = 92;
		display.DrawString(&t, "MAC");
		break;

	case MAC:
		t.x = 10;
		display.DrawChar(&t, 'D');
		t.x = 70;
		display.DrawString(&t, "DETAILS");
		t.x = 216;
		display.DrawChar(&t, 'U');
		break;

	case DETAILS:
		t.x = 85;
		display.DrawString(&t, "BACK");
		break;

	default:
		break;
	}
}
