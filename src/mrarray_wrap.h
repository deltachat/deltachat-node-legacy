#ifndef __MRARRAYWRAP_H__
#define __MRARRAYWRAP_H__

#include <nan.h>
#include <mrmailbox.h>

class MrArrayWrap : public Nan::ObjectWrap {
public:
  mrarray_t* state;
  uint32_t        m_magic;
  mrmailbox_t*    m_mailbox;     
  size_t          m_allocated;   
  size_t          m_count;       
  uintptr_t*      m_array;   

  static void Init ();
  static v8::Local<v8::Value> NewInstance ();
  MrArrayWrap ();
  ~MrArrayWrap ();

private:
  static NAN_METHOD(New);
};

#endif
