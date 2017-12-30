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

NAN_METHOD(mrmailbox_set_config_int) {
  ASSERT_UNWRAP(info[0], mailbox, MrMailboxWrap);
  v8::String::Utf8Value key(info[1]);
  ASSERT_UINT(info[2], value);
  mrmailbox_set_config_int(mailbox->state, *key, value);
}

NAN_METHOD(mrmailbox_get_config) {
  ASSERT_UNWRAP(info[0], mailbox, MrMailboxWrap);
  v8::String::Utf8Value key(info[1]);
  v8::String::Utf8Value def(info[2]);
  const char *ret = mrmailbox_get_config(mailbox->state, *key, *def);
  info.GetReturnValue().Set(*ret);
}

NAN_METHOD(mrmailbox_get_config_int) {
  ASSERT_UNWRAP(info[0], mailbox, MrMailboxWrap);
  v8::String::Utf8Value key(info[1]);
  ASSERT_UINT(info[2], def);
  info.GetReturnValue().Set(
    Nan::New<v8::Number>(mrmailbox_get_config_int(mailbox->state, *key, def))
  );
}

NAN_METHOD(mrmailbox_get_info) {
  ASSERT_UNWRAP(info[0], mailbox, MrMailboxWrap);
  const char *ret = mrmailbox_get_info(mailbox->state);
  info.GetReturnValue().Set(*ret);
}

NAN_METHOD(mrmailbox_get_version_str) {
  const char *ret = mrmailbox_get_version_str();
  info.GetReturnValue().Set(*ret);
}

NAN_METHOD(mrmailbox_connect) {
  ASSERT_UNWRAP(info[0], mailbox, MrMailboxWrap);
  mrmailbox_connect(mailbox->state);
}

NAN_METHOD(mrmailbox_disconnect) {
  ASSERT_UNWRAP(info[0], mailbox, MrMailboxWrap);
  mrmailbox_disconnect(mailbox->state);
}

NAN_METHOD(mrmailbox_heartbeat) {
  ASSERT_UNWRAP(info[0], mailbox, MrMailboxWrap);
  mrmailbox_heartbeat(mailbox->state);
}

NAN_METHOD(mrmailbox_open) {
  ASSERT_UNWRAP(info[0], mailbox, MrMailboxWrap)
  v8::String::Utf8Value dbfile(info[1]);
  v8::String::Utf8Value blobdir(info[2]);
  info.GetReturnValue().Set(
    Nan::New<v8::Number>(mrmailbox_open(mailbox->state, *dbfile, *blobdir))
  );
}

NAN_METHOD(mrmailbox_close) {
  ASSERT_UNWRAP(info[0], mailbox, MrMailboxWrap);
  mrmailbox_close(mailbox->state);
}

