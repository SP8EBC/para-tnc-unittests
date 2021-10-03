/*
 * io.h
 *
 *  Created on: 11.06.2020
 *      Author: mateusz
 */

#ifndef IO_H_
#define IO_H_

#include "stdint.h"

void io_oc_init(void);
void io_oc_output_low(void);
void io_oc_output_hiz(void);

void io_ext_watchdog_config(void);
void io_ext_watchdog_service(void);


void io_5v_isol_sw___cntrl_vbat_s_enable(void);
void io_5v_isol_sw___cntrl_vbat_s_disable(void);

void io_12v_sw___cntrl_vbat_g_enable(void);
void io_12v_sw___cntrl_vbat_g_disable(void);

uint8_t io_get_5v_isol_sw___cntrl_vbat_s(void);

uint8_t io_get_12v_sw___cntrl_vbat_g(void);

void io___cntrl_vbat_r_enable(void);
void io___cntrl_vbat_r_disable(void);

#endif /* IO_H_ */
