#include <mrmailbox.h>
#include "src/macros.h"
#include "src/mrmailboxwrap.h"

const char* ToCString(const v8::String::Utf8Value& value) {
  return *value ? *value : "<string conversion failed>";
}

NAN_METHOD(mrmailbox_new) {
  info.GetReturnValue().Set(MrMailboxWrap::NewInstance());
}

NAN_METHOD(mrmailbox_set_config) {
  ASSERT_UNWRAP(info[0], mailbox, MrMailboxWrap);
  v8::String::Utf8Value key(info[1]);
  v8::String::Utf8Value value(info[2]);
  mrmailbox_set_config(mailbox->state, ToCString(key), ToCString(value));
}

NAN_METHOD(mrmailbox_configure_and_connect) {
  ASSERT_UNWRAP(info[0], mailbox, MrMailboxWrap)
  mrmailbox_configure_and_connect(mailbox->state);
}

NAN_METHOD(mrmailbox_create_contact) {
  ASSERT_UNWRAP(info[0], mailbox, MrMailboxWrap);
  v8::String::Utf8Value name(info[1]);
  v8::String::Utf8Value addr(info[2]);
  
  info.GetReturnValue().Set(
    Nan::New<v8::Number>(mrmailbox_create_contact(mailbox->state, ToCString(name), ToCString(addr)))
  );
}

NAN_METHOD(mrmailbox_create_chat_by_contact_id) {
  ASSERT_UNWRAP(info[0], mailbox, MrMailboxWrap);
  ASSERT_UINT(info[1], contact_id);
  info.GetReturnValue().Set(
    Nan::New<v8::Number>(mrmailbox_create_chat_by_contact_id(mailbox->state, contact_id))
  );
}

NAN_METHOD(mrmailbox_send_text_msg) {
  ASSERT_UNWRAP(info[0], mailbox, MrMailboxWrap);
  ASSERT_UINT(info[1], chat_id);
  v8::String::Utf8Value text_to_send(info[2]);
  info.GetReturnValue().Set(
    Nan::New<v8::Number>(mrmailbox_send_text_msg(mailbox->state, chat_id, ToCString(text_to_send)))
  );
}

NAN_METHOD(mrmailbox_get_chat_msgs) {
  ASSERT_UNWRAP(info[0], mailbox, MrMailboxWrap);
  ASSERT_UINT(info[1], chat_id);
  ASSERT_UINT(info[2], flags);
  ASSERT_UINT(info[3], marker1before);
  mrmailbox_get_chat_msgs(mailbox->state, chat_id, flags, marker1before);
}

NAN_MODULE_INIT(InitAll) {
  MrMailboxWrap::Init();
  EXPORT_FUNCTION(mrmailbox_new);
  EXPORT_FUNCTION(mrmailbox_set_config);
  EXPORT_FUNCTION(mrmailbox_configure_and_connect);
  EXPORT_FUNCTION(mrmailbox_create_chat_by_contact_id);
  EXPORT_FUNCTION(mrmailbox_send_text_msg);
  EXPORT_FUNCTION(mrmailbox_get_chat_msgs);
}

NODE_MODULE(deltachat, InitAll);

#undef EXPORT_FUNCTION
#undef EXPORT_NUMBER
#undef EXPORT_STRING
#undef LOCAL_FUNCTION
#undef LOCAL_STRING
#undef CDATA
#undef CLENGTH
#undef STR
#undef STR_HELPER
#undef ASSERT_BUFFER
#undef ASSERT_BUFFER_MIN_LENGTH
#undef ASSERT_BUFFER_SET_LENGTH
#undef ASSERT_UINT
#undef ASSERT_UINT_BOUNDS
#undef ASSERT_FUNCTION
#undef ASSERT_UNWRAP
