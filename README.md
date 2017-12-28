# deltachat-node

A Node.js API for deltachat-core's native C library. This is a WORK IN
PROGRESS.

```
npm install deltachat-node
```

## Usage

#### Set up
```js
var deltachat = require('deltachat-node')

function my_delta_handler(mailbox, ev, data1, data2) {
  return 0
}

var mailbox = deltachat.mrmailbox_new(my_delta_handler, null, null)

deltachat.mrmailbox_set_config(mailbox, "addr", "alice@delta.chat") // use some real test credentials here
deltachat.mrmailbox_set_config(mailbox, "mail_pw", "***") 

deltachat.mrmailbox_configure_and_connect(mailbox)
```

#### Sending a message

```js
var contact_id = deltachat.mrmailbox_create_contact(mailbox, NULL, "bob@delta.chat") // use a real testing address here
var chat_id = deltachat.mrmailbox_create_chat_by_contact_id(mailbox, contact_id)
deltachat.mrmailbox_send_text_msg(mailbox, chat_id, "Hi, here is my first message!");
```

There are many more functions available that further manage and retrieve contacts, messages, and chats. Learn about all of the functions in API in the [deltachat C documentation](https://deltachat.github.io/deltachat-core/html/).

## License
GPLv3
