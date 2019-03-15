/**
 ******************************************************************************
 * \file    TerminalOutput.cpp
 * \author  Lucas Degner
 * \version V1.0.0
 * \date    13.03.2019
 * \brief   Implementation of terminal output functions
 ******************************************************************************
 */

#include "TerminalOutput.h"
#include "VCOM/VCOM.h"
#include "StringConverter.h"
#include <stdio.h>


static VCOM & vcom = VCOM::GetInstance();

static uint8_t const VCOM_BufferSize = 80;
static char VCOM_Buffer[VCOM_BufferSize];

void Terminal_PrintNetCfg(wiz_NetInfo const & netinfo, uint32_t const leasetime, bool const printTitle)
{
	if (printTitle)
		vcom.Println("Network configuration");

	// MAC
	MacToString(netinfo.mac, VCOM_Buffer);
	vcom.Print("MAC : ");
	vcom.Println(VCOM_Buffer);

	// IP
	snprintf(VCOM_Buffer, VCOM_BufferSize, "IP  : %d.%d.%d.%d",
			netinfo.ip[0], netinfo.ip[1], netinfo.ip[2], netinfo.ip[3]);
	vcom.Println(VCOM_Buffer);

	// SN
	snprintf(VCOM_Buffer, VCOM_BufferSize, "SN  : %d.%d.%d.%d",
			netinfo.sn[0], netinfo.sn[1], netinfo.sn[2], netinfo.sn[3]);
	vcom.Println(VCOM_Buffer);

	// GW
	snprintf(VCOM_Buffer, VCOM_BufferSize, "GW  : %d.%d.%d.%d",
			netinfo.gw[0], netinfo.gw[1], netinfo.gw[2], netinfo.gw[3]);
	vcom.Println(VCOM_Buffer);

	// DNS
	snprintf(VCOM_Buffer, VCOM_BufferSize, "DNS : %d.%d.%d.%d",
			netinfo.dns[0], netinfo.dns[1], netinfo.dns[2], netinfo.dns[3]);
	vcom.Println(VCOM_Buffer);

	if (netinfo.dhcp == NETINFO_DHCP)
	{
		TimeToString(leasetime, "Leasetime: ", VCOM_Buffer);
		vcom.Println(VCOM_Buffer);
	}

	if (printTitle)
		vcom.Println("");
}

void Terminal_PrintMacList(FrameDecoder const & decoder)
{
	uint16_t entries = decoder.NetData_GetEntryCount();
	NetData const * tmp;

	vcom.Println("Detected MAC addresses");

	for (uint16_t i = 0; i < entries; ++i)
	{
		tmp = decoder.NetData_GetAt(i);
		MacToString(tmp->mac, VCOM_Buffer);
		vcom.Print(VCOM_Buffer);
		snprintf(VCOM_Buffer, VCOM_BufferSize, " -> %d.%d.%d.%d",
				tmp->ip[0], tmp->ip[1], tmp->ip[2], tmp->ip[3]);
		vcom.Println(VCOM_Buffer);
	}

	vcom.Println("");
}

