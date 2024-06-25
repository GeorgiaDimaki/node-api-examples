#include "main.h"

#include <node_api.h>
#include <iostream>
#include <map>

// used to print the array item's type
std::map<napi_valuetype, char*> typeName{
  {napi_undefined,   "napi_undefined"},
  {napi_null,             "napi_null"},
  {napi_boolean,       "napi_boolean"},
  {napi_number,         "napi_number"},
  {napi_symbol,         "napi_symbol"},
  {napi_object,         "napi_object"},
  {napi_string,         "napi_string"},
  {napi_function,     "napi_function"},
  {napi_external,     "napi_external"},
  {napi_bigint,         "napi_bigint"}
};


napi_value mainf(napi_env env, napi_callback_info info) {

  // define variables
  size_t      argc = 1; // number of arguments expected
  napi_value  argv[1];  // array to receive the arguments
  
  napi_valuetype type = napi_undefined; // the type of the argument expected

  if(napi_get_cb_info(env, info, &argc, argv, NULL, NULL) != napi_ok) return NULL;
  if (argc == 0) return NULL; // a later example shows how to throw an error


  // check whether we have a napi_object
  
  if(napi_typeof(env, argv[0], &type) != napi_ok) return NULL;


  if (type != napi_object) {
    std::cout << std::endl << "Argument is not a napi_object" << std::endl << std::endl;
    return NULL;
  }

  // verify we received an array
  bool isArray = false;
  if (napi_is_array(env, argv[0], &isArray) != napi_ok) return NULL;
  if (!isArray) {
    std::cout << std::endl << "The napi_object received is not an array. Aborting!" << std::endl << std::endl;
    return NULL;
  }

  // read array's length
  uint32_t arrayLength = 0;
  if (napi_get_array_length(env, argv[0], &arrayLength) != napi_ok) return NULL;


  // process array's elements
  
  napi_valuetype elementType = napi_undefined;
  napi_value element = NULL;

  std::cout << std::endl << "[ " ;

  for (uint32_t  i=0; i < arrayLength; i++) {

    // if array length is too large you might want to consider opening a handle scope as follows:

    /*
    napi_handle_scope scope;
    if (napi_open_handle_scope(env, &scope) != napi_ok) break;
    */

    if (napi_get_element(env, argv[0], i, &element) != napi_ok) break;
    
    if (napi_typeof(env, element, &elementType) != napi_ok) break;

    std::cout << typeName.at(elementType) << ((i == arrayLength - 1) ? " " : ", ");

    /*
    if (napi_close_handle_scope(env, scope) != napi_ok) break;
    */
  }

  std::cout << "]" << std::endl << std::endl;

  return NULL;
}

