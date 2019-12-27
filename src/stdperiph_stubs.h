/*
 * stdperiph_stubs.h
 *
 *  Created on: 06.07.2019
 *      Author: mateusz
 */

#ifndef STDPERIPH_STUBS_H_
#define STDPERIPH_STUBS_H_

#include "stm32f10x.h"
#include "stm32f10x_gpio.h"

void GPIO_Init(GPIO_TypeDef* GPIOx, GPIO_InitTypeDef* GPIO_InitStruct);
void GPIO_ResetBits(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin);

void TX20BlinkLed();

extern uint8_t rte_wx_tx20_excessive_slew_rate;



#endif /* STDPERIPH_STUBS_H_ */
