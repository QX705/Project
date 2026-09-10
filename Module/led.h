#ifndef __LED_H__
#define __LED_H__   

// 定义LED引脚端口
#define LED_GPIO_PORT GPIOA

// 定义LED引脚
#define LED1_GPIO_PIN GPIO_PIN_11
#define LED2_GPIO_PIN GPIO_PIN_12
#define LED3_GPIO_PIN GPIO_PIN_13
#define LED4_GPIO_PIN GPIO_PIN_14

#include "stm32f1xx_hal.h"
#include <stdint.h>
#include "cmsis_os.h"


void led_ctr(void);

#endif
