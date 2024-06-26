/*
 * backup_registers.h
 *
 *  Created on: Oct 19, 2023
 *      Author: mateusz
 */

#ifndef BACKUP_REGISTERS_H_
#define BACKUP_REGISTERS_H_

#include <stdint.h>

#define BACKUP_REG_ASSERT_CONCURENT_ACCES_APRSIS_WX				(1U)
#define BACKUP_REG_ASSERT_CONCURENT_ACCES_APRSIS_BEACON			(1U << 1U)
#define BACKUP_REG_ASSERT_CONCURENT_ACCES_APRSIS_TELEMETRY		(1U << 2U)
#define BACKUP_REG_ASSERT_CONCURENT_ACCES_APRSIS_DESCR			(1U << 3U)
#define BACKUP_REG_ASSERT_CONCURENT_ACCES_APRSIS_IGATE			(1U << 4U)
#define BACKUP_REG_ASSERT_CONCURENT_ACCES_APRSIS_CNTRS			(1U << 5U)
#define BACKUP_REG_ASSERT_CONCURENT_ACCES_APRSIS_LOGINSTRING	(1U << 6U)
#define BACKUP_REG_ASSERT_CONCURENT_ACCES_APRSIS_OTHER			(1U << 7U)
#define BACKUP_REG_ASSERT_ERASE_FAIL_WHILE_STORING_EVENT		(1U << 8U)

#ifdef __cplusplus
extern "C" {
#endif
	void backup_assert(uint32_t assert);
	uint32_t backup_reg_get_register_reset_check_fail();
#ifdef __cplusplus
}
#endif

#endif /* BACKUP_REGISTERS_H_ */
