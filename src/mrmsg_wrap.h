#ifndef __MRMSGWRAP_H__
#define __MRMSGWRAP_H__

#include <nan.h>
#include <mrmailbox.h>

class MrMsgWrap : public Nan::ObjectWrap {
public:
  mrmsg_t* state;

  static void Init ();
  static v8::Local<v8::Value> NewInstance (mrmsg_t*);
  MrMsgWrap ();
  ~MrMsgWrap ();

private:
  static NAN_METHOD(New);
};

#endif
