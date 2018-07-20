#include <deltachat.h>
#include <array>
#include <iostream>
#include "src/dc_context_wrap.h"
#include "src/dc_contact_wrap.h"
#include "src/dc_array_wrap.h"
#include "src/dc_chatlist_wrap.h"
#include "src/dc_msg_wrap.h"
#include "src/dc_chat_wrap.h"
#include "src/macros.h"

/**
 * deltachat
 **/

Nan::Callback *cbPeriodic;

uintptr_t my_delta_handler(dc_context_t* mailbox, int event, uintptr_t data1, uintptr_t data2)
{
  v8::Local<v8::Value> argv[3];

  argv[0] = LOCAL_NUMBER(event);
  switch (event) {
    case DC_EVENT_WARNING:
      printf("DC_EVENT_WARNING %d %s\n", event, (const char*) data2);
    case DC_EVENT_ERROR:
      printf("DC_EVENT_ERROR %d %s\n", event, (const char*) data2);
    case DC_EVENT_INFO:
      printf("DC_EVENT_INFO %s\n", (const char*) data2);
    case DC_EVENT_CONTACTS_CHANGED:
      argv[1] = Nan::New<v8::Integer>((uint32_t) data1); 
      argv[2] = Nan::New<v8::Number>(0);
      break;
    default:
      argv[1] = Nan::New<v8::Number>(0);
      argv[2] = Nan::New<v8::Number>(0);
  }
  if (cbPeriodic) {
    v8::Local<v8::Value> val = cbPeriodic->Call(3, argv);
    int32_t ret = val->IntegerValue();
    return ret;
  }

  return 0;
}

NAN_METHOD(dc_context_new) {
  cbPeriodic = new Nan::Callback(info[0].As<v8::Function>());

  v8::Local<v8::Value> instance = DcContextWrap::NewInstance(my_delta_handler);
  DcContextWrap *context = Nan::ObjectWrap::Unwrap<DcContextWrap>(instance->ToObject());

  info.GetReturnValue().Set(instance);
}


NAN_METHOD(perform_imap_jobs) {
  ASSERT_UNWRAP(info[0], mailbox, DcContextWrap);
  printf("performing imap jobs\n");
  dc_perform_imap_jobs(mailbox->state);
}

NAN_METHOD(perform_imap_fetch) {
  ASSERT_UNWRAP(info[0], mailbox, DcContextWrap);
  printf("performing imap fetch\n");
  dc_perform_imap_fetch(mailbox->state);
}

NAN_METHOD(perform_imap_idle) {
  ASSERT_UNWRAP(info[0], mailbox, DcContextWrap);
  printf("performing imap idle\n");
  dc_perform_imap_idle(mailbox->state);
}

NAN_METHOD(perform_smtp_jobs) {
  ASSERT_UNWRAP(info[0], mailbox, DcContextWrap);
  printf("performing smtp jobs\n");
  dc_perform_smtp_jobs(mailbox->state);
}

NAN_METHOD(perform_smtp_idle) {
  ASSERT_UNWRAP(info[0], mailbox, DcContextWrap);
  printf("performing smtp idle\n");
  dc_perform_smtp_idle(mailbox->state);
}

NAN_METHOD(dc_set_config) {
  ASSERT_UNWRAP(info[0], mailbox, DcContextWrap);
  v8::String::Utf8Value key(info[1]);
  v8::String::Utf8Value value(info[2]);
  dc_set_config(mailbox->state, *key, *value);
}

NAN_METHOD(dc_set_config_int) {
  ASSERT_UNWRAP(info[0], mailbox, DcContextWrap);
  v8::String::Utf8Value key(info[1]);
  ASSERT_UINT(info[2], value);
  dc_set_config_int(mailbox->state, *key, value);
}

NAN_METHOD(dc_get_config) {
  ASSERT_UNWRAP(info[0], mailbox, DcContextWrap);
  v8::String::Utf8Value key(info[1]);
  v8::String::Utf8Value def(info[2]);
  info.GetReturnValue().Set(Nan::New<v8::String>(dc_get_config(mailbox->state, *key, *def)).ToLocalChecked());
}

NAN_METHOD(dc_get_config_int) {
  ASSERT_UNWRAP(info[0], mailbox, DcContextWrap);
  v8::String::Utf8Value key(info[1]);
  ASSERT_UINT(info[2], def);
  info.GetReturnValue().Set(
    Nan::New<v8::Number>(dc_get_config_int(mailbox->state, *key, def))
  );
}

