#include "macros.h"
#include <nan.h>
#include <mrmailbox.h>

NAN_METHOD(hello) {
  info.GetReturnValue().Set(LOCAL_STRING("world"));
}

NAN_MODULE_INIT(InitAll) {
  EXPORT_FUNCTION(hello);
}

NODE_MODULE(hello, InitAll)
