#include "mrmailboxwrap.h"
#include "macros.h"

static Nan::Persistent<v8::FunctionTemplate> mrmailbox_constructor;

MrMailboxWrap::MrMailboxWrap () {}

MrMailboxWrap::~MrMailboxWrap () {}

NAN_METHOD(MrMailboxWrap::New) {
  MrMailboxWrap* obj = new MrMailboxWrap();
  obj->Wrap(info.This());
  info.GetReturnValue().Set(info.This());
}

void MrMailboxWrap::Init () {
  v8::Local<v8::FunctionTemplate> tpl = Nan::New<v8::FunctionTemplate>(MrMailboxWrap::New);
  mrmailbox_constructor.Reset(tpl);
  tpl->SetClassName(Nan::New("MrMailboxWrap").ToLocalChecked());
  tpl->InstanceTemplate()->SetInternalFieldCount(1);
}

uintptr_t my_delta_handler(mrmailbox_t* mailbox, int event, uintptr_t data1, uintptr_t data2)
{
  return 0; // for unhandled events, it is always safe to return 0
}

v8::Local<v8::Value> MrMailboxWrap::NewInstance () {
  Nan::EscapableHandleScope scope;

  v8::Local<v8::Object> instance;

  v8::Local<v8::FunctionTemplate> constructorHandle = Nan::New<v8::FunctionTemplate>(mrmailbox_constructor);
  instance = Nan::NewInstance(constructorHandle->GetFunction()).ToLocalChecked();

  MrMailboxWrap *self = Nan::ObjectWrap::Unwrap<MrMailboxWrap>(instance);
  self->mailbox = mrmailbox_new(my_delta_handler, NULL, NULL);

  return scope.Escape(instance);
}
