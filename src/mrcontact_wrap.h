#ifndef __MRCONTACTWRAP_H__
#define __MRCONTACTWRAP_H__

#include <nan.h>
#include <mrmailbox.h>

class MrContactWrap : public Nan::ObjectWrap {
public:
  mrcontact_t* state;

  static void Init ();
  static v8::Local<v8::Value> NewInstance (mrcontact_t *);
  MrContactWrap ();
  ~MrContactWrap ();

private:
  static NAN_METHOD(New);
};

#endif
