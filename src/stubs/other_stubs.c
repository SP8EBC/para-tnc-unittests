/*
 * other_stubs.c
 *
 *  Created on: 28.12.2019
 *      Author: mateusz
 */

#include <stm32f10x_dma.h>

typedef uint32_t bool;

void dma_helper_start_ch7(DMA_InitTypeDef* DMA_InitStruct) {

}

void delay_fixed(uint16_t delay_in_msecs) {

}

void GPIO_SetBits(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin) {

}

void led_control_led1_upper(bool _in) {

}

void led_control_led2_bottom(bool _in) {

}

void led_flip_led1_upper(void) {

}

void led_flip_led2_bottom(void) {

}

void led_blink_led1_upper(void) {


	led_flip_led1_upper();
}

void led_blink_led2_botoom(void) {


	led_flip_led2_bottom();

}
