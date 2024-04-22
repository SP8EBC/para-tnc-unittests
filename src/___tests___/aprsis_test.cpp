
/*
 * aprsis_test.cpp
 *
 *  Created on: Jun 15, 2023
 *      Author: mateusz
 */

extern "C" {
#include <___stubs___/other_stubs.h>
#include <___stubs___/stdperiph_stubs.h>
#include "aprsis.h"
#include "rte_wx.h"
#include "message.h"

extern int aprsis_check_is_message(const uint8_t * const message, const uint16_t message_ln);
extern void aprsis_receive_callback(srl_context_t* srl_context);
}

#include "boost/lexical_cast.hpp"

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

// trim from end (in place)
inline void rtrim(std::string &s) {
    s.erase(std::find_if(s.rbegin(), s.rend(), [](unsigned char ch) {
        return !std::isspace(ch);
    }).base(), s.end());
}

inline bool has_newline(std::string &s) {

	auto iterator = std::find_if(s.begin(), s.end(), [](unsigned char ch) {
	        return (ch == '\r') ? true : false;
	    });

	std::string::const_iterator e = s.end();

	if (iterator == e) {
		return false;
	}

	if (iterator == (e - 2)) {
		return true;
	}
	else {
		return false;
	}

}

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
	BOOST_CHECK(has_newline(ouput_tx_buffer));
	::rtrim(ouput_tx_buffer);

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
	BOOST_CHECK(has_newline(ouput_tx_buffer));
	::rtrim(ouput_tx_buffer);

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
	BOOST_CHECK(has_newline(ouput_tx_buffer));
	::rtrim(ouput_tx_buffer);

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
	BOOST_CHECK(has_newline(ouput_tx_buffer));
	::rtrim(ouput_tx_buffer);

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
	BOOST_CHECK(has_newline(ouput_tx_buffer));
	::rtrim(ouput_tx_buffer);

	BOOST_TEST_MESSAGE(ouput_tx_buffer);

	BOOST_CHECK_EQUAL("SP8EBC-2>AKLPRZ,SR9WXS-1*,qAR,SR9NSK-3:dupa", ouput_tx_buffer);
}

BOOST_AUTO_TEST_CASE(is_message_one) {

	const char * message = "SP8EBC>APX216,TCPIP*,qAC,NINTH::SR9WXZ   :tedt{0s}\r\n";

	const int result = aprsis_check_is_message((const uint8_t*)message, strlen(message));

	BOOST_CHECK_EQUAL(result, 32);
}

// SP3LYR>APRS,WIDE2-2::AB9FX    :test{1
BOOST_AUTO_TEST_CASE(is_message_two) {
	const char * message = "SP3LYR>APRS,WIDE2-2::AB9FX    :test{1\r\n";

	const int result = aprsis_check_is_message((const uint8_t*)message, strlen(message));

	BOOST_CHECK_EQUAL(result, 21);
}

BOOST_AUTO_TEST_CASE(no_message) {
	const char * message = "dupajasia123";

	const int result = aprsis_check_is_message((const uint8_t*)message, strlen(message));

	BOOST_CHECK_EQUAL(result, 0);
}

BOOST_AUTO_TEST_CASE(decode_message_one) {
	const std::string recipient{"SR9WXZ"};
	const std::string message_content{"tedt"};
	const char * message = "SP8EBC>APX216,TCPIP*,qAC,NINTH::SR9WXZ   :tedt{0s}\r\n";
	message_t decoded;
	BOOST_TEST_MESSAGE(message);

	const uint8_t result = message_decode_from_aprsis((const uint8_t*)message, strlen(message), 0, MESSAGE_SOURCE_APRSIS, &decoded);
	BOOST_CHECK_EQUAL(result, 0);

	std::string decoded_recipient{decoded.to.call, 6};
	BOOST_TEST_MESSAGE(decoded_recipient);
	BOOST_TEST_MESSAGE(boost::lexical_cast<std::string>((int)decoded.to.ssid));

	BOOST_CHECK_EQUAL(decoded_recipient, recipient);

	std::string decoded_message_content{(char*)decoded.content};
	BOOST_CHECK_EQUAL(message_content, decoded_message_content);

	BOOST_CHECK_EQUAL(0, decoded.number);
}

