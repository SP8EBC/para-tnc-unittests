/*
 * packet_tx_handler_stubs.c
 *
 *  Created on: Apr 20, 2024
 *      Author: mateusz
 */

#include "packet_tx_handler.h"


void packet_tx_send_wx_frame(void) {

}

void packet_tx_init(uint8_t meteo_interval, uint8_t beacon_interval, config_data_powersave_mode_t powersave) {

}
void packet_tx_restore_from_backupregs(void) {

}

void packet_tx_tcp_handler(void) {

}

void packet_tx_handler(const config_data_basic_t * const config_basic, const config_data_mode_t * const config_mode) {

}

void packet_tx_get_current_counters(packet_tx_counter_values_t * out) {

}

void packet_tx_set_current_counters(packet_tx_counter_values_t * in) {

}

int16_t packet_tx_get_minutes_to_next_wx(void) {
	return 0;
}

uint8_t packet_tx_is_gsm_meteo_pending(void) {
	return 0;
}

void packet_tx_force_gsm_status(void) {

}
