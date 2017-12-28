#include <mrmailbox.h>
#include "src/macros.h"
#include "src/mrmailbox_wrap.h"
#include "src/mrarray_wrap.h"
#include "src/mrmsg_wrap.h"

/** 
 * mrmailbox
 **/

NAN_METHOD(mrmailbox_new) {
  info.GetReturnValue().Set(MrMailboxWrap::NewInstance());
}

NAN_METHOD(mrmailbox_set_config) {
  ASSERT_UNWRAP(info[0], mailbox, MrMailboxWrap);
  v8::String::Utf8Value key(info[1]);
  v8::String::Utf8Value value(info[2]);
  mrmailbox_set_config(mailbox->state, *key, *value);
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
    Nan::New<v8::Number>(mrmailbox_create_contact(mailbox->state, *name, *addr))
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
    Nan::New<v8::Number>(mrmailbox_send_text_msg(mailbox->state, chat_id, *text_to_send))
  );
}

NAN_METHOD(mrmailbox_get_chat_msgs) {
  ASSERT_UNWRAP(info[0], mailbox, MrMailboxWrap);
  ASSERT_UINT(info[1], chat_id);
  ASSERT_UINT(info[2], flags);
  ASSERT_UINT(info[3], markerbefore);
  info.GetReturnValue().Set(
    mrmailbox_get_chat_msgs(mailbox->state, chat_id, flags, markerbefore)
  );
}

NAN_METHOD(mrmailbox_get_msg) {
  ASSERT_UNWRAP(info[0], mailbox, MrMailboxWrap);
  ASSERT_UINT(info[1], msg_id);
  info.GetReturnValue().Set(
    mrmailbox_get_msg(mailbox->state, msg_id)
  );
}

/** 
 * mrarray
 **/

NAN_METHOD(mrarray_get_cnt) {
  ASSERT_UNWRAP(info[0], array, MrArrayWrap);
  info.GetReturnValue().Set(
    Nan::New<v8::Number>(mrarray_get_cnt(array->state))
  );
}

NAN_METHOD(mrarray_get_id) {
  ASSERT_UNWRAP(info[0], array, MrArrayWrap);
  ASSERT_UINT(info[1], i);
  info.GetReturnValue().Set(
    Nan::New<v8::Number>(mrarray_get_id(array->state, i))
  );
}

NAN_METHOD(mrarray_unref) {
  ASSERT_UNWRAP(info[0], array, MrArrayWrap);
  mrarray_unref(array->state);
}


/**
 * mrmsg
 **/

NAN_METHOD(mrmsg_get_text) {
  ASSERT_UNWRAP(info[0], msg, MrMsgWrap);
  const char *text = mrmsg_get_text(msg->state);
  info.GetReturnValue().Set(*text);
}

NAN_METHOD(mrmsg_unref) {
  ASSERT_UNWRAP(info[0], msg, MrMsgWrap);
  mrmsg_unref(msg->state);
}

NAN_MODULE_INIT(InitAll) {
  MrMailboxWrap::Init();
  MrArrayWrap::Init();
  MrMsgWrap::Init();

  EXPORT_FUNCTION(mrmailbox_new);
  EXPORT_FUNCTION(mrmailbox_set_config);
  EXPORT_FUNCTION(mrmailbox_configure_and_connect);
  EXPORT_FUNCTION(mrmailbox_create_chat_by_contact_id);
  EXPORT_FUNCTION(mrmailbox_send_text_msg);
  EXPORT_FUNCTION(mrmailbox_get_chat_msgs);
  EXPORT_FUNCTION(mrmailbox_get_msg);

  EXPORT_FUNCTION(mrarray_get_cnt);
  EXPORT_FUNCTION(mrarray_get_id);
  EXPORT_FUNCTION(mrarray_unref);

  EXPORT_FUNCTION(mrmsg_get_text);
  EXPORT_FUNCTION(mrmsg_unref);
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
