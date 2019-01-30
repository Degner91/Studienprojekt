/**
 ******************************************************************************
 * @file    TftDisplay_V2.h
 * @author  Julian Grasböck
 * @version V1.0.0
 * @date    29.03.2017
 * @brief   TFT Display Controller Module (ST7789S controller chip)
 * @copyright
 * Copyright (c) FH OÖ Forschungs und Entwicklungs GmbH, thermocollect
 * You may not use or copy this file except with written permission of the owners.
 ******************************************************************************
 */

/** \defgroup TftDisplay
 *	\brief Tft Display constants, types and usage functions
 *  @{
 */

#ifndef TFTDISPLAY_H
#define TFTDISPLAY_H

#include "Services/StdDef.h"
#include "BSP/DisplayOrientation_Cfg.h"
#include "stm32f0xx.h"
#include "FONTS/TftFont.h"
#include "Rect.h"
#include "Position.h"

/****************************************************************
 * Macros
 ***************************************************************/

/* Defines for some rgb24 colours */
#define TFT_COLOUR_RED					(uint32_t)(0x00FF0000)
#define TFT_COLOUR_DARK_RED			(uint32_t)(0x00CC0000)
#define TFT_COLOUR_GREEN				(uint32_t)(0x0000FF00)
#define TFT_COLOUR_DARK_GREEN		(uint32_t)(0x0000CC00)
#define TFT_COLOUR_BLUE					(uint32_t)(0x000000FF)
#define TFT_COLOUR_BLACK				(uint32_t)(0x00000000)
#define TFT_COLOUR_GREY					(uint32_t)(0x00C0C0C0)
#define TFT_COLOUR_DARK_GREY		(uint32_t)(0x00808080)
#define TFT_COLOUR_WHITE  			(uint32_t)(0x00FFFFFF)
#define TFT_COLOUR_YELLOW 			(uint32_t)(0x00FFFF00)
#define TFT_COLOUR_DARK_YELLOW	(uint32_t)(0x00CCCC00)

/* Defines for the width and height depending on the orientation */
#if (DISPLAY_ORIENTATION_SWAP_XY == FALSE)
	#define TFT_WIDTH		240u
	#define TFT_HEIGHT	320u
#else
	#define TFT_WIDTH		320u
	#define TFT_HEIGHT	240u
#endif

/****************************************************************
 * Type definitions
 ***************************************************************/

/**
 * @brief Enum that defines the positions of the colours in the colour array
 */
typedef enum
{
	Tft_ColourIdx_Background = 0, /**< Index of the background colour */
	Tft_ColourIdx_Foreground,     /**< Index of the foreground colour */
	Tft_ColourIdx_Count						/**< Num of colours */
} Tft_ColourIdx;

/**
 * @brief Structure to initialize the module
 */
typedef struct
{
	uint16_t colours[Tft_ColourIdx_Count];	/**< Background and Foreground Colours */
	const TftFontType* font;								/**< Font to be used when writing chars */
} Tft_ConfigType;

/****************************************************************
 * Global variables
 ***************************************************************/

/**
 * @brief External declaration of the module initialization struct so that
 *				the user doesn't have to include the config module
 */
extern Tft_ConfigType Tft_config;


/****************************************************************
 * User functions
 ***************************************************************/

/** 
 * @brief Initializes the TftDisplay Module
 * @param config: Configuration off the module
 * @retval TRUE if the function succeeded else FALSE
 */
BOOL Tft_Init(Tft_ConfigType* const config);

/** 
 * @brief Performs a HW Reset
 *				All Registers will get their HW default values
 * @retval TRUE if the function succeeded else FALSE
 *
 * ATTENTION: Call Tft_Init afterwards !!!
 */
BOOL Tft_Reset(void);

/**
 * @brief Set foreground colour
 * @param colour Colour value in rgb 24 bit format
 *
 * Colour coding:
 *		31..24 = Empty (not used)
 *		23..16 = Red
 *		15..8  = Green
 *		 7..0  = Blue
 */
void Tft_SetForegroundColourRgb24(const uint32_t colour);

/**
 * @brief Set background colour
 * @param colour Colour value in rgb 24 bit format
 */
void Tft_SetBackgroundColourRgb24(const uint32_t colour);

/**
 * @brief Set foreground colour
 * @param colour Colour value in rgb 16 bit format
 *
 * Colour coding:
 *		15..11 = Red
 *		10..5  = Green
 *		 4..0  = Blue
 */
void Tft_SetForegroundColourRgb16(const uint16_t colour);

