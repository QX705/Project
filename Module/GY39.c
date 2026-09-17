#include "GY39.h"

extern I2C_HandleTypeDef hi2c2;

uint8_t Single_WriteI2C_byte(uint8_t Slave_Address,uint8_t REG_Address,uint8_t data)
{
	if(HAL_I2C_Mem_Write(&hi2c2, Slave_Address, REG_Address, I2C_MEMADD_SIZE_8BIT, &data, 1, HAL_MAX_DELAY) == HAL_OK)
	{
		return SET;
	}
	return RESET;
}

uint8_t Single_ReadI2C(uint8_t Slave_Address,uint8_t REG_Address,uint8_t *REG_data,uint8_t length)
{
	if(HAL_I2C_Mem_Read(&hi2c2, Slave_Address, REG_Address, I2C_MEMADD_SIZE_8BIT, REG_data, length, HAL_MAX_DELAY) == HAL_OK)
	{
		return SET;
	}
	return RESET;
}

extern UART_HandleTypeDef huart1;

GY39_Data_t GY39Data = {0, 0, 0, 0, 0};

void GY39_ReadData(void)
{
    uint8_t raw_data[13] = {0};
    uint16_t data_16[2] = {0};
    uint8_t i2c_status;
    
    i2c_status = Single_ReadI2C(0xB6, 0x04, raw_data, 10);
    if(i2c_status)
    {
        GY39Data.Temp = (raw_data[0] << 8) | raw_data[1];
        data_16[0] = (((uint16_t)raw_data[2]) << 8) | raw_data[3];
        data_16[1] = (((uint16_t)raw_data[4]) << 8) | raw_data[5];
        GY39Data.P = (((uint32_t)data_16[0]) << 16) | data_16[1];
        GY39Data.Hum = (raw_data[6] << 8) | raw_data[7];
        GY39Data.Alt = (raw_data[8] << 8) | raw_data[9];
    }
    
    i2c_status = Single_ReadI2C(0xB6, 0x00, raw_data, 4);
    if(i2c_status)
    {
        data_16[0] = (((uint16_t)raw_data[0]) << 8) | raw_data[1];
        data_16[1] = (((uint16_t)raw_data[2]) << 8) | raw_data[3];
        GY39Data.Lux = (((uint32_t)data_16[0]) << 16) | data_16[1];
    }
}
