/*
 * serial.c
 *
 *  Created on: 21.03.2020
 *      Author: mateusz
 */


#include "drivers/serial.h"

uint8_t srl_tx_buffer[TX_BUFFER_1_LN] = {'\0'};		// dane do wys�ania do zdalnego urz�dzenia
uint8_t srl_rx_buffer[RX_BUFFER_1_LN] = {'\0'};		// dane odebrane od zdalnego urz�dzenia

void srl_init(srl_context_t *ctx, USART_TypeDef *port, uint8_t *rx_buffer, uint16_t rx_buffer_size, uint8_t *tx_buffer, uint16_t tx_buffer_size, uint32_t baudrate, uint8_t stop_bits) {

}

uint8_t srl_send_data(srl_context_t *ctx, uint8_t* data, uint8_t mode, uint16_t leng, uint8_t internal_external) {
	return 0;
}

uint8_t srl_start_tx(srl_context_t *ctx, short leng) {
	return 0;

}

void srl_wait_for_tx_completion(srl_context_t *ctx) {

}

void srl_irq_handler(srl_context_t *ctx) {

}

uint8_t srl_receive_data(srl_context_t *ctx, int num, char start, char stop, char echo, char len_addr, char len_modifier) {
	return 0;

}

uint16_t srl_get_num_bytes_rxed(srl_context_t *ctx) {
	return 0;

}

uint8_t* srl_get_rx_buffer(srl_context_t *ctx) {
	return 0;

}

void srl_keep_timeout(srl_context_t *ctx) {

}

void srl_switch_timeout(srl_context_t *ctx, uint8_t disable_enable, uint32_t value) {

}

void srl_switch_timeout_for_waiting(srl_context_t *ctx, uint8_t disable_enable) {

}

uint8_t srl_wait_for_rx_completion_or_timeout(srl_context_t *ctx, uint8_t* output) {
	return 0;
}
