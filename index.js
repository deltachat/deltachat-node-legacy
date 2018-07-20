var deltachat = require('node-gyp-build')(__dirname)

var NON_CONTEXT = ['msg', 'chat', 'array', 'chatlist', 'lot', 'contact']

function Delta (cb) {
  if (!(this instanceof Delta)) return new Delta(cb)
  var context = new deltachat.dc_context_new(cb)
  this.context = context
  function imapForever () {
    console.log('imap thread')
    deltachat.perform_imap_jobs(context)
    deltachat.perform_imap_fetch(context)
    deltachat.perform_imap_idle(context)
    setTimeout(imapForever, 1)
  }
  setTimeout(imapForever, 1)
  console.log('imap done')

  function smtpForever () {
    console.log('smtp thread')
    deltachat.perform_smtp_jobs(context)
    deltachat.perform_smtp_idle(context)
    setTimeout(smtpForever, 1)
  }
  setTimeout(smtpForever, 1)
  console.log('smtp done')
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
