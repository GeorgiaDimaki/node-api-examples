{
  'targets': [
    {
      'target_name': 'example',
      'sources': [           
        "<!@(node -p \"require('fs').readdirSync('src/').map(f=>'src/'+f).join(' ')\")" 
      ],
      "include_dirs": [
        "<(module_root_dir)/src/",
      ], 
      "defines":        [ 'NAPI_CPP_EXCEPTIONS', 'NAPI_EXPERIMENTAL'],
      "cflags":         ["-Wall", "-std=c++14", '-unresolved-symbols=ignore-all'],
      "cflags!":        ["-fno-exceptions"],
      "cflags_cc!":     ["-fno-exceptions"],
      "conditions": [
        ['OS=="win"', { 
          'configurations': {
            'Debug': {
              'msvs_settings': {
                'VCCLCompilerTool': {
                  'RuntimeTypeInfo': 'true',
                  "ExceptionHandling": "1",
                  "AdditionalOptions": ['-std:c++latest'],
                }
              }
            },
            'Release': {
              'msvs_settings': {
                'VCCLCompilerTool': {
                  'RuntimeTypeInfo': 'true',
                  "ExceptionHandling": "1",
                  "AdditionalOptions": ['-std:c++latest'],
                }
              }
            }
          }
        }],
        ['OS=="mac"', {
          "xcode_settings": {
            'GCC_ENABLE_CPP_EXCEPTIONS': 'YES',
            'OTHER_CPLUSPLUSFLAGS' : ['-stdlib=libc++', '-fexceptions', '-frtti'],
            'OTHER_LDFLAGS': ['-stdlib=libc++','-flat_namespace',' -headerpad_max_install_names', '-shared-libgcc', '-ObjC'],
            'MACOSX_DEPLOYMENT_TARGET': '14.0'
          }
        }]
      ]
    },
  ],
}
