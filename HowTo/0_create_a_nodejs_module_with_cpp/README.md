# How to create a Node.js Module

## Use Case Description

The first thing you will probably worry about is how to create a Node.js module from your C/C++ code.
This will be your entry point to any functionality written in C/C++ when loading your module.

## Approach

First of all we need to include the file that describes all the Node API functionality and this is the napi.h. This file ensures that the functions we will be using and the module we will build is going to be [ABI stable](https://nodejs.org/en/learn/modules/abi-stability). This concept might be confusing at first. In short, ABI-stability guarantees that any functionality you use from version x of the Node API will be the same if you decide to to build with version y > x in the future (API backward compatibility). It also guarantees that if you build for version x.x.x of Node.js you will be able to use your module in future versions of Node.js. Each version of the Node API was introduced in a specific Node.js version described by the [Node-API version matrix](https://nodejs.org/api/n-api.html#node-api-version-matrix). You can think of this matrix as the minimun Node.js version you can build for when using N-API version x.


Node.js requires you to define your functionality in a single object that will be then registered to Node.js using a macro defined in napi.h (NODE_MODULE or NODE_MODULE_INIT). We will be using the NODE_MODULE macro specifically, which accepts two arguments, the module's name and a function pointer to the function that initializes the module object. To make our life easier, the Node API describes the signature of this function as follows:

```
napi_value functionName(napi_env env, napi_value exports)
```

This signature allows us to use the "predefined" object *exports* to register the functionality (functions, classes, constants etc) of our module. The argument *env* represents the Node.js runtime environment that loads our module. We will need this for any subsequent calls in the Node API. Finally, the returned value should be the object that has all of our module's functionality defined, in this case the "extended" exports object. Note that we could completely ignore the exports parameter and define our own Node.js object to return. Having exports makes it a bit more intuitive as it looks like the module.exports object we would use if defining functionality in JavaScript.

Defining a function like the one described above and registering our module using the NODE_MODULE macro is enough to bring our new module to life!