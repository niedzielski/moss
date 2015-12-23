#include "global.h"
#include "app.h"

static Window * _win;

static void on_window_load(Window * win) {
  Layer * layer = window_get_root_layer(_win);
  layer_set_update_proc(layer, on_layer_update);

  on_layer_init(layer);
}

static void on_window_unload(Window * win) {
  on_layer_deinit(window_get_root_layer(_win));
}

static void init() {
  log("win init");
  _win = window_create();
  window_set_window_handlers(_win, (WindowHandlers) {
    .load = on_window_load,
    .unload = on_window_unload,
  });
  const bool animated = true;
  window_stack_push(_win, animated);
}

static void deinit() {
  window_destroy(_win);
  _win = NULL;
  log("win deinit");
}

int main() {
  init();
  app_event_loop();
  deinit();
}