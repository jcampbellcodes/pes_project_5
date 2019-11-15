#include "MKL25Z4.h"

// milliseconds
static uint64_t gSystemTime = 0;
static const uint64_t gTimeMax = ~0;

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

