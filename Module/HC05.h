#ifndef __HC05_H__
#define __HC05_H__

#include "stm32f1xx_hal.h"
#include "usart.h"
#include "string.h"
#include "stdio.h"

typedef struct
{
    uint32_t P;
    uint16_t Temp;
    uint16_t Hum;
    uint16_t Alt;
} bme;

extern bme Bme;

void USART1_send_byte(uint8_t byte);
void USART2_send_byte(uint8_t byte);
void send_3out(uint8_t *data,uint8_t len,uint8_t send);
void send_out(uint16_t *data,uint8_t len,uint8_t send);
void display(int16_t *num,uint8_t send,uint8_t count);
void USART_Send(uint8_t *Buffer, uint8_t Len);
void USART_Send_bytes(uint8_t *Buffer, uint8_t Len);
void CHeck(uint8_t *re_data);
int fputc(int ch, FILE *f);

// HC05蓝牙模块函数
void HC05_Init(void);
void HC05_SendString(const char *str);
void HC05_SendGY39Data(uint16_t temp, uint16_t hum, uint32_t p, uint16_t alt, uint32_t lux);
void HC05_BuildMessage(uint8_t *buf, uint8_t *len, uint16_t temp, uint16_t hum, uint32_t p, uint16_t alt, uint32_t lux);

#endif
