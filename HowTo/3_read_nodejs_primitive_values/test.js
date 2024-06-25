const { main } = require('.') // will require the folder test.js is in.
// since the folder has a package.json we can load the "example" module without installing it.

// Since main is a named export we can use the above syntax to load it.

// let's call main with different type of arguments

main(undefined)          // undefined

main(null)               // null

main(true)               // boolean

main(3.14)               // number

main(1234n)              // bigint 

main("hi🍌")            // unicode

main("hello")            // latin1

main(Symbol("hello"))    // symbol
