/*
 * http_client_rx_callback_test.cpp
 *
 *  Created on: Mar 19, 2022
 *      Author: mateusz
 */


extern "C" {


#include "stdperiph_stubs.h"
#include "other_stubs.h"
#include "http_client/http_client.h"
#include "http_client/http_client_rx_callback.h"
}


#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE HTTP_CLIENT_RX_CBK
#include <boost/test/unit_test.hpp>
#include <string>
#include <iostream>

#define HEADER_BUFFER_LN 64

/**
 *	HTTP code returned by the latest query. It is zeroed after each successful call to async
 *	function. This indicate that a request is currently in progress. Negative values means some
 *	non HTTP error, like communication timeout or response longer than expected
 */
int16_t http_client_http_code = 0;

/**
 * Content lenght received from HTTP response headers or chunked encoding
 */
uint16_t http_client_content_lenght = 0;

/**
 * Temporary buffer for processing
 */
char http_client_header_buffer[HEADER_BUFFER_LN];

/**
 * Index used to walk through 'http_client_header_buffer'
 */
uint8_t http_client_header_index = 0;



/**
 *
 * HTTP/1.1 200
Content-Type: application/json;charset=UTF-8
Transfer-Encoding: chunked
Date: Sat, 19 Mar 2022 07:53:47 GMT
Keep-Alive: timeout=20
Connection: keep-alive

142
{"last_timestamp":1647676251,"number_of_measurements":20,"avg_temperature":-4.44444,"temperature_qf":"FULL","qnh":1035,"qnh_qf":"FULL","humidity":36,"humidity_qf":"NOT_AVALIABLE","direction":88,"average_speed":6.6,"gusts":8.36,"hour_gusts":9.24,"hour_max_average_speed":7.04,"hour_min_average_speed":4.84,"wind_qf":"FULL"}
0

 *
 *
 *
 */
const char * meteo_backend_response_one = 	"\x48\x54\x54\x50\x2f\x31\x2e\x31\x20\x32\x30\x30\x20\x0d\x0a\x43" \
											"\x6f\x6e\x74\x65\x6e\x74\x2d\x54\x79\x70\x65\x3a\x20\x61\x70\x70" \
											"\x6c\x69\x63\x61\x74\x69\x6f\x6e\x2f\x6a\x73\x6f\x6e\x3b\x63\x68" \
											"\x61\x72\x73\x65\x74\x3d\x55\x54\x46\x2d\x38\x0d\x0a\x54\x72\x61" \
											"\x6e\x73\x66\x65\x72\x2d\x45\x6e\x63\x6f\x64\x69\x6e\x67\x3a\x20" \
											"\x63\x68\x75\x6e\x6b\x65\x64\x0d\x0a\x44\x61\x74\x65\x3a\x20\x53" \
											"\x61\x74\x2c\x20\x31\x39\x20\x4d\x61\x72\x20\x32\x30\x32\x32\x20" \
											"\x30\x37\x3a\x35\x33\x3a\x34\x37\x20\x47\x4d\x54\x0d\x0a\x4b\x65" \
											"\x65\x70\x2d\x41\x6c\x69\x76\x65\x3a\x20\x74\x69\x6d\x65\x6f\x75" \
											"\x74\x3d\x32\x30\x0d\x0a\x43\x6f\x6e\x6e\x65\x63\x74\x69\x6f\x6e" \
											"\x3a\x20\x6b\x65\x65\x70\x2d\x61\x6c\x69\x76\x65\x0d\x0a\x0d\x0a" \
											"\x31\x34\x32\x0d\x0a\x7b\x22\x6c\x61\x73\x74\x5f\x74\x69\x6d\x65" \
											"\x73\x74\x61\x6d\x70\x22\x3a\x31\x36\x34\x37\x36\x37\x36\x32\x35" \
											"\x31\x2c\x22\x6e\x75\x6d\x62\x65\x72\x5f\x6f\x66\x5f\x6d\x65\x61" \
											"\x73\x75\x72\x65\x6d\x65\x6e\x74\x73\x22\x3a\x32\x30\x2c\x22\x61" \
											"\x76\x67\x5f\x74\x65\x6d\x70\x65\x72\x61\x74\x75\x72\x65\x22\x3a" \
											"\x2d\x34\x2e\x34\x34\x34\x34\x34\x2c\x22\x74\x65\x6d\x70\x65\x72" \
											"\x61\x74\x75\x72\x65\x5f\x71\x66\x22\x3a\x22\x46\x55\x4c\x4c\x22" \
											"\x2c\x22\x71\x6e\x68\x22\x3a\x31\x30\x33\x35\x2c\x22\x71\x6e\x68" \
											"\x5f\x71\x66\x22\x3a\x22\x46\x55\x4c\x4c\x22\x2c\x22\x68\x75\x6d" \
											"\x69\x64\x69\x74\x79\x22\x3a\x33\x36\x2c\x22\x68\x75\x6d\x69\x64" \
											"\x69\x74\x79\x5f\x71\x66\x22\x3a\x22\x4e\x4f\x54\x5f\x41\x56\x41" \
											"\x4c\x49\x41\x42\x4c\x45\x22\x2c\x22\x64\x69\x72\x65\x63\x74\x69" \
											"\x6f\x6e\x22\x3a\x38\x38\x2c\x22\x61\x76\x65\x72\x61\x67\x65\x5f" \
											"\x73\x70\x65\x65\x64\x22\x3a\x36\x2e\x36\x2c\x22\x67\x75\x73\x74" \
											"\x73\x22\x3a\x38\x2e\x33\x36\x2c\x22\x68\x6f\x75\x72\x5f\x67\x75" \
											"\x73\x74\x73\x22\x3a\x39\x2e\x32\x34\x2c\x22\x68\x6f\x75\x72\x5f" \
											"\x6d\x61\x78\x5f\x61\x76\x65\x72\x61\x67\x65\x5f\x73\x70\x65\x65" \
											"\x64\x22\x3a\x37\x2e\x30\x34\x2c\x22\x68\x6f\x75\x72\x5f\x6d\x69" \
											"\x6e\x5f\x61\x76\x65\x72\x61\x67\x65\x5f\x73\x70\x65\x65\x64\x22" \
											"\x3a\x34\x2e\x38\x34\x2c\x22\x77\x69\x6e\x64\x5f\x71\x66\x22\x3a" \
											"\x22\x46\x55\x4c\x4c\x22\x7d\x0d\x0a\x30\x0d\x0a\x0d\x0a\0\0\0\0";

struct fixture {
	fixture() {
		//;
	}
};

BOOST_FIXTURE_TEST_CASE(test_one, fixture) {

	int len = strlen(meteo_backend_response_one);

	uint8_t output = 0;

	for (int i = 0; i < len; i++) {
		output = http_client_rx_done_callback(*(meteo_backend_response_one + i), reinterpret_cast<const uint8_t*>(meteo_backend_response_one), i);
	}

	BOOST_CHECK_EQUAL(200, http_client_http_code);
	BOOST_CHECK_EQUAL(322, http_client_content_lenght);

}