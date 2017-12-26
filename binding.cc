#include "src/macros.h"
#include "src/mrmailboxwrap.h"

NAN_METHOD(mrmailbox_new) {
  info.GetReturnValue().Set(MrMailboxWrap::NewInstance());
}

NAN_MODULE_INIT(InitAll) {
  MrMailboxWrap::Init();
  EXPORT_FUNCTION(mrmailbox_new);
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
