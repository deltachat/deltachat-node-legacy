# deltachat-node

A Node.js API for deltachat-core's native C library. 

```
npm install deltachat
```

## Usage

#### Set up
```js
var Deltachat = require('deltachat-node')

function my_delta_handler(ev, data1, data2) {
  return 0
}

var dc = new Deltachat(my_delta_handler, null, null)

dc.set_config("addr", "alice@delta.chat") // use some real test credentials here
dc.set_config(mailbox, "mail_pw", "***") 

dc.configure()
```

#### Tear Down

This also kills the child processes that are created to handle SMTP and IMAP
jobs.

```
dc.unref()
```

#### Sending a message

```js
var contact_id = dc.create_contact(mailbox, NULL, "bob@delta.chat") // use a real testing address here
var chat_id = dc.create_chat_by_contact_id(mailbox, contact_id)
dc.send_text_msg(mailbox, chat_id, "Hi, here is my first message!");
```

There are many more functions available that further manage and retrieve contacts, messages, and chats. Learn about all of the functions in API in the [deltachat C documentation](https://deltachat.github.io/deltachat-core/html/).

## Developing

```
git submodule init
git submodule update
cd deltachat-core
cat README.md
```

Then, `npm install`. You need to remove `build/` on subsequent installs.

## License
GPLv3