BOOST_AUTO_TEST_CASE(decode_message_with_ssid) {
	const std::string sender{"SP8EBC"};
	const std::string recipient{"SR9WXZ"};
	const std::string message_content{"tedt"};
	const char * message = "SP8EBC>APX216,TCPIP*,qAC,NINTH::SR9WXZ-9 :tedt{0s}\r\n";
	message_t decoded;
	BOOST_TEST_MESSAGE(message);

	const uint8_t result = message_decode_from_aprsis((const uint8_t*)message, strlen(message), 0, MESSAGE_SOURCE_APRSIS, &decoded);
	BOOST_CHECK_EQUAL(result, 0);

	std::string decoded_sender{decoded.from.call, 6};
	BOOST_TEST_MESSAGE(decoded_sender);
	BOOST_TEST_MESSAGE(boost::lexical_cast<std::string>((int)decoded.from.ssid));

	BOOST_CHECK_EQUAL(decoded_sender, sender);
	BOOST_CHECK_EQUAL(decoded.from.ssid, 0);

	std::string decoded_recipient{decoded.to.call, 6};
	BOOST_TEST_MESSAGE(decoded_recipient);
	BOOST_TEST_MESSAGE(boost::lexical_cast<std::string>((int)decoded.to.ssid));

	BOOST_CHECK_EQUAL(decoded_recipient, recipient);
	BOOST_CHECK_EQUAL(decoded.to.ssid, 9);

	std::string decoded_message_content{(char*)decoded.content};
	BOOST_CHECK_EQUAL(message_content, decoded_message_content);

	BOOST_CHECK_EQUAL(0, decoded.number);
}

BOOST_AUTO_TEST_CASE(decode_message_with_twodigit_ssid) {
	const std::string recipient{"SR9WXZ"};
	const std::string message_content{"tedt"};
	const char * message = "SP8EBC>APX216,TCPIP*,qAC,NINTH::SR9WXZ-12:tedt{0s}\r\n";
	message_t decoded;
	BOOST_TEST_MESSAGE(message);

	const uint8_t result = message_decode_from_aprsis((const uint8_t*)message, strlen(message), 0, MESSAGE_SOURCE_APRSIS, &decoded);
	BOOST_CHECK_EQUAL(result, 0);

	std::string decoded_recipient{decoded.to.call, 6};
	BOOST_TEST_MESSAGE(decoded_recipient);
	BOOST_TEST_MESSAGE(boost::lexical_cast<std::string>((int)decoded.to.ssid));

	BOOST_CHECK_EQUAL(decoded_recipient, recipient);
	BOOST_CHECK_EQUAL(decoded.to.ssid, 12);

	std::string decoded_message_content{(char*)decoded.content};
	BOOST_CHECK_EQUAL(message_content, decoded_message_content);

	BOOST_CHECK_EQUAL(0, decoded.number);
}

BOOST_AUTO_TEST_CASE(decode_message_with_sender_and_recipient_ssid) {
	const std::string sender{"SP8EBC"};
	const std::string recipient{"SR9WXZ"};
	const std::string message_content{"rgagagtest1234556785465AH   "};
	const char * message = "SP8EBC-11>APX216,TCPIP*,qAC,NINTH::SR9WXZ-9 :rgagagtest1234556785465AH   {0s}\r\n";
	message_t decoded;
	BOOST_TEST_MESSAGE(message);

	const uint8_t result = message_decode_from_aprsis((const uint8_t*)message, strlen(message), 0, MESSAGE_SOURCE_APRSIS, &decoded);
	BOOST_CHECK_EQUAL(result, 0);

	std::string decoded_sender{decoded.from.call, 6};
	BOOST_TEST_MESSAGE(decoded_sender);
	BOOST_TEST_MESSAGE(boost::lexical_cast<std::string>((int)decoded.from.ssid));

	BOOST_CHECK_EQUAL(decoded_sender, sender);
	BOOST_CHECK_EQUAL(decoded.from.ssid, 11);

	std::string decoded_recipient{decoded.to.call, 6};
	BOOST_TEST_MESSAGE(decoded_recipient);
	BOOST_TEST_MESSAGE(boost::lexical_cast<std::string>((int)decoded.to.ssid));

	BOOST_CHECK_EQUAL(decoded_recipient, recipient);
	BOOST_CHECK_EQUAL(decoded.to.ssid, 9);

	std::string decoded_message_content{(char*)decoded.content};
	BOOST_CHECK_EQUAL(message_content, decoded_message_content);

	BOOST_CHECK_EQUAL(0, decoded.number);
}


