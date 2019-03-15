/**
 ******************************************************************************
 * \file    Delay.h
 * \author  Lucas Degner
 * \version V1.0.0
 * \date    30.01.2019
 * \brief   Definition of SysTick and delay functions
 ******************************************************************************
 */

#ifndef UTILITIES_DELAY_H_
#define UTILITIES_DELAY_H_

#ifdef __cplusplus
 extern "C" {
#endif

#include <stdint.h>

/**
 * \brief Initialize SysTick
 * \param None
 * \return None
 */
void InitializeSysTick(void);

/**
 * \brief Get current tick count
 * \param None
 * \return Current tick count
 */
uint32_t GetTick(void);

/**
 * \brief Increment tick counter
 * \param None
 * \return None
 */
void IncrementTick(void);

/**
 * \brief Blocking delay for n times 10us
 * \param delay Number of how often 10us delay should be waited
 * \return None
 */
void Delay_10us(uint32_t const delay);

/**
 * \brief Blocking delay for n times 1ms
 * \param delay Number of how often 1ms delay should be waited
 * \return None
 */
void Delay_ms(uint32_t const delay);

/**
 * \brief Blocking delay for n times 1s
 * \param delay Number of how often 1s delay should be waited
 * \return None
 */
void Delay_sec(uint32_t const delay);

#ifdef __cplusplus
 }
#endif

#endif
