/*
 * message.h
 *
 *  Created on: Apr 20, 2024
 *      Author: mateusz
 */

#ifndef INCLUDE_APRS_MESSAGE_H_
#define INCLUDE_APRS_MESSAGE_H_

#include "ax25_t.h"

#define MESSAGE_MAX_LENGHT	67

typedef struct message_t {
	AX25Call from;
	AX25Call to;
	uint8_t content[MESSAGE_MAX_LENGHT];
	uint8_t number;
}message_t;

uint8_t message_decode(const uint8_t * const message, const uint16_t message_ln, message_t * output);


#endif /* INCLUDE_APRS_MESSAGE_H_ */
