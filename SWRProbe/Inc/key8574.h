#ifndef __key8574_H
#define __key8574_H
#ifdef __cplusplus
extern "C" {
#endif

#include "stm32f1xx_hal.h"
#include "i2c.h"

#define PCF8574  0x20
#define PCF8574_KEY1  1
#define PCF8574_KEY2  2
#define PCF8574_KEY3  4
#define PCF8574_KEY4  8

  uint8_t keyRead8574();

#ifdef __cplusplus
}
#endif
#endif
