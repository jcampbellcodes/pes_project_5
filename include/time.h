#ifndef __timeh__
#define __timeh__

#include <stdint.h>

void time_init();

uint64_t time_passed(uint64_t since);

uint64_t time_now();

#endif
