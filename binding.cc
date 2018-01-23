#include <mrmailbox.h>
#include <array>
#include <iostream>
#include "src/macros.h"
#include "src/mrmailbox_wrap.h"
#include "src/mrcontact_wrap.h"
#include "src/mrarray_wrap.h"
#include "src/mrmailbox_wrap.h"
#include "src/mrchatlist_wrap.h"
#include "src/mrmsg_wrap.h"
#include "src/mrchat_wrap.h"

/**
 * mrmailbox
 **/

struct delta_data {
  int event;
  uintptr_t data1;
  uintptr_t data2;
};

uv_async_t async;
Nan::Callback *cbPeriodic;

void asyncmsg(uv_async_t* handle) {
  delta_data *data = ((delta_data*)handle->data);
  std::cout << "async\n";
  Nan::HandleScope scope;

  v8::Local<v8::Value> argv[] = {};
  printf("switching event %d\n", data->event);

  std::cout << "Put event in\n";
  argv[0] = LOCAL_NUMBER(data->event);

  std::cout << "initialize local string\n";
  v8::Local<v8::Value> ZERO = LOCAL_NUMBER(0);
  std::cout << "Initialize ZERO\n";
  switch (data->event) {
    case 100:
    case 200:
    case 300:
    case 400:
      argv[1] = ZERO;
      argv[2] = LOCAL_STRING((char*)data->data2);
      break;
    case 2000:
    case 2005:
    case 2010:
    case 2015:
    case 2020:
    case 2041:
    case 2091:
    case 2110:
      argv[1] = LOCAL_NUMBER(data->data1);
      argv[2] = LOCAL_NUMBER(data->data2);
      break;
    case 2030:
    case 2052:
    case 2100:
      argv[1] = LOCAL_STRING((char*)data->data1);
      argv[2] = ZERO;
      break;
    default:
      argv[1] = ZERO;
      argv[2] = ZERO;
      break;
  }
  std::cout << "Sending vector data\n";
  cbPeriodic->Call(3, argv);
}


uintptr_t my_delta_handler(mrmailbox_t* mailbox, int event, uintptr_t data1, uintptr_t data2)
{
  void *ptr = malloc(sizeof(delta_data));
  ((delta_data*)ptr)->event = event;
  ((delta_data*)ptr)->data1 = data1;
  ((delta_data*)ptr)->data2 = data2;
  async.data = ptr;
  uv_async_send(&async);
  printf("got event %d\n", event);
  return 0;
}

NAN_METHOD(mrmailbox_new) {
  cbPeriodic = new Nan::Callback(info[0].As<v8::Function>());
  uv_loop_t* loop = uv_default_loop();
  uv_async_init(loop, &async, asyncmsg);
  info.GetReturnValue().Set(MrMailboxWrap::NewInstance(my_delta_handler));
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
  info.GetReturnValue().Set(Nan::New<v8::String>(mrmailbox_get_config(mailbox->state, *key, *def)).ToLocalChecked());
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
  info.GetReturnValue().Set(Nan::New<v8::String>(mrmailbox_get_info(mailbox->state)).ToLocalChecked());
}

NAN_METHOD(mrmailbox_get_version_str) {
  info.GetReturnValue().Set(Nan::New<v8::String>(mrmailbox_get_version_str()).ToLocalChecked());
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
  ASSERT_UNWRAP(info[0], mailbox, MrMailboxWrap);
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
  ASSERT_UNWRAP(info[0], mailbox, MrMailboxWrap);
  info.GetReturnValue().Set(
    Nan::New<v8::Number>(mrmailbox_is_open(mailbox->state))
  );
}

NAN_METHOD(mrmailbox_configure_and_connect) {
  ASSERT_UNWRAP(info[0], mailbox, MrMailboxWrap);
  info.GetReturnValue().Set(
    Nan::New<v8::Number>(mrmailbox_configure_and_connect(mailbox->state))
  );
}

