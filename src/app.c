#include "global.h"
#include "app.h"

static GPath * model_instance;
static Layer * layer;

static const GPathInfo MODEL = {
  .num_points = 4,
  .points = (GPoint []) {{0,0}, {0,-10}, {-10,-10}, {-10,0}}
};

void on_layer_update(Layer * layer, GContext * ctx) {
  graphics_context_set_stroke_color(ctx, gcolor(0xff00ff00));
  gpath_draw_outline_open(ctx, model_instance);
}

void init_model_instance(GPoint origin) {
  model_instance = gpath_create(&MODEL);
  gpath_move_to(model_instance, origin);
}

void on_window_load(Window * window) {
  Layer * window_layer = window_get_root_layer(window);
  GRect bounds = layer_get_bounds(window_layer);

  layer = layer_create(bounds);
  layer_set_update_proc(layer, on_layer_update);
  layer_add_child(window_layer, layer);

  init_model_instance((GPoint) {
    bounds.size.w / 2,
    bounds.size.h
  });
}

void on_window_unload(Window * window) {
  layer_destroy(layer);
  gpath_destroy(model_instance);
}