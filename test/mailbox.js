var test = require('tape')
var deltachat = require('bindings')('deltachat')

var mailbox

test('make mailbox', function (t) {
  function cb () {
    console.log('called back', arguments)
  }

  mailbox = deltachat.mrmailbox_new(cb, null, null)
  t.end()
})

test('configure mailbox', function (t) {
  deltachat.mrmailbox_set_config(mailbox, "addr", process.env.DELTACHAT_ADDR); 
  deltachat.mrmailbox_set_config(mailbox, "mail_pw", process.env.DELTACHAT_PW);

  deltachat.mrmailbox_configure_and_connect(mailbox);
  t.end()
})

test('send test message', function (t) {
  var contact_id = deltachat.mrmailbox_create_contact(mailbox, NULL, process.env.DELTACHAT_TEST_RECIPIENT); 
  var chat_id    = deltachat.mrmailbox_create_chat_by_contact_id(mailbox, contact_id);

  deltachat.mrmailbox_send_text_msg(mailbox, chat_id, "Hi, here is my first message!");
  t.end()
})
