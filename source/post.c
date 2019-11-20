/*
 * @file post.c
 * @brief Project 5
 *
 * A power on self test.
 *
 * @author Jack Campbell
 * @tools  PC Compiler: GNU gcc 8.3.0
 *         PC Linker: GNU ld 2.32
 *         PC Debugger: GNU gdb 8.2.91.20190405-git
 *         ARM Compiler: GNU gcc version 8.2.1 20181213
 *         ARM Linker: GNU ld 2.31.51.20181213
 *         ARM Debugger: GNU gdb 8.2.50.20181213-git
 */

#include "handle_led.h"
#include "post.h"
#include "logger.h"
#include "MKL25Z4.h"
#include "uart.h"
#include "delay.h"

bool power_on_self_test()
{
	LOG_STRING( LOG_MODULE_POST, LOG_SEVERITY_STATUS, "Starting power-on self test." );

	// Check delays and LED timing
	LOG_STRING(LOG_MODULE_POST,
			LOG_SEVERITY_DEBUG,
			"LED RED ON");
    set_led(1, RED);
    delay(10);

	LOG_STRING(LOG_MODULE_POST,
			LOG_SEVERITY_DEBUG,
			"LED GREEN ON");
    set_led(1, GREEN);
    delay(10);

	LOG_STRING(LOG_MODULE_POST,
			LOG_SEVERITY_DEBUG,
			"LED BLUE ON");
    set_led(1, BLUE);
    delay(10);

    // Log will succeed if uart is enabled correctly
    LOG_STRING( LOG_MODULE_POST, LOG_SEVERITY_STATUS, "POST SUCCESS!");

    return true;
}
