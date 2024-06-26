# How to read Node.js binary data
## Use Case Description

In JS and Node.js there is a set of objects that aim to handle data in a binary form. Specifically there is the concept of an ArrayBuffer which holds binary data that you are able to read through TypedArrays and DataViews. TypedArrays specifically is a set of classes, each one of which is able to read the data using a specific type. For instance a Uint8Array array is a TypedArray with type being the unsigned 8 bit integer. The difference between TypedArrays and DataViews lies at the way the two different types work with endiances. You can read more about them in the [MDN Web Docs](https://developer.mozilla.org/en-US/docs/Web/JavaScript/Reference/Global_Objects/TypedArray). All of those objects will generally be passed in your native functions (functions written using the Node API) as *napi_values* with type *napi_object* and you will have to read them accordingly.


## Approach

The reason there is only one example that covers all of the above types is mostly the fact that the respective Node API functions have similar expectations of inputs/outputs. Of course it also makes sense to talk about them in the same section since they all have to do with binary data. A couple of things to know before we get started are that there is only one function for all different flavors of TypedArrays (as you might have guessed this is a generic type, there are multiple classes of this form, each one handling a different type) and that there is on Node.js specific type, the Buffer, which is specifically a subclass of Uint8Array aimed to provide some extra functionality to the typed array. The Node API functions to read any of the above are named **napi_get_x_info**, where x can be arraybuffer, typedadday, dataview or buffer.

The general approach will look as follows:
1. Check to verify the received object is of the type of interest using a **napi_is_x** function.
2. Define an array (pointer) that will receive the binary data after the Node API function call.
3. Make the call to the specific **napi_get_x_info** function.
4. Use the data as you like.
5. **DO NOT** delete any pointer.

A little bit on the process before we get on the details. First of all, step (2) is vague. To make it simpler, since we are expecting to be reading *bytes* we can define an array of an unsigned 8 bit integer type, like *unsigned char*. Once data is read we can decide how we will be processing them further. Also, as you can see in step (1) we have to first figure out what type of data we received, and this is due to all of the above types coming in as *napi_object*s. It's also good to know that some of these types overlap. For example Node.js Buffer is a subclass of Uint8Array, so the check for buffer and the check for typedarray will both pass. Lastly, step (5) might look a little aggressive. Although it is not pointed out explicitely in the Node API documentation (if you find any mention let me know :blush:), the data returned seem to be pointing to the internal data themselves. It is suggested you treat them as pointers to observe (your functions won't own them). With that, let's get into some details of the specific types.

Overall, the respective Node API functions are almost self explanatory. The simplest type to read is the ArrayBuffer, since you only get a pointer to data and a length back. Same is true for Buffer (it is kept simple since you can process it using the TypedArray interface instead). The other two types, TypedArray and DataView, allow you to also get back their internal ArrayBuffer along with information about where the data begin and end in this ArrayBuffer. In all situations its up to you how many information you actually want to read. If you want to skip something you can just pass NULL to the function and skip it.

This covers most of it. One final note is that, as mentioned in the Node API docs, you should be cautious when reading binary information because your data might get invalidated soon after you read them. One approach to make sure this will not happen is to keep a reference to the data (we have not discussed references yet. Be patient.). It is suggested you keep an eye on the Node API documentation and at least be aware of this scenario when dealing with a faulty function.

The code sample demonstrates two things:
1. How to process a *napi_object* when you actually don't know what type of object you received.
2. How to read binary data that come in as arraybuffer, buffer, typedarray or dataview.

> **Note:** When an object is received the main function intentionally goes through all the types of interest so you can see the potential overlaps. You are encouraged to experiment with the order *napi_is_x* functions are called.

## Optional Readings
* [Interesting article on Buffers](https://blog.risingstack.com/using-buffers-node-js-c-plus-plus/)
* **napi_is_x** functions
    * [napi_is_arraybuffer](https://nodejs.org/api/n-api.html#napi_is_arraybuffer)
    * [napi_is_buffer](https://nodejs.org/api/n-api.html#napi_is_buffer)
    * [napi_is_typedarray](https://nodejs.org/api/n-api.html#napi_is_typedarray)
    * [napi_is_dataview](https://nodejs.org/api/n-api.html#napi_is_dataview)
* **napi_get_x_info** functions
    * [napi_get_arraybuffer_info](https://nodejs.org/api/n-api.html#napi_get_arraybuffer_info)
    * [napi_get_buffer_info](https://nodejs.org/api/n-api.html#napi_get_buffer_info)
    * [napi_get_typedarray_info](https://nodejs.org/api/n-api.html#napi_get_typedarray_info)
    * [napi_get_dataview_info](https://nodejs.org/api/n-api.html#napi_get_dataview_info)