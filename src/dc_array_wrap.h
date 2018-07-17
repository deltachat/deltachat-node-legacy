#ifndef __DC_ARRAYWRAP_H__
#define __DC_ARRAYWRAP_H__

#include <nan.h>
#include <deltachat.h>

class DcArrayWrap : public Nan::ObjectWrap {
public:
  dc_array_t*     state;
  uint32_t        magic;
  dc_context_t*   context;
  size_t          allocated;
  size_t          count;
  uintptr_t*      array;

  static void Init ();
  static v8::Local<v8::Value> NewInstance (dc_array_t *);
  DcArrayWrap ();
  ~DcArrayWrap ();

private:
  static NAN_METHOD(New);
};

#endif
