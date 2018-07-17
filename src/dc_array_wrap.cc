#include "dc_array_wrap.h"
#include "macros.h"

static Nan::Persistent<v8::FunctionTemplate> dc_array_constructor;

DcArrayWrap::DcArrayWrap () {}

DcArrayWrap::~DcArrayWrap () {}

NAN_METHOD(DcArrayWrap::New) {
  DcArrayWrap* obj = new DcArrayWrap();
  obj->Wrap(info.This());
  info.GetReturnValue().Set(info.This());
}

void DcArrayWrap::Init () {
  v8::Local<v8::FunctionTemplate> tpl = Nan::New<v8::FunctionTemplate>(DcArrayWrap::New);
  dc_array_constructor.Reset(tpl);
  tpl->SetClassName(Nan::New("DcArrayWrap").ToLocalChecked());
  tpl->InstanceTemplate()->SetInternalFieldCount(1);
}

v8::Local<v8::Value> DcArrayWrap::NewInstance (dc_array_t *dc_array) {
  Nan::EscapableHandleScope scope;

  v8::Local<v8::Object> instance;

  v8::Local<v8::FunctionTemplate> constructorHandle = Nan::New<v8::FunctionTemplate>(dc_array_constructor);
  instance = Nan::NewInstance(constructorHandle->GetFunction()).ToLocalChecked();

  DcArrayWrap *self = Nan::ObjectWrap::Unwrap<DcArrayWrap>(instance);
  self->state = dc_array;

  return scope.Escape(instance);
}
