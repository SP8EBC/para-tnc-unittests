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

uint32_t main_get_nvm_timestamp(void) {
	uint32_t out = 123u;

	/**
	 * Date-time timestamp in timezone local for a place where station is installed.
	 * Mixture of BCD and integer format, this is just sligtly processed RTC registers
	 * content.
	 *	bit 0  - bit 12 === number of minutes starting from midnight (max 1440)
	 *	bit 16 - bit 24 === days from new year (max 356)
	 *	bit 25 - bit 31 === years (from 00 to 99, from 2000 up to 2099)
	 */

#ifdef STM32L471xx

	uint16_t temp = 0;

	// minutes
	temp = 600 * ((RTC->TR & RTC_TR_HT) >> RTC_TR_HT_Pos) +
			60 * ((RTC->TR & RTC_TR_HU) >> RTC_TR_HU_Pos) +
			10 * ((RTC->TR & RTC_TR_MNT) >> RTC_TR_MNT_Pos) +
			 1 * ((RTC->TR & RTC_TR_MNU) >> RTC_TR_MNU_Pos);

	out = out | (temp & 0x7FF);

	// current month
	temp = 	 1 * ((RTC->DR & RTC_DR_MU) >> RTC_DR_MU_Pos) +
			10 * ((RTC->DR & RTC_DR_MT) >> RTC_DR_MT_Pos);

	switch (temp) {
	case 1: temp = 0; break;
	case 2: temp = 31; break;
	case 3: temp = 31 + 28; break;
	case 4:	temp = 31 + 28 + 31; break;
	case 5: temp = 31 + 28 + 31 + 30; break;
	case 6: temp = 31 + 28 + 31 + 30 + 31; break;
	case 7: temp = 31 + 28 + 31 + 30 + 31 + 30; break;
	case 8: temp = 31 + 28 + 31 + 30 + 31 + 30 + 31; break;
	case 9: temp = 31 + 28 + 31 + 30 + 31 + 30 + 31 + 31; break;
	case 10:temp = 31 + 28 + 31 + 30 + 31 + 30 + 31 + 31 + 30; break;
	case 11:temp = 31 + 28 + 31 + 30 + 31 + 30 + 31 + 31 + 30 + 31; break;
	case 12:temp = 31 + 28 + 31 + 30 + 31 + 30 + 31 + 31 + 30 + 31 + 30; break;
	}

	// then add number of days from current month
	temp = temp +
			 1 * ((RTC->DR & RTC_DR_DU) >> RTC_DR_DU_Pos) +
			10 * ((RTC->DR & RTC_DR_DT) >> RTC_DR_DT_Pos);

	out = out | ((temp & 0x1FF) << 16);

	// years
	temp = 	10 * ((RTC->DR & RTC_DR_YT) >> RTC_DR_YT_Pos) +
			 1 * ((RTC->DR & RTC_DR_YU) >> RTC_DR_YU_Pos);

	out = out | ((temp & 0x7F) << 25);

#endif

	return out;
}
