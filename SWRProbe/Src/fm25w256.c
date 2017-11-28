#include "fm25w256.h"
#include "spi.h"
#include "dwt_stm32_delay.h"
#include "gpio.h"

uint8_t WREN = 0x06;
uint8_t WRITE = 0x02;
uint8_t READ = 0x03;
uint8_t RDSR = 0x05;
uint8_t WRSR = 0x01;
uint8_t WRDI = 0x04;
uint8_t DUMMY = 0xff;

void FramWriteByte(uint16_t Address, uint8_t Data)
{
  uint8_t AddressMSB = (uint8_t)((Address & 0xFF00) >> 8);
  uint8_t AddressLSB = (uint8_t)(Address & 0x00FF);
  
  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, GPIO_PIN_RESET); // CS = 0
  DWT_Delay_us(1);
  
  HAL_SPI_Transmit(&hspi2, &WREN, 1, 1000);
  
  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, GPIO_PIN_SET); // CS = 1
  DWT_Delay_us(1);
  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, GPIO_PIN_RESET); // CS = 0
  DWT_Delay_us(1);
  
  HAL_SPI_Transmit(&hspi2, &WRITE, 1, 1000);
  HAL_SPI_Transmit(&hspi2, &AddressMSB, 1, 1000);
  HAL_SPI_Transmit(&hspi2, &AddressLSB, 1, 1000);
  HAL_SPI_Transmit(&hspi2, &Data, 1, 1000);
  
  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, GPIO_PIN_SET); // CS = 1
  DWT_Delay_us(1);
}

uint8_t FramReadByte(uint16_t Address)
{ 
  uint8_t Ret;
  
  uint8_t AddressMSB = (uint8_t)((Address & 0xFF00) >> 8);
  uint8_t AddressLSB = (uint8_t)(Address & 0x00FF);
  
  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, GPIO_PIN_RESET); // CS = 0
  DWT_Delay_us(1);
 
  HAL_SPI_Transmit(&hspi2, &READ, 1, 1000);
  HAL_SPI_Transmit(&hspi2, &AddressMSB, 1, 1000);
  HAL_SPI_Transmit(&hspi2, &AddressLSB, 1, 1000);
  HAL_SPI_Receive(&hspi2, &Ret, 1, 1000);
  
  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, GPIO_PIN_SET); // CS = 1
  DWT_Delay_us(1);
  
  return Ret;
}
