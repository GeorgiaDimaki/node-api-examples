#include "main.h"

#include <node_api.h>

#include <iostream>

napi_value mainf(napi_env env, napi_callback_info info) {

  // Please uncomment the desired section to try different variations.
  // Only uncomment one "throw". In fact if you uncomment more follow up calls will return a status 
  // indicating a previous exception is pending, returning immediatelly. So only the first error
  // set will be thrown.

  const char* code = "YOUR_ERROR_CODE";
  const char* msg = "Your Error Message";

  ////// throw error 

  // /* 

  // > throw a Node.js error
  if (napi_throw_error(env, code, msg) != napi_ok) return NULL;
  // Note: error code is optional, but error message is required!
  
  // // > throw a Node.js Type error
  // if (napi_throw_type_error(env, code, msg) != napi_ok) return NULL;
  
  // // > throw a Node.js Range error
  // if (napi_throw_range_error(env, code, msg) != napi_ok) return NULL;

  // // > throw a Node.js Syntax error
  // if (node_api_throw_syntax_error(env, code, msg) != napi_ok) return NULL;

  // // > throw a Node.js fatal error

  // // this is a special type of error since it can be called even if an exception is pendng.
  // // try uncomment any of the previous napi_throw_ examples along with this one to see this in action.
  // // also, after this call the full process will be terminated.
  // napi_fatal_error("A LOCATION", NAPI_AUTO_LENGTH, msg, NAPI_AUTO_LENGTH);
  // // Note: the location is optional, but error message is required!

  // */
  
  
  
  
  
  
  ////// create and throw error 
  
  /*
  
  // > create

  napi_value error = NULL;
  napi_value errorCode = NULL;
  napi_value errorMessage = NULL;

  // create the errorCode value
  if (napi_create_string_utf8(env, code, NAPI_AUTO_LENGTH, &errorCode) != napi_ok) return NULL;

  // create the errorMessage value
  if (napi_create_string_utf8(env, msg, NAPI_AUTO_LENGTH, &errorMessage) != napi_ok) return NULL;


  // Note: Uncommenting multiple create functions doesn't matter. In fact, the function that updates
  // the error variable last will be the one in effect.

  // Node.js error
  if (napi_create_error(env, errorCode, errorMessage, &error) != napi_ok) return NULL;
  // Note: error code is optional, but error message is required!
  
  // // Type error
  // if (napi_create_type_error(env, errorCode, errorMessage, &error) != napi_ok) return NULL;
  
  // // Range error
  // if (napi_create_range_error(env, errorCode, errorMessage, &error) != napi_ok) return NULL;

  // // Syntax error
  // if (node_api_create_syntax_error(env, errorCode, errorMessage, &error) != napi_ok) return NULL;
  

  // > throw

  // Note: there is only one function that throws any type of error you created.
  if (napi_throw(env, error) != napi_ok) return NULL;

  // // In case you are working with asynchronous functions the code bellow can trigger an 
  // // 'uncaughtException' with no way to recover. 
  // // Here you likely won't see any difference with the call above.
  // if (napi_fatal_exception(env, error) != napi_ok) return NULL;

  */


  return NULL;
}

