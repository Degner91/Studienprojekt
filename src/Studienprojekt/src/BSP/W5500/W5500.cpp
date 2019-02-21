/*
 * W5500.cpp
 *
 *  Created on: 06.02.2019
 *      Author: degne
 */

#include "W5500.h"
#include <string.h>

static uint32_t const BufferSize_Max = 16;

uint8_t WIZnet_W5500::wizchip_read(uint8_t block, uint16_t address)
{
	uint8_t ret;

	wizchip_cs_select();

	block |= AccessModeRead;

	wizchip_spi_write_byte((address & 0xFF00) >> 8);
	wizchip_spi_write_byte((address & 0x00FF) >> 0);
	wizchip_spi_write_byte(block);

	ret = wizchip_spi_read_byte();

	wizchip_cs_deselect();
	return ret;
}

uint16_t WIZnet_W5500::wizchip_read_word(uint8_t block, uint16_t address)
{
	return ((uint16_t) wizchip_read(block, address) << 8)
			+ wizchip_read(block, address + 1);
}

void WIZnet_W5500::wizchip_read_buf(uint8_t block, uint16_t address,
		uint8_t* pBuf, uint16_t len)
{
	uint16_t i;

	wizchip_cs_select();

	block |= AccessModeRead;

	wizchip_spi_write_byte((address & 0xFF00) >> 8);
	wizchip_spi_write_byte((address & 0x00FF) >> 0);
	wizchip_spi_write_byte(block);
	for (i = 0; i < len; i++)
		pBuf[i] = wizchip_spi_read_byte();

	wizchip_cs_deselect();
}

void WIZnet_W5500::wizchip_write(uint8_t block, uint16_t address, uint8_t wb)
{
	wizchip_cs_select();

	block |= AccessModeWrite;

	wizchip_spi_write_byte((address & 0xFF00) >> 8);
	wizchip_spi_write_byte((address & 0x00FF) >> 0);
	wizchip_spi_write_byte(block);
	wizchip_spi_write_byte(wb);

	wizchip_cs_deselect();
}

void WIZnet_W5500::wizchip_write_word(uint8_t block, uint16_t address,
		uint16_t word)
{
	wizchip_write(block, address, (uint8_t) (word >> 8));
	wizchip_write(block, address + 1, (uint8_t) word);
}

void WIZnet_W5500::wizchip_write_buf(uint8_t block, uint16_t address,
		const uint8_t* pBuf, uint16_t len)
{
	uint16_t i;

	wizchip_cs_select();

	block |= AccessModeWrite;

	wizchip_spi_write_byte((address & 0xFF00) >> 8);
	wizchip_spi_write_byte((address & 0x00FF) >> 0);
	wizchip_spi_write_byte(block);
	for (i = 0; i < len; i++)
		wizchip_spi_write_byte(pBuf[i]);

	wizchip_cs_deselect();
}

void WIZnet_W5500::setSn_CR(uint8_t cr)
{
	// Write the command to the Command Register
	wizchip_write(BlockSelectSReg, Sn_CR, cr);

	// Now wait for the command to complete
	while (wizchip_read(BlockSelectSReg, Sn_CR))
		;
}

uint16_t WIZnet_W5500::getSn_TX_FSR()
{
	uint16_t val = 0, val1 = 0;
	do
	{
		val1 = wizchip_read_word(BlockSelectSReg, Sn_TX_FSR);
		if (val1 != 0)
		{
			val = wizchip_read_word(BlockSelectSReg, Sn_TX_FSR);
		}
	} while (val != val1);
	return val;
}

uint16_t WIZnet_W5500::getSn_RX_RSR()
{
	uint16_t val = 0, val1 = 0;
	do
	{
		val1 = wizchip_read_word(BlockSelectSReg, Sn_RX_RSR);
		if (val1 != 0)
		{
			val = wizchip_read_word(BlockSelectSReg, Sn_RX_RSR);
		}
	} while (val != val1);
	return val;
}

void WIZnet_W5500::wizchip_send_data(const uint8_t *wizdata, uint16_t len)
{
	uint16_t ptr = 0;

	if (len == 0)
		return;
	ptr = getSn_TX_WR();
	wizchip_write_buf(BlockSelectTxBuf, ptr, wizdata, len);

	ptr += len;

	setSn_TX_WR(ptr);
}

void WIZnet_W5500::wizchip_recv_data(uint8_t *wizdata, uint16_t len)
{
	uint16_t ptr;

	if (len == 0)
		return;
	ptr = getSn_RX_RD();
	wizchip_read_buf(BlockSelectRxBuf, ptr, wizdata, len);
	ptr += len;

	setSn_RX_RD(ptr);
}

void WIZnet_W5500::wizchip_recv_ignore(uint16_t len)
{
	uint16_t ptr;

	ptr = getSn_RX_RD();
	ptr += len;
	setSn_RX_RD(ptr);
}

void WIZnet_W5500::wizchip_sw_reset()
{
	setMR(MR_RST);
	getMR(); // for delay

	setSHAR(macAddress);
}

int8_t WIZnet_W5500::wizphy_getphylink()
{
	int8_t tmp;
	if (getPHYCFGR() & PHYCFGR_LNK_ON)
		tmp = PHY_LINK_ON;
	else
		tmp = PHY_LINK_OFF;
	return tmp;
}

