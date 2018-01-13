#include "mrarray_wrap.h"
#include "macros.h"

static Nan::Persistent<v8::FunctionTemplate> mrarray_constructor;

MrArrayWrap::MrArrayWrap () {}

MrArrayWrap::~MrArrayWrap () {}

NAN_METHOD(MrArrayWrap::New) {
  MrArrayWrap* obj = new MrArrayWrap();
  obj->Wrap(info.This());
  info.GetReturnValue().Set(info.This());
}

void MrArrayWrap::Init () {
  v8::Local<v8::FunctionTemplate> tpl = Nan::New<v8::FunctionTemplate>(MrArrayWrap::New);
  mrarray_constructor.Reset(tpl);
  tpl->SetClassName(Nan::New("MrArrayWrap").ToLocalChecked());
  tpl->InstanceTemplate()->SetInternalFieldCount(1);
}

v8::Local<v8::Value> MrArrayWrap::NewInstance (mrarray_t *mrarray) {
  Nan::EscapableHandleScope scope;

  v8::Local<v8::Object> instance;

  v8::Local<v8::FunctionTemplate> constructorHandle = Nan::New<v8::FunctionTemplate>(mrarray_constructor);
  instance = Nan::NewInstance(constructorHandle->GetFunction()).ToLocalChecked();

  MrArrayWrap *self = Nan::ObjectWrap::Unwrap<MrArrayWrap>(instance);
  self->state = mrarray;

  return scope.Escape(instance);
}
