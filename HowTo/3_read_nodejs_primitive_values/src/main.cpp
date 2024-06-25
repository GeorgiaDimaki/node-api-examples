#include "main.h"

#include <node_api.h>
#include <iostream>
#include <stdio.h>


// The following are internal functions, they are not exported to Node.js.
// They are defined so that the code it is easier to read :)

// Disclaimer: It is assumed that the functions are called in the switch above, where type is known.
// Otherwise we would have to also perform a type check before calling the Node API functions
// OR handle any error appropriately. For now there is no error handling.

void readBoolean(napi_env env, napi_value& arg) {
    bool val = false;
    if (napi_get_value_bool(env, arg, &val) != napi_ok) return;
    std::cout << std::endl << "Received a napi_boolean argument with value: " << (val ? "true" : "false") <<std::endl;
}

void readNumber (napi_env env, napi_value& arg) {
    std::cout << std::endl << "Received a napi_number. Read as a(n): \n" << std::endl;
    
    // in JS numbers are always double precision. However, Node API allows us to read them
    // as double, int32, int64 or unit32
    double dval;
    int32_t i32val;
    int64_t i64val;
    uint32_t ui32val;

    if (napi_get_value_double(env, arg, &dval) != napi_ok) return;
    std::cout << "double - " << dval << std::endl;

    if (napi_get_value_int32(env, arg, &i32val) != napi_ok) return;
    std::cout << "int32_t - " << i32val << std::endl;
    
    if (napi_get_value_int64(env, arg, &i64val) != napi_ok) return;
    std::cout << "int64_t - " << i64val << std::endl;

    if (napi_get_value_uint32(env, arg, &ui32val) != napi_ok) return;
    std::cout << "uint32_t - " << ui32val << std::endl;

}

void readString (napi_env env, napi_value& arg) {
    std::cout << std::endl << "Received a napi_string. Read as a(n): \n" << std::endl;

    // > latin1
 
    // You can either preallocate a buffer or create one dynamically. 
    // In this scenario we will create one dynamically. 
    
    char* latin1s = nullptr;
    size_t latin1sLength = 0;
    napi_status status = napi_ok;

    // first call gets the length. Length will not include the null terminator
    if (napi_get_value_string_latin1(env, arg, NULL, 0, &latin1sLength) != napi_ok) return;

    latin1s = new char[latin1sLength + 1];
    // second call gets the string
    if (napi_get_value_string_latin1(env, arg, latin1s, latin1sLength + 1, &latin1sLength) != napi_ok) {
        if (latin1s) delete[] latin1s; // make sure to clean the space allocated
        return;
    }

    std::cout << "latin1 - ";
    for (int i=0; i<latin1sLength; i++) printf("%#x ", latin1s[i]);
    std::cout << std::endl;

    if (latin1s) delete[] latin1s; // make sure to clean the space allocated

    // > utf8
    
    // In the following scenario we will use a static array. If array is not enough for the amount
    // of characters the string will be truncated

    char utf8s[100];
    size_t utf8sLength = 100;
    if (napi_get_value_string_utf8(env, arg, utf8s, utf8sLength, &utf8sLength) != napi_ok) return; 
    
    std::cout << "utf8 - ";
    for (int i=0; i<utf8sLength; i++) printf("%#x ", utf8s[i]);
    std::cout << std::endl;
    
    
    // > utf16

    char16_t utf16s[100];
    size_t utf16sLength = 100;
    if (napi_get_value_string_utf16(env, arg, utf16s, utf16sLength, &utf16sLength) != napi_ok) return; 
    
    std::cout << "utf16 - ";
    for (int i=0; i<utf16sLength; i++) printf("%#x ", utf16s[i]);
    std::cout << std::endl;
    
}

