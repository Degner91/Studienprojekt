/**
 ******************************************************************************
 * \file    VCOM.cpp
 * \author  Lucas Degner
 * \version V1.0.0
 * \date    05.02.2019
 * \brief   Implementation of USART interface class and functions
 ******************************************************************************
 */

#include "VCOM.h"
#include "stm32f0xx_rcc.h"
#include "stm32f0xx_gpio.h"
#include "stm32f0xx_usart.h"

void VCOM::Initialize()
{
	USART_DeInit(USART3);
	RCC_APB1PeriphClockCmd(RCC_APB1ENR_USART3EN, ENABLE);
	USART_InitTypeDef usartVCOM;
	USART_StructInit(&usartVCOM); // sets all as I want except baud rate
	usartVCOM.USART_BaudRate = 115200;
	USART_Init(USART3, &usartVCOM);
	USART_Cmd(USART3, ENABLE);

	RCC_AHBPeriphClockCmd(RCC_AHBENR_GPIODEN, ENABLE);
	GPIO_InitTypeDef gpioVCOM;
	gpioVCOM.GPIO_Mode = GPIO_Mode_AF;
	gpioVCOM.GPIO_OType = GPIO_OType_PP;
	gpioVCOM.GPIO_Pin = (GPIO_Pin_8 | GPIO_Pin_9);
	gpioVCOM.GPIO_Speed = GPIO_Speed_10MHz;
	GPIO_Init(GPIOD, &gpioVCOM);
	GPIO_PinAFConfig(GPIOD, GPIO_PinSource8, GPIO_AF_0);
	GPIO_PinAFConfig(GPIOD, GPIO_PinSource9, GPIO_AF_0);

	isInitialized = true;
}

void VCOM::Print(char const * const str)
{
	if (!isInitialized)
		return;

	uint16_t charpos = 0;

	while (str[charpos] != '\0')
	{
		USART_SendData(USART3, (uint16_t) (str[charpos++]));

		while (!USART_GetFlagStatus(USART3, USART_FLAG_TC));
	}
}

void VCOM::Println(char const * const str)
{
	if (!isInitialized)
		return;

	char const end[] = "\r\n";
	Print(str);
	Print(end);
}
