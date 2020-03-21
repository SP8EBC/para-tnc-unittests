/*
 * serial.c
 *
 *  Created on: 21.03.2020
 *      Author: mateusz
 */


#include "drivers/serial.h"

uint8_t srl_tx_buffer[TX_BUFFER_LN] = {'\0'};		// dane do wys�ania do zdalnego urz�dzenia
uint8_t srl_rx_buffer[RX_BUFFER_LN] = {'\0'};		// dane odebrane od zdalnego urz�dzenia

void srl_init(void) {

}

uint8_t srl_send_data(uint8_t* data, uint8_t mode, uint16_t leng, uint8_t internal_external) {
	return 0;
}

uint8_t srl_start_tx(short leng) {
	return 0;

}

void srl_wait_for_tx_completion() {

}

void srl_irq_handler(void) {

}

uint8_t srl_receive_data(int num, char start, char stop, char echo, char len_addr, char len_modifier) {
	return 0;

}

uint16_t srl_get_num_bytes_rxed() {
	return 0;

}

uint8_t* srl_get_rx_buffer() {
	return 0;

}

void srl_keep_timeout(void) {

}

void srl_switch_timeout(uint8_t disable_enable, uint32_t value) {

}
