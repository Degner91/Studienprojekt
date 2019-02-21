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
#include "TFT_Display.h"
#include "Color.h"
#include "Fonts/Font_Helvetica_16.h"
#include "Delay.h"
#include "W5500.h"
//#include <stdio.h>

static LED & leds = LED::GetInstance();
static Button & buttons = Button::GetInstance();
static VCOM & vcom = VCOM::GetInstance();
static TFT_Display & display = TFT_Display::GetInstance();


WIZnet_W5500 w5500;

static uint8_t MAC_Address[] =
{ 0xCA, 0xFE, 0xBA, 0xBE, 0x22, 0x06 };

static void SystemClockConfig();
static void ErrorFunc();
static void Animation();
static void HexToChar(uint8_t const h, char * c);
static void PrintReceivedFrame(uint8_t * buf, uint32_t const size);
static bool MAC_Filter(uint8_t * buf, uint32_t const size, uint8_t * mac);

static void GetEthernetFrame(uint8_t * buf, uint32_t const size,
		EthernetFrame_t * frame);
static void GetIPv4Packet(EthernetFrame_t * frame, IPv4_Packet_t * packet);
static void PrintFrameAndPacket(EthernetFrame_t * frame,
		IPv4_Packet_t * packet);

static void LED_Callback(Button::Button_Name const name);

int main()
{

	uint32_t frameCnt = 0;
	uint32_t const eth_frame_size = 1518;
	uint8_t eth_buffer[eth_frame_size];
	uint32_t recv_size = 0;

	SystemClockConfig();
	InitializeSysTick();

	leds.Initialize();
	buttons.Initialize();
	buttons.RegisterCallback(LED_Callback);
	vcom.Initialize();
	display.Initialize();
	display.SetFont(&Font_Helvetica_16);
	display.SetForegroundColor(TFT_COLOUR_WHITE);
	display.SetBackgroundColor(TFT_COLOUR_GREEN);
	display.ClearScreen();

	char buffer[] = "Hello Display class";
	char hexbuf[2];
	PositionType a = { 0, 0 };
	PositionType b = { 10, 10 };
	PositionType c = { 50, 50 };

	display.DrawLine(&b, &c);

	display.DrawString(&a, buffer);

	/*
	w5500.Initialize();
	w5500.Configure(MAC_Address);
	if (!w5500.OpenSocket())
		ErrorFunc();
*/

	while (1)
	{
		vcom.Println(buffer);
		Animation();
		Delay_sec(1);
		/*
		EthernetFrame_t frame;
		IPv4_Packet_t packet;

		recv_size = w5500.ReceiveFrame(eth_buffer, eth_frame_size);

		if (recv_size > 0)
		{
			/*
			 if (eth_buffer[12] == 0x08 && eth_buffer[13] == 0x00)
			 frameCnt++;

			 snprintf(buffer, 16, "Frame: %ld", frameCnt);
			 VCOM_Println(buffer);
			 PrintReceivedFrame(eth_buffer, recv_size);

			GetEthernetFrame(eth_buffer, eth_frame_size, &frame);
			GetIPv4Packet(&frame, &packet);
			PrintFrameAndPacket(&frame, &packet);
		}
	*/
	}

	//w5500.CloseSocket();
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
	leds.On(LED::RED);
	while (1)
	{
		leds.Toggle(LED::RED);
		Delay_ms(50);
	}
}

static void Animation()
{
	leds.On(LED::RED);
	Delay_ms(200);
	leds.On(LED::YELLOW);
	Delay_ms(200);
	leds.On(LED::GREEN);
	Delay_ms(600);
	leds.Off(LED::RED);
	Delay_ms(200);
	leds.Off(LED::YELLOW);
	Delay_ms(200);
	leds.Off(LED::GREEN);
	Delay_ms(600);
}

static void HexToChar(uint8_t const h, char * c)
{
	uint8_t tmp = 0;

	tmp = h & 0x0F;

	if (tmp < 10)
		c[1] = (char) (tmp + 48);
	else
		c[1] = (char) (tmp + 65 - 10);

	tmp = (h >> 4) & 0x0F;

	if (tmp < 10)
		c[0] = (char) (tmp + 48);
	else
		c[0] = (char) (tmp + 65 - 10);
}

