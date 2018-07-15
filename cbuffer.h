/*
 * Circular Buffer for MCUs
 * coded by bbingju (pjhwang@gmail.com)
 */
#pragma once

#include <stdint.h>

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

int  cbuffer_isfull(cbuffer_t *self);
int  cbuffer_isempty(cbuffer_t *self);
void cbuffer_reset(cbuffer_t *self);
int  cbuffer_push(cbuffer_t *self, uint8_t data);
int  cbuffer_pop(cbuffer_t *self, uint8_t *data);
int  cbuffer_peek(cbuffer_t *self, uint8_t *data);
