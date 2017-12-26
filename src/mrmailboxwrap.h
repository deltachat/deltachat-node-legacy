#ifndef __MRMAILBOXWRAP_H__
#define __MRMAILBOXWRAP_H__

#include <nan.h>
#include <mrmailbox.h>

class MrMailboxWrap : public Nan::ObjectWrap {
public:
  static void Init ();
  static v8::Local<v8::Value> NewInstance ();
  MrMailboxWrap ();
  ~MrMailboxWrap ();

private:
  mrmailbox_t* mailbox;

  static NAN_METHOD(New);
};

#endif
