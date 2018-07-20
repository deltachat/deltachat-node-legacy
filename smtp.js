var deltachat = require('node-gyp-build')(__dirname)

process.on('message', function (msg) {
  while (true) {
    deltachat.perform_smtp_jobs()
    deltachat.perform_smtp_idle()
  }
})
