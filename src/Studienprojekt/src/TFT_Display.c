/*
 * TFT_Display.c
 *
 *  Created on: 30.01.2019
 *      Author: degne
 */

#include "TFT_Display.h"
#include "stm32f0xx.h"

/* Constants for the pin placement */
/* Current setup -> APUS V1.1 */
static const uint16_t TFT_nCS = GPIO_Pin_8;
static const uint16_t TFT_nWR = GPIO_Pin_10;
static const uint16_t TFT_nRD = GPIO_Pin_11;
static const uint16_t TFT_DC = GPIO_Pin_9;
static const uint16_t TFT_nRES = GPIO_Pin_10;

/* Interface port */
static GPIO_TypeDef * const TFT_Port = GPIOE;
static GPIO_TypeDef * const TFT_ResPort = GPIOF;

/* Helper constants */
static const uint8_t TFT_Shift1Byte = 8;
static const uint8_t TFT_ShiftHalfWord = 16;
static const uint8_t TFT_PixelHeight = 1;
static const uint8_t TFT_PixelWidth = 1;
static const uint8_t TFT_SelColMode16bpp = 0x05;

static uint32_t ForegroundColor = 0x00000000;
static uint32_t BackgroundColor = 0x00FFFFFF;

/*
 * Defines the commands for the display
 * See TSC2046E ref. manual
 */
typedef enum
{
	TFT_Cmd_NOP = 0x00, /* No Operation */
	TFT_Cmd_RDDID = 0x04, /* Read display ID */
	TFT_Cmd_RDDST = 0x09, /* Read display status */
	TFT_Cmd_RDDPM = 0x0A, /* Read display power mode */
	TFT_Cmd_RDDMADCTL = 0x0B, /* Read display MADCTL */
	TFT_Cmd_RDDCOLMOD = 0x0C, /* Read display pixel format */
	TFT_Cmd_RDDIM = 0x0D, /* Read display image mode */
	TFT_Cmd_RDDSM = 0x0E, /* Read display signal mode */
	TFT_Cmd_RDDSDR = 0x0F, /* Read display self-diagnostic result*/
	TFT_Cmd_SLPIN = 0x10, /* Sleep in (It will be necessary to wait
	 *	5msec before sending any new commands
	 *	to the display module after this command) */
	TFT_Cmd_SLPOUT = 0x11, /* Sleep out (It will be necessary to wait
	 *	 5msec before sending any new commands
	 *	 to the display module after this command)
	 *	 (It will be necessary to wait 120msec
	 *	 after sending sleep out command
	 *	 (when in sleep in mode) before sending an
	 *	 sleep in command. */
	TFT_Cmd_PTLON = 0x12, /* Partial display mode on */
	TFT_Cmd_NORON = 0x13, /* Normal display mode on */
	TFT_Cmd_INVOFF = 0x20, /* Display inversion off */
	TFT_Cmd_INVON = 0x21, /* Display inversion on */
	TFT_Cmd_GAMSET = 0x26, /* Gamma set */
	TFT_Cmd_DISPOFF = 0x28, /* Display off */
	TFT_Cmd_DISPON = 0x29, /* Display on */
	TFT_Cmd_CASET = 0x2A, /* Column adress set */
	TFT_Cmd_RASET = 0x2B, /* Row adress set */
	TFT_Cmd_RAMWR = 0x2C, /* Memory write */
	TFT_Cmd_RAMRD = 0x2E, /* Memory read */
	TFT_Cmd_PTLAR = 0x30, /* Partial area */
	TFT_Cmd_VSCRDEF = 0x33, /* Vertical scrolling definition */
	TFT_Cmd_MADCTL = 0x36, /* Memory data access control */
	TFT_Cmd_VSCSAD = 0x37, /* Vertical scroll start adress of RAM */
	TFT_Cmd_IDMOFF = 0x38, /* Idle mode off */
	TFT_Cmd_IDMON = 0x39, /* Idle mode on */
	TFT_Cmd_COLMOD = 0x3A, /* Interface pixel format */
	TFT_Cmd_WRMEMC = 0x3C, /* Write memory continue */
	TFT_Cmd_RDMEMC = 0x3E, /* Read memory continue */
	TFT_Cmd_WRDISBV = 0x51, /* Write display brightness */
	TFT_Cmd_RDDISBV = 0x52, /* Read display brightness value */
	TFT_Cmd_WRCTRLD = 0x53, /* Write CTRL display */
	TFT_Cmd_RDCTRLD = 0x54, /* Read CTRL value display */
	TFT_Cmd_WRCACE = 0x55, /* Write content adaptive brightness control and color enhancement */
	TFT_Cmd_RDCABC = 0x56, /* Read content adaptive brightness control */
	TFT_Cmd_WRCABCMB = 0x5E, /* Write CABC minimum brightness */
	TFT_Cmd_RDCABCMB = 0x5F, /* Read CABC minimum brightness */
	TFT_Cmd_RDID1 = 0xDA, /* Read ID1 */
	TFT_Cmd_RDID2 = 0xDB, /* Read ID2 */
	TFT_Cmd_RDID3 = 0xDC, /* Read ID3 */
	TFT_Cmd_RAMCTRL = 0xB0, /* RAM control */
	TFT_Cmd_FRCTRL1 = 0xB3, /* Frame rate control 1 (In partial mode/ idle colors) */
	TFT_Cmd_DGMEN = 0xBA, /* Digital gamma enable */
	TFT_Cmd_LCMCTRL = 0xC0, /* LCM control */
	TFT_Cmd_IDSET = 0xC1, /* ID code setting */
	TFT_Cmd_FRCTRL2 = 0xC6, /* Frame control in normal mode */
	TFT_Cmd_CABCCTRL = 0xC7, /* CABC control */
	TFT_Cmd_PVGAMCTRL = 0xE0, /* Positive voltage gamma control */
	TFT_Cmd_NVGAMCTRL = 0xE1, /* Negative voltage gamma control */
	TFT_Cmd_DGMLUTR = 0xE2, /* Digital gamma look-up table for red */
	TFT_Cmd_DGMLUTB = 0xE3, /* Digital gamma look-up table for blue */
} TFT_CmdType;