NAN_METHOD(dc_get_info) {
  ASSERT_UNWRAP(info[0], mailbox, DcContextWrap);
  info.GetReturnValue().Set(Nan::New<v8::String>(dc_get_info(mailbox->state)).ToLocalChecked());
}

NAN_METHOD(dc_get_version_str) {
  info.GetReturnValue().Set(Nan::New<v8::String>(dc_get_version_str()).ToLocalChecked());
}


NAN_METHOD(dc_open) {
  ASSERT_UNWRAP(info[0], mailbox, DcContextWrap);
  v8::String::Utf8Value dbfile(info[1]);
  v8::String::Utf8Value blobdir(info[2]);
  info.GetReturnValue().Set(
    Nan::New<v8::Number>(dc_open(mailbox->state, *dbfile, *blobdir))
  );
}

NAN_METHOD(dc_close) {
  ASSERT_UNWRAP(info[0], mailbox, DcContextWrap);
  dc_close(mailbox->state);
}

NAN_METHOD(dc_is_open) {
  ASSERT_UNWRAP(info[0], mailbox, DcContextWrap);
  info.GetReturnValue().Set(
    Nan::New<v8::Number>(dc_is_open(mailbox->state))
  );
}

NAN_METHOD(dc_configure) {
  ASSERT_UNWRAP(info[0], mailbox, DcContextWrap);
  dc_configure(mailbox->state);
}

NAN_METHOD(dc_is_configured) {
  ASSERT_UNWRAP(info[0], mailbox, DcContextWrap);
  info.GetReturnValue().Set(
    Nan::New<v8::Number>(dc_is_configured(mailbox->state))
  );
}

NAN_METHOD(dc_stop_ongoing_process) {
  ASSERT_UNWRAP(info[0], mailbox, DcContextWrap);
  dc_stop_ongoing_process(mailbox->state);
}

NAN_METHOD(dc_initiate_key_transfer) {
  ASSERT_UNWRAP(info[0], mailbox, DcContextWrap)
  info.GetReturnValue().Set(
    Nan::New<v8::String>(dc_initiate_key_transfer(mailbox->state)).ToLocalChecked()
  );
}

NAN_METHOD(dc_continue_key_transfer) {
  ASSERT_UNWRAP(info[0], mailbox, DcContextWrap);
  ASSERT_UINT(info[1], msg_id);
  v8::String::Utf8Value setup_code(info[2]);
  info.GetReturnValue().Set(
    Nan::New<v8::Number>(dc_continue_key_transfer(mailbox->state, msg_id, *setup_code))
  );
}

NAN_METHOD(dc_imex) {
  ASSERT_UNWRAP(info[0], mailbox, DcContextWrap);
  ASSERT_UINT(info[1], what);
  v8::String::Utf8Value param_one(info[2]);
  v8::String::Utf8Value param_two(info[3]);
  dc_imex(mailbox->state, what, *param_one, *param_two);
}

NAN_METHOD(dc_imex_has_backup) {
  ASSERT_UNWRAP(info[0], mailbox, DcContextWrap);
  v8::String::Utf8Value dir_name(info[1]);
  info.GetReturnValue().Set(
    Nan::New<v8::String>(dc_imex_has_backup(mailbox->state, *dir_name)).ToLocalChecked()
  );
}

NAN_METHOD(dc_check_password) {
  ASSERT_UNWRAP(info[0], mailbox, DcContextWrap);
  v8::String::Utf8Value test_pw(info[1]);
  info.GetReturnValue().Set(
    Nan::New<v8::Number>(dc_check_password(mailbox->state, *test_pw))
  );
}

NAN_METHOD(dc_create_contact) {
  ASSERT_UNWRAP(info[0], mailbox, DcContextWrap);
  v8::String::Utf8Value name(info[1]);
  v8::String::Utf8Value addr(info[2]);

  info.GetReturnValue().Set(
    Nan::New<v8::Number>(dc_create_contact(mailbox->state, *name, *addr))
  );
}

NAN_METHOD(dc_create_chat_by_contact_id) {
  ASSERT_UNWRAP(info[0], mailbox, DcContextWrap);
  ASSERT_UINT(info[1], contact_id);
  info.GetReturnValue().Set(
    Nan::New<v8::Number>(dc_create_chat_by_contact_id(mailbox->state, contact_id))
  );
}

NAN_METHOD(dc_send_text_msg) {
  ASSERT_UNWRAP(info[0], mailbox, DcContextWrap);
  ASSERT_UINT(info[1], chat_id);
  v8::String::Utf8Value text_to_send(info[2]);
  info.GetReturnValue().Set(
    Nan::New<v8::Number>(dc_send_text_msg(mailbox->state, chat_id, *text_to_send))
  );
}

