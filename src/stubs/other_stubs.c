/*
 * other_stubs.c
 *
 *  Created on: 28.12.2019
 *      Author: mateusz
 */

#include "stm32f10x_dma.h"
#include "stm32f10x.h"

typedef uint32_t bool;

const char * TCP2 = "TCP2\0";
const char * TCP3 = "TCP3\0";
const char * TCP4 = "TCP4\0";

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

void __DSB() {

}

void __NOP() {

}

void io___cntrl_vbat_g_disable(void) {

}

void 	io___cntrl_vbat_g_enable() {

}

void io___cntrl_gprs_pwrkey_press() {

}

void io___cntrl_gprs_pwrkey_release() {

}