NAN_METHOD(mrmailbox_is_configured) {
  ASSERT_UNWRAP(info[0], mailbox, MrMailboxWrap);
  info.GetReturnValue().Set(
    Nan::New<v8::Number>(mrmailbox_is_configured(mailbox->state))
  );
}

NAN_METHOD(mrmailbox_stop_ongoing_process) {
  ASSERT_UNWRAP(info[0], mailbox, MrMailboxWrap);
  mrmailbox_stop_ongoing_process(mailbox->state);
}

NAN_METHOD(mrmailbox_initiate_key_transfer) {
  ASSERT_UNWRAP(info[0], mailbox, MrMailboxWrap)
  info.GetReturnValue().Set(
    Nan::New<v8::String>(mrmailbox_initiate_key_transfer(mailbox->state)).ToLocalChecked()
  );
}

NAN_METHOD(mrmailbox_continue_key_transfer) {
  ASSERT_UNWRAP(info[0], mailbox, MrMailboxWrap);
  ASSERT_UINT(info[1], msg_id);
  v8::String::Utf8Value setup_code(info[2]);
  info.GetReturnValue().Set(
    Nan::New<v8::Number>(mrmailbox_continue_key_transfer(mailbox->state, msg_id, *setup_code))
  );
}

NAN_METHOD(mrmailbox_imex) {
  ASSERT_UNWRAP(info[0], mailbox, MrMailboxWrap);
  ASSERT_UINT(info[1], what);
  v8::String::Utf8Value param_one(info[2]);
  v8::String::Utf8Value param_two(info[3]);
  info.GetReturnValue().Set(
    Nan::New<v8::Number>(mrmailbox_imex(mailbox->state, what, *param_one, *param_two))
  );
}

NAN_METHOD(mrmailbox_imex_has_backup) {
  ASSERT_UNWRAP(info[0], mailbox, MrMailboxWrap);
  v8::String::Utf8Value dir_name(info[1]);
  info.GetReturnValue().Set(
    Nan::New<v8::String>(mrmailbox_imex_has_backup(mailbox->state, *dir_name)).ToLocalChecked()
  );
}

NAN_METHOD(mrmailbox_check_password) {
  ASSERT_UNWRAP(info[0], mailbox, MrMailboxWrap);
  v8::String::Utf8Value test_pw(info[1]);
  info.GetReturnValue().Set(
    Nan::New<v8::Number>(mrmailbox_check_password(mailbox->state, *test_pw))
  );
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
    MrArrayWrap::NewInstance(mrmailbox_get_chat_msgs(mailbox->state, chat_id, flags, markerbefore))
  );
}

NAN_METHOD(mrmailbox_get_msg) {
  ASSERT_UNWRAP(info[0], mailbox, MrMailboxWrap);
  ASSERT_UINT(info[1], msg_id);
  info.GetReturnValue().Set(
    MrMsgWrap::NewInstance(mrmailbox_get_msg(mailbox->state, msg_id))
  );
}

NAN_METHOD(mrmailbox_unref) {
  ASSERT_UNWRAP(info[0], mailbox, MrMailboxWrap);
  uv_close((uv_handle_t*) &async, NULL);
  mrmailbox_unref(mailbox->state);
}

NAN_METHOD(mrmailbox_get_chatlist) {
  ASSERT_UNWRAP(info[0], mailbox, MrMailboxWrap);
  ASSERT_UINT(info[1], listflags);
  v8::String::Utf8Value query(info[2]);
  info.GetReturnValue().Set(
    MrChatListWrap::NewInstance(mrmailbox_get_chatlist(mailbox->state, listflags, *query))
  );
}

NAN_METHOD(mrmailbox_get_chat) {
  ASSERT_UNWRAP(info[0], mailbox, MrMailboxWrap);
  ASSERT_UINT(info[1], chat_id);
  info.GetReturnValue().Set(
    MrChatWrap::NewInstance(mrmailbox_get_chat(mailbox->state, chat_id))
  );
}

