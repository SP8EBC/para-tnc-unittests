/*
 * flash_stubs.h
 *
 *  Created on: Jun 12, 2024
 *      Author: mateusz
 */

#ifndef STUBS____FLASH_STUBS_H_
#define STUBS____FLASH_STUBS_H_

#include <stdint.h>
#include "./nvm/nvm_internals.h"

//// currently defined here for unit tests
//typedef enum
//{
//  FLASH_BUSY = 1,
//  FLASH_ERROR_PG,
//  FLASH_ERROR_WRP,
//  FLASH_COMPLETE,
//  FLASH_TIMEOUT
//}FLASH_Status;

typedef void(*FLASH_ErasePage_CheckFn_t)(uint32_t PageAddress);

extern FLASH_ErasePage_CheckFn_t checkFunction;

FLASH_Status FLASH_ErasePage(uint32_t Page_Address);



#endif /* STUBS____FLASH_STUBS_H_ */
