/**
 ******************************************************************************
 * @file    Font.h
 * @author  Julian Grasb�ck
 * @version V1.0.0
 * @date    18.04.2017
 * @brief   Defines the types that are used when drawing characters in the
 *					TftDisplay module. Fonts can be generated by using the "Font Tool"
 * @copyright
 * Copyright (c) FH O� Forschungs und Entwicklungs GmbH, thermocollect
 * You may not use or copy this file except with written permission of the owners.
 ******************************************************************************
 */

/** \defgroup TftFont
 *	\brief Module defining the font type and usage functions
 *  @{
 */
 
#ifndef FONT_H
#define FONT_H

#include "StdDefs.h"

/* Uncomment this define if using TftDisplay_V1 */
/* #define Tft_FontType TftIf_FontType */

/****************************************************************
 * Macros                                                       *
 ***************************************************************/

/**
 * @brief Defines the number of characters
 */
#define FONT_CHAR_CNT	256u

/****************************************************************
 * Type definitions
 ***************************************************************/

/**
 * @brief Type for the graphical reperesentation of a single character
 */
typedef struct
{
	uint32_t width;         /**< The width in pixel */
	const uint32_t* bitmap; /**< The bitmap with 1 bit per pixel */
} Font_GlyphType;

/**
 * @brief Represents a font
 *
 * ISO/IEC 8859-1 is used (see <a href="https://en.wikipedia.org/wiki/ISO/IEC_8859-1">Wikipedia</a> for details)
 */
typedef struct
{
	uint8_t glyphMap[FONT_CHAR_CNT];		/**< Maps the ISO/IEC 8859-1 characters to glyphs array
																				 *	 by saving the corresponding index in the glyps array
																				 *	 for each character */
	uint32_t glyphCount;									/**< Number of glyphs in the font (size of the glyphs array) */
	uint32_t height;       								/**< Height of each glyph in pixels */
	const Font_GlyphType* glyphs;			/**< The array of glyphs */
} FontType;

/****************************************************************
 * User functions
 ***************************************************************/

/**
 * @brief Calculates the width of the given string in pixels
 *
 * @param font The font
 * @param str The string
 * @return The width of the string in pixel
 */
uint32_t Font_GetStrWidth(const FontType* const font, const char* str);

#endif /* FONT_H */

/** @}*/
