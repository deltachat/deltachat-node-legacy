var Pool = require('threads').Pool
var deltachat = require('.')
var minimist = require('minimist')

var argv = minimist(process.argv.slice(2))


console.log('Delta.Chat Version ' + deltachat.dc_get_version_str())
if (!argv.email || !argv.password) {
  console.error("--email and --password required")
  process.exit(1)
}
console.log('Logging in with', argv.email, argv.password)

function cb (event, data1, data2) {
  console.log('called back', event, data1, data2)
  return 0
}

var context = new deltachat.dc_context_new(cb)

deltachat.dc_open(context)

deltachat.dc_set_config(context, 'addr', argv.email)
deltachat.dc_set_config(context, 'mail_pw', argv.password)

deltachat.dc_configure(context)

const deps = {
  deltachat: '.'
}

var connected = deltachat.dc_is_configured(context)
console.log('connected?', connected)

var contact_id = deltachat.dc_create_contact(context, 'Karissa', "okdistribute@riseup.net")
var contact = deltachat.dc_get_contact(context, contact_id)
var info = deltachat.dc_contact_get_name_n_addr(contact)
console.log('contact', contact, info)
var chat_id = deltachat.dc_create_chat_by_contact_id(context, contact_id);
console.log('created chat with id:', chat_id)
var msglist = deltachat.dc_get_chat_msgs(context, chat_id, 0, 0)
console.log('has', deltachat.dc_array_get_cnt(msglist), 'chats')

setTimeout(function () {
  var connected = deltachat.dc_configure(context)
  console.log('connected?', connected)
  deltachat.dc_send_text_msg(context, chat_id, "Hi, here is my first message!");
}, 30000)
