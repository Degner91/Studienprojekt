/**
 ******************************************************************************
 * \file    LED.cpp
 * \author  Lucas Degner
 * \version V1.0.0
 * \date    05.02.2019
 * \brief   Implementation of LED class and functions
 ******************************************************************************
 */

#include "LED.h"
#include "stm32f0xx_rcc.h"
#include "stm32f0xx_gpio.h"

void LED::Initialize()
{
	GPIO_DeInit(GPIOC);
	RCC_AHBPeriphClockCmd(RCC_AHBENR_GPIOCEN, ENABLE);
	GPIO_InitTypeDef gpioLED;
	gpioLED.GPIO_Mode = GPIO_Mode_OUT;
	gpioLED.GPIO_OType = GPIO_OType_OD;
	gpioLED.GPIO_Pin = (GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2);
	GPIO_Init(GPIOC, &gpioLED);

	GPIO_WriteBit(GPIOC, GPIO_Pin_0, Bit_SET);
	redState = false;
	GPIO_WriteBit(GPIOC, GPIO_Pin_1, Bit_SET);
	yellowState = false;
	GPIO_WriteBit(GPIOC, GPIO_Pin_2, Bit_SET);
	greenState = false;

	isInitialized = true;
}

void LED::On(LED_Color const color)
{
	if (!isInitialized)
		return;

	switch (color)
	{
	case RED:
		GPIO_WriteBit(GPIOC, GPIO_Pin_0, Bit_RESET);
		redState = true;
		break;

	case YELLOW:
		GPIO_WriteBit(GPIOC, GPIO_Pin_1, Bit_RESET);
		yellowState = true;
		break;

	case GREEN:
		GPIO_WriteBit(GPIOC, GPIO_Pin_2, Bit_RESET);
		greenState = true;
		break;

	case ALL:
		GPIO_WriteBit(GPIOC, GPIO_Pin_0, Bit_RESET);
		redState = true;
		GPIO_WriteBit(GPIOC, GPIO_Pin_1, Bit_RESET);
		yellowState = true;
		GPIO_WriteBit(GPIOC, GPIO_Pin_2, Bit_RESET);
		greenState = true;
		break;

	default:
		break;
	}
}

void LED::Off(LED_Color const color)
{
	if (!isInitialized)
		return;

	switch (color)
	{
	case RED:
		GPIO_WriteBit(GPIOC, GPIO_Pin_0, Bit_SET);
		redState = false;
		break;

	case YELLOW:
		GPIO_WriteBit(GPIOC, GPIO_Pin_1, Bit_SET);
		yellowState = false;
		break;

	case GREEN:
		GPIO_WriteBit(GPIOC, GPIO_Pin_2, Bit_SET);
		greenState = false;
		break;

	case ALL:
		GPIO_WriteBit(GPIOC, GPIO_Pin_0, Bit_SET);
		redState = false;
		GPIO_WriteBit(GPIOC, GPIO_Pin_1, Bit_SET);
		yellowState = false;
		GPIO_WriteBit(GPIOC, GPIO_Pin_2, Bit_SET);
		greenState = false;
		break;

	default:
		break;
	}
}

void LED::Toggle(LED_Color const color)
{
	if (!isInitialized)
		return;

	switch (color)
	{
	case RED:
		GPIO_WriteBit(GPIOC, GPIO_Pin_0,
				(GPIO_ReadOutputDataBit(GPIOC, GPIO_Pin_0) == Bit_SET ?
						Bit_RESET : Bit_SET));
		redState = (redState == true ? false : true);
		break;

	case YELLOW:
		GPIO_WriteBit(GPIOC, GPIO_Pin_1,
				(GPIO_ReadOutputDataBit(GPIOC, GPIO_Pin_1) == Bit_SET ?
						Bit_RESET : Bit_SET));
		yellowState = (yellowState == true ? false : true);
		break;

	case GREEN:
		GPIO_WriteBit(GPIOC, GPIO_Pin_2,
				(GPIO_ReadOutputDataBit(GPIOC, GPIO_Pin_2) == Bit_SET ?
						Bit_RESET : Bit_SET));
		greenState = (greenState == true ? false : true);
		break;

	case ALL:
		GPIO_WriteBit(GPIOC, GPIO_Pin_0,
				(GPIO_ReadOutputDataBit(GPIOC, GPIO_Pin_0) == Bit_SET ?
						Bit_RESET : Bit_SET));
		redState = (redState == true ? false : true);
		GPIO_WriteBit(GPIOC, GPIO_Pin_1,
				(GPIO_ReadOutputDataBit(GPIOC, GPIO_Pin_1) == Bit_SET ?
						Bit_RESET : Bit_SET));
		yellowState = (yellowState == true ? false : true);
		GPIO_WriteBit(GPIOC, GPIO_Pin_2,
				(GPIO_ReadOutputDataBit(GPIOC, GPIO_Pin_2) == Bit_SET ?
						Bit_RESET : Bit_SET));
		greenState = (greenState == true ? false : true);
		break;

	default:
		break;
	}
}

bool LED::GetState(LED_Color const color)
{
	if (!isInitialized)
		return false;

	bool ret = false;

	switch (color)
	{
	case RED:
		ret = redState;
		break;

	case YELLOW:
		ret = yellowState;
		break;

	case GREEN:
		ret = greenState;
		break;

	case ALL:
		ret = redState && yellowState && greenState;
		break;

	default:
		break;
	}

	return ret;
}