NAN_METHOD(mrmailbox_marknoticed_chat) {
  ASSERT_UNWRAP(info[0], mailbox, MrMailboxWrap);
  ASSERT_UINT(info[1], chat_id);
  mrmailbox_marknoticed_chat(mailbox->state, chat_id);
}

NAN_METHOD(mrmailbox_get_chat_id_by_contact_id) {
  ASSERT_UNWRAP(info[0], mailbox, MrMailboxWrap);
  ASSERT_UINT(info[1], contact_id);
  info.GetReturnValue().Set(
    Nan::New<v8::Number>(mrmailbox_get_chat_id_by_contact_id(mailbox->state, contact_id))
  );
}

NAN_METHOD(mrmailbox_get_chat_media) {
  ASSERT_UNWRAP(info[0], mailbox, MrMailboxWrap);
  ASSERT_UINT(info[1], chat_id);
  ASSERT_UINT(info[2], msg_type);
  ASSERT_UINT(info[3], or_msg_type);
  info.GetReturnValue().Set(
    MrArrayWrap::NewInstance(mrmailbox_get_chat_media(mailbox->state, chat_id, msg_type, or_msg_type))
  );
}

NAN_METHOD(mrmailbox_get_next_media) {
  ASSERT_UNWRAP(info[0], mailbox, MrMailboxWrap);
  ASSERT_UINT(info[1], curr_msg_id);
  ASSERT_UINT(info[2], dir);
  info.GetReturnValue().Set(
    Nan::New<v8::Number>(mrmailbox_get_next_media(mailbox->state, curr_msg_id, dir))
  );
}

NAN_METHOD(mrmailbox_get_chat_contacts) {
  ASSERT_UNWRAP(info[0], mailbox, MrMailboxWrap);
  ASSERT_UINT(info[1], chat_id);
  info.GetReturnValue().Set(
    MrArrayWrap::NewInstance(mrmailbox_get_chat_contacts(mailbox->state, chat_id))
  );
}

NAN_METHOD(mrmailbox_get_fresh_msgs) {
  ASSERT_UNWRAP(info[0], mailbox, MrMailboxWrap);
  mrarray_t *msglist = mrmailbox_get_fresh_msgs(mailbox->state);
  info.GetReturnValue().Set(MrArrayWrap::NewInstance(msglist));
}

NAN_METHOD(mrmailbox_search_msgs) {
  ASSERT_UNWRAP(info[0], mailbox, MrMailboxWrap);
  ASSERT_UINT(info[1], chat_id);
  v8::String::Utf8Value query(info[2]);
  mrarray_t *msglist = mrmailbox_search_msgs(mailbox->state, chat_id, *query);
  info.GetReturnValue().Set(MrArrayWrap::NewInstance(msglist));
}

NAN_METHOD(mrmailbox_set_draft) {
  ASSERT_UNWRAP(info[0], mailbox, MrMailboxWrap);
  ASSERT_UINT(info[1], chat_id);
  v8::String::Utf8Value msg(info[2]);
  mrmailbox_set_draft(mailbox->state, chat_id, *msg);
}

NAN_METHOD(mrmailbox_get_total_msg_count) {
  ASSERT_UNWRAP(info[0], mailbox, MrMailboxWrap);
  ASSERT_UINT(info[1], chat_id);
  info.GetReturnValue().Set(
    Nan::New<v8::Number>(mrmailbox_get_total_msg_count(mailbox->state, chat_id))
  );
}

NAN_METHOD(mrmailbox_get_fresh_msg_count) {
  ASSERT_UNWRAP(info[0], mailbox, MrMailboxWrap);
  ASSERT_UINT(info[1], chat_id);
  info.GetReturnValue().Set(
    Nan::New<v8::Number>(mrmailbox_get_fresh_msg_count(mailbox->state, chat_id))
  );
}

