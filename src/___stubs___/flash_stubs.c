/*
 * flash_stubs.c
 *
 *  Created on: Jun 12, 2024
 *      Author: mateusz
 */

#include "flash_stubs.h"

FLASH_ErasePage_CheckFn_t checkFunction = 0;

FLASH_Status FLASH_ErasePage(uint32_t Page_Address) {

	FLASH_Status out = FLASH_COMPLETE;

	if (checkFunction != 0) {
		checkFunction(Page_Address);
	}

	return out;
}

