# How to create Node.js primitive values
## Use Case Description

After you've mastered how to create "void" functions (functions that return NULL) you are at a point that you need to create some extra functionality that returns something. You want to be simple so you aim for some primitive values first (number, bigint, boolean, string, null, undefined)

## Approach

In a similar way that you could get a JavaScript value as a C value and you had a set of C values supported per type, you can do the same when you create a JavaScript value. Specifically, the same set of C types can be used (with some caution -- see int64_t -> number) to create a specific JavaScript type. So as we know in the Node API all JavaScript values are represented as a napi_value. So our goal is to create a napi_value of a specific JavaScript type (the napi_typeof on it would return one of the predefined types). The Node API create functions are described as follows:

```
napi_status napi_create_<c type>(napi_env, <c type var>, napi_value*)
```

Of course the return value is napi_status so that we can do the error checking and the first parameter is the Node.js runtime environment we are creating the JavaScript value into. The rest is almost self explanatory. Usually you will create a napi_value as a local variable and use &myvar during the function call. The only functios that diverts a bit from this pattern are functions that accept arrays, like the *napi_create_string_* and *napi_create_bigint_words*. In those, apart from the "c type var" you will also need the length of the array you are passing in.

To sum up:

1. Define the (C) variable you are trying to convert to a JS value
2. Define the napi_value variable that you want to create/return
3. Make a call to any of the Node API create functions
4. Return your freshly created napi_value

Oh and don't forget your error handling!

> **Note:** The example is structured as a "Q&A" so that you can experience the creation of different type of primitives through a single "main" function. In comparison to any previous examples, this time main is not "void". You are encouraged to experiment with the code.

## Optional Readings
[Functions to convert from C types to Node-API](https://nodejs.org/docs/latest/api/n-api.html#functions-to-convert-from-c-types-to-node-api)