NAN_METHOD(dc_get_chat_msgs) {
  ASSERT_UNWRAP(info[0], mailbox, DcContextWrap);
  ASSERT_UINT(info[1], chat_id);
  ASSERT_UINT(info[2], flags);
  ASSERT_UINT(info[3], markerbefore);
  info.GetReturnValue().Set(
    DcArrayWrap::NewInstance(dc_get_chat_msgs(mailbox->state, chat_id, flags, markerbefore))
  );
}

NAN_METHOD(dc_get_msg) {
  ASSERT_UNWRAP(info[0], mailbox, DcContextWrap);
  ASSERT_UINT(info[1], msg_id);
  info.GetReturnValue().Set(
    DcMsgWrap::NewInstance(dc_get_msg(mailbox->state, msg_id))
  );
}

NAN_METHOD(dc_context_unref) {
  ASSERT_UNWRAP(info[0], mailbox, DcContextWrap);
  dc_context_unref(mailbox->state);
}

NAN_METHOD(dc_get_chatlist) {
  ASSERT_UNWRAP(info[0], mailbox, DcContextWrap);
  ASSERT_UINT(info[1], listflags);
  v8::String::Utf8Value query(info[2]);
  ASSERT_UINT(info[3], query_id);
  info.GetReturnValue().Set(
    DcChatListWrap::NewInstance(dc_get_chatlist(mailbox->state, listflags, *query, query_id))
  );
}

NAN_METHOD(dc_get_chat) {
  ASSERT_UNWRAP(info[0], mailbox, DcContextWrap);
  ASSERT_UINT(info[1], chat_id);
  info.GetReturnValue().Set(
    DcChatWrap::NewInstance(dc_get_chat(mailbox->state, chat_id))
  );
}

NAN_METHOD(dc_marknoticed_chat) {
  ASSERT_UNWRAP(info[0], mailbox, DcContextWrap);
  ASSERT_UINT(info[1], chat_id);
  dc_marknoticed_chat(mailbox->state, chat_id);
}

NAN_METHOD(dc_get_chat_id_by_contact_id) {
  ASSERT_UNWRAP(info[0], mailbox, DcContextWrap);
  ASSERT_UINT(info[1], contact_id);
  info.GetReturnValue().Set(
    Nan::New<v8::Number>(dc_get_chat_id_by_contact_id(mailbox->state, contact_id))
  );
}

NAN_METHOD(dc_get_chat_media) {
  ASSERT_UNWRAP(info[0], mailbox, DcContextWrap);
  ASSERT_UINT(info[1], chat_id);
  ASSERT_UINT(info[2], msg_type);
  ASSERT_UINT(info[3], or_msg_type);
  info.GetReturnValue().Set(
    DcArrayWrap::NewInstance(dc_get_chat_media(mailbox->state, chat_id, msg_type, or_msg_type))
  );
}

NAN_METHOD(dc_get_next_media) {
  ASSERT_UNWRAP(info[0], mailbox, DcContextWrap);
  ASSERT_UINT(info[1], curr_msg_id);
  ASSERT_UINT(info[2], dir);
  info.GetReturnValue().Set(
    Nan::New<v8::Number>(dc_get_next_media(mailbox->state, curr_msg_id, dir))
  );
}

NAN_METHOD(dc_get_chat_contacts) {
  ASSERT_UNWRAP(info[0], mailbox, DcContextWrap);
  ASSERT_UINT(info[1], chat_id);
  info.GetReturnValue().Set(
    DcArrayWrap::NewInstance(dc_get_chat_contacts(mailbox->state, chat_id))
  );
}

NAN_METHOD(dc_get_fresh_msgs) {
  ASSERT_UNWRAP(info[0], mailbox, DcContextWrap);
  dc_array_t *msglist = dc_get_fresh_msgs(mailbox->state);
  info.GetReturnValue().Set(DcArrayWrap::NewInstance(msglist));
}

NAN_METHOD(dc_search_msgs) {
  ASSERT_UNWRAP(info[0], mailbox, DcContextWrap);
  ASSERT_UINT(info[1], chat_id);
  v8::String::Utf8Value query(info[2]);
  dc_array_t *msglist = dc_search_msgs(mailbox->state, chat_id, *query);
  info.GetReturnValue().Set(DcArrayWrap::NewInstance(msglist));
}

NAN_METHOD(dc_set_text_draft) {
  ASSERT_UNWRAP(info[0], mailbox, DcContextWrap);
  ASSERT_UINT(info[1], chat_id);
  v8::String::Utf8Value msg(info[2]);
  dc_set_text_draft(mailbox->state, chat_id, *msg);
}