int8_t WIZnet_W5500::wizphy_getphypmode()
{
	int8_t tmp = 0;
	if (getPHYCFGR() & PHYCFGR_OPMDC_PDOWN)
		tmp = PHY_POWER_DOWN;
	else
		tmp = PHY_POWER_NORM;
	return tmp;
}

void WIZnet_W5500::wizphy_reset()
{
	uint8_t tmp = getPHYCFGR();
	tmp &= PHYCFGR_RST;
	setPHYCFGR(tmp);
	tmp = getPHYCFGR();
	tmp |= ~PHYCFGR_RST;
	setPHYCFGR(tmp);
}

int8_t WIZnet_W5500::wizphy_setphypmode(uint8_t pmode)
{
	uint8_t tmp = 0;
	tmp = getPHYCFGR();
	if ((tmp & PHYCFGR_OPMD) == 0)
		return -1;
	tmp &= ~PHYCFGR_OPMDC_ALLA;
	if (pmode == PHY_POWER_DOWN)
		tmp |= PHYCFGR_OPMDC_PDOWN;
	else
		tmp |= PHYCFGR_OPMDC_ALLA;
	setPHYCFGR(tmp);
	wizphy_reset();
	tmp = getPHYCFGR();
	if (pmode == PHY_POWER_DOWN)
	{
		if (tmp & PHYCFGR_OPMDC_PDOWN)
			return 0;
	}
	else
	{
		if (tmp & PHYCFGR_OPMDC_ALLA)
			return 0;
	}
	return -1;
}

void WIZnet_W5500::Initialize()
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

	wizchip_sw_reset();
}

void WIZnet_W5500::Configure(uint8_t const * address)
{
	for (uint8_t idx = 0; idx < 6; ++idx)
		macAddress[idx] = (uint8_t) address[idx];

	// Use the full 16Kb of RAM for Socket 0
	setSn_RXBUF_SIZE(BufferSize_Max);
	setSn_TXBUF_SIZE(BufferSize_Max);

	// Set our local MAC address
	setSHAR (macAddress);
	// set ip gateway etc
}

bool WIZnet_W5500::OpenSocket()
{
	uint8_t tmp = 0;
	// Open Socket 0 in MACRaw mode
	setSn_MR(Sn_MR_MACRAW | Sn_MR_MIP6B);
	setSn_CR(Sn_CR_OPEN);
	tmp = getSn_SR();

	if (tmp != SOCK_MACRAW)
	{
		// Failed to put socket 0 into MACRaw mode
		return false;
	}

	// Success
	return true;
}

void WIZnet_W5500::CloseSocket()
{
	setSn_CR(Sn_CR_CLOSE);

	// clear all interrupt of the socket
	setSn_IR(0xFF);

	// Wait for socket to change to closed
	while (getSn_SR() != SOCK_CLOSED)
		;
}

uint16_t WIZnet_W5500::ReceiveFrame(uint8_t * buffer,
		uint16_t const buffer_length)
{
	uint16_t len = getSn_RX_RSR();

	if (len > 0)
	{
		uint8_t head[2];
		uint16_t data_len = 0;

		wizchip_recv_data(head, 2);
		setSn_CR(Sn_CR_RECV);

		data_len = head[0];
		data_len = (data_len << 8) + head[1];
		data_len -= 2;

		if (data_len > buffer_length)
		{
			// Packet is bigger than buffer - drop the packet
			wizchip_recv_ignore(data_len);
			setSn_CR(Sn_CR_RECV);
			return 0;
		}

		wizchip_recv_data(buffer, data_len);
		setSn_CR(Sn_CR_RECV);

		// Had problems with W5500 MAC address filtering (the Sn_MR_MFEN option)
		// Do it in software instead:
		if ((buffer[0] & 0x01) || memcmp(&buffer[0], macAddress, 6) == 0)
		{
			// Addressed to an Ethernet multicast address or our unicast address
			return data_len;
		}
		else
		{
			return 0;
		}
	}

	return 0;
}

int16_t WIZnet_W5500::TransmitFrame(uint8_t const * buffer,
		uint16_t const buffer_length)
{
	// Wait for space in the transmit buffer
	while (1)
	{
		uint16_t freesize = getSn_TX_FSR();
		if (getSn_SR() == SOCK_CLOSED)
		{
			return -1;
		}
		if (buffer_length <= freesize)
			break;
	};

	wizchip_send_data(buffer, buffer_length);
	setSn_CR(Sn_CR_SEND);

	while (1)
	{
		uint8_t tmp = getSn_IR();
		if (tmp & Sn_IR_SENDOK)
		{
			setSn_IR(Sn_IR_SENDOK);
			// Packet sent ok
			break;
		}
		else if (tmp & Sn_IR_TIMEOUT)
		{
			setSn_IR(Sn_IR_TIMEOUT);
			// There was a timeout
			return -1;
		}
	}

	return buffer_length;
}

uint8_t WIZnet_W5500::ReadVersionNumber()
{
	return wizchip_read(BlockSelectCReg, VERSIONR);
}
