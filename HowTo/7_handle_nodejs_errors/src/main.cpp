#include "main.h"

#include <node_api.h>

#include <iostream>

// addon.c
#include "addon.h"

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

  // let's create a scenario that can return something other than napi_ok

  // define variables
  size_t      argc = 1;
  napi_value  argv[1];
  int64_t intReceived = 0;
  
  if(napi_get_cb_info(env, info, &argc, argv, NULL, NULL) != napi_ok) {
    
    // at this point we ignore the extensive error handling and just return if an error occurs

    const napi_extended_error_info* error_info = NULL;
    bool is_pending = false;
    const char* message = nullptr;
    
    if(napi_get_last_error_info(env, &error_info) != napi_ok) return NULL;

    message = ((error_info == NULL)||(error_info->error_message == NULL))
              ? "An error occured during argument retrieval" 
              :  error_info->error_message; 

    if (napi_is_exception_pending(env, &is_pending) != napi_ok) return NULL;
    if (!is_pending) {
      if (napi_throw_error(env, NULL, message) != napi_ok) return NULL;
    }
  }
  
  // alternatively
  // NODE_API_CALL(env, napi_get_cb_info(env, info, &argc, argv, NULL, NULL));

  if (argc == 0) {
    
    if(napi_throw_error(env, NULL, "Expected at least one argument!") != napi_ok) {
      
      // at this point we ignore the extensive error handling and just return if an error occurs

      const napi_extended_error_info* error_info = NULL;
      bool is_pending = false;
      const char* message = nullptr;
      
      if(napi_get_last_error_info(env, &error_info) != napi_ok) return NULL;

      message = ((error_info == NULL)||(error_info->error_message == NULL))
                ? "An error while attempting to throw an exception" 
                :  error_info->error_message; 

      if (napi_is_exception_pending(env, &is_pending) != napi_ok) return NULL;

      // slightly different approach
      if (is_pending) {
        return NULL;
      }

      if (napi_throw_error(env, NULL, message) != napi_ok) return NULL;
    }


    // alternatively
    // NODE_API_CALL(env, napi_throw_error(env, NULL, "Expected at least one argument!"));

    return NULL; 
  }

  if (napi_get_value_int64(env, argv[0], &intReceived) != napi_ok) {

    // at this point we ignore the extensive error handling and just return if an error occurs

    const napi_extended_error_info* error_info = NULL;
    bool is_pending = false;
    const char* message = nullptr;
    
    if(napi_get_last_error_info(env, &error_info) != napi_ok) return NULL;

    message = ((error_info == NULL)||(error_info->error_message == NULL))
              ? "Wrong argument! An integer was expected." 
              :  error_info->error_message; 

    // the code bellow demonstrates how you can use napi_get_and_clean_last_exception
    // but it is not the suggested way of error handling, since you need to rethrow.
    // In fact, if you debug this you will figure out that there is no exception pending and 
    // so this code will never actually run.
    // It is better to use it when you believe you can handle the exception OR you can
    // do some extra ("safe") work before rethrowing.

    bool isPending;
    if (napi_is_exception_pending(env, &isPending) != napi_ok) return NULL;
    
    if (isPending) {
        napi_value exception = NULL;
        if (napi_get_and_clear_last_exception(env, &exception) != napi_ok) return NULL;
        if (exception == NULL) {
          if (napi_throw_error(env, NULL, message) != napi_ok) return NULL;
        } else {
          if (napi_throw(env, exception) != napi_ok) return NULL;
        }
    }
    else {
        if (napi_throw_error(env, NULL, message)) return NULL;
    }

    return NULL;
  }

  // alternatively
  // NODE_API_CALL(env, napi_get_value_int64(env, argv[0], &intReceived));

  // if no error occured the following will be printed
  std::cout << "Success! Received int: " << intReceived << std::endl << std::endl;
 
  return NULL;
}
