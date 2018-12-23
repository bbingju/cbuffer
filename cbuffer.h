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

int  cbuffer_push(cbuffer_t *self, uint8_t data);
int  cbuffer_pop(cbuffer_t *self, uint8_t *data);
int  cbuffer_peek(cbuffer_t *self, uint8_t *data, int index);

#ifdef __cplusplus
}
#endif    
