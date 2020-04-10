/*
 * umb_master_test.cpp
 *
 *  Created on: 21.03.2020
 *      Author: mateusz
 */

extern "C" {
#include "inc/umb_master/umb_master.h"
#include "inc/umb_master/umb_0x23_offline_data.h"
#include "inc/umb_master/umb_0x26_status.h"
#include "stdperiph_stubs.h"
#include "rte_wx.h"
#include "other_stubs.h"
//#include <cstdint>

}

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE UMB_MASTER
#include <boost/test/unit_test.hpp>

unsigned char dummy_rx_buffer[64];
umb_context_t ctx;


struct fixture_qf {
	fixture_qf() {
		::umb_master_init(&ctx);
	}
};

struct fixture_1 {
	fixture_1() {
		::umb_master_init(&ctx);

		::memset(dummy_rx_buffer, 0x00, sizeof(dummy_rx_buffer));
		dummy_rx_buffer[0] = 0x01;
		dummy_rx_buffer[1] = 0x10;
		dummy_rx_buffer[2] = 0x01;
		dummy_rx_buffer[3] = 0xF0;
		dummy_rx_buffer[4] = 0x01;
		dummy_rx_buffer[5] = 0x80;
		dummy_rx_buffer[6] = 0x0A;
		dummy_rx_buffer[7] = 0x02;
		dummy_rx_buffer[8] = 0x23;
		dummy_rx_buffer[9] = 0x10;
		dummy_rx_buffer[10]= 0x00;
		dummy_rx_buffer[11]= 0x64;
		dummy_rx_buffer[12]= 0x00;
		dummy_rx_buffer[13]= 0x16;
		dummy_rx_buffer[14]= 0x00;
		dummy_rx_buffer[15]= 0x00;
		dummy_rx_buffer[16]= 0xB4;
		dummy_rx_buffer[17]= 0x41;
		dummy_rx_buffer[18]= 0x03;
		dummy_rx_buffer[19]= 0x1F;
		dummy_rx_buffer[20]= 0x94;
		dummy_rx_buffer[21]= 0x04;

		for (int i = 0; i < UMB_CHANNELS_STORAGE_CAPAC; i++)
			rte_wx_umb_channel_values[i][0] = (int16_t)0xFFFF;
	}
};

struct fixture_2 {
	fixture_2() {
		::umb_master_init(&ctx);

		::memset(dummy_rx_buffer, 0x00, sizeof(dummy_rx_buffer));
		dummy_rx_buffer[0] = 0x01;
		dummy_rx_buffer[1] = 0x10;
		dummy_rx_buffer[2] = 0x01;
		dummy_rx_buffer[3] = 0xF0;
		dummy_rx_buffer[4] = 0x01;
		dummy_rx_buffer[5] = 0x80;
		dummy_rx_buffer[6] = 0x0A;
		dummy_rx_buffer[7] = 0x02;
		dummy_rx_buffer[8] = 0x23;
		dummy_rx_buffer[9] = 0x10;
		dummy_rx_buffer[10]= 0x00;
		dummy_rx_buffer[11]= 0x64;
		dummy_rx_buffer[12]= 0x80;
		dummy_rx_buffer[13]= 0x16;
		dummy_rx_buffer[14]= 0x00;
		dummy_rx_buffer[15]= 0x00;
		dummy_rx_buffer[16]= 0xB4;
		dummy_rx_buffer[17]= 0x41;
		dummy_rx_buffer[18]= 0x03;
		dummy_rx_buffer[19]= 0x1F;
		dummy_rx_buffer[20]= 0x94;
		dummy_rx_buffer[21]= 0x04;

		for (int i = 0; i < UMB_CHANNELS_STORAGE_CAPAC; i++)
			rte_wx_umb_channel_values[i][0] = (int16_t)0xFFFF;
	}
};

struct fixture_int32 {
	fixture_int32() {
		::umb_master_init(&ctx);

		::memset(dummy_rx_buffer, 0x00, sizeof(dummy_rx_buffer));
		dummy_rx_buffer[0] = 0x01;
		dummy_rx_buffer[1] = 0x10;
		dummy_rx_buffer[2] = 0x01;
		dummy_rx_buffer[3] = 0xF0;
		dummy_rx_buffer[4] = 0x01;
		dummy_rx_buffer[5] = 0x80;
		dummy_rx_buffer[6] = 0x0A;
		dummy_rx_buffer[7] = 0x02;
		dummy_rx_buffer[8] = 0x23;
		dummy_rx_buffer[9] = 0x10;
		dummy_rx_buffer[10]= 0x00;
		dummy_rx_buffer[11]= 0x64;
		dummy_rx_buffer[12]= 0x80;
		dummy_rx_buffer[13]= 0x15;	// SIGNED_LONG
		dummy_rx_buffer[14]= 0xF4;
		dummy_rx_buffer[15]= 0xFF;
		dummy_rx_buffer[16]= 0xFF;
		dummy_rx_buffer[17]= 0xFF;	// -12
		dummy_rx_buffer[18]= 0x03;
		dummy_rx_buffer[19]= 0x1F;
		dummy_rx_buffer[20]= 0x94;
		dummy_rx_buffer[21]= 0x04;

		for (int i = 0; i < UMB_CHANNELS_STORAGE_CAPAC; i++)
			rte_wx_umb_channel_values[i][0] = (int16_t)0xFFFF;
	}
};

