#ifndef RECEIVER_H
#define RECEIVER_H

#include <avr/io.h>
#include "mklib_usart/mklib_usart.h"

#define SERVOS_COUNT 2

struct actors_settings_t
{
	uint8_t valid;
	uint8_t settings[SERVOS_COUNT];
};

struct actors_settings_t receive(uint8_t _byte);

#endif //RECEIVER_H
