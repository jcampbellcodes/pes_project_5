#include "handle_led.h"
#include "post.h"
#include "logger.h"
#include "MKL25Z4.h"
#include "uart.h"
#include "delay.h"

bool power_on_self_test()
{
	LOG_STRING( LOG_MODULE_POST, LOG_SEVERITY_DEBUG, "Starting power-on self test." );
    set_led(1, RED);
    delay(100);
    set_led(1, GREEN);
    delay(100);
    set_led(1, BLUE);
    delay(100);

    LOG_STRING( LOG_MODULE_POST, LOG_SEVERITY_DEBUG, "POST SUCCESS!");

    return true;
}
