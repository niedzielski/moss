#include "global.h"
#include "app.h"
#include "gfx.h"

#include "l_sys.h"

static Layer * layer;
static GRect win_bounds;

void on_layer_update(Layer * layer, GContext * ctx) {
  graphics_context_set_stroke_color(ctx, gcolor(0xff00ff00));

  l_sys_t sys = {
    .axiom = "0",
    .successors = (seq_t []) {"1[0]0", "11"},
    .successors_len = 2
  };

  seq_t succession = succeed(&sys, 6);
  log("succession=%s", succession);

  draw(ctx, (GPoint) {win_bounds.size.w / 2, win_bounds.size.h}, 180, succession);

  sdsfree(succession);
}

void on_window_load(Window * window) {
  Layer * window_layer = window_get_root_layer(window);
  win_bounds = layer_get_bounds(window_layer);

  layer = layer_create(win_bounds);
  layer_set_update_proc(layer, on_layer_update);
  layer_add_child(window_layer, layer);
}

void on_window_unload(Window * window) {
  layer_destroy(layer);
}