/****************************************************************
 * Function declarations
 ***************************************************************/

static void TFT_WriteData(const uint8_t data);
static void TFT_WriteCmd(const TFT_CmdType command);
static void TFT_WritePixel(const uint16_t rgbPixelValue);
static void TFT_WritePixels(const uint16_t rgbPixelValue, const uint32_t num);
static void TFT_SetWindow(const RectType* const rect);
static uint32_t TFT_ToBSRRValue(const uint8_t data);
static uint16_t TFT_To16bpp(const uint32_t rgbPixelValue);
static void TFT_DrawFilledArea(const RectType* const rect, const uint16_t colour);

void TFT_Reset(void)
{
	/* Set reset active */
	TFT_ResPort->BRR = TFT_nRES;
	/* wait for at least 10 us */
	Delay_10us(1);
}

void TFT_Initialize(void)
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
	TFT_Port->BSRR = TFT_nRD | TFT_nWR;
	/* Set chip enabled */
	/* Chip can always stay enabled cause there is no other chip */
	/* on the same bus */
	TFT_Port->BRR = TFT_nCS;

	/* Set reset inactive */
	TFT_ResPort->BSRR = TFT_nRES;

	/* Using busy waiting cause init function is normaly only called once
	 * and to keep it simple */
	Delay_10us(120);

	/* After S/W reset H/W reset and power on sequence display is in sleep mode */
	/* -> Exit sleep mode */
	TFT_WriteCmd(TFT_Cmd_SLPOUT);
	Delay_10us(5);
	/* Set method of pixel data transfer */
	TFT_WriteCmd(TFT_Cmd_MADCTL);
	/* Init data transfer */
	TFT_Port->BSRR = TFT_DC;
	TFT_WriteData(0);

	/* Set choosen colour resolution */
	TFT_WriteCmd(TFT_Cmd_COLMOD);
	/* Init data transfer */
	TFT_Port->BSRR = TFT_DC;
	TFT_WriteData(TFT_SelColMode16bpp);

	/* Enable display */
	TFT_WriteCmd(TFT_Cmd_DISPON);
}

void TFT_SetForegroundColor(uint32_t const color) // 24 bit color, initialized in BLACK
{

}

void TFT_SetBackgroundColor(uint32_t const color) // 24 bit color, initialized in WHITE
{

}

void TFT_ClearScreen(void)
{
	const RectType rect = { { 0, 0 }, TFT_WIDTH, TFT_HEIGHT };
	TFT_DrawFilledArea(&rect, TFT_To16bpp(BackgroundColor));
}

void TFT_DrawPixel(PositionType * p)
{

}

