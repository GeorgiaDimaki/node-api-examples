# How to read a Node.js array
## Use Case Description

As shown in a previous example, reading primitive values is relatively a simple process. However there are more complex objects we have not explored, like the arrays.


## Approach

[Javascript arrays](https://developer.mozilla.org/en-US/docs/Web/JavaScript/Reference/Global_Objects/Array) are objects that store multiple items under a single variable name. When fed into a Node.js function their respective type is *napi_object*. As we will discuss later on *napi_object* is a type used for multiple values. This means that if we intend to read an array we first need to verify that we have received and array as an argument. Once we do that we can proceed reading the array. To read the array we have to read its items/elements one by one. In summary, we have to follow the steps bellow:

1. Verify the argument is a *napi_object* by checking its type.
2. Verify the argument is an array using the function **napi_is_array** function.
3. Read the length of the array using the **napi_get_array_length** function.
4. Loop and read all the elements one by one using the **napi_get_element** function.

Interestingly the last function does not indicate that it is an "array" only function. The reason is that it can be actually used in any type of object to get its "elements" which can be object properties. In fact arrays in JS are a specific type of object where its properties are the array indices ('0', '1', '2' ...).

Another thing worth mentioning is that occassionally you might be dealing with large arrays. Trying to read the elements can exhaust your resources according to Node API documentation, so it is suggested that you make use of *napi_handle_scope*s. You can find more on that in the [Optional Readings](#optional-readings) section bellow.

## Optional Readings
* [More on handle scopes](https://nodejs.org/api/n-api.html#making-handle-lifespan-shorter-than-that-of-the-native-method)
* [napi_is_array](https://nodejs.org/api/n-api.html#napi_is_array)
* [napi_get_array_length](https://nodejs.org/api/n-api.html#napi_get_array_length)
* [napi_get_element](https://nodejs.org/api/n-api.html#napi_get_element)