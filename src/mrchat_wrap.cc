#include "mrchat_wrap.h"
#include "macros.h"

static Nan::Persistent<v8::FunctionTemplate> constructor;

MrChatWrap::MrChatWrap () {}

MrChatWrap::~MrChatWrap () {}

NAN_METHOD(MrChatWrap::New) {
  MrChatWrap* obj = new MrChatWrap();
  obj->Wrap(info.This());
  info.GetReturnValue().Set(info.This());
}

void MrChatWrap::Init () {
  v8::Local<v8::FunctionTemplate> tpl = Nan::New<v8::FunctionTemplate>(MrChatWrap::New);
  constructor.Reset(tpl);
  tpl->SetClassName(Nan::New("MrChatWrap").ToLocalChecked());
  tpl->InstanceTemplate()->SetInternalFieldCount(1);
}

v8::Local<v8::Value> MrChatWrap::NewInstance (mrchat_t *mrchat) {
  Nan::EscapableHandleScope scope;

  v8::Local<v8::Object> instance;

  v8::Local<v8::FunctionTemplate> constructorHandle = Nan::New<v8::FunctionTemplate>(constructor);
  instance = Nan::NewInstance(constructorHandle->GetFunction()).ToLocalChecked();

  MrChatWrap *self = Nan::ObjectWrap::Unwrap<MrChatWrap>(instance);
  self->state = mrchat;

  return scope.Escape(instance);
}
