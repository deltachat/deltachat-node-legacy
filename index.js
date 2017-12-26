var deltachat = require('bindings')('deltachat');

function cb () {
  console.log('called back', arguments)
}

console.log(deltachat.mrmailbox_new(cb, null, null))
