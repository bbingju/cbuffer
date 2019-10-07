/*
 * Circular Buffer for MCUs
 * coded by bbingju (pjhwang@gmail.com)
 */
#pragma once

#include <stdint.h>

#ifndef __STATIC_INLINE
#define __STATIC_INLINE     static inline
#endif

typedef struct _cbuffer {
    uint8_t *buffer;
    int head, tail;
    int size;
} cbuffer_t;

#define CBUFFER_DEF_STATIC(_name, _size)        \
    uint8_t _name##_raw[_size];                 \
    cbuffer_t _name = {                         \
        .buffer = _name##_raw,                  \
        .head = 0,                              \
        .tail = 0,                              \
        .size = _size,                          \
    }

#ifdef __cplusplus
extern "C" {
#endif

__STATIC_INLINE int cbuffer_isfull(cbuffer_t *self)
{
    return (self->head + 1) % self->size == self->tail;
}

__STATIC_INLINE int cbuffer_isempty(cbuffer_t *self)
{
    return self->head == self->tail;
}

__STATIC_INLINE void cbuffer_reset(cbuffer_t *self)
{
    self->head = 0;
    self->tail = 0;
}

__STATIC_INLINE int cbuffer_len(cbuffer_t *self)
{
    return (self->head >= self->tail) ? self->head - self->tail : 
        self->size - (self->tail - self->head);
}

__STATIC_INLINE void cbuffer_enqueue(cbuffer_t *self, uint8_t data)
{
    self->buffer[self->head] = data;
    self->head = (self->head + 1) % self->size; /* next */
}

__STATIC_INLINE uint8_t cbuffer_dequeue(cbuffer_t *self)
{
    int tail = self->tail;
    self->tail = (self->tail + 1) % self->size; /* next */
    return self->buffer[tail];
}

__STATIC_INLINE int cbuffer_push(cbuffer_t *self, uint8_t data)
{
    if (cbuffer_isfull(self))
        return -1;

    cbuffer_enqueue(self, data);
    return 0;
}

__STATIC_INLINE int cbuffer_pop(cbuffer_t *self, uint8_t *data)
{
    if (cbuffer_isempty(self))
        return -1;

    *data = cbuffer_dequeue(self);
    return 0;
}

__STATIC_INLINE int cbuffer_peek(cbuffer_t *self, uint8_t *data, int index)
{
    int i = (self->tail + index) % self->size;

    if (self->tail == self->head) /* is empty? */
        return -1;

    *data = self->buffer[i];
    return 0;
}

#ifdef __cplusplus
}
#endif
