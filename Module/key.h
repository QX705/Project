#ifndef __KEY_H__
#define __KEY_H__

// 定义按键引脚端口
#define KEY1_GPIO_PORT GPIOA

// 定义按键引脚
#define KEY1_GPIO_PIN GPIO_PIN_1
#define KEY2_GPIO_PIN GPIO_PIN_7

// 定义按键引脚端口
#define KEY2_GPIO_PORT GPIOC

// 定义按键引脚
#define KEY3_GPIO_PIN GPIO_PIN_4
#define KEY4_GPIO_PIN GPIO_PIN_5

typedef enum num{
    KEY1,
    KEY2,
    KEY3,
    KEY4
}key_num;

typedef enum key_state{
    KEY1_ON,
    KEY2_ON,
    KEY3_ON,
    KEY4_ON,
    KEY_OFF
}key_state;

#include "stm32f1xx_hal.h"

key_state key_ctr(key_num KEx);

#endif
