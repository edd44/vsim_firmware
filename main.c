#include <avr/io.h>
#include <util/delay.h>
#include "mklib_usart/mklib_usart.h"

#define T_ON OCR1A

const int cycle_time_us = 20000;

int main()
{
	USART_stdout_redirect();
	USART_init(9600, 0, 1, 0, 0);
	printf("dzindybry!");
	DDRD |= 0xFF;
	TCCR1A |= 1<<WGM11 | 1<<COM1A1 ;
	TCCR1B |= 1<<WGM13 | 1<<WGM12 | 1<<CS11;
	ICR1 = cycle_time_us;

	int i = 2000;
	while (1)
		{
			T_ON = i;
			printf("%d\n",i);
			i>=2300 ? i=500 : i++;
			//_delay_ms(1);
		}

	return 0;
}
