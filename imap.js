var deltachat = require('node-gyp-build')(__dirname)

process.on('message', function (msg) {
  var context = msg.context
  while (true) {
    console.log('while imap')
    deltachat.dc_perform_imap_jobs(context)
    deltachat.dc_perform_imap_fetch(context)
    deltachat.dc_perform_imap_idle(context)
  }
})
