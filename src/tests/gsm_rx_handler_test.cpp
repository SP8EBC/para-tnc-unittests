/*
 * gsm_rx_handler_test.cpp
 *
 *  Created on: Feb 14, 2022
 *      Author: mateusz
 */


extern "C" {
#include "gsm/gsm.h"
#include "stdperiph_stubs.h"
#include "rte_wx.h"
#include "other_stubs.h"
}


#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE ANALOG_ANEMOMETER
#include <boost/test/unit_test.hpp>

