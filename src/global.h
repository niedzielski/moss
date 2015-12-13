#pragma once

#include <pebble.h>

#define log(...) APP_LOG(APP_LOG_LEVEL_DEBUG, __VA_ARGS__);
#define gcolor(argb) GColorFromRGBA(((argb) >> 16) & 0xff, \
                                    ((argb) >>  8) & 0xff, \
                                    ((argb) >>  0) & 0xff, \
                                    ((argb) >> 24) & 0xff)