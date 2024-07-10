/*
 * nvm_configuration.h
 *
 *  Created on: Jul 4, 2024
 *      Author: mateusz
 */

#ifndef STUBS____NVM_CONFIGURATION_H_
#define STUBS____NVM_CONFIGURATION_H_

#include "flash_stubs.h"

#define NVM_EVENT_LOGGING_TARGETS(ENTRY)														\
			/* TargetName,	NonPtrBasedWriteFunction,	AreaStartAddress,			AreaEndAddress,				EraseFunction,		PgmingEnableFunction,	WaitPgmCompleteFunction,	PgmingDisableFunction,	MinimumSeverityLevel,	PointerBasedAccess */	\
	ENTRY(	Flash,			NULL,						MEMORY_MAP_EVENT_LOG_START,	MEMORY_MAP_EVENT_LOG_END,	FLASH_ErasePage,	NVM_CONFIG_ENABLE_PGM,	WAIT_FOR_PGM_COMPLETION,	NVM_CONFIG_DISABLE_PGM,	1,						true)					\

/**
 *
*/
#define NVM_EVENT_CREATE_EXTERN_FOR_TARGET(_name, _non_ptr_based_write_function, _area_start_addr, _area_end_addr, _erase_fn, _enable_pgm_fn, _wait_for_pgm_fn, _disable_pgm_fn, _severity, pointer_based_access) \
		extern event_log_t* nvm_event_oldest##_name;							\
		extern event_log_t* nvm_event_newest##_name;							\
																				\

#define WAIT_FOR_PGM_COMPLETION

#define NVM_CONFIG_ENABLE_PGM

#define NVM_CONFIG_DISABLE_PGM



#endif /* STUBS____NVM_CONFIGURATION_H_ */
