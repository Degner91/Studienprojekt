/**
 ******************************************************************************
 * \file    StringConverter.h
 * \author  Lucas Degner
 * \version V1.0.0
 * \date    13.03.2019
 * \brief   Implementation of string converter functions
 ******************************************************************************
 */

#include "StringConverter.h"
#include <stdio.h>

static uint32_t const SEC_OF_MIN = 60;
static uint32_t const SEC_OF_HR = 3600;
static uint8_t const ASCII_START_0 = 48;
static uint8_t const ASCII_START_A = 65;
static uint8_t const MAC_ELEMS = 6;
static uint8_t const SHIFT_HALF_BYTE = 4;

void MacToString(uint8_t const * const mac, char * string)
{
	// mac has to be 6 elems
	// string has to be at least 18 elems (: and \0)
	if (!mac || !string)
		return;

	uint8_t charIdx = 0;
	char upper = 0;
	char lower = 0;

	for (uint8_t idx = 0; idx < MAC_ELEMS; ++idx)
	{
		lower = HexToChar(mac[idx]);
		upper = HexToChar(mac[idx] >> SHIFT_HALF_BYTE);
		string[charIdx++] = upper;
		string[charIdx++] = lower;
		string[charIdx++] = (idx < MAC_ELEMS - 1 ? ':' : '\0');
	}
}

char HexToChar(uint8_t const hex)
{
	uint8_t c = (hex & 0x0F);
	char ret = 0;

	if (c < 0xA)
		ret = (char) (c + ASCII_START_0); // 0 in ascii is 48
	else
		ret = (char) (c + ASCII_START_A - 0xA); // A = 65 in ascii - 0xA to get to the base

	return ret;
}

void TimeToString(uint32_t const seconds, char const * prefix, char * str)
{
	if (!str || !prefix)
		return;

	uint32_t secs = seconds;
	uint8_t mins = 0;
	uint8_t hrs = 0;

	while (secs >= SEC_OF_HR)
	{
		secs -= SEC_OF_HR;
		hrs++;
	}

	while (secs >= SEC_OF_MIN)
	{
		secs -= SEC_OF_MIN;
		mins++;
	}

	snprintf(str, 20, "%s%d:%02d:%02d", prefix, hrs, mins, (uint8_t) secs);
}
