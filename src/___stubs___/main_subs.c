/*
 * main_subs.c
 *
 *  Created on: 27.12.2019
 *      Author: mateusz
 */

#include <stdint.h>

#include "config_data.h"
#include "main.h"

uint32_t master_time = 0;

char main_string_latitude[9];
char main_string_longitude[9];
char main_callsign_with_ssid[10];

char main_symbol_f;
char main_symbol_s;

config_data_mode_t * main_config_data_mode;
config_data_basic_t * main_config_data_basic;

char main_own_aprs_msg[OWN_APRS_MSG_LN];

uint32_t main_get_master_time(void) {
	return master_time;
}
