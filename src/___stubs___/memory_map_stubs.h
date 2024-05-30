/*
 * memory_map_stubs.h
 *
 *  Created on: May 30, 2024
 *      Author: mateusz
 */

#ifndef STUBS____MEMORY_MAP_STUBS_H_
#define STUBS____MEMORY_MAP_STUBS_H_


#include <stdint.h>

#define LOG_ENTRY_SIZE		16

#define LOG_ENTRIES			20

extern uint8_t EventLogStub[LOG_ENTRY_SIZE * LOG_ENTRIES];

#endif /* STUBS____MEMORY_MAP_STUBS_H_ */
