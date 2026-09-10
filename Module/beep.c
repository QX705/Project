#include "beep.h"

void beep_ctr(void)
{
    // 检测按键是否按下
    if (HAL_GPIO_ReadPin(KEY1_GPIO_PORT, KEY1_GPIO_PIN) == GPIO_PIN_RESET)
    {
        osDelay(20); // 延时消抖
        // 再次确认
        if (HAL_GPIO_ReadPin(KEY1_GPIO_PORT, KEY1_GPIO_PIN) == GPIO_PIN_RESET)
        {
            BEEP_ON(); // 按下时蜂鸣器响
            
            // 等待按键松开
            while (HAL_GPIO_ReadPin(KEY1_GPIO_PORT, KEY1_GPIO_PIN) == GPIO_PIN_RESET)
            {
                osDelay(10); // 让出 CPU，避免卡死其他任务
            }
            
            BEEP_OFF(); // 松手后关闭蜂鸣器
        }
    }
    else
    {
        BEEP_OFF();
    }
}
