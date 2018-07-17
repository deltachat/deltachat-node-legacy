#include "dc_msg_wrap.h"
#include "macros.h"

static Nan::Persistent<v8::FunctionTemplate> dc_msg_constructor;

DcMsgWrap::DcMsgWrap () {}

DcMsgWrap::~DcMsgWrap () {}

NAN_METHOD(DcMsgWrap::New) {
  DcMsgWrap* obj = new DcMsgWrap();
  obj->Wrap(info.This());
  info.GetReturnValue().Set(info.This());
}

void DcMsgWrap::Init () {
  v8::Local<v8::FunctionTemplate> tpl = Nan::New<v8::FunctionTemplate>(DcMsgWrap::New);
  dc_msg_constructor.Reset(tpl);
  tpl->SetClassName(Nan::New("DcMsgWrap").ToLocalChecked());
  tpl->InstanceTemplate()->SetInternalFieldCount(1);
}

v8::Local<v8::Value> DcMsgWrap::NewInstance (dc_msg_t *dc_msg) {
  Nan::EscapableHandleScope scope;

  v8::Local<v8::Object> instance;

  v8::Local<v8::FunctionTemplate> constructorHandle = Nan::New<v8::FunctionTemplate>(dc_msg_constructor);
  instance = Nan::NewInstance(constructorHandle->GetFunction()).ToLocalChecked();

  DcMsgWrap *self = Nan::ObjectWrap::Unwrap<DcMsgWrap>(instance);
  self->state = dc_msg;

  return scope.Escape(instance);
}