/**
 * @brief Set background colour
 * @param colour Colour value in rgb 16 bit format
 */
void Tft_SetBackgroundColourRgb16(const uint16_t colour);

/**
 * @brief Clear screen (with active background colour)
 * @retval TRUE if the function succeeded else FALSE
 */
BOOL Tft_ClearScreen(void);

/**
 * @brief Set active font
 * @param font Pointer to font structure
 * @retval TRUE if the function succeeded else FALSE
 */
BOOL Tft_SetFont(const TftFontType* const font);

/**
 * @brief Draw pixel (in active foreground colour)
 * @param pos Position where to draw the pixel
 *						(x = 0 left corner; y = 0 upper corner)
 * @retval TRUE if the function succeeded else FALSE
 */
BOOL Tft_DrawPixel(const PositionType* const pos);

/**
 * @brief Draw horizontal line (in active foreground colour)
 * @param pos Position where to start the line
 *						(x = 0 left corner; y = 0 upper corner)
 * @param length Line length in pixels
 * @retval TRUE if the function succeeded else FALSE
 */
BOOL Tft_DrawHLine(const PositionType* const pos, const uint16_t length);

/**
 * @brief Draw vertical line (in active foreground colour)
 * @param pos Position where to start the line
 *						(x = 0 left corner; y = 0 upper corner)
 * @param length Line length in pixels
 * @retval TRUE if the function succeeded else FALSE
 */
BOOL Tft_DrawVLine(const PositionType* const pos, const uint16_t length);

/**
 * @brief Draw rectangle (in active foreground colour)
 * @param rect Rectangle that should be drawn, where position defines
 *						 the upper left corner from where to start drawing
 * @retval TRUE if the function succeeded else FALSE
 */
BOOL Tft_DrawRectangle(const RectType* const rect);

/**
 * @brief Draw filled rectangle (in active foreground colour)
 * @param rect Rectangle that should be drawn, where position defines
 *						 the upper left corner
 * @retval TRUE if the function succeeded else FALSE
 */
BOOL Tft_DrawFilledRectangle(const RectType* const rect);

/**
 * @brief Draw bargraph (in active foreground colour)
 * @param rect Rectangle that represents the full area of the bargraph
 *						 where position defines the upper left corner
 *						 from where the foreground region drawing starts
 * @param val Active bargraph value (maximum value is 100)
 * @retval TRUE if the function succeeded else FALSE
 */
BOOL Tft_DrawBargraph(const RectType* const rect, const uint8_t val);

/**
 * @brief Draw character (in active foreground colour)
 * @param pos Position where to start the line
 *						(x = 0 left corner; y = 0 upper corner)
 * @param ch Character
 * @retval TRUE if the function succeeded else FALSE
 */
BOOL Tft_DrawChar(const PositionType* const pos, const char ch);

/**
 * @brief Draw string (in active foreground colour)
 * @param pos Position where to start the line
 *						(x = 0 left corner; y = 0 upper corner)
 * @param str Null-terminated String
 * @retval TRUE if the function succeeded else FALSE
 */
BOOL Tft_DrawString(const PositionType* const pos, const char* str);

/**
 * @brief Draws a image with 1 bit per pixel (foreground- and backgroundcolour)
 * @param rect Rectangle defining the geometrics of the image where position defines
 *						 the upper left corner from where to start drawing
 * @param data Bitmap data
 * @param colours Array containing the two colours of the image
 * @retval TRUE if the function succeeded else FALSE
 */
BOOL Tft_DrawImage1bpp(const RectType* const rect, const uint32_t* const data,
											 const uint16_t* const colours);

/**
 * @brief Draws a image with 8 bits per pixel
 *
 * The values in the data array are used as index for the given color array
 * Each value in the colourMap represents one pixel
 *
 * @param rect Rectangle defining the geometrics of the image where position defines
 *						 the upper left corner from where to start drawing
 * @param data Bitmap data
 * @param colours Array containing all colours of the image
 * @retval TRUE if the function succeeded else FALSE
 */
BOOL Tft_DrawImage8bpp(const RectType* const rect, const uint8_t* const data,
											 const uint16_t* const colours);

/**
 * @brief Draws a image with 16 bits per pixel
 *
 * @param rect Rectangle defining the geometrics of the image where position defines
 *						 the upper left corner from where to start drawing
 * @param data Bitmap data
 * @retval TRUE if the function succeeded else FALSE
 */
BOOL Tft_DrawImage16bpp(const RectType* const rect, const uint16_t* const data);

/****************************************************************
 * Internal functions/callbacks
 ***************************************************************/

#endif

/** @}*/
