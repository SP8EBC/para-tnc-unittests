/*
 * davis_vantage_test.cpp
 *
 *  Created on: 13.08.2020
 *      Author: mateusz
 */

extern "C" {
#include "davis_vantage/davis_parsers.h"
}

#include <cstdint>

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE DAVIS_VANTAGE
#include <boost/test/unit_test.hpp>

const uint8_t crc_data_1[] = {0xC6, 0xCE, 0xA2, 0x03, 0xE2, 0xB4};

struct fixture {
	fixture() {
		;
	}
};

BOOST_FIXTURE_TEST_CASE(crc_1, fixture) {
	int32_t crc = davis_parsers_check_crc(const_cast<uint8_t*>(crc_data_1), sizeof(crc_data_1));
}
