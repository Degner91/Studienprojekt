/**
 ******************************************************************************
 * \file    TFT_Display.cpp
 * \author  Lucas Degner
 * \version V1.0.0
 * \date    30.01.2019
 * \brief   Implementation of TFT display class and functions
 * \note	Original by FH OÖ Embedded Systems Lab
 ******************************************************************************
 */

#include "TFT_Display.h"
#include "stm32f0xx_rcc.h"
#include "stm32f0xx_gpio.h"
#include "Delay.h"

/* Constants for the pin placement */
/* Current setup -> APUS V1.1 */
static const uint16_t TFT_nCS = GPIO_Pin_8;
static const uint16_t TFT_nWR = GPIO_Pin_10;
static const uint16_t TFT_nRD = GPIO_Pin_11;
static const uint16_t TFT_DC = GPIO_Pin_9;
static const uint16_t TFT_nRES = GPIO_Pin_10;

/* Helper constants */
static const uint8_t TFT_Shift1Byte = 8;
static const uint8_t TFT_ShiftHalfWord = 16;
static const uint8_t TFT_PixelHeight = 1;
static const uint8_t TFT_PixelWidth = 1;
static const uint8_t TFT_SelColMode16bpp = 0x05;


void TFT_Display::Initialize()
{
	GPIO_InitTypeDef gpioTFT;

	GPIO_DeInit(GPIOE);
	GPIO_DeInit(GPIOF);

	RCC_AHBPeriphClockCmd(RCC_AHBENR_GPIOEEN, ENABLE);
	RCC_AHBPeriphClockCmd(RCC_AHBENR_GPIOFEN, ENABLE);

	gpioTFT.GPIO_Mode = GPIO_Mode_OUT;
	gpioTFT.GPIO_OType = GPIO_OType_PP;
	gpioTFT.GPIO_Pin = (GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3 |
	GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7 |
	GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_10 | GPIO_Pin_11);
	gpioTFT.GPIO_Speed = GPIO_Speed_10MHz;

	GPIO_Init(GPIOE, &gpioTFT);

	gpioTFT.GPIO_OType = GPIO_OType_OD;
	gpioTFT.GPIO_Pin = GPIO_Pin_10;

	GPIO_Init(GPIOF, &gpioTFT);

	/* Set read and write inactive */
	GPIOE->BSRR = TFT_nRD | TFT_nWR;
	/* Set chip enabled */
	/* Chip can always stay enabled cause there is no other chip */
	/* on the same bus */
	GPIOE->BRR = TFT_nCS;

	/* Set reset inactive */
	GPIOF->BSRR = TFT_nRES;

	/* Using busy waiting cause init function is normaly only called once
	 * and to keep it simple */
	Delay_ms(120);

	/* After S/W reset H/W reset and power on sequence display is in sleep mode */
	/* -> Exit sleep mode */
	WriteCmd(TFT_Cmd_SLPOUT);
	Delay_ms(5);
	/* Set method of pixel data transfer */
	WriteCmd(TFT_Cmd_MADCTL);
	/* Init data transfer */
	GPIOE->BSRR = TFT_DC;
	WriteData(0);

	/* Set choosen colour resolution */
	WriteCmd(TFT_Cmd_COLMOD);
	/* Init data transfer */
	GPIOE->BSRR = TFT_DC;
	WriteData(TFT_SelColMode16bpp);

	/* Enable display */
	WriteCmd(TFT_Cmd_DISPON);
}

void TFT_Display::SetForegroundColor(uint32_t const color)
{
	foregroundColor = color;
}

void TFT_Display::SetBackgroundColor(uint32_t const color)
{
	backgroundColor = color;
}

void TFT_Display::SetFont(FontType const * const f)
{
	font = f;
}

void TFT_Display::ClearScreen()
{
	RectType const rect = { { 0, 0 }, WIDTH, HEIGHT };
	DrawFilledArea(&rect, To16bpp(backgroundColor));
}

