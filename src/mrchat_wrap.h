#ifndef __MRCHATWRAP_H__
#define __MRCHATWRAP_H__

#include <nan.h>
#include <mrmailbox.h>

class MrChatWrap : public Nan::ObjectWrap {
public:
  mrchat_t* state;

  static void Init ();
  static v8::Local<v8::Value> NewInstance (mrchat_t *);
  MrChatWrap ();
  ~MrChatWrap ();

private:
  static NAN_METHOD(New);
};

#endif
