var deltachat = require('node-gyp-build')(__dirname)

module.exports = function () {
  while (true) {
    deltachat.perform_imap_jobs()
    deltachat.perform_imap_fetch()
    deltachat.perform_imap_idle()
  }
}
