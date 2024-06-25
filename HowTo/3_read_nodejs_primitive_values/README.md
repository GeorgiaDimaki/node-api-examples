# How to read Node.js (JS) primitive values

## Use Case Description

Functions wouldn't be that useful if the user couldn't pass arguments to them. So part of what we will eventually have to do when implementing Node.js functions in C/C++ is to read those arguments and translate them from arguments in the one languagte to the other. Of course the data types of JavaScript and the data types of C/C++ do not map one to one. To allow some flexibility to the API user the Node API defines functions from one JS type to one or more C/C++ types. The first thing you will have to learn is how to read and process primitive types, meaning types that are not composites of other types. In JavaScript these are string, number, bigint, boolean, undefined, null and symbol. Once you understand how to work with those you can move on to more complex types (objects).


## Approach

The Node API functions aimed at reading primitive values have names that start with **napi_get_value_**.  Last part will be a C/C++ type or combination of JS type and C/C++ type to indicate that we read from one type and convert to the other. These function operate on *napi_value*s to extract data stored in them. You might already know what type is the argument you expect but if you don't you have to read the *napi_valuetype* of the *napi_value* object first and then decide how to proceed. Finally, if you call a function on a *napi_value* of the wrong type you will get an exception that indicates that a different type was expected. The type mapping between the languages happens as follows:

* 'undefined' - no mapping
* 'null' - no mapping
* 'boolean' - bool
* 'number' - int32_t, int64_t, uint64_t, double
* 'string' - char* (either latin1 or utf8 encoded), char16_t* (utf16 encoded)
* 'bigint' - int64_t, uint64_t, uint64_t* (array of words for large bigint) 

Obviously whenever you have a JS type that maps to multiple types in C/C++ you can choose the one that fits your use case. Notice that some of them are not there just for convenience, but they are to support different encodings or different argument sizes. Be very mindful especially when working with JS 'number' arguments, since this type internally is implemented using double precision and is not able to fully support the full range of 64 bit integers. Information on that are beyond the scope of this example but you can read more in [MDN Web Docs: Number](https://developer.mozilla.org/en-US/docs/Web/JavaScript/Reference/Global_Objects/Number).

To summarize, to read the napi_value arguments of a function you can:
1. Identify the argument's type using the **napi_typeof** function.
2. Depending on the type, use a **napi_get_value_\<type\>** function to convert the JavaScript value to a C/C++ value. 
3. Handle any conversion error.

> Note: This is an introduction of how to get primitive values. There is a separate sections that is dedicated specifically to objects and how to work with them.