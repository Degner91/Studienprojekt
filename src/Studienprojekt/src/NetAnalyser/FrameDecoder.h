/**
 ******************************************************************************
 * \file    FrameDecoder.h
 * \author  Lucas Degner
 * \version V1.0.0
 * \date    09.03.2019
 * \brief   Definition of ethernet frame decoder class and functions
 ******************************************************************************
 */

#ifndef FRAMEDECODER_H_
#define FRAMEDECODER_H_

#include <stdint.h>

uint16_t const MAX_ENTRIES = 100; /**< Number of maximum entries in NetData array */

/**
 * \brief Structure to collect number of sent and received packets of specific type
 */
struct SRCount_t
{
	uint16_t sent; /**< Number of sent packets */
	uint16_t received; /**< Number of received packets */
};

/**
 * \brief Structure to collect MAC and IP addresses and packet counts
 */
struct NetData
{
	// addresses
	uint8_t mac[6]; /**< MAC address */
	uint8_t ip[4]; /**< IP address */

	// packet counter
	SRCount_t arp; /**< ARP packet counter */
	SRCount_t icmp; /**< ICMP packet counter */
	SRCount_t igmp; /**< IGMP packet counter */
	SRCount_t other; /**< Other IP packet counter apart from ICMP, IGMP, TCP and UDP */

	/**
	 * TCP packet counter
	 */
	struct
	{
		SRCount_t http; /**< HTTP packet counter */
		SRCount_t https; /**< HTTPS packet counter */
		SRCount_t imap; /**< IMAP over TCP  packet counter */
		SRCount_t smtp; /**< SMTP packet counter */
		SRCount_t ssh; /**< SSH over TCP packet counter */
		SRCount_t other; /**< Other TCP packet counter */
	} tcp;

	/**
	 * UDP packet counter
	 */
	struct
	{
		SRCount_t imap; /**< IMAP over UDP packet counter */
		SRCount_t dhcp_s; /**< DHCP server packet counter */
		SRCount_t dhcp_c; /**< DHCP client packet counter */
		SRCount_t ssh; /**< SSH over UDP packet counter */
		SRCount_t tftp; /**< TFTP packet counter */
		SRCount_t other; /**< Other UDP packet counter */
	} udp;

};

/**
 * \brief FrameDecoder class for decoding ethernet frames and save collected data
 */
class FrameDecoder
{
public:
	FrameDecoder()
	{
		entryCnt = 0;
		InitializeOverview();
	}

	~FrameDecoder()
	{
	}

	/**
	 * \brief Decode an ethernet frame and save collected data in class
	 * \param buffer Buffer containing ethernet frame
	 * \param length Length of frame
	 */
	void EthFrame_Decode(uint8_t const * const buffer, uint16_t const length);

	/**
	 * \brief Initialize given NetData all zero
	 * \param data To be initialized NetData
	 * \return None
	 */
	void NetData_StructInit(NetData * const data);

	/**
	 * \brief Add NetData manually
	 * \param data NetData to be added manually
	 * \return None
	 */
	void NetData_Add(NetData const * const data);

	/**
	 * \brief Get current number of entries in NetData array
	 * \param None
	 * \return Number of current entries
	 */
	uint16_t NetData_GetEntryCount() const;

	/**
	 * \brief Get NetData at given index
	 * \param pos To be read index
	 * \return NetData at given index or null if index is out of range
	 */
	NetData const * NetData_GetAt(uint16_t const pos) const;

	/**
	 * \brief Get NetData of all packets read
	 * \paaram None
	 * \return NetData containing numbers of all read packets
	 */
	NetData const * NetData_GetAll() const;

private:
	FrameDecoder(FrameDecoder const &);
	FrameDecoder& operator =(FrameDecoder const &);

	/**
	 * \brief Initialize member all to zero
	 * \param None
	 * \return None
	 */
	void InitializeOverview();

	/**
	 * \brief Check if MAC address s already listed
	 * \param mac To be checked MAC address
	 * \param pos Position where MAC address is found (when found, else not changed)
	 * \return true = found, false = not found
	 */
	bool IsMacListed(uint8_t const * const mac, uint16_t * pos);

	/**
	 * \brief Check if MAC address is broadcast address (all Fs)
	 * \param mac To be checked MAC address
	 * \return true if MAC is all Fs, false otherwise
	 */
	bool IsMacBC(uint8_t const * const mac);

	NetData entries[MAX_ENTRIES]; /**< Counters of read packets, specific with addresses */
	NetData all; /**< Counters of all packets */
	uint16_t entryCnt; /**< Current number of entries (different MACs) */
};

#endif /* FRAMEDECODER_H_ */
