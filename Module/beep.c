#include "beep.h"
#include "GY39.h"

void beep_ctr(void)
{
    // 检测温度或湿度是否超过第二级阈值（更严重）
    if (GY39Data.Temp > 3500 || GY39Data.Hum > 8500)
    {
        osDelay(20); // 延时消抖
        // 再次确认温度或湿度是否超过阈值
        if (GY39Data.Temp > 3500 || GY39Data.Hum > 8500)
        {
            // 快速蜂鸣报警，直到温度/湿度恢复正常
            while (GY39Data.Temp > 3500 || GY39Data.Hum > 8500)
            {
                HAL_GPIO_WritePin(BEEP_GPIO_PORT, BEEP_GPIO_PIN, GPIO_PIN_SET);
                osDelay(250);
                HAL_GPIO_TogglePin(BEEP_GPIO_PORT, BEEP_GPIO_PIN);
                osDelay(250);
            }
            BEEP_OFF(); // 温度或湿度返回正常阈值后关闭蜂鸣器
        }
    }
    // 检测温度或湿度是否超过第一级阈值
    else if (GY39Data.Temp > 3000 || GY39Data.Hum > 6000)
    {
        osDelay(20); // 延时消抖
        // 再次确认温度或湿度是否超过阈值
        if (GY39Data.Temp > 3000 || GY39Data.Hum > 6000)
        {
            // 慢速蜂鸣报警，直到温度/湿度恢复正常
            while (GY39Data.Temp > 3000 || GY39Data.Hum > 6000)
            {
                HAL_GPIO_WritePin(BEEP_GPIO_PORT, BEEP_GPIO_PIN, GPIO_PIN_SET);
                osDelay(500);
                HAL_GPIO_TogglePin(BEEP_GPIO_PORT, BEEP_GPIO_PIN);
                osDelay(500);
            }
            BEEP_OFF(); // 温度或湿度返回正常阈值后关闭蜂鸣器
        }
    }
    else{
        BEEP_OFF();
    }

}
