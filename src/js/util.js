var safe = require('safe');

var dbg = true;

module.exports.log = dbg && function() {
  var sub = safe.translateError(new Error()).split('\n')[3];
  var prefix = sub.replace(/\s*at\s+(\S+)\s+\(([^:]+:)(\d+:)\d+\)\s*/, '$2$3');
  [].unshift.call(arguments, prefix);
  console.log.apply(null, arguments);
} || function() {};