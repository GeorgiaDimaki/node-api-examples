#include "Addon.h"

// necessary import when building a Node API module. This specific import makes sure the module
// you will build will be ABI-stable. ABI stable in short means that if you build for version x.x.x
// you will be able to use your module in Node.js versions after x.x.x. For more details read 
// https://nodejs.org/en/learn/modules/abi-stability.
#include <node_api.h> 

// function to initialize all the functionality of your module.
// env is the Node.js environment
// exports is an object (a Node.js object) used to register your functionality and return it to Node.js
napi_value init_all(napi_env env, napi_value exports) {

  return exports;

}

// A macro used to register the module. First arg should be the name of your module. NODE_GYP_MODULE_NAME
// is used to make sure that what you have in your binding.gyp and what you register here are in sync.
// It can only be used when you are building using node-gyp.
NAPI_MODULE(NODE_GYP_MODULE_NAME, init_all)
