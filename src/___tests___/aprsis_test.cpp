
/*
 * aprsis_test.cpp
 *
 *  Created on: Jun 15, 2023
 *      Author: mateusz
 */

extern "C" {
#include "aprsis.h"
#include <___stubs___/stdperiph_stubs.h>
#include "rte_wx.h"
#include <___stubs___/other_stubs.h>
}

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE APRSIS
#include <boost/test/unit_test.hpp>
#include <string>
#include <iostream>
#include <fstream>

const char * wiadomosc = "dupa\0";

const char aklprz[6] = {0x41, 0x4b, 0x4c, 0x50, 0x52, 0x5a};
const char sp8ebc[6] = {0x53, 0x50, 0x38, 0x45, 0x42, 0x43};
const char wide[6] = {0x57, 0x49, 0x44, 0x45, 0x31, 0x0};
const char sr9wxs[6] = {0x53, 0x52, 0x39, 0x57, 0x58, 0x53};

static const char * aprsis_callsign_with_ssid = "SR9NSK-3";

extern uint8_t aprsis_logged;

struct MyConfig
{
  MyConfig() : test_log( "./test_reports/aprsis_test.log" )
  {
    boost::unit_test::unit_test_log.set_stream( test_log );
    boost::unit_test::unit_test_log.set_threshold_level(boost::unit_test::log_level::log_successful_tests);

  }
  ~MyConfig()
  {
    boost::unit_test::unit_test_log.set_stream( std::cout );
  }

  std::ofstream test_log;
};

BOOST_GLOBAL_FIXTURE (MyConfig);

BOOST_AUTO_TEST_CASE(igate_packet_one) {

	AX25Msg message = {0u};

	aprsis_logged = 1;

	memcpy(message.dst.call, aklprz, 6);
	message.dst.ssid = 0;

	memcpy(message.src.call, sp8ebc, 6);
	message.src.ssid = 7;

	message.rpt_cnt = 1;

	memcpy(message.rpt_lst[0].call, wide, 6);
	message.rpt_lst[0].ssid = 1;

	message.info = (uint8_t*)wiadomosc;
	message.len = 4;

	aprsis_igate_to_aprsis(&message, aprsis_callsign_with_ssid);

	const char * tx_buffer = aprsis_get_tx_buffer();

	std::string ouput_tx_buffer = std::string(tx_buffer);

	BOOST_TEST_MESSAGE(ouput_tx_buffer);

	BOOST_CHECK_EQUAL("SP8EBC-7>AKLPRZ,WIDE1-1,qAR,SR9NSK-3:dupa", ouput_tx_buffer);
}

BOOST_AUTO_TEST_CASE(igate_packet_two) {

	AX25Msg message = {0u};

	aprsis_logged = 1;

	memcpy(message.dst.call, aklprz, 6);
	message.dst.ssid = 0;

	memcpy(message.src.call, sp8ebc, 6);
	message.src.ssid = 0;

	message.rpt_cnt = 1;

	memcpy(message.rpt_lst[0].call, wide, 6);
	message.rpt_lst[0].ssid = 1;

	message.info = (uint8_t*)wiadomosc;
	message.len = 4;

	aprsis_igate_to_aprsis(&message, aprsis_callsign_with_ssid);

	const char * tx_buffer = aprsis_get_tx_buffer();

	std::string ouput_tx_buffer = std::string(tx_buffer);

	BOOST_TEST_MESSAGE(ouput_tx_buffer);

	BOOST_CHECK_EQUAL("SP8EBC>AKLPRZ,WIDE1-1,qAR,SR9NSK-3:dupa", ouput_tx_buffer);
}

BOOST_AUTO_TEST_CASE(igate_packet_three) {

	AX25Msg message = {0u};

	aprsis_logged = 1;

	memcpy(message.dst.call, aklprz, 6);
	message.dst.ssid = 0;

	memcpy(message.src.call, sp8ebc, 6);
	message.src.ssid = 0;

	message.rpt_cnt = 1;

	memcpy(message.rpt_lst[0].call, wide, 6);
	message.rpt_lst[0].ssid = 0x40;

	message.info = (uint8_t*)wiadomosc;
	message.len = 4;

	aprsis_igate_to_aprsis(&message, aprsis_callsign_with_ssid);

	const char * tx_buffer = aprsis_get_tx_buffer();

	std::string ouput_tx_buffer = std::string(tx_buffer);

	BOOST_TEST_MESSAGE(ouput_tx_buffer);

	BOOST_CHECK_EQUAL("SP8EBC>AKLPRZ,WIDE1*,qAR,SR9NSK-3:dupa", ouput_tx_buffer);
}

BOOST_AUTO_TEST_CASE(igate_packet_four) {

	AX25Msg message = {0u};

	aprsis_logged = 1;

	memcpy(message.dst.call, aklprz, 6);
	message.dst.ssid = 0;

	memcpy(message.src.call, sp8ebc, 6);
	message.src.ssid = 0;

	message.rpt_cnt = 1;

	memcpy(message.rpt_lst[0].call, sr9wxs, 6);
	message.rpt_lst[0].ssid = 0x41;

	message.info = (uint8_t*)wiadomosc;
	message.len = 4;

	aprsis_igate_to_aprsis(&message, aprsis_callsign_with_ssid);

	const char * tx_buffer = aprsis_get_tx_buffer();

	std::string ouput_tx_buffer = std::string(tx_buffer);

	BOOST_TEST_MESSAGE(ouput_tx_buffer);

	BOOST_CHECK_EQUAL("SP8EBC>AKLPRZ,SR9WXS-1*,qAR,SR9NSK-3:dupa", ouput_tx_buffer);
}

BOOST_AUTO_TEST_CASE(igate_packet_five) {

	AX25Msg message = {0u};

	aprsis_logged = 1;

	memcpy(message.dst.call, aklprz, 6);
	message.dst.ssid = 0;

	memcpy(message.src.call, sp8ebc, 6);
	message.src.ssid = 2;

	message.rpt_cnt = 1;

	memcpy(message.rpt_lst[0].call, sr9wxs, 6);
	message.rpt_lst[0].ssid = 0x41;

	message.info = (uint8_t*)wiadomosc;
	message.len = 4;

	aprsis_igate_to_aprsis(&message, aprsis_callsign_with_ssid);

	const char * tx_buffer = aprsis_get_tx_buffer();

	std::string ouput_tx_buffer = std::string(tx_buffer);

	BOOST_TEST_MESSAGE(ouput_tx_buffer);

	BOOST_CHECK_EQUAL("SP8EBC-2>AKLPRZ,SR9WXS-1*,qAR,SR9NSK-3:dupa", ouput_tx_buffer);
}

