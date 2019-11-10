/*
 * @file setup_teardown.h
 * @brief Project 4
 *
 * @details Contains the setup and cleanup prototypes.
 *
 * @tools  PC Compiler: GNU gcc 8.3.0
 *         PC Linker: GNU ld 2.32
 *         PC Debugger: GNU gdb 8.2.91.20190405-git
 *         ARM Compiler: GNU gcc version 8.2.1 20181213
 *         ARM Linker: GNU ld 2.31.51.20181213
 *         ARM Debugger: GNU gdb 8.2.50.20181213-git
 */

#include "board.h"
#include "peripherals.h"
#include "clock_config.h"
#include "pin_mux.h"
#include "post.h"
#include "logger.h"
#include "stdlib.h"

void initialize()
{
  	/* Init board hardware. */
    BOARD_InitBootPins();
    BOARD_InitBootClocks();
    BOARD_InitBootPeripherals();

#ifdef DEBUG
	BOARD_InitDebugConsole();
	log_enable(LOG_SEVERITY_TEST);
	LOG_STRING(LOG_MODULE_SETUP_TEARDOWN, LOG_SEVERITY_DEBUG, "program start");
#else
	log_enable(SEVERITY_STATUS);
#endif

	/* led setup */
	LED_RED_INIT(1);
	LED_BLUE_INIT(1);
	LED_GREEN_INIT(1);

	LED_BLUE_OFF();
	LED_GREEN_OFF();
	LED_RED_OFF();

	if(!power_on_self_test())
		exit(-1);
}

/**
 * terminate
 *
 * @details Print "program end" in debug builds.
 *          Shows that the program successfully completed.
 *
 */
void terminate()
{
#ifdef DEBUG
	LOG_STRING(LOG_MODULE_SETUP_TEARDOWN, LOG_SEVERITY_DEBUG, "program end");
#endif
}
