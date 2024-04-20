/*
 * stdperiph_stubs.c
 *
 *  Created on: 06.07.2019
 *      Author: mateusz
 */

#include <___stubs___/stdperiph_stubs.h>
#include "stm32f10x_tim.h"
#include "stm32f10x_dma.h"
#include <stdint.h>

void GPIO_Init(GPIO_TypeDef* GPIOx, GPIO_InitTypeDef* GPIO_InitStruct) {

}

void GPIO_ResetBits(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin) {

}

void TX20BlinkLed() {

}

void Configure_GPIO(GPIO_TypeDef* gpio, uint8_t pin, uint8_t conf) {

}

void TIM_DeInit(TIM_TypeDef* TIMx) {

}

void TIM_TimeBaseStructInit(TIM_TimeBaseInitTypeDef* TIM_TimeBaseInitStruct) {

}

void TIM_TimeBaseInit(TIM_TypeDef* TIMx, TIM_TimeBaseInitTypeDef* TIM_TimeBaseInitStruct) {

}

void TIM_TIxExternalClockConfig(TIM_TypeDef* TIMx, uint16_t TIM_TIxExternalCLKSource,
                                uint16_t TIM_ICPolarity, uint16_t ICFilter) {

}

void TIM_ETRClockMode2Config(TIM_TypeDef* TIMx, uint16_t TIM_ExtTRGPrescaler,
                             uint16_t TIM_ExtTRGPolarity, uint16_t ExtTRGFilter) {

}

void TIM_SetCounter(TIM_TypeDef* TIMx, uint16_t Counter) {

}

uint16_t TIM_GetCounter(TIM_TypeDef* TIMx) {
	return 0;
}

void TIM_Cmd(TIM_TypeDef* TIMx, FunctionalState NewState) {

}

void TIM_DMACmd(TIM_TypeDef* TIMx, uint16_t TIM_DMASource, FunctionalState NewState) {

}

void TIM_ITConfig(TIM_TypeDef* TIMx, uint16_t TIM_IT, FunctionalState NewState) {

}

void DMA_StructInit(DMA_InitTypeDef* DMA_InitStruct) {

}

void DMA_DeInit(DMA_Channel_TypeDef* DMAy_Channelx) {

}

void DMA_Init(DMA_Channel_TypeDef* DMAy_Channelx, DMA_InitTypeDef* DMA_InitStruct) {

}
