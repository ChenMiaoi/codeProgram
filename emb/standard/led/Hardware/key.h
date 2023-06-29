#ifndef __KEY_H__
#define __KEY_H__

#include "stm32f10x.h"

/**
 * @brief the led init function
 * @param RCC_GPIO the RCC_APB2PeriphGPIO
 * @param GPIO the GPIOA、B、C....
 * @param GPIO_Pins GPIO_Pin_0 | GPIO_Pin_1 ....
 */
void KEY_Init_PP(uint32_t RCC_GPIO, GPIO_TypeDef* GPIO, uint16_t GPIO_Pins);

uint8_t KEY_Get_Value(GPIO_TypeDef* GPIO, uint16_t GPIO_Pin);

#endif //! __KEY__H__
