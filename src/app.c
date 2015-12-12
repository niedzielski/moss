#include "global.h"
#include "app.h"

static GPath * model_instance;
static Layer * layer;

static const GPathInfo MODEL = {
  .num_points = 6,
  .points = (GPoint []) {{21, 0}, {14, 26}, {28, 26}, {7, 60}, {14, 34}, {0, 34}}
};

void on_layer_update(Layer * layer, GContext * ctx) {
  // Fill the path:
  graphics_context_set_fill_color(ctx, gcolor(0xffff0000));
  gpath_draw_filled(ctx, model_instance);

  // Stroke the path:
  graphics_context_set_stroke_color(ctx, gcolor(0xff00ff00));
  gpath_draw_outline(ctx, model_instance);
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
    bounds.size.h / 2
  });
}

void on_window_unload(Window * window) {
  layer_destroy(layer);
  gpath_destroy(model_instance);
}