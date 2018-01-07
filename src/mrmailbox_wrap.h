#ifndef __MRMAILBOXWRAP_H__
#define __MRMAILBOXWRAP_H__

#include <nan.h>
#include <mrmailbox.h>

class MrMailboxWrap : public Nan::ObjectWrap {
public:
  mrmailbox_t* state;

  static void Init ();
  static v8::Local<v8::Value> NewInstance (mrmailboxcb_t);
  MrMailboxWrap ();
  ~MrMailboxWrap ();

private:
  static NAN_METHOD(New);
  static Nan::Persistent<v8::FunctionTemplate> constructor;
};

#endif
