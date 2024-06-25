#include "main.h"

#include <node_api.h>
#include <iostream>

napi_value mainf(napi_env env, napi_callback_info info) {

    // define variables
    size_t      argc = 1; // number of arguments expected
    napi_value  argv[1];  // array to receive the arguments

    if(napi_get_cb_info(env, info, &argc, argv, NULL, NULL) != napi_ok) return NULL;

    // The variable argc will receive the actual number of arguments passed to the function.
    // You can decide to throw an error based on the new value of argc.
    // For this example we will fail if the number of arguments is 0

    std::cout << std::endl << "Received " << argc << " arguments" << std::endl;

    if (argc == 0) return NULL; // a later example shows how to throw an error

    // we could also check to see if we have more arguments than required.
    // for now we skip this check.


    /*
    
    // Alternatively you can read any amount of arguments by calling napi_get_cb_info twice!

    size_t argc = 0; // will change after the first call
    napi_value* argv = nullptr;

    // ignore argv in the first call
    if(napi_get_cb_info(env, info, &argc, NULL, NULL, NULL) != napi_ok) return NULL;

    argv = new napi_value[argc]; // create an array with space enough for argc arguments

    // finally read the arguments
    if(napi_get_cb_info(env, info, &argc, argv, NULL, NULL) != napi_ok) return NULL;
    
    std::cout << std::endl << "Received " << argc << " arguments" << std::endl;

    if (argc == 0) return NULL; // a later example shows how to throw an error
    
    */


    return NULL;
}