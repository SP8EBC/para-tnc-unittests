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
#include "rte_wx.h"
#include "other_stubs.h"
}


#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE ANALOG_ANEMOMETER
#include <boost/test/unit_test.hpp>

struct fixture {
	fixture() {
		int i = 0;

		for (i = 0; i < ANALOG_ANEMOMETER_SPEED_PULSES_N; i++) {
			analog_anemometer_windspeed_pulses_time[i] = 0x00;
			analog_anemometer_time_between_pulses[i] = 0x00;
			analog_anemometer_pulses_per_m_s_constant = 0x00;
			analog_anemometer_timer_has_been_fired = 0x00;
		}
	}
};

struct fixture_converting_davis {
	fixture_converting_davis() {
		analog_anemometer_pulses_per_m_s_constant = 10;
	}
};

struct fixture_converting_pm {
	fixture_converting_pm() {
		analog_anemometer_pulses_per_m_s_constant = 15;
	}
};

BOOST_FIXTURE_TEST_CASE(correct_pulses, fixture) {
	analog_anemometer_windspeed_pulses_time[0] = 385;																		// 333
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
	BOOST_CHECK_EQUAL(0, analog_anemometer_slew_limit_fired);
	BOOST_CHECK_EQUAL(0, analog_anemometer_deboucing_fired);
}

BOOST_FIXTURE_TEST_CASE(bouncing_pulses_1, fixture) {
	analog_anemometer_windspeed_pulses_time[0] = 385;																		// 2
	analog_anemometer_windspeed_pulses_time[1] = 385 + 2;															// 387	// 500
	analog_anemometer_windspeed_pulses_time[2] = 385 + 2 + 500;														// 887	// 250
	analog_anemometer_windspeed_pulses_time[3] = 385 + 2 + 500 + 250;												// 1137 // 502
	analog_anemometer_windspeed_pulses_time[4] = 385 + 2 + 500 + 250 + 208 + 294;									// 1639 // 313
	analog_anemometer_windspeed_pulses_time[5] = 385 + 2 + 500 + 250 + 208 + 294 + 313; 							// 1952 // 455
	analog_anemometer_windspeed_pulses_time[6] = 385 + 2 + 500 + 250 + 208 + 294 + 313 + 455; 						// 2407 // 313
	analog_anemometer_windspeed_pulses_time[7] = 385 + 2 + 500 + 250 + 208 + 294 + 313 + 455 + 313;					// 2720 // 417
	analog_anemometer_windspeed_pulses_time[8] = 385 + 2 + 500 + 250 + 208 + 294 + 313 + 455 + 313 + 417;			// 3137 // 13
	analog_anemometer_windspeed_pulses_time[9] = 385 + 2 + 500 + 250 + 208 + 294 + 313 + 455 + 313 + 417 + 13;		// 3150

	analog_anemometer_dma_irq();

	BOOST_CHECK_EQUAL(376, rte_wx_windspeed_pulses);
	BOOST_CHECK_EQUAL(0, analog_anemometer_slew_limit_fired);
	BOOST_CHECK_EQUAL(1, analog_anemometer_deboucing_fired);
}

BOOST_FIXTURE_TEST_CASE(bouncing_pulses_2, fixture) {
	analog_anemometer_windspeed_pulses_time[0] = 385;																	// 2
	analog_anemometer_windspeed_pulses_time[1] = 385 + 2;														// 387	// 4
	analog_anemometer_windspeed_pulses_time[2] = 385 + 2 + 4;													// 391	// 250
	analog_anemometer_windspeed_pulses_time[3] = 385 + 2 + 4 + 250;												// 641 	// 499
	analog_anemometer_windspeed_pulses_time[4] = 385 + 2 + 4 + 250 + 205 + 294;									// 1140 // 313
	analog_anemometer_windspeed_pulses_time[5] = 385 + 2 + 4 + 250 + 205 + 294 + 313; 							// 1453 // 455
	analog_anemometer_windspeed_pulses_time[6] = 385 + 2 + 4 + 250 + 205 + 294 + 313 + 455; 					// 1908 // 313
	analog_anemometer_windspeed_pulses_time[7] = 385 + 2 + 4 + 250 + 205 + 294 + 313 + 455 + 313;				// 2221 // 417
	analog_anemometer_windspeed_pulses_time[8] = 385 + 2 + 4 + 250 + 205 + 294 + 313 + 455 + 313 + 417;			// 2638 // 13
	analog_anemometer_windspeed_pulses_time[9] = 385 + 2 + 4 + 250 + 205 + 294 + 313 + 455 + 313 + 417 + 13;	// 2651

	analog_anemometer_dma_irq();

	BOOST_CHECK_EQUAL(374, rte_wx_windspeed_pulses);
	BOOST_CHECK_EQUAL(0, analog_anemometer_slew_limit_fired);
	BOOST_CHECK_EQUAL(1, analog_anemometer_deboucing_fired);
}

