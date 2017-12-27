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

NAN_METHOD(mrmailbox_create_contact) {
  ASSERT_UNWRAP(info[0], mailbox, MrMailboxWrap);
  v8::String::Utf8Value name(info[1]);
  v8::String::Utf8Value addr(info[2]);
  mrmailbox_create_contact(mailbox->state, ToCString(name), ToCString(addr));
}

NAN_METHOD(mrmailbox_configure_and_connect) {
  ASSERT_UNWRAP(info[0], mailbox, MrMailboxWrap)
  mrmailbox_configure_and_connect(mailbox->state);
}

NAN_MODULE_INIT(InitAll) {
  MrMailboxWrap::Init();
  EXPORT_FUNCTION(mrmailbox_new);
  EXPORT_FUNCTION(mrmailbox_set_config);
  EXPORT_FUNCTION(mrmailbox_configure_and_connect);
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
