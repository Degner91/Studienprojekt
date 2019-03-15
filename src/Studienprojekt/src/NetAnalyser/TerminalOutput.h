/**
 ******************************************************************************
 * \file    TerminalOutput.cpp
 * \author  Lucas Degner
 * \version V1.0.0
 * \date    13.03.2019
 * \brief   Definition of terminal output functions
 ******************************************************************************
 */

#ifndef UTILITIES_TERMINALOUTPUT_H_
#define UTILITIES_TERMINALOUTPUT_H_

#include "W5500/wizchip_conf.h"
#include "FrameDecoder.h"

/**
 * \brief Print network configuration to serial interface
 * \param netinfo Variable containing network config
 * \param leasetime In case of DHCP, lease time of IP address
 * \param printTitle If true print title and empty line after network config, else print only network config
 */
void Terminal_PrintNetCfg(wiz_NetInfo const & netinfo, uint32_t const leasetime, bool const printTitle);

/**
 * \brief Print all received MAC addresses to serial interface
 * \param decoder Instance of frame decoder class containing all received MAC addresses
 * \return None
 */
void Terminal_PrintMacList(FrameDecoder const & decoder);

/**
 * \brief Print details to specific MAC address to serial interface
 * \param decoder Instance of frame decoder class containing detailed data
 * \param macIdx Index of MAC address
 * \return None
 */
void Terminal_PrintDetails(FrameDecoder const & decoder, uint8_t const macIdx);

/**
 * \brief Print all received packets (not only from and to 'me') to serial interface
 * \param all NetData containing all read packets
 * \return None
 */
void Terminal_PrintOverview(NetData const * all);


#endif /* UTILITIES_TERMINALOUTPUT_H_ */
