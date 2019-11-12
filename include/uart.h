#ifndef __uart_H__
#define __uart_H__

#include "MKL25Z4.h"
#include <stdbool.h>
#include <stdint.h>

// LEVERAGED CODE dean: https://github.com/alexander-g-dean/ESF/tree/master/Code/Chapter_8/Serial-Demo


#define USE_UART_INTERRUPTS 	(0) // 0 for polled UART communications, 1 for interrupt-driven
#define UART_OVERSAMPLE_RATE 	(16)
#define BUS_CLOCK 						(24e6)
#define SYS_CLOCK							(48e6)

void uart_init(int64_t baud_rate);

char uart_getchar();

void uart_putchar(char ch);

int uart_room_to_tx_char();

int uart_num_chars_available();

void uart_put_string(const char* inChar);

void uart_echo();

#endif
