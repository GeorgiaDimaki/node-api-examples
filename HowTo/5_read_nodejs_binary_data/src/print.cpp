#include "print.h"

#include <node_api.h>

#include <iostream>
#include <map>

// used to print the array item's type
std::map<napi_typedarray_type, const char*> typeName {
  {napi_int8_array,                   "napi_int8_array"},
  {napi_uint8_array,                  "napi_uint8_array"},
  {napi_uint8_clamped_array,  "napi_uint8_clamped_array"},
  {napi_int16_array,                  "napi_int16_array"},
  {napi_uint16_array,                "napi_uint16_array"},
  {napi_int32_array,                  "napi_int32_array"},
  {napi_uint32_array,                "napi_uint32_array"},
  {napi_float32_array,              "napi_float32_array"},
  {napi_float64_array,              "napi_float64_array"},
  {napi_bigint64_array,            "napi_bigint64_array"},
  {napi_biguint64_array,          "napi_biguint64_array"}
};

void printArrayBuffer (unsigned char* bytes, size_t byteLength, size_t start, size_t dataLength) {

  size_t bytesToPrint = byteLength - start;
  if (dataLength) bytesToPrint = dataLength;

  std::cout << std::endl << "ArrayBuffer (";
  for (size_t i=0; i < bytesToPrint; i++) {
    printf(((i == bytesToPrint - 1) ? "%#x": "%#x, "), bytes[start + i]);
  } 

  std::cout << ")" << "\tshowing: " << bytesToPrint << "/" << byteLength << std::endl << std::endl;

}

void printBuffer (unsigned char* bytes, size_t byteLength) {

  std::cout << std::endl << "Buffer (";
  for (size_t i=0; i < byteLength; i++) {
    printf(((i == byteLength - 1) ? "%#x": "%#x, "), bytes[i]);
  } 

  std::cout << ")" << std::endl << std::endl;
}

void printTypedArray (unsigned char* bytes, size_t byteLength, size_t byteOffset, const napi_typedarray_type& type) {

  std::cout << std::endl << "TypedArray (" << typeName.at(type) << ") (";
  for (size_t i= 0; i < byteLength; i++) {
    printf(((i == byteLength - 1) ? "%#x": "%#x, "), bytes[i]);
  } 

  std::cout << ")   -    byte offset: " << byteOffset << std::endl << std::endl;
}

void printDataView (unsigned char* bytes, size_t byteLength, size_t byteOffset) {

  std::cout << std::endl << "DataView (";
  for (size_t i= 0; i < byteLength; i++) {
    printf(((i == byteLength - 1) ? "%#x": "%#x, "), bytes[i]);
  } 

  std::cout << ")   -    byte offset: " << byteOffset << std::endl << std::endl;
}
