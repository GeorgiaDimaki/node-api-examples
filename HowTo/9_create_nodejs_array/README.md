# How to create a Node.js array
## Use Case Description

You already know to to create and return primitive values. This is the baseline when it comes to baseline JS value creation. In JavaScript there are more complex types like objects or Arrays. Let's focus our attention on how to create Arrays first.

## Approach

An Array is a special type of an object. In the Node API, in order to create an Array we first have to create it and then fill it with JavaScript items. Now that you know how to create JavaScript primitive values you can use ur fresh knowledge to create array elements. The overall approach looks like follows:

1. Create an array object using the *napi_create_array* function.
2. Create some array elements using the *napi_create_* set of functions. These can be primitive values or complex types.
3. Use the *napi_set_element* function to fill up the array napi_value you create in step 1

If you wish to create an array of a specific size you can also use the *napi_create_array_with_length* function.

## Optional Readings
* [Working with JavaScript properties](https://nodejs.org/api/n-api.html#working-with-javascript-properties)
* [napi_create_array](https://nodejs.org/api/n-api.html#napi_create_array)
* [napi_create_array_with_length](https://nodejs.org/api/n-api.html#napi_create_array_with_length)
* [napi_set_element](https://nodejs.org/api/n-api.html#napi_set_element)