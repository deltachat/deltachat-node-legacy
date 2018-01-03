#include "mrmailbox_wrap.h"
#include "mrmailbox_worker.cc"
#include "macros.h"
#include "cify.cc"

Nan::Persistent<v8::FunctionTemplate> MrMailboxWrap::constructor;

MrMailboxWrap::MrMailboxWrap () {}

MrMailboxWrap::~MrMailboxWrap () {}

NAN_METHOD(MrMailboxWrap::New) {
  MrMailboxWrap* obj = new MrMailboxWrap();
  obj->Wrap(info.This());
  info.GetReturnValue().Set(info.This());
}

void MrMailboxWrap::Init () {
  v8::Local<v8::FunctionTemplate> tpl = Nan::New<v8::FunctionTemplate>(MrMailboxWrap::New);
  constructor.Reset(tpl);
  tpl->SetClassName(Nan::New("MrMailboxWrap").ToLocalChecked());
  tpl->InstanceTemplate()->SetInternalFieldCount(1);
}

v8::Local<v8::Value> MrMailboxWrap::NewInstance (Nan::Callback *callback) {
  Nan::EscapableHandleScope scope;

  v8::Local<v8::Object> instance;

  v8::Local<v8::FunctionTemplate> constructorHandle = Nan::New<v8::FunctionTemplate>(MrMailboxWrap::constructor);
  instance = Nan::NewInstance(constructorHandle->GetFunction()).ToLocalChecked();

  MrMailboxWrap *wrap = Nan::ObjectWrap::Unwrap<MrMailboxWrap>(instance);
  auto const delta_handler = cify<uintptr_t(*)(mrmailbox_t*, int, uintptr_t, uintptr_t)>([&](mrmailbox_t* mailbox, int event, uintptr_t data1, uintptr_t data2) -> uintptr_t {
    printf("got event %d %s %s\n", event, data1, data2);
    Nan::AsyncQueueWorker(new MailboxWorker(callback, mailbox, event, data1, data2));
    return 0;
  });
  wrap->state = mrmailbox_new(delta_handler, NULL, NULL);

  return scope.Escape(instance);
}
