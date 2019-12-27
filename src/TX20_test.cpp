/*
 * TX20test_test.cpp
 *
 *  Created on: 06.07.2019
 *      Author: mateusz
 */

extern "C" {
#include "./drivers/tx20.h"
#include "stdperiph_stubs.h"
}



#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE TX20
#include <boost/test/unit_test.hpp>

struct fixture {
	fixture() {

		#define BS VNAME.BitSampler
		#define BQ VNAME.BitQueue
		#define QL VNAME.QueueLenght
		#define DCD VNAME.FrameRX
		#define FC VNAME.FrameBitCounter
		#define RD VNAME.ReceiveDone
		#define MC VNAME.MeasCounter
		#define PM VNAME.PrevMeasCounter
		#define OE VNAME.OddEven

		uint8_t i;

		rte_wx_tx20_excessive_slew_rate = 0;

		////////////////////////////////////////
		//// inicjalizacja p�l struktury      //
		////////////////////////////////////////
		BQ = 0, QL = 0, FC = 0, DCD = 0, RD = 0, MC = 1, OE = 0, PM = 1;
		for (i = 1; i <= TX20_BUFF_LN - 1; i++) {
			VNAME.HistoryAVG[i].WindSpeed = -1;
			VNAME.HistoryAVG[i].WindDirX	= -1;
			VNAME.HistoryAVG[i].WindDirY	= -1;
		}

	}
};

BOOST_FIXTURE_TEST_CASE(equal_samples, fixture) {
	VNAME.Data.WindDirX = (short)(1 * 22.5);
	VNAME.Data.WindSpeed = (float)10*0.1;
	VNAME.Data.CalcChecksum = 0;
	VNAME.Data.Checksum = 0;

	TX20DataAverage();

	VNAME.Data.WindDirX = (short)(1 * 22.5);
	VNAME.Data.WindSpeed = (float)10*0.1;
	VNAME.Data.CalcChecksum = 0;
	VNAME.Data.Checksum = 0;

	TX20DataAverage();

	BOOST_CHECK_EQUAL(rte_wx_tx20_excessive_slew_rate, 0);
	BOOST_CHECK_CLOSE(VNAME.HistoryAVG[0].WindSpeed, 1.0f, 0.1f);
	BOOST_CHECK_CLOSE(VNAME.HistoryAVG[0].WindDirX, 22.5f, 7.5f);

}

BOOST_FIXTURE_TEST_CASE(equal_samples_above_slew_liit, fixture) {
	VNAME.Data.WindDirX = (short)(1 * 22.5);
	VNAME.Data.WindSpeed = (float)100*0.1;
	VNAME.Data.CalcChecksum = 0;
	VNAME.Data.Checksum = 0;

	TX20DataAverage();

	VNAME.Data.WindDirX = (short)(1 * 22.5);
	VNAME.Data.WindSpeed = (float)100*0.1;
	VNAME.Data.CalcChecksum = 0;
	VNAME.Data.Checksum = 0;

	TX20DataAverage();

	BOOST_CHECK_EQUAL(rte_wx_tx20_excessive_slew_rate, 0);
	BOOST_CHECK_CLOSE(VNAME.HistoryAVG[0].WindSpeed, 10.0f, 0.1f);
	BOOST_CHECK_CLOSE(VNAME.HistoryAVG[0].WindDirX, 22.5f, 7.5f);

}

BOOST_FIXTURE_TEST_CASE(different_wind_speed, fixture) {
	VNAME.Data.WindDirX = (short)(1 * 22.5);
	VNAME.Data.WindSpeed = (float)20*0.1;
	VNAME.Data.CalcChecksum = 0;
	VNAME.Data.Checksum = 0;

	TX20DataAverage();

	VNAME.Data.WindDirX = (short)(1 * 22.5);
	VNAME.Data.WindSpeed = (float)10*0.1;
	VNAME.Data.CalcChecksum = 0;
	VNAME.Data.Checksum = 0;

	TX20DataAverage();

	BOOST_CHECK_EQUAL(rte_wx_tx20_excessive_slew_rate, 0);
	BOOST_CHECK_CLOSE(VNAME.HistoryAVG[0].WindSpeed, 1.5f, 0.1f);
	BOOST_CHECK_CLOSE(VNAME.HistoryAVG[0].WindDirX, 22.5f, 7.5f);


}

