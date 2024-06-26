# How to throw a Node.js error
## Use Case Description

Suppose you have some functionality that can be error prone. You add a try - catch in your C++ code or you add an if statement in your C code. Whatever that is, at the end of the day you need to somehow inform Node.js (the calling environment) that something went wrong. How can you do that?

> Before we continue with more complex operations it might be a good time to take a break and introduce some error handling concepts. In fact one could argue that this could have happened earlier too, but it felt better you experiment a bit with the API before we jump into that.

## Approach

It is expected you are already know how to catch or identify an error and you are at the point of handling it. First of all, handling doesn't always mean you have to throw an error, this discussion is for the case you do. In the Node API world, where all your functions are defined as *napi_callback*s, you are already expected to return a *napi_value* or NULL. In order to throw an error you first have to create it and throw it. Any subsequent calls to the Node API functions will indicate that an exception is pending instead of returning *napi_ok*. It is suggested you try to return as soon as your error is thrown.

Since Node.js has different types of Errors, the Node API also allows us to create different types of errors. You can create plain, type, range, syntax and even fatal (unrecoverable) errors. You have the option to create them and then throw them or throw them right away (with the exception of the fatal errors\exceptions)

In summary:
1. Identify your error
2. Create - throw / throw a Node API error
3. Return

> **Note:** In the code sample the creation of an error has some extra code that shows how you create Node.js string values. If you have hard time following up, please read the section on How to create Node.js values first and then return to this example.

> **Warning:** Watch out! For Syntax Errors the Node API function name is not consistent with the rest! (starts with node_api instead of napi_ )

## Optional Readings
* [Node API Error Handling](https://nodejs.org/api/n-api.html#error-handling)
* [napi_throw_error](https://nodejs.org/api/n-api.html#napi_throw_error)
* [napi_create_error](https://nodejs.org/api/n-api.html#napi_create_error)
* [napi_throw](https://nodejs.org/api/n-api.html#napi_throw)
* [napi_fatal_exception](https://nodejs.org/api/n-api.html#napi_fatal_exception)
* [Fatal Errors](https://nodejs.org/api/n-api.html#fatal-errors)
