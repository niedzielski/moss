#include "global.h"
#include "app.h"

typedef GRect bounds_msg_t;

typedef enum {
  READY_MSG_TYPE = 0,
  BOUNDS_MSG_TYPE = 1
} msg_type_t;

static const Layer * _layer;

// todo: error handling.
static void send_msg(msg_type_t type, const void * msg, uint16_t size) {
  DictionaryIterator * iter;
  if (app_message_outbox_begin(&iter) != APP_MSG_OK) {
    log("begin fail")
    return;
  }
  dict_write_data(iter, type, (const uint8_t *) msg, size);
  dict_write_end(iter);
  uint8_t ret = app_message_outbox_send();
  log((ret == APP_MSG_OK) ? "app_message_outbox_send ok" : "app_message_outbox_send fail=%02x", ret);
}

static void on_inbox_msg_receive(DictionaryIterator * iter, void * ctx) {
  log("inbox receive");
  bounds_msg_t msg = layer_get_bounds(_layer);
  log("win origin=%d,%d bounds=%dx%d",
    msg.origin.x, msg.origin.y, msg.size.w, msg.size.h);
  send_msg(BOUNDS_MSG_TYPE, &msg, sizeof(msg));
}

static void on_inbox_msg_drop(AppMessageResult reason, void * ctx) {
  log("inbox drop reason=%08x", reason);
}

static void on_outbox_msg_sent(DictionaryIterator * iter, void * ctx) {
  log("outbox sent");
}

static void on_outbox_msg_fail(DictionaryIterator * iter,
                               AppMessageResult reason,
                               void * ctx) {
  log("outbox fail reason=%08x", reason);
}

static void enable_msg_callbacks() {
  uint32_t max_inbound_msg_size = dict_calc_buffer_size(1, 0);
  uint32_t max_outbound_msg_size = dict_calc_buffer_size(1, sizeof(bounds_msg_t));
  app_message_open(max_inbound_msg_size, max_outbound_msg_size);
}

static void disable_msg_callbacks() {
  app_message_open(0, 0);
}

static void register_msg_callbacks() {
  app_message_register_outbox_failed(on_outbox_msg_fail);
  app_message_register_outbox_sent(on_outbox_msg_sent);
  app_message_register_inbox_dropped(on_inbox_msg_drop);
  app_message_register_inbox_received(on_inbox_msg_receive);
}

static void deregister_msg_callbacks() {
  app_message_register_inbox_received(NULL);
  app_message_register_inbox_dropped(NULL);
  app_message_register_outbox_sent(NULL);
  app_message_register_outbox_failed(NULL);
}

void on_layer_init(const Layer * layer) {
  log("layer init");
  _layer = layer;
  register_msg_callbacks();
  enable_msg_callbacks();
}

void on_layer_deinit(const Layer * layer) {
  disable_msg_callbacks();
  deregister_msg_callbacks();
  app_message_deregister_callbacks();
  _layer = NULL;
  log("layer deinit");
}

void on_layer_update(Layer * const layer, GContext * ctx) {
  log("layer update");
}