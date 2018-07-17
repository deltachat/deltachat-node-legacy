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
}

var context = new deltachat.dc_context_new(cb, null, null)
var ret = deltachat.dc_open(context)

deltachat.dc_set_config(context, 'addr', argv.email)
deltachat.dc_set_config(context, 'mail_pw', argv.password)

deltachat.dc_configure(context)

const pool = new Pool()
const deps = {
  deltachat: '.'
}

const imapJobs = pool.run(function (context, done) {
  while (true) {
    console.log('hi')
    deltachat.dc_perform_imap_jobs(context)
    deltachat.dc_perform_imap_idle(context)
    deltachat.dc_perform_imap_fetch(context)
  }
}, deps).send(context)

const smtpJobs = pool.run(function (context, done) {
  while (true) {
    deltachat.dc_perform_smtp_jobs(context)
    deltachat.dc_perform_smtp_idle(context)
  }
}, deps).send(context)

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

process.on('SIGINT', function () {
  pool.killAll()
})
