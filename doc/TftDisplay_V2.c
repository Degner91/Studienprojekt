/**
 ******************************************************************************
 * @file    TftDisplay_V2.c
 * @author  Julian Grasböck
 * @version V1.0.0
 * @date    29.03.2017
 * @brief   TFT Display Controller Module (ST7789S controller chip)
 * @copyright
 * Copyright (c) FH OÖ Forschungs und Entwicklungs GmbH, thermocollect
 * You may not use or copy this file except with written permission of the owners.
 ******************************************************************************
 */

#include "TftDisplay_V2.h"
#include "Services/Stopwatch.h"
#include <assert.h>

/****************************************************************
 * Macros
 ***************************************************************/
 
/****************************************************************
 * Type definitions
 ***************************************************************/

/*
 * Defines the commands for the display
 * See TSC2046E ref. manual
 */
typedef enum
{
	Tft_Cmd_NOP = 0x00,       /* No Operation */
	Tft_Cmd_RDDID = 0x04,     /* Read display ID */
	Tft_Cmd_RDDST = 0x09,     /* Read display status */
	Tft_Cmd_RDDPM = 0x0A,     /* Read display power mode */
	Tft_Cmd_RDDMADCTL = 0x0B, /* Read display MADCTL */
	Tft_Cmd_RDDCOLMOD = 0x0C, /* Read display pixel format */
	Tft_Cmd_RDDIM = 0x0D,     /* Read display image mode */
	Tft_Cmd_RDDSM = 0x0E,     /* Read display signal mode */
	Tft_Cmd_RDDSDR = 0x0F,    /* Read display self-diagnostic result*/
	Tft_Cmd_SLPIN = 0x10,     /* Sleep in (It will be necessary to wait
														 *	5msec before sending any new commands
														 *	to the display module after this command) */
	Tft_Cmd_SLPOUT = 0x11,    /* Sleep out (It will be necessary to wait
														 *	 5msec before sending any new commands
														 *	 to the display module after this command)
														 *	 (It will be necessary to wait 120msec
														 *	 after sending sleep out command
														 *	 (when in sleep in mode) before sending an
														 *	 sleep in command. */
	Tft_Cmd_PTLON = 0x12,     /* Partial display mode on */
	Tft_Cmd_NORON = 0x13,     /* Normal display mode on */
	Tft_Cmd_INVOFF = 0x20,    /* Display inversion off */
	Tft_Cmd_INVON = 0x21,     /* Display inversion on */
	Tft_Cmd_GAMSET = 0x26,    /* Gamma set */
	Tft_Cmd_DISPOFF = 0x28,   /* Display off */
	Tft_Cmd_DISPON = 0x29,    /* Display on */
	Tft_Cmd_CASET = 0x2A,     /* Column adress set */
	Tft_Cmd_RASET = 0x2B,     /* Row adress set */
	Tft_Cmd_RAMWR = 0x2C,     /* Memory write */
	Tft_Cmd_RAMRD = 0x2E,     /* Memory read */
	Tft_Cmd_PTLAR = 0x30,     /* Partial area */
	Tft_Cmd_VSCRDEF = 0x33,   /* Vertical scrolling definition */
	Tft_Cmd_MADCTL = 0x36,    /* Memory data access control */
	Tft_Cmd_VSCSAD = 0x37,    /* Vertical scroll start adress of RAM */
	Tft_Cmd_IDMOFF = 0x38,    /* Idle mode off */
	Tft_Cmd_IDMON = 0x39,     /* Idle mode on */
	Tft_Cmd_COLMOD = 0x3A,		/* Interface pixel format */
	Tft_Cmd_WRMEMC = 0x3C,    /* Write memory continue */
	Tft_Cmd_RDMEMC = 0x3E,    /* Read memory continue */
	Tft_Cmd_WRDISBV = 0x51,   /* Write display brightness */
	Tft_Cmd_RDDISBV = 0x52,   /* Read display brightness value */
	Tft_Cmd_WRCTRLD = 0x53,   /* Write CTRL display */
	Tft_Cmd_RDCTRLD = 0x54,   /* Read CTRL value display */
	Tft_Cmd_WRCACE = 0x55,    /* Write content adaptive brightness control and color enhancement */
	Tft_Cmd_RDCABC = 0x56,    /* Read content adaptive brightness control */
	Tft_Cmd_WRCABCMB = 0x5E,  /* Write CABC minimum brightness */
	Tft_Cmd_RDCABCMB = 0x5F,  /* Read CABC minimum brightness */
	Tft_Cmd_RDID1 = 0xDA,     /* Read ID1 */
	Tft_Cmd_RDID2 = 0xDB,     /* Read ID2 */
	Tft_Cmd_RDID3 = 0xDC,     /* Read ID3 */
	Tft_Cmd_RAMCTRL = 0xB0,		/* RAM control */
	Tft_Cmd_FRCTRL1 = 0xB3,   /* Frame rate control 1 (In partial mode/ idle colors) */
	Tft_Cmd_DGMEN = 0xBA,     /* Digital gamma enable */
	Tft_Cmd_LCMCTRL = 0xC0,   /* LCM control */
	Tft_Cmd_IDSET = 0xC1,     /* ID code setting */
	Tft_Cmd_FRCTRL2 = 0xC6,   /* Frame control in normal mode */
	Tft_Cmd_CABCCTRL = 0xC7,  /* CABC control */
	Tft_Cmd_PVGAMCTRL = 0xE0, /* Positive voltage gamma control */
	Tft_Cmd_NVGAMCTRL = 0xE1, /* Negative voltage gamma control */
	Tft_Cmd_DGMLUTR = 0xE2,   /* Digital gamma look-up table for red */
	Tft_Cmd_DGMLUTB = 0xE3,   /* Digital gamma look-up table for blue */
} Tft_CmdType;

