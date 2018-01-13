#include "mrcontact_wrap.h"
#include "macros.h"

static Nan::Persistent<v8::FunctionTemplate> constructor;

MrContactWrap::MrContactWrap () {}

MrContactWrap::~MrContactWrap () {}

NAN_METHOD(MrContactWrap::New) {
  MrContactWrap* obj = new MrContactWrap();
  obj->Wrap(info.This());
  info.GetReturnValue().Set(info.This());
}

void MrContactWrap::Init () {
  v8::Local<v8::FunctionTemplate> tpl = Nan::New<v8::FunctionTemplate>(MrContactWrap::New);
  constructor.Reset(tpl);
  tpl->SetClassName(Nan::New("MrContactWrap").ToLocalChecked());
  tpl->InstanceTemplate()->SetInternalFieldCount(1);
}

v8::Local<v8::Value> MrContactWrap::NewInstance (mrcontact_t *mrcontact) {
  Nan::EscapableHandleScope scope;

  v8::Local<v8::Object> instance;

  v8::Local<v8::FunctionTemplate> constructorHandle = Nan::New<v8::FunctionTemplate>(constructor);
  instance = Nan::NewInstance(constructorHandle->GetFunction()).ToLocalChecked();

  MrContactWrap *self = Nan::ObjectWrap::Unwrap<MrContactWrap>(instance);
  self->state = mrcontact;

  return scope.Escape(instance);
}
