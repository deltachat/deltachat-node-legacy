var deltachat = require('node-gyp-build')(__dirname)

process.on('message', function (msg) {
  var context = msg.context
  while (true) {
    console.log('while smtp')
    deltachat.dc_perform_smtp_jobs(context)
    deltachat.dc_perform_smtp_idle(context)
  }
})
