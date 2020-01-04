/*
 * dallas_stubs.c
 *
 *  Created on: 04.01.2020
 *      Author: mateusz
 */

#include "drivers/dallas.h"

float dallas_query(DallasQF *qf) {
	return 0.0f;
}

void dallas_average(float in, DallasAverage_t* average) {

}

float dallas_get_average(const DallasAverage_t* average) {
	return 0.0f;
}

float dallas_get_min(const DallasAverage_t* average) {
	return 0.0f;

}

float dallas_get_max(const DallasAverage_t* average) {
	return 0.0f;

}