static void PrintReceivedFrame(uint8_t * buf, uint32_t const size)
{
	uint32_t offset = 0;
	char convbuf[2];
	char printbuf[13];
	PositionType printpos =
	{ 0, 0 };

	printbuf[12] = '\0';

	if (size < 14)
		return;

	// Print Dst MAC
	for (uint32_t i = 0; i < 6; ++i)
	{
		HexToChar(buf[offset + i], convbuf);
		printbuf[2 * i] = convbuf[0];
		printbuf[2 * i + 1] = convbuf[1];
	}

	//TFT_DrawString(&printpos, printbuf);
	//VCOM_Println(printbuf);

	// Print Src MAC
	offset = 6;
	printpos.y += 18;

	for (uint32_t i = 0; i < 6; ++i)
	{
		HexToChar(buf[offset + i], convbuf);
		printbuf[2 * i] = convbuf[0];
		printbuf[2 * i + 1] = convbuf[1];
	}

	//TFT_DrawString(&printpos, printbuf);
	//VCOM_Println(printbuf);

	// Print Eth Type
	offset = 12;
	printpos.y += 18;
	printbuf[4] = '\0';

	for (uint32_t i = 0; i < 2; ++i)
	{
		HexToChar(buf[offset + i], convbuf);
		printbuf[2 * i] = convbuf[0];
		printbuf[2 * i + 1] = convbuf[1];
	}

	//TFT_DrawString(&printpos, printbuf);
	//VCOM_Println(printbuf);
	//VCOM_Println("\0");
}

static bool MAC_Filter(uint8_t * buf, uint32_t const size, uint8_t * mac)
{
	for (uint8_t idx = 0; idx < 3; ++idx)
	{
		if ((buf[idx] != mac[idx]) || (buf[idx + 6] != mac[idx]))
			return false;
	}

	return true;
}

static void GetEthernetFrame(uint8_t * buf, uint32_t const size,
		EthernetFrame_t * frame)
{
	uint16_t tmp16 = 0;
	uint32_t tmp32 = 0;

	if (buf != 0 && size > 0 && frame != 0)
	{
		for (uint8_t i = 0; i < 6; ++i)
			frame->destination_addr[i] = buf[i];

		for (uint8_t i = 0; i < 6; ++i)
			frame->source_addr[i] = buf[i + 6];

		tmp16 = buf[12];
		tmp16 = ((tmp16 << 8) | buf[13]);

		frame->type = tmp16;
		frame->data = &(buf[14]);

		tmp32 = buf[size - 4];
		tmp32 = (tmp32 << 8) | buf[size - 3];
		tmp32 = (tmp32 << 8) | buf[size - 2];
		tmp32 = (tmp32 << 8) | buf[size - 1];

		frame->crc = tmp32;
	}
}

static void GetIPv4Packet(EthernetFrame_t * frame, IPv4_Packet_t * packet)
{
	uint8_t tmp8 = 0;
	uint16_t tmp16 = 0;

	if (frame->type == EtherType_IPv4)
	{
		packet->version = ((frame->data[0] & 0xF0) >> 4);
		packet->ihl = (frame->data[0] & 0x0F);
		packet->tos = frame->data[1];
		packet->total_length = ((frame->data[2] << 8) | (frame->data[3]));
		packet->identification = ((frame->data[4] << 8) | (frame->data[5]));
		packet->flags = ((frame->data[6] & 0xE0) >> 5);
		packet->fragment_offset = (((frame->data[6] & 0x1F) << 8)
				| (frame->data[7]));
		packet->ttl = frame->data[8];
		packet->protocol = frame->data[9];
		packet->header_checksum = ((frame->data[10] << 8) | (frame->data[11]));
		packet->source_addr[0] = frame->data[12];
		packet->source_addr[1] = frame->data[13];
		packet->source_addr[2] = frame->data[14];
		packet->source_addr[3] = frame->data[15];
		packet->destination_addr[0] = frame->data[16];
		packet->destination_addr[1] = frame->data[17];
		packet->destination_addr[2] = frame->data[18];
		packet->destination_addr[3] = frame->data[19];
		// options don't get in here
		packet->data = (uint32_t *) &(frame->data[(packet->ihl << 2)]);
	}
}

