#include "gfx.h"

static const int LEN = 2;

void draw_i(GContext * ctx, GPoint origin, int angle, seq_t cmds, int i) {
  for (int n = strlen(cmds); i < n; ++i) {
    char cmd = cmds[i];
    if (cmd >= '0' && cmd <= '9') {
      int32_t rads = DEG_TO_TRIGANGLE(angle);
      int32_t dx = (sin_lookup(rads) * LEN) / TRIG_MAX_RATIO;
      int32_t dy = (cos_lookup(rads) * LEN) / TRIG_MAX_RATIO;

      graphics_draw_line(ctx, origin, (GPoint) {origin.x + dx, origin.y + dy});

      origin.x += dx;
      origin.y += dy;
    } else if (cmd == '[') {
      draw_i(ctx, origin, angle - 45, cmds, i + 1);
      angle += 45;
    } else if (cmd == ']') {
      return;
    }
  }
}

void draw(GContext * ctx, GPoint origin, int angle, seq_t cmds) {
  draw_i(ctx, origin, angle, cmds, 0);
}