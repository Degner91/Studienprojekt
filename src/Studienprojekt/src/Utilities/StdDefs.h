
#ifndef __STDDEFS_H
#define __STDDEFS_H

#include <stdint.h>

typedef struct
{
	uint16_t x;
	uint16_t y;
} PositionType;

typedef struct
{
	PositionType pos;
	uint32_t width;
	uint32_t height;
} RectType;

enum
{
	EtherType_IPv4 = 0x0800,
	EtherType_ARP = 0x0806,
	EtherType_WoL = 0x0842,
	EtherType_RARP = 0x8035,
	EtherType_VLAN = 0x8100,
	EtherType_IPv6 = 0x86DD,
	EtherType_HomePlugAV = 0x88E1
};

typedef struct
{
	uint8_t destination_addr[6];
	uint8_t source_addr[6];
	uint16_t type;
	uint8_t * data;
	uint32_t crc;
} EthernetFrame_t;

typedef struct
{
	uint8_t version : 4;
	uint8_t ihl : 4; 		// ip header length
	uint8_t tos; 			// type of service
	uint16_t total_length;
	uint16_t identification;
	uint16_t flags : 3;
	uint16_t fragment_offset : 13;
	uint8_t ttl;			// time to live
	uint8_t protocol;
	uint16_t header_checksum;
	uint8_t source_addr[4];
	uint8_t destination_addr[4];
	uint32_t options;
	uint32_t * data;
} IPv4_Packet_t;

enum
{
	IP_Protocol_ICMP = 1,
	IP_Protocol_IGMP = 2,
	IP_Protocol_TCP = 6,
	IP_Protocol_UDP = 17
};

#endif
