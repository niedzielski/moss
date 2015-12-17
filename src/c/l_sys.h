// https://en.wikipedia.org/wiki/L-system

#pragma once

#include "global.h"

typedef sds seq_t;

typedef struct {
  seq_t axiom;

  // the predecessor is the index
  seq_t * successors;
  uint8_t successors_len;
} l_sys_t;

seq_t succeed(l_sys_t * const l_sys, int n);