
#ifndef __STDDEFS_H
#define __STDDEFS_H

#include <stdint.h>

typedef struct
{
	uint16_t x;
	uint16_t y;
} PositionType;

typedef struct
{
	PositionType pos;
	uint16_t width;
	uint16_t height;
} RectType;

#endif