BOOST_AUTO_TEST_CASE(decode_message_with_ssid_nonzero_counter) {
	const std::string recipient{"SR9WXZ"};
	const std::string message_content{"tedt"};
	const char * message = "SP8EBC>APX216,TCPIP*,qAC,NINTH::SR9WXZ-9 :tedt{4s}\r\n";
	message_t decoded;
	BOOST_TEST_MESSAGE(message);

	const uint8_t result = message_decode_from_aprsis((const uint8_t*)message, strlen(message), 0, MESSAGE_SOURCE_APRSIS, &decoded);
	BOOST_CHECK_EQUAL(result, 0);

	std::string decoded_recipient{decoded.to.call, 6};
	BOOST_TEST_MESSAGE(decoded_recipient);
	BOOST_TEST_MESSAGE(boost::lexical_cast<std::string>((int)decoded.to.ssid));

	BOOST_CHECK_EQUAL(decoded_recipient, recipient);
	BOOST_CHECK_EQUAL(decoded.to.ssid, 9);

	std::string decoded_message_content{(char*)decoded.content};
	BOOST_CHECK_EQUAL(message_content, decoded_message_content);

	BOOST_CHECK_EQUAL(4, decoded.number);
}

BOOST_AUTO_TEST_CASE(decode_message_with_ssid_twodigits_counter) {
	const std::string recipient{"SR9WXZ"};
	const std::string message_content{"tedt"};
	const char * message = "SP8EBC>APX216,TCPIP*,qAC,NINTH::SR9WXZ-9 :tedt{14s}\r\n";
	message_t decoded;
	BOOST_TEST_MESSAGE(message);

	const uint8_t result = message_decode_from_aprsis((const uint8_t*)message, strlen(message), 0, MESSAGE_SOURCE_APRSIS, &decoded);
	BOOST_CHECK_EQUAL(result, 0);

	std::string decoded_recipient{decoded.to.call, 6};
	BOOST_TEST_MESSAGE(decoded_recipient);
	BOOST_TEST_MESSAGE(boost::lexical_cast<std::string>((int)decoded.to.ssid));

	BOOST_CHECK_EQUAL(decoded_recipient, recipient);
	BOOST_CHECK_EQUAL(decoded.to.ssid, 9);

	std::string decoded_message_content{(char*)decoded.content};
	BOOST_CHECK_EQUAL(message_content, decoded_message_content);

	BOOST_CHECK_EQUAL(14, decoded.number);
}

BOOST_AUTO_TEST_CASE(decode_message_with_ssid_twodigits_counter_provided_content_position) {
	const std::string recipient{"SR9WXZ"};
	const std::string message_content{"tedt"};
	const char * message = "SP8EBC>APX216,TCPIP*,qAC,NINTH::SR9WXZ-9 :tedt{14s}\r\n";
	message_t decoded;
	BOOST_TEST_MESSAGE(message);

	const uint8_t result = message_decode_from_aprsis((const uint8_t*)message, strlen(message), 32, MESSAGE_SOURCE_APRSIS, &decoded);
	BOOST_CHECK_EQUAL(result, 0);

	std::string decoded_recipient{decoded.to.call, 6};
	BOOST_TEST_MESSAGE(decoded_recipient);
	BOOST_TEST_MESSAGE(boost::lexical_cast<std::string>((int)decoded.to.ssid));

	BOOST_CHECK_EQUAL(decoded_recipient, recipient);
	BOOST_CHECK_EQUAL(decoded.to.ssid, 9);

	std::string decoded_message_content{(char*)decoded.content};
	BOOST_CHECK_EQUAL(message_content, decoded_message_content);

	BOOST_CHECK_EQUAL(14, decoded.number);
}

BOOST_AUTO_TEST_CASE(decode_message_wrong_content_position) {
	const std::string recipient{"SR9WXZ"};
	const std::string message_content{"tedt"};
	const char * message = "SP8EBC>APX216,TCPIP*,qAC,NINTH::SR9WXZ-9 :tedt{14s}\r\n";
	message_t decoded;
	BOOST_TEST_MESSAGE(message);

	const uint8_t result = message_decode_from_aprsis((const uint8_t*)message, strlen(message), 44, MESSAGE_SOURCE_APRSIS, &decoded);
	BOOST_CHECK_NE(result, 0);
}

BOOST_AUTO_TEST_CASE(decode_message_wrong_content_position_to_small) {
	const std::string recipient{"SR9WXZ"};
	const std::string message_content{"tedt"};
	const char * message = "SP8EBC>APX216,TCPIP*,qAC,NINTH::SR9WXZ-9 :tedt{14s}\r\n";
	message_t decoded;
	BOOST_TEST_MESSAGE(message);

	const uint8_t result = message_decode_from_aprsis((const uint8_t*)message, strlen(message), 4, MESSAGE_SOURCE_APRSIS, &decoded);
	BOOST_CHECK_NE(result, 0);
}

