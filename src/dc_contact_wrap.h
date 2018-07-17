#ifndef __DC_CONTACTWRAP_H__
#define __DC_CONTACTWRAP_H__

#include <nan.h>
#include <deltachat.h>

class DcContactWrap : public Nan::ObjectWrap {
public:
  dc_contact_t* state;

  static void Init ();
  static v8::Local<v8::Value> NewInstance (dc_contact_t *);
  DcContactWrap ();
  ~DcContactWrap ();

private:
  static NAN_METHOD(New);
};

#endif
