/*
 * Button.cpp
 *
 *  Created on: 15.02.2019
 *      Author: degne
 */

#include "Button.h"
#include "stm32f0xx_rcc.h"
#include "stm32f0xx_gpio.h"

void Button::Initialize()
{
	RCC_AHBPeriphClockCmd(RCC_AHBENR_GPIODEN, ENABLE);

	GPIO_InitTypeDef gpio;

	gpio.GPIO_Mode = GPIO_Mode_IN;
	gpio.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2;
	gpio.GPIO_PuPd = GPIO_PuPd_NOPULL;

	GPIO_Init(GPIOD, &gpio);

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);

	EXTI_InitTypeDef exti;

	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOD, EXTI_PinSource0);
	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOD, EXTI_PinSource1);
	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOD, EXTI_PinSource2);

	exti.EXTI_Line = EXTI_Line0 | EXTI_Line1 | EXTI_Line2;
	exti.EXTI_Mode = EXTI_Mode_Interrupt;
	exti.EXTI_Trigger = EXTI_Trigger_Rising;
	exti.EXTI_LineCmd = ENABLE;

	EXTI_Init(&exti);

	NVIC_SetPriority(EXTI0_1_IRQn, 1);
	NVIC_SetPriority(EXTI2_3_IRQn, 1);
	NVIC_EnableIRQ(EXTI0_1_IRQn);
	NVIC_EnableIRQ(EXTI2_3_IRQn);

	isInitialized = true;
}

Button::Button_Name Button::GetState()
{
	if (!isInitialized)
		return NOBTN;

	Button_Name ret = lastButton;

	lastButton = NOBTN;

	return ret;
}

void Button::SetState(Button_Name const name)
{
	if (!isInitialized)
		return;

	lastButton = name;
}
