/*
 * rte_main_stubs.c
 *
 *  Created on: Apr 20, 2024
 *      Author: mateusz
 */

#include "stored_configuration_nvm/config_data.h"
#include "message.h"

uint8_t rte_main_trigger_gsm_status = 0;

uint8_t rte_main_trigger_gsm_loginstring_packet = 0;

config_data_powersave_mode_t rte_main_curret_powersave_mode;

message_source_t rte_main_received_message_source;

message_t rte_main_received_message;

//!< Trigger preparing and sending ACK
uint8_t rte_main_trigger_message_ack = 0;
