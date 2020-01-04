/*
 * other_stubs.h
 *
 *  Created on: 28.12.2019
 *      Author: mateusz
 */

#ifndef OTHER_STUBS_H_
#define OTHER_STUBS_H_

#include <stm32f10x_dma.h>

void dma_helper_start_ch7(DMA_InitTypeDef* DMA_InitStruct);
void delay_fixed(uint16_t delay_in_msecs);
void GPIO_SetBits(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin);



#endif /* OTHER_STUBS_H_ */
