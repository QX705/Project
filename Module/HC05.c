#include "HC05.h"

// 通过蓝牙发送GY39传感器数据
void HC05_SendGY39Data(uint16_t temp, uint16_t hum, uint32_t p, uint16_t alt, uint32_t lux)
{
    uint8_t msg_buf[100];
    uint8_t msg_len = 0;
    uint8_t num_chars[] = "0123456789";
    
    msg_buf[msg_len++] = 'T'; msg_buf[msg_len++] = 'e'; msg_buf[msg_len++] = 'm';
    msg_buf[msg_len++] = 'p'; msg_buf[msg_len++] = ':'; msg_buf[msg_len++] = ' ';
    msg_buf[msg_len++] = num_chars[(temp / 1000) % 10];
    msg_buf[msg_len++] = num_chars[(temp / 100) % 10];
    msg_buf[msg_len++] = '.';
    msg_buf[msg_len++] = num_chars[(temp / 10) % 10];
    msg_buf[msg_len++] = num_chars[temp % 10];
    msg_buf[msg_len++] = ' '; msg_buf[msg_len++] = 'C'; msg_buf[msg_len++] = ' ';
    msg_buf[msg_len++] = ' '; msg_buf[msg_len++] = 'P'; msg_buf[msg_len++] = ':';
    msg_buf[msg_len++] = ' ';
    msg_buf[msg_len++] = num_chars[(p / 10000000) % 10];
    msg_buf[msg_len++] = num_chars[(p / 1000000) % 10];
    msg_buf[msg_len++] = num_chars[(p / 100000) % 10];
    msg_buf[msg_len++] = num_chars[(p / 10000) % 10];
    msg_buf[msg_len++] = num_chars[(p / 1000) % 10];
    msg_buf[msg_len++] = num_chars[(p / 100) % 10];
    msg_buf[msg_len++] = '.';
    msg_buf[msg_len++] = num_chars[(p / 10) % 10];
    msg_buf[msg_len++] = num_chars[p % 10];
    msg_buf[msg_len++] = ' '; msg_buf[msg_len++] = 'P'; msg_buf[msg_len++] = 'a';
    msg_buf[msg_len++] = ' '; msg_buf[msg_len++] = ' '; msg_buf[msg_len++] = 'H';
    msg_buf[msg_len++] = 'u'; msg_buf[msg_len++] = 'm'; msg_buf[msg_len++] = ':';
    msg_buf[msg_len++] = ' ';
    msg_buf[msg_len++] = num_chars[(hum / 1000) % 10];
    msg_buf[msg_len++] = num_chars[(hum / 100) % 10];
    msg_buf[msg_len++] = '.'; 
    msg_buf[msg_len++] = num_chars[(hum / 10) % 10];
    msg_buf[msg_len++] = num_chars[hum % 10];
    msg_buf[msg_len++] = '%';
    msg_buf[msg_len++] = ' '; msg_buf[msg_len++] = ' '; msg_buf[msg_len++] = 'A';
    msg_buf[msg_len++] = 'l'; msg_buf[msg_len++] = 't'; msg_buf[msg_len++] = ':';
    msg_buf[msg_len++] = ' ';
    msg_buf[msg_len++] = num_chars[(alt / 100) % 10];
    msg_buf[msg_len++] = '.';
    msg_buf[msg_len++] = num_chars[(alt / 10) % 10];
    msg_buf[msg_len++] = num_chars[alt % 10];
    msg_buf[msg_len++] = ' '; msg_buf[msg_len++] = 'm'; msg_buf[msg_len++] = ' ';
    msg_buf[msg_len++] = ' '; msg_buf[msg_len++] = 'L'; msg_buf[msg_len++] = 'u';
    msg_buf[msg_len++] = 'x'; msg_buf[msg_len++] = ':'; msg_buf[msg_len++] = ' ';
    msg_buf[msg_len++] = num_chars[(lux / 10000) % 10];
    msg_buf[msg_len++] = num_chars[(lux / 1000) % 10];
    msg_buf[msg_len++] = num_chars[(lux / 100) % 10];
    msg_buf[msg_len++] = '.';
    msg_buf[msg_len++] = num_chars[(lux / 10) % 10];
    msg_buf[msg_len++] = num_chars[lux % 10];
    msg_buf[msg_len++] = ' '; msg_buf[msg_len++] = 'l'; msg_buf[msg_len++] = 'u';
    msg_buf[msg_len++] = 'x'; msg_buf[msg_len++] = '\r'; msg_buf[msg_len++] = '\n';
    
    HAL_UART_Transmit(&huart2, msg_buf, msg_len, HAL_MAX_DELAY);
}

