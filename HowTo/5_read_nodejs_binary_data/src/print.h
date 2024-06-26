#pragma once

#include <node_api.h>

void printArrayBuffer (unsigned char* bytes, size_t byteLength, size_t start = 0, size_t dataLength = 0);

void printBuffer (unsigned char* bytes, size_t byteLength);

void printTypedArray (unsigned char* bytes, size_t byteLength, size_t byteOffset, const napi_typedarray_type& type);

void printDataView (unsigned char* bytes, size_t byteLength, size_t byteOffset);
