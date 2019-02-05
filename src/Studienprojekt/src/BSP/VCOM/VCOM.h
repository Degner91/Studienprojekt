/*
 * VCOM.h
 *
 *  Created on: 05.02.2019
 *      Author: degne
 */

#ifndef BSP_VCOM_VCOM_H_
#define BSP_VCOM_VCOM_H_

#ifdef __cplusplus
 extern "C" {
#endif

void VCOM_Initialize();
void VCOM_Print(char * s);
void VCOM_Println(char * s);

#ifdef __cplusplus
 }
#endif

#endif /* BSP_VCOM_VCOM_H_ */
