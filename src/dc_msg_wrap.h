#ifndef __DC_MSGWRAP_H__
#define __DC_MSGWRAP_H__

#include <nan.h>
#include <deltachat.h>

class DcMsgWrap : public Nan::ObjectWrap {
public:
  dc_msg_t* state;

  static void Init ();
  static v8::Local<v8::Value> NewInstance (dc_msg_t*);
  DcMsgWrap ();
  ~DcMsgWrap ();

private:
  static NAN_METHOD(New);
};

#endif