/****************************************************************
 * Constants
 ***************************************************************/

/* Constants for the pin placement */
/* Current setup -> APUS V1.1 */
static const uint16_t Tft_nCS = GPIO_Pin_8;
static const uint16_t Tft_nWR = GPIO_Pin_10;
static const uint16_t Tft_nRD = GPIO_Pin_11;
static const uint16_t Tft_DC = GPIO_Pin_9;
static const uint16_t Tft_nRES = GPIO_Pin_10;

/* Interface port */
static GPIO_TypeDef * const Tft_Port = GPIOE;
static GPIO_TypeDef * const Tft_ResPort = GPIOF;

/* Helper constants */
static const uint8_t Tft_Shift1Byte = 8;
static const uint8_t Tft_ShiftHalfWord = 16;
static const uint8_t Tft_PixelHeight = 1;
static const uint8_t Tft_PixelWidth = 1;

/* Parameter values used to init controller */
#if DISPLAY_ORIENTATION_SWAP_XY == FALSE
	static const uint8_t Tft_MirrorX_Value = 0x40;
	static const uint8_t Tft_MirrorY_Value = 0x80;
#else
	static const uint8_t Tft_MirrorX_Value = 0x80;
	static const uint8_t Tft_MirrorY_Value = 0x40;
#endif
static const uint8_t Tft_SwapXY_Value = 0x20;
static const uint8_t Tft_SelColMode16bpp = 0x05;


/* Timing constraints */
static const Stopwatch_ValueType Tft_TimeTRW = 1; /* See (RefManual page 46) */
static const Stopwatch_ValueType Tft_TimeTRT = 120; /* See (RefManual page 46) */
static const Stopwatch_ValueType Tft_TimeSleepOut = 5; /* See (RefManual page 177, -> restriction) */

/****************************************************************
 * Function declarations
 ***************************************************************/

static void Tft_WriteData(const uint8_t data);
static void Tft_WriteCmd(const Tft_CmdType command);
static void Tft_WritePixel(const uint16_t rgbPixelValue);
static void Tft_WritePixels(const uint16_t rgbPixelValue, const	uint32_t num);
static void Tft_SetWindow(const RectType* const rect);
static uint32_t Tft_ToBSRRValue(const uint8_t data);
static uint16_t Tft_To16bpp(const uint32_t rgbPixelValue);
static void Tft_DrawFilledArea(const RectType* const rect, const uint16_t colour);

/****************************************************************
 * Global variables
 ***************************************************************/

