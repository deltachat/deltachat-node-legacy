var deltachat = require('node-gyp-build')(__dirname)

process.on('message', function (msg) {
  while (true) {
    console.log('imap while')
    deltachat.perform_imap_jobs()
    deltachat.perform_imap_fetch()
    deltachat.perform_imap_idle()
  }
})
