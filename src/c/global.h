#pragma once

#include <pebble.h>
#include "sds.h"

#define log(...) APP_LOG(APP_LOG_LEVEL_DEBUG, __VA_ARGS__);

#define argb2gcolor(argb) GColorFromRGBA(((argb) >> 16) & 0xff, \
                                         ((argb) >>  8) & 0xff, \
                                         ((argb) >>  0) & 0xff, \
                                         ((argb) >> 24) & 0xff)
#define gcolor(argb) COLOR_FALLBACK(argb2gcolor((argb)), (argb) ? (GColorBlack) : (GColorClear))


#define static_assert(x) int static_assert(int static_assert[(x) ? 0 : -1])