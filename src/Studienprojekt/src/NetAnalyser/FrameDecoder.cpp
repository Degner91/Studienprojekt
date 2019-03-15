/**
 ******************************************************************************
 * \file    FrameDecoder.cpp
 * \author  Lucas Degner
 * \version V1.0.0
 * \date    09.03.2019
 * \brief   Implementation of ethernet frame decoder class and functions
 ******************************************************************************
 */

#include "FrameDecoder.h"

/**
 * \brief Type of overlying protocol
 */
enum EtherType
{
	ET_IPV4 = 0x0800,      //!< IPv4 protocol
	ET_ARP = 0x0806,       //!< ARP protocol
	ET_WoL = 0x0842,       //!< Wake on LAN protocol
	ET_RARP = 0x8035,      //!< RARP protocol
	ET_VLAN = 0x8100,      //!< VLAN tag
	ET_IPv6 = 0x86DD,      //!< IPv6 protocol
	ET_HomePlugAV = 0x88E1 //!< HomePlugAV protocol
};

/**
 * \brief Type of IP packet
 */
enum IP_Protocol
{
	IP_PROT_ICMP = 1, //!< ICMP packet
	IP_PROT_IGMP = 2, //!< IGMP packet
	IP_PROT_TCP = 6, //!< TCP packet
	IP_PROT_UDP = 17 //!< UDP packet
};

/**
 * \brief TCP and UDP port numbers
 */
enum Port_Number
{
	Port_SSH = 22,        //!< SSH port number (TCP and UDP)
	Port_SMTP = 25,       //!< SMTP port number (TCP)
	Port_DHCP_Server = 67,       //!< DHCP_Server port number (UDP)
	Port_DHCP_Client = 68,       //!< DHCP_Client port number (UDP)
	Port_TFTP = 69,       //!< TFTP port number (UDP)
	Port_HTTP = 80,       //!< HTTP port number (TCP)
	Port_IMAP = 143,      //!< IMAP port number (TCP and UDP)
	Port_HTTPS = 443      //!< HTTPS port number (TCP)
};

