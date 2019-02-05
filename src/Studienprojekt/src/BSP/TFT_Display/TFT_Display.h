
#ifndef __TFT_DISPLAY_H
#define __TFT_DISPLAY_H

#ifdef __cplusplus
 extern "C" {
#endif

#include "StdDefs.h"
#include "Fonts/Font.h"

// Display orientation is not intended
#define TFT_WIDTH	240u
#define TFT_HEIGHT	320u

void TFT_Reset(void);
void TFT_Initialize(void);
void TFT_SetForegroundColor(uint32_t const color); // 24 bit color, initialized in BLACK
void TFT_SetBackgroundColor(uint32_t const color); // 24 bit color, initialized in WHITE
void TFT_SetFont(FontType const * const font);
void TFT_ClearScreen(void);
void TFT_DrawPixel(PositionType * p);
void TFT_DrawLine(PositionType * start, PositionType * end);
void TFT_DrawChar(PositionType * p, char const c);
void TFT_DrawString(PositionType * p, char * s);

#ifdef __cplusplus
 }
#endif

#endif
