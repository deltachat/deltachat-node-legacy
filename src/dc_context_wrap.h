#ifndef __DC_CONTEXTWRAP_H___
#define __DC_CONTEXTWRAP_H___

#include <nan.h>
#include <deltachat.h>

class DcContextWrap : public Nan::ObjectWrap {
public:
  dc_context_t* state;

  static void Init ();
  static v8::Local<v8::Value> NewInstance (dc_callback_t);
  DcContextWrap ();
  ~DcContextWrap ();

private:
  static NAN_METHOD(New);
  static Nan::Persistent<v8::FunctionTemplate> constructor;
};

#endif