void FrameDecoder::EthFrame_Decode(uint8_t const * const buffer,
		uint16_t const length)
{
	if (!buffer || length < 14)
		return;

	uint8_t const * buf = buffer;
	NetData src;
	NetData dst;
	uint16_t mac_pos = 0;
	uint8_t eoh = 0;
	uint8_t ip_prot = 0;
	uint16_t port_src = 0;
	uint16_t port_dst = 0;

	NetData_StructInit(&src);
	NetData_StructInit(&dst);

	//buf += 6; // dont know why but it works

	// get dst mac
	for (uint8_t i = 0; i < 6; ++i)
		dst.mac[i] = buf[i];

	buf += 6;

	// get dst mac
	for (uint8_t i = 0; i < 6; ++i)
		src.mac[i] = buf[i];

	buf += 6;

	uint16_t eth_type = ((*buf) << 8) | (*(buf + 1));

	buf += 2;

	switch (eth_type)
	{
	case ET_ARP:
		dst.arp.received++;
		src.arp.sent++;
		all.arp.received++;
		break;

	case ET_IPV4:
		eoh = ((*buf & 0x0F) << 2) - 12; // end of IP header
		buf += 9; // position of protocol identifier

		ip_prot = *buf;

		buf += 3;

		for (uint8_t i = 0; i < 4; ++i)
		{
			src.ip[i] = buf[i];
			dst.ip[i] = buf[i + 4];
		}

		buf += eoh;

		switch (ip_prot)
		{
		case IP_PROT_ICMP:
			src.icmp.sent++;
			dst.icmp.received++;
			all.icmp.received++;
			break;

		case IP_PROT_IGMP:
			src.igmp.sent++;
			dst.igmp.received++;
			all.igmp.received++;
			break;

		case IP_PROT_TCP:
		case IP_PROT_UDP:

			port_src = (*buf << 8) | (*(buf + 1));
			port_dst = (*(buf + 2) << 8) | (*(buf + 3));

			switch (port_src)
			{
			case Port_DHCP_Client:
				src.udp.dhcp_c.sent++;
				break;

			case Port_DHCP_Server:
				src.udp.dhcp_s.sent++;
				break;

			case Port_HTTP:
				src.tcp.http.sent++;
				break;

			case Port_HTTPS:
				src.tcp.https.sent++;
				break;

			case Port_IMAP:
				if (ip_prot == IP_PROT_TCP)
				{
					src.tcp.imap.sent++;
				}
				else
				{
					src.udp.imap.sent++;
				}
				break;

			case Port_SMTP:
				src.tcp.smtp.sent++;
				break;

			case Port_SSH:
				if (ip_prot == IP_PROT_TCP)
				{
					src.tcp.ssh.sent++;
				}
				else
				{
					src.udp.ssh.sent++;
				}
				break;

			case Port_TFTP:
				src.udp.tftp.sent++;
				break;

			default:
				if (ip_prot == IP_PROT_TCP)
				{
					dst.tcp.other.sent++;
					all.tcp.other.sent++;
				}
				else
				{
					dst.udp.other.sent++;
					all.udp.other.sent++;
				}
				break;
			}

			switch (port_dst)
			{
			case Port_DHCP_Client:
				dst.udp.dhcp_c.received++;
				all.udp.dhcp_c.received++;
				break;

			case Port_DHCP_Server:
				dst.udp.dhcp_s.received++;
				all.udp.dhcp_s.received++;
				break;

			case Port_HTTP:
				dst.tcp.http.received++;
				all.tcp.http.received++;
				break;

			case Port_HTTPS:
				dst.tcp.https.received++;
				all.tcp.https.received++;
				break;

			case Port_IMAP:
				if (ip_prot == IP_PROT_TCP)
				{
					dst.tcp.imap.received++;
					all.tcp.imap.received++;
				}
				else
				{
					dst.udp.imap.received++;
					all.udp.imap.received++;
				}
				break;

			case Port_SMTP:
				dst.tcp.smtp.received++;
				all.tcp.smtp.received++;
				break;

			case Port_SSH:
				if (ip_prot == IP_PROT_TCP)
				{
					dst.tcp.ssh.received++;
					all.tcp.ssh.received++;
				}
				else
				{
					dst.udp.ssh.received++;
					all.udp.ssh.received++;
				}
				break;

			case Port_TFTP:
				dst.udp.tftp.received++;
				all.udp.tftp.received++;
				break;

			default:
				if (ip_prot == IP_PROT_TCP)
				{
					dst.tcp.other.received++;
					all.tcp.other.received++;
				}
				else
				{
					dst.udp.other.received++;
					all.udp.other.received++;
				}
				break;

			}
			break;

		default:
			src.other.sent++;
			dst.other.received++;
			all.other.received++;
			break;
		}
		break;

	default:
		return;
	}

	if (IsMacListed(src.mac, &mac_pos))
	{
		for (uint16_t i = 0; i < entryCnt; ++i)
		{
			if (i != mac_pos)
				continue;

			entries[i].arp.sent += src.arp.sent;
			entries[i].icmp.sent += src.icmp.sent;
			entries[i].igmp.sent += src.igmp.sent;
			entries[i].other.sent += src.other.sent;
			entries[i].tcp.http.sent += src.tcp.http.sent;
			entries[i].tcp.https.sent += src.tcp.https.sent;
			entries[i].tcp.imap.sent += src.tcp.imap.sent;
			entries[i].tcp.smtp.sent += src.tcp.smtp.sent;
			entries[i].tcp.ssh.sent += src.tcp.ssh.sent;
			entries[i].tcp.other.sent += src.tcp.other.sent;
			entries[i].udp.dhcp_c.sent += src.udp.dhcp_c.sent;
			entries[i].udp.dhcp_s.sent += src.udp.dhcp_s.sent;
			entries[i].udp.imap.sent += src.udp.imap.sent;
			entries[i].udp.ssh.sent += src.udp.ssh.sent;
			entries[i].udp.tftp.sent += src.udp.tftp.sent;
			entries[i].udp.other.sent += src.udp.other.sent;
		}
	}
	else
	{
		NetData_Add(&src);
	}

	if (IsMacListed(dst.mac, &mac_pos))
	{
		bool bc = IsMacBC(dst.mac);

		for (uint16_t i = 0; i < entryCnt; ++i)
		{
			if (!bc && i != mac_pos)
				continue;

			entries[i].arp.received += dst.arp.received;
			entries[i].icmp.received += dst.icmp.received;
			entries[i].igmp.received += dst.igmp.received;
			entries[i].other.received += dst.other.received;
			entries[i].tcp.http.received += dst.tcp.http.received;
			entries[i].tcp.https.received += dst.tcp.https.received;
			entries[i].tcp.imap.received += dst.tcp.imap.received;
			entries[i].tcp.smtp.received += dst.tcp.smtp.received;
			entries[i].tcp.ssh.received += dst.tcp.ssh.received;
			entries[i].tcp.other.received += dst.tcp.other.received;
			entries[i].udp.dhcp_c.received += dst.udp.dhcp_c.received;
			entries[i].udp.dhcp_s.received += dst.udp.dhcp_s.received;
			entries[i].udp.imap.received += dst.udp.imap.received;
			entries[i].udp.ssh.received += dst.udp.ssh.received;
			entries[i].udp.tftp.received += dst.udp.tftp.received;
			entries[i].udp.other.received += dst.udp.other.received;
		}
	}
	else
	{
		NetData_Add(&dst);
	}
}

