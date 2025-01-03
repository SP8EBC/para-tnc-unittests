/*
 * nvm_tests.cpp
 *
 *  Created on: May 30, 2024
 *      Author: mateusz
 */

// TODO: Make a test where an empty area will be completely filled by inserted events

extern "C" {
#include <___stubs___/other_stubs.h>
#include <___stubs___/stdperiph_stubs.h>
#include <___stubs___/flash_stubs.h>
#include "./nvm/nvm_event.h"
#include "memory_map.h"
#include "nvm_configuration.h"
#include "crc/crc_.h"
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
#include <sstream>
#include <cstdlib>

#define PUSH_TESTS_TIMESYNC_FIRST_IDX	(EMULATED_PAGE_EVENTS_NUM)
#define PUSH_TESTS_TIMESYNC_SECOND_IDX	(EMULATED_PAGE_EVENTS_NUM * 2)


extern uint32_t nvm_fix_broken_event_ids (event_log_t **oldest, event_log_t **newest, void *area_start,
									  void *area_end, event_log_t * current_broken,
									  FLASH_Status (*erase_fn) (uint32_t), int16_t page_size);

static const int pushTests_oldestIndexBeforeFirstInsert = (PUSH_TESTS_TIMESYNC_FIRST_IDX * sizeof(event_log_t));
static const int pushTests_newestIndexBeforeFirstInsert = ((PUSH_TESTS_TIMESYNC_FIRST_IDX - 1) * sizeof(event_log_t));

static uint32_t EraseTestCallback_index = 0;

static event_log_t EventLogTimesyncFactory(uint32_t ev_counter_id, uint32_t time, uint32_t date) {

	event_log_t out;
	memset(&out, 0x00, sizeof(event_log_t));

	out.lparam = date;
	out.lparam2 = time;

	out.event_counter_id = ev_counter_id;
	out.event_id = EVENT_TIMESYNC;
	out.wparam = EVENT_LOG_TIMESYNC_BOOTUP_WPARAM;

	const uint32_t crc = calcCRC32std(&out, sizeof(event_log_t) - 1, 0x04C11DB7, 0xFFFFFFFF, 0, 0, 0);

	out.crc_checksum = (uint8_t)(crc & 0xFF);

	return out;
}

static event_log_t EventLogEventFactory(uint32_t ev_counter_id, uint32_t master_time, uint16_t wParam) {

	event_log_t out;
	memset(&out, 0x00, sizeof(event_log_t));

	const event_log_severity_t 	severity 	= EVENT_INFO;
	const event_log_source_t 	source  	= EVENT_SRC_WX_HANDLER;
	out.severity = severity & 0xF;
	out.source = source & 0xF;

	out.event_counter_id = ev_counter_id;
	out.event_master_time = master_time;
	out.wparam = wParam;

	const uint32_t crc = calcCRC32std(&out, sizeof(event_log_t) - 1, 0x04C11DB7, 0xFFFFFFFF, 0, 0, 0);

	out.crc_checksum = (uint8_t)(crc & 0xFF);

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

BOOST_AUTO_TEST_CASE(fix_broken_event_ids)
{
	event_log_t ev;

	uint16_t nvm_event_fill_rate;

	// initialize to all FFs, which is default memory content in erase state
	memset(EventLogStub, 0xFF, LOG_ENTRY_SIZE * LOG_ENTRIES);


	for (int i = 0; i < LOG_ENTRIES; i++) {

	}
}

BOOST_AUTO_TEST_CASE(find_first_oldest_newest____no_overrun)
{
	event_log_t ev;

	uint16_t nvm_event_fill_rate;

	// initialize to all FFs, which is default memory content in erase state
	memset(EventLogStub, 0xFF, LOG_ENTRY_SIZE * LOG_ENTRIES);

	// create artificial event log with event_log_severity_t set to EVENT_TIMESYNC
	const event_log_t startTimesync = EventLogTimesyncFactory(1, 123, 456);

	// place this EVENT_TIMESYNC at the begining of stubbed event log area
	memcpy(EventLogStub, (void*)&startTimesync, sizeof(event_log_t));

	// push some more "normal" (non TIMESYNC)events into stubbed log area
	for (int i = 1; i < LOG_ENTRIES; i++) {
		ev = EventLogEventFactory(i + 1, 234 * (i + 1), 1);
		memcpy(EventLogStub + i * sizeof(event_log_t), (void*)&ev, sizeof(event_log_t));
	}

	event_log_t* oldest;
	event_log_t* newest;

	const nvm_event_result_t res = nvm_event_log_find_first_oldest_newest(&oldest, &newest, (void*)MEMORY_MAP_EVENT_LOG_START, (void*)MEMORY_MAP_EVENT_LOG_END, NVM_PAGE_SIZE, &nvm_event_fill_rate);

	BOOST_CHECK_EQUAL(res, NVM_EVENT_OK);

	BOOST_CHECK_EQUAL(nvm_event_get_crc_errors(), 0);

	BOOST_CHECK(oldest);
	BOOST_CHECK(newest);

	// oldest entry is the EVENT_TIMESYNC placed at the begining
	BOOST_CHECK_EQUAL(oldest->lparam, startTimesync.lparam);
	BOOST_CHECK_EQUAL(oldest->lparam2, startTimesync.lparam2);

	BOOST_CHECK_EQUAL(newest->event_master_time, ev.event_master_time);
	BOOST_CHECK_EQUAL(newest->wparam, ev.wparam);
}

BOOST_AUTO_TEST_CASE(find_first_oldest_newest____not_filled_completely)
{
	event_log_t ev;

	uint16_t nvm_event_fill_rate;

	// initialize to all FFs, which is default memory content in erase state
	memset(EventLogStub, 0xFF, LOG_ENTRY_SIZE * LOG_ENTRIES);

	const event_log_t startTimesync = EventLogTimesyncFactory(1, 123, 456);

	memcpy(EventLogStub, (void*)&startTimesync, sizeof(event_log_t));

	for (int i = 1; i < LOG_ENTRIES - 3; i++) {
		ev = EventLogEventFactory(i + 1, 234 * i, 1);
		memcpy(EventLogStub + i * sizeof(event_log_t), (void*)&ev, sizeof(event_log_t));
	}

	event_log_t* oldest;
	event_log_t* newest;

	const nvm_event_result_t res = nvm_event_log_find_first_oldest_newest(&oldest, &newest, (void*)MEMORY_MAP_EVENT_LOG_START, (void*)MEMORY_MAP_EVENT_LOG_END, NVM_PAGE_SIZE, &nvm_event_fill_rate);

	BOOST_CHECK_EQUAL(res, NVM_EVENT_OK);

	BOOST_CHECK_EQUAL(nvm_event_get_crc_errors(), 0);

	BOOST_CHECK(oldest);
	BOOST_CHECK(newest);

	BOOST_CHECK_EQUAL(oldest->lparam, startTimesync.lparam);
	BOOST_CHECK_EQUAL(oldest->lparam2, startTimesync.lparam2);

	BOOST_CHECK_EQUAL(newest->event_master_time, ev.event_master_time);
	BOOST_CHECK_EQUAL(newest->wparam, ev.wparam);
}

BOOST_AUTO_TEST_CASE(find_first_oldest_newest____overruned)
{
	event_log_t ev, pre, aft;

	event_log_t expected_oldest;

	uint16_t nvm_event_fill_rate;

	memset(&expected_oldest, 0x00, sizeof(event_log_t));

	// initialize to all FFs, which is default memory content in erase state
	memset(EventLogStub, 0xFF, LOG_ENTRY_SIZE * LOG_ENTRIES);

	for (int i = 0; i < LOG_ENTRIES; i++) {

		if (i == EMULATED_PAGE_EVENTS_NUM) {
			ev = EventLogTimesyncFactory(23 * (i + 2), 123, 456);;
			expected_oldest = ev;
		}
		else if (i < EMULATED_PAGE_EVENTS_NUM) {
			pre = EventLogEventFactory(234 * (i + 2), 234 * i, 11);
			ev = pre;
		}
		else if (i > EMULATED_PAGE_EVENTS_NUM) {
			aft = EventLogEventFactory(23 * (i + 2), 23 * i, 1);
			ev = aft;
		}

		memcpy(EventLogStub + i * sizeof(event_log_t), (void*)&ev, sizeof(event_log_t));
	}

	event_log_t* oldest;
	event_log_t* newest;

	const nvm_event_result_t res = nvm_event_log_find_first_oldest_newest(&oldest, &newest, (void*)MEMORY_MAP_EVENT_LOG_START, (void*)MEMORY_MAP_EVENT_LOG_END, NVM_PAGE_SIZE, &nvm_event_fill_rate);

	BOOST_CHECK_EQUAL(res, NVM_EVENT_OVERRUN);

	BOOST_CHECK_EQUAL(nvm_event_get_crc_errors(), 0);

	BOOST_CHECK(oldest);
	BOOST_CHECK(newest);

	BOOST_CHECK_EQUAL(oldest->lparam, expected_oldest.lparam);
	BOOST_CHECK_EQUAL(oldest->lparam2, expected_oldest.lparam2);

	BOOST_CHECK_EQUAL(newest->event_master_time, pre.event_master_time);
	BOOST_CHECK_EQUAL(newest->wparam, pre.wparam);
}

/**
 * This test case checks a situation when NVM area is so small, and events
 * are generated so fast that overruned, erasing all timesync
 */
BOOST_AUTO_TEST_CASE(find_first_oldest_newest____no_timestamps)
{
	event_log_t ev;

	uint16_t nvm_event_fill_rate;

	// initialize to all FFs, which is default memory content in erase state
	memset(EventLogStub, 0xFF, LOG_ENTRY_SIZE * LOG_ENTRIES);

	for (int i = 0; i < LOG_ENTRIES; i++) {
		ev = EventLogEventFactory(234 * i + 2, 234 * i, 1+i);
		memcpy(EventLogStub + i * sizeof(event_log_t), (void*)&ev, sizeof(event_log_t));
	}

	event_log_t* oldest;
	event_log_t* newest;

	event_log_t* first_in_stub = (event_log_t*)EventLogStub;

	const nvm_event_result_t res = nvm_event_log_find_first_oldest_newest(&oldest, &newest, (void*)MEMORY_MAP_EVENT_LOG_START, (void*)MEMORY_MAP_EVENT_LOG_END, NVM_PAGE_SIZE, &nvm_event_fill_rate);

	BOOST_CHECK_EQUAL(res, NVM_EVENT_OK);

	BOOST_CHECK_EQUAL(nvm_event_get_crc_errors(), 0);

	BOOST_CHECK(oldest);
	BOOST_CHECK(newest);

	BOOST_CHECK_EQUAL(oldest->lparam, first_in_stub->lparam);
	BOOST_CHECK_EQUAL(oldest->lparam2, first_in_stub->lparam2);

	BOOST_CHECK_EQUAL(newest->event_master_time, ev.event_master_time);
	BOOST_CHECK_EQUAL(newest->wparam, ev.wparam);
}

/**
 * This test checks overruned condition in case that there is a hole
 * with erased memory between the newest and oldest event.
 */
BOOST_AUTO_TEST_CASE(find_first_oldest_newest____overruned_w_unprog_gap)
{
	event_log_t ev, pre, aft;

	uint16_t nvm_event_fill_rate;

	// initialize to all FFs, which is default memory content in erase state
	memset(EventLogStub, 0xFF, LOG_ENTRY_SIZE * LOG_ENTRIES);

	const event_log_t startTimesync = EventLogTimesyncFactory(1, 123, 456);

	memcpy(EventLogStub, (void*)&startTimesync, sizeof(event_log_t));

	for (int i = 0; i < LOG_ENTRIES; i++) {

		if (i == EMULATED_PAGE_EVENTS_NUM * 2) {
			ev = startTimesync;
		}
		else if (i < EMULATED_PAGE_EVENTS_NUM) {
			pre = EventLogEventFactory(234 * i + 2, 234 * i, 11);
			ev = pre;
		}
		else if (i > EMULATED_PAGE_EVENTS_NUM * 2) {
			aft = EventLogEventFactory(23 * i + 2, 23 * i, 1);
			ev = aft;
		}

		memcpy(EventLogStub + i * sizeof(event_log_t), (void*)&ev, sizeof(event_log_t));
	}

	event_log_t* oldest;
	event_log_t* newest;

	const nvm_event_result_t res = nvm_event_log_find_first_oldest_newest(&oldest, &newest, (void*)MEMORY_MAP_EVENT_LOG_START, (void*)MEMORY_MAP_EVENT_LOG_END, NVM_PAGE_SIZE, &nvm_event_fill_rate);

	BOOST_CHECK_EQUAL(res, NVM_EVENT_OVERRUN);

	BOOST_CHECK_EQUAL(nvm_event_get_crc_errors(), 0);

	BOOST_CHECK(oldest);
	BOOST_CHECK(newest);

	BOOST_CHECK_EQUAL(oldest->lparam, startTimesync.lparam);
	BOOST_CHECK_EQUAL(oldest->lparam2, startTimesync.lparam2);

	BOOST_CHECK_EQUAL(newest->event_master_time, pre.event_master_time);
	BOOST_CHECK_EQUAL(newest->wparam, pre.wparam);
}

BOOST_AUTO_TEST_CASE(find_first_oldest_newest____empty)
{
	uint16_t nvm_event_fill_rate;

	// initialize to all FFs, which is default memory content in erase state
	memset(EventLogStub, 0xFF, LOG_ENTRY_SIZE * LOG_ENTRIES);

	event_log_t* oldest;
	event_log_t* newest;

	const nvm_event_result_t res = nvm_event_log_find_first_oldest_newest(&oldest, &newest, (void*)MEMORY_MAP_EVENT_LOG_START, (void*)MEMORY_MAP_EVENT_LOG_END, NVM_PAGE_SIZE, &nvm_event_fill_rate);

	BOOST_CHECK_EQUAL(res, NVM_EVENT_EMPTY);

}

BOOST_AUTO_TEST_CASE(random_event_ids)
{
	// initialize to all FFs, which is default memory content in erase state
	memset(EventLogStub, 0x00, LOG_ENTRY_SIZE * LOG_ENTRIES);

	uint16_t nvm_event_fill_rate;

	for (int i = 0; i < LOG_ENTRIES; i++) {

		const event_log_t ev = EventLogEventFactory(23 * i + (rand() % 1000), 23 * i, 1);

		memcpy(EventLogStub + i * sizeof(event_log_t), (void*)&ev, sizeof(event_log_t));
	}

	event_log_t* oldest;
	event_log_t* newest;

	const nvm_event_result_t res = nvm_event_log_find_first_oldest_newest(&oldest, &newest, (void*)MEMORY_MAP_EVENT_LOG_START, (void*)MEMORY_MAP_EVENT_LOG_END, NVM_PAGE_SIZE, &nvm_event_fill_rate);

	BOOST_CHECK_EQUAL(res, NVM_EVENT_AREA_ERROR);
}

void erase_test_callback(uint32_t address) {
	char message[128];

	const uint32_t start = (uint32_t)((uintptr_t)MEMORY_MAP_EVENT_LOG_START & (uintptr_t)0xFFFFFFFFu);
	const uint32_t end = (uint32_t)((uintptr_t)MEMORY_MAP_EVENT_LOG_END & (uintptr_t)0xFFFFFFFFu);

	EraseTestCallback_index = (address - start) / sizeof(event_log_t);

	snprintf(message, 128, "called address: 0x%X, start 0x%X, end 0x%X, index %d", address, start, end, EraseTestCallback_index);
	BOOST_TEST_MESSAGE(message);

	BOOST_ASSERT(EMULATED_PAGE_EVENTS_NUM == EraseTestCallback_index);
	BOOST_ASSERT((address - start) % EMULATED_PAGE_SIZE == 0);

	// memory offset to current
	uint64_t offset = (EraseTestCallback_index) * sizeof(event_log_t);

	for (unsigned i = 0; i < EMULATED_PAGE_SIZE; i++) {
		*(MEMORY_MAP_EVENT_LOG_START + offset + i) = 0xFF;
	}
}

NVM_EVENT_LOGGING_TARGETS(NVM_EVENT_CREATE_EXTERN_FOR_TARGET)

BOOST_AUTO_TEST_CASE(push_new_event_single_timesync)
{
	event_log_t ev, pre, aft, newly_inserted;
	event_log_t oldest_not_erased_ev;
	uint16_t nvm_event_fill_rate;

	EraseTestCallback_index = 0;

	// initialize to all FFs, which is default memory content in erase state
	memset(EventLogStub, 0xFF, LOG_ENTRY_SIZE * LOG_ENTRIES);

	const event_log_t startTimesync = EventLogTimesyncFactory(1, 123, 456);

	memcpy(EventLogStub, (void*)&startTimesync, sizeof(event_log_t));

	// emulated page size is LOG_ENTRIES / 5 * sizeof(event_log_t), which is
	// 4 * sizeof(event_log_t), which equals to 4 * LOG_ENTRY_SIZE = 96
	for (int i = 0; i < LOG_ENTRIES; i++) {

		if (i == EMULATED_PAGE_EVENTS_NUM) {
			ev = startTimesync;
		}
		else if (i < EMULATED_PAGE_EVENTS_NUM) {
			pre = EventLogEventFactory(234 * (i + 2), 234 * i, 11);
			ev = pre;
		}
		else if (i > EMULATED_PAGE_EVENTS_NUM) {
			aft = EventLogEventFactory(23 * (i + 2), 23 * i, 1);
			ev = aft;
		}

		if (i == (EMULATED_PAGE_EVENTS_NUM * 2)) {
			oldest_not_erased_ev = ev;
		}

		memcpy(EventLogStub + i * sizeof(event_log_t), (void*)&ev, sizeof(event_log_t));
	}


//	event_log_t* oldest;
//	event_log_t* newest;

	for (int i = 0; i < 3; i++)
	{
		std::stringstream msg_log;
		msg_log << "push_new_event_two_timesync, Inserting event, iteration: " << i;
		BOOST_TEST_MESSAGE(msg_log.str());
		const nvm_event_result_t res = nvm_event_log_find_first_oldest_newest(&nvm_event_oldestFlash, &nvm_event_newestFlash, (void*)MEMORY_MAP_EVENT_LOG_START, (void*)MEMORY_MAP_EVENT_LOG_END, NVM_PAGE_SIZE, &nvm_event_fill_rate);

		const uint8_t* oldest_buf_ptr = (uint8_t*)&EventLogStub[(i == 0) ? pushTests_oldestIndexBeforeFirstInsert : (EMULATED_PAGE_EVENTS_NUM * 2 * sizeof(event_log_t))];
		const uint8_t* newest_buf_ptr = (uint8_t*)&EventLogStub[(i == 0) ? pushTests_newestIndexBeforeFirstInsert : ((EMULATED_PAGE_EVENTS_NUM - 1 + i) * sizeof(event_log_t))];

		if (i == 0)
		{
			BOOST_CHECK_EQUAL(res, NVM_EVENT_OVERRUN);
		}
		else
		{
			// timesync was at index 4 which was erased
			BOOST_CHECK_EQUAL(res, NVM_EVENT_OVERRUN);
		}

		BOOST_CHECK_EQUAL((uint8_t*)nvm_event_oldestFlash, oldest_buf_ptr);
		BOOST_CHECK_EQUAL((uint8_t*)nvm_event_newestFlash, newest_buf_ptr);

		newly_inserted.event_counter_id = 123456 + i;
		newly_inserted.crc_checksum = calcCRC32std(&newly_inserted, sizeof(event_log_t) - 1, 0x04C11DB7, 0xFFFFFFFF, 0, 0, 0) & 0xFF;

		checkFunction = erase_test_callback;

		nvm_event_log_push_new_event(&newly_inserted);

		const uint16_t nvm_errors = nvm_event_get_crc_errors();
		BOOST_CHECK_EQUAL(nvm_errors, 0);

		const uint8_t* oldest_buf_postinst_ptr = (uint8_t*)&EventLogStub[(EMULATED_PAGE_EVENTS_NUM * 2) * sizeof(event_log_t)];
		const uint8_t* newest_buf_postinst_ptr = (uint8_t*)&EventLogStub[((EMULATED_PAGE_EVENTS_NUM + i) * sizeof(event_log_t))];
		const event_log_t * oldest_postinst_event_type_ptr = (event_log_t*)oldest_buf_postinst_ptr;
		//const event_log_t * newest_postinst_event_type_ptr = (event_log_t*)newest_buf_postinst_ptr;

		BOOST_CHECK_EQUAL((uint8_t*)nvm_event_oldestFlash, oldest_buf_postinst_ptr);
		BOOST_CHECK_EQUAL((uint8_t*)nvm_event_newestFlash, newest_buf_postinst_ptr);
		BOOST_CHECK_EQUAL(oldest_not_erased_ev.event_id, oldest_postinst_event_type_ptr->event_id);
		BOOST_CHECK_EQUAL(oldest_not_erased_ev.event_master_time, oldest_postinst_event_type_ptr->event_master_time);

		/*const nvm_event_result_t res_postinst = */(void)nvm_event_log_find_first_oldest_newest(&nvm_event_oldestFlash, &nvm_event_newestFlash, (void*)MEMORY_MAP_EVENT_LOG_START, (void*)MEMORY_MAP_EVENT_LOG_END, NVM_PAGE_SIZE, &nvm_event_fill_rate);

		BOOST_CHECK_EQUAL((uint8_t*)nvm_event_oldestFlash, oldest_buf_postinst_ptr);
		BOOST_CHECK_EQUAL((uint8_t*)nvm_event_newestFlash, newest_buf_postinst_ptr);
	}

}

BOOST_AUTO_TEST_CASE(push_new_event_two_timesync)
{
	event_log_t ev, pre, aft, newly_inserted;
	event_log_t oldest_not_erased_ev;
	uint16_t nvm_event_fill_rate;

	EraseTestCallback_index = 0;

	// initialize to all FFs, which is default memory content in erase state
	memset(EventLogStub, 0xFF, LOG_ENTRY_SIZE * LOG_ENTRIES);

	const event_log_t startTimesync = EventLogTimesyncFactory(1, 123, 456);

	memcpy(EventLogStub, (void*)&startTimesync, sizeof(event_log_t));

	// emulated page size is LOG_ENTRIES / 5 * sizeof(event_log_t), which is
	// 4 * sizeof(event_log_t), which equals to 4 * LOG_ENTRY_SIZE = 64
	for (int i = 0; i < LOG_ENTRIES; i++) {

		if (i == PUSH_TESTS_TIMESYNC_FIRST_IDX || i == PUSH_TESTS_TIMESYNC_SECOND_IDX) {
			ev = startTimesync;
		}
		else if (i < PUSH_TESTS_TIMESYNC_FIRST_IDX) {
			pre = EventLogEventFactory(234 * i + 2, 234 * i, 11);
			ev = pre;
		}
		else if (i > PUSH_TESTS_TIMESYNC_FIRST_IDX && i != PUSH_TESTS_TIMESYNC_SECOND_IDX) {
			aft = EventLogEventFactory(23 * i + 2, 23 * i, 1);
			ev = aft;
		}

		if (i == (PUSH_TESTS_TIMESYNC_SECOND_IDX)) {
			oldest_not_erased_ev = ev;
		}

		memcpy(EventLogStub + i * sizeof(event_log_t), (void*)&ev, sizeof(event_log_t));
	}

//	event_log_t* oldest;
//	event_log_t* newest;

	for (int i = 0; i < 4; i++)
	{
		std::stringstream msg_log;
		msg_log << "push_new_event_two_timesync, Inserting event, iteration: " << i;
		BOOST_TEST_MESSAGE(msg_log.str());
		const nvm_event_result_t res = nvm_event_log_find_first_oldest_newest(&nvm_event_oldestFlash, &nvm_event_newestFlash, (void*)MEMORY_MAP_EVENT_LOG_START, (void*)MEMORY_MAP_EVENT_LOG_END, NVM_PAGE_SIZE, &nvm_event_fill_rate);

		const uint8_t* oldest_buf_ptr = (uint8_t*)&EventLogStub[(i == 0) ? (EMULATED_PAGE_EVENTS_NUM * sizeof(event_log_t)) : (EMULATED_PAGE_EVENTS_NUM * 2 * sizeof(event_log_t))];
		const uint8_t* newest_buf_ptr = (uint8_t*)&EventLogStub[(i == 0) ? ((EMULATED_PAGE_EVENTS_NUM - 1) * sizeof(event_log_t)) : ((EMULATED_PAGE_EVENTS_NUM - 1 + i) * sizeof(event_log_t))];

			BOOST_CHECK_EQUAL(res, NVM_EVENT_OVERRUN);

			BOOST_CHECK_EQUAL((uint8_t*)nvm_event_oldestFlash, oldest_buf_ptr);
			BOOST_CHECK_EQUAL((uint8_t*)nvm_event_newestFlash, newest_buf_ptr);


		newly_inserted.event_counter_id = 123456 + i;
		newly_inserted.crc_checksum = calcCRC32std(&newly_inserted, sizeof(event_log_t) - 1, 0x04C11DB7, 0xFFFFFFFF, 0, 0, 0) & 0xFF;

		checkFunction = erase_test_callback;

		nvm_event_log_push_new_event(&newly_inserted);

		const uint8_t* oldest_buf_postinst_ptr = (uint8_t*)&EventLogStub[(EMULATED_PAGE_EVENTS_NUM * 2) * sizeof(event_log_t)];
		const uint8_t* newest_buf_postinst_ptr = (uint8_t*)&EventLogStub[((EMULATED_PAGE_EVENTS_NUM + i) * sizeof(event_log_t))];
		const event_log_t * oldest_postinst_event_type_ptr = (event_log_t*)oldest_buf_postinst_ptr;
		//const event_log_t * newest_postinst_event_type_ptr = (event_log_t*)newest_buf_postinst_ptr;

		BOOST_CHECK_EQUAL((uint8_t*)nvm_event_oldestFlash, oldest_buf_postinst_ptr);
		BOOST_CHECK_EQUAL((uint8_t*)nvm_event_newestFlash, newest_buf_postinst_ptr);
		BOOST_CHECK_EQUAL(oldest_not_erased_ev.event_id, oldest_postinst_event_type_ptr->event_id);
		BOOST_CHECK_EQUAL(oldest_not_erased_ev.event_master_time, oldest_postinst_event_type_ptr->event_master_time);

		const nvm_event_result_t res_postinst = nvm_event_log_find_first_oldest_newest(&nvm_event_oldestFlash, &nvm_event_newestFlash, (void*)MEMORY_MAP_EVENT_LOG_START, (void*)MEMORY_MAP_EVENT_LOG_END, NVM_PAGE_SIZE, &nvm_event_fill_rate);

		BOOST_CHECK_EQUAL(res_postinst, NVM_EVENT_OVERRUN);

		BOOST_CHECK_EQUAL(nvm_event_get_crc_errors(), 0);

		BOOST_CHECK_EQUAL((uint8_t*)nvm_event_oldestFlash, oldest_buf_postinst_ptr);
		BOOST_CHECK_EQUAL((uint8_t*)nvm_event_newestFlash, newest_buf_postinst_ptr);
	}

}

//BOOST_AUTO_TEST_CASE(push_lot_of_events)
//{
//	event_log_t ev, pre, aft, neew;
//
//	EraseTestCallback_index = 0;
//
//	// initialize to all FFs, which is default memory content in erase state
//	memset(EventLogStub, 0xFF, LOG_ENTRY_SIZE * LOG_ENTRIES);
//
//	const event_log_t startTimesync = EventLogTimesyncFactory(123, 456);
//}

