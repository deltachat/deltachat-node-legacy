#include "mrchatlist_wrap.h"
#include "macros.h"

static Nan::Persistent<v8::FunctionTemplate> constructor;

MrChatListWrap::MrChatListWrap () {}

MrChatListWrap::~MrChatListWrap () {}

NAN_METHOD(MrChatListWrap::New) {
  MrChatListWrap* obj = new MrChatListWrap();
  obj->Wrap(info.This());
  info.GetReturnValue().Set(info.This());
}

void MrChatListWrap::Init () {
  v8::Local<v8::FunctionTemplate> tpl = Nan::New<v8::FunctionTemplate>(MrChatListWrap::New);
  constructor.Reset(tpl);
  tpl->SetClassName(Nan::New("MrChatListWrap").ToLocalChecked());
  tpl->InstanceTemplate()->SetInternalFieldCount(1);
}

v8::Local<v8::Value> MrChatListWrap::NewInstance (mrchatlist_t *mrchatlist) {
  Nan::EscapableHandleScope scope;

  v8::Local<v8::Object> instance;

  v8::Local<v8::FunctionTemplate> constructorHandle = Nan::New<v8::FunctionTemplate>(constructor);
  instance = Nan::NewInstance(constructorHandle->GetFunction()).ToLocalChecked();

  MrChatListWrap *self = Nan::ObjectWrap::Unwrap<MrChatListWrap>(instance);
  self->state = mrchatlist;

  return scope.Escape(instance);
}
