#include "mrmailbox_wrap.h"
#include "macros.h"

Nan::Persistent<v8::FunctionTemplate> MrMailboxWrap::constructor;

MrMailboxWrap::MrMailboxWrap () {}

MrMailboxWrap::~MrMailboxWrap () {}

NAN_METHOD(MrMailboxWrap::New) {
  MrMailboxWrap* obj = new MrMailboxWrap();
  obj->Wrap(info.This());
  info.GetReturnValue().Set(info.This());
}

void MrMailboxWrap::Init () {
  v8::Local<v8::FunctionTemplate> tpl = Nan::New<v8::FunctionTemplate>(MrMailboxWrap::New);
  constructor.Reset(tpl);
  tpl->SetClassName(Nan::New("MrMailboxWrap").ToLocalChecked());
  tpl->InstanceTemplate()->SetInternalFieldCount(1);
}

v8::Local<v8::Value> MrMailboxWrap::NewInstance (mrmailboxcb_t function) {
  Nan::EscapableHandleScope scope;

  v8::Local<v8::Object> instance;

  v8::Local<v8::FunctionTemplate> constructorHandle = Nan::New<v8::FunctionTemplate>(MrMailboxWrap::constructor);
  instance = Nan::NewInstance(constructorHandle->GetFunction()).ToLocalChecked();

  MrMailboxWrap *wrap = Nan::ObjectWrap::Unwrap<MrMailboxWrap>(instance);
  
  wrap->state = mrmailbox_new(function, NULL, NULL);

  return scope.Escape(instance);
}