NAN_METHOD(mrmailbox_archive_chat) {
  ASSERT_UNWRAP(info[0], mailbox, MrMailboxWrap);
  ASSERT_UINT(info[1], chat_id);
  ASSERT_UINT(info[2], archive);
  mrmailbox_archive_chat(mailbox->state, chat_id, archive);
}

NAN_METHOD(mrmailbox_delete_chat) {
  ASSERT_UNWRAP(info[0], mailbox, MrMailboxWrap);
  ASSERT_UINT(info[1], chat_id);
  mrmailbox_delete_chat(mailbox->state, chat_id);
}

NAN_METHOD(mrmailbox_send_image_msg) {
  ASSERT_UNWRAP(info[0], mailbox, MrMailboxWrap);
  ASSERT_UINT(info[1], chat_id);
  v8::String::Utf8Value file(info[2]);
  v8::String::Utf8Value filemime(info[3]);
  ASSERT_UINT(info[4], width);
  ASSERT_UINT(info[5], height);
  info.GetReturnValue().Set(
    Nan::New<v8::Number>(mrmailbox_send_image_msg(mailbox->state, chat_id, *file, *filemime, width, height))
  );
}

NAN_METHOD(mrmailbox_send_video_msg) {
  ASSERT_UNWRAP(info[0], mailbox, MrMailboxWrap);
  ASSERT_UINT(info[1], chat_id);
  v8::String::Utf8Value file(info[2]);
  v8::String::Utf8Value filemime(info[3]);
  ASSERT_UINT(info[4], width);
  ASSERT_UINT(info[5], height);
  ASSERT_UINT(info[6], duration);
  info.GetReturnValue().Set(
    Nan::New<v8::Number>(mrmailbox_send_video_msg(mailbox->state, chat_id, *file, *filemime, width, height, duration))
  );
}

NAN_METHOD(mrmailbox_send_voice_msg) {
  ASSERT_UNWRAP(info[0], mailbox, MrMailboxWrap);
  ASSERT_UINT(info[1], chat_id);
  v8::String::Utf8Value file(info[2]);
  v8::String::Utf8Value filemime(info[3]);
  ASSERT_UINT(info[4], duration);
  info.GetReturnValue().Set(
    Nan::New<v8::Number>(mrmailbox_send_voice_msg(mailbox->state, chat_id, *file, *filemime, duration))
  );
}

NAN_METHOD(mrmailbox_send_audio_msg) {
  ASSERT_UNWRAP(info[0], mailbox, MrMailboxWrap);
  ASSERT_UINT(info[1], chat_id);
  v8::String::Utf8Value file(info[2]);
  v8::String::Utf8Value filemime(info[3]);
  ASSERT_UINT(info[4], duration);
  v8::String::Utf8Value author(info[5]);
  v8::String::Utf8Value trackname(info[6]);
  info.GetReturnValue().Set(
    Nan::New<v8::Number>(mrmailbox_send_audio_msg(mailbox->state, chat_id, *file, *filemime, duration, *author, *trackname))
  );
}

NAN_METHOD(mrmailbox_send_file_msg) {
  ASSERT_UNWRAP(info[0], mailbox, MrMailboxWrap);
  ASSERT_UINT(info[1], chat_id);
  v8::String::Utf8Value file(info[2]);
  v8::String::Utf8Value filemime(info[3]);
  info.GetReturnValue().Set(
    Nan::New<v8::Number>(mrmailbox_send_file_msg(mailbox->state, chat_id, *file, *filemime))
  );
}

NAN_METHOD(mrmailbox_send_vcard_msg) {
  ASSERT_UNWRAP(info[0], mailbox, MrMailboxWrap);
  ASSERT_UINT(info[1], chat_id);
  ASSERT_UINT(info[2], contact_id);
  info.GetReturnValue().Set(
    Nan::New<v8::Number>(mrmailbox_send_vcard_msg(mailbox->state, chat_id, contact_id))
  );
}

