/*
 * main.cpp
 *
 *  Created on: 29.01.2019
 *      Author: degne
 */

#include "stm32f0xx.h"
#include "stm32f0xx_conf.h"
#include "Delay.h"
#include "TFT_Display.h"

void SetupSystemClockPLL();
void Initialize_Hardware();
void printf(char * str);
void ErrorFunc();

int main()
{
	SetupSystemClockPLL();
	InitializeSysTick();
	Initialize_Hardware();

	char string[] = "System clock and hardware initialized successfully.\r\n";

	printf(string);

	while (1)
	{
		Delay_10us(100000);
		GPIO_WriteBit(GPIOC, GPIO_Pin_0, Bit_RESET);
		Delay_10us(100000);
		GPIO_WriteBit(GPIOC, GPIO_Pin_0, Bit_SET);
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

	TFT_Reset();
	TFT_Initialize();
	TFT_ClearScreen();
}

void printf(char * str)
{
	uint16_t charpos = 0;

	while (str[charpos] != '\0')
	{
		USART_SendData(USART3, (uint16_t) (str[charpos++]));

		while (!USART_GetFlagStatus(USART3, USART_FLAG_TXE))
			;
	}
}

void ErrorFunc()
{
	GPIO_WriteBit(GPIOC, GPIO_Pin_0, Bit_RESET);

	while (1)
		;
}
