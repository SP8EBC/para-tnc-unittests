/*
 * memory_map_stubs.h
 *
 *  Created on: May 30, 2024
 *      Author: mateusz
 */

#ifndef STUBS____MEMORY_MAP_STUBS_H_
#define STUBS____MEMORY_MAP_STUBS_H_


#include <stdint.h>

#define LOG_ENTRY_SIZE		24

#define LOG_ENTRIES			20

extern uint8_t EventLogStub[LOG_ENTRY_SIZE * LOG_ENTRIES];

//typedef enum
//{
//  FLASH_BUSY = 1,
//  FLASH_ERROR_PG,
//  FLASH_ERROR_WRP,
//  FLASH_COMPLETE,
//  FLASH_TIMEOUT
//}FLASH_Status;

#endif /* STUBS____MEMORY_MAP_STUBS_H_ */
