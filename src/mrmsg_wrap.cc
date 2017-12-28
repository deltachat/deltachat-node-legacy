#include "mrmsg_wrap.h"
#include "macros.h"

static Nan::Persistent<v8::FunctionTemplate> mrmsg_constructor;

MrMsgWrap::MrMsgWrap () {}

MrMsgWrap::~MrMsgWrap () {}

NAN_METHOD(MrMsgWrap::New) {
  MrMsgWrap* obj = new MrMsgWrap();
  obj->Wrap(info.This());
  info.GetReturnValue().Set(info.This());
}

void MrMsgWrap::Init () {
  v8::Local<v8::FunctionTemplate> tpl = Nan::New<v8::FunctionTemplate>(MrMsgWrap::New);
  mrmsg_constructor.Reset(tpl);
  tpl->SetClassName(Nan::New("MrMsgWrap").ToLocalChecked());
  tpl->InstanceTemplate()->SetInternalFieldCount(1);
}

v8::Local<v8::Value> MrMsgWrap::NewInstance () {
  Nan::EscapableHandleScope scope;

  v8::Local<v8::Object> instance;

  v8::Local<v8::FunctionTemplate> constructorHandle = Nan::New<v8::FunctionTemplate>(mrmsg_constructor);
  instance = Nan::NewInstance(constructorHandle->GetFunction()).ToLocalChecked();

  MrMsgWrap *self = Nan::ObjectWrap::Unwrap<MrMsgWrap>(instance);
  self->state = mrmsg_new();

  return scope.Escape(instance);
}
