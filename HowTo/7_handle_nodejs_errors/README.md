# How to handle Node.js errors
## Use Case Description

As you might have already noticed, most (if not all) of the Noded API functionality returns **napi_status**. If the returned value is *napi_ok* then we are good to go, everything went as expected. But what if we are faced with an actual error?

## Approach

Error handling is already well documented in the Node API. But let's break down the approach. So first of all, if an error happens during any of your Node API calls you might get a status back that is different from *napi_ok*. Getting an error code (all the suported error codes can be found [here](https://nodejs.org/api/n-api.html#napi_status)) doesn't necessarily mean an exception was thrown. So first of all you have to check if an exception is pending using a call to a function called *napi_is_exception_pending*. If an exception is pending then you can clean up, return from your function and let it be thrown in Node.js. If it is not pending you might decide to actually throw an error yourself using any of the calls we described in the previous section. Occassionally you will receive back a status *napi_pending_exception* which usually means your call to the API returned prematurely due to some exception pending (but not due to error during the call). Now, if an error occured, there is a call you can use to get more information about the error, including an error message. This call is the *napi_get_last_error_info*. You can use these info for your own hapiness or you might actually need it if you want to actively throw an error yourself. One important thing to notice is that this call can be only called immediately after a faulty napi_status was returned. Any subsequent calls to the API can override the error information. 

So, the suggested way of handling an error is the following:
1. Identify an error occured (check whether napi_ok was returned after every call to Node API)
2. Once you see an error might have occured make a call to *napi_get_last_error_info* to learn more.
3. **copy** the error message if you think you will need it later. The structure returned in step 3 can get overwritten!
4. Make a call to the *napi_is_exception_pending* to check if an exception was indeed thrown.
5. If an exception was thrown clean up and return
6. If an exception was not thrown, decide if you want to throw an error.

et voilà!

There is one last note to make. There is a change an exception is thrown but you are very positive you can handle it OR you have some extra stuff to finish (and you can achieve that safely) before you return. In this case you can use the *napi_get_and_clear_last_exception* to get and clear the last exception. You can keep the error returned from the call and rethrow it later!

> **Note:** The sample code demonstrated is implemented in a way that demonstrates different approaches. One thing you will notice is that the amount of code to perform error handling in place is unsustainable. The alternative proposed by the Node API documentation is the definition of a macro function. You can define your own macros, functions or whatever is more useful for your library. Regardless, it might be a good idea to define your error handling scheme early on in the development process.

## Optional Readings
* [Error Handling](https://nodejs.org/api/n-api.html#error-handling)
* [Node API Exceptions](https://nodejs.org/api/n-api.html#exceptions)
* [napi_get_last_error_info](https://nodejs.org/api/n-api.html#napi_get_last_error_info)
* [napi_is_exception_pending](https://nodejs.org/api/n-api.html#napi_is_exception_pending)
* [napi_get_and_clear_last_exception](https://nodejs.org/api/n-api.html#napi_get_and_clear_last_exception)
* [See sample code in Node.js Version Matrix section](https://nodejs.org/api/n-api.html#node-api-version-matrix)
* [napi_status](https://nodejs.org/api/n-api.html#napi_status)