NAN_METHOD(dc_get_msg_cnt) {
  ASSERT_UNWRAP(info[0], mailbox, DcContextWrap);
  ASSERT_UINT(info[1], chat_id);
  info.GetReturnValue().Set(
    Nan::New<v8::Number>(dc_get_msg_cnt(mailbox->state, chat_id))
  );
}

NAN_METHOD(dc_get_fresh_msg_cnt) {
  ASSERT_UNWRAP(info[0], mailbox, DcContextWrap);
  ASSERT_UINT(info[1], chat_id);
  info.GetReturnValue().Set(
    Nan::New<v8::Number>(dc_get_fresh_msg_cnt(mailbox->state, chat_id))
  );
}

NAN_METHOD(dc_archive_chat) {
  ASSERT_UNWRAP(info[0], mailbox, DcContextWrap);
  ASSERT_UINT(info[1], chat_id);
  ASSERT_UINT(info[2], archive);
  dc_archive_chat(mailbox->state, chat_id, archive);
}

NAN_METHOD(dc_delete_chat) {
  ASSERT_UNWRAP(info[0], mailbox, DcContextWrap);
  ASSERT_UINT(info[1], chat_id);
  dc_delete_chat(mailbox->state, chat_id);
}

NAN_METHOD(dc_send_image_msg) {
  ASSERT_UNWRAP(info[0], mailbox, DcContextWrap);
  ASSERT_UINT(info[1], chat_id);
  v8::String::Utf8Value file(info[2]);
  v8::String::Utf8Value filemime(info[3]);
  ASSERT_UINT(info[4], width);
  ASSERT_UINT(info[5], height);
  info.GetReturnValue().Set(
    Nan::New<v8::Number>(dc_send_image_msg(mailbox->state, chat_id, *file, *filemime, width, height))
  );
}

NAN_METHOD(dc_send_video_msg) {
  ASSERT_UNWRAP(info[0], mailbox, DcContextWrap);
  ASSERT_UINT(info[1], chat_id);
  v8::String::Utf8Value file(info[2]);
  v8::String::Utf8Value filemime(info[3]);
  ASSERT_UINT(info[4], width);
  ASSERT_UINT(info[5], height);
  ASSERT_UINT(info[6], duration);
  info.GetReturnValue().Set(
    Nan::New<v8::Number>(dc_send_video_msg(mailbox->state, chat_id, *file, *filemime, width, height, duration))
  );
}

NAN_METHOD(dc_send_voice_msg) {
  ASSERT_UNWRAP(info[0], mailbox, DcContextWrap);
  ASSERT_UINT(info[1], chat_id);
  v8::String::Utf8Value file(info[2]);
  v8::String::Utf8Value filemime(info[3]);
  ASSERT_UINT(info[4], duration);
  info.GetReturnValue().Set(
    Nan::New<v8::Number>(dc_send_voice_msg(mailbox->state, chat_id, *file, *filemime, duration))
  );
}

NAN_METHOD(dc_send_audio_msg) {
  ASSERT_UNWRAP(info[0], mailbox, DcContextWrap);
  ASSERT_UINT(info[1], chat_id);
  v8::String::Utf8Value file(info[2]);
  v8::String::Utf8Value filemime(info[3]);
  ASSERT_UINT(info[4], duration);
  v8::String::Utf8Value author(info[5]);
  v8::String::Utf8Value trackname(info[6]);
  info.GetReturnValue().Set(
    Nan::New<v8::Number>(dc_send_audio_msg(mailbox->state, chat_id, *file, *filemime, duration, *author, *trackname))
  );
}

NAN_METHOD(dc_send_file_msg) {
  ASSERT_UNWRAP(info[0], mailbox, DcContextWrap);
  ASSERT_UINT(info[1], chat_id);
  v8::String::Utf8Value file(info[2]);
  v8::String::Utf8Value filemime(info[3]);
  info.GetReturnValue().Set(
    Nan::New<v8::Number>(dc_send_file_msg(mailbox->state, chat_id, *file, *filemime))
  );
}

NAN_METHOD(dc_send_vcard_msg) {
  ASSERT_UNWRAP(info[0], mailbox, DcContextWrap);
  ASSERT_UINT(info[1], chat_id);
  ASSERT_UINT(info[2], contact_id);
  info.GetReturnValue().Set(
    Nan::New<v8::Number>(dc_send_vcard_msg(mailbox->state, chat_id, contact_id))
  );
}

