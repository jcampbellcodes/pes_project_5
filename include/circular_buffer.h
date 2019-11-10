/*
 * @file circular_buffer.h
 * @brief Project 4
 *
 * @details This file contains prototypes for calculating a spin-wait
 *          on various platforms, used for delaying LED state changes.
 *
 * @author Jack Campbell
 * @tools  PC Compiler: GNU gcc 8.3.0
 *         PC Linker: GNU ld 2.32
 *         PC Debugger: GNU gdb 8.2.91.20190405-git
 *         ARM Compiler: GNU gcc version 8.2.1 20181213
 *         ARM Linker: GNU ld 2.31.51.20181213
 *         ARM Debugger: GNU gdb 8.2.50.20181213-git
 *
 *  LEVERAGED API AND IMPLEMENTATION FROM:
 *  https://embeddedartistry.com/blog/2017/05/17/creating-a-circular-buffer-in-c-and-c/
 */


#ifndef CIRCULAR_BUFFER_H
#define CIRCULAR_BUFFER_H
#include <stdint.h>
#include <stdbool.h>

typedef enum buff_err {
	buff_err_success,
	buff_err_full,
	buff_err_empty,
	buff_err_invalid
} buff_err;

// opaque struct
typedef struct circular_buf_t {
	uint8_t * buffer;
	size_t write;
	size_t read;
	size_t max;
	bool full;
} circular_buf_t;

// Handle type, the way users interact with the API
typedef circular_buf_t* cbuf_handle_t;


/// Pass in a storage buffer and size
/// Returns a circular buffer handle
cbuf_handle_t circular_buf_init(size_t inSize);

/// Free a circular buffer structure.
/// Does not free data buffer; owner is responsible for that
void circular_buf_free(cbuf_handle_t inBufHandle);

/// Put Version 2 rejects new data if the buffer is full
/// Returns 0 on success, -1 if buffer is full
buff_err circular_buf_push(cbuf_handle_t inBufHandle, uint8_t inData);

/// Retrieve a value from the buffer
/// Returns 0 on success, -1 if the buffer is empty
buff_err circular_buf_pop(cbuf_handle_t inBufHandle, uint8_t * outData);

/// Returns true if the buffer is empty
bool circular_buf_empty(cbuf_handle_t inBufHandle);

/// Returns true if the buffer is full
bool circular_buf_full(cbuf_handle_t inBufHandle);

/// Returns the maximum capacity of the buffer
size_t circular_buf_capacity(cbuf_handle_t inBufHandle);

/// Returns the current number of elements in the buffer
size_t circular_buf_size(cbuf_handle_t inBufHandle);

#endif