BOOST_AUTO_TEST_CASE(decode_message_malformed_structure) {
	const std::string recipient{"SR9WXZ"};
	const std::string message_content{"tedt"};
	const char * message = "SP8EBC>APX216,TCPIP*,qAC,NINTH::SR9WXZ-9  :tedt{14s}\r\n";
	message_t decoded;
	BOOST_TEST_MESSAGE(message);

	const uint8_t result = message_decode_from_aprsis((const uint8_t*)message, strlen(message), 0, MESSAGE_SOURCE_APRSIS, &decoded);
	BOOST_CHECK_NE(result, 0);
}

BOOST_AUTO_TEST_CASE(decode_message_from_radio_one) {
	const std::string recipient{"SR9WXZ"};
	const std::string message_content{"tedt"};
	const char * message = ":SR9WXZ-9 :tedt{14s}\r\n";
	message_t decoded;
	BOOST_TEST_MESSAGE(message);

	const uint8_t result = message_decode_from_aprsis((const uint8_t*)message, strlen(message), 0, MESSAGE_SOURCE_RADIO, &decoded);
	BOOST_CHECK_EQUAL(result, 0);

	std::string decoded_recipient{decoded.to.call, 6};
	BOOST_TEST_MESSAGE(decoded_recipient);
	BOOST_TEST_MESSAGE(boost::lexical_cast<std::string>((int)decoded.to.ssid));

	BOOST_CHECK_EQUAL(decoded_recipient, recipient);
	BOOST_CHECK_EQUAL(decoded.to.ssid, 9);

	std::string decoded_message_content{(char*)decoded.content};
	BOOST_CHECK_EQUAL(message_content, decoded_message_content);

	BOOST_CHECK_EQUAL(14, decoded.number);
}

BOOST_AUTO_TEST_CASE(decode_message_from_radio_twodigit_ssid) {
	const std::string recipient{"SR9WXZ"};
	const std::string message_content{"tedt"};
	const char * message = ":SR9WXZ-13:tedt{14s}\r\n";
	message_t decoded;
	BOOST_TEST_MESSAGE(message);

	const uint8_t result = message_decode_from_aprsis((const uint8_t*)message, strlen(message), 0, MESSAGE_SOURCE_RADIO, &decoded);
	BOOST_CHECK_EQUAL(result, 0);

	std::string decoded_recipient{decoded.to.call, 6};
	BOOST_TEST_MESSAGE(decoded_recipient);
	BOOST_TEST_MESSAGE(boost::lexical_cast<std::string>((int)decoded.to.ssid));

	BOOST_CHECK_EQUAL(decoded_recipient, recipient);
	BOOST_CHECK_EQUAL(decoded.to.ssid, 13);

	std::string decoded_message_content{(char*)decoded.content};
	BOOST_CHECK_EQUAL(message_content, decoded_message_content);

	BOOST_CHECK_EQUAL(14, decoded.number);
}

BOOST_AUTO_TEST_CASE(decode_message_from_radio_twodigit_ssid_whitespaces) {
	const std::string recipient{"SR9WXZ"};
	const std::string message_content{"tedt"};
	const char * message = "    :SR9WXZ-13:tedt{14s}\r\n";
	message_t decoded;
	BOOST_TEST_MESSAGE(message);

	const uint8_t result = message_decode_from_aprsis((const uint8_t*)message, strlen(message), 0, MESSAGE_SOURCE_RADIO, &decoded);
	BOOST_CHECK_EQUAL(result, 0);

	std::string decoded_recipient{decoded.to.call, 6};
	BOOST_TEST_MESSAGE(decoded_recipient);
	BOOST_TEST_MESSAGE(boost::lexical_cast<std::string>((int)decoded.to.ssid));

	BOOST_CHECK_EQUAL(decoded_recipient, recipient);
	BOOST_CHECK_EQUAL(decoded.to.ssid, 13);

	std::string decoded_message_content{(char*)decoded.content};
	BOOST_CHECK_EQUAL(message_content, decoded_message_content);

	BOOST_CHECK_EQUAL(14, decoded.number);
}

