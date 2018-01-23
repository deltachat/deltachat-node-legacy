var test = require('tape')
var deltachat = require('..')


test('make and unref mailbox', function (t) {
  function cb (event, data1, data2) {
    t.ok(event)
  }

  var mailbox = deltachat.mrmailbox_new(cb, null, null)
  t.same(1, deltachat.mrmailbox_open(mailbox), 'open mailbox')
  t.same(1, deltachat.mrmailbox_is_open(mailbox), 'mailbox is open')
  deltachat.mrmailbox_unref(mailbox)
  t.end()
})

test('deltachat version', function (t) {
  var version = deltachat.mrmailbox_get_version_str()
  t.same(version, '0.11.1', 'got version number')
  t.end()
})

test('deltachat set and get config', function (t) {
  function cb (event, data1, data2) {
    t.ok(event)
  }

  var mailbox = deltachat.mrmailbox_new(cb, null, null)
  t.same('a', deltachat.mrmailbox_get_config(mailbox, 'addr', 'a'), 'uses default value parameter')
  var email = 'myemail@email.com'
  var password = 'password'
  deltachat.mrmailbox_set_config(mailbox, 'addr', email)
  t.same('undefined', deltachat.mrmailbox_get_config(mailbox, 'addr'), 'is not set without calling configure')
  t.same(email, deltachat.mrmailbox_get_config(mailbox, 'addr'), 'get_config returns proper value on configure')
  t.end()

})
