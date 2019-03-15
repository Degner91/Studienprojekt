/**
 ******************************************************************************
 * \file    DisplayOutput.h
 * \author  Lucas Degner
 * \version V1.0.0
 * \date    13.03.2019
 * \brief   Definition of display output
 ******************************************************************************
 */

#ifndef UTILITIES_DISPLAYOUTPUT_H_
#define UTILITIES_DISPLAYOUTPUT_H_


#include "W5500/wizchip_conf.h"
#include "FrameDecoder.h"

/**
 * \brief Print menu on display
 * \param idx Marked index of menu entry
 * \param menusize Number of menu entries
 * \return None
 */
void Display_PrintMenu(uint8_t const idx, uint8_t const menusize);

/**
 * \brief Print network configuration on display
 * \param netinfo Variable containing network config
 * \param leasetime In case of DHCP, lease time of IP address
 * \return None
 */
void Display_PrintNetCfg(wiz_NetInfo const & netinfo, uint32_t const leasetime);

/**
 * \brief Print all collected packets (not only from and to 'me') on display
 * \param data Contains all data
 * \return None
 */
void Display_PrintOverview(NetData const * data);

/**
 * \brief Print all received MAC addresses on display
 * \param decoder Instance of frame decoder class containing all received MAC addresses
 * \param idx Index of marked entry
 * \return None
 */
void Display_PrintMacList(FrameDecoder const & decoder, uint8_t const idx);

/**
 * \brief Print details to specific MAC address on display
 * \param decoder Instance of frame decoder class containing detailed data
 * \param macIdx Index of MAC address
 * \param page Page of details (0 = common packets (ARP, ICMP, IGMP, etc.), 1 = TCP packets, 2 = UDP packets)
 * \return None
 */
void Display_PrintDetails(FrameDecoder const & decoder, uint8_t const macIdx, uint8_t const page);


#endif /* UTILITIES_DISPLAYOUTPUT_H_ */