static Tft_ConfigType* Tft_userCfg = NULL_PTR;

/****************************************************************
 * User functions
 ***************************************************************/

/*
 * Function that initializes the module and the display
 */
BOOL Tft_Init(Tft_ConfigType* const config)
{
	uint8_t Tft_OrientInitVal = 0;
	Stopwatch_ValueType refTime = 0;
	
	/* Check if module is uninitialized and pointer is valid */
  if ((config != NULL_PTR) && (Tft_userCfg == NULL_PTR))
  {
		/* Init module intern user config pointer */
    Tft_userCfg = config;

		/* Set read and write inactive */
		Tft_Port->BSRR = Tft_nRD | Tft_nWR;
		/* Set chip enabled */
		/* Chip can always stay enabled cause there is no other chip */
		/* on the same bus */
		Tft_Port->BRR = Tft_nCS;
		
		/* Set reset inactive */
		Tft_ResPort->BSRR = Tft_nRES;
		
		/* Using busy waiting cause init function is normaly only called once
		 * and to keep it simple */
		refTime = Stopwatch_GetValue();
		while(Stopwatch_CheckInterval(Tft_TimeTRT, refTime) == FALSE);
		
		/* After S/W reset H/W reset and power on sequence display is in sleep mode */
		/* -> Exit sleep mode */
		Tft_WriteCmd(Tft_Cmd_SLPOUT);
		refTime = Stopwatch_GetValue();
		while(Stopwatch_CheckInterval(Tft_TimeSleepOut, refTime) == FALSE);
	
		if(DISPLAY_ORIENTATION_SWAP_XY == TRUE)
		{
			Tft_OrientInitVal |= Tft_SwapXY_Value;
		}
		if(DISPLAY_ORIENTATION_MIRROR_X == TRUE)
		{
			Tft_OrientInitVal |= Tft_MirrorX_Value;
		}
		if(DISPLAY_ORIENTATION_MIRROR_Y == TRUE)
		{
			Tft_OrientInitVal |= Tft_MirrorY_Value;
		}
		/* Set method of pixel data transfer */
		Tft_WriteCmd(Tft_Cmd_MADCTL);
		/* Init data transfer */
		Tft_Port->BSRR = Tft_DC;
		Tft_WriteData(Tft_OrientInitVal);

		/* Set choosen colour resolution */
		Tft_WriteCmd(Tft_Cmd_COLMOD);
		/* Init data transfer */
		Tft_Port->BSRR = Tft_DC;
		Tft_WriteData(Tft_SelColMode16bpp);
		
		/* Enable display */
		Tft_WriteCmd(Tft_Cmd_DISPON);

		return TRUE;
	}
	return FALSE;
}

/*
 * Function to perform a hardware reset
 */
BOOL Tft_Reset(void)
{
	/* Check initialization */
	if(Tft_userCfg != NULL_PTR)
	{
		/* Set reset active */
		Tft_ResPort->BRR = Tft_nRES;
		/* Reset user config so that following init will work */
		Tft_userCfg = NULL_PTR;
		/* wait for at least 10 us */
		Stopwatch_ValueType refTime = Stopwatch_GetValue();
		while(Stopwatch_CheckInterval(Tft_TimeTRW, refTime) == FALSE);
		
		return TRUE;
	}
	return FALSE;
}

/*
 * Sets the given colour as the current foreground colour
 */
void Tft_SetForegroundColourRgb24(const uint32_t colour)
{
	/* Check initialization */
	if(Tft_userCfg != NULL_PTR)
	{
		Tft_userCfg->colours[Tft_ColourIdx_Foreground] = Tft_To16bpp(colour);
	}
}

/*
 * Sets the given colour as the current background colour
 */
void Tft_SetBackgroundColourRgb24(const uint32_t colour)
{
	/* Check initialization */
	if(Tft_userCfg != NULL_PTR)
	{
		Tft_userCfg->colours[Tft_ColourIdx_Background] = Tft_To16bpp(colour);
	}
}

/*
 * Sets the given colour as the current foreground colour
 */
