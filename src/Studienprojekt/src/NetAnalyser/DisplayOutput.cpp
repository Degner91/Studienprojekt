/**
 ******************************************************************************
 * \file    DisplayOutput.cpp
 * \author  Lucas Degner
 * \version V1.0.0
 * \date    13.03.2019
 * \brief   Implementation of display output
 ******************************************************************************
 */

#include "DisplayOutput.h"
#include "StdDefs.h"
#include "TFT_Display/TFT_Display.h"
#include "TFT_Display/Color.h"
#include "TFT_Display/Fonts/Font_Helvetica_16.h"
#include "TFT_Display/Fonts/Font_Helvetica_24.h"
#include "StringConverter.h"
#include <stdio.h>


static uint8_t const WindowSize = 8;
static uint8_t const DisplayBufferSize = 20;
static uint8_t const LineSpace_16 = 16;
static uint8_t const LineSpace_16_Header = 20;
static uint8_t const LineSpace_24 = 24;
static uint8_t const LineSpace_24_Header = 28;

static char DisplayBuffer[DisplayBufferSize];
static char const * MenuEntries[] = { "Network config", "MAC list", "Traffic overview" };

static TFT_Display & display = TFT_Display::GetInstance();


static void Display_PrintFooter(State const s)
{
	// Draw line
	PositionType ls = { 0, 286 };
	PositionType le = { 240, 286 };
	PositionType t =  { 0, 288 };

	display.DrawLine(&ls, &le);

	// Print footer text
	switch (s)
	{
	case MENU:
		t.x = 5;   display.DrawString(&t, "Up");
		t.x = 90;  display.DrawString(&t, "Enter");
		t.x = 206; display.DrawString(&t, "Dn");
		break;

	case NETCFG:
		t.x = 85;  display.DrawString(&t, "Menu");
		t.x = 185; display.DrawString(&t, "Now");
		break;

	case MACLIST:
		t.x = 5;   display.DrawString(&t, "Up");
		t.x = 82;  display.DrawString(&t, "Details");
		t.x = 206; display.DrawString(&t, "Dn");
		break;

	case OVERVIEW:
		t.x = 85;  display.DrawString(&t, "Menu");
		t.x = 185; display.DrawString(&t, "Now");
		break;

	case DETAILS:
		t.x = 5;   display.DrawString(&t, "MAC");
		t.x = 90;  display.DrawString(&t, "Menu");
		t.x = 181; display.DrawString(&t, "Infos");
		break;

	default:
		break;
	}
}

void Display_PrintNetCfg(wiz_NetInfo const & netinfo, uint32_t const leasetime)
{
	PositionType p = { 35, 0 };

	display.ClearScreen();
	display.DrawString(&p, "Network config");

	p.x = 5;
	p.y += 30;
	snprintf(DisplayBuffer, DisplayBufferSize, "IP: %d.%d.%d.%d",
			netinfo.ip[0], netinfo.ip[1], netinfo.ip[2], netinfo.ip[3]);
	display.DrawString(&p, DisplayBuffer);

	p.y += 26;
	snprintf(DisplayBuffer, DisplayBufferSize, "SN: %d.%d.%d.%d",
			netinfo.sn[0], netinfo.sn[1], netinfo.sn[2], netinfo.sn[3]);
	display.DrawString(&p, DisplayBuffer);

	p.y += 26;
	snprintf(DisplayBuffer, DisplayBufferSize, "GW: %d.%d.%d.%d",
			netinfo.gw[0], netinfo.gw[1], netinfo.gw[2], netinfo.gw[3]);
	display.DrawString(&p, DisplayBuffer);

	p.y += 26;
	snprintf(DisplayBuffer, DisplayBufferSize, "DNS: %d.%d.%d.%d",
			netinfo.dns[0], netinfo.dns[1], netinfo.dns[2], netinfo.dns[3]);
	display.DrawString(&p, DisplayBuffer);

	p.y += 26;
	TimeToString(leasetime, "Leasetime ", DisplayBuffer);
	display.DrawString(&p, DisplayBuffer);

	Display_PrintFooter(NETCFG);
}

void Display_PrintMenu(uint8_t const idx, uint8_t const menusize)
{
	if (idx >= menusize)
		return;

	PositionType pos = { 90, 0 };

	display.ClearScreen();
	display.DrawString(&pos, "Menu");

	pos.x = 5;
	pos.y = 32;

	for (uint8_t i = 0; i < menusize; ++i)
	{
		if (i == idx)
		{
			display.DrawStringInv(&pos, MenuEntries[i]);
		}
		else
		{
			display.DrawString(&pos, MenuEntries[i]);
		}

		pos.y += 32;
	}

	Display_PrintFooter(MENU);
}

