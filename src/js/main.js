var safe = require('safe');
var util = require('util');

Pebble.addEventListener('ready', function() {
  util.log('ready');
  require('./app');
});