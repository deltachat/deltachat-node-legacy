var Pool = require('threads').Pool
var Deltachat = require('.')
var minimist = require('minimist')

var argv = minimist(process.argv.slice(2))

if (!argv.email || !argv.password) {
  console.error("--email and --password required")
  process.exit(1)
}
console.log('Logging in with', argv.email, argv.password)

function cb (event, data1, data2) {
  console.log('called back', event, data1, data2)
  return 0
}

var deltachat = new Deltachat(cb)

deltachat.open('./deltachat.sqlite')

deltachat.set_config('addr', argv.email)
deltachat.set_config('mail_pw', argv.password)

deltachat.configure()

var connected = deltachat.is_configured()
console.log('connected?', connected)

var contact_id = deltachat.create_contact('Karissa', "okdistribute@riseup.net")
console.log(contact_id)
var contact = deltachat.get_contact(contact_id)
var info = deltachat.contact_get_name_n_addr(contact)
console.log('contact', contact, info)
var chat_id = deltachat.create_chat_by_contact_id(contact_id)
console.log('created chat with id:', chat_id)
var msglist = deltachat.get_chat_msgs(chat_id, 0, 0)
console.log('has', deltachat.array_get_cnt(msglist), 'chats')

setTimeout(function () {
  var connected = deltachat.configure()
  console.log('connected?', connected)
  deltachat.send_text_msg(chat_id, "Hi, here is my first message!");
}, 30000)
