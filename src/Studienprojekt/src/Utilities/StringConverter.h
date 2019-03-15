/**
 ******************************************************************************
 * \file    StringConverter.h
 * \author  Lucas Degner
 * \version V1.0.0
 * \date    13.03.2019
 * \brief   Definition of string converter functions
 ******************************************************************************
 */

#ifndef UTILITIES_STRINGCONVERTER_H_
#define UTILITIES_STRINGCONVERTER_H_

#include <stdint.h>

/**
 * \brief Convert a MAC address to a string
 * \param mac The MAC address to be converted
 * \param string The to a string converted MAC address
 * \note Both parameter must have the corresponding buffers when called (mac -> 6 byte, string -> >=18 byte)
 */
void MacToString(uint8_t const * const mac, char * string);

/**
 * \brief Convert the lower 4 bit hex to a character (0x0A -> 'A', 0xA0 -> '0')
 * \param hex To be converted hex number
 * \return Converted hex character
 */
char HexToChar(uint8_t const hex);

/**
 * \brief Convert a time given in seconds into a string if desired with prefix
 * \param seconds Time in seconds
 * \param prefix Desired prefix
 * \param String of time in format "prefixh:mm:ss"
 * \note Between prefix and time is no space!
 */
void TimeToString(uint32_t const seconds, char const * prefix, char * str);

#endif /* UTILITIES_STRINGCONVERTER_H_ */
