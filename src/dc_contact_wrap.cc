#include "dc_contact_wrap.h"
#include "macros.h"

static Nan::Persistent<v8::FunctionTemplate> constructor;

DcContactWrap::DcContactWrap () {}

DcContactWrap::~DcContactWrap () {}

NAN_METHOD(DcContactWrap::New) {
  DcContactWrap* obj = new DcContactWrap();
  obj->Wrap(info.This());
  info.GetReturnValue().Set(info.This());
}

void DcContactWrap::Init () {
  v8::Local<v8::FunctionTemplate> tpl = Nan::New<v8::FunctionTemplate>(DcContactWrap::New);
  constructor.Reset(tpl);
  tpl->SetClassName(Nan::New("DcContactWrap").ToLocalChecked());
  tpl->InstanceTemplate()->SetInternalFieldCount(1);
}

v8::Local<v8::Value> DcContactWrap::NewInstance (dc_contact_t *dc_contact) {
  Nan::EscapableHandleScope scope;

  v8::Local<v8::Object> instance;

  v8::Local<v8::FunctionTemplate> constructorHandle = Nan::New<v8::FunctionTemplate>(constructor);
  instance = Nan::NewInstance(constructorHandle->GetFunction()).ToLocalChecked();

  DcContactWrap *self = Nan::ObjectWrap::Unwrap<DcContactWrap>(instance);
  self->state = dc_contact;

  return scope.Escape(instance);
}