NAN_METHOD(mrmailbox_create_group_chat) {
  ASSERT_UNWRAP(info[0], mailbox, MrMailboxWrap);
  v8::String::Utf8Value chatname(info[1]);
  info.GetReturnValue().Set(
    Nan::New<v8::Number>(mrmailbox_create_group_chat(mailbox->state, *chatname))
  );
}

NAN_METHOD(mrmailbox_set_chat_name) {
  ASSERT_UNWRAP(info[0], mailbox, MrMailboxWrap);
  ASSERT_UINT(info[1], chat_id);
  v8::String::Utf8Value new_name(info[2]);
  info.GetReturnValue().Set(
    Nan::New<v8::Number>(mrmailbox_set_chat_name(mailbox->state, chat_id, *new_name))
  );
}

NAN_METHOD(mrmailbox_set_chat_profile_image) {
  ASSERT_UNWRAP(info[0], mailbox, MrMailboxWrap);
  ASSERT_UINT(info[1], chat_id);
  v8::String::Utf8Value new_image(info[2]);
  info.GetReturnValue().Set(
    Nan::New<v8::Number>(mrmailbox_set_chat_profile_image(mailbox->state, chat_id, *new_image))
  );
}

NAN_METHOD(mrmailbox_is_contact_in_chat) {
  ASSERT_UNWRAP(info[0], mailbox, MrMailboxWrap);
  ASSERT_UINT(info[1], chat_id);
  ASSERT_UINT(info[2], contact_id);
  info.GetReturnValue().Set(
    Nan::New<v8::Number>(mrmailbox_is_contact_in_chat(mailbox->state, chat_id, contact_id))
  );
}

NAN_METHOD(mrmailbox_add_contact_to_chat) {
  ASSERT_UNWRAP(info[0], mailbox, MrMailboxWrap);
  ASSERT_UINT(info[1], chat_id);
  ASSERT_UINT(info[2], contact_id);
  info.GetReturnValue().Set(
    Nan::New<v8::Number>(mrmailbox_add_contact_to_chat(mailbox->state, chat_id, contact_id))
  );
}

NAN_METHOD(mrmailbox_remove_contact_from_chat) {
  ASSERT_UNWRAP(info[0], mailbox, MrMailboxWrap);
  ASSERT_UINT(info[1], chat_id);
  ASSERT_UINT(info[2], contact_id);
  info.GetReturnValue().Set(
    Nan::New<v8::Number>(mrmailbox_remove_contact_from_chat(mailbox->state, chat_id, contact_id))
  );
}

NAN_METHOD(mrmailbox_add_address_book) {
  ASSERT_UNWRAP(info[0], mailbox, MrMailboxWrap);
  v8::String::Utf8Value adr_book(info[1]);
  info.GetReturnValue().Set(
    Nan::New<v8::Number>(mrmailbox_add_address_book(mailbox->state, *adr_book))
  );
}

NAN_METHOD(mrmailbox_get_known_contacts) {
  ASSERT_UNWRAP(info[0], mailbox, MrMailboxWrap);
  v8::String::Utf8Value query(info[1]);
  info.GetReturnValue().Set(
    MrArrayWrap::NewInstance(mrmailbox_get_known_contacts(mailbox->state, *query))
  );
}

NAN_METHOD(mrmailbox_get_blocked_contacts) {
  ASSERT_UNWRAP(info[0], mailbox, MrMailboxWrap);
  info.GetReturnValue().Set(
    MrArrayWrap::NewInstance(mrmailbox_get_blocked_contacts(mailbox->state))
  );
}

NAN_METHOD(mrmailbox_get_blocked_count) {
  ASSERT_UNWRAP(info[0], mailbox, MrMailboxWrap);
  info.GetReturnValue().Set(
    Nan::New<v8::Number>(mrmailbox_get_blocked_count(mailbox->state))
  );
}

NAN_METHOD(mrmailbox_get_contact) {
  ASSERT_UNWRAP(info[0], mailbox, MrMailboxWrap);
  ASSERT_UINT(info[1], contact_id);
  info.GetReturnValue().Set(
    MrContactWrap::NewInstance(mrmailbox_get_contact(mailbox->state, contact_id))
  );
}

