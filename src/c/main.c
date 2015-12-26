#include "global.h"
#include "app.h"

static void on_window_load(Window * win) {
  Layer * layer = window_get_root_layer(win);
  layer_set_update_proc(layer, on_layer_update);

  on_layer_init(layer);
}

static void on_window_unload(Window * win) {
  on_layer_deinit(window_get_root_layer(win));
}

static Window * init() {
  log("win init");
  Window * win = window_create();
  window_set_window_handlers(win, (WindowHandlers) {
    .load = on_window_load,
    .unload = on_window_unload,
  });
  const bool animated = true;
  window_stack_push(win, animated);
  return win;
}

static void deinit(Window * win) {
  window_destroy(win);
  log("win deinit");
}

int main() {
  Window * win = init();
  app_event_loop();
  deinit(win);
}