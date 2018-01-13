{
  "targets": [
    {
      "target_name": "deltachat",
      "sources": [
        "binding.cc",
        "src/mrmailbox_wrap.cc",
        "src/mrarray_wrap.cc",
        "src/mrmsg_wrap.cc",
        "src/mrchat_wrap.cc",
        "src/mrcontact_wrap.cc",
        "src/mrchatlist_wrap.cc"
      ],
      "libraries": [
        "../deltachat-core/builddir/src/libdeltachat.dylib"
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
