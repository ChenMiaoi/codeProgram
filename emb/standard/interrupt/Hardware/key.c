#include "key.h"
#include "delay.h"

void KEY_Init_PP(uint32_t RCC_GPIO, GPIO_TypeDef* GPIO, uint16_t GPIO_Pins) {
    RCC_APB2PeriphClockCmd(RCC_GPIO, ENABLE);

    GPIO_InitTypeDef GPIO_KEY_Structure;
    GPIO_KEY_Structure.GPIO_Mode   = GPIO_Mode_IPU;
    GPIO_KEY_Structure.GPIO_Pin    = GPIO_Pins;
    GPIO_KEY_Structure.GPIO_Speed  = GPIO_Speed_50MHz;

    GPIO_Init(GPIO, &GPIO_KEY_Structure);
}

uint8_t KEY_Get_Value(GPIO_TypeDef* GPIO, uint16_t GPIO_Pin) {
    uint8_t key_value = 0;

    if (GPIO_ReadInputDataBit(GPIO, GPIO_Pin) == 0) {
        delay_ms(20);
        while (GPIO_ReadInputDataBit(GPIO, GPIO_Pin) == 0);
        delay_ms(20);
        key_value = 1;
    }
    return key_value;
}
