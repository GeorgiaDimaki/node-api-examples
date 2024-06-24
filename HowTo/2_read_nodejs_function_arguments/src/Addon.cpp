#include "Addon.h"
#include "main.h"

#include <node_api.h>

napi_value init_all(napi_env env, napi_value exports) {

  // export function "main" to Node.js

  napi_value  fn = NULL;
  if(napi_create_function(env,
                          "main", 
                          NAPI_AUTO_LENGTH,
                          mainf, NULL, &fn) != napi_ok) return NULL;

  if(napi_set_named_property(env, exports, "main", fn) != napi_ok) return NULL; 

  return exports;

}

NAPI_MODULE(addon, init_all)
