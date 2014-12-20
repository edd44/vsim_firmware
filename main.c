#include <avr/io.h>
#include <util/delay.h>

#define T_ON OCR1A

const int cycle_time_us = 20000;

int main()
{
		DDRD |= 0xFF;
		TCCR1A |= 1<<WGM11 | 1<<COM1A1 ;
		TCCR1B |= 1<<WGM13 | 1<<WGM12 | 1<<CS11;
		ICR1 = cycle_time_us;

		int i = 2000;
		while (1)
			{
				T_ON = i;
				i>=3400 ? i=0 : i++;
				_delay_ms(1);
			}


	return 0;
}