void TFT_DrawLine(PositionType * start, PositionType * end)
{

}

void TFT_DrawChar(PositionType * p, char const c)
{

}

void TFT_DrawString(PositionType * p, char * s)
{

}

/************************************************************/
static void TFT_WriteData(uint8_t data)
{
	/* Initiate write cycle and put data on GPIOs */
	TFT_Port->BSRR = TFT_ToBSRRValue(data) | (TFT_nWR << TFT_ShiftHalfWord);
	/* Stop writing sequence */
	TFT_Port->BSRR = TFT_nWR;
}

static void TFT_WriteCmd(const TFT_CmdType command)
{
	/* Init command transfer */
	TFT_Port->BSRR = TFT_DC << TFT_ShiftHalfWord;
	/* Send command */
	TFT_WriteData((uint8_t) command);
}

static void TFT_WritePixel(const uint16_t rgbPixelValue)
{
	/* Write first byte */
	TFT_Port->BSRR = TFT_ToBSRRValue(
			(uint8_t) (rgbPixelValue >> TFT_Shift1Byte))
			| (TFT_nWR << TFT_ShiftHalfWord);
	TFT_Port->BSRR = TFT_nWR;
	/* Write second byte */
	TFT_Port->BSRR = TFT_ToBSRRValue((uint8_t) rgbPixelValue)
			| (TFT_nWR << TFT_ShiftHalfWord);
	TFT_Port->BSRR = TFT_nWR;
}

static void TFT_WritePixels(const uint16_t rgbPixelValue, uint32_t num)
{
	/* Send write command */
	TFT_WriteCmd(TFT_Cmd_RAMWR);
	/* Init pixel transfer */
	TFT_Port->BSRR = TFT_DC;

	/* Seperate transmit bytes and get the corresponding bsrr value */
	uint32_t bsrrVal1 = TFT_ToBSRRValue(
			(uint8_t) (rgbPixelValue >> TFT_Shift1Byte))
			| (TFT_nWR << TFT_ShiftHalfWord);
	uint32_t bsrrVal2 = TFT_ToBSRRValue((uint8_t) rgbPixelValue)
			| (TFT_nWR << TFT_ShiftHalfWord);

	while ((num--) > 0)
	{
		/* Initiate write cycle and put data on GPIOs */
		TFT_Port->BSRR = bsrrVal1;
		/* Stop writing sequence */
		TFT_Port->BSRR = TFT_nWR;
		/* Initiate write cycle and put data on GPIOs */
		TFT_Port->BSRR = bsrrVal2;
		/* Stop writing sequence */
		TFT_Port->BSRR = TFT_nWR;
	}
}

static void TFT_SetWindow(const RectType* const rect)
{
	const uint16_t xe = rect->pos.x + rect->width - 1;
	const uint16_t ye = rect->pos.y + rect->height - 1;

	/* Set column span */
	TFT_WriteCmd(TFT_Cmd_CASET);
	/* Init data transfer */
	TFT_Port->BSRR = TFT_DC;
	TFT_WriteData((uint8_t) (rect->pos.x >> TFT_Shift1Byte)); /* Column address start MSB */
	TFT_WriteData((uint8_t) rect->pos.x); /* Column address start LSB */
	TFT_WriteData((uint8_t) (xe >> TFT_Shift1Byte)); /* Column address end MSB */
	TFT_WriteData((uint8_t) xe); /* Column address end LSB */

	/* Set row span */
	TFT_WriteCmd(TFT_Cmd_RASET);
	/* Init data transfer */
	TFT_Port->BSRR = TFT_DC;
	TFT_WriteData((uint8_t) (rect->pos.y >> TFT_Shift1Byte)); /* Row address start MSB */
	TFT_WriteData((uint8_t) rect->pos.y); /* Row address start LSB */
	TFT_WriteData((uint8_t) (ye >> TFT_Shift1Byte)); /* Row address end MSB */
	TFT_WriteData((uint8_t) ye); /* Row address end LSB */
}

static uint16_t TFT_To16bpp(const uint32_t rgbPixelValue)
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

static uint32_t TFT_ToBSRRValue(uint8_t data)
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

static void TFT_DrawFilledArea(const RectType* const rect,
		const uint16_t colour)
{
	/* Set drawing region and draw in the given colour */
	TFT_SetWindow(rect);
	/* Draw the arrea with the given colour */
	TFT_WritePixels(colour, rect->width * rect->height);
}
