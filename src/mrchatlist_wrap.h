#ifndef __MRCHATLISTWRAP_H__
#define __MRCHATLISTWRAP_H__

#include <nan.h>
#include <mrmailbox.h>

class MrChatListWrap : public Nan::ObjectWrap {
public:
  mrchatlist_t* state;

  static void Init ();
  static v8::Local<v8::Value> NewInstance (mrchatlist_t *);
  MrChatListWrap ();
  ~MrChatListWrap ();

private:
  static NAN_METHOD(New);
};

#endif