BOOST_AUTO_TEST_CASE(decode_message_from_radio_random_garbage) {
	const char * message = " dupa dupa dupa cycki";
	message_t decoded;
	BOOST_TEST_MESSAGE(message);

	const uint8_t result = message_decode_from_aprsis((const uint8_t*)message, strlen(message), 0, MESSAGE_SOURCE_RADIO, &decoded);
	BOOST_CHECK_NE(result, 0);		// check not equal
}

BOOST_AUTO_TEST_CASE(decode_message_from_aprsis_random_garbage) {
	const uint8_t message[] = {0xDEu, 0xADu, 0xBEu, 0xEFu, 0xBAu, 0xDCu, 0x0Fu, 0xFE,
			0xDEu, 0xADu, 0xBEu, 0xEFu, 0xBAu, 0xDCu, 0x0Fu, 0xFE,
			0xDEu, 0xADu, 0xBEu, 0xEFu, 0xBAu, 0xDCu, 0x0Fu, 0xFE,
			0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u};
	message_t decoded;

	const uint8_t result = message_decode_from_aprsis((const uint8_t*)message, 32, 0, MESSAGE_SOURCE_RADIO, &decoded);
	BOOST_CHECK_NE(result, 0);		// check not equal
}

BOOST_AUTO_TEST_CASE(message_for_me) {
	config_data_basic_t config;

	config.ssid = 7;
	strncpy(config.callsign, "SP8EBC\0", 7);

	message_t message;
	message.to.ssid = 7;
	memcpy(message.to.call, "SP8EBC", 6);

	BOOST_CHECK_EQUAL(0, message_is_for_me(&config, &message));
}

BOOST_AUTO_TEST_CASE(message_for_me_second) {
	config_data_basic_t config;

	config.ssid = 7;
	strncpy(config.callsign, "SR0L\0", 7);

	message_t message;
	message.to.ssid = 7;
	memcpy(message.to.call, "SR0L\0", 6);

	BOOST_CHECK_EQUAL(0, message_is_for_me(&config, &message));
}

BOOST_AUTO_TEST_CASE(message_not_for_me) {
	config_data_basic_t config;

	config.ssid = 7;
	strncpy(config.callsign, "SR0L\0", 7);

	message_t message;
	message.to.ssid = 7;
	memcpy(message.to.call, "SR9WXM", 6);

	BOOST_CHECK_EQUAL(1, message_is_for_me(&config, &message));
}

BOOST_AUTO_TEST_CASE(create_ack_aprsis_theirs_ssid) {

	message_source_t source = MESSAGE_SOURCE_APRSIS;
	message_t message;
	char buffer[128];

	message.number = 9;
	memcpy(message.to.call, "SR9WXZ", 6);
	message.to.ssid = 1;
	memcpy(message.from.call, "SP8EBC", 6);
	message.from.ssid = 0;

	message_create_ack_for((uint8_t*) buffer, 128, &message, source);
	BOOST_TEST_MESSAGE(buffer);

	std::string ack{buffer};
	BOOST_CHECK_EQUAL(ack, "SR9WXZ-1>AKLPRZ::SP8EBC   :ack9");
}

BOOST_AUTO_TEST_CASE(create_ack_aprsis_theirs_no_ssid) {

	message_source_t source = MESSAGE_SOURCE_APRSIS;
	message_t message;
	char buffer[128];

	message.number = 9;
	memcpy(message.to.call, "SR9WXZ", 6);
	message.to.ssid = 0;
	memcpy(message.from.call, "SP8EBC", 6);
	message.from.ssid = 0;

	message_create_ack_for((uint8_t*) buffer, 128, &message, source);
	BOOST_TEST_MESSAGE(buffer);

	std::string ack{buffer};
	BOOST_CHECK_EQUAL(ack, "SR9WXZ>AKLPRZ::SP8EBC   :ack9");
}

BOOST_AUTO_TEST_CASE(create_ack_aprsis_mine_ssid) {

	message_source_t source = MESSAGE_SOURCE_APRSIS;
	message_t message;
	char buffer[128];

	message.number = 9;
	memcpy(message.to.call, "SR9WXZ", 6);
	message.to.ssid = 0;
	memcpy(message.from.call, "SP8EBC", 6);
	message.from.ssid = 11;

	message_create_ack_for((uint8_t*) buffer, 128, &message, source);
	BOOST_TEST_MESSAGE(buffer);

	std::string ack{buffer};
	BOOST_CHECK_EQUAL(ack, "SR9WXZ>AKLPRZ::SP8EBC-11:ack9");
}