void Tft_SetForegroundColourRgb16(const uint16_t colour)
{
	/* Check initialization */
	if(Tft_userCfg != NULL_PTR)
	{
		Tft_userCfg->colours[Tft_ColourIdx_Foreground] = colour;
	}
}

/*
 * Sets the given colour as the current background colour
 */
void Tft_SetBackgroundColourRgb16(const uint16_t colour)
{
	/* Check initialization */
	if(Tft_userCfg != NULL_PTR)
	{
		Tft_userCfg->colours[Tft_ColourIdx_Background] = colour;
	}
}


/*
 * Sets the whole display area to the background colour
 */
BOOL Tft_ClearScreen(void)
{
	/* Check initialization */
	if(Tft_userCfg != NULL_PTR)
	{
		/* Draw whole display in background colour */
		const RectType rect = { { 0, 0 }, TFT_WIDTH, TFT_HEIGHT };
		Tft_DrawFilledArea(&rect, Tft_userCfg->colours[Tft_ColourIdx_Background]);		
		return TRUE;
	}
	return FALSE;
}

/*
 * Sets the given font as active font
 */
BOOL Tft_SetFont(const TftFontType* const font)
{
	/* Check initialization and given font */
	if((Tft_userCfg != NULL_PTR) &&
		(font != NULL_PTR) &&
		(font->glyphs != NULL_PTR) &&
		(font->height <= TFT_HEIGHT))
	{
		Tft_userCfg->font = font;
		return TRUE;
	}
	return FALSE;
}

/*
 * Draws one pixel at the given position
 */
BOOL Tft_DrawPixel(const PositionType* const pos)
{
	if((Tft_userCfg != NULL_PTR) &&
		(pos != NULL_PTR) &&
		(pos->x < TFT_WIDTH) &&
		(pos->y < TFT_HEIGHT))
	{
		/* Set drawing region to pixel location */
		const RectType rect = { *pos, Tft_PixelWidth, Tft_PixelHeight };
		Tft_SetWindow(&rect);
		/* Send write command */
		Tft_WriteCmd(Tft_Cmd_RAMWR);
		/* Init pixel transfer */
		Tft_Port->BSRR = Tft_DC;
		/* Send pixel */
		Tft_WritePixel(Tft_userCfg->colours[Tft_ColourIdx_Foreground]);
		
		return TRUE;
	}
	return FALSE;
}

/*
 * Draws a horizontal line at the given position with the given length
 */
BOOL Tft_DrawHLine(const PositionType* const pos, const uint16_t length)
{
	if((Tft_userCfg != NULL_PTR) &&
		(pos != NULL_PTR) &&
		((pos->x + length) <= TFT_WIDTH) &&
		(pos->y < TFT_HEIGHT))
	{
		if(length > 0)
		{
			/* Draw 1 pixel high area */
			const RectType rect = { *pos, length, Tft_PixelHeight };
			Tft_DrawFilledArea(&rect, Tft_userCfg->colours[Tft_ColourIdx_Foreground]);
		}
		/* else Nothing to do */
		return TRUE;
	}
	return FALSE;
}

/*
 * Draws a vertical line at the given position with the given length
 */
BOOL Tft_DrawVLine(const PositionType* const pos, const uint16_t length)
{
	if((Tft_userCfg != NULL_PTR) &&
		(pos != NULL_PTR) &&
		((pos->y + length) <= TFT_HEIGHT) &&
		(pos->x < TFT_WIDTH))
	{
		if(length > 0)
		{
			/* Draw 1 pixel wide area */
			const RectType rect = { *pos, Tft_PixelWidth, length };
			Tft_DrawFilledArea(&rect, Tft_userCfg->colours[Tft_ColourIdx_Foreground]);
		}
		/* else Nothing to do */
		return TRUE;
	}
	return FALSE;
}

/*
 * Draws a rectangle beginning from the given position with the given
 * geometrics
 */
