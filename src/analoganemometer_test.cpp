/*
 * analoganemometer_test.cpp
 *
 *  Created on: 28.12.2019
 *      Author: mateusz
 */

#include "analoganemometer_test.h"

extern "C" {
#include "drivers/analog_anemometer.h"
#include "stdperiph_stubs.h"
#include "rte_wx_stubs.h"
#include "other_stubs.h"
}


#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE ANALOG_TEMPERATURE
#include <boost/test/unit_test.hpp>

struct fixture {
	fixture() {
		int i = 0;

		for (i = 0; i < ANALOG_ANEMOMETER_SPEED_PULSES_N; i++) {
			analog_anemometer_windspeed_pulses_time[i] = 0x00;
			analog_anemometer_pulses_durations[i] = 0x00;
			analog_anemometer_pulses_per_ms_constant = 0x00;
			analog_anemometer_timer_has_been_fired = 0x00;
		}
	}
};

BOOST_FIXTURE_TEST_CASE(correct_pulses, fixture) {
	analog_anemometer_windspeed_pulses_time[0] = 385;
	analog_anemometer_windspeed_pulses_time[1] = 385 + 333;															// 718	// 500
	analog_anemometer_windspeed_pulses_time[2] = 385 + 333 + 500;													// 1218	// 250
	analog_anemometer_windspeed_pulses_time[3] = 385 + 333 + 500 + 250;												// 1468 // 294
	analog_anemometer_windspeed_pulses_time[4] = 385 + 333 + 500 + 250 + 208 + 294;									// 1762 // 313
	analog_anemometer_windspeed_pulses_time[5] = 385 + 333 + 500 + 250 + 208 + 294 + 313; 							// 2075 // 455
	analog_anemometer_windspeed_pulses_time[6] = 385 + 333 + 500 + 250 + 208 + 294 + 313 + 455; 					// 2530 // 313
	analog_anemometer_windspeed_pulses_time[7] = 385 + 333 + 500 + 250 + 208 + 294 + 313 + 455 + 313;				// 2843 // 417
	analog_anemometer_windspeed_pulses_time[8] = 385 + 333 + 500 + 250 + 208 + 294 + 313 + 455 + 313 + 417;			// 3260 // 556
	analog_anemometer_windspeed_pulses_time[9] = 385 + 333 + 500 + 250 + 208 + 294 + 313 + 455 + 313 + 417 + 556;	// 3816

	analog_anemometer_dma_irq();

	BOOST_CHECK_EQUAL(403, rte_wx_windspeed_pulses);

}