NAN_METHOD(dc_create_group_chat) {
  ASSERT_UNWRAP(info[0], mailbox, DcContextWrap);
  ASSERT_UINT(info[1], verified);
  v8::String::Utf8Value chatname(info[2]);
  info.GetReturnValue().Set(
    Nan::New<v8::Number>(dc_create_group_chat(mailbox->state, verified, *chatname))
  );
}

NAN_METHOD(dc_set_chat_name) {
  ASSERT_UNWRAP(info[0], mailbox, DcContextWrap);
  ASSERT_UINT(info[1], chat_id);
  v8::String::Utf8Value new_name(info[2]);
  info.GetReturnValue().Set(
    Nan::New<v8::Number>(dc_set_chat_name(mailbox->state, chat_id, *new_name))
  );
}

NAN_METHOD(dc_set_chat_profile_image) {
  ASSERT_UNWRAP(info[0], mailbox, DcContextWrap);
  ASSERT_UINT(info[1], chat_id);
  v8::String::Utf8Value new_image(info[2]);
  info.GetReturnValue().Set(
    Nan::New<v8::Number>(dc_set_chat_profile_image(mailbox->state, chat_id, *new_image))
  );
}

NAN_METHOD(dc_is_contact_in_chat) {
  ASSERT_UNWRAP(info[0], mailbox, DcContextWrap);
  ASSERT_UINT(info[1], chat_id);
  ASSERT_UINT(info[2], contact_id);
  info.GetReturnValue().Set(
    Nan::New<v8::Number>(dc_is_contact_in_chat(mailbox->state, chat_id, contact_id))
  );
}

NAN_METHOD(dc_add_contact_to_chat) {
  ASSERT_UNWRAP(info[0], mailbox, DcContextWrap);
  ASSERT_UINT(info[1], chat_id);
  ASSERT_UINT(info[2], contact_id);
  info.GetReturnValue().Set(
    Nan::New<v8::Number>(dc_add_contact_to_chat(mailbox->state, chat_id, contact_id))
  );
}

NAN_METHOD(dc_remove_contact_from_chat) {
  ASSERT_UNWRAP(info[0], mailbox, DcContextWrap);
  ASSERT_UINT(info[1], chat_id);
  ASSERT_UINT(info[2], contact_id);
  info.GetReturnValue().Set(
    Nan::New<v8::Number>(dc_remove_contact_from_chat(mailbox->state, chat_id, contact_id))
  );
}

NAN_METHOD(dc_add_address_book) {
  ASSERT_UNWRAP(info[0], mailbox, DcContextWrap);
  v8::String::Utf8Value adr_book(info[1]);
  info.GetReturnValue().Set(
    Nan::New<v8::Number>(dc_add_address_book(mailbox->state, *adr_book))
  );
}

NAN_METHOD(dc_get_contacts) {
  ASSERT_UNWRAP(info[0], mailbox, DcContextWrap);
  ASSERT_UINT(info[1], listflags);
  v8::String::Utf8Value query(info[2]);
  info.GetReturnValue().Set(
    DcArrayWrap::NewInstance(dc_get_contacts(mailbox->state, listflags, *query))
  );
}

NAN_METHOD(dc_get_blocked_contacts) {
  ASSERT_UNWRAP(info[0], mailbox, DcContextWrap);
  info.GetReturnValue().Set(
    DcArrayWrap::NewInstance(dc_get_blocked_contacts(mailbox->state))
  );
}

NAN_METHOD(dc_get_blocked_cnt) {
  ASSERT_UNWRAP(info[0], mailbox, DcContextWrap);
  info.GetReturnValue().Set(
    Nan::New<v8::Number>(dc_get_blocked_cnt(mailbox->state))
  );
}

NAN_METHOD(dc_get_contact) {
  ASSERT_UNWRAP(info[0], mailbox, DcContextWrap);
  ASSERT_UINT(info[1], contact_id);
  info.GetReturnValue().Set(
    DcContactWrap::NewInstance(dc_get_contact(mailbox->state, contact_id))
  );
}

NAN_METHOD(dc_marknoticed_contact) {
  ASSERT_UNWRAP(info[0], mailbox, DcContextWrap);
  ASSERT_UINT(info[1], contact_id);
  dc_marknoticed_contact(mailbox->state, contact_id);
}

NAN_METHOD(dc_block_contact) {
  ASSERT_UNWRAP(info[0], mailbox, DcContextWrap);
  ASSERT_UINT(info[1], contact_id);
  ASSERT_UINT(info[2], new_blocking);
  dc_block_contact(mailbox->state, contact_id, new_blocking);
}

