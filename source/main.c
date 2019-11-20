/*
 * @file main.c
 * @brief Project 5
 *
 * @details Main controller for the echo and application modes.
 *          Echo mode just transmits back any data received from the PC.
 *          Application mode makes reports for characters send over UART.
 *
 * @author Jack Campbell
 * @tools  PC Compiler: GNU gcc 8.3.0
 *         PC Linker: GNU ld 2.32
 *         PC Debugger: GNU gdb 8.2.91.20190405-git
 *         ARM Compiler: GNU gcc version 8.2.1 20181213
 *         ARM Linker: GNU ld 2.31.51.20181213
 *         ARM Debugger: GNU gdb 8.2.50.20181213-git
 */
#include <stdio.h>
#include "board.h"
#include "peripherals.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "MKL25Z4.h"
#include "fsl_debug_console.h"

#include "handle_led.h"
#include "setup_teardown.h"
#include "logger.h"
#include "post.h"
#include "delay.h"
#include "uart.h"
#include "time.h"
#include "circular_buffer.h"

/**
 * @brief Define this to enter echo mode, undef to use application mode.
 */
#define ECHO_MODE

struct CharCounts_t
{
	uint32_t mSeen[0xFF+1];
};

static struct CharCounts_t sCharCounts = {{0}};


/**
 * @brief How often to print the character report in application mode
 */
#define REPORT_TIMER 17

#ifndef ECHO_MODE
/**
 * Used as a size for static char arrays.
 */
#define ARRLEN 2048

static char format_buf[ARRLEN] = {0};
#endif

int main(void) {

	initialize();
    uint8_t outChar;

    for(int i =0; i < 0xFF+1;i++)
    {
    	sCharCounts.mSeen[i] =0x0;
    }
#ifdef ECHO_MODE
	while(1)
	{
	    uart_echo(&outChar);
	}
#else // application mode

    uint64_t countdownTimer = 0;
	while(1)
	{
		if(uart_echo(&outChar) == true)
		{
			sCharCounts.mSeen[outChar]++;
		}

		if((time_passed(countdownTimer) >= REPORT_TIMER))
		{
			countdownTimer = time_now();
			// print the report!
			LOG_STRING(LOG_MODULE_MAIN,
					LOG_SEVERITY_STATUS,
					"Application mode character report: ");

			for(uint32_t c = 0; c < 0xFF+1; c++)
			{
				if(sCharCounts.mSeen[c] > 0)
				{
					sprintf(format_buf, "%c - %d; ", c, sCharCounts.mSeen[c]);
					uart_put_string(format_buf);

				}
			}
			uart_put_string("\r");
			LOG_STRING(LOG_MODULE_MAIN,
					LOG_SEVERITY_STATUS,
					"Application mode character report complete.");
		}

	}

#endif

    return 0 ;
}
