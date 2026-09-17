#ifndef __HC05_H__
#define __HC05_H__

#include "stm32f1xx_hal.h"
#include "usart.h"
#include "string.h"
#include "stdio.h"

void HC05_SendGY39Data(uint16_t temp, uint16_t hum, uint32_t p, uint16_t alt, uint32_t lux);
void HC05_BuildMessage(uint8_t *buf, uint8_t *len, uint16_t temp, uint16_t hum, uint32_t p, uint16_t alt, uint32_t lux);

#endif