NAN_METHOD(dc_get_contact_encrinfo) {
  ASSERT_UNWRAP(info[0], mailbox, DcContextWrap);
  ASSERT_UINT(info[1], contact_id);
  info.GetReturnValue().Set(Nan::New<v8::String>(dc_get_contact_encrinfo(mailbox->state, contact_id)).ToLocalChecked());
}

NAN_METHOD(dc_delete_contact) {
  ASSERT_UNWRAP(info[0], mailbox, DcContextWrap);
  ASSERT_UINT(info[1], contact_id);
  info.GetReturnValue().Set(Nan::New<v8::Number>(dc_delete_contact(mailbox->state, contact_id)));
}

NAN_METHOD(dc_get_msg_info) {
  ASSERT_UNWRAP(info[0], mailbox, DcContextWrap);
  ASSERT_UINT(info[1], msg_id);
  info.GetReturnValue().Set(Nan::New<v8::String>(dc_get_msg_info(mailbox->state, msg_id)).ToLocalChecked());
}

NAN_METHOD(dc_forward_msgs) {
  ASSERT_UNWRAP(info[0], mailbox, DcContextWrap);
  const uint32_t msg_ids = Nan::To<uint32_t>(info[1]).FromJust();
  ASSERT_UINT(info[2], msg_cnt);
  ASSERT_UINT(info[3], chat_id);
  dc_forward_msgs(mailbox->state, &msg_ids, msg_cnt, chat_id);
}

NAN_METHOD(dc_star_msgs) {
  ASSERT_UNWRAP(info[0], mailbox, DcContextWrap);
  const uint32_t msg_ids = Nan::To<uint32_t>(info[1]).FromJust();
  ASSERT_UINT(info[2], msg_cnt);
  ASSERT_UINT(info[3], chat_id);
  dc_star_msgs(mailbox->state, &msg_ids, msg_cnt, chat_id);
}

NAN_METHOD(dc_delete_msgs) {
  ASSERT_UNWRAP(info[0], mailbox, DcContextWrap);
  const uint32_t msg_ids = Nan::To<uint32_t>(info[1]).FromJust();
  ASSERT_UINT(info[2], msg_cnt);
  dc_delete_msgs(mailbox->state, &msg_ids, msg_cnt);
}

NAN_METHOD(dc_markseen_msgs) {
  ASSERT_UNWRAP(info[0], mailbox, DcContextWrap);
  const uint32_t msg_ids = Nan::To<uint32_t>(info[1]).FromJust();
  ASSERT_UINT(info[2], msg_cnt);
  dc_markseen_msgs(mailbox->state, &msg_ids, msg_cnt);
}


/**
 * mrarray
 **/

NAN_METHOD(dc_array_get_cnt) {
  ASSERT_UNWRAP(info[0], array, DcArrayWrap);
  info.GetReturnValue().Set(
    Nan::New<v8::Number>(dc_array_get_cnt(array->state))
  );
}

NAN_METHOD(dc_array_get_id) {
  ASSERT_UNWRAP(info[0], array, DcArrayWrap);
  ASSERT_UINT(info[1], i);
  info.GetReturnValue().Set(
    Nan::New<v8::Number>(dc_array_get_id(array->state, i))
  );
}

NAN_METHOD(dc_array_unref) {
  ASSERT_UNWRAP(info[0], array, DcArrayWrap);
  dc_array_unref(array->state);
}


/**
 * mrmsg
 **/

NAN_METHOD(dc_msg_get_text) {
  ASSERT_UNWRAP(info[0], msg, DcMsgWrap);
  info.GetReturnValue().Set(Nan::New<v8::String>(dc_msg_get_text(msg->state)).ToLocalChecked());
}

NAN_METHOD(dc_msg_unref) {
  ASSERT_UNWRAP(info[0], msg, DcMsgWrap);
  dc_msg_unref(msg->state);
}

/**
 * mrchat
 */

NAN_METHOD(dc_chat_unref) {
  ASSERT_UNWRAP(info[0], chat, DcChatWrap);
  dc_chat_unref(chat->state);
}

NAN_METHOD(dc_chat_is_unpromoted) {
  ASSERT_UNWRAP(info[0], chat, DcChatWrap);
  info.GetReturnValue().Set(Nan::New<v8::Number>(dc_chat_is_unpromoted(chat->state)));
}

NAN_METHOD(dc_chat_get_text_draft) {
  ASSERT_UNWRAP(info[0], chat, DcChatWrap);
  const char *text = dc_chat_get_text_draft(chat->state);
  info.GetReturnValue().Set(Nan::New<v8::String>(text).ToLocalChecked());
}

