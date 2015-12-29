#include "ring_buf.h"

static void * ptr_at(const ring_buf_t * ring, int pos) {
  return ring->buf + pos * ring->sizeof_item;
}

static unsigned next_pos(const ring_buf_t * ring, int pos) {
  return (pos + 1) % ring->capacity;
}

void ring_buf_init(ring_buf_t * ring, unsigned sizeof_item, unsigned capacity, void * buf) {
  ring->read_pos = ring->write_pos = 0;
  ring->sizeof_item = sizeof_item;
  ring->capacity = capacity;
  ring->buf = buf;
}

void ring_buf_push_back(ring_buf_t * ring, void * item) {
  if (ring_buf_is_full(ring)) {
    return;
  }

  memcpy(ptr_at(ring, ring->write_pos), item, ring->sizeof_item);
  ring->write_pos = next_pos(ring, ring->write_pos);
}

void * ring_buf_pop_front(ring_buf_t * ring) {
  if (ring_buf_is_empty(ring)) {
    return NULL;
  }

  void * item = ptr_at(ring, ring->read_pos);
  ring->read_pos = next_pos(ring, ring->read_pos);
  return item;
}

void * ring_buf_peek(const ring_buf_t * ring) {
  return ring_buf_is_empty(ring) ? NULL : ptr_at(ring, ring->read_pos);
}

unsigned ring_buf_size(const ring_buf_t * ring) {
  return (ring->write_pos + ring->capacity - ring->read_pos) % ring->capacity;
}

bool ring_buf_is_empty(const ring_buf_t * ring) {
  return ring->read_pos == ring->write_pos;
}

bool ring_buf_is_full(const ring_buf_t * ring) {
  return next_pos(ring, ring->write_pos) == ring->read_pos;
}