void FrameDecoder::NetData_StructInit(NetData * const data)
{
	if (!data)
		return;

	// MAC
	for (uint8_t i = 0; i < 6; ++i)
		data->mac[i] = 0;

	// IP
	for (uint8_t i = 0; i < 4; ++i)
		data->ip[i] = 0;

	// ARP
	data->arp.sent = 0;
	data->arp.received = 0;

	// ICMP
	data->icmp.sent = 0;
	data->icmp.received = 0;

	// IGMP
	data->igmp.sent = 0;
	data->igmp.received = 0;

	// Other packet types
	data->other.sent = 0;
	data->other.received = 0;

	// TCP
	data->tcp.http.sent = 0;
	data->tcp.http.received = 0;
	data->tcp.https.sent = 0;
	data->tcp.https.received = 0;
	data->tcp.imap.sent = 0;
	data->tcp.imap.received = 0;
	data->tcp.smtp.sent = 0;
	data->tcp.smtp.received = 0;
	data->tcp.ssh.sent = 0;
	data->tcp.ssh.received = 0;
	data->tcp.other.sent = 0;
	data->tcp.other.received = 0;

	// UDP
	data->udp.dhcp_c.sent = 0;
	data->udp.dhcp_c.received = 0;
	data->udp.dhcp_s.sent = 0;
	data->udp.dhcp_s.received = 0;
	data->udp.imap.sent = 0;
	data->udp.imap.received = 0;
	data->udp.ssh.sent = 0;
	data->udp.ssh.received = 0;
	data->udp.tftp.sent = 0;
	data->udp.tftp.received = 0;
	data->udp.other.sent = 0;
	data->udp.other.received = 0;

}

