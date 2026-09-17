#include "led.h"

uint32_t led_pin[4] = {LED1_GPIO_PIN, LED2_GPIO_PIN, LED3_GPIO_PIN, LED4_GPIO_PIN};
//流水灯
void led_ctr(void)
{
    int i = 0;

    for(i = 0;i < 4;i++)
    {
        // 关闭LED
        HAL_GPIO_WritePin(LED_GPIO_PORT, LED1_GPIO_PIN | LED2_GPIO_PIN | LED3_GPIO_PIN | LED4_GPIO_PIN, GPIO_PIN_RESET);
        osDelay(100);

        // 点亮LED
        HAL_GPIO_WritePin(LED_GPIO_PORT, led_pin[i], GPIO_PIN_SET);
        osDelay(100);
    }
}
