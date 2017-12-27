var deltachat = require('.')
var minimist = require('minimist')

var argv = minimist(process.argv.slice(2))

function cb () {
  console.log('called back', arguments)
}

var mailbox = deltachat.mailbox_new(cb, null, null)

deltachat.mailbox_set_config(mailbox, 'addr', argv.email)
deltachat.mailbox_set_config(mailbox, 'mail_pw', argv.mail_pw)

deltachat.mailbox_configure_and_connect()