void Terminal_PrintDetails(FrameDecoder const & decoder, uint8_t const macIdx)
{
	uint16_t entries = decoder.NetData_GetEntryCount();

	if (macIdx >= entries)
		return;

	NetData const * tmp = decoder.NetData_GetAt(macIdx);

	MacToString(tmp->mac, VCOM_Buffer);
	vcom.Print("MAC: ");
	vcom.Println(VCOM_Buffer);

	snprintf(VCOM_Buffer, VCOM_BufferSize, "IP : %d.%d.%d.%d",
			tmp->ip[0],	tmp->ip[1], tmp->ip[2], tmp->ip[3]);
	vcom.Println(VCOM_Buffer);

	vcom.Println("");
	vcom.Println("General packet counter");

	snprintf(VCOM_Buffer, VCOM_BufferSize, "ARP: %d/%d",
			tmp->arp.sent, tmp->arp.received);
	vcom.Println(VCOM_Buffer);

	snprintf(VCOM_Buffer, VCOM_BufferSize, "ICMP: %d/%d",
			tmp->icmp.sent, tmp->icmp.received);
	vcom.Println(VCOM_Buffer);

	snprintf(VCOM_Buffer, VCOM_BufferSize, "IGMP: %d/%d",
			tmp->igmp.sent, tmp->igmp.received);
	vcom.Println(VCOM_Buffer);

	snprintf(VCOM_Buffer, VCOM_BufferSize, "Other: %d/%d",
			tmp->other.sent, tmp->other.received);
	vcom.Println(VCOM_Buffer);

	vcom.Println("");
	vcom.Println("TCP packet counter");

	snprintf(VCOM_Buffer, VCOM_BufferSize, "HTTP: %d/%d",
			tmp->tcp.http.sent, tmp->tcp.http.received);
	vcom.Println(VCOM_Buffer);

	snprintf(VCOM_Buffer, VCOM_BufferSize, "HTTPS: %d/%d",
			tmp->tcp.https.sent, tmp->tcp.https.received);
	vcom.Println(VCOM_Buffer);

	snprintf(VCOM_Buffer, VCOM_BufferSize, "IMAP: %d/%d",
			tmp->tcp.imap.sent, tmp->tcp.imap.received);
	vcom.Println(VCOM_Buffer);

	snprintf(VCOM_Buffer, VCOM_BufferSize, "SMTP: %d/%d",
			tmp->tcp.smtp.sent, tmp->tcp.smtp.received);
	vcom.Println(VCOM_Buffer);

	snprintf(VCOM_Buffer, VCOM_BufferSize, "SSH: %d/%d",
			tmp->tcp.ssh.sent, tmp->tcp.ssh.received);
	vcom.Println(VCOM_Buffer);

	snprintf(VCOM_Buffer, VCOM_BufferSize, "Other: %d/%d",
			tmp->tcp.other.sent, tmp->tcp.other.received);
	vcom.Println(VCOM_Buffer);

	vcom.Println("");
	vcom.Println("UDP packet counter");

	snprintf(VCOM_Buffer, VCOM_BufferSize, "DHCP Server: %d/%d",
			tmp->udp.dhcp_s.sent, tmp->udp.dhcp_s.received);
	vcom.Println(VCOM_Buffer);

	snprintf(VCOM_Buffer, VCOM_BufferSize, "DHCP Client: %d/%d",
			tmp->udp.dhcp_c.sent, tmp->udp.dhcp_c.received);
	vcom.Println(VCOM_Buffer);

	snprintf(VCOM_Buffer, VCOM_BufferSize, "IMAP: %d/%d",
			tmp->udp.imap.sent, tmp->udp.imap.received);
	vcom.Println(VCOM_Buffer);

	snprintf(VCOM_Buffer, VCOM_BufferSize, "TFTP: %d/%d",
			tmp->udp.tftp.sent, tmp->udp.tftp.received);
	vcom.Println(VCOM_Buffer);

	snprintf(VCOM_Buffer, VCOM_BufferSize, "SSH: %d/%d",
			tmp->udp.ssh.sent, tmp->udp.ssh.received);
	vcom.Println(VCOM_Buffer);

	snprintf(VCOM_Buffer, VCOM_BufferSize, "Other: %d/%d",
			tmp->udp.other.sent, tmp->udp.other.received);
	vcom.Println(VCOM_Buffer);

	vcom.Println("");

}

void Terminal_PrintOverview(NetData const * all)
{
	vcom.Println("Overview");
	vcom.Println("General packet counter");

	snprintf(VCOM_Buffer, VCOM_BufferSize, "ARP: %d", all->arp.received);
	vcom.Println(VCOM_Buffer);

	snprintf(VCOM_Buffer, VCOM_BufferSize, "ICMP: %d", all->icmp.received);
	vcom.Println(VCOM_Buffer);

	snprintf(VCOM_Buffer, VCOM_BufferSize, "IGMP: %d", all->igmp.received);
	vcom.Println(VCOM_Buffer);

	snprintf(VCOM_Buffer, VCOM_BufferSize, "Other: %d", all->other.received);
	vcom.Println(VCOM_Buffer);

	vcom.Println("");
	vcom.Println("TCP packet counter");

	snprintf(VCOM_Buffer, VCOM_BufferSize, "HTTP: %d", all->tcp.http.received);
	vcom.Println(VCOM_Buffer);

	snprintf(VCOM_Buffer, VCOM_BufferSize, "HTTPS: %d", all->tcp.https.received);
	vcom.Println(VCOM_Buffer);

	snprintf(VCOM_Buffer, VCOM_BufferSize, "IMAP: %d", all->tcp.imap.received);
	vcom.Println(VCOM_Buffer);

	snprintf(VCOM_Buffer, VCOM_BufferSize, "SMTP: %d", all->tcp.smtp.received);
	vcom.Println(VCOM_Buffer);

	snprintf(VCOM_Buffer, VCOM_BufferSize, "SSH: %d", all->tcp.ssh.received);
	vcom.Println(VCOM_Buffer);

	snprintf(VCOM_Buffer, VCOM_BufferSize, "Other: %d", all->tcp.other.received);
	vcom.Println(VCOM_Buffer);

	vcom.Println("");
	vcom.Println("UDP packet counter");

	snprintf(VCOM_Buffer, VCOM_BufferSize, "DHCP Server: %d", all->udp.dhcp_s.received);
	vcom.Println(VCOM_Buffer);

	snprintf(VCOM_Buffer, VCOM_BufferSize, "DHCP Client: %d", all->udp.dhcp_c.received);
	vcom.Println(VCOM_Buffer);

	snprintf(VCOM_Buffer, VCOM_BufferSize, "IMAP: %d", all->udp.imap.received);
	vcom.Println(VCOM_Buffer);

	snprintf(VCOM_Buffer, VCOM_BufferSize, "TFTP: %d", all->udp.tftp.received);
	vcom.Println(VCOM_Buffer);

	snprintf(VCOM_Buffer, VCOM_BufferSize, "SSH: %d", all->udp.ssh.received);
	vcom.Println(VCOM_Buffer);

	snprintf(VCOM_Buffer, VCOM_BufferSize, "Other: %d", all->udp.other.received);
	vcom.Println(VCOM_Buffer);

	vcom.Println("");
}