static void PrintFrameAndPacket(EthernetFrame_t * frame, IPv4_Packet_t * packet)
{
	static char printbuf[64];
	static char hexbuf[12];
	static uint32_t offset = 0;
	static char convbuf[2];

	//snprintf(printbuf, 64, "");

	for (uint32_t i = 0; i < 6; ++i)
	{
		HexToChar(frame->destination_addr[offset + i], convbuf);
		hexbuf[2 * i] = convbuf[0];
		hexbuf[2 * i + 1] = convbuf[1];
	}

	//snprintf(printbuf, 64, "Dst: %c%c:%c%c:%c%c:%c%c:%c%c:%c%c", hexbuf[0],
			//hexbuf[1], hexbuf[2], hexbuf[3], hexbuf[4], hexbuf[5], hexbuf[6],
			//hexbuf[7], hexbuf[8], hexbuf[9], hexbuf[10], hexbuf[11]);
	//VCOM_Println(printbuf);

	if (frame->type = EtherType_IPv4)
	{
		//snprintf(printbuf, 64, "Dst: %d.%d.%d.%d", packet->destination_addr[0],
				//packet->destination_addr[1], packet->destination_addr[2],
				//packet->destination_addr[3]);
		//VCOM_Println(printbuf);
	}

	offset += 6;
	for (uint32_t i = 0; i < 6; ++i)
	{
		HexToChar(frame->source_addr[offset + i], convbuf);
		hexbuf[2 * i] = convbuf[0];
		hexbuf[2 * i + 1] = convbuf[1];
	}

	//snprintf(printbuf, 64, "Src: %c%c:%c%c:%c%c:%c%c:%c%c:%c%c", hexbuf[0],
			//hexbuf[1], hexbuf[2], hexbuf[3], hexbuf[4], hexbuf[5], hexbuf[6],
			//hexbuf[7], hexbuf[8], hexbuf[9], hexbuf[10], hexbuf[11]);
	//VCOM_Println(printbuf);

	if (frame->type = EtherType_IPv4)
	{
		//snprintf(printbuf, 64, "Src: %d.%d.%d.%d", packet->source_addr[0],
				//packet->source_addr[1], packet->source_addr[2],
				//packet->source_addr[3]);
		//VCOM_Println(printbuf);
	}

	switch (frame->type)
	{
	case EtherType_IPv4:
		//snprintf(printbuf, 64, "Version: %d", packet->version);
		//VCOM_Println(printbuf);
		//snprintf(printbuf, 64, "IHL: %d", (packet->ihl << 2));
		//VCOM_Println(printbuf);
		//snprintf(printbuf, 64, "Length: %d", packet->total_length);
		//VCOM_Println(printbuf);
		//snprintf(printbuf, 64, "TLL: %d", packet->ttl);
		//VCOM_Println(printbuf);

		switch (packet->protocol)
		{
		case IP_Protocol_ICMP:
			//snprintf(printbuf, 64, "Protocol: ICMP");
			//VCOM_Println(printbuf);
			break;

		case IP_Protocol_IGMP:
			//snprintf(printbuf, 64, "Protocol: IGMP");
			//VCOM_Println(printbuf);
			break;

		case IP_Protocol_TCP:
			//snprintf(printbuf, 64, "Protocol: TCP");
			//VCOM_Println(printbuf);
			break;

		case IP_Protocol_UDP:
			//snprintf(printbuf, 64, "Protocol: UDP");
			//VCOM_Println(printbuf);
			break;

		default:
			//snprintf(printbuf, 64, "Unknown");
			//VCOM_Println(printbuf);
			break;
		}
		break;

	case EtherType_ARP:
		//snprintf(printbuf, 64, "ARP");
		//VCOM_Println(printbuf);
		break;

	default:
		//snprintf(printbuf, 64, "Unknown");
		//VCOM_Println(printbuf);
		break;
	}

	//snprintf(printbuf, 64, "\0");
	//VCOM_Println(printbuf);
}

static void LED_Callback(Button::Button_Name const name)
{
	LED::LED_Color col = LED::ALL;

	switch(name)
	{
	case Button::WAKEUP:
		col = LED::RED;
		break;

	case Button::USER0:
		col = LED::YELLOW;
		break;

	case Button::USER1:
		col = LED::GREEN;
		break;

	default:
		break;
	}

	leds.Toggle(col);
	Delay_ms(50);
}