BOOST_FIXTURE_TEST_CASE(status_string, fixture_1) {
	char buffer[128];
	memset(buffer, 0x00, 0x80);
	uint16_t string_ln;

	ctx.trigger_status_msg = 1;
	ctx.nok_error_codes[0] = 0x12;
	ctx.nok_error_codes[1] = 0x32;
	ctx.nok_error_codes[2] = 0x42;
	ctx.nok_error_codes[3] = 0xF2;

	umb_construct_status_str(&ctx, buffer, 128, &string_ln, 0x1234);

	return;

}

BOOST_FIXTURE_TEST_CASE(status_string_too_small_buff, fixture_1) {
	char buffer[66];
	memset(buffer, 0x00, 66);
	uint16_t string_ln;

	ctx.trigger_status_msg = 1;
	ctx.nok_error_codes[0] = 0x12;
	ctx.nok_error_codes[1] = 0x32;
	ctx.nok_error_codes[2] = 0x42;
	ctx.nok_error_codes[3] = 0xF2;

	umb_construct_status_str(&ctx, buffer, 66, &string_ln, 0x1234);

	return;

}

BOOST_FIXTURE_TEST_CASE(offline_data_callback_1, fixture_1) {
	umb_retval_t returnvalue;
	umb_frame_t frame;

	returnvalue = umb_parse_serial_buffer_to_frame(dummy_rx_buffer, 64, &frame);

	BOOST_CHECK_EQUAL(UMB_OK, returnvalue);

	returnvalue = umb_0x23_offline_data_callback(&frame, &ctx);

	BOOST_CHECK_EQUAL(UMB_OK, returnvalue);
	BOOST_CHECK_EQUAL(225, rte_wx_umb_channel_values[0][1]);


}

BOOST_FIXTURE_TEST_CASE(offline_data_callback_big_chn, fixture_2) {
	umb_retval_t returnvalue;
	umb_frame_t frame;

	returnvalue = umb_parse_serial_buffer_to_frame(dummy_rx_buffer, 64, &frame);

	BOOST_CHECK_EQUAL(UMB_WRONG_CRC, returnvalue);

	returnvalue = umb_0x23_offline_data_callback(&frame, &ctx);

	BOOST_CHECK_EQUAL(UMB_OK, returnvalue);
	BOOST_CHECK_EQUAL(32868, (uint16_t)rte_wx_umb_channel_values[0][0]);
	BOOST_CHECK_EQUAL(225, rte_wx_umb_channel_values[0][1]);



}

BOOST_FIXTURE_TEST_CASE(offline_data_callback_int32, fixture_int32) {
	umb_retval_t returnvalue;
	umb_frame_t frame;

	returnvalue = umb_parse_serial_buffer_to_frame(dummy_rx_buffer, 64, &frame);

	BOOST_CHECK_EQUAL(UMB_WRONG_CRC, returnvalue);

	returnvalue = umb_0x23_offline_data_callback(&frame, &ctx);

	BOOST_CHECK_EQUAL(UMB_OK, returnvalue);
	BOOST_CHECK_EQUAL(32868, (uint16_t)rte_wx_umb_channel_values[0][0]);
	BOOST_CHECK_EQUAL(-120, rte_wx_umb_channel_values[0][1]);



}

/**
 * Last error sooner than 10 minutes ago
 * Last timeout later than 10 minutes ago
 */
BOOST_FIXTURE_TEST_CASE(quality_factor_1, fixture_qf) {
	uint32_t master_time;

	master_time = 0x1000 + (1000 * 600);

	ctx.time_of_last_nok = 0x500;
	ctx.time_of_last_comms_timeout = 0x2000;
	ctx.time_of_last_successful_comms = 1000 * 600;

	umb_qf_t quality_factor = umb_get_current_qf(&ctx, master_time);

	BOOST_CHECK_EQUAL(UMB_QF_DEGRADED, quality_factor);
}

/**
 * Last error sooner than 10 minutes ago
 * Last timeout sooner than 10 minutes ago
 */
BOOST_FIXTURE_TEST_CASE(quality_factor_2, fixture_qf) {
	uint32_t master_time;

	master_time = 0x4000 + (1000 * 600);

	ctx.time_of_last_nok = 0x500;
	ctx.time_of_last_comms_timeout = 0x2000;
	ctx.time_of_last_successful_comms = 1000 * 600;

	umb_qf_t quality_factor = umb_get_current_qf(&ctx, master_time);

	BOOST_CHECK_EQUAL(UMB_QF_FULL, quality_factor);
}

