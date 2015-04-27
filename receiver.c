#include "receiver.h"

static struct actors_settings_t actors_settings;
static uint8_t frame_rx_in_progress;

static uint8_t buffer[6];
static uint8_t position;

/*Protocol specification
=======================================================================
| '/' | #actor | VAL_DIGIT2 | VAL_DIGIT1 | VAL_DIGIT0 | CHECKSUM | '\'|
=======================================================================
|  0  |    1   |      2     |     3      |      4     |     5    |  6 |
*/

uint8_t digit_to_int(uint8_t digit)
{
	return (digit-'0');
}

uint8_t digits_to_int(uint8_t hundreds, uint8_t tens, uint8_t units)
{
	return (hundreds*100+tens*10+units);
}

void print_buffer()
{
	for (uint8_t i = 0; i<7; i++)
		{
			//printf("%c", buffer[i]);
		}
}

void error()
{
	//printf("error\n");
}

struct actors_settings_t receive(uint8_t _byte)
{
	actors_settings.valid = 0;

	switch (_byte)
	{
		case '/':
			position = 0;
			buffer[position] = _byte;
			position++;
			break;
		case '\\':
			buffer[position] = _byte;
			if (checksum_valid(buffer) == true)
			{
				actors_settings.valid = 1;
				actors_settings.value[digit_to_int(buffer[1])] = digits_to_int(digit_to_int(buffer[2]), digit_to_int(buffer[3]), digit_to_int(buffer[4]));
			}
			else
			{
				actors_settings.valid = 0;
				error();
			}
			break;
		default:
			buffer[position] = _byte;
			position++;
			;
	}

	return actors_settings;
}

bool checksum_valid(uint8_t *buffer)
{
	//TO DO: replace magic number with defined consts, eg. buffer[CHECKSUM]
	uint8_t calculated_checksum = (digit_to_int(buffer[1]) + digit_to_int(buffer[2]) + digit_to_int(buffer[3]) + digit_to_int(buffer[4])) % 10;
	return calculated_checksum == digit_to_int(buffer[5]);
}
