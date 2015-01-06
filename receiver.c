#include "receiver.h"

static struct actors_settings_t actors_settings;
static uint8_t frame_rx_in_progress;

/*Protocol specification
=================================================================
| SOH | #actor | US | VAL_DIGIT1 | VAL_DIGIT2 | VAL_DIGIT3 | EOT|
=================================================================
|  1  |    2   |  3 |     4      |      5     |     6      |  7 |
*/

struct actors_settings_t receive(uint8_t _byte)
{
	actors_settings.valid = 0;
	return actors_settings;
}
