#include "oled.h"

volatile uint32_t times;			//	全局变量,用于在中断处理函数中进行累加;volatile 防止优化

void OLED_HAL_Init(void)
{
    // OLED初始化序列
    osDelay(100); // 这里的延时很重要
    OLED_HAL_WriteCmd(0xAE); // display off
    OLED_HAL_WriteCmd(0x20); // Set Memory Addressing Mode
    OLED_HAL_WriteCmd(0x10); // 00,Horizontal Addressing Mode;01,Vertical Addressing Mode;10,Page Addressing Mode (RESET);11,Invalid
    OLED_HAL_WriteCmd(0xb0); // Set Page Start Address for Page Addressing Mode,0-7
    OLED_HAL_WriteCmd(0xc8); // Set COM Output Scan Direction
    OLED_HAL_WriteCmd(0x00); // ---set low column address
    OLED_HAL_WriteCmd(0x10); // ---set high column address
    OLED_HAL_WriteCmd(0x40); // --set start line address
    OLED_HAL_WriteCmd(0x81); // --set contrast control register
    OLED_HAL_WriteCmd(0xff); // 亮度调节 0x00~0xff
    OLED_HAL_WriteCmd(0xa1); // --set segment re-map 0 to 127
    OLED_HAL_WriteCmd(0xa6); // --set normal display
    OLED_HAL_WriteCmd(0xa8); // --set multiplex ratio(1 to 64)
    OLED_HAL_WriteCmd(0x3F); //
    OLED_HAL_WriteCmd(0xa4); // 0xa4,Output follows RAM content;0xa5,Output ignores RAM content
    OLED_HAL_WriteCmd(0xd3); // -set display offset
    OLED_HAL_WriteCmd(0x00); // -not offset
    OLED_HAL_WriteCmd(0xd5); // --set display clock divide ratio/oscillator frequency
    OLED_HAL_WriteCmd(0xf0); // --set divide ratio
    OLED_HAL_WriteCmd(0xd9); // --set pre-charge period
    OLED_HAL_WriteCmd(0x22); //
    OLED_HAL_WriteCmd(0xda); // --set com pins hardware configuration
    OLED_HAL_WriteCmd(0x12); //
    OLED_HAL_WriteCmd(0xdb); // --set vcomh
    OLED_HAL_WriteCmd(0x20); // 0.77xVcc
    OLED_HAL_WriteCmd(0x8d); // --set DC-DC enable
    OLED_HAL_WriteCmd(0x14); //
    OLED_HAL_WriteCmd(0xaf); // --turn on oled panel
}

/*
    功能: 往OLED写入一个字节(内部函数)
*/
void OLED_HAL_WriteByte(uint8_t addr, uint8_t data)
{
    HAL_I2C_Mem_Write(&hi2c1, OLED_ADDRESS, addr, I2C_MEMADD_SIZE_8BIT, &data, 1, 100);
}

/*
    功能: 写命令到OLED
*/
void OLED_HAL_WriteCmd(unsigned char I2C_Command)
{
    OLED_HAL_WriteByte(0x00, I2C_Command);
}

/*
    功能: 写数据到OLED
*/
void OLED_HAL_WriteDat(unsigned char I2C_Data)
{
    OLED_HAL_WriteByte(0x40, I2C_Data);
}

/*
    功能: 设置起始点坐标
*/
void OLED_HAL_SetPos(unsigned char x, unsigned char y)
{
    OLED_HAL_WriteCmd(0xb0 + y);
    OLED_HAL_WriteCmd(((x & 0xf0) >> 4) | 0x10);
    OLED_HAL_WriteCmd((x & 0x0f) | 0x01);
}

/*
    功能: 全屏填充
*/
void OLED_HAL_Fill(unsigned char fill_Data)
{
    unsigned char m, n;
    for(m = 0; m < 8; m++)
    {
        OLED_HAL_WriteCmd(0xb0 + m);      // page0-page7
        OLED_HAL_WriteCmd(0x00);          // low column start address
        OLED_HAL_WriteCmd(0x10);          // high column start address
        for(n = 0; n < 128; n++)
        {
            OLED_HAL_WriteDat(fill_Data);
        }
    }
}

