#pragma once

#include <pebble.h>

#define DBG 1

#ifdef DBG
  #define log(...) APP_LOG(APP_LOG_LEVEL_DEBUG, __VA_ARGS__);
#else
  #define log(...) ((void) 0)
#endif

#define static_assert(x) int static_assert(int static_assert[(x) ? 0 : -1])