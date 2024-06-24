#include "Addon.h"
#include "main.h"

#include <node_api.h>

napi_value init_all(napi_env env, napi_value exports) {

  // define variables
  napi_value  fn = NULL;

  // export "main" function to Node.js
  // > first create the function object
  if(napi_create_function(env,               // Node.js runtime environment
                          "main",            // the name of the function to export. Can be anything
                          NAPI_AUTO_LENGTH,  // Constant to request automatic computation of the string length
                          mainf,             // the function we want to export
                          NULL,              // this can be a pointer to (C++) data you want to pass to the function when it gets invoked
                          &fn                // the variable that will receive the object created
                          ) != napi_ok) return NULL;
  
  
  // > then register the function object as a named property of the exports object
  if(napi_set_named_property(env, exports, "main", fn) != napi_ok) return NULL; 

  // > return the exports object that should now have the function "main" as a property
  return exports;
  
  /*

  // If you wish to have more control over whether the property will be enumerable, writable etc
  // you can use a property descriptor + napi_define_properties function in place of the 
  // napi_set_named_property function

  napi_property_descriptor desc = {
    "main",
    NULL,
    mainf,
    NULL,
    NULL,
    NULL,
    napi_property_attributes(napi_writable | napi_enumerable | napi_configurable),  // change any property attributes here
    NULL
  };
  // for more on the above structure see: https://nodejs.org/api/n-api.html#napi_property_descriptor

  if (napi_define_properties(env, exports, 1, &desc) != napi_ok) return NULL;
  
  return exports;

  */  

}

NAPI_MODULE(addon, init_all)
