/*
 * Circular Buffer for MCUs
 * coded by bbingju (pjhwang@gmail.com)
 */
#include "cbuffer.h"

int cbuffer_push(cbuffer_t *self, uint8_t data)
{
    int next = (self->head + 1) % self->size;

    if (next == self->tail)     /* is full? */
        return -1;

    self->buffer[self->head] = data;
    self->head = next;

    return 0;
}

int cbuffer_pop(cbuffer_t *self, uint8_t *data)
{
    int next = (self->tail + 1) % self->size;

    if (cbuffer_peek(self, data, 0))
        return -1;

    self->tail = next;

    return 0;
}

int cbuffer_peek(cbuffer_t *self, uint8_t *data, int index)
{
    int i = (self->tail + index) % self->size;

    if (self->tail == self->head) /* is empty? */
        return -1;

    *data = self->buffer[i];

    return 0;
}
