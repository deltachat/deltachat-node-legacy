#include "dc_chat_wrap.h"
#include "macros.h"

static Nan::Persistent<v8::FunctionTemplate> constructor;

DcChatWrap::DcChatWrap () {}

DcChatWrap::~DcChatWrap () {}

NAN_METHOD(DcChatWrap::New) {
  DcChatWrap* obj = new DcChatWrap();
  obj->Wrap(info.This());
  info.GetReturnValue().Set(info.This());
}

void DcChatWrap::Init () {
  v8::Local<v8::FunctionTemplate> tpl = Nan::New<v8::FunctionTemplate>(DcChatWrap::New);
  constructor.Reset(tpl);
  tpl->SetClassName(Nan::New("DcChatWrap").ToLocalChecked());
  tpl->InstanceTemplate()->SetInternalFieldCount(1);
}

v8::Local<v8::Value> DcChatWrap::NewInstance (dc_chat_t *dc_chat) {
  Nan::EscapableHandleScope scope;

  v8::Local<v8::Object> instance;

  v8::Local<v8::FunctionTemplate> constructorHandle = Nan::New<v8::FunctionTemplate>(constructor);
  instance = Nan::NewInstance(constructorHandle->GetFunction()).ToLocalChecked();

  DcChatWrap *self = Nan::ObjectWrap::Unwrap<DcChatWrap>(instance);
  self->state = dc_chat;

  return scope.Escape(instance);
}
