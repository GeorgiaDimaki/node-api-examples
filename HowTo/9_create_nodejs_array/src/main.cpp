#include "main.h"

#include <node_api.h>


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


napi_value mainf(napi_env env, napi_callback_info info) {
 
  // let's create an this array: ["hello", 7, true]

  napi_value myArray = NULL;
  napi_value hello = NULL;
  napi_value seven = NULL;
  napi_value trueV = NULL;

  NODE_API_CALL(env, napi_create_array(env, &myArray));

  NODE_API_CALL(env, napi_create_string_utf8(env, "hello", NAPI_AUTO_LENGTH, &hello));
  NODE_API_CALL(env, napi_create_int32(env, int32_t(7), &seven));
  NODE_API_CALL(env, napi_get_boolean(env, true, &trueV));

  NODE_API_CALL(env, napi_set_element(env, myArray, 0, hello));
  NODE_API_CALL(env, napi_set_element(env, myArray, 1, seven));
  NODE_API_CALL(env, napi_set_element(env, myArray, 2, trueV));

  return myArray;
}

