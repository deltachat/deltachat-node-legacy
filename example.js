var deltachat = require('.')
var minimist = require('minimist')

var argv = minimist(process.argv.slice(2))

function cb () {
  console.log('called back', arguments)
}

var mailbox = deltachat.mrmailbox_new(cb, null, null)

deltachat.mrmailbox_set_config(mailbox, 'addr', argv.email)
deltachat.mrmailbox_set_config(mailbox, 'mail_pw', argv.mail_pw)

deltachat.mrmailbox_configure_and_connect()