NAN_METHOD(dc_chat_get_archived) {
  ASSERT_UNWRAP(info[0], chat, DcChatWrap);
  info.GetReturnValue().Set(Nan::New<v8::Number>(dc_chat_get_archived(chat->state)));
}

NAN_METHOD(dc_chat_get_profile_image) {
  ASSERT_UNWRAP(info[0], chat, DcChatWrap);
  const char *text = dc_chat_get_profile_image(chat->state);
  info.GetReturnValue().Set(Nan::New<v8::String>(text).ToLocalChecked());
}

NAN_METHOD(dc_chat_get_subtitle) {
  ASSERT_UNWRAP(info[0], chat, DcChatWrap);
  const char *text = dc_chat_get_subtitle(chat->state);
  info.GetReturnValue().Set(Nan::New<v8::String>(text).ToLocalChecked());
}

NAN_METHOD(dc_chat_get_name) {
  ASSERT_UNWRAP(info[0], chat, DcChatWrap);
  const char *text = dc_chat_get_name(chat->state);
  info.GetReturnValue().Set(Nan::New<v8::String>(text).ToLocalChecked());
}

NAN_METHOD(dc_chat_get_type) {
  ASSERT_UNWRAP(info[0], chat, DcChatWrap);
  info.GetReturnValue().Set(Nan::New<v8::Number>(dc_chat_get_type(chat->state)));
}

NAN_METHOD(dc_chat_is_self_talk) {
  ASSERT_UNWRAP(info[0], chat, DcChatWrap);
  info.GetReturnValue().Set(Nan::New<v8::Number>(dc_chat_is_self_talk(chat->state)));
}

/**
 * mrcontact
 */

NAN_METHOD(dc_contact_unref) {
  ASSERT_UNWRAP(info[0], obj, DcContactWrap);
  dc_contact_unref(obj->state);
}

NAN_METHOD(dc_contact_is_blocked) {
  ASSERT_UNWRAP(info[0], obj, DcContactWrap);
  info.GetReturnValue().Set(Nan::New<v8::Number>(dc_contact_is_blocked(obj->state)));
}

NAN_METHOD(dc_contact_get_addr) {
  ASSERT_UNWRAP(info[0], obj, DcContactWrap);
  const char *text = dc_contact_get_addr(obj->state);
  info.GetReturnValue().Set(Nan::New<v8::String>(text).ToLocalChecked());
}

NAN_METHOD(dc_contact_get_name) {
  ASSERT_UNWRAP(info[0], obj, DcContactWrap);
  const char *text = dc_contact_get_name(obj->state);
  info.GetReturnValue().Set(Nan::New<v8::String>(text).ToLocalChecked());
}

NAN_METHOD(dc_contact_get_display_name) {
  ASSERT_UNWRAP(info[0], obj, DcContactWrap);
  const char *text = dc_contact_get_display_name(obj->state);
  info.GetReturnValue().Set(Nan::New<v8::String>(text).ToLocalChecked());
}

NAN_METHOD(dc_contact_get_name_n_addr) {
  ASSERT_UNWRAP(info[0], obj, DcContactWrap);
  const char *text = dc_contact_get_name_n_addr(obj->state);
  info.GetReturnValue().Set(Nan::New<v8::String>(text).ToLocalChecked());
}