/*
    功能: 清屏
*/
void OLED_HAL_CLS(void)
{
    OLED_HAL_Fill(0x00);
}

/*
    功能: 唤醒OLED
*/
void OLED_HAL_ON(void)
{
    OLED_HAL_WriteCmd(0X8D);  // 设置电荷泵
    OLED_HAL_WriteCmd(0X14);  // 开启电荷泵
    OLED_HAL_WriteCmd(0XAF);  // OLED唤醒
}

/*
    功能: 让OLED休眠
*/
void OLED_HAL_OFF(void)
{
    OLED_HAL_WriteCmd(0X8D);  // 设置电荷泵
    OLED_HAL_WriteCmd(0X10);  // 关闭电荷泵
    OLED_HAL_WriteCmd(0XAE);  // OLED休眠
}

/*
    功能: 显示字符串
    参数: x,y -- 起始点坐标(x:0~127, y:0~7); ch[] -- 要显示的字符串; TextSize -- 字符大小(1:6*8 ; 2:8*16)
*/
void OLED_HAL_ShowStr(unsigned char x, unsigned char y, unsigned char ch[], unsigned char TextSize)
{
    unsigned char c = 0, i = 0, j = 0;
    switch(TextSize)
    {
        case 1:
        {
            while(ch[j] != '\0')
            {
                c = ch[j] - 32;
                if(x > 126)
                {
                    x = 0;
                    y++;
                }
                OLED_HAL_SetPos(x, y);
                for(i = 0; i < 6; i++)
                    OLED_HAL_WriteDat(F6x8[c][i]);
                x += 6;
                j++;
            }
        } break;
        case 2:
        {
            while(ch[j] != '\0')
            {
                c = ch[j] - 32;
                if(x > 120)
                {
                    x = 0;
                    y++;
                }
                OLED_HAL_SetPos(x, y);
                for(i = 0; i < 8; i++)
                    OLED_HAL_WriteDat(F8X16[c * 16 + i]);
                OLED_HAL_SetPos(x, y + 1);
                for(i = 0; i < 8; i++)
                    OLED_HAL_WriteDat(F8X16[c * 16 + i + 8]);
                x += 8;
                j++;
            }
        } break;
    }
}

/*
    功能: 显示中文
    参数: x,y -- 起始点坐标(x:0~127, y:0~7); N:汉字在codetab.h中的索引
*/
void OLED_HAL_ShowCN(unsigned char x, unsigned char y, unsigned char N)
{
    unsigned char wm = 0;
    unsigned int adder = 32 * N;
    OLED_HAL_SetPos(x, y);
    for(wm = 0; wm < 16; wm++)
    {
        OLED_HAL_WriteDat(F16x16[adder]);
        adder += 1;
    }
    OLED_HAL_SetPos(x, y + 1);
    for(wm = 0; wm < 16; wm++)
    {
        OLED_HAL_WriteDat(F16x16[adder]);
        adder += 1;
    }
}

/*
    功能: 显示BMP位图
    参数: x0,y0 -- 起始点坐标(x0:0~127, y0:0~7); x1,y1 -- 起点对角线(结束点)的坐标(x1:1~128,y1:1~8)
*/
void OLED_HAL_DrawBMP(unsigned char x0, unsigned char y0, unsigned char x1, unsigned char y1, unsigned char BMP[])
{
    unsigned int j = 0;
    unsigned char x, y;

    if(y1 % 8 == 0)
        y = y1 / 8;
    else
        y = y1 / 8 + 1;
    for(y = y0; y < y1; y++)
    {
        OLED_HAL_SetPos(x0, y);
        for(x = x0; x < x1; x++)
        {
            OLED_HAL_WriteDat(BMP[j++]);
        }
    }
}

