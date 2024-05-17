
/*
 * kiss_diagnostics_test.cpp
 *
 *  Created on: May 6, 2024
 *      Author: mateusz
 */

extern "C" {
#include <___stubs___/other_stubs.h>
#include <___stubs___/stdperiph_stubs.h>
#include <kiss_communication/kiss_communication_aprsmsg.h>
#include "message.h"

}


#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE KISS_DIAGNOSTIC
#include <boost/test/unit_test.hpp>
#include <string>
#include <iostream>
#include <fstream>

#define DECODED_BINARY_LN		128

uint8_t decoded_binary[DECODED_BINARY_LN];

struct MyConfig
{
  MyConfig() : test_log( "./test_reports/kiss_diagnostic_test.log" )
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

BOOST_AUTO_TEST_CASE(decode_hexstring_first) {

	uint8_t testhexstring[] = "HSAABBCCDDEEFF0011223344\0\0";
	const uint16_t hexstring_ln = strlen((const char*)testhexstring);

	memset(decoded_binary, 0x00, DECODED_BINARY_LN);

	const uint8_t expected[] = {0xAA, 0xBB, 0xCC, 0xDD, 0xEE, 0xFF, 0x00, 0x11, 0x22, 0x33, 0x44};

	// uint8_t kiss_communication_aprsmsg_decode_hexstring(uint8_t * message_payload, uint16_t message_payload_ln, uint8_t * output_binary_buffer, uint16_t output_ln);

	const uint8_t result = kiss_communication_aprsmsg_decode_hexstring(testhexstring, hexstring_ln, decoded_binary, DECODED_BINARY_LN);

	BOOST_CHECK_EQUAL(result, 11);
	BOOST_CHECK_EQUAL_COLLECTIONS(decoded_binary, decoded_binary + 10, expected, expected + 10);
	BOOST_CHECK_EQUAL(decoded_binary[11], 0x00);
}

BOOST_AUTO_TEST_CASE(decode_hexstring_corrupted) {

	uint8_t testhexstring[] = "HSAABBCCDDEEFF00xx223344\0\0";
	const uint16_t hexstring_ln = strlen((const char*)testhexstring);

	memset(decoded_binary, 0x00, DECODED_BINARY_LN);

	const uint8_t expected[] = {0xAA, 0xBB, 0xCC, 0xDD, 0xEE, 0xFF, 0x00};

	// uint8_t kiss_communication_aprsmsg_decode_hexstring(uint8_t * message_payload, uint16_t message_payload_ln, uint8_t * output_binary_buffer, uint16_t output_ln);

	const uint8_t result = kiss_communication_aprsmsg_decode_hexstring(testhexstring, hexstring_ln, decoded_binary, DECODED_BINARY_LN);

	BOOST_CHECK_EQUAL(result, 7);
	BOOST_CHECK_EQUAL_COLLECTIONS(decoded_binary, decoded_binary + 6, expected, expected + 6);
	BOOST_CHECK_EQUAL(decoded_binary[7], 0x00);
}

BOOST_AUTO_TEST_CASE(decode_hexstring_text) {

	uint8_t testhexstring[] = "HS4A4B4C4D4E4F5051\0\0";
	const uint16_t hexstring_ln = strlen((const char*)testhexstring);

	memset(decoded_binary, 0x00, DECODED_BINARY_LN);

	const uint8_t expected[] = "JKLMNOPQ";

	// uint8_t kiss_communication_aprsmsg_decode_hexstring(uint8_t * message_payload, uint16_t message_payload_ln, uint8_t * output_binary_buffer, uint16_t output_ln);

	const uint8_t result = kiss_communication_aprsmsg_decode_hexstring(testhexstring, hexstring_ln, decoded_binary, DECODED_BINARY_LN);

	BOOST_CHECK_EQUAL(result, 8);
	BOOST_CHECK_EQUAL_COLLECTIONS(decoded_binary, decoded_binary + 7, expected, expected + 7);
	BOOST_CHECK_EQUAL(decoded_binary[8], 0x00);
}

BOOST_AUTO_TEST_CASE(decode_hexstring_missing_prefix) {

	uint8_t testhexstring[] = "4A4B4C4D4E4F5051\0\0";
	const uint16_t hexstring_ln = strlen((const char*)testhexstring);

	memset(decoded_binary, 0x00, DECODED_BINARY_LN);

	const uint8_t expected[] = "JKLMNOPQ";

	// uint8_t kiss_communication_aprsmsg_decode_hexstring(uint8_t * message_payload, uint16_t message_payload_ln, uint8_t * output_binary_buffer, uint16_t output_ln);

	const uint8_t result = kiss_communication_aprsmsg_decode_hexstring(testhexstring, hexstring_ln, decoded_binary, DECODED_BINARY_LN);

	BOOST_CHECK_EQUAL(result, 0);
}

BOOST_AUTO_TEST_CASE(encode_binary_1) {

	uint8_t input[] 	= {0xAA, 0xBB, 0xCC, 0xDD, 0xEE, 0xFF, 0x00, 0x11, 0x22, 0x33, 0x44};
	uint8_t expected[] 	= "HSAABBCCDDEEFF0011223344\0";
	const size_t expected_ln = strlen((const char*)expected);
	const size_t expected_end = expected_ln - 1;

	memset(decoded_binary, 0x00, DECODED_BINARY_LN);

	const uint8_t result = kiss_communication_aprsmsg_encode_hexstring(input, 11, decoded_binary, DECODED_BINARY_LN);

	BOOST_CHECK_EQUAL(result, expected_ln);
	BOOST_CHECK_EQUAL_COLLECTIONS(expected, expected + expected_end, decoded_binary, decoded_binary + expected_end);
}

BOOST_AUTO_TEST_CASE(encode_binary_2) {

	uint8_t input[] 	= {0x12, 0x13, 0x14, 0x15, 0x16, 0x17, 0x18, 0x19, 0x20, 0x21, 0x44};
	uint8_t expected[] 	= "HS1213141516171819202144\0";
	const size_t expected_ln = strlen((const char*)expected);
	const size_t expected_end = expected_ln - 1;

	memset(decoded_binary, 0x00, DECODED_BINARY_LN);

	const uint8_t result = kiss_communication_aprsmsg_encode_hexstring(input, 11, decoded_binary, DECODED_BINARY_LN);

	BOOST_CHECK_EQUAL(result, expected_ln);
	BOOST_CHECK_EQUAL_COLLECTIONS(expected, expected + expected_end, decoded_binary, decoded_binary + expected_end);
}

BOOST_AUTO_TEST_CASE(encode_binary_outputbuff_to_small) {

	uint8_t input[] 	= {0x12, 0x13, 0x14, 0x15, 0x16, 0x17, 0x18, 0x19, 0x20, 0x21, 0x44};
	uint8_t expected[] 	= "HS1213141516171819202144\0";
	const size_t expected_ln = strlen((const char*)expected);
	const size_t expected_end = expected_ln - 1;

	memset(decoded_binary, 0x00, DECODED_BINARY_LN);

	const uint8_t result = kiss_communication_aprsmsg_encode_hexstring(input, 11, decoded_binary, expected_ln - 4);

	BOOST_CHECK_EQUAL(result, 0);
	BOOST_CHECK_EQUAL(decoded_binary[0], 0);
	BOOST_CHECK_EQUAL(decoded_binary[1], 0);

}

BOOST_AUTO_TEST_CASE(check_type_hs) {
	uint8_t testhexstring[] = "HS4A4B4C4D4E4F5051\0\0";

	const kiss_communication_aprsmsg_transport_t current = kiss_communication_aprsmsg_check_type(testhexstring, strlen((const char*)testhexstring));

	BOOST_CHECK_EQUAL(current, APRSMSG_TRANSPORT_HEXSTRING);
}

BOOST_AUTO_TEST_CASE(check_type_hs_missingprefix) {
	uint8_t testhexstring[] = "4A4B4C4D4E4F5051\0\0";

	const kiss_communication_aprsmsg_transport_t current = kiss_communication_aprsmsg_check_type(testhexstring, strlen((const char*)testhexstring));

	BOOST_CHECK_EQUAL(current, APRSMSG_TRANSPORT_NOT_KISS);
}

BOOST_AUTO_TEST_CASE(check_type_hs_random) {
	uint8_t testhexstring[] = "    random deadBEEAF\0\0";

	const kiss_communication_aprsmsg_transport_t current = kiss_communication_aprsmsg_check_type(testhexstring, strlen((const char*)testhexstring));

	BOOST_CHECK_EQUAL(current, APRSMSG_TRANSPORT_NOT_KISS);
}

BOOST_AUTO_TEST_CASE(check_type_hs_too_long) {
	uint8_t testhexstring[] = "    random deadBEEAFdeadBEEAFdeadBEEAFdeadBEEAFdeadBEEAFdeadBEEAFdeadBEEAFdeadBEEAFdeadBEEAFdeadBEEAFdeadBEEAFdeadBEEAF\0\0";
	const size_t ln = strlen((const char*)testhexstring);

	const kiss_communication_aprsmsg_transport_t current = kiss_communication_aprsmsg_check_type(testhexstring, ln);

	BOOST_CHECK_EQUAL(current, APRSMSG_TRANSPORT_UNINITIALIZED);
}

