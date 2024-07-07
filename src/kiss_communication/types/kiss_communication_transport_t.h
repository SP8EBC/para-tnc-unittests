/*
 * kiss_communication_transport_t.h
 *
 *  Created on: May 23, 2024
 *      Author: mateusz
 */

#ifndef KISS_COMMUNICATION_KISS_COMMUNICATION_TRANSPORT_T_H_
#define KISS_COMMUNICATION_KISS_COMMUNICATION_TRANSPORT_T_H_


typedef enum kiss_communication_aprsmsg_transport_t {

    /**
     * Transport KISS diagnostic messages as plain unencrypted hex-string
     * which looks like
     *  HSxxxxxxxxxxxxxxxxxxxxxxxxx
     * Where 'HS' is a prefix and all 'x' are binary data. Because of
     * size limit of message content lenght, which is 67 characters,
     * this payload can have no more than 32 bytes. Each byte is
     * encoded in two characters + 'HS' prefix
    */
    KISS_TRANSPORT_HEXSTRING,

    /**
     * Transport KISS diagnostic messages, encrypted using AES128 cipher
     * in ECB mode and then put into message as a hex string. It looks
     * like that
     *  Pyyxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
     * Where 'P' is contant prefix. 'yy' is a two-character salt to protect
     * agains problems with electronic codebook mode. The rest of 'x' is exactly
     * 62 characters, what resembles:
     *      - 58 hexstring characters / 29 bytes of KISS diagnostic message,
     *      - 4 hextring characters / 2 bytes of the salt (two characters)
     *
     * An example:
     *    06FF1122334455000000000000000000000000000000000000000000006D6E - clear message in binary
     *      - 06FF11223344550000000 (...) - KISS message padded with zeros to 58 characters / 29 bytes
     *      - 6D6E - four characters / 2 bytes of salt
     *
     *    da1044bfccd776eb8b717ec3f945a4b799616a3bf4bf5ba08ba1f2d39301e5f0 - encrypted with AES128-ECB
     *
     *    Pmnda1044bfccd776eb8b717ec3f945a4b799616a3bf4bf5ba08ba1f2d39301e5f0 - encrypted & transported
     *      - P - constant prefix
     *      - 'mn' - two characters of salt
     *      - 'da1044bf (...)' ebcrypted message
     *
     *  Internally the controller holds salt value from last UDS request in RTC backup register as a 16bit word.
     *  Each request is checked and a salt value cannot be smaller than the previous one, the check is done by
     *  'converting' two character into one uint16_t value in way presented below"
     *      'mn' - 'm' 0x6D, 'n' 0x6E => 0x6D6E
     *  Value of the salt could be reverted only if it is bigger than 0x7A00 ('~' as a first char), but it may
     *  be reverted only if  0x2100 < new_salt_value < 0x2200. In another words: reverted salt must have '!'
     *  as a first character.
     *
     *  Because UDS requests and responses are transmitted as APRS text message salt must contain only printable
     *  characters (of course except tab and space)
     *
     *  Responses generated by the controller also contains salt, which is
     *
     *
    */
    KISS_TRANSPORT_ENCRYPTED_HEXSTRING,

	KISS_TRANSPORT_SERIAL_PORT,


	/**
	 * Just an echo request
	 */
	KISS_TRANSPORT_ECHO,

    /**
     * Unallowed salt value
    */
    KISS_TRANSPORT_ERROR_SALT,

    /**
     * Transport type is known to the application, but it is not implemented yet.
    */
    KISS_TRANSPORT_ERROR_UNSUPPORTED,

    KISS_TRANSPORT_NOT_KISS,

    KISS_TRANSPORT_UNINITIALIZED

} kiss_communication_transport_t;


#endif /* KISS_COMMUNICATION_KISS_COMMUNICATION_TRANSPORT_T_H_ */