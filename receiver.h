#ifndef RECEIVER_H
#define RECEIVER_H

#include <avr/io.h>
#include <stdbool.h>
#include <stdint.h>

//#include "mklib_usart/mklib_usart.h"

#define SERVOS_COUNT 2

struct actors_settings_t
{
	uint8_t valid;
	uint8_t value[SERVOS_COUNT];
};

struct actors_settings_t receive(uint8_t _byte);

bool checksum_valid(uint8_t *buffer);
void error();
uint8_t digit_to_int(uint8_t digit);
uint8_t digits_to_int(uint8_t hundreds, uint8_t tens, uint8_t units);


#endif //RECEIVER_H