void TFT_Display::DrawPixel(PositionType const * const p)
{
	/* Set drawing region to pixel location */
	RectType const rect = { *p, TFT_PixelWidth, TFT_PixelHeight };
	SetWindow(&rect);
	/* Send write command */
	WriteCmd(TFT_Cmd_RAMWR);
	/* Init pixel transfer */
	GPIOE->BSRR = TFT_DC;
	/* Send pixel */
	WritePixel(foregroundColor);
}

void TFT_Display::DrawLine(PositionType const * const start, PositionType const * const end)
{
	int16_t dx, dy, loopinc, incx, incy, pdx, pdy, ddx, ddy, dsd, dfd, error;
	PositionType act;

	dx = end->x - start->x;
	dy = end->y - start->y;

	incx = (dx > 0) ? 1 : (dx < 0) ? -1 : 0;
	incy = (dy > 0) ? 1 : (dy < 0) ? -1 : 0;

	if (dx < 0)
		dx = -dx;
	if (dy < 0)
		dy = -dy;

	if (dx > dy)
	{
		/* x ist schnelle Richtung */
		pdx = incx;
		pdy = 0; /* pd. ist Parallelschritt */
		ddx = incx;
		ddy = incy; /* dd. ist Diagonalschritt */
		dsd = dy;
		dfd = dx; /* Delta in langsamer Richtung, Delta in schneller Richtung */
	}
	else
	{
		/* y ist schnelle Richtung */
		pdx = 0;
		pdy = incy; /* pd. ist Parallelschritt */
		ddx = incx;
		ddy = incy; /* dd. ist Diagonalschritt */
		dsd = dx;
		dfd = dy; /* Delta in langsamer Richtung, Delta in schneller Richtung */
	}

	act.x = start->x;
	act.y = start->y;
	error = dfd / 2;

	DrawPixel(&act);

	for (loopinc = 0; loopinc < dfd; ++loopinc)
	{
		error -= dsd;

		if (error < 0)
		{
			error += dfd;

			act.x += ddx;
			act.y += ddy;
		}
		else
		{
			act.x += pdx;
			act.y += pdy;
		}

		DrawPixel(&act);
	}
}

void TFT_Display::DrawChar(PositionType const * const p, char const c)
{
	Font_GlyphType const * glyph = &font->glyphs[font->glyphMap[(uint8_t) c]];

	/* Check boundaries */
	if (((p->x + glyph->width) > WIDTH) || ((p->y + font->height) > HEIGHT))
	{
		return;
	}

	/* Check if bitmap available and if not draw background colour rectangle */
	if (glyph->bitmap == 0)
	{
		/* Draw only background colour */
		RectType const tmpRect = { *p, glyph->width, font->height };
		DrawFilledArea(&tmpRect, backgroundColor);
	}
	else
	{
		/* Draw the chars bitmap */
		RectType const tmpRect = { *p, glyph->width, font->height };
		DrawImage1bpp(&tmpRect, glyph->bitmap);
	}
}

void TFT_Display::DrawString(PositionType const * const p, char const * const s)
{
	static char const strEnd = '\0';
	static char const endl = '\n';

	char const * str = s;
	char currCh = 0;
	PositionType currPos = *p;

	/* Draw char after char till terminating 0 is found */
	while ((currCh = *str++) != strEnd)
	{
		/* Check if line break intended */
		if (currCh == endl)
		{
			/* Increment y position and set x back to initial */
			currPos.y += font->height;
			currPos.x = p->x;
		}
		else
		{
			DrawChar(&currPos, currCh);
			currPos.x += font->glyphs[font->glyphMap[(uint8_t)currCh]].width;
		}
	}
}