BOOL Tft_DrawRectangle(const RectType* const rect)
{
	if((Tft_userCfg != NULL_PTR) &&
		(rect != NULL_PTR) &&
		((rect->pos.x + rect->width) <= TFT_WIDTH) &&
		((rect->pos.y + rect->height) <= TFT_HEIGHT))
	{
		if((rect->height > 0) && (rect->width > 0))
		{
			/* Draw HLines */
			RectType tmpRect = (*rect);
			tmpRect.height = Tft_PixelHeight;
			Tft_DrawFilledArea(&tmpRect, Tft_userCfg->colours[Tft_ColourIdx_Foreground]);
			tmpRect.pos.y += rect->height - 1;
			Tft_DrawFilledArea(&tmpRect, Tft_userCfg->colours[Tft_ColourIdx_Foreground]);
			
			/* Draw VLines */
			tmpRect = (*rect);
			tmpRect.width = Tft_PixelWidth;
			Tft_DrawFilledArea(&tmpRect, Tft_userCfg->colours[Tft_ColourIdx_Foreground]);
			tmpRect.pos.x += rect->width - 1;
			Tft_DrawFilledArea(&tmpRect, Tft_userCfg->colours[Tft_ColourIdx_Foreground]);
		}
		/* else Nothing to do */
		return TRUE;
	}
	return FALSE;
}

/*
 * Draws a rectangle beginning from the given position with the given
 * geometrics filled with the foreground colour
 */
BOOL Tft_DrawFilledRectangle(const RectType* const rect)
{
	if((Tft_userCfg != NULL_PTR) &&
		(rect != NULL_PTR) &&
		((rect->pos.x + rect->width) <= TFT_WIDTH) &&
		((rect->pos.y + rect->height) <= TFT_HEIGHT))
	{
		if((rect->height > 0) && (rect->width > 0))
		{
			Tft_DrawFilledArea(rect, Tft_userCfg->colours[Tft_ColourIdx_Foreground]);
		}
		/* else Nothing to do */
		return TRUE;
	}
	return FALSE;
}

/*
 * Draws a bargraph with the given geometrics
 * val percent of the bargraph will be printed in foureground
 * and the rest in background colour
 */
BOOL Tft_DrawBargraph(const RectType* const rect, const uint8_t val)
{
	static const uint8_t maxVal = 100;
	
	if((Tft_userCfg != NULL_PTR) &&
		(rect != NULL_PTR) &&
		((rect->pos.x + rect->width) <= TFT_WIDTH) &&
		((rect->pos.y + rect->height) <= TFT_HEIGHT) &&
		(val <= maxVal))
	{
		if(rect->width > 0)
		{
			/* Calc height of foreground and background area */
			const uint16_t foreground_height = (val * rect->height) / maxVal;
			const uint16_t background_height = rect->height - foreground_height;
			RectType tmpRect = (*rect);
			
			if(foreground_height > 0)
			{
				/* Draw foreground area */
				tmpRect.height = foreground_height;
				Tft_DrawFilledArea(&tmpRect, Tft_userCfg->colours[Tft_ColourIdx_Foreground]);
			}
			if(background_height > 0)
			{
				/* Draw background area */
				tmpRect.height = background_height;
				tmpRect.pos.y += foreground_height;
				Tft_DrawFilledArea(&tmpRect, Tft_userCfg->colours[Tft_ColourIdx_Background]);
			}
		}
		/* else Nothing to do */
		return TRUE;
	}
	return FALSE;
}

/*
 * Draws the given char at the given position
 */
BOOL Tft_DrawChar(const PositionType* const pos, const char ch)
{
	/* Check initialization */
	if((Tft_userCfg == NULL_PTR) ||
		(Tft_userCfg->font == NULL_PTR) ||
		(Tft_userCfg->font->glyphs == NULL_PTR) ||
		(pos == NULL_PTR))
	{
		return FALSE;
	}

	const TftFontType* const font = Tft_userCfg->font;
	const TftFont_GlyphType* const glyph =
		&font->glyphs[font->glyphMap[(uint8_t)ch]];

	/* Check boundaries */
	if (((pos->x + glyph->width) > TFT_WIDTH) ||
			((pos->y + font->height) > TFT_HEIGHT))
	{
		return FALSE;
	}

	/* Check if bitmap available and if not draw background colour rectangle */
	if (glyph->bitmap == NULL_PTR)
	{
		/* Draw only background colour */
		const RectType tmpRect = { *pos, glyph->width, font->height };
		Tft_DrawFilledArea(&tmpRect, Tft_userCfg->colours[Tft_ColourIdx_Background]);
	}
	else
	{
		/* Draw the chars bitmap */
		const RectType tmpRect = { *pos, glyph->width, font->height };
		Tft_DrawImage1bpp(&tmpRect, glyph->bitmap, Tft_userCfg->colours);
	}
	return TRUE;
}


