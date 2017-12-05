#include "tle6208.h"
#include "spi.h"
#include "dwt_stm32_delay.h"
#include "gpio.h"

uint16_t tleWrite(uint16_t Data)
{
  uint16_t Ret;

  HAL_GPIO_WritePin(GPIOD, GPIO_PIN_2, GPIO_PIN_RESET); // CS = 0
  DWT_Delay_us(15);
  
  HAL_SPI_TransmitReceive(&hspi1, (uint8_t*)&Data, (uint8_t*)&Ret, 1, 1000);
//  HAL_SPI_Transmit(&hspi1, (uint8_t*)&Data, 1, 1000);
//  HAL_SPI_Receive(&hspi1, (uint8_t*)&Ret, 1, 1000);
    
  HAL_GPIO_WritePin(GPIOD, GPIO_PIN_2, GPIO_PIN_SET); // CS = 1
  DWT_Delay_us(15);
  return Ret;

}
