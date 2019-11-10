/*
 * @file delay.c
 * @brief Project 4
 *
 * @details This file contains prototypes for calculating a spin-wait
 *          on the FB, used for delaying LED state changes.
 *
 * @author Jack Campbell
 * @tools  PC Compiler: GNU gcc 8.3.0
 *         PC Linker: GNU ld 2.32
 *         PC Debugger: GNU gdb 8.2.91.20190405-git
 *         ARM Compiler: GNU gcc version 8.2.1 20181213
 *         ARM Linker: GNU ld 2.31.51.20181213
 *         ARM Debugger: GNU gdb 8.2.50.20181213-git
 */
#include "delay.h"
#include "fsl_debug_console.h"

/* GLOBALS */
const uint64_t CLOCKS_PER_MILLISECOND = 2600UL;

/**
 * delay
 *
 * @brief Blocks execution for the specified time.
 * @param inDelayMs Then time in milliseconds to block.
 */
void delay(uint64_t inDelayMs)
{
	volatile uint64_t number = inDelayMs * CLOCKS_PER_MILLISECOND;

	while(number--)
	{
		__asm volatile ("nop");
	}
}
