#include "key.h"

key_state key_ctr(key_num KEx)
{
    switch(KEx)
    {
        case KEY1:
            HAL_GPIO_ReadPin(KEY1_GPIO_PORT, KEY1_GPIO_PIN);
            return KEY1_ON;
        case KEY2:
            HAL_GPIO_ReadPin(KEY1_GPIO_PORT, KEY2_GPIO_PIN);
            return KEY2_ON;
        case KEY3:
            HAL_GPIO_ReadPin(KEY2_GPIO_PORT, KEY3_GPIO_PIN);
            return KEY3_ON;
        case KEY4:
            HAL_GPIO_ReadPin(KEY2_GPIO_PORT, KEY4_GPIO_PIN);
            return KEY4_ON;
    }
    return KEY_OFF;
}
