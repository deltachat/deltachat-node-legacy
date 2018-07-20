var deltachat = require('node-gyp-build')(__dirname)

module.exports = function () {
  while (true) {
    deltachat.perform_smtp_jobs()
    deltachat.perform_smtp_idle()
  }
}