NAN_METHOD(mrmailbox_marknoticed_contact) {
  ASSERT_UNWRAP(info[0], mailbox, MrMailboxWrap);
  ASSERT_UINT(info[1], contact_id);
  mrmailbox_marknoticed_contact(mailbox->state, contact_id);
}

NAN_METHOD(mrmailbox_block_contact) {
  ASSERT_UNWRAP(info[0], mailbox, MrMailboxWrap);
  ASSERT_UINT(info[1], contact_id);
  ASSERT_UINT(info[2], new_blocking);
  mrmailbox_block_contact(mailbox->state, contact_id, new_blocking);
}

NAN_METHOD(mrmailbox_get_contact_encrinfo) {
  ASSERT_UNWRAP(info[0], mailbox, MrMailboxWrap);
  ASSERT_UINT(info[1], contact_id);
  info.GetReturnValue().Set(Nan::New<v8::String>(mrmailbox_get_contact_encrinfo(mailbox->state, contact_id)).ToLocalChecked());
}

NAN_METHOD(mrmailbox_delete_contact) {
  ASSERT_UNWRAP(info[0], mailbox, MrMailboxWrap);
  ASSERT_UINT(info[1], contact_id);
  info.GetReturnValue().Set(Nan::New<v8::Number>(mrmailbox_delete_contact(mailbox->state, contact_id)));
}

NAN_METHOD(mrmailbox_get_msg_info) {
  ASSERT_UNWRAP(info[0], mailbox, MrMailboxWrap);
  ASSERT_UINT(info[1], msg_id);
  info.GetReturnValue().Set(Nan::New<v8::String>(mrmailbox_get_msg_info(mailbox->state, msg_id)).ToLocalChecked());
}

NAN_METHOD(mrmailbox_forward_msgs) {
  ASSERT_UNWRAP(info[0], mailbox, MrMailboxWrap);
  const uint32_t msg_ids = Nan::To<uint32_t>(info[1]).FromJust();
  ASSERT_UINT(info[2], msg_cnt);
  ASSERT_UINT(info[3], chat_id);
  mrmailbox_forward_msgs(mailbox->state, &msg_ids, msg_cnt, chat_id);
}

NAN_METHOD(mrmailbox_star_msgs) {
  ASSERT_UNWRAP(info[0], mailbox, MrMailboxWrap);
  const uint32_t msg_ids = Nan::To<uint32_t>(info[1]).FromJust();
  ASSERT_UINT(info[2], msg_cnt);
  ASSERT_UINT(info[3], chat_id);
  mrmailbox_star_msgs(mailbox->state, &msg_ids, msg_cnt, chat_id);
}

NAN_METHOD(mrmailbox_delete_msgs) {
  ASSERT_UNWRAP(info[0], mailbox, MrMailboxWrap);
  const uint32_t msg_ids = Nan::To<uint32_t>(info[1]).FromJust();
  ASSERT_UINT(info[2], msg_cnt);
  mrmailbox_delete_msgs(mailbox->state, &msg_ids, msg_cnt);
}

NAN_METHOD(mrmailbox_markseen_msgs) {
  ASSERT_UNWRAP(info[0], mailbox, MrMailboxWrap);
  const uint32_t msg_ids = Nan::To<uint32_t>(info[1]).FromJust();
  ASSERT_UINT(info[2], msg_cnt);
  mrmailbox_markseen_msgs(mailbox->state, &msg_ids, msg_cnt);
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
  info.GetReturnValue().Set(Nan::New<v8::String>(mrmsg_get_text(msg->state)).ToLocalChecked());
}

NAN_METHOD(mrmsg_unref) {
  ASSERT_UNWRAP(info[0], msg, MrMsgWrap);
  mrmsg_unref(msg->state);
}

/**
 * mrchat
 */

