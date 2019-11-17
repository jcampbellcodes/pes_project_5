/*
 * @file time.c
 * @brief Project 5
 *
 * @details Contains interface for telling and initializing time.
 *
 * @tools  PC Compiler: GNU gcc 8.3.0
 *         PC Linker: GNU ld 2.32
 *         PC Debugger: GNU gdb 8.2.91.20190405-git
 *         ARM Compiler: GNU gcc version 8.2.1 20181213
 *         ARM Linker: GNU ld 2.31.51.20181213
 *         ARM Debugger: GNU gdb 8.2.50.20181213-git
 *
 *  LEVERAGED CODE: This time-passed and time_now pseudocode
 *  is taken from the White book, p140.
 */

#include "MKL25Z4.h"

// tenths of a second
static uint64_t gSystemTime = 0;


void time_init()
{
	SysTick->LOAD = 48000000UL/100;

	NVIC_SetPriority(SysTick_IRQn, 3); // 0, 1, 2, or 3
	NVIC_ClearPendingIRQ(SysTick_IRQn);
	NVIC_EnableIRQ(SysTick_IRQn);

	SysTick->VAL = 0;
	SysTick->CTRL = SysTick_CTRL_TICKINT_Msk | SysTick_CTRL_ENABLE_Msk;
}

void SysTick_Handler()
{
	gSystemTime++;
}

// taken from the white book
uint64_t time_passed(uint64_t since)
{
	// used to rollover the time
	static const uint64_t gTimeMax = ~0;
	uint64_t now = gSystemTime;

	if(now >= since)
	{
		return now - since;
	}

	// rollover has occurred
	return (now + (gTimeMax-since));
}

uint64_t time_now()
{
	return gSystemTime;
}

