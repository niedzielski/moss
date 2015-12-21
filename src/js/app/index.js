var log = require('util').log;

var READY_MSG_TYPE = 0;
var BOUNDS_MSG_TYPE = 1;

sendReadyMsg();

Pebble.addEventListener('appmessage', function(msg) {
  log(JSON.stringify(msg));
});

function sendReadyMsg() {
  var msg = {};
  msg[READY_MSG_TYPE] = null;
  sendMsg(msg);
}

// todo: error handling.
function sendMsg(msg) {
  var id = Pebble.sendAppMessage(msg,
    function(result) {
      log(result);
    },
    function(result) {
      log(result);
    }
  );
  log('requested msg id=' + id);
}