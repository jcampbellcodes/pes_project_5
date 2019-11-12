
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include "circular_buffer.h"
#include <assert.h>
#include <stdlib.h>
#include <stddef.h>

/**
 * ABS
 * @details Leveraged code in this file includes the ABS macro, taken from
 *          Slide 30 of "More C Topics" lecture from ECEN 5813
 *          Link: https://canvas.colorado.edu/courses/53078/files/folder/Class%20FIles?preview=7085601
 *  Takes a number and returns the absolute value of that number.
 */
#define ABS(x) ((x)>0?(x):-(x))

// linked list
struct mem_list_node
{
	circular_buf_t* data;
	size_t size;
	struct mem_list_node* next;
};

// sentinel struct, always has null data
static struct mem_list_node memListHead = { NULL, 0, NULL };

bool bufferIsOwned(cbuf_handle_t inHandle)
{
	circular_buf_t* buffer = (circular_buf_t*)inHandle;
	if(buffer)
	{
		// try and see if the requested location resides in owned memory
		struct mem_list_node* iter = &memListHead;
		while (iter)
		{
			if(iter->data == buffer)
			{
				return true;
			}
			iter = iter->next;
		}
	}
	return false;
}

/// Pass in a storage buffer and size
/// Returns a circular buffer handle
cbuf_handle_t circular_buf_init(size_t inSize)
{
	assert(inSize);

	struct mem_list_node* iter = &memListHead;

	while(iter->next)
	{
		iter = iter->next;
	}
	iter->next = (struct mem_list_node*)malloc(sizeof(struct mem_list_node));

	iter->next->data = (circular_buf_t*)malloc(sizeof(circular_buf_t));

	assert(iter->next->data);

	iter->next->data->buffer = (uint8_t*)malloc(sizeof(uint8_t)*inSize);
	assert(iter->next->data->buffer);
	iter->next->data->max = inSize;
	iter->next->data->write = 0;
	iter->next->data->read = 0;
	iter->next->data->full = false;

	iter->next->next = NULL;

	assert(circular_buf_empty(iter->next->data));
	return iter->next->data;
}

/// Free a circular buffer structure.
/// Does not free data buffer; owner is responsible for that
void circular_buf_free(cbuf_handle_t inBufHandle)
{
	circular_buf_t* buffer = (circular_buf_t*)inBufHandle;
	if(buffer)
	{
		struct mem_list_node* iter = &memListHead;

		while (iter->next)
		{
			if(iter->next->data == buffer)
			{
				free(buffer->buffer);
				free(buffer);
				struct mem_list_node* node_to_delete = iter->next;
				iter->next = iter->next->next;
				free(node_to_delete);
				return;
			}
			iter = iter->next;
		}
	}
}

/// Put Version 2 rejects new data if the buffer is full
/// Returns 0 on success, -1 if buffer is full
buff_err circular_buf_push(cbuf_handle_t inBufHandle, uint8_t inData)
{
	buff_err err = buff_err_invalid;

	if(bufferIsOwned(inBufHandle))
	{
		if(circular_buf_full(inBufHandle))
			return buff_err_full;

		inBufHandle->buffer[inBufHandle->write] = inData;
		if(inBufHandle->full)
		{
			inBufHandle->read = (inBufHandle->read + 1) % inBufHandle->max;
		}

		inBufHandle->write = (inBufHandle->write + 1) % inBufHandle->max;
		inBufHandle->full = (inBufHandle->write == inBufHandle->read);
		err = buff_err_success;

	}
	return err;
}

/// Retrieve a value from the buffer
/// Returns 0 on success, -1 if the buffer is empty
buff_err circular_buf_pop(cbuf_handle_t inBufHandle, uint8_t * outData)
{
	buff_err err = buff_err_invalid;
	if(bufferIsOwned(inBufHandle))
	{
		if(circular_buf_empty(inBufHandle))
			return buff_err_empty;

		*outData = inBufHandle->buffer[inBufHandle->read];
		inBufHandle->full = false;
		inBufHandle->read = (inBufHandle->read + 1) % inBufHandle->max;
		err = buff_err_success;
	}
	return err;
}

/// Returns true if the buffer is empty
bool circular_buf_empty(cbuf_handle_t inBufHandle)
{
	assert(bufferIsOwned(inBufHandle));
    return (!inBufHandle->full && (inBufHandle->write == inBufHandle->read));
}

/// Returns true if the buffer is full
bool circular_buf_full(cbuf_handle_t inBufHandle)
{
	assert(bufferIsOwned(inBufHandle));
    return inBufHandle->full;
}

/// Returns the maximum capacity of the buffer
size_t circular_buf_capacity(cbuf_handle_t inBufHandle)
{
	assert(bufferIsOwned(inBufHandle));
	return inBufHandle->max;
}

/// Returns the current number of elements in the buffer
size_t circular_buf_size(cbuf_handle_t inBufHandle)
{
	assert(bufferIsOwned(inBufHandle));

	size_t size = inBufHandle->max;

	if(!inBufHandle->full)
	{
		if(inBufHandle->write >= inBufHandle->read)
		{
			size = (inBufHandle->write - inBufHandle->read);
		}
		else
		{
			size = (inBufHandle->max + inBufHandle->write - inBufHandle->read);
		}
	}

	return size;
}
