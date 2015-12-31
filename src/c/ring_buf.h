#pragma once

#include "global.h"

typedef struct {
  unsigned read_pos;
  unsigned write_pos;
  unsigned item_size;
  unsigned capacity;
  void * buf;
} ring_buf_t;

void ring_buf_init(ring_buf_t * ring, unsigned item_size, unsigned capacity, void * buf);
void ring_buf_push_back(ring_buf_t * ring, void * item);
void * ring_buf_pop_front(ring_buf_t * ring);
void * ring_buf_peek(const ring_buf_t * ring);
unsigned ring_buf_size(const ring_buf_t * ring);
bool ring_buf_is_empty(const ring_buf_t * ring);
bool ring_buf_is_full(const ring_buf_t * ring);