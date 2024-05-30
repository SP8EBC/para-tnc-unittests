/*
 * nvm_tests.cpp
 *
 *  Created on: May 30, 2024
 *      Author: mateusz
 */

extern "C" {
#include <___stubs___/other_stubs.h>
#include <___stubs___/stdperiph_stubs.h>
#include "nvm.h"
}

#include "memory_map_stubs.h"
#include "boost/lexical_cast.hpp"

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE NVM
#include <boost/test/unit_test.hpp>
#include <string>
#include <cstring>
#include <iostream>
#include <fstream>

static event_log_t EventLogTimesyncFactory(uint32_t time, uint32_t date) {

	event_log_t out;
	memset(&out, 0x00, sizeof(event_log_t));

	out.lparam = date;
	out.lparam2 = time;

	out.event_id = EVENT_TIMESYNC;
	out.wparam = 0x77;

	return out;
}

static event_log_t EventLogEventFactory(uint32_t master_time, uint16_t wParam) {

	event_log_t out;
	memset(&out, 0x00, sizeof(event_log_t));

	const event_log_severity_t 	severity 	= EVENT_INFO;
	const event_log_source_t 	source  	= EVENT_SRC_WX_HANDLER;
	out.severity_and_source = (((uint8_t)severity & 0xF) << 4) | ((uint8_t)source & 0xF);

	out.event_master_time = master_time;
	out.wparam = wParam;

	return out;
}

struct MyConfig
{
  MyConfig() : test_log( "./test_reports/nvm_test.log" )
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

BOOST_AUTO_TEST_CASE(find_first_oldest_newest____no_overrun)
{
	event_log_t ev;

	// initialize to all FFs, which is default memory content in erase state
	memset(EventLogStub, 0xFF, LOG_ENTRY_SIZE * LOG_ENTRIES);

	const event_log_t startTimesync = EventLogTimesyncFactory(123, 456);

	memcpy(EventLogStub, (void*)&startTimesync, sizeof(event_log_t));

	for (int i = 1; i < LOG_ENTRIES; i++) {
		ev = EventLogEventFactory(234 * i, 1);
		memcpy(EventLogStub + i * sizeof(event_log_t), (void*)&ev, sizeof(event_log_t));
	}

	event_log_t* oldest;
	event_log_t* newest;

	nvm_event_log_find_first_oldest_newest(&oldest, &newest);

	BOOST_CHECK_EQUAL(oldest->lparam, startTimesync.lparam);
	BOOST_CHECK_EQUAL(oldest->lparam2, startTimesync.lparam2);

	BOOST_CHECK_EQUAL(newest->event_master_time, ev.event_master_time);
	BOOST_CHECK_EQUAL(newest->wparam, ev.wparam);
}
