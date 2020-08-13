/*
 * main_subs.c
 *
 *  Created on: 27.12.2019
 *      Author: mateusz
 */

#include <stdint.h>

uint32_t master_time = 0;

uint32_t main_get_master_time(void) {
	return master_time;
}