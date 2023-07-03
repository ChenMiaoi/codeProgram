#include "led.h"

void LED_Init_PP(uint32_t RCC_GPIO, GPIO_TypeDef* GPIO, uint16_t GPIO_Pins, int flag) {
    RCC_APB2PeriphClockCmd(RCC_GPIO, ENABLE);

    GPIO_InitTypeDef GPIO_LED_Structure;
    GPIO_LED_Structure.GPIO_Mode  = GPIO_Mode_Out_PP;
    GPIO_LED_Structure.GPIO_Pin   = GPIO_Pins;
    GPIO_LED_Structure.GPIO_Speed = GPIO_Speed_50MHz;

    GPIO_Init(GPIO, &GPIO_LED_Structure);

    if (flag == 1) {
        GPIO_ResetBits(GPIO, GPIO_Pins);
    } else {
        GPIO_SetBits(GPIO, GPIO_Pins);
    }
}

void LEDs_ON(GPIO_TypeDef* GPIO, uint16_t GPIO_Pins) {
    GPIO_ResetBits(GPIO, GPIO_Pins);
}


void LEDs_OFF(GPIO_TypeDef* GPIO, uint16_t GPIO_Pins) {
    GPIO_SetBits(GPIO, GPIO_Pins);
}
