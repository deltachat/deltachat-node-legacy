# deltachat-node

A Node.js API for deltachat-core's native C library. This is a WORK IN
PROGRESS.

```
npm install deltachat-node
```

## API

## Usage

#### Set up
```js
var deltachat = require('deltachat-node')

function my_delta_handler(mailbox, event, data1, data2) {
  return 0
}

var mailbox = deltachat.mrmailbox_new(my_delta_handler, null, null)

deltachat.mrmailbox_set_config(mailbox, "addr", "alice@delta.chat") // use some real test credentials here
deltachat.mrmailbox_set_config(mailbox, "mail_pw", "***") 

mrmailbox_configure_and_connect(mailbox)
```

#### Sending a message

```js
var contact_id = deltachat.mrmailbox_create_contact(mailbox, NULL, "bob@delta.chat") // use a real testing address here
var chat_id = deltachat.mrmailbox_create_chat_by_contact_id(mailbox, contact_id)
deltachat.mrmailbox_send_text_msg(mailbox, chat_id, "Hi, here is my first message!");
```

There are many more functions available dealing with contacts, messages, and the mailbox. Read more about the API on the [deltachat C documentation](https://deltachat.github.io/deltachat-core/html/).

## License
GPLv3
