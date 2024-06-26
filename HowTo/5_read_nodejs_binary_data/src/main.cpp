#include "main.h"
#include "print.h"

#include <node_api.h>

#include <iostream>


void readArrayBuffer (napi_env env, napi_value& arg, size_t start = 0, size_t dataLength = 0) {

  // > read binary data

  // define variables
  unsigned char* bytes = nullptr;
  size_t byteLength = 0;
  
  // get info
  if (napi_get_arraybuffer_info(env, arg, (void**)&bytes, &byteLength) != napi_ok) return;

  // > use binary data
  printArrayBuffer(bytes, byteLength, start, dataLength);

}

void readBuffer (napi_env env, napi_value& arg) {

  // > read binary data
  
  // define variables
  unsigned char* bytes = nullptr;
  size_t byteLength = 0;

  // get info
  if (napi_get_buffer_info(env, arg, (void**)&bytes, &byteLength) != napi_ok) return;

  // > use binary data
  printBuffer(bytes, byteLength);

}

void readTypedArray (napi_env env, napi_value& arg) {

  // > read binary data

  // define variables
  unsigned char* bytes = nullptr;
  size_t byteLength = 0;
  napi_typedarray_type type;
  napi_value buffer;
  size_t byteOffset = 0;

  // get info
  if (napi_get_typedarray_info(env, arg, &type, &byteLength, (void**)&bytes, &buffer, &byteOffset) != napi_ok) return;


  // > use binary data
  printTypedArray(bytes, byteLength, byteOffset, type);
  readArrayBuffer(env, buffer, byteOffset, byteLength); // read its internal ArrayBuffer
  
}

void readDataView (napi_env env, napi_value& arg) {

  // > read binary data

  // define variables
  unsigned char* bytes = nullptr;
  size_t byteLength = 0;
  napi_value buffer;
  size_t byteOffset = 0;

  // get info
  if (napi_get_dataview_info(env, arg, &byteLength, (void**)&bytes, &buffer, &byteOffset) != napi_ok) return;

  // > use binary data
  printDataView(bytes, byteLength, byteOffset);
  readArrayBuffer(env, buffer, byteOffset, byteLength); // read its internal ArrayBuffer
  
}

napi_value mainf(napi_env env, napi_callback_info info) {

  // > get function arguments
  
  // define variables
  size_t      argc = 1;
  napi_value  argv[1];
  napi_valuetype type = napi_undefined;

  if(napi_get_cb_info(env, info, &argc, argv, NULL, NULL) != napi_ok) return NULL;
  if (argc == 0) return NULL; // a later example shows how to throw an error

  
  std::cout << ">>>>>>>>>>>>>>>>> Process data <<<<<<<<<<<<<<<<<" << std::endl;

  // > check whether we have a napi_object

  if(napi_typeof(env, argv[0], &type) != napi_ok) return NULL;
  if (type != napi_object) {
    std::cout << std::endl << "Argument is not a napi_object" << std::endl << std::endl;
    return NULL;
  }

  // > decide what type of object you are dealing with and call respective functions.

  bool isArrayBuffer = false;
  if (napi_is_arraybuffer(env, argv[0], &isArrayBuffer) != napi_ok) return NULL;
  if (isArrayBuffer) {
    readArrayBuffer(env, argv[0]);
  }

  bool isBuffer = false;
  if (napi_is_buffer(env, argv[0], &isBuffer) != napi_ok) return NULL;
  if (isBuffer) {
    readBuffer(env, argv[0]);
  }

  bool isTypedArray = false;
  if (napi_is_typedarray(env, argv[0], &isTypedArray) != napi_ok) return NULL;
  if (isTypedArray) {
    readTypedArray(env, argv[0]);
  }

  bool isDataView = false;
  if (napi_is_dataview(env, argv[0], &isDataView) != napi_ok) return NULL;
  if (isDataView) {
    readDataView(env, argv[0]);
  }

  // > Check if no binary data received

  if (!(isArrayBuffer | isBuffer | isTypedArray | isDataView)) {
    std::cout << std::endl << "No binary data received!" << std::endl << std::endl;
  }


  return NULL;
}

