var safe = require('safe');

var dbg = true;

module.exports.log = dbg && function() {
  var sub = safe.translateError(new Error()).split('\n')[3];
  var prefixRegex = /\s*at\s*([^:]+)?\s+\(?([^:]+:)(\d+:)\d+\)?\s*/;
  var prefix = sub.replace(prefixRegex, '$2$3');
  [].unshift.call(arguments, prefix);
  console.log.apply(null, arguments);
} || function() {};