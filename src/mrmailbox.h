#ifndef MRMAILBOX_H 
#define MRMAILBOX_H 

#include <nan.h>
#include <mrmailbox.h>

class MrMailbox : public Nan::ObjectWrap {
public:
  static void Init ();
  static v8::Local<v8::Value> NewInstance ();
  MrMailbox ();
  ~MrMailbox ();

private:
  mrmailbox_t mrmailbox_t;

};

#endif
