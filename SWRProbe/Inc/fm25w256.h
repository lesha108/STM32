#ifndef __fm25w256_H
#define __fm25w256_H
#ifdef __cplusplus
extern "C" {
#endif
 
#include "stm32f1xx_hal.h"
 
  void FramWriteByte(uint16_t Address, uint8_t Data);
  uint8_t FramReadByte(uint16_t Address);
 
#ifdef __cplusplus
}
#endif
#endif