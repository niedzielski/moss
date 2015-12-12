#include "global.h"
#include "app.h"

static Window * window;

static void on_init() {
  window = window_create();
  window_set_window_handlers(window, (WindowHandlers) {
    .load = on_window_load,
    .unload = on_window_unload,
  });
  const bool animated = true;
  window_stack_push(window, animated);
}

static void on_deinit() {
  window_destroy(window);
  window = NULL;
}

int main() {
  on_init();
  app_event_loop();
  on_deinit();
}