BOOST_FIXTURE_TEST_CASE(slew_rate_too_hi_1, fixture) {
	analog_anemometer_windspeed_pulses_time[0] = 385;																		// 333
	analog_anemometer_windspeed_pulses_time[1] = 385 + 333;															// 718	// 500
	analog_anemometer_windspeed_pulses_time[2] = 385 + 333 + 500;													// 1218	// 250
	analog_anemometer_windspeed_pulses_time[3] = 385 + 333 + 500 + 250;												// 1468 // 294
	analog_anemometer_windspeed_pulses_time[4] = 385 + 333 + 500 + 250 + 208 + 294;									// 1762 // 313
	analog_anemometer_windspeed_pulses_time[5] = 385 + 333 + 500 + 250 + 208 + 294 + 313; 							// 2075 // 5555
	analog_anemometer_windspeed_pulses_time[6] = 385 + 333 + 500 + 250 + 208 + 294 + 313 + 5555; 					// 7630 // 313
	analog_anemometer_windspeed_pulses_time[7] = 385 + 333 + 500 + 250 + 208 + 294 + 313 + 5555 + 313;				// 7943 // 417
	analog_anemometer_windspeed_pulses_time[8] = 385 + 333 + 500 + 250 + 208 + 294 + 313 + 5555 + 313 + 417;		// 8360 // 556
	analog_anemometer_windspeed_pulses_time[9] = 385 + 333 + 500 + 250 + 208 + 294 + 313 + 5555 + 313 + 417 + 556;	// 8916

	analog_anemometer_dma_irq();

	BOOST_CHECK_EQUAL(531, rte_wx_windspeed_pulses);
	BOOST_CHECK_EQUAL(1, analog_anemometer_slew_limit_fired);
	BOOST_CHECK_EQUAL(0, analog_anemometer_deboucing_fired);
}

BOOST_FIXTURE_TEST_CASE(davis_1, fixture_converting_davis) {
	uint32_t ret = analog_anemometer_get_ms_from_pulse(555);

	BOOST_CHECK_EQUAL(18, ret);
}

BOOST_FIXTURE_TEST_CASE(davis_2, fixture_converting_davis) {
	uint32_t ret = analog_anemometer_get_ms_from_pulse(142);

	BOOST_CHECK_EQUAL(70, ret);
}

BOOST_FIXTURE_TEST_CASE(davis_3, fixture_converting_davis) {
	uint32_t ret = analog_anemometer_get_ms_from_pulse(2500);

	BOOST_CHECK_EQUAL(4, ret);
}

BOOST_FIXTURE_TEST_CASE(davis_4, fixture_converting_davis) {
	uint32_t ret = analog_anemometer_get_ms_from_pulse(294);

	BOOST_CHECK_EQUAL(34, ret);
}

BOOST_FIXTURE_TEST_CASE(davis_5, fixture_converting_davis) {
	uint32_t ret = analog_anemometer_get_ms_from_pulse(24);

	BOOST_CHECK_EQUAL(416, ret);
}

BOOST_FIXTURE_TEST_CASE(pm1, fixture_converting_pm) {
	uint32_t ret = analog_anemometer_get_ms_from_pulse(1666);

	BOOST_CHECK_EQUAL(4, ret);
}

BOOST_FIXTURE_TEST_CASE(pm2, fixture_converting_pm) {
	uint32_t ret = analog_anemometer_get_ms_from_pulse(138);

	BOOST_CHECK_EQUAL(48, ret);
}

BOOST_FIXTURE_TEST_CASE(pm3, fixture_converting_pm) {
	uint32_t ret = analog_anemometer_get_ms_from_pulse(277);

	BOOST_CHECK_EQUAL(24, ret);
}

BOOST_FIXTURE_TEST_CASE(pm4, fixture_converting_pm) {
	uint32_t ret = analog_anemometer_get_ms_from_pulse(531);

	BOOST_CHECK_EQUAL(12, ret);
}

BOOST_FIXTURE_TEST_CASE(pm5, fixture_converting_pm) {
	uint32_t ret = analog_anemometer_get_ms_from_pulse(374);

	BOOST_CHECK_EQUAL(17, ret);
}

BOOST_FIXTURE_TEST_CASE(pm6, fixture_converting_pm) {
	uint32_t ret = analog_anemometer_get_ms_from_pulse(403);

	BOOST_CHECK_EQUAL(16, ret);
}