/*
 * Prints the given string in foreground colour
 */
BOOL Tft_DrawString(const PositionType* const pos, const char* str)
{
	static const char strEnd = '\0';
	static const char endl = '\n';
	
	/* Check user config and given string ptr */
	if((Tft_userCfg == NULL_PTR) ||
		(Tft_userCfg->font == NULL_PTR) ||
		(pos == NULL_PTR) ||
		(str == NULL_PTR))
	{
		return FALSE;
	}

	char currCh = 0;
	PositionType currPos = *pos;
	const TftFontType* const font = Tft_userCfg->font;
	
	/* Draw char after char till terminating 0 is found */
	while((currCh = *str++) != strEnd)
	{
		/* Check if line break intended */
		if(currCh == endl)
		{
			/* Increment y position and set x back to initial */
			currPos.y += font->height;
			currPos.x = pos->x;
		}
		/* Draw current char */
		else if(Tft_DrawChar(&currPos, currCh) == TRUE)
		{
			/* Increment x value */
			currPos.x += font->glyphs[font->glyphMap[(uint8_t)currCh]].width;
		}
		else
		{
			return FALSE;
		}
	}
	return TRUE;
}

/*
 * Draws the given Bitmap with the given colours
 */
BOOL Tft_DrawImage1bpp(const RectType* const rect, const uint32_t* const data,
	const uint16_t* const colours)
{
	if((Tft_userCfg == NULL_PTR) ||
		(rect == NULL_PTR) ||
		(data == NULL_PTR)  ||
		((rect->pos.x + rect->width) > TFT_WIDTH) ||
		((rect->pos.y + rect->height) > TFT_HEIGHT))
	{
		return FALSE;
	}
	else if((rect->height == 0) || (rect->width == 0))
	{
		return TRUE;
	}
	
	/* Set window */
	Tft_SetWindow(rect);
	/* Send write command */
	Tft_WriteCmd(Tft_Cmd_RAMWR);
	/* Init pixel transfer */
	Tft_Port->BSRR = Tft_DC;
	
	uint32_t currBitMask = 0;
	uint32_t currVal = 0;

	for (uint32_t i = 0; i < (rect->width * rect->height); i++)
	{
		/* limits i range from 0 to 31 */
		currBitMask = 1u << (i & 0x1Fu);
		currVal = data[i >> 5u];
		
		/* Check if current pixel should be drawn in foreground colour */
		if((currVal & currBitMask) == currBitMask)
		{
			/* If bit is set draw pixel */
			Tft_WritePixel(colours[Tft_ColourIdx_Foreground]);
		}
		else
		{
			/* Else draw pixel in bakground colour */
			Tft_WritePixel(colours[Tft_ColourIdx_Background]);
		}
	}
	return TRUE;
}

/*
 * Draws the given Bitmap with the given colours
 */
BOOL Tft_DrawImage8bpp(const RectType* const rect, const uint8_t* data, const uint16_t* colours)
{
	if((Tft_userCfg == NULL_PTR) ||
		(rect == NULL_PTR) ||
		(data == NULL_PTR)  ||
		(colours == NULL_PTR) ||
		((rect->pos.x + rect->width) > TFT_WIDTH) ||
		((rect->pos.y + rect->height) > TFT_HEIGHT))
	{
		return FALSE;
	}
	else if((rect->height == 0) || (rect->width == 0))
	{
		return TRUE;
	}
	
	/* Set window */
	Tft_SetWindow(rect);
	/* Send write command */
	Tft_WriteCmd(Tft_Cmd_RAMWR);
	/* Init pixel transfer */
	Tft_Port->BSRR = Tft_DC;
	
	for (uint32_t i = 0; i < (rect->height * rect->width); i++)
	{
		Tft_WritePixel(colours[data[i]]);
	}
	return TRUE;
}