void Display_PrintOverview(NetData const * data)
{

	PositionType pos = { 65, 0 };

	display.ClearScreen();
	display.DrawString(&pos, "Overview");
	display.SetFont(&Font_Helvetica_16);

	pos.x = 5;
	pos.y += LineSpace_24_Header;

	snprintf(DisplayBuffer, DisplayBufferSize, "ARP: %d", data->arp.received);
	display.DrawString(&pos, DisplayBuffer);
	pos.x += 120;

	snprintf(DisplayBuffer, DisplayBufferSize, "Other: %d", data->other.received);
	display.DrawString(&pos, DisplayBuffer);
	pos.x = 5;
	pos.y += LineSpace_16_Header;

	snprintf(DisplayBuffer, DisplayBufferSize, "ICMP: %d", data->icmp.received);
	display.DrawString(&pos, DisplayBuffer);
	pos.x += 120;

	snprintf(DisplayBuffer, DisplayBufferSize, "IGMP: %d", data->igmp.received);
	display.DrawString(&pos, DisplayBuffer);
	pos.x = 5;
	pos.y += LineSpace_16_Header;

	display.DrawString(&pos, "TCP");
	pos.x += 120;

	display.DrawString(&pos, "UDP");
	pos.x = 5;
	pos.y += LineSpace_16;

	snprintf(DisplayBuffer, DisplayBufferSize, "HTTP: %d", data->tcp.http.received);
	display.DrawString(&pos, DisplayBuffer);
	pos.x += 120;

	snprintf(DisplayBuffer, DisplayBufferSize, "DHCP C: %d",
			data->udp.dhcp_c.received);
	display.DrawString(&pos, DisplayBuffer);
	pos.x = 5;
	pos.y += LineSpace_16;

	snprintf(DisplayBuffer, DisplayBufferSize, "HTTPS: %d", data->tcp.https.received);
	display.DrawString(&pos, DisplayBuffer);
	pos.x += 120;

	snprintf(DisplayBuffer, DisplayBufferSize, "DHCP S: %d",
			data->udp.dhcp_s.received);
	display.DrawString(&pos, DisplayBuffer);
	pos.x = 5;
	pos.y += LineSpace_16;

	snprintf(DisplayBuffer, DisplayBufferSize, "SMTP: %d", data->tcp.smtp.received);
	display.DrawString(&pos, DisplayBuffer);
	pos.x += 120;

	snprintf(DisplayBuffer, DisplayBufferSize, "TFTP: %d", data->udp.tftp.received);
	display.DrawString(&pos, DisplayBuffer);
	pos.x = 5;
	pos.y += LineSpace_16;

	snprintf(DisplayBuffer, DisplayBufferSize, "IMAP: %d", data->tcp.imap.received);
	display.DrawString(&pos, DisplayBuffer);
	pos.x += 120;

	snprintf(DisplayBuffer, DisplayBufferSize, "IMAP: %d", data->udp.imap.received);
	display.DrawString(&pos, DisplayBuffer);
	pos.x = 5;
	pos.y += LineSpace_16;

	snprintf(DisplayBuffer, DisplayBufferSize, "SSH: %d", data->tcp.ssh.received);
	display.DrawString(&pos, DisplayBuffer);
	pos.x += 120;

	snprintf(DisplayBuffer, DisplayBufferSize, "SSH: %d", data->udp.ssh.received);
	display.DrawString(&pos, DisplayBuffer);
	pos.x = 5;
	pos.y += LineSpace_16;

	snprintf(DisplayBuffer, DisplayBufferSize, "Other: %d", data->tcp.other.received);
	display.DrawString(&pos, DisplayBuffer);
	pos.x += 120;

	snprintf(DisplayBuffer, DisplayBufferSize, "Other: %d", data->udp.other.received);
	display.DrawString(&pos, DisplayBuffer);
	pos.x = 5;
	pos.y += LineSpace_16;

	display.SetFont(&Font_Helvetica_24);

	Display_PrintFooter(OVERVIEW);
}

void Display_PrintMacList(FrameDecoder const & decoder, uint8_t const idx)
{
	static uint8_t begin = 0;
	static uint8_t end = 0;
	static uint16_t oldLength = 0;
	uint16_t length = decoder.NetData_GetEntryCount();
	char buffer[DisplayBufferSize];
	PositionType pos = { 73, 0 };

	display.ClearScreen();
	display.DrawString(&pos, "MAC list");

	pos.x = 5;
	pos.y = LineSpace_24_Header;

	if (length > 0)
	{
		// Is new window calculation nesscessary
		if (begin == end || length != oldLength || idx < begin || idx > end)
		{
			// Calculate new window
			if (length < WindowSize)
			{
				begin = idx;
				end = length - 1;
			}
			else if (idx + WindowSize < length)
			{
				begin = idx;
				end = idx + WindowSize - 1;
			}
			else
			{
				begin = length - WindowSize;
				end = length - 1;
			}
		}

		for (uint8_t i = begin; i <= end; ++i)
		{
			MacToString(decoder.NetData_GetAt(i)->mac, buffer);

			if (i == idx)
				display.DrawStringInv(&pos, buffer);
			else
				display.DrawString(&pos, buffer);

			pos.y += 32;
		}
	}

	oldLength = length;

	Display_PrintFooter(MACLIST);
}

