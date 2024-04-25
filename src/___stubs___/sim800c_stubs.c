/*
 * sim800c_stubs.c
 *
 *  Created on: Jun 15, 2023
 *      Author: mateusz
 */


#include "gsm/sim800c.h"
#include "gsm/sim800c_engineering.h"
#include "gsm/sim800c_gprs.h"
#include "gsm/sim800c_inline.h"
#include "gsm/sim800c_tcpip.h"
#include "gsm/sim800_return_t.h"
#include "gsm/sim800_async_message_t.h"
#include "gsm/sim800_simcard_status_t.h"
#include "gsm/sim800_network_status_t.h"

#include "main.h"
#include "io.h"

#include "text.h"

#include <string.h>
#include <stdlib.h>

//#define SIM800_DEFAULT_TIMEOUT 250	// in miliseconds
//
//
///**
// * Detect async messages which are not a response to AT commands, but a status
// * sent by GSM module on it's own when some event is detected. If async message
// * is dected it rewind an offset over this async, to the begin of real response
// * @param ptr	pointer to buffer with data to look through
// * @param size	size of this buffer
// * @param offset
// * @return	Type of async message detected or unknown if nothing has been found
// */
//sim800_async_message_t gsm_sim800_check_for_async_messages(uint8_t * ptr, uint16_t size, uint16_t * offset) {
//	// offset is a pointer to variable where this function will store a position of first response character
//	// after the async message
//
//	sim800_async_message_t out = SIM800_ASYNC_UNKNOWN;
//
//
//	return out;
//
//}
//
///**
// * Function checks how many lines has been returned in a response from GSM modem
// * which miht be a signal that async message was somewhere received.
// * @param ptr
// * @param size
// * @return
// */
//uint32_t gsm_sim800_check_for_extra_newlines(uint8_t * ptr, uint16_t size) {
//
//	return 0;
//}
//
//uint8_t gsm_sim800_get_waiting_for_command_response(void) {
//	return 0;
//}
//
////gsm_response_start_idx
//uint16_t gsm_sim800_get_response_start_idx(void) {
//	return 0;
//}
//
//void gsm_sim800_init(gsm_sim800_state_t * state, uint8_t enable_echo) {
//
//}
//
//void gsm_sim800_initialization_pool(srl_context_t * srl_context, gsm_sim800_state_t * state) {
//
//}
//
///**
// * Callback used to terminate UART serial transaction
// */
//uint8_t gsm_sim800_rx_terminating_callback(uint8_t current_data, const uint8_t * const rx_buffer, uint16_t rx_bytes_counter) {
//
//	return 0;
//
//}
//
///**
// *	This is a main callback invoked, when any data has been received from GSM modem
// */
//void gsm_sim800_rx_done_event_handler(srl_context_t * srl_context, gsm_sim800_state_t * state) {
//
//}
//
//void gsm_sim800_tx_done_event_handler(srl_context_t * srl_context, gsm_sim800_state_t * state) {
//
//
//}
//
///**
// * Power cycle GSM modem
// * @param state
// */
//void gsm_sim800_reset(gsm_sim800_state_t * state) {
//
//}

sim800_return_t gsm_sim800_tcpip_connect(char * ip_or_dns_address, uint8_t address_ln, char * port, uint8_t port_ln, srl_context_t * srl_context, gsm_sim800_state_t * state) {
	// this function has blocking io

	sim800_return_t out = SIM800_OK;

	return out;
}

sim800_return_t gsm_sim800_tcpip_async_receive(srl_context_t * srl_context, gsm_sim800_state_t * state, srl_rx_termination_callback_t rx_callback, uint32_t timeout, gsm_sim800_tcpip_receive_callback_t rx_done_callback) {

	sim800_return_t out = SIM800_OK;

	return out;
}

sim800_return_t gsm_sim800_tcpip_receive(uint8_t * buffer, uint16_t buffer_size, srl_context_t * srl_context, gsm_sim800_state_t * state, srl_rx_termination_callback_t rx_callback, uint32_t timeout) {

	sim800_return_t out = SIM800_UNSET;

	return out;
}

sim800_return_t gsm_sim800_tcpip_async_write(uint8_t * data, uint16_t data_len, srl_context_t * srl_context, gsm_sim800_state_t * state) {
	sim800_return_t out = SIM800_OK;

	return out;
}

sim800_return_t gsm_sim800_tcpip_write(uint8_t * data, uint16_t data_len, srl_context_t * srl_context, gsm_sim800_state_t * state) {

	sim800_return_t out = SIM800_OK;

	return out;
}

/**
 * Closes established TCP connection
 * @param srl_context	pointer to serial context used to communication with gprs module
 * @param state
 * @param force			force changing internal connection state even if there
 * 						were problems with a response to diconnection AT command.
 * @return	SIM800_OK connection was closed successfully
 *			SIM800_TCP_CLOSE_ALREADY connection has been closed in the meantime by remote server
 *			SIM800_TCP_CLOSE_UNCERTAIN no valid response was received from gprs module on disconnect request
 *			SIM800_WRONG_STATE_TO_CLOSE no connection has been
 */
sim800_return_t gsm_sim800_tcpip_close(srl_context_t * srl_context, gsm_sim800_state_t * state, uint8_t force) {

	/**
	 * Name : srl_rx_buf_pointer
	Details:0x20000828 <srl_usart3_rx_buffer> "AT+CIPCLOSE\r\r\nERROR\r\n"
	 *
	 *Name : srl_rx_buf_pointer
	Details:0x20000828 <srl_usart3_rx_buffer> "AT+CIPCLOSE\r\r\nCLOSE OK"
	 *
	 */

	sim800_return_t out = SIM800_UNSET;

	return out;
}

void gsm_sim800_tcpip_rx_done_callback(srl_context_t * srl_context, gsm_sim800_state_t * state) {

}

void gsm_sim800_tcpip_tx_done_callback(srl_context_t * srl_context, gsm_sim800_state_t * state) {

}

uint8_t gsm_sim800_newline_terminating_callback(uint8_t current_data, const uint8_t * const rx_buffer, uint16_t rx_bytes_counter) {

	sim800_return_t out = SIM800_OK;

	return out;
}

void gsm_sim800_tcpip_reset(void) {

}

uint8_t gsm_sim800_tcpip_tx_busy(void) {
	return 0;
}