NAN_MODULE_INIT(InitAll) {
  DcContextWrap::Init();
  DcArrayWrap::Init();
  DcChatWrap::Init();
  DcContactWrap::Init();
  DcChatListWrap::Init();
  DcMsgWrap::Init();

  EXPORT_FUNCTION(dc_context_new);
  EXPORT_FUNCTION(dc_context_unref);
  EXPORT_FUNCTION(dc_open);
  EXPORT_FUNCTION(dc_close);
  EXPORT_FUNCTION(dc_is_open);
  EXPORT_FUNCTION(dc_get_version_str);
  EXPORT_FUNCTION(dc_get_info);
  EXPORT_FUNCTION(dc_set_config);
  EXPORT_FUNCTION(dc_get_config);
  EXPORT_FUNCTION(dc_set_config_int);
  EXPORT_FUNCTION(dc_get_config_int);
  EXPORT_FUNCTION(dc_configure);
  EXPORT_FUNCTION(dc_create_chat_by_contact_id);
  EXPORT_FUNCTION(dc_send_text_msg);
  EXPORT_FUNCTION(dc_send_image_msg);
  EXPORT_FUNCTION(dc_send_video_msg);
  EXPORT_FUNCTION(dc_send_voice_msg);
  EXPORT_FUNCTION(dc_send_audio_msg);
  EXPORT_FUNCTION(dc_send_file_msg);
  EXPORT_FUNCTION(dc_send_vcard_msg);
  EXPORT_FUNCTION(dc_get_chat_msgs);
  EXPORT_FUNCTION(dc_get_chatlist);
  EXPORT_FUNCTION(dc_get_chat);
  EXPORT_FUNCTION(dc_get_msg);
  EXPORT_FUNCTION(dc_marknoticed_chat);
  EXPORT_FUNCTION(dc_get_chat_id_by_contact_id);
  EXPORT_FUNCTION(dc_get_chat_media);
  EXPORT_FUNCTION(dc_get_next_media);
  EXPORT_FUNCTION(dc_get_chat_contacts);
  EXPORT_FUNCTION(dc_get_fresh_msgs);
  EXPORT_FUNCTION(dc_search_msgs);
  EXPORT_FUNCTION(dc_set_text_draft);
  EXPORT_FUNCTION(dc_get_msg_cnt);
  EXPORT_FUNCTION(dc_get_fresh_msg_cnt);
  EXPORT_FUNCTION(dc_archive_chat);
  EXPORT_FUNCTION(dc_delete_chat);
  EXPORT_FUNCTION(dc_create_group_chat);
  EXPORT_FUNCTION(dc_set_chat_name);
  EXPORT_FUNCTION(dc_set_chat_profile_image);
  EXPORT_FUNCTION(dc_is_contact_in_chat);
  EXPORT_FUNCTION(dc_add_contact_to_chat);
  EXPORT_FUNCTION(dc_remove_contact_from_chat);
  EXPORT_FUNCTION(dc_create_contact);
  EXPORT_FUNCTION(dc_add_address_book);
  EXPORT_FUNCTION(dc_get_contacts);
  EXPORT_FUNCTION(dc_get_blocked_contacts);
  EXPORT_FUNCTION(dc_get_blocked_cnt);
  EXPORT_FUNCTION(dc_get_contact);
  EXPORT_FUNCTION(dc_block_contact);
  EXPORT_FUNCTION(dc_get_contact_encrinfo);
  EXPORT_FUNCTION(dc_delete_contact);
  EXPORT_FUNCTION(dc_get_msg_info);
  EXPORT_FUNCTION(dc_forward_msgs);
  EXPORT_FUNCTION(dc_star_msgs);
  EXPORT_FUNCTION(dc_delete_msgs);
  EXPORT_FUNCTION(dc_markseen_msgs);
  EXPORT_FUNCTION(dc_is_configured);
  EXPORT_FUNCTION(dc_stop_ongoing_process);
  EXPORT_FUNCTION(dc_initiate_key_transfer);
  EXPORT_FUNCTION(dc_continue_key_transfer);
  EXPORT_FUNCTION(dc_imex);
  EXPORT_FUNCTION(dc_imex_has_backup);
  EXPORT_FUNCTION(dc_check_password);

  EXPORT_FUNCTION(perform_imap_jobs);
  EXPORT_FUNCTION(perform_imap_fetch);
  EXPORT_FUNCTION(perform_imap_idle);
  EXPORT_FUNCTION(perform_smtp_idle);
  EXPORT_FUNCTION(perform_smtp_jobs);

  EXPORT_FUNCTION(dc_array_get_cnt);
  EXPORT_FUNCTION(dc_array_get_id);
  EXPORT_FUNCTION(dc_array_unref);

  EXPORT_FUNCTION(dc_msg_get_text);
  EXPORT_FUNCTION(dc_msg_unref);

  EXPORT_FUNCTION(dc_chat_get_type);
  EXPORT_FUNCTION(dc_chat_get_name);
  EXPORT_FUNCTION(dc_chat_get_subtitle);
  EXPORT_FUNCTION(dc_chat_get_profile_image);
  EXPORT_FUNCTION(dc_chat_get_archived);
  EXPORT_FUNCTION(dc_chat_is_unpromoted);
  EXPORT_FUNCTION(dc_chat_is_self_talk);
  EXPORT_FUNCTION(dc_chat_unref);

  EXPORT_FUNCTION(dc_contact_get_addr);
  EXPORT_FUNCTION(dc_contact_get_name);
  EXPORT_FUNCTION(dc_contact_get_display_name);
  EXPORT_FUNCTION(dc_contact_get_name_n_addr);
  EXPORT_FUNCTION(dc_contact_is_blocked);
  EXPORT_FUNCTION(dc_contact_unref);

  EXPORT_NUMBER(DC_GCL_ARCHIVED_ONLY)
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
