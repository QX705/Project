#ifndef __GY39_H__
#define __GY39_H__

#include "stm32f1xx_hal.h"

typedef struct
{
    uint16_t Temp;
    uint32_t P;
    uint16_t Hum;
    uint16_t Alt;
    uint32_t Lux;
} GY39_Data_t;

extern GY39_Data_t GY39Data;

uint8_t Single_WriteI2C_byte(uint8_t Slave_Address,uint8_t REG_Address,uint8_t data);

uint8_t Single_ReadI2C(uint8_t Slave_Address,uint8_t REG_Address,uint8_t *REG_data,uint8_t length);

void GY39_ReadData(void);

#endif