NAN_METHOD(mrchat_unref) {
  ASSERT_UNWRAP(info[0], chat, MrChatWrap);
  mrchat_unref(chat->state);
}

NAN_METHOD(mrchat_is_unpromoted) {
  ASSERT_UNWRAP(info[0], chat, MrChatWrap);
  info.GetReturnValue().Set(Nan::New<v8::Number>(mrchat_is_unpromoted(chat->state)));
}

NAN_METHOD(mrchat_get_draft) {
  ASSERT_UNWRAP(info[0], chat, MrChatWrap);
  const char *text = mrchat_get_draft(chat->state);
  info.GetReturnValue().Set(Nan::New<v8::String>(text).ToLocalChecked());
}

NAN_METHOD(mrchat_get_archived) {
  ASSERT_UNWRAP(info[0], chat, MrChatWrap);
  info.GetReturnValue().Set(Nan::New<v8::Number>(mrchat_get_archived(chat->state)));
}

NAN_METHOD(mrchat_get_profile_image) {
  ASSERT_UNWRAP(info[0], chat, MrChatWrap);
  const char *text = mrchat_get_profile_image(chat->state);
  info.GetReturnValue().Set(Nan::New<v8::String>(text).ToLocalChecked());
}

NAN_METHOD(mrchat_get_subtitle) {
  ASSERT_UNWRAP(info[0], chat, MrChatWrap);
  const char *text = mrchat_get_subtitle(chat->state);
  info.GetReturnValue().Set(Nan::New<v8::String>(text).ToLocalChecked());
}

NAN_METHOD(mrchat_get_name) {
  ASSERT_UNWRAP(info[0], chat, MrChatWrap);
  const char *text = mrchat_get_name(chat->state);
  info.GetReturnValue().Set(Nan::New<v8::String>(text).ToLocalChecked());
}

NAN_METHOD(mrchat_get_type) {
  ASSERT_UNWRAP(info[0], chat, MrChatWrap);
  info.GetReturnValue().Set(Nan::New<v8::Number>(mrchat_get_type(chat->state)));
}

NAN_METHOD(mrchat_is_self_talk) {
  ASSERT_UNWRAP(info[0], chat, MrChatWrap);
  info.GetReturnValue().Set(Nan::New<v8::Number>(mrchat_is_self_talk(chat->state)));
}

/**
 * mrcontact
 */

NAN_METHOD(mrcontact_unref) {
  ASSERT_UNWRAP(info[0], obj, MrContactWrap);
  mrcontact_unref(obj->state);
}

NAN_METHOD(mrcontact_is_blocked) {
  ASSERT_UNWRAP(info[0], obj, MrContactWrap);
  info.GetReturnValue().Set(Nan::New<v8::Number>(mrcontact_is_blocked(obj->state)));
}

NAN_METHOD(mrcontact_get_addr) {
  ASSERT_UNWRAP(info[0], obj, MrContactWrap);
  const char *text = mrcontact_get_addr(obj->state);
  info.GetReturnValue().Set(Nan::New<v8::String>(text).ToLocalChecked());
}

NAN_METHOD(mrcontact_get_name) {
  ASSERT_UNWRAP(info[0], obj, MrContactWrap);
  const char *text = mrcontact_get_name(obj->state);
  info.GetReturnValue().Set(Nan::New<v8::String>(text).ToLocalChecked());
}

NAN_METHOD(mrcontact_get_display_name) {
  ASSERT_UNWRAP(info[0], obj, MrContactWrap);
  const char *text = mrcontact_get_display_name(obj->state);
  info.GetReturnValue().Set(Nan::New<v8::String>(text).ToLocalChecked());
}

NAN_METHOD(mrcontact_get_name_n_addr) {
  ASSERT_UNWRAP(info[0], obj, MrContactWrap);
  const char *text = mrcontact_get_name_n_addr(obj->state);
  info.GetReturnValue().Set(Nan::New<v8::String>(text).ToLocalChecked());
}

