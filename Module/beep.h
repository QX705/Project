#ifndef __BEEP_H__
#define __BEEP_H__

// 定义蜂鸣器引脚端口
#define BEEP_GPIO_PORT GPIOA

// 定义蜂鸣器引脚
#define BEEP_GPIO_PIN GPIO_PIN_8

//BEEP状态控制
#define BEEP_ON() HAL_GPIO_WritePin(BEEP_GPIO_PORT, BEEP_GPIO_PIN, GPIO_PIN_SET)
#define BEEP_OFF() HAL_GPIO_WritePin(BEEP_GPIO_PORT, BEEP_GPIO_PIN, GPIO_PIN_RESET)

typedef enum beep_state{
    BEEP_ON,
    BEEP_OFF
}BEEP_Status;

#include "stm32f1xx_hal.h"
#include "cmsis_os.h"

void beep_ctr(void); 

#endif
