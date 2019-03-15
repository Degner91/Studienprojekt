/*
 * main.cpp
 *
 *  Created on: 29.01.2019
 *      Author: Lucas Degner
 */

#include "stm32f0xx_rcc.h"
#include "LED/LED.h"
#include "Button/Button.h"
#include "VCOM/VCOM.h"
#include "SPI/SPI.h"
#include "W5500/w5500.h"
#include "TFT_Display/TFT_Display.h"
#include "TFT_Display/Fonts/Font_Helvetica_16.h"
#include "TFT_Display/Fonts/Font_Helvetica_24.h"
#include "Delay.h"
#include "DHCP/dhcp.h"
#include "Socket/socket.h"
#include "Utilities/StringConverter.h"
#include "NetAnalyser/TerminalOutput.h"
#include "NetAnalyser/DisplayOutput.h"
#include <stdio.h>

static uint8_t const MACRAW_SOCKET = 0;
static uint8_t const DHCP_SOCKET = 1;
static uint8_t const MenuSize = 3;
static uint16_t const EthBufferSize = 78; // 78 to get IP and protocol and port numbers, 1518 bzw. 1522(VLAN) for all data
static uint16_t const DHCPBufferSize = 2048;
static uint8_t const DetailsPages = 3;

//! Instances of hardware
static LED & leds = LED::GetInstance();
static Button & buttons = Button::GetInstance();
static VCOM & vcom = VCOM::GetInstance();
static TFT_Display & display = TFT_Display::GetInstance();

//! System functions
/**
 * \brief Initialize system core clock to 48MHz
 * \param None
 * \return None
 */
static void SystemClockConfig();

/**
 * \brief To be called funtion in case of an error
 * \param None
 * \return None
 */
static void ErrorFunc();

// Netinfos etc.
static wiz_NetInfo netinfo;
uint32_t leasetime = 0; // not static because it is decremented in SysTick_Handler
static bool NetinfoChanged = false;

// DHCP callback functions
/**
 * \brief Callback function, called when IP address is assigned by DHCP
 * \param None
 * \return None
 */
static void IP_Assign();

/**
 * \brief Callback function, called when IP address is changed by DHCP
 * \param None
 * \return None
 */
static void IP_Update();

/**
 * \brief Callback function, called when IP address conflict is found
 * \param None
 * \return None
 */
static void IP_Conflict();

