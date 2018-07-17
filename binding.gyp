{
  "targets": [
    {
      "target_name": "deltachat",
      "sources": [
        "binding.cc",
        "src/dc_context_wrap.cc",
        "src/dc_array_wrap.cc",
        "src/dc_msg_wrap.cc",
        "src/dc_chat_wrap.cc",
        "src/dc_contact_wrap.cc",
        "src/dc_chatlist_wrap.cc"
      ],
      "libraries": [
        "../deltachat-core/builddir/src/libdeltachat.so"
      ],
      "conditions": [
        [ 'OS=="mac"', {
          "xcode_settings": {
            'OTHER_CPLUSPLUSFLAGS' : ['-std=c++11','-stdlib=libc++', '-v'],
            'OTHER_LDFLAGS': ['-stdlib=libc++'],
            'GCC_ENABLE_CPP_EXCEPTIONS': 'YES'
          }
        }]
      ],
      "cflags_cc!": [ "-fno-rtti", "-fno-exceptions" ],
      "cflags!": [ "-fno-exceptions" ],
      "include_dirs": [
        "<!(node -e \"require('nan')\")",
        "deltachat-core/src",
        "deltachat-core/libs/libetpan/include/"
      ]
    }
  ]
}
