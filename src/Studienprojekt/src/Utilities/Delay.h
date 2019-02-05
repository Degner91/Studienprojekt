
#ifndef __DELAY_H
#define __DELAY_H

#ifdef __cplusplus
 extern "C" {
#endif

#include <stdint.h>

void InitializeSysTick(void);
uint32_t GetTick(void);
void IncrementTick(void);
void Delay_10us(uint32_t const delay);

#ifdef __cplusplus
 }
#endif

#endif