BOOST_FIXTURE_TEST_CASE(sleew_rate, fixture) {
	VNAME.Data.WindDirX = (short)(1 * 22.5);
	VNAME.Data.WindSpeed = (float)20*0.1;
	VNAME.Data.CalcChecksum = 0;
	VNAME.Data.Checksum = 0;

	TX20DataAverage();

	VNAME.Data.WindDirX = (short)(1 * 22.5);
	VNAME.Data.WindSpeed = (float)10*0.1;
	VNAME.Data.CalcChecksum = 0;
	VNAME.Data.Checksum = 0;

	TX20DataAverage();

	VNAME.Data.WindDirX = (short)(1 * 22.5);
	VNAME.Data.WindSpeed = (float)120*0.1;
	VNAME.Data.CalcChecksum = 0;
	VNAME.Data.Checksum = 0;

	TX20DataAverage();

	VNAME.Data.WindDirX = (short)(1 * 22.5);
	VNAME.Data.WindSpeed = (float)10*0.1;
	VNAME.Data.CalcChecksum = 0;
	VNAME.Data.Checksum = 0;

	TX20DataAverage();

	BOOST_CHECK_EQUAL(rte_wx_tx20_excessive_slew_rate, 1);
	BOOST_CHECK_CLOSE(VNAME.HistoryAVG[0].WindSpeed, 1.3f, 3.0f);
	BOOST_CHECK_CLOSE(VNAME.HistoryAVG[0].WindDirX, 22.5f, 7.5f);


}

BOOST_FIXTURE_TEST_CASE(more_samples, fixture) {
	VNAME.Data.WindDirX = (short)(1 * 22.5);
	VNAME.Data.WindSpeed = (float)20*0.1;
	VNAME.Data.CalcChecksum = 0;
	VNAME.Data.Checksum = 0;

	TX20DataAverage();

	VNAME.Data.WindDirX = (short)(15 * 22.5);
	VNAME.Data.WindSpeed = (float)10*0.1;
	VNAME.Data.CalcChecksum = 0;
	VNAME.Data.Checksum = 0;

	TX20DataAverage();

	VNAME.Data.WindDirX = (short)(1 * 22.5);
	VNAME.Data.WindSpeed = (float)10*0.1;
	VNAME.Data.CalcChecksum = 0;
	VNAME.Data.Checksum = 0;

	TX20DataAverage();

	VNAME.Data.WindDirX = (short)(15 * 22.5);
	VNAME.Data.WindSpeed = (float)10*0.1;
	VNAME.Data.CalcChecksum = 0;
	VNAME.Data.Checksum = 0;

	TX20DataAverage();

	VNAME.Data.WindDirX = (short)(1 * 22.5);
	VNAME.Data.WindSpeed = (float)10*0.1;
	VNAME.Data.CalcChecksum = 0;
	VNAME.Data.Checksum = 0;

	TX20DataAverage();

	VNAME.Data.WindDirX = (short)(15 * 22.5);
	VNAME.Data.WindSpeed = (float)10*0.1;
	VNAME.Data.CalcChecksum = 0;
	VNAME.Data.Checksum = 0;

	TX20DataAverage();

	BOOST_CHECK_EQUAL(rte_wx_tx20_excessive_slew_rate, 0);
	BOOST_CHECK_CLOSE(VNAME.HistoryAVG[0].WindSpeed, 1.16f, 1.0f);
	BOOST_CHECK_CLOSE(VNAME.HistoryAVG[0].WindDirX, 0.0f, 7.5f);


}

BOOST_FIXTURE_TEST_CASE(full_buffer, fixture) {

	for (int i = 0; i < TX20_BUFF_LN + 2; i++) {
		VNAME.Data.WindDirX = (short)(1 * 22.5);
		VNAME.Data.WindSpeed = (float)0.5f*(float)i;
		VNAME.Data.CalcChecksum = 0;
		VNAME.Data.Checksum = 0;

		TX20DataAverage();
	}

	BOOST_CHECK_EQUAL(rte_wx_tx20_excessive_slew_rate, 0);
	BOOST_CHECK_CLOSE(VNAME.HistoryAVG[0].WindSpeed, 5.25f, 6.0f);
	BOOST_CHECK_CLOSE(VNAME.HistoryAVG[0].WindDirX, 22.5f, 7.5f);


}

