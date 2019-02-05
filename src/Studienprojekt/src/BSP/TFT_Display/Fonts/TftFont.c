/**
 ******************************************************************************
 * @file    TftFont.c
 * @author  Julian Grasböck
 * @version V1.0.0
 * @date    18.04.2017
 * @brief   Fonts that can be used in combination with the TftDisplay modules
 * @copyright
 * Copyright (c) FH OÖ Forschungs und Entwicklungs GmbH, thermocollect
 * You may not use or copy this file except with written permission of the owners.
 ******************************************************************************
 */

#include "TftFont.h"

/*
 * Sums up the width of all chars in the string
 */
uint32_t TftFont_GetStrWidth(const TftFontType* const font, const char* str)
{
	static const char strEnd = '\0';
	uint32_t width = 0;
	
	if((font != 0) && (str != 0))
	{
		while ((*str) != strEnd)
		{
			width += font->glyphs[font->glyphMap[(uint8_t)*str]].width;
			str++;
		}
	}
	return width;
}
