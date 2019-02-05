/*
 * LED.h
 *
 *  Created on: 05.02.2019
 *      Author: degne
 */

#ifndef _LED_H_
#define _LED_H_

#ifdef __cplusplus
 extern "C" {
#endif

enum LED_Color
{
	Red, Yellow, Green, All
};

void LED_Initialize();
void LED_On(LED_Color const color);
void LED_Off(LED_Color const color);
void LED_Toggle(LED_Color const color);

#ifdef __cplusplus
 }
#endif

#endif
