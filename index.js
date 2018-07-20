var deltachat = require('node-gyp-build')(__dirname)

var NON_CONTEXT = ['msg', 'chat', 'array', 'chatlist', 'lot', 'contact']

function Delta (cb) {
  if (!(this instanceof Delta)) return new Delta(cb)
  var context = new deltachat.dc_context_new(cb)
  setTimeout(function () {
    while (true) {
      console.log('imap while')
      deltachat.perform_imap_jobs(context)
      deltachat.perform_imap_fetch(context)
      deltachat.perform_imap_idle(context)
    }
  }, 1)

  setTimeout(function () {
    while (true) {
      console.log('imap smtp')
      deltachat.perform_smtp_jobs(context)
      deltachat.perform_smtp_idle(context)
    }
  }, 1)

  this.context = context
}

Object.keys(deltachat).forEach(function (arg) {
  var name = arg.replace('dc_', '')
  Delta.prototype[name] = function () {
    var args = Array.from(arguments)
    if (isContextFunction(name)) {
      args.unshift(this.context)
    }
    return deltachat[arg].apply(this, args)
  }
})

function isContextFunction (name) {
  return NON_CONTEXT.some(function (element) {
    return !name.startsWith(element + '_')
  })
}

module.exports = Delta