void Display_PrintDetails(FrameDecoder const & decoder, uint8_t const macIdx, uint8_t const page)
{
	NetData const * data;
	char buffer[DisplayBufferSize];
	PositionType pos = { 60, 0 };

	display.ClearScreen();
	snprintf(buffer, DisplayBufferSize, "Details %d/3", (page + 1));
	display.DrawString(&pos, buffer);

	pos.x = 5;
	pos.y += LineSpace_24_Header;

	data = decoder.NetData_GetAt(macIdx);
	MacToString(data->mac, buffer);
	display.DrawString(&pos, buffer);
	pos.y += LineSpace_24;

	snprintf(buffer, DisplayBufferSize, "%d.%d.%d.%d",
			data->ip[0], data->ip[1], data->ip[2], data->ip[3]);
	display.DrawString(&pos, buffer);
	display.SetFont(&Font_Helvetica_16);
	pos.x = 20;
	pos.y += LineSpace_24_Header;

	switch (page)
	{
	case 0:
		display.DrawString(&pos, "General");
		pos.x = 5;
		pos.y += LineSpace_16_Header;

		snprintf(buffer, DisplayBufferSize, "ARP: %d/%d", data->arp.sent, data->arp.received);
		display.DrawString(&pos, buffer);
		pos.y += LineSpace_16;

		snprintf(buffer, DisplayBufferSize, "ICMP: %d/%d", data->icmp.sent,	data->icmp.received);
		display.DrawString(&pos, buffer);
		pos.y += LineSpace_16;

		snprintf(buffer, DisplayBufferSize, "IGMP: %d/%d", data->igmp.sent,	data->igmp.received);
		display.DrawString(&pos, buffer);
		pos.y += LineSpace_16;

		snprintf(buffer, DisplayBufferSize, "Other: %d/%d", data->other.sent, data->other.received);
		display.DrawString(&pos, buffer);
		break;

	case 1:
		display.DrawString(&pos, "TCP-Ports");
		pos.x = 5;
		pos.y += LineSpace_16_Header;

		snprintf(buffer, DisplayBufferSize, "HTTP: %d/%d", data->tcp.http.sent,	data->tcp.http.received);
		display.DrawString(&pos, buffer);
		pos.y += LineSpace_16;

		snprintf(buffer, DisplayBufferSize, "HTTPS: %d/%d",	data->tcp.https.sent, data->tcp.https.received);
		display.DrawString(&pos, buffer);
		pos.y += LineSpace_16;

		snprintf(buffer, DisplayBufferSize, "IMAP: %d/%d", data->tcp.imap.sent,	data->tcp.imap.received);
		display.DrawString(&pos, buffer);
		pos.y += LineSpace_16;

		snprintf(buffer, DisplayBufferSize, "SMTP: %d/%d", data->tcp.smtp.sent,	data->tcp.smtp.received);
		display.DrawString(&pos, buffer);
		pos.y += LineSpace_16;

		snprintf(buffer, DisplayBufferSize, "SSH: %d/%d", data->tcp.ssh.sent, data->tcp.ssh.received);
		display.DrawString(&pos, buffer);
		pos.y += LineSpace_16;

		snprintf(buffer, DisplayBufferSize, "Other: %d/%d",
				data->tcp.other.sent, data->tcp.other.received);
		display.DrawString(&pos, buffer);
		break;

	case 2:
		display.DrawString(&pos, "UDP-Ports");
		pos.x = 5;
		pos.y += LineSpace_16_Header;

		snprintf(buffer, DisplayBufferSize, "DHCP Client: %d/%d", data->udp.dhcp_c.sent, data->udp.dhcp_c.received);
		display.DrawString(&pos, buffer);
		pos.y += LineSpace_16;

		snprintf(buffer, DisplayBufferSize, "DHCP Server: %d/%d", data->udp.dhcp_s.sent, data->udp.dhcp_s.received);
		display.DrawString(&pos, buffer);
		pos.y += LineSpace_16;

		snprintf(buffer, DisplayBufferSize, "IMAP: %d/%d", data->udp.imap.sent,	data->udp.imap.received);
		display.DrawString(&pos, buffer);
		pos.y += LineSpace_16;

		snprintf(buffer, DisplayBufferSize, "SSH: %d/%d", data->udp.ssh.sent, data->udp.ssh.received);
		display.DrawString(&pos, buffer);
		pos.y += LineSpace_16;

		snprintf(buffer, DisplayBufferSize, "TFTP: %d/%d", data->udp.tftp.sent,	data->udp.tftp.received);
		display.DrawString(&pos, buffer);
		pos.y += LineSpace_16;

		snprintf(buffer, DisplayBufferSize, "Other: %d/%d",	data->udp.other.sent, data->udp.other.received);
		display.DrawString(&pos, buffer);
		break;

	default:
		break;
	}

	display.SetFont(&Font_Helvetica_24);

	Display_PrintFooter(DETAILS);
}