int main()
{
	uint8_t dhcp_buffer[DHCPBufferSize];
	uint8_t eth_buffer[EthBufferSize];
	uint16_t frame_length = 0;
	uint8_t menuIdx = 0;
	uint8_t macIdx = 0;
	uint8_t detailsPage = 0;
	State startState = MENU; //MENU;
	State currentState = startState;
	State nextState = startState;
	FrameDecoder decoder;
	NetData const * all = 0;

	netinfo.dhcp = NETINFO_STATIC;
	bool stateChanged = true;
	bool menuIndexChanged = false;
	bool macScreenChanged = false;
	bool pageChanged = false;

	Button::Button_Name currentButton = Button::NOBTN;

	// Core initialization
	SystemClockConfig();
	InitializeSysTick();

	// HW initialization
	leds.Initialize();
	leds.On(LED::RED);
	buttons.Initialize();
	vcom.Initialize();
	display.Initialize();
	SPI_Initialize();

	vcom.Println("");
	vcom.Println("");
	vcom.Println("Hardware initialized");

	leds.Off(LED::RED);
	leds.On(LED::YELLOW);

	// HW configuration
	display.SetFont(&Font_Helvetica_24);
	display.SetBackgroundColor(TFT_COLOUR_WHITE);
	display.SetForegroundColor(TFT_COLOUR_BLACK);
	display.ClearScreen();
	reg_wizchip_cs_cbfunc(SPI_CS_Select, SPI_CS_Deselect);
	reg_wizchip_spi_cbfunc(SPI_ReadByte, SPI_WriteByte);

	netinfo.mac[0] = 0xB1;
	netinfo.mac[1] = 0x6B;
	netinfo.mac[2] = 0x00;
	netinfo.mac[3] = 0xBD;
	netinfo.mac[4] = 0xBA;
	netinfo.mac[5] = 0xBE;
	setSHAR(netinfo.mac);

	vcom.Println("Configuration successful");
	vcom.Print("Network configuration ");
	vcom.Println((netinfo.dhcp == NETINFO_STATIC) ? "static" : "dynamic (DHCP)");

	if (netinfo.dhcp == NETINFO_STATIC)
	{
		netinfo.ip[0] = 192;
		netinfo.ip[1] = 168;
		netinfo.ip[2] = 0;
		netinfo.ip[3] = 226;

		netinfo.sn[0] = 255;
		netinfo.sn[1] = 255;
		netinfo.sn[2] = 255;
		netinfo.sn[3] = 0;

		netinfo.gw[0] = 192;
		netinfo.gw[1] = 168;
		netinfo.gw[2] = 0;
		netinfo.gw[3] = 1;

		netinfo.dns[0] = 8;
		netinfo.dns[1] = 8;
		netinfo.dns[2] = 8;
		netinfo.dns[3] = 8;

		leasetime = 0;

		setSIPR(netinfo.ip);
		setSUBR(netinfo.sn);
		setGAR(netinfo.gw);
	}
	else
	{
		reg_dhcp_cbfunc(IP_Assign, IP_Update, IP_Conflict);
		DHCP_init(DHCP_SOCKET, dhcp_buffer);

		PositionType load_pos = { 5, 148 };
		display.DrawString(&load_pos, "Get IP from DHCP...");
		vcom.Print("Gathering IP from DHCP server... ");

		// Get IP from DHCP
		while (DHCP_run() != DHCP_IP_LEASED);

		vcom.Println("done");
	}

	// vcom print network settings
	Terminal_PrintNetCfg(netinfo, leasetime, false);

	// Open MACRAW socket
	vcom.Print("Opening socket 0 in MACRAW mode ");

	if (socket(MACRAW_SOCKET, Sn_MR_MACRAW, 0, 0) != MACRAW_SOCKET)
	{
		vcom.Println("failed");
		ErrorFunc();
	}

	vcom.Println("succeeded");

	// Add own MAC and IP in the list
	NetData me;

	decoder.NetData_StructInit(&me);
	vcom.Println("Adding own network configuration to list");

	me.mac[0] = netinfo.mac[0];
	me.mac[1] = netinfo.mac[1];
	me.mac[2] = netinfo.mac[2];
	me.mac[3] = netinfo.mac[3];
	me.mac[4] = netinfo.mac[4];
	me.mac[5] = netinfo.mac[5];
	me.ip[0] = netinfo.ip[0];
	me.ip[1] = netinfo.ip[1];
	me.ip[2] = netinfo.ip[2];
	me.ip[3] = netinfo.ip[3];
	decoder.NetData_Add(&me);

	leds.Off(LED::YELLOW);
	leds.On(LED::GREEN);

	vcom.Println("Network sniffer successfully set up");
	vcom.Println("-----------------------------------");
	vcom.Println("");

	while (1)
	{
		currentButton = buttons.GetState();

		if (netinfo.dhcp == NETINFO_DHCP)
		{
			DHCP_run();
		}

		frame_length = recvfrom(MACRAW_SOCKET, eth_buffer, EthBufferSize, 0, 0);

		if (frame_length > 0)
		{
			decoder.EthFrame_Decode(eth_buffer, frame_length);
			all = decoder.NetData_GetAll();
		}

		switch (currentState)
		{
		case MENU:
			if (stateChanged || menuIndexChanged)
			{
				Display_PrintMenu(menuIdx, MenuSize);
				menuIndexChanged = false;
			}

			if (currentButton == Button::WAKEUP)
			{
				if (menuIdx > 0)
				{
					menuIdx--;
					menuIndexChanged = true;
				}
			}
			else if (currentButton == Button::USER0)
			{
				switch (menuIdx)
				{
				case (NETCFG - 1):
					nextState = NETCFG;
					break;
				case (MACLIST - 1):
					nextState = MACLIST;
					break;
				case (OVERVIEW - 1):
					nextState = OVERVIEW;
					break;
				default:
					break;
				}
			}
			else if (currentButton == Button::USER1)
			{
				if (menuIdx < MenuSize - 1)
				{
					menuIdx++;
					menuIndexChanged = true;
				}
			}

			break;

		case NETCFG:
			if (stateChanged || NetinfoChanged)
			{
				Display_PrintNetCfg(netinfo, leasetime);
				Terminal_PrintNetCfg(netinfo, leasetime, true);
				NetinfoChanged = false;
			}

			if (currentButton == Button::USER0)
			{
				nextState = MENU;
			}
			else if (currentButton == Button::USER1)
			{
				Display_PrintNetCfg(netinfo, leasetime);
				Terminal_PrintNetCfg(netinfo, leasetime, true);
			}

			break;

		case MACLIST:
			if (stateChanged || macScreenChanged)
			{
				Display_PrintMacList(decoder, macIdx);
				macScreenChanged = false;
				if (stateChanged)
					Terminal_PrintMacList(decoder);
				detailsPage = 0;
			}

			if (currentButton == Button::USER1)
			{
				if (macIdx < decoder.NetData_GetEntryCount() - 1)
				{
					macIdx++;
					macScreenChanged = true;
				}
			}
			else if (currentButton == Button::WAKEUP)
			{
				if (macIdx > 0)
				{
					macIdx--;
					macScreenChanged = true;
				}
			}
			else if (currentButton == Button::USER0)
			{
				nextState = DETAILS;
			}

			break;

		case OVERVIEW:
			if (stateChanged)
			{
				Display_PrintOverview(all);
				Terminal_PrintOverview(all);
			}

			if (currentButton == Button::USER0)
			{
				nextState = MENU;
			}
			else if (currentButton == Button::USER1)
			{
				Display_PrintOverview(all);
				Terminal_PrintOverview(all);
			}

			break;

		case DETAILS:
			if (stateChanged || pageChanged)		// || macScreenChanged)
			{
				Display_PrintDetails(decoder, macIdx, detailsPage);

				if (stateChanged)
					Terminal_PrintDetails(decoder, macIdx);

				pageChanged = false;
			}

			if (currentButton == Button::WAKEUP)
			{
				nextState = MACLIST;
			}
			else if (currentButton == Button::USER0)
			{
				nextState = MENU;
				macIdx = 0;
			}
			else if (currentButton == Button::USER1)
			{
				detailsPage = (detailsPage < DetailsPages - 1 ? detailsPage + 1 : 0);
				pageChanged = true;
			}
			break;

		default: // forbidden state
			ErrorFunc();
			break;
		}

		stateChanged = false;

		if (nextState != currentState)
		{
			currentState = nextState;
			stateChanged = true;
		}

	}

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

static void IP_Assign()
{
	getIPfromDHCP(netinfo.ip);
	getSNfromDHCP(netinfo.sn);
	getGWfromDHCP(netinfo.gw);
	getDNSfromDHCP(netinfo.dns);
	leasetime = getDHCPLeasetime();
	NetinfoChanged = true;
}

static void IP_Update()
{
	getIPfromDHCP(netinfo.ip);
	getSNfromDHCP(netinfo.sn);
	getGWfromDHCP(netinfo.gw);
	getDNSfromDHCP(netinfo.dns);
	leasetime = getDHCPLeasetime();
	NetinfoChanged = true;
}

static void IP_Conflict()
{
	ErrorFunc();
}
