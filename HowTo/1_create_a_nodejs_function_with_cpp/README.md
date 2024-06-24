# How to create a Node.js function with C++

## Use Case Description

For a Node.js addon (dynamically-linked shared objects written in C++) to be useful it must provide some functionality to their users. Functionality in Node.js and JavaScript in general is organized in files, functions or classes. One of the things you might sooner or later wish to do is to define a Node.js function.

## Approach

Let's assume that you have already mastered the concept of modules, addons and how to create a Node.js module with C/C++.
So as you might expect we need to register our function in the object exported to Node.js and this can happen in the form of a property. Apart from that, there are a couple of other things to know. 

First, Node.js expects any function we plan to export to have a specific signature, defined in the Node API as the *napi_callback* signature:

```cpp
typedef napi_value (*napi_callback)(napi_env, napi_callback_info);
```

This means that it only allows for two arguments, the Node.js runtime environment and a napi_callback_info object that carries information about the context in which the callback was invoked, and it returns to Node.js a napi_value object. Examples that follow will dive deeper into those data types and how you can use them.

Second, in order to register the function as a property of your exports object you will first need to create a napi_value object of type napi_function. To do this we will be using the *napi_create_function* function of the Node API.

So, to summarize the above, what we will need to do is:
1. Define our function with respect to the *napi_callback* signature.
2. Use the *napi_create_function* to create the napi_function Node.js object that represents our function.
3. Define a new property in the exports object with our function (specifically the object we created at step 2) as a value. For this we will be using the *napi_set_named_property* function

Last but not least, calls to the Node API like the ones we will be using return back *napi_status*. The *napi_status* is an enum type that communicates to the caller whether the function call was successful or not. In the first case the value returned is **napi_ok** and in the second a value that indicates what type of error occured during the call. This approach is due to the C style of the API, since C does not support exceptions. As a rule of thumb, every time you call a Node API function that returns napi_status you should check whether the returned value is **napi_ok**. If not, then you should handle the error that happened. We will get into more details later on. For now you can simply return *NULL* from your functions when an error occurs.

## Optional Readings
* [Module registration](https://nodejs.org/api/n-api.html#module-registration)
* [napi_set_named_property](https://nodejs.org/api/n-api.html#napi_set_named_property)
* [napi_callback](https://nodejs.org/api/n-api.html#napi_callback)
* [napi_create_function](https://nodejs.org/api/n-api.html#napi_create_function)
* [napi_status](https://nodejs.org/api/n-api.html#napi_status)