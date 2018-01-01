#ifndef __MRARRAYWRAP_H__
#define __MRARRAYWRAP_H__

#include <nan.h>
#include <mrmailbox.h>

class MrArrayWrap : public Nan::ObjectWrap {
public:
  mrarray_t* state;

  static void Init ();
  static v8::Local<v8::Value> NewInstance ();
  MrArrayWrap ();
  ~MrArrayWrap ();

private:
  static NAN_METHOD(New);
};

#endif