void TFT_Display::DrawCharInv(PositionType const * const p, char const c)
{
	Font_GlyphType const * glyph = &font->glyphs[font->glyphMap[(uint8_t) c]];

	/* Check boundaries */
	if (((p->x + glyph->width) > WIDTH) || ((p->y + font->height) > HEIGHT))
	{
		return;
	}

	/* Check if bitmap available and if not draw background colour rectangle */
	if (glyph->bitmap == 0)
	{
		/* Draw only background colour */
		RectType const tmpRect = { *p, glyph->width, font->height };
		DrawFilledArea(&tmpRect, foregroundColor);
	}
	else
	{
		/* Draw the chars bitmap */
		RectType const tmpRect = { *p, glyph->width, font->height };
		DrawImage1bppInv(&tmpRect, glyph->bitmap);
	}
}

void TFT_Display::DrawStringInv(PositionType const * const p, char const * const s)
{
	static char const strEnd = '\0';
	static char const endl = '\n';

	char const * str = s;
	char currCh = 0;
	PositionType currPos = *p;

	/* Draw char after char till terminating 0 is found */
	while ((currCh = *str++) != strEnd)
	{
		/* Check if line break intended */
		if (currCh == endl)
		{
			/* Increment y position and set x back to initial */
			currPos.y += font->height;
			currPos.x = p->x;
		}
		else
		{
			DrawCharInv(&currPos, currCh);
			currPos.x += font->glyphs[font->glyphMap[(uint8_t)currCh]].width;
		}
	}
}

void TFT_Display::DrawImage1bpp(RectType const * const rect, uint32_t const * const data)
{
	/* Set window */
	SetWindow(rect);
	/* Send write command */
	WriteCmd(TFT_Cmd_RAMWR);
	/* Init pixel transfer */
	GPIOE->BSRR = TFT_DC;

	uint32_t currBitMask = 0;
	uint32_t currVal = 0;

	for (uint32_t i = 0; i < (rect->width * rect->height); i++)
	{
		/* limits i range from 0 to 31 */
		currBitMask = 1u << (i & 0x1Fu);
		currVal = data[i >> 5u];

		/* Check if current pixel should be drawn in foreground colour */
		if ((currVal & currBitMask) == currBitMask)
		{
			/* If bit is set draw pixel */
			WritePixel(foregroundColor);
		}
		else
		{
			/* Else draw pixel in bakground colour */
			WritePixel(backgroundColor);
		}
	}
}

void TFT_Display::DrawImage1bppInv(RectType const * const rect, uint32_t const * const data)
{
	/* Set window */
	SetWindow(rect);
	/* Send write command */
	WriteCmd(TFT_Cmd_RAMWR);
	/* Init pixel transfer */
	GPIOE->BSRR = TFT_DC;

	uint32_t currBitMask = 0;
	uint32_t currVal = 0;

	for (uint32_t i = 0; i < (rect->width * rect->height); i++)
	{
		/* limits i range from 0 to 31 */
		currBitMask = 1u << (i & 0x1Fu);
		currVal = data[i >> 5u];

		/* Check if current pixel should be drawn in foreground colour */
		if ((currVal & currBitMask) == currBitMask)
		{
			/* If bit is set draw pixel */
			WritePixel(backgroundColor);
		}
		else
		{
			/* Else draw pixel in bakground colour */
			WritePixel(foregroundColor);
		}
	}
}

/************************************************************/
void TFT_Display::WriteData(uint8_t const data)
{
	/* Initiate write cycle and put data on GPIOs */
	GPIOE->BSRR = ToBSRRValue(data) | (TFT_nWR << TFT_ShiftHalfWord);
	/* Stop writing sequence */
	GPIOE->BSRR = TFT_nWR;
}

void TFT_Display::WriteCmd(CmdType const command)
{
	/* Init command transfer */
	GPIOE->BSRR = TFT_DC << TFT_ShiftHalfWord;
	/* Send command */
	WriteData((uint8_t) command);
}