/*
    功能: 显示GY39传感器数据（第一页）
    参数: temp -- 温度(0.1度单位), alt -- 高度(m)
    显示: GY39、温度、海拔
*/
void OLED_HAL_ShowGY39Data(uint16_t temp, uint16_t hum, uint32_t p, uint16_t alt, uint32_t lux)
{
    unsigned char temp_str[20];
    unsigned char alt_str[20];
    uint8_t num_chars[] = "0123456789";
    
    temp_str[0] = 'T'; temp_str[1] = ':'; temp_str[2] = ' ';
    temp_str[3] = num_chars[(temp / 1000) % 10];
    temp_str[4] = num_chars[(temp / 100) % 10];
    temp_str[5] = '.';
    temp_str[6] = num_chars[(temp / 10) % 10];
    temp_str[7] = num_chars[temp % 10];
	temp_str[8] = ' ';
    temp_str[9] = 'C'; temp_str[10] = '\0';
    
    alt_str[0] = 'A'; alt_str[1] = ':'; alt_str[2] = ' ';
    alt_str[3] = num_chars[(alt / 100) % 10];
    alt_str[4] = '.';
    alt_str[5] = num_chars[(alt / 10) % 10];
    alt_str[6] = num_chars[alt % 10];
	alt_str[7] = ' ';
    alt_str[8] = 'm'; alt_str[9] = '\0';
    
    OLED_HAL_ShowStr(0, 1, "GY39:", 2);
    OLED_HAL_ShowStr(0, 3, temp_str, 2);
    OLED_HAL_ShowStr(0, 5, alt_str, 2);
}

/*
    功能: 显示GY39传感器数据（第二页）
    参数: hum -- 湿度(0.1%单位), p -- 气压(Pa), lux -- 光照度(lux)
    显示: 湿度、气压、光照度
*/
void OLED_HAL_ShowGY39Data2(uint16_t hum, uint32_t p, uint32_t lux)
{
    unsigned char hum_str[20];
    unsigned char p_str[20];
    unsigned char lux_str[20];
    uint8_t num_chars[] = "0123456789";
    
    hum_str[0] = 'H'; hum_str[1] = ':'; hum_str[2] = ' ';
    hum_str[3] = num_chars[(hum / 1000) % 10];
    hum_str[4] = num_chars[(hum / 100) % 10];
    hum_str[5] = '.';
    hum_str[6] = num_chars[(hum / 10) % 10];
    hum_str[7] = num_chars[hum % 10];
	hum_str[8] = ' ';
    hum_str[9] = '%'; hum_str[10] = '\0';
    
    p_str[0] = 'P'; p_str[1] = ':'; p_str[2] = ' ';
    p_str[3] = num_chars[(p / 10000000) % 10];
    p_str[4] = num_chars[(p / 1000000) % 10];
    p_str[5] = num_chars[(p / 100000) % 10];
    p_str[6] = num_chars[(p / 10000) % 10];
    p_str[7] = num_chars[(p / 1000) % 10];
    p_str[8] = num_chars[(p / 100) % 10];
    p_str[9] = '.';
    p_str[10] = num_chars[(p / 10) % 10];
    p_str[11] = num_chars[p % 10];
	p_str[12] = ' ';
    p_str[13] = 'P'; p_str[14] = '\0';
    
    lux_str[0] = 'L'; lux_str[1] = ':'; lux_str[2] = ' ';
    lux_str[3] = num_chars[(lux / 10000) % 10];
    lux_str[4] = num_chars[(lux / 1000) % 10];
    lux_str[5] = num_chars[(lux / 100) % 10];
    lux_str[6] = '.';
    lux_str[7] = num_chars[(lux / 10) % 10];
    lux_str[8] = num_chars[lux % 10];
	lux_str[9] = ' ';
    lux_str[10] = 'l'; lux_str[11] = '\0';
    
    OLED_HAL_ShowStr(0, 1, hum_str, 2);
    OLED_HAL_ShowStr(0, 3, p_str, 2);
    OLED_HAL_ShowStr(0, 5, lux_str, 2);
}
