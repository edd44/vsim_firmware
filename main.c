#include <avr/io.h>
#include <util/delay.h>
#include "mklib_usart/mklib_usart.h"
#include "receiver.h"

#define PWM_T_ON_US OCR1A
#define PWM_PERIOD_US ICR1

const int cycle_time_us = 20000;

int main()
{
	USART_stdout_redirect();
	USART_init(19200, RX_ENABLE, TX_ENABLE, RX_INT_DISABLE, TX_INT_DISABLE);
	printf("\nHello there my little fellow!\n");

	DDRD |= 0xFF;
	TCCR1A |= 1<<WGM11 | 1<<COM1A1 ;
	TCCR1B |= 1<<WGM13 | 1<<WGM12 | 1<<CS11;
	PWM_PERIOD_US = cycle_time_us;

	uint8_t i = 70;
	while (1)
		{
			receive(USART_getchar());
			//PWM_T_ON_US = USART_getchar()*10;
		}

	return 0;
}
