#include "dc_context_wrap.h"
#include "macros.h"

Nan::Persistent<v8::FunctionTemplate> DcContextWrap::constructor;

DcContextWrap::DcContextWrap () {}

DcContextWrap::~DcContextWrap () {}

NAN_METHOD(DcContextWrap::New) {
  DcContextWrap* obj = new DcContextWrap();
  obj->Wrap(info.This());
  info.GetReturnValue().Set(info.This());
}

void DcContextWrap::Init () {
  v8::Local<v8::FunctionTemplate> tpl = Nan::New<v8::FunctionTemplate>(DcContextWrap::New);
  constructor.Reset(tpl);
  tpl->SetClassName(Nan::New("DcContextWrap").ToLocalChecked());
  tpl->InstanceTemplate()->SetInternalFieldCount(1);
}

v8::Local<v8::Value> DcContextWrap::NewInstance (dc_callback_t function) {
  Nan::EscapableHandleScope scope;

  v8::Local<v8::Object> instance;

  v8::Local<v8::FunctionTemplate> constructorHandle = Nan::New<v8::FunctionTemplate>(DcContextWrap::constructor);
  instance = Nan::NewInstance(constructorHandle->GetFunction()).ToLocalChecked();

  DcContextWrap *wrap = Nan::ObjectWrap::Unwrap<DcContextWrap>(instance);
  
  wrap->state = dc_context_new(function, NULL, NULL);

  return scope.Escape(instance);
}