/*
 * Draws the given Bitmap with the given colours
 */
BOOL Tft_DrawImage16bpp(const RectType* const rect, const uint16_t* data)
{
	if((Tft_userCfg == NULL_PTR) ||
		(rect == NULL_PTR) ||
		(data == NULL_PTR)  ||
		((rect->pos.x + rect->width) > TFT_WIDTH) ||
		((rect->pos.y + rect->height) > TFT_HEIGHT))
	{
		return FALSE;
	}
	else if((rect->height == 0) || (rect->width == 0))
	{
		return TRUE;
	}
	
	/* Set window */
	Tft_SetWindow(rect);
	/* Send write command */
	Tft_WriteCmd(Tft_Cmd_RAMWR);
	/* Init pixel transfer */
	Tft_Port->BSRR = Tft_DC;

	for (uint32_t i = 0; i < (rect->height * rect->width); i++)
	{
		Tft_WritePixel(data[i]);
	}
	
	return TRUE;
}


/****************************************************************
 * Static functions
 ***************************************************************/

/*
 * Draws the given rectangle in the given colour
 */
static void Tft_DrawFilledArea(const RectType* const rect, const uint16_t colour)
{
	assert(Tft_userCfg != NULL_PTR);
	assert(rect != NULL_PTR);
	assert(rect->width > 0);
	assert(rect->height > 0);
	assert((rect->pos.x + rect->width) <= TFT_WIDTH);
	assert((rect->pos.y + rect->height) <= TFT_HEIGHT);
	
	/* Set drawing region and draw in the given colour */
	Tft_SetWindow(rect);
	/* Draw the arrea with the given colour */
	Tft_WritePixels(colour, rect->width * rect->height);
}

/*
 * Sets the drawing region of the display
 */
static void Tft_SetWindow(const RectType* const rect)
{
	assert(Tft_userCfg != NULL_PTR);
	assert(rect != NULL_PTR);
	assert(rect->width > 0);
	assert(rect->height > 0);
	assert((rect->pos.x + rect->width) <= TFT_WIDTH);
	assert((rect->pos.y + rect->height) <= TFT_HEIGHT);
	
  const uint16_t xe = rect->pos.x + rect->width - 1;
	const uint16_t ye = rect->pos.y + rect->height - 1;

	/* Set column span */
	Tft_WriteCmd(Tft_Cmd_CASET);
	/* Init data transfer */
	Tft_Port->BSRR = Tft_DC;
	Tft_WriteData((uint8_t)(rect->pos.x >> Tft_Shift1Byte));	/* Column address start MSB */
	Tft_WriteData((uint8_t)rect->pos.x);											/* Column address start LSB */
	Tft_WriteData((uint8_t)(xe >> Tft_Shift1Byte));						/* Column address end MSB */
	Tft_WriteData((uint8_t)xe);																/* Column address end LSB */
	
	/* Set row span */
	Tft_WriteCmd(Tft_Cmd_RASET);
	/* Init data transfer */
	Tft_Port->BSRR = Tft_DC;
	Tft_WriteData((uint8_t)(rect->pos.y >> Tft_Shift1Byte));	/* Row address start MSB */
	Tft_WriteData((uint8_t)rect->pos.y);											/* Row address start LSB */
	Tft_WriteData((uint8_t)(ye >> Tft_Shift1Byte));						/* Row address end MSB */
	Tft_WriteData((uint8_t)ye);																/* Row address end LSB */
}

/*
 * Function to write a user command to the display
 */
static void Tft_WriteCmd(const Tft_CmdType command)
{	
	assert(Tft_userCfg != NULL_PTR);

	/* Init command transfer */
	Tft_Port->BSRR = Tft_DC << Tft_ShiftHalfWord;
	/* Send command */
	Tft_WriteData((uint8_t)command);
}

/*
 * Function to write data to the display
 */
static void Tft_WriteData(uint8_t data)
{
	assert(Tft_userCfg != NULL_PTR);
	
	/* Initiate write cycle and put data on GPIOs */
	Tft_Port->BSRR = Tft_ToBSRRValue(data) | (Tft_nWR << Tft_ShiftHalfWord);
	/* Stop writing sequence */
  Tft_Port->BSRR = Tft_nWR;
}

