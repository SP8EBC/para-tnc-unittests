/*
 * stdperiph_stubs.c
 *
 *  Created on: 06.07.2019
 *      Author: mateusz
 */

#include "stdperiph_stubs.h"
#include <stdint.h>

void GPIO_Init(GPIO_TypeDef* GPIOx, GPIO_InitTypeDef* GPIO_InitStruct) {

}

void GPIO_ResetBits(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin) {

}

void TX20BlinkLed() {

}

uint8_t rte_wx_tx20_excessive_slew_rate = 0;
