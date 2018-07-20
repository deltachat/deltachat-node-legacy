var deltachat = require('node-gyp-build')(__dirname)

var NON_CONTEXT = ['msg', 'chat', 'array', 'chatlist', 'lot', 'contact']

function Delta (cb) {
  if (!(this instanceof Delta)) return new Delta(cb)
  this.context = new deltachat.dc_context_new(cb)
}

Object.keys(deltachat).forEach(function (arg) {
  var name = arg.replace('dc_', '')
  Delta.prototype[name] = function () {
    var args = Array.from(arguments)
    if (isContextFunction(name)) {
      console.log(arg, name, this.context)
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
