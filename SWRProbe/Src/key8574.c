#include "key8574.h"

uint8_t keyRead8574() {
	uint8_t i2c_Buffer[] = { 0x0F };

	// �������� ��������� ������ � �����
	HAL_I2C_Master_Transmit(&hi2c1, (uint16_t) (PCF8574 << 1), i2c_Buffer, 1, 1000);
	// ������ ����� ������
	HAL_I2C_Master_Receive(&hi2c1, (uint16_t) (PCF8574 << 1), i2c_Buffer, 1, 1000);

	return ~i2c_Buffer[0];
}

