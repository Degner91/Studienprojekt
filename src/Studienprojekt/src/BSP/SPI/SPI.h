/**
 ******************************************************************************
 * \file    SPI.h
 * \author  Lucas Degner
 * \version V1.0.0
 * \date    27.02.2019
 * \brief   Definiton of SPI interface functions
 ******************************************************************************
 */

#ifndef BSP_SPI_SPI_H_
#define BSP_SPI_SPI_H_

#ifdef __cplusplus
 extern "C" {
#endif

#include <stdint.h>

 /**
  * \brief Initialize SPI hardware
  * \param None
  * \return None
  */
void SPI_Initialize(void);

/**
 * \brief Read byte from SPI interface
 * \param None
 * \return Read byte
 */
uint8_t SPI_ReadByte(void);

/**
 * \brief Write byte over SPI interface
 * \param To be sent byte
 * \return None
 */
void SPI_WriteByte(uint8_t byte);


/**
 * \brief Set chip select
 * \param None
 * \return None
 */
void SPI_CS_Select(void);

/**
 * \brief Reset chip select
 * \param None
 * \return None
 */
void SPI_CS_Deselect(void);

#ifdef __cplusplus
 }
#endif

#endif /* BSP_SPI_SPI_H_ */
