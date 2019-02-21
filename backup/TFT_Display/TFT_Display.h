#ifndef __TFT_DISPLAY_H
#define __TFT_DISPLAY_H

#include "StdDefs.h"
#include "Fonts/Font.h"
#include "stdint.h"
#include "Color.h"

class TFT_Display
{
public:
	static TFT_Display& GetInstance()
	{
		static TFT_Display instance;
		return instance;
	}
	~TFT_Display()
	{
	}

	// Dynamic display orientation is not intended in this project
	static uint32_t const WIDTH = 240;
	static uint32_t const HEIGHT = 320;

	void Initialize();
	void Reset();
	void SetForegroundColor(uint32_t const color); // 24 bit color, initialized in BLACK
	void SetBackgroundColor(uint32_t const color); // 24 bit color, initialized in WHITE
	void SetFont(FontType const * const font);
	void ClearScreen(void);
	void DrawPixel(PositionType const * const p);
	void DrawLine(PositionType const * const start, PositionType const * const end);
	void DrawChar(PositionType const * const p, char const c);
	void DrawString(PositionType const * const p, char const * const s);

private:
	// prevent more than one instances
	TFT_Display()
	{
		foregroundColor = TFT_COLOUR_BLACK;
		backgroundColor = TFT_COLOUR_WHITE;
		font = 0;
	}
	TFT_Display(TFT_Display const &);
	TFT_Display& operator =(TFT_Display const &);

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
	} CmdType;

	void WriteData(uint8_t const data);
	void WriteCmd(CmdType const command);
	void WritePixel(uint16_t const rgbPixelValue);
	void WritePixels(uint16_t const rgbPixelValue, uint32_t const num);
	void SetWindow(RectType const * const rect);
	uint32_t ToBSRRValue(uint8_t const data);
	uint16_t To16bpp(uint32_t const rgbPixelValue);
	void DrawFilledArea(RectType const * const rect, uint16_t const colour);
	void DrawImage1bpp(RectType const * const rect, uint32_t const * const data, uint32_t const colours);

	uint32_t foregroundColor;
	uint32_t backgroundColor;
	FontType const * font;
};

#endif