/*
 * Function to write a single pixel
 */
static void Tft_WritePixel(const uint16_t rgbPixelValue)
{
	assert(Tft_userCfg != NULL_PTR);
	
	/* Write first byte */
	Tft_Port->BSRR = Tft_ToBSRRValue((uint8_t)(rgbPixelValue >> Tft_Shift1Byte)) |
																(Tft_nWR << Tft_ShiftHalfWord);
  Tft_Port->BSRR = Tft_nWR;
	/* Write second byte */
	Tft_Port->BSRR = Tft_ToBSRRValue((uint8_t)rgbPixelValue) |
																(Tft_nWR << Tft_ShiftHalfWord);
  Tft_Port->BSRR = Tft_nWR;
}

/*
 * Function to write num pixels in the given colour
 */
static void Tft_WritePixels(const uint16_t rgbPixelValue, uint32_t num)
{
	/* Check user config */
	assert(Tft_userCfg != NULL_PTR);
	
	/* Send write command */
	Tft_WriteCmd(Tft_Cmd_RAMWR);
	/* Init pixel transfer */
	Tft_Port->BSRR = Tft_DC;
	
	/* Seperate transmit bytes and get the corresponding bsrr value */
	uint32_t bsrrVal1 = Tft_ToBSRRValue((uint8_t)(rgbPixelValue >> Tft_Shift1Byte)) |
		(Tft_nWR << Tft_ShiftHalfWord);
	uint32_t bsrrVal2 = Tft_ToBSRRValue((uint8_t)rgbPixelValue) |
		(Tft_nWR << Tft_ShiftHalfWord);
	
	while((num--) > 0)
	{
		/* Initiate write cycle and put data on GPIOs */
		Tft_Port->BSRR = bsrrVal1;
		/* Stop writing sequence */
		Tft_Port->BSRR = Tft_nWR;
		/* Initiate write cycle and put data on GPIOs */
		Tft_Port->BSRR = bsrrVal2;
		/* Stop writing sequence */
		Tft_Port->BSRR = Tft_nWR;
	}
}

/*
 * Function that converts the colour value to the display 16bpp format (RGB565)
 * Bits 15 to 8 contain the first byte to transmit
 * Bits 7 to 0 contain the second byte to transmit
 */
static uint16_t Tft_To16bpp(const uint32_t rgbPixelValue)
{
	static const uint32_t maskRed = 0x00F80000;
	static const uint32_t maskGreen = 0x0000FC00;
	static const uint32_t maskBlue = 0x000000F8;
	static const uint8_t shiftRed = 8;
	static const uint8_t shiftGreen = 5;
	static const uint8_t shiftBlue = 3;
	
	/* Check user config */
	assert(Tft_userCfg != NULL_PTR);
	
	return ((rgbPixelValue & maskRed) >> shiftRed) |			/* ->R7-R6-R5-R4-R3 */
				 ((rgbPixelValue & maskGreen) >> shiftGreen) |	/* ->G7-G6-G5-G4-G3-G2 */
				 ((rgbPixelValue & maskBlue) >> shiftBlue);			/* ->B7-B6-B5-B4-B3 */
}

/*
 * Function that returns the 32 bit value that sets the given data
 * on the DB pins when written to the BSRR register
 */
static uint32_t Tft_ToBSRRValue(uint8_t data)
{
	/* Check user config */
	assert(Tft_userCfg != NULL_PTR);
	
	/* BSRR => Reset-> P15 | P14 |...| P7 | P6 | P5 | P4 | P3 | P2 | P1 | P0
	 *				 Set->	 P15 | P14 |...| P7 | P6 | P5 | P4 | P3 | P2 | P1 | P0
	 * Therefor bits to be set always have to be in first byte position of lower
	 * halfword and bits to be cleared have to be in first byte position of upper
	 * halfword
	 *
	 * Add '1' values of data to BSRR write value */
	uint32_t bsrrVal = data;
	/* Invert data to get '0' values */
	data = ~data;
	
	/* Add '0' values of data to BSRR write value and return result */	
	return bsrrVal | (data << Tft_ShiftHalfWord);
}
