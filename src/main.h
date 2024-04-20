#define SYSTICK_TICKS_PER_SECONDS 100
#define SYSTICK_TICKS_PERIOD 10

#include "config_data.h"

#define INTERNAL_WATCHDOG
#define EXTERNAL_WATCHDOG


#define OWN_APRS_MSG_LN 	256u

#define SW_VER "EA05"
#define SW_DATE "06042022"

extern config_data_mode_t * main_config_data_mode;
extern config_data_basic_t * main_config_data_basic;

extern char main_string_latitude[9];
extern char main_string_longitude[9];
extern char main_callsign_with_ssid[10];

extern char main_symbol_f;
extern char main_symbol_s;

extern char main_own_aprs_msg[OWN_APRS_MSG_LN];

//extern uint32_t master_time;