NAN_MODULE_INIT(InitAll) {
  MrMailboxWrap::Init();
  MrArrayWrap::Init();
  MrChatWrap::Init();
  MrContactWrap::Init();
  MrChatListWrap::Init();
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
  EXPORT_FUNCTION(mrmailbox_send_image_msg);
  EXPORT_FUNCTION(mrmailbox_send_video_msg);
  EXPORT_FUNCTION(mrmailbox_send_voice_msg);
  EXPORT_FUNCTION(mrmailbox_send_audio_msg);
  EXPORT_FUNCTION(mrmailbox_send_file_msg);
  EXPORT_FUNCTION(mrmailbox_send_vcard_msg);
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
  EXPORT_FUNCTION(mrmailbox_create_group_chat);
  EXPORT_FUNCTION(mrmailbox_set_chat_name);
  EXPORT_FUNCTION(mrmailbox_set_chat_profile_image);
  EXPORT_FUNCTION(mrmailbox_is_contact_in_chat);
  EXPORT_FUNCTION(mrmailbox_add_contact_to_chat);
  EXPORT_FUNCTION(mrmailbox_remove_contact_from_chat);
  EXPORT_FUNCTION(mrmailbox_create_contact);
  EXPORT_FUNCTION(mrmailbox_add_address_book);
  EXPORT_FUNCTION(mrmailbox_get_known_contacts);
  EXPORT_FUNCTION(mrmailbox_get_blocked_contacts);
  EXPORT_FUNCTION(mrmailbox_get_blocked_count);
  EXPORT_FUNCTION(mrmailbox_get_contact);
  EXPORT_FUNCTION(mrmailbox_block_contact);
  EXPORT_FUNCTION(mrmailbox_get_contact_encrinfo);
  EXPORT_FUNCTION(mrmailbox_delete_contact);
  EXPORT_FUNCTION(mrmailbox_get_msg_info);
  EXPORT_FUNCTION(mrmailbox_forward_msgs);
  EXPORT_FUNCTION(mrmailbox_star_msgs);
  EXPORT_FUNCTION(mrmailbox_delete_msgs);
  EXPORT_FUNCTION(mrmailbox_markseen_msgs);
  EXPORT_FUNCTION(mrmailbox_is_configured);
  EXPORT_FUNCTION(mrmailbox_stop_ongoing_process);
  EXPORT_FUNCTION(mrmailbox_initiate_key_transfer);
  EXPORT_FUNCTION(mrmailbox_continue_key_transfer);
  EXPORT_FUNCTION(mrmailbox_imex);
  EXPORT_FUNCTION(mrmailbox_imex_has_backup);
  EXPORT_FUNCTION(mrmailbox_check_password);

  EXPORT_FUNCTION(mrarray_get_cnt);
  EXPORT_FUNCTION(mrarray_get_id);
  EXPORT_FUNCTION(mrarray_unref);

  EXPORT_FUNCTION(mrmsg_get_text);
  EXPORT_FUNCTION(mrmsg_unref);

  EXPORT_FUNCTION(mrchat_get_type);
  EXPORT_FUNCTION(mrchat_get_name);
  EXPORT_FUNCTION(mrchat_get_subtitle);
  EXPORT_FUNCTION(mrchat_get_profile_image);
  EXPORT_FUNCTION(mrchat_get_archived);
  EXPORT_FUNCTION(mrchat_is_unpromoted);
  EXPORT_FUNCTION(mrchat_is_self_talk);
  EXPORT_FUNCTION(mrchat_unref);

  EXPORT_FUNCTION(mrcontact_get_addr);
  EXPORT_FUNCTION(mrcontact_get_name);
  EXPORT_FUNCTION(mrcontact_get_display_name);
  EXPORT_FUNCTION(mrcontact_get_name_n_addr);
  EXPORT_FUNCTION(mrcontact_is_blocked);
  EXPORT_FUNCTION(mrcontact_unref);

  EXPORT_NUMBER(MR_GCL_ARCHIVED_ONLY)
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
