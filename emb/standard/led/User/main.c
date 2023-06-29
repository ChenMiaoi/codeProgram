#include "stm32f10x.h"
#include "delay.h"
#include "led.h"
#include "key.h"

int main(void) {
    LED_Init_PP(RCC_APB2Periph_GPIOA, GPIOA, GPIO_Pin_1 | GPIO_Pin_2, 0);
    KEY_Init_PP(RCC_APB2Periph_GPIOB, GPIOB, GPIO_Pin_2 | GPIO_Pin_3);

    uint8_t key_1 = 0;
    uint8_t key_2 = 0;
    while (1) {
        key_1 = KEY_Get_Value(GPIOB, GPIO_Pin_2);
        key_2 = KEY_Get_Value(GPIOB, GPIO_Pin_3);

        if (key_1 == 1) {
            LEDs_ON(GPIOA, GPIO_Pin_1);
        }
        
        if (key_2 == 1) {
            LEDs_OFF(GPIOA, GPIO_Pin_1);
        }
    }
}
