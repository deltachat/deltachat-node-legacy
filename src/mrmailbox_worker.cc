#include <iostream>
#include "mrmailbox_wrap.h"

class MailboxWorker : public Nan::AsyncProgressWorker {
    public:
        MailboxWorker(Nan::Callback *callback, mrmailbox_t *mailbox, int event, uintptr_t data1, uintptr_t data2) 
          : Nan::AsyncProgressWorker(callback), mailbox(mailbox), event(event), data1(data1), data2(data2) {}

        ~MailboxWorker() {}

        void Execute (const Nan::AsyncProgressWorker::ExecutionProgress& progress) {
          std::cout << 'executing' << '\n';
          progress.Send(reinterpret_cast<const char*>(5), sizeof(int));
        }
        void HandleProgressCallback(const char *data, size_t count) {
          std::cout << 'progress here' << '\n';
          v8::Local<v8::Value> argv[] = {
            Nan::New<v8::Integer>(*reinterpret_cast<int*>(const_cast<char*>(data)))
          };
          std::cout << 'callback call' << '\n';
          callback->Call(1, argv);
        }

    private:
        mrmailbox_t *mailbox;
        int event;
        uintptr_t data1;
        uintptr_t data2;
};
