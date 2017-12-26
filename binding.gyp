{
  "targets": [
    {
      "target_name": "deltachat",
      "sources": [ "src/deltachat.cc" ],
      "include_dirs": [
        "<!(node -e \"require('nan')\")",
        "deltachat-core/src",
        "deltachat-core/libs/libetpan/include/"
      ]
    }
  ]
}
