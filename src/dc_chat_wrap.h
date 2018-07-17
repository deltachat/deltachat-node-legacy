#ifndef __DC_CHATWRAP_H__
#define __DC_CHATWRAP_H__

#include <nan.h>
#include <deltachat.h>

class DcChatWrap : public Nan::ObjectWrap {
public:
  dc_chat_t* state;

  static void Init ();
  static v8::Local<v8::Value> NewInstance (dc_chat_t *);
  DcChatWrap ();
  ~DcChatWrap ();

private:
  static NAN_METHOD(New);
};

#endif
