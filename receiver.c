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


void print_buffer()
{
	for (uint8_t i = 0; i<7; i++)
		{
			printf("%c\n", buffer[i]);
		}
}

void error()
{
	printf("error\n");
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
			print_buffer();
			break;
		default:
			buffer[position] = _byte;
			position++;
			;
	}

	return actors_settings;
}

