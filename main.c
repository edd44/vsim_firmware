#include <avr/io.h>
#include <util/delay.h>
#include "mklib_usart/mklib_usart.h"
#include "receiver.h"

#define PWM_T_ON_US_0 OCR1A
#define PWM_T_ON_US_1 OCR1B
#define PWM_PERIOD_US ICR1

const int cycle_time_us = 20000;

void set_servo(uint8_t servo_nr, uint8_t value)
{
	switch (servo_nr)
	{
		case 0:
			PWM_T_ON_US_0 = value *10;
			break;
		case 1:
			PWM_T_ON_US_1 = value *10;
			break;
		default:
			break;
	}
}

void config_timer()
{
	//FAST PWM, /8 prescaler, clear OC1A on compare match
	DDRD |= 0xFF;
	TCCR1A |= 1<<COM1A1 | 1<<COM1B1; //clear output on compare match
	TCCR1A |= 1<<WGM11 ;
	TCCR1B |= 1<<WGM13 | 1<<WGM12 | 1<<CS11;
	PWM_PERIOD_US = cycle_time_us;

}

int main()
{
	USART_stdout_redirect();
	USART_init(19200, RX_ENABLE, TX_ENABLE, RX_INT_DISABLE, TX_INT_DISABLE);
	printf("\nHello there my little fellow!\n");

	config_timer();
	set_servo(0, 150);
	set_servo(1, 50);

	while (1)
		{
			struct actors_settings_t settings = receive(USART_getchar());
			if (settings.valid)
			{
				for (uint8_t i=0; i<SERVOS_COUNT; i++)
					{
						printf("Servo #%d: %d\n", i, settings.value[i]);
					}
				set_servo(1, settings.value[1]);
				set_servo(0, settings.value[0]);
			}
		}

	return 0;
}
