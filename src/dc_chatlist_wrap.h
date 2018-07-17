#ifndef __DC_CHATLISTWRAP_H__
#define __DC_CHATLISTWRAP_H__

#include <nan.h>
#include <deltachat.h>

class DcChatListWrap : public Nan::ObjectWrap {
public:
  dc_chatlist_t* state;

  static void Init ();
  static v8::Local<v8::Value> NewInstance (dc_chatlist_t *);
  DcChatListWrap ();
  ~DcChatListWrap ();

private:
  static NAN_METHOD(New);
};

#endif
