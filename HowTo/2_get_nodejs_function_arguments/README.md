# How to get Node.js function arguments

## Use Case Description

Functions in Node API are defined using the *napi_callback* signature. This signature allows for only
two arguments, the Node.js runtime environment and the napi_callback_info object. So how do we retrieve
arguments passed from the user?

## Approach

The *napi_callback_info* object fortunatelly contains all the information we might need, including the arguments, the object the function was called on etc. For now we will be focusing primarily into retrieving the arguments. Node API provides a function we can use to get information from the napi_callback_info object. This function is called napi_get_cb_info. To get the arguments we have to define a napi_value array to store the values.

Depending on whether we expect a specific number of arguments we can define a static or a dynamic array. The former case is straight forward. For the later we will need to use the napi_get_cb_info twice, once to retrieve the amount of arguments passed to the function and once to receive the actual values after we initialize our dynamic array. 

In any case, we will need to pass in a size_t pointer pointing to the number of arguments we are trying to read. This pointer is used by the function as an in-out value. After the call the pointed value will be updated to the actual number of arguments passed in the function. We can use this information not only to create dynamic arrays for the arguments but also to decide whether the amount of arguments we received was correct and if we want to throw an error.

Later on we will see how we can process our freshly retrieved values.

## Optional Readings

* [napi_get_cb_info](https://nodejs.org/api/n-api.html#napi_get_cb_info)