// 构建GY39传感器数据消息（用于UART1串口打印）
void HC05_BuildMessage(uint8_t *buf, uint8_t *len, uint16_t temp, uint16_t hum, uint32_t p, uint16_t alt, uint32_t lux)
{
    uint8_t num_chars[] = "0123456789";
    uint8_t idx = 0;
    
    buf[idx++] = 'T'; buf[idx++] = 'e'; buf[idx++] = 'm';
    buf[idx++] = 'p'; buf[idx++] = ':'; buf[idx++] = ' ';
    buf[idx++] = num_chars[(temp / 1000) % 10];
    buf[idx++] = num_chars[(temp / 100) % 10];
    buf[idx++] = '.';
    buf[idx++] = num_chars[(temp / 10) % 10];
    buf[idx++] = num_chars[temp % 10];
    buf[idx++] = ' '; buf[idx++] = 'C'; buf[idx++] = ' ';
    buf[idx++] = ' '; buf[idx++] = 'P'; buf[idx++] = ':';
    buf[idx++] = ' ';
    buf[idx++] = num_chars[(p / 10000000) % 10];
    buf[idx++] = num_chars[(p / 1000000) % 10];
    buf[idx++] = num_chars[(p / 100000) % 10];
    buf[idx++] = num_chars[(p / 10000) % 10];
    buf[idx++] = num_chars[(p / 1000) % 10];
    buf[idx++] = num_chars[(p / 100) % 10];
    buf[idx++] = '.';
    buf[idx++] = num_chars[(p / 10) % 10];
    buf[idx++] = num_chars[p % 10];
    buf[idx++] = ' '; buf[idx++] = 'P'; buf[idx++] = 'a';
    buf[idx++] = ' '; buf[idx++] = ' '; buf[idx++] = 'H';
    buf[idx++] = 'u'; buf[idx++] = 'm'; buf[idx++] = ':';
    buf[idx++] = ' ';
    buf[idx++] = num_chars[(hum / 1000) % 10];
    buf[idx++] = num_chars[(hum / 100) % 10];
    buf[idx++] = '.'; 
    buf[idx++] = num_chars[(hum / 10) % 10];
    buf[idx++] = num_chars[hum % 10];
    buf[idx++] = '%';
    buf[idx++] = ' '; buf[idx++] = ' '; buf[idx++] = 'A';
    buf[idx++] = 'l'; buf[idx++] = 't'; buf[idx++] = ':';
    buf[idx++] = ' ';
    buf[idx++] = num_chars[(alt / 100) % 10];
    buf[idx++] = '.';
    buf[idx++] = num_chars[(alt / 10) % 10];
    buf[idx++] = num_chars[alt % 10];
    buf[idx++] = ' '; buf[idx++] = 'm'; buf[idx++] = ' ';
    buf[idx++] = ' '; buf[idx++] = 'L'; buf[idx++] = 'u';
    buf[idx++] = 'x'; buf[idx++] = ':'; buf[idx++] = ' ';
    buf[idx++] = num_chars[(lux / 10000) % 10];
    buf[idx++] = num_chars[(lux / 1000) % 10];
    buf[idx++] = num_chars[(lux / 100) % 10];
    buf[idx++] = '.';
    buf[idx++] = num_chars[(lux / 10) % 10];
    buf[idx++] = num_chars[lux % 10];
    buf[idx++] = ' '; buf[idx++] = 'l'; buf[idx++] = 'u';
    buf[idx++] = 'x'; buf[idx++] = '\r'; buf[idx++] = '\n';
    
    *len = idx;
}
