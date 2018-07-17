#include "dc_chatlist_wrap.h"
#include "macros.h"

static Nan::Persistent<v8::FunctionTemplate> constructor;

DcChatListWrap::DcChatListWrap () {}

DcChatListWrap::~DcChatListWrap () {}

NAN_METHOD(DcChatListWrap::New) {
  DcChatListWrap* obj = new DcChatListWrap();
  obj->Wrap(info.This());
  info.GetReturnValue().Set(info.This());
}

void DcChatListWrap::Init () {
  v8::Local<v8::FunctionTemplate> tpl = Nan::New<v8::FunctionTemplate>(DcChatListWrap::New);
  constructor.Reset(tpl);
  tpl->SetClassName(Nan::New("DcChatListWrap").ToLocalChecked());
  tpl->InstanceTemplate()->SetInternalFieldCount(1);
}

v8::Local<v8::Value> DcChatListWrap::NewInstance (dc_chatlist_t *dc_chatlist) {
  Nan::EscapableHandleScope scope;

  v8::Local<v8::Object> instance;

  v8::Local<v8::FunctionTemplate> constructorHandle = Nan::New<v8::FunctionTemplate>(constructor);
  instance = Nan::NewInstance(constructorHandle->GetFunction()).ToLocalChecked();

  DcChatListWrap *self = Nan::ObjectWrap::Unwrap<DcChatListWrap>(instance);
  self->state = dc_chatlist;

  return scope.Escape(instance);
}
