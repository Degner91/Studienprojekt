/**
 ******************************************************************************
 * \file    SPI.cpp
 * \author  Lucas Degner
 * \version V1.0.0
 * \date    27.02.2019
 * \brief   Implementation of SPI interface functions
 ******************************************************************************
 */

#include "SPI.h"
#include "stm32f0xx_rcc.h"
#include "stm32f0xx_gpio.h"
#include "stm32f0xx_spi.h"

void SPI_Initialize(void)
{
	// Init SPI
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_SPI2, ENABLE);
	RCC_AHBPeriphClockCmd(RCC_AHBENR_GPIOBEN, ENABLE);

	GPIO_InitTypeDef gpiospi;

	// NSS
	gpiospi.GPIO_Pin = GPIO_Pin_12;
	gpiospi.GPIO_Mode = GPIO_Mode_OUT;
	gpiospi.GPIO_Speed = GPIO_Speed_2MHz;
	gpiospi.GPIO_OType = GPIO_OType_PP;
	gpiospi.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOB, &gpiospi);

	// SCK, MISO & MOSI
	gpiospi.GPIO_Pin = GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15;
	gpiospi.GPIO_Mode = GPIO_Mode_AF;
	gpiospi.GPIO_Speed = GPIO_Speed_50MHz;
	gpiospi.GPIO_OType = GPIO_OType_PP;
	gpiospi.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOB, &gpiospi);

	//GPIO_PinAFConfig(GPIOB, GPIO_PinSource12, GPIO_AF_0);
	GPIO_PinAFConfig(GPIOB, GPIO_PinSource13, GPIO_AF_0); // SCK O PP
	GPIO_PinAFConfig(GPIOB, GPIO_PinSource14, GPIO_AF_0); // MISO I
	GPIO_PinAFConfig(GPIOB, GPIO_PinSource15, GPIO_AF_0); // MOSI O PP

	SPI_InitTypeDef spi;
	spi.SPI_Mode = SPI_Mode_Master;
	spi.SPI_Direction = SPI_Direction_2Lines_FullDuplex;
	spi.SPI_DataSize = SPI_DataSize_8b;
	spi.SPI_FirstBit = SPI_FirstBit_MSB;
	spi.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_16;
	spi.SPI_CPOL = SPI_CPOL_Low;
	spi.SPI_CPHA = SPI_CPHA_1Edge;
	spi.SPI_CRCPolynomial = 0;
	spi.SPI_NSS = SPI_NSS_Soft;
	SPI_Init(SPI2, &spi);
	//SPI_RxFIFOThresholdConfig(SPI2, SPI_RxFIFOThreshold_QF);
	SPI_CalculateCRC(SPI2, DISABLE);
	SPI_Cmd(SPI2, ENABLE);
}

uint8_t SPI_ReadByte(void)
{
	SPI_SendData8(SPI2, 0);
	while (SPI2->SR & SPI_SR_BSY);
	return SPI_ReceiveData8(SPI2);
}

void SPI_WriteByte(uint8_t byte)
{
	SPI_SendData8(SPI2, byte);
	while (SPI2->SR & SPI_SR_BSY);
	SPI_ReceiveData8(SPI2);
}

void SPI_CS_Select(void)
{
	GPIO_WriteBit(GPIOB, GPIO_Pin_12, Bit_RESET);
}

void SPI_CS_Deselect(void)
{
	GPIO_WriteBit(GPIOB, GPIO_Pin_12, Bit_SET);
}