void TFT_Display::WritePixel(uint16_t const rgbPixelValue)
{
	/* Write first byte */
	GPIOE->BSRR = ToBSRRValue((uint8_t) (rgbPixelValue >> TFT_Shift1Byte))
			| (TFT_nWR << TFT_ShiftHalfWord);
	GPIOE->BSRR = TFT_nWR;
	/* Write second byte */
	GPIOE->BSRR = ToBSRRValue((uint8_t) rgbPixelValue)
			| (TFT_nWR << TFT_ShiftHalfWord);
	GPIOE->BSRR = TFT_nWR;
}

void TFT_Display::WritePixels(uint16_t const rgbPixelValue, uint32_t const num)
{
	uint32_t cnt = num;
	/* Send write command */
	WriteCmd(TFT_Cmd_RAMWR);
	/* Init pixel transfer */
	GPIOE->BSRR = TFT_DC;

	/* Seperate transmit bytes and get the corresponding bsrr value */
	uint32_t bsrrVal1 = ToBSRRValue(
			(uint8_t) (rgbPixelValue >> TFT_Shift1Byte))
			| (TFT_nWR << TFT_ShiftHalfWord);
	uint32_t bsrrVal2 = ToBSRRValue((uint8_t) rgbPixelValue)
			| (TFT_nWR << TFT_ShiftHalfWord);

	while ((cnt--) > 0)
	{
		/* Initiate write cycle and put data on GPIOs */
		GPIOE->BSRR = bsrrVal1;
		/* Stop writing sequence */
		GPIOE->BSRR = TFT_nWR;
		/* Initiate write cycle and put data on GPIOs */
		GPIOE->BSRR = bsrrVal2;
		/* Stop writing sequence */
		GPIOE->BSRR = TFT_nWR;
	}
}

void TFT_Display::SetWindow(RectType const * const rect)
{
	const uint16_t xe = rect->pos.x + rect->width - 1;
	const uint16_t ye = rect->pos.y + rect->height - 1;

	/* Set column span */
	WriteCmd(TFT_Cmd_CASET);
	/* Init data transfer */
	GPIOE->BSRR = TFT_DC;
	WriteData((uint8_t) (rect->pos.x >> TFT_Shift1Byte)); /* Column address start MSB */
	WriteData((uint8_t) rect->pos.x); /* Column address start LSB */
	WriteData((uint8_t) (xe >> TFT_Shift1Byte)); /* Column address end MSB */
	WriteData((uint8_t) xe); /* Column address end LSB */

	/* Set row span */
	WriteCmd(TFT_Cmd_RASET);
	/* Init data transfer */
	GPIOE->BSRR = TFT_DC;
	WriteData((uint8_t) (rect->pos.y >> TFT_Shift1Byte)); /* Row address start MSB */
	WriteData((uint8_t) rect->pos.y); /* Row address start LSB */
	WriteData((uint8_t) (ye >> TFT_Shift1Byte)); /* Row address end MSB */
	WriteData((uint8_t) ye); /* Row address end LSB */
}

uint16_t TFT_Display::To16bpp(uint32_t const rgbPixelValue)
{
	static const uint32_t maskRed = 0x00F80000;
	static const uint32_t maskGreen = 0x0000FC00;
	static const uint32_t maskBlue = 0x000000F8;
	static const uint8_t shiftRed = 8;
	static const uint8_t shiftGreen = 5;
	static const uint8_t shiftBlue = 3;

	return ((rgbPixelValue & maskRed) >> shiftRed) | /* ->R7-R6-R5-R4-R3 */
	((rgbPixelValue & maskGreen) >> shiftGreen) | /* ->G7-G6-G5-G4-G3-G2 */
	((rgbPixelValue & maskBlue) >> shiftBlue); /* ->B7-B6-B5-B4-B3 */
}

uint32_t TFT_Display::ToBSRRValue(uint8_t data)
{

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
	return bsrrVal | (data << TFT_ShiftHalfWord);
}

void TFT_Display::DrawFilledArea(RectType const * const rect, uint16_t const colour)
{
	/* Set drawing region and draw in the given colour */
	SetWindow(rect);
	/* Draw the arrea with the given colour */
	WritePixels(colour, rect->width * rect->height);
}
