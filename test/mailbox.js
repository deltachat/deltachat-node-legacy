var test = require('tape')
var deltachat = require('..')

var mailbox

test('make and unref mailbox', function (t) {
  function cb (event, data1, data2) {
    t.ok(event)
  }

  mailbox = deltachat.mrmailbox_new(cb, null, null)
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