void FrameDecoder::NetData_Add(NetData const * const data)
{
	if (!data || entryCnt >= MAX_ENTRIES - 1)
		return;

	uint16_t mac_pos = 0;

	if (!IsMacListed(data->mac, &mac_pos))
	{
		for (uint8_t i = 0; i < 6; ++i)
			entries[entryCnt].mac[i] = data->mac[i];

		for (uint8_t i = 0; i < 4; ++i)
			entries[entryCnt].ip[i] = data->ip[i];

		// ARP
		entries[entryCnt].arp.received = data->arp.received;
		entries[entryCnt].arp.sent = data->arp.sent;

		// ICMP
		entries[entryCnt].icmp.received = data->icmp.received;
		entries[entryCnt].icmp.sent = data->icmp.sent;

		// IGMP
		entries[entryCnt].igmp.received = data->igmp.received;
		entries[entryCnt].igmp.sent = data->igmp.sent;

		// Other packet types
		entries[entryCnt].other.received = data->other.received;
		entries[entryCnt].other.sent = data->other.sent;

		// TCP
		entries[entryCnt].tcp.http.received = data->tcp.http.received;
		entries[entryCnt].tcp.http.sent = data->tcp.http.sent;
		entries[entryCnt].tcp.https.received = data->tcp.https.received;
		entries[entryCnt].tcp.https.sent = data->tcp.https.sent;
		entries[entryCnt].tcp.imap.received = data->tcp.imap.received;
		entries[entryCnt].tcp.imap.sent = data->tcp.imap.sent;
		entries[entryCnt].tcp.smtp.received = data->tcp.smtp.received;
		entries[entryCnt].tcp.smtp.sent = data->tcp.smtp.sent;
		entries[entryCnt].tcp.ssh.received = data->tcp.ssh.received;
		entries[entryCnt].tcp.ssh.sent = data->tcp.ssh.sent;
		entries[entryCnt].tcp.other.received = data->tcp.other.received;
		entries[entryCnt].tcp.other.sent = data->tcp.other.sent;

		// UDP
		entries[entryCnt].udp.dhcp_c.received = data->udp.dhcp_c.received;
		entries[entryCnt].udp.dhcp_c.sent = data->udp.dhcp_c.sent;
		entries[entryCnt].udp.dhcp_s.received = data->udp.dhcp_s.received;
		entries[entryCnt].udp.dhcp_s.sent = data->udp.dhcp_s.sent;
		entries[entryCnt].udp.imap.received = data->udp.imap.received;
		entries[entryCnt].udp.imap.sent = data->udp.imap.sent;
		entries[entryCnt].udp.ssh.received = data->udp.ssh.received;
		entries[entryCnt].udp.ssh.sent = data->udp.ssh.sent;
		entries[entryCnt].udp.tftp.received = data->udp.tftp.received;
		entries[entryCnt].udp.tftp.sent = data->udp.tftp.sent;
		entries[entryCnt].udp.other.received = data->udp.other.received;
		entries[entryCnt].udp.other.sent = data->udp.other.sent;

		entryCnt++;
	}
}

uint16_t FrameDecoder::NetData_GetEntryCount() const
{
	return entryCnt;
}

NetData const * FrameDecoder::NetData_GetAt(uint16_t const pos) const
{
	NetData const * ret = 0;

	if (entryCnt > 0 && pos < entryCnt)
		ret = &(entries[pos]);

	return ret;
}

NetData const * FrameDecoder::NetData_GetAll() const
{
	return &all;
}

// -------------------------------------------------------------------------------------

void FrameDecoder::InitializeOverview()
{
	all.arp.received = 0;
	all.arp.sent = 0;
	all.icmp.received = 0;
	all.icmp.sent = 0;
	all.igmp.received = 0;
	all.igmp.sent = 0;
	all.other.received = 0;
	all.other.sent = 0;

	all.tcp.http.received = 0;
	all.tcp.http.sent = 0;
	all.tcp.https.received = 0;
	all.tcp.https.sent = 0;
	all.tcp.imap.received = 0;
	all.tcp.imap.sent = 0;
	all.tcp.smtp.received = 0;
	all.tcp.smtp.sent = 0;
	all.tcp.ssh.received = 0;
	all.tcp.ssh.sent = 0;
	all.tcp.other.received = 0;
	all.tcp.other.sent = 0;

	all.udp.dhcp_c.received = 0;
	all.udp.dhcp_c.sent = 0;
	all.udp.dhcp_s.received = 0;
	all.udp.dhcp_s.sent = 0;
	all.udp.imap.received = 0;
	all.udp.imap.sent = 0;
	all.udp.tftp.received = 0;
	all.udp.tftp.sent = 0;
	all.udp.ssh.received = 0;
	all.udp.ssh.sent = 0;
	all.udp.other.received = 0;
	all.udp.other.sent = 0;
}

bool FrameDecoder::IsMacListed(uint8_t const * const mac, uint16_t * pos)
{
	for (uint8_t i = 0; i < entryCnt; ++i)
	{
		if (entries[i].mac[0] == mac[0] && entries[i].mac[1] == mac[1]
				&& entries[i].mac[2] == mac[2] && entries[i].mac[3] == mac[3]
				&& entries[i].mac[4] == mac[4] && entries[i].mac[5] == mac[5])
		{
			*pos = i;
			return true;
		}
	}

	return false;
}

bool FrameDecoder::IsMacBC(uint8_t const * const mac)
{
	return (mac[0] == 0xFF && mac[1] == 0xFF && mac[2] == 0xFF && mac[3] == 0xFF
			&& mac[4] == 0xFF && mac[5] == 0xFF);
}
