/**
 ******************************************************************************
 * \file    StdDefs.h
 * \author  Lucas Degner
 * \version V1.0.0
 * \date    -
 * \brief   Some definitions
 ******************************************************************************
 */

#ifndef UTILITIES_STDDEFS_H_
#define UTILITIES_STDDEFS_H_

#include <stdint.h>

/**
 * \struct PositionType
 * \brief 2D coordinate position
 */
typedef struct
{
	uint16_t x; /**< x coordinate */
	uint16_t y; /**< y coordinate */
} PositionType;

/**
 * \struct RectType
 * \brief Rectangle definition with one coordinate, width and height
 */
typedef struct
{
	PositionType pos;	/**< Position of the rectangle */
	uint32_t width;		/**< Width of the rectangle */
	uint32_t height;	/**< Height of the rectangle */
} RectType;

/**
 * \enum State
 * \brief States for menu structure
 */
enum State
{
	MENU,		/**< Main menu state */
	NETCFG, 	/**< Network config state */
	MACLIST,	/**< MAC list state */
	OVERVIEW, 	/**< Details of a MAC entry state */
	DETAILS		/**< Packets overview state */
};

#endif
