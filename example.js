var deltachat = require('.')
var minimist = require('minimist')

var argv = minimist(process.argv.slice(2))

function cb () {
  console.log('called back', arguments)
}

console.log('Delta.Chat Version ' + deltachat.mrmailbox_get_version_str())
if (!argv.email || !argv.password) {
  console.error("--email and --password required")
  process.exit(1)
}
console.log('Logging in with', argv.email, argv.password)

var mailbox = new deltachat.mrmailbox_new(cb, null, null)

deltachat.mrmailbox_set_config(mailbox, 'addr', argv.email)
deltachat.mrmailbox_set_config(mailbox, 'mail_pw', argv.password)
deltachat.mrmailbox_set_config(mailbox, 'send_user', argv.email)

var connected = deltachat.mrmailbox_configure_and_connect(mailbox)
console.log('connected?', connected)

var contact_id = deltachat.mrmailbox_create_contact(mailbox, null, "okdistribute@riseup.net"); 
var chat_id = deltachat.mrmailbox_create_chat_by_contact_id(mailbox, contact_id);
var msglist = deltachat.mrmailbox_get_chat_msgs(mailbox, chat_id, 0, 0)
console.log(msglist)

setTimeout(function () {
  var connected = deltachat.mrmailbox_is_configured(mailbox)
  console.log('connected?', connected)
  deltachat.mrmailbox_send_text_msg(mailbox, chat_id, "Hi, here is my first message!");
}, 14000)

