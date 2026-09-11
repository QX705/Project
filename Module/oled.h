#ifndef __OLED_H__
#define __OLED_H__

#include "stm32f1xx_hal.h"
#include "codetab.h"
#include "i2c.h"
#include "cmsis_os.h"

#define OLED_ADDRESS  0x78 //OLED模块的I2C地址

// OLED初始化函数
void OLED_HAL_Init(void);

// OLED清除函数
void OLED_HAL_CLS(void);

// OLED显示字符串函数
void OLED_HAL_ShowStr(unsigned char x, unsigned char y, unsigned char ch[], unsigned char TextSize);

// OLED显示中文函数
void OLED_HAL_ShowCN(unsigned char x, unsigned char y, unsigned char N);

// OLED写入字节函数
void OLED_HAL_WriteByte(uint8_t addr, uint8_t data);

// OLED写入命令函数
void OLED_HAL_WriteCmd(unsigned char I2C_Command);

// OLED写入数据函数
void OLED_HAL_WriteDat(unsigned char I2C_Data);

// OLED设置位置函数
void OLED_HAL_SetPos(unsigned char x, unsigned char y);

// OLED填充函数
void OLED_HAL_Fill(unsigned char fill_Data);

// OLED显示函数
void OLED_HAL_ON(void);

// OLED关闭函数
void OLED_HAL_OFF(void);

// OLED显示字符串函数
void OLED_HAL_ShowStr(unsigned char x, unsigned char y, unsigned char ch[], unsigned char TextSize);

// OLED显示中文函数
void OLED_HAL_ShowCN(unsigned char x, unsigned char y, unsigned char N);

// OLED绘制位图函数
void OLED_HAL_DrawBMP(unsigned char x0, unsigned char y0, unsigned char x1, unsigned char y1, unsigned char BMP[]);

#endif
