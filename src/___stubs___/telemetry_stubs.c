/*
 * telemetry_stubs.c
 *
 *  Created on: Apr 20, 2024
 *      Author: mateusz
 */


#include "telemetry.h"
#include "string.h"
#include "stdio.h"

int telemetry_create_description_string(const config_data_basic_t * const config_basic, const telemetry_description_t what, char * out, uint16_t out_ln)
{

	// real size of a string put into a buffer pointed by 'out'
	int out_size = 0;

	// a buffer to assembly the 'call-ssid' string at the begining of the frame
	char message_prefix_buffer[9];

	memset(message_prefix_buffer, 0x00, 0x09);

	sprintf(message_prefix_buffer, "%s-%d", config_basic->callsign, config_basic->ssid);

	switch (what) {
		case TELEMETRY_PV_PARM: {

				out_size = snprintf(out, out_ln, ":%-6s   :PARM.Rx10min,Digi10min,BatAmps,BatVolt,PvVolt,DS_QF_FULL,DS_QF_DEGRAD,DS_QF_NAVBLE,QNH_QF_NAVBLE,HUM_QF_NAVBLE,WIND_QF_DEGR,WIND_QF_NAVB", config_basic->callsign);

			break;
		}

		case TELEMETRY_PV_EQNS: {

				out_size = snprintf(out, out_ln, ":%-6s   :EQNS.0,1,0,0,1,0,0,0.07,-8,0,0.07,4,0,0.07,4", config_basic->callsign);


			break;
		}

		case TELEMETRY_PV_UNIT: {

				out_size = snprintf(out, out_ln, ":%-6s   :UNIT.Pkt,Pkt,A,V,V,Hi,Hi,Hi,Hi,Hi,Hi,Hi", config_basic->callsign);

			break;
		}

		case TELEMETRY_NORMAL_PARAM : {

				out_size = snprintf(out, out_ln, ":%-6s   :PARM.Rx10min,Tx10min,Digi10min,Vbatt,Tempre,DS_QF_FULL,DS_QF_DEGRAD,DS_QF_NAVBLE,QNH_QF_NAVBLE,HUM_QF_NAVBLE,WIND_QF_DEGR,WIND_QF_NAVB,VBATT_LOW", config_basic->callsign);


			break;
		}

		case TELEMETRY_VISCOUS_EQNS :
		case TELEMETRY_NORMAL_EQNS : {

				out_size = snprintf(out, out_ln, ":%-6s   :EQNS.0,1,0,0,1,0,0,1,0,0,0.02,10,0,0.5,-50", config_basic->callsign);

				break;
		}

		case TELEMETRY_VISCOUS_UNIT :
		case TELEMETRY_NORMAL_UNIT : {

				out_size = snprintf(out, out_ln, ":%-6s   :UNIT.Pkt,Pkt,Pkt,V,DegC,Hi,Hi,Hi,Hi,Hi,Hi,Hi,Hi", config_basic->callsign);

			break;
		}

		case TELEMETRY_VISCOUS_PARAM : {

				out_size = snprintf(out, out_ln, ":%-6s   :PARM.Rx10min,Visc10min,Digi10min,Vbatt,Tempre,DS_QF_FULL,DS_QF_DEGRAD,DS_QF_NAVBLE,QNH_QF_NAVBLE,HUM_QF_NAVBLE,WIND_QF_DEGR,WIND_QF_NAVB,VBATT_LOW", config_basic->callsign);


			break;
		}
	}

	out[out_size] = 0;

	return out_size;

}

