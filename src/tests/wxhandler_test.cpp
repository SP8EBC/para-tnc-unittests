/*
 * wxhandler_test.cpp
 *
 *  Created on: 04.01.2020
 *      Author: mateusz
 */

#include "wxhandler.h"

extern "C" {
#include "drivers/analog_anemometer.h"
#include "stdperiph_stubs.h"
#include "rte_wx.h"
#include "other_stubs.h"
#include "wx_handler.h"
}


#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE WX_HANDLER_TEST
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
