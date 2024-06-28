#include "main.h"

#include <node_api.h>

#include <iostream>


// As defined by the Node API documentation

#define NODE_API_CALL(env, call)                                  \
  do {                                                            \
    napi_status status = (call);                                  \
    if (status != napi_ok) {                                      \
      const napi_extended_error_info* error_info = NULL;          \
      napi_get_last_error_info((env), &error_info);               \
      const char* err_message = error_info->error_message;        \
      bool is_pending;                                            \
      napi_is_exception_pending((env), &is_pending);              \
      /* If an exception is already pending, don't rethrow it */  \
      if (!is_pending) {                                          \
        const char* message = (err_message == NULL)               \
            ? "empty error message"                               \
            : err_message;                                        \
        napi_throw_error((env), NULL, message);                   \
      }                                                           \
      return NULL;                                                \
    }                                                             \
  } while(0)


napi_value create_number (napi_env env) {

  // You can create a number from int32, int64, uint32 and double.
  // Depending on the C type you use the appropriate napi_create function.
  // Try uncommenting any of the lines bellow (only the last uncommented section will be in effect).

  napi_value numberV = NULL;

  NODE_API_CALL(env, napi_create_int32(env, int32_t(5), &numberV));
  // NODE_API_CALL(env, napi_create_uint32(env, uint32_t(25), &numberV));
  // NODE_API_CALL(env, napi_create_int64(env, int64_t(145), &numberV)); // Note: Some int64_t will loose precision! See: JavaScript Number type
  // NODE_API_CALL(env, napi_create_double(env, double(3.14), &numberV));

  return numberV;
}

napi_value create_bigint (napi_env env) {

  // You can create a bigint from int64, uint64 and uint64 array (bigint words).
  // Depending on the C data you have you can use the appropriate napi_create_bigint_ function.
  // Try uncommenting any of the lines bellow (only the last uncommented section will be in effect).

  napi_value bigintV = NULL;

  NODE_API_CALL(env, napi_create_bigint_int64(env, int64_t(12345), &bigintV));
  // NODE_API_CALL(env, napi_create_bigint_uint64(env, uint64_t(1234567), &bigintV));

  // uint16_t words[] = {321, 123};
  // NODE_API_CALL(env, napi_create_bigint_words(env, -1, 2, (uint64_t*)words, &bigintV));
  // The resulting BigInt is calculated as: (–1)sign_bit (words[0] × (2^64)^0 + words[1] × (2^64)^1 + …)

  return bigintV;

}

napi_value create_string (napi_env env) {
  
  // You can create a string from latin1, utf8 and utf16 encoded string, assuming types const char*
  // const char* and const char16_t* respectively.
  // Depending on the C data you have you can use the appropriate napi_create_string_ function.
  // Try uncommenting any of the lines bellow (only the last uncommented section will be in effect).

  napi_value strV = NULL;
  std::string originalStr("Hello World!");
  std::u16string originalUStr(u"Hello World! 🍌");

  NODE_API_CALL(env, napi_create_string_utf8(env, originalStr.c_str(), NAPI_AUTO_LENGTH, &strV));
  // NODE_API_CALL(env, napi_create_string_latin1(env, originalStr.c_str(), NAPI_AUTO_LENGTH, &strV));
  // NODE_API_CALL(env, napi_create_string_utf16(env, originalUStr.c_str(), NAPI_AUTO_LENGTH, &strV));

  // Note: Some of the experimental functionality will not be covered here.

  return strV;
}

napi_value create_boolean (napi_env env, bool isTrue) {
  napi_value booleanV = NULL;
  NODE_API_CALL(env, napi_get_boolean(env, isTrue, &booleanV));
  return booleanV;
}

napi_value create_null (napi_env env) {
  napi_value nullV = NULL;
  NODE_API_CALL(env, napi_get_null(env, &nullV));
  return nullV;
}

napi_value create_undefined (napi_env env) {
  napi_value undefV = NULL;
  NODE_API_CALL(env, napi_get_undefined(env, &undefV));
  return undefV;
}


napi_value mainf(napi_env env, napi_callback_info info) {
  
  // ignore any arguments in this example
  // calling main with params will neither have any effect nor fail.

  std::cout << "Create a primitive value. Enter: "  << std::endl
            << "1. to create a number"              << std::endl
            << "2. to create a string"              << std::endl
            << "3. to create a bigint"              << std::endl
            << "4. to create a true value"          << std::endl
            << "5. to create a false value"         << std::endl
            << "6. to create a null value"          << std::endl
            << "7. to create an undefined value"    << std::endl;

  int choice = 0;

  while (true) {
    std::cout << "> ";
    std::cin >> choice;
    std::cout << std::endl;
    switch (choice)
    {
    case 1:
      return create_number(env);
    case 2:
      return create_string(env);
    case 3:
      return create_bigint(env);
    case 4:
      return create_boolean(env, true);
    case 5:
      return create_boolean(env, false);
    case 6:
      return create_null(env);
    case 7:
      return create_undefined(env);
    default:
      std::cout << "Unknown choice. Please try again." << std::endl << std::endl;
      break;
    }
  }

}

