/*
 * main.cpp
 *
 *  Created on: 29.01.2019
 *      Author: degne
 */

#include "stm32f0xx_gpio.h"


int main()
{
	GPIO_DeInit(GPIOC);
	RCC_AHBPeriphClockCmd(RCC_AHBENR_GPIOCEN, ENABLE);
	GPIO_InitTypeDef gpioLED;
	gpioLED.GPIO_Mode = GPIO_Mode_OUT;
	gpioLED.GPIO_OType = GPIO_OType_OD;
	gpioLED.GPIO_Pin = (GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2);
	GPIO_Init(GPIOC, &gpioLED);
	GPIO_WriteBit(GPIOC, (GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2), Bit_SET);

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



	char string[] = "Hello world!\r\n";
	uint16_t temp = 0;

	while (string[temp] != '\0')
	{
		USART_SendData(USART3, (uint16_t)(string[temp++]));

		while(!USART_GetFlagStatus(USART3, USART_FLAG_TXE));
	}

	while (1)
	{

	}

	return 0;
}

// RCC_APB1ENR_USART3EN
// VCOM ist USART3
