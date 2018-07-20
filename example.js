var Deltachat = require('.')
var minimist = require('minimist')

var argv = minimist(process.argv.slice(2))

if (!argv.email || !argv.password) {
  console.error("--email and --password required")
  process.exit(1)
}

function cb (event, data1, data2) {
  console.log(event, data1, data2)
  if (event === 2041) {
    var contact_id = deltachat.create_contact('Karissa', 'okdistribute@riseup.net')
    var contact = deltachat.get_contact(contact_id)
    var info = deltachat.contact_get_name_n_addr(contact)
    var chat_id = deltachat.create_chat_by_contact_id(contact_id)
    deltachat.send_text_msg(chat_id, "Hi, here is my first message!")
  }
  return 0
}

var deltachat = new Deltachat(cb)

deltachat.open()

deltachat.set_config('addr', argv.email)
deltachat.set_config('mail_pw', argv.password)

deltachat.configure()

var connected = deltachat.is_configured()
console.log('connected', connected)
while(true) { }

