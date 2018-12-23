/*
 * Circular Buffer for MCUs
 * coded by bbingju (pjhwang@gmail.com)
 */
#include "cbuffer.h"

int cbuffer_isfull(cbuffer_t *self)
{
    return (self->head + 1) % self->size == self->tail;
}

int cbuffer_isempty(cbuffer_t *self)
{
    return self->head == self->tail;
}

void cbuffer_reset(cbuffer_t *self)
{
    self->head = 0;
    self->tail = 0;
}

int cbuffer_push(cbuffer_t *self, uint8_t data)
{
    int next = (self->head + 1) % self->size;

    if (cbuffer_isfull(self))
        return -1;

    self->buffer[self->head] = data;
    self->head = next;

    return 0;
}

int cbuffer_pop(cbuffer_t *self, uint8_t *data)
{
    int next = (self->tail + 1) % self->size;

    if (cbuffer_peek(self, data))
        return -1;

    self->tail = next;

    return 0;
}

int cbuffer_peek(cbuffer_t *self, uint8_t *data)
{
    if (cbuffer_isempty(self))
        return -1;

    *data = self->buffer[self->tail];

    return 0;
}

int  cbuffer_len(cbuffer_t *self)
{
    return (self->head >= self->tail) ? self->head - self->tail : 
        self->size - (self->tail - self->head);
}
