/*
 * gsm_rx_handler_test.cpp
 *
 *  Created on: Feb 14, 2022
 *      Author: mateusz
 */


extern "C" {
#include "gsm/sim800c.h"
#include "gsm/sim800c_inline.h"
#include "stdperiph_stubs.h"
#include "rte_wx.h"
#include "other_stubs.h"
}


#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE GSM_RX_HANDLER
#include <boost/test/unit_test.hpp>
#include <string>
#include <iostream>

struct fixture {
	fixture() {
		//;
	}
};

BOOST_FIXTURE_TEST_CASE(check_for_extra_newlines_1, fixture) {
	std::string input = "\r\nNO CARRIER\r\nAT\r\nOK\r\n\r\nRING\r\n\r\nRING\r\n\r\nRING\r\nAT+CREG?\r\n+CREG: 0,1\r\n\r\nOK\r\n\r\nRING\r\n\r\nRING\r\n\r\nNO CARRIER\r\n";

	uint32_t result = gsm_sim800_check_for_extra_newlines(reinterpret_cast<uint8_t *>(const_cast<char *>(input.c_str())), input.length());

	BOOST_CHECK(result != 0);
}

BOOST_FIXTURE_TEST_CASE(look_for_ring_1, fixture) {
	std::string input = "\r\nRING\r\nAT+CREG?\r\n+CREG: 0,1\r\n\r\nOK\r\n\r\nRING\r\n\r\nRING\r\n\r\nNO CARRIER\r\n";

	uint16_t offset = 0;

	uint32_t result = gsm_sim800_check_for_extra_newlines(reinterpret_cast<uint8_t *>(const_cast<char *>(input.c_str())), input.length());

	std::string substr = input.substr(result & 0xFF);

	gsm_sim800_check_for_async_messages(reinterpret_cast<uint8_t *>(const_cast<char *>(substr.c_str())), substr.length(), &offset);

	BOOST_CHECK_EQUAL(offset, 6);
}

BOOST_FIXTURE_TEST_CASE(look_for_nocarrier_1, fixture) {
	std::string input = "\r\nAT\r\nNO CARRIER\r\nRING\r\n\r\nOK\r\n\r\nRING\r\n\r\nRING\r\n\r\nRING\r\nAT+CREG?\r\n+CREG: 0,1\r\n\r\nOK\r\n\r\nRING\r\n\r\nRING\r\n\r\nNO CARRIER\r\n";

	uint16_t offset = 0;

	uint32_t result = gsm_sim800_check_for_extra_newlines(reinterpret_cast<uint8_t *>(const_cast<char *>(input.c_str())), input.length());

	std::string substr = input.substr(result & 0xFF);

	gsm_sim800_check_for_async_messages(reinterpret_cast<uint8_t *>(const_cast<char *>(substr.c_str())), substr.length(), &offset);

	BOOST_CHECK_EQUAL(offset, 6);
}
