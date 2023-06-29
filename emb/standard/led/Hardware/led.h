#ifndef __LED_H__
#define __LED_H__

#include "stm32f10x.h"

/**
 * @brief the led init function
 * @param RCC_GPIO the RCC_APB2PeriphGPIO
 * @param GPIO the GPIOA、B、C....
 * @param GPIO_Pins GPIO_Pin_0 | GPIO_Pin_1 ....
 * @param flag the led on by default
 */
void LED_Init_PP(uint32_t RCC_GPIO, GPIO_TypeDef* GPIO, uint16_t GPIO_Pins, int flag);

/**
 * @brief the led on
 * @param GPIO the GPIOA、B、C....
 * @param GPIO_Pins GPIO_Pin_0 | GPIO_Pin_1 ....
 */
void LEDs_ON(GPIO_TypeDef* GPIO, uint16_t GPIO_Pins);

/**
 * @brief the led off
 * @param GPIO the GPIOA、B、C....
 * @param GPIO_Pins GPIO_Pin_0 | GPIO_Pin_1 ....
 */
void LEDs_OFF(GPIO_TypeDef* GPIO, uint16_t GPIO_Pins);

#endif //! __LED_H__
