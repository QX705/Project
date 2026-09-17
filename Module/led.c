#include "led.h"


//led控制
void led_ctr(void)
{
    int state = led_state();
    
    // 先关闭所有LED
    HAL_GPIO_WritePin(LED_GPIO_PORT, LED1_GPIO_PIN|LED2_GPIO_PIN|LED3_GPIO_PIN|LED4_GPIO_PIN, GPIO_PIN_SET);
    
    // 根据温度等级点亮对应数量的LED
    switch(state)
    {
        case 4:  // 温度>45°C，点亮4个LED
            HAL_GPIO_WritePin(LED_GPIO_PORT, LED1_GPIO_PIN, GPIO_PIN_RESET);
        case 3:  // 温度>40°C，点亮3个LED
            HAL_GPIO_WritePin(LED_GPIO_PORT, LED2_GPIO_PIN, GPIO_PIN_RESET);
        case 2:  // 温度>35°C，点亮2个LED
            HAL_GPIO_WritePin(LED_GPIO_PORT, LED3_GPIO_PIN, GPIO_PIN_RESET);
        case 1:  // 温度>30°C，点亮1个LED
            HAL_GPIO_WritePin(LED_GPIO_PORT, LED4_GPIO_PIN, GPIO_PIN_RESET);
            break;
        default:
            break;
    }
}

int led_state(void)
{
    if(GY39Data.Temp > 3000 || GY39Data.Hum > 8000){
        return 1;
    }
    else if(GY39Data.Temp > 3500 && GY39Data.Hum > 8500)
    {
        return 2;
    }
    else if(GY39Data.Temp > 4000 && GY39Data.Hum > 9000)
    {
        return 3;
    }
    else if(GY39Data.Temp > 4500 && GY39Data.Hum > 9500)
    {
        return 4;
    }
    return 0;
}
