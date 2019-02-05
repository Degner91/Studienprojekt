/*
 * LED.cpp
 *
 *  Created on: 05.02.2019
 *      Author: degne
 */

#include "LED.h"
#include "stm32f0xx_rcc.h"
#include "stm32f0xx_gpio.h"

void LED_Initialize()
{
	GPIO_DeInit(GPIOC);
	RCC_AHBPeriphClockCmd(RCC_AHBENR_GPIOCEN, ENABLE);
	GPIO_InitTypeDef gpioLED;
	gpioLED.GPIO_Mode = GPIO_Mode_OUT;
	gpioLED.GPIO_OType = GPIO_OType_OD;
	gpioLED.GPIO_Pin = (GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2);
	GPIO_Init(GPIOC, &gpioLED);
	GPIO_WriteBit(GPIOC, GPIO_Pin_0, Bit_SET);
	GPIO_WriteBit(GPIOC, GPIO_Pin_1, Bit_SET);
	GPIO_WriteBit(GPIOC, GPIO_Pin_2, Bit_SET);
}

void LED_On(LED_Color const color)
{
	switch (color)
	{
	case Red:
		GPIO_WriteBit(GPIOC, GPIO_Pin_0, Bit_RESET);
		break;

	case Yellow:
		GPIO_WriteBit(GPIOC, GPIO_Pin_1, Bit_RESET);
		break;

	case Green:
		GPIO_WriteBit(GPIOC, GPIO_Pin_2, Bit_RESET);
		break;

	case All:
		GPIO_WriteBit(GPIOC, GPIO_Pin_0, Bit_RESET);
		GPIO_WriteBit(GPIOC, GPIO_Pin_1, Bit_RESET);
		GPIO_WriteBit(GPIOC, GPIO_Pin_2, Bit_RESET);
		break;

	default:
		break;
	}
}

void LED_Off(LED_Color const color)
{
	switch (color)
	{
	case Red:
		GPIO_WriteBit(GPIOC, GPIO_Pin_0, Bit_SET);
		break;

	case Yellow:
		GPIO_WriteBit(GPIOC, GPIO_Pin_1, Bit_SET);
		break;

	case Green:
		GPIO_WriteBit(GPIOC, GPIO_Pin_2, Bit_SET);
		break;

	case All:
		GPIO_WriteBit(GPIOC, GPIO_Pin_0, Bit_SET);
		GPIO_WriteBit(GPIOC, GPIO_Pin_1, Bit_SET);
		GPIO_WriteBit(GPIOC, GPIO_Pin_2, Bit_SET);
		break;

	default:
		break;
	}
}

void LED_Toggle(LED_Color const color)
{
	switch (color)
	{
	case Red:
		GPIO_WriteBit(GPIOC, GPIO_Pin_0,
				(GPIO_ReadOutputDataBit(GPIOC, GPIO_Pin_0) == Bit_SET ? Bit_RESET : Bit_SET));
		break;

	case Yellow:
		GPIO_WriteBit(GPIOC, GPIO_Pin_1,
				(GPIO_ReadOutputDataBit(GPIOC, GPIO_Pin_1) == Bit_SET ? Bit_RESET : Bit_SET));
		break;

	case Green:
		GPIO_WriteBit(GPIOC, GPIO_Pin_2,
				(GPIO_ReadOutputDataBit(GPIOC, GPIO_Pin_2) == Bit_SET ? Bit_RESET : Bit_SET));
		break;

	case All:
		GPIO_WriteBit(GPIOC, GPIO_Pin_0,
						(GPIO_ReadOutputDataBit(GPIOC, GPIO_Pin_0) == Bit_SET ? Bit_RESET : Bit_SET));
		GPIO_WriteBit(GPIOC, GPIO_Pin_1,
						(GPIO_ReadOutputDataBit(GPIOC, GPIO_Pin_1) == Bit_SET ? Bit_RESET : Bit_SET));
		GPIO_WriteBit(GPIOC, GPIO_Pin_2,
						(GPIO_ReadOutputDataBit(GPIOC, GPIO_Pin_2) == Bit_SET ? Bit_RESET : Bit_SET));
		break;

	default:
		break;
	}
}