NAN_METHOD(mrmailbox_is_open) {
  ASSERT_UNWRAP(info[0], mailbox, MrMailboxWrap)
  info.GetReturnValue().Set(
    Nan::New<v8::Number>(mrmailbox_is_open(mailbox->state))
  );
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

NAN_METHOD(mrmailbox_unref) {
  ASSERT_UNWRAP(info[0], mailbox, MrMailboxWrap);
  mrmailbox_unref(mailbox->state);
}

NAN_METHOD(mrmailbox_get_chatlist) {
  ASSERT_UNWRAP(info[0], mailbox, MrMailboxWrap);
  ASSERT_UINT(info[1], listflags);
  v8::String::Utf8Value query(info[2]);
  info.GetReturnValue().Set(
    mrmailbox_get_chatlist(mailbox->state, listflags, *query)
  );
}

NAN_METHOD(mrmailbox_get_chat) {
  ASSERT_UNWRAP(info[0], mailbox, MrMailboxWrap);
  ASSERT_UINT(info[1], chat_id);
  info.GetReturnValue().Set(
    mrmailbox_get_chat(mailbox->state, chat_id)
  )
}

NAN_METHOD(mrmailbox_marknoticed_chat) {
  ASSERT_UNWRAP(info[0], mailbox, MrMailboxWrap);
  ASSERT_UINT(info[1], chat_id);
  mrmailbox_marknoticed_chat(mailbox->state, chat_id)
}

NAN_METHOD(mrmailbox_get_chat_id_by_contact_id) {
  ASSERT_UNWRAP(info[0], mailbox, MrMailboxWrap);
  ASSERT_UINT(info[1], contact_id);
  info.GetReturnValue().Set(
    Nan::New<v8::Number>(mrmailbox_get_chat_id_by_contact_id(mailbox->state, contact_id))
  )
}

NAN_METHOD(mrmailbox_get_chat_media) {
  ASSERT_UNWRAP(info[0], mailbox, MrMailboxWrap);
  ASSERT_UINT(info[1], chat_id);
  ASSERT_UINT(info[2], msg_type);
  ASSERT_UINT(info[3], or_msg_type);
  info.GetReturnValue().Set(
    mrmailbox_get_chat_media(mailbox->state, contact_id)
  )
}

NAN_METHOD(mrmailbox_get_next_media) {
  ASSERT_UNWRAP(info[0], mailbox, MrMailboxWrap);
  ASSERT_UINT(info[1], curr_msg_id);
  ASSERT_UINT(info[2], dir);
  info.GetReturnValue().Set(
    Nan::New<v8::Number>(mrmailbox_get_next_media(mailbox->state, curr_msg_id, dir))
  )
}

NAN_METHOD(mrmailbox_get_chat_contacts) {
  ASSERT_UNWRAP(info[0], mailbox, MrMailboxWrap);
  ASSERT_UINT(info[1], chat_id);
  info.GetReturnValue().Set(
    mrmailbox_get_next_media(mailbox->state, chat_id)
  )
}

NAN_METHOD(mrmailbox_get_fresh_msgs) {
  ASSERT_UNWRAP(info[0], mailbox, MrMailboxWrap);
  info.GetReturnValue().Set(
    mrmailbox_get_fresh_msgs(mailbox->state)
  )
}

NAN_METHOD(mrmailbox_search_msgs) {
  ASSERT_UNWRAP(info[0], mailbox, MrMailboxWrap);
  ASSERT_UINT(info[1], chat_id);
  v8::String::Utf8Value query(info[2]);
  info.GetReturnValue().Set(
    mrmailbox_search_msgs(mailbox->state, chat_id, *query)
  )
}

NAN_METHOD(mrmailbox_set_draft) {
  ASSERT_UNWRAP(info[0], mailbox, MrMailboxWrap);
  ASSERT_UINT(info[1], chat_id);
  v8::String::Utf8Value msg(info[2]);
  info.GetReturnValue().Set(
    mrmailbox_set_draft(mailbox->state, chat_id, *msg)
  )
}

NAN_METHOD(mrmailbox_get_total_msg_count) {
  ASSERT_UNWRAP(info[0], mailbox, MrMailboxWrap);
  ASSERT_UINT(info[1], chat_id);
  info.GetReturnValue().Set(
    Nan::New<v8::Number>(mrmailbox_get_total_msg_count(mailbox->state, chat_id))
  )
}

NAN_METHOD(mrmailbox_get_fresh_msg_count) {
  ASSERT_UNWRAP(info[0], mailbox, MrMailboxWrap);
  ASSERT_UINT(info[1], chat_id);
  info.GetReturnValue().Set(
    Nan::New<v8::Number>(mrmailbox_get_fresh_msg_count(mailbox->state, chat_id))
  )
}

NAN_METHOD(mrmailbox_archive_chat) {
  ASSERT_UNWRAP(info[0], mailbox, MrMailboxWrap);
  ASSERT_UINT(info[1], chat_id);
  mrmailbox_archive_chat(mailbox->state, chat_id)
}

NAN_METHOD(mrmailbox_delete_chat) {
  ASSERT_UNWRAP(info[0], mailbox, MrMailboxWrap);
  ASSERT_UINT(info[1], chat_id);
  mrmailbox_delete_chat(mailbox->state, chat_id)
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
  EXPORT_FUNCTION(mrmailbox_unref);
  EXPORT_FUNCTION(mrmailbox_open);
  EXPORT_FUNCTION(mrmailbox_close);
  EXPORT_FUNCTION(mrmailbox_is_open);
  EXPORT_FUNCTION(mrmailbox_heartbeat);
  EXPORT_FUNCTION(mrmailbox_get_version_str);
  EXPORT_FUNCTION(mrmailbox_get_info);
  EXPORT_FUNCTION(mrmailbox_set_config);
  EXPORT_FUNCTION(mrmailbox_get_config);
  EXPORT_FUNCTION(mrmailbox_set_config_int);
  EXPORT_FUNCTION(mrmailbox_get_config_int);
  EXPORT_FUNCTION(mrmailbox_configure_and_connect);
  EXPORT_FUNCTION(mrmailbox_connect);
  EXPORT_FUNCTION(mrmailbox_disconnect);
  EXPORT_FUNCTION(mrmailbox_create_chat_by_contact_id);
  EXPORT_FUNCTION(mrmailbox_send_text_msg);
  EXPORT_FUNCTION(mrmailbox_get_chat_msgs);
  EXPORT_FUNCTION(mrmailbox_get_chatlist);
  EXPORT_FUNCTION(mrmailbox_get_chat);
  EXPORT_FUNCTION(mrmailbox_get_msg);
  EXPORT_FUNCTION(mrmailbox_marknoticed_chat);
  EXPORT_FUNCTION(mrmailbox_get_chat_id_by_contact_id);
  EXPORT_FUNCTION(mrmailbox_get_chat_media);
  EXPORT_FUNCTION(mrmailbox_get_next_media);
  EXPORT_FUNCTION(mrmailbox_get_chat_contacts);
  EXPORT_FUNCTION(mrmailbox_get_fresh_msgs);
  EXPORT_FUNCTION(mrmailbox_search_msgs);
  EXPORT_FUNCTION(mrmailbox_set_draft);
  EXPORT_FUNCTION(mrmailbox_get_total_msg_count);
  EXPORT_FUNCTION(mrmailbox_get_fresh_msg_count);
  EXPORT_FUNCTION(mrmailbox_archive_chat);
  EXPORT_FUNCTION(mrmailbox_delete_chat);

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