void readBigInt (napi_env env, napi_value& arg) {

    // Node API allows us to read bigint using int64_t and uint64_t. Since bigint can representa
    // a very large number the respective functions return whether conversion was lossless.
    // Finally, there is one function that will allow us to read the digits of the bigint
    // represented by an uint64_t array of "words". If you don't know how large your number
    // will be you can start with either of the int64 or uint64 functions and if you don't get
    // a lossless conversion move on to read the bigint words.
    
    std::cout << std::endl << "Received a napi_bigint. Read as a(n): \n" << std::endl;
    
    // define variables
    int64_t i64val = 0;
    uint64_t ui64val = 0;
    bool lossless = false;

    uint64_t* ui64array = nullptr;
    size_t ui64arrayLength = 0;
    int sign_bit = 0;

    // int64_t
    if(napi_get_value_bigint_int64(env, arg, &i64val, &lossless) != napi_ok) return;
    std::cout << "int64_t - " << i64val << (lossless ? " lossless" : "") << std::endl;

    
    // uint64_t
    if(napi_get_value_bigint_uint64(env, arg, &ui64val, &lossless) != napi_ok) return;
    std::cout << "uint64_t - " << ui64val << (lossless ? " lossless" : "") << std::endl;

    
    // bigint_words 
    if(napi_get_value_bigint_words(env, arg, NULL, &ui64arrayLength, NULL) != napi_ok) return;
    
    // Now that we know the size of the array we can allocate the space and read the words.
    ui64array = new uint64_t[ui64arrayLength];
    if(napi_get_value_bigint_words(env, arg, &sign_bit, &ui64arrayLength, ui64array) != napi_ok) {
        if (ui64array) delete[] ui64array;        
        return;
    }

    std::cout << "uint64_t words - " << (sign_bit == 1 ? "- " : "+ ");
    for (int i=0; i < ui64arrayLength; i++) {
        std::cout <<  ui64array[i] << " ";
    } 

    std::cout << std::endl;

    // release any space we allocated dynamically
    if (ui64array) delete[] ui64array;
}

napi_value mainf(napi_env env, napi_callback_info info) {

    // define variables
    size_t      argc = 1; // number of arguments expected
    napi_value  argv[1];  // array to receive the arguments
    
    napi_valuetype type = napi_undefined; // the type of the argument expected

    if(napi_get_cb_info(env, info, &argc, argv, NULL, NULL) != napi_ok) return NULL;
    if (argc == 0) return NULL; // a later example shows how to throw an error

    // since all arguments are received as napi_values we have to know the type of an 
    // argument we have before being able to process it. So let's first read the argument type
    
    if(napi_typeof(env, argv[0], &type) != napi_ok) return NULL;

    // Depending on the use case, we might expect a specific type or not. 
    // In this example, to demonstrate how you can process a variety of types 
    // we do not expect a specific argument.

    // ES6 types as returned by typeof can be processed using switch statement since napi_valuetype
    // is enumerable
    switch (type)
    {
    case napi_undefined:
        std::cout << std::endl << "Received a napi_undefined argument" << std::endl;
        break;
    case napi_null:
        std::cout << std::endl << "Received a napi_null argument" << std::endl;
        break;
    case napi_boolean:
        readBoolean(env, argv[0]);
        break;
    case napi_number:
        readNumber(env, argv[0]);
        break;
    case napi_string:
        readString(env, argv[0]);
        break;
    case napi_symbol:
        // There is no functionality to process symbols in Node API just yet.
        // You can only create them (napi_create_symbol) or ask for a specific symbol (node_api_symbol_for).
        std::cout << std::endl << "Received napi_symbol." << std::endl;
        break;
    case napi_object:
        // objects are not considered primitive values. They are composed of other primitive values.
        // we will see how to process them later on.
        std::cout << std::endl << "Received napi_object." << std::endl;
        break;
    case napi_function:
        // These objects we can only call.
        std::cout << std::endl << "Received napi_function." << std::endl;
        break;
    case napi_external:
        // This type is for objects we have created using the napi_create_external.
        // This means that they are internal objects we exposed to Node.js by
        // wrapping them in an external object.
        // We will explore external objects in a later example.
        std::cout << std::endl << "Received napi_external." << std::endl;
        break;
    case napi_bigint:
        readBigInt(env, argv[0]);
        break;
    default:
        std::cout << std::endl << "Unknown type received" << std::endl;
    }


    return NULL;
}

