/*
 * dallas_stubs.c
 *
 *  Created on: 04.01.2020
 *      Author: mateusz
 */

#include "drivers/dallas.h"

float dallas_query(dallas_qf_t *qf) {
	return 0.0f;
}

void dallas_average(float in, dallas_average_t* average) {

}

float dallas_get_average(const dallas_average_t* average) {
	return 0.0f;
}

float dallas_get_min(const dallas_average_t* average) {
	return 0.0f;

}

float dallas_get_max(const dallas_average_t* average) {
	return 0.0